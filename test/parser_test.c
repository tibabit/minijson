#include <stdio.h>
#include "../minijson_parser.h"

void open_file(char *file);
void close_file();

int main(int argc, char **argv)
{
    int opend_file = 0;
    if (argc > 1)
    {
        open_file(argv[1]);
        opend_file = 1;
    }
    int ret = yyparse();

    if (opend_file)
    {
        close_file();
    }

    return ret;
}
