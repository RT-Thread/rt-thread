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
 * @file n32h76x_78x_shrtim.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef N32H76X_78X_SHRTIM_H
#define N32H76X_78X_SHRTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "n32h76x_78x.h"

/*** SHRTIM structure definition start ***/
static const uint16_t REG_OFFSET_TAB_TIMER[] =
{
  0x00U,   /* 0: MASTER  */
  0x80U,   /* 1: TIMER A */
  0x100U,  /* 2: TIMER B */
  0x180U,  /* 3: TIMER C */
  0x200U,  /* 4: TIMER D */
  0x280U,  /* 5: TIMER E */
  0x300U,  /* 6: TIMER F */
};

static const uint8_t REG_OFFSET_TAB_ADTGSRC[] =
{
  0x00U,    /* SHRTIM_ADCTRIG_1_GROUP1:  SHRTIM_ADTG1SRC1 */
  0x04U,    /* SHRTIM_ADCTRIG_1_GROUP2:  SHRTIM_ADTG1SRC2 */
  0x08U,    /* SHRTIM_ADCTRIG_2_GROUP1:  SHRTIM_ADTG2SRC1 */
  0x0CU,    /* SHRTIM_ADCTRIG_2_GROUP2:  SHRTIM_ADTG2SRC2 */
  0x10U,    /* SHRTIM_ADCTRIG_3_GROUP1:  SHRTIM_ADTG3SRC1 */
  0x14U,    /* SHRTIM_ADCTRIG_3_GROUP2:  SHRTIM_ADTG3SRC2 */
  0x18U,    /* SHRTIM_ADCTRIG_4_GROUP1:  SHRTIM_ADTG4SRC1 */
  0x1CU,    /* SHRTIM_ADCTRIG_4_GROUP2:  SHRTIM_ADTG4SRC2 */
  0x50U,    /* SHRTIM_ADCTRIG_5:         SHRTIM_ADTGEX1 */
  0x50U,    /* SHRTIM_ADCTRIG_7:         SHRTIM_ADTGEX1 */
  0x50U,    /* SHRTIM_ADCTRIG_9:         SHRTIM_ADTGEX1 */
  0x54U,    /* SHRTIM_ADCTRIG_6:         SHRTIM_ADTGEX2 */
  0x54U,    /* SHRTIM_ADCTRIG_8:         SHRTIM_ADTGEX2 */
  0x54U,    /* SHRTIM_ADCTRIG_10:        SHRTIM_ADTGEX2 */
};

static const uint8_t REG_OFFSET_TAB_ADTGUPD[] =
{
  0x00U,    /* SHRTIM_ADCTRIG_1:  SHRTIM_CTRL1 */
  0x00U,    /* SHRTIM_ADCTRIG_2:  SHRTIM_CTRL1 */
  0x00U,    /* SHRTIM_ADCTRIG_3:  SHRTIM_CTRL1 */
  0x00U,    /* SHRTIM_ADCTRIG_4:  SHRTIM_CTRL1 */
  0x98U,    /* SHRTIM_ADCTRIG_5:  SHRTIM_ADTGUPD */
  0x98U,    /* SHRTIM_ADCTRIG_6:  SHRTIM_ADTGUPD */
  0x98U,    /* SHRTIM_ADCTRIG_7:  SHRTIM_ADTGUPD */
  0x98U,    /* SHRTIM_ADCTRIG_8:  SHRTIM_ADTGUPD */
  0x98U,    /* SHRTIM_ADCTRIG_9:  SHRTIM_ADTGUPD */
  0x98U,    /* SHRTIM_ADCTRIG_10: SHRTIM_ADTGUPD */
};

static const uint8_t REG_SHIFT_TAB_ADTGSRC[] =
{
  0,    /* SHRTIM_ADCTRIG1_SOURCE_GROUP1 */
  0,    /* SHRTIM_ADCTRIG1_SOURCE_GROUP2 */
  0,    /* SHRTIM_ADCTRIG2_SOURCE_GROUP1 */
  0,    /* SHRTIM_ADCTRIG2_SOURCE_GROUP2 */
  0,    /* SHRTIM_ADCTRIG3_SOURCE_GROUP1 */
  0,    /* SHRTIM_ADCTRIG3_SOURCE_GROUP2 */
  0,    /* SHRTIM_ADCTRIG4_SOURCE_GROUP1 */
  0,    /* SHRTIM_ADCTRIG4_SOURCE_GROUP2 */
  0,    /* SHRTIM_ADCTRIG_5 */
  0,    /* SHRTIM_ADCTRIG_6 */
  8,    /* SHRTIM_ADCTRIG_7 */
  8,    /* SHRTIM_ADCTRIG_8 */
  16,    /* SHRTIM_ADCTRIG_9 */
  16,    /* SHRTIM_ADCTRIG_10 */
};

static const uint8_t REG_SHIFT_TAB_ADTGUPD[] =
{
  16,   /* SHRTIM_ADCTRIG_1  */
  19,   /* SHRTIM_ADCTRIG_2  */
  22,   /* SHRTIM_ADCTRIG_3  */
  25,   /* SHRTIM_ADCTRIG_4  */
  0,    /* SHRTIM_ADCTRIG_5  */
  4,    /* SHRTIM_ADCTRIG_6  */
  8,    /* SHRTIM_ADCTRIG_7  */
  12,   /* SHRTIM_ADCTRIG_8  */
  16,   /* SHRTIM_ADCTRIG_9  */
  20    /* SHRTIM_ADCTRIG_10 */
};

static const uint32_t REG_MASK_TAB_ADTGSRC[] =
{
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG1_SOURCE_GROUP1 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG1_SOURCE_GROUP2 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG2_SOURCE_GROUP1 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG2_SOURCE_GROUP2 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG3_SOURCE_GROUP1 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG3_SOURCE_GROUP2 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG4_SOURCE_GROUP1 */
    0xFFFFFFFFU,    /* SHRTIM_ADCTRIG4_SOURCE_GROUP2 */
    0x0000003FU,    /* SHRTIM_ADCTRIG_5 */
    0x0000003FU,    /* SHRTIM_ADCTRIG_6 */
    0x00003F00U,    /* SHRTIM_ADCTRIG_7 */
    0x00003F00U,    /* SHRTIM_ADCTRIG_8 */
    0x003F0000U,    /* SHRTIM_ADCTRIG_9 */
    0x003F0000U,    /* SHRTIM_ADCTRIG_10 */
};

static const uint32_t REG_MASK_TAB_ADTGUPD[] =
{
  0x00070000U,   /* SHRTIM_ADCTRIG_1  */
  0x00380000U,   /* SHRTIM_ADCTRIG_2  */
  0x01C00000U,   /* SHRTIM_ADCTRIG_3  */
  0x0E000000U,   /* SHRTIM_ADCTRIG_4  */
  0x00000007U,   /* SHRTIM_ADCTRIG_5  */
  0x00000070U,   /* SHRTIM_ADCTRIG_6  */
  0x00000700U,   /* SHRTIM_ADCTRIG_7  */
  0x00007000U,   /* SHRTIM_ADCTRIG_8  */
  0x00070000U,   /* SHRTIM_ADCTRIG_9  */
  0x00700000U    /* SHRTIM_ADCTRIG_10 */
};

static const uint8_t REG_OFFSET_TAB_ADCPSx[] =
{
  0U,    /* 0: SHRTIM_ADC1R  */
  6U,    /* 1: SHRTIM_ADC2R  */
  12U,   /* 2: SHRTIM_ADC3R  */
  18U,   /* 3: SHRTIM_ADC4R  */
  24U,   /* 4: SHRTIM_ADC5R  */
  32U,   /* 5: SHRTIM_ADC6R  */
  38U,   /* 6: SHRTIM_ADC7R  */
  44U,   /* 7: SHRTIM_ADC8R  */
  50U,   /* 8: SHRTIM_ADC9R  */
  56U    /* 9: SHRTIM_ADC10R */
};

static const uint16_t REG_OFFSET_TAB_TxSET[] =
{
  0x00U,   /* 0: TA1 */
  0x08U,   /* 1: TA2 */
  0x80U,   /* 2: TB1 */
  0x88U,   /* 3: TB2 */
  0x100U,  /* 4: TC1 */
  0x108U,  /* 5: TC2 */
  0x180U,  /* 6: TD1 */
  0x188U,  /* 7: TD2 */
  0x200U,  /* 8: TE1 */
  0x208U,  /* 9: TE2 */
  0x280U,  /* 10: TF1 */
  0x288U   /* 11: TF2 */
};

static const uint16_t REG_OFFSET_TAB_TxOUT[] =
{
  0x00U,   /*  0: TA1 */
  0x00U,   /*  1: TA2 */
  0x80U,   /*  2: TB1 */
  0x80U,   /*  3: TB2 */
  0x100U,  /*  4: TC1 */
  0x100U,  /*  5: TC2 */
  0x180U,  /*  6: TD1 */
  0x180U,  /*  7: TD2 */
  0x200U,  /*  8: TE1 */
  0x200U,  /*  9: TE2 */
  0x280U,  /* 10: TF1 */
  0x280U   /* 11: TF2 */
};

static const uint8_t REG_OFFSET_TAB_EXEVCTRL[] =
{
  0x00U, /* SHRTIM_EVENT_1 */
  0x00U, /* SHRTIM_EVENT_2 */
  0x00U, /* SHRTIM_EVENT_3 */
  0x00U, /* SHRTIM_EVENT_4 */
  0x00U, /* SHRTIM_EVENT_5 */
  0x04U, /* SHRTIM_EVENT_6 */
  0x04U, /* SHRTIM_EVENT_7 */
  0x04U, /* SHRTIM_EVENT_8 */
  0x04U, /* SHRTIM_EVENT_9 */
  0x04U  /* SHRTIM_EVENT_10 */
};

static const uint8_t REG_OFFSET_TAB_FALTIN[] =
{
  0x00U, /* SHRTIM_FAULT_1 */
  0x00U, /* SHRTIM_FAULT_2 */
  0x00U, /* SHRTIM_FAULT_3 */
  0x00U, /* SHRTIM_FAULT_4 */
  0x04U, /* SHRTIM_FAULT_5 */
  0x04U  /* SHRTIM_FAULT_6 */
};

static const uint32_t REG_MASK_TAB_UPDATETRIG[] =
{
  0x20000000U,  /* 0: MASTER  */
  0x01FF0000U,  /* 1: TIMER A */
  0x01FF0000U,  /* 2: TIMER B */
  0x01FF0000U,  /* 3: TIMER C */
  0x01FF0000U,  /* 4: TIMER D */
  0x01FF0000U,  /* 5: TIMER E */
  0x01FF0000U,  /* 5: TIMER E */
  0x01FF0000U   /* 6: TIMER F */
};

static const uint8_t REG_SHIFT_TAB_UPDATETRIG[] =
{
  12U, /* 0: MASTER  */
  0U,  /* 1: TIMER A */
  0U,  /* 2: TIMER B  */
  0U,  /* 3: TIMER C */
  0U,  /* 4: TIMER D  */
  0U,  /* 5: TIMER E */
  0U   /* 6: TIMER F */
};

static const uint8_t REG_SHIFT_TAB_EXEVx[] =
{
  0U,  /* SHRTIM_EVENT_1  */
  6U,  /* SHRTIM_EVENT_2  */
  12U, /* SHRTIM_EVENT_3  */
  18U, /* SHRTIM_EVENT_4  */
  24U, /* SHRTIM_EVENT_5  */
  0U,  /* SHRTIM_EVENT_6  */
  6U,  /* SHRTIM_EVENT_7  */
  12U, /* SHRTIM_EVENT_8  */
  18U, /* SHRTIM_EVENT_9  */
  24U  /* SHRTIM_EVENT_10 */
};

static const uint8_t REG_SHIFT_TAB_EXEVxCSEL[] =
{
  0U,  /* SHRTIM_EVENT_1  */
  3U,  /* SHRTIM_EVENT_2  */
  6U,  /* SHRTIM_EVENT_3  */
  9U,  /* SHRTIM_EVENT_4  */
  12U, /* SHRTIM_EVENT_5  */
  15U, /* SHRTIM_EVENT_6  */
  18U, /* SHRTIM_EVENT_7  */
  21U, /* SHRTIM_EVENT_8  */
  24U, /* SHRTIM_EVENT_9  */
  27U  /* SHRTIM_EVENT_10 */
};

static const uint8_t REG_SHIFT_TAB_FALTxCSEL[] =
{
  0U,  /* SHRTIM_FAULT_1  */
  4U,  /* SHRTIM_FAULT_2  */
  8U,  /* SHRTIM_FAULT_3  */
  12U,  /* SHRTIM_FAULT_4  */
  16U, /* SHRTIM_FAULT_5  */
  20U, /* SHRTIM_FAULT_6  */
};

static const uint32_t REG_MASK_TAB_UPDATEGATING[] =
{
  SHRTIM_MCTRL_BRSTDMA,   /* 0: MASTER  */
  SHRTIM_TXCTRL_UPDGAT,  /* 1: TIMER A */
  SHRTIM_TXCTRL_UPDGAT,  /* 2: TIMER B  */
  SHRTIM_TXCTRL_UPDGAT,  /* 3: TIMER C */
  SHRTIM_TXCTRL_UPDGAT,  /* 4: TIMER D  */
  SHRTIM_TXCTRL_UPDGAT,  /* 5: TIMER E */
  SHRTIM_TXCTRL_UPDGAT   /* 6: TIMER F */
};

static const uint8_t REG_SHIFT_TAB_UPDATEGATING[] =
{
  2U, /* 0: MASTER  */
  0U, /* 1: TIMER A */
  0U, /* 2: TIMER B  */
  0U, /* 3: TIMER C */
  0U, /* 4: TIMER D  */
  0U, /* 5: TIMER E */
  0U  /* 6: TIMER F */
};

static const uint8_t REG_SHIFT_TAB_TxOUT[] =
{
  0U,  /* 0: TA1  */
  16U, /* 1: TA2 */
  0U,  /* 2: TB1  */
  16U, /* 3: TB2 */
  0U,  /* 4: TC1  */
  16U, /* 5: TC2 */
  0U,  /* 6: TD1  */
  16U, /* 7: TD2 */
  0U,  /* 8: TE1  */
  16U, /* 9: TE2 */
  0U,  /* 10: TF1  */
  16U  /* 11: TF2 */
};

static const uint8_t REG_SHIFT_TAB_OxSTS[] =
{
  0U,  /* 0: TA1  */
  1U,  /* 1: TA2 */
  0U,  /* 2: TB1  */
  1U,  /* 3: TB2 */
  0U,  /* 4: TC1  */
  1U,  /* 5: TC2 */
  0U,  /* 6: TD1  */
  1U,  /* 7: TD2 */
  0U,  /* 8: TE1  */
  1U,  /* 9: TE2 */
  0U,  /* 10: TF1  */
  1U   /* 11: TF2 */
};

static const uint8_t REG_SHIFT_TAB_FALTxE[] =
{
  0U,   /* SHRTIM_FAULT_1 */
  8U,   /* SHRTIM_FAULT_2 */
  16U,  /* SHRTIM_FAULT_3 */
  24U,  /* SHRTIM_FAULT_4 */
  0U,   /* SHRTIM_FAULT_5 */
  8U    /* SHRTIM_FAULT_6 */
};

static const uint8_t REG_SHIFT_TAB_FALTxF[] =
{
  0U,   /* SHRTIM_FAULT_1 */
  8U,   /* SHRTIM_FAULT_2 */
  16U,  /* SHRTIM_FAULT_3 */
  24U,  /* SHRTIM_FAULT_4 */
  32U,  /* SHRTIM_FAULT_5 */
  40U   /* SHRTIM_FAULT_6 */
};

static const uint8_t REG_SHIFT_TAB_FALTx[] =
{
  0,  /* SHRTIM_FAULT_1 */
  1,  /* SHRTIM_FAULT_2 */
  2,  /* SHRTIM_FAULT_3 */
  3,  /* SHRTIM_FAULT_4 */
  4,  /* SHRTIM_FAULT_5 */
  5   /* SHRTIM_FAULT_6 */
};

static const uint8_t REG_SHIFT_TAB_ILV[] =
{
  0U,  /* 0: MASTER  */
  1U,  /* 1: TIMER A */
  1U,  /* 2: TIMER B */
  1U,  /* 3: TIMER C */
  1U,  /* 4: TIMER D */
  1U,  /* 5: TIMER E */
  1U,  /* 6: TIMER F */
};

static const uint32_t REG_MASK_TAB_ILV[] =
{
  0x000000E0U,  /* 0: MASTER  */
  0x000001A0U,  /* 1: TIMER A */
  0x000001A0U,  /* 2: TIMER B */
  0x000001A0U,  /* 3: TIMER C */
  0x000001A0U,  /* 4: TIMER D */
  0x000001A0U,  /* 5: TIMER E */
  0x000001A0U,  /* 6: TIMER F */
};

static const uint8_t REG_SHIFT_TAB_CPT[] =
{
  12U,  /* 1: TIMER A */
  16U,  /* 2: TIMER B */
  20U,  /* 3: TIMER C */
  24U,  /* 4: TIMER D */
  28U,  /* 5: TIMER E */
  32U,  /* 6: TIMER F */
};

static const uint32_t REG_MASK_TAB_CPT[] =
{
  0xFFFF0000U,  /* 1: TIMER A */
  0xFFF0F000U,  /* 2: TIMER B */
  0xFF0FF000U,  /* 3: TIMER C */
  0xF0FFF000U,  /* 4: TIMER D */
  0x0FFFF000U,  /* 5: TIMER E */
  0xFFFFF000U,  /* 6: TIMER F */
};
/*** SHRTIM structure definition end ***/



/*** SHRTIM macro definitions start ***/
#define SHRTIM_CTRL1_UDIS_MASK   ((uint32_t)(SHRTIM_CTRL1_MUPDDIS  |\
                                          SHRTIM_CTRL1_TAUPDDIS |\
                                          SHRTIM_CTRL1_TBUPDDIS |\
                                          SHRTIM_CTRL1_TCUPDDIS |\
                                          SHRTIM_CTRL1_TDUPDDIS |\
                                          SHRTIM_CTRL1_TEUPDDIS |\
                                          SHRTIM_CTRL1_TFUPDDIS))

#define SHRTIM_CTRL2_SWUPD_MASK   ((uint32_t)(SHRTIM_CTRL2_MSWUPD |\
                                           SHRTIM_CTRL2_TASWUPD |\
                                           SHRTIM_CTRL2_TBSWUPD |\
                                           SHRTIM_CTRL2_TCSWUPD |\
                                           SHRTIM_CTRL2_TDSWUPD |\
                                           SHRTIM_CTRL2_TESWUPD |\
                                           SHRTIM_CTRL2_TFSWUPD))

#define SHRTIM_CTRL2_SWAP_MASK   ((uint32_t)(SHRTIM_CTRL2_SWAPA |\
                                          SHRTIM_CTRL2_SWAPB |\
                                          SHRTIM_CTRL2_SWAPC |\
                                          SHRTIM_CTRL2_SWAPD |\
                                          SHRTIM_CTRL2_SWAPE |\
                                          SHRTIM_CTRL2_SWAPF))

#define SHRTIM_CTRL2_SWRST_MASK   ((uint32_t)(SHRTIM_CTRL2_MSWCNTRST |\
                                           SHRTIM_CTRL2_TASWCNTRST |\
                                           SHRTIM_CTRL2_TBSWCNTRST |\
                                           SHRTIM_CTRL2_TCSWCNTRST |\
                                           SHRTIM_CTRL2_TDSWCNTRST |\
                                           SHRTIM_CTRL2_TESWCNTRST |\
                                           SHRTIM_CTRL2_TFSWCNTRST))

#define SHRTIM_OEN_OEN_MASK   ((uint32_t)(SHRTIM_OEN_TA1OEN |\
                                          SHRTIM_OEN_TA2OEN |\
                                          SHRTIM_OEN_TB1OEN |\
                                          SHRTIM_OEN_TB2OEN |\
                                          SHRTIM_OEN_TC1OEN |\
                                          SHRTIM_OEN_TC2OEN |\
                                          SHRTIM_OEN_TD1OEN |\
                                          SHRTIM_OEN_TD2OEN |\
                                          SHRTIM_OEN_TE1OEN |\
                                          SHRTIM_OEN_TE2OEN |\
                                          SHRTIM_OEN_TF1OEN |\
                                          SHRTIM_OEN_TF2OEN))

#define SHRTIM_ODIS_ODIS_MASK  ((uint32_t)(SHRTIM_ODIS_TA1ODIS  |\
                                          SHRTIM_ODIS_TA2ODIS  |\
                                          SHRTIM_ODIS_TB1ODIS  |\
                                          SHRTIM_ODIS_TB2ODIS  |\
                                          SHRTIM_ODIS_TC1ODIS  |\
                                          SHRTIM_ODIS_TC2ODIS  |\
                                          SHRTIM_ODIS_TD1ODIS  |\
                                          SHRTIM_ODIS_TD2ODIS  |\
                                          SHRTIM_ODIS_TE1ODIS  |\
                                          SHRTIM_ODIS_TE2ODIS  |\
                                          SHRTIM_ODIS_TF1ODIS  |\
                                          SHRTIM_ODIS_TF2ODIS))

#define SHRTIM_OUT_CONFIG_MASK  ((uint32_t)(SHRTIM_TXOUT_POL1   |\
                                           SHRTIM_TXOUT_IDLES1 |\
                                           SHRTIM_TXOUT_FALT1 |\
                                           SHRTIM_TXOUT_CHP1   |\
                                           SHRTIM_TXOUT_DIDL1))
                                           
#define SHRTIM_FALT_CONFIG_MASK   ((uint32_t)(SHRTIM_FALTIN1_FALT1POL |\
                                            SHRTIM_FALTIN1_FALT1SRC0 ))

#define SHRTIM_FALT_SRC_1_MASK   ((uint32_t)(SHRTIM_FALTIN2_FALT6SRC1 |\
                                           SHRTIM_FALTIN2_FALT5SRC1 |\
                                           SHRTIM_FALTIN2_FALT4SRC1 |\
                                           SHRTIM_FALTIN2_FALT3SRC1 |\
                                           SHRTIM_FALTIN2_FALT2SRC1 |\
                                           SHRTIM_FALTIN2_FALT1SRC1))

#define SHRTIM_BM_CONFIG_MASK   ((uint32_t)( SHRTIM_BMCTRL_BMPSC |\
                                            SHRTIM_BMCTRL_BMCK  |\
                                            SHRTIM_BMCTRL_BMOM))
                                            
#define SHRTIM_FRZDIS_CONFIG_MASK   ((uint32_t)(SHRTIM_FRZDIS_TFDBGEN |\
                                                 SHRTIM_FRZDIS_TEDBGEN |\
                                                 SHRTIM_FRZDIS_TDDBGEN |\
                                                 SHRTIM_FRZDIS_TCDBGEN |\
                                                 SHRTIM_FRZDIS_TBDBGEN |\
                                                 SHRTIM_FRZDIS_TADBGEN |\
                                                 SHRTIM_FRZDIS_MDBGEN))

#define SHRTIM_SFTDP_CONFIG_MASK   ((uint32_t)(SHRTIM_SFTDP_SFTDPA1 |\
                                               SHRTIM_SFTDP_SFTDPA2 |\
                                               SHRTIM_SFTDP_SFTDPB1 |\
                                               SHRTIM_SFTDP_SFTDPB2 |\
                                               SHRTIM_SFTDP_SFTDPC1 |\
                                               SHRTIM_SFTDP_SFTDPC2 |\
                                               SHRTIM_SFTDP_SFTDPD1 |\
                                               SHRTIM_SFTDP_SFTDPD2 |\
                                               SHRTIM_SFTDP_SFTDPE1 |\
                                               SHRTIM_SFTDP_SFTDPE2 |\
                                               SHRTIM_SFTDP_SFTDPF1 |\
                                               SHRTIM_SFTDP_SFTDPF2))
     

/** Flags defines which can be used with SHRTIM_ReadReg function **/
#define SHRTIM_INTERRUPT_STATUS_FALT1ITF                  SHRTIM_INTSTS_FALT1ITF
#define SHRTIM_INTERRUPT_STATUS_FALT2ITF                  SHRTIM_INTSTS_FALT2ITF
#define SHRTIM_INTERRUPT_STATUS_FALT3ITF                  SHRTIM_INTSTS_FALT3ITF
#define SHRTIM_INTERRUPT_STATUS_FALT4ITF                  SHRTIM_INTSTS_FALT4ITF
#define SHRTIM_INTERRUPT_STATUS_FALT5ITF                  SHRTIM_INTSTS_FALT5ITF
#define SHRTIM_INTERRUPT_STATUS_FALT6ITF                  SHRTIM_INTSTS_FALT6ITF
#define SHRTIM_INTERRUPT_STATUS_SYSFALTITF                SHRTIM_INTSTS_SYSFALTITF
#define SHRTIM_INTERRUPT_STATUS_BMPRDITF                  SHRTIM_INTSTS_BMPRDITF

#define SHRTIM_MASTER_INTERRUPT_STATUS_MCMP1ITF                SHRTIM_MINTSTS_MCMP1ITF
#define SHRTIM_MASTER_INTERRUPT_STATUS_MCMP2ITF                SHRTIM_MINTSTS_MCMP2ITF
#define SHRTIM_MASTER_INTERRUPT_STATUS_MCMP3ITF                SHRTIM_MINTSTS_MCMP3ITF
#define SHRTIM_MASTER_INTERRUPT_STATUS_MCMP4ITF                SHRTIM_MINTSTS_MCMP4ITF
#define SHRTIM_MASTER_INTERRUPT_STATUS_MREPTITF                SHRTIM_MINTSTS_MREPTITF
#define SHRTIM_MASTER_INTERRUPT_STATUS_SYNCINITF               SHRTIM_MINTSTS_SYNCINITF
#define SHRTIM_MASTER_INTERRUPT_STATUS_MUPDITF                 SHRTIM_MINTSTS_MUPDITF

#define SHRTIM_TX_INTERRUPT_STATUS_CMP1ITF               SHRTIM_TXINTSTS_CMP1ITF
#define SHRTIM_TX_INTERRUPT_STATUS_CMP2ITF               SHRTIM_TXINTSTS_CMP2ITF
#define SHRTIM_TX_INTERRUPT_STATUS_CMP3ITF               SHRTIM_TXINTSTS_CMP3ITF
#define SHRTIM_TX_INTERRUPT_STATUS_CMP4ITF               SHRTIM_TXINTSTS_CMP4ITF
#define SHRTIM_TX_INTERRUPT_STATUS_REPTITF               SHRTIM_TXINTSTS_REPTITF
#define SHRTIM_TX_INTERRUPT_STATUS_UPDITF                SHRTIM_TXINTSTS_UPDITF
#define SHRTIM_TX_INTERRUPT_STATUS_CPT1ITF               SHRTIM_TXINTSTS_CPT1ITF
#define SHRTIM_TX_INTERRUPT_STATUS_CPT2ITF               SHRTIM_TXINTSTS_CPT2ITF
#define SHRTIM_TX_INTERRUPT_STATUS_SET1ITF               SHRTIM_TXINTSTS_SET1ITF
#define SHRTIM_TX_INTERRUPT_STATUS_RST1ITF               SHRTIM_TXINTSTS_RST1ITF
#define SHRTIM_TX_INTERRUPT_STATUS_SET2ITF               SHRTIM_TXINTSTS_SET2ITF
#define SHRTIM_TX_INTERRUPT_STATUS_RST2ITF               SHRTIM_TXINTSTS_RST2ITF
#define SHRTIM_TX_INTERRUPT_STATUS_RSTROITF              SHRTIM_TXINTSTS_RSTROITF
#define SHRTIM_TX_INTERRUPT_STATUS_DPITF                 SHRTIM_TXINTSTS_DPITF

/** Defines which can be used with SHRTIM_ReadReg and SHRTIM_WriteReg functions **/
#define SHRTIM_INTERRUPT_ENABLE_FALT1IEN                SHRTIM_INTEN_FALT1IEN
#define SHRTIM_INTERRUPT_ENABLE_FALT2IEN                SHRTIM_INTEN_FALT2IEN
#define SHRTIM_INTERRUPT_ENABLE_FALT3IEN                SHRTIM_INTEN_FALT3IEN
#define SHRTIM_INTERRUPT_ENABLE_FALT4IEN                SHRTIM_INTEN_FALT4IEN
#define SHRTIM_INTERRUPT_ENABLE_FALT5IEN                SHRTIM_INTEN_FALT5IEN
#define SHRTIM_INTERRUPT_ENABLE_FALT6IEN                SHRTIM_INTEN_FALT6IEN
#define SHRTIM_INTERRUPT_ENABLE_SYSFALTIEN              SHRTIM_INTEN_SYSFALTIEN
#define SHRTIM_INTERRUPT_ENABLE_BMPRDIEN                SHRTIM_INTEN_BMPRDIEN

#define SHRTIM_MASTER_INTERRUPT_ENABLE_MCMP1IEN             SHRTIM_MIDEN_MCMP1IEN
#define SHRTIM_MASTER_INTERRUPT_ENABLE_MCMP2IEN             SHRTIM_MIDEN_MCMP2IEN
#define SHRTIM_MASTER_INTERRUPT_ENABLE_MCMP3IEN             SHRTIM_MIDEN_MCMP3IEN
#define SHRTIM_MASTER_INTERRUPT_ENABLE_MCMP4IEN             SHRTIM_MIDEN_MCMP4IEN
#define SHRTIM_MASTER_INTERRUPT_ENABLE_MREPTIEN             SHRTIM_MIDEN_MREPTIEN
#define SHRTIM_MASTER_INTERRUPT_ENABLE_SYNCINIEN            SHRTIM_MIDEN_SYNCINIEN
#define SHRTIM_MASTER_INTERRUPT_ENABLE_MUPDIEN              SHRTIM_MIDEN_MUPDIEN

#define SHRTIM_TX_INTERRUPT_ENABLE_CMP1IEN            SHRTIM_TXIDEN_CMP1IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_CMP2IEN            SHRTIM_TXIDEN_CMP2IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_CMP3IEN            SHRTIM_TXIDEN_CMP3IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_CMP4IEN            SHRTIM_TXIDEN_CMP4IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_REPTIEN            SHRTIM_TXIDEN_REPTIEN
#define SHRTIM_TX_INTERRUPT_ENABLE_UPDIEN             SHRTIM_TXIDEN_UPDIEN
#define SHRTIM_TX_INTERRUPT_ENABLE_CPT1IEN            SHRTIM_TXIDEN_CPT1IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_CPT2IEN            SHRTIM_TXIDEN_CPT2IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_SET1IEN            SHRTIM_TXIDEN_SET1IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_RST1IEN            SHRTIM_TXIDEN_RST1IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_SET2IEN            SHRTIM_TXIDEN_SET2IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_RST2IEN            SHRTIM_TXIDEN_RST2IEN
#define SHRTIM_TX_INTERRUPT_ENABLE_RSTRODEN           SHRTIM_TXIDEN_RSTRODEN
#define SHRTIM_TX_INTERRUPT_ENABLE_DPIEN              SHRTIM_TXIDEN_DPIEN


/** Defining the synchronization input source. **/
#define SHRTIM_SYNCIN_SRC_NONE                0x00000000U                        /* SHRTIM is not synchronized and runs in standalone mode */
#define SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_0    (SHRTIM_MCTRL_SYNCIN_0)            /* The SHRTIM is synchronized with the on-chip timer, from ATIM1 trgo */
#define SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_1    (SHRTIM_MCTRL_SYNCIN_1)            /* The SHRTIM is synchronized with the on-chip timer from ATIM2 trgo */
#define SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_2    (SHRTIM_MCTRL_SYNCIN_1 | SHRTIM_MCTRL_SYNCIN_0)            /* The SHRTIM is synchronized with the on-chip timer, from ATIM3 trgo */
#define SHRTIM_SYNCIN_SRC_EXTERNAL_EVENT_3    (SHRTIM_MCTRL_SYNCIN_2)                                    /* A positive pulse on SYNCIN input triggers the SHRTIM */
#define SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_4    (SHRTIM_MCTRL_SYNCIN_2 | SHRTIM_MCTRL_SYNCIN_0)            /* The SHRTIM is synchronized with the on-chip timer, from shrtim_out_sync2 of another SHRTIM */


/** Defining the source and event to be sent on the synchronization output. */
#define SHRTIM_SYNCOUT_SRC_MASTER_START  0x00000000U                                    /* A pulse is sent on SHRTIM_SCOUT output and shrtim_out_sync2 upon master timer start event      */
#define SHRTIM_SYNCOUT_SRC_MASTER_CMP1   (SHRTIM_MCTRL_SYNCOSRC_0)                         /* A pulse is sent on SHRTIM_SCOUT output and shrtim_out_sync2 upon master timer compare 1 event  */
#define SHRTIM_SYNCOUT_SRC_TIMA_START    (SHRTIM_MCTRL_SYNCOSRC_1)                         /* A pulse is sent on SHRTIM_SCOUT output and shrtim_out_sync2 upon timer A start or reset events */
#define SHRTIM_SYNCOUT_SRC_TIMA_CMP1     (SHRTIM_MCTRL_SYNCOSRC_1 | SHRTIM_MCTRL_SYNCOSRC_0)  /* A pulse is sent on SHRTIM_SCOUT output and shrtim_out_sync2 upon timer A compare 1 event       */


/** Defining the routing and conditioning of the synchronization output event. */
#define SHRTIM_SYNCOUT_DISABLED       0x00000000U                                                   /* Synchronization output event is disabled */
#define SHRTIM_SYNCOUT_POSITIVE_PULSE (SHRTIM_SYNCOUT_SYNCOUTPUS_1)                                 /* Synchronization output has a low idle level and issues a positive pulse of 16 fSHRTIM clock cycles length for the synchronization */
#define SHRTIM_SYNCOUT_NEGATIVE_PULSE (SHRTIM_SYNCOUT_SYNCOUTPUS_1 | SHRTIM_SYNCOUT_SYNCOUTPUS_0)   /* Synchronization output has a high idle level and issues a negative pulse of 16 fSHRTIM clock cycles length for the synchronization */


/** Identifying a timing unit. **/
#define SHRTIM_TIMER_NONE                0U   /* Master timer identifier */
#define SHRTIM_TIMER_MASTER              SHRTIM_MCTRL_MCNTEN   /* Master timer identifier */
#define SHRTIM_TIMER_A                   SHRTIM_MCTRL_TACNTEN  /* Timer A identifier */
#define SHRTIM_TIMER_B                   SHRTIM_MCTRL_TBCNTEN  /* Timer B identifier */
#define SHRTIM_TIMER_C                   SHRTIM_MCTRL_TCCNTEN  /* Timer C identifier */
#define SHRTIM_TIMER_D                   SHRTIM_MCTRL_TDCNTEN  /* Timer D identifier */
#define SHRTIM_TIMER_E                   SHRTIM_MCTRL_TECNTEN  /* Timer E identifier */
#define SHRTIM_TIMER_F                   SHRTIM_MCTRL_TFCNTEN  /* Timer F identifier */

#define SHRTIM_TIMER_X                  (SHRTIM_MCTRL_TFCNTEN | SHRTIM_MCTRL_TACNTEN |\
                                           SHRTIM_MCTRL_TBCNTEN | SHRTIM_MCTRL_TCCNTEN |\
                                           SHRTIM_MCTRL_TDCNTEN | SHRTIM_MCTRL_TECNTEN )
#define SHRTIM_TIMER_ALL                (SHRTIM_TIMER_MASTER | SHRTIM_TIMER_X)

/** Identifying an SHRTIM output. **/
#define SHRTIM_OUTPUT_TA1                SHRTIM_OEN_TA1OEN  /* Timer A - Output 1 identifier */
#define SHRTIM_OUTPUT_TA2                SHRTIM_OEN_TA2OEN  /* Timer A - Output 2 identifier */
#define SHRTIM_OUTPUT_TB1                SHRTIM_OEN_TB1OEN  /* Timer B - Output 1 identifier */
#define SHRTIM_OUTPUT_TB2                SHRTIM_OEN_TB2OEN  /* Timer B - Output 2 identifier */
#define SHRTIM_OUTPUT_TC1                SHRTIM_OEN_TC1OEN  /* Timer C - Output 1 identifier */
#define SHRTIM_OUTPUT_TC2                SHRTIM_OEN_TC2OEN  /* Timer C - Output 2 identifier */
#define SHRTIM_OUTPUT_TD1                SHRTIM_OEN_TD1OEN  /* Timer D - Output 1 identifier */
#define SHRTIM_OUTPUT_TD2                SHRTIM_OEN_TD2OEN  /* Timer D - Output 2 identifier */
#define SHRTIM_OUTPUT_TE1                SHRTIM_OEN_TE1OEN  /* Timer E - Output 1 identifier */
#define SHRTIM_OUTPUT_TE2                SHRTIM_OEN_TE2OEN  /* Timer E - Output 2 identifier */
#define SHRTIM_OUTPUT_TF1                SHRTIM_OEN_TF1OEN  /* Timer F - Output 1 identifier */
#define SHRTIM_OUTPUT_TF2                SHRTIM_OEN_TF2OEN  /* Timer F - Output 2 identifier */

/** Identifying a compare unit. **/
#define SHRTIM_COMPAREUNIT_2             SHRTIM_TXCTRL_DELCMP2M  /* Compare unit 2 identifier */
#define SHRTIM_COMPAREUNIT_4             SHRTIM_TXCTRL_DELCMP4M  /* Compare unit 4 identifier */


/** Identifying a capture unit. **/
#define SHRTIM_CAPTUREUNIT_1             0  /* Capture unit 1 identifier */
#define SHRTIM_CAPTUREUNIT_2             1  /* Capture unit 2 identifier */


/** Identifying a fault channel. **/
#define SHRTIM_FAULT_1      SHRTIM_TXFALT_FALT1EN     /* Fault channel 1 identifier */
#define SHRTIM_FAULT_2      SHRTIM_TXFALT_FALT2EN     /* Fault channel 2 identifier */
#define SHRTIM_FAULT_3      SHRTIM_TXFALT_FALT3EN     /* Fault channel 3 identifier */
#define SHRTIM_FAULT_4      SHRTIM_TXFALT_FALT4EN     /* Fault channel 4 identifier */
#define SHRTIM_FAULT_5      SHRTIM_TXFALT_FALT5EN     /* Fault channel 5 identifier */
#define SHRTIM_FAULT_6      SHRTIM_TXFALT_FALT6EN     /* Fault channel 6 identifier */


/** Identifying an external event channel. **/
#define SHRTIM_EVENT_1        ((uint32_t)0x00000001U)     /* External event channel 1 identifier */
#define SHRTIM_EVENT_2        ((uint32_t)0x00000002U)     /* External event channel 2 identifier */
#define SHRTIM_EVENT_3        ((uint32_t)0x00000004U)     /* External event channel 3 identifier */
#define SHRTIM_EVENT_4        ((uint32_t)0x00000008U)     /* External event channel 4 identifier */
#define SHRTIM_EVENT_5        ((uint32_t)0x00000010U)     /* External event channel 5 identifier */
#define SHRTIM_EVENT_6        ((uint32_t)0x00000020U)     /* External event channel 6 identifier */
#define SHRTIM_EVENT_7        ((uint32_t)0x00000040U)     /* External event channel 7 identifier */
#define SHRTIM_EVENT_8        ((uint32_t)0x00000080U)     /* External event channel 8 identifier */
#define SHRTIM_EVENT_9        ((uint32_t)0x00000100U)     /* External event channel 9 identifier */
#define SHRTIM_EVENT_10       ((uint32_t)0x00000200U)     /* External event channel 10 identifier */

#define SHRTIM_EXEV_SOURCE_1 ((uint32_t)0x00000000U) /* Eternal event source is from GPIO */
#define SHRTIM_EXEV_SOURCE_2 ((uint32_t)0x00000001U) /* Eternal event source is from Comparator */
#define SHRTIM_EXEV_SOURCE_3 ((uint32_t)0x00000002U) /* Eternal event source is from timer */
#define SHRTIM_EXEV_SOURCE_4 ((uint32_t)0x00000003U) /* Eternal event source is from adc analog watch dog */
#define SHRTIM_EXEV_SOURCE_5 ((uint32_t)0x00000004U) /* Eternal event source is from CAN */

/** Defining the state of an SHRTIM output. **/
#define SHRTIM_OUTPUTSTATE_IDLE          ((uint32_t)0x00000001U) /* Main operating mode, where the output can take the active or inactive level as programmed in the crossbar unit */
#define SHRTIM_OUTPUTSTATE_RUN           ((uint32_t)0x00000002U) /* Default operating state (e.g. after an SHRTIM reset, when the outputs are disabled by software or during a burst mode operation) */
#define SHRTIM_OUTPUTSTATE_FAULT         ((uint32_t)0x00000003U) /* Safety state, entered in case of a shut-down request on FAULTx inputs */


/** Identifying an ADC trigger source register. **/
#define SHRTIM_ADCTRIG1_SOURCE_GROUP1              ((uint32_t)0x00000000U) /* ADC trigger 1's source group 1 identifier */
#define SHRTIM_ADCTRIG1_SOURCE_GROUP2              ((uint32_t)0x00000001U) /* ADC trigger 1's source group 2 identifier */
#define SHRTIM_ADCTRIG2_SOURCE_GROUP1              ((uint32_t)0x00000002U) /* ADC trigger 2's source group 1 identifier */
#define SHRTIM_ADCTRIG2_SOURCE_GROUP2              ((uint32_t)0x00000003U) /* ADC trigger 2's source group 2 identifier */
#define SHRTIM_ADCTRIG3_SOURCE_GROUP1              ((uint32_t)0x00000004U) /* ADC trigger 3's source group 1 identifier */
#define SHRTIM_ADCTRIG3_SOURCE_GROUP2              ((uint32_t)0x00000005U) /* ADC trigger 3's source group 2 identifier */
#define SHRTIM_ADCTRIG4_SOURCE_GROUP1              ((uint32_t)0x00000006U) /* ADC trigger 4's source group 1 identifier */
#define SHRTIM_ADCTRIG4_SOURCE_GROUP2              ((uint32_t)0x00000007U) /* ADC trigger 4's source group 2 identifier */
#define SHRTIM_ADCTRIG5_SOURCE                           ((uint32_t)0x00000008U)  /* ADC trigger 5 identifier */
#define SHRTIM_ADCTRIG6_SOURCE                           ((uint32_t)0x00000009U)  /* ADC trigger 6 identifier */
#define SHRTIM_ADCTRIG7_SOURCE                           ((uint32_t)0x0000000AU)  /* ADC trigger 7 identifier */
#define SHRTIM_ADCTRIG8_SOURCE                           ((uint32_t)0x0000000BU)  /* ADC trigger 8 identifier */
#define SHRTIM_ADCTRIG9_SOURCE                           ((uint32_t)0x0000000CU)  /* ADC trigger 9 identifier */
#define SHRTIM_ADCTRIG10_SOURCE                          ((uint32_t)0x0000000DU)  /* ADC trigger 10 identifier */

/** Identifying the ADC trigger's **/
#define SHRTIM_ADCTRIG_1                           ((uint32_t)0x00000000U) /* ADC trigger 1's  identifier */
#define SHRTIM_ADCTRIG_2                           ((uint32_t)0x00000001U) /* ADC trigger 2's  identifier */
#define SHRTIM_ADCTRIG_3                           ((uint32_t)0x00000002U) /* ADC trigger 3's  identifier */
#define SHRTIM_ADCTRIG_4                           ((uint32_t)0x00000003U) /* ADC trigger 4's  identifier */
#define SHRTIM_ADCTRIG_5                           ((uint32_t)0x00000004U)  /* ADC trigger 5's  identifier */
#define SHRTIM_ADCTRIG_6                           ((uint32_t)0x00000005U)  /* ADC trigger 6's  identifier */
#define SHRTIM_ADCTRIG_7                           ((uint32_t)0x00000006U)  /* ADC trigger 7's  identifier */
#define SHRTIM_ADCTRIG_8                           ((uint32_t)0x00000007U)  /* ADC trigger 8's  identifier */
#define SHRTIM_ADCTRIG_9                           ((uint32_t)0x00000008U)  /* ADC trigger 9's  identifier */
#define SHRTIM_ADCTRIG_10                          ((uint32_t)0x00000009U)  /* ADC trigger 10's  identifier */

/** Defining the source triggering the update of the SHRTIM_ADCxR register (transfer from preload to active register). **/
#define SHRTIM_ADCTRIG_UPDATE_MASTER  0x00000000U  /* SHRTIM_ADCxR register update is triggered by the Master timer */
#define SHRTIM_ADCTRIG_UPDATE_TIMER_A 0x00000001U  /* SHRTIM_ADCxR register update is triggered by the Timer A */
#define SHRTIM_ADCTRIG_UPDATE_TIMER_B 0x00000002U  /* SHRTIM_ADCxR register update is triggered by the Timer B */
#define SHRTIM_ADCTRIG_UPDATE_TIMER_C 0x00000003U  /* SHRTIM_ADCxR register update is triggered by the Timer C */
#define SHRTIM_ADCTRIG_UPDATE_TIMER_D 0x00000004U  /* SHRTIM_ADCxR register update is triggered by the Timer D */
#define SHRTIM_ADCTRIG_UPDATE_TIMER_E 0x00000005U  /* SHRTIM_ADCxR register update is triggered by the Timer E */
#define SHRTIM_ADCTRIG_UPDATE_TIMER_F 0x00000006U  /* SHRTIM_ADCxR register update is triggered by the Timer F */

/** defining the events triggering ADC conversion for ADC Triggers 1 and 3. **/
#define SHRTIM_ADTG13_SOURCE_GROUP1_TCPRD      SHRTIM_ADTG1SRC1_ADTG1TCPRD                    /* ADC trigger driven by timer C period event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP5     SHRTIM_ADTG1SRC1_ADTG1TCCMP5                   /* ADC trigger driven by timer C compare 5 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP4     SHRTIM_ADTG1SRC1_ADTG1TCCMP4                   /* ADC trigger driven by timer C compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP3     SHRTIM_ADTG1SRC1_ADTG1TCCMP3                   /* ADC trigger driven by timer C compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP2     SHRTIM_ADTG1SRC1_ADTG1TCCMP2                   /* ADC trigger driven by timer C compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP1     SHRTIM_ADTG1SRC1_ADTG1TCCMP1                   /* ADC trigger driven by timer C compare 1 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBRSTRO    SHRTIM_ADTG1SRC1_ADTG1TBRSTRO                  /* ADC trigger driven by timer B reset and roll-over events */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBPRD      SHRTIM_ADTG1SRC1_ADTG1TBPRD                    /* ADC trigger driven by timer B period event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP5     SHRTIM_ADTG1SRC1_ADTG1TBCMP5                   /* ADC trigger driven by timer B compare 5 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP4     SHRTIM_ADTG1SRC1_ADTG1TBCMP4                   /* ADC trigger driven by timer B compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP3     SHRTIM_ADTG1SRC1_ADTG1TBCMP3                   /* ADC trigger driven by timer B compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP2     SHRTIM_ADTG1SRC1_ADTG1TBCMP2                   /* ADC trigger driven by timer B compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP1     SHRTIM_ADTG1SRC1_ADTG1TBCMP1                   /* ADC trigger driven by timer B compare 1 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TARSTRO    SHRTIM_ADTG1SRC1_ADTG1TARSTRO                  /* ADC trigger driven by timer A reset and roll-over events */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TAPRD      SHRTIM_ADTG1SRC1_ADTG1TAPRD                    /* ADC trigger driven by timer A period event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TACMP5     SHRTIM_ADTG1SRC1_ADTG1TACMP5                   /* ADC trigger driven by timer A compare 5 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TACMP4     SHRTIM_ADTG1SRC1_ADTG1TACMP4                   /* ADC trigger driven by timer A compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TACMP3     SHRTIM_ADTG1SRC1_ADTG1TACMP3                   /* ADC trigger driven by timer A compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TACMP2     SHRTIM_ADTG1SRC1_ADTG1TACMP2                   /* ADC trigger driven by timer A compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_TACMP1     SHRTIM_ADTG1SRC1_ADTG1TACMP1                   /* ADC trigger driven by timer A compare 1 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_MPRD       SHRTIM_ADTG1SRC1_ADTG1MPRD                     /* ADC trigger driven by master period event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_MCMP4      SHRTIM_ADTG1SRC1_ADTG1MCMP4                    /* ADC trigger driven by master compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_MCMP3      SHRTIM_ADTG1SRC1_ADTG1MCMP3                    /* ADC trigger driven by master compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_MCMP2      SHRTIM_ADTG1SRC1_ADTG1MCMP2                    /* ADC trigger driven by master compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP1_MCMP1      SHRTIM_ADTG1SRC1_ADTG1MCMP1                    /* ADC trigger driven by master compare 1 event */

#define SHRTIM_ADTG13_SOURCE_GROUP2_EXEV5      SHRTIM_ADTG1SRC2_ADTG1EXEV5                    /* ADC trigger driven by external event 5 */
#define SHRTIM_ADTG13_SOURCE_GROUP2_EXEV4      SHRTIM_ADTG1SRC2_ADTG1EXEV4                    /* ADC trigger driven by external event 4 */
#define SHRTIM_ADTG13_SOURCE_GROUP2_EXEV3      SHRTIM_ADTG1SRC2_ADTG1EXEV3                    /* ADC trigger driven by external event 3 */
#define SHRTIM_ADTG13_SOURCE_GROUP2_EXEV2      SHRTIM_ADTG1SRC2_ADTG1EXEV2                    /* ADC trigger driven by external event 2 */
#define SHRTIM_ADTG13_SOURCE_GROUP2_EXEV1      SHRTIM_ADTG1SRC2_ADTG1EXEV1                    /* ADC trigger driven by external event 1 */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFRSTRO    SHRTIM_ADTG1SRC2_ADTG1TFRSTRO                  /* ADC trigger driven by timer F reset and roll-over events */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFPRD      SHRTIM_ADTG1SRC2_ADTG1TFPRD                    /* ADC trigger driven by timer F period event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP5     SHRTIM_ADTG1SRC2_ADTG1TFCMP5                   /* ADC trigger driven by timer F compare 5 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP4     SHRTIM_ADTG1SRC2_ADTG1TFCMP4                   /* ADC trigger driven by timer F compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP3     SHRTIM_ADTG1SRC2_ADTG1TFCMP3                   /* ADC trigger driven by timer F compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP2     SHRTIM_ADTG1SRC2_ADTG1TFCMP2                   /* ADC trigger driven by timer F compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP1     SHRTIM_ADTG1SRC2_ADTG1TFCMP1                   /* ADC trigger driven by timer F compare 1 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TEPRD      SHRTIM_ADTG1SRC2_ADTG1TEPRD                    /* ADC trigger driven by timer E period event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TECMP5     SHRTIM_ADTG1SRC2_ADTG1TECMP5                   /* ADC trigger driven by timer E compare 5 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TECMP4     SHRTIM_ADTG1SRC2_ADTG1TECMP4                   /* ADC trigger driven by timer E compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TECMP3     SHRTIM_ADTG1SRC2_ADTG1TECMP3                   /* ADC trigger driven by timer E compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TECMP2     SHRTIM_ADTG1SRC2_ADTG1TECMP2                   /* ADC trigger driven by timer E compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TECMP1     SHRTIM_ADTG1SRC2_ADTG1TECMP1                   /* ADC trigger driven by timer E compare 1 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TDPRD      SHRTIM_ADTG1SRC2_ADTG1TDPRD                    /* ADC trigger driven by timer D period event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP5     SHRTIM_ADTG1SRC2_ADTG1TDCMP5                   /* ADC trigger driven by timer D compare 5 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP4     SHRTIM_ADTG1SRC2_ADTG1TDCMP4                   /* ADC trigger driven by timer D compare 4 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP3     SHRTIM_ADTG1SRC2_ADTG1TDCMP3                   /* ADC trigger driven by timer D compare 3 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP2     SHRTIM_ADTG1SRC2_ADTG1TDCMP2                   /* ADC trigger driven by timer D compare 2 event */
#define SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP1     SHRTIM_ADTG1SRC2_ADTG1TDCMP1                   /* ADC trigger driven by timer D compare 1 event */

/** defining the events triggering ADC conversion for ADC Triggers 2 and 4. **/
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCRSTRO   SHRTIM_ADTG2SRC1_ADTG2TCRSTRO                                       /* ADC trigger  driven by timer C reset and roll-over events */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCPRD     SHRTIM_ADTG2SRC1_ADTG2TCPRD                                         /* ADC trigger  driven by timer C period event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP5    SHRTIM_ADTG2SRC1_ADTG2TCCMP5                                        /* ADC trigger  driven by timer C compare 5 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP4    SHRTIM_ADTG2SRC1_ADTG2TCCMP4                                        /* ADC trigger  driven by timer C compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP3    SHRTIM_ADTG2SRC1_ADTG2TCCMP3                                        /* ADC trigger  driven by timer C compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP2    SHRTIM_ADTG2SRC1_ADTG2TCCMP2                                        /* ADC trigger  driven by timer C compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP1    SHRTIM_ADTG2SRC1_ADTG2TCCMP1                                        /* ADC trigger  driven by timer C compare 1 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TBPRD     SHRTIM_ADTG2SRC1_ADTG2TBPRD                                         /* ADC trigger  driven by timer B period event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP5    SHRTIM_ADTG2SRC1_ADTG2TBCMP5                                        /* ADC trigger  driven by timer B compare 5 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP4    SHRTIM_ADTG2SRC1_ADTG2TBCMP4                                        /* ADC trigger  driven by timer B compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP3    SHRTIM_ADTG2SRC1_ADTG2TBCMP3                                        /* ADC trigger  driven by timer B compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP2    SHRTIM_ADTG2SRC1_ADTG2TBCMP2                                        /* ADC trigger  driven by timer B compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP1    SHRTIM_ADTG2SRC1_ADTG2TBCMP1                                        /* ADC trigger  driven by timer B compare 1 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TAPRD     SHRTIM_ADTG2SRC1_ADTG2TAPRD                                         /* ADC trigger  driven by timer A period event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TACMP5    SHRTIM_ADTG2SRC1_ADTG2TACMP5                                        /* ADC trigger  driven by timer A compare 5 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TACMP4    SHRTIM_ADTG2SRC1_ADTG2TACMP4                                        /* ADC trigger  driven by timer A compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TACMP3    SHRTIM_ADTG2SRC1_ADTG2TACMP3                                        /* ADC trigger  driven by timer A compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TACMP2    SHRTIM_ADTG2SRC1_ADTG2TACMP2                                        /* ADC trigger  driven by timer A compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_TACMP1    SHRTIM_ADTG2SRC1_ADTG2TACMP1                                        /* ADC trigger  driven by timer A compare 1 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_MPRD      SHRTIM_ADTG2SRC1_ADTG2MPRD                                          /* ADC trigger  driven by master period event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_MCMP4     SHRTIM_ADTG2SRC1_ADTG2MCMP4                                         /* ADC trigger  driven by master compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_MCMP3     SHRTIM_ADTG2SRC1_ADTG2MCMP3                                         /* ADC trigger  driven by master compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_MCMP2     SHRTIM_ADTG2SRC1_ADTG2MCMP2                                         /* ADC trigger  driven by master compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP1_MCMP1     SHRTIM_ADTG2SRC1_ADTG2MCMP1                                         /* ADC trigger  driven by master compare 1 event */

#define SHRTIM_ADTG24_SOURCE_GROUP2_EXEV10    SHRTIM_ADTG2SRC2_ADTG2EXEV10                                        /* ADC trigger  driven by external event 10 */
#define SHRTIM_ADTG24_SOURCE_GROUP2_EXEV9     SHRTIM_ADTG2SRC2_ADTG2EXEV9                                         /* ADC trigger  driven by external event 9 */
#define SHRTIM_ADTG24_SOURCE_GROUP2_EXEV8     SHRTIM_ADTG2SRC2_ADTG2EXEV8                                         /* ADC trigger  driven by external event 8 */
#define SHRTIM_ADTG24_SOURCE_GROUP2_EXEV7     SHRTIM_ADTG2SRC2_ADTG2EXEV7                                         /* ADC trigger  driven by external event 7 */
#define SHRTIM_ADTG24_SOURCE_GROUP2_EXEV6     SHRTIM_ADTG2SRC2_ADTG2EXEV6                                         /* ADC trigger  driven by external event 6 */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TFPRD     SHRTIM_ADTG2SRC2_ADTG2TFPRD                                         /* ADC trigger  driven by timer F period event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP5    SHRTIM_ADTG2SRC2_ADTG2TFCMP5                                        /* ADC trigger  driven by timer F compare 5 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP4    SHRTIM_ADTG2SRC2_ADTG2TFCMP4                                        /* ADC trigger  driven by timer F compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP3    SHRTIM_ADTG2SRC2_ADTG2TFCMP3                                        /* ADC trigger  driven by timer F compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP2    SHRTIM_ADTG2SRC2_ADTG2TFCMP2                                        /* ADC trigger  driven by timer F compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP1    SHRTIM_ADTG2SRC2_ADTG2TFCMP1                                        /* ADC trigger  driven by timer F compare 1 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TERSTRO   SHRTIM_ADTG2SRC2_ADTG2TERSTRO                                       /* ADC trigger  driven by timer E reset and roll-over events */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TECMP5    SHRTIM_ADTG2SRC2_ADTG2TECMP5                                        /* ADC trigger  driven by timer E compare 5 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TECMP4    SHRTIM_ADTG2SRC2_ADTG2TECMP4                                        /* ADC trigger  driven by timer E compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TECMP3    SHRTIM_ADTG2SRC2_ADTG2TECMP3                                        /* ADC trigger  driven by timer E compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TECMP2    SHRTIM_ADTG2SRC2_ADTG2TECMP2                                        /* ADC trigger  driven by timer E compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TECMP1    SHRTIM_ADTG2SRC2_ADTG2TECMP1                                        /* ADC trigger  driven by timer E compare 1 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDRSTRO   SHRTIM_ADTG2SRC2_ADTG2TDRSTRO                                       /* ADC trigger  driven by timer D reset and roll-over events */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDPRD     SHRTIM_ADTG2SRC2_ADTG2TDPRD                                         /* ADC trigger  driven by timer D period event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP5    SHRTIM_ADTG2SRC2_ADTG2TDCMP5                                        /* ADC trigger  driven by timer D compare 5 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP4    SHRTIM_ADTG2SRC2_ADTG2TDCMP4                                        /* ADC trigger  driven by timer D compare 4 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP3    SHRTIM_ADTG2SRC2_ADTG2TDCMP3                                        /* ADC trigger  driven by timer D compare 3 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP2    SHRTIM_ADTG2SRC2_ADTG2TDCMP2                                        /* ADC trigger  driven by timer D compare 2 event */
#define SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP1    SHRTIM_ADTG2SRC2_ADTG2TDCMP1                                        /* ADC trigger  driven by timer D compare 1 event */

/** defining the selection that can be used as ADC trigger source for extended ADC 5, 7 ,9 **/
#define SHRTIM_ADTG579_MCMP1      (uint32_t)0x00 /* Trigger on master compare 1 */
#define SHRTIM_ADTG579_MCMP2      (uint32_t)0x01 /* Trigger on master compare 2 */
#define SHRTIM_ADTG579_MCMP3      (uint32_t)0x02 /* Trigger on master compare 3 */
#define SHRTIM_ADTG579_MCMP4      (uint32_t)0x03 /* Trigger on master compare 4 */
#define SHRTIM_ADTG579_MPRD       (uint32_t)0x04 /* Trigger on master period */
#define SHRTIM_ADTG579_EXEV1      (uint32_t)0x05 /* Trigger on external event 1 */
#define SHRTIM_ADTG579_EXEV2      (uint32_t)0x06 /* Trigger on external event 2 */
#define SHRTIM_ADTG579_EXEV3      (uint32_t)0x07 /* Trigger on external event 3 */
#define SHRTIM_ADTG579_EXEV4      (uint32_t)0x08 /* Trigger on external event 4 */
#define SHRTIM_ADTG579_EXEV5      (uint32_t)0x09 /* Trigger on external event 5 */
#define SHRTIM_ADTG579_TACMP1       (uint32_t)0x0A /* Trigger on timer A compare 1 */
#define SHRTIM_ADTG579_TACMP2       (uint32_t)0x0B /* Trigger on timer A compare 2 */
#define SHRTIM_ADTG579_TACMP3       (uint32_t)0x0C /* Trigger on timer A compare 3 */
#define SHRTIM_ADTG579_TACMP4       (uint32_t)0x0D /* Trigger on timer A compare 4 */
#define SHRTIM_ADTG579_TACMP5       (uint32_t)0x0E /* Trigger on timer A compare 5 */
#define SHRTIM_ADTG579_TAPRD      (uint32_t)0x0F /* Trigger on timer A period */
#define SHRTIM_ADTG579_TARSTRO      (uint32_t)0x10 /* Trigger on timer A reset and counter roll-over */
#define SHRTIM_ADTG579_TBCMP1       (uint32_t)0x11 /* Trigger on timer B compare 1 */
#define SHRTIM_ADTG579_TBCMP2       (uint32_t)0x12 /* Trigger on timer B compare 2 */
#define SHRTIM_ADTG579_TBCMP3       (uint32_t)0x13 /* Trigger on timer B compare 3 */
#define SHRTIM_ADTG579_TBCMP4       (uint32_t)0x14 /* Trigger on timer B compare 4 */
#define SHRTIM_ADTG579_TBCMP5       (uint32_t)0x15 /* Trigger on timer B compare 5 */
#define SHRTIM_ADTG579_TBPRD      (uint32_t)0x16 /* Trigger on timer B period */
#define SHRTIM_ADTG579_TBRSTRO      (uint32_t)0x17 /* Trigger on timer B reset and counter roll-over */
#define SHRTIM_ADTG579_TCCMP1       (uint32_t)0x18 /* Trigger on timer C compare 1 */
#define SHRTIM_ADTG579_TCCMP2       (uint32_t)0x19 /* Trigger on timer C compare 2 */
#define SHRTIM_ADTG579_TCCMP3       (uint32_t)0x1A /* Trigger on timer C compare 3 */
#define SHRTIM_ADTG579_TCCMP4       (uint32_t)0x1B /* Trigger on timer C compare 4 */
#define SHRTIM_ADTG579_TCCMP5       (uint32_t)0x1C /* Trigger on timer C compare 5 */
#define SHRTIM_ADTG579_TCPRD      (uint32_t)0x1D /* Trigger on timer C period */
#define SHRTIM_ADTG579_TDCMP1       (uint32_t)0x1E /* Trigger on timer D compare 1 */
#define SHRTIM_ADTG579_TDCMP2       (uint32_t)0x1F /* Trigger on timer D compare 2 */
#define SHRTIM_ADTG579_TDCMP3       (uint32_t)0x20 /* Trigger on timer D compare 3 */
#define SHRTIM_ADTG579_TDCMP4       (uint32_t)0x21 /* Trigger on timer D compare 4 */
#define SHRTIM_ADTG579_TDCMP5       (uint32_t)0x22 /* Trigger on timer D compare 5 */
#define SHRTIM_ADTG579_TDPRD      (uint32_t)0x23 /* Trigger on timer D period */
#define SHRTIM_ADTG579_TECMP1       (uint32_t)0x24 /* Trigger on timer E compare 1 */
#define SHRTIM_ADTG579_TECMP2       (uint32_t)0x25 /* Trigger on timer E compare 2 */
#define SHRTIM_ADTG579_TECMP3       (uint32_t)0x26 /* Trigger on timer E compare 3 */
#define SHRTIM_ADTG579_TECMP4       (uint32_t)0x27 /* Trigger on timer E compare 4 */
#define SHRTIM_ADTG579_TECMP5       (uint32_t)0x28 /* Trigger on timer E compare 5 */
#define SHRTIM_ADTG579_TEPRD      (uint32_t)0x29 /* Trigger on timer E period */
#define SHRTIM_ADTG579_TFCMP1       (uint32_t)0x2A /* Trigger on timer F compare 1 */
#define SHRTIM_ADTG579_TFCMP2       (uint32_t)0x2B /* Trigger on timer F compare 2 */
#define SHRTIM_ADTG579_TFCMP3       (uint32_t)0x2C /* Trigger on timer F compare 3 */
#define SHRTIM_ADTG579_TFCMP4       (uint32_t)0x2D /* Trigger on timer F compare 4 */
#define SHRTIM_ADTG579_TFCMP5       (uint32_t)0x2E /* Trigger on timer F compare 5 */
#define SHRTIM_ADTG579_TFPRD      (uint32_t)0x2F /* Trigger on timer F period */
#define SHRTIM_ADTG579_TFRSTRO      (uint32_t)0x30 /* Trigger on timer F reset and counter roll-over */

/** defining the selection that can be used as ADC trigger source for extended ADC 6, 8 ,10 **/
#define SHRTIM_ADTG6810_MCMP1     (uint32_t)0x00 /* ADC extended trigger on master compare 1 */
#define SHRTIM_ADTG6810_MCMP2     (uint32_t)0x01 /* ADC extended trigger on master compare 2 */
#define SHRTIM_ADTG6810_MCMP3     (uint32_t)0x02 /* ADC extended trigger on master compare 3 */
#define SHRTIM_ADTG6810_MCMP4     (uint32_t)0x03 /* ADC extended trigger on master compare 4 */
#define SHRTIM_ADTG6810_MPRD      (uint32_t)0x04 /* ADC extended trigger on master period */
#define SHRTIM_ADTG6810_EXEV6     (uint32_t)0x05 /* ADC extended trigger on external event 6 */
#define SHRTIM_ADTG6810_EXEV7     (uint32_t)0x06 /* ADC extended trigger on external event 7 */
#define SHRTIM_ADTG6810_EXEV8     (uint32_t)0x07 /* ADC extended trigger on external event 8 */
#define SHRTIM_ADTG6810_EXEV9     (uint32_t)0x08 /* ADC extended trigger on external event 9 */
#define SHRTIM_ADTG6810_EXEV10    (uint32_t)0x09 /* ADC extended trigger on external event 10 */
#define SHRTIM_ADTG6810_TACMP1    (uint32_t)0x0A /* ADC extended trigger on timer A compare 1 */
#define SHRTIM_ADTG6810_TACMP2    (uint32_t)0x0B /* ADC extended trigger on timer A compare 2 */
#define SHRTIM_ADTG6810_TACMP3    (uint32_t)0x0C /* ADC extended trigger on timer A compare 3 */
#define SHRTIM_ADTG6810_TACMP4    (uint32_t)0x0D /* ADC extended trigger on timer A compare 4 */
#define SHRTIM_ADTG6810_TACMP5    (uint32_t)0x0E /* ADC extended trigger on timer A compare 5 */
#define SHRTIM_ADTG6810_TAPRD     (uint32_t)0x0F /* ADC extended trigger on timer A period */
#define SHRTIM_ADTG6810_TBCMP1    (uint32_t)0x10 /* ADC extended trigger on timer B compare 1 */
#define SHRTIM_ADTG6810_TBCMP2    (uint32_t)0x11 /* ADC extended trigger on timer B compare 2 */
#define SHRTIM_ADTG6810_TBCMP3    (uint32_t)0x12 /* ADC extended trigger on timer B compare 3 */
#define SHRTIM_ADTG6810_TBCMP4    (uint32_t)0x13 /* ADC extended trigger on timer B compare 4 */
#define SHRTIM_ADTG6810_TBCMP5    (uint32_t)0x14 /* ADC extended trigger on timer B compare 5 */
#define SHRTIM_ADTG6810_TBPRD     (uint32_t)0x15 /* ADC extended trigger on timer B period */
#define SHRTIM_ADTG6810_TCCMP1    (uint32_t)0x16 /* ADC extended trigger on timer C compare 1 */
#define SHRTIM_ADTG6810_TCCMP2    (uint32_t)0x17 /* ADC extended trigger on timer C compare 2 */
#define SHRTIM_ADTG6810_TCCMP3    (uint32_t)0x18 /* ADC extended trigger on timer C compare 3 */
#define SHRTIM_ADTG6810_TCCMP4    (uint32_t)0x19 /* ADC extended trigger on timer C compare 4 */
#define SHRTIM_ADTG6810_TCCMP5    (uint32_t)0x1A /* ADC extended trigger on timer C compare 5 */
#define SHRTIM_ADTG6810_TCPRD     (uint32_t)0x1B /* ADC extended trigger on timer C period */
#define SHRTIM_ADTG6810_TCRSTRO   (uint32_t)0x1C /* ADC extended trigger on timer C reset and counter roll-over */
#define SHRTIM_ADTG6810_TDCMP1    (uint32_t)0x1D /* ADC extended trigger on timer D compare 1 */
#define SHRTIM_ADTG6810_TDCMP2    (uint32_t)0x1E /* ADC extended trigger on timer D compare 2 */
#define SHRTIM_ADTG6810_TDCMP3    (uint32_t)0x1F /* ADC extended trigger on timer D compare 3 */
#define SHRTIM_ADTG6810_TDCMP4    (uint32_t)0x20 /* ADC extended trigger on timer D compare 4 */
#define SHRTIM_ADTG6810_TDCMP5    (uint32_t)0x21 /* ADC extended trigger on timer D compare 5 */
#define SHRTIM_ADTG6810_TDPRD     (uint32_t)0x22 /* ADC extended trigger on timer D period */
#define SHRTIM_ADTG6810_TDRSTRO   (uint32_t)0x23 /* ADC extended trigger on timer D reset and counter roll-over */
#define SHRTIM_ADTG6810_TECMP1    (uint32_t)0x24 /* ADC extended trigger on timer E compare 1 */
#define SHRTIM_ADTG6810_TECMP2    (uint32_t)0x25 /* ADC extended trigger on timer E compare 2 */
#define SHRTIM_ADTG6810_TECMP3    (uint32_t)0x26 /* ADC extended trigger on timer E compare 3 */
#define SHRTIM_ADTG6810_TECMP4    (uint32_t)0x27 /* ADC extended trigger on timer E compare 4 */
#define SHRTIM_ADTG6810_TECMP5    (uint32_t)0x28 /* ADC extended trigger on timer E compare 5 */
#define SHRTIM_ADTG6810_TERSTRO   (uint32_t)0x29 /* ADC extended trigger on timer E reset and counter roll-over */
#define SHRTIM_ADTG6810_TFCMP1    (uint32_t)0x2A /* ADC extended trigger on timer F compare 1 */
#define SHRTIM_ADTG6810_TFCMP2    (uint32_t)0x2B /* ADC extended trigger on timer F compare 2 */
#define SHRTIM_ADTG6810_TFCMP3    (uint32_t)0x2C /* ADC extended trigger on timer F compare 3 */
#define SHRTIM_ADTG6810_TFCMP4    (uint32_t)0x2D /* ADC extended trigger on timer F compare 4 */
#define SHRTIM_ADTG6810_TFCMP5    (uint32_t)0x2E /* ADC extended trigger on timer F compare 5 */
#define SHRTIM_ADTG6810_TFPRD     (uint32_t)0x2F /* ADC extended trigger on timer F period */

/** Defining timer high-resolution clock prescaler ratio. **/
#define SHRTIM_PRESCALERRATIO_MUL32      0x00000000U              /* fHRCK: fSHRTIM x 32 = 8 GHz - Resolution: 125 ps - Min PWM frequency: 122.1 kHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_MUL16      ((uint32_t)0x00000001U)  /* fHRCK: fSHRTIM x 16 = 4 GHz - Resolution: 250 ps - Min PWM frequency: 61.0 KHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_MUL8       ((uint32_t)0x00000002U)  /* fHRCK: fSHRTIM x 8 = 2 GHz - Resolution: 500 ps - Min PWM frequency: 30.5 kHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_MUL4       ((uint32_t)0x00000003U)  /* fHRCK: fSHRTIM x 4 = 1 GHz - Resolution: 1 ns - Min PWM frequency: 15.3 kHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_MUL2       ((uint32_t)0x00000004U)  /* fHRCK: fSHRTIM x 2 = 500 MHz - Resolution: 2 ns - Min PWM frequency: 7.63 kHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_DIV1       ((uint32_t)0x00000005U)  /* fHRCK: fSHRTIM = 250 MHz - Resolution: 4 ns - Min PWM frequency: 3.81 kHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_DIV2       ((uint32_t)0x00000006U)  /* fHRCK: fSHRTIM / 2 = 125 MHz - Resolution: 8 ns- Min PWM frequency: 1.91 kHz (fSHRTIM=250MHz) */
#define SHRTIM_PRESCALERRATIO_DIV4       ((uint32_t)0x00000007U)  /* fHRCK: fSHRTIM / 4 = 62.5 MHz - Resolution: 16 ns- Min PWM frequency: 0.95 Hz (fSHRTIM=250MHz) */

/** Defining timer counter operating mode. **/
#define SHRTIM_MODE_CONTINUOUS           ((uint32_t)0x00000008U)  /* The timer operates in continuous (free-running) mode */
#define SHRTIM_MODE_SINGLESHOT           0x00000000U              /* The timer operates in non retriggerable single-shot mode */
#define SHRTIM_MODE_RETRIGGERABLE        ((uint32_t)0x00000010U)  /* The timer operates in retriggerable single-shot mode */


/** Defining on which output the DAC synchronization event is sent. **/
#define SHRTIM_DACTRIG_NONE           0x00000000U                     /* No DAC synchronization event generated */
#define SHRTIM_DACTRIG_DACTRIGOUT_1   (SHRTIM_MCTRL_DACTRIG_0)                       /* DAC synchronization event generated on DACTrigOut1 output upon timer update */
#define SHRTIM_DACTRIG_DACTRIGOUT_2   (SHRTIM_MCTRL_DACTRIG_1)                       /* DAC synchronization event generated on DACTrigOut2 output upon timer update */
#define SHRTIM_DACTRIG_DACTRIGOUT_3   (SHRTIM_MCTRL_DACTRIG_1 | SHRTIM_MCTRL_DACTRIG_0) /* DAC synchronization event generated on DACTrigOut3 output upon timer update */


/** Defining whether the registers update is done synchronously with any other timer or master update. **/
#define SHRTIM_UPDATETRIG_NONE        0x00000000U            /* Register update is disabled */
#define SHRTIM_UPDATETRIG_MASTER      SHRTIM_TXCTRL_MUEN       /* Register update is triggered by the master timer update */
#define SHRTIM_UPDATETRIG_TIMER_A     SHRTIM_TXCTRL_TAUEN        /* Register update is triggered by the timer A update */
#define SHRTIM_UPDATETRIG_TIMER_B     SHRTIM_TXCTRL_TBUEN        /* Register update is triggered by the timer B update */
#define SHRTIM_UPDATETRIG_TIMER_C     SHRTIM_TXCTRL_TCUEN        /* Register update is triggered by the timer C update*/
#define SHRTIM_UPDATETRIG_TIMER_D     SHRTIM_TXCTRL_TDUEN        /* Register update is triggered by the timer D update */
#define SHRTIM_UPDATETRIG_TIMER_E     SHRTIM_TXCTRL_TEUEN        /* Register update is triggered by the timer E update */
#define SHRTIM_UPDATETRIG_TIMER_F     SHRTIM_TXCTRL_TFUEN        /* Register update is triggered by the timer F update */
#define SHRTIM_UPDATETRIG_REPETITION  SHRTIM_TXCTRL_REPTUEN      /* Register update is triggered when the counter rolls over and SHRTIM_TxREPT = 0*/
#define SHRTIM_UPDATETRIG_RESET       SHRTIM_TXCTRL_RSTROUEN      /* Register update is triggered by counter reset or roll-over to 0 after reaching the period value in continuous mode */

/** Defining how the update occurs relatively to the burst DMA transaction and the 
    external update request on update enable inputs 1 to 3. **/
#define SHRTIM_UPDATEGATING_INDEPENDENT     0x00000000U                                               /* Update done independently from the DMA burst transfer completion */
#define SHRTIM_UPDATEGATING_DMABURST        (SHRTIM_TXCTRL_UPDGAT_0)                                                /* Update done when the DMA burst transfer is completed */
#define SHRTIM_UPDATEGATING_DMABURST_UPDATE (SHRTIM_TXCTRL_UPDGAT_1)                                                /* Update done on timer roll-over following a DMA burst transfer completion*/
#define SHRTIM_UPDATEGATING_UPDEN1          (SHRTIM_TXCTRL_UPDGAT_1 | SHRTIM_TXCTRL_UPDGAT_0)                         /* Slave timer only - Update done on a rising edge of SHRTIM update enable input 1 */
#define SHRTIM_UPDATEGATING_UPDEN2          (SHRTIM_TXCTRL_UPDGAT_2)                                                /* Slave timer only - Update done on a rising edge of SHRTIM update enable input 2 */
#define SHRTIM_UPDATEGATING_UPDEN3          (SHRTIM_TXCTRL_UPDGAT_2 | SHRTIM_TXCTRL_UPDGAT_0)                         /* Slave timer only - Update done on a rising edge of SHRTIM update enable input 3 */
#define SHRTIM_UPDATEGATING_UPDEN1_UPDATE   (SHRTIM_TXCTRL_UPDGAT_2 | SHRTIM_TXCTRL_UPDGAT_1)                         /* Slave timer only -  Update done on the update event following a rising edge of SHRTIM update enable input 1 */
#define SHRTIM_UPDATEGATING_UPDEN2_UPDATE   (SHRTIM_TXCTRL_UPDGAT_2 | SHRTIM_TXCTRL_UPDGAT_1 | SHRTIM_TXCTRL_UPDGAT_0)  /* Slave timer only - Update done on the update event following a rising edge of SHRTIM update enable input 2 */
#define SHRTIM_UPDATEGATING_UPDEN3_UPDATE   (SHRTIM_TXCTRL_UPDGAT_3)                                                /* Slave timer only - Update done on the update event following a rising edge of SHRTIM update enable input 3 */


/** Defining whether the compare register is behaving in regular mode 
    (compare match issued as soon as counter equal compare) or in auto-delayed mode. **/
#define SHRTIM_COMPAREMODE_REGULAR          0x00000000U                         /* standard compare mode */
#define SHRTIM_COMPAREMODE_DELAY_NOTIMEOUT  (SHRTIM_TXCTRL_DELCMP2M_0)                         /* Compare event generated only if a capture has occurred */
#define SHRTIM_COMPAREMODE_DELAY_CMP1       (SHRTIM_TXCTRL_DELCMP2M_1)                         /* Compare event generated if a capture has occurred or after a Compare 1 match (timeout if capture event is missing) */
#define SHRTIM_COMPAREMODE_DELAY_CMP3       (SHRTIM_TXCTRL_DELCMP2M_1 | SHRTIM_TXCTRL_DELCMP2M_0) /* Compare event generated if a capture has occurred or after a Compare 3 match (timeout if capture event is missing) */

/** Defining the events that can be selected to trigger the reset of the timer counter. **/
#define SHRTIM_RESETTRIG_NONE        0x00000000U            /* No counter reset trigger */
#define SHRTIM_RESETTRIG_UPDATE         SHRTIM_TACNTRST_UPD      /* The timer counter is reset upon update event */
#define SHRTIM_RESETTRIG_CMP2           SHRTIM_TACNTRST_CMP2        /* The timer counter is reset upon Timer Compare 2 event */
#define SHRTIM_RESETTRIG_CMP4           SHRTIM_TACNTRST_CMP4        /* The timer counter is reset upon Timer Compare 4 event */
#define SHRTIM_RESETTRIG_MASTER_PER     SHRTIM_TACNTRST_MPRD      /* The timer counter is reset upon master timer period event */
#define SHRTIM_RESETTRIG_MASTER_CMP1    SHRTIM_TACNTRST_MCMP1     /* The timer counter is reset upon master timer Compare 1 event */
#define SHRTIM_RESETTRIG_MASTER_CMP2    SHRTIM_TACNTRST_MCMP2     /* The timer counter is reset upon master timer Compare 2 event */
#define SHRTIM_RESETTRIG_MASTER_CMP3    SHRTIM_TACNTRST_MCMP3     /* The timer counter is reset upon master timer Compare 3 event */
#define SHRTIM_RESETTRIG_MASTER_CMP4    SHRTIM_TACNTRST_MCMP4     /* The timer counter is reset upon master timer Compare 4 event */
#define SHRTIM_RESETTRIG_EXEV_1         SHRTIM_TACNTRST_EXEV1    /* The timer counter is reset upon external event 1 */
#define SHRTIM_RESETTRIG_EXEV_2         SHRTIM_TACNTRST_EXEV2    /* The timer counter is reset upon external event 2 */
#define SHRTIM_RESETTRIG_EXEV_3         SHRTIM_TACNTRST_EXEV3    /* The timer counter is reset upon external event 3 */
#define SHRTIM_RESETTRIG_EXEV_4         SHRTIM_TACNTRST_EXEV4    /* The timer counter is reset upon external event 4 */
#define SHRTIM_RESETTRIG_EXEV_5         SHRTIM_TACNTRST_EXEV5    /* The timer counter is reset upon external event 5 */
#define SHRTIM_RESETTRIG_EXEV_6         SHRTIM_TACNTRST_EXEV6    /* The timer counter is reset upon external event 6 */
#define SHRTIM_RESETTRIG_EXEV_7         SHRTIM_TACNTRST_EXEV7    /* The timer counter is reset upon external event 7 */
#define SHRTIM_RESETTRIG_EXEV_8         SHRTIM_TACNTRST_EXEV8    /* The timer counter is reset upon external event 8 */
#define SHRTIM_RESETTRIG_EXEV_9         SHRTIM_TACNTRST_EXEV9    /* The timer counter is reset upon external event 9 */
#define SHRTIM_RESETTRIG_EXEV_10        SHRTIM_TACNTRST_EXEV10   /* The timer counter is reset upon external event 10 */
#define SHRTIM_RESETTRIG_OTHER1_CMP1    SHRTIM_TACNTRST_TBCMP1    /* The timer counter is reset upon other timer Compare 1 event */
#define SHRTIM_RESETTRIG_OTHER1_CMP2    SHRTIM_TACNTRST_TBCMP2    /* The timer counter is reset upon other timer Compare 2 event */
#define SHRTIM_RESETTRIG_OTHER1_CMP4    SHRTIM_TACNTRST_TBCMP4    /* The timer counter is reset upon other timer Compare 4 event */
#define SHRTIM_RESETTRIG_OTHER2_CMP1    SHRTIM_TACNTRST_TCCMP1    /* The timer counter is reset upon other timer Compare 1 event */
#define SHRTIM_RESETTRIG_OTHER2_CMP2    SHRTIM_TACNTRST_TCCMP2    /* The timer counter is reset upon other timer Compare 2 event */
#define SHRTIM_RESETTRIG_OTHER2_CMP4    SHRTIM_TACNTRST_TCCMP4    /* The timer counter is reset upon other timer Compare 4 event */
#define SHRTIM_RESETTRIG_OTHER3_CMP1    SHRTIM_TACNTRST_TDCMP1    /* The timer counter is reset upon other timer Compare 1 event */
#define SHRTIM_RESETTRIG_OTHER3_CMP2    SHRTIM_TACNTRST_TDCMP2    /* The timer counter is reset upon other timer Compare 2 event */
#define SHRTIM_RESETTRIG_OTHER3_CMP4    SHRTIM_TACNTRST_TDCMP4    /* The timer counter is reset upon other timer Compare 4 event */
#define SHRTIM_RESETTRIG_OTHER4_CMP1    SHRTIM_TACNTRST_TECMP1    /* The timer counter is reset upon other timer Compare 1 event */
#define SHRTIM_RESETTRIG_OTHER4_CMP2    SHRTIM_TACNTRST_TECMP2    /* The timer counter is reset upon other timer Compare 2 event */
#define SHRTIM_RESETTRIG_OTHER4_CMP4    SHRTIM_TACNTRST_TECMP4    /* The timer counter is reset upon other timer Compare 4 event */
#define SHRTIM_RESETTRIG_OTHER5_CMP1    SHRTIM_TACNTRST_TFCMP1    /* The timer counter is reset upon other timer Compare 1 event */
#define SHRTIM_RESETTRIG_OTHER5_CMP2    SHRTIM_TACNTRST_TFCMP2    /* The timer counter is reset upon other timer Compare 2 event */

/** Defining the events that can be selected to trigger the capture of the timing unit counter. **/
#define SHRTIM_CAPTURETRIG_NONE        (uint64_t)0                               /* Capture trigger is disabled */
#define SHRTIM_CAPTURETRIG_SW          (uint64_t)SHRTIM_TACPT1CTRL_SW              /* The sw event triggers the Capture */
#define SHRTIM_CAPTURETRIG_UPDATE      (uint64_t)SHRTIM_TACPT1CTRL_UPD             /* The update event triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_1      (uint64_t)SHRTIM_TACPT1CTRL_EXEV1           /* The External event 1 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_2      (uint64_t)SHRTIM_TACPT1CTRL_EXEV2           /* The External event 2 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_3      (uint64_t)SHRTIM_TACPT1CTRL_EXEV3           /* The External event 3 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_4      (uint64_t)SHRTIM_TACPT1CTRL_EXEV4           /* The External event 4 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_5      (uint64_t)SHRTIM_TACPT1CTRL_EXEV5           /* The External event 5 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_6      (uint64_t)SHRTIM_TACPT1CTRL_EXEV6           /* The External event 6 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_7      (uint64_t)SHRTIM_TACPT1CTRL_EXEV7           /* The External event 7 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_8      (uint64_t)SHRTIM_TACPT1CTRL_EXEV8           /* The External event 8 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_9      (uint64_t)SHRTIM_TACPT1CTRL_EXEV9           /* The External event 9 triggers the Capture */
#define SHRTIM_CAPTURETRIG_EXEV_10     (uint64_t)SHRTIM_TACPT1CTRL_EXEV10          /* The External event 10 triggers the Capture */
#define SHRTIM_CAPTURETRIG_TA1_SET     (uint64_t)(12U) <<32  /* Capture is triggered by TA1 output inactive to active transition */
#define SHRTIM_CAPTURETRIG_TA1_RESET   (uint64_t)(13U) <<32  /* Capture is triggered by TA1 output active to inactive transition */
#define SHRTIM_CAPTURETRIG_TIMA_CMP1   (uint64_t)(14U) <<32  /* Timer A Compare 1 triggers Capture */
#define SHRTIM_CAPTURETRIG_TIMA_CMP2   (uint64_t)(15U) <<32  /* Timer A Compare 2 triggers Capture */
#define SHRTIM_CAPTURETRIG_TB1_SET     (uint64_t)(16U) <<32  /* Capture is triggered by TB1 output inactive to active transition */
#define SHRTIM_CAPTURETRIG_TB1_RESET   (uint64_t)(17U) <<32  /* Capture is triggered by TB1 output active to inactive transition */
#define SHRTIM_CAPTURETRIG_TIMB_CMP1   (uint64_t)(18U) <<32  /* Timer B Compare 1 triggers Capture */
#define SHRTIM_CAPTURETRIG_TIMB_CMP2   (uint64_t)(19U) <<32  /* Timer B Compare 2 triggers Capture */
#define SHRTIM_CAPTURETRIG_TC1_SET     (uint64_t)(20U) <<32  /* Capture is triggered by TC1 output inactive to active transition */
#define SHRTIM_CAPTURETRIG_TC1_RESET   (uint64_t)(21U) <<32  /* Capture is triggered by TC1 output active to inactive transition */
#define SHRTIM_CAPTURETRIG_TIMC_CMP1   (uint64_t)(22U) <<32  /* Timer C Compare 1 triggers Capture */
#define SHRTIM_CAPTURETRIG_TIMC_CMP2   (uint64_t)(23U) <<32  /* Timer C Compare 2 triggers Capture */
#define SHRTIM_CAPTURETRIG_TD1_SET     (uint64_t)(24U) <<32  /* Capture is triggered by TD1 output inactive to active transition */
#define SHRTIM_CAPTURETRIG_TD1_RESET   (uint64_t)(25U) <<32  /* Capture is triggered by TD1 output active to inactive transition */
#define SHRTIM_CAPTURETRIG_TIMD_CMP1   (uint64_t)(26U) <<32  /* Timer D Compare 1 triggers Capture */
#define SHRTIM_CAPTURETRIG_TIMD_CMP2   (uint64_t)(27U) <<32  /* Timer D Compare 2 triggers Capture */
#define SHRTIM_CAPTURETRIG_TE1_SET     (uint64_t)(28U) <<32  /* Capture is triggered by TE1 output inactive to active transition */
#define SHRTIM_CAPTURETRIG_TE1_RESET   (uint64_t)(29U) <<32  /* Capture is triggered by TE1 output active to inactive transition */
#define SHRTIM_CAPTURETRIG_TIME_CMP1   (uint64_t)(30U) <<32  /* Timer E Compare 1 triggers Capture */
#define SHRTIM_CAPTURETRIG_TIME_CMP2   (uint64_t)(31U) <<32  /* Timer E Compare 2 triggers Capture */
#define SHRTIM_CAPTURETRIG_TF1_SET     (uint64_t)(0U) <<32  /* Capture is triggered by TF1 output inactive to active transition */
#define SHRTIM_CAPTURETRIG_TF1_RESET   (uint64_t)(1U) <<32  /* Capture is triggered by TF1 output active to inactive transition */
#define SHRTIM_CAPTURETRIG_TIMF_CMP1   (uint64_t)(2U) <<32  /* Timer F Compare 1 triggers Capture */
#define SHRTIM_CAPTURETRIG_TIMF_CMP2   (uint64_t)(3U) <<32  /* Timer F Compare 2 triggers Capture */


/** Defining all possible delayed protection modes for a timer
    (also define the source and outputs on which the delayed protection schemes are applied). **/
#define SHRTIM_DP_DELAYOUT1_EXEV6  0x00000000U                                            /* Timers A, B, C: Output 1 delayed Idle on external Event 6 */
#define SHRTIM_DP_DELAYOUT2_EXEV6  (SHRTIM_TXOUT_DP_0)                                             /* Timers A, B, C: Output 2 delayed Idle on external Event 6 */
#define SHRTIM_DP_DELAYBOTH_EXEV6  (SHRTIM_TXOUT_DP_1)                                             /* Timers A, B, C: Output 1 and output 2 delayed Idle on external Event 6 */
#define SHRTIM_DP_BALANCED_EXEV6   (SHRTIM_TXOUT_DP_1 | SHRTIM_TXOUT_DP_0)                       /* Timers A, B, C: Balanced Idle on external Event 6 */
#define SHRTIM_DP_DELAYOUT1_EXEV7  (SHRTIM_TXOUT_DP_2)                                             /* Timers A, B, C: Output 1 delayed Idle on external Event 7 */
#define SHRTIM_DP_DELAYOUT2_EXEV7  (SHRTIM_TXOUT_DP_2 | SHRTIM_TXOUT_DP_0)                       /* Timers A, B, C: Output 2 delayed Idle on external Event 7 */
#define SHRTIM_DP_DELAYBOTH_EXEV7  (SHRTIM_TXOUT_DP_2 | SHRTIM_TXOUT_DP_1)                       /* Timers A, B, C: Output 1 and output2 delayed Idle on external Event 7 */
#define SHRTIM_DP_BALANCED_EXEV7   (SHRTIM_TXOUT_DP_2 | SHRTIM_TXOUT_DP_1 | SHRTIM_TXOUT_DP_0) /* Timers A, B, C: Balanced Idle on external Event 7 */

#define SHRTIM_DP_DELAYOUT1_EXEV8  0x00000000U                                             /* Timers D, E: Output 1 delayed Idle on external Event 8 */
#define SHRTIM_DP_DELAYOUT2_EXEV8  (SHRTIM_TXOUT_DP_0)                                               /* Timers D, E: Output 2 delayed Idle on external Event 8 */
#define SHRTIM_DP_DELAYBOTH_EXEV8  (SHRTIM_TXOUT_DP_1)                                               /* Timers D, E: Output 1 and output 2 delayed Idle on external Event 8 */
#define SHRTIM_DP_BALANCED_EXEV8   (SHRTIM_TXOUT_DP_1 | SHRTIM_TXOUT_DP_0)                         /* Timers D, E: Balanced Idle on external Event 8 */
#define SHRTIM_DP_DELAYOUT1_EXEV9  (SHRTIM_TXOUT_DP_2)                                               /* Timers D, E: Output 1 delayed Idle on external Event 9 */
#define SHRTIM_DP_DELAYOUT2_EXEV9  (SHRTIM_TXOUT_DP_2 | SHRTIM_TXOUT_DP_0)                         /* Timers D, E: Output 2 delayed Idle on external Event 9 */
#define SHRTIM_DP_DELAYBOTH_EXEV9  (SHRTIM_TXOUT_DP_2 | SHRTIM_TXOUT_DP_1)                         /* Timers D, E: Output 1 and output2 delayed Idle on external Event 9 */
#define SHRTIM_DP_BALANCED_EXEV9   (SHRTIM_TXOUT_DP_2 | SHRTIM_TXOUT_DP_1 | SHRTIM_TXOUT_DP_0)   /* Timers D, E: Balanced Idle on external Event 9 */

/** Identifying an software delay protection. **/
#define SHRTIM_SOFT_DP_TA1                (SHRTIM_SFTDP_SFTDPA1)  /* Timer A - channel 1 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TA2                (SHRTIM_SFTDP_SFTDPA2)  /* Timer A - channel 2 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TB1                (SHRTIM_SFTDP_SFTDPB1)  /* Timer B - channel 1 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TB2                (SHRTIM_SFTDP_SFTDPB2)  /* Timer B - channel 2 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TC1                (SHRTIM_SFTDP_SFTDPC1)  /* Timer C - channel 1 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TC2                (SHRTIM_SFTDP_SFTDPC2)  /* Timer C - channel 2 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TD1                (SHRTIM_SFTDP_SFTDPD1)  /* Timer D - channel 1 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TD2                (SHRTIM_SFTDP_SFTDPD2)  /* Timer D - channel 2 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TE1                (SHRTIM_SFTDP_SFTDPE1)  /* Timer E - channel 1 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TE2                (SHRTIM_SFTDP_SFTDPE2)  /* Timer E - channel 2 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TF1                (SHRTIM_SFTDP_SFTDPF1)  /* Timer F - channel 1 soft delay protection identifier */
#define SHRTIM_SOFT_DP_TF2                (SHRTIM_SFTDP_SFTDPF2)  /* Timer F - channel 2 soft delay protection identifier */

/** Defining how the timer behaves during a burst mode operation. **/
#define SHRTIM_BURSTMODE_MAINTAINCLOCK (uint32_t)0x000000 /* Timer counter clock is maintained and the timer operates normally */
#define SHRTIM_BURSTMODE_RESETCOUNTER  (SHRTIM_BMCTRL_MBM)  /* Timer counter clock is stopped and the counter is reset */

/** Defining the registers that can be written during a burst DMA operation. **/
#define SHRTIM_BURSTDMA_NONE                0x00000000U               /* No register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MCTRL               (SHRTIM_BDMTUPD_MCTRL)        /* MCTRL register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MINTCLR             (SHRTIM_BDMTUPD_MINTCLR)       /* MINTCLR register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MIDEN               (SHRTIM_BDMTUPD_MIDEN)      /* MIDEN register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MCNT                (SHRTIM_BDMTUPD_MCNT)       /* MCNT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MPRD                (SHRTIM_BDMTUPD_MPRD)       /* MPRD register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MREPT               (SHRTIM_BDMTUPD_MREPT)       /* MREPT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MCMPDAT1            (SHRTIM_BDMTUPD_MCMPDAT1)      /* MCMPDAT1 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MCMPDAT2            (SHRTIM_BDMTUPD_MCMPDAT2)      /* MCMPDAT2 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MCMPDAT3            (SHRTIM_BDMTUPD_MCMPDAT3)      /* MCMPDAT3 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_MCMPDAT4            (SHRTIM_BDMTUPD_MCMPDAT4)      /* MCMPDAT4 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCTRL              (SHRTIM_BDTAUPD_TACTRL)      /* TxCTRL register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXINTCLR            (SHRTIM_BDTAUPD_TAINTCLR)     /* TxINTCLR register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXIDEN              (SHRTIM_BDTAUPD_TAIDEN)    /* TxIDEN register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCNT               (SHRTIM_BDTAUPD_TACNT)     /* TxCNT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXPRD               (SHRTIM_BDTAUPD_TAPRD)     /* TxPRD register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXREPT              (SHRTIM_BDTAUPD_TAREPT)     /* TxREPT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCMP1DAT           (SHRTIM_BDTAUPD_TACMP1DAT)    /* TxCMP1DAT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCMP2DAT           (SHRTIM_BDTAUPD_TACMP2DAT)    /* TxCMP2DAT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCMP3DAT           (SHRTIM_BDTAUPD_TACMP3DAT)    /* TxCMP3DAT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCMP4DAT           (SHRTIM_BDTAUPD_TACMP4DAT)    /* TxCMP4DAT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXDT                (SHRTIM_BDTAUPD_TADT)     /* TxDT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXSET1              (SHRTIM_BDTAUPD_TASET1)   /* TxSET1 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXRST1              (SHRTIM_BDTAUPD_TARST1)   /* TxRST1 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXSET2              (SHRTIM_BDTAUPD_TASET2)   /* TxSET2 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXRST2              (SHRTIM_BDTAUPD_TARST2)   /* TxRST2 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXEXEVFLT1          (SHRTIM_BDTAUPD_TAEXEVFLT1)   /* TxEXEVFLT1 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXEXEVFLT2          (SHRTIM_BDTAUPD_TAEXEVFLT2)   /* TxEXEVFLT2 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCNTRST            (SHRTIM_BDTAUPD_TACNTRST)    /* TxCNTRST register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCHOP              (SHRTIM_BDTAUPD_TACHOP)    /* TxCHOP register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXOUT               (SHRTIM_BDTAUPD_TAOUT)    /* TxOUT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXFALT              (SHRTIM_BDTAUPD_TAFALT)    /* TxFALT register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXCTRL2             (SHRTIM_BDTAUPD_TACTRL2)     /* TxCTRL2 register is updated by Burst DMA accesses */
#define SHRTIM_BURSTDMA_TXEXEVFLT3          (SHRTIM_BDTAUPD_TAEXEVFLT3)   /* TxEXEVFLT3 register is updated by Burst DMA accesses */


/** Defining on which output the signal is currently applied in push-pull mode. **/
#define SHRTIM_CPPSTAT_OUTPUT1   ((uint32_t) 0x00000000U) /* Signal applied on output 1 and output 2 forced inactive */
#define SHRTIM_CPPSTAT_OUTPUT2   (SHRTIM_TXINTSTS_CPPSTS)  /* Signal applied on output 2 and output 1 forced inactive */


/** Defining on which output the signal was applied, 
    in push-pull mode balanced fault mode or delayed idle mode, when the protection was triggered. **/
#define SHRTIM_IPPSTAT_OUTPUT1   ((uint32_t) 0x00000000U)    /* Protection occurred when the output 1 was active and output 2 forced inactive */
#define SHRTIM_IPPSTAT_OUTPUT2   (SHRTIM_TXINTSTS_IPPSTS)     /* Protection occurred when the output 2 was active and output 1 forced inactive */

/** Defining the event filtering applied to external events by a timer. **/
#define SHRTIM_EXEVFLT_NONE                            (0x00000000U)
#define SHRTIM_EXEVFLT_BLANKINGCMP1                    (SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                                                   /* Blanking from counter reset/roll-over to Compare 1U */
#define SHRTIM_EXEVFLT_BLANKINGCMP2                    (SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                                                   /* Blanking from counter reset/roll-over to Compare 2U */
#define SHRTIM_EXEVFLT_BLANKINGCMP3                    (SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from counter reset/roll-over to Compare 3U */
#define SHRTIM_EXEVFLT_BLANKINGCMP4                    (SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                                                   /* Blanking from counter reset/roll-over to Compare 4U */
/* Blanking Filter for TIMER A */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF1_TIMBCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR1 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF2_TIMBCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR2 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF3_TIMBOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR3 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF4_TIMCCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3)                                                   /* Blanking from another timing unit: TIMFLTR4 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF5_TIMCCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR5 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF6_TIMFCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR6 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF7_TIMDCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR7 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMAEEF8_TIMECMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                           /* Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER B */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF1_TIMACMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR1 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF2_TIMACMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR2 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF3_TIMAOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR3 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF4_TIMCCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3)                                                   /* Blanking from another timing unit: TIMFLTR4 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF5_TIMCCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR5 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF6_TIMFCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR6 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF7_TIMDCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR7 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMBEEF8_TIMECMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                           /* Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER C */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF1_TIMACMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR1 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF2_TIMBCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR2 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF3_TIMBCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR3 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF4_TIMFCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3)                                                   /* Blanking from another timing unit: TIMFLTR4 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF5_TIMDCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR5 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF6_TIMDCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR6 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF7_TIMDOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR7 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMCEEF8_TIMECMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                           /* Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER D */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF1_TIMACMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR1 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF2_TIMBCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR2 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF3_TIMCCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR3 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF4_TIMCCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3)                                                   /* Blanking from another timing unit: TIMFLTR4 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF5_TIMCOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR5 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF6_TIMECMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR6 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF7_TIMECMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR7 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMDEEF8_TIMFCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                           /* Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER E */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF1_TIMACMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR1 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF2_TIMBCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR2 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF3_TIMCCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR3 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF4_TIMFCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3)                                                   /* Blanking from another timing unit: TIMFLTR4 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF5_TIMFOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR5 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF6_TIMDCMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR6 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF7_TIMDCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR7 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMEEEF8_TIMDOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                           /* Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER F */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF1_TIMACMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR1 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF2_TIMBCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR2 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF3_TIMCCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR3 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF4_TIMDCMP2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3)                                                   /* Blanking from another timing unit: TIMFLTR4 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF5_TIMDCMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)                           /* Blanking from another timing unit: TIMFLTR5 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF6_TIMECMP1      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)                           /* Blanking from another timing unit: TIMFLTR6 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF7_TIMECMP4      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Blanking from another timing unit: TIMFLTR7 source */
#define SHRTIM_EXEVFLT_BLANKING_TIMFEEF8_TIMEOUT2      (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2)                           /* Blanking from another timing unit: TIMFLTR8 source */

#define SHRTIM_EXEVFLT_WINDOWINGCMP2                   (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Windowing from counter reset/roll-over to Compare 2U */
#define SHRTIM_EXEVFLT_WINDOWINGCMP3                   (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1)   /* Windowing from counter reset/roll-over to Compare 3U */
#define SHRTIM_EXEVFLT_WINDOWINGTIM                    (SHRTIM_TXEXEVFLT1_EXEV1FLT_3 | SHRTIM_TXEXEVFLT1_EXEV1FLT_2 | SHRTIM_TXEXEVFLT1_EXEV1FLT_1\
                                                                                                       | SHRTIM_TXEXEVFLT1_EXEV1FLT_0)   /* Windowing from another timing unit: TIMWIN source */


/** Defining whether or not the external event is memorized (latched)
    and generated as soon as the blanking period is completed or the window ends. **/
#define SHRTIM_EXEVLATCH_DISABLED    0x00000000U             /* Event is ignored if it happens during a blank, or passed through during a window */
#define SHRTIM_EXEVLATCH_ENABLED     SHRTIM_TXEXEVFLT1_EXEV1LATCH     /* Event is latched and delayed till the end of the blanking or windowing period */


/** Defining division ratio between the timer clock frequency (fSHRTIM) 
    and the deadtime generator clock (fDTG). **/
#define SHRTIM_DT_PRESCALER_MUL8    0x00000000U                                         /* fDTG = fSHRTIM * 8 */
#define SHRTIM_DT_PRESCALER_MUL4    (SHRTIM_TXDT_DTPSC_0)                                            /* fDTG = fSHRTIM * 4 */
#define SHRTIM_DT_PRESCALER_MUL2    (SHRTIM_TXDT_DTPSC_1)                                            /* fDTG = fSHRTIM * 2 */
#define SHRTIM_DT_PRESCALER_DIV1    (SHRTIM_TXDT_DTPSC_1 | SHRTIM_TXDT_DTPSC_0)                       /* fDTG = fSHRTIM */
#define SHRTIM_DT_PRESCALER_DIV2    (SHRTIM_TXDT_DTPSC_2)                                            /* fDTG = fSHRTIM / 2 */
#define SHRTIM_DT_PRESCALER_DIV4    (SHRTIM_TXDT_DTPSC_2 | SHRTIM_TXDT_DTPSC_0)                       /* fDTG = fSHRTIM / 4 */
#define SHRTIM_DT_PRESCALER_DIV8    (SHRTIM_TXDT_DTPSC_2 | SHRTIM_TXDT_DTPSC_1)                       /* fDTG = fSHRTIM / 8 */
#define SHRTIM_DT_PRESCALER_DIV16   (SHRTIM_TXDT_DTPSC_2 | SHRTIM_TXDT_DTPSC_1 | SHRTIM_TXDT_DTPSC_0)  /* fDTG = fSHRTIM / 16 */


/** Defining whether the deadtime is positive or negative (overlapping signal) on rising edge. **/
#define SHRTIM_DT_RISING_POSITIVE    0x00000000U             /* Positive deadtime on rising edge */
#define SHRTIM_DT_RISING_NEGATIVE    (SHRTIM_TXDT_SDTR)        /* Negative deadtime on rising edge */


/** Defining whether the deadtime is positive or negative (overlapping signal) on falling edge. **/
#define SHRTIM_DT_FALLING_POSITIVE    0x00000000U             /* Positive deadtime on falling edge */
#define SHRTIM_DT_FALLING_NEGATIVE    (SHRTIM_TXDT_SDTF)        /* Negative deadtime on falling edge */


/** Defining the frequency of the generated high frequency carrier (fCHPFRQ). **/
#define SHRTIM_CHP_PRESCALER_DIV16  0x00000000U                                                                     /* fCHPFRQ = fSHRTIM / 16  */
#define SHRTIM_CHP_PRESCALER_DIV32  (SHRTIM_TXCHOP_CARFRQ_0)                                                                    /* fCHPFRQ = fSHRTIM / 32  */
#define SHRTIM_CHP_PRESCALER_DIV48  (SHRTIM_TXCHOP_CARFRQ_1)                                                                    /* fCHPFRQ = fSHRTIM / 48  */
#define SHRTIM_CHP_PRESCALER_DIV64  (SHRTIM_TXCHOP_CARFRQ_1 | SHRTIM_TXCHOP_CARFRQ_0)                                              /* fCHPFRQ = fSHRTIM / 64  */
#define SHRTIM_CHP_PRESCALER_DIV80  (SHRTIM_TXCHOP_CARFRQ_2)                                                                    /* fCHPFRQ = fSHRTIM / 80  */
#define SHRTIM_CHP_PRESCALER_DIV96  (SHRTIM_TXCHOP_CARFRQ_2 | SHRTIM_TXCHOP_CARFRQ_0)                                              /* fCHPFRQ = fSHRTIM / 96  */
#define SHRTIM_CHP_PRESCALER_DIV112 (SHRTIM_TXCHOP_CARFRQ_2 | SHRTIM_TXCHOP_CARFRQ_1)                                              /* fCHPFRQ = fSHRTIM / 112  */
#define SHRTIM_CHP_PRESCALER_DIV128 (SHRTIM_TXCHOP_CARFRQ_2 | SHRTIM_TXCHOP_CARFRQ_1 | SHRTIM_TXCHOP_CARFRQ_0)                        /* fCHPFRQ = fSHRTIM / 128  */
#define SHRTIM_CHP_PRESCALER_DIV144 (SHRTIM_TXCHOP_CARFRQ_3)                                                                    /* fCHPFRQ = fSHRTIM / 144  */
#define SHRTIM_CHP_PRESCALER_DIV160 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_0)                                              /* fCHPFRQ = fSHRTIM / 160  */
#define SHRTIM_CHP_PRESCALER_DIV176 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_1)                                              /* fCHPFRQ = fSHRTIM / 176  */
#define SHRTIM_CHP_PRESCALER_DIV192 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_1 | SHRTIM_TXCHOP_CARFRQ_0)                        /* fCHPFRQ = fSHRTIM / 192  */
#define SHRTIM_CHP_PRESCALER_DIV208 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_2)                                              /* fCHPFRQ = fSHRTIM / 208  */
#define SHRTIM_CHP_PRESCALER_DIV224 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_2 | SHRTIM_TXCHOP_CARFRQ_0)                        /* fCHPFRQ = fSHRTIM / 224  */
#define SHRTIM_CHP_PRESCALER_DIV240 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_2 | SHRTIM_TXCHOP_CARFRQ_1)                        /* fCHPFRQ = fSHRTIM / 240  */
#define SHRTIM_CHP_PRESCALER_DIV256 (SHRTIM_TXCHOP_CARFRQ_3 | SHRTIM_TXCHOP_CARFRQ_2 | SHRTIM_TXCHOP_CARFRQ_1 | SHRTIM_TXCHOP_CARFRQ_0)  /* fCHPFRQ = fSHRTIM / 256  */


/** Defining the duty cycle of the generated high frequency carrier. 
    Duty cycle can be adjusted by 1/8 step (from 0/8 up to 7/8). **/
#define SHRTIM_CHP_DUTYCYCLE_0    0x00000000U                                              /* Only 1st pulse is present */
#define SHRTIM_CHP_DUTYCYCLE_125  (SHRTIM_TXCHOP_CARDCY_0)                                             /* Duty cycle of the carrier signal is 12.5 % */
#define SHRTIM_CHP_DUTYCYCLE_250  (SHRTIM_TXCHOP_CARDCY_1)                                             /* Duty cycle of the carrier signal is 25 % */
#define SHRTIM_CHP_DUTYCYCLE_375  (SHRTIM_TXCHOP_CARDCY_1 | SHRTIM_TXCHOP_CARDCY_0)                       /* Duty cycle of the carrier signal is 37.5 % */
#define SHRTIM_CHP_DUTYCYCLE_500  (SHRTIM_TXCHOP_CARDCY_2)                                             /* Duty cycle of the carrier signal is 50 % */
#define SHRTIM_CHP_DUTYCYCLE_625  (SHRTIM_TXCHOP_CARDCY_2 | SHRTIM_TXCHOP_CARDCY_0)                       /* Duty cycle of the carrier signal is 62.5 % */
#define SHRTIM_CHP_DUTYCYCLE_750  (SHRTIM_TXCHOP_CARDCY_2 | SHRTIM_TXCHOP_CARDCY_1)                       /* Duty cycle of the carrier signal is 75 % */
#define SHRTIM_CHP_DUTYCYCLE_875  (SHRTIM_TXCHOP_CARDCY_2 | SHRTIM_TXCHOP_CARDCY_1 | SHRTIM_TXCHOP_CARDCY_0) /* Duty cycle of the carrier signal is 87.5 % */


/** Defining the pulse width of the first pulse of the generated high frequency carrier. **/
#define SHRTIM_CHP_PULSEWIDTH_16   0x00000000U                                                                 /* tSTPW = tHRTIM x 16  */
#define SHRTIM_CHP_PULSEWIDTH_32   (SHRTIM_TXCHOP_STARTPW_0)                                                                 /* tSTPW = tHRTIM x 32  */
#define SHRTIM_CHP_PULSEWIDTH_48   (SHRTIM_TXCHOP_STARTPW_1)                                                                 /* tSTPW = tHRTIM x 48  */
#define SHRTIM_CHP_PULSEWIDTH_64   (SHRTIM_TXCHOP_STARTPW_1 | SHRTIM_TXCHOP_STARTPW_0)                                            /* tSTPW = tHRTIM x 64  */
#define SHRTIM_CHP_PULSEWIDTH_80   (SHRTIM_TXCHOP_STARTPW_2)                                                                 /* tSTPW = tHRTIM x 80  */
#define SHRTIM_CHP_PULSEWIDTH_96   (SHRTIM_TXCHOP_STARTPW_2 | SHRTIM_TXCHOP_STARTPW_0)                                            /* tSTPW = tHRTIM x 96  */
#define SHRTIM_CHP_PULSEWIDTH_112  (SHRTIM_TXCHOP_STARTPW_2 | SHRTIM_TXCHOP_STARTPW_1)                                            /* tSTPW = tHRTIM x 112  */
#define SHRTIM_CHP_PULSEWIDTH_128  (SHRTIM_TXCHOP_STARTPW_2 | SHRTIM_TXCHOP_STARTPW_1 | SHRTIM_TXCHOP_STARTPW_0)                       /* tSTPW = tHRTIM x 128  */
#define SHRTIM_CHP_PULSEWIDTH_144  (SHRTIM_TXCHOP_STARTPW_3)                                                                 /* tSTPW = tHRTIM x 144  */
#define SHRTIM_CHP_PULSEWIDTH_160  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_0)                                            /* tSTPW = tHRTIM x 160  */
#define SHRTIM_CHP_PULSEWIDTH_176  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_1)                                            /* tSTPW = tHRTIM x 176  */
#define SHRTIM_CHP_PULSEWIDTH_192  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_1 | SHRTIM_TXCHOP_STARTPW_0)                       /* tSTPW = tHRTIM x 192  */
#define SHRTIM_CHP_PULSEWIDTH_208  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_2)                                            /* tSTPW = tHRTIM x 208  */
#define SHRTIM_CHP_PULSEWIDTH_224  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_2 | SHRTIM_TXCHOP_STARTPW_0)                       /* tSTPW = tHRTIM x 224  */
#define SHRTIM_CHP_PULSEWIDTH_240  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_2 | SHRTIM_TXCHOP_STARTPW_1)                       /* tSTPW = tHRTIM x 240  */
#define SHRTIM_CHP_PULSEWIDTH_256  (SHRTIM_TXCHOP_STARTPW_3 | SHRTIM_TXCHOP_STARTPW_2 | SHRTIM_TXCHOP_STARTPW_1 | SHRTIM_TXCHOP_STARTPW_0)  /* tSTPW = tHRTIM x 256  */

/** Defining the events that can be selected to configure the set/reset crossbar of a timer output. **/
#define SHRTIM_OUTPUTSET_NONE                0x00000000U             /* Reset the output set crossbar */
#define SHRTIM_OUTPUTSET_RESYNC              (SHRTIM_TXSET1_RSYNC)    /* Timer reset event coming solely from software or SYNC input forces an output level transition */
#define SHRTIM_OUTPUTSET_TIMPER              (SHRTIM_TXSET1_PRD)       /* Timer period event forces an output level transition */
#define SHRTIM_OUTPUTSET_TIMCMP1             (SHRTIM_TXSET1_CMP1)      /* Timer compare 1 event forces an output level transition */
#define SHRTIM_OUTPUTSET_TIMCMP2             (SHRTIM_TXSET1_CMP2)      /* Timer compare 2 event forces an output level transition */
#define SHRTIM_OUTPUTSET_TIMCMP3             (SHRTIM_TXSET1_CMP3)      /* Timer compare 3 event forces an output level transition */
#define SHRTIM_OUTPUTSET_TIMCMP4             (SHRTIM_TXSET1_CMP4)      /* Timer compare 4 event forces an output level transition */
#define SHRTIM_OUTPUTSET_MASTERPER           (SHRTIM_TXSET1_MPRD)    /* The master timer period event forces an output level transition */
#define SHRTIM_OUTPUTSET_MASTERCMP1          (SHRTIM_TXSET1_MCMP1)   /* Master Timer compare 1 event forces an output level transition */
#define SHRTIM_OUTPUTSET_MASTERCMP2          (SHRTIM_TXSET1_MCMP2)   /* Master Timer compare 2 event forces an output level transition */
#define SHRTIM_OUTPUTSET_MASTERCMP3          (SHRTIM_TXSET1_MCMP3)   /* Master Timer compare 3 event forces an output level transition */
#define SHRTIM_OUTPUTSET_MASTERCMP4          (SHRTIM_TXSET1_MCMP4)   /* Master Timer compare 4 event forces an output level transition */
/* Timer Events mapping for Timer A */
#define SHRTIM_OUTPUTSET_TIMAEV1_TIMBCMP1    (SHRTIM_TXSET1_TIMEV1)  /* Timer event 1 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV2_TIMBCMP2    (SHRTIM_TXSET1_TIMEV2)  /* Timer event 2 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV3_TIMCCMP2    (SHRTIM_TXSET1_TIMEV3)  /* Timer event 3 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV4_TIMCCMP3    (SHRTIM_TXSET1_TIMEV4)  /* Timer event 4 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV5_TIMDCMP1    (SHRTIM_TXSET1_TIMEV5)  /* Timer event 5 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV6_TIMDCMP2    (SHRTIM_TXSET1_TIMEV6)  /* Timer event 6 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV7_TIMECMP3    (SHRTIM_TXSET1_TIMEV7)  /* Timer event 7 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV8_TIMECMP4    (SHRTIM_TXSET1_TIMEV8)  /* Timer event 8 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMAEV9_TIMFCMP4    (SHRTIM_TXSET1_TIMEV9)  /* Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer B */
#define SHRTIM_OUTPUTSET_TIMBEV1_TIMACMP1    (SHRTIM_TXSET1_TIMEV1)  /* Timer event 1 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV2_TIMACMP2    (SHRTIM_TXSET1_TIMEV2)  /* Timer event 2 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV3_TIMCCMP3    (SHRTIM_TXSET1_TIMEV3)  /* Timer event 3 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV4_TIMCCMP4    (SHRTIM_TXSET1_TIMEV4)  /* Timer event 4 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV5_TIMDCMP3    (SHRTIM_TXSET1_TIMEV5)  /* Timer event 5 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV6_TIMDCMP4    (SHRTIM_TXSET1_TIMEV6)  /* Timer event 6 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV7_TIMECMP1    (SHRTIM_TXSET1_TIMEV7)  /* Timer event 7 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV8_TIMECMP2    (SHRTIM_TXSET1_TIMEV8)  /* Timer event 8 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMBEV9_TIMFCMP3    (SHRTIM_TXSET1_TIMEV9)  /* Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer C */
#define SHRTIM_OUTPUTSET_TIMCEV1_TIMACMP2    (SHRTIM_TXSET1_TIMEV1)  /* Timer event 1 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV2_TIMACMP3    (SHRTIM_TXSET1_TIMEV2)  /* Timer event 2 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV3_TIMBCMP2    (SHRTIM_TXSET1_TIMEV3)  /* Timer event 3 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV4_TIMBCMP3    (SHRTIM_TXSET1_TIMEV4)  /* Timer event 4 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV5_TIMDCMP2    (SHRTIM_TXSET1_TIMEV5)  /* Timer event 5 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV6_TIMDCMP4    (SHRTIM_TXSET1_TIMEV6)  /* Timer event 6 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV7_TIMECMP3    (SHRTIM_TXSET1_TIMEV7)  /* Timer event 7 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV8_TIMECMP4    (SHRTIM_TXSET1_TIMEV8)  /* Timer event 8 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMCEV9_TIMFCMP2    (SHRTIM_TXSET1_TIMEV9)  /* Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer D */
#define SHRTIM_OUTPUTSET_TIMDEV1_TIMACMP1    (SHRTIM_TXSET1_TIMEV1)  /* Timer event 1 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV2_TIMACMP4    (SHRTIM_TXSET1_TIMEV2)  /* Timer event 2 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV3_TIMBCMP2    (SHRTIM_TXSET1_TIMEV3)  /* Timer event 3 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV4_TIMBCMP4    (SHRTIM_TXSET1_TIMEV4)  /* Timer event 4 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV5_TIMCCMP4    (SHRTIM_TXSET1_TIMEV5)  /* Timer event 5 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV6_TIMECMP1    (SHRTIM_TXSET1_TIMEV6)  /* Timer event 6 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV7_TIMECMP4    (SHRTIM_TXSET1_TIMEV7)  /* Timer event 7 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV8_TIMFCMP1    (SHRTIM_TXSET1_TIMEV8)  /* Timer event 8 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMDEV9_TIMFCMP3    (SHRTIM_TXSET1_TIMEV9)  /* Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer E */
#define SHRTIM_OUTPUTSET_TIMEEV1_TIMACMP4    (SHRTIM_TXSET1_TIMEV1)  /* Timer event 1 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV2_TIMBCMP3    (SHRTIM_TXSET1_TIMEV2)  /* Timer event 2 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV3_TIMBCMP4    (SHRTIM_TXSET1_TIMEV3)  /* Timer event 3 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV4_TIMCCMP1    (SHRTIM_TXSET1_TIMEV4)  /* Timer event 4 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV5_TIMCCMP2    (SHRTIM_TXSET1_TIMEV5)  /* Timer event 5 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV6_TIMDCMP1    (SHRTIM_TXSET1_TIMEV6)  /* Timer event 6 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV7_TIMDCMP2    (SHRTIM_TXSET1_TIMEV7)  /* Timer event 7 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV8_TIMFCMP3    (SHRTIM_TXSET1_TIMEV8)  /* Timer event 8 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMEEV9_TIMFCMP4    (SHRTIM_TXSET1_TIMEV9)  /* Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer F */
#define SHRTIM_OUTPUTSET_TIMFEV1_TIMACMP3    (SHRTIM_TXSET1_TIMEV1)  /* Timer event 1 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV2_TIMBCMP1    (SHRTIM_TXSET1_TIMEV2)  /* Timer event 2 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV3_TIMBCMP4    (SHRTIM_TXSET1_TIMEV3)  /* Timer event 3 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV4_TIMCCMP1    (SHRTIM_TXSET1_TIMEV4)  /* Timer event 4 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV5_TIMCCMP4    (SHRTIM_TXSET1_TIMEV5)  /* Timer event 5 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV6_TIMDCMP3    (SHRTIM_TXSET1_TIMEV6)  /* Timer event 6 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV7_TIMDCMP4    (SHRTIM_TXSET1_TIMEV7)  /* Timer event 7 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV8_TIMECMP2    (SHRTIM_TXSET1_TIMEV8)  /* Timer event 8 forces the output to its active state */
#define SHRTIM_OUTPUTSET_TIMFEV9_TIMECMP3    (SHRTIM_TXSET1_TIMEV9)  /* Timer event 9 forces the output to its active state */
#define SHRTIM_OUTPUTSET_EXEV_1               (SHRTIM_TXSET1_EXEV1)   /* External event 1 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_2               (SHRTIM_TXSET1_EXEV2)   /* External event 2 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_3               (SHRTIM_TXSET1_EXEV3)   /* External event 3 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_4               (SHRTIM_TXSET1_EXEV4)   /* External event 4 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_5               (SHRTIM_TXSET1_EXEV5)   /* External event 5 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_6               (SHRTIM_TXSET1_EXEV6)   /* External event 6 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_7               (SHRTIM_TXSET1_EXEV7)   /* External event 7 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_8               (SHRTIM_TXSET1_EXEV8)   /* External event 8 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_9               (SHRTIM_TXSET1_EXEV9)   /* External event 9 forces an output level transition */
#define SHRTIM_OUTPUTSET_EXEV_10              (SHRTIM_TXSET1_EXEV10)  /* External event 10 forces an output level transition */
#define SHRTIM_OUTPUTSET_UPDATE              (SHRTIM_TXSET1_UPD)    /* Timer register update event forces an output level transition */

/** Defining the events that can be selected to configure the set crossbar of a timer output **/
#define SHRTIM_OUTPUTRESET_NONE                0x00000000U             /* Reset the output reset crossbar */
#define SHRTIM_OUTPUTRESET_RESYNC              (SHRTIM_TXRST1_RSYNC)    /* Timer reset event coming solely from software or SYNC input forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMPER              (SHRTIM_TXRST1_PRD)       /* Timer period event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCMP1             (SHRTIM_TXRST1_CMP1)      /* Timer compare 1 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCMP2             (SHRTIM_TXRST1_CMP2)      /* Timer compare 2 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCMP3             (SHRTIM_TXRST1_CMP3)      /* Timer compare 3 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCMP4             (SHRTIM_TXRST1_CMP4)      /* Timer compare 4 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_MASTERPER           (SHRTIM_TXRST1_MPRD)    /* The master timer period event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_MASTERCMP1          (SHRTIM_TXRST1_MCMP1)   /* Master Timer compare 1 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_MASTERCMP2          (SHRTIM_TXRST1_MCMP2)   /* Master Timer compare 2 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_MASTERCMP3          (SHRTIM_TXRST1_MCMP3)   /* Master Timer compare 3 event forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_MASTERCMP4          (SHRTIM_TXRST1_MCMP4)   /* Master Timer compare 4 event forces the output to its inactive state */
/* Timer Events mapping for Timer A */
#define SHRTIM_OUTPUTRESET_TIMAEV1_TIMBCMP1    (SHRTIM_TXRST1_TIMEV1)  /* Timer event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV2_TIMBCMP2    (SHRTIM_TXRST1_TIMEV2)  /* Timer event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV3_TIMCCMP2    (SHRTIM_TXRST1_TIMEV3)  /* Timer event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV4_TIMCCMP3    (SHRTIM_TXRST1_TIMEV4)  /* Timer event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV5_TIMDCMP1    (SHRTIM_TXRST1_TIMEV5)  /* Timer event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV6_TIMDCMP2    (SHRTIM_TXRST1_TIMEV6)  /* Timer event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV7_TIMECMP3    (SHRTIM_TXRST1_TIMEV7)  /* Timer event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV8_TIMECMP4    (SHRTIM_TXRST1_TIMEV8)  /* Timer event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMAEV9_TIMFCMP4    (SHRTIM_TXRST1_TIMEV9)  /* Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer B */
#define SHRTIM_OUTPUTRESET_TIMBEV1_TIMACMP1    (SHRTIM_TXRST1_TIMEV1)  /* Timer event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV2_TIMACMP2    (SHRTIM_TXRST1_TIMEV2)  /* Timer event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV3_TIMCCMP3    (SHRTIM_TXRST1_TIMEV3)  /* Timer event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV4_TIMCCMP4    (SHRTIM_TXRST1_TIMEV4)  /* Timer event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV5_TIMDCMP3    (SHRTIM_TXRST1_TIMEV5)  /* Timer event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV6_TIMDCMP4    (SHRTIM_TXRST1_TIMEV6)  /* Timer event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV7_TIMECMP1    (SHRTIM_TXRST1_TIMEV7)  /* Timer event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV8_TIMECMP2    (SHRTIM_TXRST1_TIMEV8)  /* Timer event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMBEV9_TIMFCMP3    (SHRTIM_TXRST1_TIMEV9)  /* Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer C */
#define SHRTIM_OUTPUTRESET_TIMCEV1_TIMACMP2    (SHRTIM_TXRST1_TIMEV1)  /* Timer event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV2_TIMACMP3    (SHRTIM_TXRST1_TIMEV2)  /* Timer event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV3_TIMBCMP2    (SHRTIM_TXRST1_TIMEV3)  /* Timer event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV4_TIMBCMP3    (SHRTIM_TXRST1_TIMEV4)  /* Timer event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV5_TIMDCMP2    (SHRTIM_TXRST1_TIMEV5)  /* Timer event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV6_TIMDCMP4    (SHRTIM_TXRST1_TIMEV6)  /* Timer event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV7_TIMECMP3    (SHRTIM_TXRST1_TIMEV7)  /* Timer event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV8_TIMECMP4    (SHRTIM_TXRST1_TIMEV8)  /* Timer event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMCEV9_TIMFCMP2    (SHRTIM_TXRST1_TIMEV9)  /* Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer D */
#define SHRTIM_OUTPUTRESET_TIMDEV1_TIMACMP1    (SHRTIM_TXRST1_TIMEV1)  /* Timer event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV2_TIMACMP4    (SHRTIM_TXRST1_TIMEV2)  /* Timer event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV3_TIMBCMP2    (SHRTIM_TXRST1_TIMEV3)  /* Timer event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV4_TIMBCMP4    (SHRTIM_TXRST1_TIMEV4)  /* Timer event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV5_TIMCCMP4    (SHRTIM_TXRST1_TIMEV5)  /* Timer event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV6_TIMECMP1    (SHRTIM_TXRST1_TIMEV6)  /* Timer event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV7_TIMECMP4    (SHRTIM_TXRST1_TIMEV7)  /* Timer event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV8_TIMFCMP1    (SHRTIM_TXRST1_TIMEV8)  /* Timer event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMDEV9_TIMFCMP3    (SHRTIM_TXRST1_TIMEV9)  /* Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer E */
#define SHRTIM_OUTPUTRESET_TIMEEV1_TIMACMP4    (SHRTIM_TXRST1_TIMEV1)  /* Timer event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV2_TIMBCMP3    (SHRTIM_TXRST1_TIMEV2)  /* Timer event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV3_TIMBCMP4    (SHRTIM_TXRST1_TIMEV3)  /* Timer event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV4_TIMCCMP1    (SHRTIM_TXRST1_TIMEV4)  /* Timer event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV5_TIMCCMP2    (SHRTIM_TXRST1_TIMEV5)  /* Timer event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV6_TIMDCMP1    (SHRTIM_TXRST1_TIMEV6)  /* Timer event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV7_TIMDCMP2    (SHRTIM_TXRST1_TIMEV7)  /* Timer event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV8_TIMFCMP3    (SHRTIM_TXRST1_TIMEV8)  /* Timer event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMEEV9_TIMFCMP4    (SHRTIM_TXRST1_TIMEV9)  /* Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer F */
#define SHRTIM_OUTPUTRESET_TIMFEV1_TIMACMP3    (SHRTIM_TXRST1_TIMEV1)  /* Timer event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV2_TIMBCMP1    (SHRTIM_TXRST1_TIMEV2)  /* Timer event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV3_TIMBCMP4    (SHRTIM_TXRST1_TIMEV3)  /* Timer event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV4_TIMCCMP1    (SHRTIM_TXRST1_TIMEV4)  /* Timer event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV5_TIMCCMP4    (SHRTIM_TXRST1_TIMEV5)  /* Timer event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV6_TIMDCMP3    (SHRTIM_TXRST1_TIMEV6)  /* Timer event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV7_TIMDCMP4    (SHRTIM_TXRST1_TIMEV7)  /* Timer event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV8_TIMECMP2    (SHRTIM_TXRST1_TIMEV8)  /* Timer event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_TIMFEV9_TIMECMP3    (SHRTIM_TXRST1_TIMEV9)  /* Timer event 9 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_1              (SHRTIM_TXRST1_EXEV1)   /* External event 1 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_2              (SHRTIM_TXRST1_EXEV2)   /* External event 2 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_3              (SHRTIM_TXRST1_EXEV3)   /* External event 3 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_4              (SHRTIM_TXRST1_EXEV4)   /* External event 4 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_5              (SHRTIM_TXRST1_EXEV5)   /* External event 5 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_6              (SHRTIM_TXRST1_EXEV6)   /* External event 6 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_7              (SHRTIM_TXRST1_EXEV7)   /* External event 7 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_8              (SHRTIM_TXRST1_EXEV8)   /* External event 8 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_9              (SHRTIM_TXRST1_EXEV9)   /* External event 9 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_EXEV_10             (SHRTIM_TXRST1_EXEV10)  /* External event 10 forces the output to its inactive state */
#define SHRTIM_OUTPUTRESET_UPDATE              (SHRTIM_TXRST1_UPD)    /* Timer register update event forces the output to its inactive state */


/** Defining the polarity of a timer output. **/
#define SHRTIM_OUT_POSITIVE_POLARITY    0x00000000U             /* Output is active HIGH */
#define SHRTIM_OUT_NEGATIVE_POLARITY    (SHRTIM_TXOUT_POL1)       /* Output is active LOW */

/** Defining the interleaved mode of an SHRTIM Timer instance.
  */
#define SHRTIM_INTERLEAVED_MODE_DISABLED   0x000U              /* SHRTIM interleaved Mode is disabled */
#define SHRTIM_INTERLEAVED_MODE_DUAL       SHRTIM_MCTRL_HLF      /* SHRTIM interleaved Mode is Dual */
#define SHRTIM_INTERLEAVED_MODE_TRIPLE     SHRTIM_MCTRL_ILV_0  /* SHRTIM interleaved Mode is Triple */
#define SHRTIM_INTERLEAVED_MODE_QUAD       SHRTIM_MCTRL_ILV_1  /* SHRTIM interleaved Mode is Quad */

/** Defining the half mode of an SHRTIM Timer instance. **/
#define SHRTIM_HALF_MODE_DISABLED          0x000U              /* SHRTIM Half Mode is disabled */
#define SHRTIM_HALF_MODE_ENABLE            SHRTIM_MCTRL_HLF      /* SHRTIM Half Mode is Half */

/** Defining the output level when output is in IDLE state **/
#define SHRTIM_OUT_IDLELEVEL_INACTIVE   0x00000000U           /* Output at inactive level when in IDLE state */
#define SHRTIM_OUT_IDLELEVEL_ACTIVE     (SHRTIM_TXOUT_IDLES1)   /* Output at active level when in IDLE state */


/** Defining the output level when output is in FAULT state. **/
#define SHRTIM_OUT_FAULTSTATE_NO_ACTION 0x00000000U                      /* The output is not affected by the fault input */
#define SHRTIM_OUT_FAULTSTATE_ACTIVE    (SHRTIM_TXOUT_FALT1_0)                        /* Output at active level when in FAULT state */
#define SHRTIM_OUT_FAULTSTATE_INACTIVE  (SHRTIM_TXOUT_FALT1_1)                        /* Output at inactive level when in FAULT state */
#define SHRTIM_OUT_FAULTSTATE_HIGHZ     (SHRTIM_TXOUT_FALT1_1 | SHRTIM_TXOUT_FALT1_0)  /* Output is tri-stated when in FAULT state */

/** Defining whether or not chopper mode is enabled for a timer output. **/
#define SHRTIM_OUT_CHOPPERMODE_DISABLED   0x00000000U             /* Output signal is not altered  */
#define SHRTIM_OUT_CHOPPERMODE_ENABLED    (SHRTIM_TXOUT_CHP1)       /* Output signal is chopped by a carrier signal  */

/** Defining the idle state entry mode during a burst mode operation. 
    It is possible to delay the burst mode entry and force the output to an inactive state
    during a programmable period before the output takes its idle state. **/
#define SHRTIM_OUT_BM_ENTRYMODE_REGULAR   0x00000000U            /* The programmed Idle state is applied immediately to the Output */
#define SHRTIM_OUT_BM_ENTRYMODE_DELAYED   (SHRTIM_TXOUT_DIDL1)     /* Deadtime is inserted on output before entering the idle mode */

/** Defining the level of a timer output.
  */
#define SHRTIM_OUT_LEVEL_INACTIVE   0x00000000U            /* Corresponds to a logic level 0 for a positive polarity (High) and to a logic level 1 for a negative polarity (Low) */
#define SHRTIM_OUT_LEVEL_ACTIVE     ((uint32_t)0x00000001) /* Corresponds to a logic level 1 for a positive polarity (High) and to a logic level 0 for a negative polarity (Low) */


/** Defining available sources associated to external events. **/
#define SHRTIM_EXEV1SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 1 */
#define SHRTIM_EXEV2SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 2 */
#define SHRTIM_EXEV3SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 3 */
#define SHRTIM_EXEV4SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 4 */
#define SHRTIM_EXEV5SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 5 */
#define SHRTIM_EXEV6SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 6 */
#define SHRTIM_EXEV7SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 7 */
#define SHRTIM_EXEV8SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 8 */
#define SHRTIM_EXEV9SRC_GPIO        0x00000000U                                   /* External event source 1 for External Event 9 */
#define SHRTIM_EXEV10SRC_GPIO       0x00000000U                                   /* External event source 1 for External Event 10 */
#define SHRTIM_EXEV1SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 1 */
#define SHRTIM_EXEV2SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 2 */
#define SHRTIM_EXEV3SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 3 */
#define SHRTIM_EXEV4SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 4 */
#define SHRTIM_EXEV5SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 5 */
#define SHRTIM_EXEV6SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 6 */
#define SHRTIM_EXEV7SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 7 */
#define SHRTIM_EXEV8SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 8 */
#define SHRTIM_EXEV9SRC_COMPx_OUT       (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 9 */
#define SHRTIM_EXEV10SRC_COMPx_OUT      (SHRTIM_EXEVCTRL1_EXEV1SRC_0)                        /* External event source 2 for External Event 10 */
#define SHRTIM_EXEV1SRC_ATIM1_TRGO      (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 1 */
#define SHRTIM_EXEV2SRC_GTIMA1_TRGO     (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 2 */
#define SHRTIM_EXEV3SRC_GTIMA2_TRGO     (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 3 */
#define SHRTIM_EXEV4SRC_ATIM2_TRGO      (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 4 */
#define SHRTIM_EXEV5SRC_ATIM3_TRGO      (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 5 */
#define SHRTIM_EXEV6SRC_ATIM4_TRGO      (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 6 */
#define SHRTIM_EXEV7SRC_GTIMA6_TRGO     (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 7 */
#define SHRTIM_EXEV8SRC_GTIMA4_TRGO     (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 8 */
#define SHRTIM_EXEV9SRC_GTIMA7_TRGO     (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 9 */
#define SHRTIM_EXEV10SRC_GTIMA5_TRGO    (SHRTIM_EXEVCTRL1_EXEV1SRC_1)                        /* External event source 3 for External Event 10 */
#define SHRTIM_EXEV1SRC_ADC1_AWD1       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 1 */
#define SHRTIM_EXEV2SRC_ADC1_AWD2       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 2 */
#define SHRTIM_EXEV3SRC_ADC1_AWD3       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 3 */
#define SHRTIM_EXEV4SRC_ADC2_AWD1       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 4 */
#define SHRTIM_EXEV5SRC_ADC2_AWD2       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 5 */
#define SHRTIM_EXEV6SRC_ADC2_AWD3       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 6 */
#define SHRTIM_EXEV7SRC_ADC3_AWD1       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 7 */
#define SHRTIM_EXEV8SRC_ADC3_AWD2       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 8 */
#define SHRTIM_EXEV9SRC_GTIMA3_TRGO     (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 9 */
#define SHRTIM_EXEV10SRC_ADC3_AWD3      (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_0) /* External event source 4 for External Event 10 */
#define SHRTIM1_EXEV1SRC_CAN2_RTP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 1 */
#define SHRTIM1_EXEV2SRC_CAN2_TMP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 2 */
#define SHRTIM1_EXEV3SRC_CAN2_SOC       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 3 */
#define SHRTIM1_EXEV4SRC_CAN1_RTP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 4 */
#define SHRTIM1_EXEV5SRC_CAN1_TMP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 5 */
#define SHRTIM1_EXEV6SRC_CAN1_SOC       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 6 */
#define SHRTIM2_EXEV1SRC_CAN4_RTP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 1 */
#define SHRTIM2_EXEV2SRC_CAN4_TMP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 2 */
#define SHRTIM2_EXEV3SRC_CAN4_SOC       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 3 */
#define SHRTIM2_EXEV4SRC_CAN3_RTP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 4 */
#define SHRTIM2_EXEV5SRC_CAN3_TMP       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 5 */
#define SHRTIM2_EXEV6SRC_CAN3_SOC       (SHRTIM_EXEVCTRL1_EXEV1SRC_1 | SHRTIM_EXEVCTRL1_EXEV1SRC_1) /* External event source 4 for External Event 6 */


/** Select the analog comparator of external event source 2 **/
#define SHRTIM_EXEVXSRC2_COMP1_OUT   0x00000000U                            /*  Compx is comp1 out*/
#define SHRTIM_EXEVXSRC2_COMP2_OUT  (SHRTIM_EXEVCTRL5_EXEV1CSEL_0)                      /*  Compx is comp2 out */
#define SHRTIM_EXEVXSRC2_COMP3_OUT  (SHRTIM_EXEVCTRL5_EXEV1CSEL_1)                      /*  Compx is comp3 out */
#define SHRTIM_EXEVXSRC2_COMP4_OUT  (SHRTIM_EXEVCTRL5_EXEV1CSEL_1 | SHRTIM_EXEVCTRL5_EXEV1CSEL_0) /*  Compx is comp4 out */
#define SHRTIM_EXEVXSRC2_COMP5_OUT  (SHRTIM_EXEVCTRL5_EXEV1CSEL_2)                      /*  Compx is comp5 out */
#define SHRTIM_EXEVXSRC2_COMP6_OUT  (SHRTIM_EXEVCTRL5_EXEV1CSEL_2 | SHRTIM_EXEVCTRL5_EXEV1CSEL_0) /*  Compx is comp6 out */
#define SHRTIM_EXEVXSRC2_COMP7_OUT  (SHRTIM_EXEVCTRL5_EXEV1CSEL_2 | SHRTIM_EXEVCTRL5_EXEV1CSEL_1) /*  Compx is comp7 out */
#define SHRTIM_EXEVXSRC2_COMP_NONE  (SHRTIM_EXEVCTRL5_EXEV1CSEL_2 | SHRTIM_EXEVCTRL5_EXEV1CSEL_1 | SHRTIM_EXEVCTRL5_EXEV1CSEL_0) /*  No comparator */

/** Defining the polarity of an external event. **/
#define SHRTIM_EXEV_POLARITY_HIGH    0x00000000U             /* External event is active high */
#define SHRTIM_EXEV_POLARITY_LOW     (SHRTIM_EXEVCTRL1_EXEV1POL)    /* External event is active low */


/** Defining the sensitivity (level-sensitive or edge-sensitive) of an external event. **/
#define SHRTIM_EXEV_SENSITIVITY_LEVEL          0x00000000U                        /* External event is active on level */
#define SHRTIM_EXEV_SENSITIVITY_RISINGEDGE     (SHRTIM_EXEVCTRL1_EXEV1SENS_0)                         /* External event is active on Rising edge */
#define SHRTIM_EXEV_SENSITIVITY_FALLINGEDGE    (SHRTIM_EXEVCTRL1_EXEV1SENS_1)                         /* External event is active on Falling edge */
#define SHRTIM_EXEV_SENSITIVITY_BOTHEDGES      (SHRTIM_EXEVCTRL1_EXEV1SENS_1 | SHRTIM_EXEVCTRL1_EXEV1SENS_0)  /* External event is active on Rising and Falling edges */


/** Defining whether or not an external event is programmed in fast mode. **/
#define SHRTIM_EXEV_FASTMODE_DISABLE         0x00000000U              /* External Event is re-synchronized by the SHRTIM logic before acting on outputs */
#define SHRTIM_EXEV_FASTMODE_ENABLE          (SHRTIM_EXEVCTRL3_EXEV1FM)    /* External Event is acting asynchronously on outputs (low latency mode) */


/** Defining the frequency used to sample an external event input (fSAMPLING)
    and the length (N) of the digital filter applied. **/
#define SHRTIM_EXEV_FILTER_NONE      0x00000000U                                                               /* Filter disabled */
#define SHRTIM_EXEV_FILTER_1         (SHRTIM_EXEVCTRL3_EXEV1F_0)                                                                  /* fSAMPLING = fSHRTIM, N=2 */
#define SHRTIM_EXEV_FILTER_2         (SHRTIM_EXEVCTRL3_EXEV1F_1)                                                                  /* fSAMPLING = fSHRTIM, N=4 */
#define SHRTIM_EXEV_FILTER_3         (SHRTIM_EXEVCTRL3_EXEV1F_1 | SHRTIM_EXEVCTRL3_EXEV1F_0)                                             /* fSAMPLING = fSHRTIM, N=8 */
#define SHRTIM_EXEV_FILTER_4         (SHRTIM_EXEVCTRL3_EXEV1F_2)                                                                  /* fSAMPLING = fEXEVS/2, N=6 */
#define SHRTIM_EXEV_FILTER_5         (SHRTIM_EXEVCTRL3_EXEV1F_2 | SHRTIM_EXEVCTRL3_EXEV1F_0)                                             /* fSAMPLING = fEXEVS/2, N=8 */
#define SHRTIM_EXEV_FILTER_6         (SHRTIM_EXEVCTRL3_EXEV1F_2 | SHRTIM_EXEVCTRL3_EXEV1F_1)                                             /* fSAMPLING = fEXEVS/4, N=6 */
#define SHRTIM_EXEV_FILTER_7         (SHRTIM_EXEVCTRL3_EXEV1F_2 | SHRTIM_EXEVCTRL3_EXEV1F_1 | SHRTIM_EXEVCTRL3_EXEV1F_0)                        /* fSAMPLING = fEXEVS/4, N=8 */
#define SHRTIM_EXEV_FILTER_8         (SHRTIM_EXEVCTRL3_EXEV1F_3)                                                                  /* fSAMPLING = fEXEVS/8, N=6 */
#define SHRTIM_EXEV_FILTER_9         (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_0)                                             /* fSAMPLING = fEXEVS/8, N=8 */
#define SHRTIM_EXEV_FILTER_10        (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_1)                                             /* fSAMPLING = fEXEVS/16, N=5 */
#define SHRTIM_EXEV_FILTER_11        (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_1 | SHRTIM_EXEVCTRL3_EXEV1F_0)                        /* fSAMPLING = fEXEVS/16, N=6 */
#define SHRTIM_EXEV_FILTER_12        (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_2)                                             /* fSAMPLING = fEXEVS/16, N=8 */
#define SHRTIM_EXEV_FILTER_13        (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_2  | SHRTIM_EXEVCTRL3_EXEV1F_0)                       /* fSAMPLING = fEXEVS/32, N=5 */
#define SHRTIM_EXEV_FILTER_14        (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_2  | SHRTIM_EXEVCTRL3_EXEV1F_1)                       /* fSAMPLING = fEXEVS/32, N=6 */
#define SHRTIM_EXEV_FILTER_15        (SHRTIM_EXEVCTRL3_EXEV1F_3 | SHRTIM_EXEVCTRL3_EXEV1F_2  | SHRTIM_EXEVCTRL3_EXEV1F_1 | SHRTIM_EXEVCTRL3_EXEV1F_0)  /* fSAMPLING = fEXEVS/32, N=8 */


/** Defining division ratio between the timer clock frequency (fSHRTIM) and the external event signal sampling clock (fEXEVS) used by the digital filters.
  */
#define SHRTIM_EXEV_PRESCALER_DIV1    0x00000000U                     /* fEXEVS = fSHRTIM */
#define SHRTIM_EXEV_PRESCALER_DIV2    (SHRTIM_EXEVCTRL4_EXEVSCD_0)                       /* fEXEVS = fSHRTIM / 2 */
#define SHRTIM_EXEV_PRESCALER_DIV4    (SHRTIM_EXEVCTRL4_EXEVSCD_1)                       /* fEXEVS = fSHRTIM / 4 */
#define SHRTIM_EXEV_PRESCALER_DIV8    (SHRTIM_EXEVCTRL4_EXEVSCD_1 | SHRTIM_EXEVCTRL4_EXEVSCD_0) /* fEXEVS = fSHRTIM / 8 */


/** Defining the external event counter. **/
#define SHRTIM_EXEV_COUNTER_A    ((uint32_t)0U)                     /* External Event A Counter */
#define SHRTIM_EXEV_COUNTER_B    ((uint32_t)16U)                    /* External Event B Counter */


/** Defining the external event reset mode. **/
#define SHRTIM_EXEV_COUNTER_RSTMODE_UNCONDITIONAL   ((uint32_t)0U)                     /* External Event counter is reset on each reset / roll-over event */
#define SHRTIM_EXEV_COUNTER_RSTMODE_CONDITIONAL     ((uint32_t)SHRTIM_TXEXEVFLT3_EXEVRSTM)   /* External Event counter is reset on each reset / roll-over event only if no event occurs during last counting period */


/** Defining whether a faults is be triggered by any external or internal fault source. **/
#define SHRTIM_FALT_SRC_DIGITALINPUT         0x00000000U                                        /* Fault source 1, Fault input is FLT input pin */
#define SHRTIM_FALT_SRC_INTERNAL             SHRTIM_FALTIN1_FALT1SRC0                           /* Fault source 2, Fault input is FLT_Int signal (e.g. internal comparator) */
#define SHRTIM_FALT_SRC_EXEVINPUT            SHRTIM_FALTIN2_FALT1SRC1                           /* Fault source 3, Fault input is external event  pin */
#define SHRTIM_FALT_SRC_DSMU                 SHRTIM_FALTIN2_FALT1SRC1 | SHRTIM_FALTIN2_FALT1SRC0/* Fault source 4, Fault input is DSMU */ 

/** Select the analog comparator of fault source 2. **/
/** Select the analog comparator of external event source **/
#define SHRTIM_FALTXSRC2_COMP1_OUT   0x00000000U                            /*  Compx is comp1 out*/
#define SHRTIM_FALTXSRC2_COMP2_OUT  (SHRTIM_FALTIN5_FALT1CSEL_0)                      /*  Compx is comp2 out */
#define SHRTIM_FALTXSRC2_COMP3_OUT  (SHRTIM_FALTIN5_FALT1CSEL_1)                      /*  Compx is comp3 out */
#define SHRTIM_FALTXSRC2_COMP4_OUT  (SHRTIM_FALTIN5_FALT1CSEL_1 | SHRTIM_FALTIN5_FALT1CSEL_0) /*  Compx is comp4 out */
#define SHRTIM_FALTXSRC2_COMP5_OUT  (SHRTIM_FALTIN5_FALT1CSEL_2)                      /*  Compx is comp5 out */
#define SHRTIM_FALTXSRC2_COMP6_OUT  (SHRTIM_FALTIN5_FALT1CSEL_2 | SHRTIM_FALTIN5_FALT1CSEL_0) /*  Compx is comp6 out */
#define SHRTIM_FALTXSRC2_COMP7_OUT  (SHRTIM_FALTIN5_FALT1CSEL_2 | SHRTIM_FALTIN5_FALT1CSEL_1) /*  Compx is comp7 out */
#define SHRTIM_FALTXSRC2_COMP_NONE  (SHRTIM_FALTIN5_FALT1CSEL_2 | SHRTIM_FALTIN5_FALT1CSEL_1 | SHRTIM_FALTIN5_FALT1CSEL_0) /*  No comparator */

/** Defining the polarity of a fault event. **/
#define SHRTIM_FALT_POLARITY_LOW     0x00000000U                /* Fault input is active low */
#define SHRTIM_FALT_POLARITY_HIGH    (SHRTIM_FALTIN1_FALT1POL)      /* Fault input is active high */


/** Defining the frequency used to sample the fault input (fSAMPLING) and the 
    length (N) of the digital filter applied. **/
#define SHRTIM_FALT_FILTER_NONE      0x00000000U                                                                          /* Filter disabled */
#define SHRTIM_FALT_FILTER_1         (SHRTIM_FALTIN1_FALT1FLT_0)                                                                          /* fSAMPLING= fSHRTIM, N=2 */
#define SHRTIM_FALT_FILTER_2         (SHRTIM_FALTIN1_FALT1FLT_1)                                                                          /* fSAMPLING= fSHRTIM, N=4 */
#define SHRTIM_FALT_FILTER_3         (SHRTIM_FALTIN1_FALT1FLT_1 | SHRTIM_FALTIN1_FALT1FLT_0)                                                  /* fSAMPLING= fSHRTIM, N=8 */
#define SHRTIM_FALT_FILTER_4         (SHRTIM_FALTIN1_FALT1FLT_2)                                                                          /* fSAMPLING= fFALTS/2, N=6 */
#define SHRTIM_FALT_FILTER_5         (SHRTIM_FALTIN1_FALT1FLT_2 | SHRTIM_FALTIN1_FALT1FLT_0)                                                  /* fSAMPLING= fFALTS/2, N=8 */
#define SHRTIM_FALT_FILTER_6         (SHRTIM_FALTIN1_FALT1FLT_2 | SHRTIM_FALTIN1_FALT1FLT_1)                                                  /* fSAMPLING= fFALTS/4, N=6 */
#define SHRTIM_FALT_FILTER_7         (SHRTIM_FALTIN1_FALT1FLT_2 | SHRTIM_FALTIN1_FALT1FLT_1 | SHRTIM_FALTIN1_FALT1FLT_0)                          /* fSAMPLING= fFALTS/4, N=8 */
#define SHRTIM_FALT_FILTER_8         (SHRTIM_FALTIN1_FALT1FLT_3)                                                                          /* fSAMPLING= fFALTS/8, N=6 */
#define SHRTIM_FALT_FILTER_9         (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_0)                                                  /* fSAMPLING= fFALTS/8, N=8 */
#define SHRTIM_FALT_FILTER_10        (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_1)                                                  /* fSAMPLING= fFALTS/16, N=5 */
#define SHRTIM_FALT_FILTER_11        (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_1 | SHRTIM_FALTIN1_FALT1FLT_0)                          /* fSAMPLING= fFALTS/16, N=6 */
#define SHRTIM_FALT_FILTER_12        (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_2)                                                  /* fSAMPLING= fFALTS/16, N=8 */
#define SHRTIM_FALT_FILTER_13        (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_2 | SHRTIM_FALTIN1_FALT1FLT_0)                          /* fSAMPLING= fFALTS/32, N=5 */
#define SHRTIM_FALT_FILTER_14        (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_2 | SHRTIM_FALTIN1_FALT1FLT_1)                          /* fSAMPLING= fFALTS/32, N=6 */
#define SHRTIM_FALT_FILTER_15        (SHRTIM_FALTIN1_FALT1FLT_3 | SHRTIM_FALTIN1_FALT1FLT_2 | SHRTIM_FALTIN1_FALT1FLT_1 | SHRTIM_FALTIN1_FALT1FLT_0)  /* fSAMPLING= fFALTS/32, N=8 */


/** Defining the division ratio between the timer clock frequency (fSHRTIM) and the fault signal sampling clock (fFALTS) used  by the digital filters. **/
#define SHRTIM_FALT_PRESCALER_DIV1    0x00000000U                                     /* fFALTS = fSHRTIM */
#define SHRTIM_FALT_PRESCALER_DIV2    (SHRTIM_FALTIN2_FALTSCD_0)                         /* fFALTS = fSHRTIM / 2 */
#define SHRTIM_FALT_PRESCALER_DIV4    (SHRTIM_FALTIN2_FALTSCD_1)                         /* fFALTS = fSHRTIM / 4 */
#define SHRTIM_FALT_PRESCALER_DIV8    (SHRTIM_FALTIN2_FALTSCD_1 | SHRTIM_FALTIN2_FALTSCD_0) /* fFALTS = fSHRTIM / 8 */

/** Defining the Blanking Source of a fault event. **/
#define SHRTIM_FALT_BLANKING_RSTALIGNED            0x00000000U                /* Fault blanking source is Reset-aligned  */
#define SHRTIM_FALT_BLANKING_MOVING                (SHRTIM_FALTIN3_FALT1BLKS)   /* Fault blanking source is Moving window */

#define SHRTIM_SYSTEM_FAULT_SHRPLLLOCKFAULT        SHRTIM_FALTIN2_SFALTSPLLEN   /* The flash ECC double detection error as SHRTIM system fault input enable */
#define SHRTIM_SYSTEM_FAULT_PVD                    SHRTIM_FALTIN2_SFALTPVDEN   /* The PVD error as SHRTIM system fault input enable */
#define SHRTIM_SYSTEM_FAULT_LOCKUP                 SHRTIM_FALTIN2_SFALTLOCKUPEN    /* The core lockup as SHRTIM system fault input enable */
#define SHRTIM_SYSTEM_FAULT_SRAMPARITY             SHRTIM_FALTIN2_SFALTSMPAREN   /* The sram parity error as SHRTIM system fault input enable */
#define SHRTIM_SYSTEM_FAULT_SRAMECC                SHRTIM_FALTIN2_SFALTSMECCEN   /* The sram ECC error as SHRTIM system fault input enable */
#define SHRTIM_SYSTEM_FAULT_CLOCKSECURITY          SHRTIM_FALTIN2_SFALTCKSECEN   /* The clock security system error as SHRTIM system fault input enable */

/** Defining the Counter Reset Mode of a fault event. **/
#define SHRTIM_FALT_COUNTERRST_UNCONDITIONAL    0x00000000U                    /* Fault counter is reset on each reset / roll-over event */
#define SHRTIM_FALT_COUNTERRST_CONDITIONAL      (SHRTIM_FALTIN3_FALT1RSTM)     /* Fault counter is reset on each reset / roll-over event only if no fault occurred during last counting period. */


/** Defining if the burst mode is entered once or if it is continuously operating. **/
#define SHRTIM_BM_MODE_SINGLESHOT  0x00000000U            /* Burst mode operates in single shot mode */
#define SHRTIM_BM_MODE_CONTINOUS   (SHRTIM_BMCTRL_BMOM)      /* Burst mode operates in continuous mode */


/** Defining the clock source for the burst mode counter. **/
#define SHRTIM_BM_CLKSRC_MASTER       0x00000000U                                                         /* Master timer counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_TIMER_A      (SHRTIM_BMCTRL_BMCK_0)                                              /* Timer A counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_TIMER_B      (SHRTIM_BMCTRL_BMCK_1)                                              /* Timer B counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_TIMER_C      (SHRTIM_BMCTRL_BMCK_1 | SHRTIM_BMCTRL_BMCK_0)                       /* Timer C counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_TIMER_D      (SHRTIM_BMCTRL_BMCK_2)                                              /* Timer D counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_TIMER_E      (SHRTIM_BMCTRL_BMCK_2 | SHRTIM_BMCTRL_BMCK_0)                       /* Timer E counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_TIMER_F      (SHRTIM_BMCTRL_BMCK_3 | SHRTIM_BMCTRL_BMCK_1 | SHRTIM_BMCTRL_BMCK_0)/* Timer F counter reset/roll-over is used as clock source for the burst mode counter */
#define SHRTIM_BM_CLKSRC_GTIMB1_OC1   (SHRTIM_BMCTRL_BMCK_2 | SHRTIM_BMCTRL_BMCK_1)                       /* On-chip Event 1 (BMClk[1]), acting as a burst mode counter clock */
#define SHRTIM_BM_CLKSRC_GTIMB2_OC1   (SHRTIM_BMCTRL_BMCK_2 | SHRTIM_BMCTRL_BMCK_1 | SHRTIM_BMCTRL_BMCK_0)/* On-chip Event 2 (BMClk[2]), acting as a burst mode counter clock */
#define SHRTIM_BM_CLKSRC_GTIMB3_OC1   (SHRTIM_BMCTRL_BMCK_3)                                              /* On-chip Event 3 (BMClk[3]), acting as a burst mode counter clock */
#define SHRTIM_BM_CLKSRC_BTIM1_TRGO   (SHRTIM_BMCTRL_BMCK_3 | SHRTIM_BMCTRL_BMCK_0)                       /* On-chip Event 4 (BMClk[4]), acting as a burst mode counter clock */
#define SHRTIM_BM_CLKSRC_FSHRTIM      (SHRTIM_BMCTRL_BMCK_3 | SHRTIM_BMCTRL_BMCK_1)                       /* Prescaled fSHRTIM clock is used as clock source for the burst mode counter */


/** Defining the prescaling ratio of the fSHRTIM clock for the burst mode controller (fBRST). **/
#define SHRTIM_BM_PRESCALER_DIV1        0x00000000U                                                                                    /* fBRST = 1*/
#define SHRTIM_BM_PRESCALER_DIV2        (SHRTIM_BMCTRL_BMPSC_0)                                                                        /* fBRST = fSHRTIM/2*/
#define SHRTIM_BM_PRESCALER_DIV4        (SHRTIM_BMCTRL_BMPSC_1)                                                                        /* fBRST = fSHRTIM/4*/
#define SHRTIM_BM_PRESCALER_DIV8        (SHRTIM_BMCTRL_BMPSC_1 | SHRTIM_BMCTRL_BMPSC_0)                                                /* fBRST = fSHRTIM/8*/
#define SHRTIM_BM_PRESCALER_DIV16       (SHRTIM_BMCTRL_BMPSC_2)                                                                        /* fBRST = fSHRTIM/16*/
#define SHRTIM_BM_PRESCALER_DIV32       (SHRTIM_BMCTRL_BMPSC_2 | SHRTIM_BMCTRL_BMPSC_0)                                                /* fBRST = fSHRTIM/32*/
#define SHRTIM_BM_PRESCALER_DIV64       (SHRTIM_BMCTRL_BMPSC_2 | SHRTIM_BMCTRL_BMPSC_1)                                                /* fBRST = fSHRTIM/64*/
#define SHRTIM_BM_PRESCALER_DIV128      (SHRTIM_BMCTRL_BMPSC_2 | SHRTIM_BMCTRL_BMPSC_1 | SHRTIM_BMCTRL_BMPSC_0)                        /* fBRST = fSHRTIM/128*/
#define SHRTIM_BM_PRESCALER_DIV256      (SHRTIM_BMCTRL_BMPSC_3)                                                                        /* fBRST = fSHRTIM/256*/
#define SHRTIM_BM_PRESCALER_DIV512      (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_0)                                                /* fBRST = fSHRTIM/512*/
#define SHRTIM_BM_PRESCALER_DIV1024     (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_1)                                                /* fBRST = fSHRTIM/1024*/
#define SHRTIM_BM_PRESCALER_DIV2048     (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_1 | SHRTIM_BMCTRL_BMPSC_0)                        /* fBRST = fSHRTIM/2048*/
#define SHRTIM_BM_PRESCALER_DIV4096     (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_2)                                                /* fBRST = fSHRTIM/4096*/
#define SHRTIM_BM_PRESCALER_DIV8192     (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_2 | SHRTIM_BMCTRL_BMPSC_0)                        /* fBRST = fSHRTIM/8192*/
#define SHRTIM_BM_PRESCALER_DIV16384    (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_2 | SHRTIM_BMCTRL_BMPSC_1)                        /* fBRST = fSHRTIM/16384*/
#define SHRTIM_BM_PRESCALER_DIV32768    (SHRTIM_BMCTRL_BMPSC_3 | SHRTIM_BMCTRL_BMPSC_2 | SHRTIM_BMCTRL_BMPSC_1 | SHRTIM_BMCTRL_BMPSC_0)/* fBRST = fSHRTIM/32768*/


/** Defining the events that can be used to trig the burst mode operation. **/
#define SHRTIM_BM_TRIG_NONE               0x00000000U             /*  No trigger */
#define SHRTIM_BM_TRIG_MASTER_RESET       (SHRTIM_BMTG_MRSTRO)   /*  Master timer reset event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_MASTER_REPETITION  (SHRTIM_BMTG_MREPT)   /*  Master timer repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_MASTER_CMP1        (SHRTIM_BMTG_MCMP1)  /*  Master timer compare 1 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_MASTER_CMP2        (SHRTIM_BMTG_MCMP2)  /*  Master timer compare 2 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_MASTER_CMP3        (SHRTIM_BMTG_MCMP3)  /*  Master timer compare 3 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_MASTER_CMP4        (SHRTIM_BMTG_MCMP4)  /*  Master timer compare 4 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMA_RESET         (SHRTIM_BMTG_TARSTRO)    /* Timer A reset event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMA_REPETITION    (SHRTIM_BMTG_TAREPT)    /* Timer A repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMA_CMP1          (SHRTIM_BMTG_TACMP1)   /* Timer A compare 1 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMA_CMP2          (SHRTIM_BMTG_TACMP2)   /* Timer A compare 2 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMB_RESET         (SHRTIM_BMTG_TBRSTRO)    /* Timer B reset event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMB_REPETITION    (SHRTIM_BMTG_TBREPT)    /* Timer B repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMB_CMP1          (SHRTIM_BMTG_TBCMP1)   /* Timer B compare 1 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMB_CMP2          (SHRTIM_BMTG_TBCMP2)   /* Timer B compare 2 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMC_RESET         (SHRTIM_BMTG_TCRSTRO)    /* Timer C resetevent is starting the burst mode operation  */
#define SHRTIM_BM_TRIG_TIMC_REPETITION    (SHRTIM_BMTG_TCREPT)    /* Timer C repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMC_CMP1          (SHRTIM_BMTG_TCCMP1)   /* Timer C compare 1 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMD_RESET         (SHRTIM_BMTG_TDRSTRO)    /* Timer D reset event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMD_REPETITION    (SHRTIM_BMTG_TDREPT)    /* Timer D repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMD_CMP2          (SHRTIM_BMTG_TDCMP2)   /* Timer D compare 2 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIME_REPETITION    (SHRTIM_BMTG_TEREPT)    /* Timer E repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIME_CMP1          (SHRTIM_BMTG_TECMP1)   /* Timer E compare 1 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIME_CMP2          (SHRTIM_BMTG_TECMP2)   /* Timer E compare 2 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMF_RESET         (SHRTIM_BMTG_TFRSTRO)    /* Timer F reset event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMF_REPETITION    (SHRTIM_BMTG_TFREPT)    /* Timer F repetition event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMF_CMP1          (SHRTIM_BMTG_TFCMP1)   /* Timer F compare 1 event is starting the burst mode operation */
#define SHRTIM_BM_TRIG_TIMA_EVENT7        (SHRTIM_BMTG_TAPRDEXEV7)   /* Timer A period following an external event 7 (conditioned by TIMA filters) is starting the burst mode operation  */
#define SHRTIM_BM_TRIG_TIMD_EVENT8        (SHRTIM_BMTG_TDPRDEXEV8)   /* Timer D period following an external event 8 (conditioned by TIMD filters) is starting the burst mode operation  */
#define SHRTIM_BM_TRIG_EVENT_7            (SHRTIM_BMTG_EXEV7)     /* External event 7 conditioned by TIMA filters is starting the burst mode operation */
#define SHRTIM_BM_TRIG_EVENT_8            (SHRTIM_BMTG_EXEV8)     /* External event 8 conditioned by TIMD filters is starting the burst mode operation */
#define SHRTIM_BM_TRIG_EVENT_ONCHIP       (SHRTIM_BMTG_OCEV)   /* A rising edge on an on-chip Event (for instance from GP timer or comparator) triggers the burst mode operation */


/** Defining the operating state of the burst mode controller. **/
#define SHRTIM_BM_STATUS_NORMAL             0x00000000U           /* Normal operation */
#define SHRTIM_BM_STATUS_BURST_ONGOING      SHRTIM_BMCTRL_BMSTS     /* Burst operation on-going */


/** Defining the Counter Up Down Mode. **/
#define SHRTIM_COUNTING_MODE_UP                    0x00000000U           /* counter is operating in up-counting mode */
#define SHRTIM_COUNTING_MODE_UP_DOWN               SHRTIM_TXCTRL2_UPDOWNM      /* counter is operating in up-down counting mode  */


/** Defining the Roll-Over counter Mode. **/
#define SHRTIM_ROLLOVER_MODE_PER            2U                        /* Event generated when counter reaches period value  ('crest' mode) */
#define SHRTIM_ROLLOVER_MODE_RST            1U                        /* Event generated when counter equals 0 ('valley' mode) */
#define SHRTIM_ROLLOVER_MODE_BOTH           0U                        /* Event generated when counter reach both conditions (0 or SHRTIM_PERxR value) */


/** Ddefining how the timer counter operates. **/
#define SHRTIM_TRIGHALF_DISABLED        0x00000000U            /* Timer Compare 2 register is behaving in standard mode */
#define SHRTIM_TRIGHALF_ENABLED         SHRTIM_TXCTRL2_TRGHLF    /* Timer Compare 2 register is behaving in triggered-half mode  */


/** Defining the greater than compare 1 or 3 PWM Mode. **/
#define SHRTIM_GTCMP1_EQUAL             0x00000000U            /* event is generated when counter is equal to compare value */
#define SHRTIM_GTCMP1_GREATER           SHRTIM_TXCTRL2_GTCMP1    /* event is generated when counter is greater than compare value */
#define SHRTIM_GTCMP3_EQUAL             0x00000000U            /* event is generated when counter is equal to compare value */
#define SHRTIM_GTCMP3_GREATER           SHRTIM_TXCTRL2_GTCMP3    /* event is generated when counter is greater than compare value */


/** Enabling the Dual DAC Reset trigger mechanism. **/
#define SHRTIM_DUDACEN_DISABLED      0x00000000U              /*  Dual DAC trigger is generated on counter reset or roll-over event */
#define SHRTIM_DUDACEN_ENABLED       SHRTIM_TXCTRL2_DUDACEN        /*  Dual DAC trigger is generated on output 1 set  event */


/** Defining the Dual DAC Reset trigger. **/
#define SHRTIM_DUDACRST_COUNTER       0x00000000U              /* Dual DAC trigger is generated on counter reset or roll-over event */
#define SHRTIM_DUDACRST_OUT1SET       SHRTIM_TXCTRL2_DUDACRST        /* Dual DAC trigger is generated on output 1 set  event */


/** Defining the Dual DAC Step trigger. **/
#define SHRTIM_DUDACSTEP_CMP2          0x00000000U              /* trigger is generated on compare 2 event */
#define SHRTIM_DUDACSTEP_OUT1RST       SHRTIM_TXCTRL2_DUDACSTEP        /* trigger is generated on output 1 reset event */

#define SHRTIM_AUXOUTPUT_DEFAULT                        0x00000000U                /*  Default Auxiliary output follows main outpput */  
#define SHRTIM_AUXOUTPUT_FOLLOW_CROSSBAR                 SHRTIM_EXTEND_AUXBYPA_1      /*  Auxiliary output follows cross bar */
#define SHRTIM_AUXOUTPUT_FOLLOW_MAINOUTPUT               (SHRTIM_EXTEND_AUXBYPA_1 | SHRTIM_EXTEND_AUXBYPA_0)/*  Auxiliary output follows main output */
#define SHRITM_AUXOUTPUT_BYPASS                          SHRTIM_EXTEND_AUXBYPA    /*  Auxiliary output bypass */

/** Defining the some bit position  **/
#define SHRTIM_MCTRL_MCNTEN_Pos             (16U)
#define SHRTIM_MCTRL_TACNTEN_Pos            (17U)
#define SHRTIM_CTRL2_MSWCNTRST_Pos          (8U)
#define SHRTIM_CTRL2_SWAPA_Pos              (16U)
#define SHRTIM_TXCPT1_UDSTS1_Pos            (16U)
#define SHRTIM_TXCPT2_UDSTS2_Pos            (16U)
#define SHRTIM_TXCTRL2_ROM_Pos              (6U)
#define SHRTIM_TXCTRL2_FEROM_Pos        (14U)
#define SHRTIM_TXCTRL2_BMROM_Pos        (12U)
#define SHRTIM_TXCTRL2_ADCROM_Pos           (10U)
#define SHRTIM_TXCTRL2_OUTROM_Pos            (8U)
#define SHRTIM_TXCTRL2_UPDOWNM_Pos              (4U)
#define SHRTIM_TXEXEVFLT3_EXEVCNT_Pos         (8U)
#define SHRTIM_TXEXEVFLT3_EXEVSEL_Pos         (4U)
#define SHRTIM_TXDT_DTF_Pos                    (16U)
#define SHRTIM_TXINTSTS_O1DIPSTS_Pos           (18U)
#define SHRTIM_TXINTSTS_O1BCKUP_Pos            (20U)


/**
*\*\brief  Write a value in SHRTIM register
*\*\param  __INSTANCE__ SHRTIM Instance
*\*\param  __REG__ Register to be written
*\*\param  __VALUE__ Value to be written in the register
*\*\retval None
  */
#define SHRTIM_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
*\*\brief  Read a value in SHRTIM register
*\*\param  __INSTANCE__ SHRTIM Instance
*\*\param  __REG__ Register to be read
*\*\retval Register value
  */
#define SHRTIM_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/**** Function declaration start ***/
void SHRTIM_SetSyncInSrc(SHRTIM_Module *SHRTIMx, uint32_t SyncInSrc);
uint32_t SHRTIM_GetSyncInSrc(SHRTIM_Module *SHRTIMx);
void SHRTIM_ConfigSyncOut(SHRTIM_Module *SHRTIMx, uint32_t Config, uint32_t Src);
void SHRTIM_SetSyncOutConfig(SHRTIM_Module *SHRTIMx, uint32_t SyncOutConfig);
uint32_t SHRTIM_GetSyncOutConfig(SHRTIM_Module *SHRTIMx);
void SHRTIM_SetSyncOutSrc(SHRTIM_Module *SHRTIMx, uint32_t SyncOutSrc);
uint32_t SHRTIM_GetSyncOutSrc(SHRTIM_Module *SHRTIMx);
void SHRTIM_SuspendUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timers);
void SHRTIM_ResumeUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timers);
void SHRTIM_ForceUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timers);
void SHRTIM_CounterReset(SHRTIM_Module *SHRTIMx, uint32_t Timers);
void SHRTIM_EnableSwapOutputs(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableSwapOutputs(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledSwapOutputs(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableOutput(SHRTIM_Module *SHRTIMx, uint32_t Outputs);
void SHRTIM_DisableOutput(SHRTIM_Module *SHRTIMx, uint32_t Outputs);
uint32_t SHRTIM_IsEnabledOutput(SHRTIM_Module *SHRTIMx, uint32_t Output);
uint32_t SHRTIM_IsDisabledOutput(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_ConfigADCTrig(SHRTIM_Module *SHRTIMx, uint32_t ADCTrigSrcReg, uint32_t ADCTrig, uint32_t Update, uint32_t Src);
void SHRTIM_SetADCTrigUpdate(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig, uint32_t Update);
uint32_t SHRTIM_GetADCTrigUpdate(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig);
void SHRTIM_SetADCTrigSrc(SHRTIM_Module *SHRTIMx, uint32_t ADCTrigSrcReg, uint32_t Src);
uint32_t SHRTIM_GetADCTrigSrc(SHRTIM_Module *SHRTIMx, uint32_t ADCTrigSrcReg);
void SHRTIM_SetADCPostScaler(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig, uint32_t PostScaler);
uint32_t SHRTIM_GetADCPostScaler(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig);
void SHRTIM_TIM_CounterEnable(SHRTIM_Module *SHRTIMx, uint32_t Timers);
void SHRTIM_TIM_CounterDisable(SHRTIM_Module *SHRTIMx, uint32_t Timers);
uint32_t SHRTIM_TIM_IsCounterEnabled(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Prescaler);
uint32_t SHRTIM_TIM_GetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCounterMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetCounterMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableResyncUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableResyncUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledResyncUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetInterleavedMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetInterleavedMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableStartOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableStartOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledStartOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableResetOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableResetOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledResetOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetDACTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t DACTrig);
uint32_t SHRTIM_TIM_GetDACTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnablePreload(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisablePreload(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledPreload(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetUpdateTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t UpdateTrig);
uint32_t SHRTIM_TIM_GetUpdateTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetUpdateGating(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t UpdateGating);
uint32_t SHRTIM_TIM_GetUpdateGating(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnablePushPullMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisablePushPullMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledPushPullMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCompareMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareUnit,
                               uint32_t Mode);
uint32_t SHRTIM_TIM_GetCompareMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareUnit);
void SHRTIM_TIM_SetCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Counter);
uint32_t SHRTIM_TIM_GetCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetPeriod(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Period);
uint32_t SHRTIM_TIM_GetPeriod(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetRepetition(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Repetition);
uint32_t SHRTIM_TIM_GetRepetition(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCompare1(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue);
uint32_t SHRTIM_TIM_GetCompare1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCompare2(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue);
uint32_t SHRTIM_TIM_GetCompare2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCompare3(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue);
uint32_t SHRTIM_TIM_GetCompare3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCompare4(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue);
uint32_t SHRTIM_TIM_GetCompare4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCompare5(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue);
uint32_t SHRTIM_TIM_GetCompare5(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetResetTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t ResetTrig);
uint32_t SHRTIM_TIM_GetResetTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_GetCapture1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_GetCapture1Direction(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_GetCapture2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_GetCapture2Direction(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCaptureTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CaptureUnit,
                               uint64_t CaptureTrig);
uint64_t SHRTIM_TIM_GetCaptureTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CaptureUnit);
void SHRTIM_TIM_EnableDeadTime(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableDeadTime(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledDeadTime(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetDPMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t DPMode);
uint32_t SHRTIM_TIM_GetDPMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableDP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableDP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledDP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableBIAR(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableBIAR(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledBIAR(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableSoftDP(SHRTIM_Module *SHRTIMx, uint32_t SoftDP);
uint32_t SHRTIM_TIM_IsEnabledSoftDP(SHRTIM_Module *SHRTIMx, uint32_t SoftDP);
void SHRTIM_TIM_EnableFault(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Faults);
void SHRTIM_TIM_DisableFault(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Faults);
uint32_t SHRTIM_TIM_IsEnabledFault(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Fault);
void SHRTIM_TIM_LockFault(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetBurstModeOption(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t BurtsModeOption);
uint32_t SHRTIM_TIM_GetBurstModeOption(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_ConfigBurstDMA(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Registers);
uint32_t SHRTIM_TIM_GetCurrentPushPullStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_GetIdlePushPullStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableEventWindowSelection(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisbleEventWindowSelection(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetEventFilter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event, uint32_t Filter);
uint32_t SHRTIM_TIM_GetEventFilter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event);
void SHRTIM_TIM_SetEventLatchStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event,
                                    uint32_t LatchStatus);
uint32_t SHRTIM_TIM_GetEventLatchStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event);
void SHRTIM_TIM_SetTriggeredHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetTriggeredHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetComp1Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetComp1Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetComp3Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetComp3Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetFaultEventRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetFaultEventRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetBMRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetBMRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetADCRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetADCRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetOutputRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetOutputRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetCountingMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetCountingMode(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetDualDacResetTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetDualDacResetTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetDualDacStepTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode);
uint32_t SHRTIM_TIM_GetDualDacStepTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_EnableDualDacTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_DisableDualDacTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_TIM_IsEnabledDualDacTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_TIM_SetEventCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter,
                                         uint32_t Threshold);
uint32_t SHRTIM_TIM_GetEventCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Timer,
                                             uint32_t EventCounter);
void SHRTIM_TIM_SetEventCounterSource(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter,
                                      uint32_t Event);
uint32_t SHRTIM_TIM_GetEventCounterSource(SHRTIM_Module *SHRTIMx, uint32_t Timer,
                                          uint32_t EventCounter);
void SHRTIM_TIM_SetEventCounterResetMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter,
                                         uint32_t Mode);
uint32_t SHRTIM_TIM_GetEventCounterResetMode(SHRTIM_Module *SHRTIMx, uint32_t Timer,
                                             uint32_t EventCounter);
void SHRTIM_TIM_ResetEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter);
void SHRTIM_TIM_EnableEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter);
void SHRTIM_TIM_DisableEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter);
uint32_t SHRTIM_TIM_IsEnabledEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer,
                                          uint32_t EventCounter);
void SHRTIM_DT_Config(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Configuration);
void SHRTIM_DT_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Prescaler);
uint32_t SHRTIM_DT_GetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_SetRisingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t RisingValue);
uint32_t SHRTIM_DT_GetRisingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_SetRisingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t RisingSign);
uint32_t SHRTIM_DT_GetRisingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_SetFallingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t FallingValue);
uint32_t SHRTIM_DT_GetFallingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_SetFallingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t FallingSign);
uint32_t SHRTIM_DT_GetFallingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_LockRising(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_LockRisingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_LockFalling(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DT_LockFallingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_CHP_Config(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Configuration);
void SHRTIM_CHP_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Prescaler);
uint32_t SHRTIM_CHP_GetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_CHP_SetDutyCycle(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t DutyCycle);
uint32_t SHRTIM_CHP_GetDutyCycle(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_CHP_SetPulseWidth(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t PulseWidth);
uint32_t SHRTIM_CHP_GetPulseWidth(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_OUT_SetOutputSetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t SetSrc);
uint32_t SHRTIM_OUT_GetOutputSetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_SetOutputResetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t ResetSrc);
uint32_t SHRTIM_OUT_GetOutputResetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_Config(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t Configuration);
void SHRTIM_OUT_SetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t Polarity);
uint32_t SHRTIM_OUT_GetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_SetIdleLevel(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t IdleLevel);
uint32_t SHRTIM_OUT_GetIdleLevel(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_SetFaultState(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t FaultState);
uint32_t SHRTIM_OUT_GetFaultState(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_SetChopperMode(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t ChopperMode);
uint32_t SHRTIM_OUT_GetChopperMode(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_SetBMEntryMode(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t BMEntryMode);
uint32_t SHRTIM_OUT_GetBMEntryMode(SHRTIM_Module *SHRTIMx, uint32_t Output);
uint32_t SHRTIM_OUT_GetDPOutStatus(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_OUT_ForceLevel(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t OutputLevel);
uint32_t SHRTIM_OUT_GetLevel(SHRTIM_Module *SHRTIMx, uint32_t Output);
void SHRTIM_EXEV_Config(SHRTIM_Module *SHRTIMx, uint32_t Event,
                        uint32_t Src, uint32_t SrcCompSel, uint32_t Polarity,
                        uint32_t Sensitivity, uint32_t FastMode, uint32_t Filter, uint32_t Prescaler);
void SHRTIM_EXEV_SetSrc(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Src);
uint32_t SHRTIM_EXEV_GetSrc(SHRTIM_Module *SHRTIMx, uint32_t Event);
void SHRTIM_EXEV_SetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t SrcCompSel);
uint32_t SHRTIM_EXEV_GetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Event);
void SHRTIM_EXEV_SetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Polarity);
uint32_t SHRTIM_EXEV_GetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Event);
void SHRTIM_EXEV_SetSensitivity(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Sensitivity);
uint32_t SHRTIM_EXEV_GetSensitivity(SHRTIM_Module *SHRTIMx, uint32_t Event);
void SHRTIM_EXEV_SetFastMode(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t FastMode);
uint32_t SHRTIM_EXEV_GetFastMode(SHRTIM_Module *SHRTIMx, uint32_t Event);
void SHRTIM_EXEV_SetFilter(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Filter);
uint32_t SHRTIM_EXEV_GetFilter(SHRTIM_Module *SHRTIMx, uint32_t Event);
void SHRTIM_EXEV_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Prescaler);
uint32_t SHRTIM_EXEV_GetPrescaler(SHRTIM_Module *SHRTIMx);
void SHRTIM_FALT_Config(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Configuration, uint32_t SrcCompSel);
void SHRTIM_FALT_SetSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Src);
uint32_t SHRTIM_FALT_GetSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t SrcCompSel);
uint32_t SHRTIM_FALT_GetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Polarity);
uint32_t SHRTIM_FALT_GetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetFilter(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Filter);
uint32_t SHRTIM_FALT_GetFilter(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Prescaler);
uint32_t SHRTIM_FALT_GetPrescaler(SHRTIM_Module *SHRTIMx);
void SHRTIM_FALT_Lock(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_Enable(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_Disable(SHRTIM_Module *SHRTIMx, uint32_t Fault);
uint32_t SHRTIM_FALT_IsEnabled(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_EnableSysFault(SHRTIM_Module *SHRTIMx, uint32_t SysFault);
uint32_t SHRTIM_FALT_IsEnabledSysFault(SHRTIM_Module *SHRTIMx, uint32_t SysFault);
void SHRTIM_FALT_EnableBlanking(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_DisableBlanking(SHRTIM_Module *SHRTIMx, uint32_t Fault);
uint32_t SHRTIM_FALT_IsEnabledBlanking(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetBlankingSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Source);
uint32_t SHRTIM_FALT_GetBlankingSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Threshold);
uint32_t SHRTIM_FALT_GetCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_EnableSoftFault(SHRTIM_Module *SHRTIMx, uint32_t Fault);
uint32_t SHRTIM_FALT_IsEnabledSoftFault(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_SetResetMode(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Mode);
uint32_t SHRTIM_FALT_GetResetMode(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_FALT_ResetCounter(SHRTIM_Module *SHRTIMx, uint32_t Fault);
void SHRTIM_BM_Config(SHRTIM_Module *SHRTIMx, uint32_t Configuration);
void SHRTIM_BM_SetMode(SHRTIM_Module *SHRTIMx, uint32_t Mode);
uint32_t SHRTIM_BM_GetMode(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_SetClockSrc(SHRTIM_Module *SHRTIMx, uint32_t ClockSrc);
uint32_t SHRTIM_BM_GetClockSrc(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Prescaler);
uint32_t SHRTIM_BM_GetPrescaler(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_EnablePreload(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_DisablePreload(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_BM_IsEnabledPreload(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_SetTrig(SHRTIM_Module *SHRTIMx, uint32_t Trig);
uint32_t SHRTIM_BM_GetTrig(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_SetCompare(SHRTIM_Module *SHRTIMx, uint32_t CompareValue);
uint32_t SHRTIM_BM_GetCompare(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_SetPeriod(SHRTIM_Module *SHRTIMx, uint32_t Period);
uint32_t SHRTIM_BM_GetPeriod(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_Enable(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_Disable(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_BM_IsEnabled(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_Start(SHRTIM_Module *SHRTIMx);
void SHRTIM_BM_Stop(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_BM_GetStatus(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_FALT1(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_FALT1(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_FALT2(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_FALT2(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_FALT3(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_FALT3(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_FALT4(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_FALT4(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_FALT5(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_FALT5(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_FALT6(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_FALT6(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_SYSFALT(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_SYSFALT(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_BMPRD(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_BMPRD(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_SYNC(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsActiveFlag_SYNC(SHRTIM_Module *SHRTIMx);
void SHRTIM_ClearFlag_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CMP5(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CMP5(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_ClearFlag_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsActiveFlag_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_FALT1(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_FALT1(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_FALT1(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_FALT2(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_FALT2(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_FALT2(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_FALT3(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_FALT3(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_FALT3(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_FALT4(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_FALT4(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_FALT4(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_FALT5(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_FALT5(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_FALT5(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_FALT6(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_FALT6(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_FALT6(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_SYSFALT(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_SYSFALT(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_SYSFALT(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_BMPRD(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_BMPRD(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_BMPRD(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_SYNC(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableIT_SYNC(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledIT_SYNC(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableIT_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableIT_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableIT_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledIT_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_SYNC(SHRTIM_Module *SHRTIMx);
void SHRTIM_DisableDMAReq_SYNC(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledDMAReq_SYNC(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableDMAReq_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_EnableDMAReq_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDMAReq_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDMAReq_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDebugHaltAllTimers(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableDebugHaltAllTimers(SHRTIM_Module *SHRTIMx);
uint32_t SHRTIM_IsEnabledDebugHaltAllTimers(SHRTIM_Module *SHRTIMx);
void SHRTIM_EnableDebugHaltTimer(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_DisableDebugHaltTimer(SHRTIM_Module *SHRTIMx, uint32_t Timer);
uint32_t SHRTIM_IsEnabledDebugHaltTimer(SHRTIM_Module *SHRTIMx, uint32_t Timer);
void SHRTIM_SetAuxliaryBypass(SHRTIM_Module *SHRTIMx, uint32_t AuxBypa); 
uint32_t SHRTIM_GetAuxliaryBypass(SHRTIM_Module *SHRTIMx); 
/**** Function declaration end ***/

#ifdef __cplusplus
}
#endif

#endif /* N32H76X_78X_SHRTIM_H */

