/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** send_map
*/

#include "zappy_server.h"

void send_map(t_zp_pending_data *pdata, map_t *map)
{
    for (int y = 0; y < map->h && map->tiles != NULL; ++y) {
        for (int x = 0; x < map->w; ++x)
            send_tile(pdata, x, y, map->tiles[y][x].resources);
    }
}
