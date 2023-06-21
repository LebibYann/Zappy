/*
** EPITECH PROJECT, 2023
** ZappyProtocolAI
** File description:
** ZappyProtocolAI
*/

#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "ZappyProtocolClass.hpp"

typedef struct aiCommand_s {
    enum e_zp_command id;
    std::string name;
} aiCommand_t;

typedef enum e_AIResponse {
    RESPONSE_DISCONNECTION = -2,
    RESPONSE_NOTHING,
    RESPONSE_OK,
    RESPONSE_KO,
    RESPONSE_DEAD,
    RESPONSE_MESSAGE,
    RESPONSE_EJECT,
    RESPONSE_OTHER,
    RESPONSE_TOTAL
} t_AIResponse;

class ZappyProtocolAI : public ZappyProtocol {
    public:
        ZappyProtocolAI();
        ZappyProtocolAI(int fd);
        ~ZappyProtocolAI();

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
        bool sendPackage(enum e_zp_command cmd_type);

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
        bool sendPackage(enum e_zp_command cmd_type, const std::string &str);

        /**
         ** @brief You should call refresh() method before using this method.
         ** Parse the data of the received command if there's one.
         **
         ** @param pkg
         ** @return int
         ** @return int 0 on success, -1 if no data has been received,
         ** -2 if the command receive is unknown, -3 if parameters are invalid.
         */
        int receivePackage(std::string &str);
        int receivePackage(void);

    private:
        t_zp_ai_to_serv_data _pkg;
};
