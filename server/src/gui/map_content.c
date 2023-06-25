/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** explusion
*/

#include "zappy_server.h"

void map_content(server_t *server, client_t *client)
{
    map_t map = server->map;

    for (int x = 0; x < map.w; ++x)
        for (int y = 0; y < map.h; ++y)
            tile_content(&map, client, x, y);
}
