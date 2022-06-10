#include "main.h"
#include <fcntl.h>
#include "tarMock.h"
#include <unistd.h>


//OP add padding after writing content if the file content is less than 512 bytes.
// only works with files, directories are simply ignored
bool appendItemToArchive(int fd, char *name, enum fileType type)
{
    int fdFile;
    char readBuffer[BLOCK_SIZE + 1];

    struct posix_header_mock *new = malloc(sizeof(struct posix_header_mock));
    char *sizeOfFile = malloc(sizeof(char) * 10);

    //open file to be added to archive
    if ((fdFile = open(name, O_RDONLY)) == -1)
        return false;
    //create the header
    if (!createAndAppendHeader(name, fd, &new))
        return false;
    //write name + padding
    write(fd, new->name, strlen(new->name));
    if ((MAX_NAME_LENGTH -  strlen(new->name)) > 0)
        write(fd, '\0', MAX_NAME_LENGTH);

    //get size to char* format
    int nb = sprintf(sizeOfFile, "%d", new->size);
    sizeOfFile[nb] = '\0';
    
    //write size + padding
    write(fd, sizeOfFile, strlen(sizeOfFile));
    if ((MAX_SIZE_LENGTH - strlen(sizeOfFile)) > 0)
        write(fd, '\0', strlen(sizeOfFile));
    //reusing nb for convenience
    while ((nb = read(fdFile, readBuffer, BLOCK_SIZE)) > 0)
    {
        readBuffer[nb] = '\0';
        nb = write(fd, readBuffer, nb);
    }
    return true;
}

bool createArchive(data_t *Data)
{
    //OP: prgram should return if the given archive is a dead end
    int fd = open(Data->archive_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        printf("something wrong happened while creating the archive!");
        return false;
    }
    struct s_largs *tmp = Data->arguments;

    while (tmp)
    {
        if (!appendItemToArchive(fd, tmp->arg_name, tmp->type))
            return false;
        tmp = tmp->next;
    }
    char endBuffer[END_BUFFER_SIZE] = {0};
    write(fd, endBuffer, END_BUFFER_SIZE);
    return true;
}

bool extractArchive(data_t *Data)
{
    int fd = open(Data->archive_name,  O_RDONLY);
    if (fd < 0)
    {
        printf("Archive didn't open");
        return false;
    }
    char buffer[BLOCK_SIZE + 1];
    int ret;
    int fdFile;
    while (1)
    {
        ret = read(fd, buffer, MAX_NAME_LENGTH);
        //end of archive found;
        if (!buffer[0])
            return true;
        buffer[ret] = '\0';
        if ((!(fdFile = open(buffer, O_CREAT | O_RDONLY))))
        {
            printf("coudn't create of open one of the archive files");
            return false;
        }
        // reinit buffer to 0 to read the size;
        buffer = {0};
        if (!(ret = read(fd, buffer, MAX_SIZE_LENGTH)))
        {
            printf("couldn't read the size of one of the archive file. exiting...");
            return false;
        }
        buffer[ret] = '\0';
        int size = atoi(buffer);
        buffer = {0};
        while(size > 0)
        {  
            if (!(ret = read(fd, buffer, BLOCK_SIZE)))
            {
                printf("Error happened while reading one of the archives files");
                return false;
            }
            buffer[ret] = '\0';
            if (!(ret = write(fdFile, buffer, BLOCK_SIZE)))
            {
                printf("Error: Couldn't write in one of the archive file");
                return false;
            }
            size = size - BLOCK_SIZE;
        }
        close(fdFile);
    }
    close(fd);
}