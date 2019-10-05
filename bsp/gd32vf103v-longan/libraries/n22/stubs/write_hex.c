/* See LICENSE of license details. */

#include <stdint.h>
#include <unistd.h>

void write_hex(int fd, unsigned long int hex) {
    uint8_t ii;
    uint8_t jj;
    char towrite;
    write(fd, "0x", 2);
    for (ii = sizeof(unsigned long int) * 2; ii > 0; ii--) {
        jj = ii - 1;
        uint8_t digit = ((hex & (0xF << (jj * 4))) >> (jj * 4));
        towrite = digit < 0xA ? ('0' + digit) : ('A' + (digit - 0xA));
        write(fd, &towrite, 1);
    }
}
