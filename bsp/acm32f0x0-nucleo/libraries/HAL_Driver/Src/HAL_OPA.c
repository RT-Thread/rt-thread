/*
  ******************************************************************************
  * @file    HAL_OPA.c
  * @version V1.0.0
  * @date    2020
  * @brief   OPA HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Operational Amplifier (OPA).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/************************************************************************
 * function   : HAL_OPA_MspInit
 * Description: OPA MCU specific initiation, such as IO share, module clock, ...
 * input      :
 *         OPA_HandleTypeDef *hopa: pointer to opa handle structure
 * return: none
************************************************************************/
__weak void HAL_OPA_MspInit(OPA_HandleTypeDef* hopa)
{
    /*
      NOTE : This function should be modified by the user.
    */

    /* For Example */
    GPIO_InitTypeDef GPIO_OPA;

    /* Enable Clock */
    System_Module_Enable(EN_OPA);

    if(hopa->Init.OpaX == OPA1)
    {
        /* OPA1 GPIO inition VINP:PB6*/
        /* OPA1 GPIO inition VINM:PB5*/
        /* OPA1 GPIO inition OPA1_VOUT:PC5*/
        GPIO_OPA.Pin            = GPIO_PIN_5 | GPIO_PIN_6;
        GPIO_OPA.Mode           = GPIO_MODE_ANALOG;
        GPIO_OPA.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_OPA);

        GPIO_OPA.Pin            = GPIO_PIN_5;
        GPIO_OPA.Mode           = GPIO_MODE_ANALOG;
        GPIO_OPA.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOC, &GPIO_OPA);
    }

    else if(hopa->Init.OpaX == OPA2)
    {
        /* OPA2 GPIO inition VINP:PB3*/
        /* OPA2 GPIO inition VINM:PB1*/
        /* OPA2 GPIO inition OPA2_VOUT:PB0*/
        GPIO_OPA.Pin            = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3;
        GPIO_OPA.Mode           = GPIO_MODE_ANALOG;
        GPIO_OPA.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_OPA);
    }
    else if(hopa->Init.OpaX == OPA3)
    {
        /* OPA3 GPIO inition VINP:PA7*/
        /* OPA3 GPIO inition VINM:PA5*/
        /* OPA3 GPIO inition OPA2_VOUT:PA6*/
        GPIO_OPA.Pin            = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_OPA.Mode           = GPIO_MODE_ANALOG;
        GPIO_OPA.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_OPA);
    }
}

/************************************************************************
 * function   : HAL_OPA_MspDeInit
 * Description: OPA MCU De-initiation, such as IO share, module clock, ...
 * input      :
 *         OPA_HandleTypeDef *hopa: pointer to opa handle structure
 * return: none
************************************************************************/
__weak void HAL_OPA_MspDeInit(OPA_HandleTypeDef* hopa)
{
    /*
      NOTE : This function should be modified by the user.
    */

    /* For Example */

    /* Reset the OPA */
    System_Module_Reset(RST_OPA);
    /* Disable Clock */
    System_Module_Disable(EN_OPA);

}

/************************************************************************
 * function   : HAL_OPA_Init
 * Description: opa initial with parameters.
 * input :
 *         OPA_HandleTypeDef *hopa: pointer to opa handle structure
 ************************************************************************/
HAL_StatusTypeDef HAL_OPA_Init(OPA_HandleTypeDef* hopa)
{
    __IO uint32_t *gu32RegCrx;
    uint8_t trim_value;
    uint32_t u32NvrTrimValue;

    /* Check the OPA handle allocation */
    if (hopa == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_OPA_ALL_INSTANCE(hopa->Instance)) return HAL_ERROR;
    if(!IS_OPA_ALL_OPAX(hopa->Init.OpaX)) return HAL_ERROR;
    if(!IS_OPA_ALL_VINP(hopa->Init.VinPSel)) return HAL_ERROR;
    if(!IS_OPA_ALL_VINM(hopa->Init.VinMSel)) return HAL_ERROR;
    if(!IS_OPA_ALL_TRIM(hopa->Init.TrimEn)) return HAL_ERROR;

    if(hopa->Init.OpaX == OPA1)
        gu32RegCrx = &hopa->Instance->OPA1_CSR;
    else if(hopa->Init.OpaX == OPA2)
        gu32RegCrx = &hopa->Instance->OPA2_CSR;
    else if(hopa->Init.OpaX == OPA3)
        gu32RegCrx = &hopa->Instance->OPA3_CSR;

    /* Init the low level hardware : GPIO, CLOCK */
    HAL_OPA_MspInit(hopa);

    /* Select the Vin P */
    MODIFY_REG(*gu32RegCrx, OPA_CSR_VINPSEL_MASK, (hopa->Init.VinPSel)<<OPA_CSR_VINPSEL_POS);
    /* Select the Vin M */
    MODIFY_REG(*gu32RegCrx, OPA_CSR_VINMSEL_MASK, (hopa->Init.VinMSel)<<OPA_CSR_VINMSEL_POS);

    /* Enable the opa */
    SET_BIT(*gu32RegCrx, OPA_CSR_EN);

    /* Trim the opa */
    if(hopa->Init.TrimEn == OPA_CSR_TRIM_ENABLE)
    {
        /* Trim the OPA_CSR_CAL_H N channel */
        SET_BIT(*gu32RegCrx, OPA_CSR_CAL_H);
        CLEAR_BIT(*gu32RegCrx, OPA_CSR_CAL_L);

        for(trim_value=0;trim_value<32;trim_value++)
        {
            MODIFY_REG(*gu32RegCrx,OPA_CSR_TRIM_HIGH_MASK,(trim_value)<<OPA_CSR_TRIM_HIGH_POS);
            System_Delay(1000);
            if(READ_BIT(*gu32RegCrx,OPA_CSR_CAL_OUT)) break;
        }
        /* Trim the OPA_CSR_CAL_L P channel */
        SET_BIT(*gu32RegCrx, OPA_CSR_CAL_L);
        CLEAR_BIT(*gu32RegCrx, OPA_CSR_CAL_H);

        for(trim_value=0;trim_value<32;trim_value++)
        {
            MODIFY_REG(*gu32RegCrx,OPA_CSR_TRIM_LOW_MASK,(trim_value)<<OPA_CSR_TRIM_LOW_POS);
            System_Delay(1000);
            if(READ_BIT(*gu32RegCrx,OPA_CSR_CAL_OUT)) break;
        }
    }
    else
    {
        /* Use the Trim value */
        u32NvrTrimValue = *(volatile uint32_t*)(0x0008024C+(hopa->Init.OpaX-1)*4); //Read the OPA trim value;
        if(((~(u32NvrTrimValue>>16))&0xFFFF) != (u32NvrTrimValue&0xFFFF)) return HAL_ERROR;

        u32NvrTrimValue = u32NvrTrimValue & 0xFFFF;

        MODIFY_REG(*gu32RegCrx,OPA_CSR_TRIM_HIGH_MASK,((u32NvrTrimValue&0x1F)<<OPA_CSR_TRIM_HIGH_POS));

        MODIFY_REG(*gu32RegCrx,OPA_CSR_TRIM_LOW_MASK,(((u32NvrTrimValue>>5)&0x1F)<<OPA_CSR_TRIM_LOW_POS));

        System_Delay(1000);
    }

    /* After rim enable the opa*/
    SET_BIT(*gu32RegCrx, OPA_CSR_CAL_L);
    SET_BIT(*gu32RegCrx, OPA_CSR_CAL_H);

    return  HAL_OK;
}

/************************************************************************
 * function   : HAL_OPA_Enable
 * Description: opa enable.
 * input :
 *         OPA_HandleTypeDef *hopa: pointer to opa handle structure
 ************************************************************************/
HAL_StatusTypeDef HAL_OPA_Enable(OPA_HandleTypeDef* hopa)
{
    __IO uint32_t *gu32RegCrx;

    /* Check the OPA handle allocation */
    if (hopa == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_OPA_ALL_INSTANCE(hopa->Instance)) return HAL_ERROR;
    if(!IS_OPA_ALL_OPAX(hopa->Init.OpaX)) return HAL_ERROR;

    if(hopa->Init.OpaX == OPA1)
        gu32RegCrx = &hopa->Instance->OPA1_CSR;
    else if(hopa->Init.OpaX == OPA2)
        gu32RegCrx = &hopa->Instance->OPA2_CSR;
    else if(hopa->Init.OpaX == OPA3)
        gu32RegCrx = &hopa->Instance->OPA3_CSR;

    /* Enable the opa */
    SET_BIT(*gu32RegCrx, OPA_CSR_EN);

    return HAL_OK;
}
/************************************************************************
 * function   : HAL_OPA_Disable
 * Description: opa disable.
 * input :
 *         OPA_HandleTypeDef *hopa: pointer to opa handle structure
 ************************************************************************/
HAL_StatusTypeDef HAL_OPA_Disable(OPA_HandleTypeDef* hopa)
{
    __IO uint32_t *gu32RegCrx;

    /* Check the OPA handle allocation */
    if (hopa == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_OPA_ALL_INSTANCE(hopa->Instance)) return HAL_ERROR;
    if(!IS_OPA_ALL_OPAX(hopa->Init.OpaX)) return HAL_ERROR;

    if(hopa->Init.OpaX == OPA1)
        gu32RegCrx = &hopa->Instance->OPA1_CSR;
    else if(hopa->Init.OpaX == OPA2)
        gu32RegCrx = &hopa->Instance->OPA2_CSR;
    else if(hopa->Init.OpaX == OPA3)
        gu32RegCrx = &hopa->Instance->OPA3_CSR;

    /* Disable the opa */
    CLEAR_BIT(*gu32RegCrx, OPA_CSR_EN);

    return HAL_OK;
}
