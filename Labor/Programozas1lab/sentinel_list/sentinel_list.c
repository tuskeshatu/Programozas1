#include <stdio.h>
#include <stdlib.h>

int main()
{

typedef struct listelem
{
    int data;
    struct listelem *next;
} listelem;

listelem *empty = malloc(sizeof(listelem));

empty->next = malloc(sizeof(listelem));

empty->next->next = NULL;
}