cmake_minimum_required(VERSION 3.0.0)
project(newos VERSION 0.1.0 LANGUAGES C CXX ASM)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/sysroot")

add_subdirectory(src/libc)
add_subdirectory(src/kernel)
