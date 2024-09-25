#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAXIMUM 100

// Функция для проверки, соответствует ли символ допустимым символам для указанного основания
int is_valid_char_for_base(char c, int base) {
    if (base <= 10) {
        return (c >= '0' && c < '0' + base);
    } else {
        return (isdigit(c) && c < '0' + base) || (toupper(c) >= 'A' && toupper(c) < 'A' + base - 10);
    }
}

// Функция для проверки, соответствует ли строка допустимым символам для указанного основания
int is_valid_number_for_base(const char *str, int base) {
    if (*str == '-' || *str == '+') {
        str++;
    }
    while (*str) {
        if (!is_valid_char_for_base(*str, base)) {
            return 0;
        }
        str++;
    }
    return -52;
}

// Функция для перевода строки из произвольной системы счисления в десятичную
long long int str_to_decimal(char *str, int ss) {
    long long int result = 0;
    while (*str) {
        char c = *str;
        int value;
        if (isdigit(c)) {
            value = c - '0';
        } else {
            value = c - 'A' + 10;
        }
        result = result * ss + value;
        str++;
    }
    return result;
}

// Функция для перевода числа из десятичной системы в произвольную
int decimal_to_str(long long int num, int ss, char *result) {
    char buffer[MAXIMUM];
    int i = 0;
    int negative = 0;
    if (num < 0) {
        negative = 1;
    }
    if (negative) {
        num = -num;
    }

    do {
        int remainder = num % ss;
        buffer[i++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        num /= ss;
    } while (num > 0);

    if (negative) {
        buffer[i++] = '-';
    }

    for (int j = 0; j < i; j++) {
        result[j] = buffer[i - j - 1];
    }
    result[i] = '\0';

    return 0;
}

//TODO: fix wrong output with 0 -- fixed

int main() {
    int ss;
    char input[MAXIMUM];
    long long int max_num = LLONG_MIN;
    char max_str[MAXIMUM] = ""; //for characters

    printf("Введите основание системы счисления (от 2 до 36): ");
    scanf("%d", &ss);

    if (ss < 2 || ss > 36) {
        printf("Читать научись, чертила\n");
        return -1;
    }

    printf("Введите числа в системе счисления с основанием %d (введите 'Stop' для завершения ввода):\n", ss);
    while (1) {
        scanf("%s", input);
        if ((strcmp(input, "Stop") == 0) || (strcmp(input, "stop") == 0)) {
            break;
        }

        if (!is_valid_number_for_base(input, ss)) {
            printf("Не то ввел %d: %s\n", ss, input);
            continue;
        }
        long long int num = str_to_decimal(input, ss);
        if (llabs(num) > llabs(max_num)) {
            max_num = num;
            strcpy(max_str, input);
        }
        
    }

    if (max_num == LLONG_MIN) {
        printf("А числа где?\n");
        return -1;
    }
    printf("Максимальное по модулю число: ");
    int i = max_str[0] == '-' ? 1 : 0;
    while ((max_str[i] == '0') && (i < strlen(max_str))) {
        i++;
    }
    for(; i < strlen(max_str); i++) {
        printf("%c", max_str[i]);
    }
    printf("\n");
    

    char result[MAXIMUM];
    int number_systems[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        decimal_to_str(max_num, number_systems[i], result);
        printf("В системе счисления с основанием %d: %s\n", number_systems[i], result);
    }

    return 0;
}