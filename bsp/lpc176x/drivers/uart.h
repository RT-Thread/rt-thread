#ifndef __UART_H__
#define __UART_H__

void rt_hw_uart_init(void);
void rt_uart_precise_baudset(rt_uint32_t uartclk, rt_uint32_t bps, rt_uint8_t *m_fdr, rt_uint32_t *m_fdiv);

#endif
