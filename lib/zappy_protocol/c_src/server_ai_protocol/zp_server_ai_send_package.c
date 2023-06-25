/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_server_ai_send_package
*/

#include "c_zappy_protocol_server_ai.h"

void zp_server_ai_send_package(t_zp_pending_data *zp_pending_d, char *response)
{
    zp_write_data(zp_pending_d, response, strlen(response));
    zp_exchange_data(zp_pending_d, HANDLE_IGNORE, HANDLE_NO_WAIT);
}
