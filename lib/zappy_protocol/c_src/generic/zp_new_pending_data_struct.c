/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_new_pending_data_struct
*/

#include "c_zappy_protocol.h"

t_zp_pending_data *zp_new_pending_data_struct(int fd)
{
    t_zp_pending_data *zp_pdata = (t_zp_pending_data*)malloc(sizeof(*zp_pdata));

    zp_init_pending_data_struct(zp_pdata, fd);
    return (zp_pdata);
}
