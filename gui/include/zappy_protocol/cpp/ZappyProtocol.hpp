/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** ZappyProtocol
*/

#pragma once

#include <string>

#include "c_zappy_protocol_gui.h"

class ZappyProtocol {
public:
    ZappyProtocol(int fd);
    ~ZappyProtocol();

    void writeData(void *data, size_t size);
    void readData(void *data, size_t size);
    std::string getLine();
private:
    t_zp_pending_data *_data;
};