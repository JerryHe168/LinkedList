cmake_minimum_required(VERSION 3.10)
project(DoublyLinkedList)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(DoublyLinkedList main.cpp)

target_include_directories(DoublyLinkedList PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})