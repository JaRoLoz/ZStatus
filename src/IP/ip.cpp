#include "./ip.hpp"

std::string GetCurrentIPv4()
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    // Get the list of network interfaces
    if (getifaddrs(&ifaddr) == -1) {
        // std::cerr << "\033[1;31mFailed to get network interfaces.\033[0m" << std::endl;
        return "\033[1;31mNo IPv4\033[0m";
    }

    // Iterate through the network interfaces
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr)
            continue;

        family = ifa->ifa_addr->sa_family;

        // Filter for IPv4 addresses
        if (family == AF_INET) {
            s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
            if (s != 0) {
                std::cerr << "\033[1;31mFailed to get IP address: " << gai_strerror(s) << "\033[0m" << std::endl;
                freeifaddrs(ifaddr);
                return "\033[1;31mNo IPv4\033[0m";
            }

            // Exclude loopback address
            if (std::strcmp(ifa->ifa_name, "lo") != 0) {
                freeifaddrs(ifaddr);
                return host;
            }
        }
    }

    // Free the memory allocated by getifaddrs()
    freeifaddrs(ifaddr);

    std::cerr << "\033[1;31mNo private IP found.\033[0m" << std::endl;
    return "\033[1;31mNo IPv4\033[0m";
}
