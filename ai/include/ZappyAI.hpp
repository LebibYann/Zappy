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

#define PRINT_ACTION true
#define SERVER_EXPECTED_PACKAGE "WELCOME\n"
#define ON_RELATIVE_TILE(coord) ((coord).x == 0 && (coord).y == 0)
#define MAX_ACTION_AT_ONCE 10

typedef enum e_initStatus {
    INIT_OK,
    INIT_KO,
    INIT_HELP,
    TOTAL_INIT
} t_initStatus;

typedef enum e_playerDirection {
    DIR_UNDEF = -1,
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

        void surviveBehaviour(void);
        void run(void);

        bool inventory(void);
        bool look(void);
        bool forward(void);
        bool forward(t_coords &relativeCoord);
        bool right(void);
        bool left(void);
        bool take(enum e_elemOnTile elem);
        bool set(enum e_elemOnTile elem);
        bool broadcast(const std::string &msg, bool cipher = true);
        int connectNbr(void);
        bool fork(void);
        bool eject(void);
        bool elevation(void);

        void turn180(void);
        void turnTo(enum e_playerDirection direction);

        bool moveTowardRelativeCoord(t_coords &relativeCoord);
        void moveRandom(void);
        void moveRandom(t_coords &relativeCoord);

        void lookItemList(std::vector<int> &itemList);
        int lookFor(enum e_elemOnTile seekedElem, t_coords &relativeCoord);

        int takeAll(enum e_elemOnTile elem);

        int tryElevate(void);

    private:
        bool charExist(char charToCheck);

        std::string _name;
        std::string _machine = "127.0.0.1";
        uint32_t _port;
        fd_set _read_socket;
        fd_set _write_socket;
        Client _connection;
        ZappyProtocolAI _communication;

        bool _alive = true;
        int _playerId = 0;
        int _playerLevel = 1;
        int _direction = 0;
        int _inventory[TOTAL_ELEM_ON_TILE];

        // Look data
        bool _lookDone = false;
        std::vector<std::vector<int>> _lookResult;

        t_coords _targetPos = {0, 0, 0};

        char _cipherList[127];
        // std::vector<std::vector<std::vector<int>>> _map;

};
