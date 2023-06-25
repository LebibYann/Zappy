/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** explusion
*/

#include <zappy_server.h>

void expulsion(server_t *server, const char *team)
{
    client_t *client;

    LIST_FOREACH(client, &server->client_list, other_clients){
        if (client->category == CATEGORY_GUI){
            zp_gui_send_package(&client->data, SERVER_SENT,
            ZP_PEX, team);
        }
}
