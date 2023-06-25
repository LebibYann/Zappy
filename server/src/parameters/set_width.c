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
        fprintf(stderr, "./server: option requires an argument -- '-x'\n");
        return (-1);
    }
    server->map.w = atoi(av[*index]);
    if (server->map.w < 10 || server->map.w > 30){
        fprintf(stderr, "-x option only accepts integer "
        "values between 10 and 30\n");
        return (-1);
    }
    return (0);
}
