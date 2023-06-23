/*
** EPITECH PROJECT, 2023
** server
** File description:
** add_new_client
*/

#include "zappy_server.h"

bool add_new_client(server_t *server)
{
    client_t *client;
    int addr_size = sizeof(struct sockaddr_in);
    int client_socket;
    struct sockaddr_in client_addr;

    if ((client_socket = accept(server->fd, (struct sockaddr *)
    &client_addr, (socklen_t *)&addr_size)) < 0)
        return (false);
    client = new_client_struct(client_socket);
    LIST_INSERT_HEAD(&(server->client_list), client, other_clients);
    printf("New client added\n");
    return (true);
}
