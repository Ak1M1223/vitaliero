#!/usr/bin/env bash
set -e
cmake -DCMAKE_BUILD_TYPE=Release .
make -j$(nproc)
### FOR WSL USERS:
# Enable and Edit lines on the bottom to copy your build to the Windows filesystem, so you can easily copy it to your PS Vita.
cp ./openlierovita.vpk /mnt/c/Users/Akim/Downloads/openliero.vpk
cp -R ./TC /mnt/c/Users/Akim/Downloads/TC
