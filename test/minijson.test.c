/*
 * json_array_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include <stdio.h>
#include <stdlib.h>

#include "minijson.h"
#include "assertc.h"


module (minijson)
{
    suite("json array")
    {
        test("#new")
        {
            json_array_t * json_array = json_array_new();
            expect_ptr(json_array) to not be equal(NULL);
            json_destroy(json_array);
        } end

        test("#add")
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
        test("#count")
        {
            json_array_t * json_array = json_array_new();
            json_array_add(json_array, json_string_new("Circle"));
            json_array_add(json_array, json_int_new(100));
            json_array_add(json_array, json_int_new(200));

            expect_int(json_array_count(json_array)) to be equal(3);

            json_destroy(json_array);
        } end
        test("#get")
        {
            json_int_t *jint;
            json_array_t * json_array = json_array_new();
            json_array_add(json_array, json_int_new(100));

            expect_int(json_array_count(json_array)) to be equal(1);
            jint = (json_int_t*)json_array_get(json_array, 0);

            expect_int(json_int_get(jint)) to be equal(100);
            expect_ptr(json_array_get(json_array, 2)) to be equal(NULL);

            json_destroy(json_array);
        } end
    } end
    suite("json object")
    {
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
