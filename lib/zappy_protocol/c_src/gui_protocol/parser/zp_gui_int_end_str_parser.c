/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_int_end_str_parser
*/

#include "c_zappy_protocol_gui.h"

static bool str_is_int(const char *str)
{
    size_t len = strlen(str);
    size_t i = 0;

    for (; i < len && (str[i] == '-' || str[i] == '+'); ++i);
    if (i >= len)
        return (false);
    for (; i < len; ++i) {
        if (('0' < str[i] || '9' > str[i]))
            return (false);
    }
    return (true);
}

static bool add_param(t_zp_gui_protocol *pkg, char *param)
{
    if (!str_is_int(param)) {
        free(pkg->args);
        free(param);
        pkg->args = NULL;
        pkg->nbr_args = 0;
        return (false);
    }
    pkg->args = (int*) realloc(pkg->args, (pkg->nbr_args + 1) * sizeof(int));
    pkg->args[pkg->nbr_args] = atoi(param);
    ++(pkg->nbr_args);
    return (true);
}

static bool pick_conversion(t_zp_gui_protocol *pkg,
char *param, char *next_param)
{
    if (next_param != NULL) {
        if (!add_param(pkg, param)) {
            free(next_param);
            return (-1);
        }
        free(param);
    } else {
        pkg->str = param;
    }
    return (0);
}

int zp_gui_int_end_str_parser(char *cmd_line, t_zp_gui_protocol *pkg)
{
    char *next_param;
    char *param = strtok(cmd_line, " ");

    if (param == NULL)
        return (-1);
    free(param);
    zp_gui_clear_protocol_struct(pkg);
    param = strtok(NULL, " ");
    while (param != NULL) {
        next_param = strtok(NULL, " ");
        if (pick_conversion(pkg, param, next_param))
            return (-1);
        param = next_param;
    }
    return (0);
}
