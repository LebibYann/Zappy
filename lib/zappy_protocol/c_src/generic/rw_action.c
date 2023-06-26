/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** rw_action
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

ssize_t rw_action(t_zp_pending_data *zp_pending_d,
bool *something_to_read, fd_set **sock_ptr)
{
    (*something_to_read) = false;
    if (sock_ptr[0] != NULL && FD_ISSET(zp_pending_d->fd, sock_ptr[0])) {
        (*something_to_read) = true;
        switch (read_action(zp_pending_d)) {
            case -1:
                return (-3);
            case 0:
                return (-1);
        }
    }
    if (sock_ptr[1] != NULL && FD_ISSET(zp_pending_d->fd, sock_ptr[1])) {
        if (write_action(zp_pending_d) < 0)
            return (-3);
    }
    return (0);
}
