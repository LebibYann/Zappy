/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_exchange_data
*/

#include "c_zappy_protocol.h"

static ssize_t read_action(t_zp_pending_data *zp_pending_d)
{
    char buf[BUFSIZE];
    ssize_t bytes = read(zp_pending_d->fd, buf, BUFSIZE);

    switch (bytes) {
        case -1:
            return (-1);
        case 0:
            zp_pending_d->disconnected = true;
            return (0);
    }
    write_in_custom_fd(&(zp_pending_d->c_rfd), buf, bytes);
    return (bytes);
}

static ssize_t write_action(t_zp_pending_data *zp_pending_d)
{
    char buf[BUFSIZE];
    ssize_t buf_size = read_in_custom_fd(&(zp_pending_d->c_wfd), buf, BUFSIZE);

    return (write(zp_pending_d->fd, buf, buf_size));
}

static ssize_t rw_action(t_zp_pending_data *zp_pending_d,
fd_set rd_socket, fd_set wr_socket, bool *something_to_read)
{
    if (FD_ISSET(zp_pending_d->fd, &rd_socket)) {
        (*something_to_read) = true;
        switch (read_action(zp_pending_d)) {
            case -1:
                return (-1);
            case 0:
                return (1);
        }
    }
    if (FD_ISSET(zp_pending_d->fd, &wr_socket)) {
        if (write_action(zp_pending_d))
            return (-1);
    }
    return (0);
}

ssize_t zp_exchange_data(t_zp_pending_data *zp_pending_d,
fd_set rd_socket, fd_set wr_socket)
{
    bool can_read = true;
    fd_set tmp_rd_sock;
    fd_set tmp_wr_sock;

    while (!zp_pending_d->disconnected &&
    (zp_pending_d->c_wfd.size > 0 || can_read)) {
        can_read = false;
        tmp_rd_sock = rd_socket;
        tmp_wr_sock = wr_socket;
        if (select(FD_SETSIZE, &tmp_rd_sock, &tmp_wr_sock, NULL, NULL) < 0)
            return (-1);
        switch (rw_action(zp_pending_d, tmp_rd_sock, tmp_wr_sock, &can_read)) {
            case -1:
                return (-1);
            case 1:
                return (1);
        }
    }
    return (0);
}
