cmake_minimum_required(VERSION 3.13)
project(Server C)

set(CMAKE_C_STANDARD 99)

add_executable(Server server.c definitions.h definitions.c ./structures/linked_list.h ./structures/linked_list.c ./structures/item.h ./structures/item.c ./structures/constants.h ../CMemLeak.h ../CMemLeak.c evidence_system.c evidence_system.h table.c table.h column.c column.h)

target_link_libraries(Server pthread)