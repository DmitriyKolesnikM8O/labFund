#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>


// Функция для вычисления суммы a
double sum_a(const double x, const double epsilon) {
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
double sum_b(const double x, const double epsilon) {
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
double sum_c(const double x, const double epsilon) {
    if (x >= 0.99) {
        printf("X должно быть меньше 1.\n");
        printf("Поэтому вывожу результат суммы, как 0\n");
        return 0.0;
    }
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


 long double second_factorial(const int n) {
    if (n < 0) {
        printf("Отрицательное число не поддерживается в этой функции.\n");
        return -645;
    }
    if ((n == 0) || (n == 1)) {
        return 1.0;
    }
    long double result = 1.0;
    if (n % 2 == 0) {
        for (int i = 2; i <= n; i += 2) {
            result *= i;
        }
    } else {
        for (int i = 1; i <= n; i += 2) {
            result *= i;
        }
    }
    return result;
}

// Функция для вычисления суммы d
double sum_d(const double x, const double epsilon) {
    if (x > 1) {
        printf("X должно быть <= 1.\n");
        printf("Поэтому вывожу результат суммы, как 0\n");
        return 0.0;
    }
    long double sum = 0.0;
    double iter;
    int n = 1; // начинаем с n = 1

    do {
        iter = (pow(-1, n) * (second_factorial(2*n - 1) * pow(x, 2 * n)) / second_factorial(2 * n));
        sum += iter * pow(x, n); // добавляем x^n
        n++;
    } while (fabs(iter) > epsilon);

    return sum;
}


// ./5 x epsilon
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Не то\n");
        printf("%d - Неправильное количество аргументов\n", argc);
        return 52;
    }

    //указатель, который нужен для отслеживания конца строки при преобразовании строки в число
    char *endptr;

    //преобразуем строку в тип double
    //&endptr указывает на первый символ в строке, который не удалось преобразовать
    //если все гуд, то указывает на конец строки
    double epsilon = strtod(argv[2], &endptr);
    if (*endptr != '\0') {
        printf("что-то не так с эпсилон");
        return 123456;
    }
    double x = strtod(argv[1], &endptr);
    if ((endptr == argv[1] || *endptr != '\0') || (epsilon <= 0.0) || (x <= 0.0)) {
        printf("БОЖЕ ЧЕЛ ЧТО ТЫ ВВЕЕЕЕЛ.\n");
        if ((epsilon <= 0.0) || (x <= 0.0)) {
            if (x <= 0.0) {
                printf("Эпсилон должен быть строго положительный\n");
            }
            if (epsilon <= 0.0) {
                printf("x должен быть положительным\n");
            }
            
        }
        
        if ((endptr == argv[1] || *endptr != '\0')) {
            printf("Что-то не то с X\n");
        }
        return 52;
    }
    double res_a = sum_a(x, epsilon);
    printf("Sum a: %.10f\n", res_a);
    double res_b = sum_b(x, epsilon);
    printf("Sum b: %.10f\n", res_b);
    double res_c = sum_c(x, epsilon);
    printf("Sum c: %.10f\n", res_c);
    double res_d = sum_d(x, epsilon);
    printf("Sum d: %.10f\n", res_d);

    return 0;
}