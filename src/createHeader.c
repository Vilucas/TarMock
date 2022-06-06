#include "tarMock.h"
#include "main.h"
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

bool createAndAppendHeader(char *name, int fd, struct posix_header_mock **new)
{
    struct stat s;
    lstat(name, &s);

    if (*new == NULL)
        return false;
    (*new)->name = strdup(name);
    (*new)->size = s.st_size;
    return true;
    //write(fd, );
}
