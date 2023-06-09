/*
** EPITECH PROJECT, 2023
** ZappyProtocol
** File description:
** ZappyProtocol
*/

#include "ZappyProtocol.hpp"

ZappyProtocol::ZappyProtocol(int fd)
{
    zp_init_pending_data_struct(&(this->_data), fd);
}

ZappyProtocol::~ZappyProtocol()
{
    zp_clear_pending_data_struct(&(this->_data));
}

void ZappyProtocol::readData(void *data, size_t size)
{
    zp_read_data(&(this->_data), data, size);
}

void ZappyProtocol::writeData(void *data, size_t size)
{
    zp_write_data(&(this->_data), data, size);
}

std::string ZappyProtocol::getLine()
{
    return (std::string(zp_getline_pending_data(&(this->_data))));
}
