cmake_minimum_required(VERSION 3.6)
project(OpenGLTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.c fenetre.h  fenetre.c jeu.c jeu.h)
add_executable(OpenGLTest ${SOURCE_FILES})

target_link_libraries(OpenGLTest SDL2main SDL2)