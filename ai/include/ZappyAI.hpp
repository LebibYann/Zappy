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
#include <sstream>

#include <stdint.h>
#include <unistd.h>

#include "CheckFunction.hpp"
#include "ZappyProtocol.hpp"
#include "ZappyAIParam.hpp"

#define SERVER_EXPECTED_PACKAGE "WELCOME\n"

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
        void addFdInFdset(int fd);
        void removeFdInFdset(int fd);

        bool timedGetline(std::string &str, unsigned int timeout = 1);
        void displayParameters(void);
        bool connectToServer(void);
        bool checkServerPackage(void);
        bool joinTeam(void);
        bool initMap(void);
        void generateCipherList(void);

        void run(void);
        void updateInventory(void);

    private:
        bool charExist(char charToCheck);

        bool _alive = true;
        ZappyProtocolAI _communication;

        std::string _name;
        std::string _machine = "localhost";
        uint32_t _port;
        Client _connection;
        fd_set _read_socket;
        fd_set _write_socket;

        int _playerId = -1;
        int _posX = 0;
        int _posY = 0;
        int _direction = 0;
        int _inventory[TOTAL_ELEM_ON_TILE];
        std::vector<std::vector<std::vector<int>>> _map;
        char _cipherList[127];

};
