cmake_minimum_required(VERSION 3.10)
project(exercise_006_tests)

find_package(Catch2 3 REQUIRED)
find_package(fmt REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_executable(test_point_template test_point_template_cpp17.cpp)

target_link_libraries(test_point_template PRIVATE Catch2::Catch2WithMain fmt::fmt)

include(CTest)
include(Catch)
catch_discover_tests(test_point_template)