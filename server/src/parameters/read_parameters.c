/*
** EPITECH PROJECT, 2023
** read_parameters
** File description:
** The function reads the parameters of the program.
*/

#include "zappy_server.h"

const char *HELP =
"USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n\
\tport\tis the port number\n\
\twidth\tis the width of the world\n\
\theight\t is the height of the world\n\
\tnameX\tis the name of the team X\n\
\tclientsNb\tis the number of authorized clients per team\n\
\tfreq\tis the reciprocal of time unit for execution of actions\n";

const parameter_t PARAMETERS[6] = 
{
    {"-p", set_port},
    {"-x", set_width},
    {"-y", set_height},
    {"-n", set_name},
    {"-c", set_nclients},
    {"-f", set_frequency}
};

static int handle_parameter(server_t *server, int *index, int ac, char **av)
{
    if (strcmp(av[*index], "-h") == 0)    
        return (-1);
    for (size_t i = 0; i < 6; i++)
        if (strcmp(av[*index], PARAMETERS[i].parameter) == 0){
            *index = *index + 1;
            return (PARAMETERS[i].f(server, index, ac, av));
        }
    fprintf(stderr, "./server: invalid option -- '%s'\n", av[*index]);
    return (-1);
}

int read_parameters(server_t *server, int ac, char **av)
{
    for (int i = 1; i < ac; i++){
        if (handle_parameter(server, &i, ac, av) == -1){
            fprintf(stderr, HELP);
            return (-1);
        }
    }
    return (0);
}