#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>


int func_flag_h(int number) {

	if (number > 50) {
		printf("Кратных чисел нет");
		return 0;
	}
	
	int flag = 1;

    for (int i = 1; i <= 100; i++) {
        if (i % number == 0) {
			flag = 0;
            printf("%d ", i);
        }
    }

	if (flag != 0) {
		printf("Кратных чисел нет");
	}
    
    printf("\n");
	return 0;
}

int func_flag_p(int n) {
	if (n == 2) {
        printf("простое оно, простое");
		return 0;
    }
    if ((n <= 1) || (n % 2 == 0)) {
        printf("Не простое, мб золотое?");
		return 0;
    }

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
			printf("Не простое, мб золотое?");
            return 0;
        }
    }
	printf("простое оно, простое");
    return 0;
}


// wrong solution for flag -s
// void func_flag_s(int n) {

//     char hex_digits[32]; 
//     int index = 0;
    
//     int found_nonzero = 0;

//     for (int i = 7; i >= 0; --i) {
//         int digit = (n >> (i * 4)) & 0xF;

//         if (digit != 0 || found_nonzero) {
//             found_nonzero = 1;

//             if (digit < 10) {
//                 hex_digits[index++] = digit + '0';
//             } else {
//                 hex_digits[index++] = digit - 10 + 'A';
//             }
//         }
//     }

//     if (!found_nonzero) {
//         hex_digits[index++] = '0';
//     }

//     for (int i = 0; i < index; ++i) {
//         printf("%c", hex_digits[i]);
//         if (i < index - 1) {
//             printf(" "); // Добавляем пробел после каждого символа, кроме последнего
//         }
//     }
//     printf("\n");
// }

int func_flag_s(int number) {
    int number_parts[100]; //чтобы хранить части числа
    int index = 0;
    while (number > 0) {
        int digits = number % 100;
        int digits_dopolntinelno = 0; //на всякий, для 2 цифры
        //в 16 ричной только 15 цифр
        if (digits > 15) {
            digits = number % 10;
            digits_dopolntinelno = (number % 100) / 10;
            number_parts[index++] = digits;
            number_parts[index++] = digits_dopolntinelno;
            
			number /= 100;
        } else {
            number_parts[index++] = digits;
            number /= 100;
        }
    }
    for (int i = index - 1; i >= 0; --i) {
        printf("%d ", number_parts[i]);
    }

    return 0;
}

int func_flag_e(int number) {
	for (int i = 1; i != number + 1; ++i) {
		long long pow = i;
		for (int j = 0; j != 10; ++j) {
			printf("%lld ", pow);
			pow *= i;
		}
		printf("%c", '\n');
	}
	return 0;
}

int func_flag_a(int number) {
	//ok google, are you know this formula??
	long long answer = number * (number + 1) / 2;
	printf("%lld ", answer);
	return 0;
}

int func_flag_f(int number) {
	long long res = 1;
	for (int i = 2; i <= number; i++) {
		res *= i;
	}

	printf("%lld ", res);
	return 0;
}

int string_to_int(char *str, int *number) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] < 48 || str[i] > 57) {
			return 1;
		}
	}
	for (int i = 0; str[i] != '\0'; ++i) {
		*number = *number * 10 + (str[i] - '0');
	}
	return 0;
}


int switch_flags(char **argv, int number) {
	switch (argv[2][1]) {
		case 'h':
			func_flag_h(number);
			break;
		case 'p':
			func_flag_p(number);
			break;
		case 's':
			func_flag_s(number);
			// print_hex_digits(number);
			break;
		case 'e':
			if (number > 10) {
				return 666;
			}
			func_flag_e(number);
			break;
		case 'a':
			func_flag_a(number);
			break;
		case 'f':
			func_flag_f(number);
			break;
		default:
			return 666;
	}
	return 0;
}

int main(int argc, char **argv) {
	// чекаем что число аргументов вообще верное
	if (argc != 3) {
		printf("Не смог, Не дано");
		return 1234;
	}

    // заводим переменные под число
	int x = 0;

	
	//пытаемся перевести число из строки в int
	if (string_to_int(argv[1], &x)) {
		printf("Ты снова не смог");
		return 2134345647;
	}

	//проверяем правильность флагов
	if ((argv[2][0] != '-' && argv[2][0] != '/') || (argv[2][2] != '\0')) {
		printf("Флаги жи есть?");
		return 1;
	}


	//пытаемся указать флаг
	if (switch_flags(argv, x) == 666) {
		printf("ТЫ ПРОСТО ЧУДО");
		return 666;
	}

	return 0;
}
