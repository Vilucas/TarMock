#include "parsing.h"
#include "main.h"
#include "sys/stat.h"

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
        addNode(&((*Data)->arguments), av, FileType);
        return;
    }
    struct dirent *dp;
    //determine type
    while ((dp = readdir(file)))
    {
        //OP not handling the subdirectory, default type applied to all elements inside of the directory.
       addNode(&((*Data)->arguments), av, FileType);
    }
    //add argument to list
    
}

static bool addOptions(char *av, data_t **Data, bool *fetchingArgs, int *i)
{
    //
    if (!av || !av[0] || av[0] != '-' || (av[0] == '-' && av[1] == '-') || fetchingArgs == false)
    {
        *i = *i - 1;
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
    for (int i = 1; av[i]; i++)
    {
        if (fetchingOptions)
            addOptions(av[i], Data, &fetchingOptions, &i);
        else if ((*Data)->archive_name == NULL)
            addArchiveName(av[i], Data);
        else
            addArgument(av[i], Data);
    }
    //printInputData(*Data);
    if (!(*Data)->archive_name)
        return false;
    return true;
}