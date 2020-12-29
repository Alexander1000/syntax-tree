cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(syntax-tree)

set(SYNTAX_TREE_SHARED_SOURCES
    src/lexer.cpp
    src/token/token.cpp
)

set(SYNTAX_TREE_SOURCES
    src/main.cpp
    ${SYNTAX_TREE_SHARED_SOURCES}
)

include_directories(
    include
    /usr/local/include
)

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SYNTAX_TREE_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
)