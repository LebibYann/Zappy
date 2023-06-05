/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** c_zappy_protocol
*/

#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "zappy_struct.h"

ssize_t zp_send_data(int fd, fd_set write_sockets, void *data, ssize_t size);
