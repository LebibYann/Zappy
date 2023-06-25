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

    init_server(&server);
    if (read_parameters(&server, ac, av) == -1)
        return (84);
    initialize_map(&server.map, 10, 10);
    allocate_map(&server.map);
    generate_map(&server);
    if ((server.fd = open_server(server.port, 5)) < 0)
        return (84);
    run_server(&server);
    close_server(&server);
    return (0);
}
