/*
 * minijson.c
 *
 *  Created on: 15-Mar-2016
 *      Author: vikash
 */

#include "minijson.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "minijson_memory.h"

void json_conf_set_level_internal(json_conf_t * conf, int level)
{
    int num_spaces = 0;
    if (level == 0)
    {
        json_free(conf->level_spaces);
        conf->level_spaces = NULL;
        return;
    }
    num_spaces = level * conf->indent;
    conf->level = level;
    conf->level_spaces = realloc(conf->level_spaces, num_spaces + 1);
    memset(conf->level_spaces, ' ', num_spaces);
        
    conf->level_spaces[num_spaces] = 0;
}

json_conf_t * json_conf_new()
{
    json_conf_t * conf = json_alloc(sizeof(json_conf_t));

    CHECK_NULL(conf);

    conf->level    = 0;
    conf->indent   = 4; // default 4 space indentation
    conf->new_line = json_alloc(2); // '\n'
    conf->set_level = json_conf_set_level_internal;

    sprintf(conf->new_line, "\n");
    json_conf_set_level_internal(conf, conf->level);

    return conf;
}

void json_conf_destroy(json_conf_t * conf)
{
    if(!conf)
    {
        return;
    }
    json_free(conf->new_line);
    json_free(conf->level_spaces);
    json_free(conf);
}

/*************** Begin: I/O *****************/

void json_print(void * json)
{
    json_conf_t * conf = json_conf_new();

    json_base_t * json_base = (json_base_t *)json;
    json_base->write(json, conf, stdout);

    json_conf_destroy(conf);
}

//void json_sprint(void * json, string_t buffer, size_t maxlen, size_t * outlen)
//{
//    memset(buffer, 0x0, maxlen);
//    json_base_t * json_base = (json_base_t *)json;
//    json_base->write(json, buffer);
//}
void json_destroy(void * json)
{
    json_base_t * json_base = (json_base_t *)json;
    json_base->destroy(json);
}

/*************** End: I/O *****************/
