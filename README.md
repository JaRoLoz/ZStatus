# ZStatus
Versatile and high-customizable status bar for window managers such as i3.

# Compiling
Run `./build.sh` to compile as debug, run `./build_release.sh` to compile as release.
## Requirements
- g++

# Usage 
`zstatus -ip -uds -fs`
## CLI Flags
- Display IPv4 (--ipv4 / -ip)
- Display time (--time / -t)
- Display date (--date / -d)
- Display remaining disk space (--free-space / -fs)
- Display size of the user's home folder (--user-disk-usage / -uds)
- Display remaining battery charge (--battery / -b)
- Change display refresh rate, default 5 seconds (--refresh / -r)