/*
** EPITECH PROJECT, 2023
** open_server
** File description:
** The file contains the function setup server which launch a tcp
** server for the indicate port in paramters
*/

#include "zappy_server.h"

static void setup_serv_addr(struct sockaddr_in *addr, int port)
{
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
}

int open_server(int port, int queue)
{
    int server_socket;
    struct sockaddr_in server_addr;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (-1);
    setup_serv_addr(&server_addr, port);
    if (bind(server_socket, ((struct sockaddr*)&server_addr)
    , sizeof(server_addr)) < 0){
        close(server_socket);
        perror("bind");
        return (-1);
    }
    if (listen(server_socket, queue) < 0){
        close(server_socket);
        perror("listen");
        return (-1);
    }
    printf("PORT: %d\n", port);
    return (server_socket);
}
