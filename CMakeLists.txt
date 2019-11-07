cmake_minimum_required(VERSION 3.14)
project(projeto1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tests")

include_directories(Tests)

add_executable(projeto1
        Tests/auxiliar.cpp
        Tests/auxiliar.h
        Tests/Competition.cpp
        Tests/Competition.h
        Tests/Date.cpp
        Tests/Date.h
        Tests/Delegation.cpp
        Tests/Delegation.h
        Tests/Medal.cpp
        Tests/Medal.h
        Tests/Menus.cpp
        Tests/Menus.h
        Tests/Person.cpp
        Tests/Person.h
        Tests/Sport.cpp
        Tests/Sport.h
        Tests/Trial.cpp
        Tests/Trial.h
        main.cpp)
