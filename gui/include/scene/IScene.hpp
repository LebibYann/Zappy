/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** IScene
*/

#pragma once

class SceneManager;

class IScene {
public:
    ~IScene() = default;

    virtual void loadScene() = 0;
    virtual void unloadScene() = 0;
    virtual void run() = 0;
};
