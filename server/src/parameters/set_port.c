/*
** EPITECH PROJECT, 2023
** set_port
** File description:
** The function setups the port of the server.
*/

#include "zappy_server.h"

int set_port(server_t *server, int *index, int ac, char **av)
{
    if (*index >= ac){
        fprintf(stderr,  "./server: option requires an argument -- '%s'\n", "-p");
        return (-1);
    }
    for (size_t i = 0; av[*index][i] != '\0'; i++){
        if (!isdigit(av[*index][i])) {
            fprintf(stderr, "-p option only accepts valid ports\n");
            return (-1);
        }
    }
    server->port = atoi(av[*index]);
    *index = *index + 1;
    return (0);
}
