/*
** EPITECH PROJECT, 2023
** ZappyProtocol
** File description:
** ZappyProtocol
*/

#include "ZappyProtocolClass.hpp"

ZappyProtocol::ZappyProtocol(int fd)
{
    FD_ZERO(&(this->_readSocket));
    FD_ZERO(&(this->_writeSocket));
    zp_init_pending_data_struct(&(this->_data), fd);
}

ZappyProtocol::ZappyProtocol()
{
    FD_ZERO(&(this->_readSocket));
    FD_ZERO(&(this->_writeSocket));
    zp_init_pending_data_struct(&(this->_data), -1);
}

ZappyProtocol::~ZappyProtocol()
{
    zp_clear_pending_data_struct(&(this->_data));
    FD_CLR(this->_data.fd, &(this->_readSocket));
    FD_CLR(this->_data.fd, &(this->_writeSocket));
}

ssize_t ZappyProtocol::refresh(void)
{
    return (zp_exchange_data(&(this->_data), &(this->_readSocket), &(this->_writeSocket)));
}

ssize_t ZappyProtocol::receive(void)
{
    return (zp_exchange_data(&(this->_data), &(this->_readSocket), NULL));
}

ssize_t ZappyProtocol::send(void)
{
    return (zp_exchange_data(&(this->_data), NULL, &(this->_writeSocket)));
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

bool ZappyProtocol::getline(std::string &output)
{
    char *str = zp_getline_pending_data(&(this->_data));

    if (str == nullptr)
        return (false);
    output = str;
    free(str);
    return (true);
}

int ZappyProtocol::getlineTimeout(std::string &output, int timeout)
{
    char *str = zp_getline_timeout_pending_data(&(this->_data), timeout, this->_readSocket);

    if (this->_data.disconnected)
        return (-1);
    if (str == nullptr)
        return (1);
    output = str;
    free(str);
    return (0);
}

int ZappyProtocol::getFd(void) const
{
    return (this->_data.fd);
}

void ZappyProtocol::setFd(int fd)
{
    if (this->_data.fd >= 0) {
        FD_CLR(this->_data.fd, &(this->_readSocket));
        FD_CLR(this->_data.fd, &(this->_writeSocket));
    }
    zp_clear_pending_data_struct(&(this->_data));
    zp_init_pending_data_struct(&(this->_data), fd);
    FD_SET(fd, &(this->_readSocket));
    FD_SET(fd, &(this->_writeSocket));
}
