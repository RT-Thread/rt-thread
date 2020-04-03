/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <nuclei_sdk_hal.h>

ssize_t _write(int fd, const void* ptr, size_t len)
{
    if (!isatty(fd)) {
        return -1;
    }

    const uint8_t * writebuf = (const uint8_t *)ptr;
    for (size_t i = 0; i < len; i ++) {
        if (writebuf[i] == '\n') {
            uart_write(SOC_DEBUG_UART, '\r');
        }
        uart_write(SOC_DEBUG_UART, writebuf[i]);
    }
    return len;
}
