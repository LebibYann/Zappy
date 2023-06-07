/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_new_protocol_struct
*/

#include "c_zappy_protocol_gui.h"

t_zp_gui_protocol *zp_gui_new_protocol_struct(void)
{
    t_zp_gui_protocol *gui_protocol = malloc(sizeof(*gui_protocol));

    zp_gui_init_protocol_struct(gui_protocol);
    return (gui_protocol);
}
