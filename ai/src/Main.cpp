/*
** EPITECH PROJECT, 2023
** ai
** File description:
** Main
*/

#include "ZappyAI.hpp"

static std::vector<std::string> generateStrVector(int argc, char **argv)
{
    std::vector<std::string> argvList;

    for (int i = 0; i < argc; ++i) {
        argvList.push_back(argv[i]);
    }
    return (argvList);
}

int main(int argc, char **argv)
{
    std::vector<std::string> argvList = generateStrVector(argc, argv);
    ZappyAI zai;

    return (0);
}
