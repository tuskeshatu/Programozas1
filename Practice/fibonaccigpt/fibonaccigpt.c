#include <stdio.h>


// Rekurzív függvény a Fibonacci-sorozat kiszámítására
unsigned long long Fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
    unsigned long long arr[2];
    printf("Kerem adjon meg ket szamot: ");
    scanf("%llu %llu", &arr[0], &arr[1]);

    int i = 2;
    while (1) {
        arr[i % 2] = arr[0] + arr[1]; // Következő Fibonacci-szám kiszámítása
        if (arr[i % 2] < arr[0] || arr[i % 2] < arr[1]) {
            // Túlcsordulás ellenőrzése
            printf("Az utolso nem tulcsordult Fibonacci szam indexe: %d\n", i - 1);
            break;
        }
        i++;
    }

    return 0;
}