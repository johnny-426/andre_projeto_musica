cmake_minimum_required(VERSION 3.20)
project(music_library_c C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(music_library main.c pss.c)
