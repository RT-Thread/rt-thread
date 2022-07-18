/**************************************************************************//**
 * @file     M2354.h
 * @version  V3.0
 * @brief    Peripheral Access Layer Header File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/**
  \mainpage Introduction
  *
  *
  * This user manual describes the usage of M2354 device driver
  *
  * <b>Disclaimer</b>
  *
  * The Software is furnished "AS IS", without warranty as to performance or results, and
  * the entire risk as to performance or results is assumed by YOU. Nuvoton disclaims all
  * warranties, express, implied or otherwise, with regard to the Software, its use, or
  * operation, including without limitation any and all warranties of merchantability, fitness
  * for a particular purpose, and non-infringement of intellectual property rights.
  *
  */


#ifndef __M2354_H__
#define __M2354_H__

/*=============================================================================*/
typedef volatile unsigned char  vu8;
typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
#define M8(adr)  (*((vu8  *) (adr)))
#define M16(adr) (*((vu16 *) (adr)))
#define M32(adr) (*((vu32 *) (adr)))

#define outpw(port,value)   (*((volatile unsigned int *)(port))=(value))
#define inpw(port)          ((*((volatile unsigned int *)(port))))
#define outpb(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inpb(port)          ((*((volatile unsigned char *)(port))))
#define outps(port,value)   (*((volatile unsigned short *)(port))=(value))
#define inps(port)          ((*((volatile unsigned short *)(port))))

#define outp32(port,value)  (*((volatile unsigned int *)(port))=(value))
#define inp32(port)         ((*((volatile unsigned int *)(port))))
#define outp8(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inp8(port)          ((*((volatile unsigned char *)(port))))
#define outp16(port,value)  (*((volatile unsigned short *)(port))=(value))
#define inp16(port)         ((*((volatile unsigned short *)(port))))


#define E_SUCCESS   0

#define TRUE        (1L)
#define FALSE       (0L)

#define ENABLE      1
#define DISABLE     0

/* Bit Mask Definitions */
#define BIT0    0x00000001UL
#define BIT1    0x00000002UL
#define BIT2    0x00000004UL
#define BIT3    0x00000008UL
#define BIT4    0x00000010UL
#define BIT5    0x00000020UL
#define BIT6    0x00000040UL
#define BIT7    0x00000080UL
#define BIT8    0x00000100UL
#define BIT9    0x00000200UL
#define BIT10   0x00000400UL
#define BIT11   0x00000800UL
#define BIT12   0x00001000UL
#define BIT13   0x00002000UL
#define BIT14   0x00004000UL
#define BIT15   0x00008000UL
#define BIT16   0x00010000UL
#define BIT17   0x00020000UL
#define BIT18   0x00040000UL
#define BIT19   0x00080000UL
#define BIT20   0x00100000UL
#define BIT21   0x00200000UL
#define BIT22   0x00400000UL
#define BIT23   0x00800000UL
#define BIT24   0x01000000UL
#define BIT25   0x02000000UL
#define BIT26   0x04000000UL
#define BIT27   0x08000000UL
#define BIT28   0x10000000UL
#define BIT29   0x20000000UL
#define BIT30   0x40000000UL
#define BIT31   0x80000000UL


/* Byte Mask Definitions */
#define BYTE0_Msk               (0x000000FFUL)
#define BYTE1_Msk               (0x0000FF00UL)
#define BYTE2_Msk               (0x00FF0000UL)
#define BYTE3_Msk               (0xFF000000UL)

#define _GET_BYTE0(u32Param)    (((u32Param) & BYTE0_Msk)        )  /*!< Extract Byte 0 (Bit  0~ 7) from parameter u32Param */
#define _GET_BYTE1(u32Param)    (((u32Param) & BYTE1_Msk) >>  8UL)  /*!< Extract Byte 1 (Bit  8~15) from parameter u32Param */
#define _GET_BYTE2(u32Param)    (((u32Param) & BYTE2_Msk) >> 16UL)  /*!< Extract Byte 2 (Bit 16~23) from parameter u32Param */
#define _GET_BYTE3(u32Param)    (((u32Param) & BYTE3_Msk) >> 24UL)  /*!< Extract Byte 3 (Bit 24~31) from parameter u32Param */



#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup CMSIS_Device CMSIS Definitions
  Configuration of the Cortex-M23 Processor and Core Peripherals
  @{
*/


/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

/**
 * @details  Interrupt Number Definition. The maximum of 32 Specific Interrupts are possible.
 */
typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn       = -14,      /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn            = -13,      /*!< 3 Cortex-M23 Hard Fault Interrupt                    */
    SVCall_IRQn               = -5,       /*!< 11 Cortex-M23 SV Call Interrupt                      */
    PendSV_IRQn               = -2,       /*!< 14 Cortex-M23 Pend SV Interrupt                      */
    SysTick_IRQn              = -1,       /*!< 15 Cortex-M23 System Tick Interrupt                  */

    /******  ARMIKMCU Swift specific Interrupt Numbers ************************************************/

    BOD_IRQn                      = 0,        /*!< Brown Out detection Interrupt                    */
    IRC_IRQn                      = 1,        /*!< Internal RC Interrupt                            */
    PWRWU_IRQn                    = 2,        /*!< Power Down Wake Up Interrupt                     */
    RAMPE_IRQn                    = 3,        /*!< SRAM parity check failed Interrupt               */
    CKFAIL_IRQn                   = 4,        /*!< Clock failed Interrupt                           */
    ISP_IRQn                      = 5,        /*!< FMC ISP Interrupt                                */
    RTC_IRQn                      = 6,        /*!< Real Time Clock Interrupt                        */
    RTC_TAMPER_IRQn               = 7,        /*!< RTC Tamper detection Interrupt                   */
    WDT_IRQn                      = 8,        /*!< Watchdog Timer Interrupt                         */
    WWDT_IRQn                     = 9,        /*!< Window Watchdog Timer Interrupt                  */
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
    QSPI0_IRQn                    = 22,       /*!< QSPI0 Interrupt                                  */
    SPI0_IRQn                     = 23,       /*!< SPI0 Interrupt                                   */
    BRAKE0_IRQn                   = 24,       /*!< BRAKE0 Interrupt                                 */
    EPWM0_P0_IRQn                 = 25,       /*!< EPWM0P0 Interrupt                                */
    EPWM0_P1_IRQn                 = 26,       /*!< EPWM0P1 Interrupt                                */
    EPWM0_P2_IRQn                 = 27,       /*!< EPWM0P2 Interrupt                                */
    BRAKE1_IRQn                   = 28,       /*!< BRAKE1 Interrupt                                 */
    EPWM1_P0_IRQn                 = 29,       /*!< EPWM1P0 Interrupt                                */
    EPWM1_P1_IRQn                 = 30,       /*!< EPWM1P1 Interrupt                                */
    EPWM1_P2_IRQn                 = 31,       /*!< EPWM1P2 Interrupt                                */
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
    EADC0_IRQn                    = 42,       /*!< EADC Source 0 Interrupt                          */
    EADC1_IRQn                    = 43,       /*!< EADC Source 1 Interrupt                          */
    ACMP01_IRQn                   = 44,       /*!< Analog Comparator 0 and 1 Interrupt              */
    EADC2_IRQn                    = 46,       /*!< EADC Source 2 Interrupt                          */
    EADC3_IRQn                    = 47,       /*!< EADC Source 3 Interrupt                          */
    UART2_IRQn                    = 48,       /*!< UART2 Interrupt                                  */
    UART3_IRQn                    = 49,       /*!< UART3 Interrupt                                  */
    SPI1_IRQn                     = 51,       /*!< SPI1 Interrupt                                   */
    SPI2_IRQn                     = 52,       /*!< SPI2 Interrupt                                   */
    USBD_IRQn                     = 53,       /*!< USB device Interrupt                             */
    USBH_IRQn                     = 54,       /*!< USB host Interrupt                               */
    USBOTG_IRQn                   = 55,       /*!< USB OTG Interrupt                                */
    CAN0_IRQn                     = 56,       /*!< CAN0 Interrupt                                   */
    SC0_IRQn                      = 58,       /*!< Smart Card 0 Interrupt                           */
    SC1_IRQn                      = 59,       /*!< Smart Card 1 Interrupt                           */
    SC2_IRQn                      = 60,       /*!< Smart Card 2 Interrupt                           */
    SPI3_IRQn                     = 62,       /*!< SPI3 Interrupt                                   */
    SDH0_IRQn                     = 64,       /*!< SDH0 Interrupt                                   */
    I2S0_IRQn                     = 68,       /*!< I2S0 Interrupt                                   */
    CRPT_IRQn                     = 71,       /*!< CRPT Interrupt                                   */
    GPG_IRQn                      = 72,       /*!< GPIO Port G Interrupt                            */
    EINT6_IRQn                    = 73,       /*!< External Input 6 Interrupt                       */
    UART4_IRQn                    = 74,       /*!< UART4 Interrupt                                  */
    UART5_IRQn                    = 75,       /*!< UART5 Interrupt                                  */
    USCI0_IRQn                    = 76,       /*!< USCI0 Interrupt                                  */
    USCI1_IRQn                    = 77,       /*!< USCI1 Interrupt                                  */
    BPWM0_IRQn                    = 78,       /*!< BPWM0 Interrupt                                  */
    BPWM1_IRQn                    = 79,       /*!< BPWM1 Interrupt                                  */
    I2C2_IRQn                     = 82,       /*!< I2C2 Interrupt                                   */
    QEI0_IRQn                     = 84,       /*!< QEI0 Interrupt                                   */
    QEI1_IRQn                     = 85,       /*!< QEI1 Interrupt                                   */
    ECAP0_IRQn                    = 86,       /*!< ECAP0 Interrupt                                  */
    ECAP1_IRQn                    = 87,       /*!< ECAP1 Interrupt                                  */
    GPH_IRQn                      = 88,       /*!< GPIO Port H Interrupt                            */
    EINT7_IRQn                    = 89,       /*!< External Input 7 Interrupt                       */
    PDMA1_IRQn                    = 98,       /*!< Peripheral DMA 1 Interrupt                       */
    SCU_IRQn                      = 99,       /*!< SCU Interrupt                                    */
    LCD_IRQn                      = 100,      /*!< LCD interrupt                                    */
    TRNG_IRQn                     = 101,      /*!< TRNG interrupt                                   */
    KS_IRQn                       = 109,      /*!< Key Store interrupt                              */
    TAMPER_IRQn                   = 110,      /*!< TAMPER interrupt                                 */
    EWDT_IRQn                     = 111,      /*!< Extra Watchdog Timer interrupt                   */
    EWWDT_IRQn                    = 112,      /*!< Extra Window Watchdog Timer interrupt            */
    NS_ISP_IRQn                   = 113,      /*!< Non-secure FMC ISP interrupt                     */
    TMR4_IRQn                     = 114,      /*!< Timer 4 Interrupt                                */
    TMR5_IRQn                     = 115,      /*!< Timer 5 Interrupt                                */


} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

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


/* --------  Configuration of the Cortex-ARMv8MBL Processor and Core Peripherals  ------- */
#define __ARMv8MBL_REV            0x0000U   /* Core revision r0p0 */
#define __SAU_PRESENT             1U        /* SAU present */
#define __SAUREGION_PRESENT       1U        /* SAU present */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          2U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define USE_ASSERT                0U        /* Define to use Assert function or not */

/**@}*/ /* end of group CMSIS */

#include "core_armv8mbl.h"                  /* Processor and core peripherals */
#include "system_M2354.h"                   /* System Header */
#include "nu_partition_M2354.h"

/**
 * Initialize the system clock
 *
 * @brief  Setup the micro controller system
 *         Initialize the PLL and update the SystemFrequency variable
 */
extern void SystemInit(void);


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/


#include "acmp_reg.h"
#include "bpwm_reg.h"
#include "can_reg.h"
#include "clk_reg.h"
#include "crc_reg.h"
#include "dac_reg.h"
#include "eadc_reg.h"
#include "ebi_reg.h"
#include "ecap_reg.h"
#include "fmc_reg.h"
#include "gpio_reg.h"
#include "hdiv_reg.h"
#include "i2c_reg.h"
#include "i2s_reg.h"
#include "pdma_reg.h"
#include "epwm_reg.h"
#include "qei_reg.h"
#include "rtc_reg.h"
#include "sc_reg.h"
#include "scu_reg.h"
#include "sdh_reg.h"
#include "qspi_reg.h"
#include "spi_reg.h"
#include "sys_reg.h"
#include "timer_reg.h"
#include "trng_reg.h"
#include "uart_reg.h"
#include "ui2c_reg.h"
#include "usbh_reg.h"
#include "usbd_reg.h"
#include "otg_reg.h"
#include "crpt_reg.h"
#include "uspi_reg.h"
#include "uuart_reg.h"
#include "wdt_reg.h"
#include "wwdt_reg.h"
#include "keystore_reg.h"
#include "tamper_reg.h"
#include "lcd_reg.h"
#include "ewdt_reg.h"
#include "ewwdt_reg.h"



/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup PERIPHERAL_BASE Peripheral Memory Base
  Memory Mapped Structure for Series Peripheral
  @{
 */


/* Peripheral and SRAM base address */
#define SRAM_BASE            (0x20000000UL)                              /*!< (SRAM      ) Base Address */
#define PERIPH_BASE          (0x40000000UL)                              /*!< (Peripheral) Base Address */
#define NS_OFFSET            (0x10000000UL)

/* Peripheral memory map */
#define AHBPERIPH_BASE       PERIPH_BASE
#define APBPERIPH_BASE       (PERIPH_BASE + 0x00040000UL)

/*!< AHB peripherals */
#define SYS_BASE             (AHBPERIPH_BASE + 0x00000UL)
#define CLK_BASE             (AHBPERIPH_BASE + 0x00200UL)
#define INT_BASE             (AHBPERIPH_BASE + 0x00300UL)
#define GPIO_BASE            (AHBPERIPH_BASE + 0x04000UL)
#define GPIOA_BASE           (AHBPERIPH_BASE + 0x04000UL)
#define GPIOB_BASE           (AHBPERIPH_BASE + 0x04040UL)
#define GPIOC_BASE           (AHBPERIPH_BASE + 0x04080UL)
#define GPIOD_BASE           (AHBPERIPH_BASE + 0x040C0UL)
#define GPIOE_BASE           (AHBPERIPH_BASE + 0x04100UL)
#define GPIOF_BASE           (AHBPERIPH_BASE + 0x04140UL)
#define GPIOG_BASE           (AHBPERIPH_BASE + 0x04180UL)
#define GPIOH_BASE           (AHBPERIPH_BASE + 0x041C0UL)
#define GPIO_DBCTL_BASE      (AHBPERIPH_BASE + 0x04440UL)
#define GPIO_PIN_DATA_BASE   (AHBPERIPH_BASE + 0x04800UL)
#define PDMA0_BASE           (AHBPERIPH_BASE + 0x08000UL)
#define PDMA1_BASE           (AHBPERIPH_BASE + 0x18000UL)
#define USBH_BASE            (AHBPERIPH_BASE + 0x09000UL)
#define FMC_BASE             (AHBPERIPH_BASE + 0x0C000UL)
#define SDH0_BASE            (AHBPERIPH_BASE + 0x0D000UL)
#define SDH1_BASE            (AHBPERIPH_BASE + 0x0E000UL)
#define EBI_BASE             (AHBPERIPH_BASE + 0x10000UL)
#define CRC_BASE             (AHBPERIPH_BASE + 0x31000UL)
#define CRPT_BASE            (AHBPERIPH_BASE + 0x32000UL)
#define SCU_BASE             (AHBPERIPH_BASE + 0x2F000UL)
#define FVC_BASE             (AHBPERIPH_BASE + 0x2F500UL)
#define DPM_BASE             (AHBPERIPH_BASE + 0x2F600UL)
#define PLM_BASE             (AHBPERIPH_BASE + 0x2F700UL)

#define BTF_BASE             (AHBPERIPH_BASE + 0x2F800UL)

/*!< APB peripherals */
#define WDT_BASE             (APBPERIPH_BASE + 0x00000UL)
#define WWDT_BASE            (APBPERIPH_BASE + 0x00100UL)
#define RTC_BASE             (APBPERIPH_BASE + 0x01000UL)
#define EADC_BASE            (APBPERIPH_BASE + 0x03000UL)
#define ACMP01_BASE          (APBPERIPH_BASE + 0x05000UL)
#define DAC0_BASE            (APBPERIPH_BASE + 0x07000UL)
#define DAC1_BASE            (APBPERIPH_BASE + 0x07040UL)
#define I2S0_BASE            (APBPERIPH_BASE + 0x08000UL)
#define OTG_BASE             (APBPERIPH_BASE + 0x0D000UL)
#define TMR01_BASE           (APBPERIPH_BASE + 0x10000UL)
#define TMR23_BASE           (APBPERIPH_BASE + 0x11000UL)
#define TMR45_BASE           (APBPERIPH_BASE + 0x12000UL)
#define EPWM0_BASE           (APBPERIPH_BASE + 0x18000UL)
#define EPWM1_BASE           (APBPERIPH_BASE + 0x19000UL)
#define BPWM0_BASE           (APBPERIPH_BASE + 0x1A000UL)
#define BPWM1_BASE           (APBPERIPH_BASE + 0x1B000UL)
#define QSPI0_BASE           (APBPERIPH_BASE + 0x20000UL)
#define SPI0_BASE            (APBPERIPH_BASE + 0x21000UL)
#define SPI1_BASE            (APBPERIPH_BASE + 0x22000UL)
#define SPI2_BASE            (APBPERIPH_BASE + 0x23000UL)
#define SPI3_BASE            (APBPERIPH_BASE + 0x24000UL)
#define UART0_BASE           (APBPERIPH_BASE + 0x30000UL)
#define UART0_BASE           (APBPERIPH_BASE + 0x30000UL)
#define UART1_BASE           (APBPERIPH_BASE + 0x31000UL)
#define UART2_BASE           (APBPERIPH_BASE + 0x32000UL)
#define UART3_BASE           (APBPERIPH_BASE + 0x33000UL)
#define UART4_BASE           (APBPERIPH_BASE + 0x34000UL)
#define UART5_BASE           (APBPERIPH_BASE + 0x35000UL)
#define I2C0_BASE            (APBPERIPH_BASE + 0x40000UL)
#define I2C1_BASE            (APBPERIPH_BASE + 0x41000UL)
#define I2C2_BASE            (APBPERIPH_BASE + 0x42000UL)
#define SC0_BASE             (APBPERIPH_BASE + 0x50000UL)
#define SC1_BASE             (APBPERIPH_BASE + 0x51000UL)
#define SC2_BASE             (APBPERIPH_BASE + 0x52000UL)
#define CAN0_BASE            (APBPERIPH_BASE + 0x60000UL)
#define QEI0_BASE            (APBPERIPH_BASE + 0x70000UL)
#define QEI1_BASE            (APBPERIPH_BASE + 0x71000UL)
#define ECAP0_BASE           (APBPERIPH_BASE + 0x74000UL)
#define ECAP1_BASE           (APBPERIPH_BASE + 0x75000UL)
#define TRNG_BASE            (APBPERIPH_BASE + 0x79000UL)
#define USBD_BASE            (APBPERIPH_BASE + 0x80000UL)
#define USCI0_BASE           (APBPERIPH_BASE + 0x90000UL)
#define USCI1_BASE           (APBPERIPH_BASE + 0x91000UL)

#define EWDT_BASE            (APBPERIPH_BASE + 0x02000UL)
#define EWWDT_BASE           (APBPERIPH_BASE + 0x02100UL)


#define KS_BASE              (AHBPERIPH_BASE + 0x35000UL)
#define TAMPER_BASE          (AHBPERIPH_BASE + 0xBD000UL)
#define LCD_BASE             (AHBPERIPH_BASE + 0xBB000UL)



/**@}*/ /* PERIPHERAL */

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

/** @addtogroup PMODULE Peripheral Pointer
  The Declaration of Peripheral Pointer
  @{
 */

/** @addtogroup PMODULE_S Secure Peripheral Pointer
 The Declaration of Secure Peripheral Pointer
 @{
*/

#define PA_S                  ((GPIO_T *) GPIOA_BASE)                     /*!< GPIO PORTA Pointer                 */
#define PB_S                  ((GPIO_T *) GPIOB_BASE)                     /*!< GPIO PORTB Pointer                 */
#define PC_S                  ((GPIO_T *) GPIOC_BASE)                     /*!< GPIO PORTC Pointer                 */
#define PD_S                  ((GPIO_T *) GPIOD_BASE)                     /*!< GPIO PORTD Pointer                 */
#define PE_S                  ((GPIO_T *) GPIOE_BASE)                     /*!< GPIO PORTE Pointer                 */
#define PF_S                  ((GPIO_T *) GPIOF_BASE)                     /*!< GPIO PORTF Pointer                 */
#define PG_S                  ((GPIO_T *) GPIOG_BASE)                     /*!< GPIO PORTG Pointer                 */
#define PH_S                  ((GPIO_T *) GPIOH_BASE)                     /*!< GPIO PORTH Pointer                 */

#define UART0_S               ((UART_T *) UART0_BASE)                     /*!< UART0 Pointer                      */
#define UART1_S               ((UART_T *) UART1_BASE)                     /*!< UART1 Pointer                      */
#define UART2_S               ((UART_T *) UART2_BASE)                     /*!< UART2 Pointer                      */
#define UART3_S               ((UART_T *) UART3_BASE)                     /*!< UART3 Pointer                      */
#define UART4_S               ((UART_T *) UART4_BASE)                     /*!< UART4 Pointer                      */
#define UART5_S               ((UART_T *) UART5_BASE)                     /*!< UART5 Pointer                      */


#define TIMER0_S              ((TIMER_T *) TMR01_BASE)                    /*!< TIMER0 Pointer                      */
#define TIMER1_S              ((TIMER_T *) (TMR01_BASE + 0x100UL))        /*!< TIMER1 Pointer                      */
#define TIMER2_S              ((TIMER_T *) TMR23_BASE)                    /*!< TIMER2 Pointer                      */
#define TIMER3_S              ((TIMER_T *) (TMR23_BASE + 0x100UL))        /*!< TIMER3 Pointer                      */
#define TIMER4_S              ((TIMER_T *) TMR45_BASE)                    /*!< TIMER4 Pointer                      */
#define TIMER5_S              ((TIMER_T *) (TMR45_BASE + 0x100UL))        /*!< TIMER5 Pointer                      */

#define WDT_S                 ((WDT_T *) WDT_BASE)                        /*!< Watch Dog Timer Pointer             */

#define WWDT_S                ((WWDT_T *) WWDT_BASE)                      /*!< Window Watch Dog Timer Pointer      */

#define QSPI0_S               ((QSPI_T *) QSPI0_BASE)                     /*!< QSPI0 Pointer                       */
#define SPI0_S                ((SPI_T *) SPI0_BASE)                       /*!< SPI0 Pointer                        */
#define SPI1_S                ((SPI_T *) SPI1_BASE)                       /*!< SPI1 Pointer                        */
#define SPI2_S                ((SPI_T *) SPI2_BASE)                       /*!< SPI2 Pointer                        */
#define SPI3_S                ((SPI_T *) SPI3_BASE)                       /*!< SPI3 Pointer                        */

#define I2S0_S                ((I2S_T *) I2S0_BASE)                       /*!< I2S0 Pointer                        */

#define I2C0_S                ((I2C_T *) I2C0_BASE)                       /*!< I2C0 Pointer                        */
#define I2C1_S                ((I2C_T *) I2C1_BASE)                       /*!< I2C1 Pointer                        */
#define I2C2_S                ((I2C_T *) I2C2_BASE)                       /*!< I2C1 Pointer                        */

#define QEI0_S                ((QEI_T *) QEI0_BASE)                       /*!< QEI0 Pointer                        */
#define QEI1_S                ((QEI_T *) QEI1_BASE)                       /*!< QEI1 Pointer                        */

#define RTC_S                 ((RTC_T *) RTC_BASE)                        /*!< RTC Pointer                         */

#define ACMP01_S              ((ACMP_T *) ACMP01_BASE)                    /*!< ACMP01 Pointer                      */

#define CLK_S                 ((CLK_T *) CLK_BASE)                        /*!< System Clock Controller Pointer     */

#define DAC0_S                ((DAC_T *) DAC0_BASE)                       /*!< DAC0 Pointer                        */
#define DAC1_S                ((DAC_T *) DAC1_BASE)                       /*!< DAC1 Pointer                        */

#define EADC_S                ((EADC_T *) EADC_BASE)                      /*!< EADC Pointer                        */

#define SYS_S                 ((SYS_T *) SYS_BASE)                        /*!< System Global Controller Pointer    */

#define SYSINT_S              ((SYS_INT_T *) INT_BASE)                    /*!< Interrupt Source Controller Pointer */

#define FMC_S                 ((FMC_T *) FMC_BASE)                        /*!< Flash Memory Controller */

#define SDH0_S                ((SDH_T *)   SDH0_BASE)

#define CRPT_S                ((CRPT_T *) CRPT_BASE)                      /*!< Crypto Accelerator Pointer          */
#define TRNG_S                ((TRNG_T *)TRNG_BASE)                       /*!< True Random Number Pointer          */

#define BPWM0_S               ((BPWM_T *) BPWM0_BASE)                     /*!< BPWM0 Pointer                       */
#define BPWM1_S               ((BPWM_T *) BPWM1_BASE)                     /*!< BPWM1 Pointer                       */

#define EPWM0_S               ((EPWM_T *) EPWM0_BASE)                     /*!< EPWM0 Pointer                       */
#define EPWM1_S               ((EPWM_T *) EPWM1_BASE)                     /*!< EPWM1 Pointer                       */

#define SC0_S                 ((SC_T *) SC0_BASE)                         /*!< SC0 Pointer                         */
#define SC1_S                 ((SC_T *) SC1_BASE)                         /*!< SC1 Pointer                         */
#define SC2_S                 ((SC_T *) SC2_BASE)                         /*!< SC2 Pointer                         */

#define EBI_S                 ((EBI_T *) EBI_BASE)                        /*!< EBI Pointer                         */

#define CRC_S                 ((CRC_T *) CRC_BASE)                        /*!< CRC Pointer                         */

#define USBD_S                ((USBD_T *) USBD_BASE)                      /*!< USB Device Pointer                  */
#define USBH_S                ((USBH_T *) USBH_BASE)                      /*!< USBH Pointer                        */
#define OTG_S                 ((OTG_T *) OTG_BASE)                        /*!< OTG Pointer                         */

#define PDMA0_S               ((PDMA_T *) PDMA0_BASE)                     /*!< PDMA0 Pointer                        */
#define PDMA1_S               ((PDMA_T *) PDMA1_BASE)                     /*!< PDMA1 Pointer                        */

#define UI2C0_S               ((UI2C_T *) USCI0_BASE)                     /*!< UI2C0 Pointer                       */
#define UI2C1_S               ((UI2C_T *) USCI1_BASE)                     /*!< UI2C1 Pointer                       */

#define USPI0_S               ((USPI_T *) USCI0_BASE)                     /*!< USPI0 Pointer                       */
#define USPI1_S               ((USPI_T *) USCI1_BASE)                     /*!< USPI1 Pointer                       */

#define UUART0_S              ((UUART_T *) USCI0_BASE)                    /*!< UUART0 Pointer                      */
#define UUART1_S              ((UUART_T *) USCI1_BASE)                    /*!< UUART1 Pointer                      */

#define SCU_S                 ((SCU_T *) SCU_BASE)                        /*!< SCU Pointer                         */
#define ECAP0_S               ((ECAP_T *) ECAP0_BASE)                     /*!< ECAP0 Pointer                       */
#define ECAP1_S               ((ECAP_T *) ECAP1_BASE)                     /*!< ECAP1 Pointer                       */

#define CAN0_S                ((CAN_T *)CAN0_BASE)                        /*!< CAN0 Pointer                        */

#define KS_S                  ((KS_T *)KS_BASE)                           /*!< Key Store Pointer                   */
#define TAMPER_S              ((TAMPER_T *)TAMPER_BASE)                   /*!< TAMPER Pointer                      */
#define LCD_S                 ((LCD_T *)LCD_BASE)                         /*!< LCD Pointer                         */

#define EWDT_S                ((EWDT_T *) EWDT_BASE)                      /*!< Extra Watch Dog Timer Pointer       */

#define EWWDT_S               ((EWWDT_T *) EWWDT_BASE)                    /*!< Extra Window Watch Dog Timer Pointer*/

#define FVC_S                 ((FVC_T *) FVC_BASE)
#define DPM_S                 ((DPM_T *) DPM_BASE)
#define PLM_S                 ((PLM_T *) PLM_BASE)



/**@}*/ /* end of group PMODULE_S */

/** @addtogroup PMODULE_NS Non-secure Peripheral Pointer
 The Declaration of Non-secure Peripheral Pointer
 @{
*/


#define PA_NS                  ((GPIO_T *)  (GPIOA_BASE+NS_OFFSET))                     /*!< GPIO PORTA Pointer                        */
#define PB_NS                  ((GPIO_T *)  (GPIOB_BASE+NS_OFFSET))                     /*!< GPIO PORTB Pointer                        */
#define PC_NS                  ((GPIO_T *)  (GPIOC_BASE+NS_OFFSET))                     /*!< GPIO PORTC Pointer                        */
#define PD_NS                  ((GPIO_T *)  (GPIOD_BASE+NS_OFFSET))                     /*!< GPIO PORTD Pointer                        */
#define PE_NS                  ((GPIO_T *)  (GPIOE_BASE+NS_OFFSET))                     /*!< GPIO PORTE Pointer                        */
#define PF_NS                  ((GPIO_T *)  (GPIOF_BASE+NS_OFFSET))                     /*!< GPIO PORTF Pointer                        */
#define PG_NS                  ((GPIO_T *)  (GPIOG_BASE+NS_OFFSET))                     /*!< GPIO PORTG Pointer                        */
#define PH_NS                  ((GPIO_T *)  (GPIOH_BASE+NS_OFFSET))                     /*!< GPIO PORTH Pointer                        */
#define UART0_NS               ((UART_T *)  (UART0_BASE+NS_OFFSET))                     /*!< UART0 Pointer                       */
#define UART1_NS               ((UART_T *)  (UART1_BASE+NS_OFFSET))                     /*!< UART1 Pointer                       */
#define UART2_NS               ((UART_T *)  (UART2_BASE+NS_OFFSET))                     /*!< UART2 Pointer                       */
#define UART3_NS               ((UART_T *)  (UART3_BASE+NS_OFFSET))                     /*!< UART3 Pointer                       */
#define UART4_NS               ((UART_T *)  (UART4_BASE+NS_OFFSET))                     /*!< UART4 Pointer                       */
#define UART5_NS               ((UART_T *)  (UART5_BASE+NS_OFFSET))                     /*!< UART5 Pointer                       */
#define TIMER2_NS              ((TIMER_T *) (TMR23_BASE+NS_OFFSET))                     /*!< TIMER2 Pointer                      */
#define TIMER3_NS              ((TIMER_T *) (TMR23_BASE+NS_OFFSET+0x100UL))             /*!< TIMER3 Pointer                      */
#define TIMER4_NS              ((TIMER_T *) (TMR45_BASE+NS_OFFSET))                     /*!< TIMER4 Pointer                      */
#define TIMER5_NS              ((TIMER_T *) (TMR45_BASE+NS_OFFSET+0x100UL))             /*!< TIMER5 Pointer                      */
#define QSPI0_NS               ((QSPI_T *)  (QSPI0_BASE+NS_OFFSET))                      /*!< QSPI0 Pointer                       */
#define SPI0_NS                ((SPI_T *)   (SPI0_BASE+NS_OFFSET))                       /*!< SPI0 Pointer                        */
#define SPI1_NS                ((SPI_T *)   (SPI1_BASE+NS_OFFSET))                       /*!< SPI1 Pointer                        */
#define SPI2_NS                ((SPI_T *)   (SPI2_BASE+NS_OFFSET))                       /*!< SPI2 Pointer                        */
#define SPI3_NS                ((SPI_T *)   (SPI3_BASE+NS_OFFSET))                       /*!< SPI3 Pointer                        */
#define I2S0_NS                ((I2S_T *)   (I2S0_BASE+NS_OFFSET))                       /*!< I2S0 Pointer                        */
#define I2C0_NS                ((I2C_T *)   (I2C0_BASE+NS_OFFSET))                       /*!< I2C0 Pointer                        */
#define I2C1_NS                ((I2C_T *)   (I2C1_BASE+NS_OFFSET))                       /*!< I2C1 Pointer                        */
#define I2C2_NS                ((I2C_T *)   (I2C2_BASE+NS_OFFSET))                       /*!< I2C1 Pointer                        */
#define QEI0_NS                ((QEI_T *)   (QEI0_BASE+NS_OFFSET))                       /*!< QEI0 Pointer                        */
#define QEI1_NS                ((QEI_T *)   (QEI1_BASE+NS_OFFSET))                       /*!< QEI1 Pointer                        */
#define ACMP01_NS              ((ACMP_T *)  (ACMP01_BASE+NS_OFFSET))                    /*!< ACMP01 Pointer                      */
#define DAC0_NS                ((DAC_T *)   (DAC0_BASE+NS_OFFSET))                       /*!< DAC0 Pointer                        */
#define DAC1_NS                ((DAC_T *)   (DAC1_BASE+NS_OFFSET))                       /*!< DAC1 Pointer                        */
#define EADC_NS                ((EADC_T *)  (EADC_BASE+NS_OFFSET))                      /*!< EADC Pointer                        */
#define SDH0_NS                ((SDH_T *)  (SDH0_BASE +NS_OFFSET))
#define CRPT_NS                ((CRPT_T *) (CRPT_BASE +NS_OFFSET))
#define TRNG_NS                ((TRNG_T *) (TRNG_BASE +NS_OFFSET))                     /*!< Random Number Generator Pointer    */
#define BPWM0_NS               ((BPWM_T *) (BPWM0_BASE+NS_OFFSET))                     /*!< BPWM0 Pointer                       */
#define BPWM1_NS               ((BPWM_T *) (BPWM1_BASE+NS_OFFSET))                     /*!< BPWM1 Pointer                       */
#define EPWM0_NS               ((EPWM_T *) (EPWM0_BASE+NS_OFFSET))                     /*!< EPWM0 Pointer                       */
#define EPWM1_NS               ((EPWM_T *) (EPWM1_BASE+NS_OFFSET))                     /*!< EPWM1 Pointer                       */
#define SC0_NS                 ((SC_T *)   (SC0_BASE  +NS_OFFSET))                     /*!< SC0 Pointer                         */
#define SC1_NS                 ((SC_T *)   (SC1_BASE  +NS_OFFSET))                     /*!< SC1 Pointer                         */
#define SC2_NS                 ((SC_T *)   (SC2_BASE  +NS_OFFSET))                     /*!< SC2 Pointer                         */
#define EBI_NS                 ((EBI_T *)  (EBI_BASE  +NS_OFFSET))                     /*!< EBI Pointer                         */
#define CRC_NS                 ((CRC_T *)  (CRC_BASE  +NS_OFFSET))                     /*!< CRC Pointer                         */
#define USBD_NS                ((USBD_T *) (USBD_BASE +NS_OFFSET))                     /*!< USB Device Pointer                  */
#define USBH_NS                ((USBH_T *) (USBH_BASE +NS_OFFSET))                     /*!< USBH Pointer                        */
#define OTG_NS                 ((OTG_T *)  (OTG_BASE  +NS_OFFSET))                     /*!< OTG Pointer                         */
#define PDMA1_NS               ((PDMA_T *)   (PDMA1_BASE +NS_OFFSET))                     /*!< PDMA1 Pointer                        */
#define UI2C0_NS                ((UI2C_T *)  (USCI0_BASE +NS_OFFSET))                     /*!< UI2C0 Pointer                       */
#define UI2C1_NS                ((UI2C_T *)  (USCI1_BASE +NS_OFFSET))                     /*!< UI2C1 Pointer                       */
#define USPI0_NS                ((USPI_T *)  (USCI0_BASE +NS_OFFSET))                     /*!< USPI0 Pointer                       */
#define USPI1_NS                ((USPI_T *)  (USCI1_BASE +NS_OFFSET))                     /*!< USPI1 Pointer                       */
#define UUART0_NS               ((UUART_T *) (USCI0_BASE+NS_OFFSET))                    /*!< UUART0 Pointer                      */
#define UUART1_NS               ((UUART_T *) (USCI1_BASE+NS_OFFSET))                    /*!< UUART1 Pointer                      */
#define SCU_NS                 ((SCU_T *)    (SCU_BASE  +NS_OFFSET))                        /*!< SCU Pointer                         */
#define ECAP0_NS               ((ECAP_T *)   (ECAP0_BASE+NS_OFFSET))                     /*!< ECAP0 Pointer                       */
#define ECAP1_NS               ((ECAP_T *)   (ECAP1_BASE+NS_OFFSET))                     /*!< ECAP1 Pointer                       */
#define CAN0_NS                ((CAN_T *)    (CAN0_BASE +NS_OFFSET))                        /*!< CAN0 Pointer                        */

#define EWDT_NS                ((EWDT_T *) (EWDT_BASE+NS_OFFSET))                     /*!< Extra Watch Dog Timer Pointer       */

#define EWWDT_NS               ((EWWDT_T *) (EWWDT_BASE+NS_OFFSET))                   /*!< Extra Window Watch Dog Timer Pointer*/


#define LCD_NS                 ((LCD_T *)(LCD_BASE+NS_OFFSET))                        /*!< LCD Pointer                         */
#define DPM_NS                 ((DPM_T *)(DPM_BASE+NS_OFFSET))
#define FMC_NS                 ((FMC_T *)(FMC_BASE+NS_OFFSET))                        /*!< Flash Memory Controller */
#define SYS_NS                 ((SYS_T *)(SYS_BASE+NS_OFFSET))
#define CLK_NS                 ((CLK_T *)(CLK_BASE+NS_OFFSET))


/**@}*/ /* end of group PMODULE_NS */

/** @addtogroup PMODULE_SNS Peripheral Pointer
 The Declaration of Peripheral Pointer
 @{
*/

/* Always Secure Modules */
#define SYS SYS_S
#define SYSINT SYSINT_S
#define CLK CLK_S
#define FMC FMC_S
#define SCU SCU_S
#define FVC FVC_S
#define PLM PLM_S
#define DPM DPM_S
#define PDMA0 PDMA0_S
#define WDT WDT_S
#define WWDT WWDT_S
#define TIMER0  TIMER0_S
#define TIMER1  TIMER1_S
#define RTC RTC_S
#define KS KS_S
#define TAMPER TAMPER_S

#if defined (SCU_INIT_PNSSET0_VAL) && (SCU_INIT_PNSSET0_VAL & BIT9 )
# define USBH USBH_NS
#else
# define USBH USBH_S
#endif

#if defined (SCU_INIT_PNSSET0_VAL) && (SCU_INIT_PNSSET0_VAL & BIT13)
# define SDH0 SDH0_NS
#else
# define SDH0 SDH0_S
#endif

#if defined (SCU_INIT_PNSSET0_VAL) && (SCU_INIT_PNSSET0_VAL & BIT16)
# define EBI EBI_NS
#else
# define EBI EBI_S
#endif


#if defined (SCU_INIT_PNSSET0_VAL) && (SCU_INIT_PNSSET0_VAL & BIT24)
# define PDMA1 PDMA1_NS
#else
# define PDMA1 PDMA1_S
#endif

#if defined (SCU_INIT_PNSSET1_VAL) && (SCU_INIT_PNSSET1_VAL & BIT17)
# define CRC CRC_NS
#else
# define CRC CRC_S
#endif

#if defined (SCU_INIT_PNSSET1_VAL) && (SCU_INIT_PNSSET1_VAL & BIT18)
# define CRPT CRPT_NS
#else
# define CRPT CRPT_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT2 )
# define EWDT EWDT_NS
# define EWWDT EWWDT_NS
#else
# define EWDT EWDT_S
# define EWWDT EWWDT_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT3 )
# define EADC EADC_NS
#else
# define EADC EADC_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT3 )
# define EADC EADC_NS
#else
# define EADC EADC_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT3 )
# define EADC EADC_NS
#else
# define EADC EADC_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT3 )
# define EADC EADC_NS
#else
# define EADC EADC_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT5 )
# define ACMP01 ACMP01_NS
#else
# define ACMP01 ACMP01_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT7 )
# define DAC0 DAC0_NS
# define DAC1 DAC1_NS
#else
# define DAC0 DAC0_S
# define DAC1 DAC1_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT8 )
# define I2S0 I2S0_NS
#else
# define I2S0 I2S0_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT13)
# define OTG OTG_NS
#else
# define OTG OTG_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT17)
# define TIMER2 TIMER2_NS
# define TIMER3 TIMER3_NS
#else
# define TIMER2 TIMER2_S
# define TIMER3 TIMER3_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT18)
# define TIMER4 TIMER4_NS
# define TIMER5 TIMER5_NS
#else
# define TIMER4 TIMER4_S
# define TIMER5 TIMER5_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT24)
# define EPWM0 EPWM0_NS
#else
# define EPWM0 EPWM0_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT24)
# define EPWM0 EPWM0_NS
#else
# define EPWM0 EPWM0_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT24)
# define EPWM0 EPWM0_NS
#else
# define EPWM0 EPWM0_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT25)
# define EPWM1 EPWM1_NS
#else
# define EPWM1 EPWM1_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT25)
# define EPWM1 EPWM1_NS
#else
# define EPWM1 EPWM1_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT25)
# define EPWM1 EPWM1_NS
#else
# define EPWM1 EPWM1_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT26)
# define BPWM0 BPWM0_NS
#else
# define BPWM0 BPWM0_S
#endif

#if defined (SCU_INIT_PNSSET2_VAL) && (SCU_INIT_PNSSET2_VAL & BIT27)
# define BPWM1 BPWM1_NS
#else
# define BPWM1 BPWM1_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT0 )
# define QSPI0 QSPI0_NS
#else
# define QSPI0 QSPI0_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT1 )
# define SPI0 SPI0_NS
#else
# define SPI0 SPI0_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT2 )
# define SPI1 SPI1_NS
#else
# define SPI1 SPI1_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT3 )
# define SPI2 SPI2_NS
#else
# define SPI2 SPI2_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT4 )
# define SPI3 SPI3_NS
#else
# define SPI3 SPI3_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT16)
# define UART0 UART0_NS
#else
# define UART0 UART0_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT17)
# define UART1 UART1_NS
#else
# define UART1 UART1_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT18)
# define UART2 UART2_NS
#else
# define UART2 UART2_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT19)
# define UART3 UART3_NS
#else
# define UART3 UART3_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT20)
# define UART4 UART4_NS
#else
# define UART4 UART4_S
#endif

#if defined (SCU_INIT_PNSSET3_VAL) && (SCU_INIT_PNSSET3_VAL & BIT21)
# define UART5 UART5_NS
#else
# define UART5 UART5_S
#endif

#if defined (SCU_INIT_PNSSET4_VAL) && (SCU_INIT_PNSSET4_VAL & BIT0 )
# define I2C0 I2C0_NS
#else
# define I2C0 I2C0_S
#endif

#if defined (SCU_INIT_PNSSET4_VAL) && (SCU_INIT_PNSSET4_VAL & BIT1 )
# define I2C1 I2C1_NS
#else
# define I2C1 I2C1_S
#endif

#if defined (SCU_INIT_PNSSET4_VAL) && (SCU_INIT_PNSSET4_VAL & BIT2 )
# define I2C2 I2C2_NS
#else
# define I2C2 I2C2_S
#endif

#if defined (SCU_INIT_PNSSET4_VAL) && (SCU_INIT_PNSSET4_VAL & BIT16)
# define SC0 SC0_NS
#else
# define SC0 SC0_S
#endif

#if defined (SCU_INIT_PNSSET4_VAL) && (SCU_INIT_PNSSET4_VAL & BIT17)
# define SC1 SC1_NS
#else
# define SC1 SC1_S
#endif

#if defined (SCU_INIT_PNSSET4_VAL) && (SCU_INIT_PNSSET4_VAL & BIT18)
# define SC2 SC2_NS
#else
# define SC2 SC2_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT0 )
# define CAN0 CAN0_NS
#else
# define CAN0 CAN0_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT16)
# define QEI0 QEI0_NS
#else
# define QEI0 QEI0_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT17)
# define QEI1 QEI1_NS
#else
# define QEI1 QEI1_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT20)
# define ECAP0 ECAP0_NS
#else
# define ECAP0 ECAP0_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT21)
# define ECAP1 ECAP1_NS
#else
# define ECAP1 ECAP1_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT25)
# define TRNG TRNG_NS
#else
# define TRNG TRNG_S
#endif

#if defined (SCU_INIT_PNSSET5_VAL) && (SCU_INIT_PNSSET5_VAL & BIT27)
# define LCD LCD_NS
#else
# define LCD LCD_S
#endif

#if defined (SCU_INIT_PNSSET6_VAL) && (SCU_INIT_PNSSET6_VAL & BIT0 )
# define USBD USBD_NS
#else
# define USBD USBD_S
#endif

#if defined (SCU_INIT_PNSSET6_VAL) && (SCU_INIT_PNSSET6_VAL & BIT16)
# define USCI0 USCI0_NS
# define UI2C0 UI2C0_NS
# define USPI0 USPI0_NS
# define UUART0 UUART0_NS

#else
# define USCI0 USCI0_S
# define UI2C0 UI2C0_S
# define USPI0 USPI0_S
# define UUART0 UUART0_S

#endif

#if defined (SCU_INIT_PNSSET6_VAL) && (SCU_INIT_PNSSET6_VAL & BIT17)
# define USCI1 USCI1_NS
# define USPI1 USPI1_NS
# define UI2C1 UI2C1_NS
# define UUART1 UUART1_NS

#else
# define USCI1 USCI1_S
# define USPI1 USPI1_S
# define UI2C1 UI2C1_S
# define UUART1 UUART1_S
#endif

#define PA  ( (__PC() & NS_OFFSET) ? PA_NS : PA_S)
#define PB  ( (__PC() & NS_OFFSET) ? PB_NS : PB_S)
#define PC  ( (__PC() & NS_OFFSET) ? PC_NS : PC_S)
#define PD  ( (__PC() & NS_OFFSET) ? PD_NS : PD_S)
#define PE  ( (__PC() & NS_OFFSET) ? PE_NS : PE_S)
#define PF  ( (__PC() & NS_OFFSET) ? PF_NS : PF_S)
#define PG  ( (__PC() & NS_OFFSET) ? PG_NS : PG_S)
#define PH  ( (__PC() & NS_OFFSET) ? PH_NS : PH_S)

/**@}*/ /* end of group PMODULE_SNS */

/**@}*/ /* end of group PMODULE */

/* --------------------  End of section using anonymous unions  ------------------- */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
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

#ifdef __cplusplus
}
#endif



/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "nu_sys.h"
#include "nu_clk.h"
#include "nu_dac.h"
#include "nu_eadc.h"
#include "nu_ebi.h"
#include "nu_ecap.h"
#include "nu_fmc.h"
#include "nu_gpio.h"
#include "nu_i2c.h"
#include "nu_i2s.h"
#include "nu_bpwm.h"
#include "nu_epwm.h"
#include "nu_qspi.h"
#include "nu_spi.h"
#include "nu_timer.h"
#include "nu_timer_pwm.h"
#include "nu_wdt.h"
#include "nu_wwdt.h"
#include "nu_rtc.h"
#include "nu_uart.h"
#include "nu_acmp.h"
#include "nu_crc.h"
#include "nu_usbd.h"
#include "nu_otg.h"
#include "nu_pdma.h"
#include "nu_ebi.h"
#include "nu_keystore.h"
#include "nu_crypto.h"
#include "nu_sc.h"
#include "nu_scuart.h"
#include "nu_usci_spi.h"
#include "nu_usci_uart.h"
#include "nu_usci_i2c.h"
#include "nu_sdh.h"
#include "nu_qei.h"
#include "nu_can.h"
#include "nu_scu.h"
#include "nu_tamper.h"
#include "nu_rng.h"
#include "nu_trng.h"
#include "nu_dpm.h"
#include "nu_fvc.h"
#include "nu_ewwdt.h"
#include "nu_ewdt.h"
#include "nu_plm.h"
#include "nu_lcd.h"

#endif  /* __M2354_H__ */

