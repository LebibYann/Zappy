/*
** EPITECH PROJECT, 2023
** handle_connection
** File description:
** The file contains the function handle_connexion.
*/

#include "zappy_server.h"

int handle_connexion(server_t *server)
{
    int addr_size = sizeof(struct sockaddr_in);
    int client_socket;
    struct sockaddr_in client_addr;

    if ((client_socket = accept(server->fd, (struct sockaddr *)
    &client_addr, (socklen_t *)&addr_size)) < 0)
        return (-1);
    return (client_socket);
}
