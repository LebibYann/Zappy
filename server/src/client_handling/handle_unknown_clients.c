/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_unknown_clients
*/

#include "zappy_server.h"

static void send_gui_init(server_t *server, client_t *client)
{
    t_zp_pending_data *pdata = &(client->data);

    zp_gui_send_package(pdata, SERVER_SENT, ZP_MSZ, 0, 0);
    zp_gui_send_package(pdata, SERVER_SENT, ZP_SGT, server->frequency);
    for (size_t y = 0; y < 4; ++y) {
        for (size_t x = 0; x < 4; ++x) {
            zp_gui_send_package(pdata, SERVER_SENT,
                ZP_BCT, x, y, 0, 0, 0, 0, 0, 0);
        }
    }
    for (size_t i = 0; server->teams[i] != NULL; ++i)
        zp_gui_send_package(pdata, SERVER_SENT, ZP_TNA, server->teams[i]);
}

void handle_unknown_clients(server_t *server, client_t *client)
{
    char *line;
    (void)server;

    zp_exchange_data(&(client->data), HANDLE_NO_WAIT, HANDLE_IGNORE);
    if ((line = zp_getline_pending_data(&(client->data))) == NULL)
        return;
    printf("%s\n", line);
    if (strcmp(line, "GRAPHIC\n") == 0) {
        printf("It's a graphic client !\n");
        configure_client_as_gui(client);
        free(line);
        send_gui_init(server, client);
        return;
    }
    printf("Maybe an AI\n");
    free(line);
}
