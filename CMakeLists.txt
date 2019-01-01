cmake_minimum_required(VERSION 3.12)
project(languageserver_tools)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_library(languageserver_tools
        src/library.h
        src/library.cpp
        src/ThreadedQueue.cpp
        src/ThreadedQueue.h
        src/position.h
        src/position.cpp
        src/QueueManager.cpp
        src/QueueManager.h
        src/ioThreads.cpp
        src/main.cpp src/ioThreads.h)

add_executable(languageserver_tools_ex
        src/library.h
        src/library.cpp
        src/ThreadedQueue.cpp
        src/ThreadedQueue.h
        src/position.h
        src/position.cpp
        src/QueueManager.cpp
        src/QueueManager.h
        src/ioThreads.cpp
        src/main.cpp src/ioThreads.h)

target_include_directories(languageserver_tools PRIVATE
        third_party/rapidjson/include
        )

target_include_directories(languageserver_tools_ex PRIVATE
        third_party/rapidjson/include
        )