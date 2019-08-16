/* See LICENSE of license details. */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <gd32vf103.h>
#include <unistd.h>
#include <sys/types.h>

#include "stub.h"
#include "gd32vf103.h"

typedef unsigned int size_t;

extern int _put_char(int ch) __attribute__((weak));

ssize_t _write(int fd, const void* ptr, size_t len) {
    const uint8_t * current = (const uint8_t *) ptr;

//	if (isatty(fd)) 
    {
        for (size_t jj = 0; jj < len; jj++) {
            _put_char(current[jj]);

            if (current[jj] == '\n') {
                _put_char('\r');
            }
        }
        return len;
    }

    return _stub(EBADF);
}

int puts(const char* string) {
    return _write(0, (const void *) string, strlen(string));
}

int _put_char(int ch) {
    usart_data_transmit(USART0, (uint8_t) ch);
    while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET) {
    }

    return ch;
}
