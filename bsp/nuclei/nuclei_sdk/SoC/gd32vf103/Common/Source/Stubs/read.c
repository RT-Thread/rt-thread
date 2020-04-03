#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "nuclei_sdk_hal.h"
#include "gd32vf103_usart.h"

ssize_t _read(int fd, void* ptr, size_t len)
{
    if (!isatty(fd)) {
        return -1;
    }
    uint8_t *readbuf = (uint8_t *)ptr;
    for (int i = 0; i < len; i ++) {
        readbuf[i] = usart_read(GD32_COM0);
    }
    return len;
}
