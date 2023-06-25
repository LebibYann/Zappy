/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_server_struct
*/

#pragma once

#include <stdbool.h>

#include "zappy_resources.h"
#include "zappy_client.h"

typedef struct tile_s {
    int resources[RESOURCES_COUNT];
    struct player_list_s *players;
    struct egg_list_s *eggs;
}   tile_t;

typedef struct map_s {
    int w;
    int h;
    tile_t **tiles;
}   map_t;

typedef struct server_s {
    bool run;
    int fd;
    int port;
    int frequency;
    char **teams;
    int *max_team_cli;

    struct client_list_s client_list;

    map_t map;
}   server_t;
