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
#include "minijson_conf.h"
#include "minijson_stream.h"

// DECORATION MACROS

#define JSON_ARRAY_BEGIN    '['
#define JSON_ARRAY_END      ']'

typedef struct json_array
{
    json_write_fn_t	write;
    json_destroy_fn_t	destroy;
    collection_t *	children;
}json_array_t;

size_t json_array_write_internal(json_array_t * json,
        json_conf_t * json_conf,
        json_stream_t * stream);
void json_array_destroy_internal(json_array_t * json);

json_array_t * json_array_new(void)
{
    json_array_t * json = json_alloc(sizeof(json_array_t));
    json->children = collection_new(sizeof(json_base_t * ));

    CHECK_NULL(json);

    json->write = (json_write_fn_t)json_array_write_internal;
    json->destroy = (json_destroy_fn_t)json_array_destroy_internal;

    return json;
}

void json_array_add(json_array_t * json, void * item)
{
    collection_add(json->children, &item);
}

void json_array_destroy_internal(json_array_t * json)
{
    int i = 0, count;
    if (json == NULL)
    {
        return;
    }
    count = json_array_count(json);
    for(i = 0; i < count; i++)
    {
        json_base_t * child = json_array_get(json, i);
        child->destroy(child);
    }
    collection_destroy(json->children);
    json_free(json);
}
size_t json_array_count(json_array_t * json)
{
    if (json == NULL || json->children == NULL) return 0;

    return collection_count(json->children);
}

json_base_t* json_array_get(json_array_t * json, size_t index)
{
    size_t count = json_array_count(json);
    if (index >= count) return NULL;

    json_base_t * child = NULL;
    collection_at(json->children, index, &child);

    return child;
}

size_t json_array_write_internal(json_array_t * json,
        json_conf_t * json_conf,
        json_stream_t * stream)
{
    int i = 0;
    size_t total_chars = 0;

    total_chars += stream->write(stream, "%c", JSON_ARRAY_BEGIN);
    total_chars += stream->write(stream, "%s", json_conf->new_line);

    json_conf->set_level(json_conf, json_conf->level + 1);
    for(i = 0; i < collection_count(json->children); i++)
    {
        json_base_t * child;
        collection_at(json->children, i, &child);

        total_chars += stream->write(stream, "%s", json_conf->level_spaces);
        total_chars += child->write(child, json_conf, stream);
        total_chars += stream->write(stream, "%s%s", i == collection_count(json->children) - 1 ? "" : ",",
                json_conf->new_line);
    }

    json_conf->set_level(json_conf, json_conf->level - 1);

    total_chars += stream->write(stream, "%s", json_conf->level_spaces);
    total_chars += stream->write(stream, "%c", JSON_ARRAY_END);

    return total_chars;
}
