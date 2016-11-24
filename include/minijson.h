/*
 * minijson.h
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#ifndef MINIJSON_H_
#define MINIJSON_H_

#include "minijson_internal.h"

/**************** BEGIN: JSON Object ****************/

json_object_t *	json_object_new(void);
void            json_object_add(json_object_t * json_obj, const string_t key, void * item);
int             json_object_keys(json_object_t * json, string_t ** keys);
json_base_t *   json_object_get(json_object_t * json, const string_t key);

/**************** END: JSON Object ****************/

/**************** BEGIN: JSON Array ****************/

json_array_t *  json_array_new(void);
void            json_array_add(json_array_t * json, void * item);

/**************** END: JSON Array ****************/

/**************** BEGIN: JSON int ****************/

json_int_t*	json_int_new(int value);
int             json_int_get(json_int_t * json);
void            json_int_set(json_int_t * json, int value);

/**************** END: JSON int ****************/

/**************** BEGIN: JSON unsigned int ****************/

json_uint_t*	json_uint_new(uint value);
uint            json_uint_get(json_uint_t * json);
void            json_uint_set(json_uint_t * json, uint value);

/**************** END: JSON unsigned int ****************/

/**************** BEGIN: JSON double ****************/

json_double_t*	json_double_new(double value);
double          json_double_get(json_double_t * json);
void            json_double_set(json_double_t * json, double value);

/**************** END: JSON double ****************/

/**************** BEGIN: JSON char * / string ****************/

json_string_t*	json_string_new(string_t value);
string_t        json_string_get(json_string_t * json);
void            json_string_set(json_string_t * json, string_t value);

/**************** END: JSON char * / string ****************/

/*************** I/O *************************/

size_t json_print       (void * json);
size_t json_print_pretty(void * json);
size_t json_to_string   (void * json, string_t * buf);

void json_destroy       (void * json);


#endif /* MINIJSON_H_ */
