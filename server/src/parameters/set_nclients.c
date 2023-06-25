/*
** EPITECH PROJECT, 2023
** set_nclients
** File description:
** The function setups the nclients of the server.
*/

#include "zappy_server.h"

int set_nclients(server_t *server, int *index, int ac, char **av)
{
    int nclients = 3;

    if (*index >= ac){
        fprintf(stderr,  "./server: option requires an argument -- '-c'\n");
        return (-1);
    }
    nclients = atoi(av[*index]);
    if (nclients < 1){
        fprintf(stderr, "-c option only accepts integer values "
        "greater or equal to 1\n");
        return (-1);
    }
    for (size_t i = 0; i < split_len(server->teams); ++i)
        server->max_team_cli[i] = nclients;
    return (0);
}
