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
#include "minijson_conf.h"
#include "minijson_stream.h"



json_stream_t * json_stream_new();

/*************** Begin: I/O *****************/

size_t json_print(void * json)
{
    json_conf_t * conf = json_conf_new();

    json_base_t * json_base = (json_base_t *)json;
    json_stream_t * stream = json_stream_new(JSON_STREAM_FILE, (void**)stdout);
    size_t len = json_base->write(json, conf, stream);

    json_conf_destroy(conf);
    json_stream_destroy(stream);

    return len;
}

void json_destroy(void * json)
{
    json_base_t * json_base = (json_base_t *)json;
    json_base->destroy(json);
}

/*************** End: I/O *****************/
