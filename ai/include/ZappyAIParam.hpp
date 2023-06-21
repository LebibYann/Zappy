/*
** EPITECH PROJECT, 2023
** ai
** File description:
** ZappyAIParam
*/

#pragma once

#include <iostream>

#include "ZappyAI.hpp"
#include "CheckFunction.hpp"

class ZappyAI;

int paramHelp(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass);

int paramPort(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass);

int paramName(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass);

int paramMachine(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass);

typedef int(*param_func)(const std::vector<std::string> &argvList, std::size_t &argPos, ZappyAI &targetClass);

typedef struct s_paramList {
    std::string paramStr;
    param_func paramFunc;
} t_paramList;

#define PARAM_FUNC_NBR 4

typedef enum e_AIFlag {
    AIFLAG_PORT,
    AIFLAG_NAME,
    AIFLAG_HOST,
    AIFLAG_HELP,
    AIFLAG_TOTAL
} t_AIFlag;

static const t_paramList PARAMETER_FUNC[PARAM_FUNC_NBR] = {
    {"-p", paramPort},
    {"-n", paramName},
    {"-h", paramMachine},
    {"-help", paramHelp}
};
