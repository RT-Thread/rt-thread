/**
  ******************************************************************************
  * @file    tae32g58xx_ll_msp.c
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
#include "string.h"


#define DBG_TAG             "MSP LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_Examples
  * @{
  */

/** @addtogroup TAE32G58xx_GPIO_Flow_LED_Example
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @defgroup GPIO_Flow_LED_MSP_LL_Private_Functions GPIO_Flow_LED MSP LL Private Functions
  * @brief    GPIO_Flow_LED MSP LL Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP
  * @param  None
  * @retval None
  */
void LL_MspInit(void)
{
#ifdef LL_GPIO_MODULE_ENABLED
    //GPIO Msp Init
    LL_RCU_GPIOA_ClkEnRstRelease();
    LL_RCU_GPIOB_ClkEnRstRelease();
    LL_RCU_GPIOC_ClkEnRstRelease();
    LL_RCU_GPIOD_ClkEnRstRelease();
    LL_RCU_GPIOE_ClkEnRstRelease();
    LL_RCU_GPIOF_ClkEnRstRelease();
#endif

#ifdef LL_DMA_MODULE_ENABLED
    //DMA Msp Init
    LL_RCU_DMA_ClkEnRstRelease();

    //DMA Channel Interrupt Enable
    LL_NVIC_EnableIRQ(DMA_CH0_IRQn);
    LL_NVIC_EnableIRQ(DMA_CH1_IRQn);
    LL_NVIC_EnableIRQ(DMA_CH2_IRQn);
    LL_NVIC_EnableIRQ(DMA_CH3_IRQn);
    LL_NVIC_EnableIRQ(DMA_CH4_IRQn);
    LL_NVIC_EnableIRQ(DMA_CH5_IRQn);
#endif

#ifdef LL_EFLASH_MODULE_ENABLED
    //EFLASH Msp Init
    LL_RCU_EFLASH_ClkEnRstRelease();
#endif
}

/**
  * @brief  DeInitializes the Global MSP
  * @param  None
  * @retval None
  */
void LL_MspDeInit(void)
{
#ifdef LL_GPIO_MODULE_ENABLED
    //GPIO Msp DeInit
    LL_RCU_GPIOA_ClkDisRstAssert();
    LL_RCU_GPIOB_ClkDisRstAssert();
    LL_RCU_GPIOC_ClkDisRstAssert();
    LL_RCU_GPIOD_ClkDisRstAssert();
    LL_RCU_GPIOE_ClkDisRstAssert();
    LL_RCU_GPIOF_ClkDisRstAssert();
#endif

#ifdef LL_DMA_MODULE_ENABLED
    //DMA Msp DeInit
    LL_RCU_DMA_ClkDisRstAssert();

    //DMA Channel Interrupt Disable
    LL_NVIC_DisableIRQ(DMA_CH0_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH1_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH2_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH3_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH4_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH5_IRQn);
#endif

#ifdef LL_EFLASH_MODULE_ENABLED
    //EFLASH Msp DeInit
    LL_RCU_EFLASH_ClkDisRstAssert();
#endif
}

/**
  * @brief  Initializes the UART MSP
  * @param  Instance Specifies UART peripheral
  * @retval None
  */
void LL_UART_MspInit(UART_TypeDef *Instance)
{
    GPIO_InitTypeDef UART_GPIO_Init;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    //UART GPIO Common Config
    UART_GPIO_Init.IntMode = GPIO_INT_MODE_CLOSE;
    UART_GPIO_Init.OType   = GPIO_OTYPE_PP;
    UART_GPIO_Init.Pull    = GPIO_NOPULL;
    UART_GPIO_Init.Speed   = GPIO_SPEED_FREQ_LOW;

    if (Instance == UART0) {
        //UART0 Pinmux Config: PC4 & PC5
        UART_GPIO_Init.Pin = GPIO_PIN_4 | GPIO_PIN_5;
        UART_GPIO_Init.Alternate = GPIO_AF8_UART0;
        LL_GPIO_Init(GPIOC, &UART_GPIO_Init);

        //UART0 Bus Clock Enable and Soft Reset Release
        LL_RCU_UART0_ClkEnRstRelease();

        //NVIC UART0 Interrupt Enable
        LL_NVIC_EnableIRQ(UART0_IRQn);

    } else if (Instance == UART1) {

        //UART1 Pinmux Config: PA2 & PA3
        UART_GPIO_Init.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        UART_GPIO_Init.Alternate = GPIO_AF8_UART1;
        LL_GPIO_Init(GPIOA, &UART_GPIO_Init);

        //UART1 Bus Clock Enable and Soft Reset Release
        LL_RCU_UART1_ClkEnRstRelease();

        //NVIC UART1 Interrupt Enable
        LL_NVIC_EnableIRQ(UART1_IRQn);

    } else if (Instance == UART2) {

        //UART2 Pinmux Config: PC10 & PC11
        UART_GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11;
        UART_GPIO_Init.Alternate = GPIO_AF6_UART2;
        LL_GPIO_Init(GPIOC, &UART_GPIO_Init);

        //UART2 Bus Clock Enable and Soft Reset Release
        LL_RCU_UART2_ClkEnRstRelease();

        //NVIC UART2 Interrupt Enable
        LL_NVIC_EnableIRQ(UART2_IRQn);

    } else if (Instance == UART3) {

        //UART3 Pinmux Config: PC10 & PC11
        UART_GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11;
        UART_GPIO_Init.Alternate = GPIO_AF8_UART3;
        LL_GPIO_Init(GPIOC, &UART_GPIO_Init);

        //UART3 Bus Clock Enable and Soft Reset Release
        LL_RCU_UART3_ClkEnRstRelease();

        //NVIC UART3 Interrupt Enable
        LL_NVIC_EnableIRQ(UART3_IRQn);

    } else if (Instance == UART4) {

        //UART4 Pinmux Config: PC12
        UART_GPIO_Init.Pin = GPIO_PIN_12;
        UART_GPIO_Init.Alternate = GPIO_AF6_UART4;
        LL_GPIO_Init(GPIOC, &UART_GPIO_Init);

        //UART4 Pinmux Config: PD2
        UART_GPIO_Init.Pin = GPIO_PIN_2;
        UART_GPIO_Init.Alternate = GPIO_AF6_UART4;
        LL_GPIO_Init(GPIOD, &UART_GPIO_Init);

        //UART4 Bus Clock Enable and Soft Reset Release
        LL_RCU_UART4_ClkEnRstRelease();

        //NVIC UART4 Interrupt Enable
        LL_NVIC_EnableIRQ(UART4_IRQn);
    }
}

/**
  * @brief  DeInitializes the UART MSP
  * @param  Instance Specifies UART peripheral
  * @retval None
  */
void LL_UART_MspDeInit(UART_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (Instance == UART0) {
        //NVIC UART0 Interrupt Disable
        LL_NVIC_DisableIRQ(UART0_IRQn);

        //UART0 Bus Clock Disable and Soft Reset Assert
        LL_RCU_UART0_ClkDisRstAssert();

        //UART0 Pinmux DeInit
        LL_GPIO_DeInit(GPIOC, GPIO_PIN_4 | GPIO_PIN_5);

    } else if (Instance == UART1) {

        //NVIC UART1 Interrupt Disable
        LL_NVIC_DisableIRQ(UART1_IRQn);

        //UART1 Bus Clock Disable and Soft Reset Assert
        LL_RCU_UART1_ClkDisRstAssert();

        //UART1 Pinmux DeInit
        LL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

    } else if (Instance == UART2) {

        //NVIC UART2 Interrupt Disable
        LL_NVIC_DisableIRQ(UART2_IRQn);

        //UART2 Bus Clock Disable and Soft Reset Assert
        LL_RCU_UART2_ClkDisRstAssert();

        //UART2 Pinmux DeInit
        LL_GPIO_DeInit(GPIOC, GPIO_PIN_10 | GPIO_PIN_11);

    } else if (Instance == UART3) {

        //NVIC UART3 Interrupt Disable
        LL_NVIC_DisableIRQ(UART3_IRQn);

        //UART3 Bus Clock Disable and Soft Reset Assert
        LL_RCU_UART3_ClkDisRstAssert();

        //UART3 Pinmux DeInit
        LL_GPIO_DeInit(GPIOC, GPIO_PIN_10 | GPIO_PIN_11);

    } else if (Instance == UART4) {

        //NVIC UART4 Interrupt Disable
        LL_NVIC_DisableIRQ(UART4_IRQn);

        //UART4 Bus Clock Disable and Soft Reset Assert
        LL_RCU_UART4_ClkDisRstAssert();

        //UART4 Pinmux DeInit
        LL_GPIO_DeInit(GPIOC, GPIO_PIN_12);
        LL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
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

