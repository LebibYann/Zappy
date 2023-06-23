/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unistd.h>

#include "ZappyProtocolGUI.hpp"
#include "GameScene.hpp"

int main(int ac, char **av)
{
    srand(time(nullptr));

    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Reverse");
    Client connection;
    std::vector<std::string> connectionID = analyseArgs(ac - 1, &av[1]);
    connection.Connect(connectionID[0], atoi(connectionID[1].c_str()));
    ZappyProtocolGUI protocol(connection.FD());
    protocol.setFd(connection.FD());
    protocol.sendPackage(ZP_GRAPHIC);
    GameScene gameScene(window, event, protocol, connection);

    while (window.isOpen()) {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        window.clear();
        gameScene.run();
        window.display();
    }
    return 0;
}
