#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_uart_config
{
    const char *name;
    uint32_t uart_base;
    IRQn_Type irqn;
};

/* gd32 uart dirver class */
struct gd32_uart
{
    struct gd32_uart_config *config;
    struct rt_serial_device serial;
};

int rt_hw_usart_init(void);

#endif /* __DRV_USART_H__ */

/******************* end of file *******************/
