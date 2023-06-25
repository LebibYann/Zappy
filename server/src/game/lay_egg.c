/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** lay_egg
*/

#include "zappy_server.h"

void lay_egg(tile_t *tile, client_t *player)
{
    (void)tile;
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}
