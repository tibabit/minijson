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
    json_object_t * json_obj = json_object_new();
    json_object_add(json_obj, "name", json_string_new("Circle"));
    json_object_add(json_obj, "height", json_int_new(100));
    json_object_add(json_obj, "width", json_int_new(200));
    json_object_add(json_obj, "sqrt", json_float_new(20.98));

    json_print(json_obj);

    num_keys = json_object_keys(json_obj, &keys);

    printf("number of keys : %d\n", num_keys);

    for (i = 0; i < num_keys; i++)
    {
        printf("%s ", keys[i]);
        free(keys[i]);
    }
    free(keys);

    json_destroy(json_obj);

    return 0;
}
