cmake_minimum_required(VERSION 3.10.0)
project(sandbox VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# Add dependencies
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)

# Manually add glad since it doesn't have CMakeLists
set(GLAD_SOURCES dependencies/glad/glad.c)
set(GLAD_INCLUDE dependencies/glad)

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE HPPS "${SOURCE_PATH}/*.hpp")
file(GLOB_RECURSE HS "${SOURCE_PATH}/*.h")
file(GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp")
file(GLOB_RECURSE CS "${SOURCE_PATH}/*.c")

list(REMOVE_ITEM CPPS "${SOURCE_PATH}/main.cpp")

add_executable(sandbox ${HPPS} ${HS} ${CPPS} ${CS} ${GLAD_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_include_directories(sandbox PRIVATE src)
target_include_directories(sandbox PRIVATE ${GLAD_INCLUDE})
target_include_directories(sandbox PRIVATE dependencies/glfw/include)
target_include_directories(sandbox PRIVATE ${PROJECT_SOURCE_DIR}/dependencies)

target_link_libraries(sandbox PRIVATE OpenGL::OpenGL glfw)