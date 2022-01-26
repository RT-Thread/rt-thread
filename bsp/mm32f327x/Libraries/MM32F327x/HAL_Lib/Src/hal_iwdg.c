////////////////////////////////////////////////////////////////////////////////
/// @file     hal_iwdg.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE IWDG FIRMWARE FUNCTIONS.
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
#define _HAL_IWDG_C_

// Files includes
#include "hal_iwdg.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup IWDG_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup IWDG_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables write access to IWDG_PR and IWDG_RLR
///   registers.
/// @param  write_access: new state of write access to IWDG_PR and
///   IWDG_RLR registers.
///   This parameter can be one of the following values:
/// @arg IWDG_WriteAccess_Enable: Enable write access to
///   IWDG_PR and IWDG_RLR registers
/// @arg IWDG_WriteAccess_Disable: Disable write access to
///   IWDG_PR and IWDG_RLR registers
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_WriteAccessCmd(u16 write_access)
{
    IWDG->KR = write_access;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets IWDG Prescaler value.
/// @param  prescaler: specifies the IWDG Prescaler value.
///         This parameter can be one of the following values:
/// @arg    IWDG_Prescaler_4: IWDG prescaler set to 4
/// @arg    IWDG_Prescaler_8: IWDG prescaler set to 8
/// @arg    IWDG_Prescaler_16: IWDG prescaler set to 16
/// @arg    IWDG_Prescaler_32: IWDG prescaler set to 32
/// @arg    IWDG_Prescaler_64: IWDG prescaler set to 64
/// @arg    IWDG_Prescaler_128: IWDG prescaler set to 128
/// @arg    IWDG_Prescaler_256: IWDG prescaler set to 256
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_SetPrescaler(u8 prescaler)
{
    IWDG->PR = prescaler;
    PVU_CheckStatus();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set IWDG reload value.
/// @param  reload: specifies the IWDG reload value.
///         This parameter must be a number between 0 and 0x0FFF.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_SetReload(u16 reload)
{
    IWDG->RLR = reload;
    RVU_CheckStatus();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Get IWDG reload value.
/// @param  None.
/// @retval reload: specifies the IWDG reload value.
////////////////////////////////////////////////////////////////////////////////
u32 IWDG_GetReload(void)
{
    return IWDG->RLR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reloads IWDG counter with value defined in the reload register
///   (write access to IWDG_PR and IWDG_RLR registers disabled).
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_ReloadCounter(void)
{
    IWDG->KR = KR_KEY_Reload;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers
///         disabled).
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_Enable(void)
{
    IWDG->KR = KR_KEY_Enable;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified IWDG flag is set or not.
/// @param  flag: specifies the flag to check.
///   This parameter can be one of the following values:
/// @arg    IWDG_FLAG_PVU: Prescaler Value Update on going
/// @arg    IWDG_FLAG_RVU: reload Value Update on going
/// @retval The new state of flag (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus IWDG_GetFlagStatus(u16 flag)
{
    return ((IWDG->SR & flag) != (u32)RESET) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks prescaler value has been updated.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void PVU_CheckStatus(void)
{
    while (IWDG_GetFlagStatus(IWDG_FLAG_PVU) == SET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks count relead value has been updated.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RVU_CheckStatus(void)
{
    while (IWDG_GetFlagStatus(IWDG_FLAG_RVU) == SET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  IWDG overflow configuration.
/// @param  overflow_config
/// @arg    IWDG_Overflow_Interrupt: Interrupt after overflow.
/// @arg    IWDG_Overflow_Reset:     Reset after overflow.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_OverflowConfig(IWDGOverflowConfig_TypeDef overflow_config)
{
    IWDG->CR &= ~IWDG_CR_IRQSEL;
    IWDG->CR |= overflow_config;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clear interrupt flag
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_ClearITPendingBit(void)
{
    IWDG->CR |= IWDG_CR_IRQCLR;//write 1 clear interrupt Flag
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clear interrupt flag
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_ClearIT(void)
{
    IWDG->CR |= IWDG_CR_IRQCLR;//write 1 clear interrupt Flag
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable IWDG interrupt function
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_EnableIT(void)
{
    IWDG->CR |= IWDG_CR_IRQSEL;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Disable IWDG interrupt function
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void IWDG_Reset(void)
{
    IWDG->CR &= ~IWDG_CR_IRQSEL;
}



/// @}

/// @}

/// @}
