cmake_minimum_required(VERSION 3.2)
project(lunar_lander)

set(TWROOT /Applications/arm/TivaWare)
include(Cmakedefs)

include_directories(${TWROOT})
set(SOURCE_FILES src/startup_gcc.c src/initialization.c)
add_executable(lunar_lander ${SOURCE_FILES})
