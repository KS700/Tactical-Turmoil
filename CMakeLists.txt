cmake_minimum_required(VERSION 3.28)
project(Tactical_Turmoil)
set(CMAKE_CXX_STANDARD 20)

# Define the library sources
set(LIBRARY_SOURCES GameBoard.cpp Functions.cpp Player.cpp MenuFunctions.cpp Square.cpp)

# Add library target
add_library(TacticalLib STATIC ${LIBRARY_SOURCES})

# Add executable target
add_executable(${CMAKE_PROJECT_NAME} Main.cpp)

# Link the library to the executable
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE TacticalLib)

# Add the include directory
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})