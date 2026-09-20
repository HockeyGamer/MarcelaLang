cmake_minimum_required(VERSION 3.20)

project(MarcelaLang VERSION 0.01 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(marcela_compiler
    main.c
    lexer.c
    parser.c
    ast.c
    codegen.c
    semantic.c
)

target_include_directories(marcela_compiler PRIVATE include)

set_target_properties(marcela_compiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)