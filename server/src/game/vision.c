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

static tile_t *get_north_tiles(map_t *map, client_t *player)
{
    tile_t *fov = malloc(sizeof(tile_t) * get_fov_size(player->level));
    int i = 1;

    if (!fov)
        return NULL;

    fov[0] = map->tiles[player->position.y][player->position.x];
    for (int y = 1; y < player->level; y++) {
        for (int x = -y; x <= y; x++) {
            fov[i] = map->tiles[player->position.y - y][player->position.x + x];
            i++;
        }
    }

    return fov;
}

static tile_t *get_east_tiles(map_t *map, client_t *player)
{
    tile_t *fov = malloc(sizeof(tile_t) * get_fov_size(player->level));
    int i = 1;

    if (!fov)
        return NULL;

    fov[0] = map->tiles[player->position.y][player->position.x];
    for (int x = 1; x < player->level; x++) {
        for (int y = -x; y <= x; y++) {
            fov[i] = map->tiles[player->position.y + y][player->position.x + x];
            i++;
        }
    }

    return fov;
}

static tile_t *get_south_tiles(map_t *map, client_t *player)
{
    tile_t *fov = malloc(sizeof(tile_t) * get_fov_size(player->level));
    int i = 1;

    if (!fov)
        return NULL;

    fov[0] = map->tiles[player->position.y][player->position.x];
    for (int y = 1; y < player->level; y++) {
        for (int x = y; x >= -y; x--) {
            fov[i] = map->tiles[player->position.y + y][player->position.x + x];
            i++;
        }
    }

    return fov;
}

static tile_t *get_west_tiles(map_t *map, client_t *player)
{
    tile_t *fov = malloc(sizeof(tile_t) * get_fov_size(player->level));
    int i = 1;

    if (!fov)
        return NULL;

    fov[0] = map->tiles[player->position.y][player->position.x];
    for (int x = 1; x < player->level; x++) {
        for (int y = x; y >= -x; y--) {
            fov[i] = map->tiles[player->position.y + y][player->position.x - x];
            i++;
        }
    }

    return fov;
}

static tile_t *look_direction(map_t *map, client_t *player)
{
    switch (player->orientation) {
    case NORTH:
        return get_north_tiles(map, player);
        break;
    case EAST:
        return get_east_tiles(map, player);
        break;
    case SOUTH:
        return get_south_tiles(map, player);
        break;
    case WEST:
        return get_west_tiles(map, player);
        break;
    default:
        return NULL;
        break;
    }
}

tile_t *look(map_t *map, client_t *player)
{
    struct timespec start, now;
    tile_t *fov;

    timespec_get(&start, TIME_UTC);
    timespec_get(&now, TIME_UTC);

    fov = look_direction(map, player);

    while (now.tv_sec - start.tv_sec < 7)
        timespec_get(&now, TIME_UTC);
}
