#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long double summ_for_digit(const long double m) {
	long double sum = 0;
	for (long double i = 1; i <= m; ++i) {
		sum += (long double)(1 / i);
	}
	return sum - logl(m);
	return 0;
}

long double factorial_digit(const long double n) {
	long double res = 1;
	for (int i = 2; i <= n; i++) res *= i;
	return res;
}

int limit_e(const long double epsilon, long double* ans) {
	long double n = 1;
	long double one = 1;

	long double first = 2;
	long double second = 2.25;

	//сравниваем с abs в long double
	while (epsilon < fabsl(first - second)) {
		n += 1;
		first = second;
		second = powl((1 + one / (n + 1)), n + 1);
	}
	*ans = second;
	return 0;
}

int sum_e(const long double epsilon, long double* ans) {
	*ans = 0;
	int n = 0;
	long double one = 1;
	long double elem = 1;
	while (epsilon < elem) {
		*ans += elem;
		n += 1;
		elem = one / factorial_digit(n);
	}
	*ans += elem;
	return 0;
}

int equation_e(const long double epsilon, long double* ans) {
	long double l = -999;
	long double r = 1000;
	long double current = 0.5;
	while (epsilon < fabsl(l - r)) {
		if (log(current) > 1) {
			r = current;
		} else {
			l = current;
		}
		current = (l + r) / 2;
	}
	*ans = current;
	return 0;
}

int limit_pi(const long double epsilon, long double* ans) {
	long double n = 1;
	long double one = 1;
	long double first = 4;
	long double second = 8.0;
	while (epsilon < fabsl(first - second)) {
		n += 1;
		first = second;
		second = (one / (n + 1)) *
	(powl((powl(factorial_digit(n + 1), 2) * powl(2, 2 * (n + 1)) / factorial_digit(2 * (n + 1))), 2));
	}
	*ans = second;
	return 0;
}


int sum_pi(const long double epsilon, long double* ans) {
	*ans = 0;
	long double n = 1;
	long double elem = 1;
	while (epsilon < fabsl(elem)) {
		*ans += elem;
		n += 1;
		elem = powl(-1, n - 1) / (2 * n - 1);
	}
	*ans += elem;
	*ans *= 4;
	return 0;
}

int equation_pi(const long double epsilon, long double* ans) { 
	*ans = acos(-1);
	return 0; 
	}

int limit_ln(const long double epsilon, long double* ans) {
	long double n = 1;
	long double one = 1;
	long double first = 1;
	long double second = 2 * (powl(2, 0.5) - 1);
	while (epsilon < fabsl(first - second)) {
		n += 1;
		first = second;
		second = (n + 1) * (powl(2, one / (n + 1)) - 1);
	}
	*ans = second;
	return 0;
}

int summ_ln(const long double epsilon, long double* ans) {
	*ans = 0;
	long double n = 1;
	long double elem = 1;
	while (epsilon < fabsl(elem)) {
		*ans += elem;
		n += 1;
		elem = powl(-1, n - 1) / n;
	}
	*ans += elem;
	return 0;
}

int equation_ln(const long double epsilon, long double* ans) {
	long double e = 0;
	sum_e(epsilon, &e);
	long double l = -999, r = 1000;
	long double current = 0.5;
	while (epsilon < fabsl(l - r)) {
		if (powl(e, current) - 2 > 0) {
			r = current;
		} else {
			l = current;
		}
		current = (l + r) / 2;
	}
	*ans = current;
	return 0;
}

int limit_sqrt(const long double epsilon, long double* ans) {
	long double first = -0.5;
	long double second = 0.375;
	while (epsilon < fabsl(first - second)) {
		first = second;
		second = first - (powl(first, 2) / 2) + 1;
	}
	*ans = second;
	return 0;
}

int summ_sqrt(const long double epsilon, long double* ans) {
	*ans = 1;
	long double n = 2;
	long double elem = powl(2, 0.25);
	while (epsilon < fabsl(1 - elem)) {
		*ans *= elem;
		n += 1;
		elem = powl(2, powl(2, -n));
	}
	*ans *= elem;
	return 0;
}

int equation_sqrt(const long double epsilon, long double* ans) {
	long double l = -1000, r = 1000;
	long double current = 0;
	while (epsilon < fabsl(l - r)) {
		if (powl(current, 2) > 2) {
			r = current;
		} else {
			l = current;
		}
		current = (l + r) / 2;
	}
	*ans = current;
	return 0;
}

int limit_y(const long double epsilon, long double* ans) {
	long double m = 100;
	long double first = summ_for_digit(1);
	long double second = summ_for_digit(2);
	while (epsilon < fabsl(first - second)) {
		++m;
		first = second;
		second = summ_for_digit(m);
	}
	*ans = second;
	return 0;
}

//вычисляем сумму ряда
long double y_row_member(const long double n) {
	long double res = 0;
	for (int k = 1; k <= 2 * n; k++) {
		res += 1.0 / (n * n) * ((long double)k / ((long double)k + (long double)n * n));
	}
	return res;
}

int summ_y(const long double epsilon, long double* ans) {
	long double Pi = acos(-1);
	long double result = -Pi * Pi / 6.0 + 1.0 / 2.0 + 2.0 / 3.0;
	long double k = 2;
	long double pred = 123456;
	long double elem = y_row_member(k);
	while (epsilon < fabsl(pred - result)) {
		pred = result;
		result += elem;
		++k;
		elem = y_row_member(k);
	}
	*ans = result;
	return 0;
}

//находим все простые числа в диапазоне от 0 до n-1
int sieve_Eratosthenes(bool* sv, const long long n) {
	//инициализируем все элементы массива
	for (int i = 0; i < n; i++) {
		sv[i] = 1;
	}
	sv[0] = 0;
	sv[1] = 0;
	for (long long i = 2; i < n; i++) {
		if (!sv[i]) {
			continue;
		}

		for (long long j = 2; j * i < n; j++) {
			sv[i * j] = 0;
		}
	}
	return 0;
}

long double next_for_equation(const long double accuracy) {
	bool* is_prime = (bool*)malloc(sizeof(bool) * (accuracy + 1));
	if (is_prime == NULL) {
		free(is_prime);
        return 0;
	}
	sieve_Eratosthenes(is_prime, accuracy + 1);
	
	long double res = logl(accuracy);
	for (int p = 2; p <= accuracy; p++) {
		if (is_prime[p]) {
			res *= (long double)(p - 1) / (long double)p;
		}
	}
	return res;
}

int equation_y(const long double epsilon, long double* ans) {
	long double first = next_for_equation(2);
	long double second = next_for_equation(3);
	int n = 4;
	while (fabsl(first - second) >= epsilon) {
		first = second;
		second = next_for_equation(n);
		n += 1;
	}
	*ans = second;
	return 0;
}

int print_for_e(const long double epsilon) {
	long double ans = 0;
	printf("For E:		");
	limit_e(epsilon, &ans);
	printf("%.10Lf ", ans);
	sum_e(epsilon, &ans);
	printf("%.10Lf ", ans);
	equation_e(epsilon, &ans);
	printf("%.10Lf\n", ans);

	return 0;
}

int print_for_pi(const long double epsilon) {
	long double ans = 0;
	printf("For Pi: 	");
	limit_pi(epsilon, &ans);
	printf("%.10Lf ", ans);
	sum_pi(epsilon, &ans);
	printf("%.10Lf ", ans);
	equation_pi(epsilon, &ans);
	printf("%.10Lf\n", ans);

	return 0;
}

int print_for_ln(const long double epsilon) {
	long double ans = 0;
	printf("For Ln2:	");
	limit_ln(epsilon, &ans);
	printf("%.10Lf ", ans);
	summ_ln(epsilon, &ans);
	printf("%.10Lf ", ans);
	equation_ln(epsilon, &ans);
	printf("%.10Lf\n", ans);

	return 0;
}

int print_for_sqr(const long double epsilon) {
	long double ans = 0;
	printf("For Sqr2:    	");	
	limit_sqrt(epsilon, &ans);
	printf("%.10Lf ", ans);
	summ_sqrt(epsilon, &ans);
	printf("%.10Lf ", ans);
	equation_sqrt(epsilon, &ans);
	printf("%.10Lf\n", ans);
}

int print_for_y(const long double epsilon) {
	long double ans = 0;
	printf("For Y:		");
	limit_y(epsilon, &ans);
	printf("%.10Lf ", ans);
	summ_y(epsilon, &ans);
	printf("%.10Lf ", ans);
	equation_y(epsilon, &ans);
	printf("%.10Lf ", ans);
}

// считаем буковки
int main(int argc, char** argv) {
	if (argc != 2) {
		printf("%d - Неправильное количество аргументов\n", argc);
		return 1;
	}
	//считываем точность
    char *endptr;
   	long double epsilon = strtod(argv[1], &endptr);
    if ((endptr == argv[1] || *endptr != '\0') || (epsilon <= 0.0 || epsilon <= 0)) {
        printf("БОЖЕ ЧЕЛ ЧТО ТЫ ВВЕЕЕЕЛ.\n");
		if (epsilon <= 0.0 || epsilon <= 0) {
			printf("%Lf - эпсилон должен быть строго положительным", epsilon);
		} else {
			printf("Ошибка при введении аргумента");
		}
		
        return 52;
    }

	print_for_e(epsilon);
	print_for_pi(epsilon);
	print_for_ln(epsilon);	
	print_for_sqr(epsilon);
	print_for_y(epsilon);
}