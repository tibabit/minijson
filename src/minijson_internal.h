/*
 * minijson_internal.h
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#ifndef MINIJSON_INTERNAL_H_
#define MINIJSON_INTERNAL_H_


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
typedef void            stream_t;
typedef struct          json_base json_base_t;
typedef char *          string_t;
typedef unsigned int    uint;
typedef unsigned short  ushort;
typedef unsigned long   ulong;
typedef long double     ldouble;

/****************** function types *****************/
typedef void (*json_write_fn_t)		(json_base_t * json, stream_t * stream);
typedef void (*json_destroy_fn_t)	(json_base_t * json);


/**************** JSON types ******************/

/**
 * base type for all type of JSON objects
 */
typedef struct json_base
{
    json_write_fn_t 	write;
    json_destroy_fn_t	destroy;
}json_base_t;


typedef struct json_object 		json_object_t;		// represents an JSON objects
typedef struct json_array 		json_array_t;		// represents an JSON objects
typedef struct json_primitive	        json_primitive_t;
typedef json_primitive_t		json_int_t;		// int
typedef json_primitive_t		json_uint_t;		// unsigned int
typedef json_primitive_t		json_short_t;		// short
typedef json_primitive_t		json_ushort_t;		// unsigned short
typedef json_primitive_t		json_long_t;
typedef json_primitive_t		json_ulong_t;		// unsigned long
typedef json_primitive_t		json_float_t;
typedef json_primitive_t		json_double_t;
typedef json_primitive_t		json_ldouble_t;		// long float
typedef struct json_string		json_string_t;		// string

#endif /* MINIJSON_INTERNAL_H_ */
