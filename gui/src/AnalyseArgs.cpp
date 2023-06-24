/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** AnalyseArgs
*/

#include <vector>
#include <string>

std::vector<std::string> analyseArgs(int ac, char **av)
{
    std::vector<std::string> args;
    std::vector<std::string> answers = {"-1", "-1"};

    if (ac != 4)
        exit(84);
    for (int i = 0; i < ac; i++) {
        args.push_back(av[i]);
    }
    for (int i = 0; i < ac - 1; i++) {
        if (args[i] == "-h")
            answers[0] = args[i + 1];
        if (args[i] == "-p")
            answers[1] = args[i + 1];
    }
    if (answers[0] == "-1" || answers[1] == "-1")
        exit(84);
    return (answers);
}
