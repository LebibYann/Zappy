/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** remove_all_client
*/

#include "zappy_client_handling.h"

void remove_all_clients(struct client_list_s *client_list)
{
    client_t *client;

    while (!LIST_EMPTY(client_list)) {
        client = LIST_FIRST(client_list);
        LIST_REMOVE(client, other_clients);
        delete_client_struct(client);
    }
}
