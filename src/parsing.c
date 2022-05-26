#include "parsing.h"
#include "main.h"

static bool addOptions(char *av, data_t *Data, bool *fetchingArgs)
{
    if (!av || !av[0] || av[0] != '-' || (av[0] == '-' && av[1] == '-') || fetchingArgs == false)
    {
        *fetchingArgs = false;
        return false;
    }
    for (int i = 1; av[i]; i++)
    {
        switch (av[i])
        {
            case 'c':
                Data->args.c = true;
                break;
            case 'r':
                Data->args.r = true;
                break;
            case 't':
                Data->args.t = true;
                break;
            case 'u':
                Data->args.u = true;
                break;
            case 'x':
                Data->args.x = true;
                break;
            case 'f':
                Data->args.f = true;
                break;
            default:
                break;
        }
    }
    return true;
}

bool parsing(char **av, data_t *Data)
{
    bool fetchingOptions = true;
    for (int i = 0; av[i]; i++)
    {
        //take arg, if not arg or Options have already been taken, store the file as either the name of the archive or an argument
        if (fetchingOptions)
            addOptions(av[i], Data, &fetchingOptions);
        else if (Data->achive_name == NULL)
            addAchiveName(av[i], Data);
        else 
            addArgument(av[i])
        
        
        
        

    }
    return true;
}