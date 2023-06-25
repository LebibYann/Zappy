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
    client->server = server;
    LIST_INSERT_HEAD(&(server->client_list), client, other_clients);
    zp_write_data(&(client->data), "WELCOME\n", 8);
    zp_exchange_data(&(client->data), HANDLE_IGNORE, HANDLE_WAIT);
    return (true);
}
