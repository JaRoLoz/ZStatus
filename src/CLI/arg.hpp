#pragma once
#include <string>

class CLIArgument
{
public:
    CLIArgument(std::string flag, std::string alias = "", bool requiresArgument = false, size_t argumentNumber = 0) : m_flag(flag), m_alias(alias), m_requiresArgument(requiresArgument), m_argumentNumber(argumentNumber) {}
    std::string getFlag();
    std::string getAlias();
    bool getRequiresArgument();
    size_t getArgumentNumber();
    bool compareFlag(std::string flag);
    bool compareAlias(std::string alias);
protected:
    std::string m_flag;
    std::string m_alias;
    bool m_requiresArgument;
    size_t m_argumentNumber;
};