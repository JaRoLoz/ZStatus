#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <arpa/inet.h>

std::string GetCurrentIPv4();