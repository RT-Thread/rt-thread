/**
  **************************************************************************
  * @file     at32f435_437.h
  * @version  v2.0.8
  * @date     2022-04-25
  * @brief    at32f435_437 header file
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

#ifndef __AT32F435_437_H
#define __AT32F435_437_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__CC_ARM)
 #pragma anon_unions
#endif


/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F435_437
  * @{
  */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * tip: to avoid modifying this file each time you need to switch between these
  *      devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined (AT32F435CCU7) && !defined (AT32F435CGU7) && !defined (AT32F435CMU7) && \
    !defined (AT32F435CCT7) && !defined (AT32F435CGT7) && !defined (AT32F435CMT7) && \
    !defined (AT32F435RCT7) && !defined (AT32F435RGT7) && !defined (AT32F435RMT7) && \
    !defined (AT32F435VCT7) && !defined (AT32F435VGT7) && !defined (AT32F435VMT7) && \
    !defined (AT32F435ZCT7) && !defined (AT32F435ZGT7) && !defined (AT32F435ZMT7) && \
    !defined (AT32F437RCT7) && !defined (AT32F437RGT7) && !defined (AT32F437RMT7) && \
    !defined (AT32F437VCT7) && !defined (AT32F437VGT7) && !defined (AT32F437VMT7) && \
    !defined (AT32F437ZCT7) && !defined (AT32F437ZGT7) && !defined (AT32F437ZMT7)

    #error "Please select first the target device used in your application (in at32f435_437.h file)"
#endif

#if defined (AT32F435CCU7) || defined (AT32F435CGU7) || defined (AT32F435CMU7) || \
    defined (AT32F435CCT7) || defined (AT32F435CGT7) || defined (AT32F435CMT7) || \
    defined (AT32F435RCT7) || defined (AT32F435RGT7) || defined (AT32F435RMT7) || \
    defined (AT32F435VCT7) || defined (AT32F435VGT7) || defined (AT32F435VMT7) || \
    defined (AT32F435ZCT7) || defined (AT32F435ZGT7) || defined (AT32F435ZMT7)

    #define AT32F435xx
#endif

#if defined (AT32F437RCT7) || defined (AT32F437RGT7) || defined (AT32F437RMT7) || \
    defined (AT32F437VCT7) || defined (AT32F437VGT7) || defined (AT32F437VMT7) || \
    defined (AT32F437ZCT7) || defined (AT32F437ZGT7) || defined (AT32F437ZMT7)

    #define AT32F437xx
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
  * @brief at32f435_437 standard peripheral library version number
  */
#define __AT32F435_437_LIBRARY_VERSION_MAJOR    (0x02) /*!< [31:24] major version */
#define __AT32F435_437_LIBRARY_VERSION_MIDDLE   (0x00) /*!< [23:16] middle version */
#define __AT32F435_437_LIBRARY_VERSION_MINOR    (0x08) /*!< [15:8]  minor version */
#define __AT32F435_437_LIBRARY_VERSION_RC       (0x00) /*!< [7:0]  release candidate */
#define __AT32F435_437_LIBRARY_VERSION          ((__AT32F435_437_LIBRARY_VERSION_MAJOR << 24)  | \
                                                 (__AT32F435_437_LIBRARY_VERSION_MIDDLE << 16) | \
                                                 (__AT32F435_437_LIBRARY_VERSION_MINOR << 8)   | \
                                                 (__AT32F435_437_LIBRARY_VERSION_RC))

/**
  * @}
  */

/** @addtogroup configuration_section_for_cmsis
  * @{
  */

/**
  * @brief configuration of the cortex-m4 processor and core peripherals
  */
#define __CM4_REV                 0x0001U  /*!< core revision r0p1                           */
#define __MPU_PRESENT             1        /*!< mpu present                                  */
#define __NVIC_PRIO_BITS          4        /*!< at32 uses 4 bits for the priority levels     */
#define __Vendor_SysTickConfig    0        /*!< set to 1 if different systick config is used */
#define __FPU_PRESENT             1U       /*!< fpu present                                  */

/**
  * @brief at32f435_437 interrupt number definition, according to the selected device
  *        in @ref library_configuration_section
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
    EXINT0_IRQn                 = 6,      /*!< exint line0 interrupt                                */
    EXINT1_IRQn                 = 7,      /*!< exint line1 interrupt                                */
    EXINT2_IRQn                 = 8,      /*!< exint line2 interrupt                                */
    EXINT3_IRQn                 = 9,      /*!< exint line3 interrupt                                */
    EXINT4_IRQn                 = 10,     /*!< exint line4 interrupt                                */
    EDMA_Stream1_IRQn           = 11,     /*!< edma stream 1 global interrupt                       */
    EDMA_Stream2_IRQn           = 12,     /*!< edma stream 2 global interrupt                       */
    EDMA_Stream3_IRQn           = 13,     /*!< edma stream 3 global interrupt                       */
    EDMA_Stream4_IRQn           = 14,     /*!< edma stream 4 global interrupt                       */
    EDMA_Stream5_IRQn           = 15,     /*!< edma stream 5 global interrupt                       */
    EDMA_Stream6_IRQn           = 16,     /*!< edma stream 6 global interrupt                       */
    EDMA_Stream7_IRQn           = 17,     /*!< edma stream 7 global interrupt                       */

#if defined (AT32F435xx)
    ADC1_2_3_IRQn               = 18,     /*!< adc1 adc2 and adc3 global interrupt                  */
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
    SPI2_I2S2EXT_IRQn           = 36,     /*!< spi2 global interrupt                                */
    USART1_IRQn                 = 37,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /*!< usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /*!< usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /*!< external line[15:10] interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ertc alarm through exint line interrupt              */
    OTGFS1_WKUP_IRQn            = 42,     /*!< otgfs1 wakeup from suspend through exint line interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< tmr8 brake interrupt                                 */
    TMR8_OVF_TMR13_IRQn         = 44,     /*!< tmr8 overflow interrupt                              */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< tmr8 trigger and hall interrupt                      */
    TMR8_CH_IRQn                = 46,     /*!< tmr8 channel interrupt                               */
    EDMA_Stream8_IRQn           = 47,     /*!< edma stream 8 global interrupt                       */
    XMC_IRQn                    = 48,     /*!< xmc global interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< sdio global interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< tmr5 global interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< spi3 global interrupt                                */
    UART4_IRQn                  = 52,     /*!< uart4 global interrupt                               */
    UART5_IRQn                  = 53,     /*!< uart5 global interrupt                               */
    TMR6_DAC_GLOBAL_IRQn        = 54,     /*!< tmr6 and dac global interrupt                        */
    TMR7_GLOBAL_IRQn            = 55,     /*!< tmr7 global interrupt                                */
    DMA1_Channel1_IRQn          = 56,     /*!< dma1 channel 0 global interrupt                      */
    DMA1_Channel2_IRQn          = 57,     /*!< dma1 channel 1 global interrupt                      */
    DMA1_Channel3_IRQn          = 58,     /*!< dma1 channel 2 global interrupt                      */
    DMA1_Channel4_IRQn          = 59,     /*!< dma1 channel 3 global interrupt                      */
    DMA1_Channel5_IRQn          = 60,     /*!< dma1 channel 4 global interrupt                      */
    CAN2_TX_IRQn                = 63,     /*!< can2 tx interrupt                                    */
    CAN2_RX0_IRQn               = 64,     /*!< can2 rx0 interrupt                                   */
    CAN2_RX1_IRQn               = 65,     /*!< can2 rx1 interrupt                                   */
    CAN2_SE_IRQn                = 66,     /*!< can2 se interrupt                                    */
    OTGFS1_IRQn                 = 67,     /*!< otgfs1 interrupt                                     */
    DMA1_Channel6_IRQn          = 68,     /*!< dma1 channel 5 global interrupt                      */
    DMA1_Channel7_IRQn          = 69,     /*!< dma1 channel 6 global interrupt                      */
    USART6_IRQn                 = 71,     /*!< usart6 interrupt                                     */
    I2C3_EVT_IRQn               = 72,     /*!< i2c3 event interrupt                                 */
    I2C3_ERR_IRQn               = 73,     /*!< i2c3 error interrupt                                 */
    OTGFS2_WKUP_IRQn            = 76,     /*!< otgfs2 wakeup from suspend through exint line interrupt */
    OTGFS2_IRQn                 = 77,     /*!< otgfs2 interrupt                                     */
    DVP_IRQn                    = 78,     /*!< dvp interrupt                                        */
    FPU_IRQn                    = 81,     /*!< fpu interrupt                                        */
    UART7_IRQn                  = 82,     /*!< uart7 interrupt                                      */
    UART8_IRQn                  = 83,     /*!< uart8 interrupt                                      */
    SPI4_IRQn                   = 84,     /*!< spi4 global interrupt                                */
    QSPI2_IRQn                  = 91,     /*!< qspi2 global interrupt                               */
    QSPI1_IRQn                  = 92,     /*!< qspi1 global interrupt                               */
    DMAMUX_IRQn                 = 94,     /*!< dmamux global interrupt                              */
    SDIO2_IRQn                  = 102,    /*!< sdio2 global interrupt                               */
    ACC_IRQn                    = 103,    /*!< acc interrupt                                        */
    TMR20_BRK_IRQn              = 104,    /*!< tmr20 brake interrupt                                */
    TMR20_OVF_IRQn              = 105,    /*!< tmr20 overflow interrupt                             */
    TMR20_TRG_HALL_IRQn         = 106,    /*!< tmr20 trigger and hall interrupt                     */
    TMR20_CH_IRQn               = 107,    /*!< tmr20 channel interrupt                              */
    DMA2_Channel1_IRQn          = 108,    /*!< dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 109,    /*!< dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 110,    /*!< dma2 channel 3 global interrupt                      */
    DMA2_Channel4_IRQn          = 111,    /*!< dma2 channel 4 global interrupt                      */
    DMA2_Channel5_IRQn          = 112,    /*!< dma2 channel 5 global interrupt                      */
    DMA2_Channel6_IRQn          = 113,    /*!< dma2 channel 6 global interrupt                      */
    DMA2_Channel7_IRQn          = 114,    /*!< dma2 channel 7 global interrupt                      */
#endif

#if defined (AT32F437xx)
    ADC1_2_3_IRQn               = 18,     /*!< adc1 adc2 and adc3 global interrupt                  */
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
    SPI2_I2S2EXT_IRQn           = 36,     /*!< spi2 global interrupt                                */
    USART1_IRQn                 = 37,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /*!< usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /*!< usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /*!< external line[15:10] interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ertc alarm through exint line interrupt              */
    OTGFS1_WKUP_IRQn            = 42,     /*!< otgfs1 wakeup from suspend through exint line interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< tmr8 brake interrupt                                 */
    TMR8_OVF_TMR13_IRQn         = 44,     /*!< tmr8 overflow interrupt                              */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< tmr8 trigger and hall interrupt                      */
    TMR8_CH_IRQn                = 46,     /*!< tmr8 channel interrupt                               */
    EDMA_Stream8_IRQn           = 47,     /*!< dma1 stream 8 global interrupt                       */
    XMC_IRQn                    = 48,     /*!< xmc global interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< sdio global interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< tmr5 global interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< spi3 global interrupt                                */
    UART4_IRQn                  = 52,     /*!< uart4 global interrupt                               */
    UART5_IRQn                  = 53,     /*!< uart5 global interrupt                               */
    TMR6_DAC_GLOBAL_IRQn        = 54,     /*!< tmr6 and dac global interrupt                        */
    TMR7_GLOBAL_IRQn            = 55,     /*!< tmr7 global interrupt                                */
    DMA1_Channel1_IRQn          = 56,     /*!< dma1 channel 0 global interrupt                      */
    DMA1_Channel2_IRQn          = 57,     /*!< dma1 channel 1 global interrupt                      */
    DMA1_Channel3_IRQn          = 58,     /*!< dma1 channel 2 global interrupt                      */
    DMA1_Channel4_IRQn          = 59,     /*!< dma1 channel 3 global interrupt                      */
    DMA1_Channel5_IRQn          = 60,     /*!< dma1 channel 4 global interrupt                      */
    EMAC_IRQn                   = 61,     /*!< emac interrupt                                       */
    EMAC_WKUP_IRQn              = 62,     /*!< emac wakeup interrupt                                */
    CAN2_TX_IRQn                = 63,     /*!< can2 tx interrupt                                    */
    CAN2_RX0_IRQn               = 64,     /*!< can2 rx0 interrupt                                   */
    CAN2_RX1_IRQn               = 65,     /*!< can2 rx1 interrupt                                   */
    CAN2_SE_IRQn                = 66,     /*!< can2 se interrupt                                    */
    OTGFS1_IRQn                 = 67,     /*!< otgfs1 interrupt                                     */
    DMA1_Channel6_IRQn          = 68,     /*!< dma1 channel 5 global interrupt                      */
    DMA1_Channel7_IRQn          = 69,     /*!< dma1 channel 6 global interrupt                      */
    USART6_IRQn                 = 71,     /*!< usart6 interrupt                                     */
    I2C3_EVT_IRQn               = 72,     /*!< i2c3 event interrupt                                 */
    I2C3_ERR_IRQn               = 73,     /*!< i2c3 error interrupt                                 */
    OTGFS2_WKUP_IRQn            = 76,     /*!< otgfs2 wakeup from suspend through exint line interrupt */
    OTGFS2_IRQn                 = 77,     /*!< otgfs2 interrupt                                     */
    DVP_IRQn                    = 78,     /*!< dvp interrupt                                        */
    FPU_IRQn                    = 81,     /*!< fpu interrupt                                        */
    UART7_IRQn                  = 82,     /*!< uart7 interrupt                                      */
    UART8_IRQn                  = 83,     /*!< uart8 interrupt                                      */
    SPI4_IRQn                   = 84,     /*!< spi4 global interrupt                                */
    QSPI2_IRQn                  = 91,     /*!< qspi2 global interrupt                               */
    QSPI1_IRQn                  = 92,     /*!< qspi1 global interrupt                               */
    DMAMUX_IRQn                 = 94,     /*!< dmamux global interrupt                              */
    SDIO2_IRQn                  = 102,    /*!< sdio2 global interrupt                               */
    ACC_IRQn                    = 103,    /*!< acc interrupt                                        */
    TMR20_BRK_IRQn              = 104,    /*!< tmr20 brake interrupt                                */
    TMR20_OVF_IRQn              = 105,    /*!< tmr20 overflow interrupt                             */
    TMR20_TRG_HALL_IRQn         = 106,    /*!< tmr20 trigger and hall interrupt                     */
    TMR20_CH_IRQn               = 107,    /*!< tmr20 channel interrupt                              */
    DMA2_Channel1_IRQn          = 108,    /*!< dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 109,    /*!< dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 110,    /*!< dma2 channel 3 global interrupt                      */
    DMA2_Channel4_IRQn          = 111,    /*!< dma2 channel 4 global interrupt                      */
    DMA2_Channel5_IRQn          = 112,    /*!< dma2 channel 5 global interrupt                      */
    DMA2_Channel6_IRQn          = 113,    /*!< dma2 channel 6 global interrupt                      */
    DMA2_Channel7_IRQn          = 114,    /*!< dma2 channel 7 global interrupt                      */
#endif

} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"
#include "system_at32f435_437.h"
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

typedef enum {RESET = 0, SET = !RESET} flag_status;
typedef enum {FALSE = 0, TRUE = !FALSE} confirm_state;
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

#define MAKE_VALUE(reg_offset, bit_num)  (((reg_offset) << 16) | (bit_num & 0x1f))

#define PERIPH_REG(periph_base, value)   REG32((periph_base + (value >> 16)))
#define PERIPH_REG_BIT(value)            (0x1u << (value & 0x1f))

/**
  * @}
  */

/** @addtogroup Peripheral_memory_map
  * @{
  */

#define XMC_SDRAM_MEM_BASE               ((uint32_t)0xC0000000)
#define QSPI2_MEM_BASE                   ((uint32_t)0xB0000000)
#define XMC_CARD_MEM_BASE                ((uint32_t)0xA8000000)
#define QSPI2_REG_BASE                   ((uint32_t)0xA0002000)
#define QSPI1_REG_BASE                   ((uint32_t)0xA0001000)
#define XMC_REG_BASE                     ((uint32_t)0xA0000000)
#define XMC_BANK1_REG_BASE               (XMC_REG_BASE + 0x0000)
#define XMC_BANK2_REG_BASE               (XMC_REG_BASE + 0x0060)
#define XMC_BANK3_REG_BASE               (XMC_REG_BASE + 0x0080)
#define XMC_BANK4_REG_BASE               (XMC_REG_BASE + 0x00A0)
#define XMC_SDRAM_REG_BASE               (XMC_REG_BASE + 0x0140)
#define QSPI1_MEM_BASE                   ((uint32_t)0x90000000)
#define XMC_MEM_BASE                     ((uint32_t)0x60000000)
#define PERIPH_BASE                      ((uint32_t)0x40000000)
#define SRAM_BB_BASE                     ((uint32_t)0x22000000)
#define PERIPH_BB_BASE                   ((uint32_t)0x42000000)
#define SRAM_BASE                        ((uint32_t)0x20000000)
#define USD_BASE                         ((uint32_t)0x1FFFC000)
#define FLASH_BASE                       ((uint32_t)0x08000000)

#define DEBUG_BASE                       ((uint32_t)0xE0042000)

#define APB1PERIPH_BASE                  (PERIPH_BASE)
#define APB2PERIPH_BASE                  (PERIPH_BASE + 0x10000)
#define AHBPERIPH1_BASE                  (PERIPH_BASE + 0x20000)
#define AHBPERIPH2_BASE                  (PERIPH_BASE + 0x10000000)

#if defined (AT32F435xx)
/* apb1 bus base address */
#define UART8_BASE                       (APB1PERIPH_BASE + 0x7C00)
#define UART7_BASE                       (APB1PERIPH_BASE + 0x7800)
#define DAC_BASE                         (APB1PERIPH_BASE + 0x7400)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
#define CAN2_BASE                        (APB1PERIPH_BASE + 0x6800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define I2C3_BASE                        (APB1PERIPH_BASE + 0x5C00)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define UART5_BASE                       (APB1PERIPH_BASE + 0x5000)
#define UART4_BASE                       (APB1PERIPH_BASE + 0x4C00)
#define USART3_BASE                      (APB1PERIPH_BASE + 0x4800)
#define USART2_BASE                      (APB1PERIPH_BASE + 0x4400)
#define SPI3_BASE                        (APB1PERIPH_BASE + 0x3C00)
#define SPI2_BASE                        (APB1PERIPH_BASE + 0x3800)
#define WDT_BASE                         (APB1PERIPH_BASE + 0x3000)
#define WWDT_BASE                        (APB1PERIPH_BASE + 0x2C00)
#define ERTC_BASE                        (APB1PERIPH_BASE + 0x2800)
#define TMR14_BASE                       (APB1PERIPH_BASE + 0x2000)
#define TMR13_BASE                       (APB1PERIPH_BASE + 0x1C00)
#define TMR12_BASE                       (APB1PERIPH_BASE + 0x1800)
#define TMR7_BASE                        (APB1PERIPH_BASE + 0x1400)
#define TMR6_BASE                        (APB1PERIPH_BASE + 0x1000)
#define TMR5_BASE                        (APB1PERIPH_BASE + 0x0C00)
#define TMR4_BASE                        (APB1PERIPH_BASE + 0x0800)
#define TMR3_BASE                        (APB1PERIPH_BASE + 0x0400)
#define TMR2_BASE                        (APB1PERIPH_BASE + 0x0000)
/* apb2 bus base address */
#define I2S2EXT_BASE                     (APB2PERIPH_BASE + 0x7800)
#define I2S3EXT_BASE                     (APB2PERIPH_BASE + 0x7C00)
#define ACC_BASE                         (APB2PERIPH_BASE + 0x7400)
#define TMR20_BASE                       (APB2PERIPH_BASE + 0x4C00)
#define TMR11_BASE                       (APB2PERIPH_BASE + 0x4800)
#define TMR10_BASE                       (APB2PERIPH_BASE + 0x4400)
#define TMR9_BASE                        (APB2PERIPH_BASE + 0x4000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x3C00)
#define SCFG_BASE                        (APB2PERIPH_BASE + 0x3800)
#define SPI4_BASE                        (APB2PERIPH_BASE + 0x3400)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE                        (APB2PERIPH_BASE + 0x2100)
#define ADC3_BASE                        (APB2PERIPH_BASE + 0x2200)
#define ADCCOM_BASE                      (APB2PERIPH_BASE + 0x2300)
#define USART6_BASE                      (APB2PERIPH_BASE + 0x1400)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x1000)
#define TMR8_BASE                        (APB2PERIPH_BASE + 0x0400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x0000)
/* ahb bus base address */
#define OTGFS2_BASE                      (AHBPERIPH1_BASE + 0x20000)
#define SDIO1_BASE                       (AHBPERIPH1_BASE + 0xC400)
#define GPIOH_BASE                       (AHBPERIPH1_BASE + 0x1C00)
#define GPIOG_BASE                       (AHBPERIPH1_BASE + 0x1800)
#define GPIOF_BASE                       (AHBPERIPH1_BASE + 0x1400)
#define GPIOE_BASE                       (AHBPERIPH1_BASE + 0x1000)
#define GPIOD_BASE                       (AHBPERIPH1_BASE + 0x0C00)
#define GPIOC_BASE                       (AHBPERIPH1_BASE + 0x0800)
#define GPIOB_BASE                       (AHBPERIPH1_BASE + 0x0400)
#define GPIOA_BASE                       (AHBPERIPH1_BASE + 0x0000)

#define DMA1_BASE                        (AHBPERIPH1_BASE + 0x6400)
#define DMA1_CHANNEL1_BASE               (DMA1_BASE + 0x0008)
#define DMA1_CHANNEL2_BASE               (DMA1_BASE + 0x001C)
#define DMA1_CHANNEL3_BASE               (DMA1_BASE + 0x0030)
#define DMA1_CHANNEL4_BASE               (DMA1_BASE + 0x0044)
#define DMA1_CHANNEL5_BASE               (DMA1_BASE + 0x0058)
#define DMA1_CHANNEL6_BASE               (DMA1_BASE + 0x006C)
#define DMA1_CHANNEL7_BASE               (DMA1_BASE + 0x0080)

#define DMA1MUX_BASE                     (DMA1_BASE + 0x0104)
#define DMA1MUX_CHANNEL1_BASE            (DMA1MUX_BASE)
#define DMA1MUX_CHANNEL2_BASE            (DMA1MUX_BASE + 0x0004)
#define DMA1MUX_CHANNEL3_BASE            (DMA1MUX_BASE + 0x0008)
#define DMA1MUX_CHANNEL4_BASE            (DMA1MUX_BASE + 0x000C)
#define DMA1MUX_CHANNEL5_BASE            (DMA1MUX_BASE + 0x0010)
#define DMA1MUX_CHANNEL6_BASE            (DMA1MUX_BASE + 0x0014)
#define DMA1MUX_CHANNEL7_BASE            (DMA1MUX_BASE + 0x0018)

#define DMA1MUX_GENERATOR1_BASE          (DMA1_BASE + 0x0120)
#define DMA1MUX_GENERATOR2_BASE          (DMA1_BASE + 0x0124)
#define DMA1MUX_GENERATOR3_BASE          (DMA1_BASE + 0x0128)
#define DMA1MUX_GENERATOR4_BASE          (DMA1_BASE + 0x012C)

#define DMA2_BASE                        (AHBPERIPH1_BASE + 0x6600)
#define DMA2_CHANNEL1_BASE               (DMA2_BASE + 0x0008)
#define DMA2_CHANNEL2_BASE               (DMA2_BASE + 0x001C)
#define DMA2_CHANNEL3_BASE               (DMA2_BASE + 0x0030)
#define DMA2_CHANNEL4_BASE               (DMA2_BASE + 0x0044)
#define DMA2_CHANNEL5_BASE               (DMA2_BASE + 0x0058)
#define DMA2_CHANNEL6_BASE               (DMA2_BASE + 0x006C)
#define DMA2_CHANNEL7_BASE               (DMA2_BASE + 0x0080)

#define DMA2MUX_BASE                     (DMA2_BASE + 0x0104)
#define DMA2MUX_CHANNEL1_BASE            (DMA2MUX_BASE)
#define DMA2MUX_CHANNEL2_BASE            (DMA2MUX_BASE + 0x0004)
#define DMA2MUX_CHANNEL3_BASE            (DMA2MUX_BASE + 0x0008)
#define DMA2MUX_CHANNEL4_BASE            (DMA2MUX_BASE + 0x000C)
#define DMA2MUX_CHANNEL5_BASE            (DMA2MUX_BASE + 0x0010)
#define DMA2MUX_CHANNEL6_BASE            (DMA2MUX_BASE + 0x0014)
#define DMA2MUX_CHANNEL7_BASE            (DMA2MUX_BASE + 0x0018)

#define DMA2MUX_GENERATOR1_BASE          (DMA2_BASE + 0x0120)
#define DMA2MUX_GENERATOR2_BASE          (DMA2_BASE + 0x0124)
#define DMA2MUX_GENERATOR3_BASE          (DMA2_BASE + 0x0128)
#define DMA2MUX_GENERATOR4_BASE          (DMA2_BASE + 0x012C)

#define EDMA_BASE                        (AHBPERIPH1_BASE + 0x6000)
#define EDMA_STREAM1_BASE                (EDMA_BASE + 0x0010)
#define EDMA_STREAM2_BASE                (EDMA_BASE + 0x0028)
#define EDMA_STREAM3_BASE                (EDMA_BASE + 0x0040)
#define EDMA_STREAM4_BASE                (EDMA_BASE + 0x0058)
#define EDMA_STREAM5_BASE                (EDMA_BASE + 0x0070)
#define EDMA_STREAM6_BASE                (EDMA_BASE + 0x0088)
#define EDMA_STREAM7_BASE                (EDMA_BASE + 0x00A0)
#define EDMA_STREAM8_BASE                (EDMA_BASE + 0x00B8)

#define EDMA_2D_BASE                     (EDMA_BASE + 0x00F4)
#define EDMA_STREAM1_2D_BASE             (EDMA_2D_BASE + 0x0004)
#define EDMA_STREAM2_2D_BASE             (EDMA_2D_BASE + 0x000C)
#define EDMA_STREAM3_2D_BASE             (EDMA_2D_BASE + 0x0014)
#define EDMA_STREAM4_2D_BASE             (EDMA_2D_BASE + 0x001C)
#define EDMA_STREAM5_2D_BASE             (EDMA_2D_BASE + 0x0024)
#define EDMA_STREAM6_2D_BASE             (EDMA_2D_BASE + 0x002C)
#define EDMA_STREAM7_2D_BASE             (EDMA_2D_BASE + 0x0034)
#define EDMA_STREAM8_2D_BASE             (EDMA_2D_BASE + 0x003C)

#define EDMA_LL_BASE                     (EDMA_BASE + 0x00D0)
#define EDMA_STREAM1_LL_BASE             (EDMA_LL_BASE + 0x0004)
#define EDMA_STREAM2_LL_BASE             (EDMA_LL_BASE + 0x0008)
#define EDMA_STREAM3_LL_BASE             (EDMA_LL_BASE + 0x000C)
#define EDMA_STREAM4_LL_BASE             (EDMA_LL_BASE + 0x0010)
#define EDMA_STREAM5_LL_BASE             (EDMA_LL_BASE + 0x0014)
#define EDMA_STREAM6_LL_BASE             (EDMA_LL_BASE + 0x0018)
#define EDMA_STREAM7_LL_BASE             (EDMA_LL_BASE + 0x001C)
#define EDMA_STREAM8_LL_BASE             (EDMA_LL_BASE + 0x0020)

#define EDMAMUX_BASE                     (EDMA_BASE + 0x0140)
#define EDMAMUX_CHANNEL1_BASE            (EDMAMUX_BASE)
#define EDMAMUX_CHANNEL2_BASE            (EDMAMUX_BASE + 0x0004)
#define EDMAMUX_CHANNEL3_BASE            (EDMAMUX_BASE + 0x0008)
#define EDMAMUX_CHANNEL4_BASE            (EDMAMUX_BASE + 0x000C)
#define EDMAMUX_CHANNEL5_BASE            (EDMAMUX_BASE + 0x0010)
#define EDMAMUX_CHANNEL6_BASE            (EDMAMUX_BASE + 0x0014)
#define EDMAMUX_CHANNEL7_BASE            (EDMAMUX_BASE + 0x0018)
#define EDMAMUX_CHANNEL8_BASE            (EDMAMUX_BASE + 0x001C)

#define EDMAMUX_GENERATOR1_BASE          (EDMA_BASE + 0x0160)
#define EDMAMUX_GENERATOR2_BASE          (EDMA_BASE + 0x0164)
#define EDMAMUX_GENERATOR3_BASE          (EDMA_BASE + 0x0168)
#define EDMAMUX_GENERATOR4_BASE          (EDMA_BASE + 0x016C)

#define FLASH_REG_BASE                   (AHBPERIPH1_BASE + 0x3C00)
#define CRM_BASE                         (AHBPERIPH1_BASE + 0x3800)
#define CRC_BASE                         (AHBPERIPH1_BASE + 0x3000)
#define SDIO2_BASE                       (AHBPERIPH2_BASE + 0x61000)
#define DVP_BASE                         (AHBPERIPH2_BASE + 0x50000)
#define OTGFS1_BASE                      (AHBPERIPH2_BASE + 0x00000)
#endif

#if defined (AT32F437xx)
/* apb1 bus base address */
#define UART8_BASE                       (APB1PERIPH_BASE + 0x7C00)
#define UART7_BASE                       (APB1PERIPH_BASE + 0x7800)
#define DAC_BASE                         (APB1PERIPH_BASE + 0x7400)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
#define CAN2_BASE                        (APB1PERIPH_BASE + 0x6800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define I2C3_BASE                        (APB1PERIPH_BASE + 0x5C00)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define UART5_BASE                       (APB1PERIPH_BASE + 0x5000)
#define UART4_BASE                       (APB1PERIPH_BASE + 0x4C00)
#define USART3_BASE                      (APB1PERIPH_BASE + 0x4800)
#define USART2_BASE                      (APB1PERIPH_BASE + 0x4400)
#define SPI3_BASE                        (APB1PERIPH_BASE + 0x3C00)
#define SPI2_BASE                        (APB1PERIPH_BASE + 0x3800)
#define WDT_BASE                         (APB1PERIPH_BASE + 0x3000)
#define WWDT_BASE                        (APB1PERIPH_BASE + 0x2C00)
#define ERTC_BASE                        (APB1PERIPH_BASE + 0x2800)
#define TMR14_BASE                       (APB1PERIPH_BASE + 0x2000)
#define TMR13_BASE                       (APB1PERIPH_BASE + 0x1C00)
#define TMR12_BASE                       (APB1PERIPH_BASE + 0x1800)
#define TMR7_BASE                        (APB1PERIPH_BASE + 0x1400)
#define TMR6_BASE                        (APB1PERIPH_BASE + 0x1000)
#define TMR5_BASE                        (APB1PERIPH_BASE + 0x0C00)
#define TMR4_BASE                        (APB1PERIPH_BASE + 0x0800)
#define TMR3_BASE                        (APB1PERIPH_BASE + 0x0400)
#define TMR2_BASE                        (APB1PERIPH_BASE + 0x0000)
/* apb2 bus base address */
#define I2S2EXT_BASE                     (APB2PERIPH_BASE + 0x7800)
#define I2S3EXT_BASE                     (APB2PERIPH_BASE + 0x7C00)
#define ACC_BASE                         (APB2PERIPH_BASE + 0x7400)
#define TMR20_BASE                       (APB2PERIPH_BASE + 0x4C00)
#define TMR11_BASE                       (APB2PERIPH_BASE + 0x4800)
#define TMR10_BASE                       (APB2PERIPH_BASE + 0x4400)
#define TMR9_BASE                        (APB2PERIPH_BASE + 0x4000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x3C00)
#define SCFG_BASE                        (APB2PERIPH_BASE + 0x3800)
#define SPI4_BASE                        (APB2PERIPH_BASE + 0x3400)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE                        (APB2PERIPH_BASE + 0x2100)
#define ADC3_BASE                        (APB2PERIPH_BASE + 0x2200)
#define ADCCOM_BASE                      (APB2PERIPH_BASE + 0x2300)
#define USART6_BASE                      (APB2PERIPH_BASE + 0x1400)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x1000)
#define TMR8_BASE                        (APB2PERIPH_BASE + 0x0400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x0000)
/* ahb bus base address */
#define OTGFS2_BASE                      (AHBPERIPH1_BASE + 0x20000)
#define SDIO1_BASE                       (AHBPERIPH1_BASE + 0xC400)
#define EMAC_BASE                        (AHBPERIPH1_BASE + 0x8000)
#define GPIOH_BASE                       (AHBPERIPH1_BASE + 0x1C00)
#define GPIOG_BASE                       (AHBPERIPH1_BASE + 0x1800)
#define GPIOF_BASE                       (AHBPERIPH1_BASE + 0x1400)
#define GPIOE_BASE                       (AHBPERIPH1_BASE + 0x1000)
#define GPIOD_BASE                       (AHBPERIPH1_BASE + 0x0C00)
#define GPIOC_BASE                       (AHBPERIPH1_BASE + 0x0800)
#define GPIOB_BASE                       (AHBPERIPH1_BASE + 0x0400)
#define GPIOA_BASE                       (AHBPERIPH1_BASE + 0x0000)

#define DMA1_BASE                        (AHBPERIPH1_BASE + 0x6400)
#define DMA1_CHANNEL1_BASE               (DMA1_BASE + 0x0008)
#define DMA1_CHANNEL2_BASE               (DMA1_BASE + 0x001C)
#define DMA1_CHANNEL3_BASE               (DMA1_BASE + 0x0030)
#define DMA1_CHANNEL4_BASE               (DMA1_BASE + 0x0044)
#define DMA1_CHANNEL5_BASE               (DMA1_BASE + 0x0058)
#define DMA1_CHANNEL6_BASE               (DMA1_BASE + 0x006C)
#define DMA1_CHANNEL7_BASE               (DMA1_BASE + 0x0080)

#define DMA1MUX_BASE                     (DMA1_BASE + 0x0104)
#define DMA1MUX_CHANNEL1_BASE            (DMA1MUX_BASE)
#define DMA1MUX_CHANNEL2_BASE            (DMA1MUX_BASE + 0x0004)
#define DMA1MUX_CHANNEL3_BASE            (DMA1MUX_BASE + 0x0008)
#define DMA1MUX_CHANNEL4_BASE            (DMA1MUX_BASE + 0x000C)
#define DMA1MUX_CHANNEL5_BASE            (DMA1MUX_BASE + 0x0010)
#define DMA1MUX_CHANNEL6_BASE            (DMA1MUX_BASE + 0x0014)
#define DMA1MUX_CHANNEL7_BASE            (DMA1MUX_BASE + 0x0018)

#define DMA1MUX_GENERATOR1_BASE          (DMA1_BASE + 0x0120)
#define DMA1MUX_GENERATOR2_BASE          (DMA1_BASE + 0x0124)
#define DMA1MUX_GENERATOR3_BASE          (DMA1_BASE + 0x0128)
#define DMA1MUX_GENERATOR4_BASE          (DMA1_BASE + 0x012C)

#define DMA2_BASE                        (AHBPERIPH1_BASE + 0x6600)
#define DMA2_CHANNEL1_BASE               (DMA2_BASE + 0x0008)
#define DMA2_CHANNEL2_BASE               (DMA2_BASE + 0x001C)
#define DMA2_CHANNEL3_BASE               (DMA2_BASE + 0x0030)
#define DMA2_CHANNEL4_BASE               (DMA2_BASE + 0x0044)
#define DMA2_CHANNEL5_BASE               (DMA2_BASE + 0x0058)
#define DMA2_CHANNEL6_BASE               (DMA2_BASE + 0x006C)
#define DMA2_CHANNEL7_BASE               (DMA2_BASE + 0x0080)

#define DMA2MUX_BASE                     (DMA2_BASE + 0x0104)
#define DMA2MUX_CHANNEL1_BASE            (DMA2MUX_BASE)
#define DMA2MUX_CHANNEL2_BASE            (DMA2MUX_BASE + 0x0004)
#define DMA2MUX_CHANNEL3_BASE            (DMA2MUX_BASE + 0x0008)
#define DMA2MUX_CHANNEL4_BASE            (DMA2MUX_BASE + 0x000C)
#define DMA2MUX_CHANNEL5_BASE            (DMA2MUX_BASE + 0x0010)
#define DMA2MUX_CHANNEL6_BASE            (DMA2MUX_BASE + 0x0014)
#define DMA2MUX_CHANNEL7_BASE            (DMA2MUX_BASE + 0x0018)

#define DMA2MUX_GENERATOR1_BASE          (DMA2_BASE + 0x0120)
#define DMA2MUX_GENERATOR2_BASE          (DMA2_BASE + 0x0124)
#define DMA2MUX_GENERATOR3_BASE          (DMA2_BASE + 0x0128)
#define DMA2MUX_GENERATOR4_BASE          (DMA2_BASE + 0x012C)

#define EDMA_BASE                        (AHBPERIPH1_BASE + 0x6000)
#define EDMA_STREAM1_BASE                (EDMA_BASE + 0x0010)
#define EDMA_STREAM2_BASE                (EDMA_BASE + 0x0028)
#define EDMA_STREAM3_BASE                (EDMA_BASE + 0x0040)
#define EDMA_STREAM4_BASE                (EDMA_BASE + 0x0058)
#define EDMA_STREAM5_BASE                (EDMA_BASE + 0x0070)
#define EDMA_STREAM6_BASE                (EDMA_BASE + 0x0088)
#define EDMA_STREAM7_BASE                (EDMA_BASE + 0x00A0)
#define EDMA_STREAM8_BASE                (EDMA_BASE + 0x00B8)

#define EDMA_2D_BASE                     (EDMA_BASE + 0x00F4)
#define EDMA_STREAM1_2D_BASE             (EDMA_2D_BASE + 0x0004)
#define EDMA_STREAM2_2D_BASE             (EDMA_2D_BASE + 0x000C)
#define EDMA_STREAM3_2D_BASE             (EDMA_2D_BASE + 0x0014)
#define EDMA_STREAM4_2D_BASE             (EDMA_2D_BASE + 0x001C)
#define EDMA_STREAM5_2D_BASE             (EDMA_2D_BASE + 0x0024)
#define EDMA_STREAM6_2D_BASE             (EDMA_2D_BASE + 0x002C)
#define EDMA_STREAM7_2D_BASE             (EDMA_2D_BASE + 0x0034)
#define EDMA_STREAM8_2D_BASE             (EDMA_2D_BASE + 0x003C)

#define EDMA_LL_BASE                     (EDMA_BASE + 0x00D0)
#define EDMA_STREAM1_LL_BASE             (EDMA_LL_BASE + 0x0004)
#define EDMA_STREAM2_LL_BASE             (EDMA_LL_BASE + 0x0008)
#define EDMA_STREAM3_LL_BASE             (EDMA_LL_BASE + 0x000C)
#define EDMA_STREAM4_LL_BASE             (EDMA_LL_BASE + 0x0010)
#define EDMA_STREAM5_LL_BASE             (EDMA_LL_BASE + 0x0014)
#define EDMA_STREAM6_LL_BASE             (EDMA_LL_BASE + 0x0018)
#define EDMA_STREAM7_LL_BASE             (EDMA_LL_BASE + 0x001C)
#define EDMA_STREAM8_LL_BASE             (EDMA_LL_BASE + 0x0020)

#define EDMAMUX_BASE                     (EDMA_BASE + 0x0140)
#define EDMAMUX_CHANNEL1_BASE            (EDMAMUX_BASE)
#define EDMAMUX_CHANNEL2_BASE            (EDMAMUX_BASE + 0x0004)
#define EDMAMUX_CHANNEL3_BASE            (EDMAMUX_BASE + 0x0008)
#define EDMAMUX_CHANNEL4_BASE            (EDMAMUX_BASE + 0x000C)
#define EDMAMUX_CHANNEL5_BASE            (EDMAMUX_BASE + 0x0010)
#define EDMAMUX_CHANNEL6_BASE            (EDMAMUX_BASE + 0x0014)
#define EDMAMUX_CHANNEL7_BASE            (EDMAMUX_BASE + 0x0018)
#define EDMAMUX_CHANNEL8_BASE            (EDMAMUX_BASE + 0x001C)

#define EDMAMUX_GENERATOR1_BASE          (EDMA_BASE + 0x0160)
#define EDMAMUX_GENERATOR2_BASE          (EDMA_BASE + 0x0164)
#define EDMAMUX_GENERATOR3_BASE          (EDMA_BASE + 0x0168)
#define EDMAMUX_GENERATOR4_BASE          (EDMA_BASE + 0x016C)

#define FLASH_REG_BASE                   (AHBPERIPH1_BASE + 0x3C00)
#define CRM_BASE                         (AHBPERIPH1_BASE + 0x3800)
#define CRC_BASE                         (AHBPERIPH1_BASE + 0x3000)
#define SDIO2_BASE                       (AHBPERIPH2_BASE + 0x61000)
#define DVP_BASE                         (AHBPERIPH2_BASE + 0x50000)
#define OTGFS1_BASE                      (AHBPERIPH2_BASE + 0x00000)

#define EMAC_MAC_BASE                    (EMAC_BASE)
#define EMAC_MMC_BASE                    (EMAC_BASE + 0x0100)
#define EMAC_PTP_BASE                    (EMAC_BASE + 0x0700)
#define EMAC_DMA_BASE                    (EMAC_BASE + 0x1000)
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#include "at32f435_437_def.h"
#include "at32f435_437_conf.h"

#ifdef __cplusplus
}
#endif

#endif
