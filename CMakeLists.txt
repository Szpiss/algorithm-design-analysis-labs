cmake_minimum_required(VERSION 3.16)
project(algorithm_design_analysis_labs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(exp1_fake_coin exp1_fake_coin/src/main.cpp)
add_executable(exp2_maze_paths exp2_maze_paths/src/main.cpp)
add_executable(exp3_rescue_a exp3_rescue_a/src/main.cpp)
add_executable(exp4_homework_scheduling exp4_homework_scheduling/src/main.cpp)

