/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** c_zappy_protocol
*/

#pragma once

#include <time.h>
#include <sys/time.h>
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdlib.h>

#include "zappy_struct.h"
#include "c_zappy_protocol_gui.h"

/**
 ** @brief Fills c_rfd member of t_zp_pending_data
 ** (if there's something to read in the fd) and
 ** empty c_wfd member of t_zp_pending_data and send it's data
 ** to in the fd.
 **
 ** @param zp_pending_d
 ** @param rd_socket An fd_set or NULL to disable read at this call.
 ** @param wr_socket An fd_set or NULL to disable write at this call.
 ** @return ssize_t 0 on success,
 ** 1 if a disconnection is detected and -1 if it fails.
 */
extern "C"
ssize_t zp_exchange_data(t_zp_pending_data *zp_pending_d,
enum e_zp_exchangeDataHandling rcv_handling,
enum e_zp_exchangeDataHandling snd_handling);

/**
 ** @brief Writes in c_wfd member of t_zp_pending_data.
 ** NOTE: If you want to send the data to the fd use zp_exchange_data().
 **
 ** @param zp_pending_d
 ** @param data
 ** @param size
 ** @return size_t The size written
 */
extern "C"
size_t zp_write_data(
    t_zp_pending_data *zp_pending_d, const void *data, size_t size);

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
extern "C"
size_t zp_read_data(t_zp_pending_data *zp_pending_d, void *data, size_t size);

/**
 ** @brief Detect if a new connection is pending
 **
 ** @param socket_fd
 ** @return true if there's a new connection false otherwise
 */
extern "C"
bool zp_detect_new_connection(int socket_fd);

extern "C"
void zp_init_pending_data_struct(t_zp_pending_data *zp_pending_d, int fd);

extern "C"
void zp_clear_pending_data_struct(t_zp_pending_data *zp_pending_d);

extern "C"
t_zp_pending_data *zp_new_pending_data_struct(int fd);

extern "C"
void zp_delete_pending_data_struct(t_zp_pending_data *zp_pdata);

extern "C"
char *zp_getline_pending_data(t_zp_pending_data *zp_pending_d);

extern "C"
char *zp_getline_wait_pending_data(t_zp_pending_data *zp_pending_d);


extern "C"
ssize_t rw_action(t_zp_pending_data *zp_pending_d,
bool *something_to_read, fd_set **sock_ptr);
