/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** player_info
*/

#include "zappy_server.h"

void player_info(server_t *server, client_t *client)
{
    client_t *gui;

    LIST_FOREACH(gui, &server->client_list, other_clients) {
        if (gui->category == CATEGORY_GUI)
            zp_gui_send_package(&gui->data, SERVER_SENT,
            ZP_PNW, client->fd, client->pos.x, client->pos.y,
            client->orientation, client->level, client->team);
    }
}
