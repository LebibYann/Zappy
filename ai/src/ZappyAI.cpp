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

bool ZappyAI::timedGetline(std::string &str, unsigned int timeout)
{
    this->_communication.refresh();
    if(!this->_communication.getLine(str)) {
        sleep(timeout);
        this->_communication.refresh();
        if(!this->_communication.getLine(str))
            return (false);
    }
    return (true);
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
    if (!this->_communication.getLineTimeout(data, 1))
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
    if (!this->_communication.getLineTimeout(data, 1))
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
    if (!this->_communication.getLineTimeout(data, 1))
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

    memset(this->_cipherList, 0, 127);
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
