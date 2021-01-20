/**
  ******************************************************************************
  * @brief   IWDG functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_iwdg.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup IWDG
  * @brief IWDG driver modules
  * @{
  */

/** @defgroup IWDG_Private_Variables
  * @{
  */

/* CTLR register bit mask */
#define CTLR_KEY_RELOAD    ((uint16_t)0xAAAA)
#define CTLR_KEY_ENABLE    ((uint16_t)0xCCCC)

/**
  * @}
  */

/** @defgroup IWDG_Private_Functions
  * @{
  */

/**
  * @brief  Enable or disable the IWDG_PSR, IWDG_RLDR and IWDG_WND write protection.
  * @param  IWDG_WriteAccess: value to enable or disable the write access to registers.
  *   This parameter can be one of the following values:
  *     @arg IWDG_WRITEACCESS_ENABLE: Enable write access to IWDG_PSR, IWDG_RLDR and IWDG_WND registers
  *     @arg IWDG_WRITEACCESS_DISABLE: Disable write access to IWDG_PSR, IWDG_RLDR and IWDG_WND registers
  * @retval None
  */
void IWDG_Write_Enable(uint16_t IWDG_WriteAccess)
{
    IWDG->CTLR = IWDG_WriteAccess;
}

/**
  * @brief  Set IWDG prescaler value.
  * @param  PrescalerValue: IWDG Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg IWDG_PRESCALER_4: IWDG prescaler set to 4
  *     @arg IWDG_PRESCALER_8: IWDG prescaler set to 8
  *     @arg IWDG_PRESCALER_16: IWDG prescaler set to 16
  *     @arg IWDG_PRESCALER_32: IWDG prescaler set to 32
  *     @arg IWDG_PRESCALER_64: IWDG prescaler set to 64
  *     @arg IWDG_PRESCALER_128: IWDG prescaler set to 128
  *     @arg IWDG_PRESCALER_256: IWDG prescaler set to 256
  * @retval None
  */
void IWDG_SetPrescaler(uint8_t PrescalerValue)
{
    IWDG->PSR = PrescalerValue;
}

/**
  * @brief  Set independent watchdog counter reload value.
  * @param  ReloadValue: IWDG Reload value.
  *   This parameter must be between 0 and 0x0FFF.
  * @retval None
  */
void IWDG_SetReloadValue(uint16_t ReloadValue)
{
    IWDG->RLDR = ReloadValue;
}

/**
  * @brief  Reload the counter.
  * @param  None
  * @retval None
  */
void IWDG_ReloadCounter(void)
{
    IWDG->CTLR = CTLR_KEY_RELOAD;
}

/**
  * @brief  Start the independent watchdog counter.
  * @param  None
  * @retval None
  */
void IWDG_Enable(void)
{
    IWDG->CTLR = CTLR_KEY_ENABLE;
}

/**
  * @brief  Check registers' bit state.
  * @param  IWDG_FLAG: the flag to check.
  *   This parameter can be one of the following values:
  *     @arg IWDG_BIT_PUD: A write operation to IWDG_PSR register on going
  *     @arg IWDG_BIT_RUD: A write operation to IWDG_RLDR register on going
  *     @arg IWDG_BIT_WUD: A write operation to IWDG_WND register on going
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
TypeState IWDG_GetBitState(uint16_t IWDG_FLAG)
{
    if ((IWDG->STR & IWDG_FLAG) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
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

/**
  * @}
  */

