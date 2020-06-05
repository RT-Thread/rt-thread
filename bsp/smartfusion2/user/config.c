#include "config.h"

mss_uart_instance_t * const gp_my_uart0 = &g_mss_uart0;

/* gpio and uart0 initialization */
void boardInit(void)
{
    /* mss gpio init */
    MSS_GPIO_init();
    MSS_GPIO_config(MSS_GPIO_0, MSS_GPIO_OUTPUT_MODE);
    MSS_GPIO_config(MSS_GPIO_1, MSS_GPIO_OUTPUT_MODE);

    /* mss uart0 init: 115200, 8, no, 1 */
    MSS_UART_init(gp_my_uart0, MSS_UART_115200_BAUD, 
            MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
}
INIT_BOARD_EXPORT(boardInit);

/* mss uart0 transmit one byte data */
void MSS_UART_polled_tx_byte(mss_uart_instance_t *this_uart, const uint8_t byte)
{
    uint32_t tx_ready;
    do {
        tx_ready = gp_my_uart0->hw_reg->LSR & 0x20u;
    } while(!tx_ready);
    gp_my_uart0->hw_reg->THR = byte;
}

/* docking finish component */
void rt_hw_console_output(const char *str)
{
    while(*str != '\0')
    {
        if(*str == '\n')
            MSS_UART_polled_tx_byte(gp_my_uart0, '\r');
        MSS_UART_polled_tx_byte(gp_my_uart0, *str++);
        while(!MSS_UART_tx_complete(&g_mss_uart0));
    }
}

/* docking finish component */
char rt_hw_console_getchar(void)
{
    char dat;
    uint8_t rx_size;
    do {
        rx_size = MSS_UART_get_rx(gp_my_uart0, (uint8_t *)&dat, 1);
    } while(0u == rx_size);
    return dat;
}

/* custom finish command */
extern uint32_t SystemCoreClock;
void sayHello(void)
{
     rt_kprintf("Hello RT-Thread! By SmartFusion2 M2S010\r\n");
     rt_kprintf("MSS System Core Clock: %d\r\n", SystemCoreClock);
}
MSH_CMD_EXPORT(sayHello, "say hello to console");
