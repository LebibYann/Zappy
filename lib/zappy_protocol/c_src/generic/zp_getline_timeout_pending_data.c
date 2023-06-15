/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_getline_pending_data
*/

#include "c_zappy_protocol.h"

static size_t get_milliseconds(const struct timeval *time_data)
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
    int start_time_ms;
    int computed_timeout;

    gettimeofday(&tmp_time, NULL);
    start_time_ms = get_milliseconds(&tmp_time);
    computed_timeout = timeout_ms;
    while (data == NULL && computed_timeout > 0) {
        poll(&fds, 1, computed_timeout);
        zp_exchange_data(zp_pending_d, &rd_socket, NULL);
        data = getline_in_custom_fd(&(zp_pending_d->c_rfd));
        gettimeofday(&tmp_time, NULL);
        computed_timeout = start_time_ms + timeout_ms -
            get_milliseconds(&tmp_time);
    }
    return (data);
}
