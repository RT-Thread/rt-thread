#include "hbird.h"
#include "hbird_uart.h"

int32_t uart_init(UART_TypeDef *uart, uint32_t baudrate)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    uart->DIV = SystemCoreClock / baudrate - 1;
    uart->TXCTRL |= UART_TXEN;
    uart->RXCTRL |= UART_RXEN;
    return 0;
}

int32_t uart_config_stopbit(UART_TypeDef *uart, UART_STOP_BIT stopbit)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    uint32_t stopval = stopbit;
    stopval = (stopbit << UART_TXCTRL_NSTOP_OFS) & UART_TXCTRL_TXCNT_MASK;
    uart->TXCTRL &= stopval | (~UART_TXCTRL_TXCNT_MASK);
    return 0;
}

int32_t uart_write(UART_TypeDef *uart, uint8_t val)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    while (uart->TXFIFO & UART_TXFIFO_FULL);
    uart->TXFIFO = val;
    return 0;
}

uint8_t uart_read(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    while (uart->RXFIFO & UART_RXFIFO_EMPTY);
    return (uint8_t)(uart->RXFIFO);
}

int32_t uart_set_tx_watermark(UART_TypeDef *uart, uint32_t watermark)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    watermark = (watermark << UART_TXCTRL_TXCNT_OFS) & UART_TXCTRL_TXCNT_MASK;
    uart->TXCTRL &= watermark | (~UART_TXCTRL_TXCNT_MASK);
    return 0;
}

int32_t uart_enable_txint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    uart->IE |= UART_IE_TXIE_MASK;
    return 0;
}

int32_t uart_disable_txint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    uart->IE &= ~UART_IE_TXIE_MASK;
    return 0;
}

int32_t uart_set_rx_watermark(UART_TypeDef *uart, uint32_t watermark)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    watermark = (watermark << UART_RXCTRL_RXCNT_OFS) & UART_RXCTRL_RXCNT_MASK;
    uart->RXCTRL &= watermark | (~UART_RXCTRL_RXCNT_MASK);
    return 0;
}

int32_t uart_enable_rxint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    uart->IE |= UART_IE_RXIE_MASK;
    return 0;
}

int32_t uart_disable_rxint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    uart->IE &= ~UART_IE_RXIE_MASK;
    return 0;
}
