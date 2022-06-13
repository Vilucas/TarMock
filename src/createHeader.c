#include "tarMock.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>

bool createAndAppendHeader(char *name, int fd, struct posix_header_mock **new)
{
    struct stat s;
    stat(name, &s);
    char *sizeOfFile = malloc(sizeof(char) * MAX_SIZE_LENGTH);

    if (*new == NULL)
        return false;

    //name
    (*new)->name = malloc(sizeof(char) * MAX_NAME_LENGTH + 1);
    memset((*new)->name, '\0', MAX_NAME_LENGTH + 1);
    strcpy((*new)->name, name);
    (*new)->size = s.st_size;
    write(fd, (*new)->name, MAX_NAME_LENGTH);
    //size
    printf("SIZE =%d", (*new)->size);
    memset(sizeOfFile, '\0', MAX_SIZE_LENGTH);
    int nb = sprintf(sizeOfFile, "%d", (*new)->size);
    sizeOfFile[nb] = '\0';
    write(fd, sizeOfFile, MAX_SIZE_LENGTH);
    return true;
}