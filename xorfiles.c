#include <stdio.h>
#include <stdint.h>

void main(int argc, char* argv[]) {
    if(argc < 4) {
        printf("Usage: %s <source1> <source2> <destination>\n", argv[0]);
        return;
    }
    
    FILE* qcrypt_input1;
    FILE* qcrypt_input2;
    FILE* qcrypt_output;

    if((qcrypt_input1 = fopen(argv[1], "r")) == NULL) {
        printf("couldn't open first source %s for writing\n", argv[1]);
        return;
    }

    if((qcrypt_input2 = fopen(argv[2], "r")) == NULL) {
        printf("couldn't open second source %s for writing\n", argv[2]);
        return;
    }

    if((qcrypt_output = fopen(argv[3], "w")) == NULL) {
        printf("couldn't  open destination %s for writing\n", argv[3]);
        return;
    }

    int c1, c2;
    char xored;

    while((c1 = fgetc(qcrypt_input1)) != EOF && (c2 = fgetc(qcrypt_input2)) != EOF) {
        xored = c1 ^ c2;
        fputc(xored, qcrypt_output);
    }
}
