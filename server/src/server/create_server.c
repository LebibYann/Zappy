/*
** EPITECH PROJECT, 2023
** setup_server
** File description:
** The file contains the function setup server who launch a tcp
** server for the indicate port in paramters
*/

#include "zappy_server.h"

int create_server(int port, int queue)
{
    int server_socket;
    struct sockaddr_in server_addr;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (-1);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_socket, ((struct sockaddr*)&server_addr)
    , sizeof(server_addr)) < 0){
        close(server_socket);
        return (-1);
    }
    if (listen(server_socket, queue) < 0){
        close(server_socket);
        return (-1);
    }
    return (server_socket);
}
