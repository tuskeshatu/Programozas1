#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct
{
    char title[20];
    double popularity; // 1..5
} movie;
typedef struct l
{
    movie m;
    struct l *next;
} listelem;

void print_movies(listelem *movie)
{
    movie = movie->next;

    while (movie->next != NULL)
    {
        printf("%s", movie->m.title);
        for (size_t i = 0; i < 20 - strlen(movie->m.title); i++)
        {
            printf(" ");
        }

        printf("(");

        for (size_t i = 0; i < round(movie->m.popularity); i++)
        {
            printf("*");
        }

        for (size_t i = 0; i < 5 - round(movie->m.popularity); i++)
        {
            printf(" ");
        }
        

        printf(")\n");

        movie = movie->next;
        
    }
}

void insert_movie(listelem *head, char title[], double popularity)
{

    if (head->next == NULL)
        return;
    
    listelem *more_popular = head;

    head = head->next;

    while (head->next != NULL && head->m.popularity >= popularity)
    {
        head = head->next;
        more_popular = more_popular->next;
    }
    
    listelem *curmovie = malloc(sizeof(listelem));
    strcpy(curmovie->m.title, title);
    curmovie->m.popularity = popularity;

    more_popular->next = curmovie;
    curmovie->next = head;

}

int main()
{
    listelem *root = malloc(sizeof(listelem));

    root->next = malloc(sizeof(listelem));
    root->next->next = NULL;

    insert_movie(root, "Keresztapuci", 1.0);
}