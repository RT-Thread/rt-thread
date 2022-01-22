////////////////////////////////////////////////////////////////////////////////
/// @file     hal_wwdg.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE WWDG FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_WWDG_C_

// Files includes
#include "hal_wwdg.h"
#include "hal_rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup WWDG_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup WWDG_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the WWDG peripheral registers to their default reset
/// values.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_DeInit()
{
    exRCC_APB1PeriphReset(RCC_APB1RSTR_WWDG);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the WWDG Prescaler.
/// @param  WWDG_Prescaler: specifies the WWDG Prescaler.
///         This parameter can be one of the following values:
///             @arg WWDG_Prescaler_1: WWDG counter clock = APB1CLK / 4096 / 1
///             @arg WWDG_Prescaler_2: WWDG counter clock = APB1CLK / 4096 / 2
///             @arg WWDG_Prescaler_4: WWDG counter clock = APB1CLK / 4096 / 4
///             @arg WWDG_Prescaler_8: WWDG counter clock = APB1CLK / 4096 / 8
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_SetPrescaler(u32 prescaler)
{
    WWDG->CFGR = (WWDG->CFGR & ~WWDG_CFGR_WDGTB) | prescaler;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the WWDG window value.
/// @param  WindowValue: specifies the window value to be compared to the
/// downcounter.
///          This parameter value must be lower than 0x80.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_SetWindowValue(u8 window_value)
{
    WWDG->CFGR = (WWDG->CFGR & ~WWDG_CFGR_WINDOW) | (window_value & WWDG_CFGR_WINDOW);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables the WWDG Early Wakeup interrupt(EWI).
/// @note   Once enabled this interrupt cannot be disabled except by a system
/// reset.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_EnableIT()
{
    WWDG->CFGR |= WWDG_CFGR_EWI;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the WWDG counter value.
/// @param  Counter: specifies the watchdog counter value.
///         This parameter must be a number between 0x40 and 0x7F (to prevent
///         generating an immediate reset).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_SetCounter(u8 count)
{
    WWDG->CR = count & WWDG_CFGR_WINDOW;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables WWDG and load the counter value.
/// @param  Counter: specifies the watchdog counter value.
///         This parameter must be a number between 0x40 and 0x7F (to prevent
///         generating an immediate reset).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
u32 WWDG_GetCounter()
{
    return WWDG->CR & WWDG_CR_CNT;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables WWDG and load the counter value.
/// @param  Counter: specifies the watchdog counter value.
///         This parameter must be a number between 0x40 and 0x7F (to prevent
///         generating an immediate reset).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_Enable(u8 count)
{
    WWDG->CR = WWDG_CR_WDGA | count;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the Early Wakeup interrupt flag is set or not.
/// @param  None.
/// @retval The new state of the Early Wakeup interrupt flag (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus WWDG_GetFlagStatus()
{
    return WWDG->SR ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears Early Wakeup interrupt flag.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void WWDG_ClearFlag()
{
    WWDG->SR &= ~WWDG_SR_EWIF;
}

/// @}

/// @}

/// @}
