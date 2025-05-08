/**
 *******************************************************************************
 * @file  hc32_ll_utility.c
 * @brief This file provides utility functions for DDL.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-06-30       CDT             Modify register USART DR to USART TDR
                                    Prohibit DDL_DelayMS and DDL_DelayUS functions from being optimized
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_UTILITY UTILITY
 * @brief DDL Utility Driver
 * @{
 */

#if (LL_UTILITY_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup UTILITY_Local_Variables UTILITY Local Variables
 * @{
 */

static uint32_t m_u32TickStep = 0UL;
static __IO uint32_t m_u32TickCount = 0UL;

#if (LL_PRINT_ENABLE == DDL_ON)
static void *m_pvPrintDevice = NULL;
static uint32_t m_u32PrintTimeout = 0UL;
#endif

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup UTILITY_Local_Functions UTILITY Local Functions
 * @{
 */
#if (LL_PRINT_ENABLE == DDL_ON)

/**
 * @brief  Set print device.
 * @param  [in] pvPrintDevice           Pointer to print device
 * @retval None
 */
__STATIC_INLINE void LL_SetPrintDevice(void *pvPrintDevice)
{
    m_pvPrintDevice = pvPrintDevice;
}

/**
 * @brief  Get print device.
 * @param  None
 * @retval Pointer to print device
 */
__STATIC_INLINE void *LL_GetPrintDevice(void)
{
    return m_pvPrintDevice;
}

/**
 * @brief  Set print timeout.
 * @param  [in] u32Timeout              Print timeout value
 * @retval None
 */
__STATIC_INLINE void LL_SetPrintTimeout(uint32_t u32Timeout)
{
    m_u32PrintTimeout = u32Timeout;
}

/**
 * @brief  Get print timeout.
 * @param  None
 * @retval Print timeout value
 */
__STATIC_INLINE uint32_t LL_GetPrintTimeout(void)
{
    return m_u32PrintTimeout;
}
#endif /* LL_PRINT_ENABLE */

/**
 * @}
 */

/**
 * @defgroup UTILITY_Global_Functions UTILITY Global Functions
 * @{
 */

/**
 * @brief Delay function, delay ms approximately
 * @param [in] u32Count                   ms
 * @retval None
 */
#if defined (__CC_ARM)  /*!< ARM Compiler */
#pragma push
#pragma O0
#endif
__NO_OPTIMIZE void DDL_DelayMS(uint32_t u32Count)
{
    __IO uint32_t i;
    const uint32_t u32Cyc = (HCLK_VALUE + 10000UL - 1UL) / 10000UL;

    while (u32Count-- > 0UL) {
        i = u32Cyc;
        while (i-- > 0UL) {
        }
    }
}

/**
 * @brief Delay function, delay us approximately
 * @param [in] u32Count                   us
 * @retval None
 */
__NO_OPTIMIZE void DDL_DelayUS(uint32_t u32Count)
{
    __IO uint32_t i;
    const uint32_t u32Cyc = (HCLK_VALUE + 10000000UL - 1UL) / 10000000UL;

    while (u32Count-- > 0UL) {
        i = u32Cyc;
        while (i-- > 0UL) {
        }
    }
}
#if defined (__CC_ARM)  /*!< ARM Compiler */
#pragma pop
#endif

/**
 * @brief This function Initializes the interrupt frequency of the SysTick.
 * @param [in] u32Freq                  SysTick interrupt frequency (1 to 1000).
 * @retval int32_t:
 *           - LL_OK: SysTick Initializes succeed
 *           - LL_ERR: SysTick Initializes failed
 */
__WEAKDEF int32_t SysTick_Init(uint32_t u32Freq)
{
    int32_t i32Ret = LL_ERR;

    if ((0UL != u32Freq) && (u32Freq <= 1000UL)) {
        m_u32TickStep = 1000UL / u32Freq;
        /* Configure the SysTick interrupt */
        if (0UL == SysTick_Config(HCLK_VALUE / u32Freq)) {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief This function provides minimum delay (in milliseconds).
 * @param [in] u32Delay                 Delay specifies the delay time.
 * @retval None
 */
__WEAKDEF void SysTick_Delay(uint32_t u32Delay)
{
    const uint32_t tickStart = SysTick_GetTick();
    uint32_t tickEnd = u32Delay;
    uint32_t tickMax;

    if (m_u32TickStep != 0UL) {
        tickMax = 0xFFFFFFFFUL / m_u32TickStep * m_u32TickStep;
        /* Add a freq to guarantee minimum wait */
        if ((u32Delay >= tickMax) || ((tickMax - u32Delay) < m_u32TickStep)) {
            tickEnd = tickMax;
        }
        while ((SysTick_GetTick() - tickStart) < tickEnd) {
        }
    }
}

/**
 * @brief This function is called to increment a global variable "u32TickCount".
 * @note  This variable is incremented in SysTick ISR.
 * @param None
 * @retval None
 */
__WEAKDEF void SysTick_IncTick(void)
{
    m_u32TickCount += m_u32TickStep;
}

/**
 * @brief Provides a tick value in millisecond.
 * @param None
 * @retval Tick value
 */
__WEAKDEF uint32_t SysTick_GetTick(void)
{
    return m_u32TickCount;
}

/**
 * @brief Suspend SysTick increment.
 * @param None
 * @retval None
 */
__WEAKDEF void SysTick_Suspend(void)
{
    /* Disable SysTick Interrupt */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
 * @brief Resume SysTick increment.
 * @param None
 * @retval None
 */
__WEAKDEF void SysTick_Resume(void)
{
    /* Enable SysTick Interrupt */
    SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

#ifdef __DEBUG
/**
 * @brief DDL assert error handle function
 * @param [in] file                     Point to the current assert the wrong file.
 * @param [in] line                     Point line assert the wrong file in the current.
 * @retval None
 */
__WEAKDEF void DDL_AssertHandler(const char *file, int line)
{
    /* Users can re-implement this function to print information */
    DDL_Printf("Wrong parameters value: file %s on line %d\r\n", file, line);

    for (;;) {
    }
}
#endif /* __DEBUG */

#if (LL_PRINT_ENABLE == DDL_ON)

#if (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || \
    (defined (__ICCARM__) && (__VER__ < 9000000)) || (defined (__CC_ARM))
/**
 * @brief  Re-target fputc function.
 * @param  [in] ch
 * @param  [in] f
 * @retval int32_t
 */
int32_t fputc(int32_t ch, FILE *f)
{
    (void)f;  /* Prevent unused argument compilation warning */

    return (LL_OK == DDL_ConsoleOutputChar((char)ch)) ? ch : -1;
}

#elif (defined (__ICCARM__) && (__VER__ >= 9000000))
#include <LowLevelIOInterface.h>
#pragma module_name = "?__write"
size_t __dwrite(int handle, const unsigned char *buffer, size_t size)
{
    size_t nChars = 0;
    size_t i;

    if (buffer == NULL) {
        /*
         * This means that we should flush internal buffers.  Since we
         * don't we just return.  (Remember, "handle" == -1 means that all
         * handles should be flushed.)
         */
        return 0;
    }

    /* This template only writes to "standard out" and "standard err",
     * for all other file handles it returns failure. */
    if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR) {
        return _LLIO_ERROR;
    }

    for (i = 0; i < size; i++) {
        if (DDL_ConsoleOutputChar((char)buffer[i]) < 0) {
            return _LLIO_ERROR;
        }

        ++nChars;
    }

    return nChars;
}

#elif defined ( __GNUC__ ) && !defined (__CC_ARM)
/**
 * @brief  Re-target _write function.
 * @param  [in] fd
 * @param  [in] data
 * @param  [in] size
 * @retval int32_t
 */
int32_t _write(int fd, char data[], int32_t size)
{
    int32_t i = -1;

    if (NULL != data) {
        (void)fd;  /* Prevent unused argument compilation warning */

        for (i = 0; i < size; i++) {
            if (LL_OK != DDL_ConsoleOutputChar(data[i])) {
                break;
            }
        }
    }

    return i ? i : -1;
}
#endif

/**
 * @brief  Initialize printf function
 * @param  [in] vpDevice                Pointer to print device
 * @param  [in] u32Param                Print device parameter
 * @param  [in] pfnPreinit              The function pointer for initializing clock, port, print device etc.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR:                  The callback function pfnPreinit occurs error.
 *           - LL_ERR_INVD_PARAM:       The pointer pfnPreinit is NULL.
 */
int32_t LL_PrintfInit(void *vpDevice, uint32_t u32Param, int32_t (*pfnPreinit)(void *vpDevice, uint32_t u32Param))
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pfnPreinit) {
        i32Ret = pfnPreinit(vpDevice, u32Param);   /* The callback function initialize clock, port, print device etc */
        if (LL_OK == i32Ret) {
            LL_SetPrintDevice(vpDevice);
            LL_SetPrintTimeout((u32Param == 0UL) ? 0UL : (HCLK_VALUE / u32Param));
        } else {
            i32Ret = LL_ERR;
            DDL_ASSERT(i32Ret == LL_OK);           /* Initialize unsuccessfully */
        }
    }

    return i32Ret;
}

/**
 * @brief  Transmit character.
 * @param  [in] cData                   The character for transmitting
 * @retval int32_t:
 *           - LL_OK:                   Transmit successfully.
 *           - LL_ERR_TIMEOUT:          Transmit timeout.
 *           - LL_ERR_INVD_PARAM:       The print device is invalid.
 */
__WEAKDEF int32_t DDL_ConsoleOutputChar(char cData)
{
    uint32_t u32TxEmpty = 0UL;
    __IO uint32_t u32TmpCount = 0UL;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint32_t u32Timeout = LL_GetPrintTimeout();
    CM_USART_TypeDef *USARTx = (CM_USART_TypeDef *)LL_GetPrintDevice();

    if (NULL != USARTx) {
        /* Wait TX data register empty */
        while ((u32TmpCount <= u32Timeout) && (0UL == u32TxEmpty)) {
            u32TxEmpty = READ_REG32_BIT(USARTx->SR, USART_SR_TXE);
            u32TmpCount++;
        }

        if (0UL != u32TxEmpty) {
            WRITE_REG16(USARTx->TDR, (uint16_t)cData);
            i32Ret = LL_OK;
        } else {
            i32Ret = LL_ERR_TIMEOUT;
        }
    }

    return i32Ret;
}

#endif /* LL_PRINT_ENABLE */

/**
 * @}
 */

#endif /* LL_UTILITY_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
