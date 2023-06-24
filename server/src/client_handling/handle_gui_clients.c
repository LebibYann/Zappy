/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_gui_clients
*/

#include "zappy_server.h"


void handle_gui_clients(server_t *server, client_t *client)
{
    char *line;
    (void)server;

    zp_exchange_data(&(client->data), HANDLE_NO_WAIT, HANDLE_IGNORE);
    if ((line = zp_getline_pending_data(&(client->data))) == NULL)
        return;
    free(line);
}
