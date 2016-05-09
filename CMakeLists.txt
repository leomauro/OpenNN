cmake_minimum_required(VERSION 3.2)
project(OpenNN)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")

add_subdirectory(opennn)
include_directories(opennn)

add_subdirectory(examples)

add_subdirectory(blank)

add_subdirectory(tests)

set(CPACK_GENERATOR "TGZ")
include(CPack)
