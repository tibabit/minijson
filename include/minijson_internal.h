/*
 * minijson_internal.h
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#ifndef MINIJSON_INTERNAL_H_
#define MINIJSON_INTERNAL_H_

#include <string.h>

/*************** CHECK MACROS ***************/
#define CHECK_NULL(ptr)					\
    if ((void*)ptr == NULL)				\
        return NULL;

#ifdef DEBUG
#define debug(fmt, ...)     printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

// common aliases
typedef struct          json_stream json_stream_t;
typedef struct          json_base json_base_t;
typedef struct          json_conf json_conf_t;
typedef char *          string_t;
typedef unsigned int    uint;

/****************** function types *****************/
typedef size_t  (*json_write_fn_t)  (json_base_t * json,
        json_conf_t * json_conf,
        json_stream_t * stream);
typedef void    (*json_destroy_fn_t)(json_base_t * json);


/**************** JSON types ******************/

/**
 * base type for all type of JSON objects
 */
typedef struct json_base
{
    json_write_fn_t 	write;
    json_destroy_fn_t	destroy;
}json_base_t;


typedef struct json_object      json_object_t;		// represents an JSON objects
typedef struct json_array       json_array_t;		// represents an JSON objects
typedef struct json_primitive   json_primitive_t;
typedef json_primitive_t        json_int_t;		// int
typedef json_primitive_t        json_uint_t;		// unsigned int
typedef json_primitive_t        json_double_t;
typedef struct json_string      json_string_t;		// string

#endif /* MINIJSON_INTERNAL_H_ */
