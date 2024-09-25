#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int delete_arabic_from_earth(FILE *input, FILE *output) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, output);
        }
    }
    return 0;
}

int latinsckiy_bukva_i_russkia(FILE *input, FILE *output) {
    int ch, count = 0;
    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch) && (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')) {
            count++;
        }
        if (ch == '\n') {
            fprintf(output, "%d\n", count);
            count = 0;
        }
    }
    if (count > 0) {
        fprintf(output, "%d\n", count);
    }

    return 0;
}

int kakoito_hardcore(FILE *input, FILE *output) {
    int ch, count = 0;
    while ((ch = fgetc(input)) != EOF) {
        if (!isalnum(ch) && !isspace(ch)) {
            count++;
        }
        if (ch == '\n') {
            fprintf(output, "%d\n", count);
            count = 0;
        }
    }
    if (count > 0) {
        fprintf(output, "%d\n", count);
    }

    return 0;
}

void menyam_na_ascii(FILE *input, FILE *output) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (isdigit(ch)) {
            fputc(ch, output);
        } else {
            fprintf(output, "%02X", (unsigned char)ch);
        }
    }
}

void parse_flags(char flag, FILE *input, FILE *output) {
    switch (flag) {
        case 'd':
            delete_arabic_from_earth(input, output);
            break;
        case 'i':
            latinsckiy_bukva_i_russkia(input, output);
            break;
        case 's':
            kakoito_hardcore(input, output);
            break;
        case 'a':
            menyam_na_ascii(input, output);
            break;
        default:
            printf("Что?");
            exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("не то");
        return 1;
    }
    char *output = NULL;
    char *flag = argv[1];
    FILE *input = fopen(argv[2], "r");
    if (!input) {
        printf("внимание, пожарная тревога");
        return 1;
    }

    int n = 0;
    if (strlen(flag) > 2 && flag[1] == 'n') {
        n = 1;
        if (argc < 4) {
            printf("а имя ты указать не хочешь?");
            return 542;
        }
        output = argv[3];
    } else {
        output = malloc(strlen(argv[2]) + 5);
        if (output == NULL) {
            free(output);
            printf("Маловато памяти");
            return 21323465;
        }
        sprintf(output, "out_%s", argv[2]);
    }

    FILE *output_file = fopen(output, "w");
    if (!output_file) {
        printf("внимание, пожарная тревога");
        fclose(input);
        return 12354;
    }

    char flag_input = flag[1];
    if (n == 1) {
        flag_input = flag[2];
    }

    parse_flags(flag_input, input, output_file);

    
    //чистим после себя
    fclose(input);
    fclose(output_file);
    if (n == 0) {
        free(output);
    }

    return 0;
}
