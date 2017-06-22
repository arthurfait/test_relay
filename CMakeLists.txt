cmake_minimum_required(VERSION 2.6)
project(relay_socket)

add_executable(relay_socket
                main.cpp
                thread.cpp
                tcp_socket.cpp
                application.h
                application.cpp
                test_thread_recive.cpp
)

target_link_libraries(relay_socket pthread)

install(TARGETS relay_socket RUNTIME DESTINATION bin)
