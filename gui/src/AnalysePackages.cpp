/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** AnalysePackages
*/

#include "GameScene.hpp"
#include <sstream>

#define MAX_EVOLVE 3 - 1

void getTileContent(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    gameInfo.map[package.args[0]][package.args[1]] =
    {package.args[2], package.args[3], package.args[4], package.args[5], package.args[6],
    package.args[7], package.args[8]};
}

void getTeamName(t_gameInfo &gameInfo, t_zp_guiProtocol package)
{
    std::istringstream stream(package.str);
    std::string name;

    while (std::getline(stream, name, '\n'))
        gameInfo.teamNames.push_back(name);
    gameInfo.nbrTeams = gameInfo.teamNames.size();
}

void getPlayerInfo(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank)
{
    t_playerStruct player;
    bool exist = false;

    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
         if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i] = player;
            exist = true;
         }
    }
    if (!exist) {
        player.id = package.args[0];
        player.x = package.args[1];
        player.y = package.args[2];
        player.orientation = package.args[3];
        player.teamName = package.str;
        player.level = package.args[4];
        player.eggLaying = false;
        player.isIncanting = false;
        player.isDead = false;
        player.sprite = imageBank.getIdleSprite(player.level - 1);
        gameInfo.players.push_back(player);
    }
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

void changePlayerLvl(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &_imageBank)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i].level = package.args[1];
            int level = (gameInfo.players[i].level - 1) > MAX_EVOLVE ? MAX_EVOLVE : gameInfo.players[i].level - 1;
            gameInfo.players[i].sprite = _imageBank.getIdleSprite(level);
        }
    }
}

void playIncantationAnimation(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank, AudioBank &audioBank)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i].isIncanting = true;
            int level = (gameInfo.players[i].level - 1) > MAX_EVOLVE ? MAX_EVOLVE : gameInfo.players[i].level - 1;
            gameInfo.players[i].sprite = imageBank.getIncantSprite(level);
            audioBank.playSound(INCANT);
        }
    }
}

void endIncantationAnimation(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank, AudioBank &audioBank)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i].isIncanting = false;
            int level = (gameInfo.players[i].level - 1) > MAX_EVOLVE ? MAX_EVOLVE : gameInfo.players[i].level - 1;
            gameInfo.players[i].sprite = imageBank.getIdleSprite(level);
            audioBank.playSound(LVLUP);
        }
    }
}

void eggLaying(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i].eggLaying = true;
            int level = (gameInfo.players[i].level - 1) > MAX_EVOLVE ? MAX_EVOLVE : gameInfo.players[i].level - 1;
            gameInfo.players[i].sprite = imageBank.getLayingSprite(level);
        }
    }
}

void playerStopEggLaying(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank)
{
    t_eggStruct egg;

    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[1]) {
            gameInfo.players[i].eggLaying = false;
            int level = (gameInfo.players[i].level - 1) > MAX_EVOLVE ? MAX_EVOLVE : gameInfo.players[i].level - 1;
            gameInfo.players[i].sprite = imageBank.getIdleSprite(level);
            egg.id = package.args[0];
            egg.x = package.args[2];
            egg.y = package.args[3];
            egg.isDead = false;
            egg.isHatching = false;
            egg.sprite = imageBank.getEggSprite(0);
            gameInfo.eggs.push_back(egg);
        }
    }
}

void eggConnection(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank)
{
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        if (gameInfo.eggs[i].id == package.args[0]) {
            gameInfo.eggs[i].isHatching = true;
            gameInfo.eggs[i].sprite = imageBank.getEggSprite(1);
        }
    }
}

void eggDeath(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank)
{
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        if (gameInfo.eggs[i].id == package.args[0]) {
            gameInfo.eggs[i].isDead = true;
            gameInfo.eggs[i].sprite = imageBank.getEggSprite(2);
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

void playerDeath(t_gameInfo &gameInfo, t_zp_guiProtocol package, ImageBank &imageBank, AudioBank &audioBank)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        if (gameInfo.players[i].id == package.args[0]) {
            gameInfo.players[i].isDead = true;
            int level = (gameInfo.players[i].level - 1) > MAX_EVOLVE ? MAX_EVOLVE : gameInfo.players[i].level - 1;
            gameInfo.players[i].sprite = imageBank.getDeadSprite(level);
            audioBank.playSound(DEATH);
            gameInfo.players[i].id = -1;
        }
    }
}

void endGame(t_gameInfo &gameInfo)
{
    gameInfo.gameOver = true;
}

void GameScene::refreshPackages(std::vector<t_zp_guiProtocol> packages)
{

    for (size_t i = 0; i < packages.size(); ++i) {
        switch (packages[i].cmdType) {
            case ZP_MSZ:
                _gameInfo.mapSize[0] = packages[i].args[0];
                _gameInfo.mapSize[1] = packages[i].args[1];
                break;
            case ZP_BCT:
                getTileContent(_gameInfo, packages[i]);
                break;
            case ZP_TNA:
                getTeamName(_gameInfo, packages[i]);
                break;
            case ZP_PNW:
                getPlayerInfo(_gameInfo, packages[i], _imageBank);
                break;
            case ZP_PPO:
                changePlayerPos(_gameInfo, packages[i]);
                break;
            case ZP_PLV:
                changePlayerLvl(_gameInfo, packages[i], _imageBank);
                break;
            case ZP_PBC:
                std::cout << "Broadcast: " << packages[i].str << std::endl;
                break;
            case ZP_PIC:
                playIncantationAnimation(_gameInfo, packages[i], _imageBank, _audioBank);
                break;
            case ZP_PIE:
                endIncantationAnimation(_gameInfo, packages[i], _imageBank, _audioBank);
                break;
            case ZP_PFK:
                eggLaying(_gameInfo, packages[i], _imageBank);
                break;
            case ZP_PDR:
                playSoundDrop(_gameInfo, packages[i]);
                break;
            case ZP_PGT:
                playSoundCollect(_gameInfo, packages[i]);
                break;
            case ZP_PDI:
                playerDeath(_gameInfo, packages[i], _imageBank, _audioBank);
                break;
            case ZP_ENW:
                playerStopEggLaying(_gameInfo, packages[i], _imageBank);
                break;
            case ZP_EBO:
                eggConnection(_gameInfo, packages[i], _imageBank);
                break;
            case ZP_EDI:
                eggDeath(_gameInfo, packages[i], _imageBank);
                break;
            case ZP_SEG:
                endGame(_gameInfo);
                break;
            case ZP_SMG:
                std::cout << "Server message: " << packages[i].str << std::endl;
                break;
            default:
                break;
        }
    }
}