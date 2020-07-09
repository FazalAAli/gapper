#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

#define LOCAL_PATH_MAX PATH_MAX + sizeof(SEPERATOR)
int DELETE_PATH = 0;
int UPDATE_NOW = 0;
int PATH_GIVEN = 0;
char path_to_config[PATH_MAX];
char *SEPERATOR = ":\n";
char *PATH;
char *CONFIG_FILE = "/.gapperConfig"; //change to "gapperConfig.csv" when developing so the config is in the same folder as compiling/execution.
char *COMMAND_TO_RUN = "git pull";    //change to "mkdir gitPullTest" when developing so there's no unnecessary git pulls
char *HELP_MESSAGE =
    "-h : show these instructions\n"
    "-u : update all git repositories now\n"
    "-p : add path to git repositories list\n"
    "-d : remove path from  git repositories list\n";

void print_help(void);
int set_args(int argc, char **argv);
int check_args();
int perform_actions();
int add_path();
int check_if_exists(char *csvEntry);
char *create_config_entry();
int check_if_exists(char *csvEntry);
char *getfield(char *line, int num);
int update_all_now();
void delete_path(char *csvEntry);