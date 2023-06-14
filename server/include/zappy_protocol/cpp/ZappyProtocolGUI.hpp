/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** ZappyProtocolGUI
*/

#pragma once

#include <string>
#include <vector>

#include "c_zappy_protocol_gui.h"
#include "ZappyProtocol.hpp"

typedef struct s_zp_guiProtocol {
    enum e_zp_command cmdType;
    std::vector<int> args;
    bool noString;
    std::string str;
} t_zp_guiProtocol;


class ZappyProtocolGUI: public ZappyProtocol {
public:
    ZappyProtocolGUI(int fd);
    ~ZappyProtocolGUI();

    /**
     ** @brief You should call refresh() methos after using this method.
     ** Transform the cmd_type and ... (command arguments)
     ** into a correctly formed command ready to be sent.
     ** (use refresh() method to send it)
     **
     ** @param cmd_type
     ** @param ...
     ** @return true
     ** @return false
     */
    bool sendPackage(enum e_zp_command cmd_type, ...);
    /**
     ** @brief You should call refresh() method before using this method.
     ** Parse the data of the received command if there's one.
     **
     ** @param pkg
     ** @return int
     ** @return int 0 on success, -1 if no data has been received,
     ** -2 if the command receive is unknown, -3 if parameters are invalid.
     */
    int receivePackage(t_zp_guiProtocol &pkg);
protected:
private:
};
