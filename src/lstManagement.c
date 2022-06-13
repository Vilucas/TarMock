#include "main.h"

void addNode(largs_t **head, char *val, enum fileType type)
{
    largs_t *new = malloc(sizeof(largs_t));
    new->arg_name = malloc(sizeof(char) * strlen(val));
    strcpy(new->arg_name, (const char*)val);
    new->type = type;
    new->next = NULL;

    if (!(*head))
    {

        *head = new;
        return;
    }
    //avoid deferencing head
    largs_t *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}