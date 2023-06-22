/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zdf
*/

#include "SceneManager.hpp"

SceneManager::SceneManager()
{
    this->_activeScene = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::addMenu(std::string menuName, IScene *scene)
{
    _sceneList.insert({menuName, scene});
}

void SceneManager::display()
{
    if (this->_activeScene != nullptr)
        this->_activeScene->run();
}

void SceneManager::changeMenu(std::string sceneName)
{
    if (_sceneList.find(sceneName) != _sceneList.end()) {
        if (this->_activeScene != nullptr)
            this->_activeScene->unloadScene();
        _previousScene = _currentScene;
        _currentScene = sceneName;
        _activeScene = this->_sceneList.find(_currentScene)->second;
        _activeScene->loadScene();
    }
}
