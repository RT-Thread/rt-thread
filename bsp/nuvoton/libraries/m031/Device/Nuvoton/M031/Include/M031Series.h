/**************************************************************************//**
 * @file     m031series.h
 * @version  V3.0
 * $Revision: 12 $
 * $Date: 18/08/16 4:06p $
 * @brief    M031 Series Peripheral Access Layer Header File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

/**
  \mainpage NuMicro M031 Driver Reference Guide
  *
  * <b>Introduction</b>
  *
  * This user manual describes the usage of M031 Series MCU device driver
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
  * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
  */

#ifndef __M031SERIES_H__
#define __M031SERIES_H__

/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup CMSIS_Device CMSIS Definitions
  Configuration of the Cortex-M0 Processor and Core Peripherals
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
    HardFault_IRQn            = -13,      /*!< 3 Cortex-M0 Hard Fault Interrupt                     */
    SVCall_IRQn               = -5,       /*!< 11 Cortex-M0 SV Call Interrupt                       */
    PendSV_IRQn               = -2,       /*!< 14 Cortex-M0 Pend SV Interrupt                       */
    SysTick_IRQn              = -1,       /*!< 15 Cortex-M0 System Tick Interrupt                   */

    /******  ARMIKMCU Swift specific Interrupt Numbers ************************************************/
    BOD_IRQn                  = 0,        /*!< Brown-Out Low Voltage Detected Interrupt             */
    WDT_IRQn                  = 1,        /*!< Watch Dog Timer Interrupt                            */
    EINT024_IRQn              = 2,        /*!< EINT0, EINT2 and EINT4 Interrupt                     */
    EINT135_IRQn              = 3,        /*!< EINT1, EINT3 and EINT5 Interrupt                     */
    GPIO_PAPB_IRQn            = 4,        /*!< GPIO_PAPBPGPH Interrupt                              */
    GPIO_PAPBPGPH_IRQn        = 4,        /*!< GPIO_PAPBPGPH Interrupt                              */
    GPIO_PCPDPEPF_IRQn        = 5,        /*!< GPIO_PCPDPEPF Interrupt                              */
    PWM0_IRQn                 = 6,        /*!< PWM0 Interrupt                                       */
    PWM1_IRQn                 = 7,        /*!< PWM1 Interrupt                                       */
    TMR0_IRQn                 = 8,        /*!< TIMER0 Interrupt                                     */
    TMR1_IRQn                 = 9,        /*!< TIMER1 Interrupt                                     */
    TMR2_IRQn                 = 10,       /*!< TIMER2 Interrupt                                     */
    TMR3_IRQn                 = 11,       /*!< TIMER3 Interrupt                                     */
    UART02_IRQn               = 12,       /*!< UART0 and UART2 Interrupt                            */
    UART1_IRQn                = 13,       /*!< UART1 and UART3 Interrupt                            */
    UART13_IRQn               = 13,       /*!< UART1 and UART3 Interrupt                            */
    SPI0_IRQn                 = 14,       /*!< SPI0 Interrupt                                       */
    QSPI0_IRQn                = 15,       /*!< QSPI0 Interrupt                                      */
    ISP_IRQn                  = 16,       /*!< ISP Interrupt                                        */
    UART57_IRQn               = 17,       /*!< UART5 and UART7 Interrupt                            */
    I2C0_IRQn                 = 18,       /*!< I2C0 Interrupt                                       */
    I2C1_IRQn                 = 19,       /*!< I2C1 Interrupt                                       */
    BPWM0_IRQn                = 20,       /*!< BPWM0 Interrupt                                      */
    BPWM1_IRQn                = 21,       /*!< BPWM1 Interrupt                                      */
    USCI_IRQn                 = 22,       /*!< USCI0 and USCI1 interrupt                            */
    USCI01_IRQn               = 22,       /*!< USCI0 and USCI1 interrupt                            */
    USBD_IRQn                 = 23,       /*!< USB Device Interrupt                                 */
    ACMP01_IRQn               = 25,       /*!< ACMP0/1 Interrupt                                    */
    PDMA_IRQn                 = 26,       /*!< PDMA Interrupt                                       */
    UART46_IRQn               = 27,       /*!< UART4 and UART6 Interrupt                            */
    PWRWU_IRQn                = 28,       /*!< Power Down Wake Up Interrupt                         */
    ADC_IRQn                  = 29,       /*!< ADC Interrupt                                        */
    CKFAIL_IRQn               = 30,       /*!< Clock fail detect Interrupt                          */
    RTC_IRQn                  = 31,       /*!< RTC Interrupt                                        */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT           0       /*!< armikcmu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        2       /*!< armikcmu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */

/*@}*/ /* end of group CMSIS_Device */

#include "core_cm0.h"                   /*!< Cortex-M0 processor and core peripherals             */
#include "system_M031Series.h"          /*!< M031 System                                    */


#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/**
 * Initialize the system clock
 *
 * @param  None
 * @return None
 *
 * @brief  Setup the microcontroller system
 *         Initialize the PLL and update the SystemFrequency variable
 */
extern void SystemInit(void);



/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

#include "acmp_reg.h"
#include "adc_reg.h"
#include "clk_reg.h"
#include "crc_reg.h"
#include "ebi_reg.h"
#include "fmc_reg.h"
#include "gpio_reg.h"
#include "hdiv_reg.h"
#include "i2c_reg.h"
#include "pdma_reg.h"
#include "pwm_reg.h"
#include "bpwm_reg.h"
#include "qspi_reg.h"
#include "spi_reg.h"
#include "sys_reg.h"
#include "rtc_reg.h"
#include "timer_reg.h"
#include "uart_reg.h"
#include "ui2c_reg.h"
#include "usbd_reg.h"
#include "uspi_reg.h"
#include "uuart_reg.h"
#include "wdt_reg.h"
#include "wwdt_reg.h"


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup PERIPHERAL_BASE Peripheral Memory Base
  Memory Mapped Structure for Series Peripheral
  @{
 */
/* Peripheral and SRAM base address */
#define FLASH_BASE          ((     uint32_t)0x00000000)
#define SRAM_BASE           ((     uint32_t)0x20000000)
#define AHB_BASE            ((     uint32_t)0x40000000)
#define APB1_BASE           ((     uint32_t)0x40000000)
#define APB2_BASE           ((     uint32_t)0x40000000)

/* Peripheral memory map */

#define SYS_BASE            (AHB_BASE       + 0x00000)                  /*!< System Global Controller Base Address            */
#define CLK_BASE            (AHB_BASE       + 0x00200)                  /*!< System Clock Controller Base Address             */
#define INT_BASE            (AHB_BASE       + 0x00300)                  /*!< Interrupt Source Controller Base Address         */
#define NMI_BASE            (AHB_BASE       + 0x00300)                  /*!< Interrupt Source Controller Base Address         */

#define GPIO_BASE           (AHB_BASE       + 0x4000)                   /*!< GPIO Base Address                                */
#define PA_BASE             (GPIO_BASE              )                   /*!< GPIO PA Base Address                             */
#define PB_BASE             (GPIO_BASE      + 0x0040)                   /*!< GPIO PB Base Address                             */
#define PC_BASE             (GPIO_BASE      + 0x0080)                   /*!< GPIO PC Base Address                             */
#define PD_BASE             (GPIO_BASE      + 0x00C0)                   /*!< GPIO PD Base Address                             */
#define PE_BASE             (GPIO_BASE      + 0x0100)                   /*!< GPIO PE Base Address                             */
#define PF_BASE             (GPIO_BASE      + 0x0140)                   /*!< GPIO PF Base Address                             */
#define PG_BASE             (GPIO_BASE      + 0x0180)                   /*!< GPIO PG Base Address                             */
#define PH_BASE             (GPIO_BASE      + 0x01C0)                   /*!< GPIO PH Base Address                             */
#define GPIO_DBCTL_BASE     (GPIO_BASE      + 0x0440)                   /*!< GPIO De-bounce Cycle Control Base Address        */
#define GPIO_PIN_DATA_BASE  (GPIO_BASE      + 0x0800)                   /*!< GPIO Pin Data Input/Output Control Base Address  */

#define PDMA_BASE           (AHB_BASE       + 0x08000)                  /*!< PDMA Base Address                                */
#define FMC_BASE            (AHB_BASE       + 0x0C000)                  /*!< Flash Memory Controller Base Address             */
#define EBI_BASE            (AHB_BASE       + 0x10000)                  /*!< EBI Base Address                                 */
#define HDIV_BASE           (AHB_BASE       + 0x14000)                  /*!< HDIV Base Address                                */
#define CRC_BASE            (AHB_BASE       + 0x31000)                  /*!< CRC Base Address                                 */

#define WDT_BASE            (APB1_BASE      + 0x40000)                  /*!< Watch Dog Timer Base Address                     */
#define WWDT_BASE           (APB1_BASE      + 0x40100)                  /*!< Window Watch Dog Timer Base Address              */
#define RTC_BASE            (APB1_BASE      + 0x41000)                  /*!< RTC Base Address                                 */
#define ADC_BASE            (APB1_BASE      + 0x43000)                  /*!< ADC Base Address                                 */
#define ACMP01_BASE         (APB1_BASE      + 0x45000)                  /*!< ACMP01 Base Address                              */

#define TIMER0_BASE         (APB1_BASE      + 0x50000)                  /*!< Timer0 Base Address                              */
#define TIMER1_BASE         (APB1_BASE      + 0x50020)                  /*!< Timer1 Base Address                              */
#define TIMER2_BASE         (APB2_BASE      + 0x51000)                  /*!< Timer2 Base Address                              */
#define TIMER3_BASE         (APB2_BASE      + 0x51020)                  /*!< Timer3 Base Address                              */

#define PWM0_BASE           (APB1_BASE      + 0x58000)                  /*!< PWM0 Base Address                                */
#define PWM1_BASE           (APB2_BASE      + 0x59000)                  /*!< PWM1 Base Address                                */

#define BPWM0_BASE          (APB1_BASE      + 0x5A000)                  /*!< BPWM0 Base Address                               */
#define BPWM1_BASE          (APB2_BASE      + 0x5B000)                  /*!< BPWM1 Base Address                               */

#define QSPI0_BASE          (APB1_BASE      + 0x60000)                  /*!< QSPI0 Base Address                               */
#define SPI0_BASE           (APB1_BASE      + 0x61000)                  /*!< SPI0 Base Address                                */

#define UART0_BASE          (APB1_BASE      + 0x70000)                  /*!< UART0 Base Address                               */
#define UART1_BASE          (APB2_BASE      + 0x71000)                  /*!< UART1 Base Address                               */
#define UART2_BASE          (APB2_BASE      + 0x72000)                  /*!< UART2 Base Address                               */
#define UART3_BASE          (APB2_BASE      + 0x73000)                  /*!< UART3 Base Address                               */
#define UART4_BASE          (APB2_BASE      + 0x74000)                  /*!< UART4 Base Address                               */
#define UART5_BASE          (APB2_BASE      + 0x75000)                  /*!< UART5 Base Address                               */
#define UART6_BASE          (APB2_BASE      + 0x76000)                  /*!< UART6 Base Address                               */
#define UART7_BASE          (APB2_BASE      + 0x77000)                  /*!< UART7 Base Address                               */

#define I2C0_BASE           (APB1_BASE      + 0x80000)                  /*!< I2C0 Base Address                                */
#define I2C1_BASE           (APB2_BASE      + 0x81000)                  /*!< I2C1 Base Address                                */

#define USBD_BASE           (AHB_BASE       + 0xC0000)                  /*!< USBD1.1 Base Address                             */
#define USCI0_BASE          (APB1_BASE      + 0xD0000)                  /*!< USCI0 Base Address                               */
#define USCI1_BASE          (APB2_BASE      + 0xD1000)                  /*!< USCI1 Base Address                               */


/**@}*/ /* PERIPHERAL */

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

/** @addtogroup PMODULE Peripheral Pointer
  The Declaration of Peripheral Pointer
  @{
 */
#define PA                  ((GPIO_T *) PA_BASE)                        /*!< GPIO PORTA Configuration Struct                        */
#define PB                  ((GPIO_T *) PB_BASE)                        /*!< GPIO PORTB Configuration Struct                        */
#define PC                  ((GPIO_T *) PC_BASE)                        /*!< GPIO PORTC Configuration Struct                        */
#define PD                  ((GPIO_T *) PD_BASE)                        /*!< GPIO PORTD Configuration Struct                        */
#define PE                  ((GPIO_T *) PE_BASE)                        /*!< GPIO PORTE Configuration Struct                        */
#define PF                  ((GPIO_T *) PF_BASE)                        /*!< GPIO PORTF Configuration Struct                        */
#define PG                  ((GPIO_T *) PG_BASE)                        /*!< GPIO PORTG Configuration Struct                        */
#define PH                  ((GPIO_T *) PH_BASE)                        /*!< GPIO PORTH Configuration Struct                        */
#define GPIO                ((GPIO_DBCTL_T *) GPIO_DBCTL_BASE)          /*!< Interrupt De-bounce Cycle Control Configuration Struct */

#define UART0               ((UART_T *) UART0_BASE)                     /*!< UART0 Configuration Struct                       */
#define UART1               ((UART_T *) UART1_BASE)                     /*!< UART1 Configuration Struct                       */
#define UART2               ((UART_T *) UART2_BASE)                     /*!< UART2 Configuration Struct                       */
#define UART3               ((UART_T *) UART3_BASE)                     /*!< UART3 Configuration Struct                       */
#define UART4               ((UART_T *) UART4_BASE)                     /*!< UART4 Configuration Struct                       */
#define UART5               ((UART_T *) UART5_BASE)                     /*!< UART5 Configuration Struct                       */
#define UART6               ((UART_T *) UART6_BASE)                     /*!< UART6 Configuration Struct                       */
#define UART7               ((UART_T *) UART7_BASE)                     /*!< UART7 Configuration Struct                       */

#define TIMER0              ((TIMER_T *) TIMER0_BASE)                   /*!< TIMER0 Configuration Struct                      */
#define TIMER1              ((TIMER_T *) TIMER1_BASE)                   /*!< TIMER1 Configuration Struct                      */
#define TIMER2              ((TIMER_T *) TIMER2_BASE)                   /*!< TIMER2 Configuration Struct                      */
#define TIMER3              ((TIMER_T *) TIMER3_BASE)                   /*!< TIMER3 Configuration Struct                      */

#define WDT                 ((WDT_T *) WDT_BASE)                        /*!< Watch Dog Timer Configuration Struct             */

#define WWDT                ((WWDT_T *) WWDT_BASE)                      /*!< Window Watch Dog Timer Configuration Struct      */

#define SPI0                ((SPI_T *) SPI0_BASE)                       /*!< SPI0 Configuration Struct                        */
#define QSPI0               ((QSPI_T *) QSPI0_BASE)                     /*!< QSPI0 Configuration Struct                       */

#define I2C0                ((I2C_T *) I2C0_BASE)                       /*!< I2C0 Configuration Struct                        */
#define I2C1                ((I2C_T *) I2C1_BASE)                       /*!< I2C1 Configuration Struct                        */

#define ADC                 ((ADC_T *) ADC_BASE)                        /*!< ADC Configuration Struct                         */

#define ACMP01              ((ACMP_T *) ACMP01_BASE)                    /*!< ACMP01 Configuration Struct                      */

#define CLK                 ((CLK_T *) CLK_BASE)                        /*!< System Clock Controller Configuration Struct     */

#define SYS                 ((SYS_T *) SYS_BASE)                        /*!< System Global Controller Configuration Struct    */

#define SYSINT              ((NMI_T *) INT_BASE)                        /*!< Interrupt Source Controller Configuration Struct */
#define NMI                 ((NMI_T *) NMI_BASE)                        /*!< Interrupt Source Controller Configuration Struct */

#define FMC                 ((FMC_T *) FMC_BASE)                        /*!< Flash Memory Controller                          */

#define PWM0                ((PWM_T *) PWM0_BASE)                       /*!< PWM0 Configuration Struct                        */
#define PWM1                ((PWM_T *) PWM1_BASE)                       /*!< PWM1 Configuration Struct                        */
#define BPWM0               ((BPWM_T *) BPWM0_BASE)                     /*!< BPWM0 Configuration Struct                       */
#define BPWM1               ((BPWM_T *) BPWM1_BASE)                     /*!< BPWM1 Configuration Struct                       */

#define EBI                 ((EBI_T *) EBI_BASE)                        /*!< EBI Configuration Struct                         */

#define HDIV                ((HDIV_T *) HDIV_BASE)                      /*!< HDIV Configuration Struct                        */

#define CRC                 ((CRC_T *) CRC_BASE)                        /*!< CRC Configuration Struct                         */

#define USBD                ((USBD_T *) USBD_BASE)                      /*!< CRC Configuration Struct                         */

#define PDMA                ((PDMA_T *) PDMA_BASE)                      /*!< PDMA Configuration Struct                        */

#define UI2C0               ((UI2C_T *) USCI0_BASE)                     /*!< UI2C0 Configuration Struct                       */
#define UI2C1               ((UI2C_T *) USCI1_BASE)                     /*!< UI2C1 Configuration Struct                       */

#define USPI0               ((USPI_T *) USCI0_BASE)                     /*!< USPI0 Configuration Struct                       */
#define USPI1               ((USPI_T *) USCI1_BASE)                     /*!< USPI1 Configuration Struct                       */

#define UUART0              ((UUART_T *) USCI0_BASE)                    /*!< UUART0 Configuration Struct                      */
#define UUART1              ((UUART_T *) USCI1_BASE)                    /*!< UUART1 Configuration Struct                      */

#define RTC                 ((RTC_T *)   RTC_BASE)                      /*!< RTC Configuration Struct                         */

/**@}*/ /* end of group PMODULE */


//=============================================================================

/** @addtogroup IO_ROUTINE I/O Routines
  The Declaration of I/O Routines
  @{
 */

typedef volatile unsigned char  vu8;
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;

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
#define outpw(port,value)   (*((volatile unsigned int *)(port))=(value))

/**
  * @brief Get a 32-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified I/O port
  * @note The input port must be 32-bit aligned
  */
#define inpw(port)          ((*((volatile unsigned int *)(port))))

/**
  * @brief Set a 16-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 16-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 16-bit aligned
  */
#define outps(port,value)   (*((volatile unsigned short *)(port))=(value))

/**
  * @brief Get a 16-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified I/O port
  * @note The input port must be 16-bit aligned
  */
#define inps(port)          ((*((volatile unsigned short *)(port))))

/**
  * @brief Set a 8-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 8-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  */
#define outpb(port,value)   (*((volatile unsigned char *)(port))=(value))

/**
  * @brief Get a 8-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified I/O port
  */
#define inpb(port)          ((*((volatile unsigned char *)(port))))

/**
  * @brief Set a 32-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 32-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 32-bit aligned
  */
#define outp32(port,value)  (*((volatile unsigned int *)(port))=(value))

/**
  * @brief Get a 32-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified I/O port
  * @note The input port must be 32-bit aligned
  */
#define inp32(port)         ((*((volatile unsigned int *)(port))))

/**
  * @brief Set a 16-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 16-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 16-bit aligned
  */
#define outp16(port,value)  (*((volatile unsigned short *)(port))=(value))

/**
  * @brief Get a 16-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified I/O port
  * @note The input port must be 16-bit aligned
  */
#define inp16(port)         ((*((volatile unsigned short *)(port))))

/**
  * @brief Set a 8-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 8-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  */
#define outp8(port,value)   (*((volatile unsigned char *)(port))=(value))

/**
  * @brief Get a 8-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified I/O port
  */
#define inp8(port)          ((*((volatile unsigned char *)(port))))

/*@}*/ /* end of group IO_ROUTINE */

/******************************************************************************/
/*                Legacy Constants                                            */
/******************************************************************************/

/** @addtogroup Legacy_Constants Legacy Constants
  Legacy Constants
  @{
*/

#define E_SUCCESS (0)

#ifndef NULL
    #define NULL      (0)                 ///< NULL pointer
#endif

#define TRUE      (1UL)               ///< Boolean true, define to use in API parameters or return value
#define FALSE     (0UL)               ///< Boolean false, define to use in API parameters or return value

#define ENABLE    (1UL)               ///< Enable, define to use in API parameters
#define DISABLE   (0UL)               ///< Disable, define to use in API parameters

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
#define BYTE0_Msk              (0x000000FFUL)                   ///< Mask to get bit0~bit7 from a 32 bit integer
#define BYTE1_Msk              (0x0000FF00UL)                   ///< Mask to get bit8~bit15 from a 32 bit integer
#define BYTE2_Msk              (0x00FF0000UL)                   ///< Mask to get bit16~bit23 from a 32 bit integer
#define BYTE3_Msk              (0xFF000000UL)                   ///< Mask to get bit24~bit31 from a 32 bit integer

#define GET_BYTE0(u32Param)    (((u32Param) & BYTE0_Msk)      ) /*!< Extract Byte 0 (Bit  0~ 7) from parameter u32Param */
#define GET_BYTE1(u32Param)    (((u32Param) & BYTE1_Msk) >>  8) /*!< Extract Byte 1 (Bit  8~15) from parameter u32Param */
#define GET_BYTE2(u32Param)    (((u32Param) & BYTE2_Msk) >> 16) /*!< Extract Byte 2 (Bit 16~23) from parameter u32Param */
#define GET_BYTE3(u32Param)    (((u32Param) & BYTE3_Msk) >> 24) /*!< Extract Byte 3 (Bit 24~31) from parameter u32Param */

/* Chip Series number definitions */
#define GET_CHIP_SERIES_NUM    ((SYS->PDID & 0xF00) >> 8)       /*!< Extract chip series number from PDID */
#define CHIP_SERIES_NUM_B      (0xBUL)                          /*!< Chip series number for M031_B */
#define CHIP_SERIES_NUM_C      (0xCUL)                          /*!< Chip series number for M031_C */
#define CHIP_SERIES_NUM_D      (0xDUL)                          /*!< Chip series number for M031_D */
#define CHIP_SERIES_NUM_E      (0xEUL)                          /*!< Chip series number for M031_E */
#define CHIP_SERIES_NUM_G      (0x6UL)                          /*!< Chip series number for M031_G */
#define CHIP_SERIES_NUM_I      (0x1UL)                          /*!< Chip series number for M031_I */

/*@}*/ /* end of group Legacy_Constants */

/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "nu_sys.h"
#include "nu_clk.h"
#include "nu_acmp.h"
#include "nu_adc.h"
#include "nu_crc.h"
#include "nu_ebi.h"
#include "nu_fmc.h"
#include "nu_gpio.h"
#include "nu_i2c.h"
#include "nu_pdma.h"
#include "nu_pwm.h"
#include "nu_bpwm.h"
#include "nu_qspi.h"
#include "nu_spi.h"
#include "nu_rtc.h"
#include "nu_hdiv.h"
#include "nu_timer.h"
#include "nu_uart.h"
#include "nu_usbd.h"
#include "nu_usci_i2c.h"
#include "nu_usci_spi.h"
#include "nu_usci_uart.h"
#include "nu_wdt.h"
#include "nu_wwdt.h"

#endif  // __M031SERIES_H__

/* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved. */
