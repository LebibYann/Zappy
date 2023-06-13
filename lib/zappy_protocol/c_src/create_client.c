/*
** EPITECH PROJECT, 2023
** create_client
** File description:
** The file contains the function which create the client
*/

#include "client.h"

int create_client(const char *ip_adress, int port)
{
    int client_socket;
    struct sockaddr_in server_addr;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (-1);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_adress);
    server_addr.sin_port = htons(port);
    if (connect(client_socket, ((struct sockaddr*)&server_addr)
    , sizeof(server_addr)) < 0){
        close(client_socket);
        return (-1);
    }
    return (client_socket);
}
