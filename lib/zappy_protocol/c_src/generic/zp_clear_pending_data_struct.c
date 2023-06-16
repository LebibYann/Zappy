/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_init_pending_data_struct
*/

#include "c_zappy_protocol.h"

void zp_clear_pending_data_struct(t_zp_pending_data *zp_pending_d)
{
    zp_pending_d->fd = 0;
    zp_pending_d->disconnected = 0;
    clear_custom_fd(&(zp_pending_d->c_rfd));
    clear_custom_fd(&(zp_pending_d->c_wfd));
}
