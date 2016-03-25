#ifndef MINIJSON_CONF_H_
#define MINIJSON_CONF_H_

#include "minijson_internal.h"

typedef struct json_conf
{
    int         level;
    int         indent;
    string_t    new_line;
    string_t    level_spaces;
    void        (* set_level)(json_conf_t *self, int);
}json_conf_t;

void json_conf_set_level_internal(json_conf_t * conf, int level);
json_conf_t * json_conf_new();
void json_conf_destroy(json_conf_t * conf);

#endif /* MINIJSON_CONF_H */
