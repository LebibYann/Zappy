/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_server_ai_send_basic_package
*/

#include "c_zappy_protocol_server_ai.h"

void zp_server_ai_send_basic_package(t_zp_pending_data *zp_pending_d,
enum AIResponse_e response)
{
    switch (response) {
        case RESPONSE_OK:
            zp_write_data(zp_pending_d, "ok\n", 3);
            break;
        case RESPONSE_KO:
            zp_write_data(zp_pending_d, "ko\n", 3);
            break;
        case RESPONSE_DEAD:
            zp_write_data(zp_pending_d, "dead\n", 5);
            break;
        default:
            break;
    }
    zp_exchange_data(zp_pending_d, HANDLE_IGNORE, HANDLE_NO_WAIT);
}
