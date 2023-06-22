/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_server
*/

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>

#include "str_split.h"
#include "zappy_resources.h"
#include "clock.h"

typedef struct parameter_s
{
    char *parameter;
    int (*f)();
} parameter_t;

typedef struct server_s {
    int fd;
    int port;
    int width;
    int height;
    char **teams;
    int nclients;
    int frequency;
    fd_set read_sockets;
    fd_set write_sockets;
    tile_t **map;
}   server_t;

typedef struct client_s {
    int fd;
    int x;
    int y;
    int orientation;
    int inventory[7];
    int level;
    char *team;
    bool dead;
    bool evolving;
    bool egg;
}   client_t;

void init_server(server_t *server);
int open_server(int port, int queue);
bool handle_client(server_t *server);
int handle_connexion(server_t *server);

int read_parameters(server_t *server, int ac, char **av);
int set_port(server_t *server, int *index, int ac, char **av);
int set_width(server_t *server, int *index, int ac, char **av);
int set_height(server_t *server, int *index, int ac, char **av);
int set_name(server_t *server, int *index, int ac, char **av);
int set_nclients(server_t *server, int *index, int ac, char **av);
int set_frequency(server_t *server, int *index, int ac, char **av);
