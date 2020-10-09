# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)
project(WizartGaem)

file(GLOB engine "../../Engine/*.cpp")
file(GLOB render "../../Rendering/*.cpp")
find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS "../../libs/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2")
find_library(SDL2_LIB_DIR NAME SDL2 HINTS "../../libs/SDL2-2.0.12/x86_64-w64-mingw32/lib")
find_file(SDL2_MIXER_INCLUDE_DIR NAME SDL_mixer.h HINTS "../../libs/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include/SDL2")
find_library(SDL2_MIXER_LIB_DIR NAME SDL2_mixer HINTS "../../libs/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib")
find_file(SDL2_IMAGE_INCLUDE_DIR NAME SDL_image.h HINTS "../../libs/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2")
find_library(SDL2_IMAGE_LIB_DIR NAME SDL2_image HINTS "../../libs/SDL2_image-2.0.5/x86_64-w64-mingw32/lib")

message(STATUS "SDL: [${SDL2_LIB_DIR}]")
message(STATUS "SDL Mixer: [${SDL2_MIXER_LIB_DIR}]")
message(STATUS "SDL Image: [${SDL2_IMAGE_LIB_DIR}]")

message(STATUS "SDL include: [${SDL2_INCLUDE_DIR}]")
message(STATUS "SDL mixer include: [${SDL2_MIXER_INCLUDE_DIR}]")
message(STATUS "SDL image include: [${SDL2_IMAGE_INCLUDE_DIR}]")

include_directories("../../headers" "../../libs/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2" "../../libs/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include/SDL2" "../../libs/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2")
add_executable(WizartGaem ${engine} ${render})
target_include_directories(WizartGaem PUBLIC "../../headers" "../../libs/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2" "../../libs/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include/SDL2" "../../libs/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2")
target_link_libraries(WizartGaem PUBLIC ${SDL2_LIB_DIR} ${SDL2_MIXER_LIB_DIR} ${SDL2_IMAGE_LIB_DIR})