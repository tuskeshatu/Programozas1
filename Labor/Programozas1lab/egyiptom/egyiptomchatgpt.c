#include <stdio.h>

void felbontas(int m, int n) {
    while (m > 0) {
        int a = n / m;
        printf("%d ", a);
        m = m * a - n;
        n = n * a;
    }
    printf("\n");
}

int main() {
    int m, n;
    printf("Kerem adja meg m es n erteket (szokozzel elvalasztva): ");
    scanf("%d %d", &m, &n);
    
    felbontas(m, n);
    
    return 0;
}