/*
** EPITECH PROJECT, 2023
** ai
** File description:
** ZappyAI
*/

#include "ZappyAI.hpp"

ZappyAI::ZappyAI()
{
    FD_ZERO(&(this->_read_socket));
    FD_ZERO(&(this->_write_socket));
    memset(this->_inventory, 0, TOTAL_INVENTORY * sizeof(int));
    this->_targetPos.x = 0;
    this->_targetPos.y = 0;
    this->setRessourceToHave();
}

ZappyAI::~ZappyAI()
{
    this->removeFdInFdset(this->_communication.getFd());
    this->_connection.Disconnect();
}

int ZappyAI::init(const std::vector<std::string> &argvList)
{
    bool portSet = false;
    bool nameSet = false;
    bool argRecognized = false;
    int out = INIT_OK;

    for (size_t i = 1; i < argvList.size(); ++i) {
        argRecognized = false;
        for (size_t k = 0; k < PARAM_FUNC_NBR; ++k) {
            if (argvList[i].compare(PARAMETER_FUNC[k].paramStr) == 0) {
                argRecognized = true;
                if (argvList[i].compare(PARAMETER_FUNC[AIFLAG_PORT].paramStr) == 0)
                    portSet = true;
                if (argvList[i].compare(PARAMETER_FUNC[AIFLAG_NAME].paramStr) == 0)
                    nameSet = true;
                out = PARAMETER_FUNC[k].paramFunc(argvList, i, *this);
                if (out != INIT_OK)
                    return (out);
            }
        }
        if (!argRecognized) {
            std::cerr << "Unknown argument " << i << ": \"" << argvList[i] << "\"\n";
            return (INIT_KO);
        }
    }
    if (!portSet) {
        std::cerr << "Port is not set. (" <<
        PARAMETER_FUNC[AIFLAG_PORT].paramStr << ")" << std::endl;
        return (INIT_KO);
    }
    if (!nameSet) {
        std::cerr << "Team name is not set. (" <<
        PARAMETER_FUNC[AIFLAG_NAME].paramStr << ")" << std::endl;
        return (INIT_KO);
    }
    return (INIT_OK);
}

void ZappyAI::setName(const std::string &name)
{
    this->_name = name;
    this->generateCipherList();
}

std::string ZappyAI::getName(void) const
{
    return (this->_name);
}

void ZappyAI::setPort(uint32_t port)
{
    this->_port = port;
}

uint32_t ZappyAI::getPort(void) const
{
    return (this->_port);
}

void ZappyAI::setMachine(const std::string &machine)
{
    this->_machine = machine;
}

std::string ZappyAI::getMachine(void) const
{
    return (this->_machine);
}


void ZappyAI::addFdInFdset(int fd)
{
    FD_SET(fd, &(this->_read_socket));
    FD_SET(fd, &(this->_write_socket));
}

void ZappyAI::removeFdInFdset(int fd)
{
    FD_CLR(fd, &(this->_read_socket));
    FD_CLR(fd, &(this->_write_socket));
}

void ZappyAI::displayParameters(void)
{
    std::cout << std::endl;
    std::cout << "---------- Connection informations ----------" << std::endl;
    std::cout << "\tMachine   : " << this->_machine << std::endl;
    std::cout << "\tPort      : " << this->_port << std::endl;
    std::cout << "\tTeam name : " << this->_name << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::endl;
}

bool ZappyAI::checkServerPackage(void)
{
    std::string data;

    std::cout << "Checking server..." << std::endl;
    if (this->_communication.getlineWait(data) != 0)
        return (false);
    if (data.compare(SERVER_EXPECTED_PACKAGE) != 0) {
        std::cerr << "Wrong package received, expecting \"WELCOME\\n\"." << std::endl;
        return (false);
    }
    std::cout << "[OK]" << std::endl;
    return (true);
}

bool ZappyAI::joinTeam(void)
{
    std::string data;

    std::cout << "Joining \"" << this->_name << "\" team..." << std::endl;
    this->_communication.writeData(this->_name + "\n", this->_name.length() + 1);
    this->_communication.refresh();
    this->_communication.refresh();
    if (this->_communication.getlineWait(data) != 0)
        return (false);
    data[data.length() - 1] = '\0';
    if (!strIsDigit(data) || atoi(data.c_str()) < 0) {
        std::cerr << "Invalid player ID: " << data << !strIsDigit(data) << (atoi(data.c_str()) < 0) << std::endl;
        return (false);
    }
    this->_playerId = atoi(data.c_str());
    std::cout << "[OK]" << std::endl;
    return (true);
}

bool ZappyAI::initMap(void)
{
    std::string data;
    std::stringstream line;
    int mapX;
    int mapY;

    std::cout << "Getting map size..." << std::endl;
    if (this->_communication.getlineWait(data) != 0)
        return (false);
    line.str(data);
    getline(line, data, ' ');
    if (!strIsDigit(data) || atoi(data.c_str()) < 0) {
        std::cerr << "Invalid X map size: " << data << std::endl;
        return (false);
    }
    mapX = atoi(data.c_str());
    getline(line, data, '\n');
    if (!strIsDigit(data) || atoi(data.c_str()) < 0) {
        std::cerr << "Invalid Y map size: " << data << std::endl;
        return (false);
    }
    mapY = atoi(data.c_str());
    // this->_map.resize(mapY);
    // for (int i = 0; i < mapY; ++i) {
    //     this->_map[i].resize(mapX);
    //     for (int k = 0; k < mapX; ++k)
    //         this->_map[i].resize(TOTAL_ELEM_ON_TILE);
    // }
    std::cout << "[OK] {" << mapX << ", " << mapY << "}" << std::endl;
    return (true);
}

bool ZappyAI::connectToServer(void)
{
    std::cout << "Attempting connect to: " << this->_machine << ":" << this->_port << std::endl;
    if (!this->_connection.Connect(this->_machine, this->_port)) {
        std::cerr << "Connection failed" << std::endl;
        return (false);
    }
    std::cout << "[OK]" << std::endl;
    std::cout << "Initializing protocol..." << std::endl;
    this->_communication.setFd(this->_connection.FD());
    this->addFdInFdset(this->_connection.FD());
    if (!this->checkServerPackage())
        return (false);
    if (!this->joinTeam())
        return (false);
    if (!this->initMap())
        return (false);
    return (true);
}

bool ZappyAI::charExist(char charToCheck)
{
    if (charToCheck < '\0')
        return (true);
    for (int i = ' '; i <= '~'; ++i) {
        if (this->_cipherList[i] == charToCheck)
            return (true);
    }
    return (false);
}

void ZappyAI::generateCipherList(void)
{
    int cipherPart2;
    int cipherStep = 0;
    int nameLen = this->_name.length();

    for (size_t i = 0; i < 127; ++i)
        this->_cipherList[i] = i;
    for (int i = ' '; i <= '~'; ++i) {
        cipherStep = i;
        for (size_t k = 0; k < 20 && (charExist(cipherStep) || k == 0); ++k) {
            switch (cipherStep % 2) {
                case 0:
                    cipherStep += this->_name.c_str()[i % nameLen];
                    break;
                case 1:
                    cipherStep -= this->_name.c_str()[i % nameLen];
                    break;
            }
            while (cipherStep > '~')
                cipherStep = ' ' + cipherStep - '~';
            while (cipherStep < ' ')
                cipherStep = '~' - cipherStep - ' ';
        }
        if (charExist(cipherStep)) {
            cipherPart2 = (i % 2 == 0) ? ' ' : '~';
            while (cipherPart2 >= ' ' && cipherPart2 <= '~' && charExist(cipherStep)) {
                cipherStep = cipherPart2;
                cipherPart2 += 1 - ((i % 2 != 0) * 2);
            }
        }
        this->_cipherList[i] = cipherStep;
    }
}

void ZappyAI::cipherStr(std::string &str)
{
    size_t strLen = str.length();

    for (size_t i = 0; i < strLen; ++i) {
        if (str[i] >= '\0')
            str[i] = this->_cipherList[static_cast<int>(str[i])];
    }
}

void ZappyAI::uncipherStr(std::string &str)
{
    size_t strLen = str.length();

    for (size_t i = 0; i < strLen; ++i) {
        for (size_t k = 0; k < '~'; ++k) {
            if (str[i] == this->_cipherList[k]) {
                str[i] = k;
                break;
            }
        }
    }
}

int ZappyAI::handlePackageReception(enum AIResponse_e expectedResponse, std::string &str)
{
    int out;

    while (true) {
        out = this->_communication.receivePackage(str);
        switch (out) {
            case RESPONSE_EJECT:
                std::cout << "Eject" << std::endl;
                break;
            case RESPONSE_MESSAGE:
                storeMessage(str);
                break;
            default:
                if (out != expectedResponse) {
                    if (out == RESPONSE_DISCONNECTION || out == RESPONSE_DEAD) {
                        this->_alive = false;
                        return (-1);
                    }
                    return (0);
                }
                return (1);
        }

    }
    return (0);
}

void ZappyAI::setRessourceToHave(void)
{
    memset(this->_ressourceToHave, 0, TOTAL_INVENTORY * sizeof(int));

    for (size_t i = this->_playerLevel; i < TOTAL_ELEVATION; ++i) {
        for (size_t k = 0; k < TOTAL_INVENTORY; ++k) {
            this->_ressourceToHave[k] += ELEVATION_REQUIREMENT[i][k] * 2;
        }
    }
}

int ZappyAI::handlePackageReception(enum AIResponse_e expectedResponse)
{
    std::string str;

    return (this->handlePackageReception(expectedResponse, str));
}

void ZappyAI::surviveBehaviour(void)
{
    t_coords relPos;

    if (PRINT_ACTION)
        std::cout << "SURVIVE BEHAVIOUR" << std::endl;
    while (this->_inventory[ELEM_FOOD] < 10 && this->_alive) {
        if (this->lookFor(ELEM_FOOD, relPos) > 0) {
            this->takeAll(ELEM_FOOD);
            std::cout << "Relative START " << relPos.x << " " << relPos.y << " " << this->_direction << std::endl;
            while (!this->moveTowardRelativeCoord(relPos) && this->_alive) {
                std::cout << "Relative " << relPos.x << " " << relPos.y << " " << this->_direction << std::endl;
                this->takeAll(ELEM_FOOD);        
            }
            std::cout << "Relative OK " << relPos.x << " " << relPos.y << " " << this->_direction << std::endl;
        } else {
            this->moveRandom(relPos);
        }
        this->inventory();
    }
}

void ZappyAI::elevationBehaviour(enum e_elemOnTile seekedItem)
{
    t_coords relPos;
    std::vector<int> itemList;

    if (PRINT_ACTION)
        std::cout << "ELEVATION BEHAVIOUR " << seekedItem << std::endl;
    if (seekedItem != TOTAL_INVENTORY && seekedItem >= 0 &&
    this->lookFor(seekedItem, relPos) > 0) {
        std::cout << relPos.x << " " << relPos.y << " " << this->_direction << std::endl;
        this->moveTowardRelativeCoord(relPos);
        this->takeAll(ELEM_FOOD);
        this->takeAll(seekedItem);
        this->lookResourceOnTile(itemList);
        this->takeUsefulResource(itemList);
    } else {
        this->moveRandom(this->_targetPos);
    }
}

void ZappyAI::run(void)
{
    int seekedItem;

    this->_playerId = rand();
    while (this->_alive) {
        if (PRINT_ACTION)
            std::cout << "LOOP START" << std::endl;
        seekedItem = tryElevate();
        if (seekedItem == ELEM_FOOD)
            this->surviveBehaviour();
        // if (this->_inventory[ELEM_FOOD] < 30)
        //     this->takeAll(ELEM_FOOD);
        if (seekedItem == TOTAL_ELEM_ON_TILE)
            this->elevation();
        this->elevationBehaviour(static_cast<enum e_elemOnTile>(seekedItem));
        this->readMessageBuffer();
    }
    std::cout << "dead" << std::endl;
}

bool ZappyAI::inventory(void)
{
    std::string str;
    std::string itemStr;
    std::string itemName;
    std::string itemStrQuantity;
    std::stringstream stream;
    std::stringstream itemStream;

    this->_communication.sendPackage(ZP_INVENTORY);
    if (this->handlePackageReception(RESPONSE_OTHER, str) != 1)
        return (false);
    if (PRINT_ACTION)
        std::cout << "Inventory: " << str << std::endl;
    str[0] = ' ';
    str[str.length() - 2] = ' ';
    stream.str(str);
    while (getline(stream, itemStr, ',')) {
        itemStream.clear();
        itemStream.str(itemStr);
        itemName = "";
        while (getline(itemStream, itemName, ' ') &&
        itemName.compare("") == 0);
        if (itemName.compare("") == 0)
            return (false);
        itemStrQuantity = "";
        while (getline(itemStream, itemStrQuantity, ' ') &&
        itemStrQuantity.compare("") == 0);
        if (itemStrQuantity.compare("") == 0)
            return (false);
        for (size_t i = 0; i < TOTAL_INVENTORY; ++i) {
            if (itemName.compare(INVENTORY_PAIR[i].item_name) == 0) {
                this->_inventory[INVENTORY_PAIR[i].item_type] = atoi(itemStrQuantity.c_str());
                break;
            }
        }
    }
    // for (size_t i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
    //     std::cout << this->_inventory[INVENTORY_PAIR[i].item_type] << " ";
    // }
    // std::cout << std::endl;
    return (true);
}

bool ZappyAI::look(void)
{
    std::string str;
    std::string strTile;
    std::string strElem;
    std::vector<int> elemOnTile(TOTAL_ELEM_ON_TILE);
    std::stringstream stream;
    std::stringstream streamTile;

    this->_communication.sendPackage(ZP_LOOK);
    if (this->handlePackageReception(RESPONSE_OTHER, str) != 1)
        return (false);
    if (PRINT_ACTION)
        std::cout << "Look: " << str << std::endl;
    str[0] = ' ';
    str[str.length() - 2] = ' ';
    this->_lookResult.clear();
    this->_lookDone = true;
    stream.str(str);
    while (getline(stream, strTile, ',')) {
        streamTile.clear();
        streamTile.str(strTile);
        std::fill(elemOnTile.begin(), elemOnTile.end(), 0);
        while (getline(streamTile, strElem, ' ')) {
            for (size_t i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
                if (strElem.compare(INVENTORY_PAIR[i].item_name) == 0) {
                    ++(elemOnTile[INVENTORY_PAIR[i].item_type]);
                    break;
                }
            }
        }
        this->_lookResult.push_back(elemOnTile);
    }
    return (true);
}

bool ZappyAI::forward(void)
{
    if (PRINT_ACTION)
        std::cout << "Forward: " << this->_direction << std::endl;
    this->_communication.sendPackage(ZP_FORWARD);
    if (this->handlePackageReception(RESPONSE_OK) != 1)
        return (false);
    this->_lookDone = false;
    return (true);
}

void ZappyAI::updateRelativeCoord(t_coords &relativeCoord)
{
    switch (this->_direction) {
        case DIR_NORTH:
            --(relativeCoord.y);
            break;
        case DIR_SOUTH:
            ++(relativeCoord.y);
            break;
        case DIR_EAST:
            --(relativeCoord.x);
            break;
        case DIR_WEST:
            ++(relativeCoord.x);
            break;
    }
}

bool ZappyAI::forward(t_coords &relativeCoord)
{
    if (!this->forward())
        return (false);
    this->updateRelativeCoord(relativeCoord);
    return (true);
}

bool ZappyAI::right(void)
{
    if (PRINT_ACTION)
        std::cout << "Right: " << std::endl;
    this->_communication.sendPackage(ZP_LEFT);
    if (this->handlePackageReception(RESPONSE_OK) != 1)
        return (false);
    this->_direction = (this->_direction + 1) % TOTAL_DIRECTION;
    this->_lookDone = false;
    return (true);
}

bool ZappyAI::left(void)
{
    if (PRINT_ACTION)
        std::cout << "Left: " << std::endl;
    this->_communication.sendPackage(ZP_RIGHT);
    if (this->handlePackageReception(RESPONSE_OK) != 1)
        return (false);
    this->_direction = (this->_direction + TOTAL_DIRECTION - 1) % TOTAL_DIRECTION;
    this->_lookDone = false;
    return (true);
}

int ZappyAI::take(enum e_elemOnTile elem, int count)
{
    int out;
    int elemSet = 0;
    int elemIndex = -1;

    if (PRINT_ACTION)
        std::cout << "Take: " << elem << std::endl;
    for (int i = 0; i < TOTAL_INVENTORY; ++i) {
        if (INVENTORY_PAIR[i].item_type == elem) {
            elemIndex = i;
            break;
        }
    }
    if (elemIndex == -1)
        return (elemSet);
    for (int i = 0; elemIndex != -1 && i < count; ++i) {
        this->_communication.sendPackage(ZP_TAKE_OBJ, INVENTORY_PAIR[elemIndex].item_name);
        out = this->handlePackageReception(RESPONSE_OK);
        if (out < 0 || out == RESPONSE_KO)
            return (elemSet);
        this->_lookDone = false;
        elemSet += (out == 1);
        this->_inventory[elem] += (out == 1);
    }
    return (true);
}

int ZappyAI::set(enum e_elemOnTile elem, int count)
{
    int out;
    int elemSet = 0;
    int elemIndex = -1;

    if (PRINT_ACTION)
        std::cout << "Set: " << elem << " x" << count << std::endl;
    for (int i = 0; i < TOTAL_INVENTORY; ++i) {
        if (INVENTORY_PAIR[i].item_type == elem) {
            elemIndex = i;
            break;
        }
    }
    for (int i = 0; elemIndex != -1 && i < count && this->_inventory[elem] > 0; ++i) {
        this->_communication.sendPackage(ZP_SET_OBJ, INVENTORY_PAIR[elemIndex].item_name);
        out = this->handlePackageReception(RESPONSE_OK);
        if (out < 0 || out == RESPONSE_KO)
            return (elemSet);
        this->_lookDone = false;
        elemSet += (out == 1);
        this->_inventory[elem] -= (out == 1);
    }
    return (elemSet);
}

bool ZappyAI::broadcast(const std::string &msg, bool cipher)
{
    std::string tmpStr = msg;

    if (cipher)
        this->cipherStr(tmpStr);
    this->_communication.sendPackage(ZP_BROADCAST, tmpStr);
    if (this->handlePackageReception(RESPONSE_OK) != 1)
        return (false);
    return (true);
}

int ZappyAI::connectNbr(void)
{
    std::string str;

    this->_communication.sendPackage(ZP_CONNECT_NBR);
    if (this->handlePackageReception(RESPONSE_OTHER, str) != 1 &&
    !strIsDigit(str))
        return (-1);
    return (atoi(str.c_str()));
}

bool ZappyAI::fork(void)
{
    this->_communication.sendPackage(ZP_FORK);
    return (this->handlePackageReception(RESPONSE_OK) == 1);
}

bool ZappyAI::eject(void)
{
    this->_communication.sendPackage(ZP_EJECT);
    return (this->handlePackageReception(RESPONSE_OK) == 1);
}

bool ZappyAI::elevation(void)
{
    std::string str;

    this->_communication.sendPackage(ZP_INCANTATION);
    this->handlePackageReception(RESPONSE_OTHER);
    // if (str.compare("Elevation underway\n") != 0)
    //     return (false);
    if (this->handlePackageReception(RESPONSE_OTHER, str) != 1)
        return (false);
    ++(this->_playerLevel);
    if (PRINT_ACTION)
        std::cout << "Elevation success: " << this->_playerLevel << std::endl;
    return (true);
}


void ZappyAI::turn180(void)
{
    this->left();
    this->left();
}

void ZappyAI::turnTo(enum e_playerDirection direction)
{
    if (direction == this->_direction)
        return;
    if ((this->_direction + 1) % TOTAL_DIRECTION == direction) {
        this->right();
    } else if (direction % 2 == 1) {
        this->left();
    } else if (direction != DIR_UNDEF) {
        this->turn180();
    }
    this->_direction = direction;
}

bool ZappyAI::moveTowardRelativeCoord(t_coords &relativeCoord)
{
    bool xOk = (relativeCoord.x == 0);
    bool yOk = (relativeCoord.y == 0);
    enum e_playerDirection finalDirection = DIR_UNDEF;

    if (xOk && yOk)
        return (true);
    if (!yOk)
        finalDirection = (relativeCoord.y < 0) ? DIR_SOUTH : DIR_NORTH;
    if (!xOk && finalDirection != this->_direction)
        finalDirection = (relativeCoord.x < 0) ? DIR_WEST : DIR_EAST;
    this->turnTo(finalDirection);
    this->forward(relativeCoord);
    return (false);
}


void ZappyAI::moveRandom(void)
{
    int randTurn = rand() % 3;

    switch (randTurn) {
        case 0:
            this->left();
            break;
        case 1:
            this->right();
            break;
    }
    this->forward();
}

void ZappyAI::moveRandom(t_coords &relativeCoord)
{
    int randTurn = rand() % 3;

    switch (randTurn) {
        case 0:
            this->left();
            break;
        case 1:
            this->right();
            break;
    }
    this->forward(relativeCoord);
}


void ZappyAI::lookItemList(std::vector<int> &itemList)
{
    itemList.resize(TOTAL_ELEM_ON_TILE);
    std::fill(itemList.begin(), itemList.end(), 0);
    if (!this->_lookDone && !this->look())
        return;
    for (size_t i = 0; i < this->_lookResult.size(); ++i) {
        for (size_t k = 0; k < itemList.size(); ++k)
            itemList[k] += this->_lookResult[i][k];
    }
}

void ZappyAI::lookResourceOnTile(std::vector<int> &itemList)
{
    itemList.resize(TOTAL_ELEM_ON_TILE);
    std::fill(itemList.begin(), itemList.end(), 0);
    if (!this->_lookDone && !this->look())
        return;
    if (this->_lookResult.size() <= 0)
        return;
    itemList = this->_lookResult[0];
}


int ZappyAI::lookFor(enum e_elemOnTile seekedElem, t_coords &relativeCoord)
{
    int elemCount = 0;
    int tmp;
    int width;

    if (PRINT_ACTION)
        std::cout << "Look for:" << std::endl;
    if ((!this->_lookDone && !this->look()) ||
    this->_lookResult.size() <= 0)
        return (0);
    if (this->_lookResult[0][seekedElem] > 0) {
        relativeCoord.x = 0;
        relativeCoord.y = 0;
        return (this->_lookResult[0][seekedElem]);
    }
    relativeCoord.y = 1;
    width = 3;
    relativeCoord.x = -width / 2;
    for (size_t i = 1; i < this->_lookResult.size(); ++i) {
        if (relativeCoord.x > width / 2) {
            width += 2;
            relativeCoord.x = -width / 2;
            ++(relativeCoord.y);
        }
        if (this->_lookResult[i][seekedElem] > 0) {
            relativeCoord.l = i;
            elemCount = this->_lookResult[i][seekedElem];
            break;
        }
        ++(relativeCoord.x);
    }
    for (int i = 0; i < this->_direction; ++i) {
        tmp = relativeCoord.y;
        relativeCoord.y = -relativeCoord.x;
        relativeCoord.x = tmp;
    }
    return (elemCount);
}

int ZappyAI::takeAll(enum e_elemOnTile elem)
{
    t_coords coords;
    int elemToTake = this->lookFor(elem, coords);


    if (elem == ELEM_FOOD)
    // if (PRINT_ACTION)
    //     std::cout << "Take all: " << elem << std::endl;
    // if (elemToTake <= 0 || !ON_RELATIVE_TILE(coords))
    //     return (0);
    std::cout << "Take all: food " << this->take(elem, elemToTake) << std::endl;
    return (1);
}

void ZappyAI::takeUsefulResource(const std::vector<int> &itemList)
{
    for (size_t i = 0; i < TOTAL_INVENTORY; ++i) {
        if (this->_inventory[i] <
        this->_ressourceToHave[i] &&
        itemList[i] > 0)
            takeAll(static_cast<enum e_elemOnTile>(i));
    }
    this->_lookDone = false;
}

bool ZappyAI::setObjectForElevation(int level)
{
    for (size_t i = 0; i < TOTAL_INVENTORY; ++i) {
        // std::cout << i << " " << this->_inventory[i] << " " <<
        // ELEVATION_REQUIREMENT[level][i] << " " <<
        // (this->_inventory[i] < ELEVATION_REQUIREMENT[level][i]) << std::endl;
        if (this->_inventory[i] < ELEVATION_REQUIREMENT[level][i])
            return (false);
    }
    for (size_t i = 0; i <  TOTAL_INVENTORY; ++i)
        this->set(static_cast<enum e_elemOnTile>(i), ELEVATION_REQUIREMENT[level][i]);
    return (true);
}

int ZappyAI::tryElevate(void)
{
    if (PRINT_ACTION)
        std::cout << "Try elevate" << std::endl;
    this->inventory();
    if (this->_inventory[ELEM_FOOD] < 5)
        return (ELEM_FOOD);
    for (size_t i = 0; i < TOTAL_INVENTORY; ++i) {
        if (this->_inventory[i] < ELEVATION_REQUIREMENT[this->_playerLevel][i])
            return (i);
    }
    if (this->_playersReady != ELEVATION_REQUIREMENT[this->_playerLevel][ELEM_PLAYER])
        return (ELEM_PLAYER);
    if (!this->setObjectForElevation(this->_playerLevel))
        return (-1);
    return (TOTAL_ELEM_ON_TILE);
}

void ZappyAI::storeMessage(std::string str)
{
    _messages.push_back(str);
    std::cout << str << std::endl;
}

void ZappyAI::readMessageBuffer()
{
    while (_messages.size() != 0){
        readMessage(_messages.back());
        _messages.pop_back();
    }
}

void ZappyAI::readMessage(std::string msg)
{
    std::istringstream iss(msg);
    std::string prompt;
    int direction;
    char commas;
    std::string message;

    iss >> prompt >> direction >> commas >> message;
    readSignal(message, direction);
}

void ZappyAI::readSignal(std::string msg, int direction)
{
    std::string uncipheredMsg(msg);
    uncipherStr(uncipheredMsg);
    std::istringstream iss(uncipheredMsg);
    char prompt;
    int sender;
    int recever;
    int status;
    int parameter;

    iss >> prompt >> sender >> recever >> status >> parameter;
    if (prompt != '!' || (recever != -1 && recever != _playerId))
        return;
    if (status == lookingForElevation && _friendID == -1){
        if (parameter == _playerLevel){
            _friendID = sender;
            if (!sendSignal(_friendID, comingForElevation, _playerLevel))
                _friendID = -1;
        }
    }
    else if (status == comingForElevation){
        if (_friendID == -1){
            _friendID = sender;
            _master = true;
        } else if (_friendID != sender)
            sendSignal(sender, alreadySomeone, _playerLevel);
        sendSignal(_friendID, waitingForElevation, _playerLevel);
    }
    else if (status == waitingForElevation){
        if (direction == 0)
            sendSignal(_friendID, readyForElevation, _playerLevel);
        else{
            sendSignal(_friendID, comingForElevation, _playerLevel);
            moveTo(direction);
        }
    } else if (status == alreadySomeone){
        if (sender == _friendID)
            _friendID = -1;
    } else if (status == readyForElevation && sender == _friendID){
        if (_master)
            _playersReady++;
        else
            this->tryElevate();
    } else if (status == needToGo){
        if (direction == 0)
            _playersReady--;
        else {
            _friendID = -1,
            _master = false;
        }
    }
}

bool ZappyAI::sendSignal(int recever, int status, int parameter)
{
    return (broadcast("!" + std::to_string(this->_playerId) + " " + std::to_string(recever) + " " +
    std::to_string(status) + " " + std::to_string(parameter)));
}

void ZappyAI::moveTo(int direction)
{
    int orientation = DIR_NORTH;

    if (direction == 2 || direction == 1 || direction == 8)
        this->forward();
    if (direction >= 2 && direction <= 4){
        orientation = DIR_WEST;
        this->left();
        this->forward();
    } if (direction >= 6 && direction <= 8){
        orientation = DIR_EAST;
        this->right();
        this->forward();
    } if (direction >= 4 && direction <= 6){
        if (orientation == DIR_WEST)
            this->left();
        else if (orientation == DIR_EAST)
            this->right();
        else
            this->turn180();
        this->forward();
    }
}