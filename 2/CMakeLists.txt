cmake_minimum_required(VERSION 3.20)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(inc)
add_executable(lab2 main.cpp inc/ordered_set/ordered_set.h  inc/rbtree/rbtree.h inc/rbtree/rbtree.hpp inc/ordered_set/ordered_set.hpp inc/rbtree/rbtree_iterator.h inc/rbtree/rbtree_node.h  inc/errors.h inc/tests/creation.h inc/tests/main.h inc/tests/insertion.h inc/tests/removal.h inc/tests/util.h inc/tests/operations.h inc/basic_set.h inc/tests/copy_move.h inc/tests/iterators.h)

target_link_libraries(lab2 ${GTEST_LIBRARIES} Threads::Threads)
enable_testing()
