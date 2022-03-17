cmake_minimum_required(VERSION 2.8)
project(bt_daemon)
add_executable(bt_daemon bt_daemon.cpp)
install(TARGETS bt_daemon DESTINATION bin)
