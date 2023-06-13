/*
** EPITECH PROJECT, 2023
** ai
** File description:
** paramPort
*/

#include "ZappyAIParam.hpp"

// static bool strIsNum(std::string str)
// {
//     size_t i = 0;
//     bool point_passed = false;

//     for (; i < str.length() && (str[i] == '-' || str[i] == '+'); ++i);
//     if (i >= str.length())
//         return (false);
//     while (i < str.length()) {
//         if (!point_passed && str[i] == '.') {
//             ++i;
//             point_passed = true;
//         }
//         if (!isdigit(str[i]))
//             return (false);
//         ++i;
//     }
//     return (true);
// }

static bool strIsDigit(const std::string &str)
{
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return (false);
    }
    return (true);
}

// static bool strIsInt(const std::string &str)
// {
//     size_t i = 0;

//     for (; i < str.length() && (str[i] == '-' || str[i] == '+'); ++i);
//     if (i >= str.length())
//         return (false);
//     for (; i < str.length(); ++i) {
//         if (!isdigit(str[i]))
//             return (false);
//     }
//     return (strIsDigit(&(str.c_str())[i]));
// }


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
