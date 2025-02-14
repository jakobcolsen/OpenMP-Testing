#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 4

int rng_serial(int a[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = (rand() % 100 + 1);
        }
    }
    printf("Serial Done!");

    return 0;
}

int rng_parallel(int a[][N], int n) {

    int i, j;

    #pragma omp parallel private(i, j) shared(a, n)
    {
        #pragma omp for 
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                a[i][j] = (rand() % 100 + 1);
            }
        }
    }

    printf("Parallel Done!");
    return 0;
}

void print_matrix(int a[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int A[N][N];
int B[N][N];

int main() {
    srand(time(NULL)); // Seed
    rng_serial(A, N);
    rng_parallel(B, N);
    print_matrix(A, N);
    print_matrix(B, N);
    return 0;
}
