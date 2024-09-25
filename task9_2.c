#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    srand(time(NULL));

    int sizeA = rand() % 9900 + 10;
    int sizeB = rand() % 9900 + 10;
    int *A = (int *)malloc(sizeA * sizeof(int));
    int *B = (int *)malloc(sizeB * sizeof(int));
    int *C = (int *)malloc(sizeA * sizeof(int));
    
    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "АААААААААААААААААА ЖЕНЩИНААААААААААААААААА\n");
        free(A);
        free(B);
        free(C);
        return 52;
    }

    for (int i = 0; i < sizeA; i++) {
        A[i] = rand() % 2001 - 1000;
    }
    for (int i = 0; i < sizeB; i++) {
        B[i] = rand() % 2001 - 1000;
    }

    for (int i = 0; i < sizeA; i++) {
        int closestB = B[0];
        int minDiff = abs(A[i] - B[0]);

        for (int j = 1; j < sizeB; j++) {
            int diff = abs(A[i] - B[j]);
            if (diff < minDiff) {
                minDiff = diff;
                closestB = B[j];
            }
        }

        C[i] = A[i] + closestB;
    }

    printf("C:\n");
    for (int i = 0; i < sizeA; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}