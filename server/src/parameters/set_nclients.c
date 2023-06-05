/*
** EPITECH PROJECT, 2023
** set_nclients
** File description:
** The function setups the nclients of the server.
*/

#include "zappy_server.h"

int set_nclients(server_t *server, int *index, int ac, char **av)
{
    if (*index >= ac){
        fprintf(stderr,  "./server: option requires an argument -- '%s'\n", "-f");
        return (-1);
    }
    server->nclients = atoi(av[*index]);
    if (server->nclients < 1){
        fprintf(stderr, "-x option only accepts integer values greater or equal to 1\n");
        return (-1);
    }
    *index = *index + 1;
    return (0);
}