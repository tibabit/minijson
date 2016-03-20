/*
 * minijson_array.c
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

// DECORATION MACROS

#define JSON_ARRAY_BEGIN			'['
#define JSON_ARRAY_END				']'

typedef struct json_array
{
    json_write_fn_t		write;
    json_destroy_fn_t	destroy;
    collection_ptr_t	children;
}json_array_t;

void json_array_write_internal(json_array_t * json, stream_t * stream);
void json_array_destroy_internal(json_array_t * json);

json_array_t * json_array_new(void)
{
    json_array_t * json = json_alloc(sizeof(json_array_t));
    json->children = collection_new();

    CHECK_NULL(json);

    json->write = (json_write_fn_t)json_array_write_internal;
    json->destroy = (json_destroy_fn_t)json_array_destroy_internal;

    return json;
}

void json_array_add(json_array_t * json, void * item)
{
    collection_add(json->children, item);
}

void json_array_destroy_internal(json_array_t * json)
{
    int i = 0;
    if (json == NULL)
    {
        return;
    }
    if (json->children)
    {
        for(i = 0; i < json->children->count; i++)
        {
            json_base_t * child = (json_base_t *)collection_at(json->children, i);

            child->destroy(child);
        }
        collection_destroy(json->children);
    }
    json_free(json);
}

void json_array_write_internal(json_array_t * json, stream_t * stream)
{
    int i = 0;
    fprintf(stream, "%c\n", JSON_ARRAY_BEGIN);

    for(i = 0; i < json->children->count; i++)
    {
        json_base_t * child = (json_base_t *)collection_at(json->children, i);

        child->write(child, stream);
        fprintf(stream, "%s\n", i == json->children->count - 1 ? "" : ",");
    }

    fprintf(stream, "%c\n", JSON_ARRAY_END);
}
