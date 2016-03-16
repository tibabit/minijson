/*
 * key_value_pair_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "assert/assert.h"
#include "../src/key_value_pair.h"

module(key_value_pair)
{
	test("should allocate new memory to key value pair")
	{
		int value = 10;
        key_value_pair_t * pair = key_value_pair_new("key", &value);

        char * key = key_value_pair_get_key(pair);
        int * ptr = key_value_pair_get_value(pair);

        expect_string(key) to be equal("key");
        expect_int(*ptr) to be equal(10);
	} end
}

int main()
{
	register_module(key_value_pair);
	run_all();

	return 0;
}
