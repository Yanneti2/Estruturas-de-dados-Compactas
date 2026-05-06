add_library(utils
        stack.cpp
        queue.cpp
        ll2.cpp
        dll.cpp
        dfs.cpp
)

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
