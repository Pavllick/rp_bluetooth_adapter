cmake_minimum_required(VERSION 3.16)
project(bt-connect)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(bt-connect bt-connect.cpp lib/fileutil.cpp lib/gpio.cpp)

install(TARGETS bt-connect DESTINATION bin)
