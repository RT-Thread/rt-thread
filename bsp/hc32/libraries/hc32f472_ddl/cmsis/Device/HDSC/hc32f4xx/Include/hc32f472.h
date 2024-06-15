/**
 *******************************************************************************
 * @file  HC32F472.h
 * @brief Headerfile for HC32F472 series MCU
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-12-15       CDT             Modify based on RM Rev1.0
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

#ifndef __HC32F472_H__
#define __HC32F472_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 ******************************************************************************/
#define __MPU_PRESENT             1       /*!< HC32F472 provides MPU                                */
#define __VTOR_PRESENT            1       /*!< HC32F472 supported vector table registers            */
#define __NVIC_PRIO_BITS          4       /*!< HC32F472 uses 4 Bits for the Priority Levels         */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used         */
#define __FPU_PRESENT             1       /*!< FPU present                                          */

/*******************************************************************************
 * Interrupt Number Definition
 ******************************************************************************/
typedef enum {
    NMI_IRQn                    = -14, /*  2 Non Maskable                     */
    HardFault_IRQn              = -13, /*  3 Hard Fault                       */
    MemManageFault_IRQn         = -12, /*  4 MemManage Fault                  */
    BusFault_IRQn               = -11, /*  5 Bus Fault                        */
    UsageFault_IRQn             = -10, /*  6 Usage Fault                      */
    SVC_IRQn                    = -5,  /* 11 SVCall                           */
    DebugMonitor_IRQn           = -4,  /* 12 DebugMonitor                     */
    PendSV_IRQn                 = -2,  /* 14 Pend SV                          */
    SysTick_IRQn                = -1,  /* 15 System Tick                      */
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
    EXTINT_PORT_EIRQ0_IRQn      = 16,
    EXTINT_PORT_EIRQ1_IRQn      = 17,
    EXTINT_PORT_EIRQ2_IRQn      = 18,
    EXTINT_PORT_EIRQ3_IRQn      = 19,
    EXTINT_PORT_EIRQ4_IRQn      = 20,
    EXTINT_PORT_EIRQ5_IRQn      = 21,
    EXTINT_PORT_EIRQ6_IRQn      = 22,
    EXTINT_PORT_EIRQ7_IRQn      = 23,
    EXTINT_PORT_EIRQ8_IRQn      = 24,
    EXTINT_PORT_EIRQ9_IRQn      = 25,
    EXTINT_PORT_EIRQ10_IRQn     = 26,
    EXTINT_PORT_EIRQ11_IRQn     = 27,
    EXTINT_PORT_EIRQ12_IRQn     = 28,
    EXTINT_PORT_EIRQ13_IRQn     = 29,
    EXTINT_PORT_EIRQ14_IRQn     = 30,
    EXTINT_PORT_EIRQ15_IRQn     = 31,
    SWINT0_IRQn                 = 0,
    SWINT1_IRQn                 = 1,
    SWINT2_IRQn                 = 2,
    SWINT3_IRQn                 = 3,
    SWINT4_IRQn                 = 4,
    SWINT5_IRQn                 = 5,
    SWINT6_IRQn                 = 6,
    SWINT7_IRQn                 = 7,
    SWINT8_IRQn                 = 8,
    SWINT9_IRQn                 = 9,
    SWINT10_IRQn                = 10,
    SWINT11_IRQn                = 11,
    SWINT12_IRQn                = 12,
    SWINT13_IRQn                = 13,
    SWINT14_IRQn                = 14,
    SWINT15_IRQn                = 15,
    SWINT16_IRQn                = 16,
    SWINT17_IRQn                = 17,
    SWINT18_IRQn                = 18,
    SWINT19_IRQn                = 19,
    SWINT20_IRQn                = 20,
    SWINT21_IRQn                = 21,
    SWINT22_IRQn                = 22,
    SWINT23_IRQn                = 23,
    SWINT24_IRQn                = 24,
    SWINT25_IRQn                = 25,
    SWINT26_IRQn                = 26,
    SWINT27_IRQn                = 27,
    SWINT28_IRQn                = 28,
    SWINT29_IRQn                = 29,
    SWINT30_IRQn                = 30,
    SWINT31_IRQn                = 31,
    DMA1_ERR_IRQn               = 32,
    DMA1_TC0_BTC0_IRQn          = 33,
    DMA1_TC1_BTC1_IRQn          = 34,
    DMA1_TC2_BTC2_IRQn          = 35,
    DMA1_TC3_BTC3_IRQn          = 36,
    DMA1_TC4_BTC4_IRQn          = 37,
    DMA1_TC5_BTC5_IRQn          = 38,
    DMA1_TC6_BTC6_IRQn          = 39,
    DMA1_TC7_BTC7_IRQn          = 40,
    EFM_PEERR_RDCOL_IRQn        = 41,
    EFM_OPTEND_IRQn             = 42,
    QSPI_IRQn                   = 43,
    DCU1_IRQn                   = 44,
    DCU2_IRQn                   = 45,
    DCU3_IRQn                   = 46,
    DMA2_ERR_IRQn               = 47,
    DMA2_TC0_BTC0_IRQn          = 48,
    DMA2_TC1_BTC1_IRQn          = 49,
    DMA2_TC2_BTC2_IRQn          = 50,
    DMA2_TC3_BTC3_IRQn          = 51,
    DMA2_TC4_BTC4_IRQn          = 52,
    DMA2_TC5_BTC5_IRQn          = 53,
    DMA2_TC6_BTC6_IRQn          = 54,
    DMA2_TC7_BTC7_IRQn          = 55,
    MAU_IRQn                    = 56,
    FMAC1_FIR_IRQn              = 57,
    FMAC2_FIR_IRQn              = 58,
    FMAC3_FIR_IRQn              = 59,
    FMAC4_FIR_IRQn              = 60,
    TMR0_1_CMP_IRQn             = 61,
    TMR0_2_CMP_IRQn             = 62,
    TMR2_1_CMP_IRQn             = 63,
    TMR2_1_OVF_IRQn             = 64,
    TMR2_2_CMP_IRQn             = 65,
    TMR2_2_OVF_IRQn             = 66,
    TMR2_3_CMP_IRQn             = 67,
    TMR2_3_OVF_IRQn             = 68,
    TMR2_4_CMP_IRQn             = 69,
    TMR2_4_OVF_IRQn             = 70,
    RTC_IRQn                    = 71,
    XTAL_IRQn                   = 72,
    WKTM_IRQn                   = 73,
    SWDT_IRQn                   = 74,
    TMR6_1_GCMP_IRQn            = 75,
    TMR6_1_OVF_UDF_IRQn         = 76,
    TMR6_1_DTE_IRQn             = 77,
    TMR6_1_SCMP_IRQn            = 78,
    TMRA_1_OVF_UDF_IRQn         = 79,
    TMRA_1_CMP_IRQn             = 80,
    TMR6_2_GCMP_IRQn            = 81,
    TMR6_2_OVF_UDF_IRQn         = 82,
    TMR6_2_DTE_IRQn             = 83,
    TMR6_2_SCMP_IRQn            = 84,
    TMRA_2_OVF_UDF_IRQn         = 85,
    TMRA_2_CMP_IRQn             = 86,
    TMR6_3_GCMP_IRQn            = 87,
    TMR6_3_OVF_UDF_IRQn         = 88,
    TMR6_3_DTE_IRQn             = 89,
    TMR6_3_SCMP_IRQn            = 90,
    TMRA_3_OVF_UDF_IRQn         = 91,
    TMRA_3_CMP_IRQn             = 92,
    TMR6_4_GCMP_IRQn            = 93,
    TMR6_4_OVF_UDF_IRQn         = 94,
    TMR6_4_DTE_IRQn             = 95,
    TMR6_4_SCMP_IRQn            = 96,
    TMRA_4_OVF_UDF_IRQn         = 97,
    TMRA_4_CMP_IRQn             = 98,
    TMR6_5_GCMP_IRQn            = 99,
    TMR6_5_OVF_UDF_IRQn         = 100,
    TMR6_5_DTE_IRQn             = 101,
    TMR6_5_SCMP_IRQn            = 102,
    TMR6_6_GCMP_IRQn            = 104,
    TMR6_6_OVF_UDF_IRQn         = 105,
    TMR6_6_DTE_IRQn             = 106,
    TMR6_6_SCMP_IRQn            = 107,
    TMR6_7_GCMP_IRQn            = 108,
    TMR6_7_OVF_UDF_IRQn         = 109,
    TMR6_7_DTE_IRQn             = 110,
    TMR6_7_SCMP_IRQn            = 111,
    TMR6_8_GCMP_IRQn            = 112,
    TMR6_8_OVF_UDF_IRQn         = 113,
    TMR6_8_DTE_IRQn             = 114,
    TMR6_8_SCMP_IRQn            = 115,
    TMR6_9_GCMP_IRQn            = 116,
    TMR6_9_OVF_UDF_IRQn         = 117,
    TMR6_9_DTE_IRQn             = 118,
    TMR6_9_SCMP_IRQn            = 119,
    TMR6_10_GCMP_IRQn           = 120,
    TMR6_10_OVF_UDF_IRQn        = 121,
    TMR6_10_DTE_IRQn            = 122,
    TMR6_10_SCMP_IRQn           = 123,
    TMR4_1_GCMP_IRQn            = 124,
    TMR4_1_OVF_UDF_IRQn         = 125,
    TMR4_1_RELOAD_IRQn          = 126,
    TMR4_1_SCMP_IRQn            = 127,
    CMP1_IRQ_IRQn               = 128,
    CMP2_IRQ_IRQn               = 129,
    CMP3_IRQ_IRQn               = 130,
    CMP4_IRQ_IRQn               = 131,
    CAN1_INT_IRQn               = 132,
    CAN2_INT_IRQn               = 133,
    CAN3_INT_IRQn               = 134,
    USART1_IRQn                 = 135,
    USART2_IRQn                 = 136,
    SPI1_IRQn                   = 137,
    SPI2_IRQn                   = 138,
    TMRA_5_OVF_UDF_IRQn         = 139,
    TMRA_5_CMP_IRQn             = 140,
    TMRA_6_OVF_UDF_IRQn         = 141,
    TMRA_6_CMP_IRQn             = 142,
    USBFS_GLB_IRQn              = 143,
    EVENT_PORT1_IRQn            = 144,
    EVENT_PORT2_IRQn            = 145,
    EVENT_PORT3_IRQn            = 146,
    EVENT_PORT4_IRQn            = 147,
    USART3_IRQn                 = 148,
    USART4_IRQn                 = 149,
    SPI3_IRQn                   = 150,
    SPI4_IRQn                   = 151,
    EMB_GR0_IRQn                = 152,
    EMB_GR1_IRQn                = 153,
    EMB_GR2_IRQn                = 154,
    EMB_GR3_IRQn                = 155,
    EMB_GR4_IRQn                = 156,
    EMB_GR5_IRQn                = 157,
    EMB_GR6_IRQn                = 158,
    HASH_IRQn                   = 159,
    USART5_IRQn                 = 160,
    USART6_IRQn                 = 161,
    MDIO_IRQn                   = 162,
    PLA_IRQn                    = 163,
    I2C1_IRQn                   = 164,
    I2C2_IRQn                   = 165,
    I2C3_IRQn                   = 166,
    USART1_WUPI_IRQn            = 167,
    LVD1_IRQn                   = 168,
    LVD2_IRQn                   = 169,
    OTS_IRQn                    = 170,
    FCM_IRQn                    = 171,
    WDT_IRQn                    = 172,
    CTC_IRQn                    = 173,
    ADC1_IRQn                   = 174,
    ADC2_IRQn                   = 175,
    ADC3_IRQn                   = 176,
    TRNG_IRQn                   = 177,
    USART1_TCI_IRQn             = 178,
    USART2_TCI_IRQn             = 179,
    USART3_TCI_IRQn             = 180,
    USART4_TCI_IRQn             = 181,
    USART5_TCI_IRQn             = 182,
    USART6_TCI_IRQn             = 183,
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
    /*  External Interrupt   */
    EVT_SRC_PORT_EIRQ0           = 0U,      /* EIRQ0  */
    EVT_SRC_PORT_EIRQ1           = 1U,      /* EIRQ1  */
    EVT_SRC_PORT_EIRQ2           = 2U,      /* EIRQ2  */
    EVT_SRC_PORT_EIRQ3           = 3U,      /* EIRQ3  */
    EVT_SRC_PORT_EIRQ4           = 4U,      /* EIRQ4  */
    EVT_SRC_PORT_EIRQ5           = 5U,      /* EIRQ5  */
    EVT_SRC_PORT_EIRQ6           = 6U,      /* EIRQ6  */
    EVT_SRC_PORT_EIRQ7           = 7U,      /* EIRQ7  */
    EVT_SRC_PORT_EIRQ8           = 8U,      /* EIRQ8  */
    EVT_SRC_PORT_EIRQ9           = 9U,      /* EIRQ9  */
    EVT_SRC_PORT_EIRQ10          = 10U,     /* EIRQ10 */
    EVT_SRC_PORT_EIRQ11          = 11U,     /* EIRQ11 */
    EVT_SRC_PORT_EIRQ12          = 12U,     /* EIRQ12 */
    EVT_SRC_PORT_EIRQ13          = 13U,     /* EIRQ13 */
    EVT_SRC_PORT_EIRQ14          = 14U,     /* EIRQ14 */
    EVT_SRC_PORT_EIRQ15          = 15U,     /* EIRQ15 */
    /*  DMA_1  */
    EVT_SRC_DMA1_TC0             = 33U,     /* DMA_1_TC0  */
    EVT_SRC_DMA1_BTC0            = 34U,     /* DMA_1_BTC0 */
    EVT_SRC_DMA1_TC1             = 35U,     /* DMA_1_TC1  */
    EVT_SRC_DMA1_BTC1            = 36U,     /* DMA_1_BTC1 */
    EVT_SRC_DMA1_TC2             = 37U,     /* DMA_1_TC2  */
    EVT_SRC_DMA1_BTC2            = 38U,     /* DMA_1_BTC2 */
    EVT_SRC_DMA1_TC3             = 39U,     /* DMA_1_TC3  */
    EVT_SRC_DMA1_BTC3            = 40U,     /* DMA_1_BTC3 */
    EVT_SRC_DMA1_TC4             = 41U,     /* DMA_1_TC4  */
    EVT_SRC_DMA1_BTC4            = 42U,     /* DMA_1_BTC4 */
    EVT_SRC_DMA1_TC5             = 43U,     /* DMA_1_TC5  */
    EVT_SRC_DMA1_BTC5            = 44U,     /* DMA_1_BTC5 */
    EVT_SRC_DMA1_TC6             = 45U,     /* DMA_1_TC6  */
    EVT_SRC_DMA1_BTC6            = 46U,     /* DMA_1_BTC6 */
    EVT_SRC_DMA1_TC7             = 47U,     /* DMA_1_TC7  */
    EVT_SRC_DMA1_BTC7            = 48U,     /* DMA_1_BTC7 */
    /*  EFM  */
    EVT_SRC_EFM_OPTEND           = 51U,     /* EFM_OPTEND */
    /*  USBFS  */
    EVT_SRC_USBFS_SOF            = 52U,     /* USBFS_SOF */
    /*  DCU  */
    EVT_SRC_DCU1                 = 55U,     /* DCU1 */
    EVT_SRC_DCU2                 = 56U,     /* DCU2 */
    EVT_SRC_DCU3                 = 57U,     /* DCU3 */
    /*  DMA2  */
    EVT_SRC_DMA2_TC0             = 65U,     /* DMA_2_TC0  */
    EVT_SRC_DMA2_BTC0            = 66U,     /* DMA_2_BTC0 */
    EVT_SRC_DMA2_TC1             = 67U,     /* DMA_2_TC1  */
    EVT_SRC_DMA2_BTC1            = 68U,     /* DMA_2_BTC1 */
    EVT_SRC_DMA2_TC2             = 69U,     /* DMA_2_TC2  */
    EVT_SRC_DMA2_BTC2            = 70U,     /* DMA_2_BTC2 */
    EVT_SRC_DMA2_TC3             = 71U,     /* DMA_2_TC3  */
    EVT_SRC_DMA2_BTC3            = 72U,     /* DMA_2_BTC3 */
    EVT_SRC_DMA2_TC4             = 73U,     /* DMA_2_TC4  */
    EVT_SRC_DMA2_BTC4            = 74U,     /* DMA_2_BTC4 */
    EVT_SRC_DMA2_TC5             = 75U,     /* DMA_2_TC5  */
    EVT_SRC_DMA2_BTC5            = 76U,     /* DMA_2_BTC5 */
    EVT_SRC_DMA2_TC6             = 77U,     /* DMA_2_TC6  */
    EVT_SRC_DMA2_BTC6            = 78U,     /* DMA_2_BTC6 */
    EVT_SRC_DMA2_TC7             = 79U,     /* DMA_2_TC7  */
    EVT_SRC_DMA2_BTC7            = 80U,     /* DMA_2_BTC7 */
    /*  MAU  */
    EVT_SRC_MAU_SQRT             = 83U,     /* MAU_SQRT */
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
    EVT_SRC_RTC_ALM              = 121U,     /* RTC_ALM */
    EVT_SRC_RTC_PRD              = 122U,     /* RTC_PRD */
    /*  TIMER6_1  */
    EVT_SRC_TMR6_1_GCMP_A        = 128U,     /* TMR6_1_GCMA */
    EVT_SRC_TMR6_1_GCMP_B        = 129U,     /* TMR6_1_GCMB */
    EVT_SRC_TMR6_1_GCMP_C        = 130U,     /* TMR6_1_GCMC */
    EVT_SRC_TMR6_1_GCMP_D        = 131U,     /* TMR6_1_GCMD */
    EVT_SRC_TMR6_1_GCMP_E        = 132U,     /* TMR6_1_GCME */
    EVT_SRC_TMR6_1_GCMP_F        = 133U,     /* TMR6_1_GCMF */
    EVT_SRC_TMR6_1_OVF           = 134U,     /* TMR6_1_GOVF */
    EVT_SRC_TMR6_1_UDF           = 135U,     /* TMR6_1_GUDF */
    EVT_SRC_TMR6_1_SCMP_A        = 137U,     /* TMR6_1_SCMA */
    EVT_SRC_TMR6_1_SCMP_B        = 138U,     /* TMR6_1_SCMB */
    /*  TIMERA_1  */
    EVT_SRC_TMRA_1_OVF           = 139U,     /* TMRA_1_OVF */
    EVT_SRC_TMRA_1_UDF           = 140U,     /* TMRA_1_UDF */
    EVT_SRC_TMRA_1_CMP           = 141U,     /* TMRA_1_CMP */
    /*  TIMER6_2  */
    EVT_SRC_TMR6_2_GCMP_A        = 144U,     /* TMR6_2_GCMA */
    EVT_SRC_TMR6_2_GCMP_B        = 145U,     /* TMR6_2_GCMB */
    EVT_SRC_TMR6_2_GCMP_C        = 146U,     /* TMR6_2_GCMC */
    EVT_SRC_TMR6_2_GCMP_D        = 147U,     /* TMR6_2_GCMD */
    EVT_SRC_TMR6_2_GCMP_E        = 148U,     /* TMR6_2_GCME */
    EVT_SRC_TMR6_2_GCMP_F        = 149U,     /* TMR6_2_GCMF */
    EVT_SRC_TMR6_2_OVF           = 150U,     /* TMR6_2_GOVF */
    EVT_SRC_TMR6_2_UDF           = 151U,     /* TMR6_2_GUDF */
    EVT_SRC_TMR6_2_SCMP_A        = 153U,     /* TMR6_2_SCMA */
    EVT_SRC_TMR6_2_SCMP_B        = 154U,     /* TMR6_2_SCMB */
    /*  TIMERA_2  */
    EVT_SRC_TMRA_2_OVF           = 155U,     /* TMRA_2_OVF */
    EVT_SRC_TMRA_2_UDF           = 156U,     /* TMRA_2_UDF */
    EVT_SRC_TMRA_2_CMP           = 157U,     /* TMRA_2_CMP */
    /*  TIMER6_3  */
    EVT_SRC_TMR6_3_GCMP_A        = 160U,     /* TMR6_3_GCMA */
    EVT_SRC_TMR6_3_GCMP_B        = 161U,     /* TMR6_3_GCMB */
    EVT_SRC_TMR6_3_GCMP_C        = 162U,     /* TMR6_3_GCMC */
    EVT_SRC_TMR6_3_GCMP_D        = 163U,     /* TMR6_3_GCMD */
    EVT_SRC_TMR6_3_GCMP_E        = 164U,     /* TMR6_3_GCME */
    EVT_SRC_TMR6_3_GCMP_F        = 165U,     /* TMR6_3_GCMF */
    EVT_SRC_TMR6_3_OVF           = 166U,     /* TMR6_3_GOVF */
    EVT_SRC_TMR6_3_UDF           = 167U,     /* TMR6_3_GUDF */
    EVT_SRC_TMR6_3_SCMP_A        = 169U,     /* TMR6_3_SCMA */
    EVT_SRC_TMR6_3_SCMP_B        = 170U,     /* TMR6_3_SCMB */
    /*  TIMERA_3  */
    EVT_SRC_TMRA_3_OVF           = 171U,     /* TMRA_3_OVF */
    EVT_SRC_TMRA_3_UDF           = 172U,     /* TMRA_3_UDF */
    EVT_SRC_TMRA_3_CMP           = 173U,     /* TMRA_3_CMP */
    /*  TIMER6_4 */
    EVT_SRC_TMR6_4_GCMP_A        = 176U,     /* TMR6_4_GCMA */
    EVT_SRC_TMR6_4_GCMP_B        = 177U,     /* TMR6_4_GCMB */
    EVT_SRC_TMR6_4_GCMP_C        = 178U,     /* TMR6_4_GCMC */
    EVT_SRC_TMR6_4_GCMP_D        = 179U,     /* TMR6_4_GCMD */
    EVT_SRC_TMR6_4_GCMP_E        = 180U,     /* TMR6_4_GCME */
    EVT_SRC_TMR6_4_GCMP_F        = 181U,     /* TMR6_4_GCMF */
    EVT_SRC_TMR6_4_OVF           = 182U,     /* TMR6_4_GOVF */
    EVT_SRC_TMR6_4_UDF           = 183U,     /* TMR6_4_GUDF */
    EVT_SRC_TMR6_4_SCMP_A        = 185U,     /* TMR6_4_SCMA */
    EVT_SRC_TMR6_4_SCMP_B        = 186U,     /* TMR6_4_SCMB */
    /*  TIMERA_4  */
    EVT_SRC_TMRA_4_OVF           = 187U,     /* TMRA_4_OVF */
    EVT_SRC_TMRA_4_UDF           = 188U,     /* TMRA_4_UDF */
    EVT_SRC_TMRA_4_CMP           = 189U,     /* TMRA_4_CMP */
    /*  TIMER6_5  */
    EVT_SRC_TMR6_5_GCMP_A        = 192U,     /* TMR6_5_GCMA */
    EVT_SRC_TMR6_5_GCMP_B        = 193U,     /* TMR6_5_GCMB */
    EVT_SRC_TMR6_5_GCMP_C        = 194U,     /* TMR6_5_GCMC */
    EVT_SRC_TMR6_5_GCMP_D        = 195U,     /* TMR6_5_GCMD */
    EVT_SRC_TMR6_5_GCMP_E        = 196U,     /* TMR6_5_GCME */
    EVT_SRC_TMR6_5_GCMP_F        = 197U,     /* TMR6_5_GCMF */
    EVT_SRC_TMR6_5_OVF           = 198U,     /* TMR6_5_GOVF */
    EVT_SRC_TMR6_5_UDF           = 199U,     /* TMR6_5_GUDF */
    EVT_SRC_TMR6_5_SCMP_A        = 201U,     /* TMR6_5_SCMA */
    EVT_SRC_TMR6_5_SCMP_B        = 202U,     /* TMR6_5_SCMB */
    /*  TIMER6_6  */
    EVT_SRC_TMR6_6_GCMP_A        = 208U,     /* TMR6_6_GCMA */
    EVT_SRC_TMR6_6_GCMP_B        = 209U,     /* TMR6_6_GCMB */
    EVT_SRC_TMR6_6_GCMP_C        = 210U,     /* TMR6_6_GCMC */
    EVT_SRC_TMR6_6_GCMP_D        = 211U,     /* TMR6_6_GCMD */
    EVT_SRC_TMR6_6_GCMP_E        = 212U,     /* TMR6_6_GCME */
    EVT_SRC_TMR6_6_GCMP_F        = 213U,     /* TMR6_6_GCMF */
    EVT_SRC_TMR6_6_OVF           = 214U,     /* TMR6_6_GOVF */
    EVT_SRC_TMR6_6_UDF           = 215U,     /* TMR6_6_GUDF */
    EVT_SRC_TMR6_6_SCMP_A        = 217U,     /* TMR6_6_SCMA */
    EVT_SRC_TMR6_6_SCMP_B        = 218U,     /* TMR6_6_SCMB */
    /*  TIMER6_7  */
    EVT_SRC_TMR6_7_GCMP_A        = 224U,     /* TMR6_7_GCMA */
    EVT_SRC_TMR6_7_GCMP_B        = 225U,     /* TMR6_7_GCMB */
    EVT_SRC_TMR6_7_GCMP_C        = 226U,     /* TMR6_7_GCMC */
    EVT_SRC_TMR6_7_GCMP_D        = 227U,     /* TMR6_7_GCMD */
    EVT_SRC_TMR6_7_GCMP_E        = 228U,     /* TMR6_7_GCME */
    EVT_SRC_TMR6_7_GCMP_F        = 229U,     /* TMR6_7_GCMF */
    EVT_SRC_TMR6_7_OVF           = 230U,     /* TMR6_7_GOVF */
    EVT_SRC_TMR6_7_UDF           = 231U,     /* TMR6_7_GUDF */
    EVT_SRC_TMR6_7_SCMP_A        = 233U,     /* TMR6_7_SCMA */
    EVT_SRC_TMR6_7_SCMP_B        = 234U,     /* TMR6_7_SCMB */
    /*  TIMER6_8  */
    EVT_SRC_TMR6_8_GCMP_A        = 240U,     /* TMR6_8_GCMA */
    EVT_SRC_TMR6_8_GCMP_B        = 241U,     /* TMR6_8_GCMB */
    EVT_SRC_TMR6_8_GCMP_C        = 242U,     /* TMR6_8_GCMC */
    EVT_SRC_TMR6_8_GCMP_D        = 243U,     /* TMR6_8_GCMD */
    EVT_SRC_TMR6_8_GCMP_E        = 244U,     /* TMR6_8_GCME */
    EVT_SRC_TMR6_8_GCMP_F        = 245U,     /* TMR6_8_GCMF */
    EVT_SRC_TMR6_8_OVF           = 246U,     /* TMR6_8_GOVF */
    EVT_SRC_TMR6_8_UDF           = 247U,     /* TMR6_8_GUDF */
    EVT_SRC_TMR6_8_SCMP_A        = 249U,     /* TMR6_8_SCMA */
    EVT_SRC_TMR6_8_SCMP_B        = 250U,     /* TMR6_8_SCMB */
    /*  TIMER6_9  */
    EVT_SRC_TMR6_9_GCMP_A        = 256U,     /* TMR6_9_GCMA */
    EVT_SRC_TMR6_9_GCMP_B        = 257U,     /* TMR6_9_GCMB */
    EVT_SRC_TMR6_9_GCMP_C        = 258U,     /* TMR6_9_GCMC */
    EVT_SRC_TMR6_9_GCMP_D        = 259U,     /* TMR6_9_GCMD */
    EVT_SRC_TMR6_9_GCMP_E        = 260U,     /* TMR6_9_GCME */
    EVT_SRC_TMR6_9_GCMP_F        = 261U,     /* TMR6_9_GCMF */
    EVT_SRC_TMR6_9_OVF           = 262U,     /* TMR6_9_GOVF */
    EVT_SRC_TMR6_9_UDF           = 263U,     /* TMR6_9_GUDF */
    EVT_SRC_TMR6_9_SCMP_A        = 265U,     /* TMR6_9_SCMA */
    EVT_SRC_TMR6_9_SCMP_B        = 266U,     /* TMR6_9_SCMB */
    /*  TIMER6_10  */
    EVT_SRC_TMR6_10_GCMP_A       = 272U,     /* TMR6_10_GCMA */
    EVT_SRC_TMR6_10_GCMP_B       = 273U,     /* TMR6_10_GCMB */
    EVT_SRC_TMR6_10_GCMP_C       = 274U,     /* TMR6_10_GCMC */
    EVT_SRC_TMR6_10_GCMP_D       = 275U,     /* TMR6_10_GCMD */
    EVT_SRC_TMR6_10_GCMP_E       = 276U,     /* TMR6_10_GCME */
    EVT_SRC_TMR6_10_GCMP_F       = 277U,     /* TMR6_10_GCMF */
    EVT_SRC_TMR6_10_OVF          = 278U,     /* TMR6_10_GOVF */
    EVT_SRC_TMR6_10_UDF          = 279U,     /* TMR6_10_GUDF */
    EVT_SRC_TMR6_10_SCMP_A       = 281U,     /* TMR6_10_SCMA */
    EVT_SRC_TMR6_10_SCMP_B       = 282U,     /* TMR6_10_SCMB */
    /*  TIMER4_1  */
    EVT_SRC_TMR4_1_GCMP_UH       = 288U,     /* TMR4_1_GCMUH */
    EVT_SRC_TMR4_1_GCMP_UL       = 289U,     /* TMR4_1_GCMUL */
    EVT_SRC_TMR4_1_GCMP_VH       = 290U,     /* TMR4_1_GCMVH */
    EVT_SRC_TMR4_1_GCMP_VL       = 291U,     /* TMR4_1_GCMVL */
    EVT_SRC_TMR4_1_GCMP_WH       = 292U,     /* TMR4_1_GCMWH */
    EVT_SRC_TMR4_1_GCMP_WL       = 293U,     /* TMR4_1_GCMWL */
    EVT_SRC_TMR4_1_OVF           = 294U,     /* TMR4_1_GOVF  */
    EVT_SRC_TMR4_1_UDF           = 295U,     /* TMR4_1_GUDF  */
    EVT_SRC_TMR4_1_SCMP0         = 299U,     /* TMR4_1_SCM0 */
    EVT_SRC_TMR4_1_SCMP1         = 300U,     /* TMR4_1_SCM1 */
    EVT_SRC_TMR4_1_SCMP2         = 301U,     /* TMR4_1_SCM2 */
    EVT_SRC_TMR4_1_SCMP3         = 302U,     /* TMR4_1_SCM3 */
    EVT_SRC_TMR4_1_SCMP4         = 303U,     /* TMR4_1_SCM4 */
    EVT_SRC_TMR4_1_SCMP5         = 304U,     /* TMR4_1_SCM5 */
    /*  CMP  */
    EVT_SRC_CMP1                 = 305U,     /* CMP_1_IRQ */
    EVT_SRC_CMP2                 = 306U,     /* CMP_2_IRQ */
    EVT_SRC_CMP3                 = 307U,     /* CMP_3_IRQ */
    EVT_SRC_CMP4                 = 308U,     /* CMP_4_IRQ */
    /*  USART1  */
    EVT_SRC_USART1_EI            = 320U,     /* USART_1_EI  */
    EVT_SRC_USART1_RI            = 321U,     /* USART_1_RI  */
    EVT_SRC_USART1_TI            = 322U,     /* USART_1_TI  */
    EVT_SRC_USART1_TCI           = 323U,     /* USART_1_TCI */
    EVT_SRC_USART1_RTO           = 324U,     /* USART_1_RTO */
    /*  USART2  */
    EVT_SRC_USART2_EI            = 325U,     /* USART_2_EI  */
    EVT_SRC_USART2_RI            = 326U,     /* USART_2_RI  */
    EVT_SRC_USART2_TI            = 327U,     /* USART_2_TI  */
    EVT_SRC_USART2_TCI           = 328U,     /* USART_2_TCI */
    EVT_SRC_USART2_RTO           = 329U,     /* USART_2_RTO */
    /*  SPI1  */
    EVT_SRC_SPI1_SPRI            = 330U,     /* SPI_1_SPRI */
    EVT_SRC_SPI1_SPTI            = 331U,     /* SPI_1_SPTI */
    EVT_SRC_SPI1_SPII            = 332U,     /* SPI_1_SPII */
    EVT_SRC_SPI1_SPEI            = 333U,     /* SPI_1_SPEI */
    EVT_SRC_SPI1_SPEND           = 334U,     /* SPI_1_SPEND */
    /*  SPI2  */
    EVT_SRC_SPI2_SPRI            = 335U,     /* SPI_2_SPRI */
    EVT_SRC_SPI2_SPTI            = 336U,     /* SPI_2_SPTI */
    EVT_SRC_SPI2_SPII            = 337U,     /* SPI_2_SPII */
    EVT_SRC_SPI2_SPEI            = 338U,     /* SPI_2_SPEI */
    EVT_SRC_SPI2_SPEND           = 339U,     /* SPI_2_SPEND */
    /*  TIMERA_5  */
    EVT_SRC_TMRA_5_OVF           = 340U,     /* TMRA_5_OVF */
    EVT_SRC_TMRA_5_UDF           = 341U,     /* TMRA_5_UDF */
    EVT_SRC_TMRA_5_CMP           = 342U,     /* TMRA_5_CMP */
    /*  TIMERA_6  */
    EVT_SRC_TMRA_6_OVF           = 343U,     /* TMRA_6_OVF */
    EVT_SRC_TMRA_6_UDF           = 344U,     /* TMRA_6_UDF */
    EVT_SRC_TMRA_6_CMP           = 345U,     /* TMRA_6_CMP */
    /*  EVENT PORT  */
    EVT_SRC_EVENT_PORT1          = 348U,     /* EVENT_PORT1 */
    EVT_SRC_EVENT_PORT2          = 349U,     /* EVENT_PORT2 */
    EVT_SRC_EVENT_PORT3          = 350U,     /* EVENT_PORT3 */
    EVT_SRC_EVENT_PORT4          = 351U,     /* EVENT_PORT4 */
    /*  USART3  */
    EVT_SRC_USART3_BRKWKPI       = 352U,     /* USART_3_BRKWKPI */
    EVT_SRC_USART3_EI            = 353U,     /* USART_3_EI      */
    EVT_SRC_USART3_RI            = 354U,     /* USART_3_RI      */
    EVT_SRC_USART3_TI            = 355U,     /* USART_3_TI      */
    EVT_SRC_USART3_TCI           = 356U,     /* USART_3_TCI     */
    /*  USART4  */
    EVT_SRC_USART4_EI            = 357U,     /* USART_4_EI  */
    EVT_SRC_USART4_RI            = 358U,     /* USART_4_RI  */
    EVT_SRC_USART4_TI            = 359U,     /* USART_4_TI  */
    EVT_SRC_USART4_TCI           = 360U,     /* USART_4_TCI */
    EVT_SRC_USART4_RTO           = 361U,     /* USART_4_RTO */
    /*  SPI3  */
    EVT_SRC_SPI3_SPRI            = 362U,     /* SPI_3_SPRI */
    EVT_SRC_SPI3_SPTI            = 363U,     /* SPI_3_SPTI */
    EVT_SRC_SPI3_SPII            = 364U,     /* SPI_3_SPII */
    EVT_SRC_SPI3_SPEI            = 365U,     /* SPI_3_SPEI */
    EVT_SRC_SPI3_SPEND           = 366U,     /* SPI_3_SPEND */
    /*  SPI4  */
    EVT_SRC_SPI4_SPRI            = 367U,     /* SPI_4_SPRI */
    EVT_SRC_SPI4_SPTI            = 368U,     /* SPI_4_SPTI */
    EVT_SRC_SPI4_SPII            = 369U,     /* SPI_4_SPII */
    EVT_SRC_SPI4_SPEI            = 370U,     /* SPI_4_SPEI */
    EVT_SRC_SPI4_SPEND           = 371U,     /* SPI_4_SPEND */
    /*  HASH  */
    EVT_SRC_HASH                 = 379U,     /* HASH_INT */
    /*  USART5  */
    EVT_SRC_USART5_EI            = 384U,     /* USART_5_EI  */
    EVT_SRC_USART5_RI            = 385U,     /* USART_5_RI  */
    EVT_SRC_USART5_TI            = 386U,     /* USART_5_TI  */
    EVT_SRC_USART5_TCI           = 387U,     /* USART_5_TCI */
    EVT_SRC_USART5_RTO           = 388U,     /* USART_5_RTO */
    /*  USART6  */
    EVT_SRC_USART6_BRKWKPI       = 389U,     /* USART_6_BRKWKPI */
    EVT_SRC_USART6_EI            = 390U,     /* USART_6_EI      */
    EVT_SRC_USART6_RI            = 391U,     /* USART_6_RI      */
    EVT_SRC_USART6_TI            = 392U,     /* USART_6_TI      */
    EVT_SRC_USART6_TCI           = 393U,     /* USART_6_TCI     */
    /*  MDIO  */
    EVT_SRC_MDIO_AOS             = 413U,     /* MDIO_AOS */
    /*  AOS  */
    EVT_SRC_AOS_STRG             = 415U,     /* AOS_STRG */
    /*  PLA  */
    EVT_SRC_PLA_ADTRG0           = 432U,     /* PLA_ADTRG0  */
    EVT_SRC_PLA_ADTRG1           = 433U,     /* PLA_ADTRG1  */
    EVT_SRC_PLA_ADTRG2           = 434U,     /* PLA_ADTRG2  */
    EVT_SRC_PLA_ADTRG3           = 435U,     /* PLA_ADTRG3  */
    EVT_SRC_PLA_ADTRG4           = 436U,     /* PLA_ADTRG4  */
    EVT_SRC_PLA_ADTRG5           = 437U,     /* PLA_ADTRG5  */
    EVT_SRC_PLA_ADTRG6           = 438U,     /* PLA_ADTRG6  */
    EVT_SRC_PLA_ADTRG7           = 439U,     /* PLA_ADTRG7  */
    EVT_SRC_PLA_ADTRG8           = 440U,     /* PLA_ADTRG8  */
    EVT_SRC_PLA_ADTRG9           = 441U,     /* PLA_ADTRG9  */
    EVT_SRC_PLA_ADTRG10          = 442U,     /* PLA_ADTRG10 */
    EVT_SRC_PLA_ADTRG11          = 443U,     /* PLA_ADTRG11 */
    EVT_SRC_PLA_ADTRG12          = 444U,     /* PLA_ADTRG12 */
    EVT_SRC_PLA_ADTRG13          = 445U,     /* PLA_ADTRG13 */
    EVT_SRC_PLA_ADTRG14          = 446U,     /* PLA_ADTRG14 */
    EVT_SRC_PLA_ADTRG15          = 447U,     /* PLA_ADTRG15 */
    /*  I2C1  */
    EVT_SRC_I2C1_RXI             = 448U,     /* I2C_1_RXI */
    EVT_SRC_I2C1_TXI             = 449U,     /* I2C_1_TXI */
    EVT_SRC_I2C1_TEI             = 450U,     /* I2C_1_TEI */
    EVT_SRC_I2C1_EEI             = 451U,     /* I2C_1_EEI */
    /*  I2C2  */
    EVT_SRC_I2C2_RXI             = 452U,     /* I2C_2_RXI */
    EVT_SRC_I2C2_TXI             = 453U,     /* I2C_2_TXI */
    EVT_SRC_I2C2_TEI             = 454U,     /* I2C_2_TEI */
    EVT_SRC_I2C2_EEI             = 455U,     /* I2C_2_EEI */
    /*  I2C3  */
    EVT_SRC_I2C3_RXI             = 456U,     /* I2C_3_RXI */
    EVT_SRC_I2C3_TXI             = 457U,     /* I2C_3_TXI */
    EVT_SRC_I2C3_TEI             = 458U,     /* I2C_3_TEI */
    EVT_SRC_I2C3_EEI             = 459U,     /* I2C_3_EEI */
    /*  LVD  */
    EVT_SRC_LVD1                = 465U,     /* LVD1 */
    EVT_SRC_LVD2                = 466U,     /* LVD2 */
    /*  OTS  */
    EVT_SRC_OTS                  = 467U,     /* OTS */
    /*  WDT  */
    EVT_SRC_WDT_REFUDF           = 471U,     /* WDT_REFUDF */
    /*  ADC1  */
    EVT_SRC_ADC1_EOCA            = 480U,     /* ADC_1_EOCA */
    EVT_SRC_ADC1_EOCB            = 481U,     /* ADC_1_EOCB */
    EVT_SRC_ADC1_CMP0            = 482U,     /* ADC_1_CMP0 */
    EVT_SRC_ADC1_CMP1            = 483U,     /* ADC_1_CMP1 */
    /*  ADC2  */
    EVT_SRC_ADC2_EOCA            = 484U,     /* ADC_2_EOCA */
    EVT_SRC_ADC2_EOCB            = 485U,     /* ADC_2_EOCB */
    EVT_SRC_ADC2_CMP0            = 486U,     /* ADC_2_CMP0 */
    EVT_SRC_ADC2_CMP1            = 487U,     /* ADC_2_CMP1 */
    /*  ADC3  */
    EVT_SRC_ADC3_EOCA            = 488U,     /* ADC_3_EOCA */
    EVT_SRC_ADC3_EOCB            = 489U,     /* ADC_3_EOCB */
    EVT_SRC_ADC3_CMP0            = 490U,     /* ADC_3_CMP0 */
    EVT_SRC_ADC3_CMP1            = 491U,     /* ADC_3_CMP1 */
    /*  TRNG  */
    EVT_SRC_TRNG_END             = 492U,     /* TRNG_END */
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
    INT_SRC_PORT_EIRQ0           = 0U,      /* EIRQ0  */
    INT_SRC_PORT_EIRQ1           = 1U,      /* EIRQ1  */
    INT_SRC_PORT_EIRQ2           = 2U,      /* EIRQ2  */
    INT_SRC_PORT_EIRQ3           = 3U,      /* EIRQ3  */
    INT_SRC_PORT_EIRQ4           = 4U,      /* EIRQ4  */
    INT_SRC_PORT_EIRQ5           = 5U,      /* EIRQ5  */
    INT_SRC_PORT_EIRQ6           = 6U,      /* EIRQ6  */
    INT_SRC_PORT_EIRQ7           = 7U,      /* EIRQ7  */
    INT_SRC_PORT_EIRQ8           = 8U,      /* EIRQ8  */
    INT_SRC_PORT_EIRQ9           = 9U,      /* EIRQ9  */
    INT_SRC_PORT_EIRQ10          = 10U,     /* EIRQ10 */
    INT_SRC_PORT_EIRQ11          = 11U,     /* EIRQ11 */
    INT_SRC_PORT_EIRQ12          = 12U,     /* EIRQ12 */
    INT_SRC_PORT_EIRQ13          = 13U,     /* EIRQ13 */
    INT_SRC_PORT_EIRQ14          = 14U,     /* EIRQ14 */
    INT_SRC_PORT_EIRQ15          = 15U,     /* EIRQ15 */
    /*  DMA_1  */
    INT_SRC_DMA1_ERR             = 32U,     /* DMA_1_ERR  */
    INT_SRC_DMA1_TC0             = 33U,     /* DMA_1_TC0  */
    INT_SRC_DMA1_BTC0            = 34U,     /* DMA_1_BTC0 */
    INT_SRC_DMA1_TC1             = 35U,     /* DMA_1_TC1  */
    INT_SRC_DMA1_BTC1            = 36U,     /* DMA_1_BTC1 */
    INT_SRC_DMA1_TC2             = 37U,     /* DMA_1_TC2  */
    INT_SRC_DMA1_BTC2            = 38U,     /* DMA_1_BTC2 */
    INT_SRC_DMA1_TC3             = 39U,     /* DMA_1_TC3  */
    INT_SRC_DMA1_BTC3            = 40U,     /* DMA_1_BTC3 */
    INT_SRC_DMA1_TC4             = 41U,     /* DMA_1_TC4  */
    INT_SRC_DMA1_BTC4            = 42U,     /* DMA_1_BTC4 */
    INT_SRC_DMA1_TC5             = 43U,     /* DMA_1_TC5  */
    INT_SRC_DMA1_BTC5            = 44U,     /* DMA_1_BTC5 */
    INT_SRC_DMA1_TC6             = 45U,     /* DMA_1_TC6  */
    INT_SRC_DMA1_BTC6            = 46U,     /* DMA_1_BTC6 */
    INT_SRC_DMA1_TC7             = 47U,     /* DMA_1_TC7  */
    INT_SRC_DMA1_BTC7            = 48U,     /* DMA_1_BTC7 */
    /*  EFM  */
    INT_SRC_EFM_PEERR            = 49U,     /* EFM_PEERR  */
    INT_SRC_EFM_RDCOL            = 50U,     /* EFM_RDCOL  */
    INT_SRC_EFM_OPTEND           = 51U,     /* EFM_OPTEND */
    /*  QSPI  */
    INT_SRC_QSPI_INTR            = 54U,     /* QSPI_INTR */
    /*  DCU  */
    INT_SRC_DCU1                 = 55U,     /* DCU1 */
    INT_SRC_DCU2                 = 56U,     /* DCU2 */
    INT_SRC_DCU3                 = 57U,     /* DCU3 */
    /*  DMA2  */
    INT_SRC_DMA2_ERR             = 64U,     /* DMA_2_ERR  */
    INT_SRC_DMA2_TC0             = 65U,     /* DMA_2_TC0  */
    INT_SRC_DMA2_BTC0            = 66U,     /* DMA_2_BTC0 */
    INT_SRC_DMA2_TC1             = 67U,     /* DMA_2_TC1  */
    INT_SRC_DMA2_BTC1            = 68U,     /* DMA_2_BTC1 */
    INT_SRC_DMA2_TC2             = 69U,     /* DMA_2_TC2  */
    INT_SRC_DMA2_BTC2            = 70U,     /* DMA_2_BTC2 */
    INT_SRC_DMA2_TC3             = 71U,     /* DMA_2_TC3  */
    INT_SRC_DMA2_BTC3            = 72U,     /* DMA_2_BTC3 */
    INT_SRC_DMA2_TC4             = 73U,     /* DMA_2_TC4  */
    INT_SRC_DMA2_BTC4            = 74U,     /* DMA_2_BTC4 */
    INT_SRC_DMA2_TC5             = 75U,     /* DMA_2_TC5  */
    INT_SRC_DMA2_BTC5            = 76U,     /* DMA_2_BTC5 */
    INT_SRC_DMA2_TC6             = 77U,     /* DMA_2_TC6  */
    INT_SRC_DMA2_BTC6            = 78U,     /* DMA_2_BTC6 */
    INT_SRC_DMA2_TC7             = 79U,     /* DMA_2_TC7  */
    INT_SRC_DMA2_BTC7            = 80U,     /* DMA_2_BTC7 */
    /*  MAU  */
    INT_SRC_MAU_SQRT             = 83U,     /* MAU_SQRT */
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
    INT_SRC_TMR6_1_DTE           = 136U,     /* TMR6_1_GDTE */
    INT_SRC_TMR6_1_SCMP_A        = 137U,     /* TMR6_1_SCMA */
    INT_SRC_TMR6_1_SCMP_B        = 138U,     /* TMR6_1_SCMB */
    /*  TIMERA_1  */
    INT_SRC_TMRA_1_OVF           = 139U,     /* TMRA_1_OVF */
    INT_SRC_TMRA_1_UDF           = 140U,     /* TMRA_1_UDF */
    INT_SRC_TMRA_1_CMP           = 141U,     /* TMRA_1_CMP */
    /*  TIMER6_2  */
    INT_SRC_TMR6_2_GCMP_A        = 144U,     /* TMR6_2_GCMA */
    INT_SRC_TMR6_2_GCMP_B        = 145U,     /* TMR6_2_GCMB */
    INT_SRC_TMR6_2_GCMP_C        = 146U,     /* TMR6_2_GCMC */
    INT_SRC_TMR6_2_GCMP_D        = 147U,     /* TMR6_2_GCMD */
    INT_SRC_TMR6_2_GCMP_E        = 148U,     /* TMR6_2_GCME */
    INT_SRC_TMR6_2_GCMP_F        = 149U,     /* TMR6_2_GCMF */
    INT_SRC_TMR6_2_OVF           = 150U,     /* TMR6_2_GOVF */
    INT_SRC_TMR6_2_UDF           = 151U,     /* TMR6_2_GUDF */
    INT_SRC_TMR6_2_DTE           = 152U,     /* TMR6_2_GDTE */
    INT_SRC_TMR6_2_SCMP_A        = 153U,     /* TMR6_2_SCMA */
    INT_SRC_TMR6_2_SCMP_B        = 154U,     /* TMR6_2_SCMB */
    /*  TIMERA_2  */
    INT_SRC_TMRA_2_OVF           = 155U,     /* TMRA_2_OVF */
    INT_SRC_TMRA_2_UDF           = 156U,     /* TMRA_2_UDF */
    INT_SRC_TMRA_2_CMP           = 157U,     /* TMRA_2_CMP */
    /*  TIMER6_3  */
    INT_SRC_TMR6_3_GCMP_A        = 160U,     /* TMR6_3_GCMA */
    INT_SRC_TMR6_3_GCMP_B        = 161U,     /* TMR6_3_GCMB */
    INT_SRC_TMR6_3_GCMP_C        = 162U,     /* TMR6_3_GCMC */
    INT_SRC_TMR6_3_GCMP_D        = 163U,     /* TMR6_3_GCMD */
    INT_SRC_TMR6_3_GCMP_E        = 164U,     /* TMR6_3_GCME */
    INT_SRC_TMR6_3_GCMP_F        = 165U,     /* TMR6_3_GCMF */
    INT_SRC_TMR6_3_OVF           = 166U,     /* TMR6_3_GOVF */
    INT_SRC_TMR6_3_UDF           = 167U,     /* TMR6_3_GUDF */
    INT_SRC_TMR6_3_DTE           = 168U,     /* TMR6_3_GDTE */
    INT_SRC_TMR6_3_SCMP_A        = 169U,     /* TMR6_3_SCMA */
    INT_SRC_TMR6_3_SCMP_B        = 170U,     /* TMR6_3_SCMB */
    /*  TIMERA_3  */
    INT_SRC_TMRA_3_OVF           = 171U,     /* TMRA_3_OVF */
    INT_SRC_TMRA_3_UDF           = 172U,     /* TMRA_3_UDF */
    INT_SRC_TMRA_3_CMP           = 173U,     /* TMRA_3_CMP */
    /*  TIMER6_4 */
    INT_SRC_TMR6_4_GCMP_A        = 176U,     /* TMR6_4_GCMA */
    INT_SRC_TMR6_4_GCMP_B        = 177U,     /* TMR6_4_GCMB */
    INT_SRC_TMR6_4_GCMP_C        = 178U,     /* TMR6_4_GCMC */
    INT_SRC_TMR6_4_GCMP_D        = 179U,     /* TMR6_4_GCMD */
    INT_SRC_TMR6_4_GCMP_E        = 180U,     /* TMR6_4_GCME */
    INT_SRC_TMR6_4_GCMP_F        = 181U,     /* TMR6_4_GCMF */
    INT_SRC_TMR6_4_OVF           = 182U,     /* TMR6_4_GOVF */
    INT_SRC_TMR6_4_UDF           = 183U,     /* TMR6_4_GUDF */
    INT_SRC_TMR6_4_DTE           = 184U,     /* TMR6_4_GDTE */
    INT_SRC_TMR6_4_SCMP_A        = 185U,     /* TMR6_4_SCMA */
    INT_SRC_TMR6_4_SCMP_B        = 186U,     /* TMR6_4_SCMB */
    /*  TIMERA_4  */
    INT_SRC_TMRA_4_OVF           = 187U,     /* TMRA_4_OVF */
    INT_SRC_TMRA_4_UDF           = 188U,     /* TMRA_4_UDF */
    INT_SRC_TMRA_4_CMP           = 189U,     /* TMRA_4_CMP */
    /*  TIMER6_5  */
    INT_SRC_TMR6_5_GCMP_A        = 192U,     /* TMR6_5_GCMA */
    INT_SRC_TMR6_5_GCMP_B        = 193U,     /* TMR6_5_GCMB */
    INT_SRC_TMR6_5_GCMP_C        = 194U,     /* TMR6_5_GCMC */
    INT_SRC_TMR6_5_GCMP_D        = 195U,     /* TMR6_5_GCMD */
    INT_SRC_TMR6_5_GCMP_E        = 196U,     /* TMR6_5_GCME */
    INT_SRC_TMR6_5_GCMP_F        = 197U,     /* TMR6_5_GCMF */
    INT_SRC_TMR6_5_OVF           = 198U,     /* TMR6_5_GOVF */
    INT_SRC_TMR6_5_UDF           = 199U,     /* TMR6_5_GUDF */
    INT_SRC_TMR6_5_DTE           = 200U,     /* TMR6_5_GDTE */
    INT_SRC_TMR6_5_SCMP_A        = 201U,     /* TMR6_5_SCMA */
    INT_SRC_TMR6_5_SCMP_B        = 202U,     /* TMR6_5_SCMB */
    /*  TIMER6_6  */
    INT_SRC_TMR6_6_GCMP_A        = 208U,     /* TMR6_6_GCMA */
    INT_SRC_TMR6_6_GCMP_B        = 209U,     /* TMR6_6_GCMB */
    INT_SRC_TMR6_6_GCMP_C        = 210U,     /* TMR6_6_GCMC */
    INT_SRC_TMR6_6_GCMP_D        = 211U,     /* TMR6_6_GCMD */
    INT_SRC_TMR6_6_GCMP_E        = 212U,     /* TMR6_6_GCME */
    INT_SRC_TMR6_6_GCMP_F        = 213U,     /* TMR6_6_GCMF */
    INT_SRC_TMR6_6_OVF           = 214U,     /* TMR6_6_GOVF */
    INT_SRC_TMR6_6_UDF           = 215U,     /* TMR6_6_GUDF */
    INT_SRC_TMR6_6_DTE           = 216U,     /* TMR6_6_GDTE */
    INT_SRC_TMR6_6_SCMP_A        = 217U,     /* TMR6_6_SCMA */
    INT_SRC_TMR6_6_SCMP_B        = 218U,     /* TMR6_6_SCMB */
    /*  TIMER6_7  */
    INT_SRC_TMR6_7_GCMP_A        = 224U,     /* TMR6_7_GCMA */
    INT_SRC_TMR6_7_GCMP_B        = 225U,     /* TMR6_7_GCMB */
    INT_SRC_TMR6_7_GCMP_C        = 226U,     /* TMR6_7_GCMC */
    INT_SRC_TMR6_7_GCMP_D        = 227U,     /* TMR6_7_GCMD */
    INT_SRC_TMR6_7_GCMP_E        = 228U,     /* TMR6_7_GCME */
    INT_SRC_TMR6_7_GCMP_F        = 229U,     /* TMR6_7_GCMF */
    INT_SRC_TMR6_7_OVF           = 230U,     /* TMR6_7_GOVF */
    INT_SRC_TMR6_7_UDF           = 231U,     /* TMR6_7_GUDF */
    INT_SRC_TMR6_7_DTE           = 232U,     /* TMR6_7_GDTE */
    INT_SRC_TMR6_7_SCMP_A        = 233U,     /* TMR6_7_SCMA */
    INT_SRC_TMR6_7_SCMP_B        = 234U,     /* TMR6_7_SCMB */
    /*  TIMER6_8  */
    INT_SRC_TMR6_8_GCMP_A        = 240U,     /* TMR6_8_GCMA */
    INT_SRC_TMR6_8_GCMP_B        = 241U,     /* TMR6_8_GCMB */
    INT_SRC_TMR6_8_GCMP_C        = 242U,     /* TMR6_8_GCMC */
    INT_SRC_TMR6_8_GCMP_D        = 243U,     /* TMR6_8_GCMD */
    INT_SRC_TMR6_8_GCMP_E        = 244U,     /* TMR6_8_GCME */
    INT_SRC_TMR6_8_GCMP_F        = 245U,     /* TMR6_8_GCMF */
    INT_SRC_TMR6_8_OVF           = 246U,     /* TMR6_8_GOVF */
    INT_SRC_TMR6_8_UDF           = 247U,     /* TMR6_8_GUDF */
    INT_SRC_TMR6_8_DTE           = 248U,     /* TMR6_8_GDTE */
    INT_SRC_TMR6_8_SCMP_A        = 249U,     /* TMR6_8_SCMA */
    INT_SRC_TMR6_8_SCMP_B        = 250U,     /* TMR6_8_SCMB */
    /*  TIMER6_9  */
    INT_SRC_TMR6_9_GCMP_A        = 256U,     /* TMR6_9_GCMA */
    INT_SRC_TMR6_9_GCMP_B        = 257U,     /* TMR6_9_GCMB */
    INT_SRC_TMR6_9_GCMP_C        = 258U,     /* TMR6_9_GCMC */
    INT_SRC_TMR6_9_GCMP_D        = 259U,     /* TMR6_9_GCMD */
    INT_SRC_TMR6_9_GCMP_E        = 260U,     /* TMR6_9_GCME */
    INT_SRC_TMR6_9_GCMP_F        = 261U,     /* TMR6_9_GCMF */
    INT_SRC_TMR6_9_OVF           = 262U,     /* TMR6_9_GOVF */
    INT_SRC_TMR6_9_UDF           = 263U,     /* TMR6_9_GUDF */
    INT_SRC_TMR6_9_DTE           = 264U,     /* TMR6_9_GDTE */
    INT_SRC_TMR6_9_SCMP_A        = 265U,     /* TMR6_9_SCMA */
    INT_SRC_TMR6_9_SCMP_B        = 266U,     /* TMR6_9_SCMB */
    /*  TIMER6_10  */
    INT_SRC_TMR6_10_GCMP_A       = 272U,     /* TMR6_10_GCMA */
    INT_SRC_TMR6_10_GCMP_B       = 273U,     /* TMR6_10_GCMB */
    INT_SRC_TMR6_10_GCMP_C       = 274U,     /* TMR6_10_GCMC */
    INT_SRC_TMR6_10_GCMP_D       = 275U,     /* TMR6_10_GCMD */
    INT_SRC_TMR6_10_GCMP_E       = 276U,     /* TMR6_10_GCME */
    INT_SRC_TMR6_10_GCMP_F       = 277U,     /* TMR6_10_GCMF */
    INT_SRC_TMR6_10_OVF          = 278U,     /* TMR6_10_GOVF */
    INT_SRC_TMR6_10_UDF          = 279U,     /* TMR6_10_GUDF */
    INT_SRC_TMR6_10_DTE          = 280U,     /* TMR6_10_GDTE */
    INT_SRC_TMR6_10_SCMP_A       = 281U,     /* TMR6_10_SCMA */
    INT_SRC_TMR6_10_SCMP_B       = 282U,     /* TMR6_10_SCMB */
    /*  TIMER4_1  */
    INT_SRC_TMR4_1_GCMP_UH       = 288U,     /* TMR4_1_GCMUH */
    INT_SRC_TMR4_1_GCMP_UL       = 289U,     /* TMR4_1_GCMUL */
    INT_SRC_TMR4_1_GCMP_VH       = 290U,     /* TMR4_1_GCMVH */
    INT_SRC_TMR4_1_GCMP_VL       = 291U,     /* TMR4_1_GCMVL */
    INT_SRC_TMR4_1_GCMP_WH       = 292U,     /* TMR4_1_GCMWH */
    INT_SRC_TMR4_1_GCMP_WL       = 293U,     /* TMR4_1_GCMWL */
    INT_SRC_TMR4_1_OVF           = 294U,     /* TMR4_1_GOVF  */
    INT_SRC_TMR4_1_UDF           = 295U,     /* TMR4_1_GUDF  */
    INT_SRC_TMR4_1_RELOAD_U      = 296U,     /* TMR4_1_GRLU  */
    INT_SRC_TMR4_1_RELOAD_V      = 297U,     /* TMR4_1_GRLV  */
    INT_SRC_TMR4_1_RELOAD_W      = 298U,     /* TMR4_1_GRLW  */
    INT_SRC_TMR4_1_SCMP0         = 299U,     /* TMR4_1_SCM0 */
    INT_SRC_TMR4_1_SCMP1         = 300U,     /* TMR4_1_SCM1 */
    INT_SRC_TMR4_1_SCMP2         = 301U,     /* TMR4_1_SCM2 */
    INT_SRC_TMR4_1_SCMP3         = 302U,     /* TMR4_1_SCM3 */
    INT_SRC_TMR4_1_SCMP4         = 303U,     /* TMR4_1_SCM4 */
    INT_SRC_TMR4_1_SCMP5         = 304U,     /* TMR4_1_SCM5 */
    /*  CMP  */
    INT_SRC_CMP1                 = 305U,     /* CMP_1_IRQ */
    INT_SRC_CMP2                 = 306U,     /* CMP_2_IRQ */
    INT_SRC_CMP3                 = 307U,     /* CMP_3_IRQ */
    INT_SRC_CMP4                 = 308U,     /* CMP_4_IRQ */
    /*  CAN  */
    INT_SRC_CAN1_HOST            = 309U,     /* CAN_1_INT */
    INT_SRC_CAN2_HOST            = 310U,     /* CAN_2_INT */
    INT_SRC_CAN3_HOST            = 311U,     /* CAN_3_INT */
    /*  USART1  */
    INT_SRC_USART1_EI            = 320U,     /* USART_1_EI  */
    INT_SRC_USART1_RI            = 321U,     /* USART_1_RI  */
    INT_SRC_USART1_TI            = 322U,     /* USART_1_TI  */
    INT_SRC_USART1_TCI           = 323U,     /* USART_1_TCI */
    INT_SRC_USART1_RTO           = 324U,     /* USART_1_RTO */
    /*  USART2  */
    INT_SRC_USART2_EI            = 325U,     /* USART_2_EI  */
    INT_SRC_USART2_RI            = 326U,     /* USART_2_RI  */
    INT_SRC_USART2_TI            = 327U,     /* USART_2_TI  */
    INT_SRC_USART2_TCI           = 328U,     /* USART_2_TCI */
    INT_SRC_USART2_RTO           = 329U,     /* USART_2_RTO */
    /*  SPI1  */
    INT_SRC_SPI1_SPRI            = 330U,     /* SPI_1_SPRI */
    INT_SRC_SPI1_SPTI            = 331U,     /* SPI_1_SPTI */
    INT_SRC_SPI1_SPII            = 332U,     /* SPI_1_SPII */
    INT_SRC_SPI1_SPEI            = 333U,     /* SPI_1_SPEI */
    /*  SPI2  */
    INT_SRC_SPI2_SPRI            = 335U,     /* SPI_2_SPRI */
    INT_SRC_SPI2_SPTI            = 336U,     /* SPI_2_SPTI */
    INT_SRC_SPI2_SPII            = 337U,     /* SPI_2_SPII */
    INT_SRC_SPI2_SPEI            = 338U,     /* SPI_2_SPEI */
    /*  TIMERA_5  */
    INT_SRC_TMRA_5_OVF           = 340U,     /* TMRA_5_OVF */
    INT_SRC_TMRA_5_UDF           = 341U,     /* TMRA_5_UDF */
    INT_SRC_TMRA_5_CMP           = 342U,     /* TMRA_5_CMP */
    /*  TIMERA_6  */
    INT_SRC_TMRA_6_OVF           = 343U,     /* TMRA_6_OVF */
    INT_SRC_TMRA_6_UDF           = 344U,     /* TMRA_6_UDF */
    INT_SRC_TMRA_6_CMP           = 345U,     /* TMRA_6_CMP */
    /*  USBFS  */
    INT_SRC_USBFS_GLB            = 346U,     /* USBFS_GLB */
    /*  EVENT PORT  */
    INT_SRC_EVENT_PORT1          = 348U,     /* EVENT_PORT1 */
    INT_SRC_EVENT_PORT2          = 349U,     /* EVENT_PORT2 */
    INT_SRC_EVENT_PORT3          = 350U,     /* EVENT_PORT3 */
    INT_SRC_EVENT_PORT4          = 351U,     /* EVENT_PORT4 */
    /*  USART3  */
    INT_SRC_USART3_BRKWKPI       = 352U,     /* USART_3_BRKWKPI */
    INT_SRC_USART3_EI            = 353U,     /* USART_3_EI      */
    INT_SRC_USART3_RI            = 354U,     /* USART_3_RI      */
    INT_SRC_USART3_TI            = 355U,     /* USART_3_TI      */
    INT_SRC_USART3_TCI           = 356U,     /* USART_3_TCI     */
    /*  USART4  */
    INT_SRC_USART4_EI            = 357U,     /* USART_4_EI  */
    INT_SRC_USART4_RI            = 358U,     /* USART_4_RI  */
    INT_SRC_USART4_TI            = 359U,     /* USART_4_TI  */
    INT_SRC_USART4_TCI           = 360U,     /* USART_4_TCI */
    INT_SRC_USART4_RTO           = 361U,     /* USART_4_RTO */
    /*  SPI3  */
    INT_SRC_SPI3_SPRI            = 362U,     /* SPI_3_SPRI */
    INT_SRC_SPI3_SPTI            = 363U,     /* SPI_3_SPTI */
    INT_SRC_SPI3_SPII            = 364U,     /* SPI_3_SPII */
    INT_SRC_SPI3_SPEI            = 365U,     /* SPI_3_SPEI */
    /*  SPI4  */
    INT_SRC_SPI4_SPRI            = 367U,     /* SPI_4_SPRI */
    INT_SRC_SPI4_SPTI            = 368U,     /* SPI_4_SPTI */
    INT_SRC_SPI4_SPII            = 369U,     /* SPI_4_SPII */
    INT_SRC_SPI4_SPEI            = 370U,     /* SPI_4_SPEI */
    /*  EMB  */
    INT_SRC_EMB_GR0              = 372U,     /* EMB_GR0 */
    INT_SRC_EMB_GR1              = 373U,     /* EMB_GR1 */
    INT_SRC_EMB_GR2              = 374U,     /* EMB_GR2 */
    INT_SRC_EMB_GR3              = 375U,     /* EMB_GR3 */
    INT_SRC_EMB_GR4              = 376U,     /* EMB_GR4 */
    INT_SRC_EMB_GR5              = 377U,     /* EMB_GR5 */
    INT_SRC_EMB_GR6              = 378U,     /* EMB_GR6 */
    /*  HASH  */
    INT_SRC_HASH                 = 379U,     /* HASH_INT */
    /*  USART5  */
    INT_SRC_USART5_EI            = 384U,     /* USART_5_EI  */
    INT_SRC_USART5_RI            = 385U,     /* USART_5_RI  */
    INT_SRC_USART5_TI            = 386U,     /* USART_5_TI  */
    INT_SRC_USART5_TCI           = 387U,     /* USART_5_TCI */
    INT_SRC_USART5_RTO           = 388U,     /* USART_5_RTO */
    /*  USART6  */
    INT_SRC_USART6_BRKWKPI       = 389U,     /* USART_6_BRKWKPI */
    INT_SRC_USART6_EI            = 390U,     /* USART_6_EI      */
    INT_SRC_USART6_RI            = 391U,     /* USART_6_RI      */
    INT_SRC_USART6_TI            = 392U,     /* USART_6_TI      */
    INT_SRC_USART6_TCI           = 393U,     /* USART_6_TCI     */
    /*  USART1  */
    INT_SRC_USART1_TENDI         = 394U,     /* USART_1_TENDI */
    /*  USART2  */
    INT_SRC_USART2_TENDI         = 395U,     /* USART_2_TENDI */
    /*  USART3  */
    INT_SRC_USART3_TENDI         = 396U,     /* USART_3_TENDI */
    /*  USART4  */
    INT_SRC_USART4_TENDI         = 397U,     /* USART_4_TENDI */
    /*  USART5  */
    INT_SRC_USART5_TENDI         = 398U,     /* USART_5_TENDI */
    /*  USART6  */
    INT_SRC_USART6_TENDI         = 399U,     /* USART_6_TENDI */
    /*  MDIO  */
    INT_SRC_MDIO_WRF             = 400U,     /* MDIO_WRF  */
    INT_SRC_MDIO_ADRF            = 401U,     /* MDIO_ADRF */
    INT_SRC_MDIO_INCF            = 402U,     /* MDIO_INCF */
    INT_SRC_MDIO_RDF             = 403U,     /* MDIO_RDF  */
    INT_SRC_MDIO_DEVM            = 404U,     /* MDIO_DEVM */
    INT_SRC_MDIO_DEVN            = 405U,     /* MDIO_DEVN */
    INT_SRC_MDIO_PHYM            = 406U,     /* MDIO_PHYM */
    INT_SRC_MDIO_PHYN            = 407U,     /* MDIO_PHYN */
    INT_SRC_MDIO_TANM            = 408U,     /* MDIO_TANM */
    INT_SRC_MDIO_TO              = 409U,     /* MDIO_TO   */
    INT_SRC_MDIO_UDR             = 410U,     /* MDIO_UDR  */
    INT_SRC_MDIO_OVR             = 411U,     /* MDIO_OVR  */
    INT_SRC_MDIO_RBNE            = 412U,     /* MDIO_RBNE */
    /*  PLA  */
    INT_SRC_PLA_INT              = 431U,     /* PLA_INT */
    /*  I2C1  */
    INT_SRC_I2C1_RXI             = 448U,     /* I2C_1_RXI */
    INT_SRC_I2C1_TXI             = 449U,     /* I2C_1_TXI */
    INT_SRC_I2C1_TEI             = 450U,     /* I2C_1_TEI */
    INT_SRC_I2C1_EEI             = 451U,     /* I2C_1_EEI */
    /*  I2C2  */
    INT_SRC_I2C2_RXI             = 452U,     /* I2C_2_RXI */
    INT_SRC_I2C2_TXI             = 453U,     /* I2C_2_TXI */
    INT_SRC_I2C2_TEI             = 454U,     /* I2C_2_TEI */
    INT_SRC_I2C2_EEI             = 455U,     /* I2C_2_EEI */
    /*  I2C3  */
    INT_SRC_I2C3_RXI             = 456U,     /* I2C_3_RXI */
    INT_SRC_I2C3_TXI             = 457U,     /* I2C_3_TXI */
    INT_SRC_I2C3_TEI             = 458U,     /* I2C_3_TEI */
    INT_SRC_I2C3_EEI             = 459U,     /* I2C_3_EEI */
    /*  USART1  */
    INT_SRC_USART1_WUPI          = 464U,     /* USART_1_WUPI */
    /*  LVD  */
    INT_SRC_LVD1                = 465U,     /* LVD1 */
    INT_SRC_LVD2                = 466U,     /* LVD2 */
    /*  OTS  */
    INT_SRC_OTS                  = 467U,     /* OTS */
    /*  FCM  */
    INT_SRC_FCMFERRI             = 468U,     /* FCMFERRI */
    INT_SRC_FCMMENDI             = 469U,     /* FCMMENDI */
    INT_SRC_FCMCOVFI             = 470U,     /* FCMCOVFI */
    /*  WDT  */
    INT_SRC_WDT_REFUDF           = 471U,     /* WDT_REFUDF */
    /*  CTC  */
    INT_SRC_CTC_ERR              = 472U,     /* CTC_ERR */
    /*  ADC1  */
    INT_SRC_ADC1_EOCA            = 480U,     /* ADC_1_EOCA */
    INT_SRC_ADC1_EOCB            = 481U,     /* ADC_1_EOCB */
    INT_SRC_ADC1_CMP0            = 482U,     /* ADC_1_CMP0 */
    INT_SRC_ADC1_CMP1            = 483U,     /* ADC_1_CMP1 */
    /*  ADC2  */
    INT_SRC_ADC2_EOCA            = 484U,     /* ADC_2_EOCA */
    INT_SRC_ADC2_EOCB            = 485U,     /* ADC_2_EOCB */
    INT_SRC_ADC2_CMP0            = 486U,     /* ADC_2_CMP0 */
    INT_SRC_ADC2_CMP1            = 487U,     /* ADC_2_CMP1 */
    /*  ADC3  */
    INT_SRC_ADC3_EOCA            = 488U,     /* ADC_3_EOCA */
    INT_SRC_ADC3_EOCB            = 489U,     /* ADC_3_EOCB */
    INT_SRC_ADC3_CMP0            = 490U,     /* ADC_3_CMP0 */
    INT_SRC_ADC3_CMP1            = 491U,     /* ADC_3_CMP1 */
    /*  TRNG  */
    INT_SRC_TRNG_END             = 492U,     /* TRNG_END */
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
    uint8_t RESERVED4[4];
    __I  uint8_t  ISR;
    __IO uint8_t  ICR;
    __IO uint8_t  ISCLRR;
    uint8_t RESERVED5[5];
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
    __I  uint16_t DR17;
    __I  uint16_t DR18;
    __I  uint16_t DR19;
    __I  uint16_t DR20;
    __I  uint16_t DR21;
    __I  uint16_t DR22;
    __I  uint16_t DR23;
    __I  uint16_t DR24;
    uint8_t RESERVED7[30];
    __IO uint16_t AWDCR;
    __I  uint8_t  AWDSR;
    __IO uint8_t  AWDSCLRR;
    __IO uint16_t AWD0DR0;
    __IO uint16_t AWD0DR1;
    __IO uint8_t  AWD0CHSR;
    uint8_t RESERVED8[3];
    __IO uint16_t AWD1DR0;
    __IO uint16_t AWD1DR1;
    __IO uint8_t  AWD1CHSR;
    uint8_t RESERVED9[15];
    __IO uint8_t  PGACR;
    uint8_t RESERVED10[3];
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
    __IO uint32_t TMR4_TRGSEL;
    __IO uint32_t PEVNT_TRGSEL12;
    __IO uint32_t PEVNT_TRGSEL34;
    __IO uint32_t TMR0_TRGSEL;
    __IO uint32_t TMR2_TRGSEL;
    __IO uint32_t HASH_TRGSEL1;
    __IO uint32_t HASH_TRGSEL0;
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
    __IO uint32_t COMTRGSEL1;
    __IO uint32_t COMTRGSEL2;
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
    __I  uint8_t  OMR;
    __IO uint32_t PMSR;
    uint8_t RESERVED0[8];
    __IO uint32_t BWSR1;
    __IO uint16_t BWSR2;
} CM_CMP_TypeDef;

/**
 * @brief CMU
 */
typedef struct {
    uint8_t RESERVED0[24];
    __IO uint32_t XTALDIVR;
    __IO uint32_t XTALDIVCR;
    uint8_t RESERVED1[19504];
    __IO uint8_t  XTALCFGR;
    uint8_t RESERVED2[3];
    __IO uint8_t  XTAL32CR;
    uint8_t RESERVED3[3];
    __IO uint8_t  XTAL32CFGR;
    uint8_t RESERVED4[15];
    __IO uint8_t  XTAL32NFR;
    uint8_t RESERVED5[3];
    __IO uint8_t  LRCCR;
    uint8_t RESERVED6[7];
    __IO uint8_t  LRCTRM;
    uint8_t RESERVED7[29595];
    __IO uint16_t PERICKSEL;
    uint8_t RESERVED8[6];
    __IO uint16_t CANCKCFGR;
    uint8_t RESERVED9[6];
    __IO uint32_t SCFGR;
    __IO uint8_t  USBCKCFGR;
    uint8_t RESERVED10[1];
    __IO uint8_t  CKSWR;
    uint8_t RESERVED11[3];
    __IO uint8_t  PLLHCR;
    uint8_t RESERVED12[7];
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
    __I  uint16_t CNT;
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
    __IO uint32_t CHIPID;
    __IO uint32_t MCUSTAT;
    uint8_t RESERVED0[4];
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
    __IO uint32_t F0NWPRT;
    uint8_t RESERVED6[12];
    __IO uint32_t F1NWPRT;
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
    uint8_t RESERVED11[918];
    __IO uint16_t PSPCR;
    uint8_t RESERVED12[2];
    __IO uint16_t PCCR;
    uint8_t RESERVED13[2];
    __IO uint16_t PWPR;
    uint8_t RESERVED14[2];
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
    __IO uint32_t FSTR;
    __IO uint32_t SLVADDR;
} CM_I2C_TypeDef;

/**
 * @brief ICG
 */
typedef struct {
    __I  uint32_t ICG0;
    __I  uint32_t ICG1;
    uint8_t RESERVED0[4];
    __I  uint32_t ICG3;
    __I  uint32_t ICG4;
} CM_ICG_TypeDef;

/**
 * @brief INTC
 */
typedef struct {
    uint8_t RESERVED0[4];
    __IO uint32_t NMIER;
    __IO uint32_t NMIFR;
    __IO uint32_t NMIFCR;
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
    __IO uint32_t WKEN;
    __IO uint32_t EIFR;
    __IO uint32_t EIFCR;
    __IO uint32_t INTSEL0;
    __IO uint32_t INTSEL1;
    __IO uint32_t INTSEL2;
    __IO uint32_t INTSEL3;
    __IO uint32_t INTSEL4;
    __IO uint32_t INTSEL5;
    __IO uint32_t INTSEL6;
    __IO uint32_t INTSEL7;
    __IO uint32_t INTSEL8;
    __IO uint32_t INTSEL9;
    __IO uint32_t INTSEL10;
    __IO uint32_t INTSEL11;
    __IO uint32_t INTSEL12;
    __IO uint32_t INTSEL13;
    __IO uint32_t INTSEL14;
    __IO uint32_t INTSEL15;
    uint8_t RESERVED1[448];
    __IO uint32_t INTEN0;
    __IO uint32_t INTEN1;
    __IO uint32_t INTEN2;
    __IO uint32_t INTEN3;
    __IO uint32_t INTEN4;
    __IO uint32_t INTEN5;
    __IO uint32_t INTEN6;
    __IO uint32_t INTEN7;
    __IO uint32_t INTEN8;
    __IO uint32_t INTEN9;
    __IO uint32_t INTEN10;
    __IO uint32_t INTEN11;
    __IO uint32_t INTEN12;
    __IO uint32_t INTEN13;
    __IO uint32_t INTEN14;
    __IO uint32_t INTEN15;
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
 * @brief MDIO
 */
typedef struct {
    __IO uint32_t MDCON;
    __IO uint32_t MDCON1;
    __I  uint32_t MDFRM;
    __I  uint32_t MDRXD;
    __I  uint32_t MDADR;
    __IO uint32_t MDTXD;
    __IO uint32_t MDPHY;
    __IO uint32_t MDSTA;
    __IO uint32_t MDIEN;
    __I  uint32_t MDPIN;
    __IO uint32_t MDTO;
} CM_MDIO_TypeDef;

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
    __IO uint32_t MSPPBA;
    __IO uint32_t MSPPCTL;
    __IO uint32_t PSPPBA;
    __IO uint32_t PSPPCTL;
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
} CM_MPU_TypeDef;

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
    uint8_t RESERVED0[8];
    __IO uint32_t SMC_ENAR;
    uint8_t RESERVED1[8];
    __IO uint32_t CAN_SYCTLREG;
    __IO uint32_t USART1_NFC;
} CM_PERIC_TypeDef;

/**
 * @brief PLA
 */
typedef struct {
    __IO uint32_t GCTL;
    uint8_t RESERVED0[8];
    __I  uint32_t STAT;
    __IO uint32_t MUXS0;
    __IO uint32_t LUTCTL0;
    __IO uint32_t CTL0;
    __IO uint32_t MUXS1;
    __IO uint32_t LUTCTL1;
    __IO uint32_t CTL1;
    __IO uint32_t MUXS2;
    __IO uint32_t LUTCTL2;
    __IO uint32_t CTL2;
    __IO uint32_t MUXS3;
    __IO uint32_t LUTCTL3;
    __IO uint32_t CTL3;
    __IO uint32_t MUXS4;
    __IO uint32_t LUTCTL4;
    __IO uint32_t CTL4;
    __IO uint32_t MUXS5;
    __IO uint32_t LUTCTL5;
    __IO uint32_t CTL5;
    __IO uint32_t MUXS6;
    __IO uint32_t LUTCTL6;
    __IO uint32_t CTL6;
    __IO uint32_t MUXS7;
    __IO uint32_t LUTCTL7;
    __IO uint32_t CTL7;
    __IO uint32_t MUXS8;
    __IO uint32_t LUTCTL8;
    __IO uint32_t CTL8;
    __IO uint32_t MUXS9;
    __IO uint32_t LUTCTL9;
    __IO uint32_t CTL9;
    __IO uint32_t MUXS10;
    __IO uint32_t LUTCTL10;
    __IO uint32_t CTL10;
    __IO uint32_t MUXS11;
    __IO uint32_t LUTCTL11;
    __IO uint32_t CTL11;
    __IO uint32_t MUXS12;
    __IO uint32_t LUTCTL12;
    __IO uint32_t CTL12;
    __IO uint32_t MUXS13;
    __IO uint32_t LUTCTL13;
    __IO uint32_t CTL13;
    __IO uint32_t MUXS14;
    __IO uint32_t LUTCTL14;
    __IO uint32_t CTL14;
    __IO uint32_t MUXS15;
    __IO uint32_t LUTCTL15;
    __IO uint32_t CTL15;
} CM_PLA_TypeDef;

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
    uint8_t RESERVED1[2046];
    __IO uint8_t  PWRC0;
    uint8_t RESERVED2[3];
    __IO uint8_t  PWRC1;
    uint8_t RESERVED3[11];
    __IO uint8_t  PWRC4;
    uint8_t RESERVED4[3];
    __IO uint8_t  PVDCR0;
    uint8_t RESERVED5[3];
    __IO uint8_t  PVDCR1;
    uint8_t RESERVED6[3];
    __IO uint8_t  PVDFCR;
    uint8_t RESERVED7[3];
    __IO uint8_t  PVDLCR;
    uint8_t RESERVED8[7];
    __IO uint8_t  PDWKE0;
    uint8_t RESERVED9[3];
    __IO uint8_t  PDWKE1;
    uint8_t RESERVED10[3];
    __IO uint8_t  PDWKE2;
    uint8_t RESERVED11[3];
    __IO uint8_t  PDWKES;
    uint8_t RESERVED12[3];
    __IO uint8_t  PDWKF0;
    uint8_t RESERVED13[3];
    __IO uint8_t  PDWKF1;
    uint8_t RESERVED14[3];
    __IO uint8_t  PWRC5;
    uint8_t RESERVED15[3];
    __IO uint8_t  PWRC6;
    uint8_t RESERVED16[123];
    __IO uint8_t  PVDICR;
    uint8_t RESERVED17[3];
    __IO uint8_t  PVDDSR;
    uint8_t RESERVED18[3];
    __IO uint32_t RAMPC0;
    uint8_t RESERVED19[4];
    __IO uint32_t PRAMLPC;
    uint8_t RESERVED20[29496];
    __IO uint16_t STPMCR;
    uint8_t RESERVED21[1008];
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
    __IO uint32_t FRST0;
    __IO uint32_t FRST1;
    __IO uint32_t FRST2;
    __IO uint32_t FRST3;
    __IO uint8_t  PRSTCR0;
    uint8_t RESERVED0[3];
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
} CM_RTC_TypeDef;

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
    __IO uint32_t CR;
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
    uint8_t RESERVED0[8];
    __IO uint32_t CKCR;
    __IO uint32_t CKPR;
    __IO uint32_t CKSR;
    __IO uint32_t SRAM0_EIEN;
    __IO uint32_t SRAM0_EIBIT0;
    __IO uint32_t SRAM0_EIBIT1;
    __IO uint32_t SRAM0_ECCERRADDR;
    __IO uint32_t SRAMB_EIEN;
    __IO uint32_t SRAMB_EIBIT0;
    __IO uint32_t SRAMB_EIBIT1;
    __IO uint32_t SRAMB_ECCERRADDR;
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
    __IO uint16_t OCCRUH;
    uint8_t RESERVED0[2];
    __IO uint16_t OCCRUL;
    uint8_t RESERVED1[2];
    __IO uint16_t OCCRVH;
    uint8_t RESERVED2[2];
    __IO uint16_t OCCRVL;
    uint8_t RESERVED3[2];
    __IO uint16_t OCCRWH;
    uint8_t RESERVED4[2];
    __IO uint16_t OCCRWL;
    uint8_t RESERVED5[2];
    __IO uint16_t OCSRU;
    __IO uint16_t OCERU;
    __IO uint16_t OCSRV;
    __IO uint16_t OCERV;
    __IO uint16_t OCSRW;
    __IO uint16_t OCERW;
    __IO uint16_t OCMRUH;
    uint8_t RESERVED6[2];
    __IO uint32_t OCMRUL;
    __IO uint16_t OCMRVH;
    uint8_t RESERVED7[2];
    __IO uint32_t OCMRVL;
    __IO uint16_t OCMRWH;
    uint8_t RESERVED8[2];
    __IO uint32_t OCMRWL;
    uint8_t RESERVED9[4];
    __IO uint16_t CPSR;
    uint8_t RESERVED10[2];
    __IO uint16_t CNTR;
    uint8_t RESERVED11[2];
    __IO uint16_t CCSR;
    __IO uint16_t CVPR;
    __IO uint32_t PSCR;
    uint8_t RESERVED12[50];
    __IO uint16_t PFSRU;
    __IO uint16_t PDARU;
    __IO uint16_t PDBRU;
    uint8_t RESERVED13[2];
    __IO uint16_t PFSRV;
    __IO uint16_t PDARV;
    __IO uint16_t PDBRV;
    uint8_t RESERVED14[2];
    __IO uint16_t PFSRW;
    __IO uint16_t PDARW;
    __IO uint16_t PDBRW;
    __IO uint16_t POCRU;
    uint8_t RESERVED15[2];
    __IO uint16_t POCRV;
    uint8_t RESERVED16[2];
    __IO uint16_t POCRW;
    uint8_t RESERVED17[2];
    __IO uint16_t RCSR;
    uint8_t RESERVED18[10];
    __IO uint16_t SCCRUH;
    uint8_t RESERVED19[2];
    __IO uint16_t SCCRUL;
    uint8_t RESERVED20[2];
    __IO uint16_t SCCRVH;
    uint8_t RESERVED21[2];
    __IO uint16_t SCCRVL;
    uint8_t RESERVED22[2];
    __IO uint16_t SCCRWH;
    uint8_t RESERVED23[2];
    __IO uint16_t SCCRWL;
    uint8_t RESERVED24[2];
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
    __IO uint16_t SCER;
    uint8_t RESERVED25[2];
    __IO uint16_t SCIR;
    uint8_t RESERVED26[2];
    __IO uint16_t SCFR;
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
 * @brief TMR6_COMMON
 */
typedef struct {
    uint8_t RESERVED0[236];
    __IO uint32_t FCNTR;
    __IO uint32_t SSTAR;
    __IO uint32_t SSTPR;
    __IO uint32_t SCLRR;
    __IO uint32_t SUPDR;
} CM_TMR6_COMMON_TypeDef;

/**
 * @brief TMRA
 */
typedef struct {
    __IO uint32_t CNTER;
    __IO uint32_t PERAR;
    uint8_t RESERVED0[56];
    __IO uint32_t CMPAR1;
    __IO uint32_t CMPAR2;
    __IO uint32_t CMPAR3;
    __IO uint32_t CMPAR4;
    uint8_t RESERVED1[48];
    __IO uint8_t  BCSTRL;
    __IO uint8_t  BCSTRH;
    uint8_t RESERVED2[2];
    __IO uint16_t HCONR;
    uint8_t RESERVED3[2];
    __IO uint16_t HCUPR;
    uint8_t RESERVED4[2];
    __IO uint16_t HCDOR;
    uint8_t RESERVED5[2];
    __IO uint16_t ICONR;
    uint8_t RESERVED6[2];
    __IO uint16_t ECONR;
    uint8_t RESERVED7[2];
    __IO uint16_t FCONR;
    uint8_t RESERVED8[2];
    __IO uint16_t STFLR;
    uint8_t RESERVED9[34];
    __IO uint16_t BCONR1;
    uint8_t RESERVED10[6];
    __IO uint16_t BCONR2;
    uint8_t RESERVED11[54];
    __IO uint16_t CCONR1;
    uint8_t RESERVED12[2];
    __IO uint16_t CCONR2;
    uint8_t RESERVED13[2];
    __IO uint16_t CCONR3;
    uint8_t RESERVED14[2];
    __IO uint16_t CCONR4;
    uint8_t RESERVED15[50];
    __IO uint16_t PCONR1;
    uint8_t RESERVED16[2];
    __IO uint16_t PCONR2;
    uint8_t RESERVED17[2];
    __IO uint16_t PCONR3;
    uint8_t RESERVED18[2];
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
 * @brief VREF
 */
typedef struct {
    __IO uint32_t BGRCR;
    __IO uint32_t CSCR;
    __IO uint32_t CR;
} CM_VREF_TypeDef;

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
#define SMC_BASE                             (0x60000000UL)   /*!< SMC base address in the alias region */
#define QSPI_BASE                            (0x98000000UL)   /*!< QSPI base address in the alias region */

/******************************************************************************/
/*           Device Specific Peripheral Base Address                          */
/******************************************************************************/
#define CM_ADC1_BASE                         (0x40040000UL)
#define CM_ADC2_BASE                         (0x40040400UL)
#define CM_ADC3_BASE                         (0x40040800UL)
#define CM_AES_BASE                          (0x40008000UL)
#define CM_AOS_BASE                          (0x40010800UL)
#define CM_CAN1_BASE                         (0x40078000UL)
#define CM_CAN2_BASE                         (0x40071400UL)
#define CM_CAN3_BASE                         (0x40071000UL)
#define CM_CMP1_BASE                         (0x40038400UL)
#define CM_CMP2_BASE                         (0x40038500UL)
#define CM_CMP3_BASE                         (0x4003B000UL)
#define CM_CMP4_BASE                         (0x4003B100UL)
#define CM_CMU_BASE                          (0x40048000UL)
#define CM_CRC_BASE                          (0x40008C00UL)
#define CM_CTC_BASE                          (0x40049C00UL)
#define CM_DAC1_BASE                         (0x40041000UL)
#define CM_DAC2_BASE                         (0x40041400UL)
#define CM_DAC3_BASE                         (0x40041800UL)
#define CM_DAC4_BASE                         (0x40041C00UL)
#define CM_DBGC_BASE                         (0xE0042000UL)
#define CM_DCU1_BASE                         (0x40056000UL)
#define CM_DCU2_BASE                         (0x40056400UL)
#define CM_DCU3_BASE                         (0x40056800UL)
#define CM_DMA1_BASE                         (0x40053000UL)
#define CM_DMA2_BASE                         (0x40053400UL)
#define CM_EFM_BASE                          (0x40010400UL)
#define CM_EMB0_BASE                         (0x40017C00UL)
#define CM_EMB1_BASE                         (0x40017C20UL)
#define CM_EMB2_BASE                         (0x40017C40UL)
#define CM_EMB3_BASE                         (0x40017C60UL)
#define CM_EMB4_BASE                         (0x40017C80UL)
#define CM_EMB5_BASE                         (0x40017CA0UL)
#define CM_EMB6_BASE                         (0x40017CC0UL)
#define CM_FCM_BASE                          (0x40048400UL)
#define CM_FMAC1_BASE                        (0x40058000UL)
#define CM_FMAC2_BASE                        (0x40058400UL)
#define CM_FMAC3_BASE                        (0x40058800UL)
#define CM_FMAC4_BASE                        (0x40058C00UL)
#define CM_GPIO_BASE                         (0x40053800UL)
#define CM_HASH_BASE                         (0x40008400UL)
#define CM_I2C1_BASE                         (0x4003B400UL)
#define CM_I2C2_BASE                         (0x4003B800UL)
#define CM_I2C3_BASE                         (0x4003BC00UL)
#define CM_ICG_BASE                          (0x00000400UL)
#define CM_INTC_BASE                         (0x40051000UL)
#define CM_KEYSCAN_BASE                      (0x40050C00UL)
#define CM_MAU_BASE                          (0x40055000UL)
#define CM_MDIO_BASE                         (0x40028400UL)
#define CM_MPU_BASE                          (0x40050000UL)
#define CM_OTS_BASE                          (0x40010600UL)
#define CM_PERIC_BASE                        (0x40055400UL)
#define CM_PLA_BASE                          (0x4004FC00UL)
#define CM_PWC_BASE                          (0x40048000UL)
#define CM_QSPI_BASE                         (0x9C000000UL)
#define CM_RMU_BASE                          (0x4004CCE0UL)
#define CM_RTC_BASE                          (0x4004C000UL)
#define CM_SMC_BASE                          (0x88000000UL)
#define CM_SPI1_BASE                         (0x4001C000UL)
#define CM_SPI2_BASE                         (0x4001C400UL)
#define CM_SPI3_BASE                         (0x40020000UL)
#define CM_SPI4_BASE                         (0x40020400UL)
#define CM_SRAMC_BASE                        (0x40050800UL)
#define CM_SWDT_BASE                         (0x40049400UL)
#define CM_TMR0_1_BASE                       (0x40024000UL)
#define CM_TMR0_2_BASE                       (0x40024400UL)
#define CM_TMR2_1_BASE                       (0x40024800UL)
#define CM_TMR2_2_BASE                       (0x40024C00UL)
#define CM_TMR2_3_BASE                       (0x40025000UL)
#define CM_TMR2_4_BASE                       (0x40025400UL)
#define CM_TMR4_BASE                         (0x40038000UL)
#define CM_TMR6_1_BASE                       (0x4003C000UL)
#define CM_TMR6_10_BASE                      (0x4003E400UL)
#define CM_TMR6_2_BASE                       (0x4003C400UL)
#define CM_TMR6_3_BASE                       (0x4003C800UL)
#define CM_TMR6_4_BASE                       (0x4003CC00UL)
#define CM_TMR6_5_BASE                       (0x4003D000UL)
#define CM_TMR6_6_BASE                       (0x4003D400UL)
#define CM_TMR6_7_BASE                       (0x4003D800UL)
#define CM_TMR6_8_BASE                       (0x4003DC00UL)
#define CM_TMR6_9_BASE                       (0x4003E000UL)
#define CM_TMR6_COMMON_BASE                  (0x4003C300UL)
#define CM_TMRA_1_BASE                       (0x4003A000UL)
#define CM_TMRA_2_BASE                       (0x4003A400UL)
#define CM_TMRA_3_BASE                       (0x4003A800UL)
#define CM_TMRA_4_BASE                       (0x4003AC00UL)
#define CM_TMRA_5_BASE                       (0x40026000UL)
#define CM_TMRA_6_BASE                       (0x40026400UL)
#define CM_TRNG_BASE                         (0x40042000UL)
#define CM_USART1_BASE                       (0x4001CC00UL)
#define CM_USART2_BASE                       (0x4001D000UL)
#define CM_USART3_BASE                       (0x4001D400UL)
#define CM_USART4_BASE                       (0x40020C00UL)
#define CM_USART5_BASE                       (0x40021000UL)
#define CM_USART6_BASE                       (0x40021400UL)
#define CM_USBFS_BASE                        (0x40080000UL)
#define CM_VREF_BASE                         (0x4004F800UL)
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
#define CM_CAN3                              ((CM_CAN_TypeDef *)CM_CAN3_BASE)
#define CM_CMP1                              ((CM_CMP_TypeDef *)CM_CMP1_BASE)
#define CM_CMP2                              ((CM_CMP_TypeDef *)CM_CMP2_BASE)
#define CM_CMP3                              ((CM_CMP_TypeDef *)CM_CMP3_BASE)
#define CM_CMP4                              ((CM_CMP_TypeDef *)CM_CMP4_BASE)
#define CM_CMU                               ((CM_CMU_TypeDef *)CM_CMU_BASE)
#define CM_CRC                               ((CM_CRC_TypeDef *)CM_CRC_BASE)
#define CM_CTC                               ((CM_CTC_TypeDef *)CM_CTC_BASE)
#define CM_DAC1                              ((CM_DAC_TypeDef *)CM_DAC1_BASE)
#define CM_DAC2                              ((CM_DAC_TypeDef *)CM_DAC2_BASE)
#define CM_DAC3                              ((CM_DAC_TypeDef *)CM_DAC3_BASE)
#define CM_DAC4                              ((CM_DAC_TypeDef *)CM_DAC4_BASE)
#define CM_DBGC                              ((CM_DBGC_TypeDef *)CM_DBGC_BASE)
#define CM_DCU1                              ((CM_DCU_TypeDef *)CM_DCU1_BASE)
#define CM_DCU2                              ((CM_DCU_TypeDef *)CM_DCU2_BASE)
#define CM_DCU3                              ((CM_DCU_TypeDef *)CM_DCU3_BASE)
#define CM_DMA1                              ((CM_DMA_TypeDef *)CM_DMA1_BASE)
#define CM_DMA2                              ((CM_DMA_TypeDef *)CM_DMA2_BASE)
#define CM_EFM                               ((CM_EFM_TypeDef *)CM_EFM_BASE)
#define CM_EMB0                              ((CM_EMB_TypeDef *)CM_EMB0_BASE)
#define CM_EMB1                              ((CM_EMB_TypeDef *)CM_EMB1_BASE)
#define CM_EMB2                              ((CM_EMB_TypeDef *)CM_EMB2_BASE)
#define CM_EMB3                              ((CM_EMB_TypeDef *)CM_EMB3_BASE)
#define CM_EMB4                              ((CM_EMB_TypeDef *)CM_EMB4_BASE)
#define CM_EMB5                              ((CM_EMB_TypeDef *)CM_EMB5_BASE)
#define CM_EMB6                              ((CM_EMB_TypeDef *)CM_EMB6_BASE)
#define CM_FCM                               ((CM_FCM_TypeDef *)CM_FCM_BASE)
#define CM_FMAC1                             ((CM_FMAC_TypeDef *)CM_FMAC1_BASE)
#define CM_FMAC2                             ((CM_FMAC_TypeDef *)CM_FMAC2_BASE)
#define CM_FMAC3                             ((CM_FMAC_TypeDef *)CM_FMAC3_BASE)
#define CM_FMAC4                             ((CM_FMAC_TypeDef *)CM_FMAC4_BASE)
#define CM_GPIO                              ((CM_GPIO_TypeDef *)CM_GPIO_BASE)
#define CM_HASH                              ((CM_HASH_TypeDef *)CM_HASH_BASE)
#define CM_I2C1                              ((CM_I2C_TypeDef *)CM_I2C1_BASE)
#define CM_I2C2                              ((CM_I2C_TypeDef *)CM_I2C2_BASE)
#define CM_I2C3                              ((CM_I2C_TypeDef *)CM_I2C3_BASE)
#define CM_ICG                               ((CM_ICG_TypeDef *)CM_ICG_BASE)
#define CM_INTC                              ((CM_INTC_TypeDef *)CM_INTC_BASE)
#define CM_KEYSCAN                           ((CM_KEYSCAN_TypeDef *)CM_KEYSCAN_BASE)
#define CM_MAU                               ((CM_MAU_TypeDef *)CM_MAU_BASE)
#define CM_MDIO                              ((CM_MDIO_TypeDef *)CM_MDIO_BASE)
#define CM_MPU                               ((CM_MPU_TypeDef *)CM_MPU_BASE)
#define CM_OTS                               ((CM_OTS_TypeDef *)CM_OTS_BASE)
#define CM_PERIC                             ((CM_PERIC_TypeDef *)CM_PERIC_BASE)
#define CM_PLA                               ((CM_PLA_TypeDef *)CM_PLA_BASE)
#define CM_PWC                               ((CM_PWC_TypeDef *)CM_PWC_BASE)
#define CM_QSPI                              ((CM_QSPI_TypeDef *)CM_QSPI_BASE)
#define CM_RMU                               ((CM_RMU_TypeDef *)CM_RMU_BASE)
#define CM_RTC                               ((CM_RTC_TypeDef *)CM_RTC_BASE)
#define CM_SMC                               ((CM_SMC_TypeDef *)CM_SMC_BASE)
#define CM_SPI1                              ((CM_SPI_TypeDef *)CM_SPI1_BASE)
#define CM_SPI2                              ((CM_SPI_TypeDef *)CM_SPI2_BASE)
#define CM_SPI3                              ((CM_SPI_TypeDef *)CM_SPI3_BASE)
#define CM_SPI4                              ((CM_SPI_TypeDef *)CM_SPI4_BASE)
#define CM_SRAMC                             ((CM_SRAMC_TypeDef *)CM_SRAMC_BASE)
#define CM_SWDT                              ((CM_SWDT_TypeDef *)CM_SWDT_BASE)
#define CM_TMR0_1                            ((CM_TMR0_TypeDef *)CM_TMR0_1_BASE)
#define CM_TMR0_2                            ((CM_TMR0_TypeDef *)CM_TMR0_2_BASE)
#define CM_TMR2_1                            ((CM_TMR2_TypeDef *)CM_TMR2_1_BASE)
#define CM_TMR2_2                            ((CM_TMR2_TypeDef *)CM_TMR2_2_BASE)
#define CM_TMR2_3                            ((CM_TMR2_TypeDef *)CM_TMR2_3_BASE)
#define CM_TMR2_4                            ((CM_TMR2_TypeDef *)CM_TMR2_4_BASE)
#define CM_TMR4                              ((CM_TMR4_TypeDef *)CM_TMR4_BASE)
#define CM_TMR6_1                            ((CM_TMR6_TypeDef *)CM_TMR6_1_BASE)
#define CM_TMR6_10                           ((CM_TMR6_TypeDef *)CM_TMR6_10_BASE)
#define CM_TMR6_2                            ((CM_TMR6_TypeDef *)CM_TMR6_2_BASE)
#define CM_TMR6_3                            ((CM_TMR6_TypeDef *)CM_TMR6_3_BASE)
#define CM_TMR6_4                            ((CM_TMR6_TypeDef *)CM_TMR6_4_BASE)
#define CM_TMR6_5                            ((CM_TMR6_TypeDef *)CM_TMR6_5_BASE)
#define CM_TMR6_6                            ((CM_TMR6_TypeDef *)CM_TMR6_6_BASE)
#define CM_TMR6_7                            ((CM_TMR6_TypeDef *)CM_TMR6_7_BASE)
#define CM_TMR6_8                            ((CM_TMR6_TypeDef *)CM_TMR6_8_BASE)
#define CM_TMR6_9                            ((CM_TMR6_TypeDef *)CM_TMR6_9_BASE)
#define CM_TMR6_COMMON                       ((CM_TMR6_COMMON_TypeDef *)CM_TMR6_COMMON_BASE)
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
#define CM_USART5                            ((CM_USART_TypeDef *)CM_USART5_BASE)
#define CM_USART6                            ((CM_USART_TypeDef *)CM_USART6_BASE)
#define CM_USBFS                             ((CM_USBFS_TypeDef *)CM_USBFS_BASE)
#define CM_VREF                              ((CM_VREF_TypeDef *)CM_VREF_BASE)
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
#define ADC_CHSELRA_CHSELA                             (0x01FFFFFFUL)

/*  Bit definition for ADC_CHSELRB register  */
#define ADC_CHSELRB_CHSELB                             (0x01FFFFFFUL)

/*  Bit definition for ADC_AVCHSELR register  */
#define ADC_AVCHSELR_AVCHSEL                           (0x01FFFFFFUL)

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
#define ADC_PGAVSSENR_PGAVSSEN                         (0x01U)

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

/*  Bit definition for AOS_TMR4_TRGSEL register  */
#define AOS_TMR4_TRGSEL_TRGSEL_POS                     (0U)
#define AOS_TMR4_TRGSEL_TRGSEL                         (0x000001FFUL)
#define AOS_TMR4_TRGSEL_COMEN_POS                      (30U)
#define AOS_TMR4_TRGSEL_COMEN                          (0xC0000000UL)
#define AOS_TMR4_TRGSEL_COMEN_0                        (0x40000000UL)
#define AOS_TMR4_TRGSEL_COMEN_1                        (0x80000000UL)

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

/*  Bit definition for AOS_HASH_TRGSEL1 register  */
#define AOS_HASH_TRGSEL1_TRGSEL_POS                    (0U)
#define AOS_HASH_TRGSEL1_TRGSEL                        (0x000001FFUL)
#define AOS_HASH_TRGSEL1_COMEN_POS                     (30U)
#define AOS_HASH_TRGSEL1_COMEN                         (0xC0000000UL)
#define AOS_HASH_TRGSEL1_COMEN_0                       (0x40000000UL)
#define AOS_HASH_TRGSEL1_COMEN_1                       (0x80000000UL)

/*  Bit definition for AOS_HASH_TRGSEL0 register  */
#define AOS_HASH_TRGSEL0_TRGSEL_POS                    (0U)
#define AOS_HASH_TRGSEL0_TRGSEL                        (0x000001FFUL)
#define AOS_HASH_TRGSEL0_COMEN_POS                     (30U)
#define AOS_HASH_TRGSEL0_COMEN                         (0xC0000000UL)
#define AOS_HASH_TRGSEL0_COMEN_0                       (0x40000000UL)
#define AOS_HASH_TRGSEL0_COMEN_1                       (0x80000000UL)

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

/*  Bit definition for AOS_COMTRGSEL1 register  */
#define AOS_COMTRGSEL1_COMTRG                          (0x000001FFUL)

/*  Bit definition for AOS_COMTRGSEL2 register  */
#define AOS_COMTRGSEL2_COMTRG                          (0x000001FFUL)

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
#define CMP_MDR_CENA_POS                               (0U)
#define CMP_MDR_CENA                                   (0x01U)
#define CMP_MDR_HYST_POS                               (1U)
#define CMP_MDR_HYST                                   (0x0EU)
#define CMP_MDR_WDEN_POS                               (4U)
#define CMP_MDR_WDEN                                   (0x10U)

/*  Bit definition for CMP_FIR register  */
#define CMP_FIR_FCKS_POS                               (0U)
#define CMP_FIR_FCKS                                   (0x07U)
#define CMP_FIR_CIEN_POS                               (3U)
#define CMP_FIR_CIEN                                   (0x08U)
#define CMP_FIR_EDGS_POS                               (4U)
#define CMP_FIR_EDGS                                   (0x30U)
#define CMP_FIR_CFF_POS                                (6U)
#define CMP_FIR_CFF                                    (0x40U)
#define CMP_FIR_CRF_POS                                (7U)
#define CMP_FIR_CRF                                    (0x80U)

/*  Bit definition for CMP_OCR register  */
#define CMP_OCR_COEN_POS                               (0U)
#define CMP_OCR_COEN                                   (0x01U)
#define CMP_OCR_COPS_POS                               (1U)
#define CMP_OCR_COPS                                   (0x02U)
#define CMP_OCR_CPOE_POS                               (2U)
#define CMP_OCR_CPOE                                   (0x04U)
#define CMP_OCR_BWEN_POS                               (4U)
#define CMP_OCR_BWEN                                   (0x10U)
#define CMP_OCR_BWMD_POS                               (5U)
#define CMP_OCR_BWMD                                   (0x20U)
#define CMP_OCR_BWOL_POS                               (6U)
#define CMP_OCR_BWOL                                   (0xC0U)

/*  Bit definition for CMP_OMR register  */
#define CMP_OMR_CMON                                   (0x01U)

/*  Bit definition for CMP_PMSR register  */
#define CMP_PMSR_RVSL_POS                              (0U)
#define CMP_PMSR_RVSL                                  (0x000003FFUL)
#define CMP_PMSR_RVSL_0                                (0x00000001UL)
#define CMP_PMSR_RVSL_1                                (0x00000002UL)
#define CMP_PMSR_RVSL_2                                (0x00000004UL)
#define CMP_PMSR_RVSL_3                                (0x00000008UL)
#define CMP_PMSR_RVSL_4                                (0x00000010UL)
#define CMP_PMSR_RVSL_5                                (0x00000020UL)
#define CMP_PMSR_RVSL_6                                (0x00000040UL)
#define CMP_PMSR_RVSL_7                                (0x00000080UL)
#define CMP_PMSR_RVSL_8                                (0x00000100UL)
#define CMP_PMSR_RVSL_9                                (0x00000200UL)
#define CMP_PMSR_CVSL_POS                              (16U)
#define CMP_PMSR_CVSL                                  (0x000F0000UL)
#define CMP_PMSR_CVSL_0                                (0x00010000UL)
#define CMP_PMSR_CVSL_1                                (0x00020000UL)
#define CMP_PMSR_CVSL_2                                (0x00040000UL)
#define CMP_PMSR_CVSL_3                                (0x00080000UL)

/*  Bit definition for CMP_BWSR1 register  */
#define CMP_BWSR1_CTWS0_POS                            (0U)
#define CMP_BWSR1_CTWS0                                (0x00000001UL)
#define CMP_BWSR1_CTWS1_POS                            (1U)
#define CMP_BWSR1_CTWS1                                (0x00000002UL)
#define CMP_BWSR1_CTWS2_POS                            (2U)
#define CMP_BWSR1_CTWS2                                (0x00000004UL)
#define CMP_BWSR1_CTWS3_POS                            (3U)
#define CMP_BWSR1_CTWS3                                (0x00000008UL)
#define CMP_BWSR1_CTWS4_POS                            (4U)
#define CMP_BWSR1_CTWS4                                (0x00000010UL)
#define CMP_BWSR1_CTWS5_POS                            (5U)
#define CMP_BWSR1_CTWS5                                (0x00000020UL)
#define CMP_BWSR1_CTWS6_POS                            (6U)
#define CMP_BWSR1_CTWS6                                (0x00000040UL)
#define CMP_BWSR1_CTWS7_POS                            (7U)
#define CMP_BWSR1_CTWS7                                (0x00000080UL)
#define CMP_BWSR1_CTWS8_POS                            (8U)
#define CMP_BWSR1_CTWS8                                (0x00000100UL)
#define CMP_BWSR1_CTWS9_POS                            (9U)
#define CMP_BWSR1_CTWS9                                (0x00000200UL)
#define CMP_BWSR1_CTWS10_POS                           (10U)
#define CMP_BWSR1_CTWS10                               (0x00000400UL)
#define CMP_BWSR1_CTWS11_POS                           (11U)
#define CMP_BWSR1_CTWS11                               (0x00000800UL)
#define CMP_BWSR1_CTWS12_POS                           (12U)
#define CMP_BWSR1_CTWS12                               (0x00001000UL)
#define CMP_BWSR1_CTWS13_POS                           (13U)
#define CMP_BWSR1_CTWS13                               (0x00002000UL)
#define CMP_BWSR1_CTWS14_POS                           (14U)
#define CMP_BWSR1_CTWS14                               (0x00004000UL)
#define CMP_BWSR1_CTWS15_POS                           (15U)
#define CMP_BWSR1_CTWS15                               (0x00008000UL)
#define CMP_BWSR1_CTWP0_POS                            (16U)
#define CMP_BWSR1_CTWP0                                (0x00010000UL)
#define CMP_BWSR1_CTWP1_POS                            (17U)
#define CMP_BWSR1_CTWP1                                (0x00020000UL)
#define CMP_BWSR1_CTWP2_POS                            (18U)
#define CMP_BWSR1_CTWP2                                (0x00040000UL)
#define CMP_BWSR1_CTWP3_POS                            (19U)
#define CMP_BWSR1_CTWP3                                (0x00080000UL)
#define CMP_BWSR1_CTWP4_POS                            (20U)
#define CMP_BWSR1_CTWP4                                (0x00100000UL)
#define CMP_BWSR1_CTWP5_POS                            (21U)
#define CMP_BWSR1_CTWP5                                (0x00200000UL)
#define CMP_BWSR1_CTWP6_POS                            (22U)
#define CMP_BWSR1_CTWP6                                (0x00400000UL)
#define CMP_BWSR1_CTWP7_POS                            (23U)
#define CMP_BWSR1_CTWP7                                (0x00800000UL)
#define CMP_BWSR1_CTWP8_POS                            (24U)
#define CMP_BWSR1_CTWP8                                (0x01000000UL)
#define CMP_BWSR1_CTWP9_POS                            (25U)
#define CMP_BWSR1_CTWP9                                (0x02000000UL)
#define CMP_BWSR1_CTWP10_POS                           (26U)
#define CMP_BWSR1_CTWP10                               (0x04000000UL)
#define CMP_BWSR1_CTWP11_POS                           (27U)
#define CMP_BWSR1_CTWP11                               (0x08000000UL)
#define CMP_BWSR1_CTWP12_POS                           (28U)
#define CMP_BWSR1_CTWP12                               (0x10000000UL)
#define CMP_BWSR1_CTWP13_POS                           (29U)
#define CMP_BWSR1_CTWP13                               (0x20000000UL)
#define CMP_BWSR1_CTWP14_POS                           (30U)
#define CMP_BWSR1_CTWP14                               (0x40000000UL)
#define CMP_BWSR1_CTWP15_POS                           (31U)
#define CMP_BWSR1_CTWP15                               (0x80000000UL)

/*  Bit definition for CMP_BWSR2 register  */
#define CMP_BWSR2_MSKW_POS                             (0U)
#define CMP_BWSR2_MSKW                                 (0x00FFU)
#define CMP_BWSR2_TWEG_POS                             (8U)
#define CMP_BWSR2_TWEG                                 (0x0300U)
#define CMP_BWSR2_TWEG_0                               (0x0100U)
#define CMP_BWSR2_TWEG_1                               (0x0200U)

/*******************************************************************************
                Bit definition for Peripheral CMU
*******************************************************************************/
/*  Bit definition for CMU_XTALDIVR register  */
#define CMU_XTALDIVR_DENOMINATOR_POS                   (0U)
#define CMU_XTALDIVR_DENOMINATOR                       (0x000007FFUL)
#define CMU_XTALDIVR_NUMERATOR_POS                     (12U)
#define CMU_XTALDIVR_NUMERATOR                         (0x1FFFF000UL)

/*  Bit definition for CMU_XTALDIVCR register  */
#define CMU_XTALDIVCR_FRADIVEN                         (0x00000001UL)

/*  Bit definition for CMU_XTALCFGR register  */
#define CMU_XTALCFGR_XTALMS_POS                        (3U)
#define CMU_XTALCFGR_XTALMS                            (0x08U)
#define CMU_XTALCFGR_XTALDRV_POS                       (4U)
#define CMU_XTALCFGR_XTALDRV                           (0x30U)
#define CMU_XTALCFGR_XTALDRV_0                         (0x10U)
#define CMU_XTALCFGR_XTALDRV_1                         (0x20U)

/*  Bit definition for CMU_XTAL32CR register  */
#define CMU_XTAL32CR_XTAL32STP                         (0x01U)

/*  Bit definition for CMU_XTAL32CFGR register  */
#define CMU_XTAL32CFGR_XTAL32DRV                       (0x07U)

/*  Bit definition for CMU_XTAL32NFR register  */
#define CMU_XTAL32NFR_XTAL32NF                         (0x03U)

/*  Bit definition for CMU_LRCCR register  */
#define CMU_LRCCR_LRCSTP                               (0x01U)

/*  Bit definition for CMU_LRCTRM register  */
#define CMU_LRCTRM                                     (0xFFU)

/*  Bit definition for CMU_PERICKSEL register  */
#define CMU_PERICKSEL_PERICKSEL                        (0x000FU)

/*  Bit definition for CMU_CANCKCFGR register  */
#define CMU_CANCKCFGR_CAN1CKS_POS                      (0U)
#define CMU_CANCKCFGR_CAN1CKS                          (0x000FU)
#define CMU_CANCKCFGR_CAN2CKS_POS                      (4U)
#define CMU_CANCKCFGR_CAN2CKS                          (0x00F0U)
#define CMU_CANCKCFGR_CAN3CKS_POS                      (8U)
#define CMU_CANCKCFGR_CAN3CKS                          (0x0F00U)

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
#define CMU_PLLHCFGR_PLLHM                             (0x0000001FUL)
#define CMU_PLLHCFGR_PLLSRC_POS                        (7U)
#define CMU_PLLHCFGR_PLLSRC                            (0x00000080UL)
#define CMU_PLLHCFGR_PLLHN_POS                         (8U)
#define CMU_PLLHCFGR_PLLHN                             (0x0001FF00UL)
#define CMU_PLLHCFGR_PLLHR_POS                         (20U)
#define CMU_PLLHCFGR_PLLHR                             (0x00F00000UL)
#define CMU_PLLHCFGR_PLLHQ_POS                         (24U)
#define CMU_PLLHCFGR_PLLHQ                             (0x0F000000UL)
#define CMU_PLLHCFGR_PLLHP_POS                         (28U)
#define CMU_PLLHCFGR_PLLHP                             (0xF0000000UL)

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
#define CTC_CR1_REFCKS_POS                             (4U)
#define CTC_CR1_REFCKS                                 (0x00000030UL)
#define CTC_CR1_REFCKS_0                               (0x00000010UL)
#define CTC_CR1_REFCKS_1                               (0x00000020UL)
#define CTC_CR1_ERRIE_POS                              (6U)
#define CTC_CR1_ERRIE                                  (0x00000040UL)
#define CTC_CR1_CTCEN_POS                              (7U)
#define CTC_CR1_CTCEN                                  (0x00000080UL)
#define CTC_CR1_HRCPSC_POS                             (8U)
#define CTC_CR1_HRCPSC                                 (0x00000700UL)
#define CTC_CR1_REFEDG_POS                             (12U)
#define CTC_CR1_REFEDG                                 (0x00003000UL)
#define CTC_CR1_REFEDG_0                               (0x00001000UL)
#define CTC_CR1_REFEDG_1                               (0x00002000UL)
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

/*  Bit definition for CTC_CNT register  */
#define CTC_CNT_CTCCNT                                 (0xFFFFU)

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
#define DAC_DACR_DAOGS1_POS                            (3U)
#define DAC_DACR_DAOGS1                                (0x0008U)
#define DAC_DACR_DAOGS2_POS                            (4U)
#define DAC_DACR_DAOGS2                                (0x0010U)
#define DAC_DACR_DPSEL_POS                             (8U)
#define DAC_DACR_DPSEL                                 (0x0100U)
#define DAC_DACR_DAAMP1_POS                            (9U)
#define DAC_DACR_DAAMP1                                (0x0200U)
#define DAC_DACR_DAAMP2_POS                            (10U)
#define DAC_DACR_DAAMP2                                (0x0400U)

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

/*  Bit definition for DBGC_CHIPID register  */
#define DBGC_CHIPID                                    (0xFFFFFFFFUL)

/*  Bit definition for DBGC_MCUSTAT register  */
#define DBGC_MCUSTAT_AUTHFG_POS                        (0U)
#define DBGC_MCUSTAT_AUTHFG                            (0x00000001UL)
#define DBGC_MCUSTAT_PRTLV1_POS                        (2U)
#define DBGC_MCUSTAT_PRTLV1                            (0x00000004UL)
#define DBGC_MCUSTAT_PRTLV2_POS                        (3U)
#define DBGC_MCUSTAT_PRTLV2                            (0x00000008UL)
#define DBGC_MCUSTAT_PRTLV3_POS                        (4U)
#define DBGC_MCUSTAT_PRTLV3                            (0x00000010UL)

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
#define DBGC_MCUSTPCTL_M23STP_POS                      (23U)
#define DBGC_MCUSTPCTL_M23STP                          (0x00800000UL)
#define DBGC_MCUSTPCTL_M24STP_POS                      (24U)
#define DBGC_MCUSTPCTL_M24STP                          (0x01000000UL)

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

/*******************************************************************************
                Bit definition for Peripheral DCU
*******************************************************************************/
/*  Bit definition for DCU_CTL register  */
#define DCU_CTL_MODE_POS                               (0U)
#define DCU_CTL_MODE                                   (0x0000000FUL)
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
#define DMA_CHCTL_HPROT_POS                            (14U)
#define DMA_CHCTL_HPROT                                (0x0000C000UL)

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
#define EFM_WLOCK_WLOCK0_POS                           (0U)
#define EFM_WLOCK_WLOCK0                               (0x00000001UL)
#define EFM_WLOCK_WLOCK1_POS                           (4U)
#define EFM_WLOCK_WLOCK1                               (0x00000010UL)

/*  Bit definition for EFM_F0NWPRT register  */
#define EFM_F0NWPRT_F0NWPRT0_POS                       (0U)
#define EFM_F0NWPRT_F0NWPRT0                           (0x00000001UL)
#define EFM_F0NWPRT_F0NWPRT1_POS                       (1U)
#define EFM_F0NWPRT_F0NWPRT1                           (0x00000002UL)
#define EFM_F0NWPRT_F0NWPRT2_POS                       (2U)
#define EFM_F0NWPRT_F0NWPRT2                           (0x00000004UL)
#define EFM_F0NWPRT_F0NWPRT3_POS                       (3U)
#define EFM_F0NWPRT_F0NWPRT3                           (0x00000008UL)
#define EFM_F0NWPRT_F0NWPRT4_POS                       (4U)
#define EFM_F0NWPRT_F0NWPRT4                           (0x00000010UL)
#define EFM_F0NWPRT_F0NWPRT5_POS                       (5U)
#define EFM_F0NWPRT_F0NWPRT5                           (0x00000020UL)
#define EFM_F0NWPRT_F0NWPRT6_POS                       (6U)
#define EFM_F0NWPRT_F0NWPRT6                           (0x00000040UL)
#define EFM_F0NWPRT_F0NWPRT7_POS                       (7U)
#define EFM_F0NWPRT_F0NWPRT7                           (0x00000080UL)
#define EFM_F0NWPRT_F0NWPRT8_POS                       (8U)
#define EFM_F0NWPRT_F0NWPRT8                           (0x00000100UL)
#define EFM_F0NWPRT_F0NWPRT9_POS                       (9U)
#define EFM_F0NWPRT_F0NWPRT9                           (0x00000200UL)
#define EFM_F0NWPRT_F0NWPRT10_POS                      (10U)
#define EFM_F0NWPRT_F0NWPRT10                          (0x00000400UL)
#define EFM_F0NWPRT_F0NWPRT11_POS                      (11U)
#define EFM_F0NWPRT_F0NWPRT11                          (0x00000800UL)
#define EFM_F0NWPRT_F0NWPRT12_POS                      (12U)
#define EFM_F0NWPRT_F0NWPRT12                          (0x00001000UL)
#define EFM_F0NWPRT_F0NWPRT13_POS                      (13U)
#define EFM_F0NWPRT_F0NWPRT13                          (0x00002000UL)
#define EFM_F0NWPRT_F0NWPRT14_POS                      (14U)
#define EFM_F0NWPRT_F0NWPRT14                          (0x00004000UL)
#define EFM_F0NWPRT_F0NWPRT15_POS                      (15U)
#define EFM_F0NWPRT_F0NWPRT15                          (0x00008000UL)
#define EFM_F0NWPRT_F0NWPRT16_POS                      (16U)
#define EFM_F0NWPRT_F0NWPRT16                          (0x00010000UL)
#define EFM_F0NWPRT_F0NWPRT17_POS                      (17U)
#define EFM_F0NWPRT_F0NWPRT17                          (0x00020000UL)
#define EFM_F0NWPRT_F0NWPRT18_POS                      (18U)
#define EFM_F0NWPRT_F0NWPRT18                          (0x00040000UL)
#define EFM_F0NWPRT_F0NWPRT19_POS                      (19U)
#define EFM_F0NWPRT_F0NWPRT19                          (0x00080000UL)
#define EFM_F0NWPRT_F0NWPRT20_POS                      (20U)
#define EFM_F0NWPRT_F0NWPRT20                          (0x00100000UL)
#define EFM_F0NWPRT_F0NWPRT21_POS                      (21U)
#define EFM_F0NWPRT_F0NWPRT21                          (0x00200000UL)
#define EFM_F0NWPRT_F0NWPRT22_POS                      (22U)
#define EFM_F0NWPRT_F0NWPRT22                          (0x00400000UL)
#define EFM_F0NWPRT_F0NWPRT23_POS                      (23U)
#define EFM_F0NWPRT_F0NWPRT23                          (0x00800000UL)
#define EFM_F0NWPRT_F0NWPRT24_POS                      (24U)
#define EFM_F0NWPRT_F0NWPRT24                          (0x01000000UL)
#define EFM_F0NWPRT_F0NWPRT25_POS                      (25U)
#define EFM_F0NWPRT_F0NWPRT25                          (0x02000000UL)
#define EFM_F0NWPRT_F0NWPRT26_POS                      (26U)
#define EFM_F0NWPRT_F0NWPRT26                          (0x04000000UL)
#define EFM_F0NWPRT_F0NWPRT27_POS                      (27U)
#define EFM_F0NWPRT_F0NWPRT27                          (0x08000000UL)
#define EFM_F0NWPRT_F0NWPRT28_POS                      (28U)
#define EFM_F0NWPRT_F0NWPRT28                          (0x10000000UL)
#define EFM_F0NWPRT_F0NWPRT29_POS                      (29U)
#define EFM_F0NWPRT_F0NWPRT29                          (0x20000000UL)
#define EFM_F0NWPRT_F0NWPRT30_POS                      (30U)
#define EFM_F0NWPRT_F0NWPRT30                          (0x40000000UL)
#define EFM_F0NWPRT_F0NWPRT31_POS                      (31U)
#define EFM_F0NWPRT_F0NWPRT31                          (0x80000000UL)

/*  Bit definition for EFM_F1NWPRT register  */
#define EFM_F1NWPRT_F1NWPRT0_POS                       (0U)
#define EFM_F1NWPRT_F1NWPRT0                           (0x00000001UL)
#define EFM_F1NWPRT_F1NWPRT1_POS                       (1U)
#define EFM_F1NWPRT_F1NWPRT1                           (0x00000002UL)
#define EFM_F1NWPRT_F1NWPRT2_POS                       (2U)
#define EFM_F1NWPRT_F1NWPRT2                           (0x00000004UL)
#define EFM_F1NWPRT_F1NWPRT3_POS                       (3U)
#define EFM_F1NWPRT_F1NWPRT3                           (0x00000008UL)
#define EFM_F1NWPRT_F1NWPRT4_POS                       (4U)
#define EFM_F1NWPRT_F1NWPRT4                           (0x00000010UL)
#define EFM_F1NWPRT_F1NWPRT5_POS                       (5U)
#define EFM_F1NWPRT_F1NWPRT5                           (0x00000020UL)
#define EFM_F1NWPRT_F1NWPRT6_POS                       (6U)
#define EFM_F1NWPRT_F1NWPRT6                           (0x00000040UL)
#define EFM_F1NWPRT_F1NWPRT7_POS                       (7U)
#define EFM_F1NWPRT_F1NWPRT7                           (0x00000080UL)
#define EFM_F1NWPRT_F1NWPRT8_POS                       (8U)
#define EFM_F1NWPRT_F1NWPRT8                           (0x00000100UL)
#define EFM_F1NWPRT_F1NWPRT9_POS                       (9U)
#define EFM_F1NWPRT_F1NWPRT9                           (0x00000200UL)
#define EFM_F1NWPRT_F1NWPRT10_POS                      (10U)
#define EFM_F1NWPRT_F1NWPRT10                          (0x00000400UL)
#define EFM_F1NWPRT_F1NWPRT11_POS                      (11U)
#define EFM_F1NWPRT_F1NWPRT11                          (0x00000800UL)
#define EFM_F1NWPRT_F1NWPRT12_POS                      (12U)
#define EFM_F1NWPRT_F1NWPRT12                          (0x00001000UL)
#define EFM_F1NWPRT_F1NWPRT13_POS                      (13U)
#define EFM_F1NWPRT_F1NWPRT13                          (0x00002000UL)
#define EFM_F1NWPRT_F1NWPRT14_POS                      (14U)
#define EFM_F1NWPRT_F1NWPRT14                          (0x00004000UL)
#define EFM_F1NWPRT_F1NWPRT15_POS                      (15U)
#define EFM_F1NWPRT_F1NWPRT15                          (0x00008000UL)
#define EFM_F1NWPRT_F1NWPRT16_POS                      (16U)
#define EFM_F1NWPRT_F1NWPRT16                          (0x00010000UL)
#define EFM_F1NWPRT_F1NWPRT17_POS                      (17U)
#define EFM_F1NWPRT_F1NWPRT17                          (0x00020000UL)
#define EFM_F1NWPRT_F1NWPRT18_POS                      (18U)
#define EFM_F1NWPRT_F1NWPRT18                          (0x00040000UL)
#define EFM_F1NWPRT_F1NWPRT19_POS                      (19U)
#define EFM_F1NWPRT_F1NWPRT19                          (0x00080000UL)
#define EFM_F1NWPRT_F1NWPRT20_POS                      (20U)
#define EFM_F1NWPRT_F1NWPRT20                          (0x00100000UL)
#define EFM_F1NWPRT_F1NWPRT21_POS                      (21U)
#define EFM_F1NWPRT_F1NWPRT21                          (0x00200000UL)
#define EFM_F1NWPRT_F1NWPRT22_POS                      (22U)
#define EFM_F1NWPRT_F1NWPRT22                          (0x00400000UL)
#define EFM_F1NWPRT_F1NWPRT23_POS                      (23U)
#define EFM_F1NWPRT_F1NWPRT23                          (0x00800000UL)
#define EFM_F1NWPRT_F1NWPRT24_POS                      (24U)
#define EFM_F1NWPRT_F1NWPRT24                          (0x01000000UL)
#define EFM_F1NWPRT_F1NWPRT25_POS                      (25U)
#define EFM_F1NWPRT_F1NWPRT25                          (0x02000000UL)
#define EFM_F1NWPRT_F1NWPRT26_POS                      (26U)
#define EFM_F1NWPRT_F1NWPRT26                          (0x04000000UL)
#define EFM_F1NWPRT_F1NWPRT27_POS                      (27U)
#define EFM_F1NWPRT_F1NWPRT27                          (0x08000000UL)
#define EFM_F1NWPRT_F1NWPRT28_POS                      (28U)
#define EFM_F1NWPRT_F1NWPRT28                          (0x10000000UL)
#define EFM_F1NWPRT_F1NWPRT29_POS                      (29U)
#define EFM_F1NWPRT_F1NWPRT29                          (0x20000000UL)
#define EFM_F1NWPRT_F1NWPRT30_POS                      (30U)
#define EFM_F1NWPRT_F1NWPRT30                          (0x40000000UL)
#define EFM_F1NWPRT_F1NWPRT31_POS                      (31U)
#define EFM_F1NWPRT_F1NWPRT31                          (0x80000000UL)

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
#define EMB_CTL1_SYSEN_POS                             (4U)
#define EMB_CTL1_SYSEN                                 (0x00000010UL)
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
#define EMB_CTL1_PWMSEN8_POS                           (13U)
#define EMB_CTL1_PWMSEN8                               (0x00002000UL)
#define EMB_CTL1_PWMSEN9_POS                           (14U)
#define EMB_CTL1_PWMSEN9                               (0x00004000UL)
#define EMB_CTL1_PORTINEN1_POS                         (16U)
#define EMB_CTL1_PORTINEN1                             (0x00010000UL)
#define EMB_CTL1_PORTINEN2_POS                         (17U)
#define EMB_CTL1_PORTINEN2                             (0x00020000UL)
#define EMB_CTL1_PORTINEN3_POS                         (18U)
#define EMB_CTL1_PORTINEN3                             (0x00040000UL)
#define EMB_CTL1_PORTINEN4_POS                         (19U)
#define EMB_CTL1_PORTINEN4                             (0x00080000UL)
#define EMB_CTL1_PORTINEN5_POS                         (20U)
#define EMB_CTL1_PORTINEN5                             (0x00100000UL)
#define EMB_CTL1_INVSEL1_POS                           (22U)
#define EMB_CTL1_INVSEL1                               (0x00400000UL)
#define EMB_CTL1_INVSEL2_POS                           (23U)
#define EMB_CTL1_INVSEL2                               (0x00800000UL)
#define EMB_CTL1_INVSEL3_POS                           (24U)
#define EMB_CTL1_INVSEL3                               (0x01000000UL)
#define EMB_CTL1_INVSEL4_POS                           (25U)
#define EMB_CTL1_INVSEL4                               (0x02000000UL)
#define EMB_CTL1_INVSEL5_POS                           (26U)
#define EMB_CTL1_INVSEL5                               (0x04000000UL)
#define EMB_CTL1_OSCSTPEN_POS                          (27U)
#define EMB_CTL1_OSCSTPEN                              (0x08000000UL)
#define EMB_CTL1_SRAMERREN_POS                         (28U)
#define EMB_CTL1_SRAMERREN                             (0x10000000UL)
#define EMB_CTL1_SRAMPYERREN_POS                       (29U)
#define EMB_CTL1_SRAMPYERREN                           (0x20000000UL)
#define EMB_CTL1_LOCKUPEN_POS                          (30U)
#define EMB_CTL1_LOCKUPEN                              (0x40000000UL)
#define EMB_CTL1_PVDEN_POS                             (31U)
#define EMB_CTL1_PVDEN                                 (0x80000000UL)

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
#define EMB_CTL2_PWMLV8_POS                            (8U)
#define EMB_CTL2_PWMLV8                                (0x00000100UL)
#define EMB_CTL2_PWMLV9_POS                            (9U)
#define EMB_CTL2_PWMLV9                                (0x00000200UL)
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
#define EMB_CTL2_NFSEL5_POS                            (28U)
#define EMB_CTL2_NFSEL5                                (0x30000000UL)
#define EMB_CTL2_NFEN5_POS                             (30U)
#define EMB_CTL2_NFEN5                                 (0x40000000UL)

/*  Bit definition for EMB_SOE register  */
#define EMB_SOE_SOE                                    (0x00000001UL)

/*  Bit definition for EMB_STAT register  */
#define EMB_STAT_PWMSF_POS                             (1U)
#define EMB_STAT_PWMSF                                 (0x00000002UL)
#define EMB_STAT_CMPF_POS                              (2U)
#define EMB_STAT_CMPF                                  (0x00000004UL)
#define EMB_STAT_SYSF_POS                              (3U)
#define EMB_STAT_SYSF                                  (0x00000008UL)
#define EMB_STAT_PWMST_POS                             (5U)
#define EMB_STAT_PWMST                                 (0x00000020UL)
#define EMB_STAT_CMPST_POS                             (6U)
#define EMB_STAT_CMPST                                 (0x00000040UL)
#define EMB_STAT_SYSST_POS                             (7U)
#define EMB_STAT_SYSST                                 (0x00000080UL)
#define EMB_STAT_PORTINF1_POS                          (8U)
#define EMB_STAT_PORTINF1                              (0x00000100UL)
#define EMB_STAT_PORTINF2_POS                          (9U)
#define EMB_STAT_PORTINF2                              (0x00000200UL)
#define EMB_STAT_PORTINF3_POS                          (10U)
#define EMB_STAT_PORTINF3                              (0x00000400UL)
#define EMB_STAT_PORTINF4_POS                          (11U)
#define EMB_STAT_PORTINF4                              (0x00000800UL)
#define EMB_STAT_PORTINF5_POS                          (12U)
#define EMB_STAT_PORTINF5                              (0x00001000UL)
#define EMB_STAT_PORTINST1_POS                         (14U)
#define EMB_STAT_PORTINST1                             (0x00004000UL)
#define EMB_STAT_PORTINST2_POS                         (15U)
#define EMB_STAT_PORTINST2                             (0x00008000UL)
#define EMB_STAT_PORTINST3_POS                         (16U)
#define EMB_STAT_PORTINST3                             (0x00010000UL)
#define EMB_STAT_PORTINST4_POS                         (17U)
#define EMB_STAT_PORTINST4                             (0x00020000UL)
#define EMB_STAT_PORTINST5_POS                         (18U)
#define EMB_STAT_PORTINST5                             (0x00040000UL)

/*  Bit definition for EMB_STATCLR register  */
#define EMB_STATCLR_PWMSFCLR_POS                       (1U)
#define EMB_STATCLR_PWMSFCLR                           (0x00000002UL)
#define EMB_STATCLR_CMPFCLR_POS                        (2U)
#define EMB_STATCLR_CMPFCLR                            (0x00000004UL)
#define EMB_STATCLR_SYSFCLR_POS                        (3U)
#define EMB_STATCLR_SYSFCLR                            (0x00000008UL)
#define EMB_STATCLR_PORTINFCLR1_POS                    (8U)
#define EMB_STATCLR_PORTINFCLR1                        (0x00000100UL)
#define EMB_STATCLR_PORTINFCLR2_POS                    (9U)
#define EMB_STATCLR_PORTINFCLR2                        (0x00000200UL)
#define EMB_STATCLR_PORTINFCLR3_POS                    (10U)
#define EMB_STATCLR_PORTINFCLR3                        (0x00000400UL)
#define EMB_STATCLR_PORTINFCLR4_POS                    (11U)
#define EMB_STATCLR_PORTINFCLR4                        (0x00000800UL)
#define EMB_STATCLR_PORTINFCLR5_POS                    (12U)
#define EMB_STATCLR_PORTINFCLR5                        (0x00001000UL)

/*  Bit definition for EMB_INTEN register  */
#define EMB_INTEN_PWMSINTEN_POS                        (1U)
#define EMB_INTEN_PWMSINTEN                            (0x00000002UL)
#define EMB_INTEN_CMPINTEN_POS                         (2U)
#define EMB_INTEN_CMPINTEN                             (0x00000004UL)
#define EMB_INTEN_SYSINTEN_POS                         (3U)
#define EMB_INTEN_SYSINTEN                             (0x00000008UL)
#define EMB_INTEN_PORTININTEN1_POS                     (8U)
#define EMB_INTEN_PORTININTEN1                         (0x00000100UL)
#define EMB_INTEN_PORTININTEN2_POS                     (9U)
#define EMB_INTEN_PORTININTEN2                         (0x00000200UL)
#define EMB_INTEN_PORTININTEN3_POS                     (10U)
#define EMB_INTEN_PORTININTEN3                         (0x00000400UL)
#define EMB_INTEN_PORTININTEN4_POS                     (11U)
#define EMB_INTEN_PORTININTEN4                         (0x00000800UL)
#define EMB_INTEN_PORTININTEN5_POS                     (12U)
#define EMB_INTEN_PORTININTEN5                         (0x00001000UL)

/*  Bit definition for EMB_RLSSEL register  */
#define EMB_RLSSEL_PWMRSEL_POS                         (1U)
#define EMB_RLSSEL_PWMRSEL                             (0x00000002UL)
#define EMB_RLSSEL_CMPRSEL_POS                         (2U)
#define EMB_RLSSEL_CMPRSEL                             (0x00000004UL)
#define EMB_RLSSEL_SYSRSEL_POS                         (3U)
#define EMB_RLSSEL_SYSRSEL                             (0x00000008UL)
#define EMB_RLSSEL_PORTINRSEL1_POS                     (8U)
#define EMB_RLSSEL_PORTINRSEL1                         (0x00000100UL)
#define EMB_RLSSEL_PORTINRSEL2_POS                     (9U)
#define EMB_RLSSEL_PORTINRSEL2                         (0x00000200UL)
#define EMB_RLSSEL_PORTINRSEL3_POS                     (10U)
#define EMB_RLSSEL_PORTINRSEL3                         (0x00000400UL)
#define EMB_RLSSEL_PORTINRSEL4_POS                     (11U)
#define EMB_RLSSEL_PORTINRSEL4                         (0x00000800UL)
#define EMB_RLSSEL_PORTINRSEL5_POS                     (12U)
#define EMB_RLSSEL_PORTINRSEL5                         (0x00001000UL)

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

/*  Bit definition for FMAC_COR0 register  */
#define FMAC_COR0_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR1 register  */
#define FMAC_COR1_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR2 register  */
#define FMAC_COR2_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR3 register  */
#define FMAC_COR3_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR4 register  */
#define FMAC_COR4_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR5 register  */
#define FMAC_COR5_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR6 register  */
#define FMAC_COR6_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR7 register  */
#define FMAC_COR7_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR8 register  */
#define FMAC_COR8_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR9 register  */
#define FMAC_COR9_CIN                                  (0x0000FFFFUL)

/*  Bit definition for FMAC_COR10 register  */
#define FMAC_COR10_CIN                                 (0x0000FFFFUL)

/*  Bit definition for FMAC_COR11 register  */
#define FMAC_COR11_CIN                                 (0x0000FFFFUL)

/*  Bit definition for FMAC_COR12 register  */
#define FMAC_COR12_CIN                                 (0x0000FFFFUL)

/*  Bit definition for FMAC_COR13 register  */
#define FMAC_COR13_CIN                                 (0x0000FFFFUL)

/*  Bit definition for FMAC_COR14 register  */
#define FMAC_COR14_CIN                                 (0x0000FFFFUL)

/*  Bit definition for FMAC_COR15 register  */
#define FMAC_COR15_CIN                                 (0x0000FFFFUL)

/*  Bit definition for FMAC_COR16 register  */
#define FMAC_COR16_CIN                                 (0x0000FFFFUL)

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
#define GPIO_PCR_PUD_POS                               (7U)
#define GPIO_PCR_PUD                                   (0x0080U)
#define GPIO_PCR_PIN_POS                               (8U)
#define GPIO_PCR_PIN                                   (0x0100U)
#define GPIO_PCR_INVE_POS                              (9U)
#define GPIO_PCR_INVE                                  (0x0200U)
#define GPIO_PCR_CINSEL_POS                            (10U)
#define GPIO_PCR_CINSEL                                (0x0400U)
#define GPIO_PCR_INTE_POS                              (12U)
#define GPIO_PCR_INTE                                  (0x1000U)
#define GPIO_PCR_PINAE_POS                             (13U)
#define GPIO_PCR_PINAE                                 (0x2000U)
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
#define I2C_CR2_RFREQIE_POS                            (11U)
#define I2C_CR2_RFREQIE                                (0x00000800UL)
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
#define I2C_CR4_BUSFREECLREN_POS                       (12U)
#define I2C_CR4_BUSFREECLREN                           (0x00001000UL)

/*  Bit definition for I2C_SLR0 register  */
#define I2C_SLR0_SLADDR0_POS                           (0U)
#define I2C_SLR0_SLADDR0                               (0x000003FFUL)
#define I2C_SLR0_SLADDR0EN_POS                         (12U)
#define I2C_SLR0_SLADDR0EN                             (0x00001000UL)
#define I2C_SLR0_ADDRMOD0_POS                          (15U)
#define I2C_SLR0_ADDRMOD0                              (0x00008000UL)
#define I2C_SLR0_MSLADDR0_POS                          (16U)
#define I2C_SLR0_MSLADDR0                              (0x03FF0000UL)
#define I2C_SLR0_MASKEN0_POS                           (26U)
#define I2C_SLR0_MASKEN0                               (0x04000000UL)

/*  Bit definition for I2C_SLR1 register  */
#define I2C_SLR1_SLADDR1_POS                           (0U)
#define I2C_SLR1_SLADDR1                               (0x000003FFUL)
#define I2C_SLR1_SLADDR1EN_POS                         (12U)
#define I2C_SLR1_SLADDR1EN                             (0x00001000UL)
#define I2C_SLR1_ADDRMOD1_POS                          (15U)
#define I2C_SLR1_ADDRMOD1                              (0x00008000UL)
#define I2C_SLR1_MSLADDR1_POS                          (16U)
#define I2C_SLR1_MSLADDR1                              (0x03FF0000UL)
#define I2C_SLR1_MASKEN1_POS                           (26U)
#define I2C_SLR1_MASKEN1                               (0x04000000UL)

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
#define I2C_SR_TFEMPTY_POS                             (24U)
#define I2C_SR_TFEMPTY                                 (0x01000000UL)
#define I2C_SR_TFFULL_POS                              (25U)
#define I2C_SR_TFFULL                                  (0x02000000UL)
#define I2C_SR_RFEMPTY_POS                             (26U)
#define I2C_SR_RFEMPTY                                 (0x04000000UL)
#define I2C_SR_RFFULL_POS                              (27U)
#define I2C_SR_RFFULL                                  (0x08000000UL)
#define I2C_SR_TFST_POS                                (28U)
#define I2C_SR_TFST                                    (0x30000000UL)
#define I2C_SR_TFST_0                                  (0x10000000UL)
#define I2C_SR_TFST_1                                  (0x20000000UL)
#define I2C_SR_RFREQ_POS                               (31U)
#define I2C_SR_RFREQ                                   (0x80000000UL)

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
#define I2C_CLR_ARLOFCLR_POS                           (9U)
#define I2C_CLR_ARLOFCLR                               (0x00000200UL)
#define I2C_CLR_RFREQCLR_POS                           (10U)
#define I2C_CLR_RFREQCLR                               (0x00000400UL)
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
#define I2C_CCR_SLOWW                                  (0x000000FFUL)
#define I2C_CCR_SHIGHW_POS                             (8U)
#define I2C_CCR_SHIGHW                                 (0x0000FF00UL)
#define I2C_CCR_FREQ_POS                               (16U)
#define I2C_CCR_FREQ                                   (0x00070000UL)
#define I2C_CCR_FMPLUSEN_POS                           (23U)
#define I2C_CCR_FMPLUSEN                               (0x00800000UL)

/*  Bit definition for I2C_FLTR register  */
#define I2C_FLTR_DNF_POS                               (0U)
#define I2C_FLTR_DNF                                   (0x00000003UL)
#define I2C_FLTR_DNFEN_POS                             (4U)
#define I2C_FLTR_DNFEN                                 (0x00000010UL)
#define I2C_FLTR_ANFEN_POS                             (5U)
#define I2C_FLTR_ANFEN                                 (0x00000020UL)

/*  Bit definition for I2C_FSTR register  */
#define I2C_FSTR_FEN_POS                               (0U)
#define I2C_FSTR_FEN                                   (0x00000001UL)
#define I2C_FSTR_TFFLUSH_POS                           (1U)
#define I2C_FSTR_TFFLUSH                               (0x00000002UL)
#define I2C_FSTR_RFFLUSH_POS                           (2U)
#define I2C_FSTR_RFFLUSH                               (0x00000004UL)
#define I2C_FSTR_NACKTFFLUSH_POS                       (3U)
#define I2C_FSTR_NACKTFFLUSH                           (0x00000008UL)
#define I2C_FSTR_TFST_POS                              (4U)
#define I2C_FSTR_TFST                                  (0x00000030UL)
#define I2C_FSTR_TFST_0                                (0x00000010UL)
#define I2C_FSTR_TFST_1                                (0x00000020UL)
#define I2C_FSTR_RFST_POS                              (6U)
#define I2C_FSTR_RFST                                  (0x000000C0UL)
#define I2C_FSTR_RFST_0                                (0x00000040UL)
#define I2C_FSTR_RFST_1                                (0x00000080UL)

/*  Bit definition for I2C_SLVADDR register  */
#define I2C_SLVADDR_SLVADRR                            (0x000003FFUL)

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
#define ICG_ICG0_SWDTWDPT_POS                          (8U)
#define ICG_ICG0_SWDTWDPT                              (0x00000F00UL)
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
#define ICG_ICG0_WDTWDPT_POS                           (24U)
#define ICG_ICG0_WDTWDPT                               (0x0F000000UL)
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

/*  Bit definition for ICG_ICG4 register  */
#define ICG_ICG4                                       (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral INTC
*******************************************************************************/
/*  Bit definition for INTC_NMIER register  */
#define INTC_NMIER_SWDTEN_POS                          (1U)
#define INTC_NMIER_SWDTEN                              (0x00000002UL)
#define INTC_NMIER_PVD1EN_POS                          (2U)
#define INTC_NMIER_PVD1EN                              (0x00000004UL)
#define INTC_NMIER_PVD2EN_POS                          (3U)
#define INTC_NMIER_PVD2EN                              (0x00000008UL)
#define INTC_NMIER_XTALSTPEN_POS                       (5U)
#define INTC_NMIER_XTALSTPEN                           (0x00000020UL)
#define INTC_NMIER_RPARERREN_POS                       (8U)
#define INTC_NMIER_RPARERREN                           (0x00000100UL)
#define INTC_NMIER_RECCERREN_POS                       (9U)
#define INTC_NMIER_RECCERREN                           (0x00000200UL)
#define INTC_NMIER_BUSERREN_POS                        (10U)
#define INTC_NMIER_BUSERREN                            (0x00000400UL)
#define INTC_NMIER_WDTEN_POS                           (11U)
#define INTC_NMIER_WDTEN                               (0x00000800UL)

/*  Bit definition for INTC_NMIFR register  */
#define INTC_NMIFR_SWDTF_POS                           (1U)
#define INTC_NMIFR_SWDTF                               (0x00000002UL)
#define INTC_NMIFR_PVD1F_POS                           (2U)
#define INTC_NMIFR_PVD1F                               (0x00000004UL)
#define INTC_NMIFR_PVD2F_POS                           (3U)
#define INTC_NMIFR_PVD2F                               (0x00000008UL)
#define INTC_NMIFR_XTALSTPF_POS                        (5U)
#define INTC_NMIFR_XTALSTPF                            (0x00000020UL)
#define INTC_NMIFR_RPARERRF_POS                        (8U)
#define INTC_NMIFR_RPARERRF                            (0x00000100UL)
#define INTC_NMIFR_RECCERRF_POS                        (9U)
#define INTC_NMIFR_RECCERRF                            (0x00000200UL)
#define INTC_NMIFR_BUSERRF_POS                         (10U)
#define INTC_NMIFR_BUSERRF                             (0x00000400UL)
#define INTC_NMIFR_WDTF_POS                            (11U)
#define INTC_NMIFR_WDTF                                (0x00000800UL)

/*  Bit definition for INTC_NMIFCR register  */
#define INTC_NMIFCR_SWDTFCLR_POS                       (1U)
#define INTC_NMIFCR_SWDTFCLR                           (0x00000002UL)
#define INTC_NMIFCR_PVD1FCLR_POS                       (2U)
#define INTC_NMIFCR_PVD1FCLR                           (0x00000004UL)
#define INTC_NMIFCR_PVD2FCLR_POS                       (3U)
#define INTC_NMIFCR_PVD2FCLR                           (0x00000008UL)
#define INTC_NMIFCR_XTALSTPFCLR_POS                    (5U)
#define INTC_NMIFCR_XTALSTPFCLR                        (0x00000020UL)
#define INTC_NMIFCR_RPARERRFCLR_POS                    (8U)
#define INTC_NMIFCR_RPARERRFCLR                        (0x00000100UL)
#define INTC_NMIFCR_RECCERRFCLR_POS                    (9U)
#define INTC_NMIFCR_RECCERRFCLR                        (0x00000200UL)
#define INTC_NMIFCR_BUSERRFCLR_POS                     (10U)
#define INTC_NMIFCR_BUSERRFCLR                         (0x00000400UL)
#define INTC_NMIFCR_WDTFCLR_POS                        (11U)
#define INTC_NMIFCR_WDTFCLR                            (0x00000800UL)

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
#define INTC_EIRQCR_NOCSEL_POS                         (12U)
#define INTC_EIRQCR_NOCSEL                             (0x00003000UL)
#define INTC_EIRQCR_NOCSEL_0                           (0x00001000UL)
#define INTC_EIRQCR_NOCSEL_1                           (0x00002000UL)
#define INTC_EIRQCR_NOCEN_POS                          (15U)
#define INTC_EIRQCR_NOCEN                              (0x00008000UL)

/*  Bit definition for INTC_WKEN register  */
#define INTC_WKEN_EIRQWKEN_POS                         (0U)
#define INTC_WKEN_EIRQWKEN                             (0x0000FFFFUL)
#define INTC_WKEN_EIRQWKEN_0                           (0x00000001UL)
#define INTC_WKEN_EIRQWKEN_1                           (0x00000002UL)
#define INTC_WKEN_EIRQWKEN_2                           (0x00000004UL)
#define INTC_WKEN_EIRQWKEN_3                           (0x00000008UL)
#define INTC_WKEN_EIRQWKEN_4                           (0x00000010UL)
#define INTC_WKEN_EIRQWKEN_5                           (0x00000020UL)
#define INTC_WKEN_EIRQWKEN_6                           (0x00000040UL)
#define INTC_WKEN_EIRQWKEN_7                           (0x00000080UL)
#define INTC_WKEN_EIRQWKEN_8                           (0x00000100UL)
#define INTC_WKEN_EIRQWKEN_9                           (0x00000200UL)
#define INTC_WKEN_EIRQWKEN_10                          (0x00000400UL)
#define INTC_WKEN_EIRQWKEN_11                          (0x00000800UL)
#define INTC_WKEN_EIRQWKEN_12                          (0x00001000UL)
#define INTC_WKEN_EIRQWKEN_13                          (0x00002000UL)
#define INTC_WKEN_EIRQWKEN_14                          (0x00004000UL)
#define INTC_WKEN_EIRQWKEN_15                          (0x00008000UL)
#define INTC_WKEN_SWDTWKEN_POS                         (16U)
#define INTC_WKEN_SWDTWKEN                             (0x00010000UL)
#define INTC_WKEN_PVD1WKEN_POS                         (17U)
#define INTC_WKEN_PVD1WKEN                             (0x00020000UL)
#define INTC_WKEN_PVD2WKEN_POS                         (18U)
#define INTC_WKEN_PVD2WKEN                             (0x00040000UL)
#define INTC_WKEN_CMP1WKEN_POS                         (19U)
#define INTC_WKEN_CMP1WKEN                             (0x00080000UL)
#define INTC_WKEN_WKTMWKEN_POS                         (20U)
#define INTC_WKEN_WKTMWKEN                             (0x00100000UL)
#define INTC_WKEN_RTCALMWKEN_POS                       (21U)
#define INTC_WKEN_RTCALMWKEN                           (0x00200000UL)
#define INTC_WKEN_RTCPRDWKEN_POS                       (22U)
#define INTC_WKEN_RTCPRDWKEN                           (0x00400000UL)
#define INTC_WKEN_TMR0CMPWKEN_POS                      (23U)
#define INTC_WKEN_TMR0CMPWKEN                          (0x00800000UL)
#define INTC_WKEN_TMR2CMPWKEN_POS                      (24U)
#define INTC_WKEN_TMR2CMPWKEN                          (0x01000000UL)
#define INTC_WKEN_TMR2OVFWKEN_POS                      (25U)
#define INTC_WKEN_TMR2OVFWKEN                          (0x02000000UL)
#define INTC_WKEN_RXWKEN_POS                           (26U)
#define INTC_WKEN_RXWKEN                               (0x04000000UL)
#define INTC_WKEN_USFWKEN_POS                          (28U)
#define INTC_WKEN_USFWKEN                              (0x10000000UL)
#define INTC_WKEN_CMP2WKEN_POS                         (29U)
#define INTC_WKEN_CMP2WKEN                             (0x20000000UL)
#define INTC_WKEN_CMP3WKEN_POS                         (30U)
#define INTC_WKEN_CMP3WKEN                             (0x40000000UL)
#define INTC_WKEN_CMP4WKEN_POS                         (31U)
#define INTC_WKEN_CMP4WKEN                             (0x80000000UL)

/*  Bit definition for INTC_EIFR register  */
#define INTC_EIFR_EIF0_POS                             (0U)
#define INTC_EIFR_EIF0                                 (0x00000001UL)
#define INTC_EIFR_EIF1_POS                             (1U)
#define INTC_EIFR_EIF1                                 (0x00000002UL)
#define INTC_EIFR_EIF2_POS                             (2U)
#define INTC_EIFR_EIF2                                 (0x00000004UL)
#define INTC_EIFR_EIF3_POS                             (3U)
#define INTC_EIFR_EIF3                                 (0x00000008UL)
#define INTC_EIFR_EIF4_POS                             (4U)
#define INTC_EIFR_EIF4                                 (0x00000010UL)
#define INTC_EIFR_EIF5_POS                             (5U)
#define INTC_EIFR_EIF5                                 (0x00000020UL)
#define INTC_EIFR_EIF6_POS                             (6U)
#define INTC_EIFR_EIF6                                 (0x00000040UL)
#define INTC_EIFR_EIF7_POS                             (7U)
#define INTC_EIFR_EIF7                                 (0x00000080UL)
#define INTC_EIFR_EIF8_POS                             (8U)
#define INTC_EIFR_EIF8                                 (0x00000100UL)
#define INTC_EIFR_EIF9_POS                             (9U)
#define INTC_EIFR_EIF9                                 (0x00000200UL)
#define INTC_EIFR_EIF10_POS                            (10U)
#define INTC_EIFR_EIF10                                (0x00000400UL)
#define INTC_EIFR_EIF11_POS                            (11U)
#define INTC_EIFR_EIF11                                (0x00000800UL)
#define INTC_EIFR_EIF12_POS                            (12U)
#define INTC_EIFR_EIF12                                (0x00001000UL)
#define INTC_EIFR_EIF13_POS                            (13U)
#define INTC_EIFR_EIF13                                (0x00002000UL)
#define INTC_EIFR_EIF14_POS                            (14U)
#define INTC_EIFR_EIF14                                (0x00004000UL)
#define INTC_EIFR_EIF15_POS                            (15U)
#define INTC_EIFR_EIF15                                (0x00008000UL)

/*  Bit definition for INTC_EIFCR register  */
#define INTC_EIFCR_EIFCLR0_POS                         (0U)
#define INTC_EIFCR_EIFCLR0                             (0x00000001UL)
#define INTC_EIFCR_EIFCLR1_POS                         (1U)
#define INTC_EIFCR_EIFCLR1                             (0x00000002UL)
#define INTC_EIFCR_EIFCLR2_POS                         (2U)
#define INTC_EIFCR_EIFCLR2                             (0x00000004UL)
#define INTC_EIFCR_EIFCLR3_POS                         (3U)
#define INTC_EIFCR_EIFCLR3                             (0x00000008UL)
#define INTC_EIFCR_EIFCLR4_POS                         (4U)
#define INTC_EIFCR_EIFCLR4                             (0x00000010UL)
#define INTC_EIFCR_EIFCLR5_POS                         (5U)
#define INTC_EIFCR_EIFCLR5                             (0x00000020UL)
#define INTC_EIFCR_EIFCLR6_POS                         (6U)
#define INTC_EIFCR_EIFCLR6                             (0x00000040UL)
#define INTC_EIFCR_EIFCLR7_POS                         (7U)
#define INTC_EIFCR_EIFCLR7                             (0x00000080UL)
#define INTC_EIFCR_EIFCLR8_POS                         (8U)
#define INTC_EIFCR_EIFCLR8                             (0x00000100UL)
#define INTC_EIFCR_EIFCLR9_POS                         (9U)
#define INTC_EIFCR_EIFCLR9                             (0x00000200UL)
#define INTC_EIFCR_EIFCLR10_POS                        (10U)
#define INTC_EIFCR_EIFCLR10                            (0x00000400UL)
#define INTC_EIFCR_EIFCLR11_POS                        (11U)
#define INTC_EIFCR_EIFCLR11                            (0x00000800UL)
#define INTC_EIFCR_EIFCLR12_POS                        (12U)
#define INTC_EIFCR_EIFCLR12                            (0x00001000UL)
#define INTC_EIFCR_EIFCLR13_POS                        (13U)
#define INTC_EIFCR_EIFCLR13                            (0x00002000UL)
#define INTC_EIFCR_EIFCLR14_POS                        (14U)
#define INTC_EIFCR_EIFCLR14                            (0x00004000UL)
#define INTC_EIFCR_EIFCLR15_POS                        (15U)
#define INTC_EIFCR_EIFCLR15                            (0x00008000UL)

/*  Bit definition for INTC_INTSEL register  */
#define INTC_INTSEL_INTSEL                             (0x000001FFUL)

/*  Bit definition for INTC_INTEN register  */
#define INTC_INTEN_INTEN                               (0xFFFFFFFFUL)
#define INTC_INTEN_INTEN_0                             (0x00000001UL)
#define INTC_INTEN_INTEN_1                             (0x00000002UL)
#define INTC_INTEN_INTEN_2                             (0x00000004UL)
#define INTC_INTEN_INTEN_3                             (0x00000008UL)
#define INTC_INTEN_INTEN_4                             (0x00000010UL)
#define INTC_INTEN_INTEN_5                             (0x00000020UL)
#define INTC_INTEN_INTEN_6                             (0x00000040UL)
#define INTC_INTEN_INTEN_7                             (0x00000080UL)
#define INTC_INTEN_INTEN_8                             (0x00000100UL)
#define INTC_INTEN_INTEN_9                             (0x00000200UL)
#define INTC_INTEN_INTEN_10                            (0x00000400UL)
#define INTC_INTEN_INTEN_11                            (0x00000800UL)
#define INTC_INTEN_INTEN_12                            (0x00001000UL)
#define INTC_INTEN_INTEN_13                            (0x00002000UL)
#define INTC_INTEN_INTEN_14                            (0x00004000UL)
#define INTC_INTEN_INTEN_15                            (0x00008000UL)
#define INTC_INTEN_INTEN_16                            (0x00010000UL)
#define INTC_INTEN_INTEN_17                            (0x00020000UL)
#define INTC_INTEN_INTEN_18                            (0x00040000UL)
#define INTC_INTEN_INTEN_19                            (0x00080000UL)
#define INTC_INTEN_INTEN_20                            (0x00100000UL)
#define INTC_INTEN_INTEN_21                            (0x00200000UL)
#define INTC_INTEN_INTEN_22                            (0x00400000UL)
#define INTC_INTEN_INTEN_23                            (0x00800000UL)
#define INTC_INTEN_INTEN_24                            (0x01000000UL)
#define INTC_INTEN_INTEN_25                            (0x02000000UL)
#define INTC_INTEN_INTEN_26                            (0x04000000UL)
#define INTC_INTEN_INTEN_27                            (0x08000000UL)
#define INTC_INTEN_INTEN_28                            (0x10000000UL)
#define INTC_INTEN_INTEN_29                            (0x20000000UL)
#define INTC_INTEN_INTEN_30                            (0x40000000UL)
#define INTC_INTEN_INTEN_31                            (0x80000000UL)

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
#define INTC_IER_IEN0_POS                              (0U)
#define INTC_IER_IEN0                                  (0x00000001UL)
#define INTC_IER_IEN1_POS                              (1U)
#define INTC_IER_IEN1                                  (0x00000002UL)
#define INTC_IER_IEN2_POS                              (2U)
#define INTC_IER_IEN2                                  (0x00000004UL)
#define INTC_IER_IEN3_POS                              (3U)
#define INTC_IER_IEN3                                  (0x00000008UL)
#define INTC_IER_IEN4_POS                              (4U)
#define INTC_IER_IEN4                                  (0x00000010UL)
#define INTC_IER_IEN5_POS                              (5U)
#define INTC_IER_IEN5                                  (0x00000020UL)
#define INTC_IER_IEN6_POS                              (6U)
#define INTC_IER_IEN6                                  (0x00000040UL)
#define INTC_IER_IEN7_POS                              (7U)
#define INTC_IER_IEN7                                  (0x00000080UL)
#define INTC_IER_IEN8_POS                              (8U)
#define INTC_IER_IEN8                                  (0x00000100UL)
#define INTC_IER_IEN9_POS                              (9U)
#define INTC_IER_IEN9                                  (0x00000200UL)
#define INTC_IER_IEN10_POS                             (10U)
#define INTC_IER_IEN10                                 (0x00000400UL)
#define INTC_IER_IEN11_POS                             (11U)
#define INTC_IER_IEN11                                 (0x00000800UL)
#define INTC_IER_IEN12_POS                             (12U)
#define INTC_IER_IEN12                                 (0x00001000UL)
#define INTC_IER_IEN13_POS                             (13U)
#define INTC_IER_IEN13                                 (0x00002000UL)
#define INTC_IER_IEN14_POS                             (14U)
#define INTC_IER_IEN14                                 (0x00004000UL)
#define INTC_IER_IEN15_POS                             (15U)
#define INTC_IER_IEN15                                 (0x00008000UL)
#define INTC_IER_IEN16_POS                             (16U)
#define INTC_IER_IEN16                                 (0x00010000UL)
#define INTC_IER_IEN17_POS                             (17U)
#define INTC_IER_IEN17                                 (0x00020000UL)
#define INTC_IER_IEN18_POS                             (18U)
#define INTC_IER_IEN18                                 (0x00040000UL)
#define INTC_IER_IEN19_POS                             (19U)
#define INTC_IER_IEN19                                 (0x00080000UL)
#define INTC_IER_IEN20_POS                             (20U)
#define INTC_IER_IEN20                                 (0x00100000UL)
#define INTC_IER_IEN21_POS                             (21U)
#define INTC_IER_IEN21                                 (0x00200000UL)
#define INTC_IER_IEN22_POS                             (22U)
#define INTC_IER_IEN22                                 (0x00400000UL)
#define INTC_IER_IEN23_POS                             (23U)
#define INTC_IER_IEN23                                 (0x00800000UL)
#define INTC_IER_IEN24_POS                             (24U)
#define INTC_IER_IEN24                                 (0x01000000UL)
#define INTC_IER_IEN25_POS                             (25U)
#define INTC_IER_IEN25                                 (0x02000000UL)
#define INTC_IER_IEN26_POS                             (26U)
#define INTC_IER_IEN26                                 (0x04000000UL)
#define INTC_IER_IEN27_POS                             (27U)
#define INTC_IER_IEN27                                 (0x08000000UL)
#define INTC_IER_IEN28_POS                             (28U)
#define INTC_IER_IEN28                                 (0x10000000UL)
#define INTC_IER_IEN29_POS                             (29U)
#define INTC_IER_IEN29                                 (0x20000000UL)
#define INTC_IER_IEN30_POS                             (30U)
#define INTC_IER_IEN30                                 (0x40000000UL)
#define INTC_IER_IEN31_POS                             (31U)
#define INTC_IER_IEN31                                 (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral KEYSCAN
*******************************************************************************/
/*  Bit definition for KEYSCAN_SCR register  */
#define KEYSCAN_SCR_KEYINSEL_POS                       (0U)
#define KEYSCAN_SCR_KEYINSEL                           (0x0000FFFFUL)
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
                Bit definition for Peripheral MDIO
*******************************************************************************/
/*  Bit definition for MDIO_MDCON register  */
#define MDIO_MDCON_MD_RST_POS                          (0U)
#define MDIO_MDCON_MD_RST                              (0x00000001UL)
#define MDIO_MDCON_MD_PHYB_POS                         (1U)
#define MDIO_MDCON_MD_PHYB                             (0x00000002UL)

/*  Bit definition for MDIO_MDCON1 register  */
#define MDIO_MDCON1_MD_MSDEV_POS                       (0U)
#define MDIO_MDCON1_MD_MSDEV                           (0x00000001UL)
#define MDIO_MDCON1_SEL_EDGE_POS                       (2U)
#define MDIO_MDCON1_SEL_EDGE                           (0x00000004UL)
#define MDIO_MDCON1_MD_EN_POS                          (3U)
#define MDIO_MDCON1_MD_EN                              (0x00000008UL)

/*  Bit definition for MDIO_MDFRM register  */
#define MDIO_MDFRM_MD_ROP_POS                          (0U)
#define MDIO_MDFRM_MD_ROP                              (0x00000003UL)
#define MDIO_MDFRM_MD_ROP_0                            (0x00000001UL)
#define MDIO_MDFRM_MD_ROP_1                            (0x00000002UL)
#define MDIO_MDFRM_MD_RPHYAD_POS                       (2U)
#define MDIO_MDFRM_MD_RPHYAD                           (0x0000007CUL)
#define MDIO_MDFRM_MD_RDEVAD_POS                       (7U)
#define MDIO_MDFRM_MD_RDEVAD                           (0x00000F80UL)
#define MDIO_MDFRM_MD_RTA_POS                          (12U)
#define MDIO_MDFRM_MD_RTA                              (0x00003000UL)
#define MDIO_MDFRM_MD_RTA_0                            (0x00001000UL)
#define MDIO_MDFRM_MD_RTA_1                            (0x00002000UL)

/*  Bit definition for MDIO_MDRXD register  */
#define MDIO_MDRXD_MD_RXD                              (0x0000FFFFUL)

/*  Bit definition for MDIO_MDADR register  */
#define MDIO_MDADR_MD_ADR                              (0x0000FFFFUL)

/*  Bit definition for MDIO_MDTXD register  */
#define MDIO_MDTXD_MD_TXD                              (0x0000FFFFUL)

/*  Bit definition for MDIO_MDPHY register  */
#define MDIO_MDPHY_MD_PHYSW_POS                        (0U)
#define MDIO_MDPHY_MD_PHYSW                            (0x0000001FUL)
#define MDIO_MDPHY_MD_PHYSEL_POS                       (5U)
#define MDIO_MDPHY_MD_PHYSEL                           (0x000003E0UL)
#define MDIO_MDPHY_MD_DEVADD_POS                       (10U)
#define MDIO_MDPHY_MD_DEVADD                           (0x00007C00UL)

/*  Bit definition for MDIO_MDSTA register  */
#define MDIO_MDSTA_MD_WRF_POS                          (0U)
#define MDIO_MDSTA_MD_WRF                              (0x00000001UL)
#define MDIO_MDSTA_MD_ADRF_POS                         (1U)
#define MDIO_MDSTA_MD_ADRF                             (0x00000002UL)
#define MDIO_MDSTA_MD_INCF_POS                         (2U)
#define MDIO_MDSTA_MD_INCF                             (0x00000004UL)
#define MDIO_MDSTA_MD_RDF_POS                          (3U)
#define MDIO_MDSTA_MD_RDF                              (0x00000008UL)
#define MDIO_MDSTA_MD_DEVM_POS                         (4U)
#define MDIO_MDSTA_MD_DEVM                             (0x00000010UL)
#define MDIO_MDSTA_MD_DEVN_POS                         (5U)
#define MDIO_MDSTA_MD_DEVN                             (0x00000020UL)
#define MDIO_MDSTA_MD_PHYM_POS                         (6U)
#define MDIO_MDSTA_MD_PHYM                             (0x00000040UL)
#define MDIO_MDSTA_MD_PHYN_POS                         (7U)
#define MDIO_MDSTA_MD_PHYN                             (0x00000080UL)
#define MDIO_MDSTA_MD_TANM_POS                         (8U)
#define MDIO_MDSTA_MD_TANM                             (0x00000100UL)
#define MDIO_MDSTA_MD_TO_POS                           (9U)
#define MDIO_MDSTA_MD_TO                               (0x00000200UL)
#define MDIO_MDSTA_MD_UDR_POS                          (10U)
#define MDIO_MDSTA_MD_UDR                              (0x00000400UL)
#define MDIO_MDSTA_MD_OVR_POS                          (11U)
#define MDIO_MDSTA_MD_OVR                              (0x00000800UL)
#define MDIO_MDSTA_MD_RBNE_POS                         (12U)
#define MDIO_MDSTA_MD_RBNE                             (0x00001000UL)
#define MDIO_MDSTA_MD_BUSY_POS                         (16U)
#define MDIO_MDSTA_MD_BUSY                             (0x00010000UL)

/*  Bit definition for MDIO_MDIEN register  */
#define MDIO_MDIEN_MD_WRFIE_POS                        (0U)
#define MDIO_MDIEN_MD_WRFIE                            (0x00000001UL)
#define MDIO_MDIEN_MD_ADRFIE_POS                       (1U)
#define MDIO_MDIEN_MD_ADRFIE                           (0x00000002UL)
#define MDIO_MDIEN_MD_INCFIE_POS                       (2U)
#define MDIO_MDIEN_MD_INCFIE                           (0x00000004UL)
#define MDIO_MDIEN_MD_RDFIE_POS                        (3U)
#define MDIO_MDIEN_MD_RDFIE                            (0x00000008UL)
#define MDIO_MDIEN_MD_DEVMIE_POS                       (4U)
#define MDIO_MDIEN_MD_DEVMIE                           (0x00000010UL)
#define MDIO_MDIEN_MD_DEVNIE_POS                       (5U)
#define MDIO_MDIEN_MD_DEVNIE                           (0x00000020UL)
#define MDIO_MDIEN_MD_PHYMIE_POS                       (6U)
#define MDIO_MDIEN_MD_PHYMIE                           (0x00000040UL)
#define MDIO_MDIEN_MD_PHYNIE_POS                       (7U)
#define MDIO_MDIEN_MD_PHYNIE                           (0x00000080UL)
#define MDIO_MDIEN_MD_TANMIE_POS                       (8U)
#define MDIO_MDIEN_MD_TANMIE                           (0x00000100UL)
#define MDIO_MDIEN_MD_TOIE_POS                         (9U)
#define MDIO_MDIEN_MD_TOIE                             (0x00000200UL)
#define MDIO_MDIEN_MD_UDRIE_POS                        (10U)
#define MDIO_MDIEN_MD_UDRIE                            (0x00000400UL)
#define MDIO_MDIEN_MD_OVRIE_POS                        (11U)
#define MDIO_MDIEN_MD_OVRIE                            (0x00000800UL)
#define MDIO_MDIEN_MD_RBNEIE_POS                       (12U)
#define MDIO_MDIEN_MD_RBNEIE                           (0x00001000UL)

/*  Bit definition for MDIO_MDPIN register  */
#define MDIO_MDPIN_MD_PIN                              (0x0000001FUL)

/*  Bit definition for MDIO_MDTO register  */
#define MDIO_MDTO_TOCNT_POS                            (0U)
#define MDIO_MDTO_TOCNT                                (0x0000FFFFUL)
#define MDIO_MDTO_TOEN_POS                             (16U)
#define MDIO_MDTO_TOEN                                 (0x00010000UL)

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
#define MPU_SR_PSPEF_POS                               (3U)
#define MPU_SR_PSPEF                                   (0x00000008UL)
#define MPU_SR_MSPEF_POS                               (4U)
#define MPU_SR_MSPEF                                   (0x00000010UL)

/*  Bit definition for MPU_ECLR register  */
#define MPU_ECLR_SMPU1ECLR_POS                         (0U)
#define MPU_ECLR_SMPU1ECLR                             (0x00000001UL)
#define MPU_ECLR_SMPU2ECLR_POS                         (1U)
#define MPU_ECLR_SMPU2ECLR                             (0x00000002UL)
#define MPU_ECLR_FMPUECLR_POS                          (2U)
#define MPU_ECLR_FMPUECLR                              (0x00000004UL)
#define MPU_ECLR_PSPECLR_POS                           (3U)
#define MPU_ECLR_PSPECLR                               (0x00000008UL)
#define MPU_ECLR_MSPECLR_POS                           (4U)
#define MPU_ECLR_MSPECLR                               (0x00000010UL)

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

/*  Bit definition for MPU_MSPPBA register  */
#define MPU_MSPPBA_MSPPBA_POS                          (2U)
#define MPU_MSPPBA_MSPPBA                              (0xFFFFFFFCUL)

/*  Bit definition for MPU_MSPPCTL register  */
#define MPU_MSPPCTL_MSPPSIZE_POS                       (2U)
#define MPU_MSPPCTL_MSPPSIZE                           (0x0000FFFCUL)
#define MPU_MSPPCTL_MSPPACT_POS                        (30U)
#define MPU_MSPPCTL_MSPPACT                            (0x40000000UL)
#define MPU_MSPPCTL_MSPPE_POS                          (31U)
#define MPU_MSPPCTL_MSPPE                              (0x80000000UL)

/*  Bit definition for MPU_PSPPBA register  */
#define MPU_PSPPBA_PSPPBA_POS                          (2U)
#define MPU_PSPPBA_PSPPBA                              (0xFFFFFFFCUL)

/*  Bit definition for MPU_PSPPCTL register  */
#define MPU_PSPPCTL_PSPPSIZE_POS                       (2U)
#define MPU_PSPPCTL_PSPPSIZE                           (0x0000FFFCUL)
#define MPU_PSPPCTL_PSPPACT_POS                        (30U)
#define MPU_PSPPCTL_PSPPACT                            (0x40000000UL)
#define MPU_PSPPCTL_PSPPE_POS                          (31U)
#define MPU_PSPPCTL_PSPPE                              (0x80000000UL)

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
#define PERIC_USB_SYCTLREG_USBFS_WKUP_POS              (2U)
#define PERIC_USB_SYCTLREG_USBFS_WKUP                  (0x00000004UL)
#define PERIC_USB_SYCTLREG_USBFS_DMPD_POS              (3U)
#define PERIC_USB_SYCTLREG_USBFS_DMPD                  (0x00000008UL)
#define PERIC_USB_SYCTLREG_USBFS_DPPD_POS              (4U)
#define PERIC_USB_SYCTLREG_USBFS_DPPD                  (0x00000010UL)
#define PERIC_USB_SYCTLREG_USBFS_PDEN_POS              (5U)
#define PERIC_USB_SYCTLREG_USBFS_PDEN                  (0x00000020UL)
#define PERIC_USB_SYCTLREG_USBFS_NFS_POS               (16U)
#define PERIC_USB_SYCTLREG_USBFS_NFS                   (0x00030000UL)
#define PERIC_USB_SYCTLREG_USBFS_NFS_0                 (0x00010000UL)
#define PERIC_USB_SYCTLREG_USBFS_NFS_1                 (0x00020000UL)
#define PERIC_USB_SYCTLREG_USBFS_NFE_POS               (18U)
#define PERIC_USB_SYCTLREG_USBFS_NFE                   (0x00040000UL)

/*  Bit definition for PERIC_SMC_ENAR register  */
#define PERIC_SMC_ENAR_SMCEN_POS                       (1U)
#define PERIC_SMC_ENAR_SMCEN                           (0x00000002UL)

/*  Bit definition for PERIC_CAN_SYCTLREG register  */
#define PERIC_CAN_SYCTLREG_CAN1FDE_POS                 (0U)
#define PERIC_CAN_SYCTLREG_CAN1FDE                     (0x00000001UL)
#define PERIC_CAN_SYCTLREG_CAN2FDE_POS                 (1U)
#define PERIC_CAN_SYCTLREG_CAN2FDE                     (0x00000002UL)
#define PERIC_CAN_SYCTLREG_CAN3FDE_POS                 (2U)
#define PERIC_CAN_SYCTLREG_CAN3FDE                     (0x00000004UL)
#define PERIC_CAN_SYCTLREG_USBFS_NFS_POS               (16U)
#define PERIC_CAN_SYCTLREG_USBFS_NFS                   (0x00030000UL)
#define PERIC_CAN_SYCTLREG_USBFS_NFS_0                 (0x00010000UL)
#define PERIC_CAN_SYCTLREG_USBFS_NFS_1                 (0x00020000UL)
#define PERIC_CAN_SYCTLREG_USBFS_NFE_POS               (18U)
#define PERIC_CAN_SYCTLREG_USBFS_NFE                   (0x00040000UL)

/*  Bit definition for PERIC_USART1_NFC register  */
#define PERIC_USART1_NFC_USASRT1_NFS_POS               (0U)
#define PERIC_USART1_NFC_USASRT1_NFS                   (0x00000003UL)
#define PERIC_USART1_NFC_USASRT1_NFS_0                 (0x00000001UL)
#define PERIC_USART1_NFC_USASRT1_NFS_1                 (0x00000002UL)
#define PERIC_USART1_NFC_USART1_NFE_POS                (2U)
#define PERIC_USART1_NFC_USART1_NFE                    (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral PLA
*******************************************************************************/
/*  Bit definition for PLA_GCTL register  */
#define PLA_GCTL_PLA_EN                                (0x0000FFFFUL)

/*  Bit definition for PLA_STAT register  */
#define PLA_STAT_PLA_OUT                               (0x0000FFFFUL)

/*  Bit definition for PLA_MUXS register  */
#define PLA_MUXS_MUX1_POS                              (0U)
#define PLA_MUXS_MUX1                                  (0x0000000FUL)
#define PLA_MUXS_MUX0_POS                              (4U)
#define PLA_MUXS_MUX0                                  (0x000000F0UL)
#define PLA_MUXS_MUX1_4_POS                            (14U)
#define PLA_MUXS_MUX1_4                                (0x00004000UL)
#define PLA_MUXS_MUX0_4_POS                            (15U)
#define PLA_MUXS_MUX0_4                                (0x00008000UL)

/*  Bit definition for PLA_LUTCTL register  */
#define PLA_LUTCTL_LUTCTL                              (0x000000FFUL)

/*  Bit definition for PLA_CTL register  */
#define PLA_CTL_OEN_POS                                (6U)
#define PLA_CTL_OEN                                    (0x00000040UL)
#define PLA_CTL_OSEL_POS                               (7U)
#define PLA_CTL_OSEL                                   (0x00000080UL)

/*******************************************************************************
                Bit definition for Peripheral PWC
*******************************************************************************/
/*  Bit definition for PWC_FCG0 register  */
#define PWC_FCG0_SRAMH_POS                             (0U)
#define PWC_FCG0_SRAMH                                 (0x00000001UL)
#define PWC_FCG0_SRAM0_POS                             (4U)
#define PWC_FCG0_SRAM0                                 (0x00000010UL)
#define PWC_FCG0_SRAMRET_POS                           (10U)
#define PWC_FCG0_SRAMRET                               (0x00000400UL)
#define PWC_FCG0_PLA_POS                               (11U)
#define PWC_FCG0_PLA                                   (0x00000800UL)
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

/*  Bit definition for PWC_FCG1 register  */
#define PWC_FCG1_CAN1_POS                              (0U)
#define PWC_FCG1_CAN1                                  (0x00000001UL)
#define PWC_FCG1_CAN2_POS                              (1U)
#define PWC_FCG1_CAN2                                  (0x00000002UL)
#define PWC_FCG1_CAN3_POS                              (2U)
#define PWC_FCG1_CAN3                                  (0x00000004UL)
#define PWC_FCG1_QSPI_POS                              (3U)
#define PWC_FCG1_QSPI                                  (0x00000008UL)
#define PWC_FCG1_I2C1_POS                              (4U)
#define PWC_FCG1_I2C1                                  (0x00000010UL)
#define PWC_FCG1_I2C2_POS                              (5U)
#define PWC_FCG1_I2C2                                  (0x00000020UL)
#define PWC_FCG1_I2C3_POS                              (6U)
#define PWC_FCG1_I2C3                                  (0x00000040UL)
#define PWC_FCG1_MDIO_POS                              (8U)
#define PWC_FCG1_MDIO                                  (0x00000100UL)
#define PWC_FCG1_SPI1_POS                              (16U)
#define PWC_FCG1_SPI1                                  (0x00010000UL)
#define PWC_FCG1_SPI2_POS                              (17U)
#define PWC_FCG1_SPI2                                  (0x00020000UL)
#define PWC_FCG1_SPI3_POS                              (18U)
#define PWC_FCG1_SPI3                                  (0x00040000UL)
#define PWC_FCG1_SPI4_POS                              (19U)
#define PWC_FCG1_SPI4                                  (0x00080000UL)
#define PWC_FCG1_USBFS_POS                             (22U)
#define PWC_FCG1_USBFS                                 (0x00400000UL)
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
#define PWC_FCG2_TMR6_9_POS                            (8U)
#define PWC_FCG2_TMR6_9                                (0x00000100UL)
#define PWC_FCG2_TMR6_10_POS                           (9U)
#define PWC_FCG2_TMR6_10                               (0x00000200UL)
#define PWC_FCG2_TMR4_POS                              (10U)
#define PWC_FCG2_TMR4                                  (0x00000400UL)
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
#define PWC_FCG3_DAC3_POS                              (6U)
#define PWC_FCG3_DAC3                                  (0x00000040UL)
#define PWC_FCG3_DAC4_POS                              (7U)
#define PWC_FCG3_DAC4                                  (0x00000080UL)
#define PWC_FCG3_CMP12_POS                             (8U)
#define PWC_FCG3_CMP12                                 (0x00000100UL)
#define PWC_FCG3_CMP34_POS                             (9U)
#define PWC_FCG3_CMP34                                 (0x00000200UL)
#define PWC_FCG3_OTS_POS                               (12U)
#define PWC_FCG3_OTS                                   (0x00001000UL)
#define PWC_FCG3_VREF_POS                              (13U)
#define PWC_FCG3_VREF                                  (0x00002000UL)
#define PWC_FCG3_SMC_POS                               (16U)
#define PWC_FCG3_SMC                                   (0x00010000UL)
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

/*  Bit definition for PWC_FCG0PC register  */
#define PWC_FCG0PC_PRT0_POS                            (0U)
#define PWC_FCG0PC_PRT0                                (0x00000001UL)
#define PWC_FCG0PC_FCG0PCWE_POS                        (16U)
#define PWC_FCG0PC_FCG0PCWE                            (0xFFFF0000UL)

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

/*  Bit definition for PWC_PWRC4 register  */
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

/*  Bit definition for PWC_PWRC5 register  */
#define PWC_PWRC5_VVDRSD_POS                           (0U)
#define PWC_PWRC5_VVDRSD                               (0x01U)
#define PWC_PWRC5_RETRAMSD_POS                         (1U)
#define PWC_PWRC5_RETRAMSD                             (0x02U)
#define PWC_PWRC5_CSDIS_POS                            (7U)
#define PWC_PWRC5_CSDIS                                (0x80U)

/*  Bit definition for PWC_PWRC6 register  */
#define PWC_PWRC6_RTCCKSEL_POS                         (0U)
#define PWC_PWRC6_RTCCKSEL                             (0x03U)
#define PWC_PWRC6_RTCCKSEL_0                           (0x01U)
#define PWC_PWRC6_RTCCKSEL_1                           (0x02U)
#define PWC_PWRC6_IORTNCLR_POS                         (2U)
#define PWC_PWRC6_IORTNCLR                             (0x04U)
#define PWC_PWRC6_SWRDAC_POS                           (4U)
#define PWC_PWRC6_SWRDAC                               (0x10U)
#define PWC_PWRC6_WDRDAC_POS                           (5U)
#define PWC_PWRC6_WDRDAC                               (0x20U)
#define PWC_PWRC6_SWRTNE_POS                           (6U)
#define PWC_PWRC6_SWRTNE                               (0x40U)
#define PWC_PWRC6_WDRTNE_POS                           (7U)
#define PWC_PWRC6_WDRTNE                               (0x80U)

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

/*  Bit definition for PWC_RAMPC0 register  */
#define PWC_RAMPC0_RAMPDC0_POS                         (0U)
#define PWC_RAMPC0_RAMPDC0                             (0x00000001UL)
#define PWC_RAMPC0_RAMPDC10_POS                        (10U)
#define PWC_RAMPC0_RAMPDC10                            (0x00000400UL)

/*  Bit definition for PWC_PRAMLPC register  */
#define PWC_PRAMLPC_PRAMPDC0_POS                       (0U)
#define PWC_PRAMLPC_PRAMPDC0                           (0x00000001UL)
#define PWC_PRAMLPC_PRAMPDC1_POS                       (1U)
#define PWC_PRAMLPC_PRAMPDC1                           (0x00000002UL)
#define PWC_PRAMLPC_PRAMPDC2_POS                       (2U)
#define PWC_PRAMLPC_PRAMPDC2                           (0x00000004UL)
#define PWC_PRAMLPC_PRAMPDC3_POS                       (3U)
#define PWC_PRAMLPC_PRAMPDC3                           (0x00000008UL)

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
/*  Bit definition for RMU_FRST0 register  */
#define RMU_FRST0_PLA_POS                              (11U)
#define RMU_FRST0_PLA                                  (0x00000800UL)
#define RMU_FRST0_KEY_POS                              (13U)
#define RMU_FRST0_KEY                                  (0x00002000UL)
#define RMU_FRST0_DMA1_POS                             (14U)
#define RMU_FRST0_DMA1                                 (0x00004000UL)
#define RMU_FRST0_DMA2_POS                             (15U)
#define RMU_FRST0_DMA2                                 (0x00008000UL)
#define RMU_FRST0_FCM_POS                              (16U)
#define RMU_FRST0_FCM                                  (0x00010000UL)
#define RMU_FRST0_AOS_POS                              (17U)
#define RMU_FRST0_AOS                                  (0x00020000UL)
#define RMU_FRST0_CTC_POS                              (18U)
#define RMU_FRST0_CTC                                  (0x00040000UL)
#define RMU_FRST0_MAU_POS                              (19U)
#define RMU_FRST0_MAU                                  (0x00080000UL)
#define RMU_FRST0_AES_POS                              (20U)
#define RMU_FRST0_AES                                  (0x00100000UL)
#define RMU_FRST0_HASH_POS                             (21U)
#define RMU_FRST0_HASH                                 (0x00200000UL)
#define RMU_FRST0_TRNG_POS                             (22U)
#define RMU_FRST0_TRNG                                 (0x00400000UL)
#define RMU_FRST0_CRC_POS                              (23U)
#define RMU_FRST0_CRC                                  (0x00800000UL)
#define RMU_FRST0_DCU1_POS                             (24U)
#define RMU_FRST0_DCU1                                 (0x01000000UL)
#define RMU_FRST0_DCU2_POS                             (25U)
#define RMU_FRST0_DCU2                                 (0x02000000UL)
#define RMU_FRST0_DCU3_POS                             (26U)
#define RMU_FRST0_DCU3                                 (0x04000000UL)

/*  Bit definition for RMU_FRST1 register  */
#define RMU_FRST1_QSPI_POS                             (3U)
#define RMU_FRST1_QSPI                                 (0x00000008UL)
#define RMU_FRST1_MDIO_POS                             (8U)
#define RMU_FRST1_MDIO                                 (0x00000100UL)
#define RMU_FRST1_SPI1_POS                             (16U)
#define RMU_FRST1_SPI1                                 (0x00010000UL)
#define RMU_FRST1_SPI2_POS                             (17U)
#define RMU_FRST1_SPI2                                 (0x00020000UL)
#define RMU_FRST1_SPI3_POS                             (18U)
#define RMU_FRST1_SPI3                                 (0x00040000UL)
#define RMU_FRST1_SPI4_POS                             (19U)
#define RMU_FRST1_SPI4                                 (0x00080000UL)
#define RMU_FRST1_USBFS_POS                            (22U)
#define RMU_FRST1_USBFS                                (0x00400000UL)
#define RMU_FRST1_FMAC1_POS                            (24U)
#define RMU_FRST1_FMAC1                                (0x01000000UL)
#define RMU_FRST1_FMAC2_POS                            (25U)
#define RMU_FRST1_FMAC2                                (0x02000000UL)
#define RMU_FRST1_FMAC3_POS                            (26U)
#define RMU_FRST1_FMAC3                                (0x04000000UL)
#define RMU_FRST1_FMAC4_POS                            (27U)
#define RMU_FRST1_FMAC4                                (0x08000000UL)

/*  Bit definition for RMU_FRST2 register  */
#define RMU_FRST2_TMR6_POS                             (0U)
#define RMU_FRST2_TMR6                                 (0x00000001UL)
#define RMU_FRST2_TMR4_POS                             (10U)
#define RMU_FRST2_TMR4                                 (0x00000400UL)
#define RMU_FRST2_TMR0_POS                             (12U)
#define RMU_FRST2_TMR0                                 (0x00001000UL)
#define RMU_FRST2_EMB_POS                              (15U)
#define RMU_FRST2_EMB                                  (0x00008000UL)
#define RMU_FRST2_TMR2_POS                             (16U)
#define RMU_FRST2_TMR2                                 (0x00010000UL)
#define RMU_FRST2_TMRA_POS                             (20U)
#define RMU_FRST2_TMRA                                 (0x00100000UL)

/*  Bit definition for RMU_FRST3 register  */
#define RMU_FRST3_ADC1_POS                             (0U)
#define RMU_FRST3_ADC1                                 (0x00000001UL)
#define RMU_FRST3_ADC2_POS                             (1U)
#define RMU_FRST3_ADC2                                 (0x00000002UL)
#define RMU_FRST3_ADC3_POS                             (2U)
#define RMU_FRST3_ADC3                                 (0x00000004UL)
#define RMU_FRST3_DAC1_POS                             (4U)
#define RMU_FRST3_DAC1                                 (0x00000010UL)
#define RMU_FRST3_DAC2_POS                             (5U)
#define RMU_FRST3_DAC2                                 (0x00000020UL)
#define RMU_FRST3_DAC3_POS                             (6U)
#define RMU_FRST3_DAC3                                 (0x00000040UL)
#define RMU_FRST3_DAC4_POS                             (7U)
#define RMU_FRST3_DAC4                                 (0x00000080UL)
#define RMU_FRST3_CMP12_POS                            (8U)
#define RMU_FRST3_CMP12                                (0x00000100UL)
#define RMU_FRST3_CMP34_POS                            (9U)
#define RMU_FRST3_CMP34                                (0x00000200UL)
#define RMU_FRST3_OTS_POS                              (12U)
#define RMU_FRST3_OTS                                  (0x00001000UL)
#define RMU_FRST3_VREF_POS                             (13U)
#define RMU_FRST3_VREF                                 (0x00002000UL)
#define RMU_FRST3_SMC_POS                              (16U)
#define RMU_FRST3_SMC                                  (0x00010000UL)
#define RMU_FRST3_USART1_POS                           (20U)
#define RMU_FRST3_USART1                               (0x00100000UL)
#define RMU_FRST3_USART2_POS                           (21U)
#define RMU_FRST3_USART2                               (0x00200000UL)
#define RMU_FRST3_USART3_POS                           (22U)
#define RMU_FRST3_USART3                               (0x00400000UL)
#define RMU_FRST3_USART4_POS                           (23U)
#define RMU_FRST3_USART4                               (0x00800000UL)
#define RMU_FRST3_USART5_POS                           (24U)
#define RMU_FRST3_USART5                               (0x01000000UL)
#define RMU_FRST3_USART6_POS                           (25U)
#define RMU_FRST3_USART6                               (0x02000000UL)

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
#define RTC_ALMHOUR_ALMHOURD_POS                       (4U)
#define RTC_ALMHOUR_ALMHOURD                           (0x30U)
#define RTC_ALMHOUR_ALMHOURD_0                         (0x10U)
#define RTC_ALMHOUR_ALMHOURD_1                         (0x20U)

/*  Bit definition for RTC_ALMWEEK register  */
#define RTC_ALMWEEK_ALMWEEK                            (0x7FU)

/*  Bit definition for RTC_ERRCRH register  */
#define RTC_ERRCRH_COMP8_POS                           (0U)
#define RTC_ERRCRH_COMP8                               (0x01U)
#define RTC_ERRCRH_COMPEN_POS                          (7U)
#define RTC_ERRCRH_COMPEN                              (0x80U)

/*  Bit definition for RTC_ERRCRL register  */
#define RTC_ERRCRL                                     (0xFFU)

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
#define SMC_CPCR_WSYN_POS                              (4U)
#define SMC_CPCR_WSYN                                  (0x00000010UL)
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
#define SMC_CPSR_WSYN_POS                              (4U)
#define SMC_CPSR_WSYN                                  (0x00000010UL)
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

/*  Bit definition for SPI_CR register  */
#define SPI_CR_SPIMDS_POS                              (0U)
#define SPI_CR_SPIMDS                                  (0x00000001UL)
#define SPI_CR_TXMDS_POS                               (1U)
#define SPI_CR_TXMDS                                   (0x00000002UL)
#define SPI_CR_MSTR_POS                                (3U)
#define SPI_CR_MSTR                                    (0x00000008UL)
#define SPI_CR_SPLPBK_POS                              (4U)
#define SPI_CR_SPLPBK                                  (0x00000010UL)
#define SPI_CR_SPLPBK2_POS                             (5U)
#define SPI_CR_SPLPBK2                                 (0x00000020UL)
#define SPI_CR_SPE_POS                                 (6U)
#define SPI_CR_SPE                                     (0x00000040UL)
#define SPI_CR_CSUSPE_POS                              (7U)
#define SPI_CR_CSUSPE                                  (0x00000080UL)
#define SPI_CR_EIE_POS                                 (8U)
#define SPI_CR_EIE                                     (0x00000100UL)
#define SPI_CR_TXIE_POS                                (9U)
#define SPI_CR_TXIE                                    (0x00000200UL)
#define SPI_CR_RXIE_POS                                (10U)
#define SPI_CR_RXIE                                    (0x00000400UL)
#define SPI_CR_IDIE_POS                                (11U)
#define SPI_CR_IDIE                                    (0x00000800UL)
#define SPI_CR_MODFE_POS                               (12U)
#define SPI_CR_MODFE                                   (0x00001000UL)
#define SPI_CR_PATE_POS                                (13U)
#define SPI_CR_PATE                                    (0x00002000UL)
#define SPI_CR_PAOE_POS                                (14U)
#define SPI_CR_PAOE                                    (0x00004000UL)
#define SPI_CR_PAE_POS                                 (15U)
#define SPI_CR_PAE                                     (0x00008000UL)

/*  Bit definition for SPI_CFG1 register  */
#define SPI_CFG1_FTHLV_POS                             (0U)
#define SPI_CFG1_FTHLV                                 (0x00000003UL)
#define SPI_CFG1_FTHLV_0                               (0x00000001UL)
#define SPI_CFG1_FTHLV_1                               (0x00000002UL)
#define SPI_CFG1_CTMDS_POS                             (2U)
#define SPI_CFG1_CTMDS                                 (0x00000004UL)
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
#define SPI_CFG1_CLKDIV_POS                            (12U)
#define SPI_CFG1_CLKDIV                                (0x0000F000UL)
#define SPI_CFG1_MSSI_POS                              (20U)
#define SPI_CFG1_MSSI                                  (0x00700000UL)
#define SPI_CFG1_MSSDL_POS                             (24U)
#define SPI_CFG1_MSSDL                                 (0x07000000UL)
#define SPI_CFG1_MIDI_POS                              (28U)
#define SPI_CFG1_MIDI                                  (0x70000000UL)

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
#define SPI_CFG2_MBR                                   (0x0000000CUL)
#define SPI_CFG2_MBR_0                                 (0x00000004UL)
#define SPI_CFG2_MBR_1                                 (0x00000008UL)
#define SPI_CFG2_SSA_POS                               (5U)
#define SPI_CFG2_SSA                                   (0x000000E0UL)
#define SPI_CFG2_SSA_0                                 (0x00000020UL)
#define SPI_CFG2_SSA_1                                 (0x00000040UL)
#define SPI_CFG2_SSA_2                                 (0x00000080UL)
#define SPI_CFG2_DSIZE_POS                             (8U)
#define SPI_CFG2_DSIZE                                 (0x00000F00UL)
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
#define SRAMC_CKSR_SRAMH_PYERR_POS                     (3U)
#define SRAMC_CKSR_SRAMH_PYERR                         (0x00000008UL)
#define SRAMC_CKSR_SRAM0_1ERR_POS                      (4U)
#define SRAMC_CKSR_SRAM0_1ERR                          (0x00000010UL)
#define SRAMC_CKSR_SRAM0_2ERR_POS                      (5U)
#define SRAMC_CKSR_SRAM0_2ERR                          (0x00000020UL)
#define SRAMC_CKSR_SRAMB_1ERR_POS                      (6U)
#define SRAMC_CKSR_SRAMB_1ERR                          (0x00000040UL)
#define SRAMC_CKSR_SRAMB_2ERR_POS                      (7U)
#define SRAMC_CKSR_SRAMB_2ERR                          (0x00000080UL)
#define SRAMC_CKSR_CACHE_PYERR_POS                     (8U)
#define SRAMC_CKSR_CACHE_PYERR                         (0x00000100UL)

/*  Bit definition for SRAMC_SRAM0_EIEN register  */
#define SRAMC_SRAM0_EIEN_EIEN                          (0x00000001UL)

/*  Bit definition for SRAMC_SRAM0_EIBIT0 register  */
#define SRAMC_SRAM0_EIBIT0                             (0xFFFFFFFFUL)

/*  Bit definition for SRAMC_SRAM0_EIBIT1 register  */
#define SRAMC_SRAM0_EIBIT1_EIBIT                       (0x0000007FUL)

/*  Bit definition for SRAMC_SRAM0_ECCERRADDR register  */
#define SRAMC_SRAM0_ECCERRADDR_ECCERRADDR              (0x00007FFFUL)

/*  Bit definition for SRAMC_SRAMB_EIEN register  */
#define SRAMC_SRAMB_EIEN_EIEN                          (0x00000001UL)

/*  Bit definition for SRAMC_SRAMB_EIBIT0 register  */
#define SRAMC_SRAMB_EIBIT0                             (0xFFFFFFFFUL)

/*  Bit definition for SRAMC_SRAMB_EIBIT1 register  */
#define SRAMC_SRAMB_EIBIT1_EIBIT                       (0x0000007FUL)

/*  Bit definition for SRAMC_SRAMB_ECCERRADDR register  */
#define SRAMC_SRAMB_ECCERRADDR_ECCERRADDR              (0x00000FFFUL)

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
#define SWDT_CR_WDPT_POS                               (8U)
#define SWDT_CR_WDPT                                   (0x00000F00UL)
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
#define TMR0_STFLR_ICPA_POS                            (1U)
#define TMR0_STFLR_ICPA                                (0x00000002UL)
#define TMR0_STFLR_CMFB_POS                            (16U)
#define TMR0_STFLR_CMFB                                (0x00010000UL)
#define TMR0_STFLR_ICPB_POS                            (17U)
#define TMR0_STFLR_ICPB                                (0x00020000UL)

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
#define TMR2_STFLR_ICPA_POS                            (2U)
#define TMR2_STFLR_ICPA                                (0x00000004UL)
#define TMR2_STFLR_CMFB_POS                            (16U)
#define TMR2_STFLR_CMFB                                (0x00010000UL)
#define TMR2_STFLR_OVFB_POS                            (17U)
#define TMR2_STFLR_OVFB                                (0x00020000UL)
#define TMR2_STFLR_ICPB_POS                            (18U)
#define TMR2_STFLR_ICPB                                (0x00040000UL)

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
#define TMR4_CCSR_IRQZEN_POS                           (10U)
#define TMR4_CCSR_IRQZEN                               (0x0400U)
#define TMR4_CCSR_IRQZF_POS                            (11U)
#define TMR4_CCSR_IRQZF                                (0x0800U)
#define TMR4_CCSR_HST_POS                              (13U)
#define TMR4_CCSR_HST                                  (0x2000U)
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

/*  Bit definition for TMR4_SCER register  */
#define TMR4_SCER_EVTRS_POS                            (0U)
#define TMR4_SCER_EVTRS                                (0x0007U)
#define TMR4_SCER_PCTS_POS                             (3U)
#define TMR4_SCER_PCTS                                 (0x0008U)

/*  Bit definition for TMR4_SCIR register  */
#define TMR4_SCIR_ITEN0_POS                            (0U)
#define TMR4_SCIR_ITEN0                                (0x0001U)
#define TMR4_SCIR_ITEN1_POS                            (1U)
#define TMR4_SCIR_ITEN1                                (0x0002U)
#define TMR4_SCIR_ITEN2_POS                            (2U)
#define TMR4_SCIR_ITEN2                                (0x0004U)
#define TMR4_SCIR_ITEN3_POS                            (3U)
#define TMR4_SCIR_ITEN3                                (0x0008U)
#define TMR4_SCIR_ITEN4_POS                            (4U)
#define TMR4_SCIR_ITEN4                                (0x0010U)
#define TMR4_SCIR_ITEN5_POS                            (5U)
#define TMR4_SCIR_ITEN5                                (0x0020U)

/*  Bit definition for TMR4_SCFR register  */
#define TMR4_SCFR_SF0_POS                              (0U)
#define TMR4_SCFR_SF0                                  (0x0001U)
#define TMR4_SCFR_SF1_POS                              (1U)
#define TMR4_SCFR_SF1                                  (0x0002U)
#define TMR4_SCFR_SF2_POS                              (2U)
#define TMR4_SCFR_SF2                                  (0x0004U)
#define TMR4_SCFR_SF3_POS                              (3U)
#define TMR4_SCFR_SF3                                  (0x0008U)
#define TMR4_SCFR_SF4_POS                              (4U)
#define TMR4_SCFR_SF4                                  (0x0010U)
#define TMR4_SCFR_SF5_POS                              (5U)
#define TMR4_SCFR_SF5                                  (0x0020U)

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
#define TMR6_PCNAR_EMBSA                               (0x07000000UL)
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
#define TMR6_PCNBR_EMBSB                               (0x07000000UL)
#define TMR6_PCNBR_EMBSB_0                             (0x01000000UL)
#define TMR6_PCNBR_EMBSB_1                             (0x02000000UL)
#define TMR6_PCNBR_EMBSB_2                             (0x04000000UL)
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
#define TMR6_STFLR_CMAF2_POS                           (26U)
#define TMR6_STFLR_CMAF2                               (0x04000000UL)
#define TMR6_STFLR_CMBF2_POS                           (27U)
#define TMR6_STFLR_CMBF2                               (0x08000000UL)
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
                Bit definition for Peripheral TMR6_COMMON
*******************************************************************************/
/*  Bit definition for TMR6_COMMON_FCNTR register  */
#define TMR6_COMMON_FCNTR_NOFIENTA_POS                 (0U)
#define TMR6_COMMON_FCNTR_NOFIENTA                     (0x00000001UL)
#define TMR6_COMMON_FCNTR_NOFICKTA_POS                 (1U)
#define TMR6_COMMON_FCNTR_NOFICKTA                     (0x00000006UL)
#define TMR6_COMMON_FCNTR_NOFICKTA_0                   (0x00000002UL)
#define TMR6_COMMON_FCNTR_NOFICKTA_1                   (0x00000004UL)
#define TMR6_COMMON_FCNTR_NOFIENTB_POS                 (4U)
#define TMR6_COMMON_FCNTR_NOFIENTB                     (0x00000010UL)
#define TMR6_COMMON_FCNTR_NOFICKTB_POS                 (5U)
#define TMR6_COMMON_FCNTR_NOFICKTB                     (0x00000060UL)
#define TMR6_COMMON_FCNTR_NOFICKTB_0                   (0x00000020UL)
#define TMR6_COMMON_FCNTR_NOFICKTB_1                   (0x00000040UL)
#define TMR6_COMMON_FCNTR_NOFIENTC_POS                 (8U)
#define TMR6_COMMON_FCNTR_NOFIENTC                     (0x00000100UL)
#define TMR6_COMMON_FCNTR_NOFICKTC_POS                 (9U)
#define TMR6_COMMON_FCNTR_NOFICKTC                     (0x00000600UL)
#define TMR6_COMMON_FCNTR_NOFICKTC_0                   (0x00000200UL)
#define TMR6_COMMON_FCNTR_NOFICKTC_1                   (0x00000400UL)
#define TMR6_COMMON_FCNTR_NOFIENTD_POS                 (12U)
#define TMR6_COMMON_FCNTR_NOFIENTD                     (0x00001000UL)
#define TMR6_COMMON_FCNTR_NOFICKTD_POS                 (13U)
#define TMR6_COMMON_FCNTR_NOFICKTD                     (0x00006000UL)
#define TMR6_COMMON_FCNTR_NOFICKTD_0                   (0x00002000UL)
#define TMR6_COMMON_FCNTR_NOFICKTD_1                   (0x00004000UL)

/*  Bit definition for TMR6_COMMON_SSTAR register  */
#define TMR6_COMMON_SSTAR_SSTA1_POS                    (0U)
#define TMR6_COMMON_SSTAR_SSTA1                        (0x00000001UL)
#define TMR6_COMMON_SSTAR_SSTA2_POS                    (1U)
#define TMR6_COMMON_SSTAR_SSTA2                        (0x00000002UL)
#define TMR6_COMMON_SSTAR_SSTA3_POS                    (2U)
#define TMR6_COMMON_SSTAR_SSTA3                        (0x00000004UL)
#define TMR6_COMMON_SSTAR_SSTA4_POS                    (3U)
#define TMR6_COMMON_SSTAR_SSTA4                        (0x00000008UL)
#define TMR6_COMMON_SSTAR_SSTA5_POS                    (4U)
#define TMR6_COMMON_SSTAR_SSTA5                        (0x00000010UL)
#define TMR6_COMMON_SSTAR_SSTA6_POS                    (5U)
#define TMR6_COMMON_SSTAR_SSTA6                        (0x00000020UL)
#define TMR6_COMMON_SSTAR_SSTA7_POS                    (6U)
#define TMR6_COMMON_SSTAR_SSTA7                        (0x00000040UL)
#define TMR6_COMMON_SSTAR_SSTA8_POS                    (7U)
#define TMR6_COMMON_SSTAR_SSTA8                        (0x00000080UL)
#define TMR6_COMMON_SSTAR_SSTA9_POS                    (8U)
#define TMR6_COMMON_SSTAR_SSTA9                        (0x00000100UL)
#define TMR6_COMMON_SSTAR_SSTA10_POS                   (9U)
#define TMR6_COMMON_SSTAR_SSTA10                       (0x00000200UL)

/*  Bit definition for TMR6_COMMON_SSTPR register  */
#define TMR6_COMMON_SSTPR_SSTP1_POS                    (0U)
#define TMR6_COMMON_SSTPR_SSTP1                        (0x00000001UL)
#define TMR6_COMMON_SSTPR_SSTP2_POS                    (1U)
#define TMR6_COMMON_SSTPR_SSTP2                        (0x00000002UL)
#define TMR6_COMMON_SSTPR_SSTP3_POS                    (2U)
#define TMR6_COMMON_SSTPR_SSTP3                        (0x00000004UL)
#define TMR6_COMMON_SSTPR_SSTP4_POS                    (3U)
#define TMR6_COMMON_SSTPR_SSTP4                        (0x00000008UL)
#define TMR6_COMMON_SSTPR_SSTP5_POS                    (4U)
#define TMR6_COMMON_SSTPR_SSTP5                        (0x00000010UL)
#define TMR6_COMMON_SSTPR_SSTP6_POS                    (5U)
#define TMR6_COMMON_SSTPR_SSTP6                        (0x00000020UL)
#define TMR6_COMMON_SSTPR_SSTP7_POS                    (6U)
#define TMR6_COMMON_SSTPR_SSTP7                        (0x00000040UL)
#define TMR6_COMMON_SSTPR_SSTP8_POS                    (7U)
#define TMR6_COMMON_SSTPR_SSTP8                        (0x00000080UL)
#define TMR6_COMMON_SSTPR_SSTP9_POS                    (8U)
#define TMR6_COMMON_SSTPR_SSTP9                        (0x00000100UL)
#define TMR6_COMMON_SSTPR_SSTP10_POS                   (9U)
#define TMR6_COMMON_SSTPR_SSTP10                       (0x00000200UL)

/*  Bit definition for TMR6_COMMON_SCLRR register  */
#define TMR6_COMMON_SCLRR_SCLE1_POS                    (0U)
#define TMR6_COMMON_SCLRR_SCLE1                        (0x00000001UL)
#define TMR6_COMMON_SCLRR_SCLE2_POS                    (1U)
#define TMR6_COMMON_SCLRR_SCLE2                        (0x00000002UL)
#define TMR6_COMMON_SCLRR_SCLE3_POS                    (2U)
#define TMR6_COMMON_SCLRR_SCLE3                        (0x00000004UL)
#define TMR6_COMMON_SCLRR_SCLE4_POS                    (3U)
#define TMR6_COMMON_SCLRR_SCLE4                        (0x00000008UL)
#define TMR6_COMMON_SCLRR_SCLE5_POS                    (4U)
#define TMR6_COMMON_SCLRR_SCLE5                        (0x00000010UL)
#define TMR6_COMMON_SCLRR_SCLE6_POS                    (5U)
#define TMR6_COMMON_SCLRR_SCLE6                        (0x00000020UL)
#define TMR6_COMMON_SCLRR_SCLE7_POS                    (6U)
#define TMR6_COMMON_SCLRR_SCLE7                        (0x00000040UL)
#define TMR6_COMMON_SCLRR_SCLE8_POS                    (7U)
#define TMR6_COMMON_SCLRR_SCLE8                        (0x00000080UL)
#define TMR6_COMMON_SCLRR_SCLE9_POS                    (8U)
#define TMR6_COMMON_SCLRR_SCLE9                        (0x00000100UL)
#define TMR6_COMMON_SCLRR_SCLE10_POS                   (9U)
#define TMR6_COMMON_SCLRR_SCLE10                       (0x00000200UL)

/*  Bit definition for TMR6_COMMON_SUPDR register  */
#define TMR6_COMMON_SUPDR_SUPD1_POS                    (0U)
#define TMR6_COMMON_SUPDR_SUPD1                        (0x00000001UL)
#define TMR6_COMMON_SUPDR_SUPD2_POS                    (1U)
#define TMR6_COMMON_SUPDR_SUPD2                        (0x00000002UL)
#define TMR6_COMMON_SUPDR_SUPD3_POS                    (2U)
#define TMR6_COMMON_SUPDR_SUPD3                        (0x00000004UL)
#define TMR6_COMMON_SUPDR_SUPD4_POS                    (3U)
#define TMR6_COMMON_SUPDR_SUPD4                        (0x00000008UL)
#define TMR6_COMMON_SUPDR_SUPD5_POS                    (4U)
#define TMR6_COMMON_SUPDR_SUPD5                        (0x00000010UL)
#define TMR6_COMMON_SUPDR_SUPD6_POS                    (5U)
#define TMR6_COMMON_SUPDR_SUPD6                        (0x00000020UL)
#define TMR6_COMMON_SUPDR_SUPD7_POS                    (6U)
#define TMR6_COMMON_SUPDR_SUPD7                        (0x00000040UL)
#define TMR6_COMMON_SUPDR_SUPD8_POS                    (7U)
#define TMR6_COMMON_SUPDR_SUPD8                        (0x00000080UL)
#define TMR6_COMMON_SUPDR_SUPD9_POS                    (8U)
#define TMR6_COMMON_SUPDR_SUPD9                        (0x00000100UL)
#define TMR6_COMMON_SUPDR_SUPD10_POS                   (9U)
#define TMR6_COMMON_SUPDR_SUPD10                       (0x00000200UL)

/*******************************************************************************
                Bit definition for Peripheral TMRA
*******************************************************************************/
/*  Bit definition for TMRA_CNTER register  */
#define TMRA_CNTER_CNT                                 (0xFFFFFFFFUL)

/*  Bit definition for TMRA_PERAR register  */
#define TMRA_PERAR_PER                                 (0xFFFFFFFFUL)

/*  Bit definition for TMRA_CMPAR register  */
#define TMRA_CMPAR_CMP                                 (0xFFFFFFFFUL)

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
#define TMRA_STFLR_ICPF1_POS                           (8U)
#define TMRA_STFLR_ICPF1                               (0x0100U)
#define TMRA_STFLR_ICPF2_POS                           (9U)
#define TMRA_STFLR_ICPF2                               (0x0200U)
#define TMRA_STFLR_ICPF3_POS                           (10U)
#define TMRA_STFLR_ICPF3                               (0x0400U)
#define TMRA_STFLR_ICPF4_POS                           (11U)
#define TMRA_STFLR_ICPF4                               (0x0800U)

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
#define USART_SR_TEND_POS                              (11U)
#define USART_SR_TEND                                  (0x00000800UL)
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
#define USART_CR1_TENDIE_POS                           (8U)
#define USART_CR1_TENDIE                               (0x00000100UL)
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
#define USART_CR1_CTEND_POS                            (25U)
#define USART_CR1_CTEND                                (0x02000000UL)
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
#define USBFS_GRSTCTL_CSFTRSTDONE_POS                  (29U)
#define USBFS_GRSTCTL_CSFTRSTDONE                      (0x20000000UL)
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
                Bit definition for Peripheral VREF
*******************************************************************************/
/*  Bit definition for VREF_BGRCR register  */
#define VREF_BGRCR_BGREN                               (0x00000001UL)

/*  Bit definition for VREF_CSCR register  */
#define VREF_CSCR_CSEN                                 (0x00000001UL)

/*  Bit definition for VREF_CR register  */
#define VREF_CR_AVCCMONEN_POS                          (0U)
#define VREF_CR_AVCCMONEN                              (0x00000001UL)
#define VREF_CR_VREFINTEN_POS                          (1U)
#define VREF_CR_VREFINTEN                              (0x00000002UL)
#define VREF_CR_IVREFEN_POS                            (2U)
#define VREF_CR_IVREFEN                                (0x00000004UL)
#define VREF_CR_HIZ_POS                                (3U)
#define VREF_CR_HIZ                                    (0x00000008UL)
#define VREF_CR_AVCCMONS_POS                           (4U)
#define VREF_CR_AVCCMONS                               (0x00000030UL)
#define VREF_CR_AVCCMONS_0                             (0x00000010UL)
#define VREF_CR_AVCCMONS_1                             (0x00000020UL)

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
#define WDT_CR_WDPT_POS                                (8U)
#define WDT_CR_WDPT                                    (0x00000F00UL)
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
    __IO uint32_t PGAVSSEN;
    uint32_t RESERVED0[7];
} stc_adc_pgavssenr_bit_t;

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
    __IO uint32_t CENA;
    uint32_t RESERVED0[3];
    __IO uint32_t WDEN;
    uint32_t RESERVED1[3];
} stc_cmp_mdr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t CIEN;
    uint32_t RESERVED1[2];
    __IO uint32_t CFF;
    __IO uint32_t CRF;
} stc_cmp_fir_bit_t;

typedef struct {
    __IO uint32_t COEN;
    __IO uint32_t COPS;
    __IO uint32_t CPOE;
    uint32_t RESERVED0[1];
    __IO uint32_t BWEN;
    __IO uint32_t BWMD;
    uint32_t RESERVED1[2];
} stc_cmp_ocr_bit_t;

typedef struct {
    __I  uint32_t CMON;
    uint32_t RESERVED0[7];
} stc_cmp_omr_bit_t;

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
} stc_cmp_bwsr1_bit_t;

typedef struct {
    __IO uint32_t FRADIVEN;
    uint32_t RESERVED0[31];
} stc_cmu_xtaldivcr_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t XTALMS;
    uint32_t RESERVED1[4];
} stc_cmu_xtalcfgr_bit_t;

typedef struct {
    __IO uint32_t XTAL32STP;
    uint32_t RESERVED0[7];
} stc_cmu_xtal32cr_bit_t;

typedef struct {
    __IO uint32_t LRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_lrccr_bit_t;

typedef struct {
    __IO uint32_t PLLHOFF;
    uint32_t RESERVED0[7];
} stc_cmu_pllhcr_bit_t;

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
    uint32_t RESERVED2[2];
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
    __IO uint32_t DAOGS1;
    __IO uint32_t DAOGS2;
    uint32_t RESERVED0[3];
    __IO uint32_t DPSEL;
    __IO uint32_t DAAMP1;
    __IO uint32_t DAAMP2;
    uint32_t RESERVED1[5];
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
    uint32_t RESERVED0[25];
} stc_dcu_flag_bit_t;

typedef struct {
    __IO uint32_t CLR_OP;
    __IO uint32_t CLR_LS2;
    __IO uint32_t CLR_EQ2;
    __IO uint32_t CLR_GT2;
    __IO uint32_t CLR_LS1;
    __IO uint32_t CLR_EQ1;
    __IO uint32_t CLR_GT1;
    uint32_t RESERVED0[25];
} stc_dcu_flagclr_bit_t;

typedef struct {
    __IO uint32_t SEL_OP;
    __IO uint32_t SEL_LS2;
    __IO uint32_t SEL_EQ2;
    __IO uint32_t SEL_GT2;
    __IO uint32_t SEL_LS1;
    __IO uint32_t SEL_EQ1;
    __IO uint32_t SEL_GT1;
    uint32_t RESERVED0[25];
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
    __IO uint32_t WLOCK0;
    uint32_t RESERVED0[3];
    __IO uint32_t WLOCK1;
    uint32_t RESERVED1[27];
} stc_efm_wlock_bit_t;

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
} stc_efm_f0nwprt_bit_t;

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
} stc_efm_f1nwprt_bit_t;

typedef struct {
    __IO uint32_t CMPEN1;
    __IO uint32_t CMPEN2;
    __IO uint32_t CMPEN3;
    __IO uint32_t CMPEN4;
    __IO uint32_t SYSEN;
    __IO uint32_t PWMSEN0;
    __IO uint32_t PWMSEN1;
    __IO uint32_t PWMSEN2;
    __IO uint32_t PWMSEN3;
    __IO uint32_t PWMSEN4;
    __IO uint32_t PWMSEN5;
    __IO uint32_t PWMSEN6;
    __IO uint32_t PWMSEN7;
    __IO uint32_t PWMSEN8;
    __IO uint32_t PWMSEN9;
    uint32_t RESERVED0[1];
    __IO uint32_t PORTINEN1;
    __IO uint32_t PORTINEN2;
    __IO uint32_t PORTINEN3;
    __IO uint32_t PORTINEN4;
    __IO uint32_t PORTINEN5;
    uint32_t RESERVED1[1];
    __IO uint32_t INVSEL1;
    __IO uint32_t INVSEL2;
    __IO uint32_t INVSEL3;
    __IO uint32_t INVSEL4;
    __IO uint32_t INVSEL5;
    __IO uint32_t OSCSTPEN;
    __IO uint32_t SRAMERREN;
    __IO uint32_t SRAMPYERREN;
    __IO uint32_t LOCKUPEN;
    __IO uint32_t PVDEN;
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
    __IO uint32_t PWMLV8;
    __IO uint32_t PWMLV9;
    uint32_t RESERVED0[8];
    __IO uint32_t NFEN1;
    uint32_t RESERVED1[2];
    __IO uint32_t NFEN2;
    uint32_t RESERVED2[2];
    __IO uint32_t NFEN3;
    uint32_t RESERVED3[2];
    __IO uint32_t NFEN4;
    uint32_t RESERVED4[2];
    __IO uint32_t NFEN5;
    uint32_t RESERVED5[1];
} stc_emb_ctl2_bit_t;

typedef struct {
    __IO uint32_t SOE;
    uint32_t RESERVED0[31];
} stc_emb_soe_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __I  uint32_t PWMSF;
    __I  uint32_t CMPF;
    __I  uint32_t SYSF;
    uint32_t RESERVED1[1];
    __I  uint32_t PWMST;
    __I  uint32_t CMPST;
    __I  uint32_t SYSST;
    __I  uint32_t PORTINF1;
    __I  uint32_t PORTINF2;
    __I  uint32_t PORTINF3;
    __I  uint32_t PORTINF4;
    __I  uint32_t PORTINF5;
    uint32_t RESERVED2[1];
    __I  uint32_t PORTINST1;
    __I  uint32_t PORTINST2;
    __I  uint32_t PORTINST3;
    __I  uint32_t PORTINST4;
    __I  uint32_t PORTINST5;
    uint32_t RESERVED3[13];
} stc_emb_stat_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __O  uint32_t PWMSFCLR;
    __O  uint32_t CMPFCLR;
    __O  uint32_t SYSFCLR;
    uint32_t RESERVED1[4];
    __O  uint32_t PORTINFCLR1;
    __O  uint32_t PORTINFCLR2;
    __O  uint32_t PORTINFCLR3;
    __O  uint32_t PORTINFCLR4;
    __O  uint32_t PORTINFCLR5;
    uint32_t RESERVED2[19];
} stc_emb_statclr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t PWMSINTEN;
    __IO uint32_t CMPINTEN;
    __IO uint32_t SYSINTEN;
    uint32_t RESERVED1[4];
    __IO uint32_t PORTININTEN1;
    __IO uint32_t PORTININTEN2;
    __IO uint32_t PORTININTEN3;
    __IO uint32_t PORTININTEN4;
    __IO uint32_t PORTININTEN5;
    uint32_t RESERVED2[19];
} stc_emb_inten_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t PWMRSEL;
    __IO uint32_t CMPRSEL;
    __IO uint32_t SYSRSEL;
    uint32_t RESERVED1[4];
    __IO uint32_t PORTINRSEL1;
    __IO uint32_t PORTINRSEL2;
    __IO uint32_t PORTINRSEL3;
    __IO uint32_t PORTINRSEL4;
    __IO uint32_t PORTINRSEL5;
    uint32_t RESERVED2[19];
} stc_emb_rlssel_bit_t;

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
    __IO uint32_t WE;
    uint32_t RESERVED0[15];
} stc_gpio_pwpr_bit_t;

typedef struct {
    __IO uint32_t POUT;
    __IO uint32_t POUTE;
    __IO uint32_t NOD;
    uint32_t RESERVED0[3];
    __IO uint32_t PUU;
    __IO uint32_t PUD;
    __I  uint32_t PIN;
    __IO uint32_t INVE;
    __IO uint32_t CINSEL;
    uint32_t RESERVED1[1];
    __IO uint32_t INTE;
    __IO uint32_t PINAE;
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
    uint32_t RESERVED2[1];
    __IO uint32_t RFREQIE;
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
    uint32_t RESERVED1[1];
    __IO uint32_t BUSFREECLREN;
    uint32_t RESERVED2[19];
} stc_i2c_cr4_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t SLADDR0EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD0;
    uint32_t RESERVED2[10];
    __IO uint32_t MASKEN0;
    uint32_t RESERVED3[5];
} stc_i2c_slr0_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t SLADDR1EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD1;
    uint32_t RESERVED2[10];
    __IO uint32_t MASKEN1;
    uint32_t RESERVED3[5];
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
    __IO uint32_t TFEMPTY;
    __IO uint32_t TFFULL;
    __IO uint32_t RFEMPTY;
    __IO uint32_t RFFULL;
    uint32_t RESERVED6[3];
    __IO uint32_t RFREQ;
} stc_i2c_sr_bit_t;

typedef struct {
    __O  uint32_t STARTFCLR;
    __O  uint32_t SLADDR0FCLR;
    __O  uint32_t SLADDR1FCLR;
    __O  uint32_t TENDFCLR;
    __O  uint32_t STOPFCLR;
    uint32_t RESERVED0[1];
    __O  uint32_t RFULLFCLR;
    uint32_t RESERVED1[2];
    __O  uint32_t ARLOFCLR;
    __O  uint32_t RFREQCLR;
    uint32_t RESERVED2[1];
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
    uint32_t RESERVED0[23];
    __IO uint32_t FMPLUSEN;
    uint32_t RESERVED1[8];
} stc_i2c_ccr_bit_t;

typedef struct {
    uint32_t RESERVED0[4];
    __IO uint32_t DNFEN;
    __IO uint32_t ANFEN;
    uint32_t RESERVED1[26];
} stc_i2c_fltr_bit_t;

typedef struct {
    __IO uint32_t FEN;
    __IO uint32_t TFFLUSH;
    __IO uint32_t RFFLUSH;
    __IO uint32_t NACKTFFLUSH;
    uint32_t RESERVED0[28];
} stc_i2c_fstr_bit_t;

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
    __IO uint32_t SWDTEN;
    __IO uint32_t PVD1EN;
    __IO uint32_t PVD2EN;
    uint32_t RESERVED1[1];
    __IO uint32_t XTALSTPEN;
    uint32_t RESERVED2[2];
    __IO uint32_t RPARERREN;
    __IO uint32_t RECCERREN;
    __IO uint32_t BUSERREN;
    __IO uint32_t WDTEN;
    uint32_t RESERVED3[20];
} stc_intc_nmier_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SWDTF;
    __IO uint32_t PVD1F;
    __IO uint32_t PVD2F;
    uint32_t RESERVED1[1];
    __IO uint32_t XTALSTPF;
    uint32_t RESERVED2[2];
    __IO uint32_t RPARERRF;
    __IO uint32_t RECCERRF;
    __IO uint32_t BUSERRF;
    __IO uint32_t WDTF;
    uint32_t RESERVED3[20];
} stc_intc_nmifr_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SWDTFCLR;
    __IO uint32_t PVD1FCLR;
    __IO uint32_t PVD2FCLR;
    uint32_t RESERVED1[1];
    __IO uint32_t XTALSTPFCLR;
    uint32_t RESERVED2[2];
    __IO uint32_t RPARERRFCLR;
    __IO uint32_t RECCERRFCLR;
    __IO uint32_t BUSERRFCLR;
    __IO uint32_t WDTFCLR;
    uint32_t RESERVED3[20];
} stc_intc_nmifcr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t EFEN;
    uint32_t RESERVED1[7];
    __IO uint32_t NOCEN;
    uint32_t RESERVED2[16];
} stc_intc_eirqcr_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t SWDTWKEN;
    __IO uint32_t PVD1WKEN;
    __IO uint32_t PVD2WKEN;
    __IO uint32_t CMP1WKEN;
    __IO uint32_t WKTMWKEN;
    __IO uint32_t RTCALMWKEN;
    __IO uint32_t RTCPRDWKEN;
    __IO uint32_t TMR0CMPWKEN;
    __IO uint32_t TMR2CMPWKEN;
    __IO uint32_t TMR2OVFWKEN;
    __IO uint32_t RXWKEN;
    uint32_t RESERVED1[1];
    __IO uint32_t USFWKEN;
    __IO uint32_t CMP2WKEN;
    __IO uint32_t CMP3WKEN;
    __IO uint32_t CMP4WKEN;
} stc_intc_wken_bit_t;

typedef struct {
    __IO uint32_t EIF0;
    __IO uint32_t EIF1;
    __IO uint32_t EIF2;
    __IO uint32_t EIF3;
    __IO uint32_t EIF4;
    __IO uint32_t EIF5;
    __IO uint32_t EIF6;
    __IO uint32_t EIF7;
    __IO uint32_t EIF8;
    __IO uint32_t EIF9;
    __IO uint32_t EIF10;
    __IO uint32_t EIF11;
    __IO uint32_t EIF12;
    __IO uint32_t EIF13;
    __IO uint32_t EIF14;
    __IO uint32_t EIF15;
    uint32_t RESERVED0[16];
} stc_intc_eifr_bit_t;

typedef struct {
    __IO uint32_t EIFCLR0;
    __IO uint32_t EIFCLR1;
    __IO uint32_t EIFCLR2;
    __IO uint32_t EIFCLR3;
    __IO uint32_t EIFCLR4;
    __IO uint32_t EIFCLR5;
    __IO uint32_t EIFCLR6;
    __IO uint32_t EIFCLR7;
    __IO uint32_t EIFCLR8;
    __IO uint32_t EIFCLR9;
    __IO uint32_t EIFCLR10;
    __IO uint32_t EIFCLR11;
    __IO uint32_t EIFCLR12;
    __IO uint32_t EIFCLR13;
    __IO uint32_t EIFCLR14;
    __IO uint32_t EIFCLR15;
    uint32_t RESERVED0[16];
} stc_intc_eifcr_bit_t;

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
    __IO uint32_t IEN0;
    __IO uint32_t IEN1;
    __IO uint32_t IEN2;
    __IO uint32_t IEN3;
    __IO uint32_t IEN4;
    __IO uint32_t IEN5;
    __IO uint32_t IEN6;
    __IO uint32_t IEN7;
    __IO uint32_t IEN8;
    __IO uint32_t IEN9;
    __IO uint32_t IEN10;
    __IO uint32_t IEN11;
    __IO uint32_t IEN12;
    __IO uint32_t IEN13;
    __IO uint32_t IEN14;
    __IO uint32_t IEN15;
    __IO uint32_t IEN16;
    __IO uint32_t IEN17;
    __IO uint32_t IEN18;
    __IO uint32_t IEN19;
    __IO uint32_t IEN20;
    __IO uint32_t IEN21;
    __IO uint32_t IEN22;
    __IO uint32_t IEN23;
    __IO uint32_t IEN24;
    __IO uint32_t IEN25;
    __IO uint32_t IEN26;
    __IO uint32_t IEN27;
    __IO uint32_t IEN28;
    __IO uint32_t IEN29;
    __IO uint32_t IEN30;
    __IO uint32_t IEN31;
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
    __IO uint32_t MD_RST;
    __IO uint32_t MD_PHYB;
    uint32_t RESERVED0[30];
} stc_mdio_mdcon_bit_t;

typedef struct {
    __IO uint32_t MD_MSDEV;
    uint32_t RESERVED0[1];
    __IO uint32_t SEL_EDGE;
    __IO uint32_t MD_EN;
    uint32_t RESERVED1[28];
} stc_mdio_mdcon1_bit_t;

typedef struct {
    __IO uint32_t MD_WRF;
    __IO uint32_t MD_ADRF;
    __IO uint32_t MD_INCF;
    __IO uint32_t MD_RDF;
    __IO uint32_t MD_DEVM;
    __IO uint32_t MD_DEVN;
    __IO uint32_t MD_PHYM;
    __IO uint32_t MD_PHYN;
    __IO uint32_t MD_TANM;
    __IO uint32_t MD_TO;
    __IO uint32_t MD_UDR;
    __IO uint32_t MD_OVR;
    __IO uint32_t MD_RBNE;
    uint32_t RESERVED0[3];
    __IO uint32_t MD_BUSY;
    uint32_t RESERVED1[15];
} stc_mdio_mdsta_bit_t;

typedef struct {
    __IO uint32_t MD_WRFIE;
    __IO uint32_t MD_ADRFIE;
    __IO uint32_t MD_INCFIE;
    __IO uint32_t MD_RDFIE;
    __IO uint32_t MD_DEVMIE;
    __IO uint32_t MD_DEVNIE;
    __IO uint32_t MD_PHYMIE;
    __IO uint32_t MD_PHYNIE;
    __IO uint32_t MD_TANMIE;
    __IO uint32_t MD_TOIE;
    __IO uint32_t MD_UDRIE;
    __IO uint32_t MD_OVRIE;
    __IO uint32_t MD_RBNEIE;
    uint32_t RESERVED0[19];
} stc_mdio_mdien_bit_t;

typedef struct {
    uint32_t RESERVED0[16];
    __IO uint32_t TOEN;
    uint32_t RESERVED1[15];
} stc_mdio_mdto_bit_t;

typedef struct {
    __I  uint32_t SMPU1EAF;
    __I  uint32_t SMPU2EAF;
    __I  uint32_t FMPUEAF;
    __I  uint32_t PSPEF;
    __I  uint32_t MSPEF;
    uint32_t RESERVED0[27];
} stc_mpu_sr_bit_t;

typedef struct {
    __O  uint32_t SMPU1ECLR;
    __O  uint32_t SMPU2ECLR;
    __O  uint32_t FMPUECLR;
    __O  uint32_t PSPECLR;
    __O  uint32_t MSPECLR;
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
    uint32_t RESERVED0[30];
    __IO uint32_t MSPPACT;
    __IO uint32_t MSPPE;
} stc_mpu_msppctl_bit_t;

typedef struct {
    uint32_t RESERVED0[30];
    __IO uint32_t PSPPACT;
    __IO uint32_t PSPPE;
} stc_mpu_psppctl_bit_t;

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
    __IO uint32_t OTSST;
    __IO uint32_t OTSCK;
    __IO uint32_t OTSIE;
    __IO uint32_t TSSTP;
    uint32_t RESERVED0[12];
} stc_ots_ctl_bit_t;

typedef struct {
    __IO uint32_t USBFS_DFB;
    __IO uint32_t USBFS_SOFEN;
    __IO uint32_t USBFS_WKUP;
    __IO uint32_t USBFS_DMPD;
    __IO uint32_t USBFS_DPPD;
    __IO uint32_t USBFS_PDEN;
    uint32_t RESERVED0[12];
    __IO uint32_t USBFS_NFE;
    uint32_t RESERVED1[13];
} stc_peric_usb_syctlreg_bit_t;

typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t SMCEN;
    uint32_t RESERVED1[30];
} stc_peric_smc_enar_bit_t;

typedef struct {
    __IO uint32_t CAN1FDE;
    __IO uint32_t CAN2FDE;
    __IO uint32_t CAN3FDE;
    uint32_t RESERVED0[15];
    __IO uint32_t USBFS_NFE;
    uint32_t RESERVED1[13];
} stc_peric_can_syctlreg_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t USART1_NFE;
    uint32_t RESERVED1[29];
} stc_peric_usart1_nfc_bit_t;

typedef struct {
    uint32_t RESERVED0[14];
    __IO uint32_t MUX1_4;
    __IO uint32_t MUX0_4;
    uint32_t RESERVED1[16];
} stc_pla_muxs_bit_t;

typedef struct {
    uint32_t RESERVED0[6];
    __IO uint32_t OEN;
    __IO uint32_t OSEL;
    uint32_t RESERVED1[24];
} stc_pla_ctl_bit_t;

typedef struct {
    __IO uint32_t SRAMH;
    uint32_t RESERVED0[3];
    __IO uint32_t SRAM0;
    uint32_t RESERVED1[5];
    __IO uint32_t SRAMRET;
    __IO uint32_t PLA;
    uint32_t RESERVED2[1];
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
    uint32_t RESERVED3[5];
} stc_pwc_fcg0_bit_t;

typedef struct {
    __IO uint32_t CAN1;
    __IO uint32_t CAN2;
    __IO uint32_t CAN3;
    __IO uint32_t QSPI;
    __IO uint32_t I2C1;
    __IO uint32_t I2C2;
    __IO uint32_t I2C3;
    uint32_t RESERVED0[1];
    __IO uint32_t MDIO;
    uint32_t RESERVED1[7];
    __IO uint32_t SPI1;
    __IO uint32_t SPI2;
    __IO uint32_t SPI3;
    __IO uint32_t SPI4;
    uint32_t RESERVED2[2];
    __IO uint32_t USBFS;
    uint32_t RESERVED3[1];
    __IO uint32_t FMAC1;
    __IO uint32_t FMAC2;
    __IO uint32_t FMAC3;
    __IO uint32_t FMAC4;
    uint32_t RESERVED4[4];
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
    __IO uint32_t TMR6_9;
    __IO uint32_t TMR6_10;
    __IO uint32_t TMR4;
    uint32_t RESERVED0[1];
    __IO uint32_t TMR0_1;
    __IO uint32_t TMR0_2;
    uint32_t RESERVED1[1];
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
    uint32_t RESERVED2[6];
} stc_pwc_fcg2_bit_t;

typedef struct {
    __IO uint32_t ADC1;
    __IO uint32_t ADC2;
    __IO uint32_t ADC3;
    __IO uint32_t CMBIAS;
    __IO uint32_t DAC1;
    __IO uint32_t DAC2;
    __IO uint32_t DAC3;
    __IO uint32_t DAC4;
    __IO uint32_t CMP12;
    __IO uint32_t CMP34;
    uint32_t RESERVED0[2];
    __IO uint32_t OTS;
    __IO uint32_t VREF;
    uint32_t RESERVED1[2];
    __IO uint32_t SMC;
    uint32_t RESERVED2[3];
    __IO uint32_t USART1;
    __IO uint32_t USART2;
    __IO uint32_t USART3;
    __IO uint32_t USART4;
    __IO uint32_t USART5;
    __IO uint32_t USART6;
    uint32_t RESERVED3[6];
} stc_pwc_fcg3_bit_t;

typedef struct {
    __IO uint32_t PRT0;
    uint32_t RESERVED0[31];
} stc_pwc_fcg0pc_bit_t;

typedef struct {
    uint32_t RESERVED0[12];
    __IO uint32_t WKOVF;
    uint32_t RESERVED1[2];
    __IO uint32_t WKTCE;
} stc_pwc_wktcr_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
    __IO uint32_t PWDN;
} stc_pwc_pwrc0_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t VHRCSD;
    uint32_t RESERVED1[5];
} stc_pwc_pwrc1_bit_t;

typedef struct {
    uint32_t RESERVED0[7];
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
    __IO uint32_t VVDRSD;
    __IO uint32_t RETRAMSD;
    uint32_t RESERVED0[5];
    __IO uint32_t CSDIS;
} stc_pwc_pwrc5_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t IORTNCLR;
    uint32_t RESERVED1[1];
    __IO uint32_t SWRDAC;
    __IO uint32_t WDRDAC;
    __IO uint32_t SWRTNE;
    __IO uint32_t WDRTNE;
} stc_pwc_pwrc6_bit_t;

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
    __IO uint32_t RAMPDC0;
    uint32_t RESERVED0[9];
    __IO uint32_t RAMPDC10;
    uint32_t RESERVED1[21];
} stc_pwc_rampc0_bit_t;

typedef struct {
    __IO uint32_t PRAMPDC0;
    __IO uint32_t PRAMPDC1;
    __IO uint32_t PRAMPDC2;
    __IO uint32_t PRAMPDC3;
    uint32_t RESERVED0[28];
} stc_pwc_pramlpc_bit_t;

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
    uint32_t RESERVED0[11];
    __IO uint32_t PLA;
    uint32_t RESERVED1[1];
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
    uint32_t RESERVED2[5];
} stc_rmu_frst0_bit_t;

typedef struct {
    uint32_t RESERVED0[3];
    __IO uint32_t QSPI;
    uint32_t RESERVED1[4];
    __IO uint32_t MDIO;
    uint32_t RESERVED2[7];
    __IO uint32_t SPI1;
    __IO uint32_t SPI2;
    __IO uint32_t SPI3;
    __IO uint32_t SPI4;
    uint32_t RESERVED3[2];
    __IO uint32_t USBFS;
    uint32_t RESERVED4[1];
    __IO uint32_t FMAC1;
    __IO uint32_t FMAC2;
    __IO uint32_t FMAC3;
    __IO uint32_t FMAC4;
    uint32_t RESERVED5[4];
} stc_rmu_frst1_bit_t;

typedef struct {
    __IO uint32_t TMR6;
    uint32_t RESERVED0[9];
    __IO uint32_t TMR4;
    uint32_t RESERVED1[1];
    __IO uint32_t TMR0;
    uint32_t RESERVED2[2];
    __IO uint32_t EMB;
    __IO uint32_t TMR2;
    uint32_t RESERVED3[3];
    __IO uint32_t TMRA;
    uint32_t RESERVED4[11];
} stc_rmu_frst2_bit_t;

typedef struct {
    __IO uint32_t ADC1;
    __IO uint32_t ADC2;
    __IO uint32_t ADC3;
    uint32_t RESERVED0[1];
    __IO uint32_t DAC1;
    __IO uint32_t DAC2;
    __IO uint32_t DAC3;
    __IO uint32_t DAC4;
    __IO uint32_t CMP12;
    __IO uint32_t CMP34;
    uint32_t RESERVED1[2];
    __IO uint32_t OTS;
    __IO uint32_t VREF;
    uint32_t RESERVED2[2];
    __IO uint32_t SMC;
    uint32_t RESERVED3[3];
    __IO uint32_t USART1;
    __IO uint32_t USART2;
    __IO uint32_t USART3;
    __IO uint32_t USART4;
    __IO uint32_t USART5;
    __IO uint32_t USART6;
    uint32_t RESERVED4[6];
} stc_rmu_frst3_bit_t;

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
} stc_spi_cr_bit_t;

typedef struct {
    uint32_t RESERVED0[2];
    __IO uint32_t CTMDS;
    uint32_t RESERVED1[3];
    __IO uint32_t SPRDTD;
    uint32_t RESERVED2[1];
    __IO uint32_t SS0PV;
    __IO uint32_t SS1PV;
    __IO uint32_t SS2PV;
    __IO uint32_t SS3PV;
    uint32_t RESERVED3[20];
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
    uint32_t RESERVED0[3];
    __IO uint32_t SRAMH_PYERR;
    __IO uint32_t SRAM0_1ERR;
    __IO uint32_t SRAM0_2ERR;
    __IO uint32_t SRAMB_1ERR;
    __IO uint32_t SRAMB_2ERR;
    __IO uint32_t CACHE_PYERR;
    uint32_t RESERVED1[23];
} stc_sramc_cksr_bit_t;

typedef struct {
    __IO uint32_t EIEN;
    uint32_t RESERVED0[31];
} stc_sramc_sram0_eien_bit_t;

typedef struct {
    __IO uint32_t EIEN;
    uint32_t RESERVED0[31];
} stc_sramc_sramb_eien_bit_t;

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
    __IO uint32_t ICPA;
    uint32_t RESERVED0[14];
    __IO uint32_t CMFB;
    __IO uint32_t ICPB;
    uint32_t RESERVED1[14];
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
    __IO uint32_t ICPA;
    uint32_t RESERVED0[13];
    __IO uint32_t CMFB;
    __IO uint32_t OVFB;
    __IO uint32_t ICPB;
    uint32_t RESERVED1[13];
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
    __IO uint32_t IRQZEN;
    __IO uint32_t IRQZF;
    uint32_t RESERVED1[1];
    __IO uint32_t HST;
    uint32_t RESERVED2[1];
    __IO uint32_t ECKEN;
} stc_tmr4_ccsr_bit_t;

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
    uint32_t RESERVED0[3];
    __IO uint32_t PCTS;
    uint32_t RESERVED1[12];
} stc_tmr4_scer_bit_t;

typedef struct {
    __IO uint32_t ITEN0;
    __IO uint32_t ITEN1;
    __IO uint32_t ITEN2;
    __IO uint32_t ITEN3;
    __IO uint32_t ITEN4;
    __IO uint32_t ITEN5;
    uint32_t RESERVED0[10];
} stc_tmr4_scir_bit_t;

typedef struct {
    __IO uint32_t SF0;
    __IO uint32_t SF1;
    __IO uint32_t SF2;
    __IO uint32_t SF3;
    __IO uint32_t SF4;
    __IO uint32_t SF5;
    uint32_t RESERVED0[10];
} stc_tmr4_scfr_bit_t;

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
    uint32_t RESERVED0[13];
    __IO uint32_t CMAF2;
    __IO uint32_t CMBF2;
    uint32_t RESERVED1[3];
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
} stc_tmr6_common_fcntr_bit_t;

typedef struct {
    __IO uint32_t SSTA1;
    __IO uint32_t SSTA2;
    __IO uint32_t SSTA3;
    __IO uint32_t SSTA4;
    __IO uint32_t SSTA5;
    __IO uint32_t SSTA6;
    __IO uint32_t SSTA7;
    __IO uint32_t SSTA8;
    __IO uint32_t SSTA9;
    __IO uint32_t SSTA10;
    uint32_t RESERVED0[22];
} stc_tmr6_common_sstar_bit_t;

typedef struct {
    __IO uint32_t SSTP1;
    __IO uint32_t SSTP2;
    __IO uint32_t SSTP3;
    __IO uint32_t SSTP4;
    __IO uint32_t SSTP5;
    __IO uint32_t SSTP6;
    __IO uint32_t SSTP7;
    __IO uint32_t SSTP8;
    __IO uint32_t SSTP9;
    __IO uint32_t SSTP10;
    uint32_t RESERVED0[22];
} stc_tmr6_common_sstpr_bit_t;

typedef struct {
    __IO uint32_t SCLE1;
    __IO uint32_t SCLE2;
    __IO uint32_t SCLE3;
    __IO uint32_t SCLE4;
    __IO uint32_t SCLE5;
    __IO uint32_t SCLE6;
    __IO uint32_t SCLE7;
    __IO uint32_t SCLE8;
    __IO uint32_t SCLE9;
    __IO uint32_t SCLE10;
    uint32_t RESERVED0[22];
} stc_tmr6_common_sclrr_bit_t;

typedef struct {
    __IO uint32_t SUPD1;
    __IO uint32_t SUPD2;
    __IO uint32_t SUPD3;
    __IO uint32_t SUPD4;
    __IO uint32_t SUPD5;
    __IO uint32_t SUPD6;
    __IO uint32_t SUPD7;
    __IO uint32_t SUPD8;
    __IO uint32_t SUPD9;
    __IO uint32_t SUPD10;
    uint32_t RESERVED0[22];
} stc_tmr6_common_supdr_bit_t;

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
    uint32_t RESERVED0[4];
    __IO uint32_t ICPF1;
    __IO uint32_t ICPF2;
    __IO uint32_t ICPF3;
    __IO uint32_t ICPF4;
    uint32_t RESERVED1[4];
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
    __I  uint32_t TEND;
    uint32_t RESERVED1[4];
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
    __IO uint32_t TENDIE;
    __IO uint32_t PS;
    __IO uint32_t PCE;
    uint32_t RESERVED0[1];
    __IO uint32_t M;
    uint32_t RESERVED1[2];
    __IO uint32_t OVER8;
    __IO uint32_t CPE;
    __IO uint32_t CFE;
    uint32_t RESERVED2[1];
    __IO uint32_t CORE;
    __IO uint32_t CRTOF;
    __IO uint32_t CBE;
    __IO uint32_t CWKUP;
    __IO uint32_t CLBD;
    __IO uint32_t MS;
    __IO uint32_t CTEND;
    uint32_t RESERVED3[2];
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
    uint32_t RESERVED1[23];
    __IO uint32_t CSFTRSTDONE;
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
    __IO uint32_t BGREN;
    uint32_t RESERVED0[31];
} stc_vref_bgrcr_bit_t;

typedef struct {
    __IO uint32_t CSEN;
    uint32_t RESERVED0[31];
} stc_vref_cscr_bit_t;

typedef struct {
    __IO uint32_t AVCCMONEN;
    __IO uint32_t VREFINTEN;
    __IO uint32_t IVREFEN;
    __IO uint32_t HIZ;
    uint32_t RESERVED0[28];
} stc_vref_cr_bit_t;

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
    uint32_t                                 RESERVED2[448];
    stc_adc_isr_bit_t                        ISR_b;
    stc_adc_icr_bit_t                        ICR_b;
    stc_adc_isclrr_bit_t                     ISCLRR_b;
    uint32_t                                 RESERVED3[40];
    stc_adc_synccr_bit_t                     SYNCCR_b;
    uint32_t                                 RESERVED4[656];
    stc_adc_awdcr_bit_t                      AWDCR_b;
    stc_adc_awdsr_bit_t                      AWDSR_b;
    stc_adc_awdsclrr_bit_t                   AWDSCLRR_b;
    uint32_t                                 RESERVED5[256];
    stc_adc_pgavssenr_bit_t                  PGAVSSENR_b;
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
    stc_cmp_omr_bit_t                        OMR_b;
    uint32_t                                 RESERVED0[96];
    stc_cmp_bwsr1_bit_t                      BWSR1_b;
} bCM_CMP_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[224];
    stc_cmu_xtaldivcr_bit_t                  XTALDIVCR_b;
    uint32_t                                 RESERVED1[156032];
    stc_cmu_xtalcfgr_bit_t                   XTALCFGR_b;
    uint32_t                                 RESERVED2[24];
    stc_cmu_xtal32cr_bit_t                   XTAL32CR_b;
    uint32_t                                 RESERVED3[184];
    stc_cmu_lrccr_bit_t                      LRCCR_b;
    uint32_t                                 RESERVED4[237032];
    stc_cmu_pllhcr_bit_t                     PLLHCR_b;
    uint32_t                                 RESERVED5[56];
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
    uint32_t                                 RESERVED2[928];
    stc_efm_wlock_bit_t                      WLOCK_b;
    uint32_t                                 RESERVED3[96];
    stc_efm_f0nwprt_bit_t                    F0NWPRT_b;
    uint32_t                                 RESERVED4[96];
    stc_efm_f1nwprt_bit_t                    F1NWPRT_b;
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
    uint32_t                                 RESERVED11[7408];
    stc_gpio_pwpr_bit_t                      PWPR_b;
    uint32_t                                 RESERVED12[16];
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
    uint32_t                                 RESERVED0[32];
    stc_i2c_sr_bit_t                         SR_b;
    stc_i2c_clr_bit_t                        CLR_b;
    uint32_t                                 RESERVED1[64];
    stc_i2c_ccr_bit_t                        CCR_b;
    stc_i2c_fltr_bit_t                       FLTR_b;
    stc_i2c_fstr_bit_t                       FSTR_b;
} bCM_I2C_TypeDef;

typedef struct {
    stc_icg_icg0_bit_t                       ICG0_b;
    stc_icg_icg1_bit_t                       ICG1_b;
} bCM_ICG_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_intc_nmier_bit_t                     NMIER_b;
    stc_intc_nmifr_bit_t                     NMIFR_b;
    stc_intc_nmifcr_bit_t                    NMIFCR_b;
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
    stc_intc_wken_bit_t                      WKEN_b;
    stc_intc_eifr_bit_t                      EIFR_b;
    stc_intc_eifcr_bit_t                     EIFCR_b;
    uint32_t                                 RESERVED1[4608];
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
    stc_mdio_mdcon_bit_t                     MDCON_b;
    stc_mdio_mdcon1_bit_t                    MDCON1_b;
    uint32_t                                 RESERVED0[160];
    stc_mdio_mdsta_bit_t                     MDSTA_b;
    stc_mdio_mdien_bit_t                     MDIEN_b;
    uint32_t                                 RESERVED1[32];
    stc_mdio_mdto_bit_t                      MDTO_b;
} bCM_MDIO_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[512];
    stc_mpu_sr_bit_t                         SR_b;
    stc_mpu_eclr_bit_t                       ECLR_b;
    stc_mpu_wp_bit_t                         WP_b;
    stc_mpu_ippr_bit_t                       IPPR_b;
    uint32_t                                 RESERVED1[32];
    stc_mpu_msppctl_bit_t                    MSPPCTL_b;
    uint32_t                                 RESERVED2[32];
    stc_mpu_psppctl_bit_t                    PSPPCTL_b;
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
} bCM_MPU_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[1904640];
    stc_ots_ctl_bit_t                        CTL_b;
} bCM_OTS_TypeDef;

typedef struct {
    stc_peric_usb_syctlreg_bit_t             USB_SYCTLREG_b;
    uint32_t                                 RESERVED0[64];
    stc_peric_smc_enar_bit_t                 SMC_ENAR_b;
    uint32_t                                 RESERVED1[64];
    stc_peric_can_syctlreg_bit_t             CAN_SYCTLREG_b;
    stc_peric_usart1_nfc_bit_t               USART1_NFC_b;
} bCM_PERIC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[128];
    stc_pla_muxs_bit_t                       MUXS0_b;
    uint32_t                                 RESERVED1[32];
    stc_pla_ctl_bit_t                        CTL0_b;
    stc_pla_muxs_bit_t                       MUXS1_b;
    uint32_t                                 RESERVED2[32];
    stc_pla_ctl_bit_t                        CTL1_b;
    stc_pla_muxs_bit_t                       MUXS2_b;
    uint32_t                                 RESERVED3[32];
    stc_pla_ctl_bit_t                        CTL2_b;
    stc_pla_muxs_bit_t                       MUXS3_b;
    uint32_t                                 RESERVED4[32];
    stc_pla_ctl_bit_t                        CTL3_b;
    stc_pla_muxs_bit_t                       MUXS4_b;
    uint32_t                                 RESERVED5[32];
    stc_pla_ctl_bit_t                        CTL4_b;
    stc_pla_muxs_bit_t                       MUXS5_b;
    uint32_t                                 RESERVED6[32];
    stc_pla_ctl_bit_t                        CTL5_b;
    stc_pla_muxs_bit_t                       MUXS6_b;
    uint32_t                                 RESERVED7[32];
    stc_pla_ctl_bit_t                        CTL6_b;
    stc_pla_muxs_bit_t                       MUXS7_b;
    uint32_t                                 RESERVED8[32];
    stc_pla_ctl_bit_t                        CTL7_b;
    stc_pla_muxs_bit_t                       MUXS8_b;
    uint32_t                                 RESERVED9[32];
    stc_pla_ctl_bit_t                        CTL8_b;
    stc_pla_muxs_bit_t                       MUXS9_b;
    uint32_t                                 RESERVED10[32];
    stc_pla_ctl_bit_t                        CTL9_b;
    stc_pla_muxs_bit_t                       MUXS10_b;
    uint32_t                                 RESERVED11[32];
    stc_pla_ctl_bit_t                        CTL10_b;
    stc_pla_muxs_bit_t                       MUXS11_b;
    uint32_t                                 RESERVED12[32];
    stc_pla_ctl_bit_t                        CTL11_b;
    stc_pla_muxs_bit_t                       MUXS12_b;
    uint32_t                                 RESERVED13[32];
    stc_pla_ctl_bit_t                        CTL12_b;
    stc_pla_muxs_bit_t                       MUXS13_b;
    uint32_t                                 RESERVED14[32];
    stc_pla_ctl_bit_t                        CTL13_b;
    stc_pla_muxs_bit_t                       MUXS14_b;
    uint32_t                                 RESERVED15[32];
    stc_pla_ctl_bit_t                        CTL14_b;
    stc_pla_muxs_bit_t                       MUXS15_b;
    uint32_t                                 RESERVED16[32];
    stc_pla_ctl_bit_t                        CTL15_b;
} bCM_PLA_TypeDef;

typedef struct {
    stc_pwc_fcg0_bit_t                       FCG0_b;
    stc_pwc_fcg1_bit_t                       FCG1_b;
    stc_pwc_fcg2_bit_t                       FCG2_b;
    stc_pwc_fcg3_bit_t                       FCG3_b;
    stc_pwc_fcg0pc_bit_t                     FCG0PC_b;
    uint32_t                                 RESERVED0[139104];
    stc_pwc_wktcr_bit_t                      WKTCR_b;
    uint32_t                                 RESERVED1[16368];
    stc_pwc_pwrc0_bit_t                      PWRC0_b;
    uint32_t                                 RESERVED2[24];
    stc_pwc_pwrc1_bit_t                      PWRC1_b;
    uint32_t                                 RESERVED3[88];
    stc_pwc_pwrc4_bit_t                      PWRC4_b;
    uint32_t                                 RESERVED4[24];
    stc_pwc_pvdcr0_bit_t                     PVDCR0_b;
    uint32_t                                 RESERVED5[24];
    stc_pwc_pvdcr1_bit_t                     PVDCR1_b;
    uint32_t                                 RESERVED6[24];
    stc_pwc_pvdfcr_bit_t                     PVDFCR_b;
    uint32_t                                 RESERVED7[88];
    stc_pwc_pdwke0_bit_t                     PDWKE0_b;
    uint32_t                                 RESERVED8[24];
    stc_pwc_pdwke1_bit_t                     PDWKE1_b;
    uint32_t                                 RESERVED9[24];
    stc_pwc_pdwke2_bit_t                     PDWKE2_b;
    uint32_t                                 RESERVED10[24];
    stc_pwc_pdwkes_bit_t                     PDWKES_b;
    uint32_t                                 RESERVED11[24];
    stc_pwc_pdwkf0_bit_t                     PDWKF0_b;
    uint32_t                                 RESERVED12[24];
    stc_pwc_pdwkf1_bit_t                     PDWKF1_b;
    uint32_t                                 RESERVED13[24];
    stc_pwc_pwrc5_bit_t                      PWRC5_b;
    uint32_t                                 RESERVED14[24];
    stc_pwc_pwrc6_bit_t                      PWRC6_b;
    uint32_t                                 RESERVED15[984];
    stc_pwc_pvdicr_bit_t                     PVDICR_b;
    uint32_t                                 RESERVED16[24];
    stc_pwc_pvddsr_bit_t                     PVDDSR_b;
    uint32_t                                 RESERVED17[24];
    stc_pwc_rampc0_bit_t                     RAMPC0_b;
    uint32_t                                 RESERVED18[32];
    stc_pwc_pramlpc_bit_t                    PRAMLPC_b;
    uint32_t                                 RESERVED19[235968];
    stc_pwc_stpmcr_bit_t                     STPMCR_b;
    uint32_t                                 RESERVED20[8064];
    stc_pwc_fprc_bit_t                       FPRC_b;
} bCM_PWC_TypeDef;

typedef struct {
    stc_rmu_frst0_bit_t                      FRST0_b;
    stc_rmu_frst1_bit_t                      FRST1_b;
    stc_rmu_frst2_bit_t                      FRST2_b;
    stc_rmu_frst3_bit_t                      FRST3_b;
    stc_rmu_prstcr0_bit_t                    PRSTCR0_b;
    uint32_t                                 RESERVED0[24];
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
} bCM_RTC_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[32];
    stc_spi_cr_bit_t                         CR_b;
    uint32_t                                 RESERVED1[32];
    stc_spi_cfg1_bit_t                       CFG1_b;
    uint32_t                                 RESERVED2[32];
    stc_spi_sr_bit_t                         SR_b;
    stc_spi_cfg2_bit_t                       CFG2_b;
} bCM_SPI_TypeDef;

typedef struct {
    uint32_t                                 RESERVED0[64];
    stc_sramc_ckcr_bit_t                     CKCR_b;
    stc_sramc_ckpr_bit_t                     CKPR_b;
    stc_sramc_cksr_bit_t                     CKSR_b;
    stc_sramc_sram0_eien_bit_t               SRAM0_EIEN_b;
    uint32_t                                 RESERVED1[96];
    stc_sramc_sramb_eien_bit_t               SRAMB_EIEN_b;
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
    stc_tmr4_ocmrh_bit_t                     OCMRUH_b;
    uint32_t                                 RESERVED1[16];
    stc_tmr4_ocmrl_bit_t                     OCMRUL_b;
    stc_tmr4_ocmrh_bit_t                     OCMRVH_b;
    uint32_t                                 RESERVED2[16];
    stc_tmr4_ocmrl_bit_t                     OCMRVL_b;
    stc_tmr4_ocmrh_bit_t                     OCMRWH_b;
    uint32_t                                 RESERVED3[16];
    stc_tmr4_ocmrl_bit_t                     OCMRWL_b;
    uint32_t                                 RESERVED4[96];
    stc_tmr4_ccsr_bit_t                      CCSR_b;
    uint32_t                                 RESERVED5[16];
    stc_tmr4_pscr_bit_t                      PSCR_b;
    uint32_t                                 RESERVED6[672];
    stc_tmr4_rcsr_bit_t                      RCSR_b;
    uint32_t                                 RESERVED7[272];
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
    stc_tmr4_scer_bit_t                      SCER_b;
    uint32_t                                 RESERVED8[16];
    stc_tmr4_scir_bit_t                      SCIR_b;
    uint32_t                                 RESERVED9[16];
    stc_tmr4_scfr_bit_t                      SCFR_b;
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
    uint32_t                                 RESERVED0[1888];
    stc_tmr6_common_fcntr_bit_t              FCNTR_b;
    stc_tmr6_common_sstar_bit_t              SSTAR_b;
    stc_tmr6_common_sstpr_bit_t              SSTPR_b;
    stc_tmr6_common_sclrr_bit_t              SCLRR_b;
    stc_tmr6_common_supdr_bit_t              SUPDR_b;
} bCM_TMR6_COMMON_TypeDef;

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
    stc_vref_bgrcr_bit_t                     BGRCR_b;
    stc_vref_cscr_bit_t                      CSCR_b;
    stc_vref_cr_bit_t                        CR_b;
} bCM_VREF_TypeDef;

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
#define bCM_CAN1                             ((bCM_CAN_TypeDef *)0x42F00000UL)
#define bCM_CAN2                             ((bCM_CAN_TypeDef *)0x42E28000UL)
#define bCM_CAN3                             ((bCM_CAN_TypeDef *)0x42E20000UL)
#define bCM_CMP1                             ((bCM_CMP_TypeDef *)0x42708000UL)
#define bCM_CMP2                             ((bCM_CMP_TypeDef *)0x4270A000UL)
#define bCM_CMP3                             ((bCM_CMP_TypeDef *)0x42760000UL)
#define bCM_CMP4                             ((bCM_CMP_TypeDef *)0x42762000UL)
#define bCM_CMU                              ((bCM_CMU_TypeDef *)0x42900000UL)
#define bCM_CRC                              ((bCM_CRC_TypeDef *)0x42118000UL)
#define bCM_CTC                              ((bCM_CTC_TypeDef *)0x42938000UL)
#define bCM_DAC1                             ((bCM_DAC_TypeDef *)0x42820000UL)
#define bCM_DAC2                             ((bCM_DAC_TypeDef *)0x42828000UL)
#define bCM_DAC3                             ((bCM_DAC_TypeDef *)0x42830000UL)
#define bCM_DAC4                             ((bCM_DAC_TypeDef *)0x42838000UL)
#define bCM_DCU1                             ((bCM_DCU_TypeDef *)0x42AC0000UL)
#define bCM_DCU2                             ((bCM_DCU_TypeDef *)0x42AC8000UL)
#define bCM_DCU3                             ((bCM_DCU_TypeDef *)0x42AD0000UL)
#define bCM_DMA1                             ((bCM_DMA_TypeDef *)0x42A60000UL)
#define bCM_DMA2                             ((bCM_DMA_TypeDef *)0x42A68000UL)
#define bCM_EFM                              ((bCM_EFM_TypeDef *)0x42208000UL)
#define bCM_EMB0                             ((bCM_EMB_TypeDef *)0x422F8000UL)
#define bCM_EMB1                             ((bCM_EMB_TypeDef *)0x422F8400UL)
#define bCM_EMB2                             ((bCM_EMB_TypeDef *)0x422F8800UL)
#define bCM_EMB3                             ((bCM_EMB_TypeDef *)0x422F8C00UL)
#define bCM_EMB4                             ((bCM_EMB_TypeDef *)0x422F9000UL)
#define bCM_EMB5                             ((bCM_EMB_TypeDef *)0x422F9400UL)
#define bCM_EMB6                             ((bCM_EMB_TypeDef *)0x422F9800UL)
#define bCM_FCM                              ((bCM_FCM_TypeDef *)0x42908000UL)
#define bCM_FMAC1                            ((bCM_FMAC_TypeDef *)0x42B00000UL)
#define bCM_FMAC2                            ((bCM_FMAC_TypeDef *)0x42B08000UL)
#define bCM_FMAC3                            ((bCM_FMAC_TypeDef *)0x42B10000UL)
#define bCM_FMAC4                            ((bCM_FMAC_TypeDef *)0x42B18000UL)
#define bCM_GPIO                             ((bCM_GPIO_TypeDef *)0x42A70000UL)
#define bCM_HASH                             ((bCM_HASH_TypeDef *)0x42108000UL)
#define bCM_I2C1                             ((bCM_I2C_TypeDef *)0x42768000UL)
#define bCM_I2C2                             ((bCM_I2C_TypeDef *)0x42770000UL)
#define bCM_I2C3                             ((bCM_I2C_TypeDef *)0x42778000UL)
#define bCM_INTC                             ((bCM_INTC_TypeDef *)0x42A20000UL)
#define bCM_KEYSCAN                          ((bCM_KEYSCAN_TypeDef *)0x42A18000UL)
#define bCM_MAU                              ((bCM_MAU_TypeDef *)0x42AA0000UL)
#define bCM_MDIO                             ((bCM_MDIO_TypeDef *)0x42508000UL)
#define bCM_MPU                              ((bCM_MPU_TypeDef *)0x42A00000UL)
#define bCM_OTS                              ((bCM_OTS_TypeDef *)0x4220C000UL)
#define bCM_PERIC                            ((bCM_PERIC_TypeDef *)0x42AA8000UL)
#define bCM_PLA                              ((bCM_PLA_TypeDef *)0x429F8000UL)
#define bCM_PWC                              ((bCM_PWC_TypeDef *)0x42900000UL)
#define bCM_RMU                              ((bCM_RMU_TypeDef *)0x42999C00UL)
#define bCM_RTC                              ((bCM_RTC_TypeDef *)0x42980000UL)
#define bCM_SPI1                             ((bCM_SPI_TypeDef *)0x42380000UL)
#define bCM_SPI2                             ((bCM_SPI_TypeDef *)0x42388000UL)
#define bCM_SPI3                             ((bCM_SPI_TypeDef *)0x42400000UL)
#define bCM_SPI4                             ((bCM_SPI_TypeDef *)0x42408000UL)
#define bCM_SRAMC                            ((bCM_SRAMC_TypeDef *)0x42A10000UL)
#define bCM_SWDT                             ((bCM_SWDT_TypeDef *)0x42928000UL)
#define bCM_TMR0_1                           ((bCM_TMR0_TypeDef *)0x42480000UL)
#define bCM_TMR0_2                           ((bCM_TMR0_TypeDef *)0x42488000UL)
#define bCM_TMR2_1                           ((bCM_TMR2_TypeDef *)0x42490000UL)
#define bCM_TMR2_2                           ((bCM_TMR2_TypeDef *)0x42498000UL)
#define bCM_TMR2_3                           ((bCM_TMR2_TypeDef *)0x424A0000UL)
#define bCM_TMR2_4                           ((bCM_TMR2_TypeDef *)0x424A8000UL)
#define bCM_TMR4                             ((bCM_TMR4_TypeDef *)0x42700000UL)
#define bCM_TMR6_1                           ((bCM_TMR6_TypeDef *)0x42780000UL)
#define bCM_TMR6_10                          ((bCM_TMR6_TypeDef *)0x427C8000UL)
#define bCM_TMR6_2                           ((bCM_TMR6_TypeDef *)0x42788000UL)
#define bCM_TMR6_3                           ((bCM_TMR6_TypeDef *)0x42790000UL)
#define bCM_TMR6_4                           ((bCM_TMR6_TypeDef *)0x42798000UL)
#define bCM_TMR6_5                           ((bCM_TMR6_TypeDef *)0x427A0000UL)
#define bCM_TMR6_6                           ((bCM_TMR6_TypeDef *)0x427A8000UL)
#define bCM_TMR6_7                           ((bCM_TMR6_TypeDef *)0x427B0000UL)
#define bCM_TMR6_8                           ((bCM_TMR6_TypeDef *)0x427B8000UL)
#define bCM_TMR6_9                           ((bCM_TMR6_TypeDef *)0x427C0000UL)
#define bCM_TMR6_COMMON                      ((bCM_TMR6_COMMON_TypeDef *)0x42786000UL)
#define bCM_TMRA_1                           ((bCM_TMRA_TypeDef *)0x42740000UL)
#define bCM_TMRA_2                           ((bCM_TMRA_TypeDef *)0x42748000UL)
#define bCM_TMRA_3                           ((bCM_TMRA_TypeDef *)0x42750000UL)
#define bCM_TMRA_4                           ((bCM_TMRA_TypeDef *)0x42758000UL)
#define bCM_TMRA_5                           ((bCM_TMRA_TypeDef *)0x424C0000UL)
#define bCM_TMRA_6                           ((bCM_TMRA_TypeDef *)0x424C8000UL)
#define bCM_TRNG                             ((bCM_TRNG_TypeDef *)0x42840000UL)
#define bCM_USART1                           ((bCM_USART_TypeDef *)0x42398000UL)
#define bCM_USART2                           ((bCM_USART_TypeDef *)0x423A0000UL)
#define bCM_USART3                           ((bCM_USART_TypeDef *)0x423A8000UL)
#define bCM_USART4                           ((bCM_USART_TypeDef *)0x42418000UL)
#define bCM_USART5                           ((bCM_USART_TypeDef *)0x42420000UL)
#define bCM_USART6                           ((bCM_USART_TypeDef *)0x42428000UL)
#define bCM_USBFS                            ((bCM_USBFS_TypeDef *)0x43000000UL)
#define bCM_VREF                             ((bCM_VREF_TypeDef *)0x429F0000UL)
#define bCM_WDT                              ((bCM_WDT_TypeDef *)0x42920000UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32F472_H__ */
