#include "gapper.h"

int main(int argc, char **argv)
{
    PATH = malloc(LOCAL_PATH_MAX);
    strcat(strcpy(path_to_config, getenv("HOME")), CONFIG_FILE);
    //Set variables from arguements
    if (set_args(argc, argv) == 1)
        return 1;

    printf("Set commands sucessfully \n");

    //Check arguements
    if (check_args() == 1)
        return 1;

    printf("Checked commands sucessfully \n");

    //Perform actions
    if (perform_actions() == 1)
        return 1;

    printf("Performed commands sucessfully \n");
    
}

void print_help(void)
{
    printf("%s", HELP_MESSAGE);
}

int set_args(int argc, char **argv)
{
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "hup:d:s")) != -1)
    {
        switch (c)
        {
        case 'h':
            print_help();
            return 1;
        case 'u':
            UPDATE_NOW = 1;
            break;
        case 'p':
            PATH_GIVEN = 1;
            PATH = optarg;
            break;
        case 'd':
            PATH = optarg;
            DELETE_PATH = 1;
            break;
        case 's':
            show_list();
            return 1;
        case '?':
            if (optopt == 'p' || optopt == 'd')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
        default:
            abort();
        }
    }

    for (int index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    return 0;
}

int check_args()
{
    //Check if atleast one valid command is given
    if (DELETE_PATH == 0 && UPDATE_NOW == 0 && PATH_GIVEN == 0)
    {
        printf("No valid commands found. Please see -h for help\n");
        return 1;
    }

    //Check if provided path is valid while adding
    if (DELETE_PATH == 0 && PATH_GIVEN == 1)
    {
        char *git = (PATH[strlen(PATH) - 1] != '/') ? "/.git/" : ".git/";
        char *tempPath = malloc(sizeof(PATH) + sizeof(git));
        strcpy(tempPath, PATH);
        strcat(tempPath, git);

        DIR *dir = opendir(tempPath);
        if (dir)
        {
            char buf[4096];
            PATH = realpath(PATH, buf);
            /* Directory exists. */
            closedir(dir);
        }
        else if (ENOENT == errno)
        {
            /* Directory does not exist. */
            printf("Provided directory does not have .git. Please provide a path that is a git repo\n");
            return 1;
        }
        else
        {
            printf("Opendir() failed. Aborted operations.\n");
            return 1;
            /* opendir() failed for some other reason. */
        }

        free(tempPath);
    }

    return 0;
}

int perform_actions()
{
    //User wants to add path
    if (DELETE_PATH == 0 && PATH_GIVEN == 1)
    {
        if (add_path() == 1)
            return 1;
    }

    //User wants to delete path
    if (DELETE_PATH == 1)
    {
        char buf[4096];
        PATH = realpath(PATH, buf);
        char *csventry = create_config_entry();
        if (check_if_exists(csventry) == 0)
        {
            printf("Entry does not exists in gapper config file. Please use -p to add.\n");
            return 1;
        }
        else
        {
            delete_path(csventry);
        }
    }

    //User wants  to update all paths.
    if (UPDATE_NOW == 1)
    {
        return update_all_now();
    }

    return 0;
}

int add_path()
{
    //Create csv entry
    char *csvEntry = create_config_entry();

    //Check if config file exists.
    if (access(path_to_config, F_OK) != -1)
    {
        printf("Found config file\n");
        //File exists - no need to create just check and add.

        //Check if CSV entry already exists.
        if (check_if_exists(csvEntry) == 1)
        {
            printf("Path already exists. Use -u to update all repos now.\n");
            return 1;
        }

        FILE *file = fopen(path_to_config, "a");
        fputs(csvEntry, file);
        fclose(file);
    }
    else
    {
        //File does not exist - create it now.
        printf("create config file in %s\n", path_to_config);
        FILE *file = fopen(path_to_config, "w");
        if (file == NULL)
        {
            /* File not created hence exit */
            printf("Unable to create config file.\n");
            exit(EXIT_FAILURE);
        }

        fputs(csvEntry, file);
        fclose(file);
    }
    free(csvEntry);
}

char *create_config_entry()
{
    char *temp_entry = malloc(LOCAL_PATH_MAX);
    strcpy(temp_entry, PATH);
    strcat(temp_entry, SEPERATOR);
    return temp_entry;
}

int check_if_exists(char *csvEntry)
{
    FILE *file = fopen(path_to_config, "r");
    char line[LOCAL_PATH_MAX];
    while (fgets(line, LOCAL_PATH_MAX, file))
    {
        char *tmp = strdup(line);
        char *single = getfield(tmp, 1);
        strcat(single, SEPERATOR);

        if (strcmp(csvEntry, single) == 0)
        {
            free(tmp);
            return 1;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }

    return 0;
}

char *getfield(char *line, int num)
{
    char *tok;
    for (tok = strtok(line, ":");
         tok && *tok;
         tok = strtok(NULL, ":\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int update_all_now()
{
    FILE *file = fopen(path_to_config, "r");

    if (file == NULL)
    {
        printf("Could not open config file for updating. \n");
        return 1;
    }

    char line[LOCAL_PATH_MAX];
    while (fgets(line, LOCAL_PATH_MAX, file))
    {
        char *tmp = strdup(line);
        char *single = getfield(tmp, 1);
        printf("Updating %s\n", single);
        chdir(single);
        system(COMMAND_TO_RUN);
        // NOTE strtok clobbers tmp
        free(tmp);
    }

    return 0;
}

void delete_path(char *pathToDelete)
{
    char *path_to_temp = strcat(getenv("HOME"), "/.temp");
    //Open temporary file to write to.
    FILE *tempfile = fopen(path_to_temp, "a");
    FILE *currentConfig = fopen(path_to_config, "r");

    if (tempfile == NULL || currentConfig == NULL)
    {
        printf("Could not manipulate config files \n");
        exit(EXIT_FAILURE);
    }

    char line[LOCAL_PATH_MAX];
    while (fgets(line, LOCAL_PATH_MAX, currentConfig))
    {
        if (strcmp(pathToDelete, line) != 0)
        {
            fputs(line, tempfile);
        }
    }


    remove(path_to_config);
    rename(path_to_temp, path_to_config);
}

void show_list(){
    FILE *configFile = fopen(path_to_config, "r");
    
    if(configFile == NULL){
        printf("Could not find or open config file. \n");
        exit(EXIT_FAILURE);
    }

    printf("Current repos in list are: \n");
    char line[LOCAL_PATH_MAX];
    while(fgets(line, LOCAL_PATH_MAX, configFile)){
        printf("%s", line);
    }
}