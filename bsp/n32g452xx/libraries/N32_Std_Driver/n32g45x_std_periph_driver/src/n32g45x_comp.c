/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_comp.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_comp.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup COMP
 * @brief COMP driver modules
 * @{
 */

/** @addtogroup COMP_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Functions
 * @{
 */
#define SetBitMsk(reg, bit, msk) ((reg) = ((reg) & ~(msk) | (bit)))
#define ClrBit(reg, bit)         ((reg) &= ~(bit))
#define SetBit(reg, bit)         ((reg) |= (bit))
#define GetBit(reg, bit)         ((reg) & (bit))
/**
 * @brief  Deinitializes the COMP peripheral registers to their default reset values.
 */
void COMP_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_COMP, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_COMP, DISABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_COMP_FILT, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_COMP_FILT, DISABLE);
}
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
    COMP_InitStruct->InpDacConnect = false; // only COMP1 have this bit

    COMP_InitStruct->Blking = COMP_CTRL_BLKING_NO; /*see @ref COMP_CTRL_BLKING */

    COMP_InitStruct->Hyst = COMP_CTRL_HYST_NO; // see @COMPx_CTRL_HYST_MASK

    COMP_InitStruct->PolRev = false; // out polarity reverse

    COMP_InitStruct->OutSel = COMPX_CTRL_OUTSEL_NC;
    COMP_InitStruct->InpSel = COMPX_CTRL_INPSEL_RES;
    COMP_InitStruct->InmSel = COMPX_CTRL_INMSEL_RES;

    COMP_InitStruct->En = false;
}
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct)
{
    COMP_SingleType* pCS = &COMP->Cmp[COMPx];
    __IO uint32_t tmp;

    // filter
    tmp = pCS->FILC;
    SetBitMsk(tmp, COMP_InitStruct->SampWindow << 6, COMP_FILC_SAMPW_MASK);
    SetBitMsk(tmp, COMP_InitStruct->Thresh << 1, COMP_FILC_THRESH_MASK);
    SetBitMsk(tmp, COMP_InitStruct->FilterEn << 0, COMP_FILC_FILEN_MASK);
    pCS->FILC = tmp;
    // filter psc
    pCS->FILP = COMP_InitStruct->ClkPsc;

    // ctrl
    tmp = pCS->CTRL;
    if (COMPx == COMP1)
    {
        if (COMP_InitStruct->InpDacConnect)
            SetBit(tmp, COMP1_CTRL_INPDAC_MASK);
        else
            ClrBit(tmp, COMP1_CTRL_INPDAC_MASK);
    }
    SetBitMsk(tmp, COMP_InitStruct->Blking, COMP_CTRL_BLKING_MASK);
    SetBitMsk(tmp, COMP_InitStruct->Hyst, COMPx_CTRL_HYST_MASK);
    if (COMP_InitStruct->PolRev)
        SetBit(tmp, COMP_POL_MASK);
    else
        ClrBit(tmp, COMP_POL_MASK);
    SetBitMsk(tmp, COMP_InitStruct->OutSel, COMP_CTRL_OUTSEL_MASK);
    SetBitMsk(tmp, COMP_InitStruct->InpSel, COMP_CTRL_INPSEL_MASK);
    SetBitMsk(tmp, COMP_InitStruct->InmSel, COMP_CTRL_INMSEL_MASK);
    if (COMP_InitStruct->En)
        SetBit(tmp, COMP_CTRL_EN_MASK);
    else
        ClrBit(tmp, COMP_CTRL_EN_MASK);
    pCS->CTRL = tmp;
}
void COMP_Enable(COMPX COMPx, FunctionalState en)
{
    if (en)
        SetBit(COMP->Cmp[COMPx].CTRL, COMP_CTRL_EN_MASK);
    else
        ClrBit(COMP->Cmp[COMPx].CTRL, COMP_CTRL_EN_MASK);
}

void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;
    SetBitMsk(tmp, VpSel, COMP_CTRL_INPSEL_MASK);
    COMP->Cmp[COMPx].CTRL = tmp;
}
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;
    SetBitMsk(tmp, VmSel, COMP_CTRL_INMSEL_MASK);
    COMP->Cmp[COMPx].CTRL = tmp;
}
void COMP_SetOutTrig(COMPX COMPx, COMP_CTRL_OUTTRIG OutTrig)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;
    SetBitMsk(tmp, OutTrig, COMP_CTRL_OUTSEL_MASK);
    COMP->Cmp[COMPx].CTRL = tmp;
}
// Lock see @COMP_LOCK
void COMP_SetLock(uint32_t Lock)
{
    COMP->LOCK = Lock;
}
// IntEn see @COMP_INTEN_CMPIEN
void COMP_SetIntEn(uint32_t IntEn)
{
    COMP->INTEN = IntEn;
}
// return see @COMP_INTSTS_CMPIS
uint32_t COMP_GetIntSts(void)
{
    return COMP->INTSTS;
}
// parma range see @COMP_VREFSCL
// Vv2Trim,Vv1Trim max 63
void COMP_SetRefScl(uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En)
{
    __IO uint32_t tmp = 0;

    SetBitMsk(tmp, Vv2Trim << 8, COMP_VREFSCL_VV2TRM_MSK);
    SetBitMsk(tmp, Vv2En << 7, COMP_VREFSCL_VV2EN_MSK);
    SetBitMsk(tmp, Vv1Trim << 1, COMP_VREFSCL_VV1TRM_MSK);
    SetBitMsk(tmp, Vv1En << 0, COMP_VREFSCL_VV1EN_MSK);

    COMP->VREFSCL = tmp;
}
// SET when comp out 1
// RESET when comp out 0
FlagStatus COMP_GetOutStatus(COMPX COMPx)
{
    return (COMP->Cmp[COMPx].CTRL & COMP_CTRL_OUT_MASK) ? SET : RESET;
}
// get one comp interrupt flags
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx)
{
    return (COMP_GetIntSts() & (0x01 << COMPx)) ? SET : RESET;
}

/**
 * @brief  Set the COMP filter clock Prescaler value.
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param FilPreVal Prescaler Value,Div clock = FilPreVal+1.
 * @return void
 */
void COMP_SetFilterPrescaler(COMPX COMPx , uint16_t FilPreVal)
{
    COMP->Cmp[COMPx].FILP=FilPreVal;
}

/**
 * @brief  Set the COMP filter control value.
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param FilEn 1 for enable ,0 or disable
 * @param TheresNum  num under this value is noise
 * @param SampPW  total sample number in a window
 * @return void
 */
void COMP_SetFilterControl(COMPX COMPx , uint8_t FilEn, uint8_t TheresNum , uint8_t SampPW)
{
    COMP->Cmp[COMPx].FILC=(FilEn&COMP_FILC_FILEN_MASK)+((TheresNum<<1)&COMP_FILC_THRESH_MASK)+((SampPW<<6)&COMP_FILC_SAMPW_MASK);
}

/**
 * @brief  Set the COMP Hyst value.
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param HYST specifies the HYST level.
 *   This parameter can be one of the following values:
*     @arg COMP_CTRL_HYST_NO Hyst disable
*     @arg COMP_CTRL_HYST_LOW Hyst level 5.1mV
*     @arg COMP_CTRL_HYST_MID Hyst level 15mV
*     @arg COMP_CTRL_HYST_HIGH Hyst level 25mV
 * @return void
 */
void COMP_SetHyst(COMPX COMPx , COMP_CTRL_HYST HYST)
{
    uint32_t tmp=COMP->Cmp[COMPx].CTRL;
    tmp&=~COMP_CTRL_HYST_HIGH;
    tmp|=HYST;
    COMP->Cmp[COMPx].CTRL=tmp;
}

/**
 * @brief  Set the COMP Blanking source .
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param BLK specifies the blanking source .
 *   This parameter can be one of the following values:
*     @arg COMP_CTRL_BLKING_NO Blanking  disable
*     @arg COMP_CTRL_BLKING_TIM1_OC5 Blanking source TIM1_OC5
*     @arg COMP_CTRL_BLKING_TIM8_OC5 Blanking source TIM8_OC5
 * @return void
 */
void COMP_SetBlanking(COMPX COMPx , COMP_CTRL_BLKING BLK)
{
    uint32_t tmp=COMP->Cmp[COMPx].CTRL;
    tmp&=~(7<<14);
    tmp|=BLK;
    COMP->Cmp[COMPx].CTRL=tmp;
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
