cmake_minimum_required(VERSION 3.22)
project("Message Queue")
set(SRC_DIR "messaging-queue")

# Locate GTest
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB src_files ${SRC_DIR}/*.cpp)
list(FILTER src_files EXCLUDE REGEX ".*\\.test\\.cpp$")

# file(GLOB tst_files ${SRC_DIR}/*.cpp)
# list(FILTER tst_files EXCLUDE REGEX ".*main\\.cpp$")

add_executable(messageQueue ${src_files})
# add_executable(programTests ${tst_files})
# target_link_libraries(programTests ${GTEST_LIBRARIES} pthread)
