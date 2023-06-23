/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** remove_disconnected_client
*/

#include "zappy_server.h"

static bool client_has_been_disconnected(struct client_list_s *client_list)
{
    client_t *client;

    LIST_FOREACH(client, client_list, other_clients) {
        if (client->data.disconnected) {
            LIST_REMOVE(client, other_clients);
            delete_client_struct(client);
            printf("client disconnected\n");
            return (true);
        }
    }
    return (false);
}

void remove_disconnected_client(struct client_list_s *client_list)
{
    while (client_has_been_disconnected(client_list));
}
