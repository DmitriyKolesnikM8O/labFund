#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool double_from_stdin(const char* str) {
	if (str[0] == '.') {
		printf("че, это похоже на число?");
		return false;
	}
	int i = 0;
	if (str[0] == '-') {
		i++;
		if (str[1] == '.') {
			printf("бред какой-то");
			return false;
		}
	}
	int count_dot = 0;
	for (; str[i] != '\0'; ++i) {
		if (str[i] < 48 || str[i] > 57) {
			if (str[i] == 46) {
				if (count_dot == 0) {
					count_dot++;
				} else {
					return false;
				}
			} else {
				return false;
			}
		}
	}
	return true;
}

int parse_if_argc_6(char** argv, long double* eps, long double* a, long double* b, long double* c) {
	if (!(double_from_stdin(argv[2]) && double_from_stdin(argv[3]) && double_from_stdin(argv[4]) && double_from_stdin(argv[5]))) {
		printf("С твоими числами явно что-то не так");
		return 52;
	}
	if (sscanf(argv[2], "%Lf", eps) != 1) {
		printf("Невозможно");
		return 1232;
	}
	if (sscanf(argv[3], "%Lf", a) != 1) {
		printf("Невозможно");
		return 123;
	}
	if (sscanf(argv[4], "%Lf", b) != 1) {
		printf("Невозможно");
		return 124;
	}
	if (sscanf(argv[5], "%Lf", c) != 1) {
		printf("Невозможно");
		return 5678;
	}
	return 0;
}

int solution_equation(long double eps, const long double a, const long double b, const long double c) {
	printf("Квадратное уравнение для: %Lf - эпсилон, %Lf - a, %Lf - b, %Lf - c\n", eps, a, b, c);
	long double d = b * b - 4 * a * c;
	if (d + eps < 0) {
		printf("Тут нет корней\n");
		return 1234;
	} else if (d <= eps) {
		long double res = -b / (2 * a);
		printf("Единственный корень: %Lf\n", res);
	} else {
		long double res = ((-b + sqrtl(d)) / (2 * a));
		printf("Первый корень: %Lf\n", res);
		res = ((-b - sqrtl(d)) / (2 * a));
		printf("Второй корень: %Lf\n", res);
	}

	return 0;
}

int solution(const int eps, const int a, const int b, const int c) {
	solution_equation(eps, b, c, a);
	solution_equation(eps, a, b, c);
	solution_equation(eps, c, a, b);
	solution_equation(eps, a, c, b);
	solution_equation(eps, b, a, c);
	solution_equation(eps, c, b, a);

	return 0;
}

int triangle_test(const long double eps, const long double a, const long double b, const long double c) {
	if (a == 0 || b == 0 || c == 0) {
		printf("Рофл?");
		printf("Не могут образовывать треугольник");
		return 0;
	}

	//проверка на c, a, b
	if (a * a + b * b - c * c < eps && a * a + b * b - c * c > -eps) {
		printf("Да\n");
		printf("Да, могут образовывать треугольник");
		return 0;
	} else if (b * b + c * c - a * a < eps && b * b + c * c - a * a > -eps) {
		printf("Могут\n");
		printf("Да, могут образовывать треугольник");
		return 0;
	} else if (a * a + c * c - b * b < eps && a * a + c * c - b * b > -eps) {
		printf("Так точно капитан\n");
		printf("Да, могут образовывать треугольник");
		return 0; 
	}
	printf("Не фортануло\n");
	printf("Не могут образовать треугольник");
	return 0;
}

int func_for_argc_4(int argc, char** argv) {
	//проверка на флаг
	if ((argv[1][0] != '-' && argv[1][0] != '/') || argv[1][1] != 'm' || argv[1][2] != '\0') {
		printf("Вообще ничего не понятно");
		return 52;
	}

	//проверка на первое число
	for (int i = 0; argv[2][i] != '\0'; ++i) {
		if (i == 0 && argv[2][i] == '-') {
        	continue;
    	}
		if (argv[2][i] < 48 || argv[2][i] > 57) {
			printf("%d - Зачем такие нехорошие числа вводишь", argv[2][i]);
			return 42;
		}
	}
	//проверка на второе число
	for (int i = 0; argv[3][i] != '\0'; ++i) {
		if (i == 0 && argv[3][i] == '-') {
        	continue;
    	}	
		if (argv[3][i] < 48 || argv[3][i] > 57) {
			printf("%d - Зачем такие нехорошие числа вводишь", argv[3][i]);
			// printf("Зачем такие нехорошие числа вводишь");
			return 124;
		}
	}
	int a, b;
	if (sscanf(argv[2], "%d", &a) != 1) {
		printf("брат, это не число");
		return 3245;
	}
	if (sscanf(argv[3], "%d", &b) != 1) {
		printf("брат, это не число");
		return 2134545;
	}
	if (a == 0 || b == 0) {
		printf("норм  тест, но надо не равные 0");
		return 32454;
	}

	//та самая проверка на кратность
	if (a % b == 0) {
		printf("ДА\n");
	} else {
		printf("НЕТ\n");
	}
	return 0;
}

int func_for_argc_6(int argc, char** argv) {
	//снова проверка на правильность флагов
	if ((argv[1][0] != '-' && argv[1][0] != '/') || (argv[1][1] != 'q' && argv[1][1] != 't') || argv[1][2] != '\0') {
		printf("Не умеешь, не берись!");
		printf("Неправильно введены флаги");
		return 42;
	}
	if (argv[1][1] == 'q') {
		long double eps, a, b, c;
		if (parse_if_argc_6(argv, &eps, &a, &b, &c)) {
			printf("\nНе получилось\n");
			printf("Неправильно введены числа");
			return 12345;
		}

		
		if (solution(eps, a, b, c)) {
			printf("В каком-то что-то не то-то");
			return 1256789;
		}
		
	}
	if (argv[1][1] == 't') {
		long double eps, a, b, c;
		if (parse_if_argc_6(argv, &eps, &a, &b, &c)) {
			printf("\nНе получилось\n");
			return 124;
		}
		triangle_test(eps, a, b, c);
	}

	return 0;
}

// ./3 -flag {...numbers...}
/*
	-q: точность сравнения, далее 3 вещественных для квадратного уравнения
	-m: 2 ненулевых целых числа и проверка, кратно ли одно другому
	-t: точность сравнения, далее проверка на треугольник 3 чисел
*/
int main(int argc, char** argv) {
	if (argc != 6 && argc != 4) {
		printf("Не то что-то ты ввел");
		printf("%d - неправильное количество аргументов", argc);
		return 52;
	}
	if (argc == 4) {
		if (func_for_argc_4(argc, argv)) {
			return 52;
		}
	} else {
		if (func_for_argc_6(argc, argv)) {
			return 52;
		}
	}

	return 0;
}