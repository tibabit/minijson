/*
 * minijson.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "minijson.h"

#include <stdio.h>


/*************** Begin: I/O *****************/

void json_print(void * json)
{
	json_base_t * json_base = (json_base_t *)json;
	json_base->write(json, stdout);
}

void json_destroy(void * json)
{
	json_base_t * json_base = (json_base_t *)json;
	json_base->destroy(json);
}

/*************** End: I/O *****************/
