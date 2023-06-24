/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_client_handling
*/

#pragma once

#include <sys/queue.h>

#include "zappy_server_struct.h"
#include "zappy_client.h"

bool add_new_client(server_t *server);
void remove_disconnected_client(struct client_list_s *client_list);
void remove_all_clients(struct client_list_s *client_list);

void handle_clients(server_t *server);
void handle_unknown_clients(server_t *server, client_t *client);
void handle_gui_clients(server_t *server, client_t *client);
void handle_ai_clients(server_t *server, client_t *client);
