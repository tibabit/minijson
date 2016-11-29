cmake_minimum_required(VERSION 2.6)
project(minijson C)

# needed at all places
include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(BISON)
BISON_TARGET(parser "${PROJECT_SOURCE_DIR}/parser.y" "${PROJECT_SOURCE_DIR}/minijson_parser.c")

find_package(FLEX)
FLEX_TARGET(scanner "${PROJECT_SOURCE_DIR}/scanner.l" "${PROJECT_SOURCE_DIR}/minijson_scanner.c")

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

file(GLOB minijson_SRC src/*.c)

add_library(minijson "${minijson_SRC}"
    "${BISON_parser_OUTPUTS}"
    "${FLEX_scanner_OUTPUTS}")

