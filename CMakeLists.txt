cmake_minimum_required(VERSION 3.12)
project(MPointers)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(MPointer)
include_directories(MServer/AbstractDataType)
#include_directories(MServer/MServer)

add_executable(MPointers
    MPointer/Client.cpp
    MPointer/Client.h
    MPointer/json.hpp
        MPointer/MPointer.cpp
        MPointer/MPointer.h
    MPointer/main.cpp
    MServer/AbstractDataType/DoublyLinkedList.cpp
#    MServer/AbstractDataType/DoubleList.cpp
#    MServer/AbstractDataType/DoubleList.h
#    MServer/AbstractDataType/List.cpp
#    MServer/AbstractDataType/List.h
#    MServer/MServer/json.hpp
#    MServer/MServer/ServerB.cpp
#    MServer/MServer/ServerB.h
#    MServer/MServer/ServerThread.cpp
#    MServer/MServer/ServerThread.h
        README.md MPointer/MPointerGC.h MPointer/MPointerGC.cpp)
