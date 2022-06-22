/**
  **************************************************************************
  * @file     at32f415.h
  * @version  v2.0.5
  * @date     2022-05-20
  * @brief    at32f415 header file
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

#ifndef __AT32F415_H
#define __AT32F415_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__CC_ARM)
 #pragma anon_unions
#endif

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F415
  * @{
  */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * tip: to avoid modifying this file each time you need to switch between these
  *      devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined (AT32F415RCT7)   && !defined (AT32F415RCT7_7) && !defined (AT32F415CCT7)   && \
    !defined (AT32F415CCU7)   && !defined (AT32F415KCU7_4) && !defined (AT32F415RBT7)   && \
    !defined (AT32F415RBT7_7) && !defined (AT32F415CBT7)   && !defined (AT32F415CBU7)   && \
    !defined (AT32F415KBU7_4) && !defined (AT32F415R8T7)   && !defined (AT32F415R8T7_7) && \
    !defined (AT32F415C8T7)   && !defined (AT32F415K8U7_4)

    #error "Please select first the target device used in your application (in at32f415.h file)"
#endif

#if defined (AT32F415RCT7)   || defined (AT32F415RCT7_7) || defined (AT32F415CCT7)   || \
    defined (AT32F415CCU7)   || defined (AT32F415KCU7_4) || defined (AT32F415RBT7)   || \
    defined (AT32F415RBT7_7) || defined (AT32F415CBT7)   || defined (AT32F415CBU7)   || \
    defined (AT32F415KBU7_4) || defined (AT32F415R8T7)   || defined (AT32F415R8T7_7) || \
    defined (AT32F415C8T7)   || defined (AT32F415K8U7_4)

    #define AT32F415xx
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
  * @brief at32f415 standard peripheral library version number
  */
#define __AT32F415_LIBRARY_VERSION_MAJOR    (0x02) /*!< [31:24] major version */
#define __AT32F415_LIBRARY_VERSION_MIDDLE   (0x00) /*!< [23:16] middle version */
#define __AT32F415_LIBRARY_VERSION_MINOR    (0x05) /*!< [15:8]  minor version */
#define __AT32F415_LIBRARY_VERSION_RC       (0x00) /*!< [7:0]  release candidate */
#define __AT32F415_LIBRARY_VERSION          ((__AT32F415_LIBRARY_VERSION_MAJOR << 24)  | \
                                             (__AT32F415_LIBRARY_VERSION_MIDDLE << 16) | \
                                             (__AT32F415_LIBRARY_VERSION_MINOR << 8)   | \
                                             (__AT32F415_LIBRARY_VERSION_RC))

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
  * @brief at32f415 interrupt number definition, according to the selected device
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
    TAMP_STAMP_IRQn             = 2,      /*!< tamper and timestamp interrupts through the exint line */
    ERTC_WKUP_IRQn              = 3,      /*!< ertc wakeup through the exint line                   */
    FLASH_IRQn                  = 4,      /*!< flash global interrupt                               */
    CRM_IRQn                    = 5,      /*!< crm global interrupt                                 */
    EXINT0_IRQn                 = 6,      /*!< external line0 interrupt                             */
    EXINT1_IRQn                 = 7,      /*!< external line1 interrupt                             */
    EXINT2_IRQn                 = 8,      /*!< external line2 interrupt                             */
    EXINT3_IRQn                 = 9,      /*!< external line3 interrupt                             */
    EXINT4_IRQn                 = 10,     /*!< external line4 interrupt                             */
    DMA1_Channel1_IRQn          = 11,     /*!< dma1 channel 1 global interrupt                      */
    DMA1_Channel2_IRQn          = 12,     /*!< dma1 channel 2 global interrupt                      */
    DMA1_Channel3_IRQn          = 13,     /*!< dma1 channel 3 global interrupt                      */
    DMA1_Channel4_IRQn          = 14,     /*!< dma1 channel 4 global interrupt                      */
    DMA1_Channel5_IRQn          = 15,     /*!< dma1 channel 5 global interrupt                      */
    DMA1_Channel6_IRQn          = 16,     /*!< dma1 channel 6 global interrupt                      */
    DMA1_Channel7_IRQn          = 17,     /*!< dma1 channel 7 global interrupt                      */

    ADC1_IRQn                   = 18,     /*!< adc1 global interrupt                                */
    CAN1_TX_IRQn                = 19,     /*!< can1 tx interrupts                                   */
    CAN1_RX0_IRQn               = 20,     /*!< can1 rx0 interrupts                                  */
    CAN1_RX1_IRQn               = 21,     /*!< can1 rx1 interrupt                                   */
    CAN1_SE_IRQn                = 22,     /*!< can1 se interrupt                                    */
    EXINT9_5_IRQn               = 23,     /*!< external line[9:5] interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< tmr1 brake interrupt                                 */
    TMR1_OVF_TMR10_IRQn         = 25,     /*!< tmr1 overflow interrupt                              */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< tmr1 trigger and hall interrupt                      */
    TMR1_CH_IRQn                = 27,     /*!< tmr1 channel interrupt                               */
    TMR2_GLOBAL_IRQn            = 28,     /*!< tmr2 global interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< tmr3 global interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< tmr4 global interrupt                                */
    I2C1_EVT_IRQn               = 31,     /*!< i2c1 event interrupt                                 */
    I2C1_ERR_IRQn               = 32,     /*!< i2c1 error interrupt                                 */
    I2C2_EVT_IRQn               = 33,     /*!< i2c2 event interrupt                                 */
    I2C2_ERR_IRQn               = 34,     /*!< i2c2 error interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< spi1 global interrupt                                */
    SPI2_IRQn                   = 36,     /*!< spi2 global interrupt                                */
    USART1_IRQn                 = 37,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /*!< usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /*!< usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /*!< external line[15:10] interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ertc alarm through exint line interrupt              */
    OTGFS1_WKUP_IRQn            = 42,     /*!< otgfs1 wakeup from suspend through exint line interrupt */
    SDIO1_IRQn                  = 49,     /*!< sdio1 global interrupt                               */
    TMR5_GLOBAL_IRQn            = 50,     /*!< tmr5 global interrupt                                */
    UART4_IRQn                  = 52,     /*!< uart4 global interrupt                               */
    UART5_IRQn                  = 53,     /*!< uart5 global interrupt                               */
    DMA2_Channel1_IRQn          = 56,     /*!< dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< dma2 channel 3 global interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< dma2 channel 4 and channel 5 global interrupt        */
    OTGFS1_IRQn                 = 67,     /*!< otgfs1 global interrupt                              */
    CMP1_IRQn                   = 70,     /*!< comparator1 global interrupt                         */
    CMP2_IRQn                   = 71,     /*!< comparator2 global interrupt                         */
    DMA2_Channel6_7_IRQn        = 75,     /*!< dma2 channel 6 and channel 7 global interrupt        */

} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"
#include "system_at32f415.h"
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
#define SPIM_FLASH_BASE                  ((uint32_t)0x08400000)
#define USD_BASE                         ((uint32_t)0x1FFFF800)
#define SRAM_BASE                        ((uint32_t)0x20000000)
#define PERIPH_BASE                      ((uint32_t)0x40000000)
#define DEBUG_BASE                       ((uint32_t)0xE0042000)

#define APB1PERIPH_BASE                  (PERIPH_BASE + 0x00000)
#define APB2PERIPH_BASE                  (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE                   (PERIPH_BASE + 0x20000)

/* apb1 bus base address */
#define TMR2_BASE                        (APB1PERIPH_BASE + 0x0000)
#define TMR3_BASE                        (APB1PERIPH_BASE + 0x0400)
#define TMR4_BASE                        (APB1PERIPH_BASE + 0x0800)
#define TMR5_BASE                        (APB1PERIPH_BASE + 0x0C00)
#define CMP_BASE                         (APB1PERIPH_BASE + 0x2400)
#define ERTC_BASE                        (APB1PERIPH_BASE + 0x2800)
#define WWDT_BASE                        (APB1PERIPH_BASE + 0x2C00)
#define WDT_BASE                         (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE                        (APB1PERIPH_BASE + 0x3800)
#define USART2_BASE                      (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE                      (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE                       (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE                       (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
/* apb2 bus base address */
#define IOMUX_BASE                       (APB2PERIPH_BASE + 0x0000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE                       (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE                       (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE                       (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE                       (APB2PERIPH_BASE + 0x1400)
#define GPIOF_BASE                       (APB2PERIPH_BASE + 0x1C00)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x3800)
#define TMR9_BASE                        (APB2PERIPH_BASE + 0x4C00)
#define TMR10_BASE                       (APB2PERIPH_BASE + 0x5000)
#define TMR11_BASE                       (APB2PERIPH_BASE + 0x5400)
#define SDIO1_BASE                       (APB2PERIPH_BASE + 0x8000)
/* ahb bus base address */
#define DMA1_BASE                        (AHBPERIPH_BASE + 0x0000)
#define DMA1_CHANNEL1_BASE               (AHBPERIPH_BASE + 0x0008)
#define DMA1_CHANNEL2_BASE               (AHBPERIPH_BASE + 0x001C)
#define DMA1_CHANNEL3_BASE               (AHBPERIPH_BASE + 0x0030)
#define DMA1_CHANNEL4_BASE               (AHBPERIPH_BASE + 0x0044)
#define DMA1_CHANNEL5_BASE               (AHBPERIPH_BASE + 0x0058)
#define DMA1_CHANNEL6_BASE               (AHBPERIPH_BASE + 0x006C)
#define DMA1_CHANNEL7_BASE               (AHBPERIPH_BASE + 0x0080)
#define DMA2_BASE                        (AHBPERIPH_BASE + 0x0400)
#define DMA2_CHANNEL1_BASE               (AHBPERIPH_BASE + 0x0408)
#define DMA2_CHANNEL2_BASE               (AHBPERIPH_BASE + 0x041C)
#define DMA2_CHANNEL3_BASE               (AHBPERIPH_BASE + 0x0430)
#define DMA2_CHANNEL4_BASE               (AHBPERIPH_BASE + 0x0444)
#define DMA2_CHANNEL5_BASE               (AHBPERIPH_BASE + 0x0458)
#define DMA2_CHANNEL6_BASE               (AHBPERIPH_BASE + 0x046C)
#define DMA2_CHANNEL7_BASE               (AHBPERIPH_BASE + 0x0480)
#define CRM_BASE                         (AHBPERIPH_BASE + 0x1000)
#define FLASH_REG_BASE                   (AHBPERIPH_BASE + 0x2000)
#define CRC_BASE                         (AHBPERIPH_BASE + 0x3000)
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

#include "at32f415_def.h"
#include "at32f415_conf.h"

#ifdef __cplusplus
}
#endif

#endif
