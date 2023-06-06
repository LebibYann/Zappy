/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_read_data
*/

#include "c_zappy_protocol.h"

size_t zp_read_data(t_zp_pending_data *zp_pending_d, void *data, size_t size)
{
    return (read_in_custom_fd(&(zp_pending_d->c_wfd), data, size));
}
