#include <string.h>
#include <stdio.h>

#include "minijson.h"
#include "minijson_internal.h"
#include "minijson_memory.h"


typedef struct json_string
{
    json_write_fn_t   write;
    json_destroy_fn_t destroy;
    string_t          value;
}json_string_t;

void json_string_write_internal(json_string_t * json, stream_t * stream);
void json_string_destroy_internal(json_string_t * json);

json_string_t* json_string_new(string_t value)
{
    json_string_t *json = json_alloc(sizeof(json_string_t));
    CHECK_NULL(json);

    json->value   = strdup(value);
    json->write   = (json_write_fn_t)json_string_write_internal;
    json->destroy = (json_destroy_fn_t)json_string_destroy_internal;

    return json;
}

void json_string_write_internal(json_string_t * json, stream_t * stream)
{
    printf("\"%s\"", json->value);
}
void json_string_destroy_internal(json_string_t * json)
{
    if(!json)
    {
        return;
    }
    if(json->value)
    {
        json_free(json->value);
    }
    json_free(json);
}

string_t json_string_get(json_string_t * json)
{
    return json->value;
}

void json_string_set(json_string_t * json, string_t value)
{
    if (json->value)
    {
        json_free(json->value);
    }
    json->value = strdup(value);
}
