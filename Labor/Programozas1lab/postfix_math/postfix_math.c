#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listelem
{
    double val;
    struct _listelem *next;
} listelem;

void push(listelem *stack, double num)
{
    listelem *top = malloc(sizeof(listelem)), *lastelem = stack;

    while (lastelem->next != NULL)
        lastelem = lastelem->next;

    top->val = num;
    top->next = NULL;
    lastelem->next = top;
}

double pop(listelem *stack)
{
    listelem *lastelem = stack, *curelem = stack;

    while (curelem->next != NULL)
    {
        lastelem = curelem;
        curelem = curelem->next;
    }

    double retval = curelem->val;
    lastelem->next = NULL;
    free(curelem);
    return retval;
}

double evaluate(char *tokens[], int size_tokens)
{
    listelem *stack = malloc(sizeof(listelem));
    stack->next = NULL;

    for (size_t i = 0; i < size_tokens; i++)
    {
        if (strstr("+-*/", tokens[i]) == NULL)
        {
            char *temp;
            push(stack, strtod(tokens[i], &temp));
        }
        else if (!strcmp(tokens[i], "+"))
            push(stack, pop(stack) + pop(stack));
        else if (!strcmp(tokens[i], "-"))
        {
            double a, b;
            b = pop(stack);
            a = pop(stack);
            push(stack, a - b);
        }
        else if (!strcmp(tokens[i], "*"))
            push(stack, pop(stack) * pop(stack));
        else if (!strcmp(tokens[i], "/"))
        {
            double a, b;
            b = pop(stack);
            a = pop(stack);
            push(stack, a / b);
        }
    }

    double retval = pop(stack);
    free(stack);
    return retval;
}

int main()
{
    char *cigany[3] = {"1.5", "2", "-"};

    double vagy = evaluate(cigany, 3);
}