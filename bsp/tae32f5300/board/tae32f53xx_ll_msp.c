/**
  ******************************************************************************
  * @file    tae32f53xx_ll_msp.c
  * @author  MCD Application Team
  * @brief   LL MSP module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define DBG_TAG             "MSP LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_Examples
  * @{
  */

/** @addtogroup TAE32F53xx_UART_TxPolling_RxIT_Example
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup UART_TxPolling_RxIT_MSP_LL_Private_Functions UART_TxPolling_RxIT MSP LL Private Functions
  * @brief    UART_TxPolling_RxIT MSP LL Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void LL_MspInit(void)
{
    //SYSCTRL PMU Config
    LL_SYSCTRL_PMUCfg();

#ifdef LL_GPIO_MODULE_ENABLED
    //GPIO Msp Init
    LL_SYSCTRL_GPIOA_ClkEnRstRelease();
    LL_SYSCTRL_GPIOB_ClkEnRstRelease();
    LL_SYSCTRL_GPIOC_ClkEnRstRelease();
    LL_SYSCTRL_GPIOD_ClkEnRstRelease();
#endif

#ifdef LL_DMA_MODULE_ENABLED
    //DMA Msp Init
    LL_SYSCTRL_DMA_ClkEnRstRelease();

    //NVIC DMA Interrupt Enable
    LL_NVIC_EnableIRQ(DMA_IRQn);
#endif
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None
  * @retval None
  */
void LL_MspDeInit(void)
{
#ifdef LL_GPIO_MODULE_ENABLED
    //GPIO Msp DeInit
    LL_SYSCTRL_GPIOA_ClkDisRstAssert();
    LL_SYSCTRL_GPIOB_ClkDisRstAssert();
    LL_SYSCTRL_GPIOC_ClkDisRstAssert();
    LL_SYSCTRL_GPIOD_ClkDisRstAssert();
#endif

#ifdef LL_DMA_MODULE_ENABLED
    //DMA Msp DeInit
    LL_SYSCTRL_DMA_ClkDisRstAssert();

    //NVIC DMA Interrupt Disable
    LL_NVIC_DisableIRQ(DMA_IRQn);
#endif
}

/**
  * @brief  Initializes the FPLL MSP.
  * @param  Instance Specifies FPLL peripheral
  * @retval None
  */
void LL_FPLL_MspInit(FPLL_TypeDef *Instance)
{
    //Check FPLL Instance to be Valid
    if (!IS_FPLL_ALL_INSTANCE(Instance))
    {
        return;
    }

    //FPLL Soft Reset Release
    if (Instance == FPLL0)
    {
        LL_SYSCTRL_FPLL0_RstRelease();
    }
    else if (Instance == FPLL1)
    {
        LL_SYSCTRL_FPLL1_RstRelease();
    }
    else if (Instance == FPLL2)
    {
        LL_SYSCTRL_FPLL2_RstRelease();
    }
}

/**
  * @brief  DeInitializes the FPLL MSP.
  * @param  Instance Specifies FPLL peripheral
  * @retval None
  */
void LL_FPLL_MspDeInit(FPLL_TypeDef *Instance)
{
    //Check FPLL Instance to be Valid
    if (!IS_FPLL_ALL_INSTANCE(Instance))
    {
        return;
    }

    //FPLL Soft Reset Assert
    if (Instance == FPLL0)
    {
        LL_SYSCTRL_FPLL0_RstAssert();
    }
    else if (Instance == FPLL1)
    {
        LL_SYSCTRL_FPLL1_RstAssert();
    }
    else if (Instance == FPLL2)
    {
        LL_SYSCTRL_FPLL2_RstAssert();
    }
}

/**
  * @brief  Initializes the UART MSP.
  * @param  Instance Specifies UART peripheral
  * @retval None
  */
void LL_UART_MspInit(UART_TypeDef *Instance)
{
    GPIO_InitTypeDef UART_GPIO_Init;

    //Check UART Instance to be Valid
    if (!IS_UART_ALL_INSTANCE(Instance))
    {
        return;
    }

    if (Instance == UART0)
    {
        //UART0 Pinmux Config: PA10 & PA11
        UART_GPIO_Init.Pin = GPIO_PIN_7;
        UART_GPIO_Init.Mode = GPIO_MODE_AF;
        UART_GPIO_Init.Alternate = GPIO_AF10_UART0;
        LL_GPIO_Init(GPIOC, &UART_GPIO_Init);

        UART_GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11;
        UART_GPIO_Init.Mode = GPIO_MODE_AF;
        UART_GPIO_Init.OType = GPIO_OTYPE_PP;
        UART_GPIO_Init.Pull = GPIO_NOPULL;
        UART_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
        UART_GPIO_Init.Alternate = GPIO_AF10_UART0;
        LL_GPIO_Init(GPIOA, &UART_GPIO_Init);

        //UART0 Bus Clock Enable and Soft Reset Release
        LL_SYSCTRL_UART0_ClkEnRstRelease();

        //NVIC UART0 Interrupt Enable
        LL_NVIC_EnableIRQ(UART0_IRQn);
    }
    else if (Instance == UART1)
    {
        //UART1 Pinmux Config: PB8 & PB9
        UART_GPIO_Init.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        UART_GPIO_Init.Mode = GPIO_MODE_AF;
        UART_GPIO_Init.OType = GPIO_OTYPE_PP;
        UART_GPIO_Init.Pull = GPIO_NOPULL;
        UART_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
        UART_GPIO_Init.Alternate = GPIO_AF10_UART1;
        LL_GPIO_Init(GPIOB, &UART_GPIO_Init);

        //UART1 Bus Clock Enable and Soft Reset Release
        LL_SYSCTRL_UART1_ClkEnRstRelease();

        //NVIC UART1 Interrupt Enable
        LL_NVIC_EnableIRQ(UART1_IRQn);
    }
}

/**
  * @brief  DeInitializes the UART MSP.
  * @param  Instance Specifies UART peripheral
  * @retval None
  */
void LL_UART_MspDeInit(UART_TypeDef *Instance)
{
    //Check UART Instance to be Valid
    if (!IS_UART_ALL_INSTANCE(Instance))
    {
        return;
    }

    if (Instance == UART0)
    {
        //NVIC UART0 Interrupt Disable
        LL_NVIC_DisableIRQ(UART0_IRQn);

        //UART0 Bus Clock Disable and Soft Reset Assert
        LL_SYSCTRL_UART0_ClkDisRstAssert();

        //UART0 Pinmux DeInit
        LL_GPIO_DeInit(GPIOA, GPIO_PIN_10 | GPIO_PIN_11);
    }
    else if (Instance == UART1)
    {
        //NVIC UART1 Interrupt Disable
        LL_NVIC_DisableIRQ(UART1_IRQn);

        //UART1 Bus Clock Disable and Soft Reset Assert
        LL_SYSCTRL_UART1_ClkDisRstAssert();

        //UART1 Pinmux DeInit
        LL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
    }
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

