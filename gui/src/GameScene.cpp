/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** GameScene
*/

#include "GameScene.hpp"

GameScene::GameScene(sf::RenderWindow &window, sf::Event &event, ZappyProtocolGUI &protocol)
: _window(window), _event(event), _protocol(protocol)
{
    _gameInfo.mapSize = {};
    _gameInfo.map = {};
    _gameInfo.mapContent = {};
    _gameInfo.players = {};
    _gameInfo.eggs = {};
    _gameInfo.teamNames = {};
    _gameInfo.nbrTeams = 0;
    _gameInfo.gameOver = false;
}

void error(std::string str)
{
    std::cout << str << std::endl;
    exit(1);
}

void set_music(sf::Music &music, std::string name, int volume)
{
    if (!music.openFromFile(name))
    {
        std::cout << "Error loading music" << std::endl;
        exit(1);
    }
    music.setVolume(volume);
    music.setLoop(true);
}

void set_text(sf::Text &text, std::string str, sf::Color color, sf::Vector2f pos, int x)
{
    text.setString(str);
    text.setCharacterSize(80);
    text.setFillColor(color);
    pos.x += x;
    text.setPosition(pos);
}

void GameScene::loadScene()
{
    return;
}

void GameScene::unloadScene()
{
    _music.stop();
}

void drawElements(sf::RenderWindow &window, sf::Event &event, t_gameInfo &gameInfo)
{
    if (gameInfo.gameOver == true)
        return;
    for (size_t i = 0; i < gameInfo.eggs.size(); ++i) {
        sf::RectangleShape egg(sf::Vector2f(50, 50));
        sf::Vector2f pos(gameInfo.eggs[i].x * 50, gameInfo.eggs[i].y * 50);

        egg.setFillColor(sf::Color::Green);
        egg.setPosition(pos);
        window.draw(egg);
    }
    for (size_t i = 0; i < gameInfo.players.size(); ++i) {
        sf::RectangleShape player(sf::Vector2f(50, 50));
        sf::Vector2f pos(gameInfo.players[i].x * 50, gameInfo.players[i].y * 50);

        player.setFillColor(sf::Color::Blue);
        player.setPosition(pos);
        window.draw(player);
    }
}

void GameScene::run()
{
    std::vector<t_zp_guiProtocol> packages;
    t_zp_guiProtocol package;

    /*
    set_music(this->_music, "sfx/menu/menu.ogg", 10);
    this->_music.play();
    this->_music.setVolume(80);
    */
    while (_protocol.receivePackage(package) == 0)
        packages.push_back(package);
    _gameInfo = analysePackages(packages);
}