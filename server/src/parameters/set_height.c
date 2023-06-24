/*
** EPITECH PROJECT, 2023
** set_height
** File description:
** The function setups the height of the server.
*/

#include "zappy_server.h"

int set_height(server_t *server, int *index, int ac, char **av)
{
    if (*index >= ac){
        fprintf(stderr,  "./server: option requires an argument -- '%s'\n", "-y");
        return (-1);
    }
    server->map.h = atoi(av[*index]);
    if (server->map.h < 10 || server->map.h > 30){
        fprintf(stderr, "-x option only accepts integer values between 10 and 30\n");
        return (-1);
    }
    *index = *index + 1;
    return (0);
}
