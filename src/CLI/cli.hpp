#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <exception>
#include <variant>
#include <tuple>
#include <cstring>
#include "./arg.hpp"

class InsufficientArgsException : public std::exception {
public:
    const char* what() const noexcept override {
        return "InsufficientArgsException: Not enough arguments were provided";
    }
};

std::tuple<std::unordered_map<std::string, std::variant<std::vector<std::string>, bool>>, std::vector<std::string>> *ParseCLIArguments(size_t argc, char** argv, std::vector<CLIArgument> arguments);
