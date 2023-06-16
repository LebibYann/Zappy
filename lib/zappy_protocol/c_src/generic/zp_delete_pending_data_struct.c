/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_delete_pending_data_struct
*/

#include "c_zappy_protocol.h"

void zp_delete_pending_data_struct(t_zp_pending_data *zp_pdata)
{
    zp_clear_pending_data_struct(zp_pdata);
    free(zp_pdata);
}
