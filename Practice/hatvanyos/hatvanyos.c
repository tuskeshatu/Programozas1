// eletem elso nagyobb lelekzetvetelu projektje
// editors note: hajnali fel ketto, elso het vege az egyetemen
//               szinte az egesz szombatom rament erre a fosra
//               de vegre kesz van. szinte el se hiszem mennyit
//               lehet ilyen dolgokkal szenvedni, valszeg a kod                  
//               ocsmany, minden a mainbe csak bebaszva semmi
//               hierarchiaval meg amugyis olyan megoldasokkal
//               hogy erre az ember a hajat tepi...
//  ------------------------------------------------------------------
//                  K O V A C S         L E V E N T E


#include <stdio.h>
#include <math.h>

int main()
{
    
// valtozok: a: alap n: kitevo nv: negativ kitevu eseten n reciproka i: whilehoz res: eredmeny
    long double a, n, nv, res = 1;
    int i = 1, whole;

    printf("input a: ");
    scanf("%Lf", &a);

    printf("input n: ");
    scanf("%Lf", &n);

    whole = n;

// ha negativ a kitevo, akkor abszolut ertek
    if(n < 0)
    {
        nv = -n;
    }
    else
    {
        nv = n;
    }
    

// actual hatvanyozas

// tortkitevo check
    if (whole - nv != 0)
    {

        // num/denom atiras

        printf("tortkitevo!! csinald meg magadnak bazdmeg\n\n");

        long double eps = 1e-4, frac, num , denom, near;
        int whole, j = 1;

        whole = floor(nv);
        frac = nv-whole;
        near = round(frac);
    
        num = denom = 1;

        while(fabs(num/denom-frac)>eps)
        {

            near = round(frac*j);
            num = near;
            denom = j;
            j++;

            printf("%Lf/%Lf,\n%Lf\n", num, denom, num/denom);

        }

        num = num + denom*whole;

        printf("\n-------------------------------------------------------------------------------------------\n\na  =  %Lf,\n\ntort:  %Lf/%Lf  =  %Lf", n, num, denom, num/denom);

        // z.h. keresovel fgv alakitassal gyok kereses

        long double left = 0, right , mid, eps1 = 1e-8, middenom, anum;
    
        right = a;
        i = 1;

        while(i < num)
        {
            right=right*a;
            i++;
        }

        anum = a;
        i = 1;

        while(i < num)
        {
            anum=anum*a;
            i++;
        }

        while (right-left > eps1)
        {
        
            long double mid = (left + right)/2;
            i = 1;
            middenom = mid;
        

            while(i < denom)
            {
                middenom=middenom*mid;
                i++;
            } 


            if (middenom-anum > 0)
                right = mid;
            else
                left = mid;
        

        }

        res = (right+left)/2;

        // ha negativ tortkitevo

        if (n < 0)
            {
                res = 1/res;
    
            }

        printf("\n\n%Lf a %Lf. hatvanyon: %Lf", a, n, res);

        return 0;
    }

    else
    {

    // normal hatvanyozas

         while(i <= nv)
        {
            res=res*a;
            i++;
        }
    }

// ha negativ a kitevo, akkor az abszolut erteku kitevoju hatvany reciproka [a^(-n) = 1/(a^n)]
    if (n < 0)
    {
        res = 1/res;
    
    }

    printf("\n\n%Lf a %Lf. hatvanyon: %Lf", a, n, res);

    return 0;
}
