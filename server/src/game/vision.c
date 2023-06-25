/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** vision
*/

#include "zappy_server.h"

static int get_fov_size(int player_level)
{
    player_level++;
    return player_level * player_level;
}

static tile_t *get_tiles(map_t *map, client_t *player, int dx, int dy)
{
    tile_t *fov = malloc(sizeof(tile_t) * get_fov_size(player->level));
    int i = 0;

    if (!fov)
        return NULL;

    for (int depth = 0; depth < player->level; depth++) {
        for (int width = -depth; width <= depth; width++) {
            int y = player->pos.y + dy * ((dx != dy) ? depth : width);
            int x = player->pos.x + dy * ((dx != dy) ? width : depth);
            fov[i++] = map->tiles[y][x];
        }
    }

    return fov;
}

tile_t *look_around(map_t *map, client_t *player)
{
    switch (player->orientation) {
    case NORTH:
        return get_tiles(map, player, 1, -1);
        break;
    case EAST:
        return get_tiles(map, player, 1, 1);
        break;
    case SOUTH:
        return get_tiles(map, player, -1, 1);
        break;
    case WEST:
        return get_tiles(map, player, -1, -1);
        break;
    default:
        return NULL;
        break;
    }
}
