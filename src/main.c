#include "main.h"

int main(int ac, char **av)
{
    data_t *Data = (data_t *)malloc(sizeof(data_t));
    memset(&(Data->options), 0, sizeof(Data->options));
    Data->archive_name = NULL;
    Data->arguments = NULL;

    if (!parsing(av, &Data))
    {
        printf("%s", USAGE);
        return -1;
    }
    return (0);
}