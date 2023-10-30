cmake_minimum_required(VERSION 3.22)

project(advent20153 LANGUAGES CXX)

add_executable(solution main.cpp)

target_compile_features(solution PUBLIC cxx_std_20)
target_compile_options(solution PRIVATE /W4 /WX)
set_target_properties(solution PROPERTIES CXX_EXTENSION OFF)
