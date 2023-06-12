#include "./cli.hpp"

std::tuple<std::unordered_map<std::string, std::variant<std::vector<std::string>, bool>>, std::vector<std::string>> *ParseCLIArguments(size_t argc, char **argv, std::vector<CLIArgument> arguments)
{
    if (argc < 1)
    {
        if (!arguments.empty())
            throw InsufficientArgsException();
        return new std::tuple<std::unordered_map<std::string, std::variant<std::vector<std::string>, bool>>, std::vector<std::string>>;
    }

    auto flags = new std::tuple<std::unordered_map<std::string, std::variant<std::vector<std::string>, bool>>, std::vector<std::string>>;

    for (size_t i = 0; i < argc; i++)
    {
        if (!i)
            continue;
        char *currentArg = argv[i];
        if (!strncmp(currentArg, "--", 2))
        {
            for (size_t j = 0; j < arguments.size(); j++)
            {
                auto &currentFlag = arguments.at(j);
                if (currentFlag.compareFlag(currentArg))
                {
                    if (currentFlag.getRequiresArgument())
                    {
                        if (i + currentFlag.getArgumentNumber() + 1 > argc)
                            throw InsufficientArgsException();
                        std::vector<std::string> currentArgs = {};
                        for (size_t k = 0; k < currentFlag.getArgumentNumber(); k++)
                        {
                            if (argv[i + k + 1][0] == '-')
                                throw InsufficientArgsException();
                            currentArgs.push_back(argv[i + k + 1]);
                        }
                        i += currentFlag.getArgumentNumber();
                        std::get<0>(*flags).emplace(currentFlag.getFlag(), currentArgs);
                        arguments.erase(arguments.begin() + j);
                        continue;
                    } else
                        std::get<0>(*flags).emplace(currentFlag.getFlag(), true);
                }
            }
        }
        else if (currentArg[0] == '-')
        {
            for (size_t j = 0; j < arguments.size(); j++)
            {
                auto &currentAlias = arguments.at(j);
                if (currentAlias.compareAlias(currentArg))
                {
                    if (currentAlias.getRequiresArgument())
                    {
                        if (i + currentAlias.getArgumentNumber() > argc)
                            throw InsufficientArgsException();
                        std::vector<std::string> currentArgs = {};
                        for (size_t k = 0; k < currentAlias.getArgumentNumber(); k++)
                        {
                            if (argv[i + k + 1][0] == '-')
                                throw InsufficientArgsException();
                            currentArgs.push_back(argv[i + k + 1]);
                        }
                        i += currentAlias.getArgumentNumber();
                        std::get<0>(*flags).emplace(currentAlias.getFlag(), currentArgs);
                        arguments.erase(arguments.begin() + j);
                        break;
                    } else
                        std::get<0>(*flags).emplace(currentAlias.getFlag(), true);
                }
            }
        }
        else
            std::get<1>(*flags).push_back(currentArg);
    }

    return flags;
}