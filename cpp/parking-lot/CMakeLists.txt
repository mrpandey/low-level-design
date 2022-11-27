cmake_minimum_required(VERSION 3.22)
project("Parking Lot")
set(SRC_DIR "parking-lot")

file(GLOB src_files ${SRC_DIR}/*.cpp)
add_executable(parkingService ${src_files})