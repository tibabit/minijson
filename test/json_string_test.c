#include "../src/minijson.h"
#include "assert/assert.h"

module(json_string)
{
    suite("testing json_string")
    {
        test("json_string_new")
        {
            json_string_t *string = json_string_new("");
            expect_int((long)string) to not be equal(0);
            json_destroy(string);
        } end

        test("json_string_write")
        {
            json_string_t *string = json_string_new("Hello World!");
            json_print(string);
            json_destroy(string);

        } end
    } end
}

