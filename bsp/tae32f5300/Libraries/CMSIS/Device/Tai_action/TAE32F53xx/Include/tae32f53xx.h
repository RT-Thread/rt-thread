/**
  ******************************************************************************
  * @file    tae32f53xx.h
  * @author  MCD Application Team
  * @brief   CMSIS TAE32F53xx(Cortex-M3) Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for TAE32F53xx devices.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_H_
#define _TAE32F53XX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @defgroup TAE_CMSIS TAE CMSIS
  * @brief    TAE CMSIS
  * @{
  */

/** @defgroup TAE32F53xx_Series TAE32F53xx Series
  * @brief    TAE32F53xx Series
  * @{
  */


/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/* Exported types ------------------------------------------------------------*/
/** @defgroup TAE32F53xx_Exported_Types TAE32F53xx Exported Types
  * @brief    TAE32F53xx Exported Types
  * @{
  */

/** @defgroup TAE32F53xx_Peripheral_Interrupt_Number_Definition TAE32F53xx Peripheral Interrupt Number Definition
  * @brief    TAE32F53xx Peripheral Interrupt Number Definition
  * @{
  */

/**
  * @brief TAE32F53xx Peripheral Interrupt Number Definition
  */
typedef enum {
    /* ------------------  Processor Exceptions Numbers  ------------------ */
    NonMaskableInt_IRQn     = -14,      /*!<  2 Non Maskable Interrupt      */
    HardFault_IRQn          = -13,      /*!<  3 HardFault Interrupt         */
    MemoryManagement_IRQn   = -12,      /*!<  4 Memory Management Interrupt */
    BusFault_IRQn           = -11,      /*!<  5 Bus Fault Interrupt         */
    UsageFault_IRQn         = -10,      /*!<  6 Usage Fault Interrupt       */
    SVCall_IRQn             =  -5,      /*!< 11 SV Call Interrupt           */
    DebugMonitor_IRQn       =  -4,      /*!< 12 Debug Monitor Interrupt     */
    PendSV_IRQn             =  -2,      /*!< 14 Pend SV Interrupt           */
    SysTick_IRQn            =  -1,      /*!< 15 System Tick Interrupt       */

    /* ------------------  Processor Interrupt Numbers  ------------------- */
    I2C0_IRQn               =   0,      /*!< I2C0 Interrupt                 */
    I2C1_IRQn               =   1,      /*!< I2C1 Interrupt                 */
    UART0_IRQn              =   2,      /*!< UART0 Interrupt                */
    UART1_IRQn              =   3,      /*!< UART1 Interrupt                */
    TMR0_IRQn               =   4,      /*!< TIMER0 Interrupt               */
    TMR1_IRQn               =   5,      /*!< TIMER1 Interrupt               */
    TMR2_IRQn               =   6,      /*!< TIMER2 Interrupt               */
    TMR3_IRQn               =   7,      /*!< TIMER3 Interrupt               */
    LVD_IRQn                =   8,      /*!< LVD Interrupt                  */
    TMR4_IRQn               =   9,      /*!< TIMER4 Interrupt               */
    TMR5_IRQn               =  10,      /*!< TIMER5 Interrupt               */
    TMR6_IRQn               =  11,      /*!< TIMER6 Interrupt               */
    TMR7_IRQn               =  12,      /*!< TIMER7 Interrupt               */
    IWDG_IRQn               =  13,      /*!< IWDG Interrupt                 */
    WWDG_IRQn               =  14,      /*!< WWDG Interrupt                 */
    IIR0_IRQn               =  15,      /*!< IIR0 Interrupt                 */
    IIR1_IRQn               =  16,      /*!< IIR1 Interrupt                 */
    IIR2_IRQn               =  17,      /*!< IIR2 Interrupt                 */
    IIR3_IRQn               =  18,      /*!< IIR3 Interrupt                 */
    IIR4_IRQn               =  19,      /*!< IIR4 Interrupt                 */
    ECU_IRQn                =  20,      /*!< ECU Cal Done Interrupt         */
    DMA_IRQn                =  21,      /*!< DMA Interrupt                  */
    CAN_IRQn                =  22,      /*!< CAN Interrupt                  */
    GPIOA_IRQn              =  23,      /*!< GPIOA Interrupt                */
    GPIOB_IRQn              =  24,      /*!< GPIOB Interrupt                */
    GPIOC_IRQn              =  25,      /*!< GPIOC Interrupt                */
    GPIOD_IRQn              =  26,      /*!< GPIOD Interrupt                */
    FLASH_IRQn              =  27,      /*!< FLASH Interrupt                */
    DFLASH_IRQn             =  28,      /*!< DFLASH Interrupt               */
    HRPWM_MSTR_IRQn         =  29,      /*!< Hrpwm Master Global Interrupt  */
    HRPWM_SLV0_IRQn         =  30,      /*!< Hrpwm Slave0 Global Interrupt  */
    HRPWM_SLV1_IRQn         =  31,      /*!< Hrpwm Slave1 Global Interrupt  */
    HRPWM_SLV2_IRQn         =  32,      /*!< Hrpwm Slave2 Global Interrupt  */
    HRPWM_SLV3_IRQn         =  33,      /*!< Hrpwm Slave3 Global Interrupt  */
    HRPWM_SLV4_IRQn         =  34,      /*!< Hrpwm Slave4 Global Interrupt  */
    HRPWM_SLV5_IRQn         =  35,      /*!< Hrpwm Slave5 Global Interrupt  */
    HRPWM_FLT_IRQn          =  36,      /*!< Hrpwm All Fault Interrupt      */
    ADC0_NORM_IRQn          =  37,      /*!< ADC0 Normal Global Interrupt   */
    ADC0_HALF_IRQn          =  38,      /*!< ADC0 DMA Half Done Interrupt   */
    ADC0_FULL_IRQn          =  39,      /*!< ADC0 DMA Full Done Interrupt   */
    ADC0_SAMP_IRQn          =  40,      /*!< ADC0 Sample Done Interrupt     */
    ADC1_NORM_IRQn          =  41,      /*!< ADC1 Normal Global Interrupt   */
    ADC1_HALF_IRQn          =  42,      /*!< ADC1 DMA Half Done Interrupt   */
    ADC1_FULL_IRQn          =  43,      /*!< ADC1 DMA Full Done Interrupt   */
    ADC1_SAMP_IRQn          =  44,      /*!< ADC1 Sample Done Interrupt     */
    DAC_IRQn                =  45,      /*!< DAC Interrupt                  */
    CMP_IRQn                =  46,      /*!< CMP Interrupt                  */
    USB_STA_IRQn            =  47,      /*!< USB Staus Interrupt            */
    USB_DET_IRQn            =  48,      /*!< USB Detect Interrupt           */
    USB_LPM_IRQn            =  49,      /*!< USB LPM Interrupt              */
    USB_EP_IRQn             =  50,      /*!< USB Endpoint Interrupt         */
    DALI_IRQn               =  51,      /*!< DALI Interrupt                 */
} IRQn_Type;
/**
  * @}
  */


/** @defgroup TAE32F53xx_Configuration_Section_For_CMSIS TAE32F53xx Configuration Section For CMSIS
  * @brief    TAE32F53xx Configuration Section For CMSIS
  * @{
  */

/**
  * @brief Configuration of the Cortex-M3 Processor and Core Peripherals
  */
#define __CM3_REV                           0x0201U     /*!< Core revision r2p1                             */
#define __MPU_PRESENT                       0U          /*!< MPU present                                    */
#define __VTOR_PRESENT                      1U          /*!< VTOR present                                   */
#define __NVIC_PRIO_BITS                    3U          /*!< Number of Bits used for Priority Levels        */
#define __Vendor_SysTickConfig              0U          /*!< Set to 1 if different SysTick Config is used   */

/**
  * @brief CMSIS Device version number v5.3.1
  */
#define __TAE32F53XX_CMSIS_VERSION_MAIN     (0x05)      /*!< [31:24] main version                           */
#define __TAE32F53XX_CMSIS_VERSION_SUB1     (0x03)      /*!< [23:16] sub1 version                           */
#define __TAE32F53XX_CMSIS_VERSION_SUB2     (0x01)      /*!< [15:8]  sub2 version                           */
#define __TAE32F53XX_CMSIS_VERSION_RC       (0x00)      /*!< [7:0]  release candidate                       */
#define __TAE32F53XX_CMSIS_VERSION          ((__TAE32F53XX_CMSIS_VERSION_MAIN << 24) |\
                                             (__TAE32F53XX_CMSIS_VERSION_SUB1 << 16) |\
                                             (__TAE32F53XX_CMSIS_VERSION_SUB2 << 8 ) |\
                                             (__TAE32F53XX_CMSIS_VERSION_RC))
/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>                 /*!< Standard int head file         */
#include "core_cm3.h"               /*!< Processor and core peripherals */
#include "system_tae32f53xx.h"      /*!< TAE32F53xx System Header       */


/** @defgroup TAE32F53xx_Peripheral_Registers_Structures TAE32F53xx Peripheral Registers Structures
  * @brief    TAE32F53xx Peripheral Registers Structures
  * @{
  */

/**
  * @brief Embedded FLASH Controller Registers Structure
  */
typedef struct {
    __IO uint32_t CR;               /*!< Address offset: 0x00: FLASH Control Register           */
    __IO uint32_t LPR;              /*!< Address offset: 0x04: FLASH Lowpower Register          */
    __IO uint32_t ISR;              /*!< Address offset: 0x08: FLASH Interrupt Status Register  */
    __IO uint32_t SR;               /*!< Address offset: 0x0C: FLASH Status Register            */
    __IO uint32_t DR0;              /*!< Address offset: 0x10: FLASH Data Register 0            */
    __IO uint32_t DR1;              /*!< Address offset: 0x14: FLASH Data Register 1            */
    __IO uint32_t DR2;              /*!< Address offset: 0x18: FLASH Data Register 2            */
    __IO uint32_t DR3;              /*!< Address offset: 0x1C: FLASH Data Register 3            */
    __IO uint32_t ADDR;             /*!< Address offset: 0x20: FLASH Address Register           */
    __I  uint32_t RESERVED0;        /*!< Reserved                                               */
    __IO uint32_t ECR;              /*!< Address offset: 0x28: FLASH Erase Control Register     */
    __I  uint32_t RESERVED1;        /*!< Reserved                                               */
    __IO uint32_t TR0;              /*!< Address offset: 0x30: FLASH Timing Register 0          */
    __IO uint32_t TR1;              /*!< Address offset: 0x34: FLASH Timing Register 1          */
    __IO uint32_t TR2;              /*!< Address offset: 0x38: FLASH Timing Register 2          */
    __IO uint32_t TR3;              /*!< Address offset: 0x3C: FLASH Timing Register 3          */
    __I  uint32_t RESERVED2[4];     /*!< Reserved                                               */
    __IO uint32_t KEYR;             /*!< Address offset: 0x50: FLASH Key Register               */
    __I  uint32_t RESERVED3[3];     /*!< Reserved                                               */
    __IO uint32_t RDPR;             /*!< Address offset: 0x60: FLASH Read Protect Register      */
    __I  uint32_t RESERVED4[3];     /*!< Reserved                                               */
    __IO uint32_t WRPR;             /*!< Address offset: 0x70: FLASH Write Protect Register     */
    __I  uint32_t RESERVED5[3];     /*!< Reserved                                               */
    __IO uint32_t UID[4];           /*!< Address offset: 0x80: FLASH Unique Identification      */
} FLASH_TypeDef;


/**
  * @brief Data FLASH Controller Registers Structure
  */
typedef struct {
    __IO uint32_t CR;               /*!< Address offset: 0x00: DFLASH Control Register          */
    __IO uint32_t LPR;              /*!< Address offset: 0x04: DFLASH Lowpower Register         */
    __IO uint32_t ISR;              /*!< Address offset: 0x08: DFLASH Interrupt Status Register */
    __IO uint32_t SR;               /*!< Address offset: 0x0C: DFLASH Status Register           */
    __IO uint32_t DR;               /*!< Address offset: 0x10: DFLASH Data Register             */
    __IO uint32_t ADDR;             /*!< Address offset: 0x14: DFLASH Address Register          */
    __IO uint32_t ECR;              /*!< Address offset: 0x18: DFLASH Erase Control Register    */
    __I  uint32_t RESERVED0;        /*!< Reserved                                               */
    __IO uint32_t TR0;              /*!< Address offset: 0x20: DFLASH Timing Register 0         */
    __IO uint32_t TR1;              /*!< Address offset: 0x24: DFLASH Timing Register 1         */
    __IO uint32_t TR2;              /*!< Address offset: 0x28: DFLASH Timing Register 2         */
    __IO uint32_t TR3;              /*!< Address offset: 0x2C: DFLASH Timing Register 3         */
    __IO uint32_t KEYR;             /*!< Address offset: 0x30: DFLASH Key Register              */
} DFLASH_TypeDef;


/**
  * @brief General Purpose I/O (GPIO) Registers Structure
  */
typedef struct {
    __IO uint32_t BSRR;             /*!< Address offset: 0x00: GPIO Bit Set/Reset Register                      */
    __IO uint32_t DR;               /*!< Address offset: 0x04: GPIO Data Register                               */
    __IO uint32_t PUR;              /*!< Address offset: 0x08: GPIO Pullup Register                             */
    __IO uint32_t PDR;              /*!< Address offset: 0x0C: GPIO Pulldown Register                           */
    __IO uint32_t DSR;              /*!< Address offset: 0x10: GPIO Driver Strength Register                    */
    __IO uint32_t IHYR;             /*!< Address offset: 0x14: GPIO Input Hysteresis Register                   */
    __IO uint32_t OTYPR;            /*!< Address offset: 0x18: GPIO Output Type Register                        */
    __IO uint32_t OSRR;             /*!< Address offset: 0x1C: GPIO Output Slew Rate Register                   */
    __IO uint32_t IER;              /*!< Address offset: 0x20: GPIO Interrupt Enable Register                   */
    __IO uint32_t ITER;             /*!< Address offset: 0x24: GPIO Interrupt Trigger Enable Register           */
    __IO uint32_t RFTSR;            /*!< Address offset: 0x28: GPIO Rising/Falling Trigger Selection Register   */
    __IO uint32_t PR;               /*!< Address offset: 0x2C: GPIO Pending Register                            */
    __IO uint32_t SDER;             /*!< Address offset: 0x30: GPIO Sync/Debounce Enable Register               */
    __I  uint32_t RESERVED0[3];     /*!< Reserved                                                               */
    __IO uint32_t PMUXR[2];         /*!< Address offset: 0x40: GPIO Pin-Mux Register                            */
} GPIO_TypeDef;


/**
  * @brief Window WATCHDOG (WWDG) Registers Structure
  */
typedef struct {
    __IO uint32_t CR;               /*!< Address offset: 0x00: WWDG Control Register            */
    __IO uint32_t WVR;              /*!< Address offset: 0x04: WWDG Window Value Register       */
    __IO uint32_t CVR;              /*!< Address offset: 0x08: WWDG Counter Value Register      */
    __IO uint32_t PSCR;             /*!< Address offset: 0x0C: WWDG Prescaler Register          */
    __IO uint32_t ISR;              /*!< Address offset: 0x10: WWDG Interrupt Status Register   */
} WWDG_TypeDef;


/**
  * @brief Independent WATCHDOG (IWDG) Registers Structure
  */
typedef struct {
    __IO uint32_t KEYR;             /*!< Address offset: 0x00: IWDG Key register        */
    __IO uint32_t CR;               /*!< Address offset: 0x04: IWDG Control register    */
    __IO uint32_t RLR;              /*!< Address offset: 0x08: IWDG Reload register     */
    __IO uint32_t PSCR;             /*!< Address offset: 0x0C: IWDG Prescaler register  */
    __IO uint32_t SR;               /*!< Address offset: 0x10: IWDG Status register     */
} IWDG_TypeDef;


/**
  * @brief Infinite Impulse Response (IIR) Registers Structure
  */
typedef struct {
    __IOM uint32_t CR0;             /*!< Address offset: 0x00: IIR Control Register                     */
    __IOM uint32_t CR1;             /*!< Address offset: 0x04: IIR Start Register                       */
    __IOM uint32_t IER;             /*!< Address offset: 0x08: IIR Interrupt Register                   */
    __IOM uint32_t ISR;             /*!< Address offset: 0x0C: IIR Pending Register                     */
    __IM  uint32_t RESERVED0;       /*!< Reserved                                                       */
    __IOM uint32_t DOR;             /*!< Address offset: 0x14: IIR DataO Register                       */
    __IM  uint32_t RESERVED1[3];    /*!< Reserved                                                       */
    __IOM uint32_t DIAR;            /*!< Address offset: 0x24: IIR DataI Address Register               */
    __IM  uint32_t RESERVED2;       /*!< Reserved                                                       */
    __IOM uint32_t SCALR;           /*!< Address offset: 0x2C: IIR Scale Register                       */
    __IOM uint32_t BxCOEFR[5];      /*!< Address offset: 0x30: IIR BxCOEF Register(x = 0...4)           */
    __IOM uint32_t AxCOEFR[4];      /*!< Address offset: 0x44: IIR AxCOEF Register(x = 1...4)           */
    __IM  uint32_t RESERVED3[4];    /*!< Reserved                                                       */
    __IOM uint32_t DIASR;           /*!< Address offset: 0x64: IIR DataI Addr Shadow Register           */
    __IM  uint32_t RESERVED4;       /*!< Reserved                                                       */
    __IOM uint32_t SCALSR;          /*!< Address offset: 0x6C: IIR Scale Shadow Register                */
    __IOM uint32_t BxCOEFSR[5];     /*!< Address offset: 0x70: IIR B0COEF Shadow Register(x = 0...4)    */
    __IOM uint32_t AxCOEFSR[4];     /*!< Address offset: 0x84: IIR A1COEF Shadow Register(x = 1...4)    */
} IIR_TypeDef;


/**
  * @brief TIMER Registers Structure
  */
typedef struct {
    __IOM uint32_t CR;              /*!< Address offset: 0x00: Timer Counter Control Register           */
    __IOM uint32_t CCCR;            /*!< Address offset: 0x04: Timer Capture Compare Control Register   */
    __IOM uint32_t EGR;             /*!< Address offset: 0x08: Timer Event Generation Register          */
    __IOM uint32_t ICFR;            /*!< Address offset: 0x0C: Timer Input Capture Filter Register      */
    __IOM uint32_t ISR;             /*!< Address offset: 0x10: Timer Interrupt Status Register          */
    __IM  uint32_t RESERVED[3];     /*!< Reserved                                                       */
    __IOM uint32_t CSVR;            /*!< Address offset: 0x20: Timer Counter Start Register             */
    __IOM uint32_t CEVR;            /*!< Address offset: 0x24: Timer Counter End Register               */
    __IOM uint32_t CCR;             /*!< Address offset: 0x28: Timer Capture Compare Register           */
    __IOM uint32_t PSCR;            /*!< Address offset: 0x2C: Timer Prescaler Register                 */
    __IOM uint32_t CNTR;            /*!< Address offset: 0x30: Timer Counter Register                   */
    __IOM uint32_t ETER;            /*!< Address offset: 0x34: Timer Export Trigger Event Register      */
} TMR_TypeDef;

/**
  * @brief TIMERGRP (Timer Group Sync Register) Registers Structure
  */
typedef struct {
    __IOM uint32_t SYNCR;           /*!< Timer Group Sync Register                                      */
} TMRGRP_TypeDef;


/**
  * @brief UART Registers Structure
  */
typedef struct {
    union {
        __IOM uint32_t RBR;         /*!< Address offset: 0x00: Receive Buffer Register              */
        __IOM uint32_t THR;         /*!< Address offset: 0x00: Transmit Holding Register            */
        __IOM uint32_t DLL;         /*!< Address offset: 0x00: Divisor Latch Low                    */
    };
    union {
        __IOM uint32_t DLH;         /*!< Address offset: 0x04: Divisor Latch High                   */
        __IOM uint32_t IER;         /*!< Address offset: 0x04: Interrupt Enable Register            */
    };
    union {
        __IOM uint32_t IIR;         /*!< Address offset: 0x08: Interrupt Identity Register          */
        __IOM uint32_t FCR;         /*!< Address offset: 0x08: FIFO Control Register                */
    };
    __IOM uint32_t LCR;             /*!< Address offset: 0x0C: Line Control Register                */
    __IM  uint32_t RESERVED0;       /*!< Address offset: 0x10: Reserved                             */
    __IOM uint32_t LSR;             /*!< Address offset: 0x14: Line Status Register                 */
    __IM  uint32_t RESERVED1[25];   /*!< Address offset: 0x18~0x78: Reserved                        */
    __IOM uint32_t USR;             /*!< Address offset: 0x7C: UART Status Register                 */
    __IOM uint32_t TFL;             /*!< Address offset: 0x80: Transmit FIFO Level                  */
    __IOM uint32_t RFL;             /*!< Address offset: 0x84: Receive FIFO Level                   */
    __IM  uint32_t RESERVED2[7];    /*!< Address offset: 0x88~0xA0: Reserved                        */
    __IOM uint32_t HTX;             /*!< Address offset: 0xA4: Halt TX                              */
    __IM  uint32_t RESERVED3;       /*!< Address offset: 0xA8: Reserved                             */
    __IOM uint32_t TCR;             /*!< Address offset: 0xAC: Transceiver Control Register         */
    __IOM uint32_t DE_EN;           /*!< Address offset: 0xB0: Driver Output Enable Register        */
    __IOM uint32_t RE_EN;           /*!< Address offset: 0xB4: Receiver Output Enable Register      */
    __IOM uint32_t DET;             /*!< Address offset: 0xB8: Driver Output Enable Timing Register */
    __IOM uint32_t TAT;             /*!< Address offset: 0xBC: TurnAround Timing Register           */
    __IOM uint32_t DLF;             /*!< Address offset: 0xC0: Divisor Latch Fraction Register      */
    __IOM uint32_t RAR;             /*!< Address offset: 0xC4: Receive Address Register             */
    __IOM uint32_t TAR;             /*!< Address offset: 0xC8: Transmit Address Register            */
    __IOM uint32_t LCR_EXT;         /*!< Address offset: 0xCC: Line Extended Control Register       */
} UART_TypeDef;


/**
  * @brief DMA Channel Numbers
  */
#define DMA_CHN_NB      2

/**
  * @brief DMA Channel
  */
typedef struct {
    __IO uint32_t SAR;              /*!< Address offset: 0x00: DMA Channel Source Address Register      */
    __I  uint32_t RESERVED0;        /*!< Address offset: 0x04: Reserved                                 */
    __IO uint32_t DAR;              /*!< Address offset: 0x08: DMA Channel Destination Address Register */
    __I  uint32_t RESERVED1[3];     /*!< Address offset: 0x0C~0x14: Reserved                            */
    __IO uint32_t CR0;              /*!< Address offset: 0x18: DMA Channel Control Register0            */
    __IO uint32_t CR1;              /*!< Address offset: 0x1C: DMA Channel Control Register1            */
    __I  uint32_t RESERVED2[8];     /*!< Address offset: 0x20~0x3C: Reserved                            */
    __IO uint32_t CR2;              /*!< Address offset: 0x40: DMA Channel Config Register0             */
    __IO uint32_t CR3;              /*!< Address offset: 0x44: DMA Channel Config Register1             */
    __IO uint32_t RESERVED3[4];     /*!< Address offset: 0x48~0x54: Reserved                            */
} DMA_CH_TypeDef;

/**
  * @brief DMA Registers Structure
  */
typedef struct {
    DMA_CH_TypeDef CH[DMA_CHN_NB];  /*!< DMA Channel control Register                                               */

    __IM  uint32_t RESERVED4[132];  /*!< Reserved                                                                   */
    __IOM uint32_t TSR;             /*!< Address offset: 0x2C0: DMA Tranfer Status Register                         */
    __IM  uint32_t RESERVED5;       /*!< Reserved                                                                   */
    __IOM uint32_t BTSR;            /*!< Address offset: 0x2C8: DMA Block Tranfer Status Register                   */
    __IM  uint32_t RESERVED6;       /*!< Reserved                                                                   */
    __IOM uint32_t STSR;            /*!< Address offset: 0x2D0: DMA Source Transfer Status Register                 */
    __IM  uint32_t RESERVED7;       /*!< Reserved                                                                   */
    __IOM uint32_t DTSR;            /*!< Address offset: 0x2D8: DMA Destination Transfer Status Register            */
    __IM  uint32_t RESERVED8;       /*!< Reserved                                                                   */
    __IOM uint32_t TESR;            /*!< Address offset: 0x2E0: DMA Transfer Error Status Register                  */
    __IM  uint32_t RESERVED9;       /*!< Reserved                                                                   */
    __IOM uint32_t TIPR;            /*!< Address offset: 0x2E8: DMA Transfer Interrupt Pending Register             */
    __IM  uint32_t RESERVED10;      /*!< Reserved                                                                   */
    __IOM uint32_t BTIPR;           /*!< Address offset: 0x2F0: DMA Block Transfer Interrupt Pending Register       */
    __IM  uint32_t RESERVED11;      /*!< Reserved                                                                   */
    __IOM uint32_t STIPR;           /*!< Address offset: 0x2F8: DMA Source Transfer Interrupt Pending Register      */
    __IM  uint32_t RESERVED12;      /*!< Reserved                                                                   */
    __IOM uint32_t DTIPR;           /*!< Address offset: 0x300: DMA Destination Transfer Interrupt Pending Register */
    __IM  uint32_t RESERVED13;      /*!< Reserved                                                                   */
    __IOM uint32_t TEIPR;           /*!< Address offset: 0x308: DMA Transfer Error Interrupt Pending Register       */
    __IM  uint32_t RESERVED14;      /*!< Reserved                                                                   */
    __IOM uint32_t TIMR;            /*!< Address offset: 0x310: DMA Transfer Interrupt Mask Register                */
    __IM  uint32_t RESERVED15;      /*!< Reserved                                                                   */
    __IOM uint32_t BTIMR;           /*!< Address offset: 0x318: DMA Block Transfer Interrupt Mask Register          */
    __IM  uint32_t RESERVED16;      /*!< Reserved                                                                   */
    __IOM uint32_t STIMR;           /*!< Address offset: 0x320: DMA Source Transfer IntClear Register               */
    __IM  uint32_t RESERVED17;      /*!< Reserved                                                                   */
    __IOM uint32_t DTIMR;           /*!< Address offset: 0x328: DMA Destination Transfer Interrupt Mask Register    */
    __IM  uint32_t RESERVED18;      /*!< Reserved                                                                   */
    __IOM uint32_t TEIMR;           /*!< Address offset: 0x330: DMA Transfer Error Interrupt Mask Register          */
    __IM  uint32_t RESERVED19;      /*!< Reserved                                                                   */
    __IOM uint32_t TCR;             /*!< Address offset: 0x338: DMA Transfer Clear Register                         */
    __IM  uint32_t RESERVED20;      /*!< Reserved                                                                   */
    __IOM uint32_t BTCR;            /*!< Address offset: 0x340: DMA Block Transfer Clear Register                   */
    __IM  uint32_t RESERVED21;      /*!< Reserved                                                                   */
    __IOM uint32_t STCR;            /*!< Address offset: 0x348: DMA Source Transfer Clear Register                  */
    __IM  uint32_t RESERVED22;      /*!< Reserved                                                                   */
    __IOM uint32_t DTCR;            /*!< Address offset: 0x350: DMA Destination Transfer Clear Register             */
    __IM  uint32_t RESERVED23;      /*!< Reserved                                                                   */
    __IOM uint32_t TECR;            /*!< Address offset: 0x358: DMA Transfer Error Clear Register                   */
    __IM  uint32_t RESERVED24[15];  /*!< Reserved                                                                   */
    __IOM uint32_t CR0;             /*!< Address offset: 0x398: DMA Control Register0                               */
    __IM  uint32_t RESERVED25;      /*!< Reserved                                                                   */
    __IOM uint32_t CR1;             /*!< Address offset: 0x3A0: DMA Control Register1                               */
} DMA_TypeDef;


/**
  * @brief ADC DMA
  */
typedef struct {
    __IO uint32_t TCR;              /*!< Address offset: 0x110: ADC Transfer Control Register   */
    __IO uint32_t TAR;              /*!< Address offset: 0x114: ADC Transfer Address Register   */
    __I  uint32_t RESERVED;         /*!< Reserved                                               */
    __IO uint32_t TLR;              /*!< Address offset: 0x11C: ADC Transfer Length Register    */
} ADC_DMA_TypeDef;

/**
  * @brief Analog to Digital Converter (ADC) Registers Structure
  */
typedef struct {
    __IO uint32_t CR0;              /*!< Address offset: 0x00 : ADC Control Register 0                  */
    __IO uint32_t CR1;              /*!< Address offset: 0x04 : ADC Control Register 1                  */
    __IO uint32_t CR2;              /*!< Address offset: 0x08 : ADC Control Register 2                  */
    __IO uint32_t DIFSEL;           /*!< Address offset: 0x0C : ADC Differential Select Register        */
    __IO uint32_t IER;              /*!< Address offset: 0x10 : ADC Interrupt Enable Register           */
    __IO uint32_t ISR;              /*!< Address offset: 0x14 : ADC Interrupt Status Register           */
    __IO uint32_t SIER;             /*!< Address offset: 0x18 : ADC Sample Interrupt Enable Register    */
    __IO uint32_t SISR;             /*!< Address offset: 0x1C : ADC Sample Interrupt Status Register    */
    __IO uint32_t SMPR0;            /*!< Address offset: 0x20 : ADC Sample Time Register 0              */
    __IO uint32_t SMPR1;            /*!< Address offset: 0x24 : ADC Sample Time Register 1              */
    __IO uint32_t CALR0;            /*!< Address offset: 0x28 : ADC Calibration Data Register 0         */
    __IO uint32_t CALR1;            /*!< Address offset: 0x2C : ADC Calibration Data Register 1         */
    __IO uint32_t SQR0;             /*!< Address offset: 0x30 : ADC Regular Sequence Register 0         */
    __IO uint32_t SQR1;             /*!< Address offset: 0x34 : ADC Regular Sequence Register 1         */
    __IO uint32_t LR;               /*!< Address offset: 0x38 : ADC Regular Length Register             */
    __IO uint32_t DR;               /*!< Address offset: 0x3C : ADC Regular Data Register               */
    __IO uint32_t JSQR;             /*!< Address offset: 0x40 : ADC Injected Sequence Register          */
    __IO uint32_t JLR;              /*!< Address offset: 0x44 : ADC Injected Length Register            */
    __I  uint32_t RESERVED0[2];     /*!< Reserved                                                       */
    __IO uint32_t JDR[4];           /*!< Address offset: 0x50 : ADC Injected Data Register              */
    __IO uint32_t TR[3];            /*!< Address offset: 0x60 : ADC Watchdog Threshold Register         */
    __I  uint32_t RESERVED1;        /*!< Reserved                                                       */
    __IO uint32_t AWDCR[3];         /*!< Address offset: 0x70 : ADC Watchdog Control Register           */
    __I  uint32_t RESERVED2;        /*!< Reserved                                                       */
    __IO uint32_t OFR[4];           /*!< Address offset: 0x80 : ADC Single-End Offset Register          */
    __IO uint32_t DOFR[4];          /*!< Address offset: 0x90 : ADC Differential Offset Register        */
    __IO uint32_t GCR[4];           /*!< Address offset: 0xA0 : ADC Single-End Gain Coeff Register      */
    __IO uint32_t DGCR[4];          /*!< Address offset: 0xB0 : ADC Channel Data Register               */
    __IO uint32_t ECR[4];           /*!< Address offset: 0xC0 : ADC Event Control Register              */
    __I  uint32_t CDR[12];          /*!< Address offset: 0xD0 : ADC Differential Gain Coeff Register    */
    __IO uint32_t HIER;             /*!< Address offset: 0x100: ADC Half Interrupt Enable Register      */
    __IO uint32_t HISR;             /*!< Address offset: 0x104: ADC Half Interrupt Status Register      */
    __IO uint32_t FIER;             /*!< Address offset: 0x108: ADC Full Interrupt Enable Register      */
    __IO uint32_t FISR;             /*!< Address offset: 0x10C: ADC Full Interrupt Status Register      */
    ADC_DMA_TypeDef DMA_CR[12];     /*!< Address offset: 0x110: ADC Transfer Control Register           */
} ADC_TypeDef;


/**
  * @brief DAC Channel Numbers
  */
#define DAC_CHN_NB      4

/**
  * @brief Digital to Analog Converter Registers Structure
  */
typedef struct {
    __IO uint32_t CR[DAC_CHN_NB];   /*!< DAC Control Register                   */
    __IO uint32_t ISR;              /*!< DAC Interrupt Status Register          */
    __IO uint32_t SWTR;             /*!< DAC Software Trigger Register          */
    __I  uint32_t RESERVED0[2];     /*!< Reserved                               */
    __IO uint32_t WDR[DAC_CHN_NB];  /*!< DAC Write Data Register                */
    __IO uint32_t RDR[DAC_CHN_NB];  /*!< DAC Read Data Register                 */
    __IO uint32_t SIDR[DAC_CHN_NB]; /*!< DAC Sawtooth Increment Data Register   */
    __IO uint32_t SRDR[DAC_CHN_NB]; /*!< DAC Sawtooth Reset Data Register       */
} DAC_TypeDef;


/**
  * @brief CMP Channel Number
  */
#define CMP_CHN_NB      4

/**
  * @brief Comparator (CMP) Registers Structure
  */
typedef struct {
    __IO uint32_t CR[CMP_CHN_NB];   /*!< CMP Control Register   */
    __IO uint32_t SR;               /*!< CMP Status Register    */
    __IO uint32_t DEBR[CMP_CHN_NB]; /*!< CMP Debounce Register  */
} CMP_TypeDef;


/**
  * @brief Electricity Calculate Unit (ECU) Registers Structure
  */
typedef struct {
    __IO uint32_t CON;              /*!< Address offset: 0x00: ECU Control Register                 */
    __IO uint32_t PRC;              /*!< Address offset: 0x04: ECU Exit Event Select Register       */
    __IO uint32_t SQRT_IN;          /*!< Address offset: 0x08: ECU Sqrt Data Input Register         */
    __I  uint32_t SQRT_OUT;         /*!< Address offset: 0x0C: ECU Sqrt Data Output Register        */
    __IO uint32_t V_ADDR1;          /*!< Address offset: 0x10: ECU V Data Addr Register             */
    __IO uint32_t V_ADDR2;          /*!< Address offset: 0x14: ECU Register                         */
    __IO uint32_t I_ADDR1;          /*!< Address offset: 0x18: ECU I Data Addr Register             */
    __IO uint32_t I_ADDR2;          /*!< Address offset: 0x1C: ECU Register                         */
    __I  uint32_t V;                /*!< Address offset: 0x20: ECU V Data Read Register             */
    __I  uint32_t I;                /*!< Address offset: 0x24: ECU I Data Read Register             */
    __I  uint32_t P;                /*!< Address offset: 0x28: ECU P Data Read Register             */
    __I  uint32_t Q;                /*!< Address offset: 0x2C: ECU Q Data Read Register             */
    __I  uint32_t S;                /*!< Address offset: 0x30: ECU S Data Read Register             */
    __I  uint32_t PF;               /*!< Address offset: 0x34: ECU PF Data Read Register            */
    __I  uint32_t F;                /*!< Address offset: 0x38: ECU F Data Read Register             */
} ECU_TypeDef;


/**
  * @brief HRPWM Master Registers
  */
typedef struct {
    __IO uint32_t MCR ;             /*!< Address offset: 0x00: HRPWM Master PWM Control Register            */
    __I  uint32_t RESERVED0 ;       /*!< Reserved                                                           */
    __IO uint32_t MISR;             /*!< Address offset: 0x08: HRPWM Master PWM Interrupt Status Register   */
    __IO uint32_t MIER;             /*!< Address offset: 0x0C: HRPWM Master PWM Interrupt Enable Register   */
    __IO uint32_t MCNTR;            /*!< Address offset: 0x10: HRPWM Master PWM Counter Register            */
    __IO uint32_t MPER;             /*!< Address offset: 0x14: HRPWM Master Period Value Register           */
    __IO uint32_t MCMPAR;           /*!< Address offset: 0x18: HRPWM Master PWM Cmp A Value Register        */
    __IO uint32_t MCMPBR;           /*!< Address offset: 0x1c: HRPWM Master PWM Cmp B Value Register        */
    __IO uint32_t MCMPCR;           /*!< Address offset: 0x20: HRPWM Master PWM Cmp C Value Register        */
    __IO uint32_t MCMPDR;           /*!< Address offset: 0x24: HRPWM Master PWM Cmp D Value Register        */
    __I  uint32_t RESERVED1[22];    /*!< Reserved                                                           */
} HRPWM_MSTR_TypeDef;

/**
  * @brief HRPWM PWMx Registers
  */
typedef struct {
    __IO uint32_t CR0;              /*!< Address offset: 0x80: HRPWM Hrpwmx Control Register 0          */
    __IO uint32_t CR1;              /*!< Address offset: 0x84: HRPWM Hrpwmx Control Register 1          */
    __IO uint32_t ISR;              /*!< Address offset: 0x88: HRPWM Hrpwmx Interrupt Status Register   */
    __IO uint32_t IER;              /*!< Address offset: 0x8C: HRPWM Hrpwmx Interrupt Enable Register   */
    __IO uint32_t CNTR;             /*!< Address offset: 0x90: HRPWM Hrpwmx Counter Register            */
    __IO uint32_t PERR;             /*!< Address offset: 0x94: HRPWM Hrpwmx Period Value Register       */
    __IO uint32_t CMPAR;            /*!< Address offset: 0x98: HRPWM Hrpwmx Cmp A Register              */
    __IO uint32_t CMPBR;            /*!< Address offset: 0x9C: HRPWM Hrpwmx Cmp B Register              */
    __IO uint32_t CMPCR;            /*!< Address offset: 0xA0: HRPWM Hrpwmx Cmp C Register              */
    __IO uint32_t CMPDR;            /*!< Address offset: 0xA4: HRPWM Hrpwmx Cmp D Register              */
    __IO uint32_t DTR;              /*!< Address offset: 0xA8: HRPWM Hrpwmx Dead Time Register          */
    __IO uint32_t SETAR;            /*!< Address offset: 0xAC: HRPWM Hrpwmx Output A Set Register       */
    __IO uint32_t CLRAR;            /*!< Address offset: 0xB0: HRPWM Hrpwmx Output A Clear Register     */
    __IO uint32_t SETBR;            /*!< Address offset: 0xB4: HRPWM Hrpwmx Output B Set Register       */
    __IO uint32_t CLRBR;            /*!< Address offset: 0xB8: HRPWM Hrpwmx Output B Clear Register     */
    __IO uint32_t EEFR0;            /*!< Address offset: 0xBC: HRPWM Hrpwmx External Event Register     */
    __IO uint32_t EEFR1;            /*!< Address offset: 0xC0: HRPWM Hrpwmx External Event5 Register    */
    __IO uint32_t RSTR;             /*!< Address offset: 0xC4: HRPWM Hrpwmx Reset Register              */
    __IO uint32_t CHPR;             /*!< Address offset: 0xC8: HRPWM Hrpwmx Chopper Register            */
    __IO uint32_t OUTR;             /*!< Address offset: 0xCC: HRPWM Hrpwmx Output Register             */
    __IO uint32_t FLTR;             /*!< Address offset: 0xD0: HRPWM Hrpwmx Fault Register              */
    __I  uint32_t RESERVED[11];     /*!< Reserved                                                       */
} HRPWM_PWMx_TypeDef;

/**
  * @brief HRPWM Common Registers
  */
typedef struct {
    __IO uint32_t CR0;              /*!< Address offset: 0x380: HRPWM Control Register 0                */
    __IO uint32_t CR1;              /*!< Address offset: 0x384: HRPWM Control Register 1                */
    __IO uint32_t CR2;              /*!< Address offset: 0x388: HRPWM Control Register 2                */
    __IO uint32_t ISR;              /*!< Address offset: 0x38C: HRPWM Interrupt Status Register         */
    __IO uint32_t IER;              /*!< Address offset: 0x390: HRPWM Interrupt Enable Register         */
    __IO uint32_t OENR;             /*!< Address offset: 0x394: HRPWM Output Enable Register            */
    __IO uint32_t ODISR;            /*!< Address offset: 0x398: HRPWM Output Disable Register           */
    __IO uint32_t EECR0;            /*!< Address offset: 0x39C: HRPWM External Event Register 0         */
    __IO uint32_t EECR1;            /*!< Address offset: 0x3A0: HRPWM External Event Register 1         */
    __IO uint32_t EECR2;            /*!< Address offset: 0x3A4: HRPWM External Event Register 2         */
    __IO uint32_t ADTR[8];          /*!< Address offset: 0x3A8: HRPWM ADDA Trigger Post Scaler Register */
    __IO uint32_t ADPSR;            /*!< Address offset: 0x3C8: HRPWM SOC Length Register               */
    __IO uint32_t DLLCR;            /*!< Address offset: 0x3CC: HRPWM DLL Control Register              */
    __IO uint32_t FLTINR0;          /*!< Address offset: 0x3D0: HRPWM Fault Input Register 0            */
    __IO uint32_t FLTINR1;          /*!< Address offset: 0x3D4: HRPWM Fault Input Register 1            */
    __IO uint32_t FLTINR2;          /*!< Address offset: 0x3D8: HRPWM Fault Input Register 2            */
    __IO uint32_t FLTINR3;          /*!< Address offset: 0x3DC: HRPWM Fault Input Register 3            */
} HRPWM_COMMON_TypeDef;

/**
  * @brief High Resolution PWM (HRPWM) Registers Structure
  */
typedef struct {
    HRPWM_MSTR_TypeDef   Master;    /*!< HRPWM Master Registers */
    HRPWM_PWMx_TypeDef   PWM[6];    /*!< HRPWM PWMx Registers   */
    HRPWM_COMMON_TypeDef Common;    /*!< HRPWM Common Registers */
} HRPWM_TypeDef;


/**
  * @brief USB DMA
  */
typedef struct __attribute__((packed)) {
    __IO uint16_t CTRL;             /*!< Address offset: 0x00      USB DMA Control Register */
    __I  uint8_t  RESERVED0[2];     /*!< Address offset: 0x02~0x03 Reserverd                */
    __IO uint32_t ADDR;             /*!< Address offset: 0x04      USB DMA Address Register */
    __IO uint32_t CNT;              /*!< Address offset: 0x08      USB DMA Count Register   */
    __I  uint8_t  RESERVED1[4];     /*!< Address offset: 0x0C~0x0F Reserverd                */
} USB_DMA;

/**
  * @brief USB Registers Structure
  */
typedef struct __attribute__((packed)) {
    /* USB Common Register */
    __IO uint8_t  FADDR;            /*!<Address offset: 0x00: USB Function Address Register                         */
    __IO uint8_t  POWER;            /*!<Address offset: 0x01: USB Power Control Register                            */
    __IO uint16_t INTRTX;           /*!<Address offset: 0x02: USB TX Endpoint Interrupt Status Register             */
    __IO uint16_t INTRRX;           /*!<Address offset: 0x04: USB RX Endpoint Interrupt Status Register             */
    __IO uint16_t INTRTXE;          /*!<Address offset: 0x06: USB TX Endpoint Interrupt Enable Register             */
    __IO uint16_t INTRRXE;          /*!<Address offset: 0x08: USB RX Endpoint Interrupt Enable Register             */
    __IO uint8_t  INTRUSB;          /*!<Address offset: 0x0A: USB Interrupt Status Register                         */
    __IO uint8_t  INTRUSBE;         /*!<Address offset: 0x0B: USB Interrupt Enable Register                         */
    __IO uint16_t FRAME;            /*!<Address offset: 0x0C: USB Latest Frame Number Register                      */
    __IO uint8_t  INDEX;            /*!<Address offset: 0x0E: USB Endpoint Index Register                           */
    __IM uint8_t  RESERVED0;        /*!<Address offset: 0x0F: USB Test Mode Config Register                         */

    /* USB EndpointX Control/Status Register Array */
    __IO uint16_t TXMAXP;           /*!<Address offset: 0x10: USB TX MAX Payload Register                           */
    union {
        __IO uint16_t TX_CSR0;      /*!<Address offset: 0x12: USB Endpoint 0 Control/Status Register                */
        __IO uint16_t TX_CSRX;      /*!<Address offset: 0x12: USB TX Endpoint X(except 0) Control/Status Register   */
    } __attribute__((packed));
    __IO uint16_t RXMAXP;           /*!<Address offset: 0x14: USB RX MAX Payload Register                           */
    __IO uint16_t RXCSRN;           /*!<Address offset: 0x16: USB RX Endpoint X(except 0) Control/Status Register   */
    __IO uint16_t RXCOUNT;          /*!<Address offset: 0x18: USB RX Count Register                                 */
    __I  uint8_t  RESERVED1[5];     /*!<Address offset: 0x1A~0x1E: Reserved                                         */
    __IO uint8_t  FIFOSIZE;         /*!<Address offset: 0x1F: USB TX/RX FIFO Size Register                          */

    /* USB FIFO Register */
    __IO uint8_t  EP_FIFO[3][4];    /*!<Address offset: 0x20~0x28: USB Endpoint 0/1/2 FIFO Register                 */
    __I  uint8_t  RESERVED2[468];   /*!<Address offset: 0x2C~0x1FF: Reserved                                        */

    /* USB DMA Control Register */
    __IO uint8_t  DMA_INTR;         /*!<Address offset: 0x200: USB DMA Interrupt Status Register                    */
    __I  uint8_t  RESERVED3[3];     /*!<Address offset: 0x201~0x203: Reserved                                       */
    __IO USB_DMA  DMA_CTRL[2];      /*!<Address offset: 0x204~0x223: USB DMA Control Register                       */
    __I  uint8_t  RESERVED4[284];   /*!<Address offset: 0x224~0x33F: Reserved                                       */

    /* USB Extended Register */
    __IO uint16_t RX_DPBUF_DIS;     /*!<Address offset: 0x340: USB RX Double Packet Buffer Disable Register         */
    __IO uint16_t TX_DPBUF_DIS;     /*!<Address offset: 0x342: USB TX Double Packet Buffer Disable Register         */
    __I  uint8_t  RESERVED5[188];   /*!<Address offset: 0x344~0x3FF: Reserved                                       */

    /* USB User Config Register */
    __IO uint32_t UCFG0;            /*!<Address offset: 0x400: USB Config Register 0                                */
    __IO uint32_t UCFG1;            /*!<Address offset: 0x404: USB Config Register 1                                */
    __IO uint32_t UCFG2;            /*!<Address offset: 0x408: USB Config Register 2                                */
} USB_TypeDef;


/**
  * @brief LVD Control Registers Structure
  */
typedef struct {
    __IO uint32_t LACR;             /*!<Address offset: 0x00: LVD Analog Contorl Register   */
    __IO uint32_t LCR;              /*!<Address offset: 0x04: LVD Control Register          */
} LVD_TypeDef;


/**
  * @brief Frac PLL 0/1/2 Registers Structure
  */
typedef struct {
    __IO uint32_t FCR;              /*!<Address offset: 0x00: FPLL Control Register */
    __IO uint32_t FDR;              /*!<Address offset: 0x04: FPLL Divisor Register */
} FPLL_TypeDef;


/**
  * @brief System Control (SYS_CTRL) Registers Structure
  */
typedef struct {
    __IO uint32_t PLL0CR;           /*!<Address offset: 0x00: PLL0 Control Register             */
    __IO uint32_t PLL1CR;           /*!<Address offset: 0x04: PLL1 Control Register             */
    __IO uint32_t PLL2CR;           /*!<Address offset: 0x08: PLL2 Control Register             */
    __I  uint32_t RESERVED0;        /*!<Address offset: 0x0C: Reserved                          */
    __IO uint32_t SCLKCR;           /*!<Address offset: 0x10: SCLK Control Register             */
    __IO uint32_t BCLKCR;           /*!<Address offset: 0x14: BCLK Control Register             */
    __IO uint32_t FSRCCR;           /*!<Address offset: 0x18: FCLK Source Register              */
    __I  uint32_t RESERVED1;        /*!<Address offset: 0x1C: Reserved                          */
    __IO uint32_t FCD0CR;           /*!<Address offset: 0x20: FCLK Divide Register0             */
    __I  uint32_t RESERVED2;        /*!<Address offset: 0x24: Reserved                          */
    __IO uint32_t FCD1CR;           /*!<Address offset: 0x28: FCLK Divider Register1            */
    __I  uint32_t RESERVED3;        /*!<Address offset: 0x2C: Reserved                          */
    __IO uint32_t APB0CCR;          /*!<Address offset: 0x30: APB0CLK Control Register          */
    __IO uint32_t APB1CCR;          /*!<Address offset: 0x34: APB1CLK Control Register          */
    __IO uint32_t AHBCCR;           /*!<Address offset: 0x38: AHBCLK Control Register           */
    __IO uint32_t FUNCCR;           /*!<Address offset: 0x3C: FUNCLK Control Register           */
    __IO uint32_t SYSRCR;           /*!<Address offset: 0x40: SYSRST Control Register           */
    __IO uint32_t APB0RCR;          /*!<Address offset: 0x44: APB0RST Control Register          */
    __IO uint32_t APB1RCR;          /*!<Address offset: 0x48: APB1RST Control Register          */
    __IO uint32_t AHBRCR;           /*!<Address offset: 0x4C: AHBRST Control Register           */
    __I  uint32_t RESERVED4[4];     /*!<Address offset: 0x50 - 0x5C: Reserved                   */
    __IO uint32_t XOSCCR;           /*!<Address offset: 0x60: XOSC Control Register             */
    __IO uint32_t XASWCR;           /*!<Address offset: 0x64: XCSS Control Register             */
    __IO uint32_t BUFCR;            /*!<Address offset: 0x68: ADCBUF Control Register           */
    __IO uint32_t SYSCCR;           /*!<Address offset: 0x6C: System Control Register           */
    __IO uint32_t SRSTSR;           /*!<Address offset: 0x70: Reset Status Register             */
    __I  uint32_t RESERVED5[3];     /*!<Address offset: 0x74 - 0x7C: Reserved                   */
    __IO uint32_t KEY;              /*!<Address offset: 0x80: LockKey Register                  */
    __I  uint32_t RESERVED6[31];    /*!<Address offset: 0x84 - 0xFC: Reserved                   */
    __IO uint32_t PMUCR;            /*!<Address offset: 0x100: PMU Control Register             */

    __I  uint32_t RESERVED7[6];     /*!<Address offset: 0x104~0x118: Reserved                   */
    __IO uint32_t SINGLE;           /*!<Address offset: 0x11C: Single coef Register             */
    __IO uint32_t DIFFER;           /*!<Address offset: 0x120: Differ coef Register             */
    __IO uint32_t SINGLE_BUFF;      /*!<Address offset: 0x124: Single buff coef Register        */
} SYSCTRL_TypeDef;


/**
  * @brief I2C Registers Structure
  */
typedef struct {
    __IO uint32_t CON;              /*!<Address offset: 0x00: I2C Control Register                              */
    __IO uint32_t TAR;              /*!<Address offset: 0x04: I2C Target Address Register                       */
    __IO uint32_t SAR;              /*!<Address offset: 0x08: I2C Slave Address Register                        */
    __I  uint32_t RESERVED0;        /*!<Address offset: 0x0C: RESERVED                                          */
    __IO uint32_t DCMD;             /*!<Address offset: 0x10: I2C Rx/Tx Data Buffer and Command Register        */
    __IO uint32_t SSHCNT;           /*!<Address offset: 0x14: Standard Speed I2C Clock SCL High Count Register  */
    __IO uint32_t SSLCNT;           /*!<Address offset: 0x18: Standard Speed I2C Clock SCL Low Count Register   */
    __IO uint32_t FSHCNT;           /*!<Address offset: 0x1C: Fast Mode (Plus) I2C Clock SCL High Count Register*/
    __IO uint32_t FSLCNT;           /*!<Address offset: 0x20: Fast Mode (Plus) I2C Clock SCL Low Count Register */
    __I  uint32_t RESERVED1[2];     /*!<Address offset: 0x24~0x28: RESERVED                                     */
    __I  uint32_t INTRST;           /*!<Address offset: 0x2C: I2C Interrupt Status Register                     */
    __IO uint32_t INTRMS;           /*!<Address offset: 0x30: I2C Interrupt Mask Register                       */
    __I  uint32_t RINTRST;          /*!<Address offset: 0x34: I2C Raw Interrupt Status Register                 */
    __IO uint32_t RXTL;             /*!<Address offset: 0x38: I2C Receive FIFO Threshold Register               */
    __IO uint32_t TXTL;             /*!<Address offset: 0x3C: I2C Transmit FIFO Threshold Register              */
    __I  uint32_t INTRCR;           /*!<Address offset: 0x40: Clear Combined and Individual Interrupt Register  */
    __I  uint32_t RXUNCR;           /*!<Address offset: 0x44: Clear RX_UNDER Interrupt Register                 */
    __I  uint32_t RXOVCR;           /*!<Address offset: 0x48: Clear RX_OVER Interrupt Register                  */
    __I  uint32_t TXOVCR;           /*!<Address offset: 0x4C: Clear TX_OVER Interrupt Register                  */
    __I  uint32_t RDREQCR;          /*!<Address offset: 0x50: Clear RD_REQ Interrupt Register                   */
    __I  uint32_t TXABCR;           /*!<Address offset: 0x54: Clear TX_ABRT Interrupt Register                  */
    __I  uint32_t RXDOCR;           /*!<Address offset: 0x58: Clear RX_DONE Interrupt Register                  */
    __I  uint32_t ACTICR;           /*!<Address offset: 0x5C: Clear ACTIVITY Interrupt Register                 */
    __I  uint32_t SPDETCR;          /*!<Address offset: 0x60: Clear STOP_DET Interrupt Register                 */
    __I  uint32_t STDETCR;          /*!<Address offset: 0x64: Clear START_DET Interrupt Register                */
    __I  uint32_t GCCR;             /*!<Address offset: 0x68: Clear GEN_CALL Interrupt Register                 */
    __IO uint32_t ENABLE;           /*!<Address offset: 0x6C: I2C Enable Register                               */
    __I  uint32_t STATUS;           /*!<Address offset: 0x70: I2C Status Register                               */
    __I  uint32_t TXFLR;            /*!<Address offset: 0x74: I2C Transmit FIFO Level Register                  */
    __I  uint32_t RXFLR;            /*!<Address offset: 0x78: I2C Receive FIFO Level Register                   */
    __IO uint32_t SDA_HOLD;         /*!<Address offset: 0x7C: I2C SDA Hold Time Length Register                 */
    __I  uint32_t TXABSR;           /*!<Address offset: 0x80: I2C Transmit Abort Source Register                */
    __IO uint32_t NACKEN;           /*!<Address offset: 0x84: Generate Slave Data NACK Register                 */
    __IO uint32_t DMACT;            /*!<Address offset: 0x88: DMA Control Register                              */
    __IO uint32_t DMATDLR;          /*!<Address offset: 0x8C: DMA Transmit Data Level Register                  */
    __IO uint32_t DMARDLR;          /*!<Address offset: 0x90: I2C Receive Data Level Register                   */
    __IO uint32_t SDA_SETUP;        /*!<Address offset: 0x94: I2C SDA Setup Register                            */
    __IO uint32_t GCACK;            /*!<Address offset: 0x98: I2C ACK General Call Register                     */
    __I  uint32_t ENST;             /*!<Address offset: 0x9C: I2C Enable Status Register                        */
    __IO uint32_t FS_SPKLEN;        /*!<Address offset: 0xA0: I2C SS and FS Spike Suppression Limit Register    */
    __I  uint32_t RESERVED2;        /*!<Address offset: 0xA4: RESERVED                                          */
    __IO uint32_t RSDETCR;          /*!<Address offset: 0xA8: Clear RESTART_DET Interrupt Register              */
    __IO uint32_t SCLLTO;           /*!<Address offset: 0xAC: I2C SCL Stuck at Low Timeout                      */
    __IO uint32_t SDALTO;           /*!<Address offset: 0xB0: I2C SDA Stuck at Low Timeout                      */
    __IO uint32_t SSTDETCR;         /*!<Address offset: 0xB4: Clear SCL Stuck at Low Detect Interrupt Register  */
    __IO uint32_t DEVICE_ID;        /*!<Address offset: 0xB8: I2C Device ID                                     */
    __IO uint32_t TSEXT;            /*!<Address offset: 0xBC: SMBUS Slave Clock Extend Timeout Register         */
    __IO uint32_t TMEXT;            /*!<Address offset: 0xC0: SMBUS Master extend clock Timeout Register        */
    __IO uint32_t IDCNT;            /*!<Address offset: 0xC4: SMBus Thigh MAX Bus-Idle count Register           */
    __I  uint32_t SMINTRST;         /*!<Address offset: 0xC8: SMBUS Interrupt Status Register                   */
    __IO uint32_t SMINTRMS;         /*!<Address offset: 0xCC: SMBUS Interrupt Mask Register                     */
    __I  uint32_t SMINTRRST;        /*!<Address offset: 0xD0: SMBUS Raw Interrupt Status Register               */
    __O  uint32_t SMINTRCR;         /*!<Address offset: 0xD4: Clear SMBUS Interrupt Register                    */
    __IO uint32_t SAROP;            /*!<Address offset: 0xD8: I2C Optional Slave Address Register               */
    __IO uint32_t UDIDLSB;          /*!<Address offset: 0xDC: SMBUS ARP UDID LSB Register                       */
} I2C_TypeDef;


/**
  * @brief CAN (Controller Area Network) Registers Structure
  */
typedef struct {
    __IO uint32_t RXBUF[4];         /*!< Address offset: 0x00~0x0c: Receive Buffer Registers                    */
    __I  uint32_t RESERVED0[14];    /*!< Address offset: 0x10~0x44: RESERVED                                    */
    __IO uint32_t TXBUF[4];         /*!< Address offset: 0x48~0x54: Transmit Buffer Registers                   */
    __I  uint32_t RESERVED1[14];    /*!< Address offset: 0x58~0x8c: RESERVED                                    */

    __IO uint8_t  CFG_STAT;         /*!< Address offset: 0x90: Configuration and Status Register                */
    __IO uint8_t  TCMD;             /*!< Address offset: 0x91: Transmit Command Register                        */
    __IO uint8_t  TCTRL;            /*!< Address offset: 0x92: Transmit Control Register                        */
    __IO uint8_t  RCTRL;            /*!< Address offset: 0x93: Receive Control Register                         */
    __IO uint8_t  RTIE;             /*!< Address offset: 0x94: Receive and Transmit Interrupt Enable Register   */
    __I  uint8_t  RTIF;             /*!< Address offset: 0x95: Receive and Transmit Interrupt Flag Register     */
    __IO uint8_t  ERRINT;           /*!< Address offset: 0x96: ERRor INTerrupt Enable and Flag Register         */
    __IO uint8_t  LIMIT;            /*!< Address offset: 0x97: Warning Limits Register                          */
    __IO uint8_t  BITTIME0;         /*!< Address offset: 0x98: Bit Timing Register 0                            */
    __IO uint8_t  BITTIME1;         /*!< Address offset: 0x99: Bit Timing Register 1                            */
    __IO uint8_t  BITTIME2;         /*!< Address offset: 0x9a: Bit Timing Register 2                            */
    __I  uint8_t  RESERVED2;        /*!< Address offset: 0x9b: RESERVED                                         */
    __IO uint8_t  S_PRESC;          /*!< Address offset: 0x9c: Slow Speed Prescaler Register                    */
    __IO uint8_t  F_PRESC;          /*!< Address offset: 0x9d: Fast Speed Prescaler Register                    */
    __IO uint8_t  TDC;              /*!< Address offset: 0x9e: Transmitter Delay Compensation Register          */
    __I  uint8_t  RESERVED3;        /*!< Address offset: 0x9f: RESERVED                                         */
    __I  uint8_t  EALCAP;           /*!< Address offset: 0xa0: Error and Arbitration Lost Capture Register      */
    __I  uint8_t  RESERVED4;        /*!< Address offset: 0xa1: RESERVED                                         */
    __I  uint8_t  RECNT;            /*!< Address offset: 0xa2: Receive Error Counter Register                   */
    __I  uint8_t  TECNT;            /*!< Address offset: 0xa3: Transmit Error Counter Register                  */
    __IO uint8_t  ACFCTRL;          /*!< Address offset: 0xa4: Acceptance Filter Control Register               */
    __I  uint8_t  RESERVED5;        /*!< Address offset: 0xa5: RESERVED                                         */
    __IO uint8_t  ACF_EN_0;         /*!< Address offset: 0xa6: Acceptance Filter Enable Register 0              */
    __IO uint8_t  ACF_EN_1;         /*!< Address offset: 0xa7: Acceptance Filter Enable Register 1              */
    __IO uint32_t ACF;              /*!< Address offset: 0xa8: Acceptance Filter Code And Mask Config Register  */
} CAN_TypeDef;


/**
  * @brief DALI Registers Structure
  */
typedef struct {
    __IO uint32_t CR;               /*!< Address offset: 0x00: DALI Control Register            */
    __IO uint32_t ISR;              /*!< Address offset: 0x04: DALI Interrupt Status Register   */
    __IO uint32_t FDR;              /*!< Address offset: 0x08: DALI Forward Data Register       */
    __IO uint32_t BDR;              /*!< Address offset: 0x0C: DALI Backward Data Register      */
    __IO uint32_t FCR;              /*!< Address offset: 0x10: DALI Filter Control Register     */
    __IO uint32_t PSCR;             /*!< Address offset: 0x14: DALI Prescaler Register          */
    __IO uint32_t TCR;              /*!< Address offset: 0x18: DALI Timing Control Register     */
} DALI_TypeDef;
/**
  * @}
  */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup TAE32F53xx_Exported_Constants TAE32F53xx Exported Constants
  * @brief    TAE32F53xx Exported Constants
  * @{
  */

/** @defgroup TAE32F53xx_Peripheral_Memory_Map TAE32F53xx Peripheral Memory Map
  * @brief    TAE32F53xx Peripheral Memory Map
  * @{
  */

/* memory region map */
#define FLASH_BASE              0x08000000UL                        /*!< FLASH base address in the alias region                 */
#define FLASH_BANK_END          0x080FFFFFUL                        /*!< FLASH Bank End address in the alias region             */
#define SRAMA_BASE              0x20000000UL                        /*!< SRAMA base address in the alias region                 */
#define SRAMB_BASE              0x20004000UL                        /*!< SRAMB base address in the alias region                 */
#define SRAMC_BASE              0x20005000UL                        /*!< SRAMB base address in the alias region                 */

/* Peripheral Bus map */
#define PERIPH_BASE             0x40000000UL                        /*!< Peripheral base address in the alias region            */
#define APB0PERIPH_BASE         (PERIPH_BASE               )        /*!< APB0 Peripheral base address in the alias region       */
#define APB1PERIPH_BASE         (PERIPH_BASE + 0x00010000UL)        /*!< APB1 Peripheral base address in the alias region       */
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x00020000UL)        /*!< AHB Peripheral base address in the alias region        */

/* Peripheral memory map */
#define I2C0_BASE               (APB0PERIPH_BASE + 0x00000000UL)    /*!< I2C0 Peripheral base address in the alias region       */
#define I2C1_BASE               (APB0PERIPH_BASE + 0x00001000UL)    /*!< I2C1 Peripheral base address in the alias region       */
#define UART0_BASE              (APB0PERIPH_BASE + 0x00004000UL)    /*!< UART0 Peripheral base address in the alias region      */
#define UART1_BASE              (APB0PERIPH_BASE + 0x00005000UL)    /*!< UART1 Peripheral base address in the alias region      */
#define TMR0_BASE               (APB0PERIPH_BASE + 0x0000C000UL)    /*!< TMR0 Peripheral base address in the alias region       */
#define TMR1_BASE               (APB0PERIPH_BASE + 0x0000C100UL)    /*!< TMR1 Peripheral base address in the alias region       */
#define TMR2_BASE               (APB0PERIPH_BASE + 0x0000C200UL)    /*!< TMR2 Peripheral base address in the alias region       */
#define TMR3_BASE               (APB0PERIPH_BASE + 0x0000C300UL)    /*!< TMR3 Peripheral base address in the alias region       */
#define TMRGRP0_BASE            (APB0PERIPH_BASE + 0x0000C400UL)    /*!< TMRGRP0 Peripheral base address in the alias region    */
#define LVD_BASE                (APB0PERIPH_BASE + 0x0000D000UL)    /*!< LVD Peripheral base address in the alias region        */
#define PMU_BASE                (APB0PERIPH_BASE + 0x0000E000UL)    /*!< PMU Peripheral base address in the alias region        */

#define DALI_BASE               (APB1PERIPH_BASE + 0x00006000UL)    /*!< DALI Peripheral base address in the alias region       */
#define IWDG_BASE               (APB1PERIPH_BASE + 0x00007000UL)    /*!< IWDG Peripheral base address in the alias region       */
#define WWDG_BASE               (APB1PERIPH_BASE + 0x00008000UL)    /*!< WWDG Peripheral base address in the alias region       */
#define FPLL0_BASE              (APB1PERIPH_BASE + 0x00009000UL)    /*!< FPLL0 Peripheral base address in the alias region      */
#define FPLL1_BASE              (APB1PERIPH_BASE + 0x0000A000UL)    /*!< FPLL1 Peripheral base address in the alias region      */
#define FPLL2_BASE              (APB1PERIPH_BASE + 0x0000B000UL)    /*!< FPLL2 Peripheral base address in the alias region      */

#define ERPU_BASE               (APB1PERIPH_BASE + 0x0000F000UL)    /*!< ERPU Peripheral base address in the alias region       */
#define IIR0_BASE               (ERPU_BASE       + 0x500UL)         /*!< IIR0 Peripheral base address in the alias region       */
#define IIR1_BASE               (ERPU_BASE       + 0x600UL)         /*!< IIR1 Peripheral base address in the alias region       */
#define IIR2_BASE               (ERPU_BASE       + 0x700UL)         /*!< IIR2 Peripheral base address in the alias region       */
#define IIR3_BASE               (ERPU_BASE       + 0x800UL)         /*!< IIR3 Peripheral base address in the alias region       */
#define IIR4_BASE               (ERPU_BASE       + 0x900UL)         /*!< IIR4 Peripheral base address in the alias region       */
#define ECU_BASE                (ERPU_BASE       + 0xF00UL)         /*!< ECU Peripheral base address in the alias region        */

#define DMA_BASE                (AHBPERIPH_BASE  + 0x00000000UL)    /*!< DMA Peripheral base address in the alias region        */
#define CAN_BASE                (AHBPERIPH_BASE  + 0x00002000UL)    /*!< CAN Peripheral base address in the alias region        */
#define SYSCTRL_BASE            (AHBPERIPH_BASE  + 0x00003000UL)    /*!< SYSCTRL Peripheral base address in the alias region    */
#define GPIOA_BASE              (AHBPERIPH_BASE  + 0x00004000UL)    /*!< GPIOA Peripheral base address in the alias region      */
#define GPIOB_BASE              (AHBPERIPH_BASE  + 0x00005000UL)    /*!< GPIOB Peripheral base address in the alias region      */
#define GPIOC_BASE              (AHBPERIPH_BASE  + 0x00006000UL)    /*!< GPIOC Peripheral base address in the alias region      */
#define GPIOD_BASE              (AHBPERIPH_BASE  + 0x00007000UL)    /*!< GPIOD Peripheral base address in the alias region      */
#define TMR4_BASE               (AHBPERIPH_BASE  + 0x00008000UL)    /*!< TMR4 Peripheral base address in the alias region       */
#define TMR5_BASE               (AHBPERIPH_BASE  + 0x00008100UL)    /*!< TMR5 Peripheral base address in the alias region       */
#define TMR6_BASE               (AHBPERIPH_BASE  + 0x00008200UL)    /*!< TMR6 Peripheral base address in the alias region       */
#define TMR7_BASE               (AHBPERIPH_BASE  + 0x00008300UL)    /*!< TMR7 Peripheral base address in the alias region       */
#define TMRGRP1_BASE            (AHBPERIPH_BASE  + 0x00008400UL)    /*!< TMRGRP1 Peripheral base address in the alias region    */
#define FLASH_R_BASE            (AHBPERIPH_BASE  + 0x00009000UL)    /*!< FLASH R Peripheral base address in the alias region    */
#define DFLASH_R_BASE           (AHBPERIPH_BASE  + 0x0000A000UL)    /*!< DFLASH R Peripheral base address in the alias region   */
#define USB_BASE                (AHBPERIPH_BASE  + 0x0000C000UL)    /*!< USB Peripheral base address in the alias region        */

#define HRPWM_BASE              (AHBPERIPH_BASE  + 0x0000D000UL)    /*!< HRPWM Peripheral base address in the alias region      */
#define HRPWM_MASTER_BASE       (HRPWM_BASE      + 0x000UL)         /*!< HRPWM MST Peripheral base address in the alias region  */
#define HRPWM_SLAVE0_BASE       (HRPWM_BASE      + 0x080UL)         /*!< HRPWM SLV0 Peripheral base address in the alias region */
#define HRPWM_SLAVE1_BASE       (HRPWM_BASE      + 0x100UL)         /*!< HRPWM SLV1 Peripheral base address in the alias region */
#define HRPWM_SLAVE2_BASE       (HRPWM_BASE      + 0x180UL)         /*!< HRPWM SLV2 Peripheral base address in the alias region */
#define HRPWM_SLAVE3_BASE       (HRPWM_BASE      + 0x200UL)         /*!< HRPWM SLV3 Peripheral base address in the alias region */
#define HRPWM_SLAVE4_BASE       (HRPWM_BASE      + 0x280UL)         /*!< HRPWM SLV4 Peripheral base address in the alias region */
#define HRPWM_SLAVE5_BASE       (HRPWM_BASE      + 0x300UL)         /*!< HRPWM SLV5 Peripheral base address in the alias region */
#define HRPWM_COMMON_BASE       (HRPWM_BASE      + 0x380UL)         /*!< HRPWM Com Peripheral base address in the alias region  */

#define ADC0_BASE               (AHBPERIPH_BASE  + 0x0000E000UL)    /*!< ADC0 Peripheral base address in the alias region       */
#define ADC1_BASE               (AHBPERIPH_BASE  + 0x0000E400UL)    /*!< ADC1 Peripheral base address in the alias region       */
#define DAC_BASE                (AHBPERIPH_BASE  + 0x0000E800UL)    /*!< DAC  Peripheral base address in the alias region       */
#define CMP_BASE                (AHBPERIPH_BASE  + 0x0000EC00UL)    /*!< CMP Peripheral base address in the alias region        */
/**
  * @}
  */


/** @defgroup TAE32F53xx_Peripheral_Declaration TAE32F53xx Peripheral Declaration
  * @brief    TAE32F53xx Peripheral Declaration
  * @{
  */
#define I2C0        ((I2C_TypeDef     *) I2C0_BASE      )       /*!< I2C0 Peripheral Declaration    */
#define I2C1        ((I2C_TypeDef     *) I2C1_BASE      )       /*!< I2C1 Peripheral Declaration    */
#define UART0       ((UART_TypeDef    *) UART0_BASE     )       /*!< UART0 Peripheral Declaration   */
#define UART1       ((UART_TypeDef    *) UART1_BASE     )       /*!< UART1 Peripheral Declaration   */
#define USB         ((USB_TypeDef     *) USB_BASE       )       /*!< USB Peripheral Declaration     */
#define CAN         ((CAN_TypeDef     *) CAN_BASE       )       /*!< CAN Peripheral Declaration     */
#define DALI        ((DALI_TypeDef    *) DALI_BASE      )       /*!< DALI Peripheral Declaration    */

#define LVD         ((LVD_TypeDef     *) LVD_BASE       )       /*!< LVD Peripheral Declaration     */
#define FPLL0       ((FPLL_TypeDef    *) FPLL0_BASE     )       /*!< FPLL0 Peripheral Declaration   */
#define FPLL1       ((FPLL_TypeDef    *) FPLL1_BASE     )       /*!< FPLL1 Peripheral Declaration   */
#define FPLL2       ((FPLL_TypeDef    *) FPLL2_BASE     )       /*!< FPLL2 Peripheral Declaration   */
#define SYSCTRL     ((SYSCTRL_TypeDef *) SYSCTRL_BASE   )       /*!< SYSCTRL Peripheral Declaration */

#define TMR0        ((TMR_TypeDef     *) TMR0_BASE      )       /*!< TMR0 Peripheral Declaration    */
#define TMR1        ((TMR_TypeDef     *) TMR1_BASE      )       /*!< TMR1 Peripheral Declaration    */
#define TMR2        ((TMR_TypeDef     *) TMR2_BASE      )       /*!< TMR2 Peripheral Declaration    */
#define TMR3        ((TMR_TypeDef     *) TMR3_BASE      )       /*!< TMR3 Peripheral Declaration    */
#define TMRGRP0     ((TMRGRP_TypeDef  *) TMRGRP0_BASE   )       /*!< TMRRPG0 Peripheral Declaration */
#define TMR4        ((TMR_TypeDef     *) TMR4_BASE      )       /*!< TMR4 Peripheral Declaration    */
#define TMR5        ((TMR_TypeDef     *) TMR5_BASE      )       /*!< TMR5 Peripheral Declaration    */
#define TMR6        ((TMR_TypeDef     *) TMR6_BASE      )       /*!< TMR6 Peripheral Declaration    */
#define TMR7        ((TMR_TypeDef     *) TMR7_BASE      )       /*!< TMR7 Peripheral Declaration    */
#define TMRGRP1     ((TMRGRP_TypeDef  *) TMRGRP1_BASE   )       /*!< TMRGRP1 Peripheral Declaration */

#define IWDG        ((IWDG_TypeDef    *) IWDG_BASE      )       /*!< IWDG Peripheral Declaration    */
#define WWDG        ((WWDG_TypeDef    *) WWDG_BASE      )       /*!< WWDG Peripheral Declaration    */

#define DMA         ((DMA_TypeDef     *) DMA_BASE       )       /*!< DMA Peripheral Declaration     */

#define GPIOA       ((GPIO_TypeDef    *) GPIOA_BASE     )       /*!< GPIOA Peripheral Declaration   */
#define GPIOB       ((GPIO_TypeDef    *) GPIOB_BASE     )       /*!< GPIOB Peripheral Declaration   */
#define GPIOC       ((GPIO_TypeDef    *) GPIOC_BASE     )       /*!< GPIOC Peripheral Declaration   */
#define GPIOD       ((GPIO_TypeDef    *) GPIOD_BASE     )       /*!< GPIOD Peripheral Declaration   */

#define FLASH       ((FLASH_TypeDef   *) FLASH_R_BASE   )       /*!< FLASH Peripheral Declaration   */
#define DFLASH      ((DFLASH_TypeDef  *) DFLASH_R_BASE  )       /*!< DFLASH Peripheral Declaration  */

#define IIR0        ((IIR_TypeDef     *) IIR0_BASE      )       /*!< IIR0 Peripheral Declaration    */
#define IIR1        ((IIR_TypeDef     *) IIR1_BASE      )       /*!< IIR1 Peripheral Declaration    */
#define IIR2        ((IIR_TypeDef     *) IIR2_BASE      )       /*!< IIR2 Peripheral Declaration    */
#define IIR3        ((IIR_TypeDef     *) IIR3_BASE      )       /*!< IIR3 Peripheral Declaration    */
#define IIR4        ((IIR_TypeDef     *) IIR4_BASE      )       /*!< IIR4 Peripheral Declaration    */

#define HRPWM       ((HRPWM_TypeDef   *) HRPWM_BASE     )       /*!< HRPWM Peripheral Declaration   */
#define ADC0        ((ADC_TypeDef     *) ADC0_BASE      )       /*!< ADC0 Peripheral Declaration    */
#define ADC1        ((ADC_TypeDef     *) ADC1_BASE      )       /*!< ADC1 Peripheral Declaration    */
#define ECU         ((ECU_TypeDef     *) ECU_BASE       )       /*!< ECU Peripheral Declaration     */
#define DAC         ((DAC_TypeDef     *) DAC_BASE       )       /*!< DAC Peripheral Declaration     */
#define CMP         ((CMP_TypeDef     *) CMP_BASE       )       /*!< CMP Peripheral Declaration     */
/**
  * @}
  */


/** @defgroup TAE32F53xx_Peripheral_Registers_Bits_Definition TAE32F53xx Peripheral Registers Bits Definition
  * @brief    TAE32F53xx Peripheral Registers Bits Definition
  * @{
  */

/******************************************************************************/
/*                                                                            */
/*                    Embedded FLASH Controller (FLASH)                       */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FLASH_CR register  *******************/
#define FLASH_CR_LOCK_Pos           (31U)
#define FLASH_CR_LOCK_Msk           (0x1UL << FLASH_CR_LOCK_Pos)        /*!< 0x80000000UL                       */
#define FLASH_CR_LOCK               FLASH_CR_LOCK_Msk                   /*!< Lock Flag                          */
#define FLASH_CR_EIE_Pos            (17U)
#define FLASH_CR_EIE_Msk            (0x1UL << FLASH_CR_EIE_Pos)         /*!< 0x00020000UL                       */
#define FLASH_CR_EIE                FLASH_CR_EIE_Msk                    /*!< Error Interrupt Enable             */
#define FLASH_CR_DIE_Pos            (16U)
#define FLASH_CR_DIE_Msk            (0x1UL << FLASH_CR_DIE_Pos)         /*!< 0x00010000UL                       */
#define FLASH_CR_DIE                FLASH_CR_DIE_Msk                    /*!< Done Interrupt Enable              */
#define FLASH_CR_LAU_Pos            (12UL)                              /*!< Launch (Bit 12)                    */
#define FLASH_CR_LAU_Msk            (0x1UL << FLASH_CR_LAU_Pos)         /*!< Launch (Bitfield-Mask: 0x01)       */
#define FLASH_CR_LAU                FLASH_CR_LAU_Msk
#define FLASH_CR_DBPE_Pos           (9U)
#define FLASH_CR_DBPE_Msk           (0x1UL << FLASH_CR_DBPE_Pos)        /*!< 0x00000200UL                       */
#define FLASH_CR_DBPE               FLASH_CR_DBPE_Msk                   /*!< D-Bus Prefetch Enable              */
#define FLASH_CR_IBPE_Pos           (8U)
#define FLASH_CR_IBPE_Msk           (0x1UL << FLASH_CR_IBPE_Pos)        /*!< 0x00000100UL                       */
#define FLASH_CR_IBPE               FLASH_CR_IBPE_Msk                   /*!< I-Bus Prefetch Enable              */
#define FLASH_CR_ES_Pos             (1U)
#define FLASH_CR_ES_Msk             (0x1UL << FLASH_CR_ES_Pos)          /*!< 0x00000002UL                       */
#define FLASH_CR_ES                 FLASH_CR_ES_Msk                     /*!< Erase Start                        */
#define FLASH_CR_PS_Pos             (0U)
#define FLASH_CR_PS_Msk             (0x1UL << FLASH_CR_PS_Pos)          /*!< 0x00000001UL                       */
#define FLASH_CR_PS                 FLASH_CR_PS_Msk                     /*!< Program Start                      */

/******************  Bit definition for FLASH_LPR register  *******************/
#define FLASH_LPR_LPKEY_Pos         (16U)
#define FLASH_LPR_LPKEY_Msk         (0xFFFFUL << FLASH_LPR_LPKEY_Pos)   /*!< 0xFFFF0000UL                       */
#define FLASH_LPR_LPKEY             FLASH_LPR_LPKEY_Msk                 /*!< Low Power Key mask                 */
#define FLASH_LPR_WKUP_Pos          (1U)
#define FLASH_LPR_WKUP_Msk          (0x1UL << FLASH_LPR_WKUP_Pos)       /*!< 0x00000002UL                       */
#define FLASH_LPR_WKUP              FLASH_LPR_WKUP_Msk                  /*!< Wakeup                             */
#define FLASH_LPR_STDBY_Pos         (0U)
#define FLASH_LPR_STDBY_Msk         (0x1UL << FLASH_LPR_STDBY_Pos)      /*!< 0x00000001UL                       */
#define FLASH_LPR_STDBY             FLASH_LPR_STDBY_Msk                 /*!< Standby                            */

/******************  Bit definition for FLASH_ISR register  *******************/
#define FLASH_ISR_DIF_Pos           (4U)
#define FLASH_ISR_DIF_Msk           (0x1UL << FLASH_ISR_DIF_Pos)        /*!< 0x00000010UL                       */
#define FLASH_ISR_DIF               FLASH_ISR_DIF_Msk                   /*!< Done Interrupt Flag                */
#define FLASH_ISR_RPEIF_Pos         (3U)
#define FLASH_ISR_RPEIF_Msk         (0x1UL << FLASH_ISR_RPEIF_Pos)      /*!< 0x00000008UL                       */
#define FLASH_ISR_RPEIF             FLASH_ISR_RPEIF_Msk                 /*!< Read Protect Error Interrupt Flag  */
#define FLASH_ISR_ECCEIF_Pos        (2U)
#define FLASH_ISR_ECCEIF_Msk        (0x1UL << FLASH_ISR_ECCEIF_Pos)     /*!< 0x00000004UL                       */
#define FLASH_ISR_ECCEIF            FLASH_ISR_ECCEIF_Msk                /*!< ECC Error Interrupt Flag           */
#define FLASH_ISR_WPEIF_Pos         (1U)
#define FLASH_ISR_WPEIF_Msk         (0x1UL << FLASH_ISR_WPEIF_Pos)      /*!< 0x00000002UL                       */
#define FLASH_ISR_WPEIF             FLASH_ISR_WPEIF_Msk                 /*!< Write Protect Error Interrupt Flag */
#define FLASH_ISR_OPTEIF_Pos        (0U)
#define FLASH_ISR_OPTEIF_Msk        (0x1UL << FLASH_ISR_OPTEIF_Pos)     /*!< 0x00000000UL                       */
#define FLASH_ISR_OPTEIF            FLASH_ISR_OPTEIF_Msk                /*!< Option Error Interrupt Flag        */

/******************  Bit definition for FLASH_SR register  ********************/
#define FLASH_SR_BSY_Pos            (0U)
#define FLASH_SR_BSY_Msk            (0x1UL << FLASH_SR_BSY_Pos)         /*!< 0x00000001UL                       */
#define FLASH_SR_BSY                FLASH_SR_BSY_Msk                    /*!< Busy status                        */

/******************  Bit definition for FLASH_DR0 register  *******************/
#define FLASH_DR0_Pos               (0U)
#define FLASH_DR0_Msk               (0xFFFFFFFFUL << FLASH_DR0_Pos)     /*!< 0xFFFFFFFFUL                       */
#define FLASH_DR0                   FLASH_DR0_Msk                       /*!< FLASH Program Data0                */

/******************  Bit definition for FLASH_DR1 register  *******************/
#define FLASH_DR1_Pos               (0U)
#define FLASH_DR1_Msk               (0xFFFFFFFFUL << FLASH_DR1_Pos)     /*!< 0xFFFFFFFFUL                       */
#define FLASH_DR1                   FLASH_DR1_Msk                       /*!< FLASH Program Data1                */

/******************  Bit definition for FLASH_DR2 register  *******************/
#define FLASH_DR2_Pos               (0U)
#define FLASH_DR2_Msk               (0xFFFFFFFFUL << FLASH_DR2_Pos)     /*!< 0xFFFFFFFFUL                       */
#define FLASH_DR2                   FLASH_DR2_Msk                       /*!< FLASH Data2                        */

/******************  Bit definition for FLASH_DR3 register  *******************/
#define FLASH_DR3_Pos               (0U)
#define FLASH_DR3_Msk               (0xFFFFFFFFUL << FLASH_DR3_Pos)     /*!< 0xFFFFFFFFUL                       */
#define FLASH_DR3                   FLASH_DR3_Msk                       /*!< FLASH Program Data3                */

/******************  Bit definition for FLASH_ADDR register  ******************/
#define FLASH_ADDR_Pos              (0U)
#define FLASH_ADDR_Msk              (0xFFFFFFFFUL << FLASH_ADDR_Pos)    /*!< 0xFFFFFFFFUL                       */
#define FLASH_ADDR                  FLASH_ADDR_Msk                      /*!< FLASH Program Address              */

/******************  Bit definition for FLASH_ECR register  *******************/
#define FLASH_ECR_EMODE_Pos         (31U)
#define FLASH_ECR_EMODE_Msk         (0x1UL << FLASH_ECR_EMODE_Pos)      /*!< 0x80000000UL                       */
#define FLASH_ECR_EMODE             FLASH_ECR_EMODE_Msk                 /*!< Erase Mode                         */

#define FLASH_ECR_ESNB_Pos          (0U)
#define FLASH_ECR_ESNB_Msk          (0x1FFUL << FLASH_ECR_ESNB_Pos)     /*!< 0x000001FFUL                       */
#define FLASH_ECR_ESNB              FLASH_ECR_ESNB_Msk                  /*!< Erase Section Number               */

/******************  Bit definition for FLASH_TR0 register  *******************/
#define FLASH_TR0_PGH_Pos           (16U)
#define FLASH_TR0_PGH_Msk           (0xFUL << FLASH_TR0_PGH_Pos)        /*!< 0x000F0000UL                       */
#define FLASH_TR0_ADS_Pos           (12U)
#define FLASH_TR0_ADS_Msk           (0xFUL << FLASH_TR0_ADS_Pos)        /*!< 0x0000F000UL                       */
#define FLASH_TR0_ADH_Pos           (8U)
#define FLASH_TR0_ADH_Msk           (0xFUL << FLASH_TR0_ADH_Pos)        /*!< 0x00000F00UL                       */
#define FLASH_TR0_OLTCY_Pos         (4U)
#define FLASH_TR0_OLTCY_Msk         (0xFUL << FLASH_TR0_OLTCY_Pos)      /*!< 0x000000F0UL                       */
#define FLASH_TR0_RC_Pos            (0U)
#define FLASH_TR0_RC_Msk            (0xFUL << FLASH_TR0_RC_Pos)         /*!< 0x0000000FUL                       */

/******************  Bit definition for FLASH_TR1 register  *******************/
#define FLASH_TR1_USU_Pos           (0U)
#define FLASH_TR1_USU_Msk           (0xFFUL << FLASH_TR1_USU_Pos)       /*!< 0x000000FFUL                       */

/******************  Bit definition for FLASH_TR2 register  *******************/
#define FLASH_TR2_CRCV_Pos          (24U)
#define FLASH_TR2_CRCV_Msk          (0xFFUL << FLASH_TR2_CRCV_Pos)      /*!< 0xFF000000UL                       */
#define FLASH_TR2_SRCV_Pos          (16U)
#define FLASH_TR2_SRCV_Msk          (0x3FUL << FLASH_TR2_SRCV_Pos)      /*!< 0x0000F000UL                       */
#define FLASH_TR2_PRCV_Pos          (12U)
#define FLASH_TR2_PRCV_Msk          (0xFUL << FLASH_TR2_PRCV_Pos)       /*!< 0x0000F000UL                       */
#define FLASH_TR2_PROG_Pos          (8U)
#define FLASH_TR2_PROG_Msk          (0xFUL << FLASH_TR2_PROG_Pos)       /*!< 0x00000F00UL                       */
#define FLASH_TR2_PGS_Pos           (4U)
#define FLASH_TR2_PGS_Msk           (0xFUL << FLASH_TR2_PGS_Pos)        /*!< 0x000000F0UL                       */
#define FLASH_TR2_NVS_Pos           (0U)
#define FLASH_TR2_NVS_Msk           (0xFUL << FLASH_TR2_NVS_Pos)        /*!< 0x0000000FUL                       */

/******************  Bit definition for FLASH_TR3 register  *******************/
#define FLASH_TR3_WKPT_Pos          (28U)
#define FLASH_TR3_WKPT_Msk          (0xFUL << FLASH_TR3_WKPT_Pos)       /*!< 0xF0000000UL                       */
#define FLASH_TR3_CERS_Pos          (12U)
#define FLASH_TR3_CERS_Msk          (0xFFFFUL << FLASH_TR3_CERS_Pos)    /*!< 0x0FFFF000UL                       */
#define FLASH_TR3_SERS_Pos          (0U)
#define FLASH_TR3_SERS_Msk          (0xFFFUL << FLASH_TR3_SERS_Pos)     /*!< 0x00000FFFUL                       */

/******************  Bit definition for FLASH_KEYR register  ******************/
#define FLASH_KEYR_KEY_Pos          (0U)
#define FLASH_KEYR_KEY_Msk          (0xFFFFFFFFUL << FLASH_KEYR_KEY_Pos)/*!< 0xFFFFFFFFUL                       */
#define FLASH_KEYR_KEY              FLASH_KEYR_KEY_Msk                  /*!< FLASH Key                          */

/******************  Bit definition for FLASH_RDPR register  ******************/
#define FLASH_RDPR_RDP_Pos          (0U)
#define FLASH_RDPR_RDP_Msk          (0xFFUL << FLASH_RDPR_RDP_Pos)      /*!< 0x000000FFUL                       */
#define FLASH_RDPR_RDP              FLASH_RDPR_RDP_Msk                  /*!< FLASH Key                          */

/******************  Bit definition for FLASH_WRPR register  ******************/
#define FLASH_WRPR_WRP_Pos          (0U)
#define FLASH_WRPR_WRP_Msk          (0xFFFFFUL << FLASH_WRPR_WRP_Pos)   /*!< 0x000000FFUL                       */
#define FLASH_WRPR_WRP              FLASH_WRPR_WRP_Msk                  /*!< FLASH Key                          */

/******************  Bit definition for FLASH_UIDx register  ******************/
#define FLASH_UID_Pos               (0U)
#define FLASH_UID_Msk               (0xFFFFFFFFUL << FLASH_UID_Pos)     /*!< 0xFFFFFFFFUL                       */


/******************************************************************************/
/*                                                                            */
/*                     Data FLASH Controller (DFLASH)                         */
/*                                                                            */
/******************************************************************************/

/**********************  Bit definition for CR register  **********************/
#define DFLASH_CR_LOCK_Pos          (31UL)                      /*!< LOCK (Bit 31)                              */
#define DFLASH_CR_LOCK_Msk          (0x80000000UL)              /*!< LOCK (Bitfield-Mask: 0x01)                 */
#define DFLASH_CR_LOCK              DFLASH_CR_LOCK_Msk
#define DFLASH_CR_EIE_Pos           (17UL)                      /*!< EIE (Bit 17)                               */
#define DFLASH_CR_EIE_Msk           (0x20000UL)                 /*!< EIE (Bitfield-Mask: 0x01)                  */
#define DFLASH_CR_EIE               DFLASH_CR_EIE_Msk
#define DFLASH_CR_DIE_Pos           (16UL)                      /*!< DIE (Bit 16)                               */
#define DFLASH_CR_DIE_Msk           (0x10000UL)                 /*!< DIE (Bitfield-Mask: 0x01)                  */
#define DFLASH_CR_DIE               DFLASH_CR_DIE_Msk
#define DFLASH_CR_DS_Pos            (4UL)                       /*!< DS (Bit 4)                                 */
#define DFLASH_CR_DS_Msk            (0x10UL)                    /*!< DS (Bitfield-Mask: 0x01)                   */
#define DFLASH_CR_DS                DFLASH_CR_DS_Msk
#define DFLASH_CR_ES_Pos            (2UL)                       /*!< ES (Bit 2)                                 */
#define DFLASH_CR_ES_Msk            (0x4UL)                     /*!< ES (Bitfield-Mask: 0x01)                   */
#define DFLASH_CR_ES                DFLASH_CR_ES_Msk
#define DFLASH_CR_RS_Pos            (1UL)                       /*!< RS (Bit 1)                                 */
#define DFLASH_CR_RS_Msk            (0x2UL)                     /*!< RS (Bitfield-Mask: 0x01)                   */
#define DFLASH_CR_RS                DFLASH_CR_RS_Msk
#define DFLASH_CR_PS_Pos            (0UL)                       /*!< PS (Bit 0)                                 */
#define DFLASH_CR_PS_Msk            (0x1UL)                     /*!< PS (Bitfield-Mask: 0x01)                   */
#define DFLASH_CR_PS                DFLASH_CR_PS_Msk

/**********************  Bit definition for LPR register  *********************/
#define DFLASH_LPR_LPKEY_Pos        (16UL)                      /*!< LPKEY (Bit 16)                             */
#define DFLASH_LPR_LPKEY_Msk        (0xffff0000UL)              /*!< LPKEY (Bitfield-Mask: 0xffff)              */
#define DFLASH_LPR_WKUP_Pos         (1UL)                       /*!< WKUP (Bit 1)                               */
#define DFLASH_LPR_WKUP_Msk         (0x2UL)                     /*!< WKUP (Bitfield-Mask: 0x01)                 */
#define DFLASH_LPR_STDBY_Pos        (0UL)                       /*!< STDBY (Bit 0)                              */
#define DFLASH_LPR_STDBY_Msk        (0x1UL)                     /*!< STDBY (Bitfield-Mask: 0x01)                */

/**********************  Bit definition for ISR register  *********************/
#define DFLASH_ISR_DIF_Pos          (1UL)                       /*!< DIF (Bit 1)                                */
#define DFLASH_ISR_DIF_Msk          (0x2UL)                     /*!< DIF (Bitfield-Mask: 0x01)                  */
#define DFLASH_ISR_DIF              DFLASH_ISR_DIF_Msk
#define DFLASH_ISR_EIF_Pos          (0UL)                       /*!< EIF (Bit 0)                                */
#define DFLASH_ISR_EIF_Msk          (0x1UL)                     /*!< EIF (Bitfield-Mask: 0x01)                  */
#define DFLASH_ISR_EIF              DFLASH_ISR_EIF_Msk

/**********************  Bit definition for SR register  **********************/
#define DFLASH_SR_BSY_Pos           (0UL)                       /*!< BSY (Bit 0)                                */
#define DFLASH_SR_BSY_Msk           (0x1UL)                     /*!< BSY (Bitfield-Mask: 0x01)                  */
#define DFLASH_SR_BSY               DFLASH_SR_BSY_Msk

/**********************  Bit definition for DR register  **********************/
#define DFLASH_DR_Pos               (0UL)                       /*!< DR (Bit 0)                                 */
#define DFLASH_DR_Msk               (0xffffffffUL)              /*!< DR (Bitfield-Mask: 0xffffffff)             */

/*********************  Bit definition for ADDR register  *********************/
#define DFLASH_ADDR_Pos             (0UL)                       /*!< ADDR (Bit 0)                               */
#define DFLASH_ADDR_Msk             (0xffffffffUL)              /*!< ADDR (Bitfield-Mask: 0xffffffff)           */

/**********************  Bit definition for ECR register  *********************/
#define DFLASH_ECR_EMODE_Pos        (31UL)                      /*!< EMODE (Bit 31)                             */
#define DFLASH_ECR_EMODE_Msk        (0x80000000UL)              /*!< EMODE (Bitfield-Mask: 0x01)                */
#define DFLASH_ECR_EMODE            DFLASH_ECR_EMODE_Msk
#define DFLASH_ECR_ESNB_Pos         (0UL)                       /*!< ESNB (Bit 0)                               */
#define DFLASH_ECR_ESNB_Msk         (0x3fUL)                    /*!< ESNB (Bitfield-Mask: 0x3f)                 */

/**********************  Bit definition for TR0 register  *********************/
#define DFLASH_TR0_PGH_Pos          (16UL)                      /*!< PGH (Bit 16)                               */
#define DFLASH_TR0_PGH_Msk          (0xf0000UL)                 /*!< PGH (Bitfield-Mask: 0x0f)                  */
#define DFLASH_TR0_ADS_Pos          (12UL)                      /*!< ADS (Bit 12)                               */
#define DFLASH_TR0_ADS_Msk          (0xf000UL)                  /*!< ADS (Bitfield-Mask: 0x0f)                  */
#define DFLASH_TR0_ADH_Pos          (8UL)                       /*!< ADH (Bit 8)                                */
#define DFLASH_TR0_ADH_Msk          (0xf00UL)                   /*!< ADH (Bitfield-Mask: 0x0f)                  */
#define DFLASH_TR0_OLTCY_Pos        (4UL)                       /*!< Operation Latency (Bit 4)                  */
#define DFLASH_TR0_OLTCY_Msk        (0xf0UL)                    /*!< Operation Latency (Bitfield-Mask: 0x0f)    */
#define DFLASH_TR0_RC_Pos           (0UL)                       /*!< RC (Bit 0)                                 */
#define DFLASH_TR0_RC_Msk           (0xfUL)                     /*!< RC (Bitfield-Mask: 0x0f)                   */

/**********************  Bit definition for TR1 register  *********************/
#define DFLASH_TR1_UNIT_Pos         (0UL)                       /*!< UNIT (Bit 0)                               */
#define DFLASH_TR1_UNIT_Msk         (0xffUL)                    /*!< UNIT (Bitfield-Mask: 0xff)                 */

/**********************  Bit definition for TR2 register  *********************/
#define DFLASH_TR2_CRCV_Pos         (24UL)                      /*!< CRCV (Bit 24)                              */
#define DFLASH_TR2_CRCV_Msk         (0xff000000UL)              /*!< CRCV (Bitfield-Mask: 0xff)                 */
#define DFLASH_TR2_SRCV_Pos         (16UL)                      /*!< SRCV (Bit 16)                              */
#define DFLASH_TR2_SRCV_Msk         (0x3f0000UL)                /*!< SRCV (Bitfield-Mask: 0x3f)                 */
#define DFLASH_TR2_PRCV_Pos         (12UL)                      /*!< PRCV (Bit 12)                              */
#define DFLASH_TR2_PRCV_Msk         (0xf000UL)                  /*!< PRCV (Bitfield-Mask: 0x0f)                 */
#define DFLASH_TR2_PROG_Pos         (8UL)                       /*!< PROG (Bit 8)                               */
#define DFLASH_TR2_PROG_Msk         (0xf00UL)                   /*!< PROG (Bitfield-Mask: 0x0f)                 */
#define DFLASH_TR2_PGS_Pos          (4UL)                       /*!< PGS (Bit 4)                                */
#define DFLASH_TR2_PGS_Msk          (0xf0UL)                    /*!< PGS (Bitfield-Mask: 0x0f)                  */
#define DFLASH_TR2_NVS_Pos          (0UL)                       /*!< NVS (Bit 0)                                */
#define DFLASH_TR2_NVS_Msk          (0xfUL)                     /*!< NVS (Bitfield-Mask: 0x0f)                  */

/**********************  Bit definition for TR3 register  *********************/
#define DFLASH_TR3_WKUP_Pos         (28UL)                      /*!< WKUP (Bit 28)                              */
#define DFLASH_TR3_WKUP_Msk         (0xf0000000UL)              /*!< WKUP (Bitfield-Mask: 0x0f)                 */
#define DFLASH_TR3_CERS_Pos         (12UL)                      /*!< CERS (Bit 12)                              */
#define DFLASH_TR3_CERS_Msk         (0xffff000UL)               /*!< CERS (Bitfield-Mask: 0xffff)               */
#define DFLASH_TR3_SERS_Pos         (0UL)                       /*!< SERS (Bit 0)                               */
#define DFLASH_TR3_SERS_Msk         (0xfffUL)                   /*!< SERS (Bitfield-Mask: 0x0fff)               */

/*********************  Bit definition for KEYR register  *********************/
#define DFLASH_KEYR_KEY_Pos         (0UL)                       /*!< KEY (Bit 0)                                */
#define DFLASH_KEYR_KEY_Msk         (0xffffffffUL)              /*!< KEY (Bitfield-Mask: 0xffffffff)            */


/******************************************************************************/
/*                                                                            */
/*                          General Purpose I/O                               */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_BSRR register *******************/
#define GPIO_BSRR_BR_POS            (16U)
#define GPIO_BSRR_BR_Msk            (0xFFFFUL  << GPIO_BSRR_BR_POS)
#define GPIO_BSRR_BR                GPIO_BSRR_BR_Msk                /*!< GPIO Bit Reset                         */
#define GPIO_BSRR_BS_POS            (0U)
#define GPIO_BSRR_BS_Msk            (0xFFFFUL  << GPIO_BSRR_BS_POS)
#define GPIO_BSRR_BS                GPIO_BSRR_BS_Msk                /*!< GPIO Bit Reset                         */

/*******************  Bit definition for GPIO_DR register  ********************/
#define GPIO_DR_DR_POS              (0U)
#define GPIO_DR_DR_Msk              (0xFFFFUL  << GPIO_DR_DR_POS)
#define GPIO_DR_DR                  GPIO_DR_DR_Msk                  /*!< GPIO Bit Input/Output Data             */

/*******************  Bit definition for GPIO_PUR register  *******************/
#define GPIO_PUR_PU_POS             (0U)
#define GPIO_PUR_PU_Msk             (0xFFFFUL  << GPIO_PUR_PU_POS)
#define GPIO_PUR_PU                 GPIO_PUR_PU_Msk                 /*!< GPIO Bit Pullup                        */

/*******************  Bit definition for GPIO_PDR register  *******************/
#define GPIO_PDR_PD_POS             (0U)
#define GPIO_PDR_PD_Msk             (0xFFFFUL  << GPIO_PDR_PD_POS)
#define GPIO_PDR_PD                 GPIO_PDR_PD_Msk                 /*!< GPIO Bit Pulldown                      */

/*******************  Bit definition for GPIO_DSR register  *******************/
#define GPIO_DSR_DS_POS             (0U)
#define GPIO_DSR_DS_Msk             (0xFFFFUL  << GPIO_DSR_DS_POS)
#define GPIO_DSR_PD                 GPIO_DSR_DS_Msk                 /*!< GPIO Bit Driver Strength               */

/******************  Bit definition for GPIO_IHYR register  *******************/
#define GPIO_IHYR_IHY_POS           (0U)
#define GPIO_IHYR_IHY_Msk           (0xFFFFUL  << GPIO_IHYR_IHY_POS)
#define GPIO_IHYR_IHY               GPIO_IHYR_IHY_Msk               /*!< GPIO Bit Input Hysteresis              */

/******************  Bit definition for GPIO_OTYPR register  ******************/
#define GPIO_OTYPR_OT_POS           (0U)
#define GPIO_OTYPR_OT_Msk           (0xFFFFUL  << GPIO_OTYPR_OT_POS)
#define GPIO_OTYPR_OT               GPIO_OTYPR_OT_Msk               /*!< GPIO Bit Output Type                   */

/*******************  Bit definition for GPIO_OSRR register  ******************/
#define GPIO_OSRR_OSR_POS           (0U)
#define GPIO_OSRR_OSR_Msk           (0xFFFFUL  << GPIO_OSRR_OSR_POS)
#define GPIO_OSRR_OSR               GPIO_OSRR_OSR_Msk               /*!< GPIO Bit Output Slew Rate              */

/*******************  Bit definition for GPIO_IER register  *******************/
#define GPIO_IER_IE_POS             (0U)
#define GPIO_IER_IE_Msk             (0x1UL  << GPIO_IER_IE_POS)
#define GPIO_IER_IE                 GPIO_IER_IE_Msk                 /*!< GPIO Interrupt Enable                  */

/*******************  Bit definition for GPIO_ITER register  ******************/
#define GPIO_ITER_ITE_POS           (0U)
#define GPIO_ITER_ITE_Msk           (0xFFFFUL  << GPIO_ITER_ITE_POS)
#define GPIO_ITER_ITE               GPIO_ITER_ITE_Msk               /*!< GPIO Bit Interrupt Trigger Enable      */

/*******************  Bit definition for GPIO_RFTSR register  *****************/
#define GPIO_RFTSR_FTS_POS          (16U)
#define GPIO_RFTSR_FTS_Msk          (0xFFFFUL  << GPIO_RFTSR_FTS_POS)
#define GPIO_RFTSR_FTS              GPIO_RFTSR_FTS_Msk              /*!< Falling Trigger Select on GPIO Pin     */
#define GPIO_RFTSR_RTS_POS          (0U)
#define GPIO_RFTSR_RTS_Msk          (0xFFFFUL  << GPIO_RFTSR_RTS_POS)
#define GPIO_RFTSR_RTS              GPIO_RFTSR_RTS_Msk              /*!< Rising Trigger Select on GPIO Pin      */

/*******************  Bit definition for GPIO_PR register  ********************/
#define GPIO_PR_PIF_POS             (0U)
#define GPIO_PR_PIF_MSK             (0xFFFFUL  << GPIO_PR_PIF_POS)
#define GPIO_PR_PIF                 GPIO_PR_PIF_MSK                 /*!< GPIO Pin Pending Interrupt Flag        */

/*******************  Bit definition for GPIO_SDER register  ******************/
#define GPIO_SDER_SYNE_POS          (16U)
#define GPIO_SDER_SYNE_MSK          (0xFFFFUL  << GPIO_SDER_SYNE_POS)
#define GPIO_SDER_SYNE              GPIO_SDER_SYNE_MSK              /*!< GPIO Sync Enable                       */
#define GPIO_SDER_DBCE_POS          (0U)
#define GPIO_SDER_DBCE_MSK          (0xFFFFUL  << GPIO_SDER_DBCE_POS)
#define GPIO_SDER_DBCE              GPIO_SDER_DBCE_MSK              /*!< GPIO Debounce Enable                   */

/******************  Bit definition for GPIO_PMUXR0 register  *****************/
#define GPIO_PMUXR_PMUX7_POS        (28U)
#define GPIO_PMUXR_PMUX7_MSK        (0x4UL  << GPIO_PMUXR_PMUX7_POS)
#define GPIO_PMUXR_PMUX7            GPIO_PMUXR_PMUX7_MSK            /*!< GPIO Pin7 Mux select                   */
#define GPIO_PMUXR_PMUX6_POS        (24U)
#define GPIO_PMUXR_PMUX6_MSK        (0x4UL  << GPIO_PMUXR_PMUX6_POS)
#define GPIO_PMUXR_PMUX6            GPIO_PMUXR_PMUX6_MSK            /*!< GPIO Pin6 Mux select                   */
#define GPIO_PMUXR_PMUX5_POS        (20U)
#define GPIO_PMUXR_PMUX5_MSK        (0x4UL  << GPIO_PMUXR_PMUX5_POS)
#define GPIO_PMUXR_PMUX5            GPIO_PMUXR_PMUX5_MSK            /*!< GPIO Pin5 Mux select                   */
#define GPIO_PMUXR_PMUX4_POS        (16U)
#define GPIO_PMUXR_PMUX4_MSK        (0x4UL  << GPIO_PMUXR_PMUX4_POS)
#define GPIO_PMUXR_PMUX4            GPIO_PMUXR_PMUX4_MSK            /*!< GPIO Pin4 Mux select                   */
#define GPIO_PMUXR_PMUX3_POS        (12U)
#define GPIO_PMUXR_PMUX3_MSK        (0x4UL  << GPIO_PMUXR_PMUX3_POS)
#define GPIO_PMUXR_PMUX3            GPIO_PMUXR_PMUX3_MSK            /*!< GPIO Pin3 Mux select                   */
#define GPIO_PMUXR_PMUX2_POS        (8U)
#define GPIO_PMUXR_PMUX2_MSK        (0x4UL  << GPIO_PMUXR_PMUX2_POS)
#define GPIO_PMUXR_PMUX2            GPIO_PMUXR_PMUX2_MSK            /*!< GPIO Pin2 Mux select                   */
#define GPIO_PMUXR_PMUX1_POS        (4U)
#define GPIO_PMUXR_PMUX1_MSK        (0x4UL  << GPIO_PMUXR_PMUX1_POS)
#define GPIO_PMUXR_PMUX1            GPIO_PMUXR_PMUX1_MSK            /*!< GPIO Pin1 Mux select                   */
#define GPIO_PMUXR_PMUX0_POS        (0U)
#define GPIO_PMUXR_PMUX0_MSK        (0x4UL  << GPIO_PMUXR_PMUX0_POS)
#define GPIO_PMUXR_PMUX0            GPIO_PMUXR_PMUX0_MSK            /*!< GPIO Pin0 Mux select                   */

/******************  Bit definition for GPIO_PMUXR1 register  *****************/
#define GPIO_PMUXR_PMUX15_POS       (28U)
#define GPIO_PMUXR_PMUX15_MSK       (0x4UL  << GPIO_PMUXR_PMUX15_POS)
#define GPIO_PMUXR_PMUX15           GPIO_PMUXR_PMUX15_MSK           /*!< GPIO Pin15 Mux select                  */
#define GPIO_PMUXR_PMUX14_POS       (24U)
#define GPIO_PMUXR_PMUX14_MSK       (0x4UL  << GPIO_PMUXR_PMUX14_POS)
#define GPIO_PMUXR_PMUX14           GPIO_PMUXR_PMUX14_MSK           /*!< GPIO Pin14 Mux select                  */
#define GPIO_PMUXR_PMUX13_POS       (20U)
#define GPIO_PMUXR_PMUX13_MSK       (0x4UL  << GPIO_PMUXR_PMUX13_POS)
#define GPIO_PMUXR_PMUX13           GPIO_PMUXR_PMUX13_MSK           /*!< GPIO Pin13 Mux select                  */
#define GPIO_PMUXR_PMUX12_POS       (16U)
#define GPIO_PMUXR_PMUX12_MSK       (0x4UL  << GPIO_PMUXR_PMUX12_POS)
#define GPIO_PMUXR_PMUX12           GPIO_PMUXR_PMUX12_MSK           /*!< GPIO Pin12 Mux select                  */
#define GPIO_PMUXR_PMUX11_POS       (12U)
#define GPIO_PMUXR_PMUX11_MSK       (0x4UL  << GPIO_PMUXR_PMUX11_POS)
#define GPIO_PMUXR_PMUX11           GPIO_PMUXR_PMUX11_MSK           /*!< GPIO Pin11 Mux select                  */
#define GPIO_PMUXR_PMUX10_POS       (8U)
#define GPIO_PMUXR_PMUX10_MSK       (0x4UL  << GPIO_PMUXR_PMUX10_POS)
#define GPIO_PMUXR_PMUX10           GPIO_PMUXR_PMUX10_MSK           /*!< GPIO Pin10 Mux select                  */
#define GPIO_PMUXR_PMUX9_POS        (4U)
#define GPIO_PMUXR_PMUX9_MSK        (0x4UL  << GPIO_PMUXR_PMUX9_POS)
#define GPIO_PMUXR_PMUX9            GPIO_PMUXR_PMUX9_MSK            /*!< GPIO Pin9 Mux select                   */
#define GPIO_PMUXR_PMUX8_POS        (0U)
#define GPIO_PMUXR_PMUX8_MSK        (0x4UL  << GPIO_PMUXR_PMUX8_POS)
#define GPIO_PMUXR_PMUX8            GPIO_PMUXR_PMUX8_MSK            /*!< GPIO Pin8 Mux select                   */


/******************************************************************************/
/*                                                                            */
/*                         Window WATCHDOG (WWDG)                             */
/*                                                                            */
/******************************************************************************/

/**********************  Bit definition for CR register  **********************/
#define WWDG_CR_EWIE_POS            (1U)
#define WWDG_CR_EWIE_MSK            (0x1UL  << WWDG_CR_EWIE_POS)
#define WWDG_CR_EWIE                WWDG_CR_EWIE_MSK
#define WWDG_CR_WEN_POS             (0U)
#define WWDG_CR_WEN_MSK             (0x1UL  << WWDG_CR_WEN_POS)
#define WWDG_CR_WEN                 WWDG_CR_WEN_MSK

/**********************  Bit definition for WVR register  *********************/
#define WWDG_WVR_WV_POS             (0U)
#define WWDG_WVR_WV_MSK             (0xFFFFUL << WWDG_WVR_WV_POS)
#define WWDG_WVR_WV                 WWDG_WVR_WV_MSK

/**********************  Bit definition for CVR register  *********************/
#define WWDG_CVR_CV_POS             (0u)
#define WWDG_CVR_CV_MSK             (0xFFFFUL << WWDG_CVR_CV_POS)
#define WWDG_CVR_CV                 WWDG_CVR_CV_MSK

/*********************  Bit definition for PSCR register  *********************/
#define WWDG_PSCR_PSC_POS           (0U)
#define WWDG_PSCR_PSC_MSK           (0xFFFFUL << WWDG_PSCR_PSC_POS)
#define WWDG_PSCR_PSC               WWDG_PSCR_PSC_MSK

/**********************  Bit definition for ISR register  *********************/
#define WWDG_ISR_EWIF_POS           (0U)
#define WWDG_ISR_EWIF_MSK           (0x1UL  << WWDG_ISR_EWIF_POS)
#define WWDG_ISR_EWIF               WWDG_ISR_EWIF_MSK


/******************************************************************************/
/*                                                                            */
/*                      Independent WATCHDOG (IWDG)                           */
/*                                                                            */
/******************************************************************************/

/**********************  Bit definition for KEYR register  ********************/
#define IWDG_KEYR_KEY_POS           (0U)
#define IWDG_KEYR_KEY_MSK           (0xFFFFUL << IWDG_KEYR_KEY_POS)
#define IWDG_KEYR_KEY               IWDG_KEYR_KEY_MSK

/**********************  Bit definition for CR register  **********************/
#define IWDG_CR_TOIE_POS            (1U)
#define IWDG_CR_TOIE_MSK            (0x1UL  <<  IWDG_CR_TOIE_POS)
#define IWDG_CR_TOIE                IWDG_CR_TOIE_MSK
#define IWDG_CR_MODE_POS            (0U)
#define IWDG_CR_MODE_MSK            (0x1UL  <<  IWDG_CR_MODE_POS)
#define IWDG_CR_MODE                IWDG_CR_MODE_MSK
#define IWDG_CR_MODE_RESET          (0x0UL  <<  IWDG_CR_MODE_POS)
#define IWDG_CR_MODE_INTERRUPT      (0x1UL  <<  IWDG_CR_MODE_POS)

/**********************  Bit definition for RLR register  *********************/
#define IWDG_RLR_RLV_POS            (0U)
#define IWDG_RLR_RLV_MSK            (0xFFFFUL << IWDG_RLR_RLV_POS)
#define IWDG_RLR_RLV                IWDG_RLR_RLV_MSK

/*********************  Bit definition for PSCR register  *********************/
#define IWDG_PSCR_PSC_POS           (0U)
#define IWDG_PSCR_PSC_MSK           (0x7UL  <<  IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC               IWDG_PSCR_PSC_MSK
#define IWDG_PSCR_PSC_0             (0x0UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_1             (0x1UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_2             (0x2UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_3             (0x3UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_4             (0x4UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_5             (0x5UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_6             (0x6UL << IWDG_PSCR_PSC_POS)
#define IWDG_PSCR_PSC_7             (0x7UL << IWDG_PSCR_PSC_POS)


/**********************  Bit definition for SR register  **********************/
#define IWDG_SR_TOIF_POS            (2U)
#define IWDG_SR_TOIF_MSK            (0x1UL  <<  IWDG_SR_TOIF_POS)
#define IWDG_SR_TOIF                IWDG_SR_TOIF_MSK
#define IWDG_SR_RLVUPD_POS          (1U)
#define IWDG_SR_RLVUPD_MSK          (0x1UL  <<  IWDG_SR_RLVUPD_POS)
#define IWDG_SR_RLVUPD              IWDG_SR_RLVUPD_MSK
#define IWDG_SR_PSCUPD_POS          (0U)
#define IWDG_SR_PSCUPD_MSK          (0x1UL  <<  IWDG_SR_PSCUPD_POS)
#define IWDG_SR_PSCUPD              IWDG_SR_PSCUPD_MSK


/******************************************************************************/
/*                                                                            */
/*                            Infinite Impulse Response                       */
/*                                                                            */
/******************************************************************************/

/**********************  Bit definition for CR0 register  *********************/
#define IIR_CR0_ORD_Pos             (4UL)                       /*!< ORD (Bit 4)                            */
#define IIR_CR0_ORD_Msk             (0x30UL)                    /*!< ORD (Bitfield-Mask: 0x03)              */
#define IIR_CR0_ORD                 IIR_CR0_ORD_Msk
#define IIR_CR0_ORD_0               (0x1UL << IIR_CR0_ORD_Pos)
#define IIR_CR0_ORD_1               (0x2UL << IIR_CR0_ORD_Pos)
#define IIR_CR0_IBRST_Pos           (1UL)                       /*!< IBRST (Bit 1)                          */
#define IIR_CR0_IBRST_Msk           (0x2UL)                     /*!< IBRST (Bitfield-Mask: 0x01)            */
#define IIR_CR0_IBRST               IIR_CR0_IBRST_Msk
#define IIR_CR0_IIREN_Pos           (0UL)                       /*!< IIREN (Bit 0)                          */
#define IIR_CR0_IIREN_Msk           (0x1UL)                     /*!< IIREN (Bitfield-Mask: 0x01)            */
#define IIR_CR0_IIREN               IIR_CR0_IIREN_Msk

/**********************  Bit definition for CR1 register  *********************/
#define IIR_CR1_ARE_Pos             (1UL)                       /*!< ARE (Bit 1)                            */
#define IIR_CR1_ARE_Msk             (0x2UL)                     /*!< ARE (Bitfield-Mask: 0x01)              */
#define IIR_CR1_AREN                IIR_CR1_ARE_Msk
#define IIR_CR1_START_Pos           (0UL)                       /*!< START (Bit 0)                          */
#define IIR_CR1_START_Msk           (0x1UL)                     /*!< START (Bitfield-Mask: 0x01)            */
#define IIR_CR1_START               IIR_CR1_START_Msk

/**********************  Bit definition for IER register  *********************/
#define IIR_IER_IE_Pos              (0UL)                       /*!< IE (Bit 0)                             */
#define IIR_IER_IE_Msk              (0x1UL)                     /*!< IE (Bitfield-Mask: 0x01)               */
#define IIR_IER_IE                  IIR_IER_IE_Msk

/**********************  Bit definition for ISR register  *********************/
#define IIR_ISR_FDIF_Pos            (0UL)                       /*!< FDIF (Bit 0)                           */
#define IIR_ISR_FDIF_Msk            (0x1UL)                     /*!< FDIF (Bitfield-Mask: 0x01)             */
#define IIR_ISR_FDIF                IIR_ISR_FDIF_Msk

/**********************  Bit definition for DOR register  *********************/
#define IIR_DOR_DATA_Pos            (0UL)                       /*!< DATA (Bit 0)                           */
#define IIR_DOR_DATA_Msk            (0xffffUL)                  /*!< DATA (Bitfield-Mask: 0xffff)           */

/**********************  Bit definition for DIAR register  ********************/
#define IIR_DIAR_DIADDR_Pos         (0UL)                       /*!< DIADDR (Bit 0)                         */
#define IIR_DIAR_DIADDR_Msk         (0xffffffffUL)              /*!< DIADDR (Bitfield-Mask: 0xffffffff)     */

/*********************  Bit definition for SCALR register  ********************/
#define IIR_SCALR_DOSCAL_Pos        (16UL)                      /*!< DOSCAL (Bit 16)                        */
#define IIR_SCALR_DOSCAL_Msk        (0x1f0000UL)                /*!< DOSCAL (Bitfield-Mask: 0x1f)           */
#define IIR_SCALR_DOSCAL            IIR_SCALR_DOSCAL_Msk
#define IIR_SCALR_FBSCAL_Pos        (8UL)                       /*!< FBSCAL (Bit 8)                         */
#define IIR_SCALR_FBSCAL_Msk        (0x1f00UL)                  /*!< FBSCAL (Bitfield-Mask: 0x1f)           */
#define IIR_SCALR_FBSCA             IIR_SCALR_FBSCAL_Msk
#define IIR_SCALR_DISCAL_Pos        (0UL)                       /*!< DISCAL (Bit 0)                         */
#define IIR_SCALR_DISCAL_Msk        (0x1fUL)                    /*!< DISCAL (Bitfield-Mask: 0x1f)           */
#define IIR_SCALR_DISCAL            IIR_SCALR_DISCAL_Msk

/********************  Bit definition for BXCOEFR register  *******************/
#define IIR_BxCOEFR_BxCOEF_Pos      (0UL)                       /*!< BXCOEF (Bit 0)                         */
#define IIR_BxCOEFR_BxCOEF_Msk      (0xffffUL)                  /*!< BXCOEF (Bitfield-Mask: 0xffff)         */

/********************  Bit definition for AXCOEFR register  *******************/
#define IIR_AxCOEFR_AxCOEF_Pos      (0UL)                       /*!< A1COEF (Bit 0)                         */
#define IIR_AxCOEFR_AxCOEF_Msk      (0xffffUL)                  /*!< A1COEF (Bitfield-Mask: 0xffff)         */

/*********************  Bit definition for DIASR register  ********************/
#define IIR_DIASR_DIADDRS_Pos       (0UL)                       /*!< DIADDRS (Bit 0)                        */
#define IIR_DIASR_DIADDRS_Msk       (0xffffffffUL)              /*!< DIADDRS (Bitfield-Mask: 0xffffffff)    */

/*********************  Bit definition for SCALSR register  *******************/
#define IIR_SCALSR_DOSCALS_Pos      (16UL)                      /*!< DOSCALS (Bit 16)                       */
#define IIR_SCALSR_DOSCALS_Msk      (0x1f0000UL)                /*!< DOSCALS (Bitfield-Mask: 0x1f)          */
#define IIR_SCALSR_DOSCALS           IIR_SCALSR_DOSCALS_Msk
#define IIR_SCALSR_FBSCALS_Pos      (8UL)                       /*!< FBSCALS (Bit 8)                        */
#define IIR_SCALSR_FBSCALS_Msk      (0x1f00UL)                  /*!< FBSCALSR (Bitfield-Mask: 0x1f)         */
#define IIR_SCALSR_FBSCALS          IIR_SCALSR_FBSCALS_Msk
#define IIR_SCALSR_DISCALS_Pos      (0UL)                       /*!< DISCALS (Bit 0)                        */
#define IIR_SCALSR_DISCALS_Msk      (0x1fUL)                    /*!< DISCALS (Bitfield-Mask: 0x1f)          */
#define IIR_SCALSR_DISCALS          IIR_SCALSR_DISCALS_Msk

/********************  Bit definition for BXCOEFSR register  ******************/
#define IIR_BxCOEFSR_BxCOEFS_Pos    (0UL)                       /*!< BxCOEFS (Bit 0)                        */
#define IIR_BxCOEFSR_BxCOEFS_Msk    (0xffffUL)                  /*!< BxCOEFS (Bitfield-Mask: 0xffff)        */

/********************  Bit definition for AXCOEFSR register  ******************/
#define IIR_AxCOEFSR_AxCOEFS_Pos    (0UL)                       /*!< AxCOEFS (Bit 0)                        */
#define IIR_AxCOEFSR_AxCOEFS_Msk    (0xffffUL)                  /*!< AxCOEFS (Bitfield-Mask: 0xffff)        */


/******************************************************************************/
/*                                                                            */
/*                                  TIMER                                     */
/*                                                                            */
/******************************************************************************/

/***********************  Bit definition for CR register  *********************/
#define TMR_CR_CKSRC_Pos            (12UL)                      /*!< CKSRC (Bit 12)                         */
#define TMR_CR_CKSRC_Msk            (0x3000UL)                  /*!< CKSRC (Bitfield-Mask: 0x03)            */
#define TMR_CR_CKSRC                TMR_CR_CKSRC_Msk
#define TMR_CR_CKSRC_0              (0x0UL << TMR_CR_CKSRC_Pos)
#define TMR_CR_CKSRC_1              (0x1UL << TMR_CR_CKSRC_Pos)
#define TMR_CR_CKSRC_2              (0x2UL << TMR_CR_CKSRC_Pos)
#define TMR_CR_CKSRC_3              (0x3UL << TMR_CR_CKSRC_Pos)
#define TMR_CR_UIE_Pos              (9UL)                       /*!< UIE (Bit 9)                            */
#define TMR_CR_UIE_Msk              (0x200UL)                   /*!< UIE (Bitfield-Mask: 0x01)              */
#define TMR_CR_UIE                  TMR_CR_UIE_Msk
#define TMR_CR_OVIE_Pos             (8UL)                       /*!< OVIE (Bit 8)                           */
#define TMR_CR_OVIE_Msk             (0x100UL)                   /*!< OVIE (Bitfield-Mask: 0x01)             */
#define TMR_CR_OVIE                 TMR_CR_OVIE_Msk
#define TMR_CR_ARPE_Pos             (4UL)                       /*!< ARPE (Bit 4)                           */
#define TMR_CR_ARPE_Msk             (0x10UL)                    /*!< ARPE (Bitfield-Mask: 0x01)             */
#define TMR_CR_ARPE                 TMR_CR_ARPE_Msk
#define TMR_CR_MS_Pos               (3UL)                       /*!< MS (Bit 3)                             */
#define TMR_CR_MS_Msk               (0x8UL)                     /*!< MS (Bitfield-Mask: 0x01)               */
#define TMR_CR_MS                   TMR_CR_MS_Msk
#define TMR_CR_URS_Pos              (2UL)                       /*!< URS (Bit 2)                            */
#define TMR_CR_URS_Msk              (0x4UL)                     /*!< URS (Bitfield-Mask: 0x01)              */
#define TMR_CR_URS                  TMR_CR_URS_Msk
#define TMR_CR_UDIS_Pos             (1UL)                       /*!< UDIS (Bit 1)                           */
#define TMR_CR_UDIS_Msk             (0x2UL)                     /*!< UDIS (Bitfield-Mask: 0x01)             */
#define TMR_CR_UDIS                 TMR_CR_UDIS_Msk
#define TMR_CR_CEN_Pos              (0UL)                       /*!< CEN (Bit 0)                            */
#define TMR_CR_CEN_Msk              (0x1UL)                     /*!< CEN (Bitfield-Mask: 0x01)              */
#define TMR_CR_CEN                  TMR_CR_CEN_Msk

/**********************  Bit definition for CCCR register  ********************/
#define TMR_CCCR_OCM_Pos            (12UL)                      /*!< OCM (Bit 12)                           */
#define TMR_CCCR_OCM_Msk            (0x7000UL)                  /*!< OCM (Bitfield-Mask: 0x07)              */
#define TMR_CCCR_OCM_0              (0x0UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_1              (0x1UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_2              (0x2UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_3              (0x3UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_4              (0x4UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_5              (0x5UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_6              (0x6UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM_7              (0x7UL << TMR_CCCR_OCM_Pos)
#define TMR_CCCR_OCM                TMR_CCCR_OCM_Msk
#define TMR_CCCR_OCIE_Pos           (10UL)                      /*!< OCIE (Bit 10)                          */
#define TMR_CCCR_OCIE_Msk           (0x400UL)                   /*!< OCIE (Bitfield-Mask: 0x01)             */
#define TMR_CCCR_OCIE               TMR_CCCR_OCIE_Msk
#define TMR_CCCR_ICOIE_Pos          (9UL)                       /*!< ICOIE (Bit 9)                          */
#define TMR_CCCR_ICOIE_Msk          (0x200UL)                   /*!< ICOIE (Bitfield-Mask: 0x01)            */
#define TMR_CCCR_ICOIE              TMR_CCCR_ICOIE_Msk
#define TMR_CCCR_ICIE_Pos           (8UL)                       /*!< ICIE (Bit 8)                           */
#define TMR_CCCR_ICIE_Msk           (0x100UL)                   /*!< ICIE (Bitfield-Mask: 0x01)             */
#define TMR_CCCR_ICIE               TMR_CCCR_ICIE_Msk
#define TMR_CCCR_ICSRC_Pos          (5UL)                       /*!< ICSRC (Bit 5)                          */
#define TMR_CCCR_ICSRC_Msk          (0xe0UL)                    /*!< ICSRC (Bitfield-Mask: 0x07)            */
#define TMR_CCCR_ICSRS_0            (0x0UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_1            (0x1UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_2            (0x2UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_3            (0x3UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_4            (0x4UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_5            (0x5UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_6            (0x6UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRS_7            (0x7UL << TMR_CCCR_ICSRC_Pos)
#define TMR_CCCR_ICSRC              TMR_CCCR_ICSRC_Msk
#define TMR_CCCR_OCPE_Pos           (4UL)                       /*!< OCPE (Bit 4)                           */
#define TMR_CCCR_OCPE_Msk           (0x10UL)                    /*!< OCPE (Bitfield-Mask: 0x01)             */
#define TMR_CCCR_OCPE               TMR_CCCR_OCPE_Msk
#define TMR_CCCR_CCS_Pos            (3UL)                       /*!< CCS (Bit 3)                            */
#define TMR_CCCR_CCS_Msk            (0x8UL)                     /*!< CCS (Bitfield-Mask: 0x01)              */
#define TMR_CCCR_CCS                TMR_CCCR_CCS_Msk
#define TMR_CCCR_CCP_Pos            (1UL)                       /*!< CCP (Bit 1)                            */
#define TMR_CCCR_CCP_Msk            (0x6UL)                     /*!< CCP (Bitfield-Mask: 0x03)              */
#define TMR_CCCR_CCP_0              (0x1UL << TMR_CCCR_CCP_Pos)
#define TMR_CCCR_CCP_1              (0x2UL << TMR_CCCR_CCP_Pos)
#define TMR_CCCR_CCP                TMR_CCCR_CCP_Msk
#define TMR_CCCR_CCE_Pos            (0UL)                       /*!< CCE (Bit 0)                            */
#define TMR_CCCR_CCE_Msk            (0x1UL)                     /*!< CCE (Bitfield-Mask: 0x01)              */
#define TMR_CCCR_CCE                TMR_CCCR_CCE_Msk

/**********************  Bit definition for EGR register  *********************/
#define TMR_EGR_CCG_Pos             (8UL)                       /*!< CCG (Bit 8)                            */
#define TMR_EGR_CCG_Msk             (0x100UL)                   /*!< CCG (Bitfield-Mask: 0x01)              */
#define TMR_EGR_CCG                 TMR_EGR_CCG_Msk
#define TMR_EGR_UG_Pos              (0UL)                       /*!< UG (Bit 0)                             */
#define TMR_EGR_UG_Msk              (0x1UL)                     /*!< UG (Bitfield-Mask: 0x01)               */
#define TMR_EGR_UG                  TMR_EGR_UG_Msk

/**********************  Bit definition for ICFR register  ********************/
#define TMR_ICFR_ICF_Pos            (0UL)                       /*!< ICF (Bit 0)                            */
#define TMR_ICFR_ICF_Msk            (0xffUL)                    /*!< ICF (Bitfield-Mask: 0xff)              */

/**********************  Bit definition for ISR register  *********************/
#define TMR_ISR_OVIF_Pos            (4UL)                       /*!< OVIF (Bit 4)                           */
#define TMR_ISR_OVIF_Msk            (0x10UL)                    /*!< OVIF (Bitfield-Mask: 0x01)             */
#define TMR_ISR_OVIF                TMR_ISR_OVIF_Msk
#define TMR_ISR_ICOIF_Pos           (3UL)                       /*!< ICOIF (Bit 3)                          */
#define TMR_ISR_ICOIF_Msk           (0x8UL)                     /*!< ICOIF (Bitfield-Mask: 0x01)            */
#define TMR_ISR_ICOIF               TMR_ISR_ICOIF_Msk
#define TMR_ISR_ICIF_Pos            (2UL)                       /*!< ICIF (Bit 2)                           */
#define TMR_ISR_ICIF_Msk            (0x4UL)                     /*!< ICIF (Bitfield-Mask: 0x01)             */
#define TMR_ISR_ICIF                TMR_ISR_ICIF_Msk
#define TMR_ISR_OCIF_Pos            (1UL)                       /*!< OCIF (Bit 1)                           */
#define TMR_ISR_OCIF_Msk            (0x2UL)                     /*!< OCIF (Bitfield-Mask: 0x01)             */
#define TMR_ISR_OCIF                TMR_ISR_OCIF_Msk
#define TMR_ISR_UIF_Pos             (0UL)                       /*!< UIF (Bit 0)                            */
#define TMR_ISR_UIF_Msk             (0x1UL)                     /*!< UIF (Bitfield-Mask: 0x01)              */
#define TMR_ISR_UIF                 TMR_ISR_UIF_Msk

/**********************  Bit definition for CSVR register  ********************/
#define TMR_CSVR_CSVR_Pos           (0UL)                       /*!< CSVR (Bit 0)                           */
#define TMR_CSVR_CSVR_Msk           (0xffffffffUL)              /*!< CSVR (Bitfield-Mask: 0xffffffff)       */
#define TMR_CSVR_CSVR               TMR_CSVR_CSVR_Msk

/**********************  Bit definition for CEVR register  ********************/
#define TMR_CEVR_CEVR_Pos           (0UL)                       /*!< CEVR (Bit 0)                           */
#define TMR_CEVR_CEVR_Msk           (0xffffffffUL)              /*!< CEVR (Bitfield-Mask: 0xffffffff)       */
#define TMR_CEVR_CEVR               TMR_CEVR_CEVR_Msk

/**********************  Bit definition for CCR register  *********************/
#define TMR_CCR_CCR_Pos             (0UL)                       /*!< CCR (Bit 0)                            */
#define TMR_CCR_CCR_Msk             (0xffffffffUL)              /*!< CCR (Bitfield-Mask: 0xffffffff)        */

/**********************  Bit definition for PSCR register  ********************/
#define TMR_PSCR_PSC_Pos            (0UL)                       /*!< PSC (Bit 0)                            */
#define TMR_PSCR_PSC_Msk            (0xffffUL)                  /*!< PSC (Bitfield-Mask: 0xffff)            */
#define TMR_PSCR_PSC                TMR_PSCR_PSC_Msk

/**********************  Bit definition for CNTR register  ********************/
#define TMR_CNTR_CNT_Pos            (0UL)                       /*!< CNT (Bit 0)                            */
#define TMR_CNTR_CNT_Msk            (0xffffffffUL)              /*!< CNT (Bitfield-Mask: 0xffffffff)        */
#define TMR_CNTR_CNT                TMR_CNTR_CNT_Msk

/**********************  Bit definition for ETER register  ********************/
#define TMR_ETER_CCTPW_Pos          (12UL)                      /*!< CCTPW (Bit 12)                         */
#define TMR_ETER_CCTPW_Msk          (0xf000UL)                  /*!< CCTPW (Bitfield-Mask: 0x0f)            */
#define TMR_ETER_CCTPW              TMR_ETER_CCTPW_Msk
#define TMR_ETER_PWMOE_Pos          (9UL)                       /*!< PWMOE (Bit 9)                          */
#define TMR_ETER_PWMOE_Msk          (0x200UL)                   /*!< PWMOE (Bitfield-Mask: 0x01)            */
#define TMR_ETER_PWMOE              TMR_ETER_PWMOE_Msk
#define TMR_ETER_CCTE_Pos           (8UL)                       /*!< CCTE (Bit 8)                           */
#define TMR_ETER_CCTE_Msk           (0x100UL)                   /*!< CCTE (Bitfield-Mask: 0x01)             */
#define TMR_ETER_CCTE               TMR_ETER_CCTE_Msk
#define TMR_ETER_UTPW_Pos           (4UL)                       /*!< UTPW (Bit 4)                           */
#define TMR_ETER_UTPW_Msk           (0xf0UL)                    /*!< UTPW (Bitfield-Mask: 0x0f)             */
#define TMR_ETER_UTPW               TMR_ETER_UTPW_Msk
#define TMR_ETER_UTE_Pos            (0UL)                       /*!< UTE (Bit 0)                            */
#define TMR_ETER_UTE_Msk            (0x1UL)                     /*!< UTE (Bitfield-Mask: 0x01)              */
#define TMR_ETER_UTE                TMR_ETER_UTE_Msk


/******************************************************************************/
/*                                                                            */
/*                        Timer Group synchronization                         */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for TMRGRP_SYNCR register  **************/
#define TMRGRP_SYNC3EN_POS          (3U)
#define TMRGRP_SYNC3EN_MSK          (0x1UL << TMRGRP_SYNC3EN_POS)
#define TMRGRP_SYNC3EN              TMRGRP_SYNC3EN_MSK
#define TMRGRP_SYNC2EN_POS          (2U)
#define TMRGRP_SYNC2EN_MSK          (0x1UL << TMRGRP_SYNC2EN_POS)
#define TMRGRP_SYNC2EN              TMRGRP_SYNC2EN_MSK
#define TMRGRP_SYNC1EN_POS          (1U)
#define TMRGRP_SYNC1EN_MSK          (0x1UL << TMRGRP_SYNC1EN_POS)
#define TMRGRP_SYNC1EN              TMRGRP_SYNC1EN_MSK
#define TMRGRP_SYNC0EN_POS          (0U)
#define TMRGRP_SYNC0EN_MSK          (0x1UL << TMRGRP_SYNC0EN_POS)
#define TMRGRP_SYNC0EN              TMRGRP_SYNC0EN_MSK
#define TMRGRP_SYNCALL_Msk          (0x7UL << TMRGRP_SYNC0EN_POS)
#define TMRGRP_SYNCALLEN            TMRGRP_SYNCALL_Msk

/******************************************************************************/
/*                                                                            */
/*                                  UART                                      */
/*                                                                            */
/******************************************************************************/

/**********************  Bit definition for RBR register  *********************/
#define UART_RBR_MSB_9thbit_Pos         (8UL)                   /*!< MSB_9thbit (Bit 8)                                 */
#define UART_RBR_MSB_9thbit_Msk         (0x100UL)               /*!< MSB_9thbit (Bitfield-Mask: 0x01)                   */
#define UART_RBR_MSB_9thbit             UART_RBR_MSB_9thbit_Msk
#define UART_RBR_LSB_8bits_Pos          (0UL)                   /*!< LSB_8bits (Bit 0)                                  */
#define UART_RBR_LSB_8bits_Msk          (0xffUL)                /*!< LSB_8bits (Bitfield-Mask: 0xff)                    */
#define UART_RBR_LSB_8bits              UART_RBR_LSB_8bits_Msk

#define UART_RBR_9bits_Msk              (0x1ffUL)

/**********************  Bit definition for THR register  *********************/
#define UART_THR_MSB_9thbit_Pos         (8UL)                   /*!< MSB_9thbit (Bit 8)                                 */
#define UART_THR_MSB_9thbit_Msk         (0x100UL)               /*!< MSB_9thbit (Bitfield-Mask: 0x01)                   */
#define UART_THR_MSB_9thbit             UART_THR_MSB_9thbit_Msk
#define UART_THR_LSB_8bits_Pos          (0UL)                   /*!< LSB_8bits (Bit 0)                                  */
#define UART_THR_LSB_8bits_Msk          (0xffUL)                /*!< LSB_8bits (Bitfield-Mask: 0xff)                    */
#define UART_THR_LSB_8bits              UART_THR_LSB_8bits_Msk

#define UART_THR_9bits_Msk              (0x1ffUL)

/**********************  Bit definition for DLL register  *********************/
#define UART_DLL_DLL_Pos                (0UL)                   /*!< DLL (Bit 0)                                        */
#define UART_DLL_DLL_Msk                (0xffUL)                /*!< DLL (Bitfield-Mask: 0xff)                          */
#define UART_DLL_DLL                    UART_DLL_DLL_Msk

/**********************  Bit definition for DLH register  *********************/
#define UART_DLH_DLH_Pos                (0UL)                   /*!< DLH (Bit 0)                                        */
#define UART_DLH_DLH_Msk                (0xffUL)                /*!< DLH (Bitfield-Mask: 0xff)                          */
#define UART_DLH_DLH                    UART_DLH_DLH_Msk

/**********************  Bit definition for IER register  *********************/
#define UART_IER_PTIME_Pos              (7UL)                   /*!< PTIME (Bit 7)                                      */
#define UART_IER_PTIME_Msk              (0x80UL)                /*!< PTIME (Bitfield-Mask: 0x01)                        */
#define UART_IER_PTIME                  UART_IER_PTIME_Msk
#define UART_IER_EDSSI_Pos              (3UL)                   /*!< EDSSI (Bit 3)                                      */
#define UART_IER_EDSSI_Msk              (0x8UL)                 /*!< EDSSI (Bitfield-Mask: 0x01)                        */
#define UART_IER_EDSSI                  UART_IER_EDSSI_Msk
#define UART_IER_ELSI_Pos               (2UL)                   /*!< ELSI (Bit 2)                                       */
#define UART_IER_ELSI_Msk               (0x4UL)                 /*!< ELSI (Bitfield-Mask: 0x01)                         */
#define UART_IER_ELSI                   UART_IER_ELSI_Msk
#define UART_IER_ETBEI_Pos              (1UL)                   /*!< ETBEI (Bit 1)                                      */
#define UART_IER_ETBEI_Msk              (0x2UL)                 /*!< ETBEI (Bitfield-Mask: 0x01)                        */
#define UART_IER_ETBEI                  UART_IER_ETBEI_Msk
#define UART_IER_ERBFI_Pos              (0UL)                   /*!< ERBFI (Bit 0)                                      */
#define UART_IER_ERBFI_Msk              (0x1UL)                 /*!< ERBFI (Bitfield-Mask: 0x01)                        */
#define UART_IER_ERBFI                  UART_IER_ERBFI_Msk

/**********************  Bit definition for IIR register  *********************/
#define UART_IIR_FIFOSE_Pos             (6UL)                   /*!< FIFOSE (Bit 6)                                     */
#define UART_IIR_FIFOSE_Msk             (0xc0UL)                /*!< FIFOSE (Bitfield-Mask: 0x03)                       */
#define UART_IIR_FIFOSE                 UART_IIR_FIFOSE_Msk
#define UART_IIR_IID_Pos                (0UL)                   /*!< IID (Bit 0)                                        */
#define UART_IIR_IID_Msk                (0xfUL)                 /*!< IID (Bitfield-Mask: 0x0f)                          */
#define UART_IIR_IID                    UART_IIR_IID_Msk

/**********************  Bit definition for FCR register  *********************/
#define UART_FCR_RT_Pos                 (6UL)                   /*!< RT (Bit 6)                                         */
#define UART_FCR_RT_Msk                 (0xc0UL)                /*!< RT (Bitfield-Mask: 0x03)                           */
#define UART_FCR_RT                     UART_FCR_RT_Msk
#define UART_RX_FIFO_TRIG_1CHAR         (0x0UL << UART_FCR_RT_Pos)
#define UART_RX_FIFO_TRIG_QUARTER       (0x1UL << UART_FCR_RT_Pos)
#define UART_RX_FIFO_TRIG_HALF          (0x2UL << UART_FCR_RT_Pos)
#define UART_RX_FIFO_TRIG_2LESS_FULL    (0x3UL << UART_FCR_RT_Pos)
#define UART_FCR_TET_Pos                (4UL)                   /*!< TET (Bit 4)                                        */
#define UART_FCR_TET_Msk                (0x30UL)                /*!< TET (Bitfield-Mask: 0x03)                          */
#define UART_FCR_TET                    UART_FCR_TET_Msk
#define UART_TX_FIFO_TRIG_EMPTY         (0x0UL << UART_FCR_TET_Pos)
#define UART_TX_FIFO_TRIG_2CHAR         (0x1UL << UART_FCR_TET_Pos)
#define UART_TX_FIFO_TRIG_QUARTER       (0x2UL << UART_FCR_TET_Pos)
#define UART_TX_FIFO_TRIG_HALF          (0x3UL << UART_FCR_TET_Pos)
#define UART_FCR_DMAM_Pos               (3UL)                   /*!< DMAM (Bit 3)                                       */
#define UART_FCR_DMAM_Msk               (0x8UL)                 /*!< DMAM (Bitfield-Mask: 0x01)                         */
#define UART_FCR_DMAM                   UART_FCR_DMAM_Msk
#define UART_FCR_XFIFOR_Pos             (2UL)                   /*!< XFIFOR (Bit 2)                                     */
#define UART_FCR_XFIFOR_Msk             (0x4UL)                 /*!< XFIFOR (Bitfield-Mask: 0x01)                       */
#define UART_FCR_XFIFOR                 UART_FCR_XFIFOR_Msk
#define UART_FCR_RFIFOR_Pos             (1UL)                   /*!< RFIFOR (Bit 1)                                     */
#define UART_FCR_RFIFOR_Msk             (0x2UL)                 /*!< RFIFOR (Bitfield-Mask: 0x01)                       */
#define UART_FCR_RFIFOR                 UART_FCR_RFIFOR_Msk
#define UART_FCR_FIFOE_Pos              (0UL)                   /*!< FIFOE (Bit 0)                                      */
#define UART_FCR_FIFOE_Msk              (0x1UL)                 /*!< FIFOE (Bitfield-Mask: 0x01)                        */
#define UART_FCR_FIFOE                  UART_FCR_FIFOE_Msk

/**********************  Bit definition for LCR register  *********************/
#define UART_LCR_DLAB_Pos               (7UL)                   /*!< DLAB (Bit 7)                                       */
#define UART_LCR_DLAB_Msk               (0x80UL)                /*!< DLAB (Bitfield-Mask: 0x01)                         */
#define UART_LCR_DLAB                   UART_LCR_DLAB_Msk
#define UART_LCR_BC_Pos                 (6UL)                   /*!< BC (Bit 6)                                         */
#define UART_LCR_BC_Msk                 (0x40UL)                /*!< BC (Bitfield-Mask: 0x01)                           */
#define UART_LCR_BC                     UART_LCR_BC_Msk
#define UART_LCR_Stick_Parity_Pos       (5UL)                   /*!< Stick_Parity (Bit 5)                               */
#define UART_LCR_Stick_Parity_Msk       (0x20UL)                /*!< Stick_Parity (Bitfield-Mask: 0x01)                 */
#define UART_LCR_Stick_Parity           UART_LCR_Stick_Parity_Msk
#define UART_LCR_EPS_Pos                (4UL)                   /*!< EPS (Bit 4)                                        */
#define UART_LCR_EPS_Msk                (0x10UL)                /*!< EPS (Bitfield-Mask: 0x01)                          */
#define UART_LCR_EPS                    UART_LCR_EPS_Msk
#define UART_LCR_PEN_Pos                (3UL)                   /*!< PEN (Bit 3)                                        */
#define UART_LCR_PEN_Msk                (0x8UL)                 /*!< PEN (Bitfield-Mask: 0x01)                          */
#define UART_LCR_PEN                    UART_LCR_PEN_Msk
#define UART_LCR_STOP_Pos               (2UL)                   /*!< STOP (Bit 2)                                       */
#define UART_LCR_STOP_Msk               (0x4UL)                 /*!< STOP (Bitfield-Mask: 0x01)                         */
#define UART_LCR_STOP                   UART_LCR_STOP_Msk
#define UART_LCR_STOP_1B                (0x0UL << UART_LCR_STOP_Pos)
#define UART_LCR_STOP_1_5B              (0x1UL << UART_LCR_STOP_Pos)
#define UART_LCR_STOP_2B                UART_LCR_STOP_1_5B
#define UART_LCR_DLS_Pos                (0UL)                   /*!< DLS (Bit 0)                                        */
#define UART_LCR_DLS_Msk                (0x3UL)                 /*!< DLS (Bitfield-Mask: 0x03)                          */
#define UART_LCR_DLS                    UART_LCR_DLS_Msk
#define UART_LCR_DLS_5B                 (0x0UL << UART_LCR_DLS_Pos)
#define UART_LCR_DLS_6B                 (0x1UL << UART_LCR_DLS_Pos)
#define UART_LCR_DLS_7B                 (0x2UL << UART_LCR_DLS_Pos)
#define UART_LCR_DLS_8B                 (0x3UL << UART_LCR_DLS_Pos)

/**********************  Bit definition for LSR register  *********************/
#define UART_LSR_ADDR_RCVD_Pos          (8UL)                   /*!< ADDR_RCVD (Bit 8)                                  */
#define UART_LSR_ADDR_RCVD_Msk          (0x100UL)               /*!< ADDR_RCVD (Bitfield-Mask: 0x01)                    */
#define UART_LSR_ADDR_RCVD              UART_LSR_ADDR_RCVD_Msk
#define UART_LSR_RFE_Pos                (7UL)                   /*!< RFR (Bit 7)                                        */
#define UART_LSR_RFE_Msk                (0x80UL)                /*!< RFR (Bitfield-Mask: 0x01)                          */
#define UART_LSR_RFE                    UART_LSR_RFE_Msk
#define UART_LSR_TEMT_Pos               (6UL)                   /*!< TEMT (Bit 6)                                       */
#define UART_LSR_TEMT_Msk               (0x40UL)                /*!< TEMT (Bitfield-Mask: 0x01)                         */
#define UART_LSR_TEMT                   UART_LSR_TEMT_Msk
#define UART_LSR_THRE_Pos               (5UL)                   /*!< THRE (Bit 5)                                       */
#define UART_LSR_THRE_Msk               (0x20UL)                /*!< THRE (Bitfield-Mask: 0x01)                         */
#define UART_LSR_THRE                   UART_LSR_THRE_Msk
#define UART_LSR_BI_Pos                 (4UL)                   /*!< BI (Bit 4)                                         */
#define UART_LSR_BI_Msk                 (0x10UL)                /*!< BI (Bitfield-Mask: 0x01)                           */
#define UART_LSR_BI                     UART_LSR_BI_Msk
#define UART_LSR_FE_Pos                 (3UL)                   /*!< FE (Bit 3)                                         */
#define UART_LSR_FE_Msk                 (0x8UL)                 /*!< FE (Bitfield-Mask: 0x01)                           */
#define UART_LSR_FE                     UART_LSR_FE_Msk
#define UART_LSR_PE_Pos                 (2UL)                   /*!< PE (Bit 2)                                         */
#define UART_LSR_PE_Msk                 (0x4UL)                 /*!< PE (Bitfield-Mask: 0x01)                           */
#define UART_LSR_PE                     UART_LSR_PE_Msk
#define UART_LSR_OE_Pos                 (1UL)                   /*!< OE (Bit 1)                                         */
#define UART_LSR_OE_Msk                 (0x2UL)                 /*!< OE (Bitfield-Mask: 0x01)                           */
#define UART_LSR_OE                     UART_LSR_OE_Msk
#define UART_LSR_DR_Pos                 (0UL)                   /*!< DR (Bit 0)                                         */
#define UART_LSR_DR_Msk                 (0x1UL)                 /*!< DR (Bitfield-Mask: 0x01)                           */
#define UART_LSR_DR                     UART_LSR_DR_Msk

#define UART_LSR_ALL_BIT_Msk            (0x1ffUL)

/**********************  Bit definition for USR register  *********************/
#define UART_USR_RFF_Pos                (4UL)                   /*!< RFF (Bit 4)                                        */
#define UART_USR_RFF_Msk                (0x10UL)                /*!< RFF (Bitfield-Mask: 0x01)                          */
#define UART_USR_RFF                    UART_USR_RFF_Msk
#define UART_USR_RFNE_Pos               (3UL)                   /*!< RFNE (Bit 3)                                       */
#define UART_USR_RFNE_Msk               (0x8UL)                 /*!< RFNE (Bitfield-Mask: 0x01)                         */
#define UART_USR_RFNE                   UART_USR_RFNE_Msk
#define UART_USR_TFE_Pos                (2UL)                   /*!< TFE (Bit 2)                                        */
#define UART_USR_TFE_Msk                (0x4UL)                 /*!< TFE (Bitfield-Mask: 0x01)                          */
#define UART_USR_TFE                    UART_USR_TFE_Msk
#define UART_USR_TFNF_Pos               (1UL)                   /*!< TFNF (Bit 1)                                       */
#define UART_USR_TFNF_Msk               (0x2UL)                 /*!< TFNF (Bitfield-Mask: 0x01)                         */
#define UART_USR_TFNF                   UART_USR_TFNF_Msk

/**********************  Bit definition for TFL register  *********************/
#define UART_TFL_TFL_Pos                (0UL)                   /*!< TFL (Bit 0)                                        */
#define UART_TFL_TFL_Msk                (0x1fUL)                /*!< TFL (Bitfield-Mask: 0x1f)                          */
#define UART_TFL_TFL                    UART_TFL_TFL_Msk

/**********************  Bit definition for RFL register  *********************/
#define UART_RFL_RFL_Pos                (0UL)                   /*!< RFL (Bit 0)                                        */
#define UART_RFL_RFL_Msk                (0x1fUL)                /*!< RFL (Bitfield-Mask: 0x1f)                          */
#define UART_RFL_RFL                    UART_RFL_RFL_Msk

/**********************  Bit definition for HTX register  *********************/
#define UART_HTX_HTX_Pos                (0UL)                   /*!< HTX (Bit 0)                                        */
#define UART_HTX_HTX_Msk                (0x1UL)                 /*!< HTX (Bitfield-Mask: 0x01)                          */
#define UART_HTX_HTX                    UART_HTX_HTX_Msk

/**********************  Bit definition for TCR register  *********************/
#define UART_TCR_XFER_MODE_Pos          (3UL)                   /*!< XFER_MODE (Bit 3)                                  */
#define UART_TCR_XFER_MODE_Msk          (0x18UL)                /*!< XFER_MODE (Bitfield-Mask: 0x03)                    */
#define UART_TCR_XFER_MODE              UART_TCR_XFER_MODE_Msk
#define UART_TCR_XFER_MODE_FDX          (0x0UL << UART_TCR_XFER_MODE_Pos)
#define UART_TCR_XFER_MODE_SOFT_HDX     (0x1UL << UART_TCR_XFER_MODE_Pos)
#define UART_TCR_XFER_MODE_HW_HDX       (0x2UL << UART_TCR_XFER_MODE_Pos)
#define UART_TCR_DE_POL_Pos             (2UL)                   /*!< DE_POL (Bit 2)                                     */
#define UART_TCR_DE_POL_Msk             (0x4UL)                 /*!< DE_POL (Bitfield-Mask: 0x01)                       */
#define UART_TCR_DE_POL                 UART_TCR_DE_POL_Msk
#define UART_TCR_RE_POL_Pos             (1UL)                   /*!< RE_POL (Bit 1)                                     */
#define UART_TCR_RE_POL_Msk             (0x2UL)                 /*!< RE_POL (Bitfield-Mask: 0x01)                       */
#define UART_TCR_RE_POL                 UART_TCR_RE_POL_Msk
#define UART_TCR_RS485_EN_Pos           (0UL)                   /*!< RS485_EN (Bit 0)                                   */
#define UART_TCR_RS485_EN_Msk           (0x1UL)                 /*!< RS485_EN (Bitfield-Mask: 0x01)                     */
#define UART_TCR_RS485_EN               UART_TCR_RS485_EN_Msk

/*********************  Bit definition for DE_EN register  ********************/
#define UART_DE_EN_DE_EN_Pos            (0UL)                   /*!< DE_EN (Bit 0)                                      */
#define UART_DE_EN_DE_EN_Msk            (0x1UL)                 /*!< DE_EN (Bitfield-Mask: 0x01)                        */
#define UART_DE_EN_DE_EN                UART_DE_EN_DE_EN_Msk

/*********************  Bit definition for RE_EN register  ********************/
#define UART_RE_EN_RE_EN_Pos            (0UL)                   /*!< RE_EN (Bit 0)                                      */
#define UART_RE_EN_RE_EN_Msk            (0x1UL)                 /*!< RE_EN (Bitfield-Mask: 0x01)                        */
#define UART_RE_EN_RE_EN                UART_RE_EN_RE_EN_Msk

/**********************  Bit definition for DET register  *********************/
#define UART_DET_DE_DEASSERT_TIME_Pos   (16UL)                  /*!< DE_DEASSERTION_TIME (Bit 16)                       */
#define UART_DET_DE_DEASSERT_TIME_Msk   (0xff0000UL)            /*!< DE_DEASSERTION_TIME (Bitfield-Mask: 0xff)          */
#define UART_DET_DE_DEASSERT_TIME       UART_DET_DE_DEASSERT_TIME_Msk
#define UART_DET_DE_ASSERT_TIME_Pos     (0UL)                   /*!< DE_ASSERTION_TIME (Bit 0)                          */
#define UART_DET_DE_ASSERT_TIME_Msk     (0xffUL)                /*!< DE_ASSERTION_TIME (Bitfield-Mask: 0xff)            */
#define UART_DET_DE_ASSERT_TIME         UART_DET_DE_ASSERT_TIME_Msk

/**********************  Bit definition for TAT register  *********************/
#define UART_TAT_RE_TO_DE_TIME_Pos      (16UL)                  /*!< RE TO DE Turn Around Time (Bit 16)                 */
#define UART_TAT_RE_TO_DE_TIME_Msk      (0xffff0000UL)          /*!< RE TO DE Turn Around Time (Bitfield-Mask: 0xffff)  */
#define UART_TAT_RE_TO_DE_TIME          UART_TAT_RE_TO_DE_TIME_Msk
#define UART_TAT_DE_TO_RE_TIME_Pos      (0UL)                   /*!< DE TO RE Turn Around Time (Bit 0)                  */
#define UART_TAT_DE_TO_RE_TIME_Msk      (0xffffUL)              /*!< DE TO RE Turn Around Time (Bitfield-Mask: 0xffff)  */
#define UART_TAT_DE_TO_RE_TIME          UART_TAT_DE_TO_RE_TIME_Msk

/**********************  Bit definition for DLF register  *********************/
#define UART_DLF_DLF_Pos                (0UL)                   /*!< DLF (Bit 0)                                        */
#define UART_DLF_DLF_Msk                (0xfUL)                 /*!< DLF (Bitfield-Mask: 0x0f)                          */
#define UART_DLF_DLF                    UART_DLF_DLF_Msk

/**********************  Bit definition for RAR register  *********************/
#define UART_RAR_RAR_Pos                (0UL)                   /*!< RAR (Bit 0)                                        */
#define UART_RAR_RAR_Msk                (0xffUL)                /*!< RAR (Bitfield-Mask: 0xff)                          */
#define UART_RAR_RAR                    UART_RAR_RAR_Msk

/**********************  Bit definition for TAR register  *********************/
#define UART_TAR_TAR_Pos                (0UL)                   /*!< TAR (Bit 0)                                        */
#define UART_TAR_TAR_Msk                (0xffUL)                /*!< TAR (Bitfield-Mask: 0xff)                          */
#define UART_TAR_TAR                    UART_TAR_TAR_Msk

/********************  Bit definition for LCR_EXT register  *******************/
#define UART_LCR_EXT_TRANSMIT_MODE_Pos  (3UL)                   /*!< TRANSMIT_MODE (Bit 3)                              */
#define UART_LCR_EXT_TRANSMIT_MODE_Msk  (0x8UL)                 /*!< TRANSMIT_MODE (Bitfield-Mask: 0x01)                */
#define UART_LCR_EXT_TRANSMIT_MODE      UART_LCR_EXT_TRANSMIT_MODE_Msk
#define UART_LCR_EXT_SEND_ADDR_Pos      (2UL)                   /*!< SEND_ADDR (Bit 2)                                  */
#define UART_LCR_EXT_SEND_ADDR_Msk      (0x4UL)                 /*!< SEND_ADDR (Bitfield-Mask: 0x01)                    */
#define UART_LCR_EXT_SEND_ADDR          UART_LCR_EXT_SEND_ADDR_Msk
#define UART_LCR_EXT_ADDR_MATCH_Pos     (1UL)                   /*!< ADDR_MATCH (Bit 1)                                 */
#define UART_LCR_EXT_ADDR_MATCH_Msk     (0x2UL)                 /*!< ADDR_MATCH (Bitfield-Mask: 0x01)                   */
#define UART_LCR_EXT_ADDR_MATCH         UART_LCR_EXT_ADDR_MATCH_Msk
#define UART_LCR_EXT_DLS_E_Pos          (0UL)                   /*!< DLS_E (Bit 0)                                      */
#define UART_LCR_EXT_DLS_E_Msk          (0x1UL)                 /*!< DLS_E (Bitfield-Mask: 0x01)                        */
#define UART_LCR_EXT_DLS_E              UART_LCR_EXT_DLS_E_Msk


/******************************************************************************/
/*                                                                            */
/*                                   DMA                                      */
/*                                                                            */
/******************************************************************************/

/*********************  Bit definition for CH_SAR register  *******************/
#define DMA_CH_SAR_SAR_Pos          (0UL)                       /*!< SAR (Bit 0)                                            */
#define DMA_CH_SAR_SAR_Msk          (0xffffffffUL)              /*!< SAR (Bitfield-Mask: 0xffffffff)                        */
#define DMA_CH_SAR_SAR              DMA_CH_SAR_SAR_Msk

/*********************  Bit definition for CH_DAR register  *******************/
#define DMA_CH_DAR_DAR_Pos          (0UL)                       /*!< DAR (Bit 0)                                            */
#define DMA_CH_DAR_DAR_Msk          (0xffffffffUL)              /*!< DAR (Bitfield-Mask: 0xffffffff)                        */
#define DMA_CH_DAR_DAR              DMA_CH_DAR_DAR_Msk

/*********************  Bit definition for CH_CR0 register  *******************/
#define DMA_CH_CR0_SMS_Pos          (25UL)                      /*!< SMS (Bit 25)                                           */
#define DMA_CH_CR0_SMS_Msk          (0x6000000UL)               /*!< SMS (Bitfield-Mask: 0x03)                              */
#define DMA_CH_CR0_SMS              DMA_CH_CR0_SMS_Msk
#define DMA_CH_CR0_SMS_AHB_MST1     (0x0UL << DMA_CH_CR0_SMS_Pos)
#define DMA_CH_CR0_SMS_AHB_MST2     (0x1UL << DMA_CH_CR0_SMS_Pos)
#define DMA_CH_CR0_DMS_Pos          (23UL)                      /*!< DMS (Bit 23)                                           */
#define DMA_CH_CR0_DMS_Msk          (0x1800000UL)               /*!< DMS (Bitfield-Mask: 0x03)                              */
#define DMA_CH_CR0_DMS              DMA_CH_CR0_DMS_Msk
#define DMA_CH_CR0_DMS_AHB_MST1     (0x0UL << DMA_CH_CR0_DMS_Pos)
#define DMA_CH_CR0_DMS_AHB_MST2     (0x1UL << DMA_CH_CR0_DMS_Pos)
#define DMA_CH_CR0_TTC_Pos          (20UL)                      /*!< TTC (Bit 20)                                           */
#define DMA_CH_CR0_TTC_Msk          (0x300000UL)                /*!< TTC (Bitfield-Mask: 0x07)                              */
#define DMA_CH_CR0_TTC              DMA_CH_CR0_TTC_Msk
#define DMA_CH_CR0_TTC_M2M          (0x0UL << DMA_CH_CR0_TTC_Pos)
#define DMA_CH_CR0_TTC_M2P          (0x1UL << DMA_CH_CR0_TTC_Pos)
#define DMA_CH_CR0_TTC_P2M          (0x2UL << DMA_CH_CR0_TTC_Pos)
#define DMA_CH_CR0_TTC_P2P          (0x3UL << DMA_CH_CR0_TTC_Pos)
#define DMA_CH_CR0_SBTL_Pos         (14UL)                      /*!< SBTL (Bit 14)                                          */
#define DMA_CH_CR0_SBTL_Msk         (0x1c000UL)                 /*!< SBTL (Bitfield-Mask: 0x07)                             */
#define DMA_CH_CR0_SBTL             DMA_CH_CR0_SBTL_Msk
#define DMA_CH_CR0_SBTL_1           (0x0UL << DMA_CH_CR0_SBTL_Pos)
#define DMA_CH_CR0_SBTL_4           (0x1UL << DMA_CH_CR0_SBTL_Pos)
#define DMA_CH_CR0_SBTL_8           (0x2UL << DMA_CH_CR0_SBTL_Pos)
#define DMA_CH_CR0_DBTL_Pos         (11UL)                      /*!< DBTL (Bit 11)                                          */
#define DMA_CH_CR0_DBTL_Msk         (0x3800UL)                  /*!< DBTL (Bitfield-Mask: 0x07)                             */
#define DMA_CH_CR0_DBTL             DMA_CH_CR0_DBTL_Msk
#define DMA_CH_CR0_DBTL_1           (0x0UL << DMA_CH_CR0_DBTL_Pos)
#define DMA_CH_CR0_DBTL_4           (0x1UL << DMA_CH_CR0_DBTL_Pos)
#define DMA_CH_CR0_DBTL_8           (0x2UL << DMA_CH_CR0_DBTL_Pos)
#define DMA_CH_CR0_SINC_Pos         (9UL)                       /*!< SINC (Bit 9)                                           */
#define DMA_CH_CR0_SINC_Msk         (0x600UL)                   /*!< SINC (Bitfield-Mask: 0x03)                             */
#define DMA_CH_CR0_SINC             DMA_CH_CR0_SINC_Msk
#define DMA_CH_CR0_SINC_INC         (0x0UL << DMA_CH_CR0_SINC_Pos)
#define DMA_CH_CR0_SINC_DEC         (0x1UL << DMA_CH_CR0_SINC_Pos)
#define DMA_CH_CR0_SINC_FIX         (0x2UL << DMA_CH_CR0_SINC_Pos)
#define DMA_CH_CR0_DINC_Pos         (7UL)                       /*!< DINC (Bit 7)                                           */
#define DMA_CH_CR0_DINC_Msk         (0x180UL)                   /*!< DINC (Bitfield-Mask: 0x03)                             */
#define DMA_CH_CR0_DINC             DMA_CH_CR0_DINC_Msk
#define DMA_CH_CR0_DINC_INC         (0x0UL << DMA_CH_CR0_DINC_Pos)
#define DMA_CH_CR0_DINC_DEC         (0x1UL << DMA_CH_CR0_DINC_Pos)
#define DMA_CH_CR0_DINC_FIX         (0x2UL << DMA_CH_CR0_DINC_Pos)
#define DMA_CH_CR0_STW_Pos          (4UL)                       /*!< STW (Bit 4)                                            */
#define DMA_CH_CR0_STW_Msk          (0x70UL)                    /*!< STW (Bitfield-Mask: 0x07)                              */
#define DMA_CH_CR0_STW              DMA_CH_CR0_STW_Msk
#define DMA_CH_CR0_STW_8b           (0x0UL << DMA_CH_CR0_STW_Pos)
#define DMA_CH_CR0_STW_16b          (0x1UL << DMA_CH_CR0_STW_Pos)
#define DMA_CH_CR0_STW_32b          (0x2UL << DMA_CH_CR0_STW_Pos)
#define DMA_CH_CR0_DTW_Pos          (1UL)                       /*!< DTW (Bit 1)                                            */
#define DMA_CH_CR0_DTW_Msk          (0xeUL)                     /*!< DTW (Bitfield-Mask: 0x07)                              */
#define DMA_CH_CR0_DTW              DMA_CH_CR0_DTW_Msk
#define DMA_CH_CR0_DTW_8b           (0x0UL << DMA_CH_CR0_DTW_Pos)
#define DMA_CH_CR0_DTW_16b          (0x1UL << DMA_CH_CR0_DTW_Pos)
#define DMA_CH_CR0_DTW_32b          (0x2UL << DMA_CH_CR0_DTW_Pos)
#define DMA_CH_CR0_CHIE_Pos         (0UL)                       /*!< CHIE (Bit 0)                                           */
#define DMA_CH_CR0_CHIE_Msk         (0x1UL)                     /*!< CHIE (Bitfield-Mask: 0x01)                             */
#define DMA_CH_CR0_CHIE             DMA_CH_CR0_CHIE_Msk

/*********************  Bit definition for CH_CR1 register  *******************/
#define DMA_CH_CR1_DONE_Pos         (12UL)                      /*!< DONE (Bit 12)                                          */
#define DMA_CH_CR1_DONE_Msk         (0x1000UL)                  /*!< DONE (Bitfield-Mask: 0x01)                             */
#define DMA_CH_CR1_DONE             DMA_CH_CR1_DONE_Msk
#define DMA_CH_CR1_BTCNT_Pos        (0UL)                       /*!< BTCNT (Bit 0)                                          */
#define DMA_CH_CR1_BTCNT_Msk        (0xfffUL)                   /*!< BTCNT (Bitfield-Mask: 0xfff)                           */
#define DMA_CH_CR1_BTCNT            DMA_CH_CR1_BTCNT_Msk

/*********************  Bit definition for CH_CR2 register  *******************/
#define DMA_CH_CR2_MBL_Pos          (20UL)                      /*!< MBL (Bit 20)                                           */
#define DMA_CH_CR2_MBL_Msk          (0x3ff00000UL)              /*!< MBL (Bitfield-Mask: 0x3ff)                             */
#define DMA_CH_CR2_MBL              DMA_CH_CR2_MBL_Msk
#define DMA_CH_CR2_SHSM_Pos         (11UL)                      /*!< SHSM (Bit 11)                                          */
#define DMA_CH_CR2_SHSM_Msk         (0x800UL)                   /*!< SHSM (Bitfield-Mask: 0x01)                             */
#define DMA_CH_CR2_SHSM             DMA_CH_CR2_SHSM_Msk
#define DMA_CH_CR2_DHSM_Pos         (10UL)                      /*!< DHSM (Bit 10)                                          */
#define DMA_CH_CR2_DHSM_Msk         (0x400UL)                   /*!< DHSM (Bitfield-Mask: 0x01)                             */
#define DMA_CH_CR2_DHSM             DMA_CH_CR2_DHSM_Msk
#define DMA_CH_CR2_FIFO_EF_Pos      (9UL)                       /*!< FIFO_EF (Bit 9)                                        */
#define DMA_CH_CR2_FIFO_EF_Msk      (0x200UL)                   /*!< FIFO_EF (Bitfield-Mask: 0x01)                          */
#define DMA_CH_CR2_SUSP_Pos         (8UL)                       /*!< SUSP (Bit 8)                                           */
#define DMA_CH_CR2_SUSP_Msk         (0x100UL)                   /*!< SUSP (Bitfield-Mask: 0x01)                             */
#define DMA_CH_CR2_SUSP             DMA_CH_CR2_SUSP_Msk
#define DMA_CH_CR2_PRI_Pos          (5UL)                       /*!< PRI (Bit 5)                                            */
#define DMA_CH_CR2_PRI_Msk          (0x20UL)                    /*!< PRI (Bitfield-Mask: 0x01)                              */
#define DMA_CH_CR2_PRI              DMA_CH_CR2_PRI_Msk

/*********************  Bit definition for CH_CR3 register  *******************/
#define DMA_CH_CR3_DHSIF_Pos        (11UL)                      /*!< DHSIF (Bit 11)                                         */
#define DMA_CH_CR3_DHSIF_Msk        (0x7800UL)                  /*!< DHSIF (Bitfield-Mask: 0x0f)                            */
#define DMA_CH_CR3_DHSIF            DMA_CH_CR3_DHSIF_Msk
#define DMA_CH_CR3_DHSIF_I2C0_TX    (0x0UL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_I2C0_RX    (0x1UL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_I2C1_TX    (0x2UL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_I2C1_RX    (0x3UL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_UART0_TX   (0x8UL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_UART0_RX   (0x9UL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_UART1_TX   (0xaUL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_DHSIF_UART1_RX   (0xbUL << DMA_CH_CR3_DHSIF_Pos)
#define DMA_CH_CR3_SHSIF_Pos        (7UL)                       /*!< SHSIF (Bit 7)                                          */
#define DMA_CH_CR3_SHSIF_Msk        (0x780UL)                   /*!< SHSIF (Bitfield-Mask: 0x0f)                            */
#define DMA_CH_CR3_SHSIF            DMA_CH_CR3_SHSIF_Msk
#define DMA_CH_CR3_SHSIF_I2C0_TX    (0x0UL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_I2C0_RX    (0x1UL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_I2C1_TX    (0x2UL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_I2C1_RX    (0x3UL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_UART0_TX   (0x8UL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_UART0_RX   (0x9UL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_UART1_TX   (0xaUL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_SHSIF_UART1_RX   (0xbUL << DMA_CH_CR3_SHSIF_Pos)
#define DMA_CH_CR3_FMD_Pos          (1UL)                       /*!< FMD (Bit 1)                                            */
#define DMA_CH_CR3_FMD_Msk          (0x2UL)                     /*!< FMD (Bitfield-Mask: 0x01)                              */
#define DMA_CH_CR3_FMD              DMA_CH_CR3_FMD_Msk
#define DMA_CH_CR3_FCMD_Pos         (0UL)                       /*!< FCMD (Bit 0)                                           */
#define DMA_CH_CR3_FCMD_Msk         (0x1UL)                     /*!< FCMD (Bitfield-Mask: 0x01)                             */
#define DMA_CH_CR3_FCMD             DMA_CH_CR3_FCMD_Msk

/**********************  Bit definition for TSR register  *********************/
#define DMA_TSR_TS_CH1_Pos          (1UL)                       /*!< DMA CH1 Transfer Status (Bit 1)                        */
#define DMA_TSR_TS_CH1_Msk          (0x2UL)                     /*!< DMA CH1 Transfer Status (Bitfield-Mask: 0x01)          */
#define DMA_TSR_TS_CH1              DMA_TSR_TS_CH1_Msk
#define DMA_TSR_TS_CH0_Pos          (0UL)                       /*!< DMA CH0 Transfer Status (Bit 0)                        */
#define DMA_TSR_TS_CH0_Msk          (0x1UL)                     /*!< DMA CH0 Transfer Status (Bitfield-Mask: 0x01)          */
#define DMA_TSR_TS_CH0              DMA_TSR_TS_CH0_Msk

/**********************  Bit definition for BTSR register  ********************/
#define DMA_BTSR_BTS_CH1_Pos        (1UL)                       /*!< DMA CH1 Block Transfer Status (Bit 1)                  */
#define DMA_BTSR_BTS_CH1_Msk        (0x2UL)                     /*!< DMA CH1 Block Transfer Status (Bitfield-Mask: 0x01)    */
#define DMA_BTSR_BTS_CH1            DMA_BTSR_BTS_CH1_Msk
#define DMA_BTSR_BTS_CH0_Pos        (0UL)                       /*!< DMA CH0 Block Transfer Status (Bit 0)                  */
#define DMA_BTSR_BTS_CH0_Msk        (0x1UL)                     /*!< DMA CH0 Block Transfer Status (Bitfield-Mask: 0x01)    */
#define DMA_BTSR_BTS_CH0            DMA_BTSR_BTS_CH0_Msk

/**********************  Bit definition for STSR register  ********************/
#define DMA_STSR_STS_CH1_Pos        (1UL)                       /*!< DMA CH1 Source Transfer Status (Bit 1)                 */
#define DMA_STSR_STS_CH1_Msk        (0x2UL)                     /*!< DMA CH1 Source Transfer Status (Bitfield-Mask: 0x01)   */
#define DMA_STSR_STS_CH1            DMA_STSR_STS_CH1_Msk
#define DMA_STSR_STS_CH0_Pos        (0UL)                       /*!< DMA CH0 Source Transfer Status (Bit 0)                 */
#define DMA_STSR_STS_CH0_Msk        (0x1UL)                     /*!< DMA CH0 Source Transfer Status (Bitfield-Mask: 0x01)   */
#define DMA_STSR_STS_CH0            DMA_STSR_STS_CH0_Msk

/**********************  Bit definition for DTSR register  ********************/
#define DMA_DTSR_DTS_CH1_Pos        (1UL)                       /*!< DMA CH1 Dst Transfer Status (Bit 1)                    */
#define DMA_DTSR_DTS_CH1_Msk        (0x2UL)                     /*!< DMA CH1 Dst Transfer Status (Bitfield-Mask: 0x01)      */
#define DMA_DTSR_DTS_CH1            DMA_DTSR_DTS_CH1_Msk
#define DMA_DTSR_DTS_CH0_Pos        (0UL)                       /*!< DMA CH0 Dst Transfer Status (Bit 0)                    */
#define DMA_DTSR_DTS_CH0_Msk        (0x1UL)                     /*!< DMA CH0 Dst Transfer Status (Bitfield-Mask: 0x01)      */
#define DMA_DTSR_DTS_CH0            DMA_DTSR_DTS_CH0_Msk

/**********************  Bit definition for TESR register  ********************/
#define DMA_TESR_TES_CH1_Pos        (1UL)                       /*!< DMA CH1 Transfer Error Status (Bit 1)                  */
#define DMA_TESR_TES_CH1_Msk        (0x2UL)                     /*!< DMA CH1 Transfer Error Status (Bitfield-Mask: 0x01)    */
#define DMA_TESR_TES_CH1            DMA_TESR_TES_CH1_Msk
#define DMA_TESR_TES_CH0_Pos        (0UL)                       /*!< DMA CH0 Transfer Error Status (Bit 0)                  */
#define DMA_TESR_TES_CH0_Msk        (0x1UL)                     /*!< DMA CH0 Transfer Error Status (Bitfield-Mask: 0x01)    */
#define DMA_TESR_TES_CH0            DMA_TESR_TES_CH0_Msk

/**********************  Bit definition for TIPR register  ********************/
#define DMA_TIPR_TIP_CH1_Pos        (1UL)                   /*!< DMA CH1 Transfer INT pending (Bit 1)                       */
#define DMA_TIPR_TIP_CH1_Msk        (0x2UL)                 /*!< DMA CH1 Transfer INT pending (Bitfield-Mask: 0x01)         */
#define DMA_TIPR_TIP_CH1            DMA_TIPR_TIP_CH1_Msk
#define DMA_TIPR_TIP_CH0_Pos        (0UL)                   /*!< DMA CH0 Transfer INT pending (Bit 0)                       */
#define DMA_TIPR_TIP_CH0_Msk        (0x1UL)                 /*!< DMA CH0 Transfer INT pending (Bitfield-Mask: 0x01)         */
#define DMA_TIPR_TIP_CH0            DMA_TIPR_TIP_CH0_Msk

/**********************  Bit definition for BTIPR register  *******************/
#define DMA_BTIPR_BTIF_CH1_Pos      (1UL)                   /*!< DMA CH1 Block Transfer INT pending (Bit 1)                 */
#define DMA_BTIPR_BTIF_CH1_Msk      (0x2UL)                 /*!< DMA CH1 Block Transfer INT pending (Bitfield-Mask: 0x01)   */
#define DMA_BTIPR_BTIF_CH1          DMA_BTIPR_BTIF_CH1_Msk
#define DMA_BTIPR_BTIF_CH0_Pos      (0UL)                   /*!< DMA CH0 Block Transfer INT pending (Bit 0)                 */
#define DMA_BTIPR_BTIF_CH0_Msk      (0x1UL)                 /*!< DMA CH0 Block Transfer INT pending (Bitfield-Mask: 0x01)   */
#define DMA_BTIPR_BTIF_CH0          DMA_BTIPR_BTIF_CH0_Msk

/**********************  Bit definition for STIPR register  *******************/
#define DMA_STIPR_STIF_CH1_Pos      (1UL)                   /*!< DMA CH1 Source Transfer INT pending (Bit 1)                */
#define DMA_STIPR_STIF_CH1_Msk      (0x2UL)                 /*!< DMA CH1 Source Transfer INT pending (Bitfield-Mask: 0x01)  */
#define DMA_STIPR_STIF_CH1          DMA_STIPR_STIF_CH1_Msk
#define DMA_STIPR_STIF_CH0_Pos      (0UL)                   /*!< DMA CH0 Source Transfer INT pending (Bit 0)                */
#define DMA_STIPR_STIF_CH0_Msk      (0x1UL)                 /*!< DMA CH0 Source Transfer INT pending (Bitfield-Mask: 0x01)  */
#define DMA_STIPR_STIF_CH0          DMA_STIPR_STIF_CH0_Msk

/**********************  Bit definition for DTIPR register  *******************/
#define DMA_DTIPR_DTIF_CH1_Pos      (1UL)                   /*!< DMA CH1 DST Transfer INT pending (Bit 1)                   */
#define DMA_DTIPR_DTIF_CH1_Msk      (0x2UL)                 /*!< DMA CH1 DST Transfer INT pending (Bitfield-Mask: 0x01)     */
#define DMA_DTIPR_DTIF_CH1          DMA_DTIPR_DTIF_CH1_Msk
#define DMA_DTIPR_DTIF_CH0_Pos      (0UL)                   /*!< DMA CH0 DST Transfer INT pending (Bit 0)                   */
#define DMA_DTIPR_DTIF_CH0_Msk      (0x1UL)                 /*!< DMA CH0 DST Transfer INT pending (Bitfield-Mask: 0x01)     */
#define DMA_DTIPR_DTIF_CH0          DMA_DTIPR_DTIF_CH0_Msk

/**********************  Bit definition for TEIPR register  *******************/
#define DMA_TEIPR_TEIF_CH1_Pos      (1UL)                   /*!< DMA CH1 Transfer Error INT pending (Bit 1)                 */
#define DMA_TEIPR_TEIF_CH1_Msk      (0x2UL)                 /*!< DMA CH1 Transfer Error INT pending (Bitfield-Mask: 0x01)   */
#define DMA_TEIPR_TEIF_CH1          DMA_TEIPR_TEIF_CH1_Msk
#define DMA_TEIPR_TEIF_CH0_Pos      (0UL)                   /*!< DMA CH0 Transfer Error INT pending (Bit 0)                 */
#define DMA_TEIPR_TEIF_CH0_Msk      (0x1UL)                 /*!< DMA CH0 Transfer Error INT pending (Bitfield-Mask: 0x01)   */
#define DMA_TEIPR_TEIF_CH0          DMA_TEIPR_TEIF_CH0_Msk

/**********************  Bit definition for TIMR register  ********************/
#define DMA_TIMR_TIWE_CH1_Pos       (9UL)           /*!< DMA CH1 Transfer INT Mask Write Enable (Bit 9)                     */
#define DMA_TIMR_TIWE_CH1_Msk       (0x200UL)       /*!< DMA CH1 Transfer INT Mask Write Enable (Bitfield-Mask: 0x01)       */
#define DMA_TIMR_TIWE_CH1           DMA_TIMR_TIWE_CH1_Msk
#define DMA_TIMR_TIWE_CH0_Pos       (8UL)           /*!< DMA CH0 Transfer INT Mask Write Enable (Bit 8)                     */
#define DMA_TIMR_TIWE_CH0_Msk       (0x100UL)       /*!< DMA CH0 Transfer INT Mask Write Enable (Bitfield-Mask: 0x01)       */
#define DMA_TIMR_TIWE_CH0           DMA_TIMR_TIWE_CH0_Msk
#define DMA_TIMR_TIE_CH1_Pos        (1UL)           /*!< DMA CH1 Transfer INT Enable (Bit 1)                                */
#define DMA_TIMR_TIE_CH1_Msk        (0x2UL)         /*!< DMA CH1 Transfer INT Enable (Bitfield-Mask: 0x01)                  */
#define DMA_TIMR_TIE_CH1            DMA_TIMR_TIE_CH1_Msk
#define DMA_TIMR_TIE_CH0_Pos        (0UL)           /*!< DMA CH0 Transfer INT Enable (Bit 0)                                */
#define DMA_TIMR_TIE_CH0_Msk        (0x1UL)         /*!< DMA CH0 Transfer INT Enable (Bitfield-Mask: 0x01)                  */
#define DMA_TIMR_TIE_CH0            DMA_TIMR_TIE_CH0_Msk

/**********************  Bit definition for BTIMR register  *******************/
#define DMA_BTIMR_BTIWE_CH1_Pos     (9UL)           /*!< DMA CH1 Block Transfer INT Mask Write Enable (Bit 9)               */
#define DMA_BTIMR_BTIWE_CH1_Msk     (0x200UL)       /*!< DMA CH1 Block Transfer INT Mask Write Enable (Bitfield-Mask:0x01)  */
#define DMA_BTIMR_BTIWE_CH1         DMA_BTIMR_BTIWE_CH1_Msk
#define DMA_BTIMR_BTIWE_CH0_Pos     (8UL)           /*!< DMA CH0 Block Transfer INT Mask Write Enable (Bit 8)               */
#define DMA_BTIMR_BTIWE_CH0_Msk     (0x100UL)       /*!< DMA CH0 Block Transfer INT Mask Write Enable (Bitfield-Mask:0x01)  */
#define DMA_BTIMR_BTIWE_CH0         DMA_BTIMR_BTIWE_CH0_Msk
#define DMA_BTIMR_BTIE_CH1_Pos      (1UL)           /*!< DMA CH1 Block Transfer INT Enable (Bit 1)                          */
#define DMA_BTIMR_BTIE_CH1_Msk      (0x2UL)         /*!< DMA CH1 Block Transfer INT Enable (Bitfield-Mask: 0x01)            */
#define DMA_BTIMR_BTIE_CH1          DMA_BTIMR_BTIE_CH1_Msk
#define DMA_BTIMR_BTIE_CH0_Pos      (0UL)           /*!< DMA CH0 Block Transfer INT Enable (Bit 0)                          */
#define DMA_BTIMR_BTIE_CH0_Msk      (0x1UL)         /*!< DMA CH0 Block Transfer INT Enable (Bitfield-Mask: 0x01)            */
#define DMA_BTIMR_BTIE_CH0          DMA_BTIMR_BTIE_CH0_Msk

/**********************  Bit definition for STIMR register  *******************/
#define DMA_STIMR_STIWE_CH1_Pos     (9UL)           /*!< DMA CH1 Source Transfer INT Mask Write Enable (Bit 9)              */
#define DMA_STIMR_STIWE_CH1_Msk     (0x200UL)       /*!< DMA CH1 Source Transfer INT Mask Write Enable (Bitfield-Mask:0x01) */
#define DMA_STIMR_STIWE_CH1         DMA_STIMR_STIWE_CH1_Msk
#define DMA_STIMR_STIWE_CH0_Pos     (8UL)           /*!< DMA CH0 Source Transfer INT Mask Write Enable (Bit 8)              */
#define DMA_STIMR_STIWE_CH0_Msk     (0x100UL)       /*!< DMA CH0 Source Transfer INT Mask Write Enable (Bitfield-Mask:0x01) */
#define DMA_STIMR_STIWE_CH0         DMA_STIMR_STIWE_CH0_Msk
#define DMA_STIMR_STIE_CH1_Pos      (1UL)           /*!< DMA CH1 Source Transfer INT Enable (Bit 1)                         */
#define DMA_STIMR_STIE_CH1_Msk      (0x2UL)         /*!< DMA CH1 Source Transfer INT Enable (Bitfield-Mask: 0x01)           */
#define DMA_STIMR_STIE_CH1          DMA_STIMR_STIE_CH1_Msk
#define DMA_STIMR_STIE_CH0_Pos      (0UL)           /*!< DMA CH0 Source Transfer INT Enable (Bit 0)                         */
#define DMA_STIMR_STIE_CH0_Msk      (0x1UL)         /*!< DMA CH0 Source Transfer INT Enable (Bitfield-Mask: 0x01)           */
#define DMA_STIMR_STIE_CH0          DMA_STIMR_STIE_CH0_Msk

/**********************  Bit definition for DTIMR register  *******************/
#define DMA_DTIMR_DTIWE_CH1_Pos     (9UL)           /*!< DMA CH1 DST Transfer INT Mask Write Enable (Bit 9)                 */
#define DMA_DTIMR_DTIWE_CH1_Msk     (0x200UL)       /*!< DMA CH1 DST Transfer INT Mask Write Enable (Bitfield-Mask:0x01)    */
#define DMA_DTIMR_DTIWE_CH1         DMA_DTIMR_DTIWE_CH1_Msk
#define DMA_DTIMR_DTIWE_CH0_Pos     (8UL)           /*!< DMA CH0 DST Transfer INT Mask Write Enable (Bit 8)                 */
#define DMA_DTIMR_DTIWE_CH0_Msk     (0x100UL)       /*!< DMA CH0 DST Transfer INT Mask Write Enable (Bitfield-Mask:0x01)    */
#define DMA_DTIMR_DTIWE_CH0         DMA_DTIMR_DTIWE_CH0_Msk
#define DMA_DTIMR_DTIE_CH1_Pos      (1UL)           /*!< DMA CH1 DST Transfer INT Enable (Bit 1)                            */
#define DMA_DTIMR_DTIE_CH1_Msk      (0x2UL)         /*!< DMA CH1 DST Transfer INT Enable (Bitfield-Mask: 0x01)              */
#define DMA_DTIMR_DTIE_CH1          DMA_DTIMR_DTIE_CH1_Msk
#define DMA_DTIMR_DTIE_CH0_Pos      (0UL)           /*!< DMA CH0 DST Transfer INT Enable (Bit 0)                            */
#define DMA_DTIMR_DTIE_CH0_Msk      (0x1UL)         /*!< DMA CH0 DST Transfer INT Enable (Bitfield-Mask: 0x01)              */
#define DMA_DTIMR_DTIE_CH0          DMA_DTIMR_DTIE_CH0_Msk

/**********************  Bit definition for TEIMR register  *******************/
#define DMA_TEIMR_TEIWE_CH1_Pos     (9UL)           /*!< DMA CH1 Transfer Error INT Mask Write Enable (Bit 9)               */
#define DMA_TEIMR_TEIWE_CH1_Msk     (0x200UL)       /*!< DMA CH1 Transfer Error INT Mask Write Enable (Bitfield-Mask: 0x01) */
#define DMA_TEIMR_TEIWE_CH1         DMA_TEIMR_TEIWE_CH1_Msk
#define DMA_TEIMR_TEIWE_CH0_Pos     (8UL)           /*!< DMA CH0 Transfer Error INT Mask Write Enable (Bit 8)               */
#define DMA_TEIMR_TEIWE_CH0_Msk     (0x100UL)       /*!< DMA CH0 Transfer Error INT Mask Write Enable (Bitfield-Mask: 0x01) */
#define DMA_TEIMR_TEIWE_CH0         DMA_TEIMR_TEIWE_CH0_Msk
#define DMA_TEIMR_TEIE_CH1_Pos      (1UL)           /*!< DMA CH1 Transfer Error INT Enable (Bit 1)                          */
#define DMA_TEIMR_TEIE_CH1_Msk      (0x2UL)         /*!< DMA CH1 Transfer Error INT Enable (Bitfield-Mask: 0x01)            */
#define DMA_TEIMR_TEIE_CH1          DMA_TEIMR_TEIE_CH1_Msk
#define DMA_TEIMR_TEIE_CH0_Pos      (0UL)           /*!< DMA CH0 Transfer Error INT Enable (Bit 0)                          */
#define DMA_TEIMR_TEIE_CH0_Msk      (0x1UL)         /*!< DMA CH0 Transfer Error INT Enable (Bitfield-Mask: 0x01)            */
#define DMA_TEIMR_TEIE_CH0          DMA_TEIMR_TEIE_CH0_Msk

/***********************  Bit definition for TCR register  ********************/
#define DMA_TCR_TC_CH1_Pos          (1UL)               /*!< DMA CH1 Transfer INT pending Clear (Bit 1)                     */
#define DMA_TCR_TC_CH1_Msk          (0x2UL)             /*!< DMA CH1 Transfer INT pending Clear (Bitfield-Mask: 0x01)       */
#define DMA_TCR_TC_CH1              DMA_TCR_TC_CH1_Msk
#define DMA_TCR_TC_CH0_Pos          (0UL)               /*!< DMA CH0 Transfer INT pending Clear (Bit 0)                     */
#define DMA_TCR_TC_CH0_Msk          (0x1UL)             /*!< DMA CH0 Transfer INT pending Clear (Bitfield-Mask: 0x01)       */
#define DMA_TCR_TC_CH0              DMA_TCR_TC_CH0_Msk

/***********************  Bit definition for BTCR register  *******************/
#define DMA_BTCR_BTC_CH1_Pos        (1UL)               /*!< DMA CH1 Block Transfer INT pending Clear (Bit 1)               */
#define DMA_BTCR_BTC_CH1_Msk        (0x2UL)             /*!< DMA CH1 Block Transfer INT pending Clear (Bitfield-Mask:0x01)  */
#define DMA_BTCR_BTC_CH1            DMA_BTCR_BTC_CH1_Msk
#define DMA_BTCR_BTC_CH0_Pos        (0UL)               /*!< DMA CH0 Block Transfer INT pending Clear (Bit 0)               */
#define DMA_BTCR_BTC_CH0_Msk        (0x1UL)             /*!< DMA CH0 Block Transfer INT pending Clear (Bitfield-Mask:0x01)  */
#define DMA_BTCR_BTC_CH0            DMA_BTCR_BTC_CH0_Msk

/***********************  Bit definition for STCR register  *******************/
#define DMA_STCR_STC_CH1_Pos        (1UL)               /*!< DMA CH1 Source Transfer INT pending Clear (Bit 1)              */
#define DMA_STCR_STC_CH1_Msk        (0x2UL)             /*!< DMA CH1 Source Transfer INT pending Clear (Bitfield-Mask:0x01) */
#define DMA_STCR_STC_CH1            DMA_STCR_STC_CH1_Msk
#define DMA_STCR_STC_CH0_Pos        (0UL)               /*!< DMA CH0 Source Transfer INT pending Clear (Bit 0)              */
#define DMA_STCR_STC_CH0_Msk        (0x1UL)             /*!< DMA CH0 Source Transfer INT pending Clear (Bitfield-Mask:0x01) */
#define DMA_STCR_STC_CH0            DMA_STCR_STC_CH0_Msk

/***********************  Bit definition for DTCR register  *******************/
#define DMA_DTCR_DTC_CH1_Pos        (1UL)               /*!< DMA CH1 DST Transfer INT pending Clear (Bit 1)                 */
#define DMA_DTCR_DTC_CH1_Msk        (0x2UL)             /*!< DMA CH1 DST Transfer INT pending Clear (Bitfield-Mask:0x01)    */
#define DMA_DTCR_DTC_CH1            DMA_DTCR_DTC_CH1_Msk
#define DMA_DTCR_DTC_CH0_Pos        (0UL)               /*!< DMA CH0 DST Transfer INT pending Clear (Bit 0)                 */
#define DMA_DTCR_DTC_CH0_Msk        (0x1UL)             /*!< DMA CH0 DST Transfer INT pending Clear (Bitfield-Mask:0x01)    */
#define DMA_DTCR_DTC_CH0            DMA_DTCR_DTC_CH0_Msk

/***********************  Bit definition for TECR register  *******************/
#define DMA_TECR_TEC_CH1_Pos        (1UL)               /*!< DMA CH1 Transfer Error INT pending Clear (Bit 1)               */
#define DMA_TECR_TEC_CH1_Msk        (0x2UL)             /*!< DMA CH1 Transfer Error INT pending Clear (Bitfield-Mask: 0x01) */
#define DMA_TECR_TEC_CH1            DMA_TECR_TEC_CH1_Msk
#define DMA_TECR_TEC_CH0_Pos        (0UL)               /*!< DMA CH0 Transfer Error INT pending Clear (Bit 0)               */
#define DMA_TECR_TEC_CH0_Msk        (0x1UL)             /*!< DMA CH0 Transfer Error INT pending Clear (Bitfield-Mask: 0x01) */
#define DMA_TECR_TEC_CH0            DMA_TECR_TEC_CH0_Msk

/***********************  Bit definition for CR0 register  ********************/
#define DMA_CR0_PEN_Pos             (0UL)               /*!< 0x0 (Bit 0)                                                    */
#define DMA_CR0_PEN_Msk             (0x1UL)             /*!< 0x0 (Bitfield-Mask: 0x01)                                      */
#define DMA_CR0_PEN                 DMA_CR0_PEN_Msk

/***********************  Bit definition for CR1 register  ********************/
#define DMA_CR1_CHWE_CH1_Pos        (9UL)               /*!< DMA CH1 Write Enable (Bit 9)                                    */
#define DMA_CR1_CHWE_CH1_Msk        (0x200UL)           /*!< DMA CH1 Write Enable (Bitfield-Mask: 0x01)                      */
#define DMA_CR1_CHWE_CH1            DMA_CR1_CHWE_CH1_Msk
#define DMA_CR1_CHWE_CH0_Pos        (8UL)               /*!< DMA CH0 Write Enable (Bit 8)                                    */
#define DMA_CR1_CHWE_CH0_Msk        (0x100UL)           /*!< DMA CH0 Write Enable (Bitfield-Mask: 0x01)                      */
#define DMA_CR1_CHWE_CH0            DMA_CR1_CHWE_CH0_Msk
#define DMA_CR1_CHEN_CH1_Pos        (1UL)               /*!< DMA CH1 Enable (Bit 1)                                          */
#define DMA_CR1_CHEN_CH1_Msk        (0x2UL)             /*!< DMA CH1 Enable (Bitfield-Mask: 0x01)                            */
#define DMA_CR1_CHEN_CH1            DMA_CR1_CHEN_CH1_Msk
#define DMA_CR1_CHEN_CH0_Pos        (0UL)               /*!< DMA CH0 Enable (Bit 0)                                          */
#define DMA_CR1_CHEN_CH0_Msk        (0x1UL)             /*!< DMA CH0 Enable (Bitfield-Mask: 0x01)                            */
#define DMA_CR1_CHEN_CH0            DMA_CR1_CHEN_CH0_Msk


/******************************************************************************/
/*                                                                            */
/*                      Analog Comparators (CMP)                              */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for CMPx_CR register  *******************/
#define CMP_CR_OPOL_Pos             (12U)                           /*!< CMP Output Polarity (Bit 12)                       */
#define CMP_CR_OPOL_Msk             (0x1UL << CMP_CR_OPOL_Pos)      /*!< CMP Output Polarity (Bitfield-Mask)                */
#define CMP_CR_OPOL                 CMP_CR_OPOL_Msk
#define CMP_CR_ODEB_Pos             (11U)                           /*!< CMP Output Debounce (Bit 11)                       */
#define CMP_CR_ODEB_Msk             (0x1UL << CMP_CR_ODEB_Pos)      /*!< CMP Output Debounce (Bitfield-Mask)                */
#define CMP_CR_ODEB                 CMP_CR_ODEB_Msk
#define CMP_CR_BLANKING_Pos         (8U)                            /*!< CMP Blanking Source (Bit 8 - 10)                   */
#define CMP_CR_BLANKING_Msk         (0x7UL << CMP_CR_BLANKING_Pos)  /*!< CMP Blanking Source (Bitfield-Mask)                */
#define CMP_CR_BLANKING_0           (0x1UL << CMP_CR_BLANKING_Pos)
#define CMP_CR_BLANKING_1           (0x2UL << CMP_CR_BLANKING_Pos)
#define CMP_CR_BLANKING_2           (0x4UL << CMP_CR_BLANKING_Pos)
#define CMP_CR_INM_Pos              (6U)                            /*!< CMP Input Minus Select (Bit 6 - 7)                 */
#define CMP_CR_INM_Msk              (0x3UL << CMP_CR_INM_Pos)       /*!< CMP Input Minus Select (Bitfield-Mask)             */
#define CMP_CR_INM_0                (0x1UL << CMP_CR_INM_Pos)
#define CMP_CR_INM_1                (0x2UL << CMP_CR_INM_Pos)
#define CMP_CR_HYST_Pos             (4U)                            /*!< CMP Hysteresis Select (Bit 4 - 5)                  */
#define CMP_CR_HYST_Msk             (0x3UL << CMP_CR_HYST_Pos)      /*!< CMP Hysteresis Select (Bitfield-Mask)              */
#define CMP_CR_HYST_0               (0x1UL << CMP_CR_HYST_Pos)
#define CMP_CR_HYST_1               (0x2UL << CMP_CR_HYST_Pos)
#define CMP_CR_FALIE_Pos            (3U)                            /*!< CMP Falling Interrupt Enable (Bit 3)               */
#define CMP_CR_FALIE_Msk            (0x1UL << CMP_CR_FALIE_Pos)     /*!< CMP Falling Interrupt Enable (Bitfield-Mask)       */
#define CMP_CR_FALIE                CMP_CR_FALIE_Msk
#define CMP_CR_RISIE_Pos            (2U)                            /*!< CMP Rising Interrupt Enable (Bit 2)                */
#define CMP_CR_RISIE_Msk            (0x1UL << CMP_CR_RISIE_Pos)     /*!< CMP Rising Interrupt Enable (Bitfield-Mask)        */
#define CMP_CR_RISIE                CMP_CR_RISIE_Msk
#define CMP_CR_PEN_Pos              (0U)                            /*!< CMP Peripheral Enable (Bit 0)                      */
#define CMP_CR_PEN_Msk              (0x1UL << CMP_CR_PEN_Pos)       /*!< CMP Peripheral Enable (Bitfield-Mask)              */
#define CMP_CR_PEN                  CMP_CR_PEN_Msk

/********************  Bit definition for CMP_SR register  ********************/
#define CMP_SR_OVAL_3_Pos           (11U)                           /*!< CMP Channel3 Output Status (Bit 11)                */
#define CMP_SR_OVAL_3_Msk           (0x1UL << CMP_SR_OVAL_3_Pos)    /*!< CMP Channel3 Output Status (Bitfield-Mask)         */
#define CMP_SR_OVAL_3               CMP_SR_OVAL_3_Msk
#define CMP_SR_OVAL_2_Pos           (10U)                           /*!< CMP Channel2 Output Status (Bit 10)                */
#define CMP_SR_OVAL_2_Msk           (0x1UL << CMP_SR_OVAL_2_Pos)    /*!< CMP Channel2 Output Status (Bitfield-Mask)         */
#define CMP_SR_OVAL_2               CMP_SR_OVAL_2_Msk
#define CMP_SR_OVAL_1_Pos           (9U)                            /*!< CMP Channel1 Output Status (Bit 9)                 */
#define CMP_SR_OVAL_1_Msk           (0x1UL << CMP_SR_OVAL_1_Pos)    /*!< CMP Channel1 Output Status (Bitfield-Mask)         */
#define CMP_SR_OVAL_1               CMP_SR_OVAL_1_Msk
#define CMP_SR_OVAL_0_Pos           (8U)                            /*!< CMP Channel0 Output Status (Bit 8)                 */
#define CMP_SR_OVAL_0_Msk           (0x1UL << CMP_SR_OVAL_0_Pos)    /*!< CMP Channel0 Output Status (Bitfield-Mask)         */
#define CMP_SR_OVAL_0               CMP_SR_OVAL_0_Msk
#define CMP_SR_FALIF_3_Pos          (7U)                            /*!< CMP Channel3 Failling Pending Flag (Bit 7)         */
#define CMP_SR_FALIF_3_Msk          (0x1UL << CMP_SR_FALIF_3_Pos)   /*!< CMP Channel3 Failling Pending Flag (Bitfield-Mask) */
#define CMP_SR_FALIF_3              CMP_SR_FALIF_3_Msk
#define CMP_SR_FALIF_2_Pos          (6U)                            /*!< CMP Channel2 Failling Pending Flag (Bit 6)         */
#define CMP_SR_FALIF_2_Msk          (0x1UL << CMP_SR_FALIF_2_Pos)   /*!< CMP Channel2 Failling Pending Flag (Bitfield-Mask) */
#define CMP_SR_FALIF_2              CMP_SR_FALIF_2_Msk
#define CMP_SR_FALIF_1_Pos          (5U)                            /*!< CMP Channel1 Failling Pending Flag (Bit 5)         */
#define CMP_SR_FALIF_1_Msk          (0x1UL << CMP_SR_FALIF_1_Pos)   /*!< CMP Channel1 Failling Pending Flag (Bitfield-Mask) */
#define CMP_SR_FALIF_1              CMP_SR_FALIF_1_Msk
#define CMP_SR_FALIF_0_Pos          (4U)                            /*!< CMP Channel0 Failling Pending Flag (Bit 4)         */
#define CMP_SR_FALIF_0_Msk          (0x1UL << CMP_SR_FALIF_0_Pos)   /*!< CMP Channel0 Failling Pending Flag (Bitfield-Mask) */
#define CMP_SR_FALIF_0              CMP_SR_FALIF_0_Msk
#define CMP_SR_RISIF_3_Pos          (3U)                            /*!< CMP Channel3 Rising Pending Flag (Bit 3)           */
#define CMP_SR_RISIF_3_Msk          (0x1UL << CMP_SR_RISIF_3_Pos)   /*!< CMP Channel3 Rising Pending Flag (Bitfield-Mask)   */
#define CMP_SR_RISIF_3              CMP_SR_RISIF_3_Msk
#define CMP_SR_RISIF_2_Pos          (2U)                            /*!< CMP Channel2 Rising Pending Flag (Bit 2)           */
#define CMP_SR_RISIF_2_Msk          (0x1UL << CMP_SR_RISIF_2_Pos)   /*!< CMP Channel2 Rising Pending Flag (Bitfield-Mask)   */
#define CMP_SR_RISIF_2              CMP_SR_RISIF_2_Msk
#define CMP_SR_RISIF_1_Pos          (1U)                            /*!< CMP Channel1 Rising Pending Flag (Bit 1)           */
#define CMP_SR_RISIF_1_Msk          (0x1UL << CMP_SR_RISIF_1_Pos)   /*!< CMP Channel1 Rising Pending Flag (Bitfield-Mask)   */
#define CMP_SR_RISIF_1              CMP_SR_RISIF_1_Msk
#define CMP_SR_RISIF_0_Pos          (0U)                            /*!< CMP Channel0 Rising Pending Flag (Bit 0)           */
#define CMP_SR_RISIF_0_Msk          (0x1UL << CMP_SR_RISIF_0_Pos)   /*!< CMP Channel0 Rising Pending Flag (Bitfield-Mask)   */
#define CMP_SR_RISIF_0              CMP_SR_RISIF_0_Msk

/********************  Bit definition for CMPx_DEBR register  *****************/
#define CMP_DEBR_DEB_Pos            (0U)                            /*!< CMP Channelx Debounce Value (Bit 0 - 11)           */
#define CMP_DEBR_DEB_Msk            (0xFFFUL << CMP_DEBR_DEB_Pos)   /*!< CMP Channelx Debounce Value (Bitfield-Mask)        */


/******************************************************************************/
/*                                                                            */
/*                     Digital to Analog Converter (DAC)                      */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DACx_CR register  *******************/
#define DAC_CR_STE_Pos              (25U)                           /*!< Sawtooth Enable (Bit 25)                               */
#define DAC_CR_STE_Msk              (0x1UL << DAC_CR_STE_Pos)       /*!< Sawtooth Enable (Bitfield-Mask)                        */
#define DAC_CR_STE                  DAC_CR_STE_Msk
#define DAC_CR_STDIR_Pos            (24U)                           /*!< Sawtooth Direction (Bit 24)                            */
#define DAC_CR_STDIR_Msk            (0x1UL << DAC_CR_STDIR_Pos)     /*!< Sawtooth Direction (Bitfield-Mask)                     */
#define DAC_CR_STDIR                DAC_CR_STDIR_Msk
#define DAC_CR_STINCTRIG_Pos        (20U)                           /*!< Sawtooth Increment Trigger (Bit 20 - 23)               */
#define DAC_CR_STINCTRIG_Msk        (0xFUL << DAC_CR_STINCTRIG_Pos) /*!< Sawtooth Increment Trigger (Bitfield-Mask)             */
#define DAC_CR_STRSTTRIG_Pos        (16U)                           /*!< Sawtooth Reset Trigger (Bit 16 - 19)                   */
#define DAC_CR_STRSTTRIG_Msk        (0xFUL << DAC_CR_STRSTTRIG_Pos) /*!< Sawtooth Reset Trigger (Bitfield-Mask)                 */
#define DAC_CR_TGE_Pos              (13U)                           /*!< Triangle Enable (Bit 13)                               */
#define DAC_CR_TGE_Msk              (0x1UL << DAC_CR_TGE_Pos)       /*!< Triangle Enable (Bitfield-Mask)                        */
#define DAC_CR_TGE                  DAC_CR_TGE_Msk
#define DAC_CR_TGDIR_Pos            (12U)                           /*!< Triangle Direction (Bit 12)                            */
#define DAC_CR_TGDIR_Msk            (0x1UL << DAC_CR_TGDIR_Pos)     /*!< Triangle Direction (Bitfield-Mask)                     */
#define DAC_CR_TGDIR                DAC_CR_TGDIR_Msk
#define DAC_CR_TGAMP_Pos            (8U)                            /*!< Triangle Amplitude (Bit 8 - 11)                        */
#define DAC_CR_TGAMP_Msk            (0xFUL << DAC_CR_TGAMP_Pos)     /*!< Triangle Amplitude (Bitfield-Mask)                     */
#define DAC_CR_TGAMP_0              (0x1UL << DAC_CR_TGAMP_Pos)
#define DAC_CR_TGAMP_1              (0x2UL << DAC_CR_TGAMP_Pos)
#define DAC_CR_TGAMP_2              (0x4UL << DAC_CR_TGAMP_Pos)
#define DAC_CR_TGAMP_3              (0x8UL << DAC_CR_TGAMP_Pos)
#define DAC_CR_TGTRIG_Pos           (4U)                            /*!< Triangle Trigger (Bit 4 - 7)                           */
#define DAC_CR_TGTRIG_Msk           (0xFUL << DAC_CR_TGTRIG_Pos)    /*!< Triangle Trigger (Bitfield-Mask)                       */
#define DAC_CR_DBIE_Pos             (3U)                            /*!< DONEB Interrupt Enable (Bit 3)                         */
#define DAC_CR_DBIE_Msk             (0x1UL << DAC_CR_DBIE_Pos)      /*!< DONEB Interrupt Enable (Bitfield-Mask)                 */
#define DAC_CR_DBIE                 DAC_CR_DBIE_Msk
#define DAC_CR_DIE_Pos              (2U)                            /*!< DONE Interrupt Enable (Bit 2)                          */
#define DAC_CR_DIE_Msk              (0x1UL << DAC_CR_DIE_Pos)       /*!< DONE Interrupt Enable (Bitfield-Mask)                  */
#define DAC_CR_DIE                  DAC_CR_DIE_Msk
#define DAC_CR_OEN_Pos              (1U)                            /*!< Output Enable (Bit 1)                                  */
#define DAC_CR_OEN_Msk              (0x1UL << DAC_CR_OEN_Pos)       /*!< Output Enable (Bitfield-Mask)                          */
#define DAC_CR_OEN                  DAC_CR_OEN_Msk
#define DAC_CR_PEN_Pos              (0U)                            /*!< Peripheral Enable (Bit 0)                              */
#define DAC_CR_PEN_Msk              (0x1UL << DAC_CR_PEN_Pos)       /*!< Peripheral Enable (Bitfield-Mask)                      */
#define DAC_CR_PEN                  DAC_CR_PEN_Msk

/********************  Bit definition for DAC_ISR register  *******************/
#define DAC_ISR_DB3IF_Pos           (7U)                            /*!< DAC Channel_3 DONEB Pending Flag (Bit 7)               */
#define DAC_ISR_DB3IF_Msk           (0x1UL << DAC_ISR_DB3IF_Pos)    /*!< DAC Channel_3 DONEB Pending Flag (Bitfield-Mask)       */
#define DAC_ISR_DB3IF               DAC_ISR_DB3IF_Msk
#define DAC_ISR_DB2IF_Pos           (6U)                            /*!< DAC Channel_2 DONEB Pending Flag (Bit 6)               */
#define DAC_ISR_DB2IF_Msk           (0x1UL << DAC_ISR_DB2IF_Pos)    /*!< DAC Channel_2 DONEB Pending Flag (Bitfield-Mask)       */
#define DAC_ISR_DB2IF               DAC_ISR_DB2IF_Msk
#define DAC_ISR_DB1IF_Pos           (5U)                            /*!< DAC Channel_1 DONEB Pending Flag (Bit 5)               */
#define DAC_ISR_DB1IF_Msk           (0x1UL << DAC_ISR_DB1IF_Pos)    /*!< DAC Channel_1 DONEB Pending Flag (Bitfield-Mask)       */
#define DAC_ISR_DB1IF               DAC_ISR_DB1IF_Msk
#define DAC_ISR_DB0IF_Pos           (4U)                            /*!< DAC Channel_0 DONEB Pending Flag (Bit 4)               */
#define DAC_ISR_DB0IF_Msk           (0x1UL << DAC_ISR_DB0IF_Pos)    /*!< DAC Channel_0 DONEB Pending Flag (Bitfield-Mask)       */
#define DAC_ISR_DB0IF               DAC_ISR_DB0IF_Msk
#define DAC_ISR_D3IF_Pos            (3U)                            /*!< DAC Channel_3 DONE Pending Flag (Bit 3)                */
#define DAC_ISR_D3IF_Msk            (0x1UL << DAC_ISR_D3IF_Pos)     /*!< DAC Channel_3 DONE Pending Flag (Bitfield-Mask)        */
#define DAC_ISR_D3IF                DAC_ISR_D3IF_Msk
#define DAC_ISR_D2IF_Pos            (2U)                            /*!< DAC Channel_2 DONE Pending Flag (Bit 2)                */
#define DAC_ISR_D2IF_Msk            (0x1UL << DAC_ISR_D2IF_Pos)     /*!< DAC Channel_2 DONE Pending Flag (Bitfield-Mask)        */
#define DAC_ISR_D2IF                DAC_ISR_D2IF_Msk
#define DAC_ISR_D1IF_Pos            (1U)                            /*!< DAC Channel_1 DONE Pending Flag (Bit 1)                */
#define DAC_ISR_D1IF_Msk            (0x1UL << DAC_ISR_D1IF_Pos)     /*!< DAC Channel_1 DONE Pending Flag (Bitfield-Mask)        */
#define DAC_ISR_D1IF                DAC_ISR_D1IF_Msk
#define DAC_ISR_D0IF_Pos            (0U)                            /*!< DAC Channel_0 DONE Pending Flag (Bit 0)                */
#define DAC_ISR_D0IF_Msk            (0x1UL << DAC_ISR_D0IF_Pos)     /*!< DAC Channel_0 DONE Pending Flag (Bitfield-Mask)        */
#define DAC_ISR_D0IF                DAC_ISR_D0IF_Msk

/********************  Bit definition for DAC_SWTR register  ******************/
#define DAC_SWTR_SWTB3_Pos          (7U)                            /*!< DAC Channel_3 Software Trigger B (Bit 7)               */
#define DAC_SWTR_SWTB3_Msk          (0x1UL << DAC_SWTR_SWTB3_Pos)   /*!< DAC Channel_3 Software Trigger B (Bitfield-Mask)       */
#define DAC_SWTR_SWTB3              DAC_SWTR_SWTB3_Msk
#define DAC_SWTR_SWTB2_Pos          (6U)                            /*!< DAC Channel_2 Software Trigger B (Bit 6)               */
#define DAC_SWTR_SWTB2_Msk          (0x1UL << DAC_SWTR_SWTB2_Pos)   /*!< DAC Channel_2 Software Trigger B (Bitfield-Mask)       */
#define DAC_SWTR_SWTB2              DAC_SWTR_SWTB2_Msk
#define DAC_SWTR_SWTB1_Pos          (5U)                            /*!< DAC Channel_1 Software Trigger B (Bit 5)               */
#define DAC_SWTR_SWTB1_Msk          (0x1UL << DAC_SWTR_SWTB1_Pos)   /*!< DAC Channel_1 Software Trigger B (Bitfield-Mask)       */
#define DAC_SWTR_SWTB1              DAC_SWTR_SWTB1_Msk
#define DAC_SWTR_SWTB0_Pos          (4U)                            /*!< DAC Channel_0 Software Trigger B (Bit 4)               */
#define DAC_SWTR_SWTB0_Msk          (0x1UL << DAC_SWTR_SWTB0_Pos)   /*!< DAC Channel_0 Software Trigger B (Bitfield-Mask)       */
#define DAC_SWTR_SWTB0              DAC_SWTR_SWTB0_Msk
#define DAC_SWTR_SWT3_Pos           (3U)                            /*!< DAC Channel_3 Software Trigger (Bit 3)                 */
#define DAC_SWTR_SWT3_Msk           (0x1UL << DAC_SWTR_SWT3_Pos)    /*!< DAC Channel_3 Software Trigger (Bitfield-Mask)         */
#define DAC_SWTR_SWT3               DAC_SWTR_SWT3_Msk
#define DAC_SWTR_SWT2_Pos           (2U)                            /*!< DAC Channel_2 Software Trigger (Bit 2)                 */
#define DAC_SWTR_SWT2_Msk           (0x1UL << DAC_SWTR_SWT2_Pos)    /*!< DAC Channel_2 Software Trigger (Bitfield-Mask)         */
#define DAC_SWTR_SWT2               DAC_SWTR_SWT2_Msk
#define DAC_SWTR_SWT1_Pos           (1U)                            /*!< DAC Channel_1 Software Trigger (Bit 1)                 */
#define DAC_SWTR_SWT1_Msk           (0x1UL << DAC_SWTR_SWT1_Pos)    /*!< DAC Channel_1 Software Trigger (Bitfield-Mask)         */
#define DAC_SWTR_SWT1               DAC_SWTR_SWT1_Msk
#define DAC_SWTR_SWT0_Pos           (0U)                            /*!< DAC Channel_0 Software Trigger (Bit 0)                 */
#define DAC_SWTR_SWT0_Msk           (0x1UL << DAC_SWTR_SWT0_Pos)    /*!< DAC Channel_0 Software Trigger (Bitfield-Mask)         */
#define DAC_SWTR_SWT0               DAC_SWTR_SWT0_Msk

/********************  Bit definition for DACx_WDR register  ******************/
#define DAC_WDR_WDAT_Pos            (0U)                            /*!< DAC Channel x Write Data (Bit 0)                       */
#define DAC_WDR_WDAT_Msk            (0xFFFUL << DAC_WDR_WDAT_Pos)   /*!< DAC Channel x Write Data (Bitfield-Mask)               */

/********************  Bit definition for DACx_RDR register  ******************/
#define DAC_RDR_RDAT_Pos            (0U)                            /*!< DAC Channel x Read Data (Bit 0)                        */
#define DAC_RDR_RDAT_Msk            (0xFFFUL << DAC_RDR_RDAT_Pos)   /*!< DAC Channel x Read Data (Bitfield-Mask)                */

/********************  Bit definition for DACx_SIDR register  *****************/
#define DAC_SIDR_SID_Pos            (0U)                            /*!< DAC Channel x Sawtooth Increment Data (Bit 0)          */
#define DAC_SIDR_SID_Msk            (0xFFFFUL << DAC_SIDR_SID_Pos)  /*!< DAC Channel x Sawtooth Increment Data (Bitfield-Mask)  */

/********************  Bit definition for DACx_SRDR register  *****************/
#define DAC_SRDR_SRD_Pos            (0U)                            /*!< DAC Channel x Sawtooth Reset Data (Bit 0)              */
#define DAC_SRDR_SRD_Msk            (0xFFFFUL << DAC_SRDR_SRD_Pos)  /*!< DAC Channel x Sawtooth Reset Data (Bitfield-Mask)      */


/******************************************************************************/
/*                                                                            */
/*                     Analog to Digital Converter (ADC)                      */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for ADC_CR0 register  *******************/
#define ADC_CR0_JADSTP_Pos          (3U)
#define ADC_CR0_JADSTP_Msk          (0x1UL << ADC_CR0_JADSTP_Pos)   /*!< 0x00000008                                             */
#define ADC_CR0_JADSTP              ADC_CR0_JADSTP_Msk              /*!< ADC Group Injected Conversion Stop                     */
#define ADC_CR0_ADSTP_Pos           (2U)
#define ADC_CR0_ADSTP_Msk           (0x1UL << ADC_CR0_ADSTP_Pos)    /*!< 0x00000004                                             */
#define ADC_CR0_ADSTP               ADC_CR0_ADSTP_Msk               /*!< ADC Group Regular Conversion Stop                      */
#define ADC_CR0_JADSTART_Pos        (1U)
#define ADC_CR0_JADSTART_Msk        (0x1UL << ADC_CR0_JADSTART_Pos) /*!< 0x00000002                                             */
#define ADC_CR0_JADSTART            ADC_CR0_JADSTART_Msk            /*!< ADC Group Injected Conversion Start                    */
#define ADC_CR0_ADSTART_Pos         (0U)
#define ADC_CR0_ADSTART_Msk         (0x1UL << ADC_CR0_ADSTART_Pos)  /*!< 0x00000001                                             */
#define ADC_CR0_ADSTART             ADC_CR0_ADSTART_Msk             /*!< ADC Group Regular Conversion Start                     */

/********************  Bit definition for ADC_CR1 register  *******************/
#define ADC_CR1_SYNCEN_Pos          (23U)
#define ADC_CR1_SYNCEN_Msk          (0x1UL << ADC_CR1_SYNCEN_Pos)   /*!< 0x00800000                                             */
#define ADC_CR1_SYNCEN              ADC_CR1_SYNCEN_Msk              /*!< ADC Synchronous Conversion Enable                      */
#define ADC_CR1_JAUTO_Pos           (22U)
#define ADC_CR1_JAUTO_Msk           (0x1UL << ADC_CR1_JAUTO_Pos)    /*!< 0x00400000                                             */
#define ADC_CR1_JAUTO               ADC_CR1_JAUTO_Msk               /*!< ADC Group Injected Automatic Trigger Mode              */
#define ADC_CR1_JDISCEN_Pos         (20U)
#define ADC_CR1_JDISCEN_Msk         (0x1UL << ADC_CR1_JDISCEN_Pos)  /*!< 0x00100000                                             */
#define ADC_CR1_JDISCEN             ADC_CR1_JDISCEN_Msk             /*!< ADC Group Injected Sequencer Discontinuous Mode        */
#define ADC_CR1_DISCNUM_Pos         (17U)
#define ADC_CR1_DISCNUM_Msk         (0x7UL << ADC_CR1_DISCNUM_Pos)  /*!< 0x000E0000                                             */
#define ADC_CR1_DISCNUM             ADC_CR1_DISCNUM_Msk             /*!< ADC Group Regular Sequencer Discontinuous Num Of Ranks */
#define ADC_CR1_DISCNUM_0           (0x1UL << ADC_CR1_DISCNUM_Pos)  /*!< 0x00020000                                             */
#define ADC_CR1_DISCNUM_1           (0x2UL << ADC_CR1_DISCNUM_Pos)  /*!< 0x00040000                                             */
#define ADC_CR1_DISCNUM_2           (0x4UL << ADC_CR1_DISCNUM_Pos)  /*!< 0x00080000                                             */
#define ADC_CR1_DISCEN_Pos          (16U)
#define ADC_CR1_DISCEN_Msk          (0x1UL << ADC_CR1_DISCEN_Pos)   /*!< 0x00010000                                             */
#define ADC_CR1_DISCEN              ADC_CR1_DISCEN_Msk              /*!< ADC Group Regular Sequencer Discontinuous Mode         */
#define ADC_CR1_CONT_Pos            (13U)
#define ADC_CR1_CONT_Msk            (0x1UL << ADC_CR1_CONT_Pos)     /*!< 0x00002000                                             */
#define ADC_CR1_CONT                ADC_CR1_CONT_Msk                /*!< ADC Group Regular Continuous Conversion Mode           */
#define ADC_CR1_OVRMOD_Pos          (12U)
#define ADC_CR1_OVRMOD_Msk          (0x1UL << ADC_CR1_OVRMOD_Pos)   /*!< 0x00001000                                             */
#define ADC_CR1_OVRMOD              ADC_CR1_OVRMOD_Msk              /*!< ADC Group Regular Overrun Configuration                */
#define ADC_CR1_ROVSM_Pos           (10U)
#define ADC_CR1_ROVSM_Msk           (0x1UL << ADC_CR1_ROVSM_Pos)    /*!< 0x00000400                                             */
#define ADC_CR1_ROVSM               ADC_CR1_ROVSM_Msk               /*!< ADC Oversampling Mode Managing Interlaced Conversions  */
#define ADC_CR1_TROVS_Pos           (9U)
#define ADC_CR1_TROVS_Msk           (0x1UL << ADC_CR1_TROVS_Pos)    /*!< 0x00000200                                             */
#define ADC_CR1_TROVS               ADC_CR1_TROVS_Msk               /*!< ADC Oversampling Discontinuous Mode                    */
#define ADC_CR1_OVSS_Pos            (5U)
#define ADC_CR1_OVSS_Msk            (0xFUL << ADC_CR1_OVSS_Pos)     /*!< 0x000001E0                                             */
#define ADC_CR1_OVSS                ADC_CR1_OVSS_Msk                /*!< ADC Oversampling Shift                                 */
#define ADC_CR1_OVSS_0              (0x1UL << ADC_CR1_OVSS_Pos)     /*!< 0x00000020                                             */
#define ADC_CR1_OVSS_1              (0x2UL << ADC_CR1_OVSS_Pos)     /*!< 0x00000040                                             */
#define ADC_CR1_OVSS_2              (0x4UL << ADC_CR1_OVSS_Pos)     /*!< 0x00000080                                             */
#define ADC_CR1_OVSS_3              (0x8UL << ADC_CR1_OVSS_Pos)     /*!< 0x00000100                                             */
#define ADC_CR1_OVSR_Pos            (2U)
#define ADC_CR1_OVSR_Msk            (0x7UL << ADC_CR1_OVSR_Pos)     /*!< 0x0000001C                                             */
#define ADC_CR1_OVSR                ADC_CR1_OVSR_Msk                /*!< ADC Oversampling Ratio                                 */
#define ADC_CR1_OVSR_0              (0x1UL << ADC_CR1_OVSR_Pos)     /*!< 0x00000004                                             */
#define ADC_CR1_OVSR_1              (0x2UL << ADC_CR1_OVSR_Pos)     /*!< 0x00000008                                             */
#define ADC_CR1_OVSR_2              (0x4UL << ADC_CR1_OVSR_Pos)     /*!< 0x00000010                                             */
#define ADC_CR1_JOVSE_Pos           (1U)
#define ADC_CR1_JOVSE_Msk           (0x1UL << ADC_CR1_JOVSE_Pos)    /*!< 0x00000002                                             */
#define ADC_CR1_JOVSE               ADC_CR1_JOVSE_Msk               /*!< ADC Oversampler Enable On Scope ADC Group Injected     */
#define ADC_CR1_ROVSE_Pos           (0U)
#define ADC_CR1_ROVSE_Msk           (0x1UL << ADC_CR1_ROVSE_Pos)    /*!< 0x00000001                                             */
#define ADC_CR1_ROVSE               ADC_CR1_ROVSE_Msk               /*!< ADC Oversampler Enable On Scope ADC Group Regular      */

/********************  Bit definition for ADC_CR2 register  *******************/
#define ADC_CR2_ISEL_Pos            (12U)
#define ADC_CR2_ISEL_Msk            (0x3UL << ADC_CR2_ISEL_Pos)     /*!< 0x00003000                                             */
#define ADC_CR2_ISEL                ADC_CR2_ISEL_Msk                /*!< ADC                                                    */
#define ADC_CR2_ISEL_0              (0x1UL << ADC_CR2_ISEL_Pos)     /*!< 0x00001000                                             */
#define ADC_CR2_ISEL_1              (0x2UL << ADC_CR2_ISEL_Pos)     /*!< 0x00002000                                             */
#define ADC_CR2_TBOMOD_Pos          (11U)
#define ADC_CR2_TBOMOD_Msk          (0x1UL << ADC_CR2_TBOMOD_Pos)   /*!< 0x00000800                                             */
#define ADC_CR2_TBOMOD              ADC_CR2_TBOMOD_Msk              /*!< ADC                                                    */
#define ADC_CR2_TBIMOD_Pos          (8U)
#define ADC_CR2_TBIMOD_Msk          (0x7UL << ADC_CR2_TBIMOD_Pos)   /*!< 0x00000700                                             */
#define ADC_CR2_TBIMOD              ADC_CR2_TBIMOD_Msk              /*!< ADC                                                    */
#define ADC_CR2_TBIMOD_0            (0x1UL << ADC_CR2_TBIMOD_Pos)   /*!< 0x00000100                                             */
#define ADC_CR2_TBIMOD_1            (0x2UL << ADC_CR2_TBIMOD_Pos)   /*!< 0x00000200                                             */
#define ADC_CR2_TBIMOD_2            (0x4UL << ADC_CR2_TBIMOD_Pos)   /*!< 0x00000400                                             */
#define ADC_CR2_TB_EN_Pos           (4U)
#define ADC_CR2_TB_EN_Msk           (0x1UL << ADC_CR2_TB_EN_Pos)    /*!< 0x00000010                                             */
#define ADC_CR2_TB_EN               ADC_CR2_TB_EN_Msk               /*!< ADC                                                    */
#define ADC_CR2_CH_EN_Pos           (3U)
#define ADC_CR2_CH_EN_Msk           (0x1UL << ADC_CR2_CH_EN_Pos)    /*!< 0x00000008                                             */
#define ADC_CR2_CH_EN               ADC_CR2_CH_EN_Msk               /*!< ADC                                                    */
#define ADC_CR2_FADC_EN_Pos         (2U)
#define ADC_CR2_FADC_EN_Msk         (0x1UL << ADC_CR2_FADC_EN_Pos)  /*!< 0x00000004                                             */
#define ADC_CR2_FADC_EN             ADC_CR2_FADC_EN_Msk             /*!< ADC                                                    */
#define ADC_CR2_REF_EN_Pos          (1U)
#define ADC_CR2_REF_EN_Msk          (0x1UL << ADC_CR2_REF_EN_Pos)   /*!< 0x00000002                                             */
#define ADC_CR2_REF_EN              ADC_CR2_REF_EN_Msk              /*!< ADC                                                    */
#define ADC_CR2_BIAS_EN_Pos         (0U)
#define ADC_CR2_BIAS_EN_Msk         (0x1UL << ADC_CR2_BIAS_EN_Pos)  /*!< 0x00000001                                             */
#define ADC_CR2_BIAS_EN             ADC_CR2_BIAS_EN_Msk             /*!< ADC                                                    */

/*******************  Bit definition for ADC_DIFSEL register  *****************/
#define ADC_DIFSEL_DIFSEL_Pos       (0U)
#define ADC_DIFSEL_DIFSEL_Msk       (0xFFFUL << ADC_DIFSEL_DIFSEL_Pos)      /*!< 0x00000FFF                                     */
#define ADC_DIFSEL_DIFSEL           ADC_DIFSEL_DIFSEL_Msk                   /*!< ADC Channel Differential Or Single-ended Mode  */
#define ADC_DIFSEL_DIFSEL_0         (0x00001UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000001                                     */
#define ADC_DIFSEL_DIFSEL_1         (0x00002UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000002                                     */
#define ADC_DIFSEL_DIFSEL_2         (0x00004UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000004                                     */
#define ADC_DIFSEL_DIFSEL_3         (0x00008UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000008                                     */
#define ADC_DIFSEL_DIFSEL_4         (0x00010UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000010                                     */
#define ADC_DIFSEL_DIFSEL_5         (0x00020UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000020                                     */
#define ADC_DIFSEL_DIFSEL_6         (0x00040UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000040                                     */
#define ADC_DIFSEL_DIFSEL_7         (0x00080UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000080                                     */
#define ADC_DIFSEL_DIFSEL_8         (0x00100UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000100                                     */
#define ADC_DIFSEL_DIFSEL_9         (0x00200UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000200                                     */
#define ADC_DIFSEL_DIFSEL_10        (0x00400UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000400                                     */
#define ADC_DIFSEL_DIFSEL_11        (0x00800UL << ADC_DIFSEL_DIFSEL_Pos)    /*!< 0x00000800                                     */

/********************  Bit definition for ADC_IER register  *******************/
#define ADC_IER_EOSMPIE_Pos         (9U)
#define ADC_IER_EOSMPIE_Msk         (0x1UL << ADC_IER_EOSMPIE_Pos)  /*!< 0x00000200                                             */
#define ADC_IER_EOSMPIE             ADC_IER_EOSMPIE_Msk             /*!< ADC Group Regular End Of Sampling Interrupt            */
#define ADC_IER_ADRDYIE_Pos         (8U)
#define ADC_IER_ADRDYIE_Msk         (0x1UL << ADC_IER_ADRDYIE_Pos)  /*!< 0x00000100                                             */
#define ADC_IER_ADRDYIE             ADC_IER_ADRDYIE_Msk             /*!< ADC Ready Interrupt                                    */
#define ADC_IER_AWD2IE_Pos          (7U)
#define ADC_IER_AWD2IE_Msk          (0x1UL << ADC_IER_AWD2IE_Pos)   /*!< 0x00000080                                             */
#define ADC_IER_AWD2IE              ADC_IER_AWD2IE_Msk              /*!< ADC Analog Watchdog 2 Interrupt                        */
#define ADC_IER_AWD1IE_Pos          (6U)
#define ADC_IER_AWD1IE_Msk          (0x1UL << ADC_IER_AWD1IE_Pos)   /*!< 0x00000040                                             */
#define ADC_IER_AWD1IE              ADC_IER_AWD1IE_Msk              /*!< ADC Analog Watchdog 1 Interrupt                        */
#define ADC_IER_AWD0IE_Pos          (5U)
#define ADC_IER_AWD0IE_Msk          (0x1UL << ADC_IER_AWD0IE_Pos)   /*!< 0x00000020                                             */
#define ADC_IER_AWD0IE              ADC_IER_AWD0IE_Msk              /*!< ADC Analog Watchdog 0 Interrupt                        */
#define ADC_IER_OVRIE_Pos           (4U)
#define ADC_IER_OVRIE_Msk           (0x1UL << ADC_IER_OVRIE_Pos)    /*!< 0x00000010                                             */
#define ADC_IER_OVRIE               ADC_IER_OVRIE_Msk               /*!< ADC Group Regular Overrun Interrupt                    */
#define ADC_IER_JEOSIE_Pos          (3U)
#define ADC_IER_JEOSIE_Msk          (0x1UL << ADC_IER_JEOSIE_Pos)   /*!< 0x00000008                                             */
#define ADC_IER_JEOSIE              ADC_IER_JEOSIE_Msk              /*!< ADC Group Injected End Of Sequence Conversion Interrupt*/
#define ADC_IER_JEOCIE_Pos          (2U)
#define ADC_IER_JEOCIE_Msk          (0x1UL << ADC_IER_JEOCIE_Pos)   /*!< 0x00000004                                             */
#define ADC_IER_JEOCIE              ADC_IER_JEOCIE_Msk              /*!< ADC Group Injected End Of Unitary Conversion Interrupt */
#define ADC_IER_EOSIE_Pos           (1U)
#define ADC_IER_EOSIE_Msk           (0x1UL << ADC_IER_EOSIE_Pos)    /*!< 0x00000002                                             */
#define ADC_IER_EOSIE               ADC_IER_EOSIE_Msk               /*!< ADC Group Regular End Of Sequence Conversions Interrupt*/
#define ADC_IER_EOCIE_Pos           (0U)
#define ADC_IER_EOCIE_Msk           (0x1UL << ADC_IER_EOCIE_Pos)    /*!< 0x00000001                                             */
#define ADC_IER_EOCIE               ADC_IER_EOCIE_Msk               /*!< ADC Group Regular End Of Unitary Conversion Interrupt  */

/********************  Bit definition for ADC_ISR register  *******************/
#define ADC_ISR_EOSMP_Pos           (9U)
#define ADC_ISR_EOSMP_Msk           (0x1UL << ADC_ISR_EOSMP_Pos)    /*!< 0x00000200                                             */
#define ADC_ISR_EOSMP               ADC_ISR_EOSMP_Msk               /*!< ADC Group Regular End Of Sampling Flag                 */
#define ADC_ISR_ADRDY_Pos           (8U)
#define ADC_ISR_ADRDY_Msk           (0x1UL << ADC_ISR_ADRDY_Pos)    /*!< 0x00000100                                             */
#define ADC_ISR_ADRDY               ADC_ISR_ADRDY_Msk               /*!< ADC Ready Flag                                         */
#define ADC_ISR_AWD2_Pos            (7U)
#define ADC_ISR_AWD2_Msk            (0x1UL << ADC_ISR_AWD2_Pos)     /*!< 0x00000080                                             */
#define ADC_ISR_AWD2                ADC_ISR_AWD2_Msk                /*!< ADC Analog Watchdog 2 Flag                             */
#define ADC_ISR_AWD1_Pos            (6U)
#define ADC_ISR_AWD1_Msk            (0x1UL << ADC_ISR_AWD1_Pos)     /*!< 0x00000040                                             */
#define ADC_ISR_AWD1                ADC_ISR_AWD1_Msk                /*!< ADC Analog Watchdog 1 Flag                             */
#define ADC_ISR_AWD0_Pos            (5U)
#define ADC_ISR_AWD0_Msk            (0x1UL << ADC_ISR_AWD0_Pos)     /*!< 0x00000020                                             */
#define ADC_ISR_AWD0                ADC_ISR_AWD0_Msk                /*!< ADC Analog Watchdog 0 Flag                             */
#define ADC_ISR_OVR_Pos             (4U)
#define ADC_ISR_OVR_Msk             (0x1UL << ADC_ISR_OVR_Pos)      /*!< 0x00000010                                             */
#define ADC_ISR_OVR                 ADC_ISR_OVR_Msk                 /*!< ADC Group Regular Overrun Flag                         */
#define ADC_ISR_JEOS_Pos            (3U)
#define ADC_ISR_JEOS_Msk            (0x1UL << ADC_ISR_JEOS_Pos)     /*!< 0x00000008                                             */
#define ADC_ISR_JEOS                ADC_ISR_JEOS_Msk                /*!< ADC Group Injected End Of Sequence Conversions Flag    */
#define ADC_ISR_JEOC_Pos            (2U)
#define ADC_ISR_JEOC_Msk            (0x1UL << ADC_ISR_JEOC_Pos)     /*!< 0x00000004                                             */
#define ADC_ISR_JEOC                ADC_ISR_JEOC_Msk                /*!< ADC Group Injected End Of Unitary Conversion Flag      */
#define ADC_ISR_EOS_Pos             (1U)
#define ADC_ISR_EOS_Msk             (0x1UL << ADC_ISR_EOS_Pos)      /*!< 0x00000002                                             */
#define ADC_ISR_EOS                 ADC_ISR_EOS_Msk                 /*!< ADC Group Regular End Of Sequence Conversions Flag     */
#define ADC_ISR_EOC_Pos             (0U)
#define ADC_ISR_EOC_Msk             (0x1UL << ADC_ISR_EOC_Pos)      /*!< 0x00000001                                             */
#define ADC_ISR_EOC                 ADC_ISR_EOC_Msk                 /*!< ADC Group Regular End Of Unitary Conversion Flag       */

/********************  Bit definition for ADC_SIER register  ******************/
#define ADC_SIER_CHANNEL_Pos        (0U)
#define ADC_SIER_CHANNEL_Msk        (0xFFFUL << ADC_SIER_CHANNEL_Pos)   /*!< 0x00000FFF                                         */
#define ADC_SIER_CHANNEL            ADC_SIER_CHANNEL_Msk                /*!< ADC Group Regular End Of Sampling Interrupt        */
#define ADC_SIER_CHANNEL_0          (0x00001UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000001                                         */
#define ADC_SIER_CHANNEL_1          (0x00002UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000002                                         */
#define ADC_SIER_CHANNEL_2          (0x00004UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000004                                         */
#define ADC_SIER_CHANNEL_3          (0x00008UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000008                                         */
#define ADC_SIER_CHANNEL_4          (0x00010UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000010                                         */
#define ADC_SIER_CHANNEL_5          (0x00020UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000020                                         */
#define ADC_SIER_CHANNEL_6          (0x00040UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000040                                         */
#define ADC_SIER_CHANNEL_7          (0x00080UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000080                                         */
#define ADC_SIER_CHANNEL_8          (0x00100UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000100                                         */
#define ADC_SIER_CHANNEL_9          (0x00200UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000200                                         */
#define ADC_SIER_CHANNEL_10         (0x00400UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000400                                         */
#define ADC_SIER_CHANNEL_11         (0x00800UL << ADC_SIER_CHANNEL_Pos) /*!< 0x00000800                                         */

/********************  Bit definition for ADC_SISR register  ******************/
#define ADC_SISR_CHANNEL_Pos        (0U)
#define ADC_SISR_CHANNEL_Msk        (0xFFFUL << ADC_SISR_CHANNEL_Pos)   /*!< 0x00000FFF                                         */
#define ADC_SISR_CHANNEL            ADC_SISR_CHANNEL_Msk                /*!< ADC Group Regular End Of Sampling Flag             */
#define ADC_SISR_CHANNEL_0          (0x00001UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000001                                         */
#define ADC_SISR_CHANNEL_1          (0x00002UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000002                                         */
#define ADC_SISR_CHANNEL_2          (0x00004UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000004                                         */
#define ADC_SISR_CHANNEL_3          (0x00008UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000008                                         */
#define ADC_SISR_CHANNEL_4          (0x00010UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000010                                         */
#define ADC_SISR_CHANNEL_5          (0x00020UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000020                                         */
#define ADC_SISR_CHANNEL_6          (0x00040UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000040                                         */
#define ADC_SISR_CHANNEL_7          (0x00080UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000080                                         */
#define ADC_SISR_CHANNEL_8          (0x00100UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000100                                         */
#define ADC_SISR_CHANNEL_9          (0x00200UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000200                                         */
#define ADC_SISR_CHANNEL_10         (0x00400UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000400                                         */
#define ADC_SISR_CHANNEL_11         (0x00800UL << ADC_SISR_CHANNEL_Pos) /*!< 0x00000800                                         */

/*******************  Bit definition for ADC_SMPR0 register  ******************/
#define ADC_SMPR0_SMP7_Pos          (28U)
#define ADC_SMPR0_SMP7_Msk          (0x7UL << ADC_SMPR0_SMP7_Pos)       /*!< 0x70000000                                         */
#define ADC_SMPR0_SMP7              ADC_SMPR0_SMP7_Msk                  /*!< ADC channel 7 sampling time selection              */
#define ADC_SMPR0_SMP7_0            (0x1UL << ADC_SMPR0_SMP7_Pos)       /*!< 0x10000000                                         */
#define ADC_SMPR0_SMP7_1            (0x2UL << ADC_SMPR0_SMP7_Pos)       /*!< 0x20000000                                         */
#define ADC_SMPR0_SMP7_2            (0x4UL << ADC_SMPR0_SMP7_Pos)       /*!< 0x40000000                                         */
#define ADC_SMPR0_SMP6_Pos          (24U)
#define ADC_SMPR0_SMP6_Msk          (0x7UL << ADC_SMPR0_SMP6_Pos)       /*!< 0x07000000                                         */
#define ADC_SMPR0_SMP6              ADC_SMPR0_SMP6_Msk                  /*!< ADC channel 6 sampling time selection              */
#define ADC_SMPR0_SMP6_0            (0x1UL << ADC_SMPR0_SMP6_Pos)       /*!< 0x01000000                                         */
#define ADC_SMPR0_SMP6_1            (0x2UL << ADC_SMPR0_SMP6_Pos)       /*!< 0x02000000                                         */
#define ADC_SMPR0_SMP6_2            (0x4UL << ADC_SMPR0_SMP6_Pos)       /*!< 0x04000000                                         */
#define ADC_SMPR0_SMP5_Pos          (20U)
#define ADC_SMPR0_SMP5_Msk          (0x7UL << ADC_SMPR0_SMP5_Pos)       /*!< 0x00700000                                         */
#define ADC_SMPR0_SMP5              ADC_SMPR0_SMP5_Msk                  /*!< ADC channel 5 sampling time selection              */
#define ADC_SMPR0_SMP5_0            (0x1UL << ADC_SMPR0_SMP5_Pos)       /*!< 0x00100000                                         */
#define ADC_SMPR0_SMP5_1            (0x2UL << ADC_SMPR0_SMP5_Pos)       /*!< 0x00200000                                         */
#define ADC_SMPR0_SMP5_2            (0x4UL << ADC_SMPR0_SMP5_Pos)       /*!< 0x00400000                                         */
#define ADC_SMPR0_SMP4_Pos          (16U)
#define ADC_SMPR0_SMP4_Msk          (0x7UL << ADC_SMPR0_SMP4_Pos)       /*!< 0x00070000                                         */
#define ADC_SMPR0_SMP4              ADC_SMPR0_SMP4_Msk                  /*!< ADC channel 4 sampling time selection              */
#define ADC_SMPR0_SMP4_0            (0x1UL << ADC_SMPR0_SMP4_Pos)       /*!< 0x00010000                                         */
#define ADC_SMPR0_SMP4_1            (0x2UL << ADC_SMPR0_SMP4_Pos)       /*!< 0x00020000                                         */
#define ADC_SMPR0_SMP4_2            (0x4UL << ADC_SMPR0_SMP4_Pos)       /*!< 0x00040000                                         */
#define ADC_SMPR0_SMP3_Pos          (12U)
#define ADC_SMPR0_SMP3_Msk          (0x7UL << ADC_SMPR0_SMP3_Pos)       /*!< 0x00007000                                         */
#define ADC_SMPR0_SMP3              ADC_SMPR0_SMP3_Msk                  /*!< ADC channel 3 sampling time selection              */
#define ADC_SMPR0_SMP3_0            (0x1UL << ADC_SMPR0_SMP3_Pos)       /*!< 0x00001000                                         */
#define ADC_SMPR0_SMP3_1            (0x2UL << ADC_SMPR0_SMP3_Pos)       /*!< 0x00002000                                         */
#define ADC_SMPR0_SMP3_2            (0x4UL << ADC_SMPR0_SMP3_Pos)       /*!< 0x00004000                                         */
#define ADC_SMPR0_SMP2_Pos          (8U)
#define ADC_SMPR0_SMP2_Msk          (0x7UL << ADC_SMPR0_SMP2_Pos)       /*!< 0x00000700                                         */
#define ADC_SMPR0_SMP2              ADC_SMPR0_SMP2_Msk                  /*!< ADC channel 2 sampling time selection              */
#define ADC_SMPR0_SMP2_0            (0x1UL << ADC_SMPR0_SMP2_Pos)       /*!< 0x00000100                                         */
#define ADC_SMPR0_SMP2_1            (0x2UL << ADC_SMPR0_SMP2_Pos)       /*!< 0x00000200                                         */
#define ADC_SMPR0_SMP2_2            (0x4UL << ADC_SMPR0_SMP2_Pos)       /*!< 0x00000400                                         */
#define ADC_SMPR0_SMP1_Pos          (4U)
#define ADC_SMPR0_SMP1_Msk          (0x7UL << ADC_SMPR0_SMP1_Pos)       /*!< 0x00000070                                         */
#define ADC_SMPR0_SMP1              ADC_SMPR0_SMP1_Msk                  /*!< ADC channel 1 sampling time selection              */
#define ADC_SMPR0_SMP1_0            (0x1UL << ADC_SMPR0_SMP1_Pos)       /*!< 0x00000010                                         */
#define ADC_SMPR0_SMP1_1            (0x2UL << ADC_SMPR0_SMP1_Pos)       /*!< 0x00000020                                         */
#define ADC_SMPR0_SMP1_2            (0x4UL << ADC_SMPR0_SMP1_Pos)       /*!< 0x00000040                                         */
#define ADC_SMPR0_SMP0_Pos          (0U)
#define ADC_SMPR0_SMP0_Msk          (0x7UL << ADC_SMPR0_SMP0_Pos)       /*!< 0x00000007                                         */
#define ADC_SMPR0_SMP0              ADC_SMPR0_SMP0_Msk                  /*!< ADC channel 0 sampling time selection              */
#define ADC_SMPR0_SMP0_0            (0x1UL << ADC_SMPR0_SMP0_Pos)       /*!< 0x00000001                                         */
#define ADC_SMPR0_SMP0_1            (0x2UL << ADC_SMPR0_SMP0_Pos)       /*!< 0x00000002                                         */
#define ADC_SMPR0_SMP0_2            (0x4UL << ADC_SMPR0_SMP0_Pos)       /*!< 0x00000004                                         */

/*******************  Bit definition for ADC_SMPR1 register  ******************/
#define ADC_SMPR1_SMP11_Pos         (12U)
#define ADC_SMPR1_SMP11_Msk         (0x7UL << ADC_SMPR1_SMP11_Pos)      /*!< 0x00007000                                         */
#define ADC_SMPR1_SMP11             ADC_SMPR1_SMP11_Msk                 /*!< ADC channel 11 sampling time selection             */
#define ADC_SMPR1_SMP11_0           (0x1UL << ADC_SMPR1_SMP11_Pos)      /*!< 0x00001000                                         */
#define ADC_SMPR1_SMP11_1           (0x2UL << ADC_SMPR1_SMP11_Pos)      /*!< 0x00002000                                         */
#define ADC_SMPR1_SMP11_2           (0x4UL << ADC_SMPR1_SMP11_Pos)      /*!< 0x00004000                                         */
#define ADC_SMPR1_SMP10_Pos         (8U)
#define ADC_SMPR1_SMP10_Msk         (0x7UL << ADC_SMPR1_SMP10_Pos)      /*!< 0x00000700                                         */
#define ADC_SMPR1_SMP10             ADC_SMPR1_SMP10_Msk                 /*!< ADC channel 10 sampling time selection             */
#define ADC_SMPR1_SMP10_0           (0x1UL << ADC_SMPR1_SMP10_Pos)      /*!< 0x00000100                                         */
#define ADC_SMPR1_SMP10_1           (0x2UL << ADC_SMPR1_SMP10_Pos)      /*!< 0x00000200                                         */
#define ADC_SMPR1_SMP10_2           (0x4UL << ADC_SMPR1_SMP10_Pos)      /*!< 0x00000400                                         */
#define ADC_SMPR1_SMP9_Pos          (4U)
#define ADC_SMPR1_SMP9_Msk          (0x7UL << ADC_SMPR1_SMP9_Pos)       /*!< 0x38000070                                         */
#define ADC_SMPR1_SMP9              ADC_SMPR1_SMP9_Msk                  /*!< ADC channel 9 sampling time selection              */
#define ADC_SMPR1_SMP9_0            (0x1UL << ADC_SMPR1_SMP9_Pos)       /*!< 0x00000010                                         */
#define ADC_SMPR1_SMP9_1            (0x2UL << ADC_SMPR1_SMP9_Pos)       /*!< 0x00000020                                         */
#define ADC_SMPR1_SMP9_2            (0x4UL << ADC_SMPR1_SMP9_Pos)       /*!< 0x00000040                                         */
#define ADC_SMPR1_SMP8_Pos          (0U)
#define ADC_SMPR1_SMP8_Msk          (0x7UL << ADC_SMPR1_SMP8_Pos)       /*!< 0x00000007                                         */
#define ADC_SMPR1_SMP8              ADC_SMPR1_SMP8_Msk                  /*!< ADC channel 8 sampling time selection              */
#define ADC_SMPR1_SMP8_0            (0x1UL << ADC_SMPR1_SMP8_Pos)       /*!< 0x00000001                                         */
#define ADC_SMPR1_SMP8_1            (0x2UL << ADC_SMPR1_SMP8_Pos)       /*!< 0x00000002                                         */
#define ADC_SMPR1_SMP8_2            (0x4UL << ADC_SMPR1_SMP8_Pos)       /*!< 0x00000004                                         */

/*******************  Bit definition for ADC_CALR0 register  ******************/
#define ADC_CALR0_CAL7_Pos          (28U)
#define ADC_CALR0_CAL7_Msk          (0x3UL << ADC_CALR0_CAL7_Pos)       /*!< 0x30000000                                         */
#define ADC_CALR0_CAL7              ADC_CALR0_CAL7_Msk                  /*!< ADC channel 7 Calibration Coefficient selection    */
#define ADC_CALR0_CAL7_0            (0x1UL << ADC_CALR0_CAL7_Pos)       /*!< 0x10000000                                         */
#define ADC_CALR0_CAL7_1            (0x2UL << ADC_CALR0_CAL7_Pos)       /*!< 0x20000000                                         */
#define ADC_CALR0_CAL6_Pos          (24U)
#define ADC_CALR0_CAL6_Msk          (0x3UL << ADC_CALR0_CAL6_Pos)       /*!< 0x03000000                                         */
#define ADC_CALR0_CAL6              ADC_CALR0_CAL6_Msk                  /*!< ADC channel 6 Calibration Coefficient selection    */
#define ADC_CALR0_CAL6_0            (0x1UL << ADC_CALR0_CAL6_Pos)       /*!< 0x01000000                                         */
#define ADC_CALR0_CAL6_1            (0x2UL << ADC_CALR0_CAL6_Pos)       /*!< 0x02000000                                         */
#define ADC_CALR0_CAL5_Pos          (20U)
#define ADC_CALR0_CAL5_Msk          (0x3UL << ADC_CALR0_CAL5_Pos)       /*!< 0x00300000                                         */
#define ADC_CALR0_CAL5              ADC_CALR0_CAL5_Msk                  /*!< ADC channel 5 Calibration Coefficient selection    */
#define ADC_CALR0_CAL5_0            (0x1UL << ADC_CALR0_CAL5_Pos)       /*!< 0x00100000                                         */
#define ADC_CALR0_CAL5_1            (0x2UL << ADC_CALR0_CAL5_Pos)       /*!< 0x00200000                                         */
#define ADC_CALR0_CAL4_Pos          (16U)
#define ADC_CALR0_CAL4_Msk          (0x3UL << ADC_CALR0_CAL4_Pos)       /*!< 0x00030000                                         */
#define ADC_CALR0_CAL4              ADC_CALR0_CAL4_Msk                  /*!< ADC channel 4 Calibration Coefficient selection    */
#define ADC_CALR0_CAL4_0            (0x1UL << ADC_CALR0_CAL4_Pos)       /*!< 0x00010000                                         */
#define ADC_CALR0_CAL4_1            (0x2UL << ADC_CALR0_CAL4_Pos)       /*!< 0x00020000                                         */
#define ADC_CALR0_CAL3_Pos          (12U)
#define ADC_CALR0_CAL3_Msk          (0x3UL << ADC_CALR0_CAL3_Pos)       /*!< 0x00003000                                         */
#define ADC_CALR0_CAL3              ADC_CALR0_CAL3_Msk                  /*!< ADC channel 3 Calibration Coefficient selection    */
#define ADC_CALR0_CAL3_0            (0x1UL << ADC_CALR0_CAL3_Pos)       /*!< 0x00001000                                         */
#define ADC_CALR0_CAL3_1            (0x2UL << ADC_CALR0_CAL3_Pos)       /*!< 0x00002000                                         */
#define ADC_CALR0_CAL2_Pos          (8U)
#define ADC_CALR0_CAL2_Msk          (0x3UL << ADC_CALR0_CAL2_Pos)       /*!< 0x00000300                                         */
#define ADC_CALR0_CAL2              ADC_CALR0_CAL2_Msk                  /*!< ADC channel 2 Calibration Coefficient selection    */
#define ADC_CALR0_CAL2_0            (0x1UL << ADC_CALR0_CAL2_Pos)       /*!< 0x00000100                                         */
#define ADC_CALR0_CAL2_1            (0x2UL << ADC_CALR0_CAL2_Pos)       /*!< 0x00000200                                         */
#define ADC_CALR0_CAL1_Pos          (4U)
#define ADC_CALR0_CAL1_Msk          (0x3UL << ADC_CALR0_CAL1_Pos)       /*!< 0x00000030                                         */
#define ADC_CALR0_CAL1              ADC_CALR0_CAL1_Msk                  /*!< ADC channel 1 Calibration Coefficient selection    */
#define ADC_CALR0_CAL1_0            (0x1UL << ADC_CALR0_CAL1_Pos)       /*!< 0x00000010                                         */
#define ADC_CALR0_CAL1_1            (0x2UL << ADC_CALR0_CAL1_Pos)       /*!< 0x00000020                                         */
#define ADC_CALR0_CAL0_Pos          (0U)
#define ADC_CALR0_CAL0_Msk          (0x3UL << ADC_CALR0_CAL0_Pos)       /*!< 0x00000003                                         */
#define ADC_CALR0_CAL0              ADC_CALR0_CAL0_Msk                  /*!< ADC channel 0 Calibration Coefficient selection    */
#define ADC_CALR0_CAL0_0            (0x1UL << ADC_CALR0_CAL0_Pos)       /*!< 0x00000001                                         */
#define ADC_CALR0_CAL0_1            (0x2UL << ADC_CALR0_CAL0_Pos)       /*!< 0x00000002                                         */

/*******************  Bit definition for ADC_CALR1 register  ******************/
#define ADC_CALR1_CAL11_Pos         (12U)
#define ADC_CALR1_CAL11_Msk         (0x3UL << ADC_CALR1_CAL11_Pos)      /*!< 0x00003000                                         */
#define ADC_CALR1_CAL11             ADC_CALR1_CAL11_Msk                 /*!< ADC channel 11 Calibration Coefficient selection   */
#define ADC_CALR1_CAL11_0           (0x1UL << ADC_CALR1_CAL11_Pos)      /*!< 0x00001000                                         */
#define ADC_CALR1_CAL11_1           (0x2UL << ADC_CALR1_CAL11_Pos)      /*!< 0x00002000                                         */
#define ADC_CALR1_CAL10_Pos         (8U)
#define ADC_CALR1_CAL10_Msk         (0x3UL << ADC_CALR1_CAL10_Pos)      /*!< 0x00000300                                         */
#define ADC_CALR1_CAL10             ADC_CALR1_CAL10_Msk                 /*!< ADC channel 10 Calibration Coefficient selection   */
#define ADC_CALR1_CAL10_0           (0x1UL << ADC_CALR1_CAL10_Pos)      /*!< 0x00000100                                         */
#define ADC_CALR1_CAL10_1           (0x2UL << ADC_CALR1_CAL10_Pos)      /*!< 0x00000200                                         */
#define ADC_CALR1_CAL9_Pos          (4U)
#define ADC_CALR1_CAL9_Msk          (0x3UL << ADC_CALR1_CAL9_Pos)       /*!< 0x38000030                                         */
#define ADC_CALR1_CAL9              ADC_CALR1_CAL9_Msk                  /*!< ADC channel 9 Calibration Coefficient selection    */
#define ADC_CALR1_CAL9_0            (0x1UL << ADC_CALR1_CAL9_Pos)       /*!< 0x00000010                                         */
#define ADC_CALR1_CAL9_1            (0x2UL << ADC_CALR1_CAL9_Pos)       /*!< 0x00000020                                         */
#define ADC_CALR1_CAL8_Pos          (0U)
#define ADC_CALR1_CAL8_Msk          (0x3UL << ADC_CALR1_CAL8_Pos)       /*!< 0x00000003                                         */
#define ADC_CALR1_CAL8              ADC_CALR1_CAL8_Msk                  /*!< ADC channel 8 Calibration Coefficient selection    */
#define ADC_CALR1_CAL8_0            (0x1UL << ADC_CALR1_CAL8_Pos)       /*!< 0x00000001                                         */
#define ADC_CALR1_CAL8_1            (0x2UL << ADC_CALR1_CAL8_Pos)       /*!< 0x00000002                                         */

/********************  Bit definition for ADC_SQR0 register  ******************/
#define ADC_SQR0_SQ8_Pos            (28U)
#define ADC_SQR0_SQ8_Msk            (0xFUL << ADC_SQR0_SQ8_Pos)         /*!< 0xF0000000                                         */
#define ADC_SQR0_SQ8                ADC_SQR0_SQ8_Msk                    /*!< ADC group regular sequencer rank 8                 */
#define ADC_SQR0_SQ8_0              (0x1UL << ADC_SQR0_SQ8_Pos)         /*!< 0x10000000                                         */
#define ADC_SQR0_SQ8_1              (0x2UL << ADC_SQR0_SQ8_Pos)         /*!< 0x20000000                                         */
#define ADC_SQR0_SQ8_2              (0x4UL << ADC_SQR0_SQ8_Pos)         /*!< 0x40000000                                         */
#define ADC_SQR0_SQ8_3              (0x8UL << ADC_SQR0_SQ8_Pos)         /*!< 0x80000000                                         */
#define ADC_SQR0_SQ7_Pos            (24U)
#define ADC_SQR0_SQ7_Msk            (0xFUL << ADC_SQR0_SQ7_Pos)         /*!< 0x0F000000                                         */
#define ADC_SQR0_SQ7                ADC_SQR0_SQ7_Msk                    /*!< ADC group regular sequencer rank 7                 */
#define ADC_SQR0_SQ7_0              (0x1UL << ADC_SQR0_SQ7_Pos)         /*!< 0x01000000                                         */
#define ADC_SQR0_SQ7_1              (0x2UL << ADC_SQR0_SQ7_Pos)         /*!< 0x02000000                                         */
#define ADC_SQR0_SQ7_2              (0x4UL << ADC_SQR0_SQ7_Pos)         /*!< 0x04000000                                         */
#define ADC_SQR0_SQ7_3              (0x8UL << ADC_SQR0_SQ7_Pos)         /*!< 0x08000000                                         */
#define ADC_SQR0_SQ6_Pos            (20U)
#define ADC_SQR0_SQ6_Msk            (0xFUL << ADC_SQR0_SQ6_Pos)         /*!< 0x00F00000                                         */
#define ADC_SQR0_SQ6                ADC_SQR0_SQ6_Msk                    /*!< ADC group regular sequencer rank 6                 */
#define ADC_SQR0_SQ6_0              (0x1UL << ADC_SQR0_SQ6_Pos)         /*!< 0x00100000                                         */
#define ADC_SQR0_SQ6_1              (0x2UL << ADC_SQR0_SQ6_Pos)         /*!< 0x00200000                                         */
#define ADC_SQR0_SQ6_2              (0x4UL << ADC_SQR0_SQ6_Pos)         /*!< 0x00400000                                         */
#define ADC_SQR0_SQ6_3              (0x8UL << ADC_SQR0_SQ6_Pos)         /*!< 0x00800000                                         */
#define ADC_SQR0_SQ5_Pos            (16U)
#define ADC_SQR0_SQ5_Msk            (0xFUL << ADC_SQR0_SQ5_Pos)         /*!< 0x000F0000                                         */
#define ADC_SQR0_SQ5                ADC_SQR0_SQ5_Msk                    /*!< ADC group regular sequencer rank 5                 */
#define ADC_SQR0_SQ5_0              (0x1UL << ADC_SQR0_SQ5_Pos)         /*!< 0x00010000                                         */
#define ADC_SQR0_SQ5_1              (0x2UL << ADC_SQR0_SQ5_Pos)         /*!< 0x00020000                                         */
#define ADC_SQR0_SQ5_2              (0x4UL << ADC_SQR0_SQ5_Pos)         /*!< 0x00040000                                         */
#define ADC_SQR0_SQ5_3              (0x8UL << ADC_SQR0_SQ5_Pos)         /*!< 0x00080000                                         */
#define ADC_SQR0_SQ4_Pos            (12U)
#define ADC_SQR0_SQ4_Msk            (0xFUL << ADC_SQR0_SQ4_Pos)         /*!< 0x0000F000                                         */
#define ADC_SQR0_SQ4                ADC_SQR0_SQ4_Msk                    /*!< ADC group regular sequencer rank 4                 */
#define ADC_SQR0_SQ4_0              (0x1UL << ADC_SQR0_SQ4_Pos)         /*!< 0x00001000                                         */
#define ADC_SQR0_SQ4_1              (0x2UL << ADC_SQR0_SQ4_Pos)         /*!< 0x00002000                                         */
#define ADC_SQR0_SQ4_2              (0x4UL << ADC_SQR0_SQ4_Pos)         /*!< 0x00004000                                         */
#define ADC_SQR0_SQ4_3              (0x8UL << ADC_SQR0_SQ4_Pos)         /*!< 0x00008000                                         */
#define ADC_SQR0_SQ3_Pos            (8U)
#define ADC_SQR0_SQ3_Msk            (0xFUL << ADC_SQR0_SQ3_Pos)         /*!< 0x00000F00                                         */
#define ADC_SQR0_SQ3                ADC_SQR0_SQ3_Msk                    /*!< ADC group regular sequencer rank 3                 */
#define ADC_SQR0_SQ3_0              (0x1UL << ADC_SQR0_SQ3_Pos)         /*!< 0x00000100                                         */
#define ADC_SQR0_SQ3_1              (0x2UL << ADC_SQR0_SQ3_Pos)         /*!< 0x00000200                                         */
#define ADC_SQR0_SQ3_2              (0x4UL << ADC_SQR0_SQ3_Pos)         /*!< 0x00000400                                         */
#define ADC_SQR0_SQ3_3              (0x8UL << ADC_SQR0_SQ3_Pos)         /*!< 0x00000800                                         */
#define ADC_SQR0_SQ2_Pos            (4U)
#define ADC_SQR0_SQ2_Msk            (0xFUL << ADC_SQR0_SQ2_Pos)         /*!< 0x000000F0                                         */
#define ADC_SQR0_SQ2                ADC_SQR0_SQ2_Msk                    /*!< ADC group regular sequencer rank 2                 */
#define ADC_SQR0_SQ2_0              (0x1UL << ADC_SQR0_SQ2_Pos)         /*!< 0x00000010                                         */
#define ADC_SQR0_SQ2_1              (0x2UL << ADC_SQR0_SQ2_Pos)         /*!< 0x00000020                                         */
#define ADC_SQR0_SQ2_2              (0x4UL << ADC_SQR0_SQ2_Pos)         /*!< 0x00000040                                         */
#define ADC_SQR0_SQ2_3              (0x8UL << ADC_SQR0_SQ2_Pos)         /*!< 0x00000080                                         */
#define ADC_SQR0_SQ1_Pos            (0U)
#define ADC_SQR0_SQ1_Msk            (0xFUL << ADC_SQR0_SQ1_Pos)         /*!< 0x0000000F                                         */
#define ADC_SQR0_SQ1                ADC_SQR0_SQ1_Msk                    /*!< ADC group regular sequencer rank 1                 */
#define ADC_SQR0_SQ1_0              (0x1UL << ADC_SQR0_SQ1_Pos)         /*!< 0x00000001                                         */
#define ADC_SQR0_SQ1_1              (0x2UL << ADC_SQR0_SQ1_Pos)         /*!< 0x00000002                                         */
#define ADC_SQR0_SQ1_2              (0x4UL << ADC_SQR0_SQ1_Pos)         /*!< 0x00000004                                         */
#define ADC_SQR0_SQ1_3              (0x8UL << ADC_SQR0_SQ1_Pos)         /*!< 0x00000008                                         */

/********************  Bit definition for ADC_SQR1 register  ******************/
#define ADC_SQR1_SQ16_Pos           (28U)
#define ADC_SQR1_SQ16_Msk           (0xFUL << ADC_SQR1_SQ16_Pos)        /*!< 0xF0000000                                         */
#define ADC_SQR1_SQ16               ADC_SQR1_SQ16_Msk                   /*!< ADC group regular sequencer rank 16                */
#define ADC_SQR1_SQ16_0             (0x1UL << ADC_SQR1_SQ16_Pos)        /*!< 0x10000000                                         */
#define ADC_SQR1_SQ16_1             (0x2UL << ADC_SQR1_SQ16_Pos)        /*!< 0x20000000                                         */
#define ADC_SQR1_SQ16_2             (0x4UL << ADC_SQR1_SQ16_Pos)        /*!< 0x40000000                                         */
#define ADC_SQR1_SQ16_3             (0x8UL << ADC_SQR1_SQ16_Pos)        /*!< 0x80000000                                         */
#define ADC_SQR1_SQ15_Pos           (24U)
#define ADC_SQR1_SQ15_Msk           (0xFUL << ADC_SQR1_SQ15_Pos)        /*!< 0x0F000000                                         */
#define ADC_SQR1_SQ15               ADC_SQR1_SQ15_Msk                   /*!< ADC group regular sequencer rank 15                */
#define ADC_SQR1_SQ15_0             (0x1UL << ADC_SQR1_SQ15_Pos)        /*!< 0x01000000                                         */
#define ADC_SQR1_SQ15_1             (0x2UL << ADC_SQR1_SQ15_Pos)        /*!< 0x02000000                                         */
#define ADC_SQR1_SQ15_2             (0x4UL << ADC_SQR1_SQ15_Pos)        /*!< 0x04000000                                         */
#define ADC_SQR1_SQ15_3             (0x8UL << ADC_SQR1_SQ15_Pos)        /*!< 0x08000000                                         */
#define ADC_SQR1_SQ14_Pos           (20U)
#define ADC_SQR1_SQ14_Msk           (0xFUL << ADC_SQR1_SQ14_Pos)        /*!< 0x00F00000                                         */
#define ADC_SQR1_SQ14               ADC_SQR1_SQ14_Msk                   /*!< ADC group regular sequencer rank 14                */
#define ADC_SQR1_SQ14_0             (0x1UL << ADC_SQR1_SQ14_Pos)        /*!< 0x00100000                                         */
#define ADC_SQR1_SQ14_1             (0x2UL << ADC_SQR1_SQ14_Pos)        /*!< 0x00200000                                         */
#define ADC_SQR1_SQ14_2             (0x4UL << ADC_SQR1_SQ14_Pos)        /*!< 0x00400000                                         */
#define ADC_SQR1_SQ14_3             (0x8UL << ADC_SQR1_SQ14_Pos)        /*!< 0x00800000                                         */
#define ADC_SQR1_SQ13_Pos           (16U)
#define ADC_SQR1_SQ13_Msk           (0xFUL << ADC_SQR1_SQ13_Pos)        /*!< 0x000F0000                                         */
#define ADC_SQR1_SQ13               ADC_SQR1_SQ13_Msk                   /*!< ADC group regular sequencer rank 13                */
#define ADC_SQR1_SQ13_0             (0x1UL << ADC_SQR1_SQ13_Pos)        /*!< 0x00010000                                         */
#define ADC_SQR1_SQ13_1             (0x2UL << ADC_SQR1_SQ13_Pos)        /*!< 0x00020000                                         */
#define ADC_SQR1_SQ13_2             (0x4UL << ADC_SQR1_SQ13_Pos)        /*!< 0x00040000                                         */
#define ADC_SQR1_SQ13_3             (0x8UL << ADC_SQR1_SQ13_Pos)        /*!< 0x00080000                                         */
#define ADC_SQR1_SQ12_Pos           (12U)
#define ADC_SQR1_SQ12_Msk           (0xFUL << ADC_SQR1_SQ12_Pos)        /*!< 0x0000F000                                         */
#define ADC_SQR1_SQ12               ADC_SQR1_SQ12_Msk                   /*!< ADC group regular sequencer rank 12                */
#define ADC_SQR1_SQ12_0             (0x1UL << ADC_SQR1_SQ12_Pos)        /*!< 0x00001000                                         */
#define ADC_SQR1_SQ12_1             (0x2UL << ADC_SQR1_SQ12_Pos)        /*!< 0x00002000                                         */
#define ADC_SQR1_SQ12_2             (0x4UL << ADC_SQR1_SQ12_Pos)        /*!< 0x00004000                                         */
#define ADC_SQR1_SQ12_3             (0x8UL << ADC_SQR1_SQ12_Pos)        /*!< 0x00008000                                         */
#define ADC_SQR1_SQ11_Pos           (8U)
#define ADC_SQR1_SQ11_Msk           (0xFUL << ADC_SQR1_SQ11_Pos)        /*!< 0x00000F00                                         */
#define ADC_SQR1_SQ11               ADC_SQR1_SQ11_Msk                   /*!< ADC group regular sequencer rank 11                */
#define ADC_SQR1_SQ11_0             (0x1UL << ADC_SQR1_SQ11_Pos)        /*!< 0x00000100                                         */
#define ADC_SQR1_SQ11_1             (0x2UL << ADC_SQR1_SQ11_Pos)        /*!< 0x00000200                                         */
#define ADC_SQR1_SQ11_2             (0x4UL << ADC_SQR1_SQ11_Pos)        /*!< 0x00000400                                         */
#define ADC_SQR1_SQ11_3             (0x8UL << ADC_SQR1_SQ11_Pos)        /*!< 0x00000800                                         */
#define ADC_SQR1_SQ10_Pos           (4U)
#define ADC_SQR1_SQ10_Msk           (0xFUL << ADC_SQR1_SQ10_Pos)        /*!< 0x000000F0                                         */
#define ADC_SQR1_SQ10               ADC_SQR1_SQ10_Msk                   /*!< ADC group regular sequencer rank 10                */
#define ADC_SQR1_SQ10_0             (0x1UL << ADC_SQR1_SQ10_Pos)        /*!< 0x00000010                                         */
#define ADC_SQR1_SQ10_1             (0x2UL << ADC_SQR1_SQ10_Pos)        /*!< 0x00000020                                         */
#define ADC_SQR1_SQ10_2             (0x4UL << ADC_SQR1_SQ10_Pos)        /*!< 0x00000040                                         */
#define ADC_SQR1_SQ10_3             (0x8UL << ADC_SQR1_SQ10_Pos)        /*!< 0x00000080                                         */
#define ADC_SQR1_SQ9_Pos            (0U)
#define ADC_SQR1_SQ9_Msk            (0xFUL << ADC_SQR1_SQ9_Pos)         /*!< 0x0000000F                                         */
#define ADC_SQR1_SQ9                ADC_SQR1_SQ9_Msk                    /*!< ADC group regular sequencer rank 9                 */
#define ADC_SQR1_SQ9_0              (0x1UL << ADC_SQR1_SQ9_Pos)         /*!< 0x00000001                                         */
#define ADC_SQR1_SQ9_1              (0x2UL << ADC_SQR1_SQ9_Pos)         /*!< 0x00000002                                         */
#define ADC_SQR1_SQ9_2              (0x4UL << ADC_SQR1_SQ9_Pos)         /*!< 0x00000004                                         */
#define ADC_SQR1_SQ9_3              (0x8UL << ADC_SQR1_SQ9_Pos)         /*!< 0x00000008                                         */

/********************  Bit definition for ADC_LR register  ********************/
#define ADC_LR_LEN_Pos              (8U)
#define ADC_LR_LEN_Msk              (0xFUL << ADC_LR_LEN_Pos)           /*!< 0x00000F00                                         */
#define ADC_LR_LEN                  ADC_LR_LEN_Msk                      /*!< ADC group regular sequencer scan length            */
#define ADC_LR_LEN_0                (0x1UL << ADC_LR_LEN_Pos)           /*!< 0x00000100                                         */
#define ADC_LR_LEN_1                (0x2UL << ADC_LR_LEN_Pos)           /*!< 0x00000200                                         */
#define ADC_LR_LEN_2                (0x4UL << ADC_LR_LEN_Pos)           /*!< 0x00000400                                         */
#define ADC_LR_LEN_3                (0x8UL << ADC_LR_LEN_Pos)           /*!< 0x00000800                                         */
#define ADC_LR_EXTEN_Pos            (5U)
#define ADC_LR_EXTEN_Msk            (0x3UL << ADC_LR_EXTEN_Pos)         /*!< 0x00000060                                         */
#define ADC_LR_EXTEN                ADC_LR_EXTEN_Msk                    /*!< ADC group regular external trigger polarity        */
#define ADC_LR_EXTEN_0              (0x1UL << ADC_LR_EXTEN_Pos)         /*!< 0x00000020                                         */
#define ADC_LR_EXTEN_1              (0x2UL << ADC_LR_EXTEN_Pos)         /*!< 0x00000040                                         */
#define ADC_LR_EXTSEL_Pos           (0U)
#define ADC_LR_EXTSEL_Msk           (0x1FUL << ADC_LR_EXTSEL_Pos)       /*!< 0x0000001F                                         */
#define ADC_LR_EXTSEL               ADC_LR_EXTSEL_Msk                   /*!< ADC group regular external trigger source          */
#define ADC_LR_EXTSEL_0             (0x1UL << ADC_LR_EXTSEL_Pos)        /*!< 0x00000001                                         */
#define ADC_LR_EXTSEL_1             (0x2UL << ADC_LR_EXTSEL_Pos)        /*!< 0x00000002                                         */
#define ADC_LR_EXTSEL_2             (0x4UL << ADC_LR_EXTSEL_Pos)        /*!< 0x00000004                                         */
#define ADC_LR_EXTSEL_3             (0x8UL << ADC_LR_EXTSEL_Pos)        /*!< 0x00000008                                         */
#define ADC_LR_EXTSEL_4             (0x10UL << ADC_LR_EXTSEL_Pos)       /*!< 0x00000010                                         */

/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_RDATA_Pos            (0U)
#define ADC_DR_RDATA_Msk            (0xFFFFUL << ADC_DR_RDATA_Pos)      /*!< 0x0000FFFF                                         */
#define ADC_DR_RDATA                ADC_DR_RDATA_Msk                    /*!< ADC group regular conversion data                  */

/********************  Bit definition for ADC_JSQR register  ******************/
#define ADC_JSQR_JSQ4_Pos           (12U)
#define ADC_JSQR_JSQ4_Msk           (0xFUL << ADC_JSQR_JSQ4_Pos)        /*!< 0x0000F000                                         */
#define ADC_JSQR_JSQ4               ADC_JSQR_JSQ4_Msk                   /*!< ADC group injected sequencer rank 4                */
#define ADC_JSQR_JSQ4_0             (0x1UL << ADC_JSQR_JSQ4_Pos)        /*!< 0x00001000                                         */
#define ADC_JSQR_JSQ4_1             (0x2UL << ADC_JSQR_JSQ4_Pos)        /*!< 0x00002000                                         */
#define ADC_JSQR_JSQ4_2             (0x4UL << ADC_JSQR_JSQ4_Pos)        /*!< 0x00004000                                         */
#define ADC_JSQR_JSQ4_3             (0x8UL << ADC_JSQR_JSQ4_Pos)        /*!< 0x00008000                                         */
#define ADC_JSQR_JSQ3_Pos           (8U)
#define ADC_JSQR_JSQ3_Msk           (0xFUL << ADC_JSQR_JSQ3_Pos)        /*!< 0x00000F00                                         */
#define ADC_JSQR_JSQ3               ADC_JSQR_JSQ3_Msk                   /*!< ADC group injected sequencer rank 3                */
#define ADC_JSQR_JSQ3_0             (0x1UL << ADC_JSQR_JSQ3_Pos)        /*!< 0x00000100                                         */
#define ADC_JSQR_JSQ3_1             (0x2UL << ADC_JSQR_JSQ3_Pos)        /*!< 0x00000200                                         */
#define ADC_JSQR_JSQ3_2             (0x4UL << ADC_JSQR_JSQ3_Pos)        /*!< 0x00000400                                         */
#define ADC_JSQR_JSQ3_3             (0x8UL << ADC_JSQR_JSQ3_Pos)        /*!< 0x00000800                                         */
#define ADC_JSQR_JSQ2_Pos           (4U)
#define ADC_JSQR_JSQ2_Msk           (0xFUL << ADC_JSQR_JSQ2_Pos)        /*!< 0x000000F0                                         */
#define ADC_JSQR_JSQ2               ADC_JSQR_JSQ2_Msk                   /*!< ADC group injected sequencer rank 2                */
#define ADC_JSQR_JSQ2_0             (0x1UL << ADC_JSQR_JSQ2_Pos)        /*!< 0x00000010                                         */
#define ADC_JSQR_JSQ2_1             (0x2UL << ADC_JSQR_JSQ2_Pos)        /*!< 0x00000020                                         */
#define ADC_JSQR_JSQ2_2             (0x4UL << ADC_JSQR_JSQ2_Pos)        /*!< 0x00000040                                         */
#define ADC_JSQR_JSQ2_3             (0x8UL << ADC_JSQR_JSQ2_Pos)        /*!< 0x00000080                                         */
#define ADC_JSQR_JSQ1_Pos           (0U)
#define ADC_JSQR_JSQ1_Msk           (0xFUL << ADC_JSQR_JSQ1_Pos)        /*!< 0x0000000F                                         */
#define ADC_JSQR_JSQ1               ADC_JSQR_JSQ1_Msk                   /*!< ADC group injected sequencer rank 1                */
#define ADC_JSQR_JSQ1_0             (0x1UL << ADC_JSQR_JSQ1_Pos)        /*!< 0x00000001                                         */
#define ADC_JSQR_JSQ1_1             (0x2UL << ADC_JSQR_JSQ1_Pos)        /*!< 0x00000002                                         */
#define ADC_JSQR_JSQ1_2             (0x4UL << ADC_JSQR_JSQ1_Pos)        /*!< 0x00000004                                         */
#define ADC_JSQR_JSQ1_3             (0x8UL << ADC_JSQR_JSQ1_Pos)        /*!< 0x00000008                                         */

/********************  Bit definition for ADC_JLR register  *******************/
#define ADC_JLR_JLEN_Pos            (8U)
#define ADC_JLR_JLEN_Msk            (0x3UL << ADC_JLR_JLEN_Pos)         /*!< 0x00000300                                         */
#define ADC_JLR_JLEN                ADC_JLR_JLEN_Msk                    /*!< ADC group injected sequencer scan length           */
#define ADC_JLR_JLEN_0              (0x1UL << ADC_JLR_JLEN_Pos)         /*!< 0x00000100                                         */
#define ADC_JLR_JLEN_1              (0x2UL << ADC_JLR_JLEN_Pos)         /*!< 0x00000200                                         */
#define ADC_JLR_JEXTEN_Pos          (5U)
#define ADC_JLR_JEXTEN_Msk          (0x3UL << ADC_JLR_JEXTEN_Pos)       /*!< 0x00000060                                         */
#define ADC_JLR_JEXTEN              ADC_JLR_JEXTEN_Msk                  /*!< ADC group injected external trigger polarity       */
#define ADC_JLR_JEXTEN_0            (0x1UL << ADC_JLR_JEXTEN_Pos)       /*!< 0x00000020                                         */
#define ADC_JLR_JEXTEN_1            (0x2UL << ADC_JLR_JEXTEN_Pos)       /*!< 0x00000040                                         */
#define ADC_JLR_JEXTSEL_Pos         (0U)
#define ADC_JLR_JEXTSEL_Msk         (0x1FUL << ADC_JLR_JEXTSEL_Pos)     /*!< 0x0000001F                                         */
#define ADC_JLR_JEXTSEL             ADC_JLR_JEXTSEL_Msk                 /*!< ADC group injected external trigger source         */
#define ADC_JLR_JEXTSEL_0           (0x1UL << ADC_JLR_JEXTSEL_Pos)      /*!< 0x00000001                                         */
#define ADC_JLR_JEXTSEL_1           (0x2UL << ADC_JLR_JEXTSEL_Pos)      /*!< 0x00000002                                         */
#define ADC_JLR_JEXTSEL_2           (0x4UL << ADC_JLR_JEXTSEL_Pos)      /*!< 0x00000004                                         */
#define ADC_JLR_JEXTSEL_3           (0x8UL << ADC_JLR_JEXTSEL_Pos)      /*!< 0x00000008                                         */
#define ADC_JLR_JEXTSEL_4           (0x10UL << ADC_JLR_JEXTSEL_Pos)     /*!< 0x00000010                                         */

/********************  Bit definition for ADC_JDR0 register  ******************/
#define ADC_JDR0_JDATA_Pos          (0U)
#define ADC_JDR0_JDATA_Msk          (0xFFFFUL << ADC_JDR0_JDATA_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_JDR0_JDATA              ADC_JDR0_JDATA_Msk                  /*!< ADC group injected sequencer rank 4 conversion data*/

/********************  Bit definition for ADC_JDR1 register  ******************/
#define ADC_JDR1_JDATA_Pos          (0U)
#define ADC_JDR1_JDATA_Msk          (0xFFFFUL << ADC_JDR1_JDATA_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_JDR1_JDATA              ADC_JDR1_JDATA_Msk                  /*!< ADC group injected sequencer rank 1 conversion data*/

/********************  Bit definition for ADC_JDR2 register  ******************/
#define ADC_JDR2_JDATA_Pos          (0U)
#define ADC_JDR2_JDATA_Msk          (0xFFFFUL << ADC_JDR2_JDATA_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_JDR2_JDATA              ADC_JDR2_JDATA_Msk                  /*!< ADC group injected sequencer rank 2 conversion data*/

/********************  Bit definition for ADC_JDR3 register  ******************/
#define ADC_JDR3_JDATA_Pos          (0U)
#define ADC_JDR3_JDATA_Msk          (0xFFFFUL << ADC_JDR3_JDATA_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_JDR3_JDATA              ADC_JDR3_JDATA_Msk                  /*!< ADC group injected sequencer rank 3 conversion data*/

/********************  Bit definition for ADC_TR0 register  *******************/
#define ADC_TR0_HT0_Pos             (16U)
#define ADC_TR0_HT0_Msk             (0xFFFFUL << ADC_TR0_HT0_Pos)       /*!< 0xFFFF0000                                         */
#define ADC_TR0_HT0                 ADC_TR0_HT0_Msk                     /*!< ADC analog watchdog 0 threshold high               */

#define ADC_TR0_LT0_Pos             (0U)
#define ADC_TR0_LT0_Msk             (0xFFFFUL << ADC_TR0_LT0_Pos)       /*!< 0x0000FFFF                                         */
#define ADC_TR0_LT0                 ADC_TR0_LT0_Msk                     /*!< ADC analog watchdog 0 threshold low                */

/********************  Bit definition for ADC_TR1 register  *******************/
#define ADC_TR1_HT1_Pos             (16U)
#define ADC_TR1_HT1_Msk             (0xFFFFUL << ADC_TR1_HT1_Pos)       /*!< 0xFFFF0000                                         */
#define ADC_TR1_HT1                 ADC_TR1_HT1_Msk                     /*!< ADC analog watchdog 1 threshold high               */

#define ADC_TR1_LT1_Pos             (0U)
#define ADC_TR1_LT1_Msk             (0xFFFFUL << ADC_TR1_LT1_Pos)       /*!< 0x0000FFFF                                         */
#define ADC_TR1_LT1                 ADC_TR1_LT1_Msk                     /*!< ADC analog watchdog 1 threshold low                */

/********************  Bit definition for ADC_TR2 register  *******************/
#define ADC_TR2_HT2_Pos             (16U)
#define ADC_TR2_HT2_Msk             (0xFFFFUL << ADC_TR2_HT2_Pos)       /*!< 0xFFFF0000                                         */
#define ADC_TR2_HT2                 ADC_TR2_HT2_Msk                     /*!< ADC analog watchdog 2 threshold high               */

#define ADC_TR2_LT2_Pos             (0U)
#define ADC_TR2_LT2_Msk             (0xFFFFUL << ADC_TR2_LT2_Pos)       /*!< 0x0000FFFF                                         */
#define ADC_TR2_LT2                 ADC_TR2_LT2_Msk                     /*!< ADC analog watchdog 2 threshold low                */

/*******************  Bit definition for ADC_AWDCR0 register  *****************/
#define ADC_AWD0CR_AWD0FILT_Pos     (16U)
#define ADC_AWD0CR_AWD0FILT_Msk     (0xFUL << ADC_AWD0CR_AWD0FILT_Pos)  /*!< 0x000F0000                                         */
#define ADC_AWD0CR_AWD0FILT         ADC_AWD0CR_AWD0FILT_Msk             /*!< ADC analog watchdog 0 filtering parameter          */
#define ADC_AWD0CR_AWD0FILT_0       (0x1UL << ADC_AWD0CR_AWD0FILT_Pos)  /*!< 0x00010000                                         */
#define ADC_AWD0CR_AWD0FILT_1       (0x2UL << ADC_AWD0CR_AWD0FILT_Pos)  /*!< 0x00020000                                         */
#define ADC_AWD0CR_AWD0FILT_2       (0x4UL << ADC_AWD0CR_AWD0FILT_Pos)  /*!< 0x00040000                                         */
#define ADC_AWD0CR_AWD0FILT_3       (0x8UL << ADC_AWD0CR_AWD0FILT_Pos)  /*!< 0x00080000                                         */
#define ADC_AWD0CR_AWD0CH_Pos       (0U)
#define ADC_AWD0CR_AWD0CH_Msk       (0xFFFUL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000FFF                                         */
#define ADC_AWD0CR_AWD0CH           ADC_AWD0CR_AWD0CH_Msk               /*!< ADC analog watchdog 0 monitored channel selection  */
#define ADC_AWD0CR_AWD0CH_0         (0x001UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000001                                         */
#define ADC_AWD0CR_AWD0CH_1         (0x002UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000002                                         */
#define ADC_AWD0CR_AWD0CH_2         (0x004UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000004                                         */
#define ADC_AWD0CR_AWD0CH_3         (0x008UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000008                                         */
#define ADC_AWD0CR_AWD0CH_4         (0x010UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000010                                         */
#define ADC_AWD0CR_AWD0CH_5         (0x020UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000020                                         */
#define ADC_AWD0CR_AWD0CH_6         (0x040UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000040                                         */
#define ADC_AWD0CR_AWD0CH_7         (0x080UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000080                                         */
#define ADC_AWD0CR_AWD0CH_8         (0x100UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000100                                         */
#define ADC_AWD0CR_AWD0CH_9         (0x200UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000200                                         */
#define ADC_AWD0CR_AWD0CH_10        (0x400UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000400                                         */
#define ADC_AWD0CR_AWD0CH_11        (0x800UL << ADC_AWD0CR_AWD0CH_Pos)  /*!< 0x00000800                                         */

/*******************  Bit definition for ADC_AWDCR1 register  *****************/
#define ADC_AWD1CR_AWD1FILT_Pos     (16U)
#define ADC_AWD1CR_AWD1FILT_Msk     (0xFUL << ADC_AWD1CR_AWD1FILT_Pos)  /*!< 0x000F0000                                         */
#define ADC_AWD1CR_AWD1FILT         ADC_AWD1CR_AWD1FILT_Msk             /*!< ADC analog watchdog 1 filtering parameter          */
#define ADC_AWD1CR_AWD1FILT_0       (0x1UL << ADC_AWD1CR_AWD1FILT_Pos)  /*!< 0x00010000                                         */
#define ADC_AWD1CR_AWD1FILT_1       (0x2UL << ADC_AWD1CR_AWD1FILT_Pos)  /*!< 0x00020000                                         */
#define ADC_AWD1CR_AWD1FILT_2       (0x4UL << ADC_AWD1CR_AWD1FILT_Pos)  /*!< 0x00040000                                         */
#define ADC_AWD1CR_AWD1FILT_3       (0x8UL << ADC_AWD1CR_AWD1FILT_Pos)  /*!< 0x00080000                                         */
#define ADC_AWD1CR_AWD1CH_Pos       (0U)
#define ADC_AWD1CR_AWD1CH_Msk       (0xFFFUL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000FFF                                         */
#define ADC_AWD1CR_AWD1CH           ADC_AWD1CR_AWD1CH_Msk               /*!< ADC analog watchdog 1 monitored channel selection  */
#define ADC_AWD1CR_AWD1CH_0         (0x001UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000001                                         */
#define ADC_AWD1CR_AWD1CH_1         (0x002UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000002                                         */
#define ADC_AWD1CR_AWD1CH_2         (0x004UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000004                                         */
#define ADC_AWD1CR_AWD1CH_3         (0x008UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000008                                         */
#define ADC_AWD1CR_AWD1CH_4         (0x010UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000010                                         */
#define ADC_AWD1CR_AWD1CH_5         (0x020UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000020                                         */
#define ADC_AWD1CR_AWD1CH_6         (0x040UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000040                                         */
#define ADC_AWD1CR_AWD1CH_7         (0x080UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000080                                         */
#define ADC_AWD1CR_AWD1CH_8         (0x100UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000100                                         */
#define ADC_AWD1CR_AWD1CH_9         (0x200UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000200                                         */
#define ADC_AWD1CR_AWD1CH_10        (0x400UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000400                                         */
#define ADC_AWD1CR_AWD1CH_11        (0x800UL << ADC_AWD1CR_AWD1CH_Pos)  /*!< 0x00000800                                         */

/*******************  Bit definition for ADC_AWDCR2 register  *****************/
#define ADC_AWD2CR_AWD2FILT_Pos     (16U)
#define ADC_AWD2CR_AWD2FILT_Msk     (0xFUL << ADC_AWD2CR_AWD2FILT_Pos)  /*!< 0x000F0000                                         */
#define ADC_AWD2CR_AWD2FILT         ADC_AWD2CR_AWD2FILT_Msk             /*!< ADC analog watchdog 2 filtering parameter          */
#define ADC_AWD2CR_AWD2FILT_0       (0x1UL << ADC_AWD2CR_AWD2FILT_Pos)  /*!< 0x00010000                                         */
#define ADC_AWD2CR_AWD2FILT_1       (0x2UL << ADC_AWD2CR_AWD2FILT_Pos)  /*!< 0x00020000                                         */
#define ADC_AWD2CR_AWD2FILT_2       (0x4UL << ADC_AWD2CR_AWD2FILT_Pos)  /*!< 0x00040000                                         */
#define ADC_AWD2CR_AWD2FILT_3       (0x8UL << ADC_AWD2CR_AWD2FILT_Pos)  /*!< 0x00080000                                         */
#define ADC_AWD2CR_AWD2CH_Pos       (0U)
#define ADC_AWD2CR_AWD2CH_Msk       (0xFFFUL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000FFF                                         */
#define ADC_AWD2CR_AWD2CH           ADC_AWD2CR_AWD2CH_Msk               /*!< ADC analog watchdog 2 monitored channel selection  */
#define ADC_AWD2CR_AWD2CH_0         (0x001UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000001                                         */
#define ADC_AWD2CR_AWD2CH_1         (0x002UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000002                                         */
#define ADC_AWD2CR_AWD2CH_2         (0x004UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000004                                         */
#define ADC_AWD2CR_AWD2CH_3         (0x008UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000008                                         */
#define ADC_AWD2CR_AWD2CH_4         (0x010UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000010                                         */
#define ADC_AWD2CR_AWD2CH_5         (0x020UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000020                                         */
#define ADC_AWD2CR_AWD2CH_6         (0x040UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000040                                         */
#define ADC_AWD2CR_AWD2CH_7         (0x080UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000080                                         */
#define ADC_AWD2CR_AWD2CH_8         (0x100UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000100                                         */
#define ADC_AWD2CR_AWD2CH_9         (0x200UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000200                                         */
#define ADC_AWD2CR_AWD2CH_10        (0x400UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000400                                         */
#define ADC_AWD2CR_AWD2CH_11        (0x800UL << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000800                                         */

/********************  Bit definition for ADC_OFR0 register  ******************/
#define ADC_OFR0_OFFSET_Pos         (0U)
#define ADC_OFR0_OFFSET_Msk         (0xFFFFUL << ADC_OFR0_OFFSET_Pos)   /*!< 0x0000FFFF                                         */
#define ADC_OFR0_OFFSET             ADC_OFR0_OFFSET_Msk                 /*!< ADC Single-End offset number 0 offset level        */

/********************  Bit definition for ADC_OFR1 register  ******************/
#define ADC_OFR1_OFFSET_Pos         (0U)
#define ADC_OFR1_OFFSET_Msk         (0xFFFFUL << ADC_OFR1_OFFSET_Pos)   /*!< 0x0000FFFF                                         */
#define ADC_OFR1_OFFSET             ADC_OFR1_OFFSET_Msk                 /*!< ADC Single-End offset number 1 offset level        */

/********************  Bit definition for ADC_OFR2 register  ******************/
#define ADC_OFR2_OFFSET_Pos         (0U)
#define ADC_OFR2_OFFSET_Msk         (0xFFFFUL << ADC_OFR2_OFFSET_Pos)   /*!< 0x0000FFFF                                         */
#define ADC_OFR2_OFFSET             ADC_OFR2_OFFSET_Msk                 /*!< ADC Single-End offset number 2 offset level        */

/********************  Bit definition for ADC_OFR3 register  ******************/
#define ADC_OFR3_OFFSET_Pos         (0U)
#define ADC_OFR3_OFFSET_Msk         (0xFFFFUL << ADC_OFR3_OFFSET_Pos)   /*!< 0x0000FFFF                                         */
#define ADC_OFR3_OFFSET             ADC_OFR3_OFFSET_Msk                 /*!< ADC Single-End offset number 3 offset level        */

/*******************  Bit definition for ADC_DOFR0 register  ******************/
#define ADC_DOFR0_OFFSET_Pos        (0U)
#define ADC_DOFR0_OFFSET_Msk        (0xFFFFUL << ADC_DOFR0_OFFSET_Pos)  /*!< 0x0000FFFF                                         */
#define ADC_DOFR0_OFFSET            ADC_DOFR0_OFFSET_Msk                /*!< ADC Differential offset number 0 offset level      */

/*******************  Bit definition for ADC_DOFR1 register  ******************/
#define ADC_DOFR1_OFFSET_Pos        (0U)
#define ADC_DOFR1_OFFSET_Msk        (0xFFFFUL << ADC_DOFR1_OFFSET_Pos)  /*!< 0x0000FFFF                                         */
#define ADC_DOFR1_OFFSET            ADC_DOFR1_OFFSET_Msk                /*!< ADC Differential offset number 1 offset level      */

/*******************  Bit definition for ADC_DOFR2 register  ******************/
#define ADC_DOFR2_OFFSET_Pos        (0U)
#define ADC_DOFR2_OFFSET_Msk        (0xFFFFUL << ADC_DOFR2_OFFSET_Pos)  /*!< 0x0000FFFF                                         */
#define ADC_DOFR2_OFFSET            ADC_DOFR2_OFFSET_Msk                /*!< ADC Differential offset number 2 offset level      */

/*******************  Bit definition for ADC_DOFR3 register  ******************/
#define ADC_DOFR3_OFFSET_Pos        (0U)
#define ADC_DOFR3_OFFSET_Msk        (0xFFFFUL << ADC_DOFR3_OFFSET_Pos)  /*!< 0x0000FFFF                                         */
#define ADC_DOFR3_OFFSET            ADC_DOFR3_OFFSET_Msk                /*!< ADC Differential offset number 3 offset level      */

/********************  Bit definition for ADC_GCR0 register  ******************/
#define ADC_GCR0_GAIN_Pos           (0U)
#define ADC_GCR0_GAIN_Msk           (0xFFFFUL << ADC_GCR0_GAIN_Pos)     /*!< 0x0000FFFF                                         */
#define ADC_GCR0_GAIN               ADC_GCR0_GAIN_Msk                   /*!< ADC Single-End gain number 0 gain level            */

/********************  Bit definition for ADC_GCR1 register  ******************/
#define ADC_GCR1_GAIN_Pos           (0U)
#define ADC_GCR1_GAIN_Msk           (0xFFFFUL << ADC_GCR1_GAIN_Pos)     /*!< 0x0000FFFF                                         */
#define ADC_GCR1_GAIN               ADC_GCR1_GAIN_Msk                   /*!< ADC Single-End gain number 1 gain level            */

/********************  Bit definition for ADC_GCR2 register  ******************/
#define ADC_GCR2_GAIN_Pos           (0U)
#define ADC_GCR2_GAIN_Msk           (0xFFFFUL << ADC_GCR2_GAIN_Pos)     /*!< 0x0000FFFF                                         */
#define ADC_GCR2_GAIN               ADC_GCR2_GAIN_Msk                   /*!< ADC Single-End gain number 2 gain level            */

/********************  Bit definition for ADC_GCR3 register  ******************/
#define ADC_GCR3_GAIN_Pos           (0U)
#define ADC_GCR3_GAIN_Msk           (0xFFFFUL << ADC_GCR3_GAIN_Pos)     /*!< 0x0000FFFF                                         */
#define ADC_GCR3_GAIN               ADC_GCR3_GAIN_Msk                   /*!< ADC Single-End gain number 3 gain level            */

/*******************  Bit definition for ADC_DGCR0 register  ******************/
#define ADC_DGCR0_GAIN_Pos          (0U)
#define ADC_DGCR0_GAIN_Msk          (0xFFFFUL << ADC_DGCR0_GAIN_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_DGCR0_GAIN              ADC_DGCR0_GAIN_Msk                  /*!< ADC Differential gain number 0 gain level          */

/*******************  Bit definition for ADC_DGCR1 register  ******************/
#define ADC_DGCR1_GAIN_Pos          (0U)
#define ADC_DGCR1_GAIN_Msk          (0xFFFFUL << ADC_DGCR1_GAIN_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_DGCR1_GAIN              ADC_DGCR1_GAIN_Msk                  /*!< ADC Differential gain number 1 gain level          */

/*******************  Bit definition for ADC_DGCR2 register  ******************/
#define ADC_DGCR2_GAIN_Pos          (0U)
#define ADC_DGCR2_GAIN_Msk          (0xFFFFUL << ADC_DGCR2_GAIN_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_DGCR2_GAIN              ADC_DGCR2_GAIN_Msk                  /*!< ADC Differential gain number 2 gain level          */

/*******************  Bit definition for ADC_DGCR3 register  ******************/
#define ADC_DGCR3_GAIN_Pos          (0U)
#define ADC_DGCR3_GAIN_Msk          (0xFFFFUL << ADC_DGCR3_GAIN_Pos)    /*!< 0x0000FFFF                                         */
#define ADC_DGCR3_GAIN              ADC_DGCR3_GAIN_Msk                  /*!< ADC Differential gain number 3 gain level          */

/********************  Bit definition for ADC_ECR0 register  ******************/
#define ADC_ECR0_ADSRC_Pos          (16U)
#define ADC_ECR0_ADSRC_Msk          (0xFUL << ADC_ECR0_ADSRC_Pos)       /*!< 0x000F0000                                         */
#define ADC_ECR0_ADSRC              ADC_ECR0_ADSRC_Msk                  /*!< ADC To ECU Addr-Data Flag Source Select            */
#define ADC_ECR0_ADSRC_0            (0x1UL << ADC_ECR0_ADSRC_Pos)       /*!< 0x00010000                                         */
#define ADC_ECR0_ADSRC_1            (0x2UL << ADC_ECR0_ADSRC_Pos)       /*!< 0x00020000                                         */
#define ADC_ECR0_ADSRC_2            (0x4UL << ADC_ECR0_ADSRC_Pos)       /*!< 0x00040000                                         */
#define ADC_ECR0_ADSRC_3            (0x8UL << ADC_ECR0_ADSRC_Pos)       /*!< 0x00080000                                         */
#define ADC_ECR0_PSRCU_Pos          (14U)
#define ADC_ECR0_PSRCU_Msk          (0x3UL << ADC_ECR0_PSRCU_Pos)       /*!< 0x0000C000                                         */
#define ADC_ECR0_PSRCU              ADC_ECR0_PSRCU_Msk                  /*!< ADC To ECU Ping-Pong Flag Go Over Zero Src Select  */
#define ADC_ECR0_PSRCU_0            (0x1UL << ADC_ECR0_PSRCU_Pos)       /*!< 0x00004000                                         */
#define ADC_ECR0_PSRCU_1            (0x2UL << ADC_ECR0_PSRCU_Pos)       /*!< 0x00008000                                         */
#define ADC_ECR0_PSRCD_Pos          (12U)
#define ADC_ECR0_PSRCD_Msk          (0x3UL << ADC_ECR0_PSRCD_Pos)       /*!< 0x00003000                                         */
#define ADC_ECR0_PSRCD              ADC_ECR0_PSRCD_Msk                  /*!< ADC To ECU Ping-Pong Flag Dowm Over Zero Src Select*/
#define ADC_ECR0_PSRCD_0            (0x1UL << ADC_ECR0_PSRCD_Pos)       /*!< 0x00001000                                         */
#define ADC_ECR0_PSRCD_1            (0x2UL << ADC_ECR0_PSRCD_Pos)       /*!< 0x00002000                                         */
#define ADC_ECR0_AWD2SEL_Pos        (8U)
#define ADC_ECR0_AWD2SEL_Msk        (0xFUL << ADC_ECR0_AWD2SEL_Pos)     /*!< 0x00000F00                                         */
#define ADC_ECR0_AWD2SEL            ADC_ECR0_AWD2SEL_Msk                /*!< ADC To ECU analog watchdog 2 Source Select         */
#define ADC_ECR0_AWD2SEL_0          (0x1UL << ADC_ECR0_AWD2SEL_Pos)     /*!< 0x00000100                                         */
#define ADC_ECR0_AWD2SEL_1          (0x2UL << ADC_ECR0_AWD2SEL_Pos)     /*!< 0x00000200                                         */
#define ADC_ECR0_AWD2SEL_2          (0x4UL << ADC_ECR0_AWD2SEL_Pos)     /*!< 0x00000400                                         */
#define ADC_ECR0_AWD2SEL_3          (0x8UL << ADC_ECR0_AWD2SEL_Pos)     /*!< 0x00000800                                         */
#define ADC_ECR0_AWD1SEL_Pos        (4U)
#define ADC_ECR0_AWD1SEL_Msk        (0xFUL << ADC_ECR0_AWD1SEL_Pos)     /*!< 0x000000F0                                         */
#define ADC_ECR0_AWD1SEL            ADC_ECR0_AWD1SEL_Msk                /*!< ADC To ECU analog watchdog 1 Source Select         */
#define ADC_ECR0_AWD1SEL_0          (0x1UL << ADC_ECR0_AWD1SEL_Pos)     /*!< 0x00000010                                         */
#define ADC_ECR0_AWD1SEL_1          (0x2UL << ADC_ECR0_AWD1SEL_Pos)     /*!< 0x00000020                                         */
#define ADC_ECR0_AWD1SEL_2          (0x4UL << ADC_ECR0_AWD1SEL_Pos)     /*!< 0x00000040                                         */
#define ADC_ECR0_AWD1SEL_3          (0x8UL << ADC_ECR0_AWD1SEL_Pos)     /*!< 0x00000080                                         */
#define ADC_ECR0_AWD0SEL_Pos        (0U)
#define ADC_ECR0_AWD0SEL_Msk        (0xFUL << ADC_ECR0_AWD0SEL_Pos)     /*!< 0x0000000F                                         */
#define ADC_ECR0_AWD0SEL            ADC_ECR0_AWD0SEL_Msk                /*!< ADC To ECU analog watchdog 0 Source Select         */
#define ADC_ECR0_AWD0SEL_0          (0x1UL << ADC_ECR0_AWD0SEL_Pos)     /*!< 0x00000001                                         */
#define ADC_ECR0_AWD0SEL_1          (0x2UL << ADC_ECR0_AWD0SEL_Pos)     /*!< 0x00000002                                         */
#define ADC_ECR0_AWD0SEL_2          (0x4UL << ADC_ECR0_AWD0SEL_Pos)     /*!< 0x00000004                                         */
#define ADC_ECR0_AWD0SEL_3          (0x8UL << ADC_ECR0_AWD0SEL_Pos)     /*!< 0x00000008                                         */

/********************  Bit definition for ADC_ECR1 register  ******************/
#define ADC_ECR1_ADSRC_Pos          (16U)
#define ADC_ECR1_ADSRC_Msk          (0xFUL << ADC_ECR1_ADSRC_Pos)       /*!< 0x000F0000                                         */
#define ADC_ECR1_ADSRC              ADC_ECR1_ADSRC_Msk                  /*!< ADC To ECU Addr-Data Flag Source Select            */
#define ADC_ECR1_ADSRC_0            (0x1UL << ADC_ECR1_ADSRC_Pos)       /*!< 0x00010000                                         */
#define ADC_ECR1_ADSRC_1            (0x2UL << ADC_ECR1_ADSRC_Pos)       /*!< 0x00020000                                         */
#define ADC_ECR1_ADSRC_2            (0x4UL << ADC_ECR1_ADSRC_Pos)       /*!< 0x00040000                                         */
#define ADC_ECR1_ADSRC_3            (0x8UL << ADC_ECR1_ADSRC_Pos)       /*!< 0x00080000                                         */
#define ADC_ECR1_PSRCU_Pos          (14U)
#define ADC_ECR1_PSRCU_Msk          (0x3UL << ADC_ECR1_PSRCU_Pos)       /*!< 0x0000C000                                         */
#define ADC_ECR1_PSRCU              ADC_ECR1_PSRCU_Msk                  /*!< ADC To ECU Ping-Pong Flag Go Over Zero Src Select  */
#define ADC_ECR1_PSRCU_0            (0x1UL << ADC_ECR1_PSRCU_Pos)       /*!< 0x00004000                                         */
#define ADC_ECR1_PSRCU_1            (0x2UL << ADC_ECR1_PSRCU_Pos)       /*!< 0x00008000                                         */
#define ADC_ECR1_PSRCD_Pos          (12U)
#define ADC_ECR1_PSRCD_Msk          (0x3UL << ADC_ECR1_PSRCD_Pos)       /*!< 0x00003000                                         */
#define ADC_ECR1_PSRCD              ADC_ECR1_PSRCD_Msk                  /*!< ADC To ECU Ping-Pong Flag Dowm Over Zero Src Select*/
#define ADC_ECR1_PSRCD_0            (0x1UL << ADC_ECR1_PSRCD_Pos)       /*!< 0x00001000                                         */
#define ADC_ECR1_PSRCD_1            (0x2UL << ADC_ECR1_PSRCD_Pos)       /*!< 0x00002000                                         */
#define ADC_ECR1_AWD2SEL_Pos        (8U)
#define ADC_ECR1_AWD2SEL_Msk        (0xFUL << ADC_ECR1_AWD2SEL_Pos)     /*!< 0x00000F00                                         */
#define ADC_ECR1_AWD2SEL            ADC_ECR1_AWD2SEL_Msk                /*!< ADC To ECU analog watchdog 2 Source Select         */
#define ADC_ECR1_AWD2SEL_0          (0x1UL << ADC_ECR1_AWD2SEL_Pos)     /*!< 0x00000100                                         */
#define ADC_ECR1_AWD2SEL_1          (0x2UL << ADC_ECR1_AWD2SEL_Pos)     /*!< 0x00000200                                         */
#define ADC_ECR1_AWD2SEL_2          (0x4UL << ADC_ECR1_AWD2SEL_Pos)     /*!< 0x00000400                                         */
#define ADC_ECR1_AWD2SEL_3          (0x8UL << ADC_ECR1_AWD2SEL_Pos)     /*!< 0x00000800                                         */
#define ADC_ECR1_AWD1SEL_Pos        (4U)
#define ADC_ECR1_AWD1SEL_Msk        (0xFUL << ADC_ECR1_AWD1SEL_Pos)     /*!< 0x000000F0                                         */
#define ADC_ECR1_AWD1SEL            ADC_ECR1_AWD1SEL_Msk                /*!< ADC To ECU analog watchdog 1 Source Select         */
#define ADC_ECR1_AWD1SEL_0          (0x1UL << ADC_ECR1_AWD1SEL_Pos)     /*!< 0x00000010                                         */
#define ADC_ECR1_AWD1SEL_1          (0x2UL << ADC_ECR1_AWD1SEL_Pos)     /*!< 0x00000020                                         */
#define ADC_ECR1_AWD1SEL_2          (0x4UL << ADC_ECR1_AWD1SEL_Pos)     /*!< 0x00000040                                         */
#define ADC_ECR1_AWD1SEL_3          (0x8UL << ADC_ECR1_AWD1SEL_Pos)     /*!< 0x00000080                                         */
#define ADC_ECR1_AWD0SEL_Pos        (0U)
#define ADC_ECR1_AWD0SEL_Msk        (0xFUL << ADC_ECR1_AWD0SEL_Pos)     /*!< 0x0000000F                                         */
#define ADC_ECR1_AWD0SEL            ADC_ECR1_AWD0SEL_Msk                /*!< ADC To ECU analog watchdog 0 Source Select         */
#define ADC_ECR1_AWD0SEL_0          (0x1UL << ADC_ECR1_AWD0SEL_Pos)     /*!< 0x00000001                                         */
#define ADC_ECR1_AWD0SEL_1          (0x2UL << ADC_ECR1_AWD0SEL_Pos)     /*!< 0x00000002                                         */
#define ADC_ECR1_AWD0SEL_2          (0x4UL << ADC_ECR1_AWD0SEL_Pos)     /*!< 0x00000004                                         */
#define ADC_ECR1_AWD0SEL_3          (0x8UL << ADC_ECR1_AWD0SEL_Pos)     /*!< 0x00000008                                         */

/********************  Bit definition for ADC_ECR2 register  ******************/
#define ADC_ECR2_ADSRC_Pos          (16U)
#define ADC_ECR2_ADSRC_Msk          (0xFUL << ADC_ECR2_ADSRC_Pos)       /*!< 0x000F0000                                         */
#define ADC_ECR2_ADSRC              ADC_ECR2_ADSRC_Msk                  /*!< ADC To ECU Addr-Data Flag Source Select            */
#define ADC_ECR2_ADSRC_0            (0x1UL << ADC_ECR2_ADSRC_Pos)       /*!< 0x00010000                                         */
#define ADC_ECR2_ADSRC_1            (0x2UL << ADC_ECR2_ADSRC_Pos)       /*!< 0x00020000                                         */
#define ADC_ECR2_ADSRC_2            (0x4UL << ADC_ECR2_ADSRC_Pos)       /*!< 0x00040000                                         */
#define ADC_ECR2_ADSRC_3            (0x8UL << ADC_ECR2_ADSRC_Pos)       /*!< 0x00080000                                         */
#define ADC_ECR2_PSRCU_Pos          (14U)
#define ADC_ECR2_PSRCU_Msk          (0x3UL << ADC_ECR2_PSRCU_Pos)       /*!< 0x0000C000                                         */
#define ADC_ECR2_PSRCU              ADC_ECR2_PSRCU_Msk                  /*!< ADC To ECU Ping-Pong Flag Go Over Zero Src Select  */
#define ADC_ECR2_PSRCU_0            (0x1UL << ADC_ECR2_PSRCU_Pos)       /*!< 0x00004000                                         */
#define ADC_ECR2_PSRCU_1            (0x2UL << ADC_ECR2_PSRCU_Pos)       /*!< 0x00008000                                         */
#define ADC_ECR2_PSRCD_Pos          (12U)
#define ADC_ECR2_PSRCD_Msk          (0x3UL << ADC_ECR2_PSRCD_Pos)       /*!< 0x00003000                                         */
#define ADC_ECR2_PSRCD              ADC_ECR2_PSRCD_Msk                  /*!< ADC To ECU Ping-Pong Flag Dowm Over Zero Src Select*/
#define ADC_ECR2_PSRCD_0            (0x1UL << ADC_ECR2_PSRCD_Pos)       /*!< 0x00001000                                         */
#define ADC_ECR2_PSRCD_1            (0x2UL << ADC_ECR2_PSRCD_Pos)       /*!< 0x00002000                                         */
#define ADC_ECR2_AWD2SEL_Pos        (8U)
#define ADC_ECR2_AWD2SEL_Msk        (0xFUL << ADC_ECR2_AWD2SEL_Pos)     /*!< 0x00000F00                                         */
#define ADC_ECR2_AWD2SEL            ADC_ECR2_AWD2SEL_Msk                /*!< ADC To ECU analog watchdog 2 Source Select         */
#define ADC_ECR2_AWD2SEL_0          (0x1UL << ADC_ECR2_AWD2SEL_Pos)     /*!< 0x00000100                                         */
#define ADC_ECR2_AWD2SEL_1          (0x2UL << ADC_ECR2_AWD2SEL_Pos)     /*!< 0x00000200                                         */
#define ADC_ECR2_AWD2SEL_2          (0x4UL << ADC_ECR2_AWD2SEL_Pos)     /*!< 0x00000400                                         */
#define ADC_ECR2_AWD2SEL_3          (0x8UL << ADC_ECR2_AWD2SEL_Pos)     /*!< 0x00000800                                         */
#define ADC_ECR2_AWD1SEL_Pos        (4U)
#define ADC_ECR2_AWD1SEL_Msk        (0xFUL << ADC_ECR2_AWD1SEL_Pos)     /*!< 0x000000F0                                         */
#define ADC_ECR2_AWD1SEL            ADC_ECR2_AWD1SEL_Msk                /*!< ADC To ECU analog watchdog 1 Source Select         */
#define ADC_ECR2_AWD1SEL_0          (0x1UL << ADC_ECR2_AWD1SEL_Pos)     /*!< 0x00000010                                         */
#define ADC_ECR2_AWD1SEL_1          (0x2UL << ADC_ECR2_AWD1SEL_Pos)     /*!< 0x00000020                                         */
#define ADC_ECR2_AWD1SEL_2          (0x4UL << ADC_ECR2_AWD1SEL_Pos)     /*!< 0x00000040                                         */
#define ADC_ECR2_AWD1SEL_3          (0x8UL << ADC_ECR2_AWD1SEL_Pos)     /*!< 0x00000080                                         */
#define ADC_ECR2_AWD0SEL_Pos        (0U)
#define ADC_ECR2_AWD0SEL_Msk        (0xFUL << ADC_ECR2_AWD0SEL_Pos)     /*!< 0x0000000F                                         */
#define ADC_ECR2_AWD0SEL            ADC_ECR2_AWD0SEL_Msk                /*!< ADC To ECU analog watchdog 0 Source Select         */
#define ADC_ECR2_AWD0SEL_0          (0x1UL << ADC_ECR2_AWD0SEL_Pos)     /*!< 0x00000001                                         */
#define ADC_ECR2_AWD0SEL_1          (0x2UL << ADC_ECR2_AWD0SEL_Pos)     /*!< 0x00000002                                         */
#define ADC_ECR2_AWD0SEL_2          (0x4UL << ADC_ECR2_AWD0SEL_Pos)     /*!< 0x00000004                                         */
#define ADC_ECR2_AWD0SEL_3          (0x8UL << ADC_ECR2_AWD0SEL_Pos)     /*!< 0x00000008                                         */

/********************  Bit definition for ADC_ECR3 register  ******************/
#define ADC_ECR3_ADSRC_Pos          (16U)
#define ADC_ECR3_ADSRC_Msk          (0xFUL << ADC_ECR3_ADSRC_Pos)       /*!< 0x000F0000                                         */
#define ADC_ECR3_ADSRC              ADC_ECR3_ADSRC_Msk                  /*!< ADC To ECU Addr-Data Flag Source Select            */
#define ADC_ECR3_ADSRC_0            (0x1UL << ADC_ECR3_ADSRC_Pos)       /*!< 0x00010000                                         */
#define ADC_ECR3_ADSRC_1            (0x2UL << ADC_ECR3_ADSRC_Pos)       /*!< 0x00020000                                         */
#define ADC_ECR3_ADSRC_2            (0x4UL << ADC_ECR3_ADSRC_Pos)       /*!< 0x00040000                                         */
#define ADC_ECR3_ADSRC_3            (0x8UL << ADC_ECR3_ADSRC_Pos)       /*!< 0x00080000                                         */
#define ADC_ECR3_PSRCU_Pos          (14U)
#define ADC_ECR3_PSRCU_Msk          (0x3UL << ADC_ECR3_PSRCU_Pos)       /*!< 0x0000C000                                         */
#define ADC_ECR3_PSRCU              ADC_ECR3_PSRCU_Msk                  /*!< ADC To ECU Ping-Pong Flag Go Over Zero Src Select  */
#define ADC_ECR3_PSRCU_0            (0x1UL << ADC_ECR3_PSRCU_Pos)       /*!< 0x00004000                                         */
#define ADC_ECR3_PSRCU_1            (0x2UL << ADC_ECR3_PSRCU_Pos)       /*!< 0x00008000                                         */
#define ADC_ECR3_PSRCD_Pos          (12U)
#define ADC_ECR3_PSRCD_Msk          (0x3UL << ADC_ECR3_PSRCD_Pos)       /*!< 0x00003000                                         */
#define ADC_ECR3_PSRCD              ADC_ECR3_PSRCD_Msk                  /*!< ADC To ECU Ping-Pong Flag Dowm Over Zero Src Select*/
#define ADC_ECR3_PSRCD_0            (0x1UL << ADC_ECR3_PSRCD_Pos)       /*!< 0x00001000                                         */
#define ADC_ECR3_PSRCD_1            (0x2UL << ADC_ECR3_PSRCD_Pos)       /*!< 0x00002000                                         */
#define ADC_ECR3_AWD2SEL_Pos        (8U)
#define ADC_ECR3_AWD2SEL_Msk        (0xFUL << ADC_ECR3_AWD2SEL_Pos)     /*!< 0x00000F00                                         */
#define ADC_ECR3_AWD2SEL            ADC_ECR3_AWD2SEL_Msk                /*!< ADC To ECU analog watchdog 2 Source Select         */
#define ADC_ECR3_AWD2SEL_0          (0x1UL << ADC_ECR3_AWD2SEL_Pos)     /*!< 0x00000100                                         */
#define ADC_ECR3_AWD2SEL_1          (0x2UL << ADC_ECR3_AWD2SEL_Pos)     /*!< 0x00000200                                         */
#define ADC_ECR3_AWD2SEL_2          (0x4UL << ADC_ECR3_AWD2SEL_Pos)     /*!< 0x00000400                                         */
#define ADC_ECR3_AWD2SEL_3          (0x8UL << ADC_ECR3_AWD2SEL_Pos)     /*!< 0x00000800                                         */
#define ADC_ECR3_AWD1SEL_Pos        (4U)
#define ADC_ECR3_AWD1SEL_Msk        (0xFUL << ADC_ECR3_AWD1SEL_Pos)     /*!< 0x000000F0                                         */
#define ADC_ECR3_AWD1SEL            ADC_ECR3_AWD1SEL_Msk                /*!< ADC To ECU analog watchdog 1 Source Select         */
#define ADC_ECR3_AWD1SEL_0          (0x1UL << ADC_ECR3_AWD1SEL_Pos)     /*!< 0x00000010                                         */
#define ADC_ECR3_AWD1SEL_1          (0x2UL << ADC_ECR3_AWD1SEL_Pos)     /*!< 0x00000020                                         */
#define ADC_ECR3_AWD1SEL_2          (0x4UL << ADC_ECR3_AWD1SEL_Pos)     /*!< 0x00000040                                         */
#define ADC_ECR3_AWD1SEL_3          (0x8UL << ADC_ECR3_AWD1SEL_Pos)     /*!< 0x00000080                                         */
#define ADC_ECR3_AWD0SEL_Pos        (0U)
#define ADC_ECR3_AWD0SEL_Msk        (0xFUL << ADC_ECR3_AWD0SEL_Pos)     /*!< 0x0000000F                                         */
#define ADC_ECR3_AWD0SEL            ADC_ECR3_AWD0SEL_Msk                /*!< ADC To ECU analog watchdog 0 Source Select         */
#define ADC_ECR3_AWD0SEL_0          (0x1UL << ADC_ECR3_AWD0SEL_Pos)     /*!< 0x00000001                                         */
#define ADC_ECR3_AWD0SEL_1          (0x2UL << ADC_ECR3_AWD0SEL_Pos)     /*!< 0x00000002                                         */
#define ADC_ECR3_AWD0SEL_2          (0x4UL << ADC_ECR3_AWD0SEL_Pos)     /*!< 0x00000004                                         */
#define ADC_ECR3_AWD0SEL_3          (0x8UL << ADC_ECR3_AWD0SEL_Pos)     /*!< 0x00000008                                         */

/********************  Bit definition for ADC_CDR register  *******************/
#define ADC_CDR_RDATA_Pos           (0U)
#define ADC_CDR_RDATA_Msk           (0xFFFFUL << ADC_CDR_RDATA_Pos)     /*!< 0x0000FFFF                                         */
#define ADC_CDR_RDATA               ADC_CDR_RDATA_Msk                   /*!< ADC group single channel regular conversion data   */

/********************  Bit definition for ADC_HIER register  ******************/
#define ADC_HIER_CHANNEL_Pos        (0U)
#define ADC_HIER_CHANNEL_Msk        (0xFFFUL << ADC_HIER_CHANNEL_Pos)   /*!< 0x00000FFF                                         */
#define ADC_HIER_CHANNEL            ADC_HIER_CHANNEL_Msk                /*!< ADC Grp Regular End Of Half DMA Transmit Interrupt */
#define ADC_HIER_CHANNEL_0          (0x00001UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000001                                         */
#define ADC_HIER_CHANNEL_1          (0x00002UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000002                                         */
#define ADC_HIER_CHANNEL_2          (0x00004UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000004                                         */
#define ADC_HIER_CHANNEL_3          (0x00008UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000008                                         */
#define ADC_HIER_CHANNEL_4          (0x00010UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000010                                         */
#define ADC_HIER_CHANNEL_5          (0x00020UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000020                                         */
#define ADC_HIER_CHANNEL_6          (0x00040UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000040                                         */
#define ADC_HIER_CHANNEL_7          (0x00080UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000080                                         */
#define ADC_HIER_CHANNEL_8          (0x00100UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000100                                         */
#define ADC_HIER_CHANNEL_9          (0x00200UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000200                                         */
#define ADC_HIER_CHANNEL_10         (0x00400UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000400                                         */
#define ADC_HIER_CHANNEL_11         (0x00800UL << ADC_HIER_CHANNEL_Pos) /*!< 0x00000800                                         */

/********************  Bit definition for ADC_HISR register  ******************/
#define ADC_HISR_CHANNEL_Pos        (0U)
#define ADC_HISR_CHANNEL_Msk        (0xFFFUL << ADC_HISR_CHANNEL_Pos)   /*!< 0x00000FFF                                         */
#define ADC_HISR_CHANNEL            ADC_HISR_CHANNEL_Msk                /*!< ADC Group Regular End Of Half DMA Transmit Flag    */
#define ADC_HISR_CHANNEL_0          (0x00001UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000001                                         */
#define ADC_HISR_CHANNEL_1          (0x00002UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000002                                         */
#define ADC_HISR_CHANNEL_2          (0x00004UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000004                                         */
#define ADC_HISR_CHANNEL_3          (0x00008UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000008                                         */
#define ADC_HISR_CHANNEL_4          (0x00010UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000010                                         */
#define ADC_HISR_CHANNEL_5          (0x00020UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000020                                         */
#define ADC_HISR_CHANNEL_6          (0x00040UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000040                                         */
#define ADC_HISR_CHANNEL_7          (0x00080UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000080                                         */
#define ADC_HISR_CHANNEL_8          (0x00100UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000100                                         */
#define ADC_HISR_CHANNEL_9          (0x00200UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000200                                         */
#define ADC_HISR_CHANNEL_10         (0x00400UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000400                                         */
#define ADC_HISR_CHANNEL_11         (0x00800UL << ADC_HISR_CHANNEL_Pos) /*!< 0x00000800                                         */

/********************  Bit definition for ADC_FIER register  ******************/
#define ADC_FIER_CHANNEL_Pos        (0U)
#define ADC_FIER_CHANNEL_Msk        (0xFFFUL << ADC_FIER_CHANNEL_Pos)   /*!< 0x00000FFF                                         */
#define ADC_FIER_CHANNEL            ADC_FIER_CHANNEL_Msk                /*!< ADC Grp Regular End Of Full DMA Transfer Interrupt */
#define ADC_FIER_CHANNEL_0          (0x00001UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000001                                         */
#define ADC_FIER_CHANNEL_1          (0x00002UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000002                                         */
#define ADC_FIER_CHANNEL_2          (0x00004UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000004                                         */
#define ADC_FIER_CHANNEL_3          (0x00008UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000008                                         */
#define ADC_FIER_CHANNEL_4          (0x00010UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000010                                         */
#define ADC_FIER_CHANNEL_5          (0x00020UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000020                                         */
#define ADC_FIER_CHANNEL_6          (0x00040UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000040                                         */
#define ADC_FIER_CHANNEL_7          (0x00080UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000080                                         */
#define ADC_FIER_CHANNEL_8          (0x00100UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000100                                         */
#define ADC_FIER_CHANNEL_9          (0x00200UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000200                                         */
#define ADC_FIER_CHANNEL_10         (0x00400UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000400                                         */
#define ADC_FIER_CHANNEL_11         (0x00800UL << ADC_FIER_CHANNEL_Pos) /*!< 0x00000800                                         */

/********************  Bit definition for ADC_FISR register  ******************/
#define ADC_FISR_CHANNEL_Pos        (0U)
#define ADC_FISR_CHANNEL_Msk        (0xFFFUL << ADC_FISR_CHANNEL_Pos)   /*!< 0x00000FFF                                         */
#define ADC_FISR_CHANNEL            ADC_FISR_CHANNEL_Msk                /*!< ADC Group Regular End Of Full DMA Transfer Flag    */
#define ADC_FISR_CHANNEL_0          (0x00001UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000001                                         */
#define ADC_FISR_CHANNEL_1          (0x00002UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000002                                         */
#define ADC_FISR_CHANNEL_2          (0x00004UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000004                                         */
#define ADC_FISR_CHANNEL_3          (0x00008UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000008                                         */
#define ADC_FISR_CHANNEL_4          (0x00010UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000010                                         */
#define ADC_FISR_CHANNEL_5          (0x00020UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000020                                         */
#define ADC_FISR_CHANNEL_6          (0x00040UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000040                                         */
#define ADC_FISR_CHANNEL_7          (0x00080UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000080                                         */
#define ADC_FISR_CHANNEL_8          (0x00100UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000100                                         */
#define ADC_FISR_CHANNEL_9          (0x00200UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000200                                         */
#define ADC_FISR_CHANNEL_10         (0x00400UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000400                                         */
#define ADC_FISR_CHANNEL_11         (0x00800UL << ADC_FISR_CHANNEL_Pos) /*!< 0x00000800                                         */

/**************  Bit definition for ADC_DMA_CR[0~11] TCR register  ************/
#define ADC_DMA_TCR_CIRC_Pos        (2U)
#define ADC_DMA_TCR_CIRC_Msk        (0x1UL << ADC_DMA_TCR_CIRC_Pos)     /*!< 0x00000004                                         */
#define ADC_DMA_TCR_CIRC            ADC_DMA_TCR_CIRC_Msk                /*!< ADC DMA Channel 0 Transfer circle mode enable      */
#define ADC_DMA_TCR_STP_Pos         (1U)
#define ADC_DMA_TCR_STP_Msk         (0x1UL << ADC_DMA_TCR_STP_Pos)      /*!< 0x00000002                                         */
#define ADC_DMA_TCR_STP             ADC_DMA_TCR_STP_Msk                 /*!< ADC DMA Mode Channel 0 Stop                        */
#define ADC_DMA_TCR_START_Pos       (0U)
#define ADC_DMA_TCR_START_Msk       (0x1UL << ADC_DMA_TCR_START_Pos)    /*!< 0x00000001                                         */
#define ADC_DMA_TCR_START           ADC_DMA_TCR_START_Msk               /*!< ADC DMA Mode Channel 0 Start                       */

/*****************  Bit definition for ADC_DMA_CR TAR register  ***************/
#define ADC_DMA_TAR_ADDR_Pos        (0U)
#define ADC_DMA_TAR_ADDR_Msk        (0xFFFFUL << ADC_DMA_TAR_ADDR_Pos)  /*!< 0x0000FFFF                                         */
#define ADC_DMA_TAR_ADDR            ADC_DMA_TAR_ADDR_Msk                /*!< ADC DMA Channel 0 Transfer Addrdess                */

/*****************  Bit definition for ADC_DMA_CR TLR register  ***************/
#define ADC_DMA_TLR_LENG_Pos        (0U)
#define ADC_DMA_TLR_LENG_Msk        (0x1FFFUL << ADC_DMA_TLR_LENG_Pos)  /*!< 0x00001FFF                                         */
#define ADC_DMA_TLR_LENG            ADC_DMA_TLR_LENG_Msk                /*!< ADC DMA Channel 0 Transfer Byte Length             */


/******************************************************************************/
/*                                                                            */
/*                     Electricity Calculate Unit (ECU)                       */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for ECU_CON register  *******************/
#define ECU_CON_INT_Pos             (15U)
#define ECU_CON_INT_Msk             (0x1UL << ECU_CON_INT_Pos)              /*!< 0x00008000                 */
#define ECU_CON_INT                 ECU_CON_INT_Msk                         /*!< ECU End Of Calculate Flag  */
#define ECU_CON_SQRT_Pos            (14U)
#define ECU_CON_SQRT_Msk            (0x1UL << ECU_CON_SQRT_Pos)             /*!< 0x00004000                 */
#define ECU_CON_SQRT                ECU_CON_SQRT_Msk
#define ECU_CON_ACSFT_Pos           (9U)
#define ECU_CON_ACSFT_Msk           (0x1FUL << ECU_CON_ACSFT_Pos)           /*!< 0x00003E00                 */
#define ECU_CON_ACSFT               ECU_CON_ACSFT_Msk
#define ECU_CON_ACSFT_0             (0x01UL << ECU_CON_ACSFT_Pos)           /*!< 0x00000200                 */
#define ECU_CON_ACSFT_1             (0x02UL << ECU_CON_ACSFT_Pos)           /*!< 0x00000400                 */
#define ECU_CON_ACSFT_2             (0x04UL << ECU_CON_ACSFT_Pos)           /*!< 0x00000800                 */
#define ECU_CON_ACSFT_3             (0x08UL << ECU_CON_ACSFT_Pos)           /*!< 0x00001000                 */
#define ECU_CON_ACSFT_4             (0x10UL << ECU_CON_ACSFT_Pos)           /*!< 0x00002000                 */
#define ECU_CON_APSFT_Pos           (4U)
#define ECU_CON_APSFT_Msk           (0x1FUL << ECU_CON_APSFT_Pos)           /*!< 0x000001F0                 */
#define ECU_CON_APSFT               ECU_CON_APSFT_Msk
#define ECU_CON_APSFT_0             (0x01UL << ECU_CON_APSFT_Pos)           /*!< 0x00000010                 */
#define ECU_CON_APSFT_1             (0x02UL << ECU_CON_APSFT_Pos)           /*!< 0x00000020                 */
#define ECU_CON_APSFT_2             (0x04UL << ECU_CON_APSFT_Pos)           /*!< 0x00000040                 */
#define ECU_CON_APSFT_3             (0x08UL << ECU_CON_APSFT_Pos)           /*!< 0x00000080                 */
#define ECU_CON_APSFT_4             (0x10UL << ECU_CON_APSFT_Pos)           /*!< 0x00000100                 */
#define ECU_CON_AVGSEL_Pos          (2U)
#define ECU_CON_AVGSEL_Msk          (0x3UL << ECU_CON_AVGSEL_Pos)           /*!< 0x0000000C                 */
#define ECU_CON_AVGSEL              ECU_CON_AVGSEL_Msk
#define ECU_CON_AVGSEL_0            (0x1UL << ECU_CON_AVGSEL_Pos)           /*!< 0x00000004                 */
#define ECU_CON_AVGSEL_1            (0x2UL << ECU_CON_AVGSEL_Pos)           /*!< 0x00000008                 */
#define ECU_CON_INTEN_Pos           (1U)
#define ECU_CON_INTEN_Msk           (0x1UL << ECU_CON_INTEN_Pos)            /*!< 0x00000002                 */
#define ECU_CON_INTEN               ECU_CON_INTEN_Msk                       /*!< ECU End Of Calculate Flag  */
#define ECU_CON_ENABLE_Pos          (0U)
#define ECU_CON_ENABLE_Msk          (0x1UL << ECU_CON_ENABLE_Pos)           /*!< 0x00000001                 */
#define ECU_CON_ENABLE              ECU_CON_ENABLE_Msk                      /*!< ECU End Of Calculate Flag  */

/********************  Bit definition for ECU_PRC register  *******************/
#define ECU_PRC_CRSSEL_Pos          (8U)
#define ECU_PRC_CRSSEL_Msk          (0xFUL << ECU_PRC_CRSSEL_Pos)           /*!< 0x00000F00                 */
#define ECU_PRC_CRSSEL              ECU_PRC_CRSSEL_Msk
#define ECU_PRC_CRSSEL_0            (0x1UL << ECU_PRC_CRSSEL_Pos)           /*!< 0x00000100                 */
#define ECU_PRC_CRSSEL_1            (0x2UL << ECU_PRC_CRSSEL_Pos)           /*!< 0x00000200                 */
#define ECU_PRC_CRSSEL_2            (0x4UL << ECU_PRC_CRSSEL_Pos)           /*!< 0x00000400                 */
#define ECU_PRC_CRSSEL_3            (0x8UL << ECU_PRC_CRSSEL_Pos)           /*!< 0x00000800                 */
#define ECU_PRC_ADRSEL_Pos          (4U)
#define ECU_PRC_ADRSEL_Msk          (0xFUL << ECU_PRC_ADRSEL_Pos)           /*!< 0x000000F0                 */
#define ECU_PRC_ADRSEL              ECU_PRC_ADRSEL_Msk
#define ECU_PRC_ADRSEL_0            (0x1UL << ECU_PRC_ADRSEL_Pos)           /*!< 0x00000010                 */
#define ECU_PRC_ADRSEL_1            (0x2UL << ECU_PRC_ADRSEL_Pos)           /*!< 0x00000020                 */
#define ECU_PRC_ADRSEL_2            (0x4UL << ECU_PRC_ADRSEL_Pos)           /*!< 0x00000040                 */
#define ECU_PRC_ADRSEL_3            (0x8UL << ECU_PRC_ADRSEL_Pos)           /*!< 0x00000080                 */
#define ECU_PRC_DATSEL_Pos          (0U)
#define ECU_PRC_DATSEL_Msk          (0xFUL << ECU_PRC_DATSEL_Pos)           /*!< 0x0000000F                 */
#define ECU_PRC_DATSEL              ECU_PRC_DATSEL_Msk
#define ECU_PRC_DATSEL_0            (0x1UL << ECU_PRC_DATSEL_Pos)           /*!< 0x00000001                 */
#define ECU_PRC_DATSEL_1            (0x2UL << ECU_PRC_DATSEL_Pos)           /*!< 0x00000002                 */
#define ECU_PRC_DATSEL_2            (0x4UL << ECU_PRC_DATSEL_Pos)           /*!< 0x00000004                 */
#define ECU_PRC_DATSEL_3            (0x8UL << ECU_PRC_DATSEL_Pos)           /*!< 0x00000008                 */

/******************  Bit definition for ECU_SQRT_IN register  *****************/
#define ECU_SQRT_INDATA_Pos         (0U)
#define ECU_SQRT_INDATA_Msk         (0xFFFFFFFFUL << ECU_SQRT_INDATA_Pos)   /*!< 0xFFFFFFFF                 */
#define ECU_SQRT_INDATA             ECU_SQRT_INDATA_Msk

/******************  Bit definition for ECU_SQRT_OUT register  ****************/
#define ECU_SQRT_OUTDATA_Pos        (0U)
#define ECU_SQRT_OUTDATA_Msk        (0xFFFFFFFFUL << ECU_SQRT_OUTDATA_Pos)  /*!< 0xFFFFFFFF                 */
#define ECU_SQRT_OUTDATA            ECU_SQRT_OUTDATA_Msk

/******************  Bit definition for ECU_V_ADDR1 register  *****************/
#define ECU_V_ADDR1_STADDR_Pos      (0U)
#define ECU_V_ADDR1_STADDR_Msk      (0xFFFFUL << ECU_V_ADDR1_STADDR_Pos)    /*!< 0x0000FFFF                 */
#define ECU_V_ADDR1_STADDR          ECU_V_ADDR1_STADDR_Msk

/******************  Bit definition for ECU_V_ADDR2 register  *****************/
#define ECU_V_ADDR2_OFADDR_Pos      (0U)
#define ECU_V_ADDR2_OFADDR_Msk      (0xFFFFUL << ECU_V_ADDR2_OFADDR_Pos)    /*!< 0x0000FFFF                 */
#define ECU_V_ADDR2_OFADDR          ECU_V_ADDR2_OFADDR_Msk

/******************  Bit definition for ECU_I_ADDR1 register  *****************/
#define ECU_I_ADDR1_STADDR_Pos      (0U)
#define ECU_I_ADDR1_STADDR_Msk      (0xFFFFUL << ECU_I_ADDR1_STADDR_Pos)    /*!< 0x0000FFFF                 */
#define ECU_I_ADDR1_STADDR          ECU_I_ADDR1_STADDR_Msk

/******************  Bit definition for ECU_I_ADDR2 register  *****************/
#define ECU_I_ADDR2_OFADDR_Pos      (0U)
#define ECU_I_ADDR2_OFADDR_Msk      (0xFFFFUL << ECU_I_ADDR2_OFADDR_Pos)    /*!< 0x0000FFFF                 */
#define ECU_I_ADDR2_OFADDR          ECU_I_ADDR2_OFADDR_Msk

/*********************  Bit definition for ECU_V register  ********************/
#define ECU_V_VRMS_Pos              (0U)
#define ECU_V_VRMS_Msk              (0xFFFFUL << ECU_V_VRMS_Pos)            /*!< 0x0000FFFF                 */
#define ECU_V_VRMS                  ECU_V_VRMS_Msk

/*********************  Bit definition for ECU_I register  ********************/
#define ECU_I_IRMS_Pos              (0U)
#define ECU_I_IRMS_Msk              (0xFFFFUL << ECU_I_IRMS_Pos)            /*!< 0x0000FFFF                 */
#define ECU_I_IRMS                  ECU_I_IRMS_Msk

/*********************  Bit definition for ECU_P register  ********************/
#define ECU_P_PAVG_Pos              (0U)
#define ECU_P_PAVG_Msk              (0xFFFFFFFFUL << ECU_P_PAVG_Pos)        /*!< 0xFFFFFFFF                 */
#define ECU_P_PAVG                  ECU_P_PAVG_Msk

/*********************  Bit definition for ECU_Q register  ********************/
#define ECU_Q_QAVG_Pos              (0U)
#define ECU_Q_QAVG_Msk              (0xFFFFFFFFUL << ECU_Q_QAVG_Pos)        /*!< 0xFFFFFFFF                 */
#define ECU_Q_QAVG                  ECU_Q_QAVG_Msk

/*********************  Bit definition for ECU_S register  ********************/
#define ECU_S_SCAL_Pos              (0U)
#define ECU_S_SCAL_Msk              (0xFFFFFFFFUL << ECU_S_SCAL_Pos)        /*!< 0xFFFFFFFF                 */
#define ECU_S_SCAL                  ECU_S_SCAL_Msk

/********************  Bit definition for ECU_PF register  ********************/
#define ECU_PF_PFSCAL_Pos           (0U)
#define ECU_PF_PFSCAL_Msk           (0xFFFFFFFFUL << ECU_PF_PFSCAL_Pos)     /*!< 0xFFFFFFFF                 */
#define ECU_PF_PFSCAL               ECU_PF_PFSCAL_Msk

/*********************  Bit definition for ECU_F register  ********************/
#define ECU_F_FCNT_Pos              (0U)
#define ECU_F_FCNT_Msk              (0xFFFFUL << ECU_F_FCNT_Pos)            /*!< 0x0000FFFF                 */
#define ECU_F_FCNT                  ECU_F_FCNT_Msk


/******************************************************************************/
/*                                                                            */
/*                        High Resolution PWM (HRPWM)                         */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for HRPWM_MCR register  ******************/
#define HRPWM_MCR_PREEN_Pos         (25U)
#define HRPWM_MCR_PREEN_Msk         (0x1UL << HRPWM_MCR_PREEN_Pos)          /*!< 0x02000000                                     */
#define HRPWM_MCR_PREEN             HRPWM_MCR_PREEN_Msk                     /*!< Master preload enable                          */
#define HRPWM_MCR_MREPU_Pos         (24U)
#define HRPWM_MCR_MREPU_Msk         (0x1UL << HRPWM_MCR_MREPU_Pos)          /*!< 0x01000000                                     */
#define HRPWM_MCR_MREPU             HRPWM_MCR_MREPU_Msk                     /*!< Master repetition update                       */
#define HRPWM_MCR_CEN5_Pos          (22U)
#define HRPWM_MCR_CEN5_Msk          (0x1UL << HRPWM_MCR_CEN5_Pos)           /*!< 0x00400000                                     */
#define HRPWM_MCR_CEN5              HRPWM_MCR_CEN5_Msk                      /*!< Timer 5 counter enable                         */
#define HRPWM_MCR_CEN4_Pos          (21U)
#define HRPWM_MCR_CEN4_Msk          (0x1UL << HRPWM_MCR_CEN4_Pos)           /*!< 0x00200000                                     */
#define HRPWM_MCR_CEN4              HRPWM_MCR_CEN4_Msk                      /*!< Timer 4 counter enable                         */
#define HRPWM_MCR_CEN3_Pos          (20U)
#define HRPWM_MCR_CEN3_Msk          (0x1UL << HRPWM_MCR_CEN3_Pos)           /*!< 0x00100000                                     */
#define HRPWM_MCR_CEN3              HRPWM_MCR_CEN3_Msk                      /*!< Timer 3 counter enable                         */
#define HRPWM_MCR_CEN2_Pos          (19U)
#define HRPWM_MCR_CEN2_Msk          (0x1UL << HRPWM_MCR_CEN2_Pos)           /*!< 0x00080000                                     */
#define HRPWM_MCR_CEN2              HRPWM_MCR_CEN2_Msk                      /*!< Timer 2 counter enable                         */
#define HRPWM_MCR_CEN1_Pos          (18U)
#define HRPWM_MCR_CEN1_Msk          (0x1UL << HRPWM_MCR_CEN1_Pos)           /*!< 0x00040000                                     */
#define HRPWM_MCR_CEN1              HRPWM_MCR_CEN1_Msk                      /*!< Timer 1 counter enable                         */
#define HRPWM_MCR_CEN0_Pos          (17U)
#define HRPWM_MCR_CEN0_Msk          (0x1UL << HRPWM_MCR_CEN0_Pos)           /*!< 0x00020000                                     */
#define HRPWM_MCR_CEN0              HRPWM_MCR_CEN0_Msk                      /*!< Timer 0 counter enable                         */
#define HRPWM_MCR_MCEN_Pos          (16U)
#define HRPWM_MCR_MCEN_Msk          (0x1UL << HRPWM_MCR_MCEN_Pos)           /*!< 0x00010000                                     */
#define HRPWM_MCR_MCEN              HRPWM_MCR_MCEN_Msk                      /*!< Master counter enable                          */
#define HRPWM_MCR_SYNCOUT_SRC_Pos   (14U)
#define HRPWM_MCR_SYNCOUT_SRC_Msk   (0x3UL << HRPWM_MCR_SYNCOUT_SRC_Pos)    /*!< 0x0000C000                                     */
#define HRPWM_MCR_SYNCOUT_SRC       HRPWM_MCR_SYNCOUT_SRC_Msk               /*!< Synchronization output Source master           */
#define HRPWM_MCR_SYNCOUT_SRC_0     (0x1UL << HRPWM_MCR_SYNCOUT_SRC_Pos)    /*!< 0x00004000                                     */
#define HRPWM_MCR_SYNCOUT_SRC_1     (0x2UL << HRPWM_MCR_SYNCOUT_SRC_Pos)    /*!< 0x00008000                                     */
#define HRPWM_MCR_SYNCOUT_EN_Pos    (13U)
#define HRPWM_MCR_SYNCOUT_EN_Msk    (0x1UL << HRPWM_MCR_SYNCOUT_EN_Pos)     /*!< 0x00002000                                     */
#define HRPWM_MCR_SYNCOUT_EN        HRPWM_MCR_SYNCOUT_EN_Msk                /*!< Synchronization output Eanble master           */
#define HRPWM_MCR_SYNCOUT_POL_Pos   (12U)
#define HRPWM_MCR_SYNCOUT_POL_Msk   (0x1UL << HRPWM_MCR_SYNCOUT_POL_Pos)    /*!< 0x00001000                                     */
#define HRPWM_MCR_SYNCOUT_POL       HRPWM_MCR_SYNCOUT_POL_Msk               /*!< Synchronization output Polarity master         */
#define HRPWM_MCR_SYNCSTRTM_Pos     (11U)
#define HRPWM_MCR_SYNCSTRTM_Msk     (0x1UL << HRPWM_MCR_SYNCSTRTM_Pos)      /*!< 0x00000800                                     */
#define HRPWM_MCR_SYNCSTRTM         HRPWM_MCR_SYNCSTRTM_Msk                 /*!< Synchronization start master                   */
#define HRPWM_MCR_SYNCRSTM_Pos      (10U)
#define HRPWM_MCR_SYNCRSTM_Msk      (0x1UL << HRPWM_MCR_SYNCRSTM_Pos)       /*!< 0x00000400                                     */
#define HRPWM_MCR_SYNCRSTM          HRPWM_MCR_SYNCRSTM_Msk                  /*!< Synchronization reset master                   */
#define HRPWM_MCR_SYNCIN_EN_Pos     (9U)
#define HRPWM_MCR_SYNCIN_EN_Msk     (0x1UL << HRPWM_MCR_SYNCIN_EN_Pos)      /*!< 0x00000200                                     */
#define HRPWM_MCR_SYNCIN_EN         HRPWM_MCR_SYNCIN_EN_Msk                 /*!< Synchronization input Enable                   */
#define HRPWM_MCR_SYNCIN_SRC_Pos    (8U)
#define HRPWM_MCR_SYNCIN_SRC_Msk    (0x1UL << HRPWM_MCR_SYNCIN_SRC_Pos)     /*!< 0x00000100                                     */
#define HRPWM_MCR_SYNCIN_SRC        HRPWM_MCR_SYNCIN_SRC_Msk                /*!< Synchronization input Source master            */
#define HRPWM_MCR_INTLVD_Pos        (6U)
#define HRPWM_MCR_INTLVD_Msk        (0x3UL << HRPWM_MCR_INTLVD_Pos)         /*!< 0x000000C0                                     */
#define HRPWM_MCR_INTLVD            HRPWM_MCR_INTLVD_Msk                    /*!< Interleaved mode                               */
#define HRPWM_MCR_INTLVD_0          (0x1UL << HRPWM_MCR_INTLVD_Pos)         /*!< 0x00000040                                     */
#define HRPWM_MCR_INTLVD_1          (0x2UL << HRPWM_MCR_INTLVD_Pos)         /*!< 0x00000080                                     */
#define HRPWM_MCR_HALF_Pos          (5U)
#define HRPWM_MCR_HALF_Msk          (0x1UL << HRPWM_MCR_HALF_Pos)           /*!< 0x00000020                                     */
#define HRPWM_MCR_HALF              HRPWM_MCR_HALF_Msk                      /*!< Half mode                                      */
#define HRPWM_MCR_RETRIG_Pos        (4U)
#define HRPWM_MCR_RETRIG_Msk        (0x1UL << HRPWM_MCR_RETRIG_Pos)         /*!< 0x00000010                                     */
#define HRPWM_MCR_RETRIG            HRPWM_MCR_RETRIG_Msk                    /*!< Rettrigreable mode                             */
#define HRPWM_MCR_CONT_Pos          (3U)
#define HRPWM_MCR_CONT_Msk          (0x1UL << HRPWM_MCR_CONT_Pos)           /*!< 0x00000008                                     */
#define HRPWM_MCR_CONT              HRPWM_MCR_CONT_Msk                      /*!< Continuous mode                                */
#define HRPWM_MCR_CKPSC_Pos         (0U)
#define HRPWM_MCR_CKPSC_Msk         (0x7UL << HRPWM_MCR_CKPSC_Pos)          /*!< 0x00000007                                     */
#define HRPWM_MCR_CKPSC             HRPWM_MCR_CKPSC_Msk                     /*!< Prescaler mask                                 */
#define HRPWM_MCR_CKPSC_0           (0x1UL << HRPWM_MCR_CKPSC_Pos)          /*!< 0x00000001                                     */
#define HRPWM_MCR_CKPSC_1           (0x2UL << HRPWM_MCR_CKPSC_Pos)          /*!< 0x00000002                                     */
#define HRPWM_MCR_CKPSC_2           (0x4UL << HRPWM_MCR_CKPSC_Pos)          /*!< 0x00000004                                     */

/*******************  Bit definition for HRPWM_MISR register  *****************/
#define HRPWM_MISR_MREP_Pos         (7U)
#define HRPWM_MISR_MREP_Msk         (0x1UL << HRPWM_MISR_MREP_Pos)          /*!< 0x00000080                                     */
#define HRPWM_MISR_MREP             HRPWM_MISR_MREP_Msk                     /*!< Master Repetition interrupt flag               */
#define HRPWM_MISR_MUPD_Pos         (6U)
#define HRPWM_MISR_MUPD_Msk         (0x1UL << HRPWM_MISR_MUPD_Pos)          /*!< 0x00000040                                     */
#define HRPWM_MISR_MUPD             HRPWM_MISR_MUPD_Msk                     /*!< Master update interrupt flag                   */
#define HRPWM_MISR_SYNC_Pos         (5U)
#define HRPWM_MISR_SYNC_Msk         (0x1UL << HRPWM_MISR_SYNC_Pos)          /*!< 0x00000020                                     */
#define HRPWM_MISR_SYNC             HRPWM_MISR_SYNC_Msk                     /*!< Synchronization input interrupt flag           */
#define HRPWM_MISR_MPER_Pos         (4U)
#define HRPWM_MISR_MPER_Msk         (0x1UL << HRPWM_MISR_MPER_Pos)          /*!< 0x00000010                                     */
#define HRPWM_MISR_MPER             HRPWM_MISR_MPER_Msk                     /*!< Master Period interrupt flag                   */
#define HRPWM_MISR_MCMPD_Pos        (3U)
#define HRPWM_MISR_MCMPD_Msk        (0x1UL << HRPWM_MISR_MCMPD_Pos)         /*!< 0x00000008                                     */
#define HRPWM_MISR_MCMPD            HRPWM_MISR_MCMPD_Msk                    /*!< Master compare D interrupt flag                */
#define HRPWM_MISR_MCMPC_Pos        (2U)
#define HRPWM_MISR_MCMPC_Msk        (0x1UL << HRPWM_MISR_MCMPC_Pos)         /*!< 0x00000004                                     */
#define HRPWM_MISR_MCMPC            HRPWM_MISR_MCMPC_Msk                    /*!< Master compare C interrupt flag                */
#define HRPWM_MISR_MCMPB_Pos        (1U)
#define HRPWM_MISR_MCMPB_Msk        (0x1UL << HRPWM_MISR_MCMPB_Pos)         /*!< 0x00000002                                     */
#define HRPWM_MISR_MCMPB            HRPWM_MISR_MCMPB_Msk                    /*!< Master compare B interrupt flag                */
#define HRPWM_MISR_MCMPA_Pos        (0U)
#define HRPWM_MISR_MCMPA_Msk        (0x1UL << HRPWM_MISR_MCMPA_Pos)         /*!< 0x00000001                                     */
#define HRPWM_MISR_MCMPA            HRPWM_MISR_MCMPA_Msk                    /*!< Master compare A interrupt flag                */

/*******************  Bit definition for HRPWM_MIER register  *****************/
#define HRPWM_MIER_MREPIE_Pos       (7U)
#define HRPWM_MIER_MREPIE_Msk       (0x1UL << HRPWM_MIER_MREPIE_Pos)        /*!< 0x00000080                                     */
#define HRPWM_MIER_MREPIE           HRPWM_MIER_MREPIE_Msk                   /*!< Master Repetition interrupt                    */
#define HRPWM_MIER_MUPDIE_Pos       (6U)
#define HRPWM_MIER_MUPDIE_Msk       (0x1UL << HRPWM_MIER_MUPDIE_Pos)        /*!< 0x00000040                                     */
#define HRPWM_MIER_MUPDIE           HRPWM_MIER_MUPDIE_Msk                   /*!< Master update interrupt                        */
#define HRPWM_MIER_SYNCIE_Pos       (5U)
#define HRPWM_MIER_SYNCIE_Msk       (0x1UL << HRPWM_MIER_SYNCIE_Pos)        /*!< 0x00000020                                     */
#define HRPWM_MIER_SYNCIE           HRPWM_MIER_SYNCIE_Msk                   /*!< Synchronization input interrupt                */
#define HRPWM_MIER_MPERIE_Pos       (4U)
#define HRPWM_MIER_MPERIE_Msk       (0x1UL << HRPWM_MIER_MPERIE_Pos)        /*!< 0x00000010                                     */
#define HRPWM_MIER_MPERIE           HRPWM_MIER_MPERIE_Msk                   /*!< Master Period interrupt                        */
#define HRPWM_MIER_MCMPDIE_Pos      (3U)
#define HRPWM_MIER_MCMPDIE_Msk      (0x1UL << HRPWM_MIER_MCMPDIE_Pos)       /*!< 0x00000008                                     */
#define HRPWM_MIER_MCMPDIE          HRPWM_MIER_MCMPDIE_Msk                  /*!< Master compare D interrupt                     */
#define HRPWM_MIER_MCMPCIE_Pos      (2U)
#define HRPWM_MIER_MCMPCIE_Msk      (0x1UL << HRPWM_MIER_MCMPCIE_Pos)       /*!< 0x00000004                                     */
#define HRPWM_MIER_MCMPCIE          HRPWM_MIER_MCMPCIE_Msk                  /*!< Master compare C interrupt                     */
#define HRPWM_MIER_MCMPBIE_Pos      (1U)
#define HRPWM_MIER_MCMPBIE_Msk      (0x1UL << HRPWM_MIER_MCMPBIE_Pos)       /*!< 0x00000002                                     */
#define HRPWM_MIER_MCMPBIE          HRPWM_MIER_MCMPBIE_Msk                  /*!< Master compare B interrupt                     */
#define HRPWM_MIER_MCMPAIE_Pos      (0U)
#define HRPWM_MIER_MCMPAIE_Msk      (0x1UL << HRPWM_MIER_MCMPAIE_Pos)       /*!< 0x00000001                                     */
#define HRPWM_MIER_MCMPAIE          HRPWM_MIER_MCMPAIE_Msk                  /*!< Master compare A interrupt                     */

/******************  Bit definition for HRPWM_MCNTR register  *****************/
#define HRPWM_MCNTR_MREP_Pos        (24U)
#define HRPWM_MCNTR_MREP_Msk        (0xFFUL << HRPWM_MCNTR_MREP_Pos)        /*!< 0xFF000000                                     */
#define HRPWM_MCNTR_MREP            HRPWM_MCNTR_MREP_Msk                    /*!<Repetition Value                                */
#define HRPWM_MCNTR_CNTWR_Pos       (19U)
#define HRPWM_MCNTR_CNTWR_Msk       (0x1UL << HRPWM_MCNTR_CNTWR_Pos)        /*!< 0x00080000                                     */
#define HRPWM_MCNTR_CNTWR           HRPWM_MCNTR_CNTWR_Msk                   /*!<Write Counter Value                             */
#define HRPWM_MCNTR_CNTRD_Pos       (18U)
#define HRPWM_MCNTR_CNTRD_Msk       (0x1UL << HRPWM_MCNTR_CNTRD_Pos)        /*!< 0x00040000                                     */
#define HRPWM_MCNTR_CNTRD           HRPWM_MCNTR_CNTRD_Msk                   /*!<Read Counter Value                              */
#define HRPWM_MCNTR_MCNT_Pos        (0U)
#define HRPWM_MCNTR_MCNT_Msk        (0xFFFFUL << HRPWM_MCNTR_MCNT_Pos)      /*!< 0x0000FFFF                                     */
#define HRPWM_MCNTR_MCNT            HRPWM_MCNTR_MCNT_Msk                    /*!<Counter Value                                   */

/*******************  Bit definition for HRPWM_MPER register  *****************/
#define HRPWM_MPER_MPER_Pos         (0U)
#define HRPWM_MPER_MPER_Msk         (0x0000FFFFUL << HRPWM_MPER_MPER_Pos)   /*!< 0x0000FFFF                                     */
#define HRPWM_MPER_MPER             HRPWM_MPER_MPER_Msk                     /*!< Period Value                                   */

/******************  Bit definition for HRPWM_MCMPAR register  ****************/
#define HRPWM_MCMPAR_MCMPA_Pos      (0U)
#define HRPWM_MCMPAR_MCMPA_Msk      (0x0000FFFFUL << HRPWM_MCMPAR_MCMPA_Pos)/*!< 0x0000FFFF                                     */
#define HRPWM_MCMPAR_MCMPA          HRPWM_MCMPAR_MCMPA_Msk                  /*!<Compare A Value                                 */

/******************  Bit definition for HRPWM_MCMPBR register  ****************/
#define HRPWM_MCMPBR_MCMPB_Pos      (0U)
#define HRPWM_MCMPBR_MCMPB_Msk      (0x0000FFFFUL << HRPWM_MCMPBR_MCMPB_Pos)/*!< 0x0000FFFF                                     */
#define HRPWM_MCMPBR_MCMPB          HRPWM_MCMPBR_MCMPB                      /*!<Compare B Value                                 */

/******************  Bit definition for HRPWM_MCMPCR register  ****************/
#define HRPWM_MCMPCR_MCMPC_Pos      (0U)
#define HRPWM_MCMPCR_MCMPC_Msk      (0x0000FFFFUL << HRPWM_MCMPCR_MCMPC_Pos)/*!< 0x0000FFFF                                     */
#define HRPWM_MCMPCR_MCMPC          HRPWM_MCMPCR_MCMPC_Msk                  /*!<Compare C Value                                 */

/******************  Bit definition for HRPWM_MCMPDR register  ****************/
#define HRPWM_MCMPDR_MCMPD_Pos      (0U)
#define HRPWM_MCMPDR_MCMPD_Msk      (0x0000FFFFUL << HRPWM_MCMPDR_MCMPD_Pos)/*!< 0x0000FFFF                                     */
#define HRPWM_MCMPDR_MCMPD          HRPWM_MCMPDR_MCMPD_Msk                  /*!<Compare D Value                                 */

/*****************  Bit definition for HRPWM_PWMxCR0 register  ****************/
#define HRPWM_CR0_PREEN_Pos         (25U)
#define HRPWM_CR0_PREEN_Msk         (0x1UL << HRPWM_CR0_PREEN_Pos)          /*!< 0x02000000                                     */
#define HRPWM_CR0_PREEN             HRPWM_CR0_PREEN_Msk                     /*!< Slave preload enable                           */
#define HRPWM_CR0_UPDREP_Pos        (24U)
#define HRPWM_CR0_UPDREP_Msk        (0x1UL << HRPWM_CR0_UPDREP_Pos)         /*!< 0x01000000                                     */
#define HRPWM_CR0_UPDREP            HRPWM_CR0_UPDREP_Msk                    /*!< Slave repetition update                        */
#define HRPWM_CR0_UPDRST_Pos        (23U)
#define HRPWM_CR0_UPDRST_Msk        (0x1UL << HRPWM_CR0_UPDRST_Pos)         /*!< 0x00800000                                     */
#define HRPWM_CR0_UPDRST            HRPWM_CR0_UPDRST_Msk                    /*!< Slave reset update                             */
#define HRPWM_CR0_UPD5_Pos          (22U)
#define HRPWM_CR0_UPD5_Msk          (0x1UL << HRPWM_CR0_UPD5_Pos)           /*!< 0x00400000                                     */
#define HRPWM_CR0_UPD5              HRPWM_CR0_UPD5_Msk                      /*!< Slave Timer 5 update reserved for PWM 5        */
#define HRPWM_CR0_UPD4_Pos          (21U)
#define HRPWM_CR0_UPD4_Msk          (0x1UL << HRPWM_CR0_UPD4_Pos)           /*!< 0x00200000                                     */
#define HRPWM_CR0_UPD4              HRPWM_CR0_UPD4_Msk                      /*!< Slave Timer 4 update reserved for PWM 4        */
#define HRPWM_CR0_UPD3_Pos          (20U)
#define HRPWM_CR0_UPD3_Msk          (0x1UL << HRPWM_CR0_UPD3_Pos)           /*!< 0x00100000                                     */
#define HRPWM_CR0_UPD3              HRPWM_CR0_UPD3_Msk                      /*!< Slave Timer 3 update reserved for PWM 3        */
#define HRPWM_CR0_UPD2_Pos          (19U)
#define HRPWM_CR0_UPD2_Msk          (0x1UL << HRPWM_CR0_UPD2_Pos)           /*!< 0x00080000                                     */
#define HRPWM_CR0_UPD2              HRPWM_CR0_UPD2_Msk                      /*!< Slave Timer 2 update reserved for PWM 2        */
#define HRPWM_CR0_UPD1_Pos          (18U)
#define HRPWM_CR0_UPD1_Msk          (0x1UL << HRPWM_CR0_UPD1_Pos)           /*!< 0x00040000                                     */
#define HRPWM_CR0_UPD1              HRPWM_CR0_UPD1_Msk                      /*!< Slave Timer 1 update reserved for PWM 1        */
#define HRPWM_CR0_UPD0_Pos          (17U)
#define HRPWM_CR0_UPD0_Msk          (0x1UL << HRPWM_CR0_UPD0_Pos)           /*!< 0x00020000                                     */
#define HRPWM_CR0_UPD0              HRPWM_CR0_UPD0_Msk                      /*!< Slave Timer 0 update reserved for PWM 0        */
#define HRPWM_CR0_MUPD_Pos          (16U)
#define HRPWM_CR0_MUPD_Msk          (0x1UL << HRPWM_CR0_MUPD_Pos)           /*!< 0x00010000                                     */
#define HRPWM_CR0_MUPD              HRPWM_CR0_MUPD_Msk                      /*!< Master Update                                  */
#define HRPWM_CR0_SYNCSTRT_Pos      (11U)
#define HRPWM_CR0_SYNCSTRT_Msk      (0x1UL << HRPWM_CR0_SYNCSTRT_Pos)       /*!< 0x00000800                                     */
#define HRPWM_CR0_SYNCSTRT          HRPWM_CR0_SYNCSTRT_Msk                  /*!< Slave synchronization starts                   */
#define HRPWM_CR0_SYNCRST_Pos       (10U)
#define HRPWM_CR0_SYNCRST_Msk       (0x1UL << HRPWM_CR0_SYNCRST_Pos)        /*!< 0x00000400                                     */
#define HRPWM_CR0_SYNCRST           HRPWM_CR0_SYNCRST_Msk                   /*!< Slave synchronization resets                   */
#define HRPWM_CR0_RSYNCU_Pos        (9U)
#define HRPWM_CR0_RSYNCU_Msk        (0x1UL << HRPWM_CR0_RSYNCU_Pos)         /*!< 0x00000200                                     */
#define HRPWM_CR0_RSYNCU            HRPWM_CR0_RSYNCU_Msk                    /*!< Resynchronization update                       */
#define HRPWM_CR0_PSHPLL_Pos        (8U)
#define HRPWM_CR0_PSHPLL_Msk        (0x1UL << HRPWM_CR0_PSHPLL_Pos)         /*!< 0x00000100                                     */
#define HRPWM_CR0_PSHPLL            HRPWM_CR0_PSHPLL_Msk                    /*!< Slave push-pull mode                           */
#define HRPWM_CR0_INTLVD_Pos        (6U)
#define HRPWM_CR0_INTLVD_Msk        (0x3UL << HRPWM_CR0_INTLVD_Pos)         /*!< 0x000000C0                                     */
#define HRPWM_CR0_INTLVD            HRPWM_CR0_INTLVD_Msk                    /*!< Interleaved mode                               */
#define HRPWM_CR0_INTLVD_0          (0x1UL << HRPWM_CR0_INTLVD_Pos)         /*!< 0x00000040                                     */
#define HRPWM_CR0_INTLVD_1          (0x2UL << HRPWM_CR0_INTLVD_Pos)         /*!< 0x00000080                                     */
#define HRPWM_CR0_HALF_Pos          (5U)
#define HRPWM_CR0_HALF_Msk          (0x1UL << HRPWM_CR0_HALF_Pos)           /*!< 0x00000020                                     */
#define HRPWM_CR0_HALF              HRPWM_CR0_HALF_Msk                      /*!< Slave Half mode                                */
#define HRPWM_CR0_RETRIG_Pos        (4U)
#define HRPWM_CR0_RETRIG_Msk        (0x1UL << HRPWM_CR0_RETRIG_Pos)         /*!< 0x00000010                                     */
#define HRPWM_CR0_RETRIG            HRPWM_CR0_RETRIG_Msk                    /*!< Slave Retrigreable mode                        */
#define HRPWM_CR0_CONT_Pos          (3U)
#define HRPWM_CR0_CONT_Msk          (0x1UL << HRPWM_CR0_CONT_Pos)           /*!< 0x00000008                                     */
#define HRPWM_CR0_CONT              HRPWM_CR0_CONT_Msk                      /*!< Slave continuous mode                          */
#define HRPWM_CR0_CKPSC_Pos         (0U)
#define HRPWM_CR0_CKPSC_Msk         (0x7UL << HRPWM_CR0_CKPSC_Pos)          /*!< 0x00000007                                     */
#define HRPWM_CR0_CKPSC             HRPWM_CR0_CKPSC_Msk                     /*!< Slave prescaler mask                           */
#define HRPWM_CR0_CKPSC_0           (0x1UL << HRPWM_CR0_CKPSC_Pos)          /*!< 0x00000001                                     */
#define HRPWM_CR0_CKPSC_1           (0x2UL << HRPWM_CR0_CKPSC_Pos)          /*!< 0x00000002                                     */
#define HRPWM_CR0_CKPSC_2           (0x4UL << HRPWM_CR0_CKPSC_Pos)          /*!< 0x00000004                                     */

/*****************  Bit definition for HRPWM_PWMxCR1 register  ****************/
#define HRPWM_CR1_FLTROM_Pos        (14U)
#define HRPWM_CR1_FLTROM_Msk        (0x3UL << HRPWM_CR1_FLTROM_Pos)         /*!< 0x000000C0                                     */
#define HRPWM_CR1_FLTROM            HRPWM_CR1_FLTROM_Msk                    /*!< Interleaved mode                               */
#define HRPWM_CR1_FLTROM_0          (0x1UL << HRPWM_CR1_FLTROM_Pos)         /*!< 0x00000040                                     */
#define HRPWM_CR1_FLTROM_1          (0x2UL << HRPWM_CR1_FLTROM_Pos)         /*!< 0x00000080                                     */
#define HRPWM_CR1_EEVROM_Pos        (12U)
#define HRPWM_CR1_EEVROM_Msk        (0x3UL << HRPWM_CR1_EEVROM_Pos)         /*!< 0x000000C0                                     */
#define HRPWM_CR1_EEVROM            HRPWM_CR1_EEVROM_Msk                    /*!< Interleaved mode                               */
#define HRPWM_CR1_EEVROM_0          (0x1UL << HRPWM_CR1_EEVROM_Pos)         /*!< 0x00000040                                     */
#define HRPWM_CR1_EEVROM_1          (0x2UL << HRPWM_CR1_EEVROM_Pos)         /*!< 0x00000080                                     */
#define HRPWM_CR1_ADROM_Pos         (10U)
#define HRPWM_CR1_ADROM_Msk         (0x3UL << HRPWM_CR1_ADROM_Pos)          /*!< 0x000000C0                                     */
#define HRPWM_CR1_ADROM             HRPWM_CR1_ADROM_Msk                     /*!< Interleaved mode                               */
#define HRPWM_CR1_ADROM_0           (0x1UL << HRPWM_CR1_ADROM_Pos)          /*!< 0x00000040                                     */
#define HRPWM_CR1_ADROM_1           (0x2UL << HRPWM_CR1_ADROM_Pos)          /*!< 0x00000080                                     */
#define HRPWM_CR1_OUTROM_Pos        (8U)
#define HRPWM_CR1_OUTROM_Msk        (0x3UL << HRPWM_CR1_OUTROM_Pos)         /*!< 0x000000C0                                     */
#define HRPWM_CR1_OUTROM            HRPWM_CR1_OUTROM_Msk                    /*!< Interleaved mode                               */
#define HRPWM_CR1_OUTROM_0          (0x1UL << HRPWM_CR1_OUTROM_Pos)         /*!< 0x00000040                                     */
#define HRPWM_CR1_OUTROM_1          (0x2UL << HRPWM_CR1_OUTROM_Pos)         /*!< 0x00000080                                     */
#define HRPWM_CR1_ROM_Pos           (6U)
#define HRPWM_CR1_ROM_Msk           (0x3UL << HRPWM_CR1_ROM_Pos)            /*!< 0x000000C0                                     */
#define HRPWM_CR1_ROM               HRPWM_CR1_ROM_Msk                       /*!< Interleaved mode                               */
#define HRPWM_CR1_ROM_0             (0x1UL << HRPWM_CR1_ROM_Pos)            /*!< 0x00000040                                     */
#define HRPWM_CR1_ROM_1             (0x2UL << HRPWM_CR1_ROM_Pos)            /*!< 0x00000080                                     */
#define HRPWM_CR1_UDM_Pos           (4U)
#define HRPWM_CR1_UDM_Msk           (0x1UL << HRPWM_CR1_UDM_Pos)            /*!< 0x00000020                                     */
#define HRPWM_CR1_UDM               HRPWM_CR1_UDM_Msk                       /*!< Slave Half mode                                */
#define HRPWM_CR1_DCDR_Pos          (2U)
#define HRPWM_CR1_DCDR_Msk          (0x1UL << HRPWM_CR1_DCDR_Pos)           /*!< 0x00000010                                     */
#define HRPWM_CR1_DCDR              HRPWM_CR1_DCDR_Msk                      /*!< Slave Retrigreable mode                        */
#define HRPWM_CR1_DCDS_Pos          (1U)
#define HRPWM_CR1_DCDS_Msk          (0x1UL << HRPWM_CR1_DCDS_Pos)           /*!< 0x00000008                                     */
#define HRPWM_CR1_DCDS              HRPWM_CR1_DCDS_Msk                      /*!< Slave continuous mode                          */
#define HRPWM_CR1_DCDE_Pos          (0U)
#define HRPWM_CR1_DCDE_Msk          (0x1UL << HRPWM_CR1_DCDE_Pos)           /*!< 0x00000001                                     */
#define HRPWM_CR1_DCDE              HRPWM_CR1_DCDE_Msk                      /*!< Slave prescaler mask                           */

/*****************  Bit definition for HRPWM_PWMxISR register  ****************/
#define HRPWM_ISR_REP_Pos           (11U)
#define HRPWM_ISR_REP_Msk           (0x1UL << HRPWM_ISR_REP_Pos)            /*!< 0x00000800                                     */
#define HRPWM_ISR_REP               HRPWM_ISR_REP_Msk                       /*!< Slave repetition interrupt Flag                */
#define HRPWM_ISR_RST_Pos           (10U)
#define HRPWM_ISR_RST_Msk           (0x1UL << HRPWM_ISR_RST_Pos)            /*!< 0x00000400                                     */
#define HRPWM_ISR_RST               HRPWM_ISR_RST_Msk                       /*!< Slave reset interrupt Flag                     */
#define HRPWM_ISR_CLRB_Pos          (9U)
#define HRPWM_ISR_CLRB_Msk          (0x1UL << HRPWM_ISR_CLRB_Pos)           /*!< 0x00000200                                     */
#define HRPWM_ISR_CLRB              HRPWM_ISR_CLRB_Msk                      /*!< Slave output B reset interrupt Flag            */
#define HRPWM_ISR_SETB_Pos          (8U)
#define HRPWM_ISR_SETB_Msk          (0x1UL << HRPWM_ISR_SETB_Pos)           /*!< 0x00000100                                     */
#define HRPWM_ISR_SETB              HRPWM_ISR_SETB_Msk                      /*!< Slave output B set interrupt Flag              */
#define HRPWM_ISR_CLRA_Pos          (7U)
#define HRPWM_ISR_CLRA_Msk          (0x1UL << HRPWM_ISR_CLRA_Pos)           /*!< 0x00000080                                     */
#define HRPWM_ISR_CLRA              HRPWM_ISR_CLRA_Msk                      /*!< Slave output A reset interrupt Flag            */
#define HRPWM_ISR_SETA_Pos          (6U)
#define HRPWM_ISR_SETA_Msk          (0x1UL << HRPWM_ISR_SETA_Pos)           /*!< 0x00000040                                     */
#define HRPWM_ISR_SETA              HRPWM_ISR_SETA_Msk                      /*!< Slave output A set interrupt Flag              */
#define HRPWM_ISR_UPD_Pos           (5U)
#define HRPWM_ISR_UPD_Msk           (0x1UL << HRPWM_ISR_UPD_Pos)            /*!< 0x00000020                                     */
#define HRPWM_ISR_UPD               HRPWM_ISR_UPD_Msk                       /*!< Slave update interrupt Flag                    */
#define HRPWM_ISR_PER_Pos           (4U)
#define HRPWM_ISR_PER_Msk           (0x1UL << HRPWM_ISR_PER_Pos)            /*!< 0x00000010                                     */
#define HRPWM_ISR_PER               HRPWM_ISR_PER_Msk                       /*!< Slave Period interrupt Flag                    */
#define HRPWM_ISR_CMPD_Pos          (3U)
#define HRPWM_ISR_CMPD_Msk          (0x1UL << HRPWM_ISR_CMPD_Pos)           /*!< 0x00000008                                     */
#define HRPWM_ISR_CMPD              HRPWM_ISR_CMPD_Msk                      /*!< Slave compare D interrupt Flag                 */
#define HRPWM_ISR_CMPC_Pos          (2U)
#define HRPWM_ISR_CMPC_Msk          (0x1UL << HRPWM_ISR_CMPC_Pos)           /*!< 0x00000004                                     */
#define HRPWM_ISR_CMPC              HRPWM_ISR_CMPC_Msk                      /*!< Slave compare C interrupt Flag                 */
#define HRPWM_ISR_CMPB_Pos          (1U)
#define HRPWM_ISR_CMPB_Msk          (0x1UL << HRPWM_ISR_CMPB_Pos)           /*!< 0x00000002                                     */
#define HRPWM_ISR_CMPB              HRPWM_ISR_CMPB_Msk                      /*!< Slave compare B interrupt Flag                 */
#define HRPWM_ISR_CMPA_Pos          (0U)
#define HRPWM_ISR_CMPA_Msk          (0x1UL << HRPWM_ISR_CMPA_Pos)           /*!< 0x00000001                                     */
#define HRPWM_ISR_CMPA              HRPWM_ISR_CMPA_Msk                      /*!< Slave compare A interrupt Flag                 */

/*****************  Bit definition for HRPWM_PWMxIER register  ****************/
#define HRPWM_IER_REPIE_Pos         (11U)
#define HRPWM_IER_REPIE_Msk         (0x1UL << HRPWM_IER_REPIE_Pos)          /*!< 0x00000800                                     */
#define HRPWM_IER_REPIE             HRPWM_IER_REPIE_Msk                     /*!< Slave repetition interrupt enable              */
#define HRPWM_IER_RSTIE_Pos         (10U)
#define HRPWM_IER_RSTIE_Msk         (0x1UL << HRPWM_IER_RSTIE_Pos)          /*!< 0x00000400                                     */
#define HRPWM_IER_RSTIE             HRPWM_IER_RSTIE_Msk                     /*!< Slave reset interrupt enable                   */
#define HRPWM_IER_CLRBIE_Pos        (9U)
#define HRPWM_IER_CLRBIE_Msk        (0x1UL << HRPWM_IER_CLRBIE_Pos)         /*!< 0x00000200                                     */
#define HRPWM_IER_CLRBIE            HRPWM_IER_CLRBIE_Msk                    /*!< Slave output B reset interrupt enable          */
#define HRPWM_IER_SETBIE_Pos        (8U)
#define HRPWM_IER_SETBIE_Msk        (0x1UL << HRPWM_IER_SETBIE_Pos)         /*!< 0x00000100                                     */
#define HRPWM_IER_SETBIE            HRPWM_IER_SETBIE_Msk                    /*!< Slave output B set interrupt enable            */
#define HRPWM_IER_CLRAIE_Pos        (7U)
#define HRPWM_IER_CLRAIE_Msk        (0x1UL << HRPWM_IER_CLRAIE_Pos)         /*!< 0x00000080                                     */
#define HRPWM_IER_CLRAIE            HRPWM_IER_CLRAIE_Msk                    /*!< Slave output A reset interrupt enable          */
#define HRPWM_IER_SETAIE_Pos        (6U)
#define HRPWM_IER_SETAIE_Msk        (0x1UL << HRPWM_IER_SETAIE_Pos)         /*!< 0x00000040                                     */
#define HRPWM_IER_SETAIE            HRPWM_IER_SETAIE_Msk                    /*!< Slave output A set interrupt enable            */
#define HRPWM_IER_UPDIE_Pos         (5U)
#define HRPWM_IER_UPDIE_Msk         (0x1UL << HRPWM_IER_UPDIE_Pos)          /*!< 0x00000020                                     */
#define HRPWM_IER_UPDIE             HRPWM_IER_UPDIE_Msk                     /*!< Slave update interrupt enable                  */
#define HRPWM_IER_PERIE_Pos         (4U)
#define HRPWM_IER_PERIE_Msk         (0x1UL << HRPWM_IER_PERIE_Pos)          /*!< 0x00000010                                     */
#define HRPWM_IER_PERIE             HRPWM_IER_PERIE_Msk                     /*!< Slave Period interrupt enable                  */
#define HRPWM_IER_CMPDIE_Pos        (3U)
#define HRPWM_IER_CMPDIE_Msk        (0x1UL << HRPWM_IER_CMPDIE_Pos)         /*!< 0x00000008                                     */
#define HRPWM_IER_CMPDIE            HRPWM_IER_CMPDIE_Msk                    /*!< Slave compare D interrupt enable               */
#define HRPWM_IER_CMPCIE_Pos        (2U)
#define HRPWM_IER_CMPCIE_Msk        (0x1UL << HRPWM_IER_CMPCIE_Pos)         /*!< 0x00000004                                     */
#define HRPWM_IER_CMPCIE            HRPWM_IER_CMPCIE_Msk                    /*!< Slave compare C interrupt enable               */
#define HRPWM_IER_CMPBIE_Pos        (1U)
#define HRPWM_IER_CMPBIE_Msk        (0x1UL << HRPWM_IER_CMPBIE_Pos)         /*!< 0x00000002                                     */
#define HRPWM_IER_CMPBIE            HRPWM_IER_CMPBIE_Msk                    /*!< Slave compare B interrupt enable               */
#define HRPWM_IER_CMPAIE_Pos        (0U)
#define HRPWM_IER_CMPAIE_Msk        (0x1UL << HRPWM_IER_CMPAIE_Pos)         /*!< 0x00000001                                     */
#define HRPWM_IER_CMPAIE            HRPWM_IER_CMPAIE_Msk                    /*!< Slave compare A interrupt enable               */

/*****************  Bit definition for HRPWM_PWMxCNTR register  ***************/
#define HRPWM_CNTR_REP_Pos          (24U)
#define HRPWM_CNTR_REP_Msk          (0xFFUL << HRPWM_CNTR_REP_Pos)          /*!< 0xFF000000                                     */
#define HRPWM_CNTR_REP              HRPWM_CNTR_REP_Msk                      /*!<Repetition Value                                */

#define HRPWM_CNTR_CNTWR_Pos        (19U)
#define HRPWM_CNTR_CNTWR_Msk        (0x1UL << HRPWM_CNTR_CNTWR_Pos)         /*!< 0x00080000                                     */
#define HRPWM_CNTR_CNTWR            HRPWM_CNTR_CNTWR_Msk                    /*!<Write Counter Value                             */

#define HRPWM_CNTR_CNTRD_Pos        (18U)
#define HRPWM_CNTR_CNTRD_Msk        (0x1UL << HRPWM_CNTR_CNTRD_Pos)         /*!< 0x00040000                                     */
#define HRPWM_CNTR_CNTRD            HRPWM_CNTR_CNTRD_Msk                    /*!<Read Counter Value                              */

#define HRPWM_CNTR_CNT_Pos          (0U)
#define HRPWM_CNTR_CNT_Msk          (0xFFFFUL << HRPWM_CNTR_CNT_Pos)        /*!< 0x0000FFFF                                     */
#define HRPWM_CNTR_CNT              HRPWM_CNTR_CNT_Msk                      /*!<Counter Value                                   */

/*****************  Bit definition for HRPWM_PWMxPERR register  ***************/
#define HRPWM_PER_PER_Pos           (0U)
#define HRPWM_PER_PER_Msk           (0x0000FFFFUL << HRPWM_PER_PER_Pos)     /*!< 0x0000FFFF                                     */
#define HRPWM_PER_PER               HRPWM_PER_PER_Msk                       /*!< Period Value                                   */

/****************  Bit definition for HRPWM_PWMxCMPAR register  ***************/
#define HRPWM_CMPAR_CMPA_Pos        (0U)
#define HRPWM_CMPAR_CMPA_Msk        (0x0000FFFFUL << HRPWM_CMPAR_CMPA_Pos)  /*!< 0x0000FFFF                                     */
#define HRPWM_CMPAR_CMPA            HRPWM_CMPAR_CMPA_Msk                    /*!<Compare A Value                                 */

/****************  Bit definition for HRPWM_PWMxCMPBR register  ***************/
#define HRPWM_CMPBR_CMPB_Pos        (0U)
#define HRPWM_CMPBR_CMPB_Msk        (0x0000FFFFUL << HRPWM_CMPBR_CMPB_Pos)  /*!< 0x0000FFFF                                     */
#define HRPWM_CMPBR_CMPB            HRPWM_CMPBR_CMPB_Msk                    /*!<Compare B Value                                 */

/****************  Bit definition for HRPWM_PWMxCMPCR register  ***************/
#define HRPWM_CMPCR_CMPC_Pos        (0U)
#define HRPWM_CMPCR_CMPC_Msk        (0x0000FFFFUL << HRPWM_CMPCR_CMPC_Pos)  /*!< 0x0000FFFF                                     */
#define HRPWM_CMPCR_CMPC            HRPWM_CMPCR_CMPC_Msk                    /*!<Compare C Value                                 */

/****************  Bit definition for HRPWM_PWMxCMPDR register  ***************/
#define HRPWM_CMPDR_CMPD_Pos        (0U)
#define HRPWM_CMPDR_CMPD_Msk        (0x0000FFFFUL << HRPWM_CMPDR_CMPD_Pos)  /*!< 0x0000FFFF                                     */
#define HRPWM_CMPDR_CMPD            HRPWM_CMPDR_CMPD_Msk                    /*!<Compare D Value                                 */

/*****************  Bit definition for HRPWM_PWMxDTR register  ****************/
#define HRPWM_DTR_SDTF_Pos          (28U)
#define HRPWM_DTR_SDTF_Msk          (0x1UL << HRPWM_DTR_SDTF_Pos)           /*!< 0x10000000                                     */
#define HRPWM_DTR_SDTF              HRPWM_DTR_SDTF_Msk                      /*!< Sign dead time falling value                   */
#define HRPWM_DTR_DTF_Pos           (16U)
#define HRPWM_DTR_DTF_Msk           (0xFFFUL << HRPWM_DTR_DTF_Pos)          /*!< 0x0FFF0000                                     */
#define HRPWM_DTR_DTF               HRPWM_DTR_DTF_Msk                       /*!< Dead time falling value                        */
#define HRPWM_DTR_SDTR_Pos          (12U)
#define HRPWM_DTR_SDTR_Msk          (0x1UL << HRPWM_DTR_SDTR_Pos)           /*!< 0x00001000                                     */
#define HRPWM_DTR_SDTR              HRPWM_DTR_SDTR_Msk                      /*!< Sign dead time rising value                    */
#define HRPWM_DTR_DTR_Pos           (0U)
#define HRPWM_DTR_DTR_Msk           (0xFFFUL << HRPWM_DTR_DTR_Pos)          /*!< 0x00000FFF                                     */
#define HRPWM_DTR_DTR               HRPWM_DTR_DTR_Msk                       /*!< Dead time rising value                         */

/****************  Bit definition for HRPWM_PWMxSETAR register  ***************/
#define HRPWM_SETAR_SST_Pos         (18U)
#define HRPWM_SETAR_SST_Msk         (0x1UL << HRPWM_SETAR_SST_Pos)          /*!< 0x00040000                                     */
#define HRPWM_SETAR_SST             HRPWM_SETAR_SST_Msk                     /*!< software set trigger                           */
#define HRPWM_SETAR_RESYNC_Pos      (17U)
#define HRPWM_SETAR_RESYNC_Msk      (0x1UL << HRPWM_SETAR_RESYNC_Pos)       /*!< 0x00020000                                     */
#define HRPWM_SETAR_RESYNC          HRPWM_SETAR_RESYNC_Msk                  /*!< Timer X resynchronization                      */
#define HRPWM_SETAR_EXTEVNT5_Pos    (16U)
#define HRPWM_SETAR_EXTEVNT5_Msk    (0x1UL << HRPWM_SETAR_EXTEVNT5_Pos)     /*!< 0x00010000                                     */
#define HRPWM_SETAR_EXTEVNT5        HRPWM_SETAR_EXTEVNT5_Msk                /*!< Timer event 5                                  */
#define HRPWM_SETAR_EXTEVNT4_Pos    (15U)
#define HRPWM_SETAR_EXTEVNT4_Msk    (0x1UL << HRPWM_SETAR_EXTEVNT4_Pos)     /*!< 0x00008000                                     */
#define HRPWM_SETAR_EXTEVNT4        HRPWM_SETAR_EXTEVNT4_Msk                /*!< Timer event 4                                  */
#define HRPWM_SETAR_EXTEVNT3_Pos    (14U)
#define HRPWM_SETAR_EXTEVNT3_Msk    (0x1UL << HRPWM_SETAR_EXTEVNT3_Pos)     /*!< 0x00004000                                     */
#define HRPWM_SETAR_EXTEVNT3        HRPWM_SETAR_EXTEVNT3_Msk                /*!< Timer event 3                                  */
#define HRPWM_SETAR_EXTEVNT2_Pos    (13U)
#define HRPWM_SETAR_EXTEVNT2_Msk    (0x1UL << HRPWM_SETAR_EXTEVNT2_Pos)     /*!< 0x00002000                                     */
#define HRPWM_SETAR_EXTEVNT2        HRPWM_SETAR_EXTEVNT2_Msk                /*!< Timer event 2                                  */
#define HRPWM_SETAR_EXTEVNT1_Pos    (12U)
#define HRPWM_SETAR_EXTEVNT1_Msk    (0x1UL << HRPWM_SETAR_EXTEVNT1_Pos)     /*!< 0x00001000                                     */
#define HRPWM_SETAR_EXTEVNT1        HRPWM_SETAR_EXTEVNT1_Msk                /*!< Timer event 1                                  */
#define HRPWM_SETAR_EXTEVNT0_Pos    (11U)
#define HRPWM_SETAR_EXTEVNT0_Msk    (0x1UL << HRPWM_SETAR_EXTEVNT0_Pos)     /*!< 0x00000800                                     */
#define HRPWM_SETAR_EXTEVNT0        HRPWM_SETAR_EXTEVNT0_Msk                /*!< Timer event 0                                  */
#define HRPWM_SETAR_MSTPER_Pos      (10U)
#define HRPWM_SETAR_MSTPER_Msk      (0x1UL << HRPWM_SETAR_MSTPER_Pos)       /*!< 0x00000400                                     */
#define HRPWM_SETAR_MSTPER          HRPWM_SETAR_MSTPER_Msk                  /*!< Master period                                  */
#define HRPWM_SETAR_MSTCMPD_Pos     (9U)
#define HRPWM_SETAR_MSTCMPD_Msk     (0x1UL << HRPWM_SETAR_MSTCMPD_Pos)      /*!< 0x00000200                                     */
#define HRPWM_SETAR_MSTCMPD         HRPWM_SETAR_MSTCMPD_Msk                 /*!< Master compare D                               */
#define HRPWM_SETAR_MSTCMPC_Pos     (8U)
#define HRPWM_SETAR_MSTCMPC_Msk     (0x1UL << HRPWM_SETAR_MSTCMPC_Pos)      /*!< 0x00000100                                     */
#define HRPWM_SETAR_MSTCMPC         HRPWM_SETAR_MSTCMPC_Msk                 /*!< Master compare C                               */
#define HRPWM_SETAR_MSTCMPB_Pos     (7U)
#define HRPWM_SETAR_MSTCMPB_Msk     (0x1UL << HRPWM_SETAR_MSTCMPB_Pos)      /*!< 0x00000080                                     */
#define HRPWM_SETAR_MSTCMPB         HRPWM_SETAR_MSTCMPB_Msk                 /*!< Master compare B                               */
#define HRPWM_SETAR_MSTCMPA_Pos     (6U)
#define HRPWM_SETAR_MSTCMPA_Msk     (0x1UL << HRPWM_SETAR_MSTCMPA_Pos)      /*!< 0x00000040                                     */
#define HRPWM_SETAR_MSTCMPA         HRPWM_SETAR_MSTCMPA_Msk                 /*!< Master compare A                               */
#define HRPWM_SETAR_PER_Pos         (5U)
#define HRPWM_SETAR_PER_Msk         (0x1UL << HRPWM_SETAR_PER_Pos)          /*!< 0x00000020                                     */
#define HRPWM_SETAR_PER             HRPWM_SETAR_PER_Msk                     /*!< Timer X period                                 */
#define HRPWM_SETAR_CMPD_Pos        (4U)
#define HRPWM_SETAR_CMPD_Msk        (0x1UL << HRPWM_SETAR_CMPD_Pos)         /*!< 0x00000010                                     */
#define HRPWM_SETAR_CMPD            HRPWM_SETAR_CMPD_Msk                    /*!< Timer X compare D                              */
#define HRPWM_SETAR_CMPC_Pos        (3U)
#define HRPWM_SETAR_CMPC_Msk        (0x1UL << HRPWM_SETAR_CMPC_Pos)         /*!< 0x00000008                                     */
#define HRPWM_SETAR_CMPC            HRPWM_SETAR_CMPC_Msk                    /*!< Timer X compare C                              */
#define HRPWM_SETAR_CMPB_Pos        (2U)
#define HRPWM_SETAR_CMPB_Msk        (0x1UL << HRPWM_SETAR_CMPB_Pos)         /*!< 0x00000004                                     */
#define HRPWM_SETAR_CMPB            HRPWM_SETAR_CMPB_Msk                    /*!< Timer X compare B                              */
#define HRPWM_SETAR_CMPA_Pos        (1U)
#define HRPWM_SETAR_CMPA_Msk        (0x1UL << HRPWM_SETAR_CMPA_Pos)         /*!< 0x00000002                                     */
#define HRPWM_SETAR_CMPA            HRPWM_SETAR_CMPA_Msk                    /*!< Timer X compare A                              */
#define HRPWM_SETAR_UPD_Pos         (0U)
#define HRPWM_SETAR_UPD_Msk         (0x1UL << HRPWM_SETAR_UPD_Pos)          /*!< 0x00000001                                     */
#define HRPWM_SETAR_UPD             HRPWM_SETAR_UPD_Msk                     /*!< Register update (transfer preload to active)   */

/****************  Bit definition for HRPWM_PWMxCLRAR register  ***************/
#define HRPWM_CLRAR_SST_Pos         (18U)
#define HRPWM_CLRAR_SST_Msk         (0x1UL << HRPWM_CLRAR_SST_Pos)          /*!< 0x00040000                                     */
#define HRPWM_CLRAR_SST             HRPWM_CLRAR_SST_Msk                     /*!< software set trigger                           */
#define HRPWM_CLRAR_RESYNC_Pos      (17U)
#define HRPWM_CLRAR_RESYNC_Msk      (0x1UL << HRPWM_CLRAR_RESYNC_Pos)       /*!< 0x00020000                                     */
#define HRPWM_CLRAR_RESYNC          HRPWM_CLRAR_RESYNC_Msk                  /*!< Timer X resynchronization                      */
#define HRPWM_CLRAR_EXTEVNT5_Pos    (16U)
#define HRPWM_CLRAR_EXTEVNT5_Msk    (0x1UL << HRPWM_CLRAR_EXTEVNT5_Pos)     /*!< 0x00010000                                     */
#define HRPWM_CLRAR_EXTEVNT5        HRPWM_CLRAR_EXTEVNT5_Msk                /*!< Timer event 5                                  */
#define HRPWM_CLRAR_EXTEVNT4_Pos    (15U)
#define HRPWM_CLRAR_EXTEVNT4_Msk    (0x1UL << HRPWM_CLRAR_EXTEVNT4_Pos)     /*!< 0x00008000                                     */
#define HRPWM_CLRAR_EXTEVNT4        HRPWM_CLRAR_EXTEVNT4_Msk                /*!< Timer event 4                                  */
#define HRPWM_CLRAR_EXTEVNT3_Pos    (14U)
#define HRPWM_CLRAR_EXTEVNT3_Msk    (0x1UL << HRPWM_CLRAR_EXTEVNT3_Pos)     /*!< 0x00004000                                     */
#define HRPWM_CLRAR_EXTEVNT3        HRPWM_CLRAR_EXTEVNT3_Msk                /*!< Timer event 3                                  */
#define HRPWM_CLRAR_EXTEVNT2_Pos    (13U)
#define HRPWM_CLRAR_EXTEVNT2_Msk    (0x1UL << HRPWM_CLRAR_EXTEVNT2_Pos)     /*!< 0x00002000                                     */
#define HRPWM_CLRAR_EXTEVNT2        HRPWM_CLRAR_EXTEVNT2_Msk                /*!< Timer event 2                                  */
#define HRPWM_CLRAR_EXTEVNT1_Pos    (12U)
#define HRPWM_CLRAR_EXTEVNT1_Msk    (0x1UL << HRPWM_CLRAR_EXTEVNT1_Pos)     /*!< 0x00001000                                     */
#define HRPWM_CLRAR_EXTEVNT1        HRPWM_CLRAR_EXTEVNT1_Msk                /*!< Timer event 1                                  */
#define HRPWM_CLRAR_EXTEVNT0_Pos    (11U)
#define HRPWM_CLRAR_EXTEVNT0_Msk    (0x1UL << HRPWM_CLRAR_EXTEVNT0_Pos)     /*!< 0x00000800                                     */
#define HRPWM_CLRAR_EXTEVNT0        HRPWM_CLRAR_EXTEVNT0_Msk                /*!< Timer event 0                                  */
#define HRPWM_CLRAR_MSTPER_Pos      (10U)
#define HRPWM_CLRAR_MSTPER_Msk      (0x1UL << HRPWM_CLRAR_MSTPER_Pos)       /*!< 0x00000400                                     */
#define HRPWM_CLRAR_MSTPER          HRPWM_CLRAR_MSTPER_Msk                  /*!< Master period                                  */
#define HRPWM_CLRAR_MSTCMPD_Pos     (9U)
#define HRPWM_CLRAR_MSTCMPD_Msk     (0x1UL << HRPWM_CLRAR_MSTCMPD_Pos)      /*!< 0x00000200                                     */
#define HRPWM_CLRAR_MSTCMPD         HRPWM_CLRAR_MSTCMPD_Msk                 /*!< Master compare D                               */
#define HRPWM_CLRAR_MSTCMPC_Pos     (8U)
#define HRPWM_CLRAR_MSTCMPC_Msk     (0x1UL << HRPWM_CLRAR_MSTCMPC_Pos)      /*!< 0x00000100                                     */
#define HRPWM_CLRAR_MSTCMPC         HRPWM_CLRAR_MSTCMPC_Msk                 /*!< Master compare C                               */
#define HRPWM_CLRAR_MSTCMPB_Pos     (7U)
#define HRPWM_CLRAR_MSTCMPB_Msk     (0x1UL << HRPWM_CLRAR_MSTCMPB_Pos)      /*!< 0x00000080                                     */
#define HRPWM_CLRAR_MSTCMPB         HRPWM_CLRAR_MSTCMPB_Msk                 /*!< Master compare B                               */
#define HRPWM_CLRAR_MSTCMPA_Pos     (6U)
#define HRPWM_CLRAR_MSTCMPA_Msk     (0x1UL << HRPWM_CLRAR_MSTCMPA_Pos)      /*!< 0x00000040                                     */
#define HRPWM_CLRAR_MSTCMPA         HRPWM_CLRAR_MSTCMPA_Msk                 /*!< Master compare A                               */
#define HRPWM_CLRAR_PER_Pos         (5U)
#define HRPWM_CLRAR_PER_Msk         (0x1UL << HRPWM_CLRAR_PER_Pos)          /*!< 0x00000020                                     */
#define HRPWM_CLRAR_PER             HRPWM_CLRAR_PER_Msk                     /*!< Timer X period                                 */
#define HRPWM_CLRAR_CMPD_Pos        (4U)
#define HRPWM_CLRAR_CMPD_Msk        (0x1UL << HRPWM_CLRAR_CMPD_Pos)         /*!< 0x00000010                                     */
#define HRPWM_CLRAR_CMPD            HRPWM_CLRAR_CMPD_Msk                    /*!< Timer X compare D                              */
#define HRPWM_CLRAR_CMPC_Pos        (3U)
#define HRPWM_CLRAR_CMPC_Msk        (0x1UL << HRPWM_CLRAR_CMPC_Pos)         /*!< 0x00000008                                     */
#define HRPWM_CLRAR_CMPC            HRPWM_CLRAR_CMPC_Msk                    /*!< Timer X compare C                              */
#define HRPWM_CLRAR_CMPB_Pos        (2U)
#define HRPWM_CLRAR_CMPB_Msk        (0x1UL << HRPWM_CLRAR_CMPB_Pos)         /*!< 0x00000004                                     */
#define HRPWM_CLRAR_CMPB            HRPWM_CLRAR_CMPB_Msk                    /*!< Timer X compare B                              */
#define HRPWM_CLRAR_CMPA_Pos        (1U)
#define HRPWM_CLRAR_CMPA_Msk        (0x1UL << HRPWM_CLRAR_CMPA_Pos)         /*!< 0x00000002                                     */
#define HRPWM_CLRAR_CMPA            HRPWM_CLRAR_CMPA_Msk                    /*!< Timer X compare A                              */
#define HRPWM_CLRAR_UPD_Pos         (0U)
#define HRPWM_CLRAR_UPD_Msk         (0x1UL << HRPWM_CLRAR_UPD_Pos)          /*!< 0x00000001                                     */
#define HRPWM_CLRAR_UPD             HRPWM_CLRAR_UPD_Msk                     /*!< Register update (transfer preload to active)   */

/****************  Bit definition for HRPWM_PWMxSETBR register  ***************/
#define HRPWM_SETBR_SST_Pos         (18U)
#define HRPWM_SETBR_SST_Msk         (0x1UL << HRPWM_SETBR_SST_Pos)          /*!< 0x00040000                                     */
#define HRPWM_SETBR_SST             HRPWM_SETBR_SST_Msk                     /*!< software set trigger                           */
#define HRPWM_SETBR_RESYNC_Pos      (17U)
#define HRPWM_SETBR_RESYNC_Msk      (0x1UL << HRPWM_SETBR_RESYNC_Pos)       /*!< 0x00020000                                     */
#define HRPWM_SETBR_RESYNC          HRPWM_SETBR_RESYNC_Msk                  /*!< Timer X resynchronization                      */
#define HRPWM_SETBR_EXTEVNT5_Pos    (16U)
#define HRPWM_SETBR_EXTEVNT5_Msk    (0x1UL << HRPWM_SETBR_EXTEVNT5_Pos)     /*!< 0x00010000                                     */
#define HRPWM_SETBR_EXTEVNT5        HRPWM_SETBR_EXTEVNT5_Msk                /*!< Timer event 5                                  */
#define HRPWM_SETBR_EXTEVNT4_Pos    (15U)
#define HRPWM_SETBR_EXTEVNT4_Msk    (0x1UL << HRPWM_SETBR_EXTEVNT4_Pos)     /*!< 0x00008000                                     */
#define HRPWM_SETBR_EXTEVNT4        HRPWM_SETBR_EXTEVNT4_Msk                /*!< Timer event 4                                  */
#define HRPWM_SETBR_EXTEVNT3_Pos    (14U)
#define HRPWM_SETBR_EXTEVNT3_Msk    (0x1UL << HRPWM_SETBR_EXTEVNT3_Pos)     /*!< 0x00004000                                     */
#define HRPWM_SETBR_EXTEVNT3        HRPWM_SETBR_EXTEVNT3_Msk                /*!< Timer event 3                                  */
#define HRPWM_SETBR_EXTEVNT2_Pos    (13U)
#define HRPWM_SETBR_EXTEVNT2_Msk    (0x1UL << HRPWM_SETBR_EXTEVNT2_Pos)     /*!< 0x00002000                                     */
#define HRPWM_SETBR_EXTEVNT2        HRPWM_SETBR_EXTEVNT2_Msk                /*!< Timer event 2                                  */
#define HRPWM_SETBR_EXTEVNT1_Pos    (12U)
#define HRPWM_SETBR_EXTEVNT1_Msk    (0x1UL << HRPWM_SETBR_EXTEVNT1_Pos)     /*!< 0x00001000                                     */
#define HRPWM_SETBR_EXTEVNT1        HRPWM_SETBR_EXTEVNT1_Msk                /*!< Timer event 1                                  */
#define HRPWM_SETBR_EXTEVNT0_Pos    (11U)
#define HRPWM_SETBR_EXTEVNT0_Msk    (0x1UL << HRPWM_SETBR_EXTEVNT0_Pos)     /*!< 0x00000800                                     */
#define HRPWM_SETBR_EXTEVNT0        HRPWM_SETBR_EXTEVNT0_Msk                /*!< Timer event 0                                  */
#define HRPWM_SETBR_MSTPER_Pos      (10U)
#define HRPWM_SETBR_MSTPER_Msk      (0x1UL << HRPWM_SETBR_MSTPER_Pos)       /*!< 0x00000400                                     */
#define HRPWM_SETBR_MSTPER          HRPWM_SETBR_MSTPER_Msk                  /*!< Master period                                  */
#define HRPWM_SETBR_MSTCMPD_Pos     (9U)
#define HRPWM_SETBR_MSTCMPD_Msk     (0x1UL << HRPWM_SETBR_MSTCMPD_Pos)      /*!< 0x00000200                                     */
#define HRPWM_SETBR_MSTCMPD         HRPWM_SETBR_MSTCMPD_Msk                 /*!< Master compare D                               */
#define HRPWM_SETBR_MSTCMPC_Pos     (8U)
#define HRPWM_SETBR_MSTCMPC_Msk     (0x1UL << HRPWM_SETBR_MSTCMPC_Pos)      /*!< 0x00000100                                     */
#define HRPWM_SETBR_MSTCMPC         HRPWM_SETBR_MSTCMPC_Msk                 /*!< Master compare C                               */
#define HRPWM_SETBR_MSTCMPB_Pos     (7U)
#define HRPWM_SETBR_MSTCMPB_Msk     (0x1UL << HRPWM_SETBR_MSTCMPB_Pos)      /*!< 0x00000080                                     */
#define HRPWM_SETBR_MSTCMPB         HRPWM_SETBR_MSTCMPB_Msk                 /*!< Master compare B                               */
#define HRPWM_SETBR_MSTCMPA_Pos     (6U)
#define HRPWM_SETBR_MSTCMPA_Msk     (0x1UL << HRPWM_SETBR_MSTCMPA_Pos)      /*!< 0x00000040                                     */
#define HRPWM_SETBR_MSTCMPA         HRPWM_SETBR_MSTCMPA_Msk                 /*!< Master compare A                               */
#define HRPWM_SETBR_PER_Pos         (5U)
#define HRPWM_SETBR_PER_Msk         (0x1UL << HRPWM_SETBR_PER_Pos)          /*!< 0x00000020                                     */
#define HRPWM_SETBR_PER             HRPWM_SETBR_PER_Msk                     /*!< Timer X period                                 */
#define HRPWM_SETBR_CMPD_Pos        (4U)
#define HRPWM_SETBR_CMPD_Msk        (0x1UL << HRPWM_SETBR_CMPD_Pos)         /*!< 0x00000010                                     */
#define HRPWM_SETBR_CMPD            HRPWM_SETBR_CMPD_Msk                    /*!< Timer X compare D                              */
#define HRPWM_SETBR_CMPC_Pos        (3U)
#define HRPWM_SETBR_CMPC_Msk        (0x1UL << HRPWM_SETBR_CMPC_Pos)         /*!< 0x00000008                                     */
#define HRPWM_SETBR_CMPC            HRPWM_SETBR_CMPC_Msk                    /*!< Timer X compare C                              */
#define HRPWM_SETBR_CMPB_Pos        (2U)
#define HRPWM_SETBR_CMPB_Msk        (0x1UL << HRPWM_SETBR_CMPB_Pos)         /*!< 0x00000004                                     */
#define HRPWM_SETBR_CMPB            HRPWM_SETBR_CMPB_Msk                    /*!< Timer X compare B                              */
#define HRPWM_SETBR_CMPA_Pos        (1U)
#define HRPWM_SETBR_CMPA_Msk        (0x1UL << HRPWM_SETBR_CMPA_Pos)         /*!< 0x00000002                                     */
#define HRPWM_SETBR_CMPA            HRPWM_SETBR_CMPA_Msk                    /*!< Timer X compare A                              */
#define HRPWM_SETBR_UPD_Pos         (0U)
#define HRPWM_SETBR_UPD_Msk         (0x1UL << HRPWM_SETBR_UPD_Pos)          /*!< 0x00000001                                     */
#define HRPWM_SETBR_UPD             HRPWM_SETBR_UPD_Msk                     /*!< Register update (transfer preload to active)   */

/****************  Bit definition for HRPWM_PWMxCLRBR register  ***************/
#define HRPWM_CLRBR_SST_Pos         (18U)
#define HRPWM_CLRBR_SST_Msk         (0x1UL << HRPWM_CLRBR_SST_Pos)          /*!< 0x00040000                                     */
#define HRPWM_CLRBR_SST             HRPWM_CLRBR_SST_Msk                     /*!< software set trigger                           */
#define HRPWM_CLRBR_RESYNC_Pos      (17U)
#define HRPWM_CLRBR_RESYNC_Msk      (0x1UL << HRPWM_CLRBR_RESYNC_Pos)       /*!< 0x00020000                                     */
#define HRPWM_CLRBR_RESYNC          HRPWM_CLRBR_RESYNC_Msk                  /*!< Timer X resynchronization                      */
#define HRPWM_CLRBR_EXTEVNT5_Pos    (16U)
#define HRPWM_CLRBR_EXTEVNT5_Msk    (0x1UL << HRPWM_CLRBR_EXTEVNT5_Pos)     /*!< 0x00010000                                     */
#define HRPWM_CLRBR_EXTEVNT5        HRPWM_CLRBR_EXTEVNT5_Msk                /*!< Timer event 5                                  */
#define HRPWM_CLRBR_EXTEVNT4_Pos    (15U)
#define HRPWM_CLRBR_EXTEVNT4_Msk    (0x1UL << HRPWM_CLRBR_EXTEVNT4_Pos)     /*!< 0x00008000                                     */
#define HRPWM_CLRBR_EXTEVNT4        HRPWM_CLRBR_EXTEVNT4_Msk                /*!< Timer event 4                                  */
#define HRPWM_CLRBR_EXTEVNT3_Pos    (14U)
#define HRPWM_CLRBR_EXTEVNT3_Msk    (0x1UL << HRPWM_CLRBR_EXTEVNT3_Pos)     /*!< 0x00004000                                     */
#define HRPWM_CLRBR_EXTEVNT3        HRPWM_CLRBR_EXTEVNT3_Msk                /*!< Timer event 3                                  */
#define HRPWM_CLRBR_EXTEVNT2_Pos    (13U)
#define HRPWM_CLRBR_EXTEVNT2_Msk    (0x1UL << HRPWM_CLRBR_EXTEVNT2_Pos)     /*!< 0x00002000                                     */
#define HRPWM_CLRBR_EXTEVNT2        HRPWM_CLRBR_EXTEVNT2_Msk                /*!< Timer event 2                                  */
#define HRPWM_CLRBR_EXTEVNT1_Pos    (12U)
#define HRPWM_CLRBR_EXTEVNT1_Msk    (0x1UL << HRPWM_CLRBR_EXTEVNT1_Pos)     /*!< 0x00001000                                     */
#define HRPWM_CLRBR_EXTEVNT1        HRPWM_CLRBR_EXTEVNT1_Msk                /*!< Timer event 1                                  */
#define HRPWM_CLRBR_EXTEVNT0_Pos    (11U)
#define HRPWM_CLRBR_EXTEVNT0_Msk    (0x1UL << HRPWM_CLRBR_EXTEVNT0_Pos)     /*!< 0x00000800                                     */
#define HRPWM_CLRBR_EXTEVNT0        HRPWM_CLRBR_EXTEVNT0_Msk                /*!< Timer event 0                                  */
#define HRPWM_CLRBR_MSTPER_Pos      (10U)
#define HRPWM_CLRBR_MSTPER_Msk      (0x1UL << HRPWM_CLRBR_MSTPER_Pos)       /*!< 0x00000400                                     */
#define HRPWM_CLRBR_MSTPER          HRPWM_CLRBR_MSTPER_Msk                  /*!< Master period                                  */
#define HRPWM_CLRBR_MSTCMPD_Pos     (9U)
#define HRPWM_CLRBR_MSTCMPD_Msk     (0x1UL << HRPWM_CLRBR_MSTCMPD_Pos)      /*!< 0x00000200                                     */
#define HRPWM_CLRBR_MSTCMPD         HRPWM_CLRBR_MSTCMPD_Msk                 /*!< Master compare D                               */
#define HRPWM_CLRBR_MSTCMPC_Pos     (8U)
#define HRPWM_CLRBR_MSTCMPC_Msk     (0x1UL << HRPWM_CLRBR_MSTCMPC_Pos)      /*!< 0x00000100                                     */
#define HRPWM_CLRBR_MSTCMPC         HRPWM_CLRBR_MSTCMPC_Msk                 /*!< Master compare C                               */
#define HRPWM_CLRBR_MSTCMPB_Pos     (7U)
#define HRPWM_CLRBR_MSTCMPB_Msk     (0x1UL << HRPWM_CLRBR_MSTCMPB_Pos)      /*!< 0x00000080                                     */
#define HRPWM_CLRBR_MSTCMPB         HRPWM_CLRBR_MSTCMPB_Msk                 /*!< Master compare B                               */
#define HRPWM_CLRBR_MSTCMPA_Pos     (6U)
#define HRPWM_CLRBR_MSTCMPA_Msk     (0x1UL << HRPWM_CLRBR_MSTCMPA_Pos)      /*!< 0x00000040                                     */
#define HRPWM_CLRBR_MSTCMPA         HRPWM_CLRBR_MSTCMPA_Msk                 /*!< Master compare A                               */
#define HRPWM_CLRBR_PER_Pos         (5U)
#define HRPWM_CLRBR_PER_Msk         (0x1UL << HRPWM_CLRBR_PER_Pos)          /*!< 0x00000020                                     */
#define HRPWM_CLRBR_PER             HRPWM_CLRBR_PER_Msk                     /*!< Timer X period                                 */
#define HRPWM_CLRBR_CMPD_Pos        (4U)
#define HRPWM_CLRBR_CMPD_Msk        (0x1UL << HRPWM_CLRBR_CMPD_Pos)         /*!< 0x00000010                                     */
#define HRPWM_CLRBR_CMPD            HRPWM_CLRBR_CMPD_Msk                    /*!< Timer X compare D                              */
#define HRPWM_CLRBR_CMPC_Pos        (3U)
#define HRPWM_CLRBR_CMPC_Msk        (0x1UL << HRPWM_CLRBR_CMPC_Pos)         /*!< 0x00000008                                     */
#define HRPWM_CLRBR_CMPC            HRPWM_CLRBR_CMPC_Msk                    /*!< Timer X compare C                              */
#define HRPWM_CLRBR_CMPB_Pos        (2U)
#define HRPWM_CLRBR_CMPB_Msk        (0x1UL << HRPWM_CLRBR_CMPB_Pos)         /*!< 0x00000004                                     */
#define HRPWM_CLRBR_CMPB            HRPWM_CLRBR_CMPB_Msk                    /*!< Timer X compare B                              */
#define HRPWM_CLRBR_CMPA_Pos        (1U)
#define HRPWM_CLRBR_CMPA_Msk        (0x1UL << HRPWM_CLRBR_CMPA_Pos)         /*!< 0x00000002                                     */
#define HRPWM_CLRBR_CMPA            HRPWM_CLRBR_CMPA_Msk                    /*!< Timer X compare A                              */
#define HRPWM_CLRBR_UPD_Pos         (0U)
#define HRPWM_CLRBR_UPD_Msk         (0x1UL << HRPWM_CLRBR_UPD_Pos)          /*!< 0x00000001                                     */
#define HRPWM_CLRBR_UPD             HRPWM_CLRBR_UPD_Msk                     /*!< Register update (transfer preload to active)   */

/****************  Bit definition for HRPWM_PWMxEEFR0 register  ***************/
#define HRPWM_EEFR0_EE5FLTR_Pos     (26U)
#define HRPWM_EEFR0_EE5FLTR_Msk     (0xFUL << HRPWM_EEFR0_EE5FLTR_Pos)      /*!< 0x3C000000                                     */
#define HRPWM_EEFR0_EE5FLTR         HRPWM_EEFR0_EE5FLTR_Msk                 /*!< External Event 5 filter mask                   */
#define HRPWM_EEFR0_EE5FLTR_0       (0x1UL << HRPWM_EEFR0_EE5FLTR_Pos)      /*!< 0x04000000                                     */
#define HRPWM_EEFR0_EE5FLTR_1       (0x2UL << HRPWM_EEFR0_EE5FLTR_Pos)      /*!< 0x08000000                                     */
#define HRPWM_EEFR0_EE5FLTR_2       (0x4UL << HRPWM_EEFR0_EE5FLTR_Pos)      /*!< 0x10000000                                     */
#define HRPWM_EEFR0_EE5FLTR_3       (0x8UL << HRPWM_EEFR0_EE5FLTR_Pos)      /*!< 0x20000000                                     */
#define HRPWM_EEFR0_EE5LTCH_Pos     (25U)
#define HRPWM_EEFR0_EE5LTCH_Msk     (0x1UL << HRPWM_EEFR0_EE5LTCH_Pos)      /*!< 0x02000000                                     */
#define HRPWM_EEFR0_EE5LTCH         HRPWM_EEFR0_EE5LTCH_Msk                 /*!< External Event 5 latch                         */
#define HRPWM_EEFR0_EE4FLTR_Pos     (21U)
#define HRPWM_EEFR0_EE4FLTR_Msk     (0xFUL << HRPWM_EEFR0_EE4FLTR_Pos)      /*!< 0x01E00000                                     */
#define HRPWM_EEFR0_EE4FLTR         HRPWM_EEFR0_EE4FLTR_Msk                 /*!< External Event 4 filter mask                   */
#define HRPWM_EEFR0_EE4FLTR_0       (0x1UL << HRPWM_EEFR0_EE4FLTR_Pos)      /*!< 0x00200000                                     */
#define HRPWM_EEFR0_EE4FLTR_1       (0x2UL << HRPWM_EEFR0_EE4FLTR_Pos)      /*!< 0x00400000                                     */
#define HRPWM_EEFR0_EE4FLTR_2       (0x4UL << HRPWM_EEFR0_EE4FLTR_Pos)      /*!< 0x00800000                                     */
#define HRPWM_EEFR0_EE4FLTR_3       (0x8UL << HRPWM_EEFR0_EE4FLTR_Pos)      /*!< 0x01000000                                     */
#define HRPWM_EEFR0_EE4LTCH_Pos     (20U)
#define HRPWM_EEFR0_EE4LTCH_Msk     (0x1UL << HRPWM_EEFR0_EE4LTCH_Pos)      /*!< 0x00100000                                     */
#define HRPWM_EEFR0_EE4LTCH         HRPWM_EEFR0_EE4LTCH_Msk                 /*!< External Event 4 latch                         */
#define HRPWM_EEFR0_EE3FLTR_Pos     (16U)
#define HRPWM_EEFR0_EE3FLTR_Msk     (0xFUL << HRPWM_EEFR0_EE3FLTR_Pos)      /*!< 0x000F0000                                     */
#define HRPWM_EEFR0_EE3FLTR         HRPWM_EEFR0_EE3FLTR_Msk                 /*!< External Event 3 filter mask                   */
#define HRPWM_EEFR0_EE3FLTR_0       (0x1UL << HRPWM_EEFR0_EE3FLTR_Pos)      /*!< 0x00010000                                     */
#define HRPWM_EEFR0_EE3FLTR_1       (0x2UL << HRPWM_EEFR0_EE3FLTR_Pos)      /*!< 0x00020000                                     */
#define HRPWM_EEFR0_EE3FLTR_2       (0x4UL << HRPWM_EEFR0_EE3FLTR_Pos)      /*!< 0x00040000                                     */
#define HRPWM_EEFR0_EE3FLTR_3       (0x8UL << HRPWM_EEFR0_EE3FLTR_Pos)      /*!< 0x00080000                                     */
#define HRPWM_EEFR0_EE3LTCH_Pos     (15U)
#define HRPWM_EEFR0_EE3LTCH_Msk     (0x1UL << HRPWM_EEFR0_EE3LTCH_Pos)      /*!< 0x00008000                                     */
#define HRPWM_EEFR0_EE3LTCH         HRPWM_EEFR0_EE3LTCH_Msk                 /*!< External Event 3 latch                         */
#define HRPWM_EEFR0_EE2FLTR_Pos     (11U)
#define HRPWM_EEFR0_EE2FLTR_Msk     (0xFUL << HRPWM_EEFR0_EE2FLTR_Pos)      /*!< 0x00007800                                     */
#define HRPWM_EEFR0_EE2FLTR         HRPWM_EEFR0_EE2FLTR_Msk                 /*!< External Event 2 filter mask                   */
#define HRPWM_EEFR0_EE2FLTR_0       (0x1UL << HRPWM_EEFR0_EE2FLTR_Pos)      /*!< 0x00000800                                     */
#define HRPWM_EEFR0_EE2FLTR_1       (0x2UL << HRPWM_EEFR0_EE2FLTR_Pos)      /*!< 0x00001000                                     */
#define HRPWM_EEFR0_EE2FLTR_2       (0x4UL << HRPWM_EEFR0_EE2FLTR_Pos)      /*!< 0x00002000                                     */
#define HRPWM_EEFR0_EE2FLTR_3       (0x8UL << HRPWM_EEFR0_EE2FLTR_Pos)      /*!< 0x00004000                                     */
#define HRPWM_EEFR0_EE2LTCH_Pos     (10U)
#define HRPWM_EEFR0_EE2LTCH_Msk     (0x1UL << HRPWM_EEFR0_EE2LTCH_Pos)      /*!< 0x00000400                                     */
#define HRPWM_EEFR0_EE2LTCH         HRPWM_EEFR0_EE2LTCH_Msk                 /*!< External Event 2 latch                         */
#define HRPWM_EEFR0_EE1FLTR_Pos     (6U)
#define HRPWM_EEFR0_EE1FLTR_Msk     (0xFUL << HRPWM_EEFR0_EE1FLTR_Pos)      /*!< 0x00003C00                                     */
#define HRPWM_EEFR0_EE1FLTR         HRPWM_EEFR0_EE1FLTR_Msk                 /*!< External Event 1 filter mask                   */
#define HRPWM_EEFR0_EE1FLTR_0       (0x1UL << HRPWM_EEFR0_EE1FLTR_Pos)      /*!< 0x00000040                                     */
#define HRPWM_EEFR0_EE1FLTR_1       (0x2UL << HRPWM_EEFR0_EE1FLTR_Pos)      /*!< 0x00000080                                     */
#define HRPWM_EEFR0_EE1FLTR_2       (0x4UL << HRPWM_EEFR0_EE1FLTR_Pos)      /*!< 0x00000100                                     */
#define HRPWM_EEFR0_EE1FLTR_3       (0x8UL << HRPWM_EEFR0_EE1FLTR_Pos)      /*!< 0x00000200                                     */
#define HRPWM_EEFR0_EE1LTCH_Pos     (5U)
#define HRPWM_EEFR0_EE1LTCH_Msk     (0x1UL << HRPWM_EEFR0_EE1LTCH_Pos)      /*!< 0x00000020                                     */
#define HRPWM_EEFR0_EE1LTCH         HRPWM_EEFR0_EE1LTCH_Msk                 /*!< External Event 1 latch                         */
#define HRPWM_EEFR0_EE0FLTR_Pos     (1U)
#define HRPWM_EEFR0_EE0FLTR_Msk     (0xFUL << HRPWM_EEFR0_EE0FLTR_Pos)      /*!< 0x0000001E                                     */
#define HRPWM_EEFR0_EE0FLTR         HRPWM_EEFR0_EE0FLTR_Msk                 /*!< External Event 0 filter mask                   */
#define HRPWM_EEFR0_EE0FLTR_0       (0x1UL << HRPWM_EEFR0_EE0FLTR_Pos)      /*!< 0x00000002                                     */
#define HRPWM_EEFR0_EE0FLTR_1       (0x2UL << HRPWM_EEFR0_EE0FLTR_Pos)      /*!< 0x00000004                                     */
#define HRPWM_EEFR0_EE0FLTR_2       (0x4UL << HRPWM_EEFR0_EE0FLTR_Pos)      /*!< 0x00000008                                     */
#define HRPWM_EEFR0_EE0FLTR_3       (0x8UL << HRPWM_EEFR0_EE0FLTR_Pos)      /*!< 0x00000010                                     */
#define HRPWM_EEFR0_EE0LTCH_Pos     (0U)
#define HRPWM_EEFR0_EE0LTCH_Msk     (0x1UL << HRPWM_EEFR0_EE0LTCH_Pos)      /*!< 0x00000001                                     */
#define HRPWM_EEFR0_EE0LTCH         HRPWM_EEFR0_EE0LTCH_Msk                 /*!< External Event 0 latch                         */

/****************  Bit definition for HRPWM_PWMxEEFR1 register  ***************/
#define HRPWM_EEFR1_EEVACNT_Pos     (8U)
#define HRPWM_EEFR1_EEVACNT_Msk     (0x3FUL << HRPWM_EEFR1_EEVACNT_Pos)     /*!< 0x00003F00                                     */
#define HRPWM_EEFR1_EEVACNT         HRPWM_EEFR1_EEVACNT_Msk                 /*!< External Event A Count Threshold Value mask    */
#define HRPWM_EEFR1_EEVASEL_Pos     (4U)
#define HRPWM_EEFR1_EEVASEL_Msk     (0x7UL << HRPWM_EEFR1_EEVASEL_Pos)      /*!< 0x00000070                                     */
#define HRPWM_EEFR1_EEVASEL         HRPWM_EEFR1_EEVASEL_Msk                 /*!< External Event A Source Select mask            */
#define HRPWM_EEFR1_EEVARSTM_Pos    (2U)
#define HRPWM_EEFR1_EEVARSTM_Msk    (0x1UL << HRPWM_EEFR1_EEVARSTM_Pos)     /*!< 0x00000004                                     */
#define HRPWM_EEFR1_EEVARSTM        HRPWM_EEFR1_EEVARSTM_Msk                /*!< External Event A Count Reset Mode mask         */
#define HRPWM_EEFR1_EEVACRES_Pos    (1U)
#define HRPWM_EEFR1_EEVACRES_Msk    (0x1UL << HRPWM_EEFR1_EEVACRES_Pos)     /*!< 0x00000002                                     */
#define HRPWM_EEFR1_EEVACRES        HRPWM_EEFR1_EEVACRES_Msk                /*!< External Event A Count Reset mask              */
#define HRPWM_EEFR1_EEVACE_Pos      (0U)
#define HRPWM_EEFR1_EEVACE_Msk      (0x1UL << HRPWM_EEFR1_EEVACE_Pos)       /*!< 0x00000001                                     */
#define HRPWM_EEFR1_EEVACE          HRPWM_EEFR1_EEVACE_Msk                  /*!< External Event A Count Enable mask             */

/*****************  Bit definition for HRPWM_PWMxRSTR register  ***************/
#define HRPWM_RSTR_Pos              (0U)
#define HRPWM_RSTR_Msk              (0x1FFFFFFFUL << HRPWM_RSTR_Pos)        /*!< 0x1FFFFFFF                                     */
#define HRPWM_RSTR                  HRPWM_RSTR_Msk                          /*!< Reset Trigger Source mask                      */
#define HRPWM_RSTR_EXTEVT5          (0x10000000UL << HRPWM_RSTR_Pos)        /*!< External event 5                               */
#define HRPWM_RSTR_EXTEVT4          (0x08000000UL << HRPWM_RSTR_Pos)        /*!< External event 4                               */
#define HRPWM_RSTR_EXTEVT3          (0x04000000UL << HRPWM_RSTR_Pos)        /*!< External event 3                               */
#define HRPWM_RSTR_UPD_CMPA5        (0x02000000UL << HRPWM_RSTR_Pos)        /*!< Timer 5 compare A & Update                     */
#define HRPWM_RSTR_CMPD4            (0x01000000UL << HRPWM_RSTR_Pos)        /*!< Timer 4 compare D                              */
#define HRPWM_RSTR_CMPB4            (0x00800000UL << HRPWM_RSTR_Pos)        /*!< Timer 4 compare B                              */
#define HRPWM_RSTR_UPD_CMPA4        (0x00400000UL << HRPWM_RSTR_Pos)        /*!< Timer 4 compare A & Update                     */
#define HRPWM_RSTR_CMPD3            (0x00200000UL << HRPWM_RSTR_Pos)        /*!< Timer 3 compare D                              */
#define HRPWM_RSTR_CMPB3            (0x00100000UL << HRPWM_RSTR_Pos)        /*!< Timer 3 compare B                              */
#define HRPWM_RSTR_UPD_CMPA3        (0x00080000UL << HRPWM_RSTR_Pos)        /*!< Timer 3 compare A & Update                     */
#define HRPWM_RSTR_CMPD2            (0x00040000UL << HRPWM_RSTR_Pos)        /*!< Timer 2 compare D                              */
#define HRPWM_RSTR_CMPB2            (0x00020000UL << HRPWM_RSTR_Pos)        /*!< Timer 2 compare B                              */
#define HRPWM_RSTR_UPD_CMPA2        (0x00010000UL << HRPWM_RSTR_Pos)        /*!< Timer 2 compare A & Update                     */
#define HRPWM_RSTR_CMPD1            (0x00008000UL << HRPWM_RSTR_Pos)        /*!< Timer 1 compare D                              */
#define HRPWM_RSTR_CMPB1            (0x00004000UL << HRPWM_RSTR_Pos)        /*!< Timer 1 compare B                              */
#define HRPWM_RSTR_UPD_CMPA1        (0x00002000UL << HRPWM_RSTR_Pos)        /*!< Timer 1 compare A & Update                     */
#define HRPWM_RSTR_CMPD0            (0x00001000UL << HRPWM_RSTR_Pos)        /*!< Timer 0 compare D                              */
#define HRPWM_RSTR_CMPB0            (0x00000800UL << HRPWM_RSTR_Pos)        /*!< Timer 0 compare B                              */
#define HRPWM_RSTR_UPD_CMPA0        (0x00000400UL << HRPWM_RSTR_Pos)        /*!< Timer 0 compare A & Update                     */
#define HRPWM_RSTR_CMPD5            (0x00000200UL << HRPWM_RSTR_Pos)        /*!< Timer 5 compare D                              */
#define HRPWM_RSTR_CMPB5            (0x00000100UL << HRPWM_RSTR_Pos)        /*!< Timer 5 compare B                              */
#define HRPWM_RSTR_EXTEVT2          (0x00000080UL << HRPWM_RSTR_Pos)        /*!< External event 2                               */
#define HRPWM_RSTR_EXTEVT1          (0x00000040UL << HRPWM_RSTR_Pos)        /*!< External event 1                               */
#define HRPWM_RSTR_EXTEVT0          (0x00000020UL << HRPWM_RSTR_Pos)        /*!< External event 0                               */
#define HRPWM_RSTR_MSTPER           (0x00000010UL << HRPWM_RSTR_Pos)        /*!< Master period                                  */
#define HRPWM_RSTR_MSTCMPD          (0x00000008UL << HRPWM_RSTR_Pos)        /*!< Master compare D                               */
#define HRPWM_RSTR_MSTCMPC          (0x00000004UL << HRPWM_RSTR_Pos)        /*!< Master compare C                               */
#define HRPWM_RSTR_MSTCMPB          (0x00000002UL << HRPWM_RSTR_Pos)        /*!< Master compare B                               */
#define HRPWM_RSTR_MSTCMPA          (0x00000001UL << HRPWM_RSTR_Pos)        /*!< Master compare A                               */

/*****************  Bit definition for HRPWM_PWMxCHPR register  ***************/
#define HRPWM_CHPR_STRPW_Pos        (7U)
#define HRPWM_CHPR_STRPW_Msk        (0xFUL << HRPWM_CHPR_STRPW_Pos)         /*!< 0x00000780                                     */
#define HRPWM_CHPR_STRPW            HRPWM_CHPR_STRPW_Msk                    /*!< Timer start pulse width value                  */
#define HRPWM_CHPR_STRPW_0          (0x1UL << HRPWM_CHPR_STRPW_Pos)         /*!< 0x00000080                                     */
#define HRPWM_CHPR_STRPW_1          (0x2UL << HRPWM_CHPR_STRPW_Pos)         /*!< 0x00000100                                     */
#define HRPWM_CHPR_STRPW_2          (0x4UL << HRPWM_CHPR_STRPW_Pos)         /*!< 0x00000200                                     */
#define HRPWM_CHPR_STRPW_3          (0x8UL << HRPWM_CHPR_STRPW_Pos)         /*!< 0x00000400                                     */
#define HRPWM_CHPR_CARDTY_Pos       (4U)
#define HRPWM_CHPR_CARDTY_Msk       (0x7UL << HRPWM_CHPR_CARDTY_Pos)        /*!< 0x00000070                                     */
#define HRPWM_CHPR_CARDTY           HRPWM_CHPR_CARDTY_Msk                   /*!< Timer chopper duty cycle value                 */
#define HRPWM_CHPR_CARDTY_0         (0x1UL << HRPWM_CHPR_CARDTY_Pos)        /*!< 0x00000001                                     */
#define HRPWM_CHPR_CARDTY_1         (0x2UL << HRPWM_CHPR_CARDTY_Pos)        /*!< 0x00000002                                     */
#define HRPWM_CHPR_CARDTY_2         (0x4UL << HRPWM_CHPR_CARDTY_Pos)        /*!< 0x00000004                                     */
#define HRPWM_CHPR_CARFRQ_Pos       (0U)
#define HRPWM_CHPR_CARFRQ_Msk       (0xFUL << HRPWM_CHPR_CARFRQ_Pos)        /*!< 0x0000000F                                     */
#define HRPWM_CHPR_CARFRQ           HRPWM_CHPR_CARFRQ_Msk                   /*!< Timer carrier frequency value                  */
#define HRPWM_CHPR_CARFRQ_0         (0x1UL << HRPWM_CHPR_CARFRQ_Pos)        /*!< 0x00000001                                     */
#define HRPWM_CHPR_CARFRQ_1         (0x2UL << HRPWM_CHPR_CARFRQ_Pos)        /*!< 0x00000002                                     */
#define HRPWM_CHPR_CARFRQ_2         (0x4UL << HRPWM_CHPR_CARFRQ_Pos)        /*!< 0x00000004                                     */
#define HRPWM_CHPR_CARFRQ_3         (0x8UL << HRPWM_CHPR_CARFRQ_Pos)        /*!< 0x00000008                                     */

/*****************  Bit definition for HRPWM_PWMxOUTR register  ***************/
#define HRPWM_OUTR_DTEN_Pos         (31U)
#define HRPWM_OUTR_DTEN_Msk         (0x1UL << HRPWM_OUTR_DTEN_Pos)          /*!< 0x80000000                                     */
#define HRPWM_OUTR_DTEN             HRPWM_OUTR_DTEN_Msk                     /*!< Slave output deadtime enable                   */
#define HRPWM_OUTR_CHPB_Pos         (20U)
#define HRPWM_OUTR_CHPB_Msk         (0x1UL << HRPWM_OUTR_CHPB_Pos)          /*!< 0x00100000                                     */
#define HRPWM_OUTR_CHPB             HRPWM_OUTR_CHPB_Msk                     /*!< Slave output B chopper enable                  */
#define HRPWM_OUTR_IDLESB_Pos       (19U)
#define HRPWM_OUTR_IDLESB_Msk       (0x1UL << HRPWM_OUTR_IDLESB_Pos)        /*!< 0x00080000                                     */
#define HRPWM_OUTR_IDLESB           HRPWM_OUTR_IDLESB_Msk                   /*!< Slave output B idle state                      */
#define HRPWM_OUTR_FAULTB_Pos       (17U)
#define HRPWM_OUTR_FAULTB_Msk       (0x3UL << HRPWM_OUTR_FAULTB_Pos)        /*!< 0x00060000                                     */
#define HRPWM_OUTR_FAULTB           HRPWM_OUTR_FAULTB_Msk                   /*!< Slave output B fault state                     */
#define HRPWM_OUTR_FAULTB_0         (0x1UL << HRPWM_OUTR_FAULTB_Pos)        /*!< 0x00020000                                     */
#define HRPWM_OUTR_FAULTB_1         (0x2UL << HRPWM_OUTR_FAULTB_Pos)        /*!< 0x00040000                                     */
#define HRPWM_OUTR_POLB_Pos         (16U)
#define HRPWM_OUTR_POLB_Msk         (0x1UL << HRPWM_OUTR_POLB_Pos)          /*!< 0x00010000                                     */
#define HRPWM_OUTR_POLB             HRPWM_OUTR_POLB_Msk                     /*!< Slave output B polarity                        */
#define HRPWM_OUTR_CHPA_Pos         (4U)
#define HRPWM_OUTR_CHPA_Msk         (0x1UL << HRPWM_OUTR_CHPA_Pos)          /*!< 0x00000010                                     */
#define HRPWM_OUTR_CHPA             HRPWM_OUTR_CHPA_Msk                     /*!< Slave output A chopper enable                  */
#define HRPWM_OUTR_IDLESA_Pos       (3U)
#define HRPWM_OUTR_IDLESA_Msk       (0x1UL << HRPWM_OUTR_IDLESA_Pos)        /*!< 0x00000008                                     */
#define HRPWM_OUTR_IDLESA           HRPWM_OUTR_IDLESA_Msk                   /*!< Slave output A idle state                      */
#define HRPWM_OUTR_FAULTA_Pos       (1U)
#define HRPWM_OUTR_FAULTA_Msk       (0x3UL << HRPWM_OUTR_FAULTA_Pos)        /*!< 0x00000006                                     */
#define HRPWM_OUTR_FAULTA           HRPWM_OUTR_FAULTA_Msk                   /*!< Slave output A fault state                     */
#define HRPWM_OUTR_FAULTA_0         (0x1UL << HRPWM_OUTR_FAULTA_Pos)        /*!< 0x00000020                                     */
#define HRPWM_OUTR_FAULTA_1         (0x2UL << HRPWM_OUTR_FAULTA_Pos)        /*!< 0x00000040                                     */
#define HRPWM_OUTR_POLA_Pos         (0U)
#define HRPWM_OUTR_POLA_Msk         (0x1UL << HRPWM_OUTR_POLA_Pos)          /*!< 0x00000001                                     */
#define HRPWM_OUTR_POLA             HRPWM_OUTR_POLA_Msk                     /*!< Slave output A polarity                        */

/*****************  Bit definition for HRPWM_PWMxFLTR register  ***************/
#define HRPWM_FLTR_FLT5EN_Pos       (5U)
#define HRPWM_FLTR_FLT5EN_Msk       (0x1UL << HRPWM_FLTR_FLT5EN_Pos)        /*!< 0x00000020                                     */
#define HRPWM_FLTR_FLT5EN           HRPWM_FLTR_FLT5EN_Msk                   /*!< Fault 5 enable                                 */
#define HRPWM_FLTR_FLT4EN_Pos       (4U)
#define HRPWM_FLTR_FLT4EN_Msk       (0x1UL << HRPWM_FLTR_FLT4EN_Pos)        /*!< 0x00000010                                     */
#define HRPWM_FLTR_FLT4EN           HRPWM_FLTR_FLT4EN_Msk                   /*!< Fault 4 enable                                 */
#define HRPWM_FLTR_FLT3EN_Pos       (3U)
#define HRPWM_FLTR_FLT3EN_Msk       (0x1UL << HRPWM_FLTR_FLT3EN_Pos)        /*!< 0x00000008                                     */
#define HRPWM_FLTR_FLT3EN           HRPWM_FLTR_FLT3EN_Msk                   /*!< Fault 3 enable                                 */
#define HRPWM_FLTR_FLT2EN_Pos       (2U)
#define HRPWM_FLTR_FLT2EN_Msk       (0x1UL << HRPWM_FLTR_FLT2EN_Pos)        /*!< 0x00000004                                     */
#define HRPWM_FLTR_FLT2EN           HRPWM_FLTR_FLT2EN_Msk                   /*!< Fault 2 enable                                 */
#define HRPWM_FLTR_FLT1EN_Pos       (1U)
#define HRPWM_FLTR_FLT1EN_Msk       (0x1UL << HRPWM_FLTR_FLT1EN_Pos)        /*!< 0x00000002                                     */
#define HRPWM_FLTR_FLT1EN           HRPWM_FLTR_FLT1EN_Msk                   /*!< Fault 1 enable                                 */
#define HRPWM_FLTR_FLT0EN_Pos       (0U)
#define HRPWM_FLTR_FLT0EN_Msk       (0x1UL << HRPWM_FLTR_FLT0EN_Pos)        /*!< 0x00000001                                     */
#define HRPWM_FLTR_FLT0EN           HRPWM_FLTR_FLT0EN_Msk                   /*!< Fault 0 enable                                 */

/****************  Bit definition for HRPWM_Common_CR0 register  **************/
#define HRPWM_CR0_ADUSRC7_Pos       (29U)
#define HRPWM_CR0_ADUSRC7_Msk       (0x7UL << HRPWM_CR0_ADUSRC7_Pos)        /*!< 0xE0000000                                     */
#define HRPWM_CR0_ADUSRC7           HRPWM_CR0_ADUSRC7_Msk                   /*!< ADC\DAC Trigger 7 update source                */
#define HRPWM_CR0_ADUSRC7_0         (0x1UL << HRPWM_CR0_ADUSRC7_Pos)        /*!< 0x20000000                                     */
#define HRPWM_CR0_ADUSRC7_1         (0x2UL << HRPWM_CR0_ADUSRC7_Pos)        /*!< 0x40000000                                     */
#define HRPWM_CR0_ADUSRC7_2         (0x4UL << HRPWM_CR0_ADUSRC7_Pos)        /*!< 0x80000000                                     */
#define HRPWM_CR0_ADUSRC6_Pos       (26U)
#define HRPWM_CR0_ADUSRC6_Msk       (0x7UL << HRPWM_CR0_ADUSRC6_Pos)        /*!< 0x1C000000                                     */
#define HRPWM_CR0_ADUSRC6           HRPWM_CR0_ADUSRC6_Msk                   /*!< ADC\DAC Trigger 6 update source                */
#define HRPWM_CR0_ADUSRC6_0         (0x1UL << HRPWM_CR0_ADUSRC6_Pos)        /*!< 0x04000000                                     */
#define HRPWM_CR0_ADUSRC6_1         (0x2UL << HRPWM_CR0_ADUSRC6_Pos)        /*!< 0x08000000                                     */
#define HRPWM_CR0_ADUSRC6_2         (0x4UL << HRPWM_CR0_ADUSRC6_Pos)        /*!< 0x10000000                                     */
#define HRPWM_CR0_ADUSRC5_Pos       (23U)
#define HRPWM_CR0_ADUSRC5_Msk       (0x7UL << HRPWM_CR0_ADUSRC5_Pos)        /*!< 0x03800000                                     */
#define HRPWM_CR0_ADUSRC5           HRPWM_CR0_ADUSRC5_Msk                   /*!< ADC\DAC Trigger 5 update source                */
#define HRPWM_CR0_ADUSRC5_0         (0x1UL << HRPWM_CR0_ADUSRC5_Pos)        /*!< 0x00800000                                     */
#define HRPWM_CR0_ADUSRC5_1         (0x2UL << HRPWM_CR0_ADUSRC5_Pos)        /*!< 0x01000000                                     */
#define HRPWM_CR0_ADUSRC5_2         (0x4UL << HRPWM_CR0_ADUSRC5_Pos)        /*!< 0x02000000                                     */
#define HRPWM_CR0_ADUSRC4_Pos       (20U)
#define HRPWM_CR0_ADUSRC4_Msk       (0x7UL << HRPWM_CR0_ADUSRC4_Pos)        /*!< 0x00700000                                     */
#define HRPWM_CR0_ADUSRC4           HRPWM_CR0_ADUSRC4_Msk                   /*!< ADC\DAC Trigger 4 update source                */
#define HRPWM_CR0_ADUSRC4_0         (0x1UL << HRPWM_CR0_ADUSRC4_Pos)        /*!< 0x00100000                                     */
#define HRPWM_CR0_ADUSRC4_1         (0x2UL << HRPWM_CR0_ADUSRC4_Pos)        /*!< 0x00200000                                     */
#define HRPWM_CR0_ADUSRC4_2         (0x4UL << HRPWM_CR0_ADUSRC4_Pos)        /*!< 0x00400000                                     */
#define HRPWM_CR0_ADUSRC3_Pos       (17U)
#define HRPWM_CR0_ADUSRC3_Msk       (0x7UL << HRPWM_CR0_ADUSRC3_Pos)        /*!< 0x000E0000                                     */
#define HRPWM_CR0_ADUSRC3           HRPWM_CR0_ADUSRC3_Msk                   /*!< ADC\DAC Trigger 3 update source                */
#define HRPWM_CR0_ADUSRC3_0         (0x1UL << HRPWM_CR0_ADUSRC3_Pos)        /*!< 0x00020000                                     */
#define HRPWM_CR0_ADUSRC3_1         (0x2UL << HRPWM_CR0_ADUSRC3_Pos)        /*!< 0x00040000                                     */
#define HRPWM_CR0_ADUSRC3_2         (0x4UL << HRPWM_CR0_ADUSRC3_Pos)        /*!< 0x00080000                                     */
#define HRPWM_CR0_ADUSRC2_Pos       (14U)
#define HRPWM_CR0_ADUSRC2_Msk       (0x7UL << HRPWM_CR0_ADUSRC2_Pos)        /*!< 0x0001C000                                     */
#define HRPWM_CR0_ADUSRC2           HRPWM_CR0_ADUSRC2_Msk                   /*!< ADC\DAC Trigger 2 update source                */
#define HRPWM_CR0_ADUSRC2_0         (0x1UL << HRPWM_CR0_ADUSRC2_Pos)        /*!< 0x00004000                                     */
#define HRPWM_CR0_ADUSRC2_1         (0x2UL << HRPWM_CR0_ADUSRC2_Pos)        /*!< 0x00008000                                     */
#define HRPWM_CR0_ADUSRC2_2         (0x4UL << HRPWM_CR0_ADUSRC2_Pos)        /*!< 0x00010000                                     */
#define HRPWM_CR0_ADUSRC1_Pos       (11U)
#define HRPWM_CR0_ADUSRC1_Msk       (0x7UL << HRPWM_CR0_ADUSRC1_Pos)        /*!< 0x00003800                                     */
#define HRPWM_CR0_ADUSRC1           HRPWM_CR0_ADUSRC1_Msk                   /*!< ADC\DAC Trigger 1 update source                */
#define HRPWM_CR0_ADUSRC1_0         (0x1UL << HRPWM_CR0_ADUSRC1_Pos)        /*!< 0x00000800                                     */
#define HRPWM_CR0_ADUSRC1_1         (0x2UL << HRPWM_CR0_ADUSRC1_Pos)        /*!< 0x00001000                                     */
#define HRPWM_CR0_ADUSRC1_2         (0x4UL << HRPWM_CR0_ADUSRC1_Pos)        /*!< 0x00002000                                     */
#define HRPWM_CR0_ADUSRC0_Pos       (8U)
#define HRPWM_CR0_ADUSRC0_Msk       (0x7UL << HRPWM_CR0_ADUSRC0_Pos)        /*!< 0x00000700                                     */
#define HRPWM_CR0_ADUSRC0           HRPWM_CR0_ADUSRC0_Msk                   /*!< ADC\DAC Trigger 0 update source                */
#define HRPWM_CR0_ADUSRC0_0         (0x1UL << HRPWM_CR0_ADUSRC0_Pos)        /*!< 0x00000100                                     */
#define HRPWM_CR0_ADUSRC0_1         (0x2UL << HRPWM_CR0_ADUSRC0_Pos)        /*!< 0x00000200                                     */
#define HRPWM_CR0_ADUSRC0_2         (0x4UL << HRPWM_CR0_ADUSRC0_Pos)        /*!< 0x00000400                                     */
#define HRPWM_CR0_MUDIS_Pos         (6U)
#define HRPWM_CR0_MUDIS_Msk         (0x1UL << HRPWM_CR0_MUDIS_Pos)          /*!< 0x00000040                                     */
#define HRPWM_CR0_MUDIS             HRPWM_CR0_MUDIS_Msk                     /*!< Master update disable                          */
#define HRPWM_CR0_UDIS5_Pos         (5U)
#define HRPWM_CR0_UDIS5_Msk         (0x1UL << HRPWM_CR0_UDIS5_Pos)          /*!< 0x00000020                                     */
#define HRPWM_CR0_UDIS5             HRPWM_CR0_UDIS5_Msk                     /*!< Timer 5 update disable                         */
#define HRPWM_CR0_UDIS4_Pos         (4U)
#define HRPWM_CR0_UDIS4_Msk         (0x1UL << HRPWM_CR0_UDIS4_Pos)          /*!< 0x00000010                                     */
#define HRPWM_CR0_UDIS4             HRPWM_CR0_UDIS4_Msk                     /*!< Timer 4 update disable                         */
#define HRPWM_CR0_UDIS3_Pos         (3U)
#define HRPWM_CR0_UDIS3_Msk         (0x1UL << HRPWM_CR0_UDIS3_Pos)          /*!< 0x00000008                                     */
#define HRPWM_CR0_UDIS3             HRPWM_CR0_UDIS3_Msk                     /*!< Timer 3 update disable                         */
#define HRPWM_CR0_UDIS2_Pos         (2U)
#define HRPWM_CR0_UDIS2_Msk         (0x1UL << HRPWM_CR0_UDIS2_Pos)          /*!< 0x00000004                                     */
#define HRPWM_CR0_UDIS2             HRPWM_CR0_UDIS2_Msk                     /*!< Timer 2 update disable                         */
#define HRPWM_CR0_UDIS1_Pos         (1U)
#define HRPWM_CR0_UDIS1_Msk         (0x1UL << HRPWM_CR0_UDIS1_Pos)          /*!< 0x00000002                                     */
#define HRPWM_CR0_UDIS1             HRPWM_CR0_UDIS1_Msk                     /*!< Timer 1 update disable                         */
#define HRPWM_CR0_UDIS0_Pos         (0U)
#define HRPWM_CR0_UDIS0_Msk         (0x1UL << HRPWM_CR0_UDIS0_Pos)          /*!< 0x00000001                                     */
#define HRPWM_CR0_UDIS0             HRPWM_CR0_UDIS0_Msk                     /*!< Timer 0 update disable                         */

/****************  Bit definition for HRPWM_Common_CR1 register  **************/
#define HRPWM_CR1_SWP5_Pos          (21U)
#define HRPWM_CR1_SWP5_Msk          (0x1UL << HRPWM_CR1_SWP5_Pos)           /*!< 0x00200000                                     */
#define HRPWM_CR1_SWP5              HRPWM_CR1_SWP5_Msk                      /*!< Timer 5 swap outputs                           */
#define HRPWM_CR1_SWP4_Pos          (20U)
#define HRPWM_CR1_SWP4_Msk          (0x1UL << HRPWM_CR1_SWP4_Pos)           /*!< 0x00100000                                     */
#define HRPWM_CR1_SWP4              HRPWM_CR1_SWP4_Msk                      /*!< Timer 4 swap outputs                           */
#define HRPWM_CR1_SWP3_Pos          (19U)
#define HRPWM_CR1_SWP3_Msk          (0x1UL << HRPWM_CR1_SWP3_Pos)           /*!< 0x00080000                                     */
#define HRPWM_CR1_SWP3              HRPWM_CR1_SWP3_Msk                      /*!< Timer 3 swap outputs                           */
#define HRPWM_CR1_SWP2_Pos          (18U)
#define HRPWM_CR1_SWP2_Msk          (0x1UL << HRPWM_CR1_SWP2_Pos)           /*!< 0x00040000                                     */
#define HRPWM_CR1_SWP2              HRPWM_CR1_SWP2_Msk                      /*!< Timer 2 swap outputs                           */
#define HRPWM_CR1_SWP1_Pos          (17U)
#define HRPWM_CR1_SWP1_Msk          (0x1UL << HRPWM_CR1_SWP1_Pos)           /*!< 0x00020000                                     */
#define HRPWM_CR1_SWP1              HRPWM_CR1_SWP1_Msk                      /*!< Timer 1 swap outputs                           */
#define HRPWM_CR1_SWP0_Pos          (16U)
#define HRPWM_CR1_SWP0_Msk          (0x1UL << HRPWM_CR1_SWP0_Pos)           /*!< 0x00010000                                     */
#define HRPWM_CR1_SWP0              HRPWM_CR1_SWP0_Msk                      /*!< Timer 0 swap outputs                           */
#define HRPWM_CR1_MRST_Pos          (14U)
#define HRPWM_CR1_MRST_Msk          (0x1UL << HRPWM_CR1_MRST_Pos)           /*!< 0x00004000                                     */
#define HRPWM_CR1_MRST              HRPWM_CR1_MRST_Msk                      /*!< Master count software reset                    */
#define HRPWM_CR1_RST5_Pos          (13U)
#define HRPWM_CR1_RST5_Msk          (0x1UL << HRPWM_CR1_RST5_Pos)           /*!< 0x00002000                                     */
#define HRPWM_CR1_RST5              HRPWM_CR1_RST5_Msk                      /*!< Timer 5 count software reset                   */
#define HRPWM_CR1_RST4_Pos          (12U)
#define HRPWM_CR1_RST4_Msk          (0x1UL << HRPWM_CR1_RST4_Pos)           /*!< 0x00001000                                     */
#define HRPWM_CR1_RST4              HRPWM_CR1_RST4_Msk                      /*!< Timer 4 count software reset                   */
#define HRPWM_CR1_RST3_Pos          (11U)
#define HRPWM_CR1_RST3_Msk          (0x1UL << HRPWM_CR1_RST3_Pos)           /*!< 0x00000800                                     */
#define HRPWM_CR1_RST3              HRPWM_CR1_RST3_Msk                      /*!< Timer 3 count software reset                   */
#define HRPWM_CR1_RST2_Pos          (10U)
#define HRPWM_CR1_RST2_Msk          (0x1UL << HRPWM_CR1_RST2_Pos)           /*!< 0x00000400                                     */
#define HRPWM_CR1_RST2              HRPWM_CR1_RST2_Msk                      /*!< Timer 2 count software reset                   */
#define HRPWM_CR1_RST1_Pos          (9U)
#define HRPWM_CR1_RST1_Msk          (0x1UL << HRPWM_CR1_RST1_Pos)           /*!< 0x00000200                                     */
#define HRPWM_CR1_RST1              HRPWM_CR1_RST1_Msk                      /*!< Timer 1 count software reset                   */
#define HRPWM_CR1_RST0_Pos          (8U)
#define HRPWM_CR1_RST0_Msk          (0x1UL << HRPWM_CR1_RST0_Pos)           /*!< 0x00000100                                     */
#define HRPWM_CR1_RST0              HRPWM_CR1_RST0_Msk                      /*!< Timer 0 count software reset                   */
#define HRPWM_CR1_MSWU_Pos          (6U)
#define HRPWM_CR1_MSWU_Msk          (0x1UL << HRPWM_CR1_MSWU_Pos)           /*!< 0x00000040                                     */
#define HRPWM_CR1_MSWU              HRPWM_CR1_MSWU_Msk                      /*!< Master software update                         */
#define HRPWM_CR1_SWU5_Pos          (5U)
#define HRPWM_CR1_SWU5_Msk          (0x1UL << HRPWM_CR1_SWU5_Pos)           /*!< 0x00000020                                     */
#define HRPWM_CR1_SWU5              HRPWM_CR1_SWU5_Msk                      /*!< Timer 5 software update                        */
#define HRPWM_CR1_SWU4_Pos          (4U)
#define HRPWM_CR1_SWU4_Msk          (0x1UL << HRPWM_CR1_SWU4_Pos)           /*!< 0x00000010                                     */
#define HRPWM_CR1_SWU4              HRPWM_CR1_SWU4_Msk                      /*!< Timer 4 software update                        */
#define HRPWM_CR1_SWU3_Pos          (3U)
#define HRPWM_CR1_SWU3_Msk          (0x1UL << HRPWM_CR1_SWU3_Pos)           /*!< 0x00000008                                     */
#define HRPWM_CR1_SWU3              HRPWM_CR1_SWU3_Msk                      /*!< Timer 3 software update                        */
#define HRPWM_CR1_SWU2_Pos          (2U)
#define HRPWM_CR1_SWU2_Msk          (0x1UL << HRPWM_CR1_SWU2_Pos)           /*!< 0x00000004                                     */
#define HRPWM_CR1_SWU2              HRPWM_CR1_SWU2_Msk                      /*!< Timer 2 software update                        */
#define HRPWM_CR1_SWU1_Pos          (1U)
#define HRPWM_CR1_SWU1_Msk          (0x1UL << HRPWM_CR1_SWU1_Pos)           /*!< 0x00000002                                     */
#define HRPWM_CR1_SWU1              HRPWM_CR1_SWU1_Msk                      /*!< Timer 1 software update                        */
#define HRPWM_CR1_SWU0_Pos          (0U)
#define HRPWM_CR1_SWU0_Msk          (0x1UL << HRPWM_CR1_SWU0_Pos)           /*!< 0x00000001                                     */
#define HRPWM_CR1_SWU0              HRPWM_CR1_SWU0_Msk                      /*!< Timer 0 software update                        */

/****************  Bit definition for HRPWM_Common_CR2 register  **************/
#define HRPWM_CR2_TLEN7_Pos         (28U)
#define HRPWM_CR2_TLEN7_Msk         (0xFUL << HRPWM_CR2_TLEN7_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN7             HRPWM_CR2_TLEN7_Msk                     /*!< ADC\DAC Trigger 7 Event Length clk             */
#define HRPWM_CR2_TLEN7_0           (0x1UL << HRPWM_CR2_TLEN7_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN7_1           (0x2UL << HRPWM_CR2_TLEN7_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN7_2           (0x4UL << HRPWM_CR2_TLEN7_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN7_3           (0x8UL << HRPWM_CR2_TLEN7_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN6_Pos         (24U)
#define HRPWM_CR2_TLEN6_Msk         (0xFUL << HRPWM_CR2_TLEN6_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN6             HRPWM_CR2_TLEN6_Msk                     /*!< ADC\DAC Trigger 6 Event Length clk             */
#define HRPWM_CR2_TLEN6_0           (0x1UL << HRPWM_CR2_TLEN6_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN6_1           (0x2UL << HRPWM_CR2_TLEN6_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN6_2           (0x4UL << HRPWM_CR2_TLEN6_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN6_3           (0x8UL << HRPWM_CR2_TLEN6_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN5_Pos         (20U)
#define HRPWM_CR2_TLEN5_Msk         (0xFUL << HRPWM_CR2_TLEN5_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN5             HRPWM_CR2_TLEN5_Msk                     /*!< ADC\DAC Trigger 5 Event Length clk             */
#define HRPWM_CR2_TLEN5_0           (0x1UL << HRPWM_CR2_TLEN5_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN5_1           (0x2UL << HRPWM_CR2_TLEN5_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN5_2           (0x4UL << HRPWM_CR2_TLEN5_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN5_3           (0x8UL << HRPWM_CR2_TLEN5_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN4_Pos         (16U)
#define HRPWM_CR2_TLEN4_Msk         (0xFUL << HRPWM_CR2_TLEN4_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN4             HRPWM_CR2_TLEN4_Msk                     /*!< ADC\DAC Trigger 4 Event Length clk             */
#define HRPWM_CR2_TLEN4_0           (0x1UL << HRPWM_CR2_TLEN4_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN4_1           (0x2UL << HRPWM_CR2_TLEN4_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN4_2           (0x4UL << HRPWM_CR2_TLEN4_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN4_3           (0x8UL << HRPWM_CR2_TLEN4_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN3_Pos         (12U)
#define HRPWM_CR2_TLEN3_Msk         (0xFUL << HRPWM_CR2_TLEN3_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN3             HRPWM_CR2_TLEN3_Msk                     /*!< ADC\DAC Trigger 3 Event Length clk             */
#define HRPWM_CR2_TLEN3_0           (0x1UL << HRPWM_CR2_TLEN3_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN3_1           (0x2UL << HRPWM_CR2_TLEN3_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN3_2           (0x4UL << HRPWM_CR2_TLEN3_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN3_3           (0x8UL << HRPWM_CR2_TLEN3_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN2_Pos         (8U)
#define HRPWM_CR2_TLEN2_Msk         (0xFUL << HRPWM_CR2_TLEN2_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN2             HRPWM_CR2_TLEN2_Msk                     /*!< ADC\DAC Trigger 2 Event Length clk             */
#define HRPWM_CR2_TLEN2_0           (0x1UL << HRPWM_CR2_TLEN2_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN2_1           (0x2UL << HRPWM_CR2_TLEN2_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN2_2           (0x4UL << HRPWM_CR2_TLEN2_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN2_3           (0x8UL << HRPWM_CR2_TLEN2_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN1_Pos         (4U)
#define HRPWM_CR2_TLEN1_Msk         (0xFUL << HRPWM_CR2_TLEN1_Pos)          /*!< 0x00000700                                     */
#define HRPWM_CR2_TLEN1             HRPWM_CR2_TLEN1_Msk                     /*!< ADC\DAC Trigger 1 Event Length clk             */
#define HRPWM_CR2_TLEN1_0           (0x1UL << HRPWM_CR2_TLEN1_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN1_1           (0x2UL << HRPWM_CR2_TLEN1_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN1_2           (0x4UL << HRPWM_CR2_TLEN1_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN1_3           (0x8UL << HRPWM_CR2_TLEN1_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN0_Pos         (0U)
#define HRPWM_CR2_TLEN0_Msk         (0xFUL << HRPWM_CR2_TLEN0_Pos)          /*!< 0x0000000F                                     */
#define HRPWM_CR2_TLEN0             HRPWM_CR2_TLEN0_Msk                     /*!< ADC\DAC Trigger 0 Event Length clk             */
#define HRPWM_CR2_TLEN0_0           (0x1UL << HRPWM_CR2_TLEN0_Pos)          /*!< 0x00000100                                     */
#define HRPWM_CR2_TLEN0_1           (0x2UL << HRPWM_CR2_TLEN0_Pos)          /*!< 0x00000200                                     */
#define HRPWM_CR2_TLEN0_2           (0x4UL << HRPWM_CR2_TLEN0_Pos)          /*!< 0x00000400                                     */
#define HRPWM_CR2_TLEN0_3           (0x8UL << HRPWM_CR2_TLEN0_Pos)          /*!< 0x00000800                                     */

/****************  Bit definition for HRPWM_Common_ISR register  **************/
#define HRPWM_ISR_SYSFLT_Pos        (6U)
#define HRPWM_ISR_SYSFLT_Msk        (0x1UL << HRPWM_ISR_SYSFLT_Pos)         /*!< 0x00000040                                     */
#define HRPWM_ISR_SYSFLT            HRPWM_ISR_SYSFLT_Msk                    /*!< System Fault interrupt flag                    */
#define HRPWM_ISR_FLT5_Pos          (5U)
#define HRPWM_ISR_FLT5_Msk          (0x1UL << HRPWM_ISR_FLT5_Pos)           /*!< 0x00000020                                     */
#define HRPWM_ISR_FLT5              HRPWM_ISR_FLT5_Msk                      /*!< Fault 5 interrupt flag                         */
#define HRPWM_ISR_FLT4_Pos          (4U)
#define HRPWM_ISR_FLT4_Msk          (0x1UL << HRPWM_ISR_FLT4_Pos)           /*!< 0x00000010                                     */
#define HRPWM_ISR_FLT4              HRPWM_ISR_FLT4_Msk                      /*!< Fault 4 interrupt flag                         */
#define HRPWM_ISR_FLT3_Pos          (3U)
#define HRPWM_ISR_FLT3_Msk          (0x1UL << HRPWM_ISR_FLT3_Pos)           /*!< 0x00000008                                     */
#define HRPWM_ISR_FLT3              HRPWM_ISR_FLT3_Msk                      /*!< Fault 3 interrupt flag                         */
#define HRPWM_ISR_FLT2_Pos          (2U)
#define HRPWM_ISR_FLT2_Msk          (0x1UL << HRPWM_ISR_FLT2_Pos)           /*!< 0x00000004                                     */
#define HRPWM_ISR_FLT2              HRPWM_ISR_FLT2_Msk                      /*!< Fault 2 interrupt flag                         */
#define HRPWM_ISR_FLT1_Pos          (1U)
#define HRPWM_ISR_FLT1_Msk          (0x1UL << HRPWM_ISR_FLT1_Pos)           /*!< 0x00000002                                     */
#define HRPWM_ISR_FLT1              HRPWM_ISR_FLT1_Msk                      /*!< Fault 1 interrupt flag                         */
#define HRPWM_ISR_FLT0_Pos          (0U)
#define HRPWM_ISR_FLT0_Msk          (0x1UL << HRPWM_ISR_FLT0_Pos)           /*!< 0x00000001                                     */
#define HRPWM_ISR_FLT0              HRPWM_ISR_FLT0_Msk                      /*!< Fault 0 interrupt flag                         */

/****************  Bit definition for HRPWM_Common_IER register  **************/
#define HRPWM_IER_SYSFLTIE_Pos      (6U)
#define HRPWM_IER_SYSFLTIE_Msk      (0x1UL << HRPWM_IER_SYSFLTIE_Pos)       /*!< 0x00000040                                     */
#define HRPWM_IER_SYSFLTIE          HRPWM_IER_SYSFLTIE_Msk                  /*!< System Fault interrupt Enable                  */
#define HRPWM_IER_FLT5IE_Pos        (5U)
#define HRPWM_IER_FLT5IE_Msk        (0x1UL << HRPWM_IER_FLT5IE_Pos)         /*!< 0x00000020                                     */
#define HRPWM_IER_FLT5IE            HRPWM_IER_FLT5IE_Msk                    /*!< Fault 5 interrupt Enable                       */
#define HRPWM_IER_FLT4IE_Pos        (4U)
#define HRPWM_IER_FLT4IE_Msk        (0x1UL << HRPWM_IER_FLT4IE_Pos)         /*!< 0x00000010                                     */
#define HRPWM_IER_FLT4IE            HRPWM_IER_FLT4IE_Msk                    /*!< Fault 4 interrupt Enable                       */
#define HRPWM_IER_FLT3IE_Pos        (3U)
#define HRPWM_IER_FLT3IE_Msk        (0x1UL << HRPWM_IER_FLT3IE_Pos)         /*!< 0x00000008                                     */
#define HRPWM_IER_FLT3IE            HRPWM_IER_FLT3IE_Msk                    /*!< Fault 3 interrupt Enable                       */
#define HRPWM_IER_FLT2IE_Pos        (2U)
#define HRPWM_IER_FLT2IE_Msk        (0x1UL << HRPWM_IER_FLT2IE_Pos)         /*!< 0x00000004                                     */
#define HRPWM_IER_FLT2IE            HRPWM_IER_FLT2IE_Msk                    /*!< Fault 2 interrupt Enable                       */
#define HRPWM_IER_FLT1IE_Pos        (1U)
#define HRPWM_IER_FLT1IE_Msk        (0x1UL << HRPWM_IER_FLT1IE_Pos)         /*!< 0x00000002                                     */
#define HRPWM_IER_FLT1IE            HRPWM_IER_FLT1IE_Msk                    /*!< Fault 1 interrupt Enable                       */
#define HRPWM_IER_FLT0IE_Pos        (0U)
#define HRPWM_IER_FLT0IE_Msk        (0x1UL << HRPWM_IER_FLT0IE_Pos)         /*!< 0x00000001                                     */
#define HRPWM_IER_FLT0IE            HRPWM_IER_FLT0IE_Msk                    /*!< Fault 0 interrupt Enable                       */

/***************  Bit definition for HRPWM_Common_OENR register  **************/
#define HRPWM_OENR_OEN5B_Pos        (11U)
#define HRPWM_OENR_OEN5B_Msk        (0x1UL << HRPWM_OENR_OEN5B_Pos)         /*!< 0x00000800                                     */
#define HRPWM_OENR_OEN5B            HRPWM_OENR_OEN5B_Msk                    /*!< Timer 5 Output B enable                        */
#define HRPWM_OENR_OEN5A_Pos        (10U)
#define HRPWM_OENR_OEN5A_Msk        (0x1UL << HRPWM_OENR_OEN5A_Pos)         /*!< 0x00000400                                     */
#define HRPWM_OENR_OEN5A            HRPWM_OENR_OEN5A_Msk                    /*!< Timer 5 Output A enable                        */
#define HRPWM_OENR_OEN4B_Pos        (9U)
#define HRPWM_OENR_OEN4B_Msk        (0x1UL << HRPWM_OENR_OEN4B_Pos)         /*!< 0x00000200                                     */
#define HRPWM_OENR_OEN4B            HRPWM_OENR_OEN4B_Msk                    /*!< Timer 4 Output B enable                        */
#define HRPWM_OENR_OEN4A_Pos        (8U)
#define HRPWM_OENR_OEN4A_Msk        (0x1UL << HRPWM_OENR_OEN4A_Pos)         /*!< 0x00000100                                     */
#define HRPWM_OENR_OEN4A            HRPWM_OENR_OEN4A_Msk                    /*!< Timer 4 Output A enable                        */
#define HRPWM_OENR_OEN3B_Pos        (7U)
#define HRPWM_OENR_OEN3B_Msk        (0x1UL << HRPWM_OENR_OEN3B_Pos)         /*!< 0x00000080                                     */
#define HRPWM_OENR_OEN3B            HRPWM_OENR_OEN3B_Msk                    /*!< Timer 3 Output B enable                        */
#define HRPWM_OENR_OEN3A_Pos        (6U)
#define HRPWM_OENR_OEN3A_Msk        (0x1UL << HRPWM_OENR_OEN3A_Pos)         /*!< 0x00000040                                     */
#define HRPWM_OENR_OEN3A            HRPWM_OENR_OEN3A_Msk                    /*!< Timer 3 Output A enable                        */
#define HRPWM_OENR_OEN2B_Pos        (5U)
#define HRPWM_OENR_OEN2B_Msk        (0x1UL << HRPWM_OENR_OEN2B_Pos)         /*!< 0x00000020                                     */
#define HRPWM_OENR_OEN2B            HRPWM_OENR_OEN2B_Msk                    /*!< Timer 2 Output B enable                        */
#define HRPWM_OENR_OEN2A_Pos        (4U)
#define HRPWM_OENR_OEN2A_Msk        (0x1UL << HRPWM_OENR_OEN2A_Pos)         /*!< 0x00000010                                     */
#define HRPWM_OENR_OEN2A            HRPWM_OENR_OEN2A_Msk                    /*!< Timer 2 Output A enable                        */
#define HRPWM_OENR_OEN1B_Pos        (3U)
#define HRPWM_OENR_OEN1B_Msk        (0x1UL << HRPWM_OENR_OEN1B_Pos)         /*!< 0x00000008                                     */
#define HRPWM_OENR_OEN1B            HRPWM_OENR_OEN1B_Msk                    /*!< Timer 1 Output B enable                        */
#define HRPWM_OENR_OEN1A_Pos        (2U)
#define HRPWM_OENR_OEN1A_Msk        (0x1UL << HRPWM_OENR_OEN1A_Pos)         /*!< 0x00000004                                     */
#define HRPWM_OENR_OEN1A            HRPWM_OENR_OEN1A_Msk                    /*!< Timer 1 Output A enable                        */
#define HRPWM_OENR_OEN0B_Pos        (1U)
#define HRPWM_OENR_OEN0B_Msk        (0x1UL << HRPWM_OENR_OEN0B_Pos)         /*!< 0x00000002                                     */
#define HRPWM_OENR_OEN0B            HRPWM_OENR_OEN0B_Msk                    /*!< Timer 0 Output B enable                        */
#define HRPWM_OENR_OEN0A_Pos        (0U)
#define HRPWM_OENR_OEN0A_Msk        (0x1UL << HRPWM_OENR_OEN0A_Pos)         /*!< 0x00000001                                     */
#define HRPWM_OENR_OEN0A            HRPWM_OENR_OEN0A_Msk                    /*!< Timer 0 Output A enable                        */

/***************  Bit definition for HRPWM_Common_ODISR register  *************/
#define HRPWM_ODISR_ODIS5B_Pos      (11U)
#define HRPWM_ODISR_ODIS5B_Msk      (0x1UL << HRPWM_ODISR_ODIS5B_Pos)       /*!< 0x00000800                                     */
#define HRPWM_ODISR_ODIS5B          HRPWM_ODISR_ODIS5B_Msk                  /*!< Timer 5 Output B disable                       */
#define HRPWM_ODISR_ODIS5A_Pos      (10U)
#define HRPWM_ODISR_ODIS5A_Msk      (0x1UL << HRPWM_ODISR_ODIS5A_Pos)       /*!< 0x00000400                                     */
#define HRPWM_ODISR_ODIS5A          HRPWM_ODISR_ODIS5A_Msk                  /*!< Timer 5 Output A disable                       */
#define HRPWM_ODISR_ODIS4B_Pos      (9U)
#define HRPWM_ODISR_ODIS4B_Msk      (0x1UL << HRPWM_ODISR_ODIS4B_Pos)       /*!< 0x00000200                                     */
#define HRPWM_ODISR_ODIS4B          HRPWM_ODISR_ODIS4B_Msk                  /*!< Timer 4 Output B disable                       */
#define HRPWM_ODISR_ODIS4A_Pos      (8U)
#define HRPWM_ODISR_ODIS4A_Msk      (0x1UL << HRPWM_ODISR_ODIS4A_Pos)       /*!< 0x00000100                                     */
#define HRPWM_ODISR_ODIS4A          HRPWM_ODISR_ODIS4A_Msk                  /*!< Timer 4 Output A disable                       */
#define HRPWM_ODISR_ODIS3B_Pos      (7U)
#define HRPWM_ODISR_ODIS3B_Msk      (0x1UL << HRPWM_ODISR_ODIS3B_Pos)       /*!< 0x00000080                                     */
#define HRPWM_ODISR_ODIS3B          HRPWM_ODISR_ODIS3B_Msk                  /*!< Timer 3 Output B disable                       */
#define HRPWM_ODISR_ODIS3A_Pos      (6U)
#define HRPWM_ODISR_ODIS3A_Msk      (0x1UL << HRPWM_ODISR_ODIS3A_Pos)       /*!< 0x00000040                                     */
#define HRPWM_ODISR_ODIS3A          HRPWM_ODISR_ODIS3A_Msk                  /*!< Timer 3 Output A disable                       */
#define HRPWM_ODISR_ODIS2B_Pos      (5U)
#define HRPWM_ODISR_ODIS2B_Msk      (0x1UL << HRPWM_ODISR_ODIS2B_Pos)       /*!< 0x00000020                                     */
#define HRPWM_ODISR_ODIS2B          HRPWM_ODISR_ODIS2B_Msk                  /*!< Timer 2 Output B disable                       */
#define HRPWM_ODISR_ODIS2A_Pos      (4U)
#define HRPWM_ODISR_ODIS2A_Msk      (0x1UL << HRPWM_ODISR_ODIS2A_Pos)       /*!< 0x00000010                                     */
#define HRPWM_ODISR_ODIS2A          HRPWM_ODISR_ODIS2A_Msk                  /*!< Timer 2 Output A disable                       */
#define HRPWM_ODISR_ODIS1B_Pos      (3U)
#define HRPWM_ODISR_ODIS1B_Msk      (0x1UL << HRPWM_ODISR_ODIS1B_Pos)       /*!< 0x00000008                                     */
#define HRPWM_ODISR_ODIS1B          HRPWM_ODISR_ODIS1B_Msk                  /*!< Timer 1 Output B disable                       */
#define HRPWM_ODISR_ODIS1A_Pos      (2U)
#define HRPWM_ODISR_ODIS1A_Msk      (0x1UL << HRPWM_ODISR_ODIS1A_Pos)       /*!< 0x00000004                                     */
#define HRPWM_ODISR_ODIS1A          HRPWM_ODISR_ODIS1A_Msk                  /*!< Timer 1 Output A disable                       */
#define HRPWM_ODISR_ODIS0B_Pos      (1U)
#define HRPWM_ODISR_ODIS0B_Msk      (0x1UL << HRPWM_ODISR_ODIS0B_Pos)       /*!< 0x00000002                                     */
#define HRPWM_ODISR_ODIS0B          HRPWM_ODISR_ODIS0B_Msk                  /*!< Timer 0 Output B disable                       */
#define HRPWM_ODISR_ODIS0A_Pos      (0U)
#define HRPWM_ODISR_ODIS0A_Msk      (0x1UL << HRPWM_ODISR_ODIS0A_Pos)       /*!< 0x00000001                                     */
#define HRPWM_ODISR_ODIS0A          HRPWM_ODISR_ODIS0A_Msk                  /*!< Timer 0 Output A disable                       */

/***************  Bit definition for HRPWM_Common_EECR0 register  *************/
#define HRPWM_EECR0_EE4FAST_Pos     (29U)
#define HRPWM_EECR0_EE4FAST_Msk     (0x1UL << HRPWM_EECR0_EE4FAST_Pos)      /*!< 0x20000000                                     */
#define HRPWM_EECR0_EE4FAST         HRPWM_EECR0_EE4FAST_Msk                 /*!< External event 4 Fast mode                     */
#define HRPWM_EECR0_EE4SNS_Pos      (27U)
#define HRPWM_EECR0_EE4SNS_Msk      (0x3UL << HRPWM_EECR0_EE4SNS_Pos)       /*!< 0x18000000                                     */
#define HRPWM_EECR0_EE4SNS          HRPWM_EECR0_EE4SNS_Msk                  /*!< External event 4 sensitivity                   */
#define HRPWM_EECR0_EE4SNS_0        (0x1UL << HRPWM_EECR0_EE4SNS_Pos)       /*!< 0x08000000                                     */
#define HRPWM_EECR0_EE4SNS_1        (0x2UL << HRPWM_EECR0_EE4SNS_Pos)       /*!< 0x10000000                                     */
#define HRPWM_EECR0_EE4POL_Pos      (26U)
#define HRPWM_EECR0_EE4POL_Msk      (0x1UL << HRPWM_EECR0_EE4POL_Pos)       /*!< 0x04000000                                     */
#define HRPWM_EECR0_EE4POL          HRPWM_EECR0_EE4POL_Msk                  /*!< External event 4 Polarity                      */
#define HRPWM_EECR0_EE4SRC_Pos      (24U)
#define HRPWM_EECR0_EE4SRC_Msk      (0x3UL << HRPWM_EECR0_EE4SRC_Pos)       /*!< 0x03000000                                     */
#define HRPWM_EECR0_EE4SRC          HRPWM_EECR0_EE4SRC_Msk                  /*!< External event 4 source                        */
#define HRPWM_EECR0_EE4SRC_0        (0x1UL << HRPWM_EECR0_EE4SRC_Pos)       /*!< 0x01000000                                     */
#define HRPWM_EECR0_EE4SRC_1        (0x2UL << HRPWM_EECR0_EE4SRC_Pos)       /*!< 0x02000000                                     */
#define HRPWM_EECR0_EE3FAST_Pos     (23U)
#define HRPWM_EECR0_EE3FAST_Msk     (0x1UL << HRPWM_EECR0_EE3FAST_Pos)      /*!< 0x00800000                                     */
#define HRPWM_EECR0_EE3FAST         HRPWM_EECR0_EE3FAST_Msk                 /*!< External event 3 Fast mode                     */
#define HRPWM_EECR0_EE3SNS_Pos      (21U)
#define HRPWM_EECR0_EE3SNS_Msk      (0x3UL << HRPWM_EECR0_EE3SNS_Pos)       /*!< 0x00600000                                     */
#define HRPWM_EECR0_EE3SNS          HRPWM_EECR0_EE3SNS_Msk                  /*!< External event 3 sensitivity                   */
#define HRPWM_EECR0_EE3SNS_0        (0x1UL << HRPWM_EECR0_EE3SNS_Pos)       /*!< 0x02000000                                     */
#define HRPWM_EECR0_EE3SNS_1        (0x2UL << HRPWM_EECR0_EE3SNS_Pos)       /*!< 0x04000000                                     */
#define HRPWM_EECR0_EE3POL_Pos      (20U)
#define HRPWM_EECR0_EE3POL_Msk      (0x1UL << HRPWM_EECR0_EE3POL_Pos)       /*!< 0x00100000                                     */
#define HRPWM_EECR0_EE3POL          HRPWM_EECR0_EE3POL_Msk                  /*!< External event 3 Polarity                      */
#define HRPWM_EECR0_EE3SRC_Pos      (18U)
#define HRPWM_EECR0_EE3SRC_Msk      (0x3UL << HRPWM_EECR0_EE3SRC_Pos)       /*!< 0x000C0000                                     */
#define HRPWM_EECR0_EE3SRC          HRPWM_EECR0_EE3SRC_Msk                  /*!< External event 3 source                        */
#define HRPWM_EECR0_EE3SRC_0        (0x1UL << HRPWM_EECR0_EE3SRC_Pos)       /*!< 0x00040000                                     */
#define HRPWM_EECR0_EE3SRC_1        (0x2UL << HRPWM_EECR0_EE3SRC_Pos)       /*!< 0x00080000                                     */
#define HRPWM_EECR0_EE2FAST_Pos     (17U)
#define HRPWM_EECR0_EE2FAST_Msk     (0x1UL << HRPWM_EECR0_EE2FAST_Pos)      /*!< 0x00020000                                     */
#define HRPWM_EECR0_EE2FAST         HRPWM_EECR0_EE2FAST_Msk                 /*!< External event 2 Fast mode                     */
#define HRPWM_EECR0_EE2SNS_Pos      (15U)
#define HRPWM_EECR0_EE2SNS_Msk      (0x3UL << HRPWM_EECR0_EE2SNS_Pos)       /*!< 0x00018000                                     */
#define HRPWM_EECR0_EE2SNS          HRPWM_EECR0_EE2SNS_Msk                  /*!< External event 2 sensitivity                   */
#define HRPWM_EECR0_EE2SNS_0        (0x1UL << HRPWM_EECR0_EE2SNS_Pos)       /*!< 0x00008000                                     */
#define HRPWM_EECR0_EE2SNS_1        (0x2UL << HRPWM_EECR0_EE2SNS_Pos)       /*!< 0x00010000                                     */
#define HRPWM_EECR0_EE2POL_Pos      (14U)
#define HRPWM_EECR0_EE2POL_Msk      (0x1UL << HRPWM_EECR0_EE2POL_Pos)       /*!< 0x00004000                                     */
#define HRPWM_EECR0_EE2POL          HRPWM_EECR0_EE2POL_Msk                  /*!< External event 2 Polarity                      */
#define HRPWM_EECR0_EE2SRC_Pos      (12U)
#define HRPWM_EECR0_EE2SRC_Msk      (0x3UL << HRPWM_EECR0_EE2SRC_Pos)       /*!< 0x00003000                                     */
#define HRPWM_EECR0_EE2SRC          HRPWM_EECR0_EE2SRC_Msk                  /*!< External event 2 source                        */
#define HRPWM_EECR0_EE2SRC_0        (0x1UL << HRPWM_EECR0_EE2SRC_Pos)       /*!< 0x00001000                                     */
#define HRPWM_EECR0_EE2SRC_1        (0x2UL << HRPWM_EECR0_EE2SRC_Pos)       /*!< 0x00002000                                     */
#define HRPWM_EECR0_EE1FAST_Pos     (11U)
#define HRPWM_EECR0_EE1FAST_Msk     (0x1UL << HRPWM_EECR0_EE1FAST_Pos)      /*!< 0x00000800                                     */
#define HRPWM_EECR0_EE1FAST         HRPWM_EECR0_EE1FAST_Msk                 /*!< External event 1 Fast mode                     */
#define HRPWM_EECR0_EE1SNS_Pos      (9U)
#define HRPWM_EECR0_EE1SNS_Msk      (0x3UL << HRPWM_EECR0_EE1SNS_Pos)       /*!< 0x00000600                                     */
#define HRPWM_EECR0_EE1SNS          HRPWM_EECR0_EE1SNS_Msk                  /*!< External event 1 sensitivity                   */
#define HRPWM_EECR0_EE1SNS_0        (0x1UL << HRPWM_EECR0_EE1SNS_Pos)       /*!< 0x00000200                                     */
#define HRPWM_EECR0_EE1SNS_1        (0x2UL << HRPWM_EECR0_EE1SNS_Pos)       /*!< 0x00000400                                     */
#define HRPWM_EECR0_EE1POL_Pos      (8U)
#define HRPWM_EECR0_EE1POL_Msk      (0x1UL << HRPWM_EECR0_EE1POL_Pos)       /*!< 0x00000100                                     */
#define HRPWM_EECR0_EE1POL          HRPWM_EECR0_EE1POL_Msk                  /*!< External event 1 Polarity                      */
#define HRPWM_EECR0_EE1SRC_Pos      (6U)
#define HRPWM_EECR0_EE1SRC_Msk      (0x3UL << HRPWM_EECR0_EE1SRC_Pos)       /*!< 0x000000C0                                     */
#define HRPWM_EECR0_EE1SRC          HRPWM_EECR0_EE1SRC_Msk                  /*!< External event 1 source                        */
#define HRPWM_EECR0_EE1SRC_0        (0x1UL << HRPWM_EECR0_EE1SRC_Pos)       /*!< 0x00000040                                     */
#define HRPWM_EECR0_EE1SRC_1        (0x2UL << HRPWM_EECR0_EE1SRC_Pos)       /*!< 0x00000080                                     */
#define HRPWM_EECR0_EE0FAST_Pos     (5U)
#define HRPWM_EECR0_EE0FAST_Msk     (0x1UL << HRPWM_EECR0_EE0FAST_Pos)      /*!< 0x00000020                                     */
#define HRPWM_EECR0_EE0FAST         HRPWM_EECR0_EE0FAST_Msk                 /*!< External event 0 Fast mode                     */
#define HRPWM_EECR0_EE0SNS_Pos      (3U)
#define HRPWM_EECR0_EE0SNS_Msk      (0x3UL << HRPWM_EECR0_EE0SNS_Pos)       /*!< 0x00000018                                     */
#define HRPWM_EECR0_EE0SNS          HRPWM_EECR0_EE0SNS_Msk                  /*!< External event 0 sensitivity                   */
#define HRPWM_EECR0_EE0SNS_0        (0x1UL << HRPWM_EECR0_EE0SNS_Pos)       /*!< 0x00000008                                     */
#define HRPWM_EECR0_EE0SNS_1        (0x2UL << HRPWM_EECR0_EE0SNS_Pos)       /*!< 0x00000010                                     */
#define HRPWM_EECR0_EE0POL_Pos      (2U)
#define HRPWM_EECR0_EE0POL_Msk      (0x1UL << HRPWM_EECR0_EE0POL_Pos)       /*!< 0x00000004                                     */
#define HRPWM_EECR0_EE0POL          HRPWM_EECR0_EE0POL_Msk                  /*!< External event 0 Polarity                      */
#define HRPWM_EECR0_EE0SRC_Pos      (0U)
#define HRPWM_EECR0_EE0SRC_Msk      (0x3UL << HRPWM_EECR0_EE0SRC_Pos)       /*!< 0x00000003                                     */
#define HRPWM_EECR0_EE0SRC          HRPWM_EECR0_EE0SRC_Msk                  /*!< External event 0 source                        */
#define HRPWM_EECR0_EE0SRC_0        (0x1UL << HRPWM_EECR0_EE0SRC_Pos)       /*!< 0x00000001                                     */
#define HRPWM_EECR0_EE0SRC_1        (0x2UL << HRPWM_EECR0_EE0SRC_Pos)       /*!< 0x00000002                                     */

/***************  Bit definition for HRPWM_Common_EECR1 register  *************/
#define HRPWM_EECR1_EE5FAST_Pos     (5)
#define HRPWM_EECR1_EE5FAST_Msk     (0x1UL << HRPWM_EECR1_EE5FAST_Pos)      /*!< 0x00000020                                     */
#define HRPWM_EECR1_EE5FAST         HRPWM_EECR1_EE5FAST_Msk                 /*!< External event 5 Fast mode                     */
#define HRPWM_EECR1_EE5SNS_Pos      (3U)
#define HRPWM_EECR1_EE5SNS_Msk      (0x3UL << HRPWM_EECR1_EE5SNS_Pos)       /*!< 0x00000018                                     */
#define HRPWM_EECR1_EE5SNS          HRPWM_EECR1_EE5SNS_Msk                  /*!< External event 5 sensitivity                   */
#define HRPWM_EECR1_EE5SNS_0        (0x1UL << HRPWM_EECR1_EE5SNS_Pos)       /*!< 0x00000008                                     */
#define HRPWM_EECR1_EE5SNS_1        (0x2UL << HRPWM_EECR1_EE5SNS_Pos)       /*!< 0x00000010                                     */
#define HRPWM_EECR1_EE5POL_Pos      (2U)
#define HRPWM_EECR1_EE5POL_Msk      (0x1UL << HRPWM_EECR1_EE5POL_Pos)       /*!< 0x00000004                                     */
#define HRPWM_EECR1_EE5POL          HRPWM_EECR1_EE5POL_Msk                  /*!< External event 5 Polarity                      */
#define HRPWM_EECR1_EE5SRC_Pos      (0U)
#define HRPWM_EECR1_EE5SRC_Msk      (0x3UL << HRPWM_EECR1_EE5SRC_Pos)       /*!< 0x00000003                                     */
#define HRPWM_EECR1_EE5SRC          HRPWM_EECR1_EE5SRC_Msk                  /*!< External event 5 source                        */
#define HRPWM_EECR1_EE5SRC_0        (0x1UL << HRPWM_EECR1_EE5SRC_Pos)       /*!< 0x00000001                                     */
#define HRPWM_EECR1_EE5SRC_1        (0x2UL << HRPWM_EECR1_EE5SRC_Pos)       /*!< 0x00000002                                     */

/***************  Bit definition for HRPWM_Common_EECR2 register  *************/
#define HRPWM_EECR2_EEVSD_Pos       (30U)
#define HRPWM_EECR2_EEVSD_Msk       (0x3UL << HRPWM_EECR2_EEVSD_Pos)        /*!< 0xC0000000                                     */
#define HRPWM_EECR2_EEVSD           HRPWM_EECR2_EEVSD_Msk                   /*!< External event sampling clock division         */
#define HRPWM_EECR2_EEVSD_0         (0x1UL << HRPWM_EECR2_EEVSD_Pos)        /*!< 0x40000000                                     */
#define HRPWM_EECR2_EEVSD_1         (0x2UL << HRPWM_EECR2_EEVSD_Pos)        /*!< 0x80000000                                     */
#define HRPWM_EECR2_EE5F_Pos        (20U)
#define HRPWM_EECR2_EE5F_Msk        (0xFUL << HRPWM_EECR2_EE5F_Pos)         /*!< 0x00F00000                                     */
#define HRPWM_EECR2_EE5F            HRPWM_EECR2_EE5F_Msk                    /*!< External event 5 filter                        */
#define HRPWM_EECR2_EE5F_0          (0x1UL << HRPWM_EECR2_EE5F_Pos)         /*!< 0x00100000                                     */
#define HRPWM_EECR2_EE5F_1          (0x2UL << HRPWM_EECR2_EE5F_Pos)         /*!< 0x00200000                                     */
#define HRPWM_EECR2_EE5F_2          (0x4UL << HRPWM_EECR2_EE5F_Pos)         /*!< 0x00400000                                     */
#define HRPWM_EECR2_EE5F_3          (0x8UL << HRPWM_EECR2_EE5F_Pos)         /*!< 0x00800000                                     */
#define HRPWM_EECR2_EE4F_Pos        (16U)
#define HRPWM_EECR2_EE4F_Msk        (0xFUL << HRPWM_EECR2_EE4F_Pos)         /*!< 0x000F0000                                     */
#define HRPWM_EECR2_EE4F            HRPWM_EECR2_EE4F_Msk                    /*!< External event 4 filter                        */
#define HRPWM_EECR2_EE4F_0          (0x1UL << HRPWM_EECR2_EE4F_Pos)         /*!< 0x00010000                                     */
#define HRPWM_EECR2_EE4F_1          (0x2UL << HRPWM_EECR2_EE4F_Pos)         /*!< 0x00020000                                     */
#define HRPWM_EECR2_EE4F_2          (0x4UL << HRPWM_EECR2_EE4F_Pos)         /*!< 0x00040000                                     */
#define HRPWM_EECR2_EE4F_3          (0x8UL << HRPWM_EECR2_EE4F_Pos)         /*!< 0x00080000                                     */
#define HRPWM_EECR2_EE3F_Pos        (12U)
#define HRPWM_EECR2_EE3F_Msk        (0xFUL << HRPWM_EECR2_EE3F_Pos)         /*!< 0x0000F000                                     */
#define HRPWM_EECR2_EE3F            HRPWM_EECR2_EE3F_Msk                    /*!< External event 3 filter                        */
#define HRPWM_EECR2_EE3F_0          (0x1UL << HRPWM_EECR2_EE3F_Pos)         /*!< 0x00001000                                     */
#define HRPWM_EECR2_EE3F_1          (0x2UL << HRPWM_EECR2_EE3F_Pos)         /*!< 0x00002000                                     */
#define HRPWM_EECR2_EE3F_2          (0x4UL << HRPWM_EECR2_EE3F_Pos)         /*!< 0x00004000                                     */
#define HRPWM_EECR2_EE3F_3          (0x8UL << HRPWM_EECR2_EE3F_Pos)         /*!< 0x00008000                                     */
#define HRPWM_EECR2_EE2F_Pos        (8U)
#define HRPWM_EECR2_EE2F_Msk        (0xFUL << HRPWM_EECR2_EE2F_Pos)         /*!< 0x00000F00                                     */
#define HRPWM_EECR2_EE2F            HRPWM_EECR2_EE2F_Msk                    /*!< External event 2 filter                        */
#define HRPWM_EECR2_EE2F_0          (0x1UL << HRPWM_EECR2_EE2F_Pos)         /*!< 0x00000100                                     */
#define HRPWM_EECR2_EE2F_1          (0x2UL << HRPWM_EECR2_EE2F_Pos)         /*!< 0x00000200                                     */
#define HRPWM_EECR2_EE2F_2          (0x4UL << HRPWM_EECR2_EE2F_Pos)         /*!< 0x00000400                                     */
#define HRPWM_EECR2_EE2F_3          (0x8UL << HRPWM_EECR2_EE2F_Pos)         /*!< 0x00000800                                     */
#define HRPWM_EECR2_EE1F_Pos        (4U)
#define HRPWM_EECR2_EE1F_Msk        (0xFUL << HRPWM_EECR2_EE1F_Pos)         /*!< 0x000000F0                                     */
#define HRPWM_EECR2_EE1F            HRPWM_EECR2_EE1F_Msk                    /*!< External event 1 filter                        */
#define HRPWM_EECR2_EE1F_0          (0x1UL << HRPWM_EECR2_EE1F_Pos)         /*!< 0x00000010                                     */
#define HRPWM_EECR2_EE1F_1          (0x2UL << HRPWM_EECR2_EE1F_Pos)         /*!< 0x00000020                                     */
#define HRPWM_EECR2_EE1F_2          (0x4UL << HRPWM_EECR2_EE1F_Pos)         /*!< 0x00000040                                     */
#define HRPWM_EECR2_EE1F_3          (0x8UL << HRPWM_EECR2_EE1F_Pos)         /*!< 0x00000080                                     */
#define HRPWM_EECR2_EE0F_Pos        (0U)
#define HRPWM_EECR2_EE0F_Msk        (0xFUL << HRPWM_EECR2_EE0F_Pos)         /*!< 0x0000000F                                     */
#define HRPWM_EECR2_EE0F            HRPWM_EECR2_EE0F_Msk                    /*!< External event 0 filter                        */
#define HRPWM_EECR2_EE0F_0          (0x1UL << HRPWM_EECR2_EE0F_Pos)         /*!< 0x00000001                                     */
#define HRPWM_EECR2_EE0F_1          (0x2UL << HRPWM_EECR2_EE0F_Pos)         /*!< 0x00000002                                     */
#define HRPWM_EECR2_EE0F_2          (0x4UL << HRPWM_EECR2_EE0F_Pos)         /*!< 0x00000004                                     */
#define HRPWM_EECR2_EE0F_3          (0x8UL << HRPWM_EECR2_EE0F_Pos)         /*!< 0x00000008                                     */

/***************  Bit definition for HRPWM_Common_ADTR0 register  *************/
#define HRPWM_ADT0R_Pos             (0U)
#define HRPWM_ADT0R_Msk             (0xFFFFFFFFUL << HRPWM_ADT0R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT0R                 HRPWM_ADT0R_Msk
#define HRPWM_ADT0R_MCMPA           (0x00000001UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on master compare A              */
#define HRPWM_ADT0R_MCMPB           (0x00000002UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on master compare B              */
#define HRPWM_ADT0R_MCMPC           (0x00000004UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on master compare C              */
#define HRPWM_ADT0R_MCMPD           (0x00000008UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on master compare D              */
#define HRPWM_ADT0R_MPER            (0x00000010UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on master period                 */
#define HRPWM_ADT0R_EEV0            (0x00000020UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on external event 0              */
#define HRPWM_ADT0R_EEV1            (0x00000040UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on external event 1              */
#define HRPWM_ADT0R_EEV2            (0x00000080UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on external event 2              */
#define HRPWM_ADT0R_CMPB5           (0x00000100UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 5 compare B             */
#define HRPWM_ADT0R_RST5            (0x00000200UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 5 reset                 */
#define HRPWM_ADT0R_CMPB0           (0x00000400UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 0 compare B             */
#define HRPWM_ADT0R_CMPC0           (0x00000800UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 0 compare C             */
#define HRPWM_ADT0R_CMPD0           (0x00001000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 0 compare D             */
#define HRPWM_ADT0R_PER0            (0x00002000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 0 period                */
#define HRPWM_ADT0R_CMPB1           (0x00004000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 1 compare B             */
#define HRPWM_ADT0R_CMPC1           (0x00008000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 1 compare C             */
#define HRPWM_ADT0R_CMPD1           (0x00010000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 1 compare D             */
#define HRPWM_ADT0R_RST1            (0x00020000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 1 reset                 */
#define HRPWM_ADT0R_CMPB2           (0x00040000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 2 compare B             */
#define HRPWM_ADT0R_CMPC2           (0x00080000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 2 compare C             */
#define HRPWM_ADT0R_CMPD2           (0x00100000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 2 compare D             */
#define HRPWM_ADT0R_PER2            (0x00200000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 2 period                */
#define HRPWM_ADT0R_CMPB3           (0x00400000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 3 compare B             */
#define HRPWM_ADT0R_CMPC3           (0x00800000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 3 compare C             */
#define HRPWM_ADT0R_CMPD3           (0x01000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 3 compare D             */
#define HRPWM_ADT0R_RST3            (0x02000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 3 reset                 */
#define HRPWM_ADT0R_CMPB4           (0x04000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 4 compare B             */
#define HRPWM_ADT0R_CMPC4           (0x08000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 4 compare C             */
#define HRPWM_ADT0R_CMPD4           (0x10000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 4 compare D             */
#define HRPWM_ADT0R_PER4            (0x20000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 4 period                */
#define HRPWM_ADT0R_CMPC5           (0x40000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 5 compare C             */
#define HRPWM_ADT0R_CMPD5           (0x80000000UL << HRPWM_ADT0R_Pos)       /*!< ADC Trigger 0 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR1 register  *************/
#define HRPWM_ADT1R_Pos             (0U)
#define HRPWM_ADT1R_Msk             (0xFFFFFFFFUL << HRPWM_ADT1R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT1R                 HRPWM_ADT1R_Msk
#define HRPWM_ADT1R_MCMPA           (0x00000001UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on master compare A              */
#define HRPWM_ADT1R_MCMPB           (0x00000002UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on master compare B              */
#define HRPWM_ADT1R_MCMPC           (0x00000004UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on master compare C              */
#define HRPWM_ADT1R_MCMPD           (0x00000008UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on master compare D              */
#define HRPWM_ADT1R_MPER            (0x00000010UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on master period                 */
#define HRPWM_ADT1R_EEV3            (0x00000020UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on external event 3              */
#define HRPWM_ADT1R_EEV4            (0x00000040UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on external event 4              */
#define HRPWM_ADT1R_EEV5            (0x00000080UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on external event 5              */
#define HRPWM_ADT1R_CMPB5           (0x00000100UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 5 compare B             */
#define HRPWM_ADT1R_PER5            (0x00000200UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 5 period                */
#define HRPWM_ADT1R_CMPB0           (0x00000400UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 0 compare B             */
#define HRPWM_ADT1R_CMPC0           (0x00000800UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 0 compare C             */
#define HRPWM_ADT1R_CMPD0           (0x00001000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 0 compare D             */
#define HRPWM_ADT1R_RST0            (0x00002000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 0 reset                 */
#define HRPWM_ADT1R_CMPB1           (0x00004000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 1 compare B             */
#define HRPWM_ADT1R_CMPC1           (0x00008000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 1 compare C             */
#define HRPWM_ADT1R_CMPD1           (0x00010000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 1 compare D             */
#define HRPWM_ADT1R_PER1            (0x00020000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 1 period                */
#define HRPWM_ADT1R_CMPB2           (0x00040000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 2 compare B             */
#define HRPWM_ADT1R_CMPC2           (0x00080000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 2 compare C             */
#define HRPWM_ADT1R_CMPD2           (0x00100000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 2 compare D             */
#define HRPWM_ADT1R_RST2            (0x00200000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 2 reset                 */
#define HRPWM_ADT1R_CMPB3           (0x00400000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 3 compare B             */
#define HRPWM_ADT1R_CMPC3           (0x00800000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 3 compare C             */
#define HRPWM_ADT1R_CMPD3           (0x01000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 3 compare D             */
#define HRPWM_ADT1R_PER3            (0x02000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 3 period                */
#define HRPWM_ADT1R_CMPB4           (0x04000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 4 compare B             */
#define HRPWM_ADT1R_CMPC4           (0x08000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 4 compare C             */
#define HRPWM_ADT1R_CMPD4           (0x10000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 4 compare D             */
#define HRPWM_ADT1R_RST4            (0x20000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 4 reset                 */
#define HRPWM_ADT1R_CMPC5           (0x40000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 5 compare C             */
#define HRPWM_ADT1R_CMPD5           (0x80000000UL << HRPWM_ADT1R_Pos)       /*!< ADC Trigger 1 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR2 register  *************/
#define HRPWM_ADT2R_Pos             (0U)
#define HRPWM_ADT2R_Msk             (0xFFFFFFFFUL << HRPWM_ADT2R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT2R                 HRPWM_ADT2R_Msk
#define HRPWM_ADT2R_MCMPA           (0x00000001UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on master compare A              */
#define HRPWM_ADT2R_MCMPB           (0x00000002UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on master compare B              */
#define HRPWM_ADT2R_MCMPC           (0x00000004UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on master compare C              */
#define HRPWM_ADT2R_MCMPD           (0x00000008UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on master compare D              */
#define HRPWM_ADT2R_MPER            (0x00000010UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on master period                 */
#define HRPWM_ADT2R_EEV0            (0x00000020UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on external event 0              */
#define HRPWM_ADT2R_EEV1            (0x00000040UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on external event 1              */
#define HRPWM_ADT2R_EEV2            (0x00000080UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on external event 2              */
#define HRPWM_ADT2R_CMPB5           (0x00000100UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 5 compare B             */
#define HRPWM_ADT2R_RST5            (0x00000200UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 5 reset                 */
#define HRPWM_ADT2R_CMPB0           (0x00000400UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 0 compare B             */
#define HRPWM_ADT2R_CMPC0           (0x00000800UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 0 compare C             */
#define HRPWM_ADT2R_CMPD0           (0x00001000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 0 compare D             */
#define HRPWM_ADT2R_PER0            (0x00002000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 0 period                */
#define HRPWM_ADT2R_CMPB1           (0x00004000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 1 compare B             */
#define HRPWM_ADT2R_CMPC1           (0x00008000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 1 compare C             */
#define HRPWM_ADT2R_CMPD1           (0x00010000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 1 compare D             */
#define HRPWM_ADT2R_RST1            (0x00020000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 1 reset                 */
#define HRPWM_ADT2R_CMPB2           (0x00040000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 2 compare B             */
#define HRPWM_ADT2R_CMPC2           (0x00080000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 2 compare C             */
#define HRPWM_ADT2R_CMPD2           (0x00100000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 2 compare D             */
#define HRPWM_ADT2R_PER2            (0x00200000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 2 period                */
#define HRPWM_ADT2R_CMPB3           (0x00400000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 3 compare B             */
#define HRPWM_ADT2R_CMPC3           (0x00800000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 3 compare C             */
#define HRPWM_ADT2R_CMPD3           (0x01000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 3 compare D             */
#define HRPWM_ADT2R_RST3            (0x02000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 3 reset                 */
#define HRPWM_ADT2R_CMPB4           (0x04000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 4 compare B             */
#define HRPWM_ADT2R_CMPC4           (0x08000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 4 compare C             */
#define HRPWM_ADT2R_CMPD4           (0x10000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 4 compare D             */
#define HRPWM_ADT2R_PER4            (0x20000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 4 period                */
#define HRPWM_ADT2R_CMPC5           (0x40000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 5 compare C             */
#define HRPWM_ADT2R_CMPD5           (0x80000000UL << HRPWM_ADT2R_Pos)       /*!< ADC Trigger 2 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR3 register  *************/
#define HRPWM_ADT3R_Pos             (0U)
#define HRPWM_ADT3R_Msk             (0xFFFFFFFFUL << HRPWM_ADT3R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT3R                 HRPWM_ADT3R_Msk
#define HRPWM_ADT3R_MCMPA           (0x00000001UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on master compare A              */
#define HRPWM_ADT3R_MCMPB           (0x00000002UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on master compare B              */
#define HRPWM_ADT3R_MCMPC           (0x00000004UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on master compare C              */
#define HRPWM_ADT3R_MCMPD           (0x00000008UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on master compare D              */
#define HRPWM_ADT3R_MPER            (0x00000010UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on master period                 */
#define HRPWM_ADT3R_EEV3            (0x00000020UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on external event 3              */
#define HRPWM_ADT3R_EEV4            (0x00000040UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on external event 4              */
#define HRPWM_ADT3R_EEV5            (0x00000080UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on external event 5              */
#define HRPWM_ADT3R_CMPB5           (0x00000100UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 5 compare B             */
#define HRPWM_ADT3R_PER5            (0x00000200UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 5 period                */
#define HRPWM_ADT3R_CMPB0           (0x00000400UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 0 compare B             */
#define HRPWM_ADT3R_CMPC0           (0x00000800UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 0 compare C             */
#define HRPWM_ADT3R_CMPD0           (0x00001000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 0 compare D             */
#define HRPWM_ADT3R_RST0            (0x00002000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 0 reset                 */
#define HRPWM_ADT3R_CMPB1           (0x00004000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 1 compare B             */
#define HRPWM_ADT3R_CMPC1           (0x00008000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 1 compare C             */
#define HRPWM_ADT3R_CMPD1           (0x00010000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 1 compare D             */
#define HRPWM_ADT3R_PER1            (0x00020000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 1 period                */
#define HRPWM_ADT3R_CMPB2           (0x00040000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 2 compare B             */
#define HRPWM_ADT3R_CMPC2           (0x00080000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 2 compare C             */
#define HRPWM_ADT3R_CMPD2           (0x00100000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 2 compare D             */
#define HRPWM_ADT3R_RST2            (0x00200000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 2 reset                 */
#define HRPWM_ADT3R_CMPB3           (0x00400000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 3 compare B             */
#define HRPWM_ADT3R_CMPC3           (0x00800000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 3 compare C             */
#define HRPWM_ADT3R_CMPD3           (0x01000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 3 compare D             */
#define HRPWM_ADT3R_PER3            (0x02000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 3 period                */
#define HRPWM_ADT3R_CMPB4           (0x04000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 4 compare B             */
#define HRPWM_ADT3R_CMPC4           (0x08000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 4 compare C             */
#define HRPWM_ADT3R_CMPD4           (0x10000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 4 compare D             */
#define HRPWM_ADT3R_RST4            (0x20000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 4 reset                 */
#define HRPWM_ADT3R_CMPC5           (0x40000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 5 compare C             */
#define HRPWM_ADT3R_CMPD5           (0x80000000UL << HRPWM_ADT3R_Pos)       /*!< ADC Trigger 3 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR4 register  *************/
#define HRPWM_ADT4R_Pos             (0U)
#define HRPWM_ADT4R_Msk             (0xFFFFFFFFUL << HRPWM_ADT4R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT4R                 HRPWM_ADT4R_Msk
#define HRPWM_ADT4R_MCMPA           (0x00000001UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on master compare A              */
#define HRPWM_ADT4R_MCMPB           (0x00000002UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on master compare B              */
#define HRPWM_ADT4R_MCMPC           (0x00000004UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on master compare C              */
#define HRPWM_ADT4R_MCMPD           (0x00000008UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on master compare D              */
#define HRPWM_ADT4R_MPER            (0x00000010UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on master period                 */
#define HRPWM_ADT4R_EEV0            (0x00000020UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on external event 0              */
#define HRPWM_ADT4R_EEV1            (0x00000040UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on external event 1              */
#define HRPWM_ADT4R_EEV2            (0x00000080UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on external event 2              */
#define HRPWM_ADT4R_CMPB5           (0x00000100UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 5 compare B             */
#define HRPWM_ADT4R_RST5            (0x00000200UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 5 reset                 */
#define HRPWM_ADT4R_CMPB0           (0x00000400UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 0 compare B             */
#define HRPWM_ADT4R_CMPC0           (0x00000800UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 0 compare C             */
#define HRPWM_ADT4R_CMPD0           (0x00001000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 0 compare D             */
#define HRPWM_ADT4R_PER0            (0x00002000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 0 period                */
#define HRPWM_ADT4R_CMPB1           (0x00004000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 1 compare B             */
#define HRPWM_ADT4R_CMPC1           (0x00008000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 1 compare C             */
#define HRPWM_ADT4R_CMPD1           (0x00010000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 1 compare D             */
#define HRPWM_ADT4R_RST1            (0x00020000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 1 reset                 */
#define HRPWM_ADT4R_CMPB2           (0x00040000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 2 compare B             */
#define HRPWM_ADT4R_CMPC2           (0x00080000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 2 compare C             */
#define HRPWM_ADT4R_CMPD2           (0x00100000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 2 compare D             */
#define HRPWM_ADT4R_PER2            (0x00200000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 2 period                */
#define HRPWM_ADT4R_CMPB3           (0x00400000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 3 compare B             */
#define HRPWM_ADT4R_CMPC3           (0x00800000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 3 compare C             */
#define HRPWM_ADT4R_CMPD3           (0x01000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 3 compare D             */
#define HRPWM_ADT4R_RST3            (0x02000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 3 reset                 */
#define HRPWM_ADT4R_CMPB4           (0x04000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 4 compare B             */
#define HRPWM_ADT4R_CMPC4           (0x08000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 4 compare C             */
#define HRPWM_ADT4R_CMPD4           (0x10000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 4 compare D             */
#define HRPWM_ADT4R_PER4            (0x20000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 4 period                */
#define HRPWM_ADT4R_CMPC5           (0x40000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 5 compare C             */
#define HRPWM_ADT4R_CMPD5           (0x80000000UL << HRPWM_ADT4R_Pos)       /*!< ADC Trigger 4 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR5 register  *************/
#define HRPWM_ADT5R_Pos             (0U)
#define HRPWM_ADT5R_Msk             (0xFFFFFFFFUL << HRPWM_ADT5R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT5R                 HRPWM_ADT5R_Msk
#define HRPWM_ADT5R_MCMPA           (0x00000001UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on master compare A              */
#define HRPWM_ADT5R_MCMPB           (0x00000002UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on master compare B              */
#define HRPWM_ADT5R_MCMPC           (0x00000004UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on master compare C              */
#define HRPWM_ADT5R_MCMPD           (0x00000008UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on master compare D              */
#define HRPWM_ADT5R_MPER            (0x00000010UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on master period                 */
#define HRPWM_ADT5R_EEV3            (0x00000020UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on external event 3              */
#define HRPWM_ADT5R_EEV4            (0x00000040UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on external event 4              */
#define HRPWM_ADT5R_EEV5            (0x00000080UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on external event 5              */
#define HRPWM_ADT5R_CMPB5           (0x00000100UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 5 compare B             */
#define HRPWM_ADT5R_PER5            (0x00000200UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 5 period                */
#define HRPWM_ADT5R_CMPB0           (0x00000400UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 0 compare B             */
#define HRPWM_ADT5R_CMPC0           (0x00000800UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 0 compare C             */
#define HRPWM_ADT5R_CMPD0           (0x00001000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 0 compare D             */
#define HRPWM_ADT5R_RST0            (0x00002000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 0 reset                 */
#define HRPWM_ADT5R_CMPB1           (0x00004000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 1 compare B             */
#define HRPWM_ADT5R_CMPC1           (0x00008000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 1 compare C             */
#define HRPWM_ADT5R_CMPD1           (0x00010000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 1 compare D             */
#define HRPWM_ADT5R_PER1            (0x00020000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 1 period                */
#define HRPWM_ADT5R_CMPB2           (0x00040000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 2 compare B             */
#define HRPWM_ADT5R_CMPC2           (0x00080000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 2 compare C             */
#define HRPWM_ADT5R_CMPD2           (0x00100000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 2 compare D             */
#define HRPWM_ADT5R_RST2            (0x00200000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 2 reset                 */
#define HRPWM_ADT5R_CMPB3           (0x00400000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 3 compare B             */
#define HRPWM_ADT5R_CMPC3           (0x00800000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 3 compare C             */
#define HRPWM_ADT5R_CMPD3           (0x01000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 3 compare D             */
#define HRPWM_ADT5R_PER3            (0x02000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 3 period                */
#define HRPWM_ADT5R_CMPB4           (0x04000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 4 compare B             */
#define HRPWM_ADT5R_CMPC4           (0x08000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 4 compare C             */
#define HRPWM_ADT5R_CMPD4           (0x10000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 4 compare D             */
#define HRPWM_ADT5R_RST4            (0x20000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 4 reset                 */
#define HRPWM_ADT5R_CMPC5           (0x40000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 5 compare C             */
#define HRPWM_ADT5R_CMPD5           (0x80000000UL << HRPWM_ADT5R_Pos)       /*!< ADC Trigger 5 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR6 register  *************/
#define HRPWM_ADT6R_Pos             (0U)
#define HRPWM_ADT6R_Msk             (0xFFFFFFFFUL << HRPWM_ADT6R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT6R                 HRPWM_ADT6R_Msk
#define HRPWM_ADT6R_MCMPA           (0x00000001UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on master compare A              */
#define HRPWM_ADT6R_MCMPB           (0x00000002UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on master compare B              */
#define HRPWM_ADT6R_MCMPC           (0x00000004UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on master compare C              */
#define HRPWM_ADT6R_MCMPD           (0x00000008UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on master compare D              */
#define HRPWM_ADT6R_MPER            (0x00000010UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on master period                 */
#define HRPWM_ADT6R_EEV0            (0x00000020UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on external event 0              */
#define HRPWM_ADT6R_EEV1            (0x00000040UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on external event 1              */
#define HRPWM_ADT6R_EEV2            (0x00000080UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on external event 2              */
#define HRPWM_ADT6R_CMPB5           (0x00000100UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 5 compare B             */
#define HRPWM_ADT6R_RST5            (0x00000200UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 5 reset                 */
#define HRPWM_ADT6R_CMPB0           (0x00000400UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 0 compare B             */
#define HRPWM_ADT6R_CMPC0           (0x00000800UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 0 compare C             */
#define HRPWM_ADT6R_CMPD0           (0x00001000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 0 compare D             */
#define HRPWM_ADT6R_PER0            (0x00002000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 0 period                */
#define HRPWM_ADT6R_CMPB1           (0x00004000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 1 compare B             */
#define HRPWM_ADT6R_CMPC1           (0x00008000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 1 compare C             */
#define HRPWM_ADT6R_CMPD1           (0x00010000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 1 compare D             */
#define HRPWM_ADT6R_RST1            (0x00020000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 1 reset                 */
#define HRPWM_ADT6R_CMPB2           (0x00040000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 2 compare B             */
#define HRPWM_ADT6R_CMPC2           (0x00080000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 2 compare C             */
#define HRPWM_ADT6R_CMPD2           (0x00100000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 2 compare D             */
#define HRPWM_ADT6R_PER2            (0x00200000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 2 period                */
#define HRPWM_ADT6R_CMPB3           (0x00400000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 3 compare B             */
#define HRPWM_ADT6R_CMPC3           (0x00800000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 3 compare C             */
#define HRPWM_ADT6R_CMPD3           (0x01000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 3 compare D             */
#define HRPWM_ADT6R_RST3            (0x02000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 3 reset                 */
#define HRPWM_ADT6R_CMPB4           (0x04000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 4 compare B             */
#define HRPWM_ADT6R_CMPC4           (0x08000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 4 compare C             */
#define HRPWM_ADT6R_CMPD4           (0x10000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 4 compare D             */
#define HRPWM_ADT6R_PER4            (0x20000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 4 period                */
#define HRPWM_ADT6R_CMPC5           (0x40000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 5 compare C             */
#define HRPWM_ADT6R_CMPD5           (0x80000000UL << HRPWM_ADT6R_Pos)       /*!< ADC Trigger 6 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADTR7 register  *************/
#define HRPWM_ADT7R_Pos             (0U)
#define HRPWM_ADT7R_Msk             (0xFFFFFFFFUL << HRPWM_ADT7R_Pos)       /*!< 0xFFFFFFFF                                     */
#define HRPWM_ADT7R                 HRPWM_ADT7R_Msk
#define HRPWM_ADT7R_MCMPA           (0x00000001UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on master compare A              */
#define HRPWM_ADT7R_MCMPB           (0x00000002UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on master compare B              */
#define HRPWM_ADT7R_MCMPC           (0x00000004UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on master compare C              */
#define HRPWM_ADT7R_MCMPD           (0x00000008UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on master compare D              */
#define HRPWM_ADT7R_MPER            (0x00000010UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on master period                 */
#define HRPWM_ADT7R_EEV3            (0x00000020UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on external event 3              */
#define HRPWM_ADT7R_EEV4            (0x00000040UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on external event 4              */
#define HRPWM_ADT7R_EEV5            (0x00000080UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on external event 5              */
#define HRPWM_ADT7R_CMPB5           (0x00000100UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 5 compare B             */
#define HRPWM_ADT7R_PER5            (0x00000200UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 5 period                */
#define HRPWM_ADT7R_CMPB0           (0x00000400UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 0 compare B             */
#define HRPWM_ADT7R_CMPC0           (0x00000800UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 0 compare C             */
#define HRPWM_ADT7R_CMPD0           (0x00001000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 0 compare D             */
#define HRPWM_ADT7R_RST0            (0x00002000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 0 reset                 */
#define HRPWM_ADT7R_CMPB1           (0x00004000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 1 compare B             */
#define HRPWM_ADT7R_CMPC1           (0x00008000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 1 compare C             */
#define HRPWM_ADT7R_CMPD1           (0x00010000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 1 compare D             */
#define HRPWM_ADT7R_PER1            (0x00020000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 1 period                */
#define HRPWM_ADT7R_CMPB2           (0x00040000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 2 compare B             */
#define HRPWM_ADT7R_CMPC2           (0x00080000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 2 compare C             */
#define HRPWM_ADT7R_CMPD2           (0x00100000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 2 compare D             */
#define HRPWM_ADT7R_RST2            (0x00200000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 2 reset                 */
#define HRPWM_ADT7R_CMPB3           (0x00400000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 3 compare B             */
#define HRPWM_ADT7R_CMPC3           (0x00800000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 3 compare C             */
#define HRPWM_ADT7R_CMPD3           (0x01000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 3 compare D             */
#define HRPWM_ADT7R_PER3            (0x02000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 3 period                */
#define HRPWM_ADT7R_CMPB4           (0x04000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 4 compare B             */
#define HRPWM_ADT7R_CMPC4           (0x08000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 4 compare C             */
#define HRPWM_ADT7R_CMPD4           (0x10000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 4 compare D             */
#define HRPWM_ADT7R_RST4            (0x20000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 4 reset                 */
#define HRPWM_ADT7R_CMPC5           (0x40000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 5 compare C             */
#define HRPWM_ADT7R_CMPD5           (0x80000000UL << HRPWM_ADT7R_Pos)       /*!< ADC Trigger 7 on Timer 5 compare D             */

/***************  Bit definition for HRPWM_Common_ADPSR register  *************/
#define HRPWM_ADPSR_ADPSC7_Pos      (28U)
#define HRPWM_ADPSR_ADPSC7_Msk      (0xFUL << HRPWM_ADPSR_ADPSC7_Pos)       /*!< 0xF0000000                                     */
#define HRPWM_ADPSR_ADPSC7          HRPWM_ADPSR_ADPSC7_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC7_0        (0x1UL << HRPWM_ADPSR_ADPSC7_Pos)       /*!< 0x10000000                                     */
#define HRPWM_ADPSR_ADPSC7_1        (0x2UL << HRPWM_ADPSR_ADPSC7_Pos)       /*!< 0x20000000                                     */
#define HRPWM_ADPSR_ADPSC7_2        (0x4UL << HRPWM_ADPSR_ADPSC7_Pos)       /*!< 0x40000000                                     */
#define HRPWM_ADPSR_ADPSC7_3        (0x8UL << HRPWM_ADPSR_ADPSC7_Pos)       /*!< 0x80000000                                     */
#define HRPWM_ADPSR_ADPSC6_Pos      (24U)
#define HRPWM_ADPSR_ADPSC6_Msk      (0xFUL << HRPWM_ADPSR_ADPSC6_Pos)       /*!< 0x0F000000                                     */
#define HRPWM_ADPSR_ADPSC6          HRPWM_ADPSR_ADPSC6_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC6_0        (0x1UL << HRPWM_ADPSR_ADPSC6_Pos)       /*!< 0x01000000                                     */
#define HRPWM_ADPSR_ADPSC6_1        (0x2UL << HRPWM_ADPSR_ADPSC6_Pos)       /*!< 0x02000000                                     */
#define HRPWM_ADPSR_ADPSC6_2        (0x4UL << HRPWM_ADPSR_ADPSC6_Pos)       /*!< 0x04000000                                     */
#define HRPWM_ADPSR_ADPSC6_3        (0x8UL << HRPWM_ADPSR_ADPSC6_Pos)       /*!< 0x08000000                                     */
#define HRPWM_ADPSR_ADPSC5_Pos      (20U)
#define HRPWM_ADPSR_ADPSC5_Msk      (0xFUL << HRPWM_ADPSR_ADPSC5_Pos)       /*!< 0x00F00000                                     */
#define HRPWM_ADPSR_ADPSC5          HRPWM_ADPSR_ADPSC5_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC5_0        (0x1UL << HRPWM_ADPSR_ADPSC5_Pos)       /*!< 0x00100000                                     */
#define HRPWM_ADPSR_ADPSC5_1        (0x2UL << HRPWM_ADPSR_ADPSC5_Pos)       /*!< 0x00200000                                     */
#define HRPWM_ADPSR_ADPSC5_2        (0x4UL << HRPWM_ADPSR_ADPSC5_Pos)       /*!< 0x00400000                                     */
#define HRPWM_ADPSR_ADPSC5_3        (0x8UL << HRPWM_ADPSR_ADPSC5_Pos)       /*!< 0x00800000                                     */
#define HRPWM_ADPSR_ADPSC4_Pos      (16U)
#define HRPWM_ADPSR_ADPSC4_Msk      (0xFUL << HRPWM_ADPSR_ADPSC4_Pos)       /*!< 0x000F0000                                     */
#define HRPWM_ADPSR_ADPSC4          HRPWM_ADPSR_ADPSC4_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC4_0        (0x1UL << HRPWM_ADPSR_ADPSC4_Pos)       /*!< 0x00010000                                     */
#define HRPWM_ADPSR_ADPSC4_1        (0x2UL << HRPWM_ADPSR_ADPSC4_Pos)       /*!< 0x00020000                                     */
#define HRPWM_ADPSR_ADPSC4_2        (0x4UL << HRPWM_ADPSR_ADPSC4_Pos)       /*!< 0x00040000                                     */
#define HRPWM_ADPSR_ADPSC4_3        (0x8UL << HRPWM_ADPSR_ADPSC4_Pos)       /*!< 0x00080000                                     */
#define HRPWM_ADPSR_ADPSC3_Pos      (12U)
#define HRPWM_ADPSR_ADPSC3_Msk      (0xFUL << HRPWM_ADPSR_ADPSC3_Pos)       /*!< 0x0000F000                                     */
#define HRPWM_ADPSR_ADPSC3          HRPWM_ADPSR_ADPSC3_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC3_0        (0x1UL << HRPWM_ADPSR_ADPSC3_Pos)       /*!< 0x00001000                                     */
#define HRPWM_ADPSR_ADPSC3_1        (0x2UL << HRPWM_ADPSR_ADPSC3_Pos)       /*!< 0x00002000                                     */
#define HRPWM_ADPSR_ADPSC3_2        (0x4UL << HRPWM_ADPSR_ADPSC3_Pos)       /*!< 0x00004000                                     */
#define HRPWM_ADPSR_ADPSC3_3        (0x8UL << HRPWM_ADPSR_ADPSC3_Pos)       /*!< 0x00008000                                     */
#define HRPWM_ADPSR_ADPSC2_Pos      (8U)
#define HRPWM_ADPSR_ADPSC2_Msk      (0xFUL << HRPWM_ADPSR_ADPSC2_Pos)       /*!< 0x00000F00                                     */
#define HRPWM_ADPSR_ADPSC2          HRPWM_ADPSR_ADPSC2_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC2_0        (0x1UL << HRPWM_ADPSR_ADPSC2_Pos)       /*!< 0x00000100                                     */
#define HRPWM_ADPSR_ADPSC2_1        (0x2UL << HRPWM_ADPSR_ADPSC2_Pos)       /*!< 0x00000200                                     */
#define HRPWM_ADPSR_ADPSC2_2        (0x4UL << HRPWM_ADPSR_ADPSC2_Pos)       /*!< 0x00000400                                     */
#define HRPWM_ADPSR_ADPSC2_3        (0x8UL << HRPWM_ADPSR_ADPSC2_Pos)       /*!< 0x00000800                                     */
#define HRPWM_ADPSR_ADPSC1_Pos      (4U)
#define HRPWM_ADPSR_ADPSC1_Msk      (0xFUL << HRPWM_ADPSR_ADPSC1_Pos)       /*!< 0x000000F0                                     */
#define HRPWM_ADPSR_ADPSC1          HRPWM_ADPSR_ADPSC1_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC1_0        (0x1UL << HRPWM_ADPSR_ADPSC1_Pos)       /*!< 0x00000010                                     */
#define HRPWM_ADPSR_ADPSC1_1        (0x2UL << HRPWM_ADPSR_ADPSC1_Pos)       /*!< 0x00000020                                     */
#define HRPWM_ADPSR_ADPSC1_2        (0x4UL << HRPWM_ADPSR_ADPSC1_Pos)       /*!< 0x00000040                                     */
#define HRPWM_ADPSR_ADPSC1_3        (0x8UL << HRPWM_ADPSR_ADPSC1_Pos)       /*!< 0x00000080                                     */
#define HRPWM_ADPSR_ADPSC0_Pos      (0U)
#define HRPWM_ADPSR_ADPSC0_Msk      (0xFUL << HRPWM_ADPSR_ADPSC0_Pos)       /*!< 0x0000000F                                     */
#define HRPWM_ADPSR_ADPSC0          HRPWM_ADPSR_ADPSC0_Msk                  /*!< ADC Trigger post scaler                        */
#define HRPWM_ADPSR_ADPSC0_0        (0x1UL << HRPWM_ADPSR_ADPSC0_Pos)       /*!< 0x00000001                                     */
#define HRPWM_ADPSR_ADPSC0_1        (0x2UL << HRPWM_ADPSR_ADPSC0_Pos)       /*!< 0x00000002                                     */
#define HRPWM_ADPSR_ADPSC0_2        (0x4UL << HRPWM_ADPSR_ADPSC0_Pos)       /*!< 0x00000004                                     */
#define HRPWM_ADPSR_ADPSC0_3        (0x8UL << HRPWM_ADPSR_ADPSC0_Pos)       /*!< 0x00000008                                     */

/***************  Bit definition for HRPWM_Common_DLLR register  **************/
#define HRPWM_DLLCR_DLLTHRES0_Pos   (11U)
#define HRPWM_DLLCR_DLLTHRES0_Msk   (0x1FUL << HRPWM_DLLCR_DLLTHRES0_Pos)   /*!< 0x0000F800                                     */
#define HRPWM_DLLCR_DLLTHRES0       HRPWM_DLLCR_DLLTHRES0_Msk               /*!< DLL calibration rate                           */
#define HRPWM_DLLCR_DLLTHRES0_0     (0x01UL << HRPWM_DLLCR_DLLTHRES0_Pos)   /*!< 0x00000800                                     */
#define HRPWM_DLLCR_DLLTHRES0_1     (0x02UL << HRPWM_DLLCR_DLLTHRES0_Pos)   /*!< 0x00001000                                     */
#define HRPWM_DLLCR_DLLTHRES0_2     (0x04UL << HRPWM_DLLCR_DLLTHRES0_Pos)   /*!< 0x00002000                                     */
#define HRPWM_DLLCR_DLLTHRES0_3     (0x08UL << HRPWM_DLLCR_DLLTHRES0_Pos)   /*!< 0x00004000                                     */
#define HRPWM_DLLCR_DLLTHRES0_4     (0x10UL << HRPWM_DLLCR_DLLTHRES0_Pos)   /*!< 0x00008000                                     */
#define HRPWM_DLLCR_DLLTHRES1_Pos   (6U)
#define HRPWM_DLLCR_DLLTHRES1_Msk   (0x1FUL << HRPWM_DLLCR_DLLTHRES1_Pos)   /*!< 0x000007C0                                     */
#define HRPWM_DLLCR_DLLTHRES1       HRPWM_DLLCR_DLLTHRES1_Msk               /*!< DLL calibration rate                           */
#define HRPWM_DLLCR_DLLTHRES1_0     (0x01UL << HRPWM_DLLCR_DLLTHRES1_Pos)   /*!< 0x00000040                                     */
#define HRPWM_DLLCR_DLLTHRES1_1     (0x02UL << HRPWM_DLLCR_DLLTHRES1_Pos)   /*!< 0x00000080                                     */
#define HRPWM_DLLCR_DLLTHRES1_2     (0x04UL << HRPWM_DLLCR_DLLTHRES1_Pos)   /*!< 0x00000100                                     */
#define HRPWM_DLLCR_DLLTHRES1_3     (0x08UL << HRPWM_DLLCR_DLLTHRES1_Pos)   /*!< 0x00000200                                     */
#define HRPWM_DLLCR_DLLTHRES1_4     (0x10UL << HRPWM_DLLCR_DLLTHRES1_Pos)   /*!< 0x00000400                                     */
#define HRPWM_DLLCR_DLLSTART_Pos    (3U)
#define HRPWM_DLLCR_DLLSTART_Msk    (0x1UL << HRPWM_DLLCR_DLLSTART_Pos)     /*!< 0x00000008                                     */
#define HRPWM_DLLCR_DLLSTART        HRPWM_DLLCR_DLLSTART_Msk                /*!< DLL calibration start                          */
#define HRPWM_DLLCR_DLLGCP_Pos      (1U)
#define HRPWM_DLLCR_DLLGCP_Msk      (0x3UL << HRPWM_DLLCR_DLLGCP_Pos)       /*!< 0x00000006                                     */
#define HRPWM_DLLCR_DLLGCP          HRPWM_DLLCR_DLLGCP_Msk                  /*!< DLL calibration rate                           */
#define HRPWM_DLLCR_DLLGCP_0        (0x1UL << HRPWM_DLLCR_DLLGCP_Pos)       /*!< 0x00000002                                     */
#define HRPWM_DLLCR_DLLGCP_1        (0x2UL << HRPWM_DLLCR_DLLGCP_Pos)       /*!< 0x00000004                                     */
#define HRPWM_DLLCR_DLLEN_Pos       (0U)
#define HRPWM_DLLCR_DLLEN_Msk       (0x1UL << HRPWM_DLLCR_DLLEN_Pos)        /*!< 0x00000001                                     */
#define HRPWM_DLLCR_DLLEN           HRPWM_DLLCR_DLLEN_Msk                   /*!< DLL calibration enable                         */

/**************  Bit definition for HRPWM_Common_FINTR0 register  *************/
#define HRPWM_FLTINR0_FLT5SRC_Pos   (22U)
#define HRPWM_FLTINR0_FLT5SRC_Msk   (0x3UL << HRPWM_FLTINR0_FLT5SRC_Pos)    /*!< 0x00C00000                                     */
#define HRPWM_FLTINR0_FLT5SRC       HRPWM_FLTINR0_FLT5SRC_Msk               /*!< Fault 5 source bit 0                           */
#define HRPWM_FLTINR0_FLT5SRC_0     (0x1UL << HRPWM_FLTINR0_FLT5SRC_Pos)    /*!< 0x00400000                                     */
#define HRPWM_FLTINR0_FLT5SRC_1     (0x2UL << HRPWM_FLTINR0_FLT5SRC_Pos)    /*!< 0x00800000                                     */
#define HRPWM_FLTINR0_FLT5P_Pos     (21U)
#define HRPWM_FLTINR0_FLT5P_Msk     (0x1UL << HRPWM_FLTINR0_FLT5P_Pos)      /*!< 0x00200000                                     */
#define HRPWM_FLTINR0_FLT5P         HRPWM_FLTINR0_FLT5P_Msk                 /*!< Fault 5 polarity                               */
#define HRPWM_FLTINR0_FLT5E_Pos     (20U)
#define HRPWM_FLTINR0_FLT5E_Msk     (0x1UL << HRPWM_FLTINR0_FLT5E_Pos)      /*!< 0x00100000                                     */
#define HRPWM_FLTINR0_FLT5E         HRPWM_FLTINR0_FLT5E_Msk                 /*!< Fault 5 enable                                 */
#define HRPWM_FLTINR0_FLT4SRC_Pos   (18U)
#define HRPWM_FLTINR0_FLT4SRC_Msk   (0x3UL << HRPWM_FLTINR0_FLT4SRC_Pos)    /*!< 0x000C0000                                     */
#define HRPWM_FLTINR0_FLT4SRC       HRPWM_FLTINR0_FLT4SRC_Msk               /*!< Fault 4 source bit 0                           */
#define HRPWM_FLTINR0_FLT4SRC_0     (0x1UL << HRPWM_FLTINR0_FLT4SRC_Pos)    /*!< 0x00400000                                     */
#define HRPWM_FLTINR0_FLT4SRC_1     (0x2UL << HRPWM_FLTINR0_FLT4SRC_Pos)    /*!< 0x00800000                                     */
#define HRPWM_FLTINR0_FLT4P_Pos     (17U)
#define HRPWM_FLTINR0_FLT4P_Msk     (0x1UL << HRPWM_FLTINR0_FLT4P_Pos)      /*!< 0x00020000                                     */
#define HRPWM_FLTINR0_FLT4P         HRPWM_FLTINR0_FLT4P_Msk                 /*!< Fault 4 polarity                               */
#define HRPWM_FLTINR0_FLT4E_Pos     (16U)
#define HRPWM_FLTINR0_FLT4E_Msk     (0x1UL << HRPWM_FLTINR0_FLT4E_Pos)      /*!< 0x00010000                                     */
#define HRPWM_FLTINR0_FLT4E         HRPWM_FLTINR0_FLT4E_Msk                 /*!< Fault 4 enable                                 */
#define HRPWM_FLTINR0_FLT3SRC_Pos   (14U)
#define HRPWM_FLTINR0_FLT3SRC_Msk   (0x3UL << HRPWM_FLTINR0_FLT3SRC_Pos)    /*!< 0x0000C000                                     */
#define HRPWM_FLTINR0_FLT3SRC       HRPWM_FLTINR0_FLT3SRC_Msk               /*!< Fault 3 source bit 0                           */
#define HRPWM_FLTINR0_FLT3SRC_0     (0x1UL << HRPWM_FLTINR0_FLT3SRC_Pos)    /*!< 0x00004000                                     */
#define HRPWM_FLTINR0_FLT3SRC_1     (0x2UL << HRPWM_FLTINR0_FLT3SRC_Pos)    /*!< 0x00008000                                     */
#define HRPWM_FLTINR0_FLT3P_Pos     (13U)
#define HRPWM_FLTINR0_FLT3P_Msk     (0x1UL << HRPWM_FLTINR0_FLT3P_Pos)      /*!< 0x00002000                                     */
#define HRPWM_FLTINR0_FLT3P         HRPWM_FLTINR0_FLT3P_Msk                 /*!< Fault 3 polarity                               */
#define HRPWM_FLTINR0_FLT3E_Pos     (12U)
#define HRPWM_FLTINR0_FLT3E_Msk     (0x1UL << HRPWM_FLTINR0_FLT3E_Pos)      /*!< 0x00001000                                     */
#define HRPWM_FLTINR0_FLT3E         HRPWM_FLTINR0_FLT3E_Msk                 /*!< Fault 3 enable                                 */
#define HRPWM_FLTINR0_FLT2SRC_Pos   (10U)
#define HRPWM_FLTINR0_FLT2SRC_Msk   (0x3UL << HRPWM_FLTINR0_FLT2SRC_Pos)    /*!< 0x00000C00                                     */
#define HRPWM_FLTINR0_FLT2SRC       HRPWM_FLTINR0_FLT2SRC_Msk               /*!< Fault 2 source bit 0                           */
#define HRPWM_FLTINR0_FLT2SRC_0     (0x1UL << HRPWM_FLTINR0_FLT2SRC_Pos)    /*!< 0x00000400                                     */
#define HRPWM_FLTINR0_FLT2SRC_1     (0x2UL << HRPWM_FLTINR0_FLT2SRC_Pos)    /*!< 0x00000800                                     */
#define HRPWM_FLTINR0_FLT2P_Pos     (9U)
#define HRPWM_FLTINR0_FLT2P_Msk     (0x1UL << HRPWM_FLTINR0_FLT2P_Pos)      /*!< 0x00000200                                     */
#define HRPWM_FLTINR0_FLT2P         HRPWM_FLTINR0_FLT2P_Msk                 /*!< Fault 2 polarity                               */
#define HRPWM_FLTINR0_FLT2E_Pos     (8U)
#define HRPWM_FLTINR0_FLT2E_Msk     (0x1UL << HRPWM_FLTINR0_FLT2E_Pos)      /*!< 0x00000100                                     */
#define HRPWM_FLTINR0_FLT2E         HRPWM_FLTINR0_FLT2E_Msk                 /*!< Fault 2 enable                                 */
#define HRPWM_FLTINR0_FLT1SRC_Pos   (6U)
#define HRPWM_FLTINR0_FLT1SRC_Msk   (0x3UL << HRPWM_FLTINR0_FLT1SRC_Pos)    /*!< 0x000000C0                                     */
#define HRPWM_FLTINR0_FLT1SRC       HRPWM_FLTINR0_FLT1SRC_Msk               /*!< Fault 1 source bit 0                           */
#define HRPWM_FLTINR0_FLT1SRC_0     (0x1UL << HRPWM_FLTINR0_FLT1SRC_Pos)    /*!< 0x00000040                                     */
#define HRPWM_FLTINR0_FLT1SRC_1     (0x2UL << HRPWM_FLTINR0_FLT1SRC_Pos)    /*!< 0x00000080                                     */
#define HRPWM_FLTINR0_FLT1P_Pos     (5U)
#define HRPWM_FLTINR0_FLT1P_Msk     (0x1UL << HRPWM_FLTINR0_FLT1P_Pos)      /*!< 0x00000020                                     */
#define HRPWM_FLTINR0_FLT1P         HRPWM_FLTINR0_FLT1P_Msk                 /*!< Fault 1 polarity                               */
#define HRPWM_FLTINR0_FLT1E_Pos     (4U)
#define HRPWM_FLTINR0_FLT1E_Msk     (0x1UL << HRPWM_FLTINR0_FLT1E_Pos)      /*!< 0x00000010                                     */
#define HRPWM_FLTINR0_FLT1E         HRPWM_FLTINR0_FLT1E_Msk                 /*!< Fault 1 enable                                 */
#define HRPWM_FLTINR0_FLT0SRC_Pos   (2U)
#define HRPWM_FLTINR0_FLT0SRC_Msk   (0x3UL << HRPWM_FLTINR0_FLT0SRC_Pos)     /*!< 0x0000000C                                     */
#define HRPWM_FLTINR0_FLT0SRC       HRPWM_FLTINR0_FLT0SRC_Msk               /*!< Fault 0 source bit 0                           */
#define HRPWM_FLTINR0_FLT0SRC_0     (0x1UL << HRPWM_FLTINR0_FLT0SRC_Pos)    /*!< 0x00000004                                     */
#define HRPWM_FLTINR0_FLT0SRC_1     (0x2UL << HRPWM_FLTINR0_FLT0SRC_Pos)    /*!< 0x00000008                                     */
#define HRPWM_FLTINR0_FLT0P_Pos     (1U)
#define HRPWM_FLTINR0_FLT0P_Msk     (0x1UL << HRPWM_FLTINR0_FLT0P_Pos)      /*!< 0x00000002                                     */
#define HRPWM_FLTINR0_FLT0P         HRPWM_FLTINR0_FLT0P_Msk                 /*!< Fault 0 polarity                               */
#define HRPWM_FLTINR0_FLT0E_Pos     (0U)
#define HRPWM_FLTINR0_FLT0E_Msk     (0x1UL << HRPWM_FLTINR0_FLT0E_Pos)      /*!< 0x00000001                                     */
#define HRPWM_FLTINR0_FLT0E         HRPWM_FLTINR0_FLT0E_Msk                 /*!< Fault 0 enable                                 */

/**************  Bit definition for HRPWM_Common_FINTR1 register  *************/
#define HRPWM_FLTINR1_FLTSD_Pos     (30U)
#define HRPWM_FLTINR1_FLTSD_Msk     (0x3UL << HRPWM_FLTINR1_FLTSD_Pos)      /*!< 0xC0000000                                     */
#define HRPWM_FLTINR1_FLTSD         HRPWM_FLTINR1_FLTSD_Msk                 /*!< Fault sampling clock division                  */
#define HRPWM_FLTINR1_FLTSD_0       (0x1UL << HRPWM_FLTINR1_FLTSD_Pos)      /*!< 0x40000000                                     */
#define HRPWM_FLTINR1_FLTSD_1       (0x2UL << HRPWM_FLTINR1_FLTSD_Pos)      /*!< 0x80000000                                     */
#define HRPWM_FLTINR1_FLT5F_Pos     (20U)
#define HRPWM_FLTINR1_FLT5F_Msk     (0xFUL << HRPWM_FLTINR1_FLT5F_Pos)      /*!< 0x00F00000                                     */
#define HRPWM_FLTINR1_FLT5F         HRPWM_FLTINR1_FLT5F_Msk                 /*!< Fault 5 filter                                 */
#define HRPWM_FLTINR1_FLT5F_0       (0x1UL << HRPWM_FLTINR1_FLT5F_Pos)      /*!< 0x00100000                                     */
#define HRPWM_FLTINR1_FLT5F_1       (0x2UL << HRPWM_FLTINR1_FLT5F_Pos)      /*!< 0x00200000                                     */
#define HRPWM_FLTINR1_FLT5F_2       (0x4UL << HRPWM_FLTINR1_FLT5F_Pos)      /*!< 0x00400000                                     */
#define HRPWM_FLTINR1_FLT5F_3       (0x8UL << HRPWM_FLTINR1_FLT5F_Pos)      /*!< 0x00800000                                     */
#define HRPWM_FLTINR1_FLT4F_Pos     (16U)
#define HRPWM_FLTINR1_FLT4F_Msk     (0xFUL << HRPWM_FLTINR1_FLT4F_Pos)      /*!< 0x000F0000                                     */
#define HRPWM_FLTINR1_FLT4F         HRPWM_FLTINR1_FLT4F_Msk                 /*!< Fault 4 filter                                 */
#define HRPWM_FLTINR1_FLT4F_0       (0x1UL << HRPWM_FLTINR1_FLT4F_Pos)      /*!< 0x00010000                                     */
#define HRPWM_FLTINR1_FLT4F_1       (0x2UL << HRPWM_FLTINR1_FLT4F_Pos)      /*!< 0x00020000                                     */
#define HRPWM_FLTINR1_FLT4F_2       (0x4UL << HRPWM_FLTINR1_FLT4F_Pos)      /*!< 0x00040000                                     */
#define HRPWM_FLTINR1_FLT4F_3       (0x8UL << HRPWM_FLTINR1_FLT4F_Pos)      /*!< 0x00080000                                     */
#define HRPWM_FLTINR1_FLT3F_Pos     (12U)
#define HRPWM_FLTINR1_FLT3F_Msk     (0xFUL << HRPWM_FLTINR1_FLT3F_Pos)      /*!< 0x0000F000                                     */
#define HRPWM_FLTINR1_FLT3F         HRPWM_FLTINR1_FLT3F_Msk                 /*!< Fault 3 filter                                 */
#define HRPWM_FLTINR1_FLT3F_0       (0x1UL << HRPWM_FLTINR1_FLT3F_Pos)      /*!< 0x00001000                                     */
#define HRPWM_FLTINR1_FLT3F_1       (0x2UL << HRPWM_FLTINR1_FLT3F_Pos)      /*!< 0x00002000                                     */
#define HRPWM_FLTINR1_FLT3F_2       (0x4UL << HRPWM_FLTINR1_FLT3F_Pos)      /*!< 0x00004000                                     */
#define HRPWM_FLTINR1_FLT3F_3       (0x8UL << HRPWM_FLTINR1_FLT3F_Pos)      /*!< 0x00008000                                     */
#define HRPWM_FLTINR1_FLT2F_Pos     (8U)
#define HRPWM_FLTINR1_FLT2F_Msk     (0xFUL << HRPWM_FLTINR1_FLT2F_Pos)      /*!< 0x00000F00                                     */
#define HRPWM_FLTINR1_FLT2F         HRPWM_FLTINR1_FLT2F_Msk                 /*!< Fault 2 filter                                 */
#define HRPWM_FLTINR1_FLT2F_0       (0x1UL << HRPWM_FLTINR1_FLT2F_Pos)      /*!< 0x00000100                                     */
#define HRPWM_FLTINR1_FLT2F_1       (0x2UL << HRPWM_FLTINR1_FLT2F_Pos)      /*!< 0x00000200                                     */
#define HRPWM_FLTINR1_FLT2F_2       (0x4UL << HRPWM_FLTINR1_FLT2F_Pos)      /*!< 0x00000400                                     */
#define HRPWM_FLTINR1_FLT2F_3       (0x8UL << HRPWM_FLTINR1_FLT2F_Pos)      /*!< 0x00000800                                     */
#define HRPWM_FLTINR1_FLT1F_Pos     (4U)
#define HRPWM_FLTINR1_FLT1F_Msk     (0xFUL << HRPWM_FLTINR1_FLT1F_Pos)      /*!< 0x000000F0                                     */
#define HRPWM_FLTINR1_FLT1F         HRPWM_FLTINR1_FLT1F_Msk                 /*!< Fault 1 filter                                 */
#define HRPWM_FLTINR1_FLT1F_0       (0x1UL << HRPWM_FLTINR1_FLT1F_Pos)      /*!< 0x00000010                                     */
#define HRPWM_FLTINR1_FLT1F_1       (0x2UL << HRPWM_FLTINR1_FLT1F_Pos)      /*!< 0x00000020                                     */
#define HRPWM_FLTINR1_FLT1F_2       (0x4UL << HRPWM_FLTINR1_FLT1F_Pos)      /*!< 0x00000040                                     */
#define HRPWM_FLTINR1_FLT1F_3       (0x8UL << HRPWM_FLTINR1_FLT1F_Pos)      /*!< 0x00000080                                     */
#define HRPWM_FLTINR1_FLT0F_Pos     (0U)
#define HRPWM_FLTINR1_FLT0F_Msk     (0xFUL << HRPWM_FLTINR1_FLT0F_Pos)      /*!< 0x0000000F                                     */
#define HRPWM_FLTINR1_FLT0F         HRPWM_FLTINR1_FLT0F_Msk                 /*!< Fault 0 filter                                 */
#define HRPWM_FLTINR1_FLT0F_0       (0x1UL << HRPWM_FLTINR1_FLT0F_Pos)      /*!< 0x00000001                                     */
#define HRPWM_FLTINR1_FLT0F_1       (0x2UL << HRPWM_FLTINR1_FLT0F_Pos)      /*!< 0x00000002                                     */
#define HRPWM_FLTINR1_FLT0F_2       (0x4UL << HRPWM_FLTINR1_FLT0F_Pos)      /*!< 0x00000004                                     */
#define HRPWM_FLTINR1_FLT0F_3       (0x8UL << HRPWM_FLTINR1_FLT0F_Pos)      /*!< 0x00000008                                     */

/**************  Bit definition for HRPWM_Common_FINTR2 register  *************/
#define HRPWM_FLTINR2_FLT5RSTM_Pos  (23U)
#define HRPWM_FLTINR2_FLT5RSTM_Msk  (0x1UL << HRPWM_FLTINR2_FLT5RSTM_Pos)   /*!< 0x00800000                                     */
#define HRPWM_FLTINR2_FLT5RSTM      HRPWM_FLTINR2_FLT5RSTM_Msk              /*!< Fault 5 Counter Reset Mode                     */
#define HRPWM_FLTINR2_FLT5CRES_Pos  (22U)
#define HRPWM_FLTINR2_FLT5CRES_Msk  (0x1UL << HRPWM_FLTINR2_FLT5CRES_Pos)   /*!< 0x00400000                                     */
#define HRPWM_FLTINR2_FLT5CRES      HRPWM_FLTINR2_FLT5CRES_Msk              /*!< Fault 5 Counter Reset                          */
#define HRPWM_FLTINR2_FLT5BLKS_Pos  (21U)
#define HRPWM_FLTINR2_FLT5BLKS_Msk  (0x1UL << HRPWM_FLTINR2_FLT5BLKS_Pos)   /*!< 0x00200000                                     */
#define HRPWM_FLTINR2_FLT5BLKS      HRPWM_FLTINR2_FLT5BLKS_Msk              /*!< Fault 5 Blanking Source                        */
#define HRPWM_FLTINR2_FLT5BLKE_Pos  (20U)
#define HRPWM_FLTINR2_FLT5BLKE_Msk  (0x1UL << HRPWM_FLTINR2_FLT5BLKE_Pos)   /*!< 0x00100000                                     */
#define HRPWM_FLTINR2_FLT5BLKE      HRPWM_FLTINR2_FLT5BLKE_Msk              /*!< Fault 5 Blanking Enable                        */
#define HRPWM_FLTINR2_FLT4RSTM_Pos  (19U)
#define HRPWM_FLTINR2_FLT4RSTM_Msk  (0x1UL << HRPWM_FLTINR2_FLT4RSTM_Pos)   /*!< 0x00080000                                     */
#define HRPWM_FLTINR2_FLT4RSTM      HRPWM_FLTINR2_FLT4RSTM_Msk              /*!< Fault 5 Counter Reset Mode                     */
#define HRPWM_FLTINR2_FLT4CRES_Pos  (18U)
#define HRPWM_FLTINR2_FLT4CRES_Msk  (0x1UL << HRPWM_FLTINR2_FLT4CRES_Pos)   /*!< 0x00040000                                     */
#define HRPWM_FLTINR2_FLT4CRES      HRPWM_FLTINR2_FLT4CRES_Msk              /*!< Fault 5 Counter Reset                          */
#define HRPWM_FLTINR2_FLT4BLKS_Pos  (17U)
#define HRPWM_FLTINR2_FLT4BLKS_Msk  (0x1UL << HRPWM_FLTINR2_FLT4BLKS_Pos)   /*!< 0x00020000                                     */
#define HRPWM_FLTINR2_FLT4BLKS      HRPWM_FLTINR2_FLT4BLKS_Msk              /*!< Fault 5 Blanking Source                        */
#define HRPWM_FLTINR2_FLT4BLKE_Pos  (16U)
#define HRPWM_FLTINR2_FLT4BLKE_Msk  (0x1UL << HRPWM_FLTINR2_FLT4BLKE_Pos)   /*!< 0x00010000                                     */
#define HRPWM_FLTINR2_FLT4BLKE      HRPWM_FLTINR2_FLT4BLKE_Msk              /*!< Fault 5 Blanking Enable                        */
#define HRPWM_FLTINR2_FLT3RSTM_Pos  (15U)
#define HRPWM_FLTINR2_FLT3RSTM_Msk  (0x1UL << HRPWM_FLTINR2_FLT3RSTM_Pos)   /*!< 0x00008000                                     */
#define HRPWM_FLTINR2_FLT3RSTM      HRPWM_FLTINR2_FLT3RSTM_Msk              /*!< Fault 4 Counter Reset Mode                     */
#define HRPWM_FLTINR2_FLT3CRES_Pos  (14U)
#define HRPWM_FLTINR2_FLT3CRES_Msk  (0x1UL << HRPWM_FLTINR2_FLT3CRES_Pos)   /*!< 0x00004000                                     */
#define HRPWM_FLTINR2_FLT3CRES      HRPWM_FLTINR2_FLT3CRES_Msk              /*!< Fault 4 Counter Reset                          */
#define HRPWM_FLTINR2_FLT3BLKS_Pos  (13U)
#define HRPWM_FLTINR2_FLT3BLKS_Msk  (0x1UL << HRPWM_FLTINR2_FLT3BLKS_Pos)   /*!< 0x00002000                                     */
#define HRPWM_FLTINR2_FLT3BLKS      HRPWM_FLTINR2_FLT3BLKS_Msk              /*!< Fault 4 Blanking Source                        */
#define HRPWM_FLTINR2_FLT3BLKE_Pos  (12U)
#define HRPWM_FLTINR2_FLT3BLKE_Msk  (0x1UL << HRPWM_FLTINR2_FLT3BLKE_Pos)   /*!< 0x00001000                                     */
#define HRPWM_FLTINR2_FLT3BLKE      HRPWM_FLTINR2_FLT3BLKE_Msk              /*!< Fault 4 Blanking Enable                        */
#define HRPWM_FLTINR2_FLT2RSTM_Pos  (11U)
#define HRPWM_FLTINR2_FLT2RSTM_Msk  (0x1UL << HRPWM_FLTINR2_FLT2RSTM_Pos)   /*!< 0x00000800                                     */
#define HRPWM_FLTINR2_FLT2RSTM      HRPWM_FLTINR2_FLT2RSTM_Msk              /*!< Fault 3 Counter Reset Mode                     */
#define HRPWM_FLTINR2_FLT2CRES_Pos  (10U)
#define HRPWM_FLTINR2_FLT2CRES_Msk  (0x1UL << HRPWM_FLTINR2_FLT2CRES_Pos)   /*!< 0x00000400                                     */
#define HRPWM_FLTINR2_FLT2CRES      HRPWM_FLTINR2_FLT2CRES_Msk              /*!< Fault 3 Counter Reset                          */
#define HRPWM_FLTINR2_FLT2BLKS_Pos  (9U)
#define HRPWM_FLTINR2_FLT2BLKS_Msk  (0x1UL << HRPWM_FLTINR2_FLT2BLKS_Pos)   /*!< 0x00000200                                     */
#define HRPWM_FLTINR2_FLT2BLKS      HRPWM_FLTINR2_FLT2BLKS_Msk              /*!< Fault 3 Blanking Source                        */
#define HRPWM_FLTINR2_FLT2BLKE_Pos  (8U)
#define HRPWM_FLTINR2_FLT2BLKE_Msk  (0x1UL << HRPWM_FLTINR2_FLT2BLKE_Pos)   /*!< 0x00000100                                     */
#define HRPWM_FLTINR2_FLT2BLKE      HRPWM_FLTINR2_FLT2BLKE_Msk              /*!< Fault 3 Blanking Enable                        */
#define HRPWM_FLTINR2_FLT1RSTM_Pos  (7U)
#define HRPWM_FLTINR2_FLT1RSTM_Msk  (0x1UL << HRPWM_FLTINR2_FLT1RSTM_Pos)   /*!< 0x00000080                                     */
#define HRPWM_FLTINR2_FLT1RSTM      HRPWM_FLTINR2_FLT1RSTM_Msk              /*!< Fault 2 Counter Reset Mode                     */
#define HRPWM_FLTINR2_FLT1CRES_Pos  (6U)
#define HRPWM_FLTINR2_FLT1CRES_Msk  (0x1UL << HRPWM_FLTINR2_FLT1CRES_Pos)   /*!< 0x00000040                                     */
#define HRPWM_FLTINR2_FLT1CRES      HRPWM_FLTINR2_FLT1CRES_Msk              /*!< Fault 2 Counter Reset                          */
#define HRPWM_FLTINR2_FLT1BLKS_Pos  (5U)
#define HRPWM_FLTINR2_FLT1BLKS_Msk  (0x1UL << HRPWM_FLTINR2_FLT1BLKS_Pos)   /*!< 0x00000020                                     */
#define HRPWM_FLTINR2_FLT1BLKS      HRPWM_FLTINR2_FLT1BLKS_Msk              /*!< Fault 2 Blanking Source                        */
#define HRPWM_FLTINR2_FLT1BLKE_Pos  (4U)
#define HRPWM_FLTINR2_FLT1BLKE_Msk  (0x1UL << HRPWM_FLTINR2_FLT1BLKE_Pos)   /*!< 0x00000010                                     */
#define HRPWM_FLTINR2_FLT1BLKE      HRPWM_FLTINR2_FLT1BLKE_Msk              /*!< Fault 2 Blanking Enable                        */
#define HRPWM_FLTINR2_FLT0RSTM_Pos  (3U)
#define HRPWM_FLTINR2_FLT0RSTM_Msk  (0x1UL << HRPWM_FLTINR2_FLT0RSTM_Pos)   /*!< 0x00000008                                     */
#define HRPWM_FLTINR2_FLT0RSTM      HRPWM_FLTINR2_FLT0RSTM_Msk              /*!< Fault 1 Counter Reset Mode                     */
#define HRPWM_FLTINR2_FLT0CRES_Pos  (2U)
#define HRPWM_FLTINR2_FLT0CRES_Msk  (0x1UL << HRPWM_FLTINR2_FLT0CRES_Pos)   /*!< 0x00000004                                     */
#define HRPWM_FLTINR2_FLT0CRES      HRPWM_FLTINR2_FLT0CRES_Msk              /*!< Fault 1 Counter Reset                          */
#define HRPWM_FLTINR2_FLT0BLKS_Pos  (1U)
#define HRPWM_FLTINR2_FLT0BLKS_Msk  (0x1UL << HRPWM_FLTINR2_FLT0BLKS_Pos)   /*!< 0x00000002                                     */
#define HRPWM_FLTINR2_FLT0BLKS      HRPWM_FLTINR2_FLT0BLKS_Msk              /*!< Fault 1 Blanking Source                        */
#define HRPWM_FLTINR2_FLT0BLKE_Pos  (0U)
#define HRPWM_FLTINR2_FLT0BLKE_Msk  (0x1UL << HRPWM_FLTINR2_FLT0BLKE_Pos)   /*!< 0x00000001                                     */
#define HRPWM_FLTINR2_FLT0BLKE      HRPWM_FLTINR2_FLT0BLKE_Msk              /*!< Fault 1 Blanking Enable                        */

/**************  Bit definition for HRPWM_Common_FINTR3 register  *************/
#define HRPWM_FLTINR3_FLT5CNT_Pos   (20U)
#define HRPWM_FLTINR3_FLT5CNT_Msk   (0xFUL << HRPWM_FLTINR3_FLT5CNT_Pos)    /*!< 0x00F00000                                     */
#define HRPWM_FLTINR3_FLT5CNT       HRPWM_FLTINR3_FLT5CNT_Msk               /*!< Fault 5 Valid Counter N                        */
#define HRPWM_FLTINR3_FLT5CNT_0     (0x1UL << HRPWM_FLTINR3_FLT5CNT_Pos)    /*!< 0x00100000                                     */
#define HRPWM_FLTINR3_FLT5CNT_1     (0x2UL << HRPWM_FLTINR3_FLT5CNT_Pos)    /*!< 0x00200000                                     */
#define HRPWM_FLTINR3_FLT5CNT_2     (0x4UL << HRPWM_FLTINR3_FLT5CNT_Pos)    /*!< 0x00400000                                     */
#define HRPWM_FLTINR3_FLT5CNT_3     (0x8UL << HRPWM_FLTINR3_FLT5CNT_Pos)    /*!< 0x00800000                                     */
#define HRPWM_FLTINR3_FLT4CNT_Pos   (16U)
#define HRPWM_FLTINR3_FLT4CNT_Msk   (0xFUL << HRPWM_FLTINR3_FLT4CNT_Pos)    /*!< 0x000F0000                                     */
#define HRPWM_FLTINR3_FLT4CNT       HRPWM_FLTINR3_FLT4CNT_Msk               /*!< Fault 4 Valid Counter N                        */
#define HRPWM_FLTINR3_FLT4CNT_0     (0x1UL << HRPWM_FLTINR3_FLT4CNT_Pos)    /*!< 0x00010000                                     */
#define HRPWM_FLTINR3_FLT4CNT_1     (0x2UL << HRPWM_FLTINR3_FLT4CNT_Pos)    /*!< 0x00020000                                     */
#define HRPWM_FLTINR3_FLT4CNT_2     (0x4UL << HRPWM_FLTINR3_FLT4CNT_Pos)    /*!< 0x00040000                                     */
#define HRPWM_FLTINR3_FLT4CNT_3     (0x8UL << HRPWM_FLTINR3_FLT4CNT_Pos)    /*!< 0x00080000                                     */
#define HRPWM_FLTINR3_FLT3CNT_Pos   (12U)
#define HRPWM_FLTINR3_FLT3CNT_Msk   (0xFUL << HRPWM_FLTINR3_FLT3CNT_Pos)    /*!< 0x0000F000                                     */
#define HRPWM_FLTINR3_FLT3CNT       HRPWM_FLTINR3_FLT3CNT_Msk               /*!< Fault 3 Valid Counter N                        */
#define HRPWM_FLTINR3_FLT3CNT_0     (0x1UL << HRPWM_FLTINR3_FLT3CNT_Pos)    /*!< 0x00001000                                     */
#define HRPWM_FLTINR3_FLT3CNT_1     (0x2UL << HRPWM_FLTINR3_FLT3CNT_Pos)    /*!< 0x00002000                                     */
#define HRPWM_FLTINR3_FLT3CNT_2     (0x4UL << HRPWM_FLTINR3_FLT3CNT_Pos)    /*!< 0x00004000                                     */
#define HRPWM_FLTINR3_FLT3CNT_3     (0x8UL << HRPWM_FLTINR3_FLT3CNT_Pos)    /*!< 0x00008000                                     */
#define HRPWM_FLTINR3_FLT2CNT_Pos   (8U)
#define HRPWM_FLTINR3_FLT2CNT_Msk   (0xFUL << HRPWM_FLTINR3_FLT2CNT_Pos)    /*!< 0x00000F00                                     */
#define HRPWM_FLTINR3_FLT2CNT       HRPWM_FLTINR3_FLT2CNT_Msk               /*!< Fault 2 Valid Counter N                        */
#define HRPWM_FLTINR3_FLT2CNT_0     (0x1UL << HRPWM_FLTINR3_FLT2CNT_Pos)    /*!< 0x00000100                                     */
#define HRPWM_FLTINR3_FLT2CNT_1     (0x2UL << HRPWM_FLTINR3_FLT2CNT_Pos)    /*!< 0x00000200                                     */
#define HRPWM_FLTINR3_FLT2CNT_2     (0x4UL << HRPWM_FLTINR3_FLT2CNT_Pos)    /*!< 0x00000400                                     */
#define HRPWM_FLTINR3_FLT2CNT_3     (0x8UL << HRPWM_FLTINR3_FLT2CNT_Pos)    /*!< 0x00000800                                     */
#define HRPWM_FLTINR3_FLT1CNT_Pos   (4U)
#define HRPWM_FLTINR3_FLT1CNT_Msk   (0xFUL << HRPWM_FLTINR3_FLT1CNT_Pos)    /*!< 0x000000F0                                     */
#define HRPWM_FLTINR3_FLT1CNT       HRPWM_FLTINR3_FLT1CNT_Msk               /*!< Fault 1 Valid Counter N                        */
#define HRPWM_FLTINR3_FLT1CNT_0     (0x1UL << HRPWM_FLTINR3_FLT1CNT_Pos)    /*!< 0x00000010                                     */
#define HRPWM_FLTINR3_FLT1CNT_1     (0x2UL << HRPWM_FLTINR3_FLT1CNT_Pos)    /*!< 0x00000020                                     */
#define HRPWM_FLTINR3_FLT1CNT_2     (0x4UL << HRPWM_FLTINR3_FLT1CNT_Pos)    /*!< 0x00000040                                     */
#define HRPWM_FLTINR3_FLT1CNT_3     (0x8UL << HRPWM_FLTINR3_FLT1CNT_Pos)    /*!< 0x00000080                                     */
#define HRPWM_FLTINR3_FLT0CNT_Pos   (0U)
#define HRPWM_FLTINR3_FLT0CNT_Msk   (0xFUL << HRPWM_FLTINR3_FLT0CNT_Pos)    /*!< 0x000000F                                      */
#define HRPWM_FLTINR3_FLT0CNT       HRPWM_FLTINR3_FLT0CNT_Msk               /*!< Fault 0 Valid Counter N                        */
#define HRPWM_FLTINR3_FLT0CNT_0     (0x1UL << HRPWM_FLTINR3_FLT0CNT_Pos)    /*!< 0x00000001                                     */
#define HRPWM_FLTINR3_FLT0CNT_1     (0x2UL << HRPWM_FLTINR3_FLT0CNT_Pos)    /*!< 0x00000002                                     */
#define HRPWM_FLTINR3_FLT0CNT_2     (0x4UL << HRPWM_FLTINR3_FLT0CNT_Pos)    /*!< 0x00000004                                     */
#define HRPWM_FLTINR3_FLT0CNT_3     (0x8UL << HRPWM_FLTINR3_FLT0CNT_Pos)    /*!< 0x00000008                                     */


/******************************************************************************/
/*                                                                            */
/*                             USB Controler                                  */
/*                                                                            */
/******************************************************************************/

/*****************  Bit definition for USB FADDR register  ****************/
#define USB_FUNC_ADDR_Pos           (0UL)
#define USB_FUNC_ADDR_Msk           (0x7FUL << USB_FUNC_ADDR_Pos)
#define USB_FUNC_ADDR               USB_FUNC_ADDR_Msk

/******************  Bit definition for USB POWER register  ****************/
#define USB_ISO_UPDATE_Pos          (7UL)
#define USB_ISO_UPDATE_Msk          (0x1UL << USB_ISO_UPDATE_Pos)
#define USB_ISO_UPDATE              USB_ISO_UPDATE_Msk
#define USB_SOFT_CONN_EN_Pos        (6UL)
#define USB_SOFT_CONN_EN_Msk        (0x1UL << USB_SOFT_CONN_EN_Pos)
#define USB_SOFT_CONN_EN            USB_SOFT_CONN_EN_Msk
#define USB_HS_EN_Pos               (5UL)
#define USB_HS_EN_Msk               (0x1UL << USB_HS_EN_Pos)
#define USB_HS_EN                   USB_HS_EN_Msk
#define USB_HS_JUDGE_Pos            (4UL)
#define USB_HS_JUDGE_Msk            (0x1UL << USB_HS_JUDGE_Pos)
#define USB_HS_JUDGE                USB_HS_JUDGE_Msk
#define USB_RST_Pos                 (3UL)
#define USB_RST_Msk                 (0x1UL << USB_RST_Pos)
#define USB_RST                     USB_RST_Msk
#define USB_RESUME_Pos              (2UL)
#define USB_RESUME_Msk              (0x1UL << USB_RESUME_Pos)
#define USB_RESUME                  USB_RESUME_Msk
#define USB_SUSPEND_Pos             (1UL)
#define USB_SUSPEND_Msk             (0x1UL << USB_SUSPEND_Pos)
#define USB_SUSPEND                 USB_SUSPEND_Msk
#define USB_SUSPEND_DM_EN_Pos       (0UL)
#define USB_SUSPEND_DM_EN_Msk       (0x1UL << USB_SUSPEND_DM_EN_Pos)
#define USB_SUSPEND_DM_EN           USB_SUSPEND_DM_EN_Msk

/*****************  Bit definition for USB INTRTX register  ***************/
#define USB_TX_EP2_INT_STA_Pos      (2UL)
#define USB_TX_EP2_INT_STA_Msk      (0x1UL << USB_TX_EP2_INT_STA_Pos)
#define USB_TX_EP2_INT_STA          USB_TX_EP2_INT_STA_Msk
#define USB_TX_EP1_INT_STA_Pos      (1UL)
#define USB_TX_EP1_INT_STA_Msk      (0x1UL << USB_TX_EP1_INT_STA_Pos)
#define USB_TX_EP1_INT_STA          USB_TX_EP1_INT_STA_Msk
#define USB_EP0_INT_STA_Pos         (0UL)
#define USB_EP0_INT_STA_Msk         (0x1UL << USB_EP0_INT_STA_Pos)
#define USB_EP0_INT_STA             USB_EP0_INT_STA_Msk

/*****************  Bit definition for USB INTRRX register  ***************/
#define USB_RX_EP2_INT_STA_Pos      (2UL)
#define USB_RX_EP2_INT_STA_Msk      (0x1UL << USB_RX_EP2_INT_STA_Pos)
#define USB_RX_EP2_INT_STA          USB_RX_EP2_INT_STA_Msk
#define USB_RX_EP1_INT_STA_Pos      (1UL)
#define USB_RX_EP1_INT_STA_Msk      (0x1UL << USB_RX_EP1_INT_STA_Pos)
#define USB_RX_EP1_INT_STA          USB_RX_EP1_INT_STA_Msk

/*****************  Bit definition for USB INTRTXE register  ****************/
#define USB_TX_EP2_INT_EN_Pos       (2UL)
#define USB_TX_EP2_INT_EN_Msk       (0x1UL << USB_TX_EP2_INT_EN_Pos)
#define USB_TX_EP2_INT_EN           USB_TX_EP2_INT_EN_Msk
#define USB_TX_EP1_INT_EN_Pos       (1UL)
#define USB_TX_EP1_INT_EN_Msk       (0x1UL << USB_TX_EP1_INT_EN_Pos)
#define USB_TX_EP1_INT_EN           USB_TX_EP1_INT_EN_Msk
#define USB_EP0_INT_EN_Pos          (0UL)
#define USB_EP0_INT_EN_Msk          (0x1UL << USB_EP0_INT_EN_Pos)
#define USB_EP0_INT_EN              USB_EP0_INT_EN_Msk

/*****************  Bit definition for USB INTRRXE register  ****************/
#define USB_RX_EP2_INT_EN_Pos       (2UL)
#define USB_RX_EP2_INT_EN_Msk       (0x1UL << USB_RX_EP2_INT_EN_Pos)
#define USB_RX_EP2_INT_EN           USB_RX_EP2_INT_EN_Msk
#define USB_RX_EP1_INT_EN_Pos       (1UL)
#define USB_RX_EP1_INT_EN_Msk       (0x1UL << USB_RX_EP1_INT_EN_Pos)
#define USB_RX_EP1_INT_EN           USB_RX_EP1_INT_EN_Msk

/******************  Bit definition for USB INTRUSB register  *****************/
#define USB_SESS_END_INT_STA_Pos    (5UL)
#define USB_SESS_END_INT_STA_Msk    (0x1UL << USB_SESS_END_INT_STA_Pos)
#define USB_SESS_END_INT_STA        USB_SESS_END_INT_STA_Msk
#define USB_SOF_INT_STA_Pos         (3UL)
#define USB_SOF_INT_STA_Msk         (0x1UL << USB_SOF_INT_STA_Pos)
#define USB_SOF_INT_STA             USB_SOF_INT_STA_Msk
#define USB_RST_INT_STA_Pos         (2UL)
#define USB_RST_INT_STA_Msk         (0x1UL << USB_RST_INT_STA_Pos)
#define USB_RST_INT_STA             USB_RST_INT_STA_Msk
#define USB_RESUME_INT_STA_Pos      (1UL)
#define USB_RESUME_INT_STA_Msk      (0x1UL << USB_RESUME_INT_STA_Pos)
#define USB_RESUME_INT_STA          USB_RESUME_INT_STA_Msk
#define USB_SUSPEND_INT_STA_Pos     (0UL)
#define USB_SUSPEND_INT_STA_Msk     (0x1UL << USB_SUSPEND_INT_STA_Pos)
#define USB_SUSPEND_INT_STA         USB_SUSPEND_INT_STA_Msk

/*******************  Bit definition for USB INTRUSBE register  *****************/
/* USB_INT_EN: 0x0B */
#define USB_SESS_END_INT_EN_Pos     (5UL)
#define USB_SESS_END_INT_EN_Msk     (0x1UL << USB_SESS_END_INT_EN_Pos)
#define USB_SESS_END_INT_EN         USB_SESS_END_INT_EN_Msk
#define USB_SOF_INT_EN_Pos          (3UL)
#define USB_SOF_INT_EN_Msk          (0x1UL << USB_SOF_INT_EN_Pos)
#define USB_SOF_INT_EN              USB_SOF_INT_EN_Msk
#define USB_RST_INT_EN_Pos          (2UL)
#define USB_RST_INT_EN_Msk          (0x1UL << USB_RST_INT_EN_Pos)
#define USB_RST_INT_EN              USB_RST_INT_EN_Msk
#define USB_RESUME_INT_EN_Pos       (1UL)
#define USB_RESUME_INT_EN_Msk       (0x1UL << USB_RESUME_INT_EN_Pos)
#define USB_RESUME_INT_EN           USB_RESUME_INT_EN_Msk
#define USB_SUSPEND_INT_EN_Pos      (0UL)
#define USB_SUSPEND_INT_EN_Msk      (0x1UL << USB_SUSPEND_INT_EN_Pos)
#define USB_SUSPEND_INT_EN          USB_SUSPEND_INT_EN_Msk

#define USB_CTRL_INT_ALL_Msk        (USB_SESS_END_INT_EN_Msk | USB_SOF_INT_EN_Msk | USB_RST_INT_EN_Msk |\
                                    USB_RESUME_INT_EN_Msk | USB_SUSPEND_INT_EN_Msk)

/*****************  Bit definition for USB FRAME register  ****************/
#define USB_FRAME_NUM_Pos           (0UL)
#define USB_FRAME_NUM_Msk           (0x7FFUL << USB_FRAME_NUM_Pos)
#define USB_FRAME_NUM               USB_FRAME_NUM_Msk

/******************  Bit definition for USB INDEX register  ****************/
#define USB_EP_INDEX_Pos            (0UL)
#define USB_EP_INDEX_Msk            (0xFUL << USB_EP_INDEX_Pos)
#define USB_EP_INDEX                USB_EP_INDEX_Msk

/******************  Bit definition for USB TXMAXP register  *****************/
#define USB_EPX_TX_MAX_PAYLD_Pos    (0UL)
#define USB_EPX_TX_MAX_PAYLD_Msk    (0xFFFFUL << USB_EPX_TX_MAX_PAYLD_Pos)
#define USB_EPX_TX_MAX_PAYLD        USB_EPX_TX_MAX_PAYLD_Msk

/******************  Bit definition for USB TX_CSR0 register  *****************/
#define USB_EP0_FLUSH_FIFO_Pos      (8UL)
#define USB_EP0_FLUSH_FIFO_Msk      (0x1UL << USB_EP0_FLUSH_FIFO_Pos)
#define USB_EP0_FLUSH_FIFO          USB_EP0_FLUSH_FIFO_Msk
#define USB_EP0_CLR_SETUP_END_Pos   (7UL)
#define USB_EP0_CLR_SETUP_END_Msk   (0x1UL << USB_EP0_CLR_SETUP_END_Pos)
#define USB_EP0_CLR_SETUP_END       USB_EP0_CLR_SETUP_END_Msk
#define USB_EP0_CLR_RX_PKT_RDY_Pos  (6UL)
#define USB_EP0_CLR_RX_PKT_RDY_Msk  (0x1UL << USB_EP0_CLR_RX_PKT_RDY_Pos)
#define USB_EP0_CLR_RX_PKT_RDY      USB_EP0_CLR_RX_PKT_RDY_Msk
#define USB_EP0_SEND_STALL_Pos      (5UL)
#define USB_EP0_SEND_STALL_Msk      (0x1UL << USB_EP0_SEND_STALL_Pos)
#define USB_EP0_SEND_STALL          USB_EP0_SEND_STALL_Msk
#define USB_EP0_SETUP_END_Pos       (4UL)
#define USB_EP0_SETUP_END_Msk       (0x1UL << USB_EP0_SETUP_END_Pos)
#define USB_EP0_SETUP_END           USB_EP0_SETUP_END_Msk
#define USB_EP0_DATA_END_Pos        (3UL)
#define USB_EP0_DATA_END_Msk        (0x1UL << USB_EP0_DATA_END_Pos)
#define USB_EP0_DATA_END            USB_EP0_DATA_END_Msk
#define USB_EP0_SENT_STALL_Pos      (2UL)
#define USB_EP0_SENT_STALL_Msk      (0x1UL << USB_EP0_SENT_STALL_Pos)
#define USB_EP0_SENT_STALL          USB_EP0_SENT_STALL_Msk
#define USB_EP0_TX_PKT_RDY_Pos      (1UL)
#define USB_EP0_TX_PKT_RDY_Msk      (0x1UL << USB_EP0_TX_PKT_RDY_Pos)
#define USB_EP0_TX_PKT_RDY          USB_EP0_TX_PKT_RDY_Msk
#define USB_EP0_RX_PKT_RDY_Pos      (0UL)
#define USB_EP0_RX_PKT_RDY_Msk      (0x1UL << USB_EP0_RX_PKT_RDY_Pos)
#define USB_EP0_RX_PKT_RDY          USB_EP0_RX_PKT_RDY_Msk

/******************  Bit definition for USB TX_CSRX register  *****************/
#define USB_EPX_TX_AUTO_SET_Pos     (15UL)
#define USB_EPX_TX_AUTO_SET_Msk     (0x1UL << USB_EPX_TX_AUTO_SET_Pos)
#define USB_EPX_TX_AUTO_SET         USB_EPX_TX_AUTO_SET_Msk
#define USB_EPX_TX_ISO_EN_Pos       (14UL)
#define USB_EPX_TX_ISO_EN_Msk       (0x1UL << USB_EPX_TX_ISO_EN_Pos)
#define USB_EPX_TX_ISO_EN           USB_EPX_TX_ISO_EN_Msk
#define USB_EPX_DIR_MODE_Pos        (13UL)
#define USB_EPX_DIR_MODE_Msk        (0x1UL << USB_EPX_DIR_MODE_Pos)
#define USB_EPX_DIR_MODE            USB_EPX_DIR_MODE_Msk
#define USB_EPX_TX_DMA_REQ_EN_Pos   (12UL)
#define USB_EPX_TX_DMA_REQ_EN_Msk   (0x1UL << USB_EPX_TX_DMA_REQ_EN_Pos)
#define USB_EPX_TX_DMA_REQ_EN       USB_EPX_TX_DMA_REQ_EN_Msk
#define USB_EPX_TX_FRC_DATA_TOG_Pos (11UL)
#define USB_EPX_TX_FRC_DATA_TOG_Msk (0x1UL << USB_EPX_TX_FRC_DATA_TOG_Pos)
#define USB_EPX_TX_FRC_DATA_TOG     USB_EPX_TX_FRC_DATA_TOG_Msk
#define USB_EPX_TX_DMA_REQ_MODE_Pos (10UL)
#define USB_EPX_TX_DMA_REQ_MODE_Msk (0x1UL << USB_EPX_TX_DMA_REQ_MODE_Pos)
#define USB_EPX_TX_DMA_REQ_MODE     USB_EPX_TX_DMA_REQ_MODE_Msk
#define USB_EPX_TX_ISO_INCOMP_Pos   (7UL)
#define USB_EPX_TX_ISO_INCOMP_Msk   (0x1UL << USB_EPX_TX_ISO_INCOMP_Pos)
#define USB_EPX_TX_ISO_INCOMP       USB_EPX_TX_ISO_INCOMP_Msk
#define USB_EPX_TX_CLR_DATA_TOG_Pos (6UL)
#define USB_EPX_TX_CLR_DATA_TOG_Msk (0x1UL << USB_EPX_TX_CLR_DATA_TOG_Pos)
#define USB_EPX_TX_CLR_DATA_TOG     USB_EPX_TX_CLR_DATA_TOG_Msk
#define USB_EPX_TX_SENT_STALL_Pos   (5UL)
#define USB_EPX_TX_SENT_STALL_Msk   (0x1UL << USB_EPX_TX_SENT_STALL_Pos)
#define USB_EPX_TX_SENT_STALL       USB_EPX_TX_SENT_STALL_Msk
#define USB_EPX_TX_SEND_STALL_Pos   (4UL)
#define USB_EPX_TX_SEND_STALL_Msk   (0x1UL << USB_EPX_TX_SEND_STALL_Pos)
#define USB_EPX_TX_SEND_STALL       USB_EPX_TX_SEND_STALL_Msk
#define USB_EPX_TX_FLUSH_FIFO_Pos   (3UL)
#define USB_EPX_TX_FLUSH_FIFO_Msk   (0x1UL << USB_EPX_TX_FLUSH_FIFO_Pos)
#define USB_EPX_TX_FLUSH_FIFO       USB_EPX_TX_FLUSH_FIFO_Msk
#define USB_EPX_TX_UNDER_RUN_Pos    (2UL)
#define USB_EPX_TX_UNDER_RUN_Msk    (0x1UL << USB_EPX_TX_UNDER_RUN_Pos)
#define USB_EPX_TX_UNDER_RUN        USB_EPX_TX_UNDER_RUN_Msk
#define USB_EPX_TX_FIFO_NOT_EPY_Pos (1UL)
#define USB_EPX_TX_FIFO_NOT_EPY_Msk (0x1UL << USB_EPX_TX_FIFO_NOT_EPY_Pos)
#define USB_EPX_TX_FIFO_NOT_EPY     USB_EPX_TX_FIFO_NOT_EPY_Msk
#define USB_EPX_TX_PKT_RDY_Pos      (0UL)
#define USB_EPX_TX_PKT_RDY_Msk      (0x1UL << USB_EPX_TX_PKT_RDY_Pos)
#define USB_EPX_TX_PKT_RDY          USB_EPX_TX_PKT_RDY_Msk

/******************  Bit definition for USB RXMAXP register  *****************/
/* USB_RX_MAXP: 0x14 */
#define USB_EPX_RX_MAX_PAYLD_Pos    (0UL)
#define USB_EPX_RX_MAX_PAYLD_Msk    (0xFFFFUL << USB_EPX_RX_MAX_PAYLD_Pos)
#define USB_EPX_RX_MAX_PAYLD        USB_EPX_RX_MAX_PAYLD_Msk

/******************  Bit definition for USB RXCSRN register  *****************/
#define USB_EPX_RX_AUTO_CLR_Pos     (15UL)
#define USB_EPX_RX_AUTO_CLR_Msk     (0x1UL << USB_EPX_RX_AUTO_CLR_Pos)
#define USB_EPX_RX_AUTO_CLR         USB_EPX_RX_AUTO_CLR_Msk
#define USB_EPX_RX_ISO_EN_Pos       (14UL)
#define USB_EPX_RX_ISO_EN_Msk       (0x1UL << USB_EPX_RX_ISO_EN_Pos)
#define USB_EPX_RX_ISO_EN           USB_EPX_RX_ISO_EN_Msk
#define USB_EPX_RX_DMQ_REQ_EN_Pos   (13UL)
#define USB_EPX_RX_DMQ_REQ_EN_Msk   (0x1UL << USB_EPX_RX_DMQ_REQ_EN_Pos)
#define USB_EPX_RX_DMQ_REQ_EN       USB_EPX_RX_DMQ_REQ_EN_Msk
#define USB_EPX_RX_ISO_PID_ERR_Pos  (12UL)
#define USB_EPX_RX_ISO_PID_ERR_Msk  (0x1UL << USB_EPX_RX_ISO_PID_ERR_Pos)
#define USB_EPX_RX_ISO_PID_ERR      USB_EPX_RX_ISO_PID_ERR_Msk
#define USB_EPX_RX_DMA_REQ_MODE_Pos (11UL)
#define USB_EPX_RX_DMA_REQ_MODE_Msk (0x1UL << USB_EPX_RX_DMA_REQ_MODE_Pos)
#define USB_EPX_RX_DMA_REQ_MODE     USB_EPX_RX_DMA_REQ_MODE_Msk
#define USB_EPX_RX_ISO_INCOMP_Pos   (8UL)
#define USB_EPX_RX_ISO_INCOMP_Msk   (0x1UL << USB_EPX_RX_ISO_INCOMP_Pos)
#define USB_EPX_RX_ISO_INCOMP       USB_EPX_RX_ISO_INCOMP_Msk
#define USB_EPX_RX_CLR_DATA_TOG_Pos (7UL)
#define USB_EPX_RX_CLR_DATA_TOG_Msk (0x1UL << USB_EPX_RX_CLR_DATA_TOG_Pos)
#define USB_EPX_RX_CLR_DATA_TOG     USB_EPX_RX_CLR_DATA_TOG_Msk
#define USB_EPX_RX_SENT_STALL_Pos   (6UL)
#define USB_EPX_RX_SENT_STALL_Msk   (0x1UL << USB_EPX_RX_SENT_STALL_Pos)
#define USB_EPX_RX_SENT_STALL       USB_EPX_RX_SENT_STALL_Msk
#define USB_EPX_RX_SEND_STALL_Pos   (5UL)
#define USB_EPX_RX_SEND_STALL_Msk   (0x1UL << USB_EPX_RX_SEND_STALL_Pos)
#define USB_EPX_RX_SEND_STALL       USB_EPX_RX_SEND_STALL_Msk
#define USB_EPX_RX_FLUSH_FIFO_Pos   (4UL)
#define USB_EPX_RX_FLUSH_FIFO_Msk   (0x1UL << USB_EPX_RX_FLUSH_FIFO_Pos)
#define USB_EPX_RX_FLUSH_FIFO       USB_EPX_RX_FLUSH_FIFO_Msk
#define USB_EPX_RX_ISO_DATA_ERR_Pos (3UL)
#define USB_EPX_RX_ISO_DATA_ERR_Msk (0x1UL << USB_EPX_RX_ISO_DATA_ERR_Pos)
#define USB_EPX_RX_ISO_DATA_ERR     USB_EPX_RX_ISO_DATA_ERR_Msk
#define USB_EPX_RX_OVER_RUN_Pos     (2UL)
#define USB_EPX_RX_OVER_RUN_Msk     (0x1UL << USB_EPX_RX_OVER_RUN_Pos)
#define USB_EPX_RX_OVER_RUN         USB_EPX_RX_OVER_RUN_Msk
#define USB_EPX_RX_FIFO_FULL_Pos    (1UL)
#define USB_EPX_RX_FIFO_FULL_Msk    (0x1UL << USB_EPX_RX_FIFO_FULL_Pos)
#define USB_EPX_RX_FIFO_FULL        USB_EPX_RX_FIFO_FULL_Msk
#define USB_EPX_RX_PKT_RDY_Pos      (0UL)
#define USB_EPX_RX_PKT_RDY_Msk      (0x1UL << USB_EPX_RX_PKT_RDY_Pos)
#define USB_EPX_RX_PKT_RDY          USB_EPX_RX_PKT_RDY_Msk

/*******************  Bit definition for USB RXCOUNT register  *****************/
#define USB_RX_CNT_Pos              (0UL)
#define USB_RX_CNT_Msk              (0x3FFFUL << USB_RX_CNT_Pos)
#define USB_RX_CNT                  USB_RX_CNT_Msk

/*****************  Bit definition for USB FIFOSIZE register  ****************/
#define USB_RX_FIFO_SIZE_Pos        (11UL)
#define USB_RX_FIFO_SIZE_Msk        (0x1FUL << USB_RX_FIFO_SIZE_Pos)
#define USB_RX_FIFO_SIZE            USB_RX_FIFO_SIZE_Msk

#define USB_TX_FIFO_SIZE_Pos        (0UL)
#define USB_TX_FIFO_SIZE_Msk        (0x7FFUL << USB_TX_FIFO_SIZE_Pos)
#define USB_TX_FIFO_SIZE            USB_TX_FIFO_SIZE_Msk

/****************  Bit definition for USB DMA_INTR register  ***************/
#define USB_DMA2_INT_STA_Pos        (1UL)
#define USB_DMA2_INT_STA_Msk        (0x1UL << USB_DMA2_INT_STA_Pos)
#define USB_DMA2_INT_STA            USB_DMA2_INT_STA_Msk
#define USB_DMA1_INT_STA_Pos        (0UL)
#define USB_DMA1_INT_STA_Msk        (0x1UL << USB_DMA1_INT_STA_Pos)
#define USB_DMA1_INT_STA            USB_DMA1_INT_STA_Msk

/****************  Bit definition for USB DMA_CTRL 1/2 register  **************/
#define USB_DMA_BST_MODE_Pos        (9UL)
#define USB_DMA_BST_MODE_Msk        (0x3UL << USB_DMA_BST_MODE_Pos)
#define USB_DMA_BST_MODE            USB_DMA_BST_MODE_Msk
#define USB_DMA_ERR_Pos             (8UL)
#define USB_DMA_ERR_Msk             (0x1UL << USB_DMA_ERR_Pos)
#define USB_DMA_ERR                 USB_DMA_ERR_Msk
#define USB_DMA_EP_NUM_Pos          (4UL)
#define USB_DMA_EP_NUM_Msk          (0xFUL << USB_DMA_EP_NUM_Pos)
#define USB_DMA_EP_NUM              USB_DMA_EP_NUM_Msk
#define USB_DMA_INT_EN_Pos          (3UL)
#define USB_DMA_INT_EN_Msk          (0x1UL << USB_DMA_INT_EN_Pos)
#define USB_DMA_INT_EN              USB_DMA_INT_EN_Msk
#define USB_DMA_TRANS_MODE_Pos      (2UL)
#define USB_DMA_TRANS_MODE_Msk      (0x1UL << USB_DMA_TRANS_MODE_Pos)
#define USB_DMA_TRANS_MODE          USB_DMA_TRANS_MODE_Msk
#define USB_DMA_DIR_Pos             (1UL)
#define USB_DMA_DIR_Msk             (0x1UL << USB_DMA_DIR_Pos)
#define USB_DMA_DIR                 USB_DMA_DIR_Msk
#define USB_DMA_EN_Pos              (0UL)
#define USB_DMA_EN_Msk              (0x1UL << USB_DMA_EN_Pos)
#define USB_DMA_EN                  USB_DMA_EN_Msk

/****************  Bit definition for USB RX_DPBUF_DIS register  **************/
#define USB_RX_EP2_DPKTBUF_DIS_Pos  (2UL)
#define USB_RX_EP2_DPKTBUF_DIS_Msk  (0x1UL << USB_RX_EP2_DPKTBUF_DIS_Pos)
#define USB_RX_EP2_DPKTBUF_DIS      USB_RX_EP2_DPKTBUF_DIS_Msk
#define USB_RX_EP1_DPKTBUF_DIS_Pos  (1UL)
#define USB_RX_EP1_DPKTBUF_DIS_Msk  (0x1UL << USB_RX_EP1_DPKTBUF_DIS_Pos)
#define USB_RX_EP1_DPKTBUF_DIS      USB_RX_EP1_DPKTBUF_DIS_Msk

/****************  Bit definition for USB TX_DPBUF_DIS register  **************/
#define USB_TX_EP2_DPKTBUF_DIS_Pos  (2UL)
#define USB_TX_EP2_DPKTBUF_DIS_Msk  (0x1UL << USB_TX_EP2_DPKTBUF_DIS_Pos)
#define USB_TX_EP2_DPKTBUF_DIS      USB_TX_EP2_DPKTBUF_DIS_Msk
#define USB_TX_EP1_DPKTBUF_DIS_Pos  (1UL)
#define USB_TX_EP1_DPKTBUF_DIS_Msk  (0x1UL << USB_TX_EP1_DPKTBUF_DIS_Pos)
#define USB_TX_EP1_DPKTBUF_DIS      USB_TX_EP1_DPKTBUF_DIS_Msk

/********************  Bit definition for USB UCFG0 register  ******************/
#define USB_DM_OE_Pos               (31UL)
#define USB_DM_OE_Msk               (0x1UL << USB_DM_OE_Pos)
#define USB_DM_OE                   USB_DM_OE_Msk
#define USB_DM_OE_EN_Pos            (30UL)
#define USB_DM_OE_EN_Msk            (0x1UL << USB_DM_OE_EN_Pos)
#define USB_DM_OE_EN                USB_DM_OE_EN_Msk
#define USB_DP_OE_Pos               (29UL)
#define USB_DP_OE_Msk               (0x1UL << USB_DP_OE_Pos)
#define USB_DP_OE                   USB_DP_OE_Msk
#define USB_DP_OE_EN_Pos            (28UL)
#define USB_DP_OE_EN_Msk            (0x1UL << USB_DP_OE_EN_Pos)
#define USB_DP_OE_EN                USB_DP_OE_EN_Msk
#define USB_DM_IE_Pos               (27UL)
#define USB_DM_IE_Msk               (0x1UL << USB_DM_IE_Pos)
#define USB_DM_IE                   USB_DM_IE_Msk
#define USB_DM_IE_EN_Pos            (26UL)
#define USB_DM_IE_EN_Msk            (0x1UL << USB_DM_IE_EN_Pos)
#define USB_DM_IE_EN                USB_DM_IE_EN_Msk
#define USB_DP_IE_Pos               (25UL)
#define USB_DP_IE_Msk               (0x1UL << USB_DP_IE_Pos)
#define USB_DP_IE                   USB_DP_IE_Msk
#define USB_DP_IE_EN_Pos            (24UL)
#define USB_DP_IE_EN_Msk            (0x1UL << USB_DP_IE_EN_Pos)
#define USB_DP_IE_EN                USB_DP_IE_EN_Msk
#define USB_DM_SR_EN_Pos            (23UL)
#define USB_DM_SR_EN_Msk            (0x1UL << USB_DM_SR_EN_Pos)
#define USB_DM_SR_EN                USB_DM_SR_EN_Msk
#define USB_DM_TRIM_Pos             (20UL)
#define USB_DM_TRIM_Msk             (0x7UL << (USB_DM_TRIM_Pos))
#define USB_DM_TRIM                 USB_DM_TRIM_Msk
#define USB_DP_SR_EN_Pos            (19UL)
#define USB_DP_SR_EN_Msk            (0x1UL << USB_DP_SR_EN_Pos)
#define USB_DP_SR_EN                USB_DP_SR_EN_Msk
#define USB_DP_TRIM_Pos             (16UL)
#define USB_DP_TRIM_Msk             (0x7UL << (USB_DP_TRIM_Pos))
#define USB_DP_TRIM                 USB_DP_TRIM_Msk
#define USB_DM_PD_Pos               (15UL)
#define USB_DM_PD_Msk               (0x1UL << USB_DM_PD_Pos)
#define USB_DM_PD                   USB_DM_PD_Msk
#define USB_DM_PD_EN_Pos            (14UL)
#define USB_DM_PD_EN_Msk            (0x1UL << USB_DM_PD_EN_Pos)
#define USB_DM_PD_EN                USB_DM_PD_EN_Msk
#define USB_DM_PU_Pos               (13UL)
#define USB_DM_PU_Msk               (0x1UL << USB_DM_PU_Pos)
#define USB_DM_PU                   USB_DM_PU_Msk
#define USB_DM_PU_EN_Pos            (12UL)
#define USB_DM_PU_EN_Msk            (0x1UL << USB_DM_PU_EN_Pos)
#define USB_DM_PU_EN                USB_DM_PU_EN_Msk
#define USB_DP_PD_Pos               (11UL)
#define USB_DP_PD_Msk               (0x1UL << USB_DP_PD_Pos)
#define USB_DP_PD                   USB_DP_PD_Msk
#define USB_DP_PD_EN_Pos            (10UL)
#define USB_DP_PD_EN_Msk            (0x1UL << USB_DP_PD_EN_Pos)
#define USB_DP_PD_EN                USB_DP_PD_EN_Msk
#define USB_DP_PU_Pos               (9UL)
#define USB_DP_PU_Msk               (0x1UL << USB_DP_PU_Pos)
#define USB_DP_PU                   USB_DP_PU_Msk
#define USB_DP_PU_EN_Pos            (8UL)
#define USB_DP_PU_EN_Msk            (0x1UL << USB_DP_PU_EN_Pos)
#define USB_DP_PU_EN                USB_DP_PU_EN_Msk
#define USB_TEST_EN_Pos             (6UL)
#define USB_TEST_EN_Msk             (0x1UL << USB_TEST_EN_Pos)
#define USB_TEST_EN                 USB_TEST_EN_Msk
#define USB_VBUS_VALID_THRES_Pos    (5UL)
#define USB_VBUS_VALID_THRES_Msk    (0x1UL << USB_VBUS_VALID_THRES_Pos)
#define USB_VBUS_VALID_THRES        USB_VBUS_VALID_THRES_Msk
#define USB_VBUS_A_SESS_THRES_Pos   (4UL)
#define USB_VBUS_A_SESS_THRES_Msk   (0x1UL << USB_VBUS_A_SESS_THRES_Pos)
#define USB_VBUS_A_SESS_THRES       USB_VBUS_A_SESS_THRES_Msk
#define USB_VBUS_SESS_END_THRES_Pos (3UL)
#define USB_VBUS_SESS_END_THRES_Msk (0x1UL << USB_VBUS_SESS_END_THRES_Pos)
#define USB_VBUS_SESS_END_THRES     USB_VBUS_SESS_END_THRES_Msk
#define USB_MINI_AB_CONN_ID_Pos     (2UL)
#define USB_MINI_AB_CONN_ID_Msk     (0x1UL << USB_MINI_AB_CONN_ID_Pos)
#define USB_MINI_AB_CONN_ID         USB_MINI_AB_CONN_ID_Msk
#define USB_TEST_MODE_Pos           (1UL)
#define USB_TEST_MODE_Msk           (0x1UL << USB_TEST_MODE_Pos)
#define USB_TEST_MODE               USB_TEST_MODE_Msk
#define USB_PHY_EN_Pos              (0UL)
#define USB_PHY_EN_Msk              (0x1UL << USB_PHY_EN_Pos)
#define USB_PHY_EN                  USB_PHY_EN_Msk

/********************  Bit definition for USB UCFG1 register  ******************/
#define USB_LPM_ERR_CPU_INT_EN_Pos  (18UL)
#define USB_LPM_ERR_CPU_INT_EN_Msk  (0x1UL << USB_LPM_ERR_CPU_INT_EN_Pos)
#define USB_LPM_ERR_CPU_INT_EN      USB_LPM_ERR_CPU_INT_EN_Msk
#define USB_LPM_RES_CPU_INT_EN_Pos  (17UL)
#define USB_LPM_RES_CPU_INT_EN_Msk  (0x1UL << USB_LPM_RES_CPU_INT_EN_Pos)
#define USB_LPM_RES_CPU_INT_EN      USB_LPM_RES_CPU_INT_EN_Msk
#define USB_LPM_NC_CPU_INT_EN_Pos   (16UL)
#define USB_LPM_NC_CPU_INT_EN_Msk   (0x1UL << USB_LPM_NC_CPU_INT_EN_Pos)
#define USB_LPM_NC_CPU_INT_EN       USB_LPM_NC_CPU_INT_EN_Msk
#define USB_LPM_ACK_CPU_INT_EN_Pos  (15UL)
#define USB_LPM_ACK_CPU_INT_EN_Msk  (0x1UL << USB_LPM_ACK_CPU_INT_EN_Pos)
#define USB_LPM_ACK_CPU_INT_EN      USB_LPM_ACK_CPU_INT_EN_Msk
#define USB_LPM_NY_CPU_INT_EN_Pos   (14UL)
#define USB_LPM_NY_CPU_INT_EN_Msk   (0x1UL << USB_LPM_NY_CPU_INT_EN_Pos)
#define USB_LPM_NY_CPU_INT_EN       USB_LPM_NY_CPU_INT_EN_Msk
#define USB_LPM_ST_CPU_INT_EN_Pos   (13UL)
#define USB_LPM_ST_CPU_INT_EN_Msk   (0x1UL << USB_LPM_ST_CPU_INT_EN_Pos)
#define USB_LPM_ST_CPU_INT_EN       USB_LPM_ST_CPU_INT_EN_Msk
#define USB_EP2_RX_CPU_INT_EN_Pos   (12UL)
#define USB_EP2_RX_CPU_INT_EN_Msk   (0x1UL << USB_EP2_RX_CPU_INT_EN_Pos)
#define USB_EP2_RX_CPU_INT_EN       USB_EP2_RX_CPU_INT_EN_Msk
#define USB_EP1_RX_CPU_INT_EN_Pos   (11UL)
#define USB_EP1_RX_CPU_INT_EN_Msk   (0x1UL << USB_EP1_RX_CPU_INT_EN_Pos)
#define USB_EP1_RX_CPU_INT_EN       USB_EP1_RX_CPU_INT_EN_Msk
#define USB_EP2_TX_CPU_INT_EN_Pos   (10UL)
#define USB_EP2_TX_CPU_INT_EN_Msk   (0x1UL << USB_EP2_TX_CPU_INT_EN_Pos)
#define USB_EP2_TX_CPU_INT_EN       USB_EP2_TX_CPU_INT_EN_Msk
#define USB_EP1_TX_CPU_INT_EN_Pos   (9UL)
#define USB_EP1_TX_CPU_INT_EN_Msk   (0x1UL << USB_EP1_TX_CPU_INT_EN_Pos)
#define USB_EP1_TX_CPU_INT_EN       USB_EP1_TX_CPU_INT_EN_Msk
#define USB_EP0_CPU_INT_EN_Pos      (8UL)
#define USB_EP0_CPU_INT_EN_Msk      (0x1UL << USB_EP0_CPU_INT_EN_Pos)
#define USB_EP0_CPU_INT_EN          USB_EP0_CPU_INT_EN_Msk
#define USB_VBUS_ERR_CPU_INT_EN_Pos (7UL)
#define USB_VBUS_ERR_CPU_INT_EN_Msk (0x1UL << USB_VBUS_ERR_CPU_INT_EN_Pos)
#define USB_VBUS_ERR_CPU_INT_EN     USB_VBUS_ERR_CPU_INT_EN_Msk
#define USB_SESS_REQ_CPU_INT_EN_Pos (6UL)
#define USB_SESS_REQ_CPU_INT_EN_Msk (0x1UL << USB_SESS_REQ_CPU_INT_EN_Pos)
#define USB_SESS_REQ_CPU_INT_EN     USB_SESS_REQ_CPU_INT_EN_Msk
#define USB_DISCONN_CPU_INT_EN_Pos  (5UL)
#define USB_DISCONN_CPU_INT_EN_Msk  (0x1UL << USB_DISCONN_CPU_INT_EN_Pos)
#define USB_DISCONN_CPU_INT_EN      USB_DISCONN_CPU_INT_EN_Msk
#define USB_CONN_CPU_INT_EN_Pos     (4UL)
#define USB_CONN_CPU_INT_EN_Msk     (0x1UL << USB_CONN_CPU_INT_EN_Pos)
#define USB_CONN_CPU_INT_EN         USB_CONN_CPU_INT_EN_Msk
#define USB_SOF_CPU_INT_EN_Pos      (3UL)
#define USB_SOF_CPU_INT_EN_Msk      (0x1UL << USB_SOF_CPU_INT_EN_Pos)
#define USB_SOF_CPU_INT_EN          USB_SOF_CPU_INT_EN_Msk
#define USB_BABB_RST_CPU_INT_EN_Pos (2UL)
#define USB_BABB_RST_CPU_INT_EN_Msk (0x1UL << USB_BABB_RST_CPU_INT_EN_Pos)
#define USB_BABB_RST_CPU_INT_EN     USB_BABB_RST_CPU_INT_EN_Msk
#define USB_RESUME_CPU_INT_EN_Pos   (1UL)
#define USB_RESUME_CPU_INT_EN_Msk   (0x1UL << USB_RESUME_CPU_INT_EN_Pos)
#define USB_RESUME_CPU_INT_EN       USB_RESUME_CPU_INT_EN_Msk
#define USB_SUSPEND_CPU_INT_EN_Pos  (0UL)
#define USB_SUSPEND_CPU_INT_EN_Msk  (0x1UL << USB_SUSPEND_CPU_INT_EN_Pos)
#define USB_SUSPEND_CPU_INT_EN      USB_SUSPEND_CPU_INT_EN_Msk

#define USB_LPM_INT_TO_CPU_Msk      (0x3FUL << USB_LPM_ST_CPU_INT_EN_Pos)
#define USB_EP_INT_TO_CPU_Msk       (0x1FUL << USB_EP0_CPU_INT_EN_Pos)
#define USB_CTRL_INT_TO_CPU_Msk     (0xFFUL << USB_SUSPEND_CPU_INT_EN_Pos)

/********************  Bit definition for USB UCFG2 register  ******************/
#define USB_SEND_STATE_Pos          (30UL)
#define USB_SEND_STATE_Msk          (0x3UL << USB_SEND_STATE_Pos)
#define USB_SEND_STATE              USB_SEND_STATE_Msk
#define USB_IN_STATE_Pos            (26UL)
#define USB_IN_STATE_Msk            (0x1UL << USB_IN_STATE_Pos)
#define USB_IN_STATE                USB_IN_STATE_Msk
#define USB_OUT_STATE_Pos           (25UL)
#define USB_OUT_STATE_Msk           (0x1UL << USB_OUT_STATE_Pos)
#define USB_OUT_STATE               USB_OUT_STATE_Msk
#define USB_SETUP_STATE_Pos         (24UL)
#define USB_SETUP_STATE_Msk         (0x1UL << USB_SETUP_STATE_Pos)
#define USB_SETUP_STATE             USB_SETUP_STATE_Msk
#define USB_DPOE_STA_Pos            (23UL)
#define USB_DPOE_STA_Msk            (0x1UL << USB_DPOE_STA_Pos)
#define USB_DPOE_STA                USB_DPOE_STA_Msk
#define USB_DMOE_STA_Pos            (22UL)
#define USB_DMOE_STA_Msk            (0x1UL << USB_DMOE_STA_Pos)
#define USB_DMOE_STA                USB_DMOE_STA_Msk
#define USB_DPIE_STA_Pos            (21UL)
#define USB_DPIE_STA_Msk            (0x1UL << USB_DPIE_STA_Pos)
#define USB_DPIE_STA                USB_DPIE_STA_Msk
#define USB_DMIE_STA_Pos            (20UL)
#define USB_DMIE_STA_Msk            (0x1UL << USB_DMIE_STA_Pos)
#define USB_DMIE_STA                USB_DMIE_STA_Msk
#define USB_DIP_STA_Pos             (19UL)
#define USB_DIP_STA_Msk             (0x1UL << USB_DIP_STA_Pos)
#define USB_DIP_STA                 USB_DIP_STA_Msk
#define USB_DIM_STA_Pos             (18UL)
#define USB_DIM_STA_Msk             (0x1UL << USB_DIM_STA_Pos)
#define USB_DIM_STA                 USB_DIM_STA_Msk
#define USB_DOP_STA_Pos             (17UL)
#define USB_DOP_STA_Msk             (0x1UL << USB_DOP_STA_Pos)
#define USB_DOP_STA                 USB_DOP_STA_Msk
#define USB_DOM_STA_Pos             (16UL)
#define USB_DOM_STA_Msk             (0x1UL << USB_DOM_STA_Pos)
#define USB_DOM_STA                 USB_DOM_STA_Msk
#define USB_DEBOUCE_MAX_Pos         (4UL)
#define USB_DEBOUCE_MAX_Msk         (0x3FFFUL << USB_DEBOUCE_MAX_Pos)
#define USB_DEBOUCE_MAX             USB_DEBOUCE_MAX_Msk
#define USB_DISCONN_INT_EN_Pos      (3UL)
#define USB_DISCONN_INT_EN_Msk      (0x1UL << USB_DISCONN_INT_EN_Pos)
#define USB_DISCONN_INT_EN          USB_DISCONN_INT_EN_Msk
#define USB_DISCONN_INT_STA_Pos     (2UL)
#define USB_DISCONN_INT_STA_Msk     (0x1UL << USB_DISCONN_INT_STA_Pos)
#define USB_DISCONN_INT_STA         USB_DISCONN_INT_STA_Msk
#define USB_CONN_INT_EN_Pos         (1UL)
#define USB_CONN_INT_EN_Msk         (0x1UL << USB_CONN_INT_EN_Pos)
#define USB_CONN_INT_EN             USB_CONN_INT_EN_Msk
#define USB_CONN_INT_STA_Pos        (0UL)
#define USB_CONN_INT_STA_Msk        (0x1UL << USB_CONN_INT_STA_Pos)
#define USB_CONN_INT_STA            USB_CONN_INT_STA_Msk


/******************************************************************************/
/*                                                                            */
/*                        System Control (SYSCTRL)                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for PLL0CR register  *****************/
#define SYSCTRL_PLL0_EN_Pos                     (31UL)                  /*!< PLL_EN (Bit 31)                                */
#define SYSCTRL_PLL0_EN_Msk                     (0x80000000UL)          /*!< PLL_EN (Bitfield-Mask: 0x01)                   */
#define SYSCTRL_PLL0_EN                         SYSCTRL_PLL0_EN_Msk
#define SYSCTRL_PLL0_LOCKED_Pos                 (30UL)                  /*!< PLL_LOCKED (Bit 30)                            */
#define SYSCTRL_PLL0_LOCKED_Msk                 (0x40000000UL)          /*!< PLL_LOCKED (Bitfield-Mask: 0x01)               */
#define SYSCTRL_PLL0_LOCKED                     SYSCTRL_PLL0_LOCKED_Msk
#define SYSCTRL_PLL0_LPF_Pos                    (28UL)                  /*!< PLL_LPF (Bit 28)                               */
#define SYSCTRL_PLL0_LPF_Msk                    (0x10000000UL)          /*!< PLL_LPF (Bitfield-Mask: 0x01)                  */
#define SYSCTRL_PLL0_LPF                        SYSCTRL_PLL0_LPF_Msk
#define SYSCTRL_PLL0_BAND_Pos                   (21UL)                  /*!< PLL_BAND (Bit 21)                              */
#define SYSCTRL_PLL0_BAND_Msk                   (0x600000UL)            /*!< PLL_BAND (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_PLL0_BAND                       SYSCTRL_PLL0_BAND_Msk
#define SYSCTRL_PLL0_BAND_312M                  (0x0UL << SYSCTRL_PLL0_BAND_Pos)
#define SYSCTRL_PLL0_BAND_396M                  (0x1UL << SYSCTRL_PLL0_BAND_Pos)
#define SYSCTRL_PLL0_BAND_466M                  (0x2UL << SYSCTRL_PLL0_BAND_Pos)
#define SYSCTRL_PLL0_BAND_520M                  (0x3UL << SYSCTRL_PLL0_BAND_Pos)
#define SYSCTRL_PLL0_GVCO_Pos                   (18UL)                  /*!< PLL_GVCO (Bit 18)                              */
#define SYSCTRL_PLL0_GVCO_Msk                   (0xc0000UL)             /*!< PLL_GVCO (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_PLL0_GVCO                       SYSCTRL_PLL0_GVCO_Msk
#define SYSCTRL_PLL0_GVCO_0                     (0x0UL << SYSCTRL_PLL0_GVCO_Pos)
#define SYSCTRL_PLL0_GVCO_1                     (0x1UL << SYSCTRL_PLL0_GVCO_Pos)
#define SYSCTRL_PLL0_GVCO_2                     (0x2UL << SYSCTRL_PLL0_GVCO_Pos)
#define SYSCTRL_PLL0_GVCO_3                     (0x3UL << SYSCTRL_PLL0_GVCO_Pos)
#define SYSCTRL_PLL0_DIV_Pos                    (4UL)                   /*!< PLL_DIV (Bit 4)                                */
#define SYSCTRL_PLL0_DIV_Msk                    (0xf0UL)                /*!< PLL_DIV (Bitfield-Mask: 0x0f)                  */
#define SYSCTRL_PLL0_DIV                        SYSCTRL_PLL0_DIV_Msk
#define SYSCTRL_PLL0_PREDIV_Pos                 (3UL)                   /*!< PLL_PREDIV (Bit 3)                             */
#define SYSCTRL_PLL0_PREDIV_Msk                 (0x8UL)                 /*!< PLL_PREDIV (Bitfield-Mask: 0x01)               */
#define SYSCTRL_PLL0_PREDIV                     SYSCTRL_PLL0_PREDIV_Msk
#define SYSCTRL_PLL0_REFCLK_Pos                 (0UL)                   /*!< PLL_REFCLK (Bit 0)                             */
#define SYSCTRL_PLL0_REFCLK_Msk                 (0x3UL)                 /*!< PLL_REFCLK (Bitfield-Mask: 0x03)               */
#define SYSCTRL_PLL0_REFCLK                     SYSCTRL_PLL0_REFCLK_Msk
#define SYSCTRL_PLL0_REFCLK_XOSC                (0x0UL << SYSCTRL_PLL0_REFCLK_Pos)
#define SYSCTRL_PLL0_REFCLK_RC8M                (0x1UL << SYSCTRL_PLL0_REFCLK_Pos)
#define SYSCTRL_PLL0_REFCLK_CLOSE               (0x2UL << SYSCTRL_PLL0_REFCLK_Pos)
#define SYSCTRL_PLL0_REFCLK_DFT                 (0x3UL << SYSCTRL_PLL0_REFCLK_Pos)

/********************  Bit definition for PLL1CR register  *****************/
#define SYSCTRL_PLL1_EN_Pos                     (31UL)                  /*!< PLL_EN (Bit 31)                                */
#define SYSCTRL_PLL1_EN_Msk                     (0x80000000UL)          /*!< PLL_EN (Bitfield-Mask: 0x01)                   */
#define SYSCTRL_PLL1_EN                         SYSCTRL_PLL1_EN_Msk
#define SYSCTRL_PLL1_LOCKED_Pos                 (30UL)                  /*!< PLL_LOCKED (Bit 30)                            */
#define SYSCTRL_PLL1_LOCKED_Msk                 (0x40000000UL)          /*!< PLL_LOCKED (Bitfield-Mask: 0x01)               */
#define SYSCTRL_PLL1_LOCKED                     SYSCTRL_PLL1_LOCKED_Msk
#define SYSCTRL_PLL1_LPF_Pos                    (28UL)                  /*!< PLL_LPF (Bit 28)                               */
#define SYSCTRL_PLL1_LPF_Msk                    (0x10000000UL)          /*!< PLL_LPF (Bitfield-Mask: 0x01)                  */
#define SYSCTRL_PLL1_LPF                        SYSCTRL_PLL1_LPF_Msk
#define SYSCTRL_PLL1_BAND_Pos                   (21UL)                  /*!< PLL_BAND (Bit 21)                              */
#define SYSCTRL_PLL1_BAND_Msk                   (0x600000UL)            /*!< PLL_BAND (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_PLL1_BAND                       SYSCTRL_PLL1_BAND_Msk
#define SYSCTRL_PLL1_BAND_312M                  (0x0UL << SYSCTRL_PLL1_BAND_Pos)
#define SYSCTRL_PLL1_BAND_396M                  (0x1UL << SYSCTRL_PLL1_BAND_Pos)
#define SYSCTRL_PLL1_BAND_466M                  (0x2UL << SYSCTRL_PLL1_BAND_Pos)
#define SYSCTRL_PLL1_BAND_520M                  (0x3UL << SYSCTRL_PLL1_BAND_Pos)
#define SYSCTRL_PLL1_GVCO_Pos                   (18UL)                  /*!< PLL_GVCO (Bit 18)                              */
#define SYSCTRL_PLL1_GVCO_Msk                   (0xc0000UL)             /*!< PLL_GVCO (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_PLL1_GVCO                       SYSCTRL_PLL1_GVCO_Msk
#define SYSCTRL_PLL1_GVCO_0                     (0x0UL << SYSCTRL_PLL1_GVCO_Pos)
#define SYSCTRL_PLL1_GVCO_1                     (0x1UL << SYSCTRL_PLL1_GVCO_Pos)
#define SYSCTRL_PLL1_GVCO_2                     (0x2UL << SYSCTRL_PLL1_GVCO_Pos)
#define SYSCTRL_PLL1_GVCO_3                     (0x3UL << SYSCTRL_PLL1_GVCO_Pos)
#define SYSCTRL_PLL1_DIV_Pos                    (4UL)                   /*!< PLL_DIV (Bit 4)                                */
#define SYSCTRL_PLL1_DIV_Msk                    (0xf0UL)                /*!< PLL_DIV (Bitfield-Mask: 0x0f)                  */
#define SYSCTRL_PLL1_DIV                        SYSCTRL_PLL1_DIV_Msk
#define SYSCTRL_PLL1_PREDIV_Pos                 (3UL)                   /*!< PLL_PREDIV (Bit 3)                             */
#define SYSCTRL_PLL1_PREDIV_Msk                 (0x8UL)                 /*!< PLL_PREDIV (Bitfield-Mask: 0x01)               */
#define SYSCTRL_PLL1_PREDIV                     SYSCTRL_PLL1_PREDIV_Msk
#define SYSCTRL_PLL1_REFCLK_Pos                 (0UL)                   /*!< PLL_REFCLK (Bit 0)                             */
#define SYSCTRL_PLL1_REFCLK_Msk                 (0x3UL)                 /*!< PLL_REFCLK (Bitfield-Mask: 0x03)               */
#define SYSCTRL_PLL1_REFCLK                     SYSCTRL_PLL1_REFCLK_Msk
#define SYSCTRL_PLL1_REFCLK_XOSC                (0x0UL << SYSCTRL_PLL1_REFCLK_Pos)
#define SYSCTRL_PLL1_REFCLK_RC8M                (0x1UL << SYSCTRL_PLL1_REFCLK_Pos)
#define SYSCTRL_PLL1_REFCLK_CLOSE               (0x2UL << SYSCTRL_PLL1_REFCLK_Pos)
#define SYSCTRL_PLL1_REFCLK_DFT                 (0x3UL << SYSCTRL_PLL1_REFCLK_Pos)

/********************  Bit definition for PLL2CR register  *****************/
#define SYSCTRL_PLL2_EN_Pos                     (31UL)                  /*!< PLL_EN (Bit 31)                                */
#define SYSCTRL_PLL2_EN_Msk                     (0x80000000UL)          /*!< PLL_EN (Bitfield-Mask: 0x01)                   */
#define SYSCTRL_PLL2_EN                         SYSCTRL_PLL2_EN_Msk
#define SYSCTRL_PLL2_LOCKED_Pos                 (30UL)                  /*!< PLL_LOCKED (Bit 30)                            */
#define SYSCTRL_PLL2_LOCKED_Msk                 (0x40000000UL)          /*!< PLL_LOCKED (Bitfield-Mask: 0x01)               */
#define SYSCTRL_PLL2_LOCKED                     SYSCTRL_PLL2_LOCKED_Msk
#define SYSCTRL_PLL2_LPF_Pos                    (28UL)                  /*!< PLL_LPF (Bit 28)                               */
#define SYSCTRL_PLL2_LPF_Msk                    (0x10000000UL)          /*!< PLL_LPF (Bitfield-Mask: 0x01)                  */
#define SYSCTRL_PLL2_LPF                        SYSCTRL_PLL2_LPF_Msk
#define SYSCTRL_PLL2_BAND_Pos                   (21UL)                  /*!< PLL_BAND (Bit 21)                              */
#define SYSCTRL_PLL2_BAND_Msk                   (0x600000UL)            /*!< PLL_BAND (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_PLL2_BAND                       SYSCTRL_PLL2_BAND_Msk
#define SYSCTRL_PLL2_BAND_312M                  (0x0UL << SYSCTRL_PLL2_BAND_Pos)
#define SYSCTRL_PLL2_BAND_396M                  (0x1UL << SYSCTRL_PLL2_BAND_Pos)
#define SYSCTRL_PLL2_BAND_466M                  (0x2UL << SYSCTRL_PLL2_BAND_Pos)
#define SYSCTRL_PLL2_BAND_520M                  (0x3UL << SYSCTRL_PLL2_BAND_Pos)
#define SYSCTRL_PLL2_GVCO_Pos                   (18UL)                  /*!< PLL_GVCO (Bit 18)                              */
#define SYSCTRL_PLL2_GVCO_Msk                   (0xc0000UL)             /*!< PLL_GVCO (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_PLL2_GVCO                       SYSCTRL_PLL2_GVCO_Msk
#define SYSCTRL_PLL2_GVCO_0                     (0x0UL << SYSCTRL_PLL2_GVCO_Pos)
#define SYSCTRL_PLL2_GVCO_1                     (0x1UL << SYSCTRL_PLL2_GVCO_Pos)
#define SYSCTRL_PLL2_GVCO_2                     (0x2UL << SYSCTRL_PLL2_GVCO_Pos)
#define SYSCTRL_PLL2_GVCO_3                     (0x3UL << SYSCTRL_PLL2_GVCO_Pos)
#define SYSCTRL_PLL2_DIV_Pos                    (4UL)                   /*!< PLL_DIV (Bit 4)                                */
#define SYSCTRL_PLL2_DIV_Msk                    (0xf0UL)                /*!< PLL_DIV (Bitfield-Mask: 0x0f)                  */
#define SYSCTRL_PLL2_DIV                        SYSCTRL_PLL2_DIV_Msk
#define SYSCTRL_PLL2_PREDIV_Pos                 (3UL)                   /*!< PLL_PREDIV (Bit 3)                             */
#define SYSCTRL_PLL2_PREDIV_Msk                 (0x8UL)                 /*!< PLL_PREDIV (Bitfield-Mask: 0x01)               */
#define SYSCTRL_PLL2_PREDIV                     SYSCTRL_PLL2_PREDIV_Msk
#define SYSCTRL_PLL2_REFCLK_Pos                 (0UL)                   /*!< PLL_REFCLK (Bit 0)                             */
#define SYSCTRL_PLL2_REFCLK_Msk                 (0x3UL)                 /*!< PLL_REFCLK (Bitfield-Mask: 0x03)               */
#define SYSCTRL_PLL2_REFCLK                     SYSCTRL_PLL2_REFCLK_Msk
#define SYSCTRL_PLL2_REFCLK_XOSC                (0x0UL << SYSCTRL_PLL2_REFCLK_Pos)
#define SYSCTRL_PLL2_REFCLK_RC8M                (0x1UL << SYSCTRL_PLL2_REFCLK_Pos)
#define SYSCTRL_PLL2_REFCLK_CLOSE               (0x2UL << SYSCTRL_PLL2_REFCLK_Pos)
#define SYSCTRL_PLL2_REFCLK_DFT                 (0x3UL << SYSCTRL_PLL2_REFCLK_Pos)

/*******************  Bit definition for SCLKCR register  ****************/
#define SYSCTRL_SYSCLK_DIV_Pos                  (16UL)                  /*!< SYSCLK_DIV (Bit 16)                            */
#define SYSCTRL_SYSCLK_DIV_Msk                  (0xff0000UL)            /*!< SYSCLK_DIV (Bitfield-Mask: 0xff)               */
#define SYSCTRL_SYSCLK_DIV                      SYSCTRL_SYSCLK_DIV_Msk
#define SYSCTRL_SYSCLK_SRC_Pos                  (0UL)                   /*!< SYSCLK_SRC (Bit 0)                             */
#define SYSCTRL_SYSCLK_SRC_Msk                  (0x3UL)                 /*!< SYSCLK_SRC (Bitfield-Mask: 0x03)               */
#define SYSCTRL_SYSCLK_SRC                      SYSCTRL_SYSCLK_SRC_Msk
#define SYSCTRL_SYSCLK_SRC_RC32K                (0x0UL << SYSCTRL_SYSCLK_SRC_Pos)
#define SYSCTRL_SYSCLK_SRC_RC8M                 (0x1UL << SYSCTRL_SYSCLK_SRC_Pos)
#define SYSCTRL_SYSCLK_SRC_PLLDivClk            (0x2UL << SYSCTRL_SYSCLK_SRC_Pos)
#define SYSCTRL_SYSCLK_SRC_HOSC                 (0x3UL << SYSCTRL_SYSCLK_SRC_Pos)

/*******************  Bit definition for BCLKCR register  ****************/
#define SYSCTRL_APB1CLK_EN_Pos                  (18UL)                  /*!< APB1CLK_EN (Bit 18)                            */
#define SYSCTRL_APB1CLK_EN_Msk                  (0x40000UL)             /*!< APB1CLK_EN (Bitfield-Mask: 0x01)               */
#define SYSCTRL_APB1CLK_EN                      SYSCTRL_APB1CLK_EN_Msk
#define SYSCTRL_APB0CLK_EN_Pos                  (17UL)                  /*!< APB0CLK_EN (Bit 17)                            */
#define SYSCTRL_APB0CLK_EN_Msk                  (0x20000UL)             /*!< APB0CLK_EN (Bitfield-Mask: 0x01)               */
#define SYSCTRL_APB0CLK_EN                      SYSCTRL_APB0CLK_EN_Msk
#define SYSCTRL_AHBCLK_EN_Pos                   (16UL)                  /*!< AHBCLK_EN (Bit 16)                             */
#define SYSCTRL_AHBCLK_EN_Msk                   (0x10000UL)             /*!< AHBCLK_EN (Bitfield-Mask: 0x01)                */
#define SYSCTRL_AHBCLK_EN                       SYSCTRL_AHBCLK_EN_Msk
#define SYSCTRL_APB1CLK_DIV_Pos                 (8UL)                   /*!< APB1CLK_DIV (Bit 8)                            */
#define SYSCTRL_APB1CLK_DIV_Msk                 (0xff00UL)              /*!< APB1CLK_DIV (Bitfield-Mask: 0xff)              */
#define SYSCTRL_APB1CLK_DIV                     SYSCTRL_APB1CLK_DIV_Msk
#define SYSCTRL_APB0CLK_DIV_Pos                 (0UL)                   /*!< APB0CLK_DIV (Bit 0)                            */
#define SYSCTRL_APB0CLK_DIV_Msk                 (0xffUL)                /*!< APB0CLK_DIV (Bitfield-Mask: 0xff)              */
#define SYSCTRL_APB0CLK_DIV                     SYSCTRL_APB0CLK_DIV_Msk

/*********************  Bit definition for FSRCCR register  ******************/
#define SYSCTRL_GPIOD_DBCCLK_SRC_Pos            (22UL)                  /*!< GPIOD_DBCCLK_SRC (Bit 22)                      */
#define SYSCTRL_GPIOD_DBCCLK_SRC_Msk            (0xc00000UL)            /*!< GPIOD_DBCCLK_SRC (Bitfield-Mask: 0x03)         */
#define SYSCTRL_GPIOD_DBCCLK_SRC                SYSCTRL_GPIOD_DBCCLK_SRC_Msk
#define SYSCTRL_GPIOD_DBCCLK_SRC_RC8M           (0x0UL << SYSCTRL_GPIOD_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOD_DBCCLK_SRC_XOSC           (0x1UL << SYSCTRL_GPIOD_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOD_DBCCLK_SRC_SYSCLK         (0x2UL << SYSCTRL_GPIOD_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOD_DBCCLK_SRC_RC32K          (0x3UL << SYSCTRL_GPIOD_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOC_DBCCLK_SRC_Pos            (20UL)                  /*!< GPIOC_DBCCLK_SRC (Bit 20)                      */
#define SYSCTRL_GPIOC_DBCCLK_SRC_Msk            (0x300000UL)            /*!< GPIOC_DBCCLK_SRC (Bitfield-Mask: 0x03)         */
#define SYSCTRL_GPIOC_DBCCLK_SRC                SYSCTRL_GPIOC_DBCCLK_SRC_Msk
#define SYSCTRL_GPIOC_DBCCLK_SRC_RC8M           (0x0UL << SYSCTRL_GPIOC_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOC_DBCCLK_SRC_XOSC           (0x1UL << SYSCTRL_GPIOC_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOC_DBCCLK_SRC_SYSCLK         (0x2UL << SYSCTRL_GPIOC_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOC_DBCCLK_SRC_RC32K          (0x3UL << SYSCTRL_GPIOC_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOB_DBCCLK_SRC_Pos            (18UL)                  /*!< GPIOB_DBCCLK_SRC (Bit 18)                      */
#define SYSCTRL_GPIOB_DBCCLK_SRC_Msk            (0xc0000UL)             /*!< GPIOB_DBCCLK_SRC (Bitfield-Mask: 0x03)         */
#define SYSCTRL_GPIOB_DBCCLK_SRC                SYSCTRL_GPIOB_DBCCLK_SRC_Msk
#define SYSCTRL_GPIOB_DBCCLK_SRC_RC8M           (0x0UL << SYSCTRL_GPIOB_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOB_DBCCLK_SRC_XOSC           (0x1UL << SYSCTRL_GPIOB_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOB_DBCCLK_SRC_SYSCLK         (0x2UL << SYSCTRL_GPIOB_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOB_DBCCLK_SRC_RC32K          (0x3UL << SYSCTRL_GPIOB_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOA_DBCCLK_SRC_Pos            (16UL)                  /*!< GPIOA_DBCCLK_SRC (Bit 16)                      */
#define SYSCTRL_GPIOA_DBCCLK_SRC_Msk            (0x30000UL)             /*!< GPIOA_DBCCLK_SRC (Bitfield-Mask: 0x03)         */
#define SYSCTRL_GPIOA_DBCCLK_SRC                SYSCTRL_GPIOA_DBCCLK_SRC_Msk
#define SYSCTRL_GPIOA_DBCCLK_SRC_RC8M           (0x0UL << SYSCTRL_GPIOA_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOA_DBCCLK_SRC_XOSC           (0x1UL << SYSCTRL_GPIOA_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOA_DBCCLK_SRC_SYSCLK         (0x2UL << SYSCTRL_GPIOA_DBCCLK_SRC_Pos)
#define SYSCTRL_GPIOA_DBCCLK_SRC_RC32K          (0x3UL << SYSCTRL_GPIOA_DBCCLK_SRC_Pos)
#define SYSCTRL_DFLASH_MEMCLK_SRC_Pos           (7UL)                   /*!< DFLASH_MEMCLK_SRC (Bit 7)                      */
#define SYSCTRL_DFLASH_MEMCLK_SRC_Msk           (0x180UL)               /*!< DFLASH_MEMCLK_SRC (Bitfield-Mask: 0x03)        */
#define SYSCTRL_DFLASH_MEMCLK_SRC               SYSCTRL_DFLASH_MEMCLK_SRC_Msk
#define SYSCTRL_DFLASH_MEMCLK_SRC_RC8M          (0x0UL << SYSCTRL_DFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_DFLASH_MEMCLK_SRC_PLL0DivClk    (0x1UL << SYSCTRL_DFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_DFLASH_MEMCLK_SRC_PLL1DivClk    (0x2UL << SYSCTRL_DFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_DFLASH_MEMCLK_SRC_PLL2DivClk    (0x3UL << SYSCTRL_DFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_EFLASH_MEMCLK_SRC_Pos           (5UL)                   /*!< EFLASH_MEMCLK_SRC (Bit 5)                      */
#define SYSCTRL_EFLASH_MEMCLK_SRC_Msk           (0x60UL)                /*!< EFLASH_MEMCLK_SRC (Bitfield-Mask: 0x03)        */
#define SYSCTRL_EFLASH_MEMCLK_SRC               SYSCTRL_EFLASH_MEMCLK_SRC_Msk
#define SYSCTRL_EFLASH_MEMCLK_SRC_RC8M          (0x0UL << SYSCTRL_EFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_EFLASH_MEMCLK_SRC_PLL0DivClk    (0x1UL << SYSCTRL_EFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_EFLASH_MEMCLK_SRC_PLL1DivClk    (0x2UL << SYSCTRL_EFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_EFLASH_MEMCLK_SRC_PLL2DivClk    (0x3UL << SYSCTRL_EFLASH_MEMCLK_SRC_Pos)
#define SYSCTRL_ADC_FUNCLK_SRC_Pos              (2UL)                   /*!< ADC_FUNCLK_SRC (Bit 2)                         */
#define SYSCTRL_ADC_FUNCLK_SRC_Msk              (0xcUL)                 /*!< ADC_FUNCLK_SRC (Bitfield-Mask: 0x03)           */
#define SYSCTRL_ADC_FUNCLK_SRC                  SYSCTRL_ADC_FUNCLK_SRC_Msk
#define SYSCTRL_ADC_FUNCLK_SRC_RC8M             (0x0UL << SYSCTRL_ADC_FUNCLK_SRC_Pos)
#define SYSCTRL_ADC_FUNCLK_SRC_HOSC             (0x1UL << SYSCTRL_ADC_FUNCLK_SRC_Pos)
#define SYSCTRL_ADC_FUNCLK_SRC_PLL0             (0x2UL << SYSCTRL_ADC_FUNCLK_SRC_Pos)
#define SYSCTRL_ADC_FUNCLK_SRC_PLL1             (0x3UL << SYSCTRL_ADC_FUNCLK_SRC_Pos)
#define SYSCTRL_HRPWM_FUNCLK_SRC_Pos            (0UL)                   /*!< HRPWM_FUNCLK_SRC (Bit 0)                       */
#define SYSCTRL_HRPWM_FUNCLK_SRC_Msk            (0x3UL)                 /*!< HRPWM_FUNCLK_SRC (Bitfield-Mask: 0x03)         */
#define SYSCTRL_HRPWM_FUNCLK_SRC                SYSCTRL_HRPWM_FUNCLK_SRC_Msk
#define SYSCTRL_HRPWM_FUNCLK_SRC_RC8M           (0x0UL << SYSCTRL_HRPWM_FUNCLK_SRC_Pos)
#define SYSCTRL_HRPWM_FUNCLK_SRC_HOSC           (0x1UL << SYSCTRL_HRPWM_FUNCLK_SRC_Pos)
#define SYSCTRL_HRPWM_FUNCLK_SRC_PLL0           (0x2UL << SYSCTRL_HRPWM_FUNCLK_SRC_Pos)
#define SYSCTRL_HRPWM_FUNCLK_SRC_PLL1           (0x3UL << SYSCTRL_HRPWM_FUNCLK_SRC_Pos)

/*********************  Bit definition for FCD0CR register  *****************/
#define SYSCTRL_DFLASH_MEMCLK_DIV_Pos           (8UL)                   /*!< DFLASH_MEMCLK_DIV (Bit 8)                      */
#define SYSCTRL_DFLASH_MEMCLK_DIV_Msk           (0xf00UL)               /*!< DFLASH_MEMCLK_DIV (Bitfield-Mask: 0x0f)        */
#define SYSCTRL_DFLASH_MEMCLK_DIV               SYSCTRL_DFLASH_MEMCLK_DIV_Msk
#define SYSCTRL_EFLASH_MEMCLK_DIV_Pos           (4UL)                   /*!< EFLASH_MEMCLK_DIV (Bit 4)                      */
#define SYSCTRL_EFLASH_MEMCLK_DIV_Msk           (0xf0UL)                /*!< EFLASH_MEMCLK_DIV (Bitfield-Mask: 0x0f)        */
#define SYSCTRL_EFLASH_MEMCLK_DIV               SYSCTRL_EFLASH_MEMCLK_DIV_Msk
#define SYSCTRL_ADC_FUNCLK_DIV_Pos              (2UL)                   /*!< ADC_FUNCLK_DIV (Bit 2)                         */
#define SYSCTRL_ADC_FUNCLK_DIV_Msk              (0xcUL)                 /*!< ADC_FUNCLK_DIV (Bitfield-Mask: 0x03)           */
#define SYSCTRL_ADC_FUNCLK_DIV                  SYSCTRL_ADC_FUNCLK_DIV_Msk
#define SYSCTRL_HRPWM_FUNCLK_DIV_Pos            (0UL)                   /*!< HRPWM_FUNCLK_DIV (Bit 0)                       */
#define SYSCTRL_HRPWM_FUNCLK_DIV_Msk            (0x3UL)                 /*!< HRPWM_FUNCLK_DIV (Bitfield-Mask: 0x03)         */
#define SYSCTRL_HRPWM_FUNCLK_DIV                SYSCTRL_HRPWM_FUNCLK_DIV_Msk

/*********************  Bit definition for FCD1CR register  *****************/
#define SYSCTRL_GPIOD_DBCCLK_DIV_Pos            (24UL)                  /*!< GPIOD_DBCCLK_DIV (Bit 24)                      */
#define SYSCTRL_GPIOD_DBCCLK_DIV_Msk            (0xff000000UL)          /*!< GPIOD_DBCCLK_DIV (Bitfield-Mask: 0xff)         */
#define SYSCTRL_GPIOD_DBCCLK_DIV                SYSCTRL_GPIOD_DBCCLK_DIV_Msk
#define SYSCTRL_GPIOC_DBCCLK_DIV_Pos            (16UL)                  /*!< GPIOC_DBCCLK_DIV (Bit 16)                      */
#define SYSCTRL_GPIOC_DBCCLK_DIV_Msk            (0xff0000UL)            /*!< GPIOC_DBCCLK_DIV (Bitfield-Mask: 0xff)         */
#define SYSCTRL_GPIOC_DBCCLK_DIV                SYSCTRL_GPIOC_DBCCLK_DIV_Msk
#define SYSCTRL_GPIOB_DBCCLK_DIV_Pos            (8UL)                   /*!< GPIOB_DBCCLK_DIV (Bit 8)                       */
#define SYSCTRL_GPIOB_DBCCLK_DIV_Msk            (0xff00UL)              /*!< GPIOB_DBCCLK_DIV (Bitfield-Mask: 0xff)         */
#define SYSCTRL_GPIOB_DBCCLK_DIV                SYSCTRL_GPIOB_DBCCLK_DIV_Msk
#define SYSCTRL_GPIOA_DBCCLK_DIV_Pos            (0UL)                   /*!< GPIOA_DBCCLK_DIV (Bit 0)                       */
#define SYSCTRL_GPIOA_DBCCLK_DIV_Msk            (0xffUL)                /*!< GPIOA_DBCCLK_DIV (Bitfield-Mask: 0xff)         */
#define SYSCTRL_GPIOA_DBCCLK_DIV                SYSCTRL_GPIOA_DBCCLK_DIV_Msk

/*******************  Bit definition for APB0CCR register  ***************/
#define SYSCTRL_LSTIMER_BUSCLK_EN_Pos           (12UL)                  /*!< LSTIMER_BUSCLK_EN (Bit 12)                     */
#define SYSCTRL_LSTIMER_BUSCLK_EN_Msk           (0x1000UL)              /*!< LSTIMER_BUSCLK_EN (Bitfield-Mask: 0x01)        */
#define SYSCTRL_LSTIMER_BUSCLK_EN               SYSCTRL_LSTIMER_BUSCLK_EN_Msk
#define SYSCTRL_UART1_BUSCLK_EN_Pos             (5UL)                   /*!< UART1_BUSCLK_EN (Bit 5)                        */
#define SYSCTRL_UART1_BUSCLK_EN_Msk             (0x20UL)                /*!< UART1_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_UART1_BUSCLK_EN                 SYSCTRL_UART1_BUSCLK_EN_Msk
#define SYSCTRL_UART0_BUSCLK_EN_Pos             (4UL)                   /*!< UART0_BUSCLK_EN (Bit 4)                        */
#define SYSCTRL_UART0_BUSCLK_EN_Msk             (0x10UL)                /*!< UART0_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_UART0_BUSCLK_EN                 SYSCTRL_UART0_BUSCLK_EN_Msk
#define SYSCTRL_I2C1_BUSCLK_EN_Pos              (1UL)                   /*!< I2C1_BUSCLK_EN (Bit 1)                         */
#define SYSCTRL_I2C1_BUSCLK_EN_Msk              (0x2UL)                 /*!< I2C1_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_I2C1_BUSCLK_EN                  SYSCTRL_I2C1_BUSCLK_EN_Msk
#define SYSCTRL_I2C0_BUSCLK_EN_Pos              (0UL)                   /*!< I2C0_BUSCLK_EN (Bit 0)                         */
#define SYSCTRL_I2C0_BUSCLK_EN_Msk              (0x1UL)                 /*!< I2C0_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_I2C0_BUSCLK_EN                  SYSCTRL_I2C0_BUSCLK_EN_Msk

/*******************  Bit definition for APB1CCR register  ***************/
#define SYSCTRL_ECU_BUSCLK_EN_Pos               (14UL)                  /*!< ECU_BUSCLK_EN (Bit 14)                         */
#define SYSCTRL_ECU_BUSCLK_EN_Msk               (0x4000UL)              /*!< ECU_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_ECU_BUSCLK_EN                   SYSCTRL_ECU_BUSCLK_EN_Msk
#define SYSCTRL_IIR4_BUSCLK_EN_Pos              (12UL)                  /*!< IIR4_BUSCLK_EN (Bit 12)                        */
#define SYSCTRL_IIR4_BUSCLK_EN_Msk              (0x1000UL)              /*!< IIR4_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR4_BUSCLK_EN                  SYSCTRL_IIR4_BUSCLK_EN_Msk
#define SYSCTRL_IIR3_BUSCLK_EN_Pos              (11UL)                  /*!< IIR3_BUSCLK_EN (Bit 11)                        */
#define SYSCTRL_IIR3_BUSCLK_EN_Msk              (0x800UL)               /*!< IIR3_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR3_BUSCLK_EN                  SYSCTRL_IIR3_BUSCLK_EN_Msk
#define SYSCTRL_IIR2_BUSCLK_EN_Pos              (10UL)                  /*!< IIR2_BUSCLK_EN (Bit 10)                        */
#define SYSCTRL_IIR2_BUSCLK_EN_Msk              (0x400UL)               /*!< IIR2_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR2_BUSCLK_EN                  SYSCTRL_IIR2_BUSCLK_EN_Msk
#define SYSCTRL_IIR1_BUSCLK_EN_Pos              (9UL)                   /*!< IIR1_BUSCLK_EN (Bit 9)                         */
#define SYSCTRL_IIR1_BUSCLK_EN_Msk              (0x200UL)               /*!< IIR1_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR1_BUSCLK_EN                  SYSCTRL_IIR1_BUSCLK_EN_Msk
#define SYSCTRL_IIR0_BUSCLK_EN_Pos              (8UL)                   /*!< IIR0_BUSCLK_EN (Bit 8)                         */
#define SYSCTRL_IIR0_BUSCLK_EN_Msk              (0x100UL)               /*!< IIR0_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR0_BUSCLK_EN                  SYSCTRL_IIR0_BUSCLK_EN_Msk
#define SYSCTRL_DALI_BUSCLK_EN_Pos              (6UL)                   /*!< DALI_BUSCLK_EN (Bit 6)                         */
#define SYSCTRL_DALI_BUSCLK_EN_Msk              (0x40UL)                /*!< DALI_BUSCLK_EN (Bitfield-Mask: 0x40)           */
#define SYSCTRL_DALI_BUSCLK_EN                  SYSCTRL_DALI_BUSCLK_EN_Msk

/*******************  Bit definition for AHBCCR register  ***************/
#define SYSCTRL_RAM2_BUSCLK_EN_Pos              (19UL)                  /*!< RAM2_BUSCLK_EN (Bit 19)                        */
#define SYSCTRL_RAM2_BUSCLK_EN_Msk              (0x80000UL)             /*!< RAM2_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_RAM2_BUSCLK_EN                  SYSCTRL_RAM2_BUSCLK_EN_Msk
#define SYSCTRL_RAM1_BUSCLK_EN_Pos              (18UL)                  /*!< RAM1_BUSCLK_EN (Bit 18)                        */
#define SYSCTRL_RAM1_BUSCLK_EN_Msk              (0x40000UL)             /*!< RAM1_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_RAM1_BUSCLK_EN                  SYSCTRL_RAM1_BUSCLK_EN_Msk
#define SYSCTRL_RAM0_BUSCLK_EN_Pos              (17UL)                  /*!< RAM0_BUSCLK_EN (Bit 17)                        */
#define SYSCTRL_RAM0_BUSCLK_EN_Msk              (0x20000UL)             /*!< RAM0_BUSCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_RAM0_BUSCLK_EN                  SYSCTRL_RAM0_BUSCLK_EN_Msk
#define SYSCTRL_USB_BUSCLK_EN_Pos               (14UL)                  /*!< USB_BUSCLK_EN (Bit 14)                         */
#define SYSCTRL_USB_BUSCLK_EN_Msk               (0x4000UL)              /*!< USB_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_USB_BUSCLK_EN                   SYSCTRL_USB_BUSCLK_EN_Msk
#define SYSCTRL_DFLASH_BUSCLK_EN_Pos            (13UL)                  /*!< DFLASH_BUSCLK_EN (Bit 13)                      */
#define SYSCTRL_DFLASH_BUSCLK_EN_Msk            (0x2000UL)              /*!< DFLASH_BUSCLK_EN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_DFLASH_BUSCLK_EN                SYSCTRL_DFLASH_BUSCLK_EN_Msk
#define SYSCTRL_EFLASH_BUSCLK_EN_Pos            (12UL)                  /*!< EFLASH_BUSCLK_EN (Bit 12)                      */
#define SYSCTRL_EFLASH_BUSCLK_EN_Msk            (0x1000UL)              /*!< EFLASH_BUSCLK_EN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_EFLASH_BUSCLK_EN                SYSCTRL_EFLASH_BUSCLK_EN_Msk
#define SYSCTRL_HRPWM_BUSCLK_EN_Pos             (10UL)                  /*!< HRPWM_BUSCLK_EN (Bit 10)                       */
#define SYSCTRL_HRPWM_BUSCLK_EN_Msk             (0x400UL)               /*!< HRPWM_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_HRPWM_BUSCLK_EN                 SYSCTRL_HRPWM_BUSCLK_EN_Msk
#define SYSCTRL_ADC_BUSCLK_EN_Pos               (9UL)                   /*!< ADC_BUSCLK_EN (Bit 9)                          */
#define SYSCTRL_ADC_BUSCLK_EN_Msk               (0x200UL)               /*!< ADC_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_ADC_BUSCLK_EN                   SYSCTRL_ADC_BUSCLK_EN_Msk
#define SYSCTRL_DAC_BUSCLK_EN_Pos               (8UL)                   /*!< DAC_BUSCLK_EN (Bit 8)                          */
#define SYSCTRL_DAC_BUSCLK_EN_Msk               (0x100UL)               /*!< DAC_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_DAC_BUSCLK_EN                   SYSCTRL_DAC_BUSCLK_EN_Msk
#define SYSCTRL_CMP_BUSCLK_EN_Pos               (7UL)                   /*!< CMP_BUSCLK_EN (Bit 7)                          */
#define SYSCTRL_CMP_BUSCLK_EN_Msk               (0x80UL)                /*!< CMP_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_CMP_BUSCLK_EN                   SYSCTRL_CMP_BUSCLK_EN_Msk
#define SYSCTRL_GPIOD_BUSCLK_EN_Pos             (6UL)                   /*!< GPIOD_BUSCLK_EN (Bit 6)                        */
#define SYSCTRL_GPIOD_BUSCLK_EN_Msk             (0x40UL)                /*!< GPIOD_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_GPIOD_BUSCLK_EN                 SYSCTRL_GPIOD_BUSCLK_EN_Msk
#define SYSCTRL_GPIOC_BUSCLK_EN_Pos             (5UL)                   /*!< GPIOC_BUSCLK_EN (Bit 5)                        */
#define SYSCTRL_GPIOC_BUSCLK_EN_Msk             (0x20UL)                /*!< GPIOC_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_GPIOC_BUSCLK_EN                 SYSCTRL_GPIOC_BUSCLK_EN_Msk
#define SYSCTRL_GPIOB_BUSCLK_EN_Pos             (4UL)                   /*!< GPIOB_BUSCLK_EN (Bit 4)                        */
#define SYSCTRL_GPIOB_BUSCLK_EN_Msk             (0x10UL)                /*!< GPIOB_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_GPIOB_BUSCLK_EN                 SYSCTRL_GPIOB_BUSCLK_EN_Msk
#define SYSCTRL_GPIOA_BUSCLK_EN_Pos             (3UL)                   /*!< GPIOA_BUSCLK_EN (Bit 3)                        */
#define SYSCTRL_GPIOA_BUSCLK_EN_Msk             (0x8UL)                 /*!< GPIOA_BUSCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_GPIOA_BUSCLK_EN                 SYSCTRL_GPIOA_BUSCLK_EN_Msk
#define SYSCTRL_HSTIMER_BUSCLK_EN_Pos           (2UL)                   /*!< HSTIMER_BUSCLK_EN (Bit 2)                      */
#define SYSCTRL_HSTIMER_BUSCLK_EN_Msk           (0x4UL)                 /*!< HSTIMER_BUSCLK_EN (Bitfield-Mask: 0x01)        */
#define SYSCTRL_HSTIMER_BUSCLK_EN               SYSCTRL_HSTIMER_BUSCLK_EN_Msk
#define SYSCTRL_CAN_BUSCLK_EN_Pos               (1UL)                   /*!< CAN_BUSCLK_EN (Bit 1)                          */
#define SYSCTRL_CAN_BUSCLK_EN_Msk               (0x2UL)                 /*!< CAN_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_CAN_BUSCLK_EN                   SYSCTRL_CAN_BUSCLK_EN_Msk
#define SYSCTRL_DMA_BUSCLK_EN_Pos               (0UL)                   /*!< DMA_BUSCLK_EN (Bit 0)                          */
#define SYSCTRL_DMA_BUSCLK_EN_Msk               (0x1UL)                 /*!< DMA_BUSCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_DMA_BUSCLK_EN                   SYSCTRL_DMA_BUSCLK_EN_Msk

/*******************  Bit definition for FUNCCR register  ****************/
#define SYSCTRL_HRPWM_FUNCLK_EN_Pos             (11UL)                  /*!< HRPWM_FUNCLK_EN (Bit 11)                       */
#define SYSCTRL_HRPWM_FUNCLK_EN_Msk             (0x800UL)               /*!< HRPWM_FUNCLK_EN (Bitfield-Mask: 0x01)          */
#define SYSCTRL_HRPWM_FUNCLK_EN                 SYSCTRL_HRPWM_FUNCLK_EN_Msk
#define SYSCTRL_ADC_FUNCLK_EN_Pos               (10UL)                  /*!< ADC_FUNCLK_EN (Bit 10)                         */
#define SYSCTRL_ADC_FUNCLK_EN_Msk               (0x400UL)               /*!< ADC_FUNCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_ADC_FUNCLK_EN                   SYSCTRL_ADC_FUNCLK_EN_Msk
#define SYSCTRL_CAN_FUNCLK_EN_Pos               (9UL)                   /*!< CAN_FUNCLK_EN (Bit 9)                          */
#define SYSCTRL_CAN_FUNCLK_EN_Msk               (0x200UL)               /*!< CAN_FUNCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_CAN_FUNCLK_EN                   SYSCTRL_CAN_FUNCLK_EN_Msk
#define SYSCTRL_ECU_FUNCLK_EN_Pos               (8UL)                   /*!< ECU_FUNCLK_EN (Bit 8)                          */
#define SYSCTRL_ECU_FUNCLK_EN_Msk               (0x100UL)               /*!< ECU_FUNCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_ECU_FUNCLK_EN                   SYSCTRL_ECU_FUNCLK_EN_Msk
#define SYSCTRL_IIR4_FUNCLK_EN_Pos              (7UL)                   /*!< IIR4_FUNCLK_EN (Bit 7)                         */
#define SYSCTRL_IIR4_FUNCLK_EN_Msk              (0x80UL)                /*!< IIR4_FUNCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR4_FUNCLK_EN                  SYSCTRL_IIR4_FUNCLK_EN_Msk
#define SYSCTRL_IIR3_FUNCLK_EN_Pos              (6UL)                   /*!< IIR3_FUNCLK_EN (Bit 6)                         */
#define SYSCTRL_IIR3_FUNCLK_EN_Msk              (0x40UL)                /*!< IIR3_FUNCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR3_FUNCLK_EN                  SYSCTRL_IIR3_FUNCLK_EN_Msk
#define SYSCTRL_IIR2_FUNCLK_EN_Pos              (5UL)                   /*!< IIR2_FUNCLK_EN (Bit 5)                         */
#define SYSCTRL_IIR2_FUNCLK_EN_Msk              (0x20UL)                /*!< IIR2_FUNCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR2_FUNCLK_EN                  SYSCTRL_IIR2_FUNCLK_EN_Msk
#define SYSCTRL_IIR1_FUNCLK_EN_Pos              (4UL)                   /*!< IIR1_FUNCLK_EN (Bit 4)                         */
#define SYSCTRL_IIR1_FUNCLK_EN_Msk              (0x10UL)                /*!< IIR1_FUNCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR1_FUNCLK_EN                  SYSCTRL_IIR1_FUNCLK_EN_Msk
#define SYSCTRL_IIR0_FUNCLK_EN_Pos              (3UL)                   /*!< IIR0_FUNCLK_EN (Bit 3)                         */
#define SYSCTRL_IIR0_FUNCLK_EN_Msk              (0x8UL)                 /*!< IIR0_FUNCLK_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_IIR0_FUNCLK_EN                  SYSCTRL_IIR0_FUNCLK_EN_Msk
#define SYSCTRL_USB_FUNCLK_EN_Pos               (2UL)                   /*!< USB_FUNCLK_EN (Bit 2)                          */
#define SYSCTRL_USB_FUNCLK_EN_Msk               (0x4UL)                 /*!< USB_FUNCLK_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_USB_FUNCLK_EN                   SYSCTRL_USB_FUNCLK_EN_Msk
#define SYSCTRL_DFLASH_MEMCLK_EN_Pos            (1UL)                   /*!< DFLASH_MEMCLK_EN (Bit 1)                       */
#define SYSCTRL_DFLASH_MEMCLK_EN_Msk            (0x2UL)                 /*!< DFLASH_MEMCLK_EN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_DFLASH_MEMCLK_EN                SYSCTRL_DFLASH_MEMCLK_EN_Msk
#define SYSCTRL_EFLASH_MEMCLK_EN_Pos            (0UL)                   /*!< EFLASH_MEMCLK_EN (Bit 0)                       */
#define SYSCTRL_EFLASH_MEMCLK_EN_Msk            (0x1UL)                 /*!< EFLASH_MEMCLK_EN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_EFLASH_MEMCLK_EN                SYSCTRL_EFLASH_MEMCLK_EN_Msk

/*******************  Bit definition for SYSRCR register  ***************/
#define SYSCTRL_GPIOD_DBC_SOFTRST_Pos           (11UL)                  /*!< GPIOD_DBC_SOFTRST (Bit 11)                     */
#define SYSCTRL_GPIOD_DBC_SOFTRST_Msk           (0x800UL)               /*!< GPIOD_DBC_SOFTRST (Bitfield-Mask: 0x01)        */
#define SYSCTRL_GPIOD_DBC_SOFTRST               SYSCTRL_GPIOD_DBC_SOFTRST_Msk
#define SYSCTRL_GPIOC_DBC_SOFTRST_Pos           (10UL)                  /*!< GPIOC_DBC_SOFTRST (Bit 10)                     */
#define SYSCTRL_GPIOC_DBC_SOFTRST_Msk           (0x400UL)               /*!< GPIOC_DBC_SOFTRST (Bitfield-Mask: 0x01)        */
#define SYSCTRL_GPIOC_DBC_SOFTRST               SYSCTRL_GPIOC_DBC_SOFTRST_Msk
#define SYSCTRL_GPIOB_DBC_SOFTRST_Pos           (9UL)                   /*!< GPIOB_DBC_SOFTRST (Bit 9)                      */
#define SYSCTRL_GPIOB_DBC_SOFTRST_Msk           (0x200UL)               /*!< GPIOB_DBC_SOFTRST (Bitfield-Mask: 0x01)        */
#define SYSCTRL_GPIOB_DBC_SOFTRST               SYSCTRL_GPIOB_DBC_SOFTRST_Msk
#define SYSCTRL_GPIOA_DBC_SOFTRST_Pos           (8UL)                   /*!< GPIOA_DBC_SOFTRST (Bit 8)                      */
#define SYSCTRL_GPIOA_DBC_SOFTRST_Msk           (0x100UL)               /*!< GPIOA_DBC_SOFTRST (Bitfield-Mask: 0x01)        */
#define SYSCTRL_GPIOA_DBC_SOFTRST               SYSCTRL_GPIOA_DBC_SOFTRST_Msk
#define SYSCTRL_APB1BUS_SOFTRST_Pos             (3UL)                   /*!< APB1BUS_SOFTRST (Bit 3)                        */
#define SYSCTRL_APB1BUS_SOFTRST_Msk             (0x8UL)                 /*!< APB1BUS_SOFTRST (Bitfield-Mask: 0x01)          */
#define SYSCTRL_APB1BUS_SOFTRST                 SYSCTRL_APB1BUS_SOFTRST_Msk
#define SYSCTRL_APB0BUS_SOFTRST_Pos             (2UL)                   /*!< APB0BUS_SOFTRST (Bit 2)                        */
#define SYSCTRL_APB0BUS_SOFTRST_Msk             (0x4UL)                 /*!< APB0BUS_SOFTRST (Bitfield-Mask: 0x01)          */
#define SYSCTRL_APB0BUS_SOFTRST                 SYSCTRL_APB0BUS_SOFTRST_Msk
#define SYSCTRL_AHBBUS_SOFTRST_Pos              (0UL)                   /*!< AHBBUS_SOFTRST (Bit 0)                         */
#define SYSCTRL_AHBBUS_SOFTRST_Msk              (0x1UL)                 /*!< AHBBUS_SOFTRST (Bitfield-Mask: 0x01)           */
#define SYSCTRL_AHBBUS_SOFTRST                  SYSCTRL_AHBBUS_SOFTRST_Msk

/*********************  Bit definition for APB0RCR register  *****************/
#define SYSCTRL_LSTIMER_SOFTRST_Pos             (12UL)                  /*!< LSTIMER_SOFTRST (Bit 12)                       */
#define SYSCTRL_LSTIMER_SOFTRST_Msk             (0x1000UL)              /*!< LSTIMER_SOFTRST (Bitfield-Mask: 0x01)          */
#define SYSCTRL_LSTIMER_SOFTRST                 SYSCTRL_LSTIMER_SOFTRST_Msk
#define SYSCTRL_UART1_SOFTRST_Pos               (5UL)                   /*!< UART1_SOFTRST (Bit 5)                          */
#define SYSCTRL_UART1_SOFTRST_Msk               (0x20UL)                /*!< UART1_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_UART1_SOFTRST                   SYSCTRL_UART1_SOFTRST_Msk
#define SYSCTRL_UART0_SOFTRST_Pos               (4UL)                   /*!< UART0_SOFTRST (Bit 4)                          */
#define SYSCTRL_UART0_SOFTRST_Msk               (0x10UL)                /*!< UART0_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_UART0_SOFTRST                   SYSCTRL_UART0_SOFTRST_Msk
#define SYSCTRL_I2C1_SOFTRST_Pos                (1UL)                   /*!< I2C1_SOFTRST (Bit 1)                           */
#define SYSCTRL_I2C1_SOFTRST_Msk                (0x2UL)                 /*!< I2C1_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_I2C1_SOFTRST                    SYSCTRL_I2C1_SOFTRST_Msk
#define SYSCTRL_I2C0_SOFTRST_Pos                (0UL)                   /*!< I2C0_SOFTRST (Bit 0)                           */
#define SYSCTRL_I2C0_SOFTRST_Msk                (0x1UL)                 /*!< I2C0_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_I2C0_SOFTRST                    SYSCTRL_I2C0_SOFTRST_Msk

/*********************  Bit definition for APB1RCR register  *****************/
#define SYSCTRL_ECU_SOFTRST_Pos                 (18UL)                  /*!< ECU_SOFTRST (Bit 18)                           */
#define SYSCTRL_ECU_SOFTRST_Msk                 (0x40000UL)             /*!< ECU_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_ECU_SOFTRST                     SYSCTRL_ECU_SOFTRST_Msk
#define SYSCTRL_IIR4_SOFTRST_Pos                (16UL)                  /*!< IIR4_SOFTRST (Bit 16)                          */
#define SYSCTRL_IIR4_SOFTRST_Msk                (0x10000UL)             /*!< IIR4_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_IIR4_SOFTRST                    SYSCTRL_IIR4_SOFTRST_Msk
#define SYSCTRL_IIR3_SOFTRST_Pos                (15UL)                  /*!< IIR3_SOFTRST (Bit 15)                          */
#define SYSCTRL_IIR3_SOFTRST_Msk                (0x8000UL)              /*!< IIR3_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_IIR3_SOFTRST                    SYSCTRL_IIR3_SOFTRST_Msk
#define SYSCTRL_IIR2_SOFTRST_Pos                (14UL)                  /*!< IIR2_SOFTRST (Bit 14)                          */
#define SYSCTRL_IIR2_SOFTRST_Msk                (0x4000UL)              /*!< IIR2_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_IIR2_SOFTRST                    SYSCTRL_IIR2_SOFTRST_Msk
#define SYSCTRL_IIR1_SOFTRST_Pos                (13UL)                  /*!< IIR1_SOFTRST (Bit 13)                          */
#define SYSCTRL_IIR1_SOFTRST_Msk                (0x2000UL)              /*!< IIR1_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_IIR1_SOFTRST                    SYSCTRL_IIR1_SOFTRST_Msk
#define SYSCTRL_IIR0_SOFTRST_Pos                (12UL)                  /*!< IIR0_SOFTRST (Bit 12)                          */
#define SYSCTRL_IIR0_SOFTRST_Msk                (0x1000UL)              /*!< IIR0_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_IIR0_SOFTRST                    SYSCTRL_IIR0_SOFTRST_Msk
#define SYSCTRL_FPLL2_SOFTRST_Pos               (11UL)                  /*!< FPLL2_SOFTRST (Bit 11)                         */
#define SYSCTRL_FPLL2_SOFTRST_Msk               (0x800UL)               /*!< FPLL2_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_FPLL2_SOFTRST                   SYSCTRL_FPLL2_SOFTRST_Msk
#define SYSCTRL_FPLL1_SOFTRST_Pos               (10UL)                  /*!< FPLL1_SOFTRST (Bit 10)                         */
#define SYSCTRL_FPLL1_SOFTRST_Msk               (0x400UL)               /*!< FPLL1_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_FPLL1_SOFTRST                   SYSCTRL_FPLL1_SOFTRST_Msk
#define SYSCTRL_FPLL0_SOFTRST_Pos               (9UL)                   /*!< FPLL0_SOFTRST (Bit 9)                          */
#define SYSCTRL_FPLL0_SOFTRST_Msk               (0x200UL)               /*!< FPLL0_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_FPLL0_SOFTRST                   SYSCTRL_FPLL0_SOFTRST_Msk
#define SYSCTRL_DALI_SOFTRST_Pos                (6UL)                   /*!< IIR0_SOFTRST (Bit 6)                           */
#define SYSCTRL_DALI_SOFTRST_Msk                (0x40UL)                /*!< IIR0_SOFTRST (Bitfield-Mask: 0x01)             */
#define SYSCTRL_DALI_SOFTRST                    SYSCTRL_DALI_SOFTRST_Msk


/*********************  Bit definition for AHBRCR register  *****************/
#define SYSCTRL_DFLASH_SOFTRST_Pos              (13UL)                  /*!< DFLASH_SOFTRST (Bit 13)                        */
#define SYSCTRL_DFLASH_SOFTRST_Msk              (0x2000UL)              /*!< DFLASH_SOFTRST (Bitfield-Mask: 0x01)           */
#define SYSCTRL_DFLASH_SOFTRST                  SYSCTRL_DFLASH_SOFTRST_Msk
#define SYSCTRL_HSTIMER_SOFTRST_Pos             (12UL)                  /*!< HSTIMER_SOFTRST (Bit 12)                       */
#define SYSCTRL_HSTIMER_SOFTRST_Msk             (0x1000UL)              /*!< HSTIMER_SOFTRST (Bitfield-Mask: 0x01)          */
#define SYSCTRL_HSTIMER_SOFTRST                 SYSCTRL_HSTIMER_SOFTRST_Msk
#define SYSCTRL_GPIOD_SOFTRST_Pos               (11UL)                  /*!< GPIOD_SOFTRST (Bit 11)                         */
#define SYSCTRL_GPIOD_SOFTRST_Msk               (0x800UL)               /*!< GPIOD_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_GPIOD_SOFTRST                   SYSCTRL_GPIOD_SOFTRST_Msk
#define SYSCTRL_GPIOC_SOFTRST_Pos               (10UL)                  /*!< GPIOC_SOFTRST (Bit 10)                         */
#define SYSCTRL_GPIOC_SOFTRST_Msk               (0x400UL)               /*!< GPIOC_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_GPIOC_SOFTRST                   SYSCTRL_GPIOC_SOFTRST_Msk
#define SYSCTRL_GPIOB_SOFTRST_Pos               (9UL)                   /*!< GPIOB_SOFTRST (Bit 9)                          */
#define SYSCTRL_GPIOB_SOFTRST_Msk               (0x200UL)               /*!< GPIOB_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_GPIOB_SOFTRST                   SYSCTRL_GPIOB_SOFTRST_Msk
#define SYSCTRL_GPIOA_SOFTRST_Pos               (8UL)                   /*!< GPIOA_SOFTRST (Bit 8)                          */
#define SYSCTRL_GPIOA_SOFTRST_Msk               (0x100UL)               /*!< GPIOA_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_GPIOA_SOFTRST                   SYSCTRL_GPIOA_SOFTRST_Msk
#define SYSCTRL_USB_SOFTRST_Pos                 (7UL)                   /*!< USB_SOFTRST (Bit 7)                            */
#define SYSCTRL_USB_SOFTRST_Msk                 (0x80UL)                /*!< USB_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_USB_SOFTRST                     SYSCTRL_USB_SOFTRST_Msk
#define SYSCTRL_HRPWM_SOFTRST_Pos               (6UL)                   /*!< HRPWM_SOFTRST (Bit 6)                          */
#define SYSCTRL_HRPWM_SOFTRST_Msk               (0x40UL)                /*!< HRPWM_SOFTRST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_HRPWM_SOFTRST                   SYSCTRL_HRPWM_SOFTRST_Msk
#define SYSCTRL_DAC_SOFTRST_Pos                 (5UL)                   /*!< DAC_SOFTRST (Bit 5)                            */
#define SYSCTRL_DAC_SOFTRST_Msk                 (0x20UL)                /*!< DAC_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_DAC_SOFTRST                     SYSCTRL_DAC_SOFTRST_Msk
#define SYSCTRL_ADC_SOFTRST_Pos                 (4UL)                   /*!< ADC_SOFTRST (Bit 4)                            */
#define SYSCTRL_ADC_SOFTRST_Msk                 (0x10UL)                /*!< ADC_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_ADC_SOFTRST                     SYSCTRL_ADC_SOFTRST_Msk
#define SYSCTRL_CMP_SOFTRST_Pos                 (3UL)                   /*!< CMP_SOFTRST (Bit 3)                            */
#define SYSCTRL_CMP_SOFTRST_Msk                 (0x8UL)                 /*!< CMP_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_CMP_SOFTRST                     SYSCTRL_CMP_SOFTRST_Msk
#define SYSCTRL_EFLASH_SOFTRST_Pos              (2UL)                   /*!< EFLASH_SOFTRST (Bit 2)                         */
#define SYSCTRL_EFLASH_SOFTRST_Msk              (0x4UL)                 /*!< EFLASH_SOFTRST (Bitfield-Mask: 0x01)           */
#define SYSCTRL_EFLASH_SOFTRST                  SYSCTRL_EFLASH_SOFTRST_Msk
#define SYSCTRL_CAN_SOFTRST_Pos                 (1UL)                   /*!< CAN_SOFTRST (Bit 1)                            */
#define SYSCTRL_CAN_SOFTRST_Msk                 (0x2UL)                 /*!< CAN_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_CAN_SOFTRST                     SYSCTRL_CAN_SOFTRST_Msk
#define SYSCTRL_DMA_SOFTRST_Pos                 (0UL)                   /*!< DMA_SOFTRST (Bit 0)                            */
#define SYSCTRL_DMA_SOFTRST_Msk                 (0x1UL)                 /*!< DMA_SOFTRST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_DMA_SOFTRST                     SYSCTRL_DMA_SOFTRST_Msk

/*********************  Bit definition for XOSCCR register  ****************/
#define SYSCTRL_RC8M_EN_Pos                     (20UL)                  /*!< RC8M_EN (Bit 20)                               */
#define SYSCTRL_RC8M_EN_Msk                     (0x100000UL)            /*!< RC8M_EN (Bitfield-Mask: 0x01)                  */
#define SYSCTRL_RC8M_EN                         SYSCTRL_RC8M_EN_Msk
#define SYSCTRL_XOSCLOSS_IRQEN_Pos              (16UL)                  /*!< XOSCLOSS_IRQEN (Bit 16)                        */
#define SYSCTRL_XOSCLOSS_IRQEN_Msk              (0x10000UL)             /*!< XOSCLOSS_IRQEN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_XOSCLOSS_IRQEN                  SYSCTRL_XOSCLOSS_IRQEN_Msk
#define SYSCTRL_XOSC_HYEN_Pos                   (15UL)                  /*!< XOSC_HYEN (Bit 15)                             */
#define SYSCTRL_XOSC_HYEN_Msk                   (0x8000UL)              /*!< XOSC_HYEN (Bitfield-Mask: 0x01)                */
#define SYSCTRL_XOSC_HYEN                       SYSCTRL_XOSC_HYEN_Msk
#define SYSCTRL_XOSC_DR_Pos                     (12UL)                  /*!< XOSC_DR (Bit 12)                               */
#define SYSCTRL_XOSC_DR_Msk                     (0x7000UL)              /*!< XOSC_DR (Bitfield-Mask: 0x07)                  */
#define SYSCTRL_XOSC_DR                         SYSCTRL_XOSC_DR_Msk
#define SYSCTRL_XOSC_DR_250uA                   (0x0UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_375uA                   (0x1UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_500uA                   (0x2UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_625uA                   (0x3UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_750uA                   (0x4UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_875uA                   (0x5UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_1000uA                  (0x6UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_DR_1125uA                  (0x7UL << SYSCTRL_XOSC_DR_Pos)
#define SYSCTRL_XOSC_CTO_Pos                    (8UL)                   /*!< XOSC_CTO (Bit 8)                               */
#define SYSCTRL_XOSC_CTO_Msk                    (0xf00UL)               /*!< XOSC_CTO (Bitfield-Mask: 0x0f)                 */
#define SYSCTRL_XOSC_CTO                        SYSCTRL_XOSC_CTO_Msk
#define SYSCTRL_XOSC_CTI_Pos                    (4UL)                   /*!< XOSC_CTI (Bit 4)                               */
#define SYSCTRL_XOSC_CTI_Msk                    (0xf0UL)                /*!< XOSC_CTI (Bitfield-Mask: 0x0f)                 */
#define SYSCTRL_XOSC_CTI                        SYSCTRL_XOSC_CTI_Msk
#define SYSCTRL_XOSC_CS_Pos                     (1UL)                   /*!< XOSC_CS (Bit 1)                                */
#define SYSCTRL_XOSC_CS_Msk                     (0xeUL)                 /*!< XOSC_CS (Bitfield-Mask: 0x07)                  */
#define SYSCTRL_XOSC_CS                         SYSCTRL_XOSC_CS_Msk
#define SYSCTRL_XOSC_CS_0pF                     (0x0UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_2Point5pF               (0x1UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_5pF                     (0x2UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_7Point5pF               (0x3UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_10pF                    (0x4UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_12Point5pF              (0x5UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_15pF                    (0x6UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_CS_17Point5pF              (0x7UL << SYSCTRL_XOSC_CS_Pos)
#define SYSCTRL_XOSC_EN_Pos                     (0UL)                   /*!< XOSC_EN (Bit 0)                                */
#define SYSCTRL_XOSC_EN_Msk                     (0x1UL)                 /*!< XOSC_EN (Bitfield-Mask: 0x01)                  */
#define SYSCTRL_XOSC_EN                         SYSCTRL_XOSC_EN_Msk

/*******************  Bit definition for XASWCR register  **************/
#define SYSCTRL_XOSC_LOSS_PENDING_Pos           (28UL)                  /*!< XOSC_LOSS_PENDING (Bit 28)                     */
#define SYSCTRL_XOSC_LOSS_PENDING_Msk           (0x10000000UL)          /*!< XOSC_LOSS_PENDING (Bitfield-Mask: 0x01)        */
#define SYSCTRL_XOSC_LOSS_PENDING               SYSCTRL_XOSC_LOSS_PENDING_Msk
#define SYSCTRL_XOSC_SYSCLK_SWEN_Pos            (26UL)                  /*!< XOSC_SYSCLK_SWEN (Bit 26)                      */
#define SYSCTRL_XOSC_SYSCLK_SWEN_Msk            (0x4000000UL)           /*!< XOSC_SYSCLK_SWEN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_XOSC_SYSCLK_SWEN                SYSCTRL_XOSC_SYSCLK_SWEN_Msk
#define SYSCTRL_XOSC_REFCLK_SWEN_Pos            (25UL)                  /*!< XOSC_REFCLK_SWEN (Bit 25)                      */
#define SYSCTRL_XOSC_REFCLK_SWEN_Msk            (0x2000000UL)           /*!< XOSC_REFCLK_SWEN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_XOSC_REFCLK_SWEN                SYSCTRL_XOSC_REFCLK_SWEN_Msk
#define SYSCTRL_XOSC_MNTEN_Pos                  (24UL)                  /*!< XOSC_MNTEN (Bit 24)                            */
#define SYSCTRL_XOSC_MNTEN_Msk                  (0x1000000UL)           /*!< XOSC_MNTEN (Bitfield-Mask: 0x01)               */
#define SYSCTRL_XOSC_MNTEN                      SYSCTRL_XOSC_MNTEN_Msk
#define SYSCTRL_XOSC_WIDTH_Pos                  (20UL)                  /*!< XOSC_WIDTH (Bit 20)                            */
#define SYSCTRL_XOSC_WIDTH_Msk                  (0xf00000UL)            /*!< XOSC_WIDTH (Bitfield-Mask: 0x0f)               */
#define SYSCTRL_XOSC_WIDTH                      SYSCTRL_XOSC_WIDTH_Msk
#define SYSCTRL_XOSC_HIGH_LIMIT_Pos             (10UL)                  /*!< XOSC_HIGH_LIMIT (Bit 10)                       */
#define SYSCTRL_XOSC_HIGH_LIMIT_Msk             (0xffc00UL)             /*!< XOSC_HIGH_LIMIT (Bitfield-Mask: 0x3ff)         */
#define SYSCTRL_XOSC_HIGH_LIMIT                 SYSCTRL_XOSC_HIGH_LIMIT_Msk
#define SYSCTRL_XOSC_LOW_LIMIT_Pos              (0UL)                   /*!< XOSC_LOW_LIMIT (Bit 0)                         */
#define SYSCTRL_XOSC_LOW_LIMIT_Msk              (0x3ffUL)               /*!< XOSC_LOW_LIMIT (Bitfield-Mask: 0x3ff)          */
#define SYSCTRL_XOSC_LOW_LIMIT                  SYSCTRL_XOSC_LOW_LIMIT_Msk

/*******************  Bit definition for BUFCR register  **************/
#define SYSCTRL_ADCBUF_SRCSEL_Pos               (10UL)                  /*!< ADCBUF_SRCSEL (Bit 10)                         */
#define SYSCTRL_ADCBUF_SRCSEL_Msk               (0x1c00UL)              /*!< ADCBUF_SRCSEL (Bitfield-Mask: 0x07)            */
#define SYSCTRL_ADCBUF_SRCSEL                   SYSCTRL_ADCBUF_SRCSEL_Msk
#define SYSCTRL_ADCBUF_SRCSEL_TSEN              (0x0UL << SYSCTRL_ADCBUF_SRCSEL_Pos)
#define SYSCTRL_ADCBUF_SRCSEL_PLL0_CPOUT        (0x1UL << SYSCTRL_ADCBUF_SRCSEL_Pos)
#define SYSCTRL_ADCBUF_SRCSEL_PLL1_CPOUT        (0x2UL << SYSCTRL_ADCBUF_SRCSEL_Pos)
#define SYSCTRL_ADCBUF_SRCSEL_PLL2_CPOUT        (0x3UL << SYSCTRL_ADCBUF_SRCSEL_Pos)
#define SYSCTRL_ADCBUF_SRCSEL_ADC1_IN10         (0x4UL << SYSCTRL_ADCBUF_SRCSEL_Pos)
#define SYSCTRL_ADCBUF_BYPASS_Pos               (9UL)                   /*!< ADCBUF_BYPASS (Bit 9)                          */
#define SYSCTRL_ADCBUF_BYPASS_Msk               (0x200UL)               /*!< ADCBUF_BYPASS (Bitfield-Mask: 0x01)            */
#define SYSCTRL_ADCBUF_BYPASS                   SYSCTRL_ADCBUF_BYPASS_Msk
#define SYSCTRL_ADCBUF_EN_Pos                   (8UL)                   /*!< ADCBUF_EN (Bit 8)                              */
#define SYSCTRL_ADCBUF_EN_Msk                   (0x100UL)               /*!< ADCBUF_EN (Bitfield-Mask: 0x01)                */
#define SYSCTRL_ADCBUF_EN                       SYSCTRL_ADCBUF_EN_Msk
#define SYSCTRL_TOUT_SRC_Pos                    (0UL)                   /*!< TOUT_SRC (Bit 0)                               */
#define SYSCTRL_TOUT_SRC_Msk                    (0x1fUL)                /*!< TOUT_SRC (Bitfield-Mask: 0x1f)                 */
#define SYSCTRL_TOUT_SRC                        SYSCTRL_TOUT_SRC_Msk
#define SYSCTRL_TOUT_SRC_AVSS                   (0x1UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_TSENSOR                (0x2UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_AVDD                   (0x3UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_VDDRC                  (0x4UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_DLL_CPOUT              (0x5UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_DLL_CKO                (0x6UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLA_ICO               (0x8UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLA_VFBL              (0x9UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLA_CPOUT             (0xaUL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLB_ICO               (0xcUL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLB_VFBL              (0xdUL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLB_CPOUT             (0xeUL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLC_ICO               (0x10UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLC_VFBL              (0x11UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_PLLC_CPOUT             (0x12UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_VRNB                   (0x18UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_V150B                  (0x19UL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_VCMB                   (0x1aUL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_VRPB                   (0x1bUL << SYSCTRL_TOUT_SRC_Pos)
#define SYSCTRL_TOUT_SRC_VRNA                   (0x1cUL << SYSCTRL_TOUT_SRC_Pos)

/*******************  Bit definition for SYSCCR register  ***************/
#define SYSCTRL_ADCCTRL_FANOUT_EN_Pos           (26UL)                  /*!< ADCCTRL_FANOUT_EN (Bit 26)                     */
#define SYSCTRL_ADCCTRL_FANOUT_EN_Msk           (0xc000000UL)           /*!< ADCCTRL_FANOUT_EN (Bitfield-Mask: 0x03)        */
#define SYSCTRL_ADCCTRL_FANOUT_EN               SYSCTRL_ADCCTRL_FANOUT_EN_Msk
#define SYSCTRL_ADCDATA_FANOUT_SRC_Pos          (25UL)                  /*!< ADCDATA_FANOUT_SRC (Bit 25)                    */
#define SYSCTRL_ADCDATA_FANOUT_SRC_Msk          (0x2000000UL)           /*!< ADCDATA_FANOUT_SRC (Bitfield-Mask: 0x01)       */
#define SYSCTRL_ADCDATA_FANOUT_SRC              SYSCTRL_ADCDATA_FANOUT_SRC_Msk
#define SYSCTRL_ADCDATA_FANOUT_EN_Pos           (24UL)                  /*!< ADCDATA_FANOUT_EN (Bit 24)                     */
#define SYSCTRL_ADCDATA_FANOUT_EN_Msk           (0x1000000UL)           /*!< ADCDATA_FANOUT_EN (Bitfield-Mask: 0x01)        */
#define SYSCTRL_ADCDATA_FANOUT_EN               SYSCTRL_ADCDATA_FANOUT_EN_Msk
#define SYSCTRL_I2C1_SMBUS_OE_Pos               (21UL)                  /*!< I2C1_SMBUS_OE (Bit 21)                         */
#define SYSCTRL_I2C1_SMBUS_OE_Msk               (0x200000UL)            /*!< I2C1_SMBUS_OE (Bitfield-Mask: 0x01)            */
#define SYSCTRL_I2C1_SMBUS_OE                   SYSCTRL_I2C1_SMBUS_OE_Msk
#define SYSCTRL_I2C0_SMBUS_OE_Pos               (20UL)                  /*!< I2C0_SMBUS_OE (Bit 20)                         */
#define SYSCTRL_I2C0_SMBUS_OE_Msk               (0x100000UL)            /*!< I2C0_SMBUS_OE (Bitfield-Mask: 0x01)            */
#define SYSCTRL_I2C0_SMBUS_OE                   SYSCTRL_I2C0_SMBUS_OE_Msk
#define SYSCTRL_JTAG_BUGFIX_EN_Pos              (18UL)                  /*!< JTAG_BUGFIX_EN (Bit 18)                        */
#define SYSCTRL_JTAG_BUGFIX_EN_Msk              (0x40000UL)             /*!< JTAG_BUGFIX_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_JTAG_BUGFIX_EN                  SYSCTRL_JTAG_BUGFIX_EN_Msk
#define SYSCTRL_CANFD_EN_Pos                    (17UL)                  /*!< CANFD_EN (Bit 17)                              */
#define SYSCTRL_CANFD_EN_Msk                    (0x20000UL)             /*!< CANFD_EN (Bitfield-Mask: 0x01)                 */
#define SYSCTRL_CANFD_EN                        SYSCTRL_CANFD_EN_Msk
#define SYSCTRL_CPU_LOCKUPRST_EN_Pos            (16UL)                  /*!< CPU_LOCKUPRST_EN (Bit 16)                      */
#define SYSCTRL_CPU_LOCKUPRST_EN_Msk            (0x10000UL)             /*!< CPU_LOCKUPRST_EN (Bitfield-Mask: 0x01)         */
#define SYSCTRL_CPU_LOCKUPRST_EN                SYSCTRL_CPU_LOCKUPRST_EN_Msk
#define SYSCTRL_WWDG_DEBUG_EN_Pos               (15UL)                  /*!< WWDG_DEBUG_EN (Bit 15)                         */
#define SYSCTRL_WWDG_DEBUG_EN_Msk               (0x8000UL)              /*!< WWDG_DEBUG_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_WWDG_DEBUG_EN                   SYSCTRL_WWDG_DEBUG_EN_Msk
#define SYSCTRL_WWDG_TIMEOUTRST_EN_Pos          (14UL)                  /*!< WWDG_TIMEOUTRST_EN (Bit 14)                    */
#define SYSCTRL_WWDG_TIMEOUTRST_EN_Msk          (0x4000UL)              /*!< WWDG_TIMEOUTRST_EN (Bitfield-Mask: 0x01)       */
#define SYSCTRL_WWDG_TIMEOUTRST_EN              SYSCTRL_WWDG_TIMEOUTRST_EN_Msk
#define SYSCTRL_IWDG_DEBUG_EN_Pos               (13UL)                  /*!< IWDG_DEBUG_EN (Bit 13)                         */
#define SYSCTRL_IWDG_DEBUG_EN_Msk               (0x2000UL)              /*!< IWDG_DEBUG_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_IWDG_DEBUG_EN                   SYSCTRL_IWDG_DEBUG_EN_Msk
#define SYSCTRL_IWDG_TIMEOUTRST_EN_Pos          (12UL)                  /*!< IWDG_TIMEOUTRST_EN (Bit 12)                    */
#define SYSCTRL_IWDG_TIMEOUTRST_EN_Msk          (0x1000UL)              /*!< IWDG_TIMEOUTRST_EN (Bitfield-Mask: 0x01)       */
#define SYSCTRL_IWDG_TIMEOUTRST_EN              SYSCTRL_IWDG_TIMEOUTRST_EN_Msk
#define SYSCTRL_HSTMR_DEBUG_EN_Pos              (10UL)                  /*!< HSTMR_DEBUG_EN (Bit 10)                        */
#define SYSCTRL_HSTMR_DEBUG_EN_Msk              (0x400UL)               /*!< HSTMR_DEBUG_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_HSTMR_DEBUG_EN                  SYSCTRL_HSTMR_DEBUG_EN_Msk
#define SYSCTRL_LSTMR_DEBUG_EN_Pos              (9UL)                   /*!< LSTMR_DEBUG_EN (Bit 9)                         */
#define SYSCTRL_LSTMR_DEBUG_EN_Msk              (0x200UL)               /*!< LSTMR_DEBUG_EN (Bitfield-Mask: 0x01)           */
#define SYSCTRL_LSTMR_DEBUG_EN                  SYSCTRL_LSTMR_DEBUG_EN_Msk
#define SYSCTRL_GPIO_NMIEN_Pos                  (8UL)                   /*!< GPIO_NMIEN (Bit 8)                             */
#define SYSCTRL_GPIO_NMIEN_Msk                  (0x100UL)               /*!< GPIO_NMIEN (Bitfield-Mask: 0x01)               */
#define SYSCTRL_GPIO_NMIEN                      SYSCTRL_GPIO_NMIEN_Msk
#define SYSCTRL_CLK_TEST_SRC_Pos                (4UL)                   /*!< CLK_TEST_SRC (Bit 4)                           */
#define SYSCTRL_CLK_TEST_SRC_Msk                (0xf0UL)                /*!< CLK_TEST_SRC (Bitfield-Mask: 0x0f)             */
#define SYSCTRL_CLK_TEST_SRC                    SYSCTRL_CLK_TEST_SRC_Msk
#define SYSCTRL_CLK_TEST_SRC_RC32K              (0x0UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_RC8M               (0x1UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_XOSC               (0x2UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_PLL0DivClk         (0x4UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_PLL0Div16          (0x5UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_PLL1DivClk         (0x8UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_PLL1Div16          (0x9UL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_PLL2DivClk         (0xcUL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_TEST_SRC_PLL2Div16          (0xdUL << SYSCTRL_CLK_TEST_SRC_Pos)
#define SYSCTRL_CLK_FANOUT_EN_Pos               (3UL)                   /*!< CLK_FANOUT_EN (Bit 3)                          */
#define SYSCTRL_CLK_FANOUT_EN_Msk               (0x8UL)                 /*!< CLK_FANOUT_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_CLK_FANOUT_EN                   SYSCTRL_CLK_FANOUT_EN_Msk
#define SYSCTRL_PMU_DEBUG1_EN_Pos               (2UL)                   /*!< PMU_DEBUG1_EN (Bit 2)                          */
#define SYSCTRL_PMU_DEBUG1_EN_Msk               (0x4UL)                 /*!< PMU_DEBUG1_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_PMU_DEBUG1_EN                   SYSCTRL_PMU_DEBUG1_EN_Msk
#define SYSCTRL_PMU_DEBUG0_EN_Pos               (1UL)                   /*!< PMU_DEBUG0_EN (Bit 1)                          */
#define SYSCTRL_PMU_DEBUG0_EN_Msk               (0x2UL)                 /*!< PMU_DEBUG0_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_PMU_DEBUG0_EN                   SYSCTRL_PMU_DEBUG0_EN_Msk
#define SYSCTRL_TEST_CLKIN_EN_Pos               (0UL)                   /*!< TEST_CLKIN_EN (Bit 0)                          */
#define SYSCTRL_TEST_CLKIN_EN_Msk               (0x1UL)                 /*!< TEST_CLKIN_EN (Bitfield-Mask: 0x01)            */
#define SYSCTRL_TEST_CLKIN_EN                   SYSCTRL_TEST_CLKIN_EN_Msk

/*******************  Bit definition for SRSTSR register  ****************/
#define SYSCTRL_SYSREQ_RST_ST_Pos               (4UL)                   /*!< SYSREQ_RST_ST (Bit 4)                          */
#define SYSCTRL_SYSREQ_RST_ST_Msk               (0x10UL)                /*!< SYSREQ_RST_ST (Bitfield-Mask: 0x01)            */
#define SYSCTRL_SYSREQ_RST_ST                   SYSCTRL_SYSREQ_RST_ST_Msk
#define SYSCTRL_MCLR_RST_ST_Pos                 (3UL)                   /*!< MCLR_RST_ST (Bit 3)                            */
#define SYSCTRL_MCLR_RST_ST_Msk                 (0x8UL)                 /*!< MCLR_RST_ST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_MCLR_RST_ST                     SYSCTRL_MCLR_RST_ST_Msk
#define SYSCTRL_LVD_RST_ST_Pos                  (2UL)                   /*!< LVD_RST_ST (Bit 2)                             */
#define SYSCTRL_LVD_RST_ST_Msk                  (0x4UL)                 /*!< LVD_RST_ST (Bitfield-Mask: 0x01)               */
#define SYSCTRL_LVD_RST_ST                      SYSCTRL_LVD_RST_ST_Msk
#define SYSCTRL_WWDG_RST_ST_Pos                 (1UL)                   /*!< WWDG_RST_ST (Bit 1)                            */
#define SYSCTRL_WWDG_RST_ST_Msk                 (0x2UL)                 /*!< WWDG_RST_ST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_WWDG_RST_ST                     SYSCTRL_WWDG_RST_ST_Msk
#define SYSCTRL_IWDG_RST_ST_Pos                 (0UL)                   /*!< IWDG_RST_ST (Bit 0)                            */
#define SYSCTRL_IWDG_RST_ST_Msk                 (0x1UL)                 /*!< IWDG_RST_ST (Bitfield-Mask: 0x01)              */
#define SYSCTRL_IWDG_RST_ST                     SYSCTRL_IWDG_RST_ST_Msk

/*********************  Bit definition for KEY register  ******************/
#define SYSCTRL_LOCKKEY_Pos                     (0UL)                   /*!< SYSCTL_LOCKKEY (Bit 0)                         */
#define SYSCTRL_LOCKKEY_Msk                     (0xffffffffUL)          /*!< SYSCTL_LOCKKEY (Bitfield-Mask: 0xffffffff)     */
#define SYSCTRL_LOCKKEY                         SYSCTRL_LOCKKEY_Msk

/*********************  Bit definition for PMUCR register  *****************/
#define SYSCTRL_PMU_IN_Pos                      (25UL)                  /*!< PMU_IN (Bit 25)                                */
#define SYSCTRL_PMU_IN_Msk                      (0x7e000000UL)          /*!< PMU_IN (Bitfield-Mask: 0x3f)                   */
#define SYSCTRL_PMU_IN                          SYSCTRL_PMU_IN_Msk
#define SYSCTRL_CUR_RES_Pos                     (19UL)                  /*!< CUR_RES (Bit 19)                               */
#define SYSCTRL_CUR_RES_Msk                     (0x1f80000UL)           /*!< CUR_RES (Bitfield-Mask: 0x3f)                  */
#define SYSCTRL_CUR_RES                         SYSCTRL_CUR_RES_Msk
#define SYSCTRL_CUR_CAL_Pos                     (17UL)                  /*!< CUR_CAL (Bit 17)                               */
#define SYSCTRL_CUR_CAL_Msk                     (0x60000UL)             /*!< CUR_CAL (Bitfield-Mask: 0x03)                  */
#define SYSCTRL_CUR_CAL                         SYSCTRL_CUR_CAL_Msk
#define SYSCTRL_AVDD_DRD_Pos                    (16UL)                  /*!< AVDD_DRD (Bit 16)                              */
#define SYSCTRL_AVDD_DRD_Msk                    (0x10000UL)             /*!< AVDD_DRD (Bitfield-Mask: 0x01)                 */
#define SYSCTRL_AVDD_DRD                        SYSCTRL_AVDD_DRD_Msk
#define SYSCTRL_AVDD_SET_Pos                    (14UL)                  /*!< AVDD_SET (Bit 14)                              */
#define SYSCTRL_AVDD_SET_Msk                    (0xc000UL)              /*!< AVDD_SET (Bitfield-Mask: 0x03)                 */
#define SYSCTRL_AVDD_SET                        SYSCTRL_AVDD_SET_Msk
#define SYSCTRL_AVDD_SET_1V3                    (0x0UL << SYSCTRL_AVDD_SET_Pos)
#define SYSCTRL_AVDD_SET_1V4                    (0x1UL << SYSCTRL_AVDD_SET_Pos)
#define SYSCTRL_AVDD_SET_1V5                    (0x2UL << SYSCTRL_AVDD_SET_Pos)
#define SYSCTRL_AVDD_SET_1V6                    (0x3UL << SYSCTRL_AVDD_SET_Pos)
#define SYSCTRL_VDD_SET_Pos                     (10UL)                  /*!< VDD_SET (Bit 10)                               */
#define SYSCTRL_VDD_SET_Msk                     (0x3c00UL)              /*!< VDD_SET (Bitfield-Mask: 0x0f)                  */
#define SYSCTRL_VDD_SET                         SYSCTRL_VDD_SET_Msk
#define SYSCTRL_VDD_SET_1V1                     (0x0UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V15                    (0x1UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V2                     (0x2UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V25                    (0x3UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V3                     (0x4UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V35                    (0x5UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V4                     (0x6UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V45                    (0x7UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V5                     (0x8UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V55                    (0x9UL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V6                     (0xaUL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V65                    (0xbUL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V7                     (0xcUL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V75                    (0xdUL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V8                     (0xeUL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_VDD_SET_1V85                    (0xfUL << SYSCTRL_VDD_SET_Pos)
#define SYSCTRL_CUR_ENABLE_Pos                  (9UL)                   /*!< CUR_ENABLE (Bit 9)                             */
#define SYSCTRL_CUR_ENABLE_Msk                  (0x200UL)               /*!< CUR_ENABLE (Bitfield-Mask: 0x01)               */
#define SYSCTRL_CUR_ENABLE                      SYSCTRL_CUR_ENABLE_Msk
#define SYSCTRL_AVDDLDO_ENABLE_Pos              (8UL)                   /*!< AVDDLDO_ENABLE (Bit 8)                         */
#define SYSCTRL_AVDDLDO_ENABLE_Msk              (0x100UL)               /*!< AVDDLDO_ENABLE (Bitfield-Mask: 0x01)           */
#define SYSCTRL_AVDDLDO_ENABLE                  SYSCTRL_AVDDLDO_ENABLE_Msk
#define SYSCTRL_TEMPSENSOR_ENABLE_Pos           (7UL)                   /*!< TEMPSENSOR_ENABLE (Bit 7)                      */
#define SYSCTRL_TEMPSENSOR_ENABLE_Msk           (0x80UL)                /*!< TEMPSENSOR_ENABLE (Bitfield-Mask: 0x01)        */
#define SYSCTRL_TEMPSENSOR_ENABLE               SYSCTRL_TEMPSENSOR_ENABLE_Msk
#define SYSCTRL_BGR_VOL_Pos                     (2UL)                   /*!< BGR_VOL (Bit 2)                                */
#define SYSCTRL_BGR_VOL_Msk                     (0x7cUL)                /*!< BGR_VOL (Bitfield-Mask: 0x1f)                  */
#define SYSCTRL_BGR_VOL                         SYSCTRL_BGR_VOL_Msk
#define SYSCTRL_BGR_DRD_Pos                     (1UL)                   /*!< BGR_DRD (Bit 1)                                */
#define SYSCTRL_BGR_DRD_Msk                     (0x2UL)                 /*!< BGR_DRD (Bitfield-Mask: 0x01)                  */
#define SYSCTRL_BGR_DRD                         SYSCTRL_BGR_DRD_Msk
#define SYSCTRL_BGR_FILTER_Pos                  (0UL)                   /*!< BGR_FILTER (Bit 0)                             */
#define SYSCTRL_BGR_FILTER_Msk                  (0x1UL)                 /*!< BGR_FILTER (Bitfield-Mask: 0x01)               */
#define SYSCTRL_BGR_FILTER                      SYSCTRL_BGR_FILTER_Msk


/******************************************************************************/
/*                                                                            */
/*                                LVD Control                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for LACR register  ***************/
#define LVDCTRL_VDDOC_ST_Pos        (31UL)                              /*!< VDDOC_ST (Bit 31)                              */
#define LVDCTRL_VDDOC_ST_Msk        (0x80000000UL)                      /*!< VDDOC_ST (Bitfield-Mask: 0x01)                 */
#define LVDCTRL_VDDOC_ST            LVDCTRL_VDDOC_ST_Msk
#define LVDCTRL_VDDLV_ST_Pos        (30UL)                              /*!< VDDLV_ST (Bit 30)                              */
#define LVDCTRL_VDDLV_ST_Msk        (0x40000000UL)                      /*!< VDDLV_ST (Bitfield-Mask: 0x01)                 */
#define LVDCTRL_VDDLV_ST            LVDCTRL_VDDLV_ST_Msk
#define LVDCTRL_VCCLV_ST_Pos        (29UL)                              /*!< VCCLV_ST (Bit 29)                              */
#define LVDCTRL_VCCLV_ST_Msk        (0x20000000UL)                      /*!< VCCLV_ST (Bitfield-Mask: 0x01)                 */
#define LVDCTRL_VCCLV_ST            LVDCTRL_VCCLV_ST_Msk
#define LVDCTRL_AVCCLV_ST_Pos       (28UL)                              /*!< AVCCLV_ST (Bit 28)                             */
#define LVDCTRL_AVCCLV_ST_Msk       (0x10000000UL)                      /*!< AVCCLV_ST (Bitfield-Mask: 0x01)                */
#define LVDCTRL_AVCCLV_ST           LVDCTRL_AVCCLV_ST_Msk
#define LVDCTRL_VDDOC_BYP_EN_Pos    (27UL)                              /*!< VDDOC_BYP_EN (Bit 27)                          */
#define LVDCTRL_VDDOC_BYP_EN_Msk    (0x8000000UL)                       /*!< VDDOC_BYP_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDOC_BYP_EN        LVDCTRL_VDDOC_BYP_EN_Msk
#define LVDCTRL_VDDLV_BYP_EN_Pos    (26UL)                              /*!< VDDLV_BYP_EN (Bit 26)                          */
#define LVDCTRL_VDDLV_BYP_EN_Msk    (0x4000000UL)                       /*!< VDDLV_BYP_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDLV_BYP_EN        LVDCTRL_VDDLV_BYP_EN_Msk
#define LVDCTRL_VCCLV_BYP_EN_Pos    (25UL)                              /*!< VCCLV_BYP_EN (Bit 25)                          */
#define LVDCTRL_VCCLV_BYP_EN_Msk    (0x2000000UL)                       /*!< VCCLV_BYP_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VCCLV_BYP_EN        LVDCTRL_VCCLV_BYP_EN_Msk
#define LVDCTRL_AVCCLV_BYP_EN_Pos   (24UL)                              /*!< AVCCLV_BYP_EN (Bit 24)                         */
#define LVDCTRL_AVCCLV_BYP_EN_Msk   (0x1000000UL)                       /*!< AVCCLV_BYP_EN (Bitfield-Mask: 0x01)            */
#define LVDCTRL_AVCCLV_BYP_EN       LVDCTRL_AVCCLV_BYP_EN_Msk
#define LVDCTRL_ANAIN_DBC_LIMIT_Pos (16UL)                              /*!< ANAIN_DBC_LIMIT (Bit 16)                       */
#define LVDCTRL_ANAIN_DBC_LIMIT_Msk (0xff0000UL)                        /*!< ANAIN_DBC_LIMIT (Bitfield-Mask: 0xff)          */
#define LVDCTRL_ANAIN_DBC_LIMIT     LVDCTRL_ANAIN_DBC_LIMIT_Msk
#define LVDCTRL_VCCLV_SET_Pos       (11UL)                              /*!< VCCLV_SET (Bit 11)                             */
#define LVDCTRL_VCCLV_SET_Msk       (0x1800UL)                          /*!< VCCLV_SET (Bitfield-Mask: 0x03)                */
#define LVDCTRL_VCCLV_SET           LVDCTRL_VCCLV_SET_Msk
#define LVDCTRL_VCCLV_SET_2V4       (0x0UL << LVDCTRL_VCCLV_SET_Pos)
#define LVDCTRL_VCCLV_SET_2V55      (0x1UL << LVDCTRL_VCCLV_SET_Pos)
#define LVDCTRL_VCCLV_SET_2V7       (0x2UL << LVDCTRL_VCCLV_SET_Pos)
#define LVDCTRL_VCCLV_SET_3V        (0x3UL << LVDCTRL_VCCLV_SET_Pos)
#define LVDCTRL_AVCCLV_SET_Pos      (9UL)                               /*!< AVCCLV_SET (Bit 9)                             */
#define LVDCTRL_AVCCLV_SET_Msk      (0x600UL)                           /*!< AVCCLV_SET (Bitfield-Mask: 0x03)               */
#define LVDCTRL_AVCCLV_SET          LVDCTRL_AVCCLV_SET_Msk
#define LVDCTRL_AVCCLV_SET_2V4      (0x0UL << LVDCTRL_AVCCLV_SET_Pos)
#define LVDCTRL_AVCCLV_SET_2V55     (0x1UL << LVDCTRL_AVCCLV_SET_Pos)
#define LVDCTRL_AVCCLV_SET_2V7      (0x2UL << LVDCTRL_AVCCLV_SET_Pos)
#define LVDCTRL_AVCCLV_SET_3V       (0x3UL << LVDCTRL_AVCCLV_SET_Pos)
#define LVDCTRL_VDDOC_SET_Pos       (7UL)                               /*!< VDDOC_SET (Bit 7)                              */
#define LVDCTRL_VDDOC_SET_Msk       (0x180UL)                           /*!< VDDOC_SET (Bitfield-Mask: 0x03)                */
#define LVDCTRL_VDDOC_SET           LVDCTRL_VDDOC_SET_Msk
#define LVDCTRL_VDDOC_SET_300mA     (0x0UL << LVDCTRL_VDDOC_SET_Pos)
#define LVDCTRL_VDDOC_SET_350mA     (0x1UL << LVDCTRL_VDDOC_SET_Pos)
#define LVDCTRL_VDDOC_SET_400mA     (0x2UL << LVDCTRL_VDDOC_SET_Pos)
#define LVDCTRL_VDDOC_SET_450mA     (0x3UL << LVDCTRL_VDDOC_SET_Pos)
#define LVDCTRL_VDDLV_SET_Pos       (4UL)                               /*!< VDDLV_SET (Bit 4)                              */
#define LVDCTRL_VDDLV_SET_Msk       (0x70UL)                            /*!< VDDLV_SET (Bitfield-Mask: 0x07)                */
#define LVDCTRL_VDDLV_SET           LVDCTRL_VDDLV_SET_Msk
#define LVDCTRL_VDDLV_SET_800mV     (0x0UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_900mV     (0x1UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_1V        (0x2UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_1V1       (0x3UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_1V2       (0x4UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_1V3       (0x5UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_1V35      (0x6UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VDDLV_SET_1V4       (0x7UL << LVDCTRL_VDDLV_SET_Pos)
#define LVDCTRL_VCCLV_EN_Pos        (3UL)                               /*!< VCCLV_EN (Bit 3)                               */
#define LVDCTRL_VCCLV_EN_Msk        (0x8UL)                             /*!< VCCLV_EN (Bitfield-Mask: 0x01)                 */
#define LVDCTRL_VCCLV_EN            LVDCTRL_VCCLV_EN_Msk
#define LVDCTRL_AVCCLV_EN_Pos       (2UL)                               /*!< AVCCLV_EN (Bit 2)                              */
#define LVDCTRL_AVCCLV_EN_Msk       (0x4UL)                             /*!< AVCCLV_EN (Bitfield-Mask: 0x01)                */
#define LVDCTRL_AVCCLV_EN           LVDCTRL_AVCCLV_EN_Msk
#define LVDCTRL_VDDOC_EN_Pos        (1UL)                               /*!< VDDOC_EN (Bit 1)                               */
#define LVDCTRL_VDDOC_EN_Msk        (0x2UL)                             /*!< VDDOC_EN (Bitfield-Mask: 0x01)                 */
#define LVDCTRL_VDDOC_EN            LVDCTRL_VDDOC_EN_Msk
#define LVDCTRL_VDDLV_EN_Pos        (0UL)                               /*!< VDDLV_EN (Bit 0)                               */
#define LVDCTRL_VDDLV_EN_Msk        (0x1UL)                             /*!< VDDLV_EN (Bitfield-Mask: 0x01)                 */
#define LVDCTRL_VDDLV_EN            LVDCTRL_VDDLV_EN_Msk

/*********************  Bit definition for LCR register  *****************/
#define LVDCTRL_VDDOC_BRK_EN_Pos    (19UL)                              /*!< VDDOC_BRK_EN (Bit 19)                          */
#define LVDCTRL_VDDOC_BRK_EN_Msk    (0x80000UL)                         /*!< VDDOC_BRK_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDOC_BRK_EN        LVDCTRL_VDDOC_BRK_EN_Msk
#define LVDCTRL_VDDLV_BRK_EN_Pos    (18UL)                              /*!< VDDLV_BRK_EN (Bit 18)                          */
#define LVDCTRL_VDDLV_BRK_EN_Msk    (0x40000UL)                         /*!< VDDLV_BRK_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDLV_BRK_EN        LVDCTRL_VDDLV_BRK_EN_Msk
#define LVDCTRL_VCCLV_BRK_EN_Pos    (17UL)                              /*!< VCCLV_BRK_EN (Bit 17)                          */
#define LVDCTRL_VCCLV_BRK_EN_Msk    (0x20000UL)                         /*!< VCCLV_BRK_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VCCLV_BRK_EN        LVDCTRL_VCCLV_BRK_EN_Msk
#define LVDCTRL_AVCCLV_BRK_EN_Pos   (16UL)                              /*!< AVCCLV_BRK_EN (Bit 16)                         */
#define LVDCTRL_AVCCLV_BRK_EN_Msk   (0x10000UL)                         /*!< AVCCLV_BRK_EN (Bitfield-Mask: 0x01)            */
#define LVDCTRL_AVCCLV_BRK_EN       LVDCTRL_AVCCLV_BRK_EN_Msk
#define LVDCTRL_VDDOC_INT_EN_Pos    (7UL)                               /*!< VDDOC_INT_EN (Bit 7)                           */
#define LVDCTRL_VDDOC_INT_EN_Msk    (0x80UL)                            /*!< VDDOC_INT_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDOC_INT_EN        LVDCTRL_VDDOC_INT_EN_Msk
#define LVDCTRL_VDDLV_INT_EN_Pos    (6UL)                               /*!< VDDLV_INT_EN (Bit 6)                           */
#define LVDCTRL_VDDLV_INT_EN_Msk    (0x40UL)                            /*!< VDDLV_INT_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDLV_INT_EN        LVDCTRL_VDDLV_INT_EN_Msk
#define LVDCTRL_VCCLV_INT_EN_Pos    (5UL)                               /*!< VCCLV_INT_EN (Bit 5)                           */
#define LVDCTRL_VCCLV_INT_EN_Msk    (0x20UL)                            /*!< VCCLV_INT_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VCCLV_INT_EN        LVDCTRL_VCCLV_INT_EN_Msk
#define LVDCTRL_AVCCLV_INT_EN_Pos   (4UL)                               /*!< AVCCLV_INT_EN (Bit 4)                          */
#define LVDCTRL_AVCCLV_INT_EN_Msk   (0x10UL)                            /*!< AVCCLV_INT_EN (Bitfield-Mask: 0x01)            */
#define LVDCTRL_AVCCLV_INT_EN       LVDCTRL_AVCCLV_INT_EN_Msk
#define LVDCTRL_VDDOC_RST_EN_Pos    (3UL)                               /*!< VDDOC_RST_EN (Bit 3)                           */
#define LVDCTRL_VDDOC_RST_EN_Msk    (0x8UL)                             /*!< VDDOC_RST_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDOC_RST_EN        LVDCTRL_VDDOC_RST_EN_Msk
#define LVDCTRL_VDDLV_RST_EN_Pos    (2UL)                               /*!< VDDLV_RST_EN (Bit 2)                           */
#define LVDCTRL_VDDLV_RST_EN_Msk    (0x4UL)                             /*!< VDDLV_RST_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VDDLV_RST_EN        LVDCTRL_VDDLV_RST_EN_Msk
#define LVDCTRL_VCCLV_RST_EN_Pos    (1UL)                               /*!< VCCLV_RST_EN (Bit 1)                           */
#define LVDCTRL_VCCLV_RST_EN_Msk    (0x2UL)                             /*!< VCCLV_RST_EN (Bitfield-Mask: 0x01)             */
#define LVDCTRL_VCCLV_RST_EN        LVDCTRL_VCCLV_RST_EN_Msk
#define LVDCTRL_AVCCLV_RST_EN_Pos   (0UL)                               /*!< AVCCLV_RST_EN (Bit 0)                          */
#define LVDCTRL_AVCCLV_RST_EN_Msk   (0x1UL)                             /*!< AVCCLV_RST_EN (Bitfield-Mask: 0x01)            */
#define LVDCTRL_AVCCLV_RST_EN       LVDCTRL_AVCCLV_RST_EN_Msk


/******************************************************************************/
/*                                                                            */
/*                                 FPLL0/1/2                                  */
/*                                                                            */
/******************************************************************************/

/*********************  Bit definition for FCR register  *****************/
#define FPLL_EN_Pos                 (1UL)                       /*!< fpllEn (Bit 1)                             */
#define FPLL_EN_Msk                 (0x2UL)                     /*!< fpllEn (Bitfield-Mask: 0x01)               */
#define FPLL_EN                     FPLL_EN_Msk
#define FPLL_START_Pos              (0UL)                       /*!< fpllStart (Bit 0)                          */
#define FPLL_START_Msk              (0x1UL)                     /*!< fpllStart (Bitfield-Mask: 0x01)            */
#define FPLL_START                  FPLL_START_Msk

/*********************  Bit definition for FDR register  *****************/
#define FPLL_DIV_INT_Pos            (16UL)                      /*!< fpllIntDivisor (Bit 16)                    */
#define FPLL_DIV_INT_Msk            (0x3fff0000UL)              /*!< fpllIntDivisor (Bitfield-Mask: 0x3fff)     */
#define FPLL_DIV_INT                FPLL_DIV_INT_Msk
#define FPLL_DIV_FRAC_Pos           (0UL)                       /*!< fpllFracDivisor (Bit 0)                    */
#define FPLL_DIV_FRAC_Msk           (0xffffUL)                  /*!< fpllFracDivisor (Bitfield-Mask: 0xffff)    */
#define FPLL_DIV_FRAC               FPLL_DIV_FRAC_Msk


/******************************************************************************/
/*                                                                            */
/*                                   DALI                                     */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DALI_CR register  *******************/
#define DALI_CR_BEIE_Pos            (11UL)                          /*!< DALI Backward Error Interrupt Enable (Bit 11)          */
#define DALI_CR_BEIE_Msk            (0x1UL << DALI_CR_BEIE_Pos)     /*!< DALI Backward Error Interrupt Enable (Bitfield-Mask)   */
#define DALI_CR_BEIE                DALI_CR_BEIE_Msk
#define DALI_CR_FEIE_Pos            (10UL)                          /*!< DALI Forward Error Interrupt Enable (Bit 10)           */
#define DALI_CR_FEIE_Msk            (0x1UL << DALI_CR_FEIE_Pos)     /*!< DALI Forward Error Interrupt Enable (Bitfield-Mask)    */
#define DALI_CR_FEIE                DALI_CR_FEIE_Msk
#define DALI_CR_BDIE_Pos            (9UL)                           /*!< DALI Backward Done Interrupt Enable (Bit 11)           */
#define DALI_CR_BDIE_Msk            (0x1UL << DALI_CR_BDIE_Pos)     /*!< DALI Backward Done Interrupt Enable (Bitfield-Mask)    */
#define DALI_CR_BDIE                DALI_CR_BDIE_Msk
#define DALI_CR_FDIE_Pos            (8UL)                           /*!< DALI Forward Done Interrupt Enable (Bit 10)            */
#define DALI_CR_FDIE_Msk            (0x1UL << DALI_CR_FDIE_Pos)     /*!< DALI Forward Done Interrupt Enable (Bitfield-Mask)     */
#define DALI_CR_FDIE                DALI_CR_FDIE_Msk
#define DALI_CR_ML_Pos              (4UL)                           /*!< DALI Forward Message Length (Bit 4 - 5)                */
#define DALI_CR_ML_Msk              (0x3UL << DALI_CR_ML_Pos)       /*!< DALI Forward Message Length (Bitfield-Mask)            */
#define DALI_CR_ML_0                (0x1UL << DALI_CR_ML_Pos)
#define DALI_CR_ML_1                (0x2UL << DALI_CR_ML_Pos)
#define DALI_CR_POL_Pos             (3UL)                           /*!< DALI Polarity (Bit 3)                                  */
#define DALI_CR_POL_Msk             (0x1UL << DALI_CR_POL_Pos)      /*!< DALI Polarity (Bitfield-Mask)                          */
#define DALI_CR_POL                 DALI_CR_POL_Msk
#define DALI_CR_TS_Pos              (2UL)                           /*!< DALI Transmit Start (Bit 2)                            */
#define DALI_CR_TS_Msk              (0x1UL << DALI_CR_TS_Pos)       /*!< DALI Transmit Start (Bitfield-Mask)                    */
#define DALI_CR_TS                  DALI_CR_TS_Msk
#define DALI_CR_MODE_Pos            (1UL)                           /*!< DALI Mode Selection (Bit 1)                            */
#define DALI_CR_MODE_Msk            (0x1UL << DALI_CR_MODE_Pos)     /*!< DALI Mode Selection (Bitfield-Mask)                    */
#define DALI_CR_MODE                DALI_CR_MODE_Msk
#define DALI_CR_PEN_Pos             (0UL)                           /*!< DALI Peripheral Enable (Bit 0)                         */
#define DALI_CR_PEN_Msk             (0x1UL << DALI_CR_PEN_Pos)      /*!< DALI Peripheral Enable (Bitfield-Mask)                 */
#define DALI_CR_PEN                 DALI_CR_PEN_Msk

/********************  Bit definition for DALI_ISR register  ******************/
#define DALI_ISR_BSY_Pos            (4UL)                           /*!< DALI Busy status (Bit 4)                               */
#define DALI_ISR_BSY_Msk            (0x1UL << DALI_ISR_BSY_Pos)     /*!< DALI Busy status (Bitfield-Mask)                       */
#define DALI_ISR_BSY                DALI_ISR_BSY_Msk
#define DALI_ISR_BEIF_Pos           (3UL)                           /*!< DALI Backward Error Interrupt Flag (Bit 3)             */
#define DALI_ISR_BEIF_Msk           (0x1UL << DALI_ISR_BEIF_Pos)    /*!< DALI Backward Error Interrupt Flag (Bitfield-Mask)     */
#define DALI_ISR_BEIF               DALI_ISR_BEIF_Msk
#define DALI_ISR_FEIF_Pos           (2UL)                           /*!< DALI Forward Error Interrupt Flag (Bit 2)              */
#define DALI_ISR_FEIF_Msk           (0x1UL << DALI_ISR_FEIF_Pos)    /*!< DALI Forward Error Interrupt Flag (Bitfield-Mask)      */
#define DALI_ISR_FEIF               DALI_ISR_FEIF_Msk
#define DALI_ISR_BDIF_Pos           (1UL)                           /*!< DALI Backward Error Interrupt Flag (Bit 1)             */
#define DALI_ISR_BDIF_Msk           (0x1UL << DALI_ISR_BDIF_Pos)    /*!< DALI Backward Error Interrupt Flag (Bitfield-Mask)     */
#define DALI_ISR_BDIF               DALI_ISR_BDIF_Msk
#define DALI_ISR_FDIF_Pos           (0UL)                           /*!< DALI Forward Error Interrupt Flag (Bit 0)              */
#define DALI_ISR_FDIF_Msk           (0x1UL << DALI_ISR_FDIF_Pos)    /*!< DALI Forward Error Interrupt Flag (Bitfield-Mask)      */
#define DALI_ISR_FDIF               DALI_ISR_FDIF_Msk

/********************  Bit definition for DALI_FDR register  ******************/
#define DALI_FDR_FD_Pos             (0UL)                           /*!< DALI Forward Data (Bit 0 - 23)                         */
#define DALI_FDR_FD_Msk             (0xFFFFFFUL << DALI_FDR_FD_Pos) /*!< DALI Forward Data (Bitfield-Mask)                      */

/********************  Bit definition for DALI_BDR register  ******************/
#define DALI_BDR_BD_Pos             (0UL)                           /*!< DALI Backward Data (Bit 0 - 23)                        */
#define DALI_BDR_BD_Msk             (0xFFFFFFUL << DALI_BDR_BD_Pos) /*!< DALI Backward Data (Bitfield-Mask)                     */

/********************  Bit definition for DALI_FCR register  ******************/
#define DALI_FCR_FE_Pos             (16UL)                          /*!< DALI Filter Enable (Bit 16)                            */
#define DALI_FCR_FE_Msk             (0x1UL << DALI_FCR_FE_Pos)      /*!< DALI Filter Enable (Bitfield-Mask)                     */
#define DALI_FCR_FE                 DALI_FCR_FE_Msk
#define DALI_FCR_FCNT_Pos           (0UL)                           /*!< DALI Filter Counter (Bit 0 - 15)                       */
#define DALI_FCR_FCNT_Msk           (0xFFFFUL << DALI_FCR_FCNT_Pos) /*!< DALI Filter Counter (Bitfield-Mask)                    */

/********************  Bit definition for DALI_PSCR register  *****************/
#define DALI_PSCR_FTR_Pos           (12UL)                          /*!< DALI Fault Tolerance Range (Bit 12)                    */
#define DALI_PSCR_FTR_Msk           (0x1UL << DALI_PSCR_FTR_Pos)    /*!< DALI Fault Tolerance Range (Bitfield-Mask)             */
#define DALI_PSCR_PSC_Pos           (0UL)                           /*!< DALI Prescaler Value (Bit 0 - 11)                      */
#define DALI_PSCR_PSC_Msk           (0xFFFUL << DALI_PSCR_PSC_Pos)  /*!< DALI Prescaler Value (Bitfield-Mask)                   */

/********************  Bit definition for DALI_TCR register  ******************/
#define DALI_TCR_BDLY_Pos           (16UL)                          /*!< DALI Backward frame Delay (Bit 16 - 22)                */
#define DALI_TCR_BDLY_Msk           (0x7FUL << DALI_TCR_BDLY_Pos)   /*!< DALI Backward frame Delay (Bitfield-Mask)              */

#define DALI_TCR_FDLY_Pos           (0UL)                           /*!< DALI Forward frame Delay (Bit 0 - 8)                   */
#define DALI_TCR_FDLY_Msk           (0x1FFUL << DALI_TCR_FDLY_Pos)  /*!< DALI Forward frame Delay (Bitfield-Mask)               */


/******************************************************************************/
/*                                                                            */
/*                                   I2C0/1                                   */
/*                                                                            */
/******************************************************************************/

/***********************  Bit definition for CON register  ********************/
#define I2C_SMBUS_PST_SLV_ADDR_EN_Pos           (19UL)              /*!< SMBUS_PERSISTANT_SLV_ADDR_EN (Bit 19)                  */
#define I2C_SMBUS_PST_SLV_ADDR_EN_Msk           (0x80000UL)         /*!< SMBUS_PERSISTANT_SLV_ADDR_EN (Bitfield-Mask: 0x01)     */
#define I2C_SMBUS_PST_SLV_ADDR_EN               I2C_SMBUS_PST_SLV_ADDR_EN_Msk
#define I2C_SMBUS_ARP_EN_Pos                    (18UL)              /*!< SMBUS_ARP_EN (Bit 18)                                  */
#define I2C_SMBUS_ARP_EN_Msk                    (0x40000UL)         /*!< SMBUS_ARP_EN (Bitfield-Mask: 0x01)                     */
#define I2C_SMBUS_ARP_EN                        I2C_SMBUS_ARP_EN_Msk
#define I2C_SMBUS_SLV_QUICK_CMD_EN_Pos          (17UL)              /*!< SMBUS_SLV_QUICK_CMD_EN (Bit 17)                        */
#define I2C_SMBUS_SLV_QUICK_CMD_EN_Msk          (0x20000UL)         /*!< SMBUS_SLV_QUICK_CMD_EN (Bitfield-Mask: 0x01)           */
#define I2C_SMBUS_SLV_QUICK_CMD_EN              I2C_SMBUS_SLV_QUICK_CMD_EN_Msk
#define I2C_OPTIONAL_SAR_CTRL_Pos               (16UL)              /*!< OPTIONAL_SAR_CTRL (Bit 16)                             */
#define I2C_OPTIONAL_SAR_CTRL_Msk               (0x10000UL)         /*!< OPTIONAL_SAR_CTRL (Bitfield-Mask: 0x01)                */
#define I2C_OPTIONAL_SAR_CTRL                   I2C_OPTIONAL_SAR_CTRL_Msk
#define I2C_BUS_CLEAR_FEATURE_CTRL_Pos          (11UL)              /*!< BUS_CLEAR_FEATURE_CTRL (Bit 11)                        */
#define I2C_BUS_CLEAR_FEATURE_CTRL_Msk          (0x800UL)           /*!< BUS_CLEAR_FEATURE_CTRL (Bitfield-Mask: 0x01)           */
#define I2C_BUS_CLEAR_FEATURE_CTRL              I2C_BUS_CLEAR_FEATURE_CTRL_Msk
#define I2C_STOP_DET_IF_MASTER_ACT_Pos          (10UL)              /*!< STOP_DET_IF_MASTER_ACT (Bit 10)                        */
#define I2C_STOP_DET_IF_MASTER_ACT_Msk          (0x400UL)           /*!< STOP_DET_IF_MASTER_ACT (Bitfield-Mask: 0x01)           */
#define I2C_STOP_DET_IF_MASTER_ACT              I2C_STOP_DET_IF_MASTER_ACT_Msk
#define I2C_RX_FIFO_FULL_HLD_CTRL_Pos           (9UL)               /*!< RX_FIFO_FULL_HLD_CTRL (Bit 9)                          */
#define I2C_RX_FIFO_FULL_HLD_CTRL_Msk           (0x200UL)           /*!< RX_FIFO_FULL_HLD_CTRL (Bitfield-Mask: 0x01)            */
#define I2C_RX_FIFO_FULL_HLD_CTRL               I2C_RX_FIFO_FULL_HLD_CTRL_Msk
#define I2C_TX_EMPTY_CTRL_Pos                   (8UL)               /*!< TX_EMPTY_CTRL (Bit 8)                                  */
#define I2C_TX_EMPTY_CTRL_Msk                   (0x100UL)           /*!< TX_EMPTY_CTRL (Bitfield-Mask: 0x01)                    */
#define I2C_TX_EMPTY_CTRL                       I2C_TX_EMPTY_CTRL_Msk
#define I2C_STOP_DET_IFADDRESSED_Pos            (7UL)               /*!< STOP_DET_IFADDRESSED (Bit 7)                           */
#define I2C_STOP_DET_IFADDRESSED_Msk            (0x80UL)            /*!< STOP_DET_IFADDRESSED (Bitfield-Mask: 0x01)             */
#define I2C_STOP_DET_IFADDRESSED                I2C_STOP_DET_IFADDRESSED_Msk
#define I2C_SLAVE_DISABLE_Pos                   (6UL)               /*!< IC_SLAVE_DISABLE (Bit 6)                               */
#define I2C_SLAVE_DISABLE_Msk                   (0x40UL)            /*!< IC_SLAVE_DISABLE (Bitfield-Mask: 0x01)                 */
#define I2C_SLAVE_DISABLE                       I2C_SLAVE_DISABLE_Msk
#define I2C_RESTART_EN_Pos                      (5UL)               /*!< IC_RESTART_EN (Bit 5)                                  */
#define I2C_RESTART_EN_Msk                      (0x20UL)            /*!< IC_RESTART_EN (Bitfield-Mask: 0x01)                    */
#define I2C_RESTART_EN                          I2C_RESTART_EN_Msk
#define I2C_10BITADDR_MASTER_Pos                (4UL)               /*!< IC_10BITADDR_MASTER (Bit 4)                            */
#define I2C_10BITADDR_MASTER_Msk                (0x10UL)            /*!< IC_10BITADDR_MASTER (Bitfield-Mask: 0x01)              */
#define I2C_10BITADDR_MASTER                    I2C_10BITADDR_MASTER_Msk
#define I2C_10BITADDR_SLAVE_Pos                 (3UL)               /*!< IC_10BITADDR_SLAVE (Bit 3)                             */
#define I2C_10BITADDR_SLAVE_Msk                 (0x8UL)             /*!< IC_10BITADDR_SLAVE (Bitfield-Mask: 0x01)               */
#define I2C_10BITADDR_SLAVE                     I2C_10BITADDR_SLAVE_Msk
#define I2C_SPEED_Pos                           (1UL)               /*!< SPEED (Bit 1)                                          */
#define I2C_SPEED_Msk                           (0x6UL)             /*!< SPEED (Bitfield-Mask: 0x03)                            */
#define I2C_SPEED                               I2C_SPEED_Msk
#define I2C_SPEED_STD                           (0x1UL << I2C_SPEED_Pos)
#define I2C_SPEED_FAST                          (0x2UL << I2C_SPEED_Pos)
#define I2C_SPEED_HIGH                          (0x3UL << I2C_SPEED_Pos)
#define I2C_MASTER_MODE_Pos                     (0UL)               /*!< MASTER_MODE (Bit 0)                                    */
#define I2C_MASTER_MODE_Msk                     (0x1UL)             /*!< MASTER_MODE (Bitfield-Mask: 0x01)                      */
#define I2C_MASTER_MODE                         I2C_MASTER_MODE_Msk

/***********************  Bit definition for TAR register  ********************/
#define I2C_SMBUS_QUICK_CMD_Pos                 (16UL)              /*!< SMBUS_QUICK_CMD (Bit 16)                               */
#define I2C_SMBUS_QUICK_CMD_Msk                 (0x10000UL)         /*!< SMBUS_QUICK_CMD (Bitfield-Mask: 0x01)                  */
#define I2C_SMBUS_QUICK_CMD                     I2C_SMBUS_QUICK_CMD_Msk
#define I2C_TAR_DEV_ID_Pos                      (13UL)              /*!< Device_ID (Bit 13)                                     */
#define I2C_TAR_DEV_ID_Msk                      (0x2000UL)          /*!< Device_ID (Bitfield-Mask: 0x01)                        */
#define I2C_TAR_DEV_ID                          I2C_TAR_DEV_ID_Msk
#define I2C_TAR_10BITADDR_MASTER_Pos            (12UL)              /*!< IC_10BITADDR_MASTER (Bit 12)                           */
#define I2C_TAR_10BITADDR_MASTER_Msk            (0x1000UL)          /*!< IC_10BITADDR_MASTER (Bitfield-Mask: 0x01)              */
#define I2C_TAR_10BITADDR_MASTER                I2C_TAR_10BITADDR_MASTER_Msk
#define I2C_SPECIAL_Pos                         (11UL)              /*!< SPECIAL (Bit 11)                                       */
#define I2C_SPECIAL_Msk                         (0x800UL)           /*!< SPECIAL (Bitfield-Mask: 0x01)                          */
#define I2C_SPECIAL                             I2C_SPECIAL_Msk
#define I2C_GC_OR_START_Pos                     (10UL)              /*!< GC_OR_START (Bit 10)                                   */
#define I2C_GC_OR_START_Msk                     (0x400UL)           /*!< GC_OR_START (Bitfield-Mask: 0x01)                      */
#define I2C_GC_OR_START                         I2C_GC_OR_START_Msk
#define I2C_TAR_Pos                             (0UL)               /*!< IC_TAR (Bit 0)                                         */
#define I2C_TAR_Msk                             (0x3ffUL)           /*!< IC_TAR (Bitfield-Mask: 0x3ff)                          */
#define I2C_TAR                                 I2C_TAR_Msk

/***********************  Bit definition for SAR register  ********************/
#define I2C_SAR_Pos                             (0UL)               /*!< IC_SAR (Bit 0)                                         */
#define I2C_SAR_Msk                             (0x3ffUL)           /*!< IC_SAR (Bitfield-Mask: 0x3ff)                          */
#define I2C_SAR                                 I2C_SAR_Msk

/*********************  Bit definition for DCMD register  *****************/
#define I2C_FIRST_DATA_BYTE_Pos                 (11UL)              /*!< FIRST_DATA_BYTE (Bit 11)                               */
#define I2C_FIRST_DATA_BYTE_Msk                 (0x800UL)           /*!< FIRST_DATA_BYTE (Bitfield-Mask: 0x01)                  */
#define I2C_FIRST_DATA_BYTE                     I2C_FIRST_DATA_BYTE_Msk
#define I2C_RESTART_Pos                         (10UL)              /*!< RESTART (Bit 10)                                       */
#define I2C_RESTART_Msk                         (0x400UL)           /*!< RESTART (Bitfield-Mask: 0x01)                          */
#define I2C_RESTART                             I2C_RESTART_Msk
#define I2C_STOP_Pos                            (9UL)               /*!< STOP (Bit 9)                                           */
#define I2C_STOP_Msk                            (0x200UL)           /*!< STOP (Bitfield-Mask: 0x01)                             */
#define I2C_STOP                                I2C_STOP_Msk
#define I2C_CMD_Pos                             (8UL)               /*!< CMD (Bit 8)                                            */
#define I2C_CMD_Msk                             (0x100UL)           /*!< CMD (Bitfield-Mask: 0x01)                              */
#define I2C_CMD                                 I2C_CMD_Msk
#define I2C_CMD_READ                            (1UL << I2C_CMD_Pos)
#define I2C_CMD_WRITE                           (0UL << I2C_CMD_Pos)
#define I2C_DAT_Pos                             (0UL)               /*!< DAT (Bit 0)                                            */
#define I2C_DAT_Msk                             (0xffUL)            /*!< DAT (Bitfield-Mask: 0xff)                              */
#define I2C_DAT                                 I2C_DAT_Msk

/*******************  Bit definition for SSHCNT register  ****************/
#define I2C_SS_SCL_HCNT_Pos                     (0UL)               /*!< IC_SS_SCL_HCNT (Bit 0)                                 */
#define I2C_SS_SCL_HCNT_Msk                     (0xffffUL)          /*!< IC_SS_SCL_HCNT (Bitfield-Mask: 0xffff)                 */
#define I2C_SS_SCL_HCNT                         I2C_SS_SCL_HCNT_Msk

/*******************  Bit definition for SSLCNT register  ****************/
#define I2C_SS_SCL_LCNT_Pos                     (0UL)               /*!< IC_SS_SCL_LCNT (Bit 0)                                 */
#define I2C_SS_SCL_LCNT_Msk                     (0xffffUL)          /*!< IC_SS_SCL_LCNT (Bitfield-Mask: 0xffff)                 */
#define I2C_SS_SCL_LCNT                         I2C_SS_SCL_LCNT_Msk

/*******************  Bit definition for FSHCNT register  ****************/
#define I2C_FS_SCL_HCNT_Pos                     (0UL)               /*!< IC_FS_SCL_HCNT (Bit 0)                                 */
#define I2C_FS_SCL_HCNT_Msk                     (0xffffUL)          /*!< IC_FS_SCL_HCNT (Bitfield-Mask: 0xffff)                 */
#define I2C_FS_SCL_HCNT                         I2C_FS_SCL_HCNT_Msk

/*******************  Bit definition for FSLCNT register  ****************/
#define I2C_FS_SCL_LCNT_Pos                     (0UL)               /*!< IC_FS_SCL_LCNT (Bit 0)                                 */
#define I2C_FS_SCL_LCNT_Msk                     (0xffffUL)          /*!< IC_FS_SCL_LCNT (Bitfield-Mask: 0xffff)                 */
#define I2C_FS_SCL_LCNT                         I2C_FS_SCL_LCNT_Msk

/********************  Bit definition for INTRST register  *****************/
#define I2C_SCL_STK_AT_LOW_INT_STA_Pos          (14UL)              /*!< SCL_STUCK_AT_LOW (Bit 14)                              */
#define I2C_SCL_STK_AT_LOW_INT_STA_Msk          (0x4000UL)          /*!< SCL_STUCK_AT_LOW (Bitfield-Mask: 0x01)                 */
#define I2C_SCL_STK_AT_LOW_INT_STA              I2C_SCL_STK_AT_LOW_INT_STA_Msk
#define I2C_MST_ON_HOLD_INT_STA_Pos             (13UL)              /*!< MST_ON_HOLD (Bit 13)                                   */
#define I2C_MST_ON_HOLD_INT_STA_Msk             (0x2000UL)          /*!< MST_ON_HOLD (Bitfield-Mask: 0x01)                      */
#define I2C_MST_ON_HOLD_INT_STA                 I2C_MST_ON_HOLD_INT_STA_Msk
#define I2C_RESTART_DET_INT_STA_Pos             (12UL)              /*!< RESTART_DET (Bit 12)                                   */
#define I2C_RESTART_DET_INT_STA_Msk             (0x1000UL)          /*!< RESTART_DET (Bitfield-Mask: 0x01)                      */
#define I2C_RESTART_DET_INT_STA                 I2C_RESTART_DET_INT_STA_Msk
#define I2C_GEN_CALL_INT_STA_Pos                (11UL)              /*!< GEN_CALL (Bit 11)                                      */
#define I2C_GEN_CALL_INT_STA_Msk                (0x800UL)           /*!< GEN_CALL (Bitfield-Mask: 0x01)                         */
#define I2C_GEN_CALL_INT_STA                    I2C_GEN_CALL_INT_STA_Msk
#define I2C_START_DET_INT_STA_Pos               (10UL)              /*!< START_DET (Bit 10)                                     */
#define I2C_START_DET_INT_STA_Msk               (0x400UL)           /*!< START_DET (Bitfield-Mask: 0x01)                        */
#define I2C_START_DET_INT_STA                   I2C_START_DET_INT_STA_Msk
#define I2C_STOP_DET_INT_STA_Pos                (9UL)               /*!< STOP_DET (Bit 9)                                       */
#define I2C_STOP_DET_INT_STA_Msk                (0x200UL)           /*!< STOP_DET (Bitfield-Mask: 0x01)                         */
#define I2C_STOP_DET_INT_STA                    I2C_STOP_DET_INT_STA_Msk
#define I2C_ACTIVITY_INT_STA_Pos                (8UL)               /*!< ACTIVITY (Bit 8)                                       */
#define I2C_ACTIVITY_INT_STA_Msk                (0x100UL)           /*!< ACTIVITY (Bitfield-Mask: 0x01)                         */
#define I2C_ACTIVITY_INT_STA                    I2C_ACTIVITY_INT_STA_Msk
#define I2C_RX_DONE_INT_STA_Pos                 (7UL)               /*!< RX_DONE (Bit 7)                                        */
#define I2C_RX_DONE_INT_STA_Msk                 (0x80UL)            /*!< RX_DONE (Bitfield-Mask: 0x01)                          */
#define I2C_RX_DONE_INT_STA                     I2C_RX_DONE_INT_STA_Msk
#define I2C_TX_ABRT_INT_STA_Pos                 (6UL)               /*!< TX_ABRT (Bit 6)                                        */
#define I2C_TX_ABRT_INT_STA_Msk                 (0x40UL)            /*!< TX_ABRT (Bitfield-Mask: 0x01)                          */
#define I2C_TX_ABRT_INT_STA                     I2C_TX_ABRT_INT_STA_Msk
#define I2C_RD_REQ_INT_STA_Pos                  (5UL)               /*!< RD_REQ (Bit 5)                                         */
#define I2C_RD_REQ_INT_STA_Msk                  (0x20UL)            /*!< RD_REQ (Bitfield-Mask: 0x01)                           */
#define I2C_RD_REQ_INT_STA                      I2C_RD_REQ_INT_STA_Msk
#define I2C_TX_EMPTY_INT_STA_Pos                (4UL)               /*!< TX_EMPTY (Bit 4)                                       */
#define I2C_TX_EMPTY_INT_STA_Msk                (0x10UL)            /*!< TX_EMPTY (Bitfield-Mask: 0x01)                         */
#define I2C_TX_EMPTY_INT_STA                    I2C_TX_EMPTY_INT_STA_Msk
#define I2C_TX_OVER_INT_STA_Pos                 (3UL)               /*!< TX_OVER (Bit 3)                                        */
#define I2C_TX_OVER_INT_STA_Msk                 (0x8UL)             /*!< TX_OVER (Bitfield-Mask: 0x01)                          */
#define I2C_TX_OVER_INT_STA                     I2C_TX_OVER_INT_STA_Msk
#define I2C_RX_FULL_INT_STA_Pos                 (2UL)               /*!< RX_FULL (Bit 2)                                        */
#define I2C_RX_FULL_INT_STA_Msk                 (0x4UL)             /*!< RX_FULL (Bitfield-Mask: 0x01)                          */
#define I2C_RX_FULL_INT_STA                     I2C_RX_FULL_INT_STA_Msk
#define I2C_RX_OVER_INT_STA_Pos                 (1UL)               /*!< RX_OVER (Bit 1)                                        */
#define I2C_RX_OVER_INT_STA_Msk                 (0x2UL)             /*!< RX_OVER (Bitfield-Mask: 0x01)                          */
#define I2C_RX_OVER_INT_STA                     I2C_RX_OVER_INT_STA_Msk
#define I2C_RX_UNDER_INT_STA_Pos                (0UL)               /*!< RX_UNDER (Bit 0)                                       */
#define I2C_RX_UNDER_INT_STA_Msk                (0x1UL)             /*!< RX_UNDER (Bitfield-Mask: 0x01)                         */
#define I2C_RX_UNDER_INT_STA                    I2C_RX_UNDER_INT_STA_Msk

/********************  Bit definition for INTRMS register  *****************/
#define I2C_SCL_STK_AT_LOW_INT_EN_Pos           (14UL)              /*!< SCL_STUCK_AT_LOW (Bit 14)                              */
#define I2C_SCL_STK_AT_LOW_INT_EN_Msk           (0x4000UL)          /*!< SCL_STUCK_AT_LOW (Bitfield-Mask: 0x01)                 */
#define I2C_SCL_STK_AT_LOW_INT_EN               I2C_SCL_STK_AT_LOW_INT_EN_Msk
#define I2C_MST_ON_HOLD_INT_EN_Pos              (13UL)              /*!< MST_ON_HOLD (Bit 13)                                   */
#define I2C_MST_ON_HOLD_INT_EN_Msk              (0x2000UL)          /*!< MST_ON_HOLD (Bitfield-Mask: 0x01)                      */
#define I2C_MST_ON_HOLD_INT_EN                  I2C_MST_ON_HOLD_INT_EN_Msk
#define I2C_RESTART_DET_INT_EN_Pos              (12UL)              /*!< RESTART_DET (Bit 12)                                   */
#define I2C_RESTART_DET_INT_EN_Msk              (0x1000UL)          /*!< RESTART_DET (Bitfield-Mask: 0x01)                      */
#define I2C_RESTART_DET_INT_EN                  I2C_RESTART_DET_INT_EN_Msk
#define I2C_GEN_CALL_INT_EN_Pos                 (11UL)              /*!< GEN_CALL (Bit 11)                                      */
#define I2C_GEN_CALL_INT_EN_Msk                 (0x800UL)           /*!< GEN_CALL (Bitfield-Mask: 0x01)                         */
#define I2C_GEN_CALL_INT_EN                     I2C_GEN_CALL_INT_EN_Msk
#define I2C_START_DET_INT_EN_Pos                (10UL)              /*!< START_DET (Bit 10)                                     */
#define I2C_START_DET_INT_EN_Msk                (0x400UL)           /*!< START_DET (Bitfield-Mask: 0x01)                        */
#define I2C_START_DET_INT_EN                    I2C_START_DET_INT_EN_Msk
#define I2C_STOP_DET_INT_EN_Pos                 (9UL)               /*!< STOP_DET (Bit 9)                                       */
#define I2C_STOP_DET_INT_EN_Msk                 (0x200UL)           /*!< STOP_DET (Bitfield-Mask: 0x01)                         */
#define I2C_STOP_DET_INT_EN                     I2C_STOP_DET_INT_EN_Msk
#define I2C_ACTIVITY_INT_EN_Pos                 (8UL)               /*!< ACTIVITY (Bit 8)                                       */
#define I2C_ACTIVITY_INT_EN_Msk                 (0x100UL)           /*!< ACTIVITY (Bitfield-Mask: 0x01)                         */
#define I2C_ACTIVITY_INT_EN                     I2C_ACTIVITY_INT_EN_Msk
#define I2C_RX_DONE_INT_EN_Pos                  (7UL)               /*!< RX_DONE (Bit 7)                                        */
#define I2C_RX_DONE_INT_EN_Msk                  (0x80UL)            /*!< RX_DONE (Bitfield-Mask: 0x01)                          */
#define I2C_RX_DONE_INT_EN                      I2C_RX_DONE_INT_EN_Msk
#define I2C_TX_ABRT_INT_EN_Pos                  (6UL)               /*!< TX_ABRT (Bit 6)                                        */
#define I2C_TX_ABRT_INT_EN_Msk                  (0x40UL)            /*!< TX_ABRT (Bitfield-Mask: 0x01)                          */
#define I2C_TX_ABRT_INT_EN                      I2C_TX_ABRT_INT_EN_Msk
#define I2C_RD_REQ_INT_EN_Pos                   (5UL)               /*!< RD_REQ (Bit 5)                                         */
#define I2C_RD_REQ_INT_EN_Msk                   (0x20UL)            /*!< RD_REQ (Bitfield-Mask: 0x01)                           */
#define I2C_RD_REQ_INT_EN                       I2C_RD_REQ_INT_EN_Msk
#define I2C_TX_EMPTY_INT_EN_Pos                 (4UL)               /*!< TX_EMPTY (Bit 4)                                       */
#define I2C_TX_EMPTY_INT_EN_Msk                 (0x10UL)            /*!< TX_EMPTY (Bitfield-Mask: 0x01)                         */
#define I2C_TX_EMPTY_INT_EN                     I2C_TX_EMPTY_INT_EN_Msk
#define I2C_TX_OVER_INT_EN_Pos                  (3UL)               /*!< TX_OVER (Bit 3)                                        */
#define I2C_TX_OVER_INT_EN_Msk                  (0x8UL)             /*!< TX_OVER (Bitfield-Mask: 0x01)                          */
#define I2C_TX_OVER_INT_EN                      I2C_TX_OVER_INT_EN_Msk
#define I2C_RX_FULL_INT_EN_Pos                  (2UL)               /*!< RX_FULL (Bit 2)                                        */
#define I2C_RX_FULL_INT_EN_Msk                  (0x4UL)             /*!< RX_FULL (Bitfield-Mask: 0x01)                          */
#define I2C_RX_FULL_INT_EN                      I2C_RX_FULL_INT_EN_Msk
#define I2C_RX_OVER_INT_EN_Pos                  (1UL)               /*!< RX_OVER (Bit 1)                                        */
#define I2C_RX_OVER_INT_EN_Msk                  (0x2UL)             /*!< RX_OVER (Bitfield-Mask: 0x01)                          */
#define I2C_RX_OVER_INT_EN                      I2C_RX_OVER_INT_EN_Msk
#define I2C_RX_UNDER_INT_EN_Pos                 (0UL)               /*!< RX_UNDER (Bit 0)                                       */
#define I2C_RX_UNDER_INT_EN_Msk                 (0x1UL)             /*!< RX_UNDER (Bitfield-Mask: 0x01)                         */
#define I2C_RX_UNDER_INT_EN                     I2C_RX_UNDER_INT_EN_Msk

/******************  Bit definition for RINTRST register  ***************/
#define I2C_SCL_STK_AT_LOW_RAW_INT_STA_Pos      (14UL)              /*!< SCL_STUCK_AT_LOW (Bit 14)                              */
#define I2C_SCL_STK_AT_LOW_RAW_INT_STA_Msk      (0x4000UL)          /*!< SCL_STUCK_AT_LOW (Bitfield-Mask: 0x01)                 */
#define I2C_SCL_STK_AT_LOW_RAW_INT_STA          I2C_SCL_STK_AT_LOW_RAW_INT_STA_Msk
#define I2C_MST_ON_HOLD_RAW_INT_STA_Pos         (13UL)              /*!< MST_ON_HOLD (Bit 13)                                   */
#define I2C_MST_ON_HOLD_RAW_INT_STA_Msk         (0x2000UL)          /*!< MST_ON_HOLD (Bitfield-Mask: 0x01)                      */
#define I2C_MST_ON_HOLD_RAW_INT_STA             I2C_MST_ON_HOLD_RAW_INT_STA_Msk
#define I2C_RESTART_DET_RAW_INT_STA_Pos         12UL)              /*!< RESTART_DET (Bit 12)                                    */
#define I2C_RESTART_DET_RAW_INT_STA_Msk         (0x1000UL)          /*!< RESTART_DET (Bitfield-Mask: 0x01)                      */
#define I2C_RESTART_DET_RAW_INT_STA             I2C_RESTART_DET_RAW_INT_STA_Msk
#define I2C_GEN_CALL_RAW_INT_STA_Pos            (11UL)              /*!< GEN_CALL (Bit 11)                                      */
#define I2C_GEN_CALL_RAW_INT_STA_Msk            (0x800UL)           /*!< GEN_CALL (Bitfield-Mask: 0x01)                         */
#define I2C_GEN_CALL_RAW_INT_STA                I2C_GEN_CALL_RAW_INT_STA_Msk
#define I2C_START_DET_RAW_INT_STA_Pos           (10UL)              /*!< START_DET (Bit 10)                                     */
#define I2C_START_DET_RAW_INT_STA_Msk           (0x400UL)           /*!< START_DET (Bitfield-Mask: 0x01)                        */
#define I2C_START_DET_RAW_INT_STA               I2C_START_DET_RAW_INT_STA_Msk
#define I2C_STOP_DET_RAW_INT_STA_Pos            (9UL)               /*!< STOP_DET (Bit 9)                                       */
#define I2C_STOP_DET_RAW_INT_STA_Msk            (0x200UL)           /*!< STOP_DET (Bitfield-Mask: 0x01)                         */
#define I2C_STOP_DET_RAW_INT_STA                I2C_STOP_DET_RAW_INT_STA_Msk
#define I2C_ACTIVITY_RAW_INT_STA_Pos            (8UL)               /*!< ACTIVITY (Bit 8)                                       */
#define I2C_ACTIVITY_RAW_INT_STA_Msk            (0x100UL)           /*!< ACTIVITY (Bitfield-Mask: 0x01)                         */
#define I2C_ACTIVITY_RAW_INT_STA                I2C_ACTIVITY_RAW_INT_STA_Msk
#define I2C_RX_DONE_RAW_INT_STA_Pos             (7UL)               /*!< RX_DONE (Bit 7)                                        */
#define I2C_RX_DONE_RAW_INT_STA_Msk             (0x80UL)            /*!< RX_DONE (Bitfield-Mask: 0x01)                          */
#define I2C_RX_DONE_RAW_INT_STA                 I2C_RX_DONE_RAW_INT_STA_Msk
#define I2C_TX_ABRT_RAW_INT_STA_Pos             (6UL)               /*!< TX_ABRT (Bit 6)                                        */
#define I2C_TX_ABRT_RAW_INT_STA_Msk             (0x40UL)            /*!< TX_ABRT (Bitfield-Mask: 0x01)                          */
#define I2C_TX_ABRT_RAW_INT_STA                 I2C_TX_ABRT_RAW_INT_STA_Msk
#define I2C_RD_REQ_RAW_INT_STA_Pos              (5UL)               /*!< RD_REQ (Bit 5)                                         */
#define I2C_RD_REQ_RAW_INT_STA_Msk              (0x20UL)            /*!< RD_REQ (Bitfield-Mask: 0x01)                           */
#define I2C_RD_REQ_RAW_INT_STA                  I2C_RD_REQ_RAW_INT_STA_Msk
#define I2C_TX_EMPTY_RAW_INT_STA_Pos            (4UL)               /*!< TX_EMPTY (Bit 4)                                       */
#define I2C_TX_EMPTY_RAW_INT_STA_Msk            (0x10UL)            /*!< TX_EMPTY (Bitfield-Mask: 0x01)                         */
#define I2C_TX_EMPTY_RAW_INT_STA                I2C_TX_EMPTY_RAW_INT_STA_Msk
#define I2C_TX_OVER_RAW_INT_STA_Pos             (3UL)               /*!< TX_OVER (Bit 3)                                        */
#define I2C_TX_OVER_RAW_INT_STA_Msk             (0x8UL)             /*!< TX_OVER (Bitfield-Mask: 0x01)                          */
#define I2C_TX_OVER_RAW_INT_STA                 I2C_TX_OVER_RAW_INT_STA_Msk
#define I2C_RX_FULL_RAW_INT_STA_Pos             (2UL)               /*!< RX_FULL (Bit 2)                                        */
#define I2C_RX_FULL_RAW_INT_STA_Msk             (0x4UL)             /*!< RX_FULL (Bitfield-Mask: 0x01)                          */
#define I2C_RX_FULL_RAW_INT_STA                 I2C_RX_FULL_RAW_INT_STA_Msk
#define I2C_RX_OVER_RAW_INT_STA_Pos             (1UL)               /*!< RX_OVER (Bit 1)                                        */
#define I2C_RX_OVER_RAW_INT_STA_Msk             (0x2UL)             /*!< RX_OVER (Bitfield-Mask: 0x01)                          */
#define I2C_RX_OVER_RAW_INT_STA                 I2C_RX_OVER_RAW_INT_STA_Msk
#define I2C_RX_UNDER_RAW_INT_STA_Pos            (0UL)               /*!< RX_UNDER (Bit 0)                                       */
#define I2C_RX_UNDER_RAW_INT_STA_Msk            (0x1UL)             /*!< RX_UNDER (Bitfield-Mask: 0x01)                         */
#define I2C_RX_UNDER_RAW_INT_STA                I2C_RX_UNDER_RAW_INT_STA_Msk

/**********************  Bit definition for RXTL register  *******************/
#define I2C_RX_TL_Pos                           (0UL)               /*!< RXTL (Bit 0)                                           */
#define I2C_RX_TL_Msk                           (0xffUL)            /*!< RXTL (Bitfield-Mask: 0xff)                             */
#define I2C_RX_TL                               I2C_RX_TL_Msk

/**********************  Bit definition for TXTL register  *******************/
#define I2C_TX_TL_Pos                           (0UL)               /*!< TXTL (Bit 0)                                           */
#define I2C_TX_TL_Msk                           (0xffUL)            /*!< TXTL (Bitfield-Mask: 0xff)                             */
#define I2C_TX_TL                               I2C_TX_TL_Msk

/*********************  Bit definition for INTRCR register  *****************/
#define I2C_CLR_INT_Pos                         (0UL)               /*!< INTRCR (Bit 0)                                         */
#define I2C_CLR_INT_Msk                         (0x1UL)             /*!< INTRCR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_INT                             I2C_CLR_INT_Msk

/*******************  Bit definition for RXUNCR register  ***************/
#define I2C_CLR_RX_UNDER_Pos                    (0UL)               /*!< RXUNCR (Bit 0)                                         */
#define I2C_CLR_RX_UNDER_Msk                    (0x1UL)             /*!< RXUNCR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_RX_UNDER                        I2C_CLR_RX_UNDER_Msk

/*******************  Bit definition for RXOVCR register  ****************/
#define I2C_CLR_RX_OVER_Pos                     (0UL)               /*!< RXOVCR (Bit 0)                                         */
#define I2C_CLR_RX_OVER_Msk                     (0x1UL)             /*!< RXOVCR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_RX_OVER                         I2C_CLR_RX_OVER_Msk

/*******************  Bit definition for TXOVCR register  ****************/
#define I2C_CLR_TX_OVER_Pos                     (0UL)               /*!< TXOVCR (Bit 0)                                         */
#define I2C_CLR_TX_OVER_Msk                     (0x1UL)             /*!< TXOVCR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_TX_OVER                         I2C_CLR_TX_OVER_Msk

/*******************  Bit definition for RDREQCR register  *****************/
#define I2C_CLR_RD_REQ_Pos                      (0UL)               /*!< RDREQCR (Bit 0)                                        */
#define I2C_CLR_RD_REQ_Msk                      (0x1UL)             /*!< RDREQCR (Bitfield-Mask: 0x01)                          */
#define I2C_CLR_RD_REQ                          I2C_CLR_RD_REQ_Msk

/*******************  Bit definition for TXABCR register  ****************/
#define I2C_CLR_TX_ABRT_Pos                     (0UL)               /*!< TXABCR (Bit 0)                                         */
#define I2C_CLR_TX_ABRT_Msk                     (0x1UL)             /*!< TXABCR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_TX_ABRT                         I2C_CLR_TX_ABRT_Msk

/*******************  Bit definition for RXDOCR register  ****************/
#define I2C_CLR_RX_DONE_Pos                     (0UL)               /*!< RXDOCR (Bit 0)                                         */
#define I2C_CLR_RX_DONE_Msk                     (0x1UL)             /*!< RXDOCR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_RX_DONE                         I2C_CLR_RX_DONE_Msk

/*******************  Bit definition for ACTICR register  ***************/
#define I2C_CLR_ACTIVITY_Pos                    (0UL)               /*!< ACTICR (Bit 0)                                         */
#define I2C_CLR_ACTIVITY_Msk                    (0x1UL)             /*!< ACTICR (Bitfield-Mask: 0x01)                           */
#define I2C_CLR_ACTIVITY                        I2C_CLR_ACTIVITY_Msk

/*******************  Bit definition for SPDETCR register  ***************/
#define I2C_CLR_STOP_DET_Pos                    (0UL)               /*!< SPDETCR (Bit 0)                                        */
#define I2C_CLR_STOP_DET_Msk                    (0x1UL)             /*!< SPDETCR (Bitfield-Mask: 0x01)                          */
#define I2C_CLR_STOP_DET                        I2C_CLR_STOP_DET_Msk

/*******************  Bit definition for STDETCR register  **************/
#define I2C_CLR_START_DET_Pos                   (0UL)               /*!< STDETCR (Bit 0)                                        */
#define I2C_CLR_START_DET_Msk                   (0x1UL)             /*!< STDETCR (Bitfield-Mask: 0x01)                          */
#define I2C_CLR_START_DET                       I2C_CLR_START_DET_Msk

/*******************  Bit definition for GCCR register  ***************/
#define I2C_CLR_GEN_CALL_Pos                    (0UL)               /*!< GCCR (Bit 0)                                           */
#define I2C_CLR_GEN_CALL_Msk                    (0x1UL)             /*!< GCCR (Bitfield-Mask: 0x01)                             */
#define I2C_CLR_GEN_CALL                        I2C_CLR_GEN_CALL_Msk

/**********************  Bit definition for ENABLE register  ******************/
#define I2C_SMBUS_ALERT_EN_Pos                  (18UL)              /*!< SMBUS_ALERT_EN (Bit 18)                                */
#define I2C_SMBUS_ALERT_EN_Msk                  (0x40000UL)         /*!< SMBUS_ALERT_EN (Bitfield-Mask: 0x01)                   */
#define I2C_SMBUS_ALERT_EN                      I2C_SMBUS_ALERT_EN_Msk
#define I2C_SMBUS_SUSPEND_EN_Pos                (17UL)              /*!< SMBUS_SUSPEND_EN (Bit 17)                              */
#define I2C_SMBUS_SUSPEND_EN_Msk                (0x20000UL)         /*!< SMBUS_SUSPEND_EN (Bitfield-Mask: 0x01)                 */
#define I2C_SMBUS_SUSPEND_EN                    I2C_SMBUS_SUSPEND_EN_Msk
#define I2C_SMBUS_CLK_RESET_Pos                 (16UL)              /*!< SMBUS_CLK_RESET (Bit 16)                               */
#define I2C_SMBUS_CLK_RESET_Msk                 (0x10000UL)         /*!< SMBUS_CLK_RESET (Bitfield-Mask: 0x01)                  */
#define I2C_SMBUS_CLK_RESET                     I2C_SMBUS_CLK_RESET_Msk
#define I2C_SDA_STK_RECOVERY_EN_Pos             (3UL)               /*!< SDA_STUCK_RECOVERY_ENABLE (Bit 3)                      */
#define I2C_SDA_STK_RECOVERY_EN_Msk             (0x8UL)             /*!< SDA_STUCK_RECOVERY_ENABLE (Bitfield-Mask: 0x01)        */
#define I2C_SDA_STK_RECOVERY_EN                 I2C_SDA_STK_RECOVERY_EN_Msk
#define I2C_TX_CMD_BLOCK_Pos                    (2UL)               /*!< TX_CMD_BLOCK (Bit 2)                                   */
#define I2C_TX_CMD_BLOCK_Msk                    (0x4UL)             /*!< TX_CMD_BLOCK (Bitfield-Mask: 0x01)                     */
#define I2C_TX_CMD_BLOCK                        I2C_TX_CMD_BLOCK_Msk
#define I2C_ABORT_Pos                           (1UL)               /*!< ABORT (Bit 1)                                          */
#define I2C_ABORT_Msk                           (0x2UL)             /*!< ABORT (Bitfield-Mask: 0x01)                            */
#define I2C_ABORT                               I2C_ABORT_Msk
#define I2C_ENABLE_Pos                          (0UL)               /*!< ENABLE (Bit 0)                                         */
#define I2C_ENABLE_Msk                          (0x1UL)             /*!< ENABLE (Bitfield-Mask: 0x01)                           */
#define I2C_ENABLE                              I2C_ENABLE_Msk

/**********************  Bit definition for STATUS register  ******************/
#define I2C_SMBUS_ALERT_STATUS_Pos              (20UL)              /*!< SMBUS_ALERT_STATUS (Bit 20)                            */
#define I2C_SMBUS_ALERT_STATUS_Msk              (0x100000UL)        /*!< SMBUS_ALERT_STATUS (Bitfield-Mask: 0x01)               */
#define I2C_SMBUS_ALERT_STATUS                  I2C_SMBUS_ALERT_STATUS_Msk
#define I2C_SMBUS_SUSPEND_STATUS_Pos            (19UL)              /*!< SMBUS_SUSPEND_STATUS (Bit 19)                          */
#define I2C_SMBUS_SUSPEND_STATUS_Msk            (0x80000UL)         /*!< SMBUS_SUSPEND_STATUS (Bitfield-Mask: 0x01)             */
#define I2C_SMBUS_SUSPEND_STATUS                I2C_SMBUS_SUSPEND_STATUS_Msk
#define I2C_SMBUS_SLV_ADDR_RESOLVED_Pos         (18UL)              /*!< SMBUS_SLAVE_ADDR_RESOLVED (Bit 18)                     */
#define I2C_SMBUS_SLV_ADDR_RESOLVED_Msk         (0x40000UL)         /*!< SMBUS_SLAVE_ADDR_RESOLVED (Bitfield-Mask: 0x01)        */
#define I2C_SMBUS_SLV_ADDR_RESOLVED             I2C_SMBUS_SLV_ADDR_RESOLVED_Msk
#define I2C_SMBUS_SLV_ADDR_VALID_Pos            (17UL)              /*!< SMBUS_SLAVE_ADDR_VALID (Bit 17)                        */
#define I2C_SMBUS_SLV_ADDR_VALID_Msk            (0x20000UL)         /*!< SMBUS_SLAVE_ADDR_VALID (Bitfield-Mask: 0x01)           */
#define I2C_SMBUS_SLV_ADDR_VALID                I2C_SMBUS_SLV_ADDR_VALID_Msk
#define I2C_SMBUS_QUICK_CMD_BIT_Pos             (16UL)              /*!< SMBUS_QUICK_CMD_BIT (Bit 16)                           */
#define I2C_SMBUS_QUICK_CMD_BIT_Msk             (0x10000UL)         /*!< SMBUS_QUICK_CMD_BIT (Bitfield-Mask: 0x01)              */
#define I2C_SMBUS_QUICK_CMD_BIT                 I2C_SMBUS_QUICK_CMD_BIT_Msk
#define I2C_SDA_STUCK_NOT_RECOVERED_Pos         (11UL)              /*!< SDA_STUCK_NOT_RECOVERED (Bit 11)                       */
#define I2C_SDA_STUCK_NOT_RECOVERED_Msk         (0x800UL)           /*!< SDA_STUCK_NOT_RECOVERED (Bitfield-Mask: 0x01)          */
#define I2C_SDA_STUCK_NOT_RECOVERED             I2C_SDA_STUCK_NOT_RECOVERED_Msk
#define I2C_SLV_HOLD_RX_FIFO_FULL_Pos           (10UL)              /*!< SLV_HOLD_RX_FIFO_FULL (Bit 10)                         */
#define I2C_SLV_HOLD_RX_FIFO_FULL_Msk           (0x400UL)           /*!< SLV_HOLD_RX_FIFO_FULL (Bitfield-Mask: 0x01)            */
#define I2C_SLV_HOLD_RX_FIFO_FULL               I2C_SLV_HOLD_RX_FIFO_FULL_Msk
#define I2C_SLV_HOLD_TX_FIFO_EMPTY_Pos          (9UL)               /*!< SLV_HOLD_TX_FIFO_EMPTY (Bit 9)                         */
#define I2C_SLV_HOLD_TX_FIFO_EMPTY_Msk          (0x200UL)           /*!< SLV_HOLD_TX_FIFO_EMPTY (Bitfield-Mask: 0x01)           */
#define I2C_SLV_HOLD_TX_FIFO_EMPTY              I2C_SLV_HOLD_TX_FIFO_EMPTY_Msk
#define I2C_MST_HOLD_RX_FIFO_FULL_Pos           (8UL)               /*!< MST_HOLD_RX_FIFO_FULL (Bit 8)                          */
#define I2C_MST_HOLD_RX_FIFO_FULL_Msk           (0x100UL)           /*!< MST_HOLD_RX_FIFO_FULL (Bitfield-Mask: 0x01)            */
#define I2C_MST_HOLD_RX_FIFO_FULL               I2C_MST_HOLD_RX_FIFO_FULL_Msk
#define I2C_MST_HOLD_TX_FIFO_EMPTY_Pos          (7UL)               /*!< MST_HOLD_TX_FIFO_EMPTY (Bit 7)                         */
#define I2C_MST_HOLD_TX_FIFO_EMPTY_Msk          (0x80UL)            /*!< MST_HOLD_TX_FIFO_EMPTY (Bitfield-Mask: 0x01)           */
#define I2C_MST_HOLD_TX_FIFO_EMPTY              I2C_MST_HOLD_TX_FIFO_EMPTY_Msk
#define I2C_SLV_ACTIVITY_Pos                    (6UL)               /*!< SLV_ACTIVITY (Bit 6)                                   */
#define I2C_SLV_ACTIVITY_Msk                    (0x40UL)            /*!< SLV_ACTIVITY (Bitfield-Mask: 0x01)                     */
#define I2C_SLV_ACTIVITY                        I2C_SLV_ACTIVITY_Msk
#define I2C_MST_ACTIVITY_Pos                    (5UL)               /*!< MST_ACTIVITY (Bit 5)                                   */
#define I2C_MST_ACTIVITY_Msk                    (0x20UL)            /*!< MST_ACTIVITY (Bitfield-Mask: 0x01)                     */
#define I2C_MST_ACTIVITY                        I2C_MST_ACTIVITY_Msk
#define I2C_RFF_Pos                             (4UL)               /*!< RFF (Bit 4)                                            */
#define I2C_RFF_Msk                             (0x10UL)            /*!< RFF (Bitfield-Mask: 0x01)                              */
#define I2C_RFF                                 I2C_RFF_Msk
#define I2C_RFNE_Pos                            (3UL)               /*!< RFNE (Bit 3)                                           */
#define I2C_RFNE_Msk                            (0x8UL)             /*!< RFNE (Bitfield-Mask: 0x01)                             */
#define I2C_RFNE                                I2C_RFNE_Msk
#define I2C_TFE_Pos                             (2UL)               /*!< TFE (Bit 2)                                            */
#define I2C_TFE_Msk                             (0x4UL)             /*!< TFE (Bitfield-Mask: 0x01)                              */
#define I2C_TFE                                 I2C_TFE_Msk
#define I2C_TFNF_Pos                            (1UL)               /*!< TFNF (Bit 1)                                           */
#define I2C_TFNF_Msk                            (0x2UL)             /*!< TFNF (Bitfield-Mask: 0x01)                             */
#define I2C_TFNF                                I2C_TFNF_Msk
#define I2C_ACTIVITY_Pos                        (0UL)               /*!< ACTIVITY (Bit 0)                                       */
#define I2C_ACTIVITY_Msk                        (0x1UL)             /*!< ACTIVITY (Bitfield-Mask: 0x01)                         */
#define I2C_ACTIVITY                            I2C_ACTIVITY_Msk

/**********************  Bit definition for TXFLR register  *******************/
#define I2C_TXFLR_Pos                           (0UL)               /*!< TXFLR (Bit 0)                                          */
#define I2C_TXFLR_Msk                           (0xfUL)             /*!< TXFLR (Bitfield-Mask: 0x0f)                            */
#define I2C_TXFLR                               I2C_TXFLR_Msk

/**********************  Bit definition for RXFLR register  *******************/
#define I2C_RXFLR_Pos                           (0UL)               /*!< RXFLR (Bit 0)                                          */
#define I2C_RXFLR_Msk                           (0xfUL)             /*!< RXFLR (Bitfield-Mask: 0x0f)                            */
#define I2C_RXFLR                               I2C_RXFLR_Msk

/*********************  Bit definition for SDA_HOLD register  *****************/
#define I2C_SDA_RX_HOLD_Pos                     (16UL)              /*!< IC_SDA_RX_HOLD (Bit 16)                                */
#define I2C_SDA_RX_HOLD_Msk                     (0xff0000UL)        /*!< IC_SDA_RX_HOLD (Bitfield-Mask: 0xff)                   */
#define I2C_SDA_RX_HOLD                         I2C_SDA_RX_HOLD_Msk
#define I2C_SDA_TX_HOLD_Pos                     (0UL)               /*!< IC_SDA_TX_HOLD (Bit 0)                                 */
#define I2C_SDA_TX_HOLD_Msk                     (0xffffUL)          /*!< IC_SDA_TX_HOLD (Bitfield-Mask: 0xffff)                 */
#define I2C_SDA_TX_HOLD                         I2C_SDA_TX_HOLD_Msk

/******************  Bit definition for TXABSR register  **************/
#define I2C_TX_FLUSH_CNT_Pos                    (23UL)              /*!< TX_FLUSH_CNT (Bit 23)                                  */
#define I2C_TX_FLUSH_CNT_Msk                    (0xff800000UL)      /*!< TX_FLUSH_CNT (Bitfield-Mask: 0x1ff)                    */
#define I2C_TX_FLUSH_CNT                        I2C_TX_FLUSH_CNT_Msk
#define I2C_ABRT_DEV_WRITE_Pos                  (20UL)              /*!< ABRT_DEVICE_WRITE (Bit 20)                             */
#define I2C_ABRT_DEV_WRITE_Msk                  (0x100000UL)        /*!< ABRT_DEVICE_WRITE (Bitfield-Mask: 0x01)                */
#define I2C_ABRT_DEV_WRITE                      I2C_ABRT_DEV_WRITE_Msk
#define I2C_ABRT_DEV_SLV_ADDR_NOACK_Pos         (19UL)              /*!< ABRT_DEVICE_SLVADDR_NOACK (Bit 19)                     */
#define I2C_ABRT_DEV_SLV_ADDR_NOACK_Msk         (0x80000UL)         /*!< ABRT_DEVICE_SLVADDR_NOACK (Bitfield-Mask: 0x01)        */
#define I2C_ABRT_DEV_SLV_ADDR_NOACK             I2C_ABRT_DEV_SLV_ADDR_NOACK_Msk
#define I2C_ABRT_DEV_NOACK_Pos                  (18UL)              /*!< ABRT_DEVICE_NOACK (Bit 18)                             */
#define I2C_ABRT_DEV_NOACK_Msk                  (0x40000UL)         /*!< ABRT_DEVICE_NOACK (Bitfield-Mask: 0x01)                */
#define I2C_ABRT_DEV_NOACK                      I2C_ABRT_DEV_NOACK_Msk
#define I2C_ABRT_SDA_STUCK_AT_LOW_Pos           (17UL)              /*!< ABRT_SDA_STUCK_AT_LOW (Bit 17)                         */
#define I2C_ABRT_SDA_STUCK_AT_LOW_Msk           (0x20000UL)         /*!< ABRT_SDA_STUCK_AT_LOW (Bitfield-Mask: 0x01)            */
#define I2C_ABRT_SDA_STUCK_AT_LOW               I2C_ABRT_SDA_STUCK_AT_LOW_Msk
#define I2C_ABRT_USER_ABRT_Pos                  (16UL)              /*!< ABRT_USER_ABRT (Bit 16)                                */
#define I2C_ABRT_USER_ABRT_Msk                  (0x10000UL)         /*!< ABRT_USER_ABRT (Bitfield-Mask: 0x01)                   */
#define I2C_ABRT_USER_ABRT                      I2C_ABRT_USER_ABRT_Msk
#define I2C_ABRT_SLVRD_INTX_Pos                 (15UL)              /*!< ABRT_SLVRD_INTX (Bit 15)                               */
#define I2C_ABRT_SLVRD_INTX_Msk                 (0x8000UL)          /*!< ABRT_SLVRD_INTX (Bitfield-Mask: 0x01)                  */
#define I2C_ABRT_SLVRD_INTX                     I2C_ABRT_SLVRD_INTX_Msk
#define I2C_ABRT_SLV_ARBLOST_Pos                (14UL)              /*!< ABRT_SLV_ARBLOST (Bit 14)                              */
#define I2C_ABRT_SLV_ARBLOST_Msk                (0x4000UL)          /*!< ABRT_SLV_ARBLOST (Bitfield-Mask: 0x01)                 */
#define I2C_ABRT_SLV_ARBLOST                    I2C_ABRT_SLV_ARBLOST_Msk
#define I2C_ABRT_SLVFLUSH_TXFIFO_Pos            (13UL)              /*!< ABRT_SLVFLUSH_TXFIFO (Bit 13)                          */
#define I2C_ABRT_SLVFLUSH_TXFIFO_Msk            (0x2000UL)          /*!< ABRT_SLVFLUSH_TXFIFO (Bitfield-Mask: 0x01)             */
#define I2C_ABRT_SLVFLUSH_TXFIFO                I2C_ABRT_SLVFLUSH_TXFIFO_Msk
#define I2C_ARB_LOST_Pos                        (12UL)              /*!< ARB_LOST (Bit 12)                                      */
#define I2C_ARB_LOST_Msk                        (0x1000UL)          /*!< ARB_LOST (Bitfield-Mask: 0x01)                         */
#define I2C_ARB_LOST                            I2C_ARB_LOST_Msk
#define I2C_ABRT_MASTER_DIS_Pos                 (11UL)              /*!< ABRT_MASTER_DIS (Bit 11)                               */
#define I2C_ABRT_MASTER_DIS_Msk                 (0x800UL)           /*!< ABRT_MASTER_DIS (Bitfield-Mask: 0x01)                  */
#define I2C_ABRT_MASTER_DIS                     I2C_ABRT_MASTER_DIS_Msk
#define I2C_ABRT_10B_RD_NORSTRT_Pos             (10UL)              /*!< ABRT_10B_RD_NORSTRT (Bit 10)                           */
#define I2C_ABRT_10B_RD_NORSTRT_Msk             (0x400UL)           /*!< ABRT_10B_RD_NORSTRT (Bitfield-Mask: 0x01)              */
#define I2C_ABRT_10B_RD_NORSTRT                 I2C_ABRT_10B_RD_NORSTRT_Msk
#define I2C_ABRT_SBYTE_NORSTRT_Pos              (9UL)               /*!< ABRT_SBYTE_NORSTRT (Bit 9)                             */
#define I2C_ABRT_SBYTE_NORSTRT_Msk              (0x200UL)           /*!< ABRT_SBYTE_NORSTRT (Bitfield-Mask: 0x01)               */
#define I2C_ABRT_SBYTE_NORSTRT                  I2C_ABRT_SBYTE_NORSTRT_Msk
#define I2C_ABRT_HS_NORSTRT_Pos                 (8UL)               /*!< ABRT_HS_NORSTRT (Bit 8)                                */
#define I2C_ABRT_HS_NORSTRT_Msk                 (0x100UL)           /*!< ABRT_HS_NORSTRT (Bitfield-Mask: 0x01)                  */
#define I2C_ABRT_HS_NORSTRT                     I2C_ABRT_HS_NORSTRT_Msk
#define I2C_ABRT_SBYTE_ACKDET_Pos               (7UL)               /*!< ABRT_SBYTE_ACKDET (Bit 7)                              */
#define I2C_ABRT_SBYTE_ACKDET_Msk               (0x80UL)            /*!< ABRT_SBYTE_ACKDET (Bitfield-Mask: 0x01)                */
#define I2C_ABRT_SBYTE_ACKDET                   I2C_ABRT_SBYTE_ACKDET_Msk
#define I2C_ABRT_HS_ACKDET_Pos                  (6UL)               /*!< ABRT_HS_ACKDET (Bit 6)                                 */
#define I2C_ABRT_HS_ACKDET_Msk                  (0x40UL)            /*!< ABRT_HS_ACKDET (Bitfield-Mask: 0x01)                   */
#define I2C_ABRT_HS_ACKDET                      I2C_ABRT_HS_ACKDET_Msk
#define I2C_ABRT_GCALL_READ_Pos                 (5UL)               /*!< ABRT_GCALL_READ (Bit 5)                                */
#define I2C_ABRT_GCALL_READ_Msk                 (0x20UL)            /*!< ABRT_GCALL_READ (Bitfield-Mask: 0x01)                  */
#define I2C_ABRT_GCALL_READ                     I2C_ABRT_GCALL_READ_Msk
#define I2C_ABRT_GCALL_NOACK_Pos                (4UL)               /*!< ABRT_GCALL_NOACK (Bit 4)                               */
#define I2C_ABRT_GCALL_NOACK_Msk                (0x10UL)            /*!< ABRT_GCALL_NOACK (Bitfield-Mask: 0x01)                 */
#define I2C_ABRT_GCALL_NOACK                    I2C_ABRT_GCALL_NOACK_Msk
#define I2C_ABRT_TXDATA_NOACK_Pos               (3UL)               /*!< ABRT_TXDATA_NOACK (Bit 3)                              */
#define I2C_ABRT_TXDATA_NOACK_Msk               (0x8UL)             /*!< ABRT_TXDATA_NOACK (Bitfield-Mask: 0x01)                */
#define I2C_ABRT_TXDATA_NOACK                   I2C_ABRT_TXDATA_NOACK_Msk
#define I2C_ABRT_10ADDR2_NOACK_Pos              (2UL)               /*!< ABRT_10ADDR2_NOACK (Bit 2)                             */
#define I2C_ABRT_10ADDR2_NOACK_Msk              (0x4UL)             /*!< ABRT_10ADDR2_NOACK (Bitfield-Mask: 0x01)               */
#define I2C_ABRT_10ADDR2_NOACK                  I2C_ABRT_10ADDR2_NOACK_Msk
#define I2C_ABRT_10ADDR1_NOACK_Pos              (1UL)               /*!< ABRT_10ADDR1_NOACK (Bit 1)                             */
#define I2C_ABRT_10ADDR1_NOACK_Msk              (0x2UL)             /*!< ABRT_10ADDR1_NOACK (Bitfield-Mask: 0x01)               */
#define I2C_ABRT_10ADDR1_NOACK                  I2C_ABRT_10ADDR1_NOACK_Msk
#define I2C_ABRT_7B_ADDR_NOACK_Pos              (0UL)               /*!< ABRT_7B_ADDR_NOACK (Bit 0)                             */
#define I2C_ABRT_7B_ADDR_NOACK_Msk              (0x1UL)             /*!< ABRT_7B_ADDR_NOACK (Bitfield-Mask: 0x01)               */
#define I2C_ABRT_7B_ADDR_NOACK                  I2C_ABRT_7B_ADDR_NOACK_Msk

/****************  Bit definition for NACKEN register  ************/
#define I2C_SLV_DATA_NACK_Pos                   (0UL)               /*!< NACK (Bit 0)                                           */
#define I2C_SLV_DATA_NACK_Msk                   (0x1UL)             /*!< NACK (Bitfield-Mask: 0x01)                             */
#define I2C_SLV_DATA_NACK                       I2C_SLV_DATA_NACK_Msk

/**********************  Bit definition for DMACT register  ******************/
#define I2C_DMA_TDMAE_Pos                       (1UL)               /*!< TDMAE (Bit 1)                                          */
#define I2C_DMA_TDMAE_Msk                       (0x2UL)             /*!< TDMAE (Bitfield-Mask: 0x01)                            */
#define I2C_DMA_TDMAE                           I2C_DMA_TDMAE_Msk
#define I2C_DMA_RDMAE_Pos                       (0UL)               /*!< RDMAE (Bit 0)                                          */
#define I2C_DMA_RDMAE_Msk                       (0x1UL)             /*!< RDMAE (Bitfield-Mask: 0x01)                            */
#define I2C_DMA_RDMAE                           I2C_DMA_RDMAE_Msk

/*********************  Bit definition for DMATDLR register  *****************/
#define I2C_DMA_DMATDL_Pos                      (0UL)               /*!< DMATDL (Bit 0)                                         */
#define I2C_DMA_DMATDL_Msk                      (0xfUL)             /*!< DMATDL (Bitfield-Mask: 0x0f)                           */
#define I2C_DMA_DMATDL                          I2C_DMA_DMATDL_Msk

/*********************  Bit definition for DMARDLR register  *****************/
#define I2C_DMA_DMARDL_Pos                      (0UL)               /*!< DMARDL (Bit 0)                                         */
#define I2C_DMA_DMARDL_Msk                      (0xfUL)             /*!< DMARDL (Bitfield-Mask: 0x0f)                           */
#define I2C_DMA_DMARDL                          I2C_DMA_DMARDL_Msk

/*********************  Bit definition for SDA_SETUP register  ****************/
#define I2C_SDA_SETUP_Pos                       (0UL)               /*!< SDA_SETUP (Bit 0)                                      */
#define I2C_SDA_SETUP_Msk                       (0xffUL)            /*!< SDA_SETUP (Bitfield-Mask: 0xff)                        */
#define I2C_SDA_SETUP                           I2C_SDA_SETUP_Msk

/*****************  Bit definition for GCACK register  *************/
#define I2C_ACK_GEN_CALL_Pos                    (0UL)               /*!< ACK_GEN_CALL (Bit 0)                                   */
#define I2C_ACK_GEN_CALL_Msk                    (0x1UL)             /*!< ACK_GEN_CALL (Bitfield-Mask: 0x01)                     */
#define I2C_ACK_GEN_CALL                        I2C_ACK_GEN_CALL_Msk

/*******************  Bit definition for ENST register  **************/
#define I2C_SLV_RX_DATA_LOST_Pos                (2UL)               /*!< SLV_RX_DATA_LOST (Bit 2)                               */
#define I2C_SLV_RX_DATA_LOST_Msk                (0x4UL)             /*!< SLV_RX_DATA_LOST (Bitfield-Mask: 0x01)                 */
#define I2C_SLV_RX_DATA_LOST                    I2C_SLV_RX_DATA_LOST_Msk
#define I2C_SLVDIS_WHILEBUSY_Pos                (1UL)               /*!< SLV_DISABLED_WHILE_BUSY (Bit 1)                        */
#define I2C_SLVDIS_WHILEBUSY_Msk                (0x2UL)             /*!< SLV_DISABLED_WHILE_BUSY (Bitfield-Mask: 0x01)          */
#define I2C_SLVDIS_WHILEBUSY                    I2C_SLVDIS_WHILEBUSY_Msk
#define I2C_EN_Pos                              (0UL)               /*!< IC_EN (Bit 0)                                          */
#define I2C_EN_Msk                              (0x1UL)             /*!< IC_EN (Bitfield-Mask: 0x01)                            */
#define I2C_EN                                  I2C_EN_Msk

/*********************  Bit definition for FS_SPKLEN register  ****************/
#define I2C_FS_SPKLEN_Pos                       (0UL)               /*!< IC_FS_SPKLEN (Bit 0)                                   */
#define I2C_FS_SPKLEN_Msk                       (0xffUL)            /*!< IC_FS_SPKLEN (Bitfield-Mask: 0xff)                     */
#define I2C_FS_SPKLEN                           I2C_FS_SPKLEN_Msk

/******************  Bit definition for RSDETCR register  *************/
#define I2C_CLR_RESTART_DET_Pos                 (0UL)               /*!< RSDETCR (Bit 0)                                        */
#define I2C_CLR_RESTART_DET_Msk                 (0x1UL)             /*!< RSDETCR (Bitfield-Mask: 0x01)                          */
#define I2C_CLR_RESTART_DET                     I2C_CLR_RESTART_DET_Msk

/**************  Bit definition for SCLLTO register  ********/
#define I2C_SCL_STK_LOW_TIMEOUT_Pos             (0UL)               /*!< IC_SCL_STUCK_LOW_TIMEOUT (Bit 0)                       */
#define I2C_SCL_STK_LOW_TIMEOUT_Msk             (0xffffffffUL)      /*!< IC_SCL_STUCK_LOW_TIMEOUT (Bitfield-Mask: 0xffffffff)   */
#define I2C_SCL_STK_LOW_TIMEOUT                 I2C_SCL_STK_LOW_TIMEOUT_Msk

/**************  Bit definition for SDALTO register  ********/
#define I2C_SDA_STK_LOW_TIMEOUT_Pos             (0UL)               /*!< IC_SDA_STUCK_LOW_TIMEOUT (Bit 0)                       */
#define I2C_SDA_STK_LOW_TIMEOUT_Msk             (0xffffffffUL)      /*!< IC_SDA_STUCK_LOW_TIMEOUT (Bitfield-Mask: 0xffffffff)   */
#define I2C_SDA_STK_LOW_TIMEOUT                 I2C_SDA_STK_LOW_TIMEOUT_Msk

/*****************  Bit definition for SSTDETCR register  ************/
#define I2C_CLR_SCL_STK_Pos                     (0UL)               /*!< CLR_SCL_STUCK (Bit 0)                                  */
#define I2C_CLR_SCL_STK_Msk                     (0x1UL)             /*!< CLR_SCL_STUCK (Bitfield-Mask: 0x01)                    */
#define I2C_CLR_SCL_STK                         I2C_CLR_SCL_STK_Msk

/*********************  Bit definition for DEVICE_ID register  ****************/
#define I2C_DEV_ID_Pos                          (0UL)               /*!< DEVICE_ID (Bit 0)                                      */
#define I2C_DEV_ID_Msk                          (0xffffffUL)        /*!< DEVICE_ID (Bitfield-Mask: 0xffffff)                    */
#define I2C_DEV_ID                              I2C_DEV_ID_Msk

/****************  Bit definition for TSEXT register  **********/
#define I2C_SMBUS_CLK_LOW_SEXT_TIMEOUT_Pos      (0UL)               /*!< SMBUS_CLK_LOW_SEXT_TIMEOUT (Bit 0)                     */
#define I2C_SMBUS_CLK_LOW_SEXT_TIMEOUT_Msk      (0xffffffffUL)      /*!< SMBUS_CLK_LOW_SEXT_TIMEOUT (Bitfield-Mask: 0xffffffff) */
#define I2C_SMBUS_CLK_LOW_SEXT_TIMEOUT          I2C_SMBUS_CLK_LOW_SEXT_TIMEOUT_Msk

/****************  Bit definition for TMEXT register  **********/
#define I2C_SMBUS_CLK_LOW_MEXT_TIMEOUT_Pos      (0UL)               /*!< SMBUS_CLK_LOW_MEXT_TIMEOUT (Bit 0)                     */
#define I2C_SMBUS_CLK_LOW_MEXT_TIMEOUT_Msk      (0xffffffffUL)      /*!< SMBUS_CLK_LOW_MEXT_TIMEOUT (Bitfield-Mask: 0xffffffff) */
#define I2C_SMBUS_CLK_LOW_MEXT_TIMEOUT          I2C_SMBUS_CLK_LOW_MEXT_TIMEOUT_Msk

/************  Bit definition for IDCNT register  ********/
#define I2C_SMBUS_THIGH_MAX_BUS_IDLE_CNT_Pos    (0UL)               /*!< SMBUS_THIGH_MAX_BUS_IDLE_CNT (Bit 0)                   */
#define I2C_SMBUS_THIGH_MAX_BUS_IDLE_CNT_Msk    (0xffffUL)          /*!< SMBUS_THIGH_MAX_BUS_IDLE_CNT (Bitfield-Mask: 0xffff)   */
#define I2C_SMBUS_THIGH_MAX_BUS_IDLE_CNT        I2C_SMBUS_THIGH_MAX_BUS_IDLE_CNT_Msk

/******************  Bit definition for SMINTRST register  *************/
#define I2C_SMBUS_ALERT_DET_INT_STA_Pos         (10UL)              /*!< R_SMBUS_ALERT_DET (Bit 10)                             */
#define I2C_SMBUS_ALERT_DET_INT_STA_Msk         (0x400UL)           /*!< R_SMBUS_ALERT_DET (Bitfield-Mask: 0x01)                */
#define I2C_SMBUS_ALERT_DET_INT_STA             I2C_SMBUS_ALERT_DET_INT_STA_Msk
#define I2C_SMBUS_SUSPEND_DET_INT_STA_Pos       (9UL)               /*!< R_SMBUS_SUSPEND_DET (Bit 9)                            */
#define I2C_SMBUS_SUSPEND_DET_INT_STA_Msk       (0x200UL)           /*!< R_SMBUS_SUSPEND_DET (Bitfield-Mask: 0x01)              */
#define I2C_SMBUS_SUSPEND_DET_INT_STA           I2C_SMBUS_SUSPEND_DET_INT_STA_Msk
#define I2C_SLV_RX_PEC_NACK_INT_STA_Pos         (8UL)               /*!< R_SLV_RX_PEC_NACK (Bit 8)                              */
#define I2C_SLV_RX_PEC_NACK_INT_STA_Msk         (0x100UL)           /*!< R_SLV_RX_PEC_NACK (Bitfield-Mask: 0x01)                */
#define I2C_SLV_RX_PEC_NACK_INT_STA             I2C_SLV_RX_PEC_NACK_INT_STA_Msk
#define I2C_ARP_ASSGN_ADDR_CMD_DET_INT_STA_Pos  (7UL)               /*!< R_ARP_ASSGN_ADDR_CMD_DET (Bit 7)                       */
#define I2C_ARP_ASSGN_ADDR_CMD_DET_INT_STA_Msk  (0x80UL)            /*!< R_ARP_ASSGN_ADDR_CMD_DET (Bitfield-Mask: 0x01)         */
#define I2C_ARP_ASSGN_ADDR_CMD_DET_INT_STA      I2C_ARP_ASSGN_ADDR_CMD_DET_INT_STA_Msk
#define I2C_ARP_GET_UDID_CMD_DET_INT_STA_Pos    (6UL)               /*!< R_ARP_GET_UDID_CMD_DET (Bit 6)                         */
#define I2C_ARP_GET_UDID_CMD_DET_INT_STA_Msk    (0x40UL)            /*!< R_ARP_GET_UDID_CMD_DET (Bitfield-Mask: 0x01)           */
#define I2C_ARP_GET_UDID_CMD_DET_INT_STA        I2C_ARP_GET_UDID_CMD_DET_INT_STA_Msk
#define I2C_ARP_RST_CMD_DET_INT_STA_Pos         (5UL)               /*!< R_ARP_RST_CMD_DET (Bit 5)                              */
#define I2C_ARP_RST_CMD_DET_INT_STA_Msk         (0x20UL)            /*!< R_ARP_RST_CMD_DET (Bitfield-Mask: 0x01)                */
#define I2C_ARP_RST_CMD_DET_INT_STA             I2C_ARP_RST_CMD_DET_INT_STA_Msk
#define I2C_ARP_PREPARE_CMD_DET_INT_STA_Pos     (4UL)               /*!< R_ARP_PREPARE_CMD_DET (Bit 4)                          */
#define I2C_ARP_PREPARE_CMD_DET_INT_STA_Msk     (0x10UL)            /*!< R_ARP_PREPARE_CMD_DET (Bitfield-Mask: 0x01)            */
#define I2C_ARP_PREPARE_CMD_DET_INT_STA         I2C_ARP_PREPARE_CMD_DET_INT_STA_Msk
#define I2C_HOST_NOTIFY_MST_DET_INT_STA_Pos     (3UL)               /*!< R_HOST_NOTIFY_MST_DET (Bit 3)                          */
#define I2C_HOST_NOTIFY_MST_DET_INT_STA_Msk     (0x8UL)             /*!< R_HOST_NOTIFY_MST_DET (Bitfield-Mask: 0x01)            */
#define I2C_HOST_NOTIFY_MST_DET_INT_STA         I2C_HOST_NOTIFY_MST_DET_INT_STA_Msk
#define I2C_QUICK_CMD_DET_INT_STA_Pos           (2UL)               /*!< R_QUICK_CMD_DET (Bit 2)                                */
#define I2C_QUICK_CMD_DET_INT_STA_Msk           (0x4UL)             /*!< R_QUICK_CMD_DET (Bitfield-Mask: 0x01)                  */
#define I2C_QUICK_CMD_DET_INT_STA               I2C_QUICK_CMD_DET_INT_STA_Msk
#define I2C_MST_CLK_EXTND_TIMEOUT_INT_STA_Pos   (1UL)               /*!< R_MST_CLOCK_EXTND_TIMEOUT (Bit 1)                      */
#define I2C_MST_CLK_EXTND_TIMEOUT_INT_STA_Msk   (0x2UL)             /*!< R_MST_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)        */
#define I2C_MST_CLK_EXTND_TIMEOUT_INT_STA       I2C_MST_CLK_EXTND_TIMEOUT_INT_STA_Msk
#define I2C_SLV_CLK_EXTND_TIMEOUT_INT_STA_Pos   (0UL)               /*!< R_SLV_CLOCK_EXTND_TIMEOUT (Bit 0)                      */
#define I2C_SLV_CLK_EXTND_TIMEOUT_INT_STA_Msk   (0x1UL)             /*!< R_SLV_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)        */
#define I2C_SLV_CLK_EXTND_TIMEOUT_INT_STA       I2C_SLV_CLK_EXTND_TIMEOUT_INT_STA_Msk

/******************  Bit definition for SMINTRMS register  *************/
#define I2C_SMBUS_ALERT_DET_INT_EN_Pos          (10UL)              /*!< R_SMBUS_ALERT_DET (Bit 10)                             */
#define I2C_SMBUS_ALERT_DET_INT_EN_Msk          (0x400UL)           /*!< R_SMBUS_ALERT_DET (Bitfield-Mask: 0x01)                */
#define I2C_SMBUS_ALERT_DET_INT_EN              I2C_SMBUS_ALERT_DET_INT_EN_Msk
#define I2C_SMBUS_SUSPEND_DET_INT_EN_Pos        (9UL)               /*!< R_SMBUS_SUSPEND_DET (Bit 9)                            */
#define I2C_SMBUS_SUSPEND_DET_INT_EN_Msk        (0x200UL)           /*!< R_SMBUS_SUSPEND_DET (Bitfield-Mask: 0x01)              */
#define I2C_SMBUS_SUSPEND_DET_INT_EN            I2C_SMBUS_SUSPEND_DET_INT_EN_Msk
#define I2C_SLV_RX_PEC_NACK_INT_EN_Pos          (8UL)               /*!< R_SLV_RX_PEC_NACK (Bit 8)                              */
#define I2C_SLV_RX_PEC_NACK_INT_EN_Msk          (0x100UL)           /*!< R_SLV_RX_PEC_NACK (Bitfield-Mask: 0x01)                */
#define I2C_SLV_RX_PEC_NACK_INT_EN              I2C_SLV_RX_PEC_NACK_INT_EN_Msk
#define I2C_ARP_ASSGN_ADDR_CMD_DET_INT_EN_Pos   (7UL)               /*!< R_ARP_ASSGN_ADDR_CMD_DET (Bit 7)                       */
#define I2C_ARP_ASSGN_ADDR_CMD_DET_INT_EN_Msk   (0x80UL)            /*!< R_ARP_ASSGN_ADDR_CMD_DET (Bitfield-Mask: 0x01)         */
#define I2C_ARP_ASSGN_ADDR_CMD_DET_INT_EN       I2C_ARP_ASSGN_ADDR_CMD_DET_INT_EN_Msk
#define I2C_ARP_GET_UDID_CMD_DET_INT_EN_Pos     (6UL)               /*!< R_ARP_GET_UDID_CMD_DET (Bit 6)                         */
#define I2C_ARP_GET_UDID_CMD_DET_INT_EN_Msk     (0x40UL)            /*!< R_ARP_GET_UDID_CMD_DET (Bitfield-Mask: 0x01)           */
#define I2C_ARP_GET_UDID_CMD_DET_INT_EN         I2C_ARP_GET_UDID_CMD_DET_INT_EN_Msk
#define I2C_ARP_RST_CMD_DET_INT_EN_Pos          (5UL)               /*!< R_ARP_RST_CMD_DET (Bit 5)                              */
#define I2C_ARP_RST_CMD_DET_INT_EN_Msk          (0x20UL)            /*!< R_ARP_RST_CMD_DET (Bitfield-Mask: 0x01)                */
#define I2C_ARP_RST_CMD_DET_INT_EN              I2C_ARP_RST_CMD_DET_INT_EN_Msk
#define I2C_ARP_PREPARE_CMD_DET_INT_EN_Pos      (4UL)               /*!< R_ARP_PREPARE_CMD_DET (Bit 4)                          */
#define I2C_ARP_PREPARE_CMD_DET_INT_EN_Msk      (0x10UL)            /*!< R_ARP_PREPARE_CMD_DET (Bitfield-Mask: 0x01)            */
#define I2C_ARP_PREPARE_CMD_DET_INT_EN          I2C_ARP_PREPARE_CMD_DET_INT_EN_Msk
#define I2C_HOST_NOTIFY_MST_DET_INT_EN_Pos      (3UL)               /*!< R_HOST_NOTIFY_MST_DET (Bit 3)                          */
#define I2C_HOST_NOTIFY_MST_DET_INT_EN_Msk      (0x8UL)             /*!< R_HOST_NOTIFY_MST_DET (Bitfield-Mask: 0x01)            */
#define I2C_HOST_NOTIFY_MST_DET_INT_EN          I2C_HOST_NOTIFY_MST_DET_INT_EN_Msk
#define I2C_QUICK_CMD_DET_INT_EN_Pos            (2UL)               /*!< R_QUICK_CMD_DET (Bit 2)                                */
#define I2C_QUICK_CMD_DET_INT_EN_Msk            (0x4UL)             /*!< R_QUICK_CMD_DET (Bitfield-Mask: 0x01)                  */
#define I2C_QUICK_CMD_DET_INT_EN                I2C_QUICK_CMD_DET_INT_EN_Msk
#define I2C_MST_CLK_EXTND_TIMEOUT_INT_EN_Pos    (1UL)               /*!< R_MST_CLOCK_EXTND_TIMEOUT (Bit 1)                      */
#define I2C_MST_CLK_EXTND_TIMEOUT_INT_EN_Msk    (0x2UL)             /*!< R_MST_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)        */
#define I2C_MST_CLK_EXTND_TIMEOUT_INT_EN        I2C_MST_CLK_EXTND_TIMEOUT_INT_EN_Msk
#define I2C_SLV_CLK_EXTND_TIMEOUT_INT_EN_Pos    (0UL)               /*!< R_SLV_CLOCK_EXTND_TIMEOUT (Bit 0)                      */
#define I2C_SLV_CLK_EXTND_TIMEOUT_INT_EN_Msk    (0x1UL)             /*!< R_SLV_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)        */
#define I2C_SLV_CLK_EXTND_TIMEOUT_INT_EN        I2C_SLV_CLK_EXTND_TIMEOUT_INT_EN_Msk

/****************  Bit definition for SMINTRRST register  ***********/
#define I2C_SMBUS_ALERT_DET_RAW_INT_STA_Pos         (10UL)          /*!< R_SMBUS_ALERT_DET (Bit 10)                             */
#define I2C_SMBUS_ALERT_DET_RAW_INT_STA_Msk         (0x400UL)       /*!< R_SMBUS_ALERT_DET (Bitfield-Mask: 0x01)                */
#define I2C_SMBUS_ALERT_DET_RAW_INT_STA             I2C_SMBUS_ALERT_DET_RAW_INT_STA_Msk
#define I2C_SMBUS_SUSPEND_DET_RAW_INT_STA_Pos       (9UL)           /*!< R_SMBUS_SUSPEND_DET (Bit 9)                            */
#define I2C_SMBUS_SUSPEND_DET_RAW_INT_STA_Msk       (0x200UL)       /*!< R_SMBUS_SUSPEND_DET (Bitfield-Mask: 0x01)              */
#define I2C_SMBUS_SUSPEND_DET_RAW_INT_STA           I2C_SMBUS_SUSPEND_DET_RAW_INT_STA_Msk
#define I2C_SLV_RX_PEC_NACK_RAW_INT_STA_Pos         (8UL)           /*!< R_SLV_RX_PEC_NACK (Bit 8)                              */
#define I2C_SLV_RX_PEC_NACK_RAW_INT_STA_Msk         (0x100UL)       /*!< R_SLV_RX_PEC_NACK (Bitfield-Mask: 0x01)                */
#define I2C_SLV_RX_PEC_NACK_RAW_INT_STA             I2C_SLV_RX_PEC_NACK_RAW_INT_STA_Msk
#define I2C_ARP_ASSGN_ADDR_CMD_DET_RAW_INT_STA_Pos  (7UL)           /*!< R_ARP_ASSGN_ADDR_CMD_DET (Bit 7)                       */
#define I2C_ARP_ASSGN_ADDR_CMD_DET_RAW_INT_STA_Msk  (0x80UL)        /*!< R_ARP_ASSGN_ADDR_CMD_DET (Bitfield-Mask: 0x01)         */
#define I2C_ARP_ASSGN_ADDR_CMD_DET_RAW_INT_STA      I2C_ARP_ASSGN_ADDR_CMD_DET_RAW_INT_STA_Msk
#define I2C_ARP_GET_UDID_CMD_DET_RAW_INT_STA_Pos    (6UL)           /*!< R_ARP_GET_UDID_CMD_DET (Bit 6)                         */
#define I2C_ARP_GET_UDID_CMD_DET_RAW_INT_STA_Msk    (0x40UL)        /*!< R_ARP_GET_UDID_CMD_DET (Bitfield-Mask: 0x01)           */
#define I2C_ARP_GET_UDID_CMD_DET_RAW_INT_STA        I2C_ARP_GET_UDID_CMD_DET_RAW_INT_STA_Msk
#define I2C_ARP_RST_CMD_DET_RAW_INT_STA_Pos         (5UL)           /*!< R_ARP_RST_CMD_DET (Bit 5)                              */
#define I2C_ARP_RST_CMD_DET_RAW_INT_STA_Msk         (0x20UL)        /*!< R_ARP_RST_CMD_DET (Bitfield-Mask: 0x01)                */
#define I2C_ARP_RST_CMD_DET_RAW_INT_STA             I2C_ARP_RST_CMD_DET_RAW_INT_STA_Msk
#define I2C_ARP_PREPARE_CMD_DET_RAW_INT_STA_Pos     (4UL)           /*!< R_ARP_PREPARE_CMD_DET (Bit 4)                          */
#define I2C_ARP_PREPARE_CMD_DET_RAW_INT_STA_Msk     (0x10UL)        /*!< R_ARP_PREPARE_CMD_DET (Bitfield-Mask: 0x01)            */
#define I2C_ARP_PREPARE_CMD_DET_RAW_INT_STA         I2C_ARP_PREPARE_CMD_DET_RAW_INT_STA_Msk
#define I2C_HOST_NOTIFY_MST_DET_RAW_INT_STA_Pos     (3UL)           /*!< R_HOST_NOTIFY_MST_DET (Bit 3)                          */
#define I2C_HOST_NOTIFY_MST_DET_RAW_INT_STA_Msk     (0x8UL)         /*!< R_HOST_NOTIFY_MST_DET (Bitfield-Mask: 0x01)            */
#define I2C_HOST_NOTIFY_MST_DET_RAW_INT_STA         I2C_HOST_NOTIFY_MST_DET_RAW_INT_STA_Msk
#define I2C_QUICK_CMD_DET_RAW_INT_STA_Pos           (2UL)           /*!< R_QUICK_CMD_DET (Bit 2)                                */
#define I2C_QUICK_CMD_DET_RAW_INT_STA_Msk           (0x4UL)         /*!< R_QUICK_CMD_DET (Bitfield-Mask: 0x01)                  */
#define I2C_QUICK_CMD_DET_RAW_INT_STA               I2C_QUICK_CMD_DET_RAW_INT_STA_Msk
#define I2C_MST_CLK_EXTND_TIMEOUT_RAW_INT_STA_Pos   (1UL)           /*!< R_MST_CLOCK_EXTND_TIMEOUT (Bit 1)                      */
#define I2C_MST_CLK_EXTND_TIMEOUT_RAW_INT_STA_Msk   (0x2UL)         /*!< R_MST_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)        */
#define I2C_MST_CLK_EXTND_TIMEOUT_RAW_INT_STA       I2C_MST_CLK_EXTND_TIMEOUT_RAW_INT_STA_Msk
#define I2C_SLV_CLK_EXTND_TIMEOUT_RAW_INT_STA_Pos   (0UL)           /*!< R_SLV_CLOCK_EXTND_TIMEOUT (Bit 0)                      */
#define I2C_SLV_CLK_EXTND_TIMEOUT_RAW_INT_STA_Msk   (0x1UL)         /*!< R_SLV_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)        */
#define I2C_SLV_CLK_EXTND_TIMEOUT_RAW_INT_STA       I2C_SLV_CLK_EXTND_TIMEOUT_RAW_INT_STA_Msk

/******************  Bit definition for SMINTRCR register  **************/
#define I2C_CLR_SMBUS_ALERT_DET_Pos             (10UL)              /*!< CLR_SMBUS_ALERT_DET (Bit 10)                           */
#define I2C_CLR_SMBUS_ALERT_DET_Msk             (0x400UL)           /*!< CLR_SMBUS_ALERT_DET (Bitfield-Mask: 0x01)              */
#define I2C_CLR_SMBUS_ALERT_DET                 I2C_CLR_SMBUS_ALERT_DET_Msk
#define I2C_CLR_SMBUS_SUSPEND_DET_Pos           (9UL)               /*!< CLR_SMBUS_SUSPEND_DET (Bit 9)                          */
#define I2C_CLR_SMBUS_SUSPEND_DET_Msk           (0x200UL)           /*!< CLR_SMBUS_SUSPEND_DET (Bitfield-Mask: 0x01)            */
#define I2C_CLR_SMBUS_SUSPEND_DET               I2C_CLR_SMBUS_SUSPEND_DET_Msk
#define I2C_CLR_SLV_RX_PEC_NACK_Pos             (8UL)               /*!< CLR_SLV_RX_PEC_NACK (Bit 8)                            */
#define I2C_CLR_SLV_RX_PEC_NACK_Msk             (0x100UL)           /*!< CLR_SLV_RX_PEC_NACK (Bitfield-Mask: 0x01)              */
#define I2C_CLR_SLV_RX_PEC_NACK                 I2C_CLR_SLV_RX_PEC_NACK_Msk
#define I2C_CLR_ARP_ASSGN_ADDR_CMD_DET_Pos      (7UL)               /*!< CLR_ARP_ASSGN_ADDR_CMD_DET (Bit 7)                     */
#define I2C_CLR_ARP_ASSGN_ADDR_CMD_DET_Msk      (0x80UL)            /*!< CLR_ARP_ASSGN_ADDR_CMD_DET (Bitfield-Mask: 0x01)       */
#define I2C_CLR_ARP_ASSGN_ADDR_CMD_DET          I2C_CLR_ARP_ASSGN_ADDR_CMD_DET_Msk
#define I2C_CLR_ARP_GET_UDID_CMD_DET_Pos        (6UL)               /*!< CLR_ARP_GET_UDID_CMD_DET (Bit 6)                       */
#define I2C_CLR_ARP_GET_UDID_CMD_DET_Msk        (0x40UL)            /*!< CLR_ARP_GET_UDID_CMD_DET (Bitfield-Mask: 0x01)         */
#define I2C_CLR_ARP_GET_UDID_CMD_DET            I2C_CLR_ARP_GET_UDID_CMD_DET_Msk
#define I2C_CLR_ARP_RST_CMD_DET_Pos             (5UL)               /*!< CLR_ARP_RST_CMD_DET (Bit 5)                            */
#define I2C_CLR_ARP_RST_CMD_DET_Msk             (0x20UL)            /*!< CLR_ARP_RST_CMD_DET (Bitfield-Mask: 0x01)              */
#define I2C_CLR_ARP_RST_CMD_DET                 I2C_CLR_ARP_RST_CMD_DET_Msk
#define I2C_CLR_ARP_PREPARE_CMD_DET_Pos         (4UL)               /*!< CLR_ARP_PREPARE_CMD_DET (Bit 4)                        */
#define I2C_CLR_ARP_PREPARE_CMD_DET_Msk         (0x10UL)            /*!< CLR_ARP_PREPARE_CMD_DET (Bitfield-Mask: 0x01)          */
#define I2C_CLR_ARP_PREPARE_CMD_DET             I2C_CLR_ARP_PREPARE_CMD_DET_Msk
#define I2C_CLR_HOST_NOTIFY_MST_DET_Pos         (3UL)               /*!< CLR_HOST_NOTIFY_MST_DET (Bit 3)                        */
#define I2C_CLR_HOST_NOTIFY_MST_DET_Msk         (0x8UL)             /*!< CLR_HOST_NOTIFY_MST_DET (Bitfield-Mask: 0x01)          */
#define I2C_CLR_HOST_NOTIFY_MST_DET             I2C_CLR_HOST_NOTIFY_MST_DET_Msk
#define I2C_CLR_QUICK_CMD_DET_Pos               (2UL)               /*!< CLR_QUICK_CMD_DET (Bit 2)                              */
#define I2C_CLR_QUICK_CMD_DET_Msk               (0x4UL)             /*!< CLR_QUICK_CMD_DET (Bitfield-Mask: 0x01)                */
#define I2C_CLR_QUICK_CMD_DET                   I2C_CLR_QUICK_CMD_DET_Msk
#define I2C_CLR_MST_CLOCK_EXTND_TIMEOUT_Pos     (1UL)               /*!< CLR_MST_CLOCK_EXTND_TIMEOUT (Bit 1)                    */
#define I2C_CLR_MST_CLOCK_EXTND_TIMEOUT_Msk     (0x2UL)             /*!< CLR_MST_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)      */
#define I2C_CLR_MST_CLOCK_EXTND_TIMEOUT         I2C_CLR_MST_CLOCK_EXTND_TIMEOUT_Msk
#define I2C_CLR_SLV_CLOCK_EXTND_TIMEOUT_Pos     (0UL)               /*!< CLR_SLV_CLOCK_EXTND_TIMEOUT (Bit 0)                    */
#define I2C_CLR_SLV_CLOCK_EXTND_TIMEOUT_Msk     (0x1UL)             /*!< CLR_SLV_CLOCK_EXTND_TIMEOUT (Bitfield-Mask: 0x01)      */
#define I2C_CLR_SLV_CLOCK_EXTND_TIMEOUT         I2C_CLR_SLV_CLOCK_EXTND_TIMEOUT_Msk

/*******************  Bit definition for SAROP register  ***************/
#define I2C_OPTIONAL_SAR_Pos                    (0UL)               /*!< IC_OPTIONAL_SAR (Bit 0)                                */
#define I2C_OPTIONAL_SAR_Msk                    (0x7fUL)            /*!< IC_OPTIONAL_SAR (Bitfield-Mask: 0x7f)                  */
#define I2C_OPTIONAL_SAR                        I2C_OPTIONAL_SAR_Msk

/******************  Bit definition for UDIDLSB register  **************/
#define I2C_SMBUS_ARP_UDID_LSB_Pos              (0UL)               /*!< IC_SMBUS_ARP_UDID_LSB (Bit 0)                          */
#define I2C_SMBUS_ARP_UDID_LSB_Msk              (0xffffffffUL)      /*!< IC_SMBUS_ARP_UDID_LSB (Bitfield-Mask: 0xffffffff)      */
#define I2C_SMBUS_ARP_UDID_LSB                  I2C_SMBUS_ARP_UDID_LSB_Msk


/******************************************************************************/
/*                                                                            */
/*                                     CAN                                    */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for CFG_STAT register  ********************/
#define CAN_RESET_Pos                       (7UL)           /*!< RESET request bit (Bit 7)                                      */
#define CAN_RESET_Msk                       (0x80UL)        /*!< RESET request bit (Bitfield-Mask: 0x01)                        */
#define CAN_RESET                           CAN_RESET_Msk
#define CAN_LOOP_BACK_EXTERNAL_Pos          (6UL)           /*!< Loop Back Mode, External (Bit 6)                               */
#define CAN_LOOP_BACK_EXTERNAL_Msk          (0x40UL)        /*!< Loop Back Mode, External (Bitfield-Mask: 0x01)                 */
#define CAN_LOOP_BACK_EXTERNAL              CAN_LOOP_BACK_EXTERNAL_Msk
#define CAN_LOOP_BACK_INTERNAL_Pos          (5UL)           /*!< Loop Back Mode, Internal (Bit 5)                               */
#define CAN_LOOP_BACK_INTERNAL_Msk          (0x20UL)        /*!< Loop Back Mode, Internal (Bitfield-Mask: 0x01)                 */
#define CAN_LOOP_BACK_INTERNAL              CAN_LOOP_BACK_INTERNAL_Msk
#define CAN_TX_PRI_SINGLE_SHOT_Pos          (4UL)           /*!< Transmission Primary Single Shot mode (Bit 4)                  */
#define CAN_TX_PRI_SINGLE_SHOT_Msk          (0x10UL)        /*!< Transmission Primary Single Shot mode (Bitfield-Mask: 0x01)    */
#define CAN_TX_PRI_SINGLE_SHOT              CAN_TX_PRI_SINGLE_SHOT_Msk
#define CAN_TX_SEC_SINGLE_SHOT_Pos          (3UL)           /*!< Transmission Secondary Single Shot mode (Bit 3)                */
#define CAN_TX_SEC_SINGLE_SHOT_Msk          (0x8UL)         /*!< Transmission Secondary Single Shot mode (Bitfield-Mask: 0x01)  */
#define CAN_TX_SEC_SINGLE_SHOT              CAN_TX_SEC_SINGLE_SHOT_Msk
#define CAN_RX_ACT_Pos                      (2UL)           /*!< Reception ACTIVE  (Bit 2)                                      */
#define CAN_RX_ACT_Msk                      (0x4UL)         /*!< Reception ACTIVE  (Bitfield-Mask: 0x01)                        */
#define CAN_RX_ACT                          CAN_RX_ACT_Msk
#define CAN_TX_ACT_Pos                      (1UL)           /*!< Transmission ACTIVE (Bit 1)                                    */
#define CAN_TX_ACT_Msk                      (0x2UL)         /*!< Transmission ACTIVE (Bitfield-Mask: 0x01)                      */
#define CAN_TX_ACT                          CAN_TX_ACT_Msk
#define CAN_BUS_OFF_Pos                     (0UL)           /*!< Bus Off (Bit 0)                                                */
#define CAN_BUS_OFF_Msk                     (0x1UL)         /*!< Bus Off (Bitfield-Mask: 0x01)                                  */
#define CAN_BUS_OFF                         CAN_BUS_OFF_Msk

/*********************  Bit definition for TCMD register  *********************/
#define CAN_TX_BUF_SEL_Pos                  (7UL)           /*!< Transmit Buffer Select (Bit 7)                                 */
#define CAN_TX_BUF_SEL_Msk                  (0x80UL)        /*!< Transmit Buffer Select (Bitfield-Mask: 0x01)                   */
#define CAN_TX_BUF_SEL                      CAN_TX_BUF_SEL_Msk
#define CAN_LISTEN_ONLY_Pos                 (6UL)           /*!< Listen Only Mode (Bit 6)                                       */
#define CAN_LISTEN_ONLY_Msk                 (0x40UL)        /*!< Listen Only Mode (Bitfield-Mask: 0x01)                         */
#define CAN_LISTEN_ONLY                     CAN_LISTEN_ONLY_Msk
#define CAN_TX_STANDBY_Pos                  (5UL)           /*!< Transceiver Standby Mode (Bit 5)                               */
#define CAN_TX_STANDBY_Msk                  (0x20UL)        /*!< Transceiver Standby Mode (Bitfield-Mask: 0x01)                 */
#define CAN_TX_STANDBY                      CAN_TX_STANDBY_Msk
#define CAN_TX_PRI_EN_Pos                   (4UL)           /*!< Transmit Primary Enable (Bit 4)                                */
#define CAN_TX_PRI_EN_Msk                   (0x10UL)        /*!< Transmit Primary Enable (Bitfield-Mask: 0x01)                  */
#define CAN_TX_PRI_EN                       CAN_TX_PRI_EN_Msk
#define CAN_TX_PRI_ABORT_Pos                (3UL)           /*!< Transmit Primary Abort (Bit 3)                                 */
#define CAN_TX_PRI_ABORT_Msk                (0x8UL)         /*!< Transmit Primary Abort (Bitfield-Mask: 0x01)                   */
#define CAN_TX_PRI_ABORT                    CAN_TX_PRI_ABORT_Msk
#define CAN_TX_SEC_ONE_Pos                  (2UL)           /*!< Transmit Secondary ONE frame (Bit 2)                           */
#define CAN_TX_SEC_ONE_Msk                  (0x4UL)         /*!< Transmit Secondary ONE frame (Bitfield-Mask: 0x01)             */
#define CAN_TX_SEC_ONE                      CAN_TX_SEC_ONE_Msk
#define CAN_TX_SEC_ALL_Pos                  (1UL)           /*!< Transmit Secondary ALL frame (Bit 1)                           */
#define CAN_TX_SEC_ALL_Msk                  (0x2UL)         /*!< Transmit Secondary ALL frame (Bitfield-Mask: 0x01)             */
#define CAN_TX_SEC_ALL                      CAN_TX_SEC_ALL_Msk
#define CAN_TX_SEC_ABORT_Pos                (0UL)           /*!< Transmit Secondary Abort (Bit 0)                               */
#define CAN_TX_SEC_ABORT_Msk                (0x1UL)         /*!< Transmit Secondary Abort (Bitfield-Mask: 0x01)                 */
#define CAN_TX_SEC_ABORT                    CAN_TX_SEC_ABORT_Msk

/********************  Bit definition for TCTRL register  *********************/
#define CAN_FD_ISO_Pos                      (7UL)           /*!< CAN FD ISO mode (Bit 7)                                        */
#define CAN_FD_ISO_Msk                      (0x80UL)        /*!< CAN FD ISO mode (Bitfield-Mask: 0x01)                          */
#define CAN_FD_ISO                          CAN_FD_ISO_Msk
#define CAN_TX_SEC_NEXT_Pos                 (6UL)           /*!< Transmit buffer Secondary NEXT (Bit 6)                         */
#define CAN_TX_SEC_NEXT_Msk                 (0x40UL)        /*!< Transmit buffer Secondary NEXT (Bitfield-Mask: 0x01)           */
#define CAN_TX_SEC_NEXT                     CAN_TX_SEC_NEXT_Msk
#define CAN_TX_SEC_STA_Pos                  (0UL)           /*!< Transmission Secondary Status bits (Bit 0)                     */
#define CAN_TX_SEC_STA_Msk                  (0x1fUL)        /*!< Transmission Secondary Status  bits (Bitfield-Mask: 0x1f)      */
#define CAN_TX_SEC_STA                      CAN_TX_SEC_STA_Msk

/********************  Bit definition for RCTRL register  *********************/
#define CAN_RX_BUF_OVER_Pos                 (5UL)           /*!< Receive buffer Overflow (Bit 5)                                */
#define CAN_RX_BUF_OVER_Msk                 (0x20UL)        /*!< Receive buffer Overflow (Bitfield-Mask: 0x01)                  */
#define CAN_RX_BUF_OVER                     CAN_RX_BUF_OVER_Msk
#define CAN_RX_BUF_REL_Pos                  (4UL)           /*!< Receive buffer Release (Bit 4)                                 */
#define CAN_RX_BUF_REL_Msk                  (0x10UL)        /*!< Receive buffer Release (Bitfield-Mask: 0x01)                   */
#define CAN_RX_BUF_REL                      CAN_RX_BUF_REL_Msk
#define CAN_RX_BUF_STA_Pos                  (0UL)           /*!< Receive buffer Status (Bit 0)                                  */
#define CAN_RX_BUF_STA_Msk                  (0x3UL)         /*!< Receive buffer Status (Bitfield-Mask: 0x3)                     */
#define CAN_RX_BUF_STA                      CAN_RX_BUF_STA_Msk

/********************  Bit definition for RTIE register  **********************/
#define CAN_RX_INT_EN_Pos                   (7UL)           /*!< Receive Interrupt Enable (Bit 7)                               */
#define CAN_RX_INT_EN_Msk                   (0x80UL)        /*!< Receive Interrupt Enable (Bitfield-Mask: 0x01)                 */
#define CAN_RX_INT_EN                       CAN_RX_INT_EN_Msk
#define CAN_RX_BUF_OVER_INT_EN_Pos          (6UL)           /*!< RB Overrun Interrupt Enable (Bit 6)                            */
#define CAN_RX_BUF_OVER_INT_EN_Msk          (0x40UL)        /*!< RB Overrun Interrupt Enable (Bitfield-Mask: 0x01)              */
#define CAN_RX_BUF_OVER_INT_EN              CAN_RX_BUF_OVER_INT_EN_Msk
#define CAN_RX_BUF_FULL_INT_EN_Pos          (5UL)           /*!< RB Full Interrupt Enable (Bit 5)                               */
#define CAN_RX_BUF_FULL_INT_EN_Msk          (0x20UL)        /*!< RB Full Interrupt Enable (Bitfield-Mask: 0x01)                 */
#define CAN_RX_BUF_FULL_INT_EN              CAN_RX_BUF_FULL_INT_EN_Msk
#define CAN_RX_BUF_ALMOST_FULL_INT_EN_Pos   (4UL)           /*!< RB Almost Full Interrupt Enable (Bit 4)                        */
#define CAN_RX_BUF_ALMOST_FULL_INT_EN_Msk   (0x10UL)        /*!< RB Almost Full Interrupt Enable (Bitfield-Mask: 0x01)          */
#define CAN_RX_BUF_ALMOST_FULL_INT_EN       CAN_RX_BUF_ALMOST_FULL_INT_EN_Msk
#define CAN_TX_PRI_INT_EN_Pos               (3UL)           /*!< Transmission Primary Interrupt Enable (Bit 3)                  */
#define CAN_TX_PRI_INT_EN_Msk               (0x8UL)         /*!< Transmission Primary Interrupt Enable (Bitfield-Mask: 0x01)    */
#define CAN_TX_PRI_INT_EN                   CAN_TX_PRI_INT_EN_Msk
#define CAN_TX_SEC_INT_EN_Pos               (2UL)           /*!< Transmission Secondary Interrupt Enable (Bit 2)                */
#define CAN_TX_SEC_INT_EN_Msk               (0x4UL)         /*!< Transmission Secondary Interrupt Enable (Bitfield-Mask: 0x01)  */
#define CAN_TX_SEC_INT_EN                   CAN_TX_SEC_INT_EN_Msk
#define CAN_ERR_INT_EN_Pos                  (1UL)           /*!< Error Interrupt Enable (Bit 1)                                 */
#define CAN_ERR_INT_EN_Msk                  (0x2UL)         /*!< Error Interrupt Enable (Bitfield-Mask: 0x01)                   */
#define CAN_ERR_INT_EN                      CAN_ERR_INT_EN_Msk
#define CAN_TX_SEC_BUF_FULL_Pos             (0UL)           /*!< Transmit Secondary buffer Full Flag (Bit 0)                    */
#define CAN_TX_SEC_BUF_FULL_Msk             (0x1UL)         /*!< Transmit Secondary buffer Full Flag (Bitfield-Mask: 0x01)      */
#define CAN_TX_SEC_BUF_FULL                 CAN_TX_SEC_BUF_FULL_Msk

/********************  Bit definition for RTIF register  **********************/
#define CAN_RX_INT_STA_Pos                  (7UL)           /*!< Receive Interrupt Status (Bit 7)                               */
#define CAN_RX_INT_STA_Msk                  (0x80UL)        /*!< Receive Interrupt Status (Bitfield-Mask: 0x01)                 */
#define CAN_RX_INT_STA                      CAN_RX_INT_STA_Msk
#define CAN_RX_BUF_OVER_INT_STA_Pos         (6UL)           /*!< RB Overrun Interrupt Status (Bit 6)                            */
#define CAN_RX_BUF_OVER_INT_STA_Msk         (0x40UL)        /*!< RB Overrun Interrupt Status (Bitfield-Mask: 0x01)              */
#define CAN_RX_BUF_OVER_INT_STA             CAN_RX_BUF_OVER_INT_STA_Msk
#define CAN_RX_BUF_FULL_INT_STA_Pos         (5UL)           /*!< RB Full Interrupt Status (Bit 5)                               */
#define CAN_RX_BUF_FULL_INT_STA_Msk         (0x20UL)        /*!< RB Full Interrupt Status (Bitfield-Mask: 0x01)                 */
#define CAN_RX_BUF_FULL_INT_STA             CAN_RX_BUF_FULL_INT_STA_Msk
#define CAN_RX_BUF_ALMOST_FULL_INT_STA_Pos  (4UL)           /*!< RB Almost Full Interrupt Status (Bit 4)                        */
#define CAN_RX_BUF_ALMOST_FULL_INT_STA_Msk  (0x10UL)        /*!< RB Almost Full Interrupt Status (Bitfield-Mask: 0x01)          */
#define CAN_RX_BUF_ALMOST_FULL_INT_STA      CAN_RX_BUF_ALMOST_FULL_INT_STA_Msk
#define CAN_TX_PRI_INT_STA_Pos              (3UL)           /*!< Transmission Primary Interrupt Status (Bit 3)                  */
#define CAN_TX_PRI_INT_STA_Msk              (0x8UL)         /*!< Transmission Primary Interrupt Status (Bitfield-Mask: 0x01)    */
#define CAN_TX_PRI_INT_STA                  CAN_TX_PRI_INT_STA_Msk
#define CAN_TX_SEC_INT_STA_Pos              (2UL)           /*!< Transmission Secondary Interrupt Status (Bit 2)                */
#define CAN_TX_SEC_INT_STA_Msk              (0x4UL)         /*!< Transmission Secondary Interrupt Status (Bitfield-Mask: 0x01)  */
#define CAN_TX_SEC_INT_STA                  CAN_TX_SEC_INT_STA_Msk
#define CAN_ERR_INT_STA_Pos                 (1UL)           /*!< Error Interrupt Status (Bit 1)                                 */
#define CAN_ERR_INT_STA_Msk                 (0x2UL)         /*!< Error Interrupt Status (Bitfield-Mask: 0x01)                   */
#define CAN_ERR_INT_STA                     CAN_ERR_INT_STA_Msk
#define CAN_ABORT_INT_STA_Pos               (0UL)           /*!< Abort Interrupt Flag (Bit 0)                                   */
#define CAN_ABORT_INT_STA_Msk               (0x1UL)         /*!< Abort Interrupt Flag (Bitfield-Mask: 0x01)                     */
#define CAN_ABORT_INT_STA                   CAN_ABORT_INT_STA_Msk

/*******************  Bit definition for ERRINT register  *********************/
#define CAN_ERR_WARN_LIMIT_REACHED_Pos      (7UL)           /*!< Error WARNing limit reached (Bit 7)                            */
#define CAN_ERR_WARN_LIMIT_REACHED_Msk      (0x80UL)        /*!< Error WARNing limit reached (Bitfield-Mask: 0x01)              */
#define CAN_ERR_WARN_LIMIT_REACHED          CAN_ERR_WARN_LIMIT_REACHED_Msk
#define CAN_ERR_PASS_ACT_Pos                (6UL)           /*!< Error Passive mode active (Bit 6)                              */
#define CAN_ERR_PASS_ACT_Msk                (0x40UL)        /*!< Error Passive mode active (Bitfield-Mask: 0x01)                */
#define CAN_ERR_PASS_ACT                    CAN_ERR_PASS_ACT_Msk
#define CAN_ERR_PASS_INT_EN_Pos             (5UL)           /*!< Error Passive Interrupt Enable (Bit 5)                         */
#define CAN_ERR_PASS_INT_EN_Msk             (0x20UL)        /*!< Error Passive Interrupt Enable (Bitfield-Mask: 0x01)           */
#define CAN_ERR_PASS_INT_EN                 CAN_ERR_PASS_INT_EN_Msk
#define CAN_ERR_PASS_INT_STA_Pos            (4UL)           /*!< Error Passive Interrupt Flag (Bit 4)                           */
#define CAN_ERR_PASS_INT_STA_Msk            (0x10UL)        /*!< Error Passive Interrupt Flag (Bitfield-Mask: 0x01)             */
#define CAN_ERR_PASS_INT_STA                CAN_ERR_PASS_INT_STA_Msk
#define CAN_ARB_LOST_INT_EN_Pos             (3UL)           /*!< Arbitration Lost Interrupt Enable (Bit 3)                      */
#define CAN_ARB_LOST_INT_EN_Msk             (0x8UL)         /*!< Arbitration Lost Interrupt Enable (Bitfield-Mask: 0x01)        */
#define CAN_ARB_LOST_INT_EN                 CAN_ARB_LOST_INT_EN_Msk
#define CAN_ARB_LOST_INT_STA_Pos            (2UL)           /*!< Arbitration Lost Interrupt Flag (Bit 2)                        */
#define CAN_ARB_LOST_INT_STA_Msk            (0x4UL)         /*!< Arbitration Lost Interrupt Flag (Bitfield-Mask: 0x01)          */
#define CAN_ARB_LOST_INT_STA                CAN_ARB_LOST_INT_STA_Msk
#define CAN_BUS_ERR_INT_EN_Pos              (1UL)           /*!< Bus Error Interrupt Enable (Bit 1)                             */
#define CAN_BUS_ERR_INT_EN_Msk              (0x2UL)         /*!< Bus Error Interrupt Enable (Bitfield-Mask: 0x01)               */
#define CAN_BUS_ERR_INT_EN                  CAN_BUS_ERR_INT_EN_Msk
#define CAN_BUS_ERR_INT_STA_Pos             (0UL)           /*!< Bus Error Interrupt Flag (Bit 0)                               */
#define CAN_BUS_ERR_INT_STA_Msk             (0x1UL)         /*!< Bus Error Interrupt Flag (Bitfield-Mask: 0x01)                 */
#define CAN_BUS_ERR_INT_STA                 CAN_BUS_ERR_INT_STA_Msk

/********************  Bit definition for LIMIT register  *********************/
#define CAN_RX_BUF_ALMOST_FULL_LIMIT_Pos    (4UL)           /*!< Receive buffer Almost Full Warning Limit (Bit 4)               */
#define CAN_RX_BUF_ALMOST_FULL_LIMIT_Msk    (0xf0UL)        /*!< Receive buffer Almost Full Warning Limit (Bitfield-Mask: 0x0f) */
#define CAN_RX_BUF_ALMOST_FULL_LIMIT        CAN_RX_BUF_ALMOST_FULL_LIMIT_Msk
#define CAN_ERR_WARN_LIMIT_Pos              (0UL)           /*!< Programmable Error Warning Limit (Bit 0)                       */
#define CAN_ERR_WARN_LIMIT_Msk              (0xfUL)         /*!< Programmable Error Warning Limit (Bitfield-Mask: 0xf)          */
#define CAN_ERR_WARN_LIMIT                  CAN_ERR_WARN_LIMIT_Msk

/*******************  Bit definition for BITTIME0 register  *******************/
#define CAN_FS_SYNC_JUMP_WIDTH_Pos          (6UL)           /*!< Synchronization Jump Width (fast speed) (Bit 6)                */
#define CAN_FS_SYNC_JUMP_WIDTH_Msk          (0xc0UL)        /*!< Synchronization Jump Width (fast speed) (Bitfield-Mask: 0x03)  */
#define CAN_FS_SYNC_JUMP_WIDTH              CAN_FS_SYNC_JUMP_WIDTH_Msk
#define CAN_SS_SEG1_Pos                     (0UL)           /*!< Bit Timing Segment 1 (slow speed) (Bit 0)                      */
#define CAN_SS_SEG1_Msk                     (0x3fUL)        /*!< Bit Timing Segment 1 (slow speed) (Bitfield-Mask: 0x3f)        */
#define CAN_SS_SEG1                         CAN_SS_SEG1_Msk

/*******************  Bit definition for BITTIME1 register  *******************/
#define CAN_FS_SEG2_Pos                     (5UL)           /*!< Bit Timing Segment 2 (fast speed) (Bit 5)                      */
#define CAN_FS_SEG2_Msk                     (0xe0UL)        /*!< Bit Timing Segment 2 (fast speed) (Bitfield-Mask: 0x07)        */
#define CAN_FS_SEG2                         CAN_FS_SEG2_Msk
#define CAN_SS_SEG2_Pos                     (0UL)           /*!< Bit Timing Segment 2 (slow speed) (Bit 0)                      */
#define CAN_SS_SEG2_Msk                     (0x1fUL)        /*!< Bit Timing Segment 2 (slow speed) (Bitfield-Mask: 0x1f)        */
#define CAN_SS_SEG2                         CAN_SS_SEG2_Msk

/*******************  Bit definition for BITTIME2 register  *******************/
#define CAN_FS_SEG1_Pos                     (4UL)           /*!< Bit Timing Segment 1 (fast speed) (Bit 4)                      */
#define CAN_FS_SEG1_Msk                     (0xf0UL)        /*!< Bit Timing Segment 1 (fast speed) (Bitfield-Mask: 0x0f)        */
#define CAN_FS_SEG1                         CAN_FS_SEG1_Msk
#define CAN_SS_SYNC_JUMP_WIDTH_Pos          (0UL)           /*!< Synchronization Jump Width (slow speed) (Bit 0)                */
#define CAN_SS_SYNC_JUMP_WIDTH_Msk          (0xfUL)         /*!< Synchronization Jump Width (slow speed) (Bitfield-Mask: 0x0f)  */
#define CAN_SS_SYNC_JUMP_WIDTH              CAN_SS_SYNC_JUMP_WIDTH_Msk

/*******************  Bit definition for S_PRESC register  ********************/
#define CAN_SS_PRESCALER_Pos                (0UL)           /*!< Prescaler (slow speed) (Bit 0)                                 */
#define CAN_SS_PRESCALER_Msk                (0xffUL)        /*!< Prescaler (slow speed) (Bitfield-Mask: 0xff)                   */
#define CAN_SS_PRESCALER                    CAN_SS_PRESCALER_Msk

/*******************  Bit definition for F_PRESC register  ********************/
#define CAN_FS_PRESCALER_Pos                (0UL)           /*!< Prescaler (fast speed) (Bit 0)                                 */
#define CAN_FS_PRESCALER_Msk                (0xffUL)        /*!< Prescaler (fast speed) (Bitfield-Mask: 0xff)                   */
#define CAN_FS_PRESCALER                    CAN_FS_PRESCALER_Msk

/*********************  Bit definition for TDC register  **********************/
#define CAN_TX_DELAY_COMP_EN_Pos            (7UL)           /*!< Transmitter Delay Compensation Enable (Bit 7)                  */
#define CAN_TX_DELAY_COMP_EN_Msk            (0x80UL)        /*!< Transmitter Delay Compensation Enable (Bitfield-Mask: 0x01)    */
#define CAN_TX_DELAY_COMP_EN                CAN_TX_DELAY_COMP_EN_Msk
#define CAN_SEC_SAMPLE_POINT_OFFSET_Pos     (0UL)           /*!< Secondary Sample Point OFFset (Bit 0)                          */
#define CAN_SEC_SAMPLE_POINT_OFFSET_Msk     (0x1fUL)        /*!< Secondary Sample Point OFFset (Bitfield-Mask: 0x1f)            */
#define CAN_SEC_SAMPLE_POINT_OFFSET         CAN_SEC_SAMPLE_POINT_OFFSET_Msk

/********************  Bit definition for EALCAP register  ********************/
#define CAN_ERR_CODE_Pos                    (5UL)           /*!< Kind Of ERror (Error code) (Bit 5)                             */
#define CAN_ERR_CODE_Msk                    (0xeUL)         /*!< Kind Of ERror (Error code) (Bitfield-Mask: 0x7)                */
#define CAN_ERR_CODE                        CAN_ERR_CODE_Msk
#define CAN_ARB_LOST_CAPTURE_Pos            (0UL)           /*!< Arbitration Lost Capture (Bit 0)                               */
#define CAN_ARB_LOST_CAPTURE_Msk            (0x1fUL)        /*!< Arbitration Lost Capture (Bitfield-Mask: 0x1f)                 */
#define CAN_ARB_LOST_CAPTURE                CAN_ARB_LOST_CAPTURE_Msk

/********************  Bit definition for RECNT register  *********************/
#define CAN_RX_ERR_CNT_Pos                  (0UL)           /*!< Receive Error Count (Bit 0)                                    */
#define CAN_RX_ERR_CNT_Msk                  (0xffUL)        /*!< Receive Error Count (Bitfield-Mask: 0xff)                      */
#define CAN_RX_ERR_CNT                      CAN_RX_ERR_CNT_Msk

/********************  Bit definition for TECNT register  *********************/
#define CAN_TX_ERR_CNT_Pos                  (0UL)           /*!< Transmit Error Count (Bit 0)                                   */
#define CAN_TX_ERR_CNT_Msk                  (0xffUL)        /*!< Transmit Error Count (Bitfield-Mask: 0xff)                     */
#define CAN_TX_ERR_CNT                      CAN_TX_ERR_CNT_Msk

/*******************  Bit definition for ACFCTRL register  ********************/
#define CAN_ACPT_FIL_CONTENT_SEL_Pos        (5UL)           /*!< Acceptance filter Content Select (Bit 5)                       */
#define CAN_ACPT_FIL_CONTENT_SEL_Msk        (0x20UL)        /*!< Acceptance filter Content Select (Bitfield-Mask: 0x01)         */
#define CAN_ACPT_FIL_CONTENT_SEL            CAN_ACPT_FIL_CONTENT_SEL_Msk
#define CAN_ACPT_FIL_ADDR_Pos               (0UL)           /*!< acceptance filter address (Bit 0)                              */
#define CAN_ACPT_FIL_ADDR_Msk               (0xfUL)         /*!< acceptance filter address (Bitfield-Mask: 0xf)                 */
#define CAN_ACPT_FIL_ADDR                   CAN_ACPT_FIL_ADDR_Msk

/*******************  Bit definition for ACF_EN_0 register  *******************/
#define CAN_ACPT_FIL7_EN_Pos                (7UL)           /*!< Acceptance filter 7 Enable (Bit 7)                             */
#define CAN_ACPT_FIL7_EN_Msk                (0x80UL)        /*!< Acceptance filter 7 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL7_EN                    CAN_ACPT_FIL7_EN_Msk
#define CAN_ACPT_FIL6_EN_Pos                (6UL)           /*!< Acceptance filter 6 Enable (Bit 6)                             */
#define CAN_ACPT_FIL6_EN_Msk                (0x40UL)        /*!< Acceptance filter 6 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL6_EN                    CAN_ACPT_FIL6_EN_Msk
#define CAN_ACPT_FIL5_EN_Pos                (5UL)           /*!< Acceptance filter 5 Enable (Bit 5)                             */
#define CAN_ACPT_FIL5_EN_Msk                (0x20UL)        /*!< Acceptance filter 5 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL5_EN                    CAN_ACPT_FIL5_EN_Msk
#define CAN_ACPT_FIL4_EN_Pos                (4UL)           /*!< Acceptance filter 4 Enable (Bit 4)                             */
#define CAN_ACPT_FIL4_EN_Msk                (0x10UL)        /*!< Acceptance filter 4 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL4_EN                    CAN_ACPT_FIL4_EN_Msk
#define CAN_ACPT_FIL3_EN_Pos                (3UL)           /*!< Acceptance filter 3 Enable (Bit 3)                             */
#define CAN_ACPT_FIL3_EN_Msk                (0x8UL)         /*!< Acceptance filter 3 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL3_EN                    CAN_ACPT_FIL3_EN_Msk
#define CAN_ACPT_FIL2_EN_Pos                (2UL)           /*!< Acceptance filter 2 Enable (Bit 2)                             */
#define CAN_ACPT_FIL2_EN_Msk                (0x4UL)         /*!< Acceptance filter 2 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL2_EN                    CAN_ACPT_FIL2_EN_Msk
#define CAN_ACPT_FIL1_EN_Pos                (1UL)           /*!< Acceptance filter 1 Enable (Bit 1)                             */
#define CAN_ACPT_FIL1_EN_Msk                (0x2UL)         /*!< Acceptance filter 1 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL1_EN                    CAN_ACPT_FIL1_EN_Msk
#define CAN_ACPT_FIL0_EN_Pos                (0UL)           /*!< Acceptance filter 0 Enable (Bit 0)                             */
#define CAN_ACPT_FIL0_EN_Msk                (0x1UL)         /*!< Acceptance filter 0 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL0_EN                    CAN_ACPT_FIL0_EN_Msk

/*******************  Bit definition for ACF_EN_1 register  *******************/
#define CAN_ACPT_FIL15_EN_Pos               (7UL)           /*!< Acceptance filter 15 Enable (Bit 7)                            */
#define CAN_ACPT_FIL15_EN_Msk               (0x80UL)        /*!< Acceptance filter 15 Enable (Bitfield-Mask: 0x01)              */
#define CAN_ACPT_FIL15_EN                   CAN_ACPT_FIL15_EN_Msk
#define CAN_ACPT_FIL14_EN_Pos               (6UL)           /*!< Acceptance filter 14 Enable (Bit 6)                            */
#define CAN_ACPT_FIL14_EN_Msk               (0x40UL)        /*!< Acceptance filter 14 Enable (Bitfield-Mask: 0x01)              */
#define CAN_ACPT_FIL14_EN                   CAN_ACPT_FIL14_EN_Msk
#define CAN_ACPT_FIL13_EN_Pos               (5UL)           /*!< Acceptance filter 13 Enable (Bit 5)                            */
#define CAN_ACPT_FIL13_EN_Msk               (0x20UL)        /*!< Acceptance filter 13 Enable (Bitfield-Mask: 0x01)              */
#define CAN_ACPT_FIL13_EN                   CAN_ACPT_FIL13_EN_Msk
#define CAN_ACPT_FIL12_EN_Pos               (4UL)           /*!< Acceptance filter 12 Enable (Bit 4)                            */
#define CAN_ACPT_FIL12_EN_Msk               (0x10UL)        /*!< Acceptance filter 12 Enable (Bitfield-Mask: 0x01)              */
#define CAN_ACPT_FIL12_EN                   CAN_ACPT_FIL12_EN_Msk
#define CAN_ACPT_FIL11_EN_Pos               (3UL)           /*!< Acceptance filter 11 Enable (Bit 3)                            */
#define CAN_ACPT_FIL11_EN_Msk               (0x8UL)         /*!< Acceptance filter 11 Enable (Bitfield-Mask: 0x01)              */
#define CAN_ACPT_FIL11_EN                   CAN_ACPT_FIL11_EN_Msk
#define CAN_ACPT_FIL10_EN_Pos               (2UL)           /*!< Acceptance filter 10 Enable (Bit 2)                            */
#define CAN_ACPT_FIL10_EN_Msk               (0x4UL)         /*!< Acceptance filter 10 Enable (Bitfield-Mask: 0x01)              */
#define CAN_ACPT_FIL10_EN                   CAN_ACPT_FIL10_EN_Msk
#define CAN_ACPT_FIL9_EN_Pos                (1UL)           /*!< Acceptance filter 9 Enable (Bit 1)                             */
#define CAN_ACPT_FIL9_EN_Msk                (0x2UL)         /*!< Acceptance filter 9 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL9_EN                    CAN_ACPT_FIL9_EN_Msk
#define CAN_ACPT_FIL8_EN_Pos                (0UL)           /*!< Acceptance filter 8 Enable (Bit 0)                             */
#define CAN_ACPT_FIL8_EN_Msk                (0x1UL)         /*!< Acceptance filter 8 Enable (Bitfield-Mask: 0x01)               */
#define CAN_ACPT_FIL8_EN                    CAN_ACPT_FIL8_EN_Msk

/*********************  Bit definition for ACF register  **********************/
#define CAN_ACPT_MASK_IDE_CHK_EN_Pos        (30UL)          /*!< Acceptance mask IDE bit check enable (Bit 30)                  */
#define CAN_ACPT_MASK_IDE_CHK_EN_Msk        (0x40000000UL)  /*!< Acceptance mask IDE bit check enable (Bitfield-Mask: 0x01)     */
#define CAN_ACPT_MASK_IDE_CHK_EN            CAN_ACPT_MASK_IDE_CHK_EN_Msk
#define CAN_ACPT_MASK_IDE_BIT_VAL_Pos       (29UL)          /*!< Acceptance mask IDE bit value (Bit 29)                         */
#define CAN_ACPT_MASK_IDE_BIT_VAL_Msk       (0x20000000UL)  /*!< Acceptance mask IDE bit value (Bitfield-Mask: 0x01)            */
#define CAN_ACPT_MASK_IDE_BIT_VAL           CAN_ACPT_MASK_IDE_BIT_VAL_Msk
#define CAN_ACPT_CODE_OR_MASK_Pos           (0UL)           /*!< Acceptance CODE or MASK (Bit 0)                                */
#define CAN_ACPT_CODE_OR_MASK_Msk           (0x1fffffffUL)  /*!< Acceptance CODE or MASK (Bitfield-Mask: 0x1fffffff)            */
#define CAN_ACPT_CODE_OR_MASK               CAN_ACPT_CODE_OR_MASK_Msk
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup TAE32F53xx_Exported_Macro TAE32F53xx Exported Macro
  * @brief    TAE32F53xx Exported Macro
  * @{
  */

/**
  * @brief  Judge is GPIO instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't GPIO instance
  * @retval 1 is GPIO instance
  */
#define IS_GPIO_ALL_INSTANCE(__INSTANCE__)          (((__INSTANCE__) == GPIOA) || \
                                                     ((__INSTANCE__) == GPIOB) || \
                                                     ((__INSTANCE__) == GPIOC) || \
                                                     ((__INSTANCE__) == GPIOD))

/**
  * @brief  Judge is WWDG instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't WWDG instance
  * @retval 1 is WWDG instance
  */
#define IS_WWDG_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == WWDG)

/**
  * @brief  Judge is IWDG instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IWDG instance
  * @retval 1 is IWDG instance
  */
#define IS_IWDG_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == IWDG)

/**
  * @brief  Judge is IIR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IIR instance
  * @retval 1 is IIR instance
  */
#define IS_IIR_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == IIR0) || \
                                                     ((__INSTANCE__) == IIR1) || \
                                                     ((__INSTANCE__) == IIR2) || \
                                                     ((__INSTANCE__) == IIR3) || \
                                                     ((__INSTANCE__) == IIR4))

/**
  * @brief  Judge is TMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't TMR instance
  * @retval 1 is TMR instance
  */
#define IS_TMR_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == TMR0) || \
                                                     ((__INSTANCE__) == TMR1) || \
                                                     ((__INSTANCE__) == TMR2) || \
                                                     ((__INSTANCE__) == TMR3) || \
                                                     ((__INSTANCE__) == TMR4) || \
                                                     ((__INSTANCE__) == TMR5) || \
                                                     ((__INSTANCE__) == TMR6) || \
                                                     ((__INSTANCE__) == TMR7))

/**
  * @brief  Judge is TMR Group instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't TMR Group instance
  * @retval 1 is TMR Group instance
  */
#define IS_TMR_ALL_TMRGRP_INSTANCE(__INSTANCE__)    (((__INSTANCE__) == TMRGRP0) || ((__INSTANCE__) == TMRGRP1))

/**
  * @brief  Judge is UART instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't UART instance
  * @retval 1 is UART instance
  */
#define IS_UART_ALL_INSTANCE(__INSTANCE__)          (((__INSTANCE__) == UART0) || ((__INSTANCE__) == UART1))

/**
  * @brief  Judge is DMA instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DMA instance
  * @retval 1 is DMA instance
  */
#define IS_DMA_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == DMA))

/**
  * @brief  Judge is SYSCTRL instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't SYSCTRL instance
  * @retval 1 is SYSCTRL instance
  */
#define IS_SYSCTRL_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == SYSCTRL))

/**
  * @brief  Judge is FPLL instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't FPLL instance
  * @retval 1 is FPLL instance
  */
#define IS_FPLL_ALL_INSTANCE(__INSTANCE__)          (((__INSTANCE__) == FPLL0) || \
                                                     ((__INSTANCE__) == FPLL1) || \
                                                     ((__INSTANCE__) == FPLL2))

/**
  * @brief  Judge is LVD instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't LVD instance
  * @retval 1 is LVD instance
  */
#define IS_LVD_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == LVD))

/**
  * @brief  Judge is USB instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't USB instance
  * @retval 1 is USB instance
  */
#define IS_USB_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == USB))

/**
  * @brief  Judge is DAC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DAC instance
  * @retval 1 is DAC instance
  */
#define IS_DAC_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == DAC))

/**
  * @brief  Judge is CMP instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CMP instance
  * @retval 1 is CMP instance
  */
#define IS_CMP_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == CMP))

/**
  * @brief  Judge is I2C instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't I2C instance
  * @retval 1 is I2C instance
  */
#define IS_I2C_ALL_INSTANCE(__INSTANCE__)          (((__INSTANCE__) == I2C0) || ((__INSTANCE__) == I2C1))

/**
  * @brief  Judge is CAN instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CAN instance
  * @retval 1 is CAN instance
  */
#define IS_CAN_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == CAN))

/**
  * @brief  Judge is DALI instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DALI instance
  * @retval 1 is DALI instance
  */
#define IS_DALI_ALL_INSTANCE(__INSTANCE__)          (((__INSTANCE__) == DALI))

/**
  * @brief  Judge is ADC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't ADC instance
  * @retval 1 is ADC instance
  */
#define IS_ADC_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == ADC0) || ((__INSTANCE__) == ADC1))

/**
  * @brief  Judge is HRPWM instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't HRPWM instance
  * @retval 1 is HRPWM instance
  */
#define IS_HRPWM_ALL_INSTANCE(__INSTANCE__)         (((__INSTANCE__) == HRPWM))

/**
  * @brief  Judge is ECU instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't ECU instance
  * @retval 1 is ECU instance
  */
#define IS_ECU_ALL_INSTANCE(__INSTANCE__)           (((__INSTANCE__) == ECU))
/**
  * @}
  */


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/**
  * @}
  */


/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _TAE32F53XX_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

