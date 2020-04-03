// See LICENSE for license details.

#ifndef _HBIRD_UART_H
#define _HBIRD_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Register offsets */
#define UART_REG_TXFIFO         0x00
#define UART_REG_RXFIFO         0x04
#define UART_REG_TXCTRL         0x08
#define UART_REG_RXCTRL         0x0c
#define UART_REG_IE             0x10
#define UART_REG_IP             0x14
#define UART_REG_DIV            0x18

/* TXCTRL register */
#define UART_TXEN               0x1
#define UART_TXWM(x)            (((x) & 0xffff) << 16)

/* RXCTRL register */
#define UART_RXEN               0x1
#define UART_RXWM(x)            (((x) & 0xffff) << 16)

/* IP register */
#define UART_IP_TXWM            0x1
#define UART_IP_RXWM            0x2

#define UART_TXFIFO_FULL        (1<<31)
#define UART_RXFIFO_EMPTY       (1<<31)

#define UART_TXCTRL_TXCNT_OFS   (16)
#define UART_TXCTRL_TXCNT_MASK  (0x7 << UART_TXCTRL_TXCNT_OFS)
#define UART_TXCTRL_TXEN_OFS    (0)
#define UART_TXCTRL_TXEN_MASK   (0x1 << UART_TXCTRL_TXEN_OFS)
#define UART_TXCTRL_NSTOP_OFS   (1)
#define UART_TXCTRL_NSTOP_MASK  (0x1 << UART_TXCTRL_TXEN_OFS)

#define UART_RXCTRL_RXCNT_OFS   (16)
#define UART_RXCTRL_RXCNT_MASK  (0x7 << UART_RXCTRL_RXCNT_OFS)
#define UART_RXCTRL_RXEN_OFS    (0)
#define UART_RXCTRL_RXEN_MASK   (0x1 << UART_RXCTRL_RXEN_OFS)

#define UART_IE_TXIE_OFS        (0)
#define UART_IE_TXIE_MASK       (0x1 << UART_IE_TXIE_OFS)
#define UART_IE_RXIE_OFS        (1)
#define UART_IE_RXIE_MASK       (0x1 << UART_IE_RXIE_OFS)

#define UART_IP_TXIP_OFS        (0)
#define UART_IP_TXIP_MASK       (0x1 << UART_IP_TXIP_OFS)
#define UART_IP_RXIP_OFS        (1)
#define UART_IP_RXIP_MASK       (0x1 << UART_IP_RXIP_OFS)

typedef enum uart_stop_bit {
    UART_STOP_BIT_1 = 0,
    UART_STOP_BIT_2 = 1
} UART_STOP_BIT;

int32_t uart_init(UART_TypeDef *uart, uint32_t baudrate);
int32_t uart_config_stopbit(UART_TypeDef *uart, UART_STOP_BIT stopbit);
int32_t uart_write(UART_TypeDef *uart, uint8_t val);
uint8_t uart_read(UART_TypeDef *uart);
int32_t uart_set_tx_watermark(UART_TypeDef *uart, uint32_t watermark);
int32_t uart_enable_txint(UART_TypeDef *uart);
int32_t uart_disable_txint(UART_TypeDef *uart);
int32_t uart_set_rx_watermark(UART_TypeDef *uart, uint32_t watermark);
int32_t uart_enable_rxint(UART_TypeDef *uart);
int32_t uart_disable_rxint(UART_TypeDef *uart);

#ifdef __cplusplus
}
#endif
#endif /* _HBIRD_UART_H */
