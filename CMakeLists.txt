cmake_minimum_required(VERSION 3.9)
project(storm-in-a-glass)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OpenGL")

include_directories(include)
include_directories(src)

set(MAIN
    src/main.cpp
    src/environment.cpp
    include/environment.h
    src/body.cpp
    include/body.h
    src/configuration.cpp
    include/configuration.h
    src/liquid.cpp
    include/liquid.h
    src/graphics.cpp
    include/graphics.h
    include/json.hpp
)

add_executable(
    ${PROJECT_NAME}
    ${MAIN}
)

target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew)
