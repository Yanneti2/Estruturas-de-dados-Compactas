add_library(libgpt
        endian.c
        uarray.c TODO: Pedir o arquivo abrevs.h para o GPT
        bits.cpp
)

target_include_directories(libgpt PUBLIC ${CMAKE_SOURCE_DIR}/include)
