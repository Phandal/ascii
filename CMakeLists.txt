cmake_minimum_required(VERSION 3.16..4.0)

project(ascii VERSION 1.0
  DESCRIPTION "ASCII art render using my custom made image loading library"
  LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BMP_BUILD_DEMO OFF CACHE BOOL "BMP lib only")

add_subdirectory("lib/bmp")

add_subdirectory("src")
