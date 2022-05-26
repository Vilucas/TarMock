int main(int ac, char **av)
{
    if (!parsing(av))
    {
        printf("%s", USAGE);
        return -1;
    }
    return (0);
}