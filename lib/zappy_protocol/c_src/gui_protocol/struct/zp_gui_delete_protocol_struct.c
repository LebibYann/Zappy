/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_delete_protocol_struct
*/

#include "c_zappy_protocol_gui.h"

void zp_gui_delete_protocol_struct(t_zp_gui_protocol *gui_protocol)
{
    zp_gui_clear_protocol_struct(gui_protocol);
    free(gui_protocol);
}
