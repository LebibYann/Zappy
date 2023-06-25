/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** explusion
*/

#include "zappy_server.h"

void tile_content(map_t *map, client_t *client, int x, int y)
{
    tile_t tile = map->tiles[x][y];

    zp_gui_send_package(&client->data, SERVER_SENT, ZP_BCT, x, y,
    tile.resources[0], tile.resources[1], tile.resources[2], tile.resources[3],
    tile.resources[4], tile.resources[5], tile.resources[6]);
}
