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
 * @file n32h76x_78x_tim.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */

#include "n32h76x_78x_tim.h"
#include "n32h76x_78x_rcc.h"

/**
*\*\name    TIM_DeInit
*\*\fun     Deinitializes the TIMx registers.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\return  none
**/
void TIM_DeInit(TIM_Module* TIMx)
{
    if (TIMx == ATIM1)
    {
        RCC_EnableAPB2PeriphReset1(RCC_APB2_PERIPHRST_ATIM1);
    }
    else if (TIMx == ATIM2)
    {
        RCC_EnableAPB2PeriphReset1(RCC_APB2_PERIPHRST_ATIM2);
    }
    else if (TIMx == ATIM3)
    {
        RCC_EnableAPB5PeriphReset1(RCC_APB5_PERIPHRST_ATIM3);
    }
    else if (TIMx == ATIM4)
    {
        RCC_EnableAPB5PeriphReset1(RCC_APB5_PERIPHRST_ATIM4);
    }
    else if (TIMx == GTIMA1)
    {
        RCC_EnableAPB2PeriphReset1(RCC_APB2_PERIPHRST_GTIMA1);
    }
    else if (TIMx == GTIMA2)
    {
        RCC_EnableAPB2PeriphReset1(RCC_APB2_PERIPHRST_GTIMA2);
    }
    else if (TIMx == GTIMA3)
    {
        RCC_EnableAPB2PeriphReset1(RCC_APB2_PERIPHRST_GTIMA3);
    }
    else if (TIMx == GTIMA4)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_GTIMA4);
    }
    else if (TIMx == GTIMA5)
    {
        RCC_EnableAPB1PeriphReset2(RCC_APB1_PERIPHRST_GTIMA5);
    }
    else if (TIMx == GTIMA6)
    {
        RCC_EnableAPB1PeriphReset2(RCC_APB1_PERIPHRST_GTIMA6);
    }
    else if (TIMx == GTIMA7)
    {
        RCC_EnableAPB1PeriphReset2(RCC_APB1_PERIPHRST_GTIMA7);
    }
    else if (TIMx == GTIMB1)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_GTIMB1);
    }
    else if (TIMx == GTIMB2)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_GTIMB2);
    }
    else if (TIMx == GTIMB3)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_GTIMB3);
    }
    else if (TIMx == BTIM1)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_BTIM1);
    }
    else if (TIMx == BTIM2)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_BTIM2);
    }
    else if (TIMx == BTIM3)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_BTIM3);
    }
    else if (TIMx == BTIM4)
    {
        RCC_EnableAPB1PeriphReset1(RCC_APB1_PERIPHRST_BTIM4);
    }
    else
    {

    }
}

/**
*\*\name    TIM_InitTimeBase
*\*\fun     Initializes the TIMx time base unit.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_TimeBaseInitStruct: refer to the definition of TIM_TimeBaseInitType
*\*\          - Prescaler
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - CounterMode
*\*\            * TIM_CNT_MODE_UP
*\*\            * TIM_CNT_MODE_DOWN
*\*\            * TIM_CNT_MODE_CENTER_ALIGN1
*\*\            * TIM_CNT_MODE_CENTER_ALIGN2
*\*\            * TIM_CNT_MODE_CENTER_ALIGN3
*\*\          - Period
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - ClkDiv
*\*\            * TIM_CLK_DIV1
*\*\            * TIM_CLK_DIV2
*\*\            * TIM_CLK_DIV4
*\*\          - RepetCnt
*\*\            * 0x00 ~ 0xFF
*\*\          - CapCh1Sel
*\*\            * TIM_CAPCH1SEL_0
*\*\            * TIM_CAPCH1SEL_1
*\*\            * TIM_CAPCH1SEL_2
*\*\            * TIM_CAPCH1SEL_3
*\*\            * TIM_CAPCH1SEL_4
*\*\            * TIM_CAPCH1SEL_5
*\*\            * TIM_CAPCH1SEL_6
*\*\            * TIM_CAPCH1SEL_7
*\*\          - CapCh2Sel
*\*\            * TIM_CAPCH2SEL_0
*\*\            * TIM_CAPCH2SEL_1
*\*\            * TIM_CAPCH2SEL_2
*\*\            * TIM_CAPCH2SEL_3
*\*\            * TIM_CAPCH2SEL_4
*\*\            * TIM_CAPCH2SEL_TIMXCAPLSE
*\*\          - CapCh3Sel
*\*\            * TIM_CAPCH3SEL_0
*\*\            * TIM_CAPCH3SEL_1
*\*\            * TIM_CAPCH3SEL_TIMXCAPLSI
*\*\          - CapCh4Sel
*\*\            * TIM_CAPCH4SEL_0
*\*\            * TIM_CAPCH4SEL_1
*\*\            * TIM_CAPCH4SEL_2
*\*\            * TIM_CAPCH4SEL_TIMXCAPHSEDIV128
*\*\          - EtrOrClr
*\*\            * TIM_ETRSEL
*\*\            * TIM_CLRSEL
*\*\          - CapEtrClrSel
*\*\            * TIM_CAPETRSEL_0
*\*\            * TIM_CAPETRSEL_1
*\*\            * TIM_CAPETRSEL_2
*\*\            * TIM_CAPETRSEL_3
*\*\            * TIM_CAPETRSEL_4
*\*\            * TIM_CAPETRSEL_5
*\*\            * TIM_CAPETRSEL_6
*\*\            * TIM_CAPETRSEL_7
*\*\            * TIM_CAPETRSEL_8
*\*\            * TIM_CAPETRSEL_10
*\*\            * TIM_CAPETRSEL_11
*\*\            * TIM_CAPETRSEL_12
*\*\            * TIM_CAPETRSEL_13
*\*\            * TIM_OCCLRSEL_0
*\*\            * TIM_OCCLRSEL_1
*\*\            * TIM_OCCLRSEL_2
*\*\            * TIM_OCCLRSEL_3
*\*\            * TIM_OCCLRSEL_4
*\*\            * TIM_OCCLRSEL_5
*\*\            * TIM_OCCLRSEL_6
*\*\            * TIM_OCCLRSEL_7
*\*\return  none
**/
void TIM_InitTimeBase(TIM_Module* TIMx, TIM_TimeBaseInitType* TIM_TimeBaseInitStruct)
{
    uint32_t tmpctrl1, tmpinsel;
    tmpctrl1 = TIMx->CTRL1;

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Select the Counter Mode */
        tmpctrl1 &= (uint32_t)(~(TIM_CTRL1_DIR | TIM_CTRL1_CAMSEL));
        tmpctrl1 |= (uint32_t)TIM_TimeBaseInitStruct->CounterMode;
    }

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Set the clock division */
        tmpctrl1 &= (uint32_t)(~TIM_CTRL1_CLKD);
        tmpctrl1 |= (uint32_t)TIM_TimeBaseInitStruct->ClkDiv;
    }

    TIMx->CTRL1 = tmpctrl1;

    /* Set the Autoreload value */
    TIMx->AR = TIM_TimeBaseInitStruct->Period ;

    /* Set the Prescaler value */
    TIMx->PSC = TIM_TimeBaseInitStruct->Prescaler;

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Set the Repetition Counter value */
        TIMx->REPCNT = TIM_TimeBaseInitStruct->RepetCnt;
    }

    /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
    TIMx->EVTGEN = TIM_PSC_RELOAD_MODE_IMMEDIATE;

    /* Channel 1/2/3/4 & OCxclr select capture in */
    tmpctrl1 = TIMx->CTRL1;
    tmpinsel = TIMx->INSEL;

    /* Channel 1 select capture in */
    if (((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx))) && (TIMx != GTIMA1))
    {
        /* Channel 1 select capture in */
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI1S);
        tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh1Sel;
    }
    else if (TIMx == GTIMA1)
    {
        /* Channel 1 select capture in */
        tmpctrl1 &= (uint32_t)(~TIM_CTRL1_C1SEL);
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI1S);
        tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh1Sel;
    }
    else
    {
    }

    /* Channel 2 select capture in */
    if (((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx))) && (TIMx != GTIMA1))
    {
        /* Channel 2 select capture in */
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI2S);
        tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh2Sel;
    }
    else if (TIMx == GTIMA1)
    {
        /* Channel 2 select capture in */
        tmpctrl1 &= (uint32_t)(~TIM_CTRL1_C2SEL);
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI2S);

        if ((TIM_TimeBaseInitStruct->CapCh2Sel != TIM_CAPCH2SEL_TIMXCAPLSE))
        {
            tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh2Sel;
        }
        else /* TIM_CAPCH2SEL_TIMXCAPLSE */
        {
            tmpctrl1 |= (uint32_t)TIM_TimeBaseInitStruct->CapCh2Sel;
        }
    }
    else
    {
    }

    /* Channel 3 select capture in */
    if (((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx))) && (TIMx != GTIMA1))
    {
        /* Channel 3 select capture in */
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI3S);
        tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh3Sel;
    }
    else if (TIMx == GTIMA1)
    {
        /* Channel 3 select capture in */
        tmpctrl1 &= (uint32_t)(~TIM_CTRL1_C3SEL);
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI3S);

        if ((TIM_TimeBaseInitStruct->CapCh3Sel != TIM_CAPCH3SEL_TIMXCAPLSI))
        {
            tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh3Sel;
        }
        else /* TIM_CAPCH3SEL_TIMXCAPLSI */
        {
            tmpctrl1 |= (uint32_t)TIM_TimeBaseInitStruct->CapCh3Sel;
        }
    }
    else
    {
    }

    /* Channel 4 select capture in */
    if (((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx))) && (TIMx != GTIMA1))
    {
        /* Channel 4 select capture in */
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI4S);
        tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh4Sel;
    }
    else if (TIMx == GTIMA1)
    {
        /* Channel 4 select capture in */
        tmpctrl1 &= (uint32_t)(~TIM_CTRL1_C4SEL);
        tmpinsel &= (uint32_t)(~TIM_INSEL_TI4S);

        if ((TIM_TimeBaseInitStruct->CapCh4Sel != TIM_CAPCH4SEL_TIMXCAPHSEDIV128))
        {
            tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapCh4Sel;
        }
        else /* TIM_CAPCH4SEL_TIMXCAPHSEDIV128 */
        {
            tmpctrl1 |= (uint32_t)TIM_TimeBaseInitStruct->CapCh4Sel;
        }
    }
    else
    {
    }

    /* CLR or ETR select capture in */
    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        tmpctrl1 &= (uint32_t)(~TIM_CTRL1_CLRSEL);
        tmpinsel &= (uint32_t)(~TIM_INSEL_ETRS);
        tmpinsel &= (uint32_t)(~TIM_INSEL_CLRS);

        if ((TIM_TimeBaseInitStruct->EtrOrClr) == 0)
        {
            /* ETR select capture in */
            tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapEtrClrSel;
        }
        else
        {
            /* CLR select capture in */
            tmpctrl1 |= (uint32_t)TIM_CTRL1_CLRSEL;
            tmpinsel |= (uint32_t)TIM_TimeBaseInitStruct->CapEtrClrSel;
        }
    }

    TIMx->CTRL1 = tmpctrl1;
    TIMx->INSEL = tmpinsel;

}

/**
*\*\name    TIM_InitOc1
*\*\fun     Initializes the TIMx Channel 1.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\            * TIM_OCMODE_OPMOD_RETRIG1
*\*\            * TIM_OCMODE_OPMOD_RETRIG2
*\*\            * TIM_OCMODE_COMBI_PWM1
*\*\            * TIM_OCMODE_COMBI_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOc1(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint32_t tmpccmodx;
    uint32_t tmpccen, tmpctrl2;

    /* Disable the Channel 1: Reset the CC1EN Bit */
    TIMx->CCEN &= (uint32_t)(~TIM_CCEN_CC1EN);
    /* Get the TIMx_CCEN register value */
    tmpccen = TIMx->CCEN;
    /* Get the TIMx_CTRL2 register value */
    tmpctrl2 =  TIMx->CTRL2;
    /* Get the TIMx_CCMOD1 register value */
    tmpccmodx = TIMx->CCMOD1;

    /* Reset the Output Compare Mode Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC1MD);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC1MD_3);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_CC1SEL);
    /* Select the Output Compare Mode */
    tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode);

    /* Reset the Output Polarity level */
    tmpccen &= (uint32_t)(~TIM_CCEN_CC1P);
    /* Set the Output Compare Polarity */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OCPolarity);
    /* Set the Output State */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputState);

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Reset the Output N Polarity level */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC1NP);
        /* Set the Output N Polarity */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OCNPolarity);
        /* Reset the Output N State */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC1NEN);
        /* Set the Output N State */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputNState);

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI1);
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI1N);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState);
        /* Set the Output N Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCNIdleState);
    }

    /* Write to TIMx_CTRL2 */
    TIMx->CTRL2 = tmpctrl2;

    /* Write to TIMx_CCMOD1 */
    TIMx->CCMOD1 = tmpccmodx;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT1 = TIM_OCInitStruct->Pulse;

    /* Write to TIMx_CCEN */
    TIMx->CCEN = tmpccen;

}

/**
*\*\name    TIM_InitOc2
*\*\fun     Initializes the TIMx Channel 2.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\            * TIM_OCMODE_OPMOD_RETRIG1
*\*\            * TIM_OCMODE_OPMOD_RETRIG2
*\*\            * TIM_OCMODE_COMBI_PWM1
*\*\            * TIM_OCMODE_COMBI_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOc2(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmpctrl2;

    /* Disable the Channel 2: Reset the CC2EN Bit */
    TIMx->CCEN &= (uint32_t)(~TIM_CCEN_CC2EN);

    /* Get the TIMx_CCEN register value */
    tmpccen = TIMx->CCEN;
    /* Get the TIMx_CTRL2 register value */
    tmpctrl2 =  TIMx->CTRL2;

    /* Get the TIMx_CCMOD1 register value */
    tmpccmodx = TIMx->CCMOD1;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC2MD);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC2MD_3);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_CC2SEL);

    if (((TIM_OCInitStruct->OCMode) == TIM_OCMODE_OPMOD_RETRIG1) || ((TIM_OCInitStruct->OCMode) == TIM_OCMODE_OPMOD_RETRIG2) || \
            ((TIM_OCInitStruct->OCMode) == TIM_OCMODE_COMBI_PWM1) || ((TIM_OCInitStruct->OCMode) == TIM_OCMODE_COMBI_PWM2))
    {
        /* Select the Output Compare Mode */
        tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode << 8);
        tmpccmodx |= (uint32_t)TIM_CCMOD1_OC2MD_3;
    }
    else
    {
        /* Select the Output Compare Mode */
        tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode << 8);
    }

    /* Reset the Output Polarity level */
    tmpccen &= (uint32_t)(~TIM_CCEN_CC2P);
    /* Set the Output Compare Polarity */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OCPolarity << 4);
    /* Set the Output State */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputState << 4);

    if (IS_ATIM1_4_DEVICE(TIMx))
    {
        /* Reset the Output N Polarity level */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC2NP);
        /* Set the Output N Polarity */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OCNPolarity << 4);
        /* Reset the Output N State */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC2NEN);
        /* Set the Output N State */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputNState << 4);

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI2);
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI2N);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 2);
        /* Set the Output N Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCNIdleState << 2);
    }

    if (IS_GTIMB1_3_DEVICE(TIMx))
    {
        /* Reset the Output Compare IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI2);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 2);
    }

    /* Write to TIMx_CTRL2 */
    TIMx->CTRL2 = tmpctrl2;

    /* Write to TIMx_CCMOD1 */
    TIMx->CCMOD1 = tmpccmodx;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT2 = TIM_OCInitStruct->Pulse;

    /* Write to TIMx_CCEN */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_InitOc3
*\*\fun     Initializes the TIMx Channel 3.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\            * TIM_OCMODE_OPMOD_RETRIG1
*\*\            * TIM_OCMODE_OPMOD_RETRIG2
*\*\            * TIM_OCMODE_COMBI_PWM1
*\*\            * TIM_OCMODE_COMBI_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOc3(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmpctrl2 ;

    /* Disable the Channel 3: Reset the CC3EN Bit */
    TIMx->CCEN &= (uint32_t)(~TIM_CCEN_CC3EN);

    /* Get the TIMx_CCEN register value */
    tmpccen = TIMx->CCEN;

    /* Get the TIMx_CTRL2 register value */
    tmpctrl2 =  TIMx->CTRL2;

    /* Get the TIMx_CCMOD2 register value */
    tmpccmodx = TIMx->CCMOD2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC3MD);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC3MD_3);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_CC3SEL);
    /* Select the Output Compare Mode */
    tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode);

    /* Reset the Output Polarity level */
    tmpccen &= (uint32_t)(~TIM_CCEN_CC3P);
    /* Set the Output Compare Polarity */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OCPolarity << 8);
    /* Set the Output State */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputState << 8);

    if (IS_ATIM1_4_DEVICE(TIMx))
    {
        /* Reset the Output N Polarity level */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC3NP);
        /* Set the Output N Polarity */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OCNPolarity << 8);
        /* Reset the Output N State */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC3NEN);
        /* Set the Output N State */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputNState << 8);

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI3);
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI3N);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 4);
        /* Set the Output N Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCNIdleState << 4);
    }

    if (IS_GTIMB1_3_DEVICE(TIMx))
    {
        /* Reset the Output Compare IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI3);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 4);
    }

    /* Write to TIMx_CTRL2 */
    TIMx->CTRL2 = tmpctrl2;

    /* Write to TIMx_CCMOD2 */
    TIMx->CCMOD2 = tmpccmodx;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT3 = TIM_OCInitStruct->Pulse;

    /* Write to TIMx CCER */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_InitOc4
*\*\fun     Initializes the TIMx Channel 4.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\            * TIM_OCMODE_OPMOD_RETRIG1
*\*\            * TIM_OCMODE_OPMOD_RETRIG2
*\*\            * TIM_OCMODE_COMBI_PWM1
*\*\            * TIM_OCMODE_COMBI_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOc4(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmpctrl2 ;

    /* Disable the Channel 2: Reset the CC4E Bit */
    TIMx->CCEN &= (uint32_t)(~TIM_CCEN_CC4EN);

    /* Get the TIMx_CCEN register value */
    tmpccen = TIMx->CCEN;

    /* Get the TIMx_CTRL2 register value */
    tmpctrl2 =  TIMx->CTRL2;

    /* Get the TIMx_CCMOD2 register value */
    tmpccmodx = TIMx->CCMOD2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC4MD);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC4MD_3);
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_CC4SEL);

    if (((TIM_OCInitStruct->OCMode) == TIM_OCMODE_OPMOD_RETRIG1) || ((TIM_OCInitStruct->OCMode) == TIM_OCMODE_OPMOD_RETRIG2) || \
            ((TIM_OCInitStruct->OCMode) == TIM_OCMODE_COMBI_PWM1) || ((TIM_OCInitStruct->OCMode) == TIM_OCMODE_COMBI_PWM2))
    {
        /* Select the Output Compare Mode */
        tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode << 8);
        tmpccmodx |= (uint32_t)TIM_CCMOD2_OC4MD_3;
    }
    else
    {
        tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode << 8);
    }

    /* Reset the Output Polarity level */
    tmpccen &= (uint32_t)(~TIM_CCEN_CC4P);
    /* Set the Output Compare Polarity */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OCPolarity << 12);
    /* Set the Output State */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputState << 12);

    if ((IS_ATIM1_4_DEVICE(TIMx)))
    {
        /* Reset the Output N Polarity level */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC4NP) ;
        /* Set the Output N Polarity */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OCNPolarity << 12);
        /* Reset the Output N State */
        tmpccen &= (uint32_t)(~TIM_CCEN_CC4NEN);
        /* Set the Output N State */
        tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputNState << 12);

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI4);
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI4N);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 6);
        /* Set the Output N Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCNIdleState << 6);
    }

    if (IS_GTIMB1_3_DEVICE(TIMx))
    {
        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI4);
        /* Set the Output Idle state */
        tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 6);
    }

    /* Write to TIMx_CTRL2 */
    TIMx->CTRL2 = tmpctrl2;

    /* Write to TIMx_CCMOD2 */
    TIMx->CCMOD2 = tmpccmodx;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT4 = TIM_OCInitStruct->Pulse;

    /* Write to TIMx_CCEN */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_InitOc5
*\*\fun     Initializes the TIMx Channel 5.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOc5(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmpctrl2 ;

    /* Disable the Channel 5: Reset the CC5EN Bit */
    TIMx->CCEN &= (uint32_t)(~TIM_CCEN_CC5EN);

    /* Get the TIMx_CCEN register value */
    tmpccen = TIMx->CCEN;

    /* Get the TIMx_CTRL2 register value */
    tmpctrl2 =  TIMx->CTRL2;

    /* Get the TIMx_CCMOD3 register value */
    tmpccmodx = TIMx->CCMOD3;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC5MD);
    /* Select the Output Compare Mode */
    tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode);

    /* Reset the Output Polarity level */
    tmpccen &= (uint32_t)(~TIM_CCEN_CC5P);
    /* Set the Output Compare Polarity */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OCPolarity << 16);
    /* Set the Output State */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputState << 16);

    /* Reset the Output Compare IDLE State */
    tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI5);
    /* Set the Output Idle state */
    tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 8);

    /* Write to TIMx CR2 */
    TIMx->CTRL2 = tmpctrl2;

    /* Write to TIMx_CCMOD3 */
    TIMx->CCMOD3 = tmpccmodx;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT5 = TIM_OCInitStruct->Pulse;

    /* Write to TIMx CCER */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_InitOc6
*\*\fun     Initializes the TIMx Channel 6.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOc6(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmpctrl2 ;

    /* Disable the Channel 6: Reset the CC6EN Bit */
    TIMx->CCEN &= (uint32_t)(~TIM_CCEN_CC6EN);

    /* Get the TIMx_CCEN register value */
    tmpccen = TIMx->CCEN;

    /* Get the TIMx_CTRL2 register value */
    tmpctrl2 =  TIMx->CTRL2;

    /* Get the TIMx_CCMOD3 register value */
    tmpccmodx = TIMx->CCMOD3;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC6MD);
    /* Select the Output Compare Mode */
    tmpccmodx |= (uint32_t)(TIM_OCInitStruct->OCMode << 8);

    /* Reset the Output Polarity level */
    tmpccen &= (uint32_t)(~TIM_CCEN_CC6P);
    /* Set the Output Compare Polarity */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OCPolarity << 20);
    /* Set the Output State */
    tmpccen |= (uint32_t)(TIM_OCInitStruct->OutputState << 20);

    /* Reset the Output Compare IDLE State */
    tmpctrl2 &= (uint32_t)(~TIM_CTRL2_OI6);
    /* Set the Output Idle state */
    tmpctrl2 |= (uint32_t)(TIM_OCInitStruct->OCIdleState << 10);

    /* Write to TIMx CR2 */
    TIMx->CTRL2 = tmpctrl2;

    /* Write to TIMx_CCMOD3 */
    TIMx->CCMOD3 = tmpccmodx;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT6 = TIM_OCInitStruct->Pulse;

    /* Write to TIMx CCER */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ICInit
*\*\fun     Initializes the TIM peripheral according to the specified
*\*\            parameters in the TIM_ICInitStruct.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ICInitStruct: refer to the definition of TIM_ICInitType
*\*\          - Channel
*\*\            * TIM_CH_1
*\*\            * TIM_CH_2
*\*\            * TIM_CH_3
*\*\            * TIM_CH_4
*\*\          - ICPolarity
*\*\            * TIM_IC_POLARITY_RISING
*\*\            * TIM_IC_POLARITY_FALLING
*\*\          - ICSelection
*\*\            * TIM_IC_SELECTION_DIRECTTI
*\*\            * TIM_IC_SELECTION_INDIRECTTI
*\*\            * TIM_IC_SELECTION_TRC
*\*\          - ICPrescaler
*\*\            * TIM_IC_PSC_DIV1
*\*\            * TIM_IC_PSC_DIV2
*\*\            * TIM_IC_PSC_DIV4
*\*\            * TIM_IC_PSC_DIV8
*\*\          - ICFilter
*\*\            * ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_ICInit(TIM_Module* TIMx, TIM_ICInitType* TIM_ICInitStruct)
{
    if (TIM_ICInitStruct->Channel == TIM_CH_1)
    {
        /* TI1 Configuration */
        ConfigTI1(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap1Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
    }
    else if (TIM_ICInitStruct->Channel == TIM_CH_2)
    {
        /* TI2 Configuration */
        ConfigTI2(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap2Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
    }
    else if (TIM_ICInitStruct->Channel == TIM_CH_3)
    {
        /* TI3 Configuration */
        ConfigTI3(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap3Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
    }
    else if (TIM_ICInitStruct->Channel == TIM_CH_4)
    {
        /* TI4 Configuration */
        ConfigTI4(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap4Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
    }
    else
    {
    }
}

/**
*\*\name    TIM_ConfigPwmIc
*\*\fun     Configures the TIM peripheral according to the specified
*\*\            parameters in the TIM_ICInitStruct to measure an external PWM signal.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ICInitStruct: refer to the definition of TIM_ICInitType
*\*\          - Channel
*\*\            * TIM_CH_1
*\*\            * TIM_CH_2
*\*\          - ICPolarity
*\*\            * TIM_IC_POLARITY_RISING
*\*\            * TIM_IC_POLARITY_FALLING
*\*\          - ICSelection
*\*\            * TIM_IC_SELECTION_DIRECTTI
*\*\            * TIM_IC_SELECTION_INDIRECTTI
*\*\          - ICPrescaler
*\*\            * TIM_IC_PSC_DIV1
*\*\            * TIM_IC_PSC_DIV2
*\*\            * TIM_IC_PSC_DIV4
*\*\            * TIM_IC_PSC_DIV8
*\*\          - ICFilter
*\*\            * ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_ConfigPwmIc(TIM_Module* TIMx, TIM_ICInitType* TIM_ICInitStruct)
{
    uint32_t icoppositepolarity  ;
    uint32_t icoppositeselection ;

    /* Select the Opposite Input Polarity */
    if (TIM_ICInitStruct->ICPolarity == TIM_IC_POLARITY_RISING)
    {
        icoppositepolarity = TIM_IC_POLARITY_FALLING;
    }
    else
    {
        icoppositepolarity = TIM_IC_POLARITY_RISING;
    }

    /* Select the Opposite Input */
    if (TIM_ICInitStruct->ICSelection == TIM_IC_SELECTION_DIRECTTI)
    {
        icoppositeselection = TIM_IC_SELECTION_INDIRECTTI;
    }
    else
    {
        icoppositeselection = TIM_IC_SELECTION_DIRECTTI;
    }

    if (TIM_ICInitStruct->Channel == TIM_CH_1)
    {
        /* TI1 Configuration */
        ConfigTI1(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap1Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
        /* TI2 Configuration */
        ConfigTI2(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap2Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
    }
    else
    {
        /* TI2 Configuration */
        ConfigTI2(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap2Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
        /* TI1 Configuration */
        ConfigTI1(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetInCap1Prescaler(TIMx, TIM_ICInitStruct->ICPrescaler);
    }
}

/**
*\*\name    TIM_ConfigBkdt
*\*\fun     Configures the: Break feature, dead time, Lock level, the OSSI,
*\*\            the OSSR State and the AOE(automatic output enable).
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_BDTRInitStruct: refer to the definition of TIM_BDTRInitType
*\*\          - OSSRState
*\*\            * TIM_OSSR_STATE_ENABLE
*\*\            * TIM_OSSR_STATE_DISABLE
*\*\          - OSSIState
*\*\            * TIM_OSSI_STATE_ENABLE
*\*\            * TIM_OSSI_STATE_DISABLE
*\*\          - LOCKLevel
*\*\            * TIM_LOCK_LEVEL_OFF
*\*\            * TIM_LOCK_LEVEL_1
*\*\            * TIM_LOCK_LEVEL_2
*\*\            * TIM_LOCK_LEVEL_3
*\*\          - DeadTime
*\*\            * DeadTime can be a number between 0x00 and 0xFF
*\*\          - Break
*\*\            * TIM_BREAK_IN_ENABLE
*\*\            * TIM_BREAK_IN_DISABLE
*\*\          - BreakPolarity
*\*\            * TIM_BREAK_POLARITY_LOW
*\*\            * TIM_BREAK_POLARITY_HIGH
*\*\          - Bidirection
*\*\            * TIM_BREAK_BID_ENABLE
*\*\            * TIM_BREAK_BID_DISABLE
*\*\          - AutomaticOutput
*\*\            * TIM_AUTO_OUTPUT_ENABLE
*\*\            * TIM_AUTO_OUTPUT_DISABLE
*\*\          - Break2
*\*\            * TIM_BREAK2_IN_ENABLE
*\*\            * TIM_BREAK2_IN_DISABLE
*\*\          - Break2Polarity
*\*\            * TIM_BREAK2_POLARITY_LOW
*\*\            * TIM_BREAK2_POLARITY_HIGH
*\*\          - Bidirection2
*\*\            * TIM_BREAK2_BID_ENABLE
*\*\            * TIM_BREAK2_BID_DISABLE
*\*\return  none
**/
void TIM_ConfigBkdt(TIM_Module* TIMx, TIM_BDTRInitType* TIM_BDTRInitStruct)
{
    uint32_t tmpbkdt;

    /* Set the Lock level, the OSSR State, the OSSI State,
           the dead time value and the Automatic Output Enable Bit */
    tmpbkdt = TIMx->BKDT;
    tmpbkdt &= (uint32_t)(~(TIM_BKDT_OSSR | TIM_BKDT_OSSI | TIM_BKDT_LCKCFG | TIM_BKDT_DTGN | TIM_BKDT_AOEN));
    tmpbkdt |= (uint32_t)(TIM_BDTRInitStruct->OSSRState | TIM_BDTRInitStruct->OSSIState | TIM_BDTRInitStruct->LOCKLevel | \
                          TIM_BDTRInitStruct->DeadTime | TIM_BDTRInitStruct->AutomaticOutput);

    /* Set the Break enable Bit and the Ploarity */
    if  ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        tmpbkdt &= (uint32_t)(~(TIM_BKDT_BKEN | TIM_BKDT_BKP | TIM_BKDT_BRKBID));
        tmpbkdt |= (uint32_t)(TIM_BDTRInitStruct->Break | TIM_BDTRInitStruct->BreakPolarity | TIM_BDTRInitStruct->Bidirection);
    }

    /* Set the Break2 enable Bit and the Ploarity */
    if  (IS_ATIM1_4_DEVICE(TIMx))
    {
        tmpbkdt &= (uint32_t)(~(TIM_BKDT_BK2EN | TIM_BKDT_BK2P | TIM_BKDT_BRK2BID));
        tmpbkdt |= (uint32_t)(TIM_BDTRInitStruct->Break2 | TIM_BDTRInitStruct->Break2Polarity | TIM_BDTRInitStruct->Bidirection2);
    }

    TIMx->BKDT = tmpbkdt;
}

/**
*\*\name    TIM_BreakFiltConfig
*\*\fun     Config the filter of break input.
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_FiltInitStruct:
*\*\          - refer to the definition of TIM_FiltInitType
*\*\return  none
**/
void TIM_BreakFiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct)
{
    uint32_t tempbkfr;

    tempbkfr = TIMx->BKFR;

    tempbkfr &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_BKFR_THRESH)) &
                           ((uint32_t) ~((uint32_t)TIM_BKFR_WSIZE)) &
                           ((uint32_t) ~((uint32_t)TIM_BKFR_SFPSC)));

    tempbkfr |= (uint32_t)((TIM_FiltInitStruct->ThreshHold << (uint32_t)(0x18)) |
                           (TIM_FiltInitStruct->WindowSize << (uint32_t)(0x11)) |
                           (TIM_FiltInitStruct->Prescaler));
    TIMx->BKFR = tempbkfr;


}

/**
*\*\name    TIM_Break2FiltConfig
*\*\fun     Config the filter of break2 input.
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_FiltInitStruct:
*\*\          - refer to the definition of TIM_FiltInitType
*\*\return  none
**/
void TIM_Break2FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct)
{
    uint32_t tempbkfr2;

    tempbkfr2 = TIMx->BKFR2;

    tempbkfr2 &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_BKFR2_THRESH)) &
                            ((uint32_t) ~((uint32_t)TIM_BKFR2_WSIZE)) &
                            ((uint32_t) ~((uint32_t)TIM_BKFR2_SFPSC)));

    tempbkfr2 |= (uint32_t)((TIM_FiltInitStruct->ThreshHold << (uint32_t)(0x18)) |
                            (TIM_FiltInitStruct->WindowSize << (uint32_t)(0x11)) |
                            (TIM_FiltInitStruct->Prescaler));
    TIMx->BKFR2 = tempbkfr2;

}

/**
*\*\name    TIM_BreakFiltEnable
*\*\fun     Enable or disable the filter of break input.
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_BreakFiltEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the filter of break input */
        TIMx->BKFR |= (uint32_t)TIM_BKFR_FILTEN;
    }
    else
    {
        /* Disable the filter of break input */
        TIMx->BKFR &= (uint32_t)(~TIM_BKFR_FILTEN);
    }
}

/**
*\*\name    TIM_Break2FiltEnable
*\*\fun     Enable or disable the filter of break2 input.
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_Break2FiltEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the filter of break2 input */
        TIMx->BKFR2 |= (uint32_t)TIM_BKFR2_FILTEN;
    }
    else
    {
        /* Disable the filter of break2 input */
        TIMx->BKFR2 &= (uint32_t)(~TIM_BKFR2_FILTEN);
    }
}

/**
*\*\name    TIM_BreakInputSourceEnable
*\*\fun     Enable or disable the break input source , and set the polarity of the break input source.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Source
*\*\          - TIM_BREAK_LOCKUP
*\*\          - TIM_BREAK_PVD
*\*\          - TIM_BREAK_SMPAR
*\*\          - TIM_BREAK_FLECC
*\*\          - TIM_BREAK_SMECC
*\*\          - TIM_BREAK_IOM
*\*\          - TIM_BREAK_COMP1
*\*\          - TIM_BREAK_COMP2
*\*\          - TIM_BREAK_COMP3
*\*\          - TIM_BREAK_DSMU0
*\*\          - TIM_BREAK_DSMU1
*\*\          - TIM_BREAK_DSMU2
*\*\          - TIM_BREAK_DSMU3
*\*\param   Polarity
*\*\          - TIM_BREAK_SOURCE_POLARITY_INVERT
*\*\          - TIM_BREAK_SOURCE_POLARITY_NONINVERT
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_BreakInputSourceEnable(TIM_Module* TIMx, uint32_t Source, uint32_t Polarity, FunctionalState Cmd)
{
    uint32_t tempctrl1;
    uint32_t tempaf1;
    tempctrl1 = TIMx->CTRL1;
    tempaf1 = TIMx->AF1;

    if (Cmd != DISABLE)
    {
        if (IS_SYS_BREAK(Source))
        {
            tempctrl1 |= (uint32_t)(Source);
        }
        else
        {
            /* Enable break input source */
            tempaf1 |= (uint32_t)(Source);
            /* Set break input source polarity */
            tempaf1 &= (uint32_t)(~((Source & 0x1F) << 9));
            tempaf1 |= (uint32_t)(Polarity & ((Source & 0x1F) << 9));
        }

    }
    else
    {
        if (IS_SYS_BREAK(Source))
        {
            tempctrl1 &= (uint32_t)(~Source);
        }
        else
        {
            /* Disable break input source */
            tempaf1 &= (uint32_t)(~Source);
            /* Set break input source polarity */
            tempaf1 &= (uint32_t)(~((Source & 0x1F) << 9));
            tempaf1 |= (uint32_t)(Polarity & ((Source & 0x1F) << 9));
        }
    }

    TIMx->CTRL1 = tempctrl1;
    TIMx->AF1 = tempaf1;
}

/**
*\*\name    TIM_Break2InputSourceEnable
*\*\fun     Enable or disable the break2 input source , and set the polarity of the break2 input source.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   Source
*\*\          - TIM_BREAK2_IOM
*\*\          - TIM_BREAK2_COMP1
*\*\          - TIM_BREAK2_COMP2
*\*\          - TIM_BREAK2_COMP3
*\*\          - TIM_BREAK2_COMP4
*\*\          - TIM_BREAK2_DSMU0
*\*\          - TIM_BREAK2_DSMU1
*\*\          - TIM_BREAK2_DSMU2
*\*\          - TIM_BREAK2_DSMU3
*\*\param   Polarity
*\*\          - TIM_BREAK2_SOURCE_POLARITY_INVERT
*\*\          - TIM_BREAK2_SOURCE_POLARITY_NONINVERT
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_Break2InputSourceEnable(TIM_Module* TIMx, uint32_t Source, uint32_t Polarity, FunctionalState Cmd)
{
    uint32_t tempaf2;
    tempaf2 = TIMx->AF2;

    if (Cmd != DISABLE)
    {
        /* Enable break2 input source */
        tempaf2 |= (uint32_t)(Source);
        /* Set break2 input source polarity */
        tempaf2 &= (uint32_t)(~((Source & 0x1F) << 9));
        tempaf2 |= (uint32_t)(Polarity & ((Source & 0x1F) << 9));
    }
    else
    {
        /* Disable break2 input source */
        tempaf2 &= (uint32_t)(~Source);
        /* Set break2 input source polarity */
        tempaf2 &= (uint32_t)(~((Source & 0x1F) << 9));
        tempaf2 |= (uint32_t)(Polarity & ((Source & 0x1F) << 9));
    }

    TIMx->AF2 = tempaf2;
}

/**
*\*\name    TIM_BidirectionDisarm
*\*\fun     Disarm bidirection of break.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  none
**/
void TIM_BidirectionDisarm(TIM_Module* TIMx)
{
    TIMx->BKDT |= (uint32_t)TIM_BKDT_BRKDSRM;
}

/**
*\*\name    TIM_BidirectionRearm
*\*\fun     Rearm bidirection of break.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  none
**/
void TIM_BidirectionRearm(TIM_Module* TIMx)
{
    TIMx->BKDT &= (uint32_t)(~TIM_BKDT_BRKDSRM);
}

/**
*\*\name    TIM_Bidirection2Disarm
*\*\fun     Disarm bidirection of break2.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  none
**/
void TIM_Bidirection2Disarm(TIM_Module* TIMx)
{
    TIMx->BKDT |= (uint32_t)TIM_BKDT_BRK2DSRM;
}

/**
*\*\name    TIM_Bidirection2Rearm
*\*\fun     Rearm bidirection of break2.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  none
**/
void TIM_Bidirection2Rearm(TIM_Module* TIMx)
{
    TIMx->BKDT &= (uint32_t)(~TIM_BKDT_BRK2DSRM);
}

/**
*\*\name    TIM_InitTimBaseStruct
*\*\fun     Fills each TIM_TimeBaseInitStruct member with its default value.
*\*\param   TIM_TimeBaseInitStruct: refer to the definition of TIM_TimeBaseInitType
*\*\          - Prescaler
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - CounterMode
*\*\            * TIM_CNT_MODE_UP
*\*\            * TIM_CNT_MODE_DOWN
*\*\            * TIM_CNT_MODE_CENTER_ALIGN1
*\*\            * TIM_CNT_MODE_CENTER_ALIGN2
*\*\            * TIM_CNT_MODE_CENTER_ALIGN3
*\*\          - Period
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - ClkDiv
*\*\            * TIM_CLK_DIV1
*\*\            * TIM_CLK_DIV2
*\*\            * TIM_CLK_DIV4
*\*\          - RepetCnt
*\*\            * 0x00 ~ 0xFF
*\*\          - CapCh1Sel
*\*\            * TIM_CAPCH1SEL_0
*\*\            * TIM_CAPCH1SEL_1
*\*\            * TIM_CAPCH1SEL_2
*\*\            * TIM_CAPCH1SEL_3
*\*\            * TIM_CAPCH1SEL_4
*\*\            * TIM_CAPCH1SEL_5
*\*\            * TIM_CAPCH1SEL_6
*\*\            * TIM_CAPCH1SEL_7
*\*\          - CapCh2Sel
*\*\            * TIM_CAPCH2SEL_0
*\*\            * TIM_CAPCH2SEL_1
*\*\            * TIM_CAPCH2SEL_2
*\*\            * TIM_CAPCH2SEL_3
*\*\            * TIM_CAPCH2SEL_4
*\*\            * TIM_CAPCH2SEL_TIMXCAPLSE
*\*\          - CapCh3Sel
*\*\            * TIM_CAPCH3SEL_0
*\*\            * TIM_CAPCH3SEL_1
*\*\            * TIM_CAPCH3SEL_TIMXCAPLSI
*\*\          - CapCh4Sel
*\*\            * TIM_CAPCH4SEL_0
*\*\            * TIM_CAPCH4SEL_1
*\*\            * TIM_CAPCH4SEL_2
*\*\            * TIM_CAPCH4SEL_TIMXCAPHSEDIV128
*\*\          - CapEtrClrSel
*\*\            * TIM_CAPETRSEL_0
*\*\            * TIM_CAPETRSEL_1
*\*\            * TIM_CAPETRSEL_2
*\*\            * TIM_CAPETRSEL_3
*\*\            * TIM_CAPETRSEL_4
*\*\            * TIM_CAPETRSEL_5
*\*\            * TIM_CAPETRSEL_6
*\*\            * TIM_CAPETRSEL_7
*\*\            * TIM_CAPETRSEL_8
*\*\            * TIM_CAPETRSEL_10
*\*\            * TIM_CAPETRSEL_11
*\*\            * TIM_CAPETRSEL_12
*\*\            * TIM_CAPETRSEL_13
*\*\return  none
**/
void TIM_InitTimBaseStruct(TIM_TimeBaseInitType* TIM_TimeBaseInitStruct)
{
    /* Set the default configuration */
    TIM_TimeBaseInitStruct->Prescaler    = 0x00000000;
    TIM_TimeBaseInitStruct->CounterMode  = TIM_CNT_MODE_UP;
    TIM_TimeBaseInitStruct->Period       = 0x0000FFFF;
    TIM_TimeBaseInitStruct->ClkDiv       = TIM_CLK_DIV1;
    TIM_TimeBaseInitStruct->RepetCnt     = 0x00000000;

    /* CH1/CH2/CH3/CH4/ETR from IOM */
    TIM_TimeBaseInitStruct->CapCh1Sel     = TIM_CAPCH1SEL_0;
    TIM_TimeBaseInitStruct->CapCh2Sel     = TIM_CAPCH2SEL_0;
    TIM_TimeBaseInitStruct->CapCh3Sel     = TIM_CAPCH3SEL_0;
    TIM_TimeBaseInitStruct->CapCh4Sel     = TIM_CAPCH4SEL_0;
    TIM_TimeBaseInitStruct->CapEtrClrSel  = TIM_CAPETRSEL_0;
}

/**
*\*\name    TIM_InitOcStruct
*\*\fun     Fills each TIM_OCInitStruct member with its default value.
*\*\param   TIM_OCInitStruct: refer to the definition of OCInitType
*\*\          - OCMode
*\*\            * TIM_OCMODE_TIMING
*\*\            * TIM_OCMODE_ACTIVE
*\*\            * TIM_OCMODE_INACTIVE
*\*\            * TIM_OCMODE_TOGGLE
*\*\            * TIM_FORCED_ACTION_INACTIVE
*\*\            * TIM_FORCED_ACTION_ACTIVE
*\*\            * TIM_OCMODE_PWM1
*\*\            * TIM_OCMODE_PWM2
*\*\            * TIM_OCMODE_OPMOD_RETRIG1
*\*\            * TIM_OCMODE_OPMOD_RETRIG2
*\*\            * TIM_OCMODE_COMBI_PWM1
*\*\            * TIM_OCMODE_COMBI_PWM2
*\*\          - OutputState
*\*\            * TIM_OUTPUT_STATE_DISABLE
*\*\            * TIM_OUTPUT_STATE_ENABLE
*\*\          - OutputNState
*\*\            * TIM_OUTPUT_NSTATE_DISABLE
*\*\            * TIM_OUTPUT_NSTATE_ENABLE
*\*\          - Pulse
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - OCPolarity
*\*\            * TIM_OC_POLARITY_HIGH
*\*\            * TIM_OC_POLARITY_LOW
*\*\          - OCNPolarity
*\*\            * TIM_OCN_POLARITY_HIGH
*\*\            * TIM_OCN_POLARITY_LOW
*\*\          - OCIdleState
*\*\            * TIM_OC_IDLE_STATE_SET
*\*\            * TIM_OC_IDLE_STATE_RESET
*\*\          - OCNIdleState
*\*\            * TIM_OCN_IDLE_STATE_SET
*\*\            * TIM_OCN_IDLE_STATE_RESET
*\*\return  none
**/
void TIM_InitOcStruct(OCInitType* TIM_OCInitStruct)
{
    /* Set the default configuration */
    TIM_OCInitStruct->OCMode       = TIM_OCMODE_TIMING;
    TIM_OCInitStruct->OutputState  = TIM_OUTPUT_STATE_DISABLE;
    TIM_OCInitStruct->OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
    TIM_OCInitStruct->Pulse        = 0x00000000;
    TIM_OCInitStruct->OCPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStruct->OCNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStruct->OCIdleState  = TIM_OC_IDLE_STATE_RESET;
    TIM_OCInitStruct->OCNIdleState = TIM_OCN_IDLE_STATE_RESET;
}

/**
*\*\name    TIM_InitIcStruct
*\*\fun     Fills each TIM_ICInitStruct member with its default value.
*\*\param   TIM_ICInitStruct: refer to the definition of TIM_ICInitType
*\*\          - Channel
*\*\            * TIM_CH_1
*\*\            * TIM_CH_2
*\*\            * TIM_CH_3
*\*\            * TIM_CH_4
*\*\          - ICPolarity
*\*\            * TIM_IC_POLARITY_RISING
*\*\            * TIM_IC_POLARITY_FALLING
*\*\          - ICSelection
*\*\            * TIM_IC_SELECTION_DIRECTTI
*\*\            * TIM_IC_SELECTION_INDIRECTTI
*\*\            * TIM_IC_SELECTION_TRC
*\*\          - ICPrescaler
*\*\            * TIM_IC_PSC_DIV1
*\*\            * TIM_IC_PSC_DIV2
*\*\            * TIM_IC_PSC_DIV4
*\*\            * TIM_IC_PSC_DIV8
*\*\          - ICFilter
*\*\            * ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_InitIcStruct(TIM_ICInitType* TIM_ICInitStruct)
{
    /* Set the default configuration */
    TIM_ICInitStruct->Channel     = TIM_CH_1;
    TIM_ICInitStruct->ICPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStruct->ICSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStruct->ICPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStruct->ICFilter    = 0x00000000;
}

/**
*\*\name    TIM_InitBkdtStruct
*\*\fun     Fills each TIM_BDTRInitStruct member with its default value.
*\*\param   TIM_BDTRInitStruct: refer to the definition of TIM_BDTRInitType
*\*\          - OSSRState
*\*\            * TIM_OSSR_STATE_ENABLE
*\*\            * TIM_OSSR_STATE_DISABLE
*\*\          - OSSIState
*\*\            * TIM_OSSI_STATE_ENABLE
*\*\            * TIM_OSSI_STATE_DISABLE
*\*\          - LOCKLevel
*\*\            * TIM_LOCK_LEVEL_OFF
*\*\            * TIM_LOCK_LEVEL_1
*\*\            * TIM_LOCK_LEVEL_2
*\*\            * TIM_LOCK_LEVEL_3
*\*\          - DeadTime
*\*\            * DeadTime can be a number between 0x00 and 0xFF
*\*\          - Break
*\*\            * TIM_BREAK_IN_ENABLE
*\*\            * TIM_BREAK_BID_DISABLE
*\*\          - BreakPolarity
*\*\            * TIM_BREAK_POLARITY_LOW
*\*\            * TIM_BREAK_POLARITY_HIGH
*\*\          - Bidirection
*\*\            * TIM_BREAK_BID_ENABLE
*\*\            * TIM_BREAK_BID_DISABLE
*\*\          - AutomaticOutput
*\*\            * TIM_AUTO_OUTPUT_ENABLE
*\*\            * TIM_AUTO_OUTPUT_DISABLE
*\*\          - Break2
*\*\            * TIM_BREAK2_IN_ENABLE
*\*\            * TIM_BREAK2_IN_DISABLE
*\*\          - Break2Polarity
*\*\            * TIM_BREAK2_POLARITY_LOW
*\*\            * TIM_BREAK2_POLARITY_HIGH
*\*\          - Bidirection2
*\*\            * TIM_BREAK2_BID_ENABLE
*\*\            * TIM_BREAK2_BID_DISABLE
*\*\return  none
**/
void TIM_InitBkdtStruct(TIM_BDTRInitType* TIM_BDTRInitStruct)
{
    /* Set the default configuration */
    TIM_BDTRInitStruct->OSSRState       = TIM_OSSR_STATE_DISABLE;
    TIM_BDTRInitStruct->OSSIState       = TIM_OSSI_STATE_DISABLE;
    TIM_BDTRInitStruct->LOCKLevel       = TIM_LOCK_LEVEL_OFF;
    TIM_BDTRInitStruct->DeadTime        = 0x00000000;
    TIM_BDTRInitStruct->Break           = TIM_BREAK_IN_DISABLE;
    TIM_BDTRInitStruct->BreakPolarity   = TIM_BREAK_POLARITY_LOW;
    TIM_BDTRInitStruct->Bidirection     = TIM_BREAK_BID_DISABLE;
    TIM_BDTRInitStruct->AutomaticOutput = TIM_AUTO_OUTPUT_DISABLE;
    TIM_BDTRInitStruct->Break2          = TIM_BREAK2_IN_DISABLE;
    TIM_BDTRInitStruct->Break2Polarity  = TIM_BREAK2_POLARITY_LOW;
    TIM_BDTRInitStruct->Bidirection2    = TIM_BREAK2_BID_DISABLE;
}

/**
*\*\name    TIM_Enable
*\*\fun     Enables or disables the specified TIM peripheral.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_Enable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the TIM Counter */
        TIMx->CTRL1 |= (uint32_t)TIM_CTRL1_CNTEN;
    }
    else
    {
        /* Disable the TIM Counter */
        TIMx->CTRL1 &= (uint32_t)(~TIM_CTRL1_CNTEN);
    }
}

/**
*\*\name    TIM_EnableCtrlPwmOutputs
*\*\fun     Enables or disables the TIM peripheral Main Outputs.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_EnableCtrlPwmOutputs(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the TIM Main Output */
        TIMx->BKDT |= (uint32_t)TIM_BKDT_MOEN;
    }
    else
    {
        /* Disable the TIM Main Output */
        TIMx->BKDT &= (uint32_t)(~TIM_BKDT_MOEN);
    }
}

/**
*\*\name    TIM_ConfigInt
*\*\fun     Enables or disables the specified TIM interrupts.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_IT:
*\*\          - TIM_INT_CC1
*\*\          - TIM_INT_CC2
*\*\          - TIM_INT_CC3
*\*\          - TIM_INT_CC4
*\*\          - TIM_INT_CC5
*\*\          - TIM_INT_CC6
*\*\          - TIM_INT_CC7
*\*\          - TIM_INT_CC8
*\*\          - TIM_INT_CC9
*\*\          - TIM_INT_UPDATE
*\*\          - TIM_INT_TRIG
*\*\          - TIM_INT_BREAK
*\*\          - TIM_INT_COM
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_ConfigInt(TIM_Module* TIMx, uint32_t TIM_IT, FunctionalState Cmd)
{

    if (Cmd != DISABLE)
    {
        /* Enable the Interrupt sources */
        TIMx->DINTEN |= (uint32_t)TIM_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        TIMx->DINTEN &= (uint32_t)(~(uint32_t)TIM_IT);
    }
}

/**
*\*\name    TIM_GenerateEvent
*\*\fun     Configures the TIMx event to be generate by software.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_EventSource:
*\*\          - TIM_EVT_SRC_CC1
*\*\          - TIM_EVT_SRC_CC2
*\*\          - TIM_EVT_SRC_CC3
*\*\          - TIM_EVT_SRC_CC4
*\*\          - TIM_EVT_SRC_UPDATE
*\*\          - TIM_EVT_SRC_COM
*\*\          - TIM_EVT_SRC_TRIG
*\*\          - TIM_EVT_SRC_BREAK
*\*\          - TIM_EVT_SRC_BREAK2
*\*\return  none
**/
void TIM_GenerateEvent(TIM_Module* TIMx, uint32_t TIM_EventSource)
{
    /* Set the event sources */
    TIMx->EVTGEN = TIM_EventSource;
}

/**
*\*\name    TIM_ConfigDma
*\*\fun     Configures the TIMx's DMA interface.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_DMABase:
*\*\          - TIM_DMABASE_CTRL1
*\*\          - TIM_DMABASE_CTRL2
*\*\          - TIM_DMABASE_STS
*\*\          - TIM_DMABASE_EVTGEN
*\*\          - TIM_DMABASE_SMCTRL
*\*\          - TIM_DMABASE_DMAINTEN
*\*\          - TIM_DMABASE_CAPCMPMOD1
*\*\          - TIM_DMABASE_CAPCMPMOD2
*\*\          - TIM_DMABASE_CAPCMPMOD3
*\*\          - TIM_DMABASE_CAPCMPEN
*\*\          - TIM_DMABASE_CAPCMPDAT1
*\*\          - TIM_DMABASE_CAPCMPDAT2
*\*\          - TIM_DMABASE_CAPCMPDAT3
*\*\          - TIM_DMABASE_CAPCMPDAT4
*\*\          - TIM_DMABASE_CAPCMPDAT5
*\*\          - TIM_DMABASE_CAPCMPDAT6
*\*\          - TIM_DMABASE_PSC
*\*\          - TIM_DMABASE_AR
*\*\          - TIM_DMABASE_CNT
*\*\          - TIM_DMABASE_REPCNT
*\*\          - TIM_DMABASE_BKDT
*\*\          - TIM_DMABASE_CAPCMPDAT7
*\*\          - TIM_DMABASE_CAPCMPDAT8
*\*\          - TIM_DMABASE_CAPCMPDAT9
*\*\          - TIM_DMABASE_BKFR
*\*\          - TIM_DMABASE_C1FILT
*\*\          - TIM_DMABASE_C2FILT
*\*\          - TIM_DMABASE_C3FILT
*\*\          - TIM_DMABASE_C4FILT
*\*\          - TIM_DMABASE_FILTO
*\*\          - TIM_DMABASE_INSEL
*\*\          - TIM_DMABASE_AF1
*\*\          - TIM_DMABASE_AF2
*\*\          - TIM_DMABASE_BKFR2
*\*\          - TIM_DMABASE_SLIDFPSC
*\*\param   TIM_DMABurstLength:
*\*\          - This parameter can be one value between:
*\*\            TIM_DMABURST_LENGTH_1TRANSFER and TIM_DMABURST_LENGTH_35TRANSFERS.
*\*\return  none
**/
void TIM_ConfigDma(TIM_Module* TIMx, uint32_t TIM_DMABase, uint32_t TIM_DMABurstLength)
{
    /* Set the DMA Base and the DMA Burst Length */
    TIMx->DCTRL = TIM_DMABase | TIM_DMABurstLength;
}

/**
*\*\name    TIM_EnableDma
*\*\fun     Enables or disables the TIMx's DMA Requests.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_DMASource:
*\*\          - TIM_DMA_CC1
*\*\          - TIM_DMA_CC2
*\*\          - TIM_DMA_CC3
*\*\          - TIM_DMA_CC4
*\*\          - TIM_DMA_UPDATE
*\*\          - TIM_DMA_COM
*\*\          - TIM_DMA_TRIG
*\*\param   Cmd:
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return  none
**/
void TIM_EnableDma(TIM_Module* TIMx, uint32_t TIM_DMASource, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA sources */
        TIMx->DINTEN |= (uint32_t)TIM_DMASource;
    }
    else
    {
        /* Disable the DMA sources */
        TIMx->DINTEN &= (uint32_t)(~((uint32_t)TIM_DMASource));
    }
}

/**
*\*\name    TIM_ConfigInternalClk
*\*\fun     Configures the TIMx internal Clock
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  none
**/
void TIM_ConfigInternalClk(TIM_Module* TIMx)
{
    /* Disable slave mode to clock the prescaler directly with the internal clock */
    TIMx->SMCTRL &= (uint32_t)(~((uint32_t)TIM_SMCTRL_SMSEL));
}

/**
*\*\name    TIM_ConfigInternalTrigToExt
*\*\fun     Configures the TIMx Internal Trigger as External Clock
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_InputTriggerSource:
*\*\          - TIM_TRIG_SEL_IN_TR0
*\*\          - TIM_TRIG_SEL_IN_TR1
*\*\          - TIM_TRIG_SEL_IN_TR2
*\*\          - TIM_TRIG_SEL_IN_TR3
*\*\          - TIM_TRIG_SEL_IN_TR4
*\*\          - TIM_TRIG_SEL_IN_TR5
*\*\          - TIM_TRIG_SEL_IN_TR6
*\*\          - TIM_TRIG_SEL_IN_TR7
*\*\          - TIM_TRIG_SEL_IN_TR8
*\*\          - TIM_TRIG_SEL_IN_TR9
*\*\          - TIM_TRIG_SEL_IN_TR10
*\*\          - TIM_TRIG_SEL_IN_TR11
*\*\          - TIM_TRIG_SEL_IN_TR12
*\*\          - TIM_TRIG_SEL_IN_TR13
*\*\          - TIM_TRIG_SEL_IN_TR14
*\*\return  none
**/
void TIM_ConfigInternalTrigToExt(TIM_Module* TIMx, uint32_t TIM_InputTriggerSource)
{
    /* Select the Internal Trigger */
    TIM_SelectInputTrig(TIMx, TIM_InputTriggerSource);
    /* Select the External clock mode1 */
    TIMx->SMCTRL |= (uint32_t)TIM_SLAVE_MODE_EXT1;
}

/**
*\*\name    TIM_ConfigExtTrigAsClk
*\*\fun     Configures the TIMx Trigger as External Clock
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_TIxExternalCLKSource:
*\*\          - TIM_TRIG_SEL_TI1F_ED
*\*\          - TIM_TRIG_SEL_TI1FP1
*\*\          - TIM_TRIG_SEL_TI2FP2
*\*\param   ICPolarity
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   ICFilter
*\*\          - ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_ConfigExtTrigAsClk(TIM_Module* TIMx, uint32_t TIM_TIxExternalCLKSource, uint32_t IcPolarity, uint32_t ICFilter)
{
    /* Configure the Timer Input Clock Source */
    if (TIM_TIxExternalCLKSource == TIM_TRIG_SEL_TI2FP2)
    {
        ConfigTI2(TIMx, IcPolarity, TIM_IC_SELECTION_DIRECTTI, ICFilter);
    }
    else
    {
        ConfigTI1(TIMx, IcPolarity, TIM_IC_SELECTION_DIRECTTI, ICFilter);
    }

    /* Select the Trigger source */
    TIM_SelectInputTrig(TIMx, TIM_TIxExternalCLKSource);
    /* Select the External clock mode1 */
    TIMx->SMCTRL |= (uint32_t)TIM_SLAVE_MODE_EXT1;
}

/**
*\*\name    TIM_ConfigExtClkMode1
*\*\fun     Configures the External clock Mode1
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ETRInputSource:
*\*\          - TIM_CAPETRSEL_0
*\*\          - TIM_CAPETRSEL_1
*\*\          - TIM_CAPETRSEL_2
*\*\          - TIM_CAPETRSEL_3
*\*\          - TIM_CAPETRSEL_4
*\*\          - TIM_CAPETRSEL_5
*\*\          - TIM_CAPETRSEL_6
*\*\          - TIM_CAPETRSEL_7
*\*\          - TIM_CAPETRSEL_8
*\*\          - TIM_CAPETRSEL_9
*\*\          - TIM_CAPETRSEL_10
*\*\          - TIM_CAPETRSEL_11
*\*\          - TIM_CAPETRSEL_12
*\*\          - TIM_CAPETRSEL_13
*\*\param   TIM_ExtTRGPrescaler:
*\*\          - TIM_EXT_TRG_PSC_OFF
*\*\          - TIM_EXT_TRG_PSC_DIV2
*\*\          - TIM_EXT_TRG_PSC_DIV4
*\*\          - TIM_EXT_TRG_PSC_DIV8
*\*\param   TIM_ExtTRGPolarity
*\*\          - TIM_EXT_TRIG_POLARITY_INVERTED
*\*\          - TIM_EXT_TRIG_POLARITY_NONINVERTED
*\*\param   ExtTRGFilter
*\*\          - ExtTRGFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_ConfigExtClkMode1(TIM_Module* TIMx, uint32_t TIM_ETRInputSource, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
    uint32_t tmpsmctrl ;
    /* Configure the ETR input source */
    TIM_SelectETRInputSource(TIMx, TIM_ETRInputSource);
    /* Configure the ETR Clock source */
    TIM_ConfigExtTrig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

    /* Get the TIMx SMCTRL register value */
    tmpsmctrl = TIMx->SMCTRL;
    /* Reset the SMS Bits */
    tmpsmctrl &= (uint32_t)(~((uint32_t)TIM_SMCTRL_SMSEL));
    /* Select the External clock mode1 */
    tmpsmctrl |= (uint32_t)TIM_SLAVE_MODE_EXT1;
    /* Select the Trigger selection : ETRF */
    tmpsmctrl &= (uint32_t)(~((uint32_t)TIM_SMCTRL_TSEL));
    tmpsmctrl |= (uint32_t)TIM_TRIG_SEL_ETRF;
    /* Write to TIMx SMCTRL */
    TIMx->SMCTRL = tmpsmctrl;
}

/**
*\*\name    TIM_ConfigExtClkMode2
*\*\fun     Configures the External clock Mode2
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ETRInputSource:
*\*\          - TIM_CAPETRSEL_0
*\*\          - TIM_CAPETRSEL_1
*\*\          - TIM_CAPETRSEL_2
*\*\          - TIM_CAPETRSEL_3
*\*\          - TIM_CAPETRSEL_4
*\*\          - TIM_CAPETRSEL_5
*\*\          - TIM_CAPETRSEL_6
*\*\          - TIM_CAPETRSEL_7
*\*\          - TIM_CAPETRSEL_8
*\*\          - TIM_CAPETRSEL_9
*\*\          - TIM_CAPETRSEL_10
*\*\          - TIM_CAPETRSEL_11
*\*\          - TIM_CAPETRSEL_12
*\*\          - TIM_CAPETRSEL_13
*\*\param   TIM_ExtTRGPrescaler:
*\*\          - TIM_EXT_TRG_PSC_OFF
*\*\          - TIM_EXT_TRG_PSC_DIV2
*\*\          - TIM_EXT_TRG_PSC_DIV4
*\*\          - TIM_EXT_TRG_PSC_DIV8
*\*\param   TIM_ExtTRGPolarity
*\*\          - TIM_EXT_TRIG_POLARITY_INVERTED
*\*\          - TIM_EXT_TRIG_POLARITY_NONINVERTED
*\*\param   ExtTRGFilter
*\*\          - ExtTRGFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_ConfigExtClkMode2(TIM_Module* TIMx, uint32_t TIM_ETRInputSource, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
    /* Configure the ETR input source */
    TIM_SelectETRInputSource(TIMx, TIM_ETRInputSource);
    /* Configure the ETR Clock source */
    TIM_ConfigExtTrig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
    /* Enable the External clock mode2 */
    TIMx->SMCTRL |= (uint32_t)TIM_SMCTRL_EXCEN;
}

/**
*\*\name    TIM_ConfigPrescaler
*\*\fun     Configures the TIMx Prescaler.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   Prescaler:
*\*\          - 0x0000 ~ 0xFFFF
*\*\param   TIM_PSCReloadMode
*\*\          - TIM_PSC_RELOAD_MODE_UPDATE
*\*\          - TIM_PSC_RELOAD_MODE_IMMEDIATE
*\*\return  none
**/
void TIM_ConfigPrescaler(TIM_Module* TIMx, uint32_t Prescaler, uint32_t TIM_PSCReloadMode)
{
    /* Set the Prescaler value */
    TIMx->PSC = Prescaler;
    /* Set or reset the UG Bit */
    TIMx->EVTGEN = TIM_PSCReloadMode;
}

/**
*\*\name    TIM_ConfigCntMode
*\*\fun     Specifies the TIMx Counter Mode to be used.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   CntMode
*\*\          - TIM_CNT_MODE_UP
*\*\          - TIM_CNT_MODE_DOWN
*\*\          - TIM_CNT_MODE_CENTER_ALIGN1
*\*\          - TIM_CNT_MODE_CENTER_ALIGN2
*\*\          - TIM_CNT_MODE_CENTER_ALIGN3
*\*\return  none
**/
void TIM_ConfigCntMode(TIM_Module* TIMx, uint32_t CntMode)
{
    uint32_t tmpctrl1 ;
    tmpctrl1 = TIMx->CTRL1;
    /* Reset the CMS and DIR Bits */
    tmpctrl1 &= (uint32_t)(~((uint32_t)(TIM_CTRL1_DIR | TIM_CTRL1_CAMSEL)));
    /* Set the Counter Mode */
    tmpctrl1 |= (uint32_t)CntMode;
    /* Write to TIMx CTRL1 register */
    TIMx->CTRL1 = tmpctrl1;
}

/**
*\*\name    TIM_ConfigEncoderInterface
*\*\fun     Configures the TIMx Encoder Interface.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_EncoderMode
*\*\          - TIM_ENCODE_QUA_MODE_TI1
*\*\          - TIM_ENCODE_QUA_MODE_TI2
*\*\          - TIM_ENCODE_QUA_MODE_TI12
*\*\          - TIM_ENCODE_QUA_MODE_SINGLE_TI1
*\*\          - TIM_ENCODE_QUA_MODE_SINGLE_TI2
*\*\          - TIM_ENCODE_DUL_CLKPLUS_MODE1
*\*\          - TIM_ENCODE_DUL_CLKPLUS_MODE2
*\*\          - TIM_ENCODE_SINGLE_CLKPLUS_MODE1
*\*\          - TIM_ENCODE_SINGLE_CLKPLUS_MODE2
*\*\param   TIM_IC1Polarity
*\*\          - TIM_IC_POLARITY_FALLING
*\*\          - TIM_IC_POLARITY_RISING
*\*\param   TIM_IC2Polarity
*\*\          - TIM_IC_POLARITY_FALLING
*\*\          - TIM_IC_POLARITY_RISING
*\*\return  none
**/
void TIM_ConfigEncoderInterface(TIM_Module* TIMx, uint32_t TIM_EncoderMode, uint32_t TIM_IC1Polarity, uint32_t TIM_IC2Polarity)
{
    uint32_t tmpsmctrl  ;
    uint32_t tmpccmodx ;
    uint32_t tmpccen  ;

    /* Get the TIMx SMCTRL register value */
    tmpsmctrl = TIMx->SMCTRL;

    /* Get the TIMx CCMOD1 register value */
    tmpccmodx = TIMx->CCMOD1;

    /* Get the TIMx CCEN register value */
    tmpccen = TIMx->CCEN;

    /* Set the encoder Mode */
    tmpsmctrl &= (uint32_t)(~((uint32_t)TIM_SMCTRL_SMSEL));
    tmpsmctrl |= (uint32_t)TIM_EncoderMode;

    /* Select the Capture Compare 1 and the Capture Compare 2 as input */
    tmpccmodx &= (uint32_t)((~TIM_CCMOD1_CC1SEL) & (~TIM_CCMOD1_CC2SEL));
    tmpccmodx |= (uint32_t)(TIM_CCMOD1_CC1SEL_0 | TIM_CCMOD1_CC2SEL_0);

    /* Set the TI1 and the TI2 Polarities */
    tmpccen &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_CCEN_CC1P)) & ((uint32_t) ~((uint32_t)TIM_CCEN_CC2P)));
    tmpccen |= (uint32_t)(TIM_IC1Polarity | (uint32_t)(TIM_IC2Polarity << (uint32_t)4));

    /* Write to TIMx SMCTRL */
    TIMx->SMCTRL = tmpsmctrl;
    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = tmpccmodx;
    /* Write to TIMx CCEN */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigForcedOc1
*\*\fun     Forces the TIMx output 1 waveform to active or inactive level.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ForcedAction
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\return  none
**/
void TIM_ConfigForcedOc1(TIM_Module* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmodx;
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC1M Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC1MD);
    /* Configure The Forced output Mode */
    tmpccmodx |= (uint32_t)TIM_ForcedAction;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigForcedOc2
*\*\fun     Forces the TIMx output 2 waveform to active or inactive level.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ForcedAction
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\return  none
**/
void TIM_ConfigForcedOc2(TIM_Module* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC2M Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC2MD);
    /* Configure The Forced output Mode */
    tmpccmodx |= (uint32_t)(TIM_ForcedAction << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigForcedOc3
*\*\fun     Forces the TIMx output 3 waveform to active or inactive level.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ForcedAction
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\return  none
**/
void TIM_ConfigForcedOc3(TIM_Module* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC1M Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC3MD);
    /* Configure The Forced output Mode */
    tmpccmodx |= (uint32_t)TIM_ForcedAction;
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigForcedOc4
*\*\fun     Forces the TIMx output 4 waveform to active or inactive level.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ForcedAction
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\return  none
**/
void TIM_ConfigForcedOc4(TIM_Module* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC2M Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC4MD);
    /* Configure The Forced output Mode */
    tmpccmodx |= (uint32_t)(TIM_ForcedAction << 8);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigForcedOc5
*\*\fun     Forces the TIMx output 5 waveform to active or inactive level.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ForcedAction
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\return  none
**/
void TIM_ConfigForcedOc5(TIM_Module* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC2M Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC5MD);
    /* Configure The Forced output Mode */
    tmpccmodx |= (uint32_t)(TIM_ForcedAction);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigForcedOc6
*\*\fun     Forces the TIMx output 6 waveform to active or inactive level.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_ForcedAction
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\return  none
**/
void TIM_ConfigForcedOc6(TIM_Module* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC2M Bits */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC6MD);
    /* Configure The Forced output Mode */
    tmpccmodx |= (uint32_t)(TIM_ForcedAction << 8);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigArPreload
*\*\fun     Enables or disables TIMx peripheral Preload register on AR.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_ConfigArPreload(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the AR Preload Bit */
        TIMx->CTRL1 |= (uint32_t)TIM_CTRL1_ARPEN;
    }
    else
    {
        /* Reset the AR Preload Bit */
        TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_CTRL1_ARPEN));
    }
}

/**
*\*\name    TIM_SelectComEvt
*\*\fun     Selects the TIM peripheral Commutation event.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_SelectComEvt(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the CCUSEL Bit */
        TIMx->CTRL2 |= (uint32_t)TIM_CTRL2_CCUSEL;
    }
    else
    {
        /* Reset the CCUSEL Bit */
        TIMx->CTRL2 &= (uint32_t)(~((uint32_t)TIM_CTRL2_CCUSEL));
    }
}

/**
*\*\name    TIM_SelectCapCmpDmaSrc
*\*\fun     Selects the TIMx peripheral Capture Compare DMA source.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_SelectCapCmpDmaSrc(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the CCDSEL Bit */
        TIMx->CTRL2 |= (uint32_t)TIM_CTRL2_CCDSEL;
    }
    else
    {
        /* Reset the CCDSEL Bit */
        TIMx->CTRL2 &= (uint32_t)(~((uint32_t)TIM_CTRL2_CCDSEL));
    }
}

/**
*\*\name    TIM_EnableCapCmpPreloadControl
*\*\fun     Sets or Resets the TIM peripheral Capture Compare Preload Control bit.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_EnableCapCmpPreloadControl(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the CCPC Bit */
        TIMx->CTRL2 |= (uint32_t)TIM_CTRL2_CCPCTL;
    }
    else
    {
        /* Reset the CCPC Bit */
        TIMx->CTRL2 &= (uint32_t)(~((uint32_t)TIM_CTRL2_CCPCTL));
    }
}

/**
*\*\name    TIM_ConfigOc1Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT1.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc1Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC1PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC1PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)TIM_OCPreload;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc2Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT2.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc2Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC2PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC2PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc3Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT3.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc3Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC3PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC3PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)TIM_OCPreload;
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc4Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT4.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc4Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC4PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC4PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload << 8);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc5Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT5.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc5Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC5PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC5PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc6Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT6.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc6Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC6PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC6PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload << 8);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc7Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT6.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc7Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC7PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC7PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload << 14);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc8Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT6.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc8Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC8PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC8PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload << 18);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc9Preload
*\*\fun     Enables or disables the TIMx peripheral Preload register on CCDAT6.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_ConfigOc9Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmodx;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC9PEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC9PEN);
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmodx |= (uint32_t)(TIM_OCPreload << 22);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc1Fast
*\*\fun     Configures the TIMx Output Compare 1 Fast feature.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_FAST_ENABLE
*\*\          - TIM_OC_FAST_DISABLE
*\*\return  none
**/
void TIM_ConfigOc1Fast(TIM_Module* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmodx ;
    /* Get the TIMx CCMOD1 register value */
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC1FEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC1FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmodx |= (uint32_t)TIM_OCFast;
    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc2Fast
*\*\fun     Configures the TIMx Output Compare 2 Fast feature.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_FAST_ENABLE
*\*\          - TIM_OC_FAST_DISABLE
*\*\return  none
**/
void TIM_ConfigOc2Fast(TIM_Module* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmodx ;
    /* Get the TIMx CCMOD1 register value */
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC2FEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC2FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmodx |= (uint32_t)(TIM_OCFast << 8);
    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc3Fast
*\*\fun     Configures the TIMx Output Compare 3 Fast feature.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_FAST_ENABLE
*\*\          - TIM_OC_FAST_DISABLE
*\*\return  none
**/
void TIM_ConfigOc3Fast(TIM_Module* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmodx ;
    /* Get the TIMx CCMOD2 register value */
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC3FEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC3FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmodx |= (uint32_t)TIM_OCFast;
    /* Write to TIMx CCMOD2 */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc4Fast
*\*\fun     Configures the TIMx Output Compare 4 Fast feature.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_FAST_ENABLE
*\*\          - TIM_OC_FAST_DISABLE
*\*\return  none
**/
void TIM_ConfigOc4Fast(TIM_Module* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmodx ;
    /* Get the TIMx CCMOD2 register value */
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC4FEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC4FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmodx |= (uint32_t)(TIM_OCFast << 8);
    /* Write to TIMx CCMOD2 */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc5Fast
*\*\fun     Configures the TIMx Output Compare 5 Fast feature.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_FAST_ENABLE
*\*\          - TIM_OC_FAST_DISABLE
*\*\return  none
**/
void TIM_ConfigOc5Fast(TIM_Module* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmodx ;
    /* Get the TIMx CCMOD2 register value */
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC4FEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC5FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmodx |= (uint32_t)(TIM_OCFast);
    /* Write to TIMx CCMOD3 */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ConfigOc6Fast
*\*\fun     Configures the TIMx Output Compare 6 Fast feature.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_FAST_ENABLE
*\*\          - TIM_OC_FAST_DISABLE
*\*\return  none
**/
void TIM_ConfigOc6Fast(TIM_Module* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmodx ;
    /* Get the TIMx CCMOD2 register value */
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC4FEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC6FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmodx |= (uint32_t)(TIM_OCFast << 8);
    /* Write to TIMx CCMOD3 */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOc1Ref
*\*\fun     Clears or safeguards the OCREF1 signal on an external event
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_CLR_ENABLE
*\*\          - TIM_OC_CLR_DISABLE
*\*\return  none
**/
void TIM_ClrOc1Ref(TIM_Module* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC1CEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC1CEN);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmodx |= (uint32_t)TIM_OCClear;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOc2Ref
*\*\fun     Clears or safeguards the OCREF2 signal on an external event
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_CLR_ENABLE
*\*\          - TIM_OC_CLR_DISABLE
*\*\return  none
**/
void TIM_ClrOc2Ref(TIM_Module* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD1;
    /* Reset the OC2CEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD1_OC2CEN);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmodx |= (uint32_t)(TIM_OCClear << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOc3Ref
*\*\fun     Clears or safeguards the OCREF3 signal on an external event
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_CLR_ENABLE
*\*\          - TIM_OC_CLR_DISABLE
*\*\return  none
**/
void TIM_ClrOc3Ref(TIM_Module* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC3CEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC3CEN);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmodx |= (uint32_t)TIM_OCClear;
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOc4Ref
*\*\fun     Clears or safeguards the OCREF4 signal on an external event
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_CLR_ENABLE
*\*\          - TIM_OC_CLR_DISABLE
*\*\return  none
**/
void TIM_ClrOc4Ref(TIM_Module* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD2;
    /* Reset the OC4CEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD2_OC4CEN);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmodx |= (uint32_t)(TIM_OCClear << 8);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOc5Ref
*\*\fun     Clears or safeguards the OCREF5 signal on an external event
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_CLR_ENABLE
*\*\          - TIM_OC_CLR_DISABLE
*\*\return  none
**/
void TIM_ClrOc5Ref(TIM_Module* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC4CEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC5CEN);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmodx |= (uint32_t)(TIM_OCClear);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOc6Ref
*\*\fun     Clears or safeguards the OCREF6 signal on an external event
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_CLR_ENABLE
*\*\          - TIM_OC_CLR_DISABLE
*\*\return  none
**/
void TIM_ClrOc6Ref(TIM_Module* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmodx ;
    tmpccmodx = TIMx->CCMOD3;
    /* Reset the OC4CEN Bit */
    tmpccmodx &= (uint32_t)(~TIM_CCMOD3_OC6CEN);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmodx |= (uint32_t)(TIM_OCClear << 8);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = tmpccmodx;
}

/**
*\*\name    TIM_ClrOcRefInputSource
*\*\fun     Set the OCREF clear input source
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   OCRefClearInputSelect
*\*\          - TIM_ETRSEL
*\*\          - TIM_CLRSEL
*\*\param   OCRefClearInputSource
*\*\          - TIM_CAPETRSEL_0
*\*\          - TIM_CAPETRSEL_1
*\*\          - TIM_CAPETRSEL_2
*\*\          - TIM_CAPETRSEL_3
*\*\          - TIM_CAPETRSEL_4
*\*\          - TIM_CAPETRSEL_5
*\*\          - TIM_CAPETRSEL_6
*\*\          - TIM_CAPETRSEL_7
*\*\          - TIM_CAPETRSEL_8
*\*\          - TIM_CAPETRSEL_9
*\*\          - TIM_CAPETRSEL_10
*\*\          - TIM_CAPETRSEL_11
*\*\          - TIM_CAPETRSEL_12
*\*\          - TIM_CAPETRSEL_13
*\*\          - TIM_OCCLRSEL_0
*\*\          - TIM_OCCLRSEL_1
*\*\          - TIM_OCCLRSEL_2
*\*\          - TIM_OCCLRSEL_3
*\*\          - TIM_OCCLRSEL_4
*\*\          - TIM_OCCLRSEL_5
*\*\          - TIM_OCCLRSEL_6
*\*\          - TIM_OCCLRSEL_7
*\*\return  none
**/
void TIM_ClrOcRefInputSource(TIM_Module* TIMx, uint32_t OCRefClearInputSelect, uint32_t OCRefClearInputSource)
{
    uint32_t tmpctrl1 ;
    uint32_t tmpinsel ;
    /* Get the value of TIMx_CTRL1 and TIMx_INSEL */
    tmpctrl1 = TIMx->CTRL1;
    tmpinsel = TIMx->INSEL;
    /* Reset the CTRL1_CLRSEL\INSEL_ETRS\INSEL_CLRS bits */
    tmpctrl1 &= (uint32_t)(~TIM_CTRL1_CLRSEL);
    tmpinsel &= (uint32_t)(~TIM_INSEL_ETRS);
    tmpinsel &= (uint32_t)(~TIM_INSEL_CLRS);

    if (OCRefClearInputSelect)
    {
        /* CLR select capture in */
        tmpctrl1 |= (uint32_t)TIM_OCCLRSEL_COMP;
        tmpinsel |= (uint32_t)OCRefClearInputSource;
    }
    else
    {
        /* ETR select capture in */
        tmpinsel |= (uint32_t)OCRefClearInputSource;
    }

    TIMx->CTRL1 = tmpctrl1;
    TIMx->INSEL = tmpinsel;
}

/**
*\*\name    TIM_ConfigOc1Polarity
*\*\fun     Configures the TIMx channel 1 polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_POLARITY_HIGH
*\*\          - TIM_OC_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc1Polarity(TIM_Module* TIMx, uint32_t OcPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC1P Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1P));
    tmpccen |= (uint32_t)OcPolarity;
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc1NPolarity
*\*\fun     Configures the TIMx channel 1N polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OCN_POLARITY_HIGH
*\*\          - TIM_OCN_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc1NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC1NP Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1NP));
    tmpccen |= (uint32_t)OcNPolarity;
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc2Polarity
*\*\fun     Configures the TIMx channel 2 polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_POLARITY_HIGH
*\*\          - TIM_OC_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc2Polarity(TIM_Module* TIMx, uint32_t OcPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC2P Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2P));
    tmpccen |= (uint32_t)(OcPolarity << 4);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc2NPolarity
*\*\fun     Configures the TIMx channel 2N polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OCN_POLARITY_HIGH
*\*\          - TIM_OCN_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc2NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC2NP Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2NP));
    tmpccen |= (uint32_t)(OcNPolarity << 4);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc3Polarity
*\*\fun     Configures the TIMx channel 3 polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_POLARITY_HIGH
*\*\          - TIM_OC_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc3Polarity(TIM_Module* TIMx, uint32_t OcPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC3P Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3P));
    tmpccen |= (uint32_t)(OcPolarity << 8);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc3NPolarity
*\*\fun     Configures the TIMx channel 3N polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OCN_POLARITY_HIGH
*\*\          - TIM_OCN_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc3NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC3NP Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3NP));
    tmpccen |= (uint32_t)(OcNPolarity << 8);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc4Polarity
*\*\fun     Configures the TIMx channel 4 polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_POLARITY_HIGH
*\*\          - TIM_OC_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc4Polarity(TIM_Module* TIMx, uint32_t OcPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC4P Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC4P));
    tmpccen |= (uint32_t)(OcPolarity << 12);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc4NPolarity
*\*\fun     Configures the TIMx channel 4N polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OCN_POLARITY_HIGH
*\*\          - TIM_OCN_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc4NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC3NP Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC4NP));
    tmpccen |= (uint32_t)(OcNPolarity << 12);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc5Polarity
*\*\fun     Configures the TIMx channel 5 polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_POLARITY_HIGH
*\*\          - TIM_OC_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc5Polarity(TIM_Module* TIMx, uint32_t OcPolarity)
{
    uint32_t tmpccen;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC5P Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC5P));
    tmpccen |= (uint32_t)(OcPolarity << 16);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_ConfigOc6Polarity
*\*\fun     Configures the TIMx channel 6 polarity.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_OCPreload
*\*\          - TIM_OC_POLARITY_HIGH
*\*\          - TIM_OC_POLARITY_LOW
*\*\return  none
**/
void TIM_ConfigOc6Polarity(TIM_Module* TIMx, uint32_t OcPolarity)
{
    uint32_t tmpccen ;
    tmpccen = TIMx->CCEN;
    /* Set or Reset the CC6P Bit */
    tmpccen &= (uint32_t)(~((uint32_t)TIM_CCEN_CC6P));
    tmpccen |= (uint32_t)(OcPolarity << 20);
    /* Write to TIMx CCEN register */
    TIMx->CCEN = tmpccen;
}

/**
*\*\name    TIM_EnableCapCmpCh
*\*\fun     Enables or disables the TIM Capture Compare Channel x.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Channel
*\*\          - TIM_CH_1
*\*\          - TIM_CH_2
*\*\          - TIM_CH_3
*\*\          - TIM_CH_4
*\*\          - TIM_CH_5
*\*\          - TIM_CH_6
*\*\param   TIM_CCx
*\*\          - TIM_CAP_CMP_ENABLE
*\*\          - TIM_CAP_CMP_DISABLE
*\*\return  none
**/
void TIM_EnableCapCmpCh(TIM_Module* TIMx, uint32_t Channel, uint32_t TIM_CCx)
{
    uint32_t tmp ;
    tmp = CAPCMPEN_CCE_SET << Channel;
    /* Reset the CCxEN Bit */
    TIMx->CCEN &= (uint32_t)(~tmp);
    /* Set or reset the CCxEN Bit */
    TIMx->CCEN |= (uint32_t)(TIM_CCx << Channel);
}

/**
*\*\name    TIM_EnableCapCmpChN
*\*\fun     Enables or disables the TIM Capture Compare Channel xN.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Channel
*\*\          - TIM_CH_1
*\*\          - TIM_CH_2
*\*\          - TIM_CH_3
*\*\          - TIM_CH_4
*\*\param   TIM_CCx
*\*\          - TIM_CAP_CMP_N_ENABLE
*\*\          - TIM_CAP_CMP_N_DISABLE
*\*\return  none
**/
void TIM_EnableCapCmpChN(TIM_Module* TIMx, uint32_t Channel, uint32_t TIM_CCxN)
{
    uint32_t tmp ;
    tmp = CAPCMPEN_CCNE_SET << Channel;
    /* Reset the CCxNEN Bit */
    TIMx->CCEN &= (uint32_t)(~tmp);
    /* Set or reset the CCxNEN Bit */
    TIMx->CCEN |= (uint32_t)(TIM_CCxN << Channel);
}

/**
*\*\name    TIM_SelectOcMode
*\*\fun     Selects the TIM Output Compare Mode.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Channel
*\*\          - TIM_CH_1
*\*\          - TIM_CH_2
*\*\          - TIM_CH_3
*\*\          - TIM_CH_4
*\*\          - TIM_CH_5
*\*\          - TIM_CH_6
*\*\param   OcMode
*\*\          - TIM_OCMODE_TIMING
*\*\          - TIM_OCMODE_ACTIVE
*\*\          - TIM_OCMODE_INACTIVE
*\*\          - TIM_OCMODE_TOGGLE
*\*\          - TIM_OCMODE_PWM1
*\*\          - TIM_OCMODE_PWM2
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\          - TIM_OCMODE_OPMOD_RETRIG1
*\*\          - TIM_OCMODE_OPMOD_RETRIG2
*\*\          - TIM_OCMODE_COMBI_PWM1
*\*\          - TIM_OCMODE_COMBI_PWM2
*\*\return  none
**/
void TIM_SelectOcMode(TIM_Module* TIMx, uint32_t Channel, uint32_t OcMode)
{
    uint32_t tmp  ;
    uint32_t tmp1 ;

    tmp = (uint32_t)TIMx;
    tmp += CAPCMPMOD_OFFSET;

    tmp1 = CAPCMPEN_CCE_SET << Channel;

    /* Disable the Channel: Reset the CCxE Bit */
    TIMx->CCEN &= (uint32_t)(~tmp1);

    if ((Channel == TIM_CH_1) || (Channel == TIM_CH_3) || (Channel == TIM_CH_5))
    {
        tmp += (uint32_t)(Channel >> 1);

        /* Reset the OCxMD bits in the CCMRx register */
        *(__IO uint32_t*)tmp &= (uint32_t) (~((uint32_t)(TIM_CCMOD1_OC1MD | TIM_CCMOD1_OC1MD_3)));

        /* Configure the OCxMD bits in the CCMRx register */
        *(__IO uint32_t*)tmp |= (uint32_t)OcMode;
    }
    else
    {
        tmp += (uint32_t)((Channel - 4) >> 1);

        /* Reset the OCxMD bits in the CCMRx register */
        *(__IO uint32_t*)tmp &= (uint32_t)(~((uint32_t)(TIM_CCMOD1_OC2MD | TIM_CCMOD1_OC2MD_3)));

        /* Configure the OCxMD bits in the CCMRx register */
        *(__IO uint32_t*)tmp |= (uint32_t)(((OcMode << 8) & (0x0000E000)) | ((OcMode << 1) & (0x00040000)));
    }
}

/**
*\*\name    TIM_EnableUpdateEvt
*\*\fun     Enables or Disables the TIMx Update event.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_EnableUpdateEvt(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the Update Disable Bit */
        TIMx->CTRL1 |= (uint32_t)TIM_CTRL1_UPDIS;
    }
    else
    {
        /* Reset the Update Disable Bit */
        TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_CTRL1_UPDIS));
    }
}

/**
*\*\name    TIM_ConfigUpdateRequestIntSrc
*\*\fun     Configures the TIMx Update Request Interrupt source.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_UpdateSource
*\*\          - TIM_UPDATE_SRC_GLOBAL
*\*\          - TIM_UPDATE_SRC_REGULAR
*\*\return  none
**/
void TIM_ConfigUpdateRequestIntSrc(TIM_Module* TIMx, uint32_t TIM_UpdateSource)
{
    if (TIM_UpdateSource != TIM_UPDATE_SRC_GLOBAL)
    {
        /* Set the UPRS Bit */
        TIMx->CTRL1 |= (uint32_t)TIM_CTRL1_UPRS;
    }
    else
    {
        /* Reset the UPRS Bit */
        TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_CTRL1_UPRS));
    }
}

/**
*\*\name    TIM_SelectHallSensor
*\*\fun     Enables or disables the TIMx's Hall sensor interface.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_SelectHallSensor(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the TI1SEL Bit */
        TIMx->CTRL2 |= (uint32_t)TIM_CTRL2_TI1SEL;
    }
    else
    {
        /* Reset the TI1SEL Bit */
        TIMx->CTRL2 &= (uint32_t)(~((uint32_t)TIM_CTRL2_TI1SEL));
    }
}

/**
*\*\name    TIM_SelectOnePulseMode
*\*\fun     Selects the TIMx's One Pulse Mode.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_OPMode
*\*\          - TIM_OPMODE_SINGLE
*\*\          - TIM_OPMODE_REPET
*\*\return  none
**/
void TIM_SelectOnePulseMode(TIM_Module* TIMx, uint32_t TIM_OPMode)
{
    /* Reset the ONEPM Bit */
    TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_CTRL1_ONEPM));
    /* Configure the ONEPM Mode */
    TIMx->CTRL1 |= (uint32_t)TIM_OPMode;
}

/**
*\*\name    TIM_SelectOutputTrig
*\*\fun     Selects the TIMx Trigger Output Mode.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_TRGOSource
*\*\          - TIM_TRGO_SRC_RESET
*\*\          - TIM_TRGO_SRC_ENABLE
*\*\          - TIM_TRGO_SRC_UPDATE
*\*\          - TIM_TRGO_SRC_OC1
*\*\          - TIM_TRGO_SRC_OC1REF
*\*\          - TIM_TRGO_SRC_OC2REF
*\*\          - TIM_TRGO_SRC_OC3REF
*\*\          - TIM_TRGO_SRC_OC4REF
*\*\          - TIM_TRGO_SRC_OC4_7_8_9REF
*\*\return  none
**/
void TIM_SelectOutputTrig(TIM_Module* TIMx, uint32_t TIM_TRGOSource)
{
    /* Reset the MMSEL Bits */
    TIMx->CTRL2 &= (uint32_t)(~((uint32_t)TIM_CTRL2_MMSEL));
    /* Select the TRGO source */
    TIMx->CTRL2 |= TIM_TRGOSource;
}

/**
*\*\name    TIM_SelectOutputTrig2
*\*\fun     Selects the TIMx Trigger Output Mode.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_TRGO2Source
*\*\          - TIM_TRGO2_SRC_RESET
*\*\          - TIM_TRGO2_SRC_ENABLE
*\*\          - TIM_TRGO2_SRC_UPDATE
*\*\          - TIM_TRGO2_SRC_OC1
*\*\          - TIM_TRGO2_SRC_OC1REF
*\*\          - TIM_TRGO2_SRC_OC2REF
*\*\          - TIM_TRGO2_SRC_OC3REF
*\*\          - TIM_TRGO2_SRC_OC4REF
*\*\          - TIM_TRGO2_SRC_OC5REF
*\*\          - TIM_TRGO2_SRC_OC6REF
*\*\          - LL_TIM_TRGO2_OC4_RISINGFALLING
*\*\          - LL_TIM_TRGO2_OC6_RISINGFALLING
*\*\          - LL_TIM_TRGO2_OC4_RISING_OC6_RISING
*\*\          - LL_TIM_TRGO2_OC4_RISING_OC6_FALLING
*\*\          - LL_TIM_TRGO2_OC5_RISING_OC6_RISING
*\*\          - LL_TIM_TRGO2_OC5_RISING_OC6_FALLING
*\*\return  none
**/
void TIM_SelectOutputTrig2(TIM_Module* TIMx, uint32_t TIM_TRGO2Source)
{
    /* Reset the MMSEL2 Bits */
    TIMx->CTRL2 &= (uint32_t)(~((uint32_t)TIM_CTRL2_MMSEL2));
    /* Select the TRGO2 source */
    TIMx->CTRL2 |= TIM_TRGO2Source;
}

/**
*\*\name    TIM_SelectSlaveMode
*\*\fun     Selects the TIMx Slave Mode.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_SlaveMode
*\*\          - TIM_SLAVE_MODE_DISABLE
*\*\          - TIM_SLAVE_MODE_RESET
*\*\          - TIM_SLAVE_MODE_GATED
*\*\          - TIM_SLAVE_MODE_TRIG
*\*\          - TIM_SLAVE_MODE_EXT1
*\*\          - TIM_SLAVE_MODE_GATED_RESET
*\*\          - TIM_SLAVE_MODE_TRIG_RESET
*\*\return  none
**/
void TIM_SelectSlaveMode(TIM_Module* TIMx, uint32_t TIM_SlaveMode)
{
    /* Reset the SMSEL Bits */
    TIMx->SMCTRL &= (uint32_t)(~((uint32_t)TIM_SMCTRL_SMSEL));
    /* Select the Slave Mode */
    TIMx->SMCTRL |= (uint32_t)TIM_SlaveMode;
}

/**
*\*\name    TIM_SelectMasterSlaveMode
*\*\fun     Sets or Resets the TIMx Master/Slave Mode.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_SlaveMode
*\*\          - TIM_MASTER_SLAVE_MODE_ENABLE
*\*\          - TIM_MASTER_SLAVE_MODE_DISABLE
*\*\return  none
**/
void TIM_SelectMasterSlaveMode(TIM_Module* TIMx, uint32_t TIM_MasterSlaveMode)
{
    /* Reset the MSMD Bit */
    TIMx->SMCTRL &= (uint32_t)(~((uint32_t)TIM_SMCTRL_MSMD));
    /* Set or Reset the MSMD Bit */
    TIMx->SMCTRL |= (uint32_t)TIM_MasterSlaveMode;
}

/**
*\*\name    TIM_SetCnt
*\*\fun     Sets the TIMx Counter Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   Counter
*\*\          - Counter can be a number between 0x00000000 and 0xFFFFFFFF
*\*\return  none
**/
void TIM_SetCnt(TIM_Module* TIMx, uint32_t Counter)
{
    /* Set the Counter Register value */
    TIMx->CNT = (uint32_t)((uint32_t)Counter);
}

/**
*\*\name    TIM_SetAutoReload
*\*\fun     Sets the TIMx Autoreload Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   Autoreload
*\*\          - Autoreload can be a number between 0x00000000 and 0xFFFFFFFF
*\*\return  none
**/
void TIM_SetAutoReload(TIM_Module* TIMx, uint32_t Autoreload)
{
    /* Set the Autoreload Register value */
    TIMx->AR = (uint32_t)((uint32_t)Autoreload);
}

/**
*\*\name    TIM_SetCmp1
*\*\fun     Sets the TIMx Capture Compare1 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Compare1
*\*\          - Compare1 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp1(TIM_Module* TIMx, uint16_t Compare1)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT1 ;
    /* Reset the Capture Compare1 Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT1_CCDAT1);
    tmpccdatx |= (uint32_t)Compare1;
    /* Set the Capture Compare1 Register value */
    TIMx->CCDAT1 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp2
*\*\fun     Sets the TIMx Capture Compare2 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Compare2
*\*\          - Compare2 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp2(TIM_Module* TIMx, uint16_t Compare2)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT2 ;
    /* Reset the Capture Compare2 Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT2_CCDAT2);
    tmpccdatx |= (uint32_t)Compare2;
    /* Set the Capture Compare2 Register value */
    TIMx->CCDAT2 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp3
*\*\fun     Sets the TIMx Capture Compare3 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Compare3
*\*\          - Compare3 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp3(TIM_Module* TIMx, uint16_t Compare3)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT3 ;
    /* Reset the Capture Compare3 Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT3_CCDAT3);
    tmpccdatx |= (uint32_t)Compare3;
    /* Set the Capture Compare3 Register value */
    TIMx->CCDAT3 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp4
*\*\fun     Sets the TIMx Capture Compare4 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Compare4
*\*\          - Compare4 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp4(TIM_Module* TIMx, uint16_t Compare4)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT4 ;
    /* Reset the Capture Compare4 Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT4_CCDAT4);
    tmpccdatx |= (uint32_t)Compare4;
    /* Set the Capture Compare4 Register value */
    TIMx->CCDAT4 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp5
*\*\fun     Sets the TIMx Capture Compare5 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Compare5
*\*\          - Compare5 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp5(TIM_Module* TIMx, uint16_t Compare5)
{
    /* Set the Capture Compare5 Register value */
    TIMx->CCDAT5 = (uint32_t)Compare5;
}

/**
*\*\name    TIM_SetCmp6
*\*\fun     Sets the TIMx Capture Compare6 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   Compare6
*\*\          - Compare6 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp6(TIM_Module* TIMx, uint16_t Compare6)
{
    /* Set the Capture Compare6 Register value */
    TIMx->CCDAT6 = (uint32_t)Compare6;
}

/**
*\*\name    TIM_SetCmp7
*\*\fun     Sets the TIMx Capture Compare7 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   Compare7
*\*\          - Compare7 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp7(TIM_Module* TIMx, uint16_t Compare7)
{
    /* Set the Capture Compare7 Register value */
    TIMx->CCDAT7 = (uint32_t)Compare7;
}

/**
*\*\name    TIM_SetCmp8
*\*\fun     Sets the TIMx Capture Compare8 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   Compare8
*\*\          - Compare8 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp8(TIM_Module* TIMx, uint16_t Compare8)
{
    /* Set the Capture Compare8 Register value */
    TIMx->CCDAT8 = (uint32_t)Compare8;
}

/**
*\*\name    TIM_SetCmp9
*\*\fun     Sets the TIMx Capture Compare9 Register value
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   Compare9
*\*\          - Compare9 can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp9(TIM_Module* TIMx, uint16_t Compare9)
{
    /* Set the Capture Compare9 Register value */
    TIMx->CCDAT9 = (uint32_t)Compare9;
}

/**
*\*\name    TIM_SetCmp1D
*\*\fun     Sets the CCDDAT1[16:31] in TIM1_CCDAT1 register
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   compare1D
*\*\          - compare1D can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp1D(TIM_Module* TIMx, uint16_t compare1D)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT1 ;
    /* Reset the Capture compare1D Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT1_CCDDAT1);
    tmpccdatx |= (uint32_t)(((uint32_t)compare1D) << 0x00000010);
    /* Set the Capture compare1D Register value */
    TIMx->CCDAT1 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp2D
*\*\fun     Sets the CCDDAT2[16:31] in TIM1_CCDAT2 register
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   compare2D
*\*\          - compare2D can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp2D(TIM_Module* TIMx, uint16_t compare2D)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT2 ;
    /* Reset the Capture compare2D Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT2_CCDDAT2);
    tmpccdatx |= (uint32_t)(((uint32_t)compare2D) << 0x00000010);
    /* Set the Capture compare2D Register value */
    TIMx->CCDAT2 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp3D
*\*\fun     Sets the CCDDAT3[16:31] in TIM1_CCDAT3 register
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   compare3D
*\*\          - compare3D can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp3D(TIM_Module* TIMx, uint16_t compare3D)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT3 ;
    /* Reset the Capture compare3D Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT3_CCDDAT3);
    tmpccdatx |= (uint32_t)(((uint32_t)compare3D) << 0x00000010);
    /* Set the Capture compare3D Register value */
    TIMx->CCDAT3 = tmpccdatx;
}

/**
*\*\name    TIM_SetCmp4D
*\*\fun     Sets the CCDDAT4[16:31] in TIM1_CCDAT4 register
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   compare4D
*\*\          - compare4D can be a number between 0x0000 and 0xFFFF
*\*\return  none
**/
void TIM_SetCmp4D(TIM_Module* TIMx, uint16_t compare4D)
{
    uint32_t tmpccdatx ;
    tmpccdatx = TIMx->CCDAT4 ;
    /* Reset the Capture compare4D Register value */
    tmpccdatx &= (uint32_t)(~TIM_CCDAT4_CCDDAT4);
    tmpccdatx |= (uint32_t)(((uint32_t)compare4D) << 0x00000010);
    /* Set the Capture compare4D Register value */
    TIMx->CCDAT4 = tmpccdatx;
}

/**
*\*\name    ConfigTI1
*\*\fun     Configure the TI1 as Input.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPolarity
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   ICSelection
*\*\          - TIM_IC_SELECTION_DIRECTTI
*\*\          - TIM_IC_SELECTION_INDIRECTTI
*\*\          - TIM_IC_SELECTION_TRC
*\*\param   ICFilter
*\*\          - ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void ConfigTI1(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen  ;

    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCEN &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1EN));

    /* Get the TIMx_CCMOD1 and TIMx_CCEN register value */
    tmpccmodx = TIMx->CCMOD1;
    tmpccen  = TIMx->CCEN;

    /* Select the Input and set the filter */
    tmpccmodx &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_CCMOD1_CC1SEL)) & ((uint32_t) ~((uint32_t)TIM_CCMOD1_IC1F)));
    tmpccmodx |= (uint32_t)(ICSelection | (uint32_t)(ICFilter << (uint32_t)4));

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Select the Polarity and set the CC1E Bit */
        tmpccen &= (uint32_t)(~((uint32_t)(TIM_CCEN_CC1P)));
        tmpccen |= (uint32_t)(ICPolarity | (uint32_t)TIM_CCEN_CC1EN);
    }

    /* Write to TIMx CCMOD1 and CCEN registers */
    TIMx->CCMOD1 = tmpccmodx;
    TIMx->CCEN   = tmpccen;
}

/**
*\*\name    ConfigTI2
*\*\fun     Configure the TI2 as Input.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPolarity
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   ICSelection
*\*\          - TIM_IC_SELECTION_DIRECTTI
*\*\          - TIM_IC_SELECTION_INDIRECTTI
*\*\          - TIM_IC_SELECTION_TRC
*\*\param   ICFilter
*\*\          - ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void ConfigTI2(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmp ;

    /* Disable the Channel 2: Reset the CC2E Bit */
    TIMx->CCEN &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2EN));

    /* Get the TIMx_CCMOD1 and TIMx_CCEN register value */
    tmpccmodx = TIMx->CCMOD1;
    tmpccen  = TIMx->CCEN;

    tmp      = (uint32_t)(ICPolarity << 4);

    /* Select the Input and set the filter */
    tmpccmodx &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_CCMOD1_CC2SEL)) & ((uint32_t) ~((uint32_t)TIM_CCMOD1_IC2F)));
    tmpccmodx |= (uint32_t)(ICFilter << 12);
    tmpccmodx |= (uint32_t)(ICSelection << 8);

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Select the Polarity and set the CC2E Bit */
        tmpccen &= (uint32_t)(~((uint32_t)(TIM_CCEN_CC2P)));
        tmpccen |= (uint32_t)(tmp | (uint32_t)TIM_CCEN_CC2EN);
    }

    /* Write to TIMx CCMOD1 and CCEN registers */
    TIMx->CCMOD1 = tmpccmodx;
    TIMx->CCEN   = tmpccen;
}

/**
*\*\name    ConfigTI3
*\*\fun     Configure the TI3 as Input.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPolarity
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   ICSelection
*\*\          - TIM_IC_SELECTION_DIRECTTI
*\*\          - TIM_IC_SELECTION_INDIRECTTI
*\*\          - TIM_IC_SELECTION_TRC
*\*\param   ICFilter
*\*\          - ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void ConfigTI3(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmp ;

    /* Disable the Channel 3: Reset the CC3E Bit */
    TIMx->CCEN &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3EN));

    /* Get the TIMx_CCMOD2 and TIMx_CCEN register value */
    tmpccmodx = TIMx->CCMOD2;
    tmpccen  = TIMx->CCEN;

    tmp      = (uint32_t)(ICPolarity << 8);

    /* Select the Input and set the filter */
    tmpccmodx &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_CCMOD2_CC3SEL)) & ((uint32_t) ~((uint32_t)TIM_CCMOD2_IC3F)));
    tmpccmodx |= (uint32_t)(ICSelection | (uint32_t)(ICFilter << (uint32_t)4));

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Select the Polarity and set the CC3E Bit */
        tmpccen &= (uint32_t)(~((uint32_t)(TIM_CCEN_CC3P)));
        tmpccen |= (uint32_t)(tmp | (uint32_t)TIM_CCEN_CC3EN);
    }

    /* Write to TIMx CCMOD2 and CCEN registers */
    TIMx->CCMOD2 = tmpccmodx;
    TIMx->CCEN   = tmpccen;
}

/**
*\*\name    ConfigTI4
*\*\fun     Configure the TI4 as Input.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPolarity
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   ICSelection
*\*\          - TIM_IC_SELECTION_DIRECTTI
*\*\          - TIM_IC_SELECTION_INDIRECTTI
*\*\          - TIM_IC_SELECTION_TRC
*\*\param   ICFilter
*\*\          - ICFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void ConfigTI4(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter)
{
    uint32_t tmpccmodx ;
    uint32_t tmpccen, tmp ;

    /* Disable the Channel 4: Reset the CC4E Bit */
    TIMx->CCEN &= (uint32_t)(~((uint32_t)TIM_CCEN_CC4EN));

    /* Get the TIMx_CCMOD2 and TIMx_CCEN register value */
    tmpccmodx = TIMx->CCMOD2;
    tmpccen  = TIMx->CCEN;

    tmp      = (uint32_t)(ICPolarity << 12);

    /* Select the Input and set the filter */
    tmpccmodx &= (uint32_t)((uint32_t)(~(uint32_t)TIM_CCMOD2_CC4SEL) & ((uint32_t) ~((uint32_t)TIM_CCMOD2_IC4F)));
    tmpccmodx |= (uint32_t)(ICSelection << 8);
    tmpccmodx |= (uint32_t)(ICFilter << 12);

    if ((IS_ATIM1_4_DEVICE(TIMx)) || (IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        /* Select the Polarity and set the CC4E Bit */
        tmpccen &= (uint32_t)(~((uint32_t)(TIM_CCEN_CC4P)));
        tmpccen |= (uint32_t)(tmp | (uint32_t)TIM_CCEN_CC4EN);
    }
    else
    {
        /* Select the Polarity and set the CC4E Bit */
        tmpccen &= (uint32_t)(~((uint32_t)(TIM_CCEN_CC4P)));
        tmpccen |= (uint32_t)(ICPolarity | (uint32_t)TIM_CCEN_CC4EN);
    }

    /* Write to TIMx CCMOD2 and CCEN registers */
    TIMx->CCMOD2 = tmpccmodx;
    TIMx->CCEN   = tmpccen;
}

/**
*\*\name    TIM_SetInCap1Prescaler
*\*\fun     Sets the TIMx Input Capture 1 prescaler.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPrescaler
*\*\          - TIM_IC_PSC_DIV1
*\*\          - TIM_IC_PSC_DIV2
*\*\          - TIM_IC_PSC_DIV4
*\*\          - TIM_IC_PSC_DIV8
*\*\return  none
**/
void TIM_SetInCap1Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler)
{
    /* Reset the IC1PSC Bits */
    TIMx->CCMOD1 &= (uint32_t)(~TIM_CCMOD1_IC1PSC);
    /* Set the IC1PSC value */
    TIMx->CCMOD1 |= (uint32_t)ICPrescaler;
}

/**
*\*\name    TIM_SetInCap2Prescaler
*\*\fun     Sets the TIMx Input Capture 2 prescaler.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPrescaler
*\*\          - TIM_IC_PSC_DIV1
*\*\          - TIM_IC_PSC_DIV2
*\*\          - TIM_IC_PSC_DIV4
*\*\          - TIM_IC_PSC_DIV8
*\*\return  none
**/
void TIM_SetInCap2Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler)
{
    /* Reset the IC2PSC Bits */
    TIMx->CCMOD1 &= (uint32_t)(~TIM_CCMOD1_IC2PSC);
    /* Set the IC2PSC value */
    TIMx->CCMOD1 |= (uint32_t)(ICPrescaler << 8);
}

/**
*\*\name    TIM_SetInCap3Prescaler
*\*\fun     Sets the TIMx Input Capture 3 prescaler.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPrescaler
*\*\          - TIM_IC_PSC_DIV1
*\*\          - TIM_IC_PSC_DIV2
*\*\          - TIM_IC_PSC_DIV4
*\*\          - TIM_IC_PSC_DIV8
*\*\return  none
**/
void TIM_SetInCap3Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler)
{
    /* Reset the IC3PSC Bits */
    TIMx->CCMOD2 &= (uint32_t)(~TIM_CCMOD2_IC3PSC);
    /* Set the IC3PSC value */
    TIMx->CCMOD2 |= (uint32_t)ICPrescaler;
}

/**
*\*\name    TIM_SetInCap4Prescaler
*\*\fun     Sets the TIMx Input Capture 4 prescaler.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   ICPrescaler
*\*\          - TIM_IC_PSC_DIV1
*\*\          - TIM_IC_PSC_DIV2
*\*\          - TIM_IC_PSC_DIV4
*\*\          - TIM_IC_PSC_DIV8
*\*\return  none
**/
void TIM_SetInCap4Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler)
{
    /* Reset the IC4PSC Bits */
    TIMx->CCMOD2 &= (uint32_t)(~TIM_CCMOD2_IC4PSC);
    /* Set the IC4PSC value */
    TIMx->CCMOD2 |= (uint32_t)(ICPrescaler << 8);
}

/**
*\*\name    TIM_SelectInputTrig
*\*\fun     Selects the Input Trigger source
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_InputTriggerSource:
*\*\          - TIM_TRIG_SEL_IN_TR0
*\*\          - TIM_TRIG_SEL_IN_TR1
*\*\          - TIM_TRIG_SEL_IN_TR2
*\*\          - TIM_TRIG_SEL_IN_TR3
*\*\          - TIM_TRIG_SEL_IN_TR4
*\*\          - TIM_TRIG_SEL_IN_TR5
*\*\          - TIM_TRIG_SEL_IN_TR6
*\*\          - TIM_TRIG_SEL_IN_TR7
*\*\          - TIM_TRIG_SEL_IN_TR8
*\*\          - TIM_TRIG_SEL_IN_TR9
*\*\          - TIM_TRIG_SEL_IN_TR10
*\*\          - TIM_TRIG_SEL_IN_TR11
*\*\          - TIM_TRIG_SEL_IN_TR12
*\*\          - TIM_TRIG_SEL_IN_TR13
*\*\          - TIM_TRIG_SEL_IN_TR14
*\*\          - TIM_TRIG_SEL_TI1F_ED
*\*\          - TIM_TRIG_SEL_TI1FP1
*\*\          - TIM_TRIG_SEL_TI2FP2
*\*\          - TIM_TRIG_SEL_ETRF
*\*\return  none
**/
void TIM_SelectInputTrig(TIM_Module* TIMx, uint32_t TIM_InputTriggerSource)
{
    uint32_t tmpsmctrl ;
    uint32_t tmpinsel ;
    /* Get the TIMx SMCTRL and TIMx INSEL register value */
    tmpsmctrl = TIMx->SMCTRL;
    tmpinsel  = TIMx->INSEL;

    /* Reset the TS Bits */
    tmpsmctrl &= (uint32_t)(~((uint32_t)TIM_SMCTRL_TSEL));
    /* Reset the ITRS Bits */
    tmpinsel &= (uint32_t)(~((uint32_t)TIM_INSEL_ITRS));

    if (IS_ITR_SEL(TIM_InputTriggerSource))
    {
        /* Set the Input Trigger source */
        tmpinsel |= (uint32_t)TIM_InputTriggerSource;
    }
    else
    {
        /* Set the Input Trigger source */
        tmpsmctrl |= (uint32_t)TIM_InputTriggerSource;

    }

    /* Write to TIMx SMCTRL and INSEL */
    TIMx->SMCTRL = tmpsmctrl;
    TIMx->INSEL = tmpinsel;
}

/**
*\*\name    TIM_ConfigExtTrig
*\*\fun     Configures the TIMx External Trigger (ETR).
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ExtTRGPrescaler:
*\*\          - TIM_EXT_TRG_PSC_OFF
*\*\          - TIM_EXT_TRG_PSC_DIV2
*\*\          - TIM_EXT_TRG_PSC_DIV4
*\*\          - TIM_EXT_TRG_PSC_DIV8
*\*\param   TIM_ExtTRGPolarity
*\*\          - TIM_EXT_TRIG_POLARITY_INVERTED
*\*\          - TIM_EXT_TRIG_POLARITY_NONINVERTED
*\*\param   ExtTRGFilter
*\*\          - ExtTRGFilter can be a number between 0x0 and 0xF
*\*\return  none
**/
void TIM_ConfigExtTrig(TIM_Module* TIMx, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
    uint32_t tmpsmctrl ;
    tmpsmctrl = TIMx->SMCTRL;
    /* Reset the ETR Bits */
    tmpsmctrl &= (uint32_t)(~(TIM_SMCTRL_EXTPS | TIM_SMCTRL_EXTP | TIM_SMCTRL_EXTF));
    /* Set the Prescaler, the Filter value and the Polarity */
    tmpsmctrl |= (uint32_t)(TIM_ExtTRGPrescaler | (TIM_ExtTRGPolarity | (ExtTRGFilter << (uint32_t)12)));
    /* Write to TIMx SMCTRL */
    TIMx->SMCTRL = tmpsmctrl;
}

/**
*\*\name    TIM_SelectETRInputSource
*\*\fun     Configures the source of tim_etr_in.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_ETRInputSource:
*\*\          - TIM_CAPETRSEL_0
*\*\          - TIM_CAPETRSEL_1
*\*\          - TIM_CAPETRSEL_2
*\*\          - TIM_CAPETRSEL_3
*\*\          - TIM_CAPETRSEL_4
*\*\          - TIM_CAPETRSEL_5
*\*\          - TIM_CAPETRSEL_6
*\*\          - TIM_CAPETRSEL_7
*\*\          - TIM_CAPETRSEL_8
*\*\          - TIM_CAPETRSEL_10
*\*\          - TIM_CAPETRSEL_11
*\*\          - TIM_CAPETRSEL_12
*\*\          - TIM_CAPETRSEL_13
*\*\return  none
**/
void TIM_SelectETRInputSource(TIM_Module* TIMx, uint32_t TIM_ETRInputSource)
{
    uint32_t tmpinsel ;
    tmpinsel = TIMx->INSEL;
    /* Reset the ETRS Bits */
    tmpinsel &= (uint32_t)(~TIM_INSEL_ETRS);
    /* Set the ETRS Bits */
    tmpinsel |= (uint32_t)TIM_ETRInputSource;
    /* Write to TIMx SMCTRL */
    TIMx->INSEL = tmpinsel;
}

/**
*\*\name    TIM_SetClkDiv
*\*\fun     Sets the TIMx Clock Division value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_CKD:
*\*\          - TIM_CLK_DIV1
*\*\          - TIM_CLK_DIV2
*\*\          - TIM_CLK_DIV4
*\*\return  none
**/
void TIM_SetClkDiv(TIM_Module* TIMx, uint32_t TIM_CKD)
{
    /* Reset the CKD Bits */
    TIMx->CTRL1 &= (uint32_t)(~TIM_CTRL1_CLKD);
    /* Set the CKD value */
    TIMx->CTRL1 |= (uint32_t)TIM_CKD;
}

/**
*\*\name    TIM_GetCap1
*\*\fun     Gets the TIMx Input Capture 1 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  Capture Compare 1 Register value.
**/
uint16_t TIM_GetCap1(TIM_Module* TIMx)
{
    /* Get the Capture 1 Register value */
    return (uint16_t)(TIMx->CCDAT1);
}

/**
*\*\name    TIM_GetCap2
*\*\fun     Gets the TIMx Input Capture 2 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  Capture Compare 2 Register value.
**/
uint16_t TIM_GetCap2(TIM_Module* TIMx)
{
    /* Get the Capture 2 Register value */
    return (uint16_t)(TIMx->CCDAT2);
}

/**
*\*\name    TIM_GetCap3
*\*\fun     Gets the TIMx Input Capture 3 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  Capture Compare 3 Register value.
**/
uint16_t TIM_GetCap3(TIM_Module* TIMx)
{
    /* Get the Capture 3 Register value */
    return (uint16_t)(TIMx->CCDAT3);
}

/**
*\*\name    TIM_GetCap4
*\*\fun     Gets the TIMx Input Capture 4 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  Capture Compare 4 Register value.
**/
uint16_t TIM_GetCap4(TIM_Module* TIMx)
{
    /* Get the Capture 4 Register value */
    return (uint16_t)(TIMx->CCDAT4);
}

/**
*\*\name    TIM_GetCap5
*\*\fun     Gets the TIMx Input Capture 5 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\return  Capture Compare 5 Register value.
**/
uint16_t TIM_GetCap5(TIM_Module* TIMx)
{
    /* Get the Capture 5 Register value */
    return (uint16_t)(TIMx->CCDAT5);
}


/**
*\*\name    TIM_GetCap6
*\*\fun     Gets the TIMx Input Capture 6 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 6 Register value.
**/
uint16_t TIM_GetCap6(TIM_Module* TIMx)
{
    /* Get the Capture 1 Register value */
    return (uint16_t)(TIMx->CCDAT6);
}

/**
*\*\name    TIM_GetCap7
*\*\fun     Gets the TIMx Input Capture 7 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 7 Register value.
**/
uint16_t TIM_GetCap7(TIM_Module* TIMx)
{
    /* Get the Capture 7 Register value */
    return (uint16_t)(TIMx->CCDAT7);
}

/**
*\*\name    TIM_GetCap8
*\*\fun     Gets the TIMx Input Capture 8 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 8 Register value.
**/
uint16_t TIM_GetCap8(TIM_Module* TIMx)
{
    /* Get the Capture 8 Register value */
    return (uint16_t)(TIMx->CCDAT8);
}

/**
*\*\name    TIM_GetCap9
*\*\fun     Gets the TIMx Input Capture 9 value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 9 Register value.
**/
uint16_t TIM_GetCap9(TIM_Module* TIMx)
{
    /* Get the Capture 9 Register value */
    return (uint16_t)(TIMx->CCDAT9);
}

/**
*\*\name    TIM_GetCap1D
*\*\fun     Gets the TIMx Input Capture 1D value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 1D Register value.
**/
uint16_t TIM_GetCap1D(TIM_Module* TIMx)
{
    /* Get the Capture 1D Register value */
    return (uint16_t)((TIMx->CCDAT1) >> 0x00000010);
}

/**
*\*\name    TIM_GetCap2D
*\*\fun     Gets the TIMx Input Capture 2D value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 2D Register value.
**/
uint16_t TIM_GetCap2D(TIM_Module* TIMx)
{
    /* Get the Capture 2D Register value */
    return (uint16_t)((TIMx->CCDAT2) >> 0x00000010);
}

/**
*\*\name    TIM_GetCap3D
*\*\fun     Gets the TIMx Input Capture 3D value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 3D Register value.
**/
uint16_t TIM_GetCap3D(TIM_Module* TIMx)
{
    /* Get the Capture 3D Register value */
    return (uint16_t)((TIMx->CCDAT3) >> 0x00000010);
}

/**
*\*\name    TIM_GetCap4D
*\*\fun     Gets the TIMx Input Capture 4D value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\return  Capture Compare 4D Register value.
**/
uint16_t TIM_GetCap4D(TIM_Module* TIMx)
{
    /* Get the Capture 4D Register value */
    return (uint16_t)((TIMx->CCDAT4) >> 0x00000010);
}

/**
*\*\name    TIM_GetCnt
*\*\fun     Gets the TIMx Counter value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\return  Counter Register value.
**/
uint32_t TIM_GetCnt(TIM_Module* TIMx)
{
    /* Get the Counter Register value */
    return (uint32_t)(TIMx->CNT);
}

/**
*\*\name    TIM_GetPrescaler
*\*\fun     Gets the TIMx Prescaler value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\return  Prescaler Register value.
**/
uint16_t TIM_GetPrescaler(TIM_Module* TIMx)
{
    /* Get the Prescaler Register value */
    return (uint16_t)(TIMx->PSC);
}

/**
*\*\name    TIM_GetAutoReload
*\*\fun     Gets the TIMx AR value.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\return  AR Register value.
**/
uint32_t TIM_GetAutoReload(TIM_Module* TIMx)
{
    /* Get the Prescaler Register value */
    return (uint32_t)(TIMx->AR);
}

/**
*\*\name    TIM_GetCCENStatus
*\*\fun     Checks whether the specified TIM flag is set or not.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_CCEN :
*\*\          - TIM_CC1EN
*\*\          - TIM_CC1NEN
*\*\          - TIM_CC2EN
*\*\          - TIM_CC2NEN
*\*\          - TIM_CC3EN
*\*\          - TIM_CC3NEN
*\*\          - TIM_CC4EN
*\*\          - TIM_CC4NEN
*\*\          - TIM_CC5EN
*\*\          - TIM_CC6EN
*\*\return  The new state of TIM_FLAG (SET or RESET).
**/
FlagStatus TIM_GetCCENStatus(TIM_Module* TIMx, uint32_t TIM_CCEN)
{
    FlagStatus bitstatus;

    if ((TIMx->CCEN & TIM_CCEN) != (uint32_t)RESET)
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
*\*\name    TIM_GetFlagStatus
*\*\fun     Checks whether the specified TIM flag is set or not.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_FLAG :
*\*\          - TIM_FLAG_UPDATE
*\*\          - TIM_FLAG_CC1
*\*\          - TIM_FLAG_CC2
*\*\          - TIM_FLAG_CC3
*\*\          - TIM_FLAG_CC4
*\*\          - TIM_FLAG_CC5
*\*\          - TIM_FLAG_CC6
*\*\          - TIM_FLAG_CC7
*\*\          - TIM_FLAG_CC8
*\*\          - TIM_FLAG_CC9
*\*\          - TIM_FLAG_COM
*\*\          - TIM_FLAG_TRIG
*\*\          - TIM_FLAG_BREAK
*\*\          - TIM_FLAG_BREAK2
*\*\          - TIM_FLAG_SYS_BREAK
*\*\          - TIM_FLAG_CC1OF
*\*\          - TIM_FLAG_CC2OF
*\*\          - TIM_FLAG_CC3OF
*\*\          - TIM_FLAG_CC4OF
*\*\return  The new state of TIM_FLAG (SET or RESET).
**/
FlagStatus TIM_GetFlagStatus(TIM_Module* TIMx, uint32_t TIM_FLAG)
{
    FlagStatus bitstatus;

    if ((TIMx->STS & TIM_FLAG) != (uint32_t)RESET)
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
*\*\name    TIM_ClearFlag
*\*\fun     Clears the TIMx's pending flags.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_FLAG :
*\*\          - TIM_FLAG_UPDATE
*\*\          - TIM_FLAG_CC1
*\*\          - TIM_FLAG_CC2
*\*\          - TIM_FLAG_CC3
*\*\          - TIM_FLAG_CC4
*\*\          - TIM_FLAG_CC5
*\*\          - TIM_FLAG_CC6
*\*\          - TIM_FLAG_CC7
*\*\          - TIM_FLAG_CC8
*\*\          - TIM_FLAG_CC9
*\*\          - TIM_FLAG_COM
*\*\          - TIM_FLAG_TRIG
*\*\          - TIM_FLAG_BREAK
*\*\          - TIM_FLAG_BREAK2
*\*\          - TIM_FLAG_SYS_BREAK
*\*\          - TIM_FLAG_CC1OF
*\*\          - TIM_FLAG_CC2OF
*\*\          - TIM_FLAG_CC3OF
*\*\          - TIM_FLAG_CC4OF
*\*\return  none.
**/
void TIM_ClearFlag(TIM_Module* TIMx, uint32_t TIM_FLAG)
{
    /* Clear the flags */
    TIMx->STS = (uint32_t)(~TIM_FLAG);
}

/**
*\*\name    TIM_GetIntStatus
*\*\fun     Checks whether the TIM interrupt has occurred or not.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_IT :
*\*\          - TIM_INT_UPDATE
*\*\          - TIM_INT_CC1
*\*\          - TIM_INT_CC2
*\*\          - TIM_INT_CC3
*\*\          - TIM_INT_CC4
*\*\          - TIM_INT_CC5
*\*\          - TIM_INT_CC6
*\*\          - TIM_INT_CC7
*\*\          - TIM_INT_CC8
*\*\          - TIM_INT_CC9
*\*\          - TIM_INT_COM
*\*\          - TIM_INT_TRIG
*\*\          - TIM_INT_BREAK
*\*\          - TIM_INT_BREAK2
*\*\          - TIM_INT_SYS_BREAK
*\*\return  The new state of the TIM_IT(SET or RESET).
**/
INTStatus TIM_GetIntStatus(TIM_Module* TIMx, uint32_t TIM_IT)
{
    INTStatus bitstatus;
    uint32_t itstatus = 0x0, itenable;

    if(TIM_IT == TIM_INT_UPDATE)
    {
        itstatus = TIMx->STS & TIM_FLAG_UPDATE;
    }
    else if(TIM_IT == TIM_INT_CC1)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC1;
    }
    else if(TIM_IT == TIM_INT_CC2)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC2;
    }
    else if(TIM_IT == TIM_INT_CC3)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC3;
    }
    else if(TIM_IT == TIM_INT_CC4)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC4;
    }
    else if(TIM_IT == TIM_INT_CC5)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC5;
    }
    else if(TIM_IT == TIM_INT_CC6)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC6;
    }
    else if(TIM_IT == TIM_INT_CC7)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC7;
    }
    else if(TIM_IT == TIM_INT_CC8)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC8;
    }
    else if(TIM_IT == TIM_INT_CC9)
    {
        itstatus = TIMx->STS & TIM_FLAG_CC9;
    }
    else if(TIM_IT == TIM_INT_COM)
    {
        itstatus = TIMx->STS & TIM_FLAG_COM;
    }
    else if(TIM_IT == TIM_INT_TRIG)
    {
        itstatus = TIMx->STS & TIM_FLAG_TRIG;
    }
    else if(TIM_IT == TIM_INT_BREAK)
    {
        itstatus = TIMx->STS & TIM_FLAG_BREAK;
    }
    else if(TIM_IT == TIM_INT_BREAK2)
    {
        itstatus = TIMx->STS & TIM_FLAG_BREAK2;
    }
    else if(TIM_IT == TIM_INT_SYS_BREAK)
    {
        itstatus = TIMx->STS & TIM_FLAG_SYS_BREAK;
    }
    else
    {

    }

    if((TIM_IT == TIM_INT_BREAK) || (TIM_IT == TIM_INT_BREAK2) || (TIM_IT == TIM_INT_SYS_BREAK))
    {
        itenable = TIMx->DINTEN & TIM_INT_BREAK;
    }
    else
    {
        itenable = TIMx->DINTEN & TIM_IT;
    }

    if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
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
*\*\name    TIM_ClrIntPendingBit
*\*\fun     Clears the TIMx's interrupt pending bits.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\          - BTIM1
*\*\          - BTIM2
*\*\          - BTIM3
*\*\          - BTIM4
*\*\param   TIM_IT :
*\*\          - TIM_INT_UPDATE
*\*\          - TIM_INT_CC1
*\*\          - TIM_INT_CC2
*\*\          - TIM_INT_CC3
*\*\          - TIM_INT_CC4
*\*\          - TIM_INT_CC5
*\*\          - TIM_INT_CC6
*\*\          - TIM_INT_CC7
*\*\          - TIM_INT_CC8
*\*\          - TIM_INT_CC9
*\*\          - TIM_INT_COM
*\*\          - TIM_INT_TRIG
*\*\          - TIM_INT_BREAK
*\*\          - TIM_INT_BREAK2
*\*\          - TIM_INT_SYS_BREAK
*\*\return  none.
**/
void TIM_ClrIntPendingBit(TIM_Module* TIMx, uint32_t TIM_IT)
{
    /* Clear the IT pending Bit */
    if(TIM_IT == TIM_INT_UPDATE)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_UPDATE);
    }
    else if(TIM_IT == TIM_INT_CC1)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC1);
    }
    else if(TIM_IT == TIM_INT_CC2)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC2);
    }
    else if(TIM_IT == TIM_INT_CC3)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC3);
    }
    else if(TIM_IT == TIM_INT_CC4)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC4);
    }
    else if(TIM_IT == TIM_INT_CC5)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC5);
    }
    else if(TIM_IT == TIM_INT_CC6)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC6);
    }
    else if(TIM_IT == TIM_INT_CC7)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC7);
    }
    else if(TIM_IT == TIM_INT_CC8)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC8);
    }
    else if(TIM_IT == TIM_INT_CC9)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_CC9);
    }
    else if(TIM_IT == TIM_INT_COM)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_COM);
    }
    else if(TIM_IT == TIM_INT_TRIG)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_TRIG);
    }
    else if(TIM_IT == TIM_INT_BREAK)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_BREAK);
    }
    else if(TIM_IT == TIM_INT_BREAK2)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_BREAK2);
    }
    else if(TIM_IT == TIM_INT_SYS_BREAK)
    {
        TIMx->STS = (uint32_t)(~TIM_FLAG_SYS_BREAK);
    }
    else
    {

    }
}

/**
*\*\name    TIM_SelectCenterAlignTrig.
*\*\fun     Setting the trigger mode in central alignment mode.
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   TIM_CenterAlignTriggerSource
*\*\          - TIM_UP_COUNTING
*\*\          - TIM_DOWN_COUNTING
*\*\          - TIM_UP_DOWN_COUNTING
*\*\return  none
**/
void TIM_SelectCenterAlignTrig(TIM_Module* TIMx, uint32_t TIM_CenterAlignTriggerSource)
{
    uint32_t temp_value ;

    temp_value = TIMx->CTRL1;
    /* Reset the CMODE Bits */
    temp_value &= (uint32_t)(~((uint32_t)TIM_CTRL1_CMODE));
    /* Set the trigger source */
    temp_value |= (uint32_t)TIM_CenterAlignTriggerSource;
    /* Write to TIMx CTRL1 register */
    TIMx->CTRL1 = temp_value;
}

/**
*\*\name    TIM_Asymmetric_Enable.
*\*\fun     Enable or disable asymmetric mode in center-aligned.
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_AsymmetricEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the ASMMETRIC Bit */
        TIMx->CTRL1 |= (uint32_t)TIM_CTRL1_ASMMETRIC;
    }
    else
    {
        /* Reset the ASMMETRIC Bit */
        TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_CTRL1_ASMMETRIC));
    }
}

/**
*\*\name    TIM_OCxRefTriggerADC.
*\*\fun     Enable or disable OCxREF to trigger ADC(x = 4,7,8 or 9).
*\*\param   TIMx:
*\*\          - ATIM1
*\*\          - ATIM2
*\*\          - ATIM3
*\*\          - ATIM4
*\*\param   OCxRef
*\*\          - TIM_CTRL2_TRIG4
*\*\          - TIM_CTRL2_TRIG7
*\*\          - TIM_CTRL2_TRIG8
*\*\          - TIM_CTRL2_TRIG9
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_OCxRefTriggerADC(TIM_Module* TIMx, uint32_t OCxRef, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the TRIGx Bit */
        TIMx->CTRL2 |= (uint32_t)OCxRef;
    }
    else
    {
        /* Reset the TRIGx Bit */
        TIMx->CTRL2 &= (uint32_t)(~((uint32_t)OCxRef));
    }
}

/**
*\*\name    TIM_IC1FiltConfig
*\*\fun     Config the filter of channel1.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_FiltInitStruct:
*\*\          - refer to the definition of TIM_FiltInitType
*\*\return  none
**/
void TIM_IC1FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct)
{
    uint32_t temp_chxfilt = 0;

    temp_chxfilt &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_C1FILT_THRESH)) &
                               ((uint32_t) ~((uint32_t)TIM_C1FILT_WSIZE)) &
                               ((uint32_t) ~((uint32_t)TIM_C1FILT_SFPSC)));

    temp_chxfilt |= (uint32_t)((TIM_FiltInitStruct->ThreshHold << (uint32_t)(0x18)) |
                               (TIM_FiltInitStruct->WindowSize << (uint32_t)(0x11)) |
                               (TIM_FiltInitStruct->Prescaler));

    if ((IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        TIMx->C1FILT = temp_chxfilt;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_IC2FiltConfig
*\*\fun     Config the filter of channel2.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_FiltInitStruct:
*\*\          - refer to the definition of TIM_FiltInitType
*\*\return  none
**/
void TIM_IC2FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct)
{
    uint32_t temp_chxfilt = 0;

    temp_chxfilt &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_C2FILT_THRESH)) &
                               ((uint32_t) ~((uint32_t)TIM_C2FILT_WSIZE)) &
                               ((uint32_t) ~((uint32_t)TIM_C2FILT_SFPSC)));

    temp_chxfilt |= (uint32_t)((TIM_FiltInitStruct->ThreshHold << (uint32_t)(0x18)) |
                               (TIM_FiltInitStruct->WindowSize << (uint32_t)(0x11)) |
                               (TIM_FiltInitStruct->Prescaler));

    if ((IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        TIMx->C2FILT = temp_chxfilt;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_IC3FiltConfig
*\*\fun     Config the filter of channel3.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_FiltInitStruct:
*\*\          - refer to the definition of TIM_FiltInitType
*\*\return  none
**/
void TIM_IC3FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct)
{
    uint32_t temp_chxfilt = 0;

    temp_chxfilt &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_C3FILT_THRESH)) &
                               ((uint32_t) ~((uint32_t)TIM_C3FILT_WSIZE)) &
                               ((uint32_t) ~((uint32_t)TIM_C3FILT_SFPSC)));

    temp_chxfilt |= (uint32_t)((TIM_FiltInitStruct->ThreshHold << (uint32_t)(0x18)) |
                               (TIM_FiltInitStruct->WindowSize << (uint32_t)(0x11)) |
                               (TIM_FiltInitStruct->Prescaler));

    if ((IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        TIMx->C3FILT = temp_chxfilt;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_IC4FiltConfig
*\*\fun     Config the filter of channel4.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_FiltInitStruct:
*\*\          - refer to the definition of TIM_FiltInitType
*\*\return  none
**/
void TIM_IC4FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct)
{
    uint32_t temp_chxfilt = 0;

    temp_chxfilt &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_C4FILT_THRESH)) &
                               ((uint32_t) ~((uint32_t)TIM_C4FILT_WSIZE)) &
                               ((uint32_t) ~((uint32_t)TIM_C4FILT_SFPSC)));

    temp_chxfilt |= (uint32_t)((TIM_FiltInitStruct->ThreshHold << (uint32_t)(0x18)) |
                               (TIM_FiltInitStruct->WindowSize << (uint32_t)(0x11)) |
                               (TIM_FiltInitStruct->Prescaler));

    if ((IS_GTIMA1_7_DEVICE(TIMx)) || (IS_GTIMB1_3_DEVICE(TIMx)))
    {
        TIMx->C4FILT = temp_chxfilt;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_IC1FiltEnable
*\*\fun     Enable or disable the filter of channel1.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_IC1FiltEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the filter of CH1 */
        TIMx->C1FILT |= (uint32_t)TIM_C1FILT_FILTEN;
    }
    else
    {
        /* Disable the filter of CH1 */
        TIMx->C1FILT &= (uint32_t)(~TIM_C1FILT_FILTEN);
    }
}

/**
*\*\name    TIM_IC2FiltEnable
*\*\fun     Enable or disable the filter of channel2.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_IC2FiltEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the filter of CH2 */
        TIMx->C2FILT |= (uint32_t)TIM_C2FILT_FILTEN;
    }
    else
    {
        /* Disable the filter of CH2 */
        TIMx->C2FILT &= (uint32_t)(~TIM_C2FILT_FILTEN);
    }
}

/**
*\*\name    TIM_IC3FiltEnable
*\*\fun     Enable or disable the filter of channel3.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_IC3FiltEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the filter of CH3 */
        TIMx->C3FILT |= (uint32_t)TIM_C3FILT_FILTEN;
    }
    else
    {
        /* Disable the filter of CH3 */
        TIMx->C3FILT &= (uint32_t)(~TIM_C3FILT_FILTEN);
    }
}

/**
*\*\name    TIM_IC4FiltEnable
*\*\fun     Enable or disable the filter of channel4.
*\*\param   TIMx:
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void TIM_IC4FiltEnable(TIM_Module* TIMx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the filter of CH4 */
        TIMx->C4FILT |= (uint32_t)TIM_C4FILT_FILTEN;
    }
    else
    {
        /* Disable the filter of CH4 */
        TIMx->C4FILT &= (uint32_t)(~TIM_C4FILT_FILTEN);
    }
}

/**
*\*\name    TIM_GetFiltStatus
*\*\fun     Checks the specified filter status.
*\*\param   TIMx (The input parameters must be the following values):
*\*\          - GTIMA1
*\*\          - GTIMA2
*\*\          - GTIMA3
*\*\          - GTIMA4
*\*\          - GTIMA5
*\*\          - GTIMA6
*\*\          - GTIMA7
*\*\          - GTIMB1
*\*\          - GTIMB2
*\*\          - GTIMB3
*\*\param   TIM_FiltFlag :
*\*\          - TIM_C1FILTO
*\*\          - TIM_C2FILTO
*\*\          - TIM_C3FILTO
*\*\          - TIM_C4FILTO
*\*\return  The new state of TIM_FiltFlag (SET or RESET).
**/
FlagStatus TIM_GetFiltStatus(TIM_Module* TIMx, uint32_t TIM_FiltFlag)
{
    FlagStatus bitstatus;

    if ((TIMx->FILTO & TIM_FiltFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}
