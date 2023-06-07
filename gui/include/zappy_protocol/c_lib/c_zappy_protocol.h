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
#include <stdbool.h>
#include <stdlib.h>

#include "zappy_struct.h"

/**
 ** @brief Fills c_rfd member of t_zp_pending_data
 ** (if there's something to read in the fd) and
 ** empty c_wfd member of t_zp_pending_data and send it's data
 ** to in the fd.
 **
 ** @param zp_pending_d
 ** @param rd_socket
 ** @param wr_socket
 ** @return ssize_t 0 on success,
 ** 1 if a disconnection is detected and -1 if it fails.
 */
ssize_t zp_exchange_data(t_zp_pending_data *zp_pending_d,
fd_set rd_socket, fd_set wr_socket);

/**
 ** @brief Writes in c_wfd member of t_zp_pending_data.
 ** NOTE: If you want to send the data to the fd use zp_exchange_data().
 **
 ** @param zp_pending_d
 ** @param data
 ** @param size
 ** @return size_t The size written
 */
size_t zp_write_data(t_zp_pending_data *zp_pending_d, void *data, size_t size);

/**
 ** @brief Reads in c_rfd member of t_zp_pending_data.
 ** NOTE: You should call zp_exchange_data() before using this function,
 ** in order to receive the latest data sent in the fd.
 **
 ** @param zp_pending_d
 ** @param data
 ** @param size
 ** @return size_t
 */
size_t zp_read_data(t_zp_pending_data *zp_pending_d, void *data, size_t size);

void zp_init_pending_data_struct(t_zp_pending_data *zp_pending_d, int fd);

void zp_clear_pending_data_struct(t_zp_pending_data *zp_pending_d);
