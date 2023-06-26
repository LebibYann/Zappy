/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_gui_out_command
*/

#include "zappy_client_handling.h"

void handle_gui_out_command(server_t *server)
{
    char *str;
    client_t *gui;

    while ((str = getline_in_custom_fd(&(server->gui_update_data.c_wfd)))) {
        LIST_FOREACH(gui, &server->client_list, other_clients) {
            if (gui->category == CATEGORY_GUI) {
                zp_write_data(&(gui->data), str, strlen(str));
                zp_exchange_data(&(gui->data), HANDLE_IGNORE, HANDLE_NO_WAIT);
            }
        }
    }
}
