cmake_minimum_required(VERSION 3.13)
project(client C)

set(CMAKE_C_STANDARD 99)

add_executable(client client.c definitions.h definitions.c menu.c menu.h state.h)

TARGET_LINK_LIBRARIES(client pthread)