#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void symbol_in_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

int for_4_ss(char *word, char *result) {
    int index = 0;
    for (int i = 0; word[i]; i++) {
        int ascii_value = (int)word[i];
        char buf[20]; 
        int pos = 0;
        while (ascii_value > 0) {
            buf[pos++] = (ascii_value % 4) + '0';
            ascii_value /= 4;
        }
        while (pos > 0) {
            result[index++] = buf[--pos];
        }
        result[index++] = ' ';
    }
    result[index - 1] = '\0';

    return 0;
}

void to_8_ss(char *word, char *result) {
    int index = 0;
    for (int i = 0; word[i]; i++) {
        int ascii_value = (int)word[i];
        char buff[20];
        int pos = 0;
        
        

        while (ascii_value > 0) {
            buff[pos++] = (ascii_value % 8) + '0';
            ascii_value /= 8;
        }
        

        while (pos > 0) {
            result[index++] = buff[--pos];
        }
        result[index++] = ' '; 
    }
    result[index - 1] = '\0';
}

int func_for_flag_a(FILE *input, FILE *output, int *end_of_file, int word_position) {
    char leksema[100] = {0};
    
    
    int symbol;
    int word_started = 0;
    int index = 0;

    //чтобы скипнуть пробелы
    while ((symbol = fgetc(input)) != EOF && isspace(symbol)) {

    };

    if (symbol == EOF) {
        *end_of_file = 1;
        return 0;
    }

    leksema[index++] = symbol;
    word_started = 1;

    while ((symbol = fgetc(input)) != EOF && !isspace(symbol)) {
        leksema[index++] = symbol;
    }
    leksema[index] = '\0';

    //пошли делать преобразования
    if (word_position % 10 == 0) {
        symbol_in_lowercase(leksema);
        char base4_word[500] = {0};
        for_4_ss(leksema, base4_word);
        fputs(base4_word, output);
    }  else if ((word_position % 2 == 0) && (word_position % 10 != 0)) {
        symbol_in_lowercase(leksema);
        fputs(leksema, output);
    } else if ((word_position % 5 == 0) && (word_position % 10 != 0)) {
        char base8_word[500] = {0};
        to_8_ss(leksema, base8_word);
        fputs(base8_word, output);
    }else {
        fputs(leksema, output);
    }

    return word_started;
}

int func_for_flag_r(FILE *input, FILE *output, int *end_of_file, int *is_first_word) {
    int c;
    int word_started = 0;


    while ((c = fgetc(input)) != EOF && isspace(c)) {

    };

    if (c == EOF) {
        *end_of_file = 1;
        return 0;
    }
    if (!(*is_first_word)) {
        fputc(' ', output);
    } else {
        *is_first_word = 0;
    }

    fputc(c, output);
    word_started = 1;

    while ((c = fgetc(input)) != EOF && !isspace(c)) {
        fputc(c, output);
    }

    return word_started;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("МУЖИК учи матчасть\n");
        return 5252525;
    }

    int flags = 0;

    //если флаг -a 
    if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a") == 0) {
        flags = 1;
        FILE *file_in = fopen(argv[2], "r");
        if (file_in == NULL) {
            printf("Я не умею читать");
            return 1;
        }
        FILE *file_out = fopen(argv[3], "w");
        if (file_out == NULL) {
            printf("Я не умею писать");
            fclose(file_in);
            return 1;
        }
        int end = 0; 
        int pos = 1; 

        while (!end) {
            if (func_for_flag_a(file_in, file_out, &end, pos)) {
                fputc(' ', file_out);
                pos++;
            }
        }
    } 
    
    //если флаг -r
    if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "/r") == 0) {
        flags = 1;
        FILE *file1 = fopen(argv[2], "r");
        if (file1 == NULL) {
            printf("Я не умею читать");
            return 1;
        }
        FILE *file2 = fopen(argv[3], "r");
        if (file2 == NULL) {
            fprintf(stderr, "и снова я не научился читать");
            fclose(file1);
            fclose(file2);
            return 1;
        }
        FILE *file_out = fopen(argv[4], "w");
        if (file_out == NULL) {
            printf("Я не умею писать");
            fclose(file1);
            fclose(file2);
            fclose(file_out);
            return 1;
        }
        int eof1 = 0, eof2 = 0;  
        int is_first_word = 1;
        while (!eof1 || !eof2) {
            if (!eof1) {
                func_for_flag_r(file1, file_out, &eof1, &is_first_word);
            }
            if (!eof2) {
                func_for_flag_r(file2, file_out, &eof2, &is_first_word);
            }
        }
        fclose(file2);
        fclose(file1);
        fclose(file_out);
    }
    
    if (flags == 0) {
        printf("с флагами что-то не так");
        return 255;
    }

    return 0;
}
