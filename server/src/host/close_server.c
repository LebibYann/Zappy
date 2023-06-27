/*
** EPITECH PROJECT, 2023
** server
** File description:
** close_server
*/

#include "zappy_server.h"

void close_server(server_t *server)
{
    close(server->fd);
    remove_all_clients(&(server->client_list));
    split_free(server->teams);
    free(server->max_team_cli);
    zp_clear_pending_data_struct(&(server->gui_update_data));
}
