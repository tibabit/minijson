cmake_minimum_required(VERSION 2.6)
project(minijson C)

# needed at all places
include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(BISON)
if (BISON_FOUND)
    BISON_TARGET(parser "${PROJECT_SOURCE_DIR}/parser.y" "${PROJECT_SOURCE_DIR}/minijson_parser.c")
endif()

find_package(FLEX)
if (FLEX_FOUND)
    FLEX_TARGET(scanner "${PROJECT_SOURCE_DIR}/scanner.l" "${PROJECT_SOURCE_DIR}/minijson_scanner.c")
endif()

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

file(GLOB minijson_SRC "${PROJECT_SOURCE_DIR}/src/*.c")

add_library(minijson "${minijson_SRC}"
    "${BISON_parser_OUTPUTS}"
    "${FLEX_scanner_OUTPUTS}")


include(CTest)
add_subdirectory(test)
