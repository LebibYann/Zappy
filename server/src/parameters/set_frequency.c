/*
** EPITECH PROJECT, 2023
** set_frequency
** File description:
** The function setups the frequency of the server.
*/

#include "zappy_server.h"

int set_frequency(server_t *server, int *index, int ac, char **av)
{
    if (*index >= ac){
        fprintf(stderr,  "./server: option requires an argument -- '%s'\n", "-f");
        return (-1);
    }
    server->frequency = atoi(av[*index]);
    if (server->frequency < 2 || server->frequency > 10000){
        fprintf(stderr, "-f option only accepts integer values between 2 and 10000\n");
        return (-1);
    }
    *index = *index + 1;
    return (0);
}
