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
    if (map[player->y][player->x].resources[LINEMATE] >= incantations[player->level - 1].linemate &&
        map[player->y][player->x].resources[DERAUMERE] >= incantations[player->level - 1].deraumere &&
        map[player->y][player->x].resources[SIBUR] >= incantations[player->level - 1].sibur &&
        map[player->y][player->x].resources[MENDIANE] >= incantations[player->level - 1].mendiane &&
        map[player->y][player->x].resources[PHIRAS] >= incantations[player->level - 1].phiras &&
        map[player->y][player->x].resources[THYSTAME] >= incantations[player->level - 1].thystame)
        return (true);

    return (false);
}

// bool verify_incantation(tile_t **map, client_t *player)
// {
    // if (player->level >= 8) {
        // fprintf(stderr, "Player %d is already level 8.\n", player->fd);
        // return (false);
    // }
//
// }
