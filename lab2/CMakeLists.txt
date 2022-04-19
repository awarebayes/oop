cmake_minimum_required(VERSION 3.20)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(inc)
add_executable(lab2 main.cpp inc/abstract/abstract_set.h inc/rbtree/rbtree.h inc/rbtree/rbtree.hpp inc/abstract/abstract_set.hpp inc/rbtree/rbtree_iterator.h inc/rbtree/rbtree_node.h inc/concrete_set.h inc/errors.h inc/tests/creation.h inc/tests/main.h inc/tests/insertion.h inc/tests/removal.h inc/tests/util.h inc/tests/operations.h)

target_link_libraries(lab2 ${GTEST_LIBRARIES} Threads::Threads)
enable_testing()
