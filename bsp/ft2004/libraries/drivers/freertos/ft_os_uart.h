/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:40:12
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef FT_OS_UART_H
#define FT_OS_UART_H

#include "ft_uart.h"
#include "ft_parameters.h"
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

#include "ft_types.h"

#define UART0_ID FT_UART0_ID
#define UART1_ID FT_UART1_ID
#define UART2_ID FT_UART2_ID
#define UART3_ID FT_UART3_ID

/*!
* @cond RTOS_PRIVATE
* @name UART FreeRTOS handler
*
* These are the only valid states for txEvent and rxEvent 
*/
/*@{*/
/*! @brief Event flag - transfer complete. */
#define RTOS_UART_COMPLETE 0x1
/*! @brief Event flag - hardware buffer overrun. */
#define RTOS_UART_HARDWARE_BUFFER_OVERRUN 0x2
/*！ @brief Event flag Receive is error */
#define RTOS_UART_RECV_ERROR 0x4

/*@}*/

typedef struct
{
    u32 Uart_Instance; /* select uart global object */
    u32 Isr_Priority;  /* irq Priority */
} Ft_Os_Uart_Config;

typedef struct
{
    Ft_Uart UartObj;               /* Uart Object */
    SemaphoreHandle_t rxSemaphore; /*!< RX semaphore for resource sharing */
    SemaphoreHandle_t txSemaphore; /*!< TX semaphore for resource sharing */
    EventGroupHandle_t rxEvent;    /*!< RX completion event */
    EventGroupHandle_t txEvent;    /*!< TX completion event */
} Ft_Os_Uart;

void Ft_Os_UartInit(Ft_Os_Uart *OsUartPtr, Ft_Os_Uart_Config *Config);
s32 Ft_Os_UartBlockingSend(Ft_Os_Uart *OsUartPtr, u8 *buffer, u32 length);
s32 Ft_Os_UartReceiveBuffer(Ft_Os_Uart *OsUartPtr, u8 *buffer, u32 length, u32 *Received);

#endif // !
