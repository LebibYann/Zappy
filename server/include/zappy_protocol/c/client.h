/*
** EPITECH PROJECT, 2023
** server
** File description:
** The header contains the server structure
*/

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

typedef struct client_s{
    int server_fd;
    fd_set read_sockets;
    fd_set write_sockets;
} client_t;


#ifdef __cplusplus
extern "C" {
#endif

int handle_connexion(char *addr, int port);

int create_client(const char *ip_adress, int port);

void run_client(client_t *client);

#ifdef __cplusplus
}
#endif
