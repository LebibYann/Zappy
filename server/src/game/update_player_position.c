/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** update_player_position
*/

#include "zappy_server.h"

void remove_player_on_tile(tile_t *tile, client_t *player)
{
    player_list_t *tmp = tile->players;
    player_list_t *prev = NULL;

    while (tmp) {
        if (tmp->client == player && prev) {
            prev->next = tmp->next;
            free(tmp);
            return;
        }
        if (tmp->client == player && !prev) {
            tile->players = tmp->next;
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void add_player_on_tile(tile_t *tile, client_t *player)
{
    player_list_t *new = malloc(sizeof(player_list_t));
    player_list_t *tmp = tile->players;

    if (!new)
        return;

    new->client = player;
    new->next = NULL;
    if (!tmp) {
        tile->players = new;
        return;
    }

    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
