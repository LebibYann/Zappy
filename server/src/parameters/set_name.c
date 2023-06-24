/*
** EPITECH PROJECT, 2023
** set_name
** File description:
** The function setups the name of the server.
*/

#include "zappy_server.h"

int set_name(server_t *server, int *index, int ac, char **av)
{
    if (*index >= ac){
        fprintf(stderr, "./server: option requires an argument -- '-n'\n");
        return (-1);
    }
    split_free(server->teams);
    server->teams = NULL;
    for (; *index < ac && av[*index][0] != '-'; ++(*index))
        split_insert(&server->teams, av[*index], -1);
    --(*index);
    return (0);
}
