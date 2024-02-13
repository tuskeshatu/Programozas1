#include <stdio.h>
#include <stdlib.h>

typedef struct _point_listelem
{
    double x, y, z;
    struct _point_listelem *next;
} point_listelem;

void save(char filename[], point_listelem *head)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        fclose(file);
        return;
    }
    point_listelem *curelem = head;
    while (curelem != NULL)
    {
        fwrite(&(curelem->x), sizeof(curelem->x), 1, file);
        fwrite(&(curelem->y), sizeof(curelem->y), 1, file);
        fwrite(&(curelem->z), sizeof(curelem->z), 1, file);

        curelem = curelem->next;
        fflush(file);
    }

    fclose(file);
}

point_listelem *restore(char filename[])
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        fclose(file);
        return NULL;
    }

    point_listelem *head = NULL, *lastelem, *curelem, temp;

    if (fread(&(temp.x), sizeof(temp.x), 1, file) != 1 || fread(&(temp.y), sizeof(temp.y), 1, file) != 1 || fread(&(temp.z), sizeof(temp.z), 1, file) != 1)
        return head;

    head = malloc(sizeof(point_listelem));
    if (head == NULL)
        return NULL;

    head->x = temp.x;
    head->y = temp.y;
    head->z = temp.z;

    lastelem = head;

    while (fread(&(temp.x), sizeof(temp.x), 1, file) == 1 && fread(&(temp.y), sizeof(temp.y), 1, file) == 1 && fread(&(temp.z), sizeof(temp.z), 1, file) == 1)
    {
        curelem = malloc(sizeof(point_listelem));
        if (curelem == NULL)
            return NULL;

        curelem->x = temp.x;
        curelem->y = temp.y;
        curelem->z = temp.z;

        lastelem->next = curelem;
        lastelem = curelem;
    }

    fclose(file);
    lastelem->next = NULL;
    return head;
}

int main()
{
    point_listelem *head = malloc(sizeof(point_listelem));

    head->x = 3.6;
    head->y = 42;
    head->z = 69;
    head->next = NULL;

    save("test.bin", head);

    point_listelem *teszt = restore("test.bin");
}