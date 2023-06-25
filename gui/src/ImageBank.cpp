/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** ImageBank
*/

#include "ImageBank.hpp"


ImageBank::ImageBank()
{
    _idleTexture.resize(3);
    _idleTexture[0].loadFromFile("assets/idle1.png");
    _idleTexture[1].loadFromFile("assets/idle2.png");
    _idleTexture[2].loadFromFile("assets/idle3.png");
    _idleSprites.resize(3);
    _idleSprites[0].setTexture(_idleTexture[0]);
    _idleSprites[1].setTexture(_idleTexture[1]);
    _idleSprites[2].setTexture(_idleTexture[2]);

    _incantTexture.resize(3);
    _incantTexture[0].loadFromFile("assets/incant1.png");
    _incantTexture[1].loadFromFile("assets/incant2.png");
    _incantTexture[2].loadFromFile("assets/incant3.png");
    _incantSprites.resize(3);
    _incantSprites[0].setTexture(_incantTexture[0]);
    _incantSprites[1].setTexture(_incantTexture[1]);
    _incantSprites[2].setTexture(_incantTexture[2]);

    _layingTexture.resize(3);
    _layingTexture[0].loadFromFile("assets/incant1.png");
    _layingTexture[1].loadFromFile("assets/incant2.png");
    _layingTexture[2].loadFromFile("assets/incant3.png");

    _layingSprites.resize(3);
    _layingSprites[0].setTexture(_layingTexture[0]);
    _layingSprites[1].setTexture(_layingTexture[1]);
    _layingSprites[2].setTexture(_layingTexture[2]);

    _deadTexture.resize(3);
    _deadTexture[0].loadFromFile("assets/dead1.png");
    _deadTexture[1].loadFromFile("assets/dead2.png");
    _deadTexture[2].loadFromFile("assets/dead3.png");
    _deadSprites.resize(3);
    _deadSprites[0].setTexture(_deadTexture[0]);
    _deadSprites[1].setTexture(_deadTexture[1]);
    _deadSprites[2].setTexture(_deadTexture[2]);

    _eggTexture.resize(3);
    _eggTexture[0].loadFromFile("assets/egg.png");
    _eggTexture[1].loadFromFile("assets/eggCracked.png");
    _eggTexture[2].loadFromFile("assets/eggBroken.png");
    _eggSprites.resize(3);
    _eggSprites[0].setTexture(_eggTexture[0]);
    _eggSprites[1].setTexture(_eggTexture[1]);
    _eggSprites[2].setTexture(_eggTexture[2]);

    _rssTexture.resize(7);
    _rssTexture[0].loadFromFile("assets/food.png");
    _rssTexture[1].loadFromFile("assets/linemate.png");
    _rssTexture[2].loadFromFile("assets/deraumere.png");
    _rssTexture[3].loadFromFile("assets/sibur.png");
    _rssTexture[4].loadFromFile("assets/mendiane.png");
    _rssTexture[5].loadFromFile("assets/phiras.png");
    _rssTexture[6].loadFromFile("assets/thystame.png");
    _rssSprites.resize(7);
    _rssSprites[0].setTexture(_rssTexture[0]);
    _rssSprites[1].setTexture(_rssTexture[1]);
    _rssSprites[2].setTexture(_rssTexture[2]);
    _rssSprites[3].setTexture(_rssTexture[3]);
    _rssSprites[4].setTexture(_rssTexture[4]);
    _rssSprites[5].setTexture(_rssTexture[5]);
    _rssSprites[6].setTexture(_rssTexture[6]);

    _groundTexture.resize(1);
    _groundTexture[0].loadFromFile("assets/ground.png");
    _groundSprites.resize(1);
    _groundSprites[0].setTexture(_groundTexture[0]);
}

ImageBank::~ImageBank()
{
}

void ImageBank::rescaleTexture(float x, float y)
{
    float multiplyerX = x / 32;
    float multiplyerY = y / 32;

    _groundSprites[0].scale(multiplyerX, multiplyerY);
    
    _idleSprites[0].scale(multiplyerX, multiplyerY);
    _idleSprites[1].scale(multiplyerX, multiplyerY);
    _idleSprites[2].scale(multiplyerX, multiplyerY);

    _incantSprites[0].scale(multiplyerX, multiplyerY);
    _incantSprites[1].scale(multiplyerX, multiplyerY);
    _incantSprites[2].scale(multiplyerX, multiplyerY);

    _layingSprites[0].scale(multiplyerX, multiplyerY);
    _layingSprites[1].scale(multiplyerX, multiplyerY);
    _layingSprites[2].scale(multiplyerX, multiplyerY);

    _deadSprites[0].scale(multiplyerX, multiplyerY);
    _deadSprites[1].scale(multiplyerX, multiplyerY);
    _deadSprites[2].scale(multiplyerX, multiplyerY);

    _eggSprites[0].scale(multiplyerX, multiplyerY);
    _eggSprites[1].scale(multiplyerX, multiplyerY);
    _eggSprites[2].scale(multiplyerX, multiplyerY);

    multiplyerX /= 2;
    multiplyerY /= 2;

    _rssSprites[0].scale(multiplyerX, multiplyerY);
    _rssSprites[1].scale(multiplyerX, multiplyerY);
    _rssSprites[2].scale(multiplyerX, multiplyerY);
    _rssSprites[3].scale(multiplyerX, multiplyerY);
    _rssSprites[4].scale(multiplyerX, multiplyerY);
    _rssSprites[5].scale(multiplyerX, multiplyerY);
    _rssSprites[6].scale(multiplyerX, multiplyerY);
}

sf::Sprite &ImageBank::getIdleSprite(int index)
{
    return _idleSprites[index];
}

sf::Sprite &ImageBank::getIncantSprite(int index)
{
    return _incantSprites[index];
}

sf::Sprite &ImageBank::getLayingSprite(int index)
{
    return _layingSprites[index];
}

sf::Sprite &ImageBank::getDeadSprite(int index)
{
    return _deadSprites[index];
}

sf::Sprite &ImageBank::getEggSprite(int index)
{
    return _eggSprites[index];
}

sf::Sprite &ImageBank::getRssSprite(int index)
{
    return _rssSprites[index];
}

sf::Sprite &ImageBank::getGroundSprite(int index)
{
    return _groundSprites[index];
}
