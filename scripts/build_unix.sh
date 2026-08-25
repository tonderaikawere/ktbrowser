#!/usr/bin/env bash
set -e

echo "==================================================="
echo "Building CodeBrowser Native Linux / macOS Executable"
echo "==================================================="

mkdir -p build
cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release

echo "Running Unit Tests..."
ctest --output-on-failure

echo "==================================================="
echo "CodeBrowser built successfully!"
echo "==================================================="
