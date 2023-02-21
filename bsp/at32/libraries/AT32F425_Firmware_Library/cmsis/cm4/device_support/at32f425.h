/**
  **************************************************************************
  * @file     at32f425.h
  * @brief    at32f425 header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#ifndef __AT32F425_H
#define __AT32F425_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__CC_ARM)
 #pragma anon_unions
#endif

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F425
  * @{
  */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * tip: to avoid modifying this file each time you need to switch between these
  *      devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined (AT32F425R8T7)   && !defined (AT32F425R8T7_7) && !defined (AT32F425C8T7)   && \
    !defined (AT32F425C8U7)   && !defined (AT32F425K8T7)   && !defined (AT32F425K8U7_4) && \
    !defined (AT32F425F8P7)   && !defined (AT32F425G8U7)   && !defined (AT32F425R6T7)   && \
    !defined (AT32F425R6T7_7) && !defined (AT32F425C6T7)   && !defined (AT32F425C6U7)   && \
    !defined (AT32F425K6T7)   && !defined (AT32F425K6U7_4) && !defined (AT32F425F6P7)   && \
    !defined (AT32F425G6U7)

    #error "Please select first the target device used in your application (in at32f425.h file)"
#endif

#if defined (AT32F425R8T7)   || defined (AT32F425R8T7_7) || defined (AT32F425C8T7)   || \
    defined (AT32F425C8U7)   || defined (AT32F425K8T7)   || defined (AT32F425K8U7_4) || \
    defined (AT32F425F8P7)   || defined (AT32F425G8U7)   || defined (AT32F425R6T7)   || \
    defined (AT32F425R6T7_7) || defined (AT32F425C6T7)   || defined (AT32F425C6U7)   || \
    defined (AT32F425K6T7)   || defined (AT32F425K6U7_4) || defined (AT32F425F6P7)   || \
    defined (AT32F425G6U7)

    #define AT32F425xx
#endif

#if defined (AT32F425R8T7)   || defined (AT32F425R8T7_7) || defined (AT32F425R6T7)   || \
    defined (AT32F425R6T7_7)

    #define AT32F425Rx
#endif

#if defined (AT32F425C8T7)   || defined (AT32F425C8U7)   || defined (AT32F425C6T7)   || \
    defined (AT32F425C6U7)

    #define AT32F425Cx
#endif

#if defined (AT32F425K8T7)   || defined (AT32F425K8U7_4) || defined (AT32F425K6T7)   || \
    defined (AT32F425K6U7_4)

    #define AT32F425Kx
#endif

#if defined (AT32F425G8U7)   || defined (AT32F425G6U7)

    #define AT32F425Gx
#endif

#if defined (AT32F425F8P7)   || defined (AT32F425F6P7)

    #define AT32F425Fx
#endif

#ifndef USE_STDPERIPH_DRIVER
/**
  * @brief comment the line below if you will not use the peripherals drivers.
  * in this case, these drivers will not be included and the application code will
  * be based on direct access to peripherals registers
  */
  #ifdef _RTE_
    #include "RTE_Components.h"
    #ifdef RTE_DEVICE_STDPERIPH_FRAMEWORK
      #define USE_STDPERIPH_DRIVER
    #endif
  #endif
#endif

/**
  * @brief at32f425 standard peripheral library version number
  */
#define __AT32F425_LIBRARY_VERSION_MAJOR    (0x02) /*!< [31:24] major version */
#define __AT32F425_LIBRARY_VERSION_MIDDLE   (0x00) /*!< [23:16] middle version */
#define __AT32F425_LIBRARY_VERSION_MINOR    (0x06) /*!< [15:8]  minor version */
#define __AT32F425_LIBRARY_VERSION_RC       (0x00) /*!< [7:0]  release candidate */
#define __AT32F425_LIBRARY_VERSION          ((__AT32F425_LIBRARY_VERSION_MAJOR << 24)  | \
                                             (__AT32F425_LIBRARY_VERSION_MIDDLE << 16) | \
                                             (__AT32F425_LIBRARY_VERSION_MINOR << 8)   | \
                                             (__AT32F425_LIBRARY_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
  * @brief configuration of the cortex-m4 processor and core peripherals
  */
#define __CM4_REV                 0x0001U  /*!< core revision r0p1                           */
#define __MPU_PRESENT             1        /*!< mpu present                                  */
#define __NVIC_PRIO_BITS          4        /*!< at32 uses 4 bits for the priority levels     */
#define __Vendor_SysTickConfig    0        /*!< set to 1 if different systick config is used */
#define __FPU_PRESENT             0U       /*!< fpu present                                  */

/**
  * @brief at32f425 interrupt number definition, according to the selected device
  *        in @ref Library_configuration_section
  */
typedef enum IRQn
{
    /******  cortex-m4 processor exceptions numbers ***************************************************/
    Reset_IRQn                  = -15,    /*!< 1 reset vector, invoked on power up and warm reset   */
    NonMaskableInt_IRQn         = -14,    /*!< 2 non maskable interrupt                             */
    HardFault_IRQn              = -13,    /*!< 3 hard fault, all classes of fault                   */
    MemoryManagement_IRQn       = -12,    /*!< 4 cortex-m4 memory management interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 cortex-m4 bus fault interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 cortex-m4 usage fault interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 cortex-m4 sv call interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 cortex-m4 debug monitor interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 cortex-m4 pend sv interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 cortex-m4 system tick interrupt                   */

    /******  at32 specific interrupt numbers *********************************************************/
    WWDT_IRQn                   = 0,      /*!< window watchdog timer interrupt                      */
    PVM_IRQn                    = 1,      /*!< pvm through exint line detection interrupt           */
    ERTC_IRQn                   = 2,      /*!< ertc global interrupt                                */
    FLASH_IRQn                  = 3,      /*!< flash global interrupt                               */
    CRM_IRQn                    = 4,      /*!< crm global interrupt                                 */
    EXINT1_0_IRQn               = 5,      /*!< external line1~0 interrupt                           */
    EXINT3_2_IRQn               = 6,      /*!< external line3~2 interrupt                           */
    EXINT15_4_IRQn              = 7,      /*!< external line15~4 interrupt                          */

    ACC_IRQn                    = 8,      /*!< acc interrupt                                        */
    DMA1_Channel1_IRQn          = 9,      /*!< dma1 channel 1 global interrupt                      */
    DMA1_Channel3_2_IRQn        = 10,     /*!< dma1 channel 3~2 global interrupt                    */
    DMA1_Channel7_4_IRQn        = 11,     /*!< dma1 channel 7~4 global interrupt                    */
    ADC1_IRQn                   = 12,     /*!< adc1 global interrupt                                */
    TMR1_BRK_OVF_TRG_HALL_IRQn  = 13,     /*!< tmr1 brake overflow trigger and hall interrupt       */
    TMR1_CH_IRQn                = 14,     /*!< tmr1 channel interrupt                               */
    TMR2_GLOBAL_IRQn            = 15,     /*!< tmr2 channel interrupt                               */
    TMR3_GLOBAL_IRQn            = 16,     /*!< tmr3 global interrupt                                */
    TMR6_GLOBAL_IRQn            = 17,     /*!< tmr6 global interrupt                                */
    TMR7_GLOBAL_IRQn            = 18,     /*!< tmr7 channel interrupt                               */
    TMR14_GLOBAL_IRQn           = 19,     /*!< tmr14 global interrupt                               */
    TMR15_GLOBAL_IRQn           = 20,     /*!< tmr15 global interrupt                               */
    TMR16_GLOBAL_IRQn           = 21,     /*!< tmr16 global interrupt                               */
    TMR17_GLOBAL_IRQn           = 22,     /*!< tmr17 global interrupt                               */
    I2C1_EVT_IRQn               = 23,     /*!< i2c1 event interrupt                                 */
    I2C2_EVT_IRQn               = 24,     /*!< i2c2 event interrupt                                 */
    SPI1_IRQn                   = 25,     /*!< spi1 global interrupt                                */
    SPI2_IRQn                   = 26,     /*!< spi2 global interrupt                                */
    USART1_IRQn                 = 27,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 28,     /*!< usart2 global interrupt                              */
    USART4_3_IRQn               = 29,     /*!< usart3 & usart4 global interrupt                     */
    CAN1_IRQn                   = 30,     /*!< can1 global interrupt                                */
    OTGFS1_IRQn                 = 31,     /*!< otgfs1 global interrupt                              */
    I2C1_ERR_IRQn               = 32,     /*!< i2c1 error interrupt                                 */
    SPI3_IRQn                   = 33,     /*!< spi3 global interrupt                                */
    I2C2_ERR_IRQn               = 34,     /*!< i2c2 error interrupt                                 */
    TMR13_GLOBAL_IRQn           = 35,     /*!< tmr13 global interrupt                               */

} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"
#include "system_at32f425.h"
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */

typedef int32_t  INT32;
typedef int16_t  INT16;
typedef int8_t   INT8;
typedef uint32_t UINT32;
typedef uint16_t UINT16;
typedef uint8_t  UINT8;

typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef const int32_t sc32;   /*!< read only */
typedef const int16_t sc16;   /*!< read only */
typedef const int8_t  sc8;    /*!< read only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;    /*!< read only */
typedef __I int16_t vsc16;    /*!< read only */
typedef __I int8_t  vsc8;     /*!< read only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< read only */
typedef const uint16_t uc16;  /*!< read only */
typedef const uint8_t  uc8;   /*!< read only */

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;   /*!< read only */
typedef __I uint16_t vuc16;   /*!< read only */
typedef __I uint8_t  vuc8;    /*!< read only */

/**
  * @brief flag status
  */
typedef enum {RESET = 0, SET = !RESET} flag_status;

/**
  * @brief confirm state
  */
typedef enum {FALSE = 0, TRUE = !FALSE} confirm_state;

/**
  * @brief error status
  */
typedef enum {ERROR = 0, SUCCESS = !ERROR} error_status;

/**
  * @}
  */

/** @addtogroup Exported_macro
  * @{
  */

#define REG8(addr)                       *(volatile uint8_t *)(addr)
#define REG16(addr)                      *(volatile uint16_t *)(addr)
#define REG32(addr)                      *(volatile uint32_t *)(addr)

#define MAKE_VALUE(reg_offset, bit_num)  (uint32_t)(((reg_offset) << 16) | (bit_num & 0x1F))

#define PERIPH_REG(periph_base, value)   REG32((periph_base + (value >> 16)))
#define PERIPH_REG_BIT(value)            (0x1U << (value & 0x1F))

/**
  * @}
  */

/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE                       ((uint32_t)0x08000000)
#define USD_BASE                         ((uint32_t)0x1FFFF800)
#define SRAM_BASE                        ((uint32_t)0x20000000)
#define PERIPH_BASE                      ((uint32_t)0x40000000)
#define DEBUG_BASE                       ((uint32_t)0xE0042000)

#define APB1PERIPH_BASE                  (PERIPH_BASE + 0x00000)
#define APB2PERIPH_BASE                  (PERIPH_BASE + 0x10000)
#define AHBPERIPH1_BASE                  (PERIPH_BASE + 0x20000)
#define AHBPERIPH2_BASE                  (PERIPH_BASE + 0x8000000)

/* apb1 bus base address */
#define TMR2_BASE                        (APB1PERIPH_BASE + 0x0000)
#define TMR3_BASE                        (APB1PERIPH_BASE + 0x0400)
#define TMR6_BASE                        (APB1PERIPH_BASE + 0x1000)
#define TMR7_BASE                        (APB1PERIPH_BASE + 0x1400)
#define TMR13_BASE                       (APB1PERIPH_BASE + 0x1C00)
#define TMR14_BASE                       (APB1PERIPH_BASE + 0x2000)
#define ERTC_BASE                        (APB1PERIPH_BASE + 0x2800)
#define WWDT_BASE                        (APB1PERIPH_BASE + 0x2C00)
#define WDT_BASE                         (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE                        (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE                        (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASE                      (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE                      (APB1PERIPH_BASE + 0x4800)
#define USART4_BASE                      (APB1PERIPH_BASE + 0x4C00)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define ACC_BASE                         (APB1PERIPH_BASE + 0x6C00)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
/* apb2 bus base address */
#define SCFG_BASE                        (APB2PERIPH_BASE + 0x0000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x0400)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x3800)
#define TMR15_BASE                       (APB2PERIPH_BASE + 0x4000)
#define TMR16_BASE                       (APB2PERIPH_BASE + 0x4400)
#define TMR17_BASE                       (APB2PERIPH_BASE + 0x4800)
/* ahb bus base address */
#define DMA1_BASE                        (AHBPERIPH1_BASE + 0x0000)
#define DMA1_CHANNEL1_BASE               (AHBPERIPH1_BASE + 0x0008)
#define DMA1_CHANNEL2_BASE               (AHBPERIPH1_BASE + 0x001C)
#define DMA1_CHANNEL3_BASE               (AHBPERIPH1_BASE + 0x0030)
#define DMA1_CHANNEL4_BASE               (AHBPERIPH1_BASE + 0x0044)
#define DMA1_CHANNEL5_BASE               (AHBPERIPH1_BASE + 0x0058)
#define DMA1_CHANNEL6_BASE               (AHBPERIPH1_BASE + 0x006C)
#define DMA1_CHANNEL7_BASE               (AHBPERIPH1_BASE + 0x0080)
#define CRM_BASE                         (AHBPERIPH1_BASE + 0x1000)
#define FLASH_REG_BASE                   (AHBPERIPH1_BASE + 0x2000)
#define CRC_BASE                         (AHBPERIPH1_BASE + 0x3000)
#define GPIOA_BASE                       (AHBPERIPH2_BASE + 0x0000)
#define GPIOB_BASE                       (AHBPERIPH2_BASE + 0x0400)
#define GPIOC_BASE                       (AHBPERIPH2_BASE + 0x0800)
#define GPIOD_BASE                       (AHBPERIPH2_BASE + 0x0C00)
#define GPIOF_BASE                       (AHBPERIPH2_BASE + 0x1400)
#define OTGFS1_BASE                      (PERIPH_BASE + 0x10000000)

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#include "at32f425_def.h"
#include "at32f425_conf.h"

#ifdef __cplusplus
}
#endif

#endif
