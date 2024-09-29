#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

long long to_ss(const long long buf[100], const long long buf_index, const long long sys) {
    long long a = 0;
    for (long long i = 0; i < buf_index; i++) {
        a += buf[i] * pow(sys, buf_index - i - 1);
        double res_one = 2*pow(36, 7);
        double res_two = 2*pow(36, 6);
        double res_three = 2*pow(36, 7) + 2*pow(36, 6);
        // printf("%f %f %f\n", res_one, res_two, res_three);
    }
    
    return a;
}

char* remove_zeros(const char* str) {

    const char* ptr = str;
    while (*ptr == '0') {
        ptr++;
    }

    
    if (*ptr == '\0') {
        return strdup("0");
    }

    
    char* result = (char*)malloc(strlen(ptr) + 1);
    if (result == NULL) {
        printf("Не смог открыть файл \n");
        printf("не смог(");
        return strdup("0");
    }

    // Копировать строку без ведущих нулей
    strcpy(result, ptr);
    return result;
}

// ./8 file_in file_out
int main(long long argc, char *argv[]) {
    if (argc != 3) {
        printf("%Ld - неправильное количество аргументов", argc);
        printf("НЕЕЕЕЕЕТ");
        return 52;
    }

    // Обработка пути файла
    char *path_in = argv[1];
    char *path_out = argv[2];

    // Удаление лишних слешей
    if (path_in[0] == '/' && path_in[1] == '/') {
        path_in++;
    }
    if (path_out[0] == '/' && path_out[1] == '/') {
        path_out++;
    }

    FILE *in = fopen(path_in, "r");
    if (in == NULL) {
        printf("Не смог открыть файл \n");
        printf("Меня постигла неудача");
        return 1;
    }

    FILE *out = fopen(path_out, "w");
    if (out == NULL) {
        printf("Не смог открыть файл \n");
        printf("меня вновь постигла неудача");
        fclose(in);
        return 1;
    }

    long long ss_for_out_file = 0;
    long long symbol;
    long long word_started = 0;

    // лучше по АСКИ таблице смотреть, но мне лень
    char ss[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    long long size = sizeof(ss) / sizeof(ss[0]);


    char *buf = (char *)malloc(1000);
    if (buf == NULL) {
        printf("Ошибка выделения памяти");
        fclose(in);
        fclose(out);
        return 1;
    }
    long long buf_index = 0;
    long long buf_size = 1000;

    long long buffer_of_index[1000];

    while ((symbol = fgetc(in)) != EOF) {
        if (!isspace(symbol)) {
            if (islower(symbol)) {
                symbol = toupper(symbol);
            }
            if (!word_started) {
                word_started = 1;
                buf_index = 0;
            }
            for (long long i = 0; i < size; i++) {
                if (symbol == ss[i]) {
                    buffer_of_index[buf_index] = i;
                    if (i + 1 >= ss_for_out_file) {
                        ss_for_out_file = i + 1;
                    }
                }
            }
            // Проверка, нужно ли увеличить размер буфера
            if (buf_index + 1 >= buf_size) {
                buf_size *= 2; // Увеличиваем размер в два раза
                buf = (char *)realloc(buf, buf_size);
                if (buf == NULL) {
                    printf("Не смог перезаписать\n");
                    printf("Я слабый?????");
                    fclose(in);
                    fclose(out);
                    free(buf);
                    return 1;
                }
            }
            buf[buf_index++] = symbol;
        } else if (word_started) {
            buf[buf_index] = '\0';
            long long res_to_ss = to_ss(buffer_of_index, buf_index, ss_for_out_file);
            char *buf_without_zero = remove_zeros(buf);
            fprintf(out, "%s %lld %lld", buf_without_zero, ss_for_out_file, res_to_ss);
            
            fprintf(out, "\n");
            word_started = 0;
            ss_for_out_file = 0;
        }
    }

    //на случай,если слова в конце
    if (word_started) {
        buf[buf_index] = '\0';
        long long res_to_ss = to_ss(buffer_of_index, buf_index, ss_for_out_file);
        fprintf(out, "%s %lld %lld", buf, ss_for_out_file, res_to_ss);
    }

    fclose(in);
    fclose(out);
    free(buf);

    return 0;
}