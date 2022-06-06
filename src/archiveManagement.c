#include "main.h"
#include <fcntl.h>
#include "tarMock.h"


// only works with file, directories are simply ignored
bool appendItemToArchive(int fd, char *name, enum fileType type)
{
    int fdFile;
    struct posix_header_mock *new = malloc(sizeof(struct posix_header_mock));

    if ((fdFile = open(name, O_RDONLY)) == -1)
        return false;
    if (!createAndAppendHeader(name, fd, &new))
        return false;
    return true;
}

bool createArchive(data_t *Data)
{
    //Too bored to make the program return if the given archive is a dead end
    int fd = open(Data->archive_name, O_CREAT | O_RDWR);

    struct s_largs *tmp = Data->arguments;

    while (tmp)
    {
        if (!appendItemToArchive(fd, tmp->arg_name, tmp->type))
            return false;
        tmp = tmp->next;
    }
    return true;
}