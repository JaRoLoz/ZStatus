#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

mkdir build > /dev/null 2>&1

echo ""
echo "[======================================================]"
echo "Compilation started on $(date)"

g++ src/*.cpp src/**/*.cpp -g -o build/build

if [ $? -eq 0 ]; then
    echo -e "Compilation ${GREEN}successful${NC} on $(date)"
else
    echo -e "Compilation ${RED}failed${NC} on $(date)"
fi

echo "[======================================================]"
echo ""
