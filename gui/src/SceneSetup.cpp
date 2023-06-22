/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** SceneSetup
*/

#include "SceneManager.hpp"
#include "GameScene.hpp"

SceneManager sceneSetup(sf::RenderWindow &window, sf::Event &event, ZappyProtocolGUI &protocol)
{
    SceneManager scene;
    GameScene gameScene(window, event, protocol);

    scene.addMenu("GameScene", &gameScene);
    return (scene);
}