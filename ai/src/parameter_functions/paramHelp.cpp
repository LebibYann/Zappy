/*
** EPITECH PROJECT, 2023
** ai
** File description:
** paramHelp
*/

#include "ZappyAIParam.hpp"

int paramHelp(const std::vector<std::string> &argvList, int argPos, ZappyAI &targetClass)
{
    (void)argvList;
    (void)argPos;
    (void)targetClass;

    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tname\tis the name of the team" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
    return (INIT_HELP);
}
