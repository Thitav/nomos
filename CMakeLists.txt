cmake_minimum_required(VERSION 3.13.0)
project(nomos VERSION 0.1.0)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/sysroot")

add_subdirectory("src/libc")
add_subdirectory("src/kernel")
