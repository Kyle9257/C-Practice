cmake_minimum_required(VERSION 3.15)
project(GTestDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 用 FetchContent 自动拉取并编译 GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_calc test_calc.cpp)
target_link_libraries(test_calc PRIVATE gtest gtest_main)
add_test(NAME calc_tests COMMAND test_calc)
