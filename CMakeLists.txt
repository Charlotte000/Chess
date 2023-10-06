cmake_minimum_required(VERSION 3.10)

project(Chess)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Board.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Move.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Piece.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
