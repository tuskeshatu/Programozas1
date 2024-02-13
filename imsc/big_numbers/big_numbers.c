#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned length;
    unsigned char *number;
} big_number_t;

int hexchar_value(char hexval)
{
    if (hexval >= 'A' && hexval <= 'F')
    {
        hexval += 'a' - 'A';
    }

    if (hexval >= '0' && hexval <= '9')
        return hexval - '0';

    if (hexval >= 'a' && hexval <= 'f')
        return hexval - 'a' + 10;

    return -1;
}

int hexa_value(char hexastr[])
{
    int decval = 0;

    for (int i = 0; hexastr[i] != '\0'; i++)
    {
        if (hexchar_value(hexastr[i]) == -1)
            continue;

        decval *= 16;
        decval += hexchar_value(hexastr[i]);
    }
    return decval;
}

big_number_t create(char s[])
{
    big_number_t number;
    int i;

    /*meret meghatarozasa*/
    for (i = 0; s[i] != '\0'; i++)
        ;

    /*mivel ez a szar ugy csinalja h veszi a hexa szambol parosaval a kurva szamokat/betuket es azokat irja ki kulon egy charba ezert akkora char tomb kell mint a faszom
    szoval akkora hogy parosaval elferjenek benne ezek a fostaligak vagyis ha paros akkor i/2 ha pratatlan a gecis c kerekites miatt i/2 + 1*/
    if (i % 2 == 0)
        number.length = i / 2;
    else
        number.length = i / 2 + 1;

    number.number = malloc(number.length);

    i--; /*hogy actually a szam vegerol kezdjuk es ne a '\0'-rol*/
    
    /*actual create*/
    for (int j = 0;; j++)
    {
        /*3 elemu temp, hogy parosaval a szamok/betuk + 1 lezaro nulla a hexa_value fgvnek hogy string legyen*/
        char temp[3] = {0};

        /*kurvaelegansan kulon lekezelve hogyha "elfogyott" a szam akkor az utso (msb) helyiertek ele odakurunk egy nullat majd ez a vege*/
        if (i == 0)
        {
            temp[0] = '0';
            temp[1] = s[0];
            number.number[j] = hexa_value(temp);
            break;
        }
        /*amugy meg az ha -ba megy i mer akkor is elfogytak a helyiertekek*/
        if (i < 0)
            break;

        /* ha egyik se vagyis a szam elejen kozepen jarunk akkor elegansan parosaval bemasoljuk a tempbe a szamokat/betuket*/
        temp[0] = s[i - 1];
        temp[1] = s[i];
        i -= 2;
        
        /*es itt a csoda hogy a temp[0] es temp[1] mintha egy darab hexa szam lenne na annak az erteket bekurjuk a bigdaddy numberunk number cimu tombjebe*/
        number.number[j] = hexa_value(temp);
    }
    return number;
}

char *tostring(big_number_t a)
{
    /*na ez olyan orbitalisan buzi hogyha lenne apja akkor az is roman lenne*/

    /*mallocolunk szepen egy stringet aminek a hossza a bignumber hossza +1 hogy oda beferjen meg nyolc biten a faszom
    vagy eppen azert hogy fiala anyja erre maszturbaljon
    vagy talan azert hogy a lezaro '\0' is odaferjen mar nemtom*/
    char *str = malloc(2 * a.length + 1);
    for (int i = 0; i < 2 * a.length + 1; i++)
        str[i] = '\0';

    /*majd forditva (nyald a seggem orditva) bejarjuk a tombot*/
    for (int i = a.length - 1, j = 0; i >= 0; i--)
    {

        /*na ez nagyon szep am esku tehat az van h van ez a sprintf function amibe bebaszol egy stringet (temp, 2 a letarolt ertek hexa visszafejtesenek es 1 null)
        meg hogy mit irjon bele. jelen esetben meg van neki mondva hogy az a.number[i] az egy decimalis szam amibol egy 2 helyiertek hosszusagu hexat kene csinalni.
        zseni.*/
        char temp[3];
        sprintf(temp, "%02X", a.number[i]);
        /*strcat miatt muszaj lezarni a tempet, bocsi anyu ez jutott eszembe :,(*/
        temp[2] = '\0';
        strcat(str, temp);
    }

    return str;
}

/*ez easy*/
void destroy(big_number_t *a)
{
    free(a->number);
    a->length = 0;
    a->number = NULL;
}

/*hat hogy oszinte legyek itt en se tudom mi a faszt szivtam*/
big_number_t add(big_number_t a, big_number_t b)
{
    int carry = 0;
    big_number_t sum;
    
    /*a hossz legyen a hosszabbik szam hossza mer fialabacsi aztmondta*/
    if (a.length > b.length)
    {
        sum.number = malloc(a.length);
        sum.length = a.length;
    }
    else
    {
        sum.number = malloc(b.length);
        sum.length = b.length;
    }

    for (int i = 0; i + 1 <= sum.length; i++)
    {
        int temp;

        /*ha kifutottunk valamelyik szambol akkor a masik lesz a temp erteke mer valami + 0 az valami kurva anyad ifelse:))))))*/
        if (i + 1 > a.length)
            temp = b.number[i] + carry;
        else if (i + 1 > b.length)
            temp = a.number[i] + carry;
        else
            temp = a.number[i] + b.number[i] + carry;

        /*ha 256nal nagyobb tudjuk h van atvitel*/
        if (temp >= 256)
        {
            /* ES ha meg a szamnak a vegen vagyunk na akkor szopo mert akkor tudjuk hogy ha van carry es a vegen vagyunk akkor kell megegy
            helyierteknek hely ezert realloc aztan megcsinaljuk oda meg a muveletet es viszlat csokolom*/
            if (i + 1 == sum.length)
            {
                sum.number = realloc(sum.number, sum.length + 1);
                sum.length++;
                sum.number[i] = temp - 256;
                sum.number[i + 1] = 1;
                break;
            }

            /*amugy csak szimplan a maradekkepzest elvegezzuk*/
            sum.number[i] = temp - 256;
            carry = 1;
            continue;
        }

        /*ha nincs maradek minden nagyon cool, vegyunk mar mast alapul*/
        sum.number[i] = temp;
        carry = 0;
    }

    return sum;
}


/*amugy csokolom itt lehet tesztelni kreativitas a tetofokara hag valtozoelnevezesben*/
int main(void)
{
    char fasz[] = "1";
    char penisz[] = "123456789ABCDEF";
    big_number_t kuksi = create(fasz);
    big_number_t futykos = create(penisz);
    big_number_t kuksifutyi = add(kuksi, futykos);
    char *baromallat = tostring(kuksifutyi);
}