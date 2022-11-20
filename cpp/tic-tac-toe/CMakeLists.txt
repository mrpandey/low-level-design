cmake_minimum_required(VERSION 3.22)
project(tic-tac-toe)
set(SRC_DIR "tic-tac-toe")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(game ${SRC_DIR}/main.cpp ${SRC_DIR}/TicTacToe.cpp ${SRC_DIR}/Player.cpp ${SRC_DIR}/Piece.cpp ${SRC_DIR}/Board.cpp)
add_executable(unitTests ${SRC_DIR}/main.test.cpp ${SRC_DIR}/Player.cpp ${SRC_DIR}/Piece.cpp ${SRC_DIR}/Board.cpp ${SRC_DIR}/Board.test.cpp ${SRC_DIR}/Piece.test.cpp ${SRC_DIR}/Player.test.cpp)
target_link_libraries(unitTests ${GTEST_LIBRARIES} pthread)