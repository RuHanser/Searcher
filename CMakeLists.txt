cmake_minimum_required(VERSION 3.10)
project(Searcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(COPY ${CMAKE_SOURCE_DIR}/config.json DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/requests.json DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Searcher
    src/ConverterJson.cpp
    src/InvertedIndex.cpp
    src/SearchServer.cpp
    src/Searcher.cpp
)

# ===== GTest =====
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests
    test/test.cpp
    src/InvertedIndex.cpp
    src/SearchServer.cpp
    src/ConverterJson.cpp
)
target_link_libraries(tests gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)