 #include <stdio.h>

 int main()
 {
    int num, denom, i = 1;
    double a, left = 0, right , mid, eps = 1e-8, res, middenom, anum;

    scanf("%lf", &a);
    scanf("%d", &num);
    scanf("%d", &denom);
    
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

    while (right-left > eps)
    {
        
        double mid = (left + right)/2;
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

    printf("a gyok: %lf\n", left);
    

 }