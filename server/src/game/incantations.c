/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** incantations
*/

#include "zappy_server.h"
#include "zappy_incantations.h"

static bool verify_player_incantation(tile_t *tile, int level)
{
    int player_count = 0;
    player_list_t *player_list = tile->players;

    while (player_list) {
        player_list->client->level >= level ? player_count++ : 0;
        if (player_count >= INCANTATIONS[level - 1].prerequisites[0])
            return true;
        player_list = player_list->next;
    }

    return false;
}

static bool verify_stone_incantation(tile_t *tile, int level)
{
    int stone_count = 0;

    for (int stone = 1; stone < RESOURCES_COUNT; stone++) {
        stone_count = tile->resources[stone];
        if (stone_count < INCANTATIONS[level - 1].prerequisites[stone])
            return false;
    }

    return true;
}

static bool verify_incantation(tile_t *tile, client_t *player)
{
    const int player_level = player->level;

    if (player_level >= 8){
        fprintf(stderr, "Player %d is already level 8.\n", player->data.fd);
        return false;
    }

    if (!verify_player_incantation(tile, player_level)) {
        fprintf(stderr, "Player %d does not have the necessary players.\n",
            player->data.fd);
        return false;
    }
    if (!verify_stone_incantation(tile, player_level)) {
        fprintf(stderr, "Player %d does not have the necessary stones.\n",
            player->data.fd);
        return false;
    }

    return true;
}

void remove_stones(tile_t *tile, client_t *player)
{
    for (int stone = 1; stone < RESOURCES_COUNT; stone++) {
        tile->resources[stone] -= INCANTATIONS[player->level - 1]
            .prerequisites[stone];
    }
    player->incantation = false;
}

void start_incantation(tile_t **tiles, client_t *player, int frequency)
{
    struct timespec start, now;
    int time = 300 / frequency;
    tile_t *tile = &tiles[player->position.y][player->position.x];

    if (!verify_incantation(tile, player))
        return;

    timespec_get(&start, TIME_UTC);
    timespec_get(&now, TIME_UTC);
    player->incantation = true;

    while (now.tv_nsec - start.tv_nsec < time)
        timespec_get(&now, TIME_UTC);
    remove_stones(tile, player);
    if (player->incantation)
        player->level++;
}
