#include "./disk.hpp"

std::string GetRemainingDiskSpace() {
    struct statvfs vfs;
    if (statvfs("/", &vfs) != 0) {
        return "Error retrieving disk space.";
    }

    unsigned long long blockSize = vfs.f_frsize;
    unsigned long long totalSpace = vfs.f_blocks * blockSize;
    unsigned long long freeSpace = vfs.f_bfree * blockSize;
    double remainingSpaceGB = static_cast<double>(freeSpace) / (1024 * 1024 * 1024); // Convert to GB

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << remainingSpaceGB;
    return ss.str();
}

std::string GetUserFolderUsage()
{
    const char* homePath = getenv("HOME");
    if (homePath == nullptr) {
        return "Error retrieving home folder path.";
    }

    struct statvfs vfs;
    if (statvfs(homePath, &vfs) != 0) {
        return "Error retrieving disk space.";
    }

    unsigned long long blockSize = vfs.f_frsize;
    unsigned long long totalSpace = vfs.f_blocks * blockSize;
    unsigned long long freeSpace = vfs.f_bfree * blockSize;
    unsigned long long occupiedSpace = totalSpace - freeSpace;
    double occupiedSpaceGB = static_cast<double>(occupiedSpace) / (1024 * 1024 * 1024); // Convert to GB

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << occupiedSpaceGB;
    return ss.str();
}