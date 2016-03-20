/*
 * minijson_object.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */


#include <stdio.h>
#include <string.h>

#include "minijson_internal.h"
#include "minijson.h"
#include "minijson_memory.h"
#include "collection.h"
#include "key_value_pair.h"

// DECORATION MACROS

#define JSON_OBJECT_BEGIN			'{'
#define JSON_OBJECT_END				'}'

typedef struct json_object
{
	json_write_fn_t		write;
	json_destroy_fn_t	destroy;
	collection_ptr_t	children;
}json_object_t;

void json_object_write_internal(json_object_t * json, stream_t * stream);
void json_object_destroy_internal(json_object_t * json_obj);

json_object_t * json_object_new(void)
{
	json_object_t * json_obj = json_alloc(sizeof(json_object_t));
	json_obj->children = collection_new();

	CHECK_NULL(json_obj);

	json_obj->write = (json_write_fn_t)json_object_write_internal;
	json_obj->destroy = (json_destroy_fn_t)json_object_destroy_internal;

	return json_obj;
}

void json_object_add(json_object_t * json_obj, const string_t key, void * item)
{
	key_value_pair_t * pair = key_value_pair_new(key, item);
	collection_add(json_obj->children, pair);
}

void json_object_destroy_internal(json_object_t * json_obj)
{
	int i = 0;
	if (json_obj == NULL)
	{
		return;
	}
	if (json_obj->children)
	{
		for(i = 0; i < json_obj->children->count; i++)
		{
			key_value_pair_t * pair = (key_value_pair_t *)collection_at(json_obj->children, i);
			json_base_t * child = (json_base_t *)(key_value_pair_get_value(pair));

			child->destroy(child);
			key_value_pair_destroy(pair);
		}
		collection_destroy(json_obj->children);
	}
	json_free(json_obj);
}

void json_object_write_internal(json_object_t * json, stream_t * stream)
{
	int i = 0;
	fprintf(stream, "%c\n", JSON_OBJECT_BEGIN);

	for(i = 0; i < json->children->count; i++)
	{
		key_value_pair_t * pair = (key_value_pair_t *)collection_at(json->children, i);
		json_base_t * child = (json_base_t *)(key_value_pair_get_value(pair));

		fprintf(stream, "\"%s\" : ", key_value_pair_get_key(pair));
		child->write(child, stream);
		fprintf(stream, "%s\n", i == json->children->count - 1 ? "" : ",");
	}

	fprintf(stream, "%c\n", JSON_OBJECT_END);
}
