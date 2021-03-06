#include <string.h>
#include <stdlib.h>



/* returns zero if checksum isn't valid,
   positive non-zero if it is valid,
   negative non-zero if error (length not 12, challenge string not numbers)
*/
int qcrack_checksum(char *challenge) {
    char str1[5];
    char str2[8];
    unsigned long a, x, y, z, breg, sreg;

    if(strlen(challenge) != 12) {
        return -1;
    }

    strncpy(str1, challenge+1, 4);
    str1[4] = '\0';

    strncpy(str2, challenge+5, 7);
    str2[7] = '\0';

    sreg = strtoul(str1, NULL, 10);
    breg = strtoul(str2, NULL, 10);

    x = (sreg*0x3f)^breg;
    y = x/0x103;
    z = y/0x81;
    a = (z/7) + (sreg>>7) + (sreg & 0x7F) + (y%0x81) + (z%7);

    return a == x%0x103;
}

int other_stuff(char *challenge) {
    char str1[5];
    char str2[8];
    unsigned long a, x, y, z, breg, sreg, rbp0x17c, rbp0x17cLower7, edx, rbp0x184, ecx, orresult;

    if(strlen(challenge) != 12) {
        return -1;
    }

    strncpy(str1, challenge+1, 4);
    str1[4] = '\0';

    strncpy(str2, challenge+5, 7);
    str2[7] = '\0';

    sreg = strtoul(str1, NULL, 10);
    breg = strtoul(str2, NULL, 10);

    x = (sreg*0x3f)^breg;
    y = x/0x103;
    rbp0x17c = y%0x81; //game number??
    printf("%lu\n", rbp0x17c);
    z = y/0x81;
    a = (z/7) + (sreg>>7) + (sreg & 0x7F) + rbp0x17c + (z%7);
  
    rbp0x17cLower7 = rbp0x17c & 0x7F;
    edx = sreg & 0x7F;
    rbp0x184 = edx & 0xFF;
    rbp0x184 = (rbp0x184 << 3) & 0xFF;
    ecx = (z%7) & 0xFF;
      
    orresult = rbp0x184 | ecx;

    return orresult & 0xFF00;
}

int game_num(char *challenge) {
    char str1[5];
    char str2[8];
    unsigned long a, x, y, z, breg, sreg;

    if(strlen(challenge) != 12) {
        return -1;
    }

    strncpy(str1, challenge+1, 4);
    str1[4] = '\0';

    strncpy(str2, challenge+5, 7);
    str2[7] = '\0';

    sreg = strtoul(str1, NULL, 10);
    breg = strtoul(str2, NULL, 10);

    x = (sreg*0x3f)^breg;
    y = x/0x103;
    return y%0x81; 
}
