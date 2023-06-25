/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** AudioBank
*/

#include "AudioBank.hpp"

AudioBank::AudioBank()
{
    _music.openFromFile("Sounds/Sweden.ogg");

    _soundBuffers.resize(NBR_SOUNDS);
    _sounds.resize(NBR_SOUNDS);

    _soundBuffers[INCANT].loadFromFile("Sounds/evolve.ogg");
    _soundBuffers[LVLUP].loadFromFile("Sounds/lvlUp.ogg");
    _soundBuffers[DEATH].loadFromFile("Sounds/death.ogg");

    _sounds[INCANT].setBuffer(_soundBuffers[INCANT]);
    _sounds[LVLUP].setBuffer(_soundBuffers[LVLUP]);
    _sounds[DEATH].setBuffer(_soundBuffers[DEATH]);
    _sounds[DEATH].setVolume(50);
}

AudioBank::~AudioBank()
{
}

void AudioBank::playMusic()
{
    _music.play();
    _music.setLoop(true);
}

void AudioBank::playSound(int index)
{
    _sounds[index].play();
}