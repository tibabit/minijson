/*
 * minijson_object.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "minijson_internal.h"
#include "minijson.h"
#include "minijson_memory.h"
#include "collection.h"
#include "key_value_pair.h"
#include "minijson_stream.h"
#include "minijson_conf.h"

// DECORATION MACROS

#define JSON_OBJECT_BEGIN       '{'
#define JSON_OBJECT_END         '}'

typedef struct json_object
{
    json_write_fn_t     write;
    json_destroy_fn_t   destroy;
    collection_t *      children;
}json_object_t;

size_t json_object_write_internal(json_object_t * json,
        json_conf_t * json_conf,
        json_stream_t * stream);
void json_object_destroy_internal(json_object_t * json_obj);

json_object_t * json_object_new(void)
{
    json_object_t * json_obj = json_alloc(sizeof(json_object_t));
    json_obj->children = collection_new(sizeof(json_base_t *));

    CHECK_NULL(json_obj);

    json_obj->write = (json_write_fn_t)json_object_write_internal;
    json_obj->destroy = (json_destroy_fn_t)json_object_destroy_internal;

    return json_obj;
}

void json_object_add(json_object_t * json_obj, const string_t key, void * item)
{
    key_value_pair_t * pair = key_value_pair_new(key, item);

    collection_add(json_obj->children, &pair);
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
        for(i = 0; i < collection_count(json_obj->children); i++)
        {
            key_value_pair_t * pair;
            collection_at(json_obj->children, i, &pair);
            json_base_t * child = (json_base_t *)(key_value_pair_get_value(pair));

            child->destroy(child);
            key_value_pair_destroy(pair);
        }
        collection_destroy(json_obj->children);
    }
    json_free(json_obj);
}

size_t json_object_write_internal(json_object_t * json,
        json_conf_t * json_conf,
        json_stream_t * stream)
{
    int i = 0;
    size_t total_chars = 0, num_children = 0;

    total_chars += stream->write(stream, "%c", JSON_OBJECT_BEGIN);
    total_chars += stream->write(stream, "%s", json_conf->new_line);

    json_conf->set_level(json_conf, json_conf->level + 1);
    num_children = collection_count(json->children);

    for(i = 0; i < num_children; i++)
    {
        key_value_pair_t * pair = NULL;
        collection_at(json->children, i, &pair);
        json_base_t * child = (json_base_t *)(key_value_pair_get_value(pair));

        total_chars += stream->write(stream, "%s", json_conf->level_spaces);

        total_chars += stream->write(stream, "\"%s\" : ", key_value_pair_get_key(pair));
        total_chars += child->write(child, json_conf, stream);

        total_chars += stream->write(stream, "%s", i == num_children - 1 ? "" : ",");
        total_chars += stream->write(stream, "%s", json_conf->new_line);

    }

    json_conf->set_level(json_conf, json_conf->level - 1);
    total_chars += stream->write(stream, "%s", json_conf->level_spaces);
    total_chars += stream->write(stream, "%c", JSON_OBJECT_END);

    return total_chars;
}

int json_object_keys(json_object_t * json, string_t ** keys)
{
    int i, num_keys = collection_count(json->children);
    if (num_keys == 0)
    {
        return num_keys;
    }
    *keys = json_alloc(num_keys * sizeof(string_t));

    for(i = 0; i < num_keys; i++)
    {
        key_value_pair_t * pair;
        collection_at(json->children, i, &pair);
        (*keys)[i] = strdup(key_value_pair_get_key(pair));
    }
    return num_keys;
}

json_base_t * json_object_get(json_object_t * json, const string_t key)
{
    int i, num_keys = collection_count(json->children);
    if (num_keys == 0)
    {
        return NULL;
    }

    for(i = 0; i < num_keys; i++)
    {
        key_value_pair_t * pair;
        collection_at(json->children, i, &pair);
        string_t current_key = key_value_pair_get_key(pair);
        if (strcmp(key, current_key) == 0)
        {
            return (json_base_t *)(key_value_pair_get_value(pair));
        }
    }
    return NULL;
}
