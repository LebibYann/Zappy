/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** incantations
*/

#include "zappy_server.h"
#include "zappy_incantations.h"

bool verify_incantation(tile_t **map, client_t *player)
{
    const incantations_t *incantation = &INCANTATIONS[player->level - 1];
    tile_t *tile = &map[player->y][player->x];

    for (int resource = 0; resource < RESOURCES_COUNT; resource++)
        if (tile->resources[resource] < incantation->prerequisites[resource])
            return false;

    return true;
}

bool start_incantation(tile_t **map, client_t *player)
{
    if (player->level >= 8) {
        fprintf(stderr, "Player %d is already level 8.\n", player->fd);
        return (false);
    }
    if (!verify_incantation(map, player)) {
        fprintf(stderr, "Player %d does not have the necessary resources.\n",
            player->fd);
        return (false);
    }
    return (true);
}
