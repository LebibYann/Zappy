/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_exchange_data
*/

#include "c_zappy_protocol.h"


static int check_connection(t_zp_pending_data *zp_pending_d,
fd_set *socks)
{
    struct pollfd connectionCheck = {zp_pending_d->fd, 0, 0};
    int result = poll(&connectionCheck, 1, 0);

    if (connectionCheck.revents & POLLHUP || zp_pending_d->disconnected) {
        zp_pending_d->disconnected = true;
        return (-1);
    }
    if (result < 0 || connectionCheck.revents & POLLERR)
        return (-3);
    if (connectionCheck.revents & POLLNVAL)
        return (-2);
    FD_ZERO(&socks[0]);
    FD_ZERO(&socks[1]);
    FD_SET(zp_pending_d->fd, &socks[0]);
    FD_SET(zp_pending_d->fd, &socks[1]);
    return (0);
}

static ssize_t do_select(t_zp_pending_data *zp_pending_d, fd_set **sock_ptr,
enum e_zp_exchangeDataHandling rcv_handling)
{
    ssize_t out;
    bool can_read = (rcv_handling != HANDLE_IGNORE);
    struct pollfd fds = {zp_pending_d->fd, POLLIN | POLLPRI | POLLOUT, 0};
    struct timespec timeout = {0, 1};

    while (can_read || (zp_pending_d->c_wfd.size > 0 && sock_ptr[1] != NULL)) {
        if (select(FD_SETSIZE, sock_ptr[0], sock_ptr[1], NULL, NULL) < 0)
            return (-3);
        if ((out = rw_action(zp_pending_d, &can_read, sock_ptr)) < 0)
            return (out);
        ppoll(&fds, 1, &timeout, NULL);
        can_read = ((fds.revents & POLLIN) && rcv_handling != HANDLE_IGNORE);
    }
    return (0);
}

ssize_t zp_exchange_data(t_zp_pending_data *zp_pending_d,
enum e_zp_exchangeDataHandling rcv_handling,
enum e_zp_exchangeDataHandling snd_handling)
{
    struct pollfd fds = {zp_pending_d->fd, POLLIN | POLLPRI | POLLOUT, 0};
    struct timespec timeout = {0, 1};
    fd_set socks[2];
    fd_set *sock_ptr[2] = {NULL, NULL};
    int out = check_connection(zp_pending_d, socks);

    if (out < 0)
        return (out);
    ppoll(&fds, 1, &timeout, NULL);
    if (rcv_handling == HANDLE_WAIT ||
    (rcv_handling == HANDLE_NO_WAIT && fds.revents & POLLIN))
        sock_ptr[0] = &socks[0];
    if (snd_handling == HANDLE_WAIT ||
    (snd_handling == HANDLE_NO_WAIT && fds.revents & POLLOUT))
        sock_ptr[1] = &socks[1];
    if (sock_ptr[0] == NULL && sock_ptr[1] == NULL)
        return (0);
    return (do_select(zp_pending_d, sock_ptr, rcv_handling));
}
