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
    this->_map.resize(mapY);
    for (int i = 0; i < mapY; ++i) {
        this->_map[i].resize(mapX);
        for (int k = 0; k < mapX; ++k)
            this->_map[i].resize(TOTAL_ELEM_ON_TILE);
    }
    std::cout << "[OK]" << std::endl;
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

bool ZappyAI::handlePackageReception(enum e_AIResponse expectedResponse)
{
    std::string str;

    return (this->handlePackageReception(expectedResponse, str));
}

void ZappyAI::run(void)
{
    // t_coords relPos;

    while (this->_alive) {
        this->inventory();
        this->look();
        this->forward();
        this->take(ELEM_FOOD);
        this->set(ELEM_FOOD);
        this->broadcast("prout", false);
        if (this->_inventory[ELEM_FOOD] < 5) {

        }
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

int ZappyAI::lookFor(enum e_elemOnTile seekedElem, t_coords &relativeCoords)
{
    int elemCount = 0;
    int tmp;
    int width;

    if ((!this->_lookDone && !this->look()) ||
    this->_lookResult.size() <= 0)
        return (0);
    if (this->_lookResult[0][seekedElem] > 0)
        return (this->_lookResult[0][seekedElem]);
    relativeCoords.y = 1;
    width = 3;
    relativeCoords.x = -width / 2;
    for (size_t i = 1; i < this->_lookResult.size(); ++i) {
        if (relativeCoords.x >= width / 2) {
            width += 2;
            relativeCoords.x = -width / 2;
            ++(relativeCoords.y);
        }
        if (this->_lookResult[i][seekedElem] > 0) {
            relativeCoords.l = i;
            elemCount = this->_lookResult[i][seekedElem];
            break;
        }
        ++(relativeCoords.x);
    }
    for (int i = 0; i < this->_direction; ++i) {
        tmp = relativeCoords.y;
        relativeCoords.y = -relativeCoords.x;
        relativeCoords.x = tmp;
    }
    return (elemCount);
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
    std::cout << str << std::endl;
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
    this->_communication.sendPackage(ZP_FORWARD);
    if (!this->handlePackageReception(RESPONSE_OK))
        return (false);
    switch (this->_direction) {
        case DIR_NORTH:
            --(this->_targetPos.y);
            break;
        case DIR_SOUTH:
            ++(this->_targetPos.y);
            break;
        case DIR_EAST:
            --(this->_targetPos.x);
            break;
        case DIR_WEST:
            ++(this->_targetPos.x);
            break;
    }
    this->_lookDone = false;
    return (true);
}

bool ZappyAI::right(void)
{
    this->_communication.sendPackage(ZP_LEFT);
    if (!this->handlePackageReception(RESPONSE_OK))
        return (false);
    this->_direction = (this->_direction + 1) % TOTAL_DIRECTION;
    this->_lookDone = false;
    return (true);
}

bool ZappyAI::left(void)
{
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
