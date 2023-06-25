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

    switch (zai.init(argvList)) {
        case INIT_KO:
            return (84);
        case INIT_HELP:
            return (0);
    }
    zai.displayParameters();
    if (!zai.connectToServer())
        return (84);
    zai.run();
    return (0);
}
