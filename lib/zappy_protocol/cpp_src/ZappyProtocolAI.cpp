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
    {ZP_BROADCAST, "Broadcast text"},
    {ZP_CONNECT_NBR, "Connect_nbr"},
    {ZP_FORK, "Fork"},
    {ZP_EJECT, "Eject"},
    {ZP_DEAD, ""},
    {ZP_TAKE_OBJ, "Take object"},
    {ZP_SET_OBJ, "Set object"},
    {ZP_INCANTATION, "Incantation"}
};

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
            writeData(const_cast<char *>(COMMANDS[i].name.c_str()), COMMANDS[i].name.size());
            _pkg.cmd_type = cmd_type;
            return (true);
        }
    }
    return (false);
}

int ZappyProtocolAI::receivePackage()
{
    if (_pkg.cmd_type == ZP_END)
        return (-1);
    _pkg.str = const_cast<char *>(this->getLine().c_str());
    return (0);
}