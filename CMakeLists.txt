cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# Add dependencies
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/entt)

# Manually add glad since it doesn't have CMakeLists
set(GLAD_SOURCES dependencies/glad/glad.c)
set(GLAD_HEADERS dependencies/glad/glad.h)

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE HEADER_FILES "${SOURCE_PATH}/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_PATH}/*.cpp")

add_executable(${PROJECT_NAME} src/Game.cpp ${GLAD_SOURCES} ${GLAD_HEADERS} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/glad)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/glfw/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/dependencies)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/glm)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/entt/single_include)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL glfw)