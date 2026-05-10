set(LEXER_SOURCES
    Lexer.cpp
)

# Create a static library for the lexer
add_library(lexer_lib STATIC ${LEXER_SOURCES})

target_include_directories(lexer_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)