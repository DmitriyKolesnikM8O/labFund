#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double trapezoidal_rule(const double (*f)(double), const double a, const double b, const int n) {
    double h = (b - a) / n; //шаг разбиения
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

double integral_a(const double x) {
    return log(1 + x) / x;
}

double integral_b(const double x) {
    return exp(-x * x / 2);
}

double integral_c(const double x) {
    return log(1 / (1 - x));
}

double integral_d(const double x) {
    return pow(x, x);
}

// ./6 epsilon
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Пожалуйста, дай мне эпсилон\n");
        return 1;
    }

    char *endptr;
    double epsilon = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        printf("что-то не так с эпсилон");
        return 123456;
    }
    if ((endptr == argv[1] || *endptr != '\0') || (epsilon <= 0.0 || epsilon <= 0)) {
        printf("БОЖЕ ЧЕЛ ЧТО ТЫ ВВЕЕЕЕЛ.\n");
        if ((epsilon <= 0.0) || (epsilon <= 0.0)) {
            printf("Эпсилон должен быть строго положительный\n");
        }
        
        if ((endptr == argv[1] || *endptr != '\0')) {
            printf("Что-то не то с epsilon\n");
        }
        return 52;
    }



    int n = (int)(1 / epsilon); // Количество подынтервалов

    double result;
    result = trapezoidal_rule(integral_a, 0 + 1e-10, 1, n);
    printf("1: %.10f\n", result);
    result = trapezoidal_rule(integral_b, 0, 1, n);
    printf("1: %.10f\n", result);
    result = trapezoidal_rule(integral_c, 0, 1 - 1e-10, n);
    printf("1: %.10f\n", result);
    result = trapezoidal_rule(integral_d, 0, 1, n);
    printf("1: %.10f\n", result);
    
    return 0;
}