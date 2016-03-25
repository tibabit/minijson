#include "minijson_stream.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "minijson_memory.h"

#define BUF_SIZE        64 /* allocate 64 bytes at once */

#if _WIN32 || _WIN64
#define NULL_DIVICE     "NUL"
#else
#define NULL_DIVICE     "/dev/null"
#endif 


size_t json_stream_write_buffer_internal(json_stream_t * json_stream, string_t format, ...);
size_t json_stream_write_stream_internal(json_stream_t * json_stream, string_t format, ...);

json_stream_t * json_stream_new(json_stream_type_t type, void **ptr)
{
    json_stream_t * json_stream = json_alloc(sizeof(json_stream_t));

    CHECK_NULL(json_stream);

    if (type == JSON_STREAM_BUFFER)
    {
        json_stream->write = json_stream_write_buffer_internal;
        json_stream->buffer.ptr = (string_t*)ptr;
    }
    else
    {
        json_stream->write = json_stream_write_stream_internal;
        json_stream->stream = (FILE*) ptr;
    }

    json_stream->null = fopen(NULL_DIVICE, "w");

    if (json_stream->null == NULL)
    {
        json_stream_destroy(json_stream);
        return NULL;
    }

    return json_stream;
}
void json_stream_destroy(json_stream_t * json_stream)
{
    json_free(json_stream);
}

size_t json_stream_write_buffer_internal(json_stream_t * json_stream, string_t format, ...)
{
    va_list args;
    va_start(args, format);

    size_t len = vfprintf(json_stream->null, format, args);

    va_end(args);

    if (json_stream->buffer.size + len >= json_stream->buffer.capacity)
    {
        size_t needed = ((len / BUF_SIZE) + 1) * BUF_SIZE;

        *(json_stream->buffer.ptr) = realloc(*(json_stream->buffer.ptr),
                json_stream->buffer.capacity + needed);
        json_stream->buffer.capacity += needed;
    }

    va_start(args, format);

    len = vsprintf(*(json_stream->buffer.ptr) + json_stream->buffer.size, format, args);

    va_end(args);

    json_stream->buffer.size += len;

    return len;
}
size_t json_stream_write_stream_internal(json_stream_t * json_stream, string_t format, ...)
{
    va_list args;
    va_start(args, format);

    size_t len = vfprintf(json_stream->stream, format, args);

    va_end(args);

    return len;
}
