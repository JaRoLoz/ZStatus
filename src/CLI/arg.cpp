#include "./arg.hpp"

bool CLIArgument::compareFlag(std::string flag)
{
    return !this->m_flag.compare(flag);
}

bool CLIArgument::compareAlias(std::string alias)
{
    return !this->m_alias.compare(alias);
}

std::string CLIArgument::getFlag()
{
    return this->m_flag;
}

std::string CLIArgument::getAlias()
{
    return this->m_alias;
}

bool CLIArgument::getRequiresArgument()
{
    return this->m_requiresArgument;
}

size_t CLIArgument::getArgumentNumber()
{
    return this->m_argumentNumber;
}