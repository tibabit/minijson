
%define api.token.prefix {TOK_}
%define parse.error verbose

%token      EOF         0       "end of file"
%token      COMMA       ','     "comma"
%token      COLON       ':'     "semicolon"
%token      LB          '['     "Left bracket"
%token      RB          ']'     "Right bracket"
%token      LCB         '{'     "Left curly bracket"
%token      RCB         '}'     "Right curly bracket"

%union
{
    int _int;
    double _double;
    unsigned char _bool:1;
    char* _string;
}

%token <_int>       INT
%token <_double>    DOUBLE
%token <_bool>      BOOLEAN
%token <_string>    STRING

%code requires
{
#include <stdio.h>
}
%code
{
#include <stdio.h>
void yyerror(const char *msg);
}

%%

input:  /* empty line */
     | input json_object

json_object: LCB json_expr_list RCB


json_expr_list: json_expr
              | json_expr_list COMMA json_expr

json_expr: /*empty line */
         | json_key COLON json_value

json_key: STRING            { fprintf(stdout, "KEY: %s\n", $1); }

json_value: STRING          { fprintf(stdout, "VALUE %s\n", $1); }
          | INT             { fprintf(stdout, "VALUE %d\n", $1); }
          | DOUBLE          { fprintf(stdout, "VALUE\n"); }
          | BOOLEAN         { fprintf(stdout, "VALUE\n"); }
          | json_array      { fprintf(stdout, "json_array\n"); }
          | json_object     { fprintf(stdout, "STRINGn"); }

json_array : LB json_value_list RB

json_value_list: json_value
               | json_value_list COMMA json_value

%%

void yyerror(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}
