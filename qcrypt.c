#include <stdio.h>
#include <stdint.h>

void main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return;
    }
    
    FILE* qcrypt_input;
    FILE* qcrypt_output;

    if((qcrypt_input = fopen(argv[1], "r")) == NULL) {
        printf("couldn't open %s for writing\n", argv[1]);
        return;
    }

    if((qcrypt_output = fopen(argv[2], "w")) == NULL) {
        printf("couldn't  open %s for writing\n", argv[2]);
    }

    uint8_t offset = 7;
    int c;

    while((c = fgetc(qcrypt_input)) != EOF) {
        fputc(c ^ offset++, qcrypt_output);
    }
}
