#include <stdio.h>

void main(void) {
    FILE* fp;

    if((fp = fopen("QCRYPT.TST", "w")) == NULL) {
        printf("couldn't not open qcrypt.tst for writing\n");
        return;
    }

    int len = 512;
    int vals[512] = {0, 1, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < len; ++i) {
        if(fwrite(&vals[i], 1, 1, fp) != 1) {
            printf("didn't write 1 object to qcrypt.tst\n");
        }
    }
}
