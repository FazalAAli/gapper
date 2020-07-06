
#include "gapper.h"

int main(int argc, char **argv)
{
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

    printf("delete = %i, update = %i,path = %s\n",
           DELETE_PATH, UPDATE_NOW, PATH);
}

void print_help(void)
{
    printf("%s", HELP_MESSAGE);
}

int set_args(int argc, char **argv)
{
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "hup:d:")) != -1)
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
            PATH = optarg;
            break;
        case 'd':
            PATH = optarg;
            DELETE_PATH = 1;
            break;
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
    if (DELETE_PATH == 0 && UPDATE_NOW == 0 && PATH == NULL)
    {
        printf("No valid commands found. Please see -h for help\n");
        return 1;
    }

    //Check if provided path is valid while adding
    if (DELETE_PATH == 0 && PATH != NULL)
    {
        char *git = (PATH[strlen(PATH) - 1] != '/') ? "/.git/" : ".git/";
        char *tempPath = malloc(sizeof(PATH) + sizeof(git));
        strcpy(tempPath, PATH);
        strcat(tempPath, git);

        DIR *dir = opendir(tempPath);
        if (dir)
        {
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
    if (DELETE_PATH == 0 && PATH != NULL)
    {
        add_path();
    }

    //User wants to delete path
    if (DELETE_PATH == 1)
    {
        //delete_path();
    }

    //User wants  to update all paths.
    if (UPDATE_NOW == 1)
    {
        //update_all_now();
    }

    return 0;
}

void add_path()
{
    //TODO: CREATE CSV ENTRY.

    //TODO: Check if CSV entry already exists. 

    //Check if config file exists.
    if (access(CONFIG_FILE, F_OK) != -1)
    {
        //File exists - no need to create just add.
    }
    else
    {
        //File does not exist - create it now.

        FILE *file;
        file = fopen(CONFIG_FILE, "w");

        if (file == NULL)
        {
            /* File not created hence exit */
            printf("Unable to create config file.\n");
            exit(EXIT_FAILURE);
        }

        fputs(PATH, file);
        fclose(file);
    }
}