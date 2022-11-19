cmake_minimum_required(VERSION 3.22)
project(tic-tac-toe)
set(SRC_DIR "tic-tac-toe")
add_executable(game ${SRC_DIR}/main.cpp ${SRC_DIR}/TicTacToe.cpp ${SRC_DIR}/Player.cpp ${SRC_DIR}/Piece.cpp ${SRC_DIR}/Board.cpp)