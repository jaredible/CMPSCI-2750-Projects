#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int isNumeric(const char *str)
{
    if (*str == '-')
    {
        str++;
    }

    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }

    return 1;
}

int main(const int argc, char *const argv[])
{
    int n = 100;

    printf("argc: %d\n", argc);

    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    printf("\n");

    int opt;
    while ((opt = getopt(argc, argv, "hn:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("Usage: %s -n n1 n2 ... n1, n2, etc.: numbers that are integers\n", argv[0]);
            return EXIT_SUCCESS;
        case 'n':
            printf("%s\n", optarg);

            if (isNumeric(optarg))
            {
                n = atoi(optarg);
            }
            else
            {
                fprintf(stderr, "%s isn't a number!\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        default:
            fprintf(stderr, "I don't know what to do with this argument!\n");
            return EXIT_FAILURE;
        }
    }

    while (optind < argc)
    {
        printf("extra arguments: %s\n", argv[optind]);
        optind++;
    }

    return EXIT_SUCCESS;
}