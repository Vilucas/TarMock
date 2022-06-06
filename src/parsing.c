#include "parsing.h"
#include "main.h"

static void addArchiveName(char *av, data_t **Data)
{
    // add archive data to Data 
    (*Data)->archive_name = malloc(sizeof(char) * strlen(av) + 1);
    strcpy((*Data)->archive_name, av);
}

static void addArgument(char *av, data_t **Data)
{
    struct lstat *stat;
    DIR *file;
    int type;
    
    if ((file = opendir(av)) == NULL)
    {
        printf("pass 2\n");
        addNode(&((*Data)->arguments), av, FileType);
        printf("pass 2\n");

        return;
    }
    struct dirent *dp;
    //determine type
    while ((dp = readdir(file)))
    {
       dp->d_type = DT_DIR ? FolderType : FileType;
    }
    //add argument to list
    addNode(&((*Data)->arguments), av, type);
}

static bool addOptions(char *av, data_t **Data, bool *fetchingArgs)
{
    //
    if (!av || !av[0] || av[0] != '-' || (av[0] == '-' && av[1] == '-') || fetchingArgs == false)
    {
        *fetchingArgs = false;
        return false;
    }
    //fetch arguments
    for (int i = 1; av[i]; i++)
    {
        switch (av[i])
        {
            case 'c':
                (*Data)->options.c = true;
                break;
            case 'r':
                (*Data)->options.r = true;
                break;
            case 't':
                (*Data)->options.t = true;
                break;
            case 'u':
                (*Data)->options.u = true;
                break;
            case 'x':
                (*Data)->options.x = true;
                break;
            case 'f':
                (*Data)->options.f = true;
                break;
            default:
                break;
        }
    }
    return true;
}

bool parsing(char **av, data_t **Data)
{
    bool fetchingOptions = true;
    for (int i = 0; av[i]; i++)
    {
        //take arg, if not arg or Options have already been taken, store the file as either the name of the archive or an argument
        if (fetchingOptions)
            addOptions(av[i], Data, &fetchingOptions);
        else if ((*Data)->archive_name == NULL)
            addArchiveName(av[i], Data);
        else
            addArgument(av[i], Data);
    }
    printInputData(*Data);
    if (!(*Data)->archive_name || !(*Data)->arguments)
        return false;
    return true;
}