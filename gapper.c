#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "gapper.h"

int main(int argc, char **argv)
{
    int UPDATE_NOW = 0;
    char *BRANCH = "main";
    char *PATH = NULL;
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "hub:p:")) != -1)
    {
        switch (c)
        {
        case 'h': print_help(); return 0;
        case 'u':
            UPDATE_NOW = 1;
            break;
        case 'b':
            BRANCH = optarg;
            break;
        case 'p':
            PATH = optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            return 1;
        default:
            abort();
        }
    }

    for (int index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    printf("update = %i, branch = %s, path = %s\n",
           UPDATE_NOW, BRANCH, PATH);
    return 0;

    //TODO: Check for not enough inputs
}

void print_help(void){
    printf("Printing help\n");

}