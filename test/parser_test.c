#include <stdio.h>
#include <stdlib.h>
#include "assertc.h"

#include "minijson.h"

module(minijson_parse)
{
    suite("# invalid syntax")
    {
        test("# empty buffer failes")
        {
            json_object_t *json = NULL;

            json = json_parse("", 0);

            expect_ptr(json) to be equal(NULL);
        } end
        test("# NULL buffer failes")
        {
            json_object_t *json = NULL;

            json = json_parse(NULL, 0);

            expect_ptr(json) to be equal(NULL);
        } end
        test("# unmatched curly braces '{' and '}'")
        {
            json_object_t *json = NULL;
            json = json_parse("{", 1);
            expect_ptr(json) to be equal(NULL);

            json = json_parse("}", 1);
            expect_ptr(json) to be equal(NULL);
        } end
        test("# unmatched square brackets '[' and ']'")
        {
            json_object_t *json = NULL;
            json = json_parse("[", 1);
            expect_ptr(json) to be equal(NULL);

            json = json_parse("]", 1);
            expect_ptr(json) to be equal(NULL);
        } end
    } end

    suite("# Correct syntax")
    {
        test("# empty object '{}'")
        {
            json_object_t *json = NULL;
            const string_t input = "{}";
            string_t buf = NULL;
            json = json_parse(input, strlen(input));

            expect_ptr(json) to not be equal(NULL);

            json_to_string(json, &buf);

            expect_string(buf) to be equal(input);

            json_destroy(json);
            free(buf);

        } end
    } end
}

int main()
{
    register_module(minijson_parse);

    run_all();
    return 0;
}
