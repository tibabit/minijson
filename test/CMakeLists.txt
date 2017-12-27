add_subdirectory(assertc)

macro(test testname filename)
    message(STATUS "Adding test ${testname} <-- ${filename}")
    add_executable(${testname} ${filename})
    target_link_libraries(${testname} minijson assertc)
    add_test(${testname}_test ${testname})
endmacro()

test(collection ${CMAKE_CURRENT_SOURCE_DIR}/collection_test.c)
test(key_value_pair ${CMAKE_CURRENT_SOURCE_DIR}/key_value_pair_test.c)
test(json_stream ${CMAKE_CURRENT_SOURCE_DIR}/json_stream.test.c)
test(minijson_api ${CMAKE_CURRENT_SOURCE_DIR}/minijson.test.c)
test(parser ${CMAKE_CURRENT_SOURCE_DIR}/parser_test.c)

