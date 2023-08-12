cmake_minimum_required(VERSION 3.12)

project(Tira3D)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use file(GLOB ...) to automatically find all .cpp files in the project
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Tira3D ${SOURCES})

# Specify additional include directories if needed
# target_include_directories(MyCppApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
file(GLOB LIBS "../Dependencies/*.lib")

# Specify additional libraries if needed
target_link_libraries(Tira3D PUBLIC ${LIBS})

# Set output directories if needed
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
# Add executable
