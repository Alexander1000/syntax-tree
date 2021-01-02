cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

project(syntax-tree)

set(SYNTAX_TREE_SHARED_SOURCES
    src/lexer.cpp
    src/token/token.cpp
    src/token/type-token.cpp
    src/token/open-token.cpp
    src/token/close-token.cpp
    src/token/name-token.cpp
    src/token/double-dot-token.cpp
    src/token/open-brace-token.cpp
    src/token/close-brace-token.cpp
    src/token/match-value-token.cpp
    src/token/token_map.cpp
    src/position.cpp
    src/syntax/rule.cpp
    src/syntax/rule_match.cpp
    src/syntax/syntax_element.cpp
    src/syntax/tree.cpp
    src/syntax/tree_parse_tokens.cpp
    src/render/render.cpp
    src/config.cpp
    src/injector.cpp
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

set(PUBLIC_HEADERS
    include/syntax-tree.h
)

#--------------
# Static library
#--------------

project(syntax-tree-lib VERSION 0.0.1 DESCRIPTION "syntax-tree lib")

add_library(${PROJECT_NAME} STATIC ${SYNTAX_TREE_SHARED_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "syntax-tree-lib")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install(FILES ${PUBLIC_HEADERS} DESTINATION include)

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT library
)
