cmake_minimum_required(VERSION 3.17)
project(ConnectFS)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConnectFS
        src/main.cpp
        src/Node.cpp
        headers/Node.h
        src/utilities.cpp
        headers/utilities.h
        src/simple_utf_ops.cpp
        headers/simple_utf_ops.h
        src/graph_ops.cpp
        headers/graph_ops.h
        src/file_name_ops.cpp
        headers/file_name_ops.h
        src/existence_ops.cpp
        headers/existence_ops.h
        src/copy_ops.cpp
        headers/copy_ops.h
        src/load_ops.cpp
        headers/load_ops.h
        src/help_ops.cpp
        headers/help_ops.h)