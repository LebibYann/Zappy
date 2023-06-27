/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** verify_incantation
*/

#include "zappy_server.h"
#include "zappy_incantations.h"

bool verify_player_incantation(tile_t *tile, const int level)
{
    int player_count = 0;
    player_list_t *player_list = tile->players;
    client_t *player = NULL;

    while (player_list) {
        player = player_list->client;
        if (player->level == level)
            player_count++;
        if (player_count >= INCANTATIONS[level - 1].prerequisites[0])
            return true;
        player_list = player_list->next;
    }
    return false;
}

bool verify_stone_incantation(tile_t *tile, const int level)
{
    int stone_count = 0;

    for (int stone = 1; stone < RESOURCES_COUNT; stone++) {
        stone_count = tile->resources[stone];
        if (stone_count < INCANTATIONS[level - 1].prerequisites[stone])
            return false;
    }
    return true;
}

bool verify_incantation(tile_t *tile, client_t *player)
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
