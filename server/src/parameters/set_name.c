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
        fprintf(stderr,  "./server: option requires an argument -- '%s'\n", "-n");
        return (-1);
    }
    for (; av[*index][0] != '-' && *index < ac; index++)
        split_insert(&server->teams, strdup(av[*index]), -1);
    return (0);
}
