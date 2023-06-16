/*
** EPITECH PROJECT, 2023
** set_width
** File description:
** The function setups the width of the server.
*/

#include "zappy_server.h"

int set_width(server_t *server, int *index, int ac, char **av)
{
    if (*index >= ac){
        fprintf(stderr,  "./server: option requires an argument -- '%s'\n", "-x");
        return (-1);
    }
    server->width = atoi(av[*index]);
    if (server->width < 10 || server->width > 30){
        fprintf(stderr, "-x option only accepts integer values between 10 and 30\n");
        return (-1);
    }
    *index = *index + 1;
    return (0);
}