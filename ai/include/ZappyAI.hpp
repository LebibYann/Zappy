/*
** EPITECH PROJECT, 2023
** ai
** File description:
** ZappyAI
*/

#pragma once

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <iostream>
#include <cstring>

#include <stdint.h>
#include <unistd.h>

#include "ZappyProtocol.hpp"
#include "ZappyAIParam.hpp"




typedef enum e_initStatus {
    INIT_OK,
    INIT_KO,
    INIT_HELP,
    TOTAL_INIT
} t_initStatus;

class ZappyAI {
    public:
        ZappyAI();
        ~ZappyAI();

        int init(const std::vector<std::string> &argvList);
        void setName(const std::string &name);
        std::string getName(void) const;
        void setPort(uint32_t port);
        uint32_t getPort(void) const;
        void setMachine(const std::string &machine);
        std::string getMachine(void) const;

        bool connectToServer(void);
        void generateCipherList(void);

        void run();

    private:
        bool charExist(char charToCheck);

        std::string _name;
        std::string _machine;
        uint32_t _port;

        int _playerId = -1;
        int _posX = 0;
        int _posY = 0;
        int _rot = 0;
        std::vector<std::vector<int[TOTAL_ELEM_ON_TILE]>> _map;
        char _cipherList[127];

};
