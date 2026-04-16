cmake_minimum_required(VERSION 3.20)
set(APP_NAME test_log_module)
project(${APP_NAME} LANGUAGES C)

add_executable(${APP_NAME} 
    ${CMAKE_SOURCE_DIR}/main.c
    ${CMAKE_SOURCE_DIR}/../my_log.c
    ${CMAKE_SOURCE_DIR}/../my_ringbuffer.c
)

target_include_directories(${APP_NAME} PRIVATE
    # ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/..
)