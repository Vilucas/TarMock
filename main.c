#include <stdlib.h>

int main()
{
    char *s  = NULL;

    s = malloc(sizeof(char) * 1243);
    s = NULL;
    s[0] = 'a';
    printf("%s\n",s);
}