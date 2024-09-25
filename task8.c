#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

long long to_ss(long long buf[100], long long buf_index, long long sys) {
    long long a = 0;
    for (long long i = 0; i < buf_index; i++) {
        a += buf[i] * pow(sys, buf_index - i - 1);
        printf("%f %f %f\n", 2*pow(36, 7), 2*pow(36, 6), 2*pow(36, 7) + 2*pow(36, 6));
    }
    
    return a;
}

int main(long long argc, char *argv[]) {
    if (argc < 3) {
        printf("НЕЕЕЕЕЕТ");
        return 52;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Меня постигла неудача");
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("меня вновь постигла неудача");
        fclose(in);
        return 1;
    }

    long long ss_for_out_file = 0;
    long long symbol;
    long long word_started = 0;

    char ss[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    long long size = sizeof(ss) / sizeof(ss[0]);

    char buf[1000];
    long long buf_index = 0;
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
            buf[buf_index++] = symbol;
        } else if (word_started) {
            buf[buf_index] = '\0';
            fprintf(out, "%s %lld %lld", buf, ss_for_out_file, to_ss(buffer_of_index, buf_index, ss_for_out_file));
            fprintf(out, "\n");
            word_started = 0;
            ss_for_out_file = 0;
        }
    }

    //на случай,если слова в конце
    if (word_started) {
        buf[buf_index] = '\0';
        fprintf(out, "%s %lld %lld", buf, ss_for_out_file, to_ss(buffer_of_index, buf_index, ss_for_out_file));
    }

    fclose(in);
    fclose(out);

    return 0;
}
