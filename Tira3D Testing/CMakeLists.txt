cmake_minimum_required(VERSION 3.12)

project(Tira3D Testing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "*.cpp")

# Add executables
add_executable(Tira3D Testing $(SOURCES))

# Specify additional include directories if needed
target_include_directories(Tira3D Testing PRIVATE ../Tira3D/Renderer/)

# Specify additional libraries if needed
# target_link_libraries(MyCppApp PRIVATE some_library)

# Set output directories if needed
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
