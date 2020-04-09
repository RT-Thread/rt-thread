/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "stub.h"

ssize_t _read(int fd, void* ptr, size_t len)
{
    // The below code was copied from freedom-e-sdk, but seems it is definitely wrong, so just comment it out
    //   Need to implement this function in the future, otherwise cannot use the C scanf function
  //uint8_t * current = (uint8_t *)ptr;
  //volatile uint32_t * uart_rx = (uint32_t *)(UART0_CTRL_ADDR + UART_REG_RXFIFO);
  //volatile uint8_t * uart_rx_cnt = (uint8_t *)(UART0_CTRL_ADDR + UART_REG_RXCTRL + 2);

  //ssize_t result = 0;

  //if (isatty(fd)) {
  //  for (current = (uint8_t *)ptr;
  //      (current < ((uint8_t *)ptr) + len) && (*uart_rx_cnt > 0);
  //      current ++) {
  //    *current = *uart_rx;
  //    result++;
  //  }
  //  return result;
  //}

  return _stub(EBADF);
}
