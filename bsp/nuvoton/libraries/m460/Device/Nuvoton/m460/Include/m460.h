/**************************************************************************//**
 * @file     m460.h
 * @version  V3.00
 * @brief    M460 peripheral access layer header file.
 *           This file contains all the peripheral register's definitions,
 *           bits definitions and memory mapping for NuMicro M460 MCU.
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
/**
  \mainpage NuMicro M460 Driver Reference Guide
  *
  * <b>Introduction</b>
  *
  * This user manual describes the usage of M460 Series MCU device driver
  *
  * <b>Disclaimer</b>
  *
  * The Software is furnished "AS IS", without warranty as to performance or results, and
  * the entire risk as to performance or results is assumed by YOU. Nuvoton disclaims all
  * warranties, express, implied or otherwise, with regard to the Software, its use, or
  * operation, including without limitation any and all warranties of merchantability, fitness
  * for a particular purpose, and non-infringement of intellectual property rights.
  *
  * <b>Important Notice</b>
  *
  * Nuvoton Products are neither intended nor warranted for usage in systems or equipment,
  * any malfunction or failure of which may cause loss of human life, bodily injury or severe
  * property damage. Such applications are deemed, "Insecure Usage".
  *
  * Insecure usage includes, but is not limited to: equipment for surgical implementation,
  * atomic energy control instruments, airplane or spaceship instruments, the control or
  * operation of dynamic, brake or safety systems designed for vehicular use, traffic signal
  * instruments, all types of safety devices, and other applications intended to support or
  * sustain life.
  *
  * All Insecure Usage shall be made at customer's risk, and in the event that third parties
  * lay claims to Nuvoton as a result of customer's Insecure Usage, customer shall indemnify
  * the damages and liabilities thus incurred by Nuvoton.
  *
  * Please note that all data and specifications are subject to change without notice. All the
  * trademarks of products and companies mentioned in this datasheet belong to their respective
  * owners.
  *
  * <b>Copyright Notice</b>
  *
  * Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
  */
#ifndef __M460_H__
#define __M460_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup CMSIS_Device Device CMSIS Definitions
  Configuration of the Cortex-M4 Processor and Core Peripherals
  @{
*/

/**
 * @details  Interrupt Number Definition.
 */
typedef enum IRQn
{
    /******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt                        */
    MemoryManagement_IRQn         = -12,      /*!<  4 Memory Management Interrupt                   */
    BusFault_IRQn                 = -11,      /*!<  5 Bus Fault Interrupt                           */
    UsageFault_IRQn               = -10,      /*!<  6 Usage Fault Interrupt                         */
    SVCall_IRQn                   = -5,       /*!< 11 SV Call Interrupt                             */
    DebugMonitor_IRQn             = -4,       /*!< 12 Debug Monitor Interrupt                       */
    PendSV_IRQn                   = -2,       /*!< 14 Pend SV Interrupt                             */
    SysTick_IRQn                  = -1,       /*!< 15 System Tick Interrupt                         */

    /******  M460 Specific Interrupt Numbers ********************************************************/

    BOD_IRQn                      = 0,        /*!< Brown Out detection Interrupt                    */
    IRC_IRQn                      = 1,        /*!< Internal RC Interrupt                            */
    PWRWU_IRQn                    = 2,        /*!< Power Down Wake Up Interrupt                     */
    RAMPE_IRQn                    = 3,        /*!< SRAM parity check failed Interrupt               */
    CKFAIL_IRQn                   = 4,        /*!< Clock failed Interrupt                           */
    ISP_IRQn                      = 5,        /*!< FMC ISP Interrupt                                */
    RTC_IRQn                      = 6,        /*!< Real Time Clock Interrupt                        */
    TAMPER_IRQn                   = 7,        /*!< Tamper detection Interrupt                       */
    WDT_IRQn                      = 8,        /*!< Watchdog timer Interrupt                         */
    WWDT_IRQn                     = 9,        /*!< Window Watchdog timer Interrupt                  */
    EINT0_IRQn                    = 10,       /*!< External Input 0 Interrupt                       */
    EINT1_IRQn                    = 11,       /*!< External Input 1 Interrupt                       */
    EINT2_IRQn                    = 12,       /*!< External Input 2 Interrupt                       */
    EINT3_IRQn                    = 13,       /*!< External Input 3 Interrupt                       */
    EINT4_IRQn                    = 14,       /*!< External Input 4 Interrupt                       */
    EINT5_IRQn                    = 15,       /*!< External Input 5 Interrupt                       */
    GPA_IRQn                      = 16,       /*!< GPIO Port A Interrupt                            */
    GPB_IRQn                      = 17,       /*!< GPIO Port B Interrupt                            */
    GPC_IRQn                      = 18,       /*!< GPIO Port C Interrupt                            */
    GPD_IRQn                      = 19,       /*!< GPIO Port D Interrupt                            */
    GPE_IRQn                      = 20,       /*!< GPIO Port E Interrupt                            */
    GPF_IRQn                      = 21,       /*!< GPIO Port F Interrupt                            */
    QSPI0_IRQn                    = 22,       /*!< QSPI0 Interrupt                                   */
    SPI0_IRQn                     = 23,       /*!< SPI0 Interrupt                                   */
    BRAKE0_IRQn                   = 24,       /*!< BRAKE0 Interrupt                                 */
    EPWM0P0_IRQn                  = 25,       /*!< EPWM0P0 Interrupt                                */
    EPWM0P1_IRQn                  = 26,       /*!< EPWM0P1 Interrupt                                */
    EPWM0P2_IRQn                  = 27,       /*!< EPWM0P2 Interrupt                                */
    BRAKE1_IRQn                   = 28,       /*!< BRAKE1 Interrupt                                 */
    EPWM1P0_IRQn                  = 29,       /*!< EPWM1P0 Interrupt                                */
    EPWM1P1_IRQn                  = 30,       /*!< EPWM1P1 Interrupt                                */
    EPWM1P2_IRQn                  = 31,       /*!< EPWM1P2 Interrupt                                */
    TMR0_IRQn                     = 32,       /*!< Timer 0 Interrupt                                */
    TMR1_IRQn                     = 33,       /*!< Timer 1 Interrupt                                */
    TMR2_IRQn                     = 34,       /*!< Timer 2 Interrupt                                */
    TMR3_IRQn                     = 35,       /*!< Timer 3 Interrupt                                */
    UART0_IRQn                    = 36,       /*!< UART 0 Interrupt                                 */
    UART1_IRQn                    = 37,       /*!< UART 1 Interrupt                                 */
    I2C0_IRQn                     = 38,       /*!< I2C 0 Interrupt                                  */
    I2C1_IRQn                     = 39,       /*!< I2C 1 Interrupt                                  */
    PDMA0_IRQn                    = 40,       /*!< Peripheral DMA 0 Interrupt                       */
    DAC_IRQn                      = 41,       /*!< DAC Interrupt                                    */
    EADC00_IRQn                   = 42,       /*!< EADC00 Interrupt                                 */
    EADC01_IRQn                   = 43,       /*!< EADC01 Interrupt                                 */
    ACMP01_IRQn                   = 44,       /*!< Analog Comparator 0 and 1 Interrupt              */
    ACMP23_IRQn                   = 45,       /*!< Analog Comparator 2 and 3 Interrupt              */
    EADC02_IRQn                   = 46,       /*!< EADC02 Interrupt                                 */
    EADC03_IRQn                   = 47,       /*!< EADC03 Interrupt                                 */
    UART2_IRQn                    = 48,       /*!< UART2 Interrupt                                  */
    UART3_IRQn                    = 49,       /*!< UART3 Interrupt                                  */
    QSPI1_IRQn                    = 50,       /*!< QSPI1 Interrupt                                  */
    SPI1_IRQn                     = 51,       /*!< SPI1 Interrupt                                   */
    SPI2_IRQn                     = 52,       /*!< SPI2 Interrupt                                   */
    USBD_IRQn                     = 53,       /*!< USB device Interrupt                             */
    USBH_IRQn                     = 54,       /*!< USB host Interrupt                               */
    USBOTG_IRQn                   = 55,       /*!< USB OTG Interrupt                                */
    BMC_IRQn                      = 56,       /*!< BMC Interrupt                                    */
    SPI5_IRQn                     = 57,       /*!< SPI5 Interrupt                                   */
    SC0_IRQn                      = 58,       /*!< Smart Card 0 Interrupt                           */
    SC1_IRQn                      = 59,       /*!< Smart Card 1 Interrupt                           */
    SC2_IRQn                      = 60,       /*!< Smart Card 2 Interrupt                           */
    GPJ_IRQn                      = 61,       /*!< GPIO Port J Interrupt                            */
    SPI3_IRQn                     = 62,       /*!< SPI3 Interrupt                                   */
    SPI4_IRQn                     = 63,       /*!< SPI4 Interrupt                                   */
    EMAC0_TXRX_IRQn               = 66,       /*!< Ethernet MAC 0 Interrupt                         */
    SDH0_IRQn                     = 64,       /*!< Secure Digital Host Controller 0 Interrupt       */
    USBD20_IRQn                   = 65,       /*!< High Speed USB device Interrupt                  */
    I2S0_IRQn                     = 68,       /*!< I2S0 Interrupt                                   */
    I2S1_IRQn                     = 69,       /*!< I2S1 Interrupt                                   */
    SPI6_IRQn                     = 70,       /*!< SPI6 Interrupt                                   */
    CRPT_IRQn                     = 71,       /*!< CRPT Interrupt                                   */
    GPG_IRQn                      = 72,       /*!< GPIO Port G Interrupt                            */
    EINT6_IRQn                    = 73,       /*!< External Input 6 Interrupt                       */
    UART4_IRQn                    = 74,       /*!< UART4 Interrupt                                  */
    UART5_IRQn                    = 75,       /*!< UART5 Interrupt                                  */
    USCI0_IRQn                    = 76,       /*!< USCI0 Interrupt                                  */
    SPI7_IRQn                     = 77,       /*!< SPI7 Interrupt                                   */
    BPWM0_IRQn                    = 78,       /*!< BPWM0 Interrupt                                  */
    BPWM1_IRQn                    = 79,       /*!< BPWM1 Interrupt                                  */
    SPIM_IRQn                     = 80,       /*!< SPIM Interrupt                                   */
    CCAP_IRQn                     = 81,       /*!< CCAP Interrupt                                   */
    I2C2_IRQn                     = 82,       /*!< I2C2 Interrupt                                   */
    I2C3_IRQn                     = 83,       /*!< I2C3 Interrupt                                   */
    EQEI0_IRQn                    = 84,       /*!< EQEI0 Interrupt                                  */
    EQEI1_IRQn                    = 85,       /*!< EQEI1 Interrupt                                  */
    ECAP0_IRQn                    = 86,       /*!< ECAP0 Interrupt                                  */
    ECAP1_IRQn                    = 87,       /*!< ECAP1 Interrupt                                  */
    GPH_IRQn                      = 88,       /*!< GPIO Port H Interrupt                            */
    EINT7_IRQn                    = 89,       /*!< External Input 7 Interrupt                       */
    SDH1_IRQn                     = 90,       /*!< Secure Digital Host Controller 1 Interrupt       */
    PSIO_IRQn                     = 91,       /*!< PSIO Interrupt                                   */
    HSUSBH_IRQn                   = 92,       /*!< High speed USB host Interrupt                    */
    USBOTG20_IRQn                 = 93,       /*!< High speed USB OTG Interrupt                     */
    ECAP2_IRQn                    = 94,       /*!< ECAP2 Interrupt                                  */
    ECAP3_IRQn                    = 95,       /*!< ECAP3 Interrupt                                  */
    KPI_IRQn                      = 96,       /*!< Keypad Interface Interrupt                       */
    HBI_IRQn                      = 97,       /*!< HBI Interrupt                                    */
    PDMA1_IRQn                    = 98,       /*!< Peripheral DMA 1 Interrupt                       */
    UART8_IRQn                    = 99,       /*!< UART8 Interrupt                                  */
    UART9_IRQn                    = 100,      /*!< UART9 Interrupt                                  */
    TRNG_IRQn                     = 101,      /*!< TRNG Interrupt                                   */
    UART6_IRQn                    = 102,      /*!< UART6 Interrupt                                  */
    UART7_IRQn                    = 103,      /*!< UART7 Interrupt                                  */
    EADC10_IRQn                   = 104,      /*!< EADC10 Interrupt                                 */
    EADC11_IRQn                   = 105,      /*!< EADC11 Interrupt                                 */
    EADC12_IRQn                   = 106,      /*!< EADC12 Interrupt                                 */
    EADC13_IRQn                   = 107,      /*!< EADC13 Interrupt                                 */
    SPI8_IRQn                     = 108,      /*!< SPI8 Interrupt                                   */
    KS_IRQn                       = 109,      /*!< Keystore Interrupt                               */
    GPI_IRQn                      = 110,      /*!< GPIO Port I Interrupt                            */
    SPI9_IRQn                     = 111,      /*!< SPI9 Interrupt                                   */
    CANFD00_IRQn                  = 112,      /*!< CANFD00 Interrupt                                */
    CANFD01_IRQn                  = 113,      /*!< CANFD01 Interrupt                                */
    CANFD10_IRQn                  = 114,      /*!< CANFD10 Interrupt                                */
    CANFD11_IRQn                  = 115,      /*!< CANFD11 Interrupt                                */
    EQEI2_IRQn                    = 116,      /*!< EQEI2 Interrupt                                  */
    EQEI3_IRQn                    = 117,      /*!< EQEI3 Interrupt                                  */
    I2C4_IRQn                     = 118,      /*!< I2C4 Interrupt                                   */
    SPI10_IRQn                    = 119,      /*!< SPI10 Interrupt                                  */
    CANFD20_IRQn                  = 120,      /*!< CANFD20 Interrupt                                */
    CANFD21_IRQn                  = 121,      /*!< CANFD21 Interrupt                                */
    CANFD30_IRQn                  = 122,      /*!< CANFD30 Interrupt                                */
    CANFD31_IRQn                  = 123,      /*!< CANFD31 Interrupt                                */
    EADC20_IRQn                   = 124,      /*!< EADC20 Interrupt                                 */
    EADC21_IRQn                   = 125,      /*!< EADC21 Interrupt                                 */
    EADC22_IRQn                   = 126,      /*!< EADC22 Interrupt                                 */
    EADC23_IRQn                   = 127,      /*!< EADC23 Interrupt                                 */
}
IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M4 Processor and Core Peripherals */
#define __CM4_REV                 0x0201UL    /*!< Core Revision r2p1                               */
#define __NVIC_PRIO_BITS          4UL         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0UL         /*!< Set to 1 if different SysTick Config is used     */
#define __MPU_PRESENT             1UL         /*!< MPU present or not                               */
#ifdef __FPU_PRESENT
#undef __FPU_PRESENT
#define __FPU_PRESENT             1UL         /*!< FPU present or not                               */
#else
#define __FPU_PRESENT             1UL         /*!< FPU present or not                               */
#endif

/*@}*/ /* end of group CMSIS_Device */


#include "core_cm4.h"               /* Cortex-M4 processor and core peripherals           */
#include "system_m460.h"            /* System include file                         */
#include <stdint.h>



#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/******************************************************************************/
/*                            Register definitions                            */
/******************************************************************************/

#include "sys_reg.h"
#include "clk_reg.h"
#include "fmc_reg.h"
#include "gpio_reg.h"
#include "pdma_reg.h"
#include "timer_reg.h"
#include "wdt_reg.h"
#include "wwdt_reg.h"
#include "rtc_reg.h"
#include "epwm_reg.h"
#include "bpwm_reg.h"
#include "eqei_reg.h"
#include "ecap_reg.h"
#include "uart_reg.h"
#include "emac_reg.h"
#include "sc_reg.h"
#include "i2s_reg.h"
#include "spi_reg.h"
#include "qspi_reg.h"
#include "spim_reg.h"
#include "i2c_reg.h"
#include "uuart_reg.h"
#include "uspi_reg.h"
#include "ui2c_reg.h"
#include "canfd_reg.h"
#include "sdh_reg.h"
#include "ebi_reg.h"
#include "usbd_reg.h"
#include "hsusbd_reg.h"
#include "usbh_reg.h"
#include "hsusbh_reg.h"
#include "otg_reg.h"
#include "hsotg_reg.h"
#include "crc_reg.h"
#include "crypto_reg.h"
#include "trng_reg.h"
#include "eadc_reg.h"
#include "dac_reg.h"
#include "acmp_reg.h"
#include "ccap_reg.h"
#include "keystore_reg.h"
#include "kpi_reg.h"
#include "psio_reg.h"
#include "hbi_reg.h"
#include "bmc_reg.h"

/** @addtogroup PERIPHERAL_MEM_MAP Peripheral Memory Base
  Memory Mapped Structure for Peripherals
  @{
 */
/* Peripheral and SRAM base address */
#define FLASH_BASE           ((uint32_t)0x00000000)      /*!< Flash base address      */
#define SRAM_BASE            ((uint32_t)0x20000000)      /*!< SRAM Base Address       */
#define PERIPH_BASE          ((uint32_t)0x40000000)      /*!< Peripheral Base Address */

#define TCM_BASE               (PERIPH_BASE + 0xBE000)

/*!< AHB peripherals */
//HCLK
// CPU,CRC,EBI,EMC,FMC,PDMA,SD0,SD1,CRPT,SPIM,SRAM,HSUSBD, HSUSBH, USBH
#define SYS_BASE               (PERIPH_BASE + 0x00000UL)
#define CLK_BASE               (PERIPH_BASE + 0x00200UL)
#define NMI_BASE               (PERIPH_BASE + 0x00300UL)
#define GPIOA_BASE             (PERIPH_BASE + 0x04000UL)
#define GPIOB_BASE             (PERIPH_BASE + 0x04040UL)
#define GPIOC_BASE             (PERIPH_BASE + 0x04080UL)
#define GPIOD_BASE             (PERIPH_BASE + 0x040C0UL)
#define GPIOE_BASE             (PERIPH_BASE + 0x04100UL)
#define GPIOF_BASE             (PERIPH_BASE + 0x04140UL)
#define GPIOG_BASE             (PERIPH_BASE + 0x04180UL)
#define GPIOH_BASE             (PERIPH_BASE + 0x041C0UL)
#define GPIOI_BASE             (PERIPH_BASE + 0x04200UL)
#define GPIOJ_BASE             (PERIPH_BASE + 0x04240UL)
#define GPIO_INT_BASE          (PERIPH_BASE + 0x04450UL)
#define GPIO_PIN_DATA_BASE     (PERIPH_BASE + 0x04800UL)
#define SPIM_BASE              (PERIPH_BASE + 0x07000UL)
#define PDMA0_BASE              (PERIPH_BASE + 0x08000UL)
#define PDMA1_BASE              (PERIPH_BASE + 0x18000UL)
#define USBH_BASE              (PERIPH_BASE + 0x09000UL)
#define HSUSBH_BASE            (PERIPH_BASE + 0x1A000UL)
#define EMAC_BASE              (PERIPH_BASE + 0x12000UL)
#define FMC_BASE               (PERIPH_BASE + 0x0C000UL)
#define SDH0_BASE              (PERIPH_BASE + 0x0D000UL)
#define SDH1_BASE              (PERIPH_BASE + 0x0E000UL)
#define EBI_BASE               (PERIPH_BASE + 0x10000UL)
#define HSUSBD_BASE            (PERIPH_BASE + 0x19000UL)
#define CCAP_BASE              (PERIPH_BASE + 0x30000UL)
#define CRC_BASE               (PERIPH_BASE + 0x31000UL)
#define CRPT_BASE              (PERIPH_BASE + 0x32000UL)
#define KS_BASE                (PERIPH_BASE + 0x35000UL)
#define TAMPER_BASE            (PERIPH_BASE + 0xE1000UL)
#define HBI_BASE               (PERIPH_BASE + 0xCE000UL)
#define BMC_BASE               (PERIPH_BASE + 0x1B000UL)

//PCLK0
// BPWM0,QSPI0,ECAP2,I2C0/2/4,I2S0,OPA,EPWM0,EQEI0/2,SC0/2,SPI1/3/5/7/9,TMR01,UR0/2/4/6/8,USBD,USCI0,WDT

/*!< APB0 peripherals */
#define WDT_BASE              (PERIPH_BASE + 0x40000UL)
#define WWDT_BASE             (PERIPH_BASE + 0x40100UL)
#define OPA_BASE              (PERIPH_BASE + 0x46000UL)
#define I2S0_BASE             (PERIPH_BASE + 0x48000UL)
#define EADC1_BASE            (PERIPH_BASE + 0x4B000UL)
#define TIMER0_BASE           (PERIPH_BASE + 0x50000UL)
#define TIMER1_BASE           (PERIPH_BASE + 0x50100UL)
#define EPWM0_BASE            (PERIPH_BASE + 0x58000UL)
#define BPWM0_BASE            (PERIPH_BASE + 0x5A000UL)
#define QSPI0_BASE            (PERIPH_BASE + 0x60000UL)
#define SPI1_BASE             (PERIPH_BASE + 0x62000UL)
#define SPI3_BASE             (PERIPH_BASE + 0x64000UL)
#define SPI5_BASE             (PERIPH_BASE + 0x66000UL)
#define SPI7_BASE             (PERIPH_BASE + 0x68000UL)
#define SPI9_BASE             (PERIPH_BASE + 0x6C000UL)
#define UART0_BASE            (PERIPH_BASE + 0x70000UL)
#define UART2_BASE            (PERIPH_BASE + 0x72000UL)
#define UART4_BASE            (PERIPH_BASE + 0x74000UL)
#define UART6_BASE            (PERIPH_BASE + 0x76000UL)
#define UART8_BASE            (PERIPH_BASE + 0x78000UL)
#define I2C0_BASE             (PERIPH_BASE + 0x80000UL)
#define I2C2_BASE             (PERIPH_BASE + 0x82000UL)
#define CANFD0_BASE           (PERIPH_BASE + 0x20000UL)
#define CANFD2_BASE           (PERIPH_BASE + 0x28000UL)
#define EQEI0_BASE            (PERIPH_BASE + 0xB0000UL)
#define ECAP0_BASE            (PERIPH_BASE + 0xB4000UL)
#define USCI0_BASE            (PERIPH_BASE + 0xD0000UL)



//PCLK1
// ACMP01/23,EADC0/1/2,BPWM1,DAC,ECAP1/3,I2C1/3,I2S1,OTG,HSOTG,EPWM1,QEI1/3,RTC,SC1,SPI0/2/4/6/8/10,QSPI1,TMR23,UR1/3/5/7/9,PSIO

/*!< APB1 peripherals */
#define RTC_BASE              (PERIPH_BASE + 0x41000UL)
#define EADC0_BASE            (PERIPH_BASE + 0x43000UL)
#define ACMP01_BASE           (PERIPH_BASE + 0x45000UL)
#define I2S1_BASE             (PERIPH_BASE + 0x49000UL)
#define USBD_BASE             (PERIPH_BASE + 0xC0000UL)
#define EADC1_BASE            (PERIPH_BASE + 0x4B000UL)
#define OTG_BASE              (PERIPH_BASE + 0x4D000UL)
#define HSOTG_BASE            (PERIPH_BASE + 0x4F000UL)
#define TIMER2_BASE           (PERIPH_BASE + 0x51000UL)
#define TIMER3_BASE           (PERIPH_BASE + 0x51100UL)
#define EADC2_BASE            (PERIPH_BASE + 0x97000UL)
#define EPWM1_BASE            (PERIPH_BASE + 0x59000UL)
#define BPWM1_BASE            (PERIPH_BASE + 0x5B000UL)
#define SPI0_BASE             (PERIPH_BASE + 0x61000UL)
#define SPI2_BASE             (PERIPH_BASE + 0x63000UL)
#define SPI4_BASE             (PERIPH_BASE + 0x65000UL)
#define SPI6_BASE             (PERIPH_BASE + 0x67000UL)
#define QSPI1_BASE            (PERIPH_BASE + 0x69000UL)
#define SPI8_BASE             (PERIPH_BASE + 0x6B000UL)
#define SPI10_BASE            (PERIPH_BASE + 0x6D000UL)
#define UART1_BASE            (PERIPH_BASE + 0x71000UL)
#define UART3_BASE            (PERIPH_BASE + 0x73000UL)
#define UART5_BASE            (PERIPH_BASE + 0x75000UL)
#define UART7_BASE            (PERIPH_BASE + 0x77000UL)
#define UART9_BASE            (PERIPH_BASE + 0x79000UL)
#define I2C1_BASE             (PERIPH_BASE + 0x81000UL)
#define CANFD1_BASE           (PERIPH_BASE + 0x24000UL)
#define CANFD3_BASE           (PERIPH_BASE + 0x2C000UL)
#define EQEI1_BASE            (PERIPH_BASE + 0xB1000UL)
#define ECAP1_BASE            (PERIPH_BASE + 0xB5000UL)
#define TRNG_BASE             (PERIPH_BASE + 0xB9000UL)
#define ECAP2_BASE            (PERIPH_BASE + 0xB6000UL)
#define ECAP3_BASE            (PERIPH_BASE + 0xB7000UL)
#define EQEI2_BASE            (PERIPH_BASE + 0xB2000UL)
#define EQEI3_BASE            (PERIPH_BASE + 0xB3000UL)
#define I2C3_BASE             (PERIPH_BASE + 0x83000UL)
#define I2C4_BASE             (PERIPH_BASE + 0x84000UL)
#define SC0_BASE              (PERIPH_BASE + 0x90000UL)
#define SC1_BASE              (PERIPH_BASE + 0x91000UL)
#define SC2_BASE              (PERIPH_BASE + 0x92000UL)
#define DAC0_BASE             (PERIPH_BASE + 0x47000UL)
#define DAC1_BASE             (PERIPH_BASE + 0x47040UL)
#define DACDBG_BASE           (PERIPH_BASE + 0x47FECUL)
#define OPA0_BASE             (PERIPH_BASE + 0x46000UL)

#define KPI_BASE              (PERIPH_BASE + 0x0C2000UL)
#define PSIO_BASE             (PERIPH_BASE + 0x0C3000UL)
#define ACMP23_BASE           (PERIPH_BASE + 0x0C9000UL)



/*@}*/ /* end of group PERIPHERAL_MEM_MAP */


/** @addtogroup PERIPHERAL_DECLARATION Peripheral Pointer
  The Declaration of Peripherals
  @{
 */

#define TCM                  ((TCM_T *)   TCM_BASE)
#define SYS                  ((SYS_T *)   SYS_BASE)
#define CLK                  ((CLK_T *)   CLK_BASE)
#define NMI                  ((NMI_T *)   NMI_BASE)
#define PA                   ((GPIO_T *)  GPIOA_BASE)
#define PB                   ((GPIO_T *)  GPIOB_BASE)
#define PC                   ((GPIO_T *)  GPIOC_BASE)
#define PD                   ((GPIO_T *)  GPIOD_BASE)
#define PE                   ((GPIO_T *)  GPIOE_BASE)
#define PF                   ((GPIO_T *)  GPIOF_BASE)
#define PG                   ((GPIO_T *)  GPIOG_BASE)
#define PH                   ((GPIO_T *)  GPIOH_BASE)
#define PI                   ((GPIO_T *)  GPIOI_BASE)
#define PJ                   ((GPIO_T *)  GPIOJ_BASE)
#define GPA                  ((GPIO_T *)  GPIOA_BASE)
#define GPB                  ((GPIO_T *)  GPIOB_BASE)
#define GPC                  ((GPIO_T *)  GPIOC_BASE)
#define GPD                  ((GPIO_T *)  GPIOD_BASE)
#define GPE                  ((GPIO_T *)  GPIOE_BASE)
#define GPF                  ((GPIO_T *)  GPIOF_BASE)
#define GPG                  ((GPIO_T *)  GPIOG_BASE)
#define GPH                  ((GPIO_T *)  GPIOH_BASE)
#define GPI                  ((GPIO_T *)  GPIOI_BASE)
#define GPJ                  ((GPIO_T *)  GPIOJ_BASE)
#define GPIO                 ((GPIO_INT_T *) GPIO_INT_BASE)
#define PDMA0                ((PDMA_T *)  PDMA0_BASE)
#define PDMA1                ((PDMA_T *)  PDMA1_BASE)
#define USBH                 ((USBH_T *)  USBH_BASE)
#define HSUSBH               ((HSUSBH_T *)  HSUSBH_BASE)
#define EMAC                 ((EMAC_T *)  EMAC_BASE)
#define FMC                  ((FMC_T *)   FMC_BASE)
#define SDH0                 ((SDH_T *)   SDH0_BASE)
#define SDH1                 ((SDH_T *)   SDH1_BASE)
#define EBI                  ((EBI_T *)   EBI_BASE)
#define CRC                  ((CRC_T *)   CRC_BASE)
#define TAMPER               ((TAMPER_T *) TAMPER_BASE)
#define KS                   ((KS_T *) KS_BASE)
#define HBI                  ((HBI_T *) HBI_BASE)
#define WDT                  ((WDT_T *)   WDT_BASE)
#define WWDT                 ((WWDT_T *)  WWDT_BASE)
#define RTC                  ((RTC_T *)   RTC_BASE)
#define EADC0                ((EADC_T *)  EADC0_BASE)
#define EADC1                ((EADC_T *)  EADC1_BASE)
#define EADC2                ((EADC_T *)  EADC2_BASE)
#define ACMP01               ((ACMP_T *)  ACMP01_BASE)
#define ACMP23               ((ACMP_T *)  ACMP23_BASE)
#define KPI                  ((KPI_T *) KPI_BASE)

#define I2S0                 ((I2S_T *)   I2S0_BASE)
#define I2S1                 ((I2S_T *)   I2S1_BASE)
#define USBD                 ((USBD_T *)  USBD_BASE)
#define OTG                  ((OTG_T *)   OTG_BASE)
#define HSUSBD               ((HSUSBD_T *)HSUSBD_BASE)
#define HSOTG                ((HSOTG_T *) HSOTG_BASE)
#define TIMER0               ((TIMER_T *) TIMER0_BASE)
#define TIMER1               ((TIMER_T *) TIMER1_BASE)
#define TIMER2               ((TIMER_T *) TIMER2_BASE)
#define TIMER3               ((TIMER_T *) TIMER3_BASE)
#define EPWM0                ((EPWM_T *)  EPWM0_BASE)
#define EPWM1                ((EPWM_T *)  EPWM1_BASE)
#define BPWM0                ((BPWM_T *)  BPWM0_BASE)
#define BPWM1                ((BPWM_T *)  BPWM1_BASE)
#define ECAP0                ((ECAP_T *)  ECAP0_BASE)
#define ECAP1                ((ECAP_T *)  ECAP1_BASE)
#define ECAP2                ((ECAP_T *)  ECAP2_BASE)
#define ECAP3                ((ECAP_T *)  ECAP3_BASE)
#define EQEI0                ((EQEI_T *)   EQEI0_BASE)
#define EQEI1                ((EQEI_T *)   EQEI1_BASE)
#define EQEI2                ((EQEI_T *)   EQEI2_BASE)
#define EQEI3                ((EQEI_T *)   EQEI3_BASE)
#define QSPI0                ((QSPI_T *)  QSPI0_BASE)
#define QSPI1                ((QSPI_T *)  QSPI1_BASE)
#define SPI0                 ((SPI_T *)   SPI0_BASE)
#define SPI1                 ((SPI_T *)   SPI1_BASE)
#define SPI2                 ((SPI_T *)   SPI2_BASE)
#define SPI3                 ((SPI_T *)   SPI3_BASE)
#define SPI4                 ((SPI_T *)   SPI4_BASE)
#define SPI5                 ((SPI_T *)   SPI5_BASE)
#define SPI6                 ((SPI_T *)   SPI6_BASE)
#define SPI7                 ((SPI_T *)   SPI7_BASE)
#define SPI8                 ((SPI_T *)   SPI8_BASE)
#define SPI9                 ((SPI_T *)   SPI9_BASE)
#define SPI10                ((SPI_T *)   SPI10_BASE)
#define UART0                ((UART_T *)  UART0_BASE)
#define UART1                ((UART_T *)  UART1_BASE)
#define UART2                ((UART_T *)  UART2_BASE)
#define UART3                ((UART_T *)  UART3_BASE)
#define UART4                ((UART_T *)  UART4_BASE)
#define UART5                ((UART_T *)  UART5_BASE)
#define UART6                ((UART_T *)  UART6_BASE)
#define UART7                ((UART_T *)  UART7_BASE)
#define UART8                ((UART_T *)  UART8_BASE)
#define UART9                ((UART_T *)  UART9_BASE)
#define I2C0                 ((I2C_T *)   I2C0_BASE)
#define I2C1                 ((I2C_T *)   I2C1_BASE)
#define I2C2                 ((I2C_T *)   I2C2_BASE)
#define I2C3                 ((I2C_T *)   I2C3_BASE)
#define I2C4                 ((I2C_T *)   I2C4_BASE)
#define SC0                  ((SC_T *)    SC0_BASE)
#define SC1                  ((SC_T *)    SC1_BASE)
#define SC2                  ((SC_T *)    SC2_BASE)
#define CANFD0               ((CANFD_T *)   CANFD0_BASE)
#define CANFD1               ((CANFD_T *)   CANFD1_BASE)
#define CANFD2               ((CANFD_T *)   CANFD2_BASE)
#define CANFD3               ((CANFD_T *)   CANFD3_BASE)
#define CRPT                 ((CRPT_T *)  CRPT_BASE)
#define TRNG                 ((TRNG_T *)  TRNG_BASE)
#define SPIM                 ((volatile SPIM_T *)  SPIM_BASE)
#define DAC0                 ((DAC_T *)   DAC0_BASE)
#define DAC1                 ((DAC_T *)   DAC1_BASE)
#define USPI0                ((USPI_T *) USCI0_BASE)                     /*!< USPI0 Configuration Struct                       */
#define OPA                  ((OPA_T *) OPA_BASE)
#define UI2C0                ((UI2C_T *) USCI0_BASE)                     /*!< UI2C0 Configuration Struct                       */
#define UI2C1                ((UI2C_T *) USCI1_BASE)                     /*!< UI2C1 Configuration Struct                       */
#define UUART0               ((UUART_T *) USCI0_BASE)                    /*!< UUART0 Configuration Struct                      */
#define CCAP                 ((CCAP_T *)  CCAP_BASE)
#define PSIO                 ((PSIO_T *)  PSIO_BASE)
#define BMC                  ((BMC_T *)  BMC_BASE)

/*@}*/ /* end of group ERIPHERAL_DECLARATION */

/** @addtogroup IO_ROUTINE I/O Routines
  The Declaration of I/O Routines
  @{
 */

typedef volatile unsigned char  vu8;        ///< Define 8-bit unsigned volatile data type
typedef volatile unsigned short vu16;       ///< Define 16-bit unsigned volatile data type
typedef volatile unsigned int   vu32;       ///< Define 32-bit unsigned volatile data type

/**
  * @brief Get a 8-bit unsigned value from specified address
  * @param[in] addr Address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified address
  */
#define M8(addr)  (*((vu8  *) (addr)))

/**
  * @brief Get a 16-bit unsigned value from specified address
  * @param[in] addr Address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified address
  * @note The input address must be 16-bit aligned
  */
#define M16(addr) (*((vu16 *) (addr)))

/**
  * @brief Get a 32-bit unsigned value from specified address
  * @param[in] addr Address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified address
  * @note The input address must be 32-bit aligned
  */
#define M32(addr) (*((vu32 *) (addr)))

/**
  * @brief Set a 32-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 32-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 32-bit aligned
  */
#define outpw(port,value)     *((volatile unsigned int *)(port)) = (value)

/**
  * @brief Get a 32-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified I/O port
  * @note The input port must be 32-bit aligned
  */
#define inpw(port)            (*((volatile unsigned int *)(port)))

/**
  * @brief Set a 16-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 16-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 16-bit aligned
  */
#define outps(port,value)     *((volatile unsigned short *)(port)) = (value)

/**
  * @brief Get a 16-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified I/O port
  * @note The input port must be 16-bit aligned
  */
#define inps(port)            (*((volatile unsigned short *)(port)))

/**
  * @brief Set a 8-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 8-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  */
#define outpb(port,value)     *((volatile unsigned char *)(port)) = (value)

/**
  * @brief Get a 8-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified I/O port
  */
#define inpb(port)            (*((volatile unsigned char *)(port)))

/**
  * @brief Set a 32-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 32-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 32-bit aligned
  */
#define outp32(port,value)    *((volatile unsigned int *)(port)) = (value)

/**
  * @brief Get a 32-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified I/O port
  * @note The input port must be 32-bit aligned
  */
#define inp32(port)           (*((volatile unsigned int *)(port)))

/**
  * @brief Set a 16-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 16-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 16-bit aligned
  */
#define outp16(port,value)    *((volatile unsigned short *)(port)) = (value)

/**
  * @brief Get a 16-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified I/O port
  * @note The input port must be 16-bit aligned
  */
#define inp16(port)           (*((volatile unsigned short *)(port)))

/**
  * @brief Set a 8-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 8-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  */
#define outp8(port,value)     *((volatile unsigned char *)(port)) = (value)

/**
  * @brief Get a 8-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified I/O port
  */
#define inp8(port)            (*((volatile unsigned char *)(port)))


/*@}*/ /* end of group IO_ROUTINE */

/******************************************************************************/
/*                Legacy Constants                                            */
/******************************************************************************/
/** @addtogroup Legacy_Constants Legacy Constants
  Legacy Constants
  @{
*/

#ifndef NULL
#define NULL           (0)      ///< NULL pointer
#endif

#define TRUE           (1UL)      ///< Boolean true, define to use in API parameters or return value
#define FALSE          (0UL)      ///< Boolean false, define to use in API parameters or return value

#define ENABLE         (1UL)      ///< Enable, define to use in API parameters
#define DISABLE        (0UL)      ///< Disable, define to use in API parameters

/* Define one bit mask */
#define BIT0     (0x00000001UL)       ///< Bit 0 mask of an 32 bit integer
#define BIT1     (0x00000002UL)       ///< Bit 1 mask of an 32 bit integer
#define BIT2     (0x00000004UL)       ///< Bit 2 mask of an 32 bit integer
#define BIT3     (0x00000008UL)       ///< Bit 3 mask of an 32 bit integer
#define BIT4     (0x00000010UL)       ///< Bit 4 mask of an 32 bit integer
#define BIT5     (0x00000020UL)       ///< Bit 5 mask of an 32 bit integer
#define BIT6     (0x00000040UL)       ///< Bit 6 mask of an 32 bit integer
#define BIT7     (0x00000080UL)       ///< Bit 7 mask of an 32 bit integer
#define BIT8     (0x00000100UL)       ///< Bit 8 mask of an 32 bit integer
#define BIT9     (0x00000200UL)       ///< Bit 9 mask of an 32 bit integer
#define BIT10    (0x00000400UL)       ///< Bit 10 mask of an 32 bit integer
#define BIT11    (0x00000800UL)       ///< Bit 11 mask of an 32 bit integer
#define BIT12    (0x00001000UL)       ///< Bit 12 mask of an 32 bit integer
#define BIT13    (0x00002000UL)       ///< Bit 13 mask of an 32 bit integer
#define BIT14    (0x00004000UL)       ///< Bit 14 mask of an 32 bit integer
#define BIT15    (0x00008000UL)       ///< Bit 15 mask of an 32 bit integer
#define BIT16    (0x00010000UL)       ///< Bit 16 mask of an 32 bit integer
#define BIT17    (0x00020000UL)       ///< Bit 17 mask of an 32 bit integer
#define BIT18    (0x00040000UL)       ///< Bit 18 mask of an 32 bit integer
#define BIT19    (0x00080000UL)       ///< Bit 19 mask of an 32 bit integer
#define BIT20    (0x00100000UL)       ///< Bit 20 mask of an 32 bit integer
#define BIT21    (0x00200000UL)       ///< Bit 21 mask of an 32 bit integer
#define BIT22    (0x00400000UL)       ///< Bit 22 mask of an 32 bit integer
#define BIT23    (0x00800000UL)       ///< Bit 23 mask of an 32 bit integer
#define BIT24    (0x01000000UL)       ///< Bit 24 mask of an 32 bit integer
#define BIT25    (0x02000000UL)       ///< Bit 25 mask of an 32 bit integer
#define BIT26    (0x04000000UL)       ///< Bit 26 mask of an 32 bit integer
#define BIT27    (0x08000000UL)       ///< Bit 27 mask of an 32 bit integer
#define BIT28    (0x10000000UL)       ///< Bit 28 mask of an 32 bit integer
#define BIT29    (0x20000000UL)       ///< Bit 29 mask of an 32 bit integer
#define BIT30    (0x40000000UL)       ///< Bit 30 mask of an 32 bit integer
#define BIT31    (0x80000000UL)       ///< Bit 31 mask of an 32 bit integer

/* Byte Mask Definitions */
#define BYTE0_Msk              (0x000000FFUL)         ///< Mask to get bit0~bit7 from a 32 bit integer
#define BYTE1_Msk              (0x0000FF00UL)         ///< Mask to get bit8~bit15 from a 32 bit integer
#define BYTE2_Msk              (0x00FF0000UL)         ///< Mask to get bit16~bit23 from a 32 bit integer
#define BYTE3_Msk              (0xFF000000UL)         ///< Mask to get bit24~bit31 from a 32 bit integer

#define GET_BYTE0(u32Param)    (((u32Param) & BYTE0_Msk)      )  /*!< Extract Byte 0 (Bit  0~ 7) from parameter u32Param */
#define GET_BYTE1(u32Param)    (((u32Param) & BYTE1_Msk) >>  8)  /*!< Extract Byte 1 (Bit  8~15) from parameter u32Param */
#define GET_BYTE2(u32Param)    (((u32Param) & BYTE2_Msk) >> 16)  /*!< Extract Byte 2 (Bit 16~23) from parameter u32Param */
#define GET_BYTE3(u32Param)    (((u32Param) & BYTE3_Msk) >> 24)  /*!< Extract Byte 3 (Bit 24~31) from parameter u32Param */

/*@}*/ /* end of group Legacy_Constants */


/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "nu_sys.h"
#include "nu_clk.h"

#include "nu_kpi.h"
#include "nu_rng.h"
#include "nu_keystore.h"
#include "nu_acmp.h"
#include "nu_dac.h"
#include "nu_uart.h"
#include "nu_usci_spi.h"
#include "nu_gpio.h"
#include "nu_ccap.h"
#include "nu_ecap.h"
#include "nu_hbi.h"
#include "nu_eqei.h"
#include "nu_timer.h"
#include "nu_timer_pwm.h"
#include "nu_pdma.h"
#include "nu_crypto.h"
#include "nu_trng.h"
#include "nu_fmc.h"
#include "nu_spim.h"
#include "nu_i2c.h"
#include "nu_i2s.h"
#include "nu_epwm.h"
#include "nu_eadc.h"
#include "nu_bpwm.h"
#include "nu_wdt.h"
#include "nu_wwdt.h"
#include "nu_crc.h"
#include "nu_ebi.h"
#include "nu_usci_i2c.h"
#include "nu_scuart.h"
#include "nu_sc.h"
#include "nu_spi.h"
#include "nu_qspi.h"
#include "nu_canfd.h"
#include "nu_rtc.h"
#include "nu_usci_uart.h"
#include "nu_sdh.h"
#include "nu_usbd.h"
#include "nu_hsusbd.h"
#include "nu_otg.h"
#include "nu_hsotg.h"
#include "nu_psio.h"
#include "nu_bmc.h"


#ifdef __cplusplus
}
#endif

#endif  /* __M460_H__ */

