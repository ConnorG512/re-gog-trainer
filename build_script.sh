#!/bin/bash

# launcher exe
zig c++ \
    -target x86-windows-gnu \
    -static \
    -o "./build/re-gog-trainer-launcher.exe" "./src/launcher/launcher.cpp" \
    -luser32

# trainer dll
zig c++ \
    -target x86-windows-gnu \
    -shared \
    -o "./build/re-trainer.dll" "./src/trainer/dll.cpp" \
    -luser32
