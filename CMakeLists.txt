cmake_minimum_required(VERSION 3.10)
include(FetchContent)
project(test VERSION 1.0.0)

find_package(OpenGL REQUIRED)


include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)


FetchContent_MakeAvailable(glfw)

add_executable(test
    src/main.c
    src/glad.c
    src/c_config.h
    src/c_triangle.h
)

target_link_libraries(test glfw OpenGL::GL)
target_include_directories(test PRIVATE dependencies)


