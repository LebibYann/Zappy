/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_receive_package
*/

#include "c_zappy_protocol_gui.h"

static char *modular_getline(t_zp_pending_data *pdata, bool wait)
{
    if (wait)
        return (zp_getline_wait_pending_data(pdata));
    return (zp_getline_pending_data(pdata));
}

int zp_gui_receive_package(t_zp_pending_data *pdata, t_zp_gui_protocol *pkg,
enum e_sender expected_sender, bool wait)
{
    int result = 0;
    char *cmd_line;
    const t_zp_gui_pair *pair;

    if ((cmd_line = modular_getline(pdata, wait)) == NULL)
        return (-1);
    printf("GUI RECEIVED COMMAND: %s\n", cmd_line);
    if ((pair = zp_gui_find_command(cmd_line)) == NULL) {
        free(cmd_line);
        return (-2);
    }
    result = pair->gui_parser_func(cmd_line, pkg);
    free(cmd_line);
    if (result < 0 || pair->nbr_param[expected_sender] == -1 ||
    pair->nbr_param[expected_sender] > pkg->nbr_args) {
        zp_gui_clear_protocol_struct(pkg);
        return (-3);
    }
    pkg->cmd_type = pair->cmd_type;
    return (0);
}
