/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_detect_new_connection
*/

#include "c_zappy_protocol.h"

bool zp_detect_new_connection(int socket_fd)
{
    struct pollfd fds = {socket_fd, POLLIN, 0};
    struct timespec poll_timeout = {0, 1};
    struct timeval timeout = {0, 1};
    fd_set sock;

    ppoll(&fds, 1, &poll_timeout, NULL);
    if (!(fds.revents & POLLIN))
        return (false);
    FD_ZERO(&sock);
    FD_SET(socket_fd, &sock);
    select(FD_SETSIZE, &sock, NULL, NULL, &timeout);
    return (FD_ISSET(socket_fd, &sock));
}
