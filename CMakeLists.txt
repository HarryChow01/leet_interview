cmake_minimum_required(VERSION 3.0)
project(leet_interview)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(leetcode_1 leetcode_1.cpp)
add_executable(leetcode_2 leetcode_2.cpp)
add_executable(array_interview array_interview.cpp)
add_executable(list_interview list_interview.cpp)
add_executable(string_interview string_interview.cpp)
add_executable(bitree_interview bitree_interview.cpp)
add_executable(algorithm_interview algorithm_interview.cpp)
add_executable(sort_interview sort_interview.cpp)
add_executable(other_interview other_interview.cpp)


add_executable(String src/String.cpp)
add_executable(singleton src/singleton.cpp)
add_executable(BlockingQueue src/BlockingQueue.cpp)
add_executable(threadsafe_queue src/threadsafe_queue.cpp)
add_executable(threadsafe_hashmap src/threadsafe_hashmap.cpp)

add_executable(LRUCache src/LRUCache.cpp)
add_executable(smart_ptr src/smart_ptr.cpp)







