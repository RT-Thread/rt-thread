#ifndef API_HUART_H__
#define API_HUART_H__

enum {
    HUART_TR_PA7    = 0,
    HUART_TR_PB2,
    HUART_TR_PB3,
    HUART_TR_PE7,
    HUART_TR_PA1,
    HUART_TR_PA6,
    HUART_TR_PB1,
    HUART_TR_PB4,
    HUART_TR_PE6,
    HUART_TR_PA0,
};

void huart_init_do(uint8_t tx_port, uint8_t rx_port, uint32_t baud_rate, uint8_t *buf, uint16_t buf_size);
void huart_setbaudrate(unsigned int baudrate);
void huart_putchar(const char ch);
void huart_tx(const void *buf, unsigned int len);
unsigned int huart_get_rxcnt(void);
void huart_rxfifo_clear(void);
char huart_getchar(void);
void huart_exit(void);

void huart_if_rx_ovflow(void);

#endif
