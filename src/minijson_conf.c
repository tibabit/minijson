#include "minijson_conf.h"

#include <stdlib.h>
#include <stdio.h>

#include "minijson_memory.h"

void json_conf_set_level_internal(json_conf_t * conf, int level)
{
    int num_spaces = 0;

    num_spaces = level * conf->indent;
    conf->level = level;
    conf->level_spaces = realloc(conf->level_spaces, num_spaces + 1);
    memset(conf->level_spaces, ' ', num_spaces);

    conf->level_spaces[num_spaces] = 0;
}

json_conf_t * json_conf_new(int indent, bool print_new_line)
{
    json_conf_t * conf = json_alloc(sizeof(json_conf_t));

    CHECK_NULL(conf);

    indent = indent < 0 ? 0 : indent;

    conf->level    = 0;
    conf->indent   = indent;
    conf->new_line = json_alloc(2); // '\n'
    conf->set_level = json_conf_set_level_internal;

    sprintf(conf->new_line, print_new_line ? "\n" : "");
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
