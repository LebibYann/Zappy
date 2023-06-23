/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_unknown_clients
*/

#include "zappy_server.h"


void handle_unknown_clients(server_t *server, client_t *client)
{
    char *line;
    (void)server;

    zp_exchange_data(&(client->data), HANDLE_NO_WAIT, HANDLE_IGNORE);
    if ((line = zp_getline_pending_data(&(client->data))) == NULL)
        return;
    printf("%s\n", line);
    if (strcmp(line, "GRAPHIC\n") == 0) {
        printf("It's a graphic client !\n");
        configure_client_as_gui(client);
        free(line);
        return;
    }
    printf("Maybe an AI\n");
    free(line);
}
