/*
** EPITECH PROJECT, 2023
** ai
** File description:
** ZappyAIParam
*/

#pragma once

#include <iostream>

#include "ZappyAI.hpp"

class ZappyAI;

int paramHelp(const std::vector<std::string> &argvList, int argPos, ZappyAI &targetClass);

typedef int(*param_func)(const std::vector<std::string> &argvList, int argPos, ZappyAI &targetClass);

typedef struct s_paramList {
    std::string paramStr;
    param_func paramFunc;
} t_paramList;

static const t_paramList PARAMETER_FUNC[] = {
    {"-p", paramHelp},
    {"-n", paramHelp},
    {"-h", paramHelp},
    {"-help", paramHelp}
};
