/******************************************************************************
 * @file     hbird.h
 * @brief    NMSIS Core Peripheral Access Layer Header File for
 *           Nuclei HummingBird evaluation SoC which support Nuclei N/NX class cores
 * @version  V1.00
 * @date     22. Nov 2019
 ******************************************************************************/
/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HBIRD_H__
#define __HBIRD_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Nuclei
  * @{
  */


/** @addtogroup hbird
  * @{
  */


/** @addtogroup Configuration_of_NMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn
{
/* =======================================  Nuclei Core Specific Interrupt Numbers  ======================================== */

    Reserved0_IRQn            =   0,              /*!<  Internal reserved */
    Reserved1_IRQn            =   1,              /*!<  Internal reserved */
    Reserved2_IRQn            =   2,              /*!<  Internal reserved */
    SysTimerSW_IRQn           =   3,              /*!<  System Timer SW interrupt */
    Reserved3_IRQn            =   4,              /*!<  Internal reserved */
    Reserved4_IRQn            =   5,              /*!<  Internal reserved */
    Reserved5_IRQn            =   6,              /*!<  Internal reserved */
    SysTimer_IRQn             =   7,              /*!<  System Timer Interrupt */
    Reserved6_IRQn            =   8,              /*!<  Internal reserved */
    Reserved7_IRQn            =   9,              /*!<  Internal reserved */
    Reserved8_IRQn            =  10,              /*!<  Internal reserved */
    Reserved9_IRQn            =  11,              /*!<  Internal reserved */
    Reserved10_IRQn           =  12,              /*!<  Internal reserved */
    Reserved11_IRQn           =  13,              /*!<  Internal reserved */
    Reserved12_IRQn           =  14,              /*!<  Internal reserved */
    Reserved13_IRQn           =  15,              /*!<  Internal reserved */
    Reserved14_IRQn           =  16,              /*!<  Internal reserved */
    Reserved15_IRQn           =  17,              /*!<  Internal reserved */
    Reserved16_IRQn           =  18,              /*!<  Internal reserved */

/* ===========================================  hbird Specific Interrupt Numbers  ========================================= */
/* ToDo: add here your device specific external interrupt numbers. 19~1023 is reserved number for user. Maxmum interrupt supported
         could get from clicinfo.NUM_INTERRUPT. According the interrupt handlers defined in startup_Device.s
         eg.: Interrupt for Timer#1       eclic_tim1_handler   ->   TIM1_IRQn */
    SOC_INT19_IRQn           = 19,                /*!< Device Interrupt */
    SOC_INT20_IRQn           = 20,                /*!< Device Interrupt */
    SOC_INT21_IRQn           = 21,                /*!< Device Interrupt */
    SOC_INT22_IRQn           = 22,                /*!< Device Interrupt */
    SOC_INT23_IRQn           = 23,                /*!< Device Interrupt */
    SOC_INT24_IRQn           = 24,                /*!< Device Interrupt */
    SOC_INT25_IRQn           = 25,                /*!< Device Interrupt */
    SOC_INT26_IRQn           = 26,                /*!< Device Interrupt */
    SOC_INT27_IRQn           = 27,                /*!< Device Interrupt */
    SOC_INT28_IRQn           = 28,                /*!< Device Interrupt */
    SOC_INT29_IRQn           = 29,                /*!< Device Interrupt */
    SOC_INT30_IRQn           = 30,                /*!< Device Interrupt */
    SOC_INT31_IRQn           = 31,                /*!< Device Interrupt */
    SOC_INT32_IRQn           = 32,                /*!< Device Interrupt */
    SOC_INT33_IRQn           = 33,                /*!< Device Interrupt */
    SOC_INT34_IRQn           = 34,                /*!< Device Interrupt */
    SOC_INT35_IRQn           = 35,                /*!< Device Interrupt */
    SOC_INT36_IRQn           = 36,                /*!< Device Interrupt */
    SOC_INT37_IRQn           = 37,                /*!< Device Interrupt */
    SOC_INT38_IRQn           = 38,                /*!< Device Interrupt */
    SOC_INT39_IRQn           = 39,                /*!< Device Interrupt */
    SOC_INT40_IRQn           = 40,                /*!< Device Interrupt */
    SOC_INT41_IRQn           = 41,                /*!< Device Interrupt */
    SOC_INT42_IRQn           = 42,                /*!< Device Interrupt */
    SOC_INT43_IRQn           = 43,                /*!< Device Interrupt */
    SOC_INT44_IRQn           = 44,                /*!< Device Interrupt */
    SOC_INT45_IRQn           = 45,                /*!< Device Interrupt */
    SOC_INT46_IRQn           = 46,                /*!< Device Interrupt */
    SOC_INT47_IRQn           = 47,                /*!< Device Interrupt */
    SOC_INT48_IRQn           = 48,                /*!< Device Interrupt */
    SOC_INT49_IRQn           = 49,                /*!< Device Interrupt */
    SOC_INT50_IRQn           = 50,                /*!< Device Interrupt */
    SOC_INT_MAX,
} IRQn_Type;

/* =========================================================================================================================== */
/* ================                                  Exception Code Definition                                ================ */
/* =========================================================================================================================== */

typedef enum EXCn {
/* =======================================  Nuclei N/NX Specific Exception Code  ======================================== */
    InsUnalign_EXCn          =   0,              /*!<  Instruction address misaligned */
    InsAccFault_EXCn         =   1,              /*!<  Instruction access fault */
    IlleIns_EXCn             =   2,              /*!<  Illegal instruction */
    Break_EXCn               =   3,              /*!<  Beakpoint */
    LdAddrUnalign_EXCn       =   4,              /*!<  Load address misaligned */
    LdFault_EXCn             =   5,              /*!<  Load access fault */
    StAddrUnalign_EXCn       =   6,              /*!<  Store or AMO address misaligned */
    StAccessFault_EXCn       =   7,              /*!<  Store or AMO access fault */
    UmodeEcall_EXCn          =   8,              /*!<  Environment call from User mode */
    MmodeEcall_EXCn          =  11,              /*!<  Environment call from Machine mode */
    NMI_EXCn                 = 0xfff,            /*!<  NMI interrupt */
} EXCn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ToDo: set the defines according your Device */
/* ToDo: define the correct core revision */
#if __riscv_xlen == 32

#ifndef __NUCLEI_CORE_REV
#define __NUCLEI_N_REV            0x0104    /*!< Core Revision r1p4 */
#else
#define __NUCLEI_N_REV            __NUCLEI_CORE_REV
#endif

#elif __riscv_xlen == 64

#ifndef __NUCLEI_CORE_REV
#define __NUCLEI_NX_REV           0x0100    /*!< Core Revision r1p0 */
#else
#define __NUCLEI_NX_REV           __NUCLEI_CORE_REV
#endif

#endif /* __riscv_xlen == 64 */

/* ToDo: define the correct core features for the hbird */
#define __ECLIC_PRESENT           1                     /*!< Set to 1 if ECLIC is present */
#define __ECLIC_BASEADDR          0x0C000000UL          /*!< Set to ECLIC baseaddr of your device */

//#define __ECLIC_INTCTLBITS        3                     /*!< Set to 1 - 8, the number of hardware bits are actually implemented in the clicintctl registers. */
#define __ECLIC_INTNUM            51                    /*!< Set to 1 - 1024, total interrupt number of ECLIC Unit */
#define __SYSTIMER_PRESENT        1                     /*!< Set to 1 if System Timer is present */
#define __SYSTIMER_BASEADDR       0x02000000UL          /*!< Set to SysTimer baseaddr of your device */

/*!< Set to 0, 1, or 2, 0 not present, 1 single floating point unit present, 2 double floating point unit present */
#if !defined(__riscv_flen)
#define __FPU_PRESENT             0
#elif __riscv_flen == 32
#define __FPU_PRESENT             1
#else
#define __FPU_PRESENT             2
#endif

#define __DSP_PRESENT             1                     /*!< Set to 1 if DSP is present */
#define __PMP_PRESENT             1                     /*!< Set to 1 if PMP is present */
#define __PMP_ENTRY_NUM           16                    /*!< Set to 8 or 16, the number of PMP entries */
#define __ICACHE_PRESENT          0                     /*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT          0                     /*!< Set to 1 if D-Cache is present */
#define __Vendor_SysTickConfig    0                     /*!< Set to 1 if different SysTick Config is used */
#define __Vendor_EXCEPTION        0                     /*!< Set to 1 if vendor exception hander is present */

/** @} */ /* End of group Configuration_of_CMSIS */


#include <nmsis_core.h>                         /*!< Nuclei N/NX class processor and core peripherals */
/* ToDo: include your system_hbird.h file
         replace 'Device' with your device name */
#include "system_hbird.h"                    /*!< hbird System */


/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#define RTC_FREQ 32768
// The TIMER frequency is just the RTC frequency
#define SOC_TIMER_FREQ RTC_FREQ
/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

/****************************************************************************
 * Platform definitions
 *****************************************************************************/
#define SOC_ECLIC_CTRL_ADDR     _AC(0x0C000000,UL)
#define SOC_TIMER_CTRL_ADDR     _AC(0x02000000,UL)
#define GPIO_CTRL_ADDR          _AC(0x10012000,UL)
#define UART0_CTRL_ADDR         _AC(0x10013000,UL)
#define SPI0_CTRL_ADDR          _AC(0x10014000,UL)
#define PWM0_CTRL_ADDR          _AC(0x10015000,UL)
#define UART1_CTRL_ADDR         _AC(0x10023000,UL)
#define SPI1_CTRL_ADDR          _AC(0x10024000,UL)
#define PWM1_CTRL_ADDR          _AC(0x10025000,UL)
#define SPI2_CTRL_ADDR          _AC(0x10034000,UL)
#define PWM2_CTRL_ADDR          _AC(0x10035000,UL)
#define I2C_CTRL_ADDR           _AC(0x10042000,UL)
#define SPI0_MMAP_ADDR          _AC(0x20000000,UL)
#define MEM_CTRL_ADDR           _AC(0x80000000,UL)

// IOF Mappings
#define IOF0_SPI1_MASK          _AC(0x000007FC,UL)
#define SPI11_NUM_SS            (4)
#define IOF_SPI1_SS0            (2u)
#define IOF_SPI1_SS1            (8u)
#define IOF_SPI1_SS2            (9u)
#define IOF_SPI1_SS3            (10u)
#define IOF_SPI1_MOSI           (3u)
#define IOF_SPI1_MISO           (4u)
#define IOF_SPI1_SCK            (5u)
#define IOF_SPI1_DQ0            (3u)
#define IOF_SPI1_DQ1            (4u)
#define IOF_SPI1_DQ2            (6u)
#define IOF_SPI1_DQ3            (7u)

#define IOF0_SPI2_MASK          _AC(0xFC000000,UL)
#define SPI2_NUM_SS             (1)
#define IOF_SPI2_SS0            (26u)
#define IOF_SPI2_MOSI           (27u)
#define IOF_SPI2_MISO           (28u)
#define IOF_SPI2_SCK            (29u)
#define IOF_SPI2_DQ0            (27u)
#define IOF_SPI2_DQ1            (28u)
#define IOF_SPI2_DQ2            (30u)
#define IOF_SPI2_DQ3            (31u)

#define IOF0_UART0_MASK         _AC(0x00030000, UL)
#define IOF_UART0_RX            (16u)
#define IOF_UART0_TX            (17u)

#define IOF0_UART1_MASK         _AC(0x03000000, UL)
#define IOF_UART1_RX            (24u)
#define IOF_UART1_TX            (25u)

#define IOF0_I2C_MASK           _AC(0x00003000, UL)
#define IOF_I2C_SDA             (12u)
#define IOF_I2C_SCL             (13u)

#define IOF1_PWM0_MASK          _AC(0x0000000F, UL)
#define IOF1_PWM1_MASK          _AC(0x00780000, UL)
#define IOF1_PWM2_MASK          _AC(0x00003C00, UL)

// Interrupt Numbers
#define SOC_ECLIC_NUM_INTERRUPTS    32
#define SOC_ECLIC_INT_GPIO_BASE     19

// Interrupt Handler Definitions
#define SOC_MTIMER_HANDLER          eclic_mtip_handler
#define SOC_SOFTINT_HANDLER         eclic_msip_handler

#define GPIO_BIT_ALL_ZERO           (0x0)
#define GPIO_BIT_ALL_ONE            (0xFFFFFFFF)

/**
  * @brief GPIO
  */
typedef struct {  /*!< GPIO Structure */
    __IOM uint32_t INPUT_VAL;
    __IOM uint32_t INPUT_EN;
    __IOM uint32_t OUTPUT_EN;
    __IOM uint32_t OUTPUT_VAL;
    __IOM uint32_t PULLUP_EN;
    __IOM uint32_t DRIVE;
    __IOM uint32_t RISE_IE;
    __IOM uint32_t RISE_IP;
    __IOM uint32_t FALL_IE;
    __IOM uint32_t FALL_IP;
    __IOM uint32_t HIGH_IE;
    __IOM uint32_t HIGH_IP;
    __IOM uint32_t LOW_IE;
    __IOM uint32_t LOW_IP;
    __IOM uint32_t IOF_EN;
    __IOM uint32_t IOF_SEL;
    __IOM uint32_t OUTPUT_XOR;
} GPIO_TypeDef;

/**
  * @brief UART (UART)
  */
typedef struct {
    __IOM uint32_t TXFIFO;
    __IOM uint32_t RXFIFO;
    __IOM uint32_t TXCTRL;
    __IOM uint32_t RXCTRL;
    __IOM uint32_t IE;
    __IOM uint32_t IP;
    __IOM uint32_t DIV;
} UART_TypeDef;

typedef struct {
    __IOM uint32_t CFG;
          uint32_t RESERVED0;
    __IOM uint32_t COUNT;
          uint32_t RESERVED1;
    __IOM uint32_t S;
          uint32_t RESERVED2[3];
    __IOM uint32_t CMP0;
    __IOM uint32_t CMP1;
    __IOM uint32_t CMP2;
    __IOM uint32_t CMP3;
} PWM_TypeDef;

typedef struct {
    __IOM uint32_t SCKDIV;
    __IOM uint32_t SCKMODE;
    __IOM uint32_t RESERVED0[2];
    __IOM uint32_t CSID;
    __IOM uint32_t CSDEF;
    __IOM uint32_t CSMODE;
    __IOM uint32_t RESERVED1[3];
    __IOM uint32_t DELAY0;
    __IOM uint32_t DELAY1;
    __IOM uint32_t RESERVED2[4];
    __IOM uint32_t FMT;
    __IOM uint32_t RESERVED3;
    __IOM uint32_t TXFIFO;
    __IOM uint32_t RXFIFO;
    __IOM uint32_t TXCTRL;
    __IOM uint32_t RXCTRL;
    __IOM uint32_t RESERVED4[2];
    __IOM uint32_t FCTRL;
    __IOM uint32_t FFMT;
    __IOM uint32_t RESERVED5[2];
    __IOM uint32_t IE;
    __IOM uint32_t IP;
} QSPI_TypeDef;

typedef struct {
    __IOM uint8_t PRERlo;
    __IOM uint8_t PRERhi;
    __IOM uint8_t CTR;
    __IOM uint8_t TXRXR; /* TXR and RXR in same address */
    __IOM uint8_t CSR; /* CR and SR in same address */
} I2C_TypeDef;

/*@}*/ /* end of group hbird_Peripherals */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/* ToDo: add here your device peripherals base addresses
         following is an example for timer */
/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */
/* Peripheral and SRAM base address */
#define QSPI_FLASH_BASE                       (0x20000000UL)      /*!< (FLASH     ) Base Address */
#define ONCHIP_ROM_BASE                       (0x00001000UL)      /*!< (ROM       ) Base Address */
#define ONCHIP_ILM_BASE                       (0x80000000UL)      /*!< (ILM       ) Base Address */
#define ONCHIP_DLM_BASE                       (0x90000000UL)      /*!< (DLM       ) Base Address */
#define HBIRD_PERIPH_BASE                (0x10000000UL)      /*!< (Peripheral) Base Address */

/* Peripheral memory map */
/* Fast-IO Interfaced IP */
#define GPIO_BASE         (HBIRD_PERIPH_BASE + 0x12000)          /*!< (GPIO) Base Address */
/* PPI Interfaced IP */
#define UART0_BASE        (HBIRD_PERIPH_BASE + 0x13000)          /*!< (UART0) Base Address */
#define QSPI0_BASE        (HBIRD_PERIPH_BASE + 0x14000)          /*!< (QSPI0) Base Address */
#define PWM0_BASE         (HBIRD_PERIPH_BASE + 0x15000)          /*!< (PWM0) Base Address */
#define UART1_BASE        (HBIRD_PERIPH_BASE + 0x23000)          /*!< (UART1) Base Address */
#define QSPI1_BASE        (HBIRD_PERIPH_BASE + 0x24000)          /*!< (QSPI1) Base Address */
#define PWM1_BASE         (HBIRD_PERIPH_BASE + 0x25000)          /*!< (PWM1) Base Address */
#define QSPI2_BASE        (HBIRD_PERIPH_BASE + 0x34000)          /*!< (QSPI2) Base Address */
#define PWM2_BASE         (HBIRD_PERIPH_BASE + 0x35000)          /*!< (PWM2) Base Address */
#define I2C_BASE          (HBIRD_PERIPH_BASE + 0x42000)          /*!< (I2C Master) Base Address */

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/* ToDo: add here your device peripherals pointer definitions
         following is an example for timer */
/** @addtogroup Device_Peripheral_declaration
  * @{
  */
#define GPIO        ((GPIO_TypeDef *) GPIO_BASE)
#define UART0       ((UART_TypeDef *) UART0_BASE)
#define QSPI0       ((QSPI_TypeDef *) QSPI0_BASE)
#define PWM0        ((PWM_TypeDef *) PWM0_BASE)
#define UART1       ((UART_TypeDef *) UART1_BASE)
#define QSPI1       ((QSPI_TypeDef *) QSPI1_BASE)
#define PWM1        ((PWM_TypeDef *) PWM1_BASE)
#define QSPI2       ((QSPI_TypeDef *) QSPI2_BASE)
#define PWM2        ((PWM_TypeDef *) PWM2_BASE)
#define I2C         ((I2C_TypeDef *) I2C_BASE)

// Helper functions
#define _REG8(p, i)             (*(volatile uint8_t *) ((p) + (i)))
#define _REG32(p, i)            (*(volatile uint32_t *) ((p) + (i)))
#define _REG32P(p, i)           ((volatile uint32_t *) ((p) + (i)))
#define GPIO_REG(offset)        _REG32(GPIO_CTRL_ADDR, offset)
#define OTP_REG(offset)         _REG32(OTP_CTRL_ADDR, offset)
#define PRCI_REG(offset)        _REG32(PRCI_CTRL_ADDR, offset)
#define PWM0_REG(offset)        _REG32(PWM0_CTRL_ADDR, offset)
#define PWM1_REG(offset)        _REG32(PWM1_CTRL_ADDR, offset)
#define PWM2_REG(offset)        _REG32(PWM2_CTRL_ADDR, offset)
#define SPI0_REG(offset)        _REG32(SPI0_CTRL_ADDR, offset)
#define SPI1_REG(offset)        _REG32(SPI1_CTRL_ADDR, offset)
#define SPI2_REG(offset)        _REG32(SPI2_CTRL_ADDR, offset)
#define UART0_REG(offset)       _REG32(UART0_CTRL_ADDR, offset)
#define UART1_REG(offset)       _REG32(UART1_CTRL_ADDR, offset)
#define I2C_REG(offset)         _REG8(I2C_CTRL_ADDR, offset)

// Misc

#define NUM_GPIO 32

uint32_t get_cpu_freq();

/** @} */ /* End of group hbird */

/** @} */ /* End of group Nuclei */

#ifdef __cplusplus
}
#endif

#endif  /* __HBIRD_H__ */
