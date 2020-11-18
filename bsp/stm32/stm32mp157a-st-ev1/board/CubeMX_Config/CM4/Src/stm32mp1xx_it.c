/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32mp1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32mp1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern IPCC_HandleTypeDef hipcc;
extern LPTIM_HandleTypeDef hlptim1;
extern LPTIM_HandleTypeDef hlptim2;
extern LPTIM_HandleTypeDef hlptim3;
extern LPTIM_HandleTypeDef hlptim4;
extern LPTIM_HandleTypeDef hlptim5;
extern WWDG_HandleTypeDef hwwdg1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32MP1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32mp1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles Window watchdog interrupt.
  */
void WWDG1_IRQHandler(void)
{
  /* USER CODE BEGIN WWDG1_IRQn 0 */

  /* USER CODE END WWDG1_IRQn 0 */
  HAL_WWDG_IRQHandler(&hwwdg1);
  /* USER CODE BEGIN WWDG1_IRQn 1 */

  /* USER CODE END WWDG1_IRQn 1 */
}

/**
  * @brief This function handles LPTIM1 global interrupt.
  */
void LPTIM1_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM1_IRQn 0 */

  /* USER CODE END LPTIM1_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim1);
  /* USER CODE BEGIN LPTIM1_IRQn 1 */

  /* USER CODE END LPTIM1_IRQn 1 */
}

/**
  * @brief This function handles IPCC RX1 occupied interrupt.
  */
void IPCC_RX1_IRQHandler(void)
{
  /* USER CODE BEGIN IPCC_RX1_IRQn 0 */

  /* USER CODE END IPCC_RX1_IRQn 0 */
  HAL_IPCC_RX_IRQHandler(&hipcc);
  /* USER CODE BEGIN IPCC_RX1_IRQn 1 */

  /* USER CODE END IPCC_RX1_IRQn 1 */
}

/**
  * @brief This function handles IPCC TX1 free interrupt.
  */
void IPCC_TX1_IRQHandler(void)
{
  /* USER CODE BEGIN IPCC_TX1_IRQn 0 */

  /* USER CODE END IPCC_TX1_IRQn 0 */
  HAL_IPCC_TX_IRQHandler(&hipcc);
  /* USER CODE BEGIN IPCC_TX1_IRQn 1 */

  /* USER CODE END IPCC_TX1_IRQn 1 */
}

/**
  * @brief This function handles LPTIM2 global interrupt.
  */
void LPTIM2_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM2_IRQn 0 */

  /* USER CODE END LPTIM2_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim2);
  /* USER CODE BEGIN LPTIM2_IRQn 1 */

  /* USER CODE END LPTIM2_IRQn 1 */
}

/**
  * @brief This function handles LPTIM3 global interrupt.
  */
void LPTIM3_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM3_IRQn 0 */

  /* USER CODE END LPTIM3_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim3);
  /* USER CODE BEGIN LPTIM3_IRQn 1 */

  /* USER CODE END LPTIM3_IRQn 1 */
}

/**
  * @brief This function handles LPTIM4 global interrupt.
  */
void LPTIM4_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM4_IRQn 0 */

  /* USER CODE END LPTIM4_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim4);
  /* USER CODE BEGIN LPTIM4_IRQn 1 */

  /* USER CODE END LPTIM4_IRQn 1 */
}

/**
  * @brief This function handles LPTIM5 global interrupt.
  */
void LPTIM5_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM5_IRQn 0 */

  /* USER CODE END LPTIM5_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim5);
  /* USER CODE BEGIN LPTIM5_IRQn 1 */

  /* USER CODE END LPTIM5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
