/**
  ******************************************************************************
  * @file    stm32wlxx_ll_pwr.c
  * @author  MCD Application Team
  * @brief   PWR LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_ll_pwr.h"
#include "stm32wlxx_ll_bus.h"

/** @addtogroup STM32WLxx_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @addtogroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */
/* Definitions of PWR registers reset value */
#define PWR_CR1_RESET_VALUE   (0x00000200)
#define PWR_CR2_RESET_VALUE   (0x00000000)
#define PWR_CR3_RESET_VALUE   (PWR_CR3_EIWUL)
#define PWR_CR4_RESET_VALUE   (0x00000000)
#define PWR_CR5_RESET_VALUE   (0x00000000)
#define PWR_PUCRA_RESET_VALUE (0x00000000)
#define PWR_PDCRA_RESET_VALUE (0x00000000)
#define PWR_PUCRB_RESET_VALUE (0x00000000)
#define PWR_PDCRB_RESET_VALUE (0x00000000)
#define PWR_PUCRC_RESET_VALUE (0x00000000)
#define PWR_PDCRC_RESET_VALUE (0x00000000)
#define PWR_PUCRH_RESET_VALUE (0x00000000)
#define PWR_PDCRH_RESET_VALUE (0x00000000)
#if defined(DUAL_CORE)
#define PWR_C2CR1_RESET_VALUE (PWR_C2CR1_LPMS_2 | PWR_C2CR1_LPMS_1 | PWR_C2CR1_LPMS_0)
#define PWR_C2CR3_RESET_VALUE (0x00000000)
#endif
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_LL_Exported_Functions
  * @{
  */

/** @addtogroup PWR_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the PWR registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PWR registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_PWR_DeInit(void)
{
  /* Apply reset values to all PWR registers */
  LL_PWR_WriteReg(CR1, PWR_CR1_RESET_VALUE);
  LL_PWR_WriteReg(CR2, PWR_CR2_RESET_VALUE);
  LL_PWR_WriteReg(CR3, PWR_CR3_RESET_VALUE);
  LL_PWR_WriteReg(CR4, PWR_CR4_RESET_VALUE);
  LL_PWR_WriteReg(CR5, PWR_CR5_RESET_VALUE);
  LL_PWR_WriteReg(PUCRA, PWR_PUCRA_RESET_VALUE);
  LL_PWR_WriteReg(PDCRA, PWR_PDCRA_RESET_VALUE);
  LL_PWR_WriteReg(PUCRB, PWR_PUCRB_RESET_VALUE);
  LL_PWR_WriteReg(PDCRB, PWR_PDCRB_RESET_VALUE);
  LL_PWR_WriteReg(PUCRC, PWR_PUCRC_RESET_VALUE);
  LL_PWR_WriteReg(PDCRC, PWR_PDCRC_RESET_VALUE);
  LL_PWR_WriteReg(PUCRH, PWR_PUCRH_RESET_VALUE);
  LL_PWR_WriteReg(PDCRH, PWR_PDCRH_RESET_VALUE);
#ifdef CORE_CM0PLUS
  LL_PWR_WriteReg(C2CR1, PWR_C2CR1_RESET_VALUE);
  LL_PWR_WriteReg(C2CR3, PWR_C2CR3_RESET_VALUE);
#endif

  /* Clear all flags */
#if defined(DUAL_CORE)
  LL_PWR_WriteReg(SCR,
                  LL_PWR_SCR_CWUF
                  | LL_PWR_SCR_CWRFBUSYF
                  | LL_PWR_SCR_CWPVDF
                  | LL_PWR_SCR_CC2HF
                 );
#else
  LL_PWR_WriteReg(SCR,
                  LL_PWR_SCR_CWUF
                  | LL_PWR_SCR_CWRFBUSYF
                  | LL_PWR_SCR_CWPVDF
                 );
#endif

#ifdef CORE_CM0PLUS
  LL_PWR_WriteReg(EXTSCR,
                  LL_PWR_EXTSCR_C2CSSF
                 );
#else
  LL_PWR_WriteReg(EXTSCR,
                  LL_PWR_EXTSCR_C1CSSF
                 );
#endif

  return SUCCESS;
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
#endif /* defined(PWR) */
/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
