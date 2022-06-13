#include "main.h"
#include <fcntl.h>
#include "tarMock.h"
#include <unistd.h>


//OP add padding after writing content if the file content is less than 512 bytes.
// only works with files, directories are simply ignored
bool appendItemToArchive(int fd, char *name, enum fileType type)
{
    int fdFile;
    char readBuffer[BLOCK_SIZE + 1] = {0};
    int nb;
    struct posix_header_mock *new = malloc(sizeof(struct posix_header_mock));

    //open file to be added to archive
    if ((fdFile = open(name, O_RDONLY)) == -1)
        return false;
    //create the header
    if (!createAndAppendHeader(name, fd, &new))
        return false;

    while ((nb = read(fdFile, readBuffer, BLOCK_SIZE)) > 0)
    {
        if (nb == 0)
            return true;
        readBuffer[nb] = '\0';
        nb = write(fd, readBuffer, BLOCK_SIZE);
        memset(readBuffer, '\0', BLOCK_SIZE);
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
        if (!buffer[0])
            //end of archive found;
            return true;
        buffer[ret] = '\0';
        if ((!(fdFile = open(buffer, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))))
        {
            printf("coudn't create of open one of the archive files");
            return false;
        }
        // reinit buffer to 0 to read the size;
        memset(buffer, '\0', sizeof(buffer));
        if (!(ret = read(fd, buffer, MAX_SIZE_LENGTH)))
        {
            printf("couldn't read the size of one of the archive file. exiting...");
            return false;
        }
        buffer[ret] = '\0';
        int size = atoi(buffer);
        memset(buffer, '\0', sizeof(buffer));
        while(size > 0)
        {  
            if (!(ret = read(fd, buffer, BLOCK_SIZE)))
            {
                printf("Error happened while reading one of the archives files");
                return false;
            }
            printf("%d\n", size);
            if (size < BLOCK_SIZE)
            {
                ret = size;
                printf("%d\n", ret);
            }
            buffer[ret] = '\0';
            printf("%d\n", size);
            if (!(ret = write(fdFile, buffer, ret)))
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

bool printArchive(data_t *Data)
{
    int fd = open(Data->archive_name, O_RDONLY);
    char buffer[MAX_NAME_LENGTH + 1] = {0};
    int readBytes = 0;

    printf("Entering at point - %s\n", buffer);
    while ((readBytes = read(fd, buffer, MAX_NAME_LENGTH)) > 0 && buffer[0])
    {
        buffer[readBytes] = '\0';
        printf("BUFFER at point - %s\n", buffer);
        memset(buffer, '\0', strlen(buffer));
        if ((readBytes = read(fd, buffer, MAX_SIZE_LENGTH)) < 0)
        {
            printf("couldn't read the size of one of the archive file. exiting...");
            return false;
        }
        buffer[readBytes] = '\0';
        int size = atoi(buffer);
        //printf("buffer for size = %s, %d\n", buffer, size);
        char tmpBuff[size + 1];
        if ((readBytes = read(fd, tmpBuff, size)) < 0)
        {
            printf("pass\n");
            return false;
        }
        tmpBuff[readBytes] = '\0';
        memset(buffer, '\0', strlen(buffer));
    }
    printf("buffer at exit %s\n", buffer);
    return true;
}