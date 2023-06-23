/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_client
*/

#pragma once

typedef struct client_s {
    int fd;
    struct position_s position;
    int orientation;
    int inventory[7];
    int level;
    char *team;
    bool dead;
    bool incantation;
    bool egg;
}   client_t;

typedef struct client_list_s {
    client_t *client;
    struct client_list_s *next;
}   client_list_t;

typedef struct position_s {
    int x;
    int y;
}   position_t;

enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
};
