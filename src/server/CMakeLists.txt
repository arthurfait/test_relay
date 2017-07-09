cmake_minimum_required(VERSION 2.8.11)
project(relay_socket)

add_executable(${PROJECT_NAME}
                main.cpp
                server_application.cpp
                test_thread_recive.cpp
)

target_link_libraries(${PROJECT_NAME} app_base threading net_sock)

