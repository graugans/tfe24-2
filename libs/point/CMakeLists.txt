cmake_minimum_required (VERSION 3.10.2)

# Set the project name to your project name, template isn't very descriptive
project (point VERSION 0.0.1 LANGUAGES CXX)
string(TIMESTAMP BUILD_DATE "%Y-%m-%dT%H:%M:%S")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Include dependencies
find_package(fmt REQUIRED)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include") # add the source path to the include PATH
# add the executable we have to add all source files here 
add_library(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/point.cpp)

# Add libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
                                        fmt::fmt)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)