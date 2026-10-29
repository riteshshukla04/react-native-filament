cmake_minimum_required(VERSION 3.22.1)
project(NitroFilamentPhysics)

set(PACKAGE_NAME NitroFilamentPhysics)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE RNFP_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/main/cpp/*.cpp"
  "${CMAKE_SOURCE_DIR}/../cpp/*.cpp"
)
add_library(${PACKAGE_NAME} SHARED ${RNFP_SOURCES})

file(GLOB_RECURSE BULLET_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/../vendor/bullet3/src/*.cpp")
add_library(bullet3 STATIC ${BULLET_SOURCES})
target_include_directories(bullet3 SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/../vendor/bullet3/src")
target_compile_options(bullet3 PRIVATE -w)
set_target_properties(bullet3 PROPERTIES POSITION_INDEPENDENT_CODE ON)

include(${CMAKE_SOURCE_DIR}/../nitrogen/generated/android/NitroFilamentPhysics+autolinking.cmake)

target_include_directories(${PACKAGE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../cpp")

find_package(react-native-filament REQUIRED CONFIG)

find_library(LOG_LIB log)
target_link_libraries(${PACKAGE_NAME} ${LOG_LIB} bullet3 react-native-filament::NitroFilament)
target_link_options(${PACKAGE_NAME} PRIVATE "-Wl,--no-undefined" "-Wl,--gc-sections")
