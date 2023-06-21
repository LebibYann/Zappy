/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** tna
*/

#include "zappy_server.h"

void tna(server_t *server, client_t *client, char **command)
{
    char *response = NULL;

    (void)command;
    for (size_t i = 0; i < server->nb_teams; i++){
        response = my_strcat(response, "tna ");
        response = my_strcat(response, server->teams[i]->name);
        response = my_strcat(response, "\n");
    }
    send_to(client->socket, response);
    free(response);
}
