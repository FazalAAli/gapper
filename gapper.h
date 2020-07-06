#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int DELETE_PATH = 0;
int UPDATE_NOW = 0;
char *PATH = NULL;
char *CONFIG_FILE = "gapperConfig.csv"; //"~/.gapperConfig";
char *HELP_MESSAGE =
    "-h : show these instructions\n"
    "-u : update all git repositories now\n"
    "-p : add path to git repositories list\n"
    "-d : remove path from  git repositories list\n";

void print_help(void);
int set_args(int argc, char **argv);
int check_args();
int perform_actions();
void add_path();