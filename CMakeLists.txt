cmake_minimum_required(VERSION 3.10)

project(bnflite "CXX")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(variables ${SOURCE_DIR}/variables.cpp)
add_executable(libraryClassesDsc ${SOURCE_DIR}/libraryClassesDsc.cpp)
add_executable(ini ${SOURCE_DIR}/ini.cpp)
add_executable(cfg ${SOURCE_DIR}/cfg.cpp)
add_executable(calc ${SOURCE_DIR}/calc.cpp)
add_executable(cmd ${SOURCE_DIR}/cmd.cpp)

target_include_directories(variables PUBLIC ${INCLUDE_DIR})
target_include_directories(libraryClassesDsc PUBLIC ${INCLUDE_DIR})
target_include_directories(ini PUBLIC ${INCLUDE_DIR})
target_include_directories(cfg PUBLIC ${INCLUDE_DIR})
target_include_directories(calc PUBLIC ${INCLUDE_DIR})
target_include_directories(cmd PUBLIC ${INCLUDE_DIR})