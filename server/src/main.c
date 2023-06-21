/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** main
*/

#include "zappy_server.h"

int main(int ac, char **av)
{
    bool run = true;
    server_t server;
    struct timespec timing;

    init_server(&server);
    if (read_parameters(&server, ac, av) == -1)
        return (84);
    if ((server.fd = open_server(server.port, 5)) < 0)
        return (84);
    // FD_SET(server.fd, &server.current_sockets);
    while (run) {
        clock_start(&timing);
        // run = handle_client(&server);
        clock_delay(&timing, server.frequency);
        printf("Hey!\n");
    }
    close(server.fd);
    return (0);
}
