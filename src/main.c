#include "main.h"

bool checkFetchedOptions(struct arguments_t args)
{
    if ((args.c && args.r) || 
        (args.r && !args.f) ||
        (args.u && !args.f) ||
        (args.x && args.u) ||
        (args.x && args.c) ||
        (args.x && args.r)) {
        return false;
    }
    return true;
}

int main(int ac, char **av)
{
    data_t *Data = (data_t *)malloc(sizeof(data_t));
    memset(&(Data->options), 0, sizeof(Data->options));
    Data->archive_name = NULL;
    Data->arguments = NULL;

    //parsing fills Data->options, checkFetchedOptions Analyse them.
    if (!parsing(av, &Data) || !checkFetchedOptions(Data->options))
    {
        printf("%s", USAGE);
        return -1;
    }
    if (Data->options.c)
        createArchive(Data);
    else if (Data->options.r)
        appendToArchive(Data);
    //clear Args that won't be appended then append the result
    else if (Data->options.u && clearArgs(&Data))
        appendToArchive(Data);
    else if (Data->options.t)
        printArchive(Data);
    else if (Data->options.x)
        extractArchive(Data);
    return (0);
}