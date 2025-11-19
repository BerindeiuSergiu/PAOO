#!/usr/bin/env bash


echo "===== Cleaning old build directory ====="
rm -rf build

echo "===== Configuring build with CMake ====="
cmake -B build -S .

echo "===== Building project ====="
cmake --build build

echo "===== Running program ====="
echo ""
./build/LoggerApp

echo ""
echo "===== Execution finished ====="
echo "Log files stored in ./logs/"
