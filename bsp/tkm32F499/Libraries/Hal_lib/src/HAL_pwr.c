/**
******************************************************************************
* @file  HAL_pwr.c
* @author  IC Applications Department
* @version  V0.8
* @date  2019_08_02
* @brief  This file provides all the PWR firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, HOLOCENE SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 HOLOCENE</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_pwr.h"
#include "HAL_rcc.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup PWR
* @brief PWR driver modules
* @{
*/

/** @defgroup PWR_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup PWR_Private_Defines
* @{
*/

/* --------- PWR registers bit address in the alias region ---------- */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR Register ---*/

/* Alias word address of DBP bit */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of EWUP bit */
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
#define EWUP_BitNumber           0x08
#define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_PDDS_Set              ((uint32_t)0x00000002)
#define CR_DS_Mask               ((uint32_t)0xFFFFFFFC)
#define CR_CWUF_Set              ((uint32_t)0x00000004)
#define CR_PLS_Mask              ((uint32_t)0xFFFFE1FF)

/* --------- Cortex System Control register bit mask ---------------- */

/* Cortex System Control register address */
#define SCB_SysCtrl              ((uint32_t)0xE000ED10)

/* SLEEPDEEP bit mask */
#define SysCtrl_SLEEPDEEP_Set    ((uint32_t)0x00000004)
/**
* @}
*/

/** @defgroup PWR_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup PWR_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup PWR_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup PWR_Private_Functions
* @{
*/

/**
* @brief  Deinitializes the PWR peripheral registers to their default
*   reset values.
* @param  None
* @retval : None
*/
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
* @brief  Enables or disables access to the RTC and backup registers.
* @param NewState: new state of the access to the RTC and backup
*   registers. This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  //*(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
  if(NewState!=DISABLE)
  {
    PWR->CR |= 0x00000100;
  }
  else
  {
    PWR->CR &= 0xfffffeff;
  }

}

/**
* @brief  Enables or disables the Power Voltage Detector(PVD).
* @param NewState: new state of the PVD.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if(NewState==ENABLE)
  {
    PWR->CR |= 0x00000010;
  }
  else
  {
    PWR->CR &= 0xffffffef;
  }

}

/**
* @brief  Configures the voltage threshold detected by the Power Voltage
*   Detector(PVD).
* @param PWR_PVDLevel: specifies the PVD detection level
*   This parameter can be one of the following values:
* @arg PWR_PVDLevel_2V6: PVD detection level set to 2.6V
* @arg PWR_PVDLevel_2V8: PVD detection level set to 2.8V
* @arg PWR_PVDLevel_3V0: PVD detection level set to 3.0V
* @arg PWR_PVDLevel_3V2: PVD detection level set to 3.2V
* @arg PWR_PVDLevel_3V4: PVD detection level set to 3.4V
* @arg PWR_PVDLevel_3V6: PVD detection level set to 3.6V
* @arg PWR_PVDLevel_3V8: PVD detection level set to 3.8V
* @arg PWR_PVDLevel_4V0: PVD detection level set to 4.0V
* @arg PWR_PVDLevel_4V2: PVD detection level set to 4.2V
* @arg PWR_PVDLevel_4V4: PVD detection level set to 4.4V
* @arg PWR_PVDLevel_4V6: PVD detection level set to 4.6V
* @retval : None
*/
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  tmpreg = PWR->CR;
  /* Clear PLS[7:5] bits */
  tmpreg &= CR_PLS_Mask;
  /* Set PLS[7:5] bits according to PWR_PVDLevel value */
  tmpreg |= PWR_PVDLevel;
  /* Store the new value */
  PWR->CR = tmpreg;
}

/**
* @brief  Enables or disables the WakeUp Pin functionality.
* @param NewState: new state of the WakeUp Pin functionality.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if(NewState!=DISABLE)
  {
    PWR->CSR |= 0x00000100;
  }
  else
  {
    PWR->CSR &= 0xfffffeff;
  }
}

/**
* @brief  Enters STOP mode.
* @param PWR_Regulator: specifies the regulator state in STOP mode.
*   This parameter can be one of the following values:
* @arg PWR_Regulator_ON: STOP mode with regulator ON
* @arg PWR_Regulator_LowPower: STOP mode with
*   regulator in low power mode
* @param PWR_STOPEntry: specifies if STOP mode in entered with WFI or
*   WFE instruction.
*   This parameter can be one of the following values:
* @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
* @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
* @retval : None
*/
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

  /* Select the regulator state in STOP mode ---------------------------------*/
  tmpreg = PWR->CR;
  /* Clear PDDS and LPDS bits */
  tmpreg &= CR_DS_Mask;
  /* Set LPDS bit according to PWR_Regulator value */
  tmpreg |= PWR_Regulator;
  /* Store the new value */
  PWR->CR = tmpreg;
  /* Set SLEEPDEEP bit of Cortex System Control Register */

  SCB->SCR |= SysCtrl_SLEEPDEEP_Set;

  /* Select STOP mode entry --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
}

/**
* @brief  Enters STANDBY mode.
* @param  None
* @retval : None
*/
void PWR_EnterSTANDBYMode(void)
{
  /* Clear Wake-up flag */
  PWR->CR |= CR_CWUF_Set;
  /* Select STANDBY mode */
  PWR->CR |= CR_PDDS_Set;
  /* Set SLEEPDEEP bit of Cortex System Control Register */

  SCB->SCR |= SysCtrl_SLEEPDEEP_Set;
  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

/**
* @brief  Checks whether the specified PWR flag is set or not.
* @param PWR_FLAG: specifies the flag to check.
*   This parameter can be one of the following values:
* @arg PWR_FLAG_WU: Wake Up flag
* @arg PWR_FLAG_SB: StandBy flag
* @arg PWR_FLAG_PVDO: PVD Output
* @retval : The new state of PWR_FLAG (SET or RESET).
*/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
* @brief  Clears the PWR's pending flags.
* @param PWR_FLAG: specifies the flag to clear.
*   This parameter can be one of the following values:
* @arg PWR_FLAG_WU: Wake Up flag
* @arg PWR_FLAG_SB: StandBy flag
* @retval : None
*/
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

  PWR->CR |=  PWR_FLAG << 2;
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

/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/
