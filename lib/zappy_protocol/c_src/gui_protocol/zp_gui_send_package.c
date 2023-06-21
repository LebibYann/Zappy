/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_gui_send_package
*/

#include "c_zappy_protocol_gui.h"

bool zp_gui_send_package(t_zp_pending_data *pdata, enum e_sender sender,
enum e_zp_command cmd_type, ...)
{
    bool out;
    va_list args;

    va_start(args, cmd_type);
    out = zp_gui_send_package_varg(pdata, sender, cmd_type, &args);
    va_end(args);
    return (out);
}
