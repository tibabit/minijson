/*
 * json_object_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/minijson.h"

int main()
{
    string_t *keys;
    int num_keys, i;
    json_object_t * shape = json_object_new();
    json_object_add(shape, "name", json_string_new("Circle"));
    json_object_add(shape, "height", json_int_new(100));
    json_object_add(shape, "width", json_int_new(200));
    json_object_add(shape, "sqrt", json_float_new(20.98));


    json_object_t * style = json_object_new();
    json_object_add(style, "color", json_string_new("red"));
    
    json_object_add(shape, "style", style);

    json_print_pretty(shape);

    num_keys = json_object_keys(shape, &keys);

    for (i = 0; i < num_keys; i++)
    {
        free(keys[i]);
    }
    free(keys);

    json_destroy(shape);

    return 0;
}
