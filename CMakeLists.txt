cmake_minimum_required(VERSION 3.2)
project(lunar_lander)

set(TWROOT /Applications/arm/TivaWare)
include(Cmakedefs)

include_directories(${TWROOT} inc/)
set(SOURCE_FILES src/startup_gcc.c src/initialization.c src/LCD.c src/main.c src/ST7735.c src/PLL.c src/debugging_utilities.c)
add_executable(lunar_lander ${SOURCE_FILES} inc/game_outcomes.h src/game_outcomes.c inc/sound.h src/sound.c)
