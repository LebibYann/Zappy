/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** DrawMapElems
*/

#include "GameScene.hpp"
#include "ZappyProtocolGUI.hpp"

#define TILE_SIZE 50

void drawGround(sf::RenderWindow &window, t_gameInfo &gameInfo)
{
    sf::RectangleShape ground(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    sf::Vector2f pos(0, 0);

    ground.setFillColor(sf::Color::Green);
    for (int i = 0; i < gameInfo.mapSize[1]; ++i) {
        for (int j = 0; j < gameInfo.mapSize[0]; ++j) {
            pos.x = i * TILE_SIZE;
            pos.y = j * TILE_SIZE;
            ground.setPosition(pos);
            window.draw(ground);
        }
    }
}

void drawFood(sf::RenderWindow &window, t_gameInfo &gameInfo, ImageBank &imageBank)
{
    sf::Sprite sprite;
    sprite.setTexture(imageBank.getRssSprite(0));
 
    for (size_t i = 0; i < gameInfo.map.size(); ++i) {
        for (size_t j = 0; j < gameInfo.map[i].size(); ++j) {
            if (gameInfo.map[j][i][0] > 0) {
                sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                window.draw(sprite);
            }

        }
    }
}

void drawEggs(sf::RenderWindow &window, t_gameInfo &gameInfo)
{
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        gameInfo.eggs[i].sprite.setPosition(gameInfo.eggs[i].x * TILE_SIZE, gameInfo.eggs[i].y * TILE_SIZE);
        window.draw(gameInfo.eggs[i].sprite);
    }
}

void drawPlayers(sf::RenderWindow &window, t_gameInfo &gameInfo)
{
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        gameInfo.players[i].sprite.setPosition(gameInfo.players[i].x * TILE_SIZE, gameInfo.players[i].y * TILE_SIZE);
        window.draw(gameInfo.players[i].sprite);
    }
}

void drawElements(sf::RenderWindow &window, t_gameInfo &gameInfo, ImageBank &imageBank)
{
    if (gameInfo.gameOver == true)
        return;
    drawGround(window, gameInfo);
    drawFood(window, gameInfo, imageBank);
    drawEggs(window, gameInfo);
    drawPlayers(window, gameInfo);
}