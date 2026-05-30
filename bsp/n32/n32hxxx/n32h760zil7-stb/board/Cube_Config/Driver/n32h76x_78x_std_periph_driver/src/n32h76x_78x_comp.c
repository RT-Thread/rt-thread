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
 * @file n32h76x_78x_comp.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_comp.h"
#include "n32h76x_78x_rcc.h"



#define  COMP3_4_FUNCTION_ENABLE_MASK   (0x00010000u)

/** COMP Driving Functions Declaration **/

/**
*\*\name    COMP_DeInit.
*\*\fun     Reset the COMP registers.
*\*\return  none
**/
void COMP_DeInit(void)
{
    RCC_EnableRDPeriphReset2(RCC_RD_PERIPHRST_COMP);
    /*Disable COMP3/4 Function*/
    AFEC->TRIMR6 &= (~COMP3_4_FUNCTION_ENABLE_MASK);
}
/**
*\*\name    COMP_StructInit.
*\*\fun     Fills all COMP_initstruct member with default value.
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\          - Hyst
*\*\          - PolRev
*\*\          - InpSel
*\*\          - InmSel
*\*\          - FilterEn
*\*\          - ClkPsc
*\*\          - SampWindow
*\*\          - Threshold
*\*\          - En
*\*\return  none
**/
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
    /* Initialize the Blking */
    COMP_InitStruct->Blking     = COMP_CTRL_BLKING_NO;
    /* Initialize the Hyst */
    COMP_InitStruct->Hyst       = COMP_CTRL_HYST_NO;
    /* Initialize the PolRev */
    COMP_InitStruct->PolRev     = DISABLE;
    /* Initialize the InpSel */
    COMP_InitStruct->InpSel     = COMPX_CTRL_INPSEL_RES;
    /* Initialize the InmSel */
    COMP_InitStruct->InmSel     = COMPX_CTRL_INMSEL_RES;
    /* Initialize the FilterEn */
    COMP_InitStruct->FilterEn   = DISABLE;
    /* Initialize the ClkPsc */
    COMP_InitStruct->ClkPsc     = 0;
    /* Initialize the SampWindow */
    COMP_InitStruct->SampWindow = 0;
    /* Initialize the Threshold */
    COMP_InitStruct->Threshold  = 0;
    /* Initialize the En */
    COMP_InitStruct->En         = DISABLE;
}
/**
*\*\name    COMP_Initializes.
*\*\fun     Initializes the COMPx according to COMP_initstruct.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\            - COMP_CTRL_BLKING_NO
*\*\            - COMP_CTRL_BLKING_ATIM1_OC5
*\*\            - COMP_CTRL_BLKING_GTIMB1_OC5
*\*\            - COMP_CTRL_BLKING_GTIMB2_OC5
*\*\            - COMP_CTRL_BLKING_ATIM2_OC5
*\*\            - COMP_CTRL_BLKING_ATIM3_OC5
*\*\            - COMP_CTRL_BLKING_ATIM4_OC1
*\*\            - COMP_CTRL_BLKING_GTIMB3_OC5
*\*\            - COMP_CTRL_BLKING_GTIMA4_OC5
*\*\            - COMP_CTRL_BLKING_GTIMA2_OC3
*\*\            - COMP_CTRL_BLKING_GTIMA1_OC3
*\*\            - COMP_CTRL_BLKING_GTIMA3_OC3
*\*\            - COMP_CTRL_BLKING_GTIMA5_OC3
*\*\            - COMP_CTRL_BLKING_GTIMA6_OC3
*\*\            - COMP_CTRL_BLKING_GTIMA7_OC3
*\*\          - Hyst
*\*\            - COMP_CTRL_HYST_NO
*\*\            - COMP_CTRL_HYST_LOW:
*\*\            - COMP_CTRL_HYST_MID:
*\*\            - COMP_CTRL_HYST_HIGH:
*\*\          - PolRev
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - vpsel
*\*\            comp1 inp sel
*\*\            - COMP1_CTRL_INPSEL_PB0
*\*\            - COMP1_CTRL_INPSEL_PB2
*\*\            - COMP1_CTRL_INPSEL_DAC1_IOUT
*\*\            - COMP1_CTRL_INPSEL_DAC2_IOUT
*\*\            - COMP1_CTRL_INPSEL_DAC3_IOUT
*\*\            - COMP1_CTRL_INPSEL_DAC4_IOUT
*\*\            - COMP1_CTRL_INPSEL_DAC5_IOUT
*\*\            - COMP1_CTRL_INPSEL_DAC6_IOUT
*\*\            - COMP1_CTRL_INPSEL_VREF1
*\*\            - COMP1_CTRL_INPSEL_PF5
*\*\            comp2 inp sel
*\*\            - COMP2_CTRL_INPSEL_PE9
*\*\            - COMP2_CTRL_INPSEL_PE11
*\*\            - COMP2_CTRL_INPSEL_DAC1_IOUT
*\*\            - COMP2_CTRL_INPSEL_DAC2_IOUT
*\*\            - COMP2_CTRL_INPSEL_DAC3_IOUT
*\*\            - COMP2_CTRL_INPSEL_DAC4_IOUT
*\*\            - COMP2_CTRL_INPSEL_DAC5_IOUT
*\*\            - COMP2_CTRL_INPSEL_DAC6_IOUT
*\*\            - COMP2_CTRL_INPSEL_VREF2
*\*\            - COMP2_CTRL_INPSEL_PB2
*\*\            - COMP2_CTRL_INPSEL_PF7
*\*\            comp3 inp sel
*\*\            - COMP3_CTRL_INPSEL_PF2
*\*\            - COMP3_CTRL_INPSEL_PF15
*\*\            - COMP3_CTRL_INPSEL_DAC1_IOUT
*\*\            - COMP3_CTRL_INPSEL_DAC2_IOUT
*\*\            - COMP3_CTRL_INPSEL_DAC3_IOUT
*\*\            - COMP3_CTRL_INPSEL_DAC4_IOUT
*\*\            - COMP3_CTRL_INPSEL_DAC5_IOUT
*\*\            - COMP3_CTRL_INPSEL_DAC6_IOUT
*\*\            comp4 inp sel
*\*\            - COMP4_CTRL_INPSEL_PH10
*\*\            - COMP4_CTRL_INPSEL_PH7
*\*\            - COMP4_CTRL_INPSEL_DAC1_IOUT
*\*\            - COMP4_CTRL_INPSEL_DAC2_IOUT
*\*\            - COMP4_CTRL_INPSEL_DAC3_IOUT
*\*\            - COMP4_CTRL_INPSEL_DAC4_IOUT
*\*\            - COMP4_CTRL_INPSEL_DAC5_IOUT
*\*\            - COMP4_CTRL_INPSEL_DAC6_IOUT
*\*\            - COMP4_CTRL_INPSEL_PF15
*\*\            - COMP4_CTRL_INPSEL_PF10
*\*\          - InmSel
*\*\            comp1 inm sel
*\*\            - COMP1_CTRL_INMSEL_PB1
*\*\            - COMP1_CTRL_INMSEL_PC4
*\*\            - COMP1_CTRL_INMSEL_DAC1_IOUT
*\*\            - COMP1_CTRL_INMSEL_DAC2_IOUT
*\*\            - COMP1_CTRL_INMSEL_DAC3_IOUT
*\*\            - COMP1_CTRL_INMSEL_DAC4_IOUT
*\*\            - COMP1_CTRL_INMSEL_DAC5_IOUT
*\*\            - COMP1_CTRL_INMSEL_DAC6_IOUT
*\*\            - COMP1_CTRL_INMSEL_VREF1
*\*\            - COMP1_CTRL_INMSEL_PF3
*\*\            comp2 inm sel
*\*\            - COMP2_CTRL_INMSEL_PE7
*\*\            - COMP2_CTRL_INMSEL_PE10
*\*\            - COMP2_CTRL_INMSEL_DAC1_IOUT
*\*\            - COMP2_CTRL_INMSEL_DAC2_IOUT
*\*\            - COMP2_CTRL_INMSEL_DAC3_IOUT
*\*\            - COMP2_CTRL_INMSEL_DAC4_IOUT
*\*\            - COMP2_CTRL_INMSEL_DAC5_IOUT
*\*\            - COMP2_CTRL_INMSEL_DAC6_IOUT
*\*\            - COMP2_CTRL_INMSEL_VREF2
*\*\            - COMP2_CTRL_INMSEL_PF6
*\*\            comp3 inm sel
*\*\            - COMP3_CTRL_INMSEL_PF1
*\*\            - COMP3_CTRL_INMSEL_PF14
*\*\            - COMP3_CTRL_INMSEL_DAC1_IOUT
*\*\            - COMP3_CTRL_INMSEL_DAC2_IOUT
*\*\            - COMP3_CTRL_INMSEL_DAC3_IOUT
*\*\            - COMP3_CTRL_INMSEL_DAC4_IOUT
*\*\            - COMP3_CTRL_INMSEL_DAC5_IOUT
*\*\            - COMP3_CTRL_INMSEL_DAC6_IOUT
*\*\            comp4 inm sel
*\*\            - COMP4_CTRL_INMSEL_PH9
*\*\            - COMP4_CTRL_INMSEL_PH6
*\*\            - COMP4_CTRL_INMSEL_DAC1_IOUT
*\*\            - COMP4_CTRL_INMSEL_DAC2_IOUT
*\*\            - COMP4_CTRL_INMSEL_DAC3_IOUT
*\*\            - COMP4_CTRL_INMSEL_DAC4_IOUT
*\*\            - COMP4_CTRL_INMSEL_DAC5_IOUT
*\*\            - COMP4_CTRL_INMSEL_DAC6_IOUT
*\*\            - COMP4_CTRL_INMSEL_PH8
*\*\          - En
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - SampWindow
*\*\            - SampWindow Value ranges from 0~31.
*\*\          - Threshold
*\*\            - Threshold Value need > SampWindow/2.
*\*\          - FilterEn
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - ClkPsc
*\*\            - ClkPsc Value ranges from 0~65535.
*\*\return  none
**/
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct)
{
    COMP_SingleType* pCS = &COMP->Cmp[COMPx];
    __IO uint32_t temp = 0;

    /* Get the old value from COMPx_FILC register*/
    temp = pCS->FILC;
    /* Set SAMPW[4:0] select bits */
    temp  = ( ((uint32_t)COMP_InitStruct->SampWindow) << 6 ) & COMP_FILC_SAMPW_MASK;
    /* Set THRESH[4:0] select bits */
    temp += ( ((uint32_t)COMP_InitStruct->Threshold)  << 1 ) & COMP_FILC_THRESH_MASK;
    /* Set FILEN select bits */
    temp += ( (uint32_t)COMP_InitStruct->FilterEn )& COMP_FILC_FILEN_MASK;
    /* Store the new register value */
    pCS->FILC = temp;
    /* Set CLKPSC[15:0] select bits from COMPx_FILP register*/
    pCS->FILP = COMP_InitStruct->ClkPsc;

    /* Get the old value from COMPx_CTRL register*/
    temp = pCS->CTRL;
    /* Clear BLKING[3:0], BLKINGEN, POL, INMSEL[3:0], INPSEL[3:0] select bits */
    temp &= (~(COMP_CTRL_BLKING_MASK | COMP_CTRL_HYST_MASK | COMP_POL_MASK | COMP_CTRL_INPSEL_MASK | COMP_CTRL_INMSEL_MASK | COMP_CTRL_EN_MASK));
    /* Set BLKING[3:0], BLKINGEN, POL, INMSEL[3:0], INPSEL[3:0] select bits */
    temp |= ((uint32_t)COMP_InitStruct->Blking | (uint32_t)COMP_InitStruct->Hyst | \
             (uint32_t)COMP_InitStruct->InpSel | (uint32_t)COMP_InitStruct->InmSel);

    if(COMP_InitStruct->PolRev != DISABLE)
    {
        temp |= COMP_OUTPOL_FLIP ;
    }
    else
    {
        temp &= (~COMP_OUTPOL_FLIP);
    }

    if(COMP_InitStruct->En != DISABLE)
    {
        temp |= COMP_CTRL_EN_MASK ;
    }
    else
    {
        temp &= (~COMP_CTRL_EN_MASK);
    }

    /* Store the new register value */
    pCS->CTRL = temp;
}
/**
*\*\name    COMP_Enable.
*\*\fun     Configures COMPx enable or disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_Enable(COMPX COMPx, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        if( (COMPx == COMP3) || (COMPx == COMP4))
        {
            /*Enable COMP3/4 Function*/
            AFEC->TRIMR6 |= COMP3_4_FUNCTION_ENABLE_MASK;
        }
        else
        {
            /* no process */
        }

        COMP->Cmp[COMPx].CTRL |= COMP_CTRL_EN_MASK;
    }
    else
    {
        COMP->Cmp[COMPx].CTRL &= (~COMP_CTRL_EN_MASK);
    }
}
/**
*\*\name    COMP_SetInpSel.
*\*\fun     Select COMPx Non-inverting input.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   vpsel :
*\*\        comp1 inp sel
*\*\          - COMP1_CTRL_INPSEL_PB0
*\*\          - COMP1_CTRL_INPSEL_PB2
*\*\          - COMP1_CTRL_INPSEL_DAC1_IOUT
*\*\          - COMP1_CTRL_INPSEL_DAC2_IOUT
*\*\          - COMP1_CTRL_INPSEL_DAC3_IOUT
*\*\          - COMP1_CTRL_INPSEL_DAC4_IOUT
*\*\          - COMP1_CTRL_INPSEL_DAC5_IOUT
*\*\          - COMP1_CTRL_INPSEL_DAC6_IOUT
*\*\          - COMP1_CTRL_INPSEL_VREF1
*\*\          - COMP1_CTRL_INPSEL_PF5
*\*\        comp2 inp sel
*\*\          - COMP2_CTRL_INPSEL_PE9
*\*\          - COMP2_CTRL_INPSEL_PE11
*\*\          - COMP2_CTRL_INPSEL_DAC1_IOUT
*\*\          - COMP2_CTRL_INPSEL_DAC2_IOUT
*\*\          - COMP2_CTRL_INPSEL_DAC3_IOUT
*\*\          - COMP2_CTRL_INPSEL_DAC4_IOUT
*\*\          - COMP2_CTRL_INPSEL_DAC5_IOUT
*\*\          - COMP2_CTRL_INPSEL_DAC6_IOUT
*\*\          - COMP2_CTRL_INPSEL_VREF2
*\*\          - COMP2_CTRL_INPSEL_PB2
*\*\          - COMP2_CTRL_INPSEL_PF7
*\*\        comp3 inp sel
*\*\          - COMP3_CTRL_INPSEL_PF2
*\*\          - COMP3_CTRL_INPSEL_PF15
*\*\          - COMP3_CTRL_INPSEL_DAC1_IOUT
*\*\          - COMP3_CTRL_INPSEL_DAC2_IOUT
*\*\          - COMP3_CTRL_INPSEL_DAC3_IOUT
*\*\          - COMP3_CTRL_INPSEL_DAC4_IOUT
*\*\          - COMP3_CTRL_INPSEL_DAC5_IOUT
*\*\          - COMP3_CTRL_INPSEL_DAC6_IOUT
*\*\        comp4 inp sel
*\*\          - COMP4_CTRL_INPSEL_PH10
*\*\          - COMP4_CTRL_INPSEL_PH7
*\*\          - COMP4_CTRL_INPSEL_DAC1_IOUT
*\*\          - COMP4_CTRL_INPSEL_DAC2_IOUT
*\*\          - COMP4_CTRL_INPSEL_DAC3_IOUT
*\*\          - COMP4_CTRL_INPSEL_DAC4_IOUT
*\*\          - COMP4_CTRL_INPSEL_DAC5_IOUT
*\*\          - COMP4_CTRL_INPSEL_DAC6_IOUT
*\*\          - COMP4_CTRL_INPSEL_PF15
*\*\          - COMP4_CTRL_INPSEL_PF10
*\*\return  none
**/
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel)
{
    __IO uint32_t tmp ;
    /* Get the old value from COMPx_CTRL register*/
    tmp = COMP->Cmp[COMPx].CTRL;
    /* Clear INPSEL[3:0] select bits */
    tmp &= (~COMP_CTRL_INPSEL_MASK);
    /* Set INPSEL[3:0] select bits */
    tmp |= (uint32_t)VpSel;
    /* Store the new register value */
    COMP->Cmp[COMPx].CTRL = tmp;
}
/**
*\*\name    COMP_SetInmSel.
*\*\fun     Select COMPx inverting input.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   vmsel :
*\*\        comp1 inm sel
*\*\          - COMP1_CTRL_INMSEL_PB1
*\*\          - COMP1_CTRL_INMSEL_PC4
*\*\          - COMP1_CTRL_INMSEL_DAC1_IOUT
*\*\          - COMP1_CTRL_INMSEL_DAC2_IOUT
*\*\          - COMP1_CTRL_INMSEL_DAC3_IOUT
*\*\          - COMP1_CTRL_INMSEL_DAC4_IOUT
*\*\          - COMP1_CTRL_INMSEL_DAC5_IOUT
*\*\          - COMP1_CTRL_INMSEL_DAC6_IOUT
*\*\          - COMP1_CTRL_INMSEL_VREF1
*\*\          - COMP1_CTRL_INMSEL_PF3
*\*\        comp2 inm sel
*\*\          - COMP2_CTRL_INMSEL_PE7
*\*\          - COMP2_CTRL_INMSEL_PE10
*\*\          - COMP2_CTRL_INMSEL_DAC1_IOUT
*\*\          - COMP2_CTRL_INMSEL_DAC2_IOUT
*\*\          - COMP2_CTRL_INMSEL_DAC3_IOUT
*\*\          - COMP2_CTRL_INMSEL_DAC4_IOUT
*\*\          - COMP2_CTRL_INMSEL_DAC5_IOUT
*\*\          - COMP2_CTRL_INMSEL_DAC6_IOUT
*\*\          - COMP2_CTRL_INMSEL_VREF2
*\*\          - COMP2_CTRL_INMSEL_PF6
*\*\        comp3 inm sel
*\*\          - COMP3_CTRL_INMSEL_PF1
*\*\          - COMP3_CTRL_INMSEL_PF14
*\*\          - COMP3_CTRL_INMSEL_DAC1_IOUT
*\*\          - COMP3_CTRL_INMSEL_DAC2_IOUT
*\*\          - COMP3_CTRL_INMSEL_DAC3_IOUT
*\*\          - COMP3_CTRL_INMSEL_DAC4_IOUT
*\*\          - COMP3_CTRL_INMSEL_DAC5_IOUT
*\*\          - COMP3_CTRL_INMSEL_DAC6_IOUT
*\*\        comp4 inm sel
*\*\          - COMP4_CTRL_INMSEL_PH9
*\*\          - COMP4_CTRL_INMSEL_PH6
*\*\          - COMP4_CTRL_INMSEL_DAC1_IOUT
*\*\          - COMP4_CTRL_INMSEL_DAC2_IOUT
*\*\          - COMP4_CTRL_INMSEL_DAC3_IOUT
*\*\          - COMP4_CTRL_INMSEL_DAC4_IOUT
*\*\          - COMP4_CTRL_INMSEL_DAC5_IOUT
*\*\          - COMP4_CTRL_INMSEL_DAC6_IOUT
*\*\          - COMP4_CTRL_INMSEL_PH8
*\*\return  none
**/
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel)
{
    __IO uint32_t tmp ;
    /* Get the old value from COMPx_CTRL register*/
    tmp = COMP->Cmp[COMPx].CTRL;
    /* Clear INMSEL[3:0] select bits */
    tmp &= (~COMP_CTRL_INMSEL_MASK);
    /* Set INMSEL[3:0] select bits */
    tmp |= (uint32_t)VmSel;
    /* Store the new register value */
    COMP->Cmp[COMPx].CTRL = tmp;
}

/**
*\*\name    COMP_SetLowPowerMode.
*\*\fun     Enables or disables working in low power mode for COMP.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_SetLowPowerMode(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable low power mode */
        COMP->LPR |= (uint32_t)COMP_LPMODE_LP_EN_MASK;
    }
    else
    {
        /* Disable low power mode */
        COMP->LPR &= (~(uint32_t)COMP_LPMODE_LP_EN_MASK);
    }
}

/**
*\*\name    COMP_SetLock.
*\*\fun     Configures which COMPx will be Locked.
*\*\param   Lock :
*\*\          - COMP1_LOCK
*\*\          - COMP2_LOCK
*\*\          - COMP3_LOCK
*\*\          - COMP4_LOCK
*\*\return  none
**/
void COMP_SetLock(uint32_t Lock)
{
    COMP->LOCK = Lock;
}

/**
*\*\name    COMP_SetIntEn.
*\*\fun     Configures COMPx interrupt enable or disable.
*\*\param   IntEn :
*\*\          - COMP1_INTEN
*\*\          - COMP2_INTEN
*\*\          - COMP3_INTEN
*\*\          - COMP4_INTEN
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->INTEN |= IntEn;
    }
    else
    {
        COMP->INTEN &= ~IntEn;
    }
}

/**
*\*\name    COMP_WindowModeEnable.
*\*\fun     Configures COMPx window mode enable or disable.
*\*\param   WinModeEn :
*\*\          - COMP_WINMODE_CMP12MD
*\*\          - COMP_WINMODE_CMP34MD
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_WindowModeEnable(uint32_t WinModeEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->WINMODE |= WinModeEn;
    }
    else
    {
        COMP->WINMODE &= (~WinModeEn);
    }
}
/**
*\*\name    COMP_SetRefScl.
*\*\fun     Configures the COMP reference voltage.
*\*\param   Vv2Trim :
*\*\          - Value can be set from 0 to 63.
*\*\param   Vv2En :
*\*\          - false
*\*\          - true
*\*\param   Vv1Trim :
*\*\           - Value can be set from 0 to 63.
*\*\param   Vv1En :
*\*\          - false
*\*\          - true
*\*\return  none
**/
void COMP_SetRefScl( uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En)
{
    __IO uint32_t temp = 0;
    /* Get the old value from COMP1_CTRL register*/
    temp = COMP->Cmp[COMP1].CTRL;
    /* Clear VV1EN, VV1TRM[5:0] select bits */
    temp &= (~(COMP_VREFSCL_VVEN_MSK | COMP_VREFSCL_VVTRM_MSK ) );
    /* Set VV1EN, VV1TRM[5:0] select bits */
    temp |= ((uint32_t)(Vv1En ? (1UL << 22U) : 0) + ((uint32_t)Vv1Trim << 23U )) ;
    /* Store the new register value */
    COMP->Cmp[COMP1].CTRL = temp;

    /* Get the old value from COMP2_CTRL register*/
    temp = COMP->Cmp[COMP2].CTRL;
    /* Clear VV2EN, VV2TRM[5:0] select bits */
    temp &= (~(COMP_VREFSCL_VVEN_MSK | COMP_VREFSCL_VVTRM_MSK ) );
    /* Set VV2EN, VV2TRM[5:0] select bits */
    temp |= ((uint32_t)(Vv2En ? (1UL << 22U) : 0) + ((uint32_t)Vv2Trim << 23U )) ;
    /* Store the new register value */
    COMP->Cmp[COMP2].CTRL = temp;
}
/**
*\*\name    COMP_GetOutStatus.
*\*\fun     Get COMPx output status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetOutStatus(COMPX COMPx)
{
    return ((COMP->Cmp[COMPx].CTRL & COMP_CTRL_OUT_MASK) != 0U) ? SET : RESET;
}

/**
*\*\name    COMP_GetIntStsOneComp.
*\*\fun     Get COMPx interrupt Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\return
*\*\          - RESET : COMPx Interrupt status is reset;
*\*\          - SET   : COMPx Interrupt status is set;
**/
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx)
{
    return ((COMP->INTSTS & ((uint32_t)0x01U << COMPx)) != 0U) ? SET : RESET;
}

/**
*\*\name    COMP_ClearIntStsOneComp.
*\*\fun     Clear COMPx interrupt Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\return  none
**/
void COMP_ClearIntStsOneComp(COMPX COMPx)
{
    COMP->INTSTS &= ((~(0x01U << COMPx )));
}

/**
*\*\name    COMP_OutToTimEnable.
*\*\fun     Enable or disable the output channel to timer .
*\*\param   TimEn :
*\*\          - COMP1_TIM_EN
*\*\          - COMP2_TIM_EN
*\*\          - COMP3_TIM_EN
*\*\          - COMP4_TIM_EN
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_OutToTimEnable(uint32_t TimEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->OTIMEN |= TimEn;
    }
    else
    {
        COMP->OTIMEN &= (~TimEn);
    }
}

/**
*\*\name    COMP_SetFilterPrescaler.
*\*\fun     Set the COMP filter clock Prescaler value.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   FilPreVal :
*\*\          -  Value can be set from 0 to 65535.
*\*\return  none
**/
void COMP_SetFilterPrescaler(COMPX COMPx, uint16_t FilPreVal)
{
    COMP->Cmp[COMPx].FILP = FilPreVal;
}

/**
*\*\name    COMP_SetFilterControl.
*\*\fun     Configures the COMP filter control value.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   FilEn :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\param   TheresNum :
*\*\          - Threshold Value need > SampWindow/2.
*\*\param   SampPW :
*\*\          -  Value can be set from 0 to 31.
*\*\return  none
**/
void COMP_SetFilterControl(COMPX COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW)
{
    COMP->Cmp[COMPx].FILC = (uint32_t)(FilEn & COMP_FILC_FILEN_MASK) + (((uint32_t)TheresNum << 1)&COMP_FILC_THRESH_MASK) + (((uint32_t)SampPW << 6)& COMP_FILC_SAMPW_MASK);
}

/**
*\*\name    COMP_SetVflagEnable.
*\*\fun     Enable or disable using DAC stable value as Comparator's positive or negetive inputs.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\param   InputMode :
*\*\          - COMP_VFLAG_P
*\*\          - COMP_VFLAG_N
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note COMP3 and COMP4 couldn't using this fuction.
**/
void COMP_EnableVflag(COMPX COMPx, uint32_t InputMode, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].FILC |= InputMode;
    }
    else
    {
        COMP->Cmp[COMPx].FILC &= (~InputMode);
    }
}


/**
*\*\name    COMP_SetHyst.
*\*\fun     Configures COMPx hysteresis level.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   HYST :
*\*\          - COMP_CTRL_HYST_NO
*\*\          - COMP_CTRL_HYST_LOW
*\*\          - COMP_CTRL_HYST_MID
*\*\          - COMP_CTRL_HYST_HIGH
*\*\return  none
**/
void COMP_SetHyst(COMPX COMPx, COMP_CTRL_HYST HYST)
{
    uint32_t temp;
    /* Get the old value from COMPx_CTRL register*/
    temp  = COMP->Cmp[COMPx].CTRL;
    /* Clear HYST[1:0] select bits */
    temp &= (~COMP_CTRL_HYST_MASK);
    /* Set HYST[1:0] select bits */
    temp |= (uint32_t)HYST;
    /* Store the new register value */
    COMP->Cmp[COMPx].CTRL = temp;
}

/**
*\*\name    COMP_SetBlanking.
*\*\fun     Configures which TIMx output signal to control COMPx Blking.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   BLK :
*\*\          - COMP_CTRL_BLKING_NO
*\*\          - COMP_CTRL_BLKING_ATIM1_OC5
*\*\          - COMP_CTRL_BLKING_GTIMB1_OC5
*\*\          - COMP_CTRL_BLKING_GTIMB2_OC5
*\*\          - COMP_CTRL_BLKING_ATIM2_OC5
*\*\          - COMP_CTRL_BLKING_ATIM3_OC5
*\*\          - COMP_CTRL_BLKING_ATIM4_OC1
*\*\          - COMP_CTRL_BLKING_GTIMB3_OC5
*\*\          - COMP_CTRL_BLKING_GTIMA4_OC5
*\*\          - COMP_CTRL_BLKING_GTIMA2_OC3
*\*\          - COMP_CTRL_BLKING_GTIMA1_OC3
*\*\          - COMP_CTRL_BLKING_GTIMA3_OC3
*\*\          - COMP_CTRL_BLKING_GTIMA5_OC3
*\*\          - COMP_CTRL_BLKING_GTIMA6_OC3
*\*\          - COMP_CTRL_BLKING_GTIMA7_OC3
*\*\return  none
**/
void COMP_SetBlanking(COMPX COMPx, COMP_CTRL_BLKING BLK)
{
    uint32_t temp;
    /* Get the old value from COMPx_CTRL register*/
    temp  = COMP->Cmp[COMPx].CTRL;
    /* Clear HYST[3:0] select bits */
    temp &= (~COMP_CTRL_BLKING_MASK);
    /* Set HYST[3:0] select bits */
    temp |= (uint32_t)BLK;
    /* Store the new register value */
    COMP->Cmp[COMPx].CTRL = temp;
}

