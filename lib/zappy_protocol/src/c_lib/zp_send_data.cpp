/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_send_data
*/

#include "c_zappy_protocol.h"

ssize_t zp_send_data(int fd, fd_set write_sockets, void *data, ssize_t size)
{
    char *buf = ((char*) data);
    fd_set tmp_write_sockets;
    ssize_t i = 0;
    ssize_t bytes;
    ssize_t size_cpy = size;
    ssize_t byte_to_write;

    while (size > 0) {
        tmp_write_sockets = write_sockets;
        if (select(FD_SETSIZE, NULL, &tmp_write_sockets, NULL, NULL) < 0)
            return (-1);
        if (FD_ISSET(fd, &tmp_write_sockets)) {
            byte_to_write = (size > BUF_SIZE) ? BUF_SIZE : size;
            bytes = write(fd, &buf[i * BUF_SIZE], byte_to_write);
            if (bytes < 0)
                return (-1);
            size -= bytes;
            ++i;
        }
    }
    return (size_cpy);
}
