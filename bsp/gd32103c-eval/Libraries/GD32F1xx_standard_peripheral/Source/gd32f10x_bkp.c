/**
  ******************************************************************************
  * @brief   BKP functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_bkp.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup BKP
  * @brief BKP driver modules
  * @{
  */

/** @defgroup BKP_Private_Defines
  * @{
  */
/* RTCOUTPUT bit is masked in BKP_RCCR register */
#define RTCOUTPUT_MASK         ((uint16_t)0xFC7F)

/**
  * @}
  */


/** @defgroup BKP_Private_Functions
  * @{
  */

/**
  * @brief  Reset the BKP peripheral registers.
  * @param  None
  * @retval None
  */
void BKP_DeInit(void)
{
    RCC_BackupReset_Enable(ENABLE);
    RCC_BackupReset_Enable(DISABLE);
}

/**
  * @brief  Write user data to the BKP_DRx register.
  * @param  BKP_DR: the Backup Data Register.
  *   This parameter can be BKP_DRx where x can be (1..42)
  * @param  Data: data to write
  * @retval None
  */
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)BKP_BASE;
    temp += BKP_DR;

    /* Store the write data */
    *(__IO uint16_t *) temp = Data;
}

/**
  * @brief  Read data from the BKP_DRx register.
  * @param  BKP_DR: The Backup Data Register.
  *   This parameter can be BKP_DRx where x can be (1..42)
  * @retval The content of the BKP_DRx register.
  */
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)BKP_BASE;
    temp += BKP_DR;

    /* Return the BKP_DRx register value */
    return (*(__IO uint16_t *) temp);
}

/**
  * @brief  Configure the RTC output on the Tamper pin.
  * @param  BKP_RTCOUTPUT: the RTC output.
  *   This parameter can be one of the following values:
  *     @arg BKP_RTCOUTPUT_NULL: no RTC output on the TAMPER pin.
  *     @arg BKP_RTCOUTPUT_CLKCAL: output the RTC clock with frequency
  *                                divided by 64 on the TAMPER pin.
  *     @arg BKP_RTCOUTPUT_ALARM: output the RTC Alarm pulse signal on
  *                               the TAMPER pin.
  *     @arg BKP_RTCOUTPUT_SECOND: output the RTC Second pulse signal on
  *                                the TAMPER pin.
  * @retval None
  */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOUTPUT)
{
    uint16_t temp = 0;

    temp = BKP->RCCR;

    /* Clear RCCOE, ROE and ROS bits */
    temp &= RTCOUTPUT_MASK;

    /* Set RCCOE, ROE and ROS bits according to BKP_RTCOUTPUT value */
    temp |= BKP_RTCOUTPUT;

    /* Store the new value */
    BKP->RCCR = temp;
}

/**
  * @brief  Set RTC Clock Calibration value.
  * @param  CalibrationValue: the RTC Clock Calibration value.
  *   This parameter must be a number between 0 and 0x7F.
  * @retval None
  */
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue)
{
    uint16_t temp = 0;

    temp = BKP->RCCR;

    /* Clear RCCV[6:0] bits */
    temp &= ~BKP_RCCR_RCCV;

    /* Set CAL[6:0] bits according to CalibrationValue */
    temp |= CalibrationValue;

    /* Store the new value */
    BKP->RCCR = temp;
}

/**
  * @brief  Configure the TAMPER pin active level.
  * @param  BKP_TPAL: the TAMPER pin active level.
  *   This parameter can be one of the following values:
  *     @arg BKP_TPAL_HIGH: TAMPER pin active on high level
  *     @arg BKP_TPAL_LOW: TAMPER pin active on low level
  * @param  NewValue: New value of the TAMPER pin state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BKP_TamperPinConfig(uint16_t BKP_TPAL, TypeState NewValue)
{
    uint16_t temp = 0;

    temp = BKP->TPCR;

    /* Clear TPE bit */
    temp &= ~((uint16_t)BKP_TPCR_TPE);

    /* Configure TPAL bit according to BKP_TPAL value */
    temp |= BKP_TPAL;

    /* Store the new value */
    BKP->TPCR = temp;

    /* Enable the TAMPER pin */
    if (NewValue != DISABLE) {
        /* The TAMPER pin is dedicated for the Backup Reset function */
        BKP->TPCR |= BKP_TPCR_TPE;
    } else {
        /* The TAMPER pin is free for GPIO functions */
        BKP->TPCR &= ~((uint16_t)BKP_TPCR_TPE);
    }
}

/**
  * @brief  Enable or disable the Tamper Interrupt.
  * @param  NewValue: New value of the Tamper Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BKP_TamperINT_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the tamper interrupt */
        BKP->TIER |= BKP_TIER_TIE;
    } else {
        /* Disable the tamper interrupt */
        BKP->TIER &= ~BKP_TIER_TIE;
    }
}

/**
  * @brief  Get the bit flag of Tamper Event.
  * @param  None
  * @retval The new value of Tamper Event flag (SET or RESET).
  */
TypeState BKP_GetBitState(void)
{
    /* Check and get the Tamper Event flag */
    if ((BKP->TIER & BKP_TIER_TEF) != (uint16_t)RESET) {
        /* Tamper Event occured */
        return SET;
    } else {
        /* No Tamper Event occured */
        return RESET;
    }
}

/**
  * @brief  Clear the bit flag of Tamper Event.
  * @param  None
  * @retval None
  */
void BKP_ClearBitState(void)
{
    /* Set the TER bit to clear Tamper Event flag */
    BKP->TIER |= BKP_TIER_TER;
}

/**
  * @brief  Get the interrupt bit flag of Tamper Interrupt.
  * @param  None
  * @retval The new value of the Tamper Interrupt flag (SET or RESET).
  */
TypeState BKP_GetIntBitState(void)
{
    /* Check and get the Tamper Interrupt flag */
    if ((BKP->TIER & BKP_TIER_TIF) != (uint16_t)RESET) {
        /* Tamper Interrupt occured */
        return SET;
    } else {
        /* No Tamper Interrupt occured */
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt bit flag of Tamper Interrupt.
  * @param  None
  * @retval None
  */
void BKP_ClearIntBitState(void)
{
    /* Set the TIR bit to clear Tamper Interrupt flag */
    BKP->TIER |= BKP_TIER_TIR;
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
