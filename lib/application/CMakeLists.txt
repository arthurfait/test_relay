project(app_base)

add_library(${PROJECT_NAME}
    application_base.cpp
    application_base_priv.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
