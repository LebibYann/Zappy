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


class ImageBank {
    public:
        ImageBank();
        ~ImageBank();
        sf::Texture getIdleSprite(int index);
        sf::Texture getIncantSprite(int index);
        sf::Texture getLayingSprite(int index);
        sf::Texture getDeadSprite(int index);
        sf::Texture getEggSprite(int index);
        sf::Texture getRssSprite(int index);
        sf::Texture getGroundSprite(int index);

    private:
        std::vector<sf::Texture> _idleSprites;
        std::vector<sf::Texture> _incantSprites;
        std::vector<sf::Texture> _layingSprites;
        std::vector<sf::Texture> _deadSprites;
        std::vector<sf::Texture> _eggSprites;
        std::vector<sf::Texture> _rssSprites;
        std::vector<sf::Texture> _groundSprites;
};
