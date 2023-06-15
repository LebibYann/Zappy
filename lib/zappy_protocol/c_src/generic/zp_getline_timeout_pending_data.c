/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_getline_pending_data
*/

#include "c_zappy_protocol.h"

static size_t get_ms(const struct timeval *time_data)
{
    return (time_data->tv_sec * 1000 + time_data->tv_usec / 1000);
}

char *zp_getline_timeout_pending_data(t_zp_pending_data *zp_pending_d,
int timeout_ms, fd_set rd_socket)
{
    struct pollfd fds = {zp_pending_d->fd,
        POLLIN | POLLERR | POLLHUP | POLLNVAL, 0};
    char *data = getline_in_custom_fd(&(zp_pending_d->c_rfd));
    struct timeval tmp_time;
    int start_time_ms = 0;
    int computed_timeout = timeout_ms;

    while (data == NULL && (computed_timeout > 0 || timeout_ms < 0)) {
        poll(&fds, 1, computed_timeout);
        zp_exchange_data(zp_pending_d, &rd_socket, NULL);
        if (zp_pending_d->disconnected)
            return (data);
        data = getline_in_custom_fd(&(zp_pending_d->c_rfd));
        gettimeofday(&tmp_time, NULL);
        computed_timeout = start_time_ms + timeout_ms - get_ms(&tmp_time);
    }
    return (data);
}
