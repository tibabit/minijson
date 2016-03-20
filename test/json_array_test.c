/*
 * json_array_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "../src/minijson.h"

int main()
{
    json_array_t * json_array = json_array_new();
    json_array_add(json_array, json_string_new("Circle"));
    json_array_add(json_array, json_int_new(100));
    json_array_add(json_array, json_int_new(200));
    json_array_add(json_array, json_float_new(20.98));

    json_print(json_array);

    json_destroy(json_array);

    return 0;
}
