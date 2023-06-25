/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** AudioBank
*/

#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

typedef enum e_soundNames {
    INCANT,
    LVLUP,
    DEATH,
    NBR_SOUNDS
} t_soundsName;

class AudioBank {
    public:
        AudioBank();
        ~AudioBank();
        void playMusic();
        void playSound(int index);

    private:
        sf::Music _music;
        std::vector<sf::SoundBuffer> _soundBuffers;
        std::vector<sf::Sound> _sounds;
};
