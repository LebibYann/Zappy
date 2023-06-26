/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** send_tile
*/

#include "zappy_server.h"

void send_tile(t_zp_pending_data *pdata, int x, int y, int *items)
{
    zp_gui_send_package(pdata, SERVER_SENT, ZP_BCT, x, y,
        items[FOOD], items[LINEMATE], items[DERAUMERE], items[SIBUR],
        items[MENDIANE], items[PHIRAS], items[THYSTAME]);
}
