/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_global
*/

#include "c_zappy_protocol_server_ai.h"

const aiCommand_t AI_CLI_COMMANDS[ZP_TOTAL_AI_CMD] =
{
    {ZP_FORWARD, "Forward", 7},
    {ZP_RIGHT, "Right", 7},
    {ZP_LEFT, "Left", 7},
    {ZP_LOOK, "Look", 7},
    {ZP_INVENTORY, "Inventory", 1},
    {ZP_BROADCAST, "Broadcast", 7},
    {ZP_CONNECT_NBR, "Connect_nbr", 0},
    {ZP_FORK, "Fork", 42},
    {ZP_EJECT, "Eject", 7},
    {ZP_DEAD, "", 0},
    {ZP_TAKE_OBJ, "Take", 7},
    {ZP_SET_OBJ, "Set", 7},
    {ZP_INCANTATION, "Incantation", 0}
};
