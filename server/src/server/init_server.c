/*
** EPITECH PROJECT, 2023
** init_server
** File description:
** The file initialize the server values.
*/

#include "zappy_server.h"

void init_server(server_t *server)
{
    server->port = 4242;
    server->width = 10;
    server->height = 10;
    server->teams = NULL;
    server->nclients = 1;
    server->frequency = 10;
    FD_ZERO(&server->read_sockets);
    FD_ZERO(&server->write_sockets);
}
