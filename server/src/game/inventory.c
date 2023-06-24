/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** inventory
*/

#include "zappy_server.h"

void take_object(tile_t *tile, client_t *player, int resource)
{
    if (tile->resources[resource] == 0)
        return zp_server_ai_send_basic_package(&player->data, RESPONSE_KO);

    tile->resources[resource]--;
    player->inventory[resource]++;

    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}

void set_object_down(tile_t *tile, client_t *player, int resource)
{
    if (player->inventory[resource] == 0)
        return zp_server_ai_send_basic_package(&player->data, RESPONSE_KO);

    tile->resources[resource]++;
    player->inventory[resource]--;

    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}
