#include <stdio.h>
#include "qcrack_checksum.c"
#include "flowlibdir_decode.c"
#include "reverse_bits.c"
#include "sku_decrypt.c"

int main(void) {
    printf("Q12345678901 is ");
    if(qcrack_checksum("Q12345678901") <= 0) {
        printf("not ");
    }
    printf("valid\n");

    printf("Q00000000260 is ");
    if(qcrack_checksum("Q00000000260") <= 0) {
        printf("not ");
    }
    printf("valid\n");

    printf("Q23349539202 is ");
    if(qcrack_checksum("Q23349539202") <= 0) {
        printf("not ");
    }
    printf("valid\n");
  
    printf("%d\n", other_stuff("Q12345678901"));
    printf("0x%x\n", other_stuff("Q12345678901"));
    printf("game: %s, game num: %d\n", "Q12345678901", game_num("Q12345678901"));

//Q33333961566 ?
    //flowlibdir();

    uint32_t val = 0;
    uint32_t reverse = reverse_bits(val, 8);

    printf("reverse of %d is %d\n", val, reverse);

    val = 1;
    reverse = reverse_bits(val, 8);

    printf("reverse of %d is %d\n", val, reverse);
    
    val = 2;
    reverse = reverse_bits(val, 8);

    printf("reverse of %d is %d\n", val, reverse);

    val = 8;
    reverse = reverse_bits(val, 8);

    printf("reverse of %d is %d\n", val, reverse);

    val = 12;
    reverse = reverse_bits(val, 8);

    val = 15;
    reverse = reverse_bits(val, 8);

    printf("reverse of %d is %d\n", val, reverse);


    decrypt_sku();
    encrypt_sku();
    
    return 0;
}
