/**
 *******************************************************************************
 * @file  HC32F460.h
 * @brief Headerfile for HC32F460 series MCU
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 **/

#ifndef __HC32F460_H__
#define __HC32F460_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 ******************************************************************************/
#define __MPU_PRESENT             1       /*!< HC32F460 provides MPU                            */
#define __VTOR_PRESENT            1       /*!< HC32F460 supported vector table registers            */
#define __NVIC_PRIO_BITS          4       /*!< HC32F460 uses 4 Bits for the Priority Levels         */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used              */
#define __FPU_PRESENT             1       /*!< FPU present                                               */

/*******************************************************************************
 * Interrupt Number Definition
 ******************************************************************************/
typedef enum {
    NMI_IRQn                    = -14,  /* Non Maskable                             */
    HardFault_IRQn              = -13,  /* Hard Fault                               */
    MemManageFault_IRQn         = -12,  /* MemManage Fault                          */
    BusFault_IRQn               = -11,  /* Bus Fault                                */
    UsageFault_IRQn             = -10,  /* Usage Fault                              */
    SVC_IRQn                    = -5,   /* SVCall                                   */
    DebugMonitor_IRQn           = -4,   /* DebugMonitor                             */
    PendSV_IRQn                 = -2,   /* Pend SV                                  */
    SysTick_IRQn                = -1,   /* System Tick                              */
    INT000_IRQn                 = 0,
    INT001_IRQn                 = 1,
    INT002_IRQn                 = 2,
    INT003_IRQn                 = 3,
    INT004_IRQn                 = 4,
    INT005_IRQn                 = 5,
    INT006_IRQn                 = 6,
    INT007_IRQn                 = 7,
    INT008_IRQn                 = 8,
    INT009_IRQn                 = 9,
    INT010_IRQn                 = 10,
    INT011_IRQn                 = 11,
    INT012_IRQn                 = 12,
    INT013_IRQn                 = 13,
    INT014_IRQn                 = 14,
    INT015_IRQn                 = 15,
    INT016_IRQn                 = 16,
    INT017_IRQn                 = 17,
    INT018_IRQn                 = 18,
    INT019_IRQn                 = 19,
    INT020_IRQn                 = 20,
    INT021_IRQn                 = 21,
    INT022_IRQn                 = 22,
    INT023_IRQn                 = 23,
    INT024_IRQn                 = 24,
    INT025_IRQn                 = 25,
    INT026_IRQn                 = 26,
    INT027_IRQn                 = 27,
    INT028_IRQn                 = 28,
    INT029_IRQn                 = 29,
    INT030_IRQn                 = 30,
    INT031_IRQn                 = 31,
    INT032_IRQn                 = 32,
    INT033_IRQn                 = 33,
    INT034_IRQn                 = 34,
    INT035_IRQn                 = 35,
    INT036_IRQn                 = 36,
    INT037_IRQn                 = 37,
    INT038_IRQn                 = 38,
    INT039_IRQn                 = 39,
    INT040_IRQn                 = 40,
    INT041_IRQn                 = 41,
    INT042_IRQn                 = 42,
    INT043_IRQn                 = 43,
    INT044_IRQn                 = 44,
    INT045_IRQn                 = 45,
    INT046_IRQn                 = 46,
    INT047_IRQn                 = 47,
    INT048_IRQn                 = 48,
    INT049_IRQn                 = 49,
    INT050_IRQn                 = 50,
    INT051_IRQn                 = 51,
    INT052_IRQn                 = 52,
    INT053_IRQn                 = 53,
    INT054_IRQn                 = 54,
    INT055_IRQn                 = 55,
    INT056_IRQn                 = 56,
    INT057_IRQn                 = 57,
    INT058_IRQn                 = 58,
    INT059_IRQn                 = 59,
    INT060_IRQn                 = 60,
    INT061_IRQn                 = 61,
    INT062_IRQn                 = 62,
    INT063_IRQn                 = 63,
    INT064_IRQn                 = 64,
    INT065_IRQn                 = 65,
    INT066_IRQn                 = 66,
    INT067_IRQn                 = 67,
    INT068_IRQn                 = 68,
    INT069_IRQn                 = 69,
    INT070_IRQn                 = 70,
    INT071_IRQn                 = 71,
    INT072_IRQn                 = 72,
    INT073_IRQn                 = 73,
    INT074_IRQn                 = 74,
    INT075_IRQn                 = 75,
    INT076_IRQn                 = 76,
    INT077_IRQn                 = 77,
    INT078_IRQn                 = 78,
    INT079_IRQn                 = 79,
    INT080_IRQn                 = 80,
    INT081_IRQn                 = 81,
    INT082_IRQn                 = 82,
    INT083_IRQn                 = 83,
    INT084_IRQn                 = 84,
    INT085_IRQn                 = 85,
    INT086_IRQn                 = 86,
    INT087_IRQn                 = 87,
    INT088_IRQn                 = 88,
    INT089_IRQn                 = 89,
    INT090_IRQn                 = 90,
    INT091_IRQn                 = 91,
    INT092_IRQn                 = 92,
    INT093_IRQn                 = 93,
    INT094_IRQn                 = 94,
    INT095_IRQn                 = 95,
    INT096_IRQn                 = 96,
    INT097_IRQn                 = 97,
    INT098_IRQn                 = 98,
    INT099_IRQn                 = 99,
    INT100_IRQn                 = 100,
    INT101_IRQn                 = 101,
    INT102_IRQn                 = 102,
    INT103_IRQn                 = 103,
    INT104_IRQn                 = 104,
    INT105_IRQn                 = 105,
    INT106_IRQn                 = 106,
    INT107_IRQn                 = 107,
    INT108_IRQn                 = 108,
    INT109_IRQn                 = 109,
    INT110_IRQn                 = 110,
    INT111_IRQn                 = 111,
    INT112_IRQn                 = 112,
    INT113_IRQn                 = 113,
    INT114_IRQn                 = 114,
    INT115_IRQn                 = 115,
    INT116_IRQn                 = 116,
    INT117_IRQn                 = 117,
    INT118_IRQn                 = 118,
    INT119_IRQn                 = 119,
    INT120_IRQn                 = 120,
    INT121_IRQn                 = 121,
    INT122_IRQn                 = 122,
    INT123_IRQn                 = 123,
    INT124_IRQn                 = 124,
    INT125_IRQn                 = 125,
    INT126_IRQn                 = 126,
    INT127_IRQn                 = 127,
    INT128_IRQn                 = 128,
    INT129_IRQn                 = 129,
    INT130_IRQn                 = 130,
    INT131_IRQn                 = 131,
    INT132_IRQn                 = 132,
    INT133_IRQn                 = 133,
    INT134_IRQn                 = 134,
    INT135_IRQn                 = 135,
    INT136_IRQn                 = 136,
    INT137_IRQn                 = 137,
    INT138_IRQn                 = 138,
    INT139_IRQn                 = 139,
    INT140_IRQn                 = 140,
    INT141_IRQn                 = 141,
    INT142_IRQn                 = 142,
    INT143_IRQn                 = 143,

} IRQn_Type;

#include <core_cm4.h>
#include <stdint.h>

/**
 *******************************************************************************
 ** \brief Event number enumeration
 ******************************************************************************/
typedef enum {
    EVT_SRC_SWI_IRQ0            = 0U,       /* SWI_IRQ0  */
    EVT_SRC_SWI_IRQ1            = 1U,       /* SWI_IRQ1  */
    EVT_SRC_SWI_IRQ2            = 2U,       /* SWI_IRQ2  */
    EVT_SRC_SWI_IRQ3            = 3U,       /* SWI_IRQ3  */
    EVT_SRC_SWI_IRQ4            = 4U,       /* SWI_IRQ4  */
    EVT_SRC_SWI_IRQ5            = 5U,       /* SWI_IRQ5  */
    EVT_SRC_SWI_IRQ6            = 6U,       /* SWI_IRQ6  */
    EVT_SRC_SWI_IRQ7            = 7U,       /* SWI_IRQ7  */
    EVT_SRC_SWI_IRQ8            = 8U,       /* SWI_IRQ8  */
    EVT_SRC_SWI_IRQ9            = 9U,       /* SWI_IRQ9  */
    EVT_SRC_SWI_IRQ10           = 10U,      /* SWI_IRQ10 */
    EVT_SRC_SWI_IRQ11           = 11U,      /* SWI_IRQ11 */
    EVT_SRC_SWI_IRQ12           = 12U,      /* SWI_IRQ12 */
    EVT_SRC_SWI_IRQ13           = 13U,      /* SWI_IRQ13 */
    EVT_SRC_SWI_IRQ14           = 14U,      /* SWI_IRQ14 */
    EVT_SRC_SWI_IRQ15           = 15U,      /* SWI_IRQ15 */
    EVT_SRC_SWI_IRQ16           = 16U,      /* SWI_IRQ16 */
    EVT_SRC_SWI_IRQ17           = 17U,      /* SWI_IRQ17 */
    EVT_SRC_SWI_IRQ18           = 18U,      /* SWI_IRQ18 */
    EVT_SRC_SWI_IRQ19           = 19U,      /* SWI_IRQ19 */
    EVT_SRC_SWI_IRQ20           = 20U,      /* SWI_IRQ20 */
    EVT_SRC_SWI_IRQ21           = 21U,      /* SWI_IRQ21 */
    EVT_SRC_SWI_IRQ22           = 22U,      /* SWI_IRQ22 */
    EVT_SRC_SWI_IRQ23           = 23U,      /* SWI_IRQ23 */
    EVT_SRC_SWI_IRQ24           = 24U,      /* SWI_IRQ24 */
    EVT_SRC_SWI_IRQ25           = 25U,      /* SWI_IRQ25 */
    EVT_SRC_SWI_IRQ26           = 26U,      /* SWI_IRQ26 */
    EVT_SRC_SWI_IRQ27           = 27U,      /* SWI_IRQ27 */
    EVT_SRC_SWI_IRQ28           = 28U,      /* SWI_IRQ28 */
    EVT_SRC_SWI_IRQ29           = 29U,      /* SWI_IRQ29 */
    EVT_SRC_SWI_IRQ30           = 30U,      /* SWI_IRQ30 */
    EVT_SRC_SWI_IRQ31           = 31U,      /* SWI_IRQ31 */

    /* External Interrupt. */
    EVT_SRC_PORT_EIRQ0          = 0U,       /* PORT_EIRQ0  */
    EVT_SRC_PORT_EIRQ1          = 1U,       /* PORT_EIRQ1  */
    EVT_SRC_PORT_EIRQ2          = 2U,       /* PORT_EIRQ2  */
    EVT_SRC_PORT_EIRQ3          = 3U,       /* PORT_EIRQ3  */
    EVT_SRC_PORT_EIRQ4          = 4U,       /* PORT_EIRQ4  */
    EVT_SRC_PORT_EIRQ5          = 5U,       /* PORT_EIRQ5  */
    EVT_SRC_PORT_EIRQ6          = 6U,       /* PORT_EIRQ6  */
    EVT_SRC_PORT_EIRQ7          = 7U,       /* PORT_EIRQ7  */
    EVT_SRC_PORT_EIRQ8          = 8U,       /* PORT_EIRQ8  */
    EVT_SRC_PORT_EIRQ9          = 9U,       /* PORT_EIRQ9  */
    EVT_SRC_PORT_EIRQ10         = 10U,      /* PORT_EIRQ10 */
    EVT_SRC_PORT_EIRQ11         = 11U,      /* PORT_EIRQ11 */
    EVT_SRC_PORT_EIRQ12         = 12U,      /* PORT_EIRQ12 */
    EVT_SRC_PORT_EIRQ13         = 13U,      /* PORT_EIRQ13 */
    EVT_SRC_PORT_EIRQ14         = 14U,      /* PORT_EIRQ14 */
    EVT_SRC_PORT_EIRQ15         = 15U,      /* PORT_EIRQ15 */

    /* DMAC */
    EVT_SRC_DMA1_TC0            = 32U,      /* DMA1_TC0  */
    EVT_SRC_DMA1_TC1            = 33U,      /* DMA1_TC1  */
    EVT_SRC_DMA1_TC2            = 34U,      /* DMA1_TC2  */
    EVT_SRC_DMA1_TC3            = 35U,      /* DMA1_TC3  */
    EVT_SRC_DMA2_TC0            = 36U,      /* DMA2_TC0  */
    EVT_SRC_DMA2_TC1            = 37U,      /* DMA2_TC1  */
    EVT_SRC_DMA2_TC2            = 38U,      /* DMA2_TC2  */
    EVT_SRC_DMA2_TC3            = 39U,      /* DMA2_TC3  */
    EVT_SRC_DMA1_BTC0           = 40U,      /* DMA1_BTC0 */
    EVT_SRC_DMA1_BTC1           = 41U,      /* DMA1_BTC1 */
    EVT_SRC_DMA1_BTC2           = 42U,      /* DMA1_BTC2 */
    EVT_SRC_DMA1_BTC3           = 43U,      /* DMA1_BTC3 */
    EVT_SRC_DMA2_BTC0           = 44U,      /* DMA2_BTC0 */
    EVT_SRC_DMA2_BTC1           = 45U,      /* DMA2_BTC1 */
    EVT_SRC_DMA2_BTC2           = 46U,      /* DMA2_BTC2 */
    EVT_SRC_DMA2_BTC3           = 47U,      /* DMA2_BTC3 */

    /* EFM */
    EVT_SRC_EFM_OPTEND          = 52U,      /* EFM_OPTEND */

    /* USB SOF */
    EVT_SRC_USBFS_SOF           = 53U,      /* USBFS_SOF */

    /* DCU */
    EVT_SRC_DCU1                = 55U,      /* DCU1 */
    EVT_SRC_DCU2                = 56U,      /* DCU2 */
    EVT_SRC_DCU3                = 57U,      /* DCU3 */
    EVT_SRC_DCU4                = 58U,      /* DCU4 */

    /* TIMER 0 */
    EVT_SRC_TMR0_1_CMP_A        = 64U,      /* TMR01_GCMA */
    EVT_SRC_TMR0_1_CMP_B        = 65U,      /* TMR01_GCMB */
    EVT_SRC_TMR0_2_CMP_A        = 66U,      /* TMR02_GCMA */
    EVT_SRC_TMR0_2_CMP_B        = 67U,      /* TMR02_GCMB */

    /* RTC */
    EVT_SRC_RTC_ALM             = 81U,      /* RTC_ALM */
    EVT_SRC_RTC_PRD             = 82U,      /* RTC_PRD */

    /* TIMER 6 */
    EVT_SRC_TMR6_1_GCMP_A       = 96U,      /* TMR61_GCMA */
    EVT_SRC_TMR6_1_GCMP_B       = 97U,      /* TMR61_GCMB */
    EVT_SRC_TMR6_1_GCMP_C       = 98U,      /* TMR61_GCMC */
    EVT_SRC_TMR6_1_GCMP_D       = 99U,      /* TMR61_GCMD */
    EVT_SRC_TMR6_1_GCMP_E       = 100U,     /* TMR61_GCME */
    EVT_SRC_TMR6_1_GCMP_F       = 101U,     /* TMR61_GCMF */
    EVT_SRC_TMR6_1_OVF          = 102U,     /* TMR61_GOVF */
    EVT_SRC_TMR6_1_UDF          = 103U,     /* TMR61_GUDF */
    EVT_SRC_TMR6_1_SCMP_A       = 107U,     /* TMR61_SCMA */
    EVT_SRC_TMR6_1_SCMP_B       = 108U,     /* TMR61_SCMB */
    EVT_SRC_TMR6_2_GCMP_A       = 112U,     /* TMR62_GCMA */
    EVT_SRC_TMR6_2_GCMP_B       = 113U,     /* TMR62_GCMB */
    EVT_SRC_TMR6_2_GCMP_C       = 114U,     /* TMR62_GCMC */
    EVT_SRC_TMR6_2_GCMP_D       = 115U,     /* TMR62_GCMD */
    EVT_SRC_TMR6_2_GCMP_E       = 116U,     /* TMR62_GCME */
    EVT_SRC_TMR6_2_GCMP_F       = 117U,     /* TMR62_GCMF */
    EVT_SRC_TMR6_2_OVF          = 118U,     /* TMR62_GOVF */
    EVT_SRC_TMR6_2_UDF          = 119U,     /* TMR62_GUDF */
    EVT_SRC_TMR6_2_SCMP_A       = 123U,     /* TMR62_SCMA */
    EVT_SRC_TMR6_2_SCMP_B       = 124U,     /* TMR62_SCMB */
    EVT_SRC_TMR6_3_GCMP_A       = 128U,     /* TMR63_GCMA */
    EVT_SRC_TMR6_3_GCMP_B       = 129U,     /* TMR63_GCMB */
    EVT_SRC_TMR6_3_GCMP_C       = 130U,     /* TMR63_GCMC */
    EVT_SRC_TMR6_3_GCMP_D       = 131U,     /* TMR63_GCMD */
    EVT_SRC_TMR6_3_GCMP_E       = 132U,     /* TMR63_GCME */
    EVT_SRC_TMR6_3_GCMP_F       = 133U,     /* TMR63_GCMF */
    EVT_SRC_TMR6_3_OVF          = 134U,     /* TMR63_GOVF */
    EVT_SRC_TMR6_3_UDF          = 135U,     /* TMR63_GUDF */
    EVT_SRC_TMR6_3_SCMP_A       = 139U,     /* TMR63_SCMA */
    EVT_SRC_TMR6_3_SCMP_B       = 140U,     /* TMR63_SCMB */

    /* TIMER A */
    EVT_SRC_TMRA_1_OVF          = 256U,     /* TMRA1_OVF */
    EVT_SRC_TMRA_1_UDF          = 257U,     /* TMRA1_UDF */
    EVT_SRC_TMRA_1_CMP          = 258U,     /* TMRA1_CMP */
    EVT_SRC_TMRA_2_OVF          = 259U,     /* TMRA2_OVF */
    EVT_SRC_TMRA_2_UDF          = 260U,     /* TMRA2_UDF */
    EVT_SRC_TMRA_2_CMP          = 261U,     /* TMRA2_CMP */
    EVT_SRC_TMRA_3_OVF          = 262U,     /* TMRA3_OVF */
    EVT_SRC_TMRA_3_UDF          = 263U,     /* TMRA3_UDF */
    EVT_SRC_TMRA_3_CMP          = 264U,     /* TMRA3_CMP */
    EVT_SRC_TMRA_4_OVF          = 265U,     /* TMRA4_OVF */
    EVT_SRC_TMRA_4_UDF          = 266U,     /* TMRA4_UDF */
    EVT_SRC_TMRA_4_CMP          = 267U,     /* TMRA4_CMP */
    EVT_SRC_TMRA_5_OVF          = 268U,     /* TMRA5_OVF */
    EVT_SRC_TMRA_5_UDF          = 269U,     /* TMRA5_UDF */
    EVT_SRC_TMRA_5_CMP          = 270U,     /* TMRA5_CMP */
    EVT_SRC_TMRA_6_OVF          = 272U,     /* TMRA6_OVF */
    EVT_SRC_TMRA_6_UDF          = 273U,     /* TMRA6_UDF */
    EVT_SRC_TMRA_6_CMP          = 274U,     /* TMRA6_CMP */

    /* USART */
    EVT_SRC_USART1_EI           = 278U,     /* USART1_EI  */
    EVT_SRC_USART1_RI           = 279U,     /* USART1_RI  */
    EVT_SRC_USART1_TI           = 280U,     /* USART1_TI  */
    EVT_SRC_USART1_TCI          = 281U,     /* USART1_TCI */
    EVT_SRC_USART1_RTO          = 282U,     /* USART1_RTO */
    EVT_SRC_USART2_EI           = 283U,     /* USART2_EI  */
    EVT_SRC_USART2_RI           = 284U,     /* USART2_RI  */
    EVT_SRC_USART2_TI           = 285U,     /* USART2_TI  */
    EVT_SRC_USART2_TCI          = 286U,     /* USART2_TCI */
    EVT_SRC_USART2_RTO          = 287U,     /* USART2_RTO */
    EVT_SRC_USART3_EI           = 288U,     /* USART3_EI  */
    EVT_SRC_USART3_RI           = 289U,     /* USART3_RI  */
    EVT_SRC_USART3_TI           = 290U,     /* USART3_TI  */
    EVT_SRC_USART3_TCI          = 291U,     /* USART3_TCI */
    EVT_SRC_USART3_RTO          = 292U,     /* USART3_RTO */
    EVT_SRC_USART4_EI           = 293U,     /* USART4_EI  */
    EVT_SRC_USART4_RI           = 294U,     /* USART4_RI  */
    EVT_SRC_USART4_TI           = 295U,     /* USART4_TI  */
    EVT_SRC_USART4_TCI          = 296U,     /* USART4_TCI */
    EVT_SRC_USART4_RTO          = 297U,     /* USART4_RTO */

    /* SPI */
    EVT_SRC_SPI1_SPRI           = 299U,     /* SPI1_SPRI   */
    EVT_SRC_SPI1_SPTI           = 300U,     /* SPI1_SPTI   */
    EVT_SRC_SPI1_SPII           = 301U,     /* SPI1_SPII   */
    EVT_SRC_SPI1_SPEI           = 302U,     /* SPI1_SPEI   */
    EVT_SRC_SPI1_SPTEND         = 303U,     /* SPI1_SPTEND */
    EVT_SRC_SPI2_SPRI           = 304U,     /* SPI2_SPRI   */
    EVT_SRC_SPI2_SPTI           = 305U,     /* SPI2_SPTI   */
    EVT_SRC_SPI2_SPII           = 306U,     /* SPI2_SPII   */
    EVT_SRC_SPI2_SPEI           = 307U,     /* SPI2_SPEI   */
    EVT_SRC_SPI2_SPTEND         = 308U,     /* SPI2_SPTEND */
    EVT_SRC_SPI3_SPRI           = 309U,     /* SPI3_SPRI   */
    EVT_SRC_SPI3_SPTI           = 310U,     /* SPI3_SPTI   */
    EVT_SRC_SPI3_SPII           = 311U,     /* SPI3_SPII   */
    EVT_SRC_SPI3_SPEI           = 312U,     /* SPI3_SPEI   */
    EVT_SRC_SPI3_SPTEND         = 313U,     /* SPI3_SPTEND */
    EVT_SRC_SPI4_SPRI           = 314U,     /* SPI4_SPRI   */
    EVT_SRC_SPI4_SPTI           = 315U,     /* SPI4_SPTI   */
    EVT_SRC_SPI4_SPII           = 316U,     /* SPI4_SPII   */
    EVT_SRC_SPI4_SPEI           = 317U,     /* SPI4_SPEI   */
    EVT_SRC_SPI4_SPTEND         = 318U,     /* SPI4_SPTEND */

    /* AOS */
    EVT_SRC_AOS_STRG            = 319U,     /* AOS_STRG */

    /* TIMER 4 */
    EVT_SRC_TMR4_1_SCMP_UH      = 368U,     /* TMR41_SCMUH */
    EVT_SRC_TMR4_1_SCMP_UL      = 369U,     /* TMR41_SCMUL */
    EVT_SRC_TMR4_1_SCMP_VH      = 370U,     /* TMR41_SCMVH */
    EVT_SRC_TMR4_1_SCMP_VL      = 371U,     /* TMR41_SCMVL */
    EVT_SRC_TMR4_1_SCMP_WH      = 372U,     /* TMR41_SCMWH */
    EVT_SRC_TMR4_1_SCMP_WL      = 373U,     /* TMR41_SCMWL */
    EVT_SRC_TMR4_2_SCMP_UH      = 374U,     /* TMR42_SCMUH */
    EVT_SRC_TMR4_2_SCMP_UL      = 375U,     /* TMR42_SCMUL */
    EVT_SRC_TMR4_2_SCMP_VH      = 376U,     /* TMR42_SCMVH */
    EVT_SRC_TMR4_2_SCMP_VL      = 377U,     /* TMR42_SCMVL */
    EVT_SRC_TMR4_2_SCMP_WH      = 378U,     /* TMR42_SCMWH */
    EVT_SRC_TMR4_2_SCMP_WL      = 379U,     /* TMR42_SCMWL */
    EVT_SRC_TMR4_3_SCMP_UH      = 384U,     /* TMR43_SCMUH */
    EVT_SRC_TMR4_3_SCMP_UL      = 385U,     /* TMR43_SCMUL */
    EVT_SRC_TMR4_3_SCMP_VH      = 386U,     /* TMR43_SCMVH */
    EVT_SRC_TMR4_3_SCMP_VL      = 387U,     /* TMR43_SCMVL */
    EVT_SRC_TMR4_3_SCMP_WH      = 388U,     /* TMR43_SCMWH */
    EVT_SRC_TMR4_3_SCMP_WL      = 389U,     /* TMR43_SCMWL */

    /* EVENT PORT */
    EVT_SRC_EVENT_PORT1         = 394U,     /* EVENT_PORT1 */
    EVT_SRC_EVENT_PORT2         = 395U,     /* EVENT_PORT2 */
    EVT_SRC_EVENT_PORT3         = 396U,     /* EVENT_PORT3 */
    EVT_SRC_EVENT_PORT4         = 397U,     /* EVENT_PORT4 */

    /* I2S */
    EVT_SRC_I2S1_TXIRQOUT       = 400U,     /* I2S1_TXIRQOUT */
    EVT_SRC_I2S1_RXIRQOUT       = 401U,     /* I2S1_RXIRQOUT */
    EVT_SRC_I2S2_TXIRQOUT       = 403U,     /* I2S2_TXIRQOUT */
    EVT_SRC_I2S2_RXIRQOUT       = 404U,     /* I2S2_RXIRQOUT */
    EVT_SRC_I2S3_TXIRQOUT       = 406U,     /* I2S3_TXIRQOUT */
    EVT_SRC_I2S3_RXIRQOUT       = 407U,     /* I2S3_RXIRQOUT */
    EVT_SRC_I2S4_TXIRQOUT       = 409U,     /* I2S4_TXIRQOUT */
    EVT_SRC_I2S4_RXIRQOUT       = 410U,     /* I2S4_RXIRQOUT */

    /* COMPARATOR */
    EVT_SRC_CMP1                = 416U,     /* ACMP1 */
    EVT_SRC_CMP2                = 417U,     /* ACMP1 */
    EVT_SRC_CMP3                = 418U,     /* ACMP1 */

    /* I2C */
    EVT_SRC_I2C1_RXI            = 420U,     /* I2C1_RXI */
    EVT_SRC_I2C1_TXI            = 421U,     /* I2C1_TXI */
    EVT_SRC_I2C1_TEI            = 422U,     /* I2C1_TEI */
    EVT_SRC_I2C1_EEI            = 423U,     /* I2C1_EEI */
    EVT_SRC_I2C2_RXI            = 424U,     /* I2C2_RXI */
    EVT_SRC_I2C2_TXI            = 425U,     /* I2C2_TXI */
    EVT_SRC_I2C2_TEI            = 426U,     /* I2C2_TEI */
    EVT_SRC_I2C2_EEI            = 427U,     /* I2C2_EEI */
    EVT_SRC_I2C3_RXI            = 428U,     /* I2C3_RXI */
    EVT_SRC_I2C3_TXI            = 429U,     /* I2C3_TXI */
    EVT_SRC_I2C3_TEI            = 430U,     /* I2C3_TEI */
    EVT_SRC_I2C3_EEI            = 431U,     /* I2C3_EEI */

    /* LVD */
    EVT_SRC_LVD1                = 433U,     /* LVD1 */
    EVT_SRC_LVD2                = 434U,     /* LVD2 */

    /* OTS */
    EVT_SRC_OTS                 = 435U,     /* OTS */

    /* WDT */
    EVT_SRC_WDT_REFUDF          = 439U,     /* WDT_REFUDF */

    /* ADC */
    EVT_SRC_ADC1_EOCA           = 448U,     /* ADC1_EOCA   */
    EVT_SRC_ADC1_EOCB           = 449U,     /* ADC1_EOCB   */
    EVT_SRC_ADC1_CHCMP          = 450U,     /* ADC1_CHCMP  */
    EVT_SRC_ADC1_SEQCMP         = 451U,     /* ADC1_SEQCMP */
    EVT_SRC_ADC2_EOCA           = 452U,     /* ADC2_EOCA   */
    EVT_SRC_ADC2_EOCB           = 453U,     /* ADC2_EOCB   */
    EVT_SRC_ADC2_CHCMP          = 454U,     /* ADC2_CHCMP  */
    EVT_SRC_ADC2_SEQCMP         = 455U,     /* ADC2_SEQCMP */

    /* TRNG */
    EVT_SRC_TRNG_END            = 456U,     /* TRNG_END */

    /* SDIO */
    EVT_SRC_SDIOC1_DMAR         = 480U,     /* SDIOC1_DMAR */
    EVT_SRC_SDIOC1_DMAW         = 481U,     /* SDIOC1_DMAW */
    EVT_SRC_SDIOC2_DMAR         = 483U,     /* SDIOC2_DMAR */
    EVT_SRC_SDIOC2_DMAW         = 484U,     /* SDIOC2_DMAW */
    EVT_SRC_MAX                 = 511U,
} en_event_src_t;

/**
 *******************************************************************************
 ** \brief Interrupt number enumeration
 ******************************************************************************/
typedef enum {
    INT_SRC_SWI_IRQ0            = 0U,       /* SWI_IRQ0  */
    INT_SRC_SWI_IRQ1            = 1U,       /* SWI_IRQ1  */
    INT_SRC_SWI_IRQ2            = 2U,       /* SWI_IRQ2  */
    INT_SRC_SWI_IRQ3            = 3U,       /* SWI_IRQ3  */
    INT_SRC_SWI_IRQ4            = 4U,       /* SWI_IRQ4  */
    INT_SRC_SWI_IRQ5            = 5U,       /* SWI_IRQ5  */
    INT_SRC_SWI_IRQ6            = 6U,       /* SWI_IRQ6  */
    INT_SRC_SWI_IRQ7            = 7U,       /* SWI_IRQ7  */
    INT_SRC_SWI_IRQ8            = 8U,       /* SWI_IRQ8  */
    INT_SRC_SWI_IRQ9            = 9U,       /* SWI_IRQ9  */
    INT_SRC_SWI_IRQ10           = 10U,      /* SWI_IRQ10 */
    INT_SRC_SWI_IRQ11           = 11U,      /* SWI_IRQ11 */
    INT_SRC_SWI_IRQ12           = 12U,      /* SWI_IRQ12 */
    INT_SRC_SWI_IRQ13           = 13U,      /* SWI_IRQ13 */
    INT_SRC_SWI_IRQ14           = 14U,      /* SWI_IRQ14 */
    INT_SRC_SWI_IRQ15           = 15U,      /* SWI_IRQ15 */
    INT_SRC_SWI_IRQ16           = 16U,      /* SWI_IRQ16 */
    INT_SRC_SWI_IRQ17           = 17U,      /* SWI_IRQ17 */
    INT_SRC_SWI_IRQ18           = 18U,      /* SWI_IRQ18 */
    INT_SRC_SWI_IRQ19           = 19U,      /* SWI_IRQ19 */
    INT_SRC_SWI_IRQ20           = 20U,      /* SWI_IRQ20 */
    INT_SRC_SWI_IRQ21           = 21U,      /* SWI_IRQ21 */
    INT_SRC_SWI_IRQ22           = 22U,      /* SWI_IRQ22 */
    INT_SRC_SWI_IRQ23           = 23U,      /* SWI_IRQ23 */
    INT_SRC_SWI_IRQ24           = 24U,      /* SWI_IRQ24 */
    INT_SRC_SWI_IRQ25           = 25U,      /* SWI_IRQ25 */
    INT_SRC_SWI_IRQ26           = 26U,      /* SWI_IRQ26 */
    INT_SRC_SWI_IRQ27           = 27U,      /* SWI_IRQ27 */
    INT_SRC_SWI_IRQ28           = 28U,      /* SWI_IRQ28 */
    INT_SRC_SWI_IRQ29           = 29U,      /* SWI_IRQ29 */
    INT_SRC_SWI_IRQ30           = 30U,      /* SWI_IRQ30 */
    INT_SRC_SWI_IRQ31           = 31U,      /* SWI_IRQ31 */

    /* External Interrupt. */
    INT_SRC_PORT_EIRQ0          = 0U,       /* PORT_EIRQ0  */
    INT_SRC_PORT_EIRQ1          = 1U,       /* PORT_EIRQ1  */
    INT_SRC_PORT_EIRQ2          = 2U,       /* PORT_EIRQ2  */
    INT_SRC_PORT_EIRQ3          = 3U,       /* PORT_EIRQ3  */
    INT_SRC_PORT_EIRQ4          = 4U,       /* PORT_EIRQ4  */
    INT_SRC_PORT_EIRQ5          = 5U,       /* PORT_EIRQ5  */
    INT_SRC_PORT_EIRQ6          = 6U,       /* PORT_EIRQ6  */
    INT_SRC_PORT_EIRQ7          = 7U,       /* PORT_EIRQ7  */
    INT_SRC_PORT_EIRQ8          = 8U,       /* PORT_EIRQ8  */
    INT_SRC_PORT_EIRQ9          = 9U,       /* PORT_EIRQ9  */
    INT_SRC_PORT_EIRQ10         = 10U,      /* PORT_EIRQ10 */
    INT_SRC_PORT_EIRQ11         = 11U,      /* PORT_EIRQ11 */
    INT_SRC_PORT_EIRQ12         = 12U,      /* PORT_EIRQ12 */
    INT_SRC_PORT_EIRQ13         = 13U,      /* PORT_EIRQ13 */
    INT_SRC_PORT_EIRQ14         = 14U,      /* PORT_EIRQ14 */
    INT_SRC_PORT_EIRQ15         = 15U,      /* PORT_EIRQ15 */

    /* DMAC */
    INT_SRC_DMA1_TC0            = 32U,      /* DMA1_TC0  */
    INT_SRC_DMA1_TC1            = 33U,      /* DMA1_TC1  */
    INT_SRC_DMA1_TC2            = 34U,      /* DMA1_TC2  */
    INT_SRC_DMA1_TC3            = 35U,      /* DMA1_TC3  */
    INT_SRC_DMA2_TC0            = 36U,      /* DMA2_TC0  */
    INT_SRC_DMA2_TC1            = 37U,      /* DMA2_TC1  */
    INT_SRC_DMA2_TC2            = 38U,      /* DMA2_TC2  */
    INT_SRC_DMA2_TC3            = 39U,      /* DMA2_TC3  */
    INT_SRC_DMA1_BTC0           = 40U,      /* DMA1_BTC0 */
    INT_SRC_DMA1_BTC1           = 41U,      /* DMA1_BTC1 */
    INT_SRC_DMA1_BTC2           = 42U,      /* DMA1_BTC2 */
    INT_SRC_DMA1_BTC3           = 43U,      /* DMA1_BTC3 */
    INT_SRC_DMA2_BTC0           = 44U,      /* DMA2_BTC0 */
    INT_SRC_DMA2_BTC1           = 45U,      /* DMA2_BTC1 */
    INT_SRC_DMA2_BTC2           = 46U,      /* DMA2_BTC2 */
    INT_SRC_DMA2_BTC3           = 47U,      /* DMA2_BTC3 */
    INT_SRC_DMA1_ERR            = 48U,      /* DMA1_ERR */
    INT_SRC_DMA2_ERR            = 49U,      /* DMA2_ERR */

    /* EFM */
    INT_SRC_EFM_PEERR           = 50U,      /* EFM_PEERR */
    INT_SRC_EFM_COLERR          = 51U,      /* EFM_COLERR */
    INT_SRC_EFM_OPTEND          = 52U,      /* EFM_OPTEND */

    /* QSPI */
    INT_SRC_QSPI_INTR           = 54U,      /* QSPI_INTR */

    /* DCU */
    INT_SRC_DCU1                = 55U,      /* DCU1 */
    INT_SRC_DCU2                = 56U,      /* DCU2 */
    INT_SRC_DCU3                = 57U,      /* DCU3 */
    INT_SRC_DCU4                = 58U,      /* DCU4 */

    /* TIMER 0 */
    INT_SRC_TMR0_1_CMP_A        = 64U,      /* TMR01_GCMA */
    INT_SRC_TMR0_1_CMP_B        = 65U,      /* TMR01_GCMB */
    INT_SRC_TMR0_2_CMP_A        = 66U,      /* TMR02_GCMA */
    INT_SRC_TMR0_2_CMP_B        = 67U,      /* TMR02_GCMB */

    /* RTC */
    INT_SRC_RTC_ALM             = 81U,      /* RTC_ALM */
    INT_SRC_RTC_PRD             = 82U,      /* RTC_PRD */

    /* XTAL32 stop */
    INT_SRC_XTAL32_STOP         = 84U,      /* XTAL32_STOP */

    /* XTAL stop */
    INT_SRC_XTAL_STOP           = 85U,      /* XTAL_STOP */

    /* wake-up timer */
    INT_SRC_WKTM_PRD            = 86U,      /* WKTM_PRD */

    /* SWDT */
    INT_SRC_SWDT_REFUDF         = 87U,      /* SWDT_REFUDF */

    /* TIMER 6 */
    INT_SRC_TMR6_1_GCMP_A       = 96U,      /* TMR61_GCMA */
    INT_SRC_TMR6_1_GCMP_B       = 97U,      /* TMR61_GCMB */
    INT_SRC_TMR6_1_GCMP_C       = 98U,      /* TMR61_GCMC */
    INT_SRC_TMR6_1_GCMP_D       = 99U,      /* TMR61_GCMD */
    INT_SRC_TMR6_1_GCMP_E       = 100U,     /* TMR61_GCME */
    INT_SRC_TMR6_1_GCMP_F       = 101U,     /* TMR61_GCMF */
    INT_SRC_TMR6_1_OVF          = 102U,     /* TMR61_GOVF */
    INT_SRC_TMR6_1_UDF          = 103U,     /* TMR61_GUDF */
    INT_SRC_TMR6_1_DTE          = 104U,     /* TMR61_GDTE */
    INT_SRC_TMR6_1_SCMP_A       = 107U,     /* TMR61_SCMA */
    INT_SRC_TMR6_1_SCMP_B       = 108U,     /* TMR61_SCMB */
    INT_SRC_TMR6_2_GCMP_A       = 112U,     /* TMR62_GCMA */
    INT_SRC_TMR6_2_GCMP_B       = 113U,     /* TMR62_GCMB */
    INT_SRC_TMR6_2_GCMP_C       = 114U,     /* TMR62_GCMC */
    INT_SRC_TMR6_2_GCMP_D       = 115U,     /* TMR62_GCMD */
    INT_SRC_TMR6_2_GCMP_E       = 116U,     /* TMR62_GCME */
    INT_SRC_TMR6_2_GCMP_F       = 117U,     /* TMR62_GCMF */
    INT_SRC_TMR6_2_OVF          = 118U,     /* TMR62_GOVF */
    INT_SRC_TMR6_2_UDF          = 119U,     /* TMR62_GUDF */
    INT_SRC_TMR6_2_DTE          = 120U,     /* TMR62_GDTE */
    INT_SRC_TMR6_2_SCMP_A       = 123U,     /* TMR62_SCMA */
    INT_SRC_TMR6_2_SCMP_B       = 124U,     /* TMR62_SCMB */
    INT_SRC_TMR6_3_GCMP_A       = 128U,     /* TMR63_GCMA */
    INT_SRC_TMR6_3_GCMP_B       = 129U,     /* TMR63_GCMB */
    INT_SRC_TMR6_3_GCMP_C       = 130U,     /* TMR63_GCMC */
    INT_SRC_TMR6_3_GCMP_D       = 131U,     /* TMR63_GCMD */
    INT_SRC_TMR6_3_GCMP_E       = 132U,     /* TMR63_GCME */
    INT_SRC_TMR6_3_GCMP_F       = 133U,     /* TMR63_GCMF */
    INT_SRC_TMR6_3_OVF          = 134U,     /* TMR63_GOVF */
    INT_SRC_TMR6_3_UDF          = 135U,     /* TMR63_GUDF */
    INT_SRC_TMR6_3_DTE          = 136U,     /* TMR63_GDTE */
    INT_SRC_TMR6_3_SCMP_A       = 139U,     /* TMR63_SCMA */
    INT_SRC_TMR6_3_SCMP_B       = 140U,     /* TMR63_SCMB */

    /* TIMER A */
    INT_SRC_TMRA_1_OVF          = 256U,     /* TMRA1_OVF */
    INT_SRC_TMRA_1_UDF          = 257U,     /* TMRA1_UDF */
    INT_SRC_TMRA_1_CMP          = 258U,     /* TMRA1_CMP */
    INT_SRC_TMRA_2_OVF          = 259U,     /* TMRA2_OVF */
    INT_SRC_TMRA_2_UDF          = 260U,     /* TMRA2_UDF */
    INT_SRC_TMRA_2_CMP          = 261U,     /* TMRA2_CMP */
    INT_SRC_TMRA_3_OVF          = 262U,     /* TMRA3_OVF */
    INT_SRC_TMRA_3_UDF          = 263U,     /* TMRA3_UDF */
    INT_SRC_TMRA_3_CMP          = 264U,     /* TMRA3_CMP */
    INT_SRC_TMRA_4_OVF          = 265U,     /* TMRA4_OVF */
    INT_SRC_TMRA_4_UDF          = 266U,     /* TMRA4_UDF */
    INT_SRC_TMRA_4_CMP          = 267U,     /* TMRA4_CMP */
    INT_SRC_TMRA_5_OVF          = 268U,     /* TMRA5_OVF */
    INT_SRC_TMRA_5_UDF          = 269U,     /* TMRA5_UDF */
    INT_SRC_TMRA_5_CMP          = 270U,     /* TMRA5_CMP */
    INT_SRC_TMRA_6_OVF          = 272U,     /* TMRA6_OVF */
    INT_SRC_TMRA_6_UDF          = 273U,     /* TMRA6_UDF */
    INT_SRC_TMRA_6_CMP          = 274U,     /* TMRA6_CMP */

    /* USB FS */
    INT_SRC_USBFS_GLB           = 275U,     /* USBFS_GLB */

    /* USRAT */
    INT_SRC_USART1_EI           = 278U,     /* USART1_EI  */
    INT_SRC_USART1_RI           = 279U,     /* USART1_RI  */
    INT_SRC_USART1_TI           = 280U,     /* USART1_TI  */
    INT_SRC_USART1_TCI          = 281U,     /* USART1_TCI */
    INT_SRC_USART1_RTO          = 282U,     /* USART1_RTO */
    INT_SRC_USART1_WUPI         = 432U,     /* USART1_WUPI */
    INT_SRC_USART2_EI           = 283U,     /* USART2_EI  */
    INT_SRC_USART2_RI           = 284U,     /* USART2_RI  */
    INT_SRC_USART2_TI           = 285U,     /* USART2_TI  */
    INT_SRC_USART2_TCI          = 286U,     /* USART2_TCI */
    INT_SRC_USART2_RTO          = 287U,     /* USART2_RTO */
    INT_SRC_USART3_EI           = 288U,     /* USART3_EI  */
    INT_SRC_USART3_RI           = 289U,     /* USART3_RI  */
    INT_SRC_USART3_TI           = 290U,     /* USART3_TI  */
    INT_SRC_USART3_TCI          = 291U,     /* USART3_TCI */
    INT_SRC_USART3_RTO          = 292U,     /* USART3_RTO */
    INT_SRC_USART4_EI           = 293U,     /* USART4_EI  */
    INT_SRC_USART4_RI           = 294U,     /* USART4_RI  */
    INT_SRC_USART4_TI           = 295U,     /* USART4_TI  */
    INT_SRC_USART4_TCI          = 296U,     /* USART4_TCI */
    INT_SRC_USART4_RTO          = 297U,     /* USART4_RTO */

    /* SPI */
    INT_SRC_SPI1_SPRI           = 299U,     /* SPI1_SPRI   */
    INT_SRC_SPI1_SPTI           = 300U,     /* SPI1_SPTI   */
    INT_SRC_SPI1_SPII           = 301U,     /* SPI1_SPII   */
    INT_SRC_SPI1_SPEI           = 302U,     /* SPI1_SPEI   */
    INT_SRC_SPI2_SPRI           = 304U,     /* SPI2_SPRI   */
    INT_SRC_SPI2_SPTI           = 305U,     /* SPI2_SPTI   */
    INT_SRC_SPI2_SPII           = 306U,     /* SPI2_SPII   */
    INT_SRC_SPI2_SPEI           = 307U,     /* SPI2_SPEI   */
    INT_SRC_SPI3_SPRI           = 309U,     /* SPI3_SPRI   */
    INT_SRC_SPI3_SPTI           = 310U,     /* SPI3_SPTI   */
    INT_SRC_SPI3_SPII           = 311U,     /* SPI3_SPII   */
    INT_SRC_SPI3_SPEI           = 312U,     /* SPI3_SPEI   */
    INT_SRC_SPI4_SPRI           = 314U,     /* SPI4_SPRI   */
    INT_SRC_SPI4_SPTI           = 315U,     /* SPI4_SPTI   */
    INT_SRC_SPI4_SPII           = 316U,     /* SPI4_SPII   */
    INT_SRC_SPI4_SPEI           = 317U,     /* SPI4_SPEI   */

    /* TIMER 4 */
    INT_SRC_TMR4_1_GCMP_UH      = 320U,     /* TMR41_GCMUH */
    INT_SRC_TMR4_1_GCMP_UL      = 321U,     /* TMR41_GCMUL */
    INT_SRC_TMR4_1_GCMP_VH      = 322U,     /* TMR41_GCMVH */
    INT_SRC_TMR4_1_GCMP_VL      = 323U,     /* TMR41_GCMVL */
    INT_SRC_TMR4_1_GCMP_WH      = 324U,     /* TMR41_GCMWH */
    INT_SRC_TMR4_1_GCMP_WL      = 325U,     /* TMR41_GCMWL */
    INT_SRC_TMR4_1_OVF          = 326U,     /* TMR41_GOVF  */
    INT_SRC_TMR4_1_UDF          = 327U,     /* TMR41_GUDF  */
    INT_SRC_TMR4_1_RELOAD_U     = 328U,     /* TMR41_RLOU  */
    INT_SRC_TMR4_1_RELOAD_V     = 329U,     /* TMR41_RLOV  */
    INT_SRC_TMR4_1_RELOAD_W     = 330U,     /* TMR41_RLOW  */
    INT_SRC_TMR4_2_GCMP_UH      = 336U,     /* TMR42_GCMUH */
    INT_SRC_TMR4_2_GCMP_UL      = 337U,     /* TMR42_GCMUL */
    INT_SRC_TMR4_2_GCMP_VH      = 338U,     /* TMR42_GCMVH */
    INT_SRC_TMR4_2_GCMP_VL      = 339U,     /* TMR42_GCMVL */
    INT_SRC_TMR4_2_GCMP_WH      = 340U,     /* TMR42_GCMWH */
    INT_SRC_TMR4_2_GCMP_WL      = 341U,     /* TMR42_GCMWL */
    INT_SRC_TMR4_2_OVF          = 342U,     /* TMR42_GOVF  */
    INT_SRC_TMR4_2_UDF          = 343U,     /* TMR42_GUDF  */
    INT_SRC_TMR4_2_RELOAD_U     = 344U,     /* TMR42_RLOU  */
    INT_SRC_TMR4_2_RELOAD_V     = 345U,     /* TMR42_RLOV  */
    INT_SRC_TMR4_2_RELOAD_W     = 346U,     /* TMR42_RLOW  */
    INT_SRC_TMR4_3_GCMP_UH      = 352U,     /* TMR43_GCMUH */
    INT_SRC_TMR4_3_GCMP_UL      = 353U,     /* TMR43_GCMUL */
    INT_SRC_TMR4_3_GCMP_VH      = 354U,     /* TMR43_GCMVH */
    INT_SRC_TMR4_3_GCMP_VL      = 355U,     /* TMR43_GCMVL */
    INT_SRC_TMR4_3_GCMP_WH      = 356U,     /* TMR43_GCMWH */
    INT_SRC_TMR4_3_GCMP_WL      = 357U,     /* TMR43_GCMWL */
    INT_SRC_TMR4_3_OVF          = 358U,     /* TMR43_GOVF  */
    INT_SRC_TMR4_3_UDF          = 359U,     /* TMR43_GUDF  */
    INT_SRC_TMR4_3_RELOAD_U     = 360U,     /* TMR43_RLOU  */
    INT_SRC_TMR4_3_RELOAD_V     = 361U,     /* TMR43_RLOV  */
    INT_SRC_TMR4_3_RELOAD_W     = 362U,     /* TMR43_RLOW  */

    /* EMB */
    INT_SRC_EMB_GR0             = 390U,     /* EMB_GR0  */
    INT_SRC_EMB_GR1             = 391U,     /* EMB_GR1  */
    INT_SRC_EMB_GR2             = 392U,     /* EMB_GR2  */
    INT_SRC_EMB_GR3             = 393U,     /* EMB_GR3  */

    /* EVENT PORT */
    INT_SRC_EVENT_PORT1         = 394U,     /* EVENT_PORT1  */
    INT_SRC_EVENT_PORT2         = 395U,     /* EVENT_PORT2  */
    INT_SRC_EVENT_PORT3         = 396U,     /* EVENT_PORT3  */
    INT_SRC_EVENT_PORT4         = 397U,     /* EVENT_PORT4  */

    /* I2S */
    INT_SRC_I2S1_TXIRQOUT       = 400U,     /* I2S1_TXIRQOUT */
    INT_SRC_I2S1_RXIRQOUT       = 401U,     /* I2S1_RXIRQOUT */
    INT_SRC_I2S1_ERRIRQOUT      = 402U,     /* I2S1_ERRIRQOUT */
    INT_SRC_I2S2_TXIRQOUT       = 403U,     /* I2S2_TXIRQOUT */
    INT_SRC_I2S2_RXIRQOUT       = 404U,     /* I2S2_RXIRQOUT */
    INT_SRC_I2S2_ERRIRQOUT      = 405U,     /* I2S2_ERRIRQOUT */
    INT_SRC_I2S3_TXIRQOUT       = 406U,     /* I2S3_TXIRQOUT */
    INT_SRC_I2S3_RXIRQOUT       = 407U,     /* I2S3_RXIRQOUT */
    INT_SRC_I2S3_ERRIRQOUT      = 408U,     /* I2S3_ERRIRQOUT */
    INT_SRC_I2S4_TXIRQOUT       = 409U,     /* I2S4_TXIRQOUT */
    INT_SRC_I2S4_RXIRQOUT       = 410U,     /* I2S4_RXIRQOUT */
    INT_SRC_I2S4_ERRIRQOUT      = 411U,     /* I2S4_ERRIRQOUT */

    /* COMPARATOR */
    INT_SRC_CMP1                = 416U,     /* ACMP1 */
    INT_SRC_CMP2                = 417U,     /* ACMP2 */
    INT_SRC_CMP3                = 418U,     /* ACMP3 */

    /* I2C */
    INT_SRC_I2C1_RXI            = 420U,     /* I2C1_RXI */
    INT_SRC_I2C1_TXI            = 421U,     /* I2C1_TXI */
    INT_SRC_I2C1_TEI            = 422U,     /* I2C1_TEI */
    INT_SRC_I2C1_EEI            = 423U,     /* I2C1_EEI */
    INT_SRC_I2C2_RXI            = 424U,     /* I2C2_RXI */
    INT_SRC_I2C2_TXI            = 425U,     /* I2C2_TXI */
    INT_SRC_I2C2_TEI            = 426U,     /* I2C2_TEI */
    INT_SRC_I2C2_EEI            = 427U,     /* I2C2_EEI */
    INT_SRC_I2C3_RXI            = 428U,     /* I2C3_RXI */
    INT_SRC_I2C3_TXI            = 429U,     /* I2C3_TXI */
    INT_SRC_I2C3_TEI            = 430U,     /* I2C3_TEI */
    INT_SRC_I2C3_EEI            = 431U,     /* I2C3_EEI */

    /* LVD */
    INT_SRC_LVD1                = 433U,     /* LVD1 */
    INT_SRC_LVD2                = 434U,     /* LVD2 */

    /* Temp. sensor */
    INT_SRC_OTS                 = 435U,     /* OTS */

    /* FCM */
    INT_SRC_FCMFERRI            = 436U,     /* FCMFERRI */
    INT_SRC_FCMMENDI            = 437U,     /* FCMMENDI */
    INT_SRC_FCMCOVFI            = 438U,     /* FCMCOVFI */

    /* WDT */
    INT_SRC_WDT_REFUDF          = 439U,     /* WDT_REFUDF */

    /* ADC */
    INT_SRC_ADC1_EOCA           = 448U,     /* ADC1_EOCA   */
    INT_SRC_ADC1_EOCB           = 449U,     /* ADC1_EOCB   */
    INT_SRC_ADC1_CHCMP          = 450U,     /* ADC1_CHCMP  */
    INT_SRC_ADC1_SEQCMP         = 451U,     /* ADC1_SEQCMP */
    INT_SRC_ADC2_EOCA           = 452U,     /* ADC2_EOCA   */
    INT_SRC_ADC2_EOCB           = 453U,     /* ADC2_EOCB   */
    INT_SRC_ADC2_CHCMP          = 454U,     /* ADC2_CHCMP  */
    INT_SRC_ADC2_SEQCMP         = 455U,     /* ADC2_SEQCMP */

    /* TRNG */
    INT_SRC_TRNG_END            = 456U,     /* TRNG_END */

    /* SDIOC */
    INT_SRC_SDIOC1_SD           = 482U,     /* SDIOC1_SD */
    INT_SRC_SDIOC2_SD           = 485U,     /* SDIOC2_SD */

    /* CAN */
    INT_SRC_CAN_INT             = 486U,     /* CAN_INT */

    INT_SRC_MAX                 = 511U,
} en_int_src_t;

/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
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
    uint8_t RESERVED2[8];
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
    uint8_t RESERVED3[7];
    __IO uint16_t CHMUXR0;
    __IO uint16_t CHMUXR1;
    __IO uint16_t CHMUXR2;
    __IO uint16_t CHMUXR3;
    uint8_t RESERVED4[6];
    __IO uint8_t  ISR;
    __IO uint8_t  ICR;
    uint8_t RESERVED5[4];
    __IO uint16_t SYNCCR;
    uint8_t RESERVED6[2];
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
    uint8_t RESERVED7[46];
    __IO uint16_t AWDCR;
    uint8_t RESERVED8[2];
    __IO uint16_t AWDDR0;
    __IO uint16_t AWDDR1;
    uint8_t RESERVED9[4];
    __IO uint32_t AWDCHSR;
    __IO uint32_t AWDSR;
    uint8_t RESERVED10[12];
    __IO uint16_t PGACR;
    __IO uint16_t PGAGSR;
    uint8_t RESERVED11[8];
    __IO uint16_t PGAINSR0;
    __IO uint16_t PGAINSR1;
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
    __IO uint32_t DMA2_TRGSEL0;
    __IO uint32_t DMA2_TRGSEL1;
    __IO uint32_t DMA2_TRGSEL2;
    __IO uint32_t DMA2_TRGSEL3;
    __IO uint32_t DMA_TRGSELRC;
    __IO uint32_t TMR6_HTSSR0;
    __IO uint32_t TMR6_HTSSR1;
    __IO uint32_t TMR0_HTSSR;
    __IO uint32_t PEVNTTRGSR12;
    __IO uint32_t PEVNTTRGSR34;
    __IO uint32_t TMRA_HTSSR0;
    __IO uint32_t TMRA_HTSSR1;
    __IO uint32_t OTS_TRG;
    __IO uint32_t ADC1_ITRGSELR0;
    __IO uint32_t ADC1_ITRGSELR1;
    __IO uint32_t ADC2_ITRGSELR0;
    __IO uint32_t ADC2_ITRGSELR1;
    __IO uint32_t COMTRG1;
    __IO uint32_t COMTRG2;
    uint8_t RESERVED0[144];
    __IO uint32_t PEVNTDIRR1;
    __I  uint32_t PEVNTIDR1;
    __IO uint32_t PEVNTODR1;
    __IO uint32_t PEVNTORR1;
    __IO uint32_t PEVNTOSR1;
    __IO uint32_t PEVNTRISR1;
    __IO uint32_t PEVNTFAL1;
    __IO uint32_t PEVNTDIRR2;
    __I  uint32_t PEVNTIDR2;
    __IO uint32_t PEVNTODR2;
    __IO uint32_t PEVNTORR2;
    __IO uint32_t PEVNTOSR2;
    __IO uint32_t PEVNTRISR2;
    __IO uint32_t PEVNTFAL2;
    __IO uint32_t PEVNTDIRR3;
    __I  uint32_t PEVNTIDR3;
    __IO uint32_t PEVNTODR3;
    __IO uint32_t PEVNTORR3;
    __IO uint32_t PEVNTOSR3;
    __IO uint32_t PEVNTRISR3;
    __IO uint32_t PEVNTFAL3;
    __IO uint32_t PEVNTDIRR4;
    __I  uint32_t PEVNTIDR4;
    __IO uint32_t PEVNTODR4;
    __IO uint32_t PEVNTORR4;
    __IO uint32_t PEVNTOSR4;
    __IO uint32_t PEVNTRISR4;
    __IO uint32_t PEVNTFAL4;
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
    uint8_t RESERVED2[4];
    __I  uint8_t  EALCAP;
    uint8_t RESERVED3[1];
    __IO uint8_t  RECNT;
    __IO uint8_t  TECNT;
    __IO uint8_t  ACFCTRL;
    uint8_t RESERVED4[1];
    __IO uint8_t  ACFEN;
    uint8_t RESERVED5[1];
    __IO uint32_t ACF;
    uint8_t RESERVED6[2];
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
    __IO uint16_t CTRL;
    __IO uint16_t VLTSEL;
    __I  uint16_t OUTMON;
    __IO uint16_t CVSSTB;
    __IO uint16_t CVSPRD;
} CM_CMP_TypeDef;

/**
 * @brief CMPCR
 */
typedef struct {
    uint8_t RESERVED0[256];
    __IO uint16_t DADR1;
    __IO uint16_t DADR2;
    uint8_t RESERVED1[4];
    __IO uint16_t DACR;
    uint8_t RESERVED2[2];
    __IO uint16_t RVADC;
} CM_CMPCR_TypeDef;

/**
 * @brief CMU
 */
typedef struct {
    uint8_t RESERVED0[16];
    __IO uint16_t PERICKSEL;
    __IO uint16_t I2SCKSEL;
    uint8_t RESERVED1[12];
    __IO uint32_t SCFGR;
    __IO uint8_t  USBCKCFGR;
    uint8_t RESERVED2[1];
    __IO uint8_t  CKSWR;
    uint8_t RESERVED3[3];
    __IO uint8_t  PLLCR;
    uint8_t RESERVED4[3];
    __IO uint8_t  UPLLCR;
    uint8_t RESERVED5[3];
    __IO uint8_t  XTALCR;
    uint8_t RESERVED6[3];
    __IO uint8_t  HRCCR;
    uint8_t RESERVED7[1];
    __IO uint8_t  MRCCR;
    uint8_t RESERVED8[3];
    __IO uint8_t  OSCSTBSR;
    __IO uint8_t  MCOCFGR1;
    __IO uint8_t  MCOCFGR2;
    __IO uint8_t  TPIUCKCFGR;
    __IO uint8_t  XTALSTDCR;
    __IO uint8_t  XTALSTDSR;
    uint8_t RESERVED9[31];
    __IO uint8_t  MRCTRM;
    __IO uint8_t  HRCTRM;
    uint8_t RESERVED10[63];
    __IO uint8_t  XTALSTBCR;
    uint8_t RESERVED11[93];
    __IO uint32_t PLLCFGR;
    __IO uint32_t UPLLCFGR;
    uint8_t RESERVED12[776];
    __IO uint8_t  XTALCFGR;
    uint8_t RESERVED13[15];
    __IO uint8_t  XTAL32CR;
    __IO uint8_t  XTAL32CFGR;
    uint8_t RESERVED14[3];
    __IO uint8_t  XTAL32NFR;
    uint8_t RESERVED15[1];
    __IO uint8_t  LRCCR;
    uint8_t RESERVED16[1];
    __IO uint8_t  LRCTRM;
} CM_CMU_TypeDef;

/**
 * @brief CRC
 */
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t RESLT;
    uint8_t RESERVED0[4];
    __I  uint32_t FLG;
    uint8_t RESERVED1[112];
    __I  uint32_t DAT0;
    __I  uint32_t DAT1;
    __I  uint32_t DAT2;
    __I  uint32_t DAT3;
    __I  uint32_t DAT4;
    __I  uint32_t DAT5;
    __I  uint32_t DAT6;
    __I  uint32_t DAT7;
    __I  uint32_t DAT8;
    __I  uint32_t DAT9;
    __I  uint32_t DAT10;
    __I  uint32_t DAT11;
    __I  uint32_t DAT12;
    __I  uint32_t DAT13;
    __I  uint32_t DAT14;
    __I  uint32_t DAT15;
    __I  uint32_t DAT16;
    __I  uint32_t DAT17;
    __I  uint32_t DAT18;
    __I  uint32_t DAT19;
    __I  uint32_t DAT20;
    __I  uint32_t DAT21;
    __I  uint32_t DAT22;
    __I  uint32_t DAT23;
    __I  uint32_t DAT24;
    __I  uint32_t DAT25;
    __I  uint32_t DAT26;
    __I  uint32_t DAT27;
    __I  uint32_t DAT28;
    __I  uint32_t DAT29;
    __I  uint32_t DAT30;
    __I  uint32_t DAT31;
} CM_CRC_TypeDef;

/**
 * @brief DBGC
 */
typedef struct {
    __IO uint32_t AUTHID0;
    __IO uint32_t AUTHID1;
    __IO uint32_t AUTHID2;
    __IO uint32_t RESV0;
    __IO uint32_t MCUSTAT;
    __IO uint32_t MCUCTL;
    __IO uint32_t FMCCTL;
    __IO uint32_t MCUDBGSTAT;
    __IO uint32_t MCUSTPCTL;
    __IO uint32_t MCUTRACECTL;
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
    __O  uint32_t FLAGCLR;
    __IO uint32_t INTSEL;
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
    __O  uint32_t INTCLR0;
    __O  uint32_t INTCLR1;
    __IO uint32_t CHEN;
    __I  uint32_t REQSTAT;
    __I  uint32_t CHSTAT;
    uint8_t RESERVED0[4];
    __IO uint32_t RCFGCTL;
    uint8_t RESERVED1[16];
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
    uint8_t RESERVED2[8];
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
    uint8_t RESERVED3[8];
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
    uint8_t RESERVED4[8];
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
} CM_DMA_TypeDef;

/**
 * @brief EFM
 */
typedef struct {
    __IO uint32_t FAPRT;
    __IO uint32_t FSTP;
    __IO uint32_t FRMC;
    __IO uint32_t FWMC;
    __I  uint32_t FSR;
    __IO uint32_t FSCLR;
    __IO uint32_t FITE;
    __I  uint32_t FSWP;
    __IO uint32_t FPMTSW;
    __IO uint32_t FPMTEW;
    uint8_t RESERVED0[40];
    __I  uint32_t UQID0;
    __I  uint32_t UQID1;
    __I  uint32_t UQID2;
    uint8_t RESERVED1[164];
    __IO uint32_t MMF_REMPRT;
    __IO uint32_t MMF_REMCR0;
    __IO uint32_t MMF_REMCR1;
} CM_EFM_TypeDef;

/**
 * @brief EMB
 */
typedef struct {
    __IO uint32_t CTL;
    __IO uint32_t PWMLV;
    __IO uint32_t SOE;
    __I  uint32_t STAT;
    __O  uint32_t STATCLR;
    __IO uint32_t INTEN;
} CM_EMB_TypeDef;

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
 * @brief GPIO
 */
typedef struct {
    __I  uint16_t PIDRA;
    uint8_t RESERVED0[2];
    __IO uint16_t PODRA;
    __IO uint16_t POERA;
    __IO uint16_t POSRA;
    __IO uint16_t PORRA;
    __IO uint16_t POTRA;
    uint8_t RESERVED1[2];
    __I  uint16_t PIDRB;
    uint8_t RESERVED2[2];
    __IO uint16_t PODRB;
    __IO uint16_t POERB;
    __IO uint16_t POSRB;
    __IO uint16_t PORRB;
    __IO uint16_t POTRB;
    uint8_t RESERVED3[2];
    __I  uint16_t PIDRC;
    uint8_t RESERVED4[2];
    __IO uint16_t PODRC;
    __IO uint16_t POERC;
    __IO uint16_t POSRC;
    __IO uint16_t PORRC;
    __IO uint16_t POTRC;
    uint8_t RESERVED5[2];
    __I  uint16_t PIDRD;
    uint8_t RESERVED6[2];
    __IO uint16_t PODRD;
    __IO uint16_t POERD;
    __IO uint16_t POSRD;
    __IO uint16_t PORRD;
    __IO uint16_t POTRD;
    uint8_t RESERVED7[2];
    __I  uint16_t PIDRE;
    uint8_t RESERVED8[2];
    __IO uint16_t PODRE;
    __IO uint16_t POERE;
    __IO uint16_t POSRE;
    __IO uint16_t PORRE;
    __IO uint16_t POTRE;
    uint8_t RESERVED9[2];
    __I  uint16_t PIDRH;
    uint8_t RESERVED10[2];
    __IO uint16_t PODRH;
    __IO uint16_t POERH;
    __IO uint16_t POSRH;
    __IO uint16_t PORRH;
    __IO uint16_t POTRH;
    uint8_t RESERVED11[918];
    __IO uint16_t PSPCR;
    uint8_t RESERVED12[2];
    __IO uint16_t PCCR;
    __IO uint16_t PINAER;
    __IO uint16_t PWPR;
    uint8_t RESERVED13[2];
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
    __IO uint16_t PCRH0;
    __IO uint16_t PFSRH0;
    __IO uint16_t PCRH1;
    __IO uint16_t PFSRH1;
    __IO uint16_t PCRH2;
    __IO uint16_t PFSRH2;
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
    __I  uint32_t ICG2;
    __I  uint32_t ICG3;
    __I  uint32_t ICG4;
    __I  uint32_t ICG5;
    __I  uint32_t ICG6;
    __I  uint32_t ICG7;
} CM_ICG_TypeDef;

/**
 * @brief INTC
 */
typedef struct {
    __IO uint32_t NMICR;
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
    __IO uint32_t EIRQFR;
    __IO uint32_t EIRQCFR;
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
    __IO uint32_t RGCR0;
    __IO uint32_t RGCR1;
    __IO uint32_t RGCR2;
    __IO uint32_t RGCR3;
    __IO uint32_t RGCR4;
    __IO uint32_t RGCR5;
    __IO uint32_t RGCR6;
    __IO uint32_t RGCR7;
    __IO uint32_t RGCR8;
    __IO uint32_t RGCR9;
    __IO uint32_t RGCR10;
    __IO uint32_t RGCR11;
    __IO uint32_t RGCR12;
    __IO uint32_t RGCR13;
    __IO uint32_t RGCR14;
    __IO uint32_t RGCR15;
    __IO uint32_t CR;
    __I  uint32_t SR;
    __O  uint32_t ECLR;
    __IO uint32_t WP;
    uint8_t RESERVED0[16268];
    __IO uint32_t IPPR;
} CM_MPU_TypeDef;

/**
 * @brief OTS
 */
typedef struct {
    __IO uint16_t CTL;
    __IO uint16_t DR1;
    __IO uint16_t DR2;
    __IO uint16_t ECR;
    __I  uint32_t LPR;
} CM_OTS_TypeDef;

/**
 * @brief PERIC
 */
typedef struct {
    __IO uint32_t USBFS_SYCTLREG;
    __IO uint32_t SDIOC_SYCTLREG;
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
    uint8_t RESERVED0[17388];
    __IO uint16_t WKTCR;
    uint8_t RESERVED1[31754];
    __IO uint16_t STPMCR;
    uint8_t RESERVED2[6];
    __IO uint32_t RAMPC0;
    __IO uint16_t RAMOPM;
    uint8_t RESERVED3[198];
    __IO uint8_t  PVDICR;
    __IO uint8_t  PVDDSR;
    uint8_t RESERVED4[796];
    __IO uint16_t FPRC;
    __IO uint8_t  PWRC0;
    __IO uint8_t  PWRC1;
    __IO uint8_t  PWRC2;
    __IO uint8_t  PWRC3;
    __IO uint8_t  PDWKE0;
    __IO uint8_t  PDWKE1;
    __IO uint8_t  PDWKE2;
    __IO uint8_t  PDWKES;
    __IO uint8_t  PDWKF0;
    __IO uint8_t  PDWKF1;
    __IO uint8_t  PWCMR;
    uint8_t RESERVED5[4];
    __IO uint8_t  MDSWCR;
    uint8_t RESERVED6[2];
    __IO uint8_t  PVDCR0;
    __IO uint8_t  PVDCR1;
    __IO uint8_t  PVDFCR;
    __IO uint8_t  PVDLCR;
    uint8_t RESERVED7[21];
    __IO uint8_t  XTAL32CS;
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
    __IO uint16_t RSTF0;
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
    uint8_t RESERVED0[4];
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
    uint8_t RESERVED23[16];
    __IO uint16_t ECSR;
} CM_TMR4_TypeDef;

/**
 * @brief TMR4CR
 */
typedef struct {
    __IO uint32_t ECER1;
    __IO uint32_t ECER2;
    __IO uint32_t ECER3;
} CM_TMR4CR_TypeDef;

/**
 * @brief TMR6
 */
typedef struct {
    __IO uint32_t CNTER;
    __IO uint32_t PERAR;
    __IO uint32_t PERBR;
    __IO uint32_t PERCR;
    __IO uint32_t GCMAR;
    __IO uint32_t GCMBR;
    __IO uint32_t GCMCR;
    __IO uint32_t GCMDR;
    __IO uint32_t GCMER;
    __IO uint32_t GCMFR;
    __IO uint32_t SCMAR;
    __IO uint32_t SCMBR;
    __IO uint32_t SCMCR;
    __IO uint32_t SCMDR;
    __IO uint32_t SCMER;
    __IO uint32_t SCMFR;
    __IO uint32_t DTUAR;
    __IO uint32_t DTDAR;
    __IO uint32_t DTUBR;
    __IO uint32_t DTDBR;
    __IO uint32_t GCONR;
    __IO uint32_t ICONR;
    __IO uint32_t PCONR;
    __IO uint32_t BCONR;
    __IO uint32_t DCONR;
    uint8_t RESERVED0[4];
    __IO uint32_t FCONR;
    __IO uint32_t VPERR;
    __IO uint32_t STFLR;
    __IO uint32_t HSTAR;
    __IO uint32_t HSTPR;
    __IO uint32_t HCLRR;
    __IO uint32_t HCPAR;
    __IO uint32_t HCPBR;
    __IO uint32_t HCUPR;
    __IO uint32_t HCDOR;
} CM_TMR6_TypeDef;

/**
 * @brief TMR6CR
 */
typedef struct {
    uint8_t RESERVED0[1012];
    __IO uint32_t SSTAR;
    __IO uint32_t SSTPR;
    __IO uint32_t SCLRR;
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
    uint8_t RESERVED5[2];
    __IO uint16_t CMPAR5;
    uint8_t RESERVED6[2];
    __IO uint16_t CMPAR6;
    uint8_t RESERVED7[2];
    __IO uint16_t CMPAR7;
    uint8_t RESERVED8[2];
    __IO uint16_t CMPAR8;
    uint8_t RESERVED9[34];
    __IO uint16_t BCSTR;
    uint8_t RESERVED10[2];
    __IO uint16_t HCONR;
    uint8_t RESERVED11[2];
    __IO uint16_t HCUPR;
    uint8_t RESERVED12[2];
    __IO uint16_t HCDOR;
    uint8_t RESERVED13[2];
    __IO uint16_t ICONR;
    uint8_t RESERVED14[2];
    __IO uint16_t ECONR;
    uint8_t RESERVED15[2];
    __IO uint16_t FCONR;
    uint8_t RESERVED16[2];
    __IO uint16_t STFLR;
    uint8_t RESERVED17[34];
    __IO uint16_t BCONR1;
    uint8_t RESERVED18[6];
    __IO uint16_t BCONR2;
    uint8_t RESERVED19[6];
    __IO uint16_t BCONR3;
    uint8_t RESERVED20[6];
    __IO uint16_t BCONR4;
    uint8_t RESERVED21[38];
    __IO uint16_t CCONR1;
    uint8_t RESERVED22[2];
    __IO uint16_t CCONR2;
    uint8_t RESERVED23[2];
    __IO uint16_t CCONR3;
    uint8_t RESERVED24[2];
    __IO uint16_t CCONR4;
    uint8_t RESERVED25[2];
    __IO uint16_t CCONR5;
    uint8_t RESERVED26[2];
    __IO uint16_t CCONR6;
    uint8_t RESERVED27[2];
    __IO uint16_t CCONR7;
    uint8_t RESERVED28[2];
    __IO uint16_t CCONR8;
    uint8_t RESERVED29[34];
    __IO uint16_t PCONR1;
    uint8_t RESERVED30[2];
    __IO uint16_t PCONR2;
    uint8_t RESERVED31[2];
    __IO uint16_t PCONR3;
    uint8_t RESERVED32[2];
    __IO uint16_t PCONR4;
    uint8_t RESERVED33[2];
    __IO uint16_t PCONR5;
    uint8_t RESERVED34[2];
    __IO uint16_t PCONR6;
    uint8_t RESERVED35[2];
    __IO uint16_t PCONR7;
    uint8_t RESERVED36[2];
    __IO uint16_t PCONR8;
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
    __IO uint32_t DR;
    __IO uint32_t BRR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t PR;
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
    __I  uint32_t GINTSTS;
    __IO uint32_t GINTMSK;
    __I  uint32_t GRXSTSR;
    __I  uint32_t GRXSTSP;
    __IO uint32_t GRXFSIZ;
    __IO uint32_t HNPTXFSIZ;
    __I  uint32_t HNPTXSTS;
    uint8_t RESERVED1[12];
    __IO uint32_t CID;
    uint8_t RESERVED2[192];
    __IO uint32_t HPTXFSIZ;
    __IO uint32_t DIEPTXF1;
    __IO uint32_t DIEPTXF2;
    __IO uint32_t DIEPTXF3;
    __IO uint32_t DIEPTXF4;
    __IO uint32_t DIEPTXF5;
    uint8_t RESERVED3[744];
    __IO uint32_t HCFG;
    __IO uint32_t HFIR;
    __I  uint32_t HFNUM;
    uint8_t RESERVED4[4];
    __I  uint32_t HPTXSTS;
    __I  uint32_t HAINT;
    __IO uint32_t HAINTMSK;
    uint8_t RESERVED5[36];
    __I  uint32_t HPRT;
    uint8_t RESERVED6[188];
    __IO uint32_t HCCHAR0;
    uint8_t RESERVED7[4];
    __IO uint32_t HCINT0;
    __IO uint32_t HCINTMSK0;
    __IO uint32_t HCTSIZ0;
    __IO uint32_t HCDMA0;
    uint8_t RESERVED8[8];
    __IO uint32_t HCCHAR1;
    uint8_t RESERVED9[4];
    __IO uint32_t HCINT1;
    __IO uint32_t HCINTMSK1;
    __IO uint32_t HCTSIZ1;
    __IO uint32_t HCDMA1;
    uint8_t RESERVED10[8];
    __IO uint32_t HCCHAR2;
    uint8_t RESERVED11[4];
    __IO uint32_t HCINT2;
    __IO uint32_t HCINTMSK2;
    __IO uint32_t HCTSIZ2;
    __IO uint32_t HCDMA2;
    uint8_t RESERVED12[8];
    __IO uint32_t HCCHAR3;
    uint8_t RESERVED13[4];
    __IO uint32_t HCINT3;
    __IO uint32_t HCINTMSK3;
    __IO uint32_t HCTSIZ3;
    __IO uint32_t HCDMA3;
    uint8_t RESERVED14[8];
    __IO uint32_t HCCHAR4;
    uint8_t RESERVED15[4];
    __IO uint32_t HCINT4;
    __IO uint32_t HCINTMSK4;
    __IO uint32_t HCTSIZ4;
    __IO uint32_t HCDMA4;
    uint8_t RESERVED16[8];
    __IO uint32_t HCCHAR5;
    uint8_t RESERVED17[4];
    __IO uint32_t HCINT5;
    __IO uint32_t HCINTMSK5;
    __IO uint32_t HCTSIZ5;
    __IO uint32_t HCDMA5;
    uint8_t RESERVED18[8];
    __IO uint32_t HCCHAR6;
    uint8_t RESERVED19[4];
    __IO uint32_t HCINT6;
    __IO uint32_t HCINTMSK6;
    __IO uint32_t HCTSIZ6;
    __IO uint32_t HCDMA6;
    uint8_t RESERVED20[8];
    __IO uint32_t HCCHAR7;
    uint8_t RESERVED21[4];
    __IO uint32_t HCINT7;
    __IO uint32_t HCINTMSK7;
    __IO uint32_t HCTSIZ7;
    __IO uint32_t HCDMA7;
    uint8_t RESERVED22[8];
    __IO uint32_t HCCHAR8;
    uint8_t RESERVED23[4];
    __IO uint32_t HCINT8;
    __IO uint32_t HCINTMSK8;
    __IO uint32_t HCTSIZ8;
    __IO uint32_t HCDMA8;
    uint8_t RESERVED24[8];
    __IO uint32_t HCCHAR9;
    uint8_t RESERVED25[4];
    __IO uint32_t HCINT9;
    __IO uint32_t HCINTMSK9;
    __IO uint32_t HCTSIZ9;
    __IO uint32_t HCDMA9;
    uint8_t RESERVED26[8];
    __IO uint32_t HCCHAR10;
    uint8_t RESERVED27[4];
    __IO uint32_t HCINT10;
    __IO uint32_t HCINTMSK10;
    __IO uint32_t HCTSIZ10;
    __IO uint32_t HCDMA10;
    uint8_t RESERVED28[8];
    __IO uint32_t HCCHAR11;
    uint8_t RESERVED29[4];
    __IO uint32_t HCINT11;
    __IO uint32_t HCINTMSK11;
    __IO uint32_t HCTSIZ11;
    __IO uint32_t HCDMA11;
    uint8_t RESERVED30[392];
    __IO uint32_t DCFG;
    __IO uint32_t DCTL;
    __I  uint32_t DSTS;
    uint8_t RESERVED31[4];
    __IO uint32_t DIEPMSK;
    __IO uint32_t DOEPMSK;
    __IO uint32_t DAINT;
    __IO uint32_t DAINTMSK;
    uint8_t RESERVED32[20];
    __IO uint32_t DIEPEMPMSK;
    uint8_t RESERVED33[200];
    __IO uint32_t DIEPCTL0;
    uint8_t RESERVED34[4];
    __IO uint32_t DIEPINT0;
    uint8_t RESERVED35[4];
    __IO uint32_t DIEPTSIZ0;
    __IO uint32_t DIEPDMA0;
    __I  uint32_t DTXFSTS0;
    uint8_t RESERVED36[4];
    __IO uint32_t DIEPCTL1;
    uint8_t RESERVED37[4];
    __IO uint32_t DIEPINT1;
    uint8_t RESERVED38[4];
    __IO uint32_t DIEPTSIZ1;
    __IO uint32_t DIEPDMA1;
    __I  uint32_t DTXFSTS1;
    uint8_t RESERVED39[4];
    __IO uint32_t DIEPCTL2;
    uint8_t RESERVED40[4];
    __IO uint32_t DIEPINT2;
    uint8_t RESERVED41[4];
    __IO uint32_t DIEPTSIZ2;
    __IO uint32_t DIEPDMA2;
    __I  uint32_t DTXFSTS2;
    uint8_t RESERVED42[4];
    __IO uint32_t DIEPCTL3;
    uint8_t RESERVED43[4];
    __IO uint32_t DIEPINT3;
    uint8_t RESERVED44[4];
    __IO uint32_t DIEPTSIZ3;
    __IO uint32_t DIEPDMA3;
    __I  uint32_t DTXFSTS3;
    uint8_t RESERVED45[4];
    __IO uint32_t DIEPCTL4;
    uint8_t RESERVED46[4];
    __IO uint32_t DIEPINT4;
    uint8_t RESERVED47[4];
    __IO uint32_t DIEPTSIZ4;
    __IO uint32_t DIEPDMA4;
    __I  uint32_t DTXFSTS4;
    uint8_t RESERVED48[4];
    __IO uint32_t DIEPCTL5;
    uint8_t RESERVED49[4];
    __IO uint32_t DIEPINT5;
    uint8_t RESERVED50[4];
    __IO uint32_t DIEPTSIZ5;
    __IO uint32_t DIEPDMA5;
    __I  uint32_t DTXFSTS5;
    uint8_t RESERVED51[324];
    __IO uint32_t DOEPCTL0;
    uint8_t RESERVED52[4];
    __IO uint32_t DOEPINT0;
    uint8_t RESERVED53[4];
    __IO uint32_t DOEPTSIZ0;
    __IO uint32_t DOEPDMA0;
    uint8_t RESERVED54[8];
    __IO uint32_t DOEPCTL1;
    uint8_t RESERVED55[4];
    __IO uint32_t DOEPINT1;
    uint8_t RESERVED56[4];
    __IO uint32_t DOEPTSIZ1;
    __IO uint32_t DOEPDMA1;
    uint8_t RESERVED57[8];
    __IO uint32_t DOEPCTL2;
    uint8_t RESERVED58[4];
    __IO uint32_t DOEPINT2;
    uint8_t RESERVED59[4];
    __IO uint32_t DOEPTSIZ2;
    __IO uint32_t DOEPDMA2;
    uint8_t RESERVED60[8];
    __IO uint32_t DOEPCTL3;
    uint8_t RESERVED61[4];
    __IO uint32_t DOEPINT3;
    uint8_t RESERVED62[4];
    __IO uint32_t DOEPTSIZ3;
    __IO uint32_t DOEPDMA3;
    uint8_t RESERVED63[8];
    __IO uint32_t DOEPCTL4;
    uint8_t RESERVED64[4];
    __IO uint32_t DOEPINT4;
    uint8_t RESERVED65[4];
    __IO uint32_t DOEPTSIZ4;
    __IO uint32_t DOEPDMA4;
    uint8_t RESERVED66[8];
    __IO uint32_t DOEPCTL5;
    uint8_t RESERVED67[4];
    __IO uint32_t DOEPINT5;
    uint8_t RESERVED68[4];
    __IO uint32_t DOEPTSIZ5;
    __IO uint32_t DOEPDMA5;
    uint8_t RESERVED69[584];
    __IO uint32_t GCCTL;
} CM_USBFS_TypeDef;

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
#define SRAM_BASE                            (0x1FFF8000UL)   /*!< SRAM base address in the alias region */
#define QSPI_BASE                            (0x98000000UL)   /*!< QSPI base address in the alias region */

/******************************************************************************/
/*           Device Specific Peripheral Base Address                          */
/******************************************************************************/
#define CM_ADC1_BASE                         (0x40040000UL)
#define CM_ADC2_BASE                         (0x40040400UL)
#define CM_AES_BASE                          (0x40008000UL)
#define CM_AOS_BASE                          (0x40010800UL)
#define CM_CAN_BASE                          (0x40070400UL)
#define CM_CMP1_BASE                         (0x4004A000UL)
#define CM_CMP2_BASE                         (0x4004A010UL)
#define CM_CMP3_BASE                         (0x4004A020UL)
#define CM_CMPCR_BASE                        (0x4004A000UL)
#define CM_CMU_BASE                          (0x40054000UL)
#define CM_CRC_BASE                          (0x40008C00UL)
#define CM_DBGC_BASE                         (0xE0042000UL)
#define CM_DCU1_BASE                         (0x40052000UL)
#define CM_DCU2_BASE                         (0x40052400UL)
#define CM_DCU3_BASE                         (0x40052800UL)
#define CM_DCU4_BASE                         (0x40052C00UL)
#define CM_DMA1_BASE                         (0x40053000UL)
#define CM_DMA2_BASE                         (0x40053400UL)
#define CM_EFM_BASE                          (0x40010400UL)
#define CM_EMB0_BASE                         (0x40017C00UL)
#define CM_EMB1_BASE                         (0x40017C20UL)
#define CM_EMB2_BASE                         (0x40017C40UL)
#define CM_EMB3_BASE                         (0x40017C60UL)
#define CM_FCM_BASE                          (0x40048400UL)
#define CM_GPIO_BASE                         (0x40053800UL)
#define CM_HASH_BASE                         (0x40008400UL)
#define CM_I2C1_BASE                         (0x4004E000UL)
#define CM_I2C2_BASE                         (0x4004E400UL)
#define CM_I2C3_BASE                         (0x4004E800UL)
#define CM_I2S1_BASE                         (0x4001E000UL)
#define CM_I2S2_BASE                         (0x4001E400UL)
#define CM_I2S3_BASE                         (0x40022000UL)
#define CM_I2S4_BASE                         (0x40022400UL)
#define CM_ICG_BASE                          (0x00000400UL)
#define CM_INTC_BASE                         (0x40051000UL)
#define CM_KEYSCAN_BASE                      (0x40050C00UL)
#define CM_MPU_BASE                          (0x40050000UL)
#define CM_OTS_BASE                          (0x4004A400UL)
#define CM_PERIC_BASE                        (0x40055400UL)
#define CM_PWC_BASE                          (0x40048000UL)
#define CM_QSPI_BASE                         (0x9C000000UL)
#define CM_RMU_BASE                          (0x400540C0UL)
#define CM_RTC_BASE                          (0x4004C000UL)
#define CM_SDIOC1_BASE                       (0x4006FC00UL)
#define CM_SDIOC2_BASE                       (0x40070000UL)
#define CM_SPI1_BASE                         (0x4001C000UL)
#define CM_SPI2_BASE                         (0x4001C400UL)
#define CM_SPI3_BASE                         (0x40020000UL)
#define CM_SPI4_BASE                         (0x40020400UL)
#define CM_SRAMC_BASE                        (0x40050800UL)
#define CM_SWDT_BASE                         (0x40049400UL)
#define CM_TMR0_1_BASE                       (0x40024000UL)
#define CM_TMR0_2_BASE                       (0x40024400UL)
#define CM_TMR4_1_BASE                       (0x40017000UL)
#define CM_TMR4_2_BASE                       (0x40024800UL)
#define CM_TMR4_3_BASE                       (0x40024C00UL)
#define CM_TMR4CR_BASE                       (0x40055408UL)
#define CM_TMR6_1_BASE                       (0x40018000UL)
#define CM_TMR6_2_BASE                       (0x40018400UL)
#define CM_TMR6_3_BASE                       (0x40018800UL)
#define CM_TMR6CR_BASE                       (0x40018000UL)
#define CM_TMRA_1_BASE                       (0x40015000UL)
#define CM_TMRA_2_BASE                       (0x40015400UL)
#define CM_TMRA_3_BASE                       (0x40015800UL)
#define CM_TMRA_4_BASE                       (0x40015C00UL)
#define CM_TMRA_5_BASE                       (0x40016000UL)
#define CM_TMRA_6_BASE                       (0x40016400UL)
#define CM_TRNG_BASE                         (0x40041000UL)
#define CM_USART1_BASE                       (0x4001D000UL)
#define CM_USART2_BASE                       (0x4001D400UL)
#define CM_USART3_BASE                       (0x40021000UL)
#define CM_USART4_BASE                       (0x40021400UL)
#define CM_USBFS_BASE                        (0x400C0000UL)
#define CM_WDT_BASE                          (0x40049000UL)

/******************************************************************************/
/*           Device Specific Peripheral declaration & memory map              */
/******************************************************************************/
#define CM_ADC1                              ((CM_ADC_TypeDef *)CM_ADC1_BASE)
#define CM_ADC2                              ((CM_ADC_TypeDef *)CM_ADC2_BASE)
#define CM_AES                               ((CM_AES_TypeDef *)CM_AES_BASE)
#define CM_AOS                               ((CM_AOS_TypeDef *)CM_AOS_BASE)
#define CM_CAN                               ((CM_CAN_TypeDef *)CM_CAN_BASE)
#define CM_CMP1                              ((CM_CMP_TypeDef *)CM_CMP1_BASE)
#define CM_CMP2                              ((CM_CMP_TypeDef *)CM_CMP2_BASE)
#define CM_CMP3                              ((CM_CMP_TypeDef *)CM_CMP3_BASE)
#define CM_CMPCR                             ((CM_CMPCR_TypeDef *)CM_CMPCR_BASE)
#define CM_CMU                               ((CM_CMU_TypeDef *)CM_CMU_BASE)
#define CM_CRC                               ((CM_CRC_TypeDef *)CM_CRC_BASE)
#define CM_DBGC                              ((CM_DBGC_TypeDef *)CM_DBGC_BASE)
#define CM_DCU1                              ((CM_DCU_TypeDef *)CM_DCU1_BASE)
#define CM_DCU2                              ((CM_DCU_TypeDef *)CM_DCU2_BASE)
#define CM_DCU3                              ((CM_DCU_TypeDef *)CM_DCU3_BASE)
#define CM_DCU4                              ((CM_DCU_TypeDef *)CM_DCU4_BASE)
#define CM_DMA1                              ((CM_DMA_TypeDef *)CM_DMA1_BASE)
#define CM_DMA2                              ((CM_DMA_TypeDef *)CM_DMA2_BASE)
#define CM_EFM                               ((CM_EFM_TypeDef *)CM_EFM_BASE)
#define CM_EMB0                              ((CM_EMB_TypeDef *)CM_EMB0_BASE)
#define CM_EMB1                              ((CM_EMB_TypeDef *)CM_EMB1_BASE)
#define CM_EMB2                              ((CM_EMB_TypeDef *)CM_EMB2_BASE)
#define CM_EMB3                              ((CM_EMB_TypeDef *)CM_EMB3_BASE)
#define CM_FCM                               ((CM_FCM_TypeDef *)CM_FCM_BASE)
#define CM_GPIO                              ((CM_GPIO_TypeDef *)CM_GPIO_BASE)
#define CM_HASH                              ((CM_HASH_TypeDef *)CM_HASH_BASE)
#define CM_I2C1                              ((CM_I2C_TypeDef *)CM_I2C1_BASE)
#define CM_I2C2                              ((CM_I2C_TypeDef *)CM_I2C2_BASE)
#define CM_I2C3                              ((CM_I2C_TypeDef *)CM_I2C3_BASE)
#define CM_I2S1                              ((CM_I2S_TypeDef *)CM_I2S1_BASE)
#define CM_I2S2                              ((CM_I2S_TypeDef *)CM_I2S2_BASE)
#define CM_I2S3                              ((CM_I2S_TypeDef *)CM_I2S3_BASE)
#define CM_I2S4                              ((CM_I2S_TypeDef *)CM_I2S4_BASE)
#define CM_ICG                               ((CM_ICG_TypeDef *)CM_ICG_BASE)
#define CM_INTC                              ((CM_INTC_TypeDef *)CM_INTC_BASE)
#define CM_KEYSCAN                           ((CM_KEYSCAN_TypeDef *)CM_KEYSCAN_BASE)
#define CM_MPU                               ((CM_MPU_TypeDef *)CM_MPU_BASE)
#define CM_OTS                               ((CM_OTS_TypeDef *)CM_OTS_BASE)
#define CM_PERIC                             ((CM_PERIC_TypeDef *)CM_PERIC_BASE)
#define CM_PWC                               ((CM_PWC_TypeDef *)CM_PWC_BASE)
#define CM_QSPI                              ((CM_QSPI_TypeDef *)CM_QSPI_BASE)
#define CM_RMU                               ((CM_RMU_TypeDef *)CM_RMU_BASE)
#define CM_RTC                               ((CM_RTC_TypeDef *)CM_RTC_BASE)
#define CM_SDIOC1                            ((CM_SDIOC_TypeDef *)CM_SDIOC1_BASE)
#define CM_SDIOC2                            ((CM_SDIOC_TypeDef *)CM_SDIOC2_BASE)
#define CM_SPI1                              ((CM_SPI_TypeDef *)CM_SPI1_BASE)
#define CM_SPI2                              ((CM_SPI_TypeDef *)CM_SPI2_BASE)
#define CM_SPI3                              ((CM_SPI_TypeDef *)CM_SPI3_BASE)
#define CM_SPI4                              ((CM_SPI_TypeDef *)CM_SPI4_BASE)
#define CM_SRAMC                             ((CM_SRAMC_TypeDef *)CM_SRAMC_BASE)
#define CM_SWDT                              ((CM_SWDT_TypeDef *)CM_SWDT_BASE)
#define CM_TMR0_1                            ((CM_TMR0_TypeDef *)CM_TMR0_1_BASE)
#define CM_TMR0_2                            ((CM_TMR0_TypeDef *)CM_TMR0_2_BASE)
#define CM_TMR4_1                            ((CM_TMR4_TypeDef *)CM_TMR4_1_BASE)
#define CM_TMR4_2                            ((CM_TMR4_TypeDef *)CM_TMR4_2_BASE)
#define CM_TMR4_3                            ((CM_TMR4_TypeDef *)CM_TMR4_3_BASE)
#define CM_TMR4CR                            ((CM_TMR4CR_TypeDef *)CM_TMR4CR_BASE)
#define CM_TMR6_1                            ((CM_TMR6_TypeDef *)CM_TMR6_1_BASE)
#define CM_TMR6_2                            ((CM_TMR6_TypeDef *)CM_TMR6_2_BASE)
#define CM_TMR6_3                            ((CM_TMR6_TypeDef *)CM_TMR6_3_BASE)
#define CM_TMR6CR                            ((CM_TMR6CR_TypeDef *)CM_TMR6CR_BASE)
#define CM_TMRA_1                            ((CM_TMRA_TypeDef *)CM_TMRA_1_BASE)
#define CM_TMRA_2                            ((CM_TMRA_TypeDef *)CM_TMRA_2_BASE)
#define CM_TMRA_3                            ((CM_TMRA_TypeDef *)CM_TMRA_3_BASE)
#define CM_TMRA_4                            ((CM_TMRA_TypeDef *)CM_TMRA_4_BASE)
#define CM_TMRA_5                            ((CM_TMRA_TypeDef *)CM_TMRA_5_BASE)
#define CM_TMRA_6                            ((CM_TMRA_TypeDef *)CM_TMRA_6_BASE)
#define CM_TRNG                              ((CM_TRNG_TypeDef *)CM_TRNG_BASE)
#define CM_USART1                            ((CM_USART_TypeDef *)CM_USART1_BASE)
#define CM_USART2                            ((CM_USART_TypeDef *)CM_USART2_BASE)
#define CM_USART3                            ((CM_USART_TypeDef *)CM_USART3_BASE)
#define CM_USART4                            ((CM_USART_TypeDef *)CM_USART4_BASE)
#define CM_USBFS                             ((CM_USBFS_TypeDef *)CM_USBFS_BASE)
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
#define ADC_CR0_AVCNT_0                                (0x0100U)
#define ADC_CR0_AVCNT_1                                (0x0200U)
#define ADC_CR0_AVCNT_2                                (0x0400U)

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
#define ADC_CHSELRA_CHSELA                             (0x0001FFFFUL)

/*  Bit definition for ADC_CHSELRB register  */
#define ADC_CHSELRB_CHSELB                             (0x0001FFFFUL)

/*  Bit definition for ADC_AVCHSELR register  */
#define ADC_AVCHSELR_AVCHSEL                           (0x0001FFFFUL)

/*  Bit definition for ADC_SSTR0 register  */
#define ADC_SSTR0                                      (0xFFU)

/*  Bit definition for ADC_SSTR1 register  */
#define ADC_SSTR1                                      (0xFFU)

/*  Bit definition for ADC_SSTR2 register  */
#define ADC_SSTR2                                      (0xFFU)

/*  Bit definition for ADC_SSTR3 register  */
#define ADC_SSTR3                                      (0xFFU)

/*  Bit definition for ADC_SSTR4 register  */
#define ADC_SSTR4                                      (0xFFU)

/*  Bit definition for ADC_SSTR5 register  */
#define ADC_SSTR5                                      (0xFFU)

/*  Bit definition for ADC_SSTR6 register  */
#define ADC_SSTR6                                      (0xFFU)

/*  Bit definition for ADC_SSTR7 register  */
#define ADC_SSTR7                                      (0xFFU)

/*  Bit definition for ADC_SSTR8 register  */
#define ADC_SSTR8                                      (0xFFU)

/*  Bit definition for ADC_SSTR9 register  */
#define ADC_SSTR9                                      (0xFFU)

/*  Bit definition for ADC_SSTR10 register  */
#define ADC_SSTR10                                     (0xFFU)

/*  Bit definition for ADC_SSTR11 register  */
#define ADC_SSTR11                                     (0xFFU)

/*  Bit definition for ADC_SSTR12 register  */
#define ADC_SSTR12                                     (0xFFU)

/*  Bit definition for ADC_SSTR13 register  */
#define ADC_SSTR13                                     (0xFFU)

/*  Bit definition for ADC_SSTR14 register  */
#define ADC_SSTR14                                     (0xFFU)

/*  Bit definition for ADC_SSTR15 register  */
#define ADC_SSTR15                                     (0xFFU)

/*  Bit definition for ADC_SSTRL register  */
#define ADC_SSTRL                                      (0xFFU)

/*  Bit definition for ADC_CHMUXR0 register  */
#define ADC_CHMUXR0_CH00MUX_POS                        (0U)
#define ADC_CHMUXR0_CH00MUX                            (0x000FU)
#define ADC_CHMUXR0_CH00MUX_0                          (0x0001U)
#define ADC_CHMUXR0_CH00MUX_1                          (0x0002U)
#define ADC_CHMUXR0_CH00MUX_2                          (0x0004U)
#define ADC_CHMUXR0_CH00MUX_3                          (0x0008U)
#define ADC_CHMUXR0_CH01MUX_POS                        (4U)
#define ADC_CHMUXR0_CH01MUX                            (0x00F0U)
#define ADC_CHMUXR0_CH01MUX_0                          (0x0010U)
#define ADC_CHMUXR0_CH01MUX_1                          (0x0020U)
#define ADC_CHMUXR0_CH01MUX_2                          (0x0040U)
#define ADC_CHMUXR0_CH01MUX_3                          (0x0080U)
#define ADC_CHMUXR0_CH02MUX_POS                        (8U)
#define ADC_CHMUXR0_CH02MUX                            (0x0F00U)
#define ADC_CHMUXR0_CH02MUX_0                          (0x0100U)
#define ADC_CHMUXR0_CH02MUX_1                          (0x0200U)
#define ADC_CHMUXR0_CH02MUX_2                          (0x0400U)
#define ADC_CHMUXR0_CH02MUX_3                          (0x0800U)
#define ADC_CHMUXR0_CH03MUX_POS                        (12U)
#define ADC_CHMUXR0_CH03MUX                            (0xF000U)
#define ADC_CHMUXR0_CH03MUX_0                          (0x1000U)
#define ADC_CHMUXR0_CH03MUX_1                          (0x2000U)
#define ADC_CHMUXR0_CH03MUX_2                          (0x4000U)
#define ADC_CHMUXR0_CH03MUX_3                          (0x8000U)

/*  Bit definition for ADC_CHMUXR1 register  */
#define ADC_CHMUXR1_CH04MUX_POS                        (0U)
#define ADC_CHMUXR1_CH04MUX                            (0x000FU)
#define ADC_CHMUXR1_CH04MUX_0                          (0x0001U)
#define ADC_CHMUXR1_CH04MUX_1                          (0x0002U)
#define ADC_CHMUXR1_CH04MUX_2                          (0x0004U)
#define ADC_CHMUXR1_CH04MUX_3                          (0x0008U)
#define ADC_CHMUXR1_CH05MUX_POS                        (4U)
#define ADC_CHMUXR1_CH05MUX                            (0x00F0U)
#define ADC_CHMUXR1_CH05MUX_0                          (0x0010U)
#define ADC_CHMUXR1_CH05MUX_1                          (0x0020U)
#define ADC_CHMUXR1_CH05MUX_2                          (0x0040U)
#define ADC_CHMUXR1_CH05MUX_3                          (0x0080U)
#define ADC_CHMUXR1_CH06MUX_POS                        (8U)
#define ADC_CHMUXR1_CH06MUX                            (0x0F00U)
#define ADC_CHMUXR1_CH06MUX_0                          (0x0100U)
#define ADC_CHMUXR1_CH06MUX_1                          (0x0200U)
#define ADC_CHMUXR1_CH06MUX_2                          (0x0400U)
#define ADC_CHMUXR1_CH06MUX_3                          (0x0800U)
#define ADC_CHMUXR1_CH07MUX_POS                        (12U)
#define ADC_CHMUXR1_CH07MUX                            (0xF000U)
#define ADC_CHMUXR1_CH07MUX_0                          (0x1000U)
#define ADC_CHMUXR1_CH07MUX_1                          (0x2000U)
#define ADC_CHMUXR1_CH07MUX_2                          (0x4000U)
#define ADC_CHMUXR1_CH07MUX_3                          (0x8000U)

/*  Bit definition for ADC_CHMUXR2 register  */
#define ADC_CHMUXR2_CH08MUX_POS                        (0U)
#define ADC_CHMUXR2_CH08MUX                            (0x000FU)
#define ADC_CHMUXR2_CH08MUX_0                          (0x0001U)
#define ADC_CHMUXR2_CH08MUX_1                          (0x0002U)
#define ADC_CHMUXR2_CH08MUX_2                          (0x0004U)
#define ADC_CHMUXR2_CH08MUX_3                          (0x0008U)
#define ADC_CHMUXR2_CH09MUX_POS                        (4U)
#define ADC_CHMUXR2_CH09MUX                            (0x00F0U)
#define ADC_CHMUXR2_CH09MUX_0                          (0x0010U)
#define ADC_CHMUXR2_CH09MUX_1                          (0x0020U)
#define ADC_CHMUXR2_CH09MUX_2                          (0x0040U)
#define ADC_CHMUXR2_CH09MUX_3                          (0x0080U)
#define ADC_CHMUXR2_CH10MUX_POS                        (8U)
#define ADC_CHMUXR2_CH10MUX                            (0x0F00U)
#define ADC_CHMUXR2_CH10MUX_0                          (0x0100U)
#define ADC_CHMUXR2_CH10MUX_1                          (0x0200U)
#define ADC_CHMUXR2_CH10MUX_2                          (0x0400U)
#define ADC_CHMUXR2_CH10MUX_3                          (0x0800U)
#define ADC_CHMUXR2_CH11MUX_POS                        (12U)
#define ADC_CHMUXR2_CH11MUX                            (0xF000U)
#define ADC_CHMUXR2_CH11MUX_0                          (0x1000U)
#define ADC_CHMUXR2_CH11MUX_1                          (0x2000U)
#define ADC_CHMUXR2_CH11MUX_2                          (0x4000U)
#define ADC_CHMUXR2_CH11MUX_3                          (0x8000U)

/*  Bit definition for ADC_CHMUXR3 register  */
#define ADC_CHMUXR3_CH12MUX_POS                        (0U)
#define ADC_CHMUXR3_CH12MUX                            (0x000FU)
#define ADC_CHMUXR3_CH12MUX_0                          (0x0001U)
#define ADC_CHMUXR3_CH12MUX_1                          (0x0002U)
#define ADC_CHMUXR3_CH12MUX_2                          (0x0004U)
#define ADC_CHMUXR3_CH12MUX_3                          (0x0008U)
#define ADC_CHMUXR3_CH13MUX_POS                        (4U)
#define ADC_CHMUXR3_CH13MUX                            (0x00F0U)
#define ADC_CHMUXR3_CH13MUX_0                          (0x0010U)
#define ADC_CHMUXR3_CH13MUX_1                          (0x0020U)
#define ADC_CHMUXR3_CH13MUX_2                          (0x0040U)
#define ADC_CHMUXR3_CH13MUX_3                          (0x0080U)
#define ADC_CHMUXR3_CH14MUX_POS                        (8U)
#define ADC_CHMUXR3_CH14MUX                            (0x0F00U)
#define ADC_CHMUXR3_CH14MUX_0                          (0x0100U)
#define ADC_CHMUXR3_CH14MUX_1                          (0x0200U)
#define ADC_CHMUXR3_CH14MUX_2                          (0x0400U)
#define ADC_CHMUXR3_CH14MUX_3                          (0x0800U)
#define ADC_CHMUXR3_CH15MUX_POS                        (12U)
#define ADC_CHMUXR3_CH15MUX                            (0xF000U)
#define ADC_CHMUXR3_CH15MUX_0                          (0x1000U)
#define ADC_CHMUXR3_CH15MUX_1                          (0x2000U)
#define ADC_CHMUXR3_CH15MUX_2                          (0x4000U)
#define ADC_CHMUXR3_CH15MUX_3                          (0x8000U)

/*  Bit definition for ADC_ISR register  */
#define ADC_ISR_EOCAF_POS                              (0U)
#define ADC_ISR_EOCAF                                  (0x01U)
#define ADC_ISR_EOCBF_POS                              (1U)
#define ADC_ISR_EOCBF                                  (0x02U)

/*  Bit definition for ADC_ICR register  */
#define ADC_ICR_EOCAIEN_POS                            (0U)
#define ADC_ICR_EOCAIEN                                (0x01U)
#define ADC_ICR_EOCBIEN_POS                            (1U)
#define ADC_ICR_EOCBIEN                                (0x02U)

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
#define ADC_SYNCCR_SYNCDLY_0                           (0x0100U)
#define ADC_SYNCCR_SYNCDLY_1                           (0x0200U)
#define ADC_SYNCCR_SYNCDLY_2                           (0x0400U)
#define ADC_SYNCCR_SYNCDLY_3                           (0x0800U)
#define ADC_SYNCCR_SYNCDLY_4                           (0x1000U)
#define ADC_SYNCCR_SYNCDLY_5                           (0x2000U)
#define ADC_SYNCCR_SYNCDLY_6                           (0x4000U)
#define ADC_SYNCCR_SYNCDLY_7                           (0x8000U)

/*  Bit definition for ADC_DR0 register  */
#define ADC_DR0                                        (0xFFFFU)

/*  Bit definition for ADC_DR1 register  */
#define ADC_DR1                                        (0xFFFFU)

/*  Bit definition for ADC_DR2 register  */
#define ADC_DR2                                        (0xFFFFU)

/*  Bit definition for ADC_DR3 register  */
#define ADC_DR3                                        (0xFFFFU)

/*  Bit definition for ADC_DR4 register  */
#define ADC_DR4                                        (0xFFFFU)

/*  Bit definition for ADC_DR5 register  */
#define ADC_DR5                                        (0xFFFFU)

/*  Bit definition for ADC_DR6 register  */
#define ADC_DR6                                        (0xFFFFU)

/*  Bit definition for ADC_DR7 register  */
#define ADC_DR7                                        (0xFFFFU)

/*  Bit definition for ADC_DR8 register  */
#define ADC_DR8                                        (0xFFFFU)

/*  Bit definition for ADC_DR9 register  */
#define ADC_DR9                                        (0xFFFFU)

/*  Bit definition for ADC_DR10 register  */
#define ADC_DR10                                       (0xFFFFU)

/*  Bit definition for ADC_DR11 register  */
#define ADC_DR11                                       (0xFFFFU)

/*  Bit definition for ADC_DR12 register  */
#define ADC_DR12                                       (0xFFFFU)

/*  Bit definition for ADC_DR13 register  */
#define ADC_DR13                                       (0xFFFFU)

/*  Bit definition for ADC_DR14 register  */
#define ADC_DR14                                       (0xFFFFU)

/*  Bit definition for ADC_DR15 register  */
#define ADC_DR15                                       (0xFFFFU)

/*  Bit definition for ADC_DR16 register  */
#define ADC_DR16                                       (0xFFFFU)

/*  Bit definition for ADC_AWDCR register  */
#define ADC_AWDCR_AWDEN_POS                            (0U)
#define ADC_AWDCR_AWDEN                                (0x0001U)
#define ADC_AWDCR_AWDMD_POS                            (4U)
#define ADC_AWDCR_AWDMD                                (0x0010U)
#define ADC_AWDCR_AWDSS_POS                            (6U)
#define ADC_AWDCR_AWDSS                                (0x00C0U)
#define ADC_AWDCR_AWDSS_0                              (0x0040U)
#define ADC_AWDCR_AWDSS_1                              (0x0080U)
#define ADC_AWDCR_AWDIEN_POS                           (8U)
#define ADC_AWDCR_AWDIEN                               (0x0100U)

/*  Bit definition for ADC_AWDDR0 register  */
#define ADC_AWDDR0                                     (0xFFFFU)

/*  Bit definition for ADC_AWDDR1 register  */
#define ADC_AWDDR1                                     (0xFFFFU)

/*  Bit definition for ADC_AWDCHSR register  */
#define ADC_AWDCHSR_AWDCH                              (0x0001FFFFUL)

/*  Bit definition for ADC_AWDSR register  */
#define ADC_AWDSR_AWDF                                 (0x0001FFFFUL)

/*  Bit definition for ADC_PGACR register  */
#define ADC_PGACR_PGACTL                               (0x000FU)
#define ADC_PGACR_PGACTL_0                             (0x0001U)
#define ADC_PGACR_PGACTL_1                             (0x0002U)
#define ADC_PGACR_PGACTL_2                             (0x0004U)
#define ADC_PGACR_PGACTL_3                             (0x0008U)

/*  Bit definition for ADC_PGAGSR register  */
#define ADC_PGAGSR_GAIN                                (0x000FU)
#define ADC_PGAGSR_GAIN_0                              (0x0001U)
#define ADC_PGAGSR_GAIN_1                              (0x0002U)
#define ADC_PGAGSR_GAIN_2                              (0x0004U)
#define ADC_PGAGSR_GAIN_3                              (0x0008U)

/*  Bit definition for ADC_PGAINSR0 register  */
#define ADC_PGAINSR0_PGAINSEL                          (0x01FFU)
#define ADC_PGAINSR0_PGAINSEL_0                        (0x0001U)
#define ADC_PGAINSR0_PGAINSEL_1                        (0x0002U)
#define ADC_PGAINSR0_PGAINSEL_2                        (0x0004U)
#define ADC_PGAINSR0_PGAINSEL_3                        (0x0008U)
#define ADC_PGAINSR0_PGAINSEL_4                        (0x0010U)
#define ADC_PGAINSR0_PGAINSEL_5                        (0x0020U)
#define ADC_PGAINSR0_PGAINSEL_6                        (0x0040U)
#define ADC_PGAINSR0_PGAINSEL_7                        (0x0080U)
#define ADC_PGAINSR0_PGAINSEL_8                        (0x0100U)

/*  Bit definition for ADC_PGAINSR1 register  */
#define ADC_PGAINSR1_PGAVSSEN                          (0x0001U)

/*******************************************************************************
                Bit definition for Peripheral AES
*******************************************************************************/
/*  Bit definition for AES_CR register  */
#define AES_CR_START_POS                               (0U)
#define AES_CR_START                                   (0x00000001UL)
#define AES_CR_MODE_POS                                (1U)
#define AES_CR_MODE                                    (0x00000002UL)

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

/*******************************************************************************
                Bit definition for Peripheral AOS
*******************************************************************************/
/*  Bit definition for AOS_INTSFTTRG register  */
#define AOS_INTSFTTRG_STRG                             (0x00000001UL)

/*  Bit definition for AOS_DCU_TRGSEL register  */
#define AOS_DCU_TRGSEL_TRGSEL_POS                      (0U)
#define AOS_DCU_TRGSEL_TRGSEL                          (0x000001FFUL)
#define AOS_DCU_TRGSEL_COMTRG_EN_POS                   (30U)
#define AOS_DCU_TRGSEL_COMTRG_EN                       (0xC0000000UL)
#define AOS_DCU_TRGSEL_COMTRG_EN_0                     (0x40000000UL)
#define AOS_DCU_TRGSEL_COMTRG_EN_1                     (0x80000000UL)

/*  Bit definition for AOS_DMA1_TRGSEL register  */
#define AOS_DMA1_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_DMA1_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_DMA1_TRGSEL_COMTRG_EN_POS                  (30U)
#define AOS_DMA1_TRGSEL_COMTRG_EN                      (0xC0000000UL)
#define AOS_DMA1_TRGSEL_COMTRG_EN_0                    (0x40000000UL)
#define AOS_DMA1_TRGSEL_COMTRG_EN_1                    (0x80000000UL)

/*  Bit definition for AOS_DMA2_TRGSEL register  */
#define AOS_DMA2_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_DMA2_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_DMA2_TRGSEL_COMTRG_EN_POS                  (30U)
#define AOS_DMA2_TRGSEL_COMTRG_EN                      (0xC0000000UL)
#define AOS_DMA2_TRGSEL_COMTRG_EN_0                    (0x40000000UL)
#define AOS_DMA2_TRGSEL_COMTRG_EN_1                    (0x80000000UL)

/*  Bit definition for AOS_DMA_TRGSELRC register  */
#define AOS_DMA_TRGSELRC_TRGSEL_POS                    (0U)
#define AOS_DMA_TRGSELRC_TRGSEL                        (0x000001FFUL)
#define AOS_DMA_TRGSELRC_COMTRG_EN_POS                 (30U)
#define AOS_DMA_TRGSELRC_COMTRG_EN                     (0xC0000000UL)
#define AOS_DMA_TRGSELRC_COMTRG_EN_0                   (0x40000000UL)
#define AOS_DMA_TRGSELRC_COMTRG_EN_1                   (0x80000000UL)

/*  Bit definition for AOS_TMR6_HTSSR register  */
#define AOS_TMR6_HTSSR_TRGSEL_POS                      (0U)
#define AOS_TMR6_HTSSR_TRGSEL                          (0x000001FFUL)
#define AOS_TMR6_HTSSR_COMTRG_EN_POS                   (30U)
#define AOS_TMR6_HTSSR_COMTRG_EN                       (0xC0000000UL)
#define AOS_TMR6_HTSSR_COMTRG_EN_0                     (0x40000000UL)
#define AOS_TMR6_HTSSR_COMTRG_EN_1                     (0x80000000UL)

/*  Bit definition for AOS_TMR0_HTSSR register  */
#define AOS_TMR0_HTSSR_TRGSEL_POS                      (0U)
#define AOS_TMR0_HTSSR_TRGSEL                          (0x000001FFUL)
#define AOS_TMR0_HTSSR_COMTRG_EN_POS                   (30U)
#define AOS_TMR0_HTSSR_COMTRG_EN                       (0xC0000000UL)
#define AOS_TMR0_HTSSR_COMTRG_EN_0                     (0x40000000UL)
#define AOS_TMR0_HTSSR_COMTRG_EN_1                     (0x80000000UL)

/*  Bit definition for AOS_PEVNTTRGSR register  */
#define AOS_PEVNTTRGSR_TRGSEL_POS                      (0U)
#define AOS_PEVNTTRGSR_TRGSEL                          (0x000001FFUL)
#define AOS_PEVNTTRGSR_COMTRG_EN_POS                   (30U)
#define AOS_PEVNTTRGSR_COMTRG_EN                       (0xC0000000UL)
#define AOS_PEVNTTRGSR_COMTRG_EN_0                     (0x40000000UL)
#define AOS_PEVNTTRGSR_COMTRG_EN_1                     (0x80000000UL)

/*  Bit definition for AOS_TMRA_HTSSR register  */
#define AOS_TMRA_HTSSR_TRGSEL_POS                      (0U)
#define AOS_TMRA_HTSSR_TRGSEL                          (0x000001FFUL)
#define AOS_TMRA_HTSSR_COMTRG_EN_POS                   (30U)
#define AOS_TMRA_HTSSR_COMTRG_EN                       (0xC0000000UL)
#define AOS_TMRA_HTSSR_COMTRG_EN_0                     (0x40000000UL)
#define AOS_TMRA_HTSSR_COMTRG_EN_1                     (0x80000000UL)

/*  Bit definition for AOS_OTS_TRG register  */
#define AOS_OTS_TRG_TRGSEL_POS                         (0U)
#define AOS_OTS_TRG_TRGSEL                             (0x000001FFUL)
#define AOS_OTS_TRG_COMTRG_EN_POS                      (30U)
#define AOS_OTS_TRG_COMTRG_EN                          (0xC0000000UL)
#define AOS_OTS_TRG_COMTRG_EN_0                        (0x40000000UL)
#define AOS_OTS_TRG_COMTRG_EN_1                        (0x80000000UL)

/*  Bit definition for AOS_ADC1_ITRGSELR register  */
#define AOS_ADC1_ITRGSELR_TRGSEL_POS                   (0U)
#define AOS_ADC1_ITRGSELR_TRGSEL                       (0x000001FFUL)
#define AOS_ADC1_ITRGSELR_COMTRG_EN_POS                (30U)
#define AOS_ADC1_ITRGSELR_COMTRG_EN                    (0xC0000000UL)
#define AOS_ADC1_ITRGSELR_COMTRG_EN_0                  (0x40000000UL)
#define AOS_ADC1_ITRGSELR_COMTRG_EN_1                  (0x80000000UL)

/*  Bit definition for AOS_ADC2_ITRGSELR register  */
#define AOS_ADC2_ITRGSELR_TRGSEL_POS                   (0U)
#define AOS_ADC2_ITRGSELR_TRGSEL                       (0x000001FFUL)
#define AOS_ADC2_ITRGSELR_COMTRG_EN_POS                (30U)
#define AOS_ADC2_ITRGSELR_COMTRG_EN                    (0xC0000000UL)
#define AOS_ADC2_ITRGSELR_COMTRG_EN_0                  (0x40000000UL)
#define AOS_ADC2_ITRGSELR_COMTRG_EN_1                  (0x80000000UL)

/*  Bit definition for AOS_COMTRG1 register  */
#define AOS_COMTRG1_TRGSEL                             (0x000001FFUL)

/*  Bit definition for AOS_COMTRG2 register  */
#define AOS_COMTRG2_TRGSEL                             (0x000001FFUL)

/*  Bit definition for AOS_PEVNTDIRR register  */
#define AOS_PEVNTDIRR_PDIR00_POS                       (0U)
#define AOS_PEVNTDIRR_PDIR00                           (0x00000001UL)
#define AOS_PEVNTDIRR_PDIR01_POS                       (1U)
#define AOS_PEVNTDIRR_PDIR01                           (0x00000002UL)
#define AOS_PEVNTDIRR_PDIR02_POS                       (2U)
#define AOS_PEVNTDIRR_PDIR02                           (0x00000004UL)
#define AOS_PEVNTDIRR_PDIR03_POS                       (3U)
#define AOS_PEVNTDIRR_PDIR03                           (0x00000008UL)
#define AOS_PEVNTDIRR_PDIR04_POS                       (4U)
#define AOS_PEVNTDIRR_PDIR04                           (0x00000010UL)
#define AOS_PEVNTDIRR_PDIR05_POS                       (5U)
#define AOS_PEVNTDIRR_PDIR05                           (0x00000020UL)
#define AOS_PEVNTDIRR_PDIR06_POS                       (6U)
#define AOS_PEVNTDIRR_PDIR06                           (0x00000040UL)
#define AOS_PEVNTDIRR_PDIR07_POS                       (7U)
#define AOS_PEVNTDIRR_PDIR07                           (0x00000080UL)
#define AOS_PEVNTDIRR_PDIR08_POS                       (8U)
#define AOS_PEVNTDIRR_PDIR08                           (0x00000100UL)
#define AOS_PEVNTDIRR_PDIR09_POS                       (9U)
#define AOS_PEVNTDIRR_PDIR09                           (0x00000200UL)
#define AOS_PEVNTDIRR_PDIR10_POS                       (10U)
#define AOS_PEVNTDIRR_PDIR10                           (0x00000400UL)
#define AOS_PEVNTDIRR_PDIR11_POS                       (11U)
#define AOS_PEVNTDIRR_PDIR11                           (0x00000800UL)
#define AOS_PEVNTDIRR_PDIR12_POS                       (12U)
#define AOS_PEVNTDIRR_PDIR12                           (0x00001000UL)
#define AOS_PEVNTDIRR_PDIR13_POS                       (13U)
#define AOS_PEVNTDIRR_PDIR13                           (0x00002000UL)
#define AOS_PEVNTDIRR_PDIR14_POS                       (14U)
#define AOS_PEVNTDIRR_PDIR14                           (0x00004000UL)
#define AOS_PEVNTDIRR_PDIR15_POS                       (15U)
#define AOS_PEVNTDIRR_PDIR15                           (0x00008000UL)

/*  Bit definition for AOS_PEVNTIDR register  */
#define AOS_PEVNTIDR_PIN00_POS                         (0U)
#define AOS_PEVNTIDR_PIN00                             (0x00000001UL)
#define AOS_PEVNTIDR_PIN01_POS                         (1U)
#define AOS_PEVNTIDR_PIN01                             (0x00000002UL)
#define AOS_PEVNTIDR_PIN02_POS                         (2U)
#define AOS_PEVNTIDR_PIN02                             (0x00000004UL)
#define AOS_PEVNTIDR_PIN03_POS                         (3U)
#define AOS_PEVNTIDR_PIN03                             (0x00000008UL)
#define AOS_PEVNTIDR_PIN04_POS                         (4U)
#define AOS_PEVNTIDR_PIN04                             (0x00000010UL)
#define AOS_PEVNTIDR_PIN05_POS                         (5U)
#define AOS_PEVNTIDR_PIN05                             (0x00000020UL)
#define AOS_PEVNTIDR_PIN06_POS                         (6U)
#define AOS_PEVNTIDR_PIN06                             (0x00000040UL)
#define AOS_PEVNTIDR_PIN07_POS                         (7U)
#define AOS_PEVNTIDR_PIN07                             (0x00000080UL)
#define AOS_PEVNTIDR_PIN08_POS                         (8U)
#define AOS_PEVNTIDR_PIN08                             (0x00000100UL)
#define AOS_PEVNTIDR_PIN09_POS                         (9U)
#define AOS_PEVNTIDR_PIN09                             (0x00000200UL)
#define AOS_PEVNTIDR_PIN10_POS                         (10U)
#define AOS_PEVNTIDR_PIN10                             (0x00000400UL)
#define AOS_PEVNTIDR_PIN11_POS                         (11U)
#define AOS_PEVNTIDR_PIN11                             (0x00000800UL)
#define AOS_PEVNTIDR_PIN12_POS                         (12U)
#define AOS_PEVNTIDR_PIN12                             (0x00001000UL)
#define AOS_PEVNTIDR_PIN13_POS                         (13U)
#define AOS_PEVNTIDR_PIN13                             (0x00002000UL)
#define AOS_PEVNTIDR_PIN14_POS                         (14U)
#define AOS_PEVNTIDR_PIN14                             (0x00004000UL)
#define AOS_PEVNTIDR_PIN15_POS                         (15U)
#define AOS_PEVNTIDR_PIN15                             (0x00008000UL)

/*  Bit definition for AOS_PEVNTODR register  */
#define AOS_PEVNTODR_POUT00_POS                        (0U)
#define AOS_PEVNTODR_POUT00                            (0x00000001UL)
#define AOS_PEVNTODR_POUT01_POS                        (1U)
#define AOS_PEVNTODR_POUT01                            (0x00000002UL)
#define AOS_PEVNTODR_POUT02_POS                        (2U)
#define AOS_PEVNTODR_POUT02                            (0x00000004UL)
#define AOS_PEVNTODR_POUT03_POS                        (3U)
#define AOS_PEVNTODR_POUT03                            (0x00000008UL)
#define AOS_PEVNTODR_POUT04_POS                        (4U)
#define AOS_PEVNTODR_POUT04                            (0x00000010UL)
#define AOS_PEVNTODR_POUT05_POS                        (5U)
#define AOS_PEVNTODR_POUT05                            (0x00000020UL)
#define AOS_PEVNTODR_POUT06_POS                        (6U)
#define AOS_PEVNTODR_POUT06                            (0x00000040UL)
#define AOS_PEVNTODR_POUT07_POS                        (7U)
#define AOS_PEVNTODR_POUT07                            (0x00000080UL)
#define AOS_PEVNTODR_POUT08_POS                        (8U)
#define AOS_PEVNTODR_POUT08                            (0x00000100UL)
#define AOS_PEVNTODR_POUT09_POS                        (9U)
#define AOS_PEVNTODR_POUT09                            (0x00000200UL)
#define AOS_PEVNTODR_POUT10_POS                        (10U)
#define AOS_PEVNTODR_POUT10                            (0x00000400UL)
#define AOS_PEVNTODR_POUT11_POS                        (11U)
#define AOS_PEVNTODR_POUT11                            (0x00000800UL)
#define AOS_PEVNTODR_POUT12_POS                        (12U)
#define AOS_PEVNTODR_POUT12                            (0x00001000UL)
#define AOS_PEVNTODR_POUT13_POS                        (13U)
#define AOS_PEVNTODR_POUT13                            (0x00002000UL)
#define AOS_PEVNTODR_POUT14_POS                        (14U)
#define AOS_PEVNTODR_POUT14                            (0x00004000UL)
#define AOS_PEVNTODR_POUT15_POS                        (15U)
#define AOS_PEVNTODR_POUT15                            (0x00008000UL)

/*  Bit definition for AOS_PEVNTORR register  */
#define AOS_PEVNTORR_POR00_POS                         (0U)
#define AOS_PEVNTORR_POR00                             (0x00000001UL)
#define AOS_PEVNTORR_POR01_POS                         (1U)
#define AOS_PEVNTORR_POR01                             (0x00000002UL)
#define AOS_PEVNTORR_POR02_POS                         (2U)
#define AOS_PEVNTORR_POR02                             (0x00000004UL)
#define AOS_PEVNTORR_POR03_POS                         (3U)
#define AOS_PEVNTORR_POR03                             (0x00000008UL)
#define AOS_PEVNTORR_POR04_POS                         (4U)
#define AOS_PEVNTORR_POR04                             (0x00000010UL)
#define AOS_PEVNTORR_POR05_POS                         (5U)
#define AOS_PEVNTORR_POR05                             (0x00000020UL)
#define AOS_PEVNTORR_POR06_POS                         (6U)
#define AOS_PEVNTORR_POR06                             (0x00000040UL)
#define AOS_PEVNTORR_POR07_POS                         (7U)
#define AOS_PEVNTORR_POR07                             (0x00000080UL)
#define AOS_PEVNTORR_POR08_POS                         (8U)
#define AOS_PEVNTORR_POR08                             (0x00000100UL)
#define AOS_PEVNTORR_POR09_POS                         (9U)
#define AOS_PEVNTORR_POR09                             (0x00000200UL)
#define AOS_PEVNTORR_POR10_POS                         (10U)
#define AOS_PEVNTORR_POR10                             (0x00000400UL)
#define AOS_PEVNTORR_POR11_POS                         (11U)
#define AOS_PEVNTORR_POR11                             (0x00000800UL)
#define AOS_PEVNTORR_POR12_POS                         (12U)
#define AOS_PEVNTORR_POR12                             (0x00001000UL)
#define AOS_PEVNTORR_POR13_POS                         (13U)
#define AOS_PEVNTORR_POR13                             (0x00002000UL)
#define AOS_PEVNTORR_POR14_POS                         (14U)
#define AOS_PEVNTORR_POR14                             (0x00004000UL)
#define AOS_PEVNTORR_POR15_POS                         (15U)
#define AOS_PEVNTORR_POR15                             (0x00008000UL)

/*  Bit definition for AOS_PEVNTOSR register  */
#define AOS_PEVNTOSR_POS00_POS                         (0U)
#define AOS_PEVNTOSR_POS00                             (0x00000001UL)
#define AOS_PEVNTOSR_POS01_POS                         (1U)
#define AOS_PEVNTOSR_POS01                             (0x00000002UL)
#define AOS_PEVNTOSR_POS02_POS                         (2U)
#define AOS_PEVNTOSR_POS02                             (0x00000004UL)
#define AOS_PEVNTOSR_POS03_POS                         (3U)
#define AOS_PEVNTOSR_POS03                             (0x00000008UL)
#define AOS_PEVNTOSR_POS04_POS                         (4U)
#define AOS_PEVNTOSR_POS04                             (0x00000010UL)
#define AOS_PEVNTOSR_POS05_POS                         (5U)
#define AOS_PEVNTOSR_POS05                             (0x00000020UL)
#define AOS_PEVNTOSR_POS06_POS                         (6U)
#define AOS_PEVNTOSR_POS06                             (0x00000040UL)
#define AOS_PEVNTOSR_POS07_POS                         (7U)
#define AOS_PEVNTOSR_POS07                             (0x00000080UL)
#define AOS_PEVNTOSR_POS08_POS                         (8U)
#define AOS_PEVNTOSR_POS08                             (0x00000100UL)
#define AOS_PEVNTOSR_POS09_POS                         (9U)
#define AOS_PEVNTOSR_POS09                             (0x00000200UL)
#define AOS_PEVNTOSR_POS10_POS                         (10U)
#define AOS_PEVNTOSR_POS10                             (0x00000400UL)
#define AOS_PEVNTOSR_POS11_POS                         (11U)
#define AOS_PEVNTOSR_POS11                             (0x00000800UL)
#define AOS_PEVNTOSR_POS12_POS                         (12U)
#define AOS_PEVNTOSR_POS12                             (0x00001000UL)
#define AOS_PEVNTOSR_POS13_POS                         (13U)
#define AOS_PEVNTOSR_POS13                             (0x00002000UL)
#define AOS_PEVNTOSR_POS14_POS                         (14U)
#define AOS_PEVNTOSR_POS14                             (0x00004000UL)
#define AOS_PEVNTOSR_POS15_POS                         (15U)
#define AOS_PEVNTOSR_POS15                             (0x00008000UL)

/*  Bit definition for AOS_PEVNTRISR register  */
#define AOS_PEVNTRISR_RIS00_POS                        (0U)
#define AOS_PEVNTRISR_RIS00                            (0x00000001UL)
#define AOS_PEVNTRISR_RIS01_POS                        (1U)
#define AOS_PEVNTRISR_RIS01                            (0x00000002UL)
#define AOS_PEVNTRISR_RIS02_POS                        (2U)
#define AOS_PEVNTRISR_RIS02                            (0x00000004UL)
#define AOS_PEVNTRISR_RIS03_POS                        (3U)
#define AOS_PEVNTRISR_RIS03                            (0x00000008UL)
#define AOS_PEVNTRISR_RIS04_POS                        (4U)
#define AOS_PEVNTRISR_RIS04                            (0x00000010UL)
#define AOS_PEVNTRISR_RIS05_POS                        (5U)
#define AOS_PEVNTRISR_RIS05                            (0x00000020UL)
#define AOS_PEVNTRISR_RIS06_POS                        (6U)
#define AOS_PEVNTRISR_RIS06                            (0x00000040UL)
#define AOS_PEVNTRISR_RIS07_POS                        (7U)
#define AOS_PEVNTRISR_RIS07                            (0x00000080UL)
#define AOS_PEVNTRISR_RIS08_POS                        (8U)
#define AOS_PEVNTRISR_RIS08                            (0x00000100UL)
#define AOS_PEVNTRISR_RIS09_POS                        (9U)
#define AOS_PEVNTRISR_RIS09                            (0x00000200UL)
#define AOS_PEVNTRISR_RIS10_POS                        (10U)
#define AOS_PEVNTRISR_RIS10                            (0x00000400UL)
#define AOS_PEVNTRISR_RIS11_POS                        (11U)
#define AOS_PEVNTRISR_RIS11                            (0x00000800UL)
#define AOS_PEVNTRISR_RIS12_POS                        (12U)
#define AOS_PEVNTRISR_RIS12                            (0x00001000UL)
#define AOS_PEVNTRISR_RIS13_POS                        (13U)
#define AOS_PEVNTRISR_RIS13                            (0x00002000UL)
#define AOS_PEVNTRISR_RIS14_POS                        (14U)
#define AOS_PEVNTRISR_RIS14                            (0x00004000UL)
#define AOS_PEVNTRISR_RIS15_POS                        (15U)
#define AOS_PEVNTRISR_RIS15                            (0x00008000UL)

/*  Bit definition for AOS_PEVNTFAL register  */
#define AOS_PEVNTFAL_FAL00_POS                         (0U)
#define AOS_PEVNTFAL_FAL00                             (0x00000001UL)
#define AOS_PEVNTFAL_FAL01_POS                         (1U)
#define AOS_PEVNTFAL_FAL01                             (0x00000002UL)
#define AOS_PEVNTFAL_FAL02_POS                         (2U)
#define AOS_PEVNTFAL_FAL02                             (0x00000004UL)
#define AOS_PEVNTFAL_FAL03_POS                         (3U)
#define AOS_PEVNTFAL_FAL03                             (0x00000008UL)
#define AOS_PEVNTFAL_FAL04_POS                         (4U)
#define AOS_PEVNTFAL_FAL04                             (0x00000010UL)
#define AOS_PEVNTFAL_FAL05_POS                         (5U)
#define AOS_PEVNTFAL_FAL05                             (0x00000020UL)
#define AOS_PEVNTFAL_FAL06_POS                         (6U)
#define AOS_PEVNTFAL_FAL06                             (0x00000040UL)
#define AOS_PEVNTFAL_FAL07_POS                         (7U)
#define AOS_PEVNTFAL_FAL07                             (0x00000080UL)
#define AOS_PEVNTFAL_FAL08_POS                         (8U)
#define AOS_PEVNTFAL_FAL08                             (0x00000100UL)
#define AOS_PEVNTFAL_FAL09_POS                         (9U)
#define AOS_PEVNTFAL_FAL09                             (0x00000200UL)
#define AOS_PEVNTFAL_FAL10_POS                         (10U)
#define AOS_PEVNTFAL_FAL10                             (0x00000400UL)
#define AOS_PEVNTFAL_FAL11_POS                         (11U)
#define AOS_PEVNTFAL_FAL11                             (0x00000800UL)
#define AOS_PEVNTFAL_FAL12_POS                         (12U)
#define AOS_PEVNTFAL_FAL12                             (0x00001000UL)
#define AOS_PEVNTFAL_FAL13_POS                         (13U)
#define AOS_PEVNTFAL_FAL13                             (0x00002000UL)
#define AOS_PEVNTFAL_FAL14_POS                         (14U)
#define AOS_PEVNTFAL_FAL14                             (0x00004000UL)
#define AOS_PEVNTFAL_FAL15_POS                         (15U)
#define AOS_PEVNTFAL_FAL15                             (0x00008000UL)

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
#define CAN_LIMIT_EWL_0                                (0x01U)
#define CAN_LIMIT_EWL_1                                (0x02U)
#define CAN_LIMIT_EWL_2                                (0x04U)
#define CAN_LIMIT_EWL_3                                (0x08U)
#define CAN_LIMIT_AFWL_POS                             (4U)
#define CAN_LIMIT_AFWL                                 (0xF0U)
#define CAN_LIMIT_AFWL_0                               (0x10U)
#define CAN_LIMIT_AFWL_1                               (0x20U)
#define CAN_LIMIT_AFWL_2                               (0x40U)
#define CAN_LIMIT_AFWL_3                               (0x80U)

/*  Bit definition for CAN_SBT register  */
#define CAN_SBT_S_SEG_1_POS                            (0U)
#define CAN_SBT_S_SEG_1                                (0x000000FFUL)
#define CAN_SBT_S_SEG_1_0                              (0x00000001UL)
#define CAN_SBT_S_SEG_1_1                              (0x00000002UL)
#define CAN_SBT_S_SEG_1_2                              (0x00000004UL)
#define CAN_SBT_S_SEG_1_3                              (0x00000008UL)
#define CAN_SBT_S_SEG_1_4                              (0x00000010UL)
#define CAN_SBT_S_SEG_1_5                              (0x00000020UL)
#define CAN_SBT_S_SEG_1_6                              (0x00000040UL)
#define CAN_SBT_S_SEG_1_7                              (0x00000080UL)
#define CAN_SBT_S_SEG_2_POS                            (8U)
#define CAN_SBT_S_SEG_2                                (0x00007F00UL)
#define CAN_SBT_S_SEG_2_0                              (0x00000100UL)
#define CAN_SBT_S_SEG_2_1                              (0x00000200UL)
#define CAN_SBT_S_SEG_2_2                              (0x00000400UL)
#define CAN_SBT_S_SEG_2_3                              (0x00000800UL)
#define CAN_SBT_S_SEG_2_4                              (0x00001000UL)
#define CAN_SBT_S_SEG_2_5                              (0x00002000UL)
#define CAN_SBT_S_SEG_2_6                              (0x00004000UL)
#define CAN_SBT_S_SJW_POS                              (16U)
#define CAN_SBT_S_SJW                                  (0x007F0000UL)
#define CAN_SBT_S_SJW_0                                (0x00010000UL)
#define CAN_SBT_S_SJW_1                                (0x00020000UL)
#define CAN_SBT_S_SJW_2                                (0x00040000UL)
#define CAN_SBT_S_SJW_3                                (0x00080000UL)
#define CAN_SBT_S_SJW_4                                (0x00100000UL)
#define CAN_SBT_S_SJW_5                                (0x00200000UL)
#define CAN_SBT_S_SJW_6                                (0x00400000UL)
#define CAN_SBT_S_PRESC_POS                            (24U)
#define CAN_SBT_S_PRESC                                (0xFF000000UL)
#define CAN_SBT_S_PRESC_0                              (0x01000000UL)
#define CAN_SBT_S_PRESC_1                              (0x02000000UL)
#define CAN_SBT_S_PRESC_2                              (0x04000000UL)
#define CAN_SBT_S_PRESC_3                              (0x08000000UL)
#define CAN_SBT_S_PRESC_4                              (0x10000000UL)
#define CAN_SBT_S_PRESC_5                              (0x20000000UL)
#define CAN_SBT_S_PRESC_6                              (0x40000000UL)
#define CAN_SBT_S_PRESC_7                              (0x80000000UL)

/*  Bit definition for CAN_EALCAP register  */
#define CAN_EALCAP_ALC_POS                             (0U)
#define CAN_EALCAP_ALC                                 (0x1FU)
#define CAN_EALCAP_ALC_0                               (0x01U)
#define CAN_EALCAP_ALC_1                               (0x02U)
#define CAN_EALCAP_ALC_2                               (0x04U)
#define CAN_EALCAP_ALC_3                               (0x08U)
#define CAN_EALCAP_ALC_4                               (0x10U)
#define CAN_EALCAP_KOER_POS                            (5U)
#define CAN_EALCAP_KOER                                (0xE0U)
#define CAN_EALCAP_KOER_0                              (0x20U)
#define CAN_EALCAP_KOER_1                              (0x40U)
#define CAN_EALCAP_KOER_2                              (0x80U)

/*  Bit definition for CAN_RECNT register  */
#define CAN_RECNT                                      (0xFFU)

/*  Bit definition for CAN_TECNT register  */
#define CAN_TECNT                                      (0xFFU)

/*  Bit definition for CAN_ACFCTRL register  */
#define CAN_ACFCTRL_ACFADR_POS                         (0U)
#define CAN_ACFCTRL_ACFADR                             (0x0FU)
#define CAN_ACFCTRL_ACFADR_0                           (0x01U)
#define CAN_ACFCTRL_ACFADR_1                           (0x02U)
#define CAN_ACFCTRL_ACFADR_2                           (0x04U)
#define CAN_ACFCTRL_ACFADR_3                           (0x08U)
#define CAN_ACFCTRL_SELMASK_POS                        (5U)
#define CAN_ACFCTRL_SELMASK                            (0x20U)

/*  Bit definition for CAN_ACFEN register  */
#define CAN_ACFEN_AE_1_POS                             (0U)
#define CAN_ACFEN_AE_1                                 (0x01U)
#define CAN_ACFEN_AE_2_POS                             (1U)
#define CAN_ACFEN_AE_2                                 (0x02U)
#define CAN_ACFEN_AE_3_POS                             (2U)
#define CAN_ACFEN_AE_3                                 (0x04U)
#define CAN_ACFEN_AE_4_POS                             (3U)
#define CAN_ACFEN_AE_4                                 (0x08U)
#define CAN_ACFEN_AE_5_POS                             (4U)
#define CAN_ACFEN_AE_5                                 (0x10U)
#define CAN_ACFEN_AE_6_POS                             (5U)
#define CAN_ACFEN_AE_6                                 (0x20U)
#define CAN_ACFEN_AE_7_POS                             (6U)
#define CAN_ACFEN_AE_7                                 (0x40U)
#define CAN_ACFEN_AE_8_POS                             (7U)
#define CAN_ACFEN_AE_8                                 (0x80U)

/*  Bit definition for CAN_ACF register  */
#define CAN_ACF_ACODEORAMASK_POS                       (0U)
#define CAN_ACF_ACODEORAMASK                           (0x1FFFFFFFUL)
#define CAN_ACF_ACODEORAMASK_0                         (0x00000001UL)
#define CAN_ACF_ACODEORAMASK_1                         (0x00000002UL)
#define CAN_ACF_ACODEORAMASK_2                         (0x00000004UL)
#define CAN_ACF_ACODEORAMASK_3                         (0x00000008UL)
#define CAN_ACF_ACODEORAMASK_4                         (0x00000010UL)
#define CAN_ACF_ACODEORAMASK_5                         (0x00000020UL)
#define CAN_ACF_ACODEORAMASK_6                         (0x00000040UL)
#define CAN_ACF_ACODEORAMASK_7                         (0x00000080UL)
#define CAN_ACF_ACODEORAMASK_8                         (0x00000100UL)
#define CAN_ACF_ACODEORAMASK_9                         (0x00000200UL)
#define CAN_ACF_ACODEORAMASK_10                        (0x00000400UL)
#define CAN_ACF_ACODEORAMASK_11                        (0x00000800UL)
#define CAN_ACF_ACODEORAMASK_12                        (0x00001000UL)
#define CAN_ACF_ACODEORAMASK_13                        (0x00002000UL)
#define CAN_ACF_ACODEORAMASK_14                        (0x00004000UL)
#define CAN_ACF_ACODEORAMASK_15                        (0x00008000UL)
#define CAN_ACF_ACODEORAMASK_16                        (0x00010000UL)
#define CAN_ACF_ACODEORAMASK_17                        (0x00020000UL)
#define CAN_ACF_ACODEORAMASK_18                        (0x00040000UL)
#define CAN_ACF_ACODEORAMASK_19                        (0x00080000UL)
#define CAN_ACF_ACODEORAMASK_20                        (0x00100000UL)
#define CAN_ACF_ACODEORAMASK_21                        (0x00200000UL)
#define CAN_ACF_ACODEORAMASK_22                        (0x00400000UL)
#define CAN_ACF_ACODEORAMASK_23                        (0x00800000UL)
#define CAN_ACF_ACODEORAMASK_24                        (0x01000000UL)
#define CAN_ACF_ACODEORAMASK_25                        (0x02000000UL)
#define CAN_ACF_ACODEORAMASK_26                        (0x04000000UL)
#define CAN_ACF_ACODEORAMASK_27                        (0x08000000UL)
#define CAN_ACF_ACODEORAMASK_28                        (0x10000000UL)
#define CAN_ACF_AIDE_POS                               (29U)
#define CAN_ACF_AIDE                                   (0x20000000UL)
#define CAN_ACF_AIDEE_POS                              (30U)
#define CAN_ACF_AIDEE                                  (0x40000000UL)

/*  Bit definition for CAN_TBSLOT register  */
#define CAN_TBSLOT_TBPTR_POS                           (0U)
#define CAN_TBSLOT_TBPTR                               (0x3FU)
#define CAN_TBSLOT_TBPTR_0                             (0x01U)
#define CAN_TBSLOT_TBPTR_1                             (0x02U)
#define CAN_TBSLOT_TBPTR_2                             (0x04U)
#define CAN_TBSLOT_TBPTR_3                             (0x08U)
#define CAN_TBSLOT_TBPTR_4                             (0x10U)
#define CAN_TBSLOT_TBPTR_5                             (0x20U)
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
#define CAN_REF_MSG_REF_ID_0                           (0x00000001UL)
#define CAN_REF_MSG_REF_ID_1                           (0x00000002UL)
#define CAN_REF_MSG_REF_ID_2                           (0x00000004UL)
#define CAN_REF_MSG_REF_ID_3                           (0x00000008UL)
#define CAN_REF_MSG_REF_ID_4                           (0x00000010UL)
#define CAN_REF_MSG_REF_ID_5                           (0x00000020UL)
#define CAN_REF_MSG_REF_ID_6                           (0x00000040UL)
#define CAN_REF_MSG_REF_ID_7                           (0x00000080UL)
#define CAN_REF_MSG_REF_ID_8                           (0x00000100UL)
#define CAN_REF_MSG_REF_ID_9                           (0x00000200UL)
#define CAN_REF_MSG_REF_ID_10                          (0x00000400UL)
#define CAN_REF_MSG_REF_ID_11                          (0x00000800UL)
#define CAN_REF_MSG_REF_ID_12                          (0x00001000UL)
#define CAN_REF_MSG_REF_ID_13                          (0x00002000UL)
#define CAN_REF_MSG_REF_ID_14                          (0x00004000UL)
#define CAN_REF_MSG_REF_ID_15                          (0x00008000UL)
#define CAN_REF_MSG_REF_ID_16                          (0x00010000UL)
#define CAN_REF_MSG_REF_ID_17                          (0x00020000UL)
#define CAN_REF_MSG_REF_ID_18                          (0x00040000UL)
#define CAN_REF_MSG_REF_ID_19                          (0x00080000UL)
#define CAN_REF_MSG_REF_ID_20                          (0x00100000UL)
#define CAN_REF_MSG_REF_ID_21                          (0x00200000UL)
#define CAN_REF_MSG_REF_ID_22                          (0x00400000UL)
#define CAN_REF_MSG_REF_ID_23                          (0x00800000UL)
#define CAN_REF_MSG_REF_ID_24                          (0x01000000UL)
#define CAN_REF_MSG_REF_ID_25                          (0x02000000UL)
#define CAN_REF_MSG_REF_ID_26                          (0x04000000UL)
#define CAN_REF_MSG_REF_ID_27                          (0x08000000UL)
#define CAN_REF_MSG_REF_ID_28                          (0x10000000UL)
#define CAN_REF_MSG_REF_IDE_POS                        (31U)
#define CAN_REF_MSG_REF_IDE                            (0x80000000UL)

/*  Bit definition for CAN_TRG_CFG register  */
#define CAN_TRG_CFG_TTPTR_POS                          (0U)
#define CAN_TRG_CFG_TTPTR                              (0x003FU)
#define CAN_TRG_CFG_TTPTR_0                            (0x0001U)
#define CAN_TRG_CFG_TTPTR_1                            (0x0002U)
#define CAN_TRG_CFG_TTPTR_2                            (0x0004U)
#define CAN_TRG_CFG_TTPTR_3                            (0x0008U)
#define CAN_TRG_CFG_TTPTR_4                            (0x0010U)
#define CAN_TRG_CFG_TTPTR_5                            (0x0020U)
#define CAN_TRG_CFG_TTYPE_POS                          (8U)
#define CAN_TRG_CFG_TTYPE                              (0x0700U)
#define CAN_TRG_CFG_TTYPE_0                            (0x0100U)
#define CAN_TRG_CFG_TTYPE_1                            (0x0200U)
#define CAN_TRG_CFG_TTYPE_2                            (0x0400U)
#define CAN_TRG_CFG_TEW_POS                            (12U)
#define CAN_TRG_CFG_TEW                                (0xF000U)
#define CAN_TRG_CFG_TEW_0                              (0x1000U)
#define CAN_TRG_CFG_TEW_1                              (0x2000U)
#define CAN_TRG_CFG_TEW_2                              (0x4000U)
#define CAN_TRG_CFG_TEW_3                              (0x8000U)

/*  Bit definition for CAN_TT_TRIG register  */
#define CAN_TT_TRIG                                    (0xFFFFU)

/*  Bit definition for CAN_TT_WTRIG register  */
#define CAN_TT_WTRIG                                   (0xFFFFU)

/*******************************************************************************
                Bit definition for Peripheral CMP
*******************************************************************************/
/*  Bit definition for CMP_CTRL register  */
#define CMP_CTRL_FLTSL_POS                             (0U)
#define CMP_CTRL_FLTSL                                 (0x0007U)
#define CMP_CTRL_FLTSL_0                               (0x0001U)
#define CMP_CTRL_FLTSL_1                               (0x0002U)
#define CMP_CTRL_FLTSL_2                               (0x0004U)
#define CMP_CTRL_EDGSL_POS                             (5U)
#define CMP_CTRL_EDGSL                                 (0x0060U)
#define CMP_CTRL_EDGSL_0                               (0x0020U)
#define CMP_CTRL_EDGSL_1                               (0x0040U)
#define CMP_CTRL_IEN_POS                               (7U)
#define CMP_CTRL_IEN                                   (0x0080U)
#define CMP_CTRL_CVSEN_POS                             (8U)
#define CMP_CTRL_CVSEN                                 (0x0100U)
#define CMP_CTRL_OUTEN_POS                             (12U)
#define CMP_CTRL_OUTEN                                 (0x1000U)
#define CMP_CTRL_INV_POS                               (13U)
#define CMP_CTRL_INV                                   (0x2000U)
#define CMP_CTRL_CMPOE_POS                             (14U)
#define CMP_CTRL_CMPOE                                 (0x4000U)
#define CMP_CTRL_CMPON_POS                             (15U)
#define CMP_CTRL_CMPON                                 (0x8000U)

/*  Bit definition for CMP_VLTSEL register  */
#define CMP_VLTSEL_RVSL_POS                            (0U)
#define CMP_VLTSEL_RVSL                                (0x000FU)
#define CMP_VLTSEL_RVSL_0                              (0x0001U)
#define CMP_VLTSEL_RVSL_1                              (0x0002U)
#define CMP_VLTSEL_RVSL_2                              (0x0004U)
#define CMP_VLTSEL_RVSL_3                              (0x0008U)
#define CMP_VLTSEL_CVSL_POS                            (8U)
#define CMP_VLTSEL_CVSL                                (0x0F00U)
#define CMP_VLTSEL_CVSL_0                              (0x0100U)
#define CMP_VLTSEL_CVSL_1                              (0x0200U)
#define CMP_VLTSEL_CVSL_2                              (0x0400U)
#define CMP_VLTSEL_CVSL_3                              (0x0800U)
#define CMP_VLTSEL_C4SL_POS                            (12U)
#define CMP_VLTSEL_C4SL                                (0x7000U)
#define CMP_VLTSEL_C4SL_0                              (0x1000U)
#define CMP_VLTSEL_C4SL_1                              (0x2000U)
#define CMP_VLTSEL_C4SL_2                              (0x4000U)

/*  Bit definition for CMP_OUTMON register  */
#define CMP_OUTMON_OMON_POS                            (0U)
#define CMP_OUTMON_OMON                                (0x0001U)
#define CMP_OUTMON_CVST_POS                            (8U)
#define CMP_OUTMON_CVST                                (0x0F00U)
#define CMP_OUTMON_CVST_0                              (0x0100U)
#define CMP_OUTMON_CVST_1                              (0x0200U)
#define CMP_OUTMON_CVST_2                              (0x0400U)
#define CMP_OUTMON_CVST_3                              (0x0800U)

/*  Bit definition for CMP_CVSSTB register  */
#define CMP_CVSSTB_STB                                 (0x000FU)
#define CMP_CVSSTB_STB_0                               (0x0001U)
#define CMP_CVSSTB_STB_1                               (0x0002U)
#define CMP_CVSSTB_STB_2                               (0x0004U)
#define CMP_CVSSTB_STB_3                               (0x0008U)

/*  Bit definition for CMP_CVSPRD register  */
#define CMP_CVSPRD_PRD                                 (0x00FFU)
#define CMP_CVSPRD_PRD_0                               (0x0001U)
#define CMP_CVSPRD_PRD_1                               (0x0002U)
#define CMP_CVSPRD_PRD_2                               (0x0004U)
#define CMP_CVSPRD_PRD_3                               (0x0008U)
#define CMP_CVSPRD_PRD_4                               (0x0010U)
#define CMP_CVSPRD_PRD_5                               (0x0020U)
#define CMP_CVSPRD_PRD_6                               (0x0040U)
#define CMP_CVSPRD_PRD_7                               (0x0080U)

/*******************************************************************************
                Bit definition for Peripheral CMPCR
*******************************************************************************/
/*  Bit definition for CMPCR_DADR1 register  */
#define CMPCR_DADR1_DATA                               (0x00FFU)

/*  Bit definition for CMPCR_DADR2 register  */
#define CMPCR_DADR2_DATA                               (0x00FFU)

/*  Bit definition for CMPCR_DACR register  */
#define CMPCR_DACR_DA1EN_POS                           (0U)
#define CMPCR_DACR_DA1EN                               (0x0001U)
#define CMPCR_DACR_DA2EN_POS                           (1U)
#define CMPCR_DACR_DA2EN                               (0x0002U)

/*  Bit definition for CMPCR_RVADC register  */
#define CMPCR_RVADC_DA1SW_POS                          (0U)
#define CMPCR_RVADC_DA1SW                              (0x0001U)
#define CMPCR_RVADC_DA2SW_POS                          (1U)
#define CMPCR_RVADC_DA2SW                              (0x0002U)
#define CMPCR_RVADC_VREFSW_POS                         (4U)
#define CMPCR_RVADC_VREFSW                             (0x0010U)
#define CMPCR_RVADC_WPRT_POS                           (8U)
#define CMPCR_RVADC_WPRT                               (0xFF00U)

/*******************************************************************************
                Bit definition for Peripheral CMU
*******************************************************************************/
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

/*  Bit definition for CMU_PLLCR register  */
#define CMU_PLLCR_MPLLOFF                              (0x01U)

/*  Bit definition for CMU_UPLLCR register  */
#define CMU_UPLLCR_UPLLOFF                             (0x01U)

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
#define CMU_OSCSTBSR_MPLLSTBF_POS                      (5U)
#define CMU_OSCSTBSR_MPLLSTBF                          (0x20U)
#define CMU_OSCSTBSR_UPLLSTBF_POS                      (6U)
#define CMU_OSCSTBSR_UPLLSTBF                          (0x40U)

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
#define CMU_TPIUCKCFGR_TPIUCKS_0                       (0x01U)
#define CMU_TPIUCKCFGR_TPIUCKS_1                       (0x02U)
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
#define CMU_XTALSTBCR_XTALSTB_0                        (0x01U)
#define CMU_XTALSTBCR_XTALSTB_1                        (0x02U)
#define CMU_XTALSTBCR_XTALSTB_2                        (0x04U)
#define CMU_XTALSTBCR_XTALSTB_3                        (0x08U)

/*  Bit definition for CMU_PLLCFGR register  */
#define CMU_PLLCFGR_MPLLM_POS                          (0U)
#define CMU_PLLCFGR_MPLLM                              (0x0000001FUL)
#define CMU_PLLCFGR_PLLSRC_POS                         (7U)
#define CMU_PLLCFGR_PLLSRC                             (0x00000080UL)
#define CMU_PLLCFGR_MPLLN_POS                          (8U)
#define CMU_PLLCFGR_MPLLN                              (0x0001FF00UL)
#define CMU_PLLCFGR_MPLLR_POS                          (20U)
#define CMU_PLLCFGR_MPLLR                              (0x00F00000UL)
#define CMU_PLLCFGR_MPLLQ_POS                          (24U)
#define CMU_PLLCFGR_MPLLQ                              (0x0F000000UL)
#define CMU_PLLCFGR_MPLLP_POS                          (28U)
#define CMU_PLLCFGR_MPLLP                              (0xF0000000UL)

/*  Bit definition for CMU_UPLLCFGR register  */
#define CMU_UPLLCFGR_UPLLM_POS                         (0U)
#define CMU_UPLLCFGR_UPLLM                             (0x0000001FUL)
#define CMU_UPLLCFGR_UPLLN_POS                         (8U)
#define CMU_UPLLCFGR_UPLLN                             (0x0001FF00UL)
#define CMU_UPLLCFGR_UPLLR_POS                         (20U)
#define CMU_UPLLCFGR_UPLLR                             (0x00F00000UL)
#define CMU_UPLLCFGR_UPLLQ_POS                         (24U)
#define CMU_UPLLCFGR_UPLLQ                             (0x0F000000UL)
#define CMU_UPLLCFGR_UPLLP_POS                         (28U)
#define CMU_UPLLCFGR_UPLLP                             (0xF0000000UL)

/*  Bit definition for CMU_XTALCFGR register  */
#define CMU_XTALCFGR_XTALDRV_POS                       (4U)
#define CMU_XTALCFGR_XTALDRV                           (0x30U)
#define CMU_XTALCFGR_XTALDRV_0                         (0x10U)
#define CMU_XTALCFGR_XTALDRV_1                         (0x20U)
#define CMU_XTALCFGR_XTALMS_POS                        (6U)
#define CMU_XTALCFGR_XTALMS                            (0x40U)
#define CMU_XTALCFGR_SUPDRV_POS                        (7U)
#define CMU_XTALCFGR_SUPDRV                            (0x80U)

/*  Bit definition for CMU_XTAL32CR register  */
#define CMU_XTAL32CR_XTAL32STP                         (0x01U)

/*  Bit definition for CMU_XTAL32CFGR register  */
#define CMU_XTAL32CFGR_XTAL32DRV                       (0x07U)
#define CMU_XTAL32CFGR_XTAL32DRV_0                     (0x01U)
#define CMU_XTAL32CFGR_XTAL32DRV_1                     (0x02U)
#define CMU_XTAL32CFGR_XTAL32DRV_2                     (0x04U)

/*  Bit definition for CMU_XTAL32NFR register  */
#define CMU_XTAL32NFR_XTAL32NF                         (0x03U)
#define CMU_XTAL32NFR_XTAL32NF_0                       (0x01U)
#define CMU_XTAL32NFR_XTAL32NF_1                       (0x02U)

/*  Bit definition for CMU_LRCCR register  */
#define CMU_LRCCR_LRCSTP                               (0x01U)

/*  Bit definition for CMU_LRCTRM register  */
#define CMU_LRCTRM                                     (0xFFU)

/*******************************************************************************
                Bit definition for Peripheral CRC
*******************************************************************************/
/*  Bit definition for CRC_CR register  */
#define CRC_CR_CR_POS                                  (1U)
#define CRC_CR_CR                                      (0x00000002UL)
#define CRC_CR_REFIN_POS                               (2U)
#define CRC_CR_REFIN                                   (0x00000004UL)
#define CRC_CR_REFOUT_POS                              (3U)
#define CRC_CR_REFOUT                                  (0x00000008UL)
#define CRC_CR_XOROUT_POS                              (4U)
#define CRC_CR_XOROUT                                  (0x00000010UL)

/*  Bit definition for CRC_RESLT register  */
#define CRC_RESLT_CRC_REG_POS                          (0U)
#define CRC_RESLT_CRC_REG                              (0x0000FFFFUL)
#define CRC_RESLT_CRC_REG_0                            (0x00000001UL)
#define CRC_RESLT_CRC_REG_1                            (0x00000002UL)
#define CRC_RESLT_CRC_REG_2                            (0x00000004UL)
#define CRC_RESLT_CRC_REG_3                            (0x00000008UL)
#define CRC_RESLT_CRC_REG_4                            (0x00000010UL)
#define CRC_RESLT_CRC_REG_5                            (0x00000020UL)
#define CRC_RESLT_CRC_REG_6                            (0x00000040UL)
#define CRC_RESLT_CRC_REG_7                            (0x00000080UL)
#define CRC_RESLT_CRC_REG_8                            (0x00000100UL)
#define CRC_RESLT_CRC_REG_9                            (0x00000200UL)
#define CRC_RESLT_CRC_REG_10                           (0x00000400UL)
#define CRC_RESLT_CRC_REG_11                           (0x00000800UL)
#define CRC_RESLT_CRC_REG_12                           (0x00001000UL)
#define CRC_RESLT_CRC_REG_13                           (0x00002000UL)
#define CRC_RESLT_CRC_REG_14                           (0x00004000UL)
#define CRC_RESLT_CRC_REG_15                           (0x00008000UL)
#define CRC_RESLT_CRCFLAG_16_POS                       (16U)
#define CRC_RESLT_CRCFLAG_16                           (0x00010000UL)

/*  Bit definition for CRC_FLG register  */
#define CRC_FLG_CRCFLAG_32                             (0x00000001UL)

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
                Bit definition for Peripheral DBGC
*******************************************************************************/
/*  Bit definition for DBGC_AUTHID0 register  */
#define DBGC_AUTHID0                                   (0xFFFFFFFFUL)

/*  Bit definition for DBGC_AUTHID1 register  */
#define DBGC_AUTHID1                                   (0xFFFFFFFFUL)

/*  Bit definition for DBGC_AUTHID2 register  */
#define DBGC_AUTHID2                                   (0xFFFFFFFFUL)

/*  Bit definition for DBGC_RESV0 register  */
#define DBGC_RESV0                                     (0xFFFFFFFFUL)

/*  Bit definition for DBGC_MCUSTAT register  */
#define DBGC_MCUSTAT_AUTH_POS                          (0U)
#define DBGC_MCUSTAT_AUTH                              (0x00000001UL)
#define DBGC_MCUSTAT_REMVLOCK_POS                      (1U)
#define DBGC_MCUSTAT_REMVLOCK                          (0x00000002UL)
#define DBGC_MCUSTAT_SAFTYLOCK1_POS                    (2U)
#define DBGC_MCUSTAT_SAFTYLOCK1                        (0x00000004UL)
#define DBGC_MCUSTAT_SAFTYLOCK2_POS                    (3U)
#define DBGC_MCUSTAT_SAFTYLOCK2                        (0x00000008UL)
#define DBGC_MCUSTAT_CPUSTOP_POS                       (8U)
#define DBGC_MCUSTAT_CPUSTOP                           (0x00000100UL)
#define DBGC_MCUSTAT_CPUSLEEP_POS                      (9U)
#define DBGC_MCUSTAT_CPUSLEEP                          (0x00000200UL)

/*  Bit definition for DBGC_MCUCTL register  */
#define DBGC_MCUCTL_EDBGRQ_POS                         (0U)
#define DBGC_MCUCTL_EDBGRQ                             (0x00000001UL)
#define DBGC_MCUCTL_RESTART_POS                        (1U)
#define DBGC_MCUCTL_RESTART                            (0x00000002UL)
#define DBGC_MCUCTL_DIRQ_POS                           (8U)
#define DBGC_MCUCTL_DIRQ                               (0x00000100UL)

/*  Bit definition for DBGC_FMCCTL register  */
#define DBGC_FMCCTL_ERASEREQ_POS                       (0U)
#define DBGC_FMCCTL_ERASEREQ                           (0x00000001UL)
#define DBGC_FMCCTL_ERASEACK_POS                       (1U)
#define DBGC_FMCCTL_ERASEACK                           (0x00000002UL)
#define DBGC_FMCCTL_ERASEERR_POS                       (2U)
#define DBGC_FMCCTL_ERASEERR                           (0x00000004UL)

/*  Bit definition for DBGC_MCUDBGSTAT register  */
#define DBGC_MCUDBGSTAT_CDBGPWRUPREQ_POS               (0U)
#define DBGC_MCUDBGSTAT_CDBGPWRUPREQ                   (0x00000001UL)
#define DBGC_MCUDBGSTAT_CDBGPWRUPACK_POS               (1U)
#define DBGC_MCUDBGSTAT_CDBGPWRUPACK                   (0x00000002UL)

/*  Bit definition for DBGC_MCUSTPCTL register  */
#define DBGC_MCUSTPCTL_SWDTSTP_POS                     (0U)
#define DBGC_MCUSTPCTL_SWDTSTP                         (0x00000001UL)
#define DBGC_MCUSTPCTL_WDTSTP_POS                      (1U)
#define DBGC_MCUSTPCTL_WDTSTP                          (0x00000002UL)
#define DBGC_MCUSTPCTL_RTCSTP_POS                      (2U)
#define DBGC_MCUSTPCTL_RTCSTP                          (0x00000004UL)
#define DBGC_MCUSTPCTL_PVD0STP_POS                     (3U)
#define DBGC_MCUSTPCTL_PVD0STP                         (0x00000008UL)
#define DBGC_MCUSTPCTL_PVD1STP_POS                     (4U)
#define DBGC_MCUSTPCTL_PVD1STP                         (0x00000010UL)
#define DBGC_MCUSTPCTL_PVD2STP_POS                     (5U)
#define DBGC_MCUSTPCTL_PVD2STP                         (0x00000020UL)
#define DBGC_MCUSTPCTL_TMR01STP_POS                    (14U)
#define DBGC_MCUSTPCTL_TMR01STP                        (0x00004000UL)
#define DBGC_MCUSTPCTL_TMR02STP_POS                    (15U)
#define DBGC_MCUSTPCTL_TMR02STP                        (0x00008000UL)
#define DBGC_MCUSTPCTL_TMR41STP_POS                    (20U)
#define DBGC_MCUSTPCTL_TMR41STP                        (0x00100000UL)
#define DBGC_MCUSTPCTL_TMR42STP_POS                    (21U)
#define DBGC_MCUSTPCTL_TMR42STP                        (0x00200000UL)
#define DBGC_MCUSTPCTL_TMR43STP_POS                    (22U)
#define DBGC_MCUSTPCTL_TMR43STP                        (0x00400000UL)
#define DBGC_MCUSTPCTL_TM61STP_POS                     (23U)
#define DBGC_MCUSTPCTL_TM61STP                         (0x00800000UL)
#define DBGC_MCUSTPCTL_TM62STP_POS                     (24U)
#define DBGC_MCUSTPCTL_TM62STP                         (0x01000000UL)
#define DBGC_MCUSTPCTL_TMR63STP_POS                    (25U)
#define DBGC_MCUSTPCTL_TMR63STP                        (0x02000000UL)
#define DBGC_MCUSTPCTL_TMRA1STP_POS                    (26U)
#define DBGC_MCUSTPCTL_TMRA1STP                        (0x04000000UL)
#define DBGC_MCUSTPCTL_TMRA2STP_POS                    (27U)
#define DBGC_MCUSTPCTL_TMRA2STP                        (0x08000000UL)
#define DBGC_MCUSTPCTL_TMRA3STP_POS                    (28U)
#define DBGC_MCUSTPCTL_TMRA3STP                        (0x10000000UL)
#define DBGC_MCUSTPCTL_TMRA4STP_POS                    (29U)
#define DBGC_MCUSTPCTL_TMRA4STP                        (0x20000000UL)
#define DBGC_MCUSTPCTL_TMRA5STP_POS                    (30U)
#define DBGC_MCUSTPCTL_TMRA5STP                        (0x40000000UL)
#define DBGC_MCUSTPCTL_TMRA6STP_POS                    (31U)
#define DBGC_MCUSTPCTL_TMRA6STP                        (0x80000000UL)

/*  Bit definition for DBGC_MCUTRACECTL register  */
#define DBGC_MCUTRACECTL_TRACEMODE_POS                 (0U)
#define DBGC_MCUTRACECTL_TRACEMODE                     (0x00000003UL)
#define DBGC_MCUTRACECTL_TRACEMODE_0                   (0x00000001UL)
#define DBGC_MCUTRACECTL_TRACEMODE_1                   (0x00000002UL)
#define DBGC_MCUTRACECTL_TRACEIOEN_POS                 (2U)
#define DBGC_MCUTRACECTL_TRACEIOEN                     (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral DCU
*******************************************************************************/
/*  Bit definition for DCU_CTL register  */
#define DCU_CTL_MODE_POS                               (0U)
#define DCU_CTL_MODE                                   (0x00000007UL)
#define DCU_CTL_MODE_0                                 (0x00000001UL)
#define DCU_CTL_MODE_1                                 (0x00000002UL)
#define DCU_CTL_MODE_2                                 (0x00000004UL)
#define DCU_CTL_DATASIZE_POS                           (3U)
#define DCU_CTL_DATASIZE                               (0x00000018UL)
#define DCU_CTL_DATASIZE_0                             (0x00000008UL)
#define DCU_CTL_DATASIZE_1                             (0x00000010UL)
#define DCU_CTL_COMP_TRG_POS                           (8U)
#define DCU_CTL_COMP_TRG                               (0x00000100UL)
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

/*  Bit definition for DCU_INTSEL register  */
#define DCU_INTSEL_INT_OP_POS                          (0U)
#define DCU_INTSEL_INT_OP                              (0x00000001UL)
#define DCU_INTSEL_INT_LS2_POS                         (1U)
#define DCU_INTSEL_INT_LS2                             (0x00000002UL)
#define DCU_INTSEL_INT_EQ2_POS                         (2U)
#define DCU_INTSEL_INT_EQ2                             (0x00000004UL)
#define DCU_INTSEL_INT_GT2_POS                         (3U)
#define DCU_INTSEL_INT_GT2                             (0x00000008UL)
#define DCU_INTSEL_INT_LS1_POS                         (4U)
#define DCU_INTSEL_INT_LS1                             (0x00000010UL)
#define DCU_INTSEL_INT_EQ1_POS                         (5U)
#define DCU_INTSEL_INT_EQ1                             (0x00000020UL)
#define DCU_INTSEL_INT_GT1_POS                         (6U)
#define DCU_INTSEL_INT_GT1                             (0x00000040UL)
#define DCU_INTSEL_INT_WIN_POS                         (7U)
#define DCU_INTSEL_INT_WIN                             (0x00000180UL)
#define DCU_INTSEL_INT_WIN_0                           (0x00000080UL)
#define DCU_INTSEL_INT_WIN_1                           (0x00000100UL)

/*******************************************************************************
                Bit definition for Peripheral DMA
*******************************************************************************/
/*  Bit definition for DMA_EN register  */
#define DMA_EN_EN                                      (0x00000001UL)

/*  Bit definition for DMA_INTSTAT0 register  */
#define DMA_INTSTAT0_TRNERR_POS                        (0U)
#define DMA_INTSTAT0_TRNERR                            (0x0000000FUL)
#define DMA_INTSTAT0_TRNERR_0                          (0x00000001UL)
#define DMA_INTSTAT0_TRNERR_1                          (0x00000002UL)
#define DMA_INTSTAT0_TRNERR_2                          (0x00000004UL)
#define DMA_INTSTAT0_TRNERR_3                          (0x00000008UL)
#define DMA_INTSTAT0_REQERR_POS                        (16U)
#define DMA_INTSTAT0_REQERR                            (0x000F0000UL)
#define DMA_INTSTAT0_REQERR_0                          (0x00010000UL)
#define DMA_INTSTAT0_REQERR_1                          (0x00020000UL)
#define DMA_INTSTAT0_REQERR_2                          (0x00040000UL)
#define DMA_INTSTAT0_REQERR_3                          (0x00080000UL)

/*  Bit definition for DMA_INTSTAT1 register  */
#define DMA_INTSTAT1_TC_POS                            (0U)
#define DMA_INTSTAT1_TC                                (0x0000000FUL)
#define DMA_INTSTAT1_TC_0                              (0x00000001UL)
#define DMA_INTSTAT1_TC_1                              (0x00000002UL)
#define DMA_INTSTAT1_TC_2                              (0x00000004UL)
#define DMA_INTSTAT1_TC_3                              (0x00000008UL)
#define DMA_INTSTAT1_BTC_POS                           (16U)
#define DMA_INTSTAT1_BTC                               (0x000F0000UL)
#define DMA_INTSTAT1_BTC_0                             (0x00010000UL)
#define DMA_INTSTAT1_BTC_1                             (0x00020000UL)
#define DMA_INTSTAT1_BTC_2                             (0x00040000UL)
#define DMA_INTSTAT1_BTC_3                             (0x00080000UL)

/*  Bit definition for DMA_INTMASK0 register  */
#define DMA_INTMASK0_MSKTRNERR_POS                     (0U)
#define DMA_INTMASK0_MSKTRNERR                         (0x0000000FUL)
#define DMA_INTMASK0_MSKTRNERR_0                       (0x00000001UL)
#define DMA_INTMASK0_MSKTRNERR_1                       (0x00000002UL)
#define DMA_INTMASK0_MSKTRNERR_2                       (0x00000004UL)
#define DMA_INTMASK0_MSKTRNERR_3                       (0x00000008UL)
#define DMA_INTMASK0_MSKREQERR_POS                     (16U)
#define DMA_INTMASK0_MSKREQERR                         (0x000F0000UL)
#define DMA_INTMASK0_MSKREQERR_0                       (0x00010000UL)
#define DMA_INTMASK0_MSKREQERR_1                       (0x00020000UL)
#define DMA_INTMASK0_MSKREQERR_2                       (0x00040000UL)
#define DMA_INTMASK0_MSKREQERR_3                       (0x00080000UL)

/*  Bit definition for DMA_INTMASK1 register  */
#define DMA_INTMASK1_MSKTC_POS                         (0U)
#define DMA_INTMASK1_MSKTC                             (0x0000000FUL)
#define DMA_INTMASK1_MSKTC_0                           (0x00000001UL)
#define DMA_INTMASK1_MSKTC_1                           (0x00000002UL)
#define DMA_INTMASK1_MSKTC_2                           (0x00000004UL)
#define DMA_INTMASK1_MSKTC_3                           (0x00000008UL)
#define DMA_INTMASK1_MSKBTC_POS                        (16U)
#define DMA_INTMASK1_MSKBTC                            (0x000F0000UL)
#define DMA_INTMASK1_MSKBTC_0                          (0x00010000UL)
#define DMA_INTMASK1_MSKBTC_1                          (0x00020000UL)
#define DMA_INTMASK1_MSKBTC_2                          (0x00040000UL)
#define DMA_INTMASK1_MSKBTC_3                          (0x00080000UL)

/*  Bit definition for DMA_INTCLR0 register  */
#define DMA_INTCLR0_CLRTRNERR_POS                      (0U)
#define DMA_INTCLR0_CLRTRNERR                          (0x0000000FUL)
#define DMA_INTCLR0_CLRTRNERR_0                        (0x00000001UL)
#define DMA_INTCLR0_CLRTRNERR_1                        (0x00000002UL)
#define DMA_INTCLR0_CLRTRNERR_2                        (0x00000004UL)
#define DMA_INTCLR0_CLRTRNERR_3                        (0x00000008UL)
#define DMA_INTCLR0_CLRREQERR_POS                      (16U)
#define DMA_INTCLR0_CLRREQERR                          (0x000F0000UL)
#define DMA_INTCLR0_CLRREQERR_0                        (0x00010000UL)
#define DMA_INTCLR0_CLRREQERR_1                        (0x00020000UL)
#define DMA_INTCLR0_CLRREQERR_2                        (0x00040000UL)
#define DMA_INTCLR0_CLRREQERR_3                        (0x00080000UL)

/*  Bit definition for DMA_INTCLR1 register  */
#define DMA_INTCLR1_CLRTC_POS                          (0U)
#define DMA_INTCLR1_CLRTC                              (0x0000000FUL)
#define DMA_INTCLR1_CLRTC_0                            (0x00000001UL)
#define DMA_INTCLR1_CLRTC_1                            (0x00000002UL)
#define DMA_INTCLR1_CLRTC_2                            (0x00000004UL)
#define DMA_INTCLR1_CLRTC_3                            (0x00000008UL)
#define DMA_INTCLR1_CLRBTC_POS                         (16U)
#define DMA_INTCLR1_CLRBTC                             (0x000F0000UL)
#define DMA_INTCLR1_CLRBTC_0                           (0x00010000UL)
#define DMA_INTCLR1_CLRBTC_1                           (0x00020000UL)
#define DMA_INTCLR1_CLRBTC_2                           (0x00040000UL)
#define DMA_INTCLR1_CLRBTC_3                           (0x00080000UL)

/*  Bit definition for DMA_CHEN register  */
#define DMA_CHEN_CHEN                                  (0x0000000FUL)
#define DMA_CHEN_CHEN_0                                (0x00000001UL)
#define DMA_CHEN_CHEN_1                                (0x00000002UL)
#define DMA_CHEN_CHEN_2                                (0x00000004UL)
#define DMA_CHEN_CHEN_3                                (0x00000008UL)

/*  Bit definition for DMA_REQSTAT register  */
#define DMA_REQSTAT_CHREQ_POS                          (0U)
#define DMA_REQSTAT_CHREQ                              (0x0000000FUL)
#define DMA_REQSTAT_CHREQ_0                            (0x00000001UL)
#define DMA_REQSTAT_CHREQ_1                            (0x00000002UL)
#define DMA_REQSTAT_CHREQ_2                            (0x00000004UL)
#define DMA_REQSTAT_CHREQ_3                            (0x00000008UL)
#define DMA_REQSTAT_RCFGREQ_POS                        (15U)
#define DMA_REQSTAT_RCFGREQ                            (0x00008000UL)

/*  Bit definition for DMA_CHSTAT register  */
#define DMA_CHSTAT_DMAACT_POS                          (0U)
#define DMA_CHSTAT_DMAACT                              (0x00000001UL)
#define DMA_CHSTAT_RCFGACT_POS                         (1U)
#define DMA_CHSTAT_RCFGACT                             (0x00000002UL)
#define DMA_CHSTAT_CHACT_POS                           (16U)
#define DMA_CHSTAT_CHACT                               (0x000F0000UL)
#define DMA_CHSTAT_CHACT_0                             (0x00010000UL)
#define DMA_CHSTAT_CHACT_1                             (0x00020000UL)
#define DMA_CHSTAT_CHACT_2                             (0x00040000UL)
#define DMA_CHSTAT_CHACT_3                             (0x00080000UL)

/*  Bit definition for DMA_RCFGCTL register  */
#define DMA_RCFGCTL_RCFGEN_POS                         (0U)
#define DMA_RCFGCTL_RCFGEN                             (0x00000001UL)
#define DMA_RCFGCTL_RCFGLLP_POS                        (1U)
#define DMA_RCFGCTL_RCFGLLP                            (0x00000002UL)
#define DMA_RCFGCTL_RCFGCHS_POS                        (8U)
#define DMA_RCFGCTL_RCFGCHS                            (0x00000F00UL)
#define DMA_RCFGCTL_RCFGCHS_0                          (0x00000100UL)
#define DMA_RCFGCTL_RCFGCHS_1                          (0x00000200UL)
#define DMA_RCFGCTL_RCFGCHS_2                          (0x00000400UL)
#define DMA_RCFGCTL_RCFGCHS_3                          (0x00000800UL)
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

/*  Bit definition for DMA_SAR0 register  */
#define DMA_SAR0                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_DAR0 register  */
#define DMA_DAR0                                       (0xFFFFFFFFUL)

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
#define DMA_RPTB_SRPTB_0                               (0x00000001UL)
#define DMA_RPTB_SRPTB_1                               (0x00000002UL)
#define DMA_RPTB_SRPTB_2                               (0x00000004UL)
#define DMA_RPTB_SRPTB_3                               (0x00000008UL)
#define DMA_RPTB_SRPTB_4                               (0x00000010UL)
#define DMA_RPTB_SRPTB_5                               (0x00000020UL)
#define DMA_RPTB_SRPTB_6                               (0x00000040UL)
#define DMA_RPTB_SRPTB_7                               (0x00000080UL)
#define DMA_RPTB_SRPTB_8                               (0x00000100UL)
#define DMA_RPTB_SRPTB_9                               (0x00000200UL)
#define DMA_RPTB_DRPTB_POS                             (16U)
#define DMA_RPTB_DRPTB                                 (0x03FF0000UL)
#define DMA_RPTB_DRPTB_0                               (0x00010000UL)
#define DMA_RPTB_DRPTB_1                               (0x00020000UL)
#define DMA_RPTB_DRPTB_2                               (0x00040000UL)
#define DMA_RPTB_DRPTB_3                               (0x00080000UL)
#define DMA_RPTB_DRPTB_4                               (0x00100000UL)
#define DMA_RPTB_DRPTB_5                               (0x00200000UL)
#define DMA_RPTB_DRPTB_6                               (0x00400000UL)
#define DMA_RPTB_DRPTB_7                               (0x00800000UL)
#define DMA_RPTB_DRPTB_8                               (0x01000000UL)
#define DMA_RPTB_DRPTB_9                               (0x02000000UL)

/*  Bit definition for DMA_SNSEQCTL register  */
#define DMA_SNSEQCTL_SOFFSET_POS                       (0U)
#define DMA_SNSEQCTL_SOFFSET                           (0x000FFFFFUL)
#define DMA_SNSEQCTL_SNSCNT_POS                        (20U)
#define DMA_SNSEQCTL_SNSCNT                            (0xFFF00000UL)

/*  Bit definition for DMA_SNSEQCTLB register  */
#define DMA_SNSEQCTLB_SNSDIST_POS                      (0U)
#define DMA_SNSEQCTLB_SNSDIST                          (0x000FFFFFUL)
#define DMA_SNSEQCTLB_SNSDIST_0                        (0x00000001UL)
#define DMA_SNSEQCTLB_SNSDIST_1                        (0x00000002UL)
#define DMA_SNSEQCTLB_SNSDIST_2                        (0x00000004UL)
#define DMA_SNSEQCTLB_SNSDIST_3                        (0x00000008UL)
#define DMA_SNSEQCTLB_SNSDIST_4                        (0x00000010UL)
#define DMA_SNSEQCTLB_SNSDIST_5                        (0x00000020UL)
#define DMA_SNSEQCTLB_SNSDIST_6                        (0x00000040UL)
#define DMA_SNSEQCTLB_SNSDIST_7                        (0x00000080UL)
#define DMA_SNSEQCTLB_SNSDIST_8                        (0x00000100UL)
#define DMA_SNSEQCTLB_SNSDIST_9                        (0x00000200UL)
#define DMA_SNSEQCTLB_SNSDIST_10                       (0x00000400UL)
#define DMA_SNSEQCTLB_SNSDIST_11                       (0x00000800UL)
#define DMA_SNSEQCTLB_SNSDIST_12                       (0x00001000UL)
#define DMA_SNSEQCTLB_SNSDIST_13                       (0x00002000UL)
#define DMA_SNSEQCTLB_SNSDIST_14                       (0x00004000UL)
#define DMA_SNSEQCTLB_SNSDIST_15                       (0x00008000UL)
#define DMA_SNSEQCTLB_SNSDIST_16                       (0x00010000UL)
#define DMA_SNSEQCTLB_SNSDIST_17                       (0x00020000UL)
#define DMA_SNSEQCTLB_SNSDIST_18                       (0x00040000UL)
#define DMA_SNSEQCTLB_SNSDIST_19                       (0x00080000UL)
#define DMA_SNSEQCTLB_SNSCNTB_POS                      (20U)
#define DMA_SNSEQCTLB_SNSCNTB                          (0xFFF00000UL)
#define DMA_SNSEQCTLB_SNSCNTB_0                        (0x00100000UL)
#define DMA_SNSEQCTLB_SNSCNTB_1                        (0x00200000UL)
#define DMA_SNSEQCTLB_SNSCNTB_2                        (0x00400000UL)
#define DMA_SNSEQCTLB_SNSCNTB_3                        (0x00800000UL)
#define DMA_SNSEQCTLB_SNSCNTB_4                        (0x01000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_5                        (0x02000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_6                        (0x04000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_7                        (0x08000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_8                        (0x10000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_9                        (0x20000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_10                       (0x40000000UL)
#define DMA_SNSEQCTLB_SNSCNTB_11                       (0x80000000UL)

/*  Bit definition for DMA_DNSEQCTL register  */
#define DMA_DNSEQCTL_DOFFSET_POS                       (0U)
#define DMA_DNSEQCTL_DOFFSET                           (0x000FFFFFUL)
#define DMA_DNSEQCTL_DNSCNT_POS                        (20U)
#define DMA_DNSEQCTL_DNSCNT                            (0xFFF00000UL)

/*  Bit definition for DMA_DNSEQCTLB register  */
#define DMA_DNSEQCTLB_DNSDIST_POS                      (0U)
#define DMA_DNSEQCTLB_DNSDIST                          (0x000FFFFFUL)
#define DMA_DNSEQCTLB_DNSDIST_0                        (0x00000001UL)
#define DMA_DNSEQCTLB_DNSDIST_1                        (0x00000002UL)
#define DMA_DNSEQCTLB_DNSDIST_2                        (0x00000004UL)
#define DMA_DNSEQCTLB_DNSDIST_3                        (0x00000008UL)
#define DMA_DNSEQCTLB_DNSDIST_4                        (0x00000010UL)
#define DMA_DNSEQCTLB_DNSDIST_5                        (0x00000020UL)
#define DMA_DNSEQCTLB_DNSDIST_6                        (0x00000040UL)
#define DMA_DNSEQCTLB_DNSDIST_7                        (0x00000080UL)
#define DMA_DNSEQCTLB_DNSDIST_8                        (0x00000100UL)
#define DMA_DNSEQCTLB_DNSDIST_9                        (0x00000200UL)
#define DMA_DNSEQCTLB_DNSDIST_10                       (0x00000400UL)
#define DMA_DNSEQCTLB_DNSDIST_11                       (0x00000800UL)
#define DMA_DNSEQCTLB_DNSDIST_12                       (0x00001000UL)
#define DMA_DNSEQCTLB_DNSDIST_13                       (0x00002000UL)
#define DMA_DNSEQCTLB_DNSDIST_14                       (0x00004000UL)
#define DMA_DNSEQCTLB_DNSDIST_15                       (0x00008000UL)
#define DMA_DNSEQCTLB_DNSDIST_16                       (0x00010000UL)
#define DMA_DNSEQCTLB_DNSDIST_17                       (0x00020000UL)
#define DMA_DNSEQCTLB_DNSDIST_18                       (0x00040000UL)
#define DMA_DNSEQCTLB_DNSDIST_19                       (0x00080000UL)
#define DMA_DNSEQCTLB_DNSCNTB_POS                      (20U)
#define DMA_DNSEQCTLB_DNSCNTB                          (0xFFF00000UL)
#define DMA_DNSEQCTLB_DNSCNTB_0                        (0x00100000UL)
#define DMA_DNSEQCTLB_DNSCNTB_1                        (0x00200000UL)
#define DMA_DNSEQCTLB_DNSCNTB_2                        (0x00400000UL)
#define DMA_DNSEQCTLB_DNSCNTB_3                        (0x00800000UL)
#define DMA_DNSEQCTLB_DNSCNTB_4                        (0x01000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_5                        (0x02000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_6                        (0x04000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_7                        (0x08000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_8                        (0x10000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_9                        (0x20000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_10                       (0x40000000UL)
#define DMA_DNSEQCTLB_DNSCNTB_11                       (0x80000000UL)

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

/*  Bit definition for DMA_MONSAR0 register  */
#define DMA_MONSAR0                                    (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONDAR0 register  */
#define DMA_MONDAR0                                    (0xFFFFFFFFUL)

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

/*  Bit definition for DMA_SAR1 register  */
#define DMA_SAR1                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_DAR1 register  */
#define DMA_DAR1                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONSAR1 register  */
#define DMA_MONSAR1                                    (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONDAR1 register  */
#define DMA_MONDAR1                                    (0xFFFFFFFFUL)

/*  Bit definition for DMA_SAR2 register  */
#define DMA_SAR2                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_DAR2 register  */
#define DMA_DAR2                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONSAR2 register  */
#define DMA_MONSAR2                                    (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONDAR2 register  */
#define DMA_MONDAR2                                    (0xFFFFFFFFUL)

/*  Bit definition for DMA_SAR3 register  */
#define DMA_SAR3                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_DAR3 register  */
#define DMA_DAR3                                       (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONSAR3 register  */
#define DMA_MONSAR3                                    (0xFFFFFFFFUL)

/*  Bit definition for DMA_MONDAR3 register  */
#define DMA_MONDAR3                                    (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral EFM
*******************************************************************************/
/*  Bit definition for EFM_FAPRT register  */
#define EFM_FAPRT_FAPRT                                (0x0000FFFFUL)

/*  Bit definition for EFM_FSTP register  */
#define EFM_FSTP_FSTP                                  (0x00000001UL)

/*  Bit definition for EFM_FRMC register  */
#define EFM_FRMC_SLPMD_POS                             (0U)
#define EFM_FRMC_SLPMD                                 (0x00000001UL)
#define EFM_FRMC_FLWT_POS                              (4U)
#define EFM_FRMC_FLWT                                  (0x000000F0UL)
#define EFM_FRMC_LVM_POS                               (8U)
#define EFM_FRMC_LVM                                   (0x00000100UL)
#define EFM_FRMC_CACHE_POS                             (16U)
#define EFM_FRMC_CACHE                                 (0x00010000UL)
#define EFM_FRMC_CRST_POS                              (24U)
#define EFM_FRMC_CRST                                  (0x01000000UL)

/*  Bit definition for EFM_FWMC register  */
#define EFM_FWMC_PEMODE_POS                            (0U)
#define EFM_FWMC_PEMODE                                (0x00000001UL)
#define EFM_FWMC_PEMOD_POS                             (4U)
#define EFM_FWMC_PEMOD                                 (0x00000070UL)
#define EFM_FWMC_PEMOD_0                               (0x00000010UL)
#define EFM_FWMC_PEMOD_1                               (0x00000020UL)
#define EFM_FWMC_PEMOD_2                               (0x00000040UL)
#define EFM_FWMC_BUSHLDCTL_POS                         (8U)
#define EFM_FWMC_BUSHLDCTL                             (0x00000100UL)

/*  Bit definition for EFM_FSR register  */
#define EFM_FSR_PEWERR_POS                             (0U)
#define EFM_FSR_PEWERR                                 (0x00000001UL)
#define EFM_FSR_PEPRTERR_POS                           (1U)
#define EFM_FSR_PEPRTERR                               (0x00000002UL)
#define EFM_FSR_PGSZERR_POS                            (2U)
#define EFM_FSR_PGSZERR                                (0x00000004UL)
#define EFM_FSR_PGMISMTCH_POS                          (3U)
#define EFM_FSR_PGMISMTCH                              (0x00000008UL)
#define EFM_FSR_OPTEND_POS                             (4U)
#define EFM_FSR_OPTEND                                 (0x00000010UL)
#define EFM_FSR_COLERR_POS                             (5U)
#define EFM_FSR_COLERR                                 (0x00000020UL)
#define EFM_FSR_RDY_POS                                (8U)
#define EFM_FSR_RDY                                    (0x00000100UL)

/*  Bit definition for EFM_FSCLR register  */
#define EFM_FSCLR_PEWERRCLR_POS                        (0U)
#define EFM_FSCLR_PEWERRCLR                            (0x00000001UL)
#define EFM_FSCLR_PEPRTERRCLR_POS                      (1U)
#define EFM_FSCLR_PEPRTERRCLR                          (0x00000002UL)
#define EFM_FSCLR_PGSZERRCLR_POS                       (2U)
#define EFM_FSCLR_PGSZERRCLR                           (0x00000004UL)
#define EFM_FSCLR_PGMISMTCHCLR_POS                     (3U)
#define EFM_FSCLR_PGMISMTCHCLR                         (0x00000008UL)
#define EFM_FSCLR_OPTENDCLR_POS                        (4U)
#define EFM_FSCLR_OPTENDCLR                            (0x00000010UL)
#define EFM_FSCLR_COLERRCLR_POS                        (5U)
#define EFM_FSCLR_COLERRCLR                            (0x00000020UL)

/*  Bit definition for EFM_FITE register  */
#define EFM_FITE_PEERRITE_POS                          (0U)
#define EFM_FITE_PEERRITE                              (0x00000001UL)
#define EFM_FITE_OPTENDITE_POS                         (1U)
#define EFM_FITE_OPTENDITE                             (0x00000002UL)
#define EFM_FITE_COLERRITE_POS                         (2U)
#define EFM_FITE_COLERRITE                             (0x00000004UL)

/*  Bit definition for EFM_FSWP register  */
#define EFM_FSWP_FSWP                                  (0x00000001UL)

/*  Bit definition for EFM_FPMTSW register  */
#define EFM_FPMTSW_FPMTSW                              (0x0007FFFFUL)

/*  Bit definition for EFM_FPMTEW register  */
#define EFM_FPMTEW_FPMTEW                              (0x0007FFFFUL)

/*  Bit definition for EFM_UQID0 register  */
#define EFM_UQID0                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID1 register  */
#define EFM_UQID1                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID2 register  */
#define EFM_UQID2                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_MMF_REMPRT register  */
#define EFM_MMF_REMPRT_REMPRT                          (0x0000FFFFUL)

/*  Bit definition for EFM_MMF_REMCR register  */
#define EFM_MMF_REMCR_RMSIZE_POS                       (0U)
#define EFM_MMF_REMCR_RMSIZE                           (0x0000001FUL)
#define EFM_MMF_REMCR_RMTADDR_POS                      (12U)
#define EFM_MMF_REMCR_RMTADDR                          (0x1FFFF000UL)
#define EFM_MMF_REMCR_EN_POS                           (31U)
#define EFM_MMF_REMCR_EN                               (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral EMB
*******************************************************************************/
/*  Bit definition for EMB_CTL register  */
#define EMB_CTL_PORTINEN_POS                           (0U)
#define EMB_CTL_PORTINEN                               (0x00000001UL)
#define EMB_CTL_CMPEN0_POS                             (1U)
#define EMB_CTL_CMPEN0                                 (0x00000002UL)
#define EMB_CTL_CMPEN1_POS                             (2U)
#define EMB_CTL_CMPEN1                                 (0x00000004UL)
#define EMB_CTL_CMPEN2_POS                             (3U)
#define EMB_CTL_CMPEN2                                 (0x00000008UL)
#define EMB_CTL_OSCSTPEN_POS                           (5U)
#define EMB_CTL_OSCSTPEN                               (0x00000020UL)
#define EMB_CTL_PWMSEN0_POS                            (6U)
#define EMB_CTL_PWMSEN0                                (0x00000040UL)
#define EMB_CTL_PWMSEN1_POS                            (7U)
#define EMB_CTL_PWMSEN1                                (0x00000080UL)
#define EMB_CTL_PWMSEN2_POS                            (8U)
#define EMB_CTL_PWMSEN2                                (0x00000100UL)
#define EMB_CTL_NFSEL_POS                              (28U)
#define EMB_CTL_NFSEL                                  (0x30000000UL)
#define EMB_CTL_NFEN_POS                               (30U)
#define EMB_CTL_NFEN                                   (0x40000000UL)
#define EMB_CTL_INVSEL_POS                             (31U)
#define EMB_CTL_INVSEL                                 (0x80000000UL)

/*  Bit definition for EMB_PWMLV register  */
#define EMB_PWMLV_PWMLV0_POS                           (0U)
#define EMB_PWMLV_PWMLV0                               (0x00000001UL)
#define EMB_PWMLV_PWMLV1_POS                           (1U)
#define EMB_PWMLV_PWMLV1                               (0x00000002UL)
#define EMB_PWMLV_PWMLV2_POS                           (2U)
#define EMB_PWMLV_PWMLV2                               (0x00000004UL)

/*  Bit definition for EMB_SOE register  */
#define EMB_SOE_SOE                                    (0x00000001UL)

/*  Bit definition for EMB_STAT register  */
#define EMB_STAT_PORTINF_POS                           (0U)
#define EMB_STAT_PORTINF                               (0x00000001UL)
#define EMB_STAT_PWMSF_POS                             (1U)
#define EMB_STAT_PWMSF                                 (0x00000002UL)
#define EMB_STAT_CMPF_POS                              (2U)
#define EMB_STAT_CMPF                                  (0x00000004UL)
#define EMB_STAT_OSF_POS                               (3U)
#define EMB_STAT_OSF                                   (0x00000008UL)
#define EMB_STAT_PORTINST_POS                          (4U)
#define EMB_STAT_PORTINST                              (0x00000010UL)
#define EMB_STAT_PWMST_POS                             (5U)
#define EMB_STAT_PWMST                                 (0x00000020UL)

/*  Bit definition for EMB_STATCLR register  */
#define EMB_STATCLR_PORTINFCLR_POS                     (0U)
#define EMB_STATCLR_PORTINFCLR                         (0x00000001UL)
#define EMB_STATCLR_PWMSFCLR_POS                       (1U)
#define EMB_STATCLR_PWMSFCLR                           (0x00000002UL)
#define EMB_STATCLR_CMPFCLR_POS                        (2U)
#define EMB_STATCLR_CMPFCLR                            (0x00000004UL)
#define EMB_STATCLR_OSFCLR_POS                         (3U)
#define EMB_STATCLR_OSFCLR                             (0x00000008UL)

/*  Bit definition for EMB_INTEN register  */
#define EMB_INTEN_PORTINTEN_POS                        (0U)
#define EMB_INTEN_PORTINTEN                            (0x00000001UL)
#define EMB_INTEN_PWMINTEN_POS                         (1U)
#define EMB_INTEN_PWMINTEN                             (0x00000002UL)
#define EMB_INTEN_CMPINTEN_POS                         (2U)
#define EMB_INTEN_CMPINTEN                             (0x00000004UL)
#define EMB_INTEN_OSINTEN_POS                          (3U)
#define EMB_INTEN_OSINTEN                              (0x00000008UL)

/*******************************************************************************
                Bit definition for Peripheral FCM
*******************************************************************************/
/*  Bit definition for FCM_LVR register  */
#define FCM_LVR_LVR                                    (0x0000FFFFUL)
#define FCM_LVR_LVR_0                                  (0x00000001UL)
#define FCM_LVR_LVR_1                                  (0x00000002UL)
#define FCM_LVR_LVR_2                                  (0x00000004UL)
#define FCM_LVR_LVR_3                                  (0x00000008UL)
#define FCM_LVR_LVR_4                                  (0x00000010UL)
#define FCM_LVR_LVR_5                                  (0x00000020UL)
#define FCM_LVR_LVR_6                                  (0x00000040UL)
#define FCM_LVR_LVR_7                                  (0x00000080UL)
#define FCM_LVR_LVR_8                                  (0x00000100UL)
#define FCM_LVR_LVR_9                                  (0x00000200UL)
#define FCM_LVR_LVR_10                                 (0x00000400UL)
#define FCM_LVR_LVR_11                                 (0x00000800UL)
#define FCM_LVR_LVR_12                                 (0x00001000UL)
#define FCM_LVR_LVR_13                                 (0x00002000UL)
#define FCM_LVR_LVR_14                                 (0x00004000UL)
#define FCM_LVR_LVR_15                                 (0x00008000UL)

/*  Bit definition for FCM_UVR register  */
#define FCM_UVR_UVR                                    (0x0000FFFFUL)
#define FCM_UVR_UVR_0                                  (0x00000001UL)
#define FCM_UVR_UVR_1                                  (0x00000002UL)
#define FCM_UVR_UVR_2                                  (0x00000004UL)
#define FCM_UVR_UVR_3                                  (0x00000008UL)
#define FCM_UVR_UVR_4                                  (0x00000010UL)
#define FCM_UVR_UVR_5                                  (0x00000020UL)
#define FCM_UVR_UVR_6                                  (0x00000040UL)
#define FCM_UVR_UVR_7                                  (0x00000080UL)
#define FCM_UVR_UVR_8                                  (0x00000100UL)
#define FCM_UVR_UVR_9                                  (0x00000200UL)
#define FCM_UVR_UVR_10                                 (0x00000400UL)
#define FCM_UVR_UVR_11                                 (0x00000800UL)
#define FCM_UVR_UVR_12                                 (0x00001000UL)
#define FCM_UVR_UVR_13                                 (0x00002000UL)
#define FCM_UVR_UVR_14                                 (0x00004000UL)
#define FCM_UVR_UVR_15                                 (0x00008000UL)

/*  Bit definition for FCM_CNTR register  */
#define FCM_CNTR_CNTR                                  (0x0000FFFFUL)
#define FCM_CNTR_CNTR_0                                (0x00000001UL)
#define FCM_CNTR_CNTR_1                                (0x00000002UL)
#define FCM_CNTR_CNTR_2                                (0x00000004UL)
#define FCM_CNTR_CNTR_3                                (0x00000008UL)
#define FCM_CNTR_CNTR_4                                (0x00000010UL)
#define FCM_CNTR_CNTR_5                                (0x00000020UL)
#define FCM_CNTR_CNTR_6                                (0x00000040UL)
#define FCM_CNTR_CNTR_7                                (0x00000080UL)
#define FCM_CNTR_CNTR_8                                (0x00000100UL)
#define FCM_CNTR_CNTR_9                                (0x00000200UL)
#define FCM_CNTR_CNTR_10                               (0x00000400UL)
#define FCM_CNTR_CNTR_11                               (0x00000800UL)
#define FCM_CNTR_CNTR_12                               (0x00001000UL)
#define FCM_CNTR_CNTR_13                               (0x00002000UL)
#define FCM_CNTR_CNTR_14                               (0x00004000UL)
#define FCM_CNTR_CNTR_15                               (0x00008000UL)

/*  Bit definition for FCM_STR register  */
#define FCM_STR_START                                  (0x00000001UL)

/*  Bit definition for FCM_MCCR register  */
#define FCM_MCCR_MDIVS_POS                             (0U)
#define FCM_MCCR_MDIVS                                 (0x00000003UL)
#define FCM_MCCR_MDIVS_0                               (0x00000001UL)
#define FCM_MCCR_MDIVS_1                               (0x00000002UL)
#define FCM_MCCR_MCKS_POS                              (4U)
#define FCM_MCCR_MCKS                                  (0x000000F0UL)
#define FCM_MCCR_MCKS_0                                (0x00000010UL)
#define FCM_MCCR_MCKS_1                                (0x00000020UL)
#define FCM_MCCR_MCKS_2                                (0x00000040UL)
#define FCM_MCCR_MCKS_3                                (0x00000080UL)

/*  Bit definition for FCM_RCCR register  */
#define FCM_RCCR_RDIVS_POS                             (0U)
#define FCM_RCCR_RDIVS                                 (0x00000003UL)
#define FCM_RCCR_RDIVS_0                               (0x00000001UL)
#define FCM_RCCR_RDIVS_1                               (0x00000002UL)
#define FCM_RCCR_RCKS_POS                              (3U)
#define FCM_RCCR_RCKS                                  (0x00000078UL)
#define FCM_RCCR_RCKS_0                                (0x00000008UL)
#define FCM_RCCR_RCKS_1                                (0x00000010UL)
#define FCM_RCCR_RCKS_2                                (0x00000020UL)
#define FCM_RCCR_RCKS_3                                (0x00000040UL)
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

/*  Bit definition for GPIO_PIDRH register  */
#define GPIO_PIDRH_PIN00_POS                           (0U)
#define GPIO_PIDRH_PIN00                               (0x0001U)
#define GPIO_PIDRH_PIN01_POS                           (1U)
#define GPIO_PIDRH_PIN01                               (0x0002U)
#define GPIO_PIDRH_PIN02_POS                           (2U)
#define GPIO_PIDRH_PIN02                               (0x0004U)

/*  Bit definition for GPIO_PODRH register  */
#define GPIO_PODRH_POUT00_POS                          (0U)
#define GPIO_PODRH_POUT00                              (0x0001U)
#define GPIO_PODRH_POUT01_POS                          (1U)
#define GPIO_PODRH_POUT01                              (0x0002U)
#define GPIO_PODRH_POUT02_POS                          (2U)
#define GPIO_PODRH_POUT02                              (0x0004U)

/*  Bit definition for GPIO_POERH register  */
#define GPIO_POERH_POUTE00_POS                         (0U)
#define GPIO_POERH_POUTE00                             (0x0001U)
#define GPIO_POERH_POUTE01_POS                         (1U)
#define GPIO_POERH_POUTE01                             (0x0002U)
#define GPIO_POERH_POUTE02_POS                         (2U)
#define GPIO_POERH_POUTE02                             (0x0004U)

/*  Bit definition for GPIO_POSRH register  */
#define GPIO_POSRH_POS00_POS                           (0U)
#define GPIO_POSRH_POS00                               (0x0001U)
#define GPIO_POSRH_POS01_POS                           (1U)
#define GPIO_POSRH_POS01                               (0x0002U)
#define GPIO_POSRH_POS02_POS                           (2U)
#define GPIO_POSRH_POS02                               (0x0004U)

/*  Bit definition for GPIO_PORRH register  */
#define GPIO_PORRH_POR00_POS                           (0U)
#define GPIO_PORRH_POR00                               (0x0001U)
#define GPIO_PORRH_POR01_POS                           (1U)
#define GPIO_PORRH_POR01                               (0x0002U)
#define GPIO_PORRH_POR02_POS                           (2U)
#define GPIO_PORRH_POR02                               (0x0004U)

/*  Bit definition for GPIO_POTRH register  */
#define GPIO_POTRH_POT00_POS                           (0U)
#define GPIO_POTRH_POT00                               (0x0001U)
#define GPIO_POTRH_POT01_POS                           (1U)
#define GPIO_POTRH_POT01                               (0x0002U)
#define GPIO_POTRH_POT02_POS                           (2U)
#define GPIO_POTRH_POT02                               (0x0004U)

/*  Bit definition for GPIO_PSPCR register  */
#define GPIO_PSPCR_SPFE                                (0x001FU)
#define GPIO_PSPCR_SPFE_0                              (0x0001U)
#define GPIO_PSPCR_SPFE_1                              (0x0002U)
#define GPIO_PSPCR_SPFE_2                              (0x0004U)
#define GPIO_PSPCR_SPFE_3                              (0x0008U)
#define GPIO_PSPCR_SPFE_4                              (0x0010U)

/*  Bit definition for GPIO_PCCR register  */
#define GPIO_PCCR_BFSEL_POS                            (0U)
#define GPIO_PCCR_BFSEL                                (0x000FU)
#define GPIO_PCCR_BFSEL_0                              (0x0001U)
#define GPIO_PCCR_BFSEL_1                              (0x0002U)
#define GPIO_PCCR_BFSEL_2                              (0x0004U)
#define GPIO_PCCR_BFSEL_3                              (0x0008U)
#define GPIO_PCCR_RDWT_POS                             (14U)
#define GPIO_PCCR_RDWT                                 (0xC000U)
#define GPIO_PCCR_RDWT_0                               (0x4000U)
#define GPIO_PCCR_RDWT_1                               (0x8000U)

/*  Bit definition for GPIO_PINAER register  */
#define GPIO_PINAER_PINAE                              (0x003FU)
#define GPIO_PINAER_PINAE_0                            (0x0001U)
#define GPIO_PINAER_PINAE_1                            (0x0002U)
#define GPIO_PINAER_PINAE_2                            (0x0004U)
#define GPIO_PINAER_PINAE_3                            (0x0008U)
#define GPIO_PINAER_PINAE_4                            (0x0010U)
#define GPIO_PINAER_PINAE_5                            (0x0020U)

/*  Bit definition for GPIO_PWPR register  */
#define GPIO_PWPR_WE_POS                               (0U)
#define GPIO_PWPR_WE                                   (0x0001U)
#define GPIO_PWPR_WP_POS                               (8U)
#define GPIO_PWPR_WP                                   (0xFF00U)
#define GPIO_PWPR_WP_0                                 (0x0100U)
#define GPIO_PWPR_WP_1                                 (0x0200U)
#define GPIO_PWPR_WP_2                                 (0x0400U)
#define GPIO_PWPR_WP_3                                 (0x0800U)
#define GPIO_PWPR_WP_4                                 (0x1000U)
#define GPIO_PWPR_WP_5                                 (0x2000U)
#define GPIO_PWPR_WP_6                                 (0x4000U)
#define GPIO_PWPR_WP_7                                 (0x8000U)

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
#define GPIO_PCR_INTE_POS                              (12U)
#define GPIO_PCR_INTE                                  (0x1000U)
#define GPIO_PCR_LTE_POS                               (14U)
#define GPIO_PCR_LTE                                   (0x4000U)
#define GPIO_PCR_DDIS_POS                              (15U)
#define GPIO_PCR_DDIS                                  (0x8000U)

/*  Bit definition for GPIO_PFSR register  */
#define GPIO_PFSR_FSEL_POS                             (0U)
#define GPIO_PFSR_FSEL                                 (0x003FU)
#define GPIO_PFSR_FSEL_0                               (0x0001U)
#define GPIO_PFSR_FSEL_1                               (0x0002U)
#define GPIO_PFSR_FSEL_2                               (0x0004U)
#define GPIO_PFSR_FSEL_3                               (0x0008U)
#define GPIO_PFSR_FSEL_4                               (0x0010U)
#define GPIO_PFSR_FSEL_5                               (0x0020U)
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
#define I2C_CR1_GCEN_POS                               (6U)
#define I2C_CR1_GCEN                                   (0x00000040UL)
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
#define I2C_SLR0_SLADDR0_0                             (0x00000001UL)
#define I2C_SLR0_SLADDR0_1                             (0x00000002UL)
#define I2C_SLR0_SLADDR0_2                             (0x00000004UL)
#define I2C_SLR0_SLADDR0_3                             (0x00000008UL)
#define I2C_SLR0_SLADDR0_4                             (0x00000010UL)
#define I2C_SLR0_SLADDR0_5                             (0x00000020UL)
#define I2C_SLR0_SLADDR0_6                             (0x00000040UL)
#define I2C_SLR0_SLADDR0_7                             (0x00000080UL)
#define I2C_SLR0_SLADDR0_8                             (0x00000100UL)
#define I2C_SLR0_SLADDR0_9                             (0x00000200UL)
#define I2C_SLR0_SLADDR0EN_POS                         (12U)
#define I2C_SLR0_SLADDR0EN                             (0x00001000UL)
#define I2C_SLR0_ADDRMOD0_POS                          (15U)
#define I2C_SLR0_ADDRMOD0                              (0x00008000UL)

/*  Bit definition for I2C_SLR1 register  */
#define I2C_SLR1_SLADDR1_POS                           (0U)
#define I2C_SLR1_SLADDR1                               (0x000003FFUL)
#define I2C_SLR1_SLADDR1_0                             (0x00000001UL)
#define I2C_SLR1_SLADDR1_1                             (0x00000002UL)
#define I2C_SLR1_SLADDR1_2                             (0x00000004UL)
#define I2C_SLR1_SLADDR1_3                             (0x00000008UL)
#define I2C_SLR1_SLADDR1_4                             (0x00000010UL)
#define I2C_SLR1_SLADDR1_5                             (0x00000020UL)
#define I2C_SLR1_SLADDR1_6                             (0x00000040UL)
#define I2C_SLR1_SLADDR1_7                             (0x00000080UL)
#define I2C_SLR1_SLADDR1_8                             (0x00000100UL)
#define I2C_SLR1_SLADDR1_9                             (0x00000200UL)
#define I2C_SLR1_SLADDR1EN_POS                         (12U)
#define I2C_SLR1_SLADDR1EN                             (0x00001000UL)
#define I2C_SLR1_ADDRMOD1_POS                          (15U)
#define I2C_SLR1_ADDRMOD1                              (0x00008000UL)

/*  Bit definition for I2C_SLTR register  */
#define I2C_SLTR_TOUTLOW_POS                           (0U)
#define I2C_SLTR_TOUTLOW                               (0x0000FFFFUL)
#define I2C_SLTR_TOUTLOW_0                             (0x00000001UL)
#define I2C_SLTR_TOUTLOW_1                             (0x00000002UL)
#define I2C_SLTR_TOUTLOW_2                             (0x00000004UL)
#define I2C_SLTR_TOUTLOW_3                             (0x00000008UL)
#define I2C_SLTR_TOUTLOW_4                             (0x00000010UL)
#define I2C_SLTR_TOUTLOW_5                             (0x00000020UL)
#define I2C_SLTR_TOUTLOW_6                             (0x00000040UL)
#define I2C_SLTR_TOUTLOW_7                             (0x00000080UL)
#define I2C_SLTR_TOUTLOW_8                             (0x00000100UL)
#define I2C_SLTR_TOUTLOW_9                             (0x00000200UL)
#define I2C_SLTR_TOUTLOW_10                            (0x00000400UL)
#define I2C_SLTR_TOUTLOW_11                            (0x00000800UL)
#define I2C_SLTR_TOUTLOW_12                            (0x00001000UL)
#define I2C_SLTR_TOUTLOW_13                            (0x00002000UL)
#define I2C_SLTR_TOUTLOW_14                            (0x00004000UL)
#define I2C_SLTR_TOUTLOW_15                            (0x00008000UL)
#define I2C_SLTR_TOUTHIGH_POS                          (16U)
#define I2C_SLTR_TOUTHIGH                              (0xFFFF0000UL)
#define I2C_SLTR_TOUTHIGH_0                            (0x00010000UL)
#define I2C_SLTR_TOUTHIGH_1                            (0x00020000UL)
#define I2C_SLTR_TOUTHIGH_2                            (0x00040000UL)
#define I2C_SLTR_TOUTHIGH_3                            (0x00080000UL)
#define I2C_SLTR_TOUTHIGH_4                            (0x00100000UL)
#define I2C_SLTR_TOUTHIGH_5                            (0x00200000UL)
#define I2C_SLTR_TOUTHIGH_6                            (0x00400000UL)
#define I2C_SLTR_TOUTHIGH_7                            (0x00800000UL)
#define I2C_SLTR_TOUTHIGH_8                            (0x01000000UL)
#define I2C_SLTR_TOUTHIGH_9                            (0x02000000UL)
#define I2C_SLTR_TOUTHIGH_10                           (0x04000000UL)
#define I2C_SLTR_TOUTHIGH_11                           (0x08000000UL)
#define I2C_SLTR_TOUTHIGH_12                           (0x10000000UL)
#define I2C_SLTR_TOUTHIGH_13                           (0x20000000UL)
#define I2C_SLTR_TOUTHIGH_14                           (0x40000000UL)
#define I2C_SLTR_TOUTHIGH_15                           (0x80000000UL)

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
#define I2C_DTR_DT_0                                   (0x01U)
#define I2C_DTR_DT_1                                   (0x02U)
#define I2C_DTR_DT_2                                   (0x04U)
#define I2C_DTR_DT_3                                   (0x08U)
#define I2C_DTR_DT_4                                   (0x10U)
#define I2C_DTR_DT_5                                   (0x20U)
#define I2C_DTR_DT_6                                   (0x40U)
#define I2C_DTR_DT_7                                   (0x80U)

/*  Bit definition for I2C_DRR register  */
#define I2C_DRR_DR                                     (0xFFU)
#define I2C_DRR_DR_0                                   (0x01U)
#define I2C_DRR_DR_1                                   (0x02U)
#define I2C_DRR_DR_2                                   (0x04U)
#define I2C_DRR_DR_3                                   (0x08U)
#define I2C_DRR_DR_4                                   (0x10U)
#define I2C_DRR_DR_5                                   (0x20U)
#define I2C_DRR_DR_6                                   (0x40U)
#define I2C_DRR_DR_7                                   (0x80U)

/*  Bit definition for I2C_CCR register  */
#define I2C_CCR_SLOWW_POS                              (0U)
#define I2C_CCR_SLOWW                                  (0x0000001FUL)
#define I2C_CCR_SLOWW_0                                (0x00000001UL)
#define I2C_CCR_SLOWW_1                                (0x00000002UL)
#define I2C_CCR_SLOWW_2                                (0x00000004UL)
#define I2C_CCR_SLOWW_3                                (0x00000008UL)
#define I2C_CCR_SLOWW_4                                (0x00000010UL)
#define I2C_CCR_SHIGHW_POS                             (8U)
#define I2C_CCR_SHIGHW                                 (0x00001F00UL)
#define I2C_CCR_SHIGHW_0                               (0x00000100UL)
#define I2C_CCR_SHIGHW_1                               (0x00000200UL)
#define I2C_CCR_SHIGHW_2                               (0x00000400UL)
#define I2C_CCR_SHIGHW_3                               (0x00000800UL)
#define I2C_CCR_SHIGHW_4                               (0x00001000UL)
#define I2C_CCR_FREQ_POS                               (16U)
#define I2C_CCR_FREQ                                   (0x00070000UL)
#define I2C_CCR_FREQ_0                                 (0x00010000UL)
#define I2C_CCR_FREQ_1                                 (0x00020000UL)
#define I2C_CCR_FREQ_2                                 (0x00040000UL)

/*  Bit definition for I2C_FLTR register  */
#define I2C_FLTR_DNF_POS                               (0U)
#define I2C_FLTR_DNF                                   (0x00000003UL)
#define I2C_FLTR_DNF_0                                 (0x00000001UL)
#define I2C_FLTR_DNF_1                                 (0x00000002UL)
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
#define I2S_PR_I2SDIV_0                                (0x00000001UL)
#define I2S_PR_I2SDIV_1                                (0x00000002UL)
#define I2S_PR_I2SDIV_2                                (0x00000004UL)
#define I2S_PR_I2SDIV_3                                (0x00000008UL)
#define I2S_PR_I2SDIV_4                                (0x00000010UL)
#define I2S_PR_I2SDIV_5                                (0x00000020UL)
#define I2S_PR_I2SDIV_6                                (0x00000040UL)
#define I2S_PR_I2SDIV_7                                (0x00000080UL)

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
#define ICG_ICG1_SMPCLK_POS                            (26U)
#define ICG_ICG1_SMPCLK                                (0x0C000000UL)
#define ICG_ICG1_SMPCLK_0                              (0x04000000UL)
#define ICG_ICG1_SMPCLK_1                              (0x08000000UL)
#define ICG_ICG1_NMITRG_POS                            (28U)
#define ICG_ICG1_NMITRG                                (0x10000000UL)
#define ICG_ICG1_NMIEN_POS                             (29U)
#define ICG_ICG1_NMIEN                                 (0x20000000UL)
#define ICG_ICG1_NFEN_POS                              (30U)
#define ICG_ICG1_NFEN                                  (0x40000000UL)
#define ICG_ICG1_NMIICGEN_POS                          (31U)
#define ICG_ICG1_NMIICGEN                              (0x80000000UL)

/*  Bit definition for ICG_ICG2 register  */
#define ICG_ICG2                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG3 register  */
#define ICG_ICG3                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG4 register  */
#define ICG_ICG4                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG5 register  */
#define ICG_ICG5                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG6 register  */
#define ICG_ICG6                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG7 register  */
#define ICG_ICG7                                       (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral INTC
*******************************************************************************/
/*  Bit definition for INTC_NMICR register  */
#define INTC_NMICR_NMITRG_POS                          (0U)
#define INTC_NMICR_NMITRG                              (0x00000001UL)
#define INTC_NMICR_NSMPCLK_POS                         (4U)
#define INTC_NMICR_NSMPCLK                             (0x00000030UL)
#define INTC_NMICR_NSMPCLK_0                           (0x00000010UL)
#define INTC_NMICR_NSMPCLK_1                           (0x00000020UL)
#define INTC_NMICR_NFEN_POS                            (7U)
#define INTC_NMICR_NFEN                                (0x00000080UL)

/*  Bit definition for INTC_NMIENR register  */
#define INTC_NMIENR_NMIENR_POS                         (0U)
#define INTC_NMIENR_NMIENR                             (0x00000001UL)
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
#define INTC_NMIFR_NMIFR_POS                           (0U)
#define INTC_NMIFR_NMIFR                               (0x00000001UL)
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
#define INTC_NMICFR_NMICFR_POS                         (0U)
#define INTC_NMICFR_NMICFR                             (0x00000001UL)
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
#define INTC_WUPEN_CMPI0WUEN_POS                       (19U)
#define INTC_WUPEN_CMPI0WUEN                           (0x00080000UL)
#define INTC_WUPEN_WKTMWUEN_POS                        (20U)
#define INTC_WUPEN_WKTMWUEN                            (0x00100000UL)
#define INTC_WUPEN_RTCALMWUEN_POS                      (21U)
#define INTC_WUPEN_RTCALMWUEN                          (0x00200000UL)
#define INTC_WUPEN_RTCPRDWUEN_POS                      (22U)
#define INTC_WUPEN_RTCPRDWUEN                          (0x00400000UL)
#define INTC_WUPEN_TMR0WUEN_POS                        (23U)
#define INTC_WUPEN_TMR0WUEN                            (0x00800000UL)
#define INTC_WUPEN_RXWUEN_POS                          (25U)
#define INTC_WUPEN_RXWUEN                              (0x02000000UL)

/*  Bit definition for INTC_EIRQFR register  */
#define INTC_EIRQFR_EIRQFR0_POS                        (0U)
#define INTC_EIRQFR_EIRQFR0                            (0x00000001UL)
#define INTC_EIRQFR_EIRQFR1_POS                        (1U)
#define INTC_EIRQFR_EIRQFR1                            (0x00000002UL)
#define INTC_EIRQFR_EIRQFR2_POS                        (2U)
#define INTC_EIRQFR_EIRQFR2                            (0x00000004UL)
#define INTC_EIRQFR_EIRQFR3_POS                        (3U)
#define INTC_EIRQFR_EIRQFR3                            (0x00000008UL)
#define INTC_EIRQFR_EIRQFR4_POS                        (4U)
#define INTC_EIRQFR_EIRQFR4                            (0x00000010UL)
#define INTC_EIRQFR_EIRQFR5_POS                        (5U)
#define INTC_EIRQFR_EIRQFR5                            (0x00000020UL)
#define INTC_EIRQFR_EIRQFR6_POS                        (6U)
#define INTC_EIRQFR_EIRQFR6                            (0x00000040UL)
#define INTC_EIRQFR_EIRQFR7_POS                        (7U)
#define INTC_EIRQFR_EIRQFR7                            (0x00000080UL)
#define INTC_EIRQFR_EIRQFR8_POS                        (8U)
#define INTC_EIRQFR_EIRQFR8                            (0x00000100UL)
#define INTC_EIRQFR_EIRQFR9_POS                        (9U)
#define INTC_EIRQFR_EIRQFR9                            (0x00000200UL)
#define INTC_EIRQFR_EIRQFR10_POS                       (10U)
#define INTC_EIRQFR_EIRQFR10                           (0x00000400UL)
#define INTC_EIRQFR_EIRQFR11_POS                       (11U)
#define INTC_EIRQFR_EIRQFR11                           (0x00000800UL)
#define INTC_EIRQFR_EIRQFR12_POS                       (12U)
#define INTC_EIRQFR_EIRQFR12                           (0x00001000UL)
#define INTC_EIRQFR_EIRQFR13_POS                       (13U)
#define INTC_EIRQFR_EIRQFR13                           (0x00002000UL)
#define INTC_EIRQFR_EIRQFR14_POS                       (14U)
#define INTC_EIRQFR_EIRQFR14                           (0x00004000UL)
#define INTC_EIRQFR_EIRQFR15_POS                       (15U)
#define INTC_EIRQFR_EIRQFR15                           (0x00008000UL)

/*  Bit definition for INTC_EIRQCFR register  */
#define INTC_EIRQCFR_EIRQCFR0_POS                      (0U)
#define INTC_EIRQCFR_EIRQCFR0                          (0x00000001UL)
#define INTC_EIRQCFR_EIRQCFR1_POS                      (1U)
#define INTC_EIRQCFR_EIRQCFR1                          (0x00000002UL)
#define INTC_EIRQCFR_EIRQCFR2_POS                      (2U)
#define INTC_EIRQCFR_EIRQCFR2                          (0x00000004UL)
#define INTC_EIRQCFR_EIRQCFR3_POS                      (3U)
#define INTC_EIRQCFR_EIRQCFR3                          (0x00000008UL)
#define INTC_EIRQCFR_EIRQCFR4_POS                      (4U)
#define INTC_EIRQCFR_EIRQCFR4                          (0x00000010UL)
#define INTC_EIRQCFR_EIRQCFR5_POS                      (5U)
#define INTC_EIRQCFR_EIRQCFR5                          (0x00000020UL)
#define INTC_EIRQCFR_EIRQCFR6_POS                      (6U)
#define INTC_EIRQCFR_EIRQCFR6                          (0x00000040UL)
#define INTC_EIRQCFR_EIRQCFR7_POS                      (7U)
#define INTC_EIRQCFR_EIRQCFR7                          (0x00000080UL)
#define INTC_EIRQCFR_EIRQCFR8_POS                      (8U)
#define INTC_EIRQCFR_EIRQCFR8                          (0x00000100UL)
#define INTC_EIRQCFR_EIRQCFR9_POS                      (9U)
#define INTC_EIRQCFR_EIRQCFR9                          (0x00000200UL)
#define INTC_EIRQCFR_EIRQCFR10_POS                     (10U)
#define INTC_EIRQCFR_EIRQCFR10                         (0x00000400UL)
#define INTC_EIRQCFR_EIRQCFR11_POS                     (11U)
#define INTC_EIRQCFR_EIRQCFR11                         (0x00000800UL)
#define INTC_EIRQCFR_EIRQCFR12_POS                     (12U)
#define INTC_EIRQCFR_EIRQCFR12                         (0x00001000UL)
#define INTC_EIRQCFR_EIRQCFR13_POS                     (13U)
#define INTC_EIRQCFR_EIRQCFR13                         (0x00002000UL)
#define INTC_EIRQCFR_EIRQCFR14_POS                     (14U)
#define INTC_EIRQCFR_EIRQCFR14                         (0x00004000UL)
#define INTC_EIRQCFR_EIRQCFR15_POS                     (15U)
#define INTC_EIRQCFR_EIRQCFR15                         (0x00008000UL)

/*  Bit definition for INTC_SEL register  */
#define INTC_SEL_INTSEL                                (0x000001FFUL)
#define INTC_SEL_INTSEL_0                              (0x00000001UL)
#define INTC_SEL_INTSEL_1                              (0x00000002UL)
#define INTC_SEL_INTSEL_2                              (0x00000004UL)
#define INTC_SEL_INTSEL_3                              (0x00000008UL)
#define INTC_SEL_INTSEL_4                              (0x00000010UL)
#define INTC_SEL_INTSEL_5                              (0x00000020UL)
#define INTC_SEL_INTSEL_6                              (0x00000040UL)
#define INTC_SEL_INTSEL_7                              (0x00000080UL)
#define INTC_SEL_INTSEL_8                              (0x00000100UL)

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
#define KEYSCAN_SCR_KEYOUTSEL_0                        (0x00010000UL)
#define KEYSCAN_SCR_KEYOUTSEL_1                        (0x00020000UL)
#define KEYSCAN_SCR_KEYOUTSEL_2                        (0x00040000UL)
#define KEYSCAN_SCR_CKSEL_POS                          (20U)
#define KEYSCAN_SCR_CKSEL                              (0x00300000UL)
#define KEYSCAN_SCR_CKSEL_0                            (0x00100000UL)
#define KEYSCAN_SCR_CKSEL_1                            (0x00200000UL)
#define KEYSCAN_SCR_T_LLEVEL_POS                       (24U)
#define KEYSCAN_SCR_T_LLEVEL                           (0x1F000000UL)
#define KEYSCAN_SCR_T_LLEVEL_0                         (0x01000000UL)
#define KEYSCAN_SCR_T_LLEVEL_1                         (0x02000000UL)
#define KEYSCAN_SCR_T_LLEVEL_2                         (0x04000000UL)
#define KEYSCAN_SCR_T_LLEVEL_3                         (0x08000000UL)
#define KEYSCAN_SCR_T_LLEVEL_4                         (0x10000000UL)
#define KEYSCAN_SCR_T_HIZ_POS                          (29U)
#define KEYSCAN_SCR_T_HIZ                              (0xE0000000UL)
#define KEYSCAN_SCR_T_HIZ_0                            (0x20000000UL)
#define KEYSCAN_SCR_T_HIZ_1                            (0x40000000UL)
#define KEYSCAN_SCR_T_HIZ_2                            (0x80000000UL)

/*  Bit definition for KEYSCAN_SER register  */
#define KEYSCAN_SER_SEN                                (0x00000001UL)

/*  Bit definition for KEYSCAN_SSR register  */
#define KEYSCAN_SSR_INDEX                              (0x00000007UL)
#define KEYSCAN_SSR_INDEX_0                            (0x00000001UL)
#define KEYSCAN_SSR_INDEX_1                            (0x00000002UL)
#define KEYSCAN_SSR_INDEX_2                            (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral MPU
*******************************************************************************/
/*  Bit definition for MPU_RGD register  */
#define MPU_RGD_MPURGSIZE_POS                          (0U)
#define MPU_RGD_MPURGSIZE                              (0x0000001FUL)
#define MPU_RGD_MPURGSIZE_0                            (0x00000001UL)
#define MPU_RGD_MPURGSIZE_1                            (0x00000002UL)
#define MPU_RGD_MPURGSIZE_2                            (0x00000004UL)
#define MPU_RGD_MPURGSIZE_3                            (0x00000008UL)
#define MPU_RGD_MPURGSIZE_4                            (0x00000010UL)
#define MPU_RGD_MPURGADDR_POS                          (5U)
#define MPU_RGD_MPURGADDR                              (0xFFFFFFE0UL)
#define MPU_RGD_MPURGADDR_0                            (0x00000020UL)
#define MPU_RGD_MPURGADDR_1                            (0x00000040UL)
#define MPU_RGD_MPURGADDR_2                            (0x00000080UL)
#define MPU_RGD_MPURGADDR_3                            (0x00000100UL)
#define MPU_RGD_MPURGADDR_4                            (0x00000200UL)
#define MPU_RGD_MPURGADDR_5                            (0x00000400UL)
#define MPU_RGD_MPURGADDR_6                            (0x00000800UL)
#define MPU_RGD_MPURGADDR_7                            (0x00001000UL)
#define MPU_RGD_MPURGADDR_8                            (0x00002000UL)
#define MPU_RGD_MPURGADDR_9                            (0x00004000UL)
#define MPU_RGD_MPURGADDR_10                           (0x00008000UL)
#define MPU_RGD_MPURGADDR_11                           (0x00010000UL)
#define MPU_RGD_MPURGADDR_12                           (0x00020000UL)
#define MPU_RGD_MPURGADDR_13                           (0x00040000UL)
#define MPU_RGD_MPURGADDR_14                           (0x00080000UL)
#define MPU_RGD_MPURGADDR_15                           (0x00100000UL)
#define MPU_RGD_MPURGADDR_16                           (0x00200000UL)
#define MPU_RGD_MPURGADDR_17                           (0x00400000UL)
#define MPU_RGD_MPURGADDR_18                           (0x00800000UL)
#define MPU_RGD_MPURGADDR_19                           (0x01000000UL)
#define MPU_RGD_MPURGADDR_20                           (0x02000000UL)
#define MPU_RGD_MPURGADDR_21                           (0x04000000UL)
#define MPU_RGD_MPURGADDR_22                           (0x08000000UL)
#define MPU_RGD_MPURGADDR_23                           (0x10000000UL)
#define MPU_RGD_MPURGADDR_24                           (0x20000000UL)
#define MPU_RGD_MPURGADDR_25                           (0x40000000UL)
#define MPU_RGD_MPURGADDR_26                           (0x80000000UL)

/*  Bit definition for MPU_RGCR register  */
#define MPU_RGCR_S2RGRP_POS                            (0U)
#define MPU_RGCR_S2RGRP                                (0x00000001UL)
#define MPU_RGCR_S2RGWP_POS                            (1U)
#define MPU_RGCR_S2RGWP                                (0x00000002UL)
#define MPU_RGCR_S2RGE_POS                             (7U)
#define MPU_RGCR_S2RGE                                 (0x00000080UL)
#define MPU_RGCR_S1RGRP_POS                            (8U)
#define MPU_RGCR_S1RGRP                                (0x00000100UL)
#define MPU_RGCR_S1RGWP_POS                            (9U)
#define MPU_RGCR_S1RGWP                                (0x00000200UL)
#define MPU_RGCR_S1RGE_POS                             (15U)
#define MPU_RGCR_S1RGE                                 (0x00008000UL)
#define MPU_RGCR_FRGRP_POS                             (16U)
#define MPU_RGCR_FRGRP                                 (0x00010000UL)
#define MPU_RGCR_FRGWP_POS                             (17U)
#define MPU_RGCR_FRGWP                                 (0x00020000UL)
#define MPU_RGCR_FRGE_POS                              (23U)
#define MPU_RGCR_FRGE                                  (0x00800000UL)

/*  Bit definition for MPU_CR register  */
#define MPU_CR_SMPU2BRP_POS                            (0U)
#define MPU_CR_SMPU2BRP                                (0x00000001UL)
#define MPU_CR_SMPU2BWP_POS                            (1U)
#define MPU_CR_SMPU2BWP                                (0x00000002UL)
#define MPU_CR_SMPU2ACT_POS                            (2U)
#define MPU_CR_SMPU2ACT                                (0x0000000CUL)
#define MPU_CR_SMPU2ACT_0                              (0x00000004UL)
#define MPU_CR_SMPU2ACT_1                              (0x00000008UL)
#define MPU_CR_SMPU2E_POS                              (7U)
#define MPU_CR_SMPU2E                                  (0x00000080UL)
#define MPU_CR_SMPU1BRP_POS                            (8U)
#define MPU_CR_SMPU1BRP                                (0x00000100UL)
#define MPU_CR_SMPU1BWP_POS                            (9U)
#define MPU_CR_SMPU1BWP                                (0x00000200UL)
#define MPU_CR_SMPU1ACT_POS                            (10U)
#define MPU_CR_SMPU1ACT                                (0x00000C00UL)
#define MPU_CR_SMPU1ACT_0                              (0x00000400UL)
#define MPU_CR_SMPU1ACT_1                              (0x00000800UL)
#define MPU_CR_SMPU1E_POS                              (15U)
#define MPU_CR_SMPU1E                                  (0x00008000UL)
#define MPU_CR_FMPUBRP_POS                             (16U)
#define MPU_CR_FMPUBRP                                 (0x00010000UL)
#define MPU_CR_FMPUBWP_POS                             (17U)
#define MPU_CR_FMPUBWP                                 (0x00020000UL)
#define MPU_CR_FMPUACT_POS                             (18U)
#define MPU_CR_FMPUACT                                 (0x000C0000UL)
#define MPU_CR_FMPUACT_0                               (0x00040000UL)
#define MPU_CR_FMPUACT_1                               (0x00080000UL)
#define MPU_CR_FMPUE_POS                               (23U)
#define MPU_CR_FMPUE                                   (0x00800000UL)

/*  Bit definition for MPU_SR register  */
#define MPU_SR_SMPU2EAF_POS                            (0U)
#define MPU_SR_SMPU2EAF                                (0x00000001UL)
#define MPU_SR_SMPU1EAF_POS                            (8U)
#define MPU_SR_SMPU1EAF                                (0x00000100UL)
#define MPU_SR_FMPUEAF_POS                             (16U)
#define MPU_SR_FMPUEAF                                 (0x00010000UL)

/*  Bit definition for MPU_ECLR register  */
#define MPU_ECLR_SMPU2ECLR_POS                         (0U)
#define MPU_ECLR_SMPU2ECLR                             (0x00000001UL)
#define MPU_ECLR_SMPU1ECLR_POS                         (8U)
#define MPU_ECLR_SMPU1ECLR                             (0x00000100UL)
#define MPU_ECLR_FMPUECLR_POS                          (16U)
#define MPU_ECLR_FMPUECLR                              (0x00010000UL)

/*  Bit definition for MPU_WP register  */
#define MPU_WP_MPUWE_POS                               (0U)
#define MPU_WP_MPUWE                                   (0x00000001UL)
#define MPU_WP_WKEY_POS                                (1U)
#define MPU_WP_WKEY                                    (0x0000FFFEUL)
#define MPU_WP_WKEY_0                                  (0x00000002UL)
#define MPU_WP_WKEY_1                                  (0x00000004UL)
#define MPU_WP_WKEY_2                                  (0x00000008UL)
#define MPU_WP_WKEY_3                                  (0x00000010UL)
#define MPU_WP_WKEY_4                                  (0x00000020UL)
#define MPU_WP_WKEY_5                                  (0x00000040UL)
#define MPU_WP_WKEY_6                                  (0x00000080UL)
#define MPU_WP_WKEY_7                                  (0x00000100UL)
#define MPU_WP_WKEY_8                                  (0x00000200UL)
#define MPU_WP_WKEY_9                                  (0x00000400UL)
#define MPU_WP_WKEY_10                                 (0x00000800UL)
#define MPU_WP_WKEY_11                                 (0x00001000UL)
#define MPU_WP_WKEY_12                                 (0x00002000UL)
#define MPU_WP_WKEY_13                                 (0x00004000UL)
#define MPU_WP_WKEY_14                                 (0x00008000UL)

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
#define MPU_IPPR_MSTPWRP_POS                           (29U)
#define MPU_IPPR_MSTPWRP                               (0x20000000UL)
#define MPU_IPPR_BUSERRE_POS                           (31U)
#define MPU_IPPR_BUSERRE                               (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral OTS
*******************************************************************************/
/*  Bit definition for OTS_CTL register  */
#define OTS_CTL_OTSST_POS                              (0U)
#define OTS_CTL_OTSST                                  (0x0001U)
#define OTS_CTL_OTSCK_POS                              (1U)
#define OTS_CTL_OTSCK                                  (0x0002U)
#define OTS_CTL_OTSIE_POS                              (2U)
#define OTS_CTL_OTSIE                                  (0x0004U)
#define OTS_CTL_TSSTP_POS                              (3U)
#define OTS_CTL_TSSTP                                  (0x0008U)

/*  Bit definition for OTS_DR1 register  */
#define OTS_DR1                                        (0xFFFFU)

/*  Bit definition for OTS_DR2 register  */
#define OTS_DR2                                        (0xFFFFU)

/*  Bit definition for OTS_ECR register  */
#define OTS_ECR                                        (0xFFFFU)

/*  Bit definition for OTS_LPR register  */
#define OTS_LPR_TSOFS_POS                              (0U)
#define OTS_LPR_TSOFS                                  (0x000000FFUL)
#define OTS_LPR_TSOFS_0                                (0x00000001UL)
#define OTS_LPR_TSOFS_1                                (0x00000002UL)
#define OTS_LPR_TSOFS_2                                (0x00000004UL)
#define OTS_LPR_TSOFS_3                                (0x00000008UL)
#define OTS_LPR_TSOFS_4                                (0x00000010UL)
#define OTS_LPR_TSOFS_5                                (0x00000020UL)
#define OTS_LPR_TSOFS_6                                (0x00000040UL)
#define OTS_LPR_TSOFS_7                                (0x00000080UL)
#define OTS_LPR_TSSLP_POS                              (8U)
#define OTS_LPR_TSSLP                                  (0xFFFFFF00UL)
#define OTS_LPR_TSSLP_0                                (0x00000100UL)
#define OTS_LPR_TSSLP_1                                (0x00000200UL)
#define OTS_LPR_TSSLP_2                                (0x00000400UL)
#define OTS_LPR_TSSLP_3                                (0x00000800UL)
#define OTS_LPR_TSSLP_4                                (0x00001000UL)
#define OTS_LPR_TSSLP_5                                (0x00002000UL)
#define OTS_LPR_TSSLP_6                                (0x00004000UL)
#define OTS_LPR_TSSLP_7                                (0x00008000UL)
#define OTS_LPR_TSSLP_8                                (0x00010000UL)
#define OTS_LPR_TSSLP_9                                (0x00020000UL)
#define OTS_LPR_TSSLP_10                               (0x00040000UL)
#define OTS_LPR_TSSLP_11                               (0x00080000UL)
#define OTS_LPR_TSSLP_12                               (0x00100000UL)
#define OTS_LPR_TSSLP_13                               (0x00200000UL)
#define OTS_LPR_TSSLP_14                               (0x00400000UL)
#define OTS_LPR_TSSLP_15                               (0x00800000UL)
#define OTS_LPR_TSSLP_16                               (0x01000000UL)
#define OTS_LPR_TSSLP_17                               (0x02000000UL)
#define OTS_LPR_TSSLP_18                               (0x04000000UL)
#define OTS_LPR_TSSLP_19                               (0x08000000UL)
#define OTS_LPR_TSSLP_20                               (0x10000000UL)
#define OTS_LPR_TSSLP_21                               (0x20000000UL)
#define OTS_LPR_TSSLP_22                               (0x40000000UL)
#define OTS_LPR_TSSLP_23                               (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral PERIC
*******************************************************************************/
/*  Bit definition for PERIC_USBFS_SYCTLREG register  */
#define PERIC_USBFS_SYCTLREG_DFB_POS                   (0U)
#define PERIC_USBFS_SYCTLREG_DFB                       (0x00000001UL)
#define PERIC_USBFS_SYCTLREG_SOFEN_POS                 (1U)
#define PERIC_USBFS_SYCTLREG_SOFEN                     (0x00000002UL)

/*  Bit definition for PERIC_SDIOC_SYCTLREG register  */
#define PERIC_SDIOC_SYCTLREG_SELMMC1_POS               (1U)
#define PERIC_SDIOC_SYCTLREG_SELMMC1                   (0x00000002UL)
#define PERIC_SDIOC_SYCTLREG_SELMMC2_POS               (3U)
#define PERIC_SDIOC_SYCTLREG_SELMMC2                   (0x00000008UL)

/*******************************************************************************
                Bit definition for Peripheral PWC
*******************************************************************************/
/*  Bit definition for PWC_FCG0 register  */
#define PWC_FCG0_SRAMH_POS                             (0U)
#define PWC_FCG0_SRAMH                                 (0x00000001UL)
#define PWC_FCG0_SRAM12_POS                            (4U)
#define PWC_FCG0_SRAM12                                (0x00000010UL)
#define PWC_FCG0_SRAM3_POS                             (8U)
#define PWC_FCG0_SRAM3                                 (0x00000100UL)
#define PWC_FCG0_SRAMRET_POS                           (10U)
#define PWC_FCG0_SRAMRET                               (0x00000400UL)
#define PWC_FCG0_DMA1_POS                              (14U)
#define PWC_FCG0_DMA1                                  (0x00004000UL)
#define PWC_FCG0_DMA2_POS                              (15U)
#define PWC_FCG0_DMA2                                  (0x00008000UL)
#define PWC_FCG0_FCM_POS                               (16U)
#define PWC_FCG0_FCM                                   (0x00010000UL)
#define PWC_FCG0_AOS_POS                               (17U)
#define PWC_FCG0_AOS                                   (0x00020000UL)
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
#define PWC_FCG0_KEY_POS                               (31U)
#define PWC_FCG0_KEY                                   (0x80000000UL)

/*  Bit definition for PWC_FCG1 register  */
#define PWC_FCG1_CAN_POS                               (0U)
#define PWC_FCG1_CAN                                   (0x00000001UL)
#define PWC_FCG1_QSPI_POS                              (3U)
#define PWC_FCG1_QSPI                                  (0x00000008UL)
#define PWC_FCG1_I2C1_POS                              (4U)
#define PWC_FCG1_I2C1                                  (0x00000010UL)
#define PWC_FCG1_I2C2_POS                              (5U)
#define PWC_FCG1_I2C2                                  (0x00000020UL)
#define PWC_FCG1_I2C3_POS                              (6U)
#define PWC_FCG1_I2C3                                  (0x00000040UL)
#define PWC_FCG1_USBFS_POS                             (8U)
#define PWC_FCG1_USBFS                                 (0x00000100UL)
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
#define PWC_FCG1_USART1_POS                            (24U)
#define PWC_FCG1_USART1                                (0x01000000UL)
#define PWC_FCG1_USART2_POS                            (25U)
#define PWC_FCG1_USART2                                (0x02000000UL)
#define PWC_FCG1_USART3_POS                            (26U)
#define PWC_FCG1_USART3                                (0x04000000UL)
#define PWC_FCG1_USART4_POS                            (27U)
#define PWC_FCG1_USART4                                (0x08000000UL)

/*  Bit definition for PWC_FCG2 register  */
#define PWC_FCG2_TIMER0_1_POS                          (0U)
#define PWC_FCG2_TIMER0_1                              (0x00000001UL)
#define PWC_FCG2_TIMER0_2_POS                          (1U)
#define PWC_FCG2_TIMER0_2                              (0x00000002UL)
#define PWC_FCG2_TIMERA_1_POS                          (2U)
#define PWC_FCG2_TIMERA_1                              (0x00000004UL)
#define PWC_FCG2_TIMERA_2_POS                          (3U)
#define PWC_FCG2_TIMERA_2                              (0x00000008UL)
#define PWC_FCG2_TIMERA_3_POS                          (4U)
#define PWC_FCG2_TIMERA_3                              (0x00000010UL)
#define PWC_FCG2_TIMERA_4_POS                          (5U)
#define PWC_FCG2_TIMERA_4                              (0x00000020UL)
#define PWC_FCG2_TIMERA_5_POS                          (6U)
#define PWC_FCG2_TIMERA_5                              (0x00000040UL)
#define PWC_FCG2_TIMERA_6_POS                          (7U)
#define PWC_FCG2_TIMERA_6                              (0x00000080UL)
#define PWC_FCG2_TIMER4_1_POS                          (8U)
#define PWC_FCG2_TIMER4_1                              (0x00000100UL)
#define PWC_FCG2_TIMER4_2_POS                          (9U)
#define PWC_FCG2_TIMER4_2                              (0x00000200UL)
#define PWC_FCG2_TIMER4_3_POS                          (10U)
#define PWC_FCG2_TIMER4_3                              (0x00000400UL)
#define PWC_FCG2_EMB_POS                               (15U)
#define PWC_FCG2_EMB                                   (0x00008000UL)
#define PWC_FCG2_TIMER6_1_POS                          (16U)
#define PWC_FCG2_TIMER6_1                              (0x00010000UL)
#define PWC_FCG2_TIMER6_2_POS                          (17U)
#define PWC_FCG2_TIMER6_2                              (0x00020000UL)
#define PWC_FCG2_TIMER6_3_POS                          (18U)
#define PWC_FCG2_TIMER6_3                              (0x00040000UL)

/*  Bit definition for PWC_FCG3 register  */
#define PWC_FCG3_ADC1_POS                              (0U)
#define PWC_FCG3_ADC1                                  (0x00000001UL)
#define PWC_FCG3_ADC2_POS                              (1U)
#define PWC_FCG3_ADC2                                  (0x00000002UL)
#define PWC_FCG3_CMP_POS                               (8U)
#define PWC_FCG3_CMP                                   (0x00000100UL)
#define PWC_FCG3_OTS_POS                               (12U)
#define PWC_FCG3_OTS                                   (0x00001000UL)

/*  Bit definition for PWC_FCG0PC register  */
#define PWC_FCG0PC_PRT0_POS                            (0U)
#define PWC_FCG0PC_PRT0                                (0x00000001UL)
#define PWC_FCG0PC_FCG0PCWE_POS                        (16U)
#define PWC_FCG0PC_FCG0PCWE                            (0xFFFF0000UL)
#define PWC_FCG0PC_FCG0PCWE_0                          (0x00010000UL)
#define PWC_FCG0PC_FCG0PCWE_1                          (0x00020000UL)
#define PWC_FCG0PC_FCG0PCWE_2                          (0x00040000UL)
#define PWC_FCG0PC_FCG0PCWE_3                          (0x00080000UL)
#define PWC_FCG0PC_FCG0PCWE_4                          (0x00100000UL)
#define PWC_FCG0PC_FCG0PCWE_5                          (0x00200000UL)
#define PWC_FCG0PC_FCG0PCWE_6                          (0x00400000UL)
#define PWC_FCG0PC_FCG0PCWE_7                          (0x00800000UL)
#define PWC_FCG0PC_FCG0PCWE_8                          (0x01000000UL)
#define PWC_FCG0PC_FCG0PCWE_9                          (0x02000000UL)
#define PWC_FCG0PC_FCG0PCWE_10                         (0x04000000UL)
#define PWC_FCG0PC_FCG0PCWE_11                         (0x08000000UL)
#define PWC_FCG0PC_FCG0PCWE_12                         (0x10000000UL)
#define PWC_FCG0PC_FCG0PCWE_13                         (0x20000000UL)
#define PWC_FCG0PC_FCG0PCWE_14                         (0x40000000UL)
#define PWC_FCG0PC_FCG0PCWE_15                         (0x80000000UL)

/*  Bit definition for PWC_WKTCR register  */
#define PWC_WKTCR_WKTMCMP_POS                          (0U)
#define PWC_WKTCR_WKTMCMP                              (0x0FFFU)
#define PWC_WKTCR_WKOVF_POS                            (12U)
#define PWC_WKTCR_WKOVF                                (0x1000U)
#define PWC_WKTCR_WKCKS_POS                            (13U)
#define PWC_WKTCR_WKCKS                                (0x6000U)
#define PWC_WKTCR_WKCKS_0                              (0x2000U)
#define PWC_WKTCR_WKCKS_1                              (0x4000U)
#define PWC_WKTCR_WKTCE_POS                            (15U)
#define PWC_WKTCR_WKTCE                                (0x8000U)

/*  Bit definition for PWC_STPMCR register  */
#define PWC_STPMCR_FLNWT_POS                           (0U)
#define PWC_STPMCR_FLNWT                               (0x0001U)
#define PWC_STPMCR_CKSMRC_POS                          (1U)
#define PWC_STPMCR_CKSMRC                              (0x0002U)
#define PWC_STPMCR_STOP_POS                            (15U)
#define PWC_STPMCR_STOP                                (0x8000U)

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

/*  Bit definition for PWC_RAMOPM register  */
#define PWC_RAMOPM                                     (0xFFFFU)

/*  Bit definition for PWC_PVDICR register  */
#define PWC_PVDICR_PVD1NMIS_POS                        (0U)
#define PWC_PVDICR_PVD1NMIS                            (0x01U)
#define PWC_PVDICR_PVD2NMIS_POS                        (4U)
#define PWC_PVDICR_PVD2NMIS                            (0x10U)

/*  Bit definition for PWC_PVDDSR register  */
#define PWC_PVDDSR_PVD1MON_POS                         (0U)
#define PWC_PVDDSR_PVD1MON                             (0x01U)
#define PWC_PVDDSR_PVD1DETFLG_POS                      (1U)
#define PWC_PVDDSR_PVD1DETFLG                          (0x02U)
#define PWC_PVDDSR_PVD2MON_POS                         (4U)
#define PWC_PVDDSR_PVD2MON                             (0x10U)
#define PWC_PVDDSR_PVD2DETFLG_POS                      (5U)
#define PWC_PVDDSR_PVD2DETFLG                          (0x20U)

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

/*  Bit definition for PWC_PWRC0 register  */
#define PWC_PWRC0_PDMDS_POS                            (0U)
#define PWC_PWRC0_PDMDS                                (0x03U)
#define PWC_PWRC0_PDMDS_0                              (0x01U)
#define PWC_PWRC0_PDMDS_1                              (0x02U)
#define PWC_PWRC0_VVDRSD_POS                           (2U)
#define PWC_PWRC0_VVDRSD                               (0x04U)
#define PWC_PWRC0_RETRAMSD_POS                         (3U)
#define PWC_PWRC0_RETRAMSD                             (0x08U)
#define PWC_PWRC0_IORTN_POS                            (4U)
#define PWC_PWRC0_IORTN                                (0x30U)
#define PWC_PWRC0_IORTN_0                              (0x10U)
#define PWC_PWRC0_IORTN_1                              (0x20U)
#define PWC_PWRC0_PWDN_POS                             (7U)
#define PWC_PWRC0_PWDN                                 (0x80U)

/*  Bit definition for PWC_PWRC1 register  */
#define PWC_PWRC1_VPLLSD_POS                           (0U)
#define PWC_PWRC1_VPLLSD                               (0x01U)
#define PWC_PWRC1_VHRCSD_POS                           (1U)
#define PWC_PWRC1_VHRCSD                               (0x02U)
#define PWC_PWRC1_STPDAS_POS                           (6U)
#define PWC_PWRC1_STPDAS                               (0xC0U)
#define PWC_PWRC1_STPDAS_0                             (0x40U)
#define PWC_PWRC1_STPDAS_1                             (0x80U)

/*  Bit definition for PWC_PWRC2 register  */
#define PWC_PWRC2_DDAS_POS                             (0U)
#define PWC_PWRC2_DDAS                                 (0x0FU)
#define PWC_PWRC2_DDAS_0                               (0x01U)
#define PWC_PWRC2_DDAS_1                               (0x02U)
#define PWC_PWRC2_DDAS_2                               (0x04U)
#define PWC_PWRC2_DDAS_3                               (0x08U)
#define PWC_PWRC2_DVS_POS                              (4U)
#define PWC_PWRC2_DVS                                  (0x30U)
#define PWC_PWRC2_DVS_0                                (0x10U)
#define PWC_PWRC2_DVS_1                                (0x20U)

/*  Bit definition for PWC_PWRC3 register  */
#define PWC_PWRC3_PDTS_POS                             (2U)
#define PWC_PWRC3_PDTS                                 (0x04U)

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
#define PWC_PDWKE2_NMIWKE_POS                          (2U)
#define PWC_PDWKE2_NMIWKE                              (0x04U)
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
#define PWC_PDWKES_NMIEGS_POS                          (6U)
#define PWC_PDWKES_NMIEGS                              (0x40U)

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
#define PWC_PDWKF0_NMIWKF_POS                          (6U)
#define PWC_PDWKF0_NMIWKF                              (0x40U)

/*  Bit definition for PWC_PDWKF1 register  */
#define PWC_PDWKF1_RTCPRDWKF_POS                       (4U)
#define PWC_PDWKF1_RTCPRDWKF                           (0x10U)
#define PWC_PDWKF1_RTCALMWKF_POS                       (5U)
#define PWC_PDWKF1_RTCALMWKF                           (0x20U)
#define PWC_PDWKF1_WKTMWKF_POS                         (7U)
#define PWC_PDWKF1_WKTMWKF                             (0x80U)

/*  Bit definition for PWC_PWCMR register  */
#define PWC_PWCMR_ADBUFE_POS                           (7U)
#define PWC_PWCMR_ADBUFE                               (0x80U)

/*  Bit definition for PWC_MDSWCR register  */
#define PWC_MDSWCR                                     (0xFFU)

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
#define PWC_PVDLCR_PVD1LVL_0                           (0x01U)
#define PWC_PVDLCR_PVD1LVL_1                           (0x02U)
#define PWC_PVDLCR_PVD1LVL_2                           (0x04U)
#define PWC_PVDLCR_PVD2LVL_POS                         (4U)
#define PWC_PVDLCR_PVD2LVL                             (0x70U)
#define PWC_PVDLCR_PVD2LVL_0                           (0x10U)
#define PWC_PVDLCR_PVD2LVL_1                           (0x20U)
#define PWC_PVDLCR_PVD2LVL_2                           (0x40U)

/*  Bit definition for PWC_XTAL32CS register  */
#define PWC_XTAL32CS_CSDIS_POS                         (7U)
#define PWC_XTAL32CS_CSDIS                             (0x80U)

/*******************************************************************************
                Bit definition for Peripheral QSPI
*******************************************************************************/
/*  Bit definition for QSPI_CR register  */
#define QSPI_CR_MDSEL_POS                              (0U)
#define QSPI_CR_MDSEL                                  (0x00000007UL)
#define QSPI_CR_MDSEL_0                                (0x00000001UL)
#define QSPI_CR_MDSEL_1                                (0x00000002UL)
#define QSPI_CR_MDSEL_2                                (0x00000004UL)
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
#define QSPI_CR_DIV_0                                  (0x00010000UL)
#define QSPI_CR_DIV_1                                  (0x00020000UL)
#define QSPI_CR_DIV_2                                  (0x00040000UL)
#define QSPI_CR_DIV_3                                  (0x00080000UL)
#define QSPI_CR_DIV_4                                  (0x00100000UL)
#define QSPI_CR_DIV_5                                  (0x00200000UL)

/*  Bit definition for QSPI_CSCR register  */
#define QSPI_CSCR_SSHW_POS                             (0U)
#define QSPI_CSCR_SSHW                                 (0x0000000FUL)
#define QSPI_CSCR_SSHW_0                               (0x00000001UL)
#define QSPI_CSCR_SSHW_1                               (0x00000002UL)
#define QSPI_CSCR_SSHW_2                               (0x00000004UL)
#define QSPI_CSCR_SSHW_3                               (0x00000008UL)
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
#define QSPI_FCR_DMCYCN_0                              (0x00000100UL)
#define QSPI_FCR_DMCYCN_1                              (0x00000200UL)
#define QSPI_FCR_DMCYCN_2                              (0x00000400UL)
#define QSPI_FCR_DMCYCN_3                              (0x00000800UL)
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
#define QSPI_SR_PFNUM_0                                (0x00000100UL)
#define QSPI_SR_PFNUM_1                                (0x00000200UL)
#define QSPI_SR_PFNUM_2                                (0x00000400UL)
#define QSPI_SR_PFNUM_3                                (0x00000800UL)
#define QSPI_SR_PFNUM_4                                (0x00001000UL)
#define QSPI_SR_PFFUL_POS                              (14U)
#define QSPI_SR_PFFUL                                  (0x00004000UL)
#define QSPI_SR_PFAN_POS                               (15U)
#define QSPI_SR_PFAN                                   (0x00008000UL)

/*  Bit definition for QSPI_DCOM register  */
#define QSPI_DCOM_DCOM                                 (0x000000FFUL)
#define QSPI_DCOM_DCOM_0                               (0x00000001UL)
#define QSPI_DCOM_DCOM_1                               (0x00000002UL)
#define QSPI_DCOM_DCOM_2                               (0x00000004UL)
#define QSPI_DCOM_DCOM_3                               (0x00000008UL)
#define QSPI_DCOM_DCOM_4                               (0x00000010UL)
#define QSPI_DCOM_DCOM_5                               (0x00000020UL)
#define QSPI_DCOM_DCOM_6                               (0x00000040UL)
#define QSPI_DCOM_DCOM_7                               (0x00000080UL)

/*  Bit definition for QSPI_CCMD register  */
#define QSPI_CCMD_RIC                                  (0x000000FFUL)
#define QSPI_CCMD_RIC_0                                (0x00000001UL)
#define QSPI_CCMD_RIC_1                                (0x00000002UL)
#define QSPI_CCMD_RIC_2                                (0x00000004UL)
#define QSPI_CCMD_RIC_3                                (0x00000008UL)
#define QSPI_CCMD_RIC_4                                (0x00000010UL)
#define QSPI_CCMD_RIC_5                                (0x00000020UL)
#define QSPI_CCMD_RIC_6                                (0x00000040UL)
#define QSPI_CCMD_RIC_7                                (0x00000080UL)

/*  Bit definition for QSPI_XCMD register  */
#define QSPI_XCMD_XIPMC                                (0x000000FFUL)
#define QSPI_XCMD_XIPMC_0                              (0x00000001UL)
#define QSPI_XCMD_XIPMC_1                              (0x00000002UL)
#define QSPI_XCMD_XIPMC_2                              (0x00000004UL)
#define QSPI_XCMD_XIPMC_3                              (0x00000008UL)
#define QSPI_XCMD_XIPMC_4                              (0x00000010UL)
#define QSPI_XCMD_XIPMC_5                              (0x00000020UL)
#define QSPI_XCMD_XIPMC_6                              (0x00000040UL)
#define QSPI_XCMD_XIPMC_7                              (0x00000080UL)

/*  Bit definition for QSPI_SR2 register  */
#define QSPI_SR2_RAERCLR_POS                           (7U)
#define QSPI_SR2_RAERCLR                               (0x00000080UL)

/*  Bit definition for QSPI_EXAR register  */
#define QSPI_EXAR_EXADR_POS                            (26U)
#define QSPI_EXAR_EXADR                                (0xFC000000UL)
#define QSPI_EXAR_EXADR_0                              (0x04000000UL)
#define QSPI_EXAR_EXADR_1                              (0x08000000UL)
#define QSPI_EXAR_EXADR_2                              (0x10000000UL)
#define QSPI_EXAR_EXADR_3                              (0x20000000UL)
#define QSPI_EXAR_EXADR_4                              (0x40000000UL)
#define QSPI_EXAR_EXADR_5                              (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral RMU
*******************************************************************************/
/*  Bit definition for RMU_RSTF0 register  */
#define RMU_RSTF0_PORF_POS                             (0U)
#define RMU_RSTF0_PORF                                 (0x0001U)
#define RMU_RSTF0_PINRF_POS                            (1U)
#define RMU_RSTF0_PINRF                                (0x0002U)
#define RMU_RSTF0_BORF_POS                             (2U)
#define RMU_RSTF0_BORF                                 (0x0004U)
#define RMU_RSTF0_PVD1RF_POS                           (3U)
#define RMU_RSTF0_PVD1RF                               (0x0008U)
#define RMU_RSTF0_PVD2RF_POS                           (4U)
#define RMU_RSTF0_PVD2RF                               (0x0010U)
#define RMU_RSTF0_WDRF_POS                             (5U)
#define RMU_RSTF0_WDRF                                 (0x0020U)
#define RMU_RSTF0_SWDRF_POS                            (6U)
#define RMU_RSTF0_SWDRF                                (0x0040U)
#define RMU_RSTF0_PDRF_POS                             (7U)
#define RMU_RSTF0_PDRF                                 (0x0080U)
#define RMU_RSTF0_SWRF_POS                             (8U)
#define RMU_RSTF0_SWRF                                 (0x0100U)
#define RMU_RSTF0_MPUERF_POS                           (9U)
#define RMU_RSTF0_MPUERF                               (0x0200U)
#define RMU_RSTF0_RAPERF_POS                           (10U)
#define RMU_RSTF0_RAPERF                               (0x0400U)
#define RMU_RSTF0_RAECRF_POS                           (11U)
#define RMU_RSTF0_RAECRF                               (0x0800U)
#define RMU_RSTF0_CKFERF_POS                           (12U)
#define RMU_RSTF0_CKFERF                               (0x1000U)
#define RMU_RSTF0_XTALERF_POS                          (13U)
#define RMU_RSTF0_XTALERF                              (0x2000U)
#define RMU_RSTF0_MULTIRF_POS                          (14U)
#define RMU_RSTF0_MULTIRF                              (0x4000U)
#define RMU_RSTF0_CLRF_POS                             (15U)
#define RMU_RSTF0_CLRF                                 (0x8000U)

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
#define RTC_CR1_ALMFCLR_POS                            (4U)
#define RTC_CR1_ALMFCLR                                (0x10U)
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

/*******************************************************************************
                Bit definition for Peripheral SDIOC
*******************************************************************************/
/*  Bit definition for SDIOC_BLKSIZE register  */
#define SDIOC_BLKSIZE_TBS                              (0x0FFFU)
#define SDIOC_BLKSIZE_TBS_0                            (0x0001U)
#define SDIOC_BLKSIZE_TBS_1                            (0x0002U)
#define SDIOC_BLKSIZE_TBS_2                            (0x0004U)
#define SDIOC_BLKSIZE_TBS_3                            (0x0008U)
#define SDIOC_BLKSIZE_TBS_4                            (0x0010U)
#define SDIOC_BLKSIZE_TBS_5                            (0x0020U)
#define SDIOC_BLKSIZE_TBS_6                            (0x0040U)
#define SDIOC_BLKSIZE_TBS_7                            (0x0080U)
#define SDIOC_BLKSIZE_TBS_8                            (0x0100U)
#define SDIOC_BLKSIZE_TBS_9                            (0x0200U)
#define SDIOC_BLKSIZE_TBS_10                           (0x0400U)
#define SDIOC_BLKSIZE_TBS_11                           (0x0800U)

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
#define SDIOC_TOUTCON_DTO_0                            (0x01U)
#define SDIOC_TOUTCON_DTO_1                            (0x02U)
#define SDIOC_TOUTCON_DTO_2                            (0x04U)
#define SDIOC_TOUTCON_DTO_3                            (0x08U)

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
#define SRAMC_WTCR_SRAM12_RWT_POS                      (0U)
#define SRAMC_WTCR_SRAM12_RWT                          (0x00000007UL)
#define SRAMC_WTCR_SRAM12_RWT_0                        (0x00000001UL)
#define SRAMC_WTCR_SRAM12_RWT_1                        (0x00000002UL)
#define SRAMC_WTCR_SRAM12_RWT_2                        (0x00000004UL)
#define SRAMC_WTCR_SRAM12_WWT_POS                      (4U)
#define SRAMC_WTCR_SRAM12_WWT                          (0x00000070UL)
#define SRAMC_WTCR_SRAM12_WWT_0                        (0x00000010UL)
#define SRAMC_WTCR_SRAM12_WWT_1                        (0x00000020UL)
#define SRAMC_WTCR_SRAM12_WWT_2                        (0x00000040UL)
#define SRAMC_WTCR_SRAM3_RWT_POS                       (8U)
#define SRAMC_WTCR_SRAM3_RWT                           (0x00000700UL)
#define SRAMC_WTCR_SRAM3_RWT_0                         (0x00000100UL)
#define SRAMC_WTCR_SRAM3_RWT_1                         (0x00000200UL)
#define SRAMC_WTCR_SRAM3_RWT_2                         (0x00000400UL)
#define SRAMC_WTCR_SRAM3_WWT_POS                       (12U)
#define SRAMC_WTCR_SRAM3_WWT                           (0x00007000UL)
#define SRAMC_WTCR_SRAM3_WWT_0                         (0x00001000UL)
#define SRAMC_WTCR_SRAM3_WWT_1                         (0x00002000UL)
#define SRAMC_WTCR_SRAM3_WWT_2                         (0x00004000UL)
#define SRAMC_WTCR_SRAMH_RWT_POS                       (16U)
#define SRAMC_WTCR_SRAMH_RWT                           (0x00070000UL)
#define SRAMC_WTCR_SRAMH_RWT_0                         (0x00010000UL)
#define SRAMC_WTCR_SRAMH_RWT_1                         (0x00020000UL)
#define SRAMC_WTCR_SRAMH_RWT_2                         (0x00040000UL)
#define SRAMC_WTCR_SRAMH_WWT_POS                       (20U)
#define SRAMC_WTCR_SRAMH_WWT                           (0x00700000UL)
#define SRAMC_WTCR_SRAMH_WWT_0                         (0x00100000UL)
#define SRAMC_WTCR_SRAMH_WWT_1                         (0x00200000UL)
#define SRAMC_WTCR_SRAMH_WWT_2                         (0x00400000UL)
#define SRAMC_WTCR_SRAMR_RWT_POS                       (24U)
#define SRAMC_WTCR_SRAMR_RWT                           (0x07000000UL)
#define SRAMC_WTCR_SRAMR_RWT_0                         (0x01000000UL)
#define SRAMC_WTCR_SRAMR_RWT_1                         (0x02000000UL)
#define SRAMC_WTCR_SRAMR_RWT_2                         (0x04000000UL)
#define SRAMC_WTCR_SRAMR_WWT_POS                       (28U)
#define SRAMC_WTCR_SRAMR_WWT                           (0x70000000UL)
#define SRAMC_WTCR_SRAMR_WWT_0                         (0x10000000UL)
#define SRAMC_WTCR_SRAMR_WWT_1                         (0x20000000UL)
#define SRAMC_WTCR_SRAMR_WWT_2                         (0x40000000UL)

/*  Bit definition for SRAMC_WTPR register  */
#define SRAMC_WTPR_WTPRC_POS                           (0U)
#define SRAMC_WTPR_WTPRC                               (0x00000001UL)
#define SRAMC_WTPR_WTPRKW_POS                          (1U)
#define SRAMC_WTPR_WTPRKW                              (0x000000FEUL)
#define SRAMC_WTPR_WTPRKW_0                            (0x00000002UL)
#define SRAMC_WTPR_WTPRKW_1                            (0x00000004UL)
#define SRAMC_WTPR_WTPRKW_2                            (0x00000008UL)
#define SRAMC_WTPR_WTPRKW_3                            (0x00000010UL)
#define SRAMC_WTPR_WTPRKW_4                            (0x00000020UL)
#define SRAMC_WTPR_WTPRKW_5                            (0x00000040UL)
#define SRAMC_WTPR_WTPRKW_6                            (0x00000080UL)

/*  Bit definition for SRAMC_CKCR register  */
#define SRAMC_CKCR_PYOAD_POS                           (0U)
#define SRAMC_CKCR_PYOAD                               (0x00000001UL)
#define SRAMC_CKCR_ECCOAD_POS                          (16U)
#define SRAMC_CKCR_ECCOAD                              (0x00010000UL)
#define SRAMC_CKCR_ECCMOD_POS                          (24U)
#define SRAMC_CKCR_ECCMOD                              (0x03000000UL)
#define SRAMC_CKCR_ECCMOD_0                            (0x01000000UL)
#define SRAMC_CKCR_ECCMOD_1                            (0x02000000UL)

/*  Bit definition for SRAMC_CKPR register  */
#define SRAMC_CKPR_CKPRC_POS                           (0U)
#define SRAMC_CKPR_CKPRC                               (0x00000001UL)
#define SRAMC_CKPR_CKPRKW_POS                          (1U)
#define SRAMC_CKPR_CKPRKW                              (0x000000FEUL)
#define SRAMC_CKPR_CKPRKW_0                            (0x00000002UL)
#define SRAMC_CKPR_CKPRKW_1                            (0x00000004UL)
#define SRAMC_CKPR_CKPRKW_2                            (0x00000008UL)
#define SRAMC_CKPR_CKPRKW_3                            (0x00000010UL)
#define SRAMC_CKPR_CKPRKW_4                            (0x00000020UL)
#define SRAMC_CKPR_CKPRKW_5                            (0x00000040UL)
#define SRAMC_CKPR_CKPRKW_6                            (0x00000080UL)

/*  Bit definition for SRAMC_CKSR register  */
#define SRAMC_CKSR_SRAM3_1ERR_POS                      (0U)
#define SRAMC_CKSR_SRAM3_1ERR                          (0x00000001UL)
#define SRAMC_CKSR_SRAM3_2ERR_POS                      (1U)
#define SRAMC_CKSR_SRAM3_2ERR                          (0x00000002UL)
#define SRAMC_CKSR_SRAM12_PYERR_POS                    (2U)
#define SRAMC_CKSR_SRAM12_PYERR                        (0x00000004UL)
#define SRAMC_CKSR_SRAMH_PYERR_POS                     (3U)
#define SRAMC_CKSR_SRAMH_PYERR                         (0x00000008UL)
#define SRAMC_CKSR_SRAMR_PYERR_POS                     (4U)
#define SRAMC_CKSR_SRAMR_PYERR                         (0x00000010UL)

/*******************************************************************************
                Bit definition for Peripheral SWDT
*******************************************************************************/
/*  Bit definition for SWDT_SR register  */
#define SWDT_SR_CNT_POS                                (0U)
#define SWDT_SR_CNT                                    (0x0000FFFFUL)
#define SWDT_SR_CNT_0                                  (0x00000001UL)
#define SWDT_SR_CNT_1                                  (0x00000002UL)
#define SWDT_SR_CNT_2                                  (0x00000004UL)
#define SWDT_SR_CNT_3                                  (0x00000008UL)
#define SWDT_SR_CNT_4                                  (0x00000010UL)
#define SWDT_SR_CNT_5                                  (0x00000020UL)
#define SWDT_SR_CNT_6                                  (0x00000040UL)
#define SWDT_SR_CNT_7                                  (0x00000080UL)
#define SWDT_SR_CNT_8                                  (0x00000100UL)
#define SWDT_SR_CNT_9                                  (0x00000200UL)
#define SWDT_SR_CNT_10                                 (0x00000400UL)
#define SWDT_SR_CNT_11                                 (0x00000800UL)
#define SWDT_SR_CNT_12                                 (0x00001000UL)
#define SWDT_SR_CNT_13                                 (0x00002000UL)
#define SWDT_SR_CNT_14                                 (0x00004000UL)
#define SWDT_SR_CNT_15                                 (0x00008000UL)
#define SWDT_SR_UDF_POS                                (16U)
#define SWDT_SR_UDF                                    (0x00010000UL)
#define SWDT_SR_REF_POS                                (17U)
#define SWDT_SR_REF                                    (0x00020000UL)

/*  Bit definition for SWDT_RR register  */
#define SWDT_RR_RF                                     (0x0000FFFFUL)
#define SWDT_RR_RF_0                                   (0x00000001UL)
#define SWDT_RR_RF_1                                   (0x00000002UL)
#define SWDT_RR_RF_2                                   (0x00000004UL)
#define SWDT_RR_RF_3                                   (0x00000008UL)
#define SWDT_RR_RF_4                                   (0x00000010UL)
#define SWDT_RR_RF_5                                   (0x00000020UL)
#define SWDT_RR_RF_6                                   (0x00000040UL)
#define SWDT_RR_RF_7                                   (0x00000080UL)
#define SWDT_RR_RF_8                                   (0x00000100UL)
#define SWDT_RR_RF_9                                   (0x00000200UL)
#define SWDT_RR_RF_10                                  (0x00000400UL)
#define SWDT_RR_RF_11                                  (0x00000800UL)
#define SWDT_RR_RF_12                                  (0x00001000UL)
#define SWDT_RR_RF_13                                  (0x00002000UL)
#define SWDT_RR_RF_14                                  (0x00004000UL)
#define SWDT_RR_RF_15                                  (0x00008000UL)

/*******************************************************************************
                Bit definition for Peripheral TMR0
*******************************************************************************/
/*  Bit definition for TMR0_CNTAR register  */
#define TMR0_CNTAR_CNTA                                (0x0000FFFFUL)
#define TMR0_CNTAR_CNTA_0                              (0x00000001UL)
#define TMR0_CNTAR_CNTA_1                              (0x00000002UL)
#define TMR0_CNTAR_CNTA_2                              (0x00000004UL)
#define TMR0_CNTAR_CNTA_3                              (0x00000008UL)
#define TMR0_CNTAR_CNTA_4                              (0x00000010UL)
#define TMR0_CNTAR_CNTA_5                              (0x00000020UL)
#define TMR0_CNTAR_CNTA_6                              (0x00000040UL)
#define TMR0_CNTAR_CNTA_7                              (0x00000080UL)
#define TMR0_CNTAR_CNTA_8                              (0x00000100UL)
#define TMR0_CNTAR_CNTA_9                              (0x00000200UL)
#define TMR0_CNTAR_CNTA_10                             (0x00000400UL)
#define TMR0_CNTAR_CNTA_11                             (0x00000800UL)
#define TMR0_CNTAR_CNTA_12                             (0x00001000UL)
#define TMR0_CNTAR_CNTA_13                             (0x00002000UL)
#define TMR0_CNTAR_CNTA_14                             (0x00004000UL)
#define TMR0_CNTAR_CNTA_15                             (0x00008000UL)

/*  Bit definition for TMR0_CNTBR register  */
#define TMR0_CNTBR_CNTB                                (0x0000FFFFUL)
#define TMR0_CNTBR_CNTB_0                              (0x00000001UL)
#define TMR0_CNTBR_CNTB_1                              (0x00000002UL)
#define TMR0_CNTBR_CNTB_2                              (0x00000004UL)
#define TMR0_CNTBR_CNTB_3                              (0x00000008UL)
#define TMR0_CNTBR_CNTB_4                              (0x00000010UL)
#define TMR0_CNTBR_CNTB_5                              (0x00000020UL)
#define TMR0_CNTBR_CNTB_6                              (0x00000040UL)
#define TMR0_CNTBR_CNTB_7                              (0x00000080UL)
#define TMR0_CNTBR_CNTB_8                              (0x00000100UL)
#define TMR0_CNTBR_CNTB_9                              (0x00000200UL)
#define TMR0_CNTBR_CNTB_10                             (0x00000400UL)
#define TMR0_CNTBR_CNTB_11                             (0x00000800UL)
#define TMR0_CNTBR_CNTB_12                             (0x00001000UL)
#define TMR0_CNTBR_CNTB_13                             (0x00002000UL)
#define TMR0_CNTBR_CNTB_14                             (0x00004000UL)
#define TMR0_CNTBR_CNTB_15                             (0x00008000UL)

/*  Bit definition for TMR0_CMPAR register  */
#define TMR0_CMPAR_CMPA                                (0x0000FFFFUL)
#define TMR0_CMPAR_CMPA_0                              (0x00000001UL)
#define TMR0_CMPAR_CMPA_1                              (0x00000002UL)
#define TMR0_CMPAR_CMPA_2                              (0x00000004UL)
#define TMR0_CMPAR_CMPA_3                              (0x00000008UL)
#define TMR0_CMPAR_CMPA_4                              (0x00000010UL)
#define TMR0_CMPAR_CMPA_5                              (0x00000020UL)
#define TMR0_CMPAR_CMPA_6                              (0x00000040UL)
#define TMR0_CMPAR_CMPA_7                              (0x00000080UL)
#define TMR0_CMPAR_CMPA_8                              (0x00000100UL)
#define TMR0_CMPAR_CMPA_9                              (0x00000200UL)
#define TMR0_CMPAR_CMPA_10                             (0x00000400UL)
#define TMR0_CMPAR_CMPA_11                             (0x00000800UL)
#define TMR0_CMPAR_CMPA_12                             (0x00001000UL)
#define TMR0_CMPAR_CMPA_13                             (0x00002000UL)
#define TMR0_CMPAR_CMPA_14                             (0x00004000UL)
#define TMR0_CMPAR_CMPA_15                             (0x00008000UL)

/*  Bit definition for TMR0_CMPBR register  */
#define TMR0_CMPBR_CMPB                                (0x0000FFFFUL)
#define TMR0_CMPBR_CMPB_0                              (0x00000001UL)
#define TMR0_CMPBR_CMPB_1                              (0x00000002UL)
#define TMR0_CMPBR_CMPB_2                              (0x00000004UL)
#define TMR0_CMPBR_CMPB_3                              (0x00000008UL)
#define TMR0_CMPBR_CMPB_4                              (0x00000010UL)
#define TMR0_CMPBR_CMPB_5                              (0x00000020UL)
#define TMR0_CMPBR_CMPB_6                              (0x00000040UL)
#define TMR0_CMPBR_CMPB_7                              (0x00000080UL)
#define TMR0_CMPBR_CMPB_8                              (0x00000100UL)
#define TMR0_CMPBR_CMPB_9                              (0x00000200UL)
#define TMR0_CMPBR_CMPB_10                             (0x00000400UL)
#define TMR0_CMPBR_CMPB_11                             (0x00000800UL)
#define TMR0_CMPBR_CMPB_12                             (0x00001000UL)
#define TMR0_CMPBR_CMPB_13                             (0x00002000UL)
#define TMR0_CMPBR_CMPB_14                             (0x00004000UL)
#define TMR0_CMPBR_CMPB_15                             (0x00008000UL)

/*  Bit definition for TMR0_BCONR register  */
#define TMR0_BCONR_CSTA_POS                            (0U)
#define TMR0_BCONR_CSTA                                (0x00000001UL)
#define TMR0_BCONR_CAPMDA_POS                          (1U)
#define TMR0_BCONR_CAPMDA                              (0x00000002UL)
#define TMR0_BCONR_INTENA_POS                          (2U)
#define TMR0_BCONR_INTENA                              (0x00000004UL)
#define TMR0_BCONR_CKDIVA_POS                          (4U)
#define TMR0_BCONR_CKDIVA                              (0x000000F0UL)
#define TMR0_BCONR_CKDIVA_0                            (0x00000010UL)
#define TMR0_BCONR_CKDIVA_1                            (0x00000020UL)
#define TMR0_BCONR_CKDIVA_2                            (0x00000040UL)
#define TMR0_BCONR_CKDIVA_3                            (0x00000080UL)
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
#define TMR0_BCONR_CKDIVB_0                            (0x00100000UL)
#define TMR0_BCONR_CKDIVB_1                            (0x00200000UL)
#define TMR0_BCONR_CKDIVB_2                            (0x00400000UL)
#define TMR0_BCONR_CKDIVB_3                            (0x00800000UL)
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
#define TMR4_CCSR_CKDIV_0                              (0x0001U)
#define TMR4_CCSR_CKDIV_1                              (0x0002U)
#define TMR4_CCSR_CKDIV_2                              (0x0004U)
#define TMR4_CCSR_CKDIV_3                              (0x0008U)
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
#define TMR4_CVPR_ZIM_0                                (0x0001U)
#define TMR4_CVPR_ZIM_1                                (0x0002U)
#define TMR4_CVPR_ZIM_2                                (0x0004U)
#define TMR4_CVPR_ZIM_3                                (0x0008U)
#define TMR4_CVPR_PIM_POS                              (4U)
#define TMR4_CVPR_PIM                                  (0x00F0U)
#define TMR4_CVPR_PIM_0                                (0x0010U)
#define TMR4_CVPR_PIM_1                                (0x0020U)
#define TMR4_CVPR_PIM_2                                (0x0040U)
#define TMR4_CVPR_PIM_3                                (0x0080U)
#define TMR4_CVPR_ZIC_POS                              (8U)
#define TMR4_CVPR_ZIC                                  (0x0F00U)
#define TMR4_CVPR_ZIC_0                                (0x0100U)
#define TMR4_CVPR_ZIC_1                                (0x0200U)
#define TMR4_CVPR_ZIC_2                                (0x0400U)
#define TMR4_CVPR_ZIC_3                                (0x0800U)
#define TMR4_CVPR_PIC_POS                              (12U)
#define TMR4_CVPR_PIC                                  (0xF000U)
#define TMR4_CVPR_PIC_0                                (0x1000U)
#define TMR4_CVPR_PIC_1                                (0x2000U)
#define TMR4_CVPR_PIC_2                                (0x4000U)
#define TMR4_CVPR_PIC_3                                (0x8000U)

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
#define TMR4_POCR_DIVCK_0                              (0x0001U)
#define TMR4_POCR_DIVCK_1                              (0x0002U)
#define TMR4_POCR_DIVCK_2                              (0x0004U)
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
#define TMR4_SCSR_EVTOS_0                              (0x0004U)
#define TMR4_SCSR_EVTOS_1                              (0x0008U)
#define TMR4_SCSR_EVTOS_2                              (0x0010U)
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
#define TMR4_SCMR_AMC_0                                (0x0001U)
#define TMR4_SCMR_AMC_1                                (0x0002U)
#define TMR4_SCMR_AMC_2                                (0x0004U)
#define TMR4_SCMR_AMC_3                                (0x0008U)
#define TMR4_SCMR_MZCE_POS                             (6U)
#define TMR4_SCMR_MZCE                                 (0x0040U)
#define TMR4_SCMR_MPCE_POS                             (7U)
#define TMR4_SCMR_MPCE                                 (0x0080U)

/*  Bit definition for TMR4_ECSR register  */
#define TMR4_ECSR_HOLD_POS                             (7U)
#define TMR4_ECSR_HOLD                                 (0x0080U)

/*******************************************************************************
                Bit definition for Peripheral TMR4CR
*******************************************************************************/
/*  Bit definition for TMR4CR_ECER1 register  */
#define TMR4CR_ECER1_EMBVAL                            (0x00000003UL)
#define TMR4CR_ECER1_EMBVAL_0                          (0x00000001UL)
#define TMR4CR_ECER1_EMBVAL_1                          (0x00000002UL)

/*  Bit definition for TMR4CR_ECER2 register  */
#define TMR4CR_ECER2_EMBVAL                            (0x00000003UL)
#define TMR4CR_ECER2_EMBVAL_0                          (0x00000001UL)
#define TMR4CR_ECER2_EMBVAL_1                          (0x00000002UL)

/*  Bit definition for TMR4CR_ECER3 register  */
#define TMR4CR_ECER3_EMBVAL                            (0x00000003UL)
#define TMR4CR_ECER3_EMBVAL_0                          (0x00000001UL)
#define TMR4CR_ECER3_EMBVAL_1                          (0x00000002UL)

/*******************************************************************************
                Bit definition for Peripheral TMR6
*******************************************************************************/
/*  Bit definition for TMR6_CNTER register  */
#define TMR6_CNTER_CNT                                 (0x0000FFFFUL)
#define TMR6_CNTER_CNT_0                               (0x00000001UL)
#define TMR6_CNTER_CNT_1                               (0x00000002UL)
#define TMR6_CNTER_CNT_2                               (0x00000004UL)
#define TMR6_CNTER_CNT_3                               (0x00000008UL)
#define TMR6_CNTER_CNT_4                               (0x00000010UL)
#define TMR6_CNTER_CNT_5                               (0x00000020UL)
#define TMR6_CNTER_CNT_6                               (0x00000040UL)
#define TMR6_CNTER_CNT_7                               (0x00000080UL)
#define TMR6_CNTER_CNT_8                               (0x00000100UL)
#define TMR6_CNTER_CNT_9                               (0x00000200UL)
#define TMR6_CNTER_CNT_10                              (0x00000400UL)
#define TMR6_CNTER_CNT_11                              (0x00000800UL)
#define TMR6_CNTER_CNT_12                              (0x00001000UL)
#define TMR6_CNTER_CNT_13                              (0x00002000UL)
#define TMR6_CNTER_CNT_14                              (0x00004000UL)
#define TMR6_CNTER_CNT_15                              (0x00008000UL)

/*  Bit definition for TMR6_PERAR register  */
#define TMR6_PERAR_PERA                                (0x0000FFFFUL)
#define TMR6_PERAR_PERA_0                              (0x00000001UL)
#define TMR6_PERAR_PERA_1                              (0x00000002UL)
#define TMR6_PERAR_PERA_2                              (0x00000004UL)
#define TMR6_PERAR_PERA_3                              (0x00000008UL)
#define TMR6_PERAR_PERA_4                              (0x00000010UL)
#define TMR6_PERAR_PERA_5                              (0x00000020UL)
#define TMR6_PERAR_PERA_6                              (0x00000040UL)
#define TMR6_PERAR_PERA_7                              (0x00000080UL)
#define TMR6_PERAR_PERA_8                              (0x00000100UL)
#define TMR6_PERAR_PERA_9                              (0x00000200UL)
#define TMR6_PERAR_PERA_10                             (0x00000400UL)
#define TMR6_PERAR_PERA_11                             (0x00000800UL)
#define TMR6_PERAR_PERA_12                             (0x00001000UL)
#define TMR6_PERAR_PERA_13                             (0x00002000UL)
#define TMR6_PERAR_PERA_14                             (0x00004000UL)
#define TMR6_PERAR_PERA_15                             (0x00008000UL)

/*  Bit definition for TMR6_PERBR register  */
#define TMR6_PERBR_PERB                                (0x0000FFFFUL)
#define TMR6_PERBR_PERB_0                              (0x00000001UL)
#define TMR6_PERBR_PERB_1                              (0x00000002UL)
#define TMR6_PERBR_PERB_2                              (0x00000004UL)
#define TMR6_PERBR_PERB_3                              (0x00000008UL)
#define TMR6_PERBR_PERB_4                              (0x00000010UL)
#define TMR6_PERBR_PERB_5                              (0x00000020UL)
#define TMR6_PERBR_PERB_6                              (0x00000040UL)
#define TMR6_PERBR_PERB_7                              (0x00000080UL)
#define TMR6_PERBR_PERB_8                              (0x00000100UL)
#define TMR6_PERBR_PERB_9                              (0x00000200UL)
#define TMR6_PERBR_PERB_10                             (0x00000400UL)
#define TMR6_PERBR_PERB_11                             (0x00000800UL)
#define TMR6_PERBR_PERB_12                             (0x00001000UL)
#define TMR6_PERBR_PERB_13                             (0x00002000UL)
#define TMR6_PERBR_PERB_14                             (0x00004000UL)
#define TMR6_PERBR_PERB_15                             (0x00008000UL)

/*  Bit definition for TMR6_PERCR register  */
#define TMR6_PERCR_PERC                                (0x0000FFFFUL)
#define TMR6_PERCR_PERC_0                              (0x00000001UL)
#define TMR6_PERCR_PERC_1                              (0x00000002UL)
#define TMR6_PERCR_PERC_2                              (0x00000004UL)
#define TMR6_PERCR_PERC_3                              (0x00000008UL)
#define TMR6_PERCR_PERC_4                              (0x00000010UL)
#define TMR6_PERCR_PERC_5                              (0x00000020UL)
#define TMR6_PERCR_PERC_6                              (0x00000040UL)
#define TMR6_PERCR_PERC_7                              (0x00000080UL)
#define TMR6_PERCR_PERC_8                              (0x00000100UL)
#define TMR6_PERCR_PERC_9                              (0x00000200UL)
#define TMR6_PERCR_PERC_10                             (0x00000400UL)
#define TMR6_PERCR_PERC_11                             (0x00000800UL)
#define TMR6_PERCR_PERC_12                             (0x00001000UL)
#define TMR6_PERCR_PERC_13                             (0x00002000UL)
#define TMR6_PERCR_PERC_14                             (0x00004000UL)
#define TMR6_PERCR_PERC_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCMAR register  */
#define TMR6_GCMAR_GCMA                                (0x0000FFFFUL)
#define TMR6_GCMAR_GCMA_0                              (0x00000001UL)
#define TMR6_GCMAR_GCMA_1                              (0x00000002UL)
#define TMR6_GCMAR_GCMA_2                              (0x00000004UL)
#define TMR6_GCMAR_GCMA_3                              (0x00000008UL)
#define TMR6_GCMAR_GCMA_4                              (0x00000010UL)
#define TMR6_GCMAR_GCMA_5                              (0x00000020UL)
#define TMR6_GCMAR_GCMA_6                              (0x00000040UL)
#define TMR6_GCMAR_GCMA_7                              (0x00000080UL)
#define TMR6_GCMAR_GCMA_8                              (0x00000100UL)
#define TMR6_GCMAR_GCMA_9                              (0x00000200UL)
#define TMR6_GCMAR_GCMA_10                             (0x00000400UL)
#define TMR6_GCMAR_GCMA_11                             (0x00000800UL)
#define TMR6_GCMAR_GCMA_12                             (0x00001000UL)
#define TMR6_GCMAR_GCMA_13                             (0x00002000UL)
#define TMR6_GCMAR_GCMA_14                             (0x00004000UL)
#define TMR6_GCMAR_GCMA_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCMBR register  */
#define TMR6_GCMBR_GCMB                                (0x0000FFFFUL)
#define TMR6_GCMBR_GCMB_0                              (0x00000001UL)
#define TMR6_GCMBR_GCMB_1                              (0x00000002UL)
#define TMR6_GCMBR_GCMB_2                              (0x00000004UL)
#define TMR6_GCMBR_GCMB_3                              (0x00000008UL)
#define TMR6_GCMBR_GCMB_4                              (0x00000010UL)
#define TMR6_GCMBR_GCMB_5                              (0x00000020UL)
#define TMR6_GCMBR_GCMB_6                              (0x00000040UL)
#define TMR6_GCMBR_GCMB_7                              (0x00000080UL)
#define TMR6_GCMBR_GCMB_8                              (0x00000100UL)
#define TMR6_GCMBR_GCMB_9                              (0x00000200UL)
#define TMR6_GCMBR_GCMB_10                             (0x00000400UL)
#define TMR6_GCMBR_GCMB_11                             (0x00000800UL)
#define TMR6_GCMBR_GCMB_12                             (0x00001000UL)
#define TMR6_GCMBR_GCMB_13                             (0x00002000UL)
#define TMR6_GCMBR_GCMB_14                             (0x00004000UL)
#define TMR6_GCMBR_GCMB_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCMCR register  */
#define TMR6_GCMCR_GCMC                                (0x0000FFFFUL)
#define TMR6_GCMCR_GCMC_0                              (0x00000001UL)
#define TMR6_GCMCR_GCMC_1                              (0x00000002UL)
#define TMR6_GCMCR_GCMC_2                              (0x00000004UL)
#define TMR6_GCMCR_GCMC_3                              (0x00000008UL)
#define TMR6_GCMCR_GCMC_4                              (0x00000010UL)
#define TMR6_GCMCR_GCMC_5                              (0x00000020UL)
#define TMR6_GCMCR_GCMC_6                              (0x00000040UL)
#define TMR6_GCMCR_GCMC_7                              (0x00000080UL)
#define TMR6_GCMCR_GCMC_8                              (0x00000100UL)
#define TMR6_GCMCR_GCMC_9                              (0x00000200UL)
#define TMR6_GCMCR_GCMC_10                             (0x00000400UL)
#define TMR6_GCMCR_GCMC_11                             (0x00000800UL)
#define TMR6_GCMCR_GCMC_12                             (0x00001000UL)
#define TMR6_GCMCR_GCMC_13                             (0x00002000UL)
#define TMR6_GCMCR_GCMC_14                             (0x00004000UL)
#define TMR6_GCMCR_GCMC_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCMDR register  */
#define TMR6_GCMDR_GCMD                                (0x0000FFFFUL)
#define TMR6_GCMDR_GCMD_0                              (0x00000001UL)
#define TMR6_GCMDR_GCMD_1                              (0x00000002UL)
#define TMR6_GCMDR_GCMD_2                              (0x00000004UL)
#define TMR6_GCMDR_GCMD_3                              (0x00000008UL)
#define TMR6_GCMDR_GCMD_4                              (0x00000010UL)
#define TMR6_GCMDR_GCMD_5                              (0x00000020UL)
#define TMR6_GCMDR_GCMD_6                              (0x00000040UL)
#define TMR6_GCMDR_GCMD_7                              (0x00000080UL)
#define TMR6_GCMDR_GCMD_8                              (0x00000100UL)
#define TMR6_GCMDR_GCMD_9                              (0x00000200UL)
#define TMR6_GCMDR_GCMD_10                             (0x00000400UL)
#define TMR6_GCMDR_GCMD_11                             (0x00000800UL)
#define TMR6_GCMDR_GCMD_12                             (0x00001000UL)
#define TMR6_GCMDR_GCMD_13                             (0x00002000UL)
#define TMR6_GCMDR_GCMD_14                             (0x00004000UL)
#define TMR6_GCMDR_GCMD_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCMER register  */
#define TMR6_GCMER_GCME                                (0x0000FFFFUL)
#define TMR6_GCMER_GCME_0                              (0x00000001UL)
#define TMR6_GCMER_GCME_1                              (0x00000002UL)
#define TMR6_GCMER_GCME_2                              (0x00000004UL)
#define TMR6_GCMER_GCME_3                              (0x00000008UL)
#define TMR6_GCMER_GCME_4                              (0x00000010UL)
#define TMR6_GCMER_GCME_5                              (0x00000020UL)
#define TMR6_GCMER_GCME_6                              (0x00000040UL)
#define TMR6_GCMER_GCME_7                              (0x00000080UL)
#define TMR6_GCMER_GCME_8                              (0x00000100UL)
#define TMR6_GCMER_GCME_9                              (0x00000200UL)
#define TMR6_GCMER_GCME_10                             (0x00000400UL)
#define TMR6_GCMER_GCME_11                             (0x00000800UL)
#define TMR6_GCMER_GCME_12                             (0x00001000UL)
#define TMR6_GCMER_GCME_13                             (0x00002000UL)
#define TMR6_GCMER_GCME_14                             (0x00004000UL)
#define TMR6_GCMER_GCME_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCMFR register  */
#define TMR6_GCMFR_GCMF                                (0x0000FFFFUL)
#define TMR6_GCMFR_GCMF_0                              (0x00000001UL)
#define TMR6_GCMFR_GCMF_1                              (0x00000002UL)
#define TMR6_GCMFR_GCMF_2                              (0x00000004UL)
#define TMR6_GCMFR_GCMF_3                              (0x00000008UL)
#define TMR6_GCMFR_GCMF_4                              (0x00000010UL)
#define TMR6_GCMFR_GCMF_5                              (0x00000020UL)
#define TMR6_GCMFR_GCMF_6                              (0x00000040UL)
#define TMR6_GCMFR_GCMF_7                              (0x00000080UL)
#define TMR6_GCMFR_GCMF_8                              (0x00000100UL)
#define TMR6_GCMFR_GCMF_9                              (0x00000200UL)
#define TMR6_GCMFR_GCMF_10                             (0x00000400UL)
#define TMR6_GCMFR_GCMF_11                             (0x00000800UL)
#define TMR6_GCMFR_GCMF_12                             (0x00001000UL)
#define TMR6_GCMFR_GCMF_13                             (0x00002000UL)
#define TMR6_GCMFR_GCMF_14                             (0x00004000UL)
#define TMR6_GCMFR_GCMF_15                             (0x00008000UL)

/*  Bit definition for TMR6_SCMAR register  */
#define TMR6_SCMAR_SCMA                                (0x0000FFFFUL)
#define TMR6_SCMAR_SCMA_0                              (0x00000001UL)
#define TMR6_SCMAR_SCMA_1                              (0x00000002UL)
#define TMR6_SCMAR_SCMA_2                              (0x00000004UL)
#define TMR6_SCMAR_SCMA_3                              (0x00000008UL)
#define TMR6_SCMAR_SCMA_4                              (0x00000010UL)
#define TMR6_SCMAR_SCMA_5                              (0x00000020UL)
#define TMR6_SCMAR_SCMA_6                              (0x00000040UL)
#define TMR6_SCMAR_SCMA_7                              (0x00000080UL)
#define TMR6_SCMAR_SCMA_8                              (0x00000100UL)
#define TMR6_SCMAR_SCMA_9                              (0x00000200UL)
#define TMR6_SCMAR_SCMA_10                             (0x00000400UL)
#define TMR6_SCMAR_SCMA_11                             (0x00000800UL)
#define TMR6_SCMAR_SCMA_12                             (0x00001000UL)
#define TMR6_SCMAR_SCMA_13                             (0x00002000UL)
#define TMR6_SCMAR_SCMA_14                             (0x00004000UL)
#define TMR6_SCMAR_SCMA_15                             (0x00008000UL)

/*  Bit definition for TMR6_SCMBR register  */
#define TMR6_SCMBR_SCMB                                (0x0000FFFFUL)
#define TMR6_SCMBR_SCMB_0                              (0x00000001UL)
#define TMR6_SCMBR_SCMB_1                              (0x00000002UL)
#define TMR6_SCMBR_SCMB_2                              (0x00000004UL)
#define TMR6_SCMBR_SCMB_3                              (0x00000008UL)
#define TMR6_SCMBR_SCMB_4                              (0x00000010UL)
#define TMR6_SCMBR_SCMB_5                              (0x00000020UL)
#define TMR6_SCMBR_SCMB_6                              (0x00000040UL)
#define TMR6_SCMBR_SCMB_7                              (0x00000080UL)
#define TMR6_SCMBR_SCMB_8                              (0x00000100UL)
#define TMR6_SCMBR_SCMB_9                              (0x00000200UL)
#define TMR6_SCMBR_SCMB_10                             (0x00000400UL)
#define TMR6_SCMBR_SCMB_11                             (0x00000800UL)
#define TMR6_SCMBR_SCMB_12                             (0x00001000UL)
#define TMR6_SCMBR_SCMB_13                             (0x00002000UL)
#define TMR6_SCMBR_SCMB_14                             (0x00004000UL)
#define TMR6_SCMBR_SCMB_15                             (0x00008000UL)

/*  Bit definition for TMR6_SCMCR register  */
#define TMR6_SCMCR_SCMC                                (0x0000FFFFUL)
#define TMR6_SCMCR_SCMC_0                              (0x00000001UL)
#define TMR6_SCMCR_SCMC_1                              (0x00000002UL)
#define TMR6_SCMCR_SCMC_2                              (0x00000004UL)
#define TMR6_SCMCR_SCMC_3                              (0x00000008UL)
#define TMR6_SCMCR_SCMC_4                              (0x00000010UL)
#define TMR6_SCMCR_SCMC_5                              (0x00000020UL)
#define TMR6_SCMCR_SCMC_6                              (0x00000040UL)
#define TMR6_SCMCR_SCMC_7                              (0x00000080UL)
#define TMR6_SCMCR_SCMC_8                              (0x00000100UL)
#define TMR6_SCMCR_SCMC_9                              (0x00000200UL)
#define TMR6_SCMCR_SCMC_10                             (0x00000400UL)
#define TMR6_SCMCR_SCMC_11                             (0x00000800UL)
#define TMR6_SCMCR_SCMC_12                             (0x00001000UL)
#define TMR6_SCMCR_SCMC_13                             (0x00002000UL)
#define TMR6_SCMCR_SCMC_14                             (0x00004000UL)
#define TMR6_SCMCR_SCMC_15                             (0x00008000UL)

/*  Bit definition for TMR6_SCMDR register  */
#define TMR6_SCMDR_SCMD                                (0x0000FFFFUL)
#define TMR6_SCMDR_SCMD_0                              (0x00000001UL)
#define TMR6_SCMDR_SCMD_1                              (0x00000002UL)
#define TMR6_SCMDR_SCMD_2                              (0x00000004UL)
#define TMR6_SCMDR_SCMD_3                              (0x00000008UL)
#define TMR6_SCMDR_SCMD_4                              (0x00000010UL)
#define TMR6_SCMDR_SCMD_5                              (0x00000020UL)
#define TMR6_SCMDR_SCMD_6                              (0x00000040UL)
#define TMR6_SCMDR_SCMD_7                              (0x00000080UL)
#define TMR6_SCMDR_SCMD_8                              (0x00000100UL)
#define TMR6_SCMDR_SCMD_9                              (0x00000200UL)
#define TMR6_SCMDR_SCMD_10                             (0x00000400UL)
#define TMR6_SCMDR_SCMD_11                             (0x00000800UL)
#define TMR6_SCMDR_SCMD_12                             (0x00001000UL)
#define TMR6_SCMDR_SCMD_13                             (0x00002000UL)
#define TMR6_SCMDR_SCMD_14                             (0x00004000UL)
#define TMR6_SCMDR_SCMD_15                             (0x00008000UL)

/*  Bit definition for TMR6_SCMER register  */
#define TMR6_SCMER_SCME                                (0x0000FFFFUL)
#define TMR6_SCMER_SCME_0                              (0x00000001UL)
#define TMR6_SCMER_SCME_1                              (0x00000002UL)
#define TMR6_SCMER_SCME_2                              (0x00000004UL)
#define TMR6_SCMER_SCME_3                              (0x00000008UL)
#define TMR6_SCMER_SCME_4                              (0x00000010UL)
#define TMR6_SCMER_SCME_5                              (0x00000020UL)
#define TMR6_SCMER_SCME_6                              (0x00000040UL)
#define TMR6_SCMER_SCME_7                              (0x00000080UL)
#define TMR6_SCMER_SCME_8                              (0x00000100UL)
#define TMR6_SCMER_SCME_9                              (0x00000200UL)
#define TMR6_SCMER_SCME_10                             (0x00000400UL)
#define TMR6_SCMER_SCME_11                             (0x00000800UL)
#define TMR6_SCMER_SCME_12                             (0x00001000UL)
#define TMR6_SCMER_SCME_13                             (0x00002000UL)
#define TMR6_SCMER_SCME_14                             (0x00004000UL)
#define TMR6_SCMER_SCME_15                             (0x00008000UL)

/*  Bit definition for TMR6_SCMFR register  */
#define TMR6_SCMFR_SCMF                                (0x0000FFFFUL)
#define TMR6_SCMFR_SCMF_0                              (0x00000001UL)
#define TMR6_SCMFR_SCMF_1                              (0x00000002UL)
#define TMR6_SCMFR_SCMF_2                              (0x00000004UL)
#define TMR6_SCMFR_SCMF_3                              (0x00000008UL)
#define TMR6_SCMFR_SCMF_4                              (0x00000010UL)
#define TMR6_SCMFR_SCMF_5                              (0x00000020UL)
#define TMR6_SCMFR_SCMF_6                              (0x00000040UL)
#define TMR6_SCMFR_SCMF_7                              (0x00000080UL)
#define TMR6_SCMFR_SCMF_8                              (0x00000100UL)
#define TMR6_SCMFR_SCMF_9                              (0x00000200UL)
#define TMR6_SCMFR_SCMF_10                             (0x00000400UL)
#define TMR6_SCMFR_SCMF_11                             (0x00000800UL)
#define TMR6_SCMFR_SCMF_12                             (0x00001000UL)
#define TMR6_SCMFR_SCMF_13                             (0x00002000UL)
#define TMR6_SCMFR_SCMF_14                             (0x00004000UL)
#define TMR6_SCMFR_SCMF_15                             (0x00008000UL)

/*  Bit definition for TMR6_DTUAR register  */
#define TMR6_DTUAR_DTUA                                (0x0000FFFFUL)
#define TMR6_DTUAR_DTUA_0                              (0x00000001UL)
#define TMR6_DTUAR_DTUA_1                              (0x00000002UL)
#define TMR6_DTUAR_DTUA_2                              (0x00000004UL)
#define TMR6_DTUAR_DTUA_3                              (0x00000008UL)
#define TMR6_DTUAR_DTUA_4                              (0x00000010UL)
#define TMR6_DTUAR_DTUA_5                              (0x00000020UL)
#define TMR6_DTUAR_DTUA_6                              (0x00000040UL)
#define TMR6_DTUAR_DTUA_7                              (0x00000080UL)
#define TMR6_DTUAR_DTUA_8                              (0x00000100UL)
#define TMR6_DTUAR_DTUA_9                              (0x00000200UL)
#define TMR6_DTUAR_DTUA_10                             (0x00000400UL)
#define TMR6_DTUAR_DTUA_11                             (0x00000800UL)
#define TMR6_DTUAR_DTUA_12                             (0x00001000UL)
#define TMR6_DTUAR_DTUA_13                             (0x00002000UL)
#define TMR6_DTUAR_DTUA_14                             (0x00004000UL)
#define TMR6_DTUAR_DTUA_15                             (0x00008000UL)

/*  Bit definition for TMR6_DTDAR register  */
#define TMR6_DTDAR_DTDA                                (0x0000FFFFUL)
#define TMR6_DTDAR_DTDA_0                              (0x00000001UL)
#define TMR6_DTDAR_DTDA_1                              (0x00000002UL)
#define TMR6_DTDAR_DTDA_2                              (0x00000004UL)
#define TMR6_DTDAR_DTDA_3                              (0x00000008UL)
#define TMR6_DTDAR_DTDA_4                              (0x00000010UL)
#define TMR6_DTDAR_DTDA_5                              (0x00000020UL)
#define TMR6_DTDAR_DTDA_6                              (0x00000040UL)
#define TMR6_DTDAR_DTDA_7                              (0x00000080UL)
#define TMR6_DTDAR_DTDA_8                              (0x00000100UL)
#define TMR6_DTDAR_DTDA_9                              (0x00000200UL)
#define TMR6_DTDAR_DTDA_10                             (0x00000400UL)
#define TMR6_DTDAR_DTDA_11                             (0x00000800UL)
#define TMR6_DTDAR_DTDA_12                             (0x00001000UL)
#define TMR6_DTDAR_DTDA_13                             (0x00002000UL)
#define TMR6_DTDAR_DTDA_14                             (0x00004000UL)
#define TMR6_DTDAR_DTDA_15                             (0x00008000UL)

/*  Bit definition for TMR6_DTUBR register  */
#define TMR6_DTUBR_DTUB                                (0x0000FFFFUL)
#define TMR6_DTUBR_DTUB_0                              (0x00000001UL)
#define TMR6_DTUBR_DTUB_1                              (0x00000002UL)
#define TMR6_DTUBR_DTUB_2                              (0x00000004UL)
#define TMR6_DTUBR_DTUB_3                              (0x00000008UL)
#define TMR6_DTUBR_DTUB_4                              (0x00000010UL)
#define TMR6_DTUBR_DTUB_5                              (0x00000020UL)
#define TMR6_DTUBR_DTUB_6                              (0x00000040UL)
#define TMR6_DTUBR_DTUB_7                              (0x00000080UL)
#define TMR6_DTUBR_DTUB_8                              (0x00000100UL)
#define TMR6_DTUBR_DTUB_9                              (0x00000200UL)
#define TMR6_DTUBR_DTUB_10                             (0x00000400UL)
#define TMR6_DTUBR_DTUB_11                             (0x00000800UL)
#define TMR6_DTUBR_DTUB_12                             (0x00001000UL)
#define TMR6_DTUBR_DTUB_13                             (0x00002000UL)
#define TMR6_DTUBR_DTUB_14                             (0x00004000UL)
#define TMR6_DTUBR_DTUB_15                             (0x00008000UL)

/*  Bit definition for TMR6_DTDBR register  */
#define TMR6_DTDBR_DTDB                                (0x0000FFFFUL)
#define TMR6_DTDBR_DTDB_0                              (0x00000001UL)
#define TMR6_DTDBR_DTDB_1                              (0x00000002UL)
#define TMR6_DTDBR_DTDB_2                              (0x00000004UL)
#define TMR6_DTDBR_DTDB_3                              (0x00000008UL)
#define TMR6_DTDBR_DTDB_4                              (0x00000010UL)
#define TMR6_DTDBR_DTDB_5                              (0x00000020UL)
#define TMR6_DTDBR_DTDB_6                              (0x00000040UL)
#define TMR6_DTDBR_DTDB_7                              (0x00000080UL)
#define TMR6_DTDBR_DTDB_8                              (0x00000100UL)
#define TMR6_DTDBR_DTDB_9                              (0x00000200UL)
#define TMR6_DTDBR_DTDB_10                             (0x00000400UL)
#define TMR6_DTDBR_DTDB_11                             (0x00000800UL)
#define TMR6_DTDBR_DTDB_12                             (0x00001000UL)
#define TMR6_DTDBR_DTDB_13                             (0x00002000UL)
#define TMR6_DTDBR_DTDB_14                             (0x00004000UL)
#define TMR6_DTDBR_DTDB_15                             (0x00008000UL)

/*  Bit definition for TMR6_GCONR register  */
#define TMR6_GCONR_START_POS                           (0U)
#define TMR6_GCONR_START                               (0x00000001UL)
#define TMR6_GCONR_MODE_POS                            (1U)
#define TMR6_GCONR_MODE                                (0x0000000EUL)
#define TMR6_GCONR_MODE_0                              (0x00000002UL)
#define TMR6_GCONR_MODE_1                              (0x00000004UL)
#define TMR6_GCONR_MODE_2                              (0x00000008UL)
#define TMR6_GCONR_CKDIV_POS                           (4U)
#define TMR6_GCONR_CKDIV                               (0x00000070UL)
#define TMR6_GCONR_CKDIV_0                             (0x00000010UL)
#define TMR6_GCONR_CKDIV_1                             (0x00000020UL)
#define TMR6_GCONR_CKDIV_2                             (0x00000040UL)
#define TMR6_GCONR_DIR_POS                             (8U)
#define TMR6_GCONR_DIR                                 (0x00000100UL)
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

/*  Bit definition for TMR6_PCONR register  */
#define TMR6_PCONR_CAPMDA_POS                          (0U)
#define TMR6_PCONR_CAPMDA                              (0x00000001UL)
#define TMR6_PCONR_STACA_POS                           (1U)
#define TMR6_PCONR_STACA                               (0x00000002UL)
#define TMR6_PCONR_STPCA_POS                           (2U)
#define TMR6_PCONR_STPCA                               (0x00000004UL)
#define TMR6_PCONR_STASTPSA_POS                        (3U)
#define TMR6_PCONR_STASTPSA                            (0x00000008UL)
#define TMR6_PCONR_CMPCA_POS                           (4U)
#define TMR6_PCONR_CMPCA                               (0x00000030UL)
#define TMR6_PCONR_CMPCA_0                             (0x00000010UL)
#define TMR6_PCONR_CMPCA_1                             (0x00000020UL)
#define TMR6_PCONR_PERCA_POS                           (6U)
#define TMR6_PCONR_PERCA                               (0x000000C0UL)
#define TMR6_PCONR_PERCA_0                             (0x00000040UL)
#define TMR6_PCONR_PERCA_1                             (0x00000080UL)
#define TMR6_PCONR_OUTENA_POS                          (8U)
#define TMR6_PCONR_OUTENA                              (0x00000100UL)
#define TMR6_PCONR_EMBVALA_POS                         (11U)
#define TMR6_PCONR_EMBVALA                             (0x00001800UL)
#define TMR6_PCONR_EMBVALA_0                           (0x00000800UL)
#define TMR6_PCONR_EMBVALA_1                           (0x00001000UL)
#define TMR6_PCONR_CAPMDB_POS                          (16U)
#define TMR6_PCONR_CAPMDB                              (0x00010000UL)
#define TMR6_PCONR_STACB_POS                           (17U)
#define TMR6_PCONR_STACB                               (0x00020000UL)
#define TMR6_PCONR_STPCB_POS                           (18U)
#define TMR6_PCONR_STPCB                               (0x00040000UL)
#define TMR6_PCONR_STASTPSB_POS                        (19U)
#define TMR6_PCONR_STASTPSB                            (0x00080000UL)
#define TMR6_PCONR_CMPCB_POS                           (20U)
#define TMR6_PCONR_CMPCB                               (0x00300000UL)
#define TMR6_PCONR_CMPCB_0                             (0x00100000UL)
#define TMR6_PCONR_CMPCB_1                             (0x00200000UL)
#define TMR6_PCONR_PERCB_POS                           (22U)
#define TMR6_PCONR_PERCB                               (0x00C00000UL)
#define TMR6_PCONR_PERCB_0                             (0x00400000UL)
#define TMR6_PCONR_PERCB_1                             (0x00800000UL)
#define TMR6_PCONR_OUTENB_POS                          (24U)
#define TMR6_PCONR_OUTENB                              (0x01000000UL)
#define TMR6_PCONR_EMBVALB_POS                         (27U)
#define TMR6_PCONR_EMBVALB                             (0x18000000UL)
#define TMR6_PCONR_EMBVALB_0                           (0x08000000UL)
#define TMR6_PCONR_EMBVALB_1                           (0x10000000UL)

/*  Bit definition for TMR6_BCONR register  */
#define TMR6_BCONR_BENA_POS                            (0U)
#define TMR6_BCONR_BENA                                (0x00000001UL)
#define TMR6_BCONR_BSEA_POS                            (1U)
#define TMR6_BCONR_BSEA                                (0x00000002UL)
#define TMR6_BCONR_BENB_POS                            (2U)
#define TMR6_BCONR_BENB                                (0x00000004UL)
#define TMR6_BCONR_BSEB_POS                            (3U)
#define TMR6_BCONR_BSEB                                (0x00000008UL)
#define TMR6_BCONR_BENP_POS                            (8U)
#define TMR6_BCONR_BENP                                (0x00000100UL)
#define TMR6_BCONR_BSEP_POS                            (9U)
#define TMR6_BCONR_BSEP                                (0x00000200UL)
#define TMR6_BCONR_BENSPA_POS                          (16U)
#define TMR6_BCONR_BENSPA                              (0x00010000UL)
#define TMR6_BCONR_BSESPA_POS                          (17U)
#define TMR6_BCONR_BSESPA                              (0x00020000UL)
#define TMR6_BCONR_BTRUSPA_POS                         (20U)
#define TMR6_BCONR_BTRUSPA                             (0x00100000UL)
#define TMR6_BCONR_BTRDSPA_POS                         (21U)
#define TMR6_BCONR_BTRDSPA                             (0x00200000UL)
#define TMR6_BCONR_BENSPB_POS                          (24U)
#define TMR6_BCONR_BENSPB                              (0x01000000UL)
#define TMR6_BCONR_BSESPB_POS                          (25U)
#define TMR6_BCONR_BSESPB                              (0x02000000UL)
#define TMR6_BCONR_BTRUSPB_POS                         (28U)
#define TMR6_BCONR_BTRUSPB                             (0x10000000UL)
#define TMR6_BCONR_BTRDSPB_POS                         (29U)
#define TMR6_BCONR_BTRDSPB                             (0x20000000UL)

/*  Bit definition for TMR6_DCONR register  */
#define TMR6_DCONR_DTCEN_POS                           (0U)
#define TMR6_DCONR_DTCEN                               (0x00000001UL)
#define TMR6_DCONR_DTBENU_POS                          (4U)
#define TMR6_DCONR_DTBENU                              (0x00000010UL)
#define TMR6_DCONR_DTBEND_POS                          (5U)
#define TMR6_DCONR_DTBEND                              (0x00000020UL)
#define TMR6_DCONR_SEPA_POS                            (8U)
#define TMR6_DCONR_SEPA                                (0x00000100UL)

/*  Bit definition for TMR6_FCONR register  */
#define TMR6_FCONR_NOFIENGA_POS                        (0U)
#define TMR6_FCONR_NOFIENGA                            (0x00000001UL)
#define TMR6_FCONR_NOFICKGA_POS                        (1U)
#define TMR6_FCONR_NOFICKGA                            (0x00000006UL)
#define TMR6_FCONR_NOFICKGA_0                          (0x00000002UL)
#define TMR6_FCONR_NOFICKGA_1                          (0x00000004UL)
#define TMR6_FCONR_NOFIENGB_POS                        (4U)
#define TMR6_FCONR_NOFIENGB                            (0x00000010UL)
#define TMR6_FCONR_NOFICKGB_POS                        (5U)
#define TMR6_FCONR_NOFICKGB                            (0x00000060UL)
#define TMR6_FCONR_NOFICKGB_0                          (0x00000020UL)
#define TMR6_FCONR_NOFICKGB_1                          (0x00000040UL)
#define TMR6_FCONR_NOFIENTA_POS                        (16U)
#define TMR6_FCONR_NOFIENTA                            (0x00010000UL)
#define TMR6_FCONR_NOFICKTA_POS                        (17U)
#define TMR6_FCONR_NOFICKTA                            (0x00060000UL)
#define TMR6_FCONR_NOFICKTA_0                          (0x00020000UL)
#define TMR6_FCONR_NOFICKTA_1                          (0x00040000UL)
#define TMR6_FCONR_NOFIENTB_POS                        (20U)
#define TMR6_FCONR_NOFIENTB                            (0x00100000UL)
#define TMR6_FCONR_NOFICKTB_POS                        (21U)
#define TMR6_FCONR_NOFICKTB                            (0x00600000UL)
#define TMR6_FCONR_NOFICKTB_0                          (0x00200000UL)
#define TMR6_FCONR_NOFICKTB_1                          (0x00400000UL)

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
#define TMR6_HSTAR_HSTA4_POS                           (4U)
#define TMR6_HSTAR_HSTA4                               (0x00000010UL)
#define TMR6_HSTAR_HSTA5_POS                           (5U)
#define TMR6_HSTAR_HSTA5                               (0x00000020UL)
#define TMR6_HSTAR_HSTA6_POS                           (6U)
#define TMR6_HSTAR_HSTA6                               (0x00000040UL)
#define TMR6_HSTAR_HSTA7_POS                           (7U)
#define TMR6_HSTAR_HSTA7                               (0x00000080UL)
#define TMR6_HSTAR_HSTA8_POS                           (8U)
#define TMR6_HSTAR_HSTA8                               (0x00000100UL)
#define TMR6_HSTAR_HSTA9_POS                           (9U)
#define TMR6_HSTAR_HSTA9                               (0x00000200UL)
#define TMR6_HSTAR_HSTA10_POS                          (10U)
#define TMR6_HSTAR_HSTA10                              (0x00000400UL)
#define TMR6_HSTAR_HSTA11_POS                          (11U)
#define TMR6_HSTAR_HSTA11                              (0x00000800UL)
#define TMR6_HSTAR_STAS_POS                            (31U)
#define TMR6_HSTAR_STAS                                (0x80000000UL)

/*  Bit definition for TMR6_HSTPR register  */
#define TMR6_HSTPR_HSTP0_POS                           (0U)
#define TMR6_HSTPR_HSTP0                               (0x00000001UL)
#define TMR6_HSTPR_HSTP1_POS                           (1U)
#define TMR6_HSTPR_HSTP1                               (0x00000002UL)
#define TMR6_HSTPR_HSTP4_POS                           (4U)
#define TMR6_HSTPR_HSTP4                               (0x00000010UL)
#define TMR6_HSTPR_HSTP5_POS                           (5U)
#define TMR6_HSTPR_HSTP5                               (0x00000020UL)
#define TMR6_HSTPR_HSTP6_POS                           (6U)
#define TMR6_HSTPR_HSTP6                               (0x00000040UL)
#define TMR6_HSTPR_HSTP7_POS                           (7U)
#define TMR6_HSTPR_HSTP7                               (0x00000080UL)
#define TMR6_HSTPR_HSTP8_POS                           (8U)
#define TMR6_HSTPR_HSTP8                               (0x00000100UL)
#define TMR6_HSTPR_HSTP9_POS                           (9U)
#define TMR6_HSTPR_HSTP9                               (0x00000200UL)
#define TMR6_HSTPR_HSTP10_POS                          (10U)
#define TMR6_HSTPR_HSTP10                              (0x00000400UL)
#define TMR6_HSTPR_HSTP11_POS                          (11U)
#define TMR6_HSTPR_HSTP11                              (0x00000800UL)
#define TMR6_HSTPR_STPS_POS                            (31U)
#define TMR6_HSTPR_STPS                                (0x80000000UL)

/*  Bit definition for TMR6_HCLRR register  */
#define TMR6_HCLRR_HCLE0_POS                           (0U)
#define TMR6_HCLRR_HCLE0                               (0x00000001UL)
#define TMR6_HCLRR_HCLE1_POS                           (1U)
#define TMR6_HCLRR_HCLE1                               (0x00000002UL)
#define TMR6_HCLRR_HCLE4_POS                           (4U)
#define TMR6_HCLRR_HCLE4                               (0x00000010UL)
#define TMR6_HCLRR_HCLE5_POS                           (5U)
#define TMR6_HCLRR_HCLE5                               (0x00000020UL)
#define TMR6_HCLRR_HCLE6_POS                           (6U)
#define TMR6_HCLRR_HCLE6                               (0x00000040UL)
#define TMR6_HCLRR_HCLE7_POS                           (7U)
#define TMR6_HCLRR_HCLE7                               (0x00000080UL)
#define TMR6_HCLRR_HCLE8_POS                           (8U)
#define TMR6_HCLRR_HCLE8                               (0x00000100UL)
#define TMR6_HCLRR_HCLE9_POS                           (9U)
#define TMR6_HCLRR_HCLE9                               (0x00000200UL)
#define TMR6_HCLRR_HCLE10_POS                          (10U)
#define TMR6_HCLRR_HCLE10                              (0x00000400UL)
#define TMR6_HCLRR_HCLE11_POS                          (11U)
#define TMR6_HCLRR_HCLE11                              (0x00000800UL)
#define TMR6_HCLRR_CLES_POS                            (31U)
#define TMR6_HCLRR_CLES                                (0x80000000UL)

/*  Bit definition for TMR6_HCPAR register  */
#define TMR6_HCPAR_HCPA0_POS                           (0U)
#define TMR6_HCPAR_HCPA0                               (0x00000001UL)
#define TMR6_HCPAR_HCPA1_POS                           (1U)
#define TMR6_HCPAR_HCPA1                               (0x00000002UL)
#define TMR6_HCPAR_HCPA4_POS                           (4U)
#define TMR6_HCPAR_HCPA4                               (0x00000010UL)
#define TMR6_HCPAR_HCPA5_POS                           (5U)
#define TMR6_HCPAR_HCPA5                               (0x00000020UL)
#define TMR6_HCPAR_HCPA6_POS                           (6U)
#define TMR6_HCPAR_HCPA6                               (0x00000040UL)
#define TMR6_HCPAR_HCPA7_POS                           (7U)
#define TMR6_HCPAR_HCPA7                               (0x00000080UL)
#define TMR6_HCPAR_HCPA8_POS                           (8U)
#define TMR6_HCPAR_HCPA8                               (0x00000100UL)
#define TMR6_HCPAR_HCPA9_POS                           (9U)
#define TMR6_HCPAR_HCPA9                               (0x00000200UL)
#define TMR6_HCPAR_HCPA10_POS                          (10U)
#define TMR6_HCPAR_HCPA10                              (0x00000400UL)
#define TMR6_HCPAR_HCPA11_POS                          (11U)
#define TMR6_HCPAR_HCPA11                              (0x00000800UL)

/*  Bit definition for TMR6_HCPBR register  */
#define TMR6_HCPBR_HCPB0_POS                           (0U)
#define TMR6_HCPBR_HCPB0                               (0x00000001UL)
#define TMR6_HCPBR_HCPB1_POS                           (1U)
#define TMR6_HCPBR_HCPB1                               (0x00000002UL)
#define TMR6_HCPBR_HCPB4_POS                           (4U)
#define TMR6_HCPBR_HCPB4                               (0x00000010UL)
#define TMR6_HCPBR_HCPB5_POS                           (5U)
#define TMR6_HCPBR_HCPB5                               (0x00000020UL)
#define TMR6_HCPBR_HCPB6_POS                           (6U)
#define TMR6_HCPBR_HCPB6                               (0x00000040UL)
#define TMR6_HCPBR_HCPB7_POS                           (7U)
#define TMR6_HCPBR_HCPB7                               (0x00000080UL)
#define TMR6_HCPBR_HCPB8_POS                           (8U)
#define TMR6_HCPBR_HCPB8                               (0x00000100UL)
#define TMR6_HCPBR_HCPB9_POS                           (9U)
#define TMR6_HCPBR_HCPB9                               (0x00000200UL)
#define TMR6_HCPBR_HCPB10_POS                          (10U)
#define TMR6_HCPBR_HCPB10                              (0x00000400UL)
#define TMR6_HCPBR_HCPB11_POS                          (11U)
#define TMR6_HCPBR_HCPB11                              (0x00000800UL)

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

/*******************************************************************************
                Bit definition for Peripheral TMR6CR
*******************************************************************************/
/*  Bit definition for TMR6CR_SSTAR register  */
#define TMR6CR_SSTAR_SSTA1_POS                         (0U)
#define TMR6CR_SSTAR_SSTA1                             (0x00000001UL)
#define TMR6CR_SSTAR_SSTA2_POS                         (1U)
#define TMR6CR_SSTAR_SSTA2                             (0x00000002UL)
#define TMR6CR_SSTAR_SSTA3_POS                         (2U)
#define TMR6CR_SSTAR_SSTA3                             (0x00000004UL)

/*  Bit definition for TMR6CR_SSTPR register  */
#define TMR6CR_SSTPR_SSTP1_POS                         (0U)
#define TMR6CR_SSTPR_SSTP1                             (0x00000001UL)
#define TMR6CR_SSTPR_SSTP2_POS                         (1U)
#define TMR6CR_SSTPR_SSTP2                             (0x00000002UL)
#define TMR6CR_SSTPR_SSTP3_POS                         (2U)
#define TMR6CR_SSTPR_SSTP3                             (0x00000004UL)

/*  Bit definition for TMR6CR_SCLRR register  */
#define TMR6CR_SCLRR_SCLE1_POS                         (0U)
#define TMR6CR_SCLRR_SCLE1                             (0x00000001UL)
#define TMR6CR_SCLRR_SCLE2_POS                         (1U)
#define TMR6CR_SCLRR_SCLE2                             (0x00000002UL)
#define TMR6CR_SCLRR_SCLE3_POS                         (2U)
#define TMR6CR_SCLRR_SCLE3                             (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral TMRA
*******************************************************************************/
/*  Bit definition for TMRA_CNTER register  */
#define TMRA_CNTER_CNT                                 (0xFFFFU)

/*  Bit definition for TMRA_PERAR register  */
#define TMRA_PERAR_PER                                 (0xFFFFU)

/*  Bit definition for TMRA_CMPAR register  */
#define TMRA_CMPAR_CMP                                 (0xFFFFU)

/*  Bit definition for TMRA_BCSTR register  */
#define TMRA_BCSTR_START_POS                           (0U)
#define TMRA_BCSTR_START                               (0x0001U)
#define TMRA_BCSTR_DIR_POS                             (1U)
#define TMRA_BCSTR_DIR                                 (0x0002U)
#define TMRA_BCSTR_MODE_POS                            (2U)
#define TMRA_BCSTR_MODE                                (0x0004U)
#define TMRA_BCSTR_SYNST_POS                           (3U)
#define TMRA_BCSTR_SYNST                               (0x0008U)
#define TMRA_BCSTR_CKDIV_POS                           (4U)
#define TMRA_BCSTR_CKDIV                               (0x00F0U)
#define TMRA_BCSTR_ITENOVF_POS                         (12U)
#define TMRA_BCSTR_ITENOVF                             (0x1000U)
#define TMRA_BCSTR_ITENUDF_POS                         (13U)
#define TMRA_BCSTR_ITENUDF                             (0x2000U)
#define TMRA_BCSTR_OVFF_POS                            (14U)
#define TMRA_BCSTR_OVFF                                (0x4000U)
#define TMRA_BCSTR_UDFF_POS                            (15U)
#define TMRA_BCSTR_UDFF                                (0x8000U)

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
#define TMRA_ICONR_ITEN5_POS                           (4U)
#define TMRA_ICONR_ITEN5                               (0x0010U)
#define TMRA_ICONR_ITEN6_POS                           (5U)
#define TMRA_ICONR_ITEN6                               (0x0020U)
#define TMRA_ICONR_ITEN7_POS                           (6U)
#define TMRA_ICONR_ITEN7                               (0x0040U)
#define TMRA_ICONR_ITEN8_POS                           (7U)
#define TMRA_ICONR_ITEN8                               (0x0080U)

/*  Bit definition for TMRA_ECONR register  */
#define TMRA_ECONR_ETEN1_POS                           (0U)
#define TMRA_ECONR_ETEN1                               (0x0001U)
#define TMRA_ECONR_ETEN2_POS                           (1U)
#define TMRA_ECONR_ETEN2                               (0x0002U)
#define TMRA_ECONR_ETEN3_POS                           (2U)
#define TMRA_ECONR_ETEN3                               (0x0004U)
#define TMRA_ECONR_ETEN4_POS                           (3U)
#define TMRA_ECONR_ETEN4                               (0x0008U)
#define TMRA_ECONR_ETEN5_POS                           (4U)
#define TMRA_ECONR_ETEN5                               (0x0010U)
#define TMRA_ECONR_ETEN6_POS                           (5U)
#define TMRA_ECONR_ETEN6                               (0x0020U)
#define TMRA_ECONR_ETEN7_POS                           (6U)
#define TMRA_ECONR_ETEN7                               (0x0040U)
#define TMRA_ECONR_ETEN8_POS                           (7U)
#define TMRA_ECONR_ETEN8                               (0x0080U)

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
#define TMRA_STFLR_CMPF5_POS                           (4U)
#define TMRA_STFLR_CMPF5                               (0x0010U)
#define TMRA_STFLR_CMPF6_POS                           (5U)
#define TMRA_STFLR_CMPF6                               (0x0020U)
#define TMRA_STFLR_CMPF7_POS                           (6U)
#define TMRA_STFLR_CMPF7                               (0x0040U)
#define TMRA_STFLR_CMPF8_POS                           (7U)
#define TMRA_STFLR_CMPF8                               (0x0080U)

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
#define TMRA_CCONR_NOFICKCP_0                          (0x2000U)
#define TMRA_CCONR_NOFICKCP_1                          (0x4000U)

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
#define TRNG_MR_CNT_0                                  (0x00000004UL)
#define TRNG_MR_CNT_1                                  (0x00000008UL)
#define TRNG_MR_CNT_2                                  (0x00000010UL)

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
#define USART_SR_RXNE_POS                              (5U)
#define USART_SR_RXNE                                  (0x00000020UL)
#define USART_SR_TC_POS                                (6U)
#define USART_SR_TC                                    (0x00000040UL)
#define USART_SR_TXE_POS                               (7U)
#define USART_SR_TXE                                   (0x00000080UL)
#define USART_SR_RTOF_POS                              (8U)
#define USART_SR_RTOF                                  (0x00000100UL)
#define USART_SR_MPB_POS                               (16U)
#define USART_SR_MPB                                   (0x00010000UL)

/*  Bit definition for USART_DR register  */
#define USART_DR_TDR_POS                               (0U)
#define USART_DR_TDR                                   (0x000001FFUL)
#define USART_DR_MPID_POS                              (9U)
#define USART_DR_MPID                                  (0x00000200UL)
#define USART_DR_RDR_POS                               (16U)
#define USART_DR_RDR                                   (0x01FF0000UL)

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
#define USART_CR2_CLKC_POS                             (11U)
#define USART_CR2_CLKC                                 (0x00001800UL)
#define USART_CR2_CLKC_0                               (0x00000800UL)
#define USART_CR2_CLKC_1                               (0x00001000UL)
#define USART_CR2_STOP_POS                             (13U)
#define USART_CR2_STOP                                 (0x00002000UL)

/*  Bit definition for USART_CR3 register  */
#define USART_CR3_SCEN_POS                             (5U)
#define USART_CR3_SCEN                                 (0x00000020UL)
#define USART_CR3_CTSE_POS                             (9U)
#define USART_CR3_CTSE                                 (0x00000200UL)
#define USART_CR3_BCN_POS                              (21U)
#define USART_CR3_BCN                                  (0x00E00000UL)
#define USART_CR3_BCN_0                                (0x00200000UL)
#define USART_CR3_BCN_1                                (0x00400000UL)
#define USART_CR3_BCN_2                                (0x00800000UL)

/*  Bit definition for USART_PR register  */
#define USART_PR_PSC                                   (0x00000003UL)
#define USART_PR_PSC_0                                 (0x00000001UL)
#define USART_PR_PSC_1                                 (0x00000002UL)

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

/*  Bit definition for USBFS_HPTXFSIZ register  */
#define USBFS_HPTXFSIZ_PTXSA_POS                       (0U)
#define USBFS_HPTXFSIZ_PTXSA                           (0x00000FFFUL)
#define USBFS_HPTXFSIZ_PTXFD_POS                       (16U)
#define USBFS_HPTXFSIZ_PTXFD                           (0x07FF0000UL)

/*  Bit definition for USBFS_DIEPTXF register  */
#define USBFS_DIEPTXF_INEPTXSA_POS                     (0U)
#define USBFS_DIEPTXF_INEPTXSA                         (0x00000FFFUL)
#define USBFS_DIEPTXF_INEPTXFD_POS                     (16U)
#define USBFS_DIEPTXF_INEPTXFD                         (0x03FF0000UL)

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
#define USBFS_HAINT_HAINT                              (0x00000FFFUL)

/*  Bit definition for USBFS_HAINTMSK register  */
#define USBFS_HAINTMSK_HAINTM                          (0x00000FFFUL)

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

/*  Bit definition for USBFS_DIEPMSK register  */
#define USBFS_DIEPMSK_XFRCM_POS                        (0U)
#define USBFS_DIEPMSK_XFRCM                            (0x00000001UL)
#define USBFS_DIEPMSK_EPDM_POS                         (1U)
#define USBFS_DIEPMSK_EPDM                             (0x00000002UL)
#define USBFS_DIEPMSK_TOM_POS                          (3U)
#define USBFS_DIEPMSK_TOM                              (0x00000008UL)
#define USBFS_DIEPMSK_ITTXFEMSK_POS                    (4U)
#define USBFS_DIEPMSK_ITTXFEMSK                        (0x00000010UL)
#define USBFS_DIEPMSK_INEPNMM_POS                      (5U)
#define USBFS_DIEPMSK_INEPNMM                          (0x00000020UL)
#define USBFS_DIEPMSK_INEPNEM_POS                      (6U)
#define USBFS_DIEPMSK_INEPNEM                          (0x00000040UL)

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
#define USBFS_DAINT_IEPINT                             (0x0000003FUL)
#define USBFS_DAINT_OEPINT_POS                         (16U)
#define USBFS_DAINT_OEPINT                             (0x003F0000UL)

/*  Bit definition for USBFS_DAINTMSK register  */
#define USBFS_DAINTMSK_IEPINTM_POS                     (0U)
#define USBFS_DAINTMSK_IEPINTM                         (0x0000003FUL)
#define USBFS_DAINTMSK_OEPINTM_POS                     (16U)
#define USBFS_DAINTMSK_OEPINTM                         (0x003F0000UL)

/*  Bit definition for USBFS_DIEPEMPMSK register  */
#define USBFS_DIEPEMPMSK_INEPTXFEM                     (0x0000003FUL)

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

/*  Bit definition for USBFS_GCCTL register  */
#define USBFS_GCCTL_STPPCLK_POS                        (0U)
#define USBFS_GCCTL_STPPCLK                            (0x00000001UL)
#define USBFS_GCCTL_GATEHCLK_POS                       (1U)
#define USBFS_GCCTL_GATEHCLK                           (0x00000002UL)

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
#define WDT_SR_CNT_0                                   (0x00000001UL)
#define WDT_SR_CNT_1                                   (0x00000002UL)
#define WDT_SR_CNT_2                                   (0x00000004UL)
#define WDT_SR_CNT_3                                   (0x00000008UL)
#define WDT_SR_CNT_4                                   (0x00000010UL)
#define WDT_SR_CNT_5                                   (0x00000020UL)
#define WDT_SR_CNT_6                                   (0x00000040UL)
#define WDT_SR_CNT_7                                   (0x00000080UL)
#define WDT_SR_CNT_8                                   (0x00000100UL)
#define WDT_SR_CNT_9                                   (0x00000200UL)
#define WDT_SR_CNT_10                                  (0x00000400UL)
#define WDT_SR_CNT_11                                  (0x00000800UL)
#define WDT_SR_CNT_12                                  (0x00001000UL)
#define WDT_SR_CNT_13                                  (0x00002000UL)
#define WDT_SR_CNT_14                                  (0x00004000UL)
#define WDT_SR_CNT_15                                  (0x00008000UL)
#define WDT_SR_UDF_POS                                 (16U)
#define WDT_SR_UDF                                     (0x00010000UL)
#define WDT_SR_REF_POS                                 (17U)
#define WDT_SR_REF                                     (0x00020000UL)

/*  Bit definition for WDT_RR register  */
#define WDT_RR_RF                                      (0x0000FFFFUL)
#define WDT_RR_RF_0                                    (0x00000001UL)
#define WDT_RR_RF_1                                    (0x00000002UL)
#define WDT_RR_RF_2                                    (0x00000004UL)
#define WDT_RR_RF_3                                    (0x00000008UL)
#define WDT_RR_RF_4                                    (0x00000010UL)
#define WDT_RR_RF_5                                    (0x00000020UL)
#define WDT_RR_RF_6                                    (0x00000040UL)
#define WDT_RR_RF_7                                    (0x00000080UL)
#define WDT_RR_RF_8                                    (0x00000100UL)
#define WDT_RR_RF_9                                    (0x00000200UL)
#define WDT_RR_RF_10                                   (0x00000400UL)
#define WDT_RR_RF_11                                   (0x00000800UL)
#define WDT_RR_RF_12                                   (0x00001000UL)
#define WDT_RR_RF_13                                   (0x00002000UL)
#define WDT_RR_RF_14                                   (0x00004000UL)
#define WDT_RR_RF_15                                   (0x00008000UL)

/******************************************************************************/
/*             Device Specific Registers bit_band structure                   */
/******************************************************************************/

typedef struct {
    __IO uint32_t STRT;
    uint32_t RESERVED0[7];
} stc_adc_str_bit_t;

typedef struct {
    __IO uint32_t MS0;
    __IO uint32_t MS1;
    uint32_t RESERVED0[2];
    __IO uint32_t ACCSEL0;
    __IO uint32_t ACCSEL1;
    __IO uint32_t CLREN;
    __IO uint32_t DFMT;
    __IO uint32_t AVCNT0;
    __IO uint32_t AVCNT1;
    __IO uint32_t AVCNT2;
    uint32_t RESERVED1[5];
} stc_adc_cr0_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t RSCHSEL;
    uint32_t RESERVED1[13];
} stc_adc_cr1_bit_t;

typedef struct {
    __IO uint32_t TRGSELA0;
    __IO uint32_t TRGSELA1;
    uint32_t RESERVED0[5];
    __IO uint32_t TRGENA;
    __IO uint32_t TRGSELB0;
    __IO uint32_t TRGSELB1;
    uint32_t RESERVED1[5];
    __IO uint32_t TRGENB;
} stc_adc_trgsr_bit_t;

typedef struct {
    __IO uint32_t CH00MUX0;
    __IO uint32_t CH00MUX1;
    __IO uint32_t CH00MUX2;
    __IO uint32_t CH00MUX3;
    __IO uint32_t CH01MUX0;
    __IO uint32_t CH01MUX1;
    __IO uint32_t CH01MUX2;
    __IO uint32_t CH01MUX3;
    __IO uint32_t CH02MUX0;
    __IO uint32_t CH02MUX1;
    __IO uint32_t CH02MUX2;
    __IO uint32_t CH02MUX3;
    __IO uint32_t CH03MUX0;
    __IO uint32_t CH03MUX1;
    __IO uint32_t CH03MUX2;
    __IO uint32_t CH03MUX3;
} stc_adc_chmuxr0_bit_t;

typedef struct {
    __IO uint32_t CH04MUX0;
    __IO uint32_t CH04MUX1;
    __IO uint32_t CH04MUX2;
    __IO uint32_t CH04MUX3;
    __IO uint32_t CH05MUX0;
    __IO uint32_t CH05MUX1;
    __IO uint32_t CH05MUX2;
    __IO uint32_t CH05MUX3;
    __IO uint32_t CH06MUX0;
    __IO uint32_t CH06MUX1;
    __IO uint32_t CH06MUX2;
    __IO uint32_t CH06MUX3;
    __IO uint32_t CH07MUX0;
    __IO uint32_t CH07MUX1;
    __IO uint32_t CH07MUX2;
    __IO uint32_t CH07MUX3;
} stc_adc_chmuxr1_bit_t;

typedef struct {
    __IO uint32_t CH08MUX0;
    __IO uint32_t CH08MUX1;
    __IO uint32_t CH08MUX2;
    __IO uint32_t CH08MUX3;
    __IO uint32_t CH09MUX0;
    __IO uint32_t CH09MUX1;
    __IO uint32_t CH09MUX2;
    __IO uint32_t CH09MUX3;
    __IO uint32_t CH10MUX0;
    __IO uint32_t CH10MUX1;
    __IO uint32_t CH10MUX2;
    __IO uint32_t CH10MUX3;
    __IO uint32_t CH11MUX0;
    __IO uint32_t CH11MUX1;
    __IO uint32_t CH11MUX2;
    __IO uint32_t CH11MUX3;
} stc_adc_chmuxr2_bit_t;

typedef struct {
    __IO uint32_t CH12MUX0;
    __IO uint32_t CH12MUX1;
    __IO uint32_t CH12MUX2;
    __IO uint32_t CH12MUX3;
    __IO uint32_t CH13MUX0;
    __IO uint32_t CH13MUX1;
    __IO uint32_t CH13MUX2;
    __IO uint32_t CH13MUX3;
    __IO uint32_t CH14MUX0;
    __IO uint32_t CH14MUX1;
    __IO uint32_t CH14MUX2;
    __IO uint32_t CH14MUX3;
    __IO uint32_t CH15MUX0;
    __IO uint32_t CH15MUX1;
    __IO uint32_t CH15MUX2;
    __IO uint32_t CH15MUX3;
} stc_adc_chmuxr3_bit_t;

typedef struct {
    __IO uint32_t EOCAF;
    __IO uint32_t EOCBF;
    uint32_t RESERVED0[6];
} stc_adc_isr_bit_t;

typedef struct {
    __IO uint32_t EOCAIEN;
    __IO uint32_t EOCBIEN;
    uint32_t RESERVED0[6];
} stc_adc_icr_bit_t;

typedef struct {
    __IO uint32_t SYNCEN;
    uint32_t RESERVED0[3];
    __IO uint32_t SYNCMD0;
    __IO uint32_t SYNCMD1;
    __IO uint32_t SYNCMD2;
    uint32_t RESERVED1[1];
    __IO uint32_t SYNCDLY0;
    __IO uint32_t SYNCDLY1;
    __IO uint32_t SYNCDLY2;
    __IO uint32_t SYNCDLY3;
    __IO uint32_t SYNCDLY4;
    __IO uint32_t SYNCDLY5;
    __IO uint32_t SYNCDLY6;
    __IO uint32_t SYNCDLY7;
} stc_adc_synccr_bit_t;

typedef struct {
    __IO uint32_t AWDEN;
    uint32_t RESERVED0[3];
    __IO uint32_t AWDMD;
    uint32_t RESERVED1[1];
    __IO uint32_t AWDSS0;
    __IO uint32_t AWDSS1;
    __IO uint32_t AWDIEN;
    uint32_t RESERVED2[7];
} stc_adc_awdcr_bit_t;

typedef struct {
    __IO uint32_t PGACTL0;
    __IO uint32_t PGACTL1;
    __IO uint32_t PGACTL2;
    __IO uint32_t PGACTL3;
    uint32_t RESERVED0[12];
} stc_adc_pgacr_bit_t;

typedef struct {
    __IO uint32_t GAIN0;
    __IO uint32_t GAIN1;
    __IO uint32_t GAIN2;
    __IO uint32_t GAIN3;
    uint32_t RESERVED0[12];
} stc_adc_pgagsr_bit_t;

typedef struct {
    __IO uint32_t PGAINSEL0;
    __IO uint32_t PGAINSEL1;
    __IO uint32_t PGAINSEL2;
    __IO uint32_t PGAINSEL3;
    __IO uint32_t PGAINSEL4;
    __IO uint32_t PGAINSEL5;
    __IO uint32_t PGAINSEL6;
    __IO uint32_t PGAINSEL7;
    __IO uint32_t PGAINSEL8;
    uint32_t RESERVED0[7];
} stc_adc_pgainsr0_bit_t;

typedef struct {
    __IO uint32_t PGAVSSEN;
    uint32_t RESERVED0[15];
} stc_adc_pgainsr1_bit_t;

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
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_dcu_trgsel_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_dma1_trgsel_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_dma2_trgsel_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_dma_trgselrc_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_tmr6_htssr_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_tmr0_htssr_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_pevnttrgsr_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_tmra_htssr_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_ots_trg_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_adc1_itrgselr_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t COMTRG_EN0;
    __IO uint32_t COMTRG_EN1;
} stc_aos_adc2_itrgselr_bit_t;

typedef struct {
    __IO uint32_t PDIR00;
    __IO uint32_t PDIR01;
    __IO uint32_t PDIR02;
    __IO uint32_t PDIR03;
    __IO uint32_t PDIR04;
    __IO uint32_t PDIR05;
    __IO uint32_t PDIR06;
    __IO uint32_t PDIR07;
    __IO uint32_t PDIR08;
    __IO uint32_t PDIR09;
    __IO uint32_t PDIR10;
    __IO uint32_t PDIR11;
    __IO uint32_t PDIR12;
    __IO uint32_t PDIR13;
    __IO uint32_t PDIR14;
    __IO uint32_t PDIR15;
    uint32_t RESERVED0[16];
} stc_aos_pevntdirr_bit_t;

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
    uint32_t RESERVED0[16];
} stc_aos_pevntidr_bit_t;

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
    uint32_t RESERVED0[16];
} stc_aos_pevntodr_bit_t;

typedef struct {
    __IO uint32_t POR00;
    __IO uint32_t POR01;
    __IO uint32_t POR02;
    __IO uint32_t POR03;
    __IO uint32_t POR04;
    __IO uint32_t POR05;
    __IO uint32_t POR06;
    __IO uint32_t POR07;
    __IO uint32_t POR08;
    __IO uint32_t POR09;
    __IO uint32_t POR10;
    __IO uint32_t POR11;
    __IO uint32_t POR12;
    __IO uint32_t POR13;
    __IO uint32_t POR14;
    __IO uint32_t POR15;
    uint32_t RESERVED0[16];
} stc_aos_pevntorr_bit_t;

typedef struct {
    __IO uint32_t POS00;
    __IO uint32_t POS01;
    __IO uint32_t POS02;
    __IO uint32_t POS03;
    __IO uint32_t POS04;
    __IO uint32_t POS05;
    __IO uint32_t POS06;
    __IO uint32_t POS07;
    __IO uint32_t POS08;
    __IO uint32_t POS09;
    __IO uint32_t POS10;
    __IO uint32_t POS11;
    __IO uint32_t POS12;
    __IO uint32_t POS13;
    __IO uint32_t POS14;
    __IO uint32_t POS15;
    uint32_t RESERVED0[16];
} stc_aos_pevntosr_bit_t;

typedef struct {
    __IO uint32_t RIS00;
    __IO uint32_t RIS01;
    __IO uint32_t RIS02;
    __IO uint32_t RIS03;
    __IO uint32_t RIS04;
    __IO uint32_t RIS05;
    __IO uint32_t RIS06;
    __IO uint32_t RIS07;
    __IO uint32_t RIS08;
    __IO uint32_t RIS09;
    __IO uint32_t RIS10;
    __IO uint32_t RIS11;
    __IO uint32_t RIS12;
    __IO uint32_t RIS13;
    __IO uint32_t RIS14;
    __IO uint32_t RIS15;
    uint32_t RESERVED0[16];
} stc_aos_pevntrisr_bit_t;

typedef struct {
    __IO uint32_t FAL00;
    __IO uint32_t FAL01;
    __IO uint32_t FAL02;
    __IO uint32_t FAL03;
    __IO uint32_t FAL04;
    __IO uint32_t FAL05;
    __IO uint32_t FAL06;
    __IO uint32_t FAL07;
    __IO uint32_t FAL08;
    __IO uint32_t FAL09;
    __IO uint32_t FAL10;
    __IO uint32_t FAL11;
    __IO uint32_t FAL12;
    __IO uint32_t FAL13;
    __IO uint32_t FAL14;
    __IO uint32_t FAL15;
    uint32_t RESERVED0[16];
} stc_aos_pevntfal_bit_t;

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
    __I  uint32_t TSSTAT0;
    __I  uint32_t TSSTAT1;
    uint32_t RESERVED0[2];
    __IO uint32_t TTTBM;
    __IO uint32_t TSMODE;
    __IO uint32_t TSNEXT;
    uint32_t RESERVED1[1];
} stc_can_tctrl_bit_t;

typedef struct {
    __I  uint32_t RSTAT0;
    __I  uint32_t RSTAT1;
    uint32_t RESERVED0[1];
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
    __IO uint32_t EWL0;
    __IO uint32_t EWL1;
    __IO uint32_t EWL2;
    __IO uint32_t EWL3;
    __IO uint32_t AFWL0;
    __IO uint32_t AFWL1;
    __IO uint32_t AFWL2;
    __IO uint32_t AFWL3;
} stc_can_limit_bit_t;

typedef struct {
    __IO uint32_t S_SEG_10;
    __IO uint32_t S_SEG_11;
    __IO uint32_t S_SEG_12;
    __IO uint32_t S_SEG_13;
    __IO uint32_t S_SEG_14;
    __IO uint32_t S_SEG_15;
    __IO uint32_t S_SEG_16;
    __IO uint32_t S_SEG_17;
    __IO uint32_t S_SEG_20;
    __IO uint32_t S_SEG_21;
    __IO uint32_t S_SEG_22;
    __IO uint32_t S_SEG_23;
    __IO uint32_t S_SEG_24;
    __IO uint32_t S_SEG_25;
    __IO uint32_t S_SEG_26;
    uint32_t RESERVED0[1];
    __IO uint32_t S_SJW0;
    __IO uint32_t S_SJW1;
    __IO uint32_t S_SJW2;
    __IO uint32_t S_SJW3;
    __IO uint32_t S_SJW4;
    __IO uint32_t S_SJW5;
    __IO uint32_t S_SJW6;
    uint32_t RESERVED1[1];
    __IO uint32_t S_PRESC0;
    __IO uint32_t S_PRESC1;
    __IO uint32_t S_PRESC2;
    __IO uint32_t S_PRESC3;
    __IO uint32_t S_PRESC4;
    __IO uint32_t S_PRESC5;
    __IO uint32_t S_PRESC6;
    __IO uint32_t S_PRESC7;
} stc_can_sbt_bit_t;

typedef struct {
    __I  uint32_t ALC0;
    __I  uint32_t ALC1;
    __I  uint32_t ALC2;
    __I  uint32_t ALC3;
    __I  uint32_t ALC4;
    __I  uint32_t KOER0;
    __I  uint32_t KOER1;
    __I  uint32_t KOER2;
} stc_can_ealcap_bit_t;

typedef struct {
    __IO uint32_t ACFADR0;
    __IO uint32_t ACFADR1;
    __IO uint32_t ACFADR2;
    __IO uint32_t ACFADR3;
    uint32_t RESERVED0[1];
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
} stc_can_acfen_bit_t;

typedef struct {
    __IO uint32_t ACODEORAMASK0;
    __IO uint32_t ACODEORAMASK1;
    __IO uint32_t ACODEORAMASK2;
    __IO uint32_t ACODEORAMASK3;
    __IO uint32_t ACODEORAMASK4;
    __IO uint32_t ACODEORAMASK5;
    __IO uint32_t ACODEORAMASK6;
    __IO uint32_t ACODEORAMASK7;
    __IO uint32_t ACODEORAMASK8;
    __IO uint32_t ACODEORAMASK9;
    __IO uint32_t ACODEORAMASK10;
    __IO uint32_t ACODEORAMASK11;
    __IO uint32_t ACODEORAMASK12;
    __IO uint32_t ACODEORAMASK13;
    __IO uint32_t ACODEORAMASK14;
    __IO uint32_t ACODEORAMASK15;
    __IO uint32_t ACODEORAMASK16;
    __IO uint32_t ACODEORAMASK17;
    __IO uint32_t ACODEORAMASK18;
    __IO uint32_t ACODEORAMASK19;
    __IO uint32_t ACODEORAMASK20;
    __IO uint32_t ACODEORAMASK21;
    __IO uint32_t ACODEORAMASK22;
    __IO uint32_t ACODEORAMASK23;
    __IO uint32_t ACODEORAMASK24;
    __IO uint32_t ACODEORAMASK25;
    __IO uint32_t ACODEORAMASK26;
    __IO uint32_t ACODEORAMASK27;
    __IO uint32_t ACODEORAMASK28;
    __IO uint32_t AIDE;
    __IO uint32_t AIDEE;
    uint32_t RESERVED0[1];
} stc_can_acf_bit_t;

typedef struct {
    __IO uint32_t TBPTR0;
    __IO uint32_t TBPTR1;
    __IO uint32_t TBPTR2;
    __IO uint32_t TBPTR3;
    __IO uint32_t TBPTR4;
    __IO uint32_t TBPTR5;
    __IO uint32_t TBF;
    __IO uint32_t TBE;
} stc_can_tbslot_bit_t;

typedef struct {
    __IO uint32_t TTEN;
    __IO uint32_t T_PRESC0;
    __IO uint32_t T_PRESC1;
    __IO uint32_t TTIF;
    __IO uint32_t TTIE;
    __IO uint32_t TEIF;
    __IO uint32_t WTIF;
    __IO uint32_t WTIE;
} stc_can_ttcfg_bit_t;

typedef struct {
    __IO uint32_t REF_ID0;
    __IO uint32_t REF_ID1;
    __IO uint32_t REF_ID2;
    __IO uint32_t REF_ID3;
    __IO uint32_t REF_ID4;
    __IO uint32_t REF_ID5;
    __IO uint32_t REF_ID6;
    __IO uint32_t REF_ID7;
    __IO uint32_t REF_ID8;
    __IO uint32_t REF_ID9;
    __IO uint32_t REF_ID10;
    __IO uint32_t REF_ID11;
    __IO uint32_t REF_ID12;
    __IO uint32_t REF_ID13;
    __IO uint32_t REF_ID14;
    __IO uint32_t REF_ID15;
    __IO uint32_t REF_ID16;
    __IO uint32_t REF_ID17;
    __IO uint32_t REF_ID18;
    __IO uint32_t REF_ID19;
    __IO uint32_t REF_ID20;
    __IO uint32_t REF_ID21;
    __IO uint32_t REF_ID22;
    __IO uint32_t REF_ID23;
    __IO uint32_t REF_ID24;
    __IO uint32_t REF_ID25;
    __IO uint32_t REF_ID26;
    __IO uint32_t REF_ID27;
    __IO uint32_t REF_ID28;
    uint32_t RESERVED0[2];
    __IO uint32_t REF_IDE;
} stc_can_ref_msg_bit_t;

typedef struct {
    __IO uint32_t TTPTR0;
    __IO uint32_t TTPTR1;
    __IO uint32_t TTPTR2;
    __IO uint32_t TTPTR3;
    __IO uint32_t TTPTR4;
    __IO uint32_t TTPTR5;
    uint32_t RESERVED0[2];
    __IO uint32_t TTYPE0;
    __IO uint32_t TTYPE1;
    __IO uint32_t TTYPE2;
    uint32_t RESERVED1[1];
    __IO uint32_t TEW0;
    __IO uint32_t TEW1;
    __IO uint32_t TEW2;
    __IO uint32_t TEW3;
} stc_can_trg_cfg_bit_t;

typedef struct {
    __IO uint32_t FLTSL0;
    __IO uint32_t FLTSL1;
    __IO uint32_t FLTSL2;
    uint32_t RESERVED0[2];
    __IO uint32_t EDGSL0;
    __IO uint32_t EDGSL1;
    __IO uint32_t IEN;
    __IO uint32_t CVSEN;
    uint32_t RESERVED1[3];
    __IO uint32_t OUTEN;
    __IO uint32_t INV;
    __IO uint32_t CMPOE;
    __IO uint32_t CMPON;
} stc_cmp_ctrl_bit_t;

typedef struct {
    __IO uint32_t RVSL0;
    __IO uint32_t RVSL1;
    __IO uint32_t RVSL2;
    __IO uint32_t RVSL3;
    uint32_t RESERVED0[4];
    __IO uint32_t CVSL0;
    __IO uint32_t CVSL1;
    __IO uint32_t CVSL2;
    __IO uint32_t CVSL3;
    __IO uint32_t C4SL0;
    __IO uint32_t C4SL1;
    __IO uint32_t C4SL2;
    uint32_t RESERVED1[1];
} stc_cmp_vltsel_bit_t;

typedef struct {
    __I  uint32_t OMON;
    uint32_t RESERVED0[7];
    __I  uint32_t CVST0;
    __I  uint32_t CVST1;
    __I  uint32_t CVST2;
    __I  uint32_t CVST3;
    uint32_t RESERVED1[4];
} stc_cmp_outmon_bit_t;

typedef struct {
    __IO uint32_t STB0;
    __IO uint32_t STB1;
    __IO uint32_t STB2;
    __IO uint32_t STB3;
    uint32_t RESERVED0[12];
} stc_cmp_cvsstb_bit_t;

typedef struct {
    __IO uint32_t PRD0;
    __IO uint32_t PRD1;
    __IO uint32_t PRD2;
    __IO uint32_t PRD3;
    __IO uint32_t PRD4;
    __IO uint32_t PRD5;
    __IO uint32_t PRD6;
    __IO uint32_t PRD7;
    uint32_t RESERVED0[8];
} stc_cmp_cvsprd_bit_t;

typedef struct {
    __IO uint32_t DA1EN;
    __IO uint32_t DA2EN;
    uint32_t RESERVED0[14];
} stc_cmpcr_dacr_bit_t;

typedef struct {
    __IO uint32_t DA1SW;
    __IO uint32_t DA2SW;
    uint32_t RESERVED0[2];
    __IO uint32_t VREFSW;
    uint32_t RESERVED1[11];
} stc_cmpcr_rvadc_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t CR;
    __IO uint32_t REFIN;
    __IO uint32_t REFOUT;
    __IO uint32_t XOROUT;
    uint32_t RESERVED1[27];
} stc_crc_cr_bit_t;

typedef struct {
    __IO uint32_t CRC_REG0;
    __IO uint32_t CRC_REG1;
    __IO uint32_t CRC_REG2;
    __IO uint32_t CRC_REG3;
    __IO uint32_t CRC_REG4;
    __IO uint32_t CRC_REG5;
    __IO uint32_t CRC_REG6;
    __IO uint32_t CRC_REG7;
    __IO uint32_t CRC_REG8;
    __IO uint32_t CRC_REG9;
    __IO uint32_t CRC_REG10;
    __IO uint32_t CRC_REG11;
    __IO uint32_t CRC_REG12;
    __IO uint32_t CRC_REG13;
    __IO uint32_t CRC_REG14;
    __IO uint32_t CRC_REG15;
    __I  uint32_t CRCFLAG_16;
    uint32_t RESERVED0[15];
} stc_crc_reslt_bit_t;

typedef struct {
    __I  uint32_t CRCFLAG_32;
    uint32_t RESERVED0[31];
} stc_crc_flg_bit_t;

typedef struct {
    __IO uint32_t AUTH;
    __IO uint32_t REMVLOCK;
    __IO uint32_t SAFTYLOCK1;
    __IO uint32_t SAFTYLOCK2;
    uint32_t RESERVED0[4];
    __IO uint32_t CPUSTOP;
    __IO uint32_t CPUSLEEP;
    uint32_t RESERVED1[22];
} stc_dbgc_mcustat_bit_t;

typedef struct {
    __IO uint32_t EDBGRQ;
    __IO uint32_t RESTART;
    uint32_t RESERVED0[6];
    __IO uint32_t DIRQ;
    uint32_t RESERVED1[23];
} stc_dbgc_mcuctl_bit_t;

typedef struct {
    __IO uint32_t ERASEREQ;
    __IO uint32_t ERASEACK;
    __IO uint32_t ERASEERR;
    uint32_t RESERVED0[29];
} stc_dbgc_fmcctl_bit_t;

typedef struct {
    __IO uint32_t CDBGPWRUPREQ;
    __IO uint32_t CDBGPWRUPACK;
    uint32_t RESERVED0[30];
} stc_dbgc_mcudbgstat_bit_t;

typedef struct {
    __IO uint32_t SWDTSTP;
    __IO uint32_t WDTSTP;
    __IO uint32_t RTCSTP;
    __IO uint32_t PVD0STP;
    __IO uint32_t PVD1STP;
    __IO uint32_t PVD2STP;
    uint32_t RESERVED0[8];
    __IO uint32_t TMR01STP;
    __IO uint32_t TMR02STP;
    uint32_t RESERVED1[4];
    __IO uint32_t TMR41STP;
    __IO uint32_t TMR42STP;
    __IO uint32_t TMR43STP;
    __IO uint32_t TM61STP;
    __IO uint32_t TM62STP;
    __IO uint32_t TMR63STP;
    __IO uint32_t TMRA1STP;
    __IO uint32_t TMRA2STP;
    __IO uint32_t TMRA3STP;
    __IO uint32_t TMRA4STP;
    __IO uint32_t TMRA5STP;
    __IO uint32_t TMRA6STP;
} stc_dbgc_mcustpctl_bit_t;

typedef struct {
    __IO uint32_t TRACEMODE0;
    __IO uint32_t TRACEMODE1;
    __IO uint32_t TRACEIOEN;
    uint32_t RESERVED0[29];
} stc_dbgc_mcutracectl_bit_t;

typedef struct {
    __IO uint32_t MODE0;
    __IO uint32_t MODE1;
    __IO uint32_t MODE2;
    __IO uint32_t DATASIZE0;
    __IO uint32_t DATASIZE1;
    uint32_t RESERVED0[3];
    __IO uint32_t COMP_TRG;
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
    uint32_t RESERVED0[25];
} stc_dcu_flag_bit_t;

typedef struct {
    __O  uint32_t CLR_OP;
    __O  uint32_t CLR_LS2;
    __O  uint32_t CLR_EQ2;
    __O  uint32_t CLR_GT2;
    __O  uint32_t CLR_LS1;
    __O  uint32_t CLR_EQ1;
    __O  uint32_t CLR_GT1;
    uint32_t RESERVED0[25];
} stc_dcu_flagclr_bit_t;

typedef struct {
    __IO uint32_t INT_OP;
    __IO uint32_t INT_LS2;
    __IO uint32_t INT_EQ2;
    __IO uint32_t INT_GT2;
    __IO uint32_t INT_LS1;
    __IO uint32_t INT_EQ1;
    __IO uint32_t INT_GT1;
    __IO uint32_t INT_WIN0;
    __IO uint32_t INT_WIN1;
    uint32_t RESERVED0[23];
} stc_dcu_intsel_bit_t;

typedef struct {
    __IO uint32_t EN;
    uint32_t RESERVED0[31];
} stc_dma_en_bit_t;

typedef struct {
    __I  uint32_t TRNERR0;
    __I  uint32_t TRNERR1;
    __I  uint32_t TRNERR2;
    __I  uint32_t TRNERR3;
    uint32_t RESERVED0[12];
    __I  uint32_t REQERR0;
    __I  uint32_t REQERR1;
    __I  uint32_t REQERR2;
    __I  uint32_t REQERR3;
    uint32_t RESERVED1[12];
} stc_dma_intstat0_bit_t;

typedef struct {
    __I  uint32_t TC0;
    __I  uint32_t TC1;
    __I  uint32_t TC2;
    __I  uint32_t TC3;
    uint32_t RESERVED0[12];
    __I  uint32_t BTC0;
    __I  uint32_t BTC1;
    __I  uint32_t BTC2;
    __I  uint32_t BTC3;
    uint32_t RESERVED1[12];
} stc_dma_intstat1_bit_t;

typedef struct {
    __IO uint32_t MSKTRNERR0;
    __IO uint32_t MSKTRNERR1;
    __IO uint32_t MSKTRNERR2;
    __IO uint32_t MSKTRNERR3;
    uint32_t RESERVED0[12];
    __IO uint32_t MSKREQERR0;
    __IO uint32_t MSKREQERR1;
    __IO uint32_t MSKREQERR2;
    __IO uint32_t MSKREQERR3;
    uint32_t RESERVED1[12];
} stc_dma_intmask0_bit_t;

typedef struct {
    __IO uint32_t MSKTC0;
    __IO uint32_t MSKTC1;
    __IO uint32_t MSKTC2;
    __IO uint32_t MSKTC3;
    uint32_t RESERVED0[12];
    __IO uint32_t MSKBTC0;
    __IO uint32_t MSKBTC1;
    __IO uint32_t MSKBTC2;
    __IO uint32_t MSKBTC3;
    uint32_t RESERVED1[12];
} stc_dma_intmask1_bit_t;

typedef struct {
    __O  uint32_t CLRTRNERR0;
    __O  uint32_t CLRTRNERR1;
    __O  uint32_t CLRTRNERR2;
    __O  uint32_t CLRTRNERR3;
    uint32_t RESERVED0[12];
    __O  uint32_t CLRREQERR0;
    __O  uint32_t CLRREQERR1;
    __O  uint32_t CLRREQERR2;
    __O  uint32_t CLRREQERR3;
    uint32_t RESERVED1[12];
} stc_dma_intclr0_bit_t;

typedef struct {
    __O  uint32_t CLRTC0;
    __O  uint32_t CLRTC1;
    __O  uint32_t CLRTC2;
    __O  uint32_t CLRTC3;
    uint32_t RESERVED0[12];
    __O  uint32_t CLRBTC0;
    __O  uint32_t CLRBTC1;
    __O  uint32_t CLRBTC2;
    __O  uint32_t CLRBTC3;
    uint32_t RESERVED1[12];
} stc_dma_intclr1_bit_t;

typedef struct {
    __IO uint32_t CHEN0;
    __IO uint32_t CHEN1;
    __IO uint32_t CHEN2;
    __IO uint32_t CHEN3;
    uint32_t RESERVED0[28];
} stc_dma_chen_bit_t;

typedef struct {
    __I  uint32_t CHREQ0;
    __I  uint32_t CHREQ1;
    __I  uint32_t CHREQ2;
    __I  uint32_t CHREQ3;
    uint32_t RESERVED0[11];
    __I  uint32_t RCFGREQ;
    uint32_t RESERVED1[16];
} stc_dma_reqstat_bit_t;

typedef struct {
    __I  uint32_t DMAACT;
    __I  uint32_t RCFGACT;
    uint32_t RESERVED0[14];
    __I  uint32_t CHACT0;
    __I  uint32_t CHACT1;
    __I  uint32_t CHACT2;
    __I  uint32_t CHACT3;
    uint32_t RESERVED1[12];
} stc_dma_chstat_bit_t;

typedef struct {
    __IO uint32_t RCFGEN;
    __IO uint32_t RCFGLLP;
    uint32_t RESERVED0[6];
    __IO uint32_t RCFGCHS0;
    __IO uint32_t RCFGCHS1;
    __IO uint32_t RCFGCHS2;
    __IO uint32_t RCFGCHS3;
    uint32_t RESERVED1[4];
    __IO uint32_t SARMD0;
    __IO uint32_t SARMD1;
    __IO uint32_t DARMD0;
    __IO uint32_t DARMD1;
    __IO uint32_t CNTMD0;
    __IO uint32_t CNTMD1;
    uint32_t RESERVED2[10];
} stc_dma_rcfgctl_bit_t;

typedef struct {
    __IO uint32_t SRPTB0;
    __IO uint32_t SRPTB1;
    __IO uint32_t SRPTB2;
    __IO uint32_t SRPTB3;
    __IO uint32_t SRPTB4;
    __IO uint32_t SRPTB5;
    __IO uint32_t SRPTB6;
    __IO uint32_t SRPTB7;
    __IO uint32_t SRPTB8;
    __IO uint32_t SRPTB9;
    uint32_t RESERVED0[6];
    __IO uint32_t DRPTB0;
    __IO uint32_t DRPTB1;
    __IO uint32_t DRPTB2;
    __IO uint32_t DRPTB3;
    __IO uint32_t DRPTB4;
    __IO uint32_t DRPTB5;
    __IO uint32_t DRPTB6;
    __IO uint32_t DRPTB7;
    __IO uint32_t DRPTB8;
    __IO uint32_t DRPTB9;
    uint32_t RESERVED1[6];
} stc_dma_rptb_bit_t;

typedef struct {
    __IO uint32_t SNSDIST0;
    __IO uint32_t SNSDIST1;
    __IO uint32_t SNSDIST2;
    __IO uint32_t SNSDIST3;
    __IO uint32_t SNSDIST4;
    __IO uint32_t SNSDIST5;
    __IO uint32_t SNSDIST6;
    __IO uint32_t SNSDIST7;
    __IO uint32_t SNSDIST8;
    __IO uint32_t SNSDIST9;
    __IO uint32_t SNSDIST10;
    __IO uint32_t SNSDIST11;
    __IO uint32_t SNSDIST12;
    __IO uint32_t SNSDIST13;
    __IO uint32_t SNSDIST14;
    __IO uint32_t SNSDIST15;
    __IO uint32_t SNSDIST16;
    __IO uint32_t SNSDIST17;
    __IO uint32_t SNSDIST18;
    __IO uint32_t SNSDIST19;
    __IO uint32_t SNSCNTB0;
    __IO uint32_t SNSCNTB1;
    __IO uint32_t SNSCNTB2;
    __IO uint32_t SNSCNTB3;
    __IO uint32_t SNSCNTB4;
    __IO uint32_t SNSCNTB5;
    __IO uint32_t SNSCNTB6;
    __IO uint32_t SNSCNTB7;
    __IO uint32_t SNSCNTB8;
    __IO uint32_t SNSCNTB9;
    __IO uint32_t SNSCNTB10;
    __IO uint32_t SNSCNTB11;
} stc_dma_snseqctlb_bit_t;

typedef struct {
    __IO uint32_t DNSDIST0;
    __IO uint32_t DNSDIST1;
    __IO uint32_t DNSDIST2;
    __IO uint32_t DNSDIST3;
    __IO uint32_t DNSDIST4;
    __IO uint32_t DNSDIST5;
    __IO uint32_t DNSDIST6;
    __IO uint32_t DNSDIST7;
    __IO uint32_t DNSDIST8;
    __IO uint32_t DNSDIST9;
    __IO uint32_t DNSDIST10;
    __IO uint32_t DNSDIST11;
    __IO uint32_t DNSDIST12;
    __IO uint32_t DNSDIST13;
    __IO uint32_t DNSDIST14;
    __IO uint32_t DNSDIST15;
    __IO uint32_t DNSDIST16;
    __IO uint32_t DNSDIST17;
    __IO uint32_t DNSDIST18;
    __IO uint32_t DNSDIST19;
    __IO uint32_t DNSCNTB0;
    __IO uint32_t DNSCNTB1;
    __IO uint32_t DNSCNTB2;
    __IO uint32_t DNSCNTB3;
    __IO uint32_t DNSCNTB4;
    __IO uint32_t DNSCNTB5;
    __IO uint32_t DNSCNTB6;
    __IO uint32_t DNSCNTB7;
    __IO uint32_t DNSCNTB8;
    __IO uint32_t DNSCNTB9;
    __IO uint32_t DNSCNTB10;
    __IO uint32_t DNSCNTB11;
} stc_dma_dnseqctlb_bit_t;

typedef struct {
    __IO uint32_t SINC0;
    __IO uint32_t SINC1;
    __IO uint32_t DINC0;
    __IO uint32_t DINC1;
    __IO uint32_t SRPTEN;
    __IO uint32_t DRPTEN;
    __IO uint32_t SNSEQEN;
    __IO uint32_t DNSEQEN;
    __IO uint32_t HSIZE0;
    __IO uint32_t HSIZE1;
    __IO uint32_t LLPEN;
    __IO uint32_t LLPRUN;
    __IO uint32_t IE;
    uint32_t RESERVED0[19];
} stc_dma_chctl_bit_t;

typedef struct {
    __IO uint32_t FSTP;
    uint32_t RESERVED0[31];
} stc_efm_fstp_bit_t;

typedef struct {
    __IO uint32_t SLPMD;
    uint32_t RESERVED0[7];
    __IO uint32_t LVM;
    uint32_t RESERVED1[7];
    __IO uint32_t CACHE;
    uint32_t RESERVED2[7];
    __IO uint32_t CRST;
    uint32_t RESERVED3[7];
} stc_efm_frmc_bit_t;

typedef struct {
    __IO uint32_t PEMODE;
    uint32_t RESERVED0[3];
    __IO uint32_t PEMOD0;
    __IO uint32_t PEMOD1;
    __IO uint32_t PEMOD2;
    uint32_t RESERVED1[1];
    __IO uint32_t BUSHLDCTL;
    uint32_t RESERVED2[23];
} stc_efm_fwmc_bit_t;

typedef struct {
    __I  uint32_t PEWERR;
    __I  uint32_t PEPRTERR;
    __I  uint32_t PGSZERR;
    __I  uint32_t PGMISMTCH;
    __I  uint32_t OPTEND;
    __I  uint32_t COLERR;
    uint32_t RESERVED0[2];
    __I  uint32_t RDY;
    uint32_t RESERVED1[23];
} stc_efm_fsr_bit_t;

typedef struct {
    __IO uint32_t PEWERRCLR;
    __IO uint32_t PEPRTERRCLR;
    __IO uint32_t PGSZERRCLR;
    __IO uint32_t PGMISMTCHCLR;
    __IO uint32_t OPTENDCLR;
    __IO uint32_t COLERRCLR;
    uint32_t RESERVED0[26];
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
    __IO uint32_t PORTINEN;
    __IO uint32_t CMPEN0;
    __IO uint32_t CMPEN1;
    __IO uint32_t CMPEN2;
    uint32_t RESERVED0[1];
    __IO uint32_t OSCSTPEN;
    __IO uint32_t PWMSEN0;
    __IO uint32_t PWMSEN1;
    __IO uint32_t PWMSEN2;
    uint32_t RESERVED1[21];
    __IO uint32_t NFEN;
    __IO uint32_t INVSEL;
} stc_emb_ctl_bit_t;

typedef struct {
    __IO uint32_t PWMLV0;
    __IO uint32_t PWMLV1;
    __IO uint32_t PWMLV2;
    uint32_t RESERVED0[29];
} stc_emb_pwmlv_bit_t;

typedef struct {
    __IO uint32_t SOE;
    uint32_t RESERVED0[31];
} stc_emb_soe_bit_t;

typedef struct {
    __I  uint32_t PORTINF;
    __I  uint32_t PWMSF;
    __I  uint32_t CMPF;
    __I  uint32_t OSF;
    __I  uint32_t PORTINST;
    __I  uint32_t PWMST;
    uint32_t RESERVED0[26];
} stc_emb_stat_bit_t;

typedef struct {
    __O  uint32_t PORTINFCLR;
    __O  uint32_t PWMSFCLR;
    __O  uint32_t CMPFCLR;
    __O  uint32_t OSFCLR;
    uint32_t RESERVED0[28];
} stc_emb_statclr_bit_t;

typedef struct {
    __IO uint32_t PORTINTEN;
    __IO uint32_t PWMINTEN;
    __IO uint32_t CMPINTEN;
    __IO uint32_t OSINTEN;
    uint32_t RESERVED0[28];
} stc_emb_inten_bit_t;

typedef struct {
    __IO uint32_t LVR0;
    __IO uint32_t LVR1;
    __IO uint32_t LVR2;
    __IO uint32_t LVR3;
    __IO uint32_t LVR4;
    __IO uint32_t LVR5;
    __IO uint32_t LVR6;
    __IO uint32_t LVR7;
    __IO uint32_t LVR8;
    __IO uint32_t LVR9;
    __IO uint32_t LVR10;
    __IO uint32_t LVR11;
    __IO uint32_t LVR12;
    __IO uint32_t LVR13;
    __IO uint32_t LVR14;
    __IO uint32_t LVR15;
    uint32_t RESERVED0[16];
} stc_fcm_lvr_bit_t;

typedef struct {
    __IO uint32_t UVR0;
    __IO uint32_t UVR1;
    __IO uint32_t UVR2;
    __IO uint32_t UVR3;
    __IO uint32_t UVR4;
    __IO uint32_t UVR5;
    __IO uint32_t UVR6;
    __IO uint32_t UVR7;
    __IO uint32_t UVR8;
    __IO uint32_t UVR9;
    __IO uint32_t UVR10;
    __IO uint32_t UVR11;
    __IO uint32_t UVR12;
    __IO uint32_t UVR13;
    __IO uint32_t UVR14;
    __IO uint32_t UVR15;
    uint32_t RESERVED0[16];
} stc_fcm_uvr_bit_t;

typedef struct {
    __I  uint32_t CNTR0;
    __I  uint32_t CNTR1;
    __I  uint32_t CNTR2;
    __I  uint32_t CNTR3;
    __I  uint32_t CNTR4;
    __I  uint32_t CNTR5;
    __I  uint32_t CNTR6;
    __I  uint32_t CNTR7;
    __I  uint32_t CNTR8;
    __I  uint32_t CNTR9;
    __I  uint32_t CNTR10;
    __I  uint32_t CNTR11;
    __I  uint32_t CNTR12;
    __I  uint32_t CNTR13;
    __I  uint32_t CNTR14;
    __I  uint32_t CNTR15;
    uint32_t RESERVED0[16];
} stc_fcm_cntr_bit_t;

typedef struct {
    __IO uint32_t START;
    uint32_t RESERVED0[31];
} stc_fcm_str_bit_t;

typedef struct {
    __IO uint32_t MDIVS0;
    __IO uint32_t MDIVS1;
    uint32_t RESERVED0[2];
    __IO uint32_t MCKS0;
    __IO uint32_t MCKS1;
    __IO uint32_t MCKS2;
    __IO uint32_t MCKS3;
    uint32_t RESERVED1[24];
} stc_fcm_mccr_bit_t;

typedef struct {
    __IO uint32_t RDIVS0;
    __IO uint32_t RDIVS1;
    uint32_t RESERVED0[1];
    __IO uint32_t RCKS0;
    __IO uint32_t RCKS1;
    __IO uint32_t RCKS2;
    __IO uint32_t RCKS3;
    __IO uint32_t INEXS;
    __IO uint32_t DNFS0;
    __IO uint32_t DNFS1;
    uint32_t RESERVED1[2];
    __IO uint32_t EDGES0;
    __IO uint32_t EDGES1;
    uint32_t RESERVED2[1];
    __IO uint32_t EXREFE;
    uint32_t RESERVED3[16];
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
    __IO uint32_t POS00;
    __IO uint32_t POS01;
    __IO uint32_t POS02;
    __IO uint32_t POS03;
    __IO uint32_t POS04;
    __IO uint32_t POS05;
    __IO uint32_t POS06;
    __IO uint32_t POS07;
    __IO uint32_t POS08;
    __IO uint32_t POS09;
    __IO uint32_t POS10;
    __IO uint32_t POS11;
    __IO uint32_t POS12;
    __IO uint32_t POS13;
    __IO uint32_t POS14;
    __IO uint32_t POS15;
} stc_gpio_posr_bit_t;

typedef struct {
    __IO uint32_t POR00;
    __IO uint32_t POR01;
    __IO uint32_t POR02;
    __IO uint32_t POR03;
    __IO uint32_t POR04;
    __IO uint32_t POR05;
    __IO uint32_t POR06;
    __IO uint32_t POR07;
    __IO uint32_t POR08;
    __IO uint32_t POR09;
    __IO uint32_t POR10;
    __IO uint32_t POR11;
    __IO uint32_t POR12;
    __IO uint32_t POR13;
    __IO uint32_t POR14;
    __IO uint32_t POR15;
} stc_gpio_porr_bit_t;

typedef struct {
    __IO uint32_t POT00;
    __IO uint32_t POT01;
    __IO uint32_t POT02;
    __IO uint32_t POT03;
    __IO uint32_t POT04;
    __IO uint32_t POT05;
    __IO uint32_t POT06;
    __IO uint32_t POT07;
    __IO uint32_t POT08;
    __IO uint32_t POT09;
    __IO uint32_t POT10;
    __IO uint32_t POT11;
    __IO uint32_t POT12;
    __IO uint32_t POT13;
    __IO uint32_t POT14;
    __IO uint32_t POT15;
} stc_gpio_potr_bit_t;

typedef struct {
    __I  uint32_t PIN00;
    __I  uint32_t PIN01;
    __I  uint32_t PIN02;
    uint32_t RESERVED0[13];
} stc_gpio_pidrh_bit_t;

typedef struct {
    __IO uint32_t POUT00;
    __IO uint32_t POUT01;
    __IO uint32_t POUT02;
    uint32_t RESERVED0[13];
} stc_gpio_podrh_bit_t;

typedef struct {
    __IO uint32_t POUTE00;
    __IO uint32_t POUTE01;
    __IO uint32_t POUTE02;
    uint32_t RESERVED0[13];
} stc_gpio_poerh_bit_t;

typedef struct {
    __IO uint32_t POS00;
    __IO uint32_t POS01;
    __IO uint32_t POS02;
    uint32_t RESERVED0[13];
} stc_gpio_posrh_bit_t;

typedef struct {
    __IO uint32_t POR00;
    __IO uint32_t POR01;
    __IO uint32_t POR02;
    uint32_t RESERVED0[13];
} stc_gpio_porrh_bit_t;

typedef struct {
    __IO uint32_t POT00;
    __IO uint32_t POT01;
    __IO uint32_t POT02;
    uint32_t RESERVED0[13];
} stc_gpio_potrh_bit_t;

typedef struct {
    __IO uint32_t SPFE0;
    __IO uint32_t SPFE1;
    __IO uint32_t SPFE2;
    __IO uint32_t SPFE3;
    __IO uint32_t SPFE4;
    uint32_t RESERVED0[11];
} stc_gpio_pspcr_bit_t;

typedef struct {
    __IO uint32_t BFSEL0;
    __IO uint32_t BFSEL1;
    __IO uint32_t BFSEL2;
    __IO uint32_t BFSEL3;
    uint32_t RESERVED0[10];
    __IO uint32_t RDWT0;
    __IO uint32_t RDWT1;
} stc_gpio_pccr_bit_t;

typedef struct {
    __IO uint32_t PINAE0;
    __IO uint32_t PINAE1;
    __IO uint32_t PINAE2;
    __IO uint32_t PINAE3;
    __IO uint32_t PINAE4;
    __IO uint32_t PINAE5;
    uint32_t RESERVED0[10];
} stc_gpio_pinaer_bit_t;

typedef struct {
    __IO uint32_t WE;
    uint32_t RESERVED0[7];
    __O  uint32_t WP0;
    __O  uint32_t WP1;
    __O  uint32_t WP2;
    __O  uint32_t WP3;
    __O  uint32_t WP4;
    __O  uint32_t WP5;
    __O  uint32_t WP6;
    __O  uint32_t WP7;
} stc_gpio_pwpr_bit_t;

typedef struct {
    __IO uint32_t POUT;
    __IO uint32_t POUTE;
    __IO uint32_t NOD;
    uint32_t RESERVED0[1];
    __IO uint32_t DRV0;
    __IO uint32_t DRV1;
    __IO uint32_t PUU;
    uint32_t RESERVED1[1];
    __I  uint32_t PIN;
    __IO uint32_t INVE;
    uint32_t RESERVED2[2];
    __IO uint32_t INTE;
    uint32_t RESERVED3[1];
    __IO uint32_t LTE;
    __IO uint32_t DDIS;
} stc_gpio_pcr_bit_t;

typedef struct {
    __IO uint32_t FSEL0;
    __IO uint32_t FSEL1;
    __IO uint32_t FSEL2;
    __IO uint32_t FSEL3;
    __IO uint32_t FSEL4;
    __IO uint32_t FSEL5;
    uint32_t RESERVED0[2];
    __IO uint32_t BFE;
    uint32_t RESERVED1[7];
} stc_gpio_pfsr_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t FST_GRP;
    uint32_t RESERVED0[30];
} stc_hash_cr_bit_t;

typedef struct {
    __IO uint32_t PE;
    __IO uint32_t SMBUS;
    __IO uint32_t SMBALRTEN;
    __IO uint32_t SMBDEFAULTEN;
    __IO uint32_t SMBHOSTEN;
    uint32_t RESERVED0[1];
    __IO uint32_t GCEN;
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
    __IO uint32_t SLADDR00;
    __IO uint32_t SLADDR01;
    __IO uint32_t SLADDR02;
    __IO uint32_t SLADDR03;
    __IO uint32_t SLADDR04;
    __IO uint32_t SLADDR05;
    __IO uint32_t SLADDR06;
    __IO uint32_t SLADDR07;
    __IO uint32_t SLADDR08;
    __IO uint32_t SLADDR09;
    uint32_t RESERVED0[2];
    __IO uint32_t SLADDR0EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD0;
    uint32_t RESERVED2[16];
} stc_i2c_slr0_bit_t;

typedef struct {
    __IO uint32_t SLADDR10;
    __IO uint32_t SLADDR11;
    __IO uint32_t SLADDR12;
    __IO uint32_t SLADDR13;
    __IO uint32_t SLADDR14;
    __IO uint32_t SLADDR15;
    __IO uint32_t SLADDR16;
    __IO uint32_t SLADDR17;
    __IO uint32_t SLADDR18;
    __IO uint32_t SLADDR19;
    uint32_t RESERVED0[2];
    __IO uint32_t SLADDR1EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD1;
    uint32_t RESERVED2[16];
} stc_i2c_slr1_bit_t;

typedef struct {
    __IO uint32_t TOUTLOW0;
    __IO uint32_t TOUTLOW1;
    __IO uint32_t TOUTLOW2;
    __IO uint32_t TOUTLOW3;
    __IO uint32_t TOUTLOW4;
    __IO uint32_t TOUTLOW5;
    __IO uint32_t TOUTLOW6;
    __IO uint32_t TOUTLOW7;
    __IO uint32_t TOUTLOW8;
    __IO uint32_t TOUTLOW9;
    __IO uint32_t TOUTLOW10;
    __IO uint32_t TOUTLOW11;
    __IO uint32_t TOUTLOW12;
    __IO uint32_t TOUTLOW13;
    __IO uint32_t TOUTLOW14;
    __IO uint32_t TOUTLOW15;
    __IO uint32_t TOUTHIGH0;
    __IO uint32_t TOUTHIGH1;
    __IO uint32_t TOUTHIGH2;
    __IO uint32_t TOUTHIGH3;
    __IO uint32_t TOUTHIGH4;
    __IO uint32_t TOUTHIGH5;
    __IO uint32_t TOUTHIGH6;
    __IO uint32_t TOUTHIGH7;
    __IO uint32_t TOUTHIGH8;
    __IO uint32_t TOUTHIGH9;
    __IO uint32_t TOUTHIGH10;
    __IO uint32_t TOUTHIGH11;
    __IO uint32_t TOUTHIGH12;
    __IO uint32_t TOUTHIGH13;
    __IO uint32_t TOUTHIGH14;
    __IO uint32_t TOUTHIGH15;
} stc_i2c_sltr_bit_t;

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
    __O  uint32_t DT0;
    __O  uint32_t DT1;
    __O  uint32_t DT2;
    __O  uint32_t DT3;
    __O  uint32_t DT4;
    __O  uint32_t DT5;
    __O  uint32_t DT6;
    __O  uint32_t DT7;
} stc_i2c_dtr_bit_t;

typedef struct {
    __I  uint32_t DR0;
    __I  uint32_t DR1;
    __I  uint32_t DR2;
    __I  uint32_t DR3;
    __I  uint32_t DR4;
    __I  uint32_t DR5;
    __I  uint32_t DR6;
    __I  uint32_t DR7;
} stc_i2c_drr_bit_t;

typedef struct {
    __IO uint32_t SLOWW0;
    __IO uint32_t SLOWW1;
    __IO uint32_t SLOWW2;
    __IO uint32_t SLOWW3;
    __IO uint32_t SLOWW4;
    uint32_t RESERVED0[3];
    __IO uint32_t SHIGHW0;
    __IO uint32_t SHIGHW1;
    __IO uint32_t SHIGHW2;
    __IO uint32_t SHIGHW3;
    __IO uint32_t SHIGHW4;
    uint32_t RESERVED1[3];
    __IO uint32_t FREQ0;
    __IO uint32_t FREQ1;
    __IO uint32_t FREQ2;
    uint32_t RESERVED2[13];
} stc_i2c_ccr_bit_t;

typedef struct {
    __IO uint32_t DNF0;
    __IO uint32_t DNF1;
    uint32_t RESERVED0[2];
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
    __IO uint32_t TXBIRQWL0;
    __IO uint32_t TXBIRQWL1;
    __IO uint32_t TXBIRQWL2;
    uint32_t RESERVED0[1];
    __IO uint32_t RXBIRQWL0;
    __IO uint32_t RXBIRQWL1;
    __IO uint32_t RXBIRQWL2;
    uint32_t RESERVED1[1];
    __IO uint32_t FIFOR;
    __IO uint32_t CODECRC;
    __IO uint32_t I2SPLLSEL;
    __IO uint32_t SDOE;
    __IO uint32_t LRCKOE;
    __IO uint32_t CKOE;
    __IO uint32_t DUPLEX;
    __IO uint32_t CLKSEL;
    uint32_t RESERVED2[8];
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
    __IO uint32_t I2SSTD0;
    __IO uint32_t I2SSTD1;
    __IO uint32_t DATLEN0;
    __IO uint32_t DATLEN1;
    __IO uint32_t CHLEN;
    __IO uint32_t PCMSYNC;
    uint32_t RESERVED0[26];
} stc_i2s_cfgr_bit_t;

typedef struct {
    __IO uint32_t I2SDIV0;
    __IO uint32_t I2SDIV1;
    __IO uint32_t I2SDIV2;
    __IO uint32_t I2SDIV3;
    __IO uint32_t I2SDIV4;
    __IO uint32_t I2SDIV5;
    __IO uint32_t I2SDIV6;
    __IO uint32_t I2SDIV7;
    uint32_t RESERVED0[24];
} stc_i2s_pr_bit_t;

typedef struct {
    __I  uint32_t SWDTAUTS;
    __I  uint32_t SWDTITS;
    __I  uint32_t SWDTPERI0;
    __I  uint32_t SWDTPERI1;
    __I  uint32_t SWDTCKS0;
    __I  uint32_t SWDTCKS1;
    __I  uint32_t SWDTCKS2;
    __I  uint32_t SWDTCKS3;
    __I  uint32_t SWDTWDPT0;
    __I  uint32_t SWDTWDPT1;
    __I  uint32_t SWDTWDPT2;
    __I  uint32_t SWDTWDPT3;
    __I  uint32_t SWDTSLPOFF;
    uint32_t RESERVED0[3];
    __I  uint32_t WDTAUTS;
    __I  uint32_t WDTITS;
    __I  uint32_t WDTPERI0;
    __I  uint32_t WDTPERI1;
    __I  uint32_t WDTCKS0;
    __I  uint32_t WDTCKS1;
    __I  uint32_t WDTCKS2;
    __I  uint32_t WDTCKS3;
    __I  uint32_t WDTWDPT0;
    __I  uint32_t WDTWDPT1;
    __I  uint32_t WDTWDPT2;
    __I  uint32_t WDTWDPT3;
    __I  uint32_t WDTSLPOFF;
    uint32_t RESERVED1[3];
} stc_icg_icg0_bit_t;

typedef struct {
    __I  uint32_t HRCFREQSEL;
    uint32_t RESERVED0[7];
    __I  uint32_t HRCSTOP;
    uint32_t RESERVED1[7];
    __I  uint32_t BOR_LEV0;
    __I  uint32_t BOR_LEV1;
    __I  uint32_t BORDIS;
    uint32_t RESERVED2[7];
    __I  uint32_t SMPCLK0;
    __I  uint32_t SMPCLK1;
    __I  uint32_t NMITRG;
    __I  uint32_t NMIEN;
    __I  uint32_t NFEN;
    __I  uint32_t NMIICGEN;
} stc_icg_icg1_bit_t;

typedef struct {
    __IO uint32_t NMITRG;
    uint32_t RESERVED0[3];
    __IO uint32_t NSMPCLK0;
    __IO uint32_t NSMPCLK1;
    uint32_t RESERVED1[1];
    __IO uint32_t NFEN;
    uint32_t RESERVED2[24];
} stc_intc_nmicr_bit_t;

typedef struct {
    __IO uint32_t NMIENR;
    __IO uint32_t SWDTENR;
    __IO uint32_t PVD1ENR;
    __IO uint32_t PVD2ENR;
    uint32_t RESERVED0[1];
    __IO uint32_t XTALSTPENR;
    uint32_t RESERVED1[2];
    __IO uint32_t REPENR;
    __IO uint32_t RECCENR;
    __IO uint32_t BUSMENR;
    __IO uint32_t WDTENR;
    uint32_t RESERVED2[20];
} stc_intc_nmienr_bit_t;

typedef struct {
    __IO uint32_t NMIFR;
    __IO uint32_t SWDTFR;
    __IO uint32_t PVD1FR;
    __IO uint32_t PVD2FR;
    uint32_t RESERVED0[1];
    __IO uint32_t XTALSTPFR;
    uint32_t RESERVED1[2];
    __IO uint32_t REPFR;
    __IO uint32_t RECCFR;
    __IO uint32_t BUSMFR;
    __IO uint32_t WDTFR;
    uint32_t RESERVED2[20];
} stc_intc_nmifr_bit_t;

typedef struct {
    __IO uint32_t NMICFR;
    __IO uint32_t SWDTCFR;
    __IO uint32_t PVD1CFR;
    __IO uint32_t PVD2CFR;
    uint32_t RESERVED0[1];
    __IO uint32_t XTALSTPCFR;
    uint32_t RESERVED1[2];
    __IO uint32_t REPCFR;
    __IO uint32_t RECCCFR;
    __IO uint32_t BUSMCFR;
    __IO uint32_t WDTCFR;
    uint32_t RESERVED2[20];
} stc_intc_nmicfr_bit_t;

typedef struct {
    __IO uint32_t EIRQTRG0;
    __IO uint32_t EIRQTRG1;
    uint32_t RESERVED0[2];
    __IO uint32_t EISMPCLK0;
    __IO uint32_t EISMPCLK1;
    uint32_t RESERVED1[1];
    __IO uint32_t EFEN;
    uint32_t RESERVED2[24];
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
    __IO uint32_t CMPI0WUEN;
    __IO uint32_t WKTMWUEN;
    __IO uint32_t RTCALMWUEN;
    __IO uint32_t RTCPRDWUEN;
    __IO uint32_t TMR0WUEN;
    uint32_t RESERVED0[1];
    __IO uint32_t RXWUEN;
    uint32_t RESERVED1[6];
} stc_intc_wupen_bit_t;

typedef struct {
    __IO uint32_t EIRQFR0;
    __IO uint32_t EIRQFR1;
    __IO uint32_t EIRQFR2;
    __IO uint32_t EIRQFR3;
    __IO uint32_t EIRQFR4;
    __IO uint32_t EIRQFR5;
    __IO uint32_t EIRQFR6;
    __IO uint32_t EIRQFR7;
    __IO uint32_t EIRQFR8;
    __IO uint32_t EIRQFR9;
    __IO uint32_t EIRQFR10;
    __IO uint32_t EIRQFR11;
    __IO uint32_t EIRQFR12;
    __IO uint32_t EIRQFR13;
    __IO uint32_t EIRQFR14;
    __IO uint32_t EIRQFR15;
    uint32_t RESERVED0[16];
} stc_intc_eirqfr_bit_t;

typedef struct {
    __IO uint32_t EIRQCFR0;
    __IO uint32_t EIRQCFR1;
    __IO uint32_t EIRQCFR2;
    __IO uint32_t EIRQCFR3;
    __IO uint32_t EIRQCFR4;
    __IO uint32_t EIRQCFR5;
    __IO uint32_t EIRQCFR6;
    __IO uint32_t EIRQCFR7;
    __IO uint32_t EIRQCFR8;
    __IO uint32_t EIRQCFR9;
    __IO uint32_t EIRQCFR10;
    __IO uint32_t EIRQCFR11;
    __IO uint32_t EIRQCFR12;
    __IO uint32_t EIRQCFR13;
    __IO uint32_t EIRQCFR14;
    __IO uint32_t EIRQCFR15;
    uint32_t RESERVED0[16];
} stc_intc_eirqcfr_bit_t;

typedef struct {
    __IO uint32_t INTSEL0;
    __IO uint32_t INTSEL1;
    __IO uint32_t INTSEL2;
    __IO uint32_t INTSEL3;
    __IO uint32_t INTSEL4;
    __IO uint32_t INTSEL5;
    __IO uint32_t INTSEL6;
    __IO uint32_t INTSEL7;
    __IO uint32_t INTSEL8;
    uint32_t RESERVED0[23];
} stc_intc_sel_bit_t;

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
    __IO uint32_t KEYINSEL0;
    __IO uint32_t KEYINSEL1;
    __IO uint32_t KEYINSEL2;
    __IO uint32_t KEYINSEL3;
    __IO uint32_t KEYINSEL4;
    __IO uint32_t KEYINSEL5;
    __IO uint32_t KEYINSEL6;
    __IO uint32_t KEYINSEL7;
    __IO uint32_t KEYINSEL8;
    __IO uint32_t KEYINSEL9;
    __IO uint32_t KEYINSEL10;
    __IO uint32_t KEYINSEL11;
    __IO uint32_t KEYINSEL12;
    __IO uint32_t KEYINSEL13;
    __IO uint32_t KEYINSEL14;
    __IO uint32_t KEYINSEL15;
    __IO uint32_t KEYOUTSEL0;
    __IO uint32_t KEYOUTSEL1;
    __IO uint32_t KEYOUTSEL2;
    uint32_t RESERVED0[1];
    __IO uint32_t CKSEL0;
    __IO uint32_t CKSEL1;
    uint32_t RESERVED1[2];
    __IO uint32_t T_LLEVEL0;
    __IO uint32_t T_LLEVEL1;
    __IO uint32_t T_LLEVEL2;
    __IO uint32_t T_LLEVEL3;
    __IO uint32_t T_LLEVEL4;
    __IO uint32_t T_HIZ0;
    __IO uint32_t T_HIZ1;
    __IO uint32_t T_HIZ2;
} stc_keyscan_scr_bit_t;

typedef struct {
    __IO uint32_t SEN;
    uint32_t RESERVED0[31];
} stc_keyscan_ser_bit_t;

typedef struct {
    __IO uint32_t INDEX0;
    __IO uint32_t INDEX1;
    __IO uint32_t INDEX2;
    uint32_t RESERVED0[29];
} stc_keyscan_ssr_bit_t;

typedef struct {
    __IO uint32_t MPURGSIZE0;
    __IO uint32_t MPURGSIZE1;
    __IO uint32_t MPURGSIZE2;
    __IO uint32_t MPURGSIZE3;
    __IO uint32_t MPURGSIZE4;
    __IO uint32_t MPURGADDR0;
    __IO uint32_t MPURGADDR1;
    __IO uint32_t MPURGADDR2;
    __IO uint32_t MPURGADDR3;
    __IO uint32_t MPURGADDR4;
    __IO uint32_t MPURGADDR5;
    __IO uint32_t MPURGADDR6;
    __IO uint32_t MPURGADDR7;
    __IO uint32_t MPURGADDR8;
    __IO uint32_t MPURGADDR9;
    __IO uint32_t MPURGADDR10;
    __IO uint32_t MPURGADDR11;
    __IO uint32_t MPURGADDR12;
    __IO uint32_t MPURGADDR13;
    __IO uint32_t MPURGADDR14;
    __IO uint32_t MPURGADDR15;
    __IO uint32_t MPURGADDR16;
    __IO uint32_t MPURGADDR17;
    __IO uint32_t MPURGADDR18;
    __IO uint32_t MPURGADDR19;
    __IO uint32_t MPURGADDR20;
    __IO uint32_t MPURGADDR21;
    __IO uint32_t MPURGADDR22;
    __IO uint32_t MPURGADDR23;
    __IO uint32_t MPURGADDR24;
    __IO uint32_t MPURGADDR25;
    __IO uint32_t MPURGADDR26;
} stc_mpu_rgd_bit_t;

typedef struct {
    __IO uint32_t S2RGRP;
    __IO uint32_t S2RGWP;
    uint32_t RESERVED0[5];
    __IO uint32_t S2RGE;
    __IO uint32_t S1RGRP;
    __IO uint32_t S1RGWP;
    uint32_t RESERVED1[5];
    __IO uint32_t S1RGE;
    __IO uint32_t FRGRP;
    __IO uint32_t FRGWP;
    uint32_t RESERVED2[5];
    __IO uint32_t FRGE;
    uint32_t RESERVED3[8];
} stc_mpu_rgcr_bit_t;

typedef struct {
    __IO uint32_t SMPU2BRP;
    __IO uint32_t SMPU2BWP;
    __IO uint32_t SMPU2ACT0;
    __IO uint32_t SMPU2ACT1;
    uint32_t RESERVED0[3];
    __IO uint32_t SMPU2E;
    __IO uint32_t SMPU1BRP;
    __IO uint32_t SMPU1BWP;
    __IO uint32_t SMPU1ACT0;
    __IO uint32_t SMPU1ACT1;
    uint32_t RESERVED1[3];
    __IO uint32_t SMPU1E;
    __IO uint32_t FMPUBRP;
    __IO uint32_t FMPUBWP;
    __IO uint32_t FMPUACT0;
    __IO uint32_t FMPUACT1;
    uint32_t RESERVED2[3];
    __IO uint32_t FMPUE;
    uint32_t RESERVED3[8];
} stc_mpu_cr_bit_t;

typedef struct {
    __I  uint32_t SMPU2EAF;
    uint32_t RESERVED0[7];
    __I  uint32_t SMPU1EAF;
    uint32_t RESERVED1[7];
    __I  uint32_t FMPUEAF;
    uint32_t RESERVED2[15];
} stc_mpu_sr_bit_t;

typedef struct {
    __O  uint32_t SMPU2ECLR;
    uint32_t RESERVED0[7];
    __O  uint32_t SMPU1ECLR;
    uint32_t RESERVED1[7];
    __O  uint32_t FMPUECLR;
    uint32_t RESERVED2[15];
} stc_mpu_eclr_bit_t;

typedef struct {
    __IO uint32_t MPUWE;
    __O  uint32_t WKEY0;
    __O  uint32_t WKEY1;
    __O  uint32_t WKEY2;
    __O  uint32_t WKEY3;
    __O  uint32_t WKEY4;
    __O  uint32_t WKEY5;
    __O  uint32_t WKEY6;
    __O  uint32_t WKEY7;
    __O  uint32_t WKEY8;
    __O  uint32_t WKEY9;
    __O  uint32_t WKEY10;
    __O  uint32_t WKEY11;
    __O  uint32_t WKEY12;
    __O  uint32_t WKEY13;
    __O  uint32_t WKEY14;
    uint32_t RESERVED0[16];
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
    __IO uint32_t MSTPWRP;
    uint32_t RESERVED1[1];
    __IO uint32_t BUSERRE;
} stc_mpu_ippr_bit_t;

typedef struct {
    __IO uint32_t OTSST;
    __IO uint32_t OTSCK;
    __IO uint32_t OTSIE;
    __IO uint32_t TSSTP;
    uint32_t RESERVED0[12];
} stc_ots_ctl_bit_t;

typedef struct {
    __I  uint32_t TSOFS0;
    __I  uint32_t TSOFS1;
    __I  uint32_t TSOFS2;
    __I  uint32_t TSOFS3;
    __I  uint32_t TSOFS4;
    __I  uint32_t TSOFS5;
    __I  uint32_t TSOFS6;
    __I  uint32_t TSOFS7;
    __I  uint32_t TSSLP0;
    __I  uint32_t TSSLP1;
    __I  uint32_t TSSLP2;
    __I  uint32_t TSSLP3;
    __I  uint32_t TSSLP4;
    __I  uint32_t TSSLP5;
    __I  uint32_t TSSLP6;
    __I  uint32_t TSSLP7;
    __I  uint32_t TSSLP8;
    __I  uint32_t TSSLP9;
    __I  uint32_t TSSLP10;
    __I  uint32_t TSSLP11;
    __I  uint32_t TSSLP12;
    __I  uint32_t TSSLP13;
    __I  uint32_t TSSLP14;
    __I  uint32_t TSSLP15;
    __I  uint32_t TSSLP16;
    __I  uint32_t TSSLP17;
    __I  uint32_t TSSLP18;
    __I  uint32_t TSSLP19;
    __I  uint32_t TSSLP20;
    __I  uint32_t TSSLP21;
    __I  uint32_t TSSLP22;
    __I  uint32_t TSSLP23;
} stc_ots_lpr_bit_t;

typedef struct {
    __IO uint32_t DFB;
    __IO uint32_t SOFEN;
    uint32_t RESERVED0[30];
} stc_peric_usbfs_syctlreg_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SELMMC1;
    uint32_t RESERVED1[1];
    __IO uint32_t SELMMC2;
    uint32_t RESERVED2[28];
} stc_peric_sdioc_syctlreg_bit_t;

typedef struct {
    __IO uint32_t MDSEL0;
    __IO uint32_t MDSEL1;
    __IO uint32_t MDSEL2;
    __IO uint32_t PFE;
    __IO uint32_t PFSAE;
    __IO uint32_t DCOME;
    __IO uint32_t XIPE;
    __IO uint32_t SPIMD3;
    __IO uint32_t IPRSL0;
    __IO uint32_t IPRSL1;
    __IO uint32_t APRSL0;
    __IO uint32_t APRSL1;
    __IO uint32_t DPRSL0;
    __IO uint32_t DPRSL1;
    uint32_t RESERVED0[2];
    __IO uint32_t DIV0;
    __IO uint32_t DIV1;
    __IO uint32_t DIV2;
    __IO uint32_t DIV3;
    __IO uint32_t DIV4;
    __IO uint32_t DIV5;
    uint32_t RESERVED1[10];
} stc_qspi_cr_bit_t;

typedef struct {
    __IO uint32_t SSHW0;
    __IO uint32_t SSHW1;
    __IO uint32_t SSHW2;
    __IO uint32_t SSHW3;
    __IO uint32_t SSNW0;
    __IO uint32_t SSNW1;
    uint32_t RESERVED0[26];
} stc_qspi_cscr_bit_t;

typedef struct {
    __IO uint32_t AWSL0;
    __IO uint32_t AWSL1;
    __IO uint32_t FOUR_BIC;
    uint32_t RESERVED0[1];
    __IO uint32_t SSNHD;
    __IO uint32_t SSNLD;
    __IO uint32_t WPOL;
    uint32_t RESERVED1[1];
    __IO uint32_t DMCYCN0;
    __IO uint32_t DMCYCN1;
    __IO uint32_t DMCYCN2;
    __IO uint32_t DMCYCN3;
    uint32_t RESERVED2[3];
    __IO uint32_t DUTY;
    uint32_t RESERVED3[16];
} stc_qspi_fcr_bit_t;

typedef struct {
    __IO uint32_t BUSY;
    uint32_t RESERVED0[5];
    __IO uint32_t XIPF;
    __IO uint32_t RAER;
    __IO uint32_t PFNUM0;
    __IO uint32_t PFNUM1;
    __IO uint32_t PFNUM2;
    __IO uint32_t PFNUM3;
    __IO uint32_t PFNUM4;
    uint32_t RESERVED1[1];
    __IO uint32_t PFFUL;
    __IO uint32_t PFAN;
    uint32_t RESERVED2[16];
} stc_qspi_sr_bit_t;

typedef struct {
    __IO uint32_t DCOM0;
    __IO uint32_t DCOM1;
    __IO uint32_t DCOM2;
    __IO uint32_t DCOM3;
    __IO uint32_t DCOM4;
    __IO uint32_t DCOM5;
    __IO uint32_t DCOM6;
    __IO uint32_t DCOM7;
    uint32_t RESERVED0[24];
} stc_qspi_dcom_bit_t;

typedef struct {
    __IO uint32_t RIC0;
    __IO uint32_t RIC1;
    __IO uint32_t RIC2;
    __IO uint32_t RIC3;
    __IO uint32_t RIC4;
    __IO uint32_t RIC5;
    __IO uint32_t RIC6;
    __IO uint32_t RIC7;
    uint32_t RESERVED0[24];
} stc_qspi_ccmd_bit_t;

typedef struct {
    __IO uint32_t XIPMC0;
    __IO uint32_t XIPMC1;
    __IO uint32_t XIPMC2;
    __IO uint32_t XIPMC3;
    __IO uint32_t XIPMC4;
    __IO uint32_t XIPMC5;
    __IO uint32_t XIPMC6;
    __IO uint32_t XIPMC7;
    uint32_t RESERVED0[24];
} stc_qspi_xcmd_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __O  uint32_t RAERCLR;
    uint32_t RESERVED1[24];
} stc_qspi_sr2_bit_t;

typedef struct {
    uint32_t RESERVED0[26];
    __IO uint32_t EXADR0;
    __IO uint32_t EXADR1;
    __IO uint32_t EXADR2;
    __IO uint32_t EXADR3;
    __IO uint32_t EXADR4;
    __IO uint32_t EXADR5;
} stc_qspi_exar_bit_t;

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
    __IO uint32_t MULTIRF;
    __IO uint32_t CLRF;
} stc_rmu_rstf0_bit_t;

typedef struct {
    __IO uint32_t RESET;
    uint32_t RESERVED0[7];
} stc_rtc_cr0_bit_t;

typedef struct {
    __IO uint32_t PRDS0;
    __IO uint32_t PRDS1;
    __IO uint32_t PRDS2;
    __IO uint32_t AMPM;
    __IO uint32_t ALMFCLR;
    __IO uint32_t ONEHZOE;
    __IO uint32_t ONEHZSEL;
    __IO uint32_t START;
} stc_rtc_cr1_bit_t;

typedef struct {
    __IO uint32_t RWREQ;
    __IO uint32_t RWEN;
    uint32_t RESERVED0[1];
    __IO uint32_t ALMF;
    uint32_t RESERVED1[1];
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
    __IO uint32_t HOURU0;
    __IO uint32_t HOURU1;
    __IO uint32_t HOURU2;
    __IO uint32_t HOURU3;
    __IO uint32_t HOURD0;
    __IO uint32_t HOURD1;
    uint32_t RESERVED0[2];
} stc_rtc_hour_bit_t;

typedef struct {
    __IO uint32_t ALMHOURU0;
    __IO uint32_t ALMHOURU1;
    __IO uint32_t ALMHOURU2;
    __IO uint32_t ALMHOURU3;
    __IO uint32_t ALMHOURD0;
    __IO uint32_t ALMHOURD1;
    uint32_t RESERVED0[2];
} stc_rtc_almhour_bit_t;

typedef struct {
    __IO uint32_t ALMWEEK0;
    __IO uint32_t ALMWEEK1;
    __IO uint32_t ALMWEEK2;
    __IO uint32_t ALMWEEK3;
    __IO uint32_t ALMWEEK4;
    __IO uint32_t ALMWEEK5;
    __IO uint32_t ALMWEEK6;
    uint32_t RESERVED0[1];
} stc_rtc_almweek_bit_t;

typedef struct {
    __IO uint32_t COMP8;
    uint32_t RESERVED0[6];
    __IO uint32_t COMPEN;
} stc_rtc_errcrh_bit_t;

typedef struct {
    __IO uint32_t TBS0;
    __IO uint32_t TBS1;
    __IO uint32_t TBS2;
    __IO uint32_t TBS3;
    __IO uint32_t TBS4;
    __IO uint32_t TBS5;
    __IO uint32_t TBS6;
    __IO uint32_t TBS7;
    __IO uint32_t TBS8;
    __IO uint32_t TBS9;
    __IO uint32_t TBS10;
    __IO uint32_t TBS11;
    uint32_t RESERVED0[4];
} stc_sdioc_blksize_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t BCE;
    __IO uint32_t ATCEN0;
    __IO uint32_t ATCEN1;
    __IO uint32_t DDIR;
    __IO uint32_t MULB;
    uint32_t RESERVED1[10];
} stc_sdioc_transmode_bit_t;

typedef struct {
    __IO uint32_t RESTYP0;
    __IO uint32_t RESTYP1;
    uint32_t RESERVED0[1];
    __IO uint32_t CCE;
    __IO uint32_t ICE;
    __IO uint32_t DAT;
    __IO uint32_t TYP0;
    __IO uint32_t TYP1;
    __IO uint32_t IDX0;
    __IO uint32_t IDX1;
    __IO uint32_t IDX2;
    __IO uint32_t IDX3;
    __IO uint32_t IDX4;
    __IO uint32_t IDX5;
    uint32_t RESERVED1[2];
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
    __I  uint32_t DATL0;
    __I  uint32_t DATL1;
    __I  uint32_t DATL2;
    __I  uint32_t DATL3;
    __I  uint32_t CMDL;
    uint32_t RESERVED2[7];
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
    uint32_t RESERVED1[5];
    __IO uint32_t FS0;
    __IO uint32_t FS1;
    __IO uint32_t FS2;
    __IO uint32_t FS3;
    __IO uint32_t FS4;
    __IO uint32_t FS5;
    __IO uint32_t FS6;
    __IO uint32_t FS7;
} stc_sdioc_clkcon_bit_t;

typedef struct {
    __IO uint32_t DTO0;
    __IO uint32_t DTO1;
    __IO uint32_t DTO2;
    __IO uint32_t DTO3;
    uint32_t RESERVED0[4];
} stc_sdioc_toutcon_bit_t;

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
    __IO uint32_t FTHLV0;
    __IO uint32_t FTHLV1;
    uint32_t RESERVED0[4];
    __IO uint32_t SPRDTD;
    uint32_t RESERVED1[1];
    __IO uint32_t SS0PV;
    __IO uint32_t SS1PV;
    __IO uint32_t SS2PV;
    __IO uint32_t SS3PV;
    uint32_t RESERVED2[8];
    __IO uint32_t MSSI0;
    __IO uint32_t MSSI1;
    __IO uint32_t MSSI2;
    uint32_t RESERVED3[1];
    __IO uint32_t MSSDL0;
    __IO uint32_t MSSDL1;
    __IO uint32_t MSSDL2;
    uint32_t RESERVED4[1];
    __IO uint32_t MIDI0;
    __IO uint32_t MIDI1;
    __IO uint32_t MIDI2;
    uint32_t RESERVED5[1];
} stc_spi_cfg1_bit_t;

typedef struct {
    __IO uint32_t OVRERF;
    __I  uint32_t IDLNF;
    __IO uint32_t MODFERF;
    __IO uint32_t PERF;
    __IO uint32_t UDRERF;
    __IO uint32_t TDEF;
    uint32_t RESERVED0[1];
    __IO uint32_t RDFF;
    uint32_t RESERVED1[24];
} stc_spi_sr_bit_t;

typedef struct {
    __IO uint32_t CPHA;
    __IO uint32_t CPOL;
    __IO uint32_t MBR0;
    __IO uint32_t MBR1;
    __IO uint32_t MBR2;
    __IO uint32_t SSA0;
    __IO uint32_t SSA1;
    __IO uint32_t SSA2;
    __IO uint32_t DSIZE0;
    __IO uint32_t DSIZE1;
    __IO uint32_t DSIZE2;
    __IO uint32_t DSIZE3;
    __IO uint32_t LSBF;
    __IO uint32_t MIDIE;
    __IO uint32_t MSSDLE;
    __IO uint32_t MSSIE;
    uint32_t RESERVED0[16];
} stc_spi_cfg2_bit_t;

typedef struct {
    __IO uint32_t SRAM12_RWT0;
    __IO uint32_t SRAM12_RWT1;
    __IO uint32_t SRAM12_RWT2;
    uint32_t RESERVED0[1];
    __IO uint32_t SRAM12_WWT0;
    __IO uint32_t SRAM12_WWT1;
    __IO uint32_t SRAM12_WWT2;
    uint32_t RESERVED1[1];
    __IO uint32_t SRAM3_RWT0;
    __IO uint32_t SRAM3_RWT1;
    __IO uint32_t SRAM3_RWT2;
    uint32_t RESERVED2[1];
    __IO uint32_t SRAM3_WWT0;
    __IO uint32_t SRAM3_WWT1;
    __IO uint32_t SRAM3_WWT2;
    uint32_t RESERVED3[1];
    __IO uint32_t SRAMH_RWT0;
    __IO uint32_t SRAMH_RWT1;
    __IO uint32_t SRAMH_RWT2;
    uint32_t RESERVED4[1];
    __IO uint32_t SRAMH_WWT0;
    __IO uint32_t SRAMH_WWT1;
    __IO uint32_t SRAMH_WWT2;
    uint32_t RESERVED5[1];
    __IO uint32_t SRAMR_RWT0;
    __IO uint32_t SRAMR_RWT1;
    __IO uint32_t SRAMR_RWT2;
    uint32_t RESERVED6[1];
    __IO uint32_t SRAMR_WWT0;
    __IO uint32_t SRAMR_WWT1;
    __IO uint32_t SRAMR_WWT2;
    uint32_t RESERVED7[1];
} stc_sramc_wtcr_bit_t;

typedef struct {
    __IO uint32_t WTPRC;
    __IO uint32_t WTPRKW0;
    __IO uint32_t WTPRKW1;
    __IO uint32_t WTPRKW2;
    __IO uint32_t WTPRKW3;
    __IO uint32_t WTPRKW4;
    __IO uint32_t WTPRKW5;
    __IO uint32_t WTPRKW6;
    uint32_t RESERVED0[24];
} stc_sramc_wtpr_bit_t;

typedef struct {
    __IO uint32_t PYOAD;
    uint32_t RESERVED0[15];
    __IO uint32_t ECCOAD;
    uint32_t RESERVED1[7];
    __IO uint32_t ECCMOD0;
    __IO uint32_t ECCMOD1;
    uint32_t RESERVED2[6];
} stc_sramc_ckcr_bit_t;

typedef struct {
    __IO uint32_t CKPRC;
    __IO uint32_t CKPRKW0;
    __IO uint32_t CKPRKW1;
    __IO uint32_t CKPRKW2;
    __IO uint32_t CKPRKW3;
    __IO uint32_t CKPRKW4;
    __IO uint32_t CKPRKW5;
    __IO uint32_t CKPRKW6;
    uint32_t RESERVED0[24];
} stc_sramc_ckpr_bit_t;

typedef struct {
    __IO uint32_t SRAM3_1ERR;
    __IO uint32_t SRAM3_2ERR;
    __IO uint32_t SRAM12_PYERR;
    __IO uint32_t SRAMH_PYERR;
    __IO uint32_t SRAMR_PYERR;
    uint32_t RESERVED0[27];
} stc_sramc_cksr_bit_t;

typedef struct {
    __I  uint32_t CNT0;
    __I  uint32_t CNT1;
    __I  uint32_t CNT2;
    __I  uint32_t CNT3;
    __I  uint32_t CNT4;
    __I  uint32_t CNT5;
    __I  uint32_t CNT6;
    __I  uint32_t CNT7;
    __I  uint32_t CNT8;
    __I  uint32_t CNT9;
    __I  uint32_t CNT10;
    __I  uint32_t CNT11;
    __I  uint32_t CNT12;
    __I  uint32_t CNT13;
    __I  uint32_t CNT14;
    __I  uint32_t CNT15;
    __IO uint32_t UDF;
    __IO uint32_t REF;
    uint32_t RESERVED0[14];
} stc_swdt_sr_bit_t;

typedef struct {
    __IO uint32_t RF0;
    __IO uint32_t RF1;
    __IO uint32_t RF2;
    __IO uint32_t RF3;
    __IO uint32_t RF4;
    __IO uint32_t RF5;
    __IO uint32_t RF6;
    __IO uint32_t RF7;
    __IO uint32_t RF8;
    __IO uint32_t RF9;
    __IO uint32_t RF10;
    __IO uint32_t RF11;
    __IO uint32_t RF12;
    __IO uint32_t RF13;
    __IO uint32_t RF14;
    __IO uint32_t RF15;
    uint32_t RESERVED0[16];
} stc_swdt_rr_bit_t;

typedef struct {
    __IO uint32_t CNTA0;
    __IO uint32_t CNTA1;
    __IO uint32_t CNTA2;
    __IO uint32_t CNTA3;
    __IO uint32_t CNTA4;
    __IO uint32_t CNTA5;
    __IO uint32_t CNTA6;
    __IO uint32_t CNTA7;
    __IO uint32_t CNTA8;
    __IO uint32_t CNTA9;
    __IO uint32_t CNTA10;
    __IO uint32_t CNTA11;
    __IO uint32_t CNTA12;
    __IO uint32_t CNTA13;
    __IO uint32_t CNTA14;
    __IO uint32_t CNTA15;
    uint32_t RESERVED0[16];
} stc_tmr0_cntar_bit_t;

typedef struct {
    __IO uint32_t CNTB0;
    __IO uint32_t CNTB1;
    __IO uint32_t CNTB2;
    __IO uint32_t CNTB3;
    __IO uint32_t CNTB4;
    __IO uint32_t CNTB5;
    __IO uint32_t CNTB6;
    __IO uint32_t CNTB7;
    __IO uint32_t CNTB8;
    __IO uint32_t CNTB9;
    __IO uint32_t CNTB10;
    __IO uint32_t CNTB11;
    __IO uint32_t CNTB12;
    __IO uint32_t CNTB13;
    __IO uint32_t CNTB14;
    __IO uint32_t CNTB15;
    uint32_t RESERVED0[16];
} stc_tmr0_cntbr_bit_t;

typedef struct {
    __IO uint32_t CMPA0;
    __IO uint32_t CMPA1;
    __IO uint32_t CMPA2;
    __IO uint32_t CMPA3;
    __IO uint32_t CMPA4;
    __IO uint32_t CMPA5;
    __IO uint32_t CMPA6;
    __IO uint32_t CMPA7;
    __IO uint32_t CMPA8;
    __IO uint32_t CMPA9;
    __IO uint32_t CMPA10;
    __IO uint32_t CMPA11;
    __IO uint32_t CMPA12;
    __IO uint32_t CMPA13;
    __IO uint32_t CMPA14;
    __IO uint32_t CMPA15;
    uint32_t RESERVED0[16];
} stc_tmr0_cmpar_bit_t;

typedef struct {
    __IO uint32_t CMPB0;
    __IO uint32_t CMPB1;
    __IO uint32_t CMPB2;
    __IO uint32_t CMPB3;
    __IO uint32_t CMPB4;
    __IO uint32_t CMPB5;
    __IO uint32_t CMPB6;
    __IO uint32_t CMPB7;
    __IO uint32_t CMPB8;
    __IO uint32_t CMPB9;
    __IO uint32_t CMPB10;
    __IO uint32_t CMPB11;
    __IO uint32_t CMPB12;
    __IO uint32_t CMPB13;
    __IO uint32_t CMPB14;
    __IO uint32_t CMPB15;
    uint32_t RESERVED0[16];
} stc_tmr0_cmpbr_bit_t;

typedef struct {
    __IO uint32_t CSTA;
    __IO uint32_t CAPMDA;
    __IO uint32_t INTENA;
    uint32_t RESERVED0[1];
    __IO uint32_t CKDIVA0;
    __IO uint32_t CKDIVA1;
    __IO uint32_t CKDIVA2;
    __IO uint32_t CKDIVA3;
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
    uint32_t RESERVED2[1];
    __IO uint32_t CKDIVB0;
    __IO uint32_t CKDIVB1;
    __IO uint32_t CKDIVB2;
    __IO uint32_t CKDIVB3;
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
    __IO uint32_t CHBUFEN0;
    __IO uint32_t CHBUFEN1;
    __IO uint32_t CLBUFEN0;
    __IO uint32_t CLBUFEN1;
    __IO uint32_t MHBUFEN0;
    __IO uint32_t MHBUFEN1;
    __IO uint32_t MLBUFEN0;
    __IO uint32_t MLBUFEN1;
    __IO uint32_t LMCH;
    __IO uint32_t LMCL;
    __IO uint32_t LMMH;
    __IO uint32_t LMML;
    __IO uint32_t MCECH;
    __IO uint32_t MCECL;
    uint32_t RESERVED0[2];
} stc_tmr4_ocer_bit_t;

typedef struct {
    __IO uint32_t OCFDCH;
    __IO uint32_t OCFPKH;
    __IO uint32_t OCFUCH;
    __IO uint32_t OCFZRH;
    __IO uint32_t OPDCH0;
    __IO uint32_t OPDCH1;
    __IO uint32_t OPPKH0;
    __IO uint32_t OPPKH1;
    __IO uint32_t OPUCH0;
    __IO uint32_t OPUCH1;
    __IO uint32_t OPZRH0;
    __IO uint32_t OPZRH1;
    __IO uint32_t OPNPKH0;
    __IO uint32_t OPNPKH1;
    __IO uint32_t OPNZRH0;
    __IO uint32_t OPNZRH1;
} stc_tmr4_ocmrh_bit_t;

typedef struct {
    __IO uint32_t OCFDCL;
    __IO uint32_t OCFPKL;
    __IO uint32_t OCFUCL;
    __IO uint32_t OCFZRL;
    __IO uint32_t OPDCL0;
    __IO uint32_t OPDCL1;
    __IO uint32_t OPPKL0;
    __IO uint32_t OPPKL1;
    __IO uint32_t OPUCL0;
    __IO uint32_t OPUCL1;
    __IO uint32_t OPZRL0;
    __IO uint32_t OPZRL1;
    __IO uint32_t OPNPKL0;
    __IO uint32_t OPNPKL1;
    __IO uint32_t OPNZRL0;
    __IO uint32_t OPNZRL1;
    __IO uint32_t EOPNDCL0;
    __IO uint32_t EOPNDCL1;
    __IO uint32_t EOPNUCL0;
    __IO uint32_t EOPNUCL1;
    __IO uint32_t EOPDCL0;
    __IO uint32_t EOPDCL1;
    __IO uint32_t EOPPKL0;
    __IO uint32_t EOPPKL1;
    __IO uint32_t EOPUCL0;
    __IO uint32_t EOPUCL1;
    __IO uint32_t EOPZRL0;
    __IO uint32_t EOPZRL1;
    __IO uint32_t EOPNPKL0;
    __IO uint32_t EOPNPKL1;
    __IO uint32_t EOPNZRL0;
    __IO uint32_t EOPNZRL1;
} stc_tmr4_ocmrl_bit_t;

typedef struct {
    __IO uint32_t CKDIV0;
    __IO uint32_t CKDIV1;
    __IO uint32_t CKDIV2;
    __IO uint32_t CKDIV3;
    __IO uint32_t CLEAR;
    __IO uint32_t MODE;
    __IO uint32_t STOP;
    __IO uint32_t BUFEN;
    __IO uint32_t IRQPEN;
    __IO uint32_t IRQPF;
    uint32_t RESERVED0[3];
    __IO uint32_t IRQZEN;
    __IO uint32_t IRQZF;
    __IO uint32_t ECKEN;
} stc_tmr4_ccsr_bit_t;

typedef struct {
    __IO uint32_t ZIM0;
    __IO uint32_t ZIM1;
    __IO uint32_t ZIM2;
    __IO uint32_t ZIM3;
    __IO uint32_t PIM0;
    __IO uint32_t PIM1;
    __IO uint32_t PIM2;
    __IO uint32_t PIM3;
    __I  uint32_t ZIC0;
    __I  uint32_t ZIC1;
    __I  uint32_t ZIC2;
    __I  uint32_t ZIC3;
    __I  uint32_t PIC0;
    __I  uint32_t PIC1;
    __I  uint32_t PIC2;
    __I  uint32_t PIC3;
} stc_tmr4_cvpr_bit_t;

typedef struct {
    __IO uint32_t DIVCK0;
    __IO uint32_t DIVCK1;
    __IO uint32_t DIVCK2;
    uint32_t RESERVED0[1];
    __IO uint32_t PWMMD0;
    __IO uint32_t PWMMD1;
    __IO uint32_t LVLS0;
    __IO uint32_t LVLS1;
    uint32_t RESERVED1[8];
} stc_tmr4_pocr_bit_t;

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
    __IO uint32_t BUFEN0;
    __IO uint32_t BUFEN1;
    __IO uint32_t EVTOS0;
    __IO uint32_t EVTOS1;
    __IO uint32_t EVTOS2;
    __IO uint32_t LMC;
    uint32_t RESERVED0[2];
    __IO uint32_t EVTMS;
    __IO uint32_t EVTDS;
    uint32_t RESERVED1[2];
    __IO uint32_t DEN;
    __IO uint32_t PEN;
    __IO uint32_t UEN;
    __IO uint32_t ZEN;
} stc_tmr4_scsr_bit_t;

typedef struct {
    __IO uint32_t AMC0;
    __IO uint32_t AMC1;
    __IO uint32_t AMC2;
    __IO uint32_t AMC3;
    uint32_t RESERVED0[2];
    __IO uint32_t MZCE;
    __IO uint32_t MPCE;
    uint32_t RESERVED1[8];
} stc_tmr4_scmr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t HOLD;
    uint32_t RESERVED1[8];
} stc_tmr4_ecsr_bit_t;

typedef struct {
    __IO uint32_t EMBVAL0;
    __IO uint32_t EMBVAL1;
    uint32_t RESERVED0[30];
} stc_tmr4cr_ecer1_bit_t;

typedef struct {
    __IO uint32_t EMBVAL0;
    __IO uint32_t EMBVAL1;
    uint32_t RESERVED0[30];
} stc_tmr4cr_ecer2_bit_t;

typedef struct {
    __IO uint32_t EMBVAL0;
    __IO uint32_t EMBVAL1;
    uint32_t RESERVED0[30];
} stc_tmr4cr_ecer3_bit_t;

typedef struct {
    __IO uint32_t CNT0;
    __IO uint32_t CNT1;
    __IO uint32_t CNT2;
    __IO uint32_t CNT3;
    __IO uint32_t CNT4;
    __IO uint32_t CNT5;
    __IO uint32_t CNT6;
    __IO uint32_t CNT7;
    __IO uint32_t CNT8;
    __IO uint32_t CNT9;
    __IO uint32_t CNT10;
    __IO uint32_t CNT11;
    __IO uint32_t CNT12;
    __IO uint32_t CNT13;
    __IO uint32_t CNT14;
    __IO uint32_t CNT15;
    uint32_t RESERVED0[16];
} stc_tmr6_cnter_bit_t;

typedef struct {
    __IO uint32_t PERA0;
    __IO uint32_t PERA1;
    __IO uint32_t PERA2;
    __IO uint32_t PERA3;
    __IO uint32_t PERA4;
    __IO uint32_t PERA5;
    __IO uint32_t PERA6;
    __IO uint32_t PERA7;
    __IO uint32_t PERA8;
    __IO uint32_t PERA9;
    __IO uint32_t PERA10;
    __IO uint32_t PERA11;
    __IO uint32_t PERA12;
    __IO uint32_t PERA13;
    __IO uint32_t PERA14;
    __IO uint32_t PERA15;
    uint32_t RESERVED0[16];
} stc_tmr6_perar_bit_t;

typedef struct {
    __IO uint32_t PERB0;
    __IO uint32_t PERB1;
    __IO uint32_t PERB2;
    __IO uint32_t PERB3;
    __IO uint32_t PERB4;
    __IO uint32_t PERB5;
    __IO uint32_t PERB6;
    __IO uint32_t PERB7;
    __IO uint32_t PERB8;
    __IO uint32_t PERB9;
    __IO uint32_t PERB10;
    __IO uint32_t PERB11;
    __IO uint32_t PERB12;
    __IO uint32_t PERB13;
    __IO uint32_t PERB14;
    __IO uint32_t PERB15;
    uint32_t RESERVED0[16];
} stc_tmr6_perbr_bit_t;

typedef struct {
    __IO uint32_t PERC0;
    __IO uint32_t PERC1;
    __IO uint32_t PERC2;
    __IO uint32_t PERC3;
    __IO uint32_t PERC4;
    __IO uint32_t PERC5;
    __IO uint32_t PERC6;
    __IO uint32_t PERC7;
    __IO uint32_t PERC8;
    __IO uint32_t PERC9;
    __IO uint32_t PERC10;
    __IO uint32_t PERC11;
    __IO uint32_t PERC12;
    __IO uint32_t PERC13;
    __IO uint32_t PERC14;
    __IO uint32_t PERC15;
    uint32_t RESERVED0[16];
} stc_tmr6_percr_bit_t;

typedef struct {
    __IO uint32_t GCMA0;
    __IO uint32_t GCMA1;
    __IO uint32_t GCMA2;
    __IO uint32_t GCMA3;
    __IO uint32_t GCMA4;
    __IO uint32_t GCMA5;
    __IO uint32_t GCMA6;
    __IO uint32_t GCMA7;
    __IO uint32_t GCMA8;
    __IO uint32_t GCMA9;
    __IO uint32_t GCMA10;
    __IO uint32_t GCMA11;
    __IO uint32_t GCMA12;
    __IO uint32_t GCMA13;
    __IO uint32_t GCMA14;
    __IO uint32_t GCMA15;
    uint32_t RESERVED0[16];
} stc_tmr6_gcmar_bit_t;

typedef struct {
    __IO uint32_t GCMB0;
    __IO uint32_t GCMB1;
    __IO uint32_t GCMB2;
    __IO uint32_t GCMB3;
    __IO uint32_t GCMB4;
    __IO uint32_t GCMB5;
    __IO uint32_t GCMB6;
    __IO uint32_t GCMB7;
    __IO uint32_t GCMB8;
    __IO uint32_t GCMB9;
    __IO uint32_t GCMB10;
    __IO uint32_t GCMB11;
    __IO uint32_t GCMB12;
    __IO uint32_t GCMB13;
    __IO uint32_t GCMB14;
    __IO uint32_t GCMB15;
    uint32_t RESERVED0[16];
} stc_tmr6_gcmbr_bit_t;

typedef struct {
    __IO uint32_t GCMC0;
    __IO uint32_t GCMC1;
    __IO uint32_t GCMC2;
    __IO uint32_t GCMC3;
    __IO uint32_t GCMC4;
    __IO uint32_t GCMC5;
    __IO uint32_t GCMC6;
    __IO uint32_t GCMC7;
    __IO uint32_t GCMC8;
    __IO uint32_t GCMC9;
    __IO uint32_t GCMC10;
    __IO uint32_t GCMC11;
    __IO uint32_t GCMC12;
    __IO uint32_t GCMC13;
    __IO uint32_t GCMC14;
    __IO uint32_t GCMC15;
    uint32_t RESERVED0[16];
} stc_tmr6_gcmcr_bit_t;

typedef struct {
    __IO uint32_t GCMD0;
    __IO uint32_t GCMD1;
    __IO uint32_t GCMD2;
    __IO uint32_t GCMD3;
    __IO uint32_t GCMD4;
    __IO uint32_t GCMD5;
    __IO uint32_t GCMD6;
    __IO uint32_t GCMD7;
    __IO uint32_t GCMD8;
    __IO uint32_t GCMD9;
    __IO uint32_t GCMD10;
    __IO uint32_t GCMD11;
    __IO uint32_t GCMD12;
    __IO uint32_t GCMD13;
    __IO uint32_t GCMD14;
    __IO uint32_t GCMD15;
    uint32_t RESERVED0[16];
} stc_tmr6_gcmdr_bit_t;

typedef struct {
    __IO uint32_t GCME0;
    __IO uint32_t GCME1;
    __IO uint32_t GCME2;
    __IO uint32_t GCME3;
    __IO uint32_t GCME4;
    __IO uint32_t GCME5;
    __IO uint32_t GCME6;
    __IO uint32_t GCME7;
    __IO uint32_t GCME8;
    __IO uint32_t GCME9;
    __IO uint32_t GCME10;
    __IO uint32_t GCME11;
    __IO uint32_t GCME12;
    __IO uint32_t GCME13;
    __IO uint32_t GCME14;
    __IO uint32_t GCME15;
    uint32_t RESERVED0[16];
} stc_tmr6_gcmer_bit_t;

typedef struct {
    __IO uint32_t GCMF0;
    __IO uint32_t GCMF1;
    __IO uint32_t GCMF2;
    __IO uint32_t GCMF3;
    __IO uint32_t GCMF4;
    __IO uint32_t GCMF5;
    __IO uint32_t GCMF6;
    __IO uint32_t GCMF7;
    __IO uint32_t GCMF8;
    __IO uint32_t GCMF9;
    __IO uint32_t GCMF10;
    __IO uint32_t GCMF11;
    __IO uint32_t GCMF12;
    __IO uint32_t GCMF13;
    __IO uint32_t GCMF14;
    __IO uint32_t GCMF15;
    uint32_t RESERVED0[16];
} stc_tmr6_gcmfr_bit_t;

typedef struct {
    __IO uint32_t SCMA0;
    __IO uint32_t SCMA1;
    __IO uint32_t SCMA2;
    __IO uint32_t SCMA3;
    __IO uint32_t SCMA4;
    __IO uint32_t SCMA5;
    __IO uint32_t SCMA6;
    __IO uint32_t SCMA7;
    __IO uint32_t SCMA8;
    __IO uint32_t SCMA9;
    __IO uint32_t SCMA10;
    __IO uint32_t SCMA11;
    __IO uint32_t SCMA12;
    __IO uint32_t SCMA13;
    __IO uint32_t SCMA14;
    __IO uint32_t SCMA15;
    uint32_t RESERVED0[16];
} stc_tmr6_scmar_bit_t;

typedef struct {
    __IO uint32_t SCMB0;
    __IO uint32_t SCMB1;
    __IO uint32_t SCMB2;
    __IO uint32_t SCMB3;
    __IO uint32_t SCMB4;
    __IO uint32_t SCMB5;
    __IO uint32_t SCMB6;
    __IO uint32_t SCMB7;
    __IO uint32_t SCMB8;
    __IO uint32_t SCMB9;
    __IO uint32_t SCMB10;
    __IO uint32_t SCMB11;
    __IO uint32_t SCMB12;
    __IO uint32_t SCMB13;
    __IO uint32_t SCMB14;
    __IO uint32_t SCMB15;
    uint32_t RESERVED0[16];
} stc_tmr6_scmbr_bit_t;

typedef struct {
    __IO uint32_t SCMC0;
    __IO uint32_t SCMC1;
    __IO uint32_t SCMC2;
    __IO uint32_t SCMC3;
    __IO uint32_t SCMC4;
    __IO uint32_t SCMC5;
    __IO uint32_t SCMC6;
    __IO uint32_t SCMC7;
    __IO uint32_t SCMC8;
    __IO uint32_t SCMC9;
    __IO uint32_t SCMC10;
    __IO uint32_t SCMC11;
    __IO uint32_t SCMC12;
    __IO uint32_t SCMC13;
    __IO uint32_t SCMC14;
    __IO uint32_t SCMC15;
    uint32_t RESERVED0[16];
} stc_tmr6_scmcr_bit_t;

typedef struct {
    __IO uint32_t SCMD0;
    __IO uint32_t SCMD1;
    __IO uint32_t SCMD2;
    __IO uint32_t SCMD3;
    __IO uint32_t SCMD4;
    __IO uint32_t SCMD5;
    __IO uint32_t SCMD6;
    __IO uint32_t SCMD7;
    __IO uint32_t SCMD8;
    __IO uint32_t SCMD9;
    __IO uint32_t SCMD10;
    __IO uint32_t SCMD11;
    __IO uint32_t SCMD12;
    __IO uint32_t SCMD13;
    __IO uint32_t SCMD14;
    __IO uint32_t SCMD15;
    uint32_t RESERVED0[16];
} stc_tmr6_scmdr_bit_t;

typedef struct {
    __IO uint32_t SCME0;
    __IO uint32_t SCME1;
    __IO uint32_t SCME2;
    __IO uint32_t SCME3;
    __IO uint32_t SCME4;
    __IO uint32_t SCME5;
    __IO uint32_t SCME6;
    __IO uint32_t SCME7;
    __IO uint32_t SCME8;
    __IO uint32_t SCME9;
    __IO uint32_t SCME10;
    __IO uint32_t SCME11;
    __IO uint32_t SCME12;
    __IO uint32_t SCME13;
    __IO uint32_t SCME14;
    __IO uint32_t SCME15;
    uint32_t RESERVED0[16];
} stc_tmr6_scmer_bit_t;

typedef struct {
    __IO uint32_t SCMF0;
    __IO uint32_t SCMF1;
    __IO uint32_t SCMF2;
    __IO uint32_t SCMF3;
    __IO uint32_t SCMF4;
    __IO uint32_t SCMF5;
    __IO uint32_t SCMF6;
    __IO uint32_t SCMF7;
    __IO uint32_t SCMF8;
    __IO uint32_t SCMF9;
    __IO uint32_t SCMF10;
    __IO uint32_t SCMF11;
    __IO uint32_t SCMF12;
    __IO uint32_t SCMF13;
    __IO uint32_t SCMF14;
    __IO uint32_t SCMF15;
    uint32_t RESERVED0[16];
} stc_tmr6_scmfr_bit_t;

typedef struct {
    __IO uint32_t DTUA0;
    __IO uint32_t DTUA1;
    __IO uint32_t DTUA2;
    __IO uint32_t DTUA3;
    __IO uint32_t DTUA4;
    __IO uint32_t DTUA5;
    __IO uint32_t DTUA6;
    __IO uint32_t DTUA7;
    __IO uint32_t DTUA8;
    __IO uint32_t DTUA9;
    __IO uint32_t DTUA10;
    __IO uint32_t DTUA11;
    __IO uint32_t DTUA12;
    __IO uint32_t DTUA13;
    __IO uint32_t DTUA14;
    __IO uint32_t DTUA15;
    uint32_t RESERVED0[16];
} stc_tmr6_dtuar_bit_t;

typedef struct {
    __IO uint32_t DTDA0;
    __IO uint32_t DTDA1;
    __IO uint32_t DTDA2;
    __IO uint32_t DTDA3;
    __IO uint32_t DTDA4;
    __IO uint32_t DTDA5;
    __IO uint32_t DTDA6;
    __IO uint32_t DTDA7;
    __IO uint32_t DTDA8;
    __IO uint32_t DTDA9;
    __IO uint32_t DTDA10;
    __IO uint32_t DTDA11;
    __IO uint32_t DTDA12;
    __IO uint32_t DTDA13;
    __IO uint32_t DTDA14;
    __IO uint32_t DTDA15;
    uint32_t RESERVED0[16];
} stc_tmr6_dtdar_bit_t;

typedef struct {
    __IO uint32_t DTUB0;
    __IO uint32_t DTUB1;
    __IO uint32_t DTUB2;
    __IO uint32_t DTUB3;
    __IO uint32_t DTUB4;
    __IO uint32_t DTUB5;
    __IO uint32_t DTUB6;
    __IO uint32_t DTUB7;
    __IO uint32_t DTUB8;
    __IO uint32_t DTUB9;
    __IO uint32_t DTUB10;
    __IO uint32_t DTUB11;
    __IO uint32_t DTUB12;
    __IO uint32_t DTUB13;
    __IO uint32_t DTUB14;
    __IO uint32_t DTUB15;
    uint32_t RESERVED0[16];
} stc_tmr6_dtubr_bit_t;

typedef struct {
    __IO uint32_t DTDB0;
    __IO uint32_t DTDB1;
    __IO uint32_t DTDB2;
    __IO uint32_t DTDB3;
    __IO uint32_t DTDB4;
    __IO uint32_t DTDB5;
    __IO uint32_t DTDB6;
    __IO uint32_t DTDB7;
    __IO uint32_t DTDB8;
    __IO uint32_t DTDB9;
    __IO uint32_t DTDB10;
    __IO uint32_t DTDB11;
    __IO uint32_t DTDB12;
    __IO uint32_t DTDB13;
    __IO uint32_t DTDB14;
    __IO uint32_t DTDB15;
    uint32_t RESERVED0[16];
} stc_tmr6_dtdbr_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t MODE0;
    __IO uint32_t MODE1;
    __IO uint32_t MODE2;
    __IO uint32_t CKDIV0;
    __IO uint32_t CKDIV1;
    __IO uint32_t CKDIV2;
    uint32_t RESERVED0[1];
    __IO uint32_t DIR;
    uint32_t RESERVED1[7];
    __IO uint32_t ZMSKREV;
    __IO uint32_t ZMSKPOS;
    __IO uint32_t ZMSKVAL0;
    __IO uint32_t ZMSKVAL1;
    uint32_t RESERVED2[12];
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
    __IO uint32_t CAPMDA;
    __IO uint32_t STACA;
    __IO uint32_t STPCA;
    __IO uint32_t STASTPSA;
    __IO uint32_t CMPCA0;
    __IO uint32_t CMPCA1;
    __IO uint32_t PERCA0;
    __IO uint32_t PERCA1;
    __IO uint32_t OUTENA;
    uint32_t RESERVED0[2];
    __IO uint32_t EMBVALA0;
    __IO uint32_t EMBVALA1;
    uint32_t RESERVED1[3];
    __IO uint32_t CAPMDB;
    __IO uint32_t STACB;
    __IO uint32_t STPCB;
    __IO uint32_t STASTPSB;
    __IO uint32_t CMPCB0;
    __IO uint32_t CMPCB1;
    __IO uint32_t PERCB0;
    __IO uint32_t PERCB1;
    __IO uint32_t OUTENB;
    uint32_t RESERVED2[2];
    __IO uint32_t EMBVALB0;
    __IO uint32_t EMBVALB1;
    uint32_t RESERVED3[3];
} stc_tmr6_pconr_bit_t;

typedef struct {
    __IO uint32_t BENA;
    __IO uint32_t BSEA;
    __IO uint32_t BENB;
    __IO uint32_t BSEB;
    uint32_t RESERVED0[4];
    __IO uint32_t BENP;
    __IO uint32_t BSEP;
    uint32_t RESERVED1[6];
    __IO uint32_t BENSPA;
    __IO uint32_t BSESPA;
    uint32_t RESERVED2[2];
    __IO uint32_t BTRUSPA;
    __IO uint32_t BTRDSPA;
    uint32_t RESERVED3[2];
    __IO uint32_t BENSPB;
    __IO uint32_t BSESPB;
    uint32_t RESERVED4[2];
    __IO uint32_t BTRUSPB;
    __IO uint32_t BTRDSPB;
    uint32_t RESERVED5[2];
} stc_tmr6_bconr_bit_t;

typedef struct {
    __IO uint32_t DTCEN;
    uint32_t RESERVED0[3];
    __IO uint32_t DTBENU;
    __IO uint32_t DTBEND;
    uint32_t RESERVED1[2];
    __IO uint32_t SEPA;
    uint32_t RESERVED2[23];
} stc_tmr6_dconr_bit_t;

typedef struct {
    __IO uint32_t NOFIENGA;
    __IO uint32_t NOFICKGA0;
    __IO uint32_t NOFICKGA1;
    uint32_t RESERVED0[1];
    __IO uint32_t NOFIENGB;
    __IO uint32_t NOFICKGB0;
    __IO uint32_t NOFICKGB1;
    uint32_t RESERVED1[9];
    __IO uint32_t NOFIENTA;
    __IO uint32_t NOFICKTA0;
    __IO uint32_t NOFICKTA1;
    uint32_t RESERVED2[1];
    __IO uint32_t NOFIENTB;
    __IO uint32_t NOFICKTB0;
    __IO uint32_t NOFICKTB1;
    uint32_t RESERVED3[9];
} stc_tmr6_fconr_bit_t;

typedef struct {
    uint32_t RESERVED0[8];
    __IO uint32_t SPPERIA;
    __IO uint32_t SPPERIB;
    uint32_t RESERVED1[6];
    __IO uint32_t PCNTE0;
    __IO uint32_t PCNTE1;
    __IO uint32_t PCNTS0;
    __IO uint32_t PCNTS1;
    __IO uint32_t PCNTS2;
    uint32_t RESERVED2[11];
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
    uint32_t RESERVED0[8];
    __I  uint32_t VPERNUM0;
    __I  uint32_t VPERNUM1;
    __I  uint32_t VPERNUM2;
    uint32_t RESERVED1[7];
    __I  uint32_t DIRF;
} stc_tmr6_stflr_bit_t;

typedef struct {
    __IO uint32_t HSTA0;
    __IO uint32_t HSTA1;
    uint32_t RESERVED0[2];
    __IO uint32_t HSTA4;
    __IO uint32_t HSTA5;
    __IO uint32_t HSTA6;
    __IO uint32_t HSTA7;
    __IO uint32_t HSTA8;
    __IO uint32_t HSTA9;
    __IO uint32_t HSTA10;
    __IO uint32_t HSTA11;
    uint32_t RESERVED1[19];
    __IO uint32_t STAS;
} stc_tmr6_hstar_bit_t;

typedef struct {
    __IO uint32_t HSTP0;
    __IO uint32_t HSTP1;
    uint32_t RESERVED0[2];
    __IO uint32_t HSTP4;
    __IO uint32_t HSTP5;
    __IO uint32_t HSTP6;
    __IO uint32_t HSTP7;
    __IO uint32_t HSTP8;
    __IO uint32_t HSTP9;
    __IO uint32_t HSTP10;
    __IO uint32_t HSTP11;
    uint32_t RESERVED1[19];
    __IO uint32_t STPS;
} stc_tmr6_hstpr_bit_t;

typedef struct {
    __IO uint32_t HCLE0;
    __IO uint32_t HCLE1;
    uint32_t RESERVED0[2];
    __IO uint32_t HCLE4;
    __IO uint32_t HCLE5;
    __IO uint32_t HCLE6;
    __IO uint32_t HCLE7;
    __IO uint32_t HCLE8;
    __IO uint32_t HCLE9;
    __IO uint32_t HCLE10;
    __IO uint32_t HCLE11;
    uint32_t RESERVED1[19];
    __IO uint32_t CLES;
} stc_tmr6_hclrr_bit_t;

typedef struct {
    __IO uint32_t HCPA0;
    __IO uint32_t HCPA1;
    uint32_t RESERVED0[2];
    __IO uint32_t HCPA4;
    __IO uint32_t HCPA5;
    __IO uint32_t HCPA6;
    __IO uint32_t HCPA7;
    __IO uint32_t HCPA8;
    __IO uint32_t HCPA9;
    __IO uint32_t HCPA10;
    __IO uint32_t HCPA11;
    uint32_t RESERVED1[20];
} stc_tmr6_hcpar_bit_t;

typedef struct {
    __IO uint32_t HCPB0;
    __IO uint32_t HCPB1;
    uint32_t RESERVED0[2];
    __IO uint32_t HCPB4;
    __IO uint32_t HCPB5;
    __IO uint32_t HCPB6;
    __IO uint32_t HCPB7;
    __IO uint32_t HCPB8;
    __IO uint32_t HCPB9;
    __IO uint32_t HCPB10;
    __IO uint32_t HCPB11;
    uint32_t RESERVED1[20];
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
    uint32_t RESERVED1[14];
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
    uint32_t RESERVED1[14];
} stc_tmr6_hcdor_bit_t;

typedef struct {
    __IO uint32_t SSTA1;
    __IO uint32_t SSTA2;
    __IO uint32_t SSTA3;
    uint32_t RESERVED0[29];
} stc_tmr6cr_sstar_bit_t;

typedef struct {
    __IO uint32_t SSTP1;
    __IO uint32_t SSTP2;
    __IO uint32_t SSTP3;
    uint32_t RESERVED0[29];
} stc_tmr6cr_sstpr_bit_t;

typedef struct {
    __IO uint32_t SCLE1;
    __IO uint32_t SCLE2;
    __IO uint32_t SCLE3;
    uint32_t RESERVED0[29];
} stc_tmr6cr_sclrr_bit_t;

typedef struct {
    __IO uint32_t START;
    __IO uint32_t DIR;
    __IO uint32_t MODE;
    __IO uint32_t SYNST;
    uint32_t RESERVED0[8];
    __IO uint32_t ITENOVF;
    __IO uint32_t ITENUDF;
    __IO uint32_t OVFF;
    __IO uint32_t UDFF;
} stc_tmra_bcstr_bit_t;

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
    __IO uint32_t ITEN5;
    __IO uint32_t ITEN6;
    __IO uint32_t ITEN7;
    __IO uint32_t ITEN8;
    uint32_t RESERVED0[8];
} stc_tmra_iconr_bit_t;

typedef struct {
    __IO uint32_t ETEN1;
    __IO uint32_t ETEN2;
    __IO uint32_t ETEN3;
    __IO uint32_t ETEN4;
    __IO uint32_t ETEN5;
    __IO uint32_t ETEN6;
    __IO uint32_t ETEN7;
    __IO uint32_t ETEN8;
    uint32_t RESERVED0[8];
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
    __IO uint32_t CMPF5;
    __IO uint32_t CMPF6;
    __IO uint32_t CMPF7;
    __IO uint32_t CMPF8;
    uint32_t RESERVED0[8];
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
    __IO uint32_t NOFICKCP0;
    __IO uint32_t NOFICKCP1;
    uint32_t RESERVED3[1];
} stc_tmra_cconr_bit_t;

typedef struct {
    __IO uint32_t STAC0;
    __IO uint32_t STAC1;
    __IO uint32_t STPC0;
    __IO uint32_t STPC1;
    __IO uint32_t CMPC0;
    __IO uint32_t CMPC1;
    __IO uint32_t PERC0;
    __IO uint32_t PERC1;
    __IO uint32_t FORC0;
    __IO uint32_t FORC1;
    uint32_t RESERVED0[2];
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
    uint32_t RESERVED0[1];
    __IO uint32_t CNT0;
    __IO uint32_t CNT1;
    __IO uint32_t CNT2;
    uint32_t RESERVED1[27];
} stc_trng_mr_bit_t;

typedef struct {
    __I  uint32_t PE;
    __I  uint32_t FE;
    uint32_t RESERVED0[1];
    __I  uint32_t ORE;
    uint32_t RESERVED1[1];
    __I  uint32_t RXNE;
    __I  uint32_t TC;
    __I  uint32_t TXE;
    __I  uint32_t RTOF;
    uint32_t RESERVED2[7];
    __I  uint32_t MPB;
    uint32_t RESERVED3[15];
} stc_usart_sr_bit_t;

typedef struct {
    uint32_t RESERVED0[9];
    __IO uint32_t MPID;
    uint32_t RESERVED1[22];
} stc_usart_dr_bit_t;

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
    __O  uint32_t CPE;
    __O  uint32_t CFE;
    uint32_t RESERVED3[1];
    __O  uint32_t CORE;
    __O  uint32_t CRTOF;
    uint32_t RESERVED4[3];
    __IO uint32_t MS;
    uint32_t RESERVED5[3];
    __IO uint32_t ML;
    __IO uint32_t FBME;
    __IO uint32_t NFE;
    __IO uint32_t SBS;
} stc_usart_cr1_bit_t;

typedef struct {
    __IO uint32_t MPE;
    uint32_t RESERVED0[10];
    __IO uint32_t CLKC0;
    __IO uint32_t CLKC1;
    __IO uint32_t STOP;
    uint32_t RESERVED1[18];
} stc_usart_cr2_bit_t;

typedef struct {
    uint32_t RESERVED0[5];
    __IO uint32_t SCEN;
    uint32_t RESERVED1[3];
    __IO uint32_t CTSE;
    uint32_t RESERVED2[11];
    __IO uint32_t BCN0;
    __IO uint32_t BCN1;
    __IO uint32_t BCN2;
    uint32_t RESERVED3[8];
} stc_usart_cr3_bit_t;

typedef struct {
    __IO uint32_t PSC0;
    __IO uint32_t PSC1;
    uint32_t RESERVED0[30];
} stc_usart_pr_bit_t;

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
    uint32_t RESERVED4[1];
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
    uint32_t RESERVED5[1];
    __IO uint32_t CIDSCHGM;
    __IO uint32_t DISCIM;
    __IO uint32_t VBUSVIM;
    __IO uint32_t WKUIM;
} stc_usbfs_gintmsk_bit_t;

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
    uint32_t RESERVED0[1];
    __IO uint32_t STALL;
    __IO uint32_t NAK;
    __IO uint32_t ACK;
    uint32_t RESERVED1[1];
    __IO uint32_t TXERR;
    __IO uint32_t BBERR;
    __IO uint32_t FRMOR;
    __IO uint32_t DTERR;
    uint32_t RESERVED2[21];
} stc_usbfs_hcint_bit_t;

typedef struct {
    __IO uint32_t XFRCM;
    __IO uint32_t CHHM;
    uint32_t RESERVED0[1];
    __IO uint32_t STALLM;
    __IO uint32_t NAKM;
    __IO uint32_t ACKM;
    uint32_t RESERVED1[1];
    __IO uint32_t TXERRM;
    __IO uint32_t BBERRM;
    __IO uint32_t FRMORM;
    __IO uint32_t DTERRM;
    uint32_t RESERVED2[21];
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
    __O  uint32_t SGINAK;
    __O  uint32_t CGINAK;
    __O  uint32_t SGONAK;
    __O  uint32_t CGONAK;
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
    __IO uint32_t ITTXFEMSK;
    __IO uint32_t INEPNMM;
    __IO uint32_t INEPNEM;
    uint32_t RESERVED1[25];
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
    __IO uint32_t EPDIS;
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
    __I  uint32_t USBAEP;
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
    uint32_t RESERVED0[30];
} stc_usbfs_gcctl_bit_t;

typedef struct {
    __IO uint32_t PERI0;
    __IO uint32_t PERI1;
    uint32_t RESERVED0[2];
    __IO uint32_t CKS0;
    __IO uint32_t CKS1;
    __IO uint32_t CKS2;
    __IO uint32_t CKS3;
    __IO uint32_t WDPT0;
    __IO uint32_t WDPT1;
    __IO uint32_t WDPT2;
    __IO uint32_t WDPT3;
    uint32_t RESERVED1[4];
    __IO uint32_t SLPOFF;
    uint32_t RESERVED2[14];
    __IO uint32_t ITS;
} stc_wdt_cr_bit_t;

typedef struct {
    __I  uint32_t CNT0;
    __I  uint32_t CNT1;
    __I  uint32_t CNT2;
    __I  uint32_t CNT3;
    __I  uint32_t CNT4;
    __I  uint32_t CNT5;
    __I  uint32_t CNT6;
    __I  uint32_t CNT7;
    __I  uint32_t CNT8;
    __I  uint32_t CNT9;
    __I  uint32_t CNT10;
    __I  uint32_t CNT11;
    __I  uint32_t CNT12;
    __I  uint32_t CNT13;
    __I  uint32_t CNT14;
    __I  uint32_t CNT15;
    __IO uint32_t UDF;
    __IO uint32_t REF;
    uint32_t RESERVED0[14];
} stc_wdt_sr_bit_t;

typedef struct {
    __IO uint32_t RF0;
    __IO uint32_t RF1;
    __IO uint32_t RF2;
    __IO uint32_t RF3;
    __IO uint32_t RF4;
    __IO uint32_t RF5;
    __IO uint32_t RF6;
    __IO uint32_t RF7;
    __IO uint32_t RF8;
    __IO uint32_t RF9;
    __IO uint32_t RF10;
    __IO uint32_t RF11;
    __IO uint32_t RF12;
    __IO uint32_t RF13;
    __IO uint32_t RF14;
    __IO uint32_t RF15;
    uint32_t RESERVED0[16];
} stc_wdt_rr_bit_t;


typedef struct {
    stc_adc_str_bit_t                        STR_b;
    uint32_t                                 RESERVED0[8];
    stc_adc_cr0_bit_t                        CR0_b;
    stc_adc_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED1[32];
    stc_adc_trgsr_bit_t                      TRGSR_b;
    uint32_t                                 RESERVED2[352];
    stc_adc_chmuxr0_bit_t                    CHMUXR0_b;
    stc_adc_chmuxr1_bit_t                    CHMUXR1_b;
    stc_adc_chmuxr2_bit_t                    CHMUXR2_b;
    stc_adc_chmuxr3_bit_t                    CHMUXR3_b;
    uint32_t                                 RESERVED3[48];
    stc_adc_isr_bit_t                        ISR_b;
    stc_adc_icr_bit_t                        ICR_b;
    uint32_t                                 RESERVED4[32];
    stc_adc_synccr_bit_t                     SYNCCR_b;
    uint32_t                                 RESERVED5[656];
    stc_adc_awdcr_bit_t                      AWDCR_b;
    uint32_t                                 RESERVED6[240];
    stc_adc_pgacr_bit_t                      PGACR_b;
    stc_adc_pgagsr_bit_t                     PGAGSR_b;
    uint32_t                                 RESERVED7[64];
    stc_adc_pgainsr0_bit_t                   PGAINSR0_b;
    stc_adc_pgainsr1_bit_t                   PGAINSR1_b;
} bCM_ADC_TypeDef;

typedef struct {
    stc_aes_cr_bit_t                         CR_b;
} bCM_AES_TypeDef;

typedef struct {
    stc_aos_intsfttrg_bit_t                  INTSFTTRG_b;
    stc_aos_dcu_trgsel_bit_t                 DCU_TRGSEL1_b;
    stc_aos_dcu_trgsel_bit_t                 DCU_TRGSEL2_b;
    stc_aos_dcu_trgsel_bit_t                 DCU_TRGSEL3_b;
    stc_aos_dcu_trgsel_bit_t                 DCU_TRGSEL4_b;
    stc_aos_dma1_trgsel_bit_t                DMA1_TRGSEL0_b;
    stc_aos_dma1_trgsel_bit_t                DMA1_TRGSEL1_b;
    stc_aos_dma1_trgsel_bit_t                DMA1_TRGSEL2_b;
    stc_aos_dma1_trgsel_bit_t                DMA1_TRGSEL3_b;
    stc_aos_dma2_trgsel_bit_t                DMA2_TRGSEL0_b;
    stc_aos_dma2_trgsel_bit_t                DMA2_TRGSEL1_b;
    stc_aos_dma2_trgsel_bit_t                DMA2_TRGSEL2_b;
    stc_aos_dma2_trgsel_bit_t                DMA2_TRGSEL3_b;
    stc_aos_dma_trgselrc_bit_t               DMA_TRGSELRC_b;
    stc_aos_tmr6_htssr_bit_t                 TMR6_HTSSR0_b;
    stc_aos_tmr6_htssr_bit_t                 TMR6_HTSSR1_b;
    stc_aos_tmr0_htssr_bit_t                 TMR0_HTSSR_b;
    stc_aos_pevnttrgsr_bit_t                 PEVNTTRGSR12_b;
    stc_aos_pevnttrgsr_bit_t                 PEVNTTRGSR34_b;
    stc_aos_tmra_htssr_bit_t                 TMRA_HTSSR0_b;
    stc_aos_tmra_htssr_bit_t                 TMRA_HTSSR1_b;
    stc_aos_ots_trg_bit_t                    OTS_TRG_b;
    stc_aos_adc1_itrgselr_bit_t              ADC1_ITRGSELR0_b;
    stc_aos_adc1_itrgselr_bit_t              ADC1_ITRGSELR1_b;
    stc_aos_adc2_itrgselr_bit_t              ADC2_ITRGSELR0_b;
    stc_aos_adc2_itrgselr_bit_t              ADC2_ITRGSELR1_b;
    uint32_t                                 RESERVED0[1216];
    stc_aos_pevntdirr_bit_t                  PEVNTDIRR1_b;
    stc_aos_pevntidr_bit_t                   PEVNTIDR1_b;
    stc_aos_pevntodr_bit_t                   PEVNTODR1_b;
    stc_aos_pevntorr_bit_t                   PEVNTORR1_b;
    stc_aos_pevntosr_bit_t                   PEVNTOSR1_b;
    stc_aos_pevntrisr_bit_t                  PEVNTRISR1_b;
    stc_aos_pevntfal_bit_t                   PEVNTFAL1_b;
    stc_aos_pevntdirr_bit_t                  PEVNTDIRR2_b;
    stc_aos_pevntidr_bit_t                   PEVNTIDR2_b;
    stc_aos_pevntodr_bit_t                   PEVNTODR2_b;
    stc_aos_pevntorr_bit_t                   PEVNTORR2_b;
    stc_aos_pevntosr_bit_t                   PEVNTOSR2_b;
    stc_aos_pevntrisr_bit_t                  PEVNTRISR2_b;
    stc_aos_pevntfal_bit_t                   PEVNTFAL2_b;
    stc_aos_pevntdirr_bit_t                  PEVNTDIRR3_b;
    stc_aos_pevntidr_bit_t                   PEVNTIDR3_b;
    stc_aos_pevntodr_bit_t                   PEVNTODR3_b;
    stc_aos_pevntorr_bit_t                   PEVNTORR3_b;
    stc_aos_pevntosr_bit_t                   PEVNTOSR3_b;
    stc_aos_pevntrisr_bit_t                  PEVNTRISR3_b;
    stc_aos_pevntfal_bit_t                   PEVNTFAL3_b;
    stc_aos_pevntdirr_bit_t                  PEVNTDIRR4_b;
    stc_aos_pevntidr_bit_t                   PEVNTIDR4_b;
    stc_aos_pevntodr_bit_t                   PEVNTODR4_b;
    stc_aos_pevntorr_bit_t                   PEVNTORR4_b;
    stc_aos_pevntosr_bit_t                   PEVNTOSR4_b;
    stc_aos_pevntrisr_bit_t                  PEVNTRISR4_b;
    stc_aos_pevntfal_bit_t                   PEVNTFAL4_b;
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
    stc_can_limit_bit_t                      LIMIT_b;
    stc_can_sbt_bit_t                        SBT_b;
    uint32_t                                 RESERVED1[32];
    stc_can_ealcap_bit_t                     EALCAP_b;
    uint32_t                                 RESERVED2[24];
    stc_can_acfctrl_bit_t                    ACFCTRL_b;
    uint32_t                                 RESERVED3[8];
    stc_can_acfen_bit_t                      ACFEN_b;
    uint32_t                                 RESERVED4[8];
    stc_can_acf_bit_t                        ACF_b;
    uint32_t                                 RESERVED5[16];
    stc_can_tbslot_bit_t                     TBSLOT_b;
    stc_can_ttcfg_bit_t                      TTCFG_b;
    stc_can_ref_msg_bit_t                    REF_MSG_b;
    stc_can_trg_cfg_bit_t                    TRG_CFG_b;
} bCM_CAN_TypeDef;

typedef struct {
    stc_cmp_ctrl_bit_t                       CTRL_b;
    stc_cmp_vltsel_bit_t                     VLTSEL_b;
    stc_cmp_outmon_bit_t                     OUTMON_b;
    stc_cmp_cvsstb_bit_t                     CVSSTB_b;
    stc_cmp_cvsprd_bit_t                     CVSPRD_b;
} bCM_CMP_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[2112];
    stc_cmpcr_dacr_bit_t                     DACR_b;
    uint32_t                                 RESERVED1[16];
    stc_cmpcr_rvadc_bit_t                    RVADC_b;
} bCM_CMPCR_TypeDef;

typedef struct {
    stc_crc_cr_bit_t                         CR_b;
    stc_crc_reslt_bit_t                      RESLT_b;
    uint32_t                                 RESERVED0[32];
    stc_crc_flg_bit_t                        FLG_b;
} bCM_CRC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[128];
    stc_dbgc_mcustat_bit_t                   MCUSTAT_b;
    stc_dbgc_mcuctl_bit_t                    MCUCTL_b;
    stc_dbgc_fmcctl_bit_t                    FMCCTL_b;
    stc_dbgc_mcudbgstat_bit_t                MCUDBGSTAT_b;
    stc_dbgc_mcustpctl_bit_t                 MCUSTPCTL_b;
    stc_dbgc_mcutracectl_bit_t               MCUTRACECTL_b;
} bCM_DBGC_TypeDef;

typedef struct {
    stc_dcu_ctl_bit_t                        CTL_b;
    stc_dcu_flag_bit_t                       FLAG_b;
    uint32_t                                 RESERVED0[96];
    stc_dcu_flagclr_bit_t                    FLAGCLR_b;
    stc_dcu_intsel_bit_t                     INTSEL_b;
} bCM_DCU_TypeDef;

typedef struct {
    stc_dma_en_bit_t                         EN_b;
    stc_dma_intstat0_bit_t                   INTSTAT0_b;
    stc_dma_intstat1_bit_t                   INTSTAT1_b;
    stc_dma_intmask0_bit_t                   INTMASK0_b;
    stc_dma_intmask1_bit_t                   INTMASK1_b;
    stc_dma_intclr0_bit_t                    INTCLR0_b;
    stc_dma_intclr1_bit_t                    INTCLR1_b;
    stc_dma_chen_bit_t                       CHEN_b;
    stc_dma_reqstat_bit_t                    REQSTAT_b;
    stc_dma_chstat_bit_t                     CHSTAT_b;
    uint32_t                                 RESERVED0[32];
    stc_dma_rcfgctl_bit_t                    RCFGCTL_b;
    uint32_t                                 RESERVED1[256];
    stc_dma_rptb_bit_t                       RPTB0_b;
    uint32_t                                 RESERVED2[32];
    stc_dma_snseqctlb_bit_t                  SNSEQCTLB0_b;
    uint32_t                                 RESERVED3[32];
    stc_dma_dnseqctlb_bit_t                  DNSEQCTLB0_b;
    uint32_t                                 RESERVED4[32];
    stc_dma_chctl_bit_t                      CHCTL0_b;
    uint32_t                                 RESERVED5[384];
    stc_dma_rptb_bit_t                       RPTB1_b;
    uint32_t                                 RESERVED6[32];
    stc_dma_snseqctlb_bit_t                  SNSEQCTLB1_b;
    uint32_t                                 RESERVED7[32];
    stc_dma_dnseqctlb_bit_t                  DNSEQCTLB1_b;
    uint32_t                                 RESERVED8[32];
    stc_dma_chctl_bit_t                      CHCTL1_b;
    uint32_t                                 RESERVED9[384];
    stc_dma_rptb_bit_t                       RPTB2_b;
    uint32_t                                 RESERVED10[32];
    stc_dma_snseqctlb_bit_t                  SNSEQCTLB2_b;
    uint32_t                                 RESERVED11[32];
    stc_dma_dnseqctlb_bit_t                  DNSEQCTLB2_b;
    uint32_t                                 RESERVED12[32];
    stc_dma_chctl_bit_t                      CHCTL2_b;
    uint32_t                                 RESERVED13[384];
    stc_dma_rptb_bit_t                       RPTB3_b;
    uint32_t                                 RESERVED14[32];
    stc_dma_snseqctlb_bit_t                  SNSEQCTLB3_b;
    uint32_t                                 RESERVED15[32];
    stc_dma_dnseqctlb_bit_t                  DNSEQCTLB3_b;
    uint32_t                                 RESERVED16[32];
    stc_dma_chctl_bit_t                      CHCTL3_b;
} bCM_DMA_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_efm_fstp_bit_t                       FSTP_b;
    stc_efm_frmc_bit_t                       FRMC_b;
    stc_efm_fwmc_bit_t                       FWMC_b;
    stc_efm_fsr_bit_t                        FSR_b;
    stc_efm_fsclr_bit_t                      FSCLR_b;
    stc_efm_fite_bit_t                       FITE_b;
    stc_efm_fswp_bit_t                       FSWP_b;
    uint32_t                                 RESERVED1[1824];
    stc_efm_mmf_remcr_bit_t                  MMF_REMCR0_b;
    stc_efm_mmf_remcr_bit_t                  MMF_REMCR1_b;
} bCM_EFM_TypeDef;

typedef struct {
    stc_emb_ctl_bit_t                        CTL_b;
    stc_emb_pwmlv_bit_t                      PWMLV_b;
    stc_emb_soe_bit_t                        SOE_b;
    stc_emb_stat_bit_t                       STAT_b;
    stc_emb_statclr_bit_t                    STATCLR_b;
    stc_emb_inten_bit_t                      INTEN_b;
} bCM_EMB_TypeDef;

typedef struct {
    stc_fcm_lvr_bit_t                        LVR_b;
    stc_fcm_uvr_bit_t                        UVR_b;
    stc_fcm_cntr_bit_t                       CNTR_b;
    stc_fcm_str_bit_t                        STR_b;
    stc_fcm_mccr_bit_t                       MCCR_b;
    stc_fcm_rccr_bit_t                       RCCR_b;
    stc_fcm_rier_bit_t                       RIER_b;
    stc_fcm_sr_bit_t                         SR_b;
    stc_fcm_clr_bit_t                        CLR_b;
} bCM_FCM_TypeDef;

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
    stc_gpio_pidrh_bit_t                     PIDRH_b;
    uint32_t                                 RESERVED10[16];
    stc_gpio_podrh_bit_t                     PODRH_b;
    stc_gpio_poerh_bit_t                     POERH_b;
    stc_gpio_posrh_bit_t                     POSRH_b;
    stc_gpio_porrh_bit_t                     PORRH_b;
    stc_gpio_potrh_bit_t                     POTRH_b;
    uint32_t                                 RESERVED11[7344];
    stc_gpio_pspcr_bit_t                     PSPCR_b;
    uint32_t                                 RESERVED12[16];
    stc_gpio_pccr_bit_t                      PCCR_b;
    stc_gpio_pinaer_bit_t                    PINAER_b;
    stc_gpio_pwpr_bit_t                      PWPR_b;
    uint32_t                                 RESERVED13[16];
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
    stc_gpio_pcr_bit_t                       PCRH0_b;
    stc_gpio_pfsr_bit_t                      PFSRH0_b;
    stc_gpio_pcr_bit_t                       PCRH1_b;
    stc_gpio_pfsr_bit_t                      PFSRH1_b;
    stc_gpio_pcr_bit_t                       PCRH2_b;
    stc_gpio_pfsr_bit_t                      PFSRH2_b;
} bCM_GPIO_TypeDef;

typedef struct {
    stc_hash_cr_bit_t                        CR_b;
} bCM_HASH_TypeDef;

typedef struct {
    stc_i2c_cr1_bit_t                        CR1_b;
    stc_i2c_cr2_bit_t                        CR2_b;
    stc_i2c_cr3_bit_t                        CR3_b;
    stc_i2c_cr4_bit_t                        CR4_b;
    stc_i2c_slr0_bit_t                       SLR0_b;
    stc_i2c_slr1_bit_t                       SLR1_b;
    stc_i2c_sltr_bit_t                       SLTR_b;
    stc_i2c_sr_bit_t                         SR_b;
    stc_i2c_clr_bit_t                        CLR_b;
    stc_i2c_dtr_bit_t                        DTR_b;
    uint32_t                                 RESERVED0[24];
    stc_i2c_drr_bit_t                        DRR_b;
    uint32_t                                 RESERVED1[24];
    stc_i2c_ccr_bit_t                        CCR_b;
    stc_i2c_fltr_bit_t                       FLTR_b;
} bCM_I2C_TypeDef;

typedef struct {
    stc_i2s_ctrl_bit_t                       CTRL_b;
    stc_i2s_sr_bit_t                         SR_b;
    stc_i2s_er_bit_t                         ER_b;
    stc_i2s_cfgr_bit_t                       CFGR_b;
    uint32_t                                 RESERVED0[64];
    stc_i2s_pr_bit_t                         PR_b;
} bCM_I2S_TypeDef;

typedef struct {
    stc_icg_icg0_bit_t                       ICG0_b;
    stc_icg_icg1_bit_t                       ICG1_b;
} bCM_ICG_TypeDef;

typedef struct {
    stc_intc_nmicr_bit_t                     NMICR_b;
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
    stc_intc_eirqfr_bit_t                    EIRQFR_b;
    stc_intc_eirqcfr_bit_t                   EIRQCFR_b;
    stc_intc_sel_bit_t                       SEL0_b;
    stc_intc_sel_bit_t                       SEL1_b;
    stc_intc_sel_bit_t                       SEL2_b;
    stc_intc_sel_bit_t                       SEL3_b;
    stc_intc_sel_bit_t                       SEL4_b;
    stc_intc_sel_bit_t                       SEL5_b;
    stc_intc_sel_bit_t                       SEL6_b;
    stc_intc_sel_bit_t                       SEL7_b;
    stc_intc_sel_bit_t                       SEL8_b;
    stc_intc_sel_bit_t                       SEL9_b;
    stc_intc_sel_bit_t                       SEL10_b;
    stc_intc_sel_bit_t                       SEL11_b;
    stc_intc_sel_bit_t                       SEL12_b;
    stc_intc_sel_bit_t                       SEL13_b;
    stc_intc_sel_bit_t                       SEL14_b;
    stc_intc_sel_bit_t                       SEL15_b;
    stc_intc_sel_bit_t                       SEL16_b;
    stc_intc_sel_bit_t                       SEL17_b;
    stc_intc_sel_bit_t                       SEL18_b;
    stc_intc_sel_bit_t                       SEL19_b;
    stc_intc_sel_bit_t                       SEL20_b;
    stc_intc_sel_bit_t                       SEL21_b;
    stc_intc_sel_bit_t                       SEL22_b;
    stc_intc_sel_bit_t                       SEL23_b;
    stc_intc_sel_bit_t                       SEL24_b;
    stc_intc_sel_bit_t                       SEL25_b;
    stc_intc_sel_bit_t                       SEL26_b;
    stc_intc_sel_bit_t                       SEL27_b;
    stc_intc_sel_bit_t                       SEL28_b;
    stc_intc_sel_bit_t                       SEL29_b;
    stc_intc_sel_bit_t                       SEL30_b;
    stc_intc_sel_bit_t                       SEL31_b;
    stc_intc_sel_bit_t                       SEL32_b;
    stc_intc_sel_bit_t                       SEL33_b;
    stc_intc_sel_bit_t                       SEL34_b;
    stc_intc_sel_bit_t                       SEL35_b;
    stc_intc_sel_bit_t                       SEL36_b;
    stc_intc_sel_bit_t                       SEL37_b;
    stc_intc_sel_bit_t                       SEL38_b;
    stc_intc_sel_bit_t                       SEL39_b;
    stc_intc_sel_bit_t                       SEL40_b;
    stc_intc_sel_bit_t                       SEL41_b;
    stc_intc_sel_bit_t                       SEL42_b;
    stc_intc_sel_bit_t                       SEL43_b;
    stc_intc_sel_bit_t                       SEL44_b;
    stc_intc_sel_bit_t                       SEL45_b;
    stc_intc_sel_bit_t                       SEL46_b;
    stc_intc_sel_bit_t                       SEL47_b;
    stc_intc_sel_bit_t                       SEL48_b;
    stc_intc_sel_bit_t                       SEL49_b;
    stc_intc_sel_bit_t                       SEL50_b;
    stc_intc_sel_bit_t                       SEL51_b;
    stc_intc_sel_bit_t                       SEL52_b;
    stc_intc_sel_bit_t                       SEL53_b;
    stc_intc_sel_bit_t                       SEL54_b;
    stc_intc_sel_bit_t                       SEL55_b;
    stc_intc_sel_bit_t                       SEL56_b;
    stc_intc_sel_bit_t                       SEL57_b;
    stc_intc_sel_bit_t                       SEL58_b;
    stc_intc_sel_bit_t                       SEL59_b;
    stc_intc_sel_bit_t                       SEL60_b;
    stc_intc_sel_bit_t                       SEL61_b;
    stc_intc_sel_bit_t                       SEL62_b;
    stc_intc_sel_bit_t                       SEL63_b;
    stc_intc_sel_bit_t                       SEL64_b;
    stc_intc_sel_bit_t                       SEL65_b;
    stc_intc_sel_bit_t                       SEL66_b;
    stc_intc_sel_bit_t                       SEL67_b;
    stc_intc_sel_bit_t                       SEL68_b;
    stc_intc_sel_bit_t                       SEL69_b;
    stc_intc_sel_bit_t                       SEL70_b;
    stc_intc_sel_bit_t                       SEL71_b;
    stc_intc_sel_bit_t                       SEL72_b;
    stc_intc_sel_bit_t                       SEL73_b;
    stc_intc_sel_bit_t                       SEL74_b;
    stc_intc_sel_bit_t                       SEL75_b;
    stc_intc_sel_bit_t                       SEL76_b;
    stc_intc_sel_bit_t                       SEL77_b;
    stc_intc_sel_bit_t                       SEL78_b;
    stc_intc_sel_bit_t                       SEL79_b;
    stc_intc_sel_bit_t                       SEL80_b;
    stc_intc_sel_bit_t                       SEL81_b;
    stc_intc_sel_bit_t                       SEL82_b;
    stc_intc_sel_bit_t                       SEL83_b;
    stc_intc_sel_bit_t                       SEL84_b;
    stc_intc_sel_bit_t                       SEL85_b;
    stc_intc_sel_bit_t                       SEL86_b;
    stc_intc_sel_bit_t                       SEL87_b;
    stc_intc_sel_bit_t                       SEL88_b;
    stc_intc_sel_bit_t                       SEL89_b;
    stc_intc_sel_bit_t                       SEL90_b;
    stc_intc_sel_bit_t                       SEL91_b;
    stc_intc_sel_bit_t                       SEL92_b;
    stc_intc_sel_bit_t                       SEL93_b;
    stc_intc_sel_bit_t                       SEL94_b;
    stc_intc_sel_bit_t                       SEL95_b;
    stc_intc_sel_bit_t                       SEL96_b;
    stc_intc_sel_bit_t                       SEL97_b;
    stc_intc_sel_bit_t                       SEL98_b;
    stc_intc_sel_bit_t                       SEL99_b;
    stc_intc_sel_bit_t                       SEL100_b;
    stc_intc_sel_bit_t                       SEL101_b;
    stc_intc_sel_bit_t                       SEL102_b;
    stc_intc_sel_bit_t                       SEL103_b;
    stc_intc_sel_bit_t                       SEL104_b;
    stc_intc_sel_bit_t                       SEL105_b;
    stc_intc_sel_bit_t                       SEL106_b;
    stc_intc_sel_bit_t                       SEL107_b;
    stc_intc_sel_bit_t                       SEL108_b;
    stc_intc_sel_bit_t                       SEL109_b;
    stc_intc_sel_bit_t                       SEL110_b;
    stc_intc_sel_bit_t                       SEL111_b;
    stc_intc_sel_bit_t                       SEL112_b;
    stc_intc_sel_bit_t                       SEL113_b;
    stc_intc_sel_bit_t                       SEL114_b;
    stc_intc_sel_bit_t                       SEL115_b;
    stc_intc_sel_bit_t                       SEL116_b;
    stc_intc_sel_bit_t                       SEL117_b;
    stc_intc_sel_bit_t                       SEL118_b;
    stc_intc_sel_bit_t                       SEL119_b;
    stc_intc_sel_bit_t                       SEL120_b;
    stc_intc_sel_bit_t                       SEL121_b;
    stc_intc_sel_bit_t                       SEL122_b;
    stc_intc_sel_bit_t                       SEL123_b;
    stc_intc_sel_bit_t                       SEL124_b;
    stc_intc_sel_bit_t                       SEL125_b;
    stc_intc_sel_bit_t                       SEL126_b;
    stc_intc_sel_bit_t                       SEL127_b;
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
    stc_keyscan_scr_bit_t                    SCR_b;
    stc_keyscan_ser_bit_t                    SER_b;
    stc_keyscan_ssr_bit_t                    SSR_b;
} bCM_KEYSCAN_TypeDef;

typedef struct {
    stc_mpu_rgd_bit_t                        RGD0_b;
    stc_mpu_rgd_bit_t                        RGD1_b;
    stc_mpu_rgd_bit_t                        RGD2_b;
    stc_mpu_rgd_bit_t                        RGD3_b;
    stc_mpu_rgd_bit_t                        RGD4_b;
    stc_mpu_rgd_bit_t                        RGD5_b;
    stc_mpu_rgd_bit_t                        RGD6_b;
    stc_mpu_rgd_bit_t                        RGD7_b;
    stc_mpu_rgd_bit_t                        RGD8_b;
    stc_mpu_rgd_bit_t                        RGD9_b;
    stc_mpu_rgd_bit_t                        RGD10_b;
    stc_mpu_rgd_bit_t                        RGD11_b;
    stc_mpu_rgd_bit_t                        RGD12_b;
    stc_mpu_rgd_bit_t                        RGD13_b;
    stc_mpu_rgd_bit_t                        RGD14_b;
    stc_mpu_rgd_bit_t                        RGD15_b;
    stc_mpu_rgcr_bit_t                       RGCR0_b;
    stc_mpu_rgcr_bit_t                       RGCR1_b;
    stc_mpu_rgcr_bit_t                       RGCR2_b;
    stc_mpu_rgcr_bit_t                       RGCR3_b;
    stc_mpu_rgcr_bit_t                       RGCR4_b;
    stc_mpu_rgcr_bit_t                       RGCR5_b;
    stc_mpu_rgcr_bit_t                       RGCR6_b;
    stc_mpu_rgcr_bit_t                       RGCR7_b;
    stc_mpu_rgcr_bit_t                       RGCR8_b;
    stc_mpu_rgcr_bit_t                       RGCR9_b;
    stc_mpu_rgcr_bit_t                       RGCR10_b;
    stc_mpu_rgcr_bit_t                       RGCR11_b;
    stc_mpu_rgcr_bit_t                       RGCR12_b;
    stc_mpu_rgcr_bit_t                       RGCR13_b;
    stc_mpu_rgcr_bit_t                       RGCR14_b;
    stc_mpu_rgcr_bit_t                       RGCR15_b;
    stc_mpu_cr_bit_t                         CR_b;
    stc_mpu_sr_bit_t                         SR_b;
    stc_mpu_eclr_bit_t                       ECLR_b;
    stc_mpu_wp_bit_t                         WP_b;
    uint32_t                                 RESERVED0[130144];
    stc_mpu_ippr_bit_t                       IPPR_b;
} bCM_MPU_TypeDef;

typedef struct {
    stc_ots_ctl_bit_t                        CTL_b;
    uint32_t                                 RESERVED0[48];
    stc_ots_lpr_bit_t                        LPR_b;
} bCM_OTS_TypeDef;

typedef struct {
    stc_peric_usbfs_syctlreg_bit_t           USBFS_SYCTLREG_b;
    stc_peric_sdioc_syctlreg_bit_t           SDIOC_SYCTLREG_b;
} bCM_PERIC_TypeDef;

typedef struct {
    stc_qspi_cr_bit_t                        CR_b;
    stc_qspi_cscr_bit_t                      CSCR_b;
    stc_qspi_fcr_bit_t                       FCR_b;
    stc_qspi_sr_bit_t                        SR_b;
    stc_qspi_dcom_bit_t                      DCOM_b;
    stc_qspi_ccmd_bit_t                      CCMD_b;
    stc_qspi_xcmd_bit_t                      XCMD_b;
    uint32_t                                 RESERVED0[64];
    stc_qspi_sr2_bit_t                       SR2_b;
    uint32_t                                 RESERVED1[16096];
    stc_qspi_exar_bit_t                      EXAR_b;
} bCM_QSPI_TypeDef;

typedef struct {
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
    uint32_t                                 RESERVED3[88];
    stc_rtc_hour_bit_t                       HOUR_b;
    uint32_t                                 RESERVED4[184];
    stc_rtc_almhour_bit_t                    ALMHOUR_b;
    uint32_t                                 RESERVED5[24];
    stc_rtc_almweek_bit_t                    ALMWEEK_b;
    uint32_t                                 RESERVED6[24];
    stc_rtc_errcrh_bit_t                     ERRCRH_b;
} bCM_RTC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_sdioc_blksize_bit_t                  BLKSIZE_b;
    uint32_t                                 RESERVED1[48];
    stc_sdioc_transmode_bit_t                TRANSMODE_b;
    stc_sdioc_cmd_bit_t                      CMD_b;
    uint32_t                                 RESERVED2[160];
    stc_sdioc_pstat_bit_t                    PSTAT_b;
    stc_sdioc_hostcon_bit_t                  HOSTCON_b;
    stc_sdioc_pwrcon_bit_t                   PWRCON_b;
    stc_sdioc_blkgpcon_bit_t                 BLKGPCON_b;
    uint32_t                                 RESERVED3[8];
    stc_sdioc_clkcon_bit_t                   CLKCON_b;
    stc_sdioc_toutcon_bit_t                  TOUTCON_b;
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
    stc_sramc_wtcr_bit_t                     WTCR_b;
    stc_sramc_wtpr_bit_t                     WTPR_b;
    stc_sramc_ckcr_bit_t                     CKCR_b;
    stc_sramc_ckpr_bit_t                     CKPR_b;
    stc_sramc_cksr_bit_t                     CKSR_b;
} bCM_SRAMC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_swdt_sr_bit_t                        SR_b;
    stc_swdt_rr_bit_t                        RR_b;
} bCM_SWDT_TypeDef;

typedef struct {
    stc_tmr0_cntar_bit_t                     CNTAR_b;
    stc_tmr0_cntbr_bit_t                     CNTBR_b;
    stc_tmr0_cmpar_bit_t                     CMPAR_b;
    stc_tmr0_cmpbr_bit_t                     CMPBR_b;
    stc_tmr0_bconr_bit_t                     BCONR_b;
    stc_tmr0_stflr_bit_t                     STFLR_b;
} bCM_TMR0_TypeDef;

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
    stc_tmr4_cvpr_bit_t                      CVPR_b;
    uint32_t                                 RESERVED5[608];
    stc_tmr4_pocr_bit_t                      POCRU_b;
    uint32_t                                 RESERVED6[16];
    stc_tmr4_pocr_bit_t                      POCRV_b;
    uint32_t                                 RESERVED7[16];
    stc_tmr4_pocr_bit_t                      POCRW_b;
    uint32_t                                 RESERVED8[16];
    stc_tmr4_rcsr_bit_t                      RCSR_b;
    uint32_t                                 RESERVED9[272];
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
    uint32_t                                 RESERVED10[128];
    stc_tmr4_ecsr_bit_t                      ECSR_b;
} bCM_TMR4_TypeDef;

typedef struct {
    stc_tmr4cr_ecer1_bit_t                   ECER1_b;
    stc_tmr4cr_ecer2_bit_t                   ECER2_b;
    stc_tmr4cr_ecer3_bit_t                   ECER3_b;
} bCM_TMR4CR_TypeDef;

typedef struct {
    stc_tmr6_cnter_bit_t                     CNTER_b;
    stc_tmr6_perar_bit_t                     PERAR_b;
    stc_tmr6_perbr_bit_t                     PERBR_b;
    stc_tmr6_percr_bit_t                     PERCR_b;
    stc_tmr6_gcmar_bit_t                     GCMAR_b;
    stc_tmr6_gcmbr_bit_t                     GCMBR_b;
    stc_tmr6_gcmcr_bit_t                     GCMCR_b;
    stc_tmr6_gcmdr_bit_t                     GCMDR_b;
    stc_tmr6_gcmer_bit_t                     GCMER_b;
    stc_tmr6_gcmfr_bit_t                     GCMFR_b;
    stc_tmr6_scmar_bit_t                     SCMAR_b;
    stc_tmr6_scmbr_bit_t                     SCMBR_b;
    stc_tmr6_scmcr_bit_t                     SCMCR_b;
    stc_tmr6_scmdr_bit_t                     SCMDR_b;
    stc_tmr6_scmer_bit_t                     SCMER_b;
    stc_tmr6_scmfr_bit_t                     SCMFR_b;
    stc_tmr6_dtuar_bit_t                     DTUAR_b;
    stc_tmr6_dtdar_bit_t                     DTDAR_b;
    stc_tmr6_dtubr_bit_t                     DTUBR_b;
    stc_tmr6_dtdbr_bit_t                     DTDBR_b;
    stc_tmr6_gconr_bit_t                     GCONR_b;
    stc_tmr6_iconr_bit_t                     ICONR_b;
    stc_tmr6_pconr_bit_t                     PCONR_b;
    stc_tmr6_bconr_bit_t                     BCONR_b;
    stc_tmr6_dconr_bit_t                     DCONR_b;
    uint32_t                                 RESERVED0[32];
    stc_tmr6_fconr_bit_t                     FCONR_b;
    stc_tmr6_vperr_bit_t                     VPERR_b;
    stc_tmr6_stflr_bit_t                     STFLR_b;
    stc_tmr6_hstar_bit_t                     HSTAR_b;
    stc_tmr6_hstpr_bit_t                     HSTPR_b;
    stc_tmr6_hclrr_bit_t                     HCLRR_b;
    stc_tmr6_hcpar_bit_t                     HCPAR_b;
    stc_tmr6_hcpbr_bit_t                     HCPBR_b;
    stc_tmr6_hcupr_bit_t                     HCUPR_b;
    stc_tmr6_hcdor_bit_t                     HCDOR_b;
} bCM_TMR6_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[8096];
    stc_tmr6cr_sstar_bit_t                   SSTAR_b;
    stc_tmr6cr_sstpr_bit_t                   SSTPR_b;
    stc_tmr6cr_sclrr_bit_t                   SCLRR_b;
} bCM_TMR6CR_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[1024];
    stc_tmra_bcstr_bit_t                     BCSTR_b;
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
    uint32_t                                 RESERVED10[48];
    stc_tmra_bconr_bit_t                     BCONR3_b;
    uint32_t                                 RESERVED11[48];
    stc_tmra_bconr_bit_t                     BCONR4_b;
    uint32_t                                 RESERVED12[304];
    stc_tmra_cconr_bit_t                     CCONR1_b;
    uint32_t                                 RESERVED13[16];
    stc_tmra_cconr_bit_t                     CCONR2_b;
    uint32_t                                 RESERVED14[16];
    stc_tmra_cconr_bit_t                     CCONR3_b;
    uint32_t                                 RESERVED15[16];
    stc_tmra_cconr_bit_t                     CCONR4_b;
    uint32_t                                 RESERVED16[16];
    stc_tmra_cconr_bit_t                     CCONR5_b;
    uint32_t                                 RESERVED17[16];
    stc_tmra_cconr_bit_t                     CCONR6_b;
    uint32_t                                 RESERVED18[16];
    stc_tmra_cconr_bit_t                     CCONR7_b;
    uint32_t                                 RESERVED19[16];
    stc_tmra_cconr_bit_t                     CCONR8_b;
    uint32_t                                 RESERVED20[272];
    stc_tmra_pconr_bit_t                     PCONR1_b;
    uint32_t                                 RESERVED21[16];
    stc_tmra_pconr_bit_t                     PCONR2_b;
    uint32_t                                 RESERVED22[16];
    stc_tmra_pconr_bit_t                     PCONR3_b;
    uint32_t                                 RESERVED23[16];
    stc_tmra_pconr_bit_t                     PCONR4_b;
    uint32_t                                 RESERVED24[16];
    stc_tmra_pconr_bit_t                     PCONR5_b;
    uint32_t                                 RESERVED25[16];
    stc_tmra_pconr_bit_t                     PCONR6_b;
    uint32_t                                 RESERVED26[16];
    stc_tmra_pconr_bit_t                     PCONR7_b;
    uint32_t                                 RESERVED27[16];
    stc_tmra_pconr_bit_t                     PCONR8_b;
} bCM_TMRA_TypeDef;

typedef struct {
    stc_trng_cr_bit_t                        CR_b;
    stc_trng_mr_bit_t                        MR_b;
} bCM_TRNG_TypeDef;

typedef struct {
    stc_usart_sr_bit_t                       SR_b;
    stc_usart_dr_bit_t                       DR_b;
    uint32_t                                 RESERVED0[32];
    stc_usart_cr1_bit_t                      CR1_b;
    stc_usart_cr2_bit_t                      CR2_b;
    stc_usart_cr3_bit_t                      CR3_b;
    stc_usart_pr_bit_t                       PR_b;
} bCM_USART_TypeDef;

typedef struct {
    stc_usbfs_gvbuscfg_bit_t                 GVBUSCFG_b;
    uint32_t                                 RESERVED0[32];
    stc_usbfs_gahbcfg_bit_t                  GAHBCFG_b;
    stc_usbfs_gusbcfg_bit_t                  GUSBCFG_b;
    stc_usbfs_grstctl_bit_t                  GRSTCTL_b;
    stc_usbfs_gintsts_bit_t                  GINTSTS_b;
    stc_usbfs_gintmsk_bit_t                  GINTMSK_b;
    uint32_t                                 RESERVED1[7968];
    stc_usbfs_hcfg_bit_t                     HCFG_b;
    uint32_t                                 RESERVED2[480];
    stc_usbfs_hprt_bit_t                     HPRT_b;
    uint32_t                                 RESERVED3[1504];
    stc_usbfs_hcchar_bit_t                   HCCHAR0_b;
    uint32_t                                 RESERVED4[32];
    stc_usbfs_hcint_bit_t                    HCINT0_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK0_b;
    uint32_t                                 RESERVED5[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR1_b;
    uint32_t                                 RESERVED6[32];
    stc_usbfs_hcint_bit_t                    HCINT1_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK1_b;
    uint32_t                                 RESERVED7[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR2_b;
    uint32_t                                 RESERVED8[32];
    stc_usbfs_hcint_bit_t                    HCINT2_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK2_b;
    uint32_t                                 RESERVED9[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR3_b;
    uint32_t                                 RESERVED10[32];
    stc_usbfs_hcint_bit_t                    HCINT3_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK3_b;
    uint32_t                                 RESERVED11[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR4_b;
    uint32_t                                 RESERVED12[32];
    stc_usbfs_hcint_bit_t                    HCINT4_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK4_b;
    uint32_t                                 RESERVED13[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR5_b;
    uint32_t                                 RESERVED14[32];
    stc_usbfs_hcint_bit_t                    HCINT5_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK5_b;
    uint32_t                                 RESERVED15[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR6_b;
    uint32_t                                 RESERVED16[32];
    stc_usbfs_hcint_bit_t                    HCINT6_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK6_b;
    uint32_t                                 RESERVED17[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR7_b;
    uint32_t                                 RESERVED18[32];
    stc_usbfs_hcint_bit_t                    HCINT7_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK7_b;
    uint32_t                                 RESERVED19[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR8_b;
    uint32_t                                 RESERVED20[32];
    stc_usbfs_hcint_bit_t                    HCINT8_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK8_b;
    uint32_t                                 RESERVED21[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR9_b;
    uint32_t                                 RESERVED22[32];
    stc_usbfs_hcint_bit_t                    HCINT9_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK9_b;
    uint32_t                                 RESERVED23[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR10_b;
    uint32_t                                 RESERVED24[32];
    stc_usbfs_hcint_bit_t                    HCINT10_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK10_b;
    uint32_t                                 RESERVED25[128];
    stc_usbfs_hcchar_bit_t                   HCCHAR11_b;
    uint32_t                                 RESERVED26[32];
    stc_usbfs_hcint_bit_t                    HCINT11_b;
    stc_usbfs_hcintmsk_bit_t                 HCINTMSK11_b;
    uint32_t                                 RESERVED27[3200];
    stc_usbfs_dcfg_bit_t                     DCFG_b;
    stc_usbfs_dctl_bit_t                     DCTL_b;
    stc_usbfs_dsts_bit_t                     DSTS_b;
    uint32_t                                 RESERVED28[32];
    stc_usbfs_diepmsk_bit_t                  DIEPMSK_b;
    stc_usbfs_doepmsk_bit_t                  DOEPMSK_b;
    uint32_t                                 RESERVED29[1856];
    stc_usbfs_diepctl0_bit_t                 DIEPCTL0_b;
    uint32_t                                 RESERVED30[32];
    stc_usbfs_diepint_bit_t                  DIEPINT0_b;
    uint32_t                                 RESERVED31[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL1_b;
    uint32_t                                 RESERVED32[32];
    stc_usbfs_diepint_bit_t                  DIEPINT1_b;
    uint32_t                                 RESERVED33[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL2_b;
    uint32_t                                 RESERVED34[32];
    stc_usbfs_diepint_bit_t                  DIEPINT2_b;
    uint32_t                                 RESERVED35[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL3_b;
    uint32_t                                 RESERVED36[32];
    stc_usbfs_diepint_bit_t                  DIEPINT3_b;
    uint32_t                                 RESERVED37[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL4_b;
    uint32_t                                 RESERVED38[32];
    stc_usbfs_diepint_bit_t                  DIEPINT4_b;
    uint32_t                                 RESERVED39[160];
    stc_usbfs_diepctl_bit_t                  DIEPCTL5_b;
    uint32_t                                 RESERVED40[32];
    stc_usbfs_diepint_bit_t                  DIEPINT5_b;
    uint32_t                                 RESERVED41[2720];
    stc_usbfs_doepctl0_bit_t                 DOEPCTL0_b;
    uint32_t                                 RESERVED42[32];
    stc_usbfs_doepint_bit_t                  DOEPINT0_b;
    uint32_t                                 RESERVED43[32];
    stc_usbfs_doeptsiz0_bit_t                DOEPTSIZ0_b;
    uint32_t                                 RESERVED44[96];
    stc_usbfs_doepctl_bit_t                  DOEPCTL1_b;
    uint32_t                                 RESERVED45[32];
    stc_usbfs_doepint_bit_t                  DOEPINT1_b;
    uint32_t                                 RESERVED46[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL2_b;
    uint32_t                                 RESERVED47[32];
    stc_usbfs_doepint_bit_t                  DOEPINT2_b;
    uint32_t                                 RESERVED48[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL3_b;
    uint32_t                                 RESERVED49[32];
    stc_usbfs_doepint_bit_t                  DOEPINT3_b;
    uint32_t                                 RESERVED50[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL4_b;
    uint32_t                                 RESERVED51[32];
    stc_usbfs_doepint_bit_t                  DOEPINT4_b;
    uint32_t                                 RESERVED52[160];
    stc_usbfs_doepctl_bit_t                  DOEPCTL5_b;
    uint32_t                                 RESERVED53[32];
    stc_usbfs_doepint_bit_t                  DOEPINT5_b;
    uint32_t                                 RESERVED54[4768];
    stc_usbfs_gcctl_bit_t                    GCCTL_b;
} bCM_USBFS_TypeDef;

typedef struct {
    stc_wdt_cr_bit_t                         CR_b;
    stc_wdt_sr_bit_t                         SR_b;
    stc_wdt_rr_bit_t                         RR_b;
} bCM_WDT_TypeDef;


/******************************************************************************/
/*      Device Specific Peripheral bit_band declaration & memory map          */
/******************************************************************************/
#define bCM_ADC1                             ((bCM_ADC_TypeDef *)0x42800000UL)
#define bCM_ADC2                             ((bCM_ADC_TypeDef *)0x42808000UL)
#define bCM_AES                              ((bCM_AES_TypeDef *)0x42100000UL)
#define bCM_AOS                              ((bCM_AOS_TypeDef *)0x42210000UL)
#define bCM_CAN                              ((bCM_CAN_TypeDef *)0x42E08000UL)
#define bCM_CMP1                             ((bCM_CMP_TypeDef *)0x42940000UL)
#define bCM_CMP2                             ((bCM_CMP_TypeDef *)0x42940200UL)
#define bCM_CMP3                             ((bCM_CMP_TypeDef *)0x42940400UL)
#define bCM_CMPCR                            ((bCM_CMPCR_TypeDef *)0x42940000UL)
#define bCM_CMU                              ((bCM_CMU_TypeDef *)0x42A80000UL)
#define bCM_CRC                              ((bCM_CRC_TypeDef *)0x42118000UL)
#define bCM_DCU1                             ((bCM_DCU_TypeDef *)0x42A40000UL)
#define bCM_DCU2                             ((bCM_DCU_TypeDef *)0x42A48000UL)
#define bCM_DCU3                             ((bCM_DCU_TypeDef *)0x42A50000UL)
#define bCM_DCU4                             ((bCM_DCU_TypeDef *)0x42A58000UL)
#define bCM_DMA1                             ((bCM_DMA_TypeDef *)0x42A60000UL)
#define bCM_DMA2                             ((bCM_DMA_TypeDef *)0x42A68000UL)
#define bCM_EFM                              ((bCM_EFM_TypeDef *)0x42208000UL)
#define bCM_EMB0                             ((bCM_EMB_TypeDef *)0x422F8000UL)
#define bCM_EMB1                             ((bCM_EMB_TypeDef *)0x422F8400UL)
#define bCM_EMB2                             ((bCM_EMB_TypeDef *)0x422F8800UL)
#define bCM_EMB3                             ((bCM_EMB_TypeDef *)0x422F8C00UL)
#define bCM_FCM                              ((bCM_FCM_TypeDef *)0x42908000UL)
#define bCM_GPIO                             ((bCM_GPIO_TypeDef *)0x42A70000UL)
#define bCM_HASH                             ((bCM_HASH_TypeDef *)0x42108000UL)
#define bCM_I2C1                             ((bCM_I2C_TypeDef *)0x429C0000UL)
#define bCM_I2C2                             ((bCM_I2C_TypeDef *)0x429C8000UL)
#define bCM_I2C3                             ((bCM_I2C_TypeDef *)0x429D0000UL)
#define bCM_I2S1                             ((bCM_I2S_TypeDef *)0x423C0000UL)
#define bCM_I2S2                             ((bCM_I2S_TypeDef *)0x423C8000UL)
#define bCM_I2S3                             ((bCM_I2S_TypeDef *)0x42440000UL)
#define bCM_I2S4                             ((bCM_I2S_TypeDef *)0x42448000UL)
#define bCM_INTC                             ((bCM_INTC_TypeDef *)0x42A20000UL)
#define bCM_KEYSCAN                          ((bCM_KEYSCAN_TypeDef *)0x42A18000UL)
#define bCM_MPU                              ((bCM_MPU_TypeDef *)0x42A00000UL)
#define bCM_OTS                              ((bCM_OTS_TypeDef *)0x42948000UL)
#define bCM_PERIC                            ((bCM_PERIC_TypeDef *)0x42AA8000UL)
#define bCM_PWC                              ((bCM_PWC_TypeDef *)0x42900000UL)
#define bCM_RMU                              ((bCM_RMU_TypeDef *)0x42A81800UL)
#define bCM_RTC                              ((bCM_RTC_TypeDef *)0x42980000UL)
#define bCM_SDIOC1                           ((bCM_SDIOC_TypeDef *)0x42DF8000UL)
#define bCM_SDIOC2                           ((bCM_SDIOC_TypeDef *)0x42E00000UL)
#define bCM_SPI1                             ((bCM_SPI_TypeDef *)0x42380000UL)
#define bCM_SPI2                             ((bCM_SPI_TypeDef *)0x42388000UL)
#define bCM_SPI3                             ((bCM_SPI_TypeDef *)0x42400000UL)
#define bCM_SPI4                             ((bCM_SPI_TypeDef *)0x42408000UL)
#define bCM_SRAMC                            ((bCM_SRAMC_TypeDef *)0x42A10000UL)
#define bCM_SWDT                             ((bCM_SWDT_TypeDef *)0x42928000UL)
#define bCM_TMR0_1                           ((bCM_TMR0_TypeDef *)0x42480000UL)
#define bCM_TMR0_2                           ((bCM_TMR0_TypeDef *)0x42488000UL)
#define bCM_TMR4_1                           ((bCM_TMR4_TypeDef *)0x422E0000UL)
#define bCM_TMR4_2                           ((bCM_TMR4_TypeDef *)0x42490000UL)
#define bCM_TMR4_3                           ((bCM_TMR4_TypeDef *)0x42498000UL)
#define bCM_TMR4CR                           ((bCM_TMR4CR_TypeDef *)0x42AA8100UL)
#define bCM_TMR6_1                           ((bCM_TMR6_TypeDef *)0x42300000UL)
#define bCM_TMR6_2                           ((bCM_TMR6_TypeDef *)0x42308000UL)
#define bCM_TMR6_3                           ((bCM_TMR6_TypeDef *)0x42310000UL)
#define bCM_TMR6CR                           ((bCM_TMR6CR_TypeDef *)0x42300000UL)
#define bCM_TMRA_1                           ((bCM_TMRA_TypeDef *)0x422A0000UL)
#define bCM_TMRA_2                           ((bCM_TMRA_TypeDef *)0x422A8000UL)
#define bCM_TMRA_3                           ((bCM_TMRA_TypeDef *)0x422B0000UL)
#define bCM_TMRA_4                           ((bCM_TMRA_TypeDef *)0x422B8000UL)
#define bCM_TMRA_5                           ((bCM_TMRA_TypeDef *)0x422C0000UL)
#define bCM_TMRA_6                           ((bCM_TMRA_TypeDef *)0x422C8000UL)
#define bCM_TRNG                             ((bCM_TRNG_TypeDef *)0x42820000UL)
#define bCM_USART1                           ((bCM_USART_TypeDef *)0x423A0000UL)
#define bCM_USART2                           ((bCM_USART_TypeDef *)0x423A8000UL)
#define bCM_USART3                           ((bCM_USART_TypeDef *)0x42420000UL)
#define bCM_USART4                           ((bCM_USART_TypeDef *)0x42428000UL)
#define bCM_USBFS                            ((bCM_USBFS_TypeDef *)0x43800000UL)
#define bCM_WDT                              ((bCM_WDT_TypeDef *)0x42920000UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32F460_H__ */
