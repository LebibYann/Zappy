/*
** EPITECH PROJECT, 2023
** ZappyProtocol
** File description:
** ZappyProtocol
*/

#include "ZappyProtocolClass.hpp"

ZappyProtocol::ZappyProtocol(int fd)
{
    zp_init_pending_data_struct(&(this->_data), fd);
}

ZappyProtocol::ZappyProtocol()
{
    zp_init_pending_data_struct(&(this->_data), -1);
}

ZappyProtocol::~ZappyProtocol()
{
    zp_clear_pending_data_struct(&(this->_data));
}

ssize_t ZappyProtocol::refresh(fd_set read_socket, fd_set write_socket)
{
    return (zp_exchange_data(&(this->_data), read_socket, write_socket));
}

void ZappyProtocol::readData(std::string &data, size_t size)
{
    char *tmpData = new char(size);

    zp_read_data(&(this->_data), tmpData, size);
    data = tmpData;
    delete tmpData;
}

void ZappyProtocol::writeData(const std::string &data, size_t size)
{
    zp_write_data(&(this->_data), data.c_str(), size);
}

bool ZappyProtocol::getLine(std::string &output)
{
    char *str = zp_getline_pending_data(&(this->_data));

    if (str == nullptr)
        return (false);
    output = str;
    free(str);
    return (true);
}

int ZappyProtocol::getFd(void) const
{
    return (this->_data.fd);
}

void ZappyProtocol::setFd(int fd)
{
    zp_clear_pending_data_struct(&(this->_data));
    zp_init_pending_data_struct(&(this->_data), fd);
}
