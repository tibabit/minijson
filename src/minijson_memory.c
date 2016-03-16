/*
 * minijson_memory.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include <stdlib.h>
#include <string.h>

#define DEFAULT_NUM_ELEMENTS_TO_ALLOCATE		1

void * json_alloc(size_t size)
{
	return calloc(DEFAULT_NUM_ELEMENTS_TO_ALLOCATE, size);
}

void json_free(void * ptr)
{
	if(ptr != NULL)
	{
		free(ptr);
	}
}

void json_copy(void * dst, void *src, size_t size)
{
	if (dst == NULL || src == NULL)
	{
		return;
	}
	memcpy(dst, src, size);
}
