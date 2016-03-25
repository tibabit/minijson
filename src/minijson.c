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
size_t json_print_internal(void * json, int indent, bool print_new_line);

/*************** Begin: I/O *****************/

size_t json_print_internal(void * json, int indent, bool print_new_line)
{
    json_conf_t * conf = json_conf_new(indent, print_new_line);

    json_base_t * json_base = (json_base_t *)json;
    json_stream_t * stream = json_stream_new(JSON_STREAM_FILE, (void**)stdout);
    size_t len = json_base->write(json, conf, stream);

    json_conf_destroy(conf);
    json_stream_destroy(stream);

    return len;
}

size_t json_print(void * json)
{
    return json_print_internal(json, 0, false);
}
size_t json_print_pretty(void * json)
{
    return json_print_internal(json, 4, true);
}
size_t json_to_string(void * json, string_t ** buf)
{
    json_conf_t * conf = json_conf_new(0, false);

    json_base_t * json_base = (json_base_t *)json;
    json_stream_t * stream = json_stream_new(JSON_STREAM_BUFFER, (void**)buf);
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
