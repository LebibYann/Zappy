/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** AnalysePackages
*/

#include "GameScene.hpp"
#include <sstream>

void getTileContent(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    std::vector<int> tile;

    for (int i = 0; i < 9; ++i)
        tile.push_back(package.args[i]);
    gameInfo.map.push_back(tile);
}

void getMapContent(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (int i = 0; i < 9; ++i)
        gameInfo.mapContent.push_back(package.args[i]);
}

void getTeamName(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    std::istringstream stream(package.str);
    std::string name;

    while (std::getline(stream, name, '\n'))
        gameInfo.teamNames.push_back(name);
    gameInfo.nbrTeams = gameInfo.teamNames.size();
}

void getPlayerInfo(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    t_playerStruct player;
    bool exist = false;

    player.id = package.args[0];
    player.x = package.args[1];
    player.y = package.args[2];
    player.orientation = package.args[3];
    player.level = package.args[4];
    player.teamName = package.str;
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
         if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i] = player;
            exist = true;
         }
    }
    if (!exist)
        gameInfo.players.push_back(player);
}

void changePlayerPos(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i].x = package.args[1];
            gameInfo.players[i].y = package.args[2];
            gameInfo.players[i].orientation = package.args[3];
        }
    }
}

void changePlayerLvl(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0])
            gameInfo.players[i].level = package.args[1];
    }
}

void playIncantationAnimation(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0])
            gameInfo.players[i].isIncanting = true;
    }
}

void endIncantationAnimation(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0])
            gameInfo.players[i].isIncanting = false;
    }
}

void eggLaying(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0])
            gameInfo.players[i].eggLaying = true;
    }
}

void playerStopEggLaying(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    t_eggStruct egg;

    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[1]) {
            gameInfo.players[i].eggLaying = false;
            egg.id = package.args[0];
            egg.x = package.args[2];
            egg.y = package.args[3];
            egg.isDead = false;
            egg.isHatching = false;
            gameInfo.eggs.push_back(egg);
        }
    }
}

void eggConnection(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        if (gameInfo.eggs[i].id == package.args[0]) {
            gameInfo.eggs[i].isHatching = true;
        }
    }
}

void eggDeath(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        if (gameInfo.eggs[i].id == package.args[0]) {
            gameInfo.eggs[i].isDead = true;
        }
    }
}

void playSoundDrop(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    (void) gameInfo;
    (void) package;
}

void playSoundCollect(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    (void) gameInfo;
    (void) package;
}

void playerDeath(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0])
            gameInfo.players[i].isDead = true;
    }
}

void endGame(t_gameInfo &gameInfo)
{
    gameInfo.gameOver = true;
}

t_gameInfo analysePackages(std::vector<t_zp_guiProtocol> packages)
{
    t_gameInfo gameInfo;

    for (size_t i = 0; i < packages.size(); ++i) {
        if (packages[i].cmdType == ZP_MSZ) {
            gameInfo.mapSize.push_back(packages[i].args[0]);
            gameInfo.mapSize.push_back(packages[i].args[1]);
        } else if (packages[i].cmdType == ZP_BCT)
            getTileContent(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_MCT)
            getMapContent(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_TNA)
            getTeamName(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PNW)
            getPlayerInfo(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PPO)
            changePlayerPos(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PLV)
            changePlayerLvl(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PBC)
            std::cout << "Broadcast: " << packages[i].str << std::endl;
        else if (packages[i].cmdType == ZP_PIC)
            playIncantationAnimation(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PIE)
            endIncantationAnimation(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PFK)
            eggLaying(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PDR)
            playSoundDrop(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PGT)
            playSoundCollect(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_PDI)
            playerDeath(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_ENW)
            playerStopEggLaying(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_EBO)
            eggConnection(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_EDI)
            eggDeath(gameInfo, packages[i]);
        else if (packages[i].cmdType == ZP_SEG)
            endGame(gameInfo);
        else if (packages[i].cmdType == ZP_SMG)
            std::cout << "Server message: " << packages[i].str << std::endl;
    }
    return (gameInfo);
}