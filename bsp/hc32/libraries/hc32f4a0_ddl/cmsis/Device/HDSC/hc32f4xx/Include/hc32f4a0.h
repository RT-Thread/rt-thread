/**
 *******************************************************************************
 * @file  HC32F4A0.h
 * @brief Headerfile for HC32F4A0 series MCU
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             Modify headfile register address and register name based on reference manual Rev1.13
   2023-09-30       CDT             Modify headfile based on reference manual Rev1.3
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 **/

#ifndef __HC32F4A0_H__
#define __HC32F4A0_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 ******************************************************************************/
#define __MPU_PRESENT             1       /*!< HC32F4A0 provides MPU                                */
#define __VTOR_PRESENT            1       /*!< HC32F4A0 supported vector table registers            */
#define __NVIC_PRIO_BITS          4       /*!< HC32F4A0 uses 4 Bits for the Priority Levels         */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used         */
#define __FPU_PRESENT             1       /*!< FPU present                                          */

/*******************************************************************************
 * Interrupt Number Definition
 ******************************************************************************/
typedef enum {
    NMI_IRQn             = -14, /*  2 Non Maskable                            */
    HardFault_IRQn       = -13, /*  3 Hard Fault                              */
    MemManageFault_IRQn  = -12, /*  4 MemManage Fault                         */
    BusFault_IRQn        = -11, /*  5 Bus Fault                               */
    UsageFault_IRQn      = -10, /*  6 Usage Fault                             */
    SVC_IRQn             = -5,  /* 11 SVCall                                  */
    DebugMonitor_IRQn    = -4,  /* 12 DebugMonitor                            */
    PendSV_IRQn          = -2,  /* 14 Pend SV                                 */
    SysTick_IRQn         = -1,  /* 15 System Tick                             */
    INT000_IRQn          = 0,
    INT001_IRQn          = 1,
    INT002_IRQn          = 2,
    INT003_IRQn          = 3,
    INT004_IRQn          = 4,
    INT005_IRQn          = 5,
    INT006_IRQn          = 6,
    INT007_IRQn          = 7,
    INT008_IRQn          = 8,
    INT009_IRQn          = 9,
    INT010_IRQn          = 10,
    INT011_IRQn          = 11,
    INT012_IRQn          = 12,
    INT013_IRQn          = 13,
    INT014_IRQn          = 14,
    INT015_IRQn          = 15,
    INT016_IRQn          = 16,
    INT017_IRQn          = 17,
    INT018_IRQn          = 18,
    INT019_IRQn          = 19,
    INT020_IRQn          = 20,
    INT021_IRQn          = 21,
    INT022_IRQn          = 22,
    INT023_IRQn          = 23,
    INT024_IRQn          = 24,
    INT025_IRQn          = 25,
    INT026_IRQn          = 26,
    INT027_IRQn          = 27,
    INT028_IRQn          = 28,
    INT029_IRQn          = 29,
    INT030_IRQn          = 30,
    INT031_IRQn          = 31,
    INT032_IRQn          = 32,
    INT033_IRQn          = 33,
    INT034_IRQn          = 34,
    INT035_IRQn          = 35,
    INT036_IRQn          = 36,
    INT037_IRQn          = 37,
    INT038_IRQn          = 38,
    INT039_IRQn          = 39,
    INT040_IRQn          = 40,
    INT041_IRQn          = 41,
    INT042_IRQn          = 42,
    INT043_IRQn          = 43,
    INT044_IRQn          = 44,
    INT045_IRQn          = 45,
    INT046_IRQn          = 46,
    INT047_IRQn          = 47,
    INT048_IRQn          = 48,
    INT049_IRQn          = 49,
    INT050_IRQn          = 50,
    INT051_IRQn          = 51,
    INT052_IRQn          = 52,
    INT053_IRQn          = 53,
    INT054_IRQn          = 54,
    INT055_IRQn          = 55,
    INT056_IRQn          = 56,
    INT057_IRQn          = 57,
    INT058_IRQn          = 58,
    INT059_IRQn          = 59,
    INT060_IRQn          = 60,
    INT061_IRQn          = 61,
    INT062_IRQn          = 62,
    INT063_IRQn          = 63,
    INT064_IRQn          = 64,
    INT065_IRQn          = 65,
    INT066_IRQn          = 66,
    INT067_IRQn          = 67,
    INT068_IRQn          = 68,
    INT069_IRQn          = 69,
    INT070_IRQn          = 70,
    INT071_IRQn          = 71,
    INT072_IRQn          = 72,
    INT073_IRQn          = 73,
    INT074_IRQn          = 74,
    INT075_IRQn          = 75,
    INT076_IRQn          = 76,
    INT077_IRQn          = 77,
    INT078_IRQn          = 78,
    INT079_IRQn          = 79,
    INT080_IRQn          = 80,
    INT081_IRQn          = 81,
    INT082_IRQn          = 82,
    INT083_IRQn          = 83,
    INT084_IRQn          = 84,
    INT085_IRQn          = 85,
    INT086_IRQn          = 86,
    INT087_IRQn          = 87,
    INT088_IRQn          = 88,
    INT089_IRQn          = 89,
    INT090_IRQn          = 90,
    INT091_IRQn          = 91,
    INT092_IRQn          = 92,
    INT093_IRQn          = 93,
    INT094_IRQn          = 94,
    INT095_IRQn          = 95,
    INT096_IRQn          = 96,
    INT097_IRQn          = 97,
    INT098_IRQn          = 98,
    INT099_IRQn          = 99,
    INT100_IRQn          = 100,
    INT101_IRQn          = 101,
    INT102_IRQn          = 102,
    INT103_IRQn          = 103,
    INT104_IRQn          = 104,
    INT105_IRQn          = 105,
    INT106_IRQn          = 106,
    INT107_IRQn          = 107,
    INT108_IRQn          = 108,
    INT109_IRQn          = 109,
    INT110_IRQn          = 110,
    INT111_IRQn          = 111,
    INT112_IRQn          = 112,
    INT113_IRQn          = 113,
    INT114_IRQn          = 114,
    INT115_IRQn          = 115,
    INT116_IRQn          = 116,
    INT117_IRQn          = 117,
    INT118_IRQn          = 118,
    INT119_IRQn          = 119,
    INT120_IRQn          = 120,
    INT121_IRQn          = 121,
    INT122_IRQn          = 122,
    INT123_IRQn          = 123,
    INT124_IRQn          = 124,
    INT125_IRQn          = 125,
    INT126_IRQn          = 126,
    INT127_IRQn          = 127,
    INT128_IRQn          = 128,
    INT129_IRQn          = 129,
    INT130_IRQn          = 130,
    INT131_IRQn          = 131,
    INT132_IRQn          = 132,
    INT133_IRQn          = 133,
    INT134_IRQn          = 134,
    INT135_IRQn          = 135,
    INT136_IRQn          = 136,
    INT137_IRQn          = 137,
    INT138_IRQn          = 138,
    INT139_IRQn          = 139,
    INT140_IRQn          = 140,
    INT141_IRQn          = 141,
    INT142_IRQn          = 142,
    INT143_IRQn          = 143,

} IRQn_Type;

#include <core_cm4.h>
#include <stdint.h>

/**
 *******************************************************************************
 ** \brief Event number enumeration
 ******************************************************************************/
typedef enum {
    EVT_SRC_SWI_IRQ0             = 0U,
    EVT_SRC_SWI_IRQ1             = 1U,
    EVT_SRC_SWI_IRQ2             = 2U,
    EVT_SRC_SWI_IRQ3             = 3U,
    EVT_SRC_SWI_IRQ4             = 4U,
    EVT_SRC_SWI_IRQ5             = 5U,
    EVT_SRC_SWI_IRQ6             = 6U,
    EVT_SRC_SWI_IRQ7             = 7U,
    EVT_SRC_SWI_IRQ8             = 8U,
    EVT_SRC_SWI_IRQ9             = 9U,
    EVT_SRC_SWI_IRQ10            = 10U,
    EVT_SRC_SWI_IRQ11            = 11U,
    EVT_SRC_SWI_IRQ12            = 12U,
    EVT_SRC_SWI_IRQ13            = 13U,
    EVT_SRC_SWI_IRQ14            = 14U,
    EVT_SRC_SWI_IRQ15            = 15U,
    EVT_SRC_SWI_IRQ16            = 16U,
    EVT_SRC_SWI_IRQ17            = 17U,
    EVT_SRC_SWI_IRQ18            = 18U,
    EVT_SRC_SWI_IRQ19            = 19U,
    EVT_SRC_SWI_IRQ20            = 20U,
    EVT_SRC_SWI_IRQ21            = 21U,
    EVT_SRC_SWI_IRQ22            = 22U,
    EVT_SRC_SWI_IRQ23            = 23U,
    EVT_SRC_SWI_IRQ24            = 24U,
    EVT_SRC_SWI_IRQ25            = 25U,
    EVT_SRC_SWI_IRQ26            = 26U,
    EVT_SRC_SWI_IRQ27            = 27U,
    EVT_SRC_SWI_IRQ28            = 28U,
    EVT_SRC_SWI_IRQ29            = 29U,
    EVT_SRC_SWI_IRQ30            = 30U,
    EVT_SRC_SWI_IRQ31            = 31U,
    /* External Interrupt  */
    EVT_SRC_PORT_EIRQ0           = 0U,      /* PORT_EIRQ0 */
    EVT_SRC_PORT_EIRQ1           = 1U,      /* PORT_EIRQ1 */
    EVT_SRC_PORT_EIRQ2           = 2U,      /* PORT_EIRQ2 */
    EVT_SRC_PORT_EIRQ3           = 3U,      /* PORT_EIRQ3 */
    EVT_SRC_PORT_EIRQ4           = 4U,      /* PORT_EIRQ4 */
    EVT_SRC_PORT_EIRQ5           = 5U,      /* PORT_EIRQ5 */
    EVT_SRC_PORT_EIRQ6           = 6U,      /* PORT_EIRQ6 */
    EVT_SRC_PORT_EIRQ7           = 7U,      /* PORT_EIRQ7 */
    EVT_SRC_PORT_EIRQ8           = 8U,      /* PORT_EIRQ8 */
    EVT_SRC_PORT_EIRQ9           = 9U,      /* PORT_EIRQ9 */
    EVT_SRC_PORT_EIRQ10          = 10U,     /* PORT_EIRQ10 */
    EVT_SRC_PORT_EIRQ11          = 11U,     /* PORT_EIRQ11 */
    EVT_SRC_PORT_EIRQ12          = 12U,     /* PORT_EIRQ12 */
    EVT_SRC_PORT_EIRQ13          = 13U,     /* PORT_EIRQ13 */
    EVT_SRC_PORT_EIRQ14          = 14U,     /* PORT_EIRQ14 */
    EVT_SRC_PORT_EIRQ15          = 15U,     /* PORT_EIRQ15 */
    /*  DMA_1  */
    EVT_SRC_DMA1_TC0             = 32U,     /* DMA_1_TC0 */
    EVT_SRC_DMA1_TC1             = 33U,     /* DMA_1_TC1 */
    EVT_SRC_DMA1_TC2             = 34U,     /* DMA_1_TC2 */
    EVT_SRC_DMA1_TC3             = 35U,     /* DMA_1_TC3 */
    EVT_SRC_DMA1_TC4             = 36U,     /* DMA_1_TC4 */
    EVT_SRC_DMA1_TC5             = 37U,     /* DMA_1_TC5 */
    EVT_SRC_DMA1_TC6             = 38U,     /* DMA_1_TC6 */
    EVT_SRC_DMA1_TC7             = 39U,     /* DMA_1_TC7 */
    EVT_SRC_DMA1_BTC0            = 40U,     /* DMA_1_BTC0 */
    EVT_SRC_DMA1_BTC1            = 41U,     /* DMA_1_BTC1 */
    EVT_SRC_DMA1_BTC2            = 42U,     /* DMA_1_BTC2 */
    EVT_SRC_DMA1_BTC3            = 43U,     /* DMA_1_BTC3 */
    EVT_SRC_DMA1_BTC4            = 44U,     /* DMA_1_BTC4 */
    EVT_SRC_DMA1_BTC5            = 45U,     /* DMA_1_BTC5 */
    EVT_SRC_DMA1_BTC6            = 46U,     /* DMA_1_BTC6 */
    EVT_SRC_DMA1_BTC7            = 47U,     /* DMA_1_BTC7 */
    /*  EFM  */
    EVT_SRC_EFM_OPTEND           = 51U,     /* EFM_OPTEND */
    /*  USBFS  */
    EVT_SRC_USBFS_SOF            = 52U,     /* USBFS_SOF */
    /*  USBHS  */
    EVT_SRC_USBHS_SOF            = 53U,     /* USBHS_SOF */
    /*  DCU  */
    EVT_SRC_DCU1                 = 55U,     /* DCU1 */
    EVT_SRC_DCU2                 = 56U,     /* DCU2 */
    EVT_SRC_DCU3                 = 57U,     /* DCU3 */
    EVT_SRC_DCU4                 = 58U,     /* DCU4 */
    EVT_SRC_DCU5                 = 59U,     /* DCU5 */
    EVT_SRC_DCU6                 = 60U,     /* DCU6 */
    EVT_SRC_DCU7                 = 61U,     /* DCU7 */
    EVT_SRC_DCU8                 = 62U,     /* DCU8 */
    /*  DMA_2  */
    EVT_SRC_DMA2_TC0             = 64U,     /* DMA_2_TC0 */
    EVT_SRC_DMA2_TC1             = 65U,     /* DMA_2_TC1 */
    EVT_SRC_DMA2_TC2             = 66U,     /* DMA_2_TC2 */
    EVT_SRC_DMA2_TC3             = 67U,     /* DMA_2_TC3 */
    EVT_SRC_DMA2_TC4             = 68U,     /* DMA_2_TC4 */
    EVT_SRC_DMA2_TC5             = 69U,     /* DMA_2_TC5 */
    EVT_SRC_DMA2_TC6             = 70U,     /* DMA_2_TC6 */
    EVT_SRC_DMA2_TC7             = 71U,     /* DMA_2_TC7 */
    EVT_SRC_DMA2_BTC0            = 72U,     /* DMA_2_BTC0 */
    EVT_SRC_DMA2_BTC1            = 73U,     /* DMA_2_BTC1 */
    EVT_SRC_DMA2_BTC2            = 74U,     /* DMA_2_BTC2 */
    EVT_SRC_DMA2_BTC3            = 75U,     /* DMA_2_BTC3 */
    EVT_SRC_DMA2_BTC4            = 76U,     /* DMA_2_BTC4 */
    EVT_SRC_DMA2_BTC5            = 77U,     /* DMA_2_BTC5 */
    EVT_SRC_DMA2_BTC6            = 78U,     /* DMA_2_BTC6 */
    EVT_SRC_DMA2_BTC7            = 79U,     /* DMA_2_BTC7 */
    /*  MAU  */
    EVT_SRC_MAU_SQRT             = 83U,     /* MAU_SQRT */
    /*  DVP  */
    EVT_SRC_DVP_FRAMSTA          = 84U,     /* DVP_FRAMSTA */
    EVT_SRC_DVP_LINESTA          = 85U,     /* DVP_LINESTA */
    EVT_SRC_DVP_LINEEND          = 86U,     /* DVP_LINEEND */
    EVT_SRC_DVP_FRAMEND          = 87U,     /* DVP_FRAMEND */
    EVT_SRC_DVP_SQUERR           = 88U,     /* DVP_SQUERR */
    EVT_SRC_DVP_FIFOERR          = 89U,     /* DVP_FIFOERR */
    EVT_SRC_DVP_DMAREQ           = 90U,     /* DVP_DMAREQ */
    /*  FMAC  */
    EVT_SRC_FMAC_1               = 91U,     /* FMAC_1_FIR */
    EVT_SRC_FMAC_2               = 92U,     /* FMAC_2_FIR */
    EVT_SRC_FMAC_3               = 93U,     /* FMAC_3_FIR */
    EVT_SRC_FMAC_4               = 94U,     /* FMAC_4_FIR */
    /*  TIMER0  */
    EVT_SRC_TMR0_1_CMP_A         = 96U,     /* TMR0_1_CMPA */
    EVT_SRC_TMR0_1_CMP_B         = 97U,     /* TMR0_1_CMPB */
    EVT_SRC_TMR0_2_CMP_A         = 98U,     /* TMR0_2_CMPA */
    EVT_SRC_TMR0_2_CMP_B         = 99U,     /* TMR0_2_CMPB */
    /*  TIMER2  */
    EVT_SRC_TMR2_1_CMP_A         = 100U,    /* TMR2_1_CMPA  */
    EVT_SRC_TMR2_1_CMP_B         = 101U,    /* TMR2_1_CMPB  */
    EVT_SRC_TMR2_1_OVF_A         = 102U,    /* TMR2_1_OVFA  */
    EVT_SRC_TMR2_1_OVF_B         = 103U,    /* TMR2_1_OVFB  */
    EVT_SRC_TMR2_2_CMP_A         = 104U,    /* TMR2_2_CMPA  */
    EVT_SRC_TMR2_2_CMP_B         = 105U,    /* TMR2_2_CMPB  */
    EVT_SRC_TMR2_2_OVF_A         = 106U,    /* TMR2_2_OVFA  */
    EVT_SRC_TMR2_2_OVF_B         = 107U,    /* TMR2_2_OVFB  */
    EVT_SRC_TMR2_3_CMP_A         = 108U,    /* TMR2_3_CMPA  */
    EVT_SRC_TMR2_3_CMP_B         = 109U,    /* TMR2_3_CMPB  */
    EVT_SRC_TMR2_3_OVF_A         = 110U,    /* TMR2_3_OVFA  */
    EVT_SRC_TMR2_3_OVF_B         = 111U,    /* TMR2_3_OVFB  */
    EVT_SRC_TMR2_4_CMP_A         = 112U,    /* TMR2_4_CMPA  */
    EVT_SRC_TMR2_4_CMP_B         = 113U,    /* TMR2_4_CMPB  */
    EVT_SRC_TMR2_4_OVF_A         = 114U,    /* TMR2_4_OVFA  */
    EVT_SRC_TMR2_4_OVF_B         = 115U,    /* TMR2_4_OVFB  */
    /*  RTC  */
    EVT_SRC_RTC_ALM              = 121U,    /* RTC_ALM */
    EVT_SRC_RTC_PRD              = 122U,    /* RTC_PRD */
    /*  TIMER6_1  */
    EVT_SRC_TMR6_1_GCMP_A        = 128U,    /* TMR6_1_GCMA */
    EVT_SRC_TMR6_1_GCMP_B        = 129U,    /* TMR6_1_GCMB */
    EVT_SRC_TMR6_1_GCMP_C        = 130U,    /* TMR6_1_GCMC */
    EVT_SRC_TMR6_1_GCMP_D        = 131U,    /* TMR6_1_GCMD */
    EVT_SRC_TMR6_1_GCMP_E        = 132U,    /* TMR6_1_GCME */
    EVT_SRC_TMR6_1_GCMP_F        = 133U,    /* TMR6_1_GCMF */
    EVT_SRC_TMR6_1_OVF           = 134U,    /* TMR6_1_GOVF */
    EVT_SRC_TMR6_1_UDF           = 135U,    /* TMR6_1_GUDF */
    /*  TIMER4_1  */
    EVT_SRC_TMR4_1_SCMP0         = 136U,    /* TMR4_1_SCM0 */
    EVT_SRC_TMR4_1_SCMP1         = 137U,    /* TMR4_1_SCM1 */
    EVT_SRC_TMR4_1_SCMP2         = 138U,    /* TMR4_1_SCM2 */
    EVT_SRC_TMR4_1_SCMP3         = 139U,    /* TMR4_1_SCM3 */
    EVT_SRC_TMR4_1_SCMP4         = 140U,    /* TMR4_1_SCM4 */
    EVT_SRC_TMR4_1_SCMP5         = 141U,    /* TMR4_1_SCM5 */
    /*  TIMER6_2  */
    EVT_SRC_TMR6_2_GCMP_A        = 144U,    /* TMR6_2_GCMA */
    EVT_SRC_TMR6_2_GCMP_B        = 145U,    /* TMR6_2_GCMB */
    EVT_SRC_TMR6_2_GCMP_C        = 146U,    /* TMR6_2_GCMC */
    EVT_SRC_TMR6_2_GCMP_D        = 147U,    /* TMR6_2_GCMD */
    EVT_SRC_TMR6_2_GCMP_E        = 148U,    /* TMR6_2_GCME */
    EVT_SRC_TMR6_2_GCMP_F        = 149U,    /* TMR6_2_GCMF */
    EVT_SRC_TMR6_2_OVF           = 150U,    /* TMR6_2_GOVF */
    EVT_SRC_TMR6_2_UDF           = 151U,    /* TMR6_2_GUDF */
    /*  TIMER4_2  */
    EVT_SRC_TMR4_2_SCMP0         = 152U,    /* TMR4_2_SCM0 */
    EVT_SRC_TMR4_2_SCMP1         = 153U,    /* TMR4_2_SCM1 */
    EVT_SRC_TMR4_2_SCMP2         = 154U,    /* TMR4_2_SCM2 */
    EVT_SRC_TMR4_2_SCMP3         = 155U,    /* TMR4_2_SCM3 */
    EVT_SRC_TMR4_2_SCMP4         = 156U,    /* TMR4_2_SCM4 */
    EVT_SRC_TMR4_2_SCMP5         = 157U,    /* TMR4_2_SCM5 */
    /*  TIMER6_3  */
    EVT_SRC_TMR6_3_GCMP_A        = 160U,    /* TMR6_3_GCMA */
    EVT_SRC_TMR6_3_GCMP_B        = 161U,    /* TMR6_3_GCMB */
    EVT_SRC_TMR6_3_GCMP_C        = 162U,    /* TMR6_3_GCMC */
    EVT_SRC_TMR6_3_GCMP_D        = 163U,    /* TMR6_3_GCMD */
    EVT_SRC_TMR6_3_GCMP_E        = 164U,    /* TMR6_3_GCME */
    EVT_SRC_TMR6_3_GCMP_F        = 165U,    /* TMR6_3_GCMF */
    EVT_SRC_TMR6_3_OVF           = 166U,    /* TMR6_3_GOVF */
    EVT_SRC_TMR6_3_UDF           = 167U,    /* TMR6_3_GUDF */
    /*  TIMER4_3  */
    EVT_SRC_TMR4_3_SCMP0         = 168U,    /* TMR4_3_SCM0 */
    EVT_SRC_TMR4_3_SCMP1         = 169U,    /* TMR4_3_SCM1 */
    EVT_SRC_TMR4_3_SCMP2         = 170U,    /* TMR4_3_SCM2 */
    EVT_SRC_TMR4_3_SCMP3         = 171U,    /* TMR4_3_SCM3 */
    EVT_SRC_TMR4_3_SCMP4         = 172U,    /* TMR4_3_SCM4 */
    EVT_SRC_TMR4_3_SCMP5         = 173U,    /* TMR4_3_SCM5 */
    /*  TIMER6  */
    EVT_SRC_TMR6_1_SCMP_A        = 179U,    /* TMR6_1_SCMA */
    EVT_SRC_TMR6_1_SCMP_B        = 180U,    /* TMR6_1_SCMB */
    EVT_SRC_TMR6_2_SCMP_A        = 187U,    /* TMR6_2_SCMA */
    EVT_SRC_TMR6_2_SCMP_B        = 188U,    /* TMR6_2_SCMB */
    EVT_SRC_TMR6_3_SCMP_A        = 195U,    /* TMR6_3_SCMA */
    EVT_SRC_TMR6_3_SCMP_B        = 196U,    /* TMR6_3_SCMB */
    EVT_SRC_TMR6_4_GCMP_A        = 208U,    /* TMR6_4_GCMA */
    EVT_SRC_TMR6_4_GCMP_B        = 209U,    /* TMR6_4_GCMB */
    EVT_SRC_TMR6_4_GCMP_C        = 210U,    /* TMR6_4_GCMC */
    EVT_SRC_TMR6_4_GCMP_D        = 211U,    /* TMR6_4_GCMD */
    EVT_SRC_TMR6_4_GCMP_E        = 212U,    /* TMR6_4_GCME */
    EVT_SRC_TMR6_4_GCMP_F        = 213U,    /* TMR6_4_GCMF */
    EVT_SRC_TMR6_4_OVF           = 214U,    /* TMR6_4_GOVF */
    EVT_SRC_TMR6_4_UDF           = 215U,    /* TMR6_4_GUDF */
    EVT_SRC_TMR6_4_SCMP_A        = 219U,    /* TMR6_4_SCMA */
    EVT_SRC_TMR6_4_SCMP_B        = 220U,    /* TMR6_4_SCMB */
    EVT_SRC_TMR6_5_GCMP_A        = 224U,    /* TMR6_5_GCMA */
    EVT_SRC_TMR6_5_GCMP_B        = 225U,    /* TMR6_5_GCMB */
    EVT_SRC_TMR6_5_GCMP_C        = 226U,    /* TMR6_5_GCMC */
    EVT_SRC_TMR6_5_GCMP_D        = 227U,    /* TMR6_5_GCMD */
    EVT_SRC_TMR6_5_GCMP_E        = 228U,    /* TMR6_5_GCME */
    EVT_SRC_TMR6_5_GCMP_F        = 229U,    /* TMR6_5_GCMF */
    EVT_SRC_TMR6_5_OVF           = 230U,    /* TMR6_5_GOVF */
    EVT_SRC_TMR6_5_UDF           = 231U,    /* TMR6_5_GUDF */
    EVT_SRC_TMR6_5_SCMP_A        = 235U,    /* TMR6_5_SCMA */
    EVT_SRC_TMR6_5_SCMP_B        = 236U,    /* TMR6_5_SCMB */
    /*  TIMERA_1  */
    EVT_SRC_TMRA_1_OVF           = 237U,    /* TMRA_1_OVF */
    EVT_SRC_TMRA_1_UDF           = 238U,    /* TMRA_1_UDF */
    EVT_SRC_TMRA_1_CMP           = 239U,    /* TMRA_1_CMP */
    /*  TIMER6_6  */
    EVT_SRC_TMR6_6_GCMP_A        = 240U,    /* TMR6_6_GCMA */
    EVT_SRC_TMR6_6_GCMP_B        = 241U,    /* TMR6_6_GCMB */
    EVT_SRC_TMR6_6_GCMP_C        = 242U,    /* TMR6_6_GCMC */
    EVT_SRC_TMR6_6_GCMP_D        = 243U,    /* TMR6_6_GCMD */
    EVT_SRC_TMR6_6_GCMP_E        = 244U,    /* TMR6_6_GCME */
    EVT_SRC_TMR6_6_GCMP_F        = 245U,    /* TMR6_6_GCMF */
    EVT_SRC_TMR6_6_OVF           = 246U,    /* TMR6_6_GOVF */
    EVT_SRC_TMR6_6_UDF           = 247U,    /* TMR6_6_GUDF */
    EVT_SRC_TMR6_6_SCMP_A        = 251U,    /* TMR6_6_SCMA */
    EVT_SRC_TMR6_6_SCMP_B        = 252U,    /* TMR6_6_SCMB */
    /*  TIMERA_2  */
    EVT_SRC_TMRA_2_OVF           = 253U,    /* TMRA_2_OVF */
    EVT_SRC_TMRA_2_UDF           = 254U,    /* TMRA_2_UDF */
    EVT_SRC_TMRA_2_CMP           = 255U,    /* TMRA_2_CMP */
    /*  TIMER6_7  */
    EVT_SRC_TMR6_7_GCMP_A        = 256U,    /* TMR6_7_GCMA */
    EVT_SRC_TMR6_7_GCMP_B        = 257U,    /* TMR6_7_GCMB */
    EVT_SRC_TMR6_7_GCMP_C        = 258U,    /* TMR6_7_GCMC */
    EVT_SRC_TMR6_7_GCMP_D        = 259U,    /* TMR6_7_GCMD */
    EVT_SRC_TMR6_7_GCMP_E        = 260U,    /* TMR6_7_GCME */
    EVT_SRC_TMR6_7_GCMP_F        = 261U,    /* TMR6_7_GCMF */
    EVT_SRC_TMR6_7_OVF           = 262U,    /* TMR6_7_GOVF */
    EVT_SRC_TMR6_7_UDF           = 263U,    /* TMR6_7_GUDF */
    EVT_SRC_TMR6_7_SCMP_A        = 267U,    /* TMR6_7_SCMA */
    EVT_SRC_TMR6_7_SCMP_B        = 268U,    /* TMR6_7_SCMB */
    /*  TIMERA_3  */
    EVT_SRC_TMRA_3_OVF           = 269U,    /* TMRA_3_OVF */
    EVT_SRC_TMRA_3_UDF           = 270U,    /* TMRA_3_UDF */
    EVT_SRC_TMRA_3_CMP           = 271U,    /* TMRA_3_CMP */
    /*  TIMER6_8  */
    EVT_SRC_TMR6_8_GCMP_A        = 272U,    /* TMR6_8_GCMA */
    EVT_SRC_TMR6_8_GCMP_B        = 273U,    /* TMR6_8_GCMB */
    EVT_SRC_TMR6_8_GCMP_C        = 274U,    /* TMR6_8_GCMC */
    EVT_SRC_TMR6_8_GCMP_D        = 275U,    /* TMR6_8_GCMD */
    EVT_SRC_TMR6_8_GCMP_E        = 276U,    /* TMR6_8_GCME */
    EVT_SRC_TMR6_8_GCMP_F        = 277U,    /* TMR6_8_GCMF */
    EVT_SRC_TMR6_8_OVF           = 278U,    /* TMR6_8_GOVF */
    EVT_SRC_TMR6_8_UDF           = 279U,    /* TMR6_8_GUDF */
    EVT_SRC_TMR6_8_SCMP_A        = 283U,    /* TMR6_8_SCMA */
    EVT_SRC_TMR6_8_SCMP_B        = 284U,    /* TMR6_8_SCMB */
    /*  TIMERA_4  */
    EVT_SRC_TMRA_4_OVF           = 285U,    /* TMRA_4_OVF */
    EVT_SRC_TMRA_4_UDF           = 286U,    /* TMRA_4_UDF */
    EVT_SRC_TMRA_4_CMP           = 287U,    /* TMRA_4_CMP */
    /*  AOS_STRG  */
    EVT_SRC_AOS_STRG             = 299U,    /* AOS_STRG */
    /*  USART1 USART2  */
    EVT_SRC_USART1_EI            = 300U,    /* USART_1_EI */
    EVT_SRC_USART1_RI            = 301U,    /* USART_1_RI */
    EVT_SRC_USART1_TI            = 302U,    /* USART_1_TI */
    EVT_SRC_USART1_TCI           = 303U,    /* USART_1_TCI */
    EVT_SRC_USART1_RTO           = 304U,    /* USART_1_RTO */
    EVT_SRC_USART2_EI            = 305U,    /* USART_2_EI */
    EVT_SRC_USART2_RI            = 306U,    /* USART_2_RI */
    EVT_SRC_USART2_TI            = 307U,    /* USART_2_TI */
    EVT_SRC_USART2_TCI           = 308U,    /* USART_2_TCI */
    EVT_SRC_USART2_RTO           = 309U,    /* USART_2_RTO */
    /*  SPI1 SPI2  */
    EVT_SRC_SPI1_SPRI            = 310U,    /* SPI_1_SPRI */
    EVT_SRC_SPI1_SPTI            = 311U,    /* SPI_1_SPTI */
    EVT_SRC_SPI1_SPII            = 312U,    /* SPI_1_SPII */
    EVT_SRC_SPI1_SPEI            = 313U,    /* SPI_1_SPEI */
    EVT_SRC_SPI1_SPEND           = 314U,    /* SPI_1_SPEND */
    EVT_SRC_SPI2_SPRI            = 315U,    /* SPI_2_SPRI */
    EVT_SRC_SPI2_SPTI            = 316U,    /* SPI_2_SPTI */
    EVT_SRC_SPI2_SPII            = 317U,    /* SPI_2_SPII */
    EVT_SRC_SPI2_SPEI            = 318U,    /* SPI_2_SPEI */
    EVT_SRC_SPI2_SPEND           = 319U,    /* SPI_2_SPEND */
    /*  TIMERA_5 TIMERA_6 TIMERA_7 TIMERA_8  */
    EVT_SRC_TMRA_5_OVF           = 320U,    /* TMRA_5_OVF */
    EVT_SRC_TMRA_5_UDF           = 321U,    /* TMRA_5_UDF */
    EVT_SRC_TMRA_5_CMP           = 322U,    /* TMRA_5_CMP */
    EVT_SRC_TMRA_6_OVF           = 323U,    /* TMRA_6_OVF */
    EVT_SRC_TMRA_6_UDF           = 324U,    /* TMRA_6_UDF */
    EVT_SRC_TMRA_6_CMP           = 325U,    /* TMRA_6_CMP */
    EVT_SRC_TMRA_7_OVF           = 326U,    /* TMRA_7_OVF */
    EVT_SRC_TMRA_7_UDF           = 327U,    /* TMRA_7_UDF */
    EVT_SRC_TMRA_7_CMP           = 328U,    /* TMRA_7_CMP */
    EVT_SRC_TMRA_8_OVF           = 329U,    /* TMRA_8_OVF */
    EVT_SRC_TMRA_8_UDF           = 330U,    /* TMRA_8_UDF */
    EVT_SRC_TMRA_8_CMP           = 331U,    /* TMRA_8_CMP */
    /*  USART3 USART4  */
    EVT_SRC_USART3_EI            = 332U,    /* USART_3_EI */
    EVT_SRC_USART3_RI            = 333U,    /* USART_3_RI */
    EVT_SRC_USART3_TI            = 334U,    /* USART_3_TI */
    EVT_SRC_USART3_TCI           = 335U,    /* USART_3_TCI */
    EVT_SRC_USART4_EI            = 336U,    /* USART_4_EI */
    EVT_SRC_USART4_RI            = 337U,    /* USART_4_RI */
    EVT_SRC_USART4_TI            = 338U,    /* USART_4_TI */
    EVT_SRC_USART4_TCI           = 339U,    /* USART_4_TCI */
    /*  SPI3 SPI4  */
    EVT_SRC_SPI3_SPRI            = 342U,    /* SPI_3_SPRI */
    EVT_SRC_SPI3_SPTI            = 343U,    /* SPI_3_SPTI */
    EVT_SRC_SPI3_SPII            = 344U,    /* SPI_3_SPII */
    EVT_SRC_SPI3_SPEI            = 345U,    /* SPI_3_SPEI */
    EVT_SRC_SPI3_SPEND           = 346U,    /* SPI_3_SPEND */
    EVT_SRC_SPI4_SPRI            = 347U,    /* SPI_4_SPRI */
    EVT_SRC_SPI4_SPTI            = 348U,    /* SPI_4_SPTI */
    EVT_SRC_SPI4_SPII            = 349U,    /* SPI_4_SPII */
    EVT_SRC_SPI4_SPEI            = 350U,    /* SPI_4_SPEI */
    EVT_SRC_SPI4_SPEND           = 351U,    /* SPI_4_SPEND */
    /*  TIMERA_9 TIMERA_10 TIMERA_11 TIMERA_12  */
    EVT_SRC_TMRA_9_OVF           = 352U,    /* TMRA_9_OVF */
    EVT_SRC_TMRA_9_UDF           = 353U,    /* TMRA_9_UDF */
    EVT_SRC_TMRA_9_CMP           = 354U,    /* TMRA_9_CMP */
    EVT_SRC_TMRA_10_OVF          = 355U,    /* TMRA_10_OVF */
    EVT_SRC_TMRA_10_UDF          = 356U,    /* TMRA_10_UDF */
    EVT_SRC_TMRA_10_CMP          = 357U,    /* TMRA_10_CMP */
    EVT_SRC_TMRA_11_OVF          = 358U,    /* TMRA_11_OVF */
    EVT_SRC_TMRA_11_UDF          = 359U,    /* TMRA_11_UDF */
    EVT_SRC_TMRA_11_CMP          = 360U,    /* TMRA_11_CMP */
    EVT_SRC_TMRA_12_OVF          = 361U,    /* TMRA_12_OVF */
    EVT_SRC_TMRA_12_UDF          = 362U,    /* TMRA_12_UDF */
    EVT_SRC_TMRA_12_CMP          = 363U,    /* TMRA_12_CMP */
    /*  USART5 USART6  */
    EVT_SRC_USART5_BRKWKPI       = 364U,    /* USART_5_BRKWKPI */
    EVT_SRC_USART5_EI            = 365U,    /* USART_5_EI */
    EVT_SRC_USART5_RI            = 366U,    /* USART_5_RI */
    EVT_SRC_USART5_TI            = 367U,    /* USART_5_TI */
    EVT_SRC_USART5_TCI           = 368U,    /* USART_5_TCI */
    EVT_SRC_USART6_EI            = 369U,    /* USART_6_EI */
    EVT_SRC_USART6_RI            = 370U,    /* USART_6_RI */
    EVT_SRC_USART6_TI            = 371U,    /* USART_6_TI */
    EVT_SRC_USART6_TCI           = 372U,    /* USART_6_TCI */
    EVT_SRC_USART6_RTO           = 373U,    /* USART_6_RTO */
    /*  SPI5 SPI6  */
    EVT_SRC_SPI5_SPRI            = 374U,    /* SPI_5_SPRI */
    EVT_SRC_SPI5_SPTI            = 375U,    /* SPI_5_SPTI */
    EVT_SRC_SPI5_SPII            = 376U,    /* SPI_5_SPII */
    EVT_SRC_SPI5_SPEI            = 377U,    /* SPI_5_SPEI */
    EVT_SRC_SPI5_SPEND           = 378U,    /* SPI_5_SPEND */
    EVT_SRC_SPI6_SPRI            = 379U,    /* SPI_6_SPRI */
    EVT_SRC_SPI6_SPTI            = 380U,    /* SPI_6_SPTI */
    EVT_SRC_SPI6_SPII            = 381U,    /* SPI_6_SPII */
    EVT_SRC_SPI6_SPEI            = 382U,    /* SPI_6_SPEI */
    EVT_SRC_SPI6_SPEND           = 383U,    /* SPI_6_SPEND */
    /*  I2S1 I2S2  */
    EVT_SRC_I2S1_TXIRQOUT        = 384U,    /* I2S_1_TXIRQOUT */
    EVT_SRC_I2S1_RXIRQOUT        = 385U,    /* I2S_1_RXIRQOUT */
    EVT_SRC_I2S2_TXIRQOUT        = 387U,    /* I2S_2_TXIRQOUT */
    EVT_SRC_I2S2_RXIRQOUT        = 388U,    /* I2S_2_RXIRQOUT */
    /*  USART7 USART8  */
    EVT_SRC_USART7_EI            = 390U,    /* USART_7_EI */
    EVT_SRC_USART7_RI            = 391U,    /* USART_7_RI */
    EVT_SRC_USART7_TI            = 392U,    /* USART_7_TI */
    EVT_SRC_USART7_TCI           = 393U,    /* USART_7_TCI */
    EVT_SRC_USART7_RTO           = 394U,    /* USART_7_RTO */
    EVT_SRC_USART8_EI            = 395U,    /* USART_8_EI */
    EVT_SRC_USART8_RI            = 396U,    /* USART_8_RI */
    EVT_SRC_USART8_TI            = 397U,    /* USART_8_TI */
    EVT_SRC_USART8_TCI           = 398U,    /* USART_8_TCI */
    /*  HASH  */
    EVT_SRC_HASH                 = 401U,    /* HASH_INT */
    /*  SDIOC  */
    EVT_SRC_SDIOC1_DMAR          = 402U,    /* SDIOC_1_DMAR */
    EVT_SRC_SDIOC1_DMAW          = 403U,    /* SDIOC_1_DMAW */
    EVT_SRC_SDIOC2_DMAR          = 405U,    /* SDIOC_2_DMAR */
    EVT_SRC_SDIOC2_DMAW          = 406U,    /* SDIOC_2_DMAW */
    /*  EVENT PORT  */
    EVT_SRC_EVENT_PORT1          = 408U,    /* EVENT_PORT1 */
    EVT_SRC_EVENT_PORT2          = 409U,    /* EVENT_PORT2 */
    EVT_SRC_EVENT_PORT3          = 410U,    /* EVENT_PORT3 */
    EVT_SRC_EVENT_PORT4          = 411U,    /* EVENT_PORT4 */
    /*  ETHER  */
    EVT_SRC_ETH_PPS_OUT_0        = 414U,    /* ETH_PPS_OUT_0 */
    EVT_SRC_ETH_PPS_OUT_1        = 415U,    /* ETH_PPS_OUT_1 */
    /*  I2S3 I2S4  */
    EVT_SRC_I2S3_TXIRQOUT        = 416U,    /* I2S_3_TXIRQOUT */
    EVT_SRC_I2S3_RXIRQOUT        = 417U,    /* I2S_3_RXIRQOUT */
    EVT_SRC_I2S4_TXIRQOUT        = 419U,    /* I2S_4_TXIRQOUT */
    EVT_SRC_I2S4_RXIRQOUT        = 420U,    /* I2S_4_RXIRQOUT */
    /*  USART9 USART10  */
    EVT_SRC_USART9_EI            = 422U,    /* USART_9_EI */
    EVT_SRC_USART9_RI            = 423U,    /* USART_9_RI */
    EVT_SRC_USART9_TI            = 424U,    /* USART_9_TI */
    EVT_SRC_USART9_TCI           = 425U,    /* USART_9_TCI */
    EVT_SRC_USART10_BRKWKPI      = 426U,    /* USART_10_BRKWKPI */
    EVT_SRC_USART10_EI           = 427U,    /* USART_10_EI */
    EVT_SRC_USART10_RI           = 428U,    /* USART_10_RI */
    EVT_SRC_USART10_TI           = 429U,    /* USART_10_TI */
    EVT_SRC_USART10_TCI          = 430U,    /* USART_10_TCI */
    /*  I2C1 I2C2 I2C3  */
    EVT_SRC_I2C1_RXI             = 432U,    /* I2C_1_RXI */
    EVT_SRC_I2C1_TXI             = 433U,    /* I2C_1_TXI */
    EVT_SRC_I2C1_TEI             = 434U,    /* I2C_1_TEI */
    EVT_SRC_I2C1_EEI             = 435U,    /* I2C_1_EEI */
    EVT_SRC_I2C2_RXI             = 436U,    /* I2C_2_RXI */
    EVT_SRC_I2C2_TXI             = 437U,    /* I2C_2_TXI */
    EVT_SRC_I2C2_TEI             = 438U,    /* I2C_2_TEI */
    EVT_SRC_I2C2_EEI             = 439U,    /* I2C_2_EEI */
    EVT_SRC_I2C3_RXI             = 440U,    /* I2C_3_RXI */
    EVT_SRC_I2C3_TXI             = 441U,    /* I2C_3_TXI */
    EVT_SRC_I2C3_TEI             = 442U,    /* I2C_3_TEI */
    EVT_SRC_I2C3_EEI             = 443U,    /* I2C_3_EEI */
    /*  ACMP  */
    EVT_SRC_CMP1                 = 444U,    /* CMP1 */
    EVT_SRC_CMP2                 = 445U,    /* CMP2 */
    EVT_SRC_CMP3                 = 446U,    /* CMP3 */
    EVT_SRC_CMP4                 = 447U,    /* CMP4 */
    /*  I2C4 I2C5 I2C6  */
    EVT_SRC_I2C4_RXI             = 448U,    /* I2C_4_RXI */
    EVT_SRC_I2C4_TXI             = 449U,    /* I2C_4_TXI */
    EVT_SRC_I2C4_TEI             = 450U,    /* I2C_4_TEI */
    EVT_SRC_I2C4_EEI             = 451U,    /* I2C_4_EEI */
    EVT_SRC_I2C5_RXI             = 452U,    /* I2C_5_RXI */
    EVT_SRC_I2C5_TXI             = 453U,    /* I2C_5_TXI */
    EVT_SRC_I2C5_TEI             = 454U,    /* I2C_5_TEI */
    EVT_SRC_I2C5_EEI             = 455U,    /* I2C_5_EEI */
    EVT_SRC_I2C6_RXI             = 456U,    /* I2C_6_RXI */
    EVT_SRC_I2C6_TXI             = 457U,    /* I2C_6_TXI */
    EVT_SRC_I2C6_TEI             = 458U,    /* I2C_6_TEI */
    EVT_SRC_I2C6_EEI             = 459U,    /* I2C_6_EEI */
    /*  LVD  */
    EVT_SRC_LVD1                = 461U,    /* LVD1 */
    EVT_SRC_LVD2                = 462U,    /* LVD2 */
    /*  OTS  */
    EVT_SRC_OTS                  = 463U,    /* OTS */
    /*  WDT  */
    EVT_SRC_WDT_REFUDF           = 467U,    /* WDT_REFUDF */
    /*  ADC  */
    EVT_SRC_ADC1_EOCA            = 480U,    /* ADC_1_EOCA */
    EVT_SRC_ADC1_EOCB            = 481U,    /* ADC_1_EOCB */
    EVT_SRC_ADC1_CMP0            = 482U,    /* ADC_1_CMP0 */
    EVT_SRC_ADC1_CMP1            = 483U,    /* ADC_1_CMP1 */
    EVT_SRC_ADC2_EOCA            = 484U,    /* ADC_2_EOCA */
    EVT_SRC_ADC2_EOCB            = 485U,    /* ADC_2_EOCB */
    EVT_SRC_ADC2_CMP0            = 486U,    /* ADC_2_CMP0 */
    EVT_SRC_ADC2_CMP1            = 487U,    /* ADC_2_CMP1 */
    EVT_SRC_ADC3_EOCA            = 488U,    /* ADC_3_EOCA */
    EVT_SRC_ADC3_EOCB            = 489U,    /* ADC_3_EOCB */
    EVT_SRC_ADC3_CMP0            = 490U,    /* ADC_3_CMP0 */
    EVT_SRC_ADC3_CMP1            = 491U,    /* ADC_3_CMP1 */
    /*  TRNG  */
    EVT_SRC_TRNG_END             = 492U,    /* TRNG_END */
    EVT_SRC_MAX                  = 511U,
} en_event_src_t;

/**
 *******************************************************************************
 ** \brief Interrupt number enumeration
 ******************************************************************************/
typedef enum {
    INT_SRC_SWI_IRQ0             = 0U,
    INT_SRC_SWI_IRQ1             = 1U,
    INT_SRC_SWI_IRQ2             = 2U,
    INT_SRC_SWI_IRQ3             = 3U,
    INT_SRC_SWI_IRQ4             = 4U,
    INT_SRC_SWI_IRQ5             = 5U,
    INT_SRC_SWI_IRQ6             = 6U,
    INT_SRC_SWI_IRQ7             = 7U,
    INT_SRC_SWI_IRQ8             = 8U,
    INT_SRC_SWI_IRQ9             = 9U,
    INT_SRC_SWI_IRQ10            = 10U,
    INT_SRC_SWI_IRQ11            = 11U,
    INT_SRC_SWI_IRQ12            = 12U,
    INT_SRC_SWI_IRQ13            = 13U,
    INT_SRC_SWI_IRQ14            = 14U,
    INT_SRC_SWI_IRQ15            = 15U,
    INT_SRC_SWI_IRQ16            = 16U,
    INT_SRC_SWI_IRQ17            = 17U,
    INT_SRC_SWI_IRQ18            = 18U,
    INT_SRC_SWI_IRQ19            = 19U,
    INT_SRC_SWI_IRQ20            = 20U,
    INT_SRC_SWI_IRQ21            = 21U,
    INT_SRC_SWI_IRQ22            = 22U,
    INT_SRC_SWI_IRQ23            = 23U,
    INT_SRC_SWI_IRQ24            = 24U,
    INT_SRC_SWI_IRQ25            = 25U,
    INT_SRC_SWI_IRQ26            = 26U,
    INT_SRC_SWI_IRQ27            = 27U,
    INT_SRC_SWI_IRQ28            = 28U,
    INT_SRC_SWI_IRQ29            = 29U,
    INT_SRC_SWI_IRQ30            = 30U,
    INT_SRC_SWI_IRQ31            = 31U,
    /*  External Interrupt   */
    INT_SRC_PORT_EIRQ0           = 0U,      /* PORT_EIRQ0 */
    INT_SRC_PORT_EIRQ1           = 1U,      /* PORT_EIRQ1 */
    INT_SRC_PORT_EIRQ2           = 2U,      /* PORT_EIRQ2 */
    INT_SRC_PORT_EIRQ3           = 3U,      /* PORT_EIRQ3 */
    INT_SRC_PORT_EIRQ4           = 4U,      /* PORT_EIRQ4 */
    INT_SRC_PORT_EIRQ5           = 5U,      /* PORT_EIRQ5 */
    INT_SRC_PORT_EIRQ6           = 6U,      /* PORT_EIRQ6 */
    INT_SRC_PORT_EIRQ7           = 7U,      /* PORT_EIRQ7 */
    INT_SRC_PORT_EIRQ8           = 8U,      /* PORT_EIRQ8 */
    INT_SRC_PORT_EIRQ9           = 9U,      /* PORT_EIRQ9 */
    INT_SRC_PORT_EIRQ10          = 10U,     /* PORT_EIRQ10 */
    INT_SRC_PORT_EIRQ11          = 11U,     /* PORT_EIRQ11 */
    INT_SRC_PORT_EIRQ12          = 12U,     /* PORT_EIRQ12 */
    INT_SRC_PORT_EIRQ13          = 13U,     /* PORT_EIRQ13 */
    INT_SRC_PORT_EIRQ14          = 14U,     /* PORT_EIRQ14 */
    INT_SRC_PORT_EIRQ15          = 15U,     /* PORT_EIRQ15 */
    /*  DMA_1  */
    INT_SRC_DMA1_TC0             = 32U,     /* DMA_1_TC0 */
    INT_SRC_DMA1_TC1             = 33U,     /* DMA_1_TC1 */
    INT_SRC_DMA1_TC2             = 34U,     /* DMA_1_TC2 */
    INT_SRC_DMA1_TC3             = 35U,     /* DMA_1_TC3 */
    INT_SRC_DMA1_TC4             = 36U,     /* DMA_1_TC4 */
    INT_SRC_DMA1_TC5             = 37U,     /* DMA_1_TC5 */
    INT_SRC_DMA1_TC6             = 38U,     /* DMA_1_TC6 */
    INT_SRC_DMA1_TC7             = 39U,     /* DMA_1_TC7 */
    INT_SRC_DMA1_BTC0            = 40U,     /* DMA_1_BTC0 */
    INT_SRC_DMA1_BTC1            = 41U,     /* DMA_1_BTC1 */
    INT_SRC_DMA1_BTC2            = 42U,     /* DMA_1_BTC2 */
    INT_SRC_DMA1_BTC3            = 43U,     /* DMA_1_BTC3 */
    INT_SRC_DMA1_BTC4            = 44U,     /* DMA_1_BTC4 */
    INT_SRC_DMA1_BTC5            = 45U,     /* DMA_1_BTC5 */
    INT_SRC_DMA1_BTC6            = 46U,     /* DMA_1_BTC6 */
    INT_SRC_DMA1_BTC7            = 47U,     /* DMA_1_BTC7 */
    INT_SRC_DMA1_ERR             = 48U,     /* DMA_1_ERR */
    /*  EFM  */
    INT_SRC_EFM_PEERR            = 49U,     /* EFM_PEERR */
    INT_SRC_EFM_RDCOL            = 50U,     /* EFM_RDCOL */
    INT_SRC_EFM_OPTEND           = 51U,     /* EFM_OPTEND */
    /*  QSPI  */
    INT_SRC_QSPI_INTR            = 54U,     /* QSPI_INTR */
    /*  DCU  */
    INT_SRC_DCU1                 = 55U,     /* DCU1 */
    INT_SRC_DCU2                 = 56U,     /* DCU2 */
    INT_SRC_DCU3                 = 57U,     /* DCU3 */
    INT_SRC_DCU4                 = 58U,     /* DCU4 */
    INT_SRC_DCU5                 = 59U,     /* DCU5 */
    INT_SRC_DCU6                 = 60U,     /* DCU6 */
    INT_SRC_DCU7                 = 61U,     /* DCU7 */
    INT_SRC_DCU8                 = 62U,     /* DCU8 */
    /*  DMA2  */
    INT_SRC_DMA2_TC0             = 64U,     /* DMA_2_TC0 */
    INT_SRC_DMA2_TC1             = 65U,     /* DMA_2_TC1 */
    INT_SRC_DMA2_TC2             = 66U,     /* DMA_2_TC2 */
    INT_SRC_DMA2_TC3             = 67U,     /* DMA_2_TC3 */
    INT_SRC_DMA2_TC4             = 68U,     /* DMA_2_TC4 */
    INT_SRC_DMA2_TC5             = 69U,     /* DMA_2_TC5 */
    INT_SRC_DMA2_TC6             = 70U,     /* DMA_2_TC6 */
    INT_SRC_DMA2_TC7             = 71U,     /* DMA_2_TC7 */
    INT_SRC_DMA2_BTC0            = 72U,     /* DMA_2_BTC0 */
    INT_SRC_DMA2_BTC1            = 73U,     /* DMA_2_BTC1 */
    INT_SRC_DMA2_BTC2            = 74U,     /* DMA_2_BTC2 */
    INT_SRC_DMA2_BTC3            = 75U,     /* DMA_2_BTC3 */
    INT_SRC_DMA2_BTC4            = 76U,     /* DMA_2_BTC4 */
    INT_SRC_DMA2_BTC5            = 77U,     /* DMA_2_BTC5 */
    INT_SRC_DMA2_BTC6            = 78U,     /* DMA_2_BTC6 */
    INT_SRC_DMA2_BTC7            = 79U,     /* DMA_2_BTC7 */
    INT_SRC_DMA2_ERR             = 80U,     /* DMA_2_ERR */
    /*  MAU  */
    INT_SRC_MAU_SQRT             = 83U,     /* MAU_SQRT */
    /*  DVP  */
    INT_SRC_DVP_FRAMSTA          = 84U,     /* DVP_FRAMSTA */
    INT_SRC_DVP_LINESTA          = 85U,     /* DVP_LINESTA */
    INT_SRC_DVP_LINEEND          = 86U,     /* DVP_LINEEND */
    INT_SRC_DVP_FRAMEND          = 87U,     /* DVP_FRAMEND */
    INT_SRC_DVP_SQUERR           = 88U,     /* DVP_SQUERR */
    INT_SRC_DVP_FIFOERR          = 89U,     /* DVP_FIFOERR */
    /*  FMAC  */
    INT_SRC_FMAC_1               = 91U,     /* FMAC_1_FIR */
    INT_SRC_FMAC_2               = 92U,     /* FMAC_2_FIR */
    INT_SRC_FMAC_3               = 93U,     /* FMAC_3_FIR */
    INT_SRC_FMAC_4               = 94U,     /* FMAC_4_FIR */
    /*  TIMER0  */
    INT_SRC_TMR0_1_CMP_A         = 96U,     /* TMR0_1_CMPA */
    INT_SRC_TMR0_1_CMP_B         = 97U,     /* TMR0_1_CMPB */
    INT_SRC_TMR0_2_CMP_A         = 98U,     /* TMR0_2_CMPA */
    INT_SRC_TMR0_2_CMP_B         = 99U,     /* TMR0_2_CMPB */
    /*  TIMER2  */
    INT_SRC_TMR2_1_CMP_A         = 100U,    /* TMR2_1_CMPA  */
    INT_SRC_TMR2_1_CMP_B         = 101U,    /* TMR2_1_CMPB  */
    INT_SRC_TMR2_1_OVF_A         = 102U,    /* TMR2_1_OVFA  */
    INT_SRC_TMR2_1_OVF_B         = 103U,    /* TMR2_1_OVFB  */
    INT_SRC_TMR2_2_CMP_A         = 104U,    /* TMR2_2_CMPA  */
    INT_SRC_TMR2_2_CMP_B         = 105U,    /* TMR2_2_CMPB  */
    INT_SRC_TMR2_2_OVF_A         = 106U,    /* TMR2_2_OVFA  */
    INT_SRC_TMR2_2_OVF_B         = 107U,    /* TMR2_2_OVFB  */
    INT_SRC_TMR2_3_CMP_A         = 108U,    /* TMR2_3_CMPA  */
    INT_SRC_TMR2_3_CMP_B         = 109U,    /* TMR2_3_CMPB  */
    INT_SRC_TMR2_3_OVF_A         = 110U,    /* TMR2_3_OVFA  */
    INT_SRC_TMR2_3_OVF_B         = 111U,    /* TMR2_3_OVFB  */
    INT_SRC_TMR2_4_CMP_A         = 112U,    /* TMR2_4_CMPA  */
    INT_SRC_TMR2_4_CMP_B         = 113U,    /* TMR2_4_CMPB  */
    INT_SRC_TMR2_4_OVF_A         = 114U,    /* TMR2_4_OVFA  */
    INT_SRC_TMR2_4_OVF_B         = 115U,    /* TMR2_4_OVFB  */
    /*  RTC  */
    INT_SRC_RTC_TP               = 120U,     /* RTC_TP */
    INT_SRC_RTC_ALM              = 121U,     /* RTC_ALM */
    INT_SRC_RTC_PRD              = 122U,     /* RTC_PRD */
    /*  XTAL  */
    INT_SRC_XTAL_STOP            = 125U,     /* XTAL_STOP */
    /*  WKTM  */
    INT_SRC_WKTM_PRD             = 126U,     /* WKTM_PRD */
    /*  SWDT  */
    INT_SRC_SWDT_REFUDF          = 127U,     /* SWDT_REFUDF */
    /*  TIMER6_1  */
    INT_SRC_TMR6_1_GCMP_A        = 128U,     /* TMR6_1_GCMA */
    INT_SRC_TMR6_1_GCMP_B        = 129U,     /* TMR6_1_GCMB */
    INT_SRC_TMR6_1_GCMP_C        = 130U,     /* TMR6_1_GCMC */
    INT_SRC_TMR6_1_GCMP_D        = 131U,     /* TMR6_1_GCMD */
    INT_SRC_TMR6_1_GCMP_E        = 132U,     /* TMR6_1_GCME */
    INT_SRC_TMR6_1_GCMP_F        = 133U,     /* TMR6_1_GCMF */
    INT_SRC_TMR6_1_OVF           = 134U,     /* TMR6_1_GOVF */
    INT_SRC_TMR6_1_UDF           = 135U,     /* TMR6_1_GUDF */
    /*  TIMER4_1  */
    INT_SRC_TMR4_1_GCMP_UH       = 136U,     /* TMR4_1_GCMUH */
    INT_SRC_TMR4_1_GCMP_UL       = 137U,     /* TMR4_1_GCMUL */
    INT_SRC_TMR4_1_GCMP_VH       = 138U,     /* TMR4_1_GCMVH */
    INT_SRC_TMR4_1_GCMP_VL       = 139U,     /* TMR4_1_GCMVL */
    INT_SRC_TMR4_1_GCMP_WH       = 140U,     /* TMR4_1_GCMWH */
    INT_SRC_TMR4_1_GCMP_WL       = 141U,     /* TMR4_1_GCMWL */
    INT_SRC_TMR4_1_OVF           = 142U,     /* TMR4_1_GOVF */
    INT_SRC_TMR4_1_UDF           = 143U,     /* TMR4_1_GUDF */
    /*  TIMER6_2  */
    INT_SRC_TMR6_2_GCMP_A        = 144U,     /* TMR6_2_GCMA */
    INT_SRC_TMR6_2_GCMP_B        = 145U,     /* TMR6_2_GCMB */
    INT_SRC_TMR6_2_GCMP_C        = 146U,     /* TMR6_2_GCMC */
    INT_SRC_TMR6_2_GCMP_D        = 147U,     /* TMR6_2_GCMD */
    INT_SRC_TMR6_2_GCMP_E        = 148U,     /* TMR6_2_GCME */
    INT_SRC_TMR6_2_GCMP_F        = 149U,     /* TMR6_2_GCMF */
    INT_SRC_TMR6_2_OVF           = 150U,     /* TMR6_2_GOVF */
    INT_SRC_TMR6_2_UDF           = 151U,     /* TMR6_2_GUDF */
    /*  TIMER4_2  */
    INT_SRC_TMR4_2_GCMP_UH       = 152U,     /* TMR4_2_GCMUH */
    INT_SRC_TMR4_2_GCMP_UL       = 153U,     /* TMR4_2_GCMUL */
    INT_SRC_TMR4_2_GCMP_VH       = 154U,     /* TMR4_2_GCMVH */
    INT_SRC_TMR4_2_GCMP_VL       = 155U,     /* TMR4_2_GCMVL */
    INT_SRC_TMR4_2_GCMP_WH       = 156U,     /* TMR4_2_GCMWH */
    INT_SRC_TMR4_2_GCMP_WL       = 157U,     /* TMR4_2_GCMWL */
    INT_SRC_TMR4_2_OVF           = 158U,     /* TMR4_2_GOVF */
    INT_SRC_TMR4_2_UDF           = 159U,     /* TMR4_2_GUDF */
    /*  TIMER6_3  */
    INT_SRC_TMR6_3_GCMP_A        = 160U,     /* TMR6_3_GCMA */
    INT_SRC_TMR6_3_GCMP_B        = 161U,     /* TMR6_3_GCMB */
    INT_SRC_TMR6_3_GCMP_C        = 162U,     /* TMR6_3_GCMC */
    INT_SRC_TMR6_3_GCMP_D        = 163U,     /* TMR6_3_GCMD */
    INT_SRC_TMR6_3_GCMP_E        = 164U,     /* TMR6_3_GCME */
    INT_SRC_TMR6_3_GCMP_F        = 165U,     /* TMR6_3_GCMF */
    INT_SRC_TMR6_3_OVF           = 166U,     /* TMR6_3_GOVF */
    INT_SRC_TMR6_3_UDF           = 167U,     /* TMR6_3_GUDF */
    /*  TIMER4_3  */
    INT_SRC_TMR4_3_GCMP_UH       = 168U,     /* TMR4_3_GCMUH */
    INT_SRC_TMR4_3_GCMP_UL       = 169U,     /* TMR4_3_GCMUL */
    INT_SRC_TMR4_3_GCMP_VH       = 170U,     /* TMR4_3_GCMVH */
    INT_SRC_TMR4_3_GCMP_VL       = 171U,     /* TMR4_3_GCMVL */
    INT_SRC_TMR4_3_GCMP_WH       = 172U,     /* TMR4_3_GCMWH */
    INT_SRC_TMR4_3_GCMP_WL       = 173U,     /* TMR4_3_GCMWL */
    INT_SRC_TMR4_3_OVF           = 174U,     /* TMR4_3_GOVF */
    INT_SRC_TMR4_3_UDF           = 175U,     /* TMR4_3_GUDF */
    /*  TIMER6_1  */
    INT_SRC_TMR6_1_DTE           = 176U,     /* TMR6_1_GDTE */
    INT_SRC_TMR6_1_SCMP_A        = 179U,     /* TMR6_1_SCMA */
    INT_SRC_TMR6_1_SCMP_B        = 180U,     /* TMR6_1_SCMB */
    /*  TIMER4_1  */
    INT_SRC_TMR4_1_RELOAD_U      = 181U,     /* TMR4_1_RLOU */
    INT_SRC_TMR4_1_RELOAD_V      = 182U,     /* TMR4_1_RLOV */
    INT_SRC_TMR4_1_RELOAD_W      = 183U,     /* TMR4_1_RLOW */
    /*  TIMER6_2  */
    INT_SRC_TMR6_2_DTE           = 184U,     /* TMR6_2_GDTE */
    INT_SRC_TMR6_2_SCMP_A        = 187U,     /* TMR6_2_SCMA */
    INT_SRC_TMR6_2_SCMP_B        = 188U,     /* TMR6_2_SCMB */
    /*  TIMER4_2  */
    INT_SRC_TMR4_2_RELOAD_U      = 189U,     /* TMR4_2_RLOU */
    INT_SRC_TMR4_2_RELOAD_V      = 190U,     /* TMR4_2_RLOV */
    INT_SRC_TMR4_2_RELOAD_W      = 191U,     /* TMR4_2_RLOW */
    /*  TIMER6_3  */
    INT_SRC_TMR6_3_DTE           = 192U,     /* TMR6_3_GDTE */
    INT_SRC_TMR6_3_SCMP_A        = 195U,     /* TMR6_3_SCMA */
    INT_SRC_TMR6_3_SCMP_B        = 196U,     /* TMR6_3_SCMB */
    /*  TIMER4_3  */
    INT_SRC_TMR4_3_RELOAD_U      = 197U,     /* TMR4_3_RLOU */
    INT_SRC_TMR4_3_RELOAD_V      = 198U,     /* TMR4_3_RLOV */
    INT_SRC_TMR4_3_RELOAD_W      = 199U,     /* TMR4_3_RLOW */
    /*  TIMER6_4 TIMER6_5  */
    INT_SRC_TMR6_4_GCMP_A        = 208U,     /* TMR6_4_GCMA */
    INT_SRC_TMR6_4_GCMP_B        = 209U,     /* TMR6_4_GCMB */
    INT_SRC_TMR6_4_GCMP_C        = 210U,     /* TMR6_4_GCMC */
    INT_SRC_TMR6_4_GCMP_D        = 211U,     /* TMR6_4_GCMD */
    INT_SRC_TMR6_4_GCMP_E        = 212U,     /* TMR6_4_GCME */
    INT_SRC_TMR6_4_GCMP_F        = 213U,     /* TMR6_4_GCMF */
    INT_SRC_TMR6_4_OVF           = 214U,     /* TMR6_4_GOVF */
    INT_SRC_TMR6_4_UDF           = 215U,     /* TMR6_4_GUDF */
    INT_SRC_TMR6_4_DTE           = 216U,     /* TMR6_4_GDTE */
    INT_SRC_TMR6_4_SCMP_A        = 219U,     /* TMR6_4_SCMA */
    INT_SRC_TMR6_4_SCMP_B        = 220U,     /* TMR6_4_SCMB */
    INT_SRC_TMR6_5_GCMP_A        = 224U,     /* TMR6_5_GCMA */
    INT_SRC_TMR6_5_GCMP_B        = 225U,     /* TMR6_5_GCMB */
    INT_SRC_TMR6_5_GCMP_C        = 226U,     /* TMR6_5_GCMC */
    INT_SRC_TMR6_5_GCMP_D        = 227U,     /* TMR6_5_GCMD */
    INT_SRC_TMR6_5_GCMP_E        = 228U,     /* TMR6_5_GCME */
    INT_SRC_TMR6_5_GCMP_F        = 229U,     /* TMR6_5_GCMF */
    INT_SRC_TMR6_5_OVF           = 230U,     /* TMR6_5_GOVF */
    INT_SRC_TMR6_5_UDF           = 231U,     /* TMR6_5_GUDF */
    INT_SRC_TMR6_5_DTE           = 232U,     /* TMR6_5_GDTE */
    INT_SRC_TMR6_5_SCMP_A        = 235U,     /* TMR6_5_SCMA */
    INT_SRC_TMR6_5_SCMP_B        = 236U,     /* TMR6_5_SCMB */
    /*  TIMERA_1  */
    INT_SRC_TMRA_1_OVF           = 237U,     /* TMRA_1_OVF */
    INT_SRC_TMRA_1_UDF           = 238U,     /* TMRA_1_UDF */
    INT_SRC_TMRA_1_CMP           = 239U,     /* TMRA_1_CMP */
    /*  TIMER6_6  */
    INT_SRC_TMR6_6_GCMP_A        = 240U,     /* TMR6_6_GCMA */
    INT_SRC_TMR6_6_GCMP_B        = 241U,     /* TMR6_6_GCMB */
    INT_SRC_TMR6_6_GCMP_C        = 242U,     /* TMR6_6_GCMC */
    INT_SRC_TMR6_6_GCMP_D        = 243U,     /* TMR6_6_GCMD */
    INT_SRC_TMR6_6_GCMP_E        = 244U,     /* TMR6_6_GCME */
    INT_SRC_TMR6_6_GCMP_F        = 245U,     /* TMR6_6_GCMF */
    INT_SRC_TMR6_6_OVF           = 246U,     /* TMR6_6_GOVF */
    INT_SRC_TMR6_6_UDF           = 247U,     /* TMR6_6_GUDF */
    INT_SRC_TMR6_6_DTE           = 248U,     /* TMR6_6_GDTE */
    INT_SRC_TMR6_6_SCMP_A        = 251U,     /* TMR6_6_SCMA */
    INT_SRC_TMR6_6_SCMP_B        = 252U,     /* TMR6_6_SCMB */
    /*  TIMERA_2  */
    INT_SRC_TMRA_2_OVF           = 253U,     /* TMRA_2_OVF */
    INT_SRC_TMRA_2_UDF           = 254U,     /* TMRA_2_UDF */
    INT_SRC_TMRA_2_CMP           = 255U,     /* TMRA_2_CMP */
    /*  TIMER6_7  */
    INT_SRC_TMR6_7_GCMP_A        = 256U,     /* TMR6_7_GCMA */
    INT_SRC_TMR6_7_GCMP_B        = 257U,     /* TMR6_7_GCMB */
    INT_SRC_TMR6_7_GCMP_C        = 258U,     /* TMR6_7_GCMC */
    INT_SRC_TMR6_7_GCMP_D        = 259U,     /* TMR6_7_GCMD */
    INT_SRC_TMR6_7_GCMP_E        = 260U,     /* TMR6_7_GCME */
    INT_SRC_TMR6_7_GCMP_F        = 261U,     /* TMR6_7_GCMF */
    INT_SRC_TMR6_7_OVF           = 262U,     /* TMR6_7_GOVF */
    INT_SRC_TMR6_7_UDF           = 263U,     /* TMR6_7_GUDF */
    INT_SRC_TMR6_7_DTE           = 264U,     /* TMR6_7_GDTE */
    INT_SRC_TMR6_7_SCMP_A        = 267U,     /* TMR6_7_SCMA */
    INT_SRC_TMR6_7_SCMP_B        = 268U,     /* TMR6_7_SCMB */
    /*  TIMERA_3  */
    INT_SRC_TMRA_3_OVF           = 269U,     /* TMRA_3_OVF */
    INT_SRC_TMRA_3_UDF           = 270U,     /* TMRA_3_UDF */
    INT_SRC_TMRA_3_CMP           = 271U,     /* TMRA_3_CMP */
    /*  TIMER6_8  */
    INT_SRC_TMR6_8_GCMP_A        = 272U,     /* TMR6_8_GCMA */
    INT_SRC_TMR6_8_GCMP_B        = 273U,     /* TMR6_8_GCMB */
    INT_SRC_TMR6_8_GCMP_C        = 274U,     /* TMR6_8_GCMC */
    INT_SRC_TMR6_8_GCMP_D        = 275U,     /* TMR6_8_GCMD */
    INT_SRC_TMR6_8_GCMP_E        = 276U,     /* TMR6_8_GCME */
    INT_SRC_TMR6_8_GCMP_F        = 277U,     /* TMR6_8_GCMF */
    INT_SRC_TMR6_8_OVF           = 278U,     /* TMR6_8_GOVF */
    INT_SRC_TMR6_8_UDF           = 279U,     /* TMR6_8_GUDF */
    INT_SRC_TMR6_8_DTE           = 280U,     /* TMR6_8_GDTE */
    INT_SRC_TMR6_8_SCMP_A        = 283U,     /* TMR6_8_SCMA */
    INT_SRC_TMR6_8_SCMP_B        = 284U,     /* TMR6_8_SCMB */
    /*  TIMERA_4  */
    INT_SRC_TMRA_4_OVF           = 285U,     /* TMRA_4_OVF */
    INT_SRC_TMRA_4_UDF           = 286U,     /* TMRA_4_UDF */
    INT_SRC_TMRA_4_CMP           = 287U,     /* TMRA_4_CMP */
    /*  EMB  */
    INT_SRC_EMB_GR0              = 288U,     /* EMB_GR0 */
    INT_SRC_EMB_GR1              = 289U,     /* EMB_GR1 */
    INT_SRC_EMB_GR2              = 290U,     /* EMB_GR2 */
    INT_SRC_EMB_GR3              = 291U,     /* EMB_GR3 */
    INT_SRC_EMB_GR4              = 292U,     /* EMB_GR4 */
    INT_SRC_EMB_GR5              = 293U,     /* EMB_GR5 */
    INT_SRC_EMB_GR6              = 294U,     /* EMB_GR6 */
    /*  USBHS  */
    INT_SRC_USBHS_EP1_OUT        = 295U,     /* USBHS_EP1_OUT */
    INT_SRC_USBHS_EP1_IN         = 296U,     /* USBHS_EP1_IN */
    INT_SRC_USBHS_GLB            = 297U,     /* USBHS_GLB */
    INT_SRC_USBHS_WKUP           = 298U,     /* USBHS_WKUP */
    /*  USART1 USART2  */
    INT_SRC_USART1_EI            = 300U,     /* USART_1_EI */
    INT_SRC_USART1_RI            = 301U,     /* USART_1_RI */
    INT_SRC_USART1_TI            = 302U,     /* USART_1_TI */
    INT_SRC_USART1_TCI           = 303U,     /* USART_1_TCI */
    INT_SRC_USART1_RTO           = 304U,     /* USART_1_RTO */
    INT_SRC_USART2_EI            = 305U,     /* USART_2_EI */
    INT_SRC_USART2_RI            = 306U,     /* USART_2_RI */
    INT_SRC_USART2_TI            = 307U,     /* USART_2_TI */
    INT_SRC_USART2_TCI           = 308U,     /* USART_2_TCI */
    INT_SRC_USART2_RTO           = 309U,     /* USART_2_RTO */
    /*  SPI1 SPI2  */
    INT_SRC_SPI1_SPRI            = 310U,     /* SPI_1_SPRI */
    INT_SRC_SPI1_SPTI            = 311U,     /* SPI_1_SPTI */
    INT_SRC_SPI1_SPII            = 312U,     /* SPI_1_SPII */
    INT_SRC_SPI1_SPEI            = 313U,     /* SPI_1_SPEI */
    INT_SRC_SPI2_SPRI            = 315U,     /* SPI_2_SPRI */
    INT_SRC_SPI2_SPTI            = 316U,     /* SPI_2_SPTI */
    INT_SRC_SPI2_SPII            = 317U,     /* SPI_2_SPII */
    INT_SRC_SPI2_SPEI            = 318U,     /* SPI_2_SPEI */
    /*  TIMERA_5 TIMERA_6 TIMERA_7 TIMERA_8  */
    INT_SRC_TMRA_5_OVF           = 320U,     /* TMRA_5_OVF */
    INT_SRC_TMRA_5_UDF           = 321U,     /* TMRA_5_UDF */
    INT_SRC_TMRA_5_CMP           = 322U,     /* TMRA_5_CMP */
    INT_SRC_TMRA_6_OVF           = 323U,     /* TMRA_6_OVF */
    INT_SRC_TMRA_6_UDF           = 324U,     /* TMRA_6_UDF */
    INT_SRC_TMRA_6_CMP           = 325U,     /* TMRA_6_CMP */
    INT_SRC_TMRA_7_OVF           = 326U,     /* TMRA_7_OVF */
    INT_SRC_TMRA_7_UDF           = 327U,     /* TMRA_7_UDF */
    INT_SRC_TMRA_7_CMP           = 328U,     /* TMRA_7_CMP */
    INT_SRC_TMRA_8_OVF           = 329U,     /* TMRA_8_OVF */
    INT_SRC_TMRA_8_UDF           = 330U,     /* TMRA_8_UDF */
    INT_SRC_TMRA_8_CMP           = 331U,     /* TMRA_8_CMP */
    /*  USART3 USART4  */
    INT_SRC_USART3_EI            = 332U,     /* USART_3_EI */
    INT_SRC_USART3_RI            = 333U,     /* USART_3_RI */
    INT_SRC_USART3_TI            = 334U,     /* USART_3_TI */
    INT_SRC_USART3_TCI           = 335U,     /* USART_3_TCI */
    INT_SRC_USART4_EI            = 336U,     /* USART_4_EI */
    INT_SRC_USART4_RI            = 337U,     /* USART_4_RI */
    INT_SRC_USART4_TI            = 338U,     /* USART_4_TI */
    INT_SRC_USART4_TCI           = 339U,     /* USART_4_TCI */
    /*  CAN1 CAN2  */
    INT_SRC_CAN1_HOST            = 340U,     /* CAN_1_HOST */
    INT_SRC_CAN2_HOST            = 341U,     /* CAN_2_HOST */
    /*  SPI3 SPI4  */
    INT_SRC_SPI3_SPRI            = 342U,     /* SPI_3_SPRI */
    INT_SRC_SPI3_SPTI            = 343U,     /* SPI_3_SPTI */
    INT_SRC_SPI3_SPII            = 344U,     /* SPI_3_SPII */
    INT_SRC_SPI3_SPEI            = 345U,     /* SPI_3_SPEI */
    INT_SRC_SPI4_SPRI            = 347U,     /* SPI_4_SPRI */
    INT_SRC_SPI4_SPTI            = 348U,     /* SPI_4_SPTI */
    INT_SRC_SPI4_SPII            = 349U,     /* SPI_4_SPII */
    INT_SRC_SPI4_SPEI            = 350U,     /* SPI_4_SPEI */
    /*  TIMERA_9 TIMERA_10 TIMER_11 TIMER_12  */
    INT_SRC_TMRA_9_OVF           = 352U,     /* TMRA_9_OVF */
    INT_SRC_TMRA_9_UDF           = 353U,     /* TMRA_9_UDF */
    INT_SRC_TMRA_9_CMP           = 354U,     /* TMRA_9_CMP */
    INT_SRC_TMRA_10_OVF          = 355U,     /* TMRA_10_OVF */
    INT_SRC_TMRA_10_UDF          = 356U,     /* TMRA_10_UDF */
    INT_SRC_TMRA_10_CMP          = 357U,     /* TMRA_10_CMP */
    INT_SRC_TMRA_11_OVF          = 358U,     /* TMRA_11_OVF */
    INT_SRC_TMRA_11_UDF          = 359U,     /* TMRA_11_UDF */
    INT_SRC_TMRA_11_CMP          = 360U,     /* TMRA_11_CMP */
    INT_SRC_TMRA_12_OVF          = 361U,     /* TMRA_12_OVF */
    INT_SRC_TMRA_12_UDF          = 362U,     /* TMRA_12_UDF */
    INT_SRC_TMRA_12_CMP          = 363U,     /* TMRA_12_CMP */
    /*  USART5 USART6  */
    INT_SRC_USART5_BRKWKPI       = 364U,     /* USART_5_BRKWKPI */
    INT_SRC_USART5_EI            = 365U,     /* USART_5_EI */
    INT_SRC_USART5_RI            = 366U,     /* USART_5_RI */
    INT_SRC_USART5_TI            = 367U,     /* USART_5_TI */
    INT_SRC_USART5_TCI           = 368U,     /* USART_5_TCI */
    INT_SRC_USART6_EI            = 369U,     /* USART_6_EI */
    INT_SRC_USART6_RI            = 370U,     /* USART_6_RI */
    INT_SRC_USART6_TI            = 371U,     /* USART_6_TI */
    INT_SRC_USART6_TCI           = 372U,     /* USART_6_TCI */
    INT_SRC_USART6_RTO           = 373U,     /* USART_6_RTO */
    /*  SPI5 SPI6  */
    INT_SRC_SPI5_SPRI            = 374U,     /* SPI_5_SPRI */
    INT_SRC_SPI5_SPTI            = 375U,     /* SPI_5_SPTI */
    INT_SRC_SPI5_SPII            = 376U,     /* SPI_5_SPII */
    INT_SRC_SPI5_SPEI            = 377U,     /* SPI_5_SPEI */
    INT_SRC_SPI6_SPRI            = 379U,     /* SPI_6_SPRI */
    INT_SRC_SPI6_SPTI            = 380U,     /* SPI_6_SPTI */
    INT_SRC_SPI6_SPII            = 381U,     /* SPI_6_SPII */
    INT_SRC_SPI6_SPEI            = 382U,     /* SPI_6_SPEI */
    /*  I2S1 I2S2  */
    INT_SRC_I2S1_TXIRQOUT        = 384U,     /* I2S_1_TXIRQOUT */
    INT_SRC_I2S1_RXIRQOUT        = 385U,     /* I2S_1_RXIRQOUT */
    INT_SRC_I2S1_ERRIRQOUT       = 386U,     /* I2S_1_ERRIRQOUT */
    INT_SRC_I2S2_TXIRQOUT        = 387U,     /* I2S_2_TXIRQOUT */
    INT_SRC_I2S2_RXIRQOUT        = 388U,     /* I2S_2_RXIRQOUT */
    INT_SRC_I2S2_ERRIRQOUT       = 389U,     /* I2S_2_ERRIRQOUT */
    /*  USART7 USART8  */
    INT_SRC_USART7_EI            = 390U,     /* USART_7_EI */
    INT_SRC_USART7_RI            = 391U,     /* USART_7_RI */
    INT_SRC_USART7_TI            = 392U,     /* USART_7_TI */
    INT_SRC_USART7_TCI           = 393U,     /* USART_7_TCI */
    INT_SRC_USART7_RTO           = 394U,     /* USART_7_RTO */
    INT_SRC_USART8_EI            = 395U,     /* USART_8_EI */
    INT_SRC_USART8_RI            = 396U,     /* USART_8_RI */
    INT_SRC_USART8_TI            = 397U,     /* USART_8_TI */
    INT_SRC_USART8_TCI           = 398U,     /* USART_8_TCI */
    /*  USBFS  */
    INT_SRC_USBFS_GLB            = 399U,     /* USBFS_GLB */
    INT_SRC_USBFS_WKUP           = 400U,     /* USBFS_WKUP */
    /*  HASH  */
    INT_SRC_HASH                 = 401U,     /* HASH_INT */
    /*  SDIOC  */
    INT_SRC_SDIOC1_SD            = 404U,     /* SDIOC_1_SD */
    INT_SRC_SDIOC2_SD            = 407U,     /* SDIOC_2_SD */
    /*  EVENT PORT  */
    INT_SRC_EVENT_PORT1          = 408U,     /* EVENT_PORT1 */
    INT_SRC_EVENT_PORT2          = 409U,     /* EVENT_PORT2 */
    INT_SRC_EVENT_PORT3          = 410U,     /* EVENT_PORT3 */
    INT_SRC_EVENT_PORT4          = 411U,     /* EVENT_PORT4 */
    /*  ETHER  */
    INT_SRC_ETH_GLB_INT          = 412U,     /* ETH_GLB_INT */
    INT_SRC_ETH_WKP_INT          = 413U,     /* ETH_WKP_INT */
    /*  I2S3 I2S4  */
    INT_SRC_I2S3_TXIRQOUT        = 416U,     /* I2S_3_TXIRQOUT */
    INT_SRC_I2S3_RXIRQOUT        = 417U,     /* I2S_3_RXIRQOUT */
    INT_SRC_I2S3_ERRIRQOUT       = 418U,     /* I2S_3_ERRIRQOUT */
    INT_SRC_I2S4_TXIRQOUT        = 419U,     /* I2S_4_TXIRQOUT */
    INT_SRC_I2S4_RXIRQOUT        = 420U,     /* I2S_4_RXIRQOUT */
    INT_SRC_I2S4_ERRIRQOUT       = 421U,     /* I2S_4_ERRIRQOUT */
    /*  USART9 USART10  */
    INT_SRC_USART9_EI            = 422U,     /* USART_9_EI */
    INT_SRC_USART9_RI            = 423U,     /* USART_9_RI */
    INT_SRC_USART9_TI            = 424U,     /* USART_9_TI */
    INT_SRC_USART9_TCI           = 425U,     /* USART_9_TCI */
    INT_SRC_USART10_BRKWKPI      = 426U,     /* USART_10_BRKWKPI */
    INT_SRC_USART10_EI           = 427U,     /* USART_10_EI */
    INT_SRC_USART10_RI           = 428U,     /* USART_10_RI */
    INT_SRC_USART10_TI           = 429U,     /* USART_10_TI */
    INT_SRC_USART10_TCI          = 430U,     /* USART_10_TCI */
    /*  I2C1 I2C2 I2C3  */
    INT_SRC_I2C1_RXI             = 432U,     /* I2C_1_RXI */
    INT_SRC_I2C1_TXI             = 433U,     /* I2C_1_TXI */
    INT_SRC_I2C1_TEI             = 434U,     /* I2C_1_TEI */
    INT_SRC_I2C1_EEI             = 435U,     /* I2C_1_EEI */
    INT_SRC_I2C2_RXI             = 436U,     /* I2C_2_RXI */
    INT_SRC_I2C2_TXI             = 437U,     /* I2C_2_TXI */
    INT_SRC_I2C2_TEI             = 438U,     /* I2C_2_TEI */
    INT_SRC_I2C2_EEI             = 439U,     /* I2C_2_EEI */
    INT_SRC_I2C3_RXI             = 440U,     /* I2C_3_RXI */
    INT_SRC_I2C3_TXI             = 441U,     /* I2C_3_TXI */
    INT_SRC_I2C3_TEI             = 442U,     /* I2C_3_TEI */
    INT_SRC_I2C3_EEI             = 443U,     /* I2C_3_EEI */
    /*  ACMP  */
    INT_SRC_CMP1                 = 444U,     /* CMP1 */
    INT_SRC_CMP2                 = 445U,     /* CMP2 */
    INT_SRC_CMP3                 = 446U,     /* CMP3 */
    INT_SRC_CMP4                 = 447U,     /* CMP4 */
    /*  I2C4 I2C5 I2C6  */
    INT_SRC_I2C4_RXI             = 448U,     /* I2C_4_RXI */
    INT_SRC_I2C4_TXI             = 449U,     /* I2C_4_TXI */
    INT_SRC_I2C4_TEI             = 450U,     /* I2C_4_TEI */
    INT_SRC_I2C4_EEI             = 451U,     /* I2C_4_EEI */
    INT_SRC_I2C5_RXI             = 452U,     /* I2C_5_RXI */
    INT_SRC_I2C5_TXI             = 453U,     /* I2C_5_TXI */
    INT_SRC_I2C5_TEI             = 454U,     /* I2C_5_TEI */
    INT_SRC_I2C5_EEI             = 455U,     /* I2C_5_EEI */
    INT_SRC_I2C6_RXI             = 456U,     /* I2C_6_RXI */
    INT_SRC_I2C6_TXI             = 457U,     /* I2C_6_TXI */
    INT_SRC_I2C6_TEI             = 458U,     /* I2C_6_TEI */
    INT_SRC_I2C6_EEI             = 459U,     /* I2C_6_EEI */
    /*  USART1  */
    INT_SRC_USART1_WUPI          = 460U,     /* USART_1_WUPI */
    /*  LVD  */
    INT_SRC_LVD1                = 461U,     /* LVD1 */
    INT_SRC_LVD2                = 462U,     /* LVD2 */
    /*  OTS  */
    INT_SRC_OTS                  = 463U,     /* OTS */
    /*  FCM  */
    INT_SRC_FCMFERRI             = 464U,     /* FCMFERRI */
    INT_SRC_FCMMENDI             = 465U,     /* FCMMENDI */
    INT_SRC_FCMCOVFI             = 466U,     /* FCMCOVFI */
    /*  WDT  */
    INT_SRC_WDT_REFUDF           = 467U,     /* WDT_REFUDF */
    /*  CTC  */
    INT_SRC_CTC_ERR              = 468U,     /* CTC_ERR */
    /*  ADC  */
    INT_SRC_ADC1_EOCA            = 480U,     /* ADC_1_EOCA */
    INT_SRC_ADC1_EOCB            = 481U,     /* ADC_1_EOCB */
    INT_SRC_ADC1_CMP0            = 482U,     /* ADC_1_CMP0 */
    INT_SRC_ADC1_CMP1            = 483U,     /* ADC_1_CMP1 */
    INT_SRC_ADC2_EOCA            = 484U,     /* ADC_2_EOCA */
    INT_SRC_ADC2_EOCB            = 485U,     /* ADC_2_EOCB */
    INT_SRC_ADC2_CMP0            = 486U,     /* ADC_2_CMP0 */
    INT_SRC_ADC2_CMP1            = 487U,     /* ADC_2_CMP1 */
    INT_SRC_ADC3_EOCA            = 488U,     /* ADC_3_EOCA */
    INT_SRC_ADC3_EOCB            = 489U,     /* ADC_3_EOCB */
    INT_SRC_ADC3_CMP0            = 490U,     /* ADC_3_CMP0 */
    INT_SRC_ADC3_CMP1            = 491U,     /* ADC_3_CMP1 */
    /*  TRNG  */
    INT_SRC_TRNG_END             = 492U,     /* TRNG_END */
    /*  NFC  */
    INT_SRC_NFC_INT              = 496U,     /* NFC_INT */
    INT_SRC_MAX                  = 511U,
} en_int_src_t;

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

/**
 * @brief ADC
 */
typedef struct {
    __IO uint8_t  STR;
    uint8_t RESERVED0[1];
    __IO uint16_t CR0;
    __IO uint16_t CR1;
    uint8_t RESERVED1[4];
    __IO uint16_t TRGSR;
    __IO uint32_t CHSELRA;
    __IO uint32_t CHSELRB;
    __IO uint32_t AVCHSELR;
    __IO uint8_t  EXCHSELR;
    uint8_t RESERVED2[1];
    __IO uint16_t SHCR;
    uint8_t RESERVED3[4];
    __IO uint8_t  SSTR0;
    __IO uint8_t  SSTR1;
    __IO uint8_t  SSTR2;
    __IO uint8_t  SSTR3;
    __IO uint8_t  SSTR4;
    __IO uint8_t  SSTR5;
    __IO uint8_t  SSTR6;
    __IO uint8_t  SSTR7;
    __IO uint8_t  SSTR8;
    __IO uint8_t  SSTR9;
    __IO uint8_t  SSTR10;
    __IO uint8_t  SSTR11;
    __IO uint8_t  SSTR12;
    __IO uint8_t  SSTR13;
    __IO uint8_t  SSTR14;
    __IO uint8_t  SSTR15;
    __IO uint8_t  SSTRL;
    uint8_t RESERVED4[7];
    __IO uint16_t CHMUXR0;
    __IO uint16_t CHMUXR1;
    __IO uint16_t CHMUXR2;
    __IO uint16_t CHMUXR3;
    uint8_t RESERVED5[4];
    __I  uint8_t  ISR;
    __IO uint8_t  ICR;
    __IO uint8_t  ISCLRR;
    uint8_t RESERVED6[5];
    __IO uint16_t SYNCCR;
    uint8_t RESERVED7[2];
    __I  uint16_t DR0;
    __I  uint16_t DR1;
    __I  uint16_t DR2;
    __I  uint16_t DR3;
    __I  uint16_t DR4;
    __I  uint16_t DR5;
    __I  uint16_t DR6;
    __I  uint16_t DR7;
    __I  uint16_t DR8;
    __I  uint16_t DR9;
    __I  uint16_t DR10;
    __I  uint16_t DR11;
    __I  uint16_t DR12;
    __I  uint16_t DR13;
    __I  uint16_t DR14;
    __I  uint16_t DR15;
    __I  uint16_t DR16;
    __I  uint16_t DR17;
    __I  uint16_t DR18;
    __I  uint16_t DR19;
    uint8_t RESERVED8[40];
    __IO uint16_t AWDCR;
    __I  uint8_t  AWDSR;
    __IO uint8_t  AWDSCLRR;
    __IO uint16_t AWD0DR0;
    __IO uint16_t AWD0DR1;
    __IO uint8_t  AWD0CHSR;
    uint8_t RESERVED9[3];
    __IO uint16_t AWD1DR0;
    __IO uint16_t AWD1DR1;
    __IO uint8_t  AWD1CHSR;
    uint8_t RESERVED10[15];
    __IO uint8_t  PGACR1;
    __IO uint8_t  PGACR2;
    __IO uint8_t  PGACR3;
    uint8_t RESERVED11[1];
    __IO uint8_t  PGAVSSENR;
} CM_ADC_TypeDef;

/**
 * @brief AES
 */
typedef struct {
    __IO uint32_t CR;
    uint8_t RESERVED0[12];
    __IO uint32_t DR0;
    __IO uint32_t DR1;
    __IO uint32_t DR2;
    __IO uint32_t DR3;
    __IO uint32_t KR0;
    __IO uint32_t KR1;
    __IO uint32_t KR2;
    __IO uint32_t KR3;
    __IO uint32_t KR4;
    __IO uint32_t KR5;
    __IO uint32_t KR6;
    __IO uint32_t KR7;
} CM_AES_TypeDef;

/**
 * @brief AOS
 */
typedef struct {
    __O  uint32_t INTSFTTRG;
    __IO uint32_t DCU_TRGSEL1;
    __IO uint32_t DCU_TRGSEL2;
    __IO uint32_t DCU_TRGSEL3;
    __IO uint32_t DCU_TRGSEL4;
    __IO uint32_t DMA1_TRGSEL0;
    __IO uint32_t DMA1_TRGSEL1;
    __IO uint32_t DMA1_TRGSEL2;
    __IO uint32_t DMA1_TRGSEL3;
    __IO uint32_t DMA1_TRGSEL4;
    __IO uint32_t DMA1_TRGSEL5;
    __IO uint32_t DMA1_TRGSEL6;
    __IO uint32_t DMA1_TRGSEL7;
    __IO uint32_t DMA2_TRGSEL0;
    __IO uint32_t DMA2_TRGSEL1;
    __IO uint32_t DMA2_TRGSEL2;
    __IO uint32_t DMA2_TRGSEL3;
    __IO uint32_t DMA2_TRGSEL4;
    __IO uint32_t DMA2_TRGSEL5;
    __IO uint32_t DMA2_TRGSEL6;
    __IO uint32_t DMA2_TRGSEL7;
    __IO uint32_t DMA_RC_TRGSEL;
    __IO uint32_t TMR6_TRGSEL0;
    __IO uint32_t TMR6_TRGSEL1;
    __IO uint32_t TMR6_TRGSEL2;
    __IO uint32_t TMR6_TRGSEL3;
    __IO uint32_t PEVNT_TRGSEL12;
    __IO uint32_t PEVNT_TRGSEL34;
    __IO uint32_t TMR0_TRGSEL;
    __IO uint32_t TMR2_TRGSEL;
    __IO uint32_t HASH_TRGSELB;
    __IO uint32_t HASH_TRGSELA;
    __IO uint32_t TMRA_TRGSEL0;
    __IO uint32_t TMRA_TRGSEL1;
    __IO uint32_t TMRA_TRGSEL2;
    __IO uint32_t TMRA_TRGSEL3;
    __IO uint32_t OTS_TRGSEL;
    __IO uint32_t ADC1_TRGSEL0;
    __IO uint32_t ADC1_TRGSEL1;
    __IO uint32_t ADC2_TRGSEL0;
    __IO uint32_t ADC2_TRGSEL1;
    __IO uint32_t ADC3_TRGSEL0;
    __IO uint32_t ADC3_TRGSEL1;
    __IO uint32_t COMTRG1;
    __IO uint32_t COMTRG2;
    uint8_t RESERVED0[76];
    __IO uint32_t PEVNTDIRR1;
    __I  uint32_t PEVNTIDR1;
    __IO uint32_t PEVNTODR1;
    __IO uint32_t PEVNTORR1;
    __IO uint32_t PEVNTOSR1;
    __IO uint32_t PEVNTRISR1;
    __IO uint32_t PEVNTFALR1;
    __IO uint32_t PEVNTDIRR2;
    __I  uint32_t PEVNTIDR2;
    __IO uint32_t PEVNTODR2;
    __IO uint32_t PEVNTORR2;
    __IO uint32_t PEVNTOSR2;
    __IO uint32_t PEVNTRISR2;
    __IO uint32_t PEVNTFALR2;
    __IO uint32_t PEVNTDIRR3;
    __I  uint32_t PEVNTIDR3;
    __IO uint32_t PEVNTODR3;
    __IO uint32_t PEVNTORR3;
    __IO uint32_t PEVNTOSR3;
    __IO uint32_t PEVNTRISR3;
    __IO uint32_t PEVNTFALR3;
    __IO uint32_t PEVNTDIRR4;
    __I  uint32_t PEVNTIDR4;
    __IO uint32_t PEVNTODR4;
    __IO uint32_t PEVNTORR4;
    __IO uint32_t PEVNTOSR4;
    __IO uint32_t PEVNTRISR4;
    __IO uint32_t PEVNTFALR4;
    __IO uint32_t PEVNTNFCR;
} CM_AOS_TypeDef;

/**
 * @brief CAN
 */
typedef struct {
    __I  uint32_t RBUF;
    uint8_t RESERVED0[76];
    __IO uint32_t TBUF;
    uint8_t RESERVED1[76];
    __IO uint8_t  CFG_STAT;
    __IO uint8_t  TCMD;
    __IO uint8_t  TCTRL;
    __IO uint8_t  RCTRL;
    __IO uint8_t  RTIE;
    __IO uint8_t  RTIF;
    __IO uint8_t  ERRINT;
    __IO uint8_t  LIMIT;
    __IO uint32_t SBT;
    __IO uint32_t FBT;
    __I  uint8_t  EALCAP;
    __IO uint8_t  TDC;
    __IO uint8_t  RECNT;
    __IO uint8_t  TECNT;
    __IO uint8_t  ACFCTRL;
    uint8_t RESERVED2[1];
    __IO uint16_t ACFEN;
    __IO uint32_t ACF;
    uint8_t RESERVED3[2];
    __IO uint8_t  TBSLOT;
    __IO uint8_t  TTCFG;
    __IO uint32_t REF_MSG;
    __IO uint16_t TRG_CFG;
    __IO uint16_t TT_TRIG;
    __IO uint16_t TT_WTRIG;
} CM_CAN_TypeDef;

/**
 * @brief CMP
 */
typedef struct {
    __IO uint8_t  MDR;
    __IO uint8_t  FIR;
    __IO uint8_t  OCR;
    __IO uint8_t  PMSR;
    __IO uint16_t TWSR;
    __IO uint16_t TWPR;
    __IO uint16_t VISR;
} CM_CMP_TypeDef;

/**
 * @brief CMU
 */
typedef struct {
    __IO uint8_t  XTAL32CR;
    uint8_t RESERVED0[3];
    __IO uint8_t  XTAL32CFGR;
    uint8_t RESERVED1[15];
    __IO uint8_t  XTAL32NFR;
    uint8_t RESERVED2[7];
    __IO uint8_t  LRCCR;
    uint8_t RESERVED3[7];
    __IO uint8_t  LRCTRM;
    uint8_t RESERVED4[7];
    __IO uint8_t  RTCLRCTRM;
    uint8_t RESERVED5[2123];
    __IO uint8_t  XTALCFGR;
    uint8_t RESERVED6[29591];
    __IO uint16_t PERICKSEL;
    __IO uint16_t I2SCKSEL;
    uint8_t RESERVED7[4];
    __IO uint8_t  CANCKCFGR;
    uint8_t RESERVED8[7];
    __IO uint32_t SCFGR;
    __IO uint8_t  USBCKCFGR;
    uint8_t RESERVED9[1];
    __IO uint8_t  CKSWR;
    uint8_t RESERVED10[3];
    __IO uint8_t  PLLHCR;
    uint8_t RESERVED11[3];
    __IO uint8_t  PLLACR;
    uint8_t RESERVED12[3];
    __IO uint8_t  XTALCR;
    uint8_t RESERVED13[3];
    __IO uint8_t  HRCCR;
    uint8_t RESERVED14[1];
    __IO uint8_t  MRCCR;
    uint8_t RESERVED15[3];
    __IO uint8_t  OSCSTBSR;
    __IO uint8_t  MCO1CFGR;
    __IO uint8_t  MCO2CFGR;
    __IO uint8_t  TPIUCKCFGR;
    __IO uint8_t  XTALSTDCR;
    __IO uint8_t  XTALSTDSR;
    uint8_t RESERVED16[31];
    __IO uint8_t  MRCTRM;
    __IO uint8_t  HRCTRM;
    uint8_t RESERVED17[63];
    __IO uint8_t  XTALSTBCR;
    uint8_t RESERVED18[93];
    __IO uint32_t PLLHCFGR;
    __IO uint32_t PLLACFGR;
} CM_CMU_TypeDef;

/**
 * @brief CRC
 */
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t RESLT;
    uint8_t RESERVED0[120];
    __IO uint32_t DAT0;
    __IO uint32_t DAT1;
    __IO uint32_t DAT2;
    __IO uint32_t DAT3;
    __IO uint32_t DAT4;
    __IO uint32_t DAT5;
    __IO uint32_t DAT6;
    __IO uint32_t DAT7;
    __IO uint32_t DAT8;
    __IO uint32_t DAT9;
    __IO uint32_t DAT10;
    __IO uint32_t DAT11;
    __IO uint32_t DAT12;
    __IO uint32_t DAT13;
    __IO uint32_t DAT14;
    __IO uint32_t DAT15;
    __IO uint32_t DAT16;
    __IO uint32_t DAT17;
    __IO uint32_t DAT18;
    __IO uint32_t DAT19;
    __IO uint32_t DAT20;
    __IO uint32_t DAT21;
    __IO uint32_t DAT22;
    __IO uint32_t DAT23;
    __IO uint32_t DAT24;
    __IO uint32_t DAT25;
    __IO uint32_t DAT26;
    __IO uint32_t DAT27;
    __IO uint32_t DAT28;
    __IO uint32_t DAT29;
    __IO uint32_t DAT30;
    __IO uint32_t DAT31;
} CM_CRC_TypeDef;

/**
 * @brief CTC
 */
typedef struct {
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __I  uint32_t STR;
} CM_CTC_TypeDef;

/**
 * @brief DAC
 */
typedef struct {
    __IO uint16_t DADR1;
    __IO uint16_t DADR2;
    __IO uint16_t DACR;
    __IO uint16_t DAADPCR;
    uint8_t RESERVED0[20];
    __IO uint16_t DAOCR;
} CM_DAC_TypeDef;

/**
 * @brief DBGC
 */
typedef struct {
    __IO uint32_t AUTHID0;
    __IO uint32_t AUTHID1;
    __IO uint32_t AUTHID2;
    uint8_t RESERVED0[4];
    __IO uint32_t MCUSTAT;
    uint8_t RESERVED1[4];
    __IO uint32_t FERSCTL;
    __IO uint32_t MCUDBGCSTAT;
    __IO uint32_t MCUSTPCTL;
    __IO uint32_t MCUTRACECTL;
    __IO uint32_t MCUSTPCTL2;
} CM_DBGC_TypeDef;

/**
 * @brief DCU
 */
typedef struct {
    __IO uint32_t CTL;
    __I  uint32_t FLAG;
    __IO uint32_t DATA0;
    __IO uint32_t DATA1;
    __IO uint32_t DATA2;
    __IO uint32_t FLAGCLR;
    __IO uint32_t INTEVTSEL;
} CM_DCU_TypeDef;

/**
 * @brief DMA
 */
typedef struct {
    __IO uint32_t EN;
    __I  uint32_t INTSTAT0;
    __I  uint32_t INTSTAT1;
    __IO uint32_t INTMASK0;
    __IO uint32_t INTMASK1;
    __IO uint32_t INTCLR0;
    __IO uint32_t INTCLR1;
    __IO uint32_t CHEN;
    __I  uint32_t REQSTAT;
    __I  uint32_t CHSTAT;
    uint8_t RESERVED0[4];
    __IO uint32_t RCFGCTL;
    uint8_t RESERVED1[4];
    __IO uint32_t CHENCLR;
    uint8_t RESERVED2[8];
    __IO uint32_t SAR0;
    __IO uint32_t DAR0;
    __IO uint32_t DTCTL0;
    union {
        __IO uint32_t RPT0;
        __IO uint32_t RPTB0;
    };
    union {
        __IO uint32_t SNSEQCTL0;
        __IO uint32_t SNSEQCTLB0;
    };
    union {
        __IO uint32_t DNSEQCTL0;
        __IO uint32_t DNSEQCTLB0;
    };
    __IO uint32_t LLP0;
    __IO uint32_t CHCTL0;
    __I  uint32_t MONSAR0;
    __I  uint32_t MONDAR0;
    __I  uint32_t MONDTCTL0;
    __I  uint32_t MONRPT0;
    __I  uint32_t MONSNSEQCTL0;
    __I  uint32_t MONDNSEQCTL0;
    uint8_t RESERVED3[8];
    __IO uint32_t SAR1;
    __IO uint32_t DAR1;
    __IO uint32_t DTCTL1;
    union {
        __IO uint32_t RPT1;
        __IO uint32_t RPTB1;
    };
    union {
        __IO uint32_t SNSEQCTL1;
        __IO uint32_t SNSEQCTLB1;
    };
    union {
        __IO uint32_t DNSEQCTL1;
        __IO uint32_t DNSEQCTLB1;
    };
    __IO uint32_t LLP1;
    __IO uint32_t CHCTL1;
    __I  uint32_t MONSAR1;
    __I  uint32_t MONDAR1;
    __I  uint32_t MONDTCTL1;
    __I  uint32_t MONRPT1;
    __I  uint32_t MONSNSEQCTL1;
    __I  uint32_t MONDNSEQCTL1;
    uint8_t RESERVED4[8];
    __IO uint32_t SAR2;
    __IO uint32_t DAR2;
    __IO uint32_t DTCTL2;
    union {
        __IO uint32_t RPT2;
        __IO uint32_t RPTB2;
    };
    union {
        __IO uint32_t SNSEQCTL2;
        __IO uint32_t SNSEQCTLB2;
    };
    union {
        __IO uint32_t DNSEQCTL2;
        __IO uint32_t DNSEQCTLB2;
    };
    __IO uint32_t LLP2;
    __IO uint32_t CHCTL2;
    __I  uint32_t MONSAR2;
    __I  uint32_t MONDAR2;
    __I  uint32_t MONDTCTL2;
    __I  uint32_t MONRPT2;
    __I  uint32_t MONSNSEQCTL2;
    __I  uint32_t MONDNSEQCTL2;
    uint8_t RESERVED5[8];
    __IO uint32_t SAR3;
    __IO uint32_t DAR3;
    __IO uint32_t DTCTL3;
    union {
        __IO uint32_t RPT3;
        __IO uint32_t RPTB3;
    };
    union {
        __IO uint32_t SNSEQCTL3;
        __IO uint32_t SNSEQCTLB3;
    };
    union {
        __IO uint32_t DNSEQCTL3;
        __IO uint32_t DNSEQCTLB3;
    };
    __IO uint32_t LLP3;
    __IO uint32_t CHCTL3;
    __I  uint32_t MONSAR3;
    __I  uint32_t MONDAR3;
    __I  uint32_t MONDTCTL3;
    __I  uint32_t MONRPT3;
    __I  uint32_t MONSNSEQCTL3;
    __I  uint32_t MONDNSEQCTL3;
    uint8_t RESERVED6[8];
    __IO uint32_t SAR4;
    __IO uint32_t DAR4;
    __IO uint32_t DTCTL4;
    union {
        __IO uint32_t RPT4;
        __IO uint32_t RPTB4;
    };
    union {
        __IO uint32_t SNSEQCTL4;
        __IO uint32_t SNSEQCTLB4;
    };
    union {
        __IO uint32_t DNSEQCTL4;
        __IO uint32_t DNSEQCTLB4;
    };
    __IO uint32_t LLP4;
    __IO uint32_t CHCTL4;
    __I  uint32_t MONSAR4;
    __I  uint32_t MONDAR4;
    __I  uint32_t MONDTCTL4;
    __I  uint32_t MONRPT4;
    __I  uint32_t MONSNSEQCTL4;
    __I  uint32_t MONDNSEQCTL4;
    uint8_t RESERVED7[8];
    __IO uint32_t SAR5;
    __IO uint32_t DAR5;
    __IO uint32_t DTCTL5;
    union {
        __IO uint32_t RPT5;
        __IO uint32_t RPTB5;
    };
    union {
        __IO uint32_t SNSEQCTL5;
        __IO uint32_t SNSEQCTLB5;
    };
    union {
        __IO uint32_t DNSEQCTL5;
        __IO uint32_t DNSEQCTLB5;
    };
    __IO uint32_t LLP5;
    __IO uint32_t CHCTL5;
    __I  uint32_t MONSAR5;
    __I  uint32_t MONDAR5;
    __I  uint32_t MONDTCTL5;
    __I  uint32_t MONRPT5;
    __I  uint32_t MONSNSEQCTL5;
    __I  uint32_t MONDNSEQCTL5;
    uint8_t RESERVED8[8];
    __IO uint32_t SAR6;
    __IO uint32_t DAR6;
    __IO uint32_t DTCTL6;
    union {
        __IO uint32_t RPT6;
        __IO uint32_t RPTB6;
    };
    union {
        __IO uint32_t SNSEQCTL6;
        __IO uint32_t SNSEQCTLB6;
    };
    union {
        __IO uint32_t DNSEQCTL6;
        __IO uint32_t DNSEQCTLB6;
    };
    __IO uint32_t LLP6;
    __IO uint32_t CHCTL6;
    __I  uint32_t MONSAR6;
    __I  uint32_t MONDAR6;
    __I  uint32_t MONDTCTL6;
    __I  uint32_t MONRPT6;
    __I  uint32_t MONSNSEQCTL6;
    __I  uint32_t MONDNSEQCTL6;
    uint8_t RESERVED9[8];
    __IO uint32_t SAR7;
    __IO uint32_t DAR7;
    __IO uint32_t DTCTL7;
    union {
        __IO uint32_t RPT7;
        __IO uint32_t RPTB7;
    };
    union {
        __IO uint32_t SNSEQCTL7;
        __IO uint32_t SNSEQCTLB7;
    };
    union {
        __IO uint32_t DNSEQCTL7;
        __IO uint32_t DNSEQCTLB7;
    };
    __IO uint32_t LLP7;
    __IO uint32_t CHCTL7;
    __I  uint32_t MONSAR7;
    __I  uint32_t MONDAR7;
    __I  uint32_t MONDTCTL7;
    __I  uint32_t MONRPT7;
    __I  uint32_t MONSNSEQCTL7;
    __I  uint32_t MONDNSEQCTL7;
} CM_DMA_TypeDef;

/**
 * @brief DMC
 */
typedef struct {
    __I  uint32_t STSR;
    __O  uint32_t STCR;
    __O  uint32_t CMDR;
    __IO uint32_t CPCR;
    __IO uint32_t RFTR;
    __IO uint32_t TMCR_T_CASL;
    __IO uint32_t TMCR_T_DQSS;
    __IO uint32_t TMCR_T_MRD;
    __IO uint32_t TMCR_T_RAS;
    __IO uint32_t TMCR_T_RC;
    __IO uint32_t TMCR_T_RCD;
    __IO uint32_t TMCR_T_RFC;
    __IO uint32_t TMCR_T_RP;
    __IO uint32_t TMCR_T_RRD;
    __IO uint32_t TMCR_T_WR;
    __IO uint32_t TMCR_T_WTR;
    __IO uint32_t TMCR_T_XP;
    __IO uint32_t TMCR_T_XSR;
    __IO uint32_t TMCR_T_ESR;
    uint8_t RESERVED0[436];
    __IO uint32_t CSCR0;
    __IO uint32_t CSCR1;
    __IO uint32_t CSCR2;
    __IO uint32_t CSCR3;
    uint8_t RESERVED1[240];
    __IO uint32_t BACR;
} CM_DMC_TypeDef;

/**
 * @brief DVP
 */
typedef struct {
    __IO uint32_t CTR;
    __I  uint32_t DTR;
    __IO uint32_t STR;
    __IO uint32_t IER;
    __I  uint32_t DMR;
    uint8_t RESERVED0[12];
    __IO uint32_t SSYNDR;
    __IO uint32_t SSYNMR;
    __IO uint32_t CPSFTR;
    __IO uint32_t CPSZER;
} CM_DVP_TypeDef;

/**
 * @brief EFM
 */
typedef struct {
    __IO uint32_t FAPRT;
    __IO uint32_t KEY1;
    __IO uint32_t KEY2;
    uint8_t RESERVED0[8];
    __IO uint32_t FSTP;
    __IO uint32_t FRMC;
    __IO uint32_t FWMC;
    __I  uint32_t FSR;
    __IO uint32_t FSCLR;
    __IO uint32_t FITE;
    __I  uint32_t FSWP;
    uint8_t RESERVED1[16];
    __I  uint32_t CHIPID;
    uint8_t RESERVED2[12];
    __I  uint32_t UQID0;
    __I  uint32_t UQID1;
    __I  uint32_t UQID2;
    uint8_t RESERVED3[164];
    __IO uint32_t MMF_REMPRT;
    __IO uint32_t MMF_REMCR0;
    __IO uint32_t MMF_REMCR1;
    uint8_t RESERVED4[116];
    __IO uint32_t WLOCK;
    uint8_t RESERVED5[12];
    __IO uint32_t F0NWPRT0;
    __IO uint32_t F0NWPRT1;
    __IO uint32_t F0NWPRT2;
    __IO uint32_t F0NWPRT3;
    __IO uint32_t F1NWPRT0;
    __IO uint32_t F1NWPRT1;
    __IO uint32_t F1NWPRT2;
    __IO uint32_t F1NWPRT3;
} CM_EFM_TypeDef;

/**
 * @brief EMB
 */
typedef struct {
    __IO uint32_t CTL1;
    __IO uint32_t CTL2;
    __IO uint32_t SOE;
    __I  uint32_t STAT;
    __O  uint32_t STATCLR;
    __IO uint32_t INTEN;
    __IO uint32_t RLSSEL;
} CM_EMB_TypeDef;

/**
 * @brief ETH
 */
typedef struct {
    uint8_t RESERVED0[21520];
    __IO uint32_t MAC_IFCONFR;
    uint8_t RESERVED1[44012];
    __IO uint32_t MAC_CONFIGR;
    __IO uint32_t MAC_FLTCTLR;
    __IO uint32_t MAC_HASHTHR;
    __IO uint32_t MAC_HASHTLR;
    __IO uint32_t MAC_SMIADDR;
    __IO uint32_t MAC_SMIDATR;
    __IO uint32_t MAC_FLOCTLR;
    __IO uint32_t MAC_VTAFLTR;
    uint8_t RESERVED2[4];
    __I  uint32_t MAC_MACSTSR;
    __IO uint32_t MAC_RTWKFFR;
    __IO uint32_t MAC_PMTCTLR;
    uint8_t RESERVED3[8];
    __I  uint32_t MAC_INTSTSR;
    __IO uint32_t MAC_INTMSKR;
    __IO uint32_t MAC_MACADHR0;
    __IO uint32_t MAC_MACADLR0;
    __IO uint32_t MAC_MACADHR1;
    __IO uint32_t MAC_MACADLR1;
    __IO uint32_t MAC_MACADHR2;
    __IO uint32_t MAC_MACADLR2;
    __IO uint32_t MAC_MACADHR3;
    __IO uint32_t MAC_MACADLR3;
    __IO uint32_t MAC_MACADHR4;
    __IO uint32_t MAC_MACADLR4;
    uint8_t RESERVED4[152];
    __IO uint32_t MMC_MMCCTLR;
    __I  uint32_t MMC_REVSTSR;
    __I  uint32_t MMC_TRSSTSR;
    __IO uint32_t MMC_RITCTLR;
    __IO uint32_t MMC_TITCTLR;
    uint8_t RESERVED5[8];
    __I  uint32_t MMC_TXBRGFR;
    __I  uint32_t MMC_TXMUGFR;
    uint8_t RESERVED6[48];
    __I  uint32_t MMC_TXDEEFR;
    __I  uint32_t MMC_TXLCEFR;
    __I  uint32_t MMC_TXECEFR;
    __I  uint32_t MMC_TXCAEFR;
    uint8_t RESERVED7[4];
    __I  uint32_t MMC_TXUNGFR;
    __I  uint32_t MMC_TXEDEFR;
    uint8_t RESERVED8[28];
    __I  uint32_t MMC_RXBRGFR;
    __I  uint32_t MMC_RXMUGFR;
    __I  uint32_t MMC_RXCREFR;
    __I  uint32_t MMC_RXALEFR;
    __I  uint32_t MMC_RXRUEFR;
    uint8_t RESERVED9[36];
    __I  uint32_t MMC_RXUNGFR;
    __I  uint32_t MMC_RXLEEFR;
    __I  uint32_t MMC_RXOREFR;
    uint8_t RESERVED10[560];
    __IO uint32_t MAC_L34CTLR;
    __IO uint32_t MAC_L4PORTR;
    uint8_t RESERVED11[8];
    __IO uint32_t MAC_L3ADDRR0;
    __IO uint32_t MAC_L3ADDRR1;
    __IO uint32_t MAC_L3ADDRR2;
    __IO uint32_t MAC_L3ADDRR3;
    uint8_t RESERVED12[356];
    __IO uint32_t MAC_VTACTLR;
    __IO uint32_t MAC_VLAHTBR;
    uint8_t RESERVED13[372];
    __IO uint32_t PTP_TSPCTLR;
    __IO uint32_t PTP_TSPNSAR;
    __I  uint32_t PTP_TMSSECR;
    __I  uint32_t PTP_TMSNSER;
    __IO uint32_t PTP_TMUSECR;
    __IO uint32_t PTP_TMUNSER;
    __IO uint32_t PTP_TSPADDR;
    __IO uint32_t PTP_TMTSECR0;
    __IO uint32_t PTP_TMTNSER0;
    uint8_t RESERVED14[4];
    __I  uint32_t PTP_TSPSTSR;
    __IO uint32_t PTP_PPSCTLR;
    uint8_t RESERVED15[80];
    __IO uint32_t PTP_TMTSECR1;
    __IO uint32_t PTP_TMTNSER1;
    uint8_t RESERVED16[2168];
    __IO uint32_t DMA_BUSMODR;
    __IO uint32_t DMA_TXPOLLR;
    __IO uint32_t DMA_RXPOLLR;
    __IO uint32_t DMA_RXDLADR;
    __IO uint32_t DMA_TXDLADR;
    __IO uint32_t DMA_DMASTSR;
    __IO uint32_t DMA_OPRMODR;
    __IO uint32_t DMA_INTENAR;
    __I  uint32_t DMA_RFRCNTR;
    __IO uint32_t DMA_REVWDTR;
    uint8_t RESERVED17[32];
    __I  uint32_t DMA_CHTXDER;
    __I  uint32_t DMA_CHRXDER;
    __I  uint32_t DMA_CHTXBFR;
    __I  uint32_t DMA_CHRXBFR;
} CM_ETH_TypeDef;

/**
 * @brief FCM
 */
typedef struct {
    __IO uint32_t LVR;
    __IO uint32_t UVR;
    __I  uint32_t CNTR;
    __IO uint32_t STR;
    __IO uint32_t MCCR;
    __IO uint32_t RCCR;
    __IO uint32_t RIER;
    __I  uint32_t SR;
    __O  uint32_t CLR;
} CM_FCM_TypeDef;

/**
 * @brief FMAC
 */
typedef struct {
    __IO uint32_t ENR;
    __IO uint32_t CTR;
    __IO uint32_t IER;
    __IO uint32_t DTR;
    __IO uint32_t RTR0;
    __IO uint32_t RTR1;
    __IO uint32_t STR;
    uint8_t RESERVED0[4];
    __IO uint32_t COR0;
    __IO uint32_t COR1;
    __IO uint32_t COR2;
    __IO uint32_t COR3;
    __IO uint32_t COR4;
    __IO uint32_t COR5;
    __IO uint32_t COR6;
    __IO uint32_t COR7;
    __IO uint32_t COR8;
    __IO uint32_t COR9;
    __IO uint32_t COR10;
    __IO uint32_t COR11;
    __IO uint32_t COR12;
    __IO uint32_t COR13;
    __IO uint32_t COR14;
    __IO uint32_t COR15;
    __IO uint32_t COR16;
} CM_FMAC_TypeDef;

/**
 * @brief GPIO
 */
typedef struct {
    __I  uint16_t PIDRA;
    uint8_t RESERVED0[2];
    __IO uint16_t PODRA;
    __IO uint16_t POERA;
    __O  uint16_t POSRA;
    __O  uint16_t PORRA;
    __O  uint16_t POTRA;
    uint8_t RESERVED1[2];
    __I  uint16_t PIDRB;
    uint8_t RESERVED2[2];
    __IO uint16_t PODRB;
    __IO uint16_t POERB;
    __O  uint16_t POSRB;
    __O  uint16_t PORRB;
    __O  uint16_t POTRB;
    uint8_t RESERVED3[2];
    __I  uint16_t PIDRC;
    uint8_t RESERVED4[2];
    __IO uint16_t PODRC;
    __IO uint16_t POERC;
    __O  uint16_t POSRC;
    __O  uint16_t PORRC;
    __O  uint16_t POTRC;
    uint8_t RESERVED5[2];
    __I  uint16_t PIDRD;
    uint8_t RESERVED6[2];
    __IO uint16_t PODRD;
    __IO uint16_t POERD;
    __O  uint16_t POSRD;
    __O  uint16_t PORRD;
    __O  uint16_t POTRD;
    uint8_t RESERVED7[2];
    __I  uint16_t PIDRE;
    uint8_t RESERVED8[2];
    __IO uint16_t PODRE;
    __IO uint16_t POERE;
    __O  uint16_t POSRE;
    __O  uint16_t PORRE;
    __O  uint16_t POTRE;
    uint8_t RESERVED9[2];
    __I  uint16_t PIDRF;
    uint8_t RESERVED10[2];
    __IO uint16_t PODRF;
    __IO uint16_t POERF;
    __O  uint16_t POSRF;
    __O  uint16_t PORRF;
    __O  uint16_t POTRF;
    uint8_t RESERVED11[2];
    __I  uint16_t PIDRG;
    uint8_t RESERVED12[2];
    __IO uint16_t PODRG;
    __IO uint16_t POERG;
    __O  uint16_t POSRG;
    __O  uint16_t PORRG;
    __O  uint16_t POTRG;
    uint8_t RESERVED13[2];
    __I  uint16_t PIDRH;
    uint8_t RESERVED14[2];
    __IO uint16_t PODRH;
    __IO uint16_t POERH;
    __O  uint16_t POSRH;
    __O  uint16_t PORRH;
    __O  uint16_t POTRH;
    uint8_t RESERVED15[2];
    __I  uint16_t PIDRI;
    uint8_t RESERVED16[2];
    __IO uint16_t PODRI;
    __IO uint16_t POERI;
    __O  uint16_t POSRI;
    __O  uint16_t PORRI;
    __O  uint16_t POTRI;
    uint8_t RESERVED17[870];
    __IO uint16_t PSPCR;
    uint8_t RESERVED18[2];
    __IO uint16_t PCCR;
    __IO uint16_t PINAER;
    __IO uint16_t PWPR;
    uint8_t RESERVED19[2];
    __IO uint16_t PCRA0;
    __IO uint16_t PFSRA0;
    __IO uint16_t PCRA1;
    __IO uint16_t PFSRA1;
    __IO uint16_t PCRA2;
    __IO uint16_t PFSRA2;
    __IO uint16_t PCRA3;
    __IO uint16_t PFSRA3;
    __IO uint16_t PCRA4;
    __IO uint16_t PFSRA4;
    __IO uint16_t PCRA5;
    __IO uint16_t PFSRA5;
    __IO uint16_t PCRA6;
    __IO uint16_t PFSRA6;
    __IO uint16_t PCRA7;
    __IO uint16_t PFSRA7;
    __IO uint16_t PCRA8;
    __IO uint16_t PFSRA8;
    __IO uint16_t PCRA9;
    __IO uint16_t PFSRA9;
    __IO uint16_t PCRA10;
    __IO uint16_t PFSRA10;
    __IO uint16_t PCRA11;
    __IO uint16_t PFSRA11;
    __IO uint16_t PCRA12;
    __IO uint16_t PFSRA12;
    __IO uint16_t PCRA13;
    __IO uint16_t PFSRA13;
    __IO uint16_t PCRA14;
    __IO uint16_t PFSRA14;
    __IO uint16_t PCRA15;
    __IO uint16_t PFSRA15;
    __IO uint16_t PCRB0;
    __IO uint16_t PFSRB0;
    __IO uint16_t PCRB1;
    __IO uint16_t PFSRB1;
    __IO uint16_t PCRB2;
    __IO uint16_t PFSRB2;
    __IO uint16_t PCRB3;
    __IO uint16_t PFSRB3;
    __IO uint16_t PCRB4;
    __IO uint16_t PFSRB4;
    __IO uint16_t PCRB5;
    __IO uint16_t PFSRB5;
    __IO uint16_t PCRB6;
    __IO uint16_t PFSRB6;
    __IO uint16_t PCRB7;
    __IO uint16_t PFSRB7;
    __IO uint16_t PCRB8;
    __IO uint16_t PFSRB8;
    __IO uint16_t PCRB9;
    __IO uint16_t PFSRB9;
    __IO uint16_t PCRB10;
    __IO uint16_t PFSRB10;
    __IO uint16_t PCRB11;
    __IO uint16_t PFSRB11;
    __IO uint16_t PCRB12;
    __IO uint16_t PFSRB12;
    __IO uint16_t PCRB13;
    __IO uint16_t PFSRB13;
    __IO uint16_t PCRB14;
    __IO uint16_t PFSRB14;
    __IO uint16_t PCRB15;
    __IO uint16_t PFSRB15;
    __IO uint16_t PCRC0;
    __IO uint16_t PFSRC0;
    __IO uint16_t PCRC1;
    __IO uint16_t PFSRC1;
    __IO uint16_t PCRC2;
    __IO uint16_t PFSRC2;
    __IO uint16_t PCRC3;
    __IO uint16_t PFSRC3;
    __IO uint16_t PCRC4;
    __IO uint16_t PFSRC4;
    __IO uint16_t PCRC5;
    __IO uint16_t PFSRC5;
    __IO uint16_t PCRC6;
    __IO uint16_t PFSRC6;
    __IO uint16_t PCRC7;
    __IO uint16_t PFSRC7;
    __IO uint16_t PCRC8;
    __IO uint16_t PFSRC8;
    __IO uint16_t PCRC9;
    __IO uint16_t PFSRC9;
    __IO uint16_t PCRC10;
    __IO uint16_t PFSRC10;
    __IO uint16_t PCRC11;
    __IO uint16_t PFSRC11;
    __IO uint16_t PCRC12;
    __IO uint16_t PFSRC12;
    __IO uint16_t PCRC13;
    __IO uint16_t PFSRC13;
    __IO uint16_t PCRC14;
    __IO uint16_t PFSRC14;
    __IO uint16_t PCRC15;
    __IO uint16_t PFSRC15;
    __IO uint16_t PCRD0;
    __IO uint16_t PFSRD0;
    __IO uint16_t PCRD1;
    __IO uint16_t PFSRD1;
    __IO uint16_t PCRD2;
    __IO uint16_t PFSRD2;
    __IO uint16_t PCRD3;
    __IO uint16_t PFSRD3;
    __IO uint16_t PCRD4;
    __IO uint16_t PFSRD4;
    __IO uint16_t PCRD5;
    __IO uint16_t PFSRD5;
    __IO uint16_t PCRD6;
    __IO uint16_t PFSRD6;
    __IO uint16_t PCRD7;
    __IO uint16_t PFSRD7;
    __IO uint16_t PCRD8;
    __IO uint16_t PFSRD8;
    __IO uint16_t PCRD9;
    __IO uint16_t PFSRD9;
    __IO uint16_t PCRD10;
    __IO uint16_t PFSRD10;
    __IO uint16_t PCRD11;
    __IO uint16_t PFSRD11;
    __IO uint16_t PCRD12;
    __IO uint16_t PFSRD12;
    __IO uint16_t PCRD13;
    __IO uint16_t PFSRD13;
    __IO uint16_t PCRD14;
    __IO uint16_t PFSRD14;
    __IO uint16_t PCRD15;
    __IO uint16_t PFSRD15;
    __IO uint16_t PCRE0;
    __IO uint16_t PFSRE0;
    __IO uint16_t PCRE1;
    __IO uint16_t PFSRE1;
    __IO uint16_t PCRE2;
    __IO uint16_t PFSRE2;
    __IO uint16_t PCRE3;
    __IO uint16_t PFSRE3;
    __IO uint16_t PCRE4;
    __IO uint16_t PFSRE4;
    __IO uint16_t PCRE5;
    __IO uint16_t PFSRE5;
    __IO uint16_t PCRE6;
    __IO uint16_t PFSRE6;
    __IO uint16_t PCRE7;
    __IO uint16_t PFSRE7;
    __IO uint16_t PCRE8;
    __IO uint16_t PFSRE8;
    __IO uint16_t PCRE9;
    __IO uint16_t PFSRE9;
    __IO uint16_t PCRE10;
    __IO uint16_t PFSRE10;
    __IO uint16_t PCRE11;
    __IO uint16_t PFSRE11;
    __IO uint16_t PCRE12;
    __IO uint16_t PFSRE12;
    __IO uint16_t PCRE13;
    __IO uint16_t PFSRE13;
    __IO uint16_t PCRE14;
    __IO uint16_t PFSRE14;
    __IO uint16_t PCRE15;
    __IO uint16_t PFSRE15;
    __IO uint16_t PCRF0;
    __IO uint16_t PFSRF0;
    __IO uint16_t PCRF1;
    __IO uint16_t PFSRF1;
    __IO uint16_t PCRF2;
    __IO uint16_t PFSRF2;
    __IO uint16_t PCRF3;
    __IO uint16_t PFSRF3;
    __IO uint16_t PCRF4;
    __IO uint16_t PFSRF4;
    __IO uint16_t PCRF5;
    __IO uint16_t PFSRF5;
    __IO uint16_t PCRF6;
    __IO uint16_t PFSRF6;
    __IO uint16_t PCRF7;
    __IO uint16_t PFSRF7;
    __IO uint16_t PCRF8;
    __IO uint16_t PFSRF8;
    __IO uint16_t PCRF9;
    __IO uint16_t PFSRF9;
    __IO uint16_t PCRF10;
    __IO uint16_t PFSRF10;
    __IO uint16_t PCRF11;
    __IO uint16_t PFSRF11;
    __IO uint16_t PCRF12;
    __IO uint16_t PFSRF12;
    __IO uint16_t PCRF13;
    __IO uint16_t PFSRF13;
    __IO uint16_t PCRF14;
    __IO uint16_t PFSRF14;
    __IO uint16_t PCRF15;
    __IO uint16_t PFSRF15;
    __IO uint16_t PCRG0;
    __IO uint16_t PFSRG0;
    __IO uint16_t PCRG1;
    __IO uint16_t PFSRG1;
    __IO uint16_t PCRG2;
    __IO uint16_t PFSRG2;
    __IO uint16_t PCRG3;
    __IO uint16_t PFSRG3;
    __IO uint16_t PCRG4;
    __IO uint16_t PFSRG4;
    __IO uint16_t PCRG5;
    __IO uint16_t PFSRG5;
    __IO uint16_t PCRG6;
    __IO uint16_t PFSRG6;
    __IO uint16_t PCRG7;
    __IO uint16_t PFSRG7;
    __IO uint16_t PCRG8;
    __IO uint16_t PFSRG8;
    __IO uint16_t PCRG9;
    __IO uint16_t PFSRG9;
    __IO uint16_t PCRG10;
    __IO uint16_t PFSRG10;
    __IO uint16_t PCRG11;
    __IO uint16_t PFSRG11;
    __IO uint16_t PCRG12;
    __IO uint16_t PFSRG12;
    __IO uint16_t PCRG13;
    __IO uint16_t PFSRG13;
    __IO uint16_t PCRG14;
    __IO uint16_t PFSRG14;
    __IO uint16_t PCRG15;
    __IO uint16_t PFSRG15;
    __IO uint16_t PCRH0;
    __IO uint16_t PFSRH0;
    __IO uint16_t PCRH1;
    __IO uint16_t PFSRH1;
    __IO uint16_t PCRH2;
    __IO uint16_t PFSRH2;
    __IO uint16_t PCRH3;
    __IO uint16_t PFSRH3;
    __IO uint16_t PCRH4;
    __IO uint16_t PFSRH4;
    __IO uint16_t PCRH5;
    __IO uint16_t PFSRH5;
    __IO uint16_t PCRH6;
    __IO uint16_t PFSRH6;
    __IO uint16_t PCRH7;
    __IO uint16_t PFSRH7;
    __IO uint16_t PCRH8;
    __IO uint16_t PFSRH8;
    __IO uint16_t PCRH9;
    __IO uint16_t PFSRH9;
    __IO uint16_t PCRH10;
    __IO uint16_t PFSRH10;
    __IO uint16_t PCRH11;
    __IO uint16_t PFSRH11;
    __IO uint16_t PCRH12;
    __IO uint16_t PFSRH12;
    __IO uint16_t PCRH13;
    __IO uint16_t PFSRH13;
    __IO uint16_t PCRH14;
    __IO uint16_t PFSRH14;
    __IO uint16_t PCRH15;
    __IO uint16_t PFSRH15;
    __IO uint16_t PCRI0;
    __IO uint16_t PFSRI0;
    __IO uint16_t PCRI1;
    __IO uint16_t PFSRI1;
    __IO uint16_t PCRI2;
    __IO uint16_t PFSRI2;
    __IO uint16_t PCRI3;
    __IO uint16_t PFSRI3;
    __IO uint16_t PCRI4;
    __IO uint16_t PFSRI4;
    __IO uint16_t PCRI5;
    __IO uint16_t PFSRI5;
    __IO uint16_t PCRI6;
    __IO uint16_t PFSRI6;
    __IO uint16_t PCRI7;
    __IO uint16_t PFSRI7;
    __IO uint16_t PCRI8;
    __IO uint16_t PFSRI8;
    __IO uint16_t PCRI9;
    __IO uint16_t PFSRI9;
    __IO uint16_t PCRI10;
    __IO uint16_t PFSRI10;
    __IO uint16_t PCRI11;
    __IO uint16_t PFSRI11;
    __IO uint16_t PCRI12;
    __IO uint16_t PFSRI12;
    __IO uint16_t PCRI13;
    __IO uint16_t PFSRI13;
} CM_GPIO_TypeDef;

/**
 * @brief HASH
 */
typedef struct {
    __IO uint32_t CR;
    uint8_t RESERVED0[12];
    __IO uint32_t HR7;
    __IO uint32_t HR6;
    __IO uint32_t HR5;
    __IO uint32_t HR4;
    __IO uint32_t HR3;
    __IO uint32_t HR2;
    __IO uint32_t HR1;
    __IO uint32_t HR0;
    uint8_t RESERVED1[16];
    __IO uint32_t DR15;
    __IO uint32_t DR14;
    __IO uint32_t DR13;
    __IO uint32_t DR12;
    __IO uint32_t DR11;
    __IO uint32_t DR10;
    __IO uint32_t DR9;
    __IO uint32_t DR8;
    __IO uint32_t DR7;
    __IO uint32_t DR6;
    __IO uint32_t DR5;
    __IO uint32_t DR4;
    __IO uint32_t DR3;
    __IO uint32_t DR2;
    __IO uint32_t DR1;
    __IO uint32_t DR0;
} CM_HASH_TypeDef;

/**
 * @brief HRPWM
 */
typedef struct {
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t CR4;
    __IO uint32_t CR5;
    __IO uint32_t CR6;
    __IO uint32_t CR7;
    __IO uint32_t CR8;
    __IO uint32_t CR9;
    __IO uint32_t CR10;
    __IO uint32_t CR11;
    __IO uint32_t CR12;
    __IO uint32_t CR13;
    __IO uint32_t CR14;
    __IO uint32_t CR15;
    __IO uint32_t CR16;
    uint8_t RESERVED0[16];
    __IO uint32_t CALCR0;
    __IO uint32_t CALCR1;
} CM_HRPWM_TypeDef;

/**
 * @brief I2C
 */
typedef struct {
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t CR4;
    __IO uint32_t SLR0;
    __IO uint32_t SLR1;
    __IO uint32_t SLTR;
    __IO uint32_t SR;
    __O  uint32_t CLR;
    __O  uint8_t  DTR;
    uint8_t RESERVED0[3];
    __I  uint8_t  DRR;
    uint8_t RESERVED1[3];
    __IO uint32_t CCR;
    __IO uint32_t FLTR;
} CM_I2C_TypeDef;

/**
 * @brief I2S
 */
typedef struct {
    __IO uint32_t CTRL;
    __I  uint32_t SR;
    __IO uint32_t ER;
    __IO uint32_t CFGR;
    __O  uint32_t TXBUF;
    __I  uint32_t RXBUF;
    __IO uint32_t PR;
} CM_I2S_TypeDef;

/**
 * @brief ICG
 */
typedef struct {
    __I  uint32_t ICG0;
    __I  uint32_t ICG1;
    uint8_t RESERVED0[4];
    __I  uint32_t ICG3;
} CM_ICG_TypeDef;

/**
 * @brief INTC
 */
typedef struct {
    __IO uint32_t NOCCR;
    __IO uint32_t NMIENR;
    __IO uint32_t NMIFR;
    __IO uint32_t NMICFR;
    __IO uint32_t EIRQCR0;
    __IO uint32_t EIRQCR1;
    __IO uint32_t EIRQCR2;
    __IO uint32_t EIRQCR3;
    __IO uint32_t EIRQCR4;
    __IO uint32_t EIRQCR5;
    __IO uint32_t EIRQCR6;
    __IO uint32_t EIRQCR7;
    __IO uint32_t EIRQCR8;
    __IO uint32_t EIRQCR9;
    __IO uint32_t EIRQCR10;
    __IO uint32_t EIRQCR11;
    __IO uint32_t EIRQCR12;
    __IO uint32_t EIRQCR13;
    __IO uint32_t EIRQCR14;
    __IO uint32_t EIRQCR15;
    __IO uint32_t WUPEN;
    __IO uint32_t EIFR;
    __IO uint32_t EIFCR;
    __IO uint32_t SEL0;
    __IO uint32_t SEL1;
    __IO uint32_t SEL2;
    __IO uint32_t SEL3;
    __IO uint32_t SEL4;
    __IO uint32_t SEL5;
    __IO uint32_t SEL6;
    __IO uint32_t SEL7;
    __IO uint32_t SEL8;
    __IO uint32_t SEL9;
    __IO uint32_t SEL10;
    __IO uint32_t SEL11;
    __IO uint32_t SEL12;
    __IO uint32_t SEL13;
    __IO uint32_t SEL14;
    __IO uint32_t SEL15;
    __IO uint32_t SEL16;
    __IO uint32_t SEL17;
    __IO uint32_t SEL18;
    __IO uint32_t SEL19;
    __IO uint32_t SEL20;
    __IO uint32_t SEL21;
    __IO uint32_t SEL22;
    __IO uint32_t SEL23;
    __IO uint32_t SEL24;
    __IO uint32_t SEL25;
    __IO uint32_t SEL26;
    __IO uint32_t SEL27;
    __IO uint32_t SEL28;
    __IO uint32_t SEL29;
    __IO uint32_t SEL30;
    __IO uint32_t SEL31;
    __IO uint32_t SEL32;
    __IO uint32_t SEL33;
    __IO uint32_t SEL34;
    __IO uint32_t SEL35;
    __IO uint32_t SEL36;
    __IO uint32_t SEL37;
    __IO uint32_t SEL38;
    __IO uint32_t SEL39;
    __IO uint32_t SEL40;
    __IO uint32_t SEL41;
    __IO uint32_t SEL42;
    __IO uint32_t SEL43;
    __IO uint32_t SEL44;
    __IO uint32_t SEL45;
    __IO uint32_t SEL46;
    __IO uint32_t SEL47;
    __IO uint32_t SEL48;
    __IO uint32_t SEL49;
    __IO uint32_t SEL50;
    __IO uint32_t SEL51;
    __IO uint32_t SEL52;
    __IO uint32_t SEL53;
    __IO uint32_t SEL54;
    __IO uint32_t SEL55;
    __IO uint32_t SEL56;
    __IO uint32_t SEL57;
    __IO uint32_t SEL58;
    __IO uint32_t SEL59;
    __IO uint32_t SEL60;
    __IO uint32_t SEL61;
    __IO uint32_t SEL62;
    __IO uint32_t SEL63;
    __IO uint32_t SEL64;
    __IO uint32_t SEL65;
    __IO uint32_t SEL66;
    __IO uint32_t SEL67;
    __IO uint32_t SEL68;
    __IO uint32_t SEL69;
    __IO uint32_t SEL70;
    __IO uint32_t SEL71;
    __IO uint32_t SEL72;
    __IO uint32_t SEL73;
    __IO uint32_t SEL74;
    __IO uint32_t SEL75;
    __IO uint32_t SEL76;
    __IO uint32_t SEL77;
    __IO uint32_t SEL78;
    __IO uint32_t SEL79;
    __IO uint32_t SEL80;
    __IO uint32_t SEL81;
    __IO uint32_t SEL82;
    __IO uint32_t SEL83;
    __IO uint32_t SEL84;
    __IO uint32_t SEL85;
    __IO uint32_t SEL86;
    __IO uint32_t SEL87;
    __IO uint32_t SEL88;
    __IO uint32_t SEL89;
    __IO uint32_t SEL90;
    __IO uint32_t SEL91;
    __IO uint32_t SEL92;
    __IO uint32_t SEL93;
    __IO uint32_t SEL94;
    __IO uint32_t SEL95;
    __IO uint32_t SEL96;
    __IO uint32_t SEL97;
    __IO uint32_t SEL98;
    __IO uint32_t SEL99;
    __IO uint32_t SEL100;
    __IO uint32_t SEL101;
    __IO uint32_t SEL102;
    __IO uint32_t SEL103;
    __IO uint32_t SEL104;
    __IO uint32_t SEL105;
    __IO uint32_t SEL106;
    __IO uint32_t SEL107;
    __IO uint32_t SEL108;
    __IO uint32_t SEL109;
    __IO uint32_t SEL110;
    __IO uint32_t SEL111;
    __IO uint32_t SEL112;
    __IO uint32_t SEL113;
    __IO uint32_t SEL114;
    __IO uint32_t SEL115;
    __IO uint32_t SEL116;
    __IO uint32_t SEL117;
    __IO uint32_t SEL118;
    __IO uint32_t SEL119;
    __IO uint32_t SEL120;
    __IO uint32_t SEL121;
    __IO uint32_t SEL122;
    __IO uint32_t SEL123;
    __IO uint32_t SEL124;
    __IO uint32_t SEL125;
    __IO uint32_t SEL126;
    __IO uint32_t SEL127;
    __IO uint32_t VSSEL128;
    __IO uint32_t VSSEL129;
    __IO uint32_t VSSEL130;
    __IO uint32_t VSSEL131;
    __IO uint32_t VSSEL132;
    __IO uint32_t VSSEL133;
    __IO uint32_t VSSEL134;
    __IO uint32_t VSSEL135;
    __IO uint32_t VSSEL136;
    __IO uint32_t VSSEL137;
    __IO uint32_t VSSEL138;
    __IO uint32_t VSSEL139;
    __IO uint32_t VSSEL140;
    __IO uint32_t VSSEL141;
    __IO uint32_t VSSEL142;
    __IO uint32_t VSSEL143;
    __IO uint32_t SWIER;
    __IO uint32_t EVTER;
    __IO uint32_t IER;
} CM_INTC_TypeDef;

/**
 * @brief KEYSCAN
 */
typedef struct {
    __IO uint32_t SCR;
    __IO uint32_t SER;
    __IO uint32_t SSR;
} CM_KEYSCAN_TypeDef;

/**
 * @brief MAU
 */
typedef struct {
    __IO uint32_t CSR;
    __IO uint32_t DTR0;
    uint8_t RESERVED0[4];
    __IO uint32_t RTR0;
    __IO uint32_t DTR1;
    __IO uint32_t RTR1;
} CM_MAU_TypeDef;

/**
 * @brief MPU
 */
typedef struct {
    __IO uint32_t RGD0;
    __IO uint32_t RGD1;
    __IO uint32_t RGD2;
    __IO uint32_t RGD3;
    __IO uint32_t RGD4;
    __IO uint32_t RGD5;
    __IO uint32_t RGD6;
    __IO uint32_t RGD7;
    __IO uint32_t RGD8;
    __IO uint32_t RGD9;
    __IO uint32_t RGD10;
    __IO uint32_t RGD11;
    __IO uint32_t RGD12;
    __IO uint32_t RGD13;
    __IO uint32_t RGD14;
    __IO uint32_t RGD15;
    __I  uint32_t SR;
    __O  uint32_t ECLR;
    __IO uint32_t WP;
    __IO uint32_t IPPR;
    __IO uint32_t S1RGE;
    __IO uint32_t S1RGWP;
    __IO uint32_t S1RGRP;
    __IO uint32_t S1CR;
    __IO uint32_t S2RGE;
    __IO uint32_t S2RGWP;
    __IO uint32_t S2RGRP;
    __IO uint32_t S2CR;
    __IO uint32_t FRGE;
    __IO uint32_t FRGWP;
    __IO uint32_t FRGRP;
    __IO uint32_t FCR;
    __IO uint32_t HRGE;
    __IO uint32_t HRGWP;
    __IO uint32_t HRGRP;
    __IO uint32_t HCR;
    __IO uint32_t ERGE;
    __IO uint32_t ERGWP;
    __IO uint32_t ERGRP;
    __IO uint32_t ECR;
} CM_MPU_TypeDef;

/**
 * @brief NFC
 */
typedef struct {
    __IO uint32_t DATR_BASE;
    uint8_t RESERVED0[32764];
    __IO uint32_t CMDR;
    __IO uint32_t IDXR0;
    uint8_t RESERVED1[40];
    __IO uint32_t IENR;
    __IO uint32_t ISTR;
    __IO uint32_t IRSR;
    uint8_t RESERVED2[12];
    __IO uint32_t IDXR1;
    __IO uint32_t TMCR0;
    __IO uint32_t TMCR1;
    __IO uint32_t BACR;
    uint8_t RESERVED3[4];
    __IO uint32_t TMCR2;
    __I  uint32_t ECCR0;
    __I  uint32_t ECCR1;
    __I  uint32_t ECCR2;
    __I  uint32_t ECCR3;
    __I  uint32_t ECCR4;
    __I  uint32_t ECCR5;
    __I  uint32_t ECCR6;
    union {
        __I  uint32_t ECCR7;
        __I  uint32_t ECC_STAT;
    };
    union {
        __I  uint32_t ECCR8;
        __I  uint32_t ECC_SYND0_0;
    };
    union {
        __I  uint32_t ECCR9;
        __I  uint32_t ECC_SYND0_1;
    };
    union {
        __I  uint32_t ECCR10;
        __I  uint32_t ECC_SYND0_2;
    };
    union {
        __I  uint32_t ECCR11;
        __I  uint32_t ECC_SYND0_3;
    };
    union {
        __I  uint32_t ECCR12;
        __I  uint32_t ECC_SYND1_0;
    };
    union {
        __I  uint32_t ECCR13;
        __I  uint32_t ECC_SYND1_1;
    };
    union {
        __I  uint32_t ECCR14;
        __I  uint32_t ECC_SYND1_2;
    };
    union {
        __I  uint32_t ECCR15;
        __I  uint32_t ECC_SYND1_3;
    };
    __I  uint32_t ECC_SYND2_0;
    __I  uint32_t ECC_SYND2_1;
    __I  uint32_t ECC_SYND2_2;
    __I  uint32_t ECC_SYND2_3;
    __I  uint32_t ECC_SYND3_0;
    __I  uint32_t ECC_SYND3_1;
    __I  uint32_t ECC_SYND3_2;
    __I  uint32_t ECC_SYND3_3;
    __I  uint32_t ECC_SYND4_0;
    __I  uint32_t ECC_SYND4_1;
    __I  uint32_t ECC_SYND4_2;
    __I  uint32_t ECC_SYND4_3;
    __I  uint32_t ECC_SYND5_0;
    __I  uint32_t ECC_SYND5_1;
    __I  uint32_t ECC_SYND5_2;
    __I  uint32_t ECC_SYND5_3;
    __I  uint32_t ECC_SYND6_0;
    __I  uint32_t ECC_SYND6_1;
    __I  uint32_t ECC_SYND6_2;
    __I  uint32_t ECC_SYND6_3;
    __I  uint32_t ECC_SYND7_0;
    __I  uint32_t ECC_SYND7_1;
    __I  uint32_t ECC_SYND7_2;
    __I  uint32_t ECC_SYND7_3;
    __I  uint32_t ECC_SYND8_0;
    __I  uint32_t ECC_SYND8_1;
    __I  uint32_t ECC_SYND8_2;
    __I  uint32_t ECC_SYND8_3;
    __I  uint32_t ECC_SYND9_0;
    __I  uint32_t ECC_SYND9_1;
    __I  uint32_t ECC_SYND9_2;
    __I  uint32_t ECC_SYND9_3;
    __I  uint32_t ECC_SYND10_0;
    __I  uint32_t ECC_SYND10_1;
    __I  uint32_t ECC_SYND10_2;
    __I  uint32_t ECC_SYND10_3;
    __I  uint32_t ECC_SYND11_0;
    __I  uint32_t ECC_SYND11_1;
    __I  uint32_t ECC_SYND11_2;
    __I  uint32_t ECC_SYND11_3;
    __I  uint32_t ECC_SYND12_0;
    __I  uint32_t ECC_SYND12_1;
    __I  uint32_t ECC_SYND12_2;
    __I  uint32_t ECC_SYND12_3;
    __I  uint32_t ECC_SYND13_0;
    __I  uint32_t ECC_SYND13_1;
    __I  uint32_t ECC_SYND13_2;
    __I  uint32_t ECC_SYND13_3;
    __I  uint32_t ECC_SYND14_0;
    __I  uint32_t ECC_SYND14_1;
    __I  uint32_t ECC_SYND14_2;
    __I  uint32_t ECC_SYND14_3;
    __I  uint32_t ECC_SYND15_0;
    __I  uint32_t ECC_SYND15_1;
    __I  uint32_t ECC_SYND15_2;
    __I  uint32_t ECC_SYND15_3;
} CM_NFC_TypeDef;

/**
 * @brief OTS
 */
typedef struct {
    uint8_t RESERVED0[224];
    __IO uint32_t PDR1;
    uint8_t RESERVED1[16];
    __IO uint32_t PDR2;
    __IO uint32_t PDR3;
    uint8_t RESERVED2[237828];
    __IO uint16_t CTL;
    __IO uint16_t DR1;
    __IO uint16_t DR2;
    __IO uint16_t ECR;
} CM_OTS_TypeDef;

/**
 * @brief PERIC
 */
typedef struct {
    __IO uint32_t USB_SYCTLREG;
    __IO uint32_t SDIOC_SYCTLREG;
    __IO uint32_t NFC_STCR;
    union {
        __IO uint32_t NFC_ENAR;
        __IO uint32_t SMC_ENAR;
        __IO uint32_t DMC_ENAR;
    };
    uint8_t RESERVED0[12];
    __IO uint32_t USART1_NFC;
    uint8_t RESERVED1[8];
    __I  uint32_t NFC_STSR;
} CM_PERIC_TypeDef;

/**
 * @brief PWC
 */
typedef struct {
    __IO uint32_t FCG0;
    __IO uint32_t FCG1;
    __IO uint32_t FCG2;
    __IO uint32_t FCG3;
    __IO uint32_t FCG0PC;
    uint8_t RESERVED0[17436];
    __IO uint8_t  VBATRSTR;
    uint8_t RESERVED1[15];
    __IO uint8_t  VBATCR;
    uint8_t RESERVED2[15];
    __IO uint8_t  WKTC0;
    uint8_t RESERVED3[3];
    __IO uint8_t  WKTC1;
    uint8_t RESERVED4[3];
    __IO uint8_t  WKTC2;
    uint8_t RESERVED5[423];
    __IO uint8_t  BKR0;
    uint8_t RESERVED6[3];
    __IO uint8_t  BKR1;
    uint8_t RESERVED7[3];
    __IO uint8_t  BKR2;
    uint8_t RESERVED8[3];
    __IO uint8_t  BKR3;
    uint8_t RESERVED9[3];
    __IO uint8_t  BKR4;
    uint8_t RESERVED10[3];
    __IO uint8_t  BKR5;
    uint8_t RESERVED11[3];
    __IO uint8_t  BKR6;
    uint8_t RESERVED12[3];
    __IO uint8_t  BKR7;
    uint8_t RESERVED13[3];
    __IO uint8_t  BKR8;
    uint8_t RESERVED14[3];
    __IO uint8_t  BKR9;
    uint8_t RESERVED15[3];
    __IO uint8_t  BKR10;
    uint8_t RESERVED16[3];
    __IO uint8_t  BKR11;
    uint8_t RESERVED17[3];
    __IO uint8_t  BKR12;
    uint8_t RESERVED18[3];
    __IO uint8_t  BKR13;
    uint8_t RESERVED19[3];
    __IO uint8_t  BKR14;
    uint8_t RESERVED20[3];
    __IO uint8_t  BKR15;
    uint8_t RESERVED21[3];
    __IO uint8_t  BKR16;
    uint8_t RESERVED22[3];
    __IO uint8_t  BKR17;
    uint8_t RESERVED23[3];
    __IO uint8_t  BKR18;
    uint8_t RESERVED24[3];
    __IO uint8_t  BKR19;
    uint8_t RESERVED25[3];
    __IO uint8_t  BKR20;
    uint8_t RESERVED26[3];
    __IO uint8_t  BKR21;
    uint8_t RESERVED27[3];
    __IO uint8_t  BKR22;
    uint8_t RESERVED28[3];
    __IO uint8_t  BKR23;
    uint8_t RESERVED29[3];
    __IO uint8_t  BKR24;
    uint8_t RESERVED30[3];
    __IO uint8_t  BKR25;
    uint8_t RESERVED31[3];
    __IO uint8_t  BKR26;
    uint8_t RESERVED32[3];
    __IO uint8_t  BKR27;
    uint8_t RESERVED33[3];
    __IO uint8_t  BKR28;
    uint8_t RESERVED34[3];
    __IO uint8_t  BKR29;
    uint8_t RESERVED35[3];
    __IO uint8_t  BKR30;
    uint8_t RESERVED36[3];
    __IO uint8_t  BKR31;
    uint8_t RESERVED37[3];
    __IO uint8_t  BKR32;
    uint8_t RESERVED38[3];
    __IO uint8_t  BKR33;
    uint8_t RESERVED39[3];
    __IO uint8_t  BKR34;
    uint8_t RESERVED40[3];
    __IO uint8_t  BKR35;
    uint8_t RESERVED41[3];
    __IO uint8_t  BKR36;
    uint8_t RESERVED42[3];
    __IO uint8_t  BKR37;
    uint8_t RESERVED43[3];
    __IO uint8_t  BKR38;
    uint8_t RESERVED44[3];
    __IO uint8_t  BKR39;
    uint8_t RESERVED45[3];
    __IO uint8_t  BKR40;
    uint8_t RESERVED46[3];
    __IO uint8_t  BKR41;
    uint8_t RESERVED47[3];
    __IO uint8_t  BKR42;
    uint8_t RESERVED48[3];
    __IO uint8_t  BKR43;
    uint8_t RESERVED49[3];
    __IO uint8_t  BKR44;
    uint8_t RESERVED50[3];
    __IO uint8_t  BKR45;
    uint8_t RESERVED51[3];
    __IO uint8_t  BKR46;
    uint8_t RESERVED52[3];
    __IO uint8_t  BKR47;
    uint8_t RESERVED53[3];
    __IO uint8_t  BKR48;
    uint8_t RESERVED54[3];
    __IO uint8_t  BKR49;
    uint8_t RESERVED55[3];
    __IO uint8_t  BKR50;
    uint8_t RESERVED56[3];
    __IO uint8_t  BKR51;
    uint8_t RESERVED57[3];
    __IO uint8_t  BKR52;
    uint8_t RESERVED58[3];
    __IO uint8_t  BKR53;
    uint8_t RESERVED59[3];
    __IO uint8_t  BKR54;
    uint8_t RESERVED60[3];
    __IO uint8_t  BKR55;
    uint8_t RESERVED61[3];
    __IO uint8_t  BKR56;
    uint8_t RESERVED62[3];
    __IO uint8_t  BKR57;
    uint8_t RESERVED63[3];
    __IO uint8_t  BKR58;
    uint8_t RESERVED64[3];
    __IO uint8_t  BKR59;
    uint8_t RESERVED65[3];
    __IO uint8_t  BKR60;
    uint8_t RESERVED66[3];
    __IO uint8_t  BKR61;
    uint8_t RESERVED67[3];
    __IO uint8_t  BKR62;
    uint8_t RESERVED68[3];
    __IO uint8_t  BKR63;
    uint8_t RESERVED69[3];
    __IO uint8_t  BKR64;
    uint8_t RESERVED70[3];
    __IO uint8_t  BKR65;
    uint8_t RESERVED71[3];
    __IO uint8_t  BKR66;
    uint8_t RESERVED72[3];
    __IO uint8_t  BKR67;
    uint8_t RESERVED73[3];
    __IO uint8_t  BKR68;
    uint8_t RESERVED74[3];
    __IO uint8_t  BKR69;
    uint8_t RESERVED75[3];
    __IO uint8_t  BKR70;
    uint8_t RESERVED76[3];
    __IO uint8_t  BKR71;
    uint8_t RESERVED77[3];
    __IO uint8_t  BKR72;
    uint8_t RESERVED78[3];
    __IO uint8_t  BKR73;
    uint8_t RESERVED79[3];
    __IO uint8_t  BKR74;
    uint8_t RESERVED80[3];
    __IO uint8_t  BKR75;
    uint8_t RESERVED81[3];
    __IO uint8_t  BKR76;
    uint8_t RESERVED82[3];
    __IO uint8_t  BKR77;
    uint8_t RESERVED83[3];
    __IO uint8_t  BKR78;
    uint8_t RESERVED84[3];
    __IO uint8_t  BKR79;
    uint8_t RESERVED85[3];
    __IO uint8_t  BKR80;
    uint8_t RESERVED86[3];
    __IO uint8_t  BKR81;
    uint8_t RESERVED87[3];
    __IO uint8_t  BKR82;
    uint8_t RESERVED88[3];
    __IO uint8_t  BKR83;
    uint8_t RESERVED89[3];
    __IO uint8_t  BKR84;
    uint8_t RESERVED90[3];
    __IO uint8_t  BKR85;
    uint8_t RESERVED91[3];
    __IO uint8_t  BKR86;
    uint8_t RESERVED92[3];
    __IO uint8_t  BKR87;
    uint8_t RESERVED93[3];
    __IO uint8_t  BKR88;
    uint8_t RESERVED94[3];
    __IO uint8_t  BKR89;
    uint8_t RESERVED95[3];
    __IO uint8_t  BKR90;
    uint8_t RESERVED96[3];
    __IO uint8_t  BKR91;
    uint8_t RESERVED97[3];
    __IO uint8_t  BKR92;
    uint8_t RESERVED98[3];
    __IO uint8_t  BKR93;
    uint8_t RESERVED99[3];
    __IO uint8_t  BKR94;
    uint8_t RESERVED100[3];
    __IO uint8_t  BKR95;
    uint8_t RESERVED101[3];
    __IO uint8_t  BKR96;
    uint8_t RESERVED102[3];
    __IO uint8_t  BKR97;
    uint8_t RESERVED103[3];
    __IO uint8_t  BKR98;
    uint8_t RESERVED104[3];
    __IO uint8_t  BKR99;
    uint8_t RESERVED105[3];
    __IO uint8_t  BKR100;
    uint8_t RESERVED106[3];
    __IO uint8_t  BKR101;
    uint8_t RESERVED107[3];
    __IO uint8_t  BKR102;
    uint8_t RESERVED108[3];
    __IO uint8_t  BKR103;
    uint8_t RESERVED109[3];
    __IO uint8_t  BKR104;
    uint8_t RESERVED110[3];
    __IO uint8_t  BKR105;
    uint8_t RESERVED111[3];
    __IO uint8_t  BKR106;
    uint8_t RESERVED112[3];
    __IO uint8_t  BKR107;
    uint8_t RESERVED113[3];
    __IO uint8_t  BKR108;
    uint8_t RESERVED114[3];
    __IO uint8_t  BKR109;
    uint8_t RESERVED115[3];
    __IO uint8_t  BKR110;
    uint8_t RESERVED116[3];
    __IO uint8_t  BKR111;
    uint8_t RESERVED117[3];
    __IO uint8_t  BKR112;
    uint8_t RESERVED118[3];
    __IO uint8_t  BKR113;
    uint8_t RESERVED119[3];
    __IO uint8_t  BKR114;
    uint8_t RESERVED120[3];
    __IO uint8_t  BKR115;
    uint8_t RESERVED121[3];
    __IO uint8_t  BKR116;
    uint8_t RESERVED122[3];
    __IO uint8_t  BKR117;
    uint8_t RESERVED123[3];
    __IO uint8_t  BKR118;
    uint8_t RESERVED124[3];
    __IO uint8_t  BKR119;
    uint8_t RESERVED125[3];
    __IO uint8_t  BKR120;
    uint8_t RESERVED126[3];
    __IO uint8_t  BKR121;
    uint8_t RESERVED127[3];
    __IO uint8_t  BKR122;
    uint8_t RESERVED128[3];
    __IO uint8_t  BKR123;
    uint8_t RESERVED129[3];
    __IO uint8_t  BKR124;
    uint8_t RESERVED130[3];
    __IO uint8_t  BKR125;
    uint8_t RESERVED131[3];
    __IO uint8_t  BKR126;
    uint8_t RESERVED132[3];
    __IO uint8_t  BKR127;
    uint8_t RESERVED133[1027];
    __IO uint8_t  PWRC0;
    uint8_t RESERVED134[3];
    __IO uint8_t  PWRC1;
    uint8_t RESERVED135[3];
    __IO uint8_t  PWRC2;
    uint8_t RESERVED136[3];
    __IO uint8_t  PWRC3;
    uint8_t RESERVED137[3];
    __IO uint8_t  PWRC4;
    uint8_t RESERVED138[3];
    __IO uint8_t  PVDCR0;
    uint8_t RESERVED139[3];
    __IO uint8_t  PVDCR1;
    uint8_t RESERVED140[3];
    __IO uint8_t  PVDFCR;
    uint8_t RESERVED141[3];
    __IO uint8_t  PVDLCR;
    uint8_t RESERVED142[7];
    __IO uint8_t  PDWKE0;
    uint8_t RESERVED143[3];
    __IO uint8_t  PDWKE1;
    uint8_t RESERVED144[3];
    __IO uint8_t  PDWKE2;
    uint8_t RESERVED145[3];
    __IO uint8_t  PDWKES;
    uint8_t RESERVED146[3];
    __IO uint8_t  PDWKF0;
    uint8_t RESERVED147[3];
    __IO uint8_t  PDWKF1;
    uint8_t RESERVED148[163];
    __IO uint32_t RAMPC0;
    __IO uint16_t RAMOPM;
    uint8_t RESERVED149[2];
    __IO uint32_t PRAMLPC;
    uint8_t RESERVED150[4];
    __IO uint8_t  PVDICR;
    uint8_t RESERVED151[3];
    __IO uint8_t  PVDDSR;
    uint8_t RESERVED152[29463];
    __IO uint16_t STPMCR;
    uint8_t RESERVED153[1008];
    __IO uint16_t FPRC;
} CM_PWC_TypeDef;

/**
 * @brief QSPI
 */
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t CSCR;
    __IO uint32_t FCR;
    __IO uint32_t SR;
    __IO uint32_t DCOM;
    __IO uint32_t CCMD;
    __IO uint32_t XCMD;
    uint8_t RESERVED0[8];
    __O  uint32_t SR2;
    uint8_t RESERVED1[2012];
    __IO uint32_t EXAR;
} CM_QSPI_TypeDef;

/**
 * @brief RMU
 */
typedef struct {
    uint8_t RESERVED0[248];
    __IO uint8_t  PRSTCR0;
    uint8_t RESERVED1[3];
    __IO uint32_t RSTF0;
} CM_RMU_TypeDef;

/**
 * @brief RTC
 */
typedef struct {
    __IO uint8_t  CR0;
    uint8_t RESERVED0[3];
    __IO uint8_t  CR1;
    uint8_t RESERVED1[3];
    __IO uint8_t  CR2;
    uint8_t RESERVED2[3];
    __IO uint8_t  CR3;
    uint8_t RESERVED3[3];
    __IO uint8_t  SEC;
    uint8_t RESERVED4[3];
    __IO uint8_t  MIN;
    uint8_t RESERVED5[3];
    __IO uint8_t  HOUR;
    uint8_t RESERVED6[3];
    __IO uint8_t  WEEK;
    uint8_t RESERVED7[3];
    __IO uint8_t  DAY;
    uint8_t RESERVED8[3];
    __IO uint8_t  MON;
    uint8_t RESERVED9[3];
    __IO uint8_t  YEAR;
    uint8_t RESERVED10[3];
    __IO uint8_t  ALMMIN;
    uint8_t RESERVED11[3];
    __IO uint8_t  ALMHOUR;
    uint8_t RESERVED12[3];
    __IO uint8_t  ALMWEEK;
    uint8_t RESERVED13[3];
    __IO uint8_t  ERRCRH;
    uint8_t RESERVED14[3];
    __IO uint8_t  ERRCRL;
    uint8_t RESERVED15[3];
    __IO uint8_t  TPCR0;
    uint8_t RESERVED16[3];
    __IO uint8_t  TPCR1;
    uint8_t RESERVED17[3];
    __IO uint8_t  TPSR;
    uint8_t RESERVED18[3];
    __IO uint8_t  SECTP;
    uint8_t RESERVED19[3];
    __IO uint8_t  MINTP;
    uint8_t RESERVED20[3];
    __IO uint8_t  HOURTP;
    uint8_t RESERVED21[3];
    __IO uint8_t  DAYTP;
    uint8_t RESERVED22[3];
    __IO uint8_t  MONTP;
} CM_RTC_TypeDef;

/**
 * @brief SDIOC
 */
typedef struct {
    uint8_t RESERVED0[4];
    __IO uint16_t BLKSIZE;
    __IO uint16_t BLKCNT;
    __IO uint16_t ARG0;
    __IO uint16_t ARG1;
    __IO uint16_t TRANSMODE;
    __IO uint16_t CMD;
    __I  uint16_t RESP0;
    __I  uint16_t RESP1;
    __I  uint16_t RESP2;
    __I  uint16_t RESP3;
    __I  uint16_t RESP4;
    __I  uint16_t RESP5;
    __I  uint16_t RESP6;
    __I  uint16_t RESP7;
    __IO uint16_t BUF0;
    __IO uint16_t BUF1;
    __I  uint32_t PSTAT;
    __IO uint8_t  HOSTCON;
    __IO uint8_t  PWRCON;
    __IO uint8_t  BLKGPCON;
    uint8_t RESERVED1[1];
    __IO uint16_t CLKCON;
    __IO uint8_t  TOUTCON;
    __IO uint8_t  SFTRST;
    __IO uint16_t NORINTST;
    __IO uint16_t ERRINTST;
    __IO uint16_t NORINTSTEN;
    __IO uint16_t ERRINTSTEN;
    __IO uint16_t NORINTSGEN;
    __IO uint16_t ERRINTSGEN;
    __I  uint16_t ATCERRST;
    uint8_t RESERVED2[18];
    __O  uint16_t FEA;
    __O  uint16_t FEE;
} CM_SDIOC_TypeDef;

/**
 * @brief SMC
 */
typedef struct {
    __I  uint32_t STSR;
    uint8_t RESERVED0[4];
    __O  uint32_t STCR0;
    __O  uint32_t STCR1;
    __O  uint32_t CMDR;
    __O  uint32_t TMCR;
    __O  uint32_t CPCR;
    uint8_t RESERVED1[4];
    __IO uint32_t RFTR;
    uint8_t RESERVED2[220];
    __I  uint32_t TMSR0;
    __I  uint32_t CPSR0;
    uint8_t RESERVED3[24];
    __I  uint32_t TMSR1;
    __I  uint32_t CPSR1;
    uint8_t RESERVED4[24];
    __I  uint32_t TMSR2;
    __I  uint32_t CPSR2;
    uint8_t RESERVED5[24];
    __I  uint32_t TMSR3;
    __I  uint32_t CPSR3;
    uint8_t RESERVED6[152];
    __IO uint32_t BACR;
    uint8_t RESERVED7[4];
    __IO uint32_t CSCR0;
    __IO uint32_t CSCR1;
} CM_SMC_TypeDef;

/**
 * @brief SPI
 */
typedef struct {
    __IO uint32_t DR;
    __IO uint32_t CR1;
    uint8_t RESERVED0[4];
    __IO uint32_t CFG1;
    uint8_t RESERVED1[4];
    __IO uint32_t SR;
    __IO uint32_t CFG2;
} CM_SPI_TypeDef;

/**
 * @brief SRAMC
 */
typedef struct {
    __IO uint32_t WTCR;
    __IO uint32_t WTPR;
    __IO uint32_t CKCR;
    __IO uint32_t CKPR;
    __IO uint32_t CKSR;
} CM_SRAMC_TypeDef;

/**
 * @brief SWDT
 */
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t RR;
} CM_SWDT_TypeDef;

/**
 * @brief TMR0
 */
typedef struct {
    __IO uint32_t CNTAR;
    __IO uint32_t CNTBR;
    __IO uint32_t CMPAR;
    __IO uint32_t CMPBR;
    __IO uint32_t BCONR;
    __IO uint32_t STFLR;
} CM_TMR0_TypeDef;

/**
 * @brief TMR2
 */
typedef struct {
    __IO uint32_t CNTAR;
    __IO uint32_t CNTBR;
    __IO uint32_t CMPAR;
    __IO uint32_t CMPBR;
    __IO uint32_t BCONR;
    __IO uint32_t ICONR;
    __IO uint32_t PCONR;
    __IO uint32_t HCONR;
    __IO uint32_t STFLR;
} CM_TMR2_TypeDef;

/**
 * @brief TMR4
 */
typedef struct {
    uint8_t RESERVED0[2];
    __IO uint16_t OCCRUH;
    uint8_t RESERVED1[2];
    __IO uint16_t OCCRUL;
    uint8_t RESERVED2[2];
    __IO uint16_t OCCRVH;
    uint8_t RESERVED3[2];
    __IO uint16_t OCCRVL;
    uint8_t RESERVED4[2];
    __IO uint16_t OCCRWH;
    uint8_t RESERVED5[2];
    __IO uint16_t OCCRWL;
    __IO uint16_t OCSRU;
    __IO uint16_t OCERU;
    __IO uint16_t OCSRV;
    __IO uint16_t OCERV;
    __IO uint16_t OCSRW;
    __IO uint16_t OCERW;
    __IO uint16_t OCMRHUH;
    uint8_t RESERVED6[2];
    __IO uint32_t OCMRLUL;
    __IO uint16_t OCMRHVH;
    uint8_t RESERVED7[2];
    __IO uint32_t OCMRLVL;
    __IO uint16_t OCMRHWH;
    uint8_t RESERVED8[2];
    __IO uint32_t OCMRLWL;
    uint8_t RESERVED9[6];
    __IO uint16_t CPSR;
    uint8_t RESERVED10[2];
    __IO uint16_t CNTR;
    __IO uint16_t CCSR;
    __IO uint16_t CVPR;
    uint8_t RESERVED11[54];
    __IO uint16_t PFSRU;
    __IO uint16_t PDARU;
    __IO uint16_t PDBRU;
    uint8_t RESERVED12[2];
    __IO uint16_t PFSRV;
    __IO uint16_t PDARV;
    __IO uint16_t PDBRV;
    uint8_t RESERVED13[2];
    __IO uint16_t PFSRW;
    __IO uint16_t PDARW;
    __IO uint16_t PDBRW;
    __IO uint16_t POCRU;
    uint8_t RESERVED14[2];
    __IO uint16_t POCRV;
    uint8_t RESERVED15[2];
    __IO uint16_t POCRW;
    uint8_t RESERVED16[2];
    __IO uint16_t RCSR;
    uint8_t RESERVED17[12];
    __IO uint16_t SCCRUH;
    uint8_t RESERVED18[2];
    __IO uint16_t SCCRUL;
    uint8_t RESERVED19[2];
    __IO uint16_t SCCRVH;
    uint8_t RESERVED20[2];
    __IO uint16_t SCCRVL;
    uint8_t RESERVED21[2];
    __IO uint16_t SCCRWH;
    uint8_t RESERVED22[2];
    __IO uint16_t SCCRWL;
    __IO uint16_t SCSRUH;
    __IO uint16_t SCMRUH;
    __IO uint16_t SCSRUL;
    __IO uint16_t SCMRUL;
    __IO uint16_t SCSRVH;
    __IO uint16_t SCMRVH;
    __IO uint16_t SCSRVL;
    __IO uint16_t SCMRVL;
    __IO uint16_t SCSRWH;
    __IO uint16_t SCMRWH;
    __IO uint16_t SCSRWL;
    __IO uint16_t SCMRWL;
    __IO uint32_t PSCR;
    __IO uint16_t SCER;
} CM_TMR4_TypeDef;

/**
 * @brief TMR6
 */
typedef struct {
    __IO uint32_t CNTER;
    __IO uint32_t UPDAR;
    uint8_t RESERVED0[56];
    __IO uint32_t PERAR;
    __IO uint32_t PERBR;
    __IO uint32_t PERCR;
    uint8_t RESERVED1[52];
    __IO uint32_t GCMAR;
    __IO uint32_t GCMBR;
    __IO uint32_t GCMCR;
    __IO uint32_t GCMDR;
    __IO uint32_t GCMER;
    __IO uint32_t GCMFR;
    uint8_t RESERVED2[40];
    __IO uint32_t SCMAR;
    __IO uint32_t SCMBR;
    __IO uint32_t SCMCR;
    __IO uint32_t SCMDR;
    __IO uint32_t SCMER;
    __IO uint32_t SCMFR;
    uint8_t RESERVED3[40];
    __IO uint32_t DTUAR;
    __IO uint32_t DTDAR;
    __IO uint32_t DTUBR;
    __IO uint32_t DTDBR;
    uint8_t RESERVED4[48];
    __IO uint32_t GCONR;
    __IO uint32_t ICONR;
    __IO uint32_t BCONR;
    __IO uint32_t DCONR;
    uint8_t RESERVED5[4];
    __IO uint32_t PCNAR;
    __IO uint32_t PCNBR;
    __IO uint32_t FCNGR;
    __IO uint32_t VPERR;
    __IO uint32_t STFLR;
    uint8_t RESERVED6[24];
    __IO uint32_t HSTAR;
    __IO uint32_t HSTPR;
    __IO uint32_t HCLRR;
    __IO uint32_t HUPDR;
    __IO uint32_t HCPAR;
    __IO uint32_t HCPBR;
    __IO uint32_t HCUPR;
    __IO uint32_t HCDOR;
} CM_TMR6_TypeDef;

/**
 * @brief TMR6CR
 */
typedef struct {
    uint8_t RESERVED0[1004];
    __IO uint32_t FCNTR;
    __IO uint32_t SSTAR;
    __IO uint32_t SSTPR;
    __IO uint32_t SCLRR;
    __IO uint32_t SUPDR;
} CM_TMR6CR_TypeDef;

/**
 * @brief TMRA
 */
typedef struct {
    __IO uint16_t CNTER;
    uint8_t RESERVED0[2];
    __IO uint16_t PERAR;
    uint8_t RESERVED1[58];
    __IO uint16_t CMPAR1;
    uint8_t RESERVED2[2];
    __IO uint16_t CMPAR2;
    uint8_t RESERVED3[2];
    __IO uint16_t CMPAR3;
    uint8_t RESERVED4[2];
    __IO uint16_t CMPAR4;
    uint8_t RESERVED5[50];
    __IO uint8_t  BCSTRL;
    __IO uint8_t  BCSTRH;
    uint8_t RESERVED6[2];
    __IO uint16_t HCONR;
    uint8_t RESERVED7[2];
    __IO uint16_t HCUPR;
    uint8_t RESERVED8[2];
    __IO uint16_t HCDOR;
    uint8_t RESERVED9[2];
    __IO uint16_t ICONR;
    uint8_t RESERVED10[2];
    __IO uint16_t ECONR;
    uint8_t RESERVED11[2];
    __IO uint16_t FCONR;
    uint8_t RESERVED12[2];
    __IO uint16_t STFLR;
    uint8_t RESERVED13[34];
    __IO uint16_t BCONR1;
    uint8_t RESERVED14[6];
    __IO uint16_t BCONR2;
    uint8_t RESERVED15[54];
    __IO uint16_t CCONR1;
    uint8_t RESERVED16[2];
    __IO uint16_t CCONR2;
    uint8_t RESERVED17[2];
    __IO uint16_t CCONR3;
    uint8_t RESERVED18[2];
    __IO uint16_t CCONR4;
    uint8_t RESERVED19[50];
    __IO uint16_t PCONR1;
    uint8_t RESERVED20[2];
    __IO uint16_t PCONR2;
    uint8_t RESERVED21[2];
    __IO uint16_t PCONR3;
    uint8_t RESERVED22[2];
    __IO uint16_t PCONR4;
} CM_TMRA_TypeDef;

/**
 * @brief TRNG
 */
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t MR;
    uint8_t RESERVED0[4];
    __I  uint32_t DR0;
    __I  uint32_t DR1;
} CM_TRNG_TypeDef;

/**
 * @brief USART
 */
typedef struct {
    __I  uint32_t SR;
    __IO uint16_t TDR;
    __I  uint16_t RDR;
    __IO uint32_t BRR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t PR;
    __I  uint32_t LBMC;
} CM_USART_TypeDef;

/**
 * @brief USBFS
 */
typedef struct {
    __IO uint32_t GVBUSCFG;
    uint8_t RESERVED0[4];
    __IO uint32_t GAHBCFG;
    __IO uint32_t GUSBCFG;
    __IO uint32_t GRSTCTL;
    __IO uint32_t GINTSTS;
    __IO uint32_t GINTMSK;
    __I  uint32_t GRXSTSR;
    __I  uint32_t GRXSTSP;
    __IO uint32_t GRXFSIZ;
    __IO uint32_t HNPTXFSIZ;
    __I  uint32_t HNPTXSTS;
    uint8_t RESERVED1[12];
    __IO uint32_t CID;
    uint8_t RESERVED2[20];
    __IO uint32_t GLPMCFG;
    uint8_t RESERVED3[168];
    __IO uint32_t HPTXFSIZ;
    __IO uint32_t DIEPTXF1;
    __IO uint32_t DIEPTXF2;
    __IO uint32_t DIEPTXF3;
    __IO uint32_t DIEPTXF4;
    __IO uint32_t DIEPTXF5;
    __IO uint32_t DIEPTXF6;
    __IO uint32_t DIEPTXF7;
    __IO uint32_t DIEPTXF8;
    __IO uint32_t DIEPTXF9;
    __IO uint32_t DIEPTXF10;
    __IO uint32_t DIEPTXF11;
    __IO uint32_t DIEPTXF12;
    __IO uint32_t DIEPTXF13;
    __IO uint32_t DIEPTXF14;
    __IO uint32_t DIEPTXF15;
    uint8_t RESERVED4[704];
    __IO uint32_t HCFG;
    __IO uint32_t HFIR;
    __I  uint32_t HFNUM;
    uint8_t RESERVED5[4];
    __I  uint32_t HPTXSTS;
    __I  uint32_t HAINT;
    __IO uint32_t HAINTMSK;
    uint8_t RESERVED6[36];
    __IO uint32_t HPRT;
    uint8_t RESERVED7[188];
    __IO uint32_t HCCHAR0;
    uint8_t RESERVED8[4];
    __IO uint32_t HCINT0;
    __IO uint32_t HCINTMSK0;
    __IO uint32_t HCTSIZ0;
    __IO uint32_t HCDMA0;
    uint8_t RESERVED9[8];
    __IO uint32_t HCCHAR1;
    uint8_t RESERVED10[4];
    __IO uint32_t HCINT1;
    __IO uint32_t HCINTMSK1;
    __IO uint32_t HCTSIZ1;
    __IO uint32_t HCDMA1;
    uint8_t RESERVED11[8];
    __IO uint32_t HCCHAR2;
    uint8_t RESERVED12[4];
    __IO uint32_t HCINT2;
    __IO uint32_t HCINTMSK2;
    __IO uint32_t HCTSIZ2;
    __IO uint32_t HCDMA2;
    uint8_t RESERVED13[8];
    __IO uint32_t HCCHAR3;
    uint8_t RESERVED14[4];
    __IO uint32_t HCINT3;
    __IO uint32_t HCINTMSK3;
    __IO uint32_t HCTSIZ3;
    __IO uint32_t HCDMA3;
    uint8_t RESERVED15[8];
    __IO uint32_t HCCHAR4;
    uint8_t RESERVED16[4];
    __IO uint32_t HCINT4;
    __IO uint32_t HCINTMSK4;
    __IO uint32_t HCTSIZ4;
    __IO uint32_t HCDMA4;
    uint8_t RESERVED17[8];
    __IO uint32_t HCCHAR5;
    uint8_t RESERVED18[4];
    __IO uint32_t HCINT5;
    __IO uint32_t HCINTMSK5;
    __IO uint32_t HCTSIZ5;
    __IO uint32_t HCDMA5;
    uint8_t RESERVED19[8];
    __IO uint32_t HCCHAR6;
    uint8_t RESERVED20[4];
    __IO uint32_t HCINT6;
    __IO uint32_t HCINTMSK6;
    __IO uint32_t HCTSIZ6;
    __IO uint32_t HCDMA6;
    uint8_t RESERVED21[8];
    __IO uint32_t HCCHAR7;
    uint8_t RESERVED22[4];
    __IO uint32_t HCINT7;
    __IO uint32_t HCINTMSK7;
    __IO uint32_t HCTSIZ7;
    __IO uint32_t HCDMA7;
    uint8_t RESERVED23[8];
    __IO uint32_t HCCHAR8;
    uint8_t RESERVED24[4];
    __IO uint32_t HCINT8;
    __IO uint32_t HCINTMSK8;
    __IO uint32_t HCTSIZ8;
    __IO uint32_t HCDMA8;
    uint8_t RESERVED25[8];
    __IO uint32_t HCCHAR9;
    uint8_t RESERVED26[4];
    __IO uint32_t HCINT9;
    __IO uint32_t HCINTMSK9;
    __IO uint32_t HCTSIZ9;
    __IO uint32_t HCDMA9;
    uint8_t RESERVED27[8];
    __IO uint32_t HCCHAR10;
    uint8_t RESERVED28[4];
    __IO uint32_t HCINT10;
    __IO uint32_t HCINTMSK10;
    __IO uint32_t HCTSIZ10;
    __IO uint32_t HCDMA10;
    uint8_t RESERVED29[8];
    __IO uint32_t HCCHAR11;
    uint8_t RESERVED30[4];
    __IO uint32_t HCINT11;
    __IO uint32_t HCINTMSK11;
    __IO uint32_t HCTSIZ11;
    __IO uint32_t HCDMA11;
    uint8_t RESERVED31[8];
    __IO uint32_t HCCHAR12;
    uint8_t RESERVED32[4];
    __IO uint32_t HCINT12;
    __IO uint32_t HCINTMSK12;
    __IO uint32_t HCTSIZ12;
    __IO uint32_t HCDMA12;
    uint8_t RESERVED33[8];
    __IO uint32_t HCCHAR13;
    uint8_t RESERVED34[4];
    __IO uint32_t HCINT13;
    __IO uint32_t HCINTMSK13;
    __IO uint32_t HCTSIZ13;
    __IO uint32_t HCDMA13;
    uint8_t RESERVED35[8];
    __IO uint32_t HCCHAR14;
    uint8_t RESERVED36[4];
    __IO uint32_t HCINT14;
    __IO uint32_t HCINTMSK14;
    __IO uint32_t HCTSIZ14;
    __IO uint32_t HCDMA14;
    uint8_t RESERVED37[8];
    __IO uint32_t HCCHAR15;
    uint8_t RESERVED38[4];
    __IO uint32_t HCINT15;
    __IO uint32_t HCINTMSK15;
    __IO uint32_t HCTSIZ15;
    __IO uint32_t HCDMA15;
    uint8_t RESERVED39[264];
    __IO uint32_t DCFG;
    __IO uint32_t DCTL;
    __I  uint32_t DSTS;
    uint8_t RESERVED40[4];
    __IO uint32_t DIEPMSK;
    __IO uint32_t DOEPMSK;
    __IO uint32_t DAINT;
    __IO uint32_t DAINTMSK;
    uint8_t RESERVED41[20];
    __IO uint32_t DIEPEMPMSK;
    uint8_t RESERVED42[200];
    __IO uint32_t DIEPCTL0;
    uint8_t RESERVED43[4];
    __IO uint32_t DIEPINT0;
    uint8_t RESERVED44[4];
    __IO uint32_t DIEPTSIZ0;
    __IO uint32_t DIEPDMA0;
    __I  uint32_t DTXFSTS0;
    uint8_t RESERVED45[4];
    __IO uint32_t DIEPCTL1;
    uint8_t RESERVED46[4];
    __IO uint32_t DIEPINT1;
    uint8_t RESERVED47[4];
    __IO uint32_t DIEPTSIZ1;
    __IO uint32_t DIEPDMA1;
    __I  uint32_t DTXFSTS1;
    uint8_t RESERVED48[4];
    __IO uint32_t DIEPCTL2;
    uint8_t RESERVED49[4];
    __IO uint32_t DIEPINT2;
    uint8_t RESERVED50[4];
    __IO uint32_t DIEPTSIZ2;
    __IO uint32_t DIEPDMA2;
    __I  uint32_t DTXFSTS2;
    uint8_t RESERVED51[4];
    __IO uint32_t DIEPCTL3;
    uint8_t RESERVED52[4];
    __IO uint32_t DIEPINT3;
    uint8_t RESERVED53[4];
    __IO uint32_t DIEPTSIZ3;
    __IO uint32_t DIEPDMA3;
    __I  uint32_t DTXFSTS3;
    uint8_t RESERVED54[4];
    __IO uint32_t DIEPCTL4;
    uint8_t RESERVED55[4];
    __IO uint32_t DIEPINT4;
    uint8_t RESERVED56[4];
    __IO uint32_t DIEPTSIZ4;
    __IO uint32_t DIEPDMA4;
    __I  uint32_t DTXFSTS4;
    uint8_t RESERVED57[4];
    __IO uint32_t DIEPCTL5;
    uint8_t RESERVED58[4];
    __IO uint32_t DIEPINT5;
    uint8_t RESERVED59[4];
    __IO uint32_t DIEPTSIZ5;
    __IO uint32_t DIEPDMA5;
    __I  uint32_t DTXFSTS5;
    uint8_t RESERVED60[4];
    __IO uint32_t DIEPCTL6;
    uint8_t RESERVED61[4];
    __IO uint32_t DIEPINT6;
    uint8_t RESERVED62[4];
    __IO uint32_t DIEPTSIZ6;
    __IO uint32_t DIEPDMA6;
    __I  uint32_t DTXFSTS6;
    uint8_t RESERVED63[4];
    __IO uint32_t DIEPCTL7;
    uint8_t RESERVED64[4];
    __IO uint32_t DIEPINT7;
    uint8_t RESERVED65[4];
    __IO uint32_t DIEPTSIZ7;
    __IO uint32_t DIEPDMA7;
    __I  uint32_t DTXFSTS7;
    uint8_t RESERVED66[4];
    __IO uint32_t DIEPCTL8;
    uint8_t RESERVED67[4];
    __IO uint32_t DIEPINT8;
    uint8_t RESERVED68[4];
    __IO uint32_t DIEPTSIZ8;
    __IO uint32_t DIEPDMA8;
    __I  uint32_t DTXFSTS8;
    uint8_t RESERVED69[4];
    __IO uint32_t DIEPCTL9;
    uint8_t RESERVED70[4];
    __IO uint32_t DIEPINT9;
    uint8_t RESERVED71[4];
    __IO uint32_t DIEPTSIZ9;
    __IO uint32_t DIEPDMA9;
    __I  uint32_t DTXFSTS9;
    uint8_t RESERVED72[4];
    __IO uint32_t DIEPCTL10;
    uint8_t RESERVED73[4];
    __IO uint32_t DIEPINT10;
    uint8_t RESERVED74[4];
    __IO uint32_t DIEPTSIZ10;
    __IO uint32_t DIEPDMA10;
    __I  uint32_t DTXFSTS10;
    uint8_t RESERVED75[4];
    __IO uint32_t DIEPCTL11;
    uint8_t RESERVED76[4];
    __IO uint32_t DIEPINT11;
    uint8_t RESERVED77[4];
    __IO uint32_t DIEPTSIZ11;
    __IO uint32_t DIEPDMA11;
    __I  uint32_t DTXFSTS11;
    uint8_t RESERVED78[4];
    __IO uint32_t DIEPCTL12;
    uint8_t RESERVED79[4];
    __IO uint32_t DIEPINT12;
    uint8_t RESERVED80[4];
    __IO uint32_t DIEPTSIZ12;
    __IO uint32_t DIEPDMA12;
    __I  uint32_t DTXFSTS12;
    uint8_t RESERVED81[4];
    __IO uint32_t DIEPCTL13;
    uint8_t RESERVED82[4];
    __IO uint32_t DIEPINT13;
    uint8_t RESERVED83[4];
    __IO uint32_t DIEPTSIZ13;
    __IO uint32_t DIEPDMA13;
    __I  uint32_t DTXFSTS13;
    uint8_t RESERVED84[4];
    __IO uint32_t DIEPCTL14;
    uint8_t RESERVED85[4];
    __IO uint32_t DIEPINT14;
    uint8_t RESERVED86[4];
    __IO uint32_t DIEPTSIZ14;
    __IO uint32_t DIEPDMA14;
    __I  uint32_t DTXFSTS14;
    uint8_t RESERVED87[4];
    __IO uint32_t DIEPCTL15;
    uint8_t RESERVED88[4];
    __IO uint32_t DIEPINT15;
    uint8_t RESERVED89[4];
    __IO uint32_t DIEPTSIZ15;
    __IO uint32_t DIEPDMA15;
    __I  uint32_t DTXFSTS15;
    uint8_t RESERVED90[4];
    __IO uint32_t DOEPCTL0;
    uint8_t RESERVED91[4];
    __IO uint32_t DOEPINT0;
    uint8_t RESERVED92[4];
    __IO uint32_t DOEPTSIZ0;
    __IO uint32_t DOEPDMA0;
    uint8_t RESERVED93[8];
    __IO uint32_t DOEPCTL1;
    uint8_t RESERVED94[4];
    __IO uint32_t DOEPINT1;
    uint8_t RESERVED95[4];
    __IO uint32_t DOEPTSIZ1;
    __IO uint32_t DOEPDMA1;
    uint8_t RESERVED96[8];
    __IO uint32_t DOEPCTL2;
    uint8_t RESERVED97[4];
    __IO uint32_t DOEPINT2;
    uint8_t RESERVED98[4];
    __IO uint32_t DOEPTSIZ2;
    __IO uint32_t DOEPDMA2;
    uint8_t RESERVED99[8];
    __IO uint32_t DOEPCTL3;
    uint8_t RESERVED100[4];
    __IO uint32_t DOEPINT3;
    uint8_t RESERVED101[4];
    __IO uint32_t DOEPTSIZ3;
    __IO uint32_t DOEPDMA3;
    uint8_t RESERVED102[8];
    __IO uint32_t DOEPCTL4;
    uint8_t RESERVED103[4];
    __IO uint32_t DOEPINT4;
    uint8_t RESERVED104[4];
    __IO uint32_t DOEPTSIZ4;
    __IO uint32_t DOEPDMA4;
    uint8_t RESERVED105[8];
    __IO uint32_t DOEPCTL5;
    uint8_t RESERVED106[4];
    __IO uint32_t DOEPINT5;
    uint8_t RESERVED107[4];
    __IO uint32_t DOEPTSIZ5;
    __IO uint32_t DOEPDMA5;
    uint8_t RESERVED108[8];
    __IO uint32_t DOEPCTL6;
    uint8_t RESERVED109[4];
    __IO uint32_t DOEPINT6;
    uint8_t RESERVED110[4];
    __IO uint32_t DOEPTSIZ6;
    __IO uint32_t DOEPDMA6;
    uint8_t RESERVED111[8];
    __IO uint32_t DOEPCTL7;
    uint8_t RESERVED112[4];
    __IO uint32_t DOEPINT7;
    uint8_t RESERVED113[4];
    __IO uint32_t DOEPTSIZ7;
    __IO uint32_t DOEPDMA7;
    uint8_t RESERVED114[8];
    __IO uint32_t DOEPCTL8;
    uint8_t RESERVED115[4];
    __IO uint32_t DOEPINT8;
    uint8_t RESERVED116[4];
    __IO uint32_t DOEPTSIZ8;
    __IO uint32_t DOEPDMA8;
    uint8_t RESERVED117[8];
    __IO uint32_t DOEPCTL9;
    uint8_t RESERVED118[4];
    __IO uint32_t DOEPINT9;
    uint8_t RESERVED119[4];
    __IO uint32_t DOEPTSIZ9;
    __IO uint32_t DOEPDMA9;
    uint8_t RESERVED120[8];
    __IO uint32_t DOEPCTL10;
    uint8_t RESERVED121[4];
    __IO uint32_t DOEPINT10;
    uint8_t RESERVED122[4];
    __IO uint32_t DOEPTSIZ10;
    __IO uint32_t DOEPDMA10;
    uint8_t RESERVED123[8];
    __IO uint32_t DOEPCTL11;
    uint8_t RESERVED124[4];
    __IO uint32_t DOEPINT11;
    uint8_t RESERVED125[4];
    __IO uint32_t DOEPTSIZ11;
    __IO uint32_t DOEPDMA11;
    uint8_t RESERVED126[8];
    __IO uint32_t DOEPCTL12;
    uint8_t RESERVED127[4];
    __IO uint32_t DOEPINT12;
    uint8_t RESERVED128[4];
    __IO uint32_t DOEPTSIZ12;
    __IO uint32_t DOEPDMA12;
    uint8_t RESERVED129[8];
    __IO uint32_t DOEPCTL13;
    uint8_t RESERVED130[4];
    __IO uint32_t DOEPINT13;
    uint8_t RESERVED131[4];
    __IO uint32_t DOEPTSIZ13;
    __IO uint32_t DOEPDMA13;
    uint8_t RESERVED132[8];
    __IO uint32_t DOEPCTL14;
    uint8_t RESERVED133[4];
    __IO uint32_t DOEPINT14;
    uint8_t RESERVED134[4];
    __IO uint32_t DOEPTSIZ14;
    __IO uint32_t DOEPDMA14;
    uint8_t RESERVED135[8];
    __IO uint32_t DOEPCTL15;
    uint8_t RESERVED136[4];
    __IO uint32_t DOEPINT15;
    uint8_t RESERVED137[4];
    __IO uint32_t DOEPTSIZ15;
    __IO uint32_t DOEPDMA15;
    uint8_t RESERVED138[264];
    __IO uint32_t GCCTL;
} CM_USBFS_TypeDef;

/**
 * @brief USBHS
 */
typedef struct {
    __IO uint32_t GVBUSCFG;
    uint8_t RESERVED0[4];
    __IO uint32_t GAHBCFG;
    __IO uint32_t GUSBCFG;
    __IO uint32_t GRSTCTL;
    __IO uint32_t GINTSTS;
    __IO uint32_t GINTMSK;
    __I  uint32_t GRXSTSR;
    __I  uint32_t GRXSTSP;
    __IO uint32_t GRXFSIZ;
    __IO uint32_t HNPTXFSIZ;
    __I  uint32_t HNPTXSTS;
    uint8_t RESERVED1[12];
    __IO uint32_t CID;
    uint8_t RESERVED2[20];
    __IO uint32_t GLPMCFG;
    uint8_t RESERVED3[168];
    __IO uint32_t HPTXFSIZ;
    __IO uint32_t DIEPTXF1;
    __IO uint32_t DIEPTXF2;
    __IO uint32_t DIEPTXF3;
    __IO uint32_t DIEPTXF4;
    __IO uint32_t DIEPTXF5;
    __IO uint32_t DIEPTXF6;
    __IO uint32_t DIEPTXF7;
    __IO uint32_t DIEPTXF8;
    __IO uint32_t DIEPTXF9;
    __IO uint32_t DIEPTXF10;
    __IO uint32_t DIEPTXF11;
    __IO uint32_t DIEPTXF12;
    __IO uint32_t DIEPTXF13;
    __IO uint32_t DIEPTXF14;
    __IO uint32_t DIEPTXF15;
    uint8_t RESERVED4[704];
    __IO uint32_t HCFG;
    __IO uint32_t HFIR;
    __I  uint32_t HFNUM;
    uint8_t RESERVED5[4];
    __I  uint32_t HPTXSTS;
    __I  uint32_t HAINT;
    __IO uint32_t HAINTMSK;
    uint8_t RESERVED6[36];
    __IO uint32_t HPRT;
    uint8_t RESERVED7[188];
    __IO uint32_t HCCHAR0;
    __IO uint32_t HCSPLT0;
    __IO uint32_t HCINT0;
    __IO uint32_t HCINTMSK0;
    __IO uint32_t HCTSIZ0;
    __IO uint32_t HCDMA0;
    uint8_t RESERVED8[8];
    __IO uint32_t HCCHAR1;
    __IO uint32_t HCSPLT1;
    __IO uint32_t HCINT1;
    __IO uint32_t HCINTMSK1;
    __IO uint32_t HCTSIZ1;
    __IO uint32_t HCDMA1;
    uint8_t RESERVED9[8];
    __IO uint32_t HCCHAR2;
    __IO uint32_t HCSPLT2;
    __IO uint32_t HCINT2;
    __IO uint32_t HCINTMSK2;
    __IO uint32_t HCTSIZ2;
    __IO uint32_t HCDMA2;
    uint8_t RESERVED10[8];
    __IO uint32_t HCCHAR3;
    __IO uint32_t HCSPLT3;
    __IO uint32_t HCINT3;
    __IO uint32_t HCINTMSK3;
    __IO uint32_t HCTSIZ3;
    __IO uint32_t HCDMA3;
    uint8_t RESERVED11[8];
    __IO uint32_t HCCHAR4;
    __IO uint32_t HCSPLT4;
    __IO uint32_t HCINT4;
    __IO uint32_t HCINTMSK4;
    __IO uint32_t HCTSIZ4;
    __IO uint32_t HCDMA4;
    uint8_t RESERVED12[8];
    __IO uint32_t HCCHAR5;
    __IO uint32_t HCSPLT5;
    __IO uint32_t HCINT5;
    __IO uint32_t HCINTMSK5;
    __IO uint32_t HCTSIZ5;
    __IO uint32_t HCDMA5;
    uint8_t RESERVED13[8];
    __IO uint32_t HCCHAR6;
    __IO uint32_t HCSPLT6;
    __IO uint32_t HCINT6;
    __IO uint32_t HCINTMSK6;
    __IO uint32_t HCTSIZ6;
    __IO uint32_t HCDMA6;
    uint8_t RESERVED14[8];
    __IO uint32_t HCCHAR7;
    __IO uint32_t HCSPLT7;
    __IO uint32_t HCINT7;
    __IO uint32_t HCINTMSK7;
    __IO uint32_t HCTSIZ7;
    __IO uint32_t HCDMA7;
    uint8_t RESERVED15[8];
    __IO uint32_t HCCHAR8;
    __IO uint32_t HCSPLT8;
    __IO uint32_t HCINT8;
    __IO uint32_t HCINTMSK8;
    __IO uint32_t HCTSIZ8;
    __IO uint32_t HCDMA8;
    uint8_t RESERVED16[8];
    __IO uint32_t HCCHAR9;
    __IO uint32_t HCSPLT9;
    __IO uint32_t HCINT9;
    __IO uint32_t HCINTMSK9;
    __IO uint32_t HCTSIZ9;
    __IO uint32_t HCDMA9;
    uint8_t RESERVED17[8];
    __IO uint32_t HCCHAR10;
    __IO uint32_t HCSPLT10;
    __IO uint32_t HCINT10;
    __IO uint32_t HCINTMSK10;
    __IO uint32_t HCTSIZ10;
    __IO uint32_t HCDMA10;
    uint8_t RESERVED18[8];
    __IO uint32_t HCCHAR11;
    __IO uint32_t HCSPLT11;
    __IO uint32_t HCINT11;
    __IO uint32_t HCINTMSK11;
    __IO uint32_t HCTSIZ11;
    __IO uint32_t HCDMA11;
    uint8_t RESERVED19[8];
    __IO uint32_t HCCHAR12;
    __IO uint32_t HCSPLT12;
    __IO uint32_t HCINT12;
    __IO uint32_t HCINTMSK12;
    __IO uint32_t HCTSIZ12;
    __IO uint32_t HCDMA12;
    uint8_t RESERVED20[8];
    __IO uint32_t HCCHAR13;
    __IO uint32_t HCSPLT13;
    __IO uint32_t HCINT13;
    __IO uint32_t HCINTMSK13;
    __IO uint32_t HCTSIZ13;
    __IO uint32_t HCDMA13;
    uint8_t RESERVED21[8];
    __IO uint32_t HCCHAR14;
    __IO uint32_t HCSPLT14;
    __IO uint32_t HCINT14;
    __IO uint32_t HCINTMSK14;
    __IO uint32_t HCTSIZ14;
    __IO uint32_t HCDMA14;
    uint8_t RESERVED22[8];
    __IO uint32_t HCCHAR15;
    __IO uint32_t HCSPLT15;
    __IO uint32_t HCINT15;
    __IO uint32_t HCINTMSK15;
    __IO uint32_t HCTSIZ15;
    __IO uint32_t HCDMA15;
    uint8_t RESERVED23[264];
    __IO uint32_t DCFG;
    __IO uint32_t DCTL;
    __I  uint32_t DSTS;
    uint8_t RESERVED24[4];
    __IO uint32_t DIEPMSK;
    __IO uint32_t DOEPMSK;
    __IO uint32_t DAINT;
    __IO uint32_t DAINTMSK;
    uint8_t RESERVED25[16];
    __IO uint32_t DTHRCTL;
    __IO uint32_t DIEPEMPMSK;
    __IO uint32_t DEACHINT;
    __IO uint32_t DEACHINTMSK;
    uint8_t RESERVED26[4];
    __IO uint32_t DIEPEACHMSK1;
    uint8_t RESERVED27[60];
    __IO uint32_t DOEPEACHMSK1;
    uint8_t RESERVED28[120];
    __IO uint32_t DIEPCTL0;
    uint8_t RESERVED29[4];
    __IO uint32_t DIEPINT0;
    uint8_t RESERVED30[4];
    __IO uint32_t DIEPTSIZ0;
    __IO uint32_t DIEPDMA0;
    __I  uint32_t DTXFSTS0;
    uint8_t RESERVED31[4];
    __IO uint32_t DIEPCTL1;
    uint8_t RESERVED32[4];
    __IO uint32_t DIEPINT1;
    uint8_t RESERVED33[4];
    __IO uint32_t DIEPTSIZ1;
    __IO uint32_t DIEPDMA1;
    __I  uint32_t DTXFSTS1;
    uint8_t RESERVED34[4];
    __IO uint32_t DIEPCTL2;
    uint8_t RESERVED35[4];
    __IO uint32_t DIEPINT2;
    uint8_t RESERVED36[4];
    __IO uint32_t DIEPTSIZ2;
    __IO uint32_t DIEPDMA2;
    __I  uint32_t DTXFSTS2;
    uint8_t RESERVED37[4];
    __IO uint32_t DIEPCTL3;
    uint8_t RESERVED38[4];
    __IO uint32_t DIEPINT3;
    uint8_t RESERVED39[4];
    __IO uint32_t DIEPTSIZ3;
    __IO uint32_t DIEPDMA3;
    __I  uint32_t DTXFSTS3;
    uint8_t RESERVED40[4];
    __IO uint32_t DIEPCTL4;
    uint8_t RESERVED41[4];
    __IO uint32_t DIEPINT4;
    uint8_t RESERVED42[4];
    __IO uint32_t DIEPTSIZ4;
    __IO uint32_t DIEPDMA4;
    __I  uint32_t DTXFSTS4;
    uint8_t RESERVED43[4];
    __IO uint32_t DIEPCTL5;
    uint8_t RESERVED44[4];
    __IO uint32_t DIEPINT5;
    uint8_t RESERVED45[4];
    __IO uint32_t DIEPTSIZ5;
    __IO uint32_t DIEPDMA5;
    __I  uint32_t DTXFSTS5;
    uint8_t RESERVED46[4];
    __IO uint32_t DIEPCTL6;
    uint8_t RESERVED47[4];
    __IO uint32_t DIEPINT6;
    uint8_t RESERVED48[4];
    __IO uint32_t DIEPTSIZ6;
    __IO uint32_t DIEPDMA6;
    __I  uint32_t DTXFSTS6;
    uint8_t RESERVED49[4];
    __IO uint32_t DIEPCTL7;
    uint8_t RESERVED50[4];
    __IO uint32_t DIEPINT7;
    uint8_t RESERVED51[4];
    __IO uint32_t DIEPTSIZ7;
    __IO uint32_t DIEPDMA7;
    __I  uint32_t DTXFSTS7;
    uint8_t RESERVED52[4];
    __IO uint32_t DIEPCTL8;
    uint8_t RESERVED53[4];
    __IO uint32_t DIEPINT8;
    uint8_t RESERVED54[4];
    __IO uint32_t DIEPTSIZ8;
    __IO uint32_t DIEPDMA8;
    __I  uint32_t DTXFSTS8;
    uint8_t RESERVED55[4];
    __IO uint32_t DIEPCTL9;
    uint8_t RESERVED56[4];
    __IO uint32_t DIEPINT9;
    uint8_t RESERVED57[4];
    __IO uint32_t DIEPTSIZ9;
    __IO uint32_t DIEPDMA9;
    __I  uint32_t DTXFSTS9;
    uint8_t RESERVED58[4];
    __IO uint32_t DIEPCTL10;
    uint8_t RESERVED59[4];
    __IO uint32_t DIEPINT10;
    uint8_t RESERVED60[4];
    __IO uint32_t DIEPTSIZ10;
    __IO uint32_t DIEPDMA10;
    __I  uint32_t DTXFSTS10;
    uint8_t RESERVED61[4];
    __IO uint32_t DIEPCTL11;
    uint8_t RESERVED62[4];
    __IO uint32_t DIEPINT11;
    uint8_t RESERVED63[4];
    __IO uint32_t DIEPTSIZ11;
    __IO uint32_t DIEPDMA11;
    __I  uint32_t DTXFSTS11;
    uint8_t RESERVED64[4];
    __IO uint32_t DIEPCTL12;
    uint8_t RESERVED65[4];
    __IO uint32_t DIEPINT12;
    uint8_t RESERVED66[4];
    __IO uint32_t DIEPTSIZ12;
    __IO uint32_t DIEPDMA12;
    __I  uint32_t DTXFSTS12;
    uint8_t RESERVED67[4];
    __IO uint32_t DIEPCTL13;
    uint8_t RESERVED68[4];
    __IO uint32_t DIEPINT13;
    uint8_t RESERVED69[4];
    __IO uint32_t DIEPTSIZ13;
    __IO uint32_t DIEPDMA13;
    __I  uint32_t DTXFSTS13;
    uint8_t RESERVED70[4];
    __IO uint32_t DIEPCTL14;
    uint8_t RESERVED71[4];
    __IO uint32_t DIEPINT14;
    uint8_t RESERVED72[4];
    __IO uint32_t DIEPTSIZ14;
    __IO uint32_t DIEPDMA14;
    __I  uint32_t DTXFSTS14;
    uint8_t RESERVED73[4];
    __IO uint32_t DIEPCTL15;
    uint8_t RESERVED74[4];
    __IO uint32_t DIEPINT15;
    uint8_t RESERVED75[4];
    __IO uint32_t DIEPTSIZ15;
    __IO uint32_t DIEPDMA15;
    __I  uint32_t DTXFSTS15;
    uint8_t RESERVED76[4];
    __IO uint32_t DOEPCTL0;
    uint8_t RESERVED77[4];
    __IO uint32_t DOEPINT0;
    uint8_t RESERVED78[4];
    __IO uint32_t DOEPTSIZ0;
    __IO uint32_t DOEPDMA0;
    uint8_t RESERVED79[8];
    __IO uint32_t DOEPCTL1;
    uint8_t RESERVED80[4];
    __IO uint32_t DOEPINT1;
    uint8_t RESERVED81[4];
    __IO uint32_t DOEPTSIZ1;
    __IO uint32_t DOEPDMA1;
    uint8_t RESERVED82[8];
    __IO uint32_t DOEPCTL2;
    uint8_t RESERVED83[4];
    __IO uint32_t DOEPINT2;
    uint8_t RESERVED84[4];
    __IO uint32_t DOEPTSIZ2;
    __IO uint32_t DOEPDMA2;
    uint8_t RESERVED85[8];
    __IO uint32_t DOEPCTL3;
    uint8_t RESERVED86[4];
    __IO uint32_t DOEPINT3;
    uint8_t RESERVED87[4];
    __IO uint32_t DOEPTSIZ3;
    __IO uint32_t DOEPDMA3;
    uint8_t RESERVED88[8];
    __IO uint32_t DOEPCTL4;
    uint8_t RESERVED89[4];
    __IO uint32_t DOEPINT4;
    uint8_t RESERVED90[4];
    __IO uint32_t DOEPTSIZ4;
    __IO uint32_t DOEPDMA4;
    uint8_t RESERVED91[8];
    __IO uint32_t DOEPCTL5;
    uint8_t RESERVED92[4];
    __IO uint32_t DOEPINT5;
    uint8_t RESERVED93[4];
    __IO uint32_t DOEPTSIZ5;
    __IO uint32_t DOEPDMA5;
    uint8_t RESERVED94[8];
    __IO uint32_t DOEPCTL6;
    uint8_t RESERVED95[4];
    __IO uint32_t DOEPINT6;
    uint8_t RESERVED96[4];
    __IO uint32_t DOEPTSIZ6;
    __IO uint32_t DOEPDMA6;
    uint8_t RESERVED97[8];
    __IO uint32_t DOEPCTL7;
    uint8_t RESERVED98[4];
    __IO uint32_t DOEPINT7;
    uint8_t RESERVED99[4];
    __IO uint32_t DOEPTSIZ7;
    __IO uint32_t DOEPDMA7;
    uint8_t RESERVED100[8];
    __IO uint32_t DOEPCTL8;
    uint8_t RESERVED101[4];
    __IO uint32_t DOEPINT8;
    uint8_t RESERVED102[4];
    __IO uint32_t DOEPTSIZ8;
    __IO uint32_t DOEPDMA8;
    uint8_t RESERVED103[8];
    __IO uint32_t DOEPCTL9;
    uint8_t RESERVED104[4];
    __IO uint32_t DOEPINT9;
    uint8_t RESERVED105[4];
    __IO uint32_t DOEPTSIZ9;
    __IO uint32_t DOEPDMA9;
    uint8_t RESERVED106[8];
    __IO uint32_t DOEPCTL10;
    uint8_t RESERVED107[4];
    __IO uint32_t DOEPINT10;
    uint8_t RESERVED108[4];
    __IO uint32_t DOEPTSIZ10;
    __IO uint32_t DOEPDMA10;
    uint8_t RESERVED109[8];
    __IO uint32_t DOEPCTL11;
    uint8_t RESERVED110[4];
    __IO uint32_t DOEPINT11;
    uint8_t RESERVED111[4];
    __IO uint32_t DOEPTSIZ11;
    __IO uint32_t DOEPDMA11;
    uint8_t RESERVED112[8];
    __IO uint32_t DOEPCTL12;
    uint8_t RESERVED113[4];
    __IO uint32_t DOEPINT12;
    uint8_t RESERVED114[4];
    __IO uint32_t DOEPTSIZ12;
    __IO uint32_t DOEPDMA12;
    uint8_t RESERVED115[8];
    __IO uint32_t DOEPCTL13;
    uint8_t RESERVED116[4];
    __IO uint32_t DOEPINT13;
    uint8_t RESERVED117[4];
    __IO uint32_t DOEPTSIZ13;
    __IO uint32_t DOEPDMA13;
    uint8_t RESERVED118[8];
    __IO uint32_t DOEPCTL14;
    uint8_t RESERVED119[4];
    __IO uint32_t DOEPINT14;
    uint8_t RESERVED120[4];
    __IO uint32_t DOEPTSIZ14;
    __IO uint32_t DOEPDMA14;
    uint8_t RESERVED121[8];
    __IO uint32_t DOEPCTL15;
    uint8_t RESERVED122[4];
    __IO uint32_t DOEPINT15;
    uint8_t RESERVED123[4];
    __IO uint32_t DOEPTSIZ15;
    __IO uint32_t DOEPDMA15;
    uint8_t RESERVED124[264];
    __IO uint32_t GCCTL;
} CM_USBHS_TypeDef;

/**
 * @brief WDT
 */
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t RR;
} CM_WDT_TypeDef;

/******************************************************************************/
/*                     Memory Base Address                                    */
/******************************************************************************/
#define EFM_BASE                             (0x00000000UL)   /*!< EFM base address in the alias region */
#define SRAM_BASE                            (0x1FFE0000UL)   /*!< SRAM base address in the alias region */
#define SMC_BASE                             (0x60000000UL)   /*!< SMC base address in the alias region */
#define DMC_BASE                             (0x80000000UL)   /*!< DMC base address in the alias region */
#define QSPI_BASE                            (0x98000000UL)   /*!< QSPI base address in the alias region */

/******************************************************************************/
/*           Device Specific Peripheral Base Address                          */
/******************************************************************************/
#define CM_ADC1_BASE                         (0x40040000UL)
#define CM_ADC2_BASE                         (0x40040400UL)
#define CM_ADC3_BASE                         (0x40040800UL)
#define CM_AES_BASE                          (0x40008000UL)
#define CM_AOS_BASE                          (0x40010800UL)
#define CM_CAN1_BASE                         (0x40009000UL)
#define CM_CAN2_BASE                         (0x40078000UL)
#define CM_CMP1_BASE                         (0x4004A000UL)
#define CM_CMP2_BASE                         (0x4004A010UL)
#define CM_CMP3_BASE                         (0x4004A400UL)
#define CM_CMP4_BASE                         (0x4004A410UL)
#define CM_CMU_BASE                          (0x4004C400UL)
#define CM_CRC_BASE                          (0x40008C00UL)
#define CM_CTC_BASE                          (0x40049C00UL)
#define CM_DAC1_BASE                         (0x40041000UL)
#define CM_DAC2_BASE                         (0x40041400UL)
#define CM_DBGC_BASE                         (0xE0042000UL)
#define CM_DCU1_BASE                         (0x40056000UL)
#define CM_DCU2_BASE                         (0x40056400UL)
#define CM_DCU3_BASE                         (0x40056800UL)
#define CM_DCU4_BASE                         (0x40056C00UL)
#define CM_DCU5_BASE                         (0x40057000UL)
#define CM_DCU6_BASE                         (0x40057400UL)
#define CM_DCU7_BASE                         (0x40057800UL)
#define CM_DCU8_BASE                         (0x40057C00UL)
#define CM_DMA1_BASE                         (0x40053000UL)
#define CM_DMA2_BASE                         (0x40053400UL)
#define CM_DMC_BASE                          (0x88000400UL)
#define CM_DVP_BASE                          (0x40055800UL)
#define CM_EFM_BASE                          (0x40010400UL)
#define CM_EMB0_BASE                         (0x40017C00UL)
#define CM_EMB1_BASE                         (0x40017C20UL)
#define CM_EMB2_BASE                         (0x40017C40UL)
#define CM_EMB3_BASE                         (0x40017C60UL)
#define CM_EMB4_BASE                         (0x40017C80UL)
#define CM_EMB5_BASE                         (0x40017CA0UL)
#define CM_EMB6_BASE                         (0x40017CC0UL)
#define CM_ETH_BASE                          (0x40050000UL)
#define CM_FCM_BASE                          (0x40048400UL)
#define CM_FMAC1_BASE                        (0x40058000UL)
#define CM_FMAC2_BASE                        (0x40058400UL)
#define CM_FMAC3_BASE                        (0x40058800UL)
#define CM_FMAC4_BASE                        (0x40058C00UL)
#define CM_GPIO_BASE                         (0x40053800UL)
#define CM_HASH_BASE                         (0x40008400UL)
#define CM_HRPWM_BASE                        (0x4003C000UL)
#define CM_I2C1_BASE                         (0x4004E000UL)
#define CM_I2C2_BASE                         (0x4004E400UL)
#define CM_I2C3_BASE                         (0x4004E800UL)
#define CM_I2C4_BASE                         (0x4004EC00UL)
#define CM_I2C5_BASE                         (0x4004F000UL)
#define CM_I2C6_BASE                         (0x4004F400UL)
#define CM_I2S1_BASE                         (0x4001E000UL)
#define CM_I2S2_BASE                         (0x4001E400UL)
#define CM_I2S3_BASE                         (0x40022000UL)
#define CM_I2S4_BASE                         (0x40022400UL)
#define CM_ICG_BASE                          (0x00000400UL)
#define CM_INTC_BASE                         (0x40051000UL)
#define CM_KEYSCAN_BASE                      (0x40050C00UL)
#define CM_MAU_BASE                          (0x40055000UL)
#define CM_MPU_BASE                          (0x40050000UL)
#define CM_NFC_BASE                          (0x88100000UL)
#define CM_OTS_BASE                          (0x40010600UL)
#define CM_PERIC_BASE                        (0x40055400UL)
#define CM_PWC_BASE                          (0x40048000UL)
#define CM_QSPI_BASE                         (0x9C000000UL)
#define CM_RMU_BASE                          (0x4004CC00UL)
#define CM_RTC_BASE                          (0x4004C000UL)
#define CM_SDIOC1_BASE                       (0x40070000UL)
#define CM_SDIOC2_BASE                       (0x40078400UL)
#define CM_SMC_BASE                          (0x88000000UL)
#define CM_SPI1_BASE                         (0x4001C000UL)
#define CM_SPI2_BASE                         (0x4001C400UL)
#define CM_SPI3_BASE                         (0x4001C800UL)
#define CM_SPI4_BASE                         (0x40020000UL)
#define CM_SPI5_BASE                         (0x40020400UL)
#define CM_SPI6_BASE                         (0x40020800UL)
#define CM_SRAMC_BASE                        (0x40050800UL)
#define CM_SWDT_BASE                         (0x40049400UL)
#define CM_TMR0_1_BASE                       (0x40024000UL)
#define CM_TMR0_2_BASE                       (0x40024400UL)
#define CM_TMR2_1_BASE                       (0x40024800UL)
#define CM_TMR2_2_BASE                       (0x40024C00UL)
#define CM_TMR2_3_BASE                       (0x40025000UL)
#define CM_TMR2_4_BASE                       (0x40025400UL)
#define CM_TMR4_1_BASE                       (0x40038000UL)
#define CM_TMR4_2_BASE                       (0x40038400UL)
#define CM_TMR4_3_BASE                       (0x40038800UL)
#define CM_TMR6_1_BASE                       (0x40018000UL)
#define CM_TMR6_2_BASE                       (0x40018400UL)
#define CM_TMR6_3_BASE                       (0x40018800UL)
#define CM_TMR6_4_BASE                       (0x40018C00UL)
#define CM_TMR6_5_BASE                       (0x40019000UL)
#define CM_TMR6_6_BASE                       (0x40019400UL)
#define CM_TMR6_7_BASE                       (0x40019800UL)
#define CM_TMR6_8_BASE                       (0x40019C00UL)
#define CM_TMR6CR_BASE                       (0x40018000UL)
#define CM_TMRA_1_BASE                       (0x4003A000UL)
#define CM_TMRA_10_BASE                      (0x40027400UL)
#define CM_TMRA_11_BASE                      (0x40027800UL)
#define CM_TMRA_12_BASE                      (0x40027C00UL)
#define CM_TMRA_2_BASE                       (0x4003A400UL)
#define CM_TMRA_3_BASE                       (0x4003A800UL)
#define CM_TMRA_4_BASE                       (0x4003AC00UL)
#define CM_TMRA_5_BASE                       (0x40026000UL)
#define CM_TMRA_6_BASE                       (0x40026400UL)
#define CM_TMRA_7_BASE                       (0x40026800UL)
#define CM_TMRA_8_BASE                       (0x40026C00UL)
#define CM_TMRA_9_BASE                       (0x40027000UL)
#define CM_TRNG_BASE                         (0x40042000UL)
#define CM_USART1_BASE                       (0x4001CC00UL)
#define CM_USART10_BASE                      (0x40021C00UL)
#define CM_USART2_BASE                       (0x4001D000UL)
#define CM_USART3_BASE                       (0x4001D400UL)
#define CM_USART4_BASE                       (0x4001D800UL)
#define CM_USART5_BASE                       (0x4001DC00UL)
#define CM_USART6_BASE                       (0x40020C00UL)
#define CM_USART7_BASE                       (0x40021000UL)
#define CM_USART8_BASE                       (0x40021400UL)
#define CM_USART9_BASE                       (0x40021800UL)
#define CM_USBFS_BASE                        (0x40080000UL)
#define CM_USBHS_BASE                        (0x400C0000UL)
#define CM_WDT_BASE                          (0x40049000UL)

/******************************************************************************/
/*           Device Specific Peripheral declaration & memory map              */
/******************************************************************************/
#define CM_ADC1                              ((CM_ADC_TypeDef *)CM_ADC1_BASE)
#define CM_ADC2                              ((CM_ADC_TypeDef *)CM_ADC2_BASE)
#define CM_ADC3                              ((CM_ADC_TypeDef *)CM_ADC3_BASE)
#define CM_AES                               ((CM_AES_TypeDef *)CM_AES_BASE)
#define CM_AOS                               ((CM_AOS_TypeDef *)CM_AOS_BASE)
#define CM_CAN1                              ((CM_CAN_TypeDef *)CM_CAN1_BASE)
#define CM_CAN2                              ((CM_CAN_TypeDef *)CM_CAN2_BASE)
#define CM_CMP1                              ((CM_CMP_TypeDef *)CM_CMP1_BASE)
#define CM_CMP2                              ((CM_CMP_TypeDef *)CM_CMP2_BASE)
#define CM_CMP3                              ((CM_CMP_TypeDef *)CM_CMP3_BASE)
#define CM_CMP4                              ((CM_CMP_TypeDef *)CM_CMP4_BASE)
#define CM_CMU                               ((CM_CMU_TypeDef *)CM_CMU_BASE)
#define CM_CRC                               ((CM_CRC_TypeDef *)CM_CRC_BASE)
#define CM_CTC                               ((CM_CTC_TypeDef *)CM_CTC_BASE)
#define CM_DAC1                              ((CM_DAC_TypeDef *)CM_DAC1_BASE)
#define CM_DAC2                              ((CM_DAC_TypeDef *)CM_DAC2_BASE)
#define CM_DBGC                              ((CM_DBGC_TypeDef *)CM_DBGC_BASE)
#define CM_DCU1                              ((CM_DCU_TypeDef *)CM_DCU1_BASE)
#define CM_DCU2                              ((CM_DCU_TypeDef *)CM_DCU2_BASE)
#define CM_DCU3                              ((CM_DCU_TypeDef *)CM_DCU3_BASE)
#define CM_DCU4                              ((CM_DCU_TypeDef *)CM_DCU4_BASE)
#define CM_DCU5                              ((CM_DCU_TypeDef *)CM_DCU5_BASE)
#define CM_DCU6                              ((CM_DCU_TypeDef *)CM_DCU6_BASE)
#define CM_DCU7                              ((CM_DCU_TypeDef *)CM_DCU7_BASE)
#define CM_DCU8                              ((CM_DCU_TypeDef *)CM_DCU8_BASE)
#define CM_DMA1                              ((CM_DMA_TypeDef *)CM_DMA1_BASE)
#define CM_DMA2                              ((CM_DMA_TypeDef *)CM_DMA2_BASE)
#define CM_DMC                               ((CM_DMC_TypeDef *)CM_DMC_BASE)
#define CM_DVP                               ((CM_DVP_TypeDef *)CM_DVP_BASE)
#define CM_EFM                               ((CM_EFM_TypeDef *)CM_EFM_BASE)
#define CM_EMB0                              ((CM_EMB_TypeDef *)CM_EMB0_BASE)
#define CM_EMB1                              ((CM_EMB_TypeDef *)CM_EMB1_BASE)
#define CM_EMB2                              ((CM_EMB_TypeDef *)CM_EMB2_BASE)
#define CM_EMB3                              ((CM_EMB_TypeDef *)CM_EMB3_BASE)
#define CM_EMB4                              ((CM_EMB_TypeDef *)CM_EMB4_BASE)
#define CM_EMB5                              ((CM_EMB_TypeDef *)CM_EMB5_BASE)
#define CM_EMB6                              ((CM_EMB_TypeDef *)CM_EMB6_BASE)
#define CM_ETH                               ((CM_ETH_TypeDef *)CM_ETH_BASE)
#define CM_FCM                               ((CM_FCM_TypeDef *)CM_FCM_BASE)
#define CM_FMAC1                             ((CM_FMAC_TypeDef *)CM_FMAC1_BASE)
#define CM_FMAC2                             ((CM_FMAC_TypeDef *)CM_FMAC2_BASE)
#define CM_FMAC3                             ((CM_FMAC_TypeDef *)CM_FMAC3_BASE)
#define CM_FMAC4                             ((CM_FMAC_TypeDef *)CM_FMAC4_BASE)
#define CM_GPIO                              ((CM_GPIO_TypeDef *)CM_GPIO_BASE)
#define CM_HASH                              ((CM_HASH_TypeDef *)CM_HASH_BASE)
#define CM_HRPWM                             ((CM_HRPWM_TypeDef *)CM_HRPWM_BASE)
#define CM_I2C1                              ((CM_I2C_TypeDef *)CM_I2C1_BASE)
#define CM_I2C2                              ((CM_I2C_TypeDef *)CM_I2C2_BASE)
#define CM_I2C3                              ((CM_I2C_TypeDef *)CM_I2C3_BASE)
#define CM_I2C4                              ((CM_I2C_TypeDef *)CM_I2C4_BASE)
#define CM_I2C5                              ((CM_I2C_TypeDef *)CM_I2C5_BASE)
#define CM_I2C6                              ((CM_I2C_TypeDef *)CM_I2C6_BASE)
#define CM_I2S1                              ((CM_I2S_TypeDef *)CM_I2S1_BASE)
#define CM_I2S2                              ((CM_I2S_TypeDef *)CM_I2S2_BASE)
#define CM_I2S3                              ((CM_I2S_TypeDef *)CM_I2S3_BASE)
#define CM_I2S4                              ((CM_I2S_TypeDef *)CM_I2S4_BASE)
#define CM_ICG                               ((CM_ICG_TypeDef *)CM_ICG_BASE)
#define CM_INTC                              ((CM_INTC_TypeDef *)CM_INTC_BASE)
#define CM_KEYSCAN                           ((CM_KEYSCAN_TypeDef *)CM_KEYSCAN_BASE)
#define CM_MAU                               ((CM_MAU_TypeDef *)CM_MAU_BASE)
#define CM_MPU                               ((CM_MPU_TypeDef *)CM_MPU_BASE)
#define CM_NFC                               ((CM_NFC_TypeDef *)CM_NFC_BASE)
#define CM_OTS                               ((CM_OTS_TypeDef *)CM_OTS_BASE)
#define CM_PERIC                             ((CM_PERIC_TypeDef *)CM_PERIC_BASE)
#define CM_PWC                               ((CM_PWC_TypeDef *)CM_PWC_BASE)
#define CM_QSPI                              ((CM_QSPI_TypeDef *)CM_QSPI_BASE)
#define CM_RMU                               ((CM_RMU_TypeDef *)CM_RMU_BASE)
#define CM_RTC                               ((CM_RTC_TypeDef *)CM_RTC_BASE)
#define CM_SDIOC1                            ((CM_SDIOC_TypeDef *)CM_SDIOC1_BASE)
#define CM_SDIOC2                            ((CM_SDIOC_TypeDef *)CM_SDIOC2_BASE)
#define CM_SMC                               ((CM_SMC_TypeDef *)CM_SMC_BASE)
#define CM_SPI1                              ((CM_SPI_TypeDef *)CM_SPI1_BASE)
#define CM_SPI2                              ((CM_SPI_TypeDef *)CM_SPI2_BASE)
#define CM_SPI3                              ((CM_SPI_TypeDef *)CM_SPI3_BASE)
#define CM_SPI4                              ((CM_SPI_TypeDef *)CM_SPI4_BASE)
#define CM_SPI5                              ((CM_SPI_TypeDef *)CM_SPI5_BASE)
#define CM_SPI6                              ((CM_SPI_TypeDef *)CM_SPI6_BASE)
#define CM_SRAMC                             ((CM_SRAMC_TypeDef *)CM_SRAMC_BASE)
#define CM_SWDT                              ((CM_SWDT_TypeDef *)CM_SWDT_BASE)
#define CM_TMR0_1                            ((CM_TMR0_TypeDef *)CM_TMR0_1_BASE)
#define CM_TMR0_2                            ((CM_TMR0_TypeDef *)CM_TMR0_2_BASE)
#define CM_TMR2_1                            ((CM_TMR2_TypeDef *)CM_TMR2_1_BASE)
#define CM_TMR2_2                            ((CM_TMR2_TypeDef *)CM_TMR2_2_BASE)
#define CM_TMR2_3                            ((CM_TMR2_TypeDef *)CM_TMR2_3_BASE)
#define CM_TMR2_4                            ((CM_TMR2_TypeDef *)CM_TMR2_4_BASE)
#define CM_TMR4_1                            ((CM_TMR4_TypeDef *)CM_TMR4_1_BASE)
#define CM_TMR4_2                            ((CM_TMR4_TypeDef *)CM_TMR4_2_BASE)
#define CM_TMR4_3                            ((CM_TMR4_TypeDef *)CM_TMR4_3_BASE)
#define CM_TMR6_1                            ((CM_TMR6_TypeDef *)CM_TMR6_1_BASE)
#define CM_TMR6_2                            ((CM_TMR6_TypeDef *)CM_TMR6_2_BASE)
#define CM_TMR6_3                            ((CM_TMR6_TypeDef *)CM_TMR6_3_BASE)
#define CM_TMR6_4                            ((CM_TMR6_TypeDef *)CM_TMR6_4_BASE)
#define CM_TMR6_5                            ((CM_TMR6_TypeDef *)CM_TMR6_5_BASE)
#define CM_TMR6_6                            ((CM_TMR6_TypeDef *)CM_TMR6_6_BASE)
#define CM_TMR6_7                            ((CM_TMR6_TypeDef *)CM_TMR6_7_BASE)
#define CM_TMR6_8                            ((CM_TMR6_TypeDef *)CM_TMR6_8_BASE)
#define CM_TMR6CR                            ((CM_TMR6CR_TypeDef *)CM_TMR6CR_BASE)
#define CM_TMRA_1                            ((CM_TMRA_TypeDef *)CM_TMRA_1_BASE)
#define CM_TMRA_10                           ((CM_TMRA_TypeDef *)CM_TMRA_10_BASE)
#define CM_TMRA_11                           ((CM_TMRA_TypeDef *)CM_TMRA_11_BASE)
#define CM_TMRA_12                           ((CM_TMRA_TypeDef *)CM_TMRA_12_BASE)
#define CM_TMRA_2                            ((CM_TMRA_TypeDef *)CM_TMRA_2_BASE)
#define CM_TMRA_3                            ((CM_TMRA_TypeDef *)CM_TMRA_3_BASE)
#define CM_TMRA_4                            ((CM_TMRA_TypeDef *)CM_TMRA_4_BASE)
#define CM_TMRA_5                            ((CM_TMRA_TypeDef *)CM_TMRA_5_BASE)
#define CM_TMRA_6                            ((CM_TMRA_TypeDef *)CM_TMRA_6_BASE)
#define CM_TMRA_7                            ((CM_TMRA_TypeDef *)CM_TMRA_7_BASE)
#define CM_TMRA_8                            ((CM_TMRA_TypeDef *)CM_TMRA_8_BASE)
#define CM_TMRA_9                            ((CM_TMRA_TypeDef *)CM_TMRA_9_BASE)
#define CM_TRNG                              ((CM_TRNG_TypeDef *)CM_TRNG_BASE)
#define CM_USART1                            ((CM_USART_TypeDef *)CM_USART1_BASE)
#define CM_USART10                           ((CM_USART_TypeDef *)CM_USART10_BASE)
#define CM_USART2                            ((CM_USART_TypeDef *)CM_USART2_BASE)
#define CM_USART3                            ((CM_USART_TypeDef *)CM_USART3_BASE)
#define CM_USART4                            ((CM_USART_TypeDef *)CM_USART4_BASE)
#define CM_USART5                            ((CM_USART_TypeDef *)CM_USART5_BASE)
#define CM_USART6                            ((CM_USART_TypeDef *)CM_USART6_BASE)
#define CM_USART7                            ((CM_USART_TypeDef *)CM_USART7_BASE)
#define CM_USART8                            ((CM_USART_TypeDef *)CM_USART8_BASE)
#define CM_USART9                            ((CM_USART_TypeDef *)CM_USART9_BASE)
#define CM_USBFS                             ((CM_USBFS_TypeDef *)CM_USBFS_BASE)
#define CM_USBHS                             ((CM_USBHS_TypeDef *)CM_USBHS_BASE)
#define CM_WDT                               ((CM_WDT_TypeDef *)CM_WDT_BASE)

/******************************************************************************/
/*                   Peripheral Registers Bits Definition                     */
/******************************************************************************/

/*******************************************************************************
                Bit definition for Peripheral ADC
*******************************************************************************/
/*  Bit definition for ADC_STR register  */
#define ADC_STR_STRT                                   (0x01U)

/*  Bit definition for ADC_CR0 register  */
#define ADC_CR0_MS_POS                                 (0U)
#define ADC_CR0_MS                                     (0x0003U)
#define ADC_CR0_MS_0                                   (0x0001U)
#define ADC_CR0_MS_1                                   (0x0002U)
#define ADC_CR0_ACCSEL_POS                             (4U)
#define ADC_CR0_ACCSEL                                 (0x0030U)
#define ADC_CR0_ACCSEL_0                               (0x0010U)
#define ADC_CR0_ACCSEL_1                               (0x0020U)
#define ADC_CR0_CLREN_POS                              (6U)
#define ADC_CR0_CLREN                                  (0x0040U)
#define ADC_CR0_DFMT_POS                               (7U)
#define ADC_CR0_DFMT                                   (0x0080U)
#define ADC_CR0_AVCNT_POS                              (8U)
#define ADC_CR0_AVCNT                                  (0x0700U)

/*  Bit definition for ADC_CR1 register  */
#define ADC_CR1_RSCHSEL_POS                            (2U)
#define ADC_CR1_RSCHSEL                                (0x0004U)

/*  Bit definition for ADC_TRGSR register  */
#define ADC_TRGSR_TRGSELA_POS                          (0U)
#define ADC_TRGSR_TRGSELA                              (0x0003U)
#define ADC_TRGSR_TRGSELA_0                            (0x0001U)
#define ADC_TRGSR_TRGSELA_1                            (0x0002U)
#define ADC_TRGSR_TRGENA_POS                           (7U)
#define ADC_TRGSR_TRGENA                               (0x0080U)
#define ADC_TRGSR_TRGSELB_POS                          (8U)
#define ADC_TRGSR_TRGSELB                              (0x0300U)
#define ADC_TRGSR_TRGSELB_0                            (0x0100U)
#define ADC_TRGSR_TRGSELB_1                            (0x0200U)
#define ADC_TRGSR_TRGENB_POS                           (15U)
#define ADC_TRGSR_TRGENB                               (0x8000U)

/*  Bit definition for ADC_CHSELRA register  */
#define ADC_CHSELRA_CHSELA                             (0x000FFFFFUL)

/*  Bit definition for ADC_CHSELRB register  */
#define ADC_CHSELRB_CHSELB                             (0x000FFFFFUL)

/*  Bit definition for ADC_AVCHSELR register  */
#define ADC_AVCHSELR_AVCHSEL                           (0x000FFFFFUL)

/*  Bit definition for ADC_EXCHSELR register  */
#define ADC_EXCHSELR_EXCHSEL                           (0x01U)

/*  Bit definition for ADC_SHCR register  */
#define ADC_SHCR_SHSST_POS                             (0U)
#define ADC_SHCR_SHSST                                 (0x00FFU)
#define ADC_SHCR_SHSEL_POS                             (8U)
#define ADC_SHCR_SHSEL                                 (0x0700U)

/*  Bit definition for ADC_SSTR register  */
#define ADC_SSTR                                       (0xFFU)

/*  Bit definition for ADC_SSTRL register  */
#define ADC_SSTRL                                      (0xFFU)

/*  Bit definition for ADC_CHMUXR0 register  */
#define ADC_CHMUXR0_CH00MUX_POS                        (0U)
#define ADC_CHMUXR0_CH00MUX                            (0x000FU)
#define ADC_CHMUXR0_CH01MUX_POS                        (4U)
#define ADC_CHMUXR0_CH01MUX                            (0x00F0U)
#define ADC_CHMUXR0_CH02MUX_POS                        (8U)
#define ADC_CHMUXR0_CH02MUX                            (0x0F00U)
#define ADC_CHMUXR0_CH03MUX_POS                        (12U)
#define ADC_CHMUXR0_CH03MUX                            (0xF000U)

/*  Bit definition for ADC_CHMUXR1 register  */
#define ADC_CHMUXR1_CH04MUX_POS                        (0U)
#define ADC_CHMUXR1_CH04MUX                            (0x000FU)
#define ADC_CHMUXR1_CH05MUX_POS                        (4U)
#define ADC_CHMUXR1_CH05MUX                            (0x00F0U)
#define ADC_CHMUXR1_CH06MUX_POS                        (8U)
#define ADC_CHMUXR1_CH06MUX                            (0x0F00U)
#define ADC_CHMUXR1_CH07MUX_POS                        (12U)
#define ADC_CHMUXR1_CH07MUX                            (0xF000U)

/*  Bit definition for ADC_CHMUXR2 register  */
#define ADC_CHMUXR2_CH08MUX_POS                        (0U)
#define ADC_CHMUXR2_CH08MUX                            (0x000FU)
#define ADC_CHMUXR2_CH09MUX_POS                        (4U)
#define ADC_CHMUXR2_CH09MUX                            (0x00F0U)
#define ADC_CHMUXR2_CH10MUX_POS                        (8U)
#define ADC_CHMUXR2_CH10MUX                            (0x0F00U)
#define ADC_CHMUXR2_CH11MUX_POS                        (12U)
#define ADC_CHMUXR2_CH11MUX                            (0xF000U)

/*  Bit definition for ADC_CHMUXR3 register  */
#define ADC_CHMUXR3_CH12MUX_POS                        (0U)
#define ADC_CHMUXR3_CH12MUX                            (0x000FU)
#define ADC_CHMUXR3_CH13MUX_POS                        (4U)
#define ADC_CHMUXR3_CH13MUX                            (0x00F0U)
#define ADC_CHMUXR3_CH14MUX_POS                        (8U)
#define ADC_CHMUXR3_CH14MUX                            (0x0F00U)
#define ADC_CHMUXR3_CH15MUX_POS                        (12U)
#define ADC_CHMUXR3_CH15MUX                            (0xF000U)

/*  Bit definition for ADC_ISR register  */
#define ADC_ISR_EOCAF_POS                              (0U)
#define ADC_ISR_EOCAF                                  (0x01U)
#define ADC_ISR_EOCBF_POS                              (1U)
#define ADC_ISR_EOCBF                                  (0x02U)
#define ADC_ISR_SASTPDF_POS                            (4U)
#define ADC_ISR_SASTPDF                                (0x10U)

/*  Bit definition for ADC_ICR register  */
#define ADC_ICR_EOCAIEN_POS                            (0U)
#define ADC_ICR_EOCAIEN                                (0x01U)
#define ADC_ICR_EOCBIEN_POS                            (1U)
#define ADC_ICR_EOCBIEN                                (0x02U)

/*  Bit definition for ADC_ISCLRR register  */
#define ADC_ISCLRR_CLREOCAF_POS                        (0U)
#define ADC_ISCLRR_CLREOCAF                            (0x01U)
#define ADC_ISCLRR_CLREOCBF_POS                        (1U)
#define ADC_ISCLRR_CLREOCBF                            (0x02U)
#define ADC_ISCLRR_CLRSASTPDF_POS                      (4U)
#define ADC_ISCLRR_CLRSASTPDF                          (0x10U)

/*  Bit definition for ADC_SYNCCR register  */
#define ADC_SYNCCR_SYNCEN_POS                          (0U)
#define ADC_SYNCCR_SYNCEN                              (0x0001U)
#define ADC_SYNCCR_SYNCMD_POS                          (4U)
#define ADC_SYNCCR_SYNCMD                              (0x0070U)
#define ADC_SYNCCR_SYNCMD_0                            (0x0010U)
#define ADC_SYNCCR_SYNCMD_1                            (0x0020U)
#define ADC_SYNCCR_SYNCMD_2                            (0x0040U)
#define ADC_SYNCCR_SYNCDLY_POS                         (8U)
#define ADC_SYNCCR_SYNCDLY                             (0xFF00U)

/*  Bit definition for ADC_DR register  */
#define ADC_DR                                         (0xFFFFU)

/*  Bit definition for ADC_AWDCR register  */
#define ADC_AWDCR_AWD0EN_POS                           (0U)
#define ADC_AWDCR_AWD0EN                               (0x0001U)
#define ADC_AWDCR_AWD0IEN_POS                          (1U)
#define ADC_AWDCR_AWD0IEN                              (0x0002U)
#define ADC_AWDCR_AWD0MD_POS                           (2U)
#define ADC_AWDCR_AWD0MD                               (0x0004U)
#define ADC_AWDCR_AWD1EN_POS                           (4U)
#define ADC_AWDCR_AWD1EN                               (0x0010U)
#define ADC_AWDCR_AWD1IEN_POS                          (5U)
#define ADC_AWDCR_AWD1IEN                              (0x0020U)
#define ADC_AWDCR_AWD1MD_POS                           (6U)
#define ADC_AWDCR_AWD1MD                               (0x0040U)
#define ADC_AWDCR_AWDCM_POS                            (8U)
#define ADC_AWDCR_AWDCM                                (0x0300U)
#define ADC_AWDCR_AWDCM_0                              (0x0100U)
#define ADC_AWDCR_AWDCM_1                              (0x0200U)

/*  Bit definition for ADC_AWDSR register  */
#define ADC_AWDSR_AWD0F_POS                            (0U)
#define ADC_AWDSR_AWD0F                                (0x01U)
#define ADC_AWDSR_AWD1F_POS                            (1U)
#define ADC_AWDSR_AWD1F                                (0x02U)
#define ADC_AWDSR_AWDCMF_POS                           (4U)
#define ADC_AWDSR_AWDCMF                               (0x10U)

/*  Bit definition for ADC_AWDSCLRR register  */
#define ADC_AWDSCLRR_CLRAWD0F_POS                      (0U)
#define ADC_AWDSCLRR_CLRAWD0F                          (0x01U)
#define ADC_AWDSCLRR_CLRAWD1F_POS                      (1U)
#define ADC_AWDSCLRR_CLRAWD1F                          (0x02U)
#define ADC_AWDSCLRR_CLRAWDCMF_POS                     (4U)
#define ADC_AWDSCLRR_CLRAWDCMF                         (0x10U)

/*  Bit definition for ADC_AWD0DR0 register  */
#define ADC_AWD0DR0                                    (0xFFFFU)

/*  Bit definition for ADC_AWD0DR1 register  */
#define ADC_AWD0DR1                                    (0xFFFFU)

/*  Bit definition for ADC_AWD0CHSR register  */
#define ADC_AWD0CHSR_AWDCH                             (0x1FU)
#define ADC_AWD0CHSR_AWDCH_0                           (0x01U)
#define ADC_AWD0CHSR_AWDCH_1                           (0x02U)
#define ADC_AWD0CHSR_AWDCH_2                           (0x04U)
#define ADC_AWD0CHSR_AWDCH_3                           (0x08U)
#define ADC_AWD0CHSR_AWDCH_4                           (0x10U)

/*  Bit definition for ADC_AWD1DR0 register  */
#define ADC_AWD1DR0                                    (0xFFFFU)

/*  Bit definition for ADC_AWD1DR1 register  */
#define ADC_AWD1DR1                                    (0xFFFFU)

/*  Bit definition for ADC_AWD1CHSR register  */
#define ADC_AWD1CHSR_AWDCH                             (0x1FU)

/*  Bit definition for ADC_PGACR register  */
#define ADC_PGACR_PGACTL_POS                           (0U)
#define ADC_PGACR_PGACTL                               (0x0FU)
#define ADC_PGACR_PGAGAIN_POS                          (4U)
#define ADC_PGACR_PGAGAIN                              (0xF0U)

/*  Bit definition for ADC_PGAVSSENR register  */
#define ADC_PGAVSSENR_PGAVSSEN                         (0x07U)

/*******************************************************************************
                Bit definition for Peripheral AES
*******************************************************************************/
/*  Bit definition for AES_CR register  */
#define AES_CR_START_POS                               (0U)
#define AES_CR_START                                   (0x00000001UL)
#define AES_CR_MODE_POS                                (1U)
#define AES_CR_MODE                                    (0x00000002UL)
#define AES_CR_KEYSIZE_POS                             (3U)
#define AES_CR_KEYSIZE                                 (0x00000018UL)

/*  Bit definition for AES_DR0 register  */
#define AES_DR0                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_DR1 register  */
#define AES_DR1                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_DR2 register  */
#define AES_DR2                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_DR3 register  */
#define AES_DR3                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR0 register  */
#define AES_KR0                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR1 register  */
#define AES_KR1                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR2 register  */
#define AES_KR2                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR3 register  */
#define AES_KR3                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR4 register  */
#define AES_KR4                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR5 register  */
#define AES_KR5                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR6 register  */
#define AES_KR6                                        (0xFFFFFFFFUL)

/*  Bit definition for AES_KR7 register  */
#define AES_KR7                                        (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral AOS
*******************************************************************************/
/*  Bit definition for AOS_INTSFTTRG register  */
#define AOS_INTSFTTRG_STRG                             (0x00000001UL)

/*  Bit definition for AOS_DCU_TRGSEL register  */
#define AOS_DCU_TRGSEL_TRGSEL_POS                      (0U)
#define AOS_DCU_TRGSEL_TRGSEL                          (0x000001FFUL)
#define AOS_DCU_TRGSEL_COMEN_POS                       (30U)
#define AOS_DCU_TRGSEL_COMEN                           (0xC0000000UL)
#define AOS_DCU_TRGSEL_COMEN_0                         (0x40000000UL)
#define AOS_DCU_TRGSEL_COMEN_1                         (0x80000000UL)

/*  Bit definition for AOS_DMA1_TRGSEL register  */
#define AOS_DMA1_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_DMA1_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_DMA1_TRGSEL_COMEN_POS                      (30U)
#define AOS_DMA1_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_DMA1_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_DMA1_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_DMA2_TRGSEL register  */
#define AOS_DMA2_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_DMA2_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_DMA2_TRGSEL_COMEN_POS                      (30U)
#define AOS_DMA2_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_DMA2_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_DMA2_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_DMA_RC_TRGSEL register  */
#define AOS_DMA_RC_TRGSEL_TRGSEL_POS                   (0U)
#define AOS_DMA_RC_TRGSEL_TRGSEL                       (0x000001FFUL)
#define AOS_DMA_RC_TRGSEL_COMEN_POS                    (30U)
#define AOS_DMA_RC_TRGSEL_COMEN                        (0xC0000000UL)
#define AOS_DMA_RC_TRGSEL_COMEN_0                      (0x40000000UL)
#define AOS_DMA_RC_TRGSEL_COMEN_1                      (0x80000000UL)

/*  Bit definition for AOS_TMR6_TRGSEL register  */
#define AOS_TMR6_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_TMR6_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_TMR6_TRGSEL_COMEN_POS                      (30U)
#define AOS_TMR6_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_TMR6_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_TMR6_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_PEVNT_TRGSEL register  */
#define AOS_PEVNT_TRGSEL_TRGSEL_POS                    (0U)
#define AOS_PEVNT_TRGSEL_TRGSEL                        (0x000001FFUL)
#define AOS_PEVNT_TRGSEL_COMEN_POS                     (30U)
#define AOS_PEVNT_TRGSEL_COMEN                         (0xC0000000UL)
#define AOS_PEVNT_TRGSEL_COMEN_0                       (0x40000000UL)
#define AOS_PEVNT_TRGSEL_COMEN_1                       (0x80000000UL)

/*  Bit definition for AOS_TMR0_TRGSEL register  */
#define AOS_TMR0_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_TMR0_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_TMR0_TRGSEL_COMEN_POS                      (30U)
#define AOS_TMR0_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_TMR0_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_TMR0_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_TMR2_TRGSEL register  */
#define AOS_TMR2_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_TMR2_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_TMR2_TRGSEL_COMEN_POS                      (30U)
#define AOS_TMR2_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_TMR2_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_TMR2_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_HASH_TRGSELB register  */
#define AOS_HASH_TRGSELB_TRGSEL_POS                    (0U)
#define AOS_HASH_TRGSELB_TRGSEL                        (0x000001FFUL)
#define AOS_HASH_TRGSELB_COMEN_POS                     (30U)
#define AOS_HASH_TRGSELB_COMEN                         (0xC0000000UL)
#define AOS_HASH_TRGSELB_COMEN_0                       (0x40000000UL)
#define AOS_HASH_TRGSELB_COMEN_1                       (0x80000000UL)

/*  Bit definition for AOS_HASH_TRGSELA register  */
#define AOS_HASH_TRGSELA_TRGSEL_POS                    (0U)
#define AOS_HASH_TRGSELA_TRGSEL                        (0x000001FFUL)
#define AOS_HASH_TRGSELA_COMEN_POS                     (30U)
#define AOS_HASH_TRGSELA_COMEN                         (0xC0000000UL)
#define AOS_HASH_TRGSELA_COMEN_0                       (0x40000000UL)
#define AOS_HASH_TRGSELA_COMEN_1                       (0x80000000UL)

/*  Bit definition for AOS_TMRA_TRGSEL register  */
#define AOS_TMRA_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_TMRA_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_TMRA_TRGSEL_COMEN_POS                      (30U)
#define AOS_TMRA_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_TMRA_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_TMRA_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_OTS_TRGSEL register  */
#define AOS_OTS_TRGSEL_TRGSEL_POS                      (0U)
#define AOS_OTS_TRGSEL_TRGSEL                          (0x000001FFUL)
#define AOS_OTS_TRGSEL_COMEN_POS                       (30U)
#define AOS_OTS_TRGSEL_COMEN                           (0xC0000000UL)
#define AOS_OTS_TRGSEL_COMEN_0                         (0x40000000UL)
#define AOS_OTS_TRGSEL_COMEN_1                         (0x80000000UL)

/*  Bit definition for AOS_ADC1_TRGSEL register  */
#define AOS_ADC1_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_ADC1_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_ADC1_TRGSEL_COMEN_POS                      (30U)
#define AOS_ADC1_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_ADC1_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_ADC1_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_ADC2_TRGSEL register  */
#define AOS_ADC2_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_ADC2_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_ADC2_TRGSEL_COMEN_POS                      (30U)
#define AOS_ADC2_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_ADC2_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_ADC2_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_ADC3_TRGSEL register  */
#define AOS_ADC3_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_ADC3_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_ADC3_TRGSEL_COMEN_POS                      (30U)
#define AOS_ADC3_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_ADC3_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_ADC3_TRGSEL_COMEN_1                        (0x80000000UL)

/*  Bit definition for AOS_COMTRG1 register  */
#define AOS_COMTRG1_COMTRG                             (0x000001FFUL)

/*  Bit definition for AOS_COMTRG2 register  */
#define AOS_COMTRG2_COMTRG                             (0x000001FFUL)

/*  Bit definition for AOS_PEVNTDIRR register  */
#define AOS_PEVNTDIRR_PDIR                             (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTIDR register  */
#define AOS_PEVNTIDR_PIN                               (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTODR register  */
#define AOS_PEVNTODR_POUT                              (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTORR register  */
#define AOS_PEVNTORR_POR                               (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTOSR register  */
#define AOS_PEVNTOSR_POS                               (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTRISR register  */
#define AOS_PEVNTRISR_RIS                              (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTFALR register  */
#define AOS_PEVNTFALR_FAL                              (0x0000FFFFUL)

/*  Bit definition for AOS_PEVNTNFCR register  */
#define AOS_PEVNTNFCR_NFEN1_POS                        (0U)
#define AOS_PEVNTNFCR_NFEN1                            (0x00000001UL)
#define AOS_PEVNTNFCR_DIVS1_POS                        (1U)
#define AOS_PEVNTNFCR_DIVS1                            (0x00000006UL)
#define AOS_PEVNTNFCR_NFEN2_POS                        (8U)
#define AOS_PEVNTNFCR_NFEN2                            (0x00000100UL)
#define AOS_PEVNTNFCR_DIVS2_POS                        (9U)
#define AOS_PEVNTNFCR_DIVS2                            (0x00000600UL)
#define AOS_PEVNTNFCR_NFEN3_POS                        (16U)
#define AOS_PEVNTNFCR_NFEN3                            (0x00010000UL)
#define AOS_PEVNTNFCR_DIVS3_POS                        (17U)
#define AOS_PEVNTNFCR_DIVS3                            (0x00060000UL)
#define AOS_PEVNTNFCR_NFEN4_POS                        (24U)
#define AOS_PEVNTNFCR_NFEN4                            (0x01000000UL)
#define AOS_PEVNTNFCR_DIVS4_POS                        (25U)
#define AOS_PEVNTNFCR_DIVS4                            (0x06000000UL)

/*******************************************************************************
                Bit definition for Peripheral CAN
*******************************************************************************/
/*  Bit definition for CAN_RBUF register  */
#define CAN_RBUF                                       (0xFFFFFFFFUL)

/*  Bit definition for CAN_TBUF register  */
#define CAN_TBUF                                       (0xFFFFFFFFUL)

/*  Bit definition for CAN_CFG_STAT register  */
#define CAN_CFG_STAT_BUSOFF_POS                        (0U)
#define CAN_CFG_STAT_BUSOFF                            (0x01U)
#define CAN_CFG_STAT_TACTIVE_POS                       (1U)
#define CAN_CFG_STAT_TACTIVE                           (0x02U)
#define CAN_CFG_STAT_RACTIVE_POS                       (2U)
#define CAN_CFG_STAT_RACTIVE                           (0x04U)
#define CAN_CFG_STAT_TSSS_POS                          (3U)
#define CAN_CFG_STAT_TSSS                              (0x08U)
#define CAN_CFG_STAT_TPSS_POS                          (4U)
#define CAN_CFG_STAT_TPSS                              (0x10U)
#define CAN_CFG_STAT_LBMI_POS                          (5U)
#define CAN_CFG_STAT_LBMI                              (0x20U)
#define CAN_CFG_STAT_LBME_POS                          (6U)
#define CAN_CFG_STAT_LBME                              (0x40U)
#define CAN_CFG_STAT_RESET_POS                         (7U)
#define CAN_CFG_STAT_RESET                             (0x80U)

/*  Bit definition for CAN_TCMD register  */
#define CAN_TCMD_TSA_POS                               (0U)
#define CAN_TCMD_TSA                                   (0x01U)
#define CAN_TCMD_TSALL_POS                             (1U)
#define CAN_TCMD_TSALL                                 (0x02U)
#define CAN_TCMD_TSONE_POS                             (2U)
#define CAN_TCMD_TSONE                                 (0x04U)
#define CAN_TCMD_TPA_POS                               (3U)
#define CAN_TCMD_TPA                                   (0x08U)
#define CAN_TCMD_TPE_POS                               (4U)
#define CAN_TCMD_TPE                                   (0x10U)
#define CAN_TCMD_LOM_POS                               (6U)
#define CAN_TCMD_LOM                                   (0x40U)
#define CAN_TCMD_TBSEL_POS                             (7U)
#define CAN_TCMD_TBSEL                                 (0x80U)

/*  Bit definition for CAN_TCTRL register  */
#define CAN_TCTRL_TSSTAT_POS                           (0U)
#define CAN_TCTRL_TSSTAT                               (0x03U)
#define CAN_TCTRL_TSSTAT_0                             (0x01U)
#define CAN_TCTRL_TSSTAT_1                             (0x02U)
#define CAN_TCTRL_TTTBM_POS                            (4U)
#define CAN_TCTRL_TTTBM                                (0x10U)
#define CAN_TCTRL_TSMODE_POS                           (5U)
#define CAN_TCTRL_TSMODE                               (0x20U)
#define CAN_TCTRL_TSNEXT_POS                           (6U)
#define CAN_TCTRL_TSNEXT                               (0x40U)
#define CAN_TCTRL_FD_ISO_POS                           (7U)
#define CAN_TCTRL_FD_ISO                               (0x80U)

/*  Bit definition for CAN_RCTRL register  */
#define CAN_RCTRL_RSTAT_POS                            (0U)
#define CAN_RCTRL_RSTAT                                (0x03U)
#define CAN_RCTRL_RSTAT_0                              (0x01U)
#define CAN_RCTRL_RSTAT_1                              (0x02U)
#define CAN_RCTRL_RBALL_POS                            (3U)
#define CAN_RCTRL_RBALL                                (0x08U)
#define CAN_RCTRL_RREL_POS                             (4U)
#define CAN_RCTRL_RREL                                 (0x10U)
#define CAN_RCTRL_ROV_POS                              (5U)
#define CAN_RCTRL_ROV                                  (0x20U)
#define CAN_RCTRL_ROM_POS                              (6U)
#define CAN_RCTRL_ROM                                  (0x40U)
#define CAN_RCTRL_SACK_POS                             (7U)
#define CAN_RCTRL_SACK                                 (0x80U)

/*  Bit definition for CAN_RTIE register  */
#define CAN_RTIE_TSFF_POS                              (0U)
#define CAN_RTIE_TSFF                                  (0x01U)
#define CAN_RTIE_EIE_POS                               (1U)
#define CAN_RTIE_EIE                                   (0x02U)
#define CAN_RTIE_TSIE_POS                              (2U)
#define CAN_RTIE_TSIE                                  (0x04U)
#define CAN_RTIE_TPIE_POS                              (3U)
#define CAN_RTIE_TPIE                                  (0x08U)
#define CAN_RTIE_RAFIE_POS                             (4U)
#define CAN_RTIE_RAFIE                                 (0x10U)
#define CAN_RTIE_RFIE_POS                              (5U)
#define CAN_RTIE_RFIE                                  (0x20U)
#define CAN_RTIE_ROIE_POS                              (6U)
#define CAN_RTIE_ROIE                                  (0x40U)
#define CAN_RTIE_RIE_POS                               (7U)
#define CAN_RTIE_RIE                                   (0x80U)

/*  Bit definition for CAN_RTIF register  */
#define CAN_RTIF_AIF_POS                               (0U)
#define CAN_RTIF_AIF                                   (0x01U)
#define CAN_RTIF_EIF_POS                               (1U)
#define CAN_RTIF_EIF                                   (0x02U)
#define CAN_RTIF_TSIF_POS                              (2U)
#define CAN_RTIF_TSIF                                  (0x04U)
#define CAN_RTIF_TPIF_POS                              (3U)
#define CAN_RTIF_TPIF                                  (0x08U)
#define CAN_RTIF_RAFIF_POS                             (4U)
#define CAN_RTIF_RAFIF                                 (0x10U)
#define CAN_RTIF_RFIF_POS                              (5U)
#define CAN_RTIF_RFIF                                  (0x20U)
#define CAN_RTIF_ROIF_POS                              (6U)
#define CAN_RTIF_ROIF                                  (0x40U)
#define CAN_RTIF_RIF_POS                               (7U)
#define CAN_RTIF_RIF                                   (0x80U)

/*  Bit definition for CAN_ERRINT register  */
#define CAN_ERRINT_BEIF_POS                            (0U)
#define CAN_ERRINT_BEIF                                (0x01U)
#define CAN_ERRINT_BEIE_POS                            (1U)
#define CAN_ERRINT_BEIE                                (0x02U)
#define CAN_ERRINT_ALIF_POS                            (2U)
#define CAN_ERRINT_ALIF                                (0x04U)
#define CAN_ERRINT_ALIE_POS                            (3U)
#define CAN_ERRINT_ALIE                                (0x08U)
#define CAN_ERRINT_EPIF_POS                            (4U)
#define CAN_ERRINT_EPIF                                (0x10U)
#define CAN_ERRINT_EPIE_POS                            (5U)
#define CAN_ERRINT_EPIE                                (0x20U)
#define CAN_ERRINT_EPASS_POS                           (6U)
#define CAN_ERRINT_EPASS                               (0x40U)
#define CAN_ERRINT_EWARN_POS                           (7U)
#define CAN_ERRINT_EWARN                               (0x80U)

/*  Bit definition for CAN_LIMIT register  */
#define CAN_LIMIT_EWL_POS                              (0U)
#define CAN_LIMIT_EWL                                  (0x0FU)
#define CAN_LIMIT_AFWL_POS                             (4U)
#define CAN_LIMIT_AFWL                                 (0xF0U)

/*  Bit definition for CAN_SBT register  */
#define CAN_SBT_S_SEG_1_POS                            (0U)
#define CAN_SBT_S_SEG_1                                (0x000000FFUL)
#define CAN_SBT_S_SEG_2_POS                            (8U)
#define CAN_SBT_S_SEG_2                                (0x00007F00UL)
#define CAN_SBT_S_SJW_POS                              (16U)
#define CAN_SBT_S_SJW                                  (0x007F0000UL)
#define CAN_SBT_S_PRESC_POS                            (24U)
#define CAN_SBT_S_PRESC                                (0xFF000000UL)

/*  Bit definition for CAN_FBT register  */
#define CAN_FBT_F_SEG_1_POS                            (0U)
#define CAN_FBT_F_SEG_1                                (0x0000001FUL)
#define CAN_FBT_F_SEG_2_POS                            (8U)
#define CAN_FBT_F_SEG_2                                (0x00000F00UL)
#define CAN_FBT_F_SJW_POS                              (16U)
#define CAN_FBT_F_SJW                                  (0x000F0000UL)
#define CAN_FBT_F_PRESC_POS                            (24U)
#define CAN_FBT_F_PRESC                                (0xFF000000UL)

/*  Bit definition for CAN_EALCAP register  */
#define CAN_EALCAP_ALC_POS                             (0U)
#define CAN_EALCAP_ALC                                 (0x1FU)
#define CAN_EALCAP_KOER_POS                            (5U)
#define CAN_EALCAP_KOER                                (0xE0U)

/*  Bit definition for CAN_TDC register  */
#define CAN_TDC_SSPOFF_POS                             (0U)
#define CAN_TDC_SSPOFF                                 (0x7FU)
#define CAN_TDC_TDCEN_POS                              (7U)
#define CAN_TDC_TDCEN                                  (0x80U)

/*  Bit definition for CAN_RECNT register  */
#define CAN_RECNT                                      (0xFFU)

/*  Bit definition for CAN_TECNT register  */
#define CAN_TECNT                                      (0xFFU)

/*  Bit definition for CAN_ACFCTRL register  */
#define CAN_ACFCTRL_ACFADR_POS                         (0U)
#define CAN_ACFCTRL_ACFADR                             (0x0FU)
#define CAN_ACFCTRL_SELMASK_POS                        (5U)
#define CAN_ACFCTRL_SELMASK                            (0x20U)

/*  Bit definition for CAN_ACFEN register  */
#define CAN_ACFEN_AE_1_POS                             (0U)
#define CAN_ACFEN_AE_1                                 (0x0001U)
#define CAN_ACFEN_AE_2_POS                             (1U)
#define CAN_ACFEN_AE_2                                 (0x0002U)
#define CAN_ACFEN_AE_3_POS                             (2U)
#define CAN_ACFEN_AE_3                                 (0x0004U)
#define CAN_ACFEN_AE_4_POS                             (3U)
#define CAN_ACFEN_AE_4                                 (0x0008U)
#define CAN_ACFEN_AE_5_POS                             (4U)
#define CAN_ACFEN_AE_5                                 (0x0010U)
#define CAN_ACFEN_AE_6_POS                             (5U)
#define CAN_ACFEN_AE_6                                 (0x0020U)
#define CAN_ACFEN_AE_7_POS                             (6U)
#define CAN_ACFEN_AE_7                                 (0x0040U)
#define CAN_ACFEN_AE_8_POS                             (7U)
#define CAN_ACFEN_AE_8                                 (0x0080U)
#define CAN_ACFEN_AE_9_POS                             (8U)
#define CAN_ACFEN_AE_9                                 (0x0100U)
#define CAN_ACFEN_AE_10_POS                            (9U)
#define CAN_ACFEN_AE_10                                (0x0200U)
#define CAN_ACFEN_AE_11_POS                            (10U)
#define CAN_ACFEN_AE_11                                (0x0400U)
#define CAN_ACFEN_AE_12_POS                            (11U)
#define CAN_ACFEN_AE_12                                (0x0800U)
#define CAN_ACFEN_AE_13_POS                            (12U)
#define CAN_ACFEN_AE_13                                (0x1000U)
#define CAN_ACFEN_AE_14_POS                            (13U)
#define CAN_ACFEN_AE_14                                (0x2000U)
#define CAN_ACFEN_AE_15_POS                            (14U)
#define CAN_ACFEN_AE_15                                (0x4000U)
#define CAN_ACFEN_AE_16_POS                            (15U)
#define CAN_ACFEN_AE_16                                (0x8000U)

/*  Bit definition for CAN_ACF register  */
#define CAN_ACF_ACODEORAMASK_POS                       (0U)
#define CAN_ACF_ACODEORAMASK                           (0x1FFFFFFFUL)
#define CAN_ACF_AIDE_POS                               (29U)
#define CAN_ACF_AIDE                                   (0x20000000UL)
#define CAN_ACF_AIDEE_POS                              (30U)
#define CAN_ACF_AIDEE                                  (0x40000000UL)

/*  Bit definition for CAN_TBSLOT register  */
#define CAN_TBSLOT_TBPTR_POS                           (0U)
#define CAN_TBSLOT_TBPTR                               (0x3FU)
#define CAN_TBSLOT_TBF_POS                             (6U)
#define CAN_TBSLOT_TBF                                 (0x40U)
#define CAN_TBSLOT_TBE_POS                             (7U)
#define CAN_TBSLOT_TBE                                 (0x80U)

/*  Bit definition for CAN_TTCFG register  */
#define CAN_TTCFG_TTEN_POS                             (0U)
#define CAN_TTCFG_TTEN                                 (0x01U)
#define CAN_TTCFG_T_PRESC_POS                          (1U)
#define CAN_TTCFG_T_PRESC                              (0x06U)
#define CAN_TTCFG_T_PRESC_0                            (0x02U)
#define CAN_TTCFG_T_PRESC_1                            (0x04U)
#define CAN_TTCFG_TTIF_POS                             (3U)
#define CAN_TTCFG_TTIF                                 (0x08U)
#define CAN_TTCFG_TTIE_POS                             (4U)
#define CAN_TTCFG_TTIE                                 (0x10U)
#define CAN_TTCFG_TEIF_POS                             (5U)
#define CAN_TTCFG_TEIF                                 (0x20U)
#define CAN_TTCFG_WTIF_POS                             (6U)
#define CAN_TTCFG_WTIF                                 (0x40U)
#define CAN_TTCFG_WTIE_POS                             (7U)
#define CAN_TTCFG_WTIE                                 (0x80U)

/*  Bit definition for CAN_REF_MSG register  */
#define CAN_REF_MSG_REF_ID_POS                         (0U)
#define CAN_REF_MSG_REF_ID                             (0x1FFFFFFFUL)
#define CAN_REF_MSG_REF_IDE_POS                        (31U)
#define CAN_REF_MSG_REF_IDE                            (0x80000000UL)

/*  Bit definition for CAN_TRG_CFG register  */
#define CAN_TRG_CFG_TTPTR_POS                          (0U)
#define CAN_TRG_CFG_TTPTR                              (0x003FU)
#define CAN_TRG_CFG_TTYPE_POS                          (8U)
#define CAN_TRG_CFG_TTYPE                              (0x0700U)
#define CAN_TRG_CFG_TTYPE_0                            (0x0100U)
#define CAN_TRG_CFG_TTYPE_1                            (0x0200U)
#define CAN_TRG_CFG_TTYPE_2                            (0x0400U)
#define CAN_TRG_CFG_TEW_POS                            (12U)
#define CAN_TRG_CFG_TEW                                (0xF000U)

/*  Bit definition for CAN_TT_TRIG register  */
#define CAN_TT_TRIG                                    (0xFFFFU)

/*  Bit definition for CAN_TT_WTRIG register  */
#define CAN_TT_WTRIG                                   (0xFFFFU)

/*******************************************************************************
                Bit definition for Peripheral CMP
*******************************************************************************/
/*  Bit definition for CMP_MDR register  */
#define CMP_MDR_CENB_POS                               (0U)
#define CMP_MDR_CENB                                   (0x01U)
#define CMP_MDR_CWDE_POS                               (1U)
#define CMP_MDR_CWDE                                   (0x02U)
#define CMP_MDR_CMON_POS                               (7U)
#define CMP_MDR_CMON                                   (0x80U)

/*  Bit definition for CMP_FIR register  */
#define CMP_FIR_FCKS_POS                               (0U)
#define CMP_FIR_FCKS                                   (0x03U)
#define CMP_FIR_FCKS_0                                 (0x01U)
#define CMP_FIR_FCKS_1                                 (0x02U)
#define CMP_FIR_EDGS_POS                               (4U)
#define CMP_FIR_EDGS                                   (0x30U)
#define CMP_FIR_EDGS_0                                 (0x10U)
#define CMP_FIR_EDGS_1                                 (0x20U)
#define CMP_FIR_CIEN_POS                               (6U)
#define CMP_FIR_CIEN                                   (0x40U)

/*  Bit definition for CMP_OCR register  */
#define CMP_OCR_COEN_POS                               (0U)
#define CMP_OCR_COEN                                   (0x01U)
#define CMP_OCR_COPS_POS                               (1U)
#define CMP_OCR_COPS                                   (0x02U)
#define CMP_OCR_CPOE_POS                               (2U)
#define CMP_OCR_CPOE                                   (0x04U)
#define CMP_OCR_TWOE_POS                               (3U)
#define CMP_OCR_TWOE                                   (0x08U)
#define CMP_OCR_TWOL_POS                               (4U)
#define CMP_OCR_TWOL                                   (0x10U)

/*  Bit definition for CMP_PMSR register  */
#define CMP_PMSR_RVSL_POS                              (0U)
#define CMP_PMSR_RVSL                                  (0x0FU)
#define CMP_PMSR_RVSL_0                                (0x01U)
#define CMP_PMSR_RVSL_1                                (0x02U)
#define CMP_PMSR_RVSL_2                                (0x04U)
#define CMP_PMSR_RVSL_3                                (0x08U)
#define CMP_PMSR_CVSL_POS                              (4U)
#define CMP_PMSR_CVSL                                  (0xF0U)
#define CMP_PMSR_CVSL_0                                (0x10U)
#define CMP_PMSR_CVSL_1                                (0x20U)
#define CMP_PMSR_CVSL_2                                (0x40U)
#define CMP_PMSR_CVSL_3                                (0x80U)

/*  Bit definition for CMP_TWSR register  */
#define CMP_TWSR_CTWS0_POS                             (0U)
#define CMP_TWSR_CTWS0                                 (0x0001U)
#define CMP_TWSR_CTWS1_POS                             (1U)
#define CMP_TWSR_CTWS1                                 (0x0002U)
#define CMP_TWSR_CTWS2_POS                             (2U)
#define CMP_TWSR_CTWS2                                 (0x0004U)
#define CMP_TWSR_CTWS3_POS                             (3U)
#define CMP_TWSR_CTWS3                                 (0x0008U)
#define CMP_TWSR_CTWS4_POS                             (4U)
#define CMP_TWSR_CTWS4                                 (0x0010U)
#define CMP_TWSR_CTWS5_POS                             (5U)
#define CMP_TWSR_CTWS5                                 (0x0020U)
#define CMP_TWSR_CTWS6_POS                             (6U)
#define CMP_TWSR_CTWS6                                 (0x0040U)
#define CMP_TWSR_CTWS7_POS                             (7U)
#define CMP_TWSR_CTWS7                                 (0x0080U)
#define CMP_TWSR_CTWS8_POS                             (8U)
#define CMP_TWSR_CTWS8                                 (0x0100U)
#define CMP_TWSR_CTWS9_POS                             (9U)
#define CMP_TWSR_CTWS9                                 (0x0200U)
#define CMP_TWSR_CTWS10_POS                            (10U)
#define CMP_TWSR_CTWS10                                (0x0400U)
#define CMP_TWSR_CTWS11_POS                            (11U)
#define CMP_TWSR_CTWS11                                (0x0800U)
#define CMP_TWSR_CTWS12_POS                            (12U)
#define CMP_TWSR_CTWS12                                (0x1000U)
#define CMP_TWSR_CTWS13_POS                            (13U)
#define CMP_TWSR_CTWS13                                (0x2000U)
#define CMP_TWSR_CTWS14_POS                            (14U)
#define CMP_TWSR_CTWS14                                (0x4000U)
#define CMP_TWSR_CTWS15_POS                            (15U)
#define CMP_TWSR_CTWS15                                (0x8000U)

/*  Bit definition for CMP_TWPR register  */
#define CMP_TWPR_CTWP0_POS                             (0U)
#define CMP_TWPR_CTWP0                                 (0x0001U)
#define CMP_TWPR_CTWP1_POS                             (1U)
#define CMP_TWPR_CTWP1                                 (0x0002U)
#define CMP_TWPR_CTWP2_POS                             (2U)
#define CMP_TWPR_CTWP2                                 (0x0004U)
#define CMP_TWPR_CTWP3_POS                             (3U)
#define CMP_TWPR_CTWP3                                 (0x0008U)
#define CMP_TWPR_CTWP4_POS                             (4U)
#define CMP_TWPR_CTWP4                                 (0x0010U)
#define CMP_TWPR_CTWP5_POS                             (5U)
#define CMP_TWPR_CTWP5                                 (0x0020U)
#define CMP_TWPR_CTWP6_POS                             (6U)
#define CMP_TWPR_CTWP6                                 (0x0040U)
#define CMP_TWPR_CTWP7_POS                             (7U)
#define CMP_TWPR_CTWP7                                 (0x0080U)
#define CMP_TWPR_CTWP8_POS                             (8U)
#define CMP_TWPR_CTWP8                                 (0x0100U)
#define CMP_TWPR_CTWP9_POS                             (9U)
#define CMP_TWPR_CTWP9                                 (0x0200U)
#define CMP_TWPR_CTWP10_POS                            (10U)
#define CMP_TWPR_CTWP10                                (0x0400U)
#define CMP_TWPR_CTWP11_POS                            (11U)
#define CMP_TWPR_CTWP11                                (0x0800U)
#define CMP_TWPR_CTWP12_POS                            (12U)
#define CMP_TWPR_CTWP12                                (0x1000U)
#define CMP_TWPR_CTWP13_POS                            (13U)
#define CMP_TWPR_CTWP13                                (0x2000U)
#define CMP_TWPR_CTWP14_POS                            (14U)
#define CMP_TWPR_CTWP14                                (0x4000U)
#define CMP_TWPR_CTWP15_POS                            (15U)
#define CMP_TWPR_CTWP15                                (0x8000U)

/*  Bit definition for CMP_VISR register  */
#define CMP_VISR_P2SL_POS                              (0U)
#define CMP_VISR_P2SL                                  (0x0007U)
#define CMP_VISR_P2SL_0                                (0x0001U)
#define CMP_VISR_P2SL_1                                (0x0002U)
#define CMP_VISR_P2SL_2                                (0x0004U)
#define CMP_VISR_P3SL_POS                              (4U)
#define CMP_VISR_P3SL                                  (0x0030U)
#define CMP_VISR_P3SL_0                                (0x0010U)
#define CMP_VISR_P3SL_1                                (0x0020U)

/*******************************************************************************
                Bit definition for Peripheral CMU
*******************************************************************************/
/*  Bit definition for CMU_XTAL32CR register  */
#define CMU_XTAL32CR_XTAL32STP                         (0x01U)

/*  Bit definition for CMU_XTAL32CFGR register  */
#define CMU_XTAL32CFGR_XTAL32DRV_POS                   (0U)
#define CMU_XTAL32CFGR_XTAL32DRV                       (0x07U)
#define CMU_XTAL32CFGR_XTAL32IE_POS                    (3U)
#define CMU_XTAL32CFGR_XTAL32IE                        (0x08U)

/*  Bit definition for CMU_XTAL32NFR register  */
#define CMU_XTAL32NFR_XTAL32NF                         (0x03U)

/*  Bit definition for CMU_LRCCR register  */
#define CMU_LRCCR_LRCSTP                               (0x01U)

/*  Bit definition for CMU_LRCTRM register  */
#define CMU_LRCTRM                                     (0xFFU)

/*  Bit definition for CMU_RTCLRCTRM register  */
#define CMU_RTCLRCTRM                                  (0xFFU)

/*  Bit definition for CMU_XTALCFGR register  */
#define CMU_XTALCFGR_XTALDRV_POS                       (4U)
#define CMU_XTALCFGR_XTALDRV                           (0x30U)
#define CMU_XTALCFGR_XTALMS_POS                        (6U)
#define CMU_XTALCFGR_XTALMS                            (0x40U)

/*  Bit definition for CMU_PERICKSEL register  */
#define CMU_PERICKSEL_PERICKSEL                        (0x000FU)

/*  Bit definition for CMU_I2SCKSEL register  */
#define CMU_I2SCKSEL_I2S1CKSEL_POS                     (0U)
#define CMU_I2SCKSEL_I2S1CKSEL                         (0x000FU)
#define CMU_I2SCKSEL_I2S2CKSEL_POS                     (4U)
#define CMU_I2SCKSEL_I2S2CKSEL                         (0x00F0U)
#define CMU_I2SCKSEL_I2S3CKSEL_POS                     (8U)
#define CMU_I2SCKSEL_I2S3CKSEL                         (0x0F00U)
#define CMU_I2SCKSEL_I2S4CKSEL_POS                     (12U)
#define CMU_I2SCKSEL_I2S4CKSEL                         (0xF000U)

/*  Bit definition for CMU_CANCKCFGR register  */
#define CMU_CANCKCFGR_CAN1CKS_POS                      (0U)
#define CMU_CANCKCFGR_CAN1CKS                          (0x0FU)
#define CMU_CANCKCFGR_CAN2CKS_POS                      (4U)
#define CMU_CANCKCFGR_CAN2CKS                          (0xF0U)

/*  Bit definition for CMU_SCFGR register  */
#define CMU_SCFGR_PCLK0S_POS                           (0U)
#define CMU_SCFGR_PCLK0S                               (0x00000007UL)
#define CMU_SCFGR_PCLK1S_POS                           (4U)
#define CMU_SCFGR_PCLK1S                               (0x00000070UL)
#define CMU_SCFGR_PCLK2S_POS                           (8U)
#define CMU_SCFGR_PCLK2S                               (0x00000700UL)
#define CMU_SCFGR_PCLK3S_POS                           (12U)
#define CMU_SCFGR_PCLK3S                               (0x00007000UL)
#define CMU_SCFGR_PCLK4S_POS                           (16U)
#define CMU_SCFGR_PCLK4S                               (0x00070000UL)
#define CMU_SCFGR_EXCKS_POS                            (20U)
#define CMU_SCFGR_EXCKS                                (0x00700000UL)
#define CMU_SCFGR_HCLKS_POS                            (24U)
#define CMU_SCFGR_HCLKS                                (0x07000000UL)

/*  Bit definition for CMU_USBCKCFGR register  */
#define CMU_USBCKCFGR_USBCKS_POS                       (4U)
#define CMU_USBCKCFGR_USBCKS                           (0xF0U)

/*  Bit definition for CMU_CKSWR register  */
#define CMU_CKSWR_CKSW                                 (0x07U)

/*  Bit definition for CMU_PLLHCR register  */
#define CMU_PLLHCR_PLLHOFF                             (0x01U)

/*  Bit definition for CMU_PLLACR register  */
#define CMU_PLLACR_PLLAOFF                             (0x01U)

/*  Bit definition for CMU_XTALCR register  */
#define CMU_XTALCR_XTALSTP                             (0x01U)

/*  Bit definition for CMU_HRCCR register  */
#define CMU_HRCCR_HRCSTP                               (0x01U)

/*  Bit definition for CMU_MRCCR register  */
#define CMU_MRCCR_MRCSTP                               (0x01U)

/*  Bit definition for CMU_OSCSTBSR register  */
#define CMU_OSCSTBSR_HRCSTBF_POS                       (0U)
#define CMU_OSCSTBSR_HRCSTBF                           (0x01U)
#define CMU_OSCSTBSR_XTALSTBF_POS                      (3U)
#define CMU_OSCSTBSR_XTALSTBF                          (0x08U)
#define CMU_OSCSTBSR_PLLHSTBF_POS                      (5U)
#define CMU_OSCSTBSR_PLLHSTBF                          (0x20U)
#define CMU_OSCSTBSR_PLLASTBF_POS                      (6U)
#define CMU_OSCSTBSR_PLLASTBF                          (0x40U)

/*  Bit definition for CMU_MCOCFGR register  */
#define CMU_MCOCFGR_MCOSEL_POS                         (0U)
#define CMU_MCOCFGR_MCOSEL                             (0x0FU)
#define CMU_MCOCFGR_MCODIV_POS                         (4U)
#define CMU_MCOCFGR_MCODIV                             (0x70U)
#define CMU_MCOCFGR_MCOEN_POS                          (7U)
#define CMU_MCOCFGR_MCOEN                              (0x80U)

/*  Bit definition for CMU_TPIUCKCFGR register  */
#define CMU_TPIUCKCFGR_TPIUCKS_POS                     (0U)
#define CMU_TPIUCKCFGR_TPIUCKS                         (0x03U)
#define CMU_TPIUCKCFGR_TPIUCKOE_POS                    (7U)
#define CMU_TPIUCKCFGR_TPIUCKOE                        (0x80U)

/*  Bit definition for CMU_XTALSTDCR register  */
#define CMU_XTALSTDCR_XTALSTDIE_POS                    (0U)
#define CMU_XTALSTDCR_XTALSTDIE                        (0x01U)
#define CMU_XTALSTDCR_XTALSTDRE_POS                    (1U)
#define CMU_XTALSTDCR_XTALSTDRE                        (0x02U)
#define CMU_XTALSTDCR_XTALSTDRIS_POS                   (2U)
#define CMU_XTALSTDCR_XTALSTDRIS                       (0x04U)
#define CMU_XTALSTDCR_XTALSTDE_POS                     (7U)
#define CMU_XTALSTDCR_XTALSTDE                         (0x80U)

/*  Bit definition for CMU_XTALSTDSR register  */
#define CMU_XTALSTDSR_XTALSTDF                         (0x01U)

/*  Bit definition for CMU_MRCTRM register  */
#define CMU_MRCTRM                                     (0xFFU)

/*  Bit definition for CMU_HRCTRM register  */
#define CMU_HRCTRM                                     (0xFFU)

/*  Bit definition for CMU_XTALSTBCR register  */
#define CMU_XTALSTBCR_XTALSTB                          (0x0FU)

/*  Bit definition for CMU_PLLHCFGR register  */
#define CMU_PLLHCFGR_PLLHM_POS                         (0U)
#define CMU_PLLHCFGR_PLLHM                             (0x00000003UL)
#define CMU_PLLHCFGR_PLLSRC_POS                        (7U)
#define CMU_PLLHCFGR_PLLSRC                            (0x00000080UL)
#define CMU_PLLHCFGR_PLLHN_POS                         (8U)
#define CMU_PLLHCFGR_PLLHN                             (0x0000FF00UL)
#define CMU_PLLHCFGR_PLLHR_POS                         (20U)
#define CMU_PLLHCFGR_PLLHR                             (0x00F00000UL)
#define CMU_PLLHCFGR_PLLHQ_POS                         (24U)
#define CMU_PLLHCFGR_PLLHQ                             (0x0F000000UL)
#define CMU_PLLHCFGR_PLLHP_POS                         (28U)
#define CMU_PLLHCFGR_PLLHP                             (0xF0000000UL)

/*  Bit definition for CMU_PLLACFGR register  */
#define CMU_PLLACFGR_PLLAM_POS                         (0U)
#define CMU_PLLACFGR_PLLAM                             (0x0000001FUL)
#define CMU_PLLACFGR_PLLAN_POS                         (8U)
#define CMU_PLLACFGR_PLLAN                             (0x0001FF00UL)
#define CMU_PLLACFGR_PLLAR_POS                         (20U)
#define CMU_PLLACFGR_PLLAR                             (0x00F00000UL)
#define CMU_PLLACFGR_PLLAQ_POS                         (24U)
#define CMU_PLLACFGR_PLLAQ                             (0x0F000000UL)
#define CMU_PLLACFGR_PLLAP_POS                         (28U)
#define CMU_PLLACFGR_PLLAP                             (0xF0000000UL)

/*******************************************************************************
                Bit definition for Peripheral CRC
*******************************************************************************/
/*  Bit definition for CRC_CR register  */
#define CRC_CR_CR_POS                                  (0U)
#define CRC_CR_CR                                      (0x00000001UL)
#define CRC_CR_FLAG_POS                                (1U)
#define CRC_CR_FLAG                                    (0x00000002UL)

/*  Bit definition for CRC_RESLT register  */
#define CRC_RESLT                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT0 register  */
#define CRC_DAT0                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT1 register  */
#define CRC_DAT1                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT2 register  */
#define CRC_DAT2                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT3 register  */
#define CRC_DAT3                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT4 register  */
#define CRC_DAT4                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT5 register  */
#define CRC_DAT5                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT6 register  */
#define CRC_DAT6                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT7 register  */
#define CRC_DAT7                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT8 register  */
#define CRC_DAT8                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT9 register  */
#define CRC_DAT9                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT10 register  */
#define CRC_DAT10                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT11 register  */
#define CRC_DAT11                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT12 register  */
#define CRC_DAT12                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT13 register  */
#define CRC_DAT13                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT14 register  */
#define CRC_DAT14                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT15 register  */
#define CRC_DAT15                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT16 register  */
#define CRC_DAT16                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT17 register  */
#define CRC_DAT17                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT18 register  */
#define CRC_DAT18                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT19 register  */
#define CRC_DAT19                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT20 register  */
#define CRC_DAT20                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT21 register  */
#define CRC_DAT21                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT22 register  */
#define CRC_DAT22                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT23 register  */
#define CRC_DAT23                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT24 register  */
#define CRC_DAT24                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT25 register  */
#define CRC_DAT25                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT26 register  */
#define CRC_DAT26                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT27 register  */
#define CRC_DAT27                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT28 register  */
#define CRC_DAT28                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT29 register  */
#define CRC_DAT29                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT30 register  */
#define CRC_DAT30                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT31 register  */
#define CRC_DAT31                                      (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral CTC
*******************************************************************************/
/*  Bit definition for CTC_CR1 register  */
#define CTC_CR1_REFPSC_POS                             (0U)
#define CTC_CR1_REFPSC                                 (0x00000007UL)
#define CTC_CR1_REFPSC_0                               (0x00000001UL)
#define CTC_CR1_REFPSC_1                               (0x00000002UL)
#define CTC_CR1_REFPSC_2                               (0x00000004UL)
#define CTC_CR1_REFCKS_POS                             (4U)
#define CTC_CR1_REFCKS                                 (0x00000030UL)
#define CTC_CR1_REFCKS_0                               (0x00000010UL)
#define CTC_CR1_REFCKS_1                               (0x00000020UL)
#define CTC_CR1_ERRIE_POS                              (6U)
#define CTC_CR1_ERRIE                                  (0x00000040UL)
#define CTC_CR1_CTCEN_POS                              (7U)
#define CTC_CR1_CTCEN                                  (0x00000080UL)
#define CTC_CR1_TRMVAL_POS                             (16U)
#define CTC_CR1_TRMVAL                                 (0x003F0000UL)

/*  Bit definition for CTC_CR2 register  */
#define CTC_CR2_OFSVAL_POS                             (0U)
#define CTC_CR2_OFSVAL                                 (0x000000FFUL)
#define CTC_CR2_RLDVAL_POS                             (16U)
#define CTC_CR2_RLDVAL                                 (0xFFFF0000UL)

/*  Bit definition for CTC_STR register  */
#define CTC_STR_TRIMOK_POS                             (0U)
#define CTC_STR_TRIMOK                                 (0x00000001UL)
#define CTC_STR_TRMOVF_POS                             (1U)
#define CTC_STR_TRMOVF                                 (0x00000002UL)
#define CTC_STR_TRMUDF_POS                             (2U)
#define CTC_STR_TRMUDF                                 (0x00000004UL)
#define CTC_STR_CTCBSY_POS                             (3U)
#define CTC_STR_CTCBSY                                 (0x00000008UL)

/*******************************************************************************
                Bit definition for Peripheral DAC
*******************************************************************************/
/*  Bit definition for DAC_DADR1 register  */
#define DAC_DADR1                                      (0xFFFFU)

/*  Bit definition for DAC_DADR2 register  */
#define DAC_DADR2                                      (0xFFFFU)

/*  Bit definition for DAC_DACR register  */
#define DAC_DACR_DAE_POS                               (0U)
#define DAC_DACR_DAE                                   (0x0001U)
#define DAC_DACR_DA1E_POS                              (1U)
#define DAC_DACR_DA1E                                  (0x0002U)
#define DAC_DACR_DA2E_POS                              (2U)
#define DAC_DACR_DA2E                                  (0x0004U)
#define DAC_DACR_DPSEL_POS                             (8U)
#define DAC_DACR_DPSEL                                 (0x0100U)
#define DAC_DACR_DAAMP1_POS                            (9U)
#define DAC_DACR_DAAMP1                                (0x0200U)
#define DAC_DACR_DAAMP2_POS                            (10U)
#define DAC_DACR_DAAMP2                                (0x0400U)
#define DAC_DACR_EXTDSL1_POS                           (11U)
#define DAC_DACR_EXTDSL1                               (0x0800U)
#define DAC_DACR_EXTDSL2_POS                           (12U)
#define DAC_DACR_EXTDSL2                               (0x1000U)

/*  Bit definition for DAC_DAADPCR register  */
#define DAC_DAADPCR_ADCSL1_POS                         (0U)
#define DAC_DAADPCR_ADCSL1                             (0x0001U)
#define DAC_DAADPCR_ADCSL2_POS                         (1U)
#define DAC_DAADPCR_ADCSL2                             (0x0002U)
#define DAC_DAADPCR_ADCSL3_POS                         (2U)
#define DAC_DAADPCR_ADCSL3                             (0x0004U)
#define DAC_DAADPCR_DA1SF_POS                          (8U)
#define DAC_DAADPCR_DA1SF                              (0x0100U)
#define DAC_DAADPCR_DA2SF_POS                          (9U)
#define DAC_DAADPCR_DA2SF                              (0x0200U)
#define DAC_DAADPCR_ADPEN_POS                          (15U)
#define DAC_DAADPCR_ADPEN                              (0x8000U)

/*  Bit definition for DAC_DAOCR register  */
#define DAC_DAOCR_DAODIS1_POS                          (14U)
#define DAC_DAOCR_DAODIS1                              (0x4000U)
#define DAC_DAOCR_DAODIS2_POS                          (15U)
#define DAC_DAOCR_DAODIS2                              (0x8000U)

/*******************************************************************************
                Bit definition for Peripheral DBGC
*******************************************************************************/
/*  Bit definition for DBGC_AUTHID0 register  */
#define DBGC_AUTHID0                                   (0xFFFFFFFFUL)

/*  Bit definition for DBGC_AUTHID1 register  */
#define DBGC_AUTHID1                                   (0xFFFFFFFFUL)

/*  Bit definition for DBGC_AUTHID2 register  */
#define DBGC_AUTHID2                                   (0xFFFFFFFFUL)

/*  Bit definition for DBGC_MCUSTAT register  */
#define DBGC_MCUSTAT_AUTHFG_POS                        (0U)
#define DBGC_MCUSTAT_AUTHFG                            (0x00000001UL)
#define DBGC_MCUSTAT_PRTLV1_POS                        (2U)
#define DBGC_MCUSTAT_PRTLV1                            (0x00000004UL)
#define DBGC_MCUSTAT_PRTLV2_POS                        (3U)
#define DBGC_MCUSTAT_PRTLV2                            (0x00000008UL)

/*  Bit definition for DBGC_FERSCTL register  */
#define DBGC_FERSCTL_ERASEREQ_POS                      (0U)
#define DBGC_FERSCTL_ERASEREQ                          (0x00000001UL)
#define DBGC_FERSCTL_ERASEACK_POS                      (1U)
#define DBGC_FERSCTL_ERASEACK                          (0x00000002UL)
#define DBGC_FERSCTL_ERASEERR_POS                      (2U)
#define DBGC_FERSCTL_ERASEERR                          (0x00000004UL)

/*  Bit definition for DBGC_MCUDBGCSTAT register  */
#define DBGC_MCUDBGCSTAT_CDBGPWRUPREQ_POS              (0U)
#define DBGC_MCUDBGCSTAT_CDBGPWRUPREQ                  (0x00000001UL)
#define DBGC_MCUDBGCSTAT_CDBGPWRUPACK_POS              (1U)
#define DBGC_MCUDBGCSTAT_CDBGPWRUPACK                  (0x00000002UL)

/*  Bit definition for DBGC_MCUSTPCTL register  */
#define DBGC_MCUSTPCTL_SWDTSTP_POS                     (0U)
#define DBGC_MCUSTPCTL_SWDTSTP                         (0x00000001UL)
#define DBGC_MCUSTPCTL_WDTSTP_POS                      (1U)
#define DBGC_MCUSTPCTL_WDTSTP                          (0x00000002UL)
#define DBGC_MCUSTPCTL_RTCSTP_POS                      (2U)
#define DBGC_MCUSTPCTL_RTCSTP                          (0x00000004UL)
#define DBGC_MCUSTPCTL_M06STP_POS                      (6U)
#define DBGC_MCUSTPCTL_M06STP                          (0x00000040UL)
#define DBGC_MCUSTPCTL_M07STP_POS                      (7U)
#define DBGC_MCUSTPCTL_M07STP                          (0x00000080UL)
#define DBGC_MCUSTPCTL_M08STP_POS                      (8U)
#define DBGC_MCUSTPCTL_M08STP                          (0x00000100UL)
#define DBGC_MCUSTPCTL_M09STP_POS                      (9U)
#define DBGC_MCUSTPCTL_M09STP                          (0x00000200UL)
#define DBGC_MCUSTPCTL_M10STP_POS                      (10U)
#define DBGC_MCUSTPCTL_M10STP                          (0x00000400UL)
#define DBGC_MCUSTPCTL_M11STP_POS                      (11U)
#define DBGC_MCUSTPCTL_M11STP                          (0x00000800UL)
#define DBGC_MCUSTPCTL_M12STP_POS                      (12U)
#define DBGC_MCUSTPCTL_M12STP                          (0x00001000UL)
#define DBGC_MCUSTPCTL_M13STP_POS                      (13U)
#define DBGC_MCUSTPCTL_M13STP                          (0x00002000UL)
#define DBGC_MCUSTPCTL_M14STP_POS                      (14U)
#define DBGC_MCUSTPCTL_M14STP                          (0x00004000UL)
#define DBGC_MCUSTPCTL_M15STP_POS                      (15U)
#define DBGC_MCUSTPCTL_M15STP                          (0x00008000UL)
#define DBGC_MCUSTPCTL_M16STP_POS                      (16U)
#define DBGC_MCUSTPCTL_M16STP                          (0x00010000UL)
#define DBGC_MCUSTPCTL_M17STP_POS                      (17U)
#define DBGC_MCUSTPCTL_M17STP                          (0x00020000UL)
#define DBGC_MCUSTPCTL_M18STP_POS                      (18U)
#define DBGC_MCUSTPCTL_M18STP                          (0x00040000UL)
#define DBGC_MCUSTPCTL_M19STP_POS                      (19U)
#define DBGC_MCUSTPCTL_M19STP                          (0x00080000UL)
#define DBGC_MCUSTPCTL_M20STP_POS                      (20U)
#define DBGC_MCUSTPCTL_M20STP                          (0x00100000UL)
#define DBGC_MCUSTPCTL_M21STP_POS                      (21U)
#define DBGC_MCUSTPCTL_M21STP                          (0x00200000UL)
#define DBGC_MCUSTPCTL_M22STP_POS                      (22U)
#define DBGC_MCUSTPCTL_M22STP                          (0x00400000UL)

/*  Bit definition for DBGC_MCUTRACECTL register  */
#define DBGC_MCUTRACECTL_TRACEMODE_POS                 (0U)
#define DBGC_MCUTRACECTL_TRACEMODE                     (0x00000003UL)
#define DBGC_MCUTRACECTL_TRACEMODE_0                   (0x00000001UL)
#define DBGC_MCUTRACECTL_TRACEMODE_1                   (0x00000002UL)
#define DBGC_MCUTRACECTL_TRACEIOEN_POS                 (2U)
#define DBGC_MCUTRACECTL_TRACEIOEN                     (0x00000004UL)

/*  Bit definition for DBGC_MCUSTPCTL2 register  */
#define DBGC_MCUSTPCTL2_M32STP_POS                     (0U)
#define DBGC_MCUSTPCTL2_M32STP                         (0x00000001UL)
#define DBGC_MCUSTPCTL2_M33STP_POS                     (1U)
#define DBGC_MCUSTPCTL2_M33STP                         (0x00000002UL)
#define DBGC_MCUSTPCTL2_M34STP_POS                     (2U)
#define DBGC_MCUSTPCTL2_M34STP                         (0x00000004UL)
#define DBGC_MCUSTPCTL2_M35STP_POS                     (3U)
#define DBGC_MCUSTPCTL2_M35STP                         (0x00000008UL)
#define DBGC_MCUSTPCTL2_M36STP_POS                     (4U)
#define DBGC_MCUSTPCTL2_M36STP                         (0x00000010UL)
#define DBGC_MCUSTPCTL2_M37STP_POS                     (5U)
#define DBGC_MCUSTPCTL2_M37STP                         (0x00000020UL)
#define DBGC_MCUSTPCTL2_M38STP_POS                     (6U)
#define DBGC_MCUSTPCTL2_M38STP                         (0x00000040UL)
#define DBGC_MCUSTPCTL2_M39STP_POS                     (7U)
#define DBGC_MCUSTPCTL2_M39STP                         (0x00000080UL)
#define DBGC_MCUSTPCTL2_M40STP_POS                     (8U)
#define DBGC_MCUSTPCTL2_M40STP                         (0x00000100UL)
#define DBGC_MCUSTPCTL2_M41STP_POS                     (9U)
#define DBGC_MCUSTPCTL2_M41STP                         (0x00000200UL)
#define DBGC_MCUSTPCTL2_M42STP_POS                     (10U)
#define DBGC_MCUSTPCTL2_M42STP                         (0x00000400UL)
#define DBGC_MCUSTPCTL2_M43STP_POS                     (11U)
#define DBGC_MCUSTPCTL2_M43STP                         (0x00000800UL)

/*******************************************************************************
                Bit definition for Peripheral DCU
*******************************************************************************/
/*  Bit definition for DCU_CTL register  */
#define DCU_CTL_MODE_POS                               (0U)
#define DCU_CTL_MODE                                   (0x0000000FUL)
#define DCU_CTL_MODE_0                                 (0x00000001UL)
#define DCU_CTL_MODE_1                                 (0x00000002UL)
#define DCU_CTL_MODE_2                                 (0x00000004UL)
#define DCU_CTL_MODE_3                                 (0x00000008UL)
#define DCU_CTL_DATASIZE_POS                           (4U)
#define DCU_CTL_DATASIZE                               (0x00000030UL)
#define DCU_CTL_DATASIZE_0                             (0x00000010UL)
#define DCU_CTL_DATASIZE_1                             (0x00000020UL)
#define DCU_CTL_COMPTRG_POS                            (8U)
#define DCU_CTL_COMPTRG                                (0x00000100UL)
#define DCU_CTL_INTEN_POS                              (31U)
#define DCU_CTL_INTEN                                  (0x80000000UL)

/*  Bit definition for DCU_FLAG register  */
#define DCU_FLAG_FLAG_OP_POS                           (0U)
#define DCU_FLAG_FLAG_OP                               (0x00000001UL)
#define DCU_FLAG_FLAG_LS2_POS                          (1U)
#define DCU_FLAG_FLAG_LS2                              (0x00000002UL)
#define DCU_FLAG_FLAG_EQ2_POS                          (2U)
#define DCU_FLAG_FLAG_EQ2                              (0x00000004UL)
#define DCU_FLAG_FLAG_GT2_POS                          (3U)
#define DCU_FLAG_FLAG_GT2                              (0x00000008UL)
#define DCU_FLAG_FLAG_LS1_POS                          (4U)
#define DCU_FLAG_FLAG_LS1                              (0x00000010UL)
#define DCU_FLAG_FLAG_EQ1_POS                          (5U)
#define DCU_FLAG_FLAG_EQ1                              (0x00000020UL)
#define DCU_FLAG_FLAG_GT1_POS                          (6U)
#define DCU_FLAG_FLAG_GT1                              (0x00000040UL)
#define DCU_FLAG_FLAG_RLD_POS                          (9U)
#define DCU_FLAG_FLAG_RLD                              (0x00000200UL)
#define DCU_FLAG_FLAG_BTM_POS                          (10U)
#define DCU_FLAG_FLAG_BTM                              (0x00000400UL)
#define DCU_FLAG_FLAG_TOP_POS                          (11U)
#define DCU_FLAG_FLAG_TOP                              (0x00000800UL)

/*  Bit definition for DCU_DATA0 register  */
#define DCU_DATA0                                      (0xFFFFFFFFUL)

/*  Bit definition for DCU_DATA1 register  */
#define DCU_DATA1                                      (0xFFFFFFFFUL)

/*  Bit definition for DCU_DATA2 register  */
#define DCU_DATA2                                      (0xFFFFFFFFUL)

/*  Bit definition for DCU_FLAGCLR register  */
#define DCU_FLAGCLR_CLR_OP_POS                         (0U)
#define DCU_FLAGCLR_CLR_OP                             (0x00000001UL)
#define DCU_FLAGCLR_CLR_LS2_POS                        (1U)
#define DCU_FLAGCLR_CLR_LS2                            (0x00000002UL)
#define DCU_FLAGCLR_CLR_EQ2_POS                        (2U)
#define DCU_FLAGCLR_CLR_EQ2                            (0x00000004UL)
#define DCU_FLAGCLR_CLR_GT2_POS                        (3U)
#define DCU_FLAGCLR_CLR_GT2                            (0x00000008UL)
#define DCU_FLAGCLR_CLR_LS1_POS                        (4U)
#define DCU_FLAGCLR_CLR_LS1                            (0x00000010UL)
#define DCU_FLAGCLR_CLR_EQ1_POS                        (5U)
#define DCU_FLAGCLR_CLR_EQ1                            (0x00000020UL)
#define DCU_FLAGCLR_CLR_GT1_POS                        (6U)
#define DCU_FLAGCLR_CLR_GT1                            (0x00000040UL)
#define DCU_FLAGCLR_CLR_RLD_POS                        (9U)
#define DCU_FLAGCLR_CLR_RLD                            (0x00000200UL)
#define DCU_FLAGCLR_CLR_BTM_POS                        (10U)
#define DCU_FLAGCLR_CLR_BTM                            (0x00000400UL)
#define DCU_FLAGCLR_CLR_TOP_POS                        (11U)
#define DCU_FLAGCLR_CLR_TOP                            (0x00000800UL)

/*  Bit definition for DCU_INTEVTSEL register  */
#define DCU_INTEVTSEL_SEL_OP_POS                       (0U)
#define DCU_INTEVTSEL_SEL_OP                           (0x00000001UL)
#define DCU_INTEVTSEL_SEL_LS2_POS                      (1U)
#define DCU_INTEVTSEL_SEL_LS2                          (0x00000002UL)
#define DCU_INTEVTSEL_SEL_EQ2_POS                      (2U)
#define DCU_INTEVTSEL_SEL_EQ2                          (0x00000004UL)
#define DCU_INTEVTSEL_SEL_GT2_POS                      (3U)
#define DCU_INTEVTSEL_SEL_GT2                          (0x00000008UL)
#define DCU_INTEVTSEL_SEL_LS1_POS                      (4U)
#define DCU_INTEVTSEL_SEL_LS1                          (0x00000010UL)
#define DCU_INTEVTSEL_SEL_EQ1_POS                      (5U)
#define DCU_INTEVTSEL_SEL_EQ1                          (0x00000020UL)
#define DCU_INTEVTSEL_SEL_GT1_POS                      (6U)
#define DCU_INTEVTSEL_SEL_GT1                          (0x00000040UL)
#define DCU_INTEVTSEL_SEL_WIN_POS                      (7U)
#define DCU_INTEVTSEL_SEL_WIN                          (0x00000180UL)
#define DCU_INTEVTSEL_SEL_WIN_0                        (0x00000080UL)
#define DCU_INTEVTSEL_SEL_WIN_1                        (0x00000100UL)
#define DCU_INTEVTSEL_SEL_RLD_POS                      (9U)
#define DCU_INTEVTSEL_SEL_RLD                          (0x00000200UL)
#define DCU_INTEVTSEL_SEL_BTM_POS                      (10U)
#define DCU_INTEVTSEL_SEL_BTM                          (0x00000400UL)
#define DCU_INTEVTSEL_SEL_TOP_POS                      (11U)
#define DCU_INTEVTSEL_SEL_TOP                          (0x00000800UL)

/*******************************************************************************
                Bit definition for Peripheral DMA
*******************************************************************************/
/*  Bit definition for DMA_EN register  */
#define DMA_EN_EN                                      (0x00000001UL)

/*  Bit definition for DMA_INTSTAT0 register  */
#define DMA_INTSTAT0_TRNERR_POS                        (0U)
#define DMA_INTSTAT0_TRNERR                            (0x000000FFUL)
#define DMA_INTSTAT0_TRNERR_0                          (0x00000001UL)
#define DMA_INTSTAT0_TRNERR_1                          (0x00000002UL)
#define DMA_INTSTAT0_TRNERR_2                          (0x00000004UL)
#define DMA_INTSTAT0_TRNERR_3                          (0x00000008UL)
#define DMA_INTSTAT0_TRNERR_4                          (0x00000010UL)
#define DMA_INTSTAT0_TRNERR_5                          (0x00000020UL)
#define DMA_INTSTAT0_TRNERR_6                          (0x00000040UL)
#define DMA_INTSTAT0_TRNERR_7                          (0x00000080UL)
#define DMA_INTSTAT0_REQERR_POS                        (16U)
#define DMA_INTSTAT0_REQERR                            (0x00FF0000UL)
#define DMA_INTSTAT0_REQERR_0                          (0x00010000UL)
#define DMA_INTSTAT0_REQERR_1                          (0x00020000UL)
#define DMA_INTSTAT0_REQERR_2                          (0x00040000UL)
#define DMA_INTSTAT0_REQERR_3                          (0x00080000UL)
#define DMA_INTSTAT0_REQERR_4                          (0x00100000UL)
#define DMA_INTSTAT0_REQERR_5                          (0x00200000UL)
#define DMA_INTSTAT0_REQERR_6                          (0x00400000UL)
#define DMA_INTSTAT0_REQERR_7                          (0x00800000UL)

/*  Bit definition for DMA_INTSTAT1 register  */
#define DMA_INTSTAT1_TC_POS                            (0U)
#define DMA_INTSTAT1_TC                                (0x000000FFUL)
#define DMA_INTSTAT1_TC_0                              (0x00000001UL)
#define DMA_INTSTAT1_TC_1                              (0x00000002UL)
#define DMA_INTSTAT1_TC_2                              (0x00000004UL)
#define DMA_INTSTAT1_TC_3                              (0x00000008UL)
#define DMA_INTSTAT1_TC_4                              (0x00000010UL)
#define DMA_INTSTAT1_TC_5                              (0x00000020UL)
#define DMA_INTSTAT1_TC_6                              (0x00000040UL)
#define DMA_INTSTAT1_TC_7                              (0x00000080UL)
#define DMA_INTSTAT1_BTC_POS                           (16U)
#define DMA_INTSTAT1_BTC                               (0x00FF0000UL)
#define DMA_INTSTAT1_BTC_0                             (0x00010000UL)
#define DMA_INTSTAT1_BTC_1                             (0x00020000UL)
#define DMA_INTSTAT1_BTC_2                             (0x00040000UL)
#define DMA_INTSTAT1_BTC_3                             (0x00080000UL)
#define DMA_INTSTAT1_BTC_4                             (0x00100000UL)
#define DMA_INTSTAT1_BTC_5                             (0x00200000UL)
#define DMA_INTSTAT1_BTC_6                             (0x00400000UL)
#define DMA_INTSTAT1_BTC_7                             (0x00800000UL)

/*  Bit definition for DMA_INTMASK0 register  */
#define DMA_INTMASK0_MSKTRNERR_POS                     (0U)
#define DMA_INTMASK0_MSKTRNERR                         (0x000000FFUL)
#define DMA_INTMASK0_MSKTRNERR_0                       (0x00000001UL)
#define DMA_INTMASK0_MSKTRNERR_1                       (0x00000002UL)
#define DMA_INTMASK0_MSKTRNERR_2                       (0x00000004UL)
#define DMA_INTMASK0_MSKTRNERR_3                       (0x00000008UL)
#define DMA_INTMASK0_MSKTRNERR_4                       (0x00000010UL)
#define DMA_INTMASK0_MSKTRNERR_5                       (0x00000020UL)
#define DMA_INTMASK0_MSKTRNERR_6                       (0x00000040UL)
#define DMA_INTMASK0_MSKTRNERR_7                       (0x00000080UL)
#define DMA_INTMASK0_MSKREQERR_POS                     (16U)
#define DMA_INTMASK0_MSKREQERR                         (0x00FF0000UL)
#define DMA_INTMASK0_MSKREQERR_0                       (0x00010000UL)
#define DMA_INTMASK0_MSKREQERR_1                       (0x00020000UL)
#define DMA_INTMASK0_MSKREQERR_2                       (0x00040000UL)
#define DMA_INTMASK0_MSKREQERR_3                       (0x00080000UL)
#define DMA_INTMASK0_MSKREQERR_4                       (0x00100000UL)
#define DMA_INTMASK0_MSKREQERR_5                       (0x00200000UL)
#define DMA_INTMASK0_MSKREQERR_6                       (0x00400000UL)
#define DMA_INTMASK0_MSKREQERR_7                       (0x00800000UL)

/*  Bit definition for DMA_INTMASK1 register  */
#define DMA_INTMASK1_MSKTC_POS                         (0U)
#define DMA_INTMASK1_MSKTC                             (0x000000FFUL)
#define DMA_INTMASK1_MSKTC_0                           (0x00000001UL)
#define DMA_INTMASK1_MSKTC_1                           (0x00000002UL)
#define DMA_INTMASK1_MSKTC_2                           (0x00000004UL)
#define DMA_INTMASK1_MSKTC_3                           (0x00000008UL)
#define DMA_INTMASK1_MSKTC_4                           (0x00000010UL)
#define DMA_INTMASK1_MSKTC_5                           (0x00000020UL)
#define DMA_INTMASK1_MSKTC_6                           (0x00000040UL)
#define DMA_INTMASK1_MSKTC_7                           (0x00000080UL)
#define DMA_INTMASK1_MSKBTC_POS                        (16U)
#define DMA_INTMASK1_MSKBTC                            (0x00FF0000UL)
#define DMA_INTMASK1_MSKBTC_0                          (0x00010000UL)
#define DMA_INTMASK1_MSKBTC_1                          (0x00020000UL)
#define DMA_INTMASK1_MSKBTC_2                          (0x00040000UL)
#define DMA_INTMASK1_MSKBTC_3                          (0x00080000UL)
#define DMA_INTMASK1_MSKBTC_4                          (0x00100000UL)
#define DMA_INTMASK1_MSKBTC_5                          (0x00200000UL)
#define DMA_INTMASK1_MSKBTC_6                          (0x00400000UL)
#define DMA_INTMASK1_MSKBTC_7                          (0x00800000UL)

/*  Bit definition for DMA_INTCLR0 register  */
#define DMA_INTCLR0_CLRTRNERR_POS                      (0U)
#define DMA_INTCLR0_CLRTRNERR                          (0x000000FFUL)
#define DMA_INTCLR0_CLRTRNERR_0                        (0x00000001UL)
#define DMA_INTCLR0_CLRTRNERR_1                        (0x00000002UL)
#define DMA_INTCLR0_CLRTRNERR_2                        (0x00000004UL)
#define DMA_INTCLR0_CLRTRNERR_3                        (0x00000008UL)
#define DMA_INTCLR0_CLRTRNERR_4                        (0x00000010UL)
#define DMA_INTCLR0_CLRTRNERR_5                        (0x00000020UL)
#define DMA_INTCLR0_CLRTRNERR_6                        (0x00000040UL)
#define DMA_INTCLR0_CLRTRNERR_7                        (0x00000080UL)
#define DMA_INTCLR0_CLRREQERR_POS                      (16U)
#define DMA_INTCLR0_CLRREQERR                          (0x00FF0000UL)
#define DMA_INTCLR0_CLRREQERR_0                        (0x00010000UL)
#define DMA_INTCLR0_CLRREQERR_1                        (0x00020000UL)
#define DMA_INTCLR0_CLRREQERR_2                        (0x00040000UL)
#define DMA_INTCLR0_CLRREQERR_3                        (0x00080000UL)
#define DMA_INTCLR0_CLRREQERR_4                        (0x00100000UL)
#define DMA_INTCLR0_CLRREQERR_5                        (0x00200000UL)
#define DMA_INTCLR0_CLRREQERR_6                        (0x00400000UL)
#define DMA_INTCLR0_CLRREQERR_7                        (0x00800000UL)

/*  Bit definition for DMA_INTCLR1 register  */
#define DMA_INTCLR1_CLRTC_POS                          (0U)
#define DMA_INTCLR1_CLRTC                              (0x000000FFUL)
#define DMA_INTCLR1_CLRTC_0                            (0x00000001UL)
#define DMA_INTCLR1_CLRTC_1                            (0x00000002UL)
#define DMA_INTCLR1_CLRTC_2                            (0x00000004UL)
#define DMA_INTCLR1_CLRTC_3                            (0x00000008UL)
#define DMA_INTCLR1_CLRTC_4                            (0x00000010UL)
#define DMA_INTCLR1_CLRTC_5                            (0x00000020UL)
#define DMA_INTCLR1_CLRTC_6                            (0x00000040UL)
#define DMA_INTCLR1_CLRTC_7                            (0x00000080UL)
#define DMA_INTCLR1_CLRBTC_POS                         (16U)
#define DMA_INTCLR1_CLRBTC                             (0x00FF0000UL)
#define DMA_INTCLR1_CLRBTC_0                           (0x00010000UL)
#define DMA_INTCLR1_CLRBTC_1                           (0x00020000UL)
#define DMA_INTCLR1_CLRBTC_2                           (0x00040000UL)
#define DMA_INTCLR1_CLRBTC_3                           (0x00080000UL)
#define DMA_INTCLR1_CLRBTC_4                           (0x00100000UL)
#define DMA_INTCLR1_CLRBTC_5                           (0x00200000UL)
#define DMA_INTCLR1_CLRBTC_6                           (0x00400000UL)
#define DMA_INTCLR1_CLRBTC_7                           (0x00800000UL)

/*  Bit definition for DMA_CHEN register  */
#define DMA_CHEN_CHEN                                  (0x000000FFUL)
#define DMA_CHEN_CHEN_0                                (0x00000001UL)
#define DMA_CHEN_CHEN_1                                (0x00000002UL)
#define DMA_CHEN_CHEN_2                                (0x00000004UL)
#define DMA_CHEN_CHEN_3                                (0x00000008UL)
#define DMA_CHEN_CHEN_4                                (0x00000010UL)
#define DMA_CHEN_CHEN_5                                (0x00000020UL)
#define DMA_CHEN_CHEN_6                                (0x00000040UL)
#define DMA_CHEN_CHEN_7                                (0x00000080UL)

/*  Bit definition for DMA_REQSTAT register  */
#define DMA_REQSTAT_CHREQ_POS                          (0U)
#define DMA_REQSTAT_CHREQ                              (0x000000FFUL)
#define DMA_REQSTAT_CHREQ_0                            (0x00000001UL)
#define DMA_REQSTAT_CHREQ_1                            (0x00000002UL)
#define DMA_REQSTAT_CHREQ_2                            (0x00000004UL)
#define DMA_REQSTAT_CHREQ_3                            (0x00000008UL)
#define DMA_REQSTAT_CHREQ_4                            (0x00000010UL)
#define DMA_REQSTAT_CHREQ_5                            (0x00000020UL)
#define DMA_REQSTAT_CHREQ_6                            (0x00000040UL)
#define DMA_REQSTAT_CHREQ_7                            (0x00000080UL)
#define DMA_REQSTAT_RCFGREQ_POS                        (15U)
#define DMA_REQSTAT_RCFGREQ                            (0x00008000UL)

/*  Bit definition for DMA_CHSTAT register  */
#define DMA_CHSTAT_DMAACT_POS                          (0U)
#define DMA_CHSTAT_DMAACT                              (0x00000001UL)
#define DMA_CHSTAT_RCFGACT_POS                         (1U)
#define DMA_CHSTAT_RCFGACT                             (0x00000002UL)
#define DMA_CHSTAT_CHACT_POS                           (16U)
#define DMA_CHSTAT_CHACT                               (0x00FF0000UL)
#define DMA_CHSTAT_CHACT_0                             (0x00010000UL)
#define DMA_CHSTAT_CHACT_1                             (0x00020000UL)
#define DMA_CHSTAT_CHACT_2                             (0x00040000UL)
#define DMA_CHSTAT_CHACT_3                             (0x00080000UL)
#define DMA_CHSTAT_CHACT_4                             (0x00100000UL)
#define DMA_CHSTAT_CHACT_5                             (0x00200000UL)
#define DMA_CHSTAT_CHACT_6                             (0x00400000UL)
#define DMA_CHSTAT_CHACT_7                             (0x00800000UL)

/*  Bit definition for DMA_RCFGCTL register  */
#define DMA_RCFGCTL_RCFGEN_POS                         (0U)
#define DMA_RCFGCTL_RCFGEN                             (0x00000001UL)
#define DMA_RCFGCTL_RCFGLLP_POS                        (1U)
#define DMA_RCFGCTL_RCFGLLP                            (0x00000002UL)
#define DMA_RCFGCTL_RCFGCHS_POS                        (8U)
#define DMA_RCFGCTL_RCFGCHS                            (0x00000F00UL)
#define DMA_RCFGCTL_SARMD_POS                          (16U)
#define DMA_RCFGCTL_SARMD                              (0x00030000UL)
#define DMA_RCFGCTL_SARMD_0                            (0x00010000UL)
#define DMA_RCFGCTL_SARMD_1                            (0x00020000UL)
#define DMA_RCFGCTL_DARMD_POS                          (18U)
#define DMA_RCFGCTL_DARMD                              (0x000C0000UL)
#define DMA_RCFGCTL_DARMD_0                            (0x00040000UL)
#define DMA_RCFGCTL_DARMD_1                            (0x00080000UL)
#define DMA_RCFGCTL_CNTMD_POS                          (20U)
#define DMA_RCFGCTL_CNTMD                              (0x00300000UL)
#define DMA_RCFGCTL_CNTMD_0                            (0x00100000UL)
#define DMA_RCFGCTL_CNTMD_1                            (0x00200000UL)

/*  Bit definition for DMA_CHENCLR register  */
#define DMA_CHENCLR_CHENCLR                            (0x000000FFUL)
#define DMA_CHENCLR_CHENCLR_0                          (0x00000001UL)
#define DMA_CHENCLR_CHENCLR_1                          (0x00000002UL)
#define DMA_CHENCLR_CHENCLR_2                          (0x00000004UL)
#define DMA_CHENCLR_CHENCLR_3                          (0x00000008UL)
#define DMA_CHENCLR_CHENCLR_4                          (0x00000010UL)
#define DMA_CHENCLR_CHENCLR_5                          (0x00000020UL)
#define DMA_CHENCLR_CHENCLR_6                          (0x00000040UL)
#define DMA_CHENCLR_CHENCLR_7                          (0x00000080UL)

/*  Bit definition for DMA_SAR register  */
#define DMA_SAR                                        (0xFFFFFFFFUL)

/*  Bit definition for DMA_DAR register  */
#define DMA_DAR                                        (0xFFFFFFFFUL)

/*  Bit definition for DMA_DTCTL register  */
#define DMA_DTCTL_BLKSIZE_POS                          (0U)
#define DMA_DTCTL_BLKSIZE                              (0x000003FFUL)
#define DMA_DTCTL_CNT_POS                              (16U)
#define DMA_DTCTL_CNT                                  (0xFFFF0000UL)

/*  Bit definition for DMA_RPT register  */
#define DMA_RPT_SRPT_POS                               (0U)
#define DMA_RPT_SRPT                                   (0x000003FFUL)
#define DMA_RPT_DRPT_POS                               (16U)
#define DMA_RPT_DRPT                                   (0x03FF0000UL)

/*  Bit definition for DMA_RPTB register  */
#define DMA_RPTB_SRPTB_POS                             (0U)
#define DMA_RPTB_SRPTB                                 (0x000003FFUL)
#define DMA_RPTB_DRPTB_POS                             (16U)
#define DMA_RPTB_DRPTB                                 (0x03FF0000UL)

/*  Bit definition for DMA_SNSEQCTL register  */
#define DMA_SNSEQCTL_SOFFSET_POS                       (0U)
#define DMA_SNSEQCTL_SOFFSET                           (0x000FFFFFUL)
#define DMA_SNSEQCTL_SNSCNT_POS                        (20U)
#define DMA_SNSEQCTL_SNSCNT                            (0xFFF00000UL)

/*  Bit definition for DMA_SNSEQCTLB register  */
#define DMA_SNSEQCTLB_SNSDIST_POS                      (0U)
#define DMA_SNSEQCTLB_SNSDIST                          (0x000FFFFFUL)
#define DMA_SNSEQCTLB_SNSCNTB_POS                      (20U)
#define DMA_SNSEQCTLB_SNSCNTB                          (0xFFF00000UL)

/*  Bit definition for DMA_DNSEQCTL register  */
#define DMA_DNSEQCTL_DOFFSET_POS                       (0U)
#define DMA_DNSEQCTL_DOFFSET                           (0x000FFFFFUL)
#define DMA_DNSEQCTL_DNSCNT_POS                        (20U)
#define DMA_DNSEQCTL_DNSCNT                            (0xFFF00000UL)

/*  Bit definition for DMA_DNSEQCTLB register  */
#define DMA_DNSEQCTLB_DNSDIST_POS                      (0U)
#define DMA_DNSEQCTLB_DNSDIST                          (0x000FFFFFUL)
#define DMA_DNSEQCTLB_DNSCNTB_POS                      (20U)
#define DMA_DNSEQCTLB_DNSCNTB                          (0xFFF00000UL)

/*  Bit definition for DMA_LLP register  */
#define DMA_LLP_LLP_POS                                (2U)
#define DMA_LLP_LLP                                    (0xFFFFFFFCUL)

/*  Bit definition for DMA_CHCTL register  */
#define DMA_CHCTL_SINC_POS                             (0U)
#define DMA_CHCTL_SINC                                 (0x00000003UL)
#define DMA_CHCTL_SINC_0                               (0x00000001UL)
#define DMA_CHCTL_SINC_1                               (0x00000002UL)
#define DMA_CHCTL_DINC_POS                             (2U)
#define DMA_CHCTL_DINC                                 (0x0000000CUL)
#define DMA_CHCTL_DINC_0                               (0x00000004UL)
#define DMA_CHCTL_DINC_1                               (0x00000008UL)
#define DMA_CHCTL_SRPTEN_POS                           (4U)
#define DMA_CHCTL_SRPTEN                               (0x00000010UL)
#define DMA_CHCTL_DRPTEN_POS                           (5U)
#define DMA_CHCTL_DRPTEN                               (0x00000020UL)
#define DMA_CHCTL_SNSEQEN_POS                          (6U)
#define DMA_CHCTL_SNSEQEN                              (0x00000040UL)
#define DMA_CHCTL_DNSEQEN_POS                          (7U)
#define DMA_CHCTL_DNSEQEN                              (0x00000080UL)
#define DMA_CHCTL_HSIZE_POS                            (8U)
#define DMA_CHCTL_HSIZE                                (0x00000300UL)
#define DMA_CHCTL_HSIZE_0                              (0x00000100UL)
#define DMA_CHCTL_HSIZE_1                              (0x00000200UL)
#define DMA_CHCTL_LLPEN_POS                            (10U)
#define DMA_CHCTL_LLPEN                                (0x00000400UL)
#define DMA_CHCTL_LLPRUN_POS                           (11U)
#define DMA_CHCTL_LLPRUN                               (0x00000800UL)
#define DMA_CHCTL_IE_POS                               (12U)
#define DMA_CHCTL_IE                                   (0x00001000UL)

/*  Bit definition for DMA_MONSAR register  */
#define DMA_MONSAR                                     (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONDAR register  */
#define DMA_MONDAR                                     (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONDTCTL register  */
#define DMA_MONDTCTL_BLKSIZE_POS                       (0U)
#define DMA_MONDTCTL_BLKSIZE                           (0x000003FFUL)
#define DMA_MONDTCTL_CNT_POS                           (16U)
#define DMA_MONDTCTL_CNT                               (0xFFFF0000UL)

/*  Bit definition for DMA_MONRPT register  */
#define DMA_MONRPT_SRPT_POS                            (0U)
#define DMA_MONRPT_SRPT                                (0x000003FFUL)
#define DMA_MONRPT_DRPT_POS                            (16U)
#define DMA_MONRPT_DRPT                                (0x03FF0000UL)

/*  Bit definition for DMA_MONSNSEQCTL register  */
#define DMA_MONSNSEQCTL_SOFFSET_POS                    (0U)
#define DMA_MONSNSEQCTL_SOFFSET                        (0x000FFFFFUL)
#define DMA_MONSNSEQCTL_SNSCNT_POS                     (20U)
#define DMA_MONSNSEQCTL_SNSCNT                         (0xFFF00000UL)

/*  Bit definition for DMA_MONDNSEQCTL register  */
#define DMA_MONDNSEQCTL_DOFFSET_POS                    (0U)
#define DMA_MONDNSEQCTL_DOFFSET                        (0x000FFFFFUL)
#define DMA_MONDNSEQCTL_DNSCNT_POS                     (20U)
#define DMA_MONDNSEQCTL_DNSCNT                         (0xFFF00000UL)

/*******************************************************************************
                Bit definition for Peripheral DMC
*******************************************************************************/
/*  Bit definition for DMC_STSR register  */
#define DMC_STSR_STATUS_POS                            (0U)
#define DMC_STSR_STATUS                                (0x00000003UL)
#define DMC_STSR_STATUS_0                              (0x00000001UL)
#define DMC_STSR_STATUS_1                              (0x00000002UL)
#define DMC_STSR_MEMW_POS                              (2U)
#define DMC_STSR_MEMW                                  (0x0000000CUL)
#define DMC_STSR_MEMW_0                                (0x00000004UL)
#define DMC_STSR_MEMW_1                                (0x00000008UL)

/*  Bit definition for DMC_STCR register  */
#define DMC_STCR_STCTL                                 (0x00000007UL)
#define DMC_STCR_STCTL_0                               (0x00000001UL)
#define DMC_STCR_STCTL_1                               (0x00000002UL)
#define DMC_STCR_STCTL_2                               (0x00000004UL)

/*  Bit definition for DMC_CMDR register  */
#define DMC_CMDR_CMDADD_POS                            (0U)
#define DMC_CMDR_CMDADD                                (0x00003FFFUL)
#define DMC_CMDR_CMDBA_POS                             (16U)
#define DMC_CMDR_CMDBA                                 (0x00030000UL)
#define DMC_CMDR_CMDBA_0                               (0x00010000UL)
#define DMC_CMDR_CMDBA_1                               (0x00020000UL)
#define DMC_CMDR_CMD_POS                               (18U)
#define DMC_CMDR_CMD                                   (0x000C0000UL)
#define DMC_CMDR_CMD_0                                 (0x00040000UL)
#define DMC_CMDR_CMD_1                                 (0x00080000UL)
#define DMC_CMDR_CMDCHIP_POS                           (20U)
#define DMC_CMDR_CMDCHIP                               (0x00300000UL)
#define DMC_CMDR_CMDCHIP_0                             (0x00100000UL)
#define DMC_CMDR_CMDCHIP_1                             (0x00200000UL)

/*  Bit definition for DMC_CPCR register  */
#define DMC_CPCR_COLBS_POS                             (0U)
#define DMC_CPCR_COLBS                                 (0x00000007UL)
#define DMC_CPCR_ROWBS_POS                             (4U)
#define DMC_CPCR_ROWBS                                 (0x00000070UL)
#define DMC_CPCR_APBS_POS                              (7U)
#define DMC_CPCR_APBS                                  (0x00000080UL)
#define DMC_CPCR_CKEDIS_POS                            (8U)
#define DMC_CPCR_CKEDIS                                (0x00000100UL)
#define DMC_CPCR_CKSTOP_POS                            (9U)
#define DMC_CPCR_CKSTOP                                (0x00000200UL)
#define DMC_CPCR_CKEDISPRD_POS                         (10U)
#define DMC_CPCR_CKEDISPRD                             (0x0000FC00UL)
#define DMC_CPCR_BURST_POS                             (16U)
#define DMC_CPCR_BURST                                 (0x00070000UL)
#define DMC_CPCR_ACTCP_POS                             (24U)
#define DMC_CPCR_ACTCP                                 (0x03000000UL)
#define DMC_CPCR_ACTCP_0                               (0x01000000UL)
#define DMC_CPCR_ACTCP_1                               (0x02000000UL)

/*  Bit definition for DMC_RFTR register  */
#define DMC_RFTR_REFPRD                                (0x00007FFFUL)

/*  Bit definition for DMC_TMCR_T_CASL register  */
#define DMC_TMCR_T_CASL_T_CASL                         (0x00000007UL)

/*  Bit definition for DMC_TMCR_T_DQSS register  */
#define DMC_TMCR_T_DQSS_T_DQSS                         (0x00000003UL)

/*  Bit definition for DMC_TMCR_T_MRD register  */
#define DMC_TMCR_T_MRD_T_MRD                           (0x0000007FUL)

/*  Bit definition for DMC_TMCR_T_RAS register  */
#define DMC_TMCR_T_RAS_T_RAS                           (0x0000000FUL)

/*  Bit definition for DMC_TMCR_T_RC register  */
#define DMC_TMCR_T_RC_T_RC                             (0x0000000FUL)

/*  Bit definition for DMC_TMCR_T_RCD register  */
#define DMC_TMCR_T_RCD_T_RCD_B_POS                     (0U)
#define DMC_TMCR_T_RCD_T_RCD_B                         (0x00000007UL)
#define DMC_TMCR_T_RCD_T_RCD_P_POS                     (4U)
#define DMC_TMCR_T_RCD_T_RCD_P                         (0x00000070UL)

/*  Bit definition for DMC_TMCR_T_RFC register  */
#define DMC_TMCR_T_RFC_T_RFC_B_POS                     (0U)
#define DMC_TMCR_T_RFC_T_RFC_B                         (0x0000001FUL)
#define DMC_TMCR_T_RFC_T_RFC_P_POS                     (8U)
#define DMC_TMCR_T_RFC_T_RFC_P                         (0x00001F00UL)

/*  Bit definition for DMC_TMCR_T_RP register  */
#define DMC_TMCR_T_RP_T_RP_B_POS                       (0U)
#define DMC_TMCR_T_RP_T_RP_B                           (0x00000007UL)
#define DMC_TMCR_T_RP_T_RP_P_POS                       (4U)
#define DMC_TMCR_T_RP_T_RP_P                           (0x00000070UL)

/*  Bit definition for DMC_TMCR_T_RRD register  */
#define DMC_TMCR_T_RRD_T_RRD                           (0x0000000FUL)

/*  Bit definition for DMC_TMCR_T_WR register  */
#define DMC_TMCR_T_WR_T_WR                             (0x00000007UL)

/*  Bit definition for DMC_TMCR_T_WTR register  */
#define DMC_TMCR_T_WTR_T_WTR                           (0x00000007UL)

/*  Bit definition for DMC_TMCR_T_XP register  */
#define DMC_TMCR_T_XP_T_XP                             (0x000000FFUL)

/*  Bit definition for DMC_TMCR_T_XSR register  */
#define DMC_TMCR_T_XSR_T_XSR                           (0x000000FFUL)

/*  Bit definition for DMC_TMCR_T_ESR register  */
#define DMC_TMCR_T_ESR_T_ESR                           (0x000000FFUL)

/*  Bit definition for DMC_CSCR register  */
#define DMC_CSCR_ADDMSK_POS                            (0U)
#define DMC_CSCR_ADDMSK                                (0x000000FFUL)
#define DMC_CSCR_ADDMAT_POS                            (8U)
#define DMC_CSCR_ADDMAT                                (0x0000FF00UL)
#define DMC_CSCR_BRC_POS                               (16U)
#define DMC_CSCR_BRC                                   (0x00010000UL)

/*  Bit definition for DMC_BACR register  */
#define DMC_BACR_DMCMW_POS                             (0U)
#define DMC_BACR_DMCMW                                 (0x00000003UL)
#define DMC_BACR_DMCMW_0                               (0x00000001UL)
#define DMC_BACR_DMCMW_1                               (0x00000002UL)
#define DMC_BACR_CKSEL_POS                             (14U)
#define DMC_BACR_CKSEL                                 (0x0000C000UL)
#define DMC_BACR_CKSEL_0                               (0x00004000UL)
#define DMC_BACR_CKSEL_1                               (0x00008000UL)

/*******************************************************************************
                Bit definition for Peripheral DVP
*******************************************************************************/
/*  Bit definition for DVP_CTR register  */
#define DVP_CTR_CAPEN_POS                              (0U)
#define DVP_CTR_CAPEN                                  (0x00000001UL)
#define DVP_CTR_CAPMD_POS                              (1U)
#define DVP_CTR_CAPMD                                  (0x00000002UL)
#define DVP_CTR_CROPEN_POS                             (2U)
#define DVP_CTR_CROPEN                                 (0x00000004UL)
#define DVP_CTR_JPEGEN_POS                             (3U)
#define DVP_CTR_JPEGEN                                 (0x00000008UL)
#define DVP_CTR_SWSYNC_POS                             (4U)
#define DVP_CTR_SWSYNC                                 (0x00000010UL)
#define DVP_CTR_PIXCKSEL_POS                           (5U)
#define DVP_CTR_PIXCKSEL                               (0x00000020UL)
#define DVP_CTR_HSYNCSEL_POS                           (6U)
#define DVP_CTR_HSYNCSEL                               (0x00000040UL)
#define DVP_CTR_VSYNCSEL_POS                           (7U)
#define DVP_CTR_VSYNCSEL                               (0x00000080UL)
#define DVP_CTR_CAPFRC_POS                             (8U)
#define DVP_CTR_CAPFRC                                 (0x00000300UL)
#define DVP_CTR_CAPFRC_0                               (0x00000100UL)
#define DVP_CTR_CAPFRC_1                               (0x00000200UL)
#define DVP_CTR_BITSEL_POS                             (10U)
#define DVP_CTR_BITSEL                                 (0x00000C00UL)
#define DVP_CTR_BITSEL_0                               (0x00000400UL)
#define DVP_CTR_BITSEL_1                               (0x00000800UL)
#define DVP_CTR_DVPEN_POS                              (14U)
#define DVP_CTR_DVPEN                                  (0x00004000UL)

/*  Bit definition for DVP_DTR register  */
#define DVP_DTR                                        (0xFFFFFFFFUL)

/*  Bit definition for DVP_STR register  */
#define DVP_STR_FSF_POS                                (0U)
#define DVP_STR_FSF                                    (0x00000001UL)
#define DVP_STR_LSF_POS                                (1U)
#define DVP_STR_LSF                                    (0x00000002UL)
#define DVP_STR_LEF_POS                                (2U)
#define DVP_STR_LEF                                    (0x00000004UL)
#define DVP_STR_FEF_POS                                (3U)
#define DVP_STR_FEF                                    (0x00000008UL)
#define DVP_STR_SQUERF_POS                             (4U)
#define DVP_STR_SQUERF                                 (0x00000010UL)
#define DVP_STR_FIFOERF_POS                            (5U)
#define DVP_STR_FIFOERF                                (0x00000020UL)

/*  Bit definition for DVP_IER register  */
#define DVP_IER_FSIEN_POS                              (0U)
#define DVP_IER_FSIEN                                  (0x00000001UL)
#define DVP_IER_LSIEN_POS                              (1U)
#define DVP_IER_LSIEN                                  (0x00000002UL)
#define DVP_IER_LEIEN_POS                              (2U)
#define DVP_IER_LEIEN                                  (0x00000004UL)
#define DVP_IER_FEIEN_POS                              (3U)
#define DVP_IER_FEIEN                                  (0x00000008UL)
#define DVP_IER_SQUERIEN_POS                           (4U)
#define DVP_IER_SQUERIEN                               (0x00000010UL)
#define DVP_IER_FIFOERIEN_POS                          (5U)
#define DVP_IER_FIFOERIEN                              (0x00000020UL)

/*  Bit definition for DVP_DMR register  */
#define DVP_DMR                                        (0xFFFFFFFFUL)

/*  Bit definition for DVP_SSYNDR register  */
#define DVP_SSYNDR_FSDAT_POS                           (0U)
#define DVP_SSYNDR_FSDAT                               (0x000000FFUL)
#define DVP_SSYNDR_LSDAT_POS                           (8U)
#define DVP_SSYNDR_LSDAT                               (0x0000FF00UL)
#define DVP_SSYNDR_LEDAT_POS                           (16U)
#define DVP_SSYNDR_LEDAT                               (0x00FF0000UL)
#define DVP_SSYNDR_FEDAT_POS                           (24U)
#define DVP_SSYNDR_FEDAT                               (0xFF000000UL)

/*  Bit definition for DVP_SSYNMR register  */
#define DVP_SSYNMR_FSMSK_POS                           (0U)
#define DVP_SSYNMR_FSMSK                               (0x000000FFUL)
#define DVP_SSYNMR_LSMSK_POS                           (8U)
#define DVP_SSYNMR_LSMSK                               (0x0000FF00UL)
#define DVP_SSYNMR_LEMSK_POS                           (16U)
#define DVP_SSYNMR_LEMSK                               (0x00FF0000UL)
#define DVP_SSYNMR_FEMSK_POS                           (24U)
#define DVP_SSYNMR_FEMSK                               (0xFF000000UL)

/*  Bit definition for DVP_CPSFTR register  */
#define DVP_CPSFTR_RSHIFT_POS                          (0U)
#define DVP_CPSFTR_RSHIFT                              (0x00003FFFUL)
#define DVP_CPSFTR_CSHIFT_POS                          (16U)
#define DVP_CPSFTR_CSHIFT                              (0x3FFF0000UL)

/*  Bit definition for DVP_CPSZER register  */
#define DVP_CPSZER_RSIZE_POS                           (0U)
#define DVP_CPSZER_RSIZE                               (0x00003FFFUL)
#define DVP_CPSZER_CSIZE_POS                           (16U)
#define DVP_CPSZER_CSIZE                               (0x3FFF0000UL)

/*******************************************************************************
                Bit definition for Peripheral EFM
*******************************************************************************/
/*  Bit definition for EFM_FAPRT register  */
#define EFM_FAPRT_FAPRT                                (0x0000FFFFUL)

/*  Bit definition for EFM_KEY1 register  */
#define EFM_KEY1                                       (0xFFFFFFFFUL)

/*  Bit definition for EFM_KEY2 register  */
#define EFM_KEY2                                       (0xFFFFFFFFUL)

/*  Bit definition for EFM_FSTP register  */
#define EFM_FSTP_F0STP_POS                             (0U)
#define EFM_FSTP_F0STP                                 (0x00000001UL)
#define EFM_FSTP_F1STP_POS                             (1U)
#define EFM_FSTP_F1STP                                 (0x00000002UL)

/*  Bit definition for EFM_FRMC register  */
#define EFM_FRMC_FLWT_POS                              (0U)
#define EFM_FRMC_FLWT                                  (0x0000000FUL)
#define EFM_FRMC_LVM_POS                               (8U)
#define EFM_FRMC_LVM                                   (0x00000100UL)
#define EFM_FRMC_ICACHE_POS                            (16U)
#define EFM_FRMC_ICACHE                                (0x00010000UL)
#define EFM_FRMC_DCACHE_POS                            (17U)
#define EFM_FRMC_DCACHE                                (0x00020000UL)
#define EFM_FRMC_PREFETE_POS                           (18U)
#define EFM_FRMC_PREFETE                               (0x00040000UL)
#define EFM_FRMC_CRST_POS                              (19U)
#define EFM_FRMC_CRST                                  (0x00080000UL)

/*  Bit definition for EFM_FWMC register  */
#define EFM_FWMC_PEMOD_POS                             (0U)
#define EFM_FWMC_PEMOD                                 (0x00000007UL)
#define EFM_FWMC_BUSHLDCTL_POS                         (8U)
#define EFM_FWMC_BUSHLDCTL                             (0x00000100UL)
#define EFM_FWMC_KEY1LOCK_POS                          (16U)
#define EFM_FWMC_KEY1LOCK                              (0x00010000UL)
#define EFM_FWMC_KEY2LOCK_POS                          (17U)
#define EFM_FWMC_KEY2LOCK                              (0x00020000UL)

/*  Bit definition for EFM_FSR register  */
#define EFM_FSR_OTPWERR0_POS                           (0U)
#define EFM_FSR_OTPWERR0                               (0x00000001UL)
#define EFM_FSR_PRTWERR0_POS                           (1U)
#define EFM_FSR_PRTWERR0                               (0x00000002UL)
#define EFM_FSR_PGSZERR0_POS                           (2U)
#define EFM_FSR_PGSZERR0                               (0x00000004UL)
#define EFM_FSR_MISMTCH0_POS                           (3U)
#define EFM_FSR_MISMTCH0                               (0x00000008UL)
#define EFM_FSR_OPTEND0_POS                            (4U)
#define EFM_FSR_OPTEND0                                (0x00000010UL)
#define EFM_FSR_COLERR0_POS                            (5U)
#define EFM_FSR_COLERR0                                (0x00000020UL)
#define EFM_FSR_RDY0_POS                               (8U)
#define EFM_FSR_RDY0                                   (0x00000100UL)
#define EFM_FSR_PRTWERR1_POS                           (17U)
#define EFM_FSR_PRTWERR1                               (0x00020000UL)
#define EFM_FSR_PGSZERR1_POS                           (18U)
#define EFM_FSR_PGSZERR1                               (0x00040000UL)
#define EFM_FSR_MISMTCH1_POS                           (19U)
#define EFM_FSR_MISMTCH1                               (0x00080000UL)
#define EFM_FSR_OPTEND1_POS                            (20U)
#define EFM_FSR_OPTEND1                                (0x00100000UL)
#define EFM_FSR_COLERR1_POS                            (21U)
#define EFM_FSR_COLERR1                                (0x00200000UL)
#define EFM_FSR_RDY1_POS                               (24U)
#define EFM_FSR_RDY1                                   (0x01000000UL)

/*  Bit definition for EFM_FSCLR register  */
#define EFM_FSCLR_OTPWERRCLR0_POS                      (0U)
#define EFM_FSCLR_OTPWERRCLR0                          (0x00000001UL)
#define EFM_FSCLR_PRTWERRCLR0_POS                      (1U)
#define EFM_FSCLR_PRTWERRCLR0                          (0x00000002UL)
#define EFM_FSCLR_PGSZERRCLR0_POS                      (2U)
#define EFM_FSCLR_PGSZERRCLR0                          (0x00000004UL)
#define EFM_FSCLR_MISMTCHCLR0_POS                      (3U)
#define EFM_FSCLR_MISMTCHCLR0                          (0x00000008UL)
#define EFM_FSCLR_OPTENDCLR0_POS                       (4U)
#define EFM_FSCLR_OPTENDCLR0                           (0x00000010UL)
#define EFM_FSCLR_COLERRCLR0_POS                       (5U)
#define EFM_FSCLR_COLERRCLR0                           (0x00000020UL)
#define EFM_FSCLR_PRTWERRCLR1_POS                      (17U)
#define EFM_FSCLR_PRTWERRCLR1                          (0x00020000UL)
#define EFM_FSCLR_PGSZERRCLR1_POS                      (18U)
#define EFM_FSCLR_PGSZERRCLR1                          (0x00040000UL)
#define EFM_FSCLR_MISMTCHCLR1_POS                      (19U)
#define EFM_FSCLR_MISMTCHCLR1                          (0x00080000UL)
#define EFM_FSCLR_OPTENDCLR1_POS                       (20U)
#define EFM_FSCLR_OPTENDCLR1                           (0x00100000UL)
#define EFM_FSCLR_COLERRCLR1_POS                       (21U)
#define EFM_FSCLR_COLERRCLR1                           (0x00200000UL)

/*  Bit definition for EFM_FITE register  */
#define EFM_FITE_PEERRITE_POS                          (0U)
#define EFM_FITE_PEERRITE                              (0x00000001UL)
#define EFM_FITE_OPTENDITE_POS                         (1U)
#define EFM_FITE_OPTENDITE                             (0x00000002UL)
#define EFM_FITE_COLERRITE_POS                         (2U)
#define EFM_FITE_COLERRITE                             (0x00000004UL)

/*  Bit definition for EFM_FSWP register  */
#define EFM_FSWP_FSWP                                  (0x00000001UL)

/*  Bit definition for EFM_CHIPID register  */
#define EFM_CHIPID                                     (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID0 register  */
#define EFM_UQID0                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID1 register  */
#define EFM_UQID1                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID2 register  */
#define EFM_UQID2                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_MMF_REMPRT register  */
#define EFM_MMF_REMPRT_MMF_REMPRT                      (0x0000FFFFUL)

/*  Bit definition for EFM_MMF_REMCR register  */
#define EFM_MMF_REMCR_RMSIZE_POS                       (0U)
#define EFM_MMF_REMCR_RMSIZE                           (0x0000001FUL)
#define EFM_MMF_REMCR_RMTADDR_POS                      (12U)
#define EFM_MMF_REMCR_RMTADDR                          (0x1FFFF000UL)
#define EFM_MMF_REMCR_EN_POS                           (31U)
#define EFM_MMF_REMCR_EN                               (0x80000000UL)

/*  Bit definition for EFM_WLOCK register  */
#define EFM_WLOCK_WLOCK                                (0x000000FFUL)
#define EFM_WLOCK_WLOCK_0                              (0x00000001UL)
#define EFM_WLOCK_WLOCK_1                              (0x00000002UL)
#define EFM_WLOCK_WLOCK_2                              (0x00000004UL)
#define EFM_WLOCK_WLOCK_3                              (0x00000008UL)
#define EFM_WLOCK_WLOCK_4                              (0x00000010UL)
#define EFM_WLOCK_WLOCK_5                              (0x00000020UL)
#define EFM_WLOCK_WLOCK_6                              (0x00000040UL)
#define EFM_WLOCK_WLOCK_7                              (0x00000080UL)

/*  Bit definition for EFM_F0NWPRT0 register  */
#define EFM_F0NWPRT0_F0NWPRT0_POS                      (0U)
#define EFM_F0NWPRT0_F0NWPRT0                          (0x00000001UL)
#define EFM_F0NWPRT0_F0NWPRT1_POS                      (1U)
#define EFM_F0NWPRT0_F0NWPRT1                          (0x00000002UL)
#define EFM_F0NWPRT0_F0NWPRT2_POS                      (2U)
#define EFM_F0NWPRT0_F0NWPRT2                          (0x00000004UL)
#define EFM_F0NWPRT0_F0NWPRT3_POS                      (3U)
#define EFM_F0NWPRT0_F0NWPRT3                          (0x00000008UL)
#define EFM_F0NWPRT0_F0NWPRT4_POS                      (4U)
#define EFM_F0NWPRT0_F0NWPRT4                          (0x00000010UL)
#define EFM_F0NWPRT0_F0NWPRT5_POS                      (5U)
#define EFM_F0NWPRT0_F0NWPRT5                          (0x00000020UL)
#define EFM_F0NWPRT0_F0NWPRT6_POS                      (6U)
#define EFM_F0NWPRT0_F0NWPRT6                          (0x00000040UL)
#define EFM_F0NWPRT0_F0NWPRT7_POS                      (7U)
#define EFM_F0NWPRT0_F0NWPRT7                          (0x00000080UL)
#define EFM_F0NWPRT0_F0NWPRT8_POS                      (8U)
#define EFM_F0NWPRT0_F0NWPRT8                          (0x00000100UL)
#define EFM_F0NWPRT0_F0NWPRT9_POS                      (9U)
#define EFM_F0NWPRT0_F0NWPRT9                          (0x00000200UL)
#define EFM_F0NWPRT0_F0NWPRT10_POS                     (10U)
#define EFM_F0NWPRT0_F0NWPRT10                         (0x00000400UL)
#define EFM_F0NWPRT0_F0NWPRT11_POS                     (11U)
#define EFM_F0NWPRT0_F0NWPRT11                         (0x00000800UL)
#define EFM_F0NWPRT0_F0NWPRT12_POS                     (12U)
#define EFM_F0NWPRT0_F0NWPRT12                         (0x00001000UL)
#define EFM_F0NWPRT0_F0NWPRT13_POS                     (13U)
#define EFM_F0NWPRT0_F0NWPRT13                         (0x00002000UL)
#define EFM_F0NWPRT0_F0NWPRT14_POS                     (14U)
#define EFM_F0NWPRT0_F0NWPRT14                         (0x00004000UL)
#define EFM_F0NWPRT0_F0NWPRT15_POS                     (15U)
#define EFM_F0NWPRT0_F0NWPRT15                         (0x00008000UL)
#define EFM_F0NWPRT0_F0NWPRT16_POS                     (16U)
#define EFM_F0NWPRT0_F0NWPRT16                         (0x00010000UL)
#define EFM_F0NWPRT0_F0NWPRT17_POS                     (17U)
#define EFM_F0NWPRT0_F0NWPRT17                         (0x00020000UL)
#define EFM_F0NWPRT0_F0NWPRT18_POS                     (18U)
#define EFM_F0NWPRT0_F0NWPRT18                         (0x00040000UL)
#define EFM_F0NWPRT0_F0NWPRT19_POS                     (19U)
#define EFM_F0NWPRT0_F0NWPRT19                         (0x00080000UL)
#define EFM_F0NWPRT0_F0NWPRT20_POS                     (20U)
#define EFM_F0NWPRT0_F0NWPRT20                         (0x00100000UL)
#define EFM_F0NWPRT0_F0NWPRT21_POS                     (21U)
#define EFM_F0NWPRT0_F0NWPRT21                         (0x00200000UL)
#define EFM_F0NWPRT0_F0NWPRT22_POS                     (22U)
#define EFM_F0NWPRT0_F0NWPRT22                         (0x00400000UL)
#define EFM_F0NWPRT0_F0NWPRT23_POS                     (23U)
#define EFM_F0NWPRT0_F0NWPRT23                         (0x00800000UL)
#define EFM_F0NWPRT0_F0NWPRT24_POS                     (24U)
#define EFM_F0NWPRT0_F0NWPRT24                         (0x01000000UL)
#define EFM_F0NWPRT0_F0NWPRT25_POS                     (25U)
#define EFM_F0NWPRT0_F0NWPRT25                         (0x02000000UL)
#define EFM_F0NWPRT0_F0NWPRT26_POS                     (26U)
#define EFM_F0NWPRT0_F0NWPRT26                         (0x04000000UL)
#define EFM_F0NWPRT0_F0NWPRT27_POS                     (27U)
#define EFM_F0NWPRT0_F0NWPRT27                         (0x08000000UL)
#define EFM_F0NWPRT0_F0NWPRT28_POS                     (28U)
#define EFM_F0NWPRT0_F0NWPRT28                         (0x10000000UL)
#define EFM_F0NWPRT0_F0NWPRT29_POS                     (29U)
#define EFM_F0NWPRT0_F0NWPRT29                         (0x20000000UL)
#define EFM_F0NWPRT0_F0NWPRT30_POS                     (30U)
#define EFM_F0NWPRT0_F0NWPRT30                         (0x40000000UL)
#define EFM_F0NWPRT0_F0NWPRT31_POS                     (31U)
#define EFM_F0NWPRT0_F0NWPRT31                         (0x80000000UL)

/*  Bit definition for EFM_F0NWPRT1 register  */
#define EFM_F0NWPRT1_F0NWPRT32_POS                     (0U)
#define EFM_F0NWPRT1_F0NWPRT32                         (0x00000001UL)
#define EFM_F0NWPRT1_F0NWPRT33_POS                     (1U)
#define EFM_F0NWPRT1_F0NWPRT33                         (0x00000002UL)
#define EFM_F0NWPRT1_F0NWPRT34_POS                     (2U)
#define EFM_F0NWPRT1_F0NWPRT34                         (0x00000004UL)
#define EFM_F0NWPRT1_F0NWPRT35_POS                     (3U)
#define EFM_F0NWPRT1_F0NWPRT35                         (0x00000008UL)
#define EFM_F0NWPRT1_F0NWPRT36_POS                     (4U)
#define EFM_F0NWPRT1_F0NWPRT36                         (0x00000010UL)
#define EFM_F0NWPRT1_F0NWPRT37_POS                     (5U)
#define EFM_F0NWPRT1_F0NWPRT37                         (0x00000020UL)
#define EFM_F0NWPRT1_F0NWPRT38_POS                     (6U)
#define EFM_F0NWPRT1_F0NWPRT38                         (0x00000040UL)
#define EFM_F0NWPRT1_F0NWPRT39_POS                     (7U)
#define EFM_F0NWPRT1_F0NWPRT39                         (0x00000080UL)
#define EFM_F0NWPRT1_F0NWPRT40_POS                     (8U)
#define EFM_F0NWPRT1_F0NWPRT40                         (0x00000100UL)
#define EFM_F0NWPRT1_F0NWPRT41_POS                     (9U)
#define EFM_F0NWPRT1_F0NWPRT41                         (0x00000200UL)
#define EFM_F0NWPRT1_F0NWPRT42_POS                     (10U)
#define EFM_F0NWPRT1_F0NWPRT42                         (0x00000400UL)
#define EFM_F0NWPRT1_F0NWPRT43_POS                     (11U)
#define EFM_F0NWPRT1_F0NWPRT43                         (0x00000800UL)
#define EFM_F0NWPRT1_F0NWPRT44_POS                     (12U)
#define EFM_F0NWPRT1_F0NWPRT44                         (0x00001000UL)
#define EFM_F0NWPRT1_F0NWPRT45_POS                     (13U)
#define EFM_F0NWPRT1_F0NWPRT45                         (0x00002000UL)
#define EFM_F0NWPRT1_F0NWPRT46_POS                     (14U)
#define EFM_F0NWPRT1_F0NWPRT46                         (0x00004000UL)
#define EFM_F0NWPRT1_F0NWPRT47_POS                     (15U)
#define EFM_F0NWPRT1_F0NWPRT47                         (0x00008000UL)
#define EFM_F0NWPRT1_F0NWPRT48_POS                     (16U)
#define EFM_F0NWPRT1_F0NWPRT48                         (0x00010000UL)
#define EFM_F0NWPRT1_F0NWPRT49_POS                     (17U)
#define EFM_F0NWPRT1_F0NWPRT49                         (0x00020000UL)
#define EFM_F0NWPRT1_F0NWPRT50_POS                     (18U)
#define EFM_F0NWPRT1_F0NWPRT50                         (0x00040000UL)
#define EFM_F0NWPRT1_F0NWPRT51_POS                     (19U)
#define EFM_F0NWPRT1_F0NWPRT51                         (0x00080000UL)
#define EFM_F0NWPRT1_F0NWPRT52_POS                     (20U)
#define EFM_F0NWPRT1_F0NWPRT52                         (0x00100000UL)
#define EFM_F0NWPRT1_F0NWPRT53_POS                     (21U)
#define EFM_F0NWPRT1_F0NWPRT53                         (0x00200000UL)
#define EFM_F0NWPRT1_F0NWPRT54_POS                     (22U)
#define EFM_F0NWPRT1_F0NWPRT54                         (0x00400000UL)
#define EFM_F0NWPRT1_F0NWPRT55_POS                     (23U)
#define EFM_F0NWPRT1_F0NWPRT55                         (0x00800000UL)
#define EFM_F0NWPRT1_F0NWPRT56_POS                     (24U)
#define EFM_F0NWPRT1_F0NWPRT56                         (0x01000000UL)
#define EFM_F0NWPRT1_F0NWPRT57_POS                     (25U)
#define EFM_F0NWPRT1_F0NWPRT57                         (0x02000000UL)
#define EFM_F0NWPRT1_F0NWPRT58_POS                     (26U)
#define EFM_F0NWPRT1_F0NWPRT58                         (0x04000000UL)
#define EFM_F0NWPRT1_F0NWPRT59_POS                     (27U)
#define EFM_F0NWPRT1_F0NWPRT59                         (0x08000000UL)
#define EFM_F0NWPRT1_F0NWPRT60_POS                     (28U)
#define EFM_F0NWPRT1_F0NWPRT60                         (0x10000000UL)
#define EFM_F0NWPRT1_F0NWPRT61_POS                     (29U)
#define EFM_F0NWPRT1_F0NWPRT61                         (0x20000000UL)
#define EFM_F0NWPRT1_F0NWPRT62_POS                     (30U)
#define EFM_F0NWPRT1_F0NWPRT62                         (0x40000000UL)
#define EFM_F0NWPRT1_F0NWPRT63_POS                     (31U)
#define EFM_F0NWPRT1_F0NWPRT63                         (0x80000000UL)

/*  Bit definition for EFM_F0NWPRT2 register  */
#define EFM_F0NWPRT2_F0NWPRT64_POS                     (0U)
#define EFM_F0NWPRT2_F0NWPRT64                         (0x00000001UL)
#define EFM_F0NWPRT2_F0NWPRT65_POS                     (1U)
#define EFM_F0NWPRT2_F0NWPRT65                         (0x00000002UL)
#define EFM_F0NWPRT2_F0NWPRT66_POS                     (2U)
#define EFM_F0NWPRT2_F0NWPRT66                         (0x00000004UL)
#define EFM_F0NWPRT2_F0NWPRT67_POS                     (3U)
#define EFM_F0NWPRT2_F0NWPRT67                         (0x00000008UL)
#define EFM_F0NWPRT2_F0NWPRT68_POS                     (4U)
#define EFM_F0NWPRT2_F0NWPRT68                         (0x00000010UL)
#define EFM_F0NWPRT2_F0NWPRT69_POS                     (5U)
#define EFM_F0NWPRT2_F0NWPRT69                         (0x00000020UL)
#define EFM_F0NWPRT2_F0NWPRT70_POS                     (6U)
#define EFM_F0NWPRT2_F0NWPRT70                         (0x00000040UL)
#define EFM_F0NWPRT2_F0NWPRT71_POS                     (7U)
#define EFM_F0NWPRT2_F0NWPRT71                         (0x00000080UL)
#define EFM_F0NWPRT2_F0NWPRT72_POS                     (8U)
#define EFM_F0NWPRT2_F0NWPRT72                         (0x00000100UL)
#define EFM_F0NWPRT2_F0NWPRT73_POS                     (9U)
#define EFM_F0NWPRT2_F0NWPRT73                         (0x00000200UL)
#define EFM_F0NWPRT2_F0NWPRT74_POS                     (10U)
#define EFM_F0NWPRT2_F0NWPRT74                         (0x00000400UL)
#define EFM_F0NWPRT2_F0NWPRT75_POS                     (11U)
#define EFM_F0NWPRT2_F0NWPRT75                         (0x00000800UL)
#define EFM_F0NWPRT2_F0NWPRT76_POS                     (12U)
#define EFM_F0NWPRT2_F0NWPRT76                         (0x00001000UL)
#define EFM_F0NWPRT2_F0NWPRT77_POS                     (13U)
#define EFM_F0NWPRT2_F0NWPRT77                         (0x00002000UL)
#define EFM_F0NWPRT2_F0NWPRT78_POS                     (14U)
#define EFM_F0NWPRT2_F0NWPRT78                         (0x00004000UL)
#define EFM_F0NWPRT2_F0NWPRT79_POS                     (15U)
#define EFM_F0NWPRT2_F0NWPRT79                         (0x00008000UL)
#define EFM_F0NWPRT2_F0NWPRT80_POS                     (16U)
#define EFM_F0NWPRT2_F0NWPRT80                         (0x00010000UL)
#define EFM_F0NWPRT2_F0NWPRT81_POS                     (17U)
#define EFM_F0NWPRT2_F0NWPRT81                         (0x00020000UL)
#define EFM_F0NWPRT2_F0NWPRT82_POS                     (18U)
#define EFM_F0NWPRT2_F0NWPRT82                         (0x00040000UL)
#define EFM_F0NWPRT2_F0NWPRT83_POS                     (19U)
#define EFM_F0NWPRT2_F0NWPRT83                         (0x00080000UL)
#define EFM_F0NWPRT2_F0NWPRT84_POS                     (20U)
#define EFM_F0NWPRT2_F0NWPRT84                         (0x00100000UL)
#define EFM_F0NWPRT2_F0NWPRT85_POS                     (21U)
#define EFM_F0NWPRT2_F0NWPRT85                         (0x00200000UL)
#define EFM_F0NWPRT2_F0NWPRT86_POS                     (22U)
#define EFM_F0NWPRT2_F0NWPRT86                         (0x00400000UL)
#define EFM_F0NWPRT2_F0NWPRT87_POS                     (23U)
#define EFM_F0NWPRT2_F0NWPRT87                         (0x00800000UL)
#define EFM_F0NWPRT2_F0NWPRT88_POS                     (24U)
#define EFM_F0NWPRT2_F0NWPRT88                         (0x01000000UL)
#define EFM_F0NWPRT2_F0NWPRT89_POS                     (25U)
#define EFM_F0NWPRT2_F0NWPRT89                         (0x02000000UL)
#define EFM_F0NWPRT2_F0NWPRT90_POS                     (26U)
#define EFM_F0NWPRT2_F0NWPRT90                         (0x04000000UL)
#define EFM_F0NWPRT2_F0NWPRT91_POS                     (27U)
#define EFM_F0NWPRT2_F0NWPRT91                         (0x08000000UL)
#define EFM_F0NWPRT2_F0NWPRT92_POS                     (28U)
#define EFM_F0NWPRT2_F0NWPRT92                         (0x10000000UL)
#define EFM_F0NWPRT2_F0NWPRT93_POS                     (29U)
#define EFM_F0NWPRT2_F0NWPRT93                         (0x20000000UL)
#define EFM_F0NWPRT2_F0NWPRT94_POS                     (30U)
#define EFM_F0NWPRT2_F0NWPRT94                         (0x40000000UL)
#define EFM_F0NWPRT2_F0NWPRT95_POS                     (31U)
#define EFM_F0NWPRT2_F0NWPRT95                         (0x80000000UL)

/*  Bit definition for EFM_F0NWPRT3 register  */
#define EFM_F0NWPRT3_F0NWPRT96_POS                     (0U)
#define EFM_F0NWPRT3_F0NWPRT96                         (0x00000001UL)
#define EFM_F0NWPRT3_F0NWPRT97_POS                     (1U)
#define EFM_F0NWPRT3_F0NWPRT97                         (0x00000002UL)
#define EFM_F0NWPRT3_F0NWPRT98_POS                     (2U)
#define EFM_F0NWPRT3_F0NWPRT98                         (0x00000004UL)
#define EFM_F0NWPRT3_F0NWPRT99_POS                     (3U)
#define EFM_F0NWPRT3_F0NWPRT99                         (0x00000008UL)
#define EFM_F0NWPRT3_F0NWPRT100_POS                    (4U)
#define EFM_F0NWPRT3_F0NWPRT100                        (0x00000010UL)
#define EFM_F0NWPRT3_F0NWPRT101_POS                    (5U)
#define EFM_F0NWPRT3_F0NWPRT101                        (0x00000020UL)
#define EFM_F0NWPRT3_F0NWPRT102_POS                    (6U)
#define EFM_F0NWPRT3_F0NWPRT102                        (0x00000040UL)
#define EFM_F0NWPRT3_F0NWPRT103_POS                    (7U)
#define EFM_F0NWPRT3_F0NWPRT103                        (0x00000080UL)
#define EFM_F0NWPRT3_F0NWPRT104_POS                    (8U)
#define EFM_F0NWPRT3_F0NWPRT104                        (0x00000100UL)
#define EFM_F0NWPRT3_F0NWPRT105_POS                    (9U)
#define EFM_F0NWPRT3_F0NWPRT105                        (0x00000200UL)
#define EFM_F0NWPRT3_F0NWPRT106_POS                    (10U)
#define EFM_F0NWPRT3_F0NWPRT106                        (0x00000400UL)
#define EFM_F0NWPRT3_F0NWPRT107_POS                    (11U)
#define EFM_F0NWPRT3_F0NWPRT107                        (0x00000800UL)
#define EFM_F0NWPRT3_F0NWPRT108_POS                    (12U)
#define EFM_F0NWPRT3_F0NWPRT108                        (0x00001000UL)
#define EFM_F0NWPRT3_F0NWPRT109_POS                    (13U)
#define EFM_F0NWPRT3_F0NWPRT109                        (0x00002000UL)
#define EFM_F0NWPRT3_F0NWPRT110_POS                    (14U)
#define EFM_F0NWPRT3_F0NWPRT110                        (0x00004000UL)
#define EFM_F0NWPRT3_F0NWPRT111_POS                    (15U)
#define EFM_F0NWPRT3_F0NWPRT111                        (0x00008000UL)
#define EFM_F0NWPRT3_F0NWPRT112_POS                    (16U)
#define EFM_F0NWPRT3_F0NWPRT112                        (0x00010000UL)
#define EFM_F0NWPRT3_F0NWPRT113_POS                    (17U)
#define EFM_F0NWPRT3_F0NWPRT113                        (0x00020000UL)
#define EFM_F0NWPRT3_F0NWPRT114_POS                    (18U)
#define EFM_F0NWPRT3_F0NWPRT114                        (0x00040000UL)
#define EFM_F0NWPRT3_F0NWPRT115_POS                    (19U)
#define EFM_F0NWPRT3_F0NWPRT115                        (0x00080000UL)
#define EFM_F0NWPRT3_F0NWPRT116_POS                    (20U)
#define EFM_F0NWPRT3_F0NWPRT116                        (0x00100000UL)
#define EFM_F0NWPRT3_F0NWPRT117_POS                    (21U)
#define EFM_F0NWPRT3_F0NWPRT117                        (0x00200000UL)
#define EFM_F0NWPRT3_F0NWPRT118_POS                    (22U)
#define EFM_F0NWPRT3_F0NWPRT118                        (0x00400000UL)
#define EFM_F0NWPRT3_F0NWPRT119_POS                    (23U)
#define EFM_F0NWPRT3_F0NWPRT119                        (0x00800000UL)
#define EFM_F0NWPRT3_F0NWPRT120_POS                    (24U)
#define EFM_F0NWPRT3_F0NWPRT120                        (0x01000000UL)
#define EFM_F0NWPRT3_F0NWPRT121_POS                    (25U)
#define EFM_F0NWPRT3_F0NWPRT121                        (0x02000000UL)
#define EFM_F0NWPRT3_F0NWPRT122_POS                    (26U)
#define EFM_F0NWPRT3_F0NWPRT122                        (0x04000000UL)
#define EFM_F0NWPRT3_F0NWPRT123_POS                    (27U)
#define EFM_F0NWPRT3_F0NWPRT123                        (0x08000000UL)
#define EFM_F0NWPRT3_F0NWPRT124_POS                    (28U)
#define EFM_F0NWPRT3_F0NWPRT124                        (0x10000000UL)
#define EFM_F0NWPRT3_F0NWPRT125_POS                    (29U)
#define EFM_F0NWPRT3_F0NWPRT125                        (0x20000000UL)
#define EFM_F0NWPRT3_F0NWPRT126_POS                    (30U)
#define EFM_F0NWPRT3_F0NWPRT126                        (0x40000000UL)
#define EFM_F0NWPRT3_F0NWPRT127_POS                    (31U)
#define EFM_F0NWPRT3_F0NWPRT127                        (0x80000000UL)

/*  Bit definition for EFM_F1NWPRT0 register  */
#define EFM_F1NWPRT0_F1NWPRT0_POS                      (0U)
#define EFM_F1NWPRT0_F1NWPRT0                          (0x00000001UL)
#define EFM_F1NWPRT0_F1NWPRT1_POS                      (1U)
#define EFM_F1NWPRT0_F1NWPRT1                          (0x00000002UL)
#define EFM_F1NWPRT0_F1NWPRT2_POS                      (2U)
#define EFM_F1NWPRT0_F1NWPRT2                          (0x00000004UL)
#define EFM_F1NWPRT0_F1NWPRT3_POS                      (3U)
#define EFM_F1NWPRT0_F1NWPRT3                          (0x00000008UL)
#define EFM_F1NWPRT0_F1NWPRT4_POS                      (4U)
#define EFM_F1NWPRT0_F1NWPRT4                          (0x00000010UL)
#define EFM_F1NWPRT0_F1NWPRT5_POS                      (5U)
#define EFM_F1NWPRT0_F1NWPRT5                          (0x00000020UL)
#define EFM_F1NWPRT0_F1NWPRT6_POS                      (6U)
#define EFM_F1NWPRT0_F1NWPRT6                          (0x00000040UL)
#define EFM_F1NWPRT0_F1NWPRT7_POS                      (7U)
#define EFM_F1NWPRT0_F1NWPRT7                          (0x00000080UL)
#define EFM_F1NWPRT0_F1NWPRT8_POS                      (8U)
#define EFM_F1NWPRT0_F1NWPRT8                          (0x00000100UL)
#define EFM_F1NWPRT0_F1NWPRT9_POS                      (9U)
#define EFM_F1NWPRT0_F1NWPRT9                          (0x00000200UL)
#define EFM_F1NWPRT0_F1NWPRT10_POS                     (10U)
#define EFM_F1NWPRT0_F1NWPRT10                         (0x00000400UL)
#define EFM_F1NWPRT0_F1NWPRT11_POS                     (11U)
#define EFM_F1NWPRT0_F1NWPRT11                         (0x00000800UL)
#define EFM_F1NWPRT0_F1NWPRT12_POS                     (12U)
#define EFM_F1NWPRT0_F1NWPRT12                         (0x00001000UL)
#define EFM_F1NWPRT0_F1NWPRT13_POS                     (13U)
#define EFM_F1NWPRT0_F1NWPRT13                         (0x00002000UL)
#define EFM_F1NWPRT0_F1NWPRT14_POS                     (14U)
#define EFM_F1NWPRT0_F1NWPRT14                         (0x00004000UL)
#define EFM_F1NWPRT0_F1NWPRT15_POS                     (15U)
#define EFM_F1NWPRT0_F1NWPRT15                         (0x00008000UL)
#define EFM_F1NWPRT0_F1NWPRT16_POS                     (16U)
#define EFM_F1NWPRT0_F1NWPRT16                         (0x00010000UL)
#define EFM_F1NWPRT0_F1NWPRT17_POS                     (17U)
#define EFM_F1NWPRT0_F1NWPRT17                         (0x00020000UL)
#define EFM_F1NWPRT0_F1NWPRT18_POS                     (18U)
#define EFM_F1NWPRT0_F1NWPRT18                         (0x00040000UL)
#define EFM_F1NWPRT0_F1NWPRT19_POS                     (19U)
#define EFM_F1NWPRT0_F1NWPRT19                         (0x00080000UL)
#define EFM_F1NWPRT0_F1NWPRT20_POS                     (20U)
#define EFM_F1NWPRT0_F1NWPRT20                         (0x00100000UL)
#define EFM_F1NWPRT0_F1NWPRT21_POS                     (21U)
#define EFM_F1NWPRT0_F1NWPRT21                         (0x00200000UL)
#define EFM_F1NWPRT0_F1NWPRT22_POS                     (22U)
#define EFM_F1NWPRT0_F1NWPRT22                         (0x00400000UL)
#define EFM_F1NWPRT0_F1NWPRT23_POS                     (23U)
#define EFM_F1NWPRT0_F1NWPRT23                         (0x00800000UL)
#define EFM_F1NWPRT0_F1NWPRT24_POS                     (24U)
#define EFM_F1NWPRT0_F1NWPRT24                         (0x01000000UL)
#define EFM_F1NWPRT0_F1NWPRT25_POS                     (25U)
#define EFM_F1NWPRT0_F1NWPRT25                         (0x02000000UL)
#define EFM_F1NWPRT0_F1NWPRT26_POS                     (26U)
#define EFM_F1NWPRT0_F1NWPRT26                         (0x04000000UL)
#define EFM_F1NWPRT0_F1NWPRT27_POS                     (27U)
#define EFM_F1NWPRT0_F1NWPRT27                         (0x08000000UL)
#define EFM_F1NWPRT0_F1NWPRT28_POS                     (28U)
#define EFM_F1NWPRT0_F1NWPRT28                         (0x10000000UL)
#define EFM_F1NWPRT0_F1NWPRT29_POS                     (29U)
#define EFM_F1NWPRT0_F1NWPRT29                         (0x20000000UL)
#define EFM_F1NWPRT0_F1NWPRT30_POS                     (30U)
#define EFM_F1NWPRT0_F1NWPRT30                         (0x40000000UL)
#define EFM_F1NWPRT0_F1NWPRT31_POS                     (31U)
#define EFM_F1NWPRT0_F1NWPRT31                         (0x80000000UL)

/*  Bit definition for EFM_F1NWPRT1 register  */
#define EFM_F1NWPRT1_F1NWPRT32_POS                     (0U)
#define EFM_F1NWPRT1_F1NWPRT32                         (0x00000001UL)
#define EFM_F1NWPRT1_F1NWPRT33_POS                     (1U)
#define EFM_F1NWPRT1_F1NWPRT33                         (0x00000002UL)
#define EFM_F1NWPRT1_F1NWPRT34_POS                     (2U)
#define EFM_F1NWPRT1_F1NWPRT34                         (0x00000004UL)
#define EFM_F1NWPRT1_F1NWPRT35_POS                     (3U)
#define EFM_F1NWPRT1_F1NWPRT35                         (0x00000008UL)
#define EFM_F1NWPRT1_F1NWPRT36_POS                     (4U)
#define EFM_F1NWPRT1_F1NWPRT36                         (0x00000010UL)
#define EFM_F1NWPRT1_F1NWPRT37_POS                     (5U)
#define EFM_F1NWPRT1_F1NWPRT37                         (0x00000020UL)
#define EFM_F1NWPRT1_F1NWPRT38_POS                     (6U)
#define EFM_F1NWPRT1_F1NWPRT38                         (0x00000040UL)
#define EFM_F1NWPRT1_F1NWPRT39_POS                     (7U)
#define EFM_F1NWPRT1_F1NWPRT39                         (0x00000080UL)
#define EFM_F1NWPRT1_F1NWPRT40_POS                     (8U)
#define EFM_F1NWPRT1_F1NWPRT40                         (0x00000100UL)
#define EFM_F1NWPRT1_F1NWPRT41_POS                     (9U)
#define EFM_F1NWPRT1_F1NWPRT41                         (0x00000200UL)
#define EFM_F1NWPRT1_F1NWPRT42_POS                     (10U)
#define EFM_F1NWPRT1_F1NWPRT42                         (0x00000400UL)
#define EFM_F1NWPRT1_F1NWPRT43_POS                     (11U)
#define EFM_F1NWPRT1_F1NWPRT43                         (0x00000800UL)
#define EFM_F1NWPRT1_F1NWPRT44_POS                     (12U)
#define EFM_F1NWPRT1_F1NWPRT44                         (0x00001000UL)
#define EFM_F1NWPRT1_F1NWPRT45_POS                     (13U)
#define EFM_F1NWPRT1_F1NWPRT45                         (0x00002000UL)
#define EFM_F1NWPRT1_F1NWPRT46_POS                     (14U)
#define EFM_F1NWPRT1_F1NWPRT46                         (0x00004000UL)
#define EFM_F1NWPRT1_F1NWPRT47_POS                     (15U)
#define EFM_F1NWPRT1_F1NWPRT47                         (0x00008000UL)
#define EFM_F1NWPRT1_F1NWPRT48_POS                     (16U)
#define EFM_F1NWPRT1_F1NWPRT48                         (0x00010000UL)
#define EFM_F1NWPRT1_F1NWPRT49_POS                     (17U)
#define EFM_F1NWPRT1_F1NWPRT49                         (0x00020000UL)
#define EFM_F1NWPRT1_F1NWPRT50_POS                     (18U)
#define EFM_F1NWPRT1_F1NWPRT50                         (0x00040000UL)
#define EFM_F1NWPRT1_F1NWPRT51_POS                     (19U)
#define EFM_F1NWPRT1_F1NWPRT51                         (0x00080000UL)
#define EFM_F1NWPRT1_F1NWPRT52_POS                     (20U)
#define EFM_F1NWPRT1_F1NWPRT52                         (0x00100000UL)
#define EFM_F1NWPRT1_F1NWPRT53_POS                     (21U)
#define EFM_F1NWPRT1_F1NWPRT53                         (0x00200000UL)
#define EFM_F1NWPRT1_F1NWPRT54_POS                     (22U)
#define EFM_F1NWPRT1_F1NWPRT54                         (0x00400000UL)
#define EFM_F1NWPRT1_F1NWPRT55_POS                     (23U)
#define EFM_F1NWPRT1_F1NWPRT55                         (0x00800000UL)
#define EFM_F1NWPRT1_F1NWPRT56_POS                     (24U)
#define EFM_F1NWPRT1_F1NWPRT56                         (0x01000000UL)
#define EFM_F1NWPRT1_F1NWPRT57_POS                     (25U)
#define EFM_F1NWPRT1_F1NWPRT57                         (0x02000000UL)
#define EFM_F1NWPRT1_F1NWPRT58_POS                     (26U)
#define EFM_F1NWPRT1_F1NWPRT58                         (0x04000000UL)
#define EFM_F1NWPRT1_F1NWPRT59_POS                     (27U)
#define EFM_F1NWPRT1_F1NWPRT59                         (0x08000000UL)
#define EFM_F1NWPRT1_F1NWPRT60_POS                     (28U)
#define EFM_F1NWPRT1_F1NWPRT60                         (0x10000000UL)
#define EFM_F1NWPRT1_F1NWPRT61_POS                     (29U)
#define EFM_F1NWPRT1_F1NWPRT61                         (0x20000000UL)
#define EFM_F1NWPRT1_F1NWPRT62_POS                     (30U)
#define EFM_F1NWPRT1_F1NWPRT62                         (0x40000000UL)
#define EFM_F1NWPRT1_F1NWPRT63_POS                     (31U)
#define EFM_F1NWPRT1_F1NWPRT63                         (0x80000000UL)

/*  Bit definition for EFM_F1NWPRT2 register  */
#define EFM_F1NWPRT2_F1NWPRT64_POS                     (0U)
#define EFM_F1NWPRT2_F1NWPRT64                         (0x00000001UL)
#define EFM_F1NWPRT2_F1NWPRT65_POS                     (1U)
#define EFM_F1NWPRT2_F1NWPRT65                         (0x00000002UL)
#define EFM_F1NWPRT2_F1NWPRT66_POS                     (2U)
#define EFM_F1NWPRT2_F1NWPRT66                         (0x00000004UL)
#define EFM_F1NWPRT2_F1NWPRT67_POS                     (3U)
#define EFM_F1NWPRT2_F1NWPRT67                         (0x00000008UL)
#define EFM_F1NWPRT2_F1NWPRT68_POS                     (4U)
#define EFM_F1NWPRT2_F1NWPRT68                         (0x00000010UL)
#define EFM_F1NWPRT2_F1NWPRT69_POS                     (5U)
#define EFM_F1NWPRT2_F1NWPRT69                         (0x00000020UL)
#define EFM_F1NWPRT2_F1NWPRT70_POS                     (6U)
#define EFM_F1NWPRT2_F1NWPRT70                         (0x00000040UL)
#define EFM_F1NWPRT2_F1NWPRT71_POS                     (7U)
#define EFM_F1NWPRT2_F1NWPRT71                         (0x00000080UL)
#define EFM_F1NWPRT2_F1NWPRT72_POS                     (8U)
#define EFM_F1NWPRT2_F1NWPRT72                         (0x00000100UL)
#define EFM_F1NWPRT2_F1NWPRT73_POS                     (9U)
#define EFM_F1NWPRT2_F1NWPRT73                         (0x00000200UL)
#define EFM_F1NWPRT2_F1NWPRT74_POS                     (10U)
#define EFM_F1NWPRT2_F1NWPRT74                         (0x00000400UL)
#define EFM_F1NWPRT2_F1NWPRT75_POS                     (11U)
#define EFM_F1NWPRT2_F1NWPRT75                         (0x00000800UL)
#define EFM_F1NWPRT2_F1NWPRT76_POS                     (12U)
#define EFM_F1NWPRT2_F1NWPRT76                         (0x00001000UL)
#define EFM_F1NWPRT2_F1NWPRT77_POS                     (13U)
#define EFM_F1NWPRT2_F1NWPRT77                         (0x00002000UL)
#define EFM_F1NWPRT2_F1NWPRT78_POS                     (14U)
#define EFM_F1NWPRT2_F1NWPRT78                         (0x00004000UL)
#define EFM_F1NWPRT2_F1NWPRT79_POS                     (15U)
#define EFM_F1NWPRT2_F1NWPRT79                         (0x00008000UL)
#define EFM_F1NWPRT2_F1NWPRT80_POS                     (16U)
#define EFM_F1NWPRT2_F1NWPRT80                         (0x00010000UL)
#define EFM_F1NWPRT2_F1NWPRT81_POS                     (17U)
#define EFM_F1NWPRT2_F1NWPRT81                         (0x00020000UL)
#define EFM_F1NWPRT2_F1NWPRT82_POS                     (18U)
#define EFM_F1NWPRT2_F1NWPRT82                         (0x00040000UL)
#define EFM_F1NWPRT2_F1NWPRT83_POS                     (19U)
#define EFM_F1NWPRT2_F1NWPRT83                         (0x00080000UL)
#define EFM_F1NWPRT2_F1NWPRT84_POS                     (20U)
#define EFM_F1NWPRT2_F1NWPRT84                         (0x00100000UL)
#define EFM_F1NWPRT2_F1NWPRT85_POS                     (21U)
#define EFM_F1NWPRT2_F1NWPRT85                         (0x00200000UL)
#define EFM_F1NWPRT2_F1NWPRT86_POS                     (22U)
#define EFM_F1NWPRT2_F1NWPRT86                         (0x00400000UL)
#define EFM_F1NWPRT2_F1NWPRT87_POS                     (23U)
#define EFM_F1NWPRT2_F1NWPRT87                         (0x00800000UL)
#define EFM_F1NWPRT2_F1NWPRT88_POS                     (24U)
#define EFM_F1NWPRT2_F1NWPRT88                         (0x01000000UL)
#define EFM_F1NWPRT2_F1NWPRT89_POS                     (25U)
#define EFM_F1NWPRT2_F1NWPRT89                         (0x02000000UL)
#define EFM_F1NWPRT2_F1NWPRT90_POS                     (26U)
#define EFM_F1NWPRT2_F1NWPRT90                         (0x04000000UL)
#define EFM_F1NWPRT2_F1NWPRT91_POS                     (27U)
#define EFM_F1NWPRT2_F1NWPRT91                         (0x08000000UL)
#define EFM_F1NWPRT2_F1NWPRT92_POS                     (28U)
#define EFM_F1NWPRT2_F1NWPRT92                         (0x10000000UL)
#define EFM_F1NWPRT2_F1NWPRT93_POS                     (29U)
#define EFM_F1NWPRT2_F1NWPRT93                         (0x20000000UL)
#define EFM_F1NWPRT2_F1NWPRT94_POS                     (30U)
#define EFM_F1NWPRT2_F1NWPRT94                         (0x40000000UL)
#define EFM_F1NWPRT2_F1NWPRT95_POS                     (31U)
#define EFM_F1NWPRT2_F1NWPRT95                         (0x80000000UL)

/*  Bit definition for EFM_F1NWPRT3 register  */
#define EFM_F1NWPRT3_F1NWPRT96_POS                     (0U)
#define EFM_F1NWPRT3_F1NWPRT96                         (0x00000001UL)
#define EFM_F1NWPRT3_F1NWPRT97_POS                     (1U)
#define EFM_F1NWPRT3_F1NWPRT97                         (0x00000002UL)
#define EFM_F1NWPRT3_F1NWPRT98_POS                     (2U)
#define EFM_F1NWPRT3_F1NWPRT98                         (0x00000004UL)
#define EFM_F1NWPRT3_F1NWPRT99_POS                     (3U)
#define EFM_F1NWPRT3_F1NWPRT99                         (0x00000008UL)
#define EFM_F1NWPRT3_F1NWPRT100_POS                    (4U)
#define EFM_F1NWPRT3_F1NWPRT100                        (0x00000010UL)
#define EFM_F1NWPRT3_F1NWPRT101_POS                    (5U)
#define EFM_F1NWPRT3_F1NWPRT101                        (0x00000020UL)
#define EFM_F1NWPRT3_F1NWPRT102_POS                    (6U)
#define EFM_F1NWPRT3_F1NWPRT102                        (0x00000040UL)
#define EFM_F1NWPRT3_F1NWPRT103_POS                    (7U)
#define EFM_F1NWPRT3_F1NWPRT103                        (0x00000080UL)
#define EFM_F1NWPRT3_F1NWPRT104_POS                    (8U)
#define EFM_F1NWPRT3_F1NWPRT104                        (0x00000100UL)
#define EFM_F1NWPRT3_F1NWPRT105_POS                    (9U)
#define EFM_F1NWPRT3_F1NWPRT105                        (0x00000200UL)
#define EFM_F1NWPRT3_F1NWPRT106_POS                    (10U)
#define EFM_F1NWPRT3_F1NWPRT106                        (0x00000400UL)
#define EFM_F1NWPRT3_F1NWPRT107_POS                    (11U)
#define EFM_F1NWPRT3_F1NWPRT107                        (0x00000800UL)
#define EFM_F1NWPRT3_F1NWPRT108_POS                    (12U)
#define EFM_F1NWPRT3_F1NWPRT108                        (0x00001000UL)
#define EFM_F1NWPRT3_F1NWPRT109_POS                    (13U)
#define EFM_F1NWPRT3_F1NWPRT109                        (0x00002000UL)
#define EFM_F1NWPRT3_F1NWPRT110_POS                    (14U)
#define EFM_F1NWPRT3_F1NWPRT110                        (0x00004000UL)
#define EFM_F1NWPRT3_F1NWPRT111_POS                    (15U)
#define EFM_F1NWPRT3_F1NWPRT111                        (0x00008000UL)
#define EFM_F1NWPRT3_F1NWPRT112_POS                    (16U)
#define EFM_F1NWPRT3_F1NWPRT112                        (0x00010000UL)
#define EFM_F1NWPRT3_F1NWPRT113_POS                    (17U)
#define EFM_F1NWPRT3_F1NWPRT113                        (0x00020000UL)
#define EFM_F1NWPRT3_F1NWPRT114_POS                    (18U)
#define EFM_F1NWPRT3_F1NWPRT114                        (0x00040000UL)
#define EFM_F1NWPRT3_F1NWPRT115_POS                    (19U)
#define EFM_F1NWPRT3_F1NWPRT115                        (0x00080000UL)
#define EFM_F1NWPRT3_F1NWPRT116_POS                    (20U)
#define EFM_F1NWPRT3_F1NWPRT116                        (0x00100000UL)
#define EFM_F1NWPRT3_F1NWPRT117_POS                    (21U)
#define EFM_F1NWPRT3_F1NWPRT117                        (0x00200000UL)
#define EFM_F1NWPRT3_F1NWPRT118_POS                    (22U)
#define EFM_F1NWPRT3_F1NWPRT118                        (0x00400000UL)
#define EFM_F1NWPRT3_F1NWPRT119_POS                    (23U)
#define EFM_F1NWPRT3_F1NWPRT119                        (0x00800000UL)
#define EFM_F1NWPRT3_F1NWPRT120_POS                    (24U)
#define EFM_F1NWPRT3_F1NWPRT120                        (0x01000000UL)
#define EFM_F1NWPRT3_F1NWPRT121_POS                    (25U)
#define EFM_F1NWPRT3_F1NWPRT121                        (0x02000000UL)
#define EFM_F1NWPRT3_F1NWPRT122_POS                    (26U)
#define EFM_F1NWPRT3_F1NWPRT122                        (0x04000000UL)
#define EFM_F1NWPRT3_F1NWPRT123_POS                    (27U)
#define EFM_F1NWPRT3_F1NWPRT123                        (0x08000000UL)
#define EFM_F1NWPRT3_F1NWPRT124_POS                    (28U)
#define EFM_F1NWPRT3_F1NWPRT124                        (0x10000000UL)
#define EFM_F1NWPRT3_F1NWPRT125_POS                    (29U)
#define EFM_F1NWPRT3_F1NWPRT125                        (0x20000000UL)
#define EFM_F1NWPRT3_F1NWPRT126_POS                    (30U)
#define EFM_F1NWPRT3_F1NWPRT126                        (0x40000000UL)
#define EFM_F1NWPRT3_F1NWPRT127_POS                    (31U)
#define EFM_F1NWPRT3_F1NWPRT127                        (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral EMB
*******************************************************************************/
/*  Bit definition for EMB_CTL1 register  */
#define EMB_CTL1_CMPEN1_POS                            (0U)
#define EMB_CTL1_CMPEN1                                (0x00000001UL)
#define EMB_CTL1_CMPEN2_POS                            (1U)
#define EMB_CTL1_CMPEN2                                (0x00000002UL)
#define EMB_CTL1_CMPEN3_POS                            (2U)
#define EMB_CTL1_CMPEN3                                (0x00000004UL)
#define EMB_CTL1_CMPEN4_POS                            (3U)
#define EMB_CTL1_CMPEN4                                (0x00000008UL)
#define EMB_CTL1_OSCSTPEN_POS                          (4U)
#define EMB_CTL1_OSCSTPEN                              (0x00000010UL)
#define EMB_CTL1_PWMSEN0_POS                           (5U)
#define EMB_CTL1_PWMSEN0                               (0x00000020UL)
#define EMB_CTL1_PWMSEN1_POS                           (6U)
#define EMB_CTL1_PWMSEN1                               (0x00000040UL)
#define EMB_CTL1_PWMSEN2_POS                           (7U)
#define EMB_CTL1_PWMSEN2                               (0x00000080UL)
#define EMB_CTL1_PWMSEN3_POS                           (8U)
#define EMB_CTL1_PWMSEN3                               (0x00000100UL)
#define EMB_CTL1_PWMSEN4_POS                           (9U)
#define EMB_CTL1_PWMSEN4                               (0x00000200UL)
#define EMB_CTL1_PWMSEN5_POS                           (10U)
#define EMB_CTL1_PWMSEN5                               (0x00000400UL)
#define EMB_CTL1_PWMSEN6_POS                           (11U)
#define EMB_CTL1_PWMSEN6                               (0x00000800UL)
#define EMB_CTL1_PWMSEN7_POS                           (12U)
#define EMB_CTL1_PWMSEN7                               (0x00001000UL)
#define EMB_CTL1_PORTINEN1_POS                         (16U)
#define EMB_CTL1_PORTINEN1                             (0x00010000UL)
#define EMB_CTL1_PORTINEN2_POS                         (17U)
#define EMB_CTL1_PORTINEN2                             (0x00020000UL)
#define EMB_CTL1_PORTINEN3_POS                         (18U)
#define EMB_CTL1_PORTINEN3                             (0x00040000UL)
#define EMB_CTL1_PORTINEN4_POS                         (19U)
#define EMB_CTL1_PORTINEN4                             (0x00080000UL)
#define EMB_CTL1_INVSEL1_POS                           (22U)
#define EMB_CTL1_INVSEL1                               (0x00400000UL)
#define EMB_CTL1_INVSEL2_POS                           (23U)
#define EMB_CTL1_INVSEL2                               (0x00800000UL)
#define EMB_CTL1_INVSEL3_POS                           (24U)
#define EMB_CTL1_INVSEL3                               (0x01000000UL)
#define EMB_CTL1_INVSEL4_POS                           (25U)
#define EMB_CTL1_INVSEL4                               (0x02000000UL)

/*  Bit definition for EMB_CTL2 register  */
#define EMB_CTL2_PWMLV0_POS                            (0U)
#define EMB_CTL2_PWMLV0                                (0x00000001UL)
#define EMB_CTL2_PWMLV1_POS                            (1U)
#define EMB_CTL2_PWMLV1                                (0x00000002UL)
#define EMB_CTL2_PWMLV2_POS                            (2U)
#define EMB_CTL2_PWMLV2                                (0x00000004UL)
#define EMB_CTL2_PWMLV3_POS                            (3U)
#define EMB_CTL2_PWMLV3                                (0x00000008UL)
#define EMB_CTL2_PWMLV4_POS                            (4U)
#define EMB_CTL2_PWMLV4                                (0x00000010UL)
#define EMB_CTL2_PWMLV5_POS                            (5U)
#define EMB_CTL2_PWMLV5                                (0x00000020UL)
#define EMB_CTL2_PWMLV6_POS                            (6U)
#define EMB_CTL2_PWMLV6                                (0x00000040UL)
#define EMB_CTL2_PWMLV7_POS                            (7U)
#define EMB_CTL2_PWMLV7                                (0x00000080UL)
#define EMB_CTL2_NFSEL1_POS                            (16U)
#define EMB_CTL2_NFSEL1                                (0x00030000UL)
#define EMB_CTL2_NFEN1_POS                             (18U)
#define EMB_CTL2_NFEN1                                 (0x00040000UL)
#define EMB_CTL2_NFSEL2_POS                            (19U)
#define EMB_CTL2_NFSEL2                                (0x00180000UL)
#define EMB_CTL2_NFEN2_POS                             (21U)
#define EMB_CTL2_NFEN2                                 (0x00200000UL)
#define EMB_CTL2_NFSEL3_POS                            (22U)
#define EMB_CTL2_NFSEL3                                (0x00C00000UL)
#define EMB_CTL2_NFEN3_POS                             (24U)
#define EMB_CTL2_NFEN3                                 (0x01000000UL)
#define EMB_CTL2_NFSEL4_POS                            (25U)
#define EMB_CTL2_NFSEL4                                (0x06000000UL)
#define EMB_CTL2_NFEN4_POS                             (27U)
#define EMB_CTL2_NFEN4                                 (0x08000000UL)

/*  Bit definition for EMB_SOE register  */
#define EMB_SOE_SOE                                    (0x00000001UL)

/*  Bit definition for EMB_STAT register  */
#define EMB_STAT_PWMSF_POS                             (1U)
#define EMB_STAT_PWMSF                                 (0x00000002UL)
#define EMB_STAT_CMPF_POS                              (2U)
#define EMB_STAT_CMPF                                  (0x00000004UL)
#define EMB_STAT_OSF_POS                               (3U)
#define EMB_STAT_OSF                                   (0x00000008UL)
#define EMB_STAT_PWMST_POS                             (5U)
#define EMB_STAT_PWMST                                 (0x00000020UL)
#define EMB_STAT_CMPST_POS                             (6U)
#define EMB_STAT_CMPST                                 (0x00000040UL)
#define EMB_STAT_OSST_POS                              (7U)
#define EMB_STAT_OSST                                  (0x00000080UL)
#define EMB_STAT_PORTINF1_POS                          (8U)
#define EMB_STAT_PORTINF1                              (0x00000100UL)
#define EMB_STAT_PORTINF2_POS                          (9U)
#define EMB_STAT_PORTINF2                              (0x00000200UL)
#define EMB_STAT_PORTINF3_POS                          (10U)
#define EMB_STAT_PORTINF3                              (0x00000400UL)
#define EMB_STAT_PORTINF4_POS                          (11U)
#define EMB_STAT_PORTINF4                              (0x00000800UL)
#define EMB_STAT_PORTINST1_POS                         (14U)
#define EMB_STAT_PORTINST1                             (0x00004000UL)
#define EMB_STAT_PORTINST2_POS                         (15U)
#define EMB_STAT_PORTINST2                             (0x00008000UL)
#define EMB_STAT_PORTINST3_POS                         (16U)
#define EMB_STAT_PORTINST3                             (0x00010000UL)
#define EMB_STAT_PORTINST4_POS                         (17U)
#define EMB_STAT_PORTINST4                             (0x00020000UL)

/*  Bit definition for EMB_STATCLR register  */
#define EMB_STATCLR_PWMSFCLR_POS                       (1U)
#define EMB_STATCLR_PWMSFCLR                           (0x00000002UL)
#define EMB_STATCLR_CMPFCLR_POS                        (2U)
#define EMB_STATCLR_CMPFCLR                            (0x00000004UL)
#define EMB_STATCLR_OSFCLR_POS                         (3U)
#define EMB_STATCLR_OSFCLR                             (0x00000008UL)
#define EMB_STATCLR_PORTINFCLR1_POS                    (8U)
#define EMB_STATCLR_PORTINFCLR1                        (0x00000100UL)
#define EMB_STATCLR_PORTINFCLR2_POS                    (9U)
#define EMB_STATCLR_PORTINFCLR2                        (0x00000200UL)
#define EMB_STATCLR_PORTINFCLR3_POS                    (10U)
#define EMB_STATCLR_PORTINFCLR3                        (0x00000400UL)
#define EMB_STATCLR_PORTINFCLR4_POS                    (11U)
#define EMB_STATCLR_PORTINFCLR4                        (0x00000800UL)

/*  Bit definition for EMB_INTEN register  */
#define EMB_INTEN_PWMSINTEN_POS                        (1U)
#define EMB_INTEN_PWMSINTEN                            (0x00000002UL)
#define EMB_INTEN_CMPINTEN_POS                         (2U)
#define EMB_INTEN_CMPINTEN                             (0x00000004UL)
#define EMB_INTEN_OSINTEN_POS                          (3U)
#define EMB_INTEN_OSINTEN                              (0x00000008UL)
#define EMB_INTEN_PORTININTEN1_POS                     (8U)
#define EMB_INTEN_PORTININTEN1                         (0x00000100UL)
#define EMB_INTEN_PORTININTEN2_POS                     (9U)
#define EMB_INTEN_PORTININTEN2                         (0x00000200UL)
#define EMB_INTEN_PORTININTEN3_POS                     (10U)
#define EMB_INTEN_PORTININTEN3                         (0x00000400UL)
#define EMB_INTEN_PORTININTEN4_POS                     (11U)
#define EMB_INTEN_PORTININTEN4                         (0x00000800UL)

/*  Bit definition for EMB_RLSSEL register  */
#define EMB_RLSSEL_PWMRSEL_POS                         (1U)
#define EMB_RLSSEL_PWMRSEL                             (0x00000002UL)
#define EMB_RLSSEL_CMPRSEL_POS                         (2U)
#define EMB_RLSSEL_CMPRSEL                             (0x00000004UL)
#define EMB_RLSSEL_OSRSEL_POS                          (3U)
#define EMB_RLSSEL_OSRSEL                              (0x00000008UL)
#define EMB_RLSSEL_PORTINRSEL1_POS                     (8U)
#define EMB_RLSSEL_PORTINRSEL1                         (0x00000100UL)
#define EMB_RLSSEL_PORTINRSEL2_POS                     (9U)
#define EMB_RLSSEL_PORTINRSEL2                         (0x00000200UL)
#define EMB_RLSSEL_PORTINRSEL3_POS                     (10U)
#define EMB_RLSSEL_PORTINRSEL3                         (0x00000400UL)
#define EMB_RLSSEL_PORTINRSEL4_POS                     (11U)
#define EMB_RLSSEL_PORTINRSEL4                         (0x00000800UL)

/*******************************************************************************
                Bit definition for Peripheral ETH
*******************************************************************************/
/*  Bit definition for ETH_MAC_IFCONFR register  */
#define ETH_MAC_IFCONFR_IFSEL_POS                      (0U)
#define ETH_MAC_IFCONFR_IFSEL                          (0x00000001UL)
#define ETH_MAC_IFCONFR_RCKINV_POS                     (4U)
#define ETH_MAC_IFCONFR_RCKINV                         (0x00000010UL)
#define ETH_MAC_IFCONFR_TCKINV_POS                     (5U)
#define ETH_MAC_IFCONFR_TCKINV                         (0x00000020UL)

/*  Bit definition for ETH_MAC_CONFIGR register  */
#define ETH_MAC_CONFIGR_RE_POS                         (2U)
#define ETH_MAC_CONFIGR_RE                             (0x00000004UL)
#define ETH_MAC_CONFIGR_TE_POS                         (3U)
#define ETH_MAC_CONFIGR_TE                             (0x00000008UL)
#define ETH_MAC_CONFIGR_DC_POS                         (4U)
#define ETH_MAC_CONFIGR_DC                             (0x00000010UL)
#define ETH_MAC_CONFIGR_BL_POS                         (5U)
#define ETH_MAC_CONFIGR_BL                             (0x00000060UL)
#define ETH_MAC_CONFIGR_BL_0                           (0x00000020UL)
#define ETH_MAC_CONFIGR_BL_1                           (0x00000040UL)
#define ETH_MAC_CONFIGR_ACS_POS                        (7U)
#define ETH_MAC_CONFIGR_ACS                            (0x00000080UL)
#define ETH_MAC_CONFIGR_DRTY_POS                       (9U)
#define ETH_MAC_CONFIGR_DRTY                           (0x00000200UL)
#define ETH_MAC_CONFIGR_IPCO_POS                       (10U)
#define ETH_MAC_CONFIGR_IPCO                           (0x00000400UL)
#define ETH_MAC_CONFIGR_DM_POS                         (11U)
#define ETH_MAC_CONFIGR_DM                             (0x00000800UL)
#define ETH_MAC_CONFIGR_LM_POS                         (12U)
#define ETH_MAC_CONFIGR_LM                             (0x00001000UL)
#define ETH_MAC_CONFIGR_DO_POS                         (13U)
#define ETH_MAC_CONFIGR_DO                             (0x00002000UL)
#define ETH_MAC_CONFIGR_FES_POS                        (14U)
#define ETH_MAC_CONFIGR_FES                            (0x00004000UL)
#define ETH_MAC_CONFIGR_DCRS_POS                       (16U)
#define ETH_MAC_CONFIGR_DCRS                           (0x00010000UL)
#define ETH_MAC_CONFIGR_IFG_POS                        (17U)
#define ETH_MAC_CONFIGR_IFG                            (0x000E0000UL)
#define ETH_MAC_CONFIGR_IFG_0                          (0x00020000UL)
#define ETH_MAC_CONFIGR_IFG_1                          (0x00040000UL)
#define ETH_MAC_CONFIGR_IFG_2                          (0x00080000UL)
#define ETH_MAC_CONFIGR_MJB_POS                        (22U)
#define ETH_MAC_CONFIGR_MJB                            (0x00400000UL)
#define ETH_MAC_CONFIGR_MWD_POS                        (23U)
#define ETH_MAC_CONFIGR_MWD                            (0x00800000UL)
#define ETH_MAC_CONFIGR_CST_POS                        (25U)
#define ETH_MAC_CONFIGR_CST                            (0x02000000UL)
#define ETH_MAC_CONFIGR_SAIRC_POS                      (28U)
#define ETH_MAC_CONFIGR_SAIRC                          (0x70000000UL)
#define ETH_MAC_CONFIGR_SAIRC_0                        (0x10000000UL)
#define ETH_MAC_CONFIGR_SAIRC_1                        (0x20000000UL)
#define ETH_MAC_CONFIGR_SAIRC_2                        (0x40000000UL)

/*  Bit definition for ETH_MAC_FLTCTLR register  */
#define ETH_MAC_FLTCTLR_PR_POS                         (0U)
#define ETH_MAC_FLTCTLR_PR                             (0x00000001UL)
#define ETH_MAC_FLTCTLR_HUC_POS                        (1U)
#define ETH_MAC_FLTCTLR_HUC                            (0x00000002UL)
#define ETH_MAC_FLTCTLR_HMC_POS                        (2U)
#define ETH_MAC_FLTCTLR_HMC                            (0x00000004UL)
#define ETH_MAC_FLTCTLR_DAIF_POS                       (3U)
#define ETH_MAC_FLTCTLR_DAIF                           (0x00000008UL)
#define ETH_MAC_FLTCTLR_PMF_POS                        (4U)
#define ETH_MAC_FLTCTLR_PMF                            (0x00000010UL)
#define ETH_MAC_FLTCTLR_DBF_POS                        (5U)
#define ETH_MAC_FLTCTLR_DBF                            (0x00000020UL)
#define ETH_MAC_FLTCTLR_PCF_POS                        (6U)
#define ETH_MAC_FLTCTLR_PCF                            (0x000000C0UL)
#define ETH_MAC_FLTCTLR_PCF_0                          (0x00000040UL)
#define ETH_MAC_FLTCTLR_PCF_1                          (0x00000080UL)
#define ETH_MAC_FLTCTLR_SAIF_POS                       (8U)
#define ETH_MAC_FLTCTLR_SAIF                           (0x00000100UL)
#define ETH_MAC_FLTCTLR_SAF_POS                        (9U)
#define ETH_MAC_FLTCTLR_SAF                            (0x00000200UL)
#define ETH_MAC_FLTCTLR_HPF_POS                        (10U)
#define ETH_MAC_FLTCTLR_HPF                            (0x00000400UL)
#define ETH_MAC_FLTCTLR_VTFE_POS                       (16U)
#define ETH_MAC_FLTCTLR_VTFE                           (0x00010000UL)
#define ETH_MAC_FLTCTLR_IPFE_POS                       (20U)
#define ETH_MAC_FLTCTLR_IPFE                           (0x00100000UL)
#define ETH_MAC_FLTCTLR_DNTU_POS                       (21U)
#define ETH_MAC_FLTCTLR_DNTU                           (0x00200000UL)
#define ETH_MAC_FLTCTLR_RA_POS                         (31U)
#define ETH_MAC_FLTCTLR_RA                             (0x80000000UL)

/*  Bit definition for ETH_MAC_HASHTHR register  */
#define ETH_MAC_HASHTHR_HTH                            (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_HASHTLR register  */
#define ETH_MAC_HASHTLR_HTL                            (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_SMIADDR register  */
#define ETH_MAC_SMIADDR_SMIB_POS                       (0U)
#define ETH_MAC_SMIADDR_SMIB                           (0x00000001UL)
#define ETH_MAC_SMIADDR_SMIW_POS                       (1U)
#define ETH_MAC_SMIADDR_SMIW                           (0x00000002UL)
#define ETH_MAC_SMIADDR_SMIC_POS                       (2U)
#define ETH_MAC_SMIADDR_SMIC                           (0x0000003CUL)
#define ETH_MAC_SMIADDR_SMIC_0                         (0x00000004UL)
#define ETH_MAC_SMIADDR_SMIC_1                         (0x00000008UL)
#define ETH_MAC_SMIADDR_SMIC_2                         (0x00000010UL)
#define ETH_MAC_SMIADDR_SMIC_3                         (0x00000020UL)
#define ETH_MAC_SMIADDR_SMIR_POS                       (6U)
#define ETH_MAC_SMIADDR_SMIR                           (0x000007C0UL)
#define ETH_MAC_SMIADDR_SMIR_0                         (0x00000040UL)
#define ETH_MAC_SMIADDR_SMIR_1                         (0x00000080UL)
#define ETH_MAC_SMIADDR_SMIR_2                         (0x00000100UL)
#define ETH_MAC_SMIADDR_SMIR_3                         (0x00000200UL)
#define ETH_MAC_SMIADDR_SMIR_4                         (0x00000400UL)
#define ETH_MAC_SMIADDR_SMIA_POS                       (11U)
#define ETH_MAC_SMIADDR_SMIA                           (0x0000F800UL)
#define ETH_MAC_SMIADDR_SMIA_0                         (0x00000800UL)
#define ETH_MAC_SMIADDR_SMIA_1                         (0x00001000UL)
#define ETH_MAC_SMIADDR_SMIA_2                         (0x00002000UL)
#define ETH_MAC_SMIADDR_SMIA_3                         (0x00004000UL)
#define ETH_MAC_SMIADDR_SMIA_4                         (0x00008000UL)

/*  Bit definition for ETH_MAC_SMIDATR register  */
#define ETH_MAC_SMIDATR_SMID                           (0x0000FFFFUL)

/*  Bit definition for ETH_MAC_FLOCTLR register  */
#define ETH_MAC_FLOCTLR_FCA_BPA_POS                    (0U)
#define ETH_MAC_FLOCTLR_FCA_BPA                        (0x00000001UL)
#define ETH_MAC_FLOCTLR_TFE_POS                        (1U)
#define ETH_MAC_FLOCTLR_TFE                            (0x00000002UL)
#define ETH_MAC_FLOCTLR_RFE_POS                        (2U)
#define ETH_MAC_FLOCTLR_RFE                            (0x00000004UL)
#define ETH_MAC_FLOCTLR_UNP_POS                        (3U)
#define ETH_MAC_FLOCTLR_UNP                            (0x00000008UL)
#define ETH_MAC_FLOCTLR_PLT_POS                        (4U)
#define ETH_MAC_FLOCTLR_PLT                            (0x00000030UL)
#define ETH_MAC_FLOCTLR_PLT_0                          (0x00000010UL)
#define ETH_MAC_FLOCTLR_PLT_1                          (0x00000020UL)
#define ETH_MAC_FLOCTLR_DZPQ_POS                       (7U)
#define ETH_MAC_FLOCTLR_DZPQ                           (0x00000080UL)
#define ETH_MAC_FLOCTLR_PAUSET_POS                     (16U)
#define ETH_MAC_FLOCTLR_PAUSET                         (0xFFFF0000UL)

/*  Bit definition for ETH_MAC_VTAFLTR register  */
#define ETH_MAC_VTAFLTR_VLFLT_POS                      (0U)
#define ETH_MAC_VTAFLTR_VLFLT                          (0x0000FFFFUL)
#define ETH_MAC_VTAFLTR_VTAL_POS                       (16U)
#define ETH_MAC_VTAFLTR_VTAL                           (0x00010000UL)
#define ETH_MAC_VTAFLTR_VTIM_POS                       (17U)
#define ETH_MAC_VTAFLTR_VTIM                           (0x00020000UL)
#define ETH_MAC_VTAFLTR_VTHM_POS                       (19U)
#define ETH_MAC_VTAFLTR_VTHM                           (0x00080000UL)

/*  Bit definition for ETH_MAC_MACSTSR register  */
#define ETH_MAC_MACSTSR_MREA_POS                       (0U)
#define ETH_MAC_MACSTSR_MREA                           (0x00000001UL)
#define ETH_MAC_MACSTSR_MRS_POS                        (1U)
#define ETH_MAC_MACSTSR_MRS                            (0x00000006UL)
#define ETH_MAC_MACSTSR_MRS_0                          (0x00000002UL)
#define ETH_MAC_MACSTSR_MRS_1                          (0x00000004UL)
#define ETH_MAC_MACSTSR_RFWA_POS                       (4U)
#define ETH_MAC_MACSTSR_RFWA                           (0x00000010UL)
#define ETH_MAC_MACSTSR_RFRS_POS                       (5U)
#define ETH_MAC_MACSTSR_RFRS                           (0x00000060UL)
#define ETH_MAC_MACSTSR_RFRS_0                         (0x00000020UL)
#define ETH_MAC_MACSTSR_RFRS_1                         (0x00000040UL)
#define ETH_MAC_MACSTSR_RFFL_POS                       (8U)
#define ETH_MAC_MACSTSR_RFFL                           (0x00000300UL)
#define ETH_MAC_MACSTSR_RFFL_0                         (0x00000100UL)
#define ETH_MAC_MACSTSR_RFFL_1                         (0x00000200UL)
#define ETH_MAC_MACSTSR_MTEA_POS                       (16U)
#define ETH_MAC_MACSTSR_MTEA                           (0x00010000UL)
#define ETH_MAC_MACSTSR_MTS_POS                        (17U)
#define ETH_MAC_MACSTSR_MTS                            (0x00060000UL)
#define ETH_MAC_MACSTSR_MTS_0                          (0x00020000UL)
#define ETH_MAC_MACSTSR_MTS_1                          (0x00040000UL)
#define ETH_MAC_MACSTSR_MTP_POS                        (19U)
#define ETH_MAC_MACSTSR_MTP                            (0x00080000UL)
#define ETH_MAC_MACSTSR_TFRS_POS                       (20U)
#define ETH_MAC_MACSTSR_TFRS                           (0x00300000UL)
#define ETH_MAC_MACSTSR_TFRS_0                         (0x00100000UL)
#define ETH_MAC_MACSTSR_TFRS_1                         (0x00200000UL)
#define ETH_MAC_MACSTSR_TFWA_POS                       (22U)
#define ETH_MAC_MACSTSR_TFWA                           (0x00400000UL)
#define ETH_MAC_MACSTSR_TFNE_POS                       (24U)
#define ETH_MAC_MACSTSR_TFNE                           (0x01000000UL)
#define ETH_MAC_MACSTSR_TFF_POS                        (25U)
#define ETH_MAC_MACSTSR_TFF                            (0x02000000UL)

/*  Bit definition for ETH_MAC_RTWKFFR register  */
#define ETH_MAC_RTWKFFR_WKUPFRMFT                      (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_PMTCTLR register  */
#define ETH_MAC_PMTCTLR_PWDN_POS                       (0U)
#define ETH_MAC_PMTCTLR_PWDN                           (0x00000001UL)
#define ETH_MAC_PMTCTLR_MPEN_POS                       (1U)
#define ETH_MAC_PMTCTLR_MPEN                           (0x00000002UL)
#define ETH_MAC_PMTCTLR_WKEN_POS                       (2U)
#define ETH_MAC_PMTCTLR_WKEN                           (0x00000004UL)
#define ETH_MAC_PMTCTLR_MPFR_POS                       (5U)
#define ETH_MAC_PMTCTLR_MPFR                           (0x00000020UL)
#define ETH_MAC_PMTCTLR_WKFR_POS                       (6U)
#define ETH_MAC_PMTCTLR_WKFR                           (0x00000040UL)
#define ETH_MAC_PMTCTLR_GLUB_POS                       (9U)
#define ETH_MAC_PMTCTLR_GLUB                           (0x00000200UL)
#define ETH_MAC_PMTCTLR_RTWKTR_POS                     (10U)
#define ETH_MAC_PMTCTLR_RTWKTR                         (0x00000400UL)
#define ETH_MAC_PMTCTLR_RTWKPT_POS                     (24U)
#define ETH_MAC_PMTCTLR_RTWKPT                         (0x07000000UL)
#define ETH_MAC_PMTCTLR_RTWKPT_0                       (0x01000000UL)
#define ETH_MAC_PMTCTLR_RTWKPT_1                       (0x02000000UL)
#define ETH_MAC_PMTCTLR_RTWKPT_2                       (0x04000000UL)
#define ETH_MAC_PMTCTLR_RTWKFR_POS                     (31U)
#define ETH_MAC_PMTCTLR_RTWKFR                         (0x80000000UL)

/*  Bit definition for ETH_MAC_INTSTSR register  */
#define ETH_MAC_INTSTSR_PMTIS_POS                      (3U)
#define ETH_MAC_INTSTSR_PMTIS                          (0x00000008UL)
#define ETH_MAC_INTSTSR_MMCIS_POS                      (4U)
#define ETH_MAC_INTSTSR_MMCIS                          (0x00000010UL)
#define ETH_MAC_INTSTSR_MMCRXIS_POS                    (5U)
#define ETH_MAC_INTSTSR_MMCRXIS                        (0x00000020UL)
#define ETH_MAC_INTSTSR_MMCTXIS_POS                    (6U)
#define ETH_MAC_INTSTSR_MMCTXIS                        (0x00000040UL)
#define ETH_MAC_INTSTSR_TSPIS_POS                      (9U)
#define ETH_MAC_INTSTSR_TSPIS                          (0x00000200UL)

/*  Bit definition for ETH_MAC_INTMSKR register  */
#define ETH_MAC_INTMSKR_PMTIM_POS                      (3U)
#define ETH_MAC_INTMSKR_PMTIM                          (0x00000008UL)
#define ETH_MAC_INTMSKR_TSPIM_POS                      (9U)
#define ETH_MAC_INTMSKR_TSPIM                          (0x00000200UL)

/*  Bit definition for ETH_MAC_MACADHR0 register  */
#define ETH_MAC_MACADHR0_ADDRH0_POS                    (0U)
#define ETH_MAC_MACADHR0_ADDRH0                        (0x0000FFFFUL)
#define ETH_MAC_MACADHR0_AE0_POS                       (31U)
#define ETH_MAC_MACADHR0_AE0                           (0x80000000UL)

/*  Bit definition for ETH_MAC_MACADLR0 register  */
#define ETH_MAC_MACADLR0_ADDRL0                        (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_MACADHR1 register  */
#define ETH_MAC_MACADHR1_ADDRH1_POS                    (0U)
#define ETH_MAC_MACADHR1_ADDRH1                        (0x0000FFFFUL)
#define ETH_MAC_MACADHR1_MBC1_POS                      (24U)
#define ETH_MAC_MACADHR1_MBC1                          (0x3F000000UL)
#define ETH_MAC_MACADHR1_MBC1_0                        (0x01000000UL)
#define ETH_MAC_MACADHR1_MBC1_1                        (0x02000000UL)
#define ETH_MAC_MACADHR1_MBC1_2                        (0x04000000UL)
#define ETH_MAC_MACADHR1_MBC1_3                        (0x08000000UL)
#define ETH_MAC_MACADHR1_MBC1_4                        (0x10000000UL)
#define ETH_MAC_MACADHR1_MBC1_5                        (0x20000000UL)
#define ETH_MAC_MACADHR1_SA1_POS                       (30U)
#define ETH_MAC_MACADHR1_SA1                           (0x40000000UL)
#define ETH_MAC_MACADHR1_AE1_POS                       (31U)
#define ETH_MAC_MACADHR1_AE1                           (0x80000000UL)

/*  Bit definition for ETH_MAC_MACADLR1 register  */
#define ETH_MAC_MACADLR1_ADDRL1                        (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_MACADHR2 register  */
#define ETH_MAC_MACADHR2_ADDRH2_POS                    (0U)
#define ETH_MAC_MACADHR2_ADDRH2                        (0x0000FFFFUL)
#define ETH_MAC_MACADHR2_MBC2_POS                      (24U)
#define ETH_MAC_MACADHR2_MBC2                          (0x3F000000UL)
#define ETH_MAC_MACADHR2_MBC2_0                        (0x01000000UL)
#define ETH_MAC_MACADHR2_MBC2_1                        (0x02000000UL)
#define ETH_MAC_MACADHR2_MBC2_2                        (0x04000000UL)
#define ETH_MAC_MACADHR2_MBC2_3                        (0x08000000UL)
#define ETH_MAC_MACADHR2_MBC2_4                        (0x10000000UL)
#define ETH_MAC_MACADHR2_MBC2_5                        (0x20000000UL)
#define ETH_MAC_MACADHR2_SA2_POS                       (30U)
#define ETH_MAC_MACADHR2_SA2                           (0x40000000UL)
#define ETH_MAC_MACADHR2_AE2_POS                       (31U)
#define ETH_MAC_MACADHR2_AE2                           (0x80000000UL)

/*  Bit definition for ETH_MAC_MACADLR2 register  */
#define ETH_MAC_MACADLR2_ADDRL2                        (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_MACADHR3 register  */
#define ETH_MAC_MACADHR3_ADDRH3_POS                    (0U)
#define ETH_MAC_MACADHR3_ADDRH3                        (0x0000FFFFUL)
#define ETH_MAC_MACADHR3_MBC3_POS                      (24U)
#define ETH_MAC_MACADHR3_MBC3                          (0x3F000000UL)
#define ETH_MAC_MACADHR3_MBC3_0                        (0x01000000UL)
#define ETH_MAC_MACADHR3_MBC3_1                        (0x02000000UL)
#define ETH_MAC_MACADHR3_MBC3_2                        (0x04000000UL)
#define ETH_MAC_MACADHR3_MBC3_3                        (0x08000000UL)
#define ETH_MAC_MACADHR3_MBC3_4                        (0x10000000UL)
#define ETH_MAC_MACADHR3_MBC3_5                        (0x20000000UL)
#define ETH_MAC_MACADHR3_SA3_POS                       (30U)
#define ETH_MAC_MACADHR3_SA3                           (0x40000000UL)
#define ETH_MAC_MACADHR3_AE3_POS                       (31U)
#define ETH_MAC_MACADHR3_AE3                           (0x80000000UL)

/*  Bit definition for ETH_MAC_MACADLR3 register  */
#define ETH_MAC_MACADLR3_ADDRL3                        (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_MACADHR4 register  */
#define ETH_MAC_MACADHR4_ADDRH4_POS                    (0U)
#define ETH_MAC_MACADHR4_ADDRH4                        (0x0000FFFFUL)
#define ETH_MAC_MACADHR4_MBC4_POS                      (24U)
#define ETH_MAC_MACADHR4_MBC4                          (0x3F000000UL)
#define ETH_MAC_MACADHR4_MBC4_0                        (0x01000000UL)
#define ETH_MAC_MACADHR4_MBC4_1                        (0x02000000UL)
#define ETH_MAC_MACADHR4_MBC4_2                        (0x04000000UL)
#define ETH_MAC_MACADHR4_MBC4_3                        (0x08000000UL)
#define ETH_MAC_MACADHR4_MBC4_4                        (0x10000000UL)
#define ETH_MAC_MACADHR4_MBC4_5                        (0x20000000UL)
#define ETH_MAC_MACADHR4_SA4_POS                       (30U)
#define ETH_MAC_MACADHR4_SA4                           (0x40000000UL)
#define ETH_MAC_MACADHR4_AE4_POS                       (31U)
#define ETH_MAC_MACADHR4_AE4                           (0x80000000UL)

/*  Bit definition for ETH_MAC_MACADLR4 register  */
#define ETH_MAC_MACADLR4_ADDRL4                        (0xFFFFFFFFUL)

/*  Bit definition for ETH_MMC_MMCCTLR register  */
#define ETH_MMC_MMCCTLR_CRST_POS                       (0U)
#define ETH_MMC_MMCCTLR_CRST                           (0x00000001UL)
#define ETH_MMC_MMCCTLR_COS_POS                        (1U)
#define ETH_MMC_MMCCTLR_COS                            (0x00000002UL)
#define ETH_MMC_MMCCTLR_ROR_POS                        (2U)
#define ETH_MMC_MMCCTLR_ROR                            (0x00000004UL)
#define ETH_MMC_MMCCTLR_MCF_POS                        (3U)
#define ETH_MMC_MMCCTLR_MCF                            (0x00000008UL)
#define ETH_MMC_MMCCTLR_MCPSET_POS                     (4U)
#define ETH_MMC_MMCCTLR_MCPSET                         (0x00000010UL)
#define ETH_MMC_MMCCTLR_MCPSEL_POS                     (5U)
#define ETH_MMC_MMCCTLR_MCPSEL                         (0x00000020UL)

/*  Bit definition for ETH_MMC_REVSTSR register  */
#define ETH_MMC_REVSTSR_RXBGIS_POS                     (3U)
#define ETH_MMC_REVSTSR_RXBGIS                         (0x00000008UL)
#define ETH_MMC_REVSTSR_RXMGIS_POS                     (4U)
#define ETH_MMC_REVSTSR_RXMGIS                         (0x00000010UL)
#define ETH_MMC_REVSTSR_RXCEIS_POS                     (5U)
#define ETH_MMC_REVSTSR_RXCEIS                         (0x00000020UL)
#define ETH_MMC_REVSTSR_RXAEIS_POS                     (6U)
#define ETH_MMC_REVSTSR_RXAEIS                         (0x00000040UL)
#define ETH_MMC_REVSTSR_RXREIS_POS                     (7U)
#define ETH_MMC_REVSTSR_RXREIS                         (0x00000080UL)
#define ETH_MMC_REVSTSR_RXUGIS_POS                     (17U)
#define ETH_MMC_REVSTSR_RXUGIS                         (0x00020000UL)
#define ETH_MMC_REVSTSR_RXLEIS_POS                     (18U)
#define ETH_MMC_REVSTSR_RXLEIS                         (0x00040000UL)
#define ETH_MMC_REVSTSR_RXOEIS_POS                     (19U)
#define ETH_MMC_REVSTSR_RXOEIS                         (0x00080000UL)

/*  Bit definition for ETH_MMC_TRSSTSR register  */
#define ETH_MMC_TRSSTSR_TXBGIS_POS                     (2U)
#define ETH_MMC_TRSSTSR_TXBGIS                         (0x00000004UL)
#define ETH_MMC_TRSSTSR_TXMGIS_POS                     (3U)
#define ETH_MMC_TRSSTSR_TXMGIS                         (0x00000008UL)
#define ETH_MMC_TRSSTSR_TXDEEIS_POS                    (16U)
#define ETH_MMC_TRSSTSR_TXDEEIS                        (0x00010000UL)
#define ETH_MMC_TRSSTSR_TXLCEIS_POS                    (17U)
#define ETH_MMC_TRSSTSR_TXLCEIS                        (0x00020000UL)
#define ETH_MMC_TRSSTSR_TXECEIS_POS                    (18U)
#define ETH_MMC_TRSSTSR_TXECEIS                        (0x00040000UL)
#define ETH_MMC_TRSSTSR_TXCAEIS_POS                    (19U)
#define ETH_MMC_TRSSTSR_TXCAEIS                        (0x00080000UL)
#define ETH_MMC_TRSSTSR_TXUGIS_POS                     (21U)
#define ETH_MMC_TRSSTSR_TXUGIS                         (0x00200000UL)
#define ETH_MMC_TRSSTSR_TXEDEIS_POS                    (22U)
#define ETH_MMC_TRSSTSR_TXEDEIS                        (0x00400000UL)

/*  Bit definition for ETH_MMC_RITCTLR register  */
#define ETH_MMC_RITCTLR_RXBGIM_POS                     (3U)
#define ETH_MMC_RITCTLR_RXBGIM                         (0x00000008UL)
#define ETH_MMC_RITCTLR_RXMGIM_POS                     (4U)
#define ETH_MMC_RITCTLR_RXMGIM                         (0x00000010UL)
#define ETH_MMC_RITCTLR_RXCEIM_POS                     (5U)
#define ETH_MMC_RITCTLR_RXCEIM                         (0x00000020UL)
#define ETH_MMC_RITCTLR_RXAEIM_POS                     (6U)
#define ETH_MMC_RITCTLR_RXAEIM                         (0x00000040UL)
#define ETH_MMC_RITCTLR_RXREIM_POS                     (7U)
#define ETH_MMC_RITCTLR_RXREIM                         (0x00000080UL)
#define ETH_MMC_RITCTLR_RXUGIM_POS                     (17U)
#define ETH_MMC_RITCTLR_RXUGIM                         (0x00020000UL)
#define ETH_MMC_RITCTLR_RXLEIM_POS                     (18U)
#define ETH_MMC_RITCTLR_RXLEIM                         (0x00040000UL)
#define ETH_MMC_RITCTLR_RXOEIM_POS                     (19U)
#define ETH_MMC_RITCTLR_RXOEIM                         (0x00080000UL)

/*  Bit definition for ETH_MMC_TITCTLR register  */
#define ETH_MMC_TITCTLR_TXBGIM_POS                     (2U)
#define ETH_MMC_TITCTLR_TXBGIM                         (0x00000004UL)
#define ETH_MMC_TITCTLR_TXMGIM_POS                     (3U)
#define ETH_MMC_TITCTLR_TXMGIM                         (0x00000008UL)
#define ETH_MMC_TITCTLR_TXDEEIM_POS                    (16U)
#define ETH_MMC_TITCTLR_TXDEEIM                        (0x00010000UL)
#define ETH_MMC_TITCTLR_TXLCEIM_POS                    (17U)
#define ETH_MMC_TITCTLR_TXLCEIM                        (0x00020000UL)
#define ETH_MMC_TITCTLR_TXECEIM_POS                    (18U)
#define ETH_MMC_TITCTLR_TXECEIM                        (0x00040000UL)
#define ETH_MMC_TITCTLR_TXCAEIM_POS                    (19U)
#define ETH_MMC_TITCTLR_TXCAEIM                        (0x00080000UL)
#define ETH_MMC_TITCTLR_TXUGIM_POS                     (21U)
#define ETH_MMC_TITCTLR_TXUGIM                         (0x00200000UL)
#define ETH_MMC_TITCTLR_TXEDEIM_POS                    (22U)
#define ETH_MMC_TITCTLR_TXEDEIM                        (0x00400000UL)

/*  Bit definition for ETH_MMC_TXBRGFR register  */
#define ETH_MMC_TXBRGFR_TXBRGCNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXMUGFR register  */
#define ETH_MMC_TXMUGFR_TXMUGCNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXDEEFR register  */
#define ETH_MMC_TXDEEFR_TXDEECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXLCEFR register  */
#define ETH_MMC_TXLCEFR_TXLCECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXECEFR register  */
#define ETH_MMC_TXECEFR_TXECECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXCAEFR register  */
#define ETH_MMC_TXCAEFR_TXCAECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXUNGFR register  */
#define ETH_MMC_TXUNGFR_TXUNGCNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_TXEDEFR register  */
#define ETH_MMC_TXEDEFR_TXEDECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXBRGFR register  */
#define ETH_MMC_RXBRGFR_RXBRGCNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXMUGFR register  */
#define ETH_MMC_RXMUGFR_RXMUGCNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXCREFR register  */
#define ETH_MMC_RXCREFR_RXCRECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXALEFR register  */
#define ETH_MMC_RXALEFR_RXALECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXRUEFR register  */
#define ETH_MMC_RXRUEFR_RXRUECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXUNGFR register  */
#define ETH_MMC_RXUNGFR_RXUNGCNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXLEEFR register  */
#define ETH_MMC_RXLEEFR_RXLEECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MMC_RXOREFR register  */
#define ETH_MMC_RXOREFR_RXORECNT                       (0x0000FFFFUL)

/*  Bit definition for ETH_MAC_L34CTLR register  */
#define ETH_MAC_L34CTLR_L3PEN_POS                      (0U)
#define ETH_MAC_L34CTLR_L3PEN                          (0x00000001UL)
#define ETH_MAC_L34CTLR_L3SAM_POS                      (2U)
#define ETH_MAC_L34CTLR_L3SAM                          (0x00000004UL)
#define ETH_MAC_L34CTLR_L3SAIM_POS                     (3U)
#define ETH_MAC_L34CTLR_L3SAIM                         (0x00000008UL)
#define ETH_MAC_L34CTLR_L3DAM_POS                      (4U)
#define ETH_MAC_L34CTLR_L3DAM                          (0x00000010UL)
#define ETH_MAC_L34CTLR_L3DAIM_POS                     (5U)
#define ETH_MAC_L34CTLR_L3DAIM                         (0x00000020UL)
#define ETH_MAC_L34CTLR_L3HSBM_POS                     (6U)
#define ETH_MAC_L34CTLR_L3HSBM                         (0x000007C0UL)
#define ETH_MAC_L34CTLR_L3HSBM_0                       (0x00000040UL)
#define ETH_MAC_L34CTLR_L3HSBM_1                       (0x00000080UL)
#define ETH_MAC_L34CTLR_L3HSBM_2                       (0x00000100UL)
#define ETH_MAC_L34CTLR_L3HSBM_3                       (0x00000200UL)
#define ETH_MAC_L34CTLR_L3HSBM_4                       (0x00000400UL)
#define ETH_MAC_L34CTLR_L3HDBM_POS                     (11U)
#define ETH_MAC_L34CTLR_L3HDBM                         (0x0000F800UL)
#define ETH_MAC_L34CTLR_L3HDBM_0                       (0x00000800UL)
#define ETH_MAC_L34CTLR_L3HDBM_1                       (0x00001000UL)
#define ETH_MAC_L34CTLR_L3HDBM_2                       (0x00002000UL)
#define ETH_MAC_L34CTLR_L3HDBM_3                       (0x00004000UL)
#define ETH_MAC_L34CTLR_L3HDBM_4                       (0x00008000UL)
#define ETH_MAC_L34CTLR_L4PEN_POS                      (16U)
#define ETH_MAC_L34CTLR_L4PEN                          (0x00010000UL)
#define ETH_MAC_L34CTLR_L4SPM_POS                      (18U)
#define ETH_MAC_L34CTLR_L4SPM                          (0x00040000UL)
#define ETH_MAC_L34CTLR_L4SPIM_POS                     (19U)
#define ETH_MAC_L34CTLR_L4SPIM                         (0x00080000UL)
#define ETH_MAC_L34CTLR_L4DPM_POS                      (20U)
#define ETH_MAC_L34CTLR_L4DPM                          (0x00100000UL)
#define ETH_MAC_L34CTLR_L4DPIM_POS                     (21U)
#define ETH_MAC_L34CTLR_L4DPIM                         (0x00200000UL)

/*  Bit definition for ETH_MAC_L4PORTR register  */
#define ETH_MAC_L4PORTR_L4SPVAL_POS                    (0U)
#define ETH_MAC_L4PORTR_L4SPVAL                        (0x0000FFFFUL)
#define ETH_MAC_L4PORTR_L4DPVAL_POS                    (16U)
#define ETH_MAC_L4PORTR_L4DPVAL                        (0xFFFF0000UL)

/*  Bit definition for ETH_MAC_L3ADDRR0 register  */
#define ETH_MAC_L3ADDRR0_L3ADDR0                       (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_L3ADDRR1 register  */
#define ETH_MAC_L3ADDRR1_L3ADDR2                       (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_L3ADDRR2 register  */
#define ETH_MAC_L3ADDRR2_L3ADDR2                       (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_L3ADDRR3 register  */
#define ETH_MAC_L3ADDRR3_L3ADDR3                       (0xFFFFFFFFUL)

/*  Bit definition for ETH_MAC_VTACTLR register  */
#define ETH_MAC_VTACTLR_VLANV_POS                      (0U)
#define ETH_MAC_VTACTLR_VLANV                          (0x0000FFFFUL)
#define ETH_MAC_VTACTLR_VLANC_POS                      (16U)
#define ETH_MAC_VTACTLR_VLANC                          (0x00030000UL)
#define ETH_MAC_VTACTLR_VLANC_0                        (0x00010000UL)
#define ETH_MAC_VTACTLR_VLANC_1                        (0x00020000UL)
#define ETH_MAC_VTACTLR_VLANS_POS                      (18U)
#define ETH_MAC_VTACTLR_VLANS                          (0x00040000UL)

/*  Bit definition for ETH_MAC_VLAHTBR register  */
#define ETH_MAC_VLAHTBR_VLHT                           (0x0000FFFFUL)

/*  Bit definition for ETH_PTP_TSPCTLR register  */
#define ETH_PTP_TSPCTLR_TSPEN_POS                      (0U)
#define ETH_PTP_TSPCTLR_TSPEN                          (0x00000001UL)
#define ETH_PTP_TSPCTLR_TSPUPSEL_POS                   (1U)
#define ETH_PTP_TSPCTLR_TSPUPSEL                       (0x00000002UL)
#define ETH_PTP_TSPCTLR_TSPINI_POS                     (2U)
#define ETH_PTP_TSPCTLR_TSPINI                         (0x00000004UL)
#define ETH_PTP_TSPCTLR_TSPUP_POS                      (3U)
#define ETH_PTP_TSPCTLR_TSPUP                          (0x00000008UL)
#define ETH_PTP_TSPCTLR_TSPINT_POS                     (4U)
#define ETH_PTP_TSPCTLR_TSPINT                         (0x00000010UL)
#define ETH_PTP_TSPCTLR_TSPADUP_POS                    (5U)
#define ETH_PTP_TSPCTLR_TSPADUP                        (0x00000020UL)
#define ETH_PTP_TSPCTLR_TSPEALL_POS                    (8U)
#define ETH_PTP_TSPCTLR_TSPEALL                        (0x00000100UL)
#define ETH_PTP_TSPCTLR_TSPSSR_POS                     (9U)
#define ETH_PTP_TSPCTLR_TSPSSR                         (0x00000200UL)
#define ETH_PTP_TSPCTLR_TSPVER_POS                     (10U)
#define ETH_PTP_TSPCTLR_TSPVER                         (0x00000400UL)
#define ETH_PTP_TSPCTLR_TSPOVETH_POS                   (11U)
#define ETH_PTP_TSPCTLR_TSPOVETH                       (0x00000800UL)
#define ETH_PTP_TSPCTLR_TSPOVIPV6_POS                  (12U)
#define ETH_PTP_TSPCTLR_TSPOVIPV6                      (0x00001000UL)
#define ETH_PTP_TSPCTLR_TSPOVIPV4_POS                  (13U)
#define ETH_PTP_TSPCTLR_TSPOVIPV4                      (0x00002000UL)
#define ETH_PTP_TSPCTLR_TSPMTSEL_POS                   (14U)
#define ETH_PTP_TSPCTLR_TSPMTSEL                       (0x0003C000UL)
#define ETH_PTP_TSPCTLR_TSPMTSEL_0                     (0x00004000UL)
#define ETH_PTP_TSPCTLR_TSPMTSEL_1                     (0x00008000UL)
#define ETH_PTP_TSPCTLR_TSPMTSEL_2                     (0x00010000UL)
#define ETH_PTP_TSPCTLR_TSPMTSEL_3                     (0x00020000UL)
#define ETH_PTP_TSPCTLR_TSPADF_POS                     (18U)
#define ETH_PTP_TSPCTLR_TSPADF                         (0x00040000UL)

/*  Bit definition for ETH_PTP_TSPNSAR register  */
#define ETH_PTP_TSPNSAR_TSPNSEADD                      (0x000000FFUL)

/*  Bit definition for ETH_PTP_TMSSECR register  */
#define ETH_PTP_TMSSECR_TSPSYSSEC                      (0xFFFFFFFFUL)

/*  Bit definition for ETH_PTP_TMSNSER register  */
#define ETH_PTP_TMSNSER_TSPSYSNSEC                     (0x7FFFFFFFUL)

/*  Bit definition for ETH_PTP_TMUSECR register  */
#define ETH_PTP_TMUSECR_TSPUPSEC                       (0xFFFFFFFFUL)

/*  Bit definition for ETH_PTP_TMUNSER register  */
#define ETH_PTP_TMUNSER_TSPUPNSEC_POS                  (0U)
#define ETH_PTP_TMUNSER_TSPUPNSEC                      (0x7FFFFFFFUL)
#define ETH_PTP_TMUNSER_TSPUPNS_POS                    (31U)
#define ETH_PTP_TMUNSER_TSPUPNS                        (0x80000000UL)

/*  Bit definition for ETH_PTP_TSPADDR register  */
#define ETH_PTP_TSPADDR_TSPADD                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_PTP_TMTSECR0 register  */
#define ETH_PTP_TMTSECR0_TSPTAGSEC0                    (0xFFFFFFFFUL)

/*  Bit definition for ETH_PTP_TMTNSER0 register  */
#define ETH_PTP_TMTNSER0_TSPTAGNSEC0                   (0x7FFFFFFFUL)

/*  Bit definition for ETH_PTP_TSPSTSR register  */
#define ETH_PTP_TSPSTSR_TSOVF_POS                      (0U)
#define ETH_PTP_TSPSTSR_TSOVF                          (0x00000001UL)
#define ETH_PTP_TSPSTSR_TSTAR0_POS                     (1U)
#define ETH_PTP_TSPSTSR_TSTAR0                         (0x00000002UL)
#define ETH_PTP_TSPSTSR_TSERR0_POS                     (3U)
#define ETH_PTP_TSPSTSR_TSERR0                         (0x00000008UL)
#define ETH_PTP_TSPSTSR_TSTAR1_POS                     (4U)
#define ETH_PTP_TSPSTSR_TSTAR1                         (0x00000010UL)
#define ETH_PTP_TSPSTSR_TSERR1_POS                     (5U)
#define ETH_PTP_TSPSTSR_TSERR1                         (0x00000020UL)

/*  Bit definition for ETH_PTP_PPSCTLR register  */
#define ETH_PTP_PPSCTLR_PPSFRE0_POS                    (0U)
#define ETH_PTP_PPSCTLR_PPSFRE0                        (0x0000000FUL)
#define ETH_PTP_PPSCTLR_PPSFRE0_0                      (0x00000001UL)
#define ETH_PTP_PPSCTLR_PPSFRE0_1                      (0x00000002UL)
#define ETH_PTP_PPSCTLR_PPSFRE0_2                      (0x00000004UL)
#define ETH_PTP_PPSCTLR_PPSFRE0_3                      (0x00000008UL)
#define ETH_PTP_PPSCTLR_PPSOMD_POS                     (4U)
#define ETH_PTP_PPSCTLR_PPSOMD                         (0x00000010UL)
#define ETH_PTP_PPSCTLR_TT0SEL_POS                     (5U)
#define ETH_PTP_PPSCTLR_TT0SEL                         (0x00000060UL)
#define ETH_PTP_PPSCTLR_TT0SEL_0                       (0x00000020UL)
#define ETH_PTP_PPSCTLR_TT0SEL_1                       (0x00000040UL)
#define ETH_PTP_PPSCTLR_PPSFRE1_POS                    (8U)
#define ETH_PTP_PPSCTLR_PPSFRE1                        (0x00000700UL)
#define ETH_PTP_PPSCTLR_PPSFRE1_0                      (0x00000100UL)
#define ETH_PTP_PPSCTLR_PPSFRE1_1                      (0x00000200UL)
#define ETH_PTP_PPSCTLR_PPSFRE1_2                      (0x00000400UL)
#define ETH_PTP_PPSCTLR_TT1SEL_POS                     (13U)
#define ETH_PTP_PPSCTLR_TT1SEL                         (0x00006000UL)
#define ETH_PTP_PPSCTLR_TT1SEL_0                       (0x00002000UL)
#define ETH_PTP_PPSCTLR_TT1SEL_1                       (0x00004000UL)

/*  Bit definition for ETH_PTP_TMTSECR1 register  */
#define ETH_PTP_TMTSECR1_TSPTAGSEC1                    (0xFFFFFFFFUL)

/*  Bit definition for ETH_PTP_TMTNSER1 register  */
#define ETH_PTP_TMTNSER1_TSPTAGNSEC1                   (0x7FFFFFFFUL)

/*  Bit definition for ETH_DMA_BUSMODR register  */
#define ETH_DMA_BUSMODR_SWR_POS                        (0U)
#define ETH_DMA_BUSMODR_SWR                            (0x00000001UL)
#define ETH_DMA_BUSMODR_DMAA_POS                       (1U)
#define ETH_DMA_BUSMODR_DMAA                           (0x00000002UL)
#define ETH_DMA_BUSMODR_DSL_POS                        (2U)
#define ETH_DMA_BUSMODR_DSL                            (0x0000007CUL)
#define ETH_DMA_BUSMODR_DSL_0                          (0x00000004UL)
#define ETH_DMA_BUSMODR_DSL_1                          (0x00000008UL)
#define ETH_DMA_BUSMODR_DSL_2                          (0x00000010UL)
#define ETH_DMA_BUSMODR_DSL_3                          (0x00000020UL)
#define ETH_DMA_BUSMODR_DSL_4                          (0x00000040UL)
#define ETH_DMA_BUSMODR_DSEN_POS                       (7U)
#define ETH_DMA_BUSMODR_DSEN                           (0x00000080UL)
#define ETH_DMA_BUSMODR_TPBL_POS                       (8U)
#define ETH_DMA_BUSMODR_TPBL                           (0x00003F00UL)
#define ETH_DMA_BUSMODR_TPBL_0                         (0x00000100UL)
#define ETH_DMA_BUSMODR_TPBL_1                         (0x00000200UL)
#define ETH_DMA_BUSMODR_TPBL_2                         (0x00000400UL)
#define ETH_DMA_BUSMODR_TPBL_3                         (0x00000800UL)
#define ETH_DMA_BUSMODR_TPBL_4                         (0x00001000UL)
#define ETH_DMA_BUSMODR_TPBL_5                         (0x00002000UL)
#define ETH_DMA_BUSMODR_PRAT_POS                       (14U)
#define ETH_DMA_BUSMODR_PRAT                           (0x0000C000UL)
#define ETH_DMA_BUSMODR_PRAT_0                         (0x00004000UL)
#define ETH_DMA_BUSMODR_PRAT_1                         (0x00008000UL)
#define ETH_DMA_BUSMODR_FBST_POS                       (16U)
#define ETH_DMA_BUSMODR_FBST                           (0x00010000UL)
#define ETH_DMA_BUSMODR_RPBL_POS                       (17U)
#define ETH_DMA_BUSMODR_RPBL                           (0x007E0000UL)
#define ETH_DMA_BUSMODR_RPBL_0                         (0x00020000UL)
#define ETH_DMA_BUSMODR_RPBL_1                         (0x00040000UL)
#define ETH_DMA_BUSMODR_RPBL_2                         (0x00080000UL)
#define ETH_DMA_BUSMODR_RPBL_3                         (0x00100000UL)
#define ETH_DMA_BUSMODR_RPBL_4                         (0x00200000UL)
#define ETH_DMA_BUSMODR_RPBL_5                         (0x00400000UL)
#define ETH_DMA_BUSMODR_SPBL_POS                       (23U)
#define ETH_DMA_BUSMODR_SPBL                           (0x00800000UL)
#define ETH_DMA_BUSMODR_M8PBL_POS                      (24U)
#define ETH_DMA_BUSMODR_M8PBL                          (0x01000000UL)
#define ETH_DMA_BUSMODR_AAL_POS                        (25U)
#define ETH_DMA_BUSMODR_AAL                            (0x02000000UL)
#define ETH_DMA_BUSMODR_MBST_POS                       (26U)
#define ETH_DMA_BUSMODR_MBST                           (0x04000000UL)
#define ETH_DMA_BUSMODR_TXPR_POS                       (27U)
#define ETH_DMA_BUSMODR_TXPR                           (0x08000000UL)

/*  Bit definition for ETH_DMA_TXPOLLR register  */
#define ETH_DMA_TXPOLLR_TXPOLL                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_RXPOLLR register  */
#define ETH_DMA_RXPOLLR_RXPOLL                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_RXDLADR register  */
#define ETH_DMA_RXDLADR_RXDLAD                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_TXDLADR register  */
#define ETH_DMA_TXDLADR_TXDLAD                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_DMASTSR register  */
#define ETH_DMA_DMASTSR_TIS_POS                        (0U)
#define ETH_DMA_DMASTSR_TIS                            (0x00000001UL)
#define ETH_DMA_DMASTSR_TSS_POS                        (1U)
#define ETH_DMA_DMASTSR_TSS                            (0x00000002UL)
#define ETH_DMA_DMASTSR_TUS_POS                        (2U)
#define ETH_DMA_DMASTSR_TUS                            (0x00000004UL)
#define ETH_DMA_DMASTSR_TJS_POS                        (3U)
#define ETH_DMA_DMASTSR_TJS                            (0x00000008UL)
#define ETH_DMA_DMASTSR_OVS_POS                        (4U)
#define ETH_DMA_DMASTSR_OVS                            (0x00000010UL)
#define ETH_DMA_DMASTSR_UNS_POS                        (5U)
#define ETH_DMA_DMASTSR_UNS                            (0x00000020UL)
#define ETH_DMA_DMASTSR_RIS_POS                        (6U)
#define ETH_DMA_DMASTSR_RIS                            (0x00000040UL)
#define ETH_DMA_DMASTSR_RUS_POS                        (7U)
#define ETH_DMA_DMASTSR_RUS                            (0x00000080UL)
#define ETH_DMA_DMASTSR_RSS_POS                        (8U)
#define ETH_DMA_DMASTSR_RSS                            (0x00000100UL)
#define ETH_DMA_DMASTSR_RWS_POS                        (9U)
#define ETH_DMA_DMASTSR_RWS                            (0x00000200UL)
#define ETH_DMA_DMASTSR_ETS_POS                        (10U)
#define ETH_DMA_DMASTSR_ETS                            (0x00000400UL)
#define ETH_DMA_DMASTSR_FBS_POS                        (13U)
#define ETH_DMA_DMASTSR_FBS                            (0x00002000UL)
#define ETH_DMA_DMASTSR_ERS_POS                        (14U)
#define ETH_DMA_DMASTSR_ERS                            (0x00004000UL)
#define ETH_DMA_DMASTSR_AIS_POS                        (15U)
#define ETH_DMA_DMASTSR_AIS                            (0x00008000UL)
#define ETH_DMA_DMASTSR_NIS_POS                        (16U)
#define ETH_DMA_DMASTSR_NIS                            (0x00010000UL)
#define ETH_DMA_DMASTSR_RSTS_POS                       (17U)
#define ETH_DMA_DMASTSR_RSTS                           (0x000E0000UL)
#define ETH_DMA_DMASTSR_RSTS_0                         (0x00020000UL)
#define ETH_DMA_DMASTSR_RSTS_1                         (0x00040000UL)
#define ETH_DMA_DMASTSR_RSTS_2                         (0x00080000UL)
#define ETH_DMA_DMASTSR_TSTS_POS                       (20U)
#define ETH_DMA_DMASTSR_TSTS                           (0x00700000UL)
#define ETH_DMA_DMASTSR_TSTS_0                         (0x00100000UL)
#define ETH_DMA_DMASTSR_TSTS_1                         (0x00200000UL)
#define ETH_DMA_DMASTSR_TSTS_2                         (0x00400000UL)
#define ETH_DMA_DMASTSR_EBUS_POS                       (23U)
#define ETH_DMA_DMASTSR_EBUS                           (0x03800000UL)
#define ETH_DMA_DMASTSR_EBUS_0                         (0x00800000UL)
#define ETH_DMA_DMASTSR_EBUS_1                         (0x01000000UL)
#define ETH_DMA_DMASTSR_EBUS_2                         (0x02000000UL)
#define ETH_DMA_DMASTSR_MMCS_POS                       (27U)
#define ETH_DMA_DMASTSR_MMCS                           (0x08000000UL)
#define ETH_DMA_DMASTSR_PMTS_POS                       (28U)
#define ETH_DMA_DMASTSR_PMTS                           (0x10000000UL)
#define ETH_DMA_DMASTSR_PTPS_POS                       (29U)
#define ETH_DMA_DMASTSR_PTPS                           (0x20000000UL)

/*  Bit definition for ETH_DMA_OPRMODR register  */
#define ETH_DMA_OPRMODR_STR_POS                        (1U)
#define ETH_DMA_OPRMODR_STR                            (0x00000002UL)
#define ETH_DMA_OPRMODR_OSF_POS                        (2U)
#define ETH_DMA_OPRMODR_OSF                            (0x00000004UL)
#define ETH_DMA_OPRMODR_RTC_POS                        (3U)
#define ETH_DMA_OPRMODR_RTC                            (0x00000018UL)
#define ETH_DMA_OPRMODR_RTC_0                          (0x00000008UL)
#define ETH_DMA_OPRMODR_RTC_1                          (0x00000010UL)
#define ETH_DMA_OPRMODR_DGF_POS                        (5U)
#define ETH_DMA_OPRMODR_DGF                            (0x00000020UL)
#define ETH_DMA_OPRMODR_FUF_POS                        (6U)
#define ETH_DMA_OPRMODR_FUF                            (0x00000040UL)
#define ETH_DMA_OPRMODR_FEF_POS                        (7U)
#define ETH_DMA_OPRMODR_FEF                            (0x00000080UL)
#define ETH_DMA_OPRMODR_STT_POS                        (13U)
#define ETH_DMA_OPRMODR_STT                            (0x00002000UL)
#define ETH_DMA_OPRMODR_TTC_POS                        (14U)
#define ETH_DMA_OPRMODR_TTC                            (0x0001C000UL)
#define ETH_DMA_OPRMODR_TTC_0                          (0x00004000UL)
#define ETH_DMA_OPRMODR_TTC_1                          (0x00008000UL)
#define ETH_DMA_OPRMODR_TTC_2                          (0x00010000UL)
#define ETH_DMA_OPRMODR_FTF_POS                        (20U)
#define ETH_DMA_OPRMODR_FTF                            (0x00100000UL)
#define ETH_DMA_OPRMODR_TSF_POS                        (21U)
#define ETH_DMA_OPRMODR_TSF                            (0x00200000UL)
#define ETH_DMA_OPRMODR_DFRF_POS                       (24U)
#define ETH_DMA_OPRMODR_DFRF                           (0x01000000UL)
#define ETH_DMA_OPRMODR_RSF_POS                        (25U)
#define ETH_DMA_OPRMODR_RSF                            (0x02000000UL)
#define ETH_DMA_OPRMODR_DTCOE_POS                      (26U)
#define ETH_DMA_OPRMODR_DTCOE                          (0x04000000UL)

/*  Bit definition for ETH_DMA_INTENAR register  */
#define ETH_DMA_INTENAR_TIE_POS                        (0U)
#define ETH_DMA_INTENAR_TIE                            (0x00000001UL)
#define ETH_DMA_INTENAR_TSE_POS                        (1U)
#define ETH_DMA_INTENAR_TSE                            (0x00000002UL)
#define ETH_DMA_INTENAR_TUE_POS                        (2U)
#define ETH_DMA_INTENAR_TUE                            (0x00000004UL)
#define ETH_DMA_INTENAR_TJE_POS                        (3U)
#define ETH_DMA_INTENAR_TJE                            (0x00000008UL)
#define ETH_DMA_INTENAR_OVE_POS                        (4U)
#define ETH_DMA_INTENAR_OVE                            (0x00000010UL)
#define ETH_DMA_INTENAR_UNE_POS                        (5U)
#define ETH_DMA_INTENAR_UNE                            (0x00000020UL)
#define ETH_DMA_INTENAR_RIE_POS                        (6U)
#define ETH_DMA_INTENAR_RIE                            (0x00000040UL)
#define ETH_DMA_INTENAR_RUE_POS                        (7U)
#define ETH_DMA_INTENAR_RUE                            (0x00000080UL)
#define ETH_DMA_INTENAR_RSE_POS                        (8U)
#define ETH_DMA_INTENAR_RSE                            (0x00000100UL)
#define ETH_DMA_INTENAR_RWE_POS                        (9U)
#define ETH_DMA_INTENAR_RWE                            (0x00000200UL)
#define ETH_DMA_INTENAR_ETE_POS                        (10U)
#define ETH_DMA_INTENAR_ETE                            (0x00000400UL)
#define ETH_DMA_INTENAR_FBE_POS                        (13U)
#define ETH_DMA_INTENAR_FBE                            (0x00002000UL)
#define ETH_DMA_INTENAR_ERE_POS                        (14U)
#define ETH_DMA_INTENAR_ERE                            (0x00004000UL)
#define ETH_DMA_INTENAR_AIE_POS                        (15U)
#define ETH_DMA_INTENAR_AIE                            (0x00008000UL)
#define ETH_DMA_INTENAR_NIE_POS                        (16U)
#define ETH_DMA_INTENAR_NIE                            (0x00010000UL)

/*  Bit definition for ETH_DMA_RFRCNTR register  */
#define ETH_DMA_RFRCNTR_UNACNT_POS                     (0U)
#define ETH_DMA_RFRCNTR_UNACNT                         (0x0000FFFFUL)
#define ETH_DMA_RFRCNTR_UNAOVF_POS                     (16U)
#define ETH_DMA_RFRCNTR_UNAOVF                         (0x00010000UL)
#define ETH_DMA_RFRCNTR_OVFCNT_POS                     (17U)
#define ETH_DMA_RFRCNTR_OVFCNT                         (0x0FFE0000UL)
#define ETH_DMA_RFRCNTR_OVFOVF_POS                     (28U)
#define ETH_DMA_RFRCNTR_OVFOVF                         (0x10000000UL)

/*  Bit definition for ETH_DMA_REVWDTR register  */
#define ETH_DMA_REVWDTR_RIWT                           (0x000000FFUL)

/*  Bit definition for ETH_DMA_CHTXDER register  */
#define ETH_DMA_CHTXDER_CHTXDE                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_CHRXDER register  */
#define ETH_DMA_CHRXDER_CHRXDE                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_CHTXBFR register  */
#define ETH_DMA_CHTXBFR_CHTXBF                         (0xFFFFFFFFUL)

/*  Bit definition for ETH_DMA_CHRXBFR register  */
#define ETH_DMA_CHRXBFR_CHRXBF                         (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral FCM
*******************************************************************************/
/*  Bit definition for FCM_LVR register  */
#define FCM_LVR_LVR                                    (0x0000FFFFUL)

/*  Bit definition for FCM_UVR register  */
#define FCM_UVR_UVR                                    (0x0000FFFFUL)

/*  Bit definition for FCM_CNTR register  */
#define FCM_CNTR_CNTR                                  (0x0000FFFFUL)

/*  Bit definition for FCM_STR register  */
#define FCM_STR_START                                  (0x00000001UL)

/*  Bit definition for FCM_MCCR register  */
#define FCM_MCCR_MDIVS_POS                             (0U)
#define FCM_MCCR_MDIVS                                 (0x00000003UL)
#define FCM_MCCR_MCKS_POS                              (4U)
#define FCM_MCCR_MCKS                                  (0x000000F0UL)

/*  Bit definition for FCM_RCCR register  */
#define FCM_RCCR_RDIVS_POS                             (0U)
#define FCM_RCCR_RDIVS                                 (0x00000003UL)
#define FCM_RCCR_RCKS_POS                              (3U)
#define FCM_RCCR_RCKS                                  (0x00000078UL)
#define FCM_RCCR_INEXS_POS                             (7U)
#define FCM_RCCR_INEXS                                 (0x00000080UL)
#define FCM_RCCR_DNFS_POS                              (8U)
#define FCM_RCCR_DNFS                                  (0x00000300UL)
#define FCM_RCCR_DNFS_0                                (0x00000100UL)
#define FCM_RCCR_DNFS_1                                (0x00000200UL)
#define FCM_RCCR_EDGES_POS                             (12U)
#define FCM_RCCR_EDGES                                 (0x00003000UL)
#define FCM_RCCR_EDGES_0                               (0x00001000UL)
#define FCM_RCCR_EDGES_1                               (0x00002000UL)
#define FCM_RCCR_EXREFE_POS                            (15U)
#define FCM_RCCR_EXREFE                                (0x00008000UL)

/*  Bit definition for FCM_RIER register  */
#define FCM_RIER_ERRIE_POS                             (0U)
#define FCM_RIER_ERRIE                                 (0x00000001UL)
#define FCM_RIER_MENDIE_POS                            (1U)
#define FCM_RIER_MENDIE                                (0x00000002UL)
#define FCM_RIER_OVFIE_POS                             (2U)
#define FCM_RIER_OVFIE                                 (0x00000004UL)
#define FCM_RIER_ERRINTRS_POS                          (4U)
#define FCM_RIER_ERRINTRS                              (0x00000010UL)
#define FCM_RIER_ERRE_POS                              (7U)
#define FCM_RIER_ERRE                                  (0x00000080UL)

/*  Bit definition for FCM_SR register  */
#define FCM_SR_ERRF_POS                                (0U)
#define FCM_SR_ERRF                                    (0x00000001UL)
#define FCM_SR_MENDF_POS                               (1U)
#define FCM_SR_MENDF                                   (0x00000002UL)
#define FCM_SR_OVF_POS                                 (2U)
#define FCM_SR_OVF                                     (0x00000004UL)

/*  Bit definition for FCM_CLR register  */
#define FCM_CLR_ERRFCLR_POS                            (0U)
#define FCM_CLR_ERRFCLR                                (0x00000001UL)
#define FCM_CLR_MENDFCLR_POS                           (1U)
#define FCM_CLR_MENDFCLR                               (0x00000002UL)
#define FCM_CLR_OVFCLR_POS                             (2U)
#define FCM_CLR_OVFCLR                                 (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral FMAC
*******************************************************************************/
/*  Bit definition for FMAC_ENR register  */
#define FMAC_ENR_FMACEN                                (0x00000001UL)

/*  Bit definition for FMAC_CTR register  */
#define FMAC_CTR_STAGE_NUM_POS                         (0U)
#define FMAC_CTR_STAGE_NUM                             (0x0000001FUL)
#define FMAC_CTR_SHIFT_POS                             (8U)
#define FMAC_CTR_SHIFT                                 (0x00001F00UL)

/*  Bit definition for FMAC_IER register  */
#define FMAC_IER_INTEN                                 (0x00000001UL)

/*  Bit definition for FMAC_DTR register  */
#define FMAC_DTR_DIN                                   (0x0000FFFFUL)

/*  Bit definition for FMAC_RTR0 register  */
#define FMAC_RTR0                                      (0xFFFFFFFFUL)

/*  Bit definition for FMAC_RTR1 register  */
#define FMAC_RTR1                                      (0xFFFFFFFFUL)

/*  Bit definition for FMAC_STR register  */
#define FMAC_STR_READY_POS                             (31U)
#define FMAC_STR_READY                                 (0x80000000UL)

/*  Bit definition for FMAC_COR register  */
#define FMAC_COR_CIN                                   (0x0000FFFFUL)

/*******************************************************************************
                Bit definition for Peripheral GPIO
*******************************************************************************/
/*  Bit definition for GPIO_PIDR register  */
#define GPIO_PIDR_PIN00_POS                            (0U)
#define GPIO_PIDR_PIN00                                (0x0001U)
#define GPIO_PIDR_PIN01_POS                            (1U)
#define GPIO_PIDR_PIN01                                (0x0002U)
#define GPIO_PIDR_PIN02_POS                            (2U)
#define GPIO_PIDR_PIN02                                (0x0004U)
#define GPIO_PIDR_PIN03_POS                            (3U)
#define GPIO_PIDR_PIN03                                (0x0008U)
#define GPIO_PIDR_PIN04_POS                            (4U)
#define GPIO_PIDR_PIN04                                (0x0010U)
#define GPIO_PIDR_PIN05_POS                            (5U)
#define GPIO_PIDR_PIN05                                (0x0020U)
#define GPIO_PIDR_PIN06_POS                            (6U)
#define GPIO_PIDR_PIN06                                (0x0040U)
#define GPIO_PIDR_PIN07_POS                            (7U)
#define GPIO_PIDR_PIN07                                (0x0080U)
#define GPIO_PIDR_PIN08_POS                            (8U)
#define GPIO_PIDR_PIN08                                (0x0100U)
#define GPIO_PIDR_PIN09_POS                            (9U)
#define GPIO_PIDR_PIN09                                (0x0200U)
#define GPIO_PIDR_PIN10_POS                            (10U)
#define GPIO_PIDR_PIN10                                (0x0400U)
#define GPIO_PIDR_PIN11_POS                            (11U)
#define GPIO_PIDR_PIN11                                (0x0800U)
#define GPIO_PIDR_PIN12_POS                            (12U)
#define GPIO_PIDR_PIN12                                (0x1000U)
#define GPIO_PIDR_PIN13_POS                            (13U)
#define GPIO_PIDR_PIN13                                (0x2000U)
#define GPIO_PIDR_PIN14_POS                            (14U)
#define GPIO_PIDR_PIN14                                (0x4000U)
#define GPIO_PIDR_PIN15_POS                            (15U)
#define GPIO_PIDR_PIN15                                (0x8000U)

/*  Bit definition for GPIO_PODR register  */
#define GPIO_PODR_POUT00_POS                           (0U)
#define GPIO_PODR_POUT00                               (0x0001U)
#define GPIO_PODR_POUT01_POS                           (1U)
#define GPIO_PODR_POUT01                               (0x0002U)
#define GPIO_PODR_POUT02_POS                           (2U)
#define GPIO_PODR_POUT02                               (0x0004U)
#define GPIO_PODR_POUT03_POS                           (3U)
#define GPIO_PODR_POUT03                               (0x0008U)
#define GPIO_PODR_POUT04_POS                           (4U)
#define GPIO_PODR_POUT04                               (0x0010U)
#define GPIO_PODR_POUT05_POS                           (5U)
#define GPIO_PODR_POUT05                               (0x0020U)
#define GPIO_PODR_POUT06_POS                           (6U)
#define GPIO_PODR_POUT06                               (0x0040U)
#define GPIO_PODR_POUT07_POS                           (7U)
#define GPIO_PODR_POUT07                               (0x0080U)
#define GPIO_PODR_POUT08_POS                           (8U)
#define GPIO_PODR_POUT08                               (0x0100U)
#define GPIO_PODR_POUT09_POS                           (9U)
#define GPIO_PODR_POUT09                               (0x0200U)
#define GPIO_PODR_POUT10_POS                           (10U)
#define GPIO_PODR_POUT10                               (0x0400U)
#define GPIO_PODR_POUT11_POS                           (11U)
#define GPIO_PODR_POUT11                               (0x0800U)
#define GPIO_PODR_POUT12_POS                           (12U)
#define GPIO_PODR_POUT12                               (0x1000U)
#define GPIO_PODR_POUT13_POS                           (13U)
#define GPIO_PODR_POUT13                               (0x2000U)
#define GPIO_PODR_POUT14_POS                           (14U)
#define GPIO_PODR_POUT14                               (0x4000U)
#define GPIO_PODR_POUT15_POS                           (15U)
#define GPIO_PODR_POUT15                               (0x8000U)

/*  Bit definition for GPIO_POER register  */
#define GPIO_POER_POUTE00_POS                          (0U)
#define GPIO_POER_POUTE00                              (0x0001U)
#define GPIO_POER_POUTE01_POS                          (1U)
#define GPIO_POER_POUTE01                              (0x0002U)
#define GPIO_POER_POUTE02_POS                          (2U)
#define GPIO_POER_POUTE02                              (0x0004U)
#define GPIO_POER_POUTE03_POS                          (3U)
#define GPIO_POER_POUTE03                              (0x0008U)
#define GPIO_POER_POUTE04_POS                          (4U)
#define GPIO_POER_POUTE04                              (0x0010U)
#define GPIO_POER_POUTE05_POS                          (5U)
#define GPIO_POER_POUTE05                              (0x0020U)
#define GPIO_POER_POUTE06_POS                          (6U)
#define GPIO_POER_POUTE06                              (0x0040U)
#define GPIO_POER_POUTE07_POS                          (7U)
#define GPIO_POER_POUTE07                              (0x0080U)
#define GPIO_POER_POUTE08_POS                          (8U)
#define GPIO_POER_POUTE08                              (0x0100U)
#define GPIO_POER_POUTE09_POS                          (9U)
#define GPIO_POER_POUTE09                              (0x0200U)
#define GPIO_POER_POUTE10_POS                          (10U)
#define GPIO_POER_POUTE10                              (0x0400U)
#define GPIO_POER_POUTE11_POS                          (11U)
#define GPIO_POER_POUTE11                              (0x0800U)
#define GPIO_POER_POUTE12_POS                          (12U)
#define GPIO_POER_POUTE12                              (0x1000U)
#define GPIO_POER_POUTE13_POS                          (13U)
#define GPIO_POER_POUTE13                              (0x2000U)
#define GPIO_POER_POUTE14_POS                          (14U)
#define GPIO_POER_POUTE14                              (0x4000U)
#define GPIO_POER_POUTE15_POS                          (15U)
#define GPIO_POER_POUTE15                              (0x8000U)

/*  Bit definition for GPIO_POSR register  */
#define GPIO_POSR_POS00_POS                            (0U)
#define GPIO_POSR_POS00                                (0x0001U)
#define GPIO_POSR_POS01_POS                            (1U)
#define GPIO_POSR_POS01                                (0x0002U)
#define GPIO_POSR_POS02_POS                            (2U)
#define GPIO_POSR_POS02                                (0x0004U)
#define GPIO_POSR_POS03_POS                            (3U)
#define GPIO_POSR_POS03                                (0x0008U)
#define GPIO_POSR_POS04_POS                            (4U)
#define GPIO_POSR_POS04                                (0x0010U)
#define GPIO_POSR_POS05_POS                            (5U)
#define GPIO_POSR_POS05                                (0x0020U)
#define GPIO_POSR_POS06_POS                            (6U)
#define GPIO_POSR_POS06                                (0x0040U)
#define GPIO_POSR_POS07_POS                            (7U)
#define GPIO_POSR_POS07                                (0x0080U)
#define GPIO_POSR_POS08_POS                            (8U)
#define GPIO_POSR_POS08                                (0x0100U)
#define GPIO_POSR_POS09_POS                            (9U)
#define GPIO_POSR_POS09                                (0x0200U)
#define GPIO_POSR_POS10_POS                            (10U)
#define GPIO_POSR_POS10                                (0x0400U)
#define GPIO_POSR_POS11_POS                            (11U)
#define GPIO_POSR_POS11                                (0x0800U)
#define GPIO_POSR_POS12_POS                            (12U)
#define GPIO_POSR_POS12                                (0x1000U)
#define GPIO_POSR_POS13_POS                            (13U)
#define GPIO_POSR_POS13                                (0x2000U)
#define GPIO_POSR_POS14_POS                            (14U)
#define GPIO_POSR_POS14                                (0x4000U)
#define GPIO_POSR_POS15_POS                            (15U)
#define GPIO_POSR_POS15                                (0x8000U)

/*  Bit definition for GPIO_PORR register  */
#define GPIO_PORR_POR00_POS                            (0U)
#define GPIO_PORR_POR00                                (0x0001U)
#define GPIO_PORR_POR01_POS                            (1U)
#define GPIO_PORR_POR01                                (0x0002U)
#define GPIO_PORR_POR02_POS                            (2U)
#define GPIO_PORR_POR02                                (0x0004U)
#define GPIO_PORR_POR03_POS                            (3U)
#define GPIO_PORR_POR03                                (0x0008U)
#define GPIO_PORR_POR04_POS                            (4U)
#define GPIO_PORR_POR04                                (0x0010U)
#define GPIO_PORR_POR05_POS                            (5U)
#define GPIO_PORR_POR05                                (0x0020U)
#define GPIO_PORR_POR06_POS                            (6U)
#define GPIO_PORR_POR06                                (0x0040U)
#define GPIO_PORR_POR07_POS                            (7U)
#define GPIO_PORR_POR07                                (0x0080U)
#define GPIO_PORR_POR08_POS                            (8U)
#define GPIO_PORR_POR08                                (0x0100U)
#define GPIO_PORR_POR09_POS                            (9U)
#define GPIO_PORR_POR09                                (0x0200U)
#define GPIO_PORR_POR10_POS                            (10U)
#define GPIO_PORR_POR10                                (0x0400U)
#define GPIO_PORR_POR11_POS                            (11U)
#define GPIO_PORR_POR11                                (0x0800U)
#define GPIO_PORR_POR12_POS                            (12U)
#define GPIO_PORR_POR12                                (0x1000U)
#define GPIO_PORR_POR13_POS                            (13U)
#define GPIO_PORR_POR13                                (0x2000U)
#define GPIO_PORR_POR14_POS                            (14U)
#define GPIO_PORR_POR14                                (0x4000U)
#define GPIO_PORR_POR15_POS                            (15U)
#define GPIO_PORR_POR15                                (0x8000U)

/*  Bit definition for GPIO_POTR register  */
#define GPIO_POTR_POT00_POS                            (0U)
#define GPIO_POTR_POT00                                (0x0001U)
#define GPIO_POTR_POT01_POS                            (1U)
#define GPIO_POTR_POT01                                (0x0002U)
#define GPIO_POTR_POT02_POS                            (2U)
#define GPIO_POTR_POT02                                (0x0004U)
#define GPIO_POTR_POT03_POS                            (3U)
#define GPIO_POTR_POT03                                (0x0008U)
#define GPIO_POTR_POT04_POS                            (4U)
#define GPIO_POTR_POT04                                (0x0010U)
#define GPIO_POTR_POT05_POS                            (5U)
#define GPIO_POTR_POT05                                (0x0020U)
#define GPIO_POTR_POT06_POS                            (6U)
#define GPIO_POTR_POT06                                (0x0040U)
#define GPIO_POTR_POT07_POS                            (7U)
#define GPIO_POTR_POT07                                (0x0080U)
#define GPIO_POTR_POT08_POS                            (8U)
#define GPIO_POTR_POT08                                (0x0100U)
#define GPIO_POTR_POT09_POS                            (9U)
#define GPIO_POTR_POT09                                (0x0200U)
#define GPIO_POTR_POT10_POS                            (10U)
#define GPIO_POTR_POT10                                (0x0400U)
#define GPIO_POTR_POT11_POS                            (11U)
#define GPIO_POTR_POT11                                (0x0800U)
#define GPIO_POTR_POT12_POS                            (12U)
#define GPIO_POTR_POT12                                (0x1000U)
#define GPIO_POTR_POT13_POS                            (13U)
#define GPIO_POTR_POT13                                (0x2000U)
#define GPIO_POTR_POT14_POS                            (14U)
#define GPIO_POTR_POT14                                (0x4000U)
#define GPIO_POTR_POT15_POS                            (15U)
#define GPIO_POTR_POT15                                (0x8000U)

/*  Bit definition for GPIO_PIDRI register  */
#define GPIO_PIDRI_PIN00_POS                           (0U)
#define GPIO_PIDRI_PIN00                               (0x0001U)
#define GPIO_PIDRI_PIN01_POS                           (1U)
#define GPIO_PIDRI_PIN01                               (0x0002U)
#define GPIO_PIDRI_PIN02_POS                           (2U)
#define GPIO_PIDRI_PIN02                               (0x0004U)
#define GPIO_PIDRI_PIN03_POS                           (3U)
#define GPIO_PIDRI_PIN03                               (0x0008U)
#define GPIO_PIDRI_PIN04_POS                           (4U)
#define GPIO_PIDRI_PIN04                               (0x0010U)
#define GPIO_PIDRI_PIN05_POS                           (5U)
#define GPIO_PIDRI_PIN05                               (0x0020U)
#define GPIO_PIDRI_PIN06_POS                           (6U)
#define GPIO_PIDRI_PIN06                               (0x0040U)
#define GPIO_PIDRI_PIN07_POS                           (7U)
#define GPIO_PIDRI_PIN07                               (0x0080U)
#define GPIO_PIDRI_PIN08_POS                           (8U)
#define GPIO_PIDRI_PIN08                               (0x0100U)
#define GPIO_PIDRI_PIN09_POS                           (9U)
#define GPIO_PIDRI_PIN09                               (0x0200U)
#define GPIO_PIDRI_PIN10_POS                           (10U)
#define GPIO_PIDRI_PIN10                               (0x0400U)
#define GPIO_PIDRI_PIN11_POS                           (11U)
#define GPIO_PIDRI_PIN11                               (0x0800U)
#define GPIO_PIDRI_PIN12_POS                           (12U)
#define GPIO_PIDRI_PIN12                               (0x1000U)
#define GPIO_PIDRI_PIN13_POS                           (13U)
#define GPIO_PIDRI_PIN13                               (0x2000U)

/*  Bit definition for GPIO_PODRI register  */
#define GPIO_PODRI_POUT00_POS                          (0U)
#define GPIO_PODRI_POUT00                              (0x0001U)
#define GPIO_PODRI_POUT01_POS                          (1U)
#define GPIO_PODRI_POUT01                              (0x0002U)
#define GPIO_PODRI_POUT02_POS                          (2U)
#define GPIO_PODRI_POUT02                              (0x0004U)
#define GPIO_PODRI_POUT03_POS                          (3U)
#define GPIO_PODRI_POUT03                              (0x0008U)
#define GPIO_PODRI_POUT04_POS                          (4U)
#define GPIO_PODRI_POUT04                              (0x0010U)
#define GPIO_PODRI_POUT05_POS                          (5U)
#define GPIO_PODRI_POUT05                              (0x0020U)
#define GPIO_PODRI_POUT06_POS                          (6U)
#define GPIO_PODRI_POUT06                              (0x0040U)
#define GPIO_PODRI_POUT07_POS                          (7U)
#define GPIO_PODRI_POUT07                              (0x0080U)
#define GPIO_PODRI_POUT08_POS                          (8U)
#define GPIO_PODRI_POUT08                              (0x0100U)
#define GPIO_PODRI_POUT09_POS                          (9U)
#define GPIO_PODRI_POUT09                              (0x0200U)
#define GPIO_PODRI_POUT10_POS                          (10U)
#define GPIO_PODRI_POUT10                              (0x0400U)
#define GPIO_PODRI_POUT11_POS                          (11U)
#define GPIO_PODRI_POUT11                              (0x0800U)
#define GPIO_PODRI_POUT12_POS                          (12U)
#define GPIO_PODRI_POUT12                              (0x1000U)
#define GPIO_PODRI_POUT13_POS                          (13U)
#define GPIO_PODRI_POUT13                              (0x2000U)

/*  Bit definition for GPIO_POERI register  */
#define GPIO_POERI_POUTE00_POS                         (0U)
#define GPIO_POERI_POUTE00                             (0x0001U)
#define GPIO_POERI_POUTE01_POS                         (1U)
#define GPIO_POERI_POUTE01                             (0x0002U)
#define GPIO_POERI_POUTE02_POS                         (2U)
#define GPIO_POERI_POUTE02                             (0x0004U)
#define GPIO_POERI_POUTE03_POS                         (3U)
#define GPIO_POERI_POUTE03                             (0x0008U)
#define GPIO_POERI_POUTE04_POS                         (4U)
#define GPIO_POERI_POUTE04                             (0x0010U)
#define GPIO_POERI_POUTE05_POS                         (5U)
#define GPIO_POERI_POUTE05                             (0x0020U)
#define GPIO_POERI_POUTE06_POS                         (6U)
#define GPIO_POERI_POUTE06                             (0x0040U)
#define GPIO_POERI_POUTE07_POS                         (7U)
#define GPIO_POERI_POUTE07                             (0x0080U)
#define GPIO_POERI_POUTE08_POS                         (8U)
#define GPIO_POERI_POUTE08                             (0x0100U)
#define GPIO_POERI_POUTE09_POS                         (9U)
#define GPIO_POERI_POUTE09                             (0x0200U)
#define GPIO_POERI_POUTE10_POS                         (10U)
#define GPIO_POERI_POUTE10                             (0x0400U)
#define GPIO_POERI_POUTE11_POS                         (11U)
#define GPIO_POERI_POUTE11                             (0x0800U)
#define GPIO_POERI_POUTE12_POS                         (12U)
#define GPIO_POERI_POUTE12                             (0x1000U)
#define GPIO_POERI_POUTE13_POS                         (13U)
#define GPIO_POERI_POUTE13                             (0x2000U)

/*  Bit definition for GPIO_POSRI register  */
#define GPIO_POSRI_POS00_POS                           (0U)
#define GPIO_POSRI_POS00                               (0x0001U)
#define GPIO_POSRI_POS01_POS                           (1U)
#define GPIO_POSRI_POS01                               (0x0002U)
#define GPIO_POSRI_POS02_POS                           (2U)
#define GPIO_POSRI_POS02                               (0x0004U)
#define GPIO_POSRI_POS03_POS                           (3U)
#define GPIO_POSRI_POS03                               (0x0008U)
#define GPIO_POSRI_POS04_POS                           (4U)
#define GPIO_POSRI_POS04                               (0x0010U)
#define GPIO_POSRI_POS05_POS                           (5U)
#define GPIO_POSRI_POS05                               (0x0020U)
#define GPIO_POSRI_POS06_POS                           (6U)
#define GPIO_POSRI_POS06                               (0x0040U)
#define GPIO_POSRI_POS07_POS                           (7U)
#define GPIO_POSRI_POS07                               (0x0080U)
#define GPIO_POSRI_POS08_POS                           (8U)
#define GPIO_POSRI_POS08                               (0x0100U)
#define GPIO_POSRI_POS09_POS                           (9U)
#define GPIO_POSRI_POS09                               (0x0200U)
#define GPIO_POSRI_POS10_POS                           (10U)
#define GPIO_POSRI_POS10                               (0x0400U)
#define GPIO_POSRI_POS11_POS                           (11U)
#define GPIO_POSRI_POS11                               (0x0800U)
#define GPIO_POSRI_POS12_POS                           (12U)
#define GPIO_POSRI_POS12                               (0x1000U)
#define GPIO_POSRI_POS13_POS                           (13U)
#define GPIO_POSRI_POS13                               (0x2000U)

/*  Bit definition for GPIO_PORRI register  */
#define GPIO_PORRI_POR00_POS                           (0U)
#define GPIO_PORRI_POR00                               (0x0001U)
#define GPIO_PORRI_POR01_POS                           (1U)
#define GPIO_PORRI_POR01                               (0x0002U)
#define GPIO_PORRI_POR02_POS                           (2U)
#define GPIO_PORRI_POR02                               (0x0004U)
#define GPIO_PORRI_POR03_POS                           (3U)
#define GPIO_PORRI_POR03                               (0x0008U)
#define GPIO_PORRI_POR04_POS                           (4U)
#define GPIO_PORRI_POR04                               (0x0010U)
#define GPIO_PORRI_POR05_POS                           (5U)
#define GPIO_PORRI_POR05                               (0x0020U)
#define GPIO_PORRI_POR06_POS                           (6U)
#define GPIO_PORRI_POR06                               (0x0040U)
#define GPIO_PORRI_POR07_POS                           (7U)
#define GPIO_PORRI_POR07                               (0x0080U)
#define GPIO_PORRI_POR08_POS                           (8U)
#define GPIO_PORRI_POR08                               (0x0100U)
#define GPIO_PORRI_POR09_POS                           (9U)
#define GPIO_PORRI_POR09                               (0x0200U)
#define GPIO_PORRI_POR10_POS                           (10U)
#define GPIO_PORRI_POR10                               (0x0400U)
#define GPIO_PORRI_POR11_POS                           (11U)
#define GPIO_PORRI_POR11                               (0x0800U)
#define GPIO_PORRI_POR12_POS                           (12U)
#define GPIO_PORRI_POR12                               (0x1000U)
#define GPIO_PORRI_POR13_POS                           (13U)
#define GPIO_PORRI_POR13                               (0x2000U)

/*  Bit definition for GPIO_POTRI register  */
#define GPIO_POTRI_POT00_POS                           (0U)
#define GPIO_POTRI_POT00                               (0x0001U)
#define GPIO_POTRI_POT01_POS                           (1U)
#define GPIO_POTRI_POT01                               (0x0002U)
#define GPIO_POTRI_POT02_POS                           (2U)
#define GPIO_POTRI_POT02                               (0x0004U)
#define GPIO_POTRI_POT03_POS                           (3U)
#define GPIO_POTRI_POT03                               (0x0008U)
#define GPIO_POTRI_POT04_POS                           (4U)
#define GPIO_POTRI_POT04                               (0x0010U)
#define GPIO_POTRI_POT05_POS                           (5U)
#define GPIO_POTRI_POT05                               (0x0020U)
#define GPIO_POTRI_POT06_POS                           (6U)
#define GPIO_POTRI_POT06                               (0x0040U)
#define GPIO_POTRI_POT07_POS                           (7U)
#define GPIO_POTRI_POT07                               (0x0080U)
#define GPIO_POTRI_POT08_POS                           (8U)
#define GPIO_POTRI_POT08                               (0x0100U)
#define GPIO_POTRI_POT09_POS                           (9U)
#define GPIO_POTRI_POT09                               (0x0200U)
#define GPIO_POTRI_POT10_POS                           (10U)
#define GPIO_POTRI_POT10                               (0x0400U)
#define GPIO_POTRI_POT11_POS                           (11U)
#define GPIO_POTRI_POT11                               (0x0800U)
#define GPIO_POTRI_POT12_POS                           (12U)
#define GPIO_POTRI_POT12                               (0x1000U)
#define GPIO_POTRI_POT13_POS                           (13U)
#define GPIO_POTRI_POT13                               (0x2000U)

/*  Bit definition for GPIO_PSPCR register  */
#define GPIO_PSPCR_SPFE                                (0x001FU)
#define GPIO_PSPCR_SPFE_0                              (0x0001U)
#define GPIO_PSPCR_SPFE_1                              (0x0002U)
#define GPIO_PSPCR_SPFE_2                              (0x0004U)
#define GPIO_PSPCR_SPFE_3                              (0x0008U)
#define GPIO_PSPCR_SPFE_4                              (0x0010U)

/*  Bit definition for GPIO_PCCR register  */
#define GPIO_PCCR_BFSEL_POS                            (0U)
#define GPIO_PCCR_BFSEL                                (0x003FU)
#define GPIO_PCCR_RDWT_POS                             (12U)
#define GPIO_PCCR_RDWT                                 (0x7000U)

/*  Bit definition for GPIO_PINAER register  */
#define GPIO_PINAER_PINAE                              (0x01FFU)
#define GPIO_PINAER_PINAE_0                            (0x0001U)
#define GPIO_PINAER_PINAE_1                            (0x0002U)
#define GPIO_PINAER_PINAE_2                            (0x0004U)
#define GPIO_PINAER_PINAE_3                            (0x0008U)
#define GPIO_PINAER_PINAE_4                            (0x0010U)
#define GPIO_PINAER_PINAE_5                            (0x0020U)
#define GPIO_PINAER_PINAE_6                            (0x0040U)
#define GPIO_PINAER_PINAE_7                            (0x0080U)
#define GPIO_PINAER_PINAE_8                            (0x0100U)

/*  Bit definition for GPIO_PWPR register  */
#define GPIO_PWPR_WE_POS                               (0U)
#define GPIO_PWPR_WE                                   (0x0001U)
#define GPIO_PWPR_WP_POS                               (8U)
#define GPIO_PWPR_WP                                   (0xFF00U)

/*  Bit definition for GPIO_PCR register  */
#define GPIO_PCR_POUT_POS                              (0U)
#define GPIO_PCR_POUT                                  (0x0001U)
#define GPIO_PCR_POUTE_POS                             (1U)
#define GPIO_PCR_POUTE                                 (0x0002U)
#define GPIO_PCR_NOD_POS                               (2U)
#define GPIO_PCR_NOD                                   (0x0004U)
#define GPIO_PCR_DRV_POS                               (4U)
#define GPIO_PCR_DRV                                   (0x0030U)
#define GPIO_PCR_DRV_0                                 (0x0010U)
#define GPIO_PCR_DRV_1                                 (0x0020U)
#define GPIO_PCR_PUU_POS                               (6U)
#define GPIO_PCR_PUU                                   (0x0040U)
#define GPIO_PCR_PIN_POS                               (8U)
#define GPIO_PCR_PIN                                   (0x0100U)
#define GPIO_PCR_INVE_POS                              (9U)
#define GPIO_PCR_INVE                                  (0x0200U)
#define GPIO_PCR_CINSEL_POS                            (10U)
#define GPIO_PCR_CINSEL                                (0x0400U)
#define GPIO_PCR_INTE_POS                              (12U)
#define GPIO_PCR_INTE                                  (0x1000U)
#define GPIO_PCR_LTE_POS                               (14U)
#define GPIO_PCR_LTE                                   (0x4000U)
#define GPIO_PCR_DDIS_POS                              (15U)
#define GPIO_PCR_DDIS                                  (0x8000U)

/*  Bit definition for GPIO_PFSR register  */
#define GPIO_PFSR_FSEL_POS                             (0U)
#define GPIO_PFSR_FSEL                                 (0x003FU)
#define GPIO_PFSR_BFE_POS                              (8U)
#define GPIO_PFSR_BFE                                  (0x0100U)

/*******************************************************************************
                Bit definition for Peripheral HASH
*******************************************************************************/
/*  Bit definition for HASH_CR register  */
#define HASH_CR_START_POS                              (0U)
#define HASH_CR_START                                  (0x00000001UL)
#define HASH_CR_FST_GRP_POS                            (1U)
#define HASH_CR_FST_GRP                                (0x00000002UL)
#define HASH_CR_KMSG_END_POS                           (2U)
#define HASH_CR_KMSG_END                               (0x00000004UL)
#define HASH_CR_MODE_POS                               (4U)
#define HASH_CR_MODE                                   (0x00000030UL)
#define HASH_CR_MODE_0                                 (0x00000010UL)
#define HASH_CR_MODE_1                                 (0x00000020UL)
#define HASH_CR_LKEY_POS                               (6U)
#define HASH_CR_LKEY                                   (0x00000040UL)
#define HASH_CR_BUSY_POS                               (8U)
#define HASH_CR_BUSY                                   (0x00000100UL)
#define HASH_CR_CYC_END_POS                            (9U)
#define HASH_CR_CYC_END                                (0x00000200UL)
#define HASH_CR_HMAC_END_POS                           (10U)
#define HASH_CR_HMAC_END                               (0x00000400UL)
#define HASH_CR_HCIE_POS                               (14U)
#define HASH_CR_HCIE                                   (0x00004000UL)
#define HASH_CR_HEIE_POS                               (15U)
#define HASH_CR_HEIE                                   (0x00008000UL)

/*  Bit definition for HASH_HR7 register  */
#define HASH_HR7                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR6 register  */
#define HASH_HR6                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR5 register  */
#define HASH_HR5                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR4 register  */
#define HASH_HR4                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR3 register  */
#define HASH_HR3                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR2 register  */
#define HASH_HR2                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR1 register  */
#define HASH_HR1                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_HR0 register  */
#define HASH_HR0                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR15 register  */
#define HASH_DR15                                      (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR14 register  */
#define HASH_DR14                                      (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR13 register  */
#define HASH_DR13                                      (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR12 register  */
#define HASH_DR12                                      (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR11 register  */
#define HASH_DR11                                      (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR10 register  */
#define HASH_DR10                                      (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR9 register  */
#define HASH_DR9                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR8 register  */
#define HASH_DR8                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR7 register  */
#define HASH_DR7                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR6 register  */
#define HASH_DR6                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR5 register  */
#define HASH_DR5                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR4 register  */
#define HASH_DR4                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR3 register  */
#define HASH_DR3                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR2 register  */
#define HASH_DR2                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR1 register  */
#define HASH_DR1                                       (0xFFFFFFFFUL)

/*  Bit definition for HASH_DR0 register  */
#define HASH_DR0                                       (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral HRPWM
*******************************************************************************/
/*  Bit definition for HRPWM_CR register  */
#define HRPWM_CR_NSEL_POS                              (0U)
#define HRPWM_CR_NSEL                                  (0x000000FFUL)
#define HRPWM_CR_PSEL_POS                              (8U)
#define HRPWM_CR_PSEL                                  (0x0000FF00UL)
#define HRPWM_CR_NE_POS                                (29U)
#define HRPWM_CR_NE                                    (0x20000000UL)
#define HRPWM_CR_PE_POS                                (30U)
#define HRPWM_CR_PE                                    (0x40000000UL)
#define HRPWM_CR_EN_POS                                (31U)
#define HRPWM_CR_EN                                    (0x80000000UL)

/*  Bit definition for HRPWM_CALCR register  */
#define HRPWM_CALCR_CALCODE_POS                        (0U)
#define HRPWM_CALCR_CALCODE                            (0x000000FFUL)
#define HRPWM_CALCR_ENDF_POS                           (12U)
#define HRPWM_CALCR_ENDF                               (0x00001000UL)
#define HRPWM_CALCR_CALEN_POS                          (15U)
#define HRPWM_CALCR_CALEN                              (0x00008000UL)

/*******************************************************************************
                Bit definition for Peripheral I2C
*******************************************************************************/
/*  Bit definition for I2C_CR1 register  */
#define I2C_CR1_PE_POS                                 (0U)
#define I2C_CR1_PE                                     (0x00000001UL)
#define I2C_CR1_SMBUS_POS                              (1U)
#define I2C_CR1_SMBUS                                  (0x00000002UL)
#define I2C_CR1_SMBALRTEN_POS                          (2U)
#define I2C_CR1_SMBALRTEN                              (0x00000004UL)
#define I2C_CR1_SMBDEFAULTEN_POS                       (3U)
#define I2C_CR1_SMBDEFAULTEN                           (0x00000008UL)
#define I2C_CR1_SMBHOSTEN_POS                          (4U)
#define I2C_CR1_SMBHOSTEN                              (0x00000010UL)
#define I2C_CR1_ENGC_POS                               (6U)
#define I2C_CR1_ENGC                                   (0x00000040UL)
#define I2C_CR1_RESTART_POS                            (7U)
#define I2C_CR1_RESTART                                (0x00000080UL)
#define I2C_CR1_START_POS                              (8U)
#define I2C_CR1_START                                  (0x00000100UL)
#define I2C_CR1_STOP_POS                               (9U)
#define I2C_CR1_STOP                                   (0x00000200UL)
#define I2C_CR1_ACK_POS                                (10U)
#define I2C_CR1_ACK                                    (0x00000400UL)
#define I2C_CR1_SWRST_POS                              (15U)
#define I2C_CR1_SWRST                                  (0x00008000UL)

/*  Bit definition for I2C_CR2 register  */
#define I2C_CR2_STARTIE_POS                            (0U)
#define I2C_CR2_STARTIE                                (0x00000001UL)
#define I2C_CR2_SLADDR0IE_POS                          (1U)
#define I2C_CR2_SLADDR0IE                              (0x00000002UL)
#define I2C_CR2_SLADDR1IE_POS                          (2U)
#define I2C_CR2_SLADDR1IE                              (0x00000004UL)
#define I2C_CR2_TENDIE_POS                             (3U)
#define I2C_CR2_TENDIE                                 (0x00000008UL)
#define I2C_CR2_STOPIE_POS                             (4U)
#define I2C_CR2_STOPIE                                 (0x00000010UL)
#define I2C_CR2_RFULLIE_POS                            (6U)
#define I2C_CR2_RFULLIE                                (0x00000040UL)
#define I2C_CR2_TEMPTYIE_POS                           (7U)
#define I2C_CR2_TEMPTYIE                               (0x00000080UL)
#define I2C_CR2_ARLOIE_POS                             (9U)
#define I2C_CR2_ARLOIE                                 (0x00000200UL)
#define I2C_CR2_NACKIE_POS                             (12U)
#define I2C_CR2_NACKIE                                 (0x00001000UL)
#define I2C_CR2_TMOUTIE_POS                            (14U)
#define I2C_CR2_TMOUTIE                                (0x00004000UL)
#define I2C_CR2_GENCALLIE_POS                          (20U)
#define I2C_CR2_GENCALLIE                              (0x00100000UL)
#define I2C_CR2_SMBDEFAULTIE_POS                       (21U)
#define I2C_CR2_SMBDEFAULTIE                           (0x00200000UL)
#define I2C_CR2_SMBHOSTIE_POS                          (22U)
#define I2C_CR2_SMBHOSTIE                              (0x00400000UL)
#define I2C_CR2_SMBALRTIE_POS                          (23U)
#define I2C_CR2_SMBALRTIE                              (0x00800000UL)

/*  Bit definition for I2C_CR3 register  */
#define I2C_CR3_TMOUTEN_POS                            (0U)
#define I2C_CR3_TMOUTEN                                (0x00000001UL)
#define I2C_CR3_LTMOUT_POS                             (1U)
#define I2C_CR3_LTMOUT                                 (0x00000002UL)
#define I2C_CR3_HTMOUT_POS                             (2U)
#define I2C_CR3_HTMOUT                                 (0x00000004UL)
#define I2C_CR3_FACKEN_POS                             (7U)
#define I2C_CR3_FACKEN                                 (0x00000080UL)

/*  Bit definition for I2C_CR4 register  */
#define I2C_CR4_BUSWAIT_POS                            (10U)
#define I2C_CR4_BUSWAIT                                (0x00000400UL)

/*  Bit definition for I2C_SLR0 register  */
#define I2C_SLR0_SLADDR0_POS                           (0U)
#define I2C_SLR0_SLADDR0                               (0x000003FFUL)
#define I2C_SLR0_SLADDR0EN_POS                         (12U)
#define I2C_SLR0_SLADDR0EN                             (0x00001000UL)
#define I2C_SLR0_ADDRMOD0_POS                          (15U)
#define I2C_SLR0_ADDRMOD0                              (0x00008000UL)

/*  Bit definition for I2C_SLR1 register  */
#define I2C_SLR1_SLADDR1_POS                           (0U)
#define I2C_SLR1_SLADDR1                               (0x000003FFUL)
#define I2C_SLR1_SLADDR1EN_POS                         (12U)
#define I2C_SLR1_SLADDR1EN                             (0x00001000UL)
#define I2C_SLR1_ADDRMOD1_POS                          (15U)
#define I2C_SLR1_ADDRMOD1                              (0x00008000UL)

/*  Bit definition for I2C_SLTR register  */
#define I2C_SLTR_TOUTLOW_POS                           (0U)
#define I2C_SLTR_TOUTLOW                               (0x0000FFFFUL)
#define I2C_SLTR_TOUTHIGH_POS                          (16U)
#define I2C_SLTR_TOUTHIGH                              (0xFFFF0000UL)

/*  Bit definition for I2C_SR register  */
#define I2C_SR_STARTF_POS                              (0U)
#define I2C_SR_STARTF                                  (0x00000001UL)
#define I2C_SR_SLADDR0F_POS                            (1U)
#define I2C_SR_SLADDR0F                                (0x00000002UL)
#define I2C_SR_SLADDR1F_POS                            (2U)
#define I2C_SR_SLADDR1F                                (0x00000004UL)
#define I2C_SR_TENDF_POS                               (3U)
#define I2C_SR_TENDF                                   (0x00000008UL)
#define I2C_SR_STOPF_POS                               (4U)
#define I2C_SR_STOPF                                   (0x00000010UL)
#define I2C_SR_RFULLF_POS                              (6U)
#define I2C_SR_RFULLF                                  (0x00000040UL)
#define I2C_SR_TEMPTYF_POS                             (7U)
#define I2C_SR_TEMPTYF                                 (0x00000080UL)
#define I2C_SR_ARLOF_POS                               (9U)
#define I2C_SR_ARLOF                                   (0x00000200UL)
#define I2C_SR_ACKRF_POS                               (10U)
#define I2C_SR_ACKRF                                   (0x00000400UL)
#define I2C_SR_NACKF_POS                               (12U)
#define I2C_SR_NACKF                                   (0x00001000UL)
#define I2C_SR_TMOUTF_POS                              (14U)
#define I2C_SR_TMOUTF                                  (0x00004000UL)
#define I2C_SR_MSL_POS                                 (16U)
#define I2C_SR_MSL                                     (0x00010000UL)
#define I2C_SR_BUSY_POS                                (17U)
#define I2C_SR_BUSY                                    (0x00020000UL)
#define I2C_SR_TRA_POS                                 (18U)
#define I2C_SR_TRA                                     (0x00040000UL)
#define I2C_SR_GENCALLF_POS                            (20U)
#define I2C_SR_GENCALLF                                (0x00100000UL)
#define I2C_SR_SMBDEFAULTF_POS                         (21U)
#define I2C_SR_SMBDEFAULTF                             (0x00200000UL)
#define I2C_SR_SMBHOSTF_POS                            (22U)
#define I2C_SR_SMBHOSTF                                (0x00400000UL)
#define I2C_SR_SMBALRTF_POS                            (23U)
#define I2C_SR_SMBALRTF                                (0x00800000UL)

/*  Bit definition for I2C_CLR register  */
#define I2C_CLR_STARTFCLR_POS                          (0U)
#define I2C_CLR_STARTFCLR                              (0x00000001UL)
#define I2C_CLR_SLADDR0FCLR_POS                        (1U)
#define I2C_CLR_SLADDR0FCLR                            (0x00000002UL)
#define I2C_CLR_SLADDR1FCLR_POS                        (2U)
#define I2C_CLR_SLADDR1FCLR                            (0x00000004UL)
#define I2C_CLR_TENDFCLR_POS                           (3U)
#define I2C_CLR_TENDFCLR                               (0x00000008UL)
#define I2C_CLR_STOPFCLR_POS                           (4U)
#define I2C_CLR_STOPFCLR                               (0x00000010UL)
#define I2C_CLR_RFULLFCLR_POS                          (6U)
#define I2C_CLR_RFULLFCLR                              (0x00000040UL)
#define I2C_CLR_TEMPTYFCLR_POS                         (7U)
#define I2C_CLR_TEMPTYFCLR                             (0x00000080UL)
#define I2C_CLR_ARLOFCLR_POS                           (9U)
#define I2C_CLR_ARLOFCLR                               (0x00000200UL)
#define I2C_CLR_NACKFCLR_POS                           (12U)
#define I2C_CLR_NACKFCLR                               (0x00001000UL)
#define I2C_CLR_TMOUTFCLR_POS                          (14U)
#define I2C_CLR_TMOUTFCLR                              (0x00004000UL)
#define I2C_CLR_GENCALLFCLR_POS                        (20U)
#define I2C_CLR_GENCALLFCLR                            (0x00100000UL)
#define I2C_CLR_SMBDEFAULTFCLR_POS                     (21U)
#define I2C_CLR_SMBDEFAULTFCLR                         (0x00200000UL)
#define I2C_CLR_SMBHOSTFCLR_POS                        (22U)
#define I2C_CLR_SMBHOSTFCLR                            (0x00400000UL)
#define I2C_CLR_SMBALRTFCLR_POS                        (23U)
#define I2C_CLR_SMBALRTFCLR                            (0x00800000UL)

/*  Bit definition for I2C_DTR register  */
#define I2C_DTR_DT                                     (0xFFU)

/*  Bit definition for I2C_DRR register  */
#define I2C_DRR_DR                                     (0xFFU)

/*  Bit definition for I2C_CCR register  */
#define I2C_CCR_SLOWW_POS                              (0U)
#define I2C_CCR_SLOWW                                  (0x0000001FUL)
#define I2C_CCR_SHIGHW_POS                             (8U)
#define I2C_CCR_SHIGHW                                 (0x00001F00UL)
#define I2C_CCR_FREQ_POS                               (16U)
#define I2C_CCR_FREQ                                   (0x00070000UL)

/*  Bit definition for I2C_FLTR register  */
#define I2C_FLTR_DNF_POS                               (0U)
#define I2C_FLTR_DNF                                   (0x00000003UL)
#define I2C_FLTR_DNFEN_POS                             (4U)
#define I2C_FLTR_DNFEN                                 (0x00000010UL)
#define I2C_FLTR_ANFEN_POS                             (5U)
#define I2C_FLTR_ANFEN                                 (0x00000020UL)

/*******************************************************************************
                Bit definition for Peripheral I2S
*******************************************************************************/
/*  Bit definition for I2S_CTRL register  */
#define I2S_CTRL_TXE_POS                               (0U)
#define I2S_CTRL_TXE                                   (0x00000001UL)
#define I2S_CTRL_TXIE_POS                              (1U)
#define I2S_CTRL_TXIE                                  (0x00000002UL)
#define I2S_CTRL_RXE_POS                               (2U)
#define I2S_CTRL_RXE                                   (0x00000004UL)
#define I2S_CTRL_RXIE_POS                              (3U)
#define I2S_CTRL_RXIE                                  (0x00000008UL)
#define I2S_CTRL_EIE_POS                               (4U)
#define I2S_CTRL_EIE                                   (0x00000010UL)
#define I2S_CTRL_WMS_POS                               (5U)
#define I2S_CTRL_WMS                                   (0x00000020UL)
#define I2S_CTRL_ODD_POS                               (6U)
#define I2S_CTRL_ODD                                   (0x00000040UL)
#define I2S_CTRL_MCKOE_POS                             (7U)
#define I2S_CTRL_MCKOE                                 (0x00000080UL)
#define I2S_CTRL_TXBIRQWL_POS                          (8U)
#define I2S_CTRL_TXBIRQWL                              (0x00000700UL)
#define I2S_CTRL_TXBIRQWL_0                            (0x00000100UL)
#define I2S_CTRL_TXBIRQWL_1                            (0x00000200UL)
#define I2S_CTRL_TXBIRQWL_2                            (0x00000400UL)
#define I2S_CTRL_RXBIRQWL_POS                          (12U)
#define I2S_CTRL_RXBIRQWL                              (0x00007000UL)
#define I2S_CTRL_RXBIRQWL_0                            (0x00001000UL)
#define I2S_CTRL_RXBIRQWL_1                            (0x00002000UL)
#define I2S_CTRL_RXBIRQWL_2                            (0x00004000UL)
#define I2S_CTRL_FIFOR_POS                             (16U)
#define I2S_CTRL_FIFOR                                 (0x00010000UL)
#define I2S_CTRL_CODECRC_POS                           (17U)
#define I2S_CTRL_CODECRC                               (0x00020000UL)
#define I2S_CTRL_I2SPLLSEL_POS                         (18U)
#define I2S_CTRL_I2SPLLSEL                             (0x00040000UL)
#define I2S_CTRL_SDOE_POS                              (19U)
#define I2S_CTRL_SDOE                                  (0x00080000UL)
#define I2S_CTRL_LRCKOE_POS                            (20U)
#define I2S_CTRL_LRCKOE                                (0x00100000UL)
#define I2S_CTRL_CKOE_POS                              (21U)
#define I2S_CTRL_CKOE                                  (0x00200000UL)
#define I2S_CTRL_DUPLEX_POS                            (22U)
#define I2S_CTRL_DUPLEX                                (0x00400000UL)
#define I2S_CTRL_CLKSEL_POS                            (23U)
#define I2S_CTRL_CLKSEL                                (0x00800000UL)
#define I2S_CTRL_SRST_POS                              (24U)
#define I2S_CTRL_SRST                                  (0x01000000UL)

/*  Bit definition for I2S_SR register  */
#define I2S_SR_TXBA_POS                                (0U)
#define I2S_SR_TXBA                                    (0x00000001UL)
#define I2S_SR_RXBA_POS                                (1U)
#define I2S_SR_RXBA                                    (0x00000002UL)
#define I2S_SR_TXBE_POS                                (2U)
#define I2S_SR_TXBE                                    (0x00000004UL)
#define I2S_SR_TXBF_POS                                (3U)
#define I2S_SR_TXBF                                    (0x00000008UL)
#define I2S_SR_RXBE_POS                                (4U)
#define I2S_SR_RXBE                                    (0x00000010UL)
#define I2S_SR_RXBF_POS                                (5U)
#define I2S_SR_RXBF                                    (0x00000020UL)

/*  Bit definition for I2S_ER register  */
#define I2S_ER_TXERR_POS                               (0U)
#define I2S_ER_TXERR                                   (0x00000001UL)
#define I2S_ER_RXERR_POS                               (1U)
#define I2S_ER_RXERR                                   (0x00000002UL)

/*  Bit definition for I2S_CFGR register  */
#define I2S_CFGR_I2SSTD_POS                            (0U)
#define I2S_CFGR_I2SSTD                                (0x00000003UL)
#define I2S_CFGR_I2SSTD_0                              (0x00000001UL)
#define I2S_CFGR_I2SSTD_1                              (0x00000002UL)
#define I2S_CFGR_DATLEN_POS                            (2U)
#define I2S_CFGR_DATLEN                                (0x0000000CUL)
#define I2S_CFGR_DATLEN_0                              (0x00000004UL)
#define I2S_CFGR_DATLEN_1                              (0x00000008UL)
#define I2S_CFGR_CHLEN_POS                             (4U)
#define I2S_CFGR_CHLEN                                 (0x00000010UL)
#define I2S_CFGR_PCMSYNC_POS                           (5U)
#define I2S_CFGR_PCMSYNC                               (0x00000020UL)

/*  Bit definition for I2S_TXBUF register  */
#define I2S_TXBUF                                      (0xFFFFFFFFUL)

/*  Bit definition for I2S_RXBUF register  */
#define I2S_RXBUF                                      (0xFFFFFFFFUL)

/*  Bit definition for I2S_PR register  */
#define I2S_PR_I2SDIV                                  (0x000000FFUL)

/*******************************************************************************
                Bit definition for Peripheral ICG
*******************************************************************************/
/*  Bit definition for ICG_ICG0 register  */
#define ICG_ICG0_SWDTAUTS_POS                          (0U)
#define ICG_ICG0_SWDTAUTS                              (0x00000001UL)
#define ICG_ICG0_SWDTITS_POS                           (1U)
#define ICG_ICG0_SWDTITS                               (0x00000002UL)
#define ICG_ICG0_SWDTPERI_POS                          (2U)
#define ICG_ICG0_SWDTPERI                              (0x0000000CUL)
#define ICG_ICG0_SWDTPERI_0                            (0x00000004UL)
#define ICG_ICG0_SWDTPERI_1                            (0x00000008UL)
#define ICG_ICG0_SWDTCKS_POS                           (4U)
#define ICG_ICG0_SWDTCKS                               (0x000000F0UL)
#define ICG_ICG0_SWDTCKS_0                             (0x00000010UL)
#define ICG_ICG0_SWDTCKS_1                             (0x00000020UL)
#define ICG_ICG0_SWDTCKS_2                             (0x00000040UL)
#define ICG_ICG0_SWDTCKS_3                             (0x00000080UL)
#define ICG_ICG0_SWDTWDPT_POS                          (8U)
#define ICG_ICG0_SWDTWDPT                              (0x00000F00UL)
#define ICG_ICG0_SWDTWDPT_0                            (0x00000100UL)
#define ICG_ICG0_SWDTWDPT_1                            (0x00000200UL)
#define ICG_ICG0_SWDTWDPT_2                            (0x00000400UL)
#define ICG_ICG0_SWDTWDPT_3                            (0x00000800UL)
#define ICG_ICG0_SWDTSLPOFF_POS                        (12U)
#define ICG_ICG0_SWDTSLPOFF                            (0x00001000UL)
#define ICG_ICG0_WDTAUTS_POS                           (16U)
#define ICG_ICG0_WDTAUTS                               (0x00010000UL)
#define ICG_ICG0_WDTITS_POS                            (17U)
#define ICG_ICG0_WDTITS                                (0x00020000UL)
#define ICG_ICG0_WDTPERI_POS                           (18U)
#define ICG_ICG0_WDTPERI                               (0x000C0000UL)
#define ICG_ICG0_WDTPERI_0                             (0x00040000UL)
#define ICG_ICG0_WDTPERI_1                             (0x00080000UL)
#define ICG_ICG0_WDTCKS_POS                            (20U)
#define ICG_ICG0_WDTCKS                                (0x00F00000UL)
#define ICG_ICG0_WDTCKS_0                              (0x00100000UL)
#define ICG_ICG0_WDTCKS_1                              (0x00200000UL)
#define ICG_ICG0_WDTCKS_2                              (0x00400000UL)
#define ICG_ICG0_WDTCKS_3                              (0x00800000UL)
#define ICG_ICG0_WDTWDPT_POS                           (24U)
#define ICG_ICG0_WDTWDPT                               (0x0F000000UL)
#define ICG_ICG0_WDTWDPT_0                             (0x01000000UL)
#define ICG_ICG0_WDTWDPT_1                             (0x02000000UL)
#define ICG_ICG0_WDTWDPT_2                             (0x04000000UL)
#define ICG_ICG0_WDTWDPT_3                             (0x08000000UL)
#define ICG_ICG0_WDTSLPOFF_POS                         (28U)
#define ICG_ICG0_WDTSLPOFF                             (0x10000000UL)

/*  Bit definition for ICG_ICG1 register  */
#define ICG_ICG1_HRCFREQSEL_POS                        (0U)
#define ICG_ICG1_HRCFREQSEL                            (0x00000001UL)
#define ICG_ICG1_HRCSTOP_POS                           (8U)
#define ICG_ICG1_HRCSTOP                               (0x00000100UL)
#define ICG_ICG1_BOR_LEV_POS                           (16U)
#define ICG_ICG1_BOR_LEV                               (0x00030000UL)
#define ICG_ICG1_BOR_LEV_0                             (0x00010000UL)
#define ICG_ICG1_BOR_LEV_1                             (0x00020000UL)
#define ICG_ICG1_BORDIS_POS                            (18U)
#define ICG_ICG1_BORDIS                                (0x00040000UL)

/*  Bit definition for ICG_ICG3 register  */
#define ICG_ICG3_DBUSPRT                               (0x0000FFFFUL)

/*******************************************************************************
                Bit definition for Peripheral INTC
*******************************************************************************/
/*  Bit definition for INTC_NOCCR register  */
#define INTC_NOCCR_NOCSEL_POS                          (12U)
#define INTC_NOCCR_NOCSEL                              (0x00003000UL)
#define INTC_NOCCR_NOCSEL_0                            (0x00001000UL)
#define INTC_NOCCR_NOCSEL_1                            (0x00002000UL)

/*  Bit definition for INTC_NMIENR register  */
#define INTC_NMIENR_SWDTENR_POS                        (1U)
#define INTC_NMIENR_SWDTENR                            (0x00000002UL)
#define INTC_NMIENR_PVD1ENR_POS                        (2U)
#define INTC_NMIENR_PVD1ENR                            (0x00000004UL)
#define INTC_NMIENR_PVD2ENR_POS                        (3U)
#define INTC_NMIENR_PVD2ENR                            (0x00000008UL)
#define INTC_NMIENR_XTALSTPENR_POS                     (5U)
#define INTC_NMIENR_XTALSTPENR                         (0x00000020UL)
#define INTC_NMIENR_REPENR_POS                         (8U)
#define INTC_NMIENR_REPENR                             (0x00000100UL)
#define INTC_NMIENR_RECCENR_POS                        (9U)
#define INTC_NMIENR_RECCENR                            (0x00000200UL)
#define INTC_NMIENR_BUSMENR_POS                        (10U)
#define INTC_NMIENR_BUSMENR                            (0x00000400UL)
#define INTC_NMIENR_WDTENR_POS                         (11U)
#define INTC_NMIENR_WDTENR                             (0x00000800UL)

/*  Bit definition for INTC_NMIFR register  */
#define INTC_NMIFR_SWDTFR_POS                          (1U)
#define INTC_NMIFR_SWDTFR                              (0x00000002UL)
#define INTC_NMIFR_PVD1FR_POS                          (2U)
#define INTC_NMIFR_PVD1FR                              (0x00000004UL)
#define INTC_NMIFR_PVD2FR_POS                          (3U)
#define INTC_NMIFR_PVD2FR                              (0x00000008UL)
#define INTC_NMIFR_XTALSTPFR_POS                       (5U)
#define INTC_NMIFR_XTALSTPFR                           (0x00000020UL)
#define INTC_NMIFR_REPFR_POS                           (8U)
#define INTC_NMIFR_REPFR                               (0x00000100UL)
#define INTC_NMIFR_RECCFR_POS                          (9U)
#define INTC_NMIFR_RECCFR                              (0x00000200UL)
#define INTC_NMIFR_BUSMFR_POS                          (10U)
#define INTC_NMIFR_BUSMFR                              (0x00000400UL)
#define INTC_NMIFR_WDTFR_POS                           (11U)
#define INTC_NMIFR_WDTFR                               (0x00000800UL)

/*  Bit definition for INTC_NMICFR register  */
#define INTC_NMICFR_SWDTCFR_POS                        (1U)
#define INTC_NMICFR_SWDTCFR                            (0x00000002UL)
#define INTC_NMICFR_PVD1CFR_POS                        (2U)
#define INTC_NMICFR_PVD1CFR                            (0x00000004UL)
#define INTC_NMICFR_PVD2CFR_POS                        (3U)
#define INTC_NMICFR_PVD2CFR                            (0x00000008UL)
#define INTC_NMICFR_XTALSTPCFR_POS                     (5U)
#define INTC_NMICFR_XTALSTPCFR                         (0x00000020UL)
#define INTC_NMICFR_REPCFR_POS                         (8U)
#define INTC_NMICFR_REPCFR                             (0x00000100UL)
#define INTC_NMICFR_RECCCFR_POS                        (9U)
#define INTC_NMICFR_RECCCFR                            (0x00000200UL)
#define INTC_NMICFR_BUSMCFR_POS                        (10U)
#define INTC_NMICFR_BUSMCFR                            (0x00000400UL)
#define INTC_NMICFR_WDTCFR_POS                         (11U)
#define INTC_NMICFR_WDTCFR                             (0x00000800UL)

/*  Bit definition for INTC_EIRQCR register  */
#define INTC_EIRQCR_EIRQTRG_POS                        (0U)
#define INTC_EIRQCR_EIRQTRG                            (0x00000003UL)
#define INTC_EIRQCR_EIRQTRG_0                          (0x00000001UL)
#define INTC_EIRQCR_EIRQTRG_1                          (0x00000002UL)
#define INTC_EIRQCR_EISMPCLK_POS                       (4U)
#define INTC_EIRQCR_EISMPCLK                           (0x00000030UL)
#define INTC_EIRQCR_EISMPCLK_0                         (0x00000010UL)
#define INTC_EIRQCR_EISMPCLK_1                         (0x00000020UL)
#define INTC_EIRQCR_EFEN_POS                           (7U)
#define INTC_EIRQCR_EFEN                               (0x00000080UL)
#define INTC_EIRQCR_NOCEN_POS                          (15U)
#define INTC_EIRQCR_NOCEN                              (0x00008000UL)

/*  Bit definition for INTC_WUPEN register  */
#define INTC_WUPEN_EIRQWUEN_POS                        (0U)
#define INTC_WUPEN_EIRQWUEN                            (0x0000FFFFUL)
#define INTC_WUPEN_EIRQWUEN_0                          (0x00000001UL)
#define INTC_WUPEN_EIRQWUEN_1                          (0x00000002UL)
#define INTC_WUPEN_EIRQWUEN_2                          (0x00000004UL)
#define INTC_WUPEN_EIRQWUEN_3                          (0x00000008UL)
#define INTC_WUPEN_EIRQWUEN_4                          (0x00000010UL)
#define INTC_WUPEN_EIRQWUEN_5                          (0x00000020UL)
#define INTC_WUPEN_EIRQWUEN_6                          (0x00000040UL)
#define INTC_WUPEN_EIRQWUEN_7                          (0x00000080UL)
#define INTC_WUPEN_EIRQWUEN_8                          (0x00000100UL)
#define INTC_WUPEN_EIRQWUEN_9                          (0x00000200UL)
#define INTC_WUPEN_EIRQWUEN_10                         (0x00000400UL)
#define INTC_WUPEN_EIRQWUEN_11                         (0x00000800UL)
#define INTC_WUPEN_EIRQWUEN_12                         (0x00001000UL)
#define INTC_WUPEN_EIRQWUEN_13                         (0x00002000UL)
#define INTC_WUPEN_EIRQWUEN_14                         (0x00004000UL)
#define INTC_WUPEN_EIRQWUEN_15                         (0x00008000UL)
#define INTC_WUPEN_SWDTWUEN_POS                        (16U)
#define INTC_WUPEN_SWDTWUEN                            (0x00010000UL)
#define INTC_WUPEN_PVD1WUEN_POS                        (17U)
#define INTC_WUPEN_PVD1WUEN                            (0x00020000UL)
#define INTC_WUPEN_PVD2WUEN_POS                        (18U)
#define INTC_WUPEN_PVD2WUEN                            (0x00040000UL)
#define INTC_WUPEN_CMPWUEN_POS                         (19U)
#define INTC_WUPEN_CMPWUEN                             (0x00080000UL)
#define INTC_WUPEN_WKTMWUEN_POS                        (20U)
#define INTC_WUPEN_WKTMWUEN                            (0x00100000UL)
#define INTC_WUPEN_RTCALMWUEN_POS                      (21U)
#define INTC_WUPEN_RTCALMWUEN                          (0x00200000UL)
#define INTC_WUPEN_RTCPRDWUEN_POS                      (22U)
#define INTC_WUPEN_RTCPRDWUEN                          (0x00400000UL)
#define INTC_WUPEN_TMR0GCMWUEN_POS                     (23U)
#define INTC_WUPEN_TMR0GCMWUEN                         (0x00800000UL)
#define INTC_WUPEN_TMR2GCMWUEN_POS                     (24U)
#define INTC_WUPEN_TMR2GCMWUEN                         (0x01000000UL)
#define INTC_WUPEN_TMR2OVFWUEN_POS                     (25U)
#define INTC_WUPEN_TMR2OVFWUEN                         (0x02000000UL)
#define INTC_WUPEN_RXWUEN_POS                          (26U)
#define INTC_WUPEN_RXWUEN                              (0x04000000UL)
#define INTC_WUPEN_USHWUEN_POS                         (27U)
#define INTC_WUPEN_USHWUEN                             (0x08000000UL)
#define INTC_WUPEN_USFWUEN_POS                         (28U)
#define INTC_WUPEN_USFWUEN                             (0x10000000UL)
#define INTC_WUPEN_ETHWUEN_POS                         (29U)
#define INTC_WUPEN_ETHWUEN                             (0x20000000UL)

/*  Bit definition for INTC_EIFR register  */
#define INTC_EIFR_EIFR0_POS                            (0U)
#define INTC_EIFR_EIFR0                                (0x00000001UL)
#define INTC_EIFR_EIFR1_POS                            (1U)
#define INTC_EIFR_EIFR1                                (0x00000002UL)
#define INTC_EIFR_EIFR2_POS                            (2U)
#define INTC_EIFR_EIFR2                                (0x00000004UL)
#define INTC_EIFR_EIFR3_POS                            (3U)
#define INTC_EIFR_EIFR3                                (0x00000008UL)
#define INTC_EIFR_EIFR4_POS                            (4U)
#define INTC_EIFR_EIFR4                                (0x00000010UL)
#define INTC_EIFR_EIFR5_POS                            (5U)
#define INTC_EIFR_EIFR5                                (0x00000020UL)
#define INTC_EIFR_EIFR6_POS                            (6U)
#define INTC_EIFR_EIFR6                                (0x00000040UL)
#define INTC_EIFR_EIFR7_POS                            (7U)
#define INTC_EIFR_EIFR7                                (0x00000080UL)
#define INTC_EIFR_EIFR8_POS                            (8U)
#define INTC_EIFR_EIFR8                                (0x00000100UL)
#define INTC_EIFR_EIFR9_POS                            (9U)
#define INTC_EIFR_EIFR9                                (0x00000200UL)
#define INTC_EIFR_EIFR10_POS                           (10U)
#define INTC_EIFR_EIFR10                               (0x00000400UL)
#define INTC_EIFR_EIFR11_POS                           (11U)
#define INTC_EIFR_EIFR11                               (0x00000800UL)
#define INTC_EIFR_EIFR12_POS                           (12U)
#define INTC_EIFR_EIFR12                               (0x00001000UL)
#define INTC_EIFR_EIFR13_POS                           (13U)
#define INTC_EIFR_EIFR13                               (0x00002000UL)
#define INTC_EIFR_EIFR14_POS                           (14U)
#define INTC_EIFR_EIFR14                               (0x00004000UL)
#define INTC_EIFR_EIFR15_POS                           (15U)
#define INTC_EIFR_EIFR15                               (0x00008000UL)

/*  Bit definition for INTC_EIFCR register  */
#define INTC_EIFCR_EIFCR0_POS                          (0U)
#define INTC_EIFCR_EIFCR0                              (0x00000001UL)
#define INTC_EIFCR_EIFCR1_POS                          (1U)
#define INTC_EIFCR_EIFCR1                              (0x00000002UL)
#define INTC_EIFCR_EIFCR2_POS                          (2U)
#define INTC_EIFCR_EIFCR2                              (0x00000004UL)
#define INTC_EIFCR_EIFCR3_POS                          (3U)
#define INTC_EIFCR_EIFCR3                              (0x00000008UL)
#define INTC_EIFCR_EIFCR4_POS                          (4U)
#define INTC_EIFCR_EIFCR4                              (0x00000010UL)
#define INTC_EIFCR_EIFCR5_POS                          (5U)
#define INTC_EIFCR_EIFCR5                              (0x00000020UL)
#define INTC_EIFCR_EIFCR6_POS                          (6U)
#define INTC_EIFCR_EIFCR6                              (0x00000040UL)
#define INTC_EIFCR_EIFCR7_POS                          (7U)
#define INTC_EIFCR_EIFCR7                              (0x00000080UL)
#define INTC_EIFCR_EIFCR8_POS                          (8U)
#define INTC_EIFCR_EIFCR8                              (0x00000100UL)
#define INTC_EIFCR_EIFCR9_POS                          (9U)
#define INTC_EIFCR_EIFCR9                              (0x00000200UL)
#define INTC_EIFCR_EIFCR10_POS                         (10U)
#define INTC_EIFCR_EIFCR10                             (0x00000400UL)
#define INTC_EIFCR_EIFCR11_POS                         (11U)
#define INTC_EIFCR_EIFCR11                             (0x00000800UL)
#define INTC_EIFCR_EIFCR12_POS                         (12U)
#define INTC_EIFCR_EIFCR12                             (0x00001000UL)
#define INTC_EIFCR_EIFCR13_POS                         (13U)
#define INTC_EIFCR_EIFCR13                             (0x00002000UL)
#define INTC_EIFCR_EIFCR14_POS                         (14U)
#define INTC_EIFCR_EIFCR14                             (0x00004000UL)
#define INTC_EIFCR_EIFCR15_POS                         (15U)
#define INTC_EIFCR_EIFCR15                             (0x00008000UL)

/*  Bit definition for INTC_SEL register  */
#define INTC_SEL_INTSEL                                (0x000001FFUL)

/*  Bit definition for INTC_VSSEL register  */
#define INTC_VSSEL_VSEL0_POS                           (0U)
#define INTC_VSSEL_VSEL0                               (0x00000001UL)
#define INTC_VSSEL_VSEL1_POS                           (1U)
#define INTC_VSSEL_VSEL1                               (0x00000002UL)
#define INTC_VSSEL_VSEL2_POS                           (2U)
#define INTC_VSSEL_VSEL2                               (0x00000004UL)
#define INTC_VSSEL_VSEL3_POS                           (3U)
#define INTC_VSSEL_VSEL3                               (0x00000008UL)
#define INTC_VSSEL_VSEL4_POS                           (4U)
#define INTC_VSSEL_VSEL4                               (0x00000010UL)
#define INTC_VSSEL_VSEL5_POS                           (5U)
#define INTC_VSSEL_VSEL5                               (0x00000020UL)
#define INTC_VSSEL_VSEL6_POS                           (6U)
#define INTC_VSSEL_VSEL6                               (0x00000040UL)
#define INTC_VSSEL_VSEL7_POS                           (7U)
#define INTC_VSSEL_VSEL7                               (0x00000080UL)
#define INTC_VSSEL_VSEL8_POS                           (8U)
#define INTC_VSSEL_VSEL8                               (0x00000100UL)
#define INTC_VSSEL_VSEL9_POS                           (9U)
#define INTC_VSSEL_VSEL9                               (0x00000200UL)
#define INTC_VSSEL_VSEL10_POS                          (10U)
#define INTC_VSSEL_VSEL10                              (0x00000400UL)
#define INTC_VSSEL_VSEL11_POS                          (11U)
#define INTC_VSSEL_VSEL11                              (0x00000800UL)
#define INTC_VSSEL_VSEL12_POS                          (12U)
#define INTC_VSSEL_VSEL12                              (0x00001000UL)
#define INTC_VSSEL_VSEL13_POS                          (13U)
#define INTC_VSSEL_VSEL13                              (0x00002000UL)
#define INTC_VSSEL_VSEL14_POS                          (14U)
#define INTC_VSSEL_VSEL14                              (0x00004000UL)
#define INTC_VSSEL_VSEL15_POS                          (15U)
#define INTC_VSSEL_VSEL15                              (0x00008000UL)
#define INTC_VSSEL_VSEL16_POS                          (16U)
#define INTC_VSSEL_VSEL16                              (0x00010000UL)
#define INTC_VSSEL_VSEL17_POS                          (17U)
#define INTC_VSSEL_VSEL17                              (0x00020000UL)
#define INTC_VSSEL_VSEL18_POS                          (18U)
#define INTC_VSSEL_VSEL18                              (0x00040000UL)
#define INTC_VSSEL_VSEL19_POS                          (19U)
#define INTC_VSSEL_VSEL19                              (0x00080000UL)
#define INTC_VSSEL_VSEL20_POS                          (20U)
#define INTC_VSSEL_VSEL20                              (0x00100000UL)
#define INTC_VSSEL_VSEL21_POS                          (21U)
#define INTC_VSSEL_VSEL21                              (0x00200000UL)
#define INTC_VSSEL_VSEL22_POS                          (22U)
#define INTC_VSSEL_VSEL22                              (0x00400000UL)
#define INTC_VSSEL_VSEL23_POS                          (23U)
#define INTC_VSSEL_VSEL23                              (0x00800000UL)
#define INTC_VSSEL_VSEL24_POS                          (24U)
#define INTC_VSSEL_VSEL24                              (0x01000000UL)
#define INTC_VSSEL_VSEL25_POS                          (25U)
#define INTC_VSSEL_VSEL25                              (0x02000000UL)
#define INTC_VSSEL_VSEL26_POS                          (26U)
#define INTC_VSSEL_VSEL26                              (0x04000000UL)
#define INTC_VSSEL_VSEL27_POS                          (27U)
#define INTC_VSSEL_VSEL27                              (0x08000000UL)
#define INTC_VSSEL_VSEL28_POS                          (28U)
#define INTC_VSSEL_VSEL28                              (0x10000000UL)
#define INTC_VSSEL_VSEL29_POS                          (29U)
#define INTC_VSSEL_VSEL29                              (0x20000000UL)
#define INTC_VSSEL_VSEL30_POS                          (30U)
#define INTC_VSSEL_VSEL30                              (0x40000000UL)
#define INTC_VSSEL_VSEL31_POS                          (31U)
#define INTC_VSSEL_VSEL31                              (0x80000000UL)

/*  Bit definition for INTC_SWIER register  */
#define INTC_SWIER_SWIE0_POS                           (0U)
#define INTC_SWIER_SWIE0                               (0x00000001UL)
#define INTC_SWIER_SWIE1_POS                           (1U)
#define INTC_SWIER_SWIE1                               (0x00000002UL)
#define INTC_SWIER_SWIE2_POS                           (2U)
#define INTC_SWIER_SWIE2                               (0x00000004UL)
#define INTC_SWIER_SWIE3_POS                           (3U)
#define INTC_SWIER_SWIE3                               (0x00000008UL)
#define INTC_SWIER_SWIE4_POS                           (4U)
#define INTC_SWIER_SWIE4                               (0x00000010UL)
#define INTC_SWIER_SWIE5_POS                           (5U)
#define INTC_SWIER_SWIE5                               (0x00000020UL)
#define INTC_SWIER_SWIE6_POS                           (6U)
#define INTC_SWIER_SWIE6                               (0x00000040UL)
#define INTC_SWIER_SWIE7_POS                           (7U)
#define INTC_SWIER_SWIE7                               (0x00000080UL)
#define INTC_SWIER_SWIE8_POS                           (8U)
#define INTC_SWIER_SWIE8                               (0x00000100UL)
#define INTC_SWIER_SWIE9_POS                           (9U)
#define INTC_SWIER_SWIE9                               (0x00000200UL)
#define INTC_SWIER_SWIE10_POS                          (10U)
#define INTC_SWIER_SWIE10                              (0x00000400UL)
#define INTC_SWIER_SWIE11_POS                          (11U)
#define INTC_SWIER_SWIE11                              (0x00000800UL)
#define INTC_SWIER_SWIE12_POS                          (12U)
#define INTC_SWIER_SWIE12                              (0x00001000UL)
#define INTC_SWIER_SWIE13_POS                          (13U)
#define INTC_SWIER_SWIE13                              (0x00002000UL)
#define INTC_SWIER_SWIE14_POS                          (14U)
#define INTC_SWIER_SWIE14                              (0x00004000UL)
#define INTC_SWIER_SWIE15_POS                          (15U)
#define INTC_SWIER_SWIE15                              (0x00008000UL)
#define INTC_SWIER_SWIE16_POS                          (16U)
#define INTC_SWIER_SWIE16                              (0x00010000UL)
#define INTC_SWIER_SWIE17_POS                          (17U)
#define INTC_SWIER_SWIE17                              (0x00020000UL)
#define INTC_SWIER_SWIE18_POS                          (18U)
#define INTC_SWIER_SWIE18                              (0x00040000UL)
#define INTC_SWIER_SWIE19_POS                          (19U)
#define INTC_SWIER_SWIE19                              (0x00080000UL)
#define INTC_SWIER_SWIE20_POS                          (20U)
#define INTC_SWIER_SWIE20                              (0x00100000UL)
#define INTC_SWIER_SWIE21_POS                          (21U)
#define INTC_SWIER_SWIE21                              (0x00200000UL)
#define INTC_SWIER_SWIE22_POS                          (22U)
#define INTC_SWIER_SWIE22                              (0x00400000UL)
#define INTC_SWIER_SWIE23_POS                          (23U)
#define INTC_SWIER_SWIE23                              (0x00800000UL)
#define INTC_SWIER_SWIE24_POS                          (24U)
#define INTC_SWIER_SWIE24                              (0x01000000UL)
#define INTC_SWIER_SWIE25_POS                          (25U)
#define INTC_SWIER_SWIE25                              (0x02000000UL)
#define INTC_SWIER_SWIE26_POS                          (26U)
#define INTC_SWIER_SWIE26                              (0x04000000UL)
#define INTC_SWIER_SWIE27_POS                          (27U)
#define INTC_SWIER_SWIE27                              (0x08000000UL)
#define INTC_SWIER_SWIE28_POS                          (28U)
#define INTC_SWIER_SWIE28                              (0x10000000UL)
#define INTC_SWIER_SWIE29_POS                          (29U)
#define INTC_SWIER_SWIE29                              (0x20000000UL)
#define INTC_SWIER_SWIE30_POS                          (30U)
#define INTC_SWIER_SWIE30                              (0x40000000UL)
#define INTC_SWIER_SWIE31_POS                          (31U)
#define INTC_SWIER_SWIE31                              (0x80000000UL)

/*  Bit definition for INTC_EVTER register  */
#define INTC_EVTER_EVTE0_POS                           (0U)
#define INTC_EVTER_EVTE0                               (0x00000001UL)
#define INTC_EVTER_EVTE1_POS                           (1U)
#define INTC_EVTER_EVTE1                               (0x00000002UL)
#define INTC_EVTER_EVTE2_POS                           (2U)
#define INTC_EVTER_EVTE2                               (0x00000004UL)
#define INTC_EVTER_EVTE3_POS                           (3U)
#define INTC_EVTER_EVTE3                               (0x00000008UL)
#define INTC_EVTER_EVTE4_POS                           (4U)
#define INTC_EVTER_EVTE4                               (0x00000010UL)
#define INTC_EVTER_EVTE5_POS                           (5U)
#define INTC_EVTER_EVTE5                               (0x00000020UL)
#define INTC_EVTER_EVTE6_POS                           (6U)
#define INTC_EVTER_EVTE6                               (0x00000040UL)
#define INTC_EVTER_EVTE7_POS                           (7U)
#define INTC_EVTER_EVTE7                               (0x00000080UL)
#define INTC_EVTER_EVTE8_POS                           (8U)
#define INTC_EVTER_EVTE8                               (0x00000100UL)
#define INTC_EVTER_EVTE9_POS                           (9U)
#define INTC_EVTER_EVTE9                               (0x00000200UL)
#define INTC_EVTER_EVTE10_POS                          (10U)
#define INTC_EVTER_EVTE10                              (0x00000400UL)
#define INTC_EVTER_EVTE11_POS                          (11U)
#define INTC_EVTER_EVTE11                              (0x00000800UL)
#define INTC_EVTER_EVTE12_POS                          (12U)
#define INTC_EVTER_EVTE12                              (0x00001000UL)
#define INTC_EVTER_EVTE13_POS                          (13U)
#define INTC_EVTER_EVTE13                              (0x00002000UL)
#define INTC_EVTER_EVTE14_POS                          (14U)
#define INTC_EVTER_EVTE14                              (0x00004000UL)
#define INTC_EVTER_EVTE15_POS                          (15U)
#define INTC_EVTER_EVTE15                              (0x00008000UL)
#define INTC_EVTER_EVTE16_POS                          (16U)
#define INTC_EVTER_EVTE16                              (0x00010000UL)
#define INTC_EVTER_EVTE17_POS                          (17U)
#define INTC_EVTER_EVTE17                              (0x00020000UL)
#define INTC_EVTER_EVTE18_POS                          (18U)
#define INTC_EVTER_EVTE18                              (0x00040000UL)
#define INTC_EVTER_EVTE19_POS                          (19U)
#define INTC_EVTER_EVTE19                              (0x00080000UL)
#define INTC_EVTER_EVTE20_POS                          (20U)
#define INTC_EVTER_EVTE20                              (0x00100000UL)
#define INTC_EVTER_EVTE21_POS                          (21U)
#define INTC_EVTER_EVTE21                              (0x00200000UL)
#define INTC_EVTER_EVTE22_POS                          (22U)
#define INTC_EVTER_EVTE22                              (0x00400000UL)
#define INTC_EVTER_EVTE23_POS                          (23U)
#define INTC_EVTER_EVTE23                              (0x00800000UL)
#define INTC_EVTER_EVTE24_POS                          (24U)
#define INTC_EVTER_EVTE24                              (0x01000000UL)
#define INTC_EVTER_EVTE25_POS                          (25U)
#define INTC_EVTER_EVTE25                              (0x02000000UL)
#define INTC_EVTER_EVTE26_POS                          (26U)
#define INTC_EVTER_EVTE26                              (0x04000000UL)
#define INTC_EVTER_EVTE27_POS                          (27U)
#define INTC_EVTER_EVTE27                              (0x08000000UL)
#define INTC_EVTER_EVTE28_POS                          (28U)
#define INTC_EVTER_EVTE28                              (0x10000000UL)
#define INTC_EVTER_EVTE29_POS                          (29U)
#define INTC_EVTER_EVTE29                              (0x20000000UL)
#define INTC_EVTER_EVTE30_POS                          (30U)
#define INTC_EVTER_EVTE30                              (0x40000000UL)
#define INTC_EVTER_EVTE31_POS                          (31U)
#define INTC_EVTER_EVTE31                              (0x80000000UL)

/*  Bit definition for INTC_IER register  */
#define INTC_IER_IER0_POS                              (0U)
#define INTC_IER_IER0                                  (0x00000001UL)
#define INTC_IER_IER1_POS                              (1U)
#define INTC_IER_IER1                                  (0x00000002UL)
#define INTC_IER_IER2_POS                              (2U)
#define INTC_IER_IER2                                  (0x00000004UL)
#define INTC_IER_IER3_POS                              (3U)
#define INTC_IER_IER3                                  (0x00000008UL)
#define INTC_IER_IER4_POS                              (4U)
#define INTC_IER_IER4                                  (0x00000010UL)
#define INTC_IER_IER5_POS                              (5U)
#define INTC_IER_IER5                                  (0x00000020UL)
#define INTC_IER_IER6_POS                              (6U)
#define INTC_IER_IER6                                  (0x00000040UL)
#define INTC_IER_IER7_POS                              (7U)
#define INTC_IER_IER7                                  (0x00000080UL)
#define INTC_IER_IER8_POS                              (8U)
#define INTC_IER_IER8                                  (0x00000100UL)
#define INTC_IER_IER9_POS                              (9U)
#define INTC_IER_IER9                                  (0x00000200UL)
#define INTC_IER_IER10_POS                             (10U)
#define INTC_IER_IER10                                 (0x00000400UL)
#define INTC_IER_IER11_POS                             (11U)
#define INTC_IER_IER11                                 (0x00000800UL)
#define INTC_IER_IER12_POS                             (12U)
#define INTC_IER_IER12                                 (0x00001000UL)
#define INTC_IER_IER13_POS                             (13U)
#define INTC_IER_IER13                                 (0x00002000UL)
#define INTC_IER_IER14_POS                             (14U)
#define INTC_IER_IER14                                 (0x00004000UL)
#define INTC_IER_IER15_POS                             (15U)
#define INTC_IER_IER15                                 (0x00008000UL)
#define INTC_IER_IER16_POS                             (16U)
#define INTC_IER_IER16                                 (0x00010000UL)
#define INTC_IER_IER17_POS                             (17U)
#define INTC_IER_IER17                                 (0x00020000UL)
#define INTC_IER_IER18_POS                             (18U)
#define INTC_IER_IER18                                 (0x00040000UL)
#define INTC_IER_IER19_POS                             (19U)
#define INTC_IER_IER19                                 (0x00080000UL)
#define INTC_IER_IER20_POS                             (20U)
#define INTC_IER_IER20                                 (0x00100000UL)
#define INTC_IER_IER21_POS                             (21U)
#define INTC_IER_IER21                                 (0x00200000UL)
#define INTC_IER_IER22_POS                             (22U)
#define INTC_IER_IER22                                 (0x00400000UL)
#define INTC_IER_IER23_POS                             (23U)
#define INTC_IER_IER23                                 (0x00800000UL)
#define INTC_IER_IER24_POS                             (24U)
#define INTC_IER_IER24                                 (0x01000000UL)
#define INTC_IER_IER25_POS                             (25U)
#define INTC_IER_IER25                                 (0x02000000UL)
#define INTC_IER_IER26_POS                             (26U)
#define INTC_IER_IER26                                 (0x04000000UL)
#define INTC_IER_IER27_POS                             (27U)
#define INTC_IER_IER27                                 (0x08000000UL)
#define INTC_IER_IER28_POS                             (28U)
#define INTC_IER_IER28                                 (0x10000000UL)
#define INTC_IER_IER29_POS                             (29U)
#define INTC_IER_IER29                                 (0x20000000UL)
#define INTC_IER_IER30_POS                             (30U)
#define INTC_IER_IER30                                 (0x40000000UL)
#define INTC_IER_IER31_POS                             (31U)
#define INTC_IER_IER31                                 (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral KEYSCAN
*******************************************************************************/
/*  Bit definition for KEYSCAN_SCR register  */
#define KEYSCAN_SCR_KEYINSEL_POS                       (0U)
#define KEYSCAN_SCR_KEYINSEL                           (0x0000FFFFUL)
#define KEYSCAN_SCR_KEYINSEL_0                         (0x00000001UL)
#define KEYSCAN_SCR_KEYINSEL_1                         (0x00000002UL)
#define KEYSCAN_SCR_KEYINSEL_2                         (0x00000004UL)
#define KEYSCAN_SCR_KEYINSEL_3                         (0x00000008UL)
#define KEYSCAN_SCR_KEYINSEL_4                         (0x00000010UL)
#define KEYSCAN_SCR_KEYINSEL_5                         (0x00000020UL)
#define KEYSCAN_SCR_KEYINSEL_6                         (0x00000040UL)
#define KEYSCAN_SCR_KEYINSEL_7                         (0x00000080UL)
#define KEYSCAN_SCR_KEYINSEL_8                         (0x00000100UL)
#define KEYSCAN_SCR_KEYINSEL_9                         (0x00000200UL)
#define KEYSCAN_SCR_KEYINSEL_10                        (0x00000400UL)
#define KEYSCAN_SCR_KEYINSEL_11                        (0x00000800UL)
#define KEYSCAN_SCR_KEYINSEL_12                        (0x00001000UL)
#define KEYSCAN_SCR_KEYINSEL_13                        (0x00002000UL)
#define KEYSCAN_SCR_KEYINSEL_14                        (0x00004000UL)
#define KEYSCAN_SCR_KEYINSEL_15                        (0x00008000UL)
#define KEYSCAN_SCR_KEYOUTSEL_POS                      (16U)
#define KEYSCAN_SCR_KEYOUTSEL                          (0x00070000UL)
#define KEYSCAN_SCR_CKSEL_POS                          (20U)
#define KEYSCAN_SCR_CKSEL                              (0x00300000UL)
#define KEYSCAN_SCR_CKSEL_0                            (0x00100000UL)
#define KEYSCAN_SCR_CKSEL_1                            (0x00200000UL)
#define KEYSCAN_SCR_T_LLEVEL_POS                       (24U)
#define KEYSCAN_SCR_T_LLEVEL                           (0x1F000000UL)
#define KEYSCAN_SCR_T_HIZ_POS                          (29U)
#define KEYSCAN_SCR_T_HIZ                              (0xE0000000UL)

/*  Bit definition for KEYSCAN_SER register  */
#define KEYSCAN_SER_SEN                                (0x00000001UL)

/*  Bit definition for KEYSCAN_SSR register  */
#define KEYSCAN_SSR_INDEX                              (0x00000007UL)

/*******************************************************************************
                Bit definition for Peripheral MAU
*******************************************************************************/
/*  Bit definition for MAU_CSR register  */
#define MAU_CSR_START_POS                              (0U)
#define MAU_CSR_START                                  (0x00000001UL)
#define MAU_CSR_INTEN_POS                              (1U)
#define MAU_CSR_INTEN                                  (0x00000002UL)
#define MAU_CSR_BUSY_POS                               (3U)
#define MAU_CSR_BUSY                                   (0x00000008UL)
#define MAU_CSR_SHIFT_POS                              (8U)
#define MAU_CSR_SHIFT                                  (0x00001F00UL)

/*  Bit definition for MAU_DTR0 register  */
#define MAU_DTR0                                       (0xFFFFFFFFUL)

/*  Bit definition for MAU_RTR0 register  */
#define MAU_RTR0_SQRT_DOUT                             (0x0001FFFFUL)

/*  Bit definition for MAU_DTR1 register  */
#define MAU_DTR1_SIN_DIN                               (0x00000FFFUL)

/*  Bit definition for MAU_RTR1 register  */
#define MAU_RTR1_SIN_DOUT                              (0x0000FFFFUL)

/*******************************************************************************
                Bit definition for Peripheral MPU
*******************************************************************************/
/*  Bit definition for MPU_RGD register  */
#define MPU_RGD_MPURGSIZE_POS                          (0U)
#define MPU_RGD_MPURGSIZE                              (0x0000001FUL)
#define MPU_RGD_MPURGADDR_POS                          (5U)
#define MPU_RGD_MPURGADDR                              (0xFFFFFFE0UL)

/*  Bit definition for MPU_SR register  */
#define MPU_SR_SMPU1EAF_POS                            (0U)
#define MPU_SR_SMPU1EAF                                (0x00000001UL)
#define MPU_SR_SMPU2EAF_POS                            (1U)
#define MPU_SR_SMPU2EAF                                (0x00000002UL)
#define MPU_SR_FMPUEAF_POS                             (2U)
#define MPU_SR_FMPUEAF                                 (0x00000004UL)
#define MPU_SR_HMPUEAF_POS                             (3U)
#define MPU_SR_HMPUEAF                                 (0x00000008UL)
#define MPU_SR_EMPUEAF_POS                             (4U)
#define MPU_SR_EMPUEAF                                 (0x00000010UL)

/*  Bit definition for MPU_ECLR register  */
#define MPU_ECLR_SMPU1ECLR_POS                         (0U)
#define MPU_ECLR_SMPU1ECLR                             (0x00000001UL)
#define MPU_ECLR_SMPU2ECLR_POS                         (1U)
#define MPU_ECLR_SMPU2ECLR                             (0x00000002UL)
#define MPU_ECLR_FMPUECLR_POS                          (2U)
#define MPU_ECLR_FMPUECLR                              (0x00000004UL)
#define MPU_ECLR_HMPUECLR_POS                          (3U)
#define MPU_ECLR_HMPUECLR                              (0x00000008UL)
#define MPU_ECLR_EMPUECLR_POS                          (4U)
#define MPU_ECLR_EMPUECLR                              (0x00000010UL)

/*  Bit definition for MPU_WP register  */
#define MPU_WP_MPUWE_POS                               (0U)
#define MPU_WP_MPUWE                                   (0x00000001UL)
#define MPU_WP_WKEY_POS                                (1U)
#define MPU_WP_WKEY                                    (0x0000FFFEUL)

/*  Bit definition for MPU_IPPR register  */
#define MPU_IPPR_AESRDP_POS                            (0U)
#define MPU_IPPR_AESRDP                                (0x00000001UL)
#define MPU_IPPR_AESWRP_POS                            (1U)
#define MPU_IPPR_AESWRP                                (0x00000002UL)
#define MPU_IPPR_HASHRDP_POS                           (2U)
#define MPU_IPPR_HASHRDP                               (0x00000004UL)
#define MPU_IPPR_HASHWRP_POS                           (3U)
#define MPU_IPPR_HASHWRP                               (0x00000008UL)
#define MPU_IPPR_TRNGRDP_POS                           (4U)
#define MPU_IPPR_TRNGRDP                               (0x00000010UL)
#define MPU_IPPR_TRNGWRP_POS                           (5U)
#define MPU_IPPR_TRNGWRP                               (0x00000020UL)
#define MPU_IPPR_CRCRDP_POS                            (6U)
#define MPU_IPPR_CRCRDP                                (0x00000040UL)
#define MPU_IPPR_CRCWRP_POS                            (7U)
#define MPU_IPPR_CRCWRP                                (0x00000080UL)
#define MPU_IPPR_EFMRDP_POS                            (8U)
#define MPU_IPPR_EFMRDP                                (0x00000100UL)
#define MPU_IPPR_EFMWRP_POS                            (9U)
#define MPU_IPPR_EFMWRP                                (0x00000200UL)
#define MPU_IPPR_WDTRDP_POS                            (12U)
#define MPU_IPPR_WDTRDP                                (0x00001000UL)
#define MPU_IPPR_WDTWRP_POS                            (13U)
#define MPU_IPPR_WDTWRP                                (0x00002000UL)
#define MPU_IPPR_SWDTRDP_POS                           (14U)
#define MPU_IPPR_SWDTRDP                               (0x00004000UL)
#define MPU_IPPR_SWDTWRP_POS                           (15U)
#define MPU_IPPR_SWDTWRP                               (0x00008000UL)
#define MPU_IPPR_BKSRAMRDP_POS                         (16U)
#define MPU_IPPR_BKSRAMRDP                             (0x00010000UL)
#define MPU_IPPR_BKSRAMWRP_POS                         (17U)
#define MPU_IPPR_BKSRAMWRP                             (0x00020000UL)
#define MPU_IPPR_RTCRDP_POS                            (18U)
#define MPU_IPPR_RTCRDP                                (0x00040000UL)
#define MPU_IPPR_RTCWRP_POS                            (19U)
#define MPU_IPPR_RTCWRP                                (0x00080000UL)
#define MPU_IPPR_DMPURDP_POS                           (20U)
#define MPU_IPPR_DMPURDP                               (0x00100000UL)
#define MPU_IPPR_DMPUWRP_POS                           (21U)
#define MPU_IPPR_DMPUWRP                               (0x00200000UL)
#define MPU_IPPR_SRAMCRDP_POS                          (22U)
#define MPU_IPPR_SRAMCRDP                              (0x00400000UL)
#define MPU_IPPR_SRAMCWRP_POS                          (23U)
#define MPU_IPPR_SRAMCWRP                              (0x00800000UL)
#define MPU_IPPR_INTCRDP_POS                           (24U)
#define MPU_IPPR_INTCRDP                               (0x01000000UL)
#define MPU_IPPR_INTCWRP_POS                           (25U)
#define MPU_IPPR_INTCWRP                               (0x02000000UL)
#define MPU_IPPR_SYSCRDP_POS                           (26U)
#define MPU_IPPR_SYSCRDP                               (0x04000000UL)
#define MPU_IPPR_SYSCWRP_POS                           (27U)
#define MPU_IPPR_SYSCWRP                               (0x08000000UL)
#define MPU_IPPR_MSTPRDP_POS                           (28U)
#define MPU_IPPR_MSTPRDP                               (0x10000000UL)
#define MPU_IPPR_MSPTWRP_POS                           (29U)
#define MPU_IPPR_MSPTWRP                               (0x20000000UL)
#define MPU_IPPR_BUSERRE_POS                           (31U)
#define MPU_IPPR_BUSERRE                               (0x80000000UL)

/*  Bit definition for MPU_SRGE register  */
#define MPU_SRGE_RG0E_POS                              (0U)
#define MPU_SRGE_RG0E                                  (0x00000001UL)
#define MPU_SRGE_RG1E_POS                              (1U)
#define MPU_SRGE_RG1E                                  (0x00000002UL)
#define MPU_SRGE_RG2E_POS                              (2U)
#define MPU_SRGE_RG2E                                  (0x00000004UL)
#define MPU_SRGE_RG3E_POS                              (3U)
#define MPU_SRGE_RG3E                                  (0x00000008UL)
#define MPU_SRGE_RG4E_POS                              (4U)
#define MPU_SRGE_RG4E                                  (0x00000010UL)
#define MPU_SRGE_RG5E_POS                              (5U)
#define MPU_SRGE_RG5E                                  (0x00000020UL)
#define MPU_SRGE_RG6E_POS                              (6U)
#define MPU_SRGE_RG6E                                  (0x00000040UL)
#define MPU_SRGE_RG7E_POS                              (7U)
#define MPU_SRGE_RG7E                                  (0x00000080UL)
#define MPU_SRGE_RG8E_POS                              (8U)
#define MPU_SRGE_RG8E                                  (0x00000100UL)
#define MPU_SRGE_RG9E_POS                              (9U)
#define MPU_SRGE_RG9E                                  (0x00000200UL)
#define MPU_SRGE_RG10E_POS                             (10U)
#define MPU_SRGE_RG10E                                 (0x00000400UL)
#define MPU_SRGE_RG11E_POS                             (11U)
#define MPU_SRGE_RG11E                                 (0x00000800UL)
#define MPU_SRGE_RG12E_POS                             (12U)
#define MPU_SRGE_RG12E                                 (0x00001000UL)
#define MPU_SRGE_RG13E_POS                             (13U)
#define MPU_SRGE_RG13E                                 (0x00002000UL)
#define MPU_SRGE_RG14E_POS                             (14U)
#define MPU_SRGE_RG14E                                 (0x00004000UL)
#define MPU_SRGE_RG15E_POS                             (15U)
#define MPU_SRGE_RG15E                                 (0x00008000UL)

/*  Bit definition for MPU_SRGWP register  */
#define MPU_SRGWP_RG0WP_POS                            (0U)
#define MPU_SRGWP_RG0WP                                (0x00000001UL)
#define MPU_SRGWP_RG1WP_POS                            (1U)
#define MPU_SRGWP_RG1WP                                (0x00000002UL)
#define MPU_SRGWP_RG2WP_POS                            (2U)
#define MPU_SRGWP_RG2WP                                (0x00000004UL)
#define MPU_SRGWP_RG3WP_POS                            (3U)
#define MPU_SRGWP_RG3WP                                (0x00000008UL)
#define MPU_SRGWP_RG4WP_POS                            (4U)
#define MPU_SRGWP_RG4WP                                (0x00000010UL)
#define MPU_SRGWP_RG5WP_POS                            (5U)
#define MPU_SRGWP_RG5WP                                (0x00000020UL)
#define MPU_SRGWP_RG6WP_POS                            (6U)
#define MPU_SRGWP_RG6WP                                (0x00000040UL)
#define MPU_SRGWP_RG7WP_POS                            (7U)
#define MPU_SRGWP_RG7WP                                (0x00000080UL)
#define MPU_SRGWP_RG8WP_POS                            (8U)
#define MPU_SRGWP_RG8WP                                (0x00000100UL)
#define MPU_SRGWP_RG9WP_POS                            (9U)
#define MPU_SRGWP_RG9WP                                (0x00000200UL)
#define MPU_SRGWP_RG10WP_POS                           (10U)
#define MPU_SRGWP_RG10WP                               (0x00000400UL)
#define MPU_SRGWP_RG11WP_POS                           (11U)
#define MPU_SRGWP_RG11WP                               (0x00000800UL)
#define MPU_SRGWP_RG12WP_POS                           (12U)
#define MPU_SRGWP_RG12WP                               (0x00001000UL)
#define MPU_SRGWP_RG13WP_POS                           (13U)
#define MPU_SRGWP_RG13WP                               (0x00002000UL)
#define MPU_SRGWP_RG14WP_POS                           (14U)
#define MPU_SRGWP_RG14WP                               (0x00004000UL)
#define MPU_SRGWP_RG15WP_POS                           (15U)
#define MPU_SRGWP_RG15WP                               (0x00008000UL)

/*  Bit definition for MPU_SRGRP register  */
#define MPU_SRGRP_RG0RP_POS                            (0U)
#define MPU_SRGRP_RG0RP                                (0x00000001UL)
#define MPU_SRGRP_RG1RP_POS                            (1U)
#define MPU_SRGRP_RG1RP                                (0x00000002UL)
#define MPU_SRGRP_RG2RP_POS                            (2U)
#define MPU_SRGRP_RG2RP                                (0x00000004UL)
#define MPU_SRGRP_RG3RP_POS                            (3U)
#define MPU_SRGRP_RG3RP                                (0x00000008UL)
#define MPU_SRGRP_RG4RP_POS                            (4U)
#define MPU_SRGRP_RG4RP                                (0x00000010UL)
#define MPU_SRGRP_RG5RP_POS                            (5U)
#define MPU_SRGRP_RG5RP                                (0x00000020UL)
#define MPU_SRGRP_RG6RP_POS                            (6U)
#define MPU_SRGRP_RG6RP                                (0x00000040UL)
#define MPU_SRGRP_RG7RP_POS                            (7U)
#define MPU_SRGRP_RG7RP                                (0x00000080UL)
#define MPU_SRGRP_RG8RP_POS                            (8U)
#define MPU_SRGRP_RG8RP                                (0x00000100UL)
#define MPU_SRGRP_RG9RP_POS                            (9U)
#define MPU_SRGRP_RG9RP                                (0x00000200UL)
#define MPU_SRGRP_RG10RP_POS                           (10U)
#define MPU_SRGRP_RG10RP                               (0x00000400UL)
#define MPU_SRGRP_RG11RP_POS                           (11U)
#define MPU_SRGRP_RG11RP                               (0x00000800UL)
#define MPU_SRGRP_RG12RP_POS                           (12U)
#define MPU_SRGRP_RG12RP                               (0x00001000UL)
#define MPU_SRGRP_RG13RP_POS                           (13U)
#define MPU_SRGRP_RG13RP                               (0x00002000UL)
#define MPU_SRGRP_RG14RP_POS                           (14U)
#define MPU_SRGRP_RG14RP                               (0x00004000UL)
#define MPU_SRGRP_RG15RP_POS                           (15U)
#define MPU_SRGRP_RG15RP                               (0x00008000UL)

/*  Bit definition for MPU_SCR register  */
#define MPU_SCR_SMPUBRP_POS                            (0U)
#define MPU_SCR_SMPUBRP                                (0x00000001UL)
#define MPU_SCR_SMPUBWP_POS                            (1U)
#define MPU_SCR_SMPUBWP                                (0x00000002UL)
#define MPU_SCR_SMPUACT_POS                            (2U)
#define MPU_SCR_SMPUACT                                (0x0000000CUL)
#define MPU_SCR_SMPUACT_0                              (0x00000004UL)
#define MPU_SCR_SMPUACT_1                              (0x00000008UL)
#define MPU_SCR_SMPUE_POS                              (7U)
#define MPU_SCR_SMPUE                                  (0x00000080UL)

/*  Bit definition for MPU_FRGE register  */
#define MPU_FRGE_FRG0E_POS                             (0U)
#define MPU_FRGE_FRG0E                                 (0x00000001UL)
#define MPU_FRGE_FRG1E_POS                             (1U)
#define MPU_FRGE_FRG1E                                 (0x00000002UL)
#define MPU_FRGE_FRG2E_POS                             (2U)
#define MPU_FRGE_FRG2E                                 (0x00000004UL)
#define MPU_FRGE_FRG3E_POS                             (3U)
#define MPU_FRGE_FRG3E                                 (0x00000008UL)
#define MPU_FRGE_FRG4E_POS                             (4U)
#define MPU_FRGE_FRG4E                                 (0x00000010UL)
#define MPU_FRGE_FRG5E_POS                             (5U)
#define MPU_FRGE_FRG5E                                 (0x00000020UL)
#define MPU_FRGE_FRG6E_POS                             (6U)
#define MPU_FRGE_FRG6E                                 (0x00000040UL)
#define MPU_FRGE_FRG7E_POS                             (7U)
#define MPU_FRGE_FRG7E                                 (0x00000080UL)

/*  Bit definition for MPU_FRGWP register  */
#define MPU_FRGWP_FRG0WP_POS                           (0U)
#define MPU_FRGWP_FRG0WP                               (0x00000001UL)
#define MPU_FRGWP_FRG1WP_POS                           (1U)
#define MPU_FRGWP_FRG1WP                               (0x00000002UL)
#define MPU_FRGWP_FRG2WP_POS                           (2U)
#define MPU_FRGWP_FRG2WP                               (0x00000004UL)
#define MPU_FRGWP_FRG3WP_POS                           (3U)
#define MPU_FRGWP_FRG3WP                               (0x00000008UL)
#define MPU_FRGWP_FRG4WP_POS                           (4U)
#define MPU_FRGWP_FRG4WP                               (0x00000010UL)
#define MPU_FRGWP_FRG5WP_POS                           (5U)
#define MPU_FRGWP_FRG5WP                               (0x00000020UL)
#define MPU_FRGWP_FRG6WP_POS                           (6U)
#define MPU_FRGWP_FRG6WP                               (0x00000040UL)
#define MPU_FRGWP_FRG7WP_POS                           (7U)
#define MPU_FRGWP_FRG7WP                               (0x00000080UL)

/*  Bit definition for MPU_FRGRP register  */
#define MPU_FRGRP_FRG0RP_POS                           (0U)
#define MPU_FRGRP_FRG0RP                               (0x00000001UL)
#define MPU_FRGRP_FRG1RP_POS                           (1U)
#define MPU_FRGRP_FRG1RP                               (0x00000002UL)
#define MPU_FRGRP_FRG2RP_POS                           (2U)
#define MPU_FRGRP_FRG2RP                               (0x00000004UL)
#define MPU_FRGRP_FRG3RP_POS                           (3U)
#define MPU_FRGRP_FRG3RP                               (0x00000008UL)
#define MPU_FRGRP_FRG4RP_POS                           (4U)
#define MPU_FRGRP_FRG4RP                               (0x00000010UL)
#define MPU_FRGRP_FRG5RP_POS                           (5U)
#define MPU_FRGRP_FRG5RP                               (0x00000020UL)
#define MPU_FRGRP_FRG6RP_POS                           (6U)
#define MPU_FRGRP_FRG6RP                               (0x00000040UL)
#define MPU_FRGRP_FRG7RP_POS                           (7U)
#define MPU_FRGRP_FRG7RP                               (0x00000080UL)

/*  Bit definition for MPU_FCR register  */
#define MPU_FCR_FMPUBRP_POS                            (0U)
#define MPU_FCR_FMPUBRP                                (0x00000001UL)
#define MPU_FCR_FMPUBWP_POS                            (1U)
#define MPU_FCR_FMPUBWP                                (0x00000002UL)
#define MPU_FCR_FMPUACT_POS                            (2U)
#define MPU_FCR_FMPUACT                                (0x0000000CUL)
#define MPU_FCR_FMPUACT_0                              (0x00000004UL)
#define MPU_FCR_FMPUACT_1                              (0x00000008UL)
#define MPU_FCR_FMPUE_POS                              (7U)
#define MPU_FCR_FMPUE                                  (0x00000080UL)

/*  Bit definition for MPU_HRGE register  */
#define MPU_HRGE_HRG0E_POS                             (0U)
#define MPU_HRGE_HRG0E                                 (0x00000001UL)
#define MPU_HRGE_HRG1E_POS                             (1U)
#define MPU_HRGE_HRG1E                                 (0x00000002UL)
#define MPU_HRGE_HRG2E_POS                             (2U)
#define MPU_HRGE_HRG2E                                 (0x00000004UL)
#define MPU_HRGE_HRG3E_POS                             (3U)
#define MPU_HRGE_HRG3E                                 (0x00000008UL)
#define MPU_HRGE_HRG4E_POS                             (4U)
#define MPU_HRGE_HRG4E                                 (0x00000010UL)
#define MPU_HRGE_HRG5E_POS                             (5U)
#define MPU_HRGE_HRG5E                                 (0x00000020UL)
#define MPU_HRGE_HRG6E_POS                             (6U)
#define MPU_HRGE_HRG6E                                 (0x00000040UL)
#define MPU_HRGE_HRG7E_POS                             (7U)
#define MPU_HRGE_HRG7E                                 (0x00000080UL)

/*  Bit definition for MPU_HRGWP register  */
#define MPU_HRGWP_HRG0WP_POS                           (0U)
#define MPU_HRGWP_HRG0WP                               (0x00000001UL)
#define MPU_HRGWP_HRG1WP_POS                           (1U)
#define MPU_HRGWP_HRG1WP                               (0x00000002UL)
#define MPU_HRGWP_HRG2WP_POS                           (2U)
#define MPU_HRGWP_HRG2WP                               (0x00000004UL)
#define MPU_HRGWP_HRG3WP_POS                           (3U)
#define MPU_HRGWP_HRG3WP                               (0x00000008UL)
#define MPU_HRGWP_HRG4WP_POS                           (4U)
#define MPU_HRGWP_HRG4WP                               (0x00000010UL)
#define MPU_HRGWP_HRG5WP_POS                           (5U)
#define MPU_HRGWP_HRG5WP                               (0x00000020UL)
#define MPU_HRGWP_HRG6WP_POS                           (6U)
#define MPU_HRGWP_HRG6WP                               (0x00000040UL)
#define MPU_HRGWP_HRG7WP_POS                           (7U)
#define MPU_HRGWP_HRG7WP                               (0x00000080UL)

/*  Bit definition for MPU_HRGRP register  */
#define MPU_HRGRP_HRG0RP_POS                           (0U)
#define MPU_HRGRP_HRG0RP                               (0x00000001UL)
#define MPU_HRGRP_HRG1RP_POS                           (1U)
#define MPU_HRGRP_HRG1RP                               (0x00000002UL)
#define MPU_HRGRP_HRG2RP_POS                           (2U)
#define MPU_HRGRP_HRG2RP                               (0x00000004UL)
#define MPU_HRGRP_HRG3RP_POS                           (3U)
#define MPU_HRGRP_HRG3RP                               (0x00000008UL)
#define MPU_HRGRP_HRG4RP_POS                           (4U)
#define MPU_HRGRP_HRG4RP                               (0x00000010UL)
#define MPU_HRGRP_HRG5RP_POS                           (5U)
#define MPU_HRGRP_HRG5RP                               (0x00000020UL)
#define MPU_HRGRP_HRG6RP_POS                           (6U)
#define MPU_HRGRP_HRG6RP                               (0x00000040UL)
#define MPU_HRGRP_HRG7RP_POS                           (7U)
#define MPU_HRGRP_HRG7RP                               (0x00000080UL)

/*  Bit definition for MPU_HCR register  */
#define MPU_HCR_HMPUBRP_POS                            (0U)
#define MPU_HCR_HMPUBRP                                (0x00000001UL)
#define MPU_HCR_HMPUBWP_POS                            (1U)
#define MPU_HCR_HMPUBWP                                (0x00000002UL)
#define MPU_HCR_HMPUACT_POS                            (2U)
#define MPU_HCR_HMPUACT                                (0x0000000CUL)
#define MPU_HCR_HMPUACT_0                              (0x00000004UL)
#define MPU_HCR_HMPUACT_1                              (0x00000008UL)
#define MPU_HCR_HMPUE_POS                              (7U)
#define MPU_HCR_HMPUE                                  (0x00000080UL)

/*  Bit definition for MPU_ERGE register  */
#define MPU_ERGE_ERG0E_POS                             (0U)
#define MPU_ERGE_ERG0E                                 (0x00000001UL)
#define MPU_ERGE_ERG1E_POS                             (1U)
#define MPU_ERGE_ERG1E                                 (0x00000002UL)
#define MPU_ERGE_ERG2E_POS                             (2U)
#define MPU_ERGE_ERG2E                                 (0x00000004UL)
#define MPU_ERGE_ERG3E_POS                             (3U)
#define MPU_ERGE_ERG3E                                 (0x00000008UL)
#define MPU_ERGE_ERG4E_POS                             (4U)
#define MPU_ERGE_ERG4E                                 (0x00000010UL)
#define MPU_ERGE_ERG5E_POS                             (5U)
#define MPU_ERGE_ERG5E                                 (0x00000020UL)
#define MPU_ERGE_ERG6E_POS                             (6U)
#define MPU_ERGE_ERG6E                                 (0x00000040UL)
#define MPU_ERGE_ERG7E_POS                             (7U)
#define MPU_ERGE_ERG7E                                 (0x00000080UL)

/*  Bit definition for MPU_ERGWP register  */
#define MPU_ERGWP_ERG0WP_POS                           (0U)
#define MPU_ERGWP_ERG0WP                               (0x00000001UL)
#define MPU_ERGWP_ERG1WP_POS                           (1U)
#define MPU_ERGWP_ERG1WP                               (0x00000002UL)
#define MPU_ERGWP_ERG2WP_POS                           (2U)
#define MPU_ERGWP_ERG2WP                               (0x00000004UL)
#define MPU_ERGWP_ERG3WP_POS                           (3U)
#define MPU_ERGWP_ERG3WP                               (0x00000008UL)
#define MPU_ERGWP_ERG4WP_POS                           (4U)
#define MPU_ERGWP_ERG4WP                               (0x00000010UL)
#define MPU_ERGWP_ERG5WP_POS                           (5U)
#define MPU_ERGWP_ERG5WP                               (0x00000020UL)
#define MPU_ERGWP_ERG6WP_POS                           (6U)
#define MPU_ERGWP_ERG6WP                               (0x00000040UL)
#define MPU_ERGWP_ERG7WP_POS                           (7U)
#define MPU_ERGWP_ERG7WP                               (0x00000080UL)

/*  Bit definition for MPU_ERGRP register  */
#define MPU_ERGRP_ERG0RP_POS                           (0U)
#define MPU_ERGRP_ERG0RP                               (0x00000001UL)
#define MPU_ERGRP_ERG1RP_POS                           (1U)
#define MPU_ERGRP_ERG1RP                               (0x00000002UL)
#define MPU_ERGRP_ERG2RP_POS                           (2U)
#define MPU_ERGRP_ERG2RP                               (0x00000004UL)
#define MPU_ERGRP_ERG3RP_POS                           (3U)
#define MPU_ERGRP_ERG3RP                               (0x00000008UL)
#define MPU_ERGRP_ERG4RP_POS                           (4U)
#define MPU_ERGRP_ERG4RP                               (0x00000010UL)
#define MPU_ERGRP_ERG5RP_POS                           (5U)
#define MPU_ERGRP_ERG5RP                               (0x00000020UL)
#define MPU_ERGRP_ERG6RP_POS                           (6U)
#define MPU_ERGRP_ERG6RP                               (0x00000040UL)
#define MPU_ERGRP_ERG7RP_POS                           (7U)
#define MPU_ERGRP_ERG7RP                               (0x00000080UL)

/*  Bit definition for MPU_ECR register  */
#define MPU_ECR_EMPUBRP_POS                            (0U)
#define MPU_ECR_EMPUBRP                                (0x00000001UL)
#define MPU_ECR_EMPUBWP_POS                            (1U)
#define MPU_ECR_EMPUBWP                                (0x00000002UL)
#define MPU_ECR_EMPUACT_POS                            (2U)
#define MPU_ECR_EMPUACT                                (0x0000000CUL)
#define MPU_ECR_EMPUACT_0                              (0x00000004UL)
#define MPU_ECR_EMPUACT_1                              (0x00000008UL)
#define MPU_ECR_EMPUE_POS                              (7U)
#define MPU_ECR_EMPUE                                  (0x00000080UL)

/*******************************************************************************
                Bit definition for Peripheral NFC
*******************************************************************************/
/*  Bit definition for NFC_DATR_BASE register  */
#define NFC_DATR_BASE                                  (0xFFFFFFFFUL)

/*  Bit definition for NFC_CMDR register  */
#define NFC_CMDR_CMD_POS                               (0U)
#define NFC_CMDR_CMD                                   (0x000000FFUL)
#define NFC_CMDR_ARG_POS                               (8U)
#define NFC_CMDR_ARG                                   (0xFFFFFF00UL)

/*  Bit definition for NFC_IDXR0 register  */
#define NFC_IDXR0                                      (0xFFFFFFFFUL)

/*  Bit definition for NFC_IENR register  */
#define NFC_IENR_ECCEUEN_POS                           (0U)
#define NFC_IENR_ECCEUEN                               (0x00000001UL)
#define NFC_IENR_ECCECEN_POS                           (1U)
#define NFC_IENR_ECCECEN                               (0x00000002UL)
#define NFC_IENR_ECCCEN_POS                            (4U)
#define NFC_IENR_ECCCEN                                (0x00000010UL)
#define NFC_IENR_ECCEEN_POS                            (6U)
#define NFC_IENR_ECCEEN                                (0x00000040UL)
#define NFC_IENR_ECCDIS_POS                            (7U)
#define NFC_IENR_ECCDIS                                (0x00000080UL)
#define NFC_IENR_RBEN_POS                              (8U)
#define NFC_IENR_RBEN                                  (0x0000FF00UL)
#define NFC_IENR_RBEN_0                                (0x00000100UL)
#define NFC_IENR_RBEN_1                                (0x00000200UL)
#define NFC_IENR_RBEN_2                                (0x00000400UL)
#define NFC_IENR_RBEN_3                                (0x00000800UL)
#define NFC_IENR_RBEN_4                                (0x00001000UL)
#define NFC_IENR_RBEN_5                                (0x00002000UL)
#define NFC_IENR_RBEN_6                                (0x00004000UL)
#define NFC_IENR_RBEN_7                                (0x00008000UL)

/*  Bit definition for NFC_ISTR register  */
#define NFC_ISTR_ECCEUST_POS                           (0U)
#define NFC_ISTR_ECCEUST                               (0x00000001UL)
#define NFC_ISTR_ECCECST_POS                           (1U)
#define NFC_ISTR_ECCECST                               (0x00000002UL)
#define NFC_ISTR_ECCCST_POS                            (4U)
#define NFC_ISTR_ECCCST                                (0x00000010UL)
#define NFC_ISTR_ECCEST_POS                            (6U)
#define NFC_ISTR_ECCEST                                (0x00000040UL)
#define NFC_ISTR_RBST_POS                              (8U)
#define NFC_ISTR_RBST                                  (0x0000FF00UL)
#define NFC_ISTR_RBST_0                                (0x00000100UL)
#define NFC_ISTR_RBST_1                                (0x00000200UL)
#define NFC_ISTR_RBST_2                                (0x00000400UL)
#define NFC_ISTR_RBST_3                                (0x00000800UL)
#define NFC_ISTR_RBST_4                                (0x00001000UL)
#define NFC_ISTR_RBST_5                                (0x00002000UL)
#define NFC_ISTR_RBST_6                                (0x00004000UL)
#define NFC_ISTR_RBST_7                                (0x00008000UL)

/*  Bit definition for NFC_IRSR register  */
#define NFC_IRSR_ECCEURS_POS                           (0U)
#define NFC_IRSR_ECCEURS                               (0x00000001UL)
#define NFC_IRSR_ECCECRS_POS                           (1U)
#define NFC_IRSR_ECCECRS                               (0x00000002UL)
#define NFC_IRSR_ECCCRS_POS                            (4U)
#define NFC_IRSR_ECCCRS                                (0x00000010UL)
#define NFC_IRSR_ECCERS_POS                            (6U)
#define NFC_IRSR_ECCERS                                (0x00000040UL)
#define NFC_IRSR_RBRS_POS                              (8U)
#define NFC_IRSR_RBRS                                  (0x0000FF00UL)
#define NFC_IRSR_RBRS_0                                (0x00000100UL)
#define NFC_IRSR_RBRS_1                                (0x00000200UL)
#define NFC_IRSR_RBRS_2                                (0x00000400UL)
#define NFC_IRSR_RBRS_3                                (0x00000800UL)
#define NFC_IRSR_RBRS_4                                (0x00001000UL)
#define NFC_IRSR_RBRS_5                                (0x00002000UL)
#define NFC_IRSR_RBRS_6                                (0x00004000UL)
#define NFC_IRSR_RBRS_7                                (0x00008000UL)

/*  Bit definition for NFC_IDXR1 register  */
#define NFC_IDXR1_IDX1                                 (0x000000FFUL)

/*  Bit definition for NFC_TMCR0 register  */
#define NFC_TMCR0_TS_POS                               (0U)
#define NFC_TMCR0_TS                                   (0x000000FFUL)
#define NFC_TMCR0_TWP_POS                              (8U)
#define NFC_TMCR0_TWP                                  (0x0000FF00UL)
#define NFC_TMCR0_TRP_POS                              (16U)
#define NFC_TMCR0_TRP                                  (0x00FF0000UL)
#define NFC_TMCR0_TH_POS                               (24U)
#define NFC_TMCR0_TH                                   (0xFF000000UL)

/*  Bit definition for NFC_TMCR1 register  */
#define NFC_TMCR1_TWH_POS                              (0U)
#define NFC_TMCR1_TWH                                  (0x000000FFUL)
#define NFC_TMCR1_TRH_POS                              (8U)
#define NFC_TMCR1_TRH                                  (0x0000FF00UL)
#define NFC_TMCR1_TRR_POS                              (16U)
#define NFC_TMCR1_TRR                                  (0x00FF0000UL)
#define NFC_TMCR1_TWB_POS                              (24U)
#define NFC_TMCR1_TWB                                  (0xFF000000UL)

/*  Bit definition for NFC_BACR register  */
#define NFC_BACR_SIZE_POS                              (0U)
#define NFC_BACR_SIZE                                  (0x00000007UL)
#define NFC_BACR_B16BIT_POS                            (3U)
#define NFC_BACR_B16BIT                                (0x00000008UL)
#define NFC_BACR_BANK_POS                              (6U)
#define NFC_BACR_BANK                                  (0x000000C0UL)
#define NFC_BACR_BANK_0                                (0x00000040UL)
#define NFC_BACR_BANK_1                                (0x00000080UL)
#define NFC_BACR_PAGE_POS                              (8U)
#define NFC_BACR_PAGE                                  (0x00000300UL)
#define NFC_BACR_PAGE_0                                (0x00000100UL)
#define NFC_BACR_PAGE_1                                (0x00000200UL)
#define NFC_BACR_WP_POS                                (10U)
#define NFC_BACR_WP                                    (0x00000400UL)
#define NFC_BACR_ECCM_POS                              (11U)
#define NFC_BACR_ECCM                                  (0x00001800UL)
#define NFC_BACR_ECCM_0                                (0x00000800UL)
#define NFC_BACR_ECCM_1                                (0x00001000UL)
#define NFC_BACR_RAC_POS                               (13U)
#define NFC_BACR_RAC                                   (0x00002000UL)
#define NFC_BACR_SCS_POS                               (16U)
#define NFC_BACR_SCS                                   (0x00FF0000UL)

/*  Bit definition for NFC_TMCR2 register  */
#define NFC_TMCR2_TCCS_POS                             (0U)
#define NFC_TMCR2_TCCS                                 (0x000000FFUL)
#define NFC_TMCR2_TWTR_POS                             (8U)
#define NFC_TMCR2_TWTR                                 (0x0000FF00UL)
#define NFC_TMCR2_TRTW_POS                             (16U)
#define NFC_TMCR2_TRTW                                 (0x00FF0000UL)
#define NFC_TMCR2_TADL_POS                             (24U)
#define NFC_TMCR2_TADL                                 (0xFF000000UL)

/*  Bit definition for NFC_ECCR register  */
#define NFC_ECCR_ERRLOC_POS                            (0U)
#define NFC_ECCR_ERRLOC                                (0x00000FFFUL)
#define NFC_ECCR_SE_POS                                (12U)
#define NFC_ECCR_SE                                    (0x00001000UL)
#define NFC_ECCR_ME_POS                                (13U)
#define NFC_ECCR_ME                                    (0x00002000UL)

/*  Bit definition for NFC_ECC_STAT register  */
#define NFC_ECC_STAT_ERRSEC                            (0x0000FFFFUL)

/*  Bit definition for NFC_ECC_SYND_0 register  */
#define NFC_ECC_SYND_0_S1_POS                          (0U)
#define NFC_ECC_SYND_0_S1                              (0x00001FFFUL)
#define NFC_ECC_SYND_0_S2_POS                          (16U)
#define NFC_ECC_SYND_0_S2                              (0x1FFF0000UL)

/*  Bit definition for NFC_ECC_SYND_1 register  */
#define NFC_ECC_SYND_1_S3_POS                          (0U)
#define NFC_ECC_SYND_1_S3                              (0x00001FFFUL)
#define NFC_ECC_SYND_1_S4_POS                          (16U)
#define NFC_ECC_SYND_1_S4                              (0x1FFF0000UL)

/*  Bit definition for NFC_ECC_SYND_2 register  */
#define NFC_ECC_SYND_2_S5_POS                          (0U)
#define NFC_ECC_SYND_2_S5                              (0x00001FFFUL)
#define NFC_ECC_SYND_2_S6_POS                          (16U)
#define NFC_ECC_SYND_2_S6                              (0x1FFF0000UL)

/*  Bit definition for NFC_ECC_SYND_3 register  */
#define NFC_ECC_SYND_3_S7_POS                          (0U)
#define NFC_ECC_SYND_3_S7                              (0x00001FFFUL)
#define NFC_ECC_SYND_3_S8_POS                          (16U)
#define NFC_ECC_SYND_3_S8                              (0x1FFF0000UL)

/*******************************************************************************
                Bit definition for Peripheral OTS
*******************************************************************************/
/*  Bit definition for OTS_PDR register  */
#define OTS_PDR_TSPD1_POS                              (0U)
#define OTS_PDR_TSPD1                                  (0x0000FFFFUL)
#define OTS_PDR_TSPD2_POS                              (16U)
#define OTS_PDR_TSPD2                                  (0xFFFF0000UL)

/*  Bit definition for OTS_CTL register  */
#define OTS_CTL_OTSST_POS                              (0U)
#define OTS_CTL_OTSST                                  (0x0001U)
#define OTS_CTL_OTSCK_POS                              (1U)
#define OTS_CTL_OTSCK                                  (0x0002U)
#define OTS_CTL_OTSIE_POS                              (2U)
#define OTS_CTL_OTSIE                                  (0x0004U)
#define OTS_CTL_TSSTP_POS                              (3U)
#define OTS_CTL_TSSTP                                  (0x0008U)

/*  Bit definition for OTS_DR register  */
#define OTS_DR                                         (0xFFFFU)

/*  Bit definition for OTS_ECR register  */
#define OTS_ECR                                        (0xFFFFU)

/*******************************************************************************
                Bit definition for Peripheral PERIC
*******************************************************************************/
/*  Bit definition for PERIC_USB_SYCTLREG register  */
#define PERIC_USB_SYCTLREG_USBFS_DFB_POS               (0U)
#define PERIC_USB_SYCTLREG_USBFS_DFB                   (0x00000001UL)
#define PERIC_USB_SYCTLREG_USBFS_SOFEN_POS             (1U)
#define PERIC_USB_SYCTLREG_USBFS_SOFEN                 (0x00000002UL)
#define PERIC_USB_SYCTLREG_USBHS_DFB_POS               (8U)
#define PERIC_USB_SYCTLREG_USBHS_DFB                   (0x00000100UL)
#define PERIC_USB_SYCTLREG_USBHS_SOFEN_POS             (9U)
#define PERIC_USB_SYCTLREG_USBHS_SOFEN                 (0x00000200UL)
#define PERIC_USB_SYCTLREG_USBHS_FSPHYE_POS            (10U)
#define PERIC_USB_SYCTLREG_USBHS_FSPHYE                (0x00000400UL)
#define PERIC_USB_SYCTLREG_USBFS_NFS_POS               (16U)
#define PERIC_USB_SYCTLREG_USBFS_NFS                   (0x00030000UL)
#define PERIC_USB_SYCTLREG_USBFS_NFS_0                 (0x00010000UL)
#define PERIC_USB_SYCTLREG_USBFS_NFS_1                 (0x00020000UL)
#define PERIC_USB_SYCTLREG_USBFS_NFE_POS               (18U)
#define PERIC_USB_SYCTLREG_USBFS_NFE                   (0x00040000UL)
#define PERIC_USB_SYCTLREG_USBHS_NFS_POS               (24U)
#define PERIC_USB_SYCTLREG_USBHS_NFS                   (0x03000000UL)
#define PERIC_USB_SYCTLREG_USBHS_NFS_0                 (0x01000000UL)
#define PERIC_USB_SYCTLREG_USBHS_NFS_1                 (0x02000000UL)
#define PERIC_USB_SYCTLREG_USBHS_NFE_POS               (26U)
#define PERIC_USB_SYCTLREG_USBHS_NFE                   (0x04000000UL)

/*  Bit definition for PERIC_SDIOC_SYCTLREG register  */
#define PERIC_SDIOC_SYCTLREG_SELMMC1_POS               (1U)
#define PERIC_SDIOC_SYCTLREG_SELMMC1                   (0x00000002UL)
#define PERIC_SDIOC_SYCTLREG_SELMMC2_POS               (3U)
#define PERIC_SDIOC_SYCTLREG_SELMMC2                   (0x00000008UL)

/*  Bit definition for PERIC_NFC_STCR register  */
#define PERIC_NFC_STCR_OPENP                           (0x00000001UL)

/*  Bit definition for PERIC_NFC_ENAR register  */
#define PERIC_NFC_ENAR_NFCEN_POS                       (2U)
#define PERIC_NFC_ENAR_NFCEN                           (0x00000004UL)

/*  Bit definition for PERIC_SMC_ENAR register  */
#define PERIC_SMC_ENAR_SMCEN_POS                       (1U)
#define PERIC_SMC_ENAR_SMCEN                           (0x00000002UL)

/*  Bit definition for PERIC_DMC_ENAR register  */
#define PERIC_DMC_ENAR_DMCEN                           (0x00000001UL)

/*  Bit definition for PERIC_USART1_NFC register  */
#define PERIC_USART1_NFC_USASRT1_NFS_POS               (0U)
#define PERIC_USART1_NFC_USASRT1_NFS                   (0x00000003UL)
#define PERIC_USART1_NFC_USASRT1_NFS_0                 (0x00000001UL)
#define PERIC_USART1_NFC_USASRT1_NFS_1                 (0x00000002UL)
#define PERIC_USART1_NFC_USART1_NFE_POS                (2U)
#define PERIC_USART1_NFC_USART1_NFE                    (0x00000004UL)

/*  Bit definition for PERIC_NFC_STSR register  */
#define PERIC_NFC_STSR_CHIP_BUSY_POS                   (0U)
#define PERIC_NFC_STSR_CHIP_BUSY                       (0x000000FFUL)
#define PERIC_NFC_STSR_CHIP_BUSY_0                     (0x00000001UL)
#define PERIC_NFC_STSR_CHIP_BUSY_1                     (0x00000002UL)
#define PERIC_NFC_STSR_CHIP_BUSY_2                     (0x00000004UL)
#define PERIC_NFC_STSR_CHIP_BUSY_3                     (0x00000008UL)
#define PERIC_NFC_STSR_CHIP_BUSY_4                     (0x00000010UL)
#define PERIC_NFC_STSR_CHIP_BUSY_5                     (0x00000020UL)
#define PERIC_NFC_STSR_CHIP_BUSY_6                     (0x00000040UL)
#define PERIC_NFC_STSR_CHIP_BUSY_7                     (0x00000080UL)
#define PERIC_NFC_STSR_PECC_POS                        (8U)
#define PERIC_NFC_STSR_PECC                            (0x00000100UL)

/*******************************************************************************
                Bit definition for Peripheral PWC
*******************************************************************************/
/*  Bit definition for PWC_FCG0 register  */
#define PWC_FCG0_SRAMH_POS                             (0U)
#define PWC_FCG0_SRAMH                                 (0x00000001UL)
#define PWC_FCG0_SRAM1_POS                             (4U)
#define PWC_FCG0_SRAM1                                 (0x00000010UL)
#define PWC_FCG0_SRAM2_POS                             (5U)
#define PWC_FCG0_SRAM2                                 (0x00000020UL)
#define PWC_FCG0_SRAM3_POS                             (6U)
#define PWC_FCG0_SRAM3                                 (0x00000040UL)
#define PWC_FCG0_SRAM4_POS                             (7U)
#define PWC_FCG0_SRAM4                                 (0x00000080UL)
#define PWC_FCG0_SRAMB_POS                             (10U)
#define PWC_FCG0_SRAMB                                 (0x00000400UL)
#define PWC_FCG0_KEY_POS                               (13U)
#define PWC_FCG0_KEY                                   (0x00002000UL)
#define PWC_FCG0_DMA1_POS                              (14U)
#define PWC_FCG0_DMA1                                  (0x00004000UL)
#define PWC_FCG0_DMA2_POS                              (15U)
#define PWC_FCG0_DMA2                                  (0x00008000UL)
#define PWC_FCG0_FCM_POS                               (16U)
#define PWC_FCG0_FCM                                   (0x00010000UL)
#define PWC_FCG0_AOS_POS                               (17U)
#define PWC_FCG0_AOS                                   (0x00020000UL)
#define PWC_FCG0_CTC_POS                               (18U)
#define PWC_FCG0_CTC                                   (0x00040000UL)
#define PWC_FCG0_MAU_POS                               (19U)
#define PWC_FCG0_MAU                                   (0x00080000UL)
#define PWC_FCG0_AES_POS                               (20U)
#define PWC_FCG0_AES                                   (0x00100000UL)
#define PWC_FCG0_HASH_POS                              (21U)
#define PWC_FCG0_HASH                                  (0x00200000UL)
#define PWC_FCG0_TRNG_POS                              (22U)
#define PWC_FCG0_TRNG                                  (0x00400000UL)
#define PWC_FCG0_CRC_POS                               (23U)
#define PWC_FCG0_CRC                                   (0x00800000UL)
#define PWC_FCG0_DCU1_POS                              (24U)
#define PWC_FCG0_DCU1                                  (0x01000000UL)
#define PWC_FCG0_DCU2_POS                              (25U)
#define PWC_FCG0_DCU2                                  (0x02000000UL)
#define PWC_FCG0_DCU3_POS                              (26U)
#define PWC_FCG0_DCU3                                  (0x04000000UL)
#define PWC_FCG0_DCU4_POS                              (27U)
#define PWC_FCG0_DCU4                                  (0x08000000UL)
#define PWC_FCG0_DCU5_POS                              (28U)
#define PWC_FCG0_DCU5                                  (0x10000000UL)
#define PWC_FCG0_DCU6_POS                              (29U)
#define PWC_FCG0_DCU6                                  (0x20000000UL)
#define PWC_FCG0_DCU7_POS                              (30U)
#define PWC_FCG0_DCU7                                  (0x40000000UL)
#define PWC_FCG0_DCU8_POS                              (31U)
#define PWC_FCG0_DCU8                                  (0x80000000UL)

/*  Bit definition for PWC_FCG1 register  */
#define PWC_FCG1_CAN1_POS                              (0U)
#define PWC_FCG1_CAN1                                  (0x00000001UL)
#define PWC_FCG1_CAN2_POS                              (1U)
#define PWC_FCG1_CAN2                                  (0x00000002UL)
#define PWC_FCG1_ETHMAC_POS                            (2U)
#define PWC_FCG1_ETHMAC                                (0x00000004UL)
#define PWC_FCG1_QSPI_POS                              (3U)
#define PWC_FCG1_QSPI                                  (0x00000008UL)
#define PWC_FCG1_I2C1_POS                              (4U)
#define PWC_FCG1_I2C1                                  (0x00000010UL)
#define PWC_FCG1_I2C2_POS                              (5U)
#define PWC_FCG1_I2C2                                  (0x00000020UL)
#define PWC_FCG1_I2C3_POS                              (6U)
#define PWC_FCG1_I2C3                                  (0x00000040UL)
#define PWC_FCG1_I2C4_POS                              (7U)
#define PWC_FCG1_I2C4                                  (0x00000080UL)
#define PWC_FCG1_I2C5_POS                              (8U)
#define PWC_FCG1_I2C5                                  (0x00000100UL)
#define PWC_FCG1_I2C6_POS                              (9U)
#define PWC_FCG1_I2C6                                  (0x00000200UL)
#define PWC_FCG1_SDIOC1_POS                            (10U)
#define PWC_FCG1_SDIOC1                                (0x00000400UL)
#define PWC_FCG1_SDIOC2_POS                            (11U)
#define PWC_FCG1_SDIOC2                                (0x00000800UL)
#define PWC_FCG1_I2S1_POS                              (12U)
#define PWC_FCG1_I2S1                                  (0x00001000UL)
#define PWC_FCG1_I2S2_POS                              (13U)
#define PWC_FCG1_I2S2                                  (0x00002000UL)
#define PWC_FCG1_I2S3_POS                              (14U)
#define PWC_FCG1_I2S3                                  (0x00004000UL)
#define PWC_FCG1_I2S4_POS                              (15U)
#define PWC_FCG1_I2S4                                  (0x00008000UL)
#define PWC_FCG1_SPI1_POS                              (16U)
#define PWC_FCG1_SPI1                                  (0x00010000UL)
#define PWC_FCG1_SPI2_POS                              (17U)
#define PWC_FCG1_SPI2                                  (0x00020000UL)
#define PWC_FCG1_SPI3_POS                              (18U)
#define PWC_FCG1_SPI3                                  (0x00040000UL)
#define PWC_FCG1_SPI4_POS                              (19U)
#define PWC_FCG1_SPI4                                  (0x00080000UL)
#define PWC_FCG1_SPI5_POS                              (20U)
#define PWC_FCG1_SPI5                                  (0x00100000UL)
#define PWC_FCG1_SPI6_POS                              (21U)
#define PWC_FCG1_SPI6                                  (0x00200000UL)
#define PWC_FCG1_USBFS_POS                             (22U)
#define PWC_FCG1_USBFS                                 (0x00400000UL)
#define PWC_FCG1_USBHS_POS                             (23U)
#define PWC_FCG1_USBHS                                 (0x00800000UL)
#define PWC_FCG1_FMAC1_POS                             (24U)
#define PWC_FCG1_FMAC1                                 (0x01000000UL)
#define PWC_FCG1_FMAC2_POS                             (25U)
#define PWC_FCG1_FMAC2                                 (0x02000000UL)
#define PWC_FCG1_FMAC3_POS                             (26U)
#define PWC_FCG1_FMAC3                                 (0x04000000UL)
#define PWC_FCG1_FMAC4_POS                             (27U)
#define PWC_FCG1_FMAC4                                 (0x08000000UL)

/*  Bit definition for PWC_FCG2 register  */
#define PWC_FCG2_TMR6_1_POS                            (0U)
#define PWC_FCG2_TMR6_1                                (0x00000001UL)
#define PWC_FCG2_TMR6_2_POS                            (1U)
#define PWC_FCG2_TMR6_2                                (0x00000002UL)
#define PWC_FCG2_TMR6_3_POS                            (2U)
#define PWC_FCG2_TMR6_3                                (0x00000004UL)
#define PWC_FCG2_TMR6_4_POS                            (3U)
#define PWC_FCG2_TMR6_4                                (0x00000008UL)
#define PWC_FCG2_TMR6_5_POS                            (4U)
#define PWC_FCG2_TMR6_5                                (0x00000010UL)
#define PWC_FCG2_TMR6_6_POS                            (5U)
#define PWC_FCG2_TMR6_6                                (0x00000020UL)
#define PWC_FCG2_TMR6_7_POS                            (6U)
#define PWC_FCG2_TMR6_7                                (0x00000040UL)
#define PWC_FCG2_TMR6_8_POS                            (7U)
#define PWC_FCG2_TMR6_8                                (0x00000080UL)
#define PWC_FCG2_TMR4_1_POS                            (8U)
#define PWC_FCG2_TMR4_1                                (0x00000100UL)
#define PWC_FCG2_TMR4_2_POS                            (9U)
#define PWC_FCG2_TMR4_2                                (0x00000200UL)
#define PWC_FCG2_TMR4_3_POS                            (10U)
#define PWC_FCG2_TMR4_3                                (0x00000400UL)
#define PWC_FCG2_HRPWM_POS                             (11U)
#define PWC_FCG2_HRPWM                                 (0x00000800UL)
#define PWC_FCG2_TMR0_1_POS                            (12U)
#define PWC_FCG2_TMR0_1                                (0x00001000UL)
#define PWC_FCG2_TMR0_2_POS                            (13U)
#define PWC_FCG2_TMR0_2                                (0x00002000UL)
#define PWC_FCG2_EMB_POS                               (15U)
#define PWC_FCG2_EMB                                   (0x00008000UL)
#define PWC_FCG2_TMR2_1_POS                            (16U)
#define PWC_FCG2_TMR2_1                                (0x00010000UL)
#define PWC_FCG2_TMR2_2_POS                            (17U)
#define PWC_FCG2_TMR2_2                                (0x00020000UL)
#define PWC_FCG2_TMR2_3_POS                            (18U)
#define PWC_FCG2_TMR2_3                                (0x00040000UL)
#define PWC_FCG2_TMR2_4_POS                            (19U)
#define PWC_FCG2_TMR2_4                                (0x00080000UL)
#define PWC_FCG2_TMRA_1_POS                            (20U)
#define PWC_FCG2_TMRA_1                                (0x00100000UL)
#define PWC_FCG2_TMRA_2_POS                            (21U)
#define PWC_FCG2_TMRA_2                                (0x00200000UL)
#define PWC_FCG2_TMRA_3_POS                            (22U)
#define PWC_FCG2_TMRA_3                                (0x00400000UL)
#define PWC_FCG2_TMRA_4_POS                            (23U)
#define PWC_FCG2_TMRA_4                                (0x00800000UL)
#define PWC_FCG2_TMRA_5_POS                            (24U)
#define PWC_FCG2_TMRA_5                                (0x01000000UL)
#define PWC_FCG2_TMRA_6_POS                            (25U)
#define PWC_FCG2_TMRA_6                                (0x02000000UL)
#define PWC_FCG2_TMRA_7_POS                            (26U)
#define PWC_FCG2_TMRA_7                                (0x04000000UL)
#define PWC_FCG2_TMRA_8_POS                            (27U)
#define PWC_FCG2_TMRA_8                                (0x08000000UL)
#define PWC_FCG2_TMRA_9_POS                            (28U)
#define PWC_FCG2_TMRA_9                                (0x10000000UL)
#define PWC_FCG2_TMRA_10_POS                           (29U)
#define PWC_FCG2_TMRA_10                               (0x20000000UL)
#define PWC_FCG2_TMRA_11_POS                           (30U)
#define PWC_FCG2_TMRA_11                               (0x40000000UL)
#define PWC_FCG2_TMRA_12_POS                           (31U)
#define PWC_FCG2_TMRA_12                               (0x80000000UL)

/*  Bit definition for PWC_FCG3 register  */
#define PWC_FCG3_ADC1_POS                              (0U)
#define PWC_FCG3_ADC1                                  (0x00000001UL)
#define PWC_FCG3_ADC2_POS                              (1U)
#define PWC_FCG3_ADC2                                  (0x00000002UL)
#define PWC_FCG3_ADC3_POS                              (2U)
#define PWC_FCG3_ADC3                                  (0x00000004UL)
#define PWC_FCG3_CMBIAS_POS                            (3U)
#define PWC_FCG3_CMBIAS                                (0x00000008UL)
#define PWC_FCG3_DAC1_POS                              (4U)
#define PWC_FCG3_DAC1                                  (0x00000010UL)
#define PWC_FCG3_DAC2_POS                              (5U)
#define PWC_FCG3_DAC2                                  (0x00000020UL)
#define PWC_FCG3_CMP12_POS                             (8U)
#define PWC_FCG3_CMP12                                 (0x00000100UL)
#define PWC_FCG3_CMP34_POS                             (9U)
#define PWC_FCG3_CMP34                                 (0x00000200UL)
#define PWC_FCG3_OTS_POS                               (12U)
#define PWC_FCG3_OTS                                   (0x00001000UL)
#define PWC_FCG3_DVP_POS                               (15U)
#define PWC_FCG3_DVP                                   (0x00008000UL)
#define PWC_FCG3_SMC_POS                               (16U)
#define PWC_FCG3_SMC                                   (0x00010000UL)
#define PWC_FCG3_DMC_POS                               (17U)
#define PWC_FCG3_DMC                                   (0x00020000UL)
#define PWC_FCG3_NFC_POS                               (18U)
#define PWC_FCG3_NFC                                   (0x00040000UL)
#define PWC_FCG3_USART1_POS                            (20U)
#define PWC_FCG3_USART1                                (0x00100000UL)
#define PWC_FCG3_USART2_POS                            (21U)
#define PWC_FCG3_USART2                                (0x00200000UL)
#define PWC_FCG3_USART3_POS                            (22U)
#define PWC_FCG3_USART3                                (0x00400000UL)
#define PWC_FCG3_USART4_POS                            (23U)
#define PWC_FCG3_USART4                                (0x00800000UL)
#define PWC_FCG3_USART5_POS                            (24U)
#define PWC_FCG3_USART5                                (0x01000000UL)
#define PWC_FCG3_USART6_POS                            (25U)
#define PWC_FCG3_USART6                                (0x02000000UL)
#define PWC_FCG3_USART7_POS                            (26U)
#define PWC_FCG3_USART7                                (0x04000000UL)
#define PWC_FCG3_USART8_POS                            (27U)
#define PWC_FCG3_USART8                                (0x08000000UL)
#define PWC_FCG3_USART9_POS                            (28U)
#define PWC_FCG3_USART9                                (0x10000000UL)
#define PWC_FCG3_USART10_POS                           (29U)
#define PWC_FCG3_USART10                               (0x20000000UL)

/*  Bit definition for PWC_FCG0PC register  */
#define PWC_FCG0PC_PRT0_POS                            (0U)
#define PWC_FCG0PC_PRT0                                (0x00000001UL)
#define PWC_FCG0PC_FCG0PCWE_POS                        (16U)
#define PWC_FCG0PC_FCG0PCWE                            (0xFFFF0000UL)

/*  Bit definition for PWC_VBATRSTR register  */
#define PWC_VBATRSTR                                   (0xFFU)

/*  Bit definition for PWC_VBATCR register  */
#define PWC_VBATCR_VBTRSD_POS                          (0U)
#define PWC_VBATCR_VBTRSD                              (0x01U)
#define PWC_VBATCR_RAMVALID_POS                        (1U)
#define PWC_VBATCR_RAMVALID                            (0x02U)
#define PWC_VBATCR_RAMPDF_POS                          (2U)
#define PWC_VBATCR_RAMPDF                              (0x04U)
#define PWC_VBATCR_VBATDIVMONE_POS                     (3U)
#define PWC_VBATCR_VBATDIVMONE                         (0x08U)
#define PWC_VBATCR_CSDIS_POS                           (7U)
#define PWC_VBATCR_CSDIS                               (0x80U)

/*  Bit definition for PWC_WKTC0 register  */
#define PWC_WKTC0_WKTMCMP                              (0xFFU)

/*  Bit definition for PWC_WKTC1 register  */
#define PWC_WKTC1_WKTMCMP                              (0x0FU)

/*  Bit definition for PWC_WKTC2 register  */
#define PWC_WKTC2_WKOVF_POS                            (4U)
#define PWC_WKTC2_WKOVF                                (0x10U)
#define PWC_WKTC2_WKCKS_POS                            (5U)
#define PWC_WKTC2_WKCKS                                (0x60U)
#define PWC_WKTC2_WKCKS_0                              (0x20U)
#define PWC_WKTC2_WKCKS_1                              (0x40U)
#define PWC_WKTC2_WKTCE_POS                            (7U)
#define PWC_WKTC2_WKTCE                                (0x80U)

/*  Bit definition for PWC_BKR0 register  */
#define PWC_BKR0                                       (0xFFU)

/*  Bit definition for PWC_BKR1 register  */
#define PWC_BKR1                                       (0xFFU)

/*  Bit definition for PWC_BKR2 register  */
#define PWC_BKR2                                       (0xFFU)

/*  Bit definition for PWC_BKR3 register  */
#define PWC_BKR3                                       (0xFFU)

/*  Bit definition for PWC_BKR4 register  */
#define PWC_BKR4                                       (0xFFU)

/*  Bit definition for PWC_BKR5 register  */
#define PWC_BKR5                                       (0xFFU)

/*  Bit definition for PWC_BKR6 register  */
#define PWC_BKR6                                       (0xFFU)

/*  Bit definition for PWC_BKR7 register  */
#define PWC_BKR7                                       (0xFFU)

/*  Bit definition for PWC_BKR8 register  */
#define PWC_BKR8                                       (0xFFU)

/*  Bit definition for PWC_BKR9 register  */
#define PWC_BKR9                                       (0xFFU)

/*  Bit definition for PWC_BKR10 register  */
#define PWC_BKR10                                      (0xFFU)

/*  Bit definition for PWC_BKR11 register  */
#define PWC_BKR11                                      (0xFFU)

/*  Bit definition for PWC_BKR12 register  */
#define PWC_BKR12                                      (0xFFU)

/*  Bit definition for PWC_BKR13 register  */
#define PWC_BKR13                                      (0xFFU)

/*  Bit definition for PWC_BKR14 register  */
#define PWC_BKR14                                      (0xFFU)

/*  Bit definition for PWC_BKR15 register  */
#define PWC_BKR15                                      (0xFFU)

/*  Bit definition for PWC_BKR16 register  */
#define PWC_BKR16                                      (0xFFU)

/*  Bit definition for PWC_BKR17 register  */
#define PWC_BKR17                                      (0xFFU)

/*  Bit definition for PWC_BKR18 register  */
#define PWC_BKR18                                      (0xFFU)

/*  Bit definition for PWC_BKR19 register  */
#define PWC_BKR19                                      (0xFFU)

/*  Bit definition for PWC_BKR20 register  */
#define PWC_BKR20                                      (0xFFU)

/*  Bit definition for PWC_BKR21 register  */
#define PWC_BKR21                                      (0xFFU)

/*  Bit definition for PWC_BKR22 register  */
#define PWC_BKR22                                      (0xFFU)

/*  Bit definition for PWC_BKR23 register  */
#define PWC_BKR23                                      (0xFFU)

/*  Bit definition for PWC_BKR24 register  */
#define PWC_BKR24                                      (0xFFU)

/*  Bit definition for PWC_BKR25 register  */
#define PWC_BKR25                                      (0xFFU)

/*  Bit definition for PWC_BKR26 register  */
#define PWC_BKR26                                      (0xFFU)

/*  Bit definition for PWC_BKR27 register  */
#define PWC_BKR27                                      (0xFFU)

/*  Bit definition for PWC_BKR28 register  */
#define PWC_BKR28                                      (0xFFU)

/*  Bit definition for PWC_BKR29 register  */
#define PWC_BKR29                                      (0xFFU)

/*  Bit definition for PWC_BKR30 register  */
#define PWC_BKR30                                      (0xFFU)

/*  Bit definition for PWC_BKR31 register  */
#define PWC_BKR31                                      (0xFFU)

/*  Bit definition for PWC_BKR32 register  */
#define PWC_BKR32                                      (0xFFU)

/*  Bit definition for PWC_BKR33 register  */
#define PWC_BKR33                                      (0xFFU)

/*  Bit definition for PWC_BKR34 register  */
#define PWC_BKR34                                      (0xFFU)

/*  Bit definition for PWC_BKR35 register  */
#define PWC_BKR35                                      (0xFFU)

/*  Bit definition for PWC_BKR36 register  */
#define PWC_BKR36                                      (0xFFU)

/*  Bit definition for PWC_BKR37 register  */
#define PWC_BKR37                                      (0xFFU)

/*  Bit definition for PWC_BKR38 register  */
#define PWC_BKR38                                      (0xFFU)

/*  Bit definition for PWC_BKR39 register  */
#define PWC_BKR39                                      (0xFFU)

/*  Bit definition for PWC_BKR40 register  */
#define PWC_BKR40                                      (0xFFU)

/*  Bit definition for PWC_BKR41 register  */
#define PWC_BKR41                                      (0xFFU)

/*  Bit definition for PWC_BKR42 register  */
#define PWC_BKR42                                      (0xFFU)

/*  Bit definition for PWC_BKR43 register  */
#define PWC_BKR43                                      (0xFFU)

/*  Bit definition for PWC_BKR44 register  */
#define PWC_BKR44                                      (0xFFU)

/*  Bit definition for PWC_BKR45 register  */
#define PWC_BKR45                                      (0xFFU)

/*  Bit definition for PWC_BKR46 register  */
#define PWC_BKR46                                      (0xFFU)

/*  Bit definition for PWC_BKR47 register  */
#define PWC_BKR47                                      (0xFFU)

/*  Bit definition for PWC_BKR48 register  */
#define PWC_BKR48                                      (0xFFU)

/*  Bit definition for PWC_BKR49 register  */
#define PWC_BKR49                                      (0xFFU)

/*  Bit definition for PWC_BKR50 register  */
#define PWC_BKR50                                      (0xFFU)

/*  Bit definition for PWC_BKR51 register  */
#define PWC_BKR51                                      (0xFFU)

/*  Bit definition for PWC_BKR52 register  */
#define PWC_BKR52                                      (0xFFU)

/*  Bit definition for PWC_BKR53 register  */
#define PWC_BKR53                                      (0xFFU)

/*  Bit definition for PWC_BKR54 register  */
#define PWC_BKR54                                      (0xFFU)

/*  Bit definition for PWC_BKR55 register  */
#define PWC_BKR55                                      (0xFFU)

/*  Bit definition for PWC_BKR56 register  */
#define PWC_BKR56                                      (0xFFU)

/*  Bit definition for PWC_BKR57 register  */
#define PWC_BKR57                                      (0xFFU)

/*  Bit definition for PWC_BKR58 register  */
#define PWC_BKR58                                      (0xFFU)

/*  Bit definition for PWC_BKR59 register  */
#define PWC_BKR59                                      (0xFFU)

/*  Bit definition for PWC_BKR60 register  */
#define PWC_BKR60                                      (0xFFU)

/*  Bit definition for PWC_BKR61 register  */
#define PWC_BKR61                                      (0xFFU)

/*  Bit definition for PWC_BKR62 register  */
#define PWC_BKR62                                      (0xFFU)

/*  Bit definition for PWC_BKR63 register  */
#define PWC_BKR63                                      (0xFFU)

/*  Bit definition for PWC_BKR64 register  */
#define PWC_BKR64                                      (0xFFU)

/*  Bit definition for PWC_BKR65 register  */
#define PWC_BKR65                                      (0xFFU)

/*  Bit definition for PWC_BKR66 register  */
#define PWC_BKR66                                      (0xFFU)

/*  Bit definition for PWC_BKR67 register  */
#define PWC_BKR67                                      (0xFFU)

/*  Bit definition for PWC_BKR68 register  */
#define PWC_BKR68                                      (0xFFU)

/*  Bit definition for PWC_BKR69 register  */
#define PWC_BKR69                                      (0xFFU)

/*  Bit definition for PWC_BKR70 register  */
#define PWC_BKR70                                      (0xFFU)

/*  Bit definition for PWC_BKR71 register  */
#define PWC_BKR71                                      (0xFFU)

/*  Bit definition for PWC_BKR72 register  */
#define PWC_BKR72                                      (0xFFU)

/*  Bit definition for PWC_BKR73 register  */
#define PWC_BKR73                                      (0xFFU)

/*  Bit definition for PWC_BKR74 register  */
#define PWC_BKR74                                      (0xFFU)

/*  Bit definition for PWC_BKR75 register  */
#define PWC_BKR75                                      (0xFFU)

/*  Bit definition for PWC_BKR76 register  */
#define PWC_BKR76                                      (0xFFU)

/*  Bit definition for PWC_BKR77 register  */
#define PWC_BKR77                                      (0xFFU)

/*  Bit definition for PWC_BKR78 register  */
#define PWC_BKR78                                      (0xFFU)

/*  Bit definition for PWC_BKR79 register  */
#define PWC_BKR79                                      (0xFFU)

/*  Bit definition for PWC_BKR80 register  */
#define PWC_BKR80                                      (0xFFU)

/*  Bit definition for PWC_BKR81 register  */
#define PWC_BKR81                                      (0xFFU)

/*  Bit definition for PWC_BKR82 register  */
#define PWC_BKR82                                      (0xFFU)

/*  Bit definition for PWC_BKR83 register  */
#define PWC_BKR83                                      (0xFFU)

/*  Bit definition for PWC_BKR84 register  */
#define PWC_BKR84                                      (0xFFU)

/*  Bit definition for PWC_BKR85 register  */
#define PWC_BKR85                                      (0xFFU)

/*  Bit definition for PWC_BKR86 register  */
#define PWC_BKR86                                      (0xFFU)

/*  Bit definition for PWC_BKR87 register  */
#define PWC_BKR87                                      (0xFFU)

/*  Bit definition for PWC_BKR88 register  */
#define PWC_BKR88                                      (0xFFU)

/*  Bit definition for PWC_BKR89 register  */
#define PWC_BKR89                                      (0xFFU)

/*  Bit definition for PWC_BKR90 register  */
#define PWC_BKR90                                      (0xFFU)

/*  Bit definition for PWC_BKR91 register  */
#define PWC_BKR91                                      (0xFFU)

/*  Bit definition for PWC_BKR92 register  */
#define PWC_BKR92                                      (0xFFU)

/*  Bit definition for PWC_BKR93 register  */
#define PWC_BKR93                                      (0xFFU)

/*  Bit definition for PWC_BKR94 register  */
#define PWC_BKR94                                      (0xFFU)

/*  Bit definition for PWC_BKR95 register  */
#define PWC_BKR95                                      (0xFFU)

/*  Bit definition for PWC_BKR96 register  */
#define PWC_BKR96                                      (0xFFU)

/*  Bit definition for PWC_BKR97 register  */
#define PWC_BKR97                                      (0xFFU)

/*  Bit definition for PWC_BKR98 register  */
#define PWC_BKR98                                      (0xFFU)

/*  Bit definition for PWC_BKR99 register  */
#define PWC_BKR99                                      (0xFFU)

/*  Bit definition for PWC_BKR100 register  */
#define PWC_BKR100                                     (0xFFU)

/*  Bit definition for PWC_BKR101 register  */
#define PWC_BKR101                                     (0xFFU)

/*  Bit definition for PWC_BKR102 register  */
#define PWC_BKR102                                     (0xFFU)

/*  Bit definition for PWC_BKR103 register  */
#define PWC_BKR103                                     (0xFFU)

/*  Bit definition for PWC_BKR104 register  */
#define PWC_BKR104                                     (0xFFU)

/*  Bit definition for PWC_BKR105 register  */
#define PWC_BKR105                                     (0xFFU)

/*  Bit definition for PWC_BKR106 register  */
#define PWC_BKR106                                     (0xFFU)

/*  Bit definition for PWC_BKR107 register  */
#define PWC_BKR107                                     (0xFFU)

/*  Bit definition for PWC_BKR108 register  */
#define PWC_BKR108                                     (0xFFU)

/*  Bit definition for PWC_BKR109 register  */
#define PWC_BKR109                                     (0xFFU)

/*  Bit definition for PWC_BKR110 register  */
#define PWC_BKR110                                     (0xFFU)

/*  Bit definition for PWC_BKR111 register  */
#define PWC_BKR111                                     (0xFFU)

/*  Bit definition for PWC_BKR112 register  */
#define PWC_BKR112                                     (0xFFU)

/*  Bit definition for PWC_BKR113 register  */
#define PWC_BKR113                                     (0xFFU)

/*  Bit definition for PWC_BKR114 register  */
#define PWC_BKR114                                     (0xFFU)

/*  Bit definition for PWC_BKR115 register  */
#define PWC_BKR115                                     (0xFFU)

/*  Bit definition for PWC_BKR116 register  */
#define PWC_BKR116                                     (0xFFU)

/*  Bit definition for PWC_BKR117 register  */
#define PWC_BKR117                                     (0xFFU)

/*  Bit definition for PWC_BKR118 register  */
#define PWC_BKR118                                     (0xFFU)

/*  Bit definition for PWC_BKR119 register  */
#define PWC_BKR119                                     (0xFFU)

/*  Bit definition for PWC_BKR120 register  */
#define PWC_BKR120                                     (0xFFU)

/*  Bit definition for PWC_BKR121 register  */
#define PWC_BKR121                                     (0xFFU)

/*  Bit definition for PWC_BKR122 register  */
#define PWC_BKR122                                     (0xFFU)

/*  Bit definition for PWC_BKR123 register  */
#define PWC_BKR123                                     (0xFFU)

/*  Bit definition for PWC_BKR124 register  */
#define PWC_BKR124                                     (0xFFU)

/*  Bit definition for PWC_BKR125 register  */
#define PWC_BKR125                                     (0xFFU)

/*  Bit definition for PWC_BKR126 register  */
#define PWC_BKR126                                     (0xFFU)

/*  Bit definition for PWC_BKR127 register  */
#define PWC_BKR127                                     (0xFFU)

/*  Bit definition for PWC_PWRC0 register  */
#define PWC_PWRC0_PDMDS_POS                            (0U)
#define PWC_PWRC0_PDMDS                                (0x03U)
#define PWC_PWRC0_PDMDS_0                              (0x01U)
#define PWC_PWRC0_PDMDS_1                              (0x02U)
#define PWC_PWRC0_IORTN_POS                            (4U)
#define PWC_PWRC0_IORTN                                (0x30U)
#define PWC_PWRC0_IORTN_0                              (0x10U)
#define PWC_PWRC0_IORTN_1                              (0x20U)
#define PWC_PWRC0_PWDN_POS                             (7U)
#define PWC_PWRC0_PWDN                                 (0x80U)

/*  Bit definition for PWC_PWRC1 register  */
#define PWC_PWRC1_VPLLSD_POS                           (0U)
#define PWC_PWRC1_VPLLSD                               (0x03U)
#define PWC_PWRC1_VPLLSD_0                             (0x01U)
#define PWC_PWRC1_VPLLSD_1                             (0x02U)
#define PWC_PWRC1_VHRCSD_POS                           (2U)
#define PWC_PWRC1_VHRCSD                               (0x04U)
#define PWC_PWRC1_PDTS_POS                             (3U)
#define PWC_PWRC1_PDTS                                 (0x08U)
#define PWC_PWRC1_STPDAS_POS                           (6U)
#define PWC_PWRC1_STPDAS                               (0xC0U)
#define PWC_PWRC1_STPDAS_0                             (0x40U)
#define PWC_PWRC1_STPDAS_1                             (0x80U)

/*  Bit definition for PWC_PWRC2 register  */
#define PWC_PWRC2_DDAS_POS                             (0U)
#define PWC_PWRC2_DDAS                                 (0x0FU)
#define PWC_PWRC2_DVS_POS                              (4U)
#define PWC_PWRC2_DVS                                  (0x30U)
#define PWC_PWRC2_DVS_0                                (0x10U)
#define PWC_PWRC2_DVS_1                                (0x20U)

/*  Bit definition for PWC_PWRC3 register  */
#define PWC_PWRC3_DDAS                                 (0xFFU)

/*  Bit definition for PWC_PWRC4 register  */
#define PWC_PWRC4_VBATREFSEL_POS                       (0U)
#define PWC_PWRC4_VBATREFSEL                           (0x01U)
#define PWC_PWRC4_VBATME_POS                           (1U)
#define PWC_PWRC4_VBATME                               (0x02U)
#define PWC_PWRC4_VBATMON_POS                          (4U)
#define PWC_PWRC4_VBATMON                              (0x10U)
#define PWC_PWRC4_ADBUFS_POS                           (6U)
#define PWC_PWRC4_ADBUFS                               (0x40U)
#define PWC_PWRC4_ADBUFE_POS                           (7U)
#define PWC_PWRC4_ADBUFE                               (0x80U)

/*  Bit definition for PWC_PVDCR0 register  */
#define PWC_PVDCR0_EXVCCINEN_POS                       (0U)
#define PWC_PVDCR0_EXVCCINEN                           (0x01U)
#define PWC_PVDCR0_PVD1EN_POS                          (5U)
#define PWC_PVDCR0_PVD1EN                              (0x20U)
#define PWC_PVDCR0_PVD2EN_POS                          (6U)
#define PWC_PVDCR0_PVD2EN                              (0x40U)

/*  Bit definition for PWC_PVDCR1 register  */
#define PWC_PVDCR1_PVD1IRE_POS                         (0U)
#define PWC_PVDCR1_PVD1IRE                             (0x01U)
#define PWC_PVDCR1_PVD1IRS_POS                         (1U)
#define PWC_PVDCR1_PVD1IRS                             (0x02U)
#define PWC_PVDCR1_PVD1CMPOE_POS                       (2U)
#define PWC_PVDCR1_PVD1CMPOE                           (0x04U)
#define PWC_PVDCR1_PVD2IRE_POS                         (4U)
#define PWC_PVDCR1_PVD2IRE                             (0x10U)
#define PWC_PVDCR1_PVD2IRS_POS                         (5U)
#define PWC_PVDCR1_PVD2IRS                             (0x20U)
#define PWC_PVDCR1_PVD2CMPOE_POS                       (6U)
#define PWC_PVDCR1_PVD2CMPOE                           (0x40U)

/*  Bit definition for PWC_PVDFCR register  */
#define PWC_PVDFCR_PVD1NFDIS_POS                       (0U)
#define PWC_PVDFCR_PVD1NFDIS                           (0x01U)
#define PWC_PVDFCR_PVD1NFCKS_POS                       (1U)
#define PWC_PVDFCR_PVD1NFCKS                           (0x06U)
#define PWC_PVDFCR_PVD1NFCKS_0                         (0x02U)
#define PWC_PVDFCR_PVD1NFCKS_1                         (0x04U)
#define PWC_PVDFCR_PVD2NFDIS_POS                       (4U)
#define PWC_PVDFCR_PVD2NFDIS                           (0x10U)
#define PWC_PVDFCR_PVD2NFCKS_POS                       (5U)
#define PWC_PVDFCR_PVD2NFCKS                           (0x60U)
#define PWC_PVDFCR_PVD2NFCKS_0                         (0x20U)
#define PWC_PVDFCR_PVD2NFCKS_1                         (0x40U)

/*  Bit definition for PWC_PVDLCR register  */
#define PWC_PVDLCR_PVD1LVL_POS                         (0U)
#define PWC_PVDLCR_PVD1LVL                             (0x07U)
#define PWC_PVDLCR_PVD2LVL_POS                         (4U)
#define PWC_PVDLCR_PVD2LVL                             (0x70U)

/*  Bit definition for PWC_PDWKE0 register  */
#define PWC_PDWKE0_WKE00_POS                           (0U)
#define PWC_PDWKE0_WKE00                               (0x01U)
#define PWC_PDWKE0_WKE01_POS                           (1U)
#define PWC_PDWKE0_WKE01                               (0x02U)
#define PWC_PDWKE0_WKE02_POS                           (2U)
#define PWC_PDWKE0_WKE02                               (0x04U)
#define PWC_PDWKE0_WKE03_POS                           (3U)
#define PWC_PDWKE0_WKE03                               (0x08U)
#define PWC_PDWKE0_WKE10_POS                           (4U)
#define PWC_PDWKE0_WKE10                               (0x10U)
#define PWC_PDWKE0_WKE11_POS                           (5U)
#define PWC_PDWKE0_WKE11                               (0x20U)
#define PWC_PDWKE0_WKE12_POS                           (6U)
#define PWC_PDWKE0_WKE12                               (0x40U)
#define PWC_PDWKE0_WKE13_POS                           (7U)
#define PWC_PDWKE0_WKE13                               (0x80U)

/*  Bit definition for PWC_PDWKE1 register  */
#define PWC_PDWKE1_WKE20_POS                           (0U)
#define PWC_PDWKE1_WKE20                               (0x01U)
#define PWC_PDWKE1_WKE21_POS                           (1U)
#define PWC_PDWKE1_WKE21                               (0x02U)
#define PWC_PDWKE1_WKE22_POS                           (2U)
#define PWC_PDWKE1_WKE22                               (0x04U)
#define PWC_PDWKE1_WKE23_POS                           (3U)
#define PWC_PDWKE1_WKE23                               (0x08U)
#define PWC_PDWKE1_WKE30_POS                           (4U)
#define PWC_PDWKE1_WKE30                               (0x10U)
#define PWC_PDWKE1_WKE31_POS                           (5U)
#define PWC_PDWKE1_WKE31                               (0x20U)
#define PWC_PDWKE1_WKE32_POS                           (6U)
#define PWC_PDWKE1_WKE32                               (0x40U)
#define PWC_PDWKE1_WKE33_POS                           (7U)
#define PWC_PDWKE1_WKE33                               (0x80U)

/*  Bit definition for PWC_PDWKE2 register  */
#define PWC_PDWKE2_VD1WKE_POS                          (0U)
#define PWC_PDWKE2_VD1WKE                              (0x01U)
#define PWC_PDWKE2_VD2WKE_POS                          (1U)
#define PWC_PDWKE2_VD2WKE                              (0x02U)
#define PWC_PDWKE2_RTCPRDWKE_POS                       (4U)
#define PWC_PDWKE2_RTCPRDWKE                           (0x10U)
#define PWC_PDWKE2_RTCALMWKE_POS                       (5U)
#define PWC_PDWKE2_RTCALMWKE                           (0x20U)
#define PWC_PDWKE2_WKTMWKE_POS                         (7U)
#define PWC_PDWKE2_WKTMWKE                             (0x80U)

/*  Bit definition for PWC_PDWKES register  */
#define PWC_PDWKES_WK0EGS_POS                          (0U)
#define PWC_PDWKES_WK0EGS                              (0x01U)
#define PWC_PDWKES_WK1EGS_POS                          (1U)
#define PWC_PDWKES_WK1EGS                              (0x02U)
#define PWC_PDWKES_WK2EGS_POS                          (2U)
#define PWC_PDWKES_WK2EGS                              (0x04U)
#define PWC_PDWKES_WK3EGS_POS                          (3U)
#define PWC_PDWKES_WK3EGS                              (0x08U)
#define PWC_PDWKES_VD1EGS_POS                          (4U)
#define PWC_PDWKES_VD1EGS                              (0x10U)
#define PWC_PDWKES_VD2EGS_POS                          (5U)
#define PWC_PDWKES_VD2EGS                              (0x20U)

/*  Bit definition for PWC_PDWKF0 register  */
#define PWC_PDWKF0_PTWK0F_POS                          (0U)
#define PWC_PDWKF0_PTWK0F                              (0x01U)
#define PWC_PDWKF0_PTWK1F_POS                          (1U)
#define PWC_PDWKF0_PTWK1F                              (0x02U)
#define PWC_PDWKF0_PTWK2F_POS                          (2U)
#define PWC_PDWKF0_PTWK2F                              (0x04U)
#define PWC_PDWKF0_PTWK3F_POS                          (3U)
#define PWC_PDWKF0_PTWK3F                              (0x08U)
#define PWC_PDWKF0_VD1WKF_POS                          (4U)
#define PWC_PDWKF0_VD1WKF                              (0x10U)
#define PWC_PDWKF0_VD2WKF_POS                          (5U)
#define PWC_PDWKF0_VD2WKF                              (0x20U)

/*  Bit definition for PWC_PDWKF1 register  */
#define PWC_PDWKF1_RXD0WKF_POS                         (3U)
#define PWC_PDWKF1_RXD0WKF                             (0x08U)
#define PWC_PDWKF1_RTCPRDWKF_POS                       (4U)
#define PWC_PDWKF1_RTCPRDWKF                           (0x10U)
#define PWC_PDWKF1_RTCALMWKF_POS                       (5U)
#define PWC_PDWKF1_RTCALMWKF                           (0x20U)
#define PWC_PDWKF1_WKTMWKF_POS                         (7U)
#define PWC_PDWKF1_WKTMWKF                             (0x80U)

/*  Bit definition for PWC_RAMPC0 register  */
#define PWC_RAMPC0_RAMPDC0_POS                         (0U)
#define PWC_RAMPC0_RAMPDC0                             (0x00000001UL)
#define PWC_RAMPC0_RAMPDC1_POS                         (1U)
#define PWC_RAMPC0_RAMPDC1                             (0x00000002UL)
#define PWC_RAMPC0_RAMPDC2_POS                         (2U)
#define PWC_RAMPC0_RAMPDC2                             (0x00000004UL)
#define PWC_RAMPC0_RAMPDC3_POS                         (3U)
#define PWC_RAMPC0_RAMPDC3                             (0x00000008UL)
#define PWC_RAMPC0_RAMPDC4_POS                         (4U)
#define PWC_RAMPC0_RAMPDC4                             (0x00000010UL)
#define PWC_RAMPC0_RAMPDC5_POS                         (5U)
#define PWC_RAMPC0_RAMPDC5                             (0x00000020UL)
#define PWC_RAMPC0_RAMPDC6_POS                         (6U)
#define PWC_RAMPC0_RAMPDC6                             (0x00000040UL)
#define PWC_RAMPC0_RAMPDC7_POS                         (7U)
#define PWC_RAMPC0_RAMPDC7                             (0x00000080UL)
#define PWC_RAMPC0_RAMPDC8_POS                         (8U)
#define PWC_RAMPC0_RAMPDC8                             (0x00000100UL)
#define PWC_RAMPC0_RAMPDC9_POS                         (9U)
#define PWC_RAMPC0_RAMPDC9                             (0x00000200UL)
#define PWC_RAMPC0_RAMPDC10_POS                        (10U)
#define PWC_RAMPC0_RAMPDC10                            (0x00000400UL)

/*  Bit definition for PWC_RAMOPM register  */
#define PWC_RAMOPM                                     (0xFFFFU)

/*  Bit definition for PWC_PRAMLPC register  */
#define PWC_PRAMLPC_PRAMPDC0_POS                       (0U)
#define PWC_PRAMLPC_PRAMPDC0                           (0x00000001UL)
#define PWC_PRAMLPC_PRAMPDC1_POS                       (1U)
#define PWC_PRAMLPC_PRAMPDC1                           (0x00000002UL)
#define PWC_PRAMLPC_PRAMPDC2_POS                       (2U)
#define PWC_PRAMLPC_PRAMPDC2                           (0x00000004UL)
#define PWC_PRAMLPC_PRAMPDC3_POS                       (3U)
#define PWC_PRAMLPC_PRAMPDC3                           (0x00000008UL)
#define PWC_PRAMLPC_PRAMPDC4_POS                       (4U)
#define PWC_PRAMLPC_PRAMPDC4                           (0x00000010UL)
#define PWC_PRAMLPC_PRAMPDC5_POS                       (5U)
#define PWC_PRAMLPC_PRAMPDC5                           (0x00000020UL)
#define PWC_PRAMLPC_PRAMPDC6_POS                       (6U)
#define PWC_PRAMLPC_PRAMPDC6                           (0x00000040UL)
#define PWC_PRAMLPC_PRAMPDC7_POS                       (7U)
#define PWC_PRAMLPC_PRAMPDC7                           (0x00000080UL)
#define PWC_PRAMLPC_PRAMPDC8_POS                       (8U)
#define PWC_PRAMLPC_PRAMPDC8                           (0x00000100UL)
#define PWC_PRAMLPC_PRAMPDC9_POS                       (9U)
#define PWC_PRAMLPC_PRAMPDC9                           (0x00000200UL)

/*  Bit definition for PWC_PVDICR register  */
#define PWC_PVDICR_PVD1NMIS_POS                        (0U)
#define PWC_PVDICR_PVD1NMIS                            (0x01U)
#define PWC_PVDICR_PVD1EDGS_POS                        (1U)
#define PWC_PVDICR_PVD1EDGS                            (0x06U)
#define PWC_PVDICR_PVD1EDGS_0                          (0x02U)
#define PWC_PVDICR_PVD1EDGS_1                          (0x04U)
#define PWC_PVDICR_PVD2NMIS_POS                        (4U)
#define PWC_PVDICR_PVD2NMIS                            (0x10U)
#define PWC_PVDICR_PVD2EDGS_POS                        (5U)
#define PWC_PVDICR_PVD2EDGS                            (0x60U)
#define PWC_PVDICR_PVD2EDGS_0                          (0x20U)
#define PWC_PVDICR_PVD2EDGS_1                          (0x40U)

/*  Bit definition for PWC_PVDDSR register  */
#define PWC_PVDDSR_PVD1MON_POS                         (0U)
#define PWC_PVDDSR_PVD1MON                             (0x01U)
#define PWC_PVDDSR_PVD1DETFLG_POS                      (1U)
#define PWC_PVDDSR_PVD1DETFLG                          (0x02U)
#define PWC_PVDDSR_PVD2MON_POS                         (4U)
#define PWC_PVDDSR_PVD2MON                             (0x10U)
#define PWC_PVDDSR_PVD2DETFLG_POS                      (5U)
#define PWC_PVDDSR_PVD2DETFLG                          (0x20U)

/*  Bit definition for PWC_STPMCR register  */
#define PWC_STPMCR_FLNWT_POS                           (0U)
#define PWC_STPMCR_FLNWT                               (0x0001U)
#define PWC_STPMCR_CKSMRC_POS                          (1U)
#define PWC_STPMCR_CKSMRC                              (0x0002U)
#define PWC_STPMCR_EXBUSOE_POS                         (14U)
#define PWC_STPMCR_EXBUSOE                             (0x4000U)
#define PWC_STPMCR_STOP_POS                            (15U)
#define PWC_STPMCR_STOP                                (0x8000U)

/*  Bit definition for PWC_FPRC register  */
#define PWC_FPRC_FPRCB0_POS                            (0U)
#define PWC_FPRC_FPRCB0                                (0x0001U)
#define PWC_FPRC_FPRCB1_POS                            (1U)
#define PWC_FPRC_FPRCB1                                (0x0002U)
#define PWC_FPRC_FPRCB2_POS                            (2U)
#define PWC_FPRC_FPRCB2                                (0x0004U)
#define PWC_FPRC_FPRCB3_POS                            (3U)
#define PWC_FPRC_FPRCB3                                (0x0008U)
#define PWC_FPRC_FPRCWE_POS                            (8U)
#define PWC_FPRC_FPRCWE                                (0xFF00U)

/*******************************************************************************
                Bit definition for Peripheral QSPI
*******************************************************************************/
/*  Bit definition for QSPI_CR register  */
#define QSPI_CR_MDSEL_POS                              (0U)
#define QSPI_CR_MDSEL                                  (0x00000007UL)
#define QSPI_CR_PFE_POS                                (3U)
#define QSPI_CR_PFE                                    (0x00000008UL)
#define QSPI_CR_PFSAE_POS                              (4U)
#define QSPI_CR_PFSAE                                  (0x00000010UL)
#define QSPI_CR_DCOME_POS                              (5U)
#define QSPI_CR_DCOME                                  (0x00000020UL)
#define QSPI_CR_XIPE_POS                               (6U)
#define QSPI_CR_XIPE                                   (0x00000040UL)
#define QSPI_CR_SPIMD3_POS                             (7U)
#define QSPI_CR_SPIMD3                                 (0x00000080UL)
#define QSPI_CR_IPRSL_POS                              (8U)
#define QSPI_CR_IPRSL                                  (0x00000300UL)
#define QSPI_CR_IPRSL_0                                (0x00000100UL)
#define QSPI_CR_IPRSL_1                                (0x00000200UL)
#define QSPI_CR_APRSL_POS                              (10U)
#define QSPI_CR_APRSL                                  (0x00000C00UL)
#define QSPI_CR_APRSL_0                                (0x00000400UL)
#define QSPI_CR_APRSL_1                                (0x00000800UL)
#define QSPI_CR_DPRSL_POS                              (12U)
#define QSPI_CR_DPRSL                                  (0x00003000UL)
#define QSPI_CR_DPRSL_0                                (0x00001000UL)
#define QSPI_CR_DPRSL_1                                (0x00002000UL)
#define QSPI_CR_DIV_POS                                (16U)
#define QSPI_CR_DIV                                    (0x003F0000UL)

/*  Bit definition for QSPI_CSCR register  */
#define QSPI_CSCR_SSHW_POS                             (0U)
#define QSPI_CSCR_SSHW                                 (0x0000000FUL)
#define QSPI_CSCR_SSNW_POS                             (4U)
#define QSPI_CSCR_SSNW                                 (0x00000030UL)
#define QSPI_CSCR_SSNW_0                               (0x00000010UL)
#define QSPI_CSCR_SSNW_1                               (0x00000020UL)

/*  Bit definition for QSPI_FCR register  */
#define QSPI_FCR_AWSL_POS                              (0U)
#define QSPI_FCR_AWSL                                  (0x00000003UL)
#define QSPI_FCR_AWSL_0                                (0x00000001UL)
#define QSPI_FCR_AWSL_1                                (0x00000002UL)
#define QSPI_FCR_FOUR_BIC_POS                          (2U)
#define QSPI_FCR_FOUR_BIC                              (0x00000004UL)
#define QSPI_FCR_SSNHD_POS                             (4U)
#define QSPI_FCR_SSNHD                                 (0x00000010UL)
#define QSPI_FCR_SSNLD_POS                             (5U)
#define QSPI_FCR_SSNLD                                 (0x00000020UL)
#define QSPI_FCR_WPOL_POS                              (6U)
#define QSPI_FCR_WPOL                                  (0x00000040UL)
#define QSPI_FCR_DMCYCN_POS                            (8U)
#define QSPI_FCR_DMCYCN                                (0x00000F00UL)
#define QSPI_FCR_DUTY_POS                              (15U)
#define QSPI_FCR_DUTY                                  (0x00008000UL)

/*  Bit definition for QSPI_SR register  */
#define QSPI_SR_BUSY_POS                               (0U)
#define QSPI_SR_BUSY                                   (0x00000001UL)
#define QSPI_SR_XIPF_POS                               (6U)
#define QSPI_SR_XIPF                                   (0x00000040UL)
#define QSPI_SR_RAER_POS                               (7U)
#define QSPI_SR_RAER                                   (0x00000080UL)
#define QSPI_SR_PFNUM_POS                              (8U)
#define QSPI_SR_PFNUM                                  (0x00001F00UL)
#define QSPI_SR_PFFUL_POS                              (14U)
#define QSPI_SR_PFFUL                                  (0x00004000UL)
#define QSPI_SR_PFAN_POS                               (15U)
#define QSPI_SR_PFAN                                   (0x00008000UL)

/*  Bit definition for QSPI_DCOM register  */
#define QSPI_DCOM_DCOM                                 (0x000000FFUL)

/*  Bit definition for QSPI_CCMD register  */
#define QSPI_CCMD_RIC                                  (0x000000FFUL)

/*  Bit definition for QSPI_XCMD register  */
#define QSPI_XCMD_XIPMC                                (0x000000FFUL)

/*  Bit definition for QSPI_SR2 register  */
#define QSPI_SR2_RAERCLR_POS                           (7U)
#define QSPI_SR2_RAERCLR                               (0x00000080UL)

/*  Bit definition for QSPI_EXAR register  */
#define QSPI_EXAR_EXADR_POS                            (26U)
#define QSPI_EXAR_EXADR                                (0xFC000000UL)

/*******************************************************************************
                Bit definition for Peripheral RMU
*******************************************************************************/
/*  Bit definition for RMU_PRSTCR0 register  */
#define RMU_PRSTCR0_LKUPREN_POS                        (5U)
#define RMU_PRSTCR0_LKUPREN                            (0x20U)

/*  Bit definition for RMU_RSTF0 register  */
#define RMU_RSTF0_PORF_POS                             (0U)
#define RMU_RSTF0_PORF                                 (0x00000001UL)
#define RMU_RSTF0_PINRF_POS                            (1U)
#define RMU_RSTF0_PINRF                                (0x00000002UL)
#define RMU_RSTF0_BORF_POS                             (2U)
#define RMU_RSTF0_BORF                                 (0x00000004UL)
#define RMU_RSTF0_PVD1RF_POS                           (3U)
#define RMU_RSTF0_PVD1RF                               (0x00000008UL)
#define RMU_RSTF0_PVD2RF_POS                           (4U)
#define RMU_RSTF0_PVD2RF                               (0x00000010UL)
#define RMU_RSTF0_WDRF_POS                             (5U)
#define RMU_RSTF0_WDRF                                 (0x00000020UL)
#define RMU_RSTF0_SWDRF_POS                            (6U)
#define RMU_RSTF0_SWDRF                                (0x00000040UL)
#define RMU_RSTF0_PDRF_POS                             (7U)
#define RMU_RSTF0_PDRF                                 (0x00000080UL)
#define RMU_RSTF0_SWRF_POS                             (8U)
#define RMU_RSTF0_SWRF                                 (0x00000100UL)
#define RMU_RSTF0_MPUERF_POS                           (9U)
#define RMU_RSTF0_MPUERF                               (0x00000200UL)
#define RMU_RSTF0_RAPERF_POS                           (10U)
#define RMU_RSTF0_RAPERF                               (0x00000400UL)
#define RMU_RSTF0_RAECRF_POS                           (11U)
#define RMU_RSTF0_RAECRF                               (0x00000800UL)
#define RMU_RSTF0_CKFERF_POS                           (12U)
#define RMU_RSTF0_CKFERF                               (0x00001000UL)
#define RMU_RSTF0_XTALERF_POS                          (13U)
#define RMU_RSTF0_XTALERF                              (0x00002000UL)
#define RMU_RSTF0_LKUPRF_POS                           (14U)
#define RMU_RSTF0_LKUPRF                               (0x00004000UL)
#define RMU_RSTF0_MULTIRF_POS                          (30U)
#define RMU_RSTF0_MULTIRF                              (0x40000000UL)
#define RMU_RSTF0_CLRF_POS                             (31U)
#define RMU_RSTF0_CLRF                                 (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral RTC
*******************************************************************************/
/*  Bit definition for RTC_CR0 register  */
#define RTC_CR0_RESET                                  (0x01U)

/*  Bit definition for RTC_CR1 register  */
#define RTC_CR1_PRDS_POS                               (0U)
#define RTC_CR1_PRDS                                   (0x07U)
#define RTC_CR1_PRDS_0                                 (0x01U)
#define RTC_CR1_PRDS_1                                 (0x02U)
#define RTC_CR1_PRDS_2                                 (0x04U)
#define RTC_CR1_AMPM_POS                               (3U)
#define RTC_CR1_AMPM                                   (0x08U)
#define RTC_CR1_ONEHZOE_POS                            (5U)
#define RTC_CR1_ONEHZOE                                (0x20U)
#define RTC_CR1_ONEHZSEL_POS                           (6U)
#define RTC_CR1_ONEHZSEL                               (0x40U)
#define RTC_CR1_START_POS                              (7U)
#define RTC_CR1_START                                  (0x80U)

/*  Bit definition for RTC_CR2 register  */
#define RTC_CR2_RWREQ_POS                              (0U)
#define RTC_CR2_RWREQ                                  (0x01U)
#define RTC_CR2_RWEN_POS                               (1U)
#define RTC_CR2_RWEN                                   (0x02U)
#define RTC_CR2_PRDF_POS                               (2U)
#define RTC_CR2_PRDF                                   (0x04U)
#define RTC_CR2_ALMF_POS                               (3U)
#define RTC_CR2_ALMF                                   (0x08U)
#define RTC_CR2_PRDIE_POS                              (5U)
#define RTC_CR2_PRDIE                                  (0x20U)
#define RTC_CR2_ALMIE_POS                              (6U)
#define RTC_CR2_ALMIE                                  (0x40U)
#define RTC_CR2_ALME_POS                               (7U)
#define RTC_CR2_ALME                                   (0x80U)

/*  Bit definition for RTC_CR3 register  */
#define RTC_CR3_LRCEN_POS                              (4U)
#define RTC_CR3_LRCEN                                  (0x10U)
#define RTC_CR3_RCKSEL_POS                             (7U)
#define RTC_CR3_RCKSEL                                 (0x80U)

/*  Bit definition for RTC_SEC register  */
#define RTC_SEC_SECU_POS                               (0U)
#define RTC_SEC_SECU                                   (0x0FU)
#define RTC_SEC_SECD_POS                               (4U)
#define RTC_SEC_SECD                                   (0x70U)

/*  Bit definition for RTC_MIN register  */
#define RTC_MIN_MINU_POS                               (0U)
#define RTC_MIN_MINU                                   (0x0FU)
#define RTC_MIN_MIND_POS                               (4U)
#define RTC_MIN_MIND                                   (0x70U)

/*  Bit definition for RTC_HOUR register  */
#define RTC_HOUR_HOURU_POS                             (0U)
#define RTC_HOUR_HOURU                                 (0x0FU)
#define RTC_HOUR_HOURU_0                               (0x01U)
#define RTC_HOUR_HOURU_1                               (0x02U)
#define RTC_HOUR_HOURU_2                               (0x04U)
#define RTC_HOUR_HOURU_3                               (0x08U)
#define RTC_HOUR_HOURD_POS                             (4U)
#define RTC_HOUR_HOURD                                 (0x30U)
#define RTC_HOUR_HOURD_0                               (0x10U)
#define RTC_HOUR_HOURD_1                               (0x20U)

/*  Bit definition for RTC_WEEK register  */
#define RTC_WEEK_WEEK                                  (0x07U)

/*  Bit definition for RTC_DAY register  */
#define RTC_DAY_DAYU_POS                               (0U)
#define RTC_DAY_DAYU                                   (0x0FU)
#define RTC_DAY_DAYD_POS                               (4U)
#define RTC_DAY_DAYD                                   (0x30U)

/*  Bit definition for RTC_MON register  */
#define RTC_MON_MON                                    (0x1FU)

/*  Bit definition for RTC_YEAR register  */
#define RTC_YEAR_YEARU_POS                             (0U)
#define RTC_YEAR_YEARU                                 (0x0FU)
#define RTC_YEAR_YEARD_POS                             (4U)
#define RTC_YEAR_YEARD                                 (0xF0U)

/*  Bit definition for RTC_ALMMIN register  */
#define RTC_ALMMIN_ALMMINU_POS                         (0U)
#define RTC_ALMMIN_ALMMINU                             (0x0FU)
#define RTC_ALMMIN_ALMMIND_POS                         (4U)
#define RTC_ALMMIN_ALMMIND                             (0x70U)

/*  Bit definition for RTC_ALMHOUR register  */
#define RTC_ALMHOUR_ALMHOURU_POS                       (0U)
#define RTC_ALMHOUR_ALMHOURU                           (0x0FU)
#define RTC_ALMHOUR_ALMHOURU_0                         (0x01U)
#define RTC_ALMHOUR_ALMHOURU_1                         (0x02U)
#define RTC_ALMHOUR_ALMHOURU_2                         (0x04U)
#define RTC_ALMHOUR_ALMHOURU_3                         (0x08U)
#define RTC_ALMHOUR_ALMHOURD_POS                       (4U)
#define RTC_ALMHOUR_ALMHOURD                           (0x30U)
#define RTC_ALMHOUR_ALMHOURD_0                         (0x10U)
#define RTC_ALMHOUR_ALMHOURD_1                         (0x20U)

/*  Bit definition for RTC_ALMWEEK register  */
#define RTC_ALMWEEK_ALMWEEK                            (0x7FU)
#define RTC_ALMWEEK_ALMWEEK_0                          (0x01U)
#define RTC_ALMWEEK_ALMWEEK_1                          (0x02U)
#define RTC_ALMWEEK_ALMWEEK_2                          (0x04U)
#define RTC_ALMWEEK_ALMWEEK_3                          (0x08U)
#define RTC_ALMWEEK_ALMWEEK_4                          (0x10U)
#define RTC_ALMWEEK_ALMWEEK_5                          (0x20U)
#define RTC_ALMWEEK_ALMWEEK_6                          (0x40U)

/*  Bit definition for RTC_ERRCRH register  */
#define RTC_ERRCRH_COMP8_POS                           (0U)
#define RTC_ERRCRH_COMP8                               (0x01U)
#define RTC_ERRCRH_COMPEN_POS                          (7U)
#define RTC_ERRCRH_COMPEN                              (0x80U)

/*  Bit definition for RTC_ERRCRL register  */
#define RTC_ERRCRL_COMP                                (0xFFU)

/*  Bit definition for RTC_TPCR0 register  */
#define RTC_TPCR0_TPCT0_POS                            (0U)
#define RTC_TPCR0_TPCT0                                (0x03U)
#define RTC_TPCR0_TPCT0_0                              (0x01U)
#define RTC_TPCR0_TPCT0_1                              (0x02U)
#define RTC_TPCR0_TPNF0_POS                            (2U)
#define RTC_TPCR0_TPNF0                                (0x0CU)
#define RTC_TPCR0_TPNF0_0                              (0x04U)
#define RTC_TPCR0_TPNF0_1                              (0x08U)
#define RTC_TPCR0_TPRSTE0_POS                          (4U)
#define RTC_TPCR0_TPRSTE0                              (0x10U)
#define RTC_TPCR0_TPIE0_POS                            (5U)
#define RTC_TPCR0_TPIE0                                (0x20U)
#define RTC_TPCR0_TSTPE0_POS                           (6U)
#define RTC_TPCR0_TSTPE0                               (0x40U)
#define RTC_TPCR0_TPEN0_POS                            (7U)
#define RTC_TPCR0_TPEN0                                (0x80U)

/*  Bit definition for RTC_TPCR1 register  */
#define RTC_TPCR1_TPCT1_POS                            (0U)
#define RTC_TPCR1_TPCT1                                (0x03U)
#define RTC_TPCR1_TPCT1_0                              (0x01U)
#define RTC_TPCR1_TPCT1_1                              (0x02U)
#define RTC_TPCR1_TPNF1_POS                            (2U)
#define RTC_TPCR1_TPNF1                                (0x0CU)
#define RTC_TPCR1_TPNF1_0                              (0x04U)
#define RTC_TPCR1_TPNF1_1                              (0x08U)
#define RTC_TPCR1_TPRSTE1_POS                          (4U)
#define RTC_TPCR1_TPRSTE1                              (0x10U)
#define RTC_TPCR1_TPIE1_POS                            (5U)
#define RTC_TPCR1_TPIE1                                (0x20U)
#define RTC_TPCR1_TSTPE1_POS                           (6U)
#define RTC_TPCR1_TSTPE1                               (0x40U)
#define RTC_TPCR1_TPEN1_POS                            (7U)
#define RTC_TPCR1_TPEN1                                (0x80U)

/*  Bit definition for RTC_TPSR register  */
#define RTC_TPSR_TPF0_POS                              (0U)
#define RTC_TPSR_TPF0                                  (0x01U)
#define RTC_TPSR_TPF1_POS                              (1U)
#define RTC_TPSR_TPF1                                  (0x02U)
#define RTC_TPSR_TPOVF_POS                             (2U)
#define RTC_TPSR_TPOVF                                 (0x04U)

/*  Bit definition for RTC_SECTP register  */
#define RTC_SECTP_SECTPU_POS                           (0U)
#define RTC_SECTP_SECTPU                               (0x0FU)
#define RTC_SECTP_SECTPD_POS                           (4U)
#define RTC_SECTP_SECTPD                               (0x70U)

/*  Bit definition for RTC_MINTP register  */
#define RTC_MINTP_MINTPU_POS                           (0U)
#define RTC_MINTP_MINTPU                               (0x0FU)
#define RTC_MINTP_MINTPD_POS                           (4U)
#define RTC_MINTP_MINTPD                               (0x70U)

/*  Bit definition for RTC_HOURTP register  */
#define RTC_HOURTP_HOURTPU_POS                         (0U)
#define RTC_HOURTP_HOURTPU                             (0x0FU)
#define RTC_HOURTP_HOURTPU_0                           (0x01U)
#define RTC_HOURTP_HOURTPU_1                           (0x02U)
#define RTC_HOURTP_HOURTPU_2                           (0x04U)
#define RTC_HOURTP_HOURTPU_3                           (0x08U)
#define RTC_HOURTP_HOURTPD_POS                         (4U)
#define RTC_HOURTP_HOURTPD                             (0x30U)
#define RTC_HOURTP_HOURTPD_0                           (0x10U)
#define RTC_HOURTP_HOURTPD_1                           (0x20U)

/*  Bit definition for RTC_DAYTP register  */
#define RTC_DAYTP_DAYTPU_POS                           (0U)
#define RTC_DAYTP_DAYTPU                               (0x0FU)
#define RTC_DAYTP_DAYTPD_POS                           (4U)
#define RTC_DAYTP_DAYTPD                               (0x30U)

/*  Bit definition for RTC_MONTP register  */
#define RTC_MONTP_MONTP                                (0x1FU)

/*******************************************************************************
                Bit definition for Peripheral SDIOC
*******************************************************************************/
/*  Bit definition for SDIOC_BLKSIZE register  */
#define SDIOC_BLKSIZE_TBS                              (0x0FFFU)

/*  Bit definition for SDIOC_BLKCNT register  */
#define SDIOC_BLKCNT                                   (0xFFFFU)

/*  Bit definition for SDIOC_ARG0 register  */
#define SDIOC_ARG0                                     (0xFFFFU)

/*  Bit definition for SDIOC_ARG1 register  */
#define SDIOC_ARG1                                     (0xFFFFU)

/*  Bit definition for SDIOC_TRANSMODE register  */
#define SDIOC_TRANSMODE_BCE_POS                        (1U)
#define SDIOC_TRANSMODE_BCE                            (0x0002U)
#define SDIOC_TRANSMODE_ATCEN_POS                      (2U)
#define SDIOC_TRANSMODE_ATCEN                          (0x000CU)
#define SDIOC_TRANSMODE_ATCEN_0                        (0x0004U)
#define SDIOC_TRANSMODE_ATCEN_1                        (0x0008U)
#define SDIOC_TRANSMODE_DDIR_POS                       (4U)
#define SDIOC_TRANSMODE_DDIR                           (0x0010U)
#define SDIOC_TRANSMODE_MULB_POS                       (5U)
#define SDIOC_TRANSMODE_MULB                           (0x0020U)

/*  Bit definition for SDIOC_CMD register  */
#define SDIOC_CMD_RESTYP_POS                           (0U)
#define SDIOC_CMD_RESTYP                               (0x0003U)
#define SDIOC_CMD_RESTYP_0                             (0x0001U)
#define SDIOC_CMD_RESTYP_1                             (0x0002U)
#define SDIOC_CMD_CCE_POS                              (3U)
#define SDIOC_CMD_CCE                                  (0x0008U)
#define SDIOC_CMD_ICE_POS                              (4U)
#define SDIOC_CMD_ICE                                  (0x0010U)
#define SDIOC_CMD_DAT_POS                              (5U)
#define SDIOC_CMD_DAT                                  (0x0020U)
#define SDIOC_CMD_TYP_POS                              (6U)
#define SDIOC_CMD_TYP                                  (0x00C0U)
#define SDIOC_CMD_TYP_0                                (0x0040U)
#define SDIOC_CMD_TYP_1                                (0x0080U)
#define SDIOC_CMD_IDX_POS                              (8U)
#define SDIOC_CMD_IDX                                  (0x3F00U)
#define SDIOC_CMD_IDX_0                                (0x0100U)
#define SDIOC_CMD_IDX_1                                (0x0200U)
#define SDIOC_CMD_IDX_2                                (0x0400U)
#define SDIOC_CMD_IDX_3                                (0x0800U)
#define SDIOC_CMD_IDX_4                                (0x1000U)
#define SDIOC_CMD_IDX_5                                (0x2000U)

/*  Bit definition for SDIOC_RESP0 register  */
#define SDIOC_RESP0                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP1 register  */
#define SDIOC_RESP1                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP2 register  */
#define SDIOC_RESP2                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP3 register  */
#define SDIOC_RESP3                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP4 register  */
#define SDIOC_RESP4                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP5 register  */
#define SDIOC_RESP5                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP6 register  */
#define SDIOC_RESP6                                    (0xFFFFU)

/*  Bit definition for SDIOC_RESP7 register  */
#define SDIOC_RESP7                                    (0xFFFFU)

/*  Bit definition for SDIOC_BUF0 register  */
#define SDIOC_BUF0                                     (0xFFFFU)

/*  Bit definition for SDIOC_BUF1 register  */
#define SDIOC_BUF1                                     (0xFFFFU)

/*  Bit definition for SDIOC_PSTAT register  */
#define SDIOC_PSTAT_CIC_POS                            (0U)
#define SDIOC_PSTAT_CIC                                (0x00000001UL)
#define SDIOC_PSTAT_CID_POS                            (1U)
#define SDIOC_PSTAT_CID                                (0x00000002UL)
#define SDIOC_PSTAT_DA_POS                             (2U)
#define SDIOC_PSTAT_DA                                 (0x00000004UL)
#define SDIOC_PSTAT_WTA_POS                            (8U)
#define SDIOC_PSTAT_WTA                                (0x00000100UL)
#define SDIOC_PSTAT_RTA_POS                            (9U)
#define SDIOC_PSTAT_RTA                                (0x00000200UL)
#define SDIOC_PSTAT_BWE_POS                            (10U)
#define SDIOC_PSTAT_BWE                                (0x00000400UL)
#define SDIOC_PSTAT_BRE_POS                            (11U)
#define SDIOC_PSTAT_BRE                                (0x00000800UL)
#define SDIOC_PSTAT_CIN_POS                            (16U)
#define SDIOC_PSTAT_CIN                                (0x00010000UL)
#define SDIOC_PSTAT_CSS_POS                            (17U)
#define SDIOC_PSTAT_CSS                                (0x00020000UL)
#define SDIOC_PSTAT_CDL_POS                            (18U)
#define SDIOC_PSTAT_CDL                                (0x00040000UL)
#define SDIOC_PSTAT_WPL_POS                            (19U)
#define SDIOC_PSTAT_WPL                                (0x00080000UL)
#define SDIOC_PSTAT_DATL_POS                           (20U)
#define SDIOC_PSTAT_DATL                               (0x00F00000UL)
#define SDIOC_PSTAT_DATL_0                             (0x00100000UL)
#define SDIOC_PSTAT_DATL_1                             (0x00200000UL)
#define SDIOC_PSTAT_DATL_2                             (0x00400000UL)
#define SDIOC_PSTAT_DATL_3                             (0x00800000UL)
#define SDIOC_PSTAT_CMDL_POS                           (24U)
#define SDIOC_PSTAT_CMDL                               (0x01000000UL)

/*  Bit definition for SDIOC_HOSTCON register  */
#define SDIOC_HOSTCON_DW_POS                           (1U)
#define SDIOC_HOSTCON_DW                               (0x02U)
#define SDIOC_HOSTCON_HSEN_POS                         (2U)
#define SDIOC_HOSTCON_HSEN                             (0x04U)
#define SDIOC_HOSTCON_EXDW_POS                         (5U)
#define SDIOC_HOSTCON_EXDW                             (0x20U)
#define SDIOC_HOSTCON_CDTL_POS                         (6U)
#define SDIOC_HOSTCON_CDTL                             (0x40U)
#define SDIOC_HOSTCON_CDSS_POS                         (7U)
#define SDIOC_HOSTCON_CDSS                             (0x80U)

/*  Bit definition for SDIOC_PWRCON register  */
#define SDIOC_PWRCON_PWON                              (0x01U)

/*  Bit definition for SDIOC_BLKGPCON register  */
#define SDIOC_BLKGPCON_SABGR_POS                       (0U)
#define SDIOC_BLKGPCON_SABGR                           (0x01U)
#define SDIOC_BLKGPCON_CR_POS                          (1U)
#define SDIOC_BLKGPCON_CR                              (0x02U)
#define SDIOC_BLKGPCON_RWC_POS                         (2U)
#define SDIOC_BLKGPCON_RWC                             (0x04U)
#define SDIOC_BLKGPCON_IABG_POS                        (3U)
#define SDIOC_BLKGPCON_IABG                            (0x08U)

/*  Bit definition for SDIOC_CLKCON register  */
#define SDIOC_CLKCON_ICE_POS                           (0U)
#define SDIOC_CLKCON_ICE                               (0x0001U)
#define SDIOC_CLKCON_CE_POS                            (2U)
#define SDIOC_CLKCON_CE                                (0x0004U)
#define SDIOC_CLKCON_FS_POS                            (8U)
#define SDIOC_CLKCON_FS                                (0xFF00U)
#define SDIOC_CLKCON_FS_0                              (0x0100U)
#define SDIOC_CLKCON_FS_1                              (0x0200U)
#define SDIOC_CLKCON_FS_2                              (0x0400U)
#define SDIOC_CLKCON_FS_3                              (0x0800U)
#define SDIOC_CLKCON_FS_4                              (0x1000U)
#define SDIOC_CLKCON_FS_5                              (0x2000U)
#define SDIOC_CLKCON_FS_6                              (0x4000U)
#define SDIOC_CLKCON_FS_7                              (0x8000U)

/*  Bit definition for SDIOC_TOUTCON register  */
#define SDIOC_TOUTCON_DTO                              (0x0FU)

/*  Bit definition for SDIOC_SFTRST register  */
#define SDIOC_SFTRST_RSTA_POS                          (0U)
#define SDIOC_SFTRST_RSTA                              (0x01U)
#define SDIOC_SFTRST_RSTC_POS                          (1U)
#define SDIOC_SFTRST_RSTC                              (0x02U)
#define SDIOC_SFTRST_RSTD_POS                          (2U)
#define SDIOC_SFTRST_RSTD                              (0x04U)

/*  Bit definition for SDIOC_NORINTST register  */
#define SDIOC_NORINTST_CC_POS                          (0U)
#define SDIOC_NORINTST_CC                              (0x0001U)
#define SDIOC_NORINTST_TC_POS                          (1U)
#define SDIOC_NORINTST_TC                              (0x0002U)
#define SDIOC_NORINTST_BGE_POS                         (2U)
#define SDIOC_NORINTST_BGE                             (0x0004U)
#define SDIOC_NORINTST_BWR_POS                         (4U)
#define SDIOC_NORINTST_BWR                             (0x0010U)
#define SDIOC_NORINTST_BRR_POS                         (5U)
#define SDIOC_NORINTST_BRR                             (0x0020U)
#define SDIOC_NORINTST_CIST_POS                        (6U)
#define SDIOC_NORINTST_CIST                            (0x0040U)
#define SDIOC_NORINTST_CRM_POS                         (7U)
#define SDIOC_NORINTST_CRM                             (0x0080U)
#define SDIOC_NORINTST_CINT_POS                        (8U)
#define SDIOC_NORINTST_CINT                            (0x0100U)
#define SDIOC_NORINTST_EI_POS                          (15U)
#define SDIOC_NORINTST_EI                              (0x8000U)

/*  Bit definition for SDIOC_ERRINTST register  */
#define SDIOC_ERRINTST_CTOE_POS                        (0U)
#define SDIOC_ERRINTST_CTOE                            (0x0001U)
#define SDIOC_ERRINTST_CCE_POS                         (1U)
#define SDIOC_ERRINTST_CCE                             (0x0002U)
#define SDIOC_ERRINTST_CEBE_POS                        (2U)
#define SDIOC_ERRINTST_CEBE                            (0x0004U)
#define SDIOC_ERRINTST_CIE_POS                         (3U)
#define SDIOC_ERRINTST_CIE                             (0x0008U)
#define SDIOC_ERRINTST_DTOE_POS                        (4U)
#define SDIOC_ERRINTST_DTOE                            (0x0010U)
#define SDIOC_ERRINTST_DCE_POS                         (5U)
#define SDIOC_ERRINTST_DCE                             (0x0020U)
#define SDIOC_ERRINTST_DEBE_POS                        (6U)
#define SDIOC_ERRINTST_DEBE                            (0x0040U)
#define SDIOC_ERRINTST_ACE_POS                         (8U)
#define SDIOC_ERRINTST_ACE                             (0x0100U)

/*  Bit definition for SDIOC_NORINTSTEN register  */
#define SDIOC_NORINTSTEN_CCEN_POS                      (0U)
#define SDIOC_NORINTSTEN_CCEN                          (0x0001U)
#define SDIOC_NORINTSTEN_TCEN_POS                      (1U)
#define SDIOC_NORINTSTEN_TCEN                          (0x0002U)
#define SDIOC_NORINTSTEN_BGEEN_POS                     (2U)
#define SDIOC_NORINTSTEN_BGEEN                         (0x0004U)
#define SDIOC_NORINTSTEN_BWREN_POS                     (4U)
#define SDIOC_NORINTSTEN_BWREN                         (0x0010U)
#define SDIOC_NORINTSTEN_BRREN_POS                     (5U)
#define SDIOC_NORINTSTEN_BRREN                         (0x0020U)
#define SDIOC_NORINTSTEN_CISTEN_POS                    (6U)
#define SDIOC_NORINTSTEN_CISTEN                        (0x0040U)
#define SDIOC_NORINTSTEN_CRMEN_POS                     (7U)
#define SDIOC_NORINTSTEN_CRMEN                         (0x0080U)
#define SDIOC_NORINTSTEN_CINTEN_POS                    (8U)
#define SDIOC_NORINTSTEN_CINTEN                        (0x0100U)

/*  Bit definition for SDIOC_ERRINTSTEN register  */
#define SDIOC_ERRINTSTEN_CTOEEN_POS                    (0U)
#define SDIOC_ERRINTSTEN_CTOEEN                        (0x0001U)
#define SDIOC_ERRINTSTEN_CCEEN_POS                     (1U)
#define SDIOC_ERRINTSTEN_CCEEN                         (0x0002U)
#define SDIOC_ERRINTSTEN_CEBEEN_POS                    (2U)
#define SDIOC_ERRINTSTEN_CEBEEN                        (0x0004U)
#define SDIOC_ERRINTSTEN_CIEEN_POS                     (3U)
#define SDIOC_ERRINTSTEN_CIEEN                         (0x0008U)
#define SDIOC_ERRINTSTEN_DTOEEN_POS                    (4U)
#define SDIOC_ERRINTSTEN_DTOEEN                        (0x0010U)
#define SDIOC_ERRINTSTEN_DCEEN_POS                     (5U)
#define SDIOC_ERRINTSTEN_DCEEN                         (0x0020U)
#define SDIOC_ERRINTSTEN_DEBEEN_POS                    (6U)
#define SDIOC_ERRINTSTEN_DEBEEN                        (0x0040U)
#define SDIOC_ERRINTSTEN_ACEEN_POS                     (8U)
#define SDIOC_ERRINTSTEN_ACEEN                         (0x0100U)

/*  Bit definition for SDIOC_NORINTSGEN register  */
#define SDIOC_NORINTSGEN_CCSEN_POS                     (0U)
#define SDIOC_NORINTSGEN_CCSEN                         (0x0001U)
#define SDIOC_NORINTSGEN_TCSEN_POS                     (1U)
#define SDIOC_NORINTSGEN_TCSEN                         (0x0002U)
#define SDIOC_NORINTSGEN_BGESEN_POS                    (2U)
#define SDIOC_NORINTSGEN_BGESEN                        (0x0004U)
#define SDIOC_NORINTSGEN_BWRSEN_POS                    (4U)
#define SDIOC_NORINTSGEN_BWRSEN                        (0x0010U)
#define SDIOC_NORINTSGEN_BRRSEN_POS                    (5U)
#define SDIOC_NORINTSGEN_BRRSEN                        (0x0020U)
#define SDIOC_NORINTSGEN_CISTSEN_POS                   (6U)
#define SDIOC_NORINTSGEN_CISTSEN                       (0x0040U)
#define SDIOC_NORINTSGEN_CRMSEN_POS                    (7U)
#define SDIOC_NORINTSGEN_CRMSEN                        (0x0080U)
#define SDIOC_NORINTSGEN_CINTSEN_POS                   (8U)
#define SDIOC_NORINTSGEN_CINTSEN                       (0x0100U)

/*  Bit definition for SDIOC_ERRINTSGEN register  */
#define SDIOC_ERRINTSGEN_CTOESEN_POS                   (0U)
#define SDIOC_ERRINTSGEN_CTOESEN                       (0x0001U)
#define SDIOC_ERRINTSGEN_CCESEN_POS                    (1U)
#define SDIOC_ERRINTSGEN_CCESEN                        (0x0002U)
#define SDIOC_ERRINTSGEN_CEBESEN_POS                   (2U)
#define SDIOC_ERRINTSGEN_CEBESEN                       (0x0004U)
#define SDIOC_ERRINTSGEN_CIESEN_POS                    (3U)
#define SDIOC_ERRINTSGEN_CIESEN                        (0x0008U)
#define SDIOC_ERRINTSGEN_DTOESEN_POS                   (4U)
#define SDIOC_ERRINTSGEN_DTOESEN                       (0x0010U)
#define SDIOC_ERRINTSGEN_DCESEN_POS                    (5U)
#define SDIOC_ERRINTSGEN_DCESEN                        (0x0020U)
#define SDIOC_ERRINTSGEN_DEBESEN_POS                   (6U)
#define SDIOC_ERRINTSGEN_DEBESEN                       (0x0040U)
#define SDIOC_ERRINTSGEN_ACESEN_POS                    (8U)
#define SDIOC_ERRINTSGEN_ACESEN                        (0x0100U)

/*  Bit definition for SDIOC_ATCERRST register  */
#define SDIOC_ATCERRST_NE_POS                          (0U)
#define SDIOC_ATCERRST_NE                              (0x0001U)
#define SDIOC_ATCERRST_TOE_POS                         (1U)
#define SDIOC_ATCERRST_TOE                             (0x0002U)
#define SDIOC_ATCERRST_CE_POS                          (2U)
#define SDIOC_ATCERRST_CE                              (0x0004U)
#define SDIOC_ATCERRST_EBE_POS                         (3U)
#define SDIOC_ATCERRST_EBE                             (0x0008U)
#define SDIOC_ATCERRST_IE_POS                          (4U)
#define SDIOC_ATCERRST_IE                              (0x0010U)
#define SDIOC_ATCERRST_CMDE_POS                        (7U)
#define SDIOC_ATCERRST_CMDE                            (0x0080U)

/*  Bit definition for SDIOC_FEA register  */
#define SDIOC_FEA_FNE_POS                              (0U)
#define SDIOC_FEA_FNE                                  (0x0001U)
#define SDIOC_FEA_FTOE_POS                             (1U)
#define SDIOC_FEA_FTOE                                 (0x0002U)
#define SDIOC_FEA_FCE_POS                              (2U)
#define SDIOC_FEA_FCE                                  (0x0004U)
#define SDIOC_FEA_FEBE_POS                             (3U)
#define SDIOC_FEA_FEBE                                 (0x0008U)
#define SDIOC_FEA_FIE_POS                              (4U)
#define SDIOC_FEA_FIE                                  (0x0010U)
#define SDIOC_FEA_FCMDE_POS                            (7U)
#define SDIOC_FEA_FCMDE                                (0x0080U)

/*  Bit definition for SDIOC_FEE register  */
#define SDIOC_FEE_FCTOE_POS                            (0U)
#define SDIOC_FEE_FCTOE                                (0x0001U)
#define SDIOC_FEE_FCCE_POS                             (1U)
#define SDIOC_FEE_FCCE                                 (0x0002U)
#define SDIOC_FEE_FCEBE_POS                            (2U)
#define SDIOC_FEE_FCEBE                                (0x0004U)
#define SDIOC_FEE_FCIE_POS                             (3U)
#define SDIOC_FEE_FCIE                                 (0x0008U)
#define SDIOC_FEE_FDTOE_POS                            (4U)
#define SDIOC_FEE_FDTOE                                (0x0010U)
#define SDIOC_FEE_FDCE_POS                             (5U)
#define SDIOC_FEE_FDCE                                 (0x0020U)
#define SDIOC_FEE_FDEBE_POS                            (6U)
#define SDIOC_FEE_FDEBE                                (0x0040U)
#define SDIOC_FEE_FACE_POS                             (8U)
#define SDIOC_FEE_FACE                                 (0x0100U)

/*******************************************************************************
                Bit definition for Peripheral SMC
*******************************************************************************/
/*  Bit definition for SMC_STSR register  */
#define SMC_STSR_STATUS                                (0x00000001UL)

/*  Bit definition for SMC_STCR0 register  */
#define SMC_STCR0_LPWIR_POS                            (2U)
#define SMC_STCR0_LPWIR                                (0x00000004UL)

/*  Bit definition for SMC_STCR1 register  */
#define SMC_STCR1_LPWOR_POS                            (2U)
#define SMC_STCR1_LPWOR                                (0x00000004UL)

/*  Bit definition for SMC_CMDR register  */
#define SMC_CMDR_CMDADD_POS                            (0U)
#define SMC_CMDR_CMDADD                                (0x000FFFFFUL)
#define SMC_CMDR_CRES_POS                              (20U)
#define SMC_CMDR_CRES                                  (0x00100000UL)
#define SMC_CMDR_CMD_POS                               (21U)
#define SMC_CMDR_CMD                                   (0x00600000UL)
#define SMC_CMDR_CMD_0                                 (0x00200000UL)
#define SMC_CMDR_CMD_1                                 (0x00400000UL)
#define SMC_CMDR_CMDCHIP_POS                           (23U)
#define SMC_CMDR_CMDCHIP                               (0x03800000UL)

/*  Bit definition for SMC_TMCR register  */
#define SMC_TMCR_T_RC_POS                              (0U)
#define SMC_TMCR_T_RC                                  (0x0000000FUL)
#define SMC_TMCR_T_WC_POS                              (4U)
#define SMC_TMCR_T_WC                                  (0x000000F0UL)
#define SMC_TMCR_T_CEOE_POS                            (8U)
#define SMC_TMCR_T_CEOE                                (0x00000700UL)
#define SMC_TMCR_T_WP_POS                              (12U)
#define SMC_TMCR_T_WP                                  (0x00007000UL)
#define SMC_TMCR_T_PC_POS                              (16U)
#define SMC_TMCR_T_PC                                  (0x00070000UL)
#define SMC_TMCR_T_TR_POS                              (20U)
#define SMC_TMCR_T_TR                                  (0x00700000UL)

/*  Bit definition for SMC_CPCR register  */
#define SMC_CPCR_RSYN_POS                              (0U)
#define SMC_CPCR_RSYN                                  (0x00000001UL)
#define SMC_CPCR_RBL_POS                               (1U)
#define SMC_CPCR_RBL                                   (0x0000000EUL)
#define SMC_CPCR_RBL_0                                 (0x00000002UL)
#define SMC_CPCR_RBL_1                                 (0x00000004UL)
#define SMC_CPCR_RBL_2                                 (0x00000008UL)
#define SMC_CPCR_WSYN_POS                              (4U)
#define SMC_CPCR_WSYN                                  (0x00000010UL)
#define SMC_CPCR_WBL_POS                               (5U)
#define SMC_CPCR_WBL                                   (0x000000E0UL)
#define SMC_CPCR_MW_POS                                (8U)
#define SMC_CPCR_MW                                    (0x00000300UL)
#define SMC_CPCR_MW_0                                  (0x00000100UL)
#define SMC_CPCR_MW_1                                  (0x00000200UL)
#define SMC_CPCR_BAAS_POS                              (10U)
#define SMC_CPCR_BAAS                                  (0x00000400UL)
#define SMC_CPCR_ADVS_POS                              (11U)
#define SMC_CPCR_ADVS                                  (0x00000800UL)
#define SMC_CPCR_BLSS_POS                              (12U)
#define SMC_CPCR_BLSS                                  (0x00001000UL)

/*  Bit definition for SMC_RFTR register  */
#define SMC_RFTR_REFPRD                                (0x0000000FUL)

/*  Bit definition for SMC_TMSR register  */
#define SMC_TMSR_T_RC_POS                              (0U)
#define SMC_TMSR_T_RC                                  (0x0000000FUL)
#define SMC_TMSR_T_WC_POS                              (4U)
#define SMC_TMSR_T_WC                                  (0x000000F0UL)
#define SMC_TMSR_T_CEOE_POS                            (8U)
#define SMC_TMSR_T_CEOE                                (0x00000700UL)
#define SMC_TMSR_T_WP_POS                              (12U)
#define SMC_TMSR_T_WP                                  (0x00007000UL)
#define SMC_TMSR_T_PC_POS                              (16U)
#define SMC_TMSR_T_PC                                  (0x00070000UL)
#define SMC_TMSR_T_TR_POS                              (20U)
#define SMC_TMSR_T_TR                                  (0x00700000UL)

/*  Bit definition for SMC_CPSR register  */
#define SMC_CPSR_RSYN_POS                              (0U)
#define SMC_CPSR_RSYN                                  (0x00000001UL)
#define SMC_CPSR_RBL_POS                               (1U)
#define SMC_CPSR_RBL                                   (0x0000000EUL)
#define SMC_CPSR_WSYN_POS                              (4U)
#define SMC_CPSR_WSYN                                  (0x00000010UL)
#define SMC_CPSR_WBL_POS                               (5U)
#define SMC_CPSR_WBL                                   (0x000000E0UL)
#define SMC_CPSR_MW_POS                                (8U)
#define SMC_CPSR_MW                                    (0x00000300UL)
#define SMC_CPSR_BAAS_POS                              (10U)
#define SMC_CPSR_BAAS                                  (0x00000400UL)
#define SMC_CPSR_ADVS_POS                              (11U)
#define SMC_CPSR_ADVS                                  (0x00000800UL)
#define SMC_CPSR_BLSS_POS                              (12U)
#define SMC_CPSR_BLSS                                  (0x00001000UL)
#define SMC_CPSR_ADDMSK_POS                            (16U)
#define SMC_CPSR_ADDMSK                                (0x00FF0000UL)
#define SMC_CPSR_ADDMAT_POS                            (24U)
#define SMC_CPSR_ADDMAT                                (0xFF000000UL)

/*  Bit definition for SMC_BACR register  */
#define SMC_BACR_MUXMD_POS                             (4U)
#define SMC_BACR_MUXMD                                 (0x00000010UL)
#define SMC_BACR_CKSEL_POS                             (14U)
#define SMC_BACR_CKSEL                                 (0x0000C000UL)
#define SMC_BACR_CKSEL_0                               (0x00004000UL)
#define SMC_BACR_CKSEL_1                               (0x00008000UL)

/*  Bit definition for SMC_CSCR0 register  */
#define SMC_CSCR0_ADDMSK0_POS                          (0U)
#define SMC_CSCR0_ADDMSK0                              (0x000000FFUL)
#define SMC_CSCR0_ADDMSK1_POS                          (8U)
#define SMC_CSCR0_ADDMSK1                              (0x0000FF00UL)
#define SMC_CSCR0_ADDMSK2_POS                          (16U)
#define SMC_CSCR0_ADDMSK2                              (0x00FF0000UL)
#define SMC_CSCR0_ADDMSK3_POS                          (24U)
#define SMC_CSCR0_ADDMSK3                              (0xFF000000UL)

/*  Bit definition for SMC_CSCR1 register  */
#define SMC_CSCR1_ADDMAT0_POS                          (0U)
#define SMC_CSCR1_ADDMAT0                              (0x000000FFUL)
#define SMC_CSCR1_ADDMAT1_POS                          (8U)
#define SMC_CSCR1_ADDMAT1                              (0x0000FF00UL)
#define SMC_CSCR1_ADDMAT2_POS                          (16U)
#define SMC_CSCR1_ADDMAT2                              (0x00FF0000UL)
#define SMC_CSCR1_ADDMAT3_POS                          (24U)
#define SMC_CSCR1_ADDMAT3                              (0xFF000000UL)

/*******************************************************************************
                Bit definition for Peripheral SPI
*******************************************************************************/
/*  Bit definition for SPI_DR register  */
#define SPI_DR                                         (0xFFFFFFFFUL)

/*  Bit definition for SPI_CR1 register  */
#define SPI_CR1_SPIMDS_POS                             (0U)
#define SPI_CR1_SPIMDS                                 (0x00000001UL)
#define SPI_CR1_TXMDS_POS                              (1U)
#define SPI_CR1_TXMDS                                  (0x00000002UL)
#define SPI_CR1_MSTR_POS                               (3U)
#define SPI_CR1_MSTR                                   (0x00000008UL)
#define SPI_CR1_SPLPBK_POS                             (4U)
#define SPI_CR1_SPLPBK                                 (0x00000010UL)
#define SPI_CR1_SPLPBK2_POS                            (5U)
#define SPI_CR1_SPLPBK2                                (0x00000020UL)
#define SPI_CR1_SPE_POS                                (6U)
#define SPI_CR1_SPE                                    (0x00000040UL)
#define SPI_CR1_CSUSPE_POS                             (7U)
#define SPI_CR1_CSUSPE                                 (0x00000080UL)
#define SPI_CR1_EIE_POS                                (8U)
#define SPI_CR1_EIE                                    (0x00000100UL)
#define SPI_CR1_TXIE_POS                               (9U)
#define SPI_CR1_TXIE                                   (0x00000200UL)
#define SPI_CR1_RXIE_POS                               (10U)
#define SPI_CR1_RXIE                                   (0x00000400UL)
#define SPI_CR1_IDIE_POS                               (11U)
#define SPI_CR1_IDIE                                   (0x00000800UL)
#define SPI_CR1_MODFE_POS                              (12U)
#define SPI_CR1_MODFE                                  (0x00001000UL)
#define SPI_CR1_PATE_POS                               (13U)
#define SPI_CR1_PATE                                   (0x00002000UL)
#define SPI_CR1_PAOE_POS                               (14U)
#define SPI_CR1_PAOE                                   (0x00004000UL)
#define SPI_CR1_PAE_POS                                (15U)
#define SPI_CR1_PAE                                    (0x00008000UL)

/*  Bit definition for SPI_CFG1 register  */
#define SPI_CFG1_FTHLV_POS                             (0U)
#define SPI_CFG1_FTHLV                                 (0x00000003UL)
#define SPI_CFG1_FTHLV_0                               (0x00000001UL)
#define SPI_CFG1_FTHLV_1                               (0x00000002UL)
#define SPI_CFG1_SPRDTD_POS                            (6U)
#define SPI_CFG1_SPRDTD                                (0x00000040UL)
#define SPI_CFG1_SS0PV_POS                             (8U)
#define SPI_CFG1_SS0PV                                 (0x00000100UL)
#define SPI_CFG1_SS1PV_POS                             (9U)
#define SPI_CFG1_SS1PV                                 (0x00000200UL)
#define SPI_CFG1_SS2PV_POS                             (10U)
#define SPI_CFG1_SS2PV                                 (0x00000400UL)
#define SPI_CFG1_SS3PV_POS                             (11U)
#define SPI_CFG1_SS3PV                                 (0x00000800UL)
#define SPI_CFG1_MSSI_POS                              (20U)
#define SPI_CFG1_MSSI                                  (0x00700000UL)
#define SPI_CFG1_MSSI_0                                (0x00100000UL)
#define SPI_CFG1_MSSI_1                                (0x00200000UL)
#define SPI_CFG1_MSSI_2                                (0x00400000UL)
#define SPI_CFG1_MSSDL_POS                             (24U)
#define SPI_CFG1_MSSDL                                 (0x07000000UL)
#define SPI_CFG1_MSSDL_0                               (0x01000000UL)
#define SPI_CFG1_MSSDL_1                               (0x02000000UL)
#define SPI_CFG1_MSSDL_2                               (0x04000000UL)
#define SPI_CFG1_MIDI_POS                              (28U)
#define SPI_CFG1_MIDI                                  (0x70000000UL)
#define SPI_CFG1_MIDI_0                                (0x10000000UL)
#define SPI_CFG1_MIDI_1                                (0x20000000UL)
#define SPI_CFG1_MIDI_2                                (0x40000000UL)

/*  Bit definition for SPI_SR register  */
#define SPI_SR_OVRERF_POS                              (0U)
#define SPI_SR_OVRERF                                  (0x00000001UL)
#define SPI_SR_IDLNF_POS                               (1U)
#define SPI_SR_IDLNF                                   (0x00000002UL)
#define SPI_SR_MODFERF_POS                             (2U)
#define SPI_SR_MODFERF                                 (0x00000004UL)
#define SPI_SR_PERF_POS                                (3U)
#define SPI_SR_PERF                                    (0x00000008UL)
#define SPI_SR_UDRERF_POS                              (4U)
#define SPI_SR_UDRERF                                  (0x00000010UL)
#define SPI_SR_TDEF_POS                                (5U)
#define SPI_SR_TDEF                                    (0x00000020UL)
#define SPI_SR_RDFF_POS                                (7U)
#define SPI_SR_RDFF                                    (0x00000080UL)

/*  Bit definition for SPI_CFG2 register  */
#define SPI_CFG2_CPHA_POS                              (0U)
#define SPI_CFG2_CPHA                                  (0x00000001UL)
#define SPI_CFG2_CPOL_POS                              (1U)
#define SPI_CFG2_CPOL                                  (0x00000002UL)
#define SPI_CFG2_MBR_POS                               (2U)
#define SPI_CFG2_MBR                                   (0x0000001CUL)
#define SPI_CFG2_MBR_0                                 (0x00000004UL)
#define SPI_CFG2_MBR_1                                 (0x00000008UL)
#define SPI_CFG2_MBR_2                                 (0x00000010UL)
#define SPI_CFG2_SSA_POS                               (5U)
#define SPI_CFG2_SSA                                   (0x000000E0UL)
#define SPI_CFG2_SSA_0                                 (0x00000020UL)
#define SPI_CFG2_SSA_1                                 (0x00000040UL)
#define SPI_CFG2_SSA_2                                 (0x00000080UL)
#define SPI_CFG2_DSIZE_POS                             (8U)
#define SPI_CFG2_DSIZE                                 (0x00000F00UL)
#define SPI_CFG2_DSIZE_0                               (0x00000100UL)
#define SPI_CFG2_DSIZE_1                               (0x00000200UL)
#define SPI_CFG2_DSIZE_2                               (0x00000400UL)
#define SPI_CFG2_DSIZE_3                               (0x00000800UL)
#define SPI_CFG2_LSBF_POS                              (12U)
#define SPI_CFG2_LSBF                                  (0x00001000UL)
#define SPI_CFG2_MIDIE_POS                             (13U)
#define SPI_CFG2_MIDIE                                 (0x00002000UL)
#define SPI_CFG2_MSSDLE_POS                            (14U)
#define SPI_CFG2_MSSDLE                                (0x00004000UL)
#define SPI_CFG2_MSSIE_POS                             (15U)
#define SPI_CFG2_MSSIE                                 (0x00008000UL)

/*******************************************************************************
                Bit definition for Peripheral SRAMC
*******************************************************************************/
/*  Bit definition for SRAMC_WTCR register  */
#define SRAMC_WTCR_SRAM123RWT_POS                      (0U)
#define SRAMC_WTCR_SRAM123RWT                          (0x00000007UL)
#define SRAMC_WTCR_SRAM123WWT_POS                      (4U)
#define SRAMC_WTCR_SRAM123WWT                          (0x00000070UL)
#define SRAMC_WTCR_SRAM4RWT_POS                        (8U)
#define SRAMC_WTCR_SRAM4RWT                            (0x00000700UL)
#define SRAMC_WTCR_SRAM4WWT_POS                        (12U)
#define SRAMC_WTCR_SRAM4WWT                            (0x00007000UL)
#define SRAMC_WTCR_SRAMHRWT_POS                        (16U)
#define SRAMC_WTCR_SRAMHRWT                            (0x00070000UL)
#define SRAMC_WTCR_SRAMHWWT_POS                        (20U)
#define SRAMC_WTCR_SRAMHWWT                            (0x00700000UL)
#define SRAMC_WTCR_SRAMBRWT_POS                        (24U)
#define SRAMC_WTCR_SRAMBRWT                            (0x07000000UL)
#define SRAMC_WTCR_SRAMBWWT_POS                        (28U)
#define SRAMC_WTCR_SRAMBWWT                            (0x70000000UL)

/*  Bit definition for SRAMC_WTPR register  */
#define SRAMC_WTPR_WTPRC_POS                           (0U)
#define SRAMC_WTPR_WTPRC                               (0x00000001UL)
#define SRAMC_WTPR_WTPRKW_POS                          (1U)
#define SRAMC_WTPR_WTPRKW                              (0x000000FEUL)

/*  Bit definition for SRAMC_CKCR register  */
#define SRAMC_CKCR_PYOAD_POS                           (0U)
#define SRAMC_CKCR_PYOAD                               (0x00000001UL)
#define SRAMC_CKCR_ECCOAD_POS                          (16U)
#define SRAMC_CKCR_ECCOAD                              (0x00010000UL)
#define SRAMC_CKCR_BECCOAD_POS                         (17U)
#define SRAMC_CKCR_BECCOAD                             (0x00020000UL)
#define SRAMC_CKCR_ECCMOD_POS                          (24U)
#define SRAMC_CKCR_ECCMOD                              (0x03000000UL)
#define SRAMC_CKCR_ECCMOD_0                            (0x01000000UL)
#define SRAMC_CKCR_ECCMOD_1                            (0x02000000UL)
#define SRAMC_CKCR_BECCMOD_POS                         (26U)
#define SRAMC_CKCR_BECCMOD                             (0x0C000000UL)
#define SRAMC_CKCR_BECCMOD_0                           (0x04000000UL)
#define SRAMC_CKCR_BECCMOD_1                           (0x08000000UL)

/*  Bit definition for SRAMC_CKPR register  */
#define SRAMC_CKPR_CKPRC_POS                           (0U)
#define SRAMC_CKPR_CKPRC                               (0x00000001UL)
#define SRAMC_CKPR_CKPRKW_POS                          (1U)
#define SRAMC_CKPR_CKPRKW                              (0x000000FEUL)

/*  Bit definition for SRAMC_CKSR register  */
#define SRAMC_CKSR_SRAM1_PYERR_POS                     (0U)
#define SRAMC_CKSR_SRAM1_PYERR                         (0x00000001UL)
#define SRAMC_CKSR_SRAM2_PYERR_POS                     (1U)
#define SRAMC_CKSR_SRAM2_PYERR                         (0x00000002UL)
#define SRAMC_CKSR_SRAM3_PYERR_POS                     (2U)
#define SRAMC_CKSR_SRAM3_PYERR                         (0x00000004UL)
#define SRAMC_CKSR_SRAMH_PYERR_POS                     (3U)
#define SRAMC_CKSR_SRAMH_PYERR                         (0x00000008UL)
#define SRAMC_CKSR_SRAM4_1ERR_POS                      (4U)
#define SRAMC_CKSR_SRAM4_1ERR                          (0x00000010UL)
#define SRAMC_CKSR_SRAM4_2ERR_POS                      (5U)
#define SRAMC_CKSR_SRAM4_2ERR                          (0x00000020UL)
#define SRAMC_CKSR_SRAMB_1ERR_POS                      (6U)
#define SRAMC_CKSR_SRAMB_1ERR                          (0x00000040UL)
#define SRAMC_CKSR_SRAMB_2ERR_POS                      (7U)
#define SRAMC_CKSR_SRAMB_2ERR                          (0x00000080UL)
#define SRAMC_CKSR_CACHE_PYERR_POS                     (8U)
#define SRAMC_CKSR_CACHE_PYERR                         (0x00000100UL)

/*******************************************************************************
                Bit definition for Peripheral SWDT
*******************************************************************************/
/*  Bit definition for SWDT_CR register  */
#define SWDT_CR_PERI_POS                               (0U)
#define SWDT_CR_PERI                                   (0x00000003UL)
#define SWDT_CR_PERI_0                                 (0x00000001UL)
#define SWDT_CR_PERI_1                                 (0x00000002UL)
#define SWDT_CR_CKS_POS                                (4U)
#define SWDT_CR_CKS                                    (0x000000F0UL)
#define SWDT_CR_CKS_0                                  (0x00000010UL)
#define SWDT_CR_CKS_1                                  (0x00000020UL)
#define SWDT_CR_CKS_2                                  (0x00000040UL)
#define SWDT_CR_CKS_3                                  (0x00000080UL)
#define SWDT_CR_WDPT_POS                               (8U)
#define SWDT_CR_WDPT                                   (0x00000F00UL)
#define SWDT_CR_WDPT_0                                 (0x00000100UL)
#define SWDT_CR_WDPT_1                                 (0x00000200UL)
#define SWDT_CR_WDPT_2                                 (0x00000400UL)
#define SWDT_CR_WDPT_3                                 (0x00000800UL)
#define SWDT_CR_SLPOFF_POS                             (16U)
#define SWDT_CR_SLPOFF                                 (0x00010000UL)
#define SWDT_CR_ITS_POS                                (31U)
#define SWDT_CR_ITS                                    (0x80000000UL)

/*  Bit definition for SWDT_SR register  */
#define SWDT_SR_CNT_POS                                (0U)
#define SWDT_SR_CNT                                    (0x0000FFFFUL)
#define SWDT_SR_UDF_POS                                (16U)
#define SWDT_SR_UDF                                    (0x00010000UL)
#define SWDT_SR_REF_POS                                (17U)
#define SWDT_SR_REF                                    (0x00020000UL)

/*  Bit definition for SWDT_RR register  */
#define SWDT_RR_RF                                     (0x0000FFFFUL)

/*******************************************************************************
                Bit definition for Peripheral TMR0
*******************************************************************************/
/*  Bit definition for TMR0_CNTAR register  */
#define TMR0_CNTAR_CNTA                                (0x0000FFFFUL)

/*  Bit definition for TMR0_CNTBR register  */
#define TMR0_CNTBR_CNTB                                (0x0000FFFFUL)

/*  Bit definition for TMR0_CMPAR register  */
#define TMR0_CMPAR_CMPA                                (0x0000FFFFUL)

/*  Bit definition for TMR0_CMPBR register  */
#define TMR0_CMPBR_CMPB                                (0x0000FFFFUL)

/*  Bit definition for TMR0_BCONR register  */
#define TMR0_BCONR_CSTA_POS                            (0U)
#define TMR0_BCONR_CSTA                                (0x00000001UL)
#define TMR0_BCONR_CAPMDA_POS                          (1U)
#define TMR0_BCONR_CAPMDA                              (0x00000002UL)
#define TMR0_BCONR_INTENA_POS                          (2U)
#define TMR0_BCONR_INTENA                              (0x00000004UL)
#define TMR0_BCONR_CKDIVA_POS                          (4U)
#define TMR0_BCONR_CKDIVA                              (0x000000F0UL)
#define TMR0_BCONR_SYNSA_POS                           (8U)
#define TMR0_BCONR_SYNSA                               (0x00000100UL)
#define TMR0_BCONR_SYNCLKA_POS                         (9U)
#define TMR0_BCONR_SYNCLKA                             (0x00000200UL)
#define TMR0_BCONR_ASYNCLKA_POS                        (10U)
#define TMR0_BCONR_ASYNCLKA                            (0x00000400UL)
#define TMR0_BCONR_HSTAA_POS                           (12U)
#define TMR0_BCONR_HSTAA                               (0x00001000UL)
#define TMR0_BCONR_HSTPA_POS                           (13U)
#define TMR0_BCONR_HSTPA                               (0x00002000UL)
#define TMR0_BCONR_HCLEA_POS                           (14U)
#define TMR0_BCONR_HCLEA                               (0x00004000UL)
#define TMR0_BCONR_HICPA_POS                           (15U)
#define TMR0_BCONR_HICPA                               (0x00008000UL)
#define TMR0_BCONR_CSTB_POS                            (16U)
#define TMR0_BCONR_CSTB                                (0x00010000UL)
#define TMR0_BCONR_CAPMDB_POS                          (17U)
#define TMR0_BCONR_CAPMDB                              (0x00020000UL)
#define TMR0_BCONR_INTENB_POS                          (18U)
#define TMR0_BCONR_INTENB                              (0x00040000UL)
#define TMR0_BCONR_CKDIVB_POS                          (20U)
#define TMR0_BCONR_CKDIVB                              (0x00F00000UL)
#define TMR0_BCONR_SYNSB_POS                           (24U)
#define TMR0_BCONR_SYNSB                               (0x01000000UL)
#define TMR0_BCONR_SYNCLKB_POS                         (25U)
#define TMR0_BCONR_SYNCLKB                             (0x02000000UL)
#define TMR0_BCONR_ASYNCLKB_POS                        (26U)
#define TMR0_BCONR_ASYNCLKB                            (0x04000000UL)
#define TMR0_BCONR_HSTAB_POS                           (28U)
#define TMR0_BCONR_HSTAB                               (0x10000000UL)
#define TMR0_BCONR_HSTPB_POS                           (29U)
#define TMR0_BCONR_HSTPB                               (0x20000000UL)
#define TMR0_BCONR_HCLEB_POS                           (30U)
#define TMR0_BCONR_HCLEB                               (0x40000000UL)
#define TMR0_BCONR_HICPB_POS                           (31U)
#define TMR0_BCONR_HICPB                               (0x80000000UL)

/*  Bit definition for TMR0_STFLR register  */
#define TMR0_STFLR_CMFA_POS                            (0U)
#define TMR0_STFLR_CMFA                                (0x00000001UL)
#define TMR0_STFLR_CMFB_POS                            (16U)
#define TMR0_STFLR_CMFB                                (0x00010000UL)

/*******************************************************************************
                Bit definition for Peripheral TMR2
*******************************************************************************/
/*  Bit definition for TMR2_CNTAR register  */
#define TMR2_CNTAR_CNTA                                (0x0000FFFFUL)

/*  Bit definition for TMR2_CNTBR register  */
#define TMR2_CNTBR_CNTB                                (0x0000FFFFUL)

/*  Bit definition for TMR2_CMPAR register  */
#define TMR2_CMPAR_CMPA                                (0x0000FFFFUL)

/*  Bit definition for TMR2_CMPBR register  */
#define TMR2_CMPBR_CMPB                                (0x0000FFFFUL)

/*  Bit definition for TMR2_BCONR register  */
#define TMR2_BCONR_CSTA_POS                            (0U)
#define TMR2_BCONR_CSTA                                (0x00000001UL)
#define TMR2_BCONR_CAPMDA_POS                          (1U)
#define TMR2_BCONR_CAPMDA                              (0x00000002UL)
#define TMR2_BCONR_SYNSA_POS                           (3U)
#define TMR2_BCONR_SYNSA                               (0x00000008UL)
#define TMR2_BCONR_CKDIVA_POS                          (4U)
#define TMR2_BCONR_CKDIVA                              (0x000000F0UL)
#define TMR2_BCONR_SYNCLKA_POS                         (8U)
#define TMR2_BCONR_SYNCLKA                             (0x00000300UL)
#define TMR2_BCONR_SYNCLKA_0                           (0x00000100UL)
#define TMR2_BCONR_SYNCLKA_1                           (0x00000200UL)
#define TMR2_BCONR_ASYNCLKA_POS                        (10U)
#define TMR2_BCONR_ASYNCLKA                            (0x00000C00UL)
#define TMR2_BCONR_ASYNCLKA_0                          (0x00000400UL)
#define TMR2_BCONR_ASYNCLKA_1                          (0x00000800UL)
#define TMR2_BCONR_SYNCLKAT_POS                        (12U)
#define TMR2_BCONR_SYNCLKAT                            (0x00003000UL)
#define TMR2_BCONR_SYNCLKAT_0                          (0x00001000UL)
#define TMR2_BCONR_SYNCLKAT_1                          (0x00002000UL)
#define TMR2_BCONR_CSTB_POS                            (16U)
#define TMR2_BCONR_CSTB                                (0x00010000UL)
#define TMR2_BCONR_CAPMDB_POS                          (17U)
#define TMR2_BCONR_CAPMDB                              (0x00020000UL)
#define TMR2_BCONR_SYNSB_POS                           (19U)
#define TMR2_BCONR_SYNSB                               (0x00080000UL)
#define TMR2_BCONR_CKDIVB_POS                          (20U)
#define TMR2_BCONR_CKDIVB                              (0x00F00000UL)
#define TMR2_BCONR_SYNCLKB_POS                         (24U)
#define TMR2_BCONR_SYNCLKB                             (0x03000000UL)
#define TMR2_BCONR_SYNCLKB_0                           (0x01000000UL)
#define TMR2_BCONR_SYNCLKB_1                           (0x02000000UL)
#define TMR2_BCONR_ASYNCLKB_POS                        (26U)
#define TMR2_BCONR_ASYNCLKB                            (0x0C000000UL)
#define TMR2_BCONR_ASYNCLKB_0                          (0x04000000UL)
#define TMR2_BCONR_ASYNCLKB_1                          (0x08000000UL)
#define TMR2_BCONR_SYNCLKBT_POS                        (28U)
#define TMR2_BCONR_SYNCLKBT                            (0x30000000UL)
#define TMR2_BCONR_SYNCLKBT_0                          (0x10000000UL)
#define TMR2_BCONR_SYNCLKBT_1                          (0x20000000UL)

/*  Bit definition for TMR2_ICONR register  */
#define TMR2_ICONR_CMENA_POS                           (0U)
#define TMR2_ICONR_CMENA                               (0x00000001UL)
#define TMR2_ICONR_OVENA_POS                           (1U)
#define TMR2_ICONR_OVENA                               (0x00000002UL)
#define TMR2_ICONR_CMENB_POS                           (16U)
#define TMR2_ICONR_CMENB                               (0x00010000UL)
#define TMR2_ICONR_OVENB_POS                           (17U)
#define TMR2_ICONR_OVENB                               (0x00020000UL)

/*  Bit definition for TMR2_PCONR register  */
#define TMR2_PCONR_STACA_POS                           (0U)
#define TMR2_PCONR_STACA                               (0x00000003UL)
#define TMR2_PCONR_STACA_0                             (0x00000001UL)
#define TMR2_PCONR_STACA_1                             (0x00000002UL)
#define TMR2_PCONR_STPCA_POS                           (2U)
#define TMR2_PCONR_STPCA                               (0x0000000CUL)
#define TMR2_PCONR_STPCA_0                             (0x00000004UL)
#define TMR2_PCONR_STPCA_1                             (0x00000008UL)
#define TMR2_PCONR_CMPCA_POS                           (4U)
#define TMR2_PCONR_CMPCA                               (0x00000030UL)
#define TMR2_PCONR_CMPCA_0                             (0x00000010UL)
#define TMR2_PCONR_CMPCA_1                             (0x00000020UL)
#define TMR2_PCONR_OUTENA_POS                          (8U)
#define TMR2_PCONR_OUTENA                              (0x00000100UL)
#define TMR2_PCONR_NOFIENA_POS                         (12U)
#define TMR2_PCONR_NOFIENA                             (0x00001000UL)
#define TMR2_PCONR_NOFICKA_POS                         (13U)
#define TMR2_PCONR_NOFICKA                             (0x00006000UL)
#define TMR2_PCONR_NOFICKA_0                           (0x00002000UL)
#define TMR2_PCONR_NOFICKA_1                           (0x00004000UL)
#define TMR2_PCONR_STACB_POS                           (16U)
#define TMR2_PCONR_STACB                               (0x00030000UL)
#define TMR2_PCONR_STACB_0                             (0x00010000UL)
#define TMR2_PCONR_STACB_1                             (0x00020000UL)
#define TMR2_PCONR_STPCB_POS                           (18U)
#define TMR2_PCONR_STPCB                               (0x000C0000UL)
#define TMR2_PCONR_STPCB_0                             (0x00040000UL)
#define TMR2_PCONR_STPCB_1                             (0x00080000UL)
#define TMR2_PCONR_CMPCB_POS                           (20U)
#define TMR2_PCONR_CMPCB                               (0x00300000UL)
#define TMR2_PCONR_CMPCB_0                             (0x00100000UL)
#define TMR2_PCONR_CMPCB_1                             (0x00200000UL)
#define TMR2_PCONR_OUTENB_POS                          (24U)
#define TMR2_PCONR_OUTENB                              (0x01000000UL)
#define TMR2_PCONR_NOFIENB_POS                         (28U)
#define TMR2_PCONR_NOFIENB                             (0x10000000UL)
#define TMR2_PCONR_NOFICKB_POS                         (29U)
#define TMR2_PCONR_NOFICKB                             (0x60000000UL)
#define TMR2_PCONR_NOFICKB_0                           (0x20000000UL)
#define TMR2_PCONR_NOFICKB_1                           (0x40000000UL)

/*  Bit definition for TMR2_HCONR register  */
#define TMR2_HCONR_HSTAA0_POS                          (0U)
#define TMR2_HCONR_HSTAA0                              (0x00000001UL)
#define TMR2_HCONR_HSTAA1_POS                          (1U)
#define TMR2_HCONR_HSTAA1                              (0x00000002UL)
#define TMR2_HCONR_HSTAA2_POS                          (2U)
#define TMR2_HCONR_HSTAA2                              (0x00000004UL)
#define TMR2_HCONR_HSTPA0_POS                          (4U)
#define TMR2_HCONR_HSTPA0                              (0x00000010UL)
#define TMR2_HCONR_HSTPA1_POS                          (5U)
#define TMR2_HCONR_HSTPA1                              (0x00000020UL)
#define TMR2_HCONR_HSTPA2_POS                          (6U)
#define TMR2_HCONR_HSTPA2                              (0x00000040UL)
#define TMR2_HCONR_HCLEA0_POS                          (8U)
#define TMR2_HCONR_HCLEA0                              (0x00000100UL)
#define TMR2_HCONR_HCLEA1_POS                          (9U)
#define TMR2_HCONR_HCLEA1                              (0x00000200UL)
#define TMR2_HCONR_HCLEA2_POS                          (10U)
#define TMR2_HCONR_HCLEA2                              (0x00000400UL)
#define TMR2_HCONR_HICPA0_POS                          (12U)
#define TMR2_HCONR_HICPA0                              (0x00001000UL)
#define TMR2_HCONR_HICPA1_POS                          (13U)
#define TMR2_HCONR_HICPA1                              (0x00002000UL)
#define TMR2_HCONR_HICPA2_POS                          (14U)
#define TMR2_HCONR_HICPA2                              (0x00004000UL)
#define TMR2_HCONR_HSTAB0_POS                          (16U)
#define TMR2_HCONR_HSTAB0                              (0x00010000UL)
#define TMR2_HCONR_HSTAB1_POS                          (17U)
#define TMR2_HCONR_HSTAB1                              (0x00020000UL)
#define TMR2_HCONR_HSTAB2_POS                          (18U)
#define TMR2_HCONR_HSTAB2                              (0x00040000UL)
#define TMR2_HCONR_HSTPB0_POS                          (20U)
#define TMR2_HCONR_HSTPB0                              (0x00100000UL)
#define TMR2_HCONR_HSTPB1_POS                          (21U)
#define TMR2_HCONR_HSTPB1                              (0x00200000UL)
#define TMR2_HCONR_HSTPB2_POS                          (22U)
#define TMR2_HCONR_HSTPB2                              (0x00400000UL)
#define TMR2_HCONR_HCLEB0_POS                          (24U)
#define TMR2_HCONR_HCLEB0                              (0x01000000UL)
#define TMR2_HCONR_HCLEB1_POS                          (25U)
#define TMR2_HCONR_HCLEB1                              (0x02000000UL)
#define TMR2_HCONR_HCLEB2_POS                          (26U)
#define TMR2_HCONR_HCLEB2                              (0x04000000UL)
#define TMR2_HCONR_HICPB0_POS                          (28U)
#define TMR2_HCONR_HICPB0                              (0x10000000UL)
#define TMR2_HCONR_HICPB1_POS                          (29U)
#define TMR2_HCONR_HICPB1                              (0x20000000UL)
#define TMR2_HCONR_HICPB2_POS                          (30U)
#define TMR2_HCONR_HICPB2                              (0x40000000UL)

/*  Bit definition for TMR2_STFLR register  */
#define TMR2_STFLR_CMFA_POS                            (0U)
#define TMR2_STFLR_CMFA                                (0x00000001UL)
#define TMR2_STFLR_OVFA_POS                            (1U)
#define TMR2_STFLR_OVFA                                (0x00000002UL)
#define TMR2_STFLR_CMFB_POS                            (16U)
#define TMR2_STFLR_CMFB                                (0x00010000UL)
#define TMR2_STFLR_OVFB_POS                            (17U)
#define TMR2_STFLR_OVFB                                (0x00020000UL)

/*******************************************************************************
                Bit definition for Peripheral TMR4
*******************************************************************************/
/*  Bit definition for TMR4_OCCRUH register  */
#define TMR4_OCCRUH                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRUL register  */
#define TMR4_OCCRUL                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRVH register  */
#define TMR4_OCCRVH                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRVL register  */
#define TMR4_OCCRVL                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRWH register  */
#define TMR4_OCCRWH                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRWL register  */
#define TMR4_OCCRWL                                    (0xFFFFU)

/*  Bit definition for TMR4_OCSR register  */
#define TMR4_OCSR_OCEH_POS                             (0U)
#define TMR4_OCSR_OCEH                                 (0x0001U)
#define TMR4_OCSR_OCEL_POS                             (1U)
#define TMR4_OCSR_OCEL                                 (0x0002U)
#define TMR4_OCSR_OCPH_POS                             (2U)
#define TMR4_OCSR_OCPH                                 (0x0004U)
#define TMR4_OCSR_OCPL_POS                             (3U)
#define TMR4_OCSR_OCPL                                 (0x0008U)
#define TMR4_OCSR_OCIEH_POS                            (4U)
#define TMR4_OCSR_OCIEH                                (0x0010U)
#define TMR4_OCSR_OCIEL_POS                            (5U)
#define TMR4_OCSR_OCIEL                                (0x0020U)
#define TMR4_OCSR_OCFH_POS                             (6U)
#define TMR4_OCSR_OCFH                                 (0x0040U)
#define TMR4_OCSR_OCFL_POS                             (7U)
#define TMR4_OCSR_OCFL                                 (0x0080U)

/*  Bit definition for TMR4_OCER register  */
#define TMR4_OCER_CHBUFEN_POS                          (0U)
#define TMR4_OCER_CHBUFEN                              (0x0003U)
#define TMR4_OCER_CHBUFEN_0                            (0x0001U)
#define TMR4_OCER_CHBUFEN_1                            (0x0002U)
#define TMR4_OCER_CLBUFEN_POS                          (2U)
#define TMR4_OCER_CLBUFEN                              (0x000CU)
#define TMR4_OCER_CLBUFEN_0                            (0x0004U)
#define TMR4_OCER_CLBUFEN_1                            (0x0008U)
#define TMR4_OCER_MHBUFEN_POS                          (4U)
#define TMR4_OCER_MHBUFEN                              (0x0030U)
#define TMR4_OCER_MHBUFEN_0                            (0x0010U)
#define TMR4_OCER_MHBUFEN_1                            (0x0020U)
#define TMR4_OCER_MLBUFEN_POS                          (6U)
#define TMR4_OCER_MLBUFEN                              (0x00C0U)
#define TMR4_OCER_MLBUFEN_0                            (0x0040U)
#define TMR4_OCER_MLBUFEN_1                            (0x0080U)
#define TMR4_OCER_LMCH_POS                             (8U)
#define TMR4_OCER_LMCH                                 (0x0100U)
#define TMR4_OCER_LMCL_POS                             (9U)
#define TMR4_OCER_LMCL                                 (0x0200U)
#define TMR4_OCER_LMMH_POS                             (10U)
#define TMR4_OCER_LMMH                                 (0x0400U)
#define TMR4_OCER_LMML_POS                             (11U)
#define TMR4_OCER_LMML                                 (0x0800U)
#define TMR4_OCER_MCECH_POS                            (12U)
#define TMR4_OCER_MCECH                                (0x1000U)
#define TMR4_OCER_MCECL_POS                            (13U)
#define TMR4_OCER_MCECL                                (0x2000U)

/*  Bit definition for TMR4_OCMRH register  */
#define TMR4_OCMRH_OCFDCH_POS                          (0U)
#define TMR4_OCMRH_OCFDCH                              (0x0001U)
#define TMR4_OCMRH_OCFPKH_POS                          (1U)
#define TMR4_OCMRH_OCFPKH                              (0x0002U)
#define TMR4_OCMRH_OCFUCH_POS                          (2U)
#define TMR4_OCMRH_OCFUCH                              (0x0004U)
#define TMR4_OCMRH_OCFZRH_POS                          (3U)
#define TMR4_OCMRH_OCFZRH                              (0x0008U)
#define TMR4_OCMRH_OPDCH_POS                           (4U)
#define TMR4_OCMRH_OPDCH                               (0x0030U)
#define TMR4_OCMRH_OPDCH_0                             (0x0010U)
#define TMR4_OCMRH_OPDCH_1                             (0x0020U)
#define TMR4_OCMRH_OPPKH_POS                           (6U)
#define TMR4_OCMRH_OPPKH                               (0x00C0U)
#define TMR4_OCMRH_OPPKH_0                             (0x0040U)
#define TMR4_OCMRH_OPPKH_1                             (0x0080U)
#define TMR4_OCMRH_OPUCH_POS                           (8U)
#define TMR4_OCMRH_OPUCH                               (0x0300U)
#define TMR4_OCMRH_OPUCH_0                             (0x0100U)
#define TMR4_OCMRH_OPUCH_1                             (0x0200U)
#define TMR4_OCMRH_OPZRH_POS                           (10U)
#define TMR4_OCMRH_OPZRH                               (0x0C00U)
#define TMR4_OCMRH_OPZRH_0                             (0x0400U)
#define TMR4_OCMRH_OPZRH_1                             (0x0800U)
#define TMR4_OCMRH_OPNPKH_POS                          (12U)
#define TMR4_OCMRH_OPNPKH                              (0x3000U)
#define TMR4_OCMRH_OPNPKH_0                            (0x1000U)
#define TMR4_OCMRH_OPNPKH_1                            (0x2000U)
#define TMR4_OCMRH_OPNZRH_POS                          (14U)
#define TMR4_OCMRH_OPNZRH                              (0xC000U)
#define TMR4_OCMRH_OPNZRH_0                            (0x4000U)
#define TMR4_OCMRH_OPNZRH_1                            (0x8000U)

/*  Bit definition for TMR4_OCMRL register  */
#define TMR4_OCMRL_OCFDCL_POS                          (0U)
#define TMR4_OCMRL_OCFDCL                              (0x00000001UL)
#define TMR4_OCMRL_OCFPKL_POS                          (1U)
#define TMR4_OCMRL_OCFPKL                              (0x00000002UL)
#define TMR4_OCMRL_OCFUCL_POS                          (2U)
#define TMR4_OCMRL_OCFUCL                              (0x00000004UL)
#define TMR4_OCMRL_OCFZRL_POS                          (3U)
#define TMR4_OCMRL_OCFZRL                              (0x00000008UL)
#define TMR4_OCMRL_OPDCL_POS                           (4U)
#define TMR4_OCMRL_OPDCL                               (0x00000030UL)
#define TMR4_OCMRL_OPDCL_0                             (0x00000010UL)
#define TMR4_OCMRL_OPDCL_1                             (0x00000020UL)
#define TMR4_OCMRL_OPPKL_POS                           (6U)
#define TMR4_OCMRL_OPPKL                               (0x000000C0UL)
#define TMR4_OCMRL_OPPKL_0                             (0x00000040UL)
#define TMR4_OCMRL_OPPKL_1                             (0x00000080UL)
#define TMR4_OCMRL_OPUCL_POS                           (8U)
#define TMR4_OCMRL_OPUCL                               (0x00000300UL)
#define TMR4_OCMRL_OPUCL_0                             (0x00000100UL)
#define TMR4_OCMRL_OPUCL_1                             (0x00000200UL)
#define TMR4_OCMRL_OPZRL_POS                           (10U)
#define TMR4_OCMRL_OPZRL                               (0x00000C00UL)
#define TMR4_OCMRL_OPZRL_0                             (0x00000400UL)
#define TMR4_OCMRL_OPZRL_1                             (0x00000800UL)
#define TMR4_OCMRL_OPNPKL_POS                          (12U)
#define TMR4_OCMRL_OPNPKL                              (0x00003000UL)
#define TMR4_OCMRL_OPNPKL_0                            (0x00001000UL)
#define TMR4_OCMRL_OPNPKL_1                            (0x00002000UL)
#define TMR4_OCMRL_OPNZRL_POS                          (14U)
#define TMR4_OCMRL_OPNZRL                              (0x0000C000UL)
#define TMR4_OCMRL_OPNZRL_0                            (0x00004000UL)
#define TMR4_OCMRL_OPNZRL_1                            (0x00008000UL)
#define TMR4_OCMRL_EOPNDCL_POS                         (16U)
#define TMR4_OCMRL_EOPNDCL                             (0x00030000UL)
#define TMR4_OCMRL_EOPNDCL_0                           (0x00010000UL)
#define TMR4_OCMRL_EOPNDCL_1                           (0x00020000UL)
#define TMR4_OCMRL_EOPNUCL_POS                         (18U)
#define TMR4_OCMRL_EOPNUCL                             (0x000C0000UL)
#define TMR4_OCMRL_EOPNUCL_0                           (0x00040000UL)
#define TMR4_OCMRL_EOPNUCL_1                           (0x00080000UL)
#define TMR4_OCMRL_EOPDCL_POS                          (20U)
#define TMR4_OCMRL_EOPDCL                              (0x00300000UL)
#define TMR4_OCMRL_EOPDCL_0                            (0x00100000UL)
#define TMR4_OCMRL_EOPDCL_1                            (0x00200000UL)
#define TMR4_OCMRL_EOPPKL_POS                          (22U)
#define TMR4_OCMRL_EOPPKL                              (0x00C00000UL)
#define TMR4_OCMRL_EOPPKL_0                            (0x00400000UL)
#define TMR4_OCMRL_EOPPKL_1                            (0x00800000UL)
#define TMR4_OCMRL_EOPUCL_POS                          (24U)
#define TMR4_OCMRL_EOPUCL                              (0x03000000UL)
#define TMR4_OCMRL_EOPUCL_0                            (0x01000000UL)
#define TMR4_OCMRL_EOPUCL_1                            (0x02000000UL)
#define TMR4_OCMRL_EOPZRL_POS                          (26U)
#define TMR4_OCMRL_EOPZRL                              (0x0C000000UL)
#define TMR4_OCMRL_EOPZRL_0                            (0x04000000UL)
#define TMR4_OCMRL_EOPZRL_1                            (0x08000000UL)
#define TMR4_OCMRL_EOPNPKL_POS                         (28U)
#define TMR4_OCMRL_EOPNPKL                             (0x30000000UL)
#define TMR4_OCMRL_EOPNPKL_0                           (0x10000000UL)
#define TMR4_OCMRL_EOPNPKL_1                           (0x20000000UL)
#define TMR4_OCMRL_EOPNZRL_POS                         (30U)
#define TMR4_OCMRL_EOPNZRL                             (0xC0000000UL)
#define TMR4_OCMRL_EOPNZRL_0                           (0x40000000UL)
#define TMR4_OCMRL_EOPNZRL_1                           (0x80000000UL)

/*  Bit definition for TMR4_CPSR register  */
#define TMR4_CPSR                                      (0xFFFFU)

/*  Bit definition for TMR4_CNTR register  */
#define TMR4_CNTR                                      (0xFFFFU)

/*  Bit definition for TMR4_CCSR register  */
#define TMR4_CCSR_CKDIV_POS                            (0U)
#define TMR4_CCSR_CKDIV                                (0x000FU)
#define TMR4_CCSR_CLEAR_POS                            (4U)
#define TMR4_CCSR_CLEAR                                (0x0010U)
#define TMR4_CCSR_MODE_POS                             (5U)
#define TMR4_CCSR_MODE                                 (0x0020U)
#define TMR4_CCSR_STOP_POS                             (6U)
#define TMR4_CCSR_STOP                                 (0x0040U)
#define TMR4_CCSR_BUFEN_POS                            (7U)
#define TMR4_CCSR_BUFEN                                (0x0080U)
#define TMR4_CCSR_IRQPEN_POS                           (8U)
#define TMR4_CCSR_IRQPEN                               (0x0100U)
#define TMR4_CCSR_IRQPF_POS                            (9U)
#define TMR4_CCSR_IRQPF                                (0x0200U)
#define TMR4_CCSR_IRQZEN_POS                           (13U)
#define TMR4_CCSR_IRQZEN                               (0x2000U)
#define TMR4_CCSR_IRQZF_POS                            (14U)
#define TMR4_CCSR_IRQZF                                (0x4000U)
#define TMR4_CCSR_ECKEN_POS                            (15U)
#define TMR4_CCSR_ECKEN                                (0x8000U)

/*  Bit definition for TMR4_CVPR register  */
#define TMR4_CVPR_ZIM_POS                              (0U)
#define TMR4_CVPR_ZIM                                  (0x000FU)
#define TMR4_CVPR_PIM_POS                              (4U)
#define TMR4_CVPR_PIM                                  (0x00F0U)
#define TMR4_CVPR_ZIC_POS                              (8U)
#define TMR4_CVPR_ZIC                                  (0x0F00U)
#define TMR4_CVPR_PIC_POS                              (12U)
#define TMR4_CVPR_PIC                                  (0xF000U)

/*  Bit definition for TMR4_PFSRU register  */
#define TMR4_PFSRU                                     (0xFFFFU)

/*  Bit definition for TMR4_PDARU register  */
#define TMR4_PDARU                                     (0xFFFFU)

/*  Bit definition for TMR4_PDBRU register  */
#define TMR4_PDBRU                                     (0xFFFFU)

/*  Bit definition for TMR4_PFSRV register  */
#define TMR4_PFSRV                                     (0xFFFFU)

/*  Bit definition for TMR4_PDARV register  */
#define TMR4_PDARV                                     (0xFFFFU)

/*  Bit definition for TMR4_PDBRV register  */
#define TMR4_PDBRV                                     (0xFFFFU)

/*  Bit definition for TMR4_PFSRW register  */
#define TMR4_PFSRW                                     (0xFFFFU)

/*  Bit definition for TMR4_PDARW register  */
#define TMR4_PDARW                                     (0xFFFFU)

/*  Bit definition for TMR4_PDBRW register  */
#define TMR4_PDBRW                                     (0xFFFFU)

/*  Bit definition for TMR4_POCR register  */
#define TMR4_POCR_DIVCK_POS                            (0U)
#define TMR4_POCR_DIVCK                                (0x0007U)
#define TMR4_POCR_PWMMD_POS                            (4U)
#define TMR4_POCR_PWMMD                                (0x0030U)
#define TMR4_POCR_PWMMD_0                              (0x0010U)
#define TMR4_POCR_PWMMD_1                              (0x0020U)
#define TMR4_POCR_LVLS_POS                             (6U)
#define TMR4_POCR_LVLS                                 (0x00C0U)
#define TMR4_POCR_LVLS_0                               (0x0040U)
#define TMR4_POCR_LVLS_1                               (0x0080U)

/*  Bit definition for TMR4_RCSR register  */
#define TMR4_RCSR_RTIDU_POS                            (0U)
#define TMR4_RCSR_RTIDU                                (0x0001U)
#define TMR4_RCSR_RTIDV_POS                            (1U)
#define TMR4_RCSR_RTIDV                                (0x0002U)
#define TMR4_RCSR_RTIDW_POS                            (2U)
#define TMR4_RCSR_RTIDW                                (0x0004U)
#define TMR4_RCSR_RTIFU_POS                            (4U)
#define TMR4_RCSR_RTIFU                                (0x0010U)
#define TMR4_RCSR_RTICU_POS                            (5U)
#define TMR4_RCSR_RTICU                                (0x0020U)
#define TMR4_RCSR_RTEU_POS                             (6U)
#define TMR4_RCSR_RTEU                                 (0x0040U)
#define TMR4_RCSR_RTSU_POS                             (7U)
#define TMR4_RCSR_RTSU                                 (0x0080U)
#define TMR4_RCSR_RTIFV_POS                            (8U)
#define TMR4_RCSR_RTIFV                                (0x0100U)
#define TMR4_RCSR_RTICV_POS                            (9U)
#define TMR4_RCSR_RTICV                                (0x0200U)
#define TMR4_RCSR_RTEV_POS                             (10U)
#define TMR4_RCSR_RTEV                                 (0x0400U)
#define TMR4_RCSR_RTSV_POS                             (11U)
#define TMR4_RCSR_RTSV                                 (0x0800U)
#define TMR4_RCSR_RTIFW_POS                            (12U)
#define TMR4_RCSR_RTIFW                                (0x1000U)
#define TMR4_RCSR_RTICW_POS                            (13U)
#define TMR4_RCSR_RTICW                                (0x2000U)
#define TMR4_RCSR_RTEW_POS                             (14U)
#define TMR4_RCSR_RTEW                                 (0x4000U)
#define TMR4_RCSR_RTSW_POS                             (15U)
#define TMR4_RCSR_RTSW                                 (0x8000U)

/*  Bit definition for TMR4_SCCRUH register  */
#define TMR4_SCCRUH                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRUL register  */
#define TMR4_SCCRUL                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRVH register  */
#define TMR4_SCCRVH                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRVL register  */
#define TMR4_SCCRVL                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRWH register  */
#define TMR4_SCCRWH                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRWL register  */
#define TMR4_SCCRWL                                    (0xFFFFU)

/*  Bit definition for TMR4_SCSR register  */
#define TMR4_SCSR_BUFEN_POS                            (0U)
#define TMR4_SCSR_BUFEN                                (0x0003U)
#define TMR4_SCSR_BUFEN_0                              (0x0001U)
#define TMR4_SCSR_BUFEN_1                              (0x0002U)
#define TMR4_SCSR_EVTOS_POS                            (2U)
#define TMR4_SCSR_EVTOS                                (0x001CU)
#define TMR4_SCSR_LMC_POS                              (5U)
#define TMR4_SCSR_LMC                                  (0x0020U)
#define TMR4_SCSR_EVTMS_POS                            (8U)
#define TMR4_SCSR_EVTMS                                (0x0100U)
#define TMR4_SCSR_EVTDS_POS                            (9U)
#define TMR4_SCSR_EVTDS                                (0x0200U)
#define TMR4_SCSR_DEN_POS                              (12U)
#define TMR4_SCSR_DEN                                  (0x1000U)
#define TMR4_SCSR_PEN_POS                              (13U)
#define TMR4_SCSR_PEN                                  (0x2000U)
#define TMR4_SCSR_UEN_POS                              (14U)
#define TMR4_SCSR_UEN                                  (0x4000U)
#define TMR4_SCSR_ZEN_POS                              (15U)
#define TMR4_SCSR_ZEN                                  (0x8000U)

/*  Bit definition for TMR4_SCMR register  */
#define TMR4_SCMR_AMC_POS                              (0U)
#define TMR4_SCMR_AMC                                  (0x000FU)
#define TMR4_SCMR_MZCE_POS                             (6U)
#define TMR4_SCMR_MZCE                                 (0x0040U)
#define TMR4_SCMR_MPCE_POS                             (7U)
#define TMR4_SCMR_MPCE                                 (0x0080U)

/*  Bit definition for TMR4_PSCR register  */
#define TMR4_PSCR_OEUH_POS                             (0U)
#define TMR4_PSCR_OEUH                                 (0x00000001UL)
#define TMR4_PSCR_OEUL_POS                             (1U)
#define TMR4_PSCR_OEUL                                 (0x00000002UL)
#define TMR4_PSCR_OEVH_POS                             (2U)
#define TMR4_PSCR_OEVH                                 (0x00000004UL)
#define TMR4_PSCR_OEVL_POS                             (3U)
#define TMR4_PSCR_OEVL                                 (0x00000008UL)
#define TMR4_PSCR_OEWH_POS                             (4U)
#define TMR4_PSCR_OEWH                                 (0x00000010UL)
#define TMR4_PSCR_OEWL_POS                             (5U)
#define TMR4_PSCR_OEWL                                 (0x00000020UL)
#define TMR4_PSCR_ODT_POS                              (6U)
#define TMR4_PSCR_ODT                                  (0x000000C0UL)
#define TMR4_PSCR_ODT_0                                (0x00000040UL)
#define TMR4_PSCR_ODT_1                                (0x00000080UL)
#define TMR4_PSCR_MOE_POS                              (8U)
#define TMR4_PSCR_MOE                                  (0x00000100UL)
#define TMR4_PSCR_AOE_POS                              (9U)
#define TMR4_PSCR_AOE                                  (0x00000200UL)
#define TMR4_PSCR_OSUH_POS                             (16U)
#define TMR4_PSCR_OSUH                                 (0x00030000UL)
#define TMR4_PSCR_OSUH_0                               (0x00010000UL)
#define TMR4_PSCR_OSUH_1                               (0x00020000UL)
#define TMR4_PSCR_OSUL_POS                             (18U)
#define TMR4_PSCR_OSUL                                 (0x000C0000UL)
#define TMR4_PSCR_OSUL_0                               (0x00040000UL)
#define TMR4_PSCR_OSUL_1                               (0x00080000UL)
#define TMR4_PSCR_OSVH_POS                             (20U)
#define TMR4_PSCR_OSVH                                 (0x00300000UL)
#define TMR4_PSCR_OSVH_0                               (0x00100000UL)
#define TMR4_PSCR_OSVH_1                               (0x00200000UL)
#define TMR4_PSCR_OSVL_POS                             (22U)
#define TMR4_PSCR_OSVL                                 (0x00C00000UL)
#define TMR4_PSCR_OSVL_0                               (0x00400000UL)
#define TMR4_PSCR_OSVL_1                               (0x00800000UL)
#define TMR4_PSCR_OSWH_POS                             (24U)
#define TMR4_PSCR_OSWH                                 (0x03000000UL)
#define TMR4_PSCR_OSWH_0                               (0x01000000UL)
#define TMR4_PSCR_OSWH_1                               (0x02000000UL)
#define TMR4_PSCR_OSWL_POS                             (26U)
#define TMR4_PSCR_OSWL                                 (0x0C000000UL)
#define TMR4_PSCR_OSWL_0                               (0x04000000UL)
#define TMR4_PSCR_OSWL_1                               (0x08000000UL)

/*  Bit definition for TMR4_SCER register  */
#define TMR4_SCER_EVTRS_POS                            (0U)
#define TMR4_SCER_EVTRS                                (0x0007U)
#define TMR4_SCER_PCTS_POS                             (3U)
#define TMR4_SCER_PCTS                                 (0x0008U)

/*******************************************************************************
                Bit definition for Peripheral TMR6
*******************************************************************************/
/*  Bit definition for TMR6_CNTER register  */
#define TMR6_CNTER                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_UPDAR register  */
#define TMR6_UPDAR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_PERAR register  */
#define TMR6_PERAR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_PERBR register  */
#define TMR6_PERBR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_PERCR register  */
#define TMR6_PERCR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCMAR register  */
#define TMR6_GCMAR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCMBR register  */
#define TMR6_GCMBR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCMCR register  */
#define TMR6_GCMCR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCMDR register  */
#define TMR6_GCMDR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCMER register  */
#define TMR6_GCMER                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCMFR register  */
#define TMR6_GCMFR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_SCMAR register  */
#define TMR6_SCMAR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_SCMBR register  */
#define TMR6_SCMBR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_SCMCR register  */
#define TMR6_SCMCR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_SCMDR register  */
#define TMR6_SCMDR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_SCMER register  */
#define TMR6_SCMER                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_SCMFR register  */
#define TMR6_SCMFR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_DTUAR register  */
#define TMR6_DTUAR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_DTDAR register  */
#define TMR6_DTDAR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_DTUBR register  */
#define TMR6_DTUBR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_DTDBR register  */
#define TMR6_DTDBR                                     (0xFFFFFFFFUL)

/*  Bit definition for TMR6_GCONR register  */
#define TMR6_GCONR_START_POS                           (0U)
#define TMR6_GCONR_START                               (0x00000001UL)
#define TMR6_GCONR_DIR_POS                             (1U)
#define TMR6_GCONR_DIR                                 (0x00000002UL)
#define TMR6_GCONR_MODE_POS                            (2U)
#define TMR6_GCONR_MODE                                (0x00000004UL)
#define TMR6_GCONR_CKDIV_POS                           (4U)
#define TMR6_GCONR_CKDIV                               (0x000000F0UL)
#define TMR6_GCONR_CKDIV_0                             (0x00000010UL)
#define TMR6_GCONR_CKDIV_1                             (0x00000020UL)
#define TMR6_GCONR_CKDIV_2                             (0x00000040UL)
#define TMR6_GCONR_CKDIV_3                             (0x00000080UL)
#define TMR6_GCONR_OVSTP_POS                           (8U)
#define TMR6_GCONR_OVSTP                               (0x00000100UL)
#define TMR6_GCONR_ZMSKREV_POS                         (16U)
#define TMR6_GCONR_ZMSKREV                             (0x00010000UL)
#define TMR6_GCONR_ZMSKPOS_POS                         (17U)
#define TMR6_GCONR_ZMSKPOS                             (0x00020000UL)
#define TMR6_GCONR_ZMSKVAL_POS                         (18U)
#define TMR6_GCONR_ZMSKVAL                             (0x000C0000UL)
#define TMR6_GCONR_ZMSKVAL_0                           (0x00040000UL)
#define TMR6_GCONR_ZMSKVAL_1                           (0x00080000UL)

/*  Bit definition for TMR6_ICONR register  */
#define TMR6_ICONR_INTENA_POS                          (0U)
#define TMR6_ICONR_INTENA                              (0x00000001UL)
#define TMR6_ICONR_INTENB_POS                          (1U)
#define TMR6_ICONR_INTENB                              (0x00000002UL)
#define TMR6_ICONR_INTENC_POS                          (2U)
#define TMR6_ICONR_INTENC                              (0x00000004UL)
#define TMR6_ICONR_INTEND_POS                          (3U)
#define TMR6_ICONR_INTEND                              (0x00000008UL)
#define TMR6_ICONR_INTENE_POS                          (4U)
#define TMR6_ICONR_INTENE                              (0x00000010UL)
#define TMR6_ICONR_INTENF_POS                          (5U)
#define TMR6_ICONR_INTENF                              (0x00000020UL)
#define TMR6_ICONR_INTENOVF_POS                        (6U)
#define TMR6_ICONR_INTENOVF                            (0x00000040UL)
#define TMR6_ICONR_INTENUDF_POS                        (7U)
#define TMR6_ICONR_INTENUDF                            (0x00000080UL)
#define TMR6_ICONR_INTENDTE_POS                        (8U)
#define TMR6_ICONR_INTENDTE                            (0x00000100UL)
#define TMR6_ICONR_INTENSAU_POS                        (16U)
#define TMR6_ICONR_INTENSAU                            (0x00010000UL)
#define TMR6_ICONR_INTENSAD_POS                        (17U)
#define TMR6_ICONR_INTENSAD                            (0x00020000UL)
#define TMR6_ICONR_INTENSBU_POS                        (18U)
#define TMR6_ICONR_INTENSBU                            (0x00040000UL)
#define TMR6_ICONR_INTENSBD_POS                        (19U)
#define TMR6_ICONR_INTENSBD                            (0x00080000UL)

/*  Bit definition for TMR6_BCONR register  */
#define TMR6_BCONR_BENA_POS                            (0U)
#define TMR6_BCONR_BENA                                (0x00000001UL)
#define TMR6_BCONR_BSEA_POS                            (1U)
#define TMR6_BCONR_BSEA                                (0x00000002UL)
#define TMR6_BCONR_BTRUA_POS                           (2U)
#define TMR6_BCONR_BTRUA                               (0x00000004UL)
#define TMR6_BCONR_BTRDA_POS                           (3U)
#define TMR6_BCONR_BTRDA                               (0x00000008UL)
#define TMR6_BCONR_BENB_POS                            (4U)
#define TMR6_BCONR_BENB                                (0x00000010UL)
#define TMR6_BCONR_BSEB_POS                            (5U)
#define TMR6_BCONR_BSEB                                (0x00000020UL)
#define TMR6_BCONR_BTRUB_POS                           (6U)
#define TMR6_BCONR_BTRUB                               (0x00000040UL)
#define TMR6_BCONR_BTRDB_POS                           (7U)
#define TMR6_BCONR_BTRDB                               (0x00000080UL)
#define TMR6_BCONR_BENP_POS                            (8U)
#define TMR6_BCONR_BENP                                (0x00000100UL)
#define TMR6_BCONR_BSEP_POS                            (9U)
#define TMR6_BCONR_BSEP                                (0x00000200UL)
#define TMR6_BCONR_BTRUP_POS                           (10U)
#define TMR6_BCONR_BTRUP                               (0x00000400UL)
#define TMR6_BCONR_BTRDP_POS                           (11U)
#define TMR6_BCONR_BTRDP                               (0x00000800UL)
#define TMR6_BCONR_BENSPA_POS                          (16U)
#define TMR6_BCONR_BENSPA                              (0x00010000UL)
#define TMR6_BCONR_BSESPA_POS                          (17U)
#define TMR6_BCONR_BSESPA                              (0x00020000UL)
#define TMR6_BCONR_BTRUSPA_POS                         (18U)
#define TMR6_BCONR_BTRUSPA                             (0x00040000UL)
#define TMR6_BCONR_BTRDSPA_POS                         (19U)
#define TMR6_BCONR_BTRDSPA                             (0x00080000UL)
#define TMR6_BCONR_BENSPB_POS                          (20U)
#define TMR6_BCONR_BENSPB                              (0x00100000UL)
#define TMR6_BCONR_BSESPB_POS                          (21U)
#define TMR6_BCONR_BSESPB                              (0x00200000UL)
#define TMR6_BCONR_BTRUSPB_POS                         (22U)
#define TMR6_BCONR_BTRUSPB                             (0x00400000UL)
#define TMR6_BCONR_BTRDSPB_POS                         (23U)
#define TMR6_BCONR_BTRDSPB                             (0x00800000UL)

/*  Bit definition for TMR6_DCONR register  */
#define TMR6_DCONR_DTCEN_POS                           (0U)
#define TMR6_DCONR_DTCEN                               (0x00000001UL)
#define TMR6_DCONR_SEPA_POS                            (1U)
#define TMR6_DCONR_SEPA                                (0x00000002UL)
#define TMR6_DCONR_DTBENU_POS                          (4U)
#define TMR6_DCONR_DTBENU                              (0x00000010UL)
#define TMR6_DCONR_DTBEND_POS                          (5U)
#define TMR6_DCONR_DTBEND                              (0x00000020UL)
#define TMR6_DCONR_DTBTRU_POS                          (6U)
#define TMR6_DCONR_DTBTRU                              (0x00000040UL)
#define TMR6_DCONR_DTBTRD_POS                          (7U)
#define TMR6_DCONR_DTBTRD                              (0x00000080UL)

/*  Bit definition for TMR6_PCNAR register  */
#define TMR6_PCNAR_STACA_POS                           (0U)
#define TMR6_PCNAR_STACA                               (0x00000003UL)
#define TMR6_PCNAR_STACA_0                             (0x00000001UL)
#define TMR6_PCNAR_STACA_1                             (0x00000002UL)
#define TMR6_PCNAR_STPCA_POS                           (2U)
#define TMR6_PCNAR_STPCA                               (0x0000000CUL)
#define TMR6_PCNAR_STPCA_0                             (0x00000004UL)
#define TMR6_PCNAR_STPCA_1                             (0x00000008UL)
#define TMR6_PCNAR_OVFCA_POS                           (4U)
#define TMR6_PCNAR_OVFCA                               (0x00000030UL)
#define TMR6_PCNAR_OVFCA_0                             (0x00000010UL)
#define TMR6_PCNAR_OVFCA_1                             (0x00000020UL)
#define TMR6_PCNAR_UDFCA_POS                           (6U)
#define TMR6_PCNAR_UDFCA                               (0x000000C0UL)
#define TMR6_PCNAR_UDFCA_0                             (0x00000040UL)
#define TMR6_PCNAR_UDFCA_1                             (0x00000080UL)
#define TMR6_PCNAR_CMAUCA_POS                          (8U)
#define TMR6_PCNAR_CMAUCA                              (0x00000300UL)
#define TMR6_PCNAR_CMAUCA_0                            (0x00000100UL)
#define TMR6_PCNAR_CMAUCA_1                            (0x00000200UL)
#define TMR6_PCNAR_CMADCA_POS                          (10U)
#define TMR6_PCNAR_CMADCA                              (0x00000C00UL)
#define TMR6_PCNAR_CMADCA_0                            (0x00000400UL)
#define TMR6_PCNAR_CMADCA_1                            (0x00000800UL)
#define TMR6_PCNAR_CMBUCA_POS                          (12U)
#define TMR6_PCNAR_CMBUCA                              (0x00003000UL)
#define TMR6_PCNAR_CMBUCA_0                            (0x00001000UL)
#define TMR6_PCNAR_CMBUCA_1                            (0x00002000UL)
#define TMR6_PCNAR_CMBDCA_POS                          (14U)
#define TMR6_PCNAR_CMBDCA                              (0x0000C000UL)
#define TMR6_PCNAR_CMBDCA_0                            (0x00004000UL)
#define TMR6_PCNAR_CMBDCA_1                            (0x00008000UL)
#define TMR6_PCNAR_FORCA_POS                           (16U)
#define TMR6_PCNAR_FORCA                               (0x00030000UL)
#define TMR6_PCNAR_FORCA_0                             (0x00010000UL)
#define TMR6_PCNAR_FORCA_1                             (0x00020000UL)
#define TMR6_PCNAR_EMBCA_POS                           (20U)
#define TMR6_PCNAR_EMBCA                               (0x00300000UL)
#define TMR6_PCNAR_EMBCA_0                             (0x00100000UL)
#define TMR6_PCNAR_EMBCA_1                             (0x00200000UL)
#define TMR6_PCNAR_EMBRA_POS                           (22U)
#define TMR6_PCNAR_EMBRA                               (0x00C00000UL)
#define TMR6_PCNAR_EMBRA_0                             (0x00400000UL)
#define TMR6_PCNAR_EMBRA_1                             (0x00800000UL)
#define TMR6_PCNAR_EMBSA_POS                           (24U)
#define TMR6_PCNAR_EMBSA                               (0x03000000UL)
#define TMR6_PCNAR_EMBSA_0                             (0x01000000UL)
#define TMR6_PCNAR_EMBSA_1                             (0x02000000UL)
#define TMR6_PCNAR_OUTENA_POS                          (28U)
#define TMR6_PCNAR_OUTENA                              (0x10000000UL)
#define TMR6_PCNAR_CAPMDA_POS                          (31U)
#define TMR6_PCNAR_CAPMDA                              (0x80000000UL)

/*  Bit definition for TMR6_PCNBR register  */
#define TMR6_PCNBR_STACB_POS                           (0U)
#define TMR6_PCNBR_STACB                               (0x00000003UL)
#define TMR6_PCNBR_STACB_0                             (0x00000001UL)
#define TMR6_PCNBR_STACB_1                             (0x00000002UL)
#define TMR6_PCNBR_STPCB_POS                           (2U)
#define TMR6_PCNBR_STPCB                               (0x0000000CUL)
#define TMR6_PCNBR_STPCB_0                             (0x00000004UL)
#define TMR6_PCNBR_STPCB_1                             (0x00000008UL)
#define TMR6_PCNBR_OVFCB_POS                           (4U)
#define TMR6_PCNBR_OVFCB                               (0x00000030UL)
#define TMR6_PCNBR_OVFCB_0                             (0x00000010UL)
#define TMR6_PCNBR_OVFCB_1                             (0x00000020UL)
#define TMR6_PCNBR_UDFCB_POS                           (6U)
#define TMR6_PCNBR_UDFCB                               (0x000000C0UL)
#define TMR6_PCNBR_UDFCB_0                             (0x00000040UL)
#define TMR6_PCNBR_UDFCB_1                             (0x00000080UL)
#define TMR6_PCNBR_CMAUCB_POS                          (8U)
#define TMR6_PCNBR_CMAUCB                              (0x00000300UL)
#define TMR6_PCNBR_CMAUCB_0                            (0x00000100UL)
#define TMR6_PCNBR_CMAUCB_1                            (0x00000200UL)
#define TMR6_PCNBR_CMADCB_POS                          (10U)
#define TMR6_PCNBR_CMADCB                              (0x00000C00UL)
#define TMR6_PCNBR_CMADCB_0                            (0x00000400UL)
#define TMR6_PCNBR_CMADCB_1                            (0x00000800UL)
#define TMR6_PCNBR_CMBUCB_POS                          (12U)
#define TMR6_PCNBR_CMBUCB                              (0x00003000UL)
#define TMR6_PCNBR_CMBUCB_0                            (0x00001000UL)
#define TMR6_PCNBR_CMBUCB_1                            (0x00002000UL)
#define TMR6_PCNBR_CMBDCB_POS                          (14U)
#define TMR6_PCNBR_CMBDCB                              (0x0000C000UL)
#define TMR6_PCNBR_CMBDCB_0                            (0x00004000UL)
#define TMR6_PCNBR_CMBDCB_1                            (0x00008000UL)
#define TMR6_PCNBR_FORCB_POS                           (16U)
#define TMR6_PCNBR_FORCB                               (0x00030000UL)
#define TMR6_PCNBR_FORCB_0                             (0x00010000UL)
#define TMR6_PCNBR_FORCB_1                             (0x00020000UL)
#define TMR6_PCNBR_EMBCB_POS                           (20U)
#define TMR6_PCNBR_EMBCB                               (0x00300000UL)
#define TMR6_PCNBR_EMBCB_0                             (0x00100000UL)
#define TMR6_PCNBR_EMBCB_1                             (0x00200000UL)
#define TMR6_PCNBR_EMBRB_POS                           (22U)
#define TMR6_PCNBR_EMBRB                               (0x00C00000UL)
#define TMR6_PCNBR_EMBRB_0                             (0x00400000UL)
#define TMR6_PCNBR_EMBRB_1                             (0x00800000UL)
#define TMR6_PCNBR_EMBSB_POS                           (24U)
#define TMR6_PCNBR_EMBSB                               (0x03000000UL)
#define TMR6_PCNBR_EMBSB_0                             (0x01000000UL)
#define TMR6_PCNBR_EMBSB_1                             (0x02000000UL)
#define TMR6_PCNBR_OUTENB_POS                          (28U)
#define TMR6_PCNBR_OUTENB                              (0x10000000UL)
#define TMR6_PCNBR_CAPMDB_POS                          (31U)
#define TMR6_PCNBR_CAPMDB                              (0x80000000UL)

/*  Bit definition for TMR6_FCNGR register  */
#define TMR6_FCNGR_NOFIENGA_POS                        (0U)
#define TMR6_FCNGR_NOFIENGA                            (0x00000001UL)
#define TMR6_FCNGR_NOFICKGA_POS                        (1U)
#define TMR6_FCNGR_NOFICKGA                            (0x00000006UL)
#define TMR6_FCNGR_NOFICKGA_0                          (0x00000002UL)
#define TMR6_FCNGR_NOFICKGA_1                          (0x00000004UL)
#define TMR6_FCNGR_NOFIENGB_POS                        (4U)
#define TMR6_FCNGR_NOFIENGB                            (0x00000010UL)
#define TMR6_FCNGR_NOFICKGB_POS                        (5U)
#define TMR6_FCNGR_NOFICKGB                            (0x00000060UL)
#define TMR6_FCNGR_NOFICKGB_0                          (0x00000020UL)
#define TMR6_FCNGR_NOFICKGB_1                          (0x00000040UL)

/*  Bit definition for TMR6_VPERR register  */
#define TMR6_VPERR_SPPERIA_POS                         (8U)
#define TMR6_VPERR_SPPERIA                             (0x00000100UL)
#define TMR6_VPERR_SPPERIB_POS                         (9U)
#define TMR6_VPERR_SPPERIB                             (0x00000200UL)
#define TMR6_VPERR_PCNTE_POS                           (16U)
#define TMR6_VPERR_PCNTE                               (0x00030000UL)
#define TMR6_VPERR_PCNTE_0                             (0x00010000UL)
#define TMR6_VPERR_PCNTE_1                             (0x00020000UL)
#define TMR6_VPERR_PCNTS_POS                           (18U)
#define TMR6_VPERR_PCNTS                               (0x001C0000UL)
#define TMR6_VPERR_PCNTS_0                             (0x00040000UL)
#define TMR6_VPERR_PCNTS_1                             (0x00080000UL)
#define TMR6_VPERR_PCNTS_2                             (0x00100000UL)

/*  Bit definition for TMR6_STFLR register  */
#define TMR6_STFLR_CMAF_POS                            (0U)
#define TMR6_STFLR_CMAF                                (0x00000001UL)
#define TMR6_STFLR_CMBF_POS                            (1U)
#define TMR6_STFLR_CMBF                                (0x00000002UL)
#define TMR6_STFLR_CMCF_POS                            (2U)
#define TMR6_STFLR_CMCF                                (0x00000004UL)
#define TMR6_STFLR_CMDF_POS                            (3U)
#define TMR6_STFLR_CMDF                                (0x00000008UL)
#define TMR6_STFLR_CMEF_POS                            (4U)
#define TMR6_STFLR_CMEF                                (0x00000010UL)
#define TMR6_STFLR_CMFF_POS                            (5U)
#define TMR6_STFLR_CMFF                                (0x00000020UL)
#define TMR6_STFLR_OVFF_POS                            (6U)
#define TMR6_STFLR_OVFF                                (0x00000040UL)
#define TMR6_STFLR_UDFF_POS                            (7U)
#define TMR6_STFLR_UDFF                                (0x00000080UL)
#define TMR6_STFLR_DTEF_POS                            (8U)
#define TMR6_STFLR_DTEF                                (0x00000100UL)
#define TMR6_STFLR_CMSAUF_POS                          (9U)
#define TMR6_STFLR_CMSAUF                              (0x00000200UL)
#define TMR6_STFLR_CMSADF_POS                          (10U)
#define TMR6_STFLR_CMSADF                              (0x00000400UL)
#define TMR6_STFLR_CMSBUF_POS                          (11U)
#define TMR6_STFLR_CMSBUF                              (0x00000800UL)
#define TMR6_STFLR_CMSBDF_POS                          (12U)
#define TMR6_STFLR_CMSBDF                              (0x00001000UL)
#define TMR6_STFLR_VPERNUM_POS                         (21U)
#define TMR6_STFLR_VPERNUM                             (0x00E00000UL)
#define TMR6_STFLR_VPERNUM_0                           (0x00200000UL)
#define TMR6_STFLR_VPERNUM_1                           (0x00400000UL)
#define TMR6_STFLR_VPERNUM_2                           (0x00800000UL)
#define TMR6_STFLR_DIRF_POS                            (31U)
#define TMR6_STFLR_DIRF                                (0x80000000UL)

/*  Bit definition for TMR6_HSTAR register  */
#define TMR6_HSTAR_HSTA0_POS                           (0U)
#define TMR6_HSTAR_HSTA0                               (0x00000001UL)
#define TMR6_HSTAR_HSTA1_POS                           (1U)
#define TMR6_HSTAR_HSTA1                               (0x00000002UL)
#define TMR6_HSTAR_HSTA2_POS                           (2U)
#define TMR6_HSTAR_HSTA2                               (0x00000004UL)
#define TMR6_HSTAR_HSTA3_POS                           (3U)
#define TMR6_HSTAR_HSTA3                               (0x00000008UL)
#define TMR6_HSTAR_STAS_POS                            (7U)
#define TMR6_HSTAR_STAS                                (0x00000080UL)
#define TMR6_HSTAR_HSTA8_POS                           (8U)
#define TMR6_HSTAR_HSTA8                               (0x00000100UL)
#define TMR6_HSTAR_HSTA9_POS                           (9U)
#define TMR6_HSTAR_HSTA9                               (0x00000200UL)
#define TMR6_HSTAR_HSTA10_POS                          (10U)
#define TMR6_HSTAR_HSTA10                              (0x00000400UL)
#define TMR6_HSTAR_HSTA11_POS                          (11U)
#define TMR6_HSTAR_HSTA11                              (0x00000800UL)
#define TMR6_HSTAR_HSTA16_POS                          (16U)
#define TMR6_HSTAR_HSTA16                              (0x00010000UL)
#define TMR6_HSTAR_HSTA17_POS                          (17U)
#define TMR6_HSTAR_HSTA17                              (0x00020000UL)
#define TMR6_HSTAR_HSTA18_POS                          (18U)
#define TMR6_HSTAR_HSTA18                              (0x00040000UL)
#define TMR6_HSTAR_HSTA19_POS                          (19U)
#define TMR6_HSTAR_HSTA19                              (0x00080000UL)
#define TMR6_HSTAR_HSTA20_POS                          (20U)
#define TMR6_HSTAR_HSTA20                              (0x00100000UL)
#define TMR6_HSTAR_HSTA21_POS                          (21U)
#define TMR6_HSTAR_HSTA21                              (0x00200000UL)
#define TMR6_HSTAR_HSTA22_POS                          (22U)
#define TMR6_HSTAR_HSTA22                              (0x00400000UL)
#define TMR6_HSTAR_HSTA23_POS                          (23U)
#define TMR6_HSTAR_HSTA23                              (0x00800000UL)

/*  Bit definition for TMR6_HSTPR register  */
#define TMR6_HSTPR_HSTP0_POS                           (0U)
#define TMR6_HSTPR_HSTP0                               (0x00000001UL)
#define TMR6_HSTPR_HSTP1_POS                           (1U)
#define TMR6_HSTPR_HSTP1                               (0x00000002UL)
#define TMR6_HSTPR_HSTP2_POS                           (2U)
#define TMR6_HSTPR_HSTP2                               (0x00000004UL)
#define TMR6_HSTPR_HSTP3_POS                           (3U)
#define TMR6_HSTPR_HSTP3                               (0x00000008UL)
#define TMR6_HSTPR_STPS_POS                            (7U)
#define TMR6_HSTPR_STPS                                (0x00000080UL)
#define TMR6_HSTPR_HSTP8_POS                           (8U)
#define TMR6_HSTPR_HSTP8                               (0x00000100UL)
#define TMR6_HSTPR_HSTP9_POS                           (9U)
#define TMR6_HSTPR_HSTP9                               (0x00000200UL)
#define TMR6_HSTPR_HSTP10_POS                          (10U)
#define TMR6_HSTPR_HSTP10                              (0x00000400UL)
#define TMR6_HSTPR_HSTP11_POS                          (11U)
#define TMR6_HSTPR_HSTP11                              (0x00000800UL)
#define TMR6_HSTPR_HSTP16_POS                          (16U)
#define TMR6_HSTPR_HSTP16                              (0x00010000UL)
#define TMR6_HSTPR_HSTP17_POS                          (17U)
#define TMR6_HSTPR_HSTP17                              (0x00020000UL)
#define TMR6_HSTPR_HSTP18_POS                          (18U)
#define TMR6_HSTPR_HSTP18                              (0x00040000UL)
#define TMR6_HSTPR_HSTP19_POS                          (19U)
#define TMR6_HSTPR_HSTP19                              (0x00080000UL)
#define TMR6_HSTPR_HSTP20_POS                          (20U)
#define TMR6_HSTPR_HSTP20                              (0x00100000UL)
#define TMR6_HSTPR_HSTP21_POS                          (21U)
#define TMR6_HSTPR_HSTP21                              (0x00200000UL)
#define TMR6_HSTPR_HSTP22_POS                          (22U)
#define TMR6_HSTPR_HSTP22                              (0x00400000UL)
#define TMR6_HSTPR_HSTP23_POS                          (23U)
#define TMR6_HSTPR_HSTP23                              (0x00800000UL)

/*  Bit definition for TMR6_HCLRR register  */
#define TMR6_HCLRR_HCLE0_POS                           (0U)
#define TMR6_HCLRR_HCLE0                               (0x00000001UL)
#define TMR6_HCLRR_HCLE1_POS                           (1U)
#define TMR6_HCLRR_HCLE1                               (0x00000002UL)
#define TMR6_HCLRR_HCLE2_POS                           (2U)
#define TMR6_HCLRR_HCLE2                               (0x00000004UL)
#define TMR6_HCLRR_HCLE3_POS                           (3U)
#define TMR6_HCLRR_HCLE3                               (0x00000008UL)
#define TMR6_HCLRR_CLES_POS                            (7U)
#define TMR6_HCLRR_CLES                                (0x00000080UL)
#define TMR6_HCLRR_HCLE8_POS                           (8U)
#define TMR6_HCLRR_HCLE8                               (0x00000100UL)
#define TMR6_HCLRR_HCLE9_POS                           (9U)
#define TMR6_HCLRR_HCLE9                               (0x00000200UL)
#define TMR6_HCLRR_HCLE10_POS                          (10U)
#define TMR6_HCLRR_HCLE10                              (0x00000400UL)
#define TMR6_HCLRR_HCLE11_POS                          (11U)
#define TMR6_HCLRR_HCLE11                              (0x00000800UL)
#define TMR6_HCLRR_HCLE16_POS                          (16U)
#define TMR6_HCLRR_HCLE16                              (0x00010000UL)
#define TMR6_HCLRR_HCLE17_POS                          (17U)
#define TMR6_HCLRR_HCLE17                              (0x00020000UL)
#define TMR6_HCLRR_HCLE18_POS                          (18U)
#define TMR6_HCLRR_HCLE18                              (0x00040000UL)
#define TMR6_HCLRR_HCLE19_POS                          (19U)
#define TMR6_HCLRR_HCLE19                              (0x00080000UL)
#define TMR6_HCLRR_HCLE20_POS                          (20U)
#define TMR6_HCLRR_HCLE20                              (0x00100000UL)
#define TMR6_HCLRR_HCLE21_POS                          (21U)
#define TMR6_HCLRR_HCLE21                              (0x00200000UL)
#define TMR6_HCLRR_HCLE22_POS                          (22U)
#define TMR6_HCLRR_HCLE22                              (0x00400000UL)
#define TMR6_HCLRR_HCLE23_POS                          (23U)
#define TMR6_HCLRR_HCLE23                              (0x00800000UL)

/*  Bit definition for TMR6_HUPDR register  */
#define TMR6_HUPDR_HUPD0_POS                           (0U)
#define TMR6_HUPDR_HUPD0                               (0x00000001UL)
#define TMR6_HUPDR_HUPD1_POS                           (1U)
#define TMR6_HUPDR_HUPD1                               (0x00000002UL)
#define TMR6_HUPDR_HUPD2_POS                           (2U)
#define TMR6_HUPDR_HUPD2                               (0x00000004UL)
#define TMR6_HUPDR_HUPD3_POS                           (3U)
#define TMR6_HUPDR_HUPD3                               (0x00000008UL)
#define TMR6_HUPDR_UPDS_POS                            (7U)
#define TMR6_HUPDR_UPDS                                (0x00000080UL)
#define TMR6_HUPDR_HUPD8_POS                           (8U)
#define TMR6_HUPDR_HUPD8                               (0x00000100UL)
#define TMR6_HUPDR_HUPD9_POS                           (9U)
#define TMR6_HUPDR_HUPD9                               (0x00000200UL)
#define TMR6_HUPDR_HUPD10_POS                          (10U)
#define TMR6_HUPDR_HUPD10                              (0x00000400UL)
#define TMR6_HUPDR_HUPD11_POS                          (11U)
#define TMR6_HUPDR_HUPD11                              (0x00000800UL)
#define TMR6_HUPDR_HUPD16_POS                          (16U)
#define TMR6_HUPDR_HUPD16                              (0x00010000UL)
#define TMR6_HUPDR_HUPD17_POS                          (17U)
#define TMR6_HUPDR_HUPD17                              (0x00020000UL)
#define TMR6_HUPDR_HUPD18_POS                          (18U)
#define TMR6_HUPDR_HUPD18                              (0x00040000UL)
#define TMR6_HUPDR_HUPD19_POS                          (19U)
#define TMR6_HUPDR_HUPD19                              (0x00080000UL)
#define TMR6_HUPDR_HUPD20_POS                          (20U)
#define TMR6_HUPDR_HUPD20                              (0x00100000UL)
#define TMR6_HUPDR_HUPD21_POS                          (21U)
#define TMR6_HUPDR_HUPD21                              (0x00200000UL)
#define TMR6_HUPDR_HUPD22_POS                          (22U)
#define TMR6_HUPDR_HUPD22                              (0x00400000UL)
#define TMR6_HUPDR_HUPD23_POS                          (23U)
#define TMR6_HUPDR_HUPD23                              (0x00800000UL)

/*  Bit definition for TMR6_HCPAR register  */
#define TMR6_HCPAR_HCPA0_POS                           (0U)
#define TMR6_HCPAR_HCPA0                               (0x00000001UL)
#define TMR6_HCPAR_HCPA1_POS                           (1U)
#define TMR6_HCPAR_HCPA1                               (0x00000002UL)
#define TMR6_HCPAR_HCPA2_POS                           (2U)
#define TMR6_HCPAR_HCPA2                               (0x00000004UL)
#define TMR6_HCPAR_HCPA3_POS                           (3U)
#define TMR6_HCPAR_HCPA3                               (0x00000008UL)
#define TMR6_HCPAR_HCPA8_POS                           (8U)
#define TMR6_HCPAR_HCPA8                               (0x00000100UL)
#define TMR6_HCPAR_HCPA9_POS                           (9U)
#define TMR6_HCPAR_HCPA9                               (0x00000200UL)
#define TMR6_HCPAR_HCPA10_POS                          (10U)
#define TMR6_HCPAR_HCPA10                              (0x00000400UL)
#define TMR6_HCPAR_HCPA11_POS                          (11U)
#define TMR6_HCPAR_HCPA11                              (0x00000800UL)
#define TMR6_HCPAR_HCPA16_POS                          (16U)
#define TMR6_HCPAR_HCPA16                              (0x00010000UL)
#define TMR6_HCPAR_HCPA17_POS                          (17U)
#define TMR6_HCPAR_HCPA17                              (0x00020000UL)
#define TMR6_HCPAR_HCPA18_POS                          (18U)
#define TMR6_HCPAR_HCPA18                              (0x00040000UL)
#define TMR6_HCPAR_HCPA19_POS                          (19U)
#define TMR6_HCPAR_HCPA19                              (0x00080000UL)
#define TMR6_HCPAR_HCPA20_POS                          (20U)
#define TMR6_HCPAR_HCPA20                              (0x00100000UL)
#define TMR6_HCPAR_HCPA21_POS                          (21U)
#define TMR6_HCPAR_HCPA21                              (0x00200000UL)
#define TMR6_HCPAR_HCPA22_POS                          (22U)
#define TMR6_HCPAR_HCPA22                              (0x00400000UL)
#define TMR6_HCPAR_HCPA23_POS                          (23U)
#define TMR6_HCPAR_HCPA23                              (0x00800000UL)

/*  Bit definition for TMR6_HCPBR register  */
#define TMR6_HCPBR_HCPB0_POS                           (0U)
#define TMR6_HCPBR_HCPB0                               (0x00000001UL)
#define TMR6_HCPBR_HCPB1_POS                           (1U)
#define TMR6_HCPBR_HCPB1                               (0x00000002UL)
#define TMR6_HCPBR_HCPB2_POS                           (2U)
#define TMR6_HCPBR_HCPB2                               (0x00000004UL)
#define TMR6_HCPBR_HCPB3_POS                           (3U)
#define TMR6_HCPBR_HCPB3                               (0x00000008UL)
#define TMR6_HCPBR_HCPB8_POS                           (8U)
#define TMR6_HCPBR_HCPB8                               (0x00000100UL)
#define TMR6_HCPBR_HCPB9_POS                           (9U)
#define TMR6_HCPBR_HCPB9                               (0x00000200UL)
#define TMR6_HCPBR_HCPB10_POS                          (10U)
#define TMR6_HCPBR_HCPB10                              (0x00000400UL)
#define TMR6_HCPBR_HCPB11_POS                          (11U)
#define TMR6_HCPBR_HCPB11                              (0x00000800UL)
#define TMR6_HCPBR_HCPB16_POS                          (16U)
#define TMR6_HCPBR_HCPB16                              (0x00010000UL)
#define TMR6_HCPBR_HCPB17_POS                          (17U)
#define TMR6_HCPBR_HCPB17                              (0x00020000UL)
#define TMR6_HCPBR_HCPB18_POS                          (18U)
#define TMR6_HCPBR_HCPB18                              (0x00040000UL)
#define TMR6_HCPBR_HCPB19_POS                          (19U)
#define TMR6_HCPBR_HCPB19                              (0x00080000UL)
#define TMR6_HCPBR_HCPB20_POS                          (20U)
#define TMR6_HCPBR_HCPB20                              (0x00100000UL)
#define TMR6_HCPBR_HCPB21_POS                          (21U)
#define TMR6_HCPBR_HCPB21                              (0x00200000UL)
#define TMR6_HCPBR_HCPB22_POS                          (22U)
#define TMR6_HCPBR_HCPB22                              (0x00400000UL)
#define TMR6_HCPBR_HCPB23_POS                          (23U)
#define TMR6_HCPBR_HCPB23                              (0x00800000UL)

/*  Bit definition for TMR6_HCUPR register  */
#define TMR6_HCUPR_HCUP0_POS                           (0U)
#define TMR6_HCUPR_HCUP0                               (0x00000001UL)
#define TMR6_HCUPR_HCUP1_POS                           (1U)
#define TMR6_HCUPR_HCUP1                               (0x00000002UL)
#define TMR6_HCUPR_HCUP2_POS                           (2U)
#define TMR6_HCUPR_HCUP2                               (0x00000004UL)
#define TMR6_HCUPR_HCUP3_POS                           (3U)
#define TMR6_HCUPR_HCUP3                               (0x00000008UL)
#define TMR6_HCUPR_HCUP4_POS                           (4U)
#define TMR6_HCUPR_HCUP4                               (0x00000010UL)
#define TMR6_HCUPR_HCUP5_POS                           (5U)
#define TMR6_HCUPR_HCUP5                               (0x00000020UL)
#define TMR6_HCUPR_HCUP6_POS                           (6U)
#define TMR6_HCUPR_HCUP6                               (0x00000040UL)
#define TMR6_HCUPR_HCUP7_POS                           (7U)
#define TMR6_HCUPR_HCUP7                               (0x00000080UL)
#define TMR6_HCUPR_HCUP8_POS                           (8U)
#define TMR6_HCUPR_HCUP8                               (0x00000100UL)
#define TMR6_HCUPR_HCUP9_POS                           (9U)
#define TMR6_HCUPR_HCUP9                               (0x00000200UL)
#define TMR6_HCUPR_HCUP10_POS                          (10U)
#define TMR6_HCUPR_HCUP10                              (0x00000400UL)
#define TMR6_HCUPR_HCUP11_POS                          (11U)
#define TMR6_HCUPR_HCUP11                              (0x00000800UL)
#define TMR6_HCUPR_HCUP16_POS                          (16U)
#define TMR6_HCUPR_HCUP16                              (0x00010000UL)
#define TMR6_HCUPR_HCUP17_POS                          (17U)
#define TMR6_HCUPR_HCUP17                              (0x00020000UL)
#define TMR6_HCUPR_HCUP18_POS                          (18U)
#define TMR6_HCUPR_HCUP18                              (0x00040000UL)
#define TMR6_HCUPR_HCUP19_POS                          (19U)
#define TMR6_HCUPR_HCUP19                              (0x00080000UL)
#define TMR6_HCUPR_HCUP20_POS                          (20U)
#define TMR6_HCUPR_HCUP20                              (0x00100000UL)
#define TMR6_HCUPR_HCUP21_POS                          (21U)
#define TMR6_HCUPR_HCUP21                              (0x00200000UL)
#define TMR6_HCUPR_HCUP22_POS                          (22U)
#define TMR6_HCUPR_HCUP22                              (0x00400000UL)
#define TMR6_HCUPR_HCUP23_POS                          (23U)
#define TMR6_HCUPR_HCUP23                              (0x00800000UL)

/*  Bit definition for TMR6_HCDOR register  */
#define TMR6_HCDOR_HCDO0_POS                           (0U)
#define TMR6_HCDOR_HCDO0                               (0x00000001UL)
#define TMR6_HCDOR_HCDO1_POS                           (1U)
#define TMR6_HCDOR_HCDO1                               (0x00000002UL)
#define TMR6_HCDOR_HCDO2_POS                           (2U)
#define TMR6_HCDOR_HCDO2                               (0x00000004UL)
#define TMR6_HCDOR_HCDO3_POS                           (3U)
#define TMR6_HCDOR_HCDO3                               (0x00000008UL)
#define TMR6_HCDOR_HCDO4_POS                           (4U)
#define TMR6_HCDOR_HCDO4                               (0x00000010UL)
#define TMR6_HCDOR_HCDO5_POS                           (5U)
#define TMR6_HCDOR_HCDO5                               (0x00000020UL)
#define TMR6_HCDOR_HCDO6_POS                           (6U)
#define TMR6_HCDOR_HCDO6                               (0x00000040UL)
#define TMR6_HCDOR_HCDO7_POS                           (7U)
#define TMR6_HCDOR_HCDO7                               (0x00000080UL)
#define TMR6_HCDOR_HCDO8_POS                           (8U)
#define TMR6_HCDOR_HCDO8                               (0x00000100UL)
#define TMR6_HCDOR_HCDO9_POS                           (9U)
#define TMR6_HCDOR_HCDO9                               (0x00000200UL)
#define TMR6_HCDOR_HCDO10_POS                          (10U)
#define TMR6_HCDOR_HCDO10                              (0x00000400UL)
#define TMR6_HCDOR_HCDO11_POS                          (11U)
#define TMR6_HCDOR_HCDO11                              (0x00000800UL)
#define TMR6_HCDOR_HCDO16_POS                          (16U)
#define TMR6_HCDOR_HCDO16                              (0x00010000UL)
#define TMR6_HCDOR_HCDO17_POS                          (17U)
#define TMR6_HCDOR_HCDO17                              (0x00020000UL)
#define TMR6_HCDOR_HCDO18_POS                          (18U)
#define TMR6_HCDOR_HCDO18                              (0x00040000UL)
#define TMR6_HCDOR_HCDO19_POS                          (19U)
#define TMR6_HCDOR_HCDO19                              (0x00080000UL)
#define TMR6_HCDOR_HCDO20_POS                          (20U)
#define TMR6_HCDOR_HCDO20                              (0x00100000UL)
#define TMR6_HCDOR_HCDO21_POS                          (21U)
#define TMR6_HCDOR_HCDO21                              (0x00200000UL)
#define TMR6_HCDOR_HCDO22_POS                          (22U)
#define TMR6_HCDOR_HCDO22                              (0x00400000UL)
#define TMR6_HCDOR_HCDO23_POS                          (23U)
#define TMR6_HCDOR_HCDO23                              (0x00800000UL)

/*******************************************************************************
                Bit definition for Peripheral TMR6CR
*******************************************************************************/
/*  Bit definition for TMR6CR_FCNTR register  */
#define TMR6CR_FCNTR_NOFIENTA_POS                      (0U)
#define TMR6CR_FCNTR_NOFIENTA                          (0x00000001UL)
#define TMR6CR_FCNTR_NOFICKTA_POS                      (1U)
#define TMR6CR_FCNTR_NOFICKTA                          (0x00000006UL)
#define TMR6CR_FCNTR_NOFICKTA_0                        (0x00000002UL)
#define TMR6CR_FCNTR_NOFICKTA_1                        (0x00000004UL)
#define TMR6CR_FCNTR_NOFIENTB_POS                      (4U)
#define TMR6CR_FCNTR_NOFIENTB                          (0x00000010UL)
#define TMR6CR_FCNTR_NOFICKTB_POS                      (5U)
#define TMR6CR_FCNTR_NOFICKTB                          (0x00000060UL)
#define TMR6CR_FCNTR_NOFICKTB_0                        (0x00000020UL)
#define TMR6CR_FCNTR_NOFICKTB_1                        (0x00000040UL)
#define TMR6CR_FCNTR_NOFIENTC_POS                      (8U)
#define TMR6CR_FCNTR_NOFIENTC                          (0x00000100UL)
#define TMR6CR_FCNTR_NOFICKTC_POS                      (9U)
#define TMR6CR_FCNTR_NOFICKTC                          (0x00000600UL)
#define TMR6CR_FCNTR_NOFICKTC_0                        (0x00000200UL)
#define TMR6CR_FCNTR_NOFICKTC_1                        (0x00000400UL)
#define TMR6CR_FCNTR_NOFIENTD_POS                      (12U)
#define TMR6CR_FCNTR_NOFIENTD                          (0x00001000UL)
#define TMR6CR_FCNTR_NOFICKTD_POS                      (13U)
#define TMR6CR_FCNTR_NOFICKTD                          (0x00006000UL)
#define TMR6CR_FCNTR_NOFICKTD_0                        (0x00002000UL)
#define TMR6CR_FCNTR_NOFICKTD_1                        (0x00004000UL)

/*  Bit definition for TMR6CR_SSTAR register  */
#define TMR6CR_SSTAR_SSTA1_POS                         (0U)
#define TMR6CR_SSTAR_SSTA1                             (0x00000001UL)
#define TMR6CR_SSTAR_SSTA2_POS                         (1U)
#define TMR6CR_SSTAR_SSTA2                             (0x00000002UL)
#define TMR6CR_SSTAR_SSTA3_POS                         (2U)
#define TMR6CR_SSTAR_SSTA3                             (0x00000004UL)
#define TMR6CR_SSTAR_SSTA4_POS                         (3U)
#define TMR6CR_SSTAR_SSTA4                             (0x00000008UL)
#define TMR6CR_SSTAR_SSTA5_POS                         (4U)
#define TMR6CR_SSTAR_SSTA5                             (0x00000010UL)
#define TMR6CR_SSTAR_SSTA6_POS                         (5U)
#define TMR6CR_SSTAR_SSTA6                             (0x00000020UL)
#define TMR6CR_SSTAR_SSTA7_POS                         (6U)
#define TMR6CR_SSTAR_SSTA7                             (0x00000040UL)
#define TMR6CR_SSTAR_SSTA8_POS                         (7U)
#define TMR6CR_SSTAR_SSTA8                             (0x00000080UL)

/*  Bit definition for TMR6CR_SSTPR register  */
#define TMR6CR_SSTPR_SSTP1_POS                         (0U)
#define TMR6CR_SSTPR_SSTP1                             (0x00000001UL)
#define TMR6CR_SSTPR_SSTP2_POS                         (1U)
#define TMR6CR_SSTPR_SSTP2                             (0x00000002UL)
#define TMR6CR_SSTPR_SSTP3_POS                         (2U)
#define TMR6CR_SSTPR_SSTP3                             (0x00000004UL)
#define TMR6CR_SSTPR_SSTP4_POS                         (3U)
#define TMR6CR_SSTPR_SSTP4                             (0x00000008UL)
#define TMR6CR_SSTPR_SSTP5_POS                         (4U)
#define TMR6CR_SSTPR_SSTP5                             (0x00000010UL)
#define TMR6CR_SSTPR_SSTP6_POS                         (5U)
#define TMR6CR_SSTPR_SSTP6                             (0x00000020UL)
#define TMR6CR_SSTPR_SSTP7_POS                         (6U)
#define TMR6CR_SSTPR_SSTP7                             (0x00000040UL)
#define TMR6CR_SSTPR_SSTP8_POS                         (7U)
#define TMR6CR_SSTPR_SSTP8                             (0x00000080UL)

/*  Bit definition for TMR6CR_SCLRR register  */
#define TMR6CR_SCLRR_SCLE1_POS                         (0U)
#define TMR6CR_SCLRR_SCLE1                             (0x00000001UL)
#define TMR6CR_SCLRR_SCLE2_POS                         (1U)
#define TMR6CR_SCLRR_SCLE2                             (0x00000002UL)
#define TMR6CR_SCLRR_SCLE3_POS                         (2U)
#define TMR6CR_SCLRR_SCLE3                             (0x00000004UL)
#define TMR6CR_SCLRR_SCLE4_POS                         (3U)
#define TMR6CR_SCLRR_SCLE4                             (0x00000008UL)
#define TMR6CR_SCLRR_SCLE5_POS                         (4U)
#define TMR6CR_SCLRR_SCLE5                             (0x00000010UL)
#define TMR6CR_SCLRR_SCLE6_POS                         (5U)
#define TMR6CR_SCLRR_SCLE6                             (0x00000020UL)
#define TMR6CR_SCLRR_SCLE7_POS                         (6U)
#define TMR6CR_SCLRR_SCLE7                             (0x00000040UL)
#define TMR6CR_SCLRR_SCLE8_POS                         (7U)
#define TMR6CR_SCLRR_SCLE8                             (0x00000080UL)

/*  Bit definition for TMR6CR_SUPDR register  */
#define TMR6CR_SUPDR_SUPD1_POS                         (0U)
#define TMR6CR_SUPDR_SUPD1                             (0x00000001UL)
#define TMR6CR_SUPDR_SUPD2_POS                         (1U)
#define TMR6CR_SUPDR_SUPD2                             (0x00000002UL)
#define TMR6CR_SUPDR_SUPD3_POS                         (2U)
#define TMR6CR_SUPDR_SUPD3                             (0x00000004UL)
#define TMR6CR_SUPDR_SUPD4_POS                         (3U)
#define TMR6CR_SUPDR_SUPD4                             (0x00000008UL)
#define TMR6CR_SUPDR_SUPD5_POS                         (4U)
#define TMR6CR_SUPDR_SUPD5                             (0x00000010UL)
#define TMR6CR_SUPDR_SUPD6_POS                         (5U)
#define TMR6CR_SUPDR_SUPD6                             (0x00000020UL)
#define TMR6CR_SUPDR_SUPD7_POS                         (6U)
#define TMR6CR_SUPDR_SUPD7                             (0x00000040UL)
#define TMR6CR_SUPDR_SUPD8_POS                         (7U)
#define TMR6CR_SUPDR_SUPD8                             (0x00000080UL)

/*******************************************************************************
                Bit definition for Peripheral TMRA
*******************************************************************************/
/*  Bit definition for TMRA_CNTER register  */
#define TMRA_CNTER_CNT                                 (0xFFFFU)

/*  Bit definition for TMRA_PERAR register  */
#define TMRA_PERAR_PER                                 (0xFFFFU)

/*  Bit definition for TMRA_CMPAR register  */
#define TMRA_CMPAR_CMP                                 (0xFFFFU)

/*  Bit definition for TMRA_BCSTRL register  */
#define TMRA_BCSTRL_START_POS                          (0U)
#define TMRA_BCSTRL_START                              (0x01U)
#define TMRA_BCSTRL_DIR_POS                            (1U)
#define TMRA_BCSTRL_DIR                                (0x02U)
#define TMRA_BCSTRL_MODE_POS                           (2U)
#define TMRA_BCSTRL_MODE                               (0x04U)
#define TMRA_BCSTRL_SYNST_POS                          (3U)
#define TMRA_BCSTRL_SYNST                              (0x08U)
#define TMRA_BCSTRL_CKDIV_POS                          (4U)
#define TMRA_BCSTRL_CKDIV                              (0xF0U)

/*  Bit definition for TMRA_BCSTRH register  */
#define TMRA_BCSTRH_OVSTP_POS                          (0U)
#define TMRA_BCSTRH_OVSTP                              (0x01U)
#define TMRA_BCSTRH_ITENOVF_POS                        (4U)
#define TMRA_BCSTRH_ITENOVF                            (0x10U)
#define TMRA_BCSTRH_ITENUDF_POS                        (5U)
#define TMRA_BCSTRH_ITENUDF                            (0x20U)
#define TMRA_BCSTRH_OVFF_POS                           (6U)
#define TMRA_BCSTRH_OVFF                               (0x40U)
#define TMRA_BCSTRH_UDFF_POS                           (7U)
#define TMRA_BCSTRH_UDFF                               (0x80U)

/*  Bit definition for TMRA_HCONR register  */
#define TMRA_HCONR_HSTA0_POS                           (0U)
#define TMRA_HCONR_HSTA0                               (0x0001U)
#define TMRA_HCONR_HSTA1_POS                           (1U)
#define TMRA_HCONR_HSTA1                               (0x0002U)
#define TMRA_HCONR_HSTA2_POS                           (2U)
#define TMRA_HCONR_HSTA2                               (0x0004U)
#define TMRA_HCONR_HSTP0_POS                           (4U)
#define TMRA_HCONR_HSTP0                               (0x0010U)
#define TMRA_HCONR_HSTP1_POS                           (5U)
#define TMRA_HCONR_HSTP1                               (0x0020U)
#define TMRA_HCONR_HSTP2_POS                           (6U)
#define TMRA_HCONR_HSTP2                               (0x0040U)
#define TMRA_HCONR_HCLE0_POS                           (8U)
#define TMRA_HCONR_HCLE0                               (0x0100U)
#define TMRA_HCONR_HCLE1_POS                           (9U)
#define TMRA_HCONR_HCLE1                               (0x0200U)
#define TMRA_HCONR_HCLE2_POS                           (10U)
#define TMRA_HCONR_HCLE2                               (0x0400U)
#define TMRA_HCONR_HCLE3_POS                           (12U)
#define TMRA_HCONR_HCLE3                               (0x1000U)
#define TMRA_HCONR_HCLE4_POS                           (13U)
#define TMRA_HCONR_HCLE4                               (0x2000U)
#define TMRA_HCONR_HCLE5_POS                           (14U)
#define TMRA_HCONR_HCLE5                               (0x4000U)
#define TMRA_HCONR_HCLE6_POS                           (15U)
#define TMRA_HCONR_HCLE6                               (0x8000U)

/*  Bit definition for TMRA_HCUPR register  */
#define TMRA_HCUPR_HCUP0_POS                           (0U)
#define TMRA_HCUPR_HCUP0                               (0x0001U)
#define TMRA_HCUPR_HCUP1_POS                           (1U)
#define TMRA_HCUPR_HCUP1                               (0x0002U)
#define TMRA_HCUPR_HCUP2_POS                           (2U)
#define TMRA_HCUPR_HCUP2                               (0x0004U)
#define TMRA_HCUPR_HCUP3_POS                           (3U)
#define TMRA_HCUPR_HCUP3                               (0x0008U)
#define TMRA_HCUPR_HCUP4_POS                           (4U)
#define TMRA_HCUPR_HCUP4                               (0x0010U)
#define TMRA_HCUPR_HCUP5_POS                           (5U)
#define TMRA_HCUPR_HCUP5                               (0x0020U)
#define TMRA_HCUPR_HCUP6_POS                           (6U)
#define TMRA_HCUPR_HCUP6                               (0x0040U)
#define TMRA_HCUPR_HCUP7_POS                           (7U)
#define TMRA_HCUPR_HCUP7                               (0x0080U)
#define TMRA_HCUPR_HCUP8_POS                           (8U)
#define TMRA_HCUPR_HCUP8                               (0x0100U)
#define TMRA_HCUPR_HCUP9_POS                           (9U)
#define TMRA_HCUPR_HCUP9                               (0x0200U)
#define TMRA_HCUPR_HCUP10_POS                          (10U)
#define TMRA_HCUPR_HCUP10                              (0x0400U)
#define TMRA_HCUPR_HCUP11_POS                          (11U)
#define TMRA_HCUPR_HCUP11                              (0x0800U)
#define TMRA_HCUPR_HCUP12_POS                          (12U)
#define TMRA_HCUPR_HCUP12                              (0x1000U)

/*  Bit definition for TMRA_HCDOR register  */
#define TMRA_HCDOR_HCDO0_POS                           (0U)
#define TMRA_HCDOR_HCDO0                               (0x0001U)
#define TMRA_HCDOR_HCDO1_POS                           (1U)
#define TMRA_HCDOR_HCDO1                               (0x0002U)
#define TMRA_HCDOR_HCDO2_POS                           (2U)
#define TMRA_HCDOR_HCDO2                               (0x0004U)
#define TMRA_HCDOR_HCDO3_POS                           (3U)
#define TMRA_HCDOR_HCDO3                               (0x0008U)
#define TMRA_HCDOR_HCDO4_POS                           (4U)
#define TMRA_HCDOR_HCDO4                               (0x0010U)
#define TMRA_HCDOR_HCDO5_POS                           (5U)
#define TMRA_HCDOR_HCDO5                               (0x0020U)
#define TMRA_HCDOR_HCDO6_POS                           (6U)
#define TMRA_HCDOR_HCDO6                               (0x0040U)
#define TMRA_HCDOR_HCDO7_POS                           (7U)
#define TMRA_HCDOR_HCDO7                               (0x0080U)
#define TMRA_HCDOR_HCDO8_POS                           (8U)
#define TMRA_HCDOR_HCDO8                               (0x0100U)
#define TMRA_HCDOR_HCDO9_POS                           (9U)
#define TMRA_HCDOR_HCDO9                               (0x0200U)
#define TMRA_HCDOR_HCDO10_POS                          (10U)
#define TMRA_HCDOR_HCDO10                              (0x0400U)
#define TMRA_HCDOR_HCDO11_POS                          (11U)
#define TMRA_HCDOR_HCDO11                              (0x0800U)
#define TMRA_HCDOR_HCDO12_POS                          (12U)
#define TMRA_HCDOR_HCDO12                              (0x1000U)

/*  Bit definition for TMRA_ICONR register  */
#define TMRA_ICONR_ITEN1_POS                           (0U)
#define TMRA_ICONR_ITEN1                               (0x0001U)
#define TMRA_ICONR_ITEN2_POS                           (1U)
#define TMRA_ICONR_ITEN2                               (0x0002U)
#define TMRA_ICONR_ITEN3_POS                           (2U)
#define TMRA_ICONR_ITEN3                               (0x0004U)
#define TMRA_ICONR_ITEN4_POS                           (3U)
#define TMRA_ICONR_ITEN4                               (0x0008U)

/*  Bit definition for TMRA_ECONR register  */
#define TMRA_ECONR_ETEN1_POS                           (0U)
#define TMRA_ECONR_ETEN1                               (0x0001U)
#define TMRA_ECONR_ETEN2_POS                           (1U)
#define TMRA_ECONR_ETEN2                               (0x0002U)
#define TMRA_ECONR_ETEN3_POS                           (2U)
#define TMRA_ECONR_ETEN3                               (0x0004U)
#define TMRA_ECONR_ETEN4_POS                           (3U)
#define TMRA_ECONR_ETEN4                               (0x0008U)

/*  Bit definition for TMRA_FCONR register  */
#define TMRA_FCONR_NOFIENTG_POS                        (0U)
#define TMRA_FCONR_NOFIENTG                            (0x0001U)
#define TMRA_FCONR_NOFICKTG_POS                        (1U)
#define TMRA_FCONR_NOFICKTG                            (0x0006U)
#define TMRA_FCONR_NOFIENCA_POS                        (8U)
#define TMRA_FCONR_NOFIENCA                            (0x0100U)
#define TMRA_FCONR_NOFICKCA_POS                        (9U)
#define TMRA_FCONR_NOFICKCA                            (0x0600U)
#define TMRA_FCONR_NOFIENCB_POS                        (12U)
#define TMRA_FCONR_NOFIENCB                            (0x1000U)
#define TMRA_FCONR_NOFICKCB_POS                        (13U)
#define TMRA_FCONR_NOFICKCB                            (0x6000U)

/*  Bit definition for TMRA_STFLR register  */
#define TMRA_STFLR_CMPF1_POS                           (0U)
#define TMRA_STFLR_CMPF1                               (0x0001U)
#define TMRA_STFLR_CMPF2_POS                           (1U)
#define TMRA_STFLR_CMPF2                               (0x0002U)
#define TMRA_STFLR_CMPF3_POS                           (2U)
#define TMRA_STFLR_CMPF3                               (0x0004U)
#define TMRA_STFLR_CMPF4_POS                           (3U)
#define TMRA_STFLR_CMPF4                               (0x0008U)

/*  Bit definition for TMRA_BCONR register  */
#define TMRA_BCONR_BEN_POS                             (0U)
#define TMRA_BCONR_BEN                                 (0x0001U)
#define TMRA_BCONR_BSE0_POS                            (1U)
#define TMRA_BCONR_BSE0                                (0x0002U)
#define TMRA_BCONR_BSE1_POS                            (2U)
#define TMRA_BCONR_BSE1                                (0x0004U)

/*  Bit definition for TMRA_CCONR register  */
#define TMRA_CCONR_CAPMD_POS                           (0U)
#define TMRA_CCONR_CAPMD                               (0x0001U)
#define TMRA_CCONR_HICP0_POS                           (4U)
#define TMRA_CCONR_HICP0                               (0x0010U)
#define TMRA_CCONR_HICP1_POS                           (5U)
#define TMRA_CCONR_HICP1                               (0x0020U)
#define TMRA_CCONR_HICP2_POS                           (6U)
#define TMRA_CCONR_HICP2                               (0x0040U)
#define TMRA_CCONR_HICP3_POS                           (8U)
#define TMRA_CCONR_HICP3                               (0x0100U)
#define TMRA_CCONR_HICP4_POS                           (9U)
#define TMRA_CCONR_HICP4                               (0x0200U)
#define TMRA_CCONR_NOFIENCP_POS                        (12U)
#define TMRA_CCONR_NOFIENCP                            (0x1000U)
#define TMRA_CCONR_NOFICKCP_POS                        (13U)
#define TMRA_CCONR_NOFICKCP                            (0x6000U)

/*  Bit definition for TMRA_PCONR register  */
#define TMRA_PCONR_STAC_POS                            (0U)
#define TMRA_PCONR_STAC                                (0x0003U)
#define TMRA_PCONR_STAC_0                              (0x0001U)
#define TMRA_PCONR_STAC_1                              (0x0002U)
#define TMRA_PCONR_STPC_POS                            (2U)
#define TMRA_PCONR_STPC                                (0x000CU)
#define TMRA_PCONR_STPC_0                              (0x0004U)
#define TMRA_PCONR_STPC_1                              (0x0008U)
#define TMRA_PCONR_CMPC_POS                            (4U)
#define TMRA_PCONR_CMPC                                (0x0030U)
#define TMRA_PCONR_CMPC_0                              (0x0010U)
#define TMRA_PCONR_CMPC_1                              (0x0020U)
#define TMRA_PCONR_PERC_POS                            (6U)
#define TMRA_PCONR_PERC                                (0x00C0U)
#define TMRA_PCONR_PERC_0                              (0x0040U)
#define TMRA_PCONR_PERC_1                              (0x0080U)
#define TMRA_PCONR_FORC_POS                            (8U)
#define TMRA_PCONR_FORC                                (0x0300U)
#define TMRA_PCONR_FORC_0                              (0x0100U)
#define TMRA_PCONR_FORC_1                              (0x0200U)
#define TMRA_PCONR_OUTEN_POS                           (12U)
#define TMRA_PCONR_OUTEN                               (0x1000U)

/*******************************************************************************
                Bit definition for Peripheral TRNG
*******************************************************************************/
/*  Bit definition for TRNG_CR register  */
#define TRNG_CR_EN_POS                                 (0U)
#define TRNG_CR_EN                                     (0x00000001UL)
#define TRNG_CR_RUN_POS                                (1U)
#define TRNG_CR_RUN                                    (0x00000002UL)

/*  Bit definition for TRNG_MR register  */
#define TRNG_MR_LOAD_POS                               (0U)
#define TRNG_MR_LOAD                                   (0x00000001UL)
#define TRNG_MR_CNT_POS                                (2U)
#define TRNG_MR_CNT                                    (0x0000001CUL)

/*  Bit definition for TRNG_DR0 register  */
#define TRNG_DR0                                       (0xFFFFFFFFUL)

/*  Bit definition for TRNG_DR1 register  */
#define TRNG_DR1                                       (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral USART
*******************************************************************************/
/*  Bit definition for USART_SR register  */
#define USART_SR_PE_POS                                (0U)
#define USART_SR_PE                                    (0x00000001UL)
#define USART_SR_FE_POS                                (1U)
#define USART_SR_FE                                    (0x00000002UL)
#define USART_SR_ORE_POS                               (3U)
#define USART_SR_ORE                                   (0x00000008UL)
#define USART_SR_BE_POS                                (4U)
#define USART_SR_BE                                    (0x00000010UL)
#define USART_SR_RXNE_POS                              (5U)
#define USART_SR_RXNE                                  (0x00000020UL)
#define USART_SR_TC_POS                                (6U)
#define USART_SR_TC                                    (0x00000040UL)
#define USART_SR_TXE_POS                               (7U)
#define USART_SR_TXE                                   (0x00000080UL)
#define USART_SR_RTOF_POS                              (8U)
#define USART_SR_RTOF                                  (0x00000100UL)
#define USART_SR_WKUP_POS                              (9U)
#define USART_SR_WKUP                                  (0x00000200UL)
#define USART_SR_LBD_POS                               (10U)
#define USART_SR_LBD                                   (0x00000400UL)
#define USART_SR_MPB_POS                               (16U)
#define USART_SR_MPB                                   (0x00010000UL)

/*  Bit definition for USART_TDR register  */
#define USART_TDR_TDR_POS                              (0U)
#define USART_TDR_TDR                                  (0x01FFU)
#define USART_TDR_MPID_POS                             (9U)
#define USART_TDR_MPID                                 (0x0200U)

/*  Bit definition for USART_RDR register  */
#define USART_RDR_RDR                                  (0x01FFU)

/*  Bit definition for USART_BRR register  */
#define USART_BRR_DIV_FRACTION_POS                     (0U)
#define USART_BRR_DIV_FRACTION                         (0x0000007FUL)
#define USART_BRR_DIV_INTEGER_POS                      (8U)
#define USART_BRR_DIV_INTEGER                          (0x0000FF00UL)

/*  Bit definition for USART_CR1 register  */
#define USART_CR1_RTOE_POS                             (0U)
#define USART_CR1_RTOE                                 (0x00000001UL)
#define USART_CR1_RTOIE_POS                            (1U)
#define USART_CR1_RTOIE                                (0x00000002UL)
#define USART_CR1_RE_POS                               (2U)
#define USART_CR1_RE                                   (0x00000004UL)
#define USART_CR1_TE_POS                               (3U)
#define USART_CR1_TE                                   (0x00000008UL)
#define USART_CR1_SLME_POS                             (4U)
#define USART_CR1_SLME                                 (0x00000010UL)
#define USART_CR1_RIE_POS                              (5U)
#define USART_CR1_RIE                                  (0x00000020UL)
#define USART_CR1_TCIE_POS                             (6U)
#define USART_CR1_TCIE                                 (0x00000040UL)
#define USART_CR1_TXEIE_POS                            (7U)
#define USART_CR1_TXEIE                                (0x00000080UL)
#define USART_CR1_PS_POS                               (9U)
#define USART_CR1_PS                                   (0x00000200UL)
#define USART_CR1_PCE_POS                              (10U)
#define USART_CR1_PCE                                  (0x00000400UL)
#define USART_CR1_M_POS                                (12U)
#define USART_CR1_M                                    (0x00001000UL)
#define USART_CR1_OVER8_POS                            (15U)
#define USART_CR1_OVER8                                (0x00008000UL)
#define USART_CR1_CPE_POS                              (16U)
#define USART_CR1_CPE                                  (0x00010000UL)
#define USART_CR1_CFE_POS                              (17U)
#define USART_CR1_CFE                                  (0x00020000UL)
#define USART_CR1_CORE_POS                             (19U)
#define USART_CR1_CORE                                 (0x00080000UL)
#define USART_CR1_CRTOF_POS                            (20U)
#define USART_CR1_CRTOF                                (0x00100000UL)
#define USART_CR1_CBE_POS                              (21U)
#define USART_CR1_CBE                                  (0x00200000UL)
#define USART_CR1_CWKUP_POS                            (22U)
#define USART_CR1_CWKUP                                (0x00400000UL)
#define USART_CR1_CLBD_POS                             (23U)
#define USART_CR1_CLBD                                 (0x00800000UL)
#define USART_CR1_MS_POS                               (24U)
#define USART_CR1_MS                                   (0x01000000UL)
#define USART_CR1_ML_POS                               (28U)
#define USART_CR1_ML                                   (0x10000000UL)
#define USART_CR1_FBME_POS                             (29U)
#define USART_CR1_FBME                                 (0x20000000UL)
#define USART_CR1_NFE_POS                              (30U)
#define USART_CR1_NFE                                  (0x40000000UL)
#define USART_CR1_SBS_POS                              (31U)
#define USART_CR1_SBS                                  (0x80000000UL)

/*  Bit definition for USART_CR2 register  */
#define USART_CR2_MPE_POS                              (0U)
#define USART_CR2_MPE                                  (0x00000001UL)
#define USART_CR2_WKUPIE_POS                           (1U)
#define USART_CR2_WKUPIE                               (0x00000002UL)
#define USART_CR2_BEIE_POS                             (2U)
#define USART_CR2_BEIE                                 (0x00000004UL)
#define USART_CR2_BEE_POS                              (3U)
#define USART_CR2_BEE                                  (0x00000008UL)
#define USART_CR2_LBDIE_POS                            (4U)
#define USART_CR2_LBDIE                                (0x00000010UL)
#define USART_CR2_LBDL_POS                             (5U)
#define USART_CR2_LBDL                                 (0x00000020UL)
#define USART_CR2_SBKL_POS                             (6U)
#define USART_CR2_SBKL                                 (0x000000C0UL)
#define USART_CR2_SBKL_0                               (0x00000040UL)
#define USART_CR2_SBKL_1                               (0x00000080UL)
#define USART_CR2_WKUPE_POS                            (8U)
#define USART_CR2_WKUPE                                (0x00000100UL)
#define USART_CR2_CLKC_POS                             (11U)
#define USART_CR2_CLKC                                 (0x00001800UL)
#define USART_CR2_CLKC_0                               (0x00000800UL)
#define USART_CR2_CLKC_1                               (0x00001000UL)
#define USART_CR2_STOP_POS                             (13U)
#define USART_CR2_STOP                                 (0x00002000UL)
#define USART_CR2_LINEN_POS                            (14U)
#define USART_CR2_LINEN                                (0x00004000UL)
#define USART_CR2_SBK_POS                              (16U)
#define USART_CR2_SBK                                  (0x00010000UL)
#define USART_CR2_SBKM_POS                             (17U)
#define USART_CR2_SBKM                                 (0x00020000UL)

/*  Bit definition for USART_CR3 register  */
#define USART_CR3_HDSEL_POS                            (3U)
#define USART_CR3_HDSEL                                (0x00000008UL)
#define USART_CR3_LOOP_POS                             (4U)
#define USART_CR3_LOOP                                 (0x00000010UL)
#define USART_CR3_SCEN_POS                             (5U)
#define USART_CR3_SCEN                                 (0x00000020UL)
#define USART_CR3_RTSE_POS                             (8U)
#define USART_CR3_RTSE                                 (0x00000100UL)
#define USART_CR3_CTSE_POS                             (9U)
#define USART_CR3_CTSE                                 (0x00000200UL)
#define USART_CR3_BCN_POS                              (21U)
#define USART_CR3_BCN                                  (0x00E00000UL)
#define USART_CR3_BCN_0                                (0x00200000UL)
#define USART_CR3_BCN_1                                (0x00400000UL)
#define USART_CR3_BCN_2                                (0x00800000UL)

/*  Bit definition for USART_PR register  */
#define USART_PR_PSC_POS                               (0U)
#define USART_PR_PSC                                   (0x00000003UL)
#define USART_PR_PSC_0                                 (0x00000001UL)
#define USART_PR_PSC_1                                 (0x00000002UL)
#define USART_PR_LBMPSC_POS                            (2U)
#define USART_PR_LBMPSC                                (0x0000000CUL)
#define USART_PR_LBMPSC_0                              (0x00000004UL)
#define USART_PR_LBMPSC_1                              (0x00000008UL)

/*  Bit definition for USART_LBMC register  */
#define USART_LBMC_LBMC                                (0x0000FFFFUL)

/*******************************************************************************
                Bit definition for Peripheral USBFS
*******************************************************************************/
/*  Bit definition for USBFS_GVBUSCFG register  */
#define USBFS_GVBUSCFG_VBUSOVEN_POS                    (6U)
#define USBFS_GVBUSCFG_VBUSOVEN                        (0x00000040UL)
#define USBFS_GVBUSCFG_VBUSVAL_POS                     (7U)
#define USBFS_GVBUSCFG_VBUSVAL                         (0x00000080UL)

/*  Bit definition for USBFS_GAHBCFG register  */
#define USBFS_GAHBCFG_GINTMSK_POS                      (0U)
#define USBFS_GAHBCFG_GINTMSK                          (0x00000001UL)
#define USBFS_GAHBCFG_HBSTLEN_POS                      (1U)
#define USBFS_GAHBCFG_HBSTLEN                          (0x0000001EUL)
#define USBFS_GAHBCFG_DMAEN_POS                        (5U)
#define USBFS_GAHBCFG_DMAEN                            (0x00000020UL)
#define USBFS_GAHBCFG_TXFELVL_POS                      (7U)
#define USBFS_GAHBCFG_TXFELVL                          (0x00000080UL)
#define USBFS_GAHBCFG_PTXFELVL_POS                     (8U)
#define USBFS_GAHBCFG_PTXFELVL                         (0x00000100UL)

/*  Bit definition for USBFS_GUSBCFG register  */
#define USBFS_GUSBCFG_TOCAL_POS                        (0U)
#define USBFS_GUSBCFG_TOCAL                            (0x00000007UL)
#define USBFS_GUSBCFG_PHYSEL_POS                       (6U)
#define USBFS_GUSBCFG_PHYSEL                           (0x00000040UL)
#define USBFS_GUSBCFG_TRDT_POS                         (10U)
#define USBFS_GUSBCFG_TRDT                             (0x00003C00UL)
#define USBFS_GUSBCFG_FHMOD_POS                        (29U)
#define USBFS_GUSBCFG_FHMOD                            (0x20000000UL)
#define USBFS_GUSBCFG_FDMOD_POS                        (30U)
#define USBFS_GUSBCFG_FDMOD                            (0x40000000UL)

/*  Bit definition for USBFS_GRSTCTL register  */
#define USBFS_GRSTCTL_CSRST_POS                        (0U)
#define USBFS_GRSTCTL_CSRST                            (0x00000001UL)
#define USBFS_GRSTCTL_HSRST_POS                        (1U)
#define USBFS_GRSTCTL_HSRST                            (0x00000002UL)
#define USBFS_GRSTCTL_FCRST_POS                        (2U)
#define USBFS_GRSTCTL_FCRST                            (0x00000004UL)
#define USBFS_GRSTCTL_RXFFLSH_POS                      (4U)
#define USBFS_GRSTCTL_RXFFLSH                          (0x00000010UL)
#define USBFS_GRSTCTL_TXFFLSH_POS                      (5U)
#define USBFS_GRSTCTL_TXFFLSH                          (0x00000020UL)
#define USBFS_GRSTCTL_TXFNUM_POS                       (6U)
#define USBFS_GRSTCTL_TXFNUM                           (0x000007C0UL)
#define USBFS_GRSTCTL_DMAREQ_POS                       (30U)
#define USBFS_GRSTCTL_DMAREQ                           (0x40000000UL)
#define USBFS_GRSTCTL_AHBIDL_POS                       (31U)
#define USBFS_GRSTCTL_AHBIDL                           (0x80000000UL)

/*  Bit definition for USBFS_GINTSTS register  */
#define USBFS_GINTSTS_CMOD_POS                         (0U)
#define USBFS_GINTSTS_CMOD                             (0x00000001UL)
#define USBFS_GINTSTS_MMIS_POS                         (1U)
#define USBFS_GINTSTS_MMIS                             (0x00000002UL)
#define USBFS_GINTSTS_SOF_POS                          (3U)
#define USBFS_GINTSTS_SOF                              (0x00000008UL)
#define USBFS_GINTSTS_RXFNE_POS                        (4U)
#define USBFS_GINTSTS_RXFNE                            (0x00000010UL)
#define USBFS_GINTSTS_NPTXFE_POS                       (5U)
#define USBFS_GINTSTS_NPTXFE                           (0x00000020UL)
#define USBFS_GINTSTS_GINAKEFF_POS                     (6U)
#define USBFS_GINTSTS_GINAKEFF                         (0x00000040UL)
#define USBFS_GINTSTS_GONAKEFF_POS                     (7U)
#define USBFS_GINTSTS_GONAKEFF                         (0x00000080UL)
#define USBFS_GINTSTS_ESUSP_POS                        (10U)
#define USBFS_GINTSTS_ESUSP                            (0x00000400UL)
#define USBFS_GINTSTS_USBSUSP_POS                      (11U)
#define USBFS_GINTSTS_USBSUSP                          (0x00000800UL)
#define USBFS_GINTSTS_USBRST_POS                       (12U)
#define USBFS_GINTSTS_USBRST                           (0x00001000UL)
#define USBFS_GINTSTS_ENUMDNE_POS                      (13U)
#define USBFS_GINTSTS_ENUMDNE                          (0x00002000UL)
#define USBFS_GINTSTS_ISOODRP_POS                      (14U)
#define USBFS_GINTSTS_ISOODRP                          (0x00004000UL)
#define USBFS_GINTSTS_EOPF_POS                         (15U)
#define USBFS_GINTSTS_EOPF                             (0x00008000UL)
#define USBFS_GINTSTS_IEPINT_POS                       (18U)
#define USBFS_GINTSTS_IEPINT                           (0x00040000UL)
#define USBFS_GINTSTS_OEPINT_POS                       (19U)
#define USBFS_GINTSTS_OEPINT                           (0x00080000UL)
#define USBFS_GINTSTS_IISOIXFR_POS                     (20U)
#define USBFS_GINTSTS_IISOIXFR                         (0x00100000UL)
#define USBFS_GINTSTS_IPXFR_INCOMPISOOUT_POS           (21U)
#define USBFS_GINTSTS_IPXFR_INCOMPISOOUT               (0x00200000UL)
#define USBFS_GINTSTS_DATAFSUSP_POS                    (22U)
#define USBFS_GINTSTS_DATAFSUSP                        (0x00400000UL)
#define USBFS_GINTSTS_HPRTINT_POS                      (24U)
#define USBFS_GINTSTS_HPRTINT                          (0x01000000UL)
#define USBFS_GINTSTS_HCINT_POS                        (25U)
#define USBFS_GINTSTS_HCINT                            (0x02000000UL)
#define USBFS_GINTSTS_PTXFE_POS                        (26U)
#define USBFS_GINTSTS_PTXFE                            (0x04000000UL)
#define USBFS_GINTSTS_LPMINT_POS                       (27U)
#define USBFS_GINTSTS_LPMINT                           (0x08000000UL)
#define USBFS_GINTSTS_CIDSCHG_POS                      (28U)
#define USBFS_GINTSTS_CIDSCHG                          (0x10000000UL)
#define USBFS_GINTSTS_DISCINT_POS                      (29U)
#define USBFS_GINTSTS_DISCINT                          (0x20000000UL)
#define USBFS_GINTSTS_VBUSVINT_POS                     (30U)
#define USBFS_GINTSTS_VBUSVINT                         (0x40000000UL)
#define USBFS_GINTSTS_WKUINT_POS                       (31U)
#define USBFS_GINTSTS_WKUINT                           (0x80000000UL)

/*  Bit definition for USBFS_GINTMSK register  */
#define USBFS_GINTMSK_MMISM_POS                        (1U)
#define USBFS_GINTMSK_MMISM                            (0x00000002UL)
#define USBFS_GINTMSK_SOFM_POS                         (3U)
#define USBFS_GINTMSK_SOFM                             (0x00000008UL)
#define USBFS_GINTMSK_RXFNEM_POS                       (4U)
#define USBFS_GINTMSK_RXFNEM                           (0x00000010UL)
#define USBFS_GINTMSK_NPTXFEM_POS                      (5U)
#define USBFS_GINTMSK_NPTXFEM                          (0x00000020UL)
#define USBFS_GINTMSK_GINAKEFFM_POS                    (6U)
#define USBFS_GINTMSK_GINAKEFFM                        (0x00000040UL)
#define USBFS_GINTMSK_GONAKEFFM_POS                    (7U)
#define USBFS_GINTMSK_GONAKEFFM                        (0x00000080UL)
#define USBFS_GINTMSK_ESUSPM_POS                       (10U)
#define USBFS_GINTMSK_ESUSPM                           (0x00000400UL)
#define USBFS_GINTMSK_USBSUSPM_POS                     (11U)
#define USBFS_GINTMSK_USBSUSPM                         (0x00000800UL)
#define USBFS_GINTMSK_USBRSTM_POS                      (12U)
#define USBFS_GINTMSK_USBRSTM                          (0x00001000UL)
#define USBFS_GINTMSK_ENUMDNEM_POS                     (13U)
#define USBFS_GINTMSK_ENUMDNEM                         (0x00002000UL)
#define USBFS_GINTMSK_ISOODRPM_POS                     (14U)
#define USBFS_GINTMSK_ISOODRPM                         (0x00004000UL)
#define USBFS_GINTMSK_EOPFM_POS                        (15U)
#define USBFS_GINTMSK_EOPFM                            (0x00008000UL)
#define USBFS_GINTMSK_IEPIM_POS                        (18U)
#define USBFS_GINTMSK_IEPIM                            (0x00040000UL)
#define USBFS_GINTMSK_OEPIM_POS                        (19U)
#define USBFS_GINTMSK_OEPIM                            (0x00080000UL)
#define USBFS_GINTMSK_IISOIXFRM_POS                    (20U)
#define USBFS_GINTMSK_IISOIXFRM                        (0x00100000UL)
#define USBFS_GINTMSK_IPXFRM_INCOMPISOOUTM_POS         (21U)
#define USBFS_GINTMSK_IPXFRM_INCOMPISOOUTM             (0x00200000UL)
#define USBFS_GINTMSK_DATAFSUSPM_POS                   (22U)
#define USBFS_GINTMSK_DATAFSUSPM                       (0x00400000UL)
#define USBFS_GINTMSK_HPRTIM_POS                       (24U)
#define USBFS_GINTMSK_HPRTIM                           (0x01000000UL)
#define USBFS_GINTMSK_HCIM_POS                         (25U)
#define USBFS_GINTMSK_HCIM                             (0x02000000UL)
#define USBFS_GINTMSK_PTXFEM_POS                       (26U)
#define USBFS_GINTMSK_PTXFEM                           (0x04000000UL)
#define USBFS_GINTMSK_LPMINTM_POS                      (27U)
#define USBFS_GINTMSK_LPMINTM                          (0x08000000UL)
#define USBFS_GINTMSK_CIDSCHGM_POS                     (28U)
#define USBFS_GINTMSK_CIDSCHGM                         (0x10000000UL)
#define USBFS_GINTMSK_DISCIM_POS                       (29U)
#define USBFS_GINTMSK_DISCIM                           (0x20000000UL)
#define USBFS_GINTMSK_VBUSVIM_POS                      (30U)
#define USBFS_GINTMSK_VBUSVIM                          (0x40000000UL)
#define USBFS_GINTMSK_WKUIM_POS                        (31U)
#define USBFS_GINTMSK_WKUIM                            (0x80000000UL)

/*  Bit definition for USBFS_GRXSTSR register  */
#define USBFS_GRXSTSR_CHNUM_EPNUM_POS                  (0U)
#define USBFS_GRXSTSR_CHNUM_EPNUM                      (0x0000000FUL)
#define USBFS_GRXSTSR_BCNT_POS                         (4U)
#define USBFS_GRXSTSR_BCNT                             (0x00007FF0UL)
#define USBFS_GRXSTSR_DPID_POS                         (15U)
#define USBFS_GRXSTSR_DPID                             (0x00018000UL)
#define USBFS_GRXSTSR_PKTSTS_POS                       (17U)
#define USBFS_GRXSTSR_PKTSTS                           (0x001E0000UL)

/*  Bit definition for USBFS_GRXSTSP register  */
#define USBFS_GRXSTSP_CHNUM_EPNUM_POS                  (0U)
#define USBFS_GRXSTSP_CHNUM_EPNUM                      (0x0000000FUL)
#define USBFS_GRXSTSP_BCNT_POS                         (4U)
#define USBFS_GRXSTSP_BCNT                             (0x00007FF0UL)
#define USBFS_GRXSTSP_DPID_POS                         (15U)
#define USBFS_GRXSTSP_DPID                             (0x00018000UL)
#define USBFS_GRXSTSP_PKTSTS_POS                       (17U)
#define USBFS_GRXSTSP_PKTSTS                           (0x001E0000UL)

/*  Bit definition for USBFS_GRXFSIZ register  */
#define USBFS_GRXFSIZ_RXFD                             (0x000007FFUL)

/*  Bit definition for USBFS_HNPTXFSIZ register  */
#define USBFS_HNPTXFSIZ_NPTXFSA_POS                    (0U)
#define USBFS_HNPTXFSIZ_NPTXFSA                        (0x0000FFFFUL)
#define USBFS_HNPTXFSIZ_NPTXFD_POS                     (16U)
#define USBFS_HNPTXFSIZ_NPTXFD                         (0xFFFF0000UL)

/*  Bit definition for USBFS_HNPTXSTS register  */
#define USBFS_HNPTXSTS_NPTXFSAV_POS                    (0U)
#define USBFS_HNPTXSTS_NPTXFSAV                        (0x0000FFFFUL)
#define USBFS_HNPTXSTS_NPTQXSAV_POS                    (16U)
#define USBFS_HNPTXSTS_NPTQXSAV                        (0x00FF0000UL)
#define USBFS_HNPTXSTS_NPTXQTOP_POS                    (24U)
#define USBFS_HNPTXSTS_NPTXQTOP                        (0x7F000000UL)

/*  Bit definition for USBFS_CID register  */
#define USBFS_CID                                      (0xFFFFFFFFUL)

/*  Bit definition for USBFS_GLPMCFG register  */
#define USBFS_GLPMCFG_LPMEN_POS                        (0U)
#define USBFS_GLPMCFG_LPMEN                            (0x00000001UL)
#define USBFS_GLPMCFG_LPMACK_POS                       (1U)
#define USBFS_GLPMCFG_LPMACK                           (0x00000002UL)
#define USBFS_GLPMCFG_BSEL_POS                         (2U)
#define USBFS_GLPMCFG_BSEL                             (0x0000003CUL)
#define USBFS_GLPMCFG_REMWAKE_POS                      (6U)
#define USBFS_GLPMCFG_REMWAKE                          (0x00000040UL)
#define USBFS_GLPMCFG_L1SSEN_POS                       (7U)
#define USBFS_GLPMCFG_L1SSEN                           (0x00000080UL)
#define USBFS_GLPMCFG_BESLTHRS_POS                     (8U)
#define USBFS_GLPMCFG_BESLTHRS                         (0x00000F00UL)
#define USBFS_GLPMCFG_L1DSEN_POS                       (12U)
#define USBFS_GLPMCFG_L1DSEN                           (0x00001000UL)
#define USBFS_GLPMCFG_LPMRSP_POS                       (13U)
#define USBFS_GLPMCFG_LPMRSP                           (0x00006000UL)
#define USBFS_GLPMCFG_SLPSTS_POS                       (15U)
#define USBFS_GLPMCFG_SLPSTS                           (0x00008000UL)
#define USBFS_GLPMCFG_L1RSMOK_POS                      (16U)
#define USBFS_GLPMCFG_L1RSMOK                          (0x00010000UL)
#define USBFS_GLPMCFG_LPMCHIDX_POS                     (17U)
#define USBFS_GLPMCFG_LPMCHIDX                         (0x001E0000UL)
#define USBFS_GLPMCFG_LPMRCNT_POS                      (21U)
#define USBFS_GLPMCFG_LPMRCNT                          (0x00E00000UL)
#define USBFS_GLPMCFG_SENDLPM_POS                      (24U)
#define USBFS_GLPMCFG_SENDLPM                          (0x01000000UL)
#define USBFS_GLPMCFG_LPMRCNTSTS_POS                   (25U)
#define USBFS_GLPMCFG_LPMRCNTSTS                       (0x0E000000UL)
#define USBFS_GLPMCFG_ENBSEL_POS                       (28U)
#define USBFS_GLPMCFG_ENBSEL                           (0x10000000UL)

/*  Bit definition for USBFS_HPTXFSIZ register  */
#define USBFS_HPTXFSIZ_PTXSA_POS                       (0U)
#define USBFS_HPTXFSIZ_PTXSA                           (0x0000FFFFUL)
#define USBFS_HPTXFSIZ_PTXFD_POS                       (16U)
#define USBFS_HPTXFSIZ_PTXFD                           (0xFFFF0000UL)

/*  Bit definition for USBFS_DIEPTXF register  */
#define USBFS_DIEPTXF_INEPTXSA_POS                     (0U)
#define USBFS_DIEPTXF_INEPTXSA                         (0x0000FFFFUL)
#define USBFS_DIEPTXF_INEPTXFD_POS                     (16U)
#define USBFS_DIEPTXF_INEPTXFD                         (0xFFFF0000UL)

/*  Bit definition for USBFS_HCFG register  */
#define USBFS_HCFG_FSLSPCS_POS                         (0U)
#define USBFS_HCFG_FSLSPCS                             (0x00000003UL)
#define USBFS_HCFG_FSLSS_POS                           (2U)
#define USBFS_HCFG_FSLSS                               (0x00000004UL)

/*  Bit definition for USBFS_HFIR register  */
#define USBFS_HFIR_FRIVL                               (0x0000FFFFUL)

/*  Bit definition for USBFS_HFNUM register  */
#define USBFS_HFNUM_FRNUM_POS                          (0U)
#define USBFS_HFNUM_FRNUM                              (0x0000FFFFUL)
#define USBFS_HFNUM_FTREM_POS                          (16U)
#define USBFS_HFNUM_FTREM                              (0xFFFF0000UL)

/*  Bit definition for USBFS_HPTXSTS register  */
#define USBFS_HPTXSTS_PTXFSAVL_POS                     (0U)
#define USBFS_HPTXSTS_PTXFSAVL                         (0x0000FFFFUL)
#define USBFS_HPTXSTS_PTXQSAV_POS                      (16U)
#define USBFS_HPTXSTS_PTXQSAV                          (0x00FF0000UL)
#define USBFS_HPTXSTS_PTXQTOP_POS                      (24U)
#define USBFS_HPTXSTS_PTXQTOP                          (0xFF000000UL)

/*  Bit definition for USBFS_HAINT register  */
#define USBFS_HAINT_HAINT                              (0x0000FFFFUL)

/*  Bit definition for USBFS_HAINTMSK register  */
#define USBFS_HAINTMSK_HAINTM                          (0x0000FFFFUL)

/*  Bit definition for USBFS_HPRT register  */
#define USBFS_HPRT_PCSTS_POS                           (0U)
#define USBFS_HPRT_PCSTS                               (0x00000001UL)
#define USBFS_HPRT_PCDET_POS                           (1U)
#define USBFS_HPRT_PCDET                               (0x00000002UL)
#define USBFS_HPRT_PENA_POS                            (2U)
#define USBFS_HPRT_PENA                                (0x00000004UL)
#define USBFS_HPRT_PENCHNG_POS                         (3U)
#define USBFS_HPRT_PENCHNG                             (0x00000008UL)
#define USBFS_HPRT_PRES_POS                            (6U)
#define USBFS_HPRT_PRES                                (0x00000040UL)
#define USBFS_HPRT_PSUSP_POS                           (7U)
#define USBFS_HPRT_PSUSP                               (0x00000080UL)
#define USBFS_HPRT_PRST_POS                            (8U)
#define USBFS_HPRT_PRST                                (0x00000100UL)
#define USBFS_HPRT_PLSTS_POS                           (10U)
#define USBFS_HPRT_PLSTS                               (0x00000C00UL)
#define USBFS_HPRT_PWPR_POS                            (12U)
#define USBFS_HPRT_PWPR                                (0x00001000UL)
#define USBFS_HPRT_PSPD_POS                            (17U)
#define USBFS_HPRT_PSPD                                (0x00060000UL)

/*  Bit definition for USBFS_HCCHAR register  */
#define USBFS_HCCHAR_MPSIZ_POS                         (0U)
#define USBFS_HCCHAR_MPSIZ                             (0x000007FFUL)
#define USBFS_HCCHAR_EPNUM_POS                         (11U)
#define USBFS_HCCHAR_EPNUM                             (0x00007800UL)
#define USBFS_HCCHAR_EPDIR_POS                         (15U)
#define USBFS_HCCHAR_EPDIR                             (0x00008000UL)
#define USBFS_HCCHAR_LSDEV_POS                         (17U)
#define USBFS_HCCHAR_LSDEV                             (0x00020000UL)
#define USBFS_HCCHAR_EPTYP_POS                         (18U)
#define USBFS_HCCHAR_EPTYP                             (0x000C0000UL)
#define USBFS_HCCHAR_DAD_POS                           (22U)
#define USBFS_HCCHAR_DAD                               (0x1FC00000UL)
#define USBFS_HCCHAR_ODDFRM_POS                        (29U)
#define USBFS_HCCHAR_ODDFRM                            (0x20000000UL)
#define USBFS_HCCHAR_CHDIS_POS                         (30U)
#define USBFS_HCCHAR_CHDIS                             (0x40000000UL)
#define USBFS_HCCHAR_CHENA_POS                         (31U)
#define USBFS_HCCHAR_CHENA                             (0x80000000UL)

/*  Bit definition for USBFS_HCINT register  */
#define USBFS_HCINT_XFRC_POS                           (0U)
#define USBFS_HCINT_XFRC                               (0x00000001UL)
#define USBFS_HCINT_CHH_POS                            (1U)
#define USBFS_HCINT_CHH                                (0x00000002UL)
#define USBFS_HCINT_AHBERR_POS                         (2U)
#define USBFS_HCINT_AHBERR                             (0x00000004UL)
#define USBFS_HCINT_STALL_POS                          (3U)
#define USBFS_HCINT_STALL                              (0x00000008UL)
#define USBFS_HCINT_NAK_POS                            (4U)
#define USBFS_HCINT_NAK                                (0x00000010UL)
#define USBFS_HCINT_ACK_POS                            (5U)
#define USBFS_HCINT_ACK                                (0x00000020UL)
#define USBFS_HCINT_TXERR_POS                          (7U)
#define USBFS_HCINT_TXERR                              (0x00000080UL)
#define USBFS_HCINT_BBERR_POS                          (8U)
#define USBFS_HCINT_BBERR                              (0x00000100UL)
#define USBFS_HCINT_FRMOR_POS                          (9U)
#define USBFS_HCINT_FRMOR                              (0x00000200UL)
#define USBFS_HCINT_DTERR_POS                          (10U)
#define USBFS_HCINT_DTERR                              (0x00000400UL)

/*  Bit definition for USBFS_HCINTMSK register  */
#define USBFS_HCINTMSK_XFRCM_POS                       (0U)
#define USBFS_HCINTMSK_XFRCM                           (0x00000001UL)
#define USBFS_HCINTMSK_CHHM_POS                        (1U)
#define USBFS_HCINTMSK_CHHM                            (0x00000002UL)
#define USBFS_HCINTMSK_AHBERRM_POS                     (2U)
#define USBFS_HCINTMSK_AHBERRM                         (0x00000004UL)
#define USBFS_HCINTMSK_STALLM_POS                      (3U)
#define USBFS_HCINTMSK_STALLM                          (0x00000008UL)
#define USBFS_HCINTMSK_NAKM_POS                        (4U)
#define USBFS_HCINTMSK_NAKM                            (0x00000010UL)
#define USBFS_HCINTMSK_ACKM_POS                        (5U)
#define USBFS_HCINTMSK_ACKM                            (0x00000020UL)
#define USBFS_HCINTMSK_TXERRM_POS                      (7U)
#define USBFS_HCINTMSK_TXERRM                          (0x00000080UL)
#define USBFS_HCINTMSK_BBERRM_POS                      (8U)
#define USBFS_HCINTMSK_BBERRM                          (0x00000100UL)
#define USBFS_HCINTMSK_FRMORM_POS                      (9U)
#define USBFS_HCINTMSK_FRMORM                          (0x00000200UL)
#define USBFS_HCINTMSK_DTERRM_POS                      (10U)
#define USBFS_HCINTMSK_DTERRM                          (0x00000400UL)

/*  Bit definition for USBFS_HCTSIZ register  */
#define USBFS_HCTSIZ_XFRSIZ_POS                        (0U)
#define USBFS_HCTSIZ_XFRSIZ                            (0x0007FFFFUL)
#define USBFS_HCTSIZ_PKTCNT_POS                        (19U)
#define USBFS_HCTSIZ_PKTCNT                            (0x1FF80000UL)
#define USBFS_HCTSIZ_DPID_POS                          (29U)
#define USBFS_HCTSIZ_DPID                              (0x60000000UL)

/*  Bit definition for USBFS_HCDMA register  */
#define USBFS_HCDMA                                    (0xFFFFFFFFUL)

/*  Bit definition for USBFS_DCFG register  */
#define USBFS_DCFG_DSPD_POS                            (0U)
#define USBFS_DCFG_DSPD                                (0x00000003UL)
#define USBFS_DCFG_NZLSOHSK_POS                        (2U)
#define USBFS_DCFG_NZLSOHSK                            (0x00000004UL)
#define USBFS_DCFG_DAD_POS                             (4U)
#define USBFS_DCFG_DAD                                 (0x000007F0UL)
#define USBFS_DCFG_PFIVL_POS                           (11U)
#define USBFS_DCFG_PFIVL                               (0x00001800UL)

/*  Bit definition for USBFS_DCTL register  */
#define USBFS_DCTL_RWUSIG_POS                          (0U)
#define USBFS_DCTL_RWUSIG                              (0x00000001UL)
#define USBFS_DCTL_SDIS_POS                            (1U)
#define USBFS_DCTL_SDIS                                (0x00000002UL)
#define USBFS_DCTL_GINSTS_POS                          (2U)
#define USBFS_DCTL_GINSTS                              (0x00000004UL)
#define USBFS_DCTL_GONSTS_POS                          (3U)
#define USBFS_DCTL_GONSTS                              (0x00000008UL)
#define USBFS_DCTL_SGINAK_POS                          (7U)
#define USBFS_DCTL_SGINAK                              (0x00000080UL)
#define USBFS_DCTL_CGINAK_POS                          (8U)
#define USBFS_DCTL_CGINAK                              (0x00000100UL)
#define USBFS_DCTL_SGONAK_POS                          (9U)
#define USBFS_DCTL_SGONAK                              (0x00000200UL)
#define USBFS_DCTL_CGONAK_POS                          (10U)
#define USBFS_DCTL_CGONAK                              (0x00000400UL)
#define USBFS_DCTL_POPRGDNE_POS                        (11U)
#define USBFS_DCTL_POPRGDNE                            (0x00000800UL)

/*  Bit definition for USBFS_DSTS register  */
#define USBFS_DSTS_SUSPSTS_POS                         (0U)
#define USBFS_DSTS_SUSPSTS                             (0x00000001UL)
#define USBFS_DSTS_ENUMSPD_POS                         (1U)
#define USBFS_DSTS_ENUMSPD                             (0x00000006UL)
#define USBFS_DSTS_EERR_POS                            (3U)
#define USBFS_DSTS_EERR                                (0x00000008UL)
#define USBFS_DSTS_FNSOF_POS                           (8U)
#define USBFS_DSTS_FNSOF                               (0x003FFF00UL)
#define USBFS_DSTS_LNSTS_POS                           (22U)
#define USBFS_DSTS_LNSTS                               (0x00C00000UL)

/*  Bit definition for USBFS_DIEPMSK register  */
#define USBFS_DIEPMSK_XFRCM_POS                        (0U)
#define USBFS_DIEPMSK_XFRCM                            (0x00000001UL)
#define USBFS_DIEPMSK_EPDM_POS                         (1U)
#define USBFS_DIEPMSK_EPDM                             (0x00000002UL)
#define USBFS_DIEPMSK_TOM_POS                          (3U)
#define USBFS_DIEPMSK_TOM                              (0x00000008UL)
#define USBFS_DIEPMSK_TTXFEMSK_POS                     (4U)
#define USBFS_DIEPMSK_TTXFEMSK                         (0x00000010UL)
#define USBFS_DIEPMSK_INEPNMM_POS                      (5U)
#define USBFS_DIEPMSK_INEPNMM                          (0x00000020UL)
#define USBFS_DIEPMSK_INEPNEM_POS                      (6U)
#define USBFS_DIEPMSK_INEPNEM                          (0x00000040UL)
#define USBFS_DIEPMSK_NAKM_POS                         (13U)
#define USBFS_DIEPMSK_NAKM                             (0x00002000UL)

/*  Bit definition for USBFS_DOEPMSK register  */
#define USBFS_DOEPMSK_XFRCM_POS                        (0U)
#define USBFS_DOEPMSK_XFRCM                            (0x00000001UL)
#define USBFS_DOEPMSK_EPDM_POS                         (1U)
#define USBFS_DOEPMSK_EPDM                             (0x00000002UL)
#define USBFS_DOEPMSK_STUPM_POS                        (3U)
#define USBFS_DOEPMSK_STUPM                            (0x00000008UL)
#define USBFS_DOEPMSK_OTEPDM_POS                       (4U)
#define USBFS_DOEPMSK_OTEPDM                           (0x00000010UL)

/*  Bit definition for USBFS_DAINT register  */
#define USBFS_DAINT_IEPINT_POS                         (0U)
#define USBFS_DAINT_IEPINT                             (0x0000FFFFUL)
#define USBFS_DAINT_OEPINT_POS                         (16U)
#define USBFS_DAINT_OEPINT                             (0xFFFF0000UL)

/*  Bit definition for USBFS_DAINTMSK register  */
#define USBFS_DAINTMSK_IEPINTM_POS                     (0U)
#define USBFS_DAINTMSK_IEPINTM                         (0x0000FFFFUL)
#define USBFS_DAINTMSK_OEPINTM_POS                     (16U)
#define USBFS_DAINTMSK_OEPINTM                         (0xFFFF0000UL)

/*  Bit definition for USBFS_DIEPEMPMSK register  */
#define USBFS_DIEPEMPMSK_INEPTXFEM                     (0x0000FFFFUL)

/*  Bit definition for USBFS_DIEPCTL0 register  */
#define USBFS_DIEPCTL0_MPSIZ_POS                       (0U)
#define USBFS_DIEPCTL0_MPSIZ                           (0x00000003UL)
#define USBFS_DIEPCTL0_USBAEP_POS                      (15U)
#define USBFS_DIEPCTL0_USBAEP                          (0x00008000UL)
#define USBFS_DIEPCTL0_NAKSTS_POS                      (17U)
#define USBFS_DIEPCTL0_NAKSTS                          (0x00020000UL)
#define USBFS_DIEPCTL0_EPTYP_POS                       (18U)
#define USBFS_DIEPCTL0_EPTYP                           (0x000C0000UL)
#define USBFS_DIEPCTL0_STALL_POS                       (21U)
#define USBFS_DIEPCTL0_STALL                           (0x00200000UL)
#define USBFS_DIEPCTL0_TXFNUM_POS                      (22U)
#define USBFS_DIEPCTL0_TXFNUM                          (0x03C00000UL)
#define USBFS_DIEPCTL0_CNAK_POS                        (26U)
#define USBFS_DIEPCTL0_CNAK                            (0x04000000UL)
#define USBFS_DIEPCTL0_SNAK_POS                        (27U)
#define USBFS_DIEPCTL0_SNAK                            (0x08000000UL)
#define USBFS_DIEPCTL0_EPDIS_POS                       (30U)
#define USBFS_DIEPCTL0_EPDIS                           (0x40000000UL)
#define USBFS_DIEPCTL0_EPENA_POS                       (31U)
#define USBFS_DIEPCTL0_EPENA                           (0x80000000UL)

/*  Bit definition for USBFS_DIEPINT register  */
#define USBFS_DIEPINT_XFRC_POS                         (0U)
#define USBFS_DIEPINT_XFRC                             (0x00000001UL)
#define USBFS_DIEPINT_EPDISD_POS                       (1U)
#define USBFS_DIEPINT_EPDISD                           (0x00000002UL)
#define USBFS_DIEPINT_TOC_POS                          (3U)
#define USBFS_DIEPINT_TOC                              (0x00000008UL)
#define USBFS_DIEPINT_TTXFE_POS                        (4U)
#define USBFS_DIEPINT_TTXFE                            (0x00000010UL)
#define USBFS_DIEPINT_INEPNE_POS                       (6U)
#define USBFS_DIEPINT_INEPNE                           (0x00000040UL)
#define USBFS_DIEPINT_TXFE_POS                         (7U)
#define USBFS_DIEPINT_TXFE                             (0x00000080UL)

/*  Bit definition for USBFS_DIEPTSIZ0 register  */
#define USBFS_DIEPTSIZ0_XFRSIZ_POS                     (0U)
#define USBFS_DIEPTSIZ0_XFRSIZ                         (0x0000007FUL)
#define USBFS_DIEPTSIZ0_PKTCNT_POS                     (19U)
#define USBFS_DIEPTSIZ0_PKTCNT                         (0x00180000UL)

/*  Bit definition for USBFS_DIEPDMA register  */
#define USBFS_DIEPDMA                                  (0xFFFFFFFFUL)

/*  Bit definition for USBFS_DTXFSTS register  */
#define USBFS_DTXFSTS_INEPTFSAV                        (0x0000FFFFUL)

/*  Bit definition for USBFS_DIEPCTL register  */
#define USBFS_DIEPCTL_MPSIZ_POS                        (0U)
#define USBFS_DIEPCTL_MPSIZ                            (0x000007FFUL)
#define USBFS_DIEPCTL_USBAEP_POS                       (15U)
#define USBFS_DIEPCTL_USBAEP                           (0x00008000UL)
#define USBFS_DIEPCTL_EONUM_DPID_POS                   (16U)
#define USBFS_DIEPCTL_EONUM_DPID                       (0x00010000UL)
#define USBFS_DIEPCTL_NAKSTS_POS                       (17U)
#define USBFS_DIEPCTL_NAKSTS                           (0x00020000UL)
#define USBFS_DIEPCTL_EPTYP_POS                        (18U)
#define USBFS_DIEPCTL_EPTYP                            (0x000C0000UL)
#define USBFS_DIEPCTL_STALL_POS                        (21U)
#define USBFS_DIEPCTL_STALL                            (0x00200000UL)
#define USBFS_DIEPCTL_TXFNUM_POS                       (22U)
#define USBFS_DIEPCTL_TXFNUM                           (0x03C00000UL)
#define USBFS_DIEPCTL_CNAK_POS                         (26U)
#define USBFS_DIEPCTL_CNAK                             (0x04000000UL)
#define USBFS_DIEPCTL_SNAK_POS                         (27U)
#define USBFS_DIEPCTL_SNAK                             (0x08000000UL)
#define USBFS_DIEPCTL_SD0PID_SEVNFRM_POS               (28U)
#define USBFS_DIEPCTL_SD0PID_SEVNFRM                   (0x10000000UL)
#define USBFS_DIEPCTL_SODDFRM_POS                      (29U)
#define USBFS_DIEPCTL_SODDFRM                          (0x20000000UL)
#define USBFS_DIEPCTL_EPDIS_POS                        (30U)
#define USBFS_DIEPCTL_EPDIS                            (0x40000000UL)
#define USBFS_DIEPCTL_EPENA_POS                        (31U)
#define USBFS_DIEPCTL_EPENA                            (0x80000000UL)

/*  Bit definition for USBFS_DIEPTSIZ register  */
#define USBFS_DIEPTSIZ_XFRSIZ_POS                      (0U)
#define USBFS_DIEPTSIZ_XFRSIZ                          (0x0007FFFFUL)
#define USBFS_DIEPTSIZ_PKTCNT_POS                      (19U)
#define USBFS_DIEPTSIZ_PKTCNT                          (0x1FF80000UL)
#define USBFS_DIEPTSIZ_MCNT_POS                        (29U)
#define USBFS_DIEPTSIZ_MCNT                            (0x60000000UL)

/*  Bit definition for USBFS_DOEPCTL0 register  */
#define USBFS_DOEPCTL0_MPSIZ_POS                       (0U)
#define USBFS_DOEPCTL0_MPSIZ                           (0x00000003UL)
#define USBFS_DOEPCTL0_USBAEP_POS                      (15U)
#define USBFS_DOEPCTL0_USBAEP                          (0x00008000UL)
#define USBFS_DOEPCTL0_NAKSTS_POS                      (17U)
#define USBFS_DOEPCTL0_NAKSTS                          (0x00020000UL)
#define USBFS_DOEPCTL0_EPTYP_POS                       (18U)
#define USBFS_DOEPCTL0_EPTYP                           (0x000C0000UL)
#define USBFS_DOEPCTL0_SNPM_POS                        (20U)
#define USBFS_DOEPCTL0_SNPM                            (0x00100000UL)
#define USBFS_DOEPCTL0_STALL_POS                       (21U)
#define USBFS_DOEPCTL0_STALL                           (0x00200000UL)
#define USBFS_DOEPCTL0_CNAK_POS                        (26U)
#define USBFS_DOEPCTL0_CNAK                            (0x04000000UL)
#define USBFS_DOEPCTL0_SNAK_POS                        (27U)
#define USBFS_DOEPCTL0_SNAK                            (0x08000000UL)
#define USBFS_DOEPCTL0_EPDIS_POS                       (30U)
#define USBFS_DOEPCTL0_EPDIS                           (0x40000000UL)
#define USBFS_DOEPCTL0_EPENA_POS                       (31U)
#define USBFS_DOEPCTL0_EPENA                           (0x80000000UL)

/*  Bit definition for USBFS_DOEPINT register  */
#define USBFS_DOEPINT_XFRC_POS                         (0U)
#define USBFS_DOEPINT_XFRC                             (0x00000001UL)
#define USBFS_DOEPINT_EPDISD_POS                       (1U)
#define USBFS_DOEPINT_EPDISD                           (0x00000002UL)
#define USBFS_DOEPINT_STUP_POS                         (3U)
#define USBFS_DOEPINT_STUP                             (0x00000008UL)
#define USBFS_DOEPINT_OTEPDIS_POS                      (4U)
#define USBFS_DOEPINT_OTEPDIS                          (0x00000010UL)
#define USBFS_DOEPINT_B2BSTUP_POS                      (6U)
#define USBFS_DOEPINT_B2BSTUP                          (0x00000040UL)

/*  Bit definition for USBFS_DOEPTSIZ0 register  */
#define USBFS_DOEPTSIZ0_XFRSIZ_POS                     (0U)
#define USBFS_DOEPTSIZ0_XFRSIZ                         (0x0000007FUL)
#define USBFS_DOEPTSIZ0_PKTCNT_POS                     (19U)
#define USBFS_DOEPTSIZ0_PKTCNT                         (0x00080000UL)
#define USBFS_DOEPTSIZ0_STUPCNT_POS                    (29U)
#define USBFS_DOEPTSIZ0_STUPCNT                        (0x60000000UL)

/*  Bit definition for USBFS_DOEPDMA register  */
#define USBFS_DOEPDMA                                  (0xFFFFFFFFUL)

/*  Bit definition for USBFS_DOEPCTL register  */
#define USBFS_DOEPCTL_MPSIZ_POS                        (0U)
#define USBFS_DOEPCTL_MPSIZ                            (0x000007FFUL)
#define USBFS_DOEPCTL_USBAEP_POS                       (15U)
#define USBFS_DOEPCTL_USBAEP                           (0x00008000UL)
#define USBFS_DOEPCTL_DPID_POS                         (16U)
#define USBFS_DOEPCTL_DPID                             (0x00010000UL)
#define USBFS_DOEPCTL_NAKSTS_POS                       (17U)
#define USBFS_DOEPCTL_NAKSTS                           (0x00020000UL)
#define USBFS_DOEPCTL_EPTYP_POS                        (18U)
#define USBFS_DOEPCTL_EPTYP                            (0x000C0000UL)
#define USBFS_DOEPCTL_SNPM_POS                         (20U)
#define USBFS_DOEPCTL_SNPM                             (0x00100000UL)
#define USBFS_DOEPCTL_STALL_POS                        (21U)
#define USBFS_DOEPCTL_STALL                            (0x00200000UL)
#define USBFS_DOEPCTL_CNAK_POS                         (26U)
#define USBFS_DOEPCTL_CNAK                             (0x04000000UL)
#define USBFS_DOEPCTL_SNAK_POS                         (27U)
#define USBFS_DOEPCTL_SNAK                             (0x08000000UL)
#define USBFS_DOEPCTL_SD0PID_POS                       (28U)
#define USBFS_DOEPCTL_SD0PID                           (0x10000000UL)
#define USBFS_DOEPCTL_SD1PID_POS                       (29U)
#define USBFS_DOEPCTL_SD1PID                           (0x20000000UL)
#define USBFS_DOEPCTL_EPDIS_POS                        (30U)
#define USBFS_DOEPCTL_EPDIS                            (0x40000000UL)
#define USBFS_DOEPCTL_EPENA_POS                        (31U)
#define USBFS_DOEPCTL_EPENA                            (0x80000000UL)

/*  Bit definition for USBFS_DOEPTSIZ register  */
#define USBFS_DOEPTSIZ_XFRSIZ_POS                      (0U)
#define USBFS_DOEPTSIZ_XFRSIZ                          (0x0007FFFFUL)
#define USBFS_DOEPTSIZ_PKTCNT_POS                      (19U)
#define USBFS_DOEPTSIZ_PKTCNT                          (0x1FF80000UL)
#define USBFS_DOEPTSIZ_RXDPID_STUPCNT_POS              (29U)
#define USBFS_DOEPTSIZ_RXDPID_STUPCNT                  (0x60000000UL)

/*  Bit definition for USBFS_GCCTL register  */
#define USBFS_GCCTL_STPPCLK_POS                        (0U)
#define USBFS_GCCTL_STPPCLK                            (0x00000001UL)
#define USBFS_GCCTL_GATEHCLK_POS                       (1U)
#define USBFS_GCCTL_GATEHCLK                           (0x00000002UL)
#define USBFS_GCCTL_ENL1GTG_POS                        (5U)
#define USBFS_GCCTL_ENL1GTG                            (0x00000020UL)
#define USBFS_GCCTL_PHYSLEEP_POS                       (6U)
#define USBFS_GCCTL_PHYSLEEP                           (0x00000040UL)
#define USBFS_GCCTL_SUSP_POS                           (7U)
#define USBFS_GCCTL_SUSP                               (0x00000080UL)

/*******************************************************************************
                Bit definition for Peripheral USBHS
*******************************************************************************/
/*  Bit definition for USBHS_GVBUSCFG register  */
#define USBHS_GVBUSCFG_VBUSOVEN_POS                    (6U)
#define USBHS_GVBUSCFG_VBUSOVEN                        (0x00000040UL)
#define USBHS_GVBUSCFG_VBUSVAL_POS                     (7U)
#define USBHS_GVBUSCFG_VBUSVAL                         (0x00000080UL)

/*  Bit definition for USBHS_GAHBCFG register  */
#define USBHS_GAHBCFG_GINTMSK_POS                      (0U)
#define USBHS_GAHBCFG_GINTMSK                          (0x00000001UL)
#define USBHS_GAHBCFG_HBSTLEN_POS                      (1U)
#define USBHS_GAHBCFG_HBSTLEN                          (0x0000001EUL)
#define USBHS_GAHBCFG_DMAEN_POS                        (5U)
#define USBHS_GAHBCFG_DMAEN                            (0x00000020UL)
#define USBHS_GAHBCFG_TXFELVL_POS                      (7U)
#define USBHS_GAHBCFG_TXFELVL                          (0x00000080UL)
#define USBHS_GAHBCFG_PTXFELVL_POS                     (8U)
#define USBHS_GAHBCFG_PTXFELVL                         (0x00000100UL)

/*  Bit definition for USBHS_GUSBCFG register  */
#define USBHS_GUSBCFG_TOCAL_POS                        (0U)
#define USBHS_GUSBCFG_TOCAL                            (0x00000007UL)
#define USBHS_GUSBCFG_PHYSEL_POS                       (6U)
#define USBHS_GUSBCFG_PHYSEL                           (0x00000040UL)
#define USBHS_GUSBCFG_TRDT_POS                         (10U)
#define USBHS_GUSBCFG_TRDT                             (0x00003C00UL)
#define USBHS_GUSBCFG_PHYLPCS_POS                      (15U)
#define USBHS_GUSBCFG_PHYLPCS                          (0x00008000UL)
#define USBHS_GUSBCFG_ULFSLS_POS                       (17U)
#define USBHS_GUSBCFG_ULFSLS                           (0x00020000UL)
#define USBHS_GUSBCFG_ULPIAR_POS                       (18U)
#define USBHS_GUSBCFG_ULPIAR                           (0x00040000UL)
#define USBHS_GUSBCFG_ULPICSM_POS                      (19U)
#define USBHS_GUSBCFG_ULPICSM                          (0x00080000UL)
#define USBHS_GUSBCFG_ULPIEVBUSD_POS                   (20U)
#define USBHS_GUSBCFG_ULPIEVBUSD                       (0x00100000UL)
#define USBHS_GUSBCFG_ULPIEVBUSI_POS                   (21U)
#define USBHS_GUSBCFG_ULPIEVBUSI                       (0x00200000UL)
#define USBHS_GUSBCFG_PCCI_POS                         (23U)
#define USBHS_GUSBCFG_PCCI                             (0x00800000UL)
#define USBHS_GUSBCFG_PTCI_POS                         (24U)
#define USBHS_GUSBCFG_PTCI                             (0x01000000UL)
#define USBHS_GUSBCFG_ULPIPD_POS                       (25U)
#define USBHS_GUSBCFG_ULPIPD                           (0x02000000UL)
#define USBHS_GUSBCFG_FHMOD_POS                        (29U)
#define USBHS_GUSBCFG_FHMOD                            (0x20000000UL)
#define USBHS_GUSBCFG_FDMOD_POS                        (30U)
#define USBHS_GUSBCFG_FDMOD                            (0x40000000UL)

/*  Bit definition for USBHS_GRSTCTL register  */
#define USBHS_GRSTCTL_CSRST_POS                        (0U)
#define USBHS_GRSTCTL_CSRST                            (0x00000001UL)
#define USBHS_GRSTCTL_HSRST_POS                        (1U)
#define USBHS_GRSTCTL_HSRST                            (0x00000002UL)
#define USBHS_GRSTCTL_FCRST_POS                        (2U)
#define USBHS_GRSTCTL_FCRST                            (0x00000004UL)
#define USBHS_GRSTCTL_RXFFLSH_POS                      (4U)
#define USBHS_GRSTCTL_RXFFLSH                          (0x00000010UL)
#define USBHS_GRSTCTL_TXFFLSH_POS                      (5U)
#define USBHS_GRSTCTL_TXFFLSH                          (0x00000020UL)
#define USBHS_GRSTCTL_TXFNUM_POS                       (6U)
#define USBHS_GRSTCTL_TXFNUM                           (0x000007C0UL)
#define USBHS_GRSTCTL_DMAREQ_POS                       (30U)
#define USBHS_GRSTCTL_DMAREQ                           (0x40000000UL)
#define USBHS_GRSTCTL_AHBIDL_POS                       (31U)
#define USBHS_GRSTCTL_AHBIDL                           (0x80000000UL)

/*  Bit definition for USBHS_GINTSTS register  */
#define USBHS_GINTSTS_CMOD_POS                         (0U)
#define USBHS_GINTSTS_CMOD                             (0x00000001UL)
#define USBHS_GINTSTS_MMIS_POS                         (1U)
#define USBHS_GINTSTS_MMIS                             (0x00000002UL)
#define USBHS_GINTSTS_SOF_POS                          (3U)
#define USBHS_GINTSTS_SOF                              (0x00000008UL)
#define USBHS_GINTSTS_RXFNE_POS                        (4U)
#define USBHS_GINTSTS_RXFNE                            (0x00000010UL)
#define USBHS_GINTSTS_NPTXFE_POS                       (5U)
#define USBHS_GINTSTS_NPTXFE                           (0x00000020UL)
#define USBHS_GINTSTS_GINAKEFF_POS                     (6U)
#define USBHS_GINTSTS_GINAKEFF                         (0x00000040UL)
#define USBHS_GINTSTS_GONAKEFF_POS                     (7U)
#define USBHS_GINTSTS_GONAKEFF                         (0x00000080UL)
#define USBHS_GINTSTS_ESUSP_POS                        (10U)
#define USBHS_GINTSTS_ESUSP                            (0x00000400UL)
#define USBHS_GINTSTS_USBSUSP_POS                      (11U)
#define USBHS_GINTSTS_USBSUSP                          (0x00000800UL)
#define USBHS_GINTSTS_USBRST_POS                       (12U)
#define USBHS_GINTSTS_USBRST                           (0x00001000UL)
#define USBHS_GINTSTS_ENUMDNE_POS                      (13U)
#define USBHS_GINTSTS_ENUMDNE                          (0x00002000UL)
#define USBHS_GINTSTS_ISOODRP_POS                      (14U)
#define USBHS_GINTSTS_ISOODRP                          (0x00004000UL)
#define USBHS_GINTSTS_EOPF_POS                         (15U)
#define USBHS_GINTSTS_EOPF                             (0x00008000UL)
#define USBHS_GINTSTS_IEPINT_POS                       (18U)
#define USBHS_GINTSTS_IEPINT                           (0x00040000UL)
#define USBHS_GINTSTS_OEPINT_POS                       (19U)
#define USBHS_GINTSTS_OEPINT                           (0x00080000UL)
#define USBHS_GINTSTS_IISOIXFR_POS                     (20U)
#define USBHS_GINTSTS_IISOIXFR                         (0x00100000UL)
#define USBHS_GINTSTS_IPXFR_INCOMPISOOUT_POS           (21U)
#define USBHS_GINTSTS_IPXFR_INCOMPISOOUT               (0x00200000UL)
#define USBHS_GINTSTS_DATAFSUSP_POS                    (22U)
#define USBHS_GINTSTS_DATAFSUSP                        (0x00400000UL)
#define USBHS_GINTSTS_HPRTINT_POS                      (24U)
#define USBHS_GINTSTS_HPRTINT                          (0x01000000UL)
#define USBHS_GINTSTS_HCINT_POS                        (25U)
#define USBHS_GINTSTS_HCINT                            (0x02000000UL)
#define USBHS_GINTSTS_PTXFE_POS                        (26U)
#define USBHS_GINTSTS_PTXFE                            (0x04000000UL)
#define USBHS_GINTSTS_LPMINT_POS                       (27U)
#define USBHS_GINTSTS_LPMINT                           (0x08000000UL)
#define USBHS_GINTSTS_CIDSCHG_POS                      (28U)
#define USBHS_GINTSTS_CIDSCHG                          (0x10000000UL)
#define USBHS_GINTSTS_DISCINT_POS                      (29U)
#define USBHS_GINTSTS_DISCINT                          (0x20000000UL)
#define USBHS_GINTSTS_VBUSVINT_POS                     (30U)
#define USBHS_GINTSTS_VBUSVINT                         (0x40000000UL)
#define USBHS_GINTSTS_WKUINT_POS                       (31U)
#define USBHS_GINTSTS_WKUINT                           (0x80000000UL)

/*  Bit definition for USBHS_GINTMSK register  */
#define USBHS_GINTMSK_MMISM_POS                        (1U)
#define USBHS_GINTMSK_MMISM                            (0x00000002UL)
#define USBHS_GINTMSK_SOFM_POS                         (3U)
#define USBHS_GINTMSK_SOFM                             (0x00000008UL)
#define USBHS_GINTMSK_RXFNEM_POS                       (4U)
#define USBHS_GINTMSK_RXFNEM                           (0x00000010UL)
#define USBHS_GINTMSK_NPTXFEM_POS                      (5U)
#define USBHS_GINTMSK_NPTXFEM                          (0x00000020UL)
#define USBHS_GINTMSK_GINAKEFFM_POS                    (6U)
#define USBHS_GINTMSK_GINAKEFFM                        (0x00000040UL)
#define USBHS_GINTMSK_GONAKEFFM_POS                    (7U)
#define USBHS_GINTMSK_GONAKEFFM                        (0x00000080UL)
#define USBHS_GINTMSK_ESUSPM_POS                       (10U)
#define USBHS_GINTMSK_ESUSPM                           (0x00000400UL)
#define USBHS_GINTMSK_USBSUSPM_POS                     (11U)
#define USBHS_GINTMSK_USBSUSPM                         (0x00000800UL)
#define USBHS_GINTMSK_USBRSTM_POS                      (12U)
#define USBHS_GINTMSK_USBRSTM                          (0x00001000UL)
#define USBHS_GINTMSK_ENUMDNEM_POS                     (13U)
#define USBHS_GINTMSK_ENUMDNEM                         (0x00002000UL)
#define USBHS_GINTMSK_ISOODRPM_POS                     (14U)
#define USBHS_GINTMSK_ISOODRPM                         (0x00004000UL)
#define USBHS_GINTMSK_EOPFM_POS                        (15U)
#define USBHS_GINTMSK_EOPFM                            (0x00008000UL)
#define USBHS_GINTMSK_IEPIM_POS                        (18U)
#define USBHS_GINTMSK_IEPIM                            (0x00040000UL)
#define USBHS_GINTMSK_OEPIM_POS                        (19U)
#define USBHS_GINTMSK_OEPIM                            (0x00080000UL)
#define USBHS_GINTMSK_IISOIXFRM_POS                    (20U)
#define USBHS_GINTMSK_IISOIXFRM                        (0x00100000UL)
#define USBHS_GINTMSK_IPXFRM_INCOMPISOOUTM_POS         (21U)
#define USBHS_GINTMSK_IPXFRM_INCOMPISOOUTM             (0x00200000UL)
#define USBHS_GINTMSK_DATAFSUSPM_POS                   (22U)
#define USBHS_GINTMSK_DATAFSUSPM                       (0x00400000UL)
#define USBHS_GINTMSK_HPRTIM_POS                       (24U)
#define USBHS_GINTMSK_HPRTIM                           (0x01000000UL)
#define USBHS_GINTMSK_HCIM_POS                         (25U)
#define USBHS_GINTMSK_HCIM                             (0x02000000UL)
#define USBHS_GINTMSK_PTXFEM_POS                       (26U)
#define USBHS_GINTMSK_PTXFEM                           (0x04000000UL)
#define USBHS_GINTMSK_LPMINTM_POS                      (27U)
#define USBHS_GINTMSK_LPMINTM                          (0x08000000UL)
#define USBHS_GINTMSK_CIDSCHGM_POS                     (28U)
#define USBHS_GINTMSK_CIDSCHGM                         (0x10000000UL)
#define USBHS_GINTMSK_DISCIM_POS                       (29U)
#define USBHS_GINTMSK_DISCIM                           (0x20000000UL)
#define USBHS_GINTMSK_VBUSVIM_POS                      (30U)
#define USBHS_GINTMSK_VBUSVIM                          (0x40000000UL)
#define USBHS_GINTMSK_WKUIM_POS                        (31U)
#define USBHS_GINTMSK_WKUIM                            (0x80000000UL)

/*  Bit definition for USBHS_GRXSTSR register  */
#define USBHS_GRXSTSR_CHNUM_EPNUM_POS                  (0U)
#define USBHS_GRXSTSR_CHNUM_EPNUM                      (0x0000000FUL)
#define USBHS_GRXSTSR_BCNT_POS                         (4U)
#define USBHS_GRXSTSR_BCNT                             (0x00007FF0UL)
#define USBHS_GRXSTSR_DPID_POS                         (15U)
#define USBHS_GRXSTSR_DPID                             (0x00018000UL)
#define USBHS_GRXSTSR_PKTSTS_POS                       (17U)
#define USBHS_GRXSTSR_PKTSTS                           (0x001E0000UL)

/*  Bit definition for USBHS_GRXSTSP register  */
#define USBHS_GRXSTSP_CHNUM_EPNUM_POS                  (0U)
#define USBHS_GRXSTSP_CHNUM_EPNUM                      (0x0000000FUL)
#define USBHS_GRXSTSP_BCNT_POS                         (4U)
#define USBHS_GRXSTSP_BCNT                             (0x00007FF0UL)
#define USBHS_GRXSTSP_DPID_POS                         (15U)
#define USBHS_GRXSTSP_DPID                             (0x00018000UL)
#define USBHS_GRXSTSP_PKTSTS_POS                       (17U)
#define USBHS_GRXSTSP_PKTSTS                           (0x001E0000UL)

/*  Bit definition for USBHS_GRXFSIZ register  */
#define USBHS_GRXFSIZ_RXFD                             (0x00000FFFUL)

/*  Bit definition for USBHS_HNPTXFSIZ register  */
#define USBHS_HNPTXFSIZ_NPTXFSA_POS                    (0U)
#define USBHS_HNPTXFSIZ_NPTXFSA                        (0x0000FFFFUL)
#define USBHS_HNPTXFSIZ_NPTXFD_POS                     (16U)
#define USBHS_HNPTXFSIZ_NPTXFD                         (0xFFFF0000UL)

/*  Bit definition for USBHS_HNPTXSTS register  */
#define USBHS_HNPTXSTS_NPTXFSAV_POS                    (0U)
#define USBHS_HNPTXSTS_NPTXFSAV                        (0x0000FFFFUL)
#define USBHS_HNPTXSTS_NPTQXSAV_POS                    (16U)
#define USBHS_HNPTXSTS_NPTQXSAV                        (0x00FF0000UL)
#define USBHS_HNPTXSTS_NPTXQTOP_POS                    (24U)
#define USBHS_HNPTXSTS_NPTXQTOP                        (0x7F000000UL)

/*  Bit definition for USBHS_CID register  */
#define USBHS_CID                                      (0xFFFFFFFFUL)

/*  Bit definition for USBHS_GLPMCFG register  */
#define USBHS_GLPMCFG_LPMEN_POS                        (0U)
#define USBHS_GLPMCFG_LPMEN                            (0x00000001UL)
#define USBHS_GLPMCFG_LPMACK_POS                       (1U)
#define USBHS_GLPMCFG_LPMACK                           (0x00000002UL)
#define USBHS_GLPMCFG_BSEL_POS                         (2U)
#define USBHS_GLPMCFG_BSEL                             (0x0000003CUL)
#define USBHS_GLPMCFG_REMWAKE_POS                      (6U)
#define USBHS_GLPMCFG_REMWAKE                          (0x00000040UL)
#define USBHS_GLPMCFG_L1SSEN_POS                       (7U)
#define USBHS_GLPMCFG_L1SSEN                           (0x00000080UL)
#define USBHS_GLPMCFG_BESLTHRS_POS                     (8U)
#define USBHS_GLPMCFG_BESLTHRS                         (0x00000F00UL)
#define USBHS_GLPMCFG_L1DSEN_POS                       (12U)
#define USBHS_GLPMCFG_L1DSEN                           (0x00001000UL)
#define USBHS_GLPMCFG_LPMRSP_POS                       (13U)
#define USBHS_GLPMCFG_LPMRSP                           (0x00006000UL)
#define USBHS_GLPMCFG_SLPSTS_POS                       (15U)
#define USBHS_GLPMCFG_SLPSTS                           (0x00008000UL)
#define USBHS_GLPMCFG_L1RSMOK_POS                      (16U)
#define USBHS_GLPMCFG_L1RSMOK                          (0x00010000UL)
#define USBHS_GLPMCFG_LPMCHIDX_POS                     (17U)
#define USBHS_GLPMCFG_LPMCHIDX                         (0x001E0000UL)
#define USBHS_GLPMCFG_LPMRCNT_POS                      (21U)
#define USBHS_GLPMCFG_LPMRCNT                          (0x00E00000UL)
#define USBHS_GLPMCFG_SENDLPM_POS                      (24U)
#define USBHS_GLPMCFG_SENDLPM                          (0x01000000UL)
#define USBHS_GLPMCFG_LPMRCNTSTS_POS                   (25U)
#define USBHS_GLPMCFG_LPMRCNTSTS                       (0x0E000000UL)
#define USBHS_GLPMCFG_ENBSEL_POS                       (28U)
#define USBHS_GLPMCFG_ENBSEL                           (0x10000000UL)

/*  Bit definition for USBHS_HPTXFSIZ register  */
#define USBHS_HPTXFSIZ_PTXSA_POS                       (0U)
#define USBHS_HPTXFSIZ_PTXSA                           (0x0000FFFFUL)
#define USBHS_HPTXFSIZ_PTXFD_POS                       (16U)
#define USBHS_HPTXFSIZ_PTXFD                           (0xFFFF0000UL)

/*  Bit definition for USBHS_DIEPTXF register  */
#define USBHS_DIEPTXF_INEPTXSA_POS                     (0U)
#define USBHS_DIEPTXF_INEPTXSA                         (0x0000FFFFUL)
#define USBHS_DIEPTXF_INEPTXFD_POS                     (16U)
#define USBHS_DIEPTXF_INEPTXFD                         (0xFFFF0000UL)

/*  Bit definition for USBHS_HCFG register  */
#define USBHS_HCFG_FSLSPCS_POS                         (0U)
#define USBHS_HCFG_FSLSPCS                             (0x00000003UL)
#define USBHS_HCFG_FSLSS_POS                           (2U)
#define USBHS_HCFG_FSLSS                               (0x00000004UL)

/*  Bit definition for USBHS_HFIR register  */
#define USBHS_HFIR_FRIVL                               (0x0000FFFFUL)

/*  Bit definition for USBHS_HFNUM register  */
#define USBHS_HFNUM_FRNUM_POS                          (0U)
#define USBHS_HFNUM_FRNUM                              (0x0000FFFFUL)
#define USBHS_HFNUM_FTREM_POS                          (16U)
#define USBHS_HFNUM_FTREM                              (0xFFFF0000UL)

/*  Bit definition for USBHS_HPTXSTS register  */
#define USBHS_HPTXSTS_PTXFSAVL_POS                     (0U)
#define USBHS_HPTXSTS_PTXFSAVL                         (0x0000FFFFUL)
#define USBHS_HPTXSTS_PTXQSAV_POS                      (16U)
#define USBHS_HPTXSTS_PTXQSAV                          (0x00FF0000UL)
#define USBHS_HPTXSTS_PTXQTOP_POS                      (24U)
#define USBHS_HPTXSTS_PTXQTOP                          (0xFF000000UL)

/*  Bit definition for USBHS_HAINT register  */
#define USBHS_HAINT_HAINT                              (0x0000FFFFUL)

/*  Bit definition for USBHS_HAINTMSK register  */
#define USBHS_HAINTMSK_HAINTM                          (0x0000FFFFUL)

/*  Bit definition for USBHS_HPRT register  */
#define USBHS_HPRT_PCSTS_POS                           (0U)
#define USBHS_HPRT_PCSTS                               (0x00000001UL)
#define USBHS_HPRT_PCDET_POS                           (1U)
#define USBHS_HPRT_PCDET                               (0x00000002UL)
#define USBHS_HPRT_PENA_POS                            (2U)
#define USBHS_HPRT_PENA                                (0x00000004UL)
#define USBHS_HPRT_PENCHNG_POS                         (3U)
#define USBHS_HPRT_PENCHNG                             (0x00000008UL)
#define USBHS_HPRT_POCA_POS                            (4U)
#define USBHS_HPRT_POCA                                (0x00000010UL)
#define USBHS_HPRT_POCCHNG_POS                         (5U)
#define USBHS_HPRT_POCCHNG                             (0x00000020UL)
#define USBHS_HPRT_PRES_POS                            (6U)
#define USBHS_HPRT_PRES                                (0x00000040UL)
#define USBHS_HPRT_PSUSP_POS                           (7U)
#define USBHS_HPRT_PSUSP                               (0x00000080UL)
#define USBHS_HPRT_PRST_POS                            (8U)
#define USBHS_HPRT_PRST                                (0x00000100UL)
#define USBHS_HPRT_PLSTS_POS                           (10U)
#define USBHS_HPRT_PLSTS                               (0x00000C00UL)
#define USBHS_HPRT_PWPR_POS                            (12U)
#define USBHS_HPRT_PWPR                                (0x00001000UL)
#define USBHS_HPRT_PTCTL_POS                           (13U)
#define USBHS_HPRT_PTCTL                               (0x0001E000UL)
#define USBHS_HPRT_PSPD_POS                            (17U)
#define USBHS_HPRT_PSPD                                (0x00060000UL)

/*  Bit definition for USBHS_HCCHAR register  */
#define USBHS_HCCHAR_MPSIZ_POS                         (0U)
#define USBHS_HCCHAR_MPSIZ                             (0x000007FFUL)
#define USBHS_HCCHAR_EPNUM_POS                         (11U)
#define USBHS_HCCHAR_EPNUM                             (0x00007800UL)
#define USBHS_HCCHAR_EPDIR_POS                         (15U)
#define USBHS_HCCHAR_EPDIR                             (0x00008000UL)
#define USBHS_HCCHAR_LSDEV_POS                         (17U)
#define USBHS_HCCHAR_LSDEV                             (0x00020000UL)
#define USBHS_HCCHAR_EPTYP_POS                         (18U)
#define USBHS_HCCHAR_EPTYP                             (0x000C0000UL)
#define USBHS_HCCHAR_MC_POS                            (20U)
#define USBHS_HCCHAR_MC                                (0x00300000UL)
#define USBHS_HCCHAR_DAD_POS                           (22U)
#define USBHS_HCCHAR_DAD                               (0x1FC00000UL)
#define USBHS_HCCHAR_ODDFRM_POS                        (29U)
#define USBHS_HCCHAR_ODDFRM                            (0x20000000UL)
#define USBHS_HCCHAR_CHDIS_POS                         (30U)
#define USBHS_HCCHAR_CHDIS                             (0x40000000UL)
#define USBHS_HCCHAR_CHENA_POS                         (31U)
#define USBHS_HCCHAR_CHENA                             (0x80000000UL)

/*  Bit definition for USBHS_HCSPLT register  */
#define USBHS_HCSPLT_PRTADDR_POS                       (0U)
#define USBHS_HCSPLT_PRTADDR                           (0x0000007FUL)
#define USBHS_HCSPLT_HUBADDR_POS                       (7U)
#define USBHS_HCSPLT_HUBADDR                           (0x00003F80UL)
#define USBHS_HCSPLT_XACTPOS_POS                       (14U)
#define USBHS_HCSPLT_XACTPOS                           (0x0000C000UL)
#define USBHS_HCSPLT_COMPLSPLT_POS                     (16U)
#define USBHS_HCSPLT_COMPLSPLT                         (0x00010000UL)
#define USBHS_HCSPLT_SPLITEN_POS                       (31U)
#define USBHS_HCSPLT_SPLITEN                           (0x80000000UL)

/*  Bit definition for USBHS_HCINT register  */
#define USBHS_HCINT_XFRC_POS                           (0U)
#define USBHS_HCINT_XFRC                               (0x00000001UL)
#define USBHS_HCINT_CHH_POS                            (1U)
#define USBHS_HCINT_CHH                                (0x00000002UL)
#define USBHS_HCINT_AHBERR_POS                         (2U)
#define USBHS_HCINT_AHBERR                             (0x00000004UL)
#define USBHS_HCINT_STALL_POS                          (3U)
#define USBHS_HCINT_STALL                              (0x00000008UL)
#define USBHS_HCINT_NAK_POS                            (4U)
#define USBHS_HCINT_NAK                                (0x00000010UL)
#define USBHS_HCINT_ACK_POS                            (5U)
#define USBHS_HCINT_ACK                                (0x00000020UL)
#define USBHS_HCINT_NYET_POS                           (6U)
#define USBHS_HCINT_NYET                               (0x00000040UL)
#define USBHS_HCINT_TXERR_POS                          (7U)
#define USBHS_HCINT_TXERR                              (0x00000080UL)
#define USBHS_HCINT_BBERR_POS                          (8U)
#define USBHS_HCINT_BBERR                              (0x00000100UL)
#define USBHS_HCINT_FRMOR_POS                          (9U)
#define USBHS_HCINT_FRMOR                              (0x00000200UL)
#define USBHS_HCINT_DTERR_POS                          (10U)
#define USBHS_HCINT_DTERR                              (0x00000400UL)

/*  Bit definition for USBHS_HCINTMSK register  */
#define USBHS_HCINTMSK_XFRCM_POS                       (0U)
#define USBHS_HCINTMSK_XFRCM                           (0x00000001UL)
#define USBHS_HCINTMSK_CHHM_POS                        (1U)
#define USBHS_HCINTMSK_CHHM                            (0x00000002UL)
#define USBHS_HCINTMSK_AHBERRM_POS                     (2U)
#define USBHS_HCINTMSK_AHBERRM                         (0x00000004UL)
#define USBHS_HCINTMSK_STALLM_POS                      (3U)
#define USBHS_HCINTMSK_STALLM                          (0x00000008UL)
#define USBHS_HCINTMSK_NAKM_POS                        (4U)
#define USBHS_HCINTMSK_NAKM                            (0x00000010UL)
#define USBHS_HCINTMSK_ACKM_POS                        (5U)
#define USBHS_HCINTMSK_ACKM                            (0x00000020UL)
#define USBHS_HCINTMSK_NYETM_POS                       (6U)
#define USBHS_HCINTMSK_NYETM                           (0x00000040UL)
#define USBHS_HCINTMSK_TXERRM_POS                      (7U)
#define USBHS_HCINTMSK_TXERRM                          (0x00000080UL)
#define USBHS_HCINTMSK_BBERRM_POS                      (8U)
#define USBHS_HCINTMSK_BBERRM                          (0x00000100UL)
#define USBHS_HCINTMSK_FRMORM_POS                      (9U)
#define USBHS_HCINTMSK_FRMORM                          (0x00000200UL)
#define USBHS_HCINTMSK_DTERRM_POS                      (10U)
#define USBHS_HCINTMSK_DTERRM                          (0x00000400UL)

/*  Bit definition for USBHS_HCTSIZ register  */
#define USBHS_HCTSIZ_XFRSIZ_POS                        (0U)
#define USBHS_HCTSIZ_XFRSIZ                            (0x0007FFFFUL)
#define USBHS_HCTSIZ_PKTCNT_POS                        (19U)
#define USBHS_HCTSIZ_PKTCNT                            (0x1FF80000UL)
#define USBHS_HCTSIZ_DPID_POS                          (29U)
#define USBHS_HCTSIZ_DPID                              (0x60000000UL)
#define USBHS_HCTSIZ_DOPING_POS                        (31U)
#define USBHS_HCTSIZ_DOPING                            (0x80000000UL)

/*  Bit definition for USBHS_HCDMA register  */
#define USBHS_HCDMA                                    (0xFFFFFFFFUL)

/*  Bit definition for USBHS_DCFG register  */
#define USBHS_DCFG_DSPD_POS                            (0U)
#define USBHS_DCFG_DSPD                                (0x00000003UL)
#define USBHS_DCFG_NZLSOHSK_POS                        (2U)
#define USBHS_DCFG_NZLSOHSK                            (0x00000004UL)
#define USBHS_DCFG_DAD_POS                             (4U)
#define USBHS_DCFG_DAD                                 (0x000007F0UL)
#define USBHS_DCFG_PFIVL_POS                           (11U)
#define USBHS_DCFG_PFIVL                               (0x00001800UL)

/*  Bit definition for USBHS_DCTL register  */
#define USBHS_DCTL_RWUSIG_POS                          (0U)
#define USBHS_DCTL_RWUSIG                              (0x00000001UL)
#define USBHS_DCTL_SDIS_POS                            (1U)
#define USBHS_DCTL_SDIS                                (0x00000002UL)
#define USBHS_DCTL_GINSTS_POS                          (2U)
#define USBHS_DCTL_GINSTS                              (0x00000004UL)
#define USBHS_DCTL_GONSTS_POS                          (3U)
#define USBHS_DCTL_GONSTS                              (0x00000008UL)
#define USBHS_DCTL_TCTL_POS                            (4U)
#define USBHS_DCTL_TCTL                                (0x00000070UL)
#define USBHS_DCTL_SGINAK_POS                          (7U)
#define USBHS_DCTL_SGINAK                              (0x00000080UL)
#define USBHS_DCTL_CGINAK_POS                          (8U)
#define USBHS_DCTL_CGINAK                              (0x00000100UL)
#define USBHS_DCTL_SGONAK_POS                          (9U)
#define USBHS_DCTL_SGONAK                              (0x00000200UL)
#define USBHS_DCTL_CGONAK_POS                          (10U)
#define USBHS_DCTL_CGONAK                              (0x00000400UL)
#define USBHS_DCTL_POPRGDNE_POS                        (11U)
#define USBHS_DCTL_POPRGDNE                            (0x00000800UL)

/*  Bit definition for USBHS_DSTS register  */
#define USBHS_DSTS_SUSPSTS_POS                         (0U)
#define USBHS_DSTS_SUSPSTS                             (0x00000001UL)
#define USBHS_DSTS_ENUMSPD_POS                         (1U)
#define USBHS_DSTS_ENUMSPD                             (0x00000006UL)
#define USBHS_DSTS_EERR_POS                            (3U)
#define USBHS_DSTS_EERR                                (0x00000008UL)
#define USBHS_DSTS_FNSOF_POS                           (8U)
#define USBHS_DSTS_FNSOF                               (0x003FFF00UL)
#define USBHS_DSTS_LNSTS_POS                           (22U)
#define USBHS_DSTS_LNSTS                               (0x00C00000UL)

/*  Bit definition for USBHS_DIEPMSK register  */
#define USBHS_DIEPMSK_XFRCM_POS                        (0U)
#define USBHS_DIEPMSK_XFRCM                            (0x00000001UL)
#define USBHS_DIEPMSK_EPDM_POS                         (1U)
#define USBHS_DIEPMSK_EPDM                             (0x00000002UL)
#define USBHS_DIEPMSK_TOM_POS                          (3U)
#define USBHS_DIEPMSK_TOM                              (0x00000008UL)
#define USBHS_DIEPMSK_TTXFEMSK_POS                     (4U)
#define USBHS_DIEPMSK_TTXFEMSK                         (0x00000010UL)
#define USBHS_DIEPMSK_INEPNMM_POS                      (5U)
#define USBHS_DIEPMSK_INEPNMM                          (0x00000020UL)
#define USBHS_DIEPMSK_INEPNEM_POS                      (6U)
#define USBHS_DIEPMSK_INEPNEM                          (0x00000040UL)
#define USBHS_DIEPMSK_TXFURM_POS                       (8U)
#define USBHS_DIEPMSK_TXFURM                           (0x00000100UL)
#define USBHS_DIEPMSK_NAKM_POS                         (13U)
#define USBHS_DIEPMSK_NAKM                             (0x00002000UL)

/*  Bit definition for USBHS_DOEPMSK register  */
#define USBHS_DOEPMSK_XFRCM_POS                        (0U)
#define USBHS_DOEPMSK_XFRCM                            (0x00000001UL)
#define USBHS_DOEPMSK_EPDM_POS                         (1U)
#define USBHS_DOEPMSK_EPDM                             (0x00000002UL)
#define USBHS_DOEPMSK_STUPM_POS                        (3U)
#define USBHS_DOEPMSK_STUPM                            (0x00000008UL)
#define USBHS_DOEPMSK_OTEPDM_POS                       (4U)
#define USBHS_DOEPMSK_OTEPDM                           (0x00000010UL)
#define USBHS_DOEPMSK_B2BSTUP_POS                      (6U)
#define USBHS_DOEPMSK_B2BSTUP                          (0x00000040UL)
#define USBHS_DOEPMSK_OPEM_POS                         (8U)
#define USBHS_DOEPMSK_OPEM                             (0x00000100UL)
#define USBHS_DOEPMSK_NYETM_POS                        (14U)
#define USBHS_DOEPMSK_NYETM                            (0x00004000UL)

/*  Bit definition for USBHS_DAINT register  */
#define USBHS_DAINT_IEPINT_POS                         (0U)
#define USBHS_DAINT_IEPINT                             (0x0000FFFFUL)
#define USBHS_DAINT_OEPINT_POS                         (16U)
#define USBHS_DAINT_OEPINT                             (0xFFFF0000UL)

/*  Bit definition for USBHS_DAINTMSK register  */
#define USBHS_DAINTMSK_IEPINTM_POS                     (0U)
#define USBHS_DAINTMSK_IEPINTM                         (0x0000FFFFUL)
#define USBHS_DAINTMSK_OEPINTM_POS                     (16U)
#define USBHS_DAINTMSK_OEPINTM                         (0xFFFF0000UL)

/*  Bit definition for USBHS_DTHRCTL register  */
#define USBHS_DTHRCTL_NONISOTHREN_POS                  (0U)
#define USBHS_DTHRCTL_NONISOTHREN                      (0x00000001UL)
#define USBHS_DTHRCTL_ISOTHREN_POS                     (1U)
#define USBHS_DTHRCTL_ISOTHREN                         (0x00000002UL)
#define USBHS_DTHRCTL_TXTHRLEN_POS                     (2U)
#define USBHS_DTHRCTL_TXTHRLEN                         (0x000007FCUL)
#define USBHS_DTHRCTL_RXTHREN_POS                      (16U)
#define USBHS_DTHRCTL_RXTHREN                          (0x00010000UL)
#define USBHS_DTHRCTL_RXTHRLEN_POS                     (17U)
#define USBHS_DTHRCTL_RXTHRLEN                         (0x03FE0000UL)
#define USBHS_DTHRCTL_ARPEN_POS                        (27U)
#define USBHS_DTHRCTL_ARPEN                            (0x08000000UL)

/*  Bit definition for USBHS_DIEPEMPMSK register  */
#define USBHS_DIEPEMPMSK_INEPTXFEM                     (0x0000FFFFUL)

/*  Bit definition for USBHS_DEACHINT register  */
#define USBHS_DEACHINT_IEP1INT_POS                     (1U)
#define USBHS_DEACHINT_IEP1INT                         (0x00000002UL)
#define USBHS_DEACHINT_OEP1INT_POS                     (17U)
#define USBHS_DEACHINT_OEP1INT                         (0x00020000UL)

/*  Bit definition for USBHS_DEACHINTMSK register  */
#define USBHS_DEACHINTMSK_IEP1INTM_POS                 (1U)
#define USBHS_DEACHINTMSK_IEP1INTM                     (0x00000002UL)
#define USBHS_DEACHINTMSK_OEP1INTM_POS                 (17U)
#define USBHS_DEACHINTMSK_OEP1INTM                     (0x00020000UL)

/*  Bit definition for USBHS_DIEPEACHMSK1 register  */
#define USBHS_DIEPEACHMSK1_XFRCM_POS                   (0U)
#define USBHS_DIEPEACHMSK1_XFRCM                       (0x00000001UL)
#define USBHS_DIEPEACHMSK1_EPDM_POS                    (1U)
#define USBHS_DIEPEACHMSK1_EPDM                        (0x00000002UL)
#define USBHS_DIEPEACHMSK1_TOM_POS                     (3U)
#define USBHS_DIEPEACHMSK1_TOM                         (0x00000008UL)
#define USBHS_DIEPEACHMSK1_TTXFEMSK_POS                (4U)
#define USBHS_DIEPEACHMSK1_TTXFEMSK                    (0x00000010UL)
#define USBHS_DIEPEACHMSK1_INEPNMM_POS                 (5U)
#define USBHS_DIEPEACHMSK1_INEPNMM                     (0x00000020UL)
#define USBHS_DIEPEACHMSK1_INEPNEM_POS                 (6U)
#define USBHS_DIEPEACHMSK1_INEPNEM                     (0x00000040UL)
#define USBHS_DIEPEACHMSK1_TXFURM_POS                  (8U)
#define USBHS_DIEPEACHMSK1_TXFURM                      (0x00000100UL)
#define USBHS_DIEPEACHMSK1_NAKM_POS                    (13U)
#define USBHS_DIEPEACHMSK1_NAKM                        (0x00002000UL)

/*  Bit definition for USBHS_DOEPEACHMSK1 register  */
#define USBHS_DOEPEACHMSK1_XFRCM_POS                   (0U)
#define USBHS_DOEPEACHMSK1_XFRCM                       (0x00000001UL)
#define USBHS_DOEPEACHMSK1_EPDM_POS                    (1U)
#define USBHS_DOEPEACHMSK1_EPDM                        (0x00000002UL)
#define USBHS_DOEPEACHMSK1_STUPM_POS                   (3U)
#define USBHS_DOEPEACHMSK1_STUPM                       (0x00000008UL)
#define USBHS_DOEPEACHMSK1_OTEPDM_POS                  (4U)
#define USBHS_DOEPEACHMSK1_OTEPDM                      (0x00000010UL)
#define USBHS_DOEPEACHMSK1_B2BSTUP_POS                 (6U)
#define USBHS_DOEPEACHMSK1_B2BSTUP                     (0x00000040UL)
#define USBHS_DOEPEACHMSK1_OPEM_POS                    (8U)
#define USBHS_DOEPEACHMSK1_OPEM                        (0x00000100UL)
#define USBHS_DOEPEACHMSK1_NYETM_POS                   (14U)
#define USBHS_DOEPEACHMSK1_NYETM                       (0x00004000UL)

/*  Bit definition for USBHS_DIEPCTL0 register  */
#define USBHS_DIEPCTL0_MPSIZ_POS                       (0U)
#define USBHS_DIEPCTL0_MPSIZ                           (0x00000003UL)
#define USBHS_DIEPCTL0_USBAEP_POS                      (15U)
#define USBHS_DIEPCTL0_USBAEP                          (0x00008000UL)
#define USBHS_DIEPCTL0_NAKSTS_POS                      (17U)
#define USBHS_DIEPCTL0_NAKSTS                          (0x00020000UL)
#define USBHS_DIEPCTL0_EPTYP_POS                       (18U)
#define USBHS_DIEPCTL0_EPTYP                           (0x000C0000UL)
#define USBHS_DIEPCTL0_STALL_POS                       (21U)
#define USBHS_DIEPCTL0_STALL                           (0x00200000UL)
#define USBHS_DIEPCTL0_TXFNUM_POS                      (22U)
#define USBHS_DIEPCTL0_TXFNUM                          (0x03C00000UL)
#define USBHS_DIEPCTL0_CNAK_POS                        (26U)
#define USBHS_DIEPCTL0_CNAK                            (0x04000000UL)
#define USBHS_DIEPCTL0_SNAK_POS                        (27U)
#define USBHS_DIEPCTL0_SNAK                            (0x08000000UL)
#define USBHS_DIEPCTL0_EPDIS_POS                       (30U)
#define USBHS_DIEPCTL0_EPDIS                           (0x40000000UL)
#define USBHS_DIEPCTL0_EPENA_POS                       (31U)
#define USBHS_DIEPCTL0_EPENA                           (0x80000000UL)

/*  Bit definition for USBHS_DIEPINT register  */
#define USBHS_DIEPINT_XFRC_POS                         (0U)
#define USBHS_DIEPINT_XFRC                             (0x00000001UL)
#define USBHS_DIEPINT_EPDISD_POS                       (1U)
#define USBHS_DIEPINT_EPDISD                           (0x00000002UL)
#define USBHS_DIEPINT_TOC_POS                          (3U)
#define USBHS_DIEPINT_TOC                              (0x00000008UL)
#define USBHS_DIEPINT_TTXFE_POS                        (4U)
#define USBHS_DIEPINT_TTXFE                            (0x00000010UL)
#define USBHS_DIEPINT_INEPNE_POS                       (6U)
#define USBHS_DIEPINT_INEPNE                           (0x00000040UL)
#define USBHS_DIEPINT_TXFE_POS                         (7U)
#define USBHS_DIEPINT_TXFE                             (0x00000080UL)
#define USBHS_DIEPINT_TXFIFOUDRN_POS                   (8U)
#define USBHS_DIEPINT_TXFIFOUDRN                       (0x00000100UL)
#define USBHS_DIEPINT_PKTDRPSTS_POS                    (11U)
#define USBHS_DIEPINT_PKTDRPSTS                        (0x00000800UL)
#define USBHS_DIEPINT_BERR_POS                         (12U)
#define USBHS_DIEPINT_BERR                             (0x00001000UL)
#define USBHS_DIEPINT_NAK_POS                          (13U)
#define USBHS_DIEPINT_NAK                              (0x00002000UL)

/*  Bit definition for USBHS_DIEPTSIZ0 register  */
#define USBHS_DIEPTSIZ0_XFRSIZ_POS                     (0U)
#define USBHS_DIEPTSIZ0_XFRSIZ                         (0x0000007FUL)
#define USBHS_DIEPTSIZ0_PKTCNT_POS                     (19U)
#define USBHS_DIEPTSIZ0_PKTCNT                         (0x00180000UL)

/*  Bit definition for USBHS_DIEPDMA register  */
#define USBHS_DIEPDMA                                  (0xFFFFFFFFUL)

/*  Bit definition for USBHS_DTXFSTS register  */
#define USBHS_DTXFSTS_INEPTFSAV                        (0x0000FFFFUL)

/*  Bit definition for USBHS_DIEPCTL register  */
#define USBHS_DIEPCTL_MPSIZ_POS                        (0U)
#define USBHS_DIEPCTL_MPSIZ                            (0x000007FFUL)
#define USBHS_DIEPCTL_USBAEP_POS                       (15U)
#define USBHS_DIEPCTL_USBAEP                           (0x00008000UL)
#define USBHS_DIEPCTL_EONUM_DPID_POS                   (16U)
#define USBHS_DIEPCTL_EONUM_DPID                       (0x00010000UL)
#define USBHS_DIEPCTL_NAKSTS_POS                       (17U)
#define USBHS_DIEPCTL_NAKSTS                           (0x00020000UL)
#define USBHS_DIEPCTL_EPTYP_POS                        (18U)
#define USBHS_DIEPCTL_EPTYP                            (0x000C0000UL)
#define USBHS_DIEPCTL_STALL_POS                        (21U)
#define USBHS_DIEPCTL_STALL                            (0x00200000UL)
#define USBHS_DIEPCTL_TXFNUM_POS                       (22U)
#define USBHS_DIEPCTL_TXFNUM                           (0x03C00000UL)
#define USBHS_DIEPCTL_CNAK_POS                         (26U)
#define USBHS_DIEPCTL_CNAK                             (0x04000000UL)
#define USBHS_DIEPCTL_SNAK_POS                         (27U)
#define USBHS_DIEPCTL_SNAK                             (0x08000000UL)
#define USBHS_DIEPCTL_SD0PID_SEVNFRM_POS               (28U)
#define USBHS_DIEPCTL_SD0PID_SEVNFRM                   (0x10000000UL)
#define USBHS_DIEPCTL_SODDFRM_POS                      (29U)
#define USBHS_DIEPCTL_SODDFRM                          (0x20000000UL)
#define USBHS_DIEPCTL_EPDIS_POS                        (30U)
#define USBHS_DIEPCTL_EPDIS                            (0x40000000UL)
#define USBHS_DIEPCTL_EPENA_POS                        (31U)
#define USBHS_DIEPCTL_EPENA                            (0x80000000UL)

/*  Bit definition for USBHS_DIEPTSIZ register  */
#define USBHS_DIEPTSIZ_XFRSIZ_POS                      (0U)
#define USBHS_DIEPTSIZ_XFRSIZ                          (0x0007FFFFUL)
#define USBHS_DIEPTSIZ_PKTCNT_POS                      (19U)
#define USBHS_DIEPTSIZ_PKTCNT                          (0x1FF80000UL)
#define USBHS_DIEPTSIZ_MCNT_POS                        (29U)
#define USBHS_DIEPTSIZ_MCNT                            (0x60000000UL)

/*  Bit definition for USBHS_DOEPCTL0 register  */
#define USBHS_DOEPCTL0_MPSIZ_POS                       (0U)
#define USBHS_DOEPCTL0_MPSIZ                           (0x00000003UL)
#define USBHS_DOEPCTL0_USBAEP_POS                      (15U)
#define USBHS_DOEPCTL0_USBAEP                          (0x00008000UL)
#define USBHS_DOEPCTL0_NAKSTS_POS                      (17U)
#define USBHS_DOEPCTL0_NAKSTS                          (0x00020000UL)
#define USBHS_DOEPCTL0_EPTYP_POS                       (18U)
#define USBHS_DOEPCTL0_EPTYP                           (0x000C0000UL)
#define USBHS_DOEPCTL0_EPTYP_0                         (0x00040000UL)
#define USBHS_DOEPCTL0_EPTYP_1                         (0x00080000UL)
#define USBHS_DOEPCTL0_SNPM_POS                        (20U)
#define USBHS_DOEPCTL0_SNPM                            (0x00100000UL)
#define USBHS_DOEPCTL0_STALL_POS                       (21U)
#define USBHS_DOEPCTL0_STALL                           (0x00200000UL)
#define USBHS_DOEPCTL0_CNAK_POS                        (26U)
#define USBHS_DOEPCTL0_CNAK                            (0x04000000UL)
#define USBHS_DOEPCTL0_SNAK_POS                        (27U)
#define USBHS_DOEPCTL0_SNAK                            (0x08000000UL)
#define USBHS_DOEPCTL0_EPDIS_POS                       (30U)
#define USBHS_DOEPCTL0_EPDIS                           (0x40000000UL)
#define USBHS_DOEPCTL0_EPENA_POS                       (31U)
#define USBHS_DOEPCTL0_EPENA                           (0x80000000UL)

/*  Bit definition for USBHS_DOEPINT register  */
#define USBHS_DOEPINT_XFRC_POS                         (0U)
#define USBHS_DOEPINT_XFRC                             (0x00000001UL)
#define USBHS_DOEPINT_EPDISD_POS                       (1U)
#define USBHS_DOEPINT_EPDISD                           (0x00000002UL)
#define USBHS_DOEPINT_STUP_POS                         (3U)
#define USBHS_DOEPINT_STUP                             (0x00000008UL)
#define USBHS_DOEPINT_OTEPDIS_POS                      (4U)
#define USBHS_DOEPINT_OTEPDIS                          (0x00000010UL)
#define USBHS_DOEPINT_B2BSTUP_POS                      (6U)
#define USBHS_DOEPINT_B2BSTUP                          (0x00000040UL)
#define USBHS_DOEPINT_NYET_POS                         (14U)
#define USBHS_DOEPINT_NYET                             (0x00004000UL)

/*  Bit definition for USBHS_DOEPTSIZ0 register  */
#define USBHS_DOEPTSIZ0_XFRSIZ_POS                     (0U)
#define USBHS_DOEPTSIZ0_XFRSIZ                         (0x0000007FUL)
#define USBHS_DOEPTSIZ0_PKTCNT_POS                     (19U)
#define USBHS_DOEPTSIZ0_PKTCNT                         (0x00080000UL)
#define USBHS_DOEPTSIZ0_STUPCNT_POS                    (29U)
#define USBHS_DOEPTSIZ0_STUPCNT                        (0x60000000UL)

/*  Bit definition for USBHS_DOEPDMA register  */
#define USBHS_DOEPDMA                                  (0xFFFFFFFFUL)

/*  Bit definition for USBHS_DOEPCTL register  */
#define USBHS_DOEPCTL_MPSIZ_POS                        (0U)
#define USBHS_DOEPCTL_MPSIZ                            (0x000007FFUL)
#define USBHS_DOEPCTL_USBAEP_POS                       (15U)
#define USBHS_DOEPCTL_USBAEP                           (0x00008000UL)
#define USBHS_DOEPCTL_DPID_POS                         (16U)
#define USBHS_DOEPCTL_DPID                             (0x00010000UL)
#define USBHS_DOEPCTL_NAKSTS_POS                       (17U)
#define USBHS_DOEPCTL_NAKSTS                           (0x00020000UL)
#define USBHS_DOEPCTL_EPTYP_POS                        (18U)
#define USBHS_DOEPCTL_EPTYP                            (0x000C0000UL)
#define USBHS_DOEPCTL_SNPM_POS                         (20U)
#define USBHS_DOEPCTL_SNPM                             (0x00100000UL)
#define USBHS_DOEPCTL_STALL_POS                        (21U)
#define USBHS_DOEPCTL_STALL                            (0x00200000UL)
#define USBHS_DOEPCTL_CNAK_POS                         (26U)
#define USBHS_DOEPCTL_CNAK                             (0x04000000UL)
#define USBHS_DOEPCTL_SNAK_POS                         (27U)
#define USBHS_DOEPCTL_SNAK                             (0x08000000UL)
#define USBHS_DOEPCTL_SD0PID_POS                       (28U)
#define USBHS_DOEPCTL_SD0PID                           (0x10000000UL)
#define USBHS_DOEPCTL_SD1PID_POS                       (29U)
#define USBHS_DOEPCTL_SD1PID                           (0x20000000UL)
#define USBHS_DOEPCTL_EPDIS_POS                        (30U)
#define USBHS_DOEPCTL_EPDIS                            (0x40000000UL)
#define USBHS_DOEPCTL_EPENA_POS                        (31U)
#define USBHS_DOEPCTL_EPENA                            (0x80000000UL)

/*  Bit definition for USBHS_DOEPTSIZ register  */
#define USBHS_DOEPTSIZ_XFRSIZ_POS                      (0U)
#define USBHS_DOEPTSIZ_XFRSIZ                          (0x0007FFFFUL)
#define USBHS_DOEPTSIZ_PKTCNT_POS                      (19U)
#define USBHS_DOEPTSIZ_PKTCNT                          (0x1FF80000UL)
#define USBHS_DOEPTSIZ_RXDPID_STUPCNT_POS              (29U)
#define USBHS_DOEPTSIZ_RXDPID_STUPCNT                  (0x60000000UL)

/*  Bit definition for USBHS_GCCTL register  */
#define USBHS_GCCTL_STPPCLK_POS                        (0U)
#define USBHS_GCCTL_STPPCLK                            (0x00000001UL)
#define USBHS_GCCTL_GATEHCLK_POS                       (1U)
#define USBHS_GCCTL_GATEHCLK                           (0x00000002UL)
#define USBHS_GCCTL_ENL1GTG_POS                        (5U)
#define USBHS_GCCTL_ENL1GTG                            (0x00000020UL)
#define USBHS_GCCTL_PHYSLEEP_POS                       (6U)
#define USBHS_GCCTL_PHYSLEEP                           (0x00000040UL)
#define USBHS_GCCTL_SUSP_POS                           (7U)
#define USBHS_GCCTL_SUSP                               (0x00000080UL)

/*******************************************************************************
                Bit definition for Peripheral WDT
*******************************************************************************/
/*  Bit definition for WDT_CR register  */
#define WDT_CR_PERI_POS                                (0U)
#define WDT_CR_PERI                                    (0x00000003UL)
#define WDT_CR_PERI_0                                  (0x00000001UL)
#define WDT_CR_PERI_1                                  (0x00000002UL)
#define WDT_CR_CKS_POS                                 (4U)
#define WDT_CR_CKS                                     (0x000000F0UL)
#define WDT_CR_CKS_0                                   (0x00000010UL)
#define WDT_CR_CKS_1                                   (0x00000020UL)
#define WDT_CR_CKS_2                                   (0x00000040UL)
#define WDT_CR_CKS_3                                   (0x00000080UL)
#define WDT_CR_WDPT_POS                                (8U)
#define WDT_CR_WDPT                                    (0x00000F00UL)
#define WDT_CR_WDPT_0                                  (0x00000100UL)
#define WDT_CR_WDPT_1                                  (0x00000200UL)
#define WDT_CR_WDPT_2                                  (0x00000400UL)
#define WDT_CR_WDPT_3                                  (0x00000800UL)
#define WDT_CR_SLPOFF_POS                              (16U)
#define WDT_CR_SLPOFF                                  (0x00010000UL)
#define WDT_CR_ITS_POS                                 (31U)
#define WDT_CR_ITS                                     (0x80000000UL)

/*  Bit definition for WDT_SR register  */
#define WDT_SR_CNT_POS                                 (0U)
#define WDT_SR_CNT                                     (0x0000FFFFUL)
#define WDT_SR_UDF_POS                                 (16U)
#define WDT_SR_UDF                                     (0x00010000UL)
#define WDT_SR_REF_POS                                 (17U)
#define WDT_SR_REF                                     (0x00020000UL)

/*  Bit definition for WDT_RR register  */
#define WDT_RR_RF                                      (0x0000FFFFUL)

/******************************************************************************/
/*             Device Specific Registers bit_band structure                   */
/******************************************************************************/

typedef struct {
    __IO uint32_t STRT;
    uint32_t RESERVED0[7];
} stc_adc_str_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t CLREN;
    __IO uint32_t DFMT;
    uint32_t RESERVED1[8];
} stc_adc_cr0_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t RSCHSEL;
    uint32_t RESERVED1[13];
} stc_adc_cr1_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t TRGENA;
    uint32_t RESERVED1[7];
    __IO uint32_t TRGENB;
} stc_adc_trgsr_bit_t;

typedef struct {
    __IO uint32_t EXCHSEL;
    uint32_t RESERVED0[7];
} stc_adc_exchselr_bit_t;

typedef struct {
    __I  uint32_t EOCAF;
    __I  uint32_t EOCBF;
    uint32_t RESERVED0[2];
    __I  uint32_t SASTPDF;
    uint32_t RESERVED1[3];
} stc_adc_isr_bit_t;

typedef struct {
    __IO uint32_t EOCAIEN;
    __IO uint32_t EOCBIEN;
    uint32_t RESERVED0[6];
} stc_adc_icr_bit_t;

typedef struct {
    __IO uint32_t CLREOCAF;
    __IO uint32_t CLREOCBF;
    uint32_t RESERVED0[2];
    __IO uint32_t CLRSASTPDF;
    uint32_t RESERVED1[3];
} stc_adc_isclrr_bit_t;

typedef struct {
    __IO uint32_t SYNCEN;
    uint32_t RESERVED0[15];
} stc_adc_synccr_bit_t;

typedef struct {
    __IO uint32_t AWD0EN;
    __IO uint32_t AWD0IEN;
    __IO uint32_t AWD0MD;
    uint32_t RESERVED0[1];
    __IO uint32_t AWD1EN;
    __IO uint32_t AWD1IEN;
    __IO uint32_t AWD1MD;
    uint32_t RESERVED1[9];
} stc_adc_awdcr_bit_t;

typedef struct {
    __I  uint32_t AWD0F;
    __I  uint32_t AWD1F;
    uint32_t RESERVED0[2];
    __I  uint32_t AWDCMF;
    uint32_t RESERVED1[3];
} stc_adc_awdsr_bit_t;

typedef struct {
    __IO uint32_t CLRAWD0F;
    __IO uint32_t CLRAWD1F;
    uint32_t RESERVED0[2];
    __IO uint32_t CLRAWDCMF;
    uint32_t RESERVED1[3];
} stc_adc_awdsclrr_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t MODE;
    uint32_t RESERVED0[30];
} stc_aes_cr_bit_t;

typedef struct {
    __O  uint32_t STRG;
    uint32_t RESERVED0[31];
} stc_aos_intsfttrg_bit_t;

typedef struct {
    __IO uint32_t NFEN1;
    uint32_t RESERVED0[7];
    __IO uint32_t NFEN2;
    uint32_t RESERVED1[7];
    __IO uint32_t NFEN3;
    uint32_t RESERVED2[7];
    __IO uint32_t NFEN4;
    uint32_t RESERVED3[7];
} stc_aos_pevntnfcr_bit_t;

typedef struct {
    __IO uint32_t BUSOFF;
    __I  uint32_t TACTIVE;
    __I  uint32_t RACTIVE;
    __IO uint32_t TSSS;
    __IO uint32_t TPSS;
    __IO uint32_t LBMI;
    __IO uint32_t LBME;
    __IO uint32_t RESET;
} stc_can_cfg_stat_bit_t;

typedef struct {
    __IO uint32_t TSA;
    __IO uint32_t TSALL;
    __IO uint32_t TSONE;
    __IO uint32_t TPA;
    __IO uint32_t TPE;
    uint32_t RESERVED0[1];
    __IO uint32_t LOM;
    __IO uint32_t TBSEL;
} stc_can_tcmd_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t TTTBM;
    __IO uint32_t TSMODE;
    __IO uint32_t TSNEXT;
    __IO uint32_t FD_ISO;
} stc_can_tctrl_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t RBALL;
    __IO uint32_t RREL;
    __I  uint32_t ROV;
    __IO uint32_t ROM;
    __IO uint32_t SACK;
} stc_can_rctrl_bit_t;

typedef struct {
    __I  uint32_t TSFF;
    __IO uint32_t EIE;
    __IO uint32_t TSIE;
    __IO uint32_t TPIE;
    __IO uint32_t RAFIE;
    __IO uint32_t RFIE;
    __IO uint32_t ROIE;
    __IO uint32_t RIE;
} stc_can_rtie_bit_t;

typedef struct {
    __IO uint32_t AIF;
    __IO uint32_t EIF;
    __IO uint32_t TSIF;
    __IO uint32_t TPIF;
    __IO uint32_t RAFIF;
    __IO uint32_t RFIF;
    __IO uint32_t ROIF;
    __IO uint32_t RIF;
} stc_can_rtif_bit_t;

typedef struct {
    __IO uint32_t BEIF;
    __IO uint32_t BEIE;
    __IO uint32_t ALIF;
    __IO uint32_t ALIE;
    __IO uint32_t EPIF;
    __IO uint32_t EPIE;
    __I  uint32_t EPASS;
    __I  uint32_t EWARN;
} stc_can_errint_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t TDCEN;
} stc_can_tdc_bit_t;

typedef struct {
    uint32_t RESERVED0[5];
    __IO uint32_t SELMASK;
    uint32_t RESERVED1[2];
} stc_can_acfctrl_bit_t;

typedef struct {
    __IO uint32_t AE_1;
    __IO uint32_t AE_2;
    __IO uint32_t AE_3;
    __IO uint32_t AE_4;
    __IO uint32_t AE_5;
    __IO uint32_t AE_6;
    __IO uint32_t AE_7;
    __IO uint32_t AE_8;
    __IO uint32_t AE_9;
    __IO uint32_t AE_10;
    __IO uint32_t AE_11;
    __IO uint32_t AE_12;
    __IO uint32_t AE_13;
    __IO uint32_t AE_14;
    __IO uint32_t AE_15;
    __IO uint32_t AE_16;
} stc_can_acfen_bit_t;

typedef struct {
    uint32_t RESERVED0[29];
    __IO uint32_t AIDE;
    __IO uint32_t AIDEE;
    uint32_t RESERVED1[1];
} stc_can_acf_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t TBF;
    __IO uint32_t TBE;
} stc_can_tbslot_bit_t;

typedef struct {
    __IO uint32_t TTEN;
    uint32_t RESERVED0[2];
    __IO uint32_t TTIF;
    __IO uint32_t TTIE;
    __IO uint32_t TEIF;
    __IO uint32_t WTIF;
    __IO uint32_t WTIE;
} stc_can_ttcfg_bit_t;

typedef struct {
    uint32_t RESERVED0[31];
    __IO uint32_t REF_IDE;
} stc_can_ref_msg_bit_t;

typedef struct {
    __IO uint32_t CENB;
    __IO uint32_t CWDE;
    uint32_t RESERVED0[5];
    __I  uint32_t CMON;
} stc_cmp_mdr_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t CIEN;
    uint32_t RESERVED1[1];
} stc_cmp_fir_bit_t;

typedef struct {
    __IO uint32_t COEN;
    __IO uint32_t COPS;
    __IO uint32_t CPOE;
    __IO uint32_t TWOE;
    __IO uint32_t TWOL;
    uint32_t RESERVED0[3];
} stc_cmp_ocr_bit_t;

typedef struct {
    __IO uint32_t CTWS0;
    __IO uint32_t CTWS1;
    __IO uint32_t CTWS2;
    __IO uint32_t CTWS3;
    __IO uint32_t CTWS4;
    __IO uint32_t CTWS5;
    __IO uint32_t CTWS6;
    __IO uint32_t CTWS7;
    __IO uint32_t CTWS8;
    __IO uint32_t CTWS9;
    __IO uint32_t CTWS10;
    __IO uint32_t CTWS11;
    __IO uint32_t CTWS12;
    __IO uint32_t CTWS13;
    __IO uint32_t CTWS14;
    __IO uint32_t CTWS15;
} stc_cmp_twsr_bit_t;

typedef struct {
    __IO uint32_t CTWP0;
    __IO uint32_t CTWP1;
    __IO uint32_t CTWP2;
    __IO uint32_t CTWP3;
    __IO uint32_t CTWP4;
    __IO uint32_t CTWP5;
    __IO uint32_t CTWP6;
    __IO uint32_t CTWP7;
    __IO uint32_t CTWP8;
    __IO uint32_t CTWP9;
    __IO uint32_t CTWP10;
    __IO uint32_t CTWP11;
    __IO uint32_t CTWP12;
    __IO uint32_t CTWP13;
    __IO uint32_t CTWP14;
    __IO uint32_t CTWP15;
} stc_cmp_twpr_bit_t;

typedef struct {
    __IO uint32_t XTAL32STP;
    uint32_t RESERVED0[7];
} stc_cmu_xtal32cr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t XTAL32IE;
    uint32_t RESERVED1[4];
} stc_cmu_xtal32cfgr_bit_t;

typedef struct {
    __IO uint32_t LRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_lrccr_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t XTALMS;
    uint32_t RESERVED1[1];
} stc_cmu_xtalcfgr_bit_t;

typedef struct {
    __IO uint32_t PLLHOFF;
    uint32_t RESERVED0[7];
} stc_cmu_pllhcr_bit_t;

typedef struct {
    __IO uint32_t PLLAOFF;
    uint32_t RESERVED0[7];
} stc_cmu_pllacr_bit_t;

typedef struct {
    __IO uint32_t XTALSTP;
    uint32_t RESERVED0[7];
} stc_cmu_xtalcr_bit_t;

typedef struct {
    __IO uint32_t HRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_hrccr_bit_t;

typedef struct {
    __IO uint32_t MRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_mrccr_bit_t;

typedef struct {
    __IO uint32_t HRCSTBF;
    uint32_t RESERVED0[2];
    __IO uint32_t XTALSTBF;
    uint32_t RESERVED1[1];
    __IO uint32_t PLLHSTBF;
    __IO uint32_t PLLASTBF;
    uint32_t RESERVED2[1];
} stc_cmu_oscstbsr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t MCOEN;
} stc_cmu_mcocfgr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t TPIUCKOE;
} stc_cmu_tpiuckcfgr_bit_t;

typedef struct {
    __IO uint32_t XTALSTDIE;
    __IO uint32_t XTALSTDRE;
    __IO uint32_t XTALSTDRIS;
    uint32_t RESERVED0[4];
    __IO uint32_t XTALSTDE;
} stc_cmu_xtalstdcr_bit_t;

typedef struct {
    __IO uint32_t XTALSTDF;
    uint32_t RESERVED0[7];
} stc_cmu_xtalstdsr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t PLLSRC;
    uint32_t RESERVED1[24];
} stc_cmu_pllhcfgr_bit_t;

typedef struct {
    __IO uint32_t CR;
    __I  uint32_t FLAG;
    uint32_t RESERVED0[30];
} stc_crc_cr_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t ERRIE;
    __IO uint32_t CTCEN;
    uint32_t RESERVED1[24];
} stc_ctc_cr1_bit_t;

typedef struct {
    __I  uint32_t TRIMOK;
    __I  uint32_t TRMOVF;
    __I  uint32_t TRMUDF;
    __I  uint32_t CTCBSY;
    uint32_t RESERVED0[28];
} stc_ctc_str_bit_t;

typedef struct {
    __IO uint32_t DAE;
    __IO uint32_t DA1E;
    __IO uint32_t DA2E;
    uint32_t RESERVED0[5];
    __IO uint32_t DPSEL;
    __IO uint32_t DAAMP1;
    __IO uint32_t DAAMP2;
    __IO uint32_t EXTDSL1;
    __IO uint32_t EXTDSL2;
    uint32_t RESERVED1[3];
} stc_dac_dacr_bit_t;

typedef struct {
    __IO uint32_t ADCSL1;
    __IO uint32_t ADCSL2;
    __IO uint32_t ADCSL3;
    uint32_t RESERVED0[5];
    __I  uint32_t DA1SF;
    __I  uint32_t DA2SF;
    uint32_t RESERVED1[5];
    __IO uint32_t ADPEN;
} stc_dac_daadpcr_bit_t;

typedef struct {
    uint32_t RESERVED0[14];
    __IO uint32_t DAODIS1;
    __IO uint32_t DAODIS2;
} stc_dac_daocr_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t COMPTRG;
    uint32_t RESERVED1[22];
    __IO uint32_t INTEN;
} stc_dcu_ctl_bit_t;

typedef struct {
    __I  uint32_t FLAG_OP;
    __I  uint32_t FLAG_LS2;
    __I  uint32_t FLAG_EQ2;
    __I  uint32_t FLAG_GT2;
    __I  uint32_t FLAG_LS1;
    __I  uint32_t FLAG_EQ1;
    __I  uint32_t FLAG_GT1;
    uint32_t RESERVED0[2];
    __I  uint32_t FLAG_RLD;
    __I  uint32_t FLAG_BTM;
    __I  uint32_t FLAG_TOP;
    uint32_t RESERVED1[20];
} stc_dcu_flag_bit_t;

typedef struct {
    __IO uint32_t CLR_OP;
    __IO uint32_t CLR_LS2;
    __IO uint32_t CLR_EQ2;
    __IO uint32_t CLR_GT2;
    __IO uint32_t CLR_LS1;
    __IO uint32_t CLR_EQ1;
    __IO uint32_t CLR_GT1;
    uint32_t RESERVED0[2];
    __IO uint32_t CLR_RLD;
    __IO uint32_t CLR_BTM;
    __IO uint32_t CLR_TOP;
    uint32_t RESERVED1[20];
} stc_dcu_flagclr_bit_t;

typedef struct {
    __IO uint32_t SEL_OP;
    __IO uint32_t SEL_LS2;
    __IO uint32_t SEL_EQ2;
    __IO uint32_t SEL_GT2;
    __IO uint32_t SEL_LS1;
    __IO uint32_t SEL_EQ1;
    __IO uint32_t SEL_GT1;
    uint32_t RESERVED0[2];
    __IO uint32_t SEL_RLD;
    __IO uint32_t SEL_BTM;
    __IO uint32_t SEL_TOP;
    uint32_t RESERVED1[20];
} stc_dcu_intevtsel_bit_t;

typedef struct {
    __IO uint32_t EN;
    uint32_t RESERVED0[31];
} stc_dma_en_bit_t;

typedef struct {
    __I  uint32_t TRNERR0;
    __I  uint32_t TRNERR1;
    __I  uint32_t TRNERR2;
    __I  uint32_t TRNERR3;
    __I  uint32_t TRNERR4;
    __I  uint32_t TRNERR5;
    __I  uint32_t TRNERR6;
    __I  uint32_t TRNERR7;
    uint32_t RESERVED0[8];
    __I  uint32_t REQERR0;
    __I  uint32_t REQERR1;
    __I  uint32_t REQERR2;
    __I  uint32_t REQERR3;
    __I  uint32_t REQERR4;
    __I  uint32_t REQERR5;
    __I  uint32_t REQERR6;
    __I  uint32_t REQERR7;
    uint32_t RESERVED1[8];
} stc_dma_intstat0_bit_t;

typedef struct {
    __I  uint32_t TC0;
    __I  uint32_t TC1;
    __I  uint32_t TC2;
    __I  uint32_t TC3;
    __I  uint32_t TC4;
    __I  uint32_t TC5;
    __I  uint32_t TC6;
    __I  uint32_t TC7;
    uint32_t RESERVED0[8];
    __I  uint32_t BTC0;
    __I  uint32_t BTC1;
    __I  uint32_t BTC2;
    __I  uint32_t BTC3;
    __I  uint32_t BTC4;
    __I  uint32_t BTC5;
    __I  uint32_t BTC6;
    __I  uint32_t BTC7;
    uint32_t RESERVED1[8];
} stc_dma_intstat1_bit_t;

typedef struct {
    __IO uint32_t MSKTRNERR0;
    __IO uint32_t MSKTRNERR1;
    __IO uint32_t MSKTRNERR2;
    __IO uint32_t MSKTRNERR3;
    __IO uint32_t MSKTRNERR4;
    __IO uint32_t MSKTRNERR5;
    __IO uint32_t MSKTRNERR6;
    __IO uint32_t MSKTRNERR7;
    uint32_t RESERVED0[8];
    __IO uint32_t MSKREQERR0;
    __IO uint32_t MSKREQERR1;
    __IO uint32_t MSKREQERR2;
    __IO uint32_t MSKREQERR3;
    __IO uint32_t MSKREQERR4;
    __IO uint32_t MSKREQERR5;
    __IO uint32_t MSKREQERR6;
    __IO uint32_t MSKREQERR7;
    uint32_t RESERVED1[8];
} stc_dma_intmask0_bit_t;

typedef struct {
    __IO uint32_t MSKTC0;
    __IO uint32_t MSKTC1;
    __IO uint32_t MSKTC2;
    __IO uint32_t MSKTC3;
    __IO uint32_t MSKTC4;
    __IO uint32_t MSKTC5;
    __IO uint32_t MSKTC6;
    __IO uint32_t MSKTC7;
    uint32_t RESERVED0[8];
    __IO uint32_t MSKBTC0;
    __IO uint32_t MSKBTC1;
    __IO uint32_t MSKBTC2;
    __IO uint32_t MSKBTC3;
    __IO uint32_t MSKBTC4;
    __IO uint32_t MSKBTC5;
    __IO uint32_t MSKBTC6;
    __IO uint32_t MSKBTC7;
    uint32_t RESERVED1[8];
} stc_dma_intmask1_bit_t;

typedef struct {
    __IO uint32_t CLRTRNERR0;
    __IO uint32_t CLRTRNERR1;
    __IO uint32_t CLRTRNERR2;
    __IO uint32_t CLRTRNERR3;
    __IO uint32_t CLRTRNERR4;
    __IO uint32_t CLRTRNERR5;
    __IO uint32_t CLRTRNERR6;
    __IO uint32_t CLRTRNERR7;
    uint32_t RESERVED0[8];
    __IO uint32_t CLRREQERR0;
    __IO uint32_t CLRREQERR1;
    __IO uint32_t CLRREQERR2;
    __IO uint32_t CLRREQERR3;
    __IO uint32_t CLRREQERR4;
    __IO uint32_t CLRREQERR5;
    __IO uint32_t CLRREQERR6;
    __IO uint32_t CLRREQERR7;
    uint32_t RESERVED1[8];
} stc_dma_intclr0_bit_t;

typedef struct {
    __IO uint32_t CLRTC0;
    __IO uint32_t CLRTC1;
    __IO uint32_t CLRTC2;
    __IO uint32_t CLRTC3;
    __IO uint32_t CLRTC4;
    __IO uint32_t CLRTC5;
    __IO uint32_t CLRTC6;
    __IO uint32_t CLRTC7;
    uint32_t RESERVED0[8];
    __IO uint32_t CLRBTC0;
    __IO uint32_t CLRBTC1;
    __IO uint32_t CLRBTC2;
    __IO uint32_t CLRBTC3;
    __IO uint32_t CLRBTC4;
    __IO uint32_t CLRBTC5;
    __IO uint32_t CLRBTC6;
    __IO uint32_t CLRBTC7;
    uint32_t RESERVED1[8];
} stc_dma_intclr1_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __I  uint32_t RCFGREQ;
    uint32_t RESERVED1[16];
} stc_dma_reqstat_bit_t;

typedef struct {
    __I  uint32_t DMAACT;
    __I  uint32_t RCFGACT;
    uint32_t RESERVED0[30];
} stc_dma_chstat_bit_t;

typedef struct {
    __IO uint32_t RCFGEN;
    __IO uint32_t RCFGLLP;
    uint32_t RESERVED0[30];
} stc_dma_rcfgctl_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t SRPTEN;
    __IO uint32_t DRPTEN;
    __IO uint32_t SNSEQEN;
    __IO uint32_t DNSEQEN;
    uint32_t RESERVED1[2];
    __IO uint32_t LLPEN;
    __IO uint32_t LLPRUN;
    __IO uint32_t IE;
    uint32_t RESERVED2[19];
} stc_dma_chctl_bit_t;

typedef struct {
    __IO uint32_t CAPEN;
    __IO uint32_t CAPMD;
    __IO uint32_t CROPEN;
    __IO uint32_t JPEGEN;
    __IO uint32_t SWSYNC;
    __IO uint32_t PIXCKSEL;
    __IO uint32_t HSYNCSEL;
    __IO uint32_t VSYNCSEL;
    uint32_t RESERVED0[6];
    __IO uint32_t DVPEN;
    uint32_t RESERVED1[17];
} stc_dvp_ctr_bit_t;

typedef struct {
    __IO uint32_t FSF;
    __IO uint32_t LSF;
    __IO uint32_t LEF;
    __IO uint32_t FEF;
    __IO uint32_t SQUERF;
    __IO uint32_t FIFOERF;
    uint32_t RESERVED0[26];
} stc_dvp_str_bit_t;

typedef struct {
    __IO uint32_t FSIEN;
    __IO uint32_t LSIEN;
    __IO uint32_t LEIEN;
    __IO uint32_t FEIEN;
    __IO uint32_t SQUERIEN;
    __IO uint32_t FIFOERIEN;
    uint32_t RESERVED0[26];
} stc_dvp_ier_bit_t;

typedef struct {
    __IO uint32_t F0STP;
    __IO uint32_t F1STP;
    uint32_t RESERVED0[30];
} stc_efm_fstp_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t LVM;
    uint32_t RESERVED1[7];
    __IO uint32_t ICACHE;
    __IO uint32_t DCACHE;
    __IO uint32_t PREFETE;
    __IO uint32_t CRST;
    uint32_t RESERVED2[12];
} stc_efm_frmc_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t BUSHLDCTL;
    uint32_t RESERVED1[7];
    __IO uint32_t KEY1LOCK;
    __IO uint32_t KEY2LOCK;
    uint32_t RESERVED2[14];
} stc_efm_fwmc_bit_t;

typedef struct {
    __I  uint32_t OTPWERR0;
    __I  uint32_t PRTWERR0;
    __I  uint32_t PGSZERR0;
    __I  uint32_t MISMTCH0;
    __I  uint32_t OPTEND0;
    __I  uint32_t COLERR0;
    uint32_t RESERVED0[2];
    __I  uint32_t RDY0;
    uint32_t RESERVED1[8];
    __I  uint32_t PRTWERR1;
    __I  uint32_t PGSZERR1;
    __I  uint32_t MISMTCH1;
    __I  uint32_t OPTEND1;
    __I  uint32_t COLERR1;
    uint32_t RESERVED2[2];
    __I  uint32_t RDY1;
    uint32_t RESERVED3[7];
} stc_efm_fsr_bit_t;

typedef struct {
    __IO uint32_t OTPWERRCLR0;
    __IO uint32_t PRTWERRCLR0;
    __IO uint32_t PGSZERRCLR0;
    __IO uint32_t MISMTCHCLR0;
    __IO uint32_t OPTENDCLR0;
    __IO uint32_t COLERRCLR0;
    uint32_t RESERVED0[11];
    __IO uint32_t PRTWERRCLR1;
    __IO uint32_t PGSZERRCLR1;
    __IO uint32_t MISMTCHCLR1;
    __IO uint32_t OPTENDCLR1;
    __IO uint32_t COLERRCLR1;
    uint32_t RESERVED1[10];
} stc_efm_fsclr_bit_t;

typedef struct {
    __IO uint32_t PEERRITE;
    __IO uint32_t OPTENDITE;
    __IO uint32_t COLERRITE;
    uint32_t RESERVED0[29];
} stc_efm_fite_bit_t;

typedef struct {
    __I  uint32_t FSWP;
    uint32_t RESERVED0[31];
} stc_efm_fswp_bit_t;

typedef struct {
    uint32_t RESERVED0[31];
    __IO uint32_t EN;
} stc_efm_mmf_remcr_bit_t;

typedef struct {
    __IO uint32_t F0NWPRT0;
    __IO uint32_t F0NWPRT1;
    __IO uint32_t F0NWPRT2;
    __IO uint32_t F0NWPRT3;
    __IO uint32_t F0NWPRT4;
    __IO uint32_t F0NWPRT5;
    __IO uint32_t F0NWPRT6;
    __IO uint32_t F0NWPRT7;
    __IO uint32_t F0NWPRT8;
    __IO uint32_t F0NWPRT9;
    __IO uint32_t F0NWPRT10;
    __IO uint32_t F0NWPRT11;
    __IO uint32_t F0NWPRT12;
    __IO uint32_t F0NWPRT13;
    __IO uint32_t F0NWPRT14;
    __IO uint32_t F0NWPRT15;
    __IO uint32_t F0NWPRT16;
    __IO uint32_t F0NWPRT17;
    __IO uint32_t F0NWPRT18;
    __IO uint32_t F0NWPRT19;
    __IO uint32_t F0NWPRT20;
    __IO uint32_t F0NWPRT21;
    __IO uint32_t F0NWPRT22;
    __IO uint32_t F0NWPRT23;
    __IO uint32_t F0NWPRT24;
    __IO uint32_t F0NWPRT25;
    __IO uint32_t F0NWPRT26;
    __IO uint32_t F0NWPRT27;
    __IO uint32_t F0NWPRT28;
    __IO uint32_t F0NWPRT29;
    __IO uint32_t F0NWPRT30;
    __IO uint32_t F0NWPRT31;
} stc_efm_f0nwprt0_bit_t;

typedef struct {
    __IO uint32_t F0NWPRT32;
    __IO uint32_t F0NWPRT33;
    __IO uint32_t F0NWPRT34;
    __IO uint32_t F0NWPRT35;
    __IO uint32_t F0NWPRT36;
    __IO uint32_t F0NWPRT37;
    __IO uint32_t F0NWPRT38;
    __IO uint32_t F0NWPRT39;
    __IO uint32_t F0NWPRT40;
    __IO uint32_t F0NWPRT41;
    __IO uint32_t F0NWPRT42;
    __IO uint32_t F0NWPRT43;
    __IO uint32_t F0NWPRT44;
    __IO uint32_t F0NWPRT45;
    __IO uint32_t F0NWPRT46;
    __IO uint32_t F0NWPRT47;
    __IO uint32_t F0NWPRT48;
    __IO uint32_t F0NWPRT49;
    __IO uint32_t F0NWPRT50;
    __IO uint32_t F0NWPRT51;
    __IO uint32_t F0NWPRT52;
    __IO uint32_t F0NWPRT53;
    __IO uint32_t F0NWPRT54;
    __IO uint32_t F0NWPRT55;
    __IO uint32_t F0NWPRT56;
    __IO uint32_t F0NWPRT57;
    __IO uint32_t F0NWPRT58;
    __IO uint32_t F0NWPRT59;
    __IO uint32_t F0NWPRT60;
    __IO uint32_t F0NWPRT61;
    __IO uint32_t F0NWPRT62;
    __IO uint32_t F0NWPRT63;
} stc_efm_f0nwprt1_bit_t;

typedef struct {
    __IO uint32_t F0NWPRT64;
    __IO uint32_t F0NWPRT65;
    __IO uint32_t F0NWPRT66;
    __IO uint32_t F0NWPRT67;
    __IO uint32_t F0NWPRT68;
    __IO uint32_t F0NWPRT69;
    __IO uint32_t F0NWPRT70;
    __IO uint32_t F0NWPRT71;
    __IO uint32_t F0NWPRT72;
    __IO uint32_t F0NWPRT73;
    __IO uint32_t F0NWPRT74;
    __IO uint32_t F0NWPRT75;
    __IO uint32_t F0NWPRT76;
    __IO uint32_t F0NWPRT77;
    __IO uint32_t F0NWPRT78;
    __IO uint32_t F0NWPRT79;
    __IO uint32_t F0NWPRT80;
    __IO uint32_t F0NWPRT81;
    __IO uint32_t F0NWPRT82;
    __IO uint32_t F0NWPRT83;
    __IO uint32_t F0NWPRT84;
    __IO uint32_t F0NWPRT85;
    __IO uint32_t F0NWPRT86;
    __IO uint32_t F0NWPRT87;
    __IO uint32_t F0NWPRT88;
    __IO uint32_t F0NWPRT89;
    __IO uint32_t F0NWPRT90;
    __IO uint32_t F0NWPRT91;
    __IO uint32_t F0NWPRT92;
    __IO uint32_t F0NWPRT93;
    __IO uint32_t F0NWPRT94;
    __IO uint32_t F0NWPRT95;
} stc_efm_f0nwprt2_bit_t;

typedef struct {
    __IO uint32_t F0NWPRT96;
    __IO uint32_t F0NWPRT97;
    __IO uint32_t F0NWPRT98;
    __IO uint32_t F0NWPRT99;
    __IO uint32_t F0NWPRT100;
    __IO uint32_t F0NWPRT101;
    __IO uint32_t F0NWPRT102;
    __IO uint32_t F0NWPRT103;
    __IO uint32_t F0NWPRT104;
    __IO uint32_t F0NWPRT105;
    __IO uint32_t F0NWPRT106;
    __IO uint32_t F0NWPRT107;
    __IO uint32_t F0NWPRT108;
    __IO uint32_t F0NWPRT109;
    __IO uint32_t F0NWPRT110;
    __IO uint32_t F0NWPRT111;
    __IO uint32_t F0NWPRT112;
    __IO uint32_t F0NWPRT113;
    __IO uint32_t F0NWPRT114;
    __IO uint32_t F0NWPRT115;
    __IO uint32_t F0NWPRT116;
    __IO uint32_t F0NWPRT117;
    __IO uint32_t F0NWPRT118;
    __IO uint32_t F0NWPRT119;
    __IO uint32_t F0NWPRT120;
    __IO uint32_t F0NWPRT121;
    __IO uint32_t F0NWPRT122;
    __IO uint32_t F0NWPRT123;
    __IO uint32_t F0NWPRT124;
    __IO uint32_t F0NWPRT125;
    __IO uint32_t F0NWPRT126;
    __IO uint32_t F0NWPRT127;
} stc_efm_f0nwprt3_bit_t;

typedef struct {
    __IO uint32_t F1NWPRT0;
    __IO uint32_t F1NWPRT1;
    __IO uint32_t F1NWPRT2;
    __IO uint32_t F1NWPRT3;
    __IO uint32_t F1NWPRT4;
    __IO uint32_t F1NWPRT5;
    __IO uint32_t F1NWPRT6;
    __IO uint32_t F1NWPRT7;
    __IO uint32_t F1NWPRT8;
    __IO uint32_t F1NWPRT9;
    __IO uint32_t F1NWPRT10;
    __IO uint32_t F1NWPRT11;
    __IO uint32_t F1NWPRT12;
    __IO uint32_t F1NWPRT13;
    __IO uint32_t F1NWPRT14;
    __IO uint32_t F1NWPRT15;
    __IO uint32_t F1NWPRT16;
    __IO uint32_t F1NWPRT17;
    __IO uint32_t F1NWPRT18;
    __IO uint32_t F1NWPRT19;
    __IO uint32_t F1NWPRT20;
    __IO uint32_t F1NWPRT21;
    __IO uint32_t F1NWPRT22;
    __IO uint32_t F1NWPRT23;
    __IO uint32_t F1NWPRT24;
    __IO uint32_t F1NWPRT25;
    __IO uint32_t F1NWPRT26;
    __IO uint32_t F1NWPRT27;
    __IO uint32_t F1NWPRT28;
    __IO uint32_t F1NWPRT29;
    __IO uint32_t F1NWPRT30;
    __IO uint32_t F1NWPRT31;
} stc_efm_f1nwprt0_bit_t;

typedef struct {
    __IO uint32_t F1NWPRT32;
    __IO uint32_t F1NWPRT33;
    __IO uint32_t F1NWPRT34;
    __IO uint32_t F1NWPRT35;
    __IO uint32_t F1NWPRT36;
    __IO uint32_t F1NWPRT37;
    __IO uint32_t F1NWPRT38;
    __IO uint32_t F1NWPRT39;
    __IO uint32_t F1NWPRT40;
    __IO uint32_t F1NWPRT41;
    __IO uint32_t F1NWPRT42;
    __IO uint32_t F1NWPRT43;
    __IO uint32_t F1NWPRT44;
    __IO uint32_t F1NWPRT45;
    __IO uint32_t F1NWPRT46;
    __IO uint32_t F1NWPRT47;
    __IO uint32_t F1NWPRT48;
    __IO uint32_t F1NWPRT49;
    __IO uint32_t F1NWPRT50;
    __IO uint32_t F1NWPRT51;
    __IO uint32_t F1NWPRT52;
    __IO uint32_t F1NWPRT53;
    __IO uint32_t F1NWPRT54;
    __IO uint32_t F1NWPRT55;
    __IO uint32_t F1NWPRT56;
    __IO uint32_t F1NWPRT57;
    __IO uint32_t F1NWPRT58;
    __IO uint32_t F1NWPRT59;
    __IO uint32_t F1NWPRT60;
    __IO uint32_t F1NWPRT61;
    __IO uint32_t F1NWPRT62;
    __IO uint32_t F1NWPRT63;
} stc_efm_f1nwprt1_bit_t;

typedef struct {
    __IO uint32_t F1NWPRT64;
    __IO uint32_t F1NWPRT65;
    __IO uint32_t F1NWPRT66;
    __IO uint32_t F1NWPRT67;
    __IO uint32_t F1NWPRT68;
    __IO uint32_t F1NWPRT69;
    __IO uint32_t F1NWPRT70;
    __IO uint32_t F1NWPRT71;
    __IO uint32_t F1NWPRT72;
    __IO uint32_t F1NWPRT73;
    __IO uint32_t F1NWPRT74;
    __IO uint32_t F1NWPRT75;
    __IO uint32_t F1NWPRT76;
    __IO uint32_t F1NWPRT77;
    __IO uint32_t F1NWPRT78;
    __IO uint32_t F1NWPRT79;
    __IO uint32_t F1NWPRT80;
    __IO uint32_t F1NWPRT81;
    __IO uint32_t F1NWPRT82;
    __IO uint32_t F1NWPRT83;
    __IO uint32_t F1NWPRT84;
    __IO uint32_t F1NWPRT85;
    __IO uint32_t F1NWPRT86;
    __IO uint32_t F1NWPRT87;
    __IO uint32_t F1NWPRT88;
    __IO uint32_t F1NWPRT89;
    __IO uint32_t F1NWPRT90;
    __IO uint32_t F1NWPRT91;
    __IO uint32_t F1NWPRT92;
    __IO uint32_t F1NWPRT93;
    __IO uint32_t F1NWPRT94;
    __IO uint32_t F1NWPRT95;
} stc_efm_f1nwprt2_bit_t;

typedef struct {
    __IO uint32_t F1NWPRT96;
    __IO uint32_t F1NWPRT97;
    __IO uint32_t F1NWPRT98;
    __IO uint32_t F1NWPRT99;
    __IO uint32_t F1NWPRT100;
    __IO uint32_t F1NWPRT101;
    __IO uint32_t F1NWPRT102;
    __IO uint32_t F1NWPRT103;
    __IO uint32_t F1NWPRT104;
    __IO uint32_t F1NWPRT105;
    __IO uint32_t F1NWPRT106;
    __IO uint32_t F1NWPRT107;
    __IO uint32_t F1NWPRT108;
    __IO uint32_t F1NWPRT109;
    __IO uint32_t F1NWPRT110;
    __IO uint32_t F1NWPRT111;
    __IO uint32_t F1NWPRT112;
    __IO uint32_t F1NWPRT113;
    __IO uint32_t F1NWPRT114;
    __IO uint32_t F1NWPRT115;
    __IO uint32_t F1NWPRT116;
    __IO uint32_t F1NWPRT117;
    __IO uint32_t F1NWPRT118;
    __IO uint32_t F1NWPRT119;
    __IO uint32_t F1NWPRT120;
    __IO uint32_t F1NWPRT121;
    __IO uint32_t F1NWPRT122;
    __IO uint32_t F1NWPRT123;
    __IO uint32_t F1NWPRT124;
    __IO uint32_t F1NWPRT125;
    __IO uint32_t F1NWPRT126;
    __IO uint32_t F1NWPRT127;
} stc_efm_f1nwprt3_bit_t;

typedef struct {
    __IO uint32_t CMPEN1;
    __IO uint32_t CMPEN2;
    __IO uint32_t CMPEN3;
    __IO uint32_t CMPEN4;
    __IO uint32_t OSCSTPEN;
    __IO uint32_t PWMSEN0;
    __IO uint32_t PWMSEN1;
    __IO uint32_t PWMSEN2;
    __IO uint32_t PWMSEN3;
    __IO uint32_t PWMSEN4;
    __IO uint32_t PWMSEN5;
    __IO uint32_t PWMSEN6;
    __IO uint32_t PWMSEN7;
    uint32_t RESERVED0[3];
    __IO uint32_t PORTINEN1;
    __IO uint32_t PORTINEN2;
    __IO uint32_t PORTINEN3;
    __IO uint32_t PORTINEN4;
    uint32_t RESERVED1[2];
    __IO uint32_t INVSEL1;
    __IO uint32_t INVSEL2;
    __IO uint32_t INVSEL3;
    __IO uint32_t INVSEL4;
    uint32_t RESERVED2[6];
} stc_emb_ctl1_bit_t;

typedef struct {
    __IO uint32_t PWMLV0;
    __IO uint32_t PWMLV1;
    __IO uint32_t PWMLV2;
    __IO uint32_t PWMLV3;
    __IO uint32_t PWMLV4;
    __IO uint32_t PWMLV5;
    __IO uint32_t PWMLV6;
    __IO uint32_t PWMLV7;
    uint32_t RESERVED0[10];
    __IO uint32_t NFEN1;
    uint32_t RESERVED1[2];
    __IO uint32_t NFEN2;
    uint32_t RESERVED2[2];
    __IO uint32_t NFEN3;
    uint32_t RESERVED3[2];
    __IO uint32_t NFEN4;
    uint32_t RESERVED4[4];
} stc_emb_ctl2_bit_t;

typedef struct {
    __IO uint32_t SOE;
    uint32_t RESERVED0[31];
} stc_emb_soe_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __I  uint32_t PWMSF;
    __I  uint32_t CMPF;
    __I  uint32_t OSF;
    uint32_t RESERVED1[1];
    __I  uint32_t PWMST;
    __I  uint32_t CMPST;
    __I  uint32_t OSST;
    __I  uint32_t PORTINF1;
    __I  uint32_t PORTINF2;
    __I  uint32_t PORTINF3;
    __I  uint32_t PORTINF4;
    uint32_t RESERVED2[2];
    __I  uint32_t PORTINST1;
    __I  uint32_t PORTINST2;
    __I  uint32_t PORTINST3;
    __I  uint32_t PORTINST4;
    uint32_t RESERVED3[14];
} stc_emb_stat_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __O  uint32_t PWMSFCLR;
    __O  uint32_t CMPFCLR;
    __O  uint32_t OSFCLR;
    uint32_t RESERVED1[4];
    __O  uint32_t PORTINFCLR1;
    __O  uint32_t PORTINFCLR2;
    __O  uint32_t PORTINFCLR3;
    __O  uint32_t PORTINFCLR4;
    uint32_t RESERVED2[20];
} stc_emb_statclr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t PWMSINTEN;
    __IO uint32_t CMPINTEN;
    __IO uint32_t OSINTEN;
    uint32_t RESERVED1[4];
    __IO uint32_t PORTININTEN1;
    __IO uint32_t PORTININTEN2;
    __IO uint32_t PORTININTEN3;
    __IO uint32_t PORTININTEN4;
    uint32_t RESERVED2[20];
} stc_emb_inten_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t PWMRSEL;
    __IO uint32_t CMPRSEL;
    __IO uint32_t OSRSEL;
    uint32_t RESERVED1[4];
    __IO uint32_t PORTINRSEL1;
    __IO uint32_t PORTINRSEL2;
    __IO uint32_t PORTINRSEL3;
    __IO uint32_t PORTINRSEL4;
    uint32_t RESERVED2[20];
} stc_emb_rlssel_bit_t;

typedef struct {
    __IO uint32_t IFSEL;
    uint32_t RESERVED0[3];
    __IO uint32_t RCKINV;
    __IO uint32_t TCKINV;
    uint32_t RESERVED1[26];
} stc_eth_mac_ifconfr_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t RE;
    __IO uint32_t TE;
    __IO uint32_t DC;
    uint32_t RESERVED1[2];
    __IO uint32_t ACS;
    uint32_t RESERVED2[1];
    __IO uint32_t DRTY;
    __IO uint32_t IPCO;
    __IO uint32_t DM;
    __IO uint32_t LM;
    __IO uint32_t DO;
    __IO uint32_t FES;
    uint32_t RESERVED3[1];
    __IO uint32_t DCRS;
    uint32_t RESERVED4[5];
    __IO uint32_t MJB;
    __IO uint32_t MWD;
    uint32_t RESERVED5[1];
    __IO uint32_t CST;
    uint32_t RESERVED6[6];
} stc_eth_mac_configr_bit_t;

typedef struct {
    __IO uint32_t PR;
    __IO uint32_t HUC;
    __IO uint32_t HMC;
    __IO uint32_t DAIF;
    __IO uint32_t PMF;
    __IO uint32_t DBF;
    uint32_t RESERVED0[2];
    __IO uint32_t SAIF;
    __IO uint32_t SAF;
    __IO uint32_t HPF;
    uint32_t RESERVED1[5];
    __IO uint32_t VTFE;
    uint32_t RESERVED2[3];
    __IO uint32_t IPFE;
    __IO uint32_t DNTU;
    uint32_t RESERVED3[9];
    __IO uint32_t RA;
} stc_eth_mac_fltctlr_bit_t;

typedef struct {
    __IO uint32_t SMIB;
    __IO uint32_t SMIW;
    uint32_t RESERVED0[30];
} stc_eth_mac_smiaddr_bit_t;

typedef struct {
    __IO uint32_t FCA_BPA;
    __IO uint32_t TFE;
    __IO uint32_t RFE;
    __IO uint32_t UNP;
    uint32_t RESERVED0[3];
    __IO uint32_t DZPQ;
    uint32_t RESERVED1[24];
} stc_eth_mac_floctlr_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t VTAL;
    __IO uint32_t VTIM;
    uint32_t RESERVED1[1];
    __IO uint32_t VTHM;
    uint32_t RESERVED2[12];
} stc_eth_mac_vtafltr_bit_t;

typedef struct {
    __I  uint32_t MREA;
    uint32_t RESERVED0[3];
    __I  uint32_t RFWA;
    uint32_t RESERVED1[11];
    __I  uint32_t MTEA;
    uint32_t RESERVED2[2];
    __I  uint32_t MTP;
    uint32_t RESERVED3[2];
    __I  uint32_t TFWA;
    uint32_t RESERVED4[1];
    __I  uint32_t TFNE;
    __I  uint32_t TFF;
    uint32_t RESERVED5[6];
} stc_eth_mac_macstsr_bit_t;

typedef struct {
    __IO uint32_t PWDN;
    __IO uint32_t MPEN;
    __IO uint32_t WKEN;
    uint32_t RESERVED0[2];
    __I  uint32_t MPFR;
    __I  uint32_t WKFR;
    uint32_t RESERVED1[2];
    __IO uint32_t GLUB;
    __IO uint32_t RTWKTR;
    uint32_t RESERVED2[20];
    __IO uint32_t RTWKFR;
} stc_eth_mac_pmtctlr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __I  uint32_t PMTIS;
    __I  uint32_t MMCIS;
    __I  uint32_t MMCRXIS;
    __I  uint32_t MMCTXIS;
    uint32_t RESERVED1[2];
    __I  uint32_t TSPIS;
    uint32_t RESERVED2[22];
} stc_eth_mac_intstsr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t PMTIM;
    uint32_t RESERVED1[5];
    __IO uint32_t TSPIM;
    uint32_t RESERVED2[22];
} stc_eth_mac_intmskr_bit_t;

typedef struct {
    uint32_t RESERVED0[31];
    __I  uint32_t AE0;
} stc_eth_mac_macadhr0_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t SA1;
    __IO uint32_t AE1;
} stc_eth_mac_macadhr1_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t SA2;
    __IO uint32_t AE2;
} stc_eth_mac_macadhr2_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t SA3;
    __IO uint32_t AE3;
} stc_eth_mac_macadhr3_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t SA4;
    __IO uint32_t AE4;
} stc_eth_mac_macadhr4_bit_t;

typedef struct {
    __IO uint32_t CRST;
    __IO uint32_t COS;
    __IO uint32_t ROR;
    __IO uint32_t MCF;
    __IO uint32_t MCPSET;
    __IO uint32_t MCPSEL;
    uint32_t RESERVED0[26];
} stc_eth_mmc_mmcctlr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __I  uint32_t RXBGIS;
    __I  uint32_t RXMGIS;
    __I  uint32_t RXCEIS;
    __I  uint32_t RXAEIS;
    __I  uint32_t RXREIS;
    uint32_t RESERVED1[9];
    __I  uint32_t RXUGIS;
    __I  uint32_t RXLEIS;
    __I  uint32_t RXOEIS;
    uint32_t RESERVED2[12];
} stc_eth_mmc_revstsr_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __I  uint32_t TXBGIS;
    __I  uint32_t TXMGIS;
    uint32_t RESERVED1[12];
    __I  uint32_t TXDEEIS;
    __I  uint32_t TXLCEIS;
    __I  uint32_t TXECEIS;
    __I  uint32_t TXCAEIS;
    uint32_t RESERVED2[1];
    __I  uint32_t TXUGIS;
    __I  uint32_t TXEDEIS;
    uint32_t RESERVED3[9];
} stc_eth_mmc_trsstsr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t RXBGIM;
    __IO uint32_t RXMGIM;
    __IO uint32_t RXCEIM;
    __IO uint32_t RXAEIM;
    __IO uint32_t RXREIM;
    uint32_t RESERVED1[9];
    __IO uint32_t RXUGIM;
    __IO uint32_t RXLEIM;
    __IO uint32_t RXOEIM;
    uint32_t RESERVED2[12];
} stc_eth_mmc_ritctlr_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t TXBGIM;
    __IO uint32_t TXMGIM;
    uint32_t RESERVED1[12];
    __IO uint32_t TXDEEIM;
    __IO uint32_t TXLCEIM;
    __IO uint32_t TXECEIM;
    __IO uint32_t TXCAEIM;
    uint32_t RESERVED2[1];
    __IO uint32_t TXUGIM;
    __IO uint32_t TXEDEIM;
    uint32_t RESERVED3[9];
} stc_eth_mmc_titctlr_bit_t;

typedef struct {
    __IO uint32_t L3PEN;
    uint32_t RESERVED0[1];
    __IO uint32_t L3SAM;
    __IO uint32_t L3SAIM;
    __IO uint32_t L3DAM;
    __IO uint32_t L3DAIM;
    uint32_t RESERVED1[10];
    __IO uint32_t L4PEN;
    uint32_t RESERVED2[1];
    __IO uint32_t L4SPM;
    __IO uint32_t L4SPIM;
    __IO uint32_t L4DPM;
    __IO uint32_t L4DPIM;
    uint32_t RESERVED3[10];
} stc_eth_mac_l34ctlr_bit_t;

typedef struct {
    uint32_t RESERVED0[18];
    __IO uint32_t VLANS;
    uint32_t RESERVED1[13];
} stc_eth_mac_vtactlr_bit_t;

typedef struct {
    __IO uint32_t TSPEN;
    __IO uint32_t TSPUPSEL;
    __IO uint32_t TSPINI;
    __IO uint32_t TSPUP;
    __IO uint32_t TSPINT;
    __IO uint32_t TSPADUP;
    uint32_t RESERVED0[2];
    __IO uint32_t TSPEALL;
    __IO uint32_t TSPSSR;
    __IO uint32_t TSPVER;
    __IO uint32_t TSPOVETH;
    __IO uint32_t TSPOVIPV6;
    __IO uint32_t TSPOVIPV4;
    uint32_t RESERVED1[4];
    __IO uint32_t TSPADF;
    uint32_t RESERVED2[13];
} stc_eth_ptp_tspctlr_bit_t;

typedef struct {
    uint32_t RESERVED0[31];
    __IO uint32_t TSPUPNS;
} stc_eth_ptp_tmunser_bit_t;

typedef struct {
    __I  uint32_t TSOVF;
    __I  uint32_t TSTAR0;
    uint32_t RESERVED0[1];
    __I  uint32_t TSERR0;
    __I  uint32_t TSTAR1;
    __I  uint32_t TSERR1;
    uint32_t RESERVED1[26];
} stc_eth_ptp_tspstsr_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t PPSOMD;
    uint32_t RESERVED1[27];
} stc_eth_ptp_ppsctlr_bit_t;

typedef struct {
    __IO uint32_t SWR;
    __IO uint32_t DMAA;
    uint32_t RESERVED0[5];
    __IO uint32_t DSEN;
    uint32_t RESERVED1[8];
    __IO uint32_t FBST;
    uint32_t RESERVED2[6];
    __IO uint32_t SPBL;
    __IO uint32_t M8PBL;
    __IO uint32_t AAL;
    __IO uint32_t MBST;
    __IO uint32_t TXPR;
    uint32_t RESERVED3[4];
} stc_eth_dma_busmodr_bit_t;

typedef struct {
    __IO uint32_t TIS;
    __IO uint32_t TSS;
    __IO uint32_t TUS;
    __IO uint32_t TJS;
    __IO uint32_t OVS;
    __IO uint32_t UNS;
    __IO uint32_t RIS;
    __IO uint32_t RUS;
    __IO uint32_t RSS;
    __IO uint32_t RWS;
    __IO uint32_t ETS;
    uint32_t RESERVED0[2];
    __IO uint32_t FBS;
    __IO uint32_t ERS;
    __IO uint32_t AIS;
    __IO uint32_t NIS;
    uint32_t RESERVED1[10];
    __I  uint32_t MMCS;
    __I  uint32_t PMTS;
    __I  uint32_t PTPS;
    uint32_t RESERVED2[2];
} stc_eth_dma_dmastsr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t STR;
    __IO uint32_t OSF;
    uint32_t RESERVED1[2];
    __IO uint32_t DGF;
    __IO uint32_t FUF;
    __IO uint32_t FEF;
    uint32_t RESERVED2[5];
    __IO uint32_t STT;
    uint32_t RESERVED3[6];
    __IO uint32_t FTF;
    __IO uint32_t TSF;
    uint32_t RESERVED4[2];
    __IO uint32_t DFRF;
    __IO uint32_t RSF;
    __IO uint32_t DTCOE;
    uint32_t RESERVED5[5];
} stc_eth_dma_oprmodr_bit_t;

typedef struct {
    __IO uint32_t TIE;
    __IO uint32_t TSE;
    __IO uint32_t TUE;
    __IO uint32_t TJE;
    __IO uint32_t OVE;
    __IO uint32_t UNE;
    __IO uint32_t RIE;
    __IO uint32_t RUE;
    __IO uint32_t RSE;
    __IO uint32_t RWE;
    __IO uint32_t ETE;
    uint32_t RESERVED0[2];
    __IO uint32_t FBE;
    __IO uint32_t ERE;
    __IO uint32_t AIE;
    __IO uint32_t NIE;
    uint32_t RESERVED1[15];
} stc_eth_dma_intenar_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __I  uint32_t UNAOVF;
    uint32_t RESERVED1[11];
    __I  uint32_t OVFOVF;
    uint32_t RESERVED2[3];
} stc_eth_dma_rfrcntr_bit_t;

typedef struct {
    __IO uint32_t START;
    uint32_t RESERVED0[31];
} stc_fcm_str_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t INEXS;
    uint32_t RESERVED1[7];
    __IO uint32_t EXREFE;
    uint32_t RESERVED2[16];
} stc_fcm_rccr_bit_t;

typedef struct {
    __IO uint32_t ERRIE;
    __IO uint32_t MENDIE;
    __IO uint32_t OVFIE;
    uint32_t RESERVED0[1];
    __IO uint32_t ERRINTRS;
    uint32_t RESERVED1[2];
    __IO uint32_t ERRE;
    uint32_t RESERVED2[24];
} stc_fcm_rier_bit_t;

typedef struct {
    __I  uint32_t ERRF;
    __I  uint32_t MENDF;
    __I  uint32_t OVF;
    uint32_t RESERVED0[29];
} stc_fcm_sr_bit_t;

typedef struct {
    __O  uint32_t ERRFCLR;
    __O  uint32_t MENDFCLR;
    __O  uint32_t OVFCLR;
    uint32_t RESERVED0[29];
} stc_fcm_clr_bit_t;

typedef struct {
    __IO uint32_t FMACEN;
    uint32_t RESERVED0[31];
} stc_fmac_enr_bit_t;

typedef struct {
    __IO uint32_t INTEN;
    uint32_t RESERVED0[31];
} stc_fmac_ier_bit_t;

typedef struct {
    uint32_t RESERVED0[31];
    __IO uint32_t READY;
} stc_fmac_str_bit_t;

typedef struct {
    __I  uint32_t PIN00;
    __I  uint32_t PIN01;
    __I  uint32_t PIN02;
    __I  uint32_t PIN03;
    __I  uint32_t PIN04;
    __I  uint32_t PIN05;
    __I  uint32_t PIN06;
    __I  uint32_t PIN07;
    __I  uint32_t PIN08;
    __I  uint32_t PIN09;
    __I  uint32_t PIN10;
    __I  uint32_t PIN11;
    __I  uint32_t PIN12;
    __I  uint32_t PIN13;
    __I  uint32_t PIN14;
    __I  uint32_t PIN15;
} stc_gpio_pidr_bit_t;

typedef struct {
    __IO uint32_t POUT00;
    __IO uint32_t POUT01;
    __IO uint32_t POUT02;
    __IO uint32_t POUT03;
    __IO uint32_t POUT04;
    __IO uint32_t POUT05;
    __IO uint32_t POUT06;
    __IO uint32_t POUT07;
    __IO uint32_t POUT08;
    __IO uint32_t POUT09;
    __IO uint32_t POUT10;
    __IO uint32_t POUT11;
    __IO uint32_t POUT12;
    __IO uint32_t POUT13;
    __IO uint32_t POUT14;
    __IO uint32_t POUT15;
} stc_gpio_podr_bit_t;

typedef struct {
    __IO uint32_t POUTE00;
    __IO uint32_t POUTE01;
    __IO uint32_t POUTE02;
    __IO uint32_t POUTE03;
    __IO uint32_t POUTE04;
    __IO uint32_t POUTE05;
    __IO uint32_t POUTE06;
    __IO uint32_t POUTE07;
    __IO uint32_t POUTE08;
    __IO uint32_t POUTE09;
    __IO uint32_t POUTE10;
    __IO uint32_t POUTE11;
    __IO uint32_t POUTE12;
    __IO uint32_t POUTE13;
    __IO uint32_t POUTE14;
    __IO uint32_t POUTE15;
} stc_gpio_poer_bit_t;

typedef struct {
    __O  uint32_t POS00;
    __O  uint32_t POS01;
    __O  uint32_t POS02;
    __O  uint32_t POS03;
    __O  uint32_t POS04;
    __O  uint32_t POS05;
    __O  uint32_t POS06;
    __O  uint32_t POS07;
    __O  uint32_t POS08;
    __O  uint32_t POS09;
    __O  uint32_t POS10;
    __O  uint32_t POS11;
    __O  uint32_t POS12;
    __O  uint32_t POS13;
    __O  uint32_t POS14;
    __O  uint32_t POS15;
} stc_gpio_posr_bit_t;

typedef struct {
    __O  uint32_t POR00;
    __O  uint32_t POR01;
    __O  uint32_t POR02;
    __O  uint32_t POR03;
    __O  uint32_t POR04;
    __O  uint32_t POR05;
    __O  uint32_t POR06;
    __O  uint32_t POR07;
    __O  uint32_t POR08;
    __O  uint32_t POR09;
    __O  uint32_t POR10;
    __O  uint32_t POR11;
    __O  uint32_t POR12;
    __O  uint32_t POR13;
    __O  uint32_t POR14;
    __O  uint32_t POR15;
} stc_gpio_porr_bit_t;

typedef struct {
    __O  uint32_t POT00;
    __O  uint32_t POT01;
    __O  uint32_t POT02;
    __O  uint32_t POT03;
    __O  uint32_t POT04;
    __O  uint32_t POT05;
    __O  uint32_t POT06;
    __O  uint32_t POT07;
    __O  uint32_t POT08;
    __O  uint32_t POT09;
    __O  uint32_t POT10;
    __O  uint32_t POT11;
    __O  uint32_t POT12;
    __O  uint32_t POT13;
    __O  uint32_t POT14;
    __O  uint32_t POT15;
} stc_gpio_potr_bit_t;

typedef struct {
    __I  uint32_t PIN00;
    __I  uint32_t PIN01;
    __I  uint32_t PIN02;
    __I  uint32_t PIN03;
    __I  uint32_t PIN04;
    __I  uint32_t PIN05;
    __I  uint32_t PIN06;
    __I  uint32_t PIN07;
    __I  uint32_t PIN08;
    __I  uint32_t PIN09;
    __I  uint32_t PIN10;
    __I  uint32_t PIN11;
    __I  uint32_t PIN12;
    __I  uint32_t PIN13;
    uint32_t RESERVED0[2];
} stc_gpio_pidri_bit_t;

typedef struct {
    __IO uint32_t POUT00;
    __IO uint32_t POUT01;
    __IO uint32_t POUT02;
    __IO uint32_t POUT03;
    __IO uint32_t POUT04;
    __IO uint32_t POUT05;
    __IO uint32_t POUT06;
    __IO uint32_t POUT07;
    __IO uint32_t POUT08;
    __IO uint32_t POUT09;
    __IO uint32_t POUT10;
    __IO uint32_t POUT11;
    __IO uint32_t POUT12;
    __IO uint32_t POUT13;
    uint32_t RESERVED0[2];
} stc_gpio_podri_bit_t;

typedef struct {
    __IO uint32_t POUTE00;
    __IO uint32_t POUTE01;
    __IO uint32_t POUTE02;
    __IO uint32_t POUTE03;
    __IO uint32_t POUTE04;
    __IO uint32_t POUTE05;
    __IO uint32_t POUTE06;
    __IO uint32_t POUTE07;
    __IO uint32_t POUTE08;
    __IO uint32_t POUTE09;
    __IO uint32_t POUTE10;
    __IO uint32_t POUTE11;
    __IO uint32_t POUTE12;
    __IO uint32_t POUTE13;
    uint32_t RESERVED0[2];
} stc_gpio_poeri_bit_t;

typedef struct {
    __O  uint32_t POS00;
    __O  uint32_t POS01;
    __O  uint32_t POS02;
    __O  uint32_t POS03;
    __O  uint32_t POS04;
    __O  uint32_t POS05;
    __O  uint32_t POS06;
    __O  uint32_t POS07;
    __O  uint32_t POS08;
    __O  uint32_t POS09;
    __O  uint32_t POS10;
    __O  uint32_t POS11;
    __O  uint32_t POS12;
    __O  uint32_t POS13;
    uint32_t RESERVED0[2];
} stc_gpio_posri_bit_t;

typedef struct {
    __O  uint32_t POR00;
    __O  uint32_t POR01;
    __O  uint32_t POR02;
    __O  uint32_t POR03;
    __O  uint32_t POR04;
    __O  uint32_t POR05;
    __O  uint32_t POR06;
    __O  uint32_t POR07;
    __O  uint32_t POR08;
    __O  uint32_t POR09;
    __O  uint32_t POR10;
    __O  uint32_t POR11;
    __O  uint32_t POR12;
    __O  uint32_t POR13;
    uint32_t RESERVED0[2];
} stc_gpio_porri_bit_t;

typedef struct {
    __O  uint32_t POT00;
    __O  uint32_t POT01;
    __O  uint32_t POT02;
    __O  uint32_t POT03;
    __O  uint32_t POT04;
    __O  uint32_t POT05;
    __O  uint32_t POT06;
    __O  uint32_t POT07;
    __O  uint32_t POT08;
    __O  uint32_t POT09;
    __O  uint32_t POT10;
    __O  uint32_t POT11;
    __O  uint32_t POT12;
    __O  uint32_t POT13;
    uint32_t RESERVED0[2];
} stc_gpio_potri_bit_t;

typedef struct {
    __IO uint32_t WE;
    uint32_t RESERVED0[15];
} stc_gpio_pwpr_bit_t;

typedef struct {
    __IO uint32_t POUT;
    __IO uint32_t POUTE;
    __IO uint32_t NOD;
    uint32_t RESERVED0[3];
    __IO uint32_t PUU;
    uint32_t RESERVED1[1];
    __I  uint32_t PIN;
    __IO uint32_t INVE;
    __IO uint32_t CINSEL;
    uint32_t RESERVED2[1];
    __IO uint32_t INTE;
    uint32_t RESERVED3[1];
    __IO uint32_t LTE;
    __IO uint32_t DDIS;
} stc_gpio_pcr_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t BFE;
    uint32_t RESERVED1[7];
} stc_gpio_pfsr_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t FST_GRP;
    __IO uint32_t KMSG_END;
    uint32_t RESERVED0[3];
    __IO uint32_t LKEY;
    uint32_t RESERVED1[1];
    __IO uint32_t BUSY;
    __IO uint32_t CYC_END;
    __IO uint32_t HMAC_END;
    uint32_t RESERVED2[3];
    __IO uint32_t HCIE;
    __IO uint32_t HEIE;
    uint32_t RESERVED3[16];
} stc_hash_cr_bit_t;

typedef struct {
    uint32_t RESERVED0[29];
    __IO uint32_t NE;
    __IO uint32_t PE;
    __IO uint32_t EN;
} stc_hrpwm_cr_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t ENDF;
    uint32_t RESERVED1[2];
    __IO uint32_t CALEN;
    uint32_t RESERVED2[16];
} stc_hrpwm_calcr_bit_t;

typedef struct {
    __IO uint32_t PE;
    __IO uint32_t SMBUS;
    __IO uint32_t SMBALRTEN;
    __IO uint32_t SMBDEFAULTEN;
    __IO uint32_t SMBHOSTEN;
    uint32_t RESERVED0[1];
    __IO uint32_t ENGC;
    __IO uint32_t RESTART;
    __IO uint32_t START;
    __IO uint32_t STOP;
    __IO uint32_t ACK;
    uint32_t RESERVED1[4];
    __IO uint32_t SWRST;
    uint32_t RESERVED2[16];
} stc_i2c_cr1_bit_t;

typedef struct {
    __IO uint32_t STARTIE;
    __IO uint32_t SLADDR0IE;
    __IO uint32_t SLADDR1IE;
    __IO uint32_t TENDIE;
    __IO uint32_t STOPIE;
    uint32_t RESERVED0[1];
    __IO uint32_t RFULLIE;
    __IO uint32_t TEMPTYIE;
    uint32_t RESERVED1[1];
    __IO uint32_t ARLOIE;
    uint32_t RESERVED2[2];
    __IO uint32_t NACKIE;
    uint32_t RESERVED3[1];
    __IO uint32_t TMOUTIE;
    uint32_t RESERVED4[5];
    __IO uint32_t GENCALLIE;
    __IO uint32_t SMBDEFAULTIE;
    __IO uint32_t SMBHOSTIE;
    __IO uint32_t SMBALRTIE;
    uint32_t RESERVED5[8];
} stc_i2c_cr2_bit_t;

typedef struct {
    __IO uint32_t TMOUTEN;
    __IO uint32_t LTMOUT;
    __IO uint32_t HTMOUT;
    uint32_t RESERVED0[4];
    __IO uint32_t FACKEN;
    uint32_t RESERVED1[24];
} stc_i2c_cr3_bit_t;

typedef struct {
    uint32_t RESERVED0[10];
    __IO uint32_t BUSWAIT;
    uint32_t RESERVED1[21];
} stc_i2c_cr4_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t SLADDR0EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD0;
    uint32_t RESERVED2[16];
} stc_i2c_slr0_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t SLADDR1EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD1;
    uint32_t RESERVED2[16];
} stc_i2c_slr1_bit_t;

typedef struct {
    __IO uint32_t STARTF;
    __IO uint32_t SLADDR0F;
    __IO uint32_t SLADDR1F;
    __IO uint32_t TENDF;
    __IO uint32_t STOPF;
    uint32_t RESERVED0[1];
    __IO uint32_t RFULLF;
    __IO uint32_t TEMPTYF;
    uint32_t RESERVED1[1];
    __IO uint32_t ARLOF;
    __IO uint32_t ACKRF;
    uint32_t RESERVED2[1];
    __IO uint32_t NACKF;
    uint32_t RESERVED3[1];
    __IO uint32_t TMOUTF;
    uint32_t RESERVED4[1];
    __IO uint32_t MSL;
    __IO uint32_t BUSY;
    __IO uint32_t TRA;
    uint32_t RESERVED5[1];
    __IO uint32_t GENCALLF;
    __IO uint32_t SMBDEFAULTF;
    __IO uint32_t SMBHOSTF;
    __IO uint32_t SMBALRTF;
    uint32_t RESERVED6[8];
} stc_i2c_sr_bit_t;

typedef struct {
    __O  uint32_t STARTFCLR;
    __O  uint32_t SLADDR0FCLR;
    __O  uint32_t SLADDR1FCLR;
    __O  uint32_t TENDFCLR;
    __O  uint32_t STOPFCLR;
    uint32_t RESERVED0[1];
    __O  uint32_t RFULLFCLR;
    __O  uint32_t TEMPTYFCLR;
    uint32_t RESERVED1[1];
    __O  uint32_t ARLOFCLR;
    uint32_t RESERVED2[2];
    __O  uint32_t NACKFCLR;
    uint32_t RESERVED3[1];
    __O  uint32_t TMOUTFCLR;
    uint32_t RESERVED4[5];
    __O  uint32_t GENCALLFCLR;
    __O  uint32_t SMBDEFAULTFCLR;
    __O  uint32_t SMBHOSTFCLR;
    __O  uint32_t SMBALRTFCLR;
    uint32_t RESERVED5[8];
} stc_i2c_clr_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t DNFEN;
    __IO uint32_t ANFEN;
    uint32_t RESERVED1[26];
} stc_i2c_fltr_bit_t;

typedef struct {
    __IO uint32_t TXE;
    __IO uint32_t TXIE;
    __IO uint32_t RXE;
    __IO uint32_t RXIE;
    __IO uint32_t EIE;
    __IO uint32_t WMS;
    __IO uint32_t ODD;
    __IO uint32_t MCKOE;
    uint32_t RESERVED0[8];
    __IO uint32_t FIFOR;
    __IO uint32_t CODECRC;
    __IO uint32_t I2SPLLSEL;
    __IO uint32_t SDOE;
    __IO uint32_t LRCKOE;
    __IO uint32_t CKOE;
    __IO uint32_t DUPLEX;
    __IO uint32_t CLKSEL;
    __IO uint32_t SRST;
    uint32_t RESERVED1[7];
} stc_i2s_ctrl_bit_t;

typedef struct {
    __I  uint32_t TXBA;
    __I  uint32_t RXBA;
    __I  uint32_t TXBE;
    __I  uint32_t TXBF;
    __I  uint32_t RXBE;
    __I  uint32_t RXBF;
    uint32_t RESERVED0[26];
} stc_i2s_sr_bit_t;

typedef struct {
    __IO uint32_t TXERR;
    __IO uint32_t RXERR;
    uint32_t RESERVED0[30];
} stc_i2s_er_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t CHLEN;
    __IO uint32_t PCMSYNC;
    uint32_t RESERVED1[26];
} stc_i2s_cfgr_bit_t;

typedef struct {
    __I  uint32_t SWDTAUTS;
    __I  uint32_t SWDTITS;
    uint32_t RESERVED0[10];
    __I  uint32_t SWDTSLPOFF;
    uint32_t RESERVED1[3];
    __I  uint32_t WDTAUTS;
    __I  uint32_t WDTITS;
    uint32_t RESERVED2[10];
    __I  uint32_t WDTSLPOFF;
    uint32_t RESERVED3[3];
} stc_icg_icg0_bit_t;

typedef struct {
    __I  uint32_t HRCFREQSEL;
    uint32_t RESERVED0[7];
    __I  uint32_t HRCSTOP;
    uint32_t RESERVED1[9];
    __I  uint32_t BORDIS;
    uint32_t RESERVED2[13];
} stc_icg_icg1_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SWDTENR;
    __IO uint32_t PVD1ENR;
    __IO uint32_t PVD2ENR;
    uint32_t RESERVED1[1];
    __IO uint32_t XTALSTPENR;
    uint32_t RESERVED2[2];
    __IO uint32_t REPENR;
    __IO uint32_t RECCENR;
    __IO uint32_t BUSMENR;
    __IO uint32_t WDTENR;
    uint32_t RESERVED3[20];
} stc_intc_nmienr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SWDTFR;
    __IO uint32_t PVD1FR;
    __IO uint32_t PVD2FR;
    uint32_t RESERVED1[1];
    __IO uint32_t XTALSTPFR;
    uint32_t RESERVED2[2];
    __IO uint32_t REPFR;
    __IO uint32_t RECCFR;
    __IO uint32_t BUSMFR;
    __IO uint32_t WDTFR;
    uint32_t RESERVED3[20];
} stc_intc_nmifr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SWDTCFR;
    __IO uint32_t PVD1CFR;
    __IO uint32_t PVD2CFR;
    uint32_t RESERVED1[1];
    __IO uint32_t XTALSTPCFR;
    uint32_t RESERVED2[2];
    __IO uint32_t REPCFR;
    __IO uint32_t RECCCFR;
    __IO uint32_t BUSMCFR;
    __IO uint32_t WDTCFR;
    uint32_t RESERVED3[20];
} stc_intc_nmicfr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t EFEN;
    uint32_t RESERVED1[7];
    __IO uint32_t NOCEN;
    uint32_t RESERVED2[16];
} stc_intc_eirqcr_bit_t;

typedef struct {
    __IO uint32_t EIRQWUEN0;
    __IO uint32_t EIRQWUEN1;
    __IO uint32_t EIRQWUEN2;
    __IO uint32_t EIRQWUEN3;
    __IO uint32_t EIRQWUEN4;
    __IO uint32_t EIRQWUEN5;
    __IO uint32_t EIRQWUEN6;
    __IO uint32_t EIRQWUEN7;
    __IO uint32_t EIRQWUEN8;
    __IO uint32_t EIRQWUEN9;
    __IO uint32_t EIRQWUEN10;
    __IO uint32_t EIRQWUEN11;
    __IO uint32_t EIRQWUEN12;
    __IO uint32_t EIRQWUEN13;
    __IO uint32_t EIRQWUEN14;
    __IO uint32_t EIRQWUEN15;
    __IO uint32_t SWDTWUEN;
    __IO uint32_t PVD1WUEN;
    __IO uint32_t PVD2WUEN;
    __IO uint32_t CMPWUEN;
    __IO uint32_t WKTMWUEN;
    __IO uint32_t RTCALMWUEN;
    __IO uint32_t RTCPRDWUEN;
    __IO uint32_t TMR0GCMWUEN;
    __IO uint32_t TMR2GCMWUEN;
    __IO uint32_t TMR2OVFWUEN;
    __IO uint32_t RXWUEN;
    __IO uint32_t USHWUEN;
    __IO uint32_t USFWUEN;
    __IO uint32_t ETHWUEN;
    uint32_t RESERVED0[2];
} stc_intc_wupen_bit_t;

typedef struct {
    __IO uint32_t EIFR0;
    __IO uint32_t EIFR1;
    __IO uint32_t EIFR2;
    __IO uint32_t EIFR3;
    __IO uint32_t EIFR4;
    __IO uint32_t EIFR5;
    __IO uint32_t EIFR6;
    __IO uint32_t EIFR7;
    __IO uint32_t EIFR8;
    __IO uint32_t EIFR9;
    __IO uint32_t EIFR10;
    __IO uint32_t EIFR11;
    __IO uint32_t EIFR12;
    __IO uint32_t EIFR13;
    __IO uint32_t EIFR14;
    __IO uint32_t EIFR15;
    uint32_t RESERVED0[16];
} stc_intc_eifr_bit_t;

typedef struct {
    __IO uint32_t EIFCR0;
    __IO uint32_t EIFCR1;
    __IO uint32_t EIFCR2;
    __IO uint32_t EIFCR3;
    __IO uint32_t EIFCR4;
    __IO uint32_t EIFCR5;
    __IO uint32_t EIFCR6;
    __IO uint32_t EIFCR7;
    __IO uint32_t EIFCR8;
    __IO uint32_t EIFCR9;
    __IO uint32_t EIFCR10;
    __IO uint32_t EIFCR11;
    __IO uint32_t EIFCR12;
    __IO uint32_t EIFCR13;
    __IO uint32_t EIFCR14;
    __IO uint32_t EIFCR15;
    uint32_t RESERVED0[16];
} stc_intc_eifcr_bit_t;

typedef struct {
    __IO uint32_t VSEL0;
    __IO uint32_t VSEL1;
    __IO uint32_t VSEL2;
    __IO uint32_t VSEL3;
    __IO uint32_t VSEL4;
    __IO uint32_t VSEL5;
    __IO uint32_t VSEL6;
    __IO uint32_t VSEL7;
    __IO uint32_t VSEL8;
    __IO uint32_t VSEL9;
    __IO uint32_t VSEL10;
    __IO uint32_t VSEL11;
    __IO uint32_t VSEL12;
    __IO uint32_t VSEL13;
    __IO uint32_t VSEL14;
    __IO uint32_t VSEL15;
    __IO uint32_t VSEL16;
    __IO uint32_t VSEL17;
    __IO uint32_t VSEL18;
    __IO uint32_t VSEL19;
    __IO uint32_t VSEL20;
    __IO uint32_t VSEL21;
    __IO uint32_t VSEL22;
    __IO uint32_t VSEL23;
    __IO uint32_t VSEL24;
    __IO uint32_t VSEL25;
    __IO uint32_t VSEL26;
    __IO uint32_t VSEL27;
    __IO uint32_t VSEL28;
    __IO uint32_t VSEL29;
    __IO uint32_t VSEL30;
    __IO uint32_t VSEL31;
} stc_intc_vssel_bit_t;

typedef struct {
    __IO uint32_t SWIE0;
    __IO uint32_t SWIE1;
    __IO uint32_t SWIE2;
    __IO uint32_t SWIE3;
    __IO uint32_t SWIE4;
    __IO uint32_t SWIE5;
    __IO uint32_t SWIE6;
    __IO uint32_t SWIE7;
    __IO uint32_t SWIE8;
    __IO uint32_t SWIE9;
    __IO uint32_t SWIE10;
    __IO uint32_t SWIE11;
    __IO uint32_t SWIE12;
    __IO uint32_t SWIE13;
    __IO uint32_t SWIE14;
    __IO uint32_t SWIE15;
    __IO uint32_t SWIE16;
    __IO uint32_t SWIE17;
    __IO uint32_t SWIE18;
    __IO uint32_t SWIE19;
    __IO uint32_t SWIE20;
    __IO uint32_t SWIE21;
    __IO uint32_t SWIE22;
    __IO uint32_t SWIE23;
    __IO uint32_t SWIE24;
    __IO uint32_t SWIE25;
    __IO uint32_t SWIE26;
    __IO uint32_t SWIE27;
    __IO uint32_t SWIE28;
    __IO uint32_t SWIE29;
    __IO uint32_t SWIE30;
    __IO uint32_t SWIE31;
} stc_intc_swier_bit_t;

typedef struct {
    __IO uint32_t EVTE0;
    __IO uint32_t EVTE1;
    __IO uint32_t EVTE2;
    __IO uint32_t EVTE3;
    __IO uint32_t EVTE4;
    __IO uint32_t EVTE5;
    __IO uint32_t EVTE6;
    __IO uint32_t EVTE7;
    __IO uint32_t EVTE8;
    __IO uint32_t EVTE9;
    __IO uint32_t EVTE10;
    __IO uint32_t EVTE11;
    __IO uint32_t EVTE12;
    __IO uint32_t EVTE13;
    __IO uint32_t EVTE14;
    __IO uint32_t EVTE15;
    __IO uint32_t EVTE16;
    __IO uint32_t EVTE17;
    __IO uint32_t EVTE18;
    __IO uint32_t EVTE19;
    __IO uint32_t EVTE20;
    __IO uint32_t EVTE21;
    __IO uint32_t EVTE22;
    __IO uint32_t EVTE23;
    __IO uint32_t EVTE24;
    __IO uint32_t EVTE25;
    __IO uint32_t EVTE26;
    __IO uint32_t EVTE27;
    __IO uint32_t EVTE28;
    __IO uint32_t EVTE29;
    __IO uint32_t EVTE30;
    __IO uint32_t EVTE31;
} stc_intc_evter_bit_t;

typedef struct {
    __IO uint32_t IER0;
    __IO uint32_t IER1;
    __IO uint32_t IER2;
    __IO uint32_t IER3;
    __IO uint32_t IER4;
    __IO uint32_t IER5;
    __IO uint32_t IER6;
    __IO uint32_t IER7;
    __IO uint32_t IER8;
    __IO uint32_t IER9;
    __IO uint32_t IER10;
    __IO uint32_t IER11;
    __IO uint32_t IER12;
    __IO uint32_t IER13;
    __IO uint32_t IER14;
    __IO uint32_t IER15;
    __IO uint32_t IER16;
    __IO uint32_t IER17;
    __IO uint32_t IER18;
    __IO uint32_t IER19;
    __IO uint32_t IER20;
    __IO uint32_t IER21;
    __IO uint32_t IER22;
    __IO uint32_t IER23;
    __IO uint32_t IER24;
    __IO uint32_t IER25;
    __IO uint32_t IER26;
    __IO uint32_t IER27;
    __IO uint32_t IER28;
    __IO uint32_t IER29;
    __IO uint32_t IER30;
    __IO uint32_t IER31;
} stc_intc_ier_bit_t;

typedef struct {
    __IO uint32_t SEN;
    uint32_t RESERVED0[31];
} stc_keyscan_ser_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t INTEN;
    uint32_t RESERVED0[1];
    __IO uint32_t BUSY;
    uint32_t RESERVED1[28];
} stc_mau_csr_bit_t;

typedef struct {
    __I  uint32_t SMPU1EAF;
    __I  uint32_t SMPU2EAF;
    __I  uint32_t FMPUEAF;
    __I  uint32_t HMPUEAF;
    __I  uint32_t EMPUEAF;
    uint32_t RESERVED0[27];
} stc_mpu_sr_bit_t;

typedef struct {
    __O  uint32_t SMPU1ECLR;
    __O  uint32_t SMPU2ECLR;
    __O  uint32_t FMPUECLR;
    __O  uint32_t HMPUECLR;
    __O  uint32_t EMPUECLR;
    uint32_t RESERVED0[27];
} stc_mpu_eclr_bit_t;

typedef struct {
    __IO uint32_t MPUWE;
    uint32_t RESERVED0[31];
} stc_mpu_wp_bit_t;

typedef struct {
    __IO uint32_t AESRDP;
    __IO uint32_t AESWRP;
    __IO uint32_t HASHRDP;
    __IO uint32_t HASHWRP;
    __IO uint32_t TRNGRDP;
    __IO uint32_t TRNGWRP;
    __IO uint32_t CRCRDP;
    __IO uint32_t CRCWRP;
    __IO uint32_t EFMRDP;
    __IO uint32_t EFMWRP;
    uint32_t RESERVED0[2];
    __IO uint32_t WDTRDP;
    __IO uint32_t WDTWRP;
    __IO uint32_t SWDTRDP;
    __IO uint32_t SWDTWRP;
    __IO uint32_t BKSRAMRDP;
    __IO uint32_t BKSRAMWRP;
    __IO uint32_t RTCRDP;
    __IO uint32_t RTCWRP;
    __IO uint32_t DMPURDP;
    __IO uint32_t DMPUWRP;
    __IO uint32_t SRAMCRDP;
    __IO uint32_t SRAMCWRP;
    __IO uint32_t INTCRDP;
    __IO uint32_t INTCWRP;
    __IO uint32_t SYSCRDP;
    __IO uint32_t SYSCWRP;
    __IO uint32_t MSTPRDP;
    __IO uint32_t MSPTWRP;
    uint32_t RESERVED1[1];
    __IO uint32_t BUSERRE;
} stc_mpu_ippr_bit_t;

typedef struct {
    __IO uint32_t RG0E;
    __IO uint32_t RG1E;
    __IO uint32_t RG2E;
    __IO uint32_t RG3E;
    __IO uint32_t RG4E;
    __IO uint32_t RG5E;
    __IO uint32_t RG6E;
    __IO uint32_t RG7E;
    __IO uint32_t RG8E;
    __IO uint32_t RG9E;
    __IO uint32_t RG10E;
    __IO uint32_t RG11E;
    __IO uint32_t RG12E;
    __IO uint32_t RG13E;
    __IO uint32_t RG14E;
    __IO uint32_t RG15E;
    uint32_t RESERVED0[16];
} stc_mpu_srge_bit_t;

typedef struct {
    __IO uint32_t RG0WP;
    __IO uint32_t RG1WP;
    __IO uint32_t RG2WP;
    __IO uint32_t RG3WP;
    __IO uint32_t RG4WP;
    __IO uint32_t RG5WP;
    __IO uint32_t RG6WP;
    __IO uint32_t RG7WP;
    __IO uint32_t RG8WP;
    __IO uint32_t RG9WP;
    __IO uint32_t RG10WP;
    __IO uint32_t RG11WP;
    __IO uint32_t RG12WP;
    __IO uint32_t RG13WP;
    __IO uint32_t RG14WP;
    __IO uint32_t RG15WP;
    uint32_t RESERVED0[16];
} stc_mpu_srgwp_bit_t;

typedef struct {
    __IO uint32_t RG0RP;
    __IO uint32_t RG1RP;
    __IO uint32_t RG2RP;
    __IO uint32_t RG3RP;
    __IO uint32_t RG4RP;
    __IO uint32_t RG5RP;
    __IO uint32_t RG6RP;
    __IO uint32_t RG7RP;
    __IO uint32_t RG8RP;
    __IO uint32_t RG9RP;
    __IO uint32_t RG10RP;
    __IO uint32_t RG11RP;
    __IO uint32_t RG12RP;
    __IO uint32_t RG13RP;
    __IO uint32_t RG14RP;
    __IO uint32_t RG15RP;
    uint32_t RESERVED0[16];
} stc_mpu_srgrp_bit_t;

typedef struct {
    __IO uint32_t SMPUBRP;
    __IO uint32_t SMPUBWP;
    uint32_t RESERVED0[5];
    __IO uint32_t SMPUE;
    uint32_t RESERVED1[24];
} stc_mpu_scr_bit_t;

typedef struct {
    __IO uint32_t FRG0E;
    __IO uint32_t FRG1E;
    __IO uint32_t FRG2E;
    __IO uint32_t FRG3E;
    __IO uint32_t FRG4E;
    __IO uint32_t FRG5E;
    __IO uint32_t FRG6E;
    __IO uint32_t FRG7E;
    uint32_t RESERVED0[24];
} stc_mpu_frge_bit_t;

typedef struct {
    __IO uint32_t FRG0WP;
    __IO uint32_t FRG1WP;
    __IO uint32_t FRG2WP;
    __IO uint32_t FRG3WP;
    __IO uint32_t FRG4WP;
    __IO uint32_t FRG5WP;
    __IO uint32_t FRG6WP;
    __IO uint32_t FRG7WP;
    uint32_t RESERVED0[24];
} stc_mpu_frgwp_bit_t;

typedef struct {
    __IO uint32_t FRG0RP;
    __IO uint32_t FRG1RP;
    __IO uint32_t FRG2RP;
    __IO uint32_t FRG3RP;
    __IO uint32_t FRG4RP;
    __IO uint32_t FRG5RP;
    __IO uint32_t FRG6RP;
    __IO uint32_t FRG7RP;
    uint32_t RESERVED0[24];
} stc_mpu_frgrp_bit_t;

typedef struct {
    __IO uint32_t FMPUBRP;
    __IO uint32_t FMPUBWP;
    uint32_t RESERVED0[5];
    __IO uint32_t FMPUE;
    uint32_t RESERVED1[24];
} stc_mpu_fcr_bit_t;

typedef struct {
    __IO uint32_t HRG0E;
    __IO uint32_t HRG1E;
    __IO uint32_t HRG2E;
    __IO uint32_t HRG3E;
    __IO uint32_t HRG4E;
    __IO uint32_t HRG5E;
    __IO uint32_t HRG6E;
    __IO uint32_t HRG7E;
    uint32_t RESERVED0[24];
} stc_mpu_hrge_bit_t;

typedef struct {
    __IO uint32_t HRG0WP;
    __IO uint32_t HRG1WP;
    __IO uint32_t HRG2WP;
    __IO uint32_t HRG3WP;
    __IO uint32_t HRG4WP;
    __IO uint32_t HRG5WP;
    __IO uint32_t HRG6WP;
    __IO uint32_t HRG7WP;
    uint32_t RESERVED0[24];
} stc_mpu_hrgwp_bit_t;

typedef struct {
    __IO uint32_t HRG0RP;
    __IO uint32_t HRG1RP;
    __IO uint32_t HRG2RP;
    __IO uint32_t HRG3RP;
    __IO uint32_t HRG4RP;
    __IO uint32_t HRG5RP;
    __IO uint32_t HRG6RP;
    __IO uint32_t HRG7RP;
    uint32_t RESERVED0[24];
} stc_mpu_hrgrp_bit_t;

typedef struct {
    __IO uint32_t HMPUBRP;
    __IO uint32_t HMPUBWP;
    uint32_t RESERVED0[5];
    __IO uint32_t HMPUE;
    uint32_t RESERVED1[24];
} stc_mpu_hcr_bit_t;

typedef struct {
    __IO uint32_t ERG0E;
    __IO uint32_t ERG1E;
    __IO uint32_t ERG2E;
    __IO uint32_t ERG3E;
    __IO uint32_t ERG4E;
    __IO uint32_t ERG5E;
    __IO uint32_t ERG6E;
    __IO uint32_t ERG7E;
    uint32_t RESERVED0[24];
} stc_mpu_erge_bit_t;

typedef struct {
    __IO uint32_t ERG0WP;
    __IO uint32_t ERG1WP;
    __IO uint32_t ERG2WP;
    __IO uint32_t ERG3WP;
    __IO uint32_t ERG4WP;
    __IO uint32_t ERG5WP;
    __IO uint32_t ERG6WP;
    __IO uint32_t ERG7WP;
    uint32_t RESERVED0[24];
} stc_mpu_ergwp_bit_t;

typedef struct {
    __IO uint32_t ERG0RP;
    __IO uint32_t ERG1RP;
    __IO uint32_t ERG2RP;
    __IO uint32_t ERG3RP;
    __IO uint32_t ERG4RP;
    __IO uint32_t ERG5RP;
    __IO uint32_t ERG6RP;
    __IO uint32_t ERG7RP;
    uint32_t RESERVED0[24];
} stc_mpu_ergrp_bit_t;

typedef struct {
    __IO uint32_t EMPUBRP;
    __IO uint32_t EMPUBWP;
    uint32_t RESERVED0[5];
    __IO uint32_t EMPUE;
    uint32_t RESERVED1[24];
} stc_mpu_ecr_bit_t;

typedef struct {
    __IO uint32_t OTSST;
    __IO uint32_t OTSCK;
    __IO uint32_t OTSIE;
    __IO uint32_t TSSTP;
    uint32_t RESERVED0[12];
} stc_ots_ctl_bit_t;

typedef struct {
    __IO uint32_t USBFS_DFB;
    __IO uint32_t USBFS_SOFEN;
    uint32_t RESERVED0[6];
    __IO uint32_t USBHS_DFB;
    __IO uint32_t USBHS_SOFEN;
    __IO uint32_t USBHS_FSPHYE;
    uint32_t RESERVED1[7];
    __IO uint32_t USBFS_NFE;
    uint32_t RESERVED2[7];
    __IO uint32_t USBHS_NFE;
    uint32_t RESERVED3[5];
} stc_peric_usb_syctlreg_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SELMMC1;
    uint32_t RESERVED1[1];
    __IO uint32_t SELMMC2;
    uint32_t RESERVED2[28];
} stc_peric_sdioc_syctlreg_bit_t;

typedef struct {
    __IO uint32_t OPENP;
    uint32_t RESERVED0[31];
} stc_peric_nfc_stcr_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t NFCEN;
    uint32_t RESERVED1[29];
} stc_peric_nfc_enar_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SMCEN;
    uint32_t RESERVED1[30];
} stc_peric_smc_enar_bit_t;

typedef struct {
    __IO uint32_t DMCEN;
    uint32_t RESERVED0[31];
} stc_peric_dmc_enar_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t USART1_NFE;
    uint32_t RESERVED1[29];
} stc_peric_usart1_nfc_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __I  uint32_t PECC;
    uint32_t RESERVED1[23];
} stc_peric_nfc_stsr_bit_t;

typedef struct {
    __IO uint32_t SRAMH;
    uint32_t RESERVED0[3];
    __IO uint32_t SRAM1;
    __IO uint32_t SRAM2;
    __IO uint32_t SRAM3;
    __IO uint32_t SRAM4;
    uint32_t RESERVED1[2];
    __IO uint32_t SRAMB;
    uint32_t RESERVED2[2];
    __IO uint32_t KEY;
    __IO uint32_t DMA1;
    __IO uint32_t DMA2;
    __IO uint32_t FCM;
    __IO uint32_t AOS;
    __IO uint32_t CTC;
    __IO uint32_t MAU;
    __IO uint32_t AES;
    __IO uint32_t HASH;
    __IO uint32_t TRNG;
    __IO uint32_t CRC;
    __IO uint32_t DCU1;
    __IO uint32_t DCU2;
    __IO uint32_t DCU3;
    __IO uint32_t DCU4;
    __IO uint32_t DCU5;
    __IO uint32_t DCU6;
    __IO uint32_t DCU7;
    __IO uint32_t DCU8;
} stc_pwc_fcg0_bit_t;

typedef struct {
    __IO uint32_t CAN1;
    __IO uint32_t CAN2;
    __IO uint32_t ETHMAC;
    __IO uint32_t QSPI;
    __IO uint32_t I2C1;
    __IO uint32_t I2C2;
    __IO uint32_t I2C3;
    __IO uint32_t I2C4;
    __IO uint32_t I2C5;
    __IO uint32_t I2C6;
    __IO uint32_t SDIOC1;
    __IO uint32_t SDIOC2;
    __IO uint32_t I2S1;
    __IO uint32_t I2S2;
    __IO uint32_t I2S3;
    __IO uint32_t I2S4;
    __IO uint32_t SPI1;
    __IO uint32_t SPI2;
    __IO uint32_t SPI3;
    __IO uint32_t SPI4;
    __IO uint32_t SPI5;
    __IO uint32_t SPI6;
    __IO uint32_t USBFS;
    __IO uint32_t USBHS;
    __IO uint32_t FMAC1;
    __IO uint32_t FMAC2;
    __IO uint32_t FMAC3;
    __IO uint32_t FMAC4;
    uint32_t RESERVED0[4];
} stc_pwc_fcg1_bit_t;

typedef struct {
    __IO uint32_t TMR6_1;
    __IO uint32_t TMR6_2;
    __IO uint32_t TMR6_3;
    __IO uint32_t TMR6_4;
    __IO uint32_t TMR6_5;
    __IO uint32_t TMR6_6;
    __IO uint32_t TMR6_7;
    __IO uint32_t TMR6_8;
    __IO uint32_t TMR4_1;
    __IO uint32_t TMR4_2;
    __IO uint32_t TMR4_3;
    __IO uint32_t HRPWM;
    __IO uint32_t TMR0_1;
    __IO uint32_t TMR0_2;
    uint32_t RESERVED0[1];
    __IO uint32_t EMB;
    __IO uint32_t TMR2_1;
    __IO uint32_t TMR2_2;
    __IO uint32_t TMR2_3;
    __IO uint32_t TMR2_4;
    __IO uint32_t TMRA_1;
    __IO uint32_t TMRA_2;
    __IO uint32_t TMRA_3;
    __IO uint32_t TMRA_4;
    __IO uint32_t TMRA_5;
    __IO uint32_t TMRA_6;
    __IO uint32_t TMRA_7;
    __IO uint32_t TMRA_8;
    __IO uint32_t TMRA_9;
    __IO uint32_t TMRA_10;
    __IO uint32_t TMRA_11;
    __IO uint32_t TMRA_12;
} stc_pwc_fcg2_bit_t;

typedef struct {
    __IO uint32_t ADC1;
    __IO uint32_t ADC2;
    __IO uint32_t ADC3;
    __IO uint32_t CMBIAS;
    __IO uint32_t DAC1;
    __IO uint32_t DAC2;
    uint32_t RESERVED0[2];
    __IO uint32_t CMP12;
    __IO uint32_t CMP34;
    uint32_t RESERVED1[2];
    __IO uint32_t OTS;
    uint32_t RESERVED2[2];
    __IO uint32_t DVP;
    __IO uint32_t SMC;
    __IO uint32_t DMC;
    __IO uint32_t NFC;
    uint32_t RESERVED3[1];
    __IO uint32_t USART1;
    __IO uint32_t USART2;
    __IO uint32_t USART3;
    __IO uint32_t USART4;
    __IO uint32_t USART5;
    __IO uint32_t USART6;
    __IO uint32_t USART7;
    __IO uint32_t USART8;
    __IO uint32_t USART9;
    __IO uint32_t USART10;
    uint32_t RESERVED4[2];
} stc_pwc_fcg3_bit_t;

typedef struct {
    __IO uint32_t PRT0;
    uint32_t RESERVED0[31];
} stc_pwc_fcg0pc_bit_t;

typedef struct {
    __IO uint32_t VBTRSD;
    __IO uint32_t RAMVALID;
    __IO uint32_t RAMPDF;
    __IO uint32_t VBATDIVMONE;
    uint32_t RESERVED0[3];
    __IO uint32_t CSDIS;
} stc_pwc_vbatcr_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t WKOVF;
    uint32_t RESERVED1[2];
    __IO uint32_t WKTCE;
} stc_pwc_wktc2_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t PWDN;
} stc_pwc_pwrc0_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t VHRCSD;
    __IO uint32_t PDTS;
    uint32_t RESERVED1[4];
} stc_pwc_pwrc1_bit_t;

typedef struct {
    __IO uint32_t VBATREFSEL;
    __IO uint32_t VBATME;
    uint32_t RESERVED0[2];
    __IO uint32_t VBATMON;
    uint32_t RESERVED1[1];
    __IO uint32_t ADBUFS;
    __IO uint32_t ADBUFE;
} stc_pwc_pwrc4_bit_t;

typedef struct {
    __IO uint32_t EXVCCINEN;
    uint32_t RESERVED0[4];
    __IO uint32_t PVD1EN;
    __IO uint32_t PVD2EN;
    uint32_t RESERVED1[1];
} stc_pwc_pvdcr0_bit_t;

typedef struct {
    __IO uint32_t PVD1IRE;
    __IO uint32_t PVD1IRS;
    __IO uint32_t PVD1CMPOE;
    uint32_t RESERVED0[1];
    __IO uint32_t PVD2IRE;
    __IO uint32_t PVD2IRS;
    __IO uint32_t PVD2CMPOE;
    uint32_t RESERVED1[1];
} stc_pwc_pvdcr1_bit_t;

typedef struct {
    __IO uint32_t PVD1NFDIS;
    uint32_t RESERVED0[3];
    __IO uint32_t PVD2NFDIS;
    uint32_t RESERVED1[3];
} stc_pwc_pvdfcr_bit_t;

typedef struct {
    __IO uint32_t WKE00;
    __IO uint32_t WKE01;
    __IO uint32_t WKE02;
    __IO uint32_t WKE03;
    __IO uint32_t WKE10;
    __IO uint32_t WKE11;
    __IO uint32_t WKE12;
    __IO uint32_t WKE13;
} stc_pwc_pdwke0_bit_t;

typedef struct {
    __IO uint32_t WKE20;
    __IO uint32_t WKE21;
    __IO uint32_t WKE22;
    __IO uint32_t WKE23;
    __IO uint32_t WKE30;
    __IO uint32_t WKE31;
    __IO uint32_t WKE32;
    __IO uint32_t WKE33;
} stc_pwc_pdwke1_bit_t;

typedef struct {
    __IO uint32_t VD1WKE;
    __IO uint32_t VD2WKE;
    uint32_t RESERVED0[2];
    __IO uint32_t RTCPRDWKE;
    __IO uint32_t RTCALMWKE;
    uint32_t RESERVED1[1];
    __IO uint32_t WKTMWKE;
} stc_pwc_pdwke2_bit_t;

typedef struct {
    __IO uint32_t WK0EGS;
    __IO uint32_t WK1EGS;
    __IO uint32_t WK2EGS;
    __IO uint32_t WK3EGS;
    __IO uint32_t VD1EGS;
    __IO uint32_t VD2EGS;
    uint32_t RESERVED0[2];
} stc_pwc_pdwkes_bit_t;

typedef struct {
    __IO uint32_t PTWK0F;
    __IO uint32_t PTWK1F;
    __IO uint32_t PTWK2F;
    __IO uint32_t PTWK3F;
    __IO uint32_t VD1WKF;
    __IO uint32_t VD2WKF;
    uint32_t RESERVED0[2];
} stc_pwc_pdwkf0_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t RXD0WKF;
    __IO uint32_t RTCPRDWKF;
    __IO uint32_t RTCALMWKF;
    uint32_t RESERVED1[1];
    __IO uint32_t WKTMWKF;
} stc_pwc_pdwkf1_bit_t;

typedef struct {
    __IO uint32_t RAMPDC0;
    __IO uint32_t RAMPDC1;
    __IO uint32_t RAMPDC2;
    __IO uint32_t RAMPDC3;
    __IO uint32_t RAMPDC4;
    __IO uint32_t RAMPDC5;
    __IO uint32_t RAMPDC6;
    __IO uint32_t RAMPDC7;
    __IO uint32_t RAMPDC8;
    __IO uint32_t RAMPDC9;
    __IO uint32_t RAMPDC10;
    uint32_t RESERVED0[21];
} stc_pwc_rampc0_bit_t;

typedef struct {
    __IO uint32_t PRAMPDC0;
    __IO uint32_t PRAMPDC1;
    __IO uint32_t PRAMPDC2;
    __IO uint32_t PRAMPDC3;
    __IO uint32_t PRAMPDC4;
    __IO uint32_t PRAMPDC5;
    __IO uint32_t PRAMPDC6;
    __IO uint32_t PRAMPDC7;
    __IO uint32_t PRAMPDC8;
    __IO uint32_t PRAMPDC9;
    uint32_t RESERVED0[22];
} stc_pwc_pramlpc_bit_t;

typedef struct {
    __IO uint32_t PVD1NMIS;
    uint32_t RESERVED0[3];
    __IO uint32_t PVD2NMIS;
    uint32_t RESERVED1[3];
} stc_pwc_pvdicr_bit_t;

typedef struct {
    __IO uint32_t PVD1MON;
    __IO uint32_t PVD1DETFLG;
    uint32_t RESERVED0[2];
    __IO uint32_t PVD2MON;
    __IO uint32_t PVD2DETFLG;
    uint32_t RESERVED1[2];
} stc_pwc_pvddsr_bit_t;

typedef struct {
    __IO uint32_t FLNWT;
    __IO uint32_t CKSMRC;
    uint32_t RESERVED0[12];
    __IO uint32_t EXBUSOE;
    __IO uint32_t STOP;
} stc_pwc_stpmcr_bit_t;

typedef struct {
    __IO uint32_t FPRCB0;
    __IO uint32_t FPRCB1;
    __IO uint32_t FPRCB2;
    __IO uint32_t FPRCB3;
    uint32_t RESERVED0[12];
} stc_pwc_fprc_bit_t;

typedef struct {
    uint32_t RESERVED0[5];
    __IO uint32_t LKUPREN;
    uint32_t RESERVED1[2];
} stc_rmu_prstcr0_bit_t;

typedef struct {
    __IO uint32_t PORF;
    __IO uint32_t PINRF;
    __IO uint32_t BORF;
    __IO uint32_t PVD1RF;
    __IO uint32_t PVD2RF;
    __IO uint32_t WDRF;
    __IO uint32_t SWDRF;
    __IO uint32_t PDRF;
    __IO uint32_t SWRF;
    __IO uint32_t MPUERF;
    __IO uint32_t RAPERF;
    __IO uint32_t RAECRF;
    __IO uint32_t CKFERF;
    __IO uint32_t XTALERF;
    __IO uint32_t LKUPRF;
    uint32_t RESERVED0[15];
    __IO uint32_t MULTIRF;
    __IO uint32_t CLRF;
} stc_rmu_rstf0_bit_t;

typedef struct {
    __IO uint32_t RESET;
    uint32_t RESERVED0[7];
} stc_rtc_cr0_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t AMPM;
    uint32_t RESERVED1[1];
    __IO uint32_t ONEHZOE;
    __IO uint32_t ONEHZSEL;
    __IO uint32_t START;
} stc_rtc_cr1_bit_t;

typedef struct {
    __IO uint32_t RWREQ;
    __IO uint32_t RWEN;
    __IO uint32_t PRDF;
    __IO uint32_t ALMF;
    uint32_t RESERVED0[1];
    __IO uint32_t PRDIE;
    __IO uint32_t ALMIE;
    __IO uint32_t ALME;
} stc_rtc_cr2_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t LRCEN;
    uint32_t RESERVED1[2];
    __IO uint32_t RCKSEL;
} stc_rtc_cr3_bit_t;

typedef struct {
    __IO uint32_t COMP8;
    uint32_t RESERVED0[6];
    __IO uint32_t COMPEN;
} stc_rtc_errcrh_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t TPRSTE0;
    __IO uint32_t TPIE0;
    __IO uint32_t TSTPE0;
    __IO uint32_t TPEN0;
} stc_rtc_tpcr0_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t TPRSTE1;
    __IO uint32_t TPIE1;
    __IO uint32_t TSTPE1;
    __IO uint32_t TPEN1;
} stc_rtc_tpcr1_bit_t;

typedef struct {
    __IO uint32_t TPF0;
    __IO uint32_t TPF1;
    __IO uint32_t TPOVF;
    uint32_t RESERVED0[5];
} stc_rtc_tpsr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t BCE;
    uint32_t RESERVED1[2];
    __IO uint32_t DDIR;
    __IO uint32_t MULB;
    uint32_t RESERVED2[10];
} stc_sdioc_transmode_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t CCE;
    __IO uint32_t ICE;
    __IO uint32_t DAT;
    uint32_t RESERVED1[10];
} stc_sdioc_cmd_bit_t;

typedef struct {
    __I  uint32_t CIC;
    __I  uint32_t CID;
    __I  uint32_t DA;
    uint32_t RESERVED0[5];
    __I  uint32_t WTA;
    __I  uint32_t RTA;
    __I  uint32_t BWE;
    __I  uint32_t BRE;
    uint32_t RESERVED1[4];
    __I  uint32_t CIN;
    __I  uint32_t CSS;
    __I  uint32_t CDL;
    __I  uint32_t WPL;
    uint32_t RESERVED2[4];
    __I  uint32_t CMDL;
    uint32_t RESERVED3[7];
} stc_sdioc_pstat_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t DW;
    __IO uint32_t HSEN;
    uint32_t RESERVED1[2];
    __IO uint32_t EXDW;
    __IO uint32_t CDTL;
    __IO uint32_t CDSS;
} stc_sdioc_hostcon_bit_t;

typedef struct {
    __IO uint32_t PWON;
    uint32_t RESERVED0[7];
} stc_sdioc_pwrcon_bit_t;

typedef struct {
    __IO uint32_t SABGR;
    __IO uint32_t CR;
    __IO uint32_t RWC;
    __IO uint32_t IABG;
    uint32_t RESERVED0[4];
} stc_sdioc_blkgpcon_bit_t;

typedef struct {
    __IO uint32_t ICE;
    uint32_t RESERVED0[1];
    __IO uint32_t CE;
    uint32_t RESERVED1[13];
} stc_sdioc_clkcon_bit_t;

typedef struct {
    __IO uint32_t RSTA;
    __IO uint32_t RSTC;
    __IO uint32_t RSTD;
    uint32_t RESERVED0[5];
} stc_sdioc_sftrst_bit_t;

typedef struct {
    __IO uint32_t CC;
    __IO uint32_t TC;
    __IO uint32_t BGE;
    uint32_t RESERVED0[1];
    __IO uint32_t BWR;
    __IO uint32_t BRR;
    __IO uint32_t CIST;
    __IO uint32_t CRM;
    __I  uint32_t CINT;
    uint32_t RESERVED1[6];
    __I  uint32_t EI;
} stc_sdioc_norintst_bit_t;

typedef struct {
    __IO uint32_t CTOE;
    __IO uint32_t CCE;
    __IO uint32_t CEBE;
    __IO uint32_t CIE;
    __IO uint32_t DTOE;
    __IO uint32_t DCE;
    __IO uint32_t DEBE;
    uint32_t RESERVED0[1];
    __IO uint32_t ACE;
    uint32_t RESERVED1[7];
} stc_sdioc_errintst_bit_t;

typedef struct {
    __IO uint32_t CCEN;
    __IO uint32_t TCEN;
    __IO uint32_t BGEEN;
    uint32_t RESERVED0[1];
    __IO uint32_t BWREN;
    __IO uint32_t BRREN;
    __IO uint32_t CISTEN;
    __IO uint32_t CRMEN;
    __IO uint32_t CINTEN;
    uint32_t RESERVED1[7];
} stc_sdioc_norintsten_bit_t;

typedef struct {
    __IO uint32_t CTOEEN;
    __IO uint32_t CCEEN;
    __IO uint32_t CEBEEN;
    __IO uint32_t CIEEN;
    __IO uint32_t DTOEEN;
    __IO uint32_t DCEEN;
    __IO uint32_t DEBEEN;
    uint32_t RESERVED0[1];
    __IO uint32_t ACEEN;
    uint32_t RESERVED1[7];
} stc_sdioc_errintsten_bit_t;

typedef struct {
    __IO uint32_t CCSEN;
    __IO uint32_t TCSEN;
    __IO uint32_t BGESEN;
    uint32_t RESERVED0[1];
    __IO uint32_t BWRSEN;
    __IO uint32_t BRRSEN;
    __IO uint32_t CISTSEN;
    __IO uint32_t CRMSEN;
    __IO uint32_t CINTSEN;
    uint32_t RESERVED1[7];
} stc_sdioc_norintsgen_bit_t;

typedef struct {
    __IO uint32_t CTOESEN;
    __IO uint32_t CCESEN;
    __IO uint32_t CEBESEN;
    __IO uint32_t CIESEN;
    __IO uint32_t DTOESEN;
    __IO uint32_t DCESEN;
    __IO uint32_t DEBESEN;
    uint32_t RESERVED0[1];
    __IO uint32_t ACESEN;
    uint32_t RESERVED1[7];
} stc_sdioc_errintsgen_bit_t;

typedef struct {
    __I  uint32_t NE;
    __I  uint32_t TOE;
    __I  uint32_t CE;
    __I  uint32_t EBE;
    __I  uint32_t IE;
    uint32_t RESERVED0[2];
    __I  uint32_t CMDE;
    uint32_t RESERVED1[8];
} stc_sdioc_atcerrst_bit_t;

typedef struct {
    __O  uint32_t FNE;
    __O  uint32_t FTOE;
    __O  uint32_t FCE;
    __O  uint32_t FEBE;
    __O  uint32_t FIE;
    uint32_t RESERVED0[2];
    __O  uint32_t FCMDE;
    uint32_t RESERVED1[8];
} stc_sdioc_fea_bit_t;

typedef struct {
    __O  uint32_t FCTOE;
    __O  uint32_t FCCE;
    __O  uint32_t FCEBE;
    __O  uint32_t FCIE;
    __O  uint32_t FDTOE;
    __O  uint32_t FDCE;
    __O  uint32_t FDEBE;
    uint32_t RESERVED0[1];
    __O  uint32_t FACE;
    uint32_t RESERVED1[7];
} stc_sdioc_fee_bit_t;

typedef struct {
    __IO uint32_t SPIMDS;
    __IO uint32_t TXMDS;
    uint32_t RESERVED0[1];
    __IO uint32_t MSTR;
    __IO uint32_t SPLPBK;
    __IO uint32_t SPLPBK2;
    __IO uint32_t SPE;
    __IO uint32_t CSUSPE;
    __IO uint32_t EIE;
    __IO uint32_t TXIE;
    __IO uint32_t RXIE;
    __IO uint32_t IDIE;
    __IO uint32_t MODFE;
    __IO uint32_t PATE;
    __IO uint32_t PAOE;
    __IO uint32_t PAE;
    uint32_t RESERVED1[16];
} stc_spi_cr1_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t SPRDTD;
    uint32_t RESERVED1[1];
    __IO uint32_t SS0PV;
    __IO uint32_t SS1PV;
    __IO uint32_t SS2PV;
    __IO uint32_t SS3PV;
    uint32_t RESERVED2[20];
} stc_spi_cfg1_bit_t;

typedef struct {
    __IO uint32_t OVRERF;
    __I  uint32_t IDLNF;
    __IO uint32_t MODFERF;
    __IO uint32_t PERF;
    __IO uint32_t UDRERF;
    __I  uint32_t TDEF;
    uint32_t RESERVED0[1];
    __I  uint32_t RDFF;
    uint32_t RESERVED1[24];
} stc_spi_sr_bit_t;

typedef struct {
    __IO uint32_t CPHA;
    __IO uint32_t CPOL;
    uint32_t RESERVED0[10];
    __IO uint32_t LSBF;
    __IO uint32_t MIDIE;
    __IO uint32_t MSSDLE;
    __IO uint32_t MSSIE;
    uint32_t RESERVED1[16];
} stc_spi_cfg2_bit_t;

typedef struct {
    __IO uint32_t WTPRC;
    uint32_t RESERVED0[31];
} stc_sramc_wtpr_bit_t;

typedef struct {
    __IO uint32_t PYOAD;
    uint32_t RESERVED0[15];
    __IO uint32_t ECCOAD;
    __IO uint32_t BECCOAD;
    uint32_t RESERVED1[14];
} stc_sramc_ckcr_bit_t;

typedef struct {
    __IO uint32_t CKPRC;
    uint32_t RESERVED0[31];
} stc_sramc_ckpr_bit_t;

typedef struct {
    __IO uint32_t SRAM1_PYERR;
    __IO uint32_t SRAM2_PYERR;
    __IO uint32_t SRAM3_PYERR;
    __IO uint32_t SRAMH_PYERR;
    __IO uint32_t SRAM4_1ERR;
    __IO uint32_t SRAM4_2ERR;
    __IO uint32_t SRAMB_1ERR;
    __IO uint32_t SRAMB_2ERR;
    __IO uint32_t CACHE_PYERR;
    uint32_t RESERVED0[23];
} stc_sramc_cksr_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t SLPOFF;
    uint32_t RESERVED1[14];
    __IO uint32_t ITS;
} stc_swdt_cr_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t UDF;
    __IO uint32_t REF;
    uint32_t RESERVED1[14];
} stc_swdt_sr_bit_t;

typedef struct {
    __IO uint32_t CSTA;
    __IO uint32_t CAPMDA;
    __IO uint32_t INTENA;
    uint32_t RESERVED0[5];
    __IO uint32_t SYNSA;
    __IO uint32_t SYNCLKA;
    __IO uint32_t ASYNCLKA;
    uint32_t RESERVED1[1];
    __IO uint32_t HSTAA;
    __IO uint32_t HSTPA;
    __IO uint32_t HCLEA;
    __IO uint32_t HICPA;
    __IO uint32_t CSTB;
    __IO uint32_t CAPMDB;
    __IO uint32_t INTENB;
    uint32_t RESERVED2[5];
    __IO uint32_t SYNSB;
    __IO uint32_t SYNCLKB;
    __IO uint32_t ASYNCLKB;
    uint32_t RESERVED3[1];
    __IO uint32_t HSTAB;
    __IO uint32_t HSTPB;
    __IO uint32_t HCLEB;
    __IO uint32_t HICPB;
} stc_tmr0_bconr_bit_t;

typedef struct {
    __IO uint32_t CMFA;
    uint32_t RESERVED0[15];
    __IO uint32_t CMFB;
    uint32_t RESERVED1[15];
} stc_tmr0_stflr_bit_t;

typedef struct {
    __IO uint32_t CSTA;
    __IO uint32_t CAPMDA;
    uint32_t RESERVED0[1];
    __IO uint32_t SYNSA;
    uint32_t RESERVED1[12];
    __IO uint32_t CSTB;
    __IO uint32_t CAPMDB;
    uint32_t RESERVED2[1];
    __IO uint32_t SYNSB;
    uint32_t RESERVED3[12];
} stc_tmr2_bconr_bit_t;

typedef struct {
    __IO uint32_t CMENA;
    __IO uint32_t OVENA;
    uint32_t RESERVED0[14];
    __IO uint32_t CMENB;
    __IO uint32_t OVENB;
    uint32_t RESERVED1[14];
} stc_tmr2_iconr_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t OUTENA;
    uint32_t RESERVED1[3];
    __IO uint32_t NOFIENA;
    uint32_t RESERVED2[11];
    __IO uint32_t OUTENB;
    uint32_t RESERVED3[3];
    __IO uint32_t NOFIENB;
    uint32_t RESERVED4[3];
} stc_tmr2_pconr_bit_t;

typedef struct {
    __IO uint32_t HSTAA0;
    __IO uint32_t HSTAA1;
    __IO uint32_t HSTAA2;
    uint32_t RESERVED0[1];
    __IO uint32_t HSTPA0;
    __IO uint32_t HSTPA1;
    __IO uint32_t HSTPA2;
    uint32_t RESERVED1[1];
    __IO uint32_t HCLEA0;
    __IO uint32_t HCLEA1;
    __IO uint32_t HCLEA2;
    uint32_t RESERVED2[1];
    __IO uint32_t HICPA0;
    __IO uint32_t HICPA1;
    __IO uint32_t HICPA2;
    uint32_t RESERVED3[1];
    __IO uint32_t HSTAB0;
    __IO uint32_t HSTAB1;
    __IO uint32_t HSTAB2;
    uint32_t RESERVED4[1];
    __IO uint32_t HSTPB0;
    __IO uint32_t HSTPB1;
    __IO uint32_t HSTPB2;
    uint32_t RESERVED5[1];
    __IO uint32_t HCLEB0;
    __IO uint32_t HCLEB1;
    __IO uint32_t HCLEB2;
    uint32_t RESERVED6[1];
    __IO uint32_t HICPB0;
    __IO uint32_t HICPB1;
    __IO uint32_t HICPB2;
    uint32_t RESERVED7[1];
} stc_tmr2_hconr_bit_t;

typedef struct {
    __IO uint32_t CMFA;
    __IO uint32_t OVFA;
    uint32_t RESERVED0[14];
    __IO uint32_t CMFB;
    __IO uint32_t OVFB;
    uint32_t RESERVED1[14];
} stc_tmr2_stflr_bit_t;

typedef struct {
    __IO uint32_t OCEH;
    __IO uint32_t OCEL;
    __IO uint32_t OCPH;
    __IO uint32_t OCPL;
    __IO uint32_t OCIEH;
    __IO uint32_t OCIEL;
    __IO uint32_t OCFH;
    __IO uint32_t OCFL;
    uint32_t RESERVED0[8];
} stc_tmr4_ocsr_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t LMCH;
    __IO uint32_t LMCL;
    __IO uint32_t LMMH;
    __IO uint32_t LMML;
    __IO uint32_t MCECH;
    __IO uint32_t MCECL;
    uint32_t RESERVED1[2];
} stc_tmr4_ocer_bit_t;

typedef struct {
    __IO uint32_t OCFDCH;
    __IO uint32_t OCFPKH;
    __IO uint32_t OCFUCH;
    __IO uint32_t OCFZRH;
    uint32_t RESERVED0[12];
} stc_tmr4_ocmrh_bit_t;

typedef struct {
    __IO uint32_t OCFDCL;
    __IO uint32_t OCFPKL;
    __IO uint32_t OCFUCL;
    __IO uint32_t OCFZRL;
    uint32_t RESERVED0[28];
} stc_tmr4_ocmrl_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t CLEAR;
    __IO uint32_t MODE;
    __IO uint32_t STOP;
    __IO uint32_t BUFEN;
    __IO uint32_t IRQPEN;
    __IO uint32_t IRQPF;
    uint32_t RESERVED1[3];
    __IO uint32_t IRQZEN;
    __IO uint32_t IRQZF;
    __IO uint32_t ECKEN;
} stc_tmr4_ccsr_bit_t;

typedef struct {
    __IO uint32_t RTIDU;
    __IO uint32_t RTIDV;
    __IO uint32_t RTIDW;
    uint32_t RESERVED0[1];
    __I  uint32_t RTIFU;
    __IO uint32_t RTICU;
    __IO uint32_t RTEU;
    __IO uint32_t RTSU;
    __I  uint32_t RTIFV;
    __IO uint32_t RTICV;
    __IO uint32_t RTEV;
    __IO uint32_t RTSV;
    __I  uint32_t RTIFW;
    __IO uint32_t RTICW;
    __IO uint32_t RTEW;
    __IO uint32_t RTSW;
} stc_tmr4_rcsr_bit_t;

typedef struct {
    uint32_t RESERVED0[5];
    __IO uint32_t LMC;
    uint32_t RESERVED1[2];
    __IO uint32_t EVTMS;
    __IO uint32_t EVTDS;
    uint32_t RESERVED2[2];
    __IO uint32_t DEN;
    __IO uint32_t PEN;
    __IO uint32_t UEN;
    __IO uint32_t ZEN;
} stc_tmr4_scsr_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t MZCE;
    __IO uint32_t MPCE;
    uint32_t RESERVED1[8];
} stc_tmr4_scmr_bit_t;

typedef struct {
    __IO uint32_t OEUH;
    __IO uint32_t OEUL;
    __IO uint32_t OEVH;
    __IO uint32_t OEVL;
    __IO uint32_t OEWH;
    __IO uint32_t OEWL;
    uint32_t RESERVED0[2];
    __IO uint32_t MOE;
    __IO uint32_t AOE;
    uint32_t RESERVED1[22];
} stc_tmr4_pscr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t PCTS;
    uint32_t RESERVED1[12];
} stc_tmr4_scer_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t DIR;
    __IO uint32_t MODE;
    uint32_t RESERVED0[5];
    __IO uint32_t OVSTP;
    uint32_t RESERVED1[7];
    __IO uint32_t ZMSKREV;
    __IO uint32_t ZMSKPOS;
    uint32_t RESERVED2[14];
} stc_tmr6_gconr_bit_t;

typedef struct {
    __IO uint32_t INTENA;
    __IO uint32_t INTENB;
    __IO uint32_t INTENC;
    __IO uint32_t INTEND;
    __IO uint32_t INTENE;
    __IO uint32_t INTENF;
    __IO uint32_t INTENOVF;
    __IO uint32_t INTENUDF;
    __IO uint32_t INTENDTE;
    uint32_t RESERVED0[7];
    __IO uint32_t INTENSAU;
    __IO uint32_t INTENSAD;
    __IO uint32_t INTENSBU;
    __IO uint32_t INTENSBD;
    uint32_t RESERVED1[12];
} stc_tmr6_iconr_bit_t;

typedef struct {
    __IO uint32_t BENA;
    __IO uint32_t BSEA;
    __IO uint32_t BTRUA;
    __IO uint32_t BTRDA;
    __IO uint32_t BENB;
    __IO uint32_t BSEB;
    __IO uint32_t BTRUB;
    __IO uint32_t BTRDB;
    __IO uint32_t BENP;
    __IO uint32_t BSEP;
    __IO uint32_t BTRUP;
    __IO uint32_t BTRDP;
    uint32_t RESERVED0[4];
    __IO uint32_t BENSPA;
    __IO uint32_t BSESPA;
    __IO uint32_t BTRUSPA;
    __IO uint32_t BTRDSPA;
    __IO uint32_t BENSPB;
    __IO uint32_t BSESPB;
    __IO uint32_t BTRUSPB;
    __IO uint32_t BTRDSPB;
    uint32_t RESERVED1[8];
} stc_tmr6_bconr_bit_t;

typedef struct {
    __IO uint32_t DTCEN;
    __IO uint32_t SEPA;
    uint32_t RESERVED0[2];
    __IO uint32_t DTBENU;
    __IO uint32_t DTBEND;
    __IO uint32_t DTBTRU;
    __IO uint32_t DTBTRD;
    uint32_t RESERVED1[24];
} stc_tmr6_dconr_bit_t;

typedef struct {
    uint32_t RESERVED0[28];
    __IO uint32_t OUTENA;
    uint32_t RESERVED1[2];
    __IO uint32_t CAPMDA;
} stc_tmr6_pcnar_bit_t;

typedef struct {
    uint32_t RESERVED0[28];
    __IO uint32_t OUTENB;
    uint32_t RESERVED1[2];
    __IO uint32_t CAPMDB;
} stc_tmr6_pcnbr_bit_t;

typedef struct {
    __IO uint32_t NOFIENGA;
    uint32_t RESERVED0[3];
    __IO uint32_t NOFIENGB;
    uint32_t RESERVED1[27];
} stc_tmr6_fcngr_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t SPPERIA;
    __IO uint32_t SPPERIB;
    uint32_t RESERVED1[22];
} stc_tmr6_vperr_bit_t;

typedef struct {
    __IO uint32_t CMAF;
    __IO uint32_t CMBF;
    __IO uint32_t CMCF;
    __IO uint32_t CMDF;
    __IO uint32_t CMEF;
    __IO uint32_t CMFF;
    __IO uint32_t OVFF;
    __IO uint32_t UDFF;
    __I  uint32_t DTEF;
    __IO uint32_t CMSAUF;
    __IO uint32_t CMSADF;
    __IO uint32_t CMSBUF;
    __IO uint32_t CMSBDF;
    uint32_t RESERVED0[18];
    __I  uint32_t DIRF;
} stc_tmr6_stflr_bit_t;

typedef struct {
    __IO uint32_t HSTA0;
    __IO uint32_t HSTA1;
    __IO uint32_t HSTA2;
    __IO uint32_t HSTA3;
    uint32_t RESERVED0[3];
    __IO uint32_t STAS;
    __IO uint32_t HSTA8;
    __IO uint32_t HSTA9;
    __IO uint32_t HSTA10;
    __IO uint32_t HSTA11;
    uint32_t RESERVED1[4];
    __IO uint32_t HSTA16;
    __IO uint32_t HSTA17;
    __IO uint32_t HSTA18;
    __IO uint32_t HSTA19;
    __IO uint32_t HSTA20;
    __IO uint32_t HSTA21;
    __IO uint32_t HSTA22;
    __IO uint32_t HSTA23;
    uint32_t RESERVED2[8];
} stc_tmr6_hstar_bit_t;

typedef struct {
    __IO uint32_t HSTP0;
    __IO uint32_t HSTP1;
    __IO uint32_t HSTP2;
    __IO uint32_t HSTP3;
    uint32_t RESERVED0[3];
    __IO uint32_t STPS;
    __IO uint32_t HSTP8;
    __IO uint32_t HSTP9;
    __IO uint32_t HSTP10;
    __IO uint32_t HSTP11;
    uint32_t RESERVED1[4];
    __IO uint32_t HSTP16;
    __IO uint32_t HSTP17;
    __IO uint32_t HSTP18;
    __IO uint32_t HSTP19;
    __IO uint32_t HSTP20;
    __IO uint32_t HSTP21;
    __IO uint32_t HSTP22;
    __IO uint32_t HSTP23;
    uint32_t RESERVED2[8];
} stc_tmr6_hstpr_bit_t;

typedef struct {
    __IO uint32_t HCLE0;
    __IO uint32_t HCLE1;
    __IO uint32_t HCLE2;
    __IO uint32_t HCLE3;
    uint32_t RESERVED0[3];
    __IO uint32_t CLES;
    __IO uint32_t HCLE8;
    __IO uint32_t HCLE9;
    __IO uint32_t HCLE10;
    __IO uint32_t HCLE11;
    uint32_t RESERVED1[4];
    __IO uint32_t HCLE16;
    __IO uint32_t HCLE17;
    __IO uint32_t HCLE18;
    __IO uint32_t HCLE19;
    __IO uint32_t HCLE20;
    __IO uint32_t HCLE21;
    __IO uint32_t HCLE22;
    __IO uint32_t HCLE23;
    uint32_t RESERVED2[8];
} stc_tmr6_hclrr_bit_t;

typedef struct {
    __IO uint32_t HUPD0;
    __IO uint32_t HUPD1;
    __IO uint32_t HUPD2;
    __IO uint32_t HUPD3;
    uint32_t RESERVED0[3];
    __IO uint32_t UPDS;
    __IO uint32_t HUPD8;
    __IO uint32_t HUPD9;
    __IO uint32_t HUPD10;
    __IO uint32_t HUPD11;
    uint32_t RESERVED1[4];
    __IO uint32_t HUPD16;
    __IO uint32_t HUPD17;
    __IO uint32_t HUPD18;
    __IO uint32_t HUPD19;
    __IO uint32_t HUPD20;
    __IO uint32_t HUPD21;
    __IO uint32_t HUPD22;
    __IO uint32_t HUPD23;
    uint32_t RESERVED2[8];
} stc_tmr6_hupdr_bit_t;

typedef struct {
    __IO uint32_t HCPA0;
    __IO uint32_t HCPA1;
    __IO uint32_t HCPA2;
    __IO uint32_t HCPA3;
    uint32_t RESERVED0[4];
    __IO uint32_t HCPA8;
    __IO uint32_t HCPA9;
    __IO uint32_t HCPA10;
    __IO uint32_t HCPA11;
    uint32_t RESERVED1[4];
    __IO uint32_t HCPA16;
    __IO uint32_t HCPA17;
    __IO uint32_t HCPA18;
    __IO uint32_t HCPA19;
    __IO uint32_t HCPA20;
    __IO uint32_t HCPA21;
    __IO uint32_t HCPA22;
    __IO uint32_t HCPA23;
    uint32_t RESERVED2[8];
} stc_tmr6_hcpar_bit_t;

typedef struct {
    __IO uint32_t HCPB0;
    __IO uint32_t HCPB1;
    __IO uint32_t HCPB2;
    __IO uint32_t HCPB3;
    uint32_t RESERVED0[4];
    __IO uint32_t HCPB8;
    __IO uint32_t HCPB9;
    __IO uint32_t HCPB10;
    __IO uint32_t HCPB11;
    uint32_t RESERVED1[4];
    __IO uint32_t HCPB16;
    __IO uint32_t HCPB17;
    __IO uint32_t HCPB18;
    __IO uint32_t HCPB19;
    __IO uint32_t HCPB20;
    __IO uint32_t HCPB21;
    __IO uint32_t HCPB22;
    __IO uint32_t HCPB23;
    uint32_t RESERVED2[8];
} stc_tmr6_hcpbr_bit_t;

typedef struct {
    __IO uint32_t HCUP0;
    __IO uint32_t HCUP1;
    __IO uint32_t HCUP2;
    __IO uint32_t HCUP3;
    __IO uint32_t HCUP4;
    __IO uint32_t HCUP5;
    __IO uint32_t HCUP6;
    __IO uint32_t HCUP7;
    __IO uint32_t HCUP8;
    __IO uint32_t HCUP9;
    __IO uint32_t HCUP10;
    __IO uint32_t HCUP11;
    uint32_t RESERVED0[4];
    __IO uint32_t HCUP16;
    __IO uint32_t HCUP17;
    __IO uint32_t HCUP18;
    __IO uint32_t HCUP19;
    __IO uint32_t HCUP20;
    __IO uint32_t HCUP21;
    __IO uint32_t HCUP22;
    __IO uint32_t HCUP23;
    uint32_t RESERVED1[8];
} stc_tmr6_hcupr_bit_t;

typedef struct {
    __IO uint32_t HCDO0;
    __IO uint32_t HCDO1;
    __IO uint32_t HCDO2;
    __IO uint32_t HCDO3;
    __IO uint32_t HCDO4;
    __IO uint32_t HCDO5;
    __IO uint32_t HCDO6;
    __IO uint32_t HCDO7;
    __IO uint32_t HCDO8;
    __IO uint32_t HCDO9;
    __IO uint32_t HCDO10;
    __IO uint32_t HCDO11;
    uint32_t RESERVED0[4];
    __IO uint32_t HCDO16;
    __IO uint32_t HCDO17;
    __IO uint32_t HCDO18;
    __IO uint32_t HCDO19;
    __IO uint32_t HCDO20;
    __IO uint32_t HCDO21;
    __IO uint32_t HCDO22;
    __IO uint32_t HCDO23;
    uint32_t RESERVED1[8];
} stc_tmr6_hcdor_bit_t;

typedef struct {
    __IO uint32_t NOFIENTA;
    uint32_t RESERVED0[3];
    __IO uint32_t NOFIENTB;
    uint32_t RESERVED1[3];
    __IO uint32_t NOFIENTC;
    uint32_t RESERVED2[3];
    __IO uint32_t NOFIENTD;
    uint32_t RESERVED3[19];
} stc_tmr6cr_fcntr_bit_t;

typedef struct {
    __IO uint32_t SSTA1;
    __IO uint32_t SSTA2;
    __IO uint32_t SSTA3;
    __IO uint32_t SSTA4;
    __IO uint32_t SSTA5;
    __IO uint32_t SSTA6;
    __IO uint32_t SSTA7;
    __IO uint32_t SSTA8;
    uint32_t RESERVED0[24];
} stc_tmr6cr_sstar_bit_t;

typedef struct {
    __IO uint32_t SSTP1;
    __IO uint32_t SSTP2;
    __IO uint32_t SSTP3;
    __IO uint32_t SSTP4;
    __IO uint32_t SSTP5;
    __IO uint32_t SSTP6;
    __IO uint32_t SSTP7;
    __IO uint32_t SSTP8;
    uint32_t RESERVED0[24];
} stc_tmr6cr_sstpr_bit_t;

typedef struct {
    __IO uint32_t SCLE1;
    __IO uint32_t SCLE2;
    __IO uint32_t SCLE3;
    __IO uint32_t SCLE4;
    __IO uint32_t SCLE5;
    __IO uint32_t SCLE6;
    __IO uint32_t SCLE7;
    __IO uint32_t SCLE8;
    uint32_t RESERVED0[24];
} stc_tmr6cr_sclrr_bit_t;

typedef struct {
    __IO uint32_t SUPD1;
    __IO uint32_t SUPD2;
    __IO uint32_t SUPD3;
    __IO uint32_t SUPD4;
    __IO uint32_t SUPD5;
    __IO uint32_t SUPD6;
    __IO uint32_t SUPD7;
    __IO uint32_t SUPD8;
    uint32_t RESERVED0[24];
} stc_tmr6cr_supdr_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t DIR;
    __IO uint32_t MODE;
    __IO uint32_t SYNST;
    uint32_t RESERVED0[4];
} stc_tmra_bcstrl_bit_t;

typedef struct {
    __IO uint32_t OVSTP;
    uint32_t RESERVED0[3];
    __IO uint32_t ITENOVF;
    __IO uint32_t ITENUDF;
    __IO uint32_t OVFF;
    __IO uint32_t UDFF;
} stc_tmra_bcstrh_bit_t;

typedef struct {
    __IO uint32_t HSTA0;
    __IO uint32_t HSTA1;
    __IO uint32_t HSTA2;
    uint32_t RESERVED0[1];
    __IO uint32_t HSTP0;
    __IO uint32_t HSTP1;
    __IO uint32_t HSTP2;
    uint32_t RESERVED1[1];
    __IO uint32_t HCLE0;
    __IO uint32_t HCLE1;
    __IO uint32_t HCLE2;
    uint32_t RESERVED2[1];
    __IO uint32_t HCLE3;
    __IO uint32_t HCLE4;
    __IO uint32_t HCLE5;
    __IO uint32_t HCLE6;
} stc_tmra_hconr_bit_t;

typedef struct {
    __IO uint32_t HCUP0;
    __IO uint32_t HCUP1;
    __IO uint32_t HCUP2;
    __IO uint32_t HCUP3;
    __IO uint32_t HCUP4;
    __IO uint32_t HCUP5;
    __IO uint32_t HCUP6;
    __IO uint32_t HCUP7;
    __IO uint32_t HCUP8;
    __IO uint32_t HCUP9;
    __IO uint32_t HCUP10;
    __IO uint32_t HCUP11;
    __IO uint32_t HCUP12;
    uint32_t RESERVED0[3];
} stc_tmra_hcupr_bit_t;

typedef struct {
    __IO uint32_t HCDO0;
    __IO uint32_t HCDO1;
    __IO uint32_t HCDO2;
    __IO uint32_t HCDO3;
    __IO uint32_t HCDO4;
    __IO uint32_t HCDO5;
    __IO uint32_t HCDO6;
    __IO uint32_t HCDO7;
    __IO uint32_t HCDO8;
    __IO uint32_t HCDO9;
    __IO uint32_t HCDO10;
    __IO uint32_t HCDO11;
    __IO uint32_t HCDO12;
    uint32_t RESERVED0[3];
} stc_tmra_hcdor_bit_t;

typedef struct {
    __IO uint32_t ITEN1;
    __IO uint32_t ITEN2;
    __IO uint32_t ITEN3;
    __IO uint32_t ITEN4;
    uint32_t RESERVED0[12];
} stc_tmra_iconr_bit_t;

typedef struct {
    __IO uint32_t ETEN1;
    __IO uint32_t ETEN2;
    __IO uint32_t ETEN3;
    __IO uint32_t ETEN4;
    uint32_t RESERVED0[12];
} stc_tmra_econr_bit_t;

typedef struct {
    __IO uint32_t NOFIENTG;
    uint32_t RESERVED0[7];
    __IO uint32_t NOFIENCA;
    uint32_t RESERVED1[3];
    __IO uint32_t NOFIENCB;
    uint32_t RESERVED2[3];
} stc_tmra_fconr_bit_t;

typedef struct {
    __IO uint32_t CMPF1;
    __IO uint32_t CMPF2;
    __IO uint32_t CMPF3;
    __IO uint32_t CMPF4;
    uint32_t RESERVED0[12];
} stc_tmra_stflr_bit_t;

typedef struct {
    __IO uint32_t BEN;
    __IO uint32_t BSE0;
    __IO uint32_t BSE1;
    uint32_t RESERVED0[13];
} stc_tmra_bconr_bit_t;

typedef struct {
    __IO uint32_t CAPMD;
    uint32_t RESERVED0[3];
    __IO uint32_t HICP0;
    __IO uint32_t HICP1;
    __IO uint32_t HICP2;
    uint32_t RESERVED1[1];
    __IO uint32_t HICP3;
    __IO uint32_t HICP4;
    uint32_t RESERVED2[2];
    __IO uint32_t NOFIENCP;
    uint32_t RESERVED3[3];
} stc_tmra_cconr_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t OUTEN;
    uint32_t RESERVED1[3];
} stc_tmra_pconr_bit_t;

typedef struct {
    __IO uint32_t EN;
    __IO uint32_t RUN;
    uint32_t RESERVED0[30];
} stc_trng_cr_bit_t;

typedef struct {
    __IO uint32_t LOAD;
    uint32_t RESERVED0[31];
} stc_trng_mr_bit_t;

typedef struct {
    __I  uint32_t PE;
    __I  uint32_t FE;
    uint32_t RESERVED0[1];
    __I  uint32_t ORE;
    __I  uint32_t BE;
    __I  uint32_t RXNE;
    __I  uint32_t TC;
    __I  uint32_t TXE;
    __I  uint32_t RTOF;
    __I  uint32_t WKUP;
    __I  uint32_t LBD;
    uint32_t RESERVED1[5];
    __I  uint32_t MPB;
    uint32_t RESERVED2[15];
} stc_usart_sr_bit_t;

typedef struct {
    uint32_t RESERVED0[9];
    __IO uint32_t MPID;
    uint32_t RESERVED1[6];
} stc_usart_tdr_bit_t;

typedef struct {
    __IO uint32_t RTOE;
    __IO uint32_t RTOIE;
    __IO uint32_t RE;
    __IO uint32_t TE;
    __IO uint32_t SLME;
    __IO uint32_t RIE;
    __IO uint32_t TCIE;
    __IO uint32_t TXEIE;
    uint32_t RESERVED0[1];
    __IO uint32_t PS;
    __IO uint32_t PCE;
    uint32_t RESERVED1[1];
    __IO uint32_t M;
    uint32_t RESERVED2[2];
    __IO uint32_t OVER8;
    __IO uint32_t CPE;
    __IO uint32_t CFE;
    uint32_t RESERVED3[1];
    __IO uint32_t CORE;
    __IO uint32_t CRTOF;
    __IO uint32_t CBE;
    __IO uint32_t CWKUP;
    __IO uint32_t CLBD;
    __IO uint32_t MS;
    uint32_t RESERVED4[3];
    __IO uint32_t ML;
    __IO uint32_t FBME;
    __IO uint32_t NFE;
    __IO uint32_t SBS;
} stc_usart_cr1_bit_t;

typedef struct {
    __IO uint32_t MPE;
    __IO uint32_t WKUPIE;
    __IO uint32_t BEIE;
    __IO uint32_t BEE;
    __IO uint32_t LBDIE;
    __IO uint32_t LBDL;
    uint32_t RESERVED0[2];
    __IO uint32_t WKUPE;
    uint32_t RESERVED1[4];
    __IO uint32_t STOP;
    __IO uint32_t LINEN;
    uint32_t RESERVED2[1];
    __IO uint32_t SBK;
    __IO uint32_t SBKM;
    uint32_t RESERVED3[14];
} stc_usart_cr2_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t HDSEL;
    __IO uint32_t LOOP;
    __IO uint32_t SCEN;
    uint32_t RESERVED1[2];
    __IO uint32_t RTSE;
    __IO uint32_t CTSE;
    uint32_t RESERVED2[22];
} stc_usart_cr3_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t VBUSOVEN;
    __IO uint32_t VBUSVAL;
    uint32_t RESERVED1[24];
} stc_usbfs_gvbuscfg_bit_t;

typedef struct {
    __IO uint32_t GINTMSK;
    uint32_t RESERVED0[4];
    __IO uint32_t DMAEN;
    uint32_t RESERVED1[1];
    __IO uint32_t TXFELVL;
    __IO uint32_t PTXFELVL;
    uint32_t RESERVED2[23];
} stc_usbfs_gahbcfg_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t PHYSEL;
    uint32_t RESERVED1[22];
    __IO uint32_t FHMOD;
    __IO uint32_t FDMOD;
    uint32_t RESERVED2[1];
} stc_usbfs_gusbcfg_bit_t;

typedef struct {
    __IO uint32_t CSRST;
    __IO uint32_t HSRST;
    __IO uint32_t FCRST;
    uint32_t RESERVED0[1];
    __IO uint32_t RXFFLSH;
    __IO uint32_t TXFFLSH;
    uint32_t RESERVED1[24];
    __I  uint32_t DMAREQ;
    __I  uint32_t AHBIDL;
} stc_usbfs_grstctl_bit_t;

typedef struct {
    __I  uint32_t CMOD;
    __IO uint32_t MMIS;
    uint32_t RESERVED0[1];
    __IO uint32_t SOF;
    __I  uint32_t RXFNE;
    __I  uint32_t NPTXFE;
    __I  uint32_t GINAKEFF;
    __I  uint32_t GONAKEFF;
    uint32_t RESERVED1[2];
    __IO uint32_t ESUSP;
    __IO uint32_t USBSUSP;
    __IO uint32_t USBRST;
    __IO uint32_t ENUMDNE;
    __IO uint32_t ISOODRP;
    __IO uint32_t EOPF;
    uint32_t RESERVED2[2];
    __I  uint32_t IEPINT;
    __I  uint32_t OEPINT;
    __IO uint32_t IISOIXFR;
    __IO uint32_t IPXFR_INCOMPISOOUT;
    __IO uint32_t DATAFSUSP;
    uint32_t RESERVED3[1];
    __I  uint32_t HPRTINT;
    __I  uint32_t HCINT;
    __I  uint32_t PTXFE;
    __IO uint32_t LPMINT;
    __IO uint32_t CIDSCHG;
    __IO uint32_t DISCINT;
    __IO uint32_t VBUSVINT;
    __IO uint32_t WKUINT;
} stc_usbfs_gintsts_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t MMISM;
    uint32_t RESERVED1[1];
    __IO uint32_t SOFM;
    __IO uint32_t RXFNEM;
    __IO uint32_t NPTXFEM;
    __IO uint32_t GINAKEFFM;
    __IO uint32_t GONAKEFFM;
    uint32_t RESERVED2[2];
    __IO uint32_t ESUSPM;
    __IO uint32_t USBSUSPM;
    __IO uint32_t USBRSTM;
    __IO uint32_t ENUMDNEM;
    __IO uint32_t ISOODRPM;
    __IO uint32_t EOPFM;
    uint32_t RESERVED3[2];
    __IO uint32_t IEPIM;
    __IO uint32_t OEPIM;
    __IO uint32_t IISOIXFRM;
    __IO uint32_t IPXFRM_INCOMPISOOUTM;
    __IO uint32_t DATAFSUSPM;
    uint32_t RESERVED4[1];
    __IO uint32_t HPRTIM;
    __IO uint32_t HCIM;
    __IO uint32_t PTXFEM;
    __IO uint32_t LPMINTM;
    __IO uint32_t CIDSCHGM;
    __IO uint32_t DISCIM;
    __IO uint32_t VBUSVIM;
    __IO uint32_t WKUIM;
} stc_usbfs_gintmsk_bit_t;

typedef struct {
    __IO uint32_t LPMEN;
    __IO uint32_t LPMACK;
    uint32_t RESERVED0[4];
    __IO uint32_t REMWAKE;
    __IO uint32_t L1SSEN;
    uint32_t RESERVED1[4];
    __IO uint32_t L1DSEN;
    uint32_t RESERVED2[2];
    __I  uint32_t SLPSTS;
    __I  uint32_t L1RSMOK;
    uint32_t RESERVED3[7];
    __IO uint32_t SENDLPM;
    uint32_t RESERVED4[3];
    __IO uint32_t ENBSEL;
    uint32_t RESERVED5[3];
} stc_usbfs_glpmcfg_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t FSLSS;
    uint32_t RESERVED1[29];
} stc_usbfs_hcfg_bit_t;

typedef struct {
    __I  uint32_t PCSTS;
    __IO uint32_t PCDET;
    __IO uint32_t PENA;
    __IO uint32_t PENCHNG;
    uint32_t RESERVED0[2];
    __IO uint32_t PRES;
    __IO uint32_t PSUSP;
    __IO uint32_t PRST;
    uint32_t RESERVED1[3];
    __IO uint32_t PWPR;
    uint32_t RESERVED2[19];
} stc_usbfs_hprt_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __IO uint32_t EPDIR;
    uint32_t RESERVED1[1];
    __IO uint32_t LSDEV;
    uint32_t RESERVED2[11];
    __IO uint32_t ODDFRM;
    __IO uint32_t CHDIS;
    __IO uint32_t CHENA;
} stc_usbfs_hcchar_bit_t;

typedef struct {
    __IO uint32_t XFRC;
    __IO uint32_t CHH;
    __IO uint32_t AHBERR;
    __IO uint32_t STALL;
    __IO uint32_t NAK;
    __IO uint32_t ACK;
    uint32_t RESERVED0[1];
    __IO uint32_t TXERR;
    __IO uint32_t BBERR;
    __IO uint32_t FRMOR;
    __IO uint32_t DTERR;
    uint32_t RESERVED1[21];
} stc_usbfs_hcint_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t CHHM;
    __IO uint32_t AHBERRM;
    __IO uint32_t STALLM;
    __IO uint32_t NAKM;
    __IO uint32_t ACKM;
    uint32_t RESERVED0[1];
    __IO uint32_t TXERRM;
    __IO uint32_t BBERRM;
    __IO uint32_t FRMORM;
    __IO uint32_t DTERRM;
    uint32_t RESERVED1[21];
} stc_usbfs_hcintmsk_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t NZLSOHSK;
    uint32_t RESERVED1[29];
} stc_usbfs_dcfg_bit_t;

typedef struct {
    __IO uint32_t RWUSIG;
    __IO uint32_t SDIS;
    __I  uint32_t GINSTS;
    __I  uint32_t GONSTS;
    uint32_t RESERVED0[3];
    __IO uint32_t SGINAK;
    __IO uint32_t CGINAK;
    __IO uint32_t SGONAK;
    __IO uint32_t CGONAK;
    __IO uint32_t POPRGDNE;
    uint32_t RESERVED1[20];
} stc_usbfs_dctl_bit_t;

typedef struct {
    __I  uint32_t SUSPSTS;
    uint32_t RESERVED0[2];
    __I  uint32_t EERR;
    uint32_t RESERVED1[28];
} stc_usbfs_dsts_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t EPDM;
    uint32_t RESERVED0[1];
    __IO uint32_t TOM;
    __IO uint32_t TTXFEMSK;
    __IO uint32_t INEPNMM;
    __IO uint32_t INEPNEM;
    uint32_t RESERVED1[6];
    __IO uint32_t NAKM;
    uint32_t RESERVED2[18];
} stc_usbfs_diepmsk_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t EPDM;
    uint32_t RESERVED0[1];
    __IO uint32_t STUPM;
    __IO uint32_t OTEPDM;
    uint32_t RESERVED1[27];
} stc_usbfs_doepmsk_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __I  uint32_t USBAEP;
    uint32_t RESERVED1[1];
    __I  uint32_t NAKSTS;
    uint32_t RESERVED2[3];
    __IO uint32_t STALL;
    uint32_t RESERVED3[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    uint32_t RESERVED4[2];
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbfs_diepctl0_bit_t;

typedef struct {
    __IO uint32_t XFRC;
    __IO uint32_t EPDISD;
    uint32_t RESERVED0[1];
    __IO uint32_t TOC;
    __IO uint32_t TTXFE;
    uint32_t RESERVED1[1];
    __IO uint32_t INEPNE;
    __I  uint32_t TXFE;
    uint32_t RESERVED2[24];
} stc_usbfs_diepint_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __IO uint32_t USBAEP;
    __I  uint32_t EONUM_DPID;
    __I  uint32_t NAKSTS;
    uint32_t RESERVED1[3];
    __IO uint32_t STALL;
    uint32_t RESERVED2[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    __IO uint32_t SD0PID_SEVNFRM;
    __IO uint32_t SODDFRM;
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbfs_diepctl_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __I  uint32_t USBAEP;
    uint32_t RESERVED1[1];
    __I  uint32_t NAKSTS;
    uint32_t RESERVED2[2];
    __IO uint32_t SNPM;
    __IO uint32_t STALL;
    uint32_t RESERVED3[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    uint32_t RESERVED4[2];
    __I  uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbfs_doepctl0_bit_t;

typedef struct {
    __IO uint32_t XFRC;
    __IO uint32_t EPDISD;
    uint32_t RESERVED0[1];
    __IO uint32_t STUP;
    __IO uint32_t OTEPDIS;
    uint32_t RESERVED1[1];
    __IO uint32_t B2BSTUP;
    uint32_t RESERVED2[25];
} stc_usbfs_doepint_bit_t;

typedef struct {
    uint32_t RESERVED0[19];
    __IO uint32_t PKTCNT;
    uint32_t RESERVED1[12];
} stc_usbfs_doeptsiz0_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __IO uint32_t USBAEP;
    __I  uint32_t DPID;
    __I  uint32_t NAKSTS;
    uint32_t RESERVED1[2];
    __IO uint32_t SNPM;
    __IO uint32_t STALL;
    uint32_t RESERVED2[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    __IO uint32_t SD0PID;
    __IO uint32_t SD1PID;
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbfs_doepctl_bit_t;

typedef struct {
    __IO uint32_t STPPCLK;
    __IO uint32_t GATEHCLK;
    uint32_t RESERVED0[3];
    __IO uint32_t ENL1GTG;
    __IO uint32_t PHYSLEEP;
    __IO uint32_t SUSP;
    uint32_t RESERVED1[24];
} stc_usbfs_gcctl_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t VBUSOVEN;
    __IO uint32_t VBUSVAL;
    uint32_t RESERVED1[24];
} stc_usbhs_gvbuscfg_bit_t;

typedef struct {
    __IO uint32_t GINTMSK;
    uint32_t RESERVED0[4];
    __IO uint32_t DMAEN;
    uint32_t RESERVED1[1];
    __IO uint32_t TXFELVL;
    __IO uint32_t PTXFELVL;
    uint32_t RESERVED2[23];
} stc_usbhs_gahbcfg_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t PHYSEL;
    uint32_t RESERVED1[8];
    __IO uint32_t PHYLPCS;
    uint32_t RESERVED2[1];
    __IO uint32_t ULFSLS;
    __IO uint32_t ULPIAR;
    __IO uint32_t ULPICSM;
    __IO uint32_t ULPIEVBUSD;
    __IO uint32_t ULPIEVBUSI;
    uint32_t RESERVED3[1];
    __IO uint32_t PCCI;
    __IO uint32_t PTCI;
    __IO uint32_t ULPIPD;
    uint32_t RESERVED4[3];
    __IO uint32_t FHMOD;
    __IO uint32_t FDMOD;
    uint32_t RESERVED5[1];
} stc_usbhs_gusbcfg_bit_t;

typedef struct {
    __IO uint32_t CSRST;
    __IO uint32_t HSRST;
    __IO uint32_t FCRST;
    uint32_t RESERVED0[1];
    __IO uint32_t RXFFLSH;
    __IO uint32_t TXFFLSH;
    uint32_t RESERVED1[24];
    __I  uint32_t DMAREQ;
    __I  uint32_t AHBIDL;
} stc_usbhs_grstctl_bit_t;

typedef struct {
    __I  uint32_t CMOD;
    __IO uint32_t MMIS;
    uint32_t RESERVED0[1];
    __IO uint32_t SOF;
    __I  uint32_t RXFNE;
    __I  uint32_t NPTXFE;
    __I  uint32_t GINAKEFF;
    __I  uint32_t GONAKEFF;
    uint32_t RESERVED1[2];
    __IO uint32_t ESUSP;
    __IO uint32_t USBSUSP;
    __IO uint32_t USBRST;
    __IO uint32_t ENUMDNE;
    __IO uint32_t ISOODRP;
    __IO uint32_t EOPF;
    uint32_t RESERVED2[2];
    __I  uint32_t IEPINT;
    __I  uint32_t OEPINT;
    __IO uint32_t IISOIXFR;
    __IO uint32_t IPXFR_INCOMPISOOUT;
    __IO uint32_t DATAFSUSP;
    uint32_t RESERVED3[1];
    __I  uint32_t HPRTINT;
    __I  uint32_t HCINT;
    __I  uint32_t PTXFE;
    __IO uint32_t LPMINT;
    __IO uint32_t CIDSCHG;
    __IO uint32_t DISCINT;
    __IO uint32_t VBUSVINT;
    __IO uint32_t WKUINT;
} stc_usbhs_gintsts_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t MMISM;
    uint32_t RESERVED1[1];
    __IO uint32_t SOFM;
    __IO uint32_t RXFNEM;
    __IO uint32_t NPTXFEM;
    __IO uint32_t GINAKEFFM;
    __IO uint32_t GONAKEFFM;
    uint32_t RESERVED2[2];
    __IO uint32_t ESUSPM;
    __IO uint32_t USBSUSPM;
    __IO uint32_t USBRSTM;
    __IO uint32_t ENUMDNEM;
    __IO uint32_t ISOODRPM;
    __IO uint32_t EOPFM;
    uint32_t RESERVED3[2];
    __IO uint32_t IEPIM;
    __IO uint32_t OEPIM;
    __IO uint32_t IISOIXFRM;
    __IO uint32_t IPXFRM_INCOMPISOOUTM;
    __IO uint32_t DATAFSUSPM;
    uint32_t RESERVED4[1];
    __IO uint32_t HPRTIM;
    __IO uint32_t HCIM;
    __IO uint32_t PTXFEM;
    __IO uint32_t LPMINTM;
    __IO uint32_t CIDSCHGM;
    __IO uint32_t DISCIM;
    __IO uint32_t VBUSVIM;
    __IO uint32_t WKUIM;
} stc_usbhs_gintmsk_bit_t;

typedef struct {
    __IO uint32_t LPMEN;
    __IO uint32_t LPMACK;
    uint32_t RESERVED0[4];
    __IO uint32_t REMWAKE;
    __IO uint32_t L1SSEN;
    uint32_t RESERVED1[4];
    __IO uint32_t L1DSEN;
    uint32_t RESERVED2[2];
    __I  uint32_t SLPSTS;
    __I  uint32_t L1RSMOK;
    uint32_t RESERVED3[7];
    __IO uint32_t SENDLPM;
    uint32_t RESERVED4[3];
    __IO uint32_t ENBSEL;
    uint32_t RESERVED5[3];
} stc_usbhs_glpmcfg_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t FSLSS;
    uint32_t RESERVED1[29];
} stc_usbhs_hcfg_bit_t;

typedef struct {
    __I  uint32_t PCSTS;
    __IO uint32_t PCDET;
    __IO uint32_t PENA;
    __IO uint32_t PENCHNG;
    __IO uint32_t POCA;
    __IO uint32_t POCCHNG;
    __IO uint32_t PRES;
    __IO uint32_t PSUSP;
    __IO uint32_t PRST;
    uint32_t RESERVED0[3];
    __IO uint32_t PWPR;
    uint32_t RESERVED1[19];
} stc_usbhs_hprt_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __IO uint32_t EPDIR;
    uint32_t RESERVED1[1];
    __IO uint32_t LSDEV;
    uint32_t RESERVED2[11];
    __IO uint32_t ODDFRM;
    __IO uint32_t CHDIS;
    __IO uint32_t CHENA;
} stc_usbhs_hcchar_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t COMPLSPLT;
    uint32_t RESERVED1[14];
    __IO uint32_t SPLITEN;
} stc_usbhs_hcsplt_bit_t;

typedef struct {
    __IO uint32_t XFRC;
    __IO uint32_t CHH;
    __IO uint32_t AHBERR;
    __IO uint32_t STALL;
    __IO uint32_t NAK;
    __IO uint32_t ACK;
    __IO uint32_t NYET;
    __IO uint32_t TXERR;
    __IO uint32_t BBERR;
    __IO uint32_t FRMOR;
    __IO uint32_t DTERR;
    uint32_t RESERVED0[21];
} stc_usbhs_hcint_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t CHHM;
    __IO uint32_t AHBERRM;
    __IO uint32_t STALLM;
    __IO uint32_t NAKM;
    __IO uint32_t ACKM;
    __IO uint32_t NYETM;
    __IO uint32_t TXERRM;
    __IO uint32_t BBERRM;
    __IO uint32_t FRMORM;
    __IO uint32_t DTERRM;
    uint32_t RESERVED0[21];
} stc_usbhs_hcintmsk_bit_t;

typedef struct {
    uint32_t RESERVED0[31];
    __IO uint32_t DOPING;
} stc_usbhs_hctsiz_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t NZLSOHSK;
    uint32_t RESERVED1[29];
} stc_usbhs_dcfg_bit_t;

typedef struct {
    __IO uint32_t RWUSIG;
    __IO uint32_t SDIS;
    __I  uint32_t GINSTS;
    __I  uint32_t GONSTS;
    uint32_t RESERVED0[3];
    __IO uint32_t SGINAK;
    __IO uint32_t CGINAK;
    __IO uint32_t SGONAK;
    __IO uint32_t CGONAK;
    __IO uint32_t POPRGDNE;
    uint32_t RESERVED1[20];
} stc_usbhs_dctl_bit_t;

typedef struct {
    __I  uint32_t SUSPSTS;
    uint32_t RESERVED0[2];
    __I  uint32_t EERR;
    uint32_t RESERVED1[28];
} stc_usbhs_dsts_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t EPDM;
    uint32_t RESERVED0[1];
    __IO uint32_t TOM;
    __IO uint32_t TTXFEMSK;
    __IO uint32_t INEPNMM;
    __IO uint32_t INEPNEM;
    uint32_t RESERVED1[1];
    __IO uint32_t TXFURM;
    uint32_t RESERVED2[4];
    __IO uint32_t NAKM;
    uint32_t RESERVED3[18];
} stc_usbhs_diepmsk_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t EPDM;
    uint32_t RESERVED0[1];
    __IO uint32_t STUPM;
    __IO uint32_t OTEPDM;
    uint32_t RESERVED1[1];
    __IO uint32_t B2BSTUP;
    uint32_t RESERVED2[1];
    __IO uint32_t OPEM;
    uint32_t RESERVED3[5];
    __IO uint32_t NYETM;
    uint32_t RESERVED4[17];
} stc_usbhs_doepmsk_bit_t;

typedef struct {
    __IO uint32_t NONISOTHREN;
    __IO uint32_t ISOTHREN;
    uint32_t RESERVED0[14];
    __IO uint32_t RXTHREN;
    uint32_t RESERVED1[10];
    __IO uint32_t ARPEN;
    uint32_t RESERVED2[4];
} stc_usbhs_dthrctl_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t IEP1INT;
    uint32_t RESERVED1[15];
    __IO uint32_t OEP1INT;
    uint32_t RESERVED2[14];
} stc_usbhs_deachint_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t IEP1INTM;
    uint32_t RESERVED1[15];
    __IO uint32_t OEP1INTM;
    uint32_t RESERVED2[14];
} stc_usbhs_deachintmsk_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t EPDM;
    uint32_t RESERVED0[1];
    __IO uint32_t TOM;
    __IO uint32_t TTXFEMSK;
    __IO uint32_t INEPNMM;
    __IO uint32_t INEPNEM;
    uint32_t RESERVED1[1];
    __IO uint32_t TXFURM;
    uint32_t RESERVED2[4];
    __IO uint32_t NAKM;
    uint32_t RESERVED3[18];
} stc_usbhs_diepeachmsk1_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t EPDM;
    uint32_t RESERVED0[1];
    __IO uint32_t STUPM;
    __IO uint32_t OTEPDM;
    uint32_t RESERVED1[1];
    __IO uint32_t B2BSTUP;
    uint32_t RESERVED2[1];
    __IO uint32_t OPEM;
    uint32_t RESERVED3[5];
    __IO uint32_t NYETM;
    uint32_t RESERVED4[17];
} stc_usbhs_doepeachmsk1_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __I  uint32_t USBAEP;
    uint32_t RESERVED1[1];
    __I  uint32_t NAKSTS;
    uint32_t RESERVED2[3];
    __IO uint32_t STALL;
    uint32_t RESERVED3[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    uint32_t RESERVED4[2];
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbhs_diepctl0_bit_t;

typedef struct {
    __IO uint32_t XFRC;
    __IO uint32_t EPDISD;
    uint32_t RESERVED0[1];
    __IO uint32_t TOC;
    __IO uint32_t TTXFE;
    uint32_t RESERVED1[1];
    __IO uint32_t INEPNE;
    __I  uint32_t TXFE;
    __IO uint32_t TXFIFOUDRN;
    uint32_t RESERVED2[2];
    __IO uint32_t PKTDRPSTS;
    __IO uint32_t BERR;
    __IO uint32_t NAK;
    uint32_t RESERVED3[18];
} stc_usbhs_diepint_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __IO uint32_t USBAEP;
    __I  uint32_t EONUM_DPID;
    __I  uint32_t NAKSTS;
    uint32_t RESERVED1[3];
    __IO uint32_t STALL;
    uint32_t RESERVED2[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    __IO uint32_t SD0PID_SEVNFRM;
    __IO uint32_t SODDFRM;
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbhs_diepctl_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __I  uint32_t USBAEP;
    uint32_t RESERVED1[1];
    __I  uint32_t NAKSTS;
    uint32_t RESERVED2[2];
    __IO uint32_t SNPM;
    __IO uint32_t STALL;
    uint32_t RESERVED3[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    uint32_t RESERVED4[2];
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbhs_doepctl0_bit_t;

typedef struct {
    __IO uint32_t XFRC;
    __IO uint32_t EPDISD;
    uint32_t RESERVED0[1];
    __IO uint32_t STUP;
    __IO uint32_t OTEPDIS;
    uint32_t RESERVED1[1];
    __IO uint32_t B2BSTUP;
    uint32_t RESERVED2[7];
    __IO uint32_t NYET;
    uint32_t RESERVED3[17];
} stc_usbhs_doepint_bit_t;

typedef struct {
    uint32_t RESERVED0[19];
    __IO uint32_t PKTCNT;
    uint32_t RESERVED1[12];
} stc_usbhs_doeptsiz0_bit_t;

typedef struct {
    uint32_t RESERVED0[15];
    __IO uint32_t USBAEP;
    __I  uint32_t DPID;
    __I  uint32_t NAKSTS;
    uint32_t RESERVED1[2];
    __IO uint32_t SNPM;
    __IO uint32_t STALL;
    uint32_t RESERVED2[4];
    __IO uint32_t CNAK;
    __IO uint32_t SNAK;
    __IO uint32_t SD0PID;
    __IO uint32_t SD1PID;
    __IO uint32_t EPDIS;
    __IO uint32_t EPENA;
} stc_usbhs_doepctl_bit_t;

typedef struct {
    __IO uint32_t STPPCLK;
    __IO uint32_t GATEHCLK;
    uint32_t RESERVED0[3];
    __IO uint32_t ENL1GTG;
    __IO uint32_t PHYSLEEP;
    __IO uint32_t SUSP;
    uint32_t RESERVED1[24];
} stc_usbhs_gcctl_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t SLPOFF;
    uint32_t RESERVED1[14];
    __IO uint32_t ITS;
} stc_wdt_cr_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t UDF;
    __IO uint32_t REF;
    uint32_t RESERVED1[14];
} stc_wdt_sr_bit_t;


typedef struct {
    stc_adc_str_bit_t                        STR_b;
    uint32_t                                 RESERVED0[8];
    stc_adc_cr0_bit_t                        CR0_b;
    stc_adc_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED1[32];
    stc_adc_trgsr_bit_t                      TRGSR_b;
    uint32_t                                 RESERVED2[96];
    stc_adc_exchselr_bit_t                   EXCHSELR_b;
    uint32_t                                 RESERVED3[344];
    stc_adc_isr_bit_t                        ISR_b;
    stc_adc_icr_bit_t                        ICR_b;
    stc_adc_isclrr_bit_t                     ISCLRR_b;
    uint32_t                                 RESERVED4[40];
    stc_adc_synccr_bit_t                     SYNCCR_b;
    uint32_t                                 RESERVED5[656];
    stc_adc_awdcr_bit_t                      AWDCR_b;
    stc_adc_awdsr_bit_t                      AWDSR_b;
    stc_adc_awdsclrr_bit_t                   AWDSCLRR_b;
} bCM_ADC_TypeDef;

typedef struct {
    stc_aes_cr_bit_t                         CR_b;
} bCM_AES_TypeDef;

typedef struct {
    stc_aos_intsfttrg_bit_t                  INTSFTTRG_b;
    uint32_t                                 RESERVED0[2912];
    stc_aos_pevntnfcr_bit_t                  PEVNTNFCR_b;
} bCM_AOS_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[1280];
    stc_can_cfg_stat_bit_t                   CFG_STAT_b;
    stc_can_tcmd_bit_t                       TCMD_b;
    stc_can_tctrl_bit_t                      TCTRL_b;
    stc_can_rctrl_bit_t                      RCTRL_b;
    stc_can_rtie_bit_t                       RTIE_b;
    stc_can_rtif_bit_t                       RTIF_b;
    stc_can_errint_bit_t                     ERRINT_b;
    uint32_t                                 RESERVED1[80];
    stc_can_tdc_bit_t                        TDC_b;
    uint32_t                                 RESERVED2[16];
    stc_can_acfctrl_bit_t                    ACFCTRL_b;
    uint32_t                                 RESERVED3[8];
    stc_can_acfen_bit_t                      ACFEN_b;
    stc_can_acf_bit_t                        ACF_b;
    uint32_t                                 RESERVED4[16];
    stc_can_tbslot_bit_t                     TBSLOT_b;
    stc_can_ttcfg_bit_t                      TTCFG_b;
    stc_can_ref_msg_bit_t                    REF_MSG_b;
} bCM_CAN_TypeDef;

typedef struct {
    stc_cmp_mdr_bit_t                        MDR_b;
    stc_cmp_fir_bit_t                        FIR_b;
    stc_cmp_ocr_bit_t                        OCR_b;
    uint32_t                                 RESERVED0[8];
    stc_cmp_twsr_bit_t                       TWSR_b;
    stc_cmp_twpr_bit_t                       TWPR_b;
} bCM_CMP_TypeDef;

typedef struct {
    stc_cmu_xtal32cr_bit_t                   XTAL32CR_b;
    uint32_t                                 RESERVED0[24];
    stc_cmu_xtal32cfgr_bit_t                 XTAL32CFGR_b;
    uint32_t                                 RESERVED1[184];
    stc_cmu_lrccr_bit_t                      LRCCR_b;
    uint32_t                                 RESERVED2[17112];
    stc_cmu_xtalcfgr_bit_t                   XTALCFGR_b;
    uint32_t                                 RESERVED3[236936];
    stc_cmu_pllhcr_bit_t                     PLLHCR_b;
    uint32_t                                 RESERVED4[24];
    stc_cmu_pllacr_bit_t                     PLLACR_b;
    uint32_t                                 RESERVED5[24];
    stc_cmu_xtalcr_bit_t                     XTALCR_b;
    uint32_t                                 RESERVED6[24];
    stc_cmu_hrccr_bit_t                      HRCCR_b;
    uint32_t                                 RESERVED7[8];
    stc_cmu_mrccr_bit_t                      MRCCR_b;
    uint32_t                                 RESERVED8[24];
    stc_cmu_oscstbsr_bit_t                   OSCSTBSR_b;
    stc_cmu_mcocfgr_bit_t                    MCO1CFGR_b;
    stc_cmu_mcocfgr_bit_t                    MCO2CFGR_b;
    stc_cmu_tpiuckcfgr_bit_t                 TPIUCKCFGR_b;
    stc_cmu_xtalstdcr_bit_t                  XTALSTDCR_b;
    stc_cmu_xtalstdsr_bit_t                  XTALSTDSR_b;
    uint32_t                                 RESERVED9[1520];
    stc_cmu_pllhcfgr_bit_t                   PLLHCFGR_b;
} bCM_CMU_TypeDef;

typedef struct {
    stc_crc_cr_bit_t                         CR_b;
} bCM_CRC_TypeDef;

typedef struct {
    stc_ctc_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED0[32];
    stc_ctc_str_bit_t                        STR_b;
} bCM_CTC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_dac_dacr_bit_t                       DACR_b;
    stc_dac_daadpcr_bit_t                    DAADPCR_b;
    uint32_t                                 RESERVED1[160];
    stc_dac_daocr_bit_t                      DAOCR_b;
} bCM_DAC_TypeDef;

typedef struct {
    stc_dcu_ctl_bit_t                        CTL_b;
    stc_dcu_flag_bit_t                       FLAG_b;
    uint32_t                                 RESERVED0[96];
    stc_dcu_flagclr_bit_t                    FLAGCLR_b;
    stc_dcu_intevtsel_bit_t                  INTEVTSEL_b;
} bCM_DCU_TypeDef;

typedef struct {
    stc_dma_en_bit_t                         EN_b;
    stc_dma_intstat0_bit_t                   INTSTAT0_b;
    stc_dma_intstat1_bit_t                   INTSTAT1_b;
    stc_dma_intmask0_bit_t                   INTMASK0_b;
    stc_dma_intmask1_bit_t                   INTMASK1_b;
    stc_dma_intclr0_bit_t                    INTCLR0_b;
    stc_dma_intclr1_bit_t                    INTCLR1_b;
    uint32_t                                 RESERVED0[32];
    stc_dma_reqstat_bit_t                    REQSTAT_b;
    stc_dma_chstat_bit_t                     CHSTAT_b;
    uint32_t                                 RESERVED1[32];
    stc_dma_rcfgctl_bit_t                    RCFGCTL_b;
    uint32_t                                 RESERVED2[352];
    stc_dma_chctl_bit_t                      CHCTL0_b;
    uint32_t                                 RESERVED3[480];
    stc_dma_chctl_bit_t                      CHCTL1_b;
    uint32_t                                 RESERVED4[480];
    stc_dma_chctl_bit_t                      CHCTL2_b;
    uint32_t                                 RESERVED5[480];
    stc_dma_chctl_bit_t                      CHCTL3_b;
    uint32_t                                 RESERVED6[480];
    stc_dma_chctl_bit_t                      CHCTL4_b;
    uint32_t                                 RESERVED7[480];
    stc_dma_chctl_bit_t                      CHCTL5_b;
    uint32_t                                 RESERVED8[480];
    stc_dma_chctl_bit_t                      CHCTL6_b;
    uint32_t                                 RESERVED9[480];
    stc_dma_chctl_bit_t                      CHCTL7_b;
} bCM_DMA_TypeDef;

typedef struct {
    stc_dvp_ctr_bit_t                        CTR_b;
    uint32_t                                 RESERVED0[32];
    stc_dvp_str_bit_t                        STR_b;
    stc_dvp_ier_bit_t                        IER_b;
} bCM_DVP_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[160];
    stc_efm_fstp_bit_t                       FSTP_b;
    stc_efm_frmc_bit_t                       FRMC_b;
    stc_efm_fwmc_bit_t                       FWMC_b;
    stc_efm_fsr_bit_t                        FSR_b;
    stc_efm_fsclr_bit_t                      FSCLR_b;
    stc_efm_fite_bit_t                       FITE_b;
    stc_efm_fswp_bit_t                       FSWP_b;
    uint32_t                                 RESERVED1[1696];
    stc_efm_mmf_remcr_bit_t                  MMF_REMCR0_b;
    stc_efm_mmf_remcr_bit_t                  MMF_REMCR1_b;
    uint32_t                                 RESERVED2[1056];
    stc_efm_f0nwprt0_bit_t                   F0NWPRT0_b;
    stc_efm_f0nwprt1_bit_t                   F0NWPRT1_b;
    stc_efm_f0nwprt2_bit_t                   F0NWPRT2_b;
    stc_efm_f0nwprt3_bit_t                   F0NWPRT3_b;
    stc_efm_f1nwprt0_bit_t                   F1NWPRT0_b;
    stc_efm_f1nwprt1_bit_t                   F1NWPRT1_b;
    stc_efm_f1nwprt2_bit_t                   F1NWPRT2_b;
    stc_efm_f1nwprt3_bit_t                   F1NWPRT3_b;
} bCM_EFM_TypeDef;

typedef struct {
    stc_emb_ctl1_bit_t                       CTL1_b;
    stc_emb_ctl2_bit_t                       CTL2_b;
    stc_emb_soe_bit_t                        SOE_b;
    stc_emb_stat_bit_t                       STAT_b;
    stc_emb_statclr_bit_t                    STATCLR_b;
    stc_emb_inten_bit_t                      INTEN_b;
    stc_emb_rlssel_bit_t                     RLSSEL_b;
} bCM_EMB_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[172160];
    stc_eth_mac_ifconfr_bit_t                MAC_IFCONFR_b;
    uint32_t                                 RESERVED1[352096];
    stc_eth_mac_configr_bit_t                MAC_CONFIGR_b;
    stc_eth_mac_fltctlr_bit_t                MAC_FLTCTLR_b;
    uint32_t                                 RESERVED2[64];
    stc_eth_mac_smiaddr_bit_t                MAC_SMIADDR_b;
    uint32_t                                 RESERVED3[32];
    stc_eth_mac_floctlr_bit_t                MAC_FLOCTLR_b;
    stc_eth_mac_vtafltr_bit_t                MAC_VTAFLTR_b;
    uint32_t                                 RESERVED4[32];
    stc_eth_mac_macstsr_bit_t                MAC_MACSTSR_b;
    uint32_t                                 RESERVED5[32];
    stc_eth_mac_pmtctlr_bit_t                MAC_PMTCTLR_b;
    uint32_t                                 RESERVED6[64];
    stc_eth_mac_intstsr_bit_t                MAC_INTSTSR_b;
    stc_eth_mac_intmskr_bit_t                MAC_INTMSKR_b;
    stc_eth_mac_macadhr0_bit_t               MAC_MACADHR0_b;
    uint32_t                                 RESERVED7[32];
    stc_eth_mac_macadhr1_bit_t               MAC_MACADHR1_b;
    uint32_t                                 RESERVED8[32];
    stc_eth_mac_macadhr2_bit_t               MAC_MACADHR2_b;
    uint32_t                                 RESERVED9[32];
    stc_eth_mac_macadhr3_bit_t               MAC_MACADHR3_b;
    uint32_t                                 RESERVED10[32];
    stc_eth_mac_macadhr4_bit_t               MAC_MACADHR4_b;
    uint32_t                                 RESERVED11[1248];
    stc_eth_mmc_mmcctlr_bit_t                MMC_MMCCTLR_b;
    stc_eth_mmc_revstsr_bit_t                MMC_REVSTSR_b;
    stc_eth_mmc_trsstsr_bit_t                MMC_TRSSTSR_b;
    stc_eth_mmc_ritctlr_bit_t                MMC_RITCTLR_b;
    stc_eth_mmc_titctlr_bit_t                MMC_TITCTLR_b;
    uint32_t                                 RESERVED12[5984];
    stc_eth_mac_l34ctlr_bit_t                MAC_L34CTLR_b;
    uint32_t                                 RESERVED13[3072];
    stc_eth_mac_vtactlr_bit_t                MAC_VTACTLR_b;
    uint32_t                                 RESERVED14[3008];
    stc_eth_ptp_tspctlr_bit_t                PTP_TSPCTLR_b;
    uint32_t                                 RESERVED15[128];
    stc_eth_ptp_tmunser_bit_t                PTP_TMUNSER_b;
    uint32_t                                 RESERVED16[128];
    stc_eth_ptp_tspstsr_bit_t                PTP_TSPSTSR_b;
    stc_eth_ptp_ppsctlr_bit_t                PTP_PPSCTLR_b;
    uint32_t                                 RESERVED17[18048];
    stc_eth_dma_busmodr_bit_t                DMA_BUSMODR_b;
    uint32_t                                 RESERVED18[128];
    stc_eth_dma_dmastsr_bit_t                DMA_DMASTSR_b;
    stc_eth_dma_oprmodr_bit_t                DMA_OPRMODR_b;
    stc_eth_dma_intenar_bit_t                DMA_INTENAR_b;
    stc_eth_dma_rfrcntr_bit_t                DMA_RFRCNTR_b;
} bCM_ETH_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[96];
    stc_fcm_str_bit_t                        STR_b;
    uint32_t                                 RESERVED1[32];
    stc_fcm_rccr_bit_t                       RCCR_b;
    stc_fcm_rier_bit_t                       RIER_b;
    stc_fcm_sr_bit_t                         SR_b;
    stc_fcm_clr_bit_t                        CLR_b;
} bCM_FCM_TypeDef;

typedef struct {
    stc_fmac_enr_bit_t                       ENR_b;
    uint32_t                                 RESERVED0[32];
    stc_fmac_ier_bit_t                       IER_b;
    uint32_t                                 RESERVED1[96];
    stc_fmac_str_bit_t                       STR_b;
} bCM_FMAC_TypeDef;

typedef struct {
    stc_gpio_pidr_bit_t                      PIDRA_b;
    uint32_t                                 RESERVED0[16];
    stc_gpio_podr_bit_t                      PODRA_b;
    stc_gpio_poer_bit_t                      POERA_b;
    stc_gpio_posr_bit_t                      POSRA_b;
    stc_gpio_porr_bit_t                      PORRA_b;
    stc_gpio_potr_bit_t                      POTRA_b;
    uint32_t                                 RESERVED1[16];
    stc_gpio_pidr_bit_t                      PIDRB_b;
    uint32_t                                 RESERVED2[16];
    stc_gpio_podr_bit_t                      PODRB_b;
    stc_gpio_poer_bit_t                      POERB_b;
    stc_gpio_posr_bit_t                      POSRB_b;
    stc_gpio_porr_bit_t                      PORRB_b;
    stc_gpio_potr_bit_t                      POTRB_b;
    uint32_t                                 RESERVED3[16];
    stc_gpio_pidr_bit_t                      PIDRC_b;
    uint32_t                                 RESERVED4[16];
    stc_gpio_podr_bit_t                      PODRC_b;
    stc_gpio_poer_bit_t                      POERC_b;
    stc_gpio_posr_bit_t                      POSRC_b;
    stc_gpio_porr_bit_t                      PORRC_b;
    stc_gpio_potr_bit_t                      POTRC_b;
    uint32_t                                 RESERVED5[16];
    stc_gpio_pidr_bit_t                      PIDRD_b;
    uint32_t                                 RESERVED6[16];
    stc_gpio_podr_bit_t                      PODRD_b;
    stc_gpio_poer_bit_t                      POERD_b;
    stc_gpio_posr_bit_t                      POSRD_b;
    stc_gpio_porr_bit_t                      PORRD_b;
    stc_gpio_potr_bit_t                      POTRD_b;
    uint32_t                                 RESERVED7[16];
    stc_gpio_pidr_bit_t                      PIDRE_b;
    uint32_t                                 RESERVED8[16];
    stc_gpio_podr_bit_t                      PODRE_b;
    stc_gpio_poer_bit_t                      POERE_b;
    stc_gpio_posr_bit_t                      POSRE_b;
    stc_gpio_porr_bit_t                      PORRE_b;
    stc_gpio_potr_bit_t                      POTRE_b;
    uint32_t                                 RESERVED9[16];
    stc_gpio_pidr_bit_t                      PIDRF_b;
    uint32_t                                 RESERVED10[16];
    stc_gpio_podr_bit_t                      PODRF_b;
    stc_gpio_poer_bit_t                      POERF_b;
    stc_gpio_posr_bit_t                      POSRF_b;
    stc_gpio_porr_bit_t                      PORRF_b;
    stc_gpio_potr_bit_t                      POTRF_b;
    uint32_t                                 RESERVED11[16];
    stc_gpio_pidr_bit_t                      PIDRG_b;
    uint32_t                                 RESERVED12[16];
    stc_gpio_podr_bit_t                      PODRG_b;
    stc_gpio_poer_bit_t                      POERG_b;
    stc_gpio_posr_bit_t                      POSRG_b;
    stc_gpio_porr_bit_t                      PORRG_b;
    stc_gpio_potr_bit_t                      POTRG_b;
    uint32_t                                 RESERVED13[16];
    stc_gpio_pidr_bit_t                      PIDRH_b;
    uint32_t                                 RESERVED14[16];
    stc_gpio_podr_bit_t                      PODRH_b;
    stc_gpio_poer_bit_t                      POERH_b;
    stc_gpio_posr_bit_t                      POSRH_b;
    stc_gpio_porr_bit_t                      PORRH_b;
    stc_gpio_potr_bit_t                      POTRH_b;
    uint32_t                                 RESERVED15[16];
    stc_gpio_pidri_bit_t                     PIDRI_b;
    uint32_t                                 RESERVED16[16];
    stc_gpio_podri_bit_t                     PODRI_b;
    stc_gpio_poeri_bit_t                     POERI_b;
    stc_gpio_posri_bit_t                     POSRI_b;
    stc_gpio_porri_bit_t                     PORRI_b;
    stc_gpio_potri_bit_t                     POTRI_b;
    uint32_t                                 RESERVED17[7024];
    stc_gpio_pwpr_bit_t                      PWPR_b;
    uint32_t                                 RESERVED18[16];
    stc_gpio_pcr_bit_t                       PCRA0_b;
    stc_gpio_pfsr_bit_t                      PFSRA0_b;
    stc_gpio_pcr_bit_t                       PCRA1_b;
    stc_gpio_pfsr_bit_t                      PFSRA1_b;
    stc_gpio_pcr_bit_t                       PCRA2_b;
    stc_gpio_pfsr_bit_t                      PFSRA2_b;
    stc_gpio_pcr_bit_t                       PCRA3_b;
    stc_gpio_pfsr_bit_t                      PFSRA3_b;
    stc_gpio_pcr_bit_t                       PCRA4_b;
    stc_gpio_pfsr_bit_t                      PFSRA4_b;
    stc_gpio_pcr_bit_t                       PCRA5_b;
    stc_gpio_pfsr_bit_t                      PFSRA5_b;
    stc_gpio_pcr_bit_t                       PCRA6_b;
    stc_gpio_pfsr_bit_t                      PFSRA6_b;
    stc_gpio_pcr_bit_t                       PCRA7_b;
    stc_gpio_pfsr_bit_t                      PFSRA7_b;
    stc_gpio_pcr_bit_t                       PCRA8_b;
    stc_gpio_pfsr_bit_t                      PFSRA8_b;
    stc_gpio_pcr_bit_t                       PCRA9_b;
    stc_gpio_pfsr_bit_t                      PFSRA9_b;
    stc_gpio_pcr_bit_t                       PCRA10_b;
    stc_gpio_pfsr_bit_t                      PFSRA10_b;
    stc_gpio_pcr_bit_t                       PCRA11_b;
    stc_gpio_pfsr_bit_t                      PFSRA11_b;
    stc_gpio_pcr_bit_t                       PCRA12_b;
    stc_gpio_pfsr_bit_t                      PFSRA12_b;
    stc_gpio_pcr_bit_t                       PCRA13_b;
    stc_gpio_pfsr_bit_t                      PFSRA13_b;
    stc_gpio_pcr_bit_t                       PCRA14_b;
    stc_gpio_pfsr_bit_t                      PFSRA14_b;
    stc_gpio_pcr_bit_t                       PCRA15_b;
    stc_gpio_pfsr_bit_t                      PFSRA15_b;
    stc_gpio_pcr_bit_t                       PCRB0_b;
    stc_gpio_pfsr_bit_t                      PFSRB0_b;
    stc_gpio_pcr_bit_t                       PCRB1_b;
    stc_gpio_pfsr_bit_t                      PFSRB1_b;
    stc_gpio_pcr_bit_t                       PCRB2_b;
    stc_gpio_pfsr_bit_t                      PFSRB2_b;
    stc_gpio_pcr_bit_t                       PCRB3_b;
    stc_gpio_pfsr_bit_t                      PFSRB3_b;
    stc_gpio_pcr_bit_t                       PCRB4_b;
    stc_gpio_pfsr_bit_t                      PFSRB4_b;
    stc_gpio_pcr_bit_t                       PCRB5_b;
    stc_gpio_pfsr_bit_t                      PFSRB5_b;
    stc_gpio_pcr_bit_t                       PCRB6_b;
    stc_gpio_pfsr_bit_t                      PFSRB6_b;
    stc_gpio_pcr_bit_t                       PCRB7_b;
    stc_gpio_pfsr_bit_t                      PFSRB7_b;
    stc_gpio_pcr_bit_t                       PCRB8_b;
    stc_gpio_pfsr_bit_t                      PFSRB8_b;
    stc_gpio_pcr_bit_t                       PCRB9_b;
    stc_gpio_pfsr_bit_t                      PFSRB9_b;
    stc_gpio_pcr_bit_t                       PCRB10_b;
    stc_gpio_pfsr_bit_t                      PFSRB10_b;
    stc_gpio_pcr_bit_t                       PCRB11_b;
    stc_gpio_pfsr_bit_t                      PFSRB11_b;
    stc_gpio_pcr_bit_t                       PCRB12_b;
    stc_gpio_pfsr_bit_t                      PFSRB12_b;
    stc_gpio_pcr_bit_t                       PCRB13_b;
    stc_gpio_pfsr_bit_t                      PFSRB13_b;
    stc_gpio_pcr_bit_t                       PCRB14_b;
    stc_gpio_pfsr_bit_t                      PFSRB14_b;
    stc_gpio_pcr_bit_t                       PCRB15_b;
    stc_gpio_pfsr_bit_t                      PFSRB15_b;
    stc_gpio_pcr_bit_t                       PCRC0_b;
    stc_gpio_pfsr_bit_t                      PFSRC0_b;
    stc_gpio_pcr_bit_t                       PCRC1_b;
    stc_gpio_pfsr_bit_t                      PFSRC1_b;
    stc_gpio_pcr_bit_t                       PCRC2_b;
    stc_gpio_pfsr_bit_t                      PFSRC2_b;
    stc_gpio_pcr_bit_t                       PCRC3_b;
    stc_gpio_pfsr_bit_t                      PFSRC3_b;
    stc_gpio_pcr_bit_t                       PCRC4_b;
    stc_gpio_pfsr_bit_t                      PFSRC4_b;
    stc_gpio_pcr_bit_t                       PCRC5_b;
    stc_gpio_pfsr_bit_t                      PFSRC5_b;
    stc_gpio_pcr_bit_t                       PCRC6_b;
    stc_gpio_pfsr_bit_t                      PFSRC6_b;
    stc_gpio_pcr_bit_t                       PCRC7_b;
    stc_gpio_pfsr_bit_t                      PFSRC7_b;
    stc_gpio_pcr_bit_t                       PCRC8_b;
    stc_gpio_pfsr_bit_t                      PFSRC8_b;
    stc_gpio_pcr_bit_t                       PCRC9_b;
    stc_gpio_pfsr_bit_t                      PFSRC9_b;
    stc_gpio_pcr_bit_t                       PCRC10_b;
    stc_gpio_pfsr_bit_t                      PFSRC10_b;
    stc_gpio_pcr_bit_t                       PCRC11_b;
    stc_gpio_pfsr_bit_t                      PFSRC11_b;
    stc_gpio_pcr_bit_t                       PCRC12_b;
    stc_gpio_pfsr_bit_t                      PFSRC12_b;
    stc_gpio_pcr_bit_t                       PCRC13_b;
    stc_gpio_pfsr_bit_t                      PFSRC13_b;
    stc_gpio_pcr_bit_t                       PCRC14_b;
    stc_gpio_pfsr_bit_t                      PFSRC14_b;
    stc_gpio_pcr_bit_t                       PCRC15_b;
    stc_gpio_pfsr_bit_t                      PFSRC15_b;
    stc_gpio_pcr_bit_t                       PCRD0_b;
    stc_gpio_pfsr_bit_t                      PFSRD0_b;
    stc_gpio_pcr_bit_t                       PCRD1_b;
    stc_gpio_pfsr_bit_t                      PFSRD1_b;
    stc_gpio_pcr_bit_t                       PCRD2_b;
    stc_gpio_pfsr_bit_t                      PFSRD2_b;
    stc_gpio_pcr_bit_t                       PCRD3_b;
    stc_gpio_pfsr_bit_t                      PFSRD3_b;
    stc_gpio_pcr_bit_t                       PCRD4_b;
    stc_gpio_pfsr_bit_t                      PFSRD4_b;
    stc_gpio_pcr_bit_t                       PCRD5_b;
    stc_gpio_pfsr_bit_t                      PFSRD5_b;
    stc_gpio_pcr_bit_t                       PCRD6_b;
    stc_gpio_pfsr_bit_t                      PFSRD6_b;
    stc_gpio_pcr_bit_t                       PCRD7_b;
    stc_gpio_pfsr_bit_t                      PFSRD7_b;
    stc_gpio_pcr_bit_t                       PCRD8_b;
    stc_gpio_pfsr_bit_t                      PFSRD8_b;
    stc_gpio_pcr_bit_t                       PCRD9_b;
    stc_gpio_pfsr_bit_t                      PFSRD9_b;
    stc_gpio_pcr_bit_t                       PCRD10_b;
    stc_gpio_pfsr_bit_t                      PFSRD10_b;
    stc_gpio_pcr_bit_t                       PCRD11_b;
    stc_gpio_pfsr_bit_t                      PFSRD11_b;
    stc_gpio_pcr_bit_t                       PCRD12_b;
    stc_gpio_pfsr_bit_t                      PFSRD12_b;
    stc_gpio_pcr_bit_t                       PCRD13_b;
    stc_gpio_pfsr_bit_t                      PFSRD13_b;
    stc_gpio_pcr_bit_t                       PCRD14_b;
    stc_gpio_pfsr_bit_t                      PFSRD14_b;
    stc_gpio_pcr_bit_t                       PCRD15_b;
    stc_gpio_pfsr_bit_t                      PFSRD15_b;
    stc_gpio_pcr_bit_t                       PCRE0_b;
    stc_gpio_pfsr_bit_t                      PFSRE0_b;
    stc_gpio_pcr_bit_t                       PCRE1_b;
    stc_gpio_pfsr_bit_t                      PFSRE1_b;
    stc_gpio_pcr_bit_t                       PCRE2_b;
    stc_gpio_pfsr_bit_t                      PFSRE2_b;
    stc_gpio_pcr_bit_t                       PCRE3_b;
    stc_gpio_pfsr_bit_t                      PFSRE3_b;
    stc_gpio_pcr_bit_t                       PCRE4_b;
    stc_gpio_pfsr_bit_t                      PFSRE4_b;
    stc_gpio_pcr_bit_t                       PCRE5_b;
    stc_gpio_pfsr_bit_t                      PFSRE5_b;
    stc_gpio_pcr_bit_t                       PCRE6_b;
    stc_gpio_pfsr_bit_t                      PFSRE6_b;
    stc_gpio_pcr_bit_t                       PCRE7_b;
    stc_gpio_pfsr_bit_t                      PFSRE7_b;
    stc_gpio_pcr_bit_t                       PCRE8_b;
    stc_gpio_pfsr_bit_t                      PFSRE8_b;
    stc_gpio_pcr_bit_t                       PCRE9_b;
    stc_gpio_pfsr_bit_t                      PFSRE9_b;
    stc_gpio_pcr_bit_t                       PCRE10_b;
    stc_gpio_pfsr_bit_t                      PFSRE10_b;
    stc_gpio_pcr_bit_t                       PCRE11_b;
    stc_gpio_pfsr_bit_t                      PFSRE11_b;
    stc_gpio_pcr_bit_t                       PCRE12_b;
    stc_gpio_pfsr_bit_t                      PFSRE12_b;
    stc_gpio_pcr_bit_t                       PCRE13_b;
    stc_gpio_pfsr_bit_t                      PFSRE13_b;
    stc_gpio_pcr_bit_t                       PCRE14_b;
    stc_gpio_pfsr_bit_t                      PFSRE14_b;
    stc_gpio_pcr_bit_t                       PCRE15_b;
    stc_gpio_pfsr_bit_t                      PFSRE15_b;
    stc_gpio_pcr_bit_t                       PCRF0_b;
    stc_gpio_pfsr_bit_t                      PFSRF0_b;
    stc_gpio_pcr_bit_t                       PCRF1_b;
    stc_gpio_pfsr_bit_t                      PFSRF1_b;
    stc_gpio_pcr_bit_t                       PCRF2_b;
    stc_gpio_pfsr_bit_t                      PFSRF2_b;
    stc_gpio_pcr_bit_t                       PCRF3_b;
    stc_gpio_pfsr_bit_t                      PFSRF3_b;
    stc_gpio_pcr_bit_t                       PCRF4_b;
    stc_gpio_pfsr_bit_t                      PFSRF4_b;
    stc_gpio_pcr_bit_t                       PCRF5_b;
    stc_gpio_pfsr_bit_t                      PFSRF5_b;
    stc_gpio_pcr_bit_t                       PCRF6_b;
    stc_gpio_pfsr_bit_t                      PFSRF6_b;
    stc_gpio_pcr_bit_t                       PCRF7_b;
    stc_gpio_pfsr_bit_t                      PFSRF7_b;
    stc_gpio_pcr_bit_t                       PCRF8_b;
    stc_gpio_pfsr_bit_t                      PFSRF8_b;
    stc_gpio_pcr_bit_t                       PCRF9_b;
    stc_gpio_pfsr_bit_t                      PFSRF9_b;
    stc_gpio_pcr_bit_t                       PCRF10_b;
    stc_gpio_pfsr_bit_t                      PFSRF10_b;
    stc_gpio_pcr_bit_t                       PCRF11_b;
    stc_gpio_pfsr_bit_t                      PFSRF11_b;
    stc_gpio_pcr_bit_t                       PCRF12_b;
    stc_gpio_pfsr_bit_t                      PFSRF12_b;
    stc_gpio_pcr_bit_t                       PCRF13_b;
    stc_gpio_pfsr_bit_t                      PFSRF13_b;
    stc_gpio_pcr_bit_t                       PCRF14_b;
    stc_gpio_pfsr_bit_t                      PFSRF14_b;
    stc_gpio_pcr_bit_t                       PCRF15_b;
    stc_gpio_pfsr_bit_t                      PFSRF15_b;
    stc_gpio_pcr_bit_t                       PCRG0_b;
    stc_gpio_pfsr_bit_t                      PFSRG0_b;
    stc_gpio_pcr_bit_t                       PCRG1_b;
    stc_gpio_pfsr_bit_t                      PFSRG1_b;
    stc_gpio_pcr_bit_t                       PCRG2_b;
    stc_gpio_pfsr_bit_t                      PFSRG2_b;
    stc_gpio_pcr_bit_t                       PCRG3_b;
    stc_gpio_pfsr_bit_t                      PFSRG3_b;
    stc_gpio_pcr_bit_t                       PCRG4_b;
    stc_gpio_pfsr_bit_t                      PFSRG4_b;
    stc_gpio_pcr_bit_t                       PCRG5_b;
    stc_gpio_pfsr_bit_t                      PFSRG5_b;
    stc_gpio_pcr_bit_t                       PCRG6_b;
    stc_gpio_pfsr_bit_t                      PFSRG6_b;
    stc_gpio_pcr_bit_t                       PCRG7_b;
    stc_gpio_pfsr_bit_t                      PFSRG7_b;
    stc_gpio_pcr_bit_t                       PCRG8_b;
    stc_gpio_pfsr_bit_t                      PFSRG8_b;
    stc_gpio_pcr_bit_t                       PCRG9_b;
    stc_gpio_pfsr_bit_t                      PFSRG9_b;
    stc_gpio_pcr_bit_t                       PCRG10_b;
    stc_gpio_pfsr_bit_t                      PFSRG10_b;
    stc_gpio_pcr_bit_t                       PCRG11_b;
    stc_gpio_pfsr_bit_t                      PFSRG11_b;
    stc_gpio_pcr_bit_t                       PCRG12_b;
    stc_gpio_pfsr_bit_t                      PFSRG12_b;
    stc_gpio_pcr_bit_t                       PCRG13_b;
    stc_gpio_pfsr_bit_t                      PFSRG13_b;
    stc_gpio_pcr_bit_t                       PCRG14_b;
    stc_gpio_pfsr_bit_t                      PFSRG14_b;
    stc_gpio_pcr_bit_t                       PCRG15_b;
    stc_gpio_pfsr_bit_t                      PFSRG15_b;
    stc_gpio_pcr_bit_t                       PCRH0_b;
    stc_gpio_pfsr_bit_t                      PFSRH0_b;
    stc_gpio_pcr_bit_t                       PCRH1_b;
    stc_gpio_pfsr_bit_t                      PFSRH1_b;
    stc_gpio_pcr_bit_t                       PCRH2_b;
    stc_gpio_pfsr_bit_t                      PFSRH2_b;
    stc_gpio_pcr_bit_t                       PCRH3_b;
    stc_gpio_pfsr_bit_t                      PFSRH3_b;
    stc_gpio_pcr_bit_t                       PCRH4_b;
    stc_gpio_pfsr_bit_t                      PFSRH4_b;
    stc_gpio_pcr_bit_t                       PCRH5_b;
    stc_gpio_pfsr_bit_t                      PFSRH5_b;
    stc_gpio_pcr_bit_t                       PCRH6_b;
    stc_gpio_pfsr_bit_t                      PFSRH6_b;
    stc_gpio_pcr_bit_t                       PCRH7_b;
    stc_gpio_pfsr_bit_t                      PFSRH7_b;
    stc_gpio_pcr_bit_t                       PCRH8_b;
    stc_gpio_pfsr_bit_t                      PFSRH8_b;
    stc_gpio_pcr_bit_t                       PCRH9_b;
    stc_gpio_pfsr_bit_t                      PFSRH9_b;
    stc_gpio_pcr_bit_t                       PCRH10_b;
    stc_gpio_pfsr_bit_t                      PFSRH10_b;
    stc_gpio_pcr_bit_t                       PCRH11_b;
    stc_gpio_pfsr_bit_t                      PFSRH11_b;
    stc_gpio_pcr_bit_t                       PCRH12_b;
    stc_gpio_pfsr_bit_t                      PFSRH12_b;
    stc_gpio_pcr_bit_t                       PCRH13_b;
    stc_gpio_pfsr_bit_t                      PFSRH13_b;
    stc_gpio_pcr_bit_t                       PCRH14_b;
    stc_gpio_pfsr_bit_t                      PFSRH14_b;
    stc_gpio_pcr_bit_t                       PCRH15_b;
    stc_gpio_pfsr_bit_t                      PFSRH15_b;
    stc_gpio_pcr_bit_t                       PCRI0_b;
    stc_gpio_pfsr_bit_t                      PFSRI0_b;
    stc_gpio_pcr_bit_t                       PCRI1_b;
    stc_gpio_pfsr_bit_t                      PFSRI1_b;
    stc_gpio_pcr_bit_t                       PCRI2_b;
    stc_gpio_pfsr_bit_t                      PFSRI2_b;
    stc_gpio_pcr_bit_t                       PCRI3_b;
    stc_gpio_pfsr_bit_t                      PFSRI3_b;
    stc_gpio_pcr_bit_t                       PCRI4_b;
    stc_gpio_pfsr_bit_t                      PFSRI4_b;
    stc_gpio_pcr_bit_t                       PCRI5_b;
    stc_gpio_pfsr_bit_t                      PFSRI5_b;
    stc_gpio_pcr_bit_t                       PCRI6_b;
    stc_gpio_pfsr_bit_t                      PFSRI6_b;
    stc_gpio_pcr_bit_t                       PCRI7_b;
    stc_gpio_pfsr_bit_t                      PFSRI7_b;
    stc_gpio_pcr_bit_t                       PCRI8_b;
    stc_gpio_pfsr_bit_t                      PFSRI8_b;
    stc_gpio_pcr_bit_t                       PCRI9_b;
    stc_gpio_pfsr_bit_t                      PFSRI9_b;
    stc_gpio_pcr_bit_t                       PCRI10_b;
    stc_gpio_pfsr_bit_t                      PFSRI10_b;
    stc_gpio_pcr_bit_t                       PCRI11_b;
    stc_gpio_pfsr_bit_t                      PFSRI11_b;
    stc_gpio_pcr_bit_t                       PCRI12_b;
    stc_gpio_pfsr_bit_t                      PFSRI12_b;
    stc_gpio_pcr_bit_t                       PCRI13_b;
    stc_gpio_pfsr_bit_t                      PFSRI13_b;
} bCM_GPIO_TypeDef;

typedef struct {
    stc_hash_cr_bit_t                        CR_b;
} bCM_HASH_TypeDef;

typedef struct {
    stc_hrpwm_cr_bit_t                       CR1_b;
    stc_hrpwm_cr_bit_t                       CR2_b;
    stc_hrpwm_cr_bit_t                       CR3_b;
    stc_hrpwm_cr_bit_t                       CR4_b;
    stc_hrpwm_cr_bit_t                       CR5_b;
    stc_hrpwm_cr_bit_t                       CR6_b;
    stc_hrpwm_cr_bit_t                       CR7_b;
    stc_hrpwm_cr_bit_t                       CR8_b;
    stc_hrpwm_cr_bit_t                       CR9_b;
    stc_hrpwm_cr_bit_t                       CR10_b;
    stc_hrpwm_cr_bit_t                       CR11_b;
    stc_hrpwm_cr_bit_t                       CR12_b;
    stc_hrpwm_cr_bit_t                       CR13_b;
    stc_hrpwm_cr_bit_t                       CR14_b;
    stc_hrpwm_cr_bit_t                       CR15_b;
    stc_hrpwm_cr_bit_t                       CR16_b;
    uint32_t                                 RESERVED0[128];
    stc_hrpwm_calcr_bit_t                    CALCR0_b;
    stc_hrpwm_calcr_bit_t                    CALCR1_b;
} bCM_HRPWM_TypeDef;

typedef struct {
    stc_i2c_cr1_bit_t                        CR1_b;
    stc_i2c_cr2_bit_t                        CR2_b;
    stc_i2c_cr3_bit_t                        CR3_b;
    stc_i2c_cr4_bit_t                        CR4_b;
    stc_i2c_slr0_bit_t                       SLR0_b;
    stc_i2c_slr1_bit_t                       SLR1_b;
    uint32_t                                 RESERVED0[32];
    stc_i2c_sr_bit_t                         SR_b;
    stc_i2c_clr_bit_t                        CLR_b;
    uint32_t                                 RESERVED1[96];
    stc_i2c_fltr_bit_t                       FLTR_b;
} bCM_I2C_TypeDef;

typedef struct {
    stc_i2s_ctrl_bit_t                       CTRL_b;
    stc_i2s_sr_bit_t                         SR_b;
    stc_i2s_er_bit_t                         ER_b;
    stc_i2s_cfgr_bit_t                       CFGR_b;
} bCM_I2S_TypeDef;

typedef struct {
    stc_icg_icg0_bit_t                       ICG0_b;
    stc_icg_icg1_bit_t                       ICG1_b;
} bCM_ICG_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_intc_nmienr_bit_t                    NMIENR_b;
    stc_intc_nmifr_bit_t                     NMIFR_b;
    stc_intc_nmicfr_bit_t                    NMICFR_b;
    stc_intc_eirqcr_bit_t                    EIRQCR0_b;
    stc_intc_eirqcr_bit_t                    EIRQCR1_b;
    stc_intc_eirqcr_bit_t                    EIRQCR2_b;
    stc_intc_eirqcr_bit_t                    EIRQCR3_b;
    stc_intc_eirqcr_bit_t                    EIRQCR4_b;
    stc_intc_eirqcr_bit_t                    EIRQCR5_b;
    stc_intc_eirqcr_bit_t                    EIRQCR6_b;
    stc_intc_eirqcr_bit_t                    EIRQCR7_b;
    stc_intc_eirqcr_bit_t                    EIRQCR8_b;
    stc_intc_eirqcr_bit_t                    EIRQCR9_b;
    stc_intc_eirqcr_bit_t                    EIRQCR10_b;
    stc_intc_eirqcr_bit_t                    EIRQCR11_b;
    stc_intc_eirqcr_bit_t                    EIRQCR12_b;
    stc_intc_eirqcr_bit_t                    EIRQCR13_b;
    stc_intc_eirqcr_bit_t                    EIRQCR14_b;
    stc_intc_eirqcr_bit_t                    EIRQCR15_b;
    stc_intc_wupen_bit_t                     WUPEN_b;
    stc_intc_eifr_bit_t                      EIFR_b;
    stc_intc_eifcr_bit_t                     EIFCR_b;
    uint32_t                                 RESERVED1[4096];
    stc_intc_vssel_bit_t                     VSSEL128_b;
    stc_intc_vssel_bit_t                     VSSEL129_b;
    stc_intc_vssel_bit_t                     VSSEL130_b;
    stc_intc_vssel_bit_t                     VSSEL131_b;
    stc_intc_vssel_bit_t                     VSSEL132_b;
    stc_intc_vssel_bit_t                     VSSEL133_b;
    stc_intc_vssel_bit_t                     VSSEL134_b;
    stc_intc_vssel_bit_t                     VSSEL135_b;
    stc_intc_vssel_bit_t                     VSSEL136_b;
    stc_intc_vssel_bit_t                     VSSEL137_b;
    stc_intc_vssel_bit_t                     VSSEL138_b;
    stc_intc_vssel_bit_t                     VSSEL139_b;
    stc_intc_vssel_bit_t                     VSSEL140_b;
    stc_intc_vssel_bit_t                     VSSEL141_b;
    stc_intc_vssel_bit_t                     VSSEL142_b;
    stc_intc_vssel_bit_t                     VSSEL143_b;
    stc_intc_swier_bit_t                     SWIER_b;
    stc_intc_evter_bit_t                     EVTER_b;
    stc_intc_ier_bit_t                       IER_b;
} bCM_INTC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_keyscan_ser_bit_t                    SER_b;
} bCM_KEYSCAN_TypeDef;

typedef struct {
    stc_mau_csr_bit_t                        CSR_b;
} bCM_MAU_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[512];
    stc_mpu_sr_bit_t                         SR_b;
    stc_mpu_eclr_bit_t                       ECLR_b;
    stc_mpu_wp_bit_t                         WP_b;
    stc_mpu_ippr_bit_t                       IPPR_b;
    stc_mpu_srge_bit_t                       S1RGE_b;
    stc_mpu_srgwp_bit_t                      S1RGWP_b;
    stc_mpu_srgrp_bit_t                      S1RGRP_b;
    stc_mpu_scr_bit_t                        S1CR_b;
    stc_mpu_srge_bit_t                       S2RGE_b;
    stc_mpu_srgwp_bit_t                      S2RGWP_b;
    stc_mpu_srgrp_bit_t                      S2RGRP_b;
    stc_mpu_scr_bit_t                        S2CR_b;
    stc_mpu_frge_bit_t                       FRGE_b;
    stc_mpu_frgwp_bit_t                      FRGWP_b;
    stc_mpu_frgrp_bit_t                      FRGRP_b;
    stc_mpu_fcr_bit_t                        FCR_b;
    stc_mpu_hrge_bit_t                       HRGE_b;
    stc_mpu_hrgwp_bit_t                      HRGWP_b;
    stc_mpu_hrgrp_bit_t                      HRGRP_b;
    stc_mpu_hcr_bit_t                        HCR_b;
    stc_mpu_erge_bit_t                       ERGE_b;
    stc_mpu_ergwp_bit_t                      ERGWP_b;
    stc_mpu_ergrp_bit_t                      ERGRP_b;
    stc_mpu_ecr_bit_t                        ECR_b;
} bCM_MPU_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[1904640];
    stc_ots_ctl_bit_t                        CTL_b;
} bCM_OTS_TypeDef;

typedef struct {
    stc_peric_usb_syctlreg_bit_t             USB_SYCTLREG_b;
    stc_peric_sdioc_syctlreg_bit_t           SDIOC_SYCTLREG_b;
    stc_peric_nfc_stcr_bit_t                 NFC_STCR_b;
    union {
        stc_peric_nfc_enar_bit_t             NFC_ENAR_b;
        stc_peric_smc_enar_bit_t             SMC_ENAR_b;
        stc_peric_dmc_enar_bit_t             DMC_ENAR_b;
    };
    uint32_t                                 RESERVED0[96];
    stc_peric_usart1_nfc_bit_t               USART1_NFC_b;
    uint32_t                                 RESERVED1[64];
    stc_peric_nfc_stsr_bit_t                 NFC_STSR_b;
} bCM_PERIC_TypeDef;

typedef struct {
    stc_pwc_fcg0_bit_t                       FCG0_b;
    stc_pwc_fcg1_bit_t                       FCG1_b;
    stc_pwc_fcg2_bit_t                       FCG2_b;
    stc_pwc_fcg3_bit_t                       FCG3_b;
    stc_pwc_fcg0pc_bit_t                     FCG0PC_b;
    uint32_t                                 RESERVED0[139616];
    stc_pwc_vbatcr_bit_t                     VBATCR_b;
    uint32_t                                 RESERVED1[184];
    stc_pwc_wktc2_bit_t                      WKTC2_b;
    uint32_t                                 RESERVED2[15672];
    stc_pwc_pwrc0_bit_t                      PWRC0_b;
    uint32_t                                 RESERVED3[24];
    stc_pwc_pwrc1_bit_t                      PWRC1_b;
    uint32_t                                 RESERVED4[88];
    stc_pwc_pwrc4_bit_t                      PWRC4_b;
    uint32_t                                 RESERVED5[24];
    stc_pwc_pvdcr0_bit_t                     PVDCR0_b;
    uint32_t                                 RESERVED6[24];
    stc_pwc_pvdcr1_bit_t                     PVDCR1_b;
    uint32_t                                 RESERVED7[24];
    stc_pwc_pvdfcr_bit_t                     PVDFCR_b;
    uint32_t                                 RESERVED8[88];
    stc_pwc_pdwke0_bit_t                     PDWKE0_b;
    uint32_t                                 RESERVED9[24];
    stc_pwc_pdwke1_bit_t                     PDWKE1_b;
    uint32_t                                 RESERVED10[24];
    stc_pwc_pdwke2_bit_t                     PDWKE2_b;
    uint32_t                                 RESERVED11[24];
    stc_pwc_pdwkes_bit_t                     PDWKES_b;
    uint32_t                                 RESERVED12[24];
    stc_pwc_pdwkf0_bit_t                     PDWKF0_b;
    uint32_t                                 RESERVED13[24];
    stc_pwc_pdwkf1_bit_t                     PDWKF1_b;
    uint32_t                                 RESERVED14[1304];
    stc_pwc_rampc0_bit_t                     RAMPC0_b;
    uint32_t                                 RESERVED15[32];
    stc_pwc_pramlpc_bit_t                    PRAMLPC_b;
    uint32_t                                 RESERVED16[32];
    stc_pwc_pvdicr_bit_t                     PVDICR_b;
    uint32_t                                 RESERVED17[24];
    stc_pwc_pvddsr_bit_t                     PVDDSR_b;
    uint32_t                                 RESERVED18[235704];
    stc_pwc_stpmcr_bit_t                     STPMCR_b;
    uint32_t                                 RESERVED19[8064];
    stc_pwc_fprc_bit_t                       FPRC_b;
} bCM_PWC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[1984];
    stc_rmu_prstcr0_bit_t                    PRSTCR0_b;
    uint32_t                                 RESERVED1[24];
    stc_rmu_rstf0_bit_t                      RSTF0_b;
} bCM_RMU_TypeDef;

typedef struct {
    stc_rtc_cr0_bit_t                        CR0_b;
    uint32_t                                 RESERVED0[24];
    stc_rtc_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED1[24];
    stc_rtc_cr2_bit_t                        CR2_b;
    uint32_t                                 RESERVED2[24];
    stc_rtc_cr3_bit_t                        CR3_b;
    uint32_t                                 RESERVED3[344];
    stc_rtc_errcrh_bit_t                     ERRCRH_b;
    uint32_t                                 RESERVED4[56];
    stc_rtc_tpcr0_bit_t                      TPCR0_b;
    uint32_t                                 RESERVED5[24];
    stc_rtc_tpcr1_bit_t                      TPCR1_b;
    uint32_t                                 RESERVED6[24];
    stc_rtc_tpsr_bit_t                       TPSR_b;
} bCM_RTC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[96];
    stc_sdioc_transmode_bit_t                TRANSMODE_b;
    stc_sdioc_cmd_bit_t                      CMD_b;
    uint32_t                                 RESERVED1[160];
    stc_sdioc_pstat_bit_t                    PSTAT_b;
    stc_sdioc_hostcon_bit_t                  HOSTCON_b;
    stc_sdioc_pwrcon_bit_t                   PWRCON_b;
    stc_sdioc_blkgpcon_bit_t                 BLKGPCON_b;
    uint32_t                                 RESERVED2[8];
    stc_sdioc_clkcon_bit_t                   CLKCON_b;
    uint32_t                                 RESERVED3[8];
    stc_sdioc_sftrst_bit_t                   SFTRST_b;
    stc_sdioc_norintst_bit_t                 NORINTST_b;
    stc_sdioc_errintst_bit_t                 ERRINTST_b;
    stc_sdioc_norintsten_bit_t               NORINTSTEN_b;
    stc_sdioc_errintsten_bit_t               ERRINTSTEN_b;
    stc_sdioc_norintsgen_bit_t               NORINTSGEN_b;
    stc_sdioc_errintsgen_bit_t               ERRINTSGEN_b;
    stc_sdioc_atcerrst_bit_t                 ATCERRST_b;
    uint32_t                                 RESERVED4[144];
    stc_sdioc_fea_bit_t                      FEA_b;
    stc_sdioc_fee_bit_t                      FEE_b;
} bCM_SDIOC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_spi_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED1[32];
    stc_spi_cfg1_bit_t                       CFG1_b;
    uint32_t                                 RESERVED2[32];
    stc_spi_sr_bit_t                         SR_b;
    stc_spi_cfg2_bit_t                       CFG2_b;
} bCM_SPI_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_sramc_wtpr_bit_t                     WTPR_b;
    stc_sramc_ckcr_bit_t                     CKCR_b;
    stc_sramc_ckpr_bit_t                     CKPR_b;
    stc_sramc_cksr_bit_t                     CKSR_b;
} bCM_SRAMC_TypeDef;

typedef struct {
    stc_swdt_cr_bit_t                        CR_b;
    stc_swdt_sr_bit_t                        SR_b;
} bCM_SWDT_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[128];
    stc_tmr0_bconr_bit_t                     BCONR_b;
    stc_tmr0_stflr_bit_t                     STFLR_b;
} bCM_TMR0_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[128];
    stc_tmr2_bconr_bit_t                     BCONR_b;
    stc_tmr2_iconr_bit_t                     ICONR_b;
    stc_tmr2_pconr_bit_t                     PCONR_b;
    stc_tmr2_hconr_bit_t                     HCONR_b;
    stc_tmr2_stflr_bit_t                     STFLR_b;
} bCM_TMR2_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[192];
    stc_tmr4_ocsr_bit_t                      OCSRU_b;
    stc_tmr4_ocer_bit_t                      OCERU_b;
    stc_tmr4_ocsr_bit_t                      OCSRV_b;
    stc_tmr4_ocer_bit_t                      OCERV_b;
    stc_tmr4_ocsr_bit_t                      OCSRW_b;
    stc_tmr4_ocer_bit_t                      OCERW_b;
    stc_tmr4_ocmrh_bit_t                     OCMRHUH_b;
    uint32_t                                 RESERVED1[16];
    stc_tmr4_ocmrl_bit_t                     OCMRLUL_b;
    stc_tmr4_ocmrh_bit_t                     OCMRHVH_b;
    uint32_t                                 RESERVED2[16];
    stc_tmr4_ocmrl_bit_t                     OCMRLVL_b;
    stc_tmr4_ocmrh_bit_t                     OCMRHWH_b;
    uint32_t                                 RESERVED3[16];
    stc_tmr4_ocmrl_bit_t                     OCMRLWL_b;
    uint32_t                                 RESERVED4[96];
    stc_tmr4_ccsr_bit_t                      CCSR_b;
    uint32_t                                 RESERVED5[720];
    stc_tmr4_rcsr_bit_t                      RCSR_b;
    uint32_t                                 RESERVED6[272];
    stc_tmr4_scsr_bit_t                      SCSRUH_b;
    stc_tmr4_scmr_bit_t                      SCMRUH_b;
    stc_tmr4_scsr_bit_t                      SCSRUL_b;
    stc_tmr4_scmr_bit_t                      SCMRUL_b;
    stc_tmr4_scsr_bit_t                      SCSRVH_b;
    stc_tmr4_scmr_bit_t                      SCMRVH_b;
    stc_tmr4_scsr_bit_t                      SCSRVL_b;
    stc_tmr4_scmr_bit_t                      SCMRVL_b;
    stc_tmr4_scsr_bit_t                      SCSRWH_b;
    stc_tmr4_scmr_bit_t                      SCMRWH_b;
    stc_tmr4_scsr_bit_t                      SCSRWL_b;
    stc_tmr4_scmr_bit_t                      SCMRWL_b;
    stc_tmr4_pscr_bit_t                      PSCR_b;
    stc_tmr4_scer_bit_t                      SCER_b;
} bCM_TMR4_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[2560];
    stc_tmr6_gconr_bit_t                     GCONR_b;
    stc_tmr6_iconr_bit_t                     ICONR_b;
    stc_tmr6_bconr_bit_t                     BCONR_b;
    stc_tmr6_dconr_bit_t                     DCONR_b;
    uint32_t                                 RESERVED1[32];
    stc_tmr6_pcnar_bit_t                     PCNAR_b;
    stc_tmr6_pcnbr_bit_t                     PCNBR_b;
    stc_tmr6_fcngr_bit_t                     FCNGR_b;
    stc_tmr6_vperr_bit_t                     VPERR_b;
    stc_tmr6_stflr_bit_t                     STFLR_b;
    uint32_t                                 RESERVED2[192];
    stc_tmr6_hstar_bit_t                     HSTAR_b;
    stc_tmr6_hstpr_bit_t                     HSTPR_b;
    stc_tmr6_hclrr_bit_t                     HCLRR_b;
    stc_tmr6_hupdr_bit_t                     HUPDR_b;
    stc_tmr6_hcpar_bit_t                     HCPAR_b;
    stc_tmr6_hcpbr_bit_t                     HCPBR_b;
    stc_tmr6_hcupr_bit_t                     HCUPR_b;
    stc_tmr6_hcdor_bit_t                     HCDOR_b;
} bCM_TMR6_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[8032];
    stc_tmr6cr_fcntr_bit_t                   FCNTR_b;
    stc_tmr6cr_sstar_bit_t                   SSTAR_b;
    stc_tmr6cr_sstpr_bit_t                   SSTPR_b;
    stc_tmr6cr_sclrr_bit_t                   SCLRR_b;
    stc_tmr6cr_supdr_bit_t                   SUPDR_b;
} bCM_TMR6CR_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[1024];
    stc_tmra_bcstrl_bit_t                    BCSTRL_b;
    stc_tmra_bcstrh_bit_t                    BCSTRH_b;
    uint32_t                                 RESERVED1[16];
    stc_tmra_hconr_bit_t                     HCONR_b;
    uint32_t                                 RESERVED2[16];
    stc_tmra_hcupr_bit_t                     HCUPR_b;
    uint32_t                                 RESERVED3[16];
    stc_tmra_hcdor_bit_t                     HCDOR_b;
    uint32_t                                 RESERVED4[16];
    stc_tmra_iconr_bit_t                     ICONR_b;
    uint32_t                                 RESERVED5[16];
    stc_tmra_econr_bit_t                     ECONR_b;
    uint32_t                                 RESERVED6[16];
    stc_tmra_fconr_bit_t                     FCONR_b;
    uint32_t                                 RESERVED7[16];
    stc_tmra_stflr_bit_t                     STFLR_b;
    uint32_t                                 RESERVED8[272];
    stc_tmra_bconr_bit_t                     BCONR1_b;
    uint32_t                                 RESERVED9[48];
    stc_tmra_bconr_bit_t                     BCONR2_b;
    uint32_t                                 RESERVED10[432];
    stc_tmra_cconr_bit_t                     CCONR1_b;
    uint32_t                                 RESERVED11[16];
    stc_tmra_cconr_bit_t                     CCONR2_b;
    uint32_t                                 RESERVED12[16];
    stc_tmra_cconr_bit_t                     CCONR3_b;
    uint32_t                                 RESERVED13[16];
    stc_tmra_cconr_bit_t                     CCONR4_b;
    uint32_t                                 RESERVED14[400];
    stc_tmra_pconr_bit_t                     PCONR1_b;
    uint32_t                                 RESERVED15[16];
    stc_tmra_pconr_bit_t                     PCONR2_b;
    uint32_t                                 RESERVED16[16];
    stc_tmra_pconr_bit_t                     PCONR3_b;
    uint32_t                                 RESERVED17[16];
    stc_tmra_pconr_bit_t                     PCONR4_b;
} bCM_TMRA_TypeDef;

typedef struct {
    stc_trng_cr_bit_t                        CR_b;
    stc_trng_mr_bit_t                        MR_b;
} bCM_TRNG_TypeDef;

typedef struct {
    stc_usart_sr_bit_t                       SR_b;
    stc_usart_tdr_bit_t                      TDR_b;
    uint32_t                                 RESERVED0[48];
    stc_usart_cr1_bit_t                      CR1_b;
    stc_usart_cr2_bit_t                      CR2_b;
    stc_usart_cr3_bit_t                      CR3_b;
} bCM_USART_TypeDef;

typedef struct {
    stc_usbfs_gvbuscfg_bit_t                 GVBUSCFG_b;
    uint32_t                                 RESERVED0[32];
    stc_usbfs_gahbcfg_bit_t                  GAHBCFG_b;
    stc_usbfs_gusbcfg_bit_t                  GUSBCFG_b;
    stc_usbfs_grstctl_bit_t                  GRSTCTL_b;
    stc_usbfs_gintsts_bit_t                  GINTSTS_b;
    stc_usbfs_gintmsk_bit_t                  GINTMSK_b;
    uint32_t                                 RESERVED1[448];
    stc_usbfs_glpmcfg_bit_t                  GLPMCFG_b;
    uint32_t                                 RESERVED2[7488];
    stc_usbfs_hcfg_bit_t                     HCFG_b;
    uint32_t                                 RESERVED3[480];
    stc_usbfs_hprt_bit_t                     HPRT_b;
    uint32_t                                 RESERVED4[1504];
    stc_usbfs_hcchar_bit_t                   HCCHAR0_b;
    uint32_t                                 RESERVED5[32];
    stc_usbfs_hcint_bit_t                    HCINT0_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK0_b;
    uint32_t                                 RESERVED6[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR1_b;
    uint32_t                                 RESERVED7[32];
    stc_usbfs_hcint_bit_t                    HCINT1_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK1_b;
    uint32_t                                 RESERVED8[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR2_b;
    uint32_t                                 RESERVED9[32];
    stc_usbfs_hcint_bit_t                    HCINT2_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK2_b;
    uint32_t                                 RESERVED10[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR3_b;
    uint32_t                                 RESERVED11[32];
    stc_usbfs_hcint_bit_t                    HCINT3_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK3_b;
    uint32_t                                 RESERVED12[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR4_b;
    uint32_t                                 RESERVED13[32];
    stc_usbfs_hcint_bit_t                    HCINT4_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK4_b;
    uint32_t                                 RESERVED14[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR5_b;
    uint32_t                                 RESERVED15[32];
    stc_usbfs_hcint_bit_t                    HCINT5_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK5_b;
    uint32_t                                 RESERVED16[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR6_b;
    uint32_t                                 RESERVED17[32];
    stc_usbfs_hcint_bit_t                    HCINT6_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK6_b;
    uint32_t                                 RESERVED18[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR7_b;
    uint32_t                                 RESERVED19[32];
    stc_usbfs_hcint_bit_t                    HCINT7_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK7_b;
    uint32_t                                 RESERVED20[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR8_b;
    uint32_t                                 RESERVED21[32];
    stc_usbfs_hcint_bit_t                    HCINT8_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK8_b;
    uint32_t                                 RESERVED22[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR9_b;
    uint32_t                                 RESERVED23[32];
    stc_usbfs_hcint_bit_t                    HCINT9_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK9_b;
    uint32_t                                 RESERVED24[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR10_b;
    uint32_t                                 RESERVED25[32];
    stc_usbfs_hcint_bit_t                    HCINT10_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK10_b;
    uint32_t                                 RESERVED26[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR11_b;
    uint32_t                                 RESERVED27[32];
    stc_usbfs_hcint_bit_t                    HCINT11_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK11_b;
    uint32_t                                 RESERVED28[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR12_b;
    uint32_t                                 RESERVED29[32];
    stc_usbfs_hcint_bit_t                    HCINT12_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK12_b;
    uint32_t                                 RESERVED30[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR13_b;
    uint32_t                                 RESERVED31[32];
    stc_usbfs_hcint_bit_t                    HCINT13_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK13_b;
    uint32_t                                 RESERVED32[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR14_b;
    uint32_t                                 RESERVED33[32];
    stc_usbfs_hcint_bit_t                    HCINT14_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK14_b;
    uint32_t                                 RESERVED34[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR15_b;
    uint32_t                                 RESERVED35[32];
    stc_usbfs_hcint_bit_t                    HCINT15_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK15_b;
    uint32_t                                 RESERVED36[2176];
    stc_usbfs_dcfg_bit_t                     DCFG_b;
    stc_usbfs_dctl_bit_t                     DCTL_b;
    stc_usbfs_dsts_bit_t                     DSTS_b;
    uint32_t                                 RESERVED37[32];
    stc_usbfs_diepmsk_bit_t                  DIEPMSK_b;
    stc_usbfs_doepmsk_bit_t                  DOEPMSK_b;
    uint32_t                                 RESERVED38[1856];
    stc_usbfs_diepctl0_bit_t                 DIEPCTL0_b;
    uint32_t                                 RESERVED39[32];
    stc_usbfs_diepint_bit_t                  DIEPINT0_b;
    uint32_t                                 RESERVED40[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL1_b;
    uint32_t                                 RESERVED41[32];
    stc_usbfs_diepint_bit_t                  DIEPINT1_b;
    uint32_t                                 RESERVED42[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL2_b;
    uint32_t                                 RESERVED43[32];
    stc_usbfs_diepint_bit_t                  DIEPINT2_b;
    uint32_t                                 RESERVED44[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL3_b;
    uint32_t                                 RESERVED45[32];
    stc_usbfs_diepint_bit_t                  DIEPINT3_b;
    uint32_t                                 RESERVED46[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL4_b;
    uint32_t                                 RESERVED47[32];
    stc_usbfs_diepint_bit_t                  DIEPINT4_b;
    uint32_t                                 RESERVED48[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL5_b;
    uint32_t                                 RESERVED49[32];
    stc_usbfs_diepint_bit_t                  DIEPINT5_b;
    uint32_t                                 RESERVED50[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL6_b;
    uint32_t                                 RESERVED51[32];
    stc_usbfs_diepint_bit_t                  DIEPINT6_b;
    uint32_t                                 RESERVED52[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL7_b;
    uint32_t                                 RESERVED53[32];
    stc_usbfs_diepint_bit_t                  DIEPINT7_b;
    uint32_t                                 RESERVED54[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL8_b;
    uint32_t                                 RESERVED55[32];
    stc_usbfs_diepint_bit_t                  DIEPINT8_b;
    uint32_t                                 RESERVED56[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL9_b;
    uint32_t                                 RESERVED57[32];
    stc_usbfs_diepint_bit_t                  DIEPINT9_b;
    uint32_t                                 RESERVED58[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL10_b;
    uint32_t                                 RESERVED59[32];
    stc_usbfs_diepint_bit_t                  DIEPINT10_b;
    uint32_t                                 RESERVED60[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL11_b;
    uint32_t                                 RESERVED61[32];
    stc_usbfs_diepint_bit_t                  DIEPINT11_b;
    uint32_t                                 RESERVED62[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL12_b;
    uint32_t                                 RESERVED63[32];
    stc_usbfs_diepint_bit_t                  DIEPINT12_b;
    uint32_t                                 RESERVED64[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL13_b;
    uint32_t                                 RESERVED65[32];
    stc_usbfs_diepint_bit_t                  DIEPINT13_b;
    uint32_t                                 RESERVED66[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL14_b;
    uint32_t                                 RESERVED67[32];
    stc_usbfs_diepint_bit_t                  DIEPINT14_b;
    uint32_t                                 RESERVED68[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL15_b;
    uint32_t                                 RESERVED69[32];
    stc_usbfs_diepint_bit_t                  DIEPINT15_b;
    uint32_t                                 RESERVED70[160];
    stc_usbfs_doepctl0_bit_t                 DOEPCTL0_b;
    uint32_t                                 RESERVED71[32];
    stc_usbfs_doepint_bit_t                  DOEPINT0_b;
    uint32_t                                 RESERVED72[32];
    stc_usbfs_doeptsiz0_bit_t                DOEPTSIZ0_b;
    uint32_t                                 RESERVED73[96];
    stc_usbfs_doepctl_bit_t                  DOEPCTL1_b;
    uint32_t                                 RESERVED74[32];
    stc_usbfs_doepint_bit_t                  DOEPINT1_b;
    uint32_t                                 RESERVED75[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL2_b;
    uint32_t                                 RESERVED76[32];
    stc_usbfs_doepint_bit_t                  DOEPINT2_b;
    uint32_t                                 RESERVED77[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL3_b;
    uint32_t                                 RESERVED78[32];
    stc_usbfs_doepint_bit_t                  DOEPINT3_b;
    uint32_t                                 RESERVED79[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL4_b;
    uint32_t                                 RESERVED80[32];
    stc_usbfs_doepint_bit_t                  DOEPINT4_b;
    uint32_t                                 RESERVED81[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL5_b;
    uint32_t                                 RESERVED82[32];
    stc_usbfs_doepint_bit_t                  DOEPINT5_b;
    uint32_t                                 RESERVED83[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL6_b;
    uint32_t                                 RESERVED84[32];
    stc_usbfs_doepint_bit_t                  DOEPINT6_b;
    uint32_t                                 RESERVED85[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL7_b;
    uint32_t                                 RESERVED86[32];
    stc_usbfs_doepint_bit_t                  DOEPINT7_b;
    uint32_t                                 RESERVED87[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL8_b;
    uint32_t                                 RESERVED88[32];
    stc_usbfs_doepint_bit_t                  DOEPINT8_b;
    uint32_t                                 RESERVED89[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL9_b;
    uint32_t                                 RESERVED90[32];
    stc_usbfs_doepint_bit_t                  DOEPINT9_b;
    uint32_t                                 RESERVED91[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL10_b;
    uint32_t                                 RESERVED92[32];
    stc_usbfs_doepint_bit_t                  DOEPINT10_b;
    uint32_t                                 RESERVED93[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL11_b;
    uint32_t                                 RESERVED94[32];
    stc_usbfs_doepint_bit_t                  DOEPINT11_b;
    uint32_t                                 RESERVED95[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL12_b;
    uint32_t                                 RESERVED96[32];
    stc_usbfs_doepint_bit_t                  DOEPINT12_b;
    uint32_t                                 RESERVED97[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL13_b;
    uint32_t                                 RESERVED98[32];
    stc_usbfs_doepint_bit_t                  DOEPINT13_b;
    uint32_t                                 RESERVED99[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL14_b;
    uint32_t                                 RESERVED100[32];
    stc_usbfs_doepint_bit_t                  DOEPINT14_b;
    uint32_t                                 RESERVED101[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL15_b;
    uint32_t                                 RESERVED102[32];
    stc_usbfs_doepint_bit_t                  DOEPINT15_b;
    uint32_t                                 RESERVED103[2208];
    stc_usbfs_gcctl_bit_t                    GCCTL_b;
} bCM_USBFS_TypeDef;

typedef struct {
    stc_usbhs_gvbuscfg_bit_t                 GVBUSCFG_b;
    uint32_t                                 RESERVED0[32];
    stc_usbhs_gahbcfg_bit_t                  GAHBCFG_b;
    stc_usbhs_gusbcfg_bit_t                  GUSBCFG_b;
    stc_usbhs_grstctl_bit_t                  GRSTCTL_b;
    stc_usbhs_gintsts_bit_t                  GINTSTS_b;
    stc_usbhs_gintmsk_bit_t                  GINTMSK_b;
    uint32_t                                 RESERVED1[448];
    stc_usbhs_glpmcfg_bit_t                  GLPMCFG_b;
    uint32_t                                 RESERVED2[7488];
    stc_usbhs_hcfg_bit_t                     HCFG_b;
    uint32_t                                 RESERVED3[480];
    stc_usbhs_hprt_bit_t                     HPRT_b;
    uint32_t                                 RESERVED4[1504];
    stc_usbhs_hcchar_bit_t                   HCCHAR0_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT0_b;
    stc_usbhs_hcint_bit_t                    HCINT0_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK0_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ0_b;
    uint32_t                                 RESERVED5[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR1_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT1_b;
    stc_usbhs_hcint_bit_t                    HCINT1_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK1_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ1_b;
    uint32_t                                 RESERVED6[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR2_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT2_b;
    stc_usbhs_hcint_bit_t                    HCINT2_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK2_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ2_b;
    uint32_t                                 RESERVED7[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR3_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT3_b;
    stc_usbhs_hcint_bit_t                    HCINT3_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK3_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ3_b;
    uint32_t                                 RESERVED8[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR4_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT4_b;
    stc_usbhs_hcint_bit_t                    HCINT4_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK4_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ4_b;
    uint32_t                                 RESERVED9[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR5_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT5_b;
    stc_usbhs_hcint_bit_t                    HCINT5_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK5_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ5_b;
    uint32_t                                 RESERVED10[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR6_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT6_b;
    stc_usbhs_hcint_bit_t                    HCINT6_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK6_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ6_b;
    uint32_t                                 RESERVED11[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR7_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT7_b;
    stc_usbhs_hcint_bit_t                    HCINT7_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK7_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ7_b;
    uint32_t                                 RESERVED12[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR8_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT8_b;
    stc_usbhs_hcint_bit_t                    HCINT8_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK8_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ8_b;
    uint32_t                                 RESERVED13[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR9_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT9_b;
    stc_usbhs_hcint_bit_t                    HCINT9_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK9_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ9_b;
    uint32_t                                 RESERVED14[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR10_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT10_b;
    stc_usbhs_hcint_bit_t                    HCINT10_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK10_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ10_b;
    uint32_t                                 RESERVED15[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR11_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT11_b;
    stc_usbhs_hcint_bit_t                    HCINT11_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK11_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ11_b;
    uint32_t                                 RESERVED16[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR12_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT12_b;
    stc_usbhs_hcint_bit_t                    HCINT12_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK12_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ12_b;
    uint32_t                                 RESERVED17[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR13_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT13_b;
    stc_usbhs_hcint_bit_t                    HCINT13_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK13_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ13_b;
    uint32_t                                 RESERVED18[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR14_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT14_b;
    stc_usbhs_hcint_bit_t                    HCINT14_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK14_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ14_b;
    uint32_t                                 RESERVED19[96];
    stc_usbhs_hcchar_bit_t                   HCCHAR15_b;
    stc_usbhs_hcsplt_bit_t                   HCSPLT15_b;
    stc_usbhs_hcint_bit_t                    HCINT15_b;
    stc_usbhs_hcintmsk_bit_t                 HCINTMSK15_b;
    stc_usbhs_hctsiz_bit_t                   HCTSIZ15_b;
    uint32_t                                 RESERVED20[2144];
    stc_usbhs_dcfg_bit_t                     DCFG_b;
    stc_usbhs_dctl_bit_t                     DCTL_b;
    stc_usbhs_dsts_bit_t                     DSTS_b;
    uint32_t                                 RESERVED21[32];
    stc_usbhs_diepmsk_bit_t                  DIEPMSK_b;
    stc_usbhs_doepmsk_bit_t                  DOEPMSK_b;
    uint32_t                                 RESERVED22[192];
    stc_usbhs_dthrctl_bit_t                  DTHRCTL_b;
    uint32_t                                 RESERVED23[32];
    stc_usbhs_deachint_bit_t                 DEACHINT_b;
    stc_usbhs_deachintmsk_bit_t              DEACHINTMSK_b;
    uint32_t                                 RESERVED24[32];
    stc_usbhs_diepeachmsk1_bit_t             DIEPEACHMSK1_b;
    uint32_t                                 RESERVED25[480];
    stc_usbhs_doepeachmsk1_bit_t             DOEPEACHMSK1_b;
    uint32_t                                 RESERVED26[960];
    stc_usbhs_diepctl0_bit_t                 DIEPCTL0_b;
    uint32_t                                 RESERVED27[32];
    stc_usbhs_diepint_bit_t                  DIEPINT0_b;
    uint32_t                                 RESERVED28[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL1_b;
    uint32_t                                 RESERVED29[32];
    stc_usbhs_diepint_bit_t                  DIEPINT1_b;
    uint32_t                                 RESERVED30[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL2_b;
    uint32_t                                 RESERVED31[32];
    stc_usbhs_diepint_bit_t                  DIEPINT2_b;
    uint32_t                                 RESERVED32[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL3_b;
    uint32_t                                 RESERVED33[32];
    stc_usbhs_diepint_bit_t                  DIEPINT3_b;
    uint32_t                                 RESERVED34[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL4_b;
    uint32_t                                 RESERVED35[32];
    stc_usbhs_diepint_bit_t                  DIEPINT4_b;
    uint32_t                                 RESERVED36[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL5_b;
    uint32_t                                 RESERVED37[32];
    stc_usbhs_diepint_bit_t                  DIEPINT5_b;
    uint32_t                                 RESERVED38[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL6_b;
    uint32_t                                 RESERVED39[32];
    stc_usbhs_diepint_bit_t                  DIEPINT6_b;
    uint32_t                                 RESERVED40[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL7_b;
    uint32_t                                 RESERVED41[32];
    stc_usbhs_diepint_bit_t                  DIEPINT7_b;
    uint32_t                                 RESERVED42[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL8_b;
    uint32_t                                 RESERVED43[32];
    stc_usbhs_diepint_bit_t                  DIEPINT8_b;
    uint32_t                                 RESERVED44[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL9_b;
    uint32_t                                 RESERVED45[32];
    stc_usbhs_diepint_bit_t                  DIEPINT9_b;
    uint32_t                                 RESERVED46[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL10_b;
    uint32_t                                 RESERVED47[32];
    stc_usbhs_diepint_bit_t                  DIEPINT10_b;
    uint32_t                                 RESERVED48[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL11_b;
    uint32_t                                 RESERVED49[32];
    stc_usbhs_diepint_bit_t                  DIEPINT11_b;
    uint32_t                                 RESERVED50[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL12_b;
    uint32_t                                 RESERVED51[32];
    stc_usbhs_diepint_bit_t                  DIEPINT12_b;
    uint32_t                                 RESERVED52[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL13_b;
    uint32_t                                 RESERVED53[32];
    stc_usbhs_diepint_bit_t                  DIEPINT13_b;
    uint32_t                                 RESERVED54[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL14_b;
    uint32_t                                 RESERVED55[32];
    stc_usbhs_diepint_bit_t                  DIEPINT14_b;
    uint32_t                                 RESERVED56[160];
    stc_usbhs_diepctl_bit_t                  DIEPCTL15_b;
    uint32_t                                 RESERVED57[32];
    stc_usbhs_diepint_bit_t                  DIEPINT15_b;
    uint32_t                                 RESERVED58[160];
    stc_usbhs_doepctl0_bit_t                 DOEPCTL0_b;
    uint32_t                                 RESERVED59[32];
    stc_usbhs_doepint_bit_t                  DOEPINT0_b;
    uint32_t                                 RESERVED60[32];
    stc_usbhs_doeptsiz0_bit_t                DOEPTSIZ0_b;
    uint32_t                                 RESERVED61[96];
    stc_usbhs_doepctl_bit_t                  DOEPCTL1_b;
    uint32_t                                 RESERVED62[32];
    stc_usbhs_doepint_bit_t                  DOEPINT1_b;
    uint32_t                                 RESERVED63[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL2_b;
    uint32_t                                 RESERVED64[32];
    stc_usbhs_doepint_bit_t                  DOEPINT2_b;
    uint32_t                                 RESERVED65[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL3_b;
    uint32_t                                 RESERVED66[32];
    stc_usbhs_doepint_bit_t                  DOEPINT3_b;
    uint32_t                                 RESERVED67[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL4_b;
    uint32_t                                 RESERVED68[32];
    stc_usbhs_doepint_bit_t                  DOEPINT4_b;
    uint32_t                                 RESERVED69[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL5_b;
    uint32_t                                 RESERVED70[32];
    stc_usbhs_doepint_bit_t                  DOEPINT5_b;
    uint32_t                                 RESERVED71[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL6_b;
    uint32_t                                 RESERVED72[32];
    stc_usbhs_doepint_bit_t                  DOEPINT6_b;
    uint32_t                                 RESERVED73[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL7_b;
    uint32_t                                 RESERVED74[32];
    stc_usbhs_doepint_bit_t                  DOEPINT7_b;
    uint32_t                                 RESERVED75[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL8_b;
    uint32_t                                 RESERVED76[32];
    stc_usbhs_doepint_bit_t                  DOEPINT8_b;
    uint32_t                                 RESERVED77[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL9_b;
    uint32_t                                 RESERVED78[32];
    stc_usbhs_doepint_bit_t                  DOEPINT9_b;
    uint32_t                                 RESERVED79[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL10_b;
    uint32_t                                 RESERVED80[32];
    stc_usbhs_doepint_bit_t                  DOEPINT10_b;
    uint32_t                                 RESERVED81[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL11_b;
    uint32_t                                 RESERVED82[32];
    stc_usbhs_doepint_bit_t                  DOEPINT11_b;
    uint32_t                                 RESERVED83[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL12_b;
    uint32_t                                 RESERVED84[32];
    stc_usbhs_doepint_bit_t                  DOEPINT12_b;
    uint32_t                                 RESERVED85[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL13_b;
    uint32_t                                 RESERVED86[32];
    stc_usbhs_doepint_bit_t                  DOEPINT13_b;
    uint32_t                                 RESERVED87[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL14_b;
    uint32_t                                 RESERVED88[32];
    stc_usbhs_doepint_bit_t                  DOEPINT14_b;
    uint32_t                                 RESERVED89[160];
    stc_usbhs_doepctl_bit_t                  DOEPCTL15_b;
    uint32_t                                 RESERVED90[32];
    stc_usbhs_doepint_bit_t                  DOEPINT15_b;
    uint32_t                                 RESERVED91[2208];
    stc_usbhs_gcctl_bit_t                    GCCTL_b;
} bCM_USBHS_TypeDef;

typedef struct {
    stc_wdt_cr_bit_t                         CR_b;
    stc_wdt_sr_bit_t                         SR_b;
} bCM_WDT_TypeDef;


/******************************************************************************/
/*      Device Specific Peripheral bit_band declaration & memory map          */
/******************************************************************************/
#define bCM_ADC1                             ((bCM_ADC_TypeDef *)0x42800000UL)
#define bCM_ADC2                             ((bCM_ADC_TypeDef *)0x42808000UL)
#define bCM_ADC3                             ((bCM_ADC_TypeDef *)0x42810000UL)
#define bCM_AES                              ((bCM_AES_TypeDef *)0x42100000UL)
#define bCM_AOS                              ((bCM_AOS_TypeDef *)0x42210000UL)
#define bCM_CAN1                             ((bCM_CAN_TypeDef *)0x42120000UL)
#define bCM_CAN2                             ((bCM_CAN_TypeDef *)0x42F00000UL)
#define bCM_CMP1                             ((bCM_CMP_TypeDef *)0x42940000UL)
#define bCM_CMP2                             ((bCM_CMP_TypeDef *)0x42940200UL)
#define bCM_CMP3                             ((bCM_CMP_TypeDef *)0x42948000UL)
#define bCM_CMP4                             ((bCM_CMP_TypeDef *)0x42948200UL)
#define bCM_CMU                              ((bCM_CMU_TypeDef *)0x42988000UL)
#define bCM_CRC                              ((bCM_CRC_TypeDef *)0x42118000UL)
#define bCM_CTC                              ((bCM_CTC_TypeDef *)0x42938000UL)
#define bCM_DAC1                             ((bCM_DAC_TypeDef *)0x42820000UL)
#define bCM_DAC2                             ((bCM_DAC_TypeDef *)0x42828000UL)
#define bCM_DCU1                             ((bCM_DCU_TypeDef *)0x42AC0000UL)
#define bCM_DCU2                             ((bCM_DCU_TypeDef *)0x42AC8000UL)
#define bCM_DCU3                             ((bCM_DCU_TypeDef *)0x42AD0000UL)
#define bCM_DCU4                             ((bCM_DCU_TypeDef *)0x42AD8000UL)
#define bCM_DCU5                             ((bCM_DCU_TypeDef *)0x42AE0000UL)
#define bCM_DCU6                             ((bCM_DCU_TypeDef *)0x42AE8000UL)
#define bCM_DCU7                             ((bCM_DCU_TypeDef *)0x42AF0000UL)
#define bCM_DCU8                             ((bCM_DCU_TypeDef *)0x42AF8000UL)
#define bCM_DMA1                             ((bCM_DMA_TypeDef *)0x42A60000UL)
#define bCM_DMA2                             ((bCM_DMA_TypeDef *)0x42A68000UL)
#define bCM_DVP                              ((bCM_DVP_TypeDef *)0x42AB0000UL)
#define bCM_EFM                              ((bCM_EFM_TypeDef *)0x42208000UL)
#define bCM_EMB0                             ((bCM_EMB_TypeDef *)0x422F8000UL)
#define bCM_EMB1                             ((bCM_EMB_TypeDef *)0x422F8400UL)
#define bCM_EMB2                             ((bCM_EMB_TypeDef *)0x422F8800UL)
#define bCM_EMB3                             ((bCM_EMB_TypeDef *)0x422F8C00UL)
#define bCM_EMB4                             ((bCM_EMB_TypeDef *)0x422F9000UL)
#define bCM_EMB5                             ((bCM_EMB_TypeDef *)0x422F9400UL)
#define bCM_EMB6                             ((bCM_EMB_TypeDef *)0x422F9800UL)
#define bCM_ETH                              ((bCM_ETH_TypeDef *)0x42A00000UL)
#define bCM_FCM                              ((bCM_FCM_TypeDef *)0x42908000UL)
#define bCM_FMAC1                            ((bCM_FMAC_TypeDef *)0x42B00000UL)
#define bCM_FMAC2                            ((bCM_FMAC_TypeDef *)0x42B08000UL)
#define bCM_FMAC3                            ((bCM_FMAC_TypeDef *)0x42B10000UL)
#define bCM_FMAC4                            ((bCM_FMAC_TypeDef *)0x42B18000UL)
#define bCM_GPIO                             ((bCM_GPIO_TypeDef *)0x42A70000UL)
#define bCM_HASH                             ((bCM_HASH_TypeDef *)0x42108000UL)
#define bCM_HRPWM                            ((bCM_HRPWM_TypeDef *)0x42780000UL)
#define bCM_I2C1                             ((bCM_I2C_TypeDef *)0x429C0000UL)
#define bCM_I2C2                             ((bCM_I2C_TypeDef *)0x429C8000UL)
#define bCM_I2C3                             ((bCM_I2C_TypeDef *)0x429D0000UL)
#define bCM_I2C4                             ((bCM_I2C_TypeDef *)0x429D8000UL)
#define bCM_I2C5                             ((bCM_I2C_TypeDef *)0x429E0000UL)
#define bCM_I2C6                             ((bCM_I2C_TypeDef *)0x429E8000UL)
#define bCM_I2S1                             ((bCM_I2S_TypeDef *)0x423C0000UL)
#define bCM_I2S2                             ((bCM_I2S_TypeDef *)0x423C8000UL)
#define bCM_I2S3                             ((bCM_I2S_TypeDef *)0x42440000UL)
#define bCM_I2S4                             ((bCM_I2S_TypeDef *)0x42448000UL)
#define bCM_INTC                             ((bCM_INTC_TypeDef *)0x42A20000UL)
#define bCM_KEYSCAN                          ((bCM_KEYSCAN_TypeDef *)0x42A18000UL)
#define bCM_MAU                              ((bCM_MAU_TypeDef *)0x42AA0000UL)
#define bCM_MPU                              ((bCM_MPU_TypeDef *)0x42A00000UL)
#define bCM_OTS                              ((bCM_OTS_TypeDef *)0x4220C000UL)
#define bCM_PERIC                            ((bCM_PERIC_TypeDef *)0x42AA8000UL)
#define bCM_PWC                              ((bCM_PWC_TypeDef *)0x42900000UL)
#define bCM_RMU                              ((bCM_RMU_TypeDef *)0x42998000UL)
#define bCM_RTC                              ((bCM_RTC_TypeDef *)0x42980000UL)
#define bCM_SDIOC1                           ((bCM_SDIOC_TypeDef *)0x42E00000UL)
#define bCM_SDIOC2                           ((bCM_SDIOC_TypeDef *)0x42F08000UL)
#define bCM_SPI1                             ((bCM_SPI_TypeDef *)0x42380000UL)
#define bCM_SPI2                             ((bCM_SPI_TypeDef *)0x42388000UL)
#define bCM_SPI3                             ((bCM_SPI_TypeDef *)0x42390000UL)
#define bCM_SPI4                             ((bCM_SPI_TypeDef *)0x42400000UL)
#define bCM_SPI5                             ((bCM_SPI_TypeDef *)0x42408000UL)
#define bCM_SPI6                             ((bCM_SPI_TypeDef *)0x42410000UL)
#define bCM_SRAMC                            ((bCM_SRAMC_TypeDef *)0x42A10000UL)
#define bCM_SWDT                             ((bCM_SWDT_TypeDef *)0x42928000UL)
#define bCM_TMR0_1                           ((bCM_TMR0_TypeDef *)0x42480000UL)
#define bCM_TMR0_2                           ((bCM_TMR0_TypeDef *)0x42488000UL)
#define bCM_TMR2_1                           ((bCM_TMR2_TypeDef *)0x42490000UL)
#define bCM_TMR2_2                           ((bCM_TMR2_TypeDef *)0x42498000UL)
#define bCM_TMR2_3                           ((bCM_TMR2_TypeDef *)0x424A0000UL)
#define bCM_TMR2_4                           ((bCM_TMR2_TypeDef *)0x424A8000UL)
#define bCM_TMR4_1                           ((bCM_TMR4_TypeDef *)0x42700000UL)
#define bCM_TMR4_2                           ((bCM_TMR4_TypeDef *)0x42708000UL)
#define bCM_TMR4_3                           ((bCM_TMR4_TypeDef *)0x42710000UL)
#define bCM_TMR6_1                           ((bCM_TMR6_TypeDef *)0x42300000UL)
#define bCM_TMR6_2                           ((bCM_TMR6_TypeDef *)0x42308000UL)
#define bCM_TMR6_3                           ((bCM_TMR6_TypeDef *)0x42310000UL)
#define bCM_TMR6_4                           ((bCM_TMR6_TypeDef *)0x42318000UL)
#define bCM_TMR6_5                           ((bCM_TMR6_TypeDef *)0x42320000UL)
#define bCM_TMR6_6                           ((bCM_TMR6_TypeDef *)0x42328000UL)
#define bCM_TMR6_7                           ((bCM_TMR6_TypeDef *)0x42330000UL)
#define bCM_TMR6_8                           ((bCM_TMR6_TypeDef *)0x42338000UL)
#define bCM_TMR6CR                           ((bCM_TMR6CR_TypeDef *)0x42300000UL)
#define bCM_TMRA_1                           ((bCM_TMRA_TypeDef *)0x42740000UL)
#define bCM_TMRA_10                          ((bCM_TMRA_TypeDef *)0x424E8000UL)
#define bCM_TMRA_11                          ((bCM_TMRA_TypeDef *)0x424F0000UL)
#define bCM_TMRA_12                          ((bCM_TMRA_TypeDef *)0x424F8000UL)
#define bCM_TMRA_2                           ((bCM_TMRA_TypeDef *)0x42748000UL)
#define bCM_TMRA_3                           ((bCM_TMRA_TypeDef *)0x42750000UL)
#define bCM_TMRA_4                           ((bCM_TMRA_TypeDef *)0x42758000UL)
#define bCM_TMRA_5                           ((bCM_TMRA_TypeDef *)0x424C0000UL)
#define bCM_TMRA_6                           ((bCM_TMRA_TypeDef *)0x424C8000UL)
#define bCM_TMRA_7                           ((bCM_TMRA_TypeDef *)0x424D0000UL)
#define bCM_TMRA_8                           ((bCM_TMRA_TypeDef *)0x424D8000UL)
#define bCM_TMRA_9                           ((bCM_TMRA_TypeDef *)0x424E0000UL)
#define bCM_TRNG                             ((bCM_TRNG_TypeDef *)0x42840000UL)
#define bCM_USART1                           ((bCM_USART_TypeDef *)0x42398000UL)
#define bCM_USART10                          ((bCM_USART_TypeDef *)0x42438000UL)
#define bCM_USART2                           ((bCM_USART_TypeDef *)0x423A0000UL)
#define bCM_USART3                           ((bCM_USART_TypeDef *)0x423A8000UL)
#define bCM_USART4                           ((bCM_USART_TypeDef *)0x423B0000UL)
#define bCM_USART5                           ((bCM_USART_TypeDef *)0x423B8000UL)
#define bCM_USART6                           ((bCM_USART_TypeDef *)0x42418000UL)
#define bCM_USART7                           ((bCM_USART_TypeDef *)0x42420000UL)
#define bCM_USART8                           ((bCM_USART_TypeDef *)0x42428000UL)
#define bCM_USART9                           ((bCM_USART_TypeDef *)0x42430000UL)
#define bCM_USBFS                            ((bCM_USBFS_TypeDef *)0x43000000UL)
#define bCM_USBHS                            ((bCM_USBHS_TypeDef *)0x43800000UL)
#define bCM_WDT                              ((bCM_WDT_TypeDef *)0x42920000UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_H__ */
