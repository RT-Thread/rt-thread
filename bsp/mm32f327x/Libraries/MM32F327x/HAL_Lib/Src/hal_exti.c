////////////////////////////////////////////////////////////////////////////////
/// @file     hal_exti.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE EXTI FIRMWARE FUNCTIONS.
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
#define _HAL_EXTI_C_

// Files includes
#include "hal_exti.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup EXTI_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup EXTI_Exported_Functions
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the EXTI peripheral registers to their default reset
///         values.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the EXTI registers to their default reset values.
/// @param  None.
/// @retval None.
/// @note   MEM_MODE bits are not affected by APB reset.
/// @note   MEM_MODE bits took the value from the user option bytes.
/// @note   CFGR2 register is not affected by APB reset.
/// @note   CLABBB configuration bits are locked when set.
/// @note   To unlock the configuration, perform a system reset.
////////////////////////////////////////////////////////////////////////////////
void EXTI_DeInit(void)
{
    u16 i;
    // Clear all
    exEXTI_LineDisable(~0x00000000);

    // rc_w1
    EXTI->PR = EXTI->PR;

    // Set EXTI_CFGR1 register to reset value without affecting MEM_MODE bits
    EXTI->CFGR &= EXTI_CFGR_MEMMODE;

    // Set EXTICRx registers to reset value
    for (i = 0; i < 4; i++) {
        EXTI->CR[i] = 0;
    }
}



////////////////////////////////////////////////////////////////////////////////
/// @brief  Selects the GPIO pin used as EXTI Line.
/// @param  port_source_gpio: selects the GPIO port to be used as source for EXTI lines .
/// @param  pin_source: specifies the EXTI line to be configured.
/// @note   This parameter can be pin_source where x can be:
///         For MCU: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOD.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_LineConfig(u8 port_source_gpio, u8 pin_source)
{
    EXTI->CR[pin_source >> 0x02] &= ~(0x0F << (0x04 * (pin_source & 0x03)));
    EXTI->CR[pin_source >> 0x02] |= ((port_source_gpio) << (0x04 * (pin_source & 0x03)));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the EXTI peripheral according to the specified
///         parameters in the init_struct.
/// @param  init_struct: pointer to a EXTI_InitTypeDef structure that
///         contains the configuration information for the EXTI peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_Init(EXTI_InitTypeDef* init_struct)
{
    if (init_struct->EXTI_LineCmd != DISABLE) {
        EXTI->IMR  &= ~init_struct->EXTI_Line;
        EXTI->EMR  &= ~init_struct->EXTI_Line;
        if (init_struct->EXTI_Mode == EXTI_Mode_Interrupt) {
            EXTI->IMR |= init_struct->EXTI_Line;
        }
        else {
            EXTI->EMR |= init_struct->EXTI_Line;
        }
        EXTI->RTSR &= ~init_struct->EXTI_Line;
        EXTI->FTSR &= ~init_struct->EXTI_Line;
        if (init_struct->EXTI_Trigger == EXTI_Trigger_Rising_Falling) {
            EXTI->RTSR |= init_struct->EXTI_Line;
            EXTI->FTSR |= init_struct->EXTI_Line;                               // Rising and Faling    afio
        }
        else if (init_struct->EXTI_Trigger == EXTI_Trigger_Rising) {
            EXTI->RTSR |= init_struct->EXTI_Line;
        }
        else {
            EXTI->FTSR |= init_struct->EXTI_Line;
        }
    }
    else {
        if (init_struct->EXTI_Mode == EXTI_Mode_Interrupt) {
            EXTI->IMR &= ~init_struct->EXTI_Line;
        }
        else {
            EXTI->EMR &= ~init_struct->EXTI_Line;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its reset value.
/// @param  init_struct: pointer to a EXTI_InitTypeDef structure which will
///         be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_StructInit(EXTI_InitTypeDef* init_struct)
{
    init_struct->EXTI_Line    = EXTI_LineNone;
    init_struct->EXTI_Mode    = EXTI_Mode_Interrupt;
    init_struct->EXTI_Trigger = EXTI_Trigger_Falling;
    init_struct->EXTI_LineCmd = DISABLE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates a Software interrupt on selected EXTI line.
/// @param  line: specifies the EXTI line on which the software interrupt
///         will be generated.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_GenerateSWInterrupt(u32 line)
{
    EXTI->SWIER |= line;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified EXTI line flag is set or not.
/// @param  line: specifies the EXTI line flag to check.
/// @retval The new state of line (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus EXTI_GetFlagStatus(u32 line)
{
    return (EXTI->PR & line) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the EXTI's line pending flags.
/// @param  line: specifies the EXTI lines flags to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_ClearFlag(u32 line)
{
    EXTI->PR = line;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified EXTI line is asserted or not.
/// @param  line: specifies the EXTI line to check.
/// @retval The new state of line (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus EXTI_GetITStatus(u32 line)
{
    return ((EXTI->PR & line) && (EXTI->IMR & line)) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the EXTI's line pending bits.
/// @param  line: specifies the EXTI lines to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_ClearITPendingBit(u32 line)
{
    EXTI->PR = line;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  EXTI Line Disable
/// @param  line: specifies the EXTI lines to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exEXTI_LineDisable(u32 line)
{
    EXTI->IMR  &= ~line;
    EXTI->EMR  &= ~line;
    EXTI->RTSR &= ~line;
    EXTI->FTSR &= ~line;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the EXTI's line all pending bits.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
u32 exEXTI_GetAllFlagStatus(void)
{
    return EXTI->PR;
}

/// @}

/// @}

/// @}

