// feladat: fatelepen 10 gep, mindegyikbe eredetileg 8 meter fa.
// vevo ker: input
// kiszolgalas: legrovidebb, ami kiszolgalja az igenyeit, ha nincs hosszabb vagy ugyanakkora
//, mint amit akart, akkor legrovidebb gepben csere 8m-re, maradek hozzaadasa selejthez.

#include <stdio.h>

int main()
{
    // inmachine: tomb, melyben a tomb indexe a gep sorszama, az ott tarolt elem a benne levo fa
    // customer: a vasarlo altal kert famennyiseg
    // waste: selejt

    double inmachine[10], customer, waste[10] = {0};

    // feltoltjuk a gepeket 8 meter faval

    for (int i = 0; i < 10; i++)
    {
        inmachine[i] = 8;
    }

    // amig van input addig:

    printf("\nhany meter fat akarsz?\n");

    while (scanf("%lf", &customer) == 1)
    {

        // (input check, ha a kocsog tobb mint 8, vagy kevesebb mint 0 metert kerne)
        if (customer > 8 || customer < 0)
        {
            printf("\nkurva anyad! (a keres 0 es 8 meter koze kell essek pls)\n");
            printf("\nhany meter fat akarsz?\n");
            continue;
        }
        

        // meg kell keresnunk a legkisebbet ami kiszolgalja

        // servefrommachine: megkeressuk melyik geprol tudjuk kiszolgalni (es azok kozul melyikben van a legkevesebb fa),
        // a valtozo a gep indexet tarolja.
        // inicializalasi erteke -1, ha ez a felteteles minimumkereses soran nem irodik felul, tudjuk, hogy
        // nem talaltunk olyan gepet amirol ki tudjuk szolgalni.

        // wastefrommachine: ha nem talaltunk olyan gepet amirol kiszolgaljuk (servefrommachine == -1), akkor megkeressuk a
        // legkevesebb faval rendelkezo gepet majd azt kidobjuk (waste = waste + inmachine[wastefrommachine]), majd berakunk
        // ujabb 8 meter fat (inmachine[wastefrommachine] = 8)

        int servefrommachine = -1, wastefrommachine;

        // vegignezzuk az osszes gepen, hogy

        for (int i = 0; i < 10; i++)
        {
            // az adott gepben van-e tobb vagy ugyanannyi fa mint amit a csavesz akar??
            // ÉS

            //[meg nem talaltunk gepet amirol kiszolgaljuk, VAGY a jelenlegi gepunkben (amirol ugye mar tudjuk h ki tudjuk szolgalni)
            // kevesebb fa van mint abban, amit mar megtalaltunk??]
            if (inmachine[i] >= customer && (servefrommachine == -1 || inmachine[servefrommachine] > inmachine[i]))
            {
                // ha igen, legyen ez a gep az aktualis minimumu, majd a kovetkezo iteraciokban osszehasonlitjuk a tobbivel, igy
                // megtalaljuk az egeszbol a legkevesebbet tartalmazot, amirol meg ki tudjuk szolgalni

                servefrommachine = i;
            }

            // kozbe keressuk a csak szimplan legkevesebbet tartalmazo gepet, hogyha esetleg nem tudnank kiszolgalni,
            // tudjuk, melyikbol kell selejtezni

            // ha ez az elso iteracio, vagy ha a jelenlegi gepben kevesebb van, mint az eddig megtalalt minimumban,
            // akkor legyen a jelenlegi a legkisebb (amirol selejtezunk)
            if (i == 0 || inmachine[i] < inmachine[wastefrommachine])
            {
                wastefrommachine = i;
            }
        }

        // ha NEM talaltunk olyat, amirol kiszolgalnank, akkor selejtezzuk a legkisebbet, es berakunk ujra 8m-t,
        // majd kiszolgaljuk innen
        if (servefrommachine == -1)
        {
            waste[wastefrommachine] = waste[wastefrommachine] + inmachine[wastefrommachine];

            inmachine[wastefrommachine] = 8 - customer;
        }
        // kulonben (vagyis ha talaltunk), akkor szolgaljuk ki onnan
        else
        {
            inmachine[servefrommachine] = inmachine[servefrommachine] - customer;
            
        }

        printf("\nhany meter fat akarsz?\n");
    }

    // kiirjuk az osszes gepre mennyi a selejt

    for (int i = 0; i < 10; i++)
    {
        printf("\na selejt:\n\n%d. gep: %f m", i, waste[i]);
    }
    

    return 0;
}
