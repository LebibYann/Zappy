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
    memset(this->_inventory, 0, TOTAL_ELEM_ON_TILE * sizeof(*(this->_inventory)));
    this->_targetPos.x = 0;
    this->_targetPos.y = 0;
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
    if (this->_communication.getlineTimeout(data, 1) != 0)
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
    if (this->_communication.getlineTimeout(data, 1) != 0)
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
    if (this->_communication.getlineTimeout(data, 1) != 0)
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

bool ZappyAI::handlePackageReception(enum e_AIResponse expectedResponse, std::string &str)
{
    int out;

    while (true) {
        out = this->_communication.receivePackage(str);
        switch (out) {
            case RESPONSE_EJECT:
                std::cout << "Eject" << std::endl;
                break;
            case RESPONSE_MESSAGE:
                std::cout << "Message" << std::endl;
                break;
            default:
                if (out != expectedResponse) {
                    if (out == RESPONSE_DISCONNECTION || out == RESPONSE_DEAD)
                        this->_alive = false;
                    return (false);
                }
                return (true);
        }

    }
    return (false);
}

void ZappyAI::setRessourceToHave(void)
{
    memset(this->_ressourceToHave, 0, TOTAL_ELEM_ON_TILE * sizeof(*(this->_ressourceToHave)));

    for (size_t i = this->_playerLevel; i < TOTAL_ELEVATION; ++i) {
        for (size_t k = 0; k < TOTAL_ELEM_ON_TILE; ++k) {
            this->_ressourceToHave[k] += ELEVATION_REQUIREMENT[i][k] * 2;
        }
    }
}

bool ZappyAI::handlePackageReception(enum e_AIResponse expectedResponse)
{
    std::string str;

    return (this->handlePackageReception(expectedResponse, str));
}

void ZappyAI::surviveBehaviour(void)
{
    t_coords relPos;

    while (this->_inventory[ELEM_FOOD] < 10 && this->_alive) {
        if (this->lookFor(ELEM_FOOD, relPos) > 0) {
            this->takeAll(ELEM_FOOD);
            while (!ON_RELATIVE_TILE(relPos) && this->_alive) {
                // std::cout << relPos.x << " " << relPos.y << " " << this->_direction << std::endl;
                this->moveTowardRelativeCoord(relPos);
                this->takeAll(ELEM_FOOD);
            }
        } else {
            this->moveRandom(this->_targetPos);
        }
        this->inventory();
    }
}

void ZappyAI::run(void)
{
    while (this->_alive) {
        this->inventory();
        if (this->_inventory[ELEM_FOOD] < 4)
            this->surviveBehaviour();
        if (this->_inventory[ELEM_FOOD] < 30)
            this->takeAll(ELEM_FOOD);
        this->moveRandom();
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
    if (!this->handlePackageReception(RESPONSE_OTHER, str))
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
        while (itemName.compare("") == 0)
            getline(itemStream, itemName, ' ');
        itemStrQuantity = "";
        while (itemStrQuantity.compare("") == 0)
            getline(itemStream, itemStrQuantity, ' ');
        for (size_t i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
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
    if (!this->handlePackageReception(RESPONSE_OTHER, str))
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
    if (!this->handlePackageReception(RESPONSE_OK))
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
    if (!this->handlePackageReception(RESPONSE_OK))
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
    if (!this->handlePackageReception(RESPONSE_OK))
        return (false);
    this->_direction = (this->_direction + TOTAL_DIRECTION - 1) % TOTAL_DIRECTION;
    this->_lookDone = false;
    return (true);
}

bool ZappyAI::take(enum e_elemOnTile elem)
{
    int elemIndex = -1;

    if (PRINT_ACTION)
        std::cout << "Take: " << elem << std::endl;
    for (int i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
        if (INVENTORY_PAIR[i].item_type == elem) {
            elemIndex = i;
            break;
        }
    }
    if (elemIndex == -1)
        return (false);
    this->_communication.sendPackage(ZP_TAKE_OBJ, INVENTORY_PAIR[elemIndex].item_name);
    if (!this->handlePackageReception(RESPONSE_OK))
        return (false);
    ++(this->_inventory[elem]);
    return (true);
}

bool ZappyAI::set(enum e_elemOnTile elem)
{
    int elemIndex = -1;

    if (PRINT_ACTION)
        std::cout << "Set: " << elem << std::endl;
    for (int i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
        if (INVENTORY_PAIR[i].item_type == elem) {
            elemIndex = i;
            break;
        }
    }
    if (elemIndex == -1 && this->_inventory[elem] <= 0)
        return (false);
    this->_communication.sendPackage(ZP_SET_OBJ, INVENTORY_PAIR[elemIndex].item_name);
    if (!this->handlePackageReception(RESPONSE_OK))
        return (false);
    --(this->_inventory[elem]);
    return (true);
}

bool ZappyAI::broadcast(const std::string &msg, bool cipher)
{
    std::string tmpStr = msg;

    if (cipher)
        this->cipherStr(tmpStr);
    this->_communication.sendPackage(ZP_BROADCAST, tmpStr);
    if (!this->handlePackageReception(RESPONSE_OK))
        return (false);
    return (true);
}

int ZappyAI::connectNbr(void)
{
    std::string str;

    this->_communication.sendPackage(ZP_CONNECT_NBR);
    if (!this->handlePackageReception(RESPONSE_OTHER, str) &&
    !strIsDigit(str))
        return (-1);
    return (atoi(str.c_str()));
}

bool ZappyAI::fork(void)
{
    this->_communication.sendPackage(ZP_FORK);
    return (this->handlePackageReception(RESPONSE_OK));
}

bool ZappyAI::eject(void)
{
    this->_communication.sendPackage(ZP_EJECT);
    return (this->handlePackageReception(RESPONSE_OK));
}

bool ZappyAI::elevation(void)
{
    std::string str;

    this->_communication.sendPackage(ZP_EJECT);
    if (!this->handlePackageReception(RESPONSE_OTHER, str))
        return (false);
    if (str.compare("Elevation underway\n") != 0)
        return (false);
    if (!this->handlePackageReception(RESPONSE_OTHER, str))
        return (false);
    ++(this->_playerLevel);
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
    return (this->forward(relativeCoord));
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
    int out;
    int sentRequest = 0;
    t_coords coords;
    int elemIndex = -1;
    int elemToTake = this->lookFor(elem, coords);
    int elemTaken = 0;


    if (PRINT_ACTION)
        std::cout << "Take all: " << elem << std::endl;
    if (elemToTake <= 0 || !ON_RELATIVE_TILE(coords))
        return (elemTaken);
    for (int i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
        if (INVENTORY_PAIR[i].item_type == elem) {
            elemIndex = i;
            break;
        }
    }
    if (elemIndex == -1)
        return (elemTaken);
    for (int i = 0; i < elemToTake; ++i) {
        if (sentRequest < MAX_ACTION_AT_ONCE) {
            this->_communication.sendPackage(ZP_TAKE_OBJ, INVENTORY_PAIR[elemIndex].item_name);
            ++sentRequest;
        } else {
            out = this->_communication.receivePackage();
            if (out == RESPONSE_DISCONNECTION || out == RESPONSE_DEAD) {
                this->_alive = false;
                return (elemTaken);
            }
            elemTaken += (out == RESPONSE_OK);
            --sentRequest;
        }
    }
    while (sentRequest > 0) {
        out = this->_communication.receivePackage();
        if (out == RESPONSE_DISCONNECTION || out == RESPONSE_DEAD) {
            this->_alive = false;
            return (elemTaken);
        }
        elemTaken += (out == RESPONSE_OK);
        --sentRequest;
    }
    this->_inventory[elem] += elemTaken;
    return (elemTaken);
}

void ZappyAI::takeUsefulResource(const std::vector<int> &itemList)
{
    for (size_t i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
        if (this->_inventory[i] < this->_ressourceToHave[i] && itemList[i] > 0)
            takeAll(static_cast<enum e_elemOnTile>(i));
    }
    this->look();
}

int ZappyAI::tryElevate(void)
{
    for (size_t i = 0; i < TOTAL_ELEM_ON_TILE; ++i) {
        if (this->_inventory[i] < ELEVATION_REQUIREMENT[this->_playerLevel][i])
            return (i);
    }
    if (this->_inventory[ELEM_FOOD] < 5)
        return (ELEM_FOOD);
    this->elevation();
    return (TOTAL_ELEM_ON_TILE);
}
