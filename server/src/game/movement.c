/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** movement
*/

#include "zappy_server.h"

void turn_right(client_t *client)
{
    client->orientation = (client->orientation + 1) % 4;
}

void turn_left(client_t *client)
{
    client->orientation = (client->orientation - 1) % 4;
    if (client->orientation < 0)
        client->orientation = 3;
}

static void remove_player_on_tile(tile_t *tile, client_t *player)
{
    player_list_t *tmp = tile->players;
    player_list_t *prev = NULL;

    while (tmp) {
        if (tmp->client == player) {
            if (prev)
                prev->next = tmp->next;
            else
                tile->players = tmp->next;
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

static void add_player_on_tile(tile_t *tile, client_t *player)
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

static void update_player_position(map_t *map, client_t *player)
{
    switch (player->orientation) {
    case NORTH:
        player->position.y = (player->position.y - 1) % map->h;
        break;
    case EAST:
        player->position.x = (player->position.x + 1) % map->w;
        break;
    case SOUTH:
        player->position.y = (player->position.y + 1) % map->h;
        break;
    case WEST:
        player->position.x = (player->position.x - 1) % map->w;
        break;
    default:
        break;
    }
    if (player->position.x < 0)
        player->position.x = map->w - 1;
    if (player->position.y < 0)
        player->position.y = map->h - 1;
}

void forward(map_t *map, client_t *player, int frequency)
{
    struct timespec start, now;
    int time = 7 / frequency;
    tile_t *tile;

    timespec_get(&start, TIME_UTC);
    timespec_get(&now, TIME_UTC);

    tile = &map->tiles[player->position.y][player->position.x];
    remove_player_on_tile(tile, player);

    update_player_position(map, player);

    tile = &map->tiles[player->position.y][player->position.x];
    add_player_on_tile(tile, player);

    while (now.tv_sec - start.tv_sec < time)
        timespec_get(&now, TIME_UTC);
}
