/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** inventory
*/

#include "zappy_server.h"

void take_object(server_t *server, tile_t *tile, client_t *player, const int resource)
{
    if (resource < 0 || tile->resources[resource] == 0)
        return zp_server_ai_send_basic_package(&player->data, RESPONSE_KO);

    server->resource_count[resource]--;
    tile->resources[resource]--;
    player->inventory[resource]++;

    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
    update_map(player->server);
}

void set_object_down(server_t *server, tile_t *tile, client_t *player, const int resource)
{
    if (player->inventory[resource] == 0)
        return zp_server_ai_send_basic_package(&player->data, RESPONSE_KO);

    server->resource_count[resource]++;
    tile->resources[resource]++;
    player->inventory[resource]--;

    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
    update_map(player->server);
}

void inventory(client_t *player)
{
    char response[256] = {0};

    sprintf(response, "[food %d, linemate %d, deraumere %d, sibur %d, "
"mendiane %d, phiras %d, thystame %d]\n",
            player->inventory[FOOD],
            player->inventory[LINEMATE], player->inventory[DERAUMERE],
            player->inventory[SIBUR], player->inventory[MENDIANE],
            player->inventory[PHIRAS], player->inventory[THYSTAME]);
    zp_server_ai_send_package(&player->data, response);
}
