#include <stdio.h>

void generate_kolakoski_sequence(int n) {
    int sequence[100]; // Tároló a sorozathoz
    int block_length = 1; // Az aktuális blokk hossza
    int block_value = 1; // Az aktuális blokk értéke

    for (int i = 0; i < 100; i++) {
        sequence[i] = block_value;
        block_length--;

        if (block_length == 0) {
            block_value++;
            if (block_value > n) {
                block_value = 1;
            }
            block_length = sequence[i];
        }
    }

    // Kiírás
    for (int i = 0; i < 100; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Kérem, adja meg n értékét (2 és 9 között): ");
    scanf("%d", &n);

    if (n >= 2 && n <= 9) {
        generate_kolakoski_sequence(n);
    } else {
        printf("Hibás bemenet. Az n értéke 2 és 9 között kell legyen.\n");
    }

    return 0;
}