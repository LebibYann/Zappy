/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** turn
*/

#include "zappy_server.h"

void turn_right(client_t *player)
{
    player->orientation = (player->orientation + 1) % 4;
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}

void turn_left(client_t *player)
{
    player->orientation = (player->orientation - 1) % 4;
    if (player->orientation < 0)
        player->orientation = 3;
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}
