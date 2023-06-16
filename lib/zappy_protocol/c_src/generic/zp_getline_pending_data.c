/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_getline_pending_data
*/

#include "c_zappy_protocol.h"

char *zp_getline_pending_data(t_zp_pending_data *zp_pending_d)
{
    return (getline_in_custom_fd(&(zp_pending_d->c_rfd)));
}
