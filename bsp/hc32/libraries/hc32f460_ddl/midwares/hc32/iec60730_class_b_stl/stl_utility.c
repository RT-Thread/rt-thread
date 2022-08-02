/**
 *******************************************************************************
 * @file  stl_utility.c
 * @brief This file provides utility functions for STL.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "stl_utility.h"
#include "hc32_ll_fcg.h"
#include "hc32_ll_gpio.h"
#include "hc32_ll_usart.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup IEC60730_STL
 * @{
 */

/**
 * @defgroup IEC60730_STL_Utility IEC60730 STL Utility
 * @{
 */

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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_Utility_Global_Functions STL IEC60730 Utility Global Functions
 * @{
 */

/**
 * @brief Delay function, delay us approximately
 * @param [in] u32Count                 us
 * @retval None
 */
void STL_DelayUS(uint32_t u32Count)
{
    DDL_DelayUS(u32Count);
}

/**
 * @brief Delay function, delay ms approximately
 * @param [in] u32Count                 ms
 * @retval None
 */
void STL_DelayMS(uint32_t u32Count)
{
    DDL_DelayMS(u32Count);
}

/**
 * @brief STL test safety failure handle
 * @param None
 * @retval None
 */
void STL_SafetyFailure(void)
{
#if (STL_RESET_AT_FAILURE == STL_ON)
    NVIC_SystemReset(); /* Generate system reset */
#endif
}

#if (STL_PRINT_ENABLE == STL_ON)

/**
 * @brief  Transmit character.
 * @param  [in] cData                   The character for transmitting
 * @retval uint32_t:
 *           - STL_OK:                  Transmit successfully.
 *           - STL_ERR:                 Transmit timeout.
 */
__WEAKDEF uint32_t STL_ConsoleOutputChar(char cData)
{
    uint32_t u32Ret = STL_ERR;
    uint32_t u32TxEmpty = 0UL;
    __IO uint32_t u32TmpCount = 0UL;
    uint32_t u32Timeout = 10000UL;

    /* Wait TX data register empty */
    while ((u32TmpCount <= u32Timeout) && (0UL == u32TxEmpty)) {
        u32TxEmpty = READ_REG32_BIT(STL_PRINTF_DEVICE->SR, USART_SR_TXE);
        u32TmpCount++;
    }

    if (0UL != u32TxEmpty) {
        WRITE_REG32(STL_PRINTF_DEVICE->DR, (uint32_t)cData);
        u32Ret = STL_OK;
    }

    return u32Ret;
}

#if (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || \
    (defined (__ICCARM__)) || (defined (__CC_ARM))
/**
 * @brief  Re-target fputc function.
 * @param  [in] ch
 * @param  [in] f
 * @retval int32_t
 */
int32_t fputc(int32_t ch, FILE *f)
{
    (void)f;  /* Prevent unused argument compilation warning */

    return (STL_OK == STL_ConsoleOutputChar((char)ch)) ? ch : -1;
}

#elif defined (__GNUC__) && !defined (__CC_ARM)
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
            if (STL_OK != STL_ConsoleOutputChar(data[i])) {
                break;
            }
        }
    }

    return i ? i : -1;
}
#endif

/**
 * @brief  Initialize printf function
 * @param  None
 * @retval None
 */
uint32_t STL_PrintfInit(void)
{
    uint32_t u32Div;
    float32_t f32Error;
    uint32_t u32Ret = STL_ERR;
    stc_usart_uart_init_t stcUartInit;

    /* Set TX port function */
    GPIO_SetFunc(STL_PRINTF_PORT, STL_PRINTF_PIN, STL_PRINTF_PORT_FUNC);

    /* Enable clock  */
    STL_PRINTF_DEVICE_FCG_ENALBE();

    /***************************************************************************
     * Configure UART
     ***************************************************************************
     * Baud rate: STL_PRINTF_BAUDRATE
     * Bit direction: LSB
     * Data bits: 8
     * Stop bits: 1
     * Parity: None
     * Sampling bits: 8
     **************************************************************************/
    /* Configure UART */
    (void)USART_UART_StructInit(&stcUartInit);
    stcUartInit.u32OverSampleBit = USART_OVER_SAMPLE_8BIT;
    (void)USART_UART_Init(STL_PRINTF_DEVICE, &stcUartInit, NULL);

    for (u32Div = 0UL; u32Div <= USART_CLK_DIV64; u32Div++) {
        USART_SetClockDiv(STL_PRINTF_DEVICE, u32Div);
        if ((LL_OK == USART_SetBaudrate(STL_PRINTF_DEVICE, STL_PRINTF_BAUDRATE, &f32Error)) && \
                ((-STL_PRINTF_BAUDRATE_ERR_MAX <= f32Error) && (f32Error <= STL_PRINTF_BAUDRATE_ERR_MAX))) {
            USART_FuncCmd(STL_PRINTF_DEVICE, USART_TX, ENABLE);
            u32Ret = STL_OK;
            break;
        }
    }

    return u32Ret;
}

#endif /* STL_PRINT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
