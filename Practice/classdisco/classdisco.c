#include <math.h>
#include <stdio.h>

typedef enum
{
    BOY,
    GIRL
} sex;

typedef struct
{
    sex sex;
    unsigned short int height;
} student;

int partner(student stud1, student stud2)
{
    return (stud1.sex != stud2.sex && abs(stud1.height - stud2.height) < 10);
}

int num_partners(student partners[], int size_partners, int idx)
{
    int count = 0;
    for (int i = 0; i < size_partners; i++)
    {
        if (i == idx)
            continue;
        if (partner(partners[idx], partners[i]))
            count++;
    }
    return count;
}

void tallest_and_partners(student class[], int size_class, int *p_tallest_idx, int *p_num_of_partners)
{
    unsigned short int max_height = class[0].height;
    *p_tallest_idx = 0;
    for (int i = 0; i < size_class; i++)
        if (class[i].height > max_height)
        {
            *p_tallest_idx = max_height;
            max_height = class[i].height;
        }
    *p_num_of_partners = num_partners(class, size_class, *p_tallest_idx);
}

int main(void)
{
    student class[] = {{BOY, 180}, {GIRL, 175}, {GIRL, 160}};
    int tallest_idx, num_of_partners;
    
    tallest_and_partners(class, 3, &tallest_idx, &num_of_partners);

    printf("%d %d", tallest_idx, num_of_partners);

    return 0;
}