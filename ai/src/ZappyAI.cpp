/*
** EPITECH PROJECT, 2023
** ai
** File description:
** ZappyAI
*/

#include "ZappyAI.hpp"

ZappyAI::ZappyAI()
{
}

ZappyAI::~ZappyAI()
{
}

int ZappyAI::init(const std::vector<std::string> &argvList)
{
    for (size_t i = 0; i < argvList.size(); ++i) {
        std::cout << argvList[i] << std::endl;
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

bool ZappyAI::connectToServer(void)
{
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
