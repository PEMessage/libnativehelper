#!/bin/bash
cmake -S . -B build &&
    cmake --build build

rm -rf compile_commands.json
ln -s build/compile_commands.json .
