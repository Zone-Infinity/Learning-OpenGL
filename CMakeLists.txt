cmake_minimum_required(VERSION 3.10)
project(logl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(logl
    src/main.cpp
    src/glad.c
    src/stb.cpp
    src/shader/shaderClass.cpp
    src/object/VAO.cpp
    src/object/VBO.cpp
    src/object/EBO.cpp
)

target_include_directories(logl PRIVATE
    ./include
    /usr/include
)

target_link_libraries(logl
    OpenGL::GL
    glfw
)
