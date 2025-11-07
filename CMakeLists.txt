cmake_minimum_required(VERSION 3.25)

project(Studentu_programa)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(Studentu_programa ${SOURCES})
