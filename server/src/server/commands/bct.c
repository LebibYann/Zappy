/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** bct
*/

#include "zappy_server.h"

void bct(server_t *server, client_t *client, char **command)
{
    char *response = NULL;
    int x = 0;
    int y = 0;

    if (get_nb_params(command) != 3)
        return;
    x = atoi(command[1]);
    y = atoi(command[2]);
    if (x < 0 || x >= server->map->width || y < 0 || y >= server->map->height)
        return;
    response = my_strcat(response, "bct ");
    response = my_strcat(response, my_itoa(x));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(y));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].food));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].linemate));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].deraumere));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].sibur));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].mendiane));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].phiras));
    response = my_strcat(response, " ");
    response = my_strcat(response, my_itoa(server->map->tiles[y][x].thystame));
    response = my_strcat(response, "\n");
    send_to(client->socket, response);
    free(response);
}
