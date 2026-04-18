cmake_minimum_required(VERSION 3.30)
project(EstruturasDeDadosCompactas CXX)

enable_language(C)

enable_testing()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_subdirectory(src)
add_subdirectory(tests)