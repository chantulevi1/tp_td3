cmake_minimum_required(VERSION 3.0)

project(TP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

include (CTest)

add_executable(editor editor_main.cpp Editor.cpp)
add_executable(editor_tests editor_tests.cpp Editor.cpp)

target_link_libraries(
  editor_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(editor_tests)
