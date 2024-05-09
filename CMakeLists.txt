cmake_minimum_required(VERSION 3.26)
project(shop_project)

set(CMAKE_CXX_STANDARD 23)

add_executable(shop_project main.cpp
        product.cpp
        product.h
        testing.cpp
        order.cpp
        order.h
        test.cpp
        tempp.cpp)
