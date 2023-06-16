/*
** EPITECH PROJECT, 2023
** ai
** File description:
** paramName
*/

#include "ZappyAIParam.hpp"

int paramName(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass)
{
    if (argPos + 1 >= argvList.size()) {
        std::cerr << "Missing team name after \"" << argvList[argPos] << "\"." << std::endl;
        return (INIT_KO);
    }
    targetClass.setName(argvList[++argPos]);
    return (INIT_OK);
}
