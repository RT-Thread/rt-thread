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
 * @file n32h76x_78x_wwdg.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_wwdg.h"
#include "n32h76x_78x_rcc.h"

/**
*\*\name    WWDG_DeInit.
*\*\fun     Resets the WWDG peripheral registers to their default reset values.
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\return  none
**/
void WWDG_DeInit(WWDG_Module* WWDGx)
{
    if (WWDGx == WWDG1)
    {
        RCC_EnableAXIPeriphReset2(RCC_AXI_PERIPHRST_WWDG1);
    }
    else
    {
        if (WWDGx == WWDG2)
        {
            RCC_EnableAPB1PeriphReset2(RCC_APB1_PERIPHRST_WWDG2);
        }
    }
}

/**
*\*\name    WWDG_SetPrescalerDiv.
*\*\fun     Set the WWDOG Prescaler Division Value.
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\param   WWDG_Prescaler :
*\*\          - WWDG_PRESCALER_DIV1   WWDG Counter Clock (PCLK1 / 4096) / 1
*\*\          - WWDG_PRESCALER_DIV2   WWDG Counter Clock (PCLK1 / 4096) / 2
*\*\          - WWDG_PRESCALER_DIV4   WWDG Counter Clock (PCLK1 / 4096) / 4
*\*\          - WWDG_PRESCALER_DIV8   WWDG Counter Clock (PCLK1 / 4096) / 8
*\*\return  none
**/
void WWDG_SetPrescalerDiv(WWDG_Module* WWDGx, uint32_t WWDG_Prescaler)
{
    uint32_t tmpregister;

    /* Clear TIMERB[1:0] bits */
    tmpregister = WWDGx->CFG & CFG_TIMERB_MASK;
    /* Set TIMERB[1:0] bits according to WWDG_Prescaler value */
    tmpregister |= WWDG_Prescaler;
    /* Store the new value */
    WWDGx->CFG = tmpregister;
}

/**
*\*\name    WWDG_SetWValue.
*\*\fun     Set the WWDOG Window Value.
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\param   WindowValue : WWDOG Window Value
*\*\          The value range of this parameter :
*\*\          - 0x0040 ~ 0x3FFF
*\*\return  none
**/
void WWDG_SetWValue(WWDG_Module* WWDGx, uint16_t WindowValue)
{
    __IO uint32_t tmpregister = 0;

    /* Clear W[13:0] bits */
    tmpregister = WWDGx->CFG & CFG_W_MASK;

    /* Set W[13:0] bits according to WindowValue value */
    tmpregister |= WindowValue & (uint32_t)BIT_MASK;

    /* Store the new value */
    WWDGx->CFG = tmpregister;
}

/**
*\*\name    WWDG_EnableInt.
*\*\fun     Enable WWDG Early Wakeup interrupt(EWINT).
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\return  none
**/
void WWDG_EnableInt(WWDG_Module* WWDGx)
{
    WWDGx->CFG |= EARLY_WAKEUP_INT;
}

/**
*\*\name    WWDG_SetCnt.
*\*\fun     Set the WWDOG Counter Value.
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\param   Counter : WWDOG Counter value
*\*\          The value range of this parameter :
*\*\          - 0x40 ~ 0x3FFF
*\*\return  none
**/
void WWDG_SetCnt(WWDG_Module* WWDGx, uint16_t Counter)
{
    /* Write to T[6:0] bits to configure the counter value, no need to do
       a read-modify-write; writing a 0 to WDGA bit does nothing */
    WWDGx->CTRL = (uint32_t)Counter & (uint32_t)BIT_MASK;
}

/**
*\*\name    WWDG_Enable.
*\*\fun     Set the WWDOG Counter Value and Enable WWDOG .
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\param   Counter : WWDOG Counter value
*\*\          The value range of this parameter :
*\*\          - 0x40 ~ 0x3FFF
*\*\return  none
**/
//uint32_t data;
void WWDG_Enable(WWDG_Module* WWDGx, uint16_t Counter)
{
    //data=CTRL_ACTB_SET | Counter;
    WWDGx->CTRL = CTRL_ACTB_SET | Counter;
}

/**
*\*\name    WWDG_GetEWINTF.
*\*\fun     Get WWDOG Early Wake-up Interrupt Flag.
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\param   none
*\*\return  SET or RESET
**/
FlagStatus WWDG_GetEWINTF(WWDG_Module* WWDGx)
{
    FlagStatus bitstatus;

    /* Return the status of the flag */
    if ((WWDGx->STS & EARLY_WAKEUP_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    WWDG_ClrEWINTF.
*\*\fun     Clear WWDOG Early Wake-up Interrupt Flag.
*\*\param   WWDGx (The input parameters must be the following values):
*\*\          - WWDG1
*\*\          - WWDG2
*\*\return  none
**/
void WWDG_ClrEWINTF(WWDG_Module* WWDGx)
{
    WWDGx->STS = (uint32_t)RESET;
}
