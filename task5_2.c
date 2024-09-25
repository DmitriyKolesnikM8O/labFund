#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool parse_double_digits(char* str) {
	if (str[0] == '.') {
		return false;
	}
	int i = 0;
	if (str[0] == '-') {
		i++;
		if (str[1] == '.') {
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

int get_opts(int argc, char** argv, long double* epsilon, long double* x) {
	if (argc != 3) {
		return 1;
	}
	if (!parse_double_digits(argv[1])) {
		return 2;
	}
	if (!parse_double_digits(argv[2])) {
		return 3;
	}
	sscanf(argv[1], "%Lf", epsilon);
	sscanf(argv[2], "%Lf", x);
	return 0;
}

void a(long double eps, long double x, long double* ans) {
	long double el = 1;
	long double n = 0;
	*ans = 0;
	while (fabsl(el) > eps) {
		*ans += el;
		el *= (x / (n + 1));
		n++;
	}
}

void b(long double eps, long double x, long double* ans) {
	long double el = 1;
	long double n = 0;
	*ans = 0;
	while (fabsl(el) > eps) {
		*ans += el;
		el *= ((-1) * powl(x, 2) / (2 * n + 1) / (2 * n + 2));
		n++;
	}
}

void c(long double eps, long double x, long double* ans) {
	if (x >= 1) {
		*ans = -228;
		return;
	}
	long double el = 1;
	long double n = 0;
	*ans = 0;
	long double cons = 9 * powl(x, 2);
	while (fabsl(el) > eps) {
		*ans += el;
		el *= cons * ((n * n + 2 * n + 1) / (9 * n * n + 9 * n + 2));
		n++;
	}
}

long double factorial(int n) {
	long double res = 1;
	for (int i = 2; i <= n; i++) res *= i;
	return res;
}

void d(long double eps, long double x, long double* ans) {
	long double el = 0;
	long double n = 2;
	*ans = el;
	long double cons = (-1) * powl(x, 2);
	while (fabsl(el) > eps) {
		el *= cons * (factorial(factorial(2*n)) / factorial(factorial(2*n - 1))) * (factorial(factorial(2*n)) / factorial(factorial(2*n + 2)));
		*ans += el;
		n++;
	}
	*ans += -(x * x) / 2;
}

int main(int argc, char** argv) {
	long double epsilon = 0;
	long double x = 0;
	if (get_opts(argc, argv, &epsilon, &x)) {
		printf("%s", "Incorrect option");
		return 1;
	}
	long double ans = 0;
	a(epsilon, x, &ans);
	printf("%Lf\n", ans);
	b(epsilon, x, &ans);
	printf("%Lf\n", ans);
	c(epsilon, x, &ans);
	if (ans > 0) {
		printf("%Lf\n", ans);
	} else{
		printf("X >= 1\n");
	}
	d(epsilon, x, &ans);
	printf("%Lf\n", ans);
	return 0;
}