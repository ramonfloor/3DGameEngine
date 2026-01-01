cmake_minimum_required(VERSION 3.10.0)
project(sandbox VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )

file( GLOB_RECURSE HPPS "${SOURCE_PATH}/*.hpp" )
file( GLOB_RECURSE HS "${SOURCE_PATH}/*.h" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )
file( GLOB_RECURSE CS "${SOURCE_PATH}/*.c" )

list(REMOVE_ITEM CPPS "${SOURCE_PATH}/main.cpp")

add_executable(sandbox ${HPPS} ${HS} ${CPPS} ${CS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(sandbox glfw)