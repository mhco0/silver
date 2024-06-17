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

find_package(ImGui-SFML CONFIG REQUIRED)
find_package(
  SFML
  COMPONENTS system window graphics CONFIG
  REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(tl-expected CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)

include_directories(include)

set(silver_SRCS
    ./src/main.cpp
    ./src/projection_3d.cpp
    ./src/window.cpp
    ./src/utils.cpp
    ./src/camera_controller_widget.cpp
    ./src/canvas.cpp
    ./src/geometry_selection_widget.cpp
    ./src/camera.cpp)

set(silver_HRDS
    ./include/silver/application.h
    ./include/silver/camera_3d.h
    ./include/silver/window.h
    ./include/silver/projection_3d.h
    ./include/silver/utils.h
    ./include/silver/i_widget.h
    ./include/silver/camera_controller_widget.h
    ./include/silver/canvas.h
    ./include/silver/geometry_selection_widget.h
    ./include/silver/i_node.h
    ./include/silver/triangle.h)

add_executable(silver ${silver_SRCS} ${silver_HRDS})
target_link_libraries(
  silver
  PRIVATE sfml-system
          sfml-network
          sfml-graphics
          sfml-window
          ImGui-SFML::ImGui-SFML
          OpenGL::GL
          glm::glm
          imgui::imgui
          tl::expected
          unofficial::nativefiledialog::nfd)

# Tests
include(GoogleTest)
include(CTest)
enable_testing()
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)

set(silver_TESTS ./src/utils_test.cpp)
add_executable(silver_tests ${silver_SRCS} ${silver_HRDS} ${silver_TESTS})

target_link_libraries(
  silver_tests
  PRIVATE OpenGL::GL
          glm::glm
          imgui::imgui
          tl::expected
          unofficial::nativefiledialog::nfd
          sfml-system
          sfml-network
          sfml-graphics
          sfml-window
          ImGui-SFML::ImGui-SFML
          GTest::gtest_main)
add_test(NAME silver_test COMMAND silver_tests)
gtest_discover_tests(silver_tests)
