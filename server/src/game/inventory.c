/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** inventory
*/

#include "zappy_server.h"

void take_object(tile_t *tile, client_t *player, int resource, int frequency)
{
    if (tile->resources[resource] == 0) {
        //ko
        return;
    }
    tile->resources[resource]--;
    player->inventory[resource]++;

    //ok
}
