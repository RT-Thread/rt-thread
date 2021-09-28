#include <rtthread.h>
#include <rthw.h>
#include "drv_uart_no_device.h"

#ifdef BSP_USING_DEBUG_UART
#include "bl602_uart.h"
#include "bl602_glb.h"

#define UART0_ID 0

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            UART_SendData(UART0_ID, (uint8_t *)&a, 1);
        }
        UART_SendData(UART0_ID, (uint8_t *)(str + i), 1);
    }
}

int rt_hw_debug_uart_init(void)
{
    rt_err_t result = RT_EOK;

    UART_FifoCfg_Type fifoCfg = { 0 };
    UART_CFG_Type uart_cfg = { 0 };

    /* disable all interrupt */
    UART_IntMask(UART0_ID, UART_INT_ALL, MASK);
    /* disable uart before config */
    UART_Disable(UART0_ID, UART_TXRX);

    uart_cfg.baudRate = 115200;
    uart_cfg.dataBits = 3;      /*!< Data length is 8 bits */
    uart_cfg.stopBits = 1;      /*!< 1 stop bit */
    uart_cfg.parity = 0;        /*!< UART parity none define */
    uart_cfg.uartClk = 160000000;

    GLB_Set_UART_CLK(1, 1, 0);
    /* uart init with default configuration */
    UART_Init(UART0_ID, &uart_cfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(UART0_ID, ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(UART0_ID, 100);

    /* enable uart */
    UART_Enable(UART0_ID, UART_TXRX);

    return result;
}

#endif /* BSP_USING_DEBUG_UART */
