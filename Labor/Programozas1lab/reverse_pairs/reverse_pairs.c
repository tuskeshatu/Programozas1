#include <stdio.h>
#include <stdlib.h>

typedef struct _listelem
{
    int a;
    struct _listelem *next;
} listelem;

void reverse_pairs(listelem *head)
{
    if (head->next->next == NULL || head->next->next->next == NULL)
        return;

    listelem *first, *last;

    while (1)
    {

        first = head->next;

        head->next = head->next->next;
        last = head->next->next;
        head->next->next = first;
        first->next = last;

        head = head->next->next;

        if (head->next->next == NULL || head->next->next->next == NULL)
            return;
    }
}

int main()
{

    listelem *head = malloc(sizeof(listelem));

    head->next = malloc(sizeof(listelem));
    head->next->a = 1;

    head->next->next = malloc(sizeof(listelem));
    head->next->next->a = 2;

    head->next->next->next = malloc(sizeof(listelem));
    head->next->next->next->a = 3;

    head->next->next->next->next = malloc(sizeof(listelem));
    head->next->next->next->next->next = NULL;

    reverse_pairs(head);
}