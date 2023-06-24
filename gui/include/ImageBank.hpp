/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** Imagebank
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

class ImageBank {
    public:
        ImageBank();
        ~ImageBank();
        sf::Sprite &getIdleSprite(int index);
        sf::Sprite &getIncantSprite(int index);
        sf::Sprite &getLayingSprite(int index);
        sf::Sprite &getDeadSprite(int index);
        sf::Sprite &getEggSprite(int index);
        sf::Sprite &getRssSprite(int index);
        sf::Sprite &getGroundSprite(int index);

    private:
        std::vector<sf::Texture> _idleTexture;
        std::vector<sf::Texture> _incantTexture;
        std::vector<sf::Texture> _layingTexture;
        std::vector<sf::Texture> _deadTexture;
        std::vector<sf::Texture> _eggTexture;
        std::vector<sf::Texture> _rssTexture;
        std::vector<sf::Texture> _groundTexture;
        
        std::vector<sf::Sprite> _idleSprites;
        std::vector<sf::Sprite> _incantSprites;
        std::vector<sf::Sprite> _layingSprites;
        std::vector<sf::Sprite> _deadSprites;
        std::vector<sf::Sprite> _eggSprites;
        std::vector<sf::Sprite> _rssSprites;
        std::vector<sf::Sprite> _groundSprites;
};
