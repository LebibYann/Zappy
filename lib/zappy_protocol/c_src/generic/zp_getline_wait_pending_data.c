/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_getline_pending_data
*/

#include "c_zappy_protocol.h"

// static size_t get_ms(const struct timeval *time_data)
// {
//     return (time_data->tv_sec * 1000 + time_data->tv_usec / 1000);
// }

char *zp_getline_wait_pending_data(t_zp_pending_data *zp_pending_d)
{
    int out;
    char *data = getline_in_custom_fd(&(zp_pending_d->c_rfd));

    while (data == NULL) {
        out = zp_exchange_data(zp_pending_d, HANDLE_WAIT, HANDLE_IGNORE);
        if (out < 0)
            return (data);
        data = getline_in_custom_fd(&(zp_pending_d->c_rfd));
    }
    return (data);
}
