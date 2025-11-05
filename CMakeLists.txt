cmake_minimum_required(VERSION 3.10)
project(LoggerApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(LoggerApp
    src/main.cpp
    src/LogFile.cpp
    src/Logger.cpp
)