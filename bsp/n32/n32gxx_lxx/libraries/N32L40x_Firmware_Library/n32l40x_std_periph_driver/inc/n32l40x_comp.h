/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
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
 * @file n32l40x_comp.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32L40X_COMP_H__
#define __N32L40X_COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"
#include <stdbool.h>

/** @addtogroup n32l40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup COMP
 * @{
 */

/** @addtogroup COMP_Exported_Constants
 * @{
 */
typedef enum
{
    COMP1 = 0,
    COMP2 = 1,
} COMPX;

// COMPx_CTRL
#define COMP1_CTRL_PWRMODE_MASK (0x01L << 21)
#define COMP1_CTRL_INPDAC_MASK  (0x01L << 20)
#define COMP_CTRL_OUT_MASK      (0x01L << 19)
#define COMP_CTRL_BLKING_MASK   (0x03L << 16)
typedef enum
{
    COMP_CTRL_BLKING_NO       = (0x0L << 16),
    COMP_CTRL_BLKING_TIM1_OC5 = (0x1L << 16),
    COMP_CTRL_BLKING_TIM8_OC5 = (0x2L << 16),
} COMP_CTRL_BLKING;
#define COMPx_CTRL_HYST_MASK (0x03L << 14)
typedef enum
{
    COMP_CTRL_HYST_NO   = (0x0L << 14),
    COMP_CTRL_HYST_LOW  = (0x1L << 14),
    COMP_CTRL_HYST_MID  = (0x2L << 14),
    COMP_CTRL_HYST_HIGH = (0x3L << 14),
} COMP_CTRL_HYST;

#define COMP_POL_MASK         (0x01L << 13)
#define COMP_CTRL_OUTSEL_MASK (0x0FL << 9)
typedef enum
{
    // comp1 out trig
    COMP1_CTRL_OUTSEL_NC                  = (0x0L << 9),
    COMP1_CTRL_OUTSEL_TIM1_BKIN           = (0x1L << 9),
    COMP1_CTRL_OUTSEL_TIM1_OCrefclear     = (0x2L << 9),
    COMP1_CTRL_OUTSEL_TIM1_IC1            = (0x3L << 9),
    COMP1_CTRL_OUTSEL_TIM2_IC1            = (0x4L << 9),
    COMP1_CTRL_OUTSEL_TIM2_OCrefclear     = (0x5L << 9),
    COMP1_CTRL_OUTSEL_TIM3_IC1            = (0x6L << 9),
    COMP1_CTRL_OUTSEL_TIM3_OCrefclear     = (0x7L << 9),
    COMP1_CTRL_OUTSEL_TIM4_OCrefclear     = (0x8L << 9),
    COMP1_CTRL_OUTSEL_TIM5_IC1            = (0x9L << 9),
    COMP1_CTRL_OUTSEL_TIM8_IC1            = (0xAL << 9),
    COMP1_CTRL_OUTSEL_TIM8_OCrefclear     = (0xBL << 9),
    COMP1_CTRL_OUTSEL_TIM9_OCrefclear     = (0xCL << 9),
    COMP1_CTRL_OUTSEL_TIM8_BKIN           = (0xDL << 9),
    COMP1_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN = (0xEL << 9),
    COMP1_CTRL_OUTSEL_LPTIM_ETR           = (0xFL << 9),
    // comp2 out trig
    COMP2_CTRL_OUTSEL_NC                  = (0x0L << 9),
    COMP2_CTRL_OUTSEL_TIM1_BKIN           = (0x1L << 9),
    COMP2_CTRL_OUTSEL_TIM1_OCrefclear     = (0x2L << 9),
    COMP2_CTRL_OUTSEL_TIM1_IC1            = (0x3L << 9),
    COMP2_CTRL_OUTSEL_TIM2_OCrefclear     = (0x4L << 9),
    COMP2_CTRL_OUTSEL_TIM3_OCrefclear     = (0x5L << 9),
    COMP2_CTRL_OUTSEL_TIM4_IC1            = (0x6L << 9),
    COMP2_CTRL_OUTSEL_TIM4_OCrefclear     = (0x7L << 9),
    COMP2_CTRL_OUTSEL_TIM5_IC1            = (0x8L << 9),
    COMP2_CTRL_OUTSEL_TIM8_IC1            = (0x9L << 9),
    COMP2_CTRL_OUTSEL_TIM8_OCrefclear     = (0xAL << 9),
    COMP2_CTRL_OUTSEL_TIM9_IC1            = (0xBL << 9),
    COMP2_CTRL_OUTSEL_TIM9_OCrefclear     = (0xCL << 9),
    COMP2_CTRL_OUTSEL_TIM8_BKIN           = (0xDL << 9),
    COMP2_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN = (0xEL << 9),
    COMP2_CTRL_OUTSEL_LPTIM_ETR           = (0xFL << 9),
} COMP_CTRL_OUTTRIG;

#define COMP_CTRL_INPSEL_MASK                       (0x0FL<<5)
typedef enum {
  //comp1 inp sel
  COMP1_CTRL_INPSEL_FLOAT       = ((uint32_t)0x00000000),
  COMP1_CTRL_INPSEL_PA0         = ((uint32_t)0x00000100),
  COMP1_CTRL_INPSEL_PA2         = ((uint32_t)0x00000140),
  COMP1_CTRL_INPSEL_PA12        = ((uint32_t)0x00000160),
  COMP1_CTRL_INPSEL_PB3         = ((uint32_t)0x00000180),
  COMP1_CTRL_INPSEL_PB4         = ((uint32_t)0x000001A0),
  COMP1_CTRL_INPSEL_PB10        = ((uint32_t)0x000001C0),
  COMP1_CTRL_INPSEL_PD5         = ((uint32_t)0x000001E0),
  COMP1_CTRL_INPSEL_PA1_DAC1    = ((uint32_t)0x00000120),
  //comp2 inp sel
  COMP2_CTRL_INPSEL_FLOAT       = ((uint32_t)0x00000000),
  COMP2_CTRL_INPSEL_PA1_DAC1_PA4= ((uint32_t)0x00000100),
  COMP2_CTRL_INPSEL_PA3         = ((uint32_t)0x00000120),
  COMP2_CTRL_INPSEL_PA6         = ((uint32_t)0x00000140),
  COMP2_CTRL_INPSEL_PA7         = ((uint32_t)0x00000160),
  COMP2_CTRL_INPSEL_PA11        = ((uint32_t)0x00000180),
  COMP2_CTRL_INPSEL_PA15        = ((uint32_t)0x000001A0),
  COMP2_CTRL_INPSEL_PB7         = ((uint32_t)0x000001C0),
  COMP2_CTRL_INPSEL_PD7         = ((uint32_t)0x000001E0),
}COMP_CTRL_INPSEL;


#define COMP_CTRL_INMSEL_MASK                       (0x07L<<1)
typedef enum {
  //comp1 inm sel
  COMP1_CTRL_INMSEL_DAC1_PA4    = ((uint32_t)0x00000002),
  COMP1_CTRL_INMSEL_PA0         = ((uint32_t)0x00000004),
  COMP1_CTRL_INMSEL_PA5         = ((uint32_t)0x00000006),
  COMP1_CTRL_INMSEL_PB5         = ((uint32_t)0x00000008),
  COMP1_CTRL_INMSEL_PD4         = ((uint32_t)0x0000000A),
  COMP1_CTRL_INMSEL_VREF_VC1    = ((uint32_t)0x0000000C),
  COMP1_CTRL_INMSEL_VREF_VC2    = ((uint32_t)0x0000000E),
  COMP1_CTRL_INMSEL_NC          = ((uint32_t)0x00000000),
  //comp2 inm sel
  COMP2_CTRL_INMSEL_PA2         = ((uint32_t)0x00000002),
  COMP2_CTRL_INMSEL_PA5         = ((uint32_t)0x00000004),
  COMP2_CTRL_INMSEL_PA6         = ((uint32_t)0x00000006),
  COMP2_CTRL_INMSEL_PB3         = ((uint32_t)0x00000008),
  COMP2_CTRL_INMSEL_PD6         = ((uint32_t)0x0000000A),
  COMP2_CTRL_INMSEL_DAC1_PA4    = ((uint32_t)0x0000000C),
  COMP2_CTRL_INMSEL_VREF_VC2    = ((uint32_t)0x0000000E),
  COMP2_CTRL_INMSEL_NC          = ((uint32_t)0x00000000),
}COMP_CTRL_INMSEL;

#define COMP_CTRL_EN_MASK (0x01L << 0)

//COMPx_FILC
#define COMP_FILC_SAMPW_MASK                        (0x1FL<<6)//Low filter sample window size. Number of samples to monitor is SAMPWIN+1.
#define COMP_FILC_THRESH_MASK                       (0x1FL<<1)//For proper operation, the value of THRESH must be greater than SAMPWIN / 2.
#define COMP_FILC_FILEN_MASK                        (0x01L<<0)//Filter enable.

//COMPx_FILP
#define COMP_FILP_CLKPSC_MASK                        (0xFFFFL)//Prescale number .

//COMP_WINMODE @addtogroup COMP_WINMODE_CMPMD
#define COMP_WINMODE_CMP12MD                        (0x01L <<0)//1: Comparators 1 and 2 can be used in window mode.

//COMP_INTEN @addtogroup COMP_INTEN_CMPIEN
#define COMP_INTEN_CMPIEN_MSK   (0x3L << 0) // This bit control Interrput enable of COMP.
#define COMP_INTEN_CMP2IEN      (0x01L << 1)
#define COMP_INTEN_CMP1IEN      (0x01L << 0)

//COMP_INTSTS @addtogroup COMP_INTSTS_CMPIS
#define COMP_INTSTS_INTSTS_MSK  (0x3L << 0) // This bit control Interrput enable of COMP.
#define COMP_INTSTS_CMP2IS      (0x01L << 1)
#define COMP_INTSTS_CMP1IS      (0x01L << 0)

//COMP_VREFSCL @addtogroup COMP_VREFSCL
#define COMP_VREFSCL_VV2TRM_MSK (0x3FL << 8) // Vref2 Voltage scaler triming value.
#define COMP_VREFSCL_VV2EN_MSK  (0x01L << 7)
#define COMP_VREFSCL_VV1TRM_MSK (0x3FL << 1) // Vref1 Voltage scaler triming value.
#define COMP_VREFSCL_VV1EN_MSK  (0x01L << 0)

//COMP_LOCK @addtogroup COMP_LOCK
#define COMP_LOCK_CMP2LK        (0x1L << 1) // Vref1 Voltage scaler triming value.
#define COMP_LOCK_CMP1LK        (0x1L << 0)

//COMP_LPCKSEL @addtogroup COMP_LPCKSEL
#define COMP_LKCKSEL_LPCLKSEL    (0x1L << 0)

//COMP_OSEL @addtogroup COMP_OSEL
#define COMP_OSEL_CMP2XO         (0x1L << 0)

/**
 * @}
 */

/**
 * @brief  COMP Init structure definition
 */

typedef struct
{
    // ctrl
    bool LowPoweMode; // only COMP1 have this bit
    bool InpDacConnect; // only COMP1 have this bit

    COMP_CTRL_BLKING Blking; /*see @ref COMP_CTRL_BLKING */

    COMP_CTRL_HYST Hyst;

    bool PolRev; // out polarity reverse

    COMP_CTRL_OUTTRIG OutTrig;
    COMP_CTRL_INPSEL InpSel;
    COMP_CTRL_INMSEL InmSel;

    bool En;

    // filter
    uint8_t SampWindow; // 5bit
    uint8_t Thresh;     // 5bit ,need > SampWindow/2
    bool FilterEn;

    // filter psc
    uint16_t ClkPsc;
} COMP_InitType;

/** @addtogroup COMP_Exported_Functions
 * @{
 */

void COMP_DeInit(void);
void COMP_StructInit(COMP_InitType* COMP_InitStruct);
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct);
void COMP_Enable(COMPX COMPx, FunctionalState en);
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel);
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel);
void COMP_SetOutTrig(COMPX COMPx, COMP_CTRL_OUTTRIG OutTrig);
uint32_t COMP_GetIntSts(void);                                                 // return see @COMP_INTSTS_CMPIS
void COMP_SetRefScl(uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En); // parma range see @COMP_VREFSCL
FlagStatus COMP_GetOutStatus(COMPX COMPx);
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx);
void COMP_SetLock(uint32_t Lock);                                              // see @COMP_LOCK_CMPLK
void COMP_SetIntEn(uint32_t IntEn);                                            // see @COMP_INTEN_CMPIEN
void COMP_CMP2XorOut(bool En);
void COMP_StopOrLowpower32KClkSel(bool En);
void COMP_WindowModeEn(bool En);
void COMP_SetFilterPrescaler(COMPX COMPx , uint16_t FilPreVal);
void COMP_SetFilterControl(COMPX COMPx , uint8_t FilEn, uint8_t TheresNum , uint8_t SampPW);
void COMP_SetHyst(COMPX COMPx , COMP_CTRL_HYST HYST);
void COMP_SetBlanking(COMPX COMPx , COMP_CTRL_BLKING BLK);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__N32L40X_ADC_H */
/**
 * @}
 */
/**
 * @}
 */
