cmake_minimum_required(VERSION 3.5)

set(project_name caracol)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(${project_name})

add_executable(${project_name}-examples-count examples/count.cpp)
add_executable(${project_name}-examples-sum_interval examples/sum_interval.cpp)
add_executable(${project_name}-examples-hello_world examples/hello_world.cpp)
add_executable(${project_name}-examples-hello_world2 examples/hello_world2.cpp)
add_executable(${project_name}-examples-factorial examples/factorial.cpp)
