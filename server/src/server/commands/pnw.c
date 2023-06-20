/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** pnw
*/

#include "zappy_server.h"

void pnw(server_t *server, client_t *client, char **command)
{
    char *response = NULL;
    client_t *player = NULL;

    if (get_nb_params(command) != 5)
        return;
    player = get_client_by_id(server, atoi(command[1]));
    if (!player)
        return;
    response = my_strcat(response, "pnw ");
    response = my_strcat(response, my_itoa(player->id));
    response = my_strcat(response, " ");d
    response = my_strcat(response, my_itoa(player->x));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(player->y));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(player->orientation));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(player->level));
    response = my_strcat(response, " ");
    response = my_strcat(response, player->team->name);
    response = my_strcat(response, "\n");
    send_to(client->socket, response);
    free(response);
}
