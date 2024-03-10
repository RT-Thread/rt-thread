/**********************************************************************
* $Id$      lpc_dac.c           2011-06-02
*//**
* @file     lpc_dac.c
* @brief    Contains all functions support for DAC firmware library on
*           LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup DAC
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _DAC

/* Includes ------------------------------------------------------------------- */
#include "lpc_dac.h"
#include "lpc_clkpwr.h"
#include "lpc_pinsel.h"

/* Private Functions ---------------------------------------------------------- */

/*********************************************************************//**
 * @brief       Get pointer to DAC peripheral
 * @param[in]   compId      Component ID, normally is zero (0).
 * @param[in]   pinnum      Pin number value, should be in range from 0..31
 * @return      Pointer to DAC peripheral component
 **********************************************************************/
static LPC_DAC_TypeDef * DAC_GetPointer(uint8_t compId)
{
    LPC_DAC_TypeDef *pComponent = LPC_DAC;

    return pComponent;
}



/* Public Functions ----------------------------------------------------------- */
/** @addtogroup DAC_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief       Initial ADC configuration
 *                  - Maximum   current is 700 uA
 *                  - Value to AOUT is 0
 * @param[in]   DAC_Id  the ID of the DAC component that is using, should be: zero (0)
 * @return      None
 ***********************************************************************/
void DAC_Init(uint8_t DAC_Id)
{
    /*
     * Init DAC pin connect
     * AOUT on P0.26
     */
    PINSEL_ConfigPin(0, 26, 2);                              

    PINSEL_SetAnalogPinMode(0,26,ENABLE);

    //Enable DAC for the pin
    PINSEL_DacEnable(0, 26, ENABLE);

    //Set maximum current output as default
    DAC_SetBias(DAC_Id, DAC_MAX_CURRENT_700uA);
}

/*********************************************************************//**
 * @brief       Update value to DAC
 * @param[in]   DAC_Id  the ID of the DAC component that is using, should be: zero (0)
 * @param[in]   dac_value : value 10 bit to be converted to output
 * @return      None
 ***********************************************************************/
void DAC_UpdateValue (uint8_t DAC_Id,uint32_t dac_value)
{
    uint32_t tmp;

    LPC_DAC_TypeDef* pDac = DAC_GetPointer(DAC_Id);

    tmp = pDac->CR & DAC_BIAS_EN;

    tmp |= DAC_VALUE(dac_value);

    // Update value
    pDac->CR = tmp;
}

/*********************************************************************//**
 * @brief       Set Maximum current for DAC
 * @param[in]   DAC_Id  the ID of the DAC component that is using, should be: zero (0)
 * @param[in]   bias : 0 is 700 uA
 *                     1    350 uA
 * @return      None
 ***********************************************************************/
void DAC_SetBias (uint8_t DAC_Id, uint32_t bias)
{
    LPC_DAC_TypeDef* pDac = DAC_GetPointer(DAC_Id);

    pDac->CR &=~DAC_BIAS_EN;

    if (bias  == DAC_MAX_CURRENT_350uA)
    {
        pDac->CR |= DAC_BIAS_EN;
    }
}

/*********************************************************************//**
 * @brief       To enable the DMA operation and control DMA timer
 * @param[in]   DAC_Id  the ID of the DAC component that is using, should be: zero (0)
 * @param[in]   DAC_ConverterConfigStruct pointer to DAC_CONVERTER_CFG_Type
 *                  - DBLBUF_ENA :  enable/disable DACR double buffering feature
 *                  - CNT_ENA    :  enable/disable timer out counter
 *                  - DMA_ENA    :  enable/disable DMA access
 * @return      None
 ***********************************************************************/
void DAC_ConfigDAConverterControl (uint8_t DAC_Id, DAC_CONVERTER_CFG_Type *DAC_ConverterConfigStruct)
{
    LPC_DAC_TypeDef* pDac = DAC_GetPointer(DAC_Id);

    pDac->CTRL &= ~DAC_DACCTRL_MASK;

    if (DAC_ConverterConfigStruct->DBLBUF_ENA)
        pDac->CTRL  |= DAC_DBLBUF_ENA;

    if (DAC_ConverterConfigStruct->CNT_ENA)
        pDac->CTRL  |= DAC_CNT_ENA;

    if (DAC_ConverterConfigStruct->DMA_ENA)
        pDac->CTRL  |= DAC_DMA_ENA;
}

/*********************************************************************//**
 * @brief       Set reload value for interrupt/DMA counter
 * @param[in]   DAC_Id  the ID of the DAC component that is using, should be: zero (0)
 * @param[in]   time_out time out to reload for interrupt/DMA counter
 * @return      None
 ***********************************************************************/
void DAC_SetDMATimeOut(uint8_t DAC_Id, uint32_t time_out)
{
    LPC_DAC_TypeDef* pDac = DAC_GetPointer(DAC_Id);

    pDac->CNTVAL = DAC_CCNT_VALUE(time_out);
}


/*********************************************************************//**
 * @brief       Check the interrupt/DMA counter is occured or not because of the timer counter
 * @param[in]   DAC_Id  the ID of the DAC component that is using, should be: zero (0)
 * @return      None
 ***********************************************************************/
uint8_t DAC_IsIntRequested(uint8_t DAC_Id)
{
    LPC_DAC_TypeDef* pDac = DAC_GetPointer(DAC_Id);

    //Return the INT_DMA_REQ bit of D/A control register
    return (pDac->CTRL & 0x01);
}


/**
 * @}
 */
#endif /*_DAC*/

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
