%token      EOF          0      "end of input"
%token      LB          '['
%token      RB          ']'
%token      LCB         '{'
%token      RCB         '}'
%token      COLON       ':'
%token      COMMA       ','

%union
{
    int             _int;
    double          _double;
    unsigned char   _bool:1;
    string_t        _string;
    void*           _json_value;
    json_object_t*  _json_object;
    json_array_t*   _json_array;
    json_object_t*  _json_expr_list;
    json_array_t*   _json_value_list;
}

%token <_int>       INT
%token <_double>    DOUBLE
%token <_bool>      BOOLEAN
%token <_string>    STRING

%type <_json_value>       json_value
%type <_json_object>      json_object
%type <_json_array>       json_array
%type <_json_expr_list>   json_expr_list
%type <_json_value_list>  json_value_list

%code requires
{
#include <stdio.h>
#include "minijson.h"
#include "key_value_pair.h"
}
%code
{
#include <stdio.h>
#include "minijson_scanner.h"
void yyerror(void* scanner, json_object_t** parsed_object, const char *msg);
}

%define api.token.prefix {TOK_}
%pure-parser
%define parse.error verbose
%lex-param {void *scanner}
%parse-param {void *scanner} {json_object_t ** parsed_object}


%%

input:
    json_object     { *parsed_object = $<_json_object>1; }
    | json_array    { *parsed_object = $<_json_array>1;  }
    ;

json_object:
    LCB RCB                       { $$ = json_object_new();   }
    | LCB json_expr_list RCB      { $$ = $<_json_expr_list>2; }
    ;

json_expr_list:
    STRING COLON json_value                           { $$ = json_object_new(); json_object_add($$, $<_string>1, $<_json_value>2); }
    | json_expr_list COMMA STRING COLON json_value      { json_object_add($<_json_expr_list>1, $<_string>3, $<_json_value>5);        }
    ;

json_array:
    LB RB                         { $$ = json_array_new();     }
    | LB json_value_list RB       { $$ = $<_json_value_list>2; }
    ;

json_value_list:
    json_value                            { $$ = json_array_new(); json_array_add($$, $<_json_value>1); }
    | json_value_list COMMA json_value      { json_array_add($<_json_value_list>1, $<_json_value>3);      }
    ;

json_value:
    STRING              { $$ = json_string_new($<_string>1); }
    | INT               { $$ = json_int_new($<_int>1);       }
    | DOUBLE            { $$ = json_double_new($<_double>1); }
    | BOOLEAN           { $$ = json_int_new($<_bool>1);      }
    | json_array        { $$ = $<_json_array>1;              }
    | json_object       { $$ = $<_json_object>1;             }
    ;

%%

void yyerror(void* scanner, json_object_t** parsed_object, const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}
