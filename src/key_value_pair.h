/*
 * json_tuple.h
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#ifndef KEY_VALUE_PAIR_H_
#define KEY_VALUE_PAIR_H_

typedef struct _key_value_pair key_value_pair_t;

key_value_pair_t *	key_value_pair_new		(const char * key, void * value);
void 			key_value_pair_destroy		(key_value_pair_t * pair);
char *			key_value_pair_get_key		(key_value_pair_t * pair);
void *			key_value_pair_get_value	(key_value_pair_t * pair);

#endif /* KEY_VALUE_PAIR_H_ */
