#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);

    switch (n)
    {
    case 1: printf("1es"); break;
    case 2: printf("2es"); break;
    case 3: printf("3as"); break;
    case 4: printf("4es"); break;
    case 5: printf("5os"); break;

    default: printf("ertelmetlen!");
    }
    return 0;
}
