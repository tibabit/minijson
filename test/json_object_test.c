/*
 * json_object_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "minijson.h"


int main()
{
	json_object_t * json_obj = json_object_new();
	json_object_add(json_obj, "height", json_int_new(100));
	json_object_add(json_obj, "width", json_int_new(200));

	json_print(json_obj);

	json_destroy(json_obj);

	return 0;
}
