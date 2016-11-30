
# needed at all places
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(minijson_parser_test "${PROJECT_SOURCE_DIR}/test/parser_test.c")

target_link_libraries(minijson_parser_test minijson)

