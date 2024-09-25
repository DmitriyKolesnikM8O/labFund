#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>


// Функция для вычисления суммы a
double sum_a(double x, double epsilon) {
    long double sum = 0.0;
    double iter;
    int n = 0;

    do {
        iter = pow(x, n) / tgamma(n + 1);
        sum += iter;
        n++;
    } while (fabs(iter) > epsilon);

    return sum;
}

// Функция для вычисления суммы b
double sum_b(double x, double epsilon) {
    long double sum = 0.0;
    double iter;
    int n = 0;

    do {
        iter = pow(-1, n) * pow(x, 2 * n) / tgamma(2 * n + 1); // (-1)^n * x^(2n) / (2n)!
        sum += iter;
        n++;
    } while (fabs(iter) > epsilon);

    return sum;
}

// Функция для вычисления суммы c
double sum_c(double x, double epsilon) {
    long double sum = 0.0;
    double iter;
    int n = 0;

    do {
        iter = (pow(3, 3 * n) * pow(x, 2 * n) * pow(tgamma(n + 1), 3)) / tgamma(3 * n + 1); // (3^n * x^(2n)) / (3n)!
        sum += iter;
        n++;
    } while (fabs(iter) > epsilon);

    return sum;
}

// Функция для вычисления суммы d
double sum_d(double x, double epsilon) {
    long double sum = 0.0;
    double iter;
    int n = 1; // начинаем с n = 1

    do {
        iter = (pow(-1, n) * ((tgamma(2 * n) * 2) * pow(x, 2 * n)) / (tgamma(2 * n - 1) * 2)); // (-1)^n * (2n)! / (2n)!!
        sum += iter * pow(x, n); // добавляем x^n
        n++;
    } while (fabs(iter) > epsilon);

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Не то");
        return 52;
    }

    //указатель, который нужен для отслеживания конца строки при преобразовании строки в число
    char *endptr;

    //преобразуем строку в тип double
    //&endptr указывает на первый символ в строке, который не удалось преобразовать
    //если все гуд, то указывает на конец строки
    double epsilon = strtod(argv[2], &endptr);
    double x = strtod(argv[1], &endptr);
    if ((endptr == argv[1] || endptr != '\0') || (epsilon <= 0.0) || (x <= 0.0)) {
        printf("БОЖЕ ЧЕЛ ЧТО ТЫ ВВЕЕЕЕЛ.\n");
        return 52;
    }

    printf("Sum a: %.10f\n", sum_a(x, epsilon));
    printf("Sum b: %.10f\n", sum_b(x, epsilon));
    printf("Sum c: %.10f\n", sum_c(x, epsilon));
    printf("Sum d: %.10f\n", sum_d(x, epsilon));

    return 0;
}