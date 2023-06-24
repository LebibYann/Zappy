/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_server_ai_new_protocol_struct
*/

#include "c_zappy_protocol_server_ai.h"

t_zp_ai_to_serv_data *zp_server_ai_new_protocol_struct(void)
{
    t_zp_ai_to_serv_data *ais_protocol =
        (t_zp_ai_to_serv_data*) malloc(sizeof(*ais_protocol));

    zp_server_ai_init_protocol_struct(ais_protocol);
    return (ais_protocol);
}
