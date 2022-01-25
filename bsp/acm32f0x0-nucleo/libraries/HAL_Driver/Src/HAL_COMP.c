/*
  ******************************************************************************
  * @file    HAL_COMP.c
  * @version V1.0.0
  * @date    2020
  * @brief   COMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Comparator Peripheral (COMP).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/************************************************************************
 * function   : HAL_COMP_MspInit
 * Description: Inition the comparator gpio and clock
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 * output     : none
 ************************************************************************/
__weak void HAL_COMP_MspInit(COMP_HandleTypeDef* hcomp)
{
    /*
      NOTE : This function should be modified by the user.
    */

    /* For Example */
    GPIO_InitTypeDef GPIO_Handle;

    System_Module_Enable(EN_COMP);

    if(hcomp->Init.Comparator == COMP1 )
    {
        /* COMP1 GPIO inition VINP:PA5(INP_0)*/
        /* COMP1 GPIO inition VINM:PA4(INM_0)*/
        /* COMP1 GPIO inition VOUT:PA0(FUNCTION_7)*/
        GPIO_Handle.Pin            = GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
        GPIO_Handle.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_Handle);

        GPIO_Handle.Pin            = GPIO_PIN_0;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_7;
        GPIO_Handle.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_Handle);
    }
    else if(hcomp->Init.Comparator == COMP2 )
    {
        /* COMP2 GPIO inition VINP:PB4(INP_1)*/
        /* COMP2 GPIO inition VOUT:PA2(FUNCTION_7)*/
        GPIO_Handle.Pin            = GPIO_PIN_4;
        GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
        GPIO_Handle.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_Handle);

        GPIO_Handle.Pin            = GPIO_PIN_2;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_7;
        GPIO_Handle.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_Handle);
    }
}

/************************************************************************
 * function   : HAL_COMP_MspDeInit
 * Description: De-Inition the comparator gpio and clock
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 * output     : none
 ************************************************************************/
__weak void HAL_COMP_MspDeInit(COMP_HandleTypeDef* hcomp)
{
    /*
      NOTE : This function should be modified by the user.
    */

    /* For Example */
    System_Module_Reset(RST_COMP);
    System_Module_Enable(EN_COMP);
}

/************************************************************************
 * function   : HAL_COMP_Init
 * Description: Inition the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef* hcomp)
{
    uint32_t u32RegTemp;
    __IO uint32_t *gu32RegCrx;

    /* Check the COMP handle allocation */
    if (hcomp == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_COMP_ALL_INSTANCE(hcomp->Instance)) return HAL_ERROR;
    if(!IS_COMP_ALL_COMP(hcomp->Init.Comparator)) return HAL_ERROR;
    if(!IS_COMP_ALL_CRV_EN(hcomp->Init.Crv_En)) return HAL_ERROR;
    if(!IS_COMP_ALL_CRV_SEL(hcomp->Init.Crv_Sel)) return HAL_ERROR;
    if(!IS_COMP_ALL_CRV_CFG(hcomp->Init.Crv_Cfg)) return HAL_ERROR;
    if(!IS_COMP_ALL_WINMODE(hcomp->Init.WinMode)) return HAL_ERROR;
    if(!IS_COMP_ALL_WINOUT(hcomp->Init.WinOut)) return HAL_ERROR;
    if(!IS_COMP_ALL_POLARITY(hcomp->Init.Polarity)) return HAL_ERROR;
    if(!IS_COMP_ALL_FLTEN(hcomp->Init.FltEn)) return HAL_ERROR;
    if(!IS_COMP_ALL_FLTTIME(hcomp->Init.FltTime)) return HAL_ERROR;
    if(!IS_COMP_ALL_BLANKTIME(hcomp->Init.BlankTime)) return HAL_ERROR;
    if(!IS_COMP_ALL_BLANKSEL(hcomp->Init.BlankSel)) return HAL_ERROR;
    if(!IS_COMP_ALL_INPSEL(hcomp->Init.InPSel)) return HAL_ERROR;
    if(!IS_COMP_ALL_INMSEL(hcomp->Init.InMSel)) return HAL_ERROR;
    if(!IS_COMP_ALL_HYS(hcomp->Init.HYS)) return HAL_ERROR;

    /* Init the low level hardware : GPIO, CLOCK */
    HAL_COMP_MspInit(hcomp);

    if(hcomp->Init.Comparator == COMP1 )
        gu32RegCrx = &hcomp->Instance->CR1;
    else
        gu32RegCrx = &hcomp->Instance->CR2;

    //Check if the register is locked
    if(READ_BIT(*gu32RegCrx , COMP_CR_LOCK))
    {
        System_Module_Reset(RST_COMP);
    }

    //Check if the comparetor is enable
    if(READ_BIT(*gu32RegCrx , COMP_CR_EN))
        CLEAR_BIT(*gu32RegCrx , COMP_CR_EN);

    u32RegTemp = *gu32RegCrx ;

    u32RegTemp = u32RegTemp | ((hcomp->Init.Crv_Cfg << COMP_CR_CRV_CFG_POS)& COMP_CR_CRV_CFG_MASK) | \
                              ((hcomp->Init.Crv_Sel << 24) & COMP_CR_CRV_SEL) | \
                              ((hcomp->Init.Crv_En << 23) & COMP_CR_CRV_EN) | \
                              ((hcomp->Init.WinMode << 22) & COMP_CR_WINMODE) | \
                              ((hcomp->Init.WinOut << 21) & COMP_CR_WINOUT) | \
                              ((hcomp->Init.Polarity << 20) & COMP_CR_POLARITY) | \
                              ((hcomp->Init.FltEn << 19) & COMP_CR_FLTEN) | \
                              ((hcomp->Init.FltTime << COMP_CR_FLTTIME_POS)& COMP_CR_FLTTIME_MASK) | \
                              ((hcomp->Init.BlankTime << COMP_CR_BLANKTIME_POS)& COMP_CR_BLANKTIME_MASK) | \
                              ((hcomp->Init.BlankSel << COMP_CR_BLANKSEL_POS)& COMP_CR_BLANKSEL_MASK) | \
                              ((hcomp->Init.InPSel << COMP_CR_INPSEL_POS)& COMP_CR_INPSEL_MASK) | \
                              ((hcomp->Init.InMSel << COMP_CR_INMSEL_POS)& COMP_CR_INMSEL_MASK) | \
                              ((hcomp->Init.HYS << COMP_CR_HYS_POS)& COMP_CR_HYS_MASK);

    //Write the COMP_CR register .
    WRITE_REG(*gu32RegCrx,u32RegTemp);

    SET_BIT(*gu32RegCrx , COMP_CR_EN); //enable

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_COMP_Enable
 * Description: Enable the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_Enable(COMP_HandleTypeDef* hcomp)
{
    __IO uint32_t *gu32RegCrx;

    /* Check the COMP handle allocation */
    if (hcomp == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_COMP_ALL_INSTANCE(hcomp->Instance)) return HAL_ERROR;
    if(!IS_COMP_ALL_COMP(hcomp->Init.Comparator)) return HAL_ERROR;

    if(hcomp->Init.Comparator == COMP1 )
        gu32RegCrx = &hcomp->Instance->CR1;
    else
        gu32RegCrx = &hcomp->Instance->CR2;

    SET_BIT(*gu32RegCrx , COMP_CR_EN); //enable

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_COMP_DeInit
 * Description: Deinit and reset the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef* hcomp)
{
    /* Check the COMP handle allocation */
    if (hcomp == NULL)
    {
        return HAL_ERROR;
    }

    HAL_COMP_MspDeInit(hcomp);

    memset(&hcomp->Init, 0, sizeof(hcomp->Init));
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_COMP_Disable
 * Description: Disable the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_Disable(COMP_HandleTypeDef* hcomp)
{
    __IO uint32_t *gu32RegCrx;

    /* Check the COMP handle allocation */
    if (hcomp == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_COMP_ALL_INSTANCE(hcomp->Instance)) return HAL_ERROR;
    if(!IS_COMP_ALL_COMP(hcomp->Init.Comparator)) return HAL_ERROR;

    if(hcomp->Init.Comparator == COMP1 )
        gu32RegCrx = &hcomp->Instance->CR1;
    else
        gu32RegCrx = &hcomp->Instance->CR2;

    CLEAR_BIT(*gu32RegCrx , COMP_CR_EN); //disable

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_COMP_GetOutputLevel
 * Description: Get the output level of the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_GetOutputLevel(COMP_HandleTypeDef* hcomp)
{
    uint32_t u32RegTemp;
    /* Check the parameters */
    if(!IS_COMP_ALL_INSTANCE(hcomp->Instance)) return HAL_ERROR;
    if(!IS_COMP_ALL_COMP(hcomp->Init.Comparator)) return HAL_ERROR;

    u32RegTemp = READ_REG(hcomp->Instance->SR);

    if(hcomp->Init.Comparator == COMP1 )
    {
        hcomp->OutputLevel_Org = (u32RegTemp & COMP_SR_VCOUT1_ORG)? 1:0;
        hcomp->OutputLevel = (u32RegTemp & COMP_SR_VCOUT1)? 1:0;
    }
    else
    {
        hcomp->OutputLevel_Org = (u32RegTemp & COMP_SR_VCOUT2_ORG)? 1:0;
        hcomp->OutputLevel = (u32RegTemp & COMP_SR_VCOUT2)? 1:0;
    }

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_COMP_Lock
 * Description: Lock the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef* hcomp)
{
    __IO uint32_t *gu32RegCrx;

    /* Check the COMP handle allocation */
    if (hcomp == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_COMP_ALL_INSTANCE(hcomp->Instance)) return HAL_ERROR;
    if(!IS_COMP_ALL_COMP(hcomp->Init.Comparator)) return HAL_ERROR;

    if(hcomp->Init.Comparator == COMP1 )
        gu32RegCrx = &hcomp->Instance->CR1;
    else
        gu32RegCrx = &hcomp->Instance->CR2;

    SET_BIT(*gu32RegCrx , COMP_CR_LOCK); //lock
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_COMP_Start
 * Description: Start the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp)
{
    return(HAL_COMP_Enable(hcomp));
}


/************************************************************************
 * function   : HAL_COMP_Stop
 * Description: Stop the comparator
 * input      : COMP_HandleTypeDef* hcomp: pointer to comparator structure.
 ************************************************************************/
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp)
{
    return(HAL_COMP_Disable(hcomp));
}
