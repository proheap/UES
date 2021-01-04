cmake_minimum_required(VERSION 3.13)
project(Client C)

set(CMAKE_C_STANDARD 99)

add_executable(Client client.c definitions.h definitions.c menu.c menu.h state.c state.h)

TARGET_LINK_LIBRARIES(Client pthread)