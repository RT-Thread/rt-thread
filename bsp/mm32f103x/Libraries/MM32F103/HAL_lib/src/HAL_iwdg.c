/**
******************************************************************************
* @file    HAL_iwdg.c
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file provides all the IWDG firmware functions.
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
#include "HAL_iwdg.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup IWDG
* @brief IWDG driver modules
* @{
*/

/** @defgroup IWDG_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup IWDG_Private_Defines
* @{
*/

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KR register bit mask */
#define KR_KEY_Reload    ((uint16_t)0xAAAA)
#define KR_KEY_Enable    ((uint16_t)0xCCCC)

/**
* @}
*/

/** @defgroup IWDG_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup IWDG_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup IWDG_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup IWDG_Private_Functions
* @{
*/

/**
* @brief  Enables or disables write access to IWDG_PR and IWDG_RLR
*   registers.
* @param IWDG_WriteAccess: new state of write access to IWDG_PR and
*   IWDG_RLR registers.
*   This parameter can be one of the following values:
* @arg IWDG_WriteAccess_Enable: Enable write access to
*   IWDG_PR and IWDG_RLR registers
* @arg IWDG_WriteAccess_Disable: Disable write access to
*   IWDG_PR and IWDG_RLR registers
* @retval : None
*/
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
    /* Check the parameters */
    assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
    IWDG->KR = IWDG_WriteAccess;
}

/**
* @brief  Sets IWDG Prescaler value.
* @param IWDG_Prescaler: specifies the IWDG Prescaler value.
*   This parameter can be one of the following values:
* @arg IWDG_Prescaler_4: IWDG prescaler set to 4
* @arg IWDG_Prescaler_8: IWDG prescaler set to 8
* @arg IWDG_Prescaler_16: IWDG prescaler set to 16
* @arg IWDG_Prescaler_32: IWDG prescaler set to 32
* @arg IWDG_Prescaler_64: IWDG prescaler set to 64
* @arg IWDG_Prescaler_128: IWDG prescaler set to 128
* @arg IWDG_Prescaler_256: IWDG prescaler set to 256
* @retval : None
*/
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
    /* Check the parameters */
    assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
    IWDG->PR = IWDG_Prescaler;
}

/**
* @brief  Sets IWDG Reload value.
* @param Reload: specifies the IWDG Reload value.
*   This parameter must be a number between 0 and 0x0FFF.
* @retval : None
*/
void IWDG_SetReload(uint16_t Reload)
{
    /* Check the parameters */
    assert_param(IS_IWDG_RELOAD(Reload));
    IWDG->RLR = Reload;
}

/**
* @brief  Reloads IWDG counter with value defined in the reload register
*   (write access to IWDG_PR and IWDG_RLR registers disabled).
* @param  None
* @retval : None
*/
void IWDG_ReloadCounter(void)
{
    IWDG->KR = KR_KEY_Reload;
}

/**
* @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers
*   disabled).
* @param  None
* @retval : None
*/
void IWDG_Enable(void)
{
    IWDG->KR = KR_KEY_Enable;
}

/**
* @brief  Checks whether the specified IWDG flag is set or not.
* @param IWDG_FLAG: specifies the flag to check.
*   This parameter can be one of the following values:
* @arg IWDG_FLAG_PVU: Prescaler Value Update on going
* @arg IWDG_FLAG_RVU: Reload Value Update on going
* @retval : The new state of IWDG_FLAG (SET or RESET).
*/
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_IWDG_FLAG(IWDG_FLAG));
    if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET)
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
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
