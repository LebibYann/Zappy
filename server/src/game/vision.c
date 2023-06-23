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

static tile_t get_tile(map_t *map, client_t *player, int tile_index)
{
    for (int i )

    return (tile_t) {
        .resources = {0, 0, 0, 0, 0, 0, 0},
        .players = NULL,
    };
}

tile_t *look(map_t *map, client_t *player)
{
    int player_level = player->level;
    int fov_size = get_fov_size(player->level);
    tile_t *fov = calloc(fov_size, sizeof(tile_t));

    if (!fov)
        return (NULL);

    for (int i = 0; i < fov_size; i++) {
        fov[i] = get_tile();
    }

    (void)map;
    (void)player_level;

    return fov;
}
