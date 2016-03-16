/*
 * minijson.h
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#ifndef MINIJSON_H_
#define MINIJSON_H_

#include "minijson_internal.h"

/**************** Constructors ****************/

json_object_t *		json_object_new(void);
json_int_t *		json_int_new(int value);
json_float_t *		json_float_new(float value);

/*************** JSON type manipulation functions *************************/
void json_object_add(json_object_t * json_obj, const char * const key, void * item);


/*************** I/O *************************/

void json_print		(void * json);
void json_destroy	(void * json);


#endif /* MINIJSON_H_ */
