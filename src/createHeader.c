#include "tar.h"
#include "main.h"


bool appendName(struct posix_header *new, char *name)
{
    FILE *f = opendir(".");
    struct dirent *dir;

    while ((dir = readdir(f)))
    {

    }
}

bool createAndAppendHeader(char *name, int fd)
{
    struct posix_header new;

    strcpy(new->name, name);

    //write(fd, );
}
