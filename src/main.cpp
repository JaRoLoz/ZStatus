#include <iostream>
#include <variant>
#include <chrono>
#include <thread>
#include <tuple>
#include <functional>
#include "./CLI/cli.hpp"
#include "./CLI/arg.hpp"
#include "./IP/ip.hpp"
#include "./Time/time.hpp"
#include "./Date/date.hpp"
#include "./Disk/disk.hpp"
#include "./Battery/battery.hpp"

bool IsStringValid(std::string& str);
size_t StringToSize(std::string& str);

std::vector<CLIArgument> CLIArgs = 
{
    CLIArgument("--ipv4", "-ip", false),
    CLIArgument("--time", "-t", false),
    CLIArgument("--date", "-d", false),
    CLIArgument("--free-space", "-fs", false),
    CLIArgument("--user-disk-usage", "-uds", false),
    CLIArgument("--battery", "-b", false),
    CLIArgument("--refresh", "-r", true, 1)
};

int main(int argc, char** argv)
{
    auto args                = ParseCLIArguments(argc, argv, CLIArgs);
    auto flags               = std::get<0>(*args);
    bool showIPv4            = flags.find("--ipv4") != flags.end();
    bool showTime            = flags.find("--time") != flags.end();
    bool showDate            = flags.find("--date") != flags.end();
    bool showFreeSpace       = flags.find("--free-space") != flags.end();
    bool showDiskUsage       = flags.find("--user-disk-usage") != flags.end();
    bool showBattery         = flags.find("--battery") != flags.end();
    bool refreshTimeProvided = flags.find("--refresh") != flags.end();
    size_t refreshTime = 5;
    if (refreshTimeProvided)
    {
        std::string refreshTimeStr = std::get<std::vector<std::string>>(flags.at("--refresh")).at(0);
        if (IsStringValid(refreshTimeStr)) 
            refreshTime = std::stoull(refreshTimeStr);
    }
    std::tuple<bool, std::function<std::string()>, std::string> displayData[] = { 
        std::make_tuple(showIPv4, GetCurrentIPv4, ""), 
        std::make_tuple(showFreeSpace, GetRemainingDiskSpace, "GB"),
        std::make_tuple(showDiskUsage, GetUserFolderUsage, "GB"),
        std::make_tuple(showTime, GetCurrentTime, ""),
        std::make_tuple(showDate, GetCurrentDate, ""),
        std::make_tuple(showBattery, GetRemainingBatteryCharge, "%")
    };
    std::string outputString = "";
    while (true)
    {
        for (auto& data : displayData)
        {
            if (!std::get<0>(data)) continue;
            outputString += std::get<1>(data)();
            outputString += std::get<2>(data);
            outputString += " | ";
        }
        outputString = outputString.substr(0, outputString.size() - 2);
        std::cout << outputString << std::flush;
        outputString.clear();
        std::this_thread::sleep_for(std::chrono::seconds(refreshTime));
    }
    return 0;
}

bool IsStringValid(std::string& str)
{
    if (str.empty())
        return false;
    size_t pos = 0;
    try {
        std::stoull(str, &pos);
    } catch (const std::exception&) {
        return false;
    }
    if (pos < 0 || pos > std::numeric_limits<size_t>::max())
        return false;
    return true;
}
