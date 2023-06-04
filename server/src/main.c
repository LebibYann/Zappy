/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** main
*/

#include "zappy_server.h"

int main(int ac, char **av)
{
    server_t server;

    if (ac < 2)
        return (84);
    server.fd = create_server(atoi(av[1]), 5);
    FD_ZERO(&server.current_sockets);
    FD_SET(server.fd, &server.current_sockets);
    while (handle_client(&server));
    close(server.fd);
    return (0);
}
