/* See LICENSE of license details. */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <gd32vf103.h>

#if   defined (__GNUC__)
#include <unistd.h>
#include <sys/types.h>
#endif

#include "stub.h"
#include "gd32vf103.h"

//typedef unsigned int size_t;
extern int _put_char(int ch) __attribute__((weak));

#if   defined (__ICCRISCV__)
size_t __write(int handle, const unsigned char *buf, size_t bufSize)
{
  size_t nChars = 0;

  if (handle == -1)
  {
    return 0;
  }

  for (; bufSize > 0; --bufSize)
  {
    _put_char((uint8_t) *buf);
    ++buf;
    ++nChars;
  }

  return nChars;
 }

int puts(const char* string) {
    return __write(0, (const void *) string, strlen(string));
}

#elif defined ( __GNUC__ )
ssize_t _write(int fd, const void* ptr, size_t len) {
    const uint8_t * current = (const uint8_t *) ptr;
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
#endif

int _put_char(int ch)
{
    usart_data_transmit(USART0, (uint8_t) ch );
    while (usart_flag_get(USART0, USART_FLAG_TBE)== RESET){
    }

    return ch;
}
