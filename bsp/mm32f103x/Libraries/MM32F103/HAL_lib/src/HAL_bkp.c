/**
******************************************************************************
* @file    HAL_bkp.c
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file provides all the BKP firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_bkp.h"
#include "HAL_rcc.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup BKP
* @brief BKP driver modules
* @{
*/

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
#define BKP_OFFSET        (BKP_BASE - PERIPH_BASE)

/* --- CR Register ----*/

/* Alias word address of TPAL bit */
#define CR_OFFSET         (BKP_OFFSET + 0x30)
#define TPAL_BitNumber    0x01
#define CR_TPAL_BB        (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPAL_BitNumber * 4))

/* Alias word address of TPE bit */
#define TPE_BitNumber     0x00
#define CR_TPE_BB         (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of TPIE bit */
#define CSR_OFFSET        (BKP_OFFSET + 0x34)
#define TPIE_BitNumber    0x02
#define CSR_TPIE_BB       (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TPIE_BitNumber * 4))

/* Alias word address of TIF bit */
#define TIF_BitNumber     0x09
#define CSR_TIF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TIF_BitNumber * 4))

/* Alias word address of TEF bit */
#define TEF_BitNumber     0x08
#define CSR_TEF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEF_BitNumber * 4))

/* ---------------------- BKP registers bit mask ------------------------ */

/* RTCCR register bit mask */
#define RTCCR_CAL_Mask    ((uint16_t)0xFF80)
#define RTCCR_Mask        ((uint16_t)0xFC7F)

/* CSR register bit mask */
#define CSR_CTE_Set       ((uint16_t)0x0001)
#define CSR_CTI_Set       ((uint16_t)0x0002)

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
* @brief  Deinitializes the BKP peripheral registers to their default
*   reset values.
* @param  None
* @retval : None
*/
void BKP_DeInit(void)
{
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);
}

/**
* @brief  Configures the Tamper Pin active level.
* @param BKP_TamperPinLevel: specifies the Tamper Pin active level.
*   This parameter can be one of the following values:
* @arg BKP_TamperPinLevel_High: Tamper pin active on high level
* @arg BKP_TamperPinLevel_Low: Tamper pin active on low level
* @retval : None
*/
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel)
{
    /* Check the parameters */
    assert_param(IS_BKP_TAMPER_PIN_LEVEL(BKP_TamperPinLevel));
    *(__IO uint32_t *) CR_TPAL_BB = BKP_TamperPinLevel;
}

/**
* @brief  Enables or disables the Tamper Pin activation.
* @param NewState: new state of the Tamper Pin activation.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void BKP_TamperPinCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_TPE_BB = (uint32_t)NewState;
}

/**
* @brief  Enables or disables the Tamper Pin Interrupt.
* @param NewState: new state of the Tamper Pin Interrupt.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void BKP_ITConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CSR_TPIE_BB = (uint32_t)NewState;
}

/**
* @brief  Select the RTC output source to output on the Tamper pin.
* @param BKP_RTCOutputSource: specifies the RTC output source.
*   This parameter can be one of the following values:
* @arg BKP_RTCOutputSource_None: no RTC output on the Tamper pin.
* @arg BKP_RTCOutputSource_CalibClock: output the RTC clock
*   with frequency divided by 64 on the Tamper pin.
* @arg BKP_RTCOutputSource_Alarm: output the RTC Alarm pulse
*   signal on the Tamper pin.
* @arg BKP_RTCOutputSource_Second: output the RTC Second pulse
*   signal on the Tamper pin.
* @retval : None
*/
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource)
{
    uint16_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_BKP_RTC_OUTPUT_SOURCE(BKP_RTCOutputSource));
    tmpreg = BKP->RTCCR;
    /* Clear CCO, ASOE and ASOS bits */
    tmpreg &= RTCCR_Mask;

    /* Set CCO, ASOE and ASOS bits according to BKP_RTCOutputSource value */
    tmpreg |= BKP_RTCOutputSource;
    /* Store the new value */
    BKP->RTCCR = tmpreg;
}

/**
* @brief  Sets RTC Clock Calibration value.
* @param CalibrationValue: specifies the RTC Clock Calibration value.
*   This parameter must be a number between 0 and 0x7F.
* @retval : None
*/
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue)
{
    uint16_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_BKP_CALIBRATION_VALUE(CalibrationValue));
    tmpreg = BKP->RTCCR;
    /* Clear CAL[6:0] bits */
    tmpreg &= RTCCR_CAL_Mask;
    /* Set CAL[6:0] bits according to CalibrationValue value */
    tmpreg |= CalibrationValue;
    /* Store the new value */
    BKP->RTCCR = tmpreg;
}

/**
* @brief  Writes user data to the specified Data Backup Register.
* @param BKP_DR: specifies the Data Backup Register.
*   This parameter can be BKP_DRx where x:[1, 42]
* @param Data: data to write
* @retval : None
*/
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_BKP_DR(BKP_DR));
    *(__IO uint16_t *) (BKP_BASE + BKP_DR) = Data;
}

/**
* @brief  Reads data from the specified Data Backup Register.
* @param BKP_DR: specifies the Data Backup Register.
*   This parameter can be BKP_DRx where x:[1, 42]
* @retval : The content of the specified Data Backup Register
*/
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR)
{
    /* Check the parameters */
    assert_param(IS_BKP_DR(BKP_DR));
    return (*(__IO uint16_t *) (BKP_BASE + BKP_DR));
}

/**
* @brief  Checks whether the Tamper Pin Event flag is set or not.
* @param  None
* @retval : The new state of the Tamper Pin Event flag (SET or RESET).
*/
FlagStatus BKP_GetFlagStatus(void)
{
    return (FlagStatus)(*(__IO uint32_t *) CSR_TEF_BB);
}

/**
* @brief  Clears Tamper Pin Event pending flag.
* @param  None
* @retval : None
*/
void BKP_ClearFlag(void)
{
    /* Set CTE bit to clear Tamper Pin Event flag */
    BKP->CSR |= CSR_CTE_Set;
}

/**
* @brief  Checks whether the Tamper Pin Interrupt has occurred or not.
* @param  None
* @retval : The new state of the Tamper Pin Interrupt (SET or RESET).
*/
ITStatus BKP_GetITStatus(void)
{
    return (ITStatus)(*(__IO uint32_t *) CSR_TIF_BB);
}

/**
* @brief  Clears Tamper Pin Interrupt pending bit.
* @param  None
* @retval : None
*/
void BKP_ClearITPendingBit(void)
{
    /* Set CTI bit to clear Tamper Pin Interrupt pending bit */
    BKP->CSR |= CSR_CTI_Set;
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

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
