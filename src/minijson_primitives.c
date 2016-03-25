/*
 * minijson_primitives.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */


#include "minijson_internal.h"

#include <stdio.h>
#include <string.h>

#include "minijson_memory.h"
#include "minijson_stream.h"

#define JSON_PRIMITIVE_NEW_DEFINITION(type_short, type)                                         \
    json_##type_short##_t * json_##type_short##_new(type value)                                 \
    {                                                                                           \
        json_##type_short##_t * json_##type_short = json_alloc(sizeof(json_primitive_t));       \
        json_##type_short->write = (json_write_fn_t)json_##type_short##_write_internal;         \
        json_##type_short->destroy = (json_destroy_fn_t)json_##type_short##_destroy_internal;   \
        json_copy(&json_##type_short->data.value_##type_short, &value, sizeof(type));           \
        return json_##type_short;                                                               \
    }

#define JSON_PRIMITIVE_DESTROY_DEFINITION(type_short)                                   \
    void json_##type_short##_destroy_internal(json_##type_short##_t * json)             \
    {                                                                                   \
        json_primitive_destroy(json);                                                   \
    }

#define JSON_PRIMITIVE_GET_DEFINITION(type_short, type)             \
    type json_##type_short##_get(json_##type_short##_t * json)      \
    {                                                               \
        if (json == NULL)                                           \
        {                                                           \
            return (type)0;                                         \
        }                                                           \
        return json->data.value_##type_short;                       \
    }

#define JSON_PRIMITIVE_SET_DEFINITION(type_short, type)                         \
    void json_##type_short##_set(json_##type_short##_t * json, type value)      \
    {                                                                           \
        if (json == NULL)                                                       \
        {                                                                       \
            return;                                                             \
        }                                                                       \
        json_copy(&json->data.value_##type_short, &value, sizeof(type));        \
    }

#define JSON_PRIMITIVE_WRITE_DEFINITION(type_short, format)                     \
    size_t json_##type_short##_write_internal(json_##type_short##_t * json,     \
            json_conf_t * json_conf,                                            \
            json_stream_t * stream)                                             \
    {                                                                           \
        return stream->write(stream, format, json->data.value_##type_short);    \
    }

typedef struct json_primitive
{
    json_write_fn_t write;
    json_destroy_fn_t   destroy;
    union
    {
        int value_int;
        unsigned int    value_uint;
        double  value_double;
    }data;
}json_primitive_t;


void json_primitive_destroy(json_primitive_t * primitive)
{
    json_free(primitive);
}

JSON_PRIMITIVE_DESTROY_DEFINITION(int)
JSON_PRIMITIVE_DESTROY_DEFINITION(uint)
JSON_PRIMITIVE_DESTROY_DEFINITION(double)

JSON_PRIMITIVE_WRITE_DEFINITION(int,    "%d")
JSON_PRIMITIVE_WRITE_DEFINITION(uint,   "%u")
JSON_PRIMITIVE_WRITE_DEFINITION(double, "%lf")

JSON_PRIMITIVE_NEW_DEFINITION(int,      int)
JSON_PRIMITIVE_NEW_DEFINITION(uint, uint)
JSON_PRIMITIVE_NEW_DEFINITION(double,   double)

JSON_PRIMITIVE_GET_DEFINITION(int,  int)
JSON_PRIMITIVE_GET_DEFINITION(uint, uint)
JSON_PRIMITIVE_GET_DEFINITION(double,   double)

JSON_PRIMITIVE_SET_DEFINITION(int,  int)
JSON_PRIMITIVE_SET_DEFINITION(uint, uint)
JSON_PRIMITIVE_SET_DEFINITION(double,   double)
