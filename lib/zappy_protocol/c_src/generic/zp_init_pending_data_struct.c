/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_init_pending_data_struct
*/

#include "c_zappy_protocol.h"

void zp_init_pending_data_struct(t_zp_pending_data *zp_pending_d, int fd)
{
    zp_pending_d->fd = fd;
    zp_pending_d->disconnected = false;
    init_custom_fd(&(zp_pending_d->c_rfd));
    init_custom_fd(&(zp_pending_d->c_wfd));
}
