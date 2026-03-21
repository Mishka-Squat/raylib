#!/bin/sh

mkdir build
cd build
cmake ..
make

cd ..

cp ./build/raylib/external/glfw/src/xdg-shell-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/xdg-shell-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/xdg-decoration-unstable-v1-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/xdg-decoration-unstable-v1-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/viewporter-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/viewporter-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/relative-pointer-unstable-v1-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/relative-pointer-unstable-v1-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/pointer-constraints-unstable-v1-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/pointer-constraints-unstable-v1-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/fractional-scale-v1-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/fractional-scale-v1-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/xdg-activation-v1-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/xdg-activation-v1-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/idle-inhibit-unstable-v1-client-protocol.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/idle-inhibit-unstable-v1-client-protocol-code.h ./src/external/glfw/src/
cp ./build/raylib/external/glfw/src/wayland-client-protocol-code.h ./src/external/glfw/src/
