/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_server_ai_init_protocol_struct
*/

#include "c_zappy_protocol_server_ai.h"

void zp_server_ai_init_protocol_struct(t_zp_ai_to_serv_data *zp_ais_data)
{
    zp_ais_data->cmd_type = ZP_END;
    zp_ais_data->str = NULL;
}
