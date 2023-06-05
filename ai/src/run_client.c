/*
** EPITECH PROJECT, 2023
** run_client
** File description:
** The function runs the client program
*/

#include "client.h"

void run_client(client_t *client)
{
    FD_ZERO(&client->read_sockets);
    FD_ZERO(&client->write_sockets);
    FD_SET(client->server_fd, &client->read_sockets);
    FD_SET(client->server_fd, &client->write_sockets);
    if (select(FD_SETSIZE, &client->read_sockets,
    &client->write_sockets, NULL, NULL) < 0)
        exit(84);
    if (FD_ISSET(client->server_fd, &client->write_sockets)) {

    }
    if (FD_ISSET(client->server_fd, &client->read_sockets)) {
        
    }
}
