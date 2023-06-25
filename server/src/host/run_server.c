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

static void refresh_map(server_t *server, struct timespec *time)
{
    static struct timespec now;
    double elapsed_time;

    timespec_get(&now, TIME_UTC);
    elapsed_time = (now.tv_sec - time->tv_sec)
        + (now.tv_nsec - time->tv_nsec) / 1e9;

    if (elapsed_time >= (20 / server->frequency)) {
        generate_map(server);
        *time = now;
    }
}

void run_server(server_t *server)
{
    struct timespec time;
    server->run = true;
    server_cpy_addr = server;
    signal(SIGINT, signal_handler);

    timespec_get(&time, TIME_UTC);
    while (server->run) {
        while (zp_detect_new_connection(server->fd))
            add_new_client(server);
        handle_clients(server);
        refresh_map(server, &time);
        complete_ai_incantation(server);
        food_time_ai(server);
        remove_disconnected_client(&(server->client_list));
    }
}
