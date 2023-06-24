/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** GameScene
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>

#include "IScene.hpp"
#include "ZappyProtocolGUI.hpp"
#include "ImageBank.hpp"

typedef struct s_playerStruct {
    int id;
    int x;
    int y;
    int orientation;
    int level;
    std::string teamName;
    bool eggLaying;
    bool isIncanting;
    bool isDead;
    sf::Sprite sprite;
} t_playerStruct;

typedef struct s_eggStruct {
    int id;
    int x;
    int y;
    bool isHatching;
    bool isDead;
    sf::Sprite sprite;
} t_eggStruct;

typedef struct s_gameInfo {
    std::vector<int> mapSize;
    std::vector<std::vector<std::vector<int>>> map;
    std::vector<int> mapContent;
    std::vector<t_playerStruct> players;
    std::vector<t_eggStruct> eggs;
    std::vector<std::string> teamNames;
    int nbrTeams;
    bool gameOver;
} t_gameInfo;

class GameScene: public IScene {
public:
    GameScene(sf::RenderWindow &window, sf::Event &event, ZappyProtocolGUI &protocol, Client &connection);
    ~GameScene();

    void loadScene();
    void unloadScene();
    void run();
    bool setConnection(std::string ip, std::string port);
    void refreshPackages(std::vector<t_zp_guiProtocol> packages);
private:
    sf::RenderWindow &_window;
    sf::Event &_event;
    ZappyProtocolGUI &_protocol;
    Client &_connection;
    ImageBank _imageBank;


    sf::Music _music;
    sf::Font _font;
    std::vector<sf::Sprite> _spriteDraw;
    std::vector<sf::Text> _textDraw;
    sf::Texture _personnage;
    sf::SoundBuffer _buff_sound;
    t_gameInfo _gameInfo;
};

std::vector<std::string> analyseArgs(int ac, char **av);
void drawElements(sf::RenderWindow &window, t_gameInfo &gameInfo);