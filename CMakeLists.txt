cmake_minimum_required(VERSION 3.16)

project(Clairvoyance)

set(VCPKG_ROOT C:/vcpkg)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(eigen3 3.3 REQUIRED NO_MODULE)

message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")

add_executable(analyzer lib/predictor/analyzer.cpp)

target_link_libraries(analyzer PRIVATE eigen3::Eigen)