//utility to convert dumped mem to C array format

#include <stdio.h>
#include <stdint.h>

void main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return;
    }
    
    FILE* mem_in;
    FILE* vals_out;

    if((mem_in = fopen(argv[1], "r")) == NULL) {
        printf("couldn't open first source %s for writing\n", argv[1]);
        return;
    }

    if((vals_out = fopen(argv[2], "w")) == NULL) {
        printf("couldn't  open destination %s for writing\n", argv[2]);
        return;
    }

    int c1, c2, c3, c4;
    int count = 0;
    fputc(' ', vals_out);
    fputc(' ', vals_out);
    fputc(' ', vals_out);
    fputc(' ', vals_out);
    while((c1 = fgetc(mem_in)) != EOF ) {


        if((c2 = fgetc(mem_in)) != EOF) {
            if((c3 = fgetc(mem_in)) != EOF) {
                if((c4 = fgetc(mem_in)) != EOF) {
                }
                else {
                    printf("unexpected end at char 4\n");
                    break;
                }
            }
            else {
                printf("unexpected end at char 3\n");
                break;
            }
        }
        else {
            printf("unexpected end at char 2\n");
            break;
        }

        fputc('0', vals_out);
        fputc('x', vals_out);
        fputc(c3, vals_out);
        fputc(c4, vals_out);
        fputc(c1, vals_out);
        fputc(c2, vals_out);

        fputc(',', vals_out);
        fputc(' ', vals_out);
        count++;
        if(count >= 10) {
            count = 0;
            fputc('\n', vals_out);
    fputc(' ', vals_out);
    fputc(' ', vals_out);
    fputc(' ', vals_out);
    fputc(' ', vals_out);
        }
    }
}
