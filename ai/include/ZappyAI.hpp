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

typedef enum e_playerDirection {
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST,
    TOTAL_DIRECTION
} t_playerDirection;

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

        void displayParameters(void);
        bool connectToServer(void);
        bool checkServerPackage(void);
        bool joinTeam(void);
        bool initMap(void);
        void generateCipherList(void);
        void cipherStr(std::string &str);
        void uncipherStr(std::string &str);
        bool handlePackageReception(enum e_AIResponse expectedResponse);
        bool handlePackageReception(enum e_AIResponse expectedResponse, std::string &str);

        void run(void);
        bool inventory(void);
        int lookFor(enum e_elemOnTile seekedElem, t_coords &relativeCoords);
        bool look(void);
        bool forward(void);
        bool right(void);
        bool left(void);
        bool take(enum e_elemOnTile elem);
        bool set(enum e_elemOnTile elem);
        bool broadcast(const std::string &msg, bool cipher);
        int connectNbr(void);

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
        std::vector<std::vector<int>> _lookResult;
        bool _lookDone = false;
        t_coords _targetPos;
        int _posX = 0;
        int _posY = 0;
        int _direction = 0;
        int _inventory[TOTAL_ELEM_ON_TILE];
        std::vector<std::vector<std::vector<int>>> _map;
        char _cipherList[127];

};
