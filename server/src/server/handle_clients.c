/*
** EPITECH PROJECT, 2023
** handle_clients
** File description:
** The file contains the handle clients function.
*/

#include "zappy_server.h"

static void client_interact(server_t *server, int current_fd)
{
    int client_socket;

    if (current_fd == server->fd){
        if ((client_socket = handle_connexion(server)) == -1)
            exit(84);
        FD_SET(client_socket, &server->read_sockets);
        FD_SET(client_socket, &server->write_sockets);
    } else
        handle_command(server, current_fd);
}

bool handle_client(server_t *server)
{
    fd_set read_sockets;
    fd_set write_sockets;

    read_sockets = server->read_sockets;
    write_sockets = server->write_sockets;
    if (select(FD_SETSIZE, &read_sockets, &write_sockets, NULL, NULL) < 0)
        return (false);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (FD_ISSET(i, &read_sockets))
            client_interact(server, i);
    return (true);
}
