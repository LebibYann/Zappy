/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "ZappyProtocolGUI.hpp"

GameScene::GameScene(sf::RenderWindow &window, sf::Event &event, ZappyProtocolGUI &protocol, Client &connection)
: _window(window), _event(event), _protocol(protocol), _connection(connection)
{
    _gameInfo.mapSize = {0, 0};
    _gameInfo.map = {};
    _gameInfo.mapContent = {};
    _gameInfo.players = {};
    _gameInfo.eggs = {};
    _gameInfo.teamNames = {};
    _gameInfo.nbrTeams = 0;
    _gameInfo.gameOver = false;
}

GameScene::~GameScene()
{
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

void GameScene::run()
{
    std::vector<t_zp_guiProtocol> packages;
    t_zp_guiProtocol package;

    /*
    set_music(this->_music, "sfx/menu/menu.ogg", 10);
    this->_music.play();
    this->_music.setVolume(80);
    */
    this->_protocol.receive();
    while (_protocol.receivePackage(package) == 0)
        packages.push_back(package);
    _gameInfo = analysePackages(packages);
    drawElements(_window, _gameInfo);
}

bool GameScene::setConnection(std::string ip, std::string port)
{
    if (!_connection.Connect(ip, atoi(port.c_str()))) {
        error("Error: Connection failed");
        exit(84);
    }
    return (true);
}
