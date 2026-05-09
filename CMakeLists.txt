cmake_minimum_required(VERSION 3.30)
project(EstruturasDeDadosCompactas C CXX)


option(BUILD_TESTS "Habilita a compilação dos testes" ON)

add_subdirectory(src)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
