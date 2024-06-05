cmake_minimum_required(VERSION 3.26)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Server
        src/main.cpp
        src/Time.cpp
        src/Time.h
        src/Server.cpp
        src/Server.h
)

target_link_libraries(Server PRIVATE Ws2_32)
