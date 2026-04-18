cmake_minimum_required(VERSION 3.30)
project(EstruturasDeDadosCompactas CXX)


# add_subdirectory(GPT-originals)

# add_subdirectory(utils)


include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(libbitvector
        bitvector.cpp
)


add_library(libjacobson
        jacobsonrank.cpp
)
