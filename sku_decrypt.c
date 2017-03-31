#include <stdio.h>
#include "reverse_bits.c"
#define SKU_BUFF_SIZE 1024

//zero index base fibonacci
int fib(int n) {
    int a=1, b=1, temp, i;

    for(i = 2; i<=n; ++i) {
        temp = b;
        b = temp + a;
        a = temp;
    }

    return b;
}

void encrypt_sku(void) {
FILE* sku17;
    FILE* skutestout;
    char sku_buffer[SKU_BUFF_SIZE];
    int num_bytes_read;

    if((sku17 = fopen("sku.testout", "r")) == NULL) {
        printf("couldn't open input file sku.17\n");
        return;
    }

    if((skutestout = fopen("sku.test17out", "w")) == NULL) {
        printf("couldn't open output file sku.testout\n");
        return;
    }
    
    //while fread doesn't return zero bytes read?
    while(num_bytes_read = fread(sku_buffer, 1, SKU_BUFF_SIZE, sku17)) {
        //for bytes 1 to (num_bytes_read-1)
        //   xor with that byte, prev byte, and that fib num
        int current_byte;
        sku_buffer[0] = reverse_bits(sku_buffer[0], 8);
        for(current_byte = num_bytes_read - 1; current_byte > 0; --current_byte) {
            sku_buffer[current_byte] =
                sku_buffer[current_byte-1] ^ sku_buffer[current_byte] ^ (fib(current_byte) & 0xFF);
        }

        

        fwrite(sku_buffer, num_bytes_read, 1, skutestout);
    }

    fclose(sku17);
    fclose(skutestout);

    return;    
}

void decrypt_sku(void) {
    FILE* sku17;
    FILE* skutestout;
    char sku_buffer[SKU_BUFF_SIZE];
    int num_bytes_read;

    if((sku17 = fopen("sku.17", "r")) == NULL) {
        printf("couldn't open input file sku.17\n");
        return;
    }

    if((skutestout = fopen("sku.testout", "w")) == NULL) {
        printf("couldn't open output file sku.testout\n");
        return;
    }
    
    //while fread doesn't return zero bytes read?
    while(num_bytes_read = fread(sku_buffer, 1, SKU_BUFF_SIZE, sku17)) {
        //for bytes 1 to (num_bytes_read-1)
        //   xor with that byte, prev byte, and that fib num
        int current_byte;
        for(current_byte = 1; current_byte < num_bytes_read; ++current_byte) {
            sku_buffer[current_byte] =
                sku_buffer[current_byte-1] ^ sku_buffer[current_byte] ^ (fib(current_byte) & 0xFF);
        }

        sku_buffer[0] = reverse_bits(sku_buffer[0], 8);

        fwrite(sku_buffer, num_bytes_read, 1, skutestout);
    }

    fclose(sku17);
    fclose(skutestout);

    return;
}
