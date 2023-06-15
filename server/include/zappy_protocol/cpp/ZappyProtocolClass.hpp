/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** ZappyProtocolClass
*/

#pragma once

#include <string>

#include "c_zappy_protocol.h"

class ZappyProtocol {
public:
    ZappyProtocol();
    ZappyProtocol(int fd);
    ~ZappyProtocol();

    /**
     ** @brief This method better be called
     ** before a readData() or
     ** after a writeData().
     ** The method retrieve the data sent on the file descriptor
     ** and send what was written with the writeData() method.
     **
     ** @param read_socket
     ** @param write_socket
     ** @return ssize_t
     */
    ssize_t refresh(void);
    ssize_t receive(void);
    ssize_t send(void);
    void writeData(const std::string &data, size_t size);
    void readData(std::string &data, size_t size);
    bool getLine(std::string &output);
    bool getLineTimeout(std::string &output, int timeout);
    int getFd(void) const;
    void setFd(int fd);

protected:
    t_zp_pending_data _data;
    fd_set _readSocket;
    fd_set _writeSocket;
};
