/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_global
*/

#include "c_zappy_protocol_server_ai.h"

const aiCommand_t AI_CLI_COMMANDS[ZP_TOTAL_AI_CMD] =
{
    {ZP_FORWARD, "Forward"},
    {ZP_RIGHT, "Right"},
    {ZP_LEFT, "Left"},
    {ZP_LOOK, "Look"},
    {ZP_INVENTORY, "Inventory"},
    {ZP_BROADCAST, "Broadcast"},
    {ZP_CONNECT_NBR, "Connect_nbr"},
    {ZP_FORK, "Fork"},
    {ZP_EJECT, "Eject"},
    {ZP_DEAD, ""},
    {ZP_TAKE_OBJ, "Take"},
    {ZP_SET_OBJ, "Set"},
    {ZP_INCANTATION, "Incantation"}
};
