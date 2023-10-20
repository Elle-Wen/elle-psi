cmake_minimum_required (VERSION 3.0)
project (elle-psi)
set(NAME "elle-psi")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/emp-base.cmake)

FIND_PACKAGE(emp-sh2pc REQUIRED)
INCLUDE_DIRECTORIES(${EMP-SH2PC_INCLUDE_DIRS})

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
