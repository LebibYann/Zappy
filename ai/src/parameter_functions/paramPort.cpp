/*
** EPITECH PROJECT, 2023
** ai
** File description:
** paramPort
*/

#include "ZappyAIParam.hpp"

int paramPort(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass)
{
    if (argPos + 1 >= argvList.size()) {
        std::cerr << "Missing port after \"" << argvList[argPos] << "\"." << std::endl;
        return (INIT_KO);
    }
    ++argPos;
    if (!strIsDigit(argvList[argPos]) ||
    atol(argvList[argPos].c_str()) > UINT16_MAX) {
        std::cerr << argvList[argPos] << " is not a valid port." << std::endl;
        return (INIT_KO);
    }
    targetClass.setPort(atoi(argvList[argPos].c_str()));
    return (INIT_OK);
}
