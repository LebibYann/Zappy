/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_init_protocol_struct
*/

#include "c_zappy_protocol_gui.h"

void zp_gui_clear_protocol_struct(t_zp_gui_protocol *gui_protocol)
{
    gui_protocol->cmd_type = ZP_END;
    gui_protocol->nbr_args = 0;
    if (gui_protocol->args != NULL)
        free(gui_protocol->args);
    gui_protocol->args = NULL;
    if (gui_protocol->str != NULL)
        free(gui_protocol->str);
    gui_protocol->str = NULL;
}
