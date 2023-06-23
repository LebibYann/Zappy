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

    /**
     ** @brief You should call the method refresh() or receive() before this one.
     ** Fills output parameter if a line can be recovered.
     **
     ** @param output
     ** @return true if there's a line to get or false if there's no line to get.
     */
    bool zpGetline(std::string &output);
    /**
     ** @brief Fills output parameter if a line can be recovered.
     ** The main difference with the getline() method is that
     ** it also do the reception part so there's no mandatory need to call
     ** receive() or refresh() method.
     **
     **
     ** @param output
     ** @return int 0 on success, 1 if there's nothing to get,
     ** -1 if there's a disconnection
     */
    int getlineWait(std::string &output);
    int getFd(void) const;
    void setFd(int fd);

protected:
    t_zp_pending_data _data;
};
