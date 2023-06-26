/*
** EPITECH PROJECT, 2023
** init_server
** File description:
** The file initialize the server values.
*/

#include "zappy_server.h"

void init_server(server_t *server)
{
    char *base_team_list[] = {"Team1", "Team2", "Team3", "Team4", NULL};

    server->port = 4242;
    initialize_map(&server->map, 10, 10);
    server->teams = split_dup(base_team_list);
    server->max_team_cli = malloc(sizeof(int) * split_len(server->teams));
    for (size_t i = 0; i < split_len(server->teams); ++i)
        server->max_team_cli[i] = 3;
    server->frequency = 100;
    memset(server->resource_count, 0, sizeof(int) * 7);
    LIST_INIT(&(server->client_list));
}
