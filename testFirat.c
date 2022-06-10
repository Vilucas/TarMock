int main()
{
    char a[] = "cheval";
    char b[] = "chval";



    char *s[] = {"1okok", "oko", "okok"};

    char **mal = malloc(sizeof(char*) * 3);
    mal[0] = malloc(sizeof(char) *4);
    strcpy(mal[0], "123");
    printf("%c\n", mal[0][2]);
    int  i = 0;
    while (a[i] != '\0' && a[i] == b[i]) //while a exist, and a[i] = b[i] -> move to next
    {
        i++; // move to next
    }
    if (a[i] == b[i])//if current i is == b[i] it means we are at the end so the strings are equal
    {
        printf("strigns are equal");
       return 0;//return true
    }
     printf("strigns are not equal");
    return (1);//return false
}