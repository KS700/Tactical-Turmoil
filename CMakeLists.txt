cmake_minimum_required(VERSION 3.28)
project(Tactical_Turmoil)

set(CMAKE_CXX_STANDARD 20)

# Add executable target
add_executable(Tactical Main.cpp GameBoard.cpp Functions.cpp Player.cpp MenuFunctions.cpp Square.cpp)

# Add the include directory
target_include_directories(Tactical PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})