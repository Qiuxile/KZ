cmake_minimum_required(VERSION 3.10)
project(KZ VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/ast)

# main.cpp
add_executable(kz main.cpp)

target_link_libraries(kz
    PRIVATE
    lexer_lib
)
