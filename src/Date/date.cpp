#include "./date.hpp"

std::string GetCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << localTime->tm_mday << "-"
        << std::setw(2) << (localTime->tm_mon + 1) << "-"
        << (localTime->tm_year + 1900);
    return ss.str();
}