cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ���������� ������������ ����������
add_library(MyLibrary STATIC src/library.cpp)

# ���������, ��� ������ ������������ �����
target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ���������� Google Test ����� FetchContent
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ������ �������� ����������� ����
add_executable(MyLibraryTest tests/test_basic.cpp)
target_link_libraries(MyLibraryTest PRIVATE MyLibrary gtest_main)

include(GoogleTest)
gtest_discover_tests(MyLibraryTest)

