/**
 **************************************************************************
 * File Name    : at32f4xx_bkp.c
 * Description  : at32f4xx BKP source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_bkp.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup BKP
  * @brief BKP driver modules
  * @{
  */

#if defined (AT32F403xx) || defined (AT32F413xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)

/** @defgroup BKP_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_Defines
  * @{
  */

/* ------------ BKP registers bit address in the alias region --------------- */
#define BKP_OFFSET                  (BKP_BASE - PERIPH_BASE)

/* --- CTRL Register ----*/

/* Alias word address of TPAL bit */
#define CTRL_OFFSET                 (BKP_OFFSET + 0x30)
#define TPALV_BitPos                0x01
#define CTRL_TPALV_BBMAP            (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (TPALV_BitPos * 4))

/* Alias word address of TPE bit */
#define TPEN_BitPos                 0x00
#define CTRL_TPEN_BBMAP             (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (TPEN_BitPos * 4))

/* --- CTRLSTS Register ---*/

/* Alias word address of TPIE bit */
#define CTRLSTS_OFFSET              (BKP_OFFSET + 0x34)
#define TPIEN_BitPos                0x02
#define CTRLSTS_TPIEN_BBMAP         (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (TPIEN_BitPos * 4))

/* Alias word address of TIF bit */
#define TPIF_BitPos                 0x09
#define CTRLSTS_TPIF_BBMAP          (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (TPIF_BitPos * 4))

/* Alias word address of TEF bit */
#define TPEF_BitPos                 0x08
#define CTRLSTS_TPEF_BBMAP          (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (TPEF_BitPos * 4))

/* ---------------------- BKP registers bit mask ------------------------ */

/* RTCCR register bit mask */
#define RTCCAL_CAL_MASK             ((uint16_t)0xFF80)
#define RTCCAL_MASK                 ((uint16_t)0xFC7F)

/**
  * @}
  */


/** @defgroup BKP_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the BKP peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void BKP_Reset(void)
{
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
}

/**
  * @brief  Configures the Tamper Pin active level.
  * @param  BKP_TamperPinLevel: specifies the Tamper Pin active level.
  *   This parameter can be one of the following values:
  *     @arg BKP_TamperPinLv_H: Tamper pin active on high level
  *     @arg BKP_TamperPinLv_L: Tamper pin active on low level
  * @retval None
  */
void BKP_TamperPinLvConfig(uint16_t BKP_TamperPinLevel)
{
  /* Check the parameters */
  assert_param(IS_BKP_TAMPER_PIN_LV(BKP_TamperPinLevel));
  *(__IO uint32_t *) CTRL_TPALV_BBMAP = BKP_TamperPinLevel;
}

/**
  * @brief  Enables or disables the Tamper Pin activation.
  * @param  NewState: new state of the Tamper Pin activation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BKP_TamperPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CTRL_TPEN_BBMAP = (uint32_t)NewState;
}

/**
  * @brief  Enables or disables the Tamper Pin Interrupt.
  * @param  NewState: new state of the Tamper Pin Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BKP_IntConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CTRLSTS_TPIEN_BBMAP = (uint32_t)NewState;
}

/**
  * @brief  Select the RTC output source to output on the Tamper pin.
  * @param  BKP_RTCOutputSource: specifies the RTC output source.
  *   This parameter can be one of the following values:
  *     @arg BKP_RTCOutput_None: no RTC output on the Tamper pin.
  *     @arg BKP_RTCOutput_CalClk: output the RTC clock with frequency
  *                                          divided by 64 on the Tamper pin.
  *     @arg BKP_RTCOutput_Alarm: output the RTC Alarm pulse signal on
  *                                     the Tamper pin.
  *     @arg BKP_RTCOutput_Second: output the RTC Second pulse signal on
  *                                      the Tamper pin.
  * @retval None
  */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BKP_RTC_OUTPUT_SEL(BKP_RTCOutputSource));
  tmpreg = BKP->RTCCAL;
  /* Clear CCO, ASOE and ASOS bits */
  tmpreg &= RTCCAL_MASK;

  /* Set CCO, ASOE and ASOS bits according to BKP_RTCOutputSource value */
  tmpreg |= BKP_RTCOutputSource;
  /* Store the new value */
  BKP->RTCCAL = tmpreg;
}

/**
  * @brief  Sets RTC Clock Calibration value.
  * @param  CalibrationValue: specifies the RTC Clock Calibration value.
  *   This parameter must be a number between 0 and 0x7F.
  * @retval None
  */
void BKP_SetRTCCalValue(uint8_t CalibrationValue)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BKP_CAL_VAL(CalibrationValue));
  tmpreg = BKP->RTCCAL;
  /* Clear CAL[6:0] bits */
  tmpreg &= RTCCAL_CAL_MASK;
  /* Set CAL[6:0] bits according to CalibrationValue value */
  tmpreg |= CalibrationValue;
  /* Store the new value */
  BKP->RTCCAL = tmpreg;
}

/**
  * @brief  Writes user data to the specified Data Backup Register.
  * @param  BKP_DR: specifies the Data Backup Register.
  *   This parameter can be BKP_DRx where x:[1, 42]
  * @param  Data: data to write
  * @retval None
  */
void BKP_WriteBackupReg(uint16_t BKP_DR, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_BKP_DT(BKP_DR));

  tmp = (uint32_t)BKP_BASE;
  tmp += BKP_DR;

  *(__IO uint32_t *) tmp = Data;
}

/**
  * @brief  Reads data from the specified Data Backup Register.
  * @param  BKP_DR: specifies the Data Backup Register.
  *   This parameter can be BKP_DRx where x:[1, 42]
  * @retval The content of the specified Data Backup Register
  */
uint16_t BKP_ReadBackupReg(uint16_t BKP_DR)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_BKP_DT(BKP_DR));

  tmp = (uint32_t)BKP_BASE;
  tmp += BKP_DR;

  return (*(__IO uint16_t *) tmp);
}

/**
  * @brief  Checks whether the Tamper Pin Event flag is set or not.
  * @param  None
  * @retval The new state of the Tamper Pin Event flag (SET or RESET).
  */
FlagStatus BKP_GetFlagStatus(void)
{
  return (FlagStatus)(*(__IO uint32_t *) CTRLSTS_TPEF_BBMAP);
}

/**
  * @brief  Clears Tamper Pin Event pending flag.
  * @param  None
  * @retval None
  */
void BKP_ClearFlag(void)
{
  /* Set CTE bit to clear Tamper Pin Event flag */
  BKP->CTRLSTS |= BKP_CTRLSTS_CTPEF;
}

/**
  * @brief  Checks whether the Tamper Pin Interrupt has occurred or not.
  * @param  None
  * @retval The new state of the Tamper Pin Interrupt (SET or RESET).
  */
ITStatus BKP_GetIntStatus(void)
{
  return (ITStatus)(*(__IO uint32_t *) CTRLSTS_TPIF_BBMAP);
}

/**
  * @brief  Clears Tamper Pin Interrupt pending bit.
  * @param  None
  * @retval None
  */
void BKP_ClearIntPendingBit(void)
{
  /* Set CTI bit to clear Tamper Pin Interrupt pending bit */
  BKP->CTRLSTS |= BKP_CTRLSTS_CTPIF;
}

/**
  * @}
  */

#endif /* AT32F403xx || AT32F413xx || AT32F403Axx || AT32F407xx */

/**
  * @}
  */

/**
  * @}
  */


