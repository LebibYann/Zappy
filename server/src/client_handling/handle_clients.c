/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_client
*/

#include "zappy_server.h"

void handle_clients(server_t *server)
{
    client_t *client;

    LIST_FOREACH(client, &(server->client_list), other_clients) {
        switch (client->category) {
            case CATEGORY_UNKNOWN:
                handle_unknown_clients(server, client);
                break;
            case CATEGORY_GUI:
                handle_gui_clients(server, client);
                break;
            case CATEGORY_AI:
                handle_ai_clients(server, client);
                break;
        }
    }
}
