/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_utility.c
 **
 ** A detailed description is available at
 ** @link DdlUtilityGroup Ddl Utility description @endlink
 **
 **   - 2018-11-02 CDT First version for Device Driver Library Utility.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_utility.h"

#if (DDL_UTILITY_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup DdlUtilityGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#if (DDL_PRINT_ENABLE == DDL_ON)
/*!< Parameter valid check for USART Instances. */
#define IS_VALID_UART(x)                                                       \
(   (M4_USART1 == (x))                      ||                                 \
    (M4_USART2 == (x))                      ||                                 \
    (M4_USART3 == (x))                      ||                                 \
    (M4_USART4 == (x)))

#define UART_EnableClk(x)                                                      \
do {                                                                           \
    if (M4_USART1 == (x))                                                      \
    {                                                                          \
        M4_MSTP->FCG1_f.USART1 = 0ul;                                          \
    }                                                                          \
    else if (M4_USART2 == (x))                                                 \
    {                                                                          \
        M4_MSTP->FCG1_f.USART2 = 0ul;                                          \
    }                                                                          \
    else if (M4_USART3 == (x))                                                 \
    {                                                                          \
        M4_MSTP->FCG1_f.USART3 = 0ul;                                          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        M4_MSTP->FCG1_f.USART4 = 0ul;                                          \
    }                                                                          \
} while (0)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint32_t m_u32TickStep = 0UL;
static __IO uint32_t m_u32TickCount = 0UL;

#if (DDL_PRINT_ENABLE == DDL_ON)
static M4_USART_TypeDef *m_PrintfDevice;
static uint32_t m_u32PrintfTimeout;
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
#if (DDL_PRINT_ENABLE == DDL_ON)
/**
 *******************************************************************************
 ** \brief  UART transmit.
 **
 ** \param  [in] USARTx                  Pointer to USART instance register base
 **         This parameter can be one of the following values:
 **           @arg M4_USART1:            USART unit 1 instance register base
 **           @arg M4_USART2:            USART unit 2 instance register base
 **           @arg M4_USART3:            USART unit 3 instance register base
 **           @arg M4_USART4:            USART unit 4 instance register base
 ** \param  [in] cData                   The data for transmitting
 **
 ** \retval An en_result_t enumeration value:
 **           - Ok: Send successfully
 **           - ErrorTimeout: Send timeout
 **           - ErrorInvalidParameter: The parameter USARTx is invalid
 **
 ******************************************************************************/
static en_result_t UartPutChar(M4_USART_TypeDef *USARTx, char cData)
{
    uint32_t u32TxEmpty;
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint32_t u32Timeout = m_u32PrintfTimeout;

    if (NULL != USARTx)
    {
        /* Wait TX data register empty */
        do
        {
            u32Timeout--;
            u32TxEmpty = USARTx->SR_f.TXE;
        } while ((u32Timeout > 0ul) && (0ul == u32TxEmpty));

        if (u32TxEmpty > 0ul)
        {
            USARTx->DR = (uint32_t)cData;
            enRet = Ok;
        }
        else
        {
            enRet = ErrorTimeout;
        }
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief Set synchronous clock mode baudrate
 **
 ** \param  [in] USARTx                  Pointer to USART instance register base
 **         This parameter can be one of the following values:
 **           @arg M4_USART1:            USART unit 1 instance register base
 **           @arg M4_USART2:            USART unit 2 instance register base
 **           @arg M4_USART3:            USART unit 3 instance register base
 **           @arg M4_USART4:            USART unit 4 instance register base
 ** \param [in] u32Baudrate             Baudrate
 **
 ** \retval Ok                          Configure successfully.
 ** \retval ErrorInvalidParameter       USARTx is invalid
 **
 ******************************************************************************/
static en_result_t SetUartBaudrate(M4_USART_TypeDef *USARTx, uint32_t u32Baudrate)
{
    uint32_t B;
    uint32_t C;
    uint32_t OVER8;
    float32_t DIV;
    uint64_t u64Tmp;
    uint32_t DIV_Integer;
    uint32_t DIV_Fraction;
    uint32_t u32PClk1;
    uint32_t u32UartClk;
    en_result_t enRet = ErrorInvalidParameter;

    u32PClk1 = SystemCoreClock / (1ul << (M4_SYSREG->CMU_SCFGR_f.PCLK1S));
    u32UartClk = u32PClk1 / (1ul << (2ul * (USARTx->PR_f.PSC)));

    B = u32Baudrate;
    C = u32UartClk;
    DIV_Fraction = 0ul;

    if ((0ul != C) && (0ul != B))
    {
        OVER8 = USARTx->CR1_f.OVER8;

        /* FBME = 0 Calculation formula */
        /* B = C / (8 * (2 - OVER8) * (DIV_Integer + 1)) */
        /* DIV_Integer = (C / (B * 8 * (2 - OVER8))) - 1 */
        DIV = ((float)C / ((float)B * 8.0f * (2.0f - (float)OVER8))) - 1.0f;
        DIV_Integer = (uint32_t)(DIV);

        if ((DIV < 0.0f) || (DIV_Integer > 0xFFul))
        {
            enRet = ErrorInvalidParameter;
        }
        else
        {
            if ((DIV - (float32_t)DIV_Integer) > 0.00001f)
            {
                /* FBME = 1 Calculation formula */
                /* B = C * (128 + DIV_Fraction) / (8 * (2 - OVER8) * (DIV_Integer + 1) * 256) */
                /* DIV_Fraction = ((8 * (2 - OVER8) * (DIV_Integer + 1) * 256 * B) / C) - 128 */
                /* E = (C * (128 + DIV_Fraction) / (8 * (2 - OVER8) * (DIV_Integer + 1) * 256 * B)) - 1 */
                /* DIV_Fraction = (((2 - OVER8) * (DIV_Integer + 1) * 2048 * B) / C) - 128 */
                u64Tmp = (2u - (uint64_t)OVER8) * ((uint64_t)DIV_Integer + 1u) * (uint64_t)B;
                DIV_Fraction = (uint32_t)(2048ul * u64Tmp/C - 128ul);
            }

            USARTx->CR1_f.FBME = (DIV_Fraction > 0UL) ? 1ul : 0ul;
            USARTx->BRR_f.DIV_FRACTION = DIV_Fraction;
            USARTx->BRR_f.DIV_INTEGER = DIV_Integer;
            enRet = Ok;
        }
    }

    return enRet;
}

#if defined ( __GNUC__ ) && !defined (__CC_ARM)
/**
 *******************************************************************************
 ** \brief  Re-target _write function.
 **
 ** \param  [in] fd
 ** \param  [in] data
 ** \param  [in] size
 **
 ** \retval int32_t
 **
 ******************************************************************************/
int32_t _write(int fd, char data[], int32_t size)
{
    int32_t i = -1;

    if (NULL != data)
    {
        (void)fd;  /* Prevent unused argument compilation warning */

        for (i = 0; i < size; i++)
        {
            if (Ok != UartPutChar(m_PrintfDevice, data[i]))
            {
                break;
            }
        }
    }

    return i ? i : -1;
}

#else
/**
 *******************************************************************************
 ** \brief  Re-target fputc function.
 **
 ** \param  [in] ch
 ** \param  [in] f
 **
 ** \retval int32_t
 **
 ******************************************************************************/
int32_t fputc(int32_t ch, FILE *f)
{
    (void)f;  /* Prevent unused argument compilation warning */

    return (Ok == UartPutChar(m_PrintfDevice, (char)ch)) ? ch: -1;
}
#endif

/**
 *******************************************************************************
 ** \brief Debug printf initialization function
 **
 ** \param  [in] UARTx                  Pointer to USART instance register base
 **         This parameter can be one of the following values:
 **           @arg M4_USART1:           USART unit 1 instance register base
 **           @arg M4_USART2:           USART unit 2 instance register base
 **           @arg M4_USART3:           USART unit 3 instance register base
 **           @arg M4_USART4:           USART unit 4 instance register base
 ** \param [in] u32Baudrate             Baudrate
 ** \param [in] PortInit                The pointer of printf port initialization function
 **
 ** \retval Ok                          Process successfully done
 **
 ******************************************************************************/
en_result_t UART_PrintfInit(M4_USART_TypeDef *UARTx,
                            uint32_t u32Baudrate,
                            void (*PortInit)(void))
{
    en_result_t enRet = ErrorInvalidParameter;

    if (IS_VALID_UART(UARTx) && (0ul != u32Baudrate) && (NULL != PortInit))
    {
        /* Initialize port */
        PortInit();

        /* Enable clock */
        UART_EnableClk(UARTx);

        /* Initialize USART */
        UARTx->CR1_f.ML = 0ul;      /* LSB */
        UARTx->CR1_f.MS = 0ul;      /* UART mode */
        UARTx->CR1_f.OVER8 = 1ul;   /* 8bit sampling mode */
        UARTx->CR1_f.M = 0ul;       /* 8 bit data length */
        UARTx->CR1_f.PCE = 0ul;     /* no parity bit */

        /* Set baudrate */
        if(Ok != SetUartBaudrate(UARTx, u32Baudrate))
        {
            enRet = Error;
        }
        else
        {
            UARTx->CR2 = 0ul;       /* 1 stop bit, single uart mode */
            UARTx->CR3 = 0ul;       /* CTS disable, Smart Card mode disable */
            UARTx->CR1_f.TE = 1ul;  /* TX enable */

            m_PrintfDevice = UARTx;
            m_u32PrintfTimeout = (SystemCoreClock / u32Baudrate);
        }
    }

    return enRet;
}
#endif /* DDL_PRINT_ENABLE */

/**
 *******************************************************************************
 ** \brief Delay function, delay 1ms approximately
 **
 ** \param [in]  u32Cnt                 ms
 **
 ** \retval none
 **
 ******************************************************************************/
void Ddl_Delay1ms(uint32_t u32Cnt)
{
    volatile uint32_t i;
    uint32_t u32Cyc;

    u32Cyc = SystemCoreClock;
    u32Cyc = u32Cyc / 10000ul;
    while (u32Cnt-- > 0ul)
    {
        i = u32Cyc;
        while (i-- > 0ul)
        {
            ;
        }
    }
}

/**
 *******************************************************************************
 ** \brief Delay function, delay 1us approximately
 **
 ** \param [in]  u32Cnt                 us
 **
 ** \retval none
 **
 ******************************************************************************/
void Ddl_Delay1us(uint32_t u32Cnt)
{
    uint32_t u32Cyc;
    volatile uint32_t i;

    if(SystemCoreClock > 10000000ul)
    {
        u32Cyc = SystemCoreClock / 10000000ul;
        while(u32Cnt-- > 0ul)
        {
            i = u32Cyc;
            while (i-- > 0ul)
            {
                ;
            }
        }
    }
    else
    {
         while(u32Cnt-- > 0ul)
         {
            ;
         }
    }
}

/**
 *******************************************************************************
 ** \brief This function Initializes the interrupt frequency of the SysTick.
 **
 ** \param [in] u32Freq                 SysTick interrupt frequency (1 to 1000).
 **
 ** \retval Ok                          SysTick Initializes succeed
 ** \retval Error                       SysTick Initializes failed
 **
 ******************************************************************************/
__WEAKDEF en_result_t SysTick_Init(uint32_t u32Freq)
{
    en_result_t enRet = Error;

    if ((0UL != u32Freq) && (u32Freq <= 1000UL))
    {
        m_u32TickStep = 1000UL / u32Freq;
        /* Configure the SysTick interrupt */
        if (0UL == SysTick_Config(SystemCoreClock / u32Freq))
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief This function provides minimum delay (in milliseconds).
 **
 ** \param [in] u32Delay                Delay specifies the delay time.
 **
 ** \retval None
 **
 ******************************************************************************/
__WEAKDEF void SysTick_Delay(uint32_t u32Delay)
{
    const uint32_t tickStart = SysTick_GetTick();
    uint32_t tickEnd;
    uint32_t tickMax;

    if (m_u32TickStep != 0UL)
    {
        tickMax = 0xFFFFFFFFUL / m_u32TickStep * m_u32TickStep;
        /* Add a freq to guarantee minimum wait */
        if ((u32Delay >= tickMax) || ((tickMax - u32Delay) < m_u32TickStep))
        {
            tickEnd = tickMax;
        }
        else
        {
            tickEnd = u32Delay + m_u32TickStep;
        }

        while ((SysTick_GetTick() - tickStart) < tickEnd)
        {
        }
    }
}

/**
 *******************************************************************************
 ** \brief This function is called to increment a global variable "u32TickCount".
 ** \note  This variable is incremented in SysTick ISR.
 **
 ** \param None
 **
 ** \retval None
 **
 ******************************************************************************/
__WEAKDEF void SysTick_IncTick(void)
{
    m_u32TickCount += m_u32TickStep;
}

/**
 *******************************************************************************
 ** \brief Provides a tick value in millisecond.
 **
 ** \param None
 **
 ** \retval Tick value
 **
 ******************************************************************************/
__WEAKDEF uint32_t SysTick_GetTick(void)
{
    return m_u32TickCount;
}

/**
 *******************************************************************************
 ** \brief Suspend SysTick increment.
 **
 ** \param None
 **
 ** \retval None
 **
 ******************************************************************************/
__WEAKDEF void SysTick_Suspend(void)
{
    /* Disable SysTick Interrupt */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
 *******************************************************************************
 ** \brief Resume SysTick increment.
 **
 ** \param None
 **
 ** \retval None
 **
 ******************************************************************************/
__WEAKDEF void SysTick_Resume(void)
{
    /* Enable SysTick Interrupt */
    SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

/**
 *******************************************************************************
 ** \brief ddl assert error handle function
 **
 ** \param [in]  file                   Point to the current assert the wrong file
 ** \param [in]  line                   Point line assert the wrong file in the current
 **
 ******************************************************************************/
#ifdef __DEBUG
__WEAKDEF void Ddl_AssertHandler(uint8_t *file, int16_t line)
{
    /* Users can re-implement this function to print information */
#if (DDL_PRINT_ENABLE == DDL_ON)
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
#else
    (void)file;
    (void)line;
#endif
    for (;;)
    {
        ;
    }
}
#endif /* __DEBUG */

//@} // DdlUtilityGroup

#endif /* DDL_UTILITY_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
