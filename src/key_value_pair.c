/*
 * json_tuple.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "key_value_pair.h"

#include <stdlib.h>
#include <string.h>

#include "minijson_internal.h"
#include "minijson_memory.h"

typedef struct _key_value_pair
{
	char *	key;
	void *	value;
}key_value_pair_t;


key_value_pair_t * key_value_pair_new(const char *key, void *value)
{
	key_value_pair_t * pair = json_alloc(sizeof(key_value_pair_t));

	CHECK_NULL(pair);

	pair->key = strdup(key);
	pair->value = value;

	return pair;
}

void key_value_pair_destroy(key_value_pair_t * pair)
{
	if(pair == NULL)
	{
		return;
	}
	json_free(pair->key);
	json_free(pair);
}

char * key_value_pair_get_key(key_value_pair_t * pair)
{
	return pair->key;
}
void * key_value_pair_get_value(key_value_pair_t * pair)
{
	return pair->value;
}
