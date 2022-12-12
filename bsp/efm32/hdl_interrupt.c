/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-29   onelife     Initial creation for EFM32
 * 2011-07-12   onelife     Disable interrupts in GPIO handler
 * 2011-12-09   onelife     Add giant gecko support
 * 2011-12-09   onelife     Add UART module support
 * 2011-12-09   onelife     Add LEUART module support
 * 2011-12-27   onelife     Utilize "XXX_PRESENT" and "XXX_COUNT"
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_IRQHDL_DEBUG
#define hdl_debug(format,args...)           rt_kprintf(format, ##args)
#else
#define hdl_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
efm32_irq_hook_t dmaCbTable[DMA_CHAN_COUNT * 2] = {RT_NULL};
efm32_irq_hook_t timerCbTable[TIMER_COUNT]      = {RT_NULL};
#if defined(LETIMER_PRESENT)
efm32_irq_hook_t letimerCbTable[LETIMER_COUNT]  = {RT_NULL};
#endif
efm32_irq_hook_t rtcCbTable[RTC_COUNT]          = {RT_NULL};
efm32_irq_hook_t gpioCbTable[16]                = {RT_NULL};
efm32_irq_hook_t acmpCbTable[ACMP_COUNT]        = {RT_NULL};
#if defined(USART_PRESENT)
 #if defined(UART_PRESENT)
efm32_irq_hook_t usartCbTable[USART_COUNT * 2 + UART_COUNT * 2] = {RT_NULL};
 #else
efm32_irq_hook_t usartCbTable[USART_COUNT * 2]  = {RT_NULL};
 #endif
#endif
#if defined(LEUART_PRESENT)
efm32_irq_hook_t leuartCbTable[LEUART_COUNT]    = {RT_NULL};
#endif
#if defined(I2C_PRESENT)
efm32_irq_hook_t iicCbTable[I2C_COUNT]          = {RT_NULL};
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/***************************************************************************//**
 * @brief
 *  NMI exception handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void NMI_Handler(void)
{
    hdl_debug("[NMI_Handler: NOP]\n");
}

/***************************************************************************//**
 * @brief
 *  Memory manage exception handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void MemManage_Handler(void)
{
    hdl_debug("[MemManage_Handler: infinite loop]\n");
    while (1);
}

/***************************************************************************//**
 * @brief
 *  Bus fault exception handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void BusFault_Handler(void)
{
    hdl_debug("[BusFault_Handler: infinite loop]\n");
    while (1);
}

/***************************************************************************//**
 * @brief
 *  Usage fault exception handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void UsageFault_Handler(void)
{
    hdl_debug("[UsageFault_Handler: infinite loop]\n");
    while (1);
}

/***************************************************************************//**
 * @brief
 *  Supervisor call exception handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void SVC_Handler(void)
{
    hdl_debug("[SVC_Handler: NOP]\n");
}

/***************************************************************************//**
 * @brief
 *   Debug monitor exception handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void DebugMon_Handler(void)
{
    hdl_debug("[DebugMon_Handler: NOP]\n");
}

/***************************************************************************//**
 * @brief
 *  System tick timer interrupt handler
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/*******************************************************************************
 *                 STM32F10x Peripherals Interrupt Handlers
 *  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the
 *  available peripheral interrupt handler's name please refer to the startup
 *  file (startup_stm32f10x_xx.s).
/******************************************************************************/

/***************************************************************************//**
 * @brief
 *  Common DMA interrupt handler
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void DMA_IRQHandler_All(rt_uint32_t channel, rt_bool_t primary, void *user)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* invoke callback function */
    if (dmaCbTable[channel].cbFunc != RT_NULL)
    {
        (dmaCbTable[channel].cbFunc)(dmaCbTable[channel].userPtr);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common Timer0 interrupt handler
 *
 * @details
 *  This function handles Timer0 counter overflow interrupt request
 *
 * @note
 *
 ******************************************************************************/
void TIMER0_IRQHandler(void)
{
    if (TIMER0->IF & TIMER_IF_OF)
    {
        /* invoke callback function */
        if (timerCbTable[0].cbFunc != RT_NULL)
        {
            (timerCbTable[0].cbFunc)(timerCbTable[0].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(TIMER0->IFC), _TIMER_IF_OF_SHIFT, 0x1UL);
    }
}


/***************************************************************************//**
 * @brief
 *  Common Timer1 interrupt handler
 *
 * @details
 *  This function handles Timer1 counter overflow interrupt request
 *
 * @note
 *
 ******************************************************************************/
void TIMER1_IRQHandler(void)
{
    if (TIMER1->IF & TIMER_IF_OF)
    {
        /* invoke callback function */
        if (timerCbTable[1].cbFunc != RT_NULL)
        {
            (timerCbTable[1].cbFunc)(timerCbTable[1].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(TIMER1->IFC), _TIMER_IF_OF_SHIFT, 0x1UL);
    }
}

/***************************************************************************//**
 * @brief
 *  Common Timer2 interrupt handler
 *
 * @details
 *  This function handles Timer2 counter overflow interrupt request
 *
 * @note
 *
 ******************************************************************************/
void TIMER2_IRQHandler(void)
{
    if (TIMER2->IF & TIMER_IF_OF)
    {
        /* invoke callback function */
        if (timerCbTable[2].cbFunc != RT_NULL)
        {
            (timerCbTable[2].cbFunc)(timerCbTable[2].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(TIMER2->IFC), _TIMER_IF_OF_SHIFT, 0x1UL);
    }
}

#if defined(LETIMER_PRESENT)
/***************************************************************************//**
 * @brief
 *  Common Low Energy Timer0 interrupt handler
 *
 * @details
 *  This function handles Timer0 counter overflow interrupt request
 *
 * @note
 *
 ******************************************************************************/
void LETIMER0_IRQHandler(void)
{
    if (LETIMER0->IF & LETIMER_IF_UF)
    {
        /* enter interrupt */
        rt_interrupt_enter();

        rt_tick_increase();

        /* leave interrupt */
        rt_interrupt_leave();

        /* invoke callback function */
/*      if (letimerCbTable[0].cbFunc != RT_NULL)
        {
            (letimerCbTable[0].cbFunc)(letimerCbTable[0].userPtr);
        }
*/
        /* clear interrupt */
        BITBAND_Peripheral(&(LETIMER0->IFC), _LETIMER_IF_UF_SHIFT, 0x1UL);
    }
}
#endif

/***************************************************************************//**
 * @brief
 *  Common RTC interrupt handler
 *
 * @details
 *  This function handles RTC counter overflow interrupt request
 *
 * @note
 *
 ******************************************************************************/
void RTC_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (RTC->IF & RTC_IF_OF)
    {
        /* invoke callback function */
        if (rtcCbTable[0].cbFunc != RT_NULL)
        {
            (rtcCbTable[0].cbFunc)(rtcCbTable[0].userPtr);
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common even number GPIO interrupt handler
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
    rt_uint16_t flag, n;
    rt_base_t level;

    /* Disable interrupt */
    level = rt_hw_interrupt_disable();
    /* Enter ISR */
    rt_interrupt_enter();

     /* invoke callback function */
    flag = (rt_uint16_t)(GPIO->IF & 0xFFFF);
    for ( n = 0; flag > 0; flag = flag >> 2, n = n + 2)
    {
        if ((flag & 0x0001) && (gpioCbTable[n].cbFunc != RT_NULL))
        {
            (gpioCbTable[n].cbFunc)(gpioCbTable[n].userPtr);
        }
    }

    /* clear interrupt */
    GPIO->IFC = 0x5555UL;

    /* Leave ISR */
    rt_interrupt_leave();
    /* Enable interrupt */
    rt_hw_interrupt_enable(level);
}

/***************************************************************************//**
 * @brief
 *  Common odd number GPIO interrupt handler
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
    rt_uint16_t flag, n;
    rt_base_t level;

    /* Disable interrupt */
    level = rt_hw_interrupt_disable();
    /* Enter ISR */
    rt_interrupt_enter();

     /* invoke callback function */
    flag = (rt_uint16_t)(GPIO->IF & 0xFFFF) >> 1;
    for ( n = 1; flag > 0; flag = flag >> 2, n = n + 2)
    {
        if ((flag & 0x0001) && (gpioCbTable[n].cbFunc != RT_NULL))
        {
            (gpioCbTable[n].cbFunc)(gpioCbTable[n].userPtr);
        }
    }

    /* clear interrupt */
    GPIO->IFC = 0xAAAAUL;

    /* Leave ISR */
    rt_interrupt_leave();
    /* Enable interrupt */
    rt_hw_interrupt_enable(level);
}

/***************************************************************************//**
 * @brief
 *  Common ACMP interrupt handler
 *
 * @details
 *  This function handles ACMP edge trigger interrupt request
 *
 * @note
 *
 ******************************************************************************/
void ACMP0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (ACMP0->IF & ACMP_IF_EDGE)
    {
        /* invoke callback function */
        if (acmpCbTable[0].cbFunc != RT_NULL)
        {
            (acmpCbTable[0].cbFunc)(acmpCbTable[0].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(ACMP0->IFC), _ACMP_IF_EDGE_SHIFT, 0x1UL);
    }

    if (ACMP1->IF & ACMP_IF_EDGE)
    {
        /* invoke callback function */
        if (acmpCbTable[1].cbFunc != RT_NULL)
        {
            (acmpCbTable[1].cbFunc)(acmpCbTable[1].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(ACMP1->IFC), _ACMP_IF_EDGE_SHIFT, 0x1UL);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined(USART_PRESENT)
/***************************************************************************//**
 * @brief
 *  Common USART0 TX interrupt handler
 *
 * @details
 *  This function handles USART0 TX complete interrupt request
 *
 * @note
 *
 ******************************************************************************/
void USART0_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (USART0->IF & USART_IF_TXC)
    {
        /* invoke callback function */
        if (usartCbTable[0].cbFunc != RT_NULL)
        {
            (usartCbTable[0].cbFunc)(usartCbTable[0].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(USART0->IFC), _USART_IF_TXC_SHIFT, 0x1UL);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common USART0 RX interrupt handler
 *
 * @details
 *  This function handles USART0 RX data valid interrupt request
 *
 * @note
 *
 ******************************************************************************/
void USART0_RX_IRQHandler(void)
{
    if (USART0->IF & USART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (usartCbTable[1].cbFunc != RT_NULL)
        {
            (usartCbTable[1].cbFunc)(usartCbTable[1].userPtr);
        }
    }
}
#endif

#if (defined(USART_PRESENT) && (USART_COUNT > 1))
/***************************************************************************//**
 * @brief
 *  Common USART1 TX interrupt handler
 *
 * @details
 *  This function handles USART1 TX complete interrupt request
 *
 * @note
 *
 ******************************************************************************/
void USART1_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (USART1->IF & USART_IF_TXC)
    {
        /* invoke callback function */
        if (usartCbTable[2].cbFunc != RT_NULL)
        {
            (usartCbTable[2].cbFunc)(usartCbTable[2].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(USART1->IFC), _USART_IF_TXC_SHIFT, 0x1UL);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common USART1 RX interrupt handler
 *
 * @details
 *  This function handles USART1 RX data valid interrupt request
 *
 * @note
 *
 ******************************************************************************/
void USART1_RX_IRQHandler(void)
{
    if (USART1->IF & USART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (usartCbTable[3].cbFunc != RT_NULL)
        {
            (usartCbTable[3].cbFunc)(usartCbTable[3].userPtr);
        }
    }
}
#endif

#if (defined(USART_PRESENT) && (USART_COUNT > 2))
/***************************************************************************//**
 * @brief
 *  Common USART2 TX interrupt handler
 *
 * @details
 *  This function handles USART2 TX complete interrupt request
 *
 * @note
 *
 ******************************************************************************/
void USART2_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (USART2->IF & USART_IF_TXC)
    {
        /* invoke callback function */
        if (usartCbTable[4].cbFunc != RT_NULL)
        {
            (usartCbTable[4].cbFunc)(usartCbTable[4].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(USART2->IFC), _USART_IF_TXC_SHIFT, 0x1UL);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common USART2 RX interrupt handler
 *
 * @details
 *  This function handles USART2 RX data valid interrupt request
 *
 * @note
 *
 ******************************************************************************/
void USART2_RX_IRQHandler(void)
{
    if (USART2->IF & USART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (usartCbTable[5].cbFunc != RT_NULL)
        {
            (usartCbTable[5].cbFunc)(usartCbTable[5].userPtr);
        }
    }
}
#endif

#if defined(UART_PRESENT)
/***************************************************************************//**
 * @brief
 *  Common UART0 TX interrupt handler
 *
 * @details
 *  This function handles UART0 TX complete interrupt request
 *
 * @note
 *
 ******************************************************************************/
void UART0_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART0->IF & UART_IF_TXC)
    {
        /* invoke callback function */
        if (usartCbTable[USART_COUNT * 2].cbFunc != RT_NULL)
        {
            (usartCbTable[USART_COUNT * 2].cbFunc)(usartCbTable[USART_COUNT * 2].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(UART0->IFC), _UART_IF_TXC_SHIFT, 0x1UL);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common UART0 RX interrupt handler
 *
 * @details
 *  This function handles UART0 RX data valid interrupt request
 *
 * @note
 *
 ******************************************************************************/
void UART0_RX_IRQHandler(void)
{
    if (UART0->IF & UART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (usartCbTable[USART_COUNT * 2 + 1].cbFunc != RT_NULL)
        {
            (usartCbTable[USART_COUNT * 2 + 1].cbFunc)(usartCbTable[USART_COUNT * 2 + 1].userPtr);
        }
    }
}
#endif

#if (defined(UART_PRESENT) && (UART_COUNT > 1))
/***************************************************************************//**
 * @brief
 *  Common UART1 TX interrupt handler
 *
 * @details
 *  This function handles UART1 TX complete interrupt request
 *
 * @note
 *
 ******************************************************************************/
void UART1_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART1->IF & UART_IF_TXC)
    {
        /* invoke callback function */
        if (usartCbTable[USART_COUNT * 2 + 2].cbFunc != RT_NULL)
        {
            (usartCbTable[USART_COUNT * 2 + 2].cbFunc)(usartCbTable[USART_COUNT * 2 + 2].userPtr);
        }

        /* clear interrupt */
        BITBAND_Peripheral(&(UART1->IFC), _UART_IF_TXC_SHIFT, 0x1UL);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************************************************************//**
 * @brief
 *  Common UART1 RX interrupt handler
 *
 * @details
 *  This function handles UART1 RX data valid interrupt request
 *
 * @note
 *
 ******************************************************************************/
void UART1_RX_IRQHandler(void)
{
    if (UART1->IF & UART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (usartCbTable[USART_COUNT * 2 + 3].cbFunc != RT_NULL)
        {
            (usartCbTable[USART_COUNT * 2 + 3].cbFunc)(usartCbTable[USART_COUNT * 2 + 3].userPtr);
        }
    }
}
#endif

#if defined(LEUART_PRESENT)
/***************************************************************************//**
 * @brief
 *  Common LEUART0 interrupt handler
 *
 * @details
 *  This function handles LEUART0 interrupt request
 *
 * @note
 *
 ******************************************************************************/
void LEUART0_IRQHandler(void)
{
    if (LEUART0->IF & LEUART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (leuartCbTable[0].cbFunc != RT_NULL)
        {
            (leuartCbTable[0].cbFunc)(leuartCbTable[0].userPtr);
        }
    }
}
#endif

#if (defined(LEUART_PRESENT) && (LEUART_COUNT > 1))
/***************************************************************************//**
 * @brief
 *  Common LEUART1 interrupt handler
 *
 * @details
 *  This function handles LEUART1 interrupt request
 *
 * @note
 *
 ******************************************************************************/
void LEUART1_IRQHandler(void)
{
    if (LEUART1->IF & LEUART_IF_RXDATAV)
    {
        /* invoke callback function */
        if (leuartCbTable[1].cbFunc != RT_NULL)
        {
            (leuartCbTable[1].cbFunc)(leuartCbTable[1].userPtr);
        }
    }
}
#endif

#if defined(I2C_PRESENT)
/***************************************************************************//**
 * @brief
 *  Common IIC0 interrupt handler
 *
 * @details
 *  This function handles IIC0 slave mode interrupt requests
 *
 * @note
 *
 ******************************************************************************/
void I2C0_IRQHandler(void)
{
    if ((I2C0->IF & I2C_IF_ADDR) || \
        (I2C0->IF & I2C_IF_RXDATAV) || \
        (I2C0->IF & I2C_IF_SSTOP))
    {
        /* invoke callback function */
        if (iicCbTable[0].cbFunc != RT_NULL)
        {
            (iicCbTable[0].cbFunc)(iicCbTable[0].userPtr);
        }
    }

    I2C_IntClear(I2C0, I2C_IFC_ADDR | I2C_IFC_SSTOP);
}
#endif

/***************************************************************************//**
 * @brief
 *  EFM32 common interrupt handlers register function
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void efm32_irq_hook_register(efm32_irq_hook_init_t *hook)
{
    switch (hook->type)
    {
    case efm32_irq_type_dma:
        dmaCbTable[hook->unit].cbFunc = hook->cbFunc;
        dmaCbTable[hook->unit].userPtr = hook->userPtr;
        break;

    case efm32_irq_type_rtc:
        rtcCbTable[hook->unit].cbFunc = hook->cbFunc;
        rtcCbTable[hook->unit].userPtr = hook->userPtr;
        break;

    case efm32_irq_type_timer:
        timerCbTable[hook->unit].cbFunc = hook->cbFunc;
        timerCbTable[hook->unit].userPtr = hook->userPtr;
        break;

    case efm32_irq_type_letimer:
        letimerCbTable[hook->unit].cbFunc = hook->cbFunc;
        letimerCbTable[hook->unit].userPtr = hook->userPtr;
        break;

    case efm32_irq_type_gpio:
        gpioCbTable[hook->unit].cbFunc = hook->cbFunc;
        gpioCbTable[hook->unit].userPtr = hook->userPtr;
        break;

    case efm32_irq_type_acmp:
        acmpCbTable[hook->unit].cbFunc = hook->cbFunc;
        acmpCbTable[hook->unit].userPtr = hook->userPtr;
        break;
#if defined(USART_PRESENT)
    case efm32_irq_type_usart:
        usartCbTable[hook->unit].cbFunc = hook->cbFunc;
        usartCbTable[hook->unit].userPtr = hook->userPtr;
        break;
#endif
#if defined(LEUART_PRESENT)
    case efm32_irq_type_leuart:
        leuartCbTable[hook->unit].cbFunc = hook->cbFunc;
        leuartCbTable[hook->unit].userPtr = hook->userPtr;
        break;
#endif
#if defined(I2C_PRESENT)
    case efm32_irq_type_iic:
        iicCbTable[hook->unit].cbFunc = hook->cbFunc;
        iicCbTable[hook->unit].userPtr = hook->userPtr;
        break;
#endif
    default:
        break;
    }

    hdl_debug("Hook Registered: type: %s, unit: %x, cbFunc: %x, userPtr: %x\n", \
        hook->type, hook->unit, hook->cbFunc, hook->userPtr);
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
