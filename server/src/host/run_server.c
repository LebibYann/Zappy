/*
** EPITECH PROJECT, 2023
** server
** File description:
** run_server
*/

#include "zappy_server.h"

const server_t *server_cpy_addr;

static void signal_handler(int signl_num)
{
    server_t *server = (server_t*) server_cpy_addr;

    (void)signl_num;
    server->run = false;
    return;
}

void run_server(server_t *server)
{
    server->run = true;
    server_cpy_addr = server;
    signal(SIGINT, signal_handler);

    while (server->run) {
        while (zp_detect_new_connection(server->fd))
            add_new_client(server);
        handle_clients(server);
        complete_ai_incantation(server);
        food_time_ai(server);
        remove_disconnected_client(&(server->client_list));
    }
}
