cmake_minimum_required(VERSION 3.12)
project(TowerDefense VERSION 1.0)

file(GLOB SOURCES CONFIGURE_DEPENDS *.h, *.c)

#include project and allegro headers
include_directories(allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\\include)
link_directories(allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\\lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCFILES *.cpp)
add_executable(TowerDefense ${SRCFILES})

target_link_libraries(
    TowerDefense
    allegro_acodec
    allegro_audio
    allegro_color
    allegro_dialog
    allegro_font
    allegro_image
    allegro_main
    allegro_memfile
    allegro_primitives
    allegro
    allegro_ttf
    -lm
)