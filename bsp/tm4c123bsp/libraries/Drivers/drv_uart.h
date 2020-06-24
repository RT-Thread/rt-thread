#ifndef _DRV_UART_H_
#define _DRV_UART_H_

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "rtdevice.h"

/* tm4c123 config class */
struct tm4c123_uart_config
{
    const char *name;
	  uint32_t    uartbase;
	  uint32_t    baudrate;
	  uint32_t    mode;
    //struct dma_config *dma_rx;
    //struct dma_config *dma_tx;
};


/* tm4c123 uart dirver class */
struct tm4c123_uart
{    
    struct tm4c123_uart_config *config;
    uint32_t   uartintbase;	
    
#ifdef RT_SERIAL_USING_DMA
#endif
	
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

extern int rt_hw_usart_init(void);

#endif /*_DRV_UART_H_*/


