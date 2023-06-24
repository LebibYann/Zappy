/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** ImageBank
*/

#include "ImageBank.hpp"

ImageBank::ImageBank()
{
    sf::Texture texture;

    texture.loadFromFile("assets/idle1.png");
    _idleSprites.push_back(texture);
    texture.loadFromFile("assets/idle2.png");
    _idleSprites.push_back(texture);
    texture.loadFromFile("assets/idle3.png");
    _idleSprites.push_back(texture);

    texture.loadFromFile("assets/incant1.png");
    _incantSprites.push_back(texture);
    texture.loadFromFile("assets/incant2.png");
    _incantSprites.push_back(texture);
    texture.loadFromFile("assets/incant3.png");
    _incantSprites.push_back(texture);

    texture.loadFromFile("assets/incant1.png");
    _layingSprites.push_back(texture);
    texture.loadFromFile("assets/incant2.png");
    _layingSprites.push_back(texture);
    texture.loadFromFile("assets/incant3.png");
    _layingSprites.push_back(texture);

    texture.loadFromFile("assets/dead1.png");
    _deadSprites.push_back(texture);
    texture.loadFromFile("assets/dead2.png");
    _deadSprites.push_back(texture);
    texture.loadFromFile("assets/dead3.png");
    _deadSprites.push_back(texture);

    texture.loadFromFile("assets/egg.png");
    _eggSprites.push_back(texture);
    texture.loadFromFile("assets/eggCracked.png");
    _eggSprites.push_back(texture);
    texture.loadFromFile("assets/eggBroken.png");
    _eggSprites.push_back(texture);

    texture.loadFromFile("assets/food.png");
    _rssSprites.push_back(texture);
    texture.loadFromFile("assets/linemate.png");
    _rssSprites.push_back(texture);
    texture.loadFromFile("assets/deraumere.png");
    _rssSprites.push_back(texture);
    texture.loadFromFile("assets/sibur.png");
    _rssSprites.push_back(texture);
    texture.loadFromFile("assets/mendiane.png");
    _rssSprites.push_back(texture);
    texture.loadFromFile("assets/phiras.png");
    _rssSprites.push_back(texture);
    texture.loadFromFile("assets/thystame.png");
    _rssSprites.push_back(texture);

    //texture.loadFromFile("assets/ground.png");
    //_groundSprites.push_back(texture);
}

ImageBank::~ImageBank()
{
}

sf::Texture ImageBank::getIdleSprite(int index)
{
    return _idleSprites[index];
}

sf::Texture ImageBank::getIncantSprite(int index)
{
    return _incantSprites[index];
}

sf::Texture ImageBank::getLayingSprite(int index)
{
    return _layingSprites[index];
}

sf::Texture ImageBank::getDeadSprite(int index)
{
    return _deadSprites[index];
}

sf::Texture ImageBank::getEggSprite(int index)
{
    return _eggSprites[index];
}

sf::Texture ImageBank::getRssSprite(int index)
{
    return _rssSprites[index];
}

sf::Texture ImageBank::getGroundSprite(int index)
{
    return _groundSprites[index];
}
