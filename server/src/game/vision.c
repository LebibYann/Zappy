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

static tile_t get_tile(tile_t **map, int w, int h, position_t position, int i)
{

}

tile_t *look(tile_t **map, client_t *player)
{
    int fov_size = get_fov_size(player->level);
    tile_t *fov = calloc(fov_size, sizeof(tile_t));

    if (!fov)
        return (NULL);

    for (int i = 0; i < fov_size; i++) {
    }

    return fov;
}
