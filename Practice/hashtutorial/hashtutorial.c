#include <stdio.h>

int main()
{

    // a valtozo ahanyszor ki akarod iratni, i szamolja, hogy a while hanyszor futott le eddig (hany hash-t irtal eddig)
    int a, i = 1;

    // a-nak erteket olvasol be
    scanf("%d", &a);

    // ha a > 100, akkor a = 100, mert max 100 db #-t kell kiirj, akkoris ha 100-nal nagyobb az input
    if (a > 100)
    {
        a = 100;
    }

    // while ciklus: i szamlalo szamolja hanyszor futott eddig le a ciklus.
    // Minden ciklusban megnezed, hogy lefutott-e mar annyiszor a ciklus (kiirtal- e mar annyi #-t), amennyi a erteke.
    // Mivel i a lefutott ciklusok (eddig kiirt #-ek) szamat szamolja, minden lefutasnal novelni kell eggyel a szamat.
    // Amikor lefutott a-szor a ciklus, akkor i pont 1-gyel lesz nagyobb a-nal, vagyis a+1-edjere mar nem fog lefutni, mert i nagyobb lesz mint a.
    while (i <= a)
    {
        printf("#");

        i = i + 1;
    }

    return 0;
}
