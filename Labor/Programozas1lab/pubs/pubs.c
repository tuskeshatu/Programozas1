#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct drink {
    char name[32];
    int price;
    struct drink* next;
} drink;
typedef struct pub {
    char name[32];
    drink* price_list;
    struct pub* next;
} pub;

pub* read_pubs(char* name) {
    pub head = {"", NULL, NULL};
    pub** current_pub = &(head.next);
    char buffer[32];
    int price;
    FILE* f = fopen(name, "rt");
    while (fscanf(f, "%31[^\n]\n", buffer) == 1) {
        pub* new_pub = (pub*)malloc(sizeof(pub));
        drink** current_drink;
        strcpy(new_pub->name, buffer);
        new_pub->next = NULL;
        *current_pub = new_pub;
        current_pub = &(new_pub->next);
        new_pub->price_list = NULL;
        current_drink = &(new_pub->price_list);
        while (fscanf(f, "%31[^*.]...%d\n", buffer, &price) == 2) {
            drink* new_drink = (drink*)malloc(sizeof(drink));
            new_drink->price = price;
            strcpy(new_drink->name, buffer);
            new_drink->next = NULL;
            *current_drink = new_drink;
            current_drink = &(new_drink->next);
        }
        fscanf(f, "%*[^\n]\n");
    }
    fclose(f);
    return head.next;
}

pub* find_cheapest(pub *list, char alc_drink[])
{
    pub *curpub = list, *cheapest = NULL;
    int minprice = 0;

    while (curpub != NULL)
    {
        drink *curdrink = curpub->price_list;

        while (curdrink != NULL)
        {
            if ((!strcmp(curdrink->name, alc_drink) && curdrink->price < minprice) || (minprice == 0 && !strcmp(curdrink->name, alc_drink)))
            {    
                cheapest = curpub;
                minprice = curdrink->price;
                break;
            }
            curdrink = curdrink->next;
        }
        
        curpub = curpub->next;
    }
    
    return cheapest;
}

int main()
{
    pub* pubs = read_pubs("test.txt");

    find_cheapest(pubs, "Ital c");
}