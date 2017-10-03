project(client_test)

add_executable(${PROJECT_NAME}
                main.cpp
                client_application.cpp
        SendFile.cpp SendFile.h)

target_link_libraries(${PROJECT_NAME} app_base threading net_sock)

