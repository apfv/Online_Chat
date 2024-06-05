cmake_minimum_required(VERSION 3.26)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Client
        src/main.cpp
        src/Client.cpp
        src/Client.h
        src/Time.cpp
        src/Time.h
)

target_link_libraries(Client PRIVATE Ws2_32)
