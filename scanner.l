%{

#include "minijson_parser.h"

#undef yywrap
#define yywrap() 1
%}

%option noyywrap
%option nounput
%option batch
%option noinput
%option never-interactive

digit       [0-9]
newline     \n|\r\n|\r|\f
string      \"([^\n\r\f\\"]|)*\"

%%

\"(\\.|[^\\"])*\"       { yylval._string = yytext; return TOK_STRING;           }
[0-9]+                  { yylval._int = atoi(yytext); return TOK_INT;           }
[0-9]*\.[0-9]+          { yylval._double = atof(yytext); return TOK_DOUBLE;     }
[Tt][Rr][Uu][Ee]        { yylval._bool = 1; return TOK_BOOLEAN;                 }
[Ff][Aa][Ll][Ss][Ee]    { yylval._bool = 0; return TOK_BOOLEAN;                 }
\[                      { return TOK_LB; }
\]                      { return TOK_RB; }
\{                      { return TOK_LCB; }
\}                      { return TOK_RCB; }
\:                      { return TOK_COLON; }
,                       { return TOK_COMMA; }
\s+                     /* skip whitespace */
{newline}+              /* skip new lines */
.                       { /* fprintf(stderr,"char: %s\n", yytext); */  }
<<EOF>>                 { return TOK_EOF;               }

%%

void yy_set_file(FILE* file)
{
    yyrestart(file);
}
