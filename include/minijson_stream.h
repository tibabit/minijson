#ifndef MINIJSON_STREAM_H_
#define MINIJSON_STREAM_H_

#include <stdio.h>

#include "minijson_internal.h"

typedef struct json_stream
{
    union
    {
        struct
        {
            string_t *  ptr;
            size_t      size;
            size_t      capacity;
        }buffer;
        void * stream;
    };
    size_t (*write)(json_stream_t * json_stream, string_t format, ...);
    FILE * null;
}json_stream_t;

typedef enum
{
    JSON_STREAM_BUFFER,
    JSON_STREAM_FILE
}json_stream_type_t;

json_stream_t * json_stream_new(json_stream_type_t type, void **ptr);
void json_stream_destroy(json_stream_t * json_stream);

#endif /* MINIJSON_STREAM_H */
