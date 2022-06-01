#include "main.h"
#include <fcntl.h>
#include "tar.h"


// only works with file, directories are simply ignored
bool appendItemToArchive(int fd, char *name, enum fileType type)
{
    int fdFile;
    
    if ((fdFile = open(name, O_RDONLY)) == -1)
        return false;
    if (!createAndAppendHeader(name, fd))
        return false;

}

bool createArchive(data_t *Data)
{
    //Too bored to make the program return if the given archive is a dead end
    int fd = open(Data->archive_name, O_CREAT | O_RDWR);

    largs_t *tmp = Data->arguments;

    while (tmp)
    {
        if (!appendItemToArchive(fd, tmp->arg_name, tmp->type))
            return false;
        tmp = tmp->next;
    }
    return true;
}