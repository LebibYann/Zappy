/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_server
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

typedef struct server_s{
    int fd;
    fd_set read_sockets;
    fd_set write_sockets;
} server_t;

int create_server(int port, int queue);
bool handle_client(server_t *server);
int handle_connexion(server_t *server);
