/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** inventory
*/

#include "zappy_server.h"

void take_object(tile_t *tile, client_t *player, int resource, int frequency)
{
    struct timespec start, now;
    int time = 7 / frequency;

    timespec_get(&start, TIME_UTC);
    timespec_get(&now, TIME_UTC);

    if (tile->resources[resource] == 0) {
        //ko
        return;
    }
    tile->resources[resource]--;
    player->inventory[resource]++;

    while (now.tv_sec - start.tv_sec < time)
        timespec_get(&now, TIME_UTC);
    //ok
}
