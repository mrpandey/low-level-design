cmake_minimum_required(VERSION 3.22)
project("tic-tac-toe")
set(SRC_DIR "tic-tac-toe")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB src_files ${SRC_DIR}/*.cpp)
list(FILTER src_files EXCLUDE REGEX ".*\\.test\\.cpp$")

file(GLOB tst_files ${SRC_DIR}/*.cpp)
list(FILTER tst_files EXCLUDE REGEX ".*main\\.cpp$")

add_executable(game ${src_files})
add_executable(unitTests ${tst_files})
target_link_libraries(unitTests ${GTEST_LIBRARIES} pthread)
