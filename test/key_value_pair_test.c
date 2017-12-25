/*
 * key_value_pair_test.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "assert.h"
#include "key_value_pair.h"

module(key_value_pair)
{
    test("should allocate new memory to key value pair")
    {
        int value = 10;
        key_value_pair_t * pair = key_value_pair_new("key", &value);

        expect_int(pair) to not be equal(NULL);
    } end
    test("should store a number as value")
    {
        int value = 10;
        key_value_pair_t * pair = key_value_pair_new("key", &value);

        char * key = key_value_pair_get_key(pair);
        int * ptr = key_value_pair_get_value(pair);

        expect_string(key) to be equal("key");
        expect_int(*ptr) to be equal(10);
    } end
    test("should store a string as value")
    {
        char * value = "pair_value";
        key_value_pair_t * pair = key_value_pair_new("key", value);

        char * key = key_value_pair_get_key(pair);
        char * ptr = key_value_pair_get_value(pair);

        expect_string(key) to be equal("key");
        expect_string(ptr) to be equal("pair_value");
    } end
}

int main()
{
    register_module(key_value_pair);
    run_all();

    return 0;
}
