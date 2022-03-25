/**
  ******************************************************************************
  * @file               FT32f0xx_div.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the dividor peripheral
  *                     applicable only on FT32F072xB devices:
  *                     + Comparators configuration
  *                     + Window mode control
  * @version            V1.0.0
  * @data               2021-12-01
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_div.h"

/**
  * @brief  Enable or disable the OPA peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPA_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg NOPA_Selection_OPA: OPA1 selected
  *            @arg POPA_Selection_OPA: OPA2 selected
  * @param  NewState: new state of the OPA peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the
  *         output level is low.
  * @retval None
  */
DIV_Status DivS32ByS16(DIV_ResultTypeDef* pResult,int32_t divedent,int16_t dividor)
{
    DIV_Status status = DIV_COMPLETE;
    DIV->DID = divedent;
    DIV->DIS = dividor;
    while(DIV_GetFlagStatus(DIV_FLAG_BUSY) == SET);
    if(DIV_GetFlagStatus(DIV_FLAG_DIV0ERR) == SET)
    {
        status = DIV_ERROR_DIV0ERR;
    }
    else if(DIV_GetFlagStatus(DIV_FLAG_DIVOV) == SET)
    {
        status = DIV_ERROR_DIV0V;
    }
    else
    {
        pResult -> DIV_quotient = DIV-> QUO;
        pResult -> DIV_remainder = DIV-> REM;
    }
    return status;
}

/** @defgroup DIV Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the DIV Interrupts
         and get the status and clear flags and Interrupts pending bits.

  *** Flags for DIV status ***
  ======================================================
    [..]
        (+)Flags :
           (##) DIV_FLAG_DIV0ERR : This flag is set after the ADC has been enabled (bit ADEN=1)
               and when the ADC reaches a state where it is ready to accept conversion requests
           (##) DIV_FLAG_DIVOV : This flag is set by software to enable the ADC.
                The DIV will be effectively ready to operate once the ADRDY flag has been set.
           (##) DIV_FLAG_BUSY : This flag is cleared once the ADC is effectively
                disabled.
        (+)Interrupts
           (##) DIV_IT_DIV0ERR : specifies the interrupt source for ADC ready event.
           (##) DIV_IT_DIVOV :   specifies the interrupt source for ADC ready event.

    [..] The user should identify which mode will be used in his application to
         manage the ADC controller events: Polling mode or Interrupt mode.

    [..] In the Polling Mode it is advised to use the following functions:
         (+) DIV_GetFlagStatus() : to check if flags events occur.
         (+) DIV_ClearFlag()     : to clear the flags events.

    [..] In the Interrupt Mode it is advised to use the following functions:
         (+) DIV_ITConfig()       : to enable or disable the interrupt source.
         (+) DIV_GetITStatus()    : to check if Interrupt occurs.
         (+) DIV_ClearITPendingBit() : to clear the Interrupt pending Bit
             (corresponding Flag).

@endverbatim
  * @{
  */
/**
  * @brief  Enables or disables the specified DIV interrupts.
  * @param  DIV_IT: specifies the DIV interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg DIV_IT_DIV0ERR: Divide By Zero Exception
  *            @arg DIV_IT_DIVOV: Overflow interrupt
  * @param  NewState: new state of the specified DIV interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DIV_ITConfig(uint32_t DIV_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_DIV_CONFIG_IT(DIV_IT));

    if (NewState != DISABLE)
    {
        /* Enable the selected DIV interrupts */
        DIV->SC |= DIV_IT;
    }
    else
    {
        /* Disable the selected DIV interrupts */
        DIV->SC &= (~(uint32_t)DIV_IT);
    }
}

/**
  * @brief  Checks whether the specified DIV flag is set or not.
  * @param  DIV_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg DIV_FLAG_DIV0ERR: Divide By Zero Exception flag
  *            @arg DIV_FLAG_DIVOV: Overflow flag
  *            @arg DIV_FLAG_BUSY: Busy flag
  * @retval The new state of DIV_FLAG (SET or RESET).
  */
FlagStatus DIV_GetFlagStatus(uint32_t DIV_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_DIV_GET_FLAG(DIV_FLAG));

    /* Check the status of the specified DIV flag */
    if ((DIV->SC & DIV_FLAG) != (uint32_t)RESET)
    {
        /* DIV_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* DIV_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the DIV_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the DIV's pending flags.
  * @param  DIV_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DIV_FLAG_DIV0ERRC: Divide By Zero Exception flag
  *            @arg DIV_FLAG_DIVOVC: Overflow flag
  * @retval None
  */
void DIV_ClearFlag(uint32_t DIV_FLAG)
{
    /* Check the parameters */
    assert_param(IS_DIV_CLEAR_FLAG(DIV_FLAG));
    /* Clear the selected DIV flags */
    DIV->SC |= (uint32_t)(DIV_FLAG<<8);
}

/**
  * @brief  Checks whether the specified DIV interrupt has occurred or not.
  * @param  DIV_IT: specifies the DIV interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DIV_IT_DIV0ERR: Divide By Zero Exception
  *            @arg DIV_IT_DIVOV: Overflow interrupt
  * @retval The new state of DIV_IT (SET or RESET).
  */
ITStatus DIV_GetITStatus(uint32_t DIV_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_DIV_GET_IT(DIV_IT));

    /* Get the DIV_IT enable bit status */
    enablestatus = (uint32_t)((DIV->SC>>1) & DIV_IT);

    /* Check the status of the specified DIV interrupt */
    if (((uint32_t)(DIV->SC & DIV_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
    {
        /* DIV_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DIV_IT is reset */
        bitstatus = RESET;
    }
    /* Return the DIV_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the DIV's interrupt pending bits.
  * @param  DIV: where x can be 1 to select the DIV1 peripheral.
  * @param  DIV_IT: specifies the DIV interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg DIV_IT_DIV0ERR: Divide By Zero Exception
  *            @arg DIV_IT_DIVOV: Overflow interrupt
  * @retval None
  */
void DIV_ClearITPendingBit(uint32_t DIV_IT)
{
    /* Check the parameters */
    assert_param(IS_DIV_CLEAR_IT(DIV_IT));

    /* Clear the selected DIV interrupt pending bits */
    DIV->SC |= (uint32_t)(DIV_IT<<8);
}

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

