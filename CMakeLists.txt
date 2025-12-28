cmake_minimum_required(VERSION 3.14)
project(Solar)

# --- Keep GLFW (Since this was working) ---
include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(glfw)

# --- The Manual Fix ---
# 1. Add the local 'include' folder so C++ finds glad.h
include_directories(include)

# 2. Build your app using main.cpp AND the glad.c file we just added
add_executable(Solar main.cpp src/glad.c)

# 3. Link libraries
target_link_libraries(Solar PRIVATE glfw opengl32 gdi32)