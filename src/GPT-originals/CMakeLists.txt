add_library(libgpt
        bitvectorRRR.cpp
        endian.c
        uvector.cpp
)

target_include_directories(libgpt PUBLIC ${CMAKE_SOURCE_DIR}/include)
