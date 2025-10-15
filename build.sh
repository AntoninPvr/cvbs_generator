#!/bin/zsh
# Usage: ./build.sh [release|debug|purge]

if [[ -z "$PROJECT_DIR" ]]; then
    echo "Please run setenv.sh in the project root directory before this script."
    exit 1
fi


BUILD_DIR=build
CMAKE_FLAGS=""

if [[ "$1" == "purge" ]]; then
    echo "Purging build directory..."
    rm -rf "$BUILD_DIR"
    exit 0
elif [[ "$1" == "release" ]]; then
    CMAKE_FLAGS="-DCMAKE_BUILD_TYPE=Release"
    echo "Configuring for Release build..."
else
    CMAKE_FLAGS="-DCMAKE_BUILD_TYPE=Debug"
    echo "Configuring for Debug build..."
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake $CMAKE_FLAGS ..
make -j$(nproc)
