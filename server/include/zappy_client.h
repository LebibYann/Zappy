/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_client
*/

#pragma once

#include <sys/queue.h>

#include "c_zappy_protocol.h"

typedef enum client_category_e {
    CATEGORY_UNKNOWN,
    CATEGORY_AI,
    CATEGORY_GUI,
} client_category_t;

typedef struct position_s {
    int x;
    int y;
}   position_t;

typedef struct client_s {
    t_zp_pending_data data;
    int category;

    position_t position;
    int orientation;
    int inventory[7];
    int level;
    const char *team;
    struct timespec last_meal;
    bool dead;
    bool incantation;
    bool egg;
    LIST_ENTRY(client_s) other_clients;
}   client_t;

LIST_HEAD(client_list_s, client_s);

typedef struct player_list_s {
    client_t *client;
    struct player_list_s *next;
}   player_list_t;

enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

client_t *new_client_struct(int fd);

void init_client_struct(client_t *client, int fd);

void configure_client_as_ai(client_t *client, const char *team);

void configure_client_as_gui(client_t *client);

void clear_client_struct(client_t *client);

void delete_client_struct(client_t *client);
