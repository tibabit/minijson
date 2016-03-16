/*
 * minijson_memory.h
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#ifndef MINIJSON_MEMORY_H_
#define MINIJSON_MEMORY_H_

void *	json_alloc(size_t size);
void	json_free(void * ptr);
void	json_copy(void * dst, void *src, size_t size);

#endif /* MINIJSON_MEMORY_H_ */
