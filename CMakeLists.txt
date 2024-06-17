cmake_minimum_required(VERSION 3.25)
project(CPP_Games)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES GreedySnake.cpp Pong.cpp main.cpp)

add_executable(CPP_Games ${SOURCES})

target_include_directories(CPP_Games PRIVATE ${PROJECT_SOURCE_DIR}/include)
