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

#include "Framerate.hpp"
#include "SceneManager.hpp"

int main(void)
{
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Reverse");
    Framerate fps;
    sf::Event event;

    SceneManager scene = sceneSetup();

    scene.changeMenu("GameScene");
    while (window.isOpen()) {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        window.clear();
        scene.display(NULL);
        window.display();
        fps.capFramerate();
        fps.printLog();
    }
    return 0;
}
