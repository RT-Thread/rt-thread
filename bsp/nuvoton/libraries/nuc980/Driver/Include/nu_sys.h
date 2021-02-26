/**************************************************************************//**
 * @file     sys.h
 * @brief    SYS driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef __NU_SYS_H__
#define __NU_SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SYS_Driver SYS Driver
  @{
*/


/** @addtogroup SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/


/**
 * @details  Interrupt Number Definition.
 */
typedef enum IRQn
{
    IRQ_WDT = 1,        // Watch Dog Timer
    IRQ_WWDT = 2,       // Windowed-WDT Interrupt
    IRQ_LVD = 3,        // LVD Interrupt
    IRQ_EXTI0 = 4,      // External Interrupt 0
    IRQ_EXTI1 = 5,      // External Interrupt 1
    IRQ_EXTI2 = 6,      // External Interrupt 2
    IRQ_EXTI3 = 7,      // External Interrupt 3
    IRQ_GPA = 8,        // GPA Interrupt
    IRQ_GPB = 9,        // GPB Interrupt
    IRQ_GPC = 10,       // GPC Interrupt
    IRQ_GPD = 11,       // GPD Interrupt
    IRQ_I2S = 12,       // I2S Interrupt
    IRQ_CAP0 = 14,      // Sensor Interface Controller Interrupt
    IRQ_RTC = 15,       // RTC interrupt
    IRQ_TIMER0 = 16,    // Timer 0 interrupt
    IRQ_TIMER1 = 17,    // Timer 1 interrupt
    IRQ_ADC = 18,       // ADC interrupt
    IRQ_EMC0_RX = 19,   // EMC 0 RX Interrupt
    IRQ_EMC1_RX = 20,   // EMC 1 RX Interrupt
    IRQ_EMC0_TX = 21,   // EMC 0 TX Interrupt
    IRQ_EMC1_TX = 22,   // EMC 1 TX Interrupt
    IRQ_EHCI = 23,      // USB 2.0 Host Controller Interrupt
    IRQ_OHCI = 24,      // USB 1.1 Host Controller Interrupt
    IRQ_PDMA0 = 25,     // PDMA Channel 0 Interrupt
    IRQ_PDMA1 = 26,     // PDMA Channel 1 Interrupt
    IRQ_SDH = 27,       // SD Host Interrupt
    IRQ_FMI = 28,       // NAND/eMMC Interrupt
    IRQ_UDC = 29,       // USB Device Controller Interrupt
    IRQ_TIMER2 = 30,    // Timer 2 interrupt
    IRQ_TIMER3 = 31,    // Timer 3 interrupt
    IRQ_TIMER4 = 32,    // Timer 4 interrupt
    IRQ_CAP1 = 33,      // VCAP1 Engine Interrupt
    IRQ_TIMER5 = 34,    // Timer 5 interrupt
    IRQ_CRYPTO = 35,    // CRYPTO Engine Interrupt
    IRQ_UART0 = 36,     // UART 0 interrupt
    IRQ_UART1 = 37,     // UART 1 interrupt
    IRQ_UART2 = 38,     // UART 2 interrupt
    IRQ_UART4 = 39,     // UART 4 interrupt
    IRQ_UART6 = 40,     // UART 6 interrupt
    IRQ_UART8 = 41,     // UART 8 interrupt
    IRQ_CAN3  = 42,     // CAN  3 interrupt
    IRQ_UART3 = 43,     // UART 3 interrupt
    IRQ_UART5 = 44,     // UART 5 interrupt
    IRQ_UART7 = 45,     // UART 7 interrupt
    IRQ_UART9 = 46,     // UART 9 interrupt
    IRQ_I2C2 = 47,      // I2C 2 interrupt
    IRQ_I2C3 = 48,      // I2C 3 interrupt
    IRQ_GPE = 49,       // GPE interrupt
    IRQ_SPI1 = 50,      // SPI 1 interrupt
    IRQ_QSPI0 = 51,     // QSPI 0 interrupt
    IRQ_SPI0 = 52,      // SPI 0 interrupt
    IRQ_I2C0 = 53,      // I2C 0 Interrupt
    IRQ_I2C1 = 54,      // I2C 1 Interrupt
    IRQ_SMC0 = 55,      // SmartCard 0 Interrupt
    IRQ_SMC1 = 56,      // SmartCard 1 Interrupt
    IRQ_GPF = 57,       // GPF interrupt
    IRQ_CAN0 = 58,      // CAN 0 interrupt
    IRQ_CAN1 = 59,      // CAN 1 interrupt
    IRQ_PWM0 = 60,      // PWM 0 interrupt
    IRQ_PWM1 = 61,      // PWM 1 interrupt
    IRQ_CAN2 = 62,      // CAN 2 interrupt
    IRQ_GPG = 63,       // GPG interrupt
}
IRQn_Type;

/* Define constants for use AIC in service parameters.  */
#define SYS_SWI                     0
#define SYS_D_ABORT                 1
#define SYS_I_ABORT                 2
#define SYS_UNDEFINE                3

/* The parameters for sysSetInterruptPriorityLevel() and
   sysInstallISR() use */
#define FIQ_LEVEL_0     0       /*!< FIQ Level 0 */
#define IRQ_LEVEL_1     1       /*!< IRQ Level 1 */
#define IRQ_LEVEL_2     2       /*!< IRQ Level 2 */
#define IRQ_LEVEL_3     3       /*!< IRQ Level 3 */
#define IRQ_LEVEL_4     4       /*!< IRQ Level 4 */
#define IRQ_LEVEL_5     5       /*!< IRQ Level 5 */
#define IRQ_LEVEL_6     6       /*!< IRQ Level 6 */
#define IRQ_LEVEL_7     7       /*!< IRQ Level 7 */


/* The parameters for sysSetLocalInterrupt() use */
#define ENABLE_IRQ        0x7F  /*!< Enable I-bit of CP15  */
#define ENABLE_FIQ        0xBF  /*!< Enable F-bit of CP15  */
#define ENABLE_FIQ_IRQ    0x3F  /*!< Enable I-bit and F-bit of CP15  */
#define DISABLE_IRQ       0x80  /*!< Disable I-bit of CP15  */
#define DISABLE_FIQ       0x40  /*!< Disable F-bit of CP15  */
#define DISABLE_FIQ_IRQ   0xC0  /*!< Disable I-bit and F-bit of CP15  */

/* Define Cache type  */
#define CACHE_WRITE_BACK        0     /*!< Cache Write-back mode  */
#define CACHE_WRITE_THROUGH     1     /*!< Cache Write-through mode  */
#define CACHE_DISABLE           -1    /*!< Cache Disable  */

/** \brief  Structure type of clock source
 */
typedef enum CLKn
{

    SYS_UPLL     = 1,   /*!< UPLL clock */
    SYS_APLL     = 2,   /*!< APLL clock */
    SYS_SYSTEM   = 3,   /*!< System clock */
    SYS_HCLK     = 4,   /*!< HCLK1 clock */
    SYS_PCLK01   = 5,   /*!< HCLK234 clock */
    SYS_PCLK2    = 6,   /*!< PCLK clock */
    SYS_CPU      = 7,   /*!< CPU clock */

}  CLK_Type;

/* The parameters for sysSetInterruptType() use */
#define LOW_LEVEL_SENSITIVE        0x00
#define HIGH_LEVEL_SENSITIVE       0x40
#define NEGATIVE_EDGE_TRIGGER      0x80
#define POSITIVE_EDGE_TRIGGER      0xC0

/* The parameters for sysSetGlobalInterrupt() use */
#define ENABLE_ALL_INTERRUPTS      0
#define DISABLE_ALL_INTERRUPTS     1

#define MMU_DIRECT_MAPPING  0

/* Define constants for use Cache in service parameters.  */
#define I_CACHE         6
#define D_CACHE         7
#define I_D_CACHE       8


/// @endcond HIDDEN_SYMBOLS

/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */

/*---------------------- System Manger Controller -------------------------*/
/**
    @addtogroup SYS System Manger Controller(SYS)
    Memory Mapped Structure for SYS Controller
@{ */

#define SYS                  ((SYS_T *)   SYS_BA)

typedef struct
{
    __I  uint32_t PDID;          /* Offset: 0x00  */
    __IO uint32_t PWRON;         /* Offset: 0x04  */
    __IO uint32_t ARBCON;        /* Offset: 0x08  */
    __I  uint32_t RESERVE0[5];
    __IO uint32_t LVRDCR;        /* Offset: 0x20  */
    __I  uint32_t RESERVE1[3];
    __IO uint32_t MISCFCR;       /* Offset: 0x30  */
    __I  uint32_t RESERVE2[3];
    __IO uint32_t MISCIER;       /* Offset: 0x40  */
    __IO uint32_t MISCISR;       /* Offset: 0x44  */
    __I  uint32_t RESERVE3[2];
    __IO uint32_t WKUPSER0;      /* Offset: 0x50  */
    __IO uint32_t WKUPSER1;      /* Offset: 0x54  */
    __IO uint32_t WKUPSSR0;      /* Offset: 0x58  */
    __IO uint32_t WKUPSSR1;      /* Offset: 0x5C  */
    __IO uint32_t AHBIPRST;      /* Offset: 0x60  */
    __IO uint32_t APBIPRST0;     /* Offset: 0x64  */
    __IO uint32_t APBIPRST1;     /* Offset: 0x68  */
    __IO uint32_t RSTSTS;        /* Offset: 0x6C  */
    __IO uint32_t GPA_MFPL;      /* Offset: 0x70  */
    __IO uint32_t GPA_MFPH;      /* Offset: 0x74  */
    __IO uint32_t GPB_MFPL;      /* Offset: 0x78  */
    __IO uint32_t GPB_MFPH;      /* Offset: 0x7C  */
    __IO uint32_t GPC_MFPL;      /* Offset: 0x80  */
    __IO uint32_t GPC_MFPH;      /* Offset: 0x84  */
    __IO uint32_t GPD_MFPL;      /* Offset: 0x88  */
    __IO uint32_t GPD_MFPH;      /* Offset: 0x8C  */
    __IO uint32_t GPE_MFPL;      /* Offset: 0x90  */
    __IO uint32_t GPE_MFPH;      /* Offset: 0x94  */
    __IO uint32_t GPF_MFPL;      /* Offset: 0x98  */
    __IO uint32_t GPF_MFPH;      /* Offset: 0x9c  */
    __IO uint32_t GPG_MFPL;      /* Offset: 0xA0  */
    __IO uint32_t GPG_MFPH;      /* Offset: 0xA4  */
    __I  uint32_t RESERVE4[18];
    __IO uint32_t DDR_DSCTL;     /* Offset: 0xF0  */
    __I  uint32_t RESERVE5[3];
    __IO uint32_t PORDISCR;      /* Offset: 0x100 */
    __IO uint32_t ICEDBGCR;      /* Offset: 0x104 */
    __IO uint32_t ERRADDCR;  /* Offset: 0x108 */
    __I  uint32_t RESERVE6[59];
    __IO uint32_t IRCTCTL;       /* Offset: 0x1F8 */
    __IO uint32_t REGWPCTL;      /* Offset: 0x1FC */


} SYS_T;


/* SYS GPA_MFPL Bit Field Definitions */
#define SYS_GPA_MFPL_PA0MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFPL: PA0MFP Position          */
#define SYS_GPA_MFPL_PA0MFP_Msk          (0xful << SYS_GPA_MFPL_PA0MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA0MFP Mask              */

#define SYS_GPA_MFPL_PA1MFP_Pos          (4)                                               /*!< SYS_T::GPA_MFPL: PA1MFP Position          */
#define SYS_GPA_MFPL_PA1MFP_Msk          (0xful << SYS_GPA_MFPL_PA1MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA1MFP Mask              */

#define SYS_GPA_MFPL_PA2MFP_Pos          (8)                                               /*!< SYS_T::GPA_MFPL: PA2MFP Position          */
#define SYS_GPA_MFPL_PA2MFP_Msk          (0xful << SYS_GPA_MFPL_PA2MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA2MFP Mask              */

#define SYS_GPA_MFPL_PA3MFP_Pos          (12)                                              /*!< SYS_T::GPA_MFPL: PA3MFP Position          */
#define SYS_GPA_MFPL_PA3MFP_Msk          (0xful << SYS_GPA_MFPL_PA3MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA3MFP Mask              */

#define SYS_GPA_MFPL_PA4MFP_Pos          (16)                                              /*!< SYS_T::GPA_MFPL: PA4MFP Position          */
#define SYS_GPA_MFPL_PA4MFP_Msk          (0xful << SYS_GPA_MFPL_PA4MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA4MFP Mask              */

#define SYS_GPA_MFPL_PA5MFP_Pos          (20)                                              /*!< SYS_T::GPA_MFPL: PA5MFP Position          */
#define SYS_GPA_MFPL_PA5MFP_Msk          (0xful << SYS_GPA_MFPL_PA5MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA5MFP Mask              */

#define SYS_GPA_MFPL_PA6MFP_Pos          (24)                                              /*!< SYS_T::GPA_MFPL: PA6MFP Position          */
#define SYS_GPA_MFPL_PA6MFP_Msk          (0xful << SYS_GPA_MFPL_PA6MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA6MFP Mask              */

#define SYS_GPA_MFPL_PA7MFP_Pos          (28)                                              /*!< SYS_T::GPA_MFPL: PA7MFP Position          */
#define SYS_GPA_MFPL_PA7MFP_Msk          (0xful << SYS_GPA_MFPL_PA7MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA7MFP Mask              */

/* SYS GPA_MFPH Bit Field Definitions */
#define SYS_GPA_MFPH_PA8MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFPH: PA8MFP Position          */
#define SYS_GPA_MFPH_PA8MFP_Msk          (0xful << SYS_GPA_MFPH_PA8MFP_Pos)                /*!< SYS_T::GPA_MFPH: PA8MFP Mask              */

#define SYS_GPA_MFPH_PA9MFP_Pos          (4)                                               /*!< SYS_T::GPA_MFPH: PA9MFP Position          */
#define SYS_GPA_MFPH_PA9MFP_Msk          (0xful << SYS_GPA_MFPH_PA9MFP_Pos)                /*!< SYS_T::GPA_MFPH: PA9MFP Mask              */

#define SYS_GPA_MFPH_PA10MFP_Pos         (8)                                               /*!< SYS_T::GPA_MFPH: PA10MFP Position         */
#define SYS_GPA_MFPH_PA10MFP_Msk         (0xful << SYS_GPA_MFPH_PA10MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA10MFP Mask             */

#define SYS_GPA_MFPH_PA11MFP_Pos         (12)                                              /*!< SYS_T::GPA_MFPH: PA11MFP Position         */
#define SYS_GPA_MFPH_PA11MFP_Msk         (0xful << SYS_GPA_MFPH_PA11MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA11MFP Mask             */

#define SYS_GPA_MFPH_PA12MFP_Pos         (16)                                              /*!< SYS_T::GPA_MFPH: PA12MFP Position         */
#define SYS_GPA_MFPH_PA12MFP_Msk         (0xful << SYS_GPA_MFPH_PA12MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA12MFP Mask             */

#define SYS_GPA_MFPH_PA13MFP_Pos         (20)                                              /*!< SYS_T::GPA_MFPH: PA13MFP Position         */
#define SYS_GPA_MFPH_PA13MFP_Msk         (0xful << SYS_GPA_MFPH_PA13MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA13MFP Mask             */

#define SYS_GPA_MFPH_PA14MFP_Pos         (24)                                              /*!< SYS_T::GPA_MFPH: PA14MFP Position         */
#define SYS_GPA_MFPH_PA14MFP_Msk         (0xful << SYS_GPA_MFPH_PA14MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA14MFP Mask             */

#define SYS_GPA_MFPH_PA15MFP_Pos         (28)                                              /*!< SYS_T::GPA_MFPH: PA15MFP Position         */
#define SYS_GPA_MFPH_PA15MFP_Msk         (0xful << SYS_GPA_MFPH_PA15MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA15MFP Mask             */

/* SYS GPB_MFPL Bit Field Definitions */
#define SYS_GPB_MFPL_PB0MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFPL: PB0MFP Position          */
#define SYS_GPB_MFPL_PB0MFP_Msk          (0xful << SYS_GPB_MFPL_PB0MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB0MFP Mask              */

#define SYS_GPB_MFPL_PB1MFP_Pos          (4)                                               /*!< SYS_T::GPB_MFPL: PB1MFP Position          */
#define SYS_GPB_MFPL_PB1MFP_Msk          (0xful << SYS_GPB_MFPL_PB1MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB1MFP Mask              */

#define SYS_GPB_MFPL_PB2MFP_Pos          (8)                                               /*!< SYS_T::GPB_MFPL: PB2MFP Position          */
#define SYS_GPB_MFPL_PB2MFP_Msk          (0xful << SYS_GPB_MFPL_PB2MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB2MFP Mask              */

#define SYS_GPB_MFPL_PB3MFP_Pos          (12)                                              /*!< SYS_T::GPB_MFPL: PB3MFP Position          */
#define SYS_GPB_MFPL_PB3MFP_Msk          (0xful << SYS_GPB_MFPL_PB3MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB3MFP Mask              */

#define SYS_GPB_MFPL_PB4MFP_Pos          (16)                                              /*!< SYS_T::GPB_MFPL: PB4MFP Position          */
#define SYS_GPB_MFPL_PB4MFP_Msk          (0xful << SYS_GPB_MFPL_PB4MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB4MFP Mask              */

#define SYS_GPB_MFPL_PB5MFP_Pos          (20)                                              /*!< SYS_T::GPB_MFPL: PB5MFP Position          */
#define SYS_GPB_MFPL_PB5MFP_Msk          (0xful << SYS_GPB_MFPL_PB5MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB5MFP Mask              */

#define SYS_GPB_MFPL_PB6MFP_Pos          (24)                                              /*!< SYS_T::GPB_MFPL: PB6MFP Position          */
#define SYS_GPB_MFPL_PB6MFP_Msk          (0xful << SYS_GPB_MFPL_PB6MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB6MFP Mask              */

#define SYS_GPB_MFPL_PB7MFP_Pos          (28)                                              /*!< SYS_T::GPB_MFPL: PB7MFP Position          */
#define SYS_GPB_MFPL_PB7MFP_Msk          (0xful << SYS_GPB_MFPL_PB7MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB7MFP Mask              */

/* SYS GPB_MFPH Bit Field Definitions */
#define SYS_GPB_MFPH_PB8MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFPH: PB8MFP Position          */
#define SYS_GPB_MFPH_PB8MFP_Msk          (0xful << SYS_GPB_MFPH_PB8MFP_Pos)                /*!< SYS_T::GPB_MFPH: PB8MFP Mask              */

#define SYS_GPB_MFPH_PB9MFP_Pos          (4)                                               /*!< SYS_T::GPB_MFPH: PB9MFP Position          */
#define SYS_GPB_MFPH_PB9MFP_Msk          (0xful << SYS_GPB_MFPH_PB9MFP_Pos)                /*!< SYS_T::GPB_MFPH: PB9MFP Mask              */

#define SYS_GPB_MFPH_PB10MFP_Pos         (8)                                               /*!< SYS_T::GPB_MFPH: PB10MFP Position         */
#define SYS_GPB_MFPH_PB10MFP_Msk         (0xful << SYS_GPB_MFPH_PB10MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB10MFP Mask             */

#define SYS_GPB_MFPH_PB11MFP_Pos         (12)                                              /*!< SYS_T::GPB_MFPH: PB11MFP Position         */
#define SYS_GPB_MFPH_PB11MFP_Msk         (0xful << SYS_GPB_MFPH_PB11MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB11MFP Mask             */

#define SYS_GPB_MFPH_PB12MFP_Pos         (16)                                              /*!< SYS_T::GPB_MFPH: PB12MFP Position         */
#define SYS_GPB_MFPH_PB12MFP_Msk         (0xful << SYS_GPB_MFPH_PB12MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB12MFP Mask             */

#define SYS_GPB_MFPH_PB13MFP_Pos         (20)                                              /*!< SYS_T::GPB_MFPH: PB13MFP Position         */
#define SYS_GPB_MFPH_PB13MFP_Msk         (0xful << SYS_GPB_MFPH_PB13MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB13MFP Mask             */

#define SYS_GPB_MFPH_PB14MFP_Pos         (24)                                              /*!< SYS_T::GPB_MFPH: PB14MFP Position         */
#define SYS_GPB_MFPH_PB14MFP_Msk         (0xful << SYS_GPB_MFPH_PB14MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB14MFP Mask             */

#define SYS_GPB_MFPH_PB15MFP_Pos         (28)                                              /*!< SYS_T::GPB_MFPH: PB15MFP Position         */
#define SYS_GPB_MFPH_PB15MFP_Msk         (0xful << SYS_GPB_MFPH_PB15MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB15MFP Mask             */

/* SYS GPC_MFPL Bit Field Definitions */
#define SYS_GPC_MFPL_PC0MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFPL: PC0MFP Position          */
#define SYS_GPC_MFPL_PC0MFP_Msk          (0xful << SYS_GPC_MFPL_PC0MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC0MFP Mask              */

#define SYS_GPC_MFPL_PC1MFP_Pos          (4)                                               /*!< SYS_T::GPC_MFPL: PC1MFP Position          */
#define SYS_GPC_MFPL_PC1MFP_Msk          (0xful << SYS_GPC_MFPL_PC1MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC1MFP Mask              */

#define SYS_GPC_MFPL_PC2MFP_Pos          (8)                                               /*!< SYS_T::GPC_MFPL: PC2MFP Position          */
#define SYS_GPC_MFPL_PC2MFP_Msk          (0xful << SYS_GPC_MFPL_PC2MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC2MFP Mask              */

#define SYS_GPC_MFPL_PC3MFP_Pos          (12)                                              /*!< SYS_T::GPC_MFPL: PC3MFP Position          */
#define SYS_GPC_MFPL_PC3MFP_Msk          (0xful << SYS_GPC_MFPL_PC3MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC3MFP Mask              */

#define SYS_GPC_MFPL_PC4MFP_Pos          (16)                                              /*!< SYS_T::GPC_MFPL: PC4MFP Position          */
#define SYS_GPC_MFPL_PC4MFP_Msk          (0xful << SYS_GPC_MFPL_PC4MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC4MFP Mask              */

#define SYS_GPC_MFPL_PC5MFP_Pos          (20)                                              /*!< SYS_T::GPC_MFPL: PC5MFP Position          */
#define SYS_GPC_MFPL_PC5MFP_Msk          (0xful << SYS_GPC_MFPL_PC5MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC5MFP Mask              */

#define SYS_GPC_MFPL_PC6MFP_Pos          (24)                                              /*!< SYS_T::GPC_MFPL: PC6MFP Position          */
#define SYS_GPC_MFPL_PC6MFP_Msk          (0xful << SYS_GPC_MFPL_PC6MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC6MFP Mask              */

#define SYS_GPC_MFPL_PC7MFP_Pos          (28)                                              /*!< SYS_T::GPC_MFPL: PC7MFP Position          */
#define SYS_GPC_MFPL_PC7MFP_Msk          (0xful << SYS_GPC_MFPL_PC7MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC7MFP Mask              */

/* SYS GPC_MFPH Bit Field Definitions */
#define SYS_GPC_MFPH_PC8MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFPH: PC8MFP Position          */
#define SYS_GPC_MFPH_PC8MFP_Msk          (0xful << SYS_GPC_MFPH_PC8MFP_Pos)                /*!< SYS_T::GPC_MFPH: PC8MFP Mask              */

#define SYS_GPC_MFPH_PC9MFP_Pos          (4)                                               /*!< SYS_T::GPC_MFPH: PC9MFP Position          */
#define SYS_GPC_MFPH_PC9MFP_Msk          (0xful << SYS_GPC_MFPH_PC9MFP_Pos)                /*!< SYS_T::GPC_MFPH: PC9MFP Mask              */

#define SYS_GPC_MFPH_PC10MFP_Pos         (8)                                               /*!< SYS_T::GPC_MFPH: PC10MFP Position         */
#define SYS_GPC_MFPH_PC10MFP_Msk         (0xful << SYS_GPC_MFPH_PC10MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC10MFP Mask             */

#define SYS_GPC_MFPH_PC11MFP_Pos         (12)                                              /*!< SYS_T::GPC_MFPH: PC11MFP Position         */
#define SYS_GPC_MFPH_PC11MFP_Msk         (0xful << SYS_GPC_MFPH_PC11MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC11MFP Mask             */

#define SYS_GPC_MFPH_PC12MFP_Pos         (16)                                              /*!< SYS_T::GPC_MFPH: PC12MFP Position         */
#define SYS_GPC_MFPH_PC12MFP_Msk         (0xful << SYS_GPC_MFPH_PC12MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC12MFP Mask             */

#define SYS_GPC_MFPH_PC13MFP_Pos         (20)                                              /*!< SYS_T::GPC_MFPH: PC13MFP Position         */
#define SYS_GPC_MFPH_PC13MFP_Msk         (0xful << SYS_GPC_MFPH_PC13MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC13MFP Mask             */

#define SYS_GPC_MFPH_PC14MFP_Pos         (24)                                              /*!< SYS_T::GPC_MFPH: PC14MFP Position         */
#define SYS_GPC_MFPH_PC14MFP_Msk         (0xful << SYS_GPC_MFPH_PC14MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC14MFP Mask             */

#define SYS_GPC_MFPH_PC15MFP_Pos         (28)                                              /*!< SYS_T::GPC_MFPH: PC15MFP Position         */
#define SYS_GPC_MFPH_PC15MFP_Msk         (0xful << SYS_GPC_MFPH_PC15MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC15MFP Mask             */

/* SYS GPD_MFPL Bit Field Definitions */
#define SYS_GPD_MFPL_PD0MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFPL: PD0MFP Position          */
#define SYS_GPD_MFPL_PD0MFP_Msk          (0xful << SYS_GPD_MFPL_PD0MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD0MFP Mask              */

#define SYS_GPD_MFPL_PD1MFP_Pos          (4)                                               /*!< SYS_T::GPD_MFPL: PD1MFP Position          */
#define SYS_GPD_MFPL_PD1MFP_Msk          (0xful << SYS_GPD_MFPL_PD1MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD1MFP Mask              */

#define SYS_GPD_MFPL_PD2MFP_Pos          (8)                                               /*!< SYS_T::GPD_MFPL: PD2MFP Position          */
#define SYS_GPD_MFPL_PD2MFP_Msk          (0xful << SYS_GPD_MFPL_PD2MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD2MFP Mask              */

#define SYS_GPD_MFPL_PD3MFP_Pos          (12)                                              /*!< SYS_T::GPD_MFPL: PD3MFP Position          */
#define SYS_GPD_MFPL_PD3MFP_Msk          (0xful << SYS_GPD_MFPL_PD3MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD3MFP Mask              */

#define SYS_GPD_MFPL_PD4MFP_Pos          (16)                                              /*!< SYS_T::GPD_MFPL: PD4MFP Position          */
#define SYS_GPD_MFPL_PD4MFP_Msk          (0xful << SYS_GPD_MFPL_PD4MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD4MFP Mask              */

#define SYS_GPD_MFPL_PD5MFP_Pos          (20)                                              /*!< SYS_T::GPD_MFPL: PD5MFP Position          */
#define SYS_GPD_MFPL_PD5MFP_Msk          (0xful << SYS_GPD_MFPL_PD5MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD5MFP Mask              */

#define SYS_GPD_MFPL_PD6MFP_Pos          (24)                                              /*!< SYS_T::GPD_MFPL: PD6MFP Position          */
#define SYS_GPD_MFPL_PD6MFP_Msk          (0xful << SYS_GPD_MFPL_PD6MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD6MFP Mask              */

#define SYS_GPD_MFPL_PD7MFP_Pos          (28)                                              /*!< SYS_T::GPD_MFPL: PD7MFP Position          */
#define SYS_GPD_MFPL_PD7MFP_Msk          (0xful << SYS_GPD_MFPL_PD7MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD7MFP Mask              */

/* SYS GPD_MFPH Bit Field Definitions */
#define SYS_GPD_MFPH_PD8MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFPH: PD8MFP Position          */
#define SYS_GPD_MFPH_PD8MFP_Msk          (0xful << SYS_GPD_MFPH_PD8MFP_Pos)                /*!< SYS_T::GPD_MFPH: PD8MFP Mask              */

#define SYS_GPD_MFPH_PD9MFP_Pos          (4)                                               /*!< SYS_T::GPD_MFPH: PD9MFP Position          */
#define SYS_GPD_MFPH_PD9MFP_Msk          (0xful << SYS_GPD_MFPH_PD9MFP_Pos)                /*!< SYS_T::GPD_MFPH: PD9MFP Mask              */

#define SYS_GPD_MFPH_PD10MFP_Pos         (8)                                               /*!< SYS_T::GPD_MFPH: PD10MFP Position         */
#define SYS_GPD_MFPH_PD10MFP_Msk         (0xful << SYS_GPD_MFPH_PD10MFP_Pos)              /*!< SYS_T::GPD_MFPH: PD10MFP Mask              */

#define SYS_GPD_MFPH_PD11MFP_Pos         (12)                                              /*!< SYS_T::GPD_MFPH: PD11MFP Position         */
#define SYS_GPD_MFPH_PD11MFP_Msk         (0xful << SYS_GPD_MFPH_PD11MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD11MFP Mask             */

#define SYS_GPD_MFPH_PD12MFP_Pos         (16)                                              /*!< SYS_T::GPD_MFPH: PD12MFP Position         */
#define SYS_GPD_MFPH_PD12MFP_Msk         (0xful << SYS_GPD_MFPH_PD12MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD12MFP Mask             */

#define SYS_GPD_MFPH_PD13MFP_Pos         (20)                                              /*!< SYS_T::GPD_MFPH: PD13MFP Position         */
#define SYS_GPD_MFPH_PD13MFP_Msk         (0xful << SYS_GPD_MFPH_PD13MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD13MFP Mask             */

#define SYS_GPD_MFPH_PD14MFP_Pos         (24)                                              /*!< SYS_T::GPD_MFPH: PD14MFP Position         */
#define SYS_GPD_MFPH_PD14MFP_Msk         (0xful << SYS_GPD_MFPH_PD14MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD14MFP Mask             */

#define SYS_GPD_MFPH_PD15MFP_Pos         (28)                                              /*!< SYS_T::GPD_MFPH: PD15MFP Position         */
#define SYS_GPD_MFPH_PD15MFP_Msk         (0xful << SYS_GPD_MFPH_PD15MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD15MFP Mask             */

/* SYS GPE_MFPL Bit Field Definitions */
#define SYS_GPE_MFPL_PE0MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFPL: PE0MFP Position          */
#define SYS_GPE_MFPL_PE0MFP_Msk          (0xful << SYS_GPE_MFPL_PE0MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE0MFP Mask              */

#define SYS_GPE_MFPL_PE1MFP_Pos          (4)                                               /*!< SYS_T::GPE_MFPL: PE1MFP Position          */
#define SYS_GPE_MFPL_PE1MFP_Msk          (0xful << SYS_GPE_MFPL_PE1MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE1MFP Mask              */

#define SYS_GPE_MFPL_PE2MFP_Pos          (8)                                               /*!< SYS_T::GPE_MFPL: PE2MFP Position          */
#define SYS_GPE_MFPL_PE2MFP_Msk          (0xful << SYS_GPE_MFPL_PE2MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE2MFP Mask              */

#define SYS_GPE_MFPL_PE3MFP_Pos          (12)                                              /*!< SYS_T::GPE_MFPL: PE3MFP Position          */
#define SYS_GPE_MFPL_PE3MFP_Msk          (0xful << SYS_GPE_MFPL_PE3MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE3MFP Mask              */

#define SYS_GPE_MFPL_PE4MFP_Pos          (16)                                              /*!< SYS_T::GPE_MFPL: PE4MFP Position          */
#define SYS_GPE_MFPL_PE4MFP_Msk          (0xful << SYS_GPE_MFPL_PE4MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE4MFP Mask              */

#define SYS_GPE_MFPL_PE5MFP_Pos          (20)                                              /*!< SYS_T::GPE_MFPL: PE5MFP Position          */
#define SYS_GPE_MFPL_PE5MFP_Msk          (0xful << SYS_GPE_MFPL_PE5MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE5MFP Mask              */

#define SYS_GPE_MFPL_PE6MFP_Pos          (24)                                              /*!< SYS_T::GPE_MFPL: PE6MFP Position          */
#define SYS_GPE_MFPL_PE6MFP_Msk          (0xful << SYS_GPE_MFPL_PE6MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE6MFP Mask              */

#define SYS_GPE_MFPL_PE7MFP_Pos          (28)                                              /*!< SYS_T::GPE_MFPL: PE7MFP Position          */
#define SYS_GPE_MFPL_PE7MFP_Msk          (0xful << SYS_GPE_MFPL_PE7MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE7MFP Mask              */

/* SYS GPE_MFPH Bit Field Definitions */
#define SYS_GPE_MFPH_PE8MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFPH: PE8MFP Position          */
#define SYS_GPE_MFPH_PE8MFP_Msk          (0xful << SYS_GPE_MFPH_PE8MFP_Pos)                /*!< SYS_T::GPE_MFPH: PE8MFP Mask              */

#define SYS_GPE_MFPH_PE9MFP_Pos          (4)                                               /*!< SYS_T::GPE_MFPH: PE9MFP Position          */
#define SYS_GPE_MFPH_PE9MFP_Msk          (0xful << SYS_GPE_MFPH_PE9MFP_Pos)                /*!< SYS_T::GPE_MFPH: PE9MFP Mask              */

#define SYS_GPE_MFPH_PE10MFP_Pos         (8)                                               /*!< SYS_T::GPE_MFPH: PE10MFP Position         */
#define SYS_GPE_MFPH_PE10MFP_Msk         (0xful << SYS_GPE_MFPH_PE10MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE10MFP Mask             */

#define SYS_GPE_MFPH_PE11MFP_Pos         (12)                                              /*!< SYS_T::GPE_MFPH: PE11MFP Position         */
#define SYS_GPE_MFPH_PE11MFP_Msk         (0xful << SYS_GPE_MFPH_PE11MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE11MFP Mask             */

#define SYS_GPE_MFPH_PE12MFP_Pos         (16)                                              /*!< SYS_T::GPE_MFPH: PE12MFP Position         */
#define SYS_GPE_MFPH_PE12MFP_Msk         (0xful << SYS_GPE_MFPH_PE12MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE12MFP Mask             */

#define SYS_GPE_MFPH_PE13MFP_Pos         (20)                                              /*!< SYS_T::GPE_MFPH: PE13MFP Position         */
#define SYS_GPE_MFPH_PE13MFP_Msk         (0xful << SYS_GPE_MFPH_PE13MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE13MFP Mask             */

#define SYS_GPE_MFPH_PE14MFP_Pos         (24)                                              /*!< SYS_T::GPE_MFPH: PE14MFP Position         */
#define SYS_GPE_MFPH_PE14MFP_Msk         (0xful << SYS_GPE_MFPH_PE14MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE14MFP Mask             */

#define SYS_GPE_MFPH_PE15MFP_Pos         (28)                                              /*!< SYS_T::GPE_MFPH: PE15MFP Position         */
#define SYS_GPE_MFPH_PE15MFP_Msk         (0xful << SYS_GPE_MFPH_PE15MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE15MFP Mask             */

/* SYS GPF_MFPL Bit Field Definitions */
#define SYS_GPF_MFPL_PF0MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFPL: PF0MFP Position          */
#define SYS_GPF_MFPL_PF0MFP_Msk          (0xful << SYS_GPF_MFPL_PF0MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF0MFP Mask              */

#define SYS_GPF_MFPL_PF1MFP_Pos          (4)                                               /*!< SYS_T::GPF_MFPL: PF1MFP Position          */
#define SYS_GPF_MFPL_PF1MFP_Msk          (0xful << SYS_GPF_MFPL_PF1MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF1MFP Mask              */

#define SYS_GPF_MFPL_PF2MFP_Pos          (8)                                               /*!< SYS_T::GPF_MFPL: PF2MFP Position          */
#define SYS_GPF_MFPL_PF2MFP_Msk          (0xful << SYS_GPF_MFPL_PF2MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF2MFP Mask              */

#define SYS_GPF_MFPL_PF3MFP_Pos          (12)                                              /*!< SYS_T::GPF_MFPL: PF3MFP Position          */
#define SYS_GPF_MFPL_PF3MFP_Msk          (0xful << SYS_GPF_MFPL_PF3MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF3MFP Mask              */

#define SYS_GPF_MFPL_PF4MFP_Pos          (16)                                              /*!< SYS_T::GPF_MFPL: PF4MFP Position          */
#define SYS_GPF_MFPL_PF4MFP_Msk          (0xful << SYS_GPF_MFPL_PF4MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF4MFP Mask              */

#define SYS_GPF_MFPL_PF5MFP_Pos          (20)                                              /*!< SYS_T::GPF_MFPL: PF5MFP Position          */
#define SYS_GPF_MFPL_PF5MFP_Msk          (0xful << SYS_GPF_MFPL_PF5MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF5MFP Mask              */

#define SYS_GPF_MFPL_PF6MFP_Pos          (24)                                              /*!< SYS_T::GPF_MFPL: PF6MFP Position          */
#define SYS_GPF_MFPL_PF6MFP_Msk          (0xful << SYS_GPF_MFPL_PF6MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF6MFP Mask              */

#define SYS_GPF_MFPL_PF7MFP_Pos          (28)                                              /*!< SYS_T::GPF_MFPL: PF7MFP Position          */
#define SYS_GPF_MFPL_PF7MFP_Msk          (0xful << SYS_GPF_MFPL_PF7MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF7MFP Mask              */

/* SYS GPF_MFPH Bit Field Definitions */
#define SYS_GPF_MFPH_PF8MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFPH: PF8MFP Position          */
#define SYS_GPF_MFPH_PF8MFP_Msk          (0xful << SYS_GPF_MFPH_PF8MFP_Pos)                /*!< SYS_T::GPF_MFPH: PF8MFP Mask              */

#define SYS_GPF_MFPH_PF9MFP_Pos          (4)                                               /*!< SYS_T::GPF_MFPH: PF9MFP Position          */
#define SYS_GPF_MFPH_PF9MFP_Msk          (0xful << SYS_GPF_MFPH_PF9MFP_Pos)                /*!< SYS_T::GPF_MFPH: PF9MFP Mask              */

#define SYS_GPF_MFPH_PF10MFP_Pos         (8)                                               /*!< SYS_T::GPF_MFPH: PF10MFP Position         */
#define SYS_GPF_MFPH_PF10MFP_Msk         (0xful << SYS_GPF_MFPH_PF10MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF10MFP Mask             */

#define SYS_GPF_MFPH_PF11MFP_Pos         (12)                                              /*!< SYS_T::GPF_MFPH: PF11MFP Position         */
#define SYS_GPF_MFPH_PF11MFP_Msk         (0xful << SYS_GPF_MFPH_PF11MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF11MFP Mask             */

#define SYS_GPF_MFPH_PF12MFP_Pos         (16)                                              /*!< SYS_T::GPF_MFPH: PF12MFP Position         */
#define SYS_GPF_MFPH_PF12MFP_Msk         (0xful << SYS_GPF_MFPH_PF12MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF12MFP Mask             */

#define SYS_GPF_MFPH_PF13MFP_Pos         (20)                                              /*!< SYS_T::GPF_MFPH: PF13MFP Position         */
#define SYS_GPF_MFPH_PF13MFP_Msk         (0xful << SYS_GPF_MFPH_PF13MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF13MFP Mask             */

#define SYS_GPF_MFPH_PF14MFP_Pos         (24)                                              /*!< SYS_T::GPF_MFPH: PF14MFP Position         */
#define SYS_GPF_MFPH_PF14MFP_Msk         (0xful << SYS_GPF_MFPH_PF14MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF14MFP Mask             */

#define SYS_GPF_MFPH_PF15MFP_Pos         (28)                                              /*!< SYS_T::GPF_MFPH: PF15MFP Position         */
#define SYS_GPF_MFPH_PF15MFP_Msk         (0xful << SYS_GPF_MFPH_PF15MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF15MFP Mask             */

/* SYS GPG_MFPL Bit Field Definitions */
#define SYS_GPG_MFPL_PG0MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFPL: PG0MFP Position          */
#define SYS_GPG_MFPL_PG0MFP_Msk          (0xful << SYS_GPG_MFPL_PG0MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG0MFP Mask              */

#define SYS_GPG_MFPL_PG1MFP_Pos          (4)                                               /*!< SYS_T::GPG_MFPL: PG1MFP Position          */
#define SYS_GPG_MFPL_PG1MFP_Msk          (0xful << SYS_GPG_MFPL_PG1MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG1MFP Mask              */

#define SYS_GPG_MFPL_PG2MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFPL: PG2MFP Position          */
#define SYS_GPG_MFPL_PG2MFP_Msk          (0xful << SYS_GPG_MFPL_PG2MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG2MFP Mask              */

#define SYS_GPG_MFPL_PG3MFP_Pos          (12)                                              /*!< SYS_T::GPG_MFPL: PG3MFP Position          */
#define SYS_GPG_MFPL_PG3MFP_Msk          (0xful << SYS_GPG_MFPL_PG3MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG3MFP Mask              */

#define SYS_GPG_MFPL_PG4MFP_Pos          (16)                                              /*!< SYS_T::GPG_MFPL: PG4MFP Position          */
#define SYS_GPG_MFPL_PG4MFP_Msk          (0xful << SYS_GPG_MFPL_PG4MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG4MFP Mask              */

#define SYS_GPG_MFPL_PG5MFP_Pos          (20)                                              /*!< SYS_T::GPG_MFPL: PG5MFP Position          */
#define SYS_GPG_MFPL_PG5MFP_Msk          (0xful << SYS_GPG_MFPL_PG5MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG5MFP Mask              */

#define SYS_GPG_MFPL_PG6MFP_Pos          (24)                                              /*!< SYS_T::GPG_MFPL: PG6MFP Position          */
#define SYS_GPG_MFPL_PG6MFP_Msk          (0xful << SYS_GPG_MFPL_PG6MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG6MFP Mask              */

#define SYS_GPG_MFPL_PG7MFP_Pos          (28)                                              /*!< SYS_T::GPG_MFPL: PG7MFP Position          */
#define SYS_GPG_MFPL_PG7MFP_Msk          (0xful << SYS_GPG_MFPL_PG7MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG7MFP Mask              */

/* SYS GPG_MFPH Bit Field Definitions */
#define SYS_GPG_MFPH_PG8MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFPH: PG8MFP Position          */
#define SYS_GPG_MFPH_PG8MFP_Msk          (0xful << SYS_GPG_MFPH_PG8MFP_Pos)                /*!< SYS_T::GPG_MFPH: PG8MFP Mask              */

#define SYS_GPG_MFPH_PG9MFP_Pos          (4)                                               /*!< SYS_T::GPG_MFPH: PG9MFP Position          */
#define SYS_GPG_MFPH_PG9MFP_Msk          (0xful << SYS_GPG_MFPH_PG9MFP_Pos)                /*!< SYS_T::GPG_MFPH: PG9MFP Mask              */

#define SYS_GPG_MFPH_PG10MFP_Pos         (8)                                               /*!< SYS_T::GPG_MFPH: PG10MFP Position         */
#define SYS_GPG_MFPH_PG10MFP_Msk         (0xful << SYS_GPG_MFPH_PG10MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG10MFP Mask             */

#define SYS_GPG_MFPH_PG11MFP_Pos         (12)                                              /*!< SYS_T::GPG_MFPH: PG11MFP Position         */
#define SYS_GPG_MFPH_PG11MFP_Msk         (0xful << SYS_GPG_MFPH_PG11MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG11MFP Mask             */

#define SYS_GPG_MFPH_PG12MFP_Pos         (16)                                              /*!< SYS_T::GPG_MFPH: PG12MFP Position         */
#define SYS_GPG_MFPH_PG12MFP_Msk         (0xful << SYS_GPG_MFPH_PG12MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG12MFP Mask             */

#define SYS_GPG_MFPH_PG13MFP_Pos         (20)                                              /*!< SYS_T::GPG_MFPH: PG13MFP Position         */
#define SYS_GPG_MFPH_PG13MFP_Msk         (0xful << SYS_GPG_MFPH_PG13MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG13MFP Mask             */

#define SYS_GPG_MFPH_PG14MFP_Pos         (24)                                              /*!< SYS_T::GPG_MFPH: PG14MFP Position         */
#define SYS_GPG_MFPH_PG14MFP_Msk         (0xful << SYS_GPG_MFPH_PG14MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG14MFP Mask             */

#define SYS_GPG_MFPH_PG15MFP_Pos         (28)                                              /*!< SYS_T::GPG_MFPH: PG15MFP Position         */
#define SYS_GPG_MFPH_PG15MFP_Msk         (0xful << SYS_GPG_MFPH_PG15MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG15MFP Mask             */

/*@}*/ /* end of group NUC980_SYS_EXPORTED_CONSTANTS */


/********************* Bit definition of GPA_MFPL register **********************/
#define SYS_GPA_MFPL_PA0MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA0MFP_Pos)
#define SYS_GPA_MFPL_PA1MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA1MFP_Pos)
#define SYS_GPA_MFPL_PA1MFP_EBI_nCS2          (0x01UL<<SYS_GPA_MFPL_PA1MFP_Pos)
#define SYS_GPA_MFPL_PA1MFP_EBI_MCLK          (0x02UL<<SYS_GPA_MFPL_PA1MFP_Pos)
#define SYS_GPA_MFPL_PA2MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA2MFP_Pos)
#define SYS_GPA_MFPL_PA3MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA3MFP_Pos)
#define SYS_GPA_MFPL_PA4MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA4MFP_Pos)
#define SYS_GPA_MFPL_PA5MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA5MFP_Pos)
#define SYS_GPA_MFPL_PA6MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA6MFP_Pos)
#define SYS_GPA_MFPL_PA6MFP_EBI_nCS1          (0x01UL<<SYS_GPA_MFPL_PA6MFP_Pos)
#define SYS_GPA_MFPL_PA7MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA7MFP_Pos)
#define SYS_GPA_MFPL_PA7MFP_EBI_nWE           (0x01UL<<SYS_GPA_MFPL_PA7MFP_Pos)
/********************* Bit definition of GPA_MFPH register **********************/
#define SYS_GPA_MFPH_PA8MFP_GPIO              (0x00UL<<SYS_GPA_MFPH_PA8MFP_Pos)
#define SYS_GPA_MFPH_PA8MFP_EBI_nRE           (0x01UL<<SYS_GPA_MFPH_PA8MFP_Pos)
#define SYS_GPA_MFPH_PA9MFP_GPIO              (0x00UL<<SYS_GPA_MFPH_PA9MFP_Pos)
#define SYS_GPA_MFPH_PA9MFP_EBI_nCS0          (0x01UL<<SYS_GPA_MFPH_PA9MFP_Pos)
#define SYS_GPA_MFPH_PA10MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA10MFP_Pos)
#define SYS_GPA_MFPH_PA10MFP_EBI_ADDR10       (0x01UL<<SYS_GPA_MFPH_PA10MFP_Pos)
#define SYS_GPA_MFPH_PA11MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA11MFP_Pos)
#define SYS_GPA_MFPH_PA11MFP_EBI_ADDR9        (0x01UL<<SYS_GPA_MFPH_PA11MFP_Pos)
#define SYS_GPA_MFPH_PA12MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA12MFP_Pos)
#define SYS_GPA_MFPH_PA12MFP_EBI_ADDR8        (0x01UL<<SYS_GPA_MFPH_PA12MFP_Pos)
#define SYS_GPA_MFPH_PA13MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA13MFP_Pos)
#define SYS_GPA_MFPH_PA13MFP_EBI_ADDR13       (0x01UL<<SYS_GPA_MFPH_PA13MFP_Pos)
#define SYS_GPA_MFPH_PA14MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA14MFP_Pos)
#define SYS_GPA_MFPH_PA14MFP_EBI_ADDR14       (0x01UL<<SYS_GPA_MFPH_PA14MFP_Pos)
#define SYS_GPA_MFPH_PA15MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA15MFP_Pos)
#define SYS_GPA_MFPH_PA15MFP_EBI_ADDR19       (0x01UL<<SYS_GPA_MFPH_PA15MFP_Pos)
/********************* Bit definition of GPB_MFPL register **********************/
#define SYS_GPB_MFPL_PB0MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB0MFP_Pos)
#define SYS_GPB_MFPL_PB0MFP_EBI_ADDR12        (0x01UL<<SYS_GPB_MFPL_PB0MFP_Pos)
#define SYS_GPB_MFPL_PB1MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB1MFP_Pos)
#define SYS_GPB_MFPL_PB1MFP_EBI_ADDR17        (0x01UL<<SYS_GPB_MFPL_PB1MFP_Pos)
#define SYS_GPB_MFPL_PB2MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB2MFP_Pos)
#define SYS_GPB_MFPL_PB2MFP_EBI_ADDR2         (0x01UL<<SYS_GPB_MFPL_PB2MFP_Pos)
#define SYS_GPB_MFPL_PB2MFP_EBI_MCLK          (0x03UL<<SYS_GPB_MFPL_PB2MFP_Pos)
#define SYS_GPB_MFPL_PB3MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB3MFP_Pos)
#define SYS_GPB_MFPL_PB3MFP_EBI_ADDR18        (0x01UL<<SYS_GPB_MFPL_PB3MFP_Pos)
#define SYS_GPB_MFPL_PB4MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB4MFP_Pos)
#define SYS_GPB_MFPL_PB4MFP_EBI_ADDR14        (0x01UL<<SYS_GPB_MFPL_PB4MFP_Pos)
#define SYS_GPB_MFPL_PB5MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB5MFP_Pos)
#define SYS_GPB_MFPL_PB5MFP_EBI_ADDR16        (0x01UL<<SYS_GPB_MFPL_PB5MFP_Pos)
#define SYS_GPB_MFPL_PB6MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB6MFP_Pos)
#define SYS_GPB_MFPL_PB6MFP_EBI_ADDR13        (0x01UL<<SYS_GPB_MFPL_PB6MFP_Pos)
#define SYS_GPB_MFPL_PB7MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB7MFP_Pos)
#define SYS_GPB_MFPL_PB7MFP_EBI_ADDR15        (0x01UL<<SYS_GPB_MFPL_PB7MFP_Pos)
/********************* Bit definition of GPB_MFPH register **********************/
#define SYS_GPB_MFPH_PB8MFP_GPIO              (0x00UL<<SYS_GPB_MFPH_PB8MFP_Pos)
#define SYS_GPB_MFPH_PB8MFP_EBI_ADDR11        (0x01UL<<SYS_GPB_MFPH_PB8MFP_Pos)
#define SYS_GPB_MFPH_PB9MFP_GPIO              (0x00UL<<SYS_GPB_MFPH_PB9MFP_Pos)
#define SYS_GPB_MFPH_PB10MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB10MFP_Pos)
#define SYS_GPB_MFPH_PB11MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB11MFP_Pos)
#define SYS_GPB_MFPH_PB12MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB12MFP_Pos)
#define SYS_GPB_MFPH_PB13MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB13MFP_Pos)
/********************* Bit definition of GPC_MFPL register **********************/
#define SYS_GPC_MFPL_PC0MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC0MFP_Pos)
#define SYS_GPC_MFPL_PC0MFP_EBI_DATA0         (0x01UL<<SYS_GPC_MFPL_PC0MFP_Pos)
#define SYS_GPC_MFPL_PC1MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC1MFP_Pos)
#define SYS_GPC_MFPL_PC1MFP_EBI_DATA1         (0x01UL<<SYS_GPC_MFPL_PC1MFP_Pos)
#define SYS_GPC_MFPL_PC2MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC2MFP_Pos)
#define SYS_GPC_MFPL_PC2MFP_EBI_DATA2         (0x01UL<<SYS_GPC_MFPL_PC2MFP_Pos)
#define SYS_GPC_MFPL_PC3MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC3MFP_Pos)
#define SYS_GPC_MFPL_PC3MFP_EBI_DATA3         (0x01UL<<SYS_GPC_MFPL_PC3MFP_Pos)
#define SYS_GPC_MFPL_PC4MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC4MFP_Pos)
#define SYS_GPC_MFPL_PC4MFP_EBI_DATA4         (0x01UL<<SYS_GPC_MFPL_PC4MFP_Pos)
#define SYS_GPC_MFPL_PC5MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC5MFP_Pos)
#define SYS_GPC_MFPL_PC5MFP_EBI_DATA5         (0x01UL<<SYS_GPC_MFPL_PC5MFP_Pos)
#define SYS_GPC_MFPL_PC6MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC6MFP_Pos)
#define SYS_GPC_MFPL_PC6MFP_EBI_DATA6         (0x01UL<<SYS_GPC_MFPL_PC6MFP_Pos)
#define SYS_GPC_MFPL_PC7MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC7MFP_Pos)
#define SYS_GPC_MFPL_PC7MFP_EBI_DATA7         (0x01UL<<SYS_GPC_MFPL_PC7MFP_Pos)
/********************* Bit definition of GPC_MFPH register **********************/
#define SYS_GPC_MFPH_PC8MFP_GPIO              (0x00UL<<SYS_GPC_MFPH_PC8MFP_Pos)
#define SYS_GPC_MFPH_PC8MFP_EBI_DATA8         (0x01UL<<SYS_GPC_MFPH_PC8MFP_Pos)
#define SYS_GPC_MFPH_PC9MFP_GPIO              (0x00UL<<SYS_GPC_MFPH_PC9MFP_Pos)
#define SYS_GPC_MFPH_PC9MFP_EBI_DATA9         (0x01UL<<SYS_GPC_MFPH_PC9MFP_Pos)
#define SYS_GPC_MFPH_PC10MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC10MFP_Pos)
#define SYS_GPC_MFPH_PC10MFP_EBI_DATA10       (0x01UL<<SYS_GPC_MFPH_PC10MFP_Pos)
#define SYS_GPC_MFPH_PC11MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC11MFP_Pos)
#define SYS_GPC_MFPH_PC11MFP_EBI_DATA11       (0x01UL<<SYS_GPC_MFPH_PC11MFP_Pos)
#define SYS_GPC_MFPH_PC12MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC12MFP_Pos)
#define SYS_GPC_MFPH_PC12MFP_EBI_DATA12       (0x01UL<<SYS_GPC_MFPH_PC12MFP_Pos)
#define SYS_GPC_MFPH_PC13MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC13MFP_Pos)
#define SYS_GPC_MFPH_PC13MFP_EBI_DATA13       (0x01UL<<SYS_GPC_MFPH_PC13MFP_Pos)
#define SYS_GPC_MFPH_PC14MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC14MFP_Pos)
#define SYS_GPC_MFPH_PC14MFP_EBI_DATA14       (0x01UL<<SYS_GPC_MFPH_PC14MFP_Pos)
#define SYS_GPC_MFPH_PC15MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC15MFP_Pos)
#define SYS_GPC_MFPH_PC15MFP_EBI_DATA15       (0x01UL<<SYS_GPC_MFPH_PC15MFP_Pos)
/********************* Bit definition of GPD_MFPL register **********************/
#define SYS_GPD_MFPL_PD0MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD0MFP_Pos)
#define SYS_GPD_MFPL_PD1MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD1MFP_Pos)
#define SYS_GPD_MFPL_PD2MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD2MFP_Pos)
#define SYS_GPD_MFPL_PD3MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD3MFP_Pos)
#define SYS_GPD_MFPL_PD4MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD4MFP_Pos)
#define SYS_GPD_MFPL_PD5MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD5MFP_Pos)
#define SYS_GPD_MFPL_PD6MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD6MFP_Pos)
#define SYS_GPD_MFPL_PD7MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD7MFP_Pos)
/********************* Bit definition of GPD_MFPH register **********************/
#define SYS_GPD_MFPH_PD8MFP_GPIO              (0x00UL<<SYS_GPD_MFPH_PD8MFP_Pos)
#define SYS_GPD_MFPH_PD9MFP_GPIO              (0x00UL<<SYS_GPD_MFPH_PD9MFP_Pos)
#define SYS_GPD_MFPH_PD10MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD10MFP_Pos)
#define SYS_GPD_MFPH_PD11MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD11MFP_Pos)
#define SYS_GPD_MFPH_PD12MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD12MFP_Pos)
#define SYS_GPD_MFPH_PD12MFP_EBI_DATA1        (0x08UL<<SYS_GPD_MFPH_PD12MFP_Pos)
#define SYS_GPD_MFPH_PD13MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD13MFP_Pos)
#define SYS_GPD_MFPH_PD13MFP_EBI_DATA2        (0x08UL<<SYS_GPD_MFPH_PD13MFP_Pos)
#define SYS_GPD_MFPH_PD14MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD14MFP_Pos)
#define SYS_GPD_MFPH_PD14MFP_EBI_DATA3        (0x08UL<<SYS_GPD_MFPH_PD14MFP_Pos)
#define SYS_GPD_MFPH_PD15MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD15MFP_Pos)
#define SYS_GPD_MFPH_PD15MFP_EBI_DATA4        (0x08UL<<SYS_GPD_MFPH_PD15MFP_Pos)
/********************* Bit definition of GPE_MFPL register **********************/
#define SYS_GPE_MFPL_PE0MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE0MFP_Pos)
#define SYS_GPE_MFPL_PE1MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE1MFP_Pos)
#define SYS_GPE_MFPL_PE2MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE2MFP_Pos)
#define SYS_GPE_MFPL_PE3MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE3MFP_Pos)
#define SYS_GPE_MFPL_PE4MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE4MFP_Pos)
#define SYS_GPE_MFPL_PE5MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE5MFP_Pos)
#define SYS_GPE_MFPL_PE6MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE6MFP_Pos)
#define SYS_GPE_MFPL_PE7MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE7MFP_Pos)
/********************* Bit definition of GPE_MFPH register **********************/
#define SYS_GPE_MFPH_PE8MFP_GPIO              (0x00UL<<SYS_GPE_MFPH_PE8MFP_Pos)
#define SYS_GPE_MFPH_PE9MFP_GPIO              (0x00UL<<SYS_GPE_MFPH_PE9MFP_Pos)
#define SYS_GPE_MFPH_PE10MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE10MFP_Pos)
#define SYS_GPE_MFPH_PE11MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE11MFP_Pos)
#define SYS_GPE_MFPH_PE12MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE12MFP_Pos)
/********************* Bit definition of GPF_MFPL register **********************/
#define SYS_GPF_MFPL_PF0MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF0MFP_Pos)
#define SYS_GPF_MFPL_PF0MFP_EBI_DATA5         (0x08UL<<SYS_GPF_MFPL_PF0MFP_Pos)
#define SYS_GPF_MFPL_PF1MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF1MFP_Pos)
#define SYS_GPF_MFPL_PF1MFP_EBI_DATA6         (0x08UL<<SYS_GPF_MFPL_PF1MFP_Pos)
#define SYS_GPF_MFPL_PF2MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF2MFP_Pos)
#define SYS_GPF_MFPL_PF2MFP_EBI_DATA7         (0x08UL<<SYS_GPF_MFPL_PF2MFP_Pos)
#define SYS_GPF_MFPL_PF3MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF3MFP_Pos)
#define SYS_GPF_MFPL_PF3MFP_EBI_DATA8         (0x08UL<<SYS_GPF_MFPL_PF3MFP_Pos)
#define SYS_GPF_MFPL_PF4MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF4MFP_Pos)
#define SYS_GPF_MFPL_PF4MFP_EBI_DATA9         (0x08UL<<SYS_GPF_MFPL_PF4MFP_Pos)
#define SYS_GPF_MFPL_PF5MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF5MFP_Pos)
#define SYS_GPF_MFPL_PF5MFP_EBI_DATA10        (0x08UL<<SYS_GPF_MFPL_PF5MFP_Pos)
#define SYS_GPF_MFPL_PF6MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF6MFP_Pos)
#define SYS_GPF_MFPL_PF6MFP_EBI_DATA11        (0x08UL<<SYS_GPF_MFPL_PF6MFP_Pos)
#define SYS_GPF_MFPL_PF7MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF7MFP_Pos)
#define SYS_GPF_MFPL_PF7MFP_EBI_DATA12        (0x08UL<<SYS_GPF_MFPL_PF7MFP_Pos)
/********************* Bit definition of GPF_MFPH register **********************/
#define SYS_GPF_MFPH_PF8MFP_GPIO              (0x00UL<<SYS_GPF_MFPH_PF8MFP_Pos)
#define SYS_GPF_MFPH_PF8MFP_EBI_DATA13        (0x08UL<<SYS_GPF_MFPH_PF8MFP_Pos)
#define SYS_GPF_MFPH_PF9MFP_GPIO              (0x00UL<<SYS_GPF_MFPH_PF9MFP_Pos)
#define SYS_GPF_MFPH_PF9MFP_EBI_DATA14        (0x08UL<<SYS_GPF_MFPH_PF9MFP_Pos)
#define SYS_GPF_MFPH_PF10MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF10MFP_Pos)
#define SYS_GPF_MFPH_PF10MFP_EBI_DATA15       (0x08UL<<SYS_GPF_MFPH_PF10MFP_Pos)
#define SYS_GPF_MFPH_PF11MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF11MFP_Pos)
#define SYS_GPF_MFPH_PF12MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF12MFP_Pos)
/********************* Bit definition of GPG_MFPL register **********************/
#define SYS_GPG_MFPL_PG0MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG0MFP_Pos)
#define SYS_GPG_MFPL_PG0MFP_EBI_ADDR0         (0x01UL<<SYS_GPG_MFPL_PG0MFP_Pos)
#define SYS_GPG_MFPL_PG1MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG1MFP_Pos)
#define SYS_GPG_MFPL_PG1MFP_EBI_ADDR1         (0x01UL<<SYS_GPG_MFPL_PG1MFP_Pos)
#define SYS_GPG_MFPL_PG2MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG2MFP_Pos)
#define SYS_GPG_MFPL_PG2MFP_EBI_ADDR2         (0x01UL<<SYS_GPG_MFPL_PG2MFP_Pos)
#define SYS_GPG_MFPL_PG3MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG3MFP_Pos)
#define SYS_GPG_MFPL_PG3MFP_EBI_ADDR3         (0x01UL<<SYS_GPG_MFPL_PG3MFP_Pos)
#define SYS_GPG_MFPL_PG4MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG4MFP_Pos)
#define SYS_GPG_MFPL_PG4MFP_EBI_ADDR18        (0x01UL<<SYS_GPG_MFPL_PG4MFP_Pos)
#define SYS_GPG_MFPL_PG5MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG5MFP_Pos)
#define SYS_GPG_MFPL_PG5MFP_EBI_ADDR12        (0x01UL<<SYS_GPG_MFPL_PG5MFP_Pos)
#define SYS_GPG_MFPL_PG6MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG6MFP_Pos)
#define SYS_GPG_MFPL_PG6MFP_EBI_ADDR4         (0x01UL<<SYS_GPG_MFPL_PG6MFP_Pos)
#define SYS_GPG_MFPL_PG7MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG7MFP_Pos)
#define SYS_GPG_MFPL_PG7MFP_EBI_ADDR5         (0x01UL<<SYS_GPG_MFPL_PG7MFP_Pos)
/********************* Bit definition of GPG_MFPH register **********************/
#define SYS_GPG_MFPH_PG8MFP_GPIO              (0x00UL<<SYS_GPG_MFPH_PG8MFP_Pos)
#define SYS_GPG_MFPH_PG8MFP_EBI_ADDR6         (0x01UL<<SYS_GPG_MFPH_PG8MFP_Pos)
#define SYS_GPG_MFPH_PG9MFP_GPIO              (0x00UL<<SYS_GPG_MFPH_PG9MFP_Pos)
#define SYS_GPG_MFPH_PG9MFP_EBI_ADDR7         (0x01UL<<SYS_GPG_MFPH_PG9MFP_Pos)
#define SYS_GPG_MFPH_PG10MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG10MFP_Pos)
#define SYS_GPG_MFPH_PG10MFP_EBI_DATA0        (0x01UL<<SYS_GPG_MFPH_PG10MFP_Pos)
#define SYS_GPG_MFPH_PG11MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG11MFP_Pos)
#define SYS_GPG_MFPH_PG12MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG12MFP_Pos)
#define SYS_GPG_MFPH_PG13MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG13MFP_Pos)
#define SYS_GPG_MFPH_PG14MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG14MFP_Pos)
#define SYS_GPG_MFPH_PG15MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG15MFP_Pos)

/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  */
static __inline void SYS_UnlockReg(void)
{
    do
    {
        outpw(0xB00001FC, 0x59UL);
        outpw(0xB00001FC, 0x16UL);
        outpw(0xB00001FC, 0x88UL);
    }
    while (inpw(0xB00001FC) == 0UL);
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function is used to enable register write-protection function.
  *             To lock the protected register to forbid write access.
  */
static __inline void SYS_LockReg(void)
{
    outpw(0xB00001FC, 0);
}

/* Define system library AIC functions */
INT32   sysDisableInterrupt(IRQn_Type eIntNo);
INT32   sysEnableInterrupt(IRQn_Type eIntNo);
BOOL    sysGetIBitState(void);
UINT32  sysGetInterruptEnableStatus(void);
UINT32  sysGetInterruptEnableStatusH(void);
PVOID   sysInstallExceptionHandler(INT32 nExceptType, PVOID pvNewHandler);
PVOID   sysInstallFiqHandler(PVOID pvNewISR);
PVOID   sysInstallIrqHandler(PVOID pvNewISR);
PVOID   sysInstallISR(INT32 nIntTypeLevel, IRQn_Type eIntNo, PVOID pvNewISR);
INT32   sysSetGlobalInterrupt(INT32 nIntState);
INT32   sysSetInterruptPriorityLevel(IRQn_Type eIntNo, UINT32 uIntLevel);
INT32   sysSetInterruptType(IRQn_Type eIntNo, UINT32 uIntSourceType);
INT32   sysSetLocalInterrupt(INT32 nIntState);


/* Define system library Cache functions */
void    sysDisableCache(void);
INT32   sysEnableCache(UINT32 uCacheOpMode);
void    sysFlushCache(INT32 nCacheType);
BOOL    sysGetCacheState(void);
INT32   sysGetSdramSizebyMB(void);
void    sysInvalidCache(void);

UINT32 sysGetClock(CLK_Type clk);

typedef void (*sys_pvFunPtr)();   /* function pointer */
extern sys_pvFunPtr sysIrqHandlerTable[];
extern UINT32 volatile _sys_bIsAICInitial;

#ifdef __cplusplus
}
#endif

/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */

#endif //__SYS_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
