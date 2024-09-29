#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ARRAY_SIZE 10

// Функция для заполнения массива псевдослучайными числами в диапазоне [a, b]
int fill_array_with_random_numbers(int *array, const int size, const int a, const int b) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (b - a + 1) + a;
    }

    return 0;
}


int find_and_swap_max_min(int *array, const int size) {
    int max_idx = 0, min_idx = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] > array[max_idx]) {
            max_idx = i;
        }
        if (array[i] < array[min_idx]) {
            min_idx = i;
        }
    }

    int temp = array[max_idx];
    array[max_idx] = array[min_idx];
    array[min_idx] = temp;

    return 0;
}


int is_integer(const char *str) {
    char *endptr;

    long long int val = strtoll(str, &endptr, 10);

    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return 0;
    }   
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <a> <b>\n", argv[0]);
        return -52;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    if (((a > b) || (abs(a - b) < ARRAY_SIZE)) || (!is_integer(argv[1]) || !is_integer(argv[2]))) {
        printf("тупой ввод, хотя смотря какой FASHION, какой FABRIC.\n");
        if (a > b) {
            printf("a и b должны быть целыми числами и b должно быть больше a\n");
        } else if (abs(a - b) < ARRAY_SIZE) {
            printf("b - a должно быть больше %d\n", ARRAY_SIZE);
        } else if (!is_integer(argv[1]) || !is_integer(argv[2])) {
            printf("a и b должны быть целыми числами\n");
        }
        
        return -52222;
    }


    srand(time(NULL));
    int array[ARRAY_SIZE];
    fill_array_with_random_numbers(array, ARRAY_SIZE, a, b);

    // Вывод исходного массива
    printf("Original array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Поиск и обмен максимального и минимального значений
    find_and_swap_max_min(array, ARRAY_SIZE);

    // Вывод измененного массива
    printf("Modified array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}