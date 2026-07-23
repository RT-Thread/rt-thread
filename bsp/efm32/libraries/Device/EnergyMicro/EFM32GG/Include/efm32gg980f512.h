/**************************************************************************//**
 * @file
 * @brief CMSIS Cortex-M3 Peripheral Access Layer Header File
 *        for EFM EFM32GG980F512
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/

#ifndef __EFM32GG980F512_H
#define __EFM32GG980F512_H

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************//**
 * @addtogroup Parts
 * @{
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup EFM32GG980F512 EFM32GG980F512
 * @{
 *****************************************************************************/

/** Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers *******************************************/
  NonMaskableInt_IRQn   = -14,              /*!< 2 Non Maskable Interrupt                 */
  HardFault_IRQn        = -13,              /*!< 3 Cortex-M3 Hard Fault Interrupt         */
  MemoryManagement_IRQn = -12,              /*!< 4 Cortex-M3 Memory Management Interrupt  */
  BusFault_IRQn         = -11,              /*!< 5 Cortex-M3 Bus Fault Interrupt          */
  UsageFault_IRQn       = -10,              /*!< 6 Cortex-M3 Usage Fault Interrupt        */
  SVCall_IRQn           = -5,               /*!< 11 Cortex-M3 SV Call Interrupt           */
  DebugMonitor_IRQn     = -4,               /*!< 12 Cortex-M3 Debug Monitor Interrupt     */
  PendSV_IRQn           = -2,               /*!< 14 Cortex-M3 Pend SV Interrupt           */
  SysTick_IRQn          = -1,               /*!< 15 Cortex-M3 System Tick Interrupt       */

/******  EFM32G Peripheral Interrupt Numbers **********************************************/
  DMA_IRQn              = 0,  /*!< 16+0 EFM32 DMA Interrupt */
  GPIO_EVEN_IRQn        = 1,  /*!< 16+1 EFM32 GPIO_EVEN Interrupt */
  TIMER0_IRQn           = 2,  /*!< 16+2 EFM32 TIMER0 Interrupt */
  USART0_RX_IRQn        = 3,  /*!< 16+3 EFM32 USART0_RX Interrupt */
  USART0_TX_IRQn        = 4,  /*!< 16+4 EFM32 USART0_TX Interrupt */
  USB_IRQn              = 5,  /*!< 16+5 EFM32 USB Interrupt */
  ACMP0_IRQn            = 6,  /*!< 16+6 EFM32 ACMP0 Interrupt */
  ADC0_IRQn             = 7,  /*!< 16+7 EFM32 ADC0 Interrupt */
  DAC0_IRQn             = 8,  /*!< 16+8 EFM32 DAC0 Interrupt */
  I2C0_IRQn             = 9,  /*!< 16+9 EFM32 I2C0 Interrupt */
  I2C1_IRQn             = 10, /*!< 16+10 EFM32 I2C1 Interrupt */
  GPIO_ODD_IRQn         = 11, /*!< 16+11 EFM32 GPIO_ODD Interrupt */
  TIMER1_IRQn           = 12, /*!< 16+12 EFM32 TIMER1 Interrupt */
  TIMER2_IRQn           = 13, /*!< 16+13 EFM32 TIMER2 Interrupt */
  TIMER3_IRQn           = 14, /*!< 16+14 EFM32 TIMER3 Interrupt */
  USART1_RX_IRQn        = 15, /*!< 16+15 EFM32 USART1_RX Interrupt */
  USART1_TX_IRQn        = 16, /*!< 16+16 EFM32 USART1_TX Interrupt */
  LESENSE_IRQn          = 17, /*!< 16+17 EFM32 LESENSE Interrupt */
  USART2_RX_IRQn        = 18, /*!< 16+18 EFM32 USART2_RX Interrupt */
  USART2_TX_IRQn        = 19, /*!< 16+19 EFM32 USART2_TX Interrupt */
  UART0_RX_IRQn         = 20, /*!< 16+20 EFM32 UART0_RX Interrupt */
  UART0_TX_IRQn         = 21, /*!< 16+21 EFM32 UART0_TX Interrupt */
  UART1_RX_IRQn         = 22, /*!< 16+22 EFM32 UART1_RX Interrupt */
  UART1_TX_IRQn         = 23, /*!< 16+23 EFM32 UART1_TX Interrupt */
  LEUART0_IRQn          = 24, /*!< 16+24 EFM32 LEUART0 Interrupt */
  LEUART1_IRQn          = 25, /*!< 16+25 EFM32 LEUART1 Interrupt */
  LETIMER0_IRQn         = 26, /*!< 16+26 EFM32 LETIMER0 Interrupt */
  PCNT0_IRQn            = 27, /*!< 16+27 EFM32 PCNT0 Interrupt */
  PCNT1_IRQn            = 28, /*!< 16+28 EFM32 PCNT1 Interrupt */
  PCNT2_IRQn            = 29, /*!< 16+29 EFM32 PCNT2 Interrupt */
  RTC_IRQn              = 30, /*!< 16+30 EFM32 RTC Interrupt */
  BURTC_IRQn            = 31, /*!< 16+31 EFM32 BURTC Interrupt */
  CMU_IRQn              = 32, /*!< 16+32 EFM32 CMU Interrupt */
  VCMP_IRQn             = 33, /*!< 16+33 EFM32 VCMP Interrupt */
  LCD_IRQn              = 34, /*!< 16+34 EFM32 LCD Interrupt */
  MSC_IRQn              = 35, /*!< 16+35 EFM32 MSC Interrupt */
  AES_IRQn              = 36, /*!< 16+36 EFM32 AES Interrupt */
  EBI_IRQn              = 37, /*!< 16+37 EFM32 EBI Interrupt */
  EMU_IRQn              = 38, /*!< 16+38 EFM32 EMU Interrupt */
} IRQn_Type;

/**************************************************************************//**
 * @defgroup EFM32GG980F512_Core EFM32GG980F512 Core
 * @{
 * @brief Processor and Core Peripheral Section
 *****************************************************************************/
#define __MPU_PRESENT             1 /**< Presence of MPU  */
#define __NVIC_PRIO_BITS          3 /**< NVIC interrupt priority bits */
#define __Vendor_SysTickConfig    0 /**< Is 1 if different SysTick counter is used */

/** @} End of group EFM32GG980F512_Core */

/**************************************************************************//**
* @defgroup EFM32GG980F512_Part EFM32GG980F512 Part
* @{
******************************************************************************/

/** Part family */
#define _EFM32_GIANT_FAMILY    1 /**< Giant/Leopard Gecko EFM32LG/GG MCU Family */

/* If part number is not defined as compiler option, define it */
#if !defined(EFM32GG980F512)
#define EFM32GG980F512    1 /**< Giant/Leopard Gecko Part  */
#endif

/** Configure part number */
#define PART_NUMBER          "EFM32GG980F512" /**< Part Number */

/** Memory Base addresses and limits */
#define EBI_MEM_BASE         ((uint32_t) 0x80000000UL)  /**< EBI base address  */
#define EBI_MEM_SIZE         ((uint32_t) 0x40000000UL)  /**< EBI available address space  */
#define EBI_MEM_END          ((uint32_t) 0xBFFFFFFFUL)  /**< EBI end address  */
#define EBI_MEM_BITS         ((uint32_t) 0x30UL)        /**< EBI used bits  */
#define USBC_MEM_BASE        ((uint32_t) 0x40100000UL)  /**< USBC base address  */
#define USBC_MEM_SIZE        ((uint32_t) 0x40000UL)     /**< USBC available address space  */
#define USBC_MEM_END         ((uint32_t) 0x4013FFFFUL)  /**< USBC end address  */
#define USBC_MEM_BITS        ((uint32_t) 0x18UL)        /**< USBC used bits  */
#define AES_MEM_BASE         ((uint32_t) 0x400E0000UL)  /**< AES base address  */
#define AES_MEM_SIZE         ((uint32_t) 0x400UL)       /**< AES available address space  */
#define AES_MEM_END          ((uint32_t) 0x400E03FFUL)  /**< AES end address  */
#define AES_MEM_BITS         ((uint32_t) 0x10UL)        /**< AES used bits  */
#define PER_MEM_BASE         ((uint32_t) 0x40000000UL)  /**< PER base address  */
#define PER_MEM_SIZE         ((uint32_t) 0xE0000UL)     /**< PER available address space  */
#define PER_MEM_END          ((uint32_t) 0x400DFFFFUL)  /**< PER end address  */
#define PER_MEM_BITS         ((uint32_t) 0x20UL)        /**< PER used bits  */
#define RAM_MEM_BASE         ((uint32_t) 0x20000000UL)  /**< RAM base address  */
#define RAM_MEM_SIZE         ((uint32_t) 0x40000UL)     /**< RAM available address space  */
#define RAM_MEM_END          ((uint32_t) 0x2003FFFFUL)  /**< RAM end address  */
#define RAM_MEM_BITS         ((uint32_t) 0x18UL)        /**< RAM used bits  */
#define EBI_CODE_MEM_BASE    ((uint32_t) 0x12000000UL)  /**< EBI_CODE base address  */
#define EBI_CODE_MEM_SIZE    ((uint32_t) 0xE000000UL)   /**< EBI_CODE available address space  */
#define EBI_CODE_MEM_END     ((uint32_t) 0x1FFFFFFFUL)  /**< EBI_CODE end address  */
#define EBI_CODE_MEM_BITS    ((uint32_t) 0x28UL)        /**< EBI_CODE used bits  */
#define RAM_CODE_MEM_BASE    ((uint32_t) 0x10000000UL)  /**< RAM_CODE base address  */
#define RAM_CODE_MEM_SIZE    ((uint32_t) 0x20000UL)     /**< RAM_CODE available address space  */
#define RAM_CODE_MEM_END     ((uint32_t) 0x1001FFFFUL)  /**< RAM_CODE end address  */
#define RAM_CODE_MEM_BITS    ((uint32_t) 0x17UL)        /**< RAM_CODE used bits  */
#define FLASH_MEM_BASE       ((uint32_t) 0x0UL)         /**< FLASH base address  */
#define FLASH_MEM_SIZE       ((uint32_t) 0x10000000UL)  /**< FLASH available address space  */
#define FLASH_MEM_END        ((uint32_t) 0xFFFFFFFUL)   /**< FLASH end address  */
#define FLASH_MEM_BITS       ((uint32_t) 0x28UL)        /**< FLASH used bits  */

/** Bit banding area */
#define BITBAND_PER_BASE     ((uint32_t) 0x42000000UL) /**< Peripheral Address Space bit-band area */
#define BITBAND_RAM_BASE     ((uint32_t) 0x22000000UL) /**< SRAM Address Space bit-band area */

/** Flash and SRAM limits for EFM32GG980F512 */
#define FLASH_BASE           (0x00000000UL) /**< Flash Base Address */
#define FLASH_SIZE           (0x00080000UL) /**< Available Flash Memory */
#define SRAM_BASE            (0x20000000UL) /**< SRAM Base Address */
#define SRAM_SIZE            (0x00020000UL) /**< Available SRAM Memory */
#define __CM3_REV            0x201          /**< Cortex-M3 Core revision r2p1 */
#define PRS_CHAN_COUNT       12             /**< Number of PRS channels */
#define DMA_CHAN_COUNT       12             /**< Number of DMA channels */

/* Part number capabilities */

#define TIMER_PRESENT         /**< TIMER is available in this part */
#define TIMER_COUNT         4 /**< 4 TIMERs available  */
#define USART_PRESENT         /**< USART is available in this part */
#define USART_COUNT         3 /**< 3 USARTs available  */
#define UART_PRESENT          /**< UART is available in this part */
#define UART_COUNT          2 /**< 2 UARTs available  */
#define LEUART_PRESENT        /**< LEUART is available in this part */
#define LEUART_COUNT        2 /**< 2 LEUARTs available  */
#define LETIMER_PRESENT       /**< LETIMER is available in this part */
#define LETIMER_COUNT       1 /**< 1 LETIMERs available  */
#define PCNT_PRESENT          /**< PCNT is available in this part */
#define PCNT_COUNT          3 /**< 3 PCNTs available  */
#define I2C_PRESENT           /**< I2C is available in this part */
#define I2C_COUNT           2 /**< 2 I2Cs available  */
#define ADC_PRESENT           /**< ADC is available in this part */
#define ADC_COUNT           1 /**< 1 ADCs available  */
#define DAC_PRESENT           /**< DAC is available in this part */
#define DAC_COUNT           1 /**< 1 DACs available  */
#define ACMP_PRESENT          /**< ACMP is available in this part */
#define ACMP_COUNT          2 /**< 2 ACMPs available  */
#define LE_PRESENT
#define LE_COUNT            1
#define MSC_PRESENT
#define MSC_COUNT           1
#define EMU_PRESENT
#define EMU_COUNT           1
#define RMU_PRESENT
#define RMU_COUNT           1
#define CMU_PRESENT
#define CMU_COUNT           1
#define AES_PRESENT
#define AES_COUNT           1
#define LESENSE_PRESENT
#define LESENSE_COUNT       1
#define EBI_PRESENT
#define EBI_COUNT           1
#define GPIO_PRESENT
#define GPIO_COUNT          1
#define PRS_PRESENT
#define PRS_COUNT           1
#define DMA_PRESENT
#define DMA_COUNT           1
#define OPAMP_PRESENT
#define OPAMP_COUNT         1
#define USB_PRESENT
#define USB_COUNT           1
#define USBC_PRESENT
#define USBC_COUNT          1
#define BU_PRESENT
#define BU_COUNT            1
#define VCMP_PRESENT
#define VCMP_COUNT          1
#define LCD_PRESENT
#define LCD_COUNT           1
#define RTC_PRESENT
#define RTC_COUNT           1
#define BURTC_PRESENT
#define BURTC_COUNT         1
#define HFXTAL_PRESENT
#define HFXTAL_COUNT        1
#define LFXTAL_PRESENT
#define LFXTAL_COUNT        1
#define WDOG_PRESENT
#define WDOG_COUNT          1
#define DBG_PRESENT
#define DBG_COUNT           1
#define ETM_PRESENT
#define ETM_COUNT           1
#define BOOTLOADER_PRESENT
#define BOOTLOADER_COUNT    1

#include "core_cm3.h"       /* Cortex-M3 processor and core peripherals */
#include "system_efm32gg.h" /* System Header */

/** @} End of group EFM32GG980F512_Part */

/**************************************************************************//**
 * @defgroup EFM32GG980F512_Peripheral_TypeDefs EFM32GG980F512 Peripheral TypeDefs
 * @{
 * @brief Device Specific Peripheral Register Structures
 *****************************************************************************/

#include "efm32gg_msc.h"
#include "efm32gg_emu.h"
#include "efm32gg_rmu.h"
#include "efm32gg_cmu.h"
#include "efm32gg_aes.h"
#include "efm32gg_lesense_st.h"
#include "efm32gg_lesense_buf.h"
#include "efm32gg_lesense_ch.h"
#include "efm32gg_lesense.h"
#include "efm32gg_ebi.h"
#include "efm32gg_gpio_p.h"
#include "efm32gg_gpio.h"
#include "efm32gg_prs_ch.h"
#include "efm32gg_prs.h"
#include "efm32gg_dma_ch.h"
#include "efm32gg_dma.h"
#include "efm32gg_timer_cc.h"
#include "efm32gg_timer.h"
#include "efm32gg_usart.h"
#include "efm32gg_leuart.h"
#include "efm32gg_letimer.h"
#include "efm32gg_pcnt.h"
#include "efm32gg_i2c.h"
#include "efm32gg_adc.h"
#include "efm32gg_dac.h"
#include "efm32gg_acmp.h"
#include "efm32gg_usb_hc.h"
#include "efm32gg_usb_diep.h"
#include "efm32gg_usb_doep.h"
#include "efm32gg_usb.h"
#include "efm32gg_vcmp.h"
#include "efm32gg_lcd.h"
#include "efm32gg_rtc.h"
#include "efm32gg_burtc_ret.h"
#include "efm32gg_burtc.h"
#include "efm32gg_wdog.h"
#include "efm32gg_etm.h"
#include "efm32gg_dma_descriptor.h"
#include "efm32gg_devinfo.h"
#include "efm32gg_romtable.h"
#include "efm32gg_calibrate.h"

/** @} End of group EFM32GG980F512_Peripheral_TypeDefs */

/**************************************************************************//**
 * @defgroup EFM32GG980F512_Peripheral_Base EFM32GG980F512 Peripheral Memory Map
 * @{
 *****************************************************************************/

#define MSC_BASE          (0x400C0000UL) /**< MSC base address  */
#define EMU_BASE          (0x400C6000UL) /**< EMU base address  */
#define RMU_BASE          (0x400CA000UL) /**< RMU base address  */
#define CMU_BASE          (0x400C8000UL) /**< CMU base address  */
#define AES_BASE          (0x400E0000UL) /**< AES base address  */
#define LESENSE_BASE      (0x4008C000UL) /**< LESENSE base address  */
#define EBI_BASE          (0x40008000UL) /**< EBI base address  */
#define GPIO_BASE         (0x40006000UL) /**< GPIO base address  */
#define PRS_BASE          (0x400CC000UL) /**< PRS base address  */
#define DMA_BASE          (0x400C2000UL) /**< DMA base address  */
#define TIMER0_BASE       (0x40010000UL) /**< TIMER0 base address  */
#define TIMER1_BASE       (0x40010400UL) /**< TIMER1 base address  */
#define TIMER2_BASE       (0x40010800UL) /**< TIMER2 base address  */
#define TIMER3_BASE       (0x40010C00UL) /**< TIMER3 base address  */
#define USART0_BASE       (0x4000C000UL) /**< USART0 base address  */
#define USART1_BASE       (0x4000C400UL) /**< USART1 base address  */
#define USART2_BASE       (0x4000C800UL) /**< USART2 base address  */
#define UART0_BASE        (0x4000E000UL) /**< UART0 base address  */
#define UART1_BASE        (0x4000E400UL) /**< UART1 base address  */
#define LEUART0_BASE      (0x40084000UL) /**< LEUART0 base address  */
#define LEUART1_BASE      (0x40084400UL) /**< LEUART1 base address  */
#define LETIMER0_BASE     (0x40082000UL) /**< LETIMER0 base address  */
#define PCNT0_BASE        (0x40086000UL) /**< PCNT0 base address  */
#define PCNT1_BASE        (0x40086400UL) /**< PCNT1 base address  */
#define PCNT2_BASE        (0x40086800UL) /**< PCNT2 base address  */
#define I2C0_BASE         (0x4000A000UL) /**< I2C0 base address  */
#define I2C1_BASE         (0x4000A400UL) /**< I2C1 base address  */
#define ADC0_BASE         (0x40002000UL) /**< ADC0 base address  */
#define DAC0_BASE         (0x40004000UL) /**< DAC0 base address  */
#define ACMP0_BASE        (0x40001000UL) /**< ACMP0 base address  */
#define ACMP1_BASE        (0x40001400UL) /**< ACMP1 base address  */
#define USB_BASE          (0x400C4000UL) /**< USB base address  */
#define VCMP_BASE         (0x40000000UL) /**< VCMP base address  */
#define LCD_BASE          (0x4008A000UL) /**< LCD base address  */
#define RTC_BASE          (0x40080000UL) /**< RTC base address  */
#define BURTC_BASE        (0x40081000UL) /**< BURTC base address  */
#define WDOG_BASE         (0x40088000UL) /**< WDOG base address  */
#define ETM_BASE          (0xE0041000UL) /**< ETM base address  */
#define CALIBRATE_BASE    (0x0FE08000UL) /**< CALIBRATE base address */
#define DEVINFO_BASE      (0x0FE081B0UL) /**< DEVINFO base address */
#define ROMTABLE_BASE     (0xE00FFFD0UL) /**< ROMTABLE base address */

/** @} End of group EFM32GG980F512_Peripheral_Base */

/**************************************************************************//**
 * @defgroup EFM32GG980F512_Peripheral_Declaration  EFM32GG980F512 Peripheral Declarations
 * @{
 *****************************************************************************/

#define MSC          ((MSC_TypeDef *) MSC_BASE)             /**< MSC base pointer */
#define EMU          ((EMU_TypeDef *) EMU_BASE)             /**< EMU base pointer */
#define RMU          ((RMU_TypeDef *) RMU_BASE)             /**< RMU base pointer */
#define CMU          ((CMU_TypeDef *) CMU_BASE)             /**< CMU base pointer */
#define AES          ((AES_TypeDef *) AES_BASE)             /**< AES base pointer */
#define LESENSE      ((LESENSE_TypeDef *) LESENSE_BASE)     /**< LESENSE base pointer */
#define EBI          ((EBI_TypeDef *) EBI_BASE)             /**< EBI base pointer */
#define GPIO         ((GPIO_TypeDef *) GPIO_BASE)           /**< GPIO base pointer */
#define PRS          ((PRS_TypeDef *) PRS_BASE)             /**< PRS base pointer */
#define DMA          ((DMA_TypeDef *) DMA_BASE)             /**< DMA base pointer */
#define TIMER0       ((TIMER_TypeDef *) TIMER0_BASE)        /**< TIMER0 base pointer */
#define TIMER1       ((TIMER_TypeDef *) TIMER1_BASE)        /**< TIMER1 base pointer */
#define TIMER2       ((TIMER_TypeDef *) TIMER2_BASE)        /**< TIMER2 base pointer */
#define TIMER3       ((TIMER_TypeDef *) TIMER3_BASE)        /**< TIMER3 base pointer */
#define USART0       ((USART_TypeDef *) USART0_BASE)        /**< USART0 base pointer */
#define USART1       ((USART_TypeDef *) USART1_BASE)        /**< USART1 base pointer */
#define USART2       ((USART_TypeDef *) USART2_BASE)        /**< USART2 base pointer */
#define UART0        ((USART_TypeDef *) UART0_BASE)         /**< UART0 base pointer */
#define UART1        ((USART_TypeDef *) UART1_BASE)         /**< UART1 base pointer */
#define LEUART0      ((LEUART_TypeDef *) LEUART0_BASE)      /**< LEUART0 base pointer */
#define LEUART1      ((LEUART_TypeDef *) LEUART1_BASE)      /**< LEUART1 base pointer */
#define LETIMER0     ((LETIMER_TypeDef *) LETIMER0_BASE)    /**< LETIMER0 base pointer */
#define PCNT0        ((PCNT_TypeDef *) PCNT0_BASE)          /**< PCNT0 base pointer */
#define PCNT1        ((PCNT_TypeDef *) PCNT1_BASE)          /**< PCNT1 base pointer */
#define PCNT2        ((PCNT_TypeDef *) PCNT2_BASE)          /**< PCNT2 base pointer */
#define I2C0         ((I2C_TypeDef *) I2C0_BASE)            /**< I2C0 base pointer */
#define I2C1         ((I2C_TypeDef *) I2C1_BASE)            /**< I2C1 base pointer */
#define ADC0         ((ADC_TypeDef *) ADC0_BASE)            /**< ADC0 base pointer */
#define DAC0         ((DAC_TypeDef *) DAC0_BASE)            /**< DAC0 base pointer */
#define ACMP0        ((ACMP_TypeDef *) ACMP0_BASE)          /**< ACMP0 base pointer */
#define ACMP1        ((ACMP_TypeDef *) ACMP1_BASE)          /**< ACMP1 base pointer */
#define USB          ((USB_TypeDef *) USB_BASE)             /**< USB base pointer */
#define VCMP         ((VCMP_TypeDef *) VCMP_BASE)           /**< VCMP base pointer */
#define LCD          ((LCD_TypeDef *) LCD_BASE)             /**< LCD base pointer */
#define RTC          ((RTC_TypeDef *) RTC_BASE)             /**< RTC base pointer */
#define BURTC        ((BURTC_TypeDef *) BURTC_BASE)         /**< BURTC base pointer */
#define WDOG         ((WDOG_TypeDef *) WDOG_BASE)           /**< WDOG base pointer */
#define ETM          ((ETM_TypeDef *) ETM_BASE)             /**< ETM base pointer */
#define CALIBRATE    ((CALIBRATE_TypeDef *) CALIBRATE_BASE) /**< CALIBRATE base pointer */
#define DEVINFO      ((DEVINFO_TypeDef *) DEVINFO_BASE)     /**< DEVINFO base pointer */
#define ROMTABLE     ((ROMTABLE_TypeDef *) ROMTABLE_BASE)   /**< ROMTABLE base pointer */

/** @} End of group EFM32GG980F512_Peripheral_Declaration */

/**************************************************************************//**
 * @defgroup EFM32GG980F512_BitFields EFM32GG980F512 Bit Fields
 * @{
 *****************************************************************************/

#include "efm32gg_prs_signals.h"
#include "efm32gg_dmareq.h"
#include "efm32gg_dmactrl.h"
#include "efm32gg_uart.h"

/**************************************************************************//**
 * @defgroup EFM32GG980F512_UNLOCK Unlock Codes
 * @{
 *****************************************************************************/
#define MSC_UNLOCK_CODE      0x1B71 /**< MSC unlock code */
#define EMU_UNLOCK_CODE      0xADE8 /**< EMU unlock code */
#define CMU_UNLOCK_CODE      0x580E /**< CMU unlock code */
#define GPIO_UNLOCK_CODE     0xA534 /**< GPIO unlock code */
#define TIMER_UNLOCK_CODE    0xCE80 /**< TIMER unlock code */
#define BURTC_UNLOCK_CODE    0xAEE8 /**< BURTC unlock code */

/** @} End of group EFM32GG980F512_UNLOCK */

/** @} End of group EFM32GG980F512_BitFields */

/**************************************************************************//**
 * @defgroup EFM32GG980F512_Alternate_Function EFM32GG980F512 Alternate Function
 * @{
 *****************************************************************************/

#include "efm32gg_af_channels.h"
#include "efm32gg_af_ports.h"
#include "efm32gg_af_pins.h"

/** @} End of group EFM32GG980F512_Alternate_Function */

/**************************************************************************//**
 *  @brief Set the value of a bit field within a register.
 *
 *  @param REG
 *       The register to update
 *  @param MASK
 *       The mask for the bit field to update
 *  @param VALUE
 *       The value to write to the bit field
 *  @param OFFSET
 *       The number of bits that the field is offset within the register.
 *       0 (zero) means LSB.
 *****************************************************************************/
#define SET_BIT_FIELD(REG, MASK, VALUE, OFFSET) \
  REG = ((REG) &~(MASK)) | (((VALUE) << (OFFSET)) & (MASK));

/** @} End of group EFM32GG980F512  */

/** @} End of group Parts */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32GG980F512_H */
