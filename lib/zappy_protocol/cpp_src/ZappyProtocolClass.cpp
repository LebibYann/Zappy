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

ssize_t ZappyProtocol::refresh(void)
{
    return (zp_exchange_data(&(this->_data), HANDLE_NO_WAIT, HANDLE_NO_WAIT));
}

ssize_t ZappyProtocol::receive(void)
{
    return (zp_exchange_data(&(this->_data), HANDLE_NO_WAIT, HANDLE_IGNORE));
}

ssize_t ZappyProtocol::send(void)
{
    return (zp_exchange_data(&(this->_data), HANDLE_IGNORE, HANDLE_NO_WAIT));
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

int ZappyProtocol::zpGetline(std::string &output)
{
    char *str = zp_getline_pending_data(&(this->_data));

    if (this->_data.disconnected) {
        if (str != nullptr)
            free(str);
        return (-1);
    }
    if (str == nullptr)
        return (1);
    output = str;
    free(str);
    return (0);
}

int ZappyProtocol::getlineWait(std::string &output)
{
    char *str = zp_getline_wait_pending_data(&(this->_data));

    if (this->_data.disconnected) {
        if (str != nullptr)
            free(str);
        return (-1);
    }
    if (str == nullptr)
        return (1);
    std::cout << "AI RECEIVED COMMAND: " << str << std::endl;
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
    zp_clear_pending_data_struct(&(this->_data));
    zp_init_pending_data_struct(&(this->_data), fd);
}
