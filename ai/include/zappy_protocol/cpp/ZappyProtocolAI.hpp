/*
** EPITECH PROJECT, 2023
** ZappyProtocolAI
** File description:
** ZappyProtocolAI
*/

#pragma once

#include "ZappyProtocolClass.hpp"

typedef struct aiCommand_s
{
    enum e_zp_command id;
    std::string name;
} aiCommand_t;

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
         ** @brief You should call refresh() method before using this method.
         ** Parse the data of the received command if there's one.
         **
         ** @param pkg
         ** @return int
         ** @return int 0 on success, -1 if no data has been received,
         ** -2 if the command receive is unknown, -3 if parameters are invalid.
         */
        int receivePackage();

    private:
        t_zp_ai_to_serv_data _pkg;
};
