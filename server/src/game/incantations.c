/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** incantations
*/

#include "zappy_server.h"
#include "zappy_incantations.h"

static bool verify_player_incantation(tile_t tile, int level)
{
    client_list_t *player_list = tile.players;
    int player_count = 0;

    while (player_list) {
        if (player_list->client->level >= level)
            player_count++;
        player_list = player_list->next;
    }

    if (player_count < INCANTATIONS[level - 1].prerequisites[0])
        return false;
    return true;
}

static bool verify_resources_incantation(tile_t tile, int level)
{
    int stone_count = 0;

    for (int stone = 1; stone < RESOURCES_COUNT; stone++) {
        stone_count = tile.resources[stone];
        if (stone_count < INCANTATIONS[level - 1].prerequisites[stone])
            return false;
    }

    return true;
}

static bool verify_incantation(tile_t **map, client_t *player)
{
    tile_t tile = map[player->position.y][player->position.x];

    if (!verify_player_incantation(tile, player->level))
        return false;
    if (!verify_resources_incantation(tile, player->level))
        return false;

    return true;
}

bool start_incantation(tile_t **map, client_t *player)
{
    if (player->level >= 8) {
        fprintf(stderr, "Player %d is already level 8.\n", player->fd);
        return false;
    }
    if (!verify_incantation(map, player)) {
        fprintf(stderr, "Player %d does not have the necessary resources.\n",
            player->fd);
        return false;
    }
    return true;
}
