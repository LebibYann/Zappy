/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** player_level
*/

#include "zappy_server.h"

void player_level(server_t *server, client_t *client, int id)
{
    client_t *ai;

    LIST_FOREACH(ai, &server->client_list, other_clients) {
        if (ai->fd == id)
            zp_gui_send_package(&client->data, SERVER_SENT,
            ZP_PLV, id, ai->level);
    }
}
