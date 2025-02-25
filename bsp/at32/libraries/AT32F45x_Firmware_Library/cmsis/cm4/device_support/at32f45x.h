/**
  **************************************************************************
  * @file     at32f45x.h
  * @brief    at32f45x header file
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

#ifndef __AT32F45x_H
#define __AT32F45x_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__CC_ARM)
 #pragma anon_unions
#endif

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F45x
  * @{
  */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * tip: to avoid modifying this file each time you need to switch between these
  *      devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined (AT32F455CCT7) && !defined (AT32F455CET7) && !defined (AT32F455CCU7) && \
    !defined (AT32F455CEU7) && !defined (AT32F455RCT7) && !defined (AT32F455RET7) && \
    !defined (AT32F455VCT7) && !defined (AT32F455VET7) && !defined (AT32F455ZCT7) && \
    !defined (AT32F455ZET7) && \
    !defined (AT32F456CCT7) && !defined (AT32F456CET7) && !defined (AT32F456CCU7) && \
    !defined (AT32F456CEU7) && !defined (AT32F456RCT7) && !defined (AT32F456RET7) && \
    !defined (AT32F456VCT7) && !defined (AT32F456VET7) && !defined (AT32F456ZCT7) && \
    !defined (AT32F456ZET7) && \
    !defined (AT32F457RCT7) && !defined (AT32F457RET7) && !defined (AT32F457VCT7) && \
    !defined (AT32F457VET7) && !defined (AT32F457ZCT7) && !defined (AT32F457ZET7)

    #error "Please select first the target device used in your application (in at32f45x.h file)"
#endif

#if defined (AT32F455CCT7) || defined (AT32F455CET7) || defined (AT32F455CCU7) || \
    defined (AT32F455CEU7) || defined (AT32F455RCT7) || defined (AT32F455RET7) || \
    defined (AT32F455VCT7) || defined (AT32F455VET7) || defined (AT32F455ZCT7) || \
    defined (AT32F455ZET7)

    #define AT32F455xx
#endif

#if defined (AT32F456CCT7) || defined (AT32F456CET7) || defined (AT32F456CCU7) || \
    defined (AT32F456CEU7) || defined (AT32F456RCT7) || defined (AT32F456RET7) || \
    defined (AT32F456VCT7) || defined (AT32F456VET7) || defined (AT32F456ZCT7) || \
    defined (AT32F456ZET7)

    #define AT32F456xx
#endif

#if defined (AT32F457RCT7) || defined (AT32F457RET7) || defined (AT32F457VCT7) || \
    defined (AT32F457VET7) || defined (AT32F457ZCT7) || defined (AT32F457ZET7)

    #define AT32F457xx
#endif

/**
  * define with package
  */
#if defined (AT32F455CCT7) || defined (AT32F455CET7) || defined (AT32F455CCU7) || \
    defined (AT32F455CEU7)

    #define AT32F455Cx
#endif

#if defined (AT32F455RCT7) || defined (AT32F455RET7)

    #define AT32F455Rx
#endif

#if defined (AT32F455VCT7) || defined (AT32F455VET7)

    #define AT32F455Vx
#endif

#if defined (AT32F455ZCT7) || defined (AT32F455ZET7)

    #define AT32F455Zx
#endif

#if defined (AT32F456CCT7) || defined (AT32F456CET7) || defined (AT32F456CCU7) || \
    defined (AT32F456CEU7)

    #define AT32F456Cx
#endif

#if defined (AT32F456RCT7) || defined (AT32F456RET7)

    #define AT32F456Rx
#endif

#if defined (AT32F456VCT7) || defined (AT32F456VET7)

    #define AT32F456Vx
#endif

#if defined (AT32F456ZCT7) || defined (AT32F456ZET7)

    #define AT32F456Zx
#endif

#if defined (AT32F457RCT7) || defined (AT32F457RET7)

    #define AT32F457Rx
#endif

#if defined (AT32F457VCT7) || defined (AT32F457VET7)

    #define AT32F457Vx
#endif

#if defined (AT32F457ZCT7) || defined (AT32F457ZET7)

    #define AT32F457Zx
#endif

/**
  * define with memory density
  */
#if defined (AT32F455CCT7) || defined (AT32F455CCU7) || defined (AT32F455RCT7) || \
    defined (AT32F455VCT7) || defined (AT32F455ZCT7)

    #define AT32F455xC
#endif

#if defined (AT32F455CET7) || defined (AT32F455CEU7) || defined (AT32F455RET7) || \
    defined (AT32F455VET7) || defined (AT32F455ZET7)

    #define AT32F455xE
#endif

#if defined (AT32F456CCT7) || defined (AT32F456CCU7) || defined (AT32F456RCT7) || \
    defined (AT32F456VCT7) || defined (AT32F456ZCT7)

    #define AT32F456xC
#endif

#if defined (AT32F456CET7) || defined (AT32F456CEU7) || defined (AT32F456RET7) || \
    defined (AT32F456VET7) || defined (AT32F456ZET7)

    #define AT32F456xE
#endif

#if defined (AT32F457RCT7) || defined (AT32F457VCT7) || defined (AT32F457ZCT7)

    #define AT32F457xC
#endif

#if defined (AT32F457RET7) || defined (AT32F457VET7) || defined (AT32F457ZET7)

    #define AT32F457xE
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
  * @brief at32f45x standard peripheral library version number
  */
#define __AT32F45x_LIBRARY_VERSION_MAJOR    (0x02) /*!< [31:24] major version */
#define __AT32F45x_LIBRARY_VERSION_MIDDLE   (0x00) /*!< [23:16] middle version */
#define __AT32F45x_LIBRARY_VERSION_MINOR    (0x00) /*!< [15:8]  minor version */
#define __AT32F45x_LIBRARY_VERSION_RC       (0x00) /*!< [7:0]  release candidate */
#define __AT32F45x_LIBRARY_VERSION          ((__AT32F45x_LIBRARY_VERSION_MAJOR << 24)  | \
                                             (__AT32F45x_LIBRARY_VERSION_MIDDLE << 16) | \
                                             (__AT32F45x_LIBRARY_VERSION_MINOR << 8)   | \
                                             (__AT32F45x_LIBRARY_VERSION_RC))

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
  * @brief at32f45x interrupt number definition, according to the selected device
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
    DMA1_Channel1_IRQn          = 11,     /*!< dma1 channel 1 global interrupt                      */
    DMA1_Channel2_IRQn          = 12,     /*!< dma1 channel 2 global interrupt                      */
    DMA1_Channel3_IRQn          = 13,     /*!< dma1 channel 3 global interrupt                      */
    DMA1_Channel4_IRQn          = 14,     /*!< dma1 channel 4 global interrupt                      */
    DMA1_Channel5_IRQn          = 15,     /*!< dma1 channel 5 global interrupt                      */
    DMA1_Channel6_IRQn          = 16,     /*!< dma1 channel 6 global interrupt                      */
    DMA1_Channel7_IRQn          = 17,     /*!< dma1 channel 7 global interrupt                      */

#if defined (AT32F455xx)
    ADC1_2_IRQn                 = 18,     /*!< adc1 and adc2 global interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< can1 tx interrupts                                   */
    CAN1_RX_IRQn                = 20,     /*!< can1 rx interrupts                                   */
    CAN1_STAT_IRQn              = 21,     /*!< can1 state interrupt                                 */
    CAN1_ERR_IRQn               = 22,     /*!< can1 error interrupt                                 */
    EXINT9_5_IRQn               = 23,     /*!< external line[9:5] interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< tmr1 brake and tmr9 interrupt                        */
    TMR1_OVF_TMR10_IRQn         = 25,     /*!< tmr1 overflow and tmr10 interrupt                    */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< tmr1 trigger and hall and tmr11 interrupt            */
    TMR1_CH_IRQn                = 27,     /*!< tmr1 channel interrupt                               */
    TMR2_GLOBAL_IRQn            = 28,     /*!< tmr2 global interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< tmr3 global interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< tmr4 global interrupt                                */
    I2C1_EVT_IRQn               = 31,     /*!< i2c1 event interrupt                                 */
    I2C1_ERR_IRQn               = 32,     /*!< i2c1 error interrupt                                 */
    I2C2_EVT_IRQn               = 33,     /*!< i2c2 event interrupt                                 */
    I2C2_ERR_IRQn               = 34,     /*!< i2c2 error interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< spi1 global interrupt                                */
    SPI2_I2S2EXT_IRQn           = 36,     /*!< spi2_i2s2ext global interrupt                        */
    USART1_IRQn                 = 37,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /*!< usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /*!< usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /*!< external line[15:10] interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ertc alarm through exint line interrupt              */
    OTGFS1_WKUP_IRQn            = 42,     /*!< otgfs1 wakeup from suspend through exint line interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< tmr8 brake and tmr12 interrupt                       */
    TMR8_OVF_TMR13_IRQn         = 44,     /*!< tmr8 overflow and tmr13 interrupt                    */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< tmr8 trigger and hall and tmr14 interrupt            */
    TMR8_CH_IRQn                = 46,     /*!< tmr8 channel interrupt                               */
    XMC_IRQn                    = 48,     /*!< xmc global interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< sdio global interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< tmr5 global interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< spi3_i2s3ext global interrupt                        */
    USART4_IRQn                 = 52,     /*!< usart4 global interrupt                              */
    USART5_IRQn                 = 53,     /*!< usart5 global interrupt                              */
    TMR6_DAC_GLOBAL_IRQn        = 54,     /*!< tmr6 and dac global interrupt                        */
    TMR7_GLOBAL_IRQn            = 55,     /*!< tmr7 global interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< dma2 channel 3 global interrupt                      */
    DMA2_Channel4_IRQn          = 59,     /*!< dma2 channel 4 global interrupt                      */
    DMA2_Channel5_IRQn          = 60,     /*!< dma2 channel 5 global interrupt                      */
    CAN2_TX_IRQn                = 63,     /*!< can2 tx interrupt                                    */
    CAN2_RX_IRQn                = 64,     /*!< can2 rx interrupt                                    */
    CAN2_STAT_IRQn              = 65,     /*!< can2 state interrupt                                 */
    CAN2_ERR_IRQn               = 66,     /*!< can2 error interrupt                                 */
    OTGFS1_IRQn                 = 67,     /*!< otgfs1 interrupt                                     */
    DMA2_Channel6_IRQn          = 68,     /*!< dma2 channel 6 global interrupt                      */
    DMA2_Channel7_IRQn          = 69,     /*!< dma2 channel 7 global interrupt                      */
    USART6_IRQn                 = 71,     /*!< usart6 interrupt                                     */
    I2C3_EVT_IRQn               = 72,     /*!< i2c3 event interrupt                                 */
    I2C3_ERR_IRQn               = 73,     /*!< i2c3 error interrupt                                 */
    CAN3_TX_IRQn                = 74,     /*!< can3 tx interrupt                                    */
    CAN3_RX_IRQn                = 75,     /*!< can3 rx interrupt                                    */
    CAN3_STAT_IRQn              = 76,     /*!< can3 state interrupt                                 */
    CAN3_ERR_IRQn               = 77,     /*!< can3 error interrupt                                 */
    AES_IRQn                    = 79,     /*!< aes interrupt                                        */
    TRNG_IRQn                   = 80,     /*!< trng interrupt                                       */
    FPU_IRQn                    = 81,     /*!< fpu interrupt                                        */
    USART7_IRQn                 = 82,     /*!< usart7 interrupt                                     */
    USART8_IRQn                 = 83,     /*!< usart8 interrupt                                     */
    SPI4_IRQn                   = 84,     /*!< spi4 global interrupt                                */
    I2SF5_IRQn                  = 85,     /*!< i2sf5 global interrupt                               */
    QSPI1_IRQn                  = 92,     /*!< qspi1 global interrupt                               */
    DMAMUX_IRQn                 = 94,     /*!< dmamux interrupt                                     */
    ACC_IRQn                    = 103,    /*!< acc interrupt                                        */
#endif

#if defined (AT32F456xx)
    ADC1_2_IRQn                 = 18,     /*!< adc1 and adc2 global interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< can1 tx interrupts                                   */
    CAN1_RX_IRQn                = 20,     /*!< can1 rx interrupts                                   */
    CAN1_STAT_IRQn              = 21,     /*!< can1 state interrupt                                 */
    CAN1_ERR_IRQn               = 22,     /*!< can1 error interrupt                                 */
    EXINT9_5_IRQn               = 23,     /*!< external line[9:5] interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< tmr1 brake and tmr9 interrupt                        */
    TMR1_OVF_TMR10_IRQn         = 25,     /*!< tmr1 overflow and tmr10 interrupt                    */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< tmr1 trigger and hall and tmr11 interrupt            */
    TMR1_CH_IRQn                = 27,     /*!< tmr1 channel interrupt                               */
    TMR2_GLOBAL_IRQn            = 28,     /*!< tmr2 global interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< tmr3 global interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< tmr4 global interrupt                                */
    I2C1_EVT_IRQn               = 31,     /*!< i2c1 event interrupt                                 */
    I2C1_ERR_IRQn               = 32,     /*!< i2c1 error interrupt                                 */
    I2C2_EVT_IRQn               = 33,     /*!< i2c2 event interrupt                                 */
    I2C2_ERR_IRQn               = 34,     /*!< i2c2 error interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< spi1 global interrupt                                */
    SPI2_I2S2EXT_IRQn           = 36,     /*!< spi2_i2s2ext global interrupt                        */
    USART1_IRQn                 = 37,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /*!< usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /*!< usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /*!< external line[15:10] interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ertc alarm through exint line interrupt              */
    OTGFS1_WKUP_IRQn            = 42,     /*!< otgfs1 wakeup from suspend through exint line interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< tmr8 brake and tmr12 interrupt                       */
    TMR8_OVF_TMR13_IRQn         = 44,     /*!< tmr8 overflow and tmr13 interrupt                    */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< tmr8 trigger and hall and tmr14 interrupt            */
    TMR8_CH_IRQn                = 46,     /*!< tmr8 channel interrupt                               */
    XMC_IRQn                    = 48,     /*!< xmc global interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< sdio global interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< tmr5 global interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< spi3_i2s3ext global interrupt                        */
    USART4_IRQn                 = 52,     /*!< usart4 global interrupt                              */
    USART5_IRQn                 = 53,     /*!< usart5 global interrupt                              */
    TMR6_DAC_GLOBAL_IRQn        = 54,     /*!< tmr6 and dac global interrupt                        */
    TMR7_GLOBAL_IRQn            = 55,     /*!< tmr7 global interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< dma2 channel 3 global interrupt                      */
    DMA2_Channel4_IRQn          = 59,     /*!< dma2 channel 4 global interrupt                      */
    DMA2_Channel5_IRQn          = 60,     /*!< dma2 channel 5 global interrupt                      */
    CAN2_TX_IRQn                = 63,     /*!< can2 tx interrupt                                    */
    CAN2_RX_IRQn                = 64,     /*!< can2 rx interrupt                                    */
    CAN2_STAT_IRQn              = 65,     /*!< can2 state interrupt                                 */
    CAN2_ERR_IRQn               = 66,     /*!< can2 error interrupt                                 */
    OTGFS1_IRQn                 = 67,     /*!< otgfs1 interrupt                                     */
    DMA2_Channel6_IRQn          = 68,     /*!< dma2 channel 6 global interrupt                      */
    DMA2_Channel7_IRQn          = 69,     /*!< dma2 channel 7 global interrupt                      */
    USART6_IRQn                 = 71,     /*!< usart6 interrupt                                     */
    I2C3_EVT_IRQn               = 72,     /*!< i2c3 event interrupt                                 */
    I2C3_ERR_IRQn               = 73,     /*!< i2c3 error interrupt                                 */
    CAN3_TX_IRQn                = 74,     /*!< can3 tx interrupt                                    */
    CAN3_RX_IRQn                = 75,     /*!< can3 rx interrupt                                    */
    CAN3_STAT_IRQn              = 76,     /*!< can3 state interrupt                                 */
    CAN3_ERR_IRQn               = 77,     /*!< can3 error interrupt                                 */
    AES_IRQn                    = 79,     /*!< aes interrupt                                        */
    TRNG_IRQn                   = 80,     /*!< trng interrupt                                       */
    FPU_IRQn                    = 81,     /*!< fpu interrupt                                        */
    USART7_IRQn                 = 82,     /*!< usart7 interrupt                                     */
    USART8_IRQn                 = 83,     /*!< usart8 interrupt                                     */
    SPI4_IRQn                   = 84,     /*!< spi4 global interrupt                                */
    I2SF5_IRQn                  = 85,     /*!< i2sf5 global interrupt                               */
    QSPI1_IRQn                  = 92,     /*!< qspi1 global interrupt                               */
    DMAMUX_IRQn                 = 94,     /*!< dmamux interrupt                                     */
    ACC_IRQn                    = 103,    /*!< acc interrupt                                        */
#endif

#if defined (AT32F457xx)
    ADC1_2_IRQn                 = 18,     /*!< adc1 and adc2 global interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< can1 tx interrupts                                   */
    CAN1_RX_IRQn                = 20,     /*!< can1 rx interrupts                                   */
    CAN1_STAT_IRQn              = 21,     /*!< can1 state interrupt                                 */
    CAN1_ERR_IRQn               = 22,     /*!< can1 error interrupt                                 */
    EXINT9_5_IRQn               = 23,     /*!< external line[9:5] interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< tmr1 brake and tmr9 interrupt                        */
    TMR1_OVF_TMR10_IRQn         = 25,     /*!< tmr1 overflow and tmr10 interrupt                    */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< tmr1 trigger and hall and tmr11 interrupt            */
    TMR1_CH_IRQn                = 27,     /*!< tmr1 channel interrupt                               */
    TMR2_GLOBAL_IRQn            = 28,     /*!< tmr2 global interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< tmr3 global interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< tmr4 global interrupt                                */
    I2C1_EVT_IRQn               = 31,     /*!< i2c1 event interrupt                                 */
    I2C1_ERR_IRQn               = 32,     /*!< i2c1 error interrupt                                 */
    I2C2_EVT_IRQn               = 33,     /*!< i2c2 event interrupt                                 */
    I2C2_ERR_IRQn               = 34,     /*!< i2c2 error interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< spi1 global interrupt                                */
    SPI2_I2S2EXT_IRQn           = 36,     /*!< spi2_i2s2ext global interrupt                        */
    USART1_IRQn                 = 37,     /*!< usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /*!< usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /*!< usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /*!< external line[15:10] interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ertc alarm through exint line interrupt              */
    OTGFS1_WKUP_IRQn            = 42,     /*!< otgfs1 wakeup from suspend through exint line interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< tmr8 brake and tmr12 interrupt                       */
    TMR8_OVF_TMR13_IRQn         = 44,     /*!< tmr8 overflow and tmr13 interrupt                    */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< tmr8 trigger and hall and tmr14 interrupt            */
    TMR8_CH_IRQn                = 46,     /*!< tmr8 channel interrupt                               */
    XMC_IRQn                    = 48,     /*!< xmc global interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< sdio global interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< tmr5 global interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< spi3_i2s3ext global interrupt                        */
    USART4_IRQn                 = 52,     /*!< usart4 global interrupt                              */
    USART5_IRQn                 = 53,     /*!< usart5 global interrupt                              */
    TMR6_DAC_GLOBAL_IRQn        = 54,     /*!< tmr6 and dac global interrupt                        */
    TMR7_GLOBAL_IRQn            = 55,     /*!< tmr7 global interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< dma2 channel 3 global interrupt                      */
    DMA2_Channel4_IRQn          = 59,     /*!< dma2 channel 4 global interrupt                      */
    DMA2_Channel5_IRQn          = 60,     /*!< dma2 channel 5 global interrupt                      */
    EMAC_IRQn                   = 61,     /*!< emac interrupt                                       */
    EMAC_WKUP_IRQn              = 62,     /*!< emac wakeup interrupt                                */
    CAN2_TX_IRQn                = 63,     /*!< can2 tx interrupt                                    */
    CAN2_RX_IRQn                = 64,     /*!< can2 rx interrupt                                    */
    CAN2_STAT_IRQn              = 65,     /*!< can2 state interrupt                                 */
    CAN2_ERR_IRQn               = 66,     /*!< can2 error interrupt                                 */
    OTGFS1_IRQn                 = 67,     /*!< otgfs1 interrupt                                     */
    DMA2_Channel6_IRQn          = 68,     /*!< dma2 channel 6 global interrupt                      */
    DMA2_Channel7_IRQn          = 69,     /*!< dma2 channel 7 global interrupt                      */
    USART6_IRQn                 = 71,     /*!< usart6 interrupt                                     */
    I2C3_EVT_IRQn               = 72,     /*!< i2c3 event interrupt                                 */
    I2C3_ERR_IRQn               = 73,     /*!< i2c3 error interrupt                                 */
    CAN3_TX_IRQn                = 74,     /*!< can3 tx interrupt                                    */
    CAN3_RX_IRQn                = 75,     /*!< can3 rx interrupt                                    */
    CAN3_STAT_IRQn              = 76,     /*!< can3 state interrupt                                 */
    CAN3_ERR_IRQn               = 77,     /*!< can3 error interrupt                                 */
    AES_IRQn                    = 79,     /*!< aes interrupt                                        */
    TRNG_IRQn                   = 80,     /*!< trng interrupt                                       */
    FPU_IRQn                    = 81,     /*!< fpu interrupt                                        */
    USART7_IRQn                 = 82,     /*!< usart7 interrupt                                     */
    USART8_IRQn                 = 83,     /*!< usart8 interrupt                                     */
    SPI4_IRQn                   = 84,     /*!< spi4 global interrupt                                */
    I2SF5_IRQn                  = 85,     /*!< i2sf5 global interrupt                               */
    QSPI1_IRQn                  = 92,     /*!< qspi1 global interrupt                               */
    DMAMUX_IRQn                 = 94,     /*!< dmamux interrupt                                     */
    ACC_IRQn                    = 103,    /*!< acc interrupt                                        */
#endif

} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"
#include "system_at32f45x.h"
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
#define XMC_CARD_MEM_BASE                ((uint32_t)0xA8000000)
#define QSPI1_REG_BASE                   ((uint32_t)0xA0001000)
#define XMC_REG_BASE                     ((uint32_t)0xA0000000)
#define XMC_BANK1_REG_BASE               (XMC_REG_BASE + 0x0000)
#define XMC_BANK2_REG_BASE               (XMC_REG_BASE + 0x0060)
#define XMC_BANK3_REG_BASE               (XMC_REG_BASE + 0x0080)
#define XMC_BANK4_REG_BASE               (XMC_REG_BASE + 0x00A0)
#define XMC_SDRAM_REG_BASE               (XMC_REG_BASE + 0x0140)
#define XMC_MEM_BASE                     ((uint32_t)0x60000000)
#define QSPI1_REG_BASE                   ((uint32_t)0xA0001000)
#define QSPI1_MEM_BASE                   ((uint32_t)0x90000000)
#define PERIPH_BASE                      ((uint32_t)0x40000000)
#define SRAM_BB_BASE                     ((uint32_t)0x22000000)
#define PERIPH_BB_BASE                   ((uint32_t)0x42000000)
#define SRAM_BASE                        ((uint32_t)0x20000000)
#define USD_BASE                         ((uint32_t)0x1FFFF800)
#define OTP_DATA_BASE                    ((uint32_t)0x1FFFE400)
#define OTP_LOCK_BASE                    ((uint32_t)0x1FFFF500)
#define FLASH_BASE                       ((uint32_t)0x08000000)

#define DEBUG_BASE                       ((uint32_t)0xE0042000)

#define APB1PERIPH_BASE                  (PERIPH_BASE)
#define APB2PERIPH_BASE                  (PERIPH_BASE + 0x10000)
#define AHBPERIPH1_BASE                  (PERIPH_BASE + 0x20000)
#define AHBPERIPH2_BASE                  (PERIPH_BASE + 0x10000000)

#if defined (AT32F455xx)
/* apb1 bus base address */
#define USART8_BASE                      (APB1PERIPH_BASE + 0x7C00)
#define USART7_BASE                      (APB1PERIPH_BASE + 0x7800)
#define DAC_BASE                         (APB1PERIPH_BASE + 0x7400)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
#define CAN3_BASE                        (APB1PERIPH_BASE + 0x6C00)
#define CAN2_BASE                        (APB1PERIPH_BASE + 0x6800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define I2C3_BASE                        (APB1PERIPH_BASE + 0x5C00)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define USART5_BASE                      (APB1PERIPH_BASE + 0x5000)
#define USART4_BASE                      (APB1PERIPH_BASE + 0x4C00)
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
#define I2SF5_BASE                       (APB2PERIPH_BASE + 0x5000)
#define TMR11_BASE                       (APB2PERIPH_BASE + 0x4800)
#define TMR10_BASE                       (APB2PERIPH_BASE + 0x4400)
#define TMR9_BASE                        (APB2PERIPH_BASE + 0x4000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x3C00)
#define SCFG_BASE                        (APB2PERIPH_BASE + 0x3800)
#define SPI4_BASE                        (APB2PERIPH_BASE + 0x3400)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE                        (APB2PERIPH_BASE + 0x2100)
#define ADCCOM_BASE                      (APB2PERIPH_BASE + 0x2300)
#define USART6_BASE                      (APB2PERIPH_BASE + 0x1400)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x1000)
#define TMR8_BASE                        (APB2PERIPH_BASE + 0x0400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x0000)
/* ahb bus base address */
#define SDIO1_BASE                       (AHBPERIPH1_BASE + 0x4C00)
#define GPIOH_BASE                       (AHBPERIPH1_BASE + 0x1C00)
#define GPIOG_BASE                       (AHBPERIPH1_BASE + 0x1800)
#define GPIOF_BASE                       (AHBPERIPH1_BASE + 0x1400)
#define GPIOE_BASE                       (AHBPERIPH1_BASE + 0x1000)
#define GPIOD_BASE                       (AHBPERIPH1_BASE + 0x0C00)
#define GPIOC_BASE                       (AHBPERIPH1_BASE + 0x0800)
#define GPIOB_BASE                       (AHBPERIPH1_BASE + 0x0400)
#define GPIOA_BASE                       (AHBPERIPH1_BASE + 0x0000)

#define DMA1_BASE                        (AHBPERIPH1_BASE + 0x6000)
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

#define DMA2_BASE                        (AHBPERIPH1_BASE + 0x6400)
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

#define FLASH_REG_BASE                   (AHBPERIPH1_BASE + 0x3C00)
#define CRM_BASE                         (AHBPERIPH1_BASE + 0x3800)
#define CRC_BASE                         (AHBPERIPH1_BASE + 0x3000)
#define OTGFS1_BASE                      (AHBPERIPH2_BASE + 0x00000)
#define AES_BASE                         (AHBPERIPH2_BASE + 0x60000)
#define TRNG_BASE                        (AHBPERIPH2_BASE + 0x60800)
#endif

#if defined (AT32F456xx)
/* apb1 bus base address */
#define USART8_BASE                      (APB1PERIPH_BASE + 0x7C00)
#define USART7_BASE                      (APB1PERIPH_BASE + 0x7800)
#define DAC_BASE                         (APB1PERIPH_BASE + 0x7400)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
#define CAN3_BASE                        (APB1PERIPH_BASE + 0x6C00)
#define CAN2_BASE                        (APB1PERIPH_BASE + 0x6800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define I2C3_BASE                        (APB1PERIPH_BASE + 0x5C00)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define USART5_BASE                      (APB1PERIPH_BASE + 0x5000)
#define USART4_BASE                      (APB1PERIPH_BASE + 0x4C00)
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
#define I2SF5_BASE                       (APB2PERIPH_BASE + 0x5000)
#define TMR11_BASE                       (APB2PERIPH_BASE + 0x4800)
#define TMR10_BASE                       (APB2PERIPH_BASE + 0x4400)
#define TMR9_BASE                        (APB2PERIPH_BASE + 0x4000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x3C00)
#define SCFG_BASE                        (APB2PERIPH_BASE + 0x3800)
#define SPI4_BASE                        (APB2PERIPH_BASE + 0x3400)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE                        (APB2PERIPH_BASE + 0x2100)
#define ADCCOM_BASE                      (APB2PERIPH_BASE + 0x2300)
#define USART6_BASE                      (APB2PERIPH_BASE + 0x1400)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x1000)
#define TMR8_BASE                        (APB2PERIPH_BASE + 0x0400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x0000)
/* ahb bus base address */
#define SDIO1_BASE                       (AHBPERIPH1_BASE + 0x4C00)
#define GPIOH_BASE                       (AHBPERIPH1_BASE + 0x1C00)
#define GPIOG_BASE                       (AHBPERIPH1_BASE + 0x1800)
#define GPIOF_BASE                       (AHBPERIPH1_BASE + 0x1400)
#define GPIOE_BASE                       (AHBPERIPH1_BASE + 0x1000)
#define GPIOD_BASE                       (AHBPERIPH1_BASE + 0x0C00)
#define GPIOC_BASE                       (AHBPERIPH1_BASE + 0x0800)
#define GPIOB_BASE                       (AHBPERIPH1_BASE + 0x0400)
#define GPIOA_BASE                       (AHBPERIPH1_BASE + 0x0000)

#define DMA1_BASE                        (AHBPERIPH1_BASE + 0x6000)
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

#define DMA2_BASE                        (AHBPERIPH1_BASE + 0x6400)
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

#define FLASH_REG_BASE                   (AHBPERIPH1_BASE + 0x3C00)
#define CRM_BASE                         (AHBPERIPH1_BASE + 0x3800)
#define CRC_BASE                         (AHBPERIPH1_BASE + 0x3000)
#define OTGFS1_BASE                      (AHBPERIPH2_BASE + 0x00000)
#define AES_BASE                         (AHBPERIPH2_BASE + 0x60000)
#define TRNG_BASE                        (AHBPERIPH2_BASE + 0x60800)
#endif

#if defined (AT32F457xx)
/* apb1 bus base address */
#define USART8_BASE                      (APB1PERIPH_BASE + 0x7C00)
#define USART7_BASE                      (APB1PERIPH_BASE + 0x7800)
#define DAC_BASE                         (APB1PERIPH_BASE + 0x7400)
#define PWC_BASE                         (APB1PERIPH_BASE + 0x7000)
#define CAN3_BASE                        (APB1PERIPH_BASE + 0x6C00)
#define CAN2_BASE                        (APB1PERIPH_BASE + 0x6800)
#define CAN1_BASE                        (APB1PERIPH_BASE + 0x6400)
#define I2C3_BASE                        (APB1PERIPH_BASE + 0x5C00)
#define I2C2_BASE                        (APB1PERIPH_BASE + 0x5800)
#define I2C1_BASE                        (APB1PERIPH_BASE + 0x5400)
#define USART5_BASE                      (APB1PERIPH_BASE + 0x5000)
#define USART4_BASE                      (APB1PERIPH_BASE + 0x4C00)
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
#define I2SF5_BASE                       (APB2PERIPH_BASE + 0x5000)
#define TMR11_BASE                       (APB2PERIPH_BASE + 0x4800)
#define TMR10_BASE                       (APB2PERIPH_BASE + 0x4400)
#define TMR9_BASE                        (APB2PERIPH_BASE + 0x4000)
#define EXINT_BASE                       (APB2PERIPH_BASE + 0x3C00)
#define SCFG_BASE                        (APB2PERIPH_BASE + 0x3800)
#define SPI4_BASE                        (APB2PERIPH_BASE + 0x3400)
#define SPI1_BASE                        (APB2PERIPH_BASE + 0x3000)
#define ADC1_BASE                        (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE                        (APB2PERIPH_BASE + 0x2100)
#define ADCCOM_BASE                      (APB2PERIPH_BASE + 0x2300)
#define USART6_BASE                      (APB2PERIPH_BASE + 0x1400)
#define USART1_BASE                      (APB2PERIPH_BASE + 0x1000)
#define TMR8_BASE                        (APB2PERIPH_BASE + 0x0400)
#define TMR1_BASE                        (APB2PERIPH_BASE + 0x0000)
/* ahb bus base address */
#define SDIO1_BASE                       (AHBPERIPH1_BASE + 0x4C00)
#define GPIOH_BASE                       (AHBPERIPH1_BASE + 0x1C00)
#define GPIOG_BASE                       (AHBPERIPH1_BASE + 0x1800)
#define GPIOF_BASE                       (AHBPERIPH1_BASE + 0x1400)
#define GPIOE_BASE                       (AHBPERIPH1_BASE + 0x1000)
#define GPIOD_BASE                       (AHBPERIPH1_BASE + 0x0C00)
#define GPIOC_BASE                       (AHBPERIPH1_BASE + 0x0800)
#define GPIOB_BASE                       (AHBPERIPH1_BASE + 0x0400)
#define GPIOA_BASE                       (AHBPERIPH1_BASE + 0x0000)

#define DMA1_BASE                        (AHBPERIPH1_BASE + 0x6000)
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

#define DMA2_BASE                        (AHBPERIPH1_BASE + 0x6400)
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

#define FLASH_REG_BASE                   (AHBPERIPH1_BASE + 0x3C00)
#define CRM_BASE                         (AHBPERIPH1_BASE + 0x3800)
#define CRC_BASE                         (AHBPERIPH1_BASE + 0x3000)
#define EMAC_BASE                        (AHBPERIPH1_BASE + 0x8000)
#define OTGFS1_BASE                      (AHBPERIPH2_BASE + 0x00000)
#define AES_BASE                         (AHBPERIPH2_BASE + 0x60000)
#define TRNG_BASE                        (AHBPERIPH2_BASE + 0x60800)

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

#include "at32f45x_def.h"
#include "at32f45x_conf.h"

#ifdef __cplusplus
}
#endif

#endif
