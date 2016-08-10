/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "fsl_smartcard_driver.h"
#include "fsl_smartcard_uart_driver.h"
#include "fsl_smartcard_ncn8025_driver.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern uint32_t g_smartcardInstance;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void UART_DRV_IRQHandler(uint32_t instance);
extern void SMARTCARD_UART_DRV_IRQHandler(uint32_t instance);
extern void SMARTCARD_UART_DRV_ErrIRQHandler(uint32_t instance);
/*******************************************************************************
 * Code
 ******************************************************************************/

/* MQX RTOS require installation of interrupt handlers. That's why is added condition 
   FSL_RTOS_MQX */
#if defined (KL25Z4_SERIES) || defined (KL46Z4_SERIES) || defined (KV10Z7_SERIES)
/* NOTE: If a sub-family has UART0 separated as another IP, it will be handled by
 * LPSCI driver. So, the IRQ will start from 1, but the instance passed into
 * the UART_DRV_IRQHandler will be cut down by 1 to work with the baseAddr
 * index. */
#if (UART0_INSTANCE_COUNT)

#if (UART_INSTANCE_COUNT > 0)
/* Implementation of UART1 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART1_IRQHandler(void)
#else
void UART1_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 0)
    {
        SMARTCARD_UART_DRV_IRQHandler(0);
    }
    else
    {
        UART_DRV_IRQHandler(0);
    }
}
#endif

#if (UART_INSTANCE_COUNT > 1)
/* Implementation of UART2 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART2_IRQHandler(void)
#else
void UART2_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 1)
    {
        SMARTCARD_UART_DRV_IRQHandler(1);
    }
    else
    {
        UART_DRV_IRQHandler(1);
    }
}
#endif

#else   /* UART0_INSTANCE_COUNT */

#if (UART_INSTANCE_COUNT > 0)
/* Implementation of UART0 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART0_IRQHandler(void)
#else
void UART0_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 0)
    {
        SMARTCARD_UART_DRV_IRQHandler(0);
    }
    else
    {
        UART_DRV_IRQHandler(0);
    }
}
#endif

#if (UART_INSTANCE_COUNT > 1)
/* Implementation of UART1 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART1_IRQHandler(void)
#else
void UART1_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 1)
    {
        SMARTCARD_UART_DRV_IRQHandler(1);
    }
    else
    {
        UART_DRV_IRQHandler(1);
    }
}
#endif

#if (UART_INSTANCE_COUNT > 2)
/* Implementation of UART2 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART2_IRQHandler(void)
#else
void UART2_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 2)
    {
        SMARTCARD_UART_DRV_IRQHandler(2);
    }
    else
    {
        UART_DRV_IRQHandler(2);
    }
}
#endif

#endif /* UART0_INSTANCE_COUNT */

#elif defined (K64F12_SERIES) || defined (K24F12_SERIES) || defined (K63F12_SERIES) || \
      defined (K22F51212_SERIES) || defined (K22F25612_SERIES) || defined (K22F12810_SERIES) || \
      defined (KV31F51212_SERIES) || defined (KV31F25612_SERIES) || defined (KV31F12810_SERIES) || \
      defined (K70F12_SERIES) || defined(K60D10_SERIES) || defined(K24F25612_SERIES) || \
      defined (KV30F12810_SERIES) || defined (K02F12810_SERIES) || defined (K21DA5_SERIES) || \
      defined (K21FA12_SERIES) || defined (KW24D5_SERIES) || defined (K26F18_SERIES) || \
      defined (K65F18_SERIES) || defined (K66F18_SERIES) || defined (KV46F15_SERIES)

#if (UART_INSTANCE_COUNT > 0)
/* Implementation of UART0 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART0_RX_TX_IRQHandler(void)
#else
void UART0_RX_TX_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 0)
    {
        SMARTCARD_UART_DRV_IRQHandler(0);
    }
    else
    {
        UART_DRV_IRQHandler(0);
    }
}
/* Enabled only for smartcard/uart-iso7826 function */
#if (FSL_RTOS_MQX)
void MQX_UART0_ERR_IRQHandler(void)
#else
void UART0_ERR_IRQHandler(void)
#endif
{
    SMARTCARD_UART_DRV_ErrIRQHandler(0);
}
#endif

#if (UART_INSTANCE_COUNT > 1)
/* Implementation of UART1 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART1_RX_TX_IRQHandler(void)
#else
void UART1_RX_TX_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 1)
    {
        SMARTCARD_UART_DRV_IRQHandler(1);
    }
    else
    {
        UART_DRV_IRQHandler(1);
    }
}
/* Enabled only for smartcard/uart-iso7826 function */
#if (FSL_RTOS_MQX)
void MQX_UART1_ERR_IRQHandler(void)
#else
void UART1_ERR_IRQHandler(void)
#endif
{
    SMARTCARD_UART_DRV_ErrIRQHandler(1);
}
#endif

#if (UART_INSTANCE_COUNT > 2)
/* Implementation of UART2 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART2_RX_TX_IRQHandler(void)
#else
void UART2_RX_TX_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 2)
    {
        SMARTCARD_UART_DRV_IRQHandler(2);
    }
    else
    {
        UART_DRV_IRQHandler(2);
    }
}
/* Enabled only for smartcard/uart-iso7826 function */
#if (FSL_RTOS_MQX)
void MQX_UART2_ERR_IRQHandler(void)
#else
void UART2_ERR_IRQHandler(void)
#endif
{
    SMARTCARD_UART_DRV_ErrIRQHandler(2);
}
#endif

#if (UART_INSTANCE_COUNT > 3)
/* Implementation of UART3 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART3_RX_TX_IRQHandler(void)
#else
void UART3_RX_TX_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 3)
    {
        SMARTCARD_UART_DRV_IRQHandler(3);
    }
    else
    {
        UART_DRV_IRQHandler(3);
    }
}
/* Enabled only for smartcard/uart-iso7826 function */
#if (FSL_RTOS_MQX)
void MQX_UART3_ERR_IRQHandler(void)
#else
void UART3_ERR_IRQHandler(void)
#endif
{
    SMARTCARD_UART_DRV_ErrIRQHandler(3);
}
#endif

#if (UART_INSTANCE_COUNT > 4)
/* Implementation of UART4 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART4_RX_TX_IRQHandler(void) {
#else
  void UART4_RX_TX_IRQHandler(void) {
#endif

    if(g_smartcardInstance == 4)
    {
        SMARTCARD_UART_DRV_IRQHandler(4);
    }
    else
    {
        UART_DRV_IRQHandler(4);
    }
}
/* Enabled only for smartcard/uart-iso7826 function */
#if (FSL_RTOS_MQX)
void MQX_UART4_ERR_IRQHandler(void)
#else
void UART4_ERR_IRQHandler(void)
#endif
{
    SMARTCARD_UART_DRV_ErrIRQHandler(5);
}
#endif

#if (UART_INSTANCE_COUNT > 5)
/* Implementation of UART5 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART5_RX_TX_IRQHandler(void)
#else
void UART5_RX_TX_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 5)
    {
        SMARTCARD_UART_DRV_IRQHandler(5);
    }
    else
    {
        UART_DRV_IRQHandler(5);
    }
}
/* Enabled only for smartcard/uart-iso7826 function */
#if (FSL_RTOS_MQX)
void MQX_UART5_ERR_IRQHandler(void)
#else
void UART5_ERR_IRQHandler(void)
#endif
{
    SMARTCARD_UART_DRV_ErrIRQHandler(5);
}
#endif

#elif defined (KL43Z4_SERIES)
#if (UART_INSTANCE_COUNT > 0)
/* Implementation of UART1 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_UART2_FLEXIO_IRQHandler(void)
#else
void UART2_FLEXIO_IRQHandler(void)
#endif
{
    if(g_smartcardInstance == 0)
    {
        SMARTCARD_UART_DRV_IRQHandler(0);
    }
    else
    {
        UART_DRV_IRQHandler(0);
    }
}
#endif

#else
    #error "No valid CPU defined!"
#endif

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTA_IRQHandler(void)
#else
void PORTA_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTA_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

#if defined (KL43Z4_SERIES)
/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTCD_IRQHandler(void)
#else
void PORTCD_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);
    PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_UART_INSTANCE);
}
#endif

#if defined (K22F12810_SERIES) || defined (K22F25612_SERIES) || defined (K22F51212_SERIES) || \
    defined (K21FA12_SERIES)
/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTD_IRQHandler(void)
#else
void PORTD_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}
#endif

#if defined (K22F12810_SERIES) || defined (K22F25612_SERIES) || defined (K22F51212_SERIES)
/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTB_IRQHandler(void)
#else
void PORTB_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTB_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTC_IRQHandler(void)
#else
void PORTC_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTE_IRQHandler(void)
#else
void PORTE_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTE_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

