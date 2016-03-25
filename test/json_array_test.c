/*
 * json_array_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "../src/minijson.h"

#include <stdio.h>

int main()
{
    string_t buf = NULL;

    json_array_t * json_array = json_array_new();
    json_array_add(json_array, json_string_new("Circle"));
    json_array_add(json_array, json_int_new(100));
    json_array_add(json_array, json_int_new(200));
    json_array_add(json_array, json_float_new(20.98));

    json_object_t * style = json_object_new();
    json_object_add(style, "color", json_string_new("red"));
    
    json_array_add(json_array, style);

    json_to_string(json_array, &buf);

    printf("%s\n", buf);

    json_destroy(json_array);

    return 0;
}
