/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : stm32mp1xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
DMA_HandleTypeDef hdma_hash_in    = {0};
DMA_HandleTypeDef hdma_cryp_in    = {0};
DMA_HandleTypeDef hdma_cryp_out   = {0};
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */
 
/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
                        
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_HSEM_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */
    if (IS_ENGINEERING_BOOT_MODE()) 
    {
        __HAL_RCC_SYSRAM_CLK_ENABLE();
    }

    HAL_NVIC_SetPriority(RCC_WAKEUP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RCC_WAKEUP_IRQn);
    __HAL_RCC_ENABLE_IT(RCC_IT_WKUP);
  /* USER CODE END MspInit 1 */
}

/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspInit 0 */

  /* USER CODE END ADC2_MspInit 0 */
  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PER;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();
  
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**ADC2 GPIO Configuration    
    PF14     ------> ADC2_INP6 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC2_MspInit 1 */
  /* USER CODE END ADC2_MspInit 1 */
  }

}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();
  
    /**ADC2 GPIO Configuration    
    PF14     ------> ADC2_INP6 
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_14);

  /* USER CODE BEGIN ADC2_MspDeInit 1 */

  /* USER CODE END ADC2_MspDeInit 1 */
  }

}

/**
* @brief DAC MSP Initialization
* This function configures the hardware resources used in this example
* @param hdac: DAC handle pointer
* @retval None
*/
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hdac->Instance==DAC1)
  {
  /* USER CODE BEGIN DAC1_MspInit 0 */

  /* USER CODE END DAC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DAC12_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC1 GPIO Configuration    
    PA4     ------> DAC1_OUT1 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN DAC1_MspInit 1 */

  /* USER CODE END DAC1_MspInit 1 */
  }

}

/**
* @brief DAC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hdac: DAC handle pointer
* @retval None
*/
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
  if(hdac->Instance==DAC1)
  {
  /* USER CODE BEGIN DAC1_MspDeInit 0 */

  /* USER CODE END DAC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC12_CLK_DISABLE();
  
    /**DAC1 GPIO Configuration    
    PA4     ------> DAC1_OUT1 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

  /* USER CODE BEGIN DAC1_MspDeInit 1 */

  /* USER CODE END DAC1_MspDeInit 1 */
  }

}

/**
* @brief IPCC MSP Initialization
* This function configures the hardware resources used in this example
* @param hipcc: IPCC handle pointer
* @retval None
*/
void HAL_IPCC_MspInit(IPCC_HandleTypeDef* hipcc)
{
  if(hipcc->Instance==IPCC)
  {
  /* USER CODE BEGIN IPCC_MspInit 0 */

  /* USER CODE END IPCC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_IPCC_CLK_ENABLE();
    /* IPCC interrupt Init */
    HAL_NVIC_SetPriority(IPCC_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(IPCC_RX1_IRQn);
    HAL_NVIC_SetPriority(IPCC_TX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(IPCC_TX1_IRQn);
  /* USER CODE BEGIN IPCC_MspInit 1 */

  /* USER CODE END IPCC_MspInit 1 */
  }

}

/**
* @brief IPCC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hipcc: IPCC handle pointer
* @retval None
*/
void HAL_IPCC_MspDeInit(IPCC_HandleTypeDef* hipcc)
{
  if(hipcc->Instance==IPCC)
  {
  /* USER CODE BEGIN IPCC_MspDeInit 0 */

  /* USER CODE END IPCC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_IPCC_CLK_DISABLE();

    /* IPCC interrupt DeInit */
    HAL_NVIC_DisableIRQ(IPCC_RX1_IRQn);
    HAL_NVIC_DisableIRQ(IPCC_TX1_IRQn);
  /* USER CODE BEGIN IPCC_MspDeInit 1 */

  /* USER CODE END IPCC_MspDeInit 1 */
  }

}

/**
* @brief LPTIM MSP Initialization
* This function configures the hardware resources used in this example
* @param hlptim: LPTIM handle pointer
* @retval None
*/
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* hlptim)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hlptim->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspInit 0 */

  /* USER CODE END LPTIM1_MspInit 0 */
  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM1;
    PeriphClkInit.Lptim1ClockSelection = RCC_LPTIM1CLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_LPTIM1_CLK_ENABLE();
    /* LPTIM1 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspInit 1 */

  /* USER CODE END LPTIM1_MspInit 1 */
  }
  else if(hlptim->Instance==LPTIM2)
  {
  /* USER CODE BEGIN LPTIM2_MspInit 0 */

  /* USER CODE END LPTIM2_MspInit 0 */

  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM23;
    PeriphClkInit.Lptim23ClockSelection = RCC_LPTIM23CLKSOURCE_PCLK3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_LPTIM2_CLK_ENABLE();
    /* LPTIM2 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM2_IRQn);
  /* USER CODE BEGIN LPTIM2_MspInit 1 */

  /* USER CODE END LPTIM2_MspInit 1 */
  }
  else if(hlptim->Instance==LPTIM3)
  {
  /* USER CODE BEGIN LPTIM3_MspInit 0 */

  /* USER CODE END LPTIM3_MspInit 0 */

  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM23;
    PeriphClkInit.Lptim23ClockSelection = RCC_LPTIM23CLKSOURCE_PCLK3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_LPTIM3_CLK_ENABLE();
    /* LPTIM3 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM3_IRQn);
  /* USER CODE BEGIN LPTIM3_MspInit 1 */

  /* USER CODE END LPTIM3_MspInit 1 */
  }
  else if(hlptim->Instance==LPTIM4)
  {
  /* USER CODE BEGIN LPTIM4_MspInit 0 */

  /* USER CODE END LPTIM4_MspInit 0 */

  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM45;
    PeriphClkInit.Lptim45ClockSelection = RCC_LPTIM45CLKSOURCE_PCLK3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_LPTIM4_CLK_ENABLE();
    /* LPTIM4 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM4_IRQn);
  /* USER CODE BEGIN LPTIM4_MspInit 1 */

  /* USER CODE END LPTIM4_MspInit 1 */
  }
  else if(hlptim->Instance==LPTIM5)
  {
  /* USER CODE BEGIN LPTIM5_MspInit 0 */

  /* USER CODE END LPTIM5_MspInit 0 */

  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM45;
    PeriphClkInit.Lptim45ClockSelection = RCC_LPTIM45CLKSOURCE_PCLK3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_LPTIM5_CLK_ENABLE();
    /* LPTIM5 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM5_IRQn);
  /* USER CODE BEGIN LPTIM5_MspInit 1 */

  /* USER CODE END LPTIM5_MspInit 1 */
  }

}

/**
* @brief LPTIM MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hlptim: LPTIM handle pointer
* @retval None
*/
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* hlptim)
{
  if(hlptim->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspDeInit 0 */

  /* USER CODE END LPTIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM1_CLK_DISABLE();

    /* LPTIM1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspDeInit 1 */

  /* USER CODE END LPTIM1_MspDeInit 1 */
  }
  else if(hlptim->Instance==LPTIM2)
  {
  /* USER CODE BEGIN LPTIM2_MspDeInit 0 */

  /* USER CODE END LPTIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM2_CLK_DISABLE();

    /* LPTIM2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM2_IRQn);
  /* USER CODE BEGIN LPTIM2_MspDeInit 1 */

  /* USER CODE END LPTIM2_MspDeInit 1 */
  }
  else if(hlptim->Instance==LPTIM3)
  {
  /* USER CODE BEGIN LPTIM3_MspDeInit 0 */

  /* USER CODE END LPTIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM3_CLK_DISABLE();

    /* LPTIM3 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM3_IRQn);
  /* USER CODE BEGIN LPTIM3_MspDeInit 1 */

  /* USER CODE END LPTIM3_MspDeInit 1 */
  }
  else if(hlptim->Instance==LPTIM4)
  {
  /* USER CODE BEGIN LPTIM4_MspDeInit 0 */

  /* USER CODE END LPTIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM4_CLK_DISABLE();

    /* LPTIM4 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM4_IRQn);
  /* USER CODE BEGIN LPTIM4_MspDeInit 1 */

  /* USER CODE END LPTIM4_MspDeInit 1 */
  }
  else if(hlptim->Instance==LPTIM5)
  {
  /* USER CODE BEGIN LPTIM5_MspDeInit 0 */

  /* USER CODE END LPTIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM5_CLK_DISABLE();

    /* LPTIM5 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM5_IRQn);
  /* USER CODE BEGIN LPTIM5_MspDeInit 1 */

  /* USER CODE END LPTIM5_MspDeInit 1 */
  }

}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hspi->Instance==SPI5)
  {
  /* USER CODE BEGIN SPI5_MspInit 0 */

  /* USER CODE END SPI5_MspInit 0 */
  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SPI45;
    PeriphClkInit.Spi45ClockSelection = RCC_SPI45CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_SPI5_CLK_ENABLE();
  
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**SPI5 GPIO Configuration    
    PF9     ------> SPI5_MOSI
    PF8     ------> SPI5_MISO
    PF7     ------> SPI5_SCK 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI5_MspInit 1 */

  /* USER CODE END SPI5_MspInit 1 */
  }

}

/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  if(hspi->Instance==SPI5)
  {
  /* USER CODE BEGIN SPI5_MspDeInit 0 */

  /* USER CODE END SPI5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI5_CLK_DISABLE();
  
    /**SPI5 GPIO Configuration    
    PF9     ------> SPI5_MOSI
    PF7     ------> SPI5_SCK 
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_9|GPIO_PIN_7);

  /* USER CODE BEGIN SPI5_MspDeInit 1 */

  /* USER CODE END SPI5_MspDeInit 1 */
  }

}

/**
* @brief TIM_Base MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();
  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
  else if(htim_base->Instance==TIM14)
  {
  /* USER CODE BEGIN TIM14_MspInit 0 */

  /* USER CODE END TIM14_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM14_CLK_ENABLE();
  /* USER CODE BEGIN TIM14_MspInit 1 */

  /* USER CODE END TIM14_MspInit 1 */
  }
  else if(htim_base->Instance==TIM16)
  {
  /* USER CODE BEGIN TIM16_MspInit 0 */

  /* USER CODE END TIM16_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM16_CLK_ENABLE();
  /* USER CODE BEGIN TIM16_MspInit 1 */

  /* USER CODE END TIM16_MspInit 1 */
  }
  else if(htim_base->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspInit 0 */

  /* USER CODE END TIM17_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM17_CLK_ENABLE();
  /* USER CODE BEGIN TIM17_MspInit 1 */

  /* USER CODE END TIM17_MspInit 1 */
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspPostInit 0 */

  /* USER CODE END TIM4_MspPostInit 0 */
  
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**TIM4 GPIO Configuration    
    PD13     ------> TIM4_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM4_MspPostInit 1 */

  /* USER CODE END TIM4_MspPostInit 1 */
  }

}
/**
* @brief TIM_Base MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();
  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM14)
  {
  /* USER CODE BEGIN TIM14_MspDeInit 0 */

  /* USER CODE END TIM14_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM14_CLK_DISABLE();
  /* USER CODE BEGIN TIM14_MspDeInit 1 */

  /* USER CODE END TIM14_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM16)
  {
  /* USER CODE BEGIN TIM16_MspDeInit 0 */

  /* USER CODE END TIM16_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM16_CLK_DISABLE();
  /* USER CODE BEGIN TIM16_MspDeInit 1 */

  /* USER CODE END TIM16_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspDeInit 0 */

  /* USER CODE END TIM17_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM17_CLK_DISABLE();
  /* USER CODE BEGIN TIM17_MspDeInit 1 */

  /* USER CODE END TIM17_MspDeInit 1 */
  }

}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(huart->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */
  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART24;
    PeriphClkInit.Uart24ClockSelection = RCC_UART24CLKSOURCE_HSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();
  
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**UART4 GPIO Configuration    
    PG11     ------> UART4_TX
    PB2     ------> UART4_RX 
    */
    GPIO_InitStruct.Pin = STLINK_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_UART4;
    HAL_GPIO_Init(STLINK_RX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = STLINK_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(STLINK_TX_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN UART4_MspInit 1 */

  /* USER CODE END UART4_MspInit 1 */
  }
  else if(huart->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */

  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART35;
    PeriphClkInit.Uart35ClockSelection = RCC_UART35CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB12     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();
  
    /**UART4 GPIO Configuration    
    PG11     ------> UART4_TX
    PB2     ------> UART4_RX 
    */
    HAL_GPIO_DeInit(STLINK_RX_GPIO_Port, STLINK_RX_Pin);

    HAL_GPIO_DeInit(STLINK_TX_GPIO_Port, STLINK_TX_Pin);

  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */
  }
  else if(huart->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB12     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_12);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }

}

/**
* @brief WWDG MSP Initialization
* This function configures the hardware resources used in this example
* @param hwwdg: WWDG handle pointer
* @retval None
*/
void HAL_WWDG_MspInit(WWDG_HandleTypeDef* hwwdg)
{
  if(hwwdg->Instance==WWDG1)
  {
  /* USER CODE BEGIN WWDG1_MspInit 0 */

  /* USER CODE END WWDG1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_WWDG1_CLK_ENABLE();
    /* WWDG1 interrupt Init */
    HAL_NVIC_SetPriority(WWDG1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(WWDG1_IRQn);
  /* USER CODE BEGIN WWDG1_MspInit 1 */

  /* USER CODE END WWDG1_MspInit 1 */
  }

}

/* USER CODE BEGIN 1 */
/**
  * @brief  Initializes I2C MSP.
  * @param  hI2c : I2C handler
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hI2c)
{
    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    
    if(hI2c->Instance == I2C4)
    {
        if(IS_ENGINEERING_BOOT_MODE())
        {
             /*** Configure the I2C peripheral clock ***/ 
            PeriphClkInit.I2c46ClockSelection = RCC_I2C46CLKSOURCE_HSI;
            PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C46;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
            {
              Error_Handler();
            }
        }

        /* Enable GPIO clock */
        __HAL_RCC_GPIOZ_CLK_ENABLE();

        /* Configure I2C Tx/RX as alternate function */
        GPIO_InitStruct.Pin       = GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF6_I2C4;
        HAL_GPIO_Init(GPIOZ, &GPIO_InitStruct);

        /* Enable I2C clock */
        __HAL_RCC_I2C4_CLK_ENABLE();
        /* Force the I2C peripheral clock reset */  
        __HAL_RCC_I2C4_FORCE_RESET();
        /* Release the I2C peripheral clock reset */  
        __HAL_RCC_I2C4_RELEASE_RESET();
        
        HAL_NVIC_SetPriority(I2C4_ER_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(I2C4_ER_IRQn);
        HAL_NVIC_SetPriority(I2C4_EV_IRQn, 0, 2);
        HAL_NVIC_EnableIRQ(I2C4_EV_IRQn);
    }
}

/**
* @brief SD MSP Initialization
* This function configures the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  
  if(hsd->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspInit 0 */
    if (IS_ENGINEERING_BOOT_MODE())
    {
        /** Initializes the peripherals clock 
        */
        PeriphClkInit.Sdmmc12ClockSelection = RCC_SDMMC12CLKSOURCE_PLL4;
        PeriphClkInit.PeriphClockSelection  = RCC_PERIPHCLK_SDMMC12;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        {
            Error_Handler();
        }
    }
  /* USER CODE END SDMMC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration    
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    __HAL_RCC_SDMMC1_FORCE_RESET();
    __HAL_RCC_SDMMC1_RELEASE_RESET();
  
    /* SDMMC1 interrupt Init */
    HAL_NVIC_SetPriority(SDMMC1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);
  /* USER CODE BEGIN SDMMC1_MspInit 1 */

  /* USER CODE END SDMMC1_MspInit 1 */
  }
  if(hsd->Instance==SDMMC2)
  {
  /* USER CODE BEGIN SDMMC2_MspInit 0 */
    if (IS_ENGINEERING_BOOT_MODE())
    {
        /** Initializes the peripherals clock 
        */
        PeriphClkInit.Sdmmc12ClockSelection = RCC_SDMMC12CLKSOURCE_PLL4;
        PeriphClkInit.PeriphClockSelection  = RCC_PERIPHCLK_SDMMC12;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        {
            Error_Handler();
        }
    }
  /* USER CODE END SDMMC2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SDMMC2_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**SDMMC2 GPIO Configuration    
    PB14     ------> SDMMC2_D0
    PB15     ------> SDMMC2_D1
    PB3     ------> SDMMC2_D2
    PB4     ------> SDMMC2_D3
    PE3     ------> SDMMC2_CK
    PG6     ------> SDMMC2_CMD 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_SDIO2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_SDIO2;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_SDIO2;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    __HAL_RCC_SDMMC2_FORCE_RESET();
    __HAL_RCC_SDMMC2_RELEASE_RESET();
  
    /* SDMMC2 interrupt Init */
    HAL_NVIC_SetPriority(SDMMC2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(SDMMC2_IRQn);
  /* USER CODE BEGIN SDMMC2_MspInit 1 */

  /* USER CODE END SDMMC2_MspInit 1 */
  }
}

/**
* @brief SD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{
  if(hsd->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspDeInit 0 */

  /* USER CODE END SDMMC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC1_CLK_DISABLE();
  
    /**SDMMC1 GPIO Configuration    
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    /* SDMMC1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(SDMMC1_IRQn);
  /* USER CODE BEGIN SDMMC1_MspDeInit 1 */

  /* USER CODE END SDMMC1_MspDeInit 1 */
  }

}

/**
  * @brief  DeInitializes I2C MSP.
  * @param  hI2c : I2C handler
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hI2c)
{
    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    
    if(hI2c->Instance == I2C4)
    {
        /* Configure I2C Tx, Rx as alternate function */
        GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
        HAL_GPIO_DeInit(GPIOZ, GPIO_InitStruct.Pin);

        /* Disable I2C clock */
        __HAL_RCC_I2C4_CLK_DISABLE();

        /* Disable NVIC for I2C */
        HAL_NVIC_DisableIRQ(I2C4_ER_IRQn);
        HAL_NVIC_DisableIRQ(I2C4_EV_IRQn);
    }
}

/**
* @brief CRC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC2)
  {
  /* USER CODE BEGIN CRC2_MspInit 0 */

  /* USER CODE END CRC2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CRC2_CLK_ENABLE();
  /* USER CODE BEGIN CRC2_MspInit 1 */

  /* USER CODE END CRC2_MspInit 1 */
  }

}

/**
* @brief CRC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC2)
  {
  /* USER CODE BEGIN CRC2_MspDeInit 0 */

  /* USER CODE END CRC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC2_CLK_DISABLE();
  /* USER CODE BEGIN CRC2_MspDeInit 1 */

  /* USER CODE END CRC2_MspDeInit 1 */
  }

}

/**
* @brief RNG MSP Initialization
* This function configures the hardware resources used in this example
* @param hrng: RNG handle pointer
* @retval None
*/
void HAL_RNG_MspInit(RNG_HandleTypeDef* hrng)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hrng->Instance==RNG2)
  {
  /* USER CODE BEGIN RNG2_MspInit 0 */

  /* USER CODE END RNG2_MspInit 0 */
  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initializes the peripherals clock 
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RNG2;
    PeriphClkInit.Rng2ClockSelection = RCC_RNG2CLKSOURCE_CSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  }

    /* Peripheral clock enable */
    __HAL_RCC_RNG2_CLK_ENABLE();
  /* USER CODE BEGIN RNG2_MspInit 1 */

  /* USER CODE END RNG2_MspInit 1 */
  }

}

/**
* @brief RNG MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrng: RNG handle pointer
* @retval None
*/
void HAL_RNG_MspDeInit(RNG_HandleTypeDef* hrng)
{
  if(hrng->Instance==RNG2)
  {
  /* USER CODE BEGIN RNG2_MspDeInit 0 */

  /* USER CODE END RNG2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RNG2_CLK_DISABLE();
  /* USER CODE BEGIN RNG2_MspDeInit 1 */

  /* USER CODE END RNG2_MspDeInit 1 */
  }

}

/**
* @brief HASH MSP Initialization
* This function configures the hardware resources used in this example
* @param hhash: HASH handle pointer
* @retval None
*/
void HAL_HASH_MspInit(HASH_HandleTypeDef* hhash)
{
  /* USER CODE BEGIN HASH2_MspInit 0 */
  /* USER CODE END HASH2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_HASH2_CLK_ENABLE();
  /* USER CODE BEGIN HASH2_MspInit 1 */
    __HAL_RCC_DMAMUX_CLK_ENABLE();
    
    /* Peripheral DMA init*/
    hdma_hash_in.Instance = DMA2_Stream7;
    hdma_hash_in.Init.Request = DMA_REQUEST_HASH2_IN;
    hdma_hash_in.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_hash_in.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_hash_in.Init.MemInc = DMA_MINC_ENABLE;
    hdma_hash_in.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_hash_in.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_hash_in.Init.Mode = DMA_NORMAL;
    hdma_hash_in.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_hash_in.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_hash_in.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_hash_in.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_hash_in.Init.PeriphBurst = DMA_PBURST_SINGLE;

    if (HAL_DMA_DeInit(&hdma_hash_in) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_DMA_Init(&hdma_hash_in) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hhash,hdmain,hdma_hash_in);
  /* USER CODE END HASH2_MspInit 1 */

}

/**
* @brief HASH MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hhash: HASH handle pointer
* @retval None
*/
void HAL_HASH_MspDeInit(HASH_HandleTypeDef* hhash)
{
  /* USER CODE BEGIN HASH2_MspDeInit 0 */

  /* USER CODE END HASH2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_HASH2_CLK_DISABLE();
  /* USER CODE BEGIN HASH2_MspDeInit 1 */

  /* USER CODE END HASH2_MspDeInit 1 */

}

#if defined (CRYP1) || defined (CRYP2)
void HAL_CRYP_MspInit(CRYP_HandleTypeDef* hcryp)
{
    if(hcryp->Instance==CRYP2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_CRYP2_CLK_ENABLE();
        __HAL_RCC_DMAMUX_CLK_ENABLE();

       /* Peripheral DMA init*/
        hdma_cryp_in.Instance = DMA2_Stream6;
        hdma_cryp_in.Init.Request = DMA_REQUEST_CRYP2_IN;
        hdma_cryp_in.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_cryp_in.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_cryp_in.Init.MemInc = DMA_MINC_ENABLE;
        hdma_cryp_in.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
        hdma_cryp_in.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
        hdma_cryp_in.Init.Mode = DMA_NORMAL;
        hdma_cryp_in.Init.Priority = DMA_PRIORITY_HIGH;
        hdma_cryp_in.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_DeInit(&hdma_cryp_in) != HAL_OK)
        {
            Error_Handler();
        }
        if (HAL_DMA_Init(&hdma_cryp_in) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hcryp,hdmain,hdma_cryp_in);

        hdma_cryp_out.Instance = DMA2_Stream5;
        hdma_cryp_out.Init.Request = DMA_REQUEST_CRYP2_OUT;
        hdma_cryp_out.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_cryp_out.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_cryp_out.Init.MemInc = DMA_MINC_ENABLE;
        hdma_cryp_out.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
        hdma_cryp_out.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
        hdma_cryp_out.Init.Mode = DMA_NORMAL;
        hdma_cryp_out.Init.Priority = DMA_PRIORITY_VERY_HIGH;
        hdma_cryp_out.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_DeInit(&hdma_cryp_out) != HAL_OK)
        {
            Error_Handler();
        }
        if (HAL_DMA_Init(&hdma_cryp_out) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hcryp,hdmaout,hdma_cryp_out);

      /* USER CODE BEGIN CRYP_MspInit 1 */

      /* USER CODE END CRYP_MspInit 1 */
    }
}

void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef* hcryp)
{

  if(hcryp->Instance==CRYP2)
  {
  /* USER CODE BEGIN CRYP_MspDeInit 0 */

  /* USER CODE END CRYP_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRYP2_CLK_DISABLE();

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(hcryp->hdmain);
    HAL_DMA_DeInit(hcryp->hdmaout);
  }
  /* USER CODE BEGIN CRYP_MspDeInit 1 */

  /* USER CODE END CRYP_MspDeInit 1 */

}
#endif

/**
* @brief RTC MSP Initialization
* This function configures the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hrtc->Instance==RTC)
  {
  /* USER CODE BEGIN SDMMC1_MspInit 0 */
    if (IS_ENGINEERING_BOOT_MODE())
    {
        /** Initializes the peripherals clock 
        */
        PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
        PeriphClkInit.PeriphClockSelection  = RCC_PERIPHCLK_RTC;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        {
            Error_Handler();
        }
    }
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE();

  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }

}

/**
* @brief RTC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }

}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
