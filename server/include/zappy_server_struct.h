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

typedef struct server_s {
    bool run;
    int fd;
    int port;
    int frequency;
    char **teams;
    int *max_team_cli;

    int nclients;
    struct client_list_s client_list;

    int width;
    int height;
    tile_t **map;
}   server_t;
