/*
** EPITECH PROJECT, 2023
** ai
** File description:
** paramMachine
*/

#include "ZappyAIParam.hpp"

int paramMachine(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass)
{
    if (argPos + 1 >= argvList.size()) {
        std::cerr << "Missing machine after \"" << argvList[argPos] << "\"." << std::endl;
        return (INIT_KO);
    }
    targetClass.setMachine(argvList[++argPos]);
    return (INIT_OK);
}
