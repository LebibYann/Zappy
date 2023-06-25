/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** DrawMapElems
*/

#include <random>

#include "GameScene.hpp"
#include "ZappyProtocolGUI.hpp"

void drawGround(sf::RenderWindow &window, t_gameInfo &gameInfo, ImageBank &imageBank)
{
    for (int i = 0; i < gameInfo.mapSize[0]; ++i) {
        for (int j = 0; j < gameInfo.mapSize[1]; ++j) {
            sf::Sprite sprite = imageBank.getGroundSprite(0);
            sprite.setPosition(i * gameInfo.tileSizeX, j * gameInfo.tileSizeY);
            window.draw(sprite);
        }
    }
}

void drawRss(sf::RenderWindow &window, t_gameInfo &gameInfo, ImageBank &imageBank)
{
    srand(time(nullptr));

    for (size_t i = 0; i < gameInfo.map.size(); ++i) {
        for (size_t j = 0; j < gameInfo.map[i].size(); ++j) {
            for (size_t k = 0; k < TOTAL_INVENTORY; k++){
                if (gameInfo.map[i][j][k] > 0) {
                    sf::Sprite sprite = imageBank.getRssSprite(k);
                    sprite.setPosition(i * gameInfo.tileSizeX, j * gameInfo.tileSizeY);
                    window.draw(sprite);
                }
            }
        }
    }
}

void drawEggs(sf::RenderWindow &window, t_gameInfo &gameInfo)
{
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        gameInfo.eggs[i].sprite.setPosition(gameInfo.eggs[i].x * gameInfo.tileSizeX, gameInfo.eggs[i].y * gameInfo.tileSizeY);
        window.draw(gameInfo.eggs[i].sprite);
    }
}

void drawPlayers(sf::RenderWindow &window, t_gameInfo &gameInfo)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        gameInfo.players[i].sprite.setPosition(gameInfo.players[i].x * gameInfo.tileSizeX, gameInfo.players[i].y * gameInfo.tileSizeY);
        window.draw(gameInfo.players[i].sprite);
    }
}

void drawElements(sf::RenderWindow &window, t_gameInfo &gameInfo, ImageBank &imageBank)
{
    if (gameInfo.gameOver == true)
        return;
    drawGround(window, gameInfo, imageBank);
    drawRss(window, gameInfo, imageBank);
    drawEggs(window, gameInfo);
    drawPlayers(window, gameInfo);
}
