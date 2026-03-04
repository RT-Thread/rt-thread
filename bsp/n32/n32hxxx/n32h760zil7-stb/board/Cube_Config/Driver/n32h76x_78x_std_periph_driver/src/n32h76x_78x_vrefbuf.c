/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_vrefbuf.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_vrefbuf.h"

/** VREFBUF Driving Functions Declaration **/

/**
*\*\name    VREFBUF_SetVoltageScale.
*\*\fun     Set the Voltage reference scale.
*\*\param   Scale
*\*\          - VREFBUF_VOLTAGE_SCALE_2_5V
*\*\          - VREFBUF_VOLTAGE_SCALE_2_0V
*\*\          - VREFBUF_VOLTAGE_SCALE_1_8V
*\*\          - VREFBUF_VOLTAGE_SCALE_1_5V
*\*\return  none
**/
void VREFBUF_SetVoltageScale(uint32_t Scale)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = *(uint32_t * )VREFBUF_CTRL2_REG_ADDR;
    /* Clear vrefbuf voltage scale select bits */
    tempreg &= (~VREFBUF_VOLTAGE_SCALE_MASK);
    /* Set vrefbuf voltage scale select bits */
    tempreg |= Scale;
    /* Store the new register value */
    *(uint32_t * )VREFBUF_CTRL2_REG_ADDR = tempreg;
}

/**
*\*\name    VREFBUF_GetVoltageScale.
*\*\fun     Get the Voltage reference scale.
*\*\param   none
*\*\return  the Voltage reference scale;
*\*\          - VREFBUF_VOLTAGE_SCALE_2_5V
*\*\          - VREFBUF_VOLTAGE_SCALE_2_0V
*\*\          - VREFBUF_VOLTAGE_SCALE_1_8V
*\*\          - VREFBUF_VOLTAGE_SCALE_1_5V
**/
uint32_t VREFBUF_GetVoltageScale(void)
{
    /* Clear vrefbuf voltage scale select bits */
    return ( (*(uint32_t * )VREFBUF_CTRL2_REG_ADDR) &VREFBUF_VOLTAGE_SCALE_MASK);
}
/**
*\*\name    VREFBUF_Enable.
*\*\fun     Enable or disable internal voltage reference.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void VREFBUF_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        *(uint32_t * )VREFBUF_CTRL1_REG_ADDR |= VREFBUF_EN_MASK;
    }
    else
    {
        *(uint32_t * )VREFBUF_CTRL1_REG_ADDR &= (~VREFBUF_EN_MASK);
    }
}

/**
*\*\name    VREFBUF_EnableHIM.
*\*\fun     Enable or disable high impedance (VREF+ pin is high impedance).
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void VREFBUF_EnableHIM(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        *(uint32_t * )VREFBUF_CTRL1_REG_ADDR |= VREFBUF_HIM_EN_MASK;
    }
    else
    {
        *(uint32_t * )VREFBUF_CTRL1_REG_ADDR &= (~VREFBUF_HIM_EN_MASK);
    }
}

/**
*\*\name    VREFBUF_SetTrimming.
*\*\fun     Set the trimming code for VREFBUF calibration.
*\*\param   Value :Value Between 0 and 0x3F
*\*\return  none
**/
void VREFBUF_SetTrimming(uint32_t Value)
{
    uint32_t tempreg, tempreg1;
    tempreg = ((*(uint32_t * )VREFBUF_CTRL2_REG_ADDR)&VREFBUF_VOLTAGE_SCALE_MASK);

    if(tempreg == VREFBUF_VOLTAGE_SCALE_2_5V)
    {
        tempreg1 = *(uint32_t * )VREFBUF_TRIM1_REG_ADDR;
        tempreg1 &= (~VREFBUF_TRIMING_2_5V_MASK);
        tempreg1 |= (Value << VREFBUF_TRIMING_2_5V_POS);
        /* Store the new register value */
        *(uint32_t * )VREFBUF_TRIM1_REG_ADDR = tempreg1;
    }
    else if(tempreg == VREFBUF_VOLTAGE_SCALE_2_048V)
    {
        tempreg1 = *(uint32_t * )VREFBUF_TRIM1_REG_ADDR;
        tempreg1 &= (~VREFBUF_TRIMING_2_0V_MASK);
        tempreg1 |= (Value << VREFBUF_TRIMING_2_0V_POS);
        /* Store the new register value */
        *(uint32_t * )VREFBUF_TRIM1_REG_ADDR = tempreg1;
    }
    else if(tempreg == VREFBUF_VOLTAGE_SCALE_1_8V)
    {
        tempreg1 = *(uint32_t * )VREFBUF_TRIM2_REG_ADDR;
        tempreg1 &= (~VREFBUF_TRIMING_1_8V_MASK);
        tempreg1 |= (Value << VREFBUF_TRIMING_1_8V_POS);
        /* Store the new register value */
        *(uint32_t * )VREFBUF_TRIM2_REG_ADDR = tempreg1;
    }
    else
    {
        tempreg1 = *(uint32_t * )VREFBUF_TRIM2_REG_ADDR;
        tempreg1 &= (~VREFBUF_TRIMING_1_5V_MASK);
        tempreg1 |= (Value << VREFBUF_TRIMING_1_5V_POS);
        /* Store the new register value */
        *(uint32_t * )VREFBUF_TRIM2_REG_ADDR = tempreg1;
    }
}

/**
*\*\name    VREFBUF_IsVREFReady.
*\*\fun     Checks whether VREFBUF ready flag is set or not.
*\*\param   none
*\*\return  The new state of VREFBUF_READY (SET or RESET).
**/
FlagStatus VREFBUF_IsVREFReady(void)
{
    return (((*(uint32_t * )VREFBUF_STS_REG_ADDR) & VREFBUF_READY_MASK) != 0U) ? SET : RESET;
}

