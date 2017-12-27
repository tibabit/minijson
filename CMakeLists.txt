cmake_minimum_required(VERSION 2.6)
project(minijson C)

add_definitions(-g)


find_package(BISON)
if (BISON_FOUND)
    BISON_TARGET(parser
        "${CMAKE_CURRENT_SOURCE_DIR}/parser.y"
        "${CMAKE_CURRENT_SOURCE_DIR}/minijson_parser.c"
        COMPILE_FLAGS "--name-prefix=minijson"
        )
endif()

find_package(FLEX)
if (FLEX_FOUND)
    FLEX_TARGET(scanner
        "${CMAKE_CURRENT_SOURCE_DIR}/scanner.l"
        "${CMAKE_CURRENT_SOURCE_DIR}/minijson_scanner.c"
        COMPILE_FLAGS "-Pminijson --header-file=${CMAKE_CURRENT_SOURCE_DIR}/minijson_scanner.h -CFa"
        )
endif()

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

file(GLOB minijson_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(minijson "${minijson_SRC}"
    "${BISON_parser_OUTPUTS}"
    "${FLEX_scanner_OUTPUTS}")
# needed at all places
target_include_directories(minijson
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    )

include(CTest)
add_subdirectory(test)
