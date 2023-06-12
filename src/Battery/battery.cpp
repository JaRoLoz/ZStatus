#include "./battery.hpp"

std::string GetRemainingBatteryCharge() {
    std::ifstream batteryFile("/sys/class/power_supply/BAT0/energy_now");
    if (!batteryFile.is_open()) {
        return "No battery";
    }

    std::string line;
    std::getline(batteryFile, line);
    batteryFile.close();

    double energyNow;
    std::stringstream(line) >> energyNow;

    std::ifstream batteryFullFile("/sys/class/power_supply/BAT0/energy_full");
    if (!batteryFullFile.is_open()) {
        return "No battery";
    }

    std::getline(batteryFullFile, line);
    batteryFullFile.close();

    double energyFull;
    std::stringstream(line) >> energyFull;

    double remainingCharge = (energyNow / energyFull) * 100;

    std::stringstream ss;
    ss << remainingCharge;
    return ss.str();
}