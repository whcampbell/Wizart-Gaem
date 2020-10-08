# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)
project(WizartGaem)

file(GLOB engine "../../Engine/*.cpp")
file(GLOB render "../../Rendering/*.cpp")

add_executable(WizartGaem ${engine} ${render})
target_include_directories(WizartGaem PRIVATE "../../headers")