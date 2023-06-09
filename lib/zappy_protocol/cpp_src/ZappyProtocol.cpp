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

ssize_t ZappyProtocol::refresh(fd_set read_socket, fd_set write_socket)
{
    return (zp_exchange_data(&(this->_data), read_socket, write_socket));
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

int ZappyProtocol::getFd(void) const
{
    return (this->_data.fd);
}
