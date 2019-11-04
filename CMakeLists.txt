cmake_minimum_required(VERSION 3.14)
project(project_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tests")

add_executable(project_1 main.cpp
        Tests/Sport.cpp
        Tests/Competition.cpp
        Tests/Date.cpp
        Tests/Trial.cpp
        Tests/Person.cpp
        Tests/Medal.cpp
        Tests/Delegation.cpp
        Tests/Menus.cpp
        Tests/auxiliar.cpp)

target_link_libraries(project_1)
