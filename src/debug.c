#include "main.h"
#include "tarMock.h"
void printInputData(data_t *Data)
{
    printf("Options:\n");
    uint8_t i;
   
    printf("c = %s\n", Data->options.c ? "true" : "false");
    printf("f = %s\n", Data->options.f ? "true" : "false");
    printf("r = %s\n", Data->options.r ? "true" : "false");
    printf("t = %s\n", Data->options.t ? "true" : "false");
    printf("u = %s\n", Data->options.u ? "true" : "false");
    printf("x = %s\n\n", Data->options.x ? "true" : "false");
    printf("Archive name = %s\n", Data->archive_name);
    largs_t *tmp = Data->arguments;
    
    printf("Arguments:\n");
    while (tmp)
    {
        printf("argument %d = %s\n", i, tmp->arg_name);
        i++;
        tmp = tmp->next;
    }
}


void   printfHeader(struct posix_header_mock *new)
{
    printf(" - Header - \n");
    printf("%s\n%d\n", new->name, new->size);
}
