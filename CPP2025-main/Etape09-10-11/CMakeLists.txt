cmake_minimum_required(VERSION 3.16)

project(ApplicGarage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(includes)

file(GLOB SOURCES
    sources/*.cpp
)

add_executable(ApplicGarage ${SOURCES})

target_link_libraries(ApplicGarage Qt5::Widgets)
