/*
** EPITECH PROJECT, 2023
** handle_connection
** File description:
** The file contains the function handle_connexion.
*/

#include "client.h"

int handle_connexion(char *addr, int port)
{
    int server_socket;
    struct sockaddr_in serv_addr;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (-1);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, addr, &(serv_addr.sin_addr)) < 0)
        return (-1);
    if (connect(server_socket,
    (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        return (-1);
    return (server_socket);
}
