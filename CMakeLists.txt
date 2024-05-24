cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(
  silver
  LANGUAGES CXX
  VERSION 1.0.0)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

set(silver_SRCS ./src/main.cpp ./src/projection_3d.cpp ./src/window.cpp)
set(silver_HRDS ./include/silver/application.h ./include/silver/camera_3d.h
                ./include/silver/window.h ./include/silver/projection_3d.h)

add_executable(silver ${silver_SRCS} ${silver_HRDS})

target_link_libraries(silver PRIVATE glfw OpenGL::GL glm::glm glad::glad)
