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
#include <signal.h>

#include "str_split.h"
#include "zappy_client.h"
#include "zappy_resources.h"
#include "clock.h"
#include "c_zappy_protocol.h"
#include "zappy_client.h"
#include "zappy_client_handling.h"
#include "zappy_pending_command.h"

typedef struct parameter_s {
    char *parameter;
    int (*f)();
} parameter_t;

void init_server(server_t *server);
int open_server(int port, int queue);
void run_server(server_t *server);
void close_server(server_t *server);

int get_client_count_in_team(const char *team,
struct client_list_s *client_list);

int read_parameters(server_t *server, int ac, char **av);
int set_port(server_t *server, int *index, int ac, char **av);
int set_width(server_t *server, int *index, int ac, char **av);
int set_height(server_t *server, int *index, int ac, char **av);
int set_name(server_t *server, int *index, int ac, char **av);
int set_nclients(server_t *server, int *index, int ac, char **av);
int set_frequency(server_t *server, int *index, int ac, char **av);

void complete_ai_incantation(server_t *server);
void kill_starving_ai(server_t *server);

void remove_player_on_tile(tile_t *tile, client_t *player);
void add_player_on_tile(tile_t *tile, client_t *player);

void forward(map_t *map, client_t *client);
void turn_right(client_t *client);
void turn_left(client_t *client);
void look_around(map_t *map, client_t *client);
void inventory(client_t *client);
void broadcast(server_t *server, client_t *client, const char *message);
void connect_nbr(server_t *server, client_t *client);
void eject(map_t *map, client_t *client);
void take_object(tile_t *tile, client_t *client, const int resource);
void set_object_down(tile_t *tile, client_t *client, const int resource);
void start_incantation(tile_t *tile, client_t *client);
void complete_incantation(tile_t *tile, client_t *client, int frequency);
