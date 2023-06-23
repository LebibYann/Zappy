/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_default_parser
*/

#include "c_zappy_protocol_gui.h"

static bool str_is_int(const char *str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len && str[i] != '\n'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            printf("ha %c\n", str[i]);
            return (false);
        }
    }
    return (true);
}

static bool add_param(t_zp_gui_protocol *pkg, char *param)
{
    if (!str_is_int(param)) {
        free(pkg->args);
        pkg->args = NULL;
        pkg->nbr_args = 0;
        return (false);
    }
    pkg->args = (int*) realloc(pkg->args, (pkg->nbr_args + 1) * sizeof(int));
    pkg->args[pkg->nbr_args] = atoi(param);
    ++(pkg->nbr_args);
    return (true);
}

int zp_gui_default_parser(char *cmd_line, t_zp_gui_protocol *pkg)
{
    char *param = strtok(cmd_line, " ");

    if (param == NULL)
        return (-1);
    zp_gui_clear_protocol_struct(pkg);
    while ((param = strtok(NULL, " ")) != NULL) {
        if (!add_param(pkg, param))
            return (-1);
    }
    return (0);
}
