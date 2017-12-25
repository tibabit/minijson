/*
 * json_array_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "minijson.h"
#include "assertc.h"

#include <stdio.h>

module (minijson)
{
    suite("minijson")
    {
        test("#json_array")
        {
            string_t buf = NULL;

            json_array_t * json_array = json_array_new();
            json_array_add(json_array, json_string_new("Circle"));
            json_array_add(json_array, json_int_new(100));
            json_array_add(json_array, json_int_new(200));

            json_object_t * style = json_object_new();
            json_object_add(style, "color", json_string_new("red"));

            json_array_add(json_array, style);

            json_to_string(json_array, &buf);

            expect_string(buf) to be equal("[\"Circle\",100,200,{\"color\":\"red\"}]");

            json_destroy(json_array);

            free(buf);

        } end

        test("#json_object")
        {
            string_t buf = NULL;
            int num_keys, i;

            json_object_t * shape = json_object_new();
            json_object_add(shape, "name", json_string_new("Circle"));
            json_object_add(shape, "height", json_int_new(100));
            json_object_add(shape, "width", json_int_new(200));


            json_object_t * style = json_object_new();
            json_object_add(style, "color", json_string_new("red"));

            json_object_add(shape, "style", style);

            json_to_string(shape, &buf);

            expect_string(buf) to be equal("{\"name\":\"Circle\",\"height\":100,\"width\":200,\"style\":{\"color\":\"red\"}}");

            json_destroy(shape);

            free(buf);
        } end
    } end
}

int main()
{
    register_module(minijson);
    run_all();

    return 0;
}
