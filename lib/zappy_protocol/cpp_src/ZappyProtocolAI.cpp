/*
** EPITECH PROJECT, 2023
** ZappyProtocolAI
** File description:
** ZappyProtocolAI
*/

#include "ZappyProtocolAI.hpp"

const aiCommand_t COMMANDS[13] =
{
    {ZP_FORWARD, "Forward"},
    {ZP_RIGHT, "Right"},
    {ZP_LEFT, "Left"},
    {ZP_LOOK, "Look"},
    {ZP_INVENTORY, "Inventory"},
    {ZP_BROADCAST, "Broadcast"},
    {ZP_CONNECT_NBR, "Connect_nbr"},
    {ZP_FORK, "Fork"},
    {ZP_EJECT, "Eject"},
    {ZP_DEAD, ""},
    {ZP_TAKE_OBJ, "Take"},
    {ZP_SET_OBJ, "Set"},
    {ZP_INCANTATION, "Incantation"}
};

ZappyProtocolAI::ZappyProtocolAI() : ZappyProtocol()
{
    _pkg.cmd_type = ZP_END;
    _pkg.str = NULL;
}

ZappyProtocolAI::ZappyProtocolAI(int fd) : ZappyProtocol(fd)
{
    _pkg.cmd_type = ZP_END;
    _pkg.str = NULL;
}

ZappyProtocolAI::~ZappyProtocolAI()
{
}

bool ZappyProtocolAI::sendPackage(enum e_zp_command cmd_type)
{
    for (size_t i = 0; i < 13; ++i){
        if (COMMANDS[i].id == cmd_type){
            writeData(COMMANDS[i].name.c_str(), COMMANDS[i].name.size());
            writeData("\n", 1);
            _pkg.cmd_type = cmd_type;
            this->send();
            return (true);
        }
    }
    return (false);
}

bool ZappyProtocolAI::sendPackage(enum e_zp_command cmd_type, const std::string &str)
{
    for (size_t i = 0; i < 13; ++i){
        if (COMMANDS[i].id == cmd_type) {
            this->writeData(COMMANDS[i].name, COMMANDS[i].name.size());
            this->writeData(" ", 1);
            this->writeData(str, str.size());
            this->writeData("\n", 1);
            _pkg.cmd_type = cmd_type;
            std::cout << "hey" << std::endl;
            this->send();
            std::cout << "hey" << std::endl;
            return (true);
        }
    }
    return (false);
}

int ZappyProtocolAI::receivePackage(std::string &str)
{
    int out = this->getlineTimeout(str);
    switch (out) {
        case -1:
            return (RESPONSE_DISCONNECTION);
        case 1:
            return (RESPONSE_NOTHING);
    }
    if (str.compare("ok\n") == 0)
        return (RESPONSE_OK);
    if (str.compare("ko\n") == 0)
        return (RESPONSE_KO);
    if (str.compare("dead\n") == 0)
        return (RESPONSE_DEAD);
    return (RESPONSE_OTHER);
}
