/**
 **************************************************************************
 * File Name    : at32f4xx.h
 * Description  : at32f4xx peripheral access layer header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup at32f4xx
  * @{
  */

#ifndef __AT32F4xx_H
#define __AT32F4xx_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Library_configuration_section
  * @{
  */

/* Uncomment the line below according to the target AT32 device used in your
   application
  */
#if !defined (AT32F403Cx_MD) && !defined (AT32F403Cx_HD) && \
    !defined (AT32F403Cx_XL) && !defined (AT32F403Rx_HD) && \
    !defined (AT32F403Rx_XL) && !defined (AT32F403Vx_HD) && \
    !defined (AT32F403Vx_XL) && !defined (AT32F403Zx_HD) && \
    !defined (AT32F403Zx_XL) && \
    !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F413Cx_MD) && !defined (AT32F413Cx_HD) && \
    !defined (AT32F413Rx_MD) && !defined (AT32F413Rx_HD) && \
    !defined (AT32FEBKCx_MD) && !defined (TS32F401CBU7)  && \
    !defined (AT32F415C8T7)  && !defined (AT32F415CBT7)  && !defined (AT32F415CCT7)  && \
    !defined (AT32F415CBU7)  && !defined (AT32F415CCU7)  && !defined (AT32F415R8T7)  && \
    !defined (AT32F415RBT7)  && !defined (AT32F415RCT7)  && !defined (AT32F415K8U7_4)&& \
    !defined (AT32F415KBU7_4)&& !defined (AT32F415KCU7_4)&& !defined (AT32F415R8T7_7)&& \
    !defined (AT32F415RBT7_7)&& !defined (AT32F415RCT7_7)&& \
    !defined (AT32F407RGT7)  && !defined (AT32F407VGT7)  && !defined (AT32F407RCT7)  && \
    !defined (AT32F407VCT7)  && \
    !defined (AT32F403AVCT7) && !defined (AT32F403ARCT7) && !defined (AT32F403ACCT7) && \
    !defined (AT32F403ACCU7) && !defined (AT32F403AVGT7) && !defined (AT32F403ACGT7) && \
    !defined (AT32F403ARGT7) && !defined (AT32F403ACGU7) && !defined (AT32F403AVET7) && \
    !defined (AT32F403ARET7) && !defined (AT32F403ACEU7) && !defined (AT32F403ACET7)
/* #define AT32F403Cx_MD */   /*!< AT32F403Cx_MD: LQFP48, Medium density devices: AT32F403CB */
/* #define AT32F403Cx_HD */   /*!< AT32F403Cx_HD: LQFP48, High density devices: AT32F403CC, AT32F403CE */
/* #define AT32F403Cx_XL */   /*!< AT32F403Cx_XL: LQFP48, XL-density devices: AT32F403CG */
/* #define AT32F403Rx_HD */   /*!< AT32F403Rx_HD: LQFP64, High density devices: AT32F403RC, AT32F403RE */
/* #define AT32F403Rx_XL */   /*!< AT32F403Rx_XL: LQFP64, XL-density devices: AT32F403RG */
/* #define AT32F403Vx_HD */   /*!< AT32F403Vx_HD: LQFP100, High density devices: AT32F403VC, AT32F403VE */
/* #define AT32F403Vx_XL */   /*!< AT32F403Vx_XL: LQFP100, XL-density devices: AT32F403VG */
/* #define AT32F403Zx_HD */   /*!< AT32F403Zx_HD: LQFP144, High density devices: AT32F403ZC, AT32F403ZE */
/* #define AT32F403Zx_XL */   /*!< AT32F403Zx_XL: LQFP144, XL-density devices: AT32F403ZG */

/* #define AT32F413Kx_MD */   /*!< AT32F413Kx_MD: LQFP32, Medium density devices: AT32F413KB */
/* #define AT32F413Kx_HD */   /*!< AT32F413Kx_HD: LQFP32, High density devices: AT32F413KC */
/* #define AT32F413Cx_MD */   /*!< AT32F413Cx_MD: LQFP48, Medium density devices: AT32F413C8, AT32F413CB */
/* #define AT32F413Cx_HD */   /*!< AT32F413Cx_HD: LQFP48, High density devices: AT32F413CC */
/* #define AT32F413Rx_MD */   /*!< AT32F413Rx_MD: LQFP64, Medium density devices: AT32F413RB */
/* #define AT32F413Rx_HD */   /*!< AT32F413Rx_HD: LQFP64, High density devices: AT32F413RC */
/* #define AT32FEBKCx_MD */   /*!< AT32FEBKCx_MD: LQFP48, Medium density devices: AT32FEBKC8*/
/* #define TS32F401CBU7 */    /*!< TS32F401CBU7: QFN48, Medium density devices: TS32F401CBU7 */

/* #define AT32F415C8T7 */    /*!< AT32F415C8T7: LQFP48, Medium density devices: AT32F415C8T7 */
/* #define AT32F415CBT7 */    /*!< AT32F415CBT7: LQFP48, Medium density devices: AT32F415CBT7 */
/* #define AT32F415CCT7 */    /*!< AT32F415CCT7: LQFP48, High density devices: AT32F415CCT7 */
/* #define AT32F415CBU7 */    /*!< AT32F415CBU7: QFN48, Medium density devices: AT32F415CBU7 */
/* #define AT32F415CCU7 */    /*!< AT32F415CCU7: QFN48, High density devices: AT32F415CCU7 */
/* #define AT32F415R8T7 */    /*!< AT32F415R8T7: LQFP64, Medium density devices: AT32F415R8T7 */
/* #define AT32F415RBT7 */    /*!< AT32F415RBT7: LQFP64, Medium density devices: AT32F415RBT7 */
/* #define AT32F415RCT7 */    /*!< AT32F415RCT7: LQFP64, High density devices: AT32F415RCT7 */
/* #define AT32F415K8U7_4 */  /*!< AT32F415K8U7_4: QFN32, Medium density devices: AT32F415K8U7_4 */
/* #define AT32F415KBU7_4 */  /*!< AT32F415KBU7_4: QFN32, Medium density devices: AT32F415KBU7_4 */
/* #define AT32F415KCU7_4 */  /*!< AT32F415KCU7_4: QFN32, High density devices: AT32F415KCU7_4 */
/* #define AT32F415R8T7_7 */  /*!< AT32F415R8T7_7: LQFP64, Medium density devices: AT32F415R8T7_7 */
/* #define AT32F415RBT7_7 */  /*!< AT32F415RBT7_7: LQFP64, Medium density devices: AT32F415RBT7_7 */
/* #define AT32F415RCT7_7 */  /*!< AT32F415RCT7_7: LQFP64, High density devices: AT32F415RCT7_7 */

/* #define AT32F407RGT7 */    /*!< AT32F407RGT7: LQFP64, XL-density devices: AT32F407RGT7 */
/* #define AT32F407VGT7 */    /*!< AT32F407VGT7: LQFP100, XL-density devices: AT32F407VGT7 */
/* #define AT32F407RET7 */    /*!< AT32F407RET7: LQFP64, XL-density devices: AT32F407RET7 */
/* #define AT32F407VET7 */    /*!< AT32F407VET7: LQFP100, XL-density devices: AT32F407VET7 */
/* #define AT32F407RCT7 */    /*!< AT32F407RCT7: LQFP64, High density devices: AT32F407RCT7 */
/* #define AT32F407VCT7 */    /*!< AT32F407VCT7: LQFP100, High density devices: AT32F407VCT7 */

/* #define AT32F403AVCT7 */   /*!< AT32F403AVCT7: LQFP100, High density devices: AT32F403AVCT7 */
/* #define AT32F403ARCT7 */   /*!< AT32F403ARCT7: LQFP64, High density devices: AT32F403ARCT7 */
/* #define AT32F403ACCT7 */   /*!< AT32F403ACCT7: LQFP48, High density devices: AT32F403ACCT7 */
/* #define AT32F403ACCU7 */   /*!< AT32F403ACCU7: QFN48, High density devices: AT32F403ACCU7 */
/* #define AT32F403AVET7 */   /*!< AT32F403AVET7: LQFP100, XL-density devices: AT32F403AVET7 */
/* #define AT32F403ARET7 */   /*!< AT32F403ARET7: LQFP64, XL-density devices: AT32F403ARET7 */
/* #define AT32F403ACET7 */   /*!< AT32F403ACET7: LQFP48, XL-density devices: AT32F403ACET7 */
/* #define AT32F403ACEU7 */   /*!< AT32F403ACEU7: QFN48, XL-density devices: AT32F403ACEU7 */
/* #define AT32F403AVGT7 */   /*!< AT32F403AVGT7: LQFP100, XL-density devices: AT32F403AVGT7 */
/* #define AT32F403ACGT7 */   /*!< AT32F403ACGT7: LQFP48, XL-density devices: AT32F403ACGT7 */
/* #define AT32F403ARGT7 */   /*!< AT32F403ARGT7: LQFP64, XL-density devices: AT32F403ARGT7 */
/* #define AT32F403ACGU7 */   /*!< AT32F403ACGU7: QFN48, XL-density devices: AT32F403ACGU7 */

#endif
/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.

 - Medium-density devices are at32f4xx microcontrollers where
   the Flash memory density ranges between 64 and 128 Kbytes.
 - High-density devices are at32f4xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.
 - XL-density devices are at32f4xx microcontrollers where
   the Flash memory density ranges between 512 and 1024 Kbytes.
  */

#if !defined (AT32F403Cx_MD) && !defined (AT32F403Cx_HD) && \
    !defined (AT32F403Cx_XL) && !defined (AT32F403Rx_HD) && \
    !defined (AT32F403Rx_XL) && !defined (AT32F403Vx_HD) && \
    !defined (AT32F403Vx_XL) && !defined (AT32F403Zx_HD) && \
    !defined (AT32F403Zx_XL) && \
    !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F413Cx_MD) && !defined (AT32F413Cx_HD) && \
    !defined (AT32F413Rx_MD) && !defined (AT32F413Rx_HD) && \
    !defined (AT32FEBKCx_MD) && !defined (TS32F401CBU7)  && \
    !defined (AT32F415C8T7)  && !defined (AT32F415CBT7)  && !defined (AT32F415CCT7)  && \
    !defined (AT32F415CBU7)  && !defined (AT32F415CCU7)  && !defined (AT32F415R8T7)  && \
    !defined (AT32F415RBT7)  && !defined (AT32F415RCT7)  && !defined (AT32F415K8U7_4)&& \
    !defined (AT32F415KBU7_4)&& !defined (AT32F415KCU7_4)&& !defined (AT32F415R8T7_7)&& \
    !defined (AT32F415RBT7_7)&& !defined (AT32F415RCT7_7)&& \
    !defined (AT32F407RGT7)  && !defined (AT32F407VGT7)  && !defined (AT32F407RCT7)  && \
    !defined (AT32F407VCT7)  && !defined (AT32F407RET7)  && !defined (AT32F407VET7)  && \
    !defined (AT32F403AVCT7) && !defined (AT32F403ARCT7) && !defined (AT32F403ACCT7) && \
    !defined (AT32F403ACCU7) && !defined (AT32F403AVGT7) && !defined (AT32F403ACGT7) && \
    !defined (AT32F403ARGT7) && !defined (AT32F403ACGU7) && !defined (AT32F403AVET7) && \
    !defined (AT32F403ARET7) && !defined (AT32F403ACET7) && !defined (AT32F403ACEU7)
#error "Please select first the target at32f4xx device used in your application (in at32f4xx.h file)"
#endif

#if defined (AT32F403Cx_MD) || defined (AT32F403Cx_HD) || \
    defined (AT32F403Cx_XL) || defined (AT32F403Rx_HD) || \
    defined (AT32F403Rx_XL) || defined (AT32F403Vx_HD) || \
    defined (AT32F403Vx_XL) || defined (AT32F403Zx_HD) || \
    defined (AT32F403Zx_XL)

    #define AT32F403xx
#endif

#if defined (AT32F413Kx_MD) || defined (AT32F413Kx_HD) || \
    defined (AT32F413Cx_MD) || defined (AT32F413Cx_HD) || \
    defined (AT32F413Rx_MD) || defined (AT32F413Rx_HD) || \
    defined (AT32FEBKCx_MD) || defined (TS32F401CBU7)

    #define AT32F413xx
#endif

#if defined (AT32F415C8T7)  || defined (AT32F415CBT7)  || defined (AT32F415CCT7)  || \
    defined (AT32F415CBU7)  || defined (AT32F415CCU7)  || defined (AT32F415R8T7)  || \
    defined (AT32F415RBT7)  || defined (AT32F415RCT7)  || defined (AT32F415K8U7_4)|| \
    defined (AT32F415KBU7_4)|| defined (AT32F415KCU7_4)|| defined (AT32F415R8T7_7)|| \
    defined (AT32F415RBT7_7)|| defined (AT32F415RCT7_7)

    #define AT32F415xx
#endif

#if defined (AT32F407RGT7)  || defined (AT32F407VGT7)  || defined (AT32F407RCT7)  || \
    defined (AT32F407VCT7)  || defined (AT32F407VET7)  || defined (AT32F407RET7)

    #define AT32F407xx
#endif

#if defined (AT32F403AVCT7) || defined (AT32F403ARCT7) || defined (AT32F403ACCT7) || \
    defined (AT32F403ACCU7) || defined (AT32F403AVGT7) || defined (AT32F403ACGT7) || \
    defined (AT32F403ARGT7) || defined (AT32F403ACGU7) || defined (AT32F403AVET7) || \
    defined (AT32F403ACET7) || defined (AT32F403ARET7) || defined (AT32F403ACEU7)

    #define AT32F403Axx
#endif

#if !defined  USE_STDPERIPH_DRIVER
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
  #ifdef _RTE_
    #include "RTE_Components.h"
    #ifdef RTE_DEVICE_STDPERIPH_FRAMEWORK
      #define USE_STDPERIPH_DRIVER
    #endif
  #endif
#endif

#if !defined  LIBRARY_VERSION
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
/*#define LIBRARY_VERSION*/
#endif

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application

   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined  HSE_VALUE
#define HSE_VALUE               ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */


/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value
   */
#define HSE_STARTUP_TIMEOUT     ((uint16_t)0x3000) /*!< Time out for HSE start up */

#define HSI_VALUE               ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/

/**
 * @brief at32f4xx Standard Peripheral Library version number
   */
#define __AT32F4xx_LIBRARY_VERSION_MAIN     (0x01) /*!< [31:24] main version */
#define __AT32F4xx_LIBRARY_VERSION_MIDDLE   (0x00) /*!< [23:16] middle version */
#define __AT32F4xx_LIBRARY_VERSION_MINOR    (0x01) /*!< [15:8]  minor version */
#define __AT32F4xx_LIBRARY_VERSION_RC       (0x00) /*!< [7:0]  release candidate */
#define __AT32F4xx_LIBRARY_VERSION          ( (__AT32F4xx_LIBRARY_VERSION_MAIN << 24)\
                                             |(__AT32F4xx_LIBRARY_VERSION_MIDDLE << 16)\
                                             |(__AT32F4xx_LIBRARY_VERSION_MINOR << 8)\
                                             |(__AT32F4xx_LIBRARY_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief Configuration of the Cortex-M4 Processor and Core Peripherals
 */
#define __CM4_REV                 0x0001U  /*!< Core revision r0p1                            */
#define __MPU_PRESENT             0     /*!< AT32 devices do not provide an MPU           */
#define __NVIC_PRIO_BITS          4     /*!< AT32 uses 4 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig    0     /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U    /*!< FPU present                                  */

/**
 * @brief at32f4xx Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum IRQn
{
    /******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
    Reset_IRQn                  = -15,    /*!< 1 Reset Vector, invoked on Power up and warm reset   */
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn              = -13,    /*!< 3 Hard Fault, all classes of Fault                   */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                   */

    /******  AT32 specific Interrupt Numbers *********************************************************/
    WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
    PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
#ifdef AT32F415xx
    TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line*/
    ERTC_WKUP_IRQn              = 3,      /*!< ERTC Wakeup interrupt through the EXTI line          */
#else
    TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
    RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
#endif
    FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
    RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
    EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
    EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
    EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
    EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
    DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */

#ifdef AT32F403Cx_MD
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
#endif /* AT32F403Cx_MD */

#ifdef AT32F403Cx_HD
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
#endif /* AT32F403Cx_HD */

#ifdef AT32F403Cx_XL
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
#endif /* AT32F403Cx_XL */

#ifdef AT32F403Rx_HD
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
#endif /* AT32F403Rx_HD */

#ifdef AT32F403Rx_XL
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
#endif /* AT32F403Rx_XL */

#ifdef AT32F403Vx_HD
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    XMC_IRQn                    = 48,     /*!< XMC global Interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
#endif /* AT32F403Vx_HD */

#ifdef AT32F403Vx_XL
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    XMC_IRQn                    = 48,     /*!< XMC global Interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
#endif /* AT32F403Vx_XL */

#ifdef AT32F403Zx_HD
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    XMC_IRQn                    = 48,     /*!< XMC global Interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
    TMR15_BRK_IRQn              = 64,     /*!< TMR15 Break interrupt                                */
    TMR15_OV_IRQn               = 65,     /*!< TMR15 Update interrupt                               */
    TMR15_TRG_HALL_IRQn         = 66,     /*!< TMR15 Trigger and Commutation Interrupt              */
    TMR15_CC_IRQn               = 67      /*!< TMR15 Capture Compare Interrupt                      */
#endif /* AT32F403Zx_HD */

#ifdef AT32F403Zx_XL
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    XMC_IRQn                    = 48,     /*!< XMC global Interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
    TMR15_BRK_IRQn              = 64,     /*!< TMR15 Break interrupt                                */
    TMR15_OV_IRQn               = 65,     /*!< TMR15 Update interrupt                               */
    TMR15_TRG_HALL_IRQn         = 66,     /*!< TMR15 Trigger and Commutation Interrupt              */
    TMR15_CC_IRQn               = 67      /*!< TMR15 Capture Compare Interrupt                      */
#endif /* AT32F403Zx_XL */

#if defined (AT32F413Kx_MD) || defined (AT32F413Kx_HD)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn                 = 74,     /*!< USB Device Low Priority Interrupts                   */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32F413Kx_MD || AT32F413Kx_HD */

#if defined (AT32F413Cx_MD) || defined (TS32F401CBU7)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 TX Interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 RX0 Interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 RX1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn                 = 74,     /*!< USB Device Low Priority Interrupts                   */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32F413Cx_MD || TS32F401CBU7 */

#if defined (AT32F413Cx_HD)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 TX Interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 RX0 Interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 RX1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn                 = 74,     /*!< USB Device Low Priority Interrupts                   */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /*AT32F413Cx_HD */

#if defined (AT32F413Rx_MD)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 TX Interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 RX0 Interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 RX1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn                 = 74,     /*!< USB Device Low Priority Interrupts                   */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32F413Rx_MD*/

#if defined (AT32F413Rx_HD)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_HALL_TMR14_IRQn    = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 TX Interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 RX0 Interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 RX1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn                 = 74,     /*!< USB Device Low Priority Interrupts                   */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /*AT32F413Rx_HD */

#if defined (AT32FEBKCx_MD)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    USB_HP_IRQn                 = 73,     /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn                 = 74,     /*!< USB Device Low Priority Interrupts                   */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32FEBKCx_MD*/

#if defined (AT32F415K8U7_4) || defined (AT32F415KBU7_4) || defined (AT32F415KCU7_4)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupts                                   */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupts                                  */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ERTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    USBOTG_IRQn                 = 67,     /*!< USBOTG interrupt                                     */
    COMP1_IRQn                  = 70,     /*!< Compare1 Interrupts                                  */
    COMP2_IRQn                  = 71,     /*!< Compare2 Interrupts                                  */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32F415K8U7_4 || AT32F415KBU7_4 || AT32F415KCU7_4 */

#if defined (AT32F415C8T7) || defined (AT32F415CBT7) || defined (AT32F415CCT7) ||\
    defined (AT32F415CBU7) || defined (AT32F415CCU7)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupts                                   */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupts                                  */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ERTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    USBOTG_IRQn                 = 67,     /*!< USBOTG interrupt                                     */
    COMP1_IRQn                  = 70,     /*!< Compare1 Interrupts                                  */
    COMP2_IRQn                  = 71,     /*!< Compare2 Interrupts                                  */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32F415C8T7 || AT32F415CBT7 || AT32F415CCT7 || AT32F415CBU7 || AT32F415CCU7 */

#if defined (AT32F415R8T7) || defined (AT32F415R8T7_7) || \
    defined (AT32F415RBT7) || defined (AT32F415RBT7_7) || \
    defined (AT32F415RCT7) || defined (AT32F415RCT7_7)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupts                                   */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupts                                  */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    ERTCAlarm_IRQn              = 41,     /*!< ERTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    USBOTG_IRQn                 = 67,     /*!< USBOTG interrupt                                     */
    COMP1_IRQn                  = 70,     /*!< Compare1 Interrupts                                  */
    COMP2_IRQn                  = 71,     /*!< Compare2 Interrupts                                  */
    ACC_IRQn                    = 72,     /*!< ACC interrupt                                        */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel6 and Channel7 global interrupts         */
#endif /* AT32F415R8T7 || AT32F415R8T7_7 || AT32F415RBT7 || AT32F415RBT7_7 || AT32F415RCT7 || AT32F415RCT7_7 */

#if defined (AT32F403AVCT7) || defined (AT32F403ARCT7) || \
    defined (AT32F403AVET7) || defined (AT32F403ARET7) || \
    defined (AT32F403AVGT7) || defined (AT32F403ARGT7)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_TMR11_IRQn     = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_I2S2EXT_IRQn           = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_COM_TMR14_IRQn     = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    XMC_IRQn                    = 48,     /*!< XMC global Interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 Tx interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 Rx0 interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 Rx1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC Interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB HP Interrupt                                     */
    USB_LP_IRQn                 = 74,     /*!< USB LP Interrupt                                     */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel 6 and Channel 7 global Interrupt        */
    USART6_IRQn                 = 76,     /*!< USART6 Interrupt                                     */
    UART7_IRQn                  = 77,     /*!< UART7 Interrupt                                      */
    UART8_IRQn                  = 78,     /*!< UART8 Interrupt                                      */
#endif /* AT32F403AVCT7 || AT32F403ARCT7 || AT32F403AVGT7 || \
          AT32F403ARGT7 || AT32F403AVET7 || AT32F403ARET7 */


#if defined (AT32F403ACCT7) || defined (AT32F403ACCU7) || \
    defined (AT32F403ACET7) || defined (AT32F403ACEU7) || \
    defined (AT32F403ACGT7) || defined (AT32F403ACGU7)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_TMR11_IRQn     = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_I2S2EXT_IRQn           = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_COM_TMR14_IRQn     = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 Tx interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 Rx0 interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 Rx1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC Interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB HP Interrupt                                     */
    USB_LP_IRQn                 = 74,     /*!< USB LP Interrupt                                     */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel 6 and Channel 7 global Interrupt        */
    USART6_IRQn                 = 76,     /*!< USART6 Interrupt                                     */
    UART7_IRQn                  = 77,     /*!< UART7 Interrupt                                      */
#endif /* AT32F403ACCT7 || AT32F403ACCU7 || AT32F403ACGT7 || \
          AT32F403ACGU7 || AT32F403ACEU7 || AT32F403ACET7 */

#if defined (AT32F407VCT7) || defined (AT32F407RCT7) || \
    defined (AT32F407VET7) || defined (AT32F407RET7) || \
    defined (AT32F407VGT7) || defined (AT32F407RGT7)
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_OV_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_TMR11_IRQn     = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_GLOBAL_IRQn            = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_I2S2EXT_IRQn           = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_OV_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_COM_TMR14_IRQn     = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    XMC_IRQn                    = 48,     /*!< XMC global Interrupt                                 */
    SDIO1_IRQn                  = 49,     /*!< SDIO global Interrupt                                */
    TMR5_GLOBAL_IRQn            = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_I2S3EXT_IRQn           = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_GLOBAL_IRQn            = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_GLOBAL_IRQn            = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    SDIO2_IRQn                  = 60,     /*!< SDIO2 global Interrupt                               */
    I2C3_EV_IRQn                = 61,     /*!< I2C3 event interrupt                                 */
    I2C3_ER_IRQn                = 62,     /*!< I2C3 error interrupt                                 */
    SPI4_IRQn                   = 63,     /*!< SPI4 global Interrupt                                */
    CAN2_TX_IRQn                = 68,     /*!< CAN2 Tx interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /*!< CAN2 Rx0 interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /*!< CAN2 Rx1 Interrupt                                   */
    CAN2_SCE_IRQn               = 71,     /*!< CAN2 SCE Interrupt                                   */
    ACC_IRQn                    = 72,     /*!< ACC Interrupt                                        */
    USB_HP_IRQn                 = 73,     /*!< USB HP Interrupt                                     */
    USB_LP_IRQn                 = 74,     /*!< USB LP Interrupt                                     */
    DMA2_Channel6_7_IRQn        = 75,     /*!< DMA2 Channel 6 and Channel 7 global Interrupt        */
    USART6_IRQn                 = 76,     /*!< USART6 Interrupt                                     */
    UART7_IRQn                  = 77,     /*!< UART7 Interrupt                                      */
    UART8_IRQn                  = 78,     /*!< UART8 Interrupt                                      */
    ETH_IRQn                    = 79,     /*!< ETH Interrupt                                        */
    ETH_WKUP_IRQn               = 80,     /*!< ETH Wakeup Interrupt                                 */
#endif /* AT32F407VCT7 || AT32F407RCT7 || AT32F407VGT7 || \
          AT32F407RGT7 || AT32F407RET7 || AT32F407VET7 */

} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"
#include "system_at32f4xx.h"
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

/** at32f4xx Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t  sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t  vsc8;   /*!< Read Only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t  uc8;   /*!< Read Only */

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t  vuc8;   /*!< Read Only */

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/** at32f4xx Standard Peripheral Library old definitions (maintained for legacy purpose) */
#define HSEStartUp_TimeOut   HSE_STARTUP_TIMEOUT
#define HSE_Value            HSE_VALUE
#define HSI_Value            HSI_VALUE
/**
  * @}
  */

/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @brief HSI Auto Clock Calibration
  */
typedef struct
{
  __IO uint32_t STS;
  __IO uint32_t CTRL1;
  __IO uint32_t CTRL2;
  __IO uint32_t C1;
  __IO uint32_t C2;
  __IO uint32_t C3;
} ACC_Type;

/**
  * @brief Analog to Digital Converter
  */
typedef struct
{
    __IO uint32_t STS;
    __IO uint32_t CTRL1;
    __IO uint32_t CTRL2;
    __IO uint32_t SMPT1;
    __IO uint32_t SMPT2;
    __IO uint32_t JOFS1;
    __IO uint32_t JOFS2;
    __IO uint32_t JOFS3;
    __IO uint32_t JOFS4;
    __IO uint32_t WHTR;
    __IO uint32_t WLTR;
    __IO uint32_t RSQ1;
    __IO uint32_t RSQ2;
    __IO uint32_t RSQ3;
    __IO uint32_t JSQ;
    __IO uint32_t JDOR1;
    __IO uint32_t JDOR2;
    __IO uint32_t JDOR3;
    __IO uint32_t JDOR4;
    __IO uint32_t RDOR;
} ADC_Type;

/**
  * @brief Backup Registers
  */
#if !defined (AT32F415xx)
typedef struct
{
    uint32_t  RESERVED0;
    __IO uint16_t DT1;
    uint16_t  RESERVED1;
    __IO uint16_t DT2;
    uint16_t  RESERVED2;
    __IO uint16_t DT3;
    uint16_t  RESERVED3;
    __IO uint16_t DT4;
    uint16_t  RESERVED4;
    __IO uint16_t DT5;
    uint16_t  RESERVED5;
    __IO uint16_t DT6;
    uint16_t  RESERVED6;
    __IO uint16_t DT7;
    uint16_t  RESERVED7;
    __IO uint16_t DT8;
    uint16_t  RESERVED8;
    __IO uint16_t DT9;
    uint16_t  RESERVED9;
    __IO uint16_t DT10;
    uint16_t  RESERVED10;
    __IO uint16_t RTCCAL;
    uint16_t  RESERVED11;
    __IO uint16_t CTRL;
    uint16_t  RESERVED12;
    __IO uint16_t CTRLSTS;
    uint16_t  RESERVED13[5];
    __IO uint16_t DT11;
    uint16_t  RESERVED14;
    __IO uint16_t DT12;
    uint16_t  RESERVED15;
    __IO uint16_t DT13;
    uint16_t  RESERVED16;
    __IO uint16_t DT14;
    uint16_t  RESERVED17;
    __IO uint16_t DT15;
    uint16_t  RESERVED18;
    __IO uint16_t DT16;
    uint16_t  RESERVED19;
    __IO uint16_t DT17;
    uint16_t  RESERVED20;
    __IO uint16_t DT18;
    uint16_t  RESERVED21;
    __IO uint16_t DT19;
    uint16_t  RESERVED22;
    __IO uint16_t DT20;
    uint16_t  RESERVED23;
    __IO uint16_t DT21;
    uint16_t  RESERVED24;
    __IO uint16_t DT22;
    uint16_t  RESERVED25;
    __IO uint16_t DT23;
    uint16_t  RESERVED26;
    __IO uint16_t DT24;
    uint16_t  RESERVED27;
    __IO uint16_t DT25;
    uint16_t  RESERVED28;
    __IO uint16_t DT26;
    uint16_t  RESERVED29;
    __IO uint16_t DT27;
    uint16_t  RESERVED30;
    __IO uint16_t DT28;
    uint16_t  RESERVED31;
    __IO uint16_t DT29;
    uint16_t  RESERVED32;
    __IO uint16_t DT30;
    uint16_t  RESERVED33;
    __IO uint16_t DT31;
    uint16_t  RESERVED34;
    __IO uint16_t DT32;
    uint16_t  RESERVED35;
    __IO uint16_t DT33;
    uint16_t  RESERVED36;
    __IO uint16_t DT34;
    uint16_t  RESERVED37;
    __IO uint16_t DT35;
    uint16_t  RESERVED38;
    __IO uint16_t DT36;
    uint16_t  RESERVED39;
    __IO uint16_t DT37;
    uint16_t  RESERVED40;
    __IO uint16_t DT38;
    uint16_t  RESERVED41;
    __IO uint16_t DT39;
    uint16_t  RESERVED42;
    __IO uint16_t DT40;
    uint16_t  RESERVED43;
    __IO uint16_t DT41;
    uint16_t  RESERVED44;
    __IO uint16_t DT42;
    uint16_t  RESERVED45;
} BKP_Type;
#endif

/**
  * @brief Controller Area Network TxMailBox
  */
typedef struct
{
    __IO uint32_t TMI;
    __IO uint32_t TDT;
    __IO uint32_t TDL;
    __IO uint32_t TDH;
} CAN_TxMailBox_Type;

/**
  * @brief Controller Area Network FIFOMailBox
  */
typedef struct
{
    __IO uint32_t RFI;
    __IO uint32_t RDT;
    __IO uint32_t RDL;
    __IO uint32_t RDH;
} CAN_FIFOMailBox_Type;

/**
  * @brief Controller Area Network FilterRegister
  */
typedef struct
{
    __IO uint32_t FBR1;
    __IO uint32_t FBR2;
} CAN_FilterRegister_Type;

/**
  * @brief Controller Area Network
  */
typedef struct
{
    __IO uint32_t MCTRL;
    __IO uint32_t MSTS;
    __IO uint32_t TSTS;
    __IO uint32_t RF0;
    __IO uint32_t RF1;
    __IO uint32_t INTEN;
    __IO uint32_t ESTS;
    __IO uint32_t BTMG;
    uint32_t  RESERVED0[88];
    CAN_TxMailBox_Type TxMailBox[3];
    CAN_FIFOMailBox_Type FIFOMailBox[2];
    uint32_t  RESERVED1[12];
    __IO uint32_t FM;
    __IO uint32_t FM1;
    uint32_t  RESERVED2;
    __IO uint32_t FS1;
    uint32_t  RESERVED3;
    __IO uint32_t FFA1;
    uint32_t  RESERVED4;
    __IO uint32_t FA1;
    uint32_t  RESERVED5[8];
    CAN_FilterRegister_Type FilterRegister[14];
} CAN_Type;

/**
  * @brief Comparator 
  */
typedef struct
{
  __IO uint32_t CTRLSTS1;     /*!< COMP comparator control and status register, Address offset: 0x1C */
  __IO uint32_t CTRLSTS2;
  __IO uint32_t G_FILTER_EN;
  __IO uint32_t HIGH_PULSE;
  __IO uint32_t LOW_PULSE;    
} COMP_Type;

/**
  * @brief CRC calculation unit
  */
typedef struct
{
    __IO uint32_t DT;
    __IO uint8_t  IDT;
    uint8_t   RESERVED0;
    uint16_t  RESERVED1;
    __IO uint32_t CTRL;
} CRC_Type;

/**
  * @brief Digital to Analog Converter
  */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t SWTRG;
    __IO uint32_t HDR12R1;
    __IO uint32_t HDR12L1;
    __IO uint32_t HDR8R1;
    __IO uint32_t HDR12R2;
    __IO uint32_t HDR12L2;
    __IO uint32_t HDR8R2;
    __IO uint32_t HDR12RD;
    __IO uint32_t HDR12LD;
    __IO uint32_t HDR8RD;
    __IO uint32_t ODT1;
    __IO uint32_t ODT2;
} DAC_Type;

/**
  * @brief MCU Debug
  */
typedef struct
{
    __IO uint32_t IDCR;
    __IO uint32_t CTRL;
} MCUDBG_Type;

/**
  * @brief DMA Controller
  */
typedef struct
{
    __IO uint32_t CHCTRL;
    __IO uint32_t TCNT;
    __IO uint32_t CPBA;
    __IO uint32_t CMBA;
} DMA_Channel_Type;

typedef struct
{
    __IO uint32_t ISTS;
    __IO uint32_t ICLR;
    uint32_t  RESERVED[38];
    __IO uint32_t DMA_SRC_SEL0;
    __IO uint32_t DMA_SRC_SEL1;	
} DMA_Type;

/**
  * @brief External Interrupt/Event Controller
  */
typedef struct
{
    __IO uint32_t INTEN;
    __IO uint32_t EVTEN;
    __IO uint32_t RTRSEL;
    __IO uint32_t FTRSEL;
    __IO uint32_t SWIE;
    __IO uint32_t PND;
} EXTI_Type;

/**
  * @brief FLASH Registers
  */
typedef struct
{
    __IO uint32_t ACR;
    __IO uint32_t FCKEY;
    __IO uint32_t OPTKEYR;
    __IO uint32_t STS;
    __IO uint32_t CTRL;
    __IO uint32_t ADDR;
    uint32_t RESERVED0;
    __IO uint32_t UOB;
    __IO uint32_t WRPRT;  
    uint32_t RESERVED1[8];
    __IO uint32_t FCKEY2;
    uint32_t RESERVED2;
    __IO uint32_t STS2;
    __IO uint32_t CTRL2;
    __IO uint32_t ADDR2;
    uint32_t RESERVED3[7];
#if defined (AT32F415xx)
    __IO uint32_t SLIB_CDR0;
    __IO uint32_t SLIB_CDR1;
    __IO uint32_t SLIB_PSW;
    __IO uint32_t SLIB_PSW_STS;
    __IO uint32_t CRC_AR;
    __IO uint32_t CRC_CR;
    __IO uint32_t CRC_OUTR;
    uint32_t RESERVED4[3];
#else
    uint32_t RESERVED5[4];
    __IO uint32_t FCKEY3;
    __IO uint32_t B3SEL;
    __IO uint32_t STS3;
    __IO uint32_t CTRL3;
    __IO uint32_t ADDR3;
    __IO uint32_t DA;
#endif
    uint32_t RESERVED6[12];
#if defined (AT32F415xx)
    uint32_t RESERVED7[6];
#else
    __IO uint32_t SLIB_CDR0;
    __IO uint32_t SLIB_CDR1;
    __IO uint32_t SLIB_PSW;
    __IO uint32_t SLIB_PSW_STS;
    __IO uint32_t SLIB_SET_PSW;
    __IO uint32_t SLIB_SET_RANGE;
#endif
    uint32_t RESERVED8[3];
#if defined (AT32F415xx)
    uint32_t RESERVED9[3];
#else
    __IO uint32_t SLIB_KEYR;
    __IO uint32_t CRC_DR;
    __IO uint32_t CRC_OUTR;
#endif
#if defined (AT32F415xx)
    uint32_t RESERVED10[25];
    __IO uint32_t SLIB_SET_PSW;
    __IO uint32_t SLIB_SET_RANGE;
    __IO uint32_t SYS_SLIB_SET;
    __IO uint32_t SYS_BOOT_DIS_SET;
    __IO uint32_t SLIB_KEYR;
#endif
} FLASH_Type;

/**
  * @brief Option Bytes Registers
  */
typedef struct
{
    __IO uint16_t RDPRT;
    __IO uint16_t USR;
    __IO uint16_t DATA0;
    __IO uint16_t DATA1;
    __IO uint16_t WRPRT0;
    __IO uint16_t WRPRT1;
    __IO uint16_t WRPRT2;
    __IO uint16_t WRPRT3;
#if !defined (AT32F415xx)
    __IO uint16_t EOPB0;
    __IO uint16_t EOPB1;
    __IO uint16_t HID[4];
    __IO uint32_t Reserved;
    __IO uint32_t BANK3SCRKEY[4];
#endif
} UOB_Type;

/**
  * @brief Flexible Static Memory Controller
  */
typedef struct
{
    __IO uint32_t BK1CTRLR[8];
} XMC_Bank1_Type;

/**
  * @brief Flexible Static Memory Controller Bank1E
  */
typedef struct
{
    __IO uint32_t BK1TMGWR[7];
} XMC_Bank1Ext_Type;

/**
  * @brief Flexible Static Memory Controller Bank1H
  */
typedef struct
{
    __IO uint32_t BK1EXT[4];
} XMC_Bank1Hide_Type;

/**
  * @brief Flexible Static Memory Controller Bank2
  */
typedef struct
{
    __IO uint32_t BK2CTRL;
    __IO uint32_t BK2STS;
    __IO uint32_t BK2TMGMEM;
    __IO uint32_t BK2TMGATT;
    uint32_t  RESERVED0;
    __IO uint32_t BK2ECC;
} XMC_Bank2_Type;

/**
  * @brief Flexible Static Memory Controller Bank3
  */
typedef struct
{
    __IO uint32_t BK3CTRL;
    __IO uint32_t BK3STS;
    __IO uint32_t BK3TMGMEM;
    __IO uint32_t BK3TMGATT;
    uint32_t  RESERVED0;
    __IO uint32_t BK3ECC;
} XMC_Bank3_Type;

/**
  * @brief Flexible Static Memory Controller Bank4
  */
typedef struct
{
    __IO uint32_t BK4CTRL;
    __IO uint32_t BK4STS;
    __IO uint32_t BK4TMGMEM;
    __IO uint32_t BK4TMGATT;
    __IO uint32_t BK4TMGIO;
} XMC_Bank4_Type;

/**
  * @brief General Purpose I/O
  */
typedef struct
{
    __IO uint32_t CTRLL;
    __IO uint32_t CTRLH;
    __IO uint32_t IPTDT;
    __IO uint32_t OPTDT;
    __IO uint32_t BSRE;
    __IO uint32_t BRE;
    __IO uint32_t LOCK;
#if defined (AT32F403Axx) || defined (AT32F407xx) 
    uint32_t RESERVED0;
    __IO uint32_t SRCTR;
    uint32_t RESERVED1;	
    uint32_t RESERVED2;	
    uint32_t RESERVED3;	
    uint32_t RESERVED4;	
    uint32_t RESERVED5;	
    uint32_t RESERVED6;	
    __IO uint32_t HDRV;
#endif
} GPIO_Type;

/**
  * @brief Alternate Function I/O
  */
typedef struct
{
    __IO uint32_t EVCTRL;
    __IO uint32_t MAP;
    __IO uint32_t EXTIC[4];
    uint32_t RESERVED0;
    __IO uint32_t MAP2;
#ifndef AT32F403xx
    __IO uint32_t MAP3;
    __IO uint32_t MAP4;
    __IO uint32_t MAP5;
    __IO uint32_t MAP6;
    __IO uint32_t MAP7;
#ifndef AT32F413xx
    __IO uint32_t MAP8;
#endif
#endif
} AFIO_Type;

/**
  * @brief Inter Integrated Circuit Interface
  */
typedef struct
{
    __IO uint16_t CTRL1;
    uint16_t  RESERVED0;
    __IO uint16_t CTRL2;
    uint16_t  RESERVED1;
    __IO uint16_t OADDR1;
    uint16_t  RESERVED2;
    __IO uint16_t OADDR2;
    uint16_t  RESERVED3;
    __IO uint16_t DT;
    uint16_t  RESERVED4;
    __IO uint16_t STS1;
    uint16_t  RESERVED5;
    __IO uint16_t STS2;
    uint16_t  RESERVED6;
    __IO uint16_t CLKCTRL;
    uint16_t  RESERVED7;
    __IO uint16_t TMRISE;
    uint16_t  RESERVED8;
} I2C_Type;

/**
  * @brief Independent WATCHDOG
  */
typedef struct
{
    __IO uint32_t KEY;
    __IO uint32_t PSC;
    __IO uint32_t RLD;
    __IO uint32_t STS;
} IWDG_Type;

/**
  * @brief Power Control
  */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CTRLSTS;
} PWR_Type;

/**
  * @brief Reset and Clock Control
  */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CFG;
    __IO uint32_t CLKINT;
    __IO uint32_t APB2RST;
    __IO uint32_t APB1RST;
    __IO uint32_t AHBEN;
    __IO uint32_t APB2EN;
    __IO uint32_t APB1EN;
    __IO uint32_t BDC;
    __IO uint32_t CTRLSTS;
#if defined (AT32F415xx)
    __IO uint32_t AHBRST;
    __IO uint32_t PLL;
#elif defined (AT32F403Axx) || defined (AT32F407xx)
    __IO uint32_t AHBRST;
    __IO uint32_t RESERVED;
#else
    __IO uint32_t RESERVED[2];
#endif
    __IO uint32_t MISC;
#if defined (AT32F413xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
    __IO uint32_t RESERVED1[7];
    __IO uint32_t TEST;
    __IO uint32_t MISC2;
    __IO uint32_t RESERVED2;
    __IO uint32_t INTCTRL;
#elif defined (AT32F415xx)
    __IO uint32_t RESERVED1[8];
    __IO uint32_t MISC2;
#endif
} RCC_Type;

/**
  * @brief Real-Time Clock
  */
#if defined (AT32F415xx)
typedef struct
{
  __IO uint32_t TIME;     /*!< ERTC time register,                                        Address offset: 0x00 */
  __IO uint32_t DATE;     /*!< ERTC date register,                                        Address offset: 0x04 */
  __IO uint32_t CTRL;     /*!< ERTC control register,                                     Address offset: 0x08 */
  __IO uint32_t ISTS;     /*!< ERTC initialization and status register,                   Address offset: 0x0C */
  __IO uint32_t PSC;      /*!< ERTC prescaler register,                                   Address offset: 0x10 */
  __IO uint32_t WATR;     /*!< ERTC wakeup timer register,                                Address offset: 0x14 */
  __IO uint32_t CAL;      /*!< ERTC calibration register,                                 Address offset: 0x18 */
  __IO uint32_t ALA;      /*!< ERTC alarm A register,                                     Address offset: 0x1C */
  __IO uint32_t ALB;      /*!< ERTC alarm B register,                                     Address offset: 0x20 */
  __IO uint32_t WPR;      /*!< ERTC write protection register,                            Address offset: 0x24 */
  __IO uint32_t SBSR;     /*!< ERTC sub second register,                                  Address offset: 0x28 */
  __IO uint32_t SFCTR;    /*!< ERTC shift control register,                               Address offset: 0x2C */
  __IO uint32_t TSTM;     /*!< ERTC time stamp time register,                             Address offset: 0x30 */
  __IO uint32_t TSDT;     /*!< ERTC time stamp date register,                             Address offset: 0x34 */
  __IO uint32_t TSSBS;    /*!< ERTC time-stamp sub second register,                       Address offset: 0x38 */
  __IO uint32_t CCR;      /*!< ERTC calibration register,                                 Address offset: 0x3C */
  __IO uint32_t TPAF;     /*!< ERTC tamper and alternate function configuration register, Address offset: 0x40 */
  __IO uint32_t ALASBS;   /*!< ERTC alarm A sub second register,                          Address offset: 0x44 */
  __IO uint32_t ALBSBS;   /*!< ERTC alarm B sub second register,                          Address offset: 0x48 */
  uint32_t RESERVED7;     /*!< Reserved, 0x4C                                                                 */
  __IO uint32_t BKP0DT;   /*!< ERTC backup register 1,                                    Address offset: 0x50 */
  __IO uint32_t BKP1DT;   /*!< ERTC backup register 1,                                    Address offset: 0x54 */
  __IO uint32_t BKP2DT;   /*!< ERTC backup register 2,                                    Address offset: 0x58 */
  __IO uint32_t BKP3DT;   /*!< ERTC backup register 3,                                    Address offset: 0x5C */
  __IO uint32_t BKP4DT;   /*!< ERTC backup register 4,                                    Address offset: 0x60 */
  __IO uint32_t BKP5DT;   /*!< ERTC backup register 5,                                    Address offset: 0x64 */
  __IO uint32_t BKP6DT;   /*!< ERTC backup register 6,                                    Address offset: 0x68 */
  __IO uint32_t BKP7DT;   /*!< ERTC backup register 7,                                    Address offset: 0x6C */
  __IO uint32_t BKP8DT;   /*!< ERTC backup register 8,                                    Address offset: 0x70 */
  __IO uint32_t BKP9DT;   /*!< ERTC backup register 9,                                    Address offset: 0x74 */
  __IO uint32_t BKP10DT;  /*!< ERTC backup register 10,                                   Address offset: 0x78 */
  __IO uint32_t BKP11DT;  /*!< ERTC backup register 11,                                   Address offset: 0x7C */
  __IO uint32_t BKP12DT;  /*!< ERTC backup register 12,                                   Address offset: 0x80 */
  __IO uint32_t BKP13DT;  /*!< ERTC backup register 13,                                   Address offset: 0x84 */
  __IO uint32_t BKP14DT;  /*!< ERTC backup register 14,                                   Address offset: 0x88 */
  __IO uint32_t BKP15DT;  /*!< ERTC backup register 15,                                   Address offset: 0x8C */
  __IO uint32_t BKP16DT;  /*!< ERTC backup register 16,                                   Address offset: 0x90 */
  __IO uint32_t BKP17DT;  /*!< ERTC backup register 17,                                   Address offset: 0x94 */
  __IO uint32_t BKP18DT;  /*!< ERTC backup register 18,                                   Address offset: 0x98 */
  __IO uint32_t BKP19DT;  /*!< ERTC backup register 19,                                   Address offset: 0x9C */
} ERTC_Type;
#else
typedef struct
{
    __IO uint16_t CTRLH;
    uint16_t  RESERVED0;
    __IO uint16_t CTRLL;
    uint16_t  RESERVED1;
    __IO uint16_t DIVH;
    uint16_t  RESERVED2;
    __IO uint16_t DIVL;
    uint16_t  RESERVED3;
    __IO uint16_t DIVCNTH;
    uint16_t  RESERVED4;
    __IO uint16_t DIVCNTL;
    uint16_t  RESERVED5;
    __IO uint16_t CNTH;
    uint16_t  RESERVED6;
    __IO uint16_t CNTL;
    uint16_t  RESERVED7;
    __IO uint16_t ALAH;
    uint16_t  RESERVED8;
    __IO uint16_t ALAL;
    uint16_t  RESERVED9;
} RTC_Type;
#endif
/**
  * @brief SD host Interface
  */
typedef struct
{
    __IO uint32_t POWER;
    __IO uint32_t CLKCTRL;
    __IO uint32_t ARG;
    __IO uint32_t CMD;
    __I uint32_t RSPCMD;
    __I uint32_t RSP1;
    __I uint32_t RSP2;
    __I uint32_t RSP3;
    __I uint32_t RSP4;
    __IO uint32_t DTTMR;
    __IO uint32_t DTLEN;
    __IO uint32_t DTCTRL;
    __I uint32_t DTCNTR;
    __I uint32_t STS;
    __IO uint32_t INTCLR;
    __IO uint32_t INTEN;
    uint32_t  RESERVED0[2];
    __I uint32_t BUFCNTR;
    uint32_t  RESERVED1[13];
    __IO uint32_t BUF;
} SDIO_Type;

/**
  * @brief Serial Peripheral Interface
  */
typedef struct
{
    __IO uint16_t CTRL1;
    uint16_t  RESERVED0;
    __IO uint16_t CTRL2;
    uint16_t  RESERVED1;
    __IO uint16_t STS;
    uint16_t  RESERVED2;
    __IO uint16_t DT;
    uint16_t  RESERVED3;
    __IO uint16_t CPOLY;
    uint16_t  RESERVED4;
    __IO uint16_t RCRC;
    uint16_t  RESERVED5;
    __IO uint16_t TCRC;
    uint16_t  RESERVED6;
    __IO uint16_t I2SCTRL;
    uint16_t  RESERVED7;
    __IO uint16_t I2SCLKP;
    uint16_t  RESERVED8;
} SPI_Type;

/**
  * @brief TIMER
  */
typedef struct
{
    __IO uint16_t CTRL1;
    uint16_t  RESERVED0;
    __IO uint16_t CTRL2;
    uint16_t  RESERVED1;
    __IO uint16_t SMC;
    uint16_t  RESERVED2;
    __IO uint16_t DIE;
    uint16_t  RESERVED3;
    __IO uint16_t STS;
    uint16_t  RESERVED4;
    __IO uint16_t EVEG;
    uint16_t  RESERVED5;
    __IO uint16_t CCM1;
    uint16_t  RESERVED6;
    __IO uint16_t CCM2;
    uint16_t  RESERVED7;
    __IO uint16_t CCE;
    uint16_t  RESERVED8;
	__IO uint32_t CNT;
    __IO uint16_t DIV;
    uint16_t  RESERVED10;
	__IO uint32_t AR;
    __IO uint16_t RC;
    uint16_t  RESERVED12;
    __IO uint32_t CC1;
    __IO uint32_t CC2;
    __IO uint32_t CC3;
    __IO uint32_t CC4;
    __IO uint16_t BRKDT;
    uint16_t  RESERVED17;
    __IO uint16_t DMAC;
    uint16_t  RESERVED18;
    __IO uint16_t DMABA;
    uint16_t  RESERVED19;
} TMR_Type;

/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
typedef struct
{
    __IO uint16_t STS;
    uint16_t  RESERVED0;
    __IO uint16_t DT;
    uint16_t  RESERVED1;
    __IO uint16_t BAUDR;
    uint16_t  RESERVED2;
    __IO uint16_t CTRL1;
    uint16_t  RESERVED3;
    __IO uint16_t CTRL2;
    uint16_t  RESERVED4;
    __IO uint16_t CTRL3;
    uint16_t  RESERVED5;
    __IO uint16_t GTP;
    uint16_t  RESERVED6;
} USART_Type;

/**
  * @brief Window WATCHDOG
  */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CFG;
    __IO uint32_t STS;
} WWDG_Type;

/** 
  * @brief Ethernet MAC
  */

typedef struct
{
  __IO uint32_t MACCTRL;
  __IO uint32_t MACFRMF;
  __IO uint32_t MACHTH;
  __IO uint32_t MACHTL;
  __IO uint32_t MACMIIADDR;
  __IO uint32_t MACMIIDT;
  __IO uint32_t MACFCTRL;
  __IO uint32_t MACVLT;             /*    8 */
       uint32_t RESERVED0[2];
  __IO uint32_t MACRWFF;             /*   11 */
  __IO uint32_t MACPMTCTRLSTS;
       uint32_t RESERVED1[2];
  __IO uint32_t MACISTS;                 /*   15 */
  __IO uint32_t MACIM;
  __IO uint32_t MACA0H;
  __IO uint32_t MACA0L;
  __IO uint32_t MACA1H;
  __IO uint32_t MACA1L;
  __IO uint32_t MACA2H;
  __IO uint32_t MACA2L;
  __IO uint32_t MACA3H;
  __IO uint32_t MACA3L;               /*   24 */
       uint32_t RESERVED2[40];
  __IO uint32_t MMCCTRL;                 /*   65 */
  __IO uint32_t MMCRI;
  __IO uint32_t MMCTI;
  __IO uint32_t MMCRIM;
  __IO uint32_t MMCTIM;               /*   69 */
       uint32_t RESERVED3[14];
  __IO uint32_t MMCTFSCC;            /*   84 */
  __IO uint32_t MMCTFMSCC;
       uint32_t RESERVED4[5];
  __IO uint32_t MMCTFCNT;
       uint32_t RESERVED5[10];
  __IO uint32_t MMCRFCECNT;
  __IO uint32_t MMCRFAECNT;
       uint32_t RESERVED6[10];
  __IO uint32_t MMCRGUFCNT;
       uint32_t RESERVED7[334];
  __IO uint32_t PTPTSCTRL;
  __IO uint32_t PTPSSINC;
  __IO uint32_t PTPTSH;
  __IO uint32_t PTPTSL;
  __IO uint32_t PTPTSHUD;
  __IO uint32_t PTPTSLUD;
  __IO uint32_t PTPTSAD;
  __IO uint32_t PTPTTH;
  __IO uint32_t PTPTTL;
       uint32_t RESERVED8[567];
  __IO uint32_t DMABM;
  __IO uint32_t DMATPD;
  __IO uint32_t DMARPD;
  __IO uint32_t DMARDLADDR;
  __IO uint32_t DMATDLADDR;
  __IO uint32_t DMASTS;
  __IO uint32_t DMAOPM;
  __IO uint32_t DMAIE;
  __IO uint32_t DMAMFBOCNT;
       uint32_t RESERVED9[9];
  __IO uint32_t DMACTD;
  __IO uint32_t DMACRD;
  __IO uint32_t DMACTBADDR;
  __IO uint32_t DMACRBADDR;
} ETH_Type;

/**
  * @}
  */

/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define EXT_FLASH_BASE        ((uint32_t)0x08400000) /*!< External FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */

#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
 #define XMC_R_BASE           ((uint32_t)0xA0000000) /*!< XMC registers base address */
#endif

#define UOB_BASE              ((uint32_t)0x1FFFF800) /*!< Flash Option Bytes base address */

#define DBGMCU_BASE           ((uint32_t)0xE0042000) /*!< Debug MCU registers base address */

/** Peripheral memory map */
#define APB1PERIPH_BASE       (PERIPH_BASE)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define TMR2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TMR3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TMR4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TMR5_BASE             (APB1PERIPH_BASE + 0x0C00)
#if !defined (AT32F415xx)
 #define RTC_BASE             (APB1PERIPH_BASE + 0x2800)
#else
 #define ERTC_BASE            (APB1PERIPH_BASE + 0x2800)
#endif
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x6400)

#if !defined (AT32F415xx)
 #define BKP_BASE             (APB1PERIPH_BASE + 0x6C00)
#endif

#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)

#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)

#if defined (AT32F413xx) || defined (AT32F415xx)
 #define GPIOA_BASE           (PERIPH_BASE + 0x10800)
 #define GPIOB_BASE           (PERIPH_BASE + 0x10C00)
 #define GPIOC_BASE           (PERIPH_BASE + 0x11000)
 #define GPIOD_BASE           (PERIPH_BASE + 0x11400)
 #define GPIOF_BASE           (PERIPH_BASE + 0x11C00)
#elif defined (AT32F403xx)
 #define GPIOA_BASE           (APB2PERIPH_BASE + 0x0800)
 #define GPIOB_BASE           (APB2PERIPH_BASE + 0x0C00)
 #define GPIOC_BASE           (APB2PERIPH_BASE + 0x1000)
 #define GPIOD_BASE           (APB2PERIPH_BASE + 0x1400)
 #define GPIOE_BASE           (APB2PERIPH_BASE + 0x1800)
 #define GPIOF_BASE           (APB2PERIPH_BASE + 0x1C00)
 #define GPIOG_BASE           (APB2PERIPH_BASE + 0x2000)
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define GPIOA_BASE           (APB2PERIPH_BASE + 0x0800)
 #define GPIOB_BASE           (APB2PERIPH_BASE + 0x0C00)
 #define GPIOC_BASE           (APB2PERIPH_BASE + 0x1000)
 #define GPIOD_BASE           (APB2PERIPH_BASE + 0x1400)
 #define GPIOE_BASE           (APB2PERIPH_BASE + 0x1800)
#endif

#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TMR1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#if !defined (AT32F415xx)
 #define TMR8_BASE            (APB2PERIPH_BASE + 0x3400)
#endif

#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
#define TMR9_BASE             (APB2PERIPH_BASE + 0x4C00)
#define TMR10_BASE            (APB2PERIPH_BASE + 0x5000)
#define TMR11_BASE            (APB2PERIPH_BASE + 0x5400)

#define DMA1_BASE             (AHBPERIPH_BASE + 0x0000)
#define DMA1_Channel1_BASE    (AHBPERIPH_BASE + 0x0008)
#define DMA1_Channel2_BASE    (AHBPERIPH_BASE + 0x001C)
#define DMA1_Channel3_BASE    (AHBPERIPH_BASE + 0x0030)
#define DMA1_Channel4_BASE    (AHBPERIPH_BASE + 0x0044)
#define DMA1_Channel5_BASE    (AHBPERIPH_BASE + 0x0058)
#define DMA1_Channel6_BASE    (AHBPERIPH_BASE + 0x006C)
#define DMA1_Channel7_BASE    (AHBPERIPH_BASE + 0x0080)
#define DMA2_BASE             (AHBPERIPH_BASE + 0x0400)
#define DMA2_Channel1_BASE    (AHBPERIPH_BASE + 0x0408)
#define DMA2_Channel2_BASE    (AHBPERIPH_BASE + 0x041C)
#define DMA2_Channel3_BASE    (AHBPERIPH_BASE + 0x0430)
#define DMA2_Channel4_BASE    (AHBPERIPH_BASE + 0x0444)
#define DMA2_Channel5_BASE    (AHBPERIPH_BASE + 0x0458)

#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000) /*!< Flash registers base address */
#define CRC_BASE              (AHBPERIPH_BASE + 0x3000)

#if defined (AT32F415xx)
 #define ACC_BASE             (APB2PERIPH_BASE + 0x5800)
 #define SDIO_BASE            (PERIPH_BASE + 0x18000)
 #define USBOTG_BASE          (PERIPH_BASE + 0x10000000)
 #define COMP_BASE            (APB1PERIPH_BASE + 0x2400)
 #define DMA2_Channel6_BASE   (AHBPERIPH_BASE + 0x046C)
 #define DMA2_Channel7_BASE   (AHBPERIPH_BASE + 0x0480)
#elif defined (AT32F413xx)
 #if !defined (AT32FEBKCx_MD)
  #define CAN2_BASE           (APB1PERIPH_BASE + 0x6800)
  #define ACC_BASE            (APB2PERIPH_BASE + 0x5800)
  #define SDIO_BASE           (PERIPH_BASE + 0x18000)
 #endif
 #define DMA2_Channel6_BASE   (AHBPERIPH_BASE + 0x046C)
 #define DMA2_Channel7_BASE   (AHBPERIPH_BASE + 0x0480)
#elif defined (AT32F403xx)
 #define TMR6_BASE            (APB1PERIPH_BASE + 0x1000)
 #define TMR7_BASE            (APB1PERIPH_BASE + 0x1400)
 #define TMR12_BASE           (APB1PERIPH_BASE + 0x1800)
 #define TMR13_BASE           (APB1PERIPH_BASE + 0x1C00)
 #define TMR14_BASE           (APB1PERIPH_BASE + 0x2000)
 #define SPI3_BASE            (APB1PERIPH_BASE + 0x3C00)
 #define SPI4_BASE            (APB1PERIPH_BASE + 0x4000)
 #define I2C3_BASE            (APB1PERIPH_BASE + 0x6800)
 #define DAC_BASE             (APB1PERIPH_BASE + 0x7400)
 #define ADC3_BASE            (APB2PERIPH_BASE + 0x3C00)
 #define TMR15_BASE           (APB2PERIPH_BASE + 0x4000)
 #define SDIO1_BASE           (PERIPH_BASE + 0x18000)
 #define SDIO2_BASE           (AHBPERIPH_BASE + 0x3400)
 #define XMC_Bank1_R_BASE     (XMC_R_BASE + 0x0000) /*!< XMC Bank1 registers base address */
 #define XMC_Bank1E_R_BASE    (XMC_R_BASE + 0x0104) /*!< XMC Bank1E registers base address */
 #define XMC_Bank1E_H_BASE    (XMC_R_BASE + 0x0220) /*!< XMC Bank1H registers base address */
 #define XMC_Bank2_R_BASE     (XMC_R_BASE + 0x0060) /*!< XMC Bank2 registers base address */
 #define XMC_Bank3_R_BASE     (XMC_R_BASE + 0x0080) /*!< XMC Bank3 registers base address */
 #define XMC_Bank4_R_BASE     (XMC_R_BASE + 0x00A0) /*!< XMC Bank4 registers base address */
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define TMR6_BASE            (APB1PERIPH_BASE + 0x1000)
 #define TMR7_BASE            (APB1PERIPH_BASE + 0x1400)
 #define TMR12_BASE           (APB1PERIPH_BASE + 0x1800)
 #define TMR13_BASE           (APB1PERIPH_BASE + 0x1C00)
 #define TMR14_BASE           (APB1PERIPH_BASE + 0x2000)
 #define SPI3_BASE            (APB1PERIPH_BASE + 0x3C00)
 #define SPI4_BASE            (APB1PERIPH_BASE + 0x4000)
 #define CAN2_BASE            (APB1PERIPH_BASE + 0x6800)
 #define DAC_BASE             (APB1PERIPH_BASE + 0x7400)
 #define ADC3_BASE            (APB2PERIPH_BASE + 0x3C00)
 #define ACC_BASE             (APB2PERIPH_BASE + 0x5800)
 #define I2C3_BASE            (APB2PERIPH_BASE + 0x5C00)
 #define USART6_BASE          (APB2PERIPH_BASE + 0x6000)
 #define UART7_BASE           (APB2PERIPH_BASE + 0x6400)
 #define UART8_BASE           (APB2PERIPH_BASE + 0x6800)
 #define I2S2EXT_BASE         (APB2PERIPH_BASE + 0x6C00)
 #define I2S3EXT_BASE         (APB2PERIPH_BASE + 0x7000)
 #define SDIO1_BASE           (PERIPH_BASE + 0x18000)
 #define SDIO2_BASE           (AHBPERIPH_BASE + 0x3400)
 #define DMA2_Channel6_BASE   (AHBPERIPH_BASE + 0x046C)
 #define DMA2_Channel7_BASE   (AHBPERIPH_BASE + 0x0480)
 #define XMC_Bank1_R_BASE     (XMC_R_BASE + 0x0000) /*!< XMC Bank1 registers base address */
 #define XMC_Bank1E_R_BASE    (XMC_R_BASE + 0x0104) /*!< XMC Bank1E registers base address */
 #define XMC_Bank1E_H_BASE    (XMC_R_BASE + 0x0220) /*!< XMC Bank1H registers base address */
 #define XMC_Bank2_R_BASE     (XMC_R_BASE + 0x0060) /*!< XMC Bank2 registers base address */
 #define XMC_Bank3_R_BASE     (XMC_R_BASE + 0x0080) /*!< XMC Bank3 registers base address */
 #define XMC_Bank4_R_BASE     (XMC_R_BASE + 0x00A0) /*!< XMC Bank4 registers base address */
#endif

#if defined (AT32F407xx)
 #define ETH_BASE             (AHBPERIPH_BASE + 0x8000)
 #define ETH_MAC_BASE         (ETH_BASE)
 #define ETH_MMC_BASE         (ETH_BASE + 0x0100)
 #define ETH_PTP_BASE         (ETH_BASE + 0x0700)
 #define ETH_DMA_BASE         (ETH_BASE + 0x1000)
#endif

/**
  * @}
  */

/** @addtogroup Peripheral_declaration
  * @{
  */
#if defined (AT32F415xx)
 #define ACC                ((ACC_Type *) ACC_BASE)
 #define COMP               ((COMP_Type *)COMP_BASE)
 #define SDIO               ((SDIO_Type *) SDIO_BASE)
 #define USBOTG             ((USBOTG_Type *) USBOTG_BASE)
 #define DMA2_Channel6      ((DMA_Channel_Type *) DMA2_Channel6_BASE)
 #define DMA2_Channel7      ((DMA_Channel_Type *) DMA2_Channel7_BASE)
#elif defined (AT32F413xx)
 #if !defined (AT32FEBKCx_MD)
  #define CAN2              ((CAN_Type *) CAN2_BASE)
  #define SDIO              ((SDIO_Type *) SDIO_BASE)
  #define ACC               ((ACC_Type *) ACC_BASE)
 #endif
 #define DMA2_Channel6      ((DMA_Channel_Type *) DMA2_Channel6_BASE)
 #define DMA2_Channel7      ((DMA_Channel_Type *) DMA2_Channel7_BASE)
#elif defined (AT32F403xx)
 #define TMR6               ((TMR_Type *) TMR6_BASE)
 #define TMR7               ((TMR_Type *) TMR7_BASE)
 #define TMR12              ((TMR_Type *) TMR12_BASE)
 #define TMR13              ((TMR_Type *) TMR13_BASE)
 #define TMR14              ((TMR_Type *) TMR14_BASE)
 #define SPI3               ((SPI_Type *) SPI3_BASE)
 #define SPI4               ((SPI_Type *) SPI4_BASE)
 #define I2C3               ((I2C_Type *) I2C3_BASE)
 #define DAC                ((DAC_Type *) DAC_BASE)
 #define GPIOE              ((GPIO_Type *) GPIOE_BASE)
 #define GPIOG              ((GPIO_Type *) GPIOG_BASE)
 #define ADC3               ((ADC_Type *) ADC3_BASE)
 #define TMR15              ((TMR_Type *) TMR15_BASE)
 #define SDIO1              ((SDIO_Type *) SDIO1_BASE)
 #define SDIO2              ((SDIO_Type *) SDIO2_BASE)
 #define XMC_Bank1          ((XMC_Bank1_Type *) XMC_Bank1_R_BASE)
 #define XMC_Bank1E         ((XMC_Bank1Ext_Type *) XMC_Bank1E_R_BASE)
 #define XMC_Bank1H         ((XMC_Bank1Hide_Type *) XMC_Bank1E_H_BASE)
 #define XMC_Bank2          ((XMC_Bank2_Type *) XMC_Bank2_R_BASE)
 #define XMC_Bank3          ((XMC_Bank3_Type *) XMC_Bank3_R_BASE)
 #define XMC_Bank4          ((XMC_Bank4_Type *) XMC_Bank4_R_BASE)
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define TMR6               ((TMR_Type *) TMR6_BASE)
 #define TMR7               ((TMR_Type *) TMR7_BASE)
 #define TMR12              ((TMR_Type *) TMR12_BASE)
 #define TMR13              ((TMR_Type *) TMR13_BASE)
 #define TMR14              ((TMR_Type *) TMR14_BASE)
 #define SPI3               ((SPI_Type *) SPI3_BASE)
 #define SPI4               ((SPI_Type *) SPI4_BASE)
 #define CAN2               ((CAN_Type *) CAN2_BASE)
 #define I2C3               ((I2C_Type *) I2C3_BASE)
 #define DAC                ((DAC_Type *) DAC_BASE)
 #define GPIOE              ((GPIO_Type *) GPIOE_BASE)
 #define ADC3               ((ADC_Type *) ADC3_BASE)
 #define ACC                ((ACC_Type *) ACC_BASE)
 #define USART6             ((USART_Type *) USART6_BASE)
 #define UART7              ((USART_Type *) UART7_BASE)
 #define UART8              ((USART_Type *) UART8_BASE)
 #define I2S2EXT            ((SPI_Type *) I2S2EXT_BASE)
 #define I2S3EXT            ((SPI_Type *) I2S3EXT_BASE)
 #define SDIO1              ((SDIO_Type *) SDIO1_BASE)
 #define SDIO2              ((SDIO_Type *) SDIO2_BASE)
 #define XMC_Bank1          ((XMC_Bank1_Type *) XMC_Bank1_R_BASE)
 #define XMC_Bank1E         ((XMC_Bank1Ext_Type *) XMC_Bank1E_R_BASE)
 #define XMC_Bank1H         ((XMC_Bank1Hide_Type *) XMC_Bank1E_H_BASE)
 #define XMC_Bank2          ((XMC_Bank2_Type *) XMC_Bank2_R_BASE)
 #define XMC_Bank3          ((XMC_Bank3_Type *) XMC_Bank3_R_BASE)
 #define XMC_Bank4          ((XMC_Bank4_Type *) XMC_Bank4_R_BASE)
 #define DMA2_Channel6      ((DMA_Channel_Type *) DMA2_Channel6_BASE)
 #define DMA2_Channel7      ((DMA_Channel_Type *) DMA2_Channel7_BASE)
#endif

#if !defined (AT32F415xx)
 #define TMR8               ((TMR_Type *) TMR8_BASE)
#endif

#define TMR2                ((TMR_Type *) TMR2_BASE)
#define TMR3                ((TMR_Type *) TMR3_BASE)
#define TMR4                ((TMR_Type *) TMR4_BASE)
#define TMR5                ((TMR_Type *) TMR5_BASE)
#if !defined (AT32F415xx)
 #define RTC                ((RTC_Type *) RTC_BASE)
#else
 #define ERTC               ((ERTC_Type *) ERTC_BASE)
#endif
#define WWDG                ((WWDG_Type *) WWDG_BASE)
#define IWDG                ((IWDG_Type *) IWDG_BASE)
#define SPI2                ((SPI_Type *) SPI2_BASE)
#define USART2              ((USART_Type *) USART2_BASE)
#define USART3              ((USART_Type *) USART3_BASE)
#define UART4               ((USART_Type *) UART4_BASE)
#define UART5               ((USART_Type *) UART5_BASE)
#define I2C1                ((I2C_Type *) I2C1_BASE)
#define I2C2                ((I2C_Type *) I2C2_BASE)
#define CAN1                ((CAN_Type *) CAN1_BASE)
#define BKP                 ((BKP_Type *) BKP_BASE)
#define PWR                 ((PWR_Type *) PWR_BASE)
#define AFIO                ((AFIO_Type *) AFIO_BASE)
#define EXTI                ((EXTI_Type *) EXTI_BASE)
#define GPIOA               ((GPIO_Type *) GPIOA_BASE)
#define GPIOB               ((GPIO_Type *) GPIOB_BASE)
#define GPIOC               ((GPIO_Type *) GPIOC_BASE)
#define GPIOD               ((GPIO_Type *) GPIOD_BASE)
#if !defined (AT32F403Axx) && !defined (AT32F407xx)
 #define GPIOF              ((GPIO_Type *) GPIOF_BASE)
#endif
#define ADC1                ((ADC_Type *) ADC1_BASE)
#define ADC2                ((ADC_Type *) ADC2_BASE)
#define TMR1                ((TMR_Type *) TMR1_BASE)
#define SPI1                ((SPI_Type *) SPI1_BASE)
#define USART1              ((USART_Type *) USART1_BASE)
#define TMR9                ((TMR_Type *) TMR9_BASE)
#define TMR10               ((TMR_Type *) TMR10_BASE)
#define TMR11               ((TMR_Type *) TMR11_BASE)
#define DMA1                ((DMA_Type *) DMA1_BASE)
#define DMA2                ((DMA_Type *) DMA2_BASE)
#define DMA1_Channel1       ((DMA_Channel_Type *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_Type *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_Type *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_Type *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_Type *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_Type *) DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_Type *) DMA1_Channel7_BASE)
#define DMA2_Channel1       ((DMA_Channel_Type *) DMA2_Channel1_BASE)
#define DMA2_Channel2       ((DMA_Channel_Type *) DMA2_Channel2_BASE)
#define DMA2_Channel3       ((DMA_Channel_Type *) DMA2_Channel3_BASE)
#define DMA2_Channel4       ((DMA_Channel_Type *) DMA2_Channel4_BASE)
#define DMA2_Channel5       ((DMA_Channel_Type *) DMA2_Channel5_BASE)
#define RCC                 ((RCC_Type *) RCC_BASE)
#define CRC                 ((CRC_Type *) CRC_BASE)
#define FLASH               ((FLASH_Type *) FLASH_R_BASE)
#define UOPTB               ((UOB_Type *) UOB_BASE)
#define DBGMCU              ((MCUDBG_Type *) DBGMCU_BASE)

#if defined (AT32F407xx)
 #define ETH                ((ETH_Type *) ETH_BASE)
#endif

/**
  * @}
  */

/** @addtogroup Exported_constants
  * @{
  */

/** @addtogroup Peripheral_Registers_Bits_Definition
* @{
*/

/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                          CRC calculation unit                              */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for CRC_DT register  *********************/
#define  CRC_DT_DR                              ((uint32_t)0xFFFFFFFF) /*!< Data register bits */


/*******************  Bit definition for CRC_IDT register  ********************/
#define  CRC_IDT_IDR                            ((uint8_t)0xFF)        /*!< General-purpose 8-bit data register bits */


/********************  Bit definition for CRC_CTRL register  ********************/
#define  CRC_CTRL_RST                           ((uint8_t)0x01)        /*!< RESET bit */

/******************************************************************************/
/*                                                                            */
/*                      Analog Comparators (COMP)                             */
/*                                                                            */
/******************************************************************************/

/*********************  Bit definition for COMP_CTRLSTS register  *************/
/* COMP1 bits definition */
#define COMP_CTRLSTS_COMP1EN                    ((uint32_t)0x00000001)        /*!< COMP1 enable */
#define COMP_CTRLSTS_COMP1SW1                   ((uint32_t)0x00000002)        /*!< SW1 switch control */
#define COMP_CTRLSTS_COMP1MDE                   ((uint32_t)0x0000000C)        /*!< COMP1 power mode */
#define COMP_CTRLSTS_COMP1MDE_0                 ((uint32_t)0x00000004)        /*!< COMP1 power mode bit 0 */
#define COMP_CTRLSTS_COMP1MDE_1                 ((uint32_t)0x00000008)        /*!< COMP1 power mode bit 1 */
#define COMP_CTRLSTS_COMP1INSEL                 ((uint32_t)0x00000070)        /*!< COMP1 inverting input select */
#define COMP_CTRLSTS_COMP1INSEL_0               ((uint32_t)0x00000010)        /*!< COMP1 inverting input select bit 0 */
#define COMP_CTRLSTS_COMP1INSEL_1               ((uint32_t)0x00000020)        /*!< COMP1 inverting input select bit 1 */
#define COMP_CTRLSTS_COMP1INSEL_2               ((uint32_t)0x00000040)        /*!< COMP1 inverting input select bit 2 */
#define COMP_CTRLSTS_COMP1OUTSEL                ((uint32_t)0x00000700)        /*!< COMP1 output select */
#define COMP_CTRLSTS_COMP1OUTSEL_0              ((uint32_t)0x00000100)        /*!< COMP1 output select bit 0 */
#define COMP_CTRLSTS_COMP1OUTSEL_1              ((uint32_t)0x00000200)        /*!< COMP1 output select bit 1 */
#define COMP_CTRLSTS_COMP1OUTSEL_2              ((uint32_t)0x00000400)        /*!< COMP1 output select bit 2 */
#define COMP_CTRLSTS_COMP1POL                   ((uint32_t)0x00000800)        /*!< COMP1 output polarity */
#define COMP_CTRLSTS_COMP1HYST                  ((uint32_t)0x00003000)        /*!< COMP1 hysteresis */
#define COMP_CTRLSTS_COMP1HYST_0                ((uint32_t)0x00001000)        /*!< COMP1 hysteresis bit 0 */
#define COMP_CTRLSTS_COMP1HYST_1                ((uint32_t)0x00002000)        /*!< COMP1 hysteresis bit 1 */
#define COMP_CTRLSTS_COMP1OUT                   ((uint32_t)0x00004000)        /*!< COMP1 output level */
#define COMP_CTRLSTS_COMP1LOCK                  ((uint32_t)0x00008000)        /*!< COMP1 lock */
/* COMP2 bits definition */
#define COMP_CTRLSTS_COMP2EN                    ((uint32_t)0x00010000)        /*!< COMP2 enable */
#define COMP_CTRLSTS_COMP2MDE                   ((uint32_t)0x000C0000)        /*!< COMP2 power mode */
#define COMP_CTRLSTS_COMP2MDE_0                 ((uint32_t)0x00040000)        /*!< COMP2 power mode bit 0 */
#define COMP_CTRLSTS_COMP2MDE_1                 ((uint32_t)0x00080000)        /*!< COMP2 power mode bit 1 */
#define COMP_CTRLSTS_COMP2INSEL                 ((uint32_t)0x00700000)        /*!< COMP2 inverting input select */
#define COMP_CTRLSTS_COMP2INSEL_0               ((uint32_t)0x00100000)        /*!< COMP2 inverting input select bit 0 */
#define COMP_CTRLSTS_COMP2INSEL_1               ((uint32_t)0x00200000)        /*!< COMP2 inverting input select bit 1 */
#define COMP_CTRLSTS_COMP2INSEL_2               ((uint32_t)0x00400000)        /*!< COMP2 inverting input select bit 2 */
#define COMP_CTRLSTS_WNDWEN                     ((uint32_t)0x00800000)        /*!< Comparators window mode enable */
#define COMP_CTRLSTS_COMP2OUTSEL                ((uint32_t)0x07000000)        /*!< COMP2 output select */
#define COMP_CTRLSTS_COMP2OUTSEL_0              ((uint32_t)0x01000000)        /*!< COMP2 output select bit 0 */
#define COMP_CTRLSTS_COMP2OUTSEL_1              ((uint32_t)0x02000000)        /*!< COMP2 output select bit 1 */
#define COMP_CTRLSTS_COMP2OUTSEL_2              ((uint32_t)0x04000000)        /*!< COMP2 output select bit 2 */
#define COMP_CTRLSTS_COMP2POL                   ((uint32_t)0x08000000)        /*!< COMP2 output polarity */
#define COMP_CTRLSTS_COMP2HYST                  ((uint32_t)0x30000000)        /*!< COMP2 hysteresis */
#define COMP_CTRLSTS_COMP2HYST_0                ((uint32_t)0x10000000)        /*!< COMP2 hysteresis bit 0 */
#define COMP_CTRLSTS_COMP2HYST_1                ((uint32_t)0x20000000)        /*!< COMP2 hysteresis bit 1 */
#define COMP_CTRLSTS_COMP2OUT                   ((uint32_t)0x40000000)        /*!< COMP2 output level */
#define COMP_CTRLSTS_COMP2LOCK                  ((uint32_t)0x80000000)        /*!< COMP2 lock */

/***************  Bit definition for COMP_G_FILTER_EN register  ***************/
#define COMP_G_FILTER_EN_GFE                    ((uint16_t)0x0001)            /*!< Comparators Glitch filter enable */

/******************************************************************************/
/*                                                                            */
/*                             Power Control                                  */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for PWR_CTRL register  ********************/
#define  PWR_CTRL_PDDS                          ((uint16_t)0x0002)            /*!< Power Down Deepsleep */
#define  PWR_CTRL_CLWUF                         ((uint16_t)0x0004)            /*!< Clear Wakeup Flag */
#define  PWR_CTRL_CLSBF                         ((uint16_t)0x0008)            /*!< Clear Standby Flag */
#define  PWR_CTRL_PVDEN                         ((uint16_t)0x0010)            /*!< Power Voltage Detector Enable */

#define  PWR_CTRL_PVDS                          ((uint16_t)0x00E0)            /*!< PLS[2:0] bits (PVD Level Selection) */
#define  PWR_CTRL_PVDS_0                        ((uint16_t)0x0020)            /*!< Bit 0 */
#define  PWR_CTRL_PVDS_1                        ((uint16_t)0x0040)            /*!< Bit 1 */
#define  PWR_CTRL_PVDS_2                        ((uint16_t)0x0080)            /*!< Bit 2 */

/** PVD level configuration */                                                
#define  PWR_CTRL_PVDS_2V2                      ((uint16_t)0x0000)            /*!< PVD level 2.2V */
#define  PWR_CTRL_PVDS_2V3                      ((uint16_t)0x0020)            /*!< PVD level 2.3V */
#define  PWR_CTRL_PVDS_2V4                      ((uint16_t)0x0040)            /*!< PVD level 2.4V */
#define  PWR_CTRL_PVDS_2V5                      ((uint16_t)0x0060)            /*!< PVD level 2.5V */
#define  PWR_CTRL_PVDS_2V6                      ((uint16_t)0x0080)            /*!< PVD level 2.6V */
#define  PWR_CTRL_PVDS_2V7                      ((uint16_t)0x00A0)            /*!< PVD level 2.7V */
#define  PWR_CTRL_PVDS_2V8                      ((uint16_t)0x00C0)            /*!< PVD level 2.8V */
#define  PWR_CTRL_PVDS_2V9                      ((uint16_t)0x00E0)            /*!< PVD level 2.9V */

#define  PWR_CTRL_DBP                           ((uint16_t)0x0100)            /*!< Disable Backup Domain write protection */

/*******************  Bit definition for PWR_CTRLSTS register  ********************/
#define  PWR_CTRLSTS_WUF                        ((uint16_t)0x0001)            /*!< Wakeup Flag */
#define  PWR_CTRLSTS_SBF                        ((uint16_t)0x0002)            /*!< Standby Flag */
#define  PWR_CTRLSTS_PVD                        ((uint16_t)0x0004)            /*!< PVD Output */
#define  PWR_CTRLSTS_WUPEN                      ((uint16_t)0x0100)            /*!< Enable WKUP pin */

/******************************************************************************/
/*                                                                            */
/*                            Backup registers                                */
/*                                                                            */
/******************************************************************************/
#if !defined (AT32F415xx)
/*******************  Bit definition for BKP_DT1 register  ********************/
#define  BKP_DT1_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT2 register  ********************/
#define  BKP_DT2_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT3 register  ********************/
#define  BKP_DT3_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT4 register  ********************/
#define  BKP_DT4_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT5 register  ********************/
#define  BKP_DT5_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT6 register  ********************/
#define  BKP_DT6_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT7 register  ********************/
#define  BKP_DT7_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT8 register  ********************/
#define  BKP_DT8_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT9 register  ********************/
#define  BKP_DT9_D                              ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT10 register  *******************/
#define  BKP_DT10_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT11 register  *******************/
#define  BKP_DT11_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT12 register  *******************/
#define  BKP_DT12_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT13 register  *******************/
#define  BKP_DT13_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT14 register  *******************/
#define  BKP_DT14_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT15 register  *******************/
#define  BKP_DT15_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT16 register  *******************/
#define  BKP_DT16_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT17 register  *******************/
#define  BKP_DT17_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/******************  Bit definition for BKP_DT18 register  ********************/
#define  BKP_DT18_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT19 register  *******************/
#define  BKP_DT19_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT20 register  *******************/
#define  BKP_DT20_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT21 register  *******************/
#define  BKP_DT21_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT22 register  *******************/
#define  BKP_DT22_D                             ((uint16_t)0xFFFF)           /*!< Backup data */

/*******************  Bit definition for BKP_DT23 register  *******************/
#define  BKP_DT23_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT24 register  *******************/
#define  BKP_DT24_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT25 register  *******************/
#define  BKP_DT25_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT26 register  *******************/
#define  BKP_DT26_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT27 register  *******************/
#define  BKP_DT27_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT28 register  *******************/
#define  BKP_DT28_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT29 register  *******************/
#define  BKP_DT29_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT30 register  *******************/
#define  BKP_DT30_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT31 register  *******************/
#define  BKP_DT31_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT32 register  *******************/
#define  BKP_DT32_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT33 register  *******************/
#define  BKP_DT33_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT34 register  *******************/
#define  BKP_DT34_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT35 register  *******************/
#define  BKP_DT35_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT36 register  *******************/
#define  BKP_DT36_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT37 register  *******************/
#define  BKP_DT37_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT38 register  *******************/
#define  BKP_DT38_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT39 register  *******************/
#define  BKP_DT39_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT40 register  *******************/
#define  BKP_DT40_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT41 register  *******************/
#define  BKP_DT41_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/*******************  Bit definition for BKP_DT42 register  *******************/
#define  BKP_DT42_D                             ((uint16_t)0xFFFF)            /*!< Backup data */

/******************  Bit definition for BKP_RTCCAL register  *******************/
#define  BKP_RTCCAL_CAL                         ((uint16_t)0x007F)            /*!< Calibration value */
#define  BKP_RTCCAL_OT1CAL                      ((uint16_t)0x0080)            /*!< Calibration Clock Output */
#define  BKP_RTCCAL_OT2EN                       ((uint16_t)0x0100)            /*!< Alarm or Second Output Enable */
#define  BKP_RTCCAL_OT2SEL                      ((uint16_t)0x0200)            /*!< Alarm or Second Output Selection */

/********************  Bit definition for BKP_CTRL register  ********************/
#define  BKP_CTRL_TPEN                          ((uint8_t)0x01)               /*!< TAMPER pin enable */
#define  BKP_CTRL_TPALV                         ((uint8_t)0x02)               /*!< TAMPER pin active level */

/*******************  Bit definition for BKP_CTRLSTS register  ********************/
#define  BKP_CTRLSTS_CTPEF                      ((uint16_t)0x0001)            /*!< Clear Tamper event */
#define  BKP_CTRLSTS_CTPIF                      ((uint16_t)0x0002)            /*!< Clear Tamper Interrupt */
#define  BKP_CTRLSTS_TPIEN                      ((uint16_t)0x0004)            /*!< TAMPER Pin interrupt enable */
#define  BKP_CTRLSTS_TPEF                       ((uint16_t)0x0100)            /*!< Tamper Event Flag */
#define  BKP_CTRLSTS_TPIF                       ((uint16_t)0x0200)            /*!< Tamper Interrupt Flag */
#endif
/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for RCC_CTRL register  ********************/
#define  RCC_CTRL_HSIEN                         ((uint32_t)0x00000001)        /*!< Internal High Speed clock enable */
#define  RCC_CTRL_HSISTBL                       ((uint32_t)0x00000002)        /*!< Internal High Speed clock ready flag */
#if defined (AT32F403xx)
 #define  RCC_CTRL_HSITWK                       ((uint32_t)0x000000F8)        /*!< Internal High Speed clock trimming */
#else
 #define  RCC_CTRL_HSITWK                       ((uint32_t)0x000000FE)        /*!< Internal High Speed clock trimming */
#endif
#define  RCC_CTRL_HSICAL                        ((uint32_t)0x0000FF00)        /*!< Internal High Speed clock Calibration */
#define  RCC_CTRL_HSEEN                         ((uint32_t)0x00010000)        /*!< External High Speed clock enable */
#define  RCC_CTRL_HSESTBL                       ((uint32_t)0x00020000)        /*!< External High Speed clock ready flag */
#define  RCC_CTRL_HSEBYPS                       ((uint32_t)0x00040000)        /*!< External High Speed clock Bypass */
#define  RCC_CTRL_HSECFDEN                      ((uint32_t)0x00080000)        /*!< Clock Security System enable */
#define  RCC_CTRL_PLLEN                         ((uint32_t)0x01000000)        /*!< PLL enable */
#define  RCC_CTRL_PLLSTBL                       ((uint32_t)0x02000000)        /*!< PLL clock ready flag */

/*******************  Bit definition for RCC_CFG register  *******************/
/** SYSCLKSEL configuration */
#define  RCC_CFG_SYSCLKSEL                      ((uint32_t)0x00000003)        /*!< SYSCLKSEL[1:0] bits (System clock Switch) */
#define  RCC_CFG_SYSCLKSEL_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFG_SYSCLKSEL_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  RCC_CFG_SYSCLKSEL_HSI                  ((uint32_t)0x00000000)        /*!< HSI selected as system clock */
#define  RCC_CFG_SYSCLKSEL_HSE                  ((uint32_t)0x00000001)        /*!< HSE selected as system clock */
#define  RCC_CFG_SYSCLKSEL_PLL                  ((uint32_t)0x00000002)        /*!< PLL selected as system clock */

/** SYSCLKSTST configuration */
#define  RCC_CFG_SYSCLKSTS                      ((uint32_t)0x0000000C)        /*!< SYSCLKSTST[1:0] bits (System Clock Switch Status) */
#define  RCC_CFG_SYSCLKSTS_0                    ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  RCC_CFG_SYSCLKSTS_1                    ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  RCC_CFG_SYSCLKSTS_HSI                  ((uint32_t)0x00000000)        /*!< HSI oscillator used as system clock */
#define  RCC_CFG_SYSCLKSTS_HSE                  ((uint32_t)0x00000004)        /*!< HSE oscillator used as system clock */
#define  RCC_CFG_SYSCLKSTS_PLL                  ((uint32_t)0x00000008)        /*!< PLL used as system clock */

/** AHBPSC configuration */
#define  RCC_CFG_AHBPSC                         ((uint32_t)0x000000F0)        /*!< AHBPSC[3:0] bits (AHB prescaler) */
#define  RCC_CFG_AHBPSC_0                       ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  RCC_CFG_AHBPSC_1                       ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  RCC_CFG_AHBPSC_2                       ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  RCC_CFG_AHBPSC_3                       ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  RCC_CFG_AHBPSC_DIV1                    ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFG_AHBPSC_DIV2                    ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFG_AHBPSC_DIV4                    ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFG_AHBPSC_DIV8                    ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFG_AHBPSC_DIV16                   ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFG_AHBPSC_DIV64                   ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFG_AHBPSC_DIV128                  ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFG_AHBPSC_DIV256                  ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFG_AHBPSC_DIV512                  ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

/** APB1PSC configuration */
#define  RCC_CFG_APB1PSC                        ((uint32_t)0x00000700)        /*!< PRE1[2:0] bits (APB1 prescaler) */
#define  RCC_CFG_APB1PSC_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_CFG_APB1PSC_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  RCC_CFG_APB1PSC_2                      ((uint32_t)0x00000400)        /*!< Bit 2 */

#define  RCC_CFG_APB1PSC_DIV1                   ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFG_APB1PSC_DIV2                   ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFG_APB1PSC_DIV4                   ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFG_APB1PSC_DIV8                   ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFG_APB1PSC_DIV16                  ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

/** APB2PSC configuration */
#define  RCC_CFG_APB2PSC                        ((uint32_t)0x00003800)        /*!< PRE2[2:0] bits (APB2 prescaler) */
#define  RCC_CFG_APB2PSC_0                      ((uint32_t)0x00000800)        /*!< Bit 0 */
#define  RCC_CFG_APB2PSC_1                      ((uint32_t)0x00001000)        /*!< Bit 1 */
#define  RCC_CFG_APB2PSC_2                      ((uint32_t)0x00002000)        /*!< Bit 2 */

#define  RCC_CFG_APB2PSC_DIV1                   ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFG_APB2PSC_DIV2                   ((uint32_t)0x00002000)        /*!< HCLK divided by 2 */
#define  RCC_CFG_APB2PSC_DIV4                   ((uint32_t)0x00002800)        /*!< HCLK divided by 4 */
#define  RCC_CFG_APB2PSC_DIV8                   ((uint32_t)0x00003000)        /*!< HCLK divided by 8 */
#define  RCC_CFG_APB2PSC_DIV16                  ((uint32_t)0x00003800)        /*!< HCLK divided by 16 */

#define  RCC_CFG_PLLRC                          ((uint32_t)0x00010000)        /*!< PLL entry clock source */
#define  RCC_CFG_PLLHSEPSC                      ((uint32_t)0x00020000)        /*!< HSE divider for PLL entry */


/** ADCPSC configuration */
#define  RCC_CFG_ADCPSC                         ((uint32_t)0x1000C000)        /*!< ADCPSC[1:0] bits (ADC prescaler) */
#define  RCC_CFG_ADCPSC_0                       ((uint32_t)0x00004000)        /*!< Bit 0 */
#define  RCC_CFG_ADCPSC_1                       ((uint32_t)0x00008000)        /*!< Bit 1 */
#define  RCC_CFG_ADCPSC_2                       ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  RCC_CFG_ADCPSC_DIV2                    ((uint32_t)0x00000000)        /*!< PCLK2 divided by 2 */
#define  RCC_CFG_ADCPSC_DIV4                    ((uint32_t)0x00004000)        /*!< PCLK2 divided by 4 */
#define  RCC_CFG_ADCPSC_DIV6                    ((uint32_t)0x00008000)        /*!< PCLK2 divided by 6 */
#define  RCC_CFG_ADCPSC_DIV8                    ((uint32_t)0x0000C000)        /*!< PCLK2 divided by 8 */
#define  RCC_CFG_ADCPSC_DIV12                   ((uint32_t)0x10004000)        /*!< PCLK2 divided by 12 */
#define  RCC_CFG_ADCPSC_DIV16                   ((uint32_t)0x1000C000)        /*!< PCLK2 divided by 16 */

#define  RCC_CFG_PLLCFG_MASK                    ((uint32_t)0x1FC0FFFF)        /*!< Mask for PLLRANGE, PLLHSEPSC, PLLMULT, PLLRC */


/** PLLMULT configuration */
#define  RCC_CFG_PLLMULT                        ((uint32_t)0x603C0000)        /*!< PLLMUL[5:0] bits (PLL multiplication factor) */
#define  RCC_CFG_PLLMULT_0                      ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  RCC_CFG_PLLMULT_1                      ((uint32_t)0x00080000)        /*!< Bit 1 */
#define  RCC_CFG_PLLMULT_2                      ((uint32_t)0x00100000)        /*!< Bit 2 */
#define  RCC_CFG_PLLMULT_3                      ((uint32_t)0x00200000)        /*!< Bit 3 */
#define  RCC_CFG_PLLMULT_4                      ((uint32_t)0x20000000)        /*!< Bit 4 */
#define  RCC_CFG_PLLMULT_5                      ((uint32_t)0x40000000)        /*!< Bit 5 */
#define  RCC_CFG_PLLMULT_LB_MASK                ((uint32_t)0x003C0000)
#define  RCC_CFG_PLLMULT_HB_MASK                ((uint32_t)0x60000000)
#define  RCC_CFG_PLLMULT_LB_POS                 ((uint32_t)18)
#define  RCC_CFG_PLLMULT_HB_POS                 ((uint32_t)29)
#define  RCC_CFG_PLLMULT_HB_OFFSET              ((uint32_t)4)


#define  RCC_CFG_PLLRANGE                       ((uint32_t)0x80000000)        /*!< PLL Frequency range.  */
#define  RCC_CFG_PLLRANGE_LE72MHZ               ((uint32_t)0x00000000)        /*!< When PLL frequency is less than or equal to 72MHz */
#define  RCC_CFG_PLLRANGE_GT72MHZ               ((uint32_t)0x80000000)        /*!< When PLL frequency is greater than 72MHz */

#define  RCC_CFG_PLLRC_HSI_DIV2                 ((uint32_t)0x00000000)        /*!< HSI clock divided by 2 selected as PLL entry clock source */
#define  RCC_CFG_PLLRC_HSE                      ((uint32_t)0x00010000)        /*!< HSE clock selected as PLL entry clock source */

#define  RCC_CFG_PLLHSEPSC_HSE                  ((uint32_t)0x00000000)        /*!< HSE clock not divided for PLL entry */
#define  RCC_CFG_PLLHSEPSC_HSE_DIV2             ((uint32_t)0x00020000)        /*!< HSE clock divided by 2 for PLL entry */

#define  RCC_CFG_PLLMULT2                       ((uint32_t)0x00000000)        /*!< PLL input clock*2 */
#define  RCC_CFG_PLLMULT3                       ((uint32_t)0x00040000)        /*!< PLL input clock*3 */
#define  RCC_CFG_PLLMULT4                       ((uint32_t)0x00080000)        /*!< PLL input clock*4 */
#define  RCC_CFG_PLLMULT5                       ((uint32_t)0x000C0000)        /*!< PLL input clock*5 */
#define  RCC_CFG_PLLMULT6                       ((uint32_t)0x00100000)        /*!< PLL input clock*6 */
#define  RCC_CFG_PLLMULT7                       ((uint32_t)0x00140000)        /*!< PLL input clock*7 */
#define  RCC_CFG_PLLMULT8                       ((uint32_t)0x00180000)        /*!< PLL input clock*8 */
#define  RCC_CFG_PLLMULT9                       ((uint32_t)0x001C0000)        /*!< PLL input clock*9 */
#define  RCC_CFG_PLLMULT10                      ((uint32_t)0x00200000)        /*!< PLL input clock*10 */
#define  RCC_CFG_PLLMULT11                      ((uint32_t)0x00240000)        /*!< PLL input clock*11 */
#define  RCC_CFG_PLLMULT12                      ((uint32_t)0x00280000)        /*!< PLL input clock*12 */
#define  RCC_CFG_PLLMULT13                      ((uint32_t)0x002C0000)        /*!< PLL input clock*13 */
#define  RCC_CFG_PLLMULT14                      ((uint32_t)0x00300000)        /*!< PLL input clock*14 */
#define  RCC_CFG_PLLMULT15                      ((uint32_t)0x00340000)        /*!< PLL input clock*15 */
#define  RCC_CFG_PLLMULT16                      ((uint32_t)0x00380000)        /*!< PLL input clock*16 */

#define  RCC_CFG_PLLMULT17                      ((uint32_t)0x20000000)        /*!< PLL input clock*17 */
#define  RCC_CFG_PLLMULT18                      ((uint32_t)0x20040000)        /*!< PLL input clock*18 */
#define  RCC_CFG_PLLMULT19                      ((uint32_t)0x20080000)        /*!< PLL input clock*19 */
#define  RCC_CFG_PLLMULT20                      ((uint32_t)0x200C0000)        /*!< PLL input clock*20 */
#define  RCC_CFG_PLLMULT21                      ((uint32_t)0x20100000)        /*!< PLL input clock*21 */
#define  RCC_CFG_PLLMULT22                      ((uint32_t)0x20140000)        /*!< PLL input clock*22 */
#define  RCC_CFG_PLLMULT23                      ((uint32_t)0x20180000)        /*!< PLL input clock*23 */
#define  RCC_CFG_PLLMULT24                      ((uint32_t)0x201C0000)        /*!< PLL input clock*24 */
#define  RCC_CFG_PLLMULT25                      ((uint32_t)0x20200000)        /*!< PLL input clock*25 */
#define  RCC_CFG_PLLMULT26                      ((uint32_t)0x20240000)        /*!< PLL input clock*26 */
#define  RCC_CFG_PLLMULT27                      ((uint32_t)0x20280000)        /*!< PLL input clock*27 */
#define  RCC_CFG_PLLMULT28                      ((uint32_t)0x202C0000)        /*!< PLL input clock*28 */
#define  RCC_CFG_PLLMULT29                      ((uint32_t)0x20300000)        /*!< PLL input clock*29 */
#define  RCC_CFG_PLLMULT30                      ((uint32_t)0x20340000)        /*!< PLL input clock*30 */
#define  RCC_CFG_PLLMULT31                      ((uint32_t)0x20380000)        /*!< PLL input clock*31 */
#define  RCC_CFG_PLLMULT32                      ((uint32_t)0x203C0000)        /*!< PLL input clock*32 */
#define  RCC_CFG_PLLMULT33                      ((uint32_t)0x40000000)        /*!< PLL input clock*33 */
#define  RCC_CFG_PLLMULT34                      ((uint32_t)0x40040000)        /*!< PLL input clock*34 */
#define  RCC_CFG_PLLMULT35                      ((uint32_t)0x40080000)        /*!< PLL input clock*35 */
#define  RCC_CFG_PLLMULT36                      ((uint32_t)0x400C0000)        /*!< PLL input clock*36 */
#define  RCC_CFG_PLLMULT37                      ((uint32_t)0x40100000)        /*!< PLL input clock*37 */
#define  RCC_CFG_PLLMULT38                      ((uint32_t)0x40140000)        /*!< PLL input clock*38 */
#define  RCC_CFG_PLLMULT39                      ((uint32_t)0x40180000)        /*!< PLL input clock*39 */
#define  RCC_CFG_PLLMULT40                      ((uint32_t)0x401C0000)        /*!< PLL input clock*40 */
#define  RCC_CFG_PLLMULT41                      ((uint32_t)0x40200000)        /*!< PLL input clock*41 */
#define  RCC_CFG_PLLMULT42                      ((uint32_t)0x40240000)        /*!< PLL input clock*42 */
#define  RCC_CFG_PLLMULT43                      ((uint32_t)0x40280000)        /*!< PLL input clock*43 */
#define  RCC_CFG_PLLMULT44                      ((uint32_t)0x402C0000)        /*!< PLL input clock*44 */
#define  RCC_CFG_PLLMULT45                      ((uint32_t)0x40300000)        /*!< PLL input clock*45 */
#define  RCC_CFG_PLLMULT46                      ((uint32_t)0x40340000)        /*!< PLL input clock*46 */
#define  RCC_CFG_PLLMULT47                      ((uint32_t)0x40380000)        /*!< PLL input clock*47 */
#define  RCC_CFG_PLLMULT48                      ((uint32_t)0x403C0000)        /*!< PLL input clock*48 */
#define  RCC_CFG_PLLMULT49                      ((uint32_t)0x60000000)        /*!< PLL input clock*49 */
#define  RCC_CFG_PLLMULT50                      ((uint32_t)0x60040000)        /*!< PLL input clock*50 */
#define  RCC_CFG_PLLMULT51                      ((uint32_t)0x60080000)        /*!< PLL input clock*51 */
#define  RCC_CFG_PLLMULT52                      ((uint32_t)0x600C0000)        /*!< PLL input clock*52 */
#define  RCC_CFG_PLLMULT53                      ((uint32_t)0x60100000)        /*!< PLL input clock*53 */
#define  RCC_CFG_PLLMULT54                      ((uint32_t)0x60140000)        /*!< PLL input clock*54 */
#define  RCC_CFG_PLLMULT55                      ((uint32_t)0x60180000)        /*!< PLL input clock*55 */
#define  RCC_CFG_PLLMULT56                      ((uint32_t)0x601C0000)        /*!< PLL input clock*56 */
#define  RCC_CFG_PLLMULT57                      ((uint32_t)0x60200000)        /*!< PLL input clock*57 */
#define  RCC_CFG_PLLMULT58                      ((uint32_t)0x60240000)        /*!< PLL input clock*58 */
#define  RCC_CFG_PLLMULT59                      ((uint32_t)0x60280000)        /*!< PLL input clock*59 */
#define  RCC_CFG_PLLMULT60                      ((uint32_t)0x602C0000)        /*!< PLL input clock*60 */
#define  RCC_CFG_PLLMULT61                      ((uint32_t)0x60300000)        /*!< PLL input clock*61 */
#define  RCC_CFG_PLLMULT62                      ((uint32_t)0x60340000)        /*!< PLL input clock*62 */
#define  RCC_CFG_PLLMULT63                      ((uint32_t)0x60380000)        /*!< PLL input clock*63 */
#define  RCC_CFG_PLLMULT64                      ((uint32_t)0x603C0000)        /*!< PLL input clock*64 */

#define  RCC_CFG_USBPSC                         ((uint32_t)0x08C00000)        /*!< USB Device prescaler */
#define  RCC_CFG_USBPSC_0                       ((uint32_t)0x00400000)        /*!< Bit 0 */
#define  RCC_CFG_USBPSC_1                       ((uint32_t)0x00800000)        /*!< Bit 1 */
#define  RCC_CFG_USBPSC_2                       ((uint32_t)0x08000000)        /*!< Bit 2 */
#define  RCC_CFG_USBPSC_DIV1_5                  ((uint32_t)0x00000000)        /*!< SYSCLK divided by 1.5 selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV1                    ((uint32_t)0x00400000)        /*!< SYSCLK selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV2_5                  ((uint32_t)0x00800000)        /*!< SYSCLK divided by 2.5 selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV2                    ((uint32_t)0x00C00000)        /*!< SYSCLK divided by 2 selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV3_5                  ((uint32_t)0x08000000)        /*!< SYSCLK divided by 3.5 selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV3                    ((uint32_t)0x08400000)        /*!< SYSCLK divided by 3 selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV4                    ((uint32_t)0x08800000)        /*!< SYSCLK divided by 4 selected as USB clock source */
#define  RCC_CFG_USBPSC_DIV4_0                  ((uint32_t)0x08C00000)        /*!< SYSCLK divided by 4 selected as USB clock source */

/** CLKOUT configuration */
#define  RCC_CFG_CLKOUT                         ((uint32_t)0x07000000)        /*!< CLKOUT[2:0] bits (Microcontroller Clock Output) */
#define  RCC_CFG_CLKOUT_0                       ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  RCC_CFG_CLKOUT_1                       ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  RCC_CFG_CLKOUT_2                       ((uint32_t)0x04000000)        /*!< Bit 2 */

#define  RCC_CFG_CLKOUT_NOCLK                   ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_CFG_CLKOUT_SYSCLK                  ((uint32_t)0x04000000)        /*!< System clock selected as CLKOUT source */
#define  RCC_CFG_CLKOUT_HSI                     ((uint32_t)0x05000000)        /*!< HSI clock selected as CLKOUT source */
#define  RCC_CFG_CLKOUT_HSE                     ((uint32_t)0x06000000)        /*!< HSE clock selected as CLKOUT source  */
#define  RCC_CFG_CLKOUT_PLL_DIV2                ((uint32_t)0x07000000)        /*!< PLL clock divided by 2 selected as CLKOUT source */

/********************  Bit definition for RCC_CLKINT register  ********************/
#define  RCC_CLKINT_LSISTBLF                    ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt flag */
#define  RCC_CLKINT_LSESTBLF                    ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt flag */
#define  RCC_CLKINT_HSISTBLF                    ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt flag */
#define  RCC_CLKINT_HSESTBLF                    ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt flag */
#define  RCC_CLKINT_PLLSTBLF                    ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt flag */
#define  RCC_CLKINT_HSECFDF                     ((uint32_t)0x00000080)        /*!< Clock Security System Interrupt flag */
#define  RCC_CLKINT_LSISTBLIE                   ((uint32_t)0x00000100)        /*!< LSI Ready Interrupt Enable */
#define  RCC_CLKINT_LSESTBLIE                   ((uint32_t)0x00000200)        /*!< LSE Ready Interrupt Enable */
#define  RCC_CLKINT_HSISTBLIE                   ((uint32_t)0x00000400)        /*!< HSI Ready Interrupt Enable */
#define  RCC_CLKINT_HSESTBLIE                   ((uint32_t)0x00000800)        /*!< HSE Ready Interrupt Enable */
#define  RCC_CLKINT_PLLSTBLIE                   ((uint32_t)0x00001000)        /*!< PLL Ready Interrupt Enable */
#define  RCC_CLKINT_LSISTBLFC                   ((uint32_t)0x00010000)        /*!< LSI Ready Interrupt Clear */
#define  RCC_CLKINT_LSESTBLFC                   ((uint32_t)0x00020000)        /*!< LSE Ready Interrupt Clear */
#define  RCC_CLKINT_HSISTBLFC                   ((uint32_t)0x00040000)        /*!< HSI Ready Interrupt Clear */
#define  RCC_CLKINT_HSESTBLFC                   ((uint32_t)0x00080000)        /*!< HSE Ready Interrupt Clear */
#define  RCC_CLKINT_PLLSTBLFC                   ((uint32_t)0x00100000)        /*!< PLL Ready Interrupt Clear */
#define  RCC_CLKINT_HSECFDFC                    ((uint32_t)0x00800000)        /*!< Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2RST register  *****************/
#define  RCC_APB2RST_AFIORST                    ((uint32_t)0x00000001)        /*!< Alternate Function I/O reset */
#define  RCC_APB2RST_GPIOARST                   ((uint32_t)0x00000004)        /*!< I/O port A reset */
#define  RCC_APB2RST_GPIOBRST                   ((uint32_t)0x00000008)        /*!< I/O port B reset */
#define  RCC_APB2RST_GPIOCRST                   ((uint32_t)0x00000010)        /*!< I/O port C reset */
#define  RCC_APB2RST_GPIODRST                   ((uint32_t)0x00000020)        /*!< I/O port D reset */
#define  RCC_APB2RST_ADC1RST                    ((uint32_t)0x00000200)        /*!< ADC 1 interface reset */
#define  RCC_APB2RST_TMR1RST                    ((uint32_t)0x00000800)        /*!< TMR1 Timer reset */
#define  RCC_APB2RST_SPI1RST                    ((uint32_t)0x00001000)        /*!< SPI 1 reset */
#define  RCC_APB2RST_USART1RST                  ((uint32_t)0x00004000)        /*!< USART1 reset */

#if !defined (AT32F415xx)
 #define  RCC_APB2RST_ADC2RST                   ((uint32_t)0x00000400)        /*!< ADC 2 interface reset */
#endif

#if !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F413Cx_MD) && !defined (AT32F413Rx_MD) && \
	!defined (AT32FEBKCx_MD) && !defined (TS32F401CBU7)  && \
    !defined (AT32F415xx)
 #define  RCC_APB2RST_TMR8RST                   ((uint32_t)0x00002000)        /*!< TMR8 Timer reset */
#endif

#if !defined (AT32F403Axx) || !defined (AT32F407xx)
 #define  RCC_APB2RST_GPIOFRST                  ((uint32_t)0x00000080)        /*!< I/O port F reset */
#endif

#if !defined (AT32FEBKCx_MD)
 #define  RCC_APB2RST_TMR9RST                   ((uint32_t)0x00080000)         /*!< TMR9 Timer reset */
 #define  RCC_APB2RST_TMR10RST                  ((uint32_t)0x00100000)         /*!< TMR10 Timer reset */
 #define  RCC_APB2RST_TMR11RST                  ((uint32_t)0x00200000)         /*!< TMR11 Timer reset */
#endif

#if defined (AT32F403xx)
 #define  RCC_APB2RST_GPIOERST                  ((uint32_t)0x00000040)        /*!< I/O port E reset */
 #define  RCC_APB2RST_GPIOGRST                  ((uint32_t)0x00000100)        /*!< I/O port G reset */
 #define  RCC_APB2RST_ADC3RST                   ((uint32_t)0x00008000)        /*!< ADC3 interface reset */
 #define  RCC_APB2RST_TMR15RST                  ((uint32_t)0x00010000)        /*!< TMR15 Timer reset */
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define  RCC_APB2RST_GPIOERST                  ((uint32_t)0x00000040)        /*!< I/O port E reset */
 #define  RCC_APB2RST_ADC3RST                   ((uint32_t)0x00008000)        /*!< ADC3 interface reset */
 #define  RCC_APB2RST_I2C3RST                   ((uint32_t)0x00800000)        /*!< I2C3 interface reset */
 #define  RCC_APB2RST_USART6RST                 ((uint32_t)0x01000000)        /*!< USART6 interface reset */
 #define  RCC_APB2RST_UART7RST                  ((uint32_t)0x02000000)        /*!< UART7 interface reset */
 #define  RCC_APB2RST_UART8RST                  ((uint32_t)0x04000000)        /*!< UART8 interface reset */
#endif

#if !defined (AT32F403xx)
 #if !defined (AT32FEBKCx_MD)
  #define  RCC_APB2RST_ACCRST                   ((uint32_t)0x00400000)         /*!< ACC reset */
 #endif
#endif

#if defined (AT32F415xx)
 #define  RCC_APB2RST_EFCBRST                   ((uint32_t)0x00800000)         /*!< EFCB reset */
#endif
/*****************  Bit definition for RCC_APB1RST register  *****************/
#define  RCC_APB1RST_TMR2RST                    ((uint32_t)0x00000001)        /*!< Timer 2 reset */
#define  RCC_APB1RST_TMR3RST                    ((uint32_t)0x00000002)        /*!< Timer 3 reset */
#define  RCC_APB1RST_WWDGRST                    ((uint32_t)0x00000800)        /*!< Window Watchdog reset */
#define  RCC_APB1RST_USART2RST                  ((uint32_t)0x00020000)        /*!< USART 2 reset */
#define  RCC_APB1RST_I2C1RST                    ((uint32_t)0x00200000)        /*!< I2C 1 reset */
#define  RCC_APB1RST_CAN1RST                    ((uint32_t)0x02000000)        /*!< CAN1 reset */
#define  RCC_APB1RST_PWRRST                     ((uint32_t)0x10000000)        /*!< Power interface reset */
#define  RCC_APB1RST_TMR4RST                    ((uint32_t)0x00000004)        /*!< Timer 4 reset */
#define  RCC_APB1RST_SPI2RST                    ((uint32_t)0x00004000)        /*!< SPI 2 reset */
#define  RCC_APB1RST_I2C2RST                    ((uint32_t)0x00400000)        /*!< I2C 2 reset */
#define  RCC_APB1RST_TMR5RST                    ((uint32_t)0x00000008)        /*!< Timer 5 reset */

#if !defined (AT32F415xx)
 #define  RCC_APB1RST_BKPRST                    ((uint32_t)0x08000000)        /*!< Backup interface reset */
 #define  RCC_APB1RST_USBRST                    ((uint32_t)0x00800000)        /*!< USB Device reset */
#endif

#if defined (AT32F415xx)
 #define  RCC_APB1RST_COMPRST                   ((uint32_t)0x00000200)        /*!< Compare reset */
#endif

#if defined (AT32F403Vx_HD) || defined (AT32F403Zx_HD) || \
    defined (AT32F403Vx_XL) || defined (AT32F403Zx_XL) || \
    defined (AT32F403Axx)   || defined (AT32F407xx)
 #define  RCC_APB1RST_SPI4RST                   ((uint32_t)0x00010000)        /*!< SPI 4 reset */
#endif /* AT32F403Vx_HD || AT32F403Zx_HD || AT32F403Vx_XL || AT32F403Zx_XL 
          AT32F403Axx   || AT32F407xx */

#if !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F415K8U7_4)&& !defined (AT32F415KBU7_4)&& \
    !defined (AT32F415KCU7_4)
 #define  RCC_APB1RST_USART3RST                 ((uint32_t)0x00040000)        /*!< USART 3 reset */
#endif

#if !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F413Cx_MD) && !defined (AT32F413Cx_HD) && \
    !defined (AT32FEBKCx_MD) && !defined (TS32F401CBU7)  && \
    !defined (AT32F415K8U7_4)&& !defined (AT32F415KBU7_4)&& \
    !defined (AT32F415KCU7_4)&& !defined (AT32F415C8T7)  && \
    !defined (AT32F415CBT7)  && !defined (AT32F415CCT7)  && \
    !defined (AT32F415CBU7)  && !defined (AT32F415CCU7)
 #define  RCC_APB1RST_UART4RST                  ((uint32_t)0x00080000)        /*!< UART 4 reset */
 #define  RCC_APB1RST_UART5RST                  ((uint32_t)0x00100000)        /*!< UART 5 reset */
#endif

#if defined (AT32F413Cx_HD) || defined (AT32F413Cx_MD) || \
    defined (AT32F413Rx_HD) || defined (AT32F413Rx_MD) || \
    defined (TS32F401CBU7)
 #define  RCC_APB1RST_CAN2RST                   ((uint32_t)0x80000000)        /*!< CAN2 reset */
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define  RCC_APB1RST_CAN2RST                   ((uint32_t)0x04000000)        /*!< CAN2 reset */
#endif

#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
 #define  RCC_APB1RST_TMR6RST                   ((uint32_t)0x00000010)        /*!< Timer 6 reset */
 #define  RCC_APB1RST_TMR7RST                   ((uint32_t)0x00000020)        /*!< Timer 7 reset */
 #define  RCC_APB1RST_SPI3RST                   ((uint32_t)0x00008000)        /*!< SPI 3 reset */
 #define  RCC_APB1RST_I2C3RST                   ((uint32_t)0x04000000)        /*!< I2C 3 reset */
 #define  RCC_APB1RST_TMR12RST                  ((uint32_t)0x00000040)        /*!< TMR12 Timer reset */
 #define  RCC_APB1RST_TMR13RST                  ((uint32_t)0x00000080)        /*!< TMR13 Timer reset */
 #define  RCC_APB1RST_TMR14RST                  ((uint32_t)0x00000100)        /*!< TMR14 Timer reset */
 #define  RCC_APB1RST_DACRST                    ((uint32_t)0x20000000)        /*!< DAC interface reset */
#endif

/******************  Bit definition for RCC_AHBEN register  ******************/
#define  RCC_AHBEN_DMA1EN                       ((uint16_t)0x0001)            /*!< DMA1 clock enable */
#define  RCC_AHBEN_DMA2EN                       ((uint16_t)0x0002)            /*!< DMA2 clock enable */
#define  RCC_AHBEN_SRAMEN                       ((uint16_t)0x0004)            /*!< SRAM interface clock enable */
#define  RCC_AHBEN_FLASHEN                      ((uint16_t)0x0010)            /*!< FLITF clock enable */
#define  RCC_AHBEN_CRCEN                        ((uint16_t)0x0040)            /*!< CRC clock enable */

#if !defined (AT32FEBKCx_MD) && !defined (AT32F403Cx_HD) && \
    !defined (AT32F403Cx_MD) && !defined (AT32F403Cx_XL) && \
    !defined (AT32F403ACCT7) && !defined (AT32F403ACCU7) && \
    !defined (AT32F403ACET7) && !defined (AT32F403ACEU7) && \
    !defined (AT32F403ACGT7) && !defined (AT32F403ACGU7)
 #define  RCC_AHBEN_SDIO1EN                     ((uint16_t)0x0400)            /*!< SDIO1 clock enable */
#endif

#if defined (AT32F403Vx_HD) || defined (AT32F403Zx_HD) || \
    defined (AT32F403Vx_XL) || defined (AT32F403Zx_XL) || \
    defined (AT32F403ARCT7) || defined (AT32F403ARGT7) || \
    defined (AT32F403ARET7) || defined (AT32F403AVET7) || \
    defined (AT32F403AVCT7) || defined (AT32F403AVGT7) || \
    defined (AT32F407xx)
 #define  RCC_AHBEN_XMCEN                       ((uint16_t)0x0100)            /*!< XMC clock enable */
#endif /* AT32F403Vx_HD || AT32F403Zx_HD || AT32F403Vx_XL ||
          AT32F403Zx_XL || AT32F403ARCT7 || AT32F403ARGT7 ||
          AT32F403AVCT7 || AT32F403AVGT7 || AT32F403ARET7 ||
          AT32F403AVET7 || AT32F407xx */

#if defined (AT32F403Vx_HD) || defined (AT32F403Vx_XL) || \
    defined (AT32F403Zx_HD) || defined (AT32F403Zx_XL) || \
    defined (AT32F403Rx_HD) || defined (AT32F403Rx_XL) || \
    defined (AT32F403Axx)   || defined (AT32F407xx)
 #define  RCC_AHBEN_SDIO2EN                     ((uint16_t)0x0800)            /*!< SDIO2 clock enable */
#endif

#if defined (AT32F415xx)
 #define  RCC_AHBEN_USBEN                       ((uint16_t)0x1000)            /*!< USB clock enable */
#endif

#if defined (AT32F403Axx) || defined (AT32F407xx)
 #define  RCC_AHBEN_ETHMACEN                    ((uint16_t)0x00004000)        /*!< ETHMAC clock enable */
 #define  RCC_AHBEN_ETHMACTXEN                  ((uint16_t)0x00008000)        /*!< ETHMACTX clock enable */
 #define  RCC_AHBEN_ETHMACRXEN                  ((uint16_t)0x00010000)        /*!< ETHMACRX clock enable */
 #define  RCC_AHBEN_ETHMACPTPEN                 ((uint16_t)0x10000000)        /*!< ETHMACPTP clock enable */
#endif

/******************  Bit definition for RCC_APB2EN register  *****************/
#define  RCC_APB2EN_AFIOEN                      ((uint32_t)0x00000001)        /*!< Alternate Function I/O clock enable */
#define  RCC_APB2EN_GPIOAEN                     ((uint32_t)0x00000004)        /*!< I/O port A clock enable */
#define  RCC_APB2EN_GPIOBEN                     ((uint32_t)0x00000008)        /*!< I/O port B clock enable */
#define  RCC_APB2EN_GPIOCEN                     ((uint32_t)0x00000010)        /*!< I/O port C clock enable */
#define  RCC_APB2EN_GPIODEN                     ((uint32_t)0x00000020)        /*!< I/O port D clock enable */
#define  RCC_APB2EN_ADC1EN                      ((uint32_t)0x00000200)        /*!< ADC 1 interface clock enable */
#define  RCC_APB2EN_TMR1EN                      ((uint32_t)0x00000800)        /*!< TMR1 Timer clock enable */
#define  RCC_APB2EN_SPI1EN                      ((uint32_t)0x00001000)        /*!< SPI 1 clock enable */
#define  RCC_APB2EN_USART1EN                    ((uint32_t)0x00004000)        /*!< USART1 clock enable */

#if !defined (AT32F415xx)
 #define  RCC_APB2EN_ADC2EN                     ((uint32_t)0x00000400)        /*!< ADC 2 interface clock enable */
#endif

#if !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F413Cx_MD) && !defined (AT32F413Rx_MD) && \
    !defined (AT32FEBKCx_MD) && !defined (TS32F401CBU7)  && \
    !defined (AT32F415xx)
 #define  RCC_APB2EN_TMR8EN                     ((uint32_t)0x00002000)        /*!< TMR8 Timer clock enable */
#endif

#define  RCC_APB2EN_GPIOFEN                     ((uint32_t)0x00000080)        /*!< I/O port F clock enable */

#if !defined (AT32FEBKCx_MD)
 #define  RCC_APB2EN_TMR9EN                     ((uint32_t)0x00080000)        /*!< TMR9 Timer clock enable  */
 #define  RCC_APB2EN_TMR10EN                    ((uint32_t)0x00100000)        /*!< TMR10 Timer clock enable  */
 #define  RCC_APB2EN_TMR11EN                    ((uint32_t)0x00200000)        /*!< TMR11 Timer clock enable */
#endif

#if defined (AT32F403xx)
 #define  RCC_APB2EN_GPIOEEN                    ((uint32_t)0x00000040)        /*!< I/O port E clock enable */
 #define  RCC_APB2EN_GPIOGEN                    ((uint32_t)0x00000100)        /*!< I/O port G clock enable */
 #define  RCC_APB2EN_ADC3EN                     ((uint32_t)0x00008000)        /*!< DMA1 clock enable */
 #define  RCC_APB2EN_TMR15EN                    ((uint32_t)0x00010000)        /*!< TMR15 Timer clock enable */
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define  RCC_APB2EN_GPIOEEN                    ((uint32_t)0x00000040)        /*!< I/O port E clock enable */
 #define  RCC_APB2EN_ADC3EN                     ((uint32_t)0x00008000)        /*!< ADC3 interface clock enable */
 #define  RCC_APB2EN_I2C3EN                     ((uint32_t)0x00800000)        /*!< I2C3 interface clock enable */
 #define  RCC_APB2EN_USART6EN                   ((uint32_t)0x01000000)        /*!< USART6 interface clock enable */
 #define  RCC_APB2EN_UART7EN                    ((uint32_t)0x02000000)        /*!< UART7 interface clock enable */
 #define  RCC_APB2EN_UART8EN                    ((uint32_t)0x04000000)        /*!< UART8 interface clock enable */
#endif

#if !defined (AT32F403xx)
 #if !defined (AT32FEBKCx_MD)
  #define  RCC_APB2EN_ACCEN                     ((uint32_t)0x00400000)        /*!< ACC enable */
 #endif
#endif

#if defined (AT32F415xx)
 #define  RCC_APB2EN_EFCBEN                     ((uint32_t)0x00800000)        /*!< EFCB enable */
#endif

/*****************  Bit definition for RCC_APB1EN register  ******************/
#define  RCC_APB1EN_TMR2EN                      ((uint32_t)0x00000001)        /*!< Timer 2 clock enabled*/
#define  RCC_APB1EN_TMR3EN                      ((uint32_t)0x00000002)        /*!< Timer 3 clock enable */
#define  RCC_APB1EN_WWDGEN                      ((uint32_t)0x00000800)        /*!< Window Watchdog clock enable */
#define  RCC_APB1EN_USART2EN                    ((uint32_t)0x00020000)        /*!< USART 2 clock enable */
#define  RCC_APB1EN_I2C1EN                      ((uint32_t)0x00200000)        /*!< I2C 1 clock enable */
#define  RCC_APB1EN_CAN1EN                      ((uint32_t)0x02000000)        /*!< CAN1 clock enable */
#define  RCC_APB1EN_PWREN                       ((uint32_t)0x10000000)        /*!< Power interface clock enable */
#define  RCC_APB1EN_TMR4EN                      ((uint32_t)0x00000004)        /*!< Timer 4 clock enable */
#define  RCC_APB1EN_SPI2EN                      ((uint32_t)0x00004000)        /*!< SPI 2 clock enable */
#define  RCC_APB1EN_I2C2EN                      ((uint32_t)0x00400000)        /*!< I2C 2 clock enable */
#define  RCC_APB1EN_TMR5EN                      ((uint32_t)0x00000008)        /*!< Timer 5 clock enable */

#if !defined (AT32F415xx)
 #define  RCC_APB1EN_BKPEN                      ((uint32_t)0x08000000)        /*!< Backup interface clock enable */
 #define  RCC_APB1EN_USBEN                      ((uint32_t)0x00800000)        /*!< USB Device clock enable */
#endif

#if defined (AT32F415xx)
 #define  RCC_APB1EN_COMPEN                     ((uint32_t)0x00000200)        /*!< Compare enable */
#endif

#if defined (AT32F403Vx_HD) || defined (AT32F403Zx_HD) || \
    defined (AT32F403Vx_XL) || defined (AT32F403Zx_XL) || \
    defined (AT32F403Axx)   || defined (AT32F407xx)
 #define  RCC_APB1EN_SPI4EN                     ((uint32_t)0x00010000)        /*!< SPI 4 clock enable */
#endif /* AT32F403Vx_HD || AT32F403Zx_HD || AT32F403Vx_XL || AT32F403Zx_XL 
          AT32F403Axx   || AT32F407xx */

#if !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F415K8U7_4)&& !defined (AT32F415KBU7_4)&& \
    !defined (AT32F415KCU7_4)
 #define  RCC_APB1EN_USART3EN                   ((uint32_t)0x00040000)        /*!< USART 3 clock enable */
#endif

#if !defined (AT32F413Kx_MD) && !defined (AT32F413Kx_HD) && \
    !defined (AT32F413Cx_MD) && !defined (AT32F413Cx_HD) && \
    !defined (AT32FEBKCx_MD) && !defined (TS32F401CBU7)  && \
    !defined (AT32F415K8U7_4)&& !defined (AT32F415KBU7_4)&& \
    !defined (AT32F415KCU7_4)&& !defined (AT32F415C8T7)  && \
    !defined (AT32F415CBT7)  && !defined (AT32F415CCT7)  && \
    !defined (AT32F415CBU7)  && !defined (AT32F415CCU7)
 #define  RCC_APB1EN_UART4EN                    ((uint32_t)0x00080000)        /*!< UART 4 clock enable */
 #define  RCC_APB1EN_UART5EN                    ((uint32_t)0x00100000)        /*!< UART 5 clock enable */
#endif

#if defined (AT32F413Cx_HD) || defined (AT32F413Cx_MD) || \
    defined (AT32F413Rx_HD) || defined (AT32F413Rx_MD) || \
    defined (TS32F401CBU7)
 #define  RCC_APB1EN_CAN2EN                     ((uint32_t)0x80000000)        /*!< CAN2 enable */
#elif defined (AT32F403Axx) || defined (AT32F407xx)
 #define  RCC_APB1EN_CAN2EN                     ((uint32_t)0x04000000)        /*!< CAN2 enable */
#endif

#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
 #define  RCC_APB1EN_TMR6EN                     ((uint32_t)0x00000010)        /*!< Timer 6 clock enable */
 #define  RCC_APB1EN_TMR7EN                     ((uint32_t)0x00000020)        /*!< Timer 7 clock enable */
 #define  RCC_APB1EN_SPI3EN                     ((uint32_t)0x00008000)        /*!< SPI 3 clock enable */
 #define  RCC_APB1EN_I2C3EN                     ((uint32_t)0x04000000)        /*!< I2C 3 clock enable */
 #define  RCC_APB1EN_TMR12EN                    ((uint32_t)0x00000040)        /*!< TMR12 Timer clock enable  */
 #define  RCC_APB1EN_TMR13EN                    ((uint32_t)0x00000080)        /*!< TMR13 Timer clock enable  */
 #define  RCC_APB1EN_TMR14EN                    ((uint32_t)0x00000100)        /*!< TMR14 Timer clock enable */
 #define  RCC_APB1EN_DACEN                      ((uint32_t)0x20000000)        /*!< DAC interface clock enable */
#endif

/*******************  Bit definition for RCC_BDC register  *******************/
#if !defined (AT32F415xx)
 #define  RCC_BDC_LSEEN                         ((uint32_t)0x00000001)        /*!< External Low Speed oscillator enable */
 #define  RCC_BDC_LSESTBL                       ((uint32_t)0x00000002)        /*!< External Low Speed oscillator Ready */
 #define  RCC_BDC_LSEBYPS                       ((uint32_t)0x00000004)        /*!< External Low Speed oscillator Bypass */

 #define  RCC_BDC_RTCSEL                        ((uint32_t)0x00000300)        /*!< RTCSEL[1:0] bits (RTC clock source selection) */
 #define  RCC_BDC_RTCSEL_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
 #define  RCC_BDC_RTCSEL_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */

 /** RTC congiguration */                       
 #define  RCC_BDC_RTCSEL_NOCLK                  ((uint32_t)0x00000000)        /*!< No clock */
 #define  RCC_BDC_RTCSEL_LSE                    ((uint32_t)0x00000100)        /*!< LSE oscillator clock used as RTC clock */
 #define  RCC_BDC_RTCSEL_LSI                    ((uint32_t)0x00000200)        /*!< LSI oscillator clock used as RTC clock */
 #define  RCC_BDC_RTCSEL_HSE_DIV128             ((uint32_t)0x00000300)        /*!< HSE oscillator clock divided by 128 used as RTC clock */

 #define  RCC_BDC_RTCEN                         ((uint32_t)0x00008000)        /*!< RTC clock enable */
 #define  RCC_BDC_BDRST                         ((uint32_t)0x00010000)        /*!< Backup domain software reset  */
#else
 #define  RCC_BDC_LSEEN                         ((uint32_t)0x00000001)        /*!< External Low Speed oscillator enable */
 #define  RCC_BDC_LSESTBL                       ((uint32_t)0x00000002)        /*!< External Low Speed oscillator Ready */
 #define  RCC_BDC_LSEBYPS                       ((uint32_t)0x00000004)        /*!< External Low Speed oscillator Bypass */

 #define  RCC_BDC_ERTCSEL                       ((uint32_t)0x00000300)        /*!< ERTCSEL[1:0] bits (ERTC clock source selection) */
 #define  RCC_BDC_ERTCSEL_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
 #define  RCC_BDC_ERTCSEL_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */

 /** ERTC congiguration */                      
 #define  RCC_BDC_ERTCSEL_NOCLK                 ((uint32_t)0x00000000)        /*!< No clock */
 #define  RCC_BDC_ERTCSEL_LSE                   ((uint32_t)0x00000100)        /*!< LSE oscillator clock used as ERTC clock */
 #define  RCC_BDC_ERTCSEL_LSI                   ((uint32_t)0x00000200)        /*!< LSI oscillator clock used as ERTC clock */
 #define  RCC_BDC_ERTCSEL_HSE_DIV128            ((uint32_t)0x00000300)        /*!< HSE oscillator clock divided by 128 used as ERTC clock */

 #define  RCC_BDC_ERTCEN                        ((uint32_t)0x00008000)        /*!< ERTC clock enable */
 #define  RCC_BDC_BDRST                         ((uint32_t)0x00010000)        /*!< Backup domain software reset  */
#endif
/*******************  Bit definition for RCC_CTRLSTS register  ********************/
#define  RCC_CTRLSTS_LSIEN                      ((uint32_t)0x00000001)        /*!< Internal Low Speed oscillator enable */
#define  RCC_CTRLSTS_LSISTBL                    ((uint32_t)0x00000002)        /*!< Internal Low Speed oscillator Ready */
#define  RCC_CTRLSTS_RSTFC                      ((uint32_t)0x01000000)        /*!< Remove reset flag */
#define  RCC_CTRLSTS_PINRSTF                    ((uint32_t)0x04000000)        /*!< PIN reset flag */
#define  RCC_CTRLSTS_PORSTF                     ((uint32_t)0x08000000)        /*!< POR/PDR reset flag */
#define  RCC_CTRLSTS_SWRSTF                     ((uint32_t)0x10000000)        /*!< Software Reset flag */
#define  RCC_CTRLSTS_IWDGRSTF                   ((uint32_t)0x20000000)        /*!< Independent Watchdog reset flag */
#define  RCC_CTRLSTS_WWDGRSTF                   ((uint32_t)0x40000000)        /*!< Window watchdog reset flag */
#define  RCC_CTRLSTS_LPRSTF                     ((uint32_t)0x80000000)        /*!< Low-Power reset flag */

/*******************  Bit definition for RCC_AHBRST register  ********************/
#if defined (AT32F415xx)
 #define  RCC_AHBRST_USBRST                     ((uint32_t)0x00001000)        /*!< USB reset */
#endif /* AT32F415xx */

#if defined (AT32F403Axx) || defined (AT32F407xx)
 #define  RCC_AHBRST_ETHMACRST                  ((uint32_t)0x00004000)        /*!< ETHMAC reset */
#endif /* AT32F43Axx || AT32F407 */

/*******************  Bit definition for RCC_PLL register  ********************/
#if defined (AT32F415xx)
 #define  RCC_PLL_PLLFR                         ((uint32_t)0x00000007)        /*!< PLL FR Configuration Value */
 #define  RCC_PLL_PLLFR_0                       ((uint32_t)0x00000000)        /*!< PLL FR Configuration VCO */
 #define  RCC_PLL_PLLFR_2                       ((uint32_t)0x00000001)        /*!< PLL FR Configuration VCO/2 */
 #define  RCC_PLL_PLLFR_4                       ((uint32_t)0x00000002)        /*!< PLL FR Configuration VCO/4 */
 #define  RCC_PLL_PLLFR_8                       ((uint32_t)0x00000003)        /*!< PLL FR Configuration VCO/8 */
 #define  RCC_PLL_PLLFR_16                      ((uint32_t)0x00000004)        /*!< PLL FR Configuration VCO/16 */
 #define  RCC_PLL_PLLFR_32                      ((uint32_t)0x00000005)        /*!< PLL FR Configuration VCO/32 */
 #define  RCC_PLL_PLLMS                         ((uint32_t)0x000000F0)        /*!< PLL MS Configuration Value */
 #define  RCC_PLL_PLLNS                         ((uint32_t)0x0001FF00)        /*!< PLL NS Configuration Value */
 #define  RCC_PLL_PLLFREF                       ((uint32_t)0x07000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLFREF_4M                    ((uint32_t)0x00000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLFREF_6M                    ((uint32_t)0x01000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLFREF_8M                    ((uint32_t)0x02000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLFREF_12M                   ((uint32_t)0x03000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLFREF_16M                   ((uint32_t)0x04000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLFREF_25M                   ((uint32_t)0x05000000)        /*!< PLL FREF Configuration Table */
 #define  RCC_PLL_PLLCFGEN                      ((uint32_t)0x80000000)        /*!< PLL CFGEN Configuration enable */
#endif /* AT32F415xx */

/*******************  Bit definition for RCC_MISC register  ********************/
#define  RCC_MISC_HSICAL_KEY                    ((uint32_t)0x000000FF)        /*!< HSICAL KEY */
#define  RCC_MISC_CLKOUT_3                      ((uint32_t)0x00010000)        /*!< CLKOUT Bit 3 */

#if defined (AT32F403xx) || defined (AT32F413xx)  || \
    defined (AT32F403Axx)|| defined (AT32F407xx)
 #define  RCC_MISC_USB768B                      ((uint32_t)0x01000000)        /*!< USB SRAM size */
#endif /* AT32F403xx | AT32F413xx | AT32F403Axx | AT32F407xx */

#if defined (AT32F413xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
#define  RCC_MISC_DIV_EN                        ((uint32_t)0x20000000)        /*!< HSI48 Div 6 enable */
#endif /* AT32F413xx | AT32F403Axx | AT32F407xx */

#if !defined (AT32F403xx)
 #define  RCC_MISC_HSI_DIV_EN                   ((uint32_t)0x02000000)        /*!< HSI DIV enable */
 #define  RCC_MISC_MCOPRE_MASK                  ((uint32_t)0xF0000000)        /*!< MCO Divider Mask Value */
 #define  RCC_MISC_MCOPRE_1                     ((uint32_t)0x10000000)        /*!< MCO Div 1 Configure */
 #define  RCC_MISC_MCOPRE_2                     ((uint32_t)0x80000000)        /*!< MCO Div 2 Configure */
 #define  RCC_MISC_MCOPRE_4                     ((uint32_t)0x90000000)        /*!< MCO Div 4 Configure */
 #define  RCC_MISC_MCOPRE_8                     ((uint32_t)0xA0000000)        /*!< MCO Div 8 Configure */
 #define  RCC_MISC_MCOPRE_16                    ((uint32_t)0xB0000000)        /*!< MCO Div 16 Configure */
 #define  RCC_MISC_MCOPRE_64                    ((uint32_t)0xC0000000)        /*!< MCO Div 64 Configure */
 #define  RCC_MISC_MCOPRE_128                   ((uint32_t)0xD0000000)        /*!< MCO Div 128 Configure */
 #define  RCC_MISC_MCOPRE_256                   ((uint32_t)0xE0000000)        /*!< MCO Div 256 Configure */
 #define  RCC_MISC_MCOPRE_512                   ((uint32_t)0xF0000000)        /*!< MCO Div 512 Configure */
#endif /* !AT32F403xx */

/*******************  Bit definition for RCC_TEST register  ********************/
#define  RCC_TEST_MCO2TMR_EN                    ((uint32_t)0x00010000)        /*!< CLKOUT to TMR10 Ch 0 */

/*******************  Bit definition for RCC_MISC2 register  *******************/
#define  RCC_MISC2_AUTO_STEP_EN                 ((uint32_t)0x00000030)        /*!< Auto Step Mode */
#define  RCC_MISC2_HSI_FOR_USB                  ((uint32_t)0x00000100)        /*!< HSI48 for USB */
#define  RCC_MISC2_HSI_SYS_CTRL                 ((uint32_t)0x00000200)        /*!< HSI48 for SYSCLK */

#define  RCC_MISC2_HSE_DIV_CTRL                 ((uint32_t)0x00003000)        /*!< HSE Div */
#define  RCC_MISC2_HSE_DIV_CTRL_2               ((uint32_t)0x00000000)        /*!< HSE Div 2 */
#define  RCC_MISC2_HSE_DIV_CTRL_3               ((uint32_t)0x00001000)        /*!< HSE Div 3 */
#define  RCC_MISC2_HSE_DIV_CTRL_4               ((uint32_t)0x00002000)        /*!< HSE Div 4 */
#define  RCC_MISC2_HSE_DIV_CTRL_5               ((uint32_t)0x00003000)        /*!< HSE Div 5 */

/*****************  Bit definition for RCC_INTCTRL register  *******************/
#define  RCC_INTCTRL_USB_INT_CTRL               ((uint32_t)0x00000001)        /*!< USB interrupt remap */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_CTRLL register  *******************/
#define  GPIO_CTRLL_MDE                         ((uint32_t)0x33333333)        /*!< Port x mode bits */

#define  GPIO_CTRLL_MDE0                        ((uint32_t)0x00000003)        /*!< MODE0[1:0] bits (Port x mode bits, pin 0) */
#define  GPIO_CTRLL_MDE0_0                      ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE0_1                      ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE1                        ((uint32_t)0x00000030)        /*!< MODE1[1:0] bits (Port x mode bits, pin 1) */
#define  GPIO_CTRLL_MDE1_0                      ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE1_1                      ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE2                        ((uint32_t)0x00000300)        /*!< MODE2[1:0] bits (Port x mode bits, pin 2) */
#define  GPIO_CTRLL_MDE2_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE2_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE3                        ((uint32_t)0x00003000)        /*!< MODE3[1:0] bits (Port x mode bits, pin 3) */
#define  GPIO_CTRLL_MDE3_0                      ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE3_1                      ((uint32_t)0x00002000)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE4                        ((uint32_t)0x00030000)        /*!< MODE4[1:0] bits (Port x mode bits, pin 4) */
#define  GPIO_CTRLL_MDE4_0                      ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE4_1                      ((uint32_t)0x00020000)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE5                        ((uint32_t)0x00300000)        /*!< MODE5[1:0] bits (Port x mode bits, pin 5) */
#define  GPIO_CTRLL_MDE5_0                      ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE5_1                      ((uint32_t)0x00200000)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE6                        ((uint32_t)0x03000000)        /*!< MODE6[1:0] bits (Port x mode bits, pin 6) */
#define  GPIO_CTRLL_MDE6_0                      ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE6_1                      ((uint32_t)0x02000000)        /*!< Bit 1 */

#define  GPIO_CTRLL_MDE7                        ((uint32_t)0x30000000)        /*!< MODE7[1:0] bits (Port x mode bits, pin 7) */
#define  GPIO_CTRLL_MDE7_0                      ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  GPIO_CTRLL_MDE7_1                      ((uint32_t)0x20000000)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF                        ((uint32_t)0xCCCCCCCC)        /*!< Port x configuration bits */

#define  GPIO_CTRLL_CONF0                       ((uint32_t)0x0000000C)        /*!< CNF0[1:0] bits (Port x configuration bits, pin 0) */
#define  GPIO_CTRLL_CONF0_0                     ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF0_1                     ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF1                       ((uint32_t)0x000000C0)        /*!< CNF1[1:0] bits (Port x configuration bits, pin 1) */
#define  GPIO_CTRLL_CONF1_0                     ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF1_1                     ((uint32_t)0x00000080)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF2                       ((uint32_t)0x00000C00)        /*!< CNF2[1:0] bits (Port x configuration bits, pin 2) */
#define  GPIO_CTRLL_CONF2_0                     ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF2_1                     ((uint32_t)0x00000800)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF3                       ((uint32_t)0x0000C000)        /*!< CNF3[1:0] bits (Port x configuration bits, pin 3) */
#define  GPIO_CTRLL_CONF3_0                     ((uint32_t)0x00004000)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF3_1                     ((uint32_t)0x00008000)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF4                       ((uint32_t)0x000C0000)        /*!< CNF4[1:0] bits (Port x configuration bits, pin 4) */
#define  GPIO_CTRLL_CONF4_0                     ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF4_1                     ((uint32_t)0x00080000)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF5                       ((uint32_t)0x00C00000)        /*!< CNF5[1:0] bits (Port x configuration bits, pin 5) */
#define  GPIO_CTRLL_CONF5_0                     ((uint32_t)0x00400000)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF5_1                     ((uint32_t)0x00800000)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF6                       ((uint32_t)0x0C000000)        /*!< CNF6[1:0] bits (Port x configuration bits, pin 6) */
#define  GPIO_CTRLL_CONF6_0                     ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF6_1                     ((uint32_t)0x08000000)        /*!< Bit 1 */

#define  GPIO_CTRLL_CONF7                       ((uint32_t)0xC0000000)        /*!< CNF7[1:0] bits (Port x configuration bits, pin 7) */
#define  GPIO_CTRLL_CONF7_0                     ((uint32_t)0x40000000)        /*!< Bit 0 */
#define  GPIO_CTRLL_CONF7_1                     ((uint32_t)0x80000000)        /*!< Bit 1 */

/*******************  Bit definition for GPIO_CTRLH register  *******************/
#define  GPIO_CTRLH_MDE                         ((uint32_t)0x33333333)        /*!< Port x mode bits */

#define  GPIO_CTRLH_MDE8                        ((uint32_t)0x00000003)        /*!< MODE8[1:0] bits (Port x mode bits, pin 8) */
#define  GPIO_CTRLH_MDE8_0                      ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE8_1                      ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE9                        ((uint32_t)0x00000030)        /*!< MODE9[1:0] bits (Port x mode bits, pin 9) */
#define  GPIO_CTRLH_MDE9_0                      ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE9_1                      ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE10                       ((uint32_t)0x00000300)        /*!< MODE10[1:0] bits (Port x mode bits, pin 10) */
#define  GPIO_CTRLH_MDE10_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE10_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE11                       ((uint32_t)0x00003000)        /*!< MODE11[1:0] bits (Port x mode bits, pin 11) */
#define  GPIO_CTRLH_MDE11_0                     ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE11_1                     ((uint32_t)0x00002000)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE12                       ((uint32_t)0x00030000)        /*!< MODE12[1:0] bits (Port x mode bits, pin 12) */
#define  GPIO_CTRLH_MDE12_0                     ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE12_1                     ((uint32_t)0x00020000)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE13                       ((uint32_t)0x00300000)        /*!< MODE13[1:0] bits (Port x mode bits, pin 13) */
#define  GPIO_CTRLH_MDE13_0                     ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE13_1                     ((uint32_t)0x00200000)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE14                       ((uint32_t)0x03000000)        /*!< MODE14[1:0] bits (Port x mode bits, pin 14) */
#define  GPIO_CTRLH_MDE14_0                     ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE14_1                     ((uint32_t)0x02000000)        /*!< Bit 1 */

#define  GPIO_CTRLH_MDE15                       ((uint32_t)0x30000000)        /*!< MODE15[1:0] bits (Port x mode bits, pin 15) */
#define  GPIO_CTRLH_MDE15_0                     ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  GPIO_CTRLH_MDE15_1                     ((uint32_t)0x20000000)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF                        ((uint32_t)0xCCCCCCCC)        /*!< Port x configuration bits */

#define  GPIO_CTRLH_CONF8                       ((uint32_t)0x0000000C)        /*!< CNF8[1:0] bits (Port x configuration bits, pin 8) */
#define  GPIO_CTRLH_CONF8_0                     ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF8_1                     ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF9                       ((uint32_t)0x000000C0)        /*!< CNF9[1:0] bits (Port x configuration bits, pin 9) */
#define  GPIO_CTRLH_CONF9_0                     ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF9_1                     ((uint32_t)0x00000080)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF10                      ((uint32_t)0x00000C00)        /*!< CNF10[1:0] bits (Port x configuration bits, pin 10) */
#define  GPIO_CTRLH_CONF10_0                    ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF10_1                    ((uint32_t)0x00000800)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF11                      ((uint32_t)0x0000C000)        /*!< CNF11[1:0] bits (Port x configuration bits, pin 11) */
#define  GPIO_CTRLH_CONF11_0                    ((uint32_t)0x00004000)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF11_1                    ((uint32_t)0x00008000)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF12                      ((uint32_t)0x000C0000)        /*!< CNF12[1:0] bits (Port x configuration bits, pin 12) */
#define  GPIO_CTRLH_CONF12_0                    ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF12_1                    ((uint32_t)0x00080000)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF13                      ((uint32_t)0x00C00000)        /*!< CNF13[1:0] bits (Port x configuration bits, pin 13) */
#define  GPIO_CTRLH_CONF13_0                    ((uint32_t)0x00400000)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF13_1                    ((uint32_t)0x00800000)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF14                      ((uint32_t)0x0C000000)        /*!< CNF14[1:0] bits (Port x configuration bits, pin 14) */
#define  GPIO_CTRLH_CONF14_0                    ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF14_1                    ((uint32_t)0x08000000)        /*!< Bit 1 */

#define  GPIO_CTRLH_CONF15                      ((uint32_t)0xC0000000)        /*!< CNF15[1:0] bits (Port x configuration bits, pin 15) */
#define  GPIO_CTRLH_CONF15_0                    ((uint32_t)0x40000000)        /*!< Bit 0 */
#define  GPIO_CTRLH_CONF15_1                    ((uint32_t)0x80000000)        /*!< Bit 1 */

/********************  Bit definition for GPIO_IPTDT register  *******************/
#define GPIO_IPTDT_IPTDT0                       ((uint16_t)0x0001)            /*!< Port input data, bit 0 */
#define GPIO_IPTDT_IPTDT1                       ((uint16_t)0x0002)            /*!< Port input data, bit 1 */
#define GPIO_IPTDT_IPTDT2                       ((uint16_t)0x0004)            /*!< Port input data, bit 2 */
#define GPIO_IPTDT_IPTDT3                       ((uint16_t)0x0008)            /*!< Port input data, bit 3 */
#define GPIO_IPTDT_IPTDT4                       ((uint16_t)0x0010)            /*!< Port input data, bit 4 */
#define GPIO_IPTDT_IPTDT5                       ((uint16_t)0x0020)            /*!< Port input data, bit 5 */
#define GPIO_IPTDT_IPTDT6                       ((uint16_t)0x0040)            /*!< Port input data, bit 6 */
#define GPIO_IPTDT_IPTDT7                       ((uint16_t)0x0080)            /*!< Port input data, bit 7 */
#define GPIO_IPTDT_IPTDT8                       ((uint16_t)0x0100)            /*!< Port input data, bit 8 */
#define GPIO_IPTDT_IPTDT9                       ((uint16_t)0x0200)            /*!< Port input data, bit 9 */
#define GPIO_IPTDT_IPTDT10                      ((uint16_t)0x0400)            /*!< Port input data, bit 10 */
#define GPIO_IPTDT_IPTDT11                      ((uint16_t)0x0800)            /*!< Port input data, bit 11 */
#define GPIO_IPTDT_IPTDT12                      ((uint16_t)0x1000)            /*!< Port input data, bit 12 */
#define GPIO_IPTDT_IPTDT13                      ((uint16_t)0x2000)            /*!< Port input data, bit 13 */
#define GPIO_IPTDT_IPTDT14                      ((uint16_t)0x4000)            /*!< Port input data, bit 14 */
#define GPIO_IPTDT_IPTDT15                      ((uint16_t)0x8000)            /*!< Port input data, bit 15 */

/*******************  Bit definition for GPIO_OPTDT register  *******************/
#define GPIO_OPTDT_OPTDT0                       ((uint16_t)0x0001)            /*!< Port output data, bit 0 */
#define GPIO_OPTDT_OPTDT1                       ((uint16_t)0x0002)            /*!< Port output data, bit 1 */
#define GPIO_OPTDT_OPTDT2                       ((uint16_t)0x0004)            /*!< Port output data, bit 2 */
#define GPIO_OPTDT_OPTDT3                       ((uint16_t)0x0008)            /*!< Port output data, bit 3 */
#define GPIO_OPTDT_OPTDT4                       ((uint16_t)0x0010)            /*!< Port output data, bit 4 */
#define GPIO_OPTDT_OPTDT5                       ((uint16_t)0x0020)            /*!< Port output data, bit 5 */
#define GPIO_OPTDT_OPTDT6                       ((uint16_t)0x0040)            /*!< Port output data, bit 6 */
#define GPIO_OPTDT_OPTDT7                       ((uint16_t)0x0080)            /*!< Port output data, bit 7 */
#define GPIO_OPTDT_OPTDT8                       ((uint16_t)0x0100)            /*!< Port output data, bit 8 */
#define GPIO_OPTDT_OPTDT9                       ((uint16_t)0x0200)            /*!< Port output data, bit 9 */
#define GPIO_OPTDT_OPTDT10                      ((uint16_t)0x0400)            /*!< Port output data, bit 10 */
#define GPIO_OPTDT_OPTDT11                      ((uint16_t)0x0800)            /*!< Port output data, bit 11 */
#define GPIO_OPTDT_OPTDT12                      ((uint16_t)0x1000)            /*!< Port output data, bit 12 */
#define GPIO_OPTDT_OPTDT13                      ((uint16_t)0x2000)            /*!< Port output data, bit 13 */
#define GPIO_OPTDT_OPTDT14                      ((uint16_t)0x4000)            /*!< Port output data, bit 14 */
#define GPIO_OPTDT_OPTDT15                      ((uint16_t)0x8000)            /*!< Port output data, bit 15 */

/******************  Bit definition for GPIO_BSRE register  *******************/
#define GPIO_BSRE_BST0                          ((uint32_t)0x00000001)        /*!< Port x Set bit 0 */
#define GPIO_BSRE_BST1                          ((uint32_t)0x00000002)        /*!< Port x Set bit 1 */
#define GPIO_BSRE_BST2                          ((uint32_t)0x00000004)        /*!< Port x Set bit 2 */
#define GPIO_BSRE_BST3                          ((uint32_t)0x00000008)        /*!< Port x Set bit 3 */
#define GPIO_BSRE_BST4                          ((uint32_t)0x00000010)        /*!< Port x Set bit 4 */
#define GPIO_BSRE_BST5                          ((uint32_t)0x00000020)        /*!< Port x Set bit 5 */
#define GPIO_BSRE_BST6                          ((uint32_t)0x00000040)        /*!< Port x Set bit 6 */
#define GPIO_BSRE_BST7                          ((uint32_t)0x00000080)        /*!< Port x Set bit 7 */
#define GPIO_BSRE_BST8                          ((uint32_t)0x00000100)        /*!< Port x Set bit 8 */
#define GPIO_BSRE_BST9                          ((uint32_t)0x00000200)        /*!< Port x Set bit 9 */
#define GPIO_BSRE_BST10                         ((uint32_t)0x00000400)        /*!< Port x Set bit 10 */
#define GPIO_BSRE_BST11                         ((uint32_t)0x00000800)        /*!< Port x Set bit 11 */
#define GPIO_BSRE_BST12                         ((uint32_t)0x00001000)        /*!< Port x Set bit 12 */
#define GPIO_BSRE_BST13                         ((uint32_t)0x00002000)        /*!< Port x Set bit 13 */
#define GPIO_BSRE_BST14                         ((uint32_t)0x00004000)        /*!< Port x Set bit 14 */
#define GPIO_BSRE_BST15                         ((uint32_t)0x00008000)        /*!< Port x Set bit 15 */

#define GPIO_BSRE_BRE0                          ((uint32_t)0x00010000)        /*!< Port x Reset bit 0 */
#define GPIO_BSRE_BRE1                          ((uint32_t)0x00020000)        /*!< Port x Reset bit 1 */
#define GPIO_BSRE_BRE2                          ((uint32_t)0x00040000)        /*!< Port x Reset bit 2 */
#define GPIO_BSRE_BRE3                          ((uint32_t)0x00080000)        /*!< Port x Reset bit 3 */
#define GPIO_BSRE_BRE4                          ((uint32_t)0x00100000)        /*!< Port x Reset bit 4 */
#define GPIO_BSRE_BRE5                          ((uint32_t)0x00200000)        /*!< Port x Reset bit 5 */
#define GPIO_BSRE_BRE6                          ((uint32_t)0x00400000)        /*!< Port x Reset bit 6 */
#define GPIO_BSRE_BRE7                          ((uint32_t)0x00800000)        /*!< Port x Reset bit 7 */
#define GPIO_BSRE_BRE8                          ((uint32_t)0x01000000)        /*!< Port x Reset bit 8 */
#define GPIO_BSRE_BRE9                          ((uint32_t)0x02000000)        /*!< Port x Reset bit 9 */
#define GPIO_BSRE_BRE10                         ((uint32_t)0x04000000)        /*!< Port x Reset bit 10 */
#define GPIO_BSRE_BRE11                         ((uint32_t)0x08000000)        /*!< Port x Reset bit 11 */
#define GPIO_BSRE_BRE12                         ((uint32_t)0x10000000)        /*!< Port x Reset bit 12 */
#define GPIO_BSRE_BRE13                         ((uint32_t)0x20000000)        /*!< Port x Reset bit 13 */
#define GPIO_BSRE_BRE14                         ((uint32_t)0x40000000)        /*!< Port x Reset bit 14 */
#define GPIO_BSRE_BRE15                         ((uint32_t)0x80000000)        /*!< Port x Reset bit 15 */

/*******************  Bit definition for GPIO_BRE register  *******************/
#define GPIO_BRE_BRE0                           ((uint16_t)0x0001)            /*!< Port x Reset bit 0 */
#define GPIO_BRE_BRE1                           ((uint16_t)0x0002)            /*!< Port x Reset bit 1 */
#define GPIO_BRE_BRE2                           ((uint16_t)0x0004)            /*!< Port x Reset bit 2 */
#define GPIO_BRE_BRE3                           ((uint16_t)0x0008)            /*!< Port x Reset bit 3 */
#define GPIO_BRE_BRE4                           ((uint16_t)0x0010)            /*!< Port x Reset bit 4 */
#define GPIO_BRE_BRE5                           ((uint16_t)0x0020)            /*!< Port x Reset bit 5 */
#define GPIO_BRE_BRE6                           ((uint16_t)0x0040)            /*!< Port x Reset bit 6 */
#define GPIO_BRE_BRE7                           ((uint16_t)0x0080)            /*!< Port x Reset bit 7 */
#define GPIO_BRE_BRE8                           ((uint16_t)0x0100)            /*!< Port x Reset bit 8 */
#define GPIO_BRE_BRE9                           ((uint16_t)0x0200)            /*!< Port x Reset bit 9 */
#define GPIO_BRE_BRE10                          ((uint16_t)0x0400)            /*!< Port x Reset bit 10 */
#define GPIO_BRE_BRE11                          ((uint16_t)0x0800)            /*!< Port x Reset bit 11 */
#define GPIO_BRE_BRE12                          ((uint16_t)0x1000)            /*!< Port x Reset bit 12 */
#define GPIO_BRE_BRE13                          ((uint16_t)0x2000)            /*!< Port x Reset bit 13 */
#define GPIO_BRE_BRE14                          ((uint16_t)0x4000)            /*!< Port x Reset bit 14 */
#define GPIO_BRE_BRE15                          ((uint16_t)0x8000)            /*!< Port x Reset bit 15 */

/******************  Bit definition for GPIO_LOCK register  *******************/
#define GPIO_LOCK_LOCK0                         ((uint32_t)0x00000001)        /*!< Port x Lock bit 0 */
#define GPIO_LOCK_LOCK1                         ((uint32_t)0x00000002)        /*!< Port x Lock bit 1 */
#define GPIO_LOCK_LOCK2                         ((uint32_t)0x00000004)        /*!< Port x Lock bit 2 */
#define GPIO_LOCK_LOCK3                         ((uint32_t)0x00000008)        /*!< Port x Lock bit 3 */
#define GPIO_LOCK_LOCK4                         ((uint32_t)0x00000010)        /*!< Port x Lock bit 4 */
#define GPIO_LOCK_LOCK5                         ((uint32_t)0x00000020)        /*!< Port x Lock bit 5 */
#define GPIO_LOCK_LOCK6                         ((uint32_t)0x00000040)        /*!< Port x Lock bit 6 */
#define GPIO_LOCK_LOCK7                         ((uint32_t)0x00000080)        /*!< Port x Lock bit 7 */
#define GPIO_LOCK_LOCK8                         ((uint32_t)0x00000100)        /*!< Port x Lock bit 8 */
#define GPIO_LOCK_LOCK9                         ((uint32_t)0x00000200)        /*!< Port x Lock bit 9 */
#define GPIO_LOCK_LOCK10                        ((uint32_t)0x00000400)        /*!< Port x Lock bit 10 */
#define GPIO_LOCK_LOCK11                        ((uint32_t)0x00000800)        /*!< Port x Lock bit 11 */
#define GPIO_LOCK_LOCK12                        ((uint32_t)0x00001000)        /*!< Port x Lock bit 12 */
#define GPIO_LOCK_LOCK13                        ((uint32_t)0x00002000)        /*!< Port x Lock bit 13 */
#define GPIO_LOCK_LOCK14                        ((uint32_t)0x00004000)        /*!< Port x Lock bit 14 */
#define GPIO_LOCK_LOCK15                        ((uint32_t)0x00008000)        /*!< Port x Lock bit 15 */
#define GPIO_LOCK_LOCKK                         ((uint32_t)0x00010000)        /*!< Lock key */

/*----------------------------------------------------------------------------*/

/******************  Bit definition for AFIO_EVCTRL register  *******************/
#define AFIO_EVCTRL_PIN                         ((uint8_t)0x0F)               /*!< PIN[3:0] bits (Pin selection) */
#define AFIO_EVCTRL_PIN_B0                      ((uint8_t)0x01)               /*!< Bit 0 */
#define AFIO_EVCTRL_PIN_B1                      ((uint8_t)0x02)               /*!< Bit 1 */
#define AFIO_EVCTRL_PIN_B2                      ((uint8_t)0x04)               /*!< Bit 2 */
#define AFIO_EVCTRL_PIN_B3                      ((uint8_t)0x08)               /*!< Bit 3 */

/** PIN configuration */
#define AFIO_EVCTRL_PIN_PN0                     ((uint8_t)0x00)               /*!< Pin 0 selected */
#define AFIO_EVCTRL_PIN_PN1                     ((uint8_t)0x01)               /*!< Pin 1 selected */
#define AFIO_EVCTRL_PIN_PN2                     ((uint8_t)0x02)               /*!< Pin 2 selected */
#define AFIO_EVCTRL_PIN_PN3                     ((uint8_t)0x03)               /*!< Pin 3 selected */
#define AFIO_EVCTRL_PIN_PN4                     ((uint8_t)0x04)               /*!< Pin 4 selected */
#define AFIO_EVCTRL_PIN_PN5                     ((uint8_t)0x05)               /*!< Pin 5 selected */
#define AFIO_EVCTRL_PIN_PN6                     ((uint8_t)0x06)               /*!< Pin 6 selected */
#define AFIO_EVCTRL_PIN_PN7                     ((uint8_t)0x07)               /*!< Pin 7 selected */
#define AFIO_EVCTRL_PIN_PN8                     ((uint8_t)0x08)               /*!< Pin 8 selected */
#define AFIO_EVCTRL_PIN_PN9                     ((uint8_t)0x09)               /*!< Pin 9 selected */
#define AFIO_EVCTRL_PIN_PN10                    ((uint8_t)0x0A)               /*!< Pin 10 selected */
#define AFIO_EVCTRL_PIN_PN11                    ((uint8_t)0x0B)               /*!< Pin 11 selected */
#define AFIO_EVCTRL_PIN_PN12                    ((uint8_t)0x0C)               /*!< Pin 12 selected */
#define AFIO_EVCTRL_PIN_PN13                    ((uint8_t)0x0D)               /*!< Pin 13 selected */
#define AFIO_EVCTRL_PIN_PN14                    ((uint8_t)0x0E)               /*!< Pin 14 selected */
#define AFIO_EVCTRL_PIN_PN15                    ((uint8_t)0x0F)               /*!< Pin 15 selected */

#define AFIO_EVCTRL_PORT                        ((uint8_t)0x70)               /*!< PORT[2:0] bits (Port selection) */
#define AFIO_EVCTRL_PORT_B0                     ((uint8_t)0x10)               /*!< Bit 0 */
#define AFIO_EVCTRL_PORT_B1                     ((uint8_t)0x20)               /*!< Bit 1 */
#define AFIO_EVCTRL_PORT_B2                     ((uint8_t)0x40)               /*!< Bit 2 */

/** PORT configuration */
#define AFIO_EVCTRL_PORT_PTA                    ((uint8_t)0x00)               /*!< Port A selected */
#define AFIO_EVCTRL_PORT_PTB                    ((uint8_t)0x10)               /*!< Port B selected */
#define AFIO_EVCTRL_PORT_PTC                    ((uint8_t)0x20)               /*!< Port C selected */
#define AFIO_EVCTRL_PORT_PTD                    ((uint8_t)0x30)               /*!< Port D selected */
#define AFIO_EVCTRL_PORT_PTE                    ((uint8_t)0x40)               /*!< Port E selected */

#define AFIO_EVCTRL_EVOEN                       ((uint8_t)0x80)               /*!< Event Output Enable */

/******************  Bit definition for AFIO_MAP register  *******************/
#define AFIO_MAP_SPI1_REMAP                     ((uint32_t)0x00000001)        /*!< SPI1 remapping */
#define AFIO_MAP_I2C1_REMAP                     ((uint32_t)0x00000002)        /*!< I2C1 remapping */
#define AFIO_MAP_USART1_REMAP                   ((uint32_t)0x00000004)        /*!< USART1 remapping */
#define AFIO_MAP_USART2_REMAP                   ((uint32_t)0x00000008)        /*!< USART2 remapping */

#define AFIO_MAP_USART3_REMAP                   ((uint32_t)0x00000030)        /*!< USART3_REMAP[1:0] bits (USART3 remapping) */
#define AFIO_MAP_USART3_REMAP_B0                ((uint32_t)0x00000010)        /*!< Bit 0 */
#define AFIO_MAP_USART3_REMAP_B1                ((uint32_t)0x00000020)        /*!< Bit 1 */

/** USART3_REMAP configuration */
#define AFIO_MAP_USART3_REMAP_NONEREMAP         ((uint32_t)0x00000000)        /*!< No remap (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14) */
#define AFIO_MAP_USART3_REMAP_PARTIALREMAP      ((uint32_t)0x00000010)        /*!< Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14) */
#define AFIO_MAP_USART3_REMAP_FULLREMAP         ((uint32_t)0x00000030)        /*!< Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12) */

#define AFIO_MAP_TMR1_REMAP                     ((uint32_t)0x000000C0)        /*!< TMR1_REMAP[1:0] bits (TMR1 remapping) */
#define AFIO_MAP_TMR1_REMAP_B0                  ((uint32_t)0x00000040)        /*!< Bit 0 */
#define AFIO_MAP_TMR1_REMAP_B1                  ((uint32_t)0x00000080)        /*!< Bit 1 */

/** TMR1_REMAP configuration */
#define AFIO_MAP_TMR1_REMAP_NONEREMAP           ((uint32_t)0x00000000)        /*!< No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15) */
#define AFIO_MAP_TMR1_REMAP_PARTIALREMAP        ((uint32_t)0x00000040)        /*!< Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1) */
#define AFIO_MAP_TMR1_REMAP_FULLREMAP           ((uint32_t)0x000000C0)        /*!< Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12) */

#define AFIO_MAP_TMR2_REMAP                     ((uint32_t)0x00000300)        /*!< TMR2_REMAP[1:0] bits (TMR2 remapping) */
#define AFIO_MAP_TMR2_REMAP_B0                  ((uint32_t)0x00000100)        /*!< Bit 0 */
#define AFIO_MAP_TMR2_REMAP_B1                  ((uint32_t)0x00000200)        /*!< Bit 1 */

/** TMR2_REMAP configuration */
#define AFIO_MAP_TMR2_REMAP_NONEREMAP           ((uint32_t)0x00000000)        /*!< No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3) */
#define AFIO_MAP_TMR2_REMAP_PARTIALREMAP1       ((uint32_t)0x00000100)        /*!< Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3) */
#define AFIO_MAP_TMR2_REMAP_PARTIALREMAP2       ((uint32_t)0x00000200)        /*!< Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11) */
#define AFIO_MAP_TMR2_REMAP_FULLREMAP           ((uint32_t)0x00000300)        /*!< Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) */

#define AFIO_MAP_TMR3_REMAP                     ((uint32_t)0x00000C00)        /*!< TMR3_REMAP[1:0] bits (TMR3 remapping) */
#define AFIO_MAP_TMR3_REMAP_B0                  ((uint32_t)0x00000400)        /*!< Bit 0 */
#define AFIO_MAP_TMR3_REMAP_B1                  ((uint32_t)0x00000800)        /*!< Bit 1 */

/** TMR3_REMAP configuration */
#define AFIO_MAP_TMR3_REMAP_NONEREMAP           ((uint32_t)0x00000000)        /*!< No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1) */
#define AFIO_MAP_TMR3_REMAP_PARTIALREMAP        ((uint32_t)0x00000800)        /*!< Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1) */
#define AFIO_MAP_TMR3_REMAP_FULLREMAP           ((uint32_t)0x00000C00)        /*!< Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) */

#define AFIO_MAP_TMR4_REMAP                     ((uint32_t)0x00001000)        /*!< TMR4_REMAP bit (TMR4 remapping) */

#define AFIO_MAP_CAN_REMAP                      ((uint32_t)0x00006000)        /*!< CAN_REMAP[1:0] bits (CAN Alternate function remapping) */
#define AFIO_MAP_CAN_REMAP_B0                   ((uint32_t)0x00002000)        /*!< Bit 0 */
#define AFIO_MAP_CAN_REMAP_B1                   ((uint32_t)0x00004000)        /*!< Bit 1 */

/** CAN_REMAP configuration */
#define AFIO_MAP_CAN_REMAP_RE1                  ((uint32_t)0x00000000)        /*!< CANRX mapped to PA11, CANTX mapped to PA12 */
#define AFIO_MAP_CAN_REMAP_RE2                  ((uint32_t)0x00004000)        /*!< CANRX mapped to PB8, CANTX mapped to PB9 */
#define AFIO_MAP_CAN_REMAP_RE3                  ((uint32_t)0x00006000)        /*!< CANRX mapped to PD0, CANTX mapped to PD1 */

#define AFIO_MAP_PTD01_REMAP                    ((uint32_t)0x00008000)        /*!< Port D0/Port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_MAP_TMR5CH4_INTLRE                 ((uint32_t)0x00010000)        /*!< TMR5 Channel4 Internal Remap */
#define AFIO_MAP_ADC1_EXTRGINJ_REMAP            ((uint32_t)0x00020000)        /*!< ADC 1 External Trigger Injected Conversion remapping */
#define AFIO_MAP_ADC1_EXTRGREG_REMAP            ((uint32_t)0x00040000)        /*!< ADC 1 External Trigger Regular Conversion remapping */
#define AFIO_MAP_ADC2_EXTRGINJ_REMAP            ((uint32_t)0x00080000)        /*!< ADC 2 External Trigger Injected Conversion remapping */
#define AFIO_MAP_ADC2_EXTRGREG_REMAP            ((uint32_t)0x00100000)        /*!< ADC 2 External Trigger Regular Conversion remapping */

/** SWJ_CFG configuration */
#define AFIO_MAP_SWJTAG_CONF                    ((uint32_t)0x07000000)        /*!< SWJ_CFG[2:0] bits (Serial Wire JTAG configuration) */
#define AFIO_MAP_SWJTAG_CONF_B0                 ((uint32_t)0x01000000)        /*!< Bit 0 */
#define AFIO_MAP_SWJTAG_CONF_B1                 ((uint32_t)0x02000000)        /*!< Bit 1 */
#define AFIO_MAP_SWJTAG_CONF_B2                 ((uint32_t)0x04000000)        /*!< Bit 2 */

#define AFIO_MAP_SWJTAG_CONF_FULL               ((uint32_t)0x00000000)        /*!< Full SWJ (JTAG-DP + SW-DP) : Reset State */
#define AFIO_MAP_SWJTAG_CONF_NOJNTRST           ((uint32_t)0x01000000)        /*!< Full SWJ (JTAG-DP + SW-DP) but without JNTRST */
#define AFIO_MAP_SWJTAG_CONF_JTAGDISABLE        ((uint32_t)0x02000000)        /*!< JTAG-DP Disabled and SW-DP Enabled */
#define AFIO_MAP_SWJTAG_CONF_ALLDISABLE         ((uint32_t)0x04000000)        /*!< JTAG-DP Disabled and SW-DP Disabled */

/*****************  Bit definition for AFIO_EXTIC1 register  *****************/
#define AFIO_EXTIC1_EXTINT0                     ((uint16_t)0x000F)            /*!< EXTI 0 configuration */
#define AFIO_EXTIC1_EXTINT1                     ((uint16_t)0x00F0)            /*!< EXTI 1 configuration */
#define AFIO_EXTIC1_EXTINT2                     ((uint16_t)0x0F00)            /*!< EXTI 2 configuration */
#define AFIO_EXTIC1_EXTINT3                     ((uint16_t)0xF000)            /*!< EXTI 3 configuration */

/** EXTI0 configuration */
#define AFIO_EXTIC1_EXTINT0_PTA                 ((uint16_t)0x0000)            /*!< PA[0] pin */
#define AFIO_EXTIC1_EXTINT0_PTB                 ((uint16_t)0x0001)            /*!< PB[0] pin */
#define AFIO_EXTIC1_EXTINT0_PTC                 ((uint16_t)0x0002)            /*!< PC[0] pin */
#define AFIO_EXTIC1_EXTINT0_PTD                 ((uint16_t)0x0003)            /*!< PD[0] pin */
#define AFIO_EXTIC1_EXTINT0_PTE                 ((uint16_t)0x0004)            /*!< PE[0] pin */
#define AFIO_EXTIC1_EXTINT0_PTF                 ((uint16_t)0x0005)            /*!< PF[0] pin */
#define AFIO_EXTIC1_EXTINT0_PTG                 ((uint16_t)0x0006)            /*!< PG[0] pin */

/** EXTI1 configuration */
#define AFIO_EXTIC1_EXTINT1_PTA                 ((uint16_t)0x0000)            /*!< PA[1] pin */
#define AFIO_EXTIC1_EXTINT1_PTB                 ((uint16_t)0x0010)            /*!< PB[1] pin */
#define AFIO_EXTIC1_EXTINT1_PTC                 ((uint16_t)0x0020)            /*!< PC[1] pin */
#define AFIO_EXTIC1_EXTINT1_PTD                 ((uint16_t)0x0030)            /*!< PD[1] pin */
#define AFIO_EXTIC1_EXTINT1_PTE                 ((uint16_t)0x0040)            /*!< PE[1] pin */
#define AFIO_EXTIC1_EXTINT1_PTF                 ((uint16_t)0x0050)            /*!< PF[1] pin */
#define AFIO_EXTIC1_EXTINT1_PTG                 ((uint16_t)0x0060)            /*!< PG[1] pin */

/** EXTI2 configuration */
#define AFIO_EXTIC1_EXTINT2_PTA                 ((uint16_t)0x0000)            /*!< PA[2] pin */
#define AFIO_EXTIC1_EXTINT2_PTB                 ((uint16_t)0x0100)            /*!< PB[2] pin */
#define AFIO_EXTIC1_EXTINT2_PTC                 ((uint16_t)0x0200)            /*!< PC[2] pin */
#define AFIO_EXTIC1_EXTINT2_PTD                 ((uint16_t)0x0300)            /*!< PD[2] pin */
#define AFIO_EXTIC1_EXTINT2_PTE                 ((uint16_t)0x0400)            /*!< PE[2] pin */
#define AFIO_EXTIC1_EXTINT2_PTF                 ((uint16_t)0x0500)            /*!< PF[2] pin */
#define AFIO_EXTIC1_EXTINT2_PTG                 ((uint16_t)0x0600)            /*!< PG[2] pin */

/** EXTI3 configuration */
#define AFIO_EXTIC1_EXTINT3_PTA                 ((uint16_t)0x0000)            /*!< PA[3] pin */
#define AFIO_EXTIC1_EXTINT3_PTB                 ((uint16_t)0x1000)            /*!< PB[3] pin */
#define AFIO_EXTIC1_EXTINT3_PTC                 ((uint16_t)0x2000)            /*!< PC[3] pin */
#define AFIO_EXTIC1_EXTINT3_PTD                 ((uint16_t)0x3000)            /*!< PD[3] pin */
#define AFIO_EXTIC1_EXTINT3_PTE                 ((uint16_t)0x4000)            /*!< PE[3] pin */
#define AFIO_EXTIC1_EXTINT3_PTF                 ((uint16_t)0x5000)            /*!< PF[3] pin */
#define AFIO_EXTIC1_EXTINT3_PTG                 ((uint16_t)0x6000)            /*!< PG[3] pin */

/*****************  Bit definition for AFIO_EXTIC2 register  *****************/
#define AFIO_EXTIC2_EXTINT4                     ((uint16_t)0x000F)            /*!< EXTI 4 configuration */
#define AFIO_EXTIC2_EXTINT5                     ((uint16_t)0x00F0)            /*!< EXTI 5 configuration */
#define AFIO_EXTIC2_EXTINT6                     ((uint16_t)0x0F00)            /*!< EXTI 6 configuration */
#define AFIO_EXTIC2_EXTINT7                     ((uint16_t)0xF000)            /*!< EXTI 7 configuration */

/** EXTI4 configuration */
#define AFIO_EXTIC2_EXTINT4_PTA                 ((uint16_t)0x0000)            /*!< PA[4] pin */
#define AFIO_EXTIC2_EXTINT4_PTB                 ((uint16_t)0x0001)            /*!< PB[4] pin */
#define AFIO_EXTIC2_EXTINT4_PTC                 ((uint16_t)0x0002)            /*!< PC[4] pin */
#define AFIO_EXTIC2_EXTINT4_PTD                 ((uint16_t)0x0003)            /*!< PD[4] pin */
#define AFIO_EXTIC2_EXTINT4_PTE                 ((uint16_t)0x0004)            /*!< PE[4] pin */
#define AFIO_EXTIC2_EXTINT4_PTF                 ((uint16_t)0x0005)            /*!< PF[4] pin */
#define AFIO_EXTIC2_EXTINT4_PTG                 ((uint16_t)0x0006)            /*!< PG[4] pin */

/* EXTI5 configuration */
#define AFIO_EXTIC2_EXTINT5_PTA                 ((uint16_t)0x0000)            /*!< PA[5] pin */
#define AFIO_EXTIC2_EXTINT5_PTB                 ((uint16_t)0x0010)            /*!< PB[5] pin */
#define AFIO_EXTIC2_EXTINT5_PTC                 ((uint16_t)0x0020)            /*!< PC[5] pin */
#define AFIO_EXTIC2_EXTINT5_PTD                 ((uint16_t)0x0030)            /*!< PD[5] pin */
#define AFIO_EXTIC2_EXTINT5_PTE                 ((uint16_t)0x0040)            /*!< PE[5] pin */
#define AFIO_EXTIC2_EXTINT5_PTF                 ((uint16_t)0x0050)            /*!< PF[5] pin */
#define AFIO_EXTIC2_EXTINT5_PTG                 ((uint16_t)0x0060)            /*!< PG[5] pin */

/** EXTI6 configuration */
#define AFIO_EXTIC2_EXTINT6_PTA                 ((uint16_t)0x0000)            /*!< PA[6] pin */
#define AFIO_EXTIC2_EXTINT6_PTB                 ((uint16_t)0x0100)            /*!< PB[6] pin */
#define AFIO_EXTIC2_EXTINT6_PTC                 ((uint16_t)0x0200)            /*!< PC[6] pin */
#define AFIO_EXTIC2_EXTINT6_PTD                 ((uint16_t)0x0300)            /*!< PD[6] pin */
#define AFIO_EXTIC2_EXTINT6_PTE                 ((uint16_t)0x0400)            /*!< PE[6] pin */
#define AFIO_EXTIC2_EXTINT6_PTF                 ((uint16_t)0x0500)            /*!< PF[6] pin */
#define AFIO_EXTIC2_EXTINT6_PTG                 ((uint16_t)0x0600)            /*!< PG[6] pin */

/** EXTI7 configuration */
#define AFIO_EXTIC2_EXTINT7_PTA                 ((uint16_t)0x0000)            /*!< PA[7] pin */
#define AFIO_EXTIC2_EXTINT7_PTB                 ((uint16_t)0x1000)            /*!< PB[7] pin */
#define AFIO_EXTIC2_EXTINT7_PTC                 ((uint16_t)0x2000)            /*!< PC[7] pin */
#define AFIO_EXTIC2_EXTINT7_PTD                 ((uint16_t)0x3000)            /*!< PD[7] pin */
#define AFIO_EXTIC2_EXTINT7_PTE                 ((uint16_t)0x4000)            /*!< PE[7] pin */
#define AFIO_EXTIC2_EXTINT7_PTF                 ((uint16_t)0x5000)            /*!< PF[7] pin */
#define AFIO_EXTIC2_EXTINT7_PTG                 ((uint16_t)0x6000)            /*!< PG[7] pin */

/*****************  Bit definition for AFIO_EXTIC3 register  *****************/
#define AFIO_EXTIC3_EXTINT8                     ((uint16_t)0x000F)            /*!< EXTI 8 configuration */
#define AFIO_EXTIC3_EXTINT9                     ((uint16_t)0x00F0)            /*!< EXTI 9 configuration */
#define AFIO_EXTIC3_EXTINT10                    ((uint16_t)0x0F00)            /*!< EXTI 10 configuration */
#define AFIO_EXTIC3_EXTINT11                    ((uint16_t)0xF000)            /*!< EXTI 11 configuration */

/** EXTI8 configuration */
#define AFIO_EXTIC3_EXTINT8_PTA                 ((uint16_t)0x0000)            /*!< PA[8] pin */
#define AFIO_EXTIC3_EXTINT8_PTB                 ((uint16_t)0x0001)            /*!< PB[8] pin */
#define AFIO_EXTIC3_EXTINT8_PTC                 ((uint16_t)0x0002)            /*!< PC[8] pin */
#define AFIO_EXTIC3_EXTINT8_PTD                 ((uint16_t)0x0003)            /*!< PD[8] pin */
#define AFIO_EXTIC3_EXTINT8_PTE                 ((uint16_t)0x0004)            /*!< PE[8] pin */
#define AFIO_EXTIC3_EXTINT8_PTF                 ((uint16_t)0x0005)            /*!< PF[8] pin */
#define AFIO_EXTIC3_EXTINT8_PTG                 ((uint16_t)0x0006)            /*!< PG[8] pin */

/** EXTI9 configuration */
#define AFIO_EXTIC3_EXTINT9_PTA                 ((uint16_t)0x0000)            /*!< PA[9] pin */
#define AFIO_EXTIC3_EXTINT9_PTB                 ((uint16_t)0x0010)            /*!< PB[9] pin */
#define AFIO_EXTIC3_EXTINT9_PTC                 ((uint16_t)0x0020)            /*!< PC[9] pin */
#define AFIO_EXTIC3_EXTINT9_PTD                 ((uint16_t)0x0030)            /*!< PD[9] pin */
#define AFIO_EXTIC3_EXTINT9_PTE                 ((uint16_t)0x0040)            /*!< PE[9] pin */
#define AFIO_EXTIC3_EXTINT9_PTF                 ((uint16_t)0x0050)            /*!< PF[9] pin */
#define AFIO_EXTIC3_EXTINT9_PTG                 ((uint16_t)0x0060)            /*!< PG[9] pin */

/** EXTI10 configuration */
#define AFIO_EXTIC3_EXTINT10_PTA                ((uint16_t)0x0000)            /*!< PA[10] pin */
#define AFIO_EXTIC3_EXTINT10_PTB                ((uint16_t)0x0100)            /*!< PB[10] pin */
#define AFIO_EXTIC3_EXTINT10_PTC                ((uint16_t)0x0200)            /*!< PC[10] pin */
#define AFIO_EXTIC3_EXTINT10_PTD                ((uint16_t)0x0300)            /*!< PD[10] pin */
#define AFIO_EXTIC3_EXTINT10_PTE                ((uint16_t)0x0400)            /*!< PE[10] pin */
#define AFIO_EXTIC3_EXTINT10_PTF                ((uint16_t)0x0500)            /*!< PF[10] pin */
#define AFIO_EXTIC3_EXTINT10_PTG                ((uint16_t)0x0600)            /*!< PG[10] pin */

/** EXTI11 configuration */
#define AFIO_EXTIC3_EXTINT11_PTA                ((uint16_t)0x0000)            /*!< PA[11] pin */
#define AFIO_EXTIC3_EXTINT11_PTB                ((uint16_t)0x1000)            /*!< PB[11] pin */
#define AFIO_EXTIC3_EXTINT11_PTC                ((uint16_t)0x2000)            /*!< PC[11] pin */
#define AFIO_EXTIC3_EXTINT11_PTD                ((uint16_t)0x3000)            /*!< PD[11] pin */
#define AFIO_EXTIC3_EXTINT11_PTE                ((uint16_t)0x4000)            /*!< PE[11] pin */
#define AFIO_EXTIC3_EXTINT11_PTF                ((uint16_t)0x5000)            /*!< PF[11] pin */
#define AFIO_EXTIC3_EXTINT11_PTG                ((uint16_t)0x6000)            /*!< PG[11] pin */

/*****************  Bit definition for AFIO_EXTIC4 register  *****************/
#define AFIO_EXTIC4_EXTINT12                    ((uint16_t)0x000F)            /*!< EXTI 12 configuration */
#define AFIO_EXTIC4_EXTINT13                    ((uint16_t)0x00F0)            /*!< EXTI 13 configuration */
#define AFIO_EXTIC4_EXTINT14                    ((uint16_t)0x0F00)            /*!< EXTI 14 configuration */
#define AFIO_EXTIC4_EXTINT15                    ((uint16_t)0xF000)            /*!< EXTI 15 configuration */

/** EXTI12 configuration */
#define AFIO_EXTIC4_EXTINT12_PTA                ((uint16_t)0x0000)            /*!< PA[12] pin */
#define AFIO_EXTIC4_EXTINT12_PTB                ((uint16_t)0x0001)            /*!< PB[12] pin */
#define AFIO_EXTIC4_EXTINT12_PTC                ((uint16_t)0x0002)            /*!< PC[12] pin */
#define AFIO_EXTIC4_EXTINT12_PTD                ((uint16_t)0x0003)            /*!< PD[12] pin */
#define AFIO_EXTIC4_EXTINT12_PTE                ((uint16_t)0x0004)            /*!< PE[12] pin */
#define AFIO_EXTIC4_EXTINT12_PTF                ((uint16_t)0x0005)            /*!< PF[12] pin */
#define AFIO_EXTIC4_EXTINT12_PTG                ((uint16_t)0x0006)            /*!< PG[12] pin */

/** EXTI13 configuration */
#define AFIO_EXTIC4_EXTINT13_PTA                ((uint16_t)0x0000)            /*!< PA[13] pin */
#define AFIO_EXTIC4_EXTINT13_PTB                ((uint16_t)0x0010)            /*!< PB[13] pin */
#define AFIO_EXTIC4_EXTINT13_PTC                ((uint16_t)0x0020)            /*!< PC[13] pin */
#define AFIO_EXTIC4_EXTINT13_PTD                ((uint16_t)0x0030)            /*!< PD[13] pin */
#define AFIO_EXTIC4_EXTINT13_PTE                ((uint16_t)0x0040)            /*!< PE[13] pin */
#define AFIO_EXTIC4_EXTINT13_PTF                ((uint16_t)0x0050)            /*!< PF[13] pin */
#define AFIO_EXTIC4_EXTINT13_PTG                ((uint16_t)0x0060)            /*!< PG[13] pin */

/** EXTI14 configuration */
#define AFIO_EXTIC4_EXTINT14_PTA                ((uint16_t)0x0000)            /*!< PA[14] pin */
#define AFIO_EXTIC4_EXTINT14_PTB                ((uint16_t)0x0100)            /*!< PB[14] pin */
#define AFIO_EXTIC4_EXTINT14_PTC                ((uint16_t)0x0200)            /*!< PC[14] pin */
#define AFIO_EXTIC4_EXTINT14_PTD                ((uint16_t)0x0300)            /*!< PD[14] pin */
#define AFIO_EXTIC4_EXTINT14_PTE                ((uint16_t)0x0400)            /*!< PE[14] pin */
#define AFIO_EXTIC4_EXTINT14_PTF                ((uint16_t)0x0500)            /*!< PF[14] pin */
#define AFIO_EXTIC4_EXTINT14_PTG                ((uint16_t)0x0600)            /*!< PG[14] pin */

/** EXTI15 configuration */
#define AFIO_EXTIC4_EXTINT15_PTA                ((uint16_t)0x0000)            /*!< PA[15] pin */
#define AFIO_EXTIC4_EXTINT15_PTB                ((uint16_t)0x1000)            /*!< PB[15] pin */
#define AFIO_EXTIC4_EXTINT15_PTC                ((uint16_t)0x2000)            /*!< PC[15] pin */
#define AFIO_EXTIC4_EXTINT15_PTD                ((uint16_t)0x3000)            /*!< PD[15] pin */
#define AFIO_EXTIC4_EXTINT15_PTE                ((uint16_t)0x4000)            /*!< PE[15] pin */
#define AFIO_EXTIC4_EXTINT15_PTF                ((uint16_t)0x5000)            /*!< PF[15] pin */
#define AFIO_EXTIC4_EXTINT15_PTG                ((uint16_t)0x6000)            /*!< PG[15] pin */


/******************  Bit definition for AFIO_MAP2 register  ******************/
#define AFIO_MAP2_TMR9_REMAP                    ((uint32_t)0x00000020)        /*!< TMR9 remapping */
#define AFIO_MAP2_TMR10_REMAP                   ((uint32_t)0x00000040)        /*!< TMR10 remapping */
#define AFIO_MAP2_TMR11_REMAP                   ((uint32_t)0x00000080)        /*!< TMR11 remapping */
#define AFIO_MAP2_TMR13_REMAP                   ((uint32_t)0x00000100)        /*!< TMR13 remapping */
#define AFIO_MAP2_TMR14_REMAP                   ((uint32_t)0x00000200)        /*!< TMR14 remapping */
#define AFIO_MAP2_XMC_NADV_REMAP                ((uint32_t)0x00000400)        /*!< XMC NADV remapping */
#define AFIO_MAP2_TMR15_REMAP                   ((uint32_t)0x00000001)        /*!< TMR15 remapping */
#define AFIO_MAP2_SPI4_REMAP                    ((uint32_t)0x00020000)        /*!< SPI4 remapping */
#define AFIO_MAP2_I2C3_REMAP                    ((uint32_t)0x00040000)        /*!< I2C3 remapping */
#define AFIO_MAP2_SDIO2_REMAP_01                ((uint32_t)0x00080000)        /*!< SDIO2 remapping01 */
#define AFIO_MAP2_SDIO2_REMAP_10                ((uint32_t)0x00100000)        /*!< SDIO2 remapping10 */
#define AFIO_MAP2_SDIO2_REMAP_11                ((uint32_t)0x00180000)        /*!< SDIO2 remapping11 */
#define AFIO_MAP2_EXT_FLASH_REMAP               ((uint32_t)0x00200000)        /*!< External FLASH remapping */

/******************  Bit definition for AFIO_MAP3 register  ******************/
#define AFIO_MAP3_TMR9_GRMP                     ((uint32_t)0x00000002)        /*!< TMR9 Alternate Function mapping  */
#define AFIO_MAP3_TMR10_GRMP                    ((uint32_t)0x00000020)        /*!< TMR10 Alternate Function mapping  */
#define AFIO_MAP3_TMR11_GRMP                    ((uint32_t)0x00000200)        /*!< TMR11 Alternate Function mapping  */

/******************  Bit definition for AFIO_MAP4 register  ******************/
#define AFIO_MAP4_TMR1_GRMP                     ((uint32_t)0x00000001)        /*!< TMR1 Alternate Function mapping */
#define AFIO_MAP4_TMR2_GRMP_01                  ((uint32_t)0x00000010)        /*!< TMR2 Alternate Function mapping 0001*/
#define AFIO_MAP4_TMR2_GRMP_10                  ((uint32_t)0x00000020)        /*!< TMR2 Alternate Function mapping 0010*/
#define AFIO_MAP4_TMR2_GRMP_11                  ((uint32_t)0x00000030)        /*!< TMR2 Alternate Function mapping 0011*/
#define AFIO_MAP4_TMR3_GRMP_10                  ((uint32_t)0x00000200)        /*!< TMR3 Alternate Function mapping 0010*/
#define AFIO_MAP4_TMR3_GRMP_11                  ((uint32_t)0x00000300)        /*!< TMR3 Alternate Function mapping 0011*/
#define AFIO_MAP4_TMR5_GRMP                     ((uint32_t)0x00010000)        /*!< TMR5 Alternate Function mapping : CH1/CH2*/
#define AFIO_MAP4_TMR5CH4_INTLRE                ((uint32_t)0x00080000)        /*!< TMR5 Channel4 Internal Remap */

/******************  Bit definition for AFIO_MAP5 register  ******************/
#define AFIO_MAP5_I2C1_GRMP_01                  ((uint32_t)0x00000010)        /*!< I2C1 Alternate Function mapping 0001*/
#define AFIO_MAP5_I2C1_GRMP_11                  ((uint32_t)0x00000030)        /*!< I2C1 Alternate Function mapping 0011*/
#define AFIO_MAP5_I2C2_GRMP_01                  ((uint32_t)0x00000100)        /*!< I2C2 Alternate Function mapping 0001*/
#define AFIO_MAP5_I2C2_GRMP_10                  ((uint32_t)0x00000200)        /*!< I2C2 Alternate Function mapping 0010*/
#define AFIO_MAP5_I2C2_GRMP_11                  ((uint32_t)0x00000300)        /*!< I2C2 Alternate Function mapping 0011*/
#define AFIO_MAP5_SPI1_GRMP                     ((uint32_t)0x00010000)        /*!< SPI1 Alternate Function mapping */
#define AFIO_MAP5_SPI2_GRMP                     ((uint32_t)0x00100000)        /*!< SPI2 Alternate Function mapping */

/******************  Bit definition for AFIO_MAP6 register  ******************/
#define AFIO_MAP6_CAN1_GRMP                     ((uint32_t)0x00000002)        /*!< CAN1 Alternate Function mapping */
#define AFIO_MAP6_CAN2_GRMP                     ((uint32_t)0x00000010)        /*!< CAN2 Alternate Function mapping */
#define AFIO_MAP6_SDIO_GRMP_100                 ((uint32_t)0x00000400)        /*!< SDIO Alternate Function mapping 100 */
#define AFIO_MAP6_SDIO_GRMP_101                 ((uint32_t)0x00000500)        /*!< SDIO Alternate Function mapping 101 */
#define AFIO_MAP6_SDIO_GRMP_110                 ((uint32_t)0x00000600)        /*!< SDIO Alternate Function mapping 110 */
#define AFIO_MAP6_SDIO_GRMP_111                 ((uint32_t)0x00000700)        /*!< SDIO Alternate Function mapping 111 */
#define AFIO_MAP6_USART1_GRMP                   ((uint32_t)0x00010000)        /*!< USART1 Alternate Function mapping */
#define AFIO_MAP6_USART3_GRMP                   ((uint32_t)0x01000000)        /*!< USART3 Partial Alternate Function mapping */
#define AFIO_MAP6_UART4_GRMP                    ((uint32_t)0x10000000)        /*!< UART4 Alternate Function mapping */

/******************  Bit definition for AFIO_MAP7 register  ******************/
#define AFIO_MAP7_SPIF_GRMP_1000                ((uint32_t)0x00000008)        /*!< EXT_FLASH Alternate Function mapping */ 
#define AFIO_MAP7_SPIF_GRMP_1001                ((uint32_t)0x00000009)        /*!< EXT_FLASH Alternate Function enable */ 
#define AFIO_MAP7_ADC1_GRMP_01                  ((uint32_t)0x00000010)        /*!< ADC1 External Trigger Injected Conversion remapping */
#define AFIO_MAP7_ADC1_GRMP_10                  ((uint32_t)0x00000020)        /*!< ADC1 External Trigger Regular Conversion remapping */
#define AFIO_MAP7_ADC1_GRMP_11                  ((uint32_t)0x00000030)        /*!< ADC1 External Trigger Regular & Injected Conversion remapping */
#define AFIO_MAP7_ADC2_GRMP_01                  ((uint32_t)0x00000100)        /*!< ADC2 External Trigger Injected Conversion remapping */
#define AFIO_MAP7_ADC2_GRMP_10                  ((uint32_t)0x00000200)        /*!< ADC2 External Trigger Regular Conversion remapping */
#define AFIO_MAP7_ADC2_GRMP_11                  ((uint32_t)0x00000300)        /*!< ADC2 External Trigger Regular & Injected Conversion remapping */
#define AFIO_MAP7_SWJTAG_GRMP_001               ((uint32_t)0x00010000)        /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define AFIO_MAP7_SWJTAG_GRMP_010               ((uint32_t)0x00020000)        /*!< JTAG-DP Disabled and SW-DP Enabled */
#define AFIO_MAP7_SWJTAG_GRMP_100               ((uint32_t)0x00040000)        /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */
#define AFIO_MAP7_PD01_GRMP                     ((uint32_t)0x00100000)        /*!< PD01 Alternate Function mapping */ 


/******************************************************************************/
/*                                                                            */
/*                               SystemTick                                   */
/*                                                                            */
/******************************************************************************/

/*****************  Bit definition for SysTick_CTRL register  *****************/
#define  SysTick_CTRL_ENABLE                    ((uint32_t)0x00000001)        /*!< Counter enable */
#define  SysTick_CTRL_TICKINT                   ((uint32_t)0x00000002)        /*!< Counting down to 0 pends the SysTick handler */
#define  SysTick_CTRL_CLKSOURCE                 ((uint32_t)0x00000004)        /*!< Clock source */
#define  SysTick_CTRL_COUNTFLAG                 ((uint32_t)0x00010000)        /*!< Count Flag */

/*****************  Bit definition for SysTick_LOAD register  *****************/
#define  SysTick_LOAD_RELOAD                    ((uint32_t)0x00FFFFFF)        /*!< Value to load into the SysTick Current Value Register when the counter reaches 0 */

/*****************  Bit definition for SysTick_VAL register  ******************/
#define  SysTick_VAL_CURRENT                    ((uint32_t)0x00FFFFFF)        /*!< Current value at the time the register is accessed */

/*****************  Bit definition for SysTick_CALIB register  ****************/
#define  SysTick_CALIB_TENMS                    ((uint32_t)0x00FFFFFF)        /*!< Reload value to use for 10ms timing */
#define  SysTick_CALIB_SKEW                     ((uint32_t)0x40000000)        /*!< Calibration value is not exactly 10 ms */
#define  SysTick_CALIB_NOREF                    ((uint32_t)0x80000000)        /*!< The reference clock is not provided */

/******************************************************************************/
/*                                                                            */
/*                  Nested Vectored Interrupt Controller                      */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for NVIC_ISER register  *******************/
#define  NVIC_ISER_SETENA                       ((uint32_t)0xFFFFFFFF)        /*!< Interrupt set enable bits */
#define  NVIC_ISER_SETENA_0                     ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ISER_SETENA_1                     ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ISER_SETENA_2                     ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ISER_SETENA_3                     ((uint32_t)0x00000008)        /*!< bit 3 */
#define  NVIC_ISER_SETENA_4                     ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ISER_SETENA_5                     ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ISER_SETENA_6                     ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ISER_SETENA_7                     ((uint32_t)0x00000080)        /*!< bit 7 */
#define  NVIC_ISER_SETENA_8                     ((uint32_t)0x00000100)        /*!< bit 8 */
#define  NVIC_ISER_SETENA_9                     ((uint32_t)0x00000200)        /*!< bit 9 */
#define  NVIC_ISER_SETENA_10                    ((uint32_t)0x00000400)        /*!< bit 10 */
#define  NVIC_ISER_SETENA_11                    ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ISER_SETENA_12                    ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ISER_SETENA_13                    ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ISER_SETENA_14                    ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ISER_SETENA_15                    ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ISER_SETENA_16                    ((uint32_t)0x00010000)        /*!< bit 16 */
#define  NVIC_ISER_SETENA_17                    ((uint32_t)0x00020000)        /*!< bit 17 */
#define  NVIC_ISER_SETENA_18                    ((uint32_t)0x00040000)        /*!< bit 18 */
#define  NVIC_ISER_SETENA_19                    ((uint32_t)0x00080000)        /*!< bit 19 */
#define  NVIC_ISER_SETENA_20                    ((uint32_t)0x00100000)        /*!< bit 20 */
#define  NVIC_ISER_SETENA_21                    ((uint32_t)0x00200000)        /*!< bit 21 */
#define  NVIC_ISER_SETENA_22                    ((uint32_t)0x00400000)        /*!< bit 22 */
#define  NVIC_ISER_SETENA_23                    ((uint32_t)0x00800000)        /*!< bit 23 */
#define  NVIC_ISER_SETENA_24                    ((uint32_t)0x01000000)        /*!< bit 24 */
#define  NVIC_ISER_SETENA_25                    ((uint32_t)0x02000000)        /*!< bit 25 */
#define  NVIC_ISER_SETENA_26                    ((uint32_t)0x04000000)        /*!< bit 26 */
#define  NVIC_ISER_SETENA_27                    ((uint32_t)0x08000000)        /*!< bit 27 */
#define  NVIC_ISER_SETENA_28                    ((uint32_t)0x10000000)        /*!< bit 28 */
#define  NVIC_ISER_SETENA_29                    ((uint32_t)0x20000000)        /*!< bit 29 */
#define  NVIC_ISER_SETENA_30                    ((uint32_t)0x40000000)        /*!< bit 30 */
#define  NVIC_ISER_SETENA_31                    ((uint32_t)0x80000000)        /*!< bit 31 */

/******************  Bit definition for NVIC_ICER register  *******************/
#define  NVIC_ICER_CLRENA                       ((uint32_t)0xFFFFFFFF)        /*!< Interrupt clear-enable bits */
#define  NVIC_ICER_CLRENA_0                     ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ICER_CLRENA_1                     ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ICER_CLRENA_2                     ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ICER_CLRENA_3                     ((uint32_t)0x00000008)        /*!< bit 3 */
#define  NVIC_ICER_CLRENA_4                     ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ICER_CLRENA_5                     ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ICER_CLRENA_6                     ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ICER_CLRENA_7                     ((uint32_t)0x00000080)        /*!< bit 7 */
#define  NVIC_ICER_CLRENA_8                     ((uint32_t)0x00000100)        /*!< bit 8 */
#define  NVIC_ICER_CLRENA_9                     ((uint32_t)0x00000200)        /*!< bit 9 */
#define  NVIC_ICER_CLRENA_10                    ((uint32_t)0x00000400)        /*!< bit 10 */
#define  NVIC_ICER_CLRENA_11                    ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ICER_CLRENA_12                    ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ICER_CLRENA_13                    ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ICER_CLRENA_14                    ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ICER_CLRENA_15                    ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ICER_CLRENA_16                    ((uint32_t)0x00010000)        /*!< bit 16 */
#define  NVIC_ICER_CLRENA_17                    ((uint32_t)0x00020000)        /*!< bit 17 */
#define  NVIC_ICER_CLRENA_18                    ((uint32_t)0x00040000)        /*!< bit 18 */
#define  NVIC_ICER_CLRENA_19                    ((uint32_t)0x00080000)        /*!< bit 19 */
#define  NVIC_ICER_CLRENA_20                    ((uint32_t)0x00100000)        /*!< bit 20 */
#define  NVIC_ICER_CLRENA_21                    ((uint32_t)0x00200000)        /*!< bit 21 */
#define  NVIC_ICER_CLRENA_22                    ((uint32_t)0x00400000)        /*!< bit 22 */
#define  NVIC_ICER_CLRENA_23                    ((uint32_t)0x00800000)        /*!< bit 23 */
#define  NVIC_ICER_CLRENA_24                    ((uint32_t)0x01000000)        /*!< bit 24 */
#define  NVIC_ICER_CLRENA_25                    ((uint32_t)0x02000000)        /*!< bit 25 */
#define  NVIC_ICER_CLRENA_26                    ((uint32_t)0x04000000)        /*!< bit 26 */
#define  NVIC_ICER_CLRENA_27                    ((uint32_t)0x08000000)        /*!< bit 27 */
#define  NVIC_ICER_CLRENA_28                    ((uint32_t)0x10000000)        /*!< bit 28 */
#define  NVIC_ICER_CLRENA_29                    ((uint32_t)0x20000000)        /*!< bit 29 */
#define  NVIC_ICER_CLRENA_30                    ((uint32_t)0x40000000)        /*!< bit 30 */
#define  NVIC_ICER_CLRENA_31                    ((uint32_t)0x80000000)        /*!< bit 31 */

/******************  Bit definition for NVIC_ISPR register  *******************/
#define  NVIC_ISPR_SETPEND                      ((uint32_t)0xFFFFFFFF)        /*!< Interrupt set-pending bits */
#define  NVIC_ISPR_SETPEND_0                    ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ISPR_SETPEND_1                    ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ISPR_SETPEND_2                    ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ISPR_SETPEND_3                    ((uint32_t)0x00000008)        /*!< bit 3 */
#define  NVIC_ISPR_SETPEND_4                    ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ISPR_SETPEND_5                    ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ISPR_SETPEND_6                    ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ISPR_SETPEND_7                    ((uint32_t)0x00000080)        /*!< bit 7 */
#define  NVIC_ISPR_SETPEND_8                    ((uint32_t)0x00000100)        /*!< bit 8 */
#define  NVIC_ISPR_SETPEND_9                    ((uint32_t)0x00000200)        /*!< bit 9 */
#define  NVIC_ISPR_SETPEND_10                   ((uint32_t)0x00000400)        /*!< bit 10 */
#define  NVIC_ISPR_SETPEND_11                   ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ISPR_SETPEND_12                   ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ISPR_SETPEND_13                   ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ISPR_SETPEND_14                   ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ISPR_SETPEND_15                   ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ISPR_SETPEND_16                   ((uint32_t)0x00010000)        /*!< bit 16 */
#define  NVIC_ISPR_SETPEND_17                   ((uint32_t)0x00020000)        /*!< bit 17 */
#define  NVIC_ISPR_SETPEND_18                   ((uint32_t)0x00040000)        /*!< bit 18 */
#define  NVIC_ISPR_SETPEND_19                   ((uint32_t)0x00080000)        /*!< bit 19 */
#define  NVIC_ISPR_SETPEND_20                   ((uint32_t)0x00100000)        /*!< bit 20 */
#define  NVIC_ISPR_SETPEND_21                   ((uint32_t)0x00200000)        /*!< bit 21 */
#define  NVIC_ISPR_SETPEND_22                   ((uint32_t)0x00400000)        /*!< bit 22 */
#define  NVIC_ISPR_SETPEND_23                   ((uint32_t)0x00800000)        /*!< bit 23 */
#define  NVIC_ISPR_SETPEND_24                   ((uint32_t)0x01000000)        /*!< bit 24 */
#define  NVIC_ISPR_SETPEND_25                   ((uint32_t)0x02000000)        /*!< bit 25 */
#define  NVIC_ISPR_SETPEND_26                   ((uint32_t)0x04000000)        /*!< bit 26 */
#define  NVIC_ISPR_SETPEND_27                   ((uint32_t)0x08000000)        /*!< bit 27 */
#define  NVIC_ISPR_SETPEND_28                   ((uint32_t)0x10000000)        /*!< bit 28 */
#define  NVIC_ISPR_SETPEND_29                   ((uint32_t)0x20000000)        /*!< bit 29 */
#define  NVIC_ISPR_SETPEND_30                   ((uint32_t)0x40000000)        /*!< bit 30 */
#define  NVIC_ISPR_SETPEND_31                   ((uint32_t)0x80000000)        /*!< bit 31 */

/******************  Bit definition for NVIC_ICPR register  *******************/
#define  NVIC_ICPR_CLRPEND                      ((uint32_t)0xFFFFFFFF)        /*!< Interrupt clear-pending bits */
#define  NVIC_ICPR_CLRPEND_0                    ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ICPR_CLRPEND_1                    ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ICPR_CLRPEND_2                    ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ICPR_CLRPEND_3                    ((uint32_t)0x00000008)        /*!< bit 3 */
#define  NVIC_ICPR_CLRPEND_4                    ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ICPR_CLRPEND_5                    ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ICPR_CLRPEND_6                    ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ICPR_CLRPEND_7                    ((uint32_t)0x00000080)        /*!< bit 7 */
#define  NVIC_ICPR_CLRPEND_8                    ((uint32_t)0x00000100)        /*!< bit 8 */
#define  NVIC_ICPR_CLRPEND_9                    ((uint32_t)0x00000200)        /*!< bit 9 */
#define  NVIC_ICPR_CLRPEND_10                   ((uint32_t)0x00000400)        /*!< bit 10 */
#define  NVIC_ICPR_CLRPEND_11                   ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ICPR_CLRPEND_12                   ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ICPR_CLRPEND_13                   ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ICPR_CLRPEND_14                   ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ICPR_CLRPEND_15                   ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ICPR_CLRPEND_16                   ((uint32_t)0x00010000)        /*!< bit 16 */
#define  NVIC_ICPR_CLRPEND_17                   ((uint32_t)0x00020000)        /*!< bit 17 */
#define  NVIC_ICPR_CLRPEND_18                   ((uint32_t)0x00040000)        /*!< bit 18 */
#define  NVIC_ICPR_CLRPEND_19                   ((uint32_t)0x00080000)        /*!< bit 19 */
#define  NVIC_ICPR_CLRPEND_20                   ((uint32_t)0x00100000)        /*!< bit 20 */
#define  NVIC_ICPR_CLRPEND_21                   ((uint32_t)0x00200000)        /*!< bit 21 */
#define  NVIC_ICPR_CLRPEND_22                   ((uint32_t)0x00400000)        /*!< bit 22 */
#define  NVIC_ICPR_CLRPEND_23                   ((uint32_t)0x00800000)        /*!< bit 23 */
#define  NVIC_ICPR_CLRPEND_24                   ((uint32_t)0x01000000)        /*!< bit 24 */
#define  NVIC_ICPR_CLRPEND_25                   ((uint32_t)0x02000000)        /*!< bit 25 */
#define  NVIC_ICPR_CLRPEND_26                   ((uint32_t)0x04000000)        /*!< bit 26 */
#define  NVIC_ICPR_CLRPEND_27                   ((uint32_t)0x08000000)        /*!< bit 27 */
#define  NVIC_ICPR_CLRPEND_28                   ((uint32_t)0x10000000)        /*!< bit 28 */
#define  NVIC_ICPR_CLRPEND_29                   ((uint32_t)0x20000000)        /*!< bit 29 */
#define  NVIC_ICPR_CLRPEND_30                   ((uint32_t)0x40000000)        /*!< bit 30 */
#define  NVIC_ICPR_CLRPEND_31                   ((uint32_t)0x80000000)        /*!< bit 31 */

/******************  Bit definition for NVIC_IABR register  *******************/
#define  NVIC_IABR_ACTIVE                       ((uint32_t)0xFFFFFFFF)        /*!< Interrupt active flags */
#define  NVIC_IABR_ACTIVE_0                     ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_IABR_ACTIVE_1                     ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_IABR_ACTIVE_2                     ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_IABR_ACTIVE_3                     ((uint32_t)0x00000008)        /*!< bit 3 */
#define  NVIC_IABR_ACTIVE_4                     ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_IABR_ACTIVE_5                     ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_IABR_ACTIVE_6                     ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_IABR_ACTIVE_7                     ((uint32_t)0x00000080)        /*!< bit 7 */
#define  NVIC_IABR_ACTIVE_8                     ((uint32_t)0x00000100)        /*!< bit 8 */
#define  NVIC_IABR_ACTIVE_9                     ((uint32_t)0x00000200)        /*!< bit 9 */
#define  NVIC_IABR_ACTIVE_10                    ((uint32_t)0x00000400)        /*!< bit 10 */
#define  NVIC_IABR_ACTIVE_11                    ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_IABR_ACTIVE_12                    ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_IABR_ACTIVE_13                    ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_IABR_ACTIVE_14                    ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_IABR_ACTIVE_15                    ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_IABR_ACTIVE_16                    ((uint32_t)0x00010000)        /*!< bit 16 */
#define  NVIC_IABR_ACTIVE_17                    ((uint32_t)0x00020000)        /*!< bit 17 */
#define  NVIC_IABR_ACTIVE_18                    ((uint32_t)0x00040000)        /*!< bit 18 */
#define  NVIC_IABR_ACTIVE_19                    ((uint32_t)0x00080000)        /*!< bit 19 */
#define  NVIC_IABR_ACTIVE_20                    ((uint32_t)0x00100000)        /*!< bit 20 */
#define  NVIC_IABR_ACTIVE_21                    ((uint32_t)0x00200000)        /*!< bit 21 */
#define  NVIC_IABR_ACTIVE_22                    ((uint32_t)0x00400000)        /*!< bit 22 */
#define  NVIC_IABR_ACTIVE_23                    ((uint32_t)0x00800000)        /*!< bit 23 */
#define  NVIC_IABR_ACTIVE_24                    ((uint32_t)0x01000000)        /*!< bit 24 */
#define  NVIC_IABR_ACTIVE_25                    ((uint32_t)0x02000000)        /*!< bit 25 */
#define  NVIC_IABR_ACTIVE_26                    ((uint32_t)0x04000000)        /*!< bit 26 */
#define  NVIC_IABR_ACTIVE_27                    ((uint32_t)0x08000000)        /*!< bit 27 */
#define  NVIC_IABR_ACTIVE_28                    ((uint32_t)0x10000000)        /*!< bit 28 */
#define  NVIC_IABR_ACTIVE_29                    ((uint32_t)0x20000000)        /*!< bit 29 */
#define  NVIC_IABR_ACTIVE_30                    ((uint32_t)0x40000000)        /*!< bit 30 */
#define  NVIC_IABR_ACTIVE_31                    ((uint32_t)0x80000000)        /*!< bit 31 */

/******************  Bit definition for NVIC_PRI0 register  *******************/
#define  NVIC_IPR0_PRI_0                        ((uint32_t)0x000000FF)        /*!< Priority of interrupt 0 */
#define  NVIC_IPR0_PRI_1                        ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 1 */
#define  NVIC_IPR0_PRI_2                        ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 2 */
#define  NVIC_IPR0_PRI_3                        ((uint32_t)0xFF000000)        /*!< Priority of interrupt 3 */

/******************  Bit definition for NVIC_PRI1 register  *******************/
#define  NVIC_IPR1_PRI_4                        ((uint32_t)0x000000FF)        /*!< Priority of interrupt 4 */
#define  NVIC_IPR1_PRI_5                        ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 5 */
#define  NVIC_IPR1_PRI_6                        ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 6 */
#define  NVIC_IPR1_PRI_7                        ((uint32_t)0xFF000000)        /*!< Priority of interrupt 7 */

/******************  Bit definition for NVIC_PRI2 register  *******************/
#define  NVIC_IPR2_PRI_8                        ((uint32_t)0x000000FF)        /*!< Priority of interrupt 8 */
#define  NVIC_IPR2_PRI_9                        ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 9 */
#define  NVIC_IPR2_PRI_10                       ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 10 */
#define  NVIC_IPR2_PRI_11                       ((uint32_t)0xFF000000)        /*!< Priority of interrupt 11 */

/******************  Bit definition for NVIC_PRI3 register  *******************/
#define  NVIC_IPR3_PRI_12                       ((uint32_t)0x000000FF)        /*!< Priority of interrupt 12 */
#define  NVIC_IPR3_PRI_13                       ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 13 */
#define  NVIC_IPR3_PRI_14                       ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 14 */
#define  NVIC_IPR3_PRI_15                       ((uint32_t)0xFF000000)        /*!< Priority of interrupt 15 */

/******************  Bit definition for NVIC_PRI4 register  *******************/
#define  NVIC_IPR4_PRI_16                       ((uint32_t)0x000000FF)        /*!< Priority of interrupt 16 */
#define  NVIC_IPR4_PRI_17                       ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 17 */
#define  NVIC_IPR4_PRI_18                       ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 18 */
#define  NVIC_IPR4_PRI_19                       ((uint32_t)0xFF000000)        /*!< Priority of interrupt 19 */

/******************  Bit definition for NVIC_PRI5 register  *******************/
#define  NVIC_IPR5_PRI_20                       ((uint32_t)0x000000FF)        /*!< Priority of interrupt 20 */
#define  NVIC_IPR5_PRI_21                       ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 21 */
#define  NVIC_IPR5_PRI_22                       ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 22 */
#define  NVIC_IPR5_PRI_23                       ((uint32_t)0xFF000000)        /*!< Priority of interrupt 23 */

/******************  Bit definition for NVIC_PRI6 register  *******************/
#define  NVIC_IPR6_PRI_24                       ((uint32_t)0x000000FF)        /*!< Priority of interrupt 24 */
#define  NVIC_IPR6_PRI_25                       ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 25 */
#define  NVIC_IPR6_PRI_26                       ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 26 */
#define  NVIC_IPR6_PRI_27                       ((uint32_t)0xFF000000)        /*!< Priority of interrupt 27 */

/******************  Bit definition for NVIC_PRI7 register  *******************/
#define  NVIC_IPR7_PRI_28                       ((uint32_t)0x000000FF)        /*!< Priority of interrupt 28 */
#define  NVIC_IPR7_PRI_29                       ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 29 */
#define  NVIC_IPR7_PRI_30                       ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 30 */
#define  NVIC_IPR7_PRI_31                       ((uint32_t)0xFF000000)        /*!< Priority of interrupt 31 */

/******************  Bit definition for SCB_CPUID register  *******************/
#define  SCB_CPUID_REVISION                     ((uint32_t)0x0000000F)        /*!< Implementation defined revision number */
#define  SCB_CPUID_PARTNO                       ((uint32_t)0x0000FFF0)        /*!< Number of processor within family */
#define  SCB_CPUID_Constant                     ((uint32_t)0x000F0000)        /*!< Reads as 0x0F */
#define  SCB_CPUID_VARIANT                      ((uint32_t)0x00F00000)        /*!< Implementation defined variant number */
#define  SCB_CPUID_IMPLEMENTER                  ((uint32_t)0xFF000000)        /*!< Implementer code. ARM is 0x41 */

/*******************  Bit definition for SCB_ICSR register  *******************/
#define  SCB_ICSR_VECTACTIVE                    ((uint32_t)0x000001FF)        /*!< Active ISR number field */
#define  SCB_ICSR_RETTOBASE                     ((uint32_t)0x00000800)        /*!< All active exceptions minus the IPSR_current_exception yields the empty set */
#define  SCB_ICSR_VECTPENDING                   ((uint32_t)0x003FF000)        /*!< Pending ISR number field */
#define  SCB_ICSR_ISRPENDING                    ((uint32_t)0x00400000)        /*!< Interrupt pending flag */
#define  SCB_ICSR_ISRPREEMPT                    ((uint32_t)0x00800000)        /*!< It indicates that a pending interrupt becomes active in the next running cycle */
#define  SCB_ICSR_PENDSTCLR                     ((uint32_t)0x02000000)        /*!< Clear pending SysTick bit */
#define  SCB_ICSR_PENDSTSET                     ((uint32_t)0x04000000)        /*!< Set pending SysTick bit */
#define  SCB_ICSR_PENDSVCLR                     ((uint32_t)0x08000000)        /*!< Clear pending pendSV bit */
#define  SCB_ICSR_PENDSVSET                     ((uint32_t)0x10000000)        /*!< Set pending pendSV bit */
#define  SCB_ICSR_NMIPENDSET                    ((uint32_t)0x80000000)        /*!< Set pending NMI bit */

/*******************  Bit definition for SCB_VTOR register  *******************/
#define  SCB_VTOR_TBLOFF                        ((uint32_t)0x1FFFFF80)        /*!< Vector table base offset field */
#define  SCB_VTOR_TBLBASE                       ((uint32_t)0x20000000)        /*!< Table base in code(0) or RAM(1) */

/*******************  Bit definition for SCB_AIRCR register  *******************/
#define  SCB_AIRCR_VECTRESET                    ((uint32_t)0x00000001)        /*!< System Reset bit */
#define  SCB_AIRCR_VECTCLRACTIVE                ((uint32_t)0x00000002)        /*!< Clear active vector bit */
#define  SCB_AIRCR_SYSRESETREQ                  ((uint32_t)0x00000004)        /*!< Requests chip control logic to generate a reset */

#define  SCB_AIRCR_PRIGROUP                     ((uint32_t)0x00000700)        /*!< PRIGROUP[2:0] bits (Priority group) */
#define  SCB_AIRCR_PRIGROUP_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  SCB_AIRCR_PRIGROUP_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  SCB_AIRCR_PRIGROUP_2                   ((uint32_t)0x00000400)        /*!< Bit 2  */

/* prority group configuration */           
#define  SCB_AIRCR_PRIGROUP0                    ((uint32_t)0x00000000)        /*!< Priority group=0 (7 bits of pre-emption priority, 1 bit of subpriority) */
#define  SCB_AIRCR_PRIGROUP1                    ((uint32_t)0x00000100)        /*!< Priority group=1 (6 bits of pre-emption priority, 2 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP2                    ((uint32_t)0x00000200)        /*!< Priority group=2 (5 bits of pre-emption priority, 3 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP3                    ((uint32_t)0x00000300)        /*!< Priority group=3 (4 bits of pre-emption priority, 4 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP4                    ((uint32_t)0x00000400)        /*!< Priority group=4 (3 bits of pre-emption priority, 5 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP5                    ((uint32_t)0x00000500)        /*!< Priority group=5 (2 bits of pre-emption priority, 6 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP6                    ((uint32_t)0x00000600)        /*!< Priority group=6 (1 bit of pre-emption priority, 7 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP7                    ((uint32_t)0x00000700)        /*!< Priority group=7 (no pre-emption priority, 8 bits of subpriority) */

#define  SCB_AIRCR_ENDIANESS                    ((uint32_t)0x00008000)        /*!< Data endianness bit */
#define  SCB_AIRCR_VECTKEY                      ((uint32_t)0xFFFF0000)        /*!< Register key (VECTKEY) - Reads as 0xFA05 (VECTKEYSTAT) */

/*******************  Bit definition for SCB_SCR register  ********************/
#define  SCB_SCR_SLEEPONEXIT                    ((uint8_t)0x02)               /*!< Sleep on exit bit */
#define  SCB_SCR_SLEEPDEEP                      ((uint8_t)0x04)               /*!< Sleep deep bit */
#define  SCB_SCR_SEVONPEND                      ((uint8_t)0x10)               /*!< Wake up from WFE */

/********************  Bit definition for SCB_CCR register  *******************/
#define  SCB_CCR_NONBASETHRDENA                 ((uint16_t)0x0001)            /*!< Thread mode can be entered from any level in Handler mode by controlled return value */
#define  SCB_CCR_USERSETMPEND                   ((uint16_t)0x0002)            /*!< Enables user code to write the Software Trigger Interrupt register to trigger (pend) a Main exception */
#define  SCB_CCR_UNALIGN_TRP                    ((uint16_t)0x0008)            /*!< Trap for unaligned access */
#define  SCB_CCR_DIV_0_TRP                      ((uint16_t)0x0010)            /*!< Trap on Divide by 0 */
#define  SCB_CCR_BFHFNMIGN                      ((uint16_t)0x0100)            /*!< Handlers running at priority -1 and -2 */
#define  SCB_CCR_STKALIGN                       ((uint16_t)0x0200)            /*!< On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned */

/*******************  Bit definition for SCB_SHPR register ********************/
#define  SCB_SHPR_PRI_N                         ((uint32_t)0x000000FF)        /*!< Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor */
#define  SCB_SHPR_PRI_N1                        ((uint32_t)0x0000FF00)        /*!< Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved */
#define  SCB_SHPR_PRI_N2                        ((uint32_t)0x00FF0000)        /*!< Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV */
#define  SCB_SHPR_PRI_N3                        ((uint32_t)0xFF000000)        /*!< Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick */

/******************  Bit definition for SCB_SHCSR register  *******************/
#define  SCB_SHCSR_MEMFAULTACT                  ((uint32_t)0x00000001)        /*!< MemManage is active */
#define  SCB_SHCSR_BUSFAULTACT                  ((uint32_t)0x00000002)        /*!< BusFault is active */
#define  SCB_SHCSR_USGFAULTACT                  ((uint32_t)0x00000008)        /*!< UsageFault is active */
#define  SCB_SHCSR_SVCALLACT                    ((uint32_t)0x00000080)        /*!< SVCall is active */
#define  SCB_SHCSR_MONITORACT                   ((uint32_t)0x00000100)        /*!< Monitor is active */
#define  SCB_SHCSR_PENDSVACT                    ((uint32_t)0x00000400)        /*!< PendSV is active */
#define  SCB_SHCSR_SYSTICKACT                   ((uint32_t)0x00000800)        /*!< SysTick is active */
#define  SCB_SHCSR_USGFAULTPENDED               ((uint32_t)0x00001000)        /*!< Usage Fault is pended */
#define  SCB_SHCSR_MEMFAULTPENDED               ((uint32_t)0x00002000)        /*!< MemManage is pended */
#define  SCB_SHCSR_BUSFAULTPENDED               ((uint32_t)0x00004000)        /*!< Bus Fault is pended */
#define  SCB_SHCSR_SVCALLPENDED                 ((uint32_t)0x00008000)        /*!< SVCall is pended */
#define  SCB_SHCSR_MEMFAULTENA                  ((uint32_t)0x00010000)        /*!< MemManage enable */
#define  SCB_SHCSR_BUSFAULTENA                  ((uint32_t)0x00020000)        /*!< Bus Fault enable */
#define  SCB_SHCSR_USGFAULTENA                  ((uint32_t)0x00040000)        /*!< UsageFault enable */

/*******************  Bit definition for SCB_CFSR register  *******************/
/** MFSR */
#define  SCB_CFSR_IACCVIOL                      ((uint32_t)0x00000001)        /*!< Instruction access violation */
#define  SCB_CFSR_DACCVIOL                      ((uint32_t)0x00000002)        /*!< Data access violation */
#define  SCB_CFSR_MUNSTKERR                     ((uint32_t)0x00000008)        /*!< Unstacking error */
#define  SCB_CFSR_MSTKERR                       ((uint32_t)0x00000010)        /*!< Stacking error */
#define  SCB_CFSR_MMARVALID                     ((uint32_t)0x00000080)        /*!< Memory Manage Address Register address valid flag */
/** BFSR */                                  
#define  SCB_CFSR_IBUSERR                       ((uint32_t)0x00000100)        /*!< Instruction bus error flag */
#define  SCB_CFSR_PRECISERR                     ((uint32_t)0x00000200)        /*!< Precise data bus error */
#define  SCB_CFSR_IMPRECISERR                   ((uint32_t)0x00000400)        /*!< Imprecise data bus error */
#define  SCB_CFSR_UNSTKERR                      ((uint32_t)0x00000800)        /*!< Unstacking error */
#define  SCB_CFSR_STKERR                        ((uint32_t)0x00001000)        /*!< Stacking error */
#define  SCB_CFSR_BFARVALID                     ((uint32_t)0x00008000)        /*!< Bus Fault Address Register address valid flag */
/** UFSR */                                  
#define  SCB_CFSR_UNDEFINSTR                    ((uint32_t)0x00010000)        /*!< The processor attempt to execute an undefined instruction */
#define  SCB_CFSR_INVSTATE                      ((uint32_t)0x00020000)        /*!< Invalid combination of EPSR and instruction */
#define  SCB_CFSR_INVPC                         ((uint32_t)0x00040000)        /*!< Attempt to load EXC_RETURN into pc illegally */
#define  SCB_CFSR_NOCP                          ((uint32_t)0x00080000)        /*!< Attempt to use a coprocessor instruction */
#define  SCB_CFSR_UNALIGNED                     ((uint32_t)0x01000000)        /*!< Fault occurs when there is an attempt to make an unaligned memory access */
#define  SCB_CFSR_DIVBYZERO                     ((uint32_t)0x02000000)        /*!< Fault occurs when SDIV or DIV instruction is used with a divisor of 0 */

/*******************  Bit definition for SCB_HFSR register  *******************/
#define  SCB_HFSR_VECTTBL                       ((uint32_t)0x00000002)        /*!< Fault occurs because of vector table read on exception processing */
#define  SCB_HFSR_FORCED                        ((uint32_t)0x40000000)        /*!< Hard Fault activated when a configurable Fault was received and cannot activate */
#define  SCB_HFSR_DEBUGEVT                      ((uint32_t)0x80000000)        /*!< Fault related to debug */

/*******************  Bit definition for SCB_DFSR register  *******************/
#define  SCB_DFSR_HALTED                        ((uint8_t)0x01)               /*!< Halt request flag */
#define  SCB_DFSR_BKPT                          ((uint8_t)0x02)               /*!< BKPT flag */
#define  SCB_DFSR_DWTTRAP                       ((uint8_t)0x04)               /*!< Data Watchpoint and Trace (DWT) flag */
#define  SCB_DFSR_VCATCH                        ((uint8_t)0x08)               /*!< Vector catch flag */
#define  SCB_DFSR_EXTERNAL                      ((uint8_t)0x10)               /*!< External debug request flag */

/*******************  Bit definition for SCB_MMFAR register  ******************/
#define  SCB_MMFAR_ADDRESS                      ((uint32_t)0xFFFFFFFF)        /*!< Mem Manage fault address field */

/*******************  Bit definition for SCB_BFAR register  *******************/
#define  SCB_BFAR_ADDRESS                       ((uint32_t)0xFFFFFFFF)        /*!< Bus fault address field */

/*******************  Bit definition for SCB_AFSR register  *******************/
#define  SCB_AFSR_IMPDEF                        ((uint32_t)0xFFFFFFFF)        /*!< Implementation defined */

/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for EXTI_INTEN register  *******************/
#define  EXTI_INTEN_LN0                         ((uint32_t)0x00000001)        /*!< Interrupt Mask on line 0 */
#define  EXTI_INTEN_LN1                         ((uint32_t)0x00000002)        /*!< Interrupt Mask on line 1 */
#define  EXTI_INTEN_LN2                         ((uint32_t)0x00000004)        /*!< Interrupt Mask on line 2 */
#define  EXTI_INTEN_LN3                         ((uint32_t)0x00000008)        /*!< Interrupt Mask on line 3 */
#define  EXTI_INTEN_LN4                         ((uint32_t)0x00000010)        /*!< Interrupt Mask on line 4 */
#define  EXTI_INTEN_LN5                         ((uint32_t)0x00000020)        /*!< Interrupt Mask on line 5 */
#define  EXTI_INTEN_LN6                         ((uint32_t)0x00000040)        /*!< Interrupt Mask on line 6 */
#define  EXTI_INTEN_LN7                         ((uint32_t)0x00000080)        /*!< Interrupt Mask on line 7 */
#define  EXTI_INTEN_LN8                         ((uint32_t)0x00000100)        /*!< Interrupt Mask on line 8 */
#define  EXTI_INTEN_LN9                         ((uint32_t)0x00000200)        /*!< Interrupt Mask on line 9 */
#define  EXTI_INTEN_LN10                        ((uint32_t)0x00000400)        /*!< Interrupt Mask on line 10 */
#define  EXTI_INTEN_LN11                        ((uint32_t)0x00000800)        /*!< Interrupt Mask on line 11 */
#define  EXTI_INTEN_LN12                        ((uint32_t)0x00001000)        /*!< Interrupt Mask on line 12 */
#define  EXTI_INTEN_LN13                        ((uint32_t)0x00002000)        /*!< Interrupt Mask on line 13 */
#define  EXTI_INTEN_LN14                        ((uint32_t)0x00004000)        /*!< Interrupt Mask on line 14 */
#define  EXTI_INTEN_LN15                        ((uint32_t)0x00008000)        /*!< Interrupt Mask on line 15 */
#define  EXTI_INTEN_LN16                        ((uint32_t)0x00010000)        /*!< Interrupt Mask on line 16 */
#define  EXTI_INTEN_LN17                        ((uint32_t)0x00020000)        /*!< Interrupt Mask on line 17 */
#define  EXTI_INTEN_LN18                        ((uint32_t)0x00040000)        /*!< Interrupt Mask on line 18 */
#define  EXTI_INTEN_LN19                        ((uint32_t)0x00080000)        /*!< Interrupt Mask on line 19 */

/*******************  Bit definition for EXTI_EVTEN register  *******************/
#define  EXTI_EVTEN_LN0                         ((uint32_t)0x00000001)        /*!< Event Mask on line 0 */
#define  EXTI_EVTEN_LN1                         ((uint32_t)0x00000002)        /*!< Event Mask on line 1 */
#define  EXTI_EVTEN_LN2                         ((uint32_t)0x00000004)        /*!< Event Mask on line 2 */
#define  EXTI_EVTEN_LN3                         ((uint32_t)0x00000008)        /*!< Event Mask on line 3 */
#define  EXTI_EVTEN_LN4                         ((uint32_t)0x00000010)        /*!< Event Mask on line 4 */
#define  EXTI_EVTEN_LN5                         ((uint32_t)0x00000020)        /*!< Event Mask on line 5 */
#define  EXTI_EVTEN_LN6                         ((uint32_t)0x00000040)        /*!< Event Mask on line 6 */
#define  EXTI_EVTEN_LN7                         ((uint32_t)0x00000080)        /*!< Event Mask on line 7 */
#define  EXTI_EVTEN_LN8                         ((uint32_t)0x00000100)        /*!< Event Mask on line 8 */
#define  EXTI_EVTEN_LN9                         ((uint32_t)0x00000200)        /*!< Event Mask on line 9 */
#define  EXTI_EVTEN_LN10                        ((uint32_t)0x00000400)        /*!< Event Mask on line 10 */
#define  EXTI_EVTEN_LN11                        ((uint32_t)0x00000800)        /*!< Event Mask on line 11 */
#define  EXTI_EVTEN_LN12                        ((uint32_t)0x00001000)        /*!< Event Mask on line 12 */
#define  EXTI_EVTEN_LN13                        ((uint32_t)0x00002000)        /*!< Event Mask on line 13 */
#define  EXTI_EVTEN_LN14                        ((uint32_t)0x00004000)        /*!< Event Mask on line 14 */
#define  EXTI_EVTEN_LN15                        ((uint32_t)0x00008000)        /*!< Event Mask on line 15 */
#define  EXTI_EVTEN_LN16                        ((uint32_t)0x00010000)        /*!< Event Mask on line 16 */
#define  EXTI_EVTEN_LN17                        ((uint32_t)0x00020000)        /*!< Event Mask on line 17 */
#define  EXTI_EVTEN_LN18                        ((uint32_t)0x00040000)        /*!< Event Mask on line 18 */
#define  EXTI_EVTEN_LN19                        ((uint32_t)0x00080000)        /*!< Event Mask on line 19 */

/******************  Bit definition for EXTI_RTRSEL register  *******************/
#define  EXTI_RTRSEL_LN0                        ((uint32_t)0x00000001)        /*!< Rising trigger event configuration bit of line 0 */
#define  EXTI_RTRSEL_LN1                        ((uint32_t)0x00000002)        /*!< Rising trigger event configuration bit of line 1 */
#define  EXTI_RTRSEL_LN2                        ((uint32_t)0x00000004)        /*!< Rising trigger event configuration bit of line 2 */
#define  EXTI_RTRSEL_LN3                        ((uint32_t)0x00000008)        /*!< Rising trigger event configuration bit of line 3 */
#define  EXTI_RTRSEL_LN4                        ((uint32_t)0x00000010)        /*!< Rising trigger event configuration bit of line 4 */
#define  EXTI_RTRSEL_LN5                        ((uint32_t)0x00000020)        /*!< Rising trigger event configuration bit of line 5 */
#define  EXTI_RTRSEL_LN6                        ((uint32_t)0x00000040)        /*!< Rising trigger event configuration bit of line 6 */
#define  EXTI_RTRSEL_LN7                        ((uint32_t)0x00000080)        /*!< Rising trigger event configuration bit of line 7 */
#define  EXTI_RTRSEL_LN8                        ((uint32_t)0x00000100)        /*!< Rising trigger event configuration bit of line 8 */
#define  EXTI_RTRSEL_LN9                        ((uint32_t)0x00000200)        /*!< Rising trigger event configuration bit of line 9 */
#define  EXTI_RTRSEL_LN10                       ((uint32_t)0x00000400)        /*!< Rising trigger event configuration bit of line 10 */
#define  EXTI_RTRSEL_LN11                       ((uint32_t)0x00000800)        /*!< Rising trigger event configuration bit of line 11 */
#define  EXTI_RTRSEL_LN12                       ((uint32_t)0x00001000)        /*!< Rising trigger event configuration bit of line 12 */
#define  EXTI_RTRSEL_LN13                       ((uint32_t)0x00002000)        /*!< Rising trigger event configuration bit of line 13 */
#define  EXTI_RTRSEL_LN14                       ((uint32_t)0x00004000)        /*!< Rising trigger event configuration bit of line 14 */
#define  EXTI_RTRSEL_LN15                       ((uint32_t)0x00008000)        /*!< Rising trigger event configuration bit of line 15 */
#define  EXTI_RTRSEL_LN16                       ((uint32_t)0x00010000)        /*!< Rising trigger event configuration bit of line 16 */
#define  EXTI_RTRSEL_LN17                       ((uint32_t)0x00020000)        /*!< Rising trigger event configuration bit of line 17 */
#define  EXTI_RTRSEL_LN18                       ((uint32_t)0x00040000)        /*!< Rising trigger event configuration bit of line 18 */
#define  EXTI_RTRSEL_LN19                       ((uint32_t)0x00080000)        /*!< Rising trigger event configuration bit of line 19 */

/******************  Bit definition for EXTI_FTRSEL register  *******************/
#define  EXTI_FTRSEL_LN0                        ((uint32_t)0x00000001)        /*!< Falling trigger event configuration bit of line 0 */
#define  EXTI_FTRSEL_LN1                        ((uint32_t)0x00000002)        /*!< Falling trigger event configuration bit of line 1 */
#define  EXTI_FTRSEL_LN2                        ((uint32_t)0x00000004)        /*!< Falling trigger event configuration bit of line 2 */
#define  EXTI_FTRSEL_LN3                        ((uint32_t)0x00000008)        /*!< Falling trigger event configuration bit of line 3 */
#define  EXTI_FTRSEL_LN4                        ((uint32_t)0x00000010)        /*!< Falling trigger event configuration bit of line 4 */
#define  EXTI_FTRSEL_LN5                        ((uint32_t)0x00000020)        /*!< Falling trigger event configuration bit of line 5 */
#define  EXTI_FTRSEL_LN6                        ((uint32_t)0x00000040)        /*!< Falling trigger event configuration bit of line 6 */
#define  EXTI_FTRSEL_LN7                        ((uint32_t)0x00000080)        /*!< Falling trigger event configuration bit of line 7 */
#define  EXTI_FTRSEL_LN8                        ((uint32_t)0x00000100)        /*!< Falling trigger event configuration bit of line 8 */
#define  EXTI_FTRSEL_LN9                        ((uint32_t)0x00000200)        /*!< Falling trigger event configuration bit of line 9 */
#define  EXTI_FTRSEL_LN10                       ((uint32_t)0x00000400)        /*!< Falling trigger event configuration bit of line 10 */
#define  EXTI_FTRSEL_LN11                       ((uint32_t)0x00000800)        /*!< Falling trigger event configuration bit of line 11 */
#define  EXTI_FTRSEL_LN12                       ((uint32_t)0x00001000)        /*!< Falling trigger event configuration bit of line 12 */
#define  EXTI_FTRSEL_LN13                       ((uint32_t)0x00002000)        /*!< Falling trigger event configuration bit of line 13 */
#define  EXTI_FTRSEL_LN14                       ((uint32_t)0x00004000)        /*!< Falling trigger event configuration bit of line 14 */
#define  EXTI_FTRSEL_LN15                       ((uint32_t)0x00008000)        /*!< Falling trigger event configuration bit of line 15 */
#define  EXTI_FTRSEL_LN16                       ((uint32_t)0x00010000)        /*!< Falling trigger event configuration bit of line 16 */
#define  EXTI_FTRSEL_LN17                       ((uint32_t)0x00020000)        /*!< Falling trigger event configuration bit of line 17 */
#define  EXTI_FTRSEL_LN18                       ((uint32_t)0x00040000)        /*!< Falling trigger event configuration bit of line 18 */
#define  EXTI_FTRSEL_LN19                       ((uint32_t)0x00080000)        /*!< Falling trigger event configuration bit of line 19 */

/******************  Bit definition for EXTI_SWIE register  ******************/
#define  EXTI_SWIE_LN0                          ((uint32_t)0x00000001)        /*!< Software Interrupt on line 0 */
#define  EXTI_SWIE_LN1                          ((uint32_t)0x00000002)        /*!< Software Interrupt on line 1 */
#define  EXTI_SWIE_LN2                          ((uint32_t)0x00000004)        /*!< Software Interrupt on line 2 */
#define  EXTI_SWIE_LN3                          ((uint32_t)0x00000008)        /*!< Software Interrupt on line 3 */
#define  EXTI_SWIE_LN4                          ((uint32_t)0x00000010)        /*!< Software Interrupt on line 4 */
#define  EXTI_SWIE_LN5                          ((uint32_t)0x00000020)        /*!< Software Interrupt on line 5 */
#define  EXTI_SWIE_LN6                          ((uint32_t)0x00000040)        /*!< Software Interrupt on line 6 */
#define  EXTI_SWIE_LN7                          ((uint32_t)0x00000080)        /*!< Software Interrupt on line 7 */
#define  EXTI_SWIE_LN8                          ((uint32_t)0x00000100)        /*!< Software Interrupt on line 8 */
#define  EXTI_SWIE_LN9                          ((uint32_t)0x00000200)        /*!< Software Interrupt on line 9 */
#define  EXTI_SWIE_LN10                         ((uint32_t)0x00000400)        /*!< Software Interrupt on line 10 */
#define  EXTI_SWIE_LN11                         ((uint32_t)0x00000800)        /*!< Software Interrupt on line 11 */
#define  EXTI_SWIE_LN12                         ((uint32_t)0x00001000)        /*!< Software Interrupt on line 12 */
#define  EXTI_SWIE_LN13                         ((uint32_t)0x00002000)        /*!< Software Interrupt on line 13 */
#define  EXTI_SWIE_LN14                         ((uint32_t)0x00004000)        /*!< Software Interrupt on line 14 */
#define  EXTI_SWIE_LN15                         ((uint32_t)0x00008000)        /*!< Software Interrupt on line 15 */
#define  EXTI_SWIE_LN16                         ((uint32_t)0x00010000)        /*!< Software Interrupt on line 16 */
#define  EXTI_SWIE_LN17                         ((uint32_t)0x00020000)        /*!< Software Interrupt on line 17 */
#define  EXTI_SWIE_LN18                         ((uint32_t)0x00040000)        /*!< Software Interrupt on line 18 */
#define  EXTI_SWIE_LN19                         ((uint32_t)0x00080000)        /*!< Software Interrupt on line 19 */

/*******************  Bit definition for EXTI_PND register  ********************/
#define  EXTI_PND_LN0                           ((uint32_t)0x00000001)        /*!< Pending bit for line 0 */
#define  EXTI_PND_LN1                           ((uint32_t)0x00000002)        /*!< Pending bit for line 1 */
#define  EXTI_PND_LN2                           ((uint32_t)0x00000004)        /*!< Pending bit for line 2 */
#define  EXTI_PND_LN3                           ((uint32_t)0x00000008)        /*!< Pending bit for line 3 */
#define  EXTI_PND_LN4                           ((uint32_t)0x00000010)        /*!< Pending bit for line 4 */
#define  EXTI_PND_LN5                           ((uint32_t)0x00000020)        /*!< Pending bit for line 5 */
#define  EXTI_PND_LN6                           ((uint32_t)0x00000040)        /*!< Pending bit for line 6 */
#define  EXTI_PND_LN7                           ((uint32_t)0x00000080)        /*!< Pending bit for line 7 */
#define  EXTI_PND_LN8                           ((uint32_t)0x00000100)        /*!< Pending bit for line 8 */
#define  EXTI_PND_LN9                           ((uint32_t)0x00000200)        /*!< Pending bit for line 9 */
#define  EXTI_PND_LN10                          ((uint32_t)0x00000400)        /*!< Pending bit for line 10 */
#define  EXTI_PND_LN11                          ((uint32_t)0x00000800)        /*!< Pending bit for line 11 */
#define  EXTI_PND_LN12                          ((uint32_t)0x00001000)        /*!< Pending bit for line 12 */
#define  EXTI_PND_LN13                          ((uint32_t)0x00002000)        /*!< Pending bit for line 13 */
#define  EXTI_PND_LN14                          ((uint32_t)0x00004000)        /*!< Pending bit for line 14 */
#define  EXTI_PND_LN15                          ((uint32_t)0x00008000)        /*!< Pending bit for line 15 */
#define  EXTI_PND_LN16                          ((uint32_t)0x00010000)        /*!< Pending bit for line 16 */
#define  EXTI_PND_LN17                          ((uint32_t)0x00020000)        /*!< Pending bit for line 17 */
#define  EXTI_PND_LN18                          ((uint32_t)0x00040000)        /*!< Pending bit for line 18 */
#define  EXTI_PND_LN19                          ((uint32_t)0x00080000)        /*!< Pending bit for line 19 */

/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for DMA_ISTS register  ********************/
#define  DMA_ISTS_GIF1                          ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt flag */
#define  DMA_ISTS_TCIF1                         ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete flag */
#define  DMA_ISTS_HTIF1                         ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer flag */
#define  DMA_ISTS_ERRIF1                        ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error flag */
#define  DMA_ISTS_GIF2                          ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt flag */
#define  DMA_ISTS_TCIF2                         ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete flag */
#define  DMA_ISTS_HTIF2                         ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer flag */
#define  DMA_ISTS_ERRIF2                        ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error flag */
#define  DMA_ISTS_GIF3                          ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt flag */
#define  DMA_ISTS_TCIF3                         ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete flag */
#define  DMA_ISTS_HTIF3                         ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer flag */
#define  DMA_ISTS_ERRIF3                        ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error flag */
#define  DMA_ISTS_GIF4                          ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt flag */
#define  DMA_ISTS_TCIF4                         ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete flag */
#define  DMA_ISTS_HTIF4                         ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer flag */
#define  DMA_ISTS_ERRIF4                        ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error flag */
#define  DMA_ISTS_GIF5                          ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt flag */
#define  DMA_ISTS_TCIF5                         ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete flag */
#define  DMA_ISTS_HTIF5                         ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer flag */
#define  DMA_ISTS_ERRIF5                        ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error flag */
#define  DMA_ISTS_GIF6                          ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt flag */
#define  DMA_ISTS_TCIF6                         ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete flag */
#define  DMA_ISTS_HTIF6                         ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer flag */
#define  DMA_ISTS_ERRIF6                        ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error flag */
#define  DMA_ISTS_GIF7                          ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt flag */
#define  DMA_ISTS_TCIF7                         ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete flag */
#define  DMA_ISTS_HTIF7                         ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer flag */
#define  DMA_ISTS_ERRIF7                        ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_ICLR register  *******************/
#define  DMA_ICLR_CGIF1                          ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt clear */
#define  DMA_ICLR_CTCIF1                         ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete clear */
#define  DMA_ICLR_CHTIF1                         ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer clear */
#define  DMA_ICLR_CERRIF1                        ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error clear */
#define  DMA_ICLR_CGIF2                          ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt clear */
#define  DMA_ICLR_CTCIF2                         ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete clear */
#define  DMA_ICLR_CHTIF2                         ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer clear */
#define  DMA_ICLR_CERRIF2                        ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error clear */
#define  DMA_ICLR_CGIF3                          ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt clear */
#define  DMA_ICLR_CTCIF3                         ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete clear */
#define  DMA_ICLR_CHTIF3                         ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer clear */
#define  DMA_ICLR_CERRIF3                        ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error clear */
#define  DMA_ICLR_CGIF4                          ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt clear */
#define  DMA_ICLR_CTCIF4                         ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete clear */
#define  DMA_ICLR_CHTIF4                         ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer clear */
#define  DMA_ICLR_CERRIF4                        ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error clear */
#define  DMA_ICLR_CGIF5                          ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt clear */
#define  DMA_ICLR_CTCIF5                         ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete clear */
#define  DMA_ICLR_CHTIF5                         ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer clear */
#define  DMA_ICLR_CERRIF5                        ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error clear */
#define  DMA_ICLR_CGIF6                          ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt clear */
#define  DMA_ICLR_CTCIF6                         ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete clear */
#define  DMA_ICLR_CHTIF6                         ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer clear */
#define  DMA_ICLR_CERRIF6                        ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error clear */
#define  DMA_ICLR_CGIF7                          ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt clear */
#define  DMA_ICLR_CTCIF7                         ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete clear */
#define  DMA_ICLR_CHTIF7                         ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer clear */
#define  DMA_ICLR_CERRIF7                        ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error clear */

/*******************  Bit definition for DMA_CHCTRL1 register  *******************/
#define  DMA_CHCTRL1_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable*/
#define  DMA_CHCTRL1_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL1_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL1_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL1_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL1_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL1_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL1_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL1_PWIDTH                     ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL1_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL1_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL1_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL1_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL1_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL1_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits(Channel Priority level) */
#define  DMA_CHCTRL1_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL1_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL1_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode */

/*******************  Bit definition for DMA_CHCTRL2 register  *******************/
#define  DMA_CHCTRL2_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable */
#define  DMA_CHCTRL2_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL2_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL2_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL2_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL2_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL2_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL2_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL2_PWIDTH                     ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL2_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL2_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL2_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL2_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL2_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL2_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits (Channel Priority level) */
#define  DMA_CHCTRL2_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL2_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL2_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode */

/*******************  Bit definition for DMA_CHCTRL3 register  *******************/
#define  DMA_CHCTRL3_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable */
#define  DMA_CHCTRL3_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL3_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL3_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL3_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL3_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL3_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL3_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL3_PWIDTH                     ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL3_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL3_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL3_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL3_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL3_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL3_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits (Channel Priority level) */
#define  DMA_CHCTRL3_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL3_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL3_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode */

/********************  Bit definition for DMA_CHCTRL4 register  *******************/
#define  DMA_CHCTRL4_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable */
#define  DMA_CHCTRL4_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL4_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL4_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL4_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL4_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL4_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL4_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL4_PWIDTH                     ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL4_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL4_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL4_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL4_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL4_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL4_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits (Channel Priority level) */
#define  DMA_CHCTRL4_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL4_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL4_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCTRL5 register  *******************/
#define  DMA_CHCTRL5_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable */
#define  DMA_CHCTRL5_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL5_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL5_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL5_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL5_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL5_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL5_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL5_PWIDTH                     ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL5_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL5_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL5_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL5_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL5_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL5_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits (Channel Priority level) */
#define  DMA_CHCTRL5_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL5_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL5_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode enable */

/*******************  Bit definition for DMA_CHCTRL6 register  *******************/
#define  DMA_CHCTRL6_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable */
#define  DMA_CHCTRL6_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL6_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL6_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL6_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL6_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL6_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL6_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL6_PWIDTH                     ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL6_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL6_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL6_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL6_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL6_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL6_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits (Channel Priority level) */
#define  DMA_CHCTRL6_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL6_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL6_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode */

/*******************  Bit definition for DMA_CHCTRL7 register  *******************/
#define  DMA_CHCTRL7_CHEN                       ((uint16_t)0x0001)            /*!< Channel enable */
#define  DMA_CHCTRL7_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CHCTRL7_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CHCTRL7_ERRIE                      ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CHCTRL7_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CHCTRL7_CIRM                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CHCTRL7_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CHCTRL7_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

#define  DMA_CHCTRL7_PWIDTH                ,    ((uint16_t)0x0300)            /*!< PSIZE[1:0] bits (Peripheral size) */
#define  DMA_CHCTRL7_PWIDTH_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  DMA_CHCTRL7_PWIDTH_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  DMA_CHCTRL7_MWIDTH                     ((uint16_t)0x0C00)            /*!< MSIZE[1:0] bits (Memory size) */
#define  DMA_CHCTRL7_MWIDTH_0                   ((uint16_t)0x0400)            /*!< Bit 0 */
#define  DMA_CHCTRL7_MWIDTH_1                   ((uint16_t)0x0800)            /*!< Bit 1 */

#define  DMA_CHCTRL7_CHPL                       ((uint16_t)0x3000)            /*!< PL[1:0] bits (Channel Priority level) */
#define  DMA_CHCTRL7_CHPL_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  DMA_CHCTRL7_CHPL_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  DMA_CHCTRL7_MEMTOMEM                   ((uint16_t)0x4000)            /*!< Memory to memory mode enable */

/******************  Bit definition for DMA_TCNT1 register  ******************/
#define  DMA_TCNT1_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TCNT2 register  ******************/
#define  DMA_TCNT2_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TCNT3 register  ******************/
#define  DMA_TCNT3_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TCNT4 register  ******************/
#define  DMA_TCNT4_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TCNT5 register  ******************/
#define  DMA_TCNT5_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TCNT6 register  ******************/
#define  DMA_TCNT6_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TCNT7 register  ******************/
#define  DMA_TCNT7_CNT                          ((uint16_t)0xFFFF)            /*!< Number of data to Transfer */

/******************  Bit definition for DMA_CPBA1 register  *******************/
#define  DMA_CPBA1_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */

/******************  Bit definition for DMA_CPBA2 register  *******************/
#define  DMA_CPBA2_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */

/******************  Bit definition for DMA_CPBA3 register  *******************/
#define  DMA_CPBA3_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */


/******************  Bit definition for DMA_CPBA4 register  *******************/
#define  DMA_CPBA4_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */

/******************  Bit definition for DMA_CPBA5 register  *******************/
#define  DMA_CPBA5_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */

/******************  Bit definition for DMA_CPBA6 register  *******************/
#define  DMA_CPBA6_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */


/******************  Bit definition for DMA_CPBA7 register  *******************/
#define  DMA_CPBA7_PA                           ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address */

/******************  Bit definition for DMA_CMBA1 register  *******************/
#define  DMA_CMBA1_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */

/******************  Bit definition for DMA_CMBA2 register  *******************/
#define  DMA_CMBA2_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */

/******************  Bit definition for DMA_CMBA3 register  *******************/
#define  DMA_CMBA3_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */


/******************  Bit definition for DMA_CMBA4 register  *******************/
#define  DMA_CMBA4_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */

/******************  Bit definition for DMA_CMBA5 register  *******************/
#define  DMA_CMBA5_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */

/******************  Bit definition for DMA_CMBA6 register  *******************/
#define  DMA_CMBA6_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */

/******************  Bit definition for DMA_CMBA7 register  *******************/
#define  DMA_CMBA7_MA                           ((uint32_t)0xFFFFFFFF)        /*!< Memory Address */

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for ADC_STS register  ********************/
#define  ADC_STS_AWD                            ((uint8_t)0x01)               /*!< Analog watchdog flag */
#define  ADC_STS_EC                             ((uint8_t)0x02)               /*!< End of conversion */
#define  ADC_STS_JEC                            ((uint8_t)0x04)               /*!< Injected channel end of conversion */
#define  ADC_STS_JSTR                           ((uint8_t)0x08)               /*!< Injected channel Start flag */
#define  ADC_STS_RSTR                           ((uint8_t)0x10)               /*!< Regular channel Start flag */

/*******************  Bit definition for ADC_CTRL1 register  ********************/
#define  ADC_CTRL1_AWDCS                        ((uint32_t)0x0000001F)        /*!< AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define  ADC_CTRL1_AWDCS_0                      ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_CTRL1_AWDCS_1                      ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_CTRL1_AWDCS_2                      ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  ADC_CTRL1_AWDCS_3                      ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  ADC_CTRL1_AWDCS_4                      ((uint32_t)0x00000010)        /*!< Bit 4 */

#define  ADC_CTRL1_ECIEN                        ((uint32_t)0x00000020)        /*!< Interrupt enable for EOC */
#define  ADC_CTRL1_AWDIEN                       ((uint32_t)0x00000040)        /*!< Analog Watchdog interrupt enable */
#define  ADC_CTRL1_JECIEN                       ((uint32_t)0x00000080)        /*!< Interrupt enable for injected channels */
#define  ADC_CTRL1_SCN                          ((uint32_t)0x00000100)        /*!< Scan mode */
#define  ADC_CTRL1_AWDSGE                       ((uint32_t)0x00000200)        /*!< Enable the watchdog on a single channel in scan mode */
#define  ADC_CTRL1_JAUT                         ((uint32_t)0x00000400)        /*!< Automatic injected group conversion */
#define  ADC_CTRL1_RDISEN                       ((uint32_t)0x00000800)        /*!< Discontinuous mode on regular channels */
#define  ADC_CTRL1_JDISEN                       ((uint32_t)0x00001000)        /*!< Discontinuous mode on injected channels */

#define  ADC_CTRL1_DISN                         ((uint32_t)0x0000E000)        /*!< DISCNUM[2:0] bits (Discontinuous mode channel count) */
#define  ADC_CTRL1_DISN_0                       ((uint32_t)0x00002000)        /*!< Bit 0 */
#define  ADC_CTRL1_DISN_1                       ((uint32_t)0x00004000)        /*!< Bit 1 */
#define  ADC_CTRL1_DISN_2                       ((uint32_t)0x00008000)        /*!< Bit 2 */

#define  ADC_CTRL1_DUALM                        ((uint32_t)0x000F0000)        /*!< DUALMOD[3:0] bits (Dual mode selection) */
#define  ADC_CTRL1_DUALM_0                      ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  ADC_CTRL1_DUALM_1                      ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  ADC_CTRL1_DUALM_2                      ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  ADC_CTRL1_DUALM_3                      ((uint32_t)0x00080000)        /*!< Bit 3 */

#define  ADC_CTRL1_JAWDEN                       ((uint32_t)0x00400000)        /*!< Analog watchdog enable on injected channels */
#define  ADC_CTRL1_AWDEN                        ((uint32_t)0x00800000)        /*!< Analog watchdog enable on regular channels */


/*******************  Bit definition for ADC_CTRL2 register  ********************/
#define  ADC_CTRL2_ADON                         ((uint32_t)0x00000001)        /*!< A/D Converter ON / OFF */
#define  ADC_CTRL2_CON                          ((uint32_t)0x00000002)        /*!< Continuous Conversion */
#define  ADC_CTRL2_CAL                          ((uint32_t)0x00000004)        /*!< A/D Calibration */
#define  ADC_CTRL2_RSTCAL                       ((uint32_t)0x00000008)        /*!< Reset Calibration */
#define  ADC_CTRL2_DMAEN                        ((uint32_t)0x00000100)        /*!< Direct Memory access mode */
#define  ADC_CTRL2_DALIGN                       ((uint32_t)0x00000800)        /*!< Data Alignment */

#define  ADC_CTRL2_JEXSEL                       ((uint32_t)0x01007000)        /*!< JEXTSEL[3:0] bits (External event select for injected group) */
#define  ADC_CTRL2_JEXSEL_0                     ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  ADC_CTRL2_JEXSEL_1                     ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  ADC_CTRL2_JEXSEL_2                     ((uint32_t)0x00004000)        /*!< Bit 2 */
#define  ADC_CTRL2_JEXSEL_3                     ((uint32_t)0x01000000)        /*!< Bit 3 */

#define  ADC_CTRL2_JEXTREN                      ((uint32_t)0x00008000)        /*!< External Trigger Conversion mode for injected channels */

#define  ADC_CTRL2_EXSEL                        ((uint32_t)0x020E0000)        /*!< EXTSEL[3:0] bits (External Event Select for regular group) */
#define  ADC_CTRL2_EXSEL_0                      ((uint32_t)0x00020000)        /*!< Bit 0 */
#define  ADC_CTRL2_EXSEL_1                      ((uint32_t)0x00040000)        /*!< Bit 1 */
#define  ADC_CTRL2_EXSEL_2                      ((uint32_t)0x00080000)        /*!< Bit 2 */
#define  ADC_CTRL2_EXSEL_3                      ((uint32_t)0x02000000)        /*!< Bit 3 */

#define  ADC_CTRL2_EXTREN                       ((uint32_t)0x00100000)        /*!< External Trigger Conversion mode for regular channels */
#define  ADC_CTRL2_JSWSTR                       ((uint32_t)0x00200000)        /*!< Start Conversion of injected channels */
#define  ADC_CTRL2_SWSTR                        ((uint32_t)0x00400000)        /*!< Start Conversion of regular channels */
#define  ADC_CTRL2_TSREF                        ((uint32_t)0x00800000)        /*!< Temperature Sensor and VREFINT Enable */

/******************  Bit definition for ADC_SMPT1 register  *******************/
#define  ADC_SMPT1_SMP10                        ((uint32_t)0x00000007)        /*!< SMP10[2:0] bits (Channel 10 Sample time selection) */
#define  ADC_SMPT1_SMP10_0                      ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP10_1                      ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP10_2                      ((uint32_t)0x00000004)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP11                        ((uint32_t)0x00000038)        /*!< SMP11[2:0] bits (Channel 11 Sample time selection) */
#define  ADC_SMPT1_SMP11_0                      ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP11_1                      ((uint32_t)0x00000010)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP11_2                      ((uint32_t)0x00000020)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP12                        ((uint32_t)0x000001C0)        /*!< SMP12[2:0] bits (Channel 12 Sample time selection) */
#define  ADC_SMPT1_SMP12_0                      ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP12_1                      ((uint32_t)0x00000080)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP12_2                      ((uint32_t)0x00000100)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP13                        ((uint32_t)0x00000E00)        /*!< SMP13[2:0] bits (Channel 13 Sample time selection) */
#define  ADC_SMPT1_SMP13_0                      ((uint32_t)0x00000200)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP13_1                      ((uint32_t)0x00000400)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP13_2                      ((uint32_t)0x00000800)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP14                        ((uint32_t)0x00007000)        /*!< SMP14[2:0] bits (Channel 14 Sample time selection) */
#define  ADC_SMPT1_SMP14_0                      ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP14_1                      ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP14_2                      ((uint32_t)0x00004000)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP15                        ((uint32_t)0x00038000)        /*!< SMP15[2:0] bits (Channel 15 Sample time selection) */
#define  ADC_SMPT1_SMP15_0                      ((uint32_t)0x00008000)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP15_1                      ((uint32_t)0x00010000)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP15_2                      ((uint32_t)0x00020000)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP16                        ((uint32_t)0x001C0000)        /*!< SMP16[2:0] bits (Channel 16 Sample time selection) */
#define  ADC_SMPT1_SMP16_0                      ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP16_1                      ((uint32_t)0x00080000)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP16_2                      ((uint32_t)0x00100000)        /*!< Bit 2 */

#define  ADC_SMPT1_SMP17                        ((uint32_t)0x00E00000)        /*!< SMP17[2:0] bits (Channel 17 Sample time selection) */
#define  ADC_SMPT1_SMP17_0                      ((uint32_t)0x00200000)        /*!< Bit 0 */
#define  ADC_SMPT1_SMP17_1                      ((uint32_t)0x00400000)        /*!< Bit 1 */
#define  ADC_SMPT1_SMP17_2                      ((uint32_t)0x00800000)        /*!< Bit 2 */

/******************  Bit definition for ADC_SMPT2 register  *******************/
#define  ADC_SMPT2_SMP0                         ((uint32_t)0x00000007)        /*!< SMP0[2:0] bits (Channel 0 Sample time selection) */
#define  ADC_SMPT2_SMP0_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP0_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP0_2                       ((uint32_t)0x00000004)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP1                         ((uint32_t)0x00000038)        /*!< SMP1[2:0] bits (Channel 1 Sample time selection) */
#define  ADC_SMPT2_SMP1_0                       ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP1_1                       ((uint32_t)0x00000010)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP1_2                       ((uint32_t)0x00000020)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP2                         ((uint32_t)0x000001C0)        /*!< SMP2[2:0] bits (Channel 2 Sample time selection) */
#define  ADC_SMPT2_SMP2_0                       ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP2_1                       ((uint32_t)0x00000080)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP2_2                       ((uint32_t)0x00000100)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP3                         ((uint32_t)0x00000E00)        /*!< SMP3[2:0] bits (Channel 3 Sample time selection) */
#define  ADC_SMPT2_SMP3_0                       ((uint32_t)0x00000200)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP3_1                       ((uint32_t)0x00000400)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP3_2                       ((uint32_t)0x00000800)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP4                         ((uint32_t)0x00007000)        /*!< SMP4[2:0] bits (Channel 4 Sample time selection) */
#define  ADC_SMPT2_SMP4_0                       ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP4_1                       ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP4_2                       ((uint32_t)0x00004000)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP5                         ((uint32_t)0x00038000)        /*!< SMP5[2:0] bits (Channel 5 Sample time selection) */
#define  ADC_SMPT2_SMP5_0                       ((uint32_t)0x00008000)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP5_1                       ((uint32_t)0x00010000)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP5_2                       ((uint32_t)0x00020000)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP6                         ((uint32_t)0x001C0000)        /*!< SMP6[2:0] bits (Channel 6 Sample time selection) */
#define  ADC_SMPT2_SMP6_0                       ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP6_1                       ((uint32_t)0x00080000)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP6_2                       ((uint32_t)0x00100000)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP7                         ((uint32_t)0x00E00000)        /*!< SMP7[2:0] bits (Channel 7 Sample time selection) */
#define  ADC_SMPT2_SMP7_0                       ((uint32_t)0x00200000)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP7_1                       ((uint32_t)0x00400000)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP7_2                       ((uint32_t)0x00800000)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP8                         ((uint32_t)0x07000000)        /*!< SMP8[2:0] bits (Channel 8 Sample time selection) */
#define  ADC_SMPT2_SMP8_0                       ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP8_1                       ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP8_2                       ((uint32_t)0x04000000)        /*!< Bit 2 */

#define  ADC_SMPT2_SMP9                         ((uint32_t)0x38000000)        /*!< SMP9[2:0] bits (Channel 9 Sample time selection) */
#define  ADC_SMPT2_SMP9_0                       ((uint32_t)0x08000000)        /*!< Bit 0 */
#define  ADC_SMPT2_SMP9_1                       ((uint32_t)0x10000000)        /*!< Bit 1 */
#define  ADC_SMPT2_SMP9_2                       ((uint32_t)0x20000000)        /*!< Bit 2 */

/******************  Bit definition for ADC_JOFS1 register  *******************/
#define  ADC_JOFS1_JOFST1                       ((uint16_t)0x0FFF)            /*!< Data offset for injected channel 1 */

/******************  Bit definition for ADC_JOFS2 register  *******************/
#define  ADC_JOFS2_JOFST2                       ((uint16_t)0x0FFF)            /*!< Data offset for injected channel 2 */

/******************  Bit definition for ADC_JOFS3 register  *******************/
#define  ADC_JOFS3_JOFST3                       ((uint16_t)0x0FFF)            /*!< Data offset for injected channel 3 */

/******************  Bit definition for ADC_JOFS4 register  *******************/
#define  ADC_JOFS4_JOFST4                       ((uint16_t)0x0FFF)            /*!< Data offset for injected channel 4 */

/*******************  Bit definition for ADC_WHTR register  ********************/
#define  ADC_WHTR_AWHT                          ((uint16_t)0x0FFF)            /*!< Analog watchdog high threshold */

/*******************  Bit definition for ADC_WLTR register  ********************/
#define  ADC_WLTR_AWLT                          ((uint16_t)0x0FFF)            /*!< Analog watchdog low threshold */

/*******************  Bit definition for ADC_RSQ1 register  *******************/
#define  ADC_RSQ1_SQ13                          ((uint32_t)0x0000001F)        /*!< SQ13[4:0] bits (13th conversion in regular sequence) */
#define  ADC_RSQ1_SQ13_0                        ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_RSQ1_SQ13_1                        ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_RSQ1_SQ13_2                        ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  ADC_RSQ1_SQ13_3                        ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  ADC_RSQ1_SQ13_4                        ((uint32_t)0x00000010)        /*!< Bit 4 */

#define  ADC_RSQ1_SQ14                          ((uint32_t)0x000003E0)        /*!< SQ14[4:0] bits (14th conversion in regular sequence) */
#define  ADC_RSQ1_SQ14_0                        ((uint32_t)0x00000020)        /*!< Bit 0 */
#define  ADC_RSQ1_SQ14_1                        ((uint32_t)0x00000040)        /*!< Bit 1 */
#define  ADC_RSQ1_SQ14_2                        ((uint32_t)0x00000080)        /*!< Bit 2 */
#define  ADC_RSQ1_SQ14_3                        ((uint32_t)0x00000100)        /*!< Bit 3 */
#define  ADC_RSQ1_SQ14_4                        ((uint32_t)0x00000200)        /*!< Bit 4 */

#define  ADC_RSQ1_SQ15                          ((uint32_t)0x00007C00)        /*!< SQ15[4:0] bits (15th conversion in regular sequence) */
#define  ADC_RSQ1_SQ15_0                        ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  ADC_RSQ1_SQ15_1                        ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  ADC_RSQ1_SQ15_2                        ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  ADC_RSQ1_SQ15_3                        ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  ADC_RSQ1_SQ15_4                        ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  ADC_RSQ1_SQ16                          ((uint32_t)0x000F8000)        /*!< SQ16[4:0] bits (16th conversion in regular sequence) */
#define  ADC_RSQ1_SQ16_0                        ((uint32_t)0x00008000)        /*!< Bit 0 */
#define  ADC_RSQ1_SQ16_1                        ((uint32_t)0x00010000)        /*!< Bit 1 */
#define  ADC_RSQ1_SQ16_2                        ((uint32_t)0x00020000)        /*!< Bit 2 */
#define  ADC_RSQ1_SQ16_3                        ((uint32_t)0x00040000)        /*!< Bit 3 */
#define  ADC_RSQ1_SQ16_4                        ((uint32_t)0x00080000)        /*!< Bit 4 */

#define  ADC_RSQ1_LEN                           ((uint32_t)0x00F00000)        /*!< L[3:0] bits (Regular channel sequence length) */
#define  ADC_RSQ1_LEN_0                         ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  ADC_RSQ1_LEN_1                         ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  ADC_RSQ1_LEN_2                         ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  ADC_RSQ1_LEN_3                         ((uint32_t)0x00800000)        /*!< Bit 3 */

/*******************  Bit definition for ADC_RSQ2 register  *******************/
#define  ADC_RSQ2_SQ7                           ((uint32_t)0x0000001F)        /*!< SQ7[4:0] bits (7th conversion in regular sequence) */
#define  ADC_RSQ2_SQ7_0                         ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_RSQ2_SQ7_1                         ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_RSQ2_SQ7_2                         ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  ADC_RSQ2_SQ7_3                         ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  ADC_RSQ2_SQ7_4                         ((uint32_t)0x00000010)        /*!< Bit 4 */

#define  ADC_RSQ2_SQ8                           ((uint32_t)0x000003E0)        /*!< SQ8[4:0] bits (8th conversion in regular sequence) */
#define  ADC_RSQ2_SQ8_0                         ((uint32_t)0x00000020)        /*!< Bit 0 */
#define  ADC_RSQ2_SQ8_1                         ((uint32_t)0x00000040)        /*!< Bit 1 */
#define  ADC_RSQ2_SQ8_2                         ((uint32_t)0x00000080)        /*!< Bit 2 */
#define  ADC_RSQ2_SQ8_3                         ((uint32_t)0x00000100)        /*!< Bit 3 */
#define  ADC_RSQ2_SQ8_4                         ((uint32_t)0x00000200)        /*!< Bit 4 */

#define  ADC_RSQ2_SQ9                           ((uint32_t)0x00007C00)        /*!< SQ9[4:0] bits (9th conversion in regular sequence) */
#define  ADC_RSQ2_SQ9_0                         ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  ADC_RSQ2_SQ9_1                         ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  ADC_RSQ2_SQ9_2                         ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  ADC_RSQ2_SQ9_3                         ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  ADC_RSQ2_SQ9_4                         ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  ADC_RSQ2_SQ10                          ((uint32_t)0x000F8000)        /*!< SQ10[4:0] bits (10th conversion in regular sequence) */
#define  ADC_RSQ2_SQ10_0                        ((uint32_t)0x00008000)        /*!< Bit 0 */
#define  ADC_RSQ2_SQ10_1                        ((uint32_t)0x00010000)        /*!< Bit 1 */
#define  ADC_RSQ2_SQ10_2                        ((uint32_t)0x00020000)        /*!< Bit 2 */
#define  ADC_RSQ2_SQ10_3                        ((uint32_t)0x00040000)        /*!< Bit 3 */
#define  ADC_RSQ2_SQ10_4                        ((uint32_t)0x00080000)        /*!< Bit 4 */

#define  ADC_RSQ2_SQ11                          ((uint32_t)0x01F00000)        /*!< SQ11[4:0] bits (11th conversion in regular sequence) */
#define  ADC_RSQ2_SQ11_0                        ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  ADC_RSQ2_SQ11_1                        ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  ADC_RSQ2_SQ11_2                        ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  ADC_RSQ2_SQ11_3                        ((uint32_t)0x00800000)        /*!< Bit 3 */
#define  ADC_RSQ2_SQ11_4                        ((uint32_t)0x01000000)        /*!< Bit 4 */

#define  ADC_RSQ2_SQ12                          ((uint32_t)0x3E000000)        /*!< SQ12[4:0] bits (12th conversion in regular sequence) */
#define  ADC_RSQ2_SQ12_0                        ((uint32_t)0x02000000)        /*!< Bit 0 */
#define  ADC_RSQ2_SQ12_1                        ((uint32_t)0x04000000)        /*!< Bit 1 */
#define  ADC_RSQ2_SQ12_2                        ((uint32_t)0x08000000)        /*!< Bit 2 */
#define  ADC_RSQ2_SQ12_3                        ((uint32_t)0x10000000)        /*!< Bit 3 */
#define  ADC_RSQ2_SQ12_4                        ((uint32_t)0x20000000)        /*!< Bit 4 */

/*******************  Bit definition for ADC_RSQ3 register  *******************/
#define  ADC_RSQ3_SQ1                           ((uint32_t)0x0000001F)        /*!< SQ1[4:0] bits (1st conversion in regular sequence) */
#define  ADC_RSQ3_SQ1_0                         ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_RSQ3_SQ1_1                         ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_RSQ3_SQ1_2                         ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  ADC_RSQ3_SQ1_3                         ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  ADC_RSQ3_SQ1_4                         ((uint32_t)0x00000010)        /*!< Bit 4 */

#define  ADC_RSQ3_SQ2                           ((uint32_t)0x000003E0)        /*!< SQ2[4:0] bits (2nd conversion in regular sequence) */
#define  ADC_RSQ3_SQ2_0                         ((uint32_t)0x00000020)        /*!< Bit 0 */
#define  ADC_RSQ3_SQ2_1                         ((uint32_t)0x00000040)        /*!< Bit 1 */
#define  ADC_RSQ3_SQ2_2                         ((uint32_t)0x00000080)        /*!< Bit 2 */
#define  ADC_RSQ3_SQ2_3                         ((uint32_t)0x00000100)        /*!< Bit 3 */
#define  ADC_RSQ3_SQ2_4                         ((uint32_t)0x00000200)        /*!< Bit 4 */

#define  ADC_RSQ3_SQ3                           ((uint32_t)0x00007C00)        /*!< SQ3[4:0] bits (3rd conversion in regular sequence) */
#define  ADC_RSQ3_SQ3_0                         ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  ADC_RSQ3_SQ3_1                         ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  ADC_RSQ3_SQ3_2                         ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  ADC_RSQ3_SQ3_3                         ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  ADC_RSQ3_SQ3_4                         ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  ADC_RSQ3_SQ4                           ((uint32_t)0x000F8000)        /*!< SQ4[4:0] bits (4th conversion in regular sequence) */
#define  ADC_RSQ3_SQ4_0                         ((uint32_t)0x00008000)        /*!< Bit 0 */
#define  ADC_RSQ3_SQ4_1                         ((uint32_t)0x00010000)        /*!< Bit 1 */
#define  ADC_RSQ3_SQ4_2                         ((uint32_t)0x00020000)        /*!< Bit 2 */
#define  ADC_RSQ3_SQ4_3                         ((uint32_t)0x00040000)        /*!< Bit 3 */
#define  ADC_RSQ3_SQ4_4                         ((uint32_t)0x00080000)        /*!< Bit 4 */

#define  ADC_RSQ3_SQ5                           ((uint32_t)0x01F00000)        /*!< SQ5[4:0] bits (5th conversion in regular sequence) */
#define  ADC_RSQ3_SQ5_0                         ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  ADC_RSQ3_SQ5_1                         ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  ADC_RSQ3_SQ5_2                         ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  ADC_RSQ3_SQ5_3                         ((uint32_t)0x00800000)        /*!< Bit 3 */
#define  ADC_RSQ3_SQ5_4                         ((uint32_t)0x01000000)        /*!< Bit 4 */

#define  ADC_RSQ3_SQ6                           ((uint32_t)0x3E000000)        /*!< SQ6[4:0] bits (6th conversion in regular sequence) */
#define  ADC_RSQ3_SQ6_0                         ((uint32_t)0x02000000)        /*!< Bit 0 */
#define  ADC_RSQ3_SQ6_1                         ((uint32_t)0x04000000)        /*!< Bit 1 */
#define  ADC_RSQ3_SQ6_2                         ((uint32_t)0x08000000)        /*!< Bit 2 */
#define  ADC_RSQ3_SQ6_3                         ((uint32_t)0x10000000)        /*!< Bit 3 */
#define  ADC_RSQ3_SQ6_4                         ((uint32_t)0x20000000)        /*!< Bit 4 */

/*******************  Bit definition for ADC_JSQ register  *******************/
#define  ADC_JSQ_JSQ1                           ((uint32_t)0x0000001F)        /*!< JSQ1[4:0] bits (1st conversion in injected sequence) */
#define  ADC_JSQ_JSQ1_0                         ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_JSQ_JSQ1_1                         ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_JSQ_JSQ1_2                         ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  ADC_JSQ_JSQ1_3                         ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  ADC_JSQ_JSQ1_4                         ((uint32_t)0x00000010)        /*!< Bit 4 */

#define  ADC_JSQ_JSQ2                           ((uint32_t)0x000003E0)        /*!< JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define  ADC_JSQ_JSQ2_0                         ((uint32_t)0x00000020)        /*!< Bit 0 */
#define  ADC_JSQ_JSQ2_1                         ((uint32_t)0x00000040)        /*!< Bit 1 */
#define  ADC_JSQ_JSQ2_2                         ((uint32_t)0x00000080)        /*!< Bit 2 */
#define  ADC_JSQ_JSQ2_3                         ((uint32_t)0x00000100)        /*!< Bit 3 */
#define  ADC_JSQ_JSQ2_4                         ((uint32_t)0x00000200)        /*!< Bit 4 */

#define  ADC_JSQ_JSQ3                           ((uint32_t)0x00007C00)        /*!< JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define  ADC_JSQ_JSQ3_0                         ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  ADC_JSQ_JSQ3_1                         ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  ADC_JSQ_JSQ3_2                         ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  ADC_JSQ_JSQ3_3                         ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  ADC_JSQ_JSQ3_4                         ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  ADC_JSQ_JSQ4                           ((uint32_t)0x000F8000)        /*!< JSQ4[4:0] bits (4th conversion in injected sequence) */
#define  ADC_JSQ_JSQ4_0                         ((uint32_t)0x00008000)        /*!< Bit 0 */
#define  ADC_JSQ_JSQ4_1                         ((uint32_t)0x00010000)        /*!< Bit 1 */
#define  ADC_JSQ_JSQ4_2                         ((uint32_t)0x00020000)        /*!< Bit 2 */
#define  ADC_JSQ_JSQ4_3                         ((uint32_t)0x00040000)        /*!< Bit 3 */
#define  ADC_JSQ_JSQ4_4                         ((uint32_t)0x00080000)        /*!< Bit 4 */

#define  ADC_JSQ_JLEN                           ((uint32_t)0x00300000)        /*!< JL[1:0] bits (Injected Sequence length) */
#define  ADC_JSQ_JLEN_0                         ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  ADC_JSQ_JLEN_1                         ((uint32_t)0x00200000)        /*!< Bit 1 */

/*******************  Bit definition for ADC_JDOR1 register  *******************/
#define  ADC_JDOR1_JD                           ((uint16_t)0xFFFF)            /*!< Injected data */

/*******************  Bit definition for ADC_JDOR2 register  *******************/
#define  ADC_JDOR2_JD                           ((uint16_t)0xFFFF)            /*!< Injected data */

/*******************  Bit definition for ADC_JDOR3 register  *******************/
#define  ADC_JDOR3_JD                           ((uint16_t)0xFFFF)            /*!< Injected data */

/*******************  Bit definition for ADC_JDOR4 register  *******************/
#define  ADC_JDOR4_JD                           ((uint16_t)0xFFFF)            /*!< Injected data */

/********************  Bit definition for ADC_RDOR register  ********************/
#define  ADC_RDOR_D                             ((uint32_t)0x0000FFFF)        /*!< Regular data */
#define  ADC_RDOR_AD2D                          ((uint32_t)0xFFFF0000)        /*!< ADC2 data */

/******************************************************************************/
/*                                                                            */
/*                      Digital to Analog Converter                           */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DAC_CTRL register  ********************/
#define  DAC_CTRL_EN1                           ((uint32_t)0x00000001)        /*!< DAC channel1 enable */
#define  DAC_CTRL_BF1                           ((uint32_t)0x00000002)        /*!< DAC channel1 output buffer disable */
#define  DAC_CTRL_TEN1                          ((uint32_t)0x00000004)        /*!< DAC channel1 Trigger enable */

#define  DAC_CTRL_TGSL1                         ((uint32_t)0x00000038)        /*!< TSEL1[2:0] (DAC channel1 Trigger selection) */
#define  DAC_CTRL_TGSL1_0                       ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  DAC_CTRL_TGSL1_1                       ((uint32_t)0x00000010)        /*!< Bit 1 */
#define  DAC_CTRL_TGSL1_2                       ((uint32_t)0x00000020)        /*!< Bit 2 */

#define  DAC_CTRL_WAVE1                         ((uint32_t)0x000000C0)        /*!< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define  DAC_CTRL_WAVE1_0                       ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  DAC_CTRL_WAVE1_1                       ((uint32_t)0x00000080)        /*!< Bit 1 */

#define  DAC_CTRL_MAMS1                         ((uint32_t)0x00000F00)        /*!< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define  DAC_CTRL_MAMS1_0                       ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  DAC_CTRL_MAMS1_1                       ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  DAC_CTRL_MAMS1_2                       ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  DAC_CTRL_MAMS1_3                       ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  DAC_CTRL_DMAEN1                        ((uint32_t)0x00001000)        /*!< DAC channel1 DMA enable */
#define  DAC_CTRL_EN2                           ((uint32_t)0x00010000)        /*!< DAC channel2 enable */
#define  DAC_CTRL_BF2                           ((uint32_t)0x00020000)        /*!< DAC channel2 output buffer disable */
#define  DAC_CTRL_TEN2                          ((uint32_t)0x00040000)        /*!< DAC channel2 Trigger enable */

#define  DAC_CTRL_TGSL2                         ((uint32_t)0x00380000)        /*!< TSEL2[2:0] (DAC channel2 Trigger selection) */
#define  DAC_CTRL_TGSL2_0                       ((uint32_t)0x00080000)        /*!< Bit 0 */
#define  DAC_CTRL_TGSL2_1                       ((uint32_t)0x00100000)        /*!< Bit 1 */
#define  DAC_CTRL_TGSL2_2                       ((uint32_t)0x00200000)        /*!< Bit 2 */

#define  DAC_CTRL_WAVE2                         ((uint32_t)0x00C00000)        /*!< WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable) */
#define  DAC_CTRL_WAVE2_0                       ((uint32_t)0x00400000)        /*!< Bit 0 */
#define  DAC_CTRL_WAVE2_1                       ((uint32_t)0x00800000)        /*!< Bit 1 */

#define  DAC_CTRL_MAMS2                         ((uint32_t)0x0F000000)        /*!< MAMP2[3:0] (DAC channel2 Mask/Amplitude selector) */
#define  DAC_CTRL_MAMS2_0                       ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  DAC_CTRL_MAMS2_1                       ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  DAC_CTRL_MAMS2_2                       ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  DAC_CTRL_MAMS2_3                       ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  DAC_CTRL_DMAEN2                        ((uint32_t)0x10000000)        /*!< DAC channel2 DMA enabled */

/*****************  Bit definition for DAC_SWTRG register  ******************/
#define  DAC_SWTRG_SWTRG1                       ((uint8_t)0x01)               /*!< DAC channel1 software trigger */
#define  DAC_SWTRG_SWTRG2                       ((uint8_t)0x02)               /*!< DAC channel2 software trigger */

/*****************  Bit definition for DAC_HDR12R1 register  ******************/
#define  DAC_HDR12R1_D1HDR                      ((uint16_t)0x0FFF)            /*!< DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_HDR12L1register  ******************/
#define  DAC_HDR12L1_D1HDR                      ((uint16_t)0xFFF0)            /*!< DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_HDR8R1 register  ******************/
#define  DAC_HDR8R1_D1HDR                       ((uint8_t)0xFF)               /*!< DAC channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_HDR12R2 register  ******************/
#define  DAC_HDR12R2_D2HDR                      ((uint16_t)0x0FFF)            /*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_HDR12L2 register  ******************/
#define  DAC_HDR12L2_D2HDR                      ((uint16_t)0xFFF0)            /*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_HDR8R2 register  ******************/
#define  DAC_HDR8R2_D2HDR                       ((uint8_t)0xFF)               /*!< DAC channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_HDR12RD register  ******************/
#define  DAC_HDR12RD_D1HDR                      ((uint32_t)0x00000FFF)        /*!< DAC channel1 12-bit Right aligned data */
#define  DAC_HDR12RD_D2HDR                      ((uint32_t)0x0FFF0000)        /*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_HDR12LD register  ******************/
#define  DAC_HDR12LD_D1HDR                      ((uint32_t)0x0000FFF0)        /*!< DAC channel1 12-bit Left aligned data */
#define  DAC_HDR12LD_D2HDR                      ((uint32_t)0xFFF00000)        /*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_HDR8RD register  ******************/
#define  DAC_HDR8RD_D1HDR                       ((uint16_t)0x00FF)            /*!< DAC channel1 8-bit Right aligned data */
#define  DAC_HDR8RD_D2HDR                       ((uint16_t)0xFF00)            /*!< DAC channel2 8-bit Right aligned data */

/*******************  Bit definition for DAC_ODT1 register  *******************/
#define  DAC_ODT1_D1ODT                         ((uint16_t)0x0FFF)            /*!< DAC channel1 data output */

/*******************  Bit definition for DAC_ODT2 register  *******************/
#define  DAC_ODT2_D2ODT                         ((uint16_t)0x0FFF)            /*!< DAC channel2 data output */

/********************  Bit definition for DAC_STS register  ********************/
#define  DAC_STS_DMAUDR1                        ((uint32_t)0x00002000)        /*!< DAC channel1 DMA underrun flag */
#define  DAC_STS_DMAUDR2                        ((uint32_t)0x20000000)        /*!< DAC channel2 DMA underrun flag */

/*****************************************************************************/
/*                                                                           */
/*                               Timers (TMR)                                */
/*                                                                           */
/*****************************************************************************/
/*******************  Bit definition for TMR_CTRL1 register  ********************/
#define  TMR_CTRL1_CNTEN                        ((uint16_t)0x0001)            /*!< Counter enable */
#define  TMR_CTRL1_UEVDIS                       ((uint16_t)0x0002)            /*!< Update disable */
#define  TMR_CTRL1_UVERS                        ((uint16_t)0x0004)            /*!< Update request source */
#define  TMR_CTRL1_OPMODE                       ((uint16_t)0x0008)            /*!< One pulse mode */
#define  TMR_CTRL1_DIR                          ((uint16_t)0x0010)            /*!< Direction */

#define  TMR_CTRL1_CMSEL                        ((uint16_t)0x0060)            /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define  TMR_CTRL1_CMSEL_0                      ((uint16_t)0x0020)            /*!< Bit 0 */
#define  TMR_CTRL1_CMSEL_1                      ((uint16_t)0x0040)            /*!< Bit 1 */

#define  TMR_CTRL1_ARPEN                        ((uint16_t)0x0080)            /*!< Auto-reload preload enable */

#define  TMR_CTRL1_CLKDIV                       ((uint16_t)0x0300)            /*!< CKD[1:0] bits (clock division) */
#define  TMR_CTRL1_CLKDIV_0                     ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TMR_CTRL1_CLKDIV_1                     ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TMR_CTRL1_PMEN                         ((uint16_t)0x0400)            /*!< 32bit counter enable */

/*******************  Bit definition for TMR_CTRL2 register  ********************/
#define  TMR_CTRL2_CPC                          ((uint16_t)0x0001)            /*!< Capture/Compare Preloaded Control */
#define  TMR_CTRL2_CUSEL                        ((uint16_t)0x0004)            /*!< Capture/Compare Control Update Selection */
#define  TMR_CTRL2_CDSEL                        ((uint16_t)0x0008)            /*!< Capture/Compare DMA Selection */

#define  TMR_CTRL2_MMSEL                        ((uint16_t)0x0070)            /*!< MMS[2:0] bits (Master Mode Selection) */
#define  TMR_CTRL2_MMSEL_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TMR_CTRL2_MMSEL_1                      ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TMR_CTRL2_MMSEL_2                      ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TMR_CTRL2_TI1SEL                       ((uint16_t)0x0080)            /*!< TI1 Selection */
#define  TMR_CTRL2_OC1IS                        ((uint16_t)0x0100)            /*!< Output Idle state 1 (OC1 output) */
#define  TMR_CTRL2_OC1NIS                       ((uint16_t)0x0200)            /*!< Output Idle state 1 (OC1N output) */
#define  TMR_CTRL2_OC2IS                        ((uint16_t)0x0400)            /*!< Output Idle state 2 (OC2 output) */
#define  TMR_CTRL2_OC2NIS                       ((uint16_t)0x0800)            /*!< Output Idle state 2 (OC2N output) */
#define  TMR_CTRL2_OC3IS                        ((uint16_t)0x1000)            /*!< Output Idle state 3 (OC3 output) */
#define  TMR_CTRL2_OC3NIS                       ((uint16_t)0x2000)            /*!< Output Idle state 3 (OC3N output) */
#define  TMR_CTRL2_OC4IS                        ((uint16_t)0x4000)            /*!< Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TMR_SMC register  *******************/
#define  TMR_SMC_SMSEL                          ((uint16_t)0x0007)            /*!< SMS[2:0] bits (Slave mode selection) */
#define  TMR_SMC_SMSEL_0                        ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TMR_SMC_SMSEL_1                        ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TMR_SMC_SMSEL_2                        ((uint16_t)0x0004)            /*!< Bit 2 */

#define  TMR_SMC_TRGSEL                         ((uint16_t)0x0070)            /*!< TS[2:0] bits (Trigger selection) */
#define  TMR_SMC_TRGSEL_0                       ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TMR_SMC_TRGSEL_1                       ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TMR_SMC_TRGSEL_2                       ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TMR_SMC_MSMODE                         ((uint16_t)0x0080)            /*!< Master/slave mode */

#define  TMR_SMC_ETDF                           ((uint16_t)0x0F00)            /*!< ETF[3:0] bits (External trigger filter) */
#define  TMR_SMC_ETDF_0                         ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TMR_SMC_ETDF_1                         ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TMR_SMC_ETDF_2                         ((uint16_t)0x0400)            /*!< Bit 2 */
#define  TMR_SMC_ETDF_3                         ((uint16_t)0x0800)            /*!< Bit 3 */

#define  TMR_SMC_ETD                            ((uint16_t)0x3000)            /*!< ETPS[1:0] bits (External trigger prescaler) */
#define  TMR_SMC_ETD_0                          ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TMR_SMC_ETD_1                          ((uint16_t)0x2000)            /*!< Bit 1 */

#define  TMR_SMC_ECLKEN                         ((uint16_t)0x4000)            /*!< External clock enable */
#define  TMR_SMC_ETRGP                          ((uint16_t)0x8000)            /*!< External trigger polarity */

/*******************  Bit definition for TMR_DIE register  *******************/
#define  TMR_DIE_UEVIE                          ((uint16_t)0x0001)            /*!< Update interrupt enable */
#define  TMR_DIE_C1IE                           ((uint16_t)0x0002)            /*!< Capture/Compare 1 interrupt enable */
#define  TMR_DIE_C2IE                           ((uint16_t)0x0004)            /*!< Capture/Compare 2 interrupt enable */
#define  TMR_DIE_C3IE                           ((uint16_t)0x0008)            /*!< Capture/Compare 3 interrupt enable */
#define  TMR_DIE_C4IE                           ((uint16_t)0x0010)            /*!< Capture/Compare 4 interrupt enable */
#define  TMR_DIE_HALLIE                         ((uint16_t)0x0020)            /*!< COM interrupt enable */
#define  TMR_DIE_TRGIE                          ((uint16_t)0x0040)            /*!< Trigger interrupt enable */
#define  TMR_DIE_BRKIE                          ((uint16_t)0x0080)            /*!< Break interrupt enable */
#define  TMR_DIE_UEVDE                          ((uint16_t)0x0100)            /*!< Update DMA request enable */
#define  TMR_DIE_C1DE                           ((uint16_t)0x0200)            /*!< Capture/Compare 1 DMA request enable */
#define  TMR_DIE_C2DE                           ((uint16_t)0x0400)            /*!< Capture/Compare 2 DMA request enable */
#define  TMR_DIE_C3DE                           ((uint16_t)0x0800)            /*!< Capture/Compare 3 DMA request enable */
#define  TMR_DIE_C4DE                           ((uint16_t)0x1000)            /*!< Capture/Compare 4 DMA request enable */
#define  TMR_DIE_HALLDE                         ((uint16_t)0x2000)            /*!< COM DMA request enable */
#define  TMR_DIE_TRGDE                          ((uint16_t)0x4000)            /*!< Trigger DMA request enable */

/********************  Bit definition for TMR_STS register  ********************/
#define  TMR_STS_UEVIF                          ((uint16_t)0x0001)            /*!< Update interrupt Flag */
#define  TMR_STS_C1IF                           ((uint16_t)0x0002)            /*!< Capture/Compare 1 interrupt Flag */
#define  TMR_STS_C2IF                           ((uint16_t)0x0004)            /*!< Capture/Compare 2 interrupt Flag */
#define  TMR_STS_C3IF                           ((uint16_t)0x0008)            /*!< Capture/Compare 3 interrupt Flag */
#define  TMR_STS_C4IF                           ((uint16_t)0x0010)            /*!< Capture/Compare 4 interrupt Flag */
#define  TMR_STS_HALLIF                         ((uint16_t)0x0020)            /*!< COM interrupt Flag */
#define  TMR_STS_TRGIF                          ((uint16_t)0x0040)            /*!< Trigger interrupt Flag */
#define  TMR_STS_BRKIF                          ((uint16_t)0x0080)            /*!< Break interrupt Flag */
#define  TMR_STS_C1OF                           ((uint16_t)0x0200)            /*!< Capture/Compare 1 Overcapture Flag */
#define  TMR_STS_C2OF                           ((uint16_t)0x0400)            /*!< Capture/Compare 2 Overcapture Flag */
#define  TMR_STS_C3OF                           ((uint16_t)0x0800)            /*!< Capture/Compare 3 Overcapture Flag */
#define  TMR_STS_C4OF                           ((uint16_t)0x1000)            /*!< Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TMR_EVEG register  ********************/
#define  TMR_EVEG_UEVG                          ((uint8_t)0x01)               /*!< Update Generation */
#define  TMR_EVEG_C1G                           ((uint8_t)0x02)               /*!< Capture/Compare 1 Generation */
#define  TMR_EVEG_C2G                           ((uint8_t)0x04)               /*!< Capture/Compare 2 Generation */
#define  TMR_EVEG_C3G                           ((uint8_t)0x08)               /*!< Capture/Compare 3 Generation */
#define  TMR_EVEG_C4G                           ((uint8_t)0x10)               /*!< Capture/Compare 4 Generation */
#define  TMR_EVEG_HALLG                         ((uint8_t)0x20)               /*!< Capture/Compare Control Update Generation */
#define  TMR_EVEG_TRGG                          ((uint8_t)0x40)               /*!< Trigger Generation */
#define  TMR_EVEG_BRKG                          ((uint8_t)0x80)               /*!< Break Generation */

/******************  Bit definition for TMR_CCM1 register  *******************/
#define  TMR_CCM1_C1SEL                         ((uint16_t)0x0003)            /*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TMR_CCM1_C1SEL_0                       ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TMR_CCM1_C1SEL_1                       ((uint16_t)0x0002)            /*!< Bit 1 */

#define  TMR_CCM1_OC1FEN                        ((uint16_t)0x0004)            /*!< Output Compare 1 Fast enable */
#define  TMR_CCM1_OC1PEN                        ((uint16_t)0x0008)            /*!< Output Compare 1 Preload enable */

#define  TMR_CCM1_OC1MODE                       ((uint16_t)0x0070)            /*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TMR_CCM1_OC1MODE_0                     ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TMR_CCM1_OC1MODE_1                     ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TMR_CCM1_OC1MODE_2                     ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TMR_CCM1_C1CDIS                        ((uint16_t)0x0080)            /*!< Output Compare 1Clear Enable */

#define  TMR_CCM1_C2SEL                         ((uint16_t)0x0300)            /*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TMR_CCM1_C2SEL_0                       ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TMR_CCM1_C2SEL_1                       ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TMR_CCM1_OC2FNE                        ((uint16_t)0x0400)            /*!< Output Compare 2 Fast enable */
#define  TMR_CCM1_OC2PEN                        ((uint16_t)0x0800)            /*!< Output Compare 2 Preload enable */

#define  TMR_CCM1_OC2MODE                       ((uint16_t)0x7000)            /*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TMR_CCM1_OC2MODE_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TMR_CCM1_OC2MODE_1                     ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TMR_CCM1_OC2MODE_2                     ((uint16_t)0x4000)            /*!< Bit 2 */

#define  TMR_CCM1_OC2CDIS                       ((uint16_t)0x8000)            /*!< Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TMR_CCM1_IC1DIV                        ((uint16_t)0x000C)            /*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TMR_CCM1_IC1DIV_0                      ((uint16_t)0x0004)            /*!< Bit 0 */
#define  TMR_CCM1_IC1DIV_1                      ((uint16_t)0x0008)            /*!< Bit 1 */

#define  TMR_CCM1_IC1F                          ((uint16_t)0x00F0)            /*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TMR_CCM1_IC1F_0                        ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TMR_CCM1_IC1F_1                        ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TMR_CCM1_IC1F_2                        ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TMR_CCM1_IC1F_3                        ((uint16_t)0x0080)            /*!< Bit 3 */

#define  TMR_CCM1_IC2DIV                        ((uint16_t)0x0C00)            /*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TMR_CCM1_IC2DIV_0                      ((uint16_t)0x0400)            /*!< Bit 0 */
#define  TMR_CCM1_IC2DIVC_1                     ((uint16_t)0x0800)            /*!< Bit 1 */

#define  TMR_CCM1_IC2DF                         ((uint16_t)0xF000)            /*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TMR_CCM1_IC2DF_0                       ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TMR_CCM1_IC2DF_1                       ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TMR_CCM1_IC2DF_2                       ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TMR_CCM1_IC2DF_3                       ((uint16_t)0x8000)            /*!< Bit 3 */

/******************  Bit definition for TMR_CCM2 register  *******************/
#define  TMR_CCM2_C3SEL                         ((uint16_t)0x0003)            /*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TMR_CCM2_C3SEL_0                       ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TMR_CCM2_C3SEL_1                       ((uint16_t)0x0002)            /*!< Bit 1 */

#define  TMR_CCM2_OC3FEN                        ((uint16_t)0x0004)            /*!< Output Compare 3 Fast enable */
#define  TMR_CCM2_OC3PEN                        ((uint16_t)0x0008)            /*!< Output Compare 3 Preload enable */

#define  TMR_CCM2_OC3MODE                       ((uint16_t)0x0070)            /*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TMR_CCM2_OC3MODE_0                     ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TMR_CCM2_OC3MODE_1                     ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TMR_CCM2_OC3MODE_2                     ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TMR_CCM2_OC3CDIS                       ((uint16_t)0x0080)            /*!< Output Compare 3 Clear Enable */

#define  TMR_CCM2_CC4S                          ((uint16_t)0x0300)            /*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TMR_CCM2_CC4S_0                        ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TMR_CCM2_CC4S_1                        ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TMR_CCM2_OC4FE                         ((uint16_t)0x0400)            /*!< Output Compare 4 Fast enable */
#define  TMR_CCM2_OC4PE                         ((uint16_t)0x0800)            /*!< Output Compare 4 Preload enable */

#define  TMR_CCM2_OC4MODE                       ((uint16_t)0x7000)            /*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TMR_CCM2_OC4MODE_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TMR_CCM2_OC4MODE_1                     ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TMR_CCM2_OC4MODE_2                     ((uint16_t)0x4000)            /*!< Bit 2 */

#define  TMR_CCM2_OC4CDIS                       ((uint16_t)0x8000)            /*!< Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TMR_CCM2_IC3DIV                        ((uint16_t)0x000C)            /*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TMR_CCM2_IC3DIV_0                      ((uint16_t)0x0004)            /*!< Bit 0 */
#define  TMR_CCM2_IC3DIV_1                      ((uint16_t)0x0008)            /*!< Bit 1 */

#define  TMR_CCM2_IC3DF                         ((uint16_t)0x00F0)            /*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TMR_CCM2_IC3DF_0                       ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TMR_CCM2_IC3DF_1                       ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TMR_CCM2_IC3DF_2                       ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TMR_CCM2_IC3DF_3                       ((uint16_t)0x0080)            /*!< Bit 3 */

#define  TMR_CCM2_IC4DIV                        ((uint16_t)0x0C00)            /*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TMR_CCM2_IC4DIV_0                      ((uint16_t)0x0400)            /*!< Bit 0 */
#define  TMR_CCM2_IC4DIV_1                      ((uint16_t)0x0800)            /*!< Bit 1 */

#define  TMR_CCM2_IC4DF                         ((uint16_t)0xF000)            /*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TMR_CCM2_IC4DF_0                       ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TMR_CCM2_IC4DF_1                       ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TMR_CCM2_IC4DF_2                       ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TMR_CCM2_IC4DF_3                       ((uint16_t)0x8000)            /*!< Bit 3 */

/*******************  Bit definition for TMR_CCE register  *******************/
#define  TMR_CCE_C1EN                           ((uint16_t)0x0001)            /*!< Capture/Compare 1 output enable */
#define  TMR_CCE_C1P                            ((uint16_t)0x0002)            /*!< Capture/Compare 1 output Polarity */
#define  TMR_CCE_C1NEN                           ((uint16_t)0x0004)            /*!< Capture/Compare 1 Complementary output enable */
#define  TMR_CCE_C1NP                           ((uint16_t)0x0008)            /*!< Capture/Compare 1 Complementary output Polarity */
#define  TMR_CCE_C2EN                           ((uint16_t)0x0010)            /*!< Capture/Compare 2 output enable */
#define  TMR_CCE_C2P                            ((uint16_t)0x0020)            /*!< Capture/Compare 2 output Polarity */
#define  TMR_CCE_C2NEN                          ((uint16_t)0x0040)            /*!< Capture/Compare 2 Complementary output enable */
#define  TMR_CCE_C2NP                           ((uint16_t)0x0080)            /*!< Capture/Compare 2 Complementary output Polarity */
#define  TMR_CCE_C3EN                           ((uint16_t)0x0100)            /*!< Capture/Compare 3 output enable */
#define  TMR_CCE_C3P                            ((uint16_t)0x0200)            /*!< Capture/Compare 3 output Polarity */
#define  TMR_CCE_C3NEN                          ((uint16_t)0x0400)            /*!< Capture/Compare 3 Complementary output enable */
#define  TMR_CCE_C3NP                           ((uint16_t)0x0800)            /*!< Capture/Compare 3 Complementary output Polarity */
#define  TMR_CCE_C4EN                           ((uint16_t)0x1000)            /*!< Capture/Compare 4 output enable */
#define  TMR_CCE_C4P                            ((uint16_t)0x2000)            /*!< Capture/Compare 4 output Polarity */
#define  TMR_CCE_C4NP                           ((uint16_t)0x8000)            /*!< Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TMR_CNT register  ********************/
#define  TMR_CNT_CNT                            ((uint16_t)0xFFFF)            /*!< Counter Value */

/*******************  Bit definition for TMR_DIV register  ********************/
#define  TMR_DIV_DIV                            ((uint16_t)0xFFFF)            /*!< Prescaler Value */

/*******************  Bit definition for TMR_AR register  ********************/
#define  TMR_AR_AR                              ((uint16_t)0xFFFF)            /*!< actual auto-reload Value */

/*******************  Bit definition for TMR_RC register  ********************/
#define  TMR_RC_RC                              ((uint8_t)0xFF)               /*!< Repetition Counter Value */

/*******************  Bit definition for TMR_CC1 register  *******************/
#define  TMR_CC1_CC1                            ((uint16_t)0xFFFF)            /*!< Capture/Compare 1 Value */

/*******************  Bit definition for TMR_CC2 register  *******************/
#define  TMR_CC2_CC2                            ((uint16_t)0xFFFF)            /*!< Capture/Compare 2 Value */

/*******************  Bit definition for TMR_CC3 register  *******************/
#define  TMR_CC3_CC3                            ((uint16_t)0xFFFF)            /*!< Capture/Compare 3 Value */

/*******************  Bit definition for TMR_CC4 register  *******************/
#define  TMR_CC4_CC4                            ((uint16_t)0xFFFF)            /*!< Capture/Compare 4 Value */

/*******************  Bit definition for TMR_BRKDT register  *******************/
#define  TMR_BRKDT_DTGS                         ((uint16_t)0x00FF)            /*!< DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TMR_BRKDT_DTGS_0                       ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TMR_BRKDT_DTGS_1                       ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TMR_BRKDT_DTGS_2                       ((uint16_t)0x0004)            /*!< Bit 2 */
#define  TMR_BRKDT_DTGS_3                       ((uint16_t)0x0008)            /*!< Bit 3 */
#define  TMR_BRKDT_DTGS_4                       ((uint16_t)0x0010)            /*!< Bit 4 */
#define  TMR_BRKDT_DTGS_5                       ((uint16_t)0x0020)            /*!< Bit 5 */
#define  TMR_BRKDT_DTGS_6                       ((uint16_t)0x0040)            /*!< Bit 6 */
#define  TMR_BRKDT_DTGS_7                       ((uint16_t)0x0080)            /*!< Bit 7 */

#define  TMR_BRKDT_LOCKC                        ((uint16_t)0x0300)            /*!< LOCK[1:0] bits (Lock Configuration) */
#define  TMR_BRKDT_LOCKC_0                      ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TMR_BRKDT_LOCKC_1                      ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TMR_BRKDT_OSIMI                        ((uint16_t)0x0400)            /*!< Off-State Selection for Idle mode */
#define  TMR_BRKDT_OSIMR                        ((uint16_t)0x0800)            /*!< Off-State Selection for Run mode */
#define  TMR_BRKDT_BRKEN                        ((uint16_t)0x1000)            /*!< Break enable */
#define  TMR_BRKDT_BRKP                         ((uint16_t)0x2000)            /*!< Break Polarity */
#define  TMR_BRKDT_AOEN                         ((uint16_t)0x4000)            /*!< Automatic Output enable */
#define  TMR_BRKDT_MOEN                         ((uint16_t)0x8000)            /*!< Main Output enable */

/*******************  Bit definition for TMR_DMAC register  ********************/
#define  TMR_DMAC_ADDR                          ((uint16_t)0x001F)            /*!< DBA[4:0] bits (DMA Base Address) */
#define  TMR_DMAC_ADDR_0                        ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TMR_DMAC_ADDR_1                        ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TMR_DMAC_ADDR_2                        ((uint16_t)0x0004)            /*!< Bit 2 */
#define  TMR_DMAC_ADDR_3                        ((uint16_t)0x0008)            /*!< Bit 3 */
#define  TMR_DMAC_ADDR_4                        ((uint16_t)0x0010)            /*!< Bit 4 */

#define  TMR_DMAC_DBLEN                         ((uint16_t)0x1F00)            /*!< DBL[4:0] bits (DMA Burst Length) */
#define  TMR_DMAC_DBLEN_0                       ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TMR_DMAC_DBLEN_1                       ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TMR_DMAC_DBLEN_2                       ((uint16_t)0x0400)            /*!< Bit 2 */
#define  TMR_DMAC_DBLEN_3                       ((uint16_t)0x0800)            /*!< Bit 3 */
#define  TMR_DMAC_DBLEN_4                       ((uint16_t)0x1000)            /*!< Bit 4 */

/*******************  Bit definition for TMR_DMABA register  *******************/
#define  TMR_DMABA_DMABA                    ((uint16_t)0xFFFF)            /*!< DMA register for burst accesses */

/******************************************************************************/
/*                                                                            */
/*                             Real-Time Clock                                */
/*                                                                            */
/******************************************************************************/
#if defined (AT32F415xx)
/********************  Bits definition for ERTC_TIME register  *******************/
#define ERTC_TIME_AMPM                          ((uint32_t)0x00400000)
#define ERTC_TIME_HT                            ((uint32_t)0x00300000)
#define ERTC_TIME_HT_0                          ((uint32_t)0x00100000)
#define ERTC_TIME_HT_1                          ((uint32_t)0x00200000)
#define ERTC_TIME_HU                            ((uint32_t)0x000F0000)
#define ERTC_TIME_HU_0                          ((uint32_t)0x00010000)
#define ERTC_TIME_HU_1                          ((uint32_t)0x00020000)
#define ERTC_TIME_HU_2                          ((uint32_t)0x00040000)
#define ERTC_TIME_HU_3                          ((uint32_t)0x00080000)
#define ERTC_TIME_MT                            ((uint32_t)0x00007000)
#define ERTC_TIME_MT_0                          ((uint32_t)0x00001000)
#define ERTC_TIME_MT_1                          ((uint32_t)0x00002000)
#define ERTC_TIME_MT_2                          ((uint32_t)0x00004000)
#define ERTC_TIME_MU                            ((uint32_t)0x00000F00)
#define ERTC_TIME_MU_0                          ((uint32_t)0x00000100)
#define ERTC_TIME_MU_1                          ((uint32_t)0x00000200)
#define ERTC_TIME_MU_2                          ((uint32_t)0x00000400)
#define ERTC_TIME_MU_3                          ((uint32_t)0x00000800)
#define ERTC_TIME_ST                            ((uint32_t)0x00000070)
#define ERTC_TIME_ST_0                          ((uint32_t)0x00000010)
#define ERTC_TIME_ST_1                          ((uint32_t)0x00000020)
#define ERTC_TIME_ST_2                          ((uint32_t)0x00000040)
#define ERTC_TIME_SU                            ((uint32_t)0x0000000F)
#define ERTC_TIME_SU_0                          ((uint32_t)0x00000001)
#define ERTC_TIME_SU_1                          ((uint32_t)0x00000002)
#define ERTC_TIME_SU_2                          ((uint32_t)0x00000004)
#define ERTC_TIME_SU_3                          ((uint32_t)0x00000008)

/********************  Bits definition for ERTC_DATE register  *******************/
#define ERTC_DATE_YT                            ((uint32_t)0x00F00000)
#define ERTC_DATE_YT_0                          ((uint32_t)0x00100000)
#define ERTC_DATE_YT_1                          ((uint32_t)0x00200000)
#define ERTC_DATE_YT_2                          ((uint32_t)0x00400000)
#define ERTC_DATE_YT_3                          ((uint32_t)0x00800000)
#define ERTC_DATE_YU                            ((uint32_t)0x000F0000)
#define ERTC_DATE_YU_0                          ((uint32_t)0x00010000)
#define ERTC_DATE_YU_1                          ((uint32_t)0x00020000)
#define ERTC_DATE_YU_2                          ((uint32_t)0x00040000)
#define ERTC_DATE_YU_3                          ((uint32_t)0x00080000)
#define ERTC_DATE_WK                            ((uint32_t)0x0000E000)
#define ERTC_DATE_WK_0                          ((uint32_t)0x00002000)
#define ERTC_DATE_WK_1                          ((uint32_t)0x00004000)
#define ERTC_DATE_WK_2                          ((uint32_t)0x00008000)
#define ERTC_DATE_MT                            ((uint32_t)0x00001000)
#define ERTC_DATE_MU                            ((uint32_t)0x00000F00)
#define ERTC_DATE_MU_0                          ((uint32_t)0x00000100)
#define ERTC_DATE_MU_1                          ((uint32_t)0x00000200)
#define ERTC_DATE_MU_2                          ((uint32_t)0x00000400)
#define ERTC_DATE_MU_3                          ((uint32_t)0x00000800)
#define ERTC_DATE_DT                            ((uint32_t)0x00000030)
#define ERTC_DATE_DT_0                          ((uint32_t)0x00000010)
#define ERTC_DATE_DT_1                          ((uint32_t)0x00000020)
#define ERTC_DATE_DU                            ((uint32_t)0x0000000F)
#define ERTC_DATE_DU_0                          ((uint32_t)0x00000001)
#define ERTC_DATE_DU_1                          ((uint32_t)0x00000002)
#define ERTC_DATE_DU_2                          ((uint32_t)0x00000004)
#define ERTC_DATE_DU_3                          ((uint32_t)0x00000008)

/********************  Bits definition for ERTC_CTRL register  *******************/
#define ERTC_CTRL_CALOE                         ((uint32_t)0x00800000)
#define ERTC_CTRL_OSEL                          ((uint32_t)0x00600000)
#define ERTC_CTRL_OSEL_0                        ((uint32_t)0x00200000)
#define ERTC_CTRL_OSEL_1                        ((uint32_t)0x00400000)
#define ERTC_CTRL_OPOL                          ((uint32_t)0x00100000)
#define ERTC_CTRL_CALSEL                        ((uint32_t)0x00080000)
#define ERTC_CTRL_BKP                           ((uint32_t)0x00040000)
#define ERTC_CTRL_SUB1H                         ((uint32_t)0x00020000)
#define ERTC_CTRL_ADD1H                         ((uint32_t)0x00010000)
#define ERTC_CTRL_TSIE                          ((uint32_t)0x00008000)
#define ERTC_CTRL_WATIE                         ((uint32_t)0x00004000)
#define ERTC_CTRL_ALBIE                         ((uint32_t)0x00002000)
#define ERTC_CTRL_ALAIE                         ((uint32_t)0x00001000)
#define ERTC_CTRL_TSE                           ((uint32_t)0x00000800)
#define ERTC_CTRL_WATE                          ((uint32_t)0x00000400)
#define ERTC_CTRL_ALBE                          ((uint32_t)0x00000200)
#define ERTC_CTRL_ALAE                          ((uint32_t)0x00000100)
#define ERTC_CTRL_CDCE                          ((uint32_t)0x00000080)
#define ERTC_CTRL_HFM                           ((uint32_t)0x00000040)
#define ERTC_CTRL_BYPSHDW                       ((uint32_t)0x00000020)
#define ERTC_CTRL_RFCKON                        ((uint32_t)0x00000010)
#define ERTC_CTRL_TSEDGE                        ((uint32_t)0x00000008)
#define ERTC_CTRL_WACKSEL                       ((uint32_t)0x00000007)
#define ERTC_CTRL_WACKSEL_0                     ((uint32_t)0x00000001)
#define ERTC_CTRL_WACKSEL_1                     ((uint32_t)0x00000002)
#define ERTC_CTRL_WACKSEL_2                     ((uint32_t)0x00000004)

/********************  Bits definition for ERTC_ISTS register  ******************/
#define ERTC_ISTS_RECALPDF                      ((uint32_t)0x00010000)
#define ERTC_ISTS_TPF                           ((uint32_t)0x00002000)
#define ERTC_ISTS_TP2F                          ((uint32_t)0x00004000)
#define ERTC_ISTS_TSOF                          ((uint32_t)0x00001000)
#define ERTC_ISTS_TSF                           ((uint32_t)0x00000800)
#define ERTC_ISTS_WATF                          ((uint32_t)0x00000400)
#define ERTC_ISTS_ALBF                          ((uint32_t)0x00000200)
#define ERTC_ISTS_ALAF                          ((uint32_t)0x00000100)
#define ERTC_ISTS_INITM                         ((uint32_t)0x00000080)
#define ERTC_ISTS_INITF                         ((uint32_t)0x00000040)
#define ERTC_ISTS_RSF                           ((uint32_t)0x00000020)
#define ERTC_ISTS_INITS                         ((uint32_t)0x00000010)
#define ERTC_ISTS_SFP                           ((uint32_t)0x00000008)
#define ERTC_ISTS_WATWF                         ((uint32_t)0x00000004)
#define ERTC_ISTS_ALBWF                         ((uint32_t)0x00000002)
#define ERTC_ISTS_ALAWF                         ((uint32_t)0x00000001)

/********************  Bits definition for ERTC_PSC register  *****************/
#define ERTC_PSC_PRDIV_A                        ((uint32_t)0x007F0000)
#define ERTC_PSC_PRDIV_S                        ((uint32_t)0x00001FFF)

/********************  Bits definition for ERTC_WATR register  *****************/
#define ERTC_WATR_WAREV                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for ERTC_CAL register  ***************/
#define ERTC_CAL_DCALS                          ((uint32_t)0x00000080)
#define ERTC_CAL_DCAL                           ((uint32_t)0x0000001F)

/********************  Bits definition for ERTC_ALA register  ***************/
#define ERTC_ALA_MASK4                          ((uint32_t)0x80000000)
#define ERTC_ALA_WKSEL                          ((uint32_t)0x40000000)
#define ERTC_ALA_DT                             ((uint32_t)0x30000000)
#define ERTC_ALA_DT_0                           ((uint32_t)0x10000000)
#define ERTC_ALA_DT_1                           ((uint32_t)0x20000000)
#define ERTC_ALA_DU                             ((uint32_t)0x0F000000)
#define ERTC_ALA_DU_0                           ((uint32_t)0x01000000)
#define ERTC_ALA_DU_1                           ((uint32_t)0x02000000)
#define ERTC_ALA_DU_2                           ((uint32_t)0x04000000)
#define ERTC_ALA_DU_3                           ((uint32_t)0x08000000)
#define ERTC_ALA_MASK3                          ((uint32_t)0x00800000)
#define ERTC_ALA_AMPM                           ((uint32_t)0x00400000)
#define ERTC_ALA_HT                             ((uint32_t)0x00300000)
#define ERTC_ALA_HT_0                           ((uint32_t)0x00100000)
#define ERTC_ALA_HT_1                           ((uint32_t)0x00200000)
#define ERTC_ALA_HU                             ((uint32_t)0x000F0000)
#define ERTC_ALA_HU_0                           ((uint32_t)0x00010000)
#define ERTC_ALA_HU_1                           ((uint32_t)0x00020000)
#define ERTC_ALA_HU_2                           ((uint32_t)0x00040000)
#define ERTC_ALA_HU_3                           ((uint32_t)0x00080000)
#define ERTC_ALA_MASK2                          ((uint32_t)0x00008000)
#define ERTC_ALA_MT                             ((uint32_t)0x00007000)
#define ERTC_ALA_MT_0                           ((uint32_t)0x00001000)
#define ERTC_ALA_MT_1                           ((uint32_t)0x00002000)
#define ERTC_ALA_MT_2                           ((uint32_t)0x00004000)
#define ERTC_ALA_MU                             ((uint32_t)0x00000F00)
#define ERTC_ALA_MU_0                           ((uint32_t)0x00000100)
#define ERTC_ALA_MU_1                           ((uint32_t)0x00000200)
#define ERTC_ALA_MU_2                           ((uint32_t)0x00000400)
#define ERTC_ALA_MU_3                           ((uint32_t)0x00000800)
#define ERTC_ALA_MASK1                          ((uint32_t)0x00000080)
#define ERTC_ALA_ST                             ((uint32_t)0x00000070)
#define ERTC_ALA_ST_0                           ((uint32_t)0x00000010)
#define ERTC_ALA_ST_1                           ((uint32_t)0x00000020)
#define ERTC_ALA_ST_2                           ((uint32_t)0x00000040)
#define ERTC_ALA_SU                             ((uint32_t)0x0000000F)
#define ERTC_ALA_SU_0                           ((uint32_t)0x00000001)
#define ERTC_ALA_SU_1                           ((uint32_t)0x00000002)
#define ERTC_ALA_SU_2                           ((uint32_t)0x00000004)
#define ERTC_ALA_SU_3                           ((uint32_t)0x00000008)

/********************  Bits definition for ERTC_ALB register  ***************/
#define ERTC_ALB_MASK4                          ((uint32_t)0x80000000)
#define ERTC_ALB_WKSEL                          ((uint32_t)0x40000000)
#define ERTC_ALB_DT                             ((uint32_t)0x30000000)
#define ERTC_ALB_DT_0                           ((uint32_t)0x10000000)
#define ERTC_ALB_DT_1                           ((uint32_t)0x20000000)
#define ERTC_ALB_DU                             ((uint32_t)0x0F000000)
#define ERTC_ALB_DU_0                           ((uint32_t)0x01000000)
#define ERTC_ALB_DU_1                           ((uint32_t)0x02000000)
#define ERTC_ALB_DU_2                           ((uint32_t)0x04000000)
#define ERTC_ALB_DU_3                           ((uint32_t)0x08000000)
#define ERTC_ALB_MASK3                          ((uint32_t)0x00800000)
#define ERTC_ALB_AMPM                           ((uint32_t)0x00400000)
#define ERTC_ALB_HT                             ((uint32_t)0x00300000)
#define ERTC_ALB_HT_0                           ((uint32_t)0x00100000)
#define ERTC_ALB_HT_1                           ((uint32_t)0x00200000)
#define ERTC_ALB_HU                             ((uint32_t)0x000F0000)
#define ERTC_ALB_HU_0                           ((uint32_t)0x00010000)
#define ERTC_ALB_HU_1                           ((uint32_t)0x00020000)
#define ERTC_ALB_HU_2                           ((uint32_t)0x00040000)
#define ERTC_ALB_HU_3                           ((uint32_t)0x00080000)
#define ERTC_ALB_MASK2                          ((uint32_t)0x00008000)
#define ERTC_ALB_MT                             ((uint32_t)0x00007000)
#define ERTC_ALB_MT_0                           ((uint32_t)0x00001000)
#define ERTC_ALB_MT_1                           ((uint32_t)0x00002000)
#define ERTC_ALB_MT_2                           ((uint32_t)0x00004000)
#define ERTC_ALB_MU                             ((uint32_t)0x00000F00)
#define ERTC_ALB_MU_0                           ((uint32_t)0x00000100)
#define ERTC_ALB_MU_1                           ((uint32_t)0x00000200)
#define ERTC_ALB_MU_2                           ((uint32_t)0x00000400)
#define ERTC_ALB_MU_3                           ((uint32_t)0x00000800)
#define ERTC_ALB_MASK1                          ((uint32_t)0x00000080)
#define ERTC_ALB_ST                             ((uint32_t)0x00000070)
#define ERTC_ALB_ST_0                           ((uint32_t)0x00000010)
#define ERTC_ALB_ST_1                           ((uint32_t)0x00000020)
#define ERTC_ALB_ST_2                           ((uint32_t)0x00000040)
#define ERTC_ALA_SU                             ((uint32_t)0x0000000F)
#define ERTC_ALA_SU_0                           ((uint32_t)0x00000001)
#define ERTC_ALA_SU_1                           ((uint32_t)0x00000002)
#define ERTC_ALA_SU_2                           ((uint32_t)0x00000004)
#define ERTC_ALA_SU_3                           ((uint32_t)0x00000008)

/********************  Bits definition for ERTC_WPR register  ******************/
#define ERTC_WPR_KEY                            ((uint32_t)0x000000FF)

/********************  Bits definition for ERTC_SBSR register  ******************/
#define ERTC_SBSR_SBS                           ((uint32_t)0x0000FFFF)

/********************  Bits definition for ERTC_SFCTR register  ***************/
#define ERTC_SFCTR_SUBSBS                       ((uint32_t)0x00007FFF)
#define ERTC_SFCTR_ADD1S                        ((uint32_t)0x80000000)

/********************  Bits definition for ERTC_TSTM register  *****************/
#define ERTC_TSTM_AMPM                          ((uint32_t)0x00400000)
#define ERTC_TSTM_HT                            ((uint32_t)0x00300000)
#define ERTC_TSTM_HT_0                          ((uint32_t)0x00100000)
#define ERTC_TSTM_HT_1                          ((uint32_t)0x00200000)
#define ERTC_TSTM_HU                            ((uint32_t)0x000F0000)
#define ERTC_TSTM_HU_0                          ((uint32_t)0x00010000)
#define ERTC_TSTM_HU_1                          ((uint32_t)0x00020000)
#define ERTC_TSTM_HU_2                          ((uint32_t)0x00040000)
#define ERTC_TSTM_HU_3                          ((uint32_t)0x00080000)
#define ERTC_TSTM_MT                            ((uint32_t)0x00007000)
#define ERTC_TSTM_MT_0                          ((uint32_t)0x00001000)
#define ERTC_TSTM_MT_1                          ((uint32_t)0x00002000)
#define ERTC_TSTM_MT_2                          ((uint32_t)0x00004000)
#define ERTC_TSTM_MU                            ((uint32_t)0x00000F00)
#define ERTC_TSTM_MU_0                          ((uint32_t)0x00000100)
#define ERTC_TSTM_MU_1                          ((uint32_t)0x00000200)
#define ERTC_TSTM_MU_2                          ((uint32_t)0x00000400)
#define ERTC_TSTM_MU_3                          ((uint32_t)0x00000800)
#define ERTC_TSTM_ST                            ((uint32_t)0x00000070)
#define ERTC_TSTM_ST_0                          ((uint32_t)0x00000010)
#define ERTC_TSTM_ST_1                          ((uint32_t)0x00000020)
#define ERTC_TSTM_ST_2                          ((uint32_t)0x00000040)
#define ERTC_TSTM_SU                            ((uint32_t)0x0000000F)
#define ERTC_TSTM_SU_0                          ((uint32_t)0x00000001)
#define ERTC_TSTM_SU_1                          ((uint32_t)0x00000002)
#define ERTC_TSTM_SU_2                          ((uint32_t)0x00000004)
#define ERTC_TSTM_SU_3                          ((uint32_t)0x00000008)

/********************  Bits definition for ERTC_TSDT register  *****************/
#define ERTC_TSDT_WK                            ((uint32_t)0x0000E000)
#define ERTC_TSDT_WK_0                          ((uint32_t)0x00002000)
#define ERTC_TSDT_WK_1                          ((uint32_t)0x00004000)
#define ERTC_TSDT_WK_2                          ((uint32_t)0x00008000)
#define ERTC_TSDT_MT                            ((uint32_t)0x00001000)
#define ERTC_TSDT_MU                            ((uint32_t)0x00000F00)
#define ERTC_TSDT_MU_0                          ((uint32_t)0x00000100)
#define ERTC_TSDT_MU_1                          ((uint32_t)0x00000200)
#define ERTC_TSDT_MU_2                          ((uint32_t)0x00000400)
#define ERTC_TSDT_MU_3                          ((uint32_t)0x00000800)
#define ERTC_TSDT_DT                            ((uint32_t)0x00000030)
#define ERTC_TSDT_DT_0                          ((uint32_t)0x00000010)
#define ERTC_TSDT_DT_1                          ((uint32_t)0x00000020)
#define ERTC_TSDT_DU                            ((uint32_t)0x0000000F)
#define ERTC_TSDT_DU_0                          ((uint32_t)0x00000001)
#define ERTC_TSDT_DU_1                          ((uint32_t)0x00000002)
#define ERTC_TSDT_DU_2                          ((uint32_t)0x00000004)
#define ERTC_TSDT_DU_3                          ((uint32_t)0x00000008)

/********************  Bits definition for ERTC_TSSBS register  ****************/
#define ERTC_TSSBS_SBS                          ((uint32_t)0x0000FFFF)

/********************  Bits definition for ERTC_CCR register  *****************/
#define ERTC_CCR_CALAD                          ((uint32_t)0x00008000)
#define ERTC_CCR_CAL8                           ((uint32_t)0x00004000)
#define ERTC_CCR_CAL16                          ((uint32_t)0x00002000)
#define ERTC_CCR_CALM                           ((uint32_t)0x000001FF)
#define ERTC_CCR_CALM_0                         ((uint32_t)0x00000001)
#define ERTC_CCR_CALM_1                         ((uint32_t)0x00000002)
#define ERTC_CCR_CALM_2                         ((uint32_t)0x00000004)
#define ERTC_CCR_CALM_3                         ((uint32_t)0x00000008)
#define ERTC_CCR_CALM_4                         ((uint32_t)0x00000010)
#define ERTC_CCR_CALM_5                         ((uint32_t)0x00000020)
#define ERTC_CCR_CALM_6                         ((uint32_t)0x00000040)
#define ERTC_CCR_CALM_7                         ((uint32_t)0x00000080)
#define ERTC_CCR_CALM_8                         ((uint32_t)0x00000100)

/********************  Bits definition for ERTC_TPAF register  ****************/
#define ERTC_TPAF_ALAOUTTYPE                    ((uint32_t)0x00040000)
#define ERTC_TPAF_TSINSEL                       ((uint32_t)0x00020000)
#define ERTC_TPAF_TMPINSEL                      ((uint32_t)0x00010000)
#define ERTC_TPAF_TMPUDIS                       ((uint32_t)0x00008000)
#define ERTC_TPAF_TMPRCH                        ((uint32_t)0x00006000)
#define ERTC_TPAF_TMPRCH_0                      ((uint32_t)0x00002000)
#define ERTC_TPAF_TMPRCH_1                      ((uint32_t)0x00004000)
#define ERTC_TPAF_TMFLT                         ((uint32_t)0x00001800)
#define ERTC_TPAF_TMFLT_0                       ((uint32_t)0x00000800)
#define ERTC_TPAF_TMFLT_1                       ((uint32_t)0x00001000)
#define ERTC_TPAF_TMFREQ                        ((uint32_t)0x00000700)
#define ERTC_TPAF_TMFREQ_0                      ((uint32_t)0x00000100)
#define ERTC_TPAF_TMFREQ_1                      ((uint32_t)0x00000200)
#define ERTC_TPAF_TMFREQ_2                      ((uint32_t)0x00000400)
#define ERTC_TPAF_TMTS                          ((uint32_t)0x00000080)
#define ERTC_TPAF_TM2TRG                        ((uint32_t)0x00000010)
#define ERTC_TPAF_TM2E                          ((uint32_t)0x00000008) 
#define ERTC_TPAF_TMIE                          ((uint32_t)0x00000004)
#define ERTC_TPAF_TM1TRG                        ((uint32_t)0x00000002)
#define ERTC_TPAF_TM1E                          ((uint32_t)0x00000001)

/********************  Bits definition for ERTC_ALASBS register  *************/
#define ERTC_ALASBS_MASKSBS                     ((uint32_t)0x0F000000)
#define ERTC_ALASBS_MASKSBS_0                   ((uint32_t)0x01000000)
#define ERTC_ALASBS_MASKSBS_1                   ((uint32_t)0x02000000)
#define ERTC_ALASBS_MASKSBS_2                   ((uint32_t)0x04000000)
#define ERTC_ALASBS_MASKSBS_3                   ((uint32_t)0x08000000)
#define ERTC_ALASBS_SBS                         ((uint32_t)0x00007FFF)

/********************  Bits definition for ERTC_ALBSBS register  *************/
#define ERTC_ALBSBS_MASKSBS                     ((uint32_t)0x0F000000)
#define ERTC_ALBSBS_MASKSBS_0                   ((uint32_t)0x01000000)
#define ERTC_ALBSBS_MASKSBS_1                   ((uint32_t)0x02000000)
#define ERTC_ALBSBS_MASKSBS_2                   ((uint32_t)0x04000000)
#define ERTC_ALBSBS_MASKSBS_3                   ((uint32_t)0x08000000)
#define ERTC_ALBSBS_SBS                         ((uint32_t)0x00007FFF)

/********************  Bits definition for ERTC_BKP0DT register  ****************/
#define ERTC_BKP0DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP1DT register  ****************/
#define ERTC_BKP1DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP2DT register  ****************/
#define ERTC_BKP2DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP3DT register  ****************/
#define ERTC_BKP3DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP4DT register  ****************/
#define ERTC_BKP4DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP5DT register  ****************/
#define ERTC_BKP5DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP6DT register  ****************/
#define ERTC_BKP6DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP7DT register  ****************/
#define ERTC_BKP7DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP8DT register  ****************/
#define ERTC_BKP8DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP9DT register  ****************/
#define ERTC_BKP9DT                             ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP10DT register  ***************/
#define ERTC_BKP10DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP11DT register  ***************/
#define ERTC_BKP11DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP12DT register  ***************/
#define ERTC_BKP12DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP13DT register  ***************/
#define ERTC_BKP13DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP14DT register  ***************/
#define ERTC_BKP14DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP15DT register  ***************/
#define ERTC_BKP15DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP16DT register  ***************/
#define ERTC_BKP16DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP17DT register  ***************/
#define ERTC_BKP17DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP18DT register  ***************/
#define ERTC_BKP18DT                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for ERTC_BKP19DT register  ***************/
#define ERTC_BKP19DT                            ((uint32_t)0xFFFFFFFF)

#else
/*******************  Bit definition for RTC_CTRLH register  ********************/
#define  RTC_CTRLH_PACEIEN                      ((uint8_t)0x01)               /*!< Second Interrupt Enable */
#define  RTC_CTRLH_ALAIEN                       ((uint8_t)0x02)               /*!< Alarm Interrupt Enable */
#define  RTC_CTRLH_OVIEN                        ((uint8_t)0x04)               /*!< OverfloW Interrupt Enable */

/*******************  Bit definition for RTC_CTRLL register  ********************/
#define  RTC_CTRLL_PACEF                        ((uint8_t)0x01)               /*!< Second Flag */
#define  RTC_CTRLL_ALAF                         ((uint8_t)0x02)               /*!< Alarm Flag */
#define  RTC_CTRLL_OVF                          ((uint8_t)0x04)               /*!< OverfloW Flag */
#define  RTC_CTRLL_RSYNF                        ((uint8_t)0x08)               /*!< Registers Synchronized Flag */
#define  RTC_CTRLL_CMF                          ((uint8_t)0x10)               /*!< Configuration Flag */
#define  RTC_CTRLL_RTF                          ((uint8_t)0x20)               /*!< RTC operation OFF */

/*******************  Bit definition for RTC_DIVH register  *******************/
#define  RTC_DIVH_DIV                           ((uint16_t)0x000F)            /*!< RTC Prescaler Reload Value High */

/*******************  Bit definition for RTC_DIVL register  *******************/
#define  RTC_DIVL_DIV                           ((uint16_t)0xFFFF)            /*!< RTC Prescaler Reload Value Low */

/*******************  Bit definition for RTC_DIVCNTH register  *******************/
#define  RTC_DIVCNTH_RTC_DIVCNT                 ((uint16_t)0x000F)            /*!< RTC Clock Divider High */

/*******************  Bit definition for RTC_DIVCNTL register  *******************/
#define  RTC_DIVCNTL_RTC_DIVCNT                 ((uint16_t)0xFFFF)            /*!< RTC Clock Divider Low */

/*******************  Bit definition for RTC_CNTH register  *******************/
#define  RTC_CNTH_CNT                           ((uint16_t)0xFFFF)            /*!< RTC Counter High */

/*******************  Bit definition for RTC_CNTL register  *******************/
#define  RTC_CNTL_CNT                           ((uint16_t)0xFFFF)            /*!< RTC Counter Low */

/*******************  Bit definition for RTC_ALAH register  *******************/
#define  RTC_ALAH_ALA                           ((uint16_t)0xFFFF)            /*!< RTC Alarm High */

/*******************  Bit definition for RTC_ALAL register  *******************/
#define  RTC_ALAL_ALA                           ((uint16_t)0xFFFF)            /*!< RTC Alarm Low */
#endif
/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for IWDG_KEY register  ********************/
#define  IWDG_KEY_KEY                           ((uint16_t)0xFFFF)            /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PSC register  ********************/
#define  IWDG_PSC_PSC                           ((uint8_t)0x07)               /*!< PR[2:0] (Prescaler divider) */
#define  IWDG_PSC_PSC_0                         ((uint8_t)0x01)               /*!< Bit 0 */
#define  IWDG_PSC_PSC_1                         ((uint8_t)0x02)               /*!< Bit 1 */
#define  IWDG_PSC_PSC_2                         ((uint8_t)0x04)               /*!< Bit 2 */

/*******************  Bit definition for IWDG_RLD register  *******************/
#define  IWDG_RLD_RLD                           ((uint16_t)0x0FFF)            /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_STS register  ********************/
#define  IWDG_STS_PSCF                          ((uint8_t)0x01)               /*!< Watchdog prescaler value update */
#define  IWDG_STS_RLDF                          ((uint8_t)0x02)               /*!< Watchdog counter reload value update */

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for WWDG_CTRL register  ********************/
#define  WWDG_CTRL_CNTR                         ((uint8_t)0x7F)               /*!< T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define  WWDG_CTRL_CNTR0                        ((uint8_t)0x01)               /*!< Bit 0 */
#define  WWDG_CTRL_CNTR1                        ((uint8_t)0x02)               /*!< Bit 1 */
#define  WWDG_CTRL_CNTR2                        ((uint8_t)0x04)               /*!< Bit 2 */
#define  WWDG_CTRL_CNTR3                        ((uint8_t)0x08)               /*!< Bit 3 */
#define  WWDG_CTRL_CNTR4                        ((uint8_t)0x10)               /*!< Bit 4 */
#define  WWDG_CTRL_CNTR5                        ((uint8_t)0x20)               /*!< Bit 5 */
#define  WWDG_CTRL_CNTR6                        ((uint8_t)0x40)               /*!< Bit 6 */

#define  WWDG_CTRL_EN                           ((uint8_t)0x80)               /*!< Activation bit */

/*******************  Bit definition for WWDG_CFG register  *******************/
#define  WWDG_CFG_WCNTR                         ((uint16_t)0x007F)            /*!< W[6:0] bits (7-bit window value) */
#define  WWDG_CFG_WCNTR0                        ((uint16_t)0x0001)            /*!< Bit 0 */
#define  WWDG_CFG_WCNTR1                        ((uint16_t)0x0002)            /*!< Bit 1 */
#define  WWDG_CFG_WCNTR2                        ((uint16_t)0x0004)            /*!< Bit 2 */
#define  WWDG_CFG_WCNTR3                        ((uint16_t)0x0008)            /*!< Bit 3 */
#define  WWDG_CFG_WCNTR4                        ((uint16_t)0x0010)            /*!< Bit 4 */
#define  WWDG_CFG_WCNTR5                        ((uint16_t)0x0020)            /*!< Bit 5 */
#define  WWDG_CFG_WCNTR6                        ((uint16_t)0x0040)            /*!< Bit 6 */

#define  WWDG_CFG_PSC                           ((uint16_t)0x0180)            /*!< WDGTB[1:0] bits (Timer Base) */
#define  WWDG_CFG_PSC0                          ((uint16_t)0x0080)            /*!< Bit 0 */
#define  WWDG_CFG_PSC1                          ((uint16_t)0x0100)            /*!< Bit 1 */

#define  WWDG_CFG_EWIEN                         ((uint16_t)0x0200)            /*!< Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_STS register  ********************/
#define  WWDG_STS_EWIF                          ((uint8_t)0x01)               /*!< Early Wakeup Interrupt Flag */

/******************************************************************************/
/*                                                                            */
/*                       eXternal Memory Controller                    		  */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for XMC_BK1CTRL1 register  *******************/
#define  XMC_BK1CTRL1_EN                        ((uint32_t)0x00000001)        /*!< Memory bank enable bit */
#define  XMC_BK1CTRL1_MUXEN                     ((uint32_t)0x00000002)        /*!< Address/data multiplexing enable bit */

#define  XMC_BK1CTRL1_DEV                       ((uint32_t)0x0000000C)        /*!< MTYP[1:0] bits (Memory type) */
#define  XMC_BK1CTRL1_DEV_0                     ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  XMC_BK1CTRL1_DEV_1                     ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  XMC_BK1CTRL1_BUSTYPE                   ((uint32_t)0x00000030)        /*!< MWID[1:0] bits (Memory data bus width) */
#define  XMC_BK1CTRL1_BUSTYPE_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1CTRL1_BUSTYPE_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK1CTRL1_NOREN                     ((uint32_t)0x00000040)        /*!< Flash access enable */
#define  XMC_BK1CTRL1_BURSTEN                   ((uint32_t)0x00000100)        /*!< Burst enable bit */
#define  XMC_BK1CTRL1_WAITALV                   ((uint32_t)0x00000200)        /*!< Wait signal polarity bit */
#define  XMC_BK1CTRL1_BRSTSPLTEN                ((uint32_t)0x00000400)        /*!< Wrapped burst mode support */
#define  XMC_BK1CTRL1_WAITCFG                   ((uint32_t)0x00000800)        /*!< Wait timing configuration */
#define  XMC_BK1CTRL1_WREN                      ((uint32_t)0x00001000)        /*!< Write enable bit */
#define  XMC_BK1CTRL1_WAITEN                    ((uint32_t)0x00002000)        /*!< Wait enable bit */
#define  XMC_BK1CTRL1_TMGWREN                   ((uint32_t)0x00004000)        /*!< Extended mode enable */
#define  XMC_BK1CTRL1_WAITASYNC                 ((uint32_t)0x00008000)       /*!< Asynchronous wait */
#define  XMC_BK1CTRL1_BURSTWRSYN                ((uint32_t)0x00080000)        /*!< Write burst enable */

/******************  Bit definition for XMC_BK1CTRL2 register  *******************/
#define  XMC_BK1CTRL2_EN                        ((uint32_t)0x00000001)        /*!< Memory bank enable bit */
#define  XMC_BK1CTRL2_MUXEN                     ((uint32_t)0x00000002)        /*!< Address/data multiplexing enable bit */

#define  XMC_BK1CTRL2_DEV                       ((uint32_t)0x0000000C)        /*!< MTYP[1:0] bits (Memory type) */
#define  XMC_BK1CTRL2_DEV_0                     ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  XMC_BK1CTRL2_DEV_1                     ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  XMC_BK1CTRL2_BUSTYPE                   ((uint32_t)0x00000030)        /*!< MWID[1:0] bits (Memory data bus width) */
#define  XMC_BK1CTRL2_BUSTYPE_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1CTRL2_BUSTYPE_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK1CTRL2_NOREN                     ((uint32_t)0x00000040)        /*!< Flash access enable */
#define  XMC_BK1CTRL2_BURSTEN                   ((uint32_t)0x00000100)        /*!< Burst enable bit */
#define  XMC_BK1CTRL2_WAITALV                   ((uint32_t)0x00000200)        /*!< Wait signal polarity bit */
#define  XMC_BK1CTRL2_BRSTSPLTEN                ((uint32_t)0x00000400)        /*!< Wrapped burst mode support */
#define  XMC_BK1CTRL2_WAITCFG                   ((uint32_t)0x00000800)        /*!< Wait timing configuration */
#define  XMC_BK1CTRL2_WREN                      ((uint32_t)0x00001000)        /*!< Write enable bit */
#define  XMC_BK1CTRL2_WAITEN                    ((uint32_t)0x00002000)        /*!< Wait enable bit */
#define  XMC_BK1CTRL2_TMGWREN                   ((uint32_t)0x00004000)        /*!< Extended mode enable */
#define  XMC_BK1CTRL2_WAITASYNC                 ((uint32_t)0x00008000)       /*!< Asynchronous wait */
#define  XMC_BK1CTRL2_BURSTWRSYN                ((uint32_t)0x00080000)        /*!< Write burst enable */

/******************  Bit definition for XMC_BK1CTRL3 register  *******************/
#define  XMC_BK1CTRL3_EN                        ((uint32_t)0x00000001)        /*!< Memory bank enable bit */
#define  XMC_BK1CTRL3_MUXEN                     ((uint32_t)0x00000002)        /*!< Address/data multiplexing enable bit */

#define  XMC_BK1CTRL3_DEV                       ((uint32_t)0x0000000C)        /*!< MTYP[1:0] bits (Memory type) */
#define  XMC_BK1CTRL3_DEV_0                     ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  XMC_BK1CTRL3_DEV_1                     ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  XMC_BK1CTRL3_BUSTYPE                   ((uint32_t)0x00000030)        /*!< MWID[1:0] bits (Memory data bus width) */
#define  XMC_BK1CTRL3_BUSTYPE_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1CTRL3_BUSTYPE_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK1CTRL3_NOREN                     ((uint32_t)0x00000040)        /*!< Flash access enable */
#define  XMC_BK1CTRL3_BURSTEN                   ((uint32_t)0x00000100)        /*!< Burst enable bit */
#define  XMC_BK1CTRL3_WAITALV                   ((uint32_t)0x00000200)        /*!< Wait signal polarity bit. */
#define  XMC_BK1CTRL3_BRSTSPLTEN                ((uint32_t)0x00000400)        /*!< Wrapped burst mode support */
#define  XMC_BK1CTRL3_WAITCFG                   ((uint32_t)0x00000800)        /*!< Wait timing configuration */
#define  XMC_BK1CTRL3_WREN                      ((uint32_t)0x00001000)        /*!< Write enable bit */
#define  XMC_BK1CTRL3_WAITEN                    ((uint32_t)0x00002000)        /*!< Wait enable bit */
#define  XMC_BK1CTRL3_TMGWREN                   ((uint32_t)0x00004000)        /*!< Extended mode enable */
#define  XMC_BK1CTRL3_WAITASYNC                 ((uint32_t)0x00008000)       /*!< Asynchronous wait */
#define  XMC_BK1CTRL3_BURSTWRSYN                ((uint32_t)0x00080000)        /*!< Write burst enable */

/******************  Bit definition for XMC_BK1CTRL4 register  *******************/
#define  XMC_BK1CTRL4_EN                        ((uint32_t)0x00000001)        /*!< Memory bank enable bit */
#define  XMC_BK1CTRL4_MUXEN                     ((uint32_t)0x00000002)        /*!< Address/data multiplexing enable bit */

#define  XMC_BK1CTRL4_DEV                       ((uint32_t)0x0000000C)        /*!< MTYP[1:0] bits (Memory type) */
#define  XMC_BK1CTRL4_DEV_0                     ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  XMC_BK1CTRL4_DEV_1                     ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  XMC_BK1CTRL4_BUSTYPE                   ((uint32_t)0x00000030)        /*!< MWID[1:0] bits (Memory data bus width) */
#define  XMC_BK1CTRL4_BUSTYPE_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1CTRL4_BUSTYPE_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK1CTRL4_NOREN                     ((uint32_t)0x00000040)        /*!< Flash access enable */
#define  XMC_BK1CTRL4_BURSTEN                   ((uint32_t)0x00000100)        /*!< Burst enable bit */
#define  XMC_BK1CTRL4_WAITALV                   ((uint32_t)0x00000200)        /*!< Wait signal polarity bit */
#define  XMC_BK1CTRL4_BRSTSPLTEN                ((uint32_t)0x00000400)        /*!< Wrapped burst mode support */
#define  XMC_BK1CTRL4_WAITCFG                   ((uint32_t)0x00000800)        /*!< Wait timing configuration */
#define  XMC_BK1CTRL4_WREN                      ((uint32_t)0x00001000)        /*!< Write enable bit */
#define  XMC_BK1CTRL4_WAITEN                    ((uint32_t)0x00002000)        /*!< Wait enable bit */
#define  XMC_BK1CTRL4_TMGWREN                   ((uint32_t)0x00004000)        /*!< Extended mode enable */
#define  XMC_BK1CTRL4_WAITASYNC                 ((uint32_t)0x00008000)       /*!< Asynchronous wait */
#define  XMC_BK1CTRL4_BURSTWRSYN                ((uint32_t)0x00080000)        /*!< Write burst enable */

/******************  Bit definition for XMC_BK1TMG1 register  ******************/
#define  XMC_BK1TMG1_ADROP                      ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMG1_ADROP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMG1_ADROP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMG1_ADROP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMG1_ADROP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMG1_ADRHLD                     ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMG1_ADRHLD_0                   ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMG1_ADRHLD_1                   ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMG1_ADRHLD_2                   ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMG1_ADRHLD_3                   ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMG1_DTOP                       ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMG1_DTOP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMG1_DTOP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMG1_DTOP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMG1_DTOP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMG1_INTVLOP                    ((uint32_t)0x000F0000)        /*!< BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define  XMC_BK1TMG1_INTVLOP_0                  ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK1TMG1_INTVLOP_1                  ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK1TMG1_INTVLOP_2                  ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK1TMG1_INTVLOP_3                  ((uint32_t)0x00080000)        /*!< Bit 3 */

#define  XMC_BK1TMG1_CLKPSC                     ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMG1_CLKPSC_0                   ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMG1_CLKPSC_1                   ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMG1_CLKPSC_2                   ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMG1_CLKPSC_3                   ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMG1_DTSTBL                     ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMG1_DTSTBL_0                   ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMG1_DTSTBL_1                   ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMG1_DTSTBL_2                   ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMG1_DTSTBL_3                   ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMG1_MODE                       ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMG1_MODE_0                     ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMG1_MODE_1                     ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK1TMG2 register  *******************/
#define  XMC_BK1TMG2_ADROP                      ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMG2_ADROP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMG2_ADROP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMG2_ADROP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMG2_ADROP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMG2_ADRHLD                     ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMG2_ADRHLD_0                   ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMG2_ADRHLD_1                   ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMG2_ADRHLD_2                   ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMG2_ADRHLD_3                   ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMG2_DTOP                       ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMG2_DTOP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMG2_DTOP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMG2_DTOP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMG2_DTOP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMG2_INTVLOP                    ((uint32_t)0x000F0000)        /*!< BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define  XMC_BK1TMG2_INTVLOP_0                  ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK1TMG2_INTVLOP_1                  ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK1TMG2_INTVLOP_2                  ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK1TMG2_INTVLOP_3                  ((uint32_t)0x00080000)        /*!< Bit 3 */

#define  XMC_BK1TMG2_CLKPSC                     ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMG2_CLKPSC_0                   ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMG2_CLKPSC_1                   ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMG2_CLKPSC_2                   ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMG2_CLKPSC_3                   ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMG2_DTSTBL                     ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMG2_DTSTBL_0                   ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMG2_DTSTBL_1                   ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMG2_DTSTBL_2                   ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMG2_DTSTBL_3                   ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMG2_MODE                       ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMG2_MODE_0                     ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMG2_MODE_1                     ((uint32_t)0x20000000)        /*!< Bit 1 */

/*******************  Bit definition for XMC_BK1TMG3 register  *******************/
#define  XMC_BK1TMG3_ADROP                      ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMG3_ADROP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMG3_ADROP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMG3_ADROP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMG3_ADROP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMG3_ADRHLD                     ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMG3_ADRHLD_0                   ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMG3_ADRHLD_1                   ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMG3_ADRHLD_2                   ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMG3_ADRHLD_3                   ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMG3_DTOP                       ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMG3_DTOP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMG3_DTOP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMG3_DTOP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMG3_DTOP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMG3_INTVLOP                    ((uint32_t)0x000F0000)        /*!< BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define  XMC_BK1TMG3_INTVLOP_0                  ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK1TMG3_INTVLOP_1                  ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK1TMG3_INTVLOP_2                  ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK1TMG3_INTVLOP_3                  ((uint32_t)0x00080000)        /*!< Bit 3 */

#define  XMC_BK1TMG3_CLKPSC                     ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMG3_CLKPSC_0                   ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMG3_CLKPSC_1                   ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMG3_CLKPSC_2                   ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMG3_CLKPSC_3                   ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMG3_DTSTBL                     ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMG3_DTSTBL_0                   ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMG3_DTSTBL_1                   ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMG3_DTSTBL_2                   ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMG3_DTSTBL_3                   ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMG3_MODE                       ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMG3_MODE_0                     ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMG3_MODE_1                     ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK1TMG4 register  *******************/
#define  XMC_BK1TMG4_ADROP                      ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMG4_ADROP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMG4_ADROP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMG4_ADROP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMG4_ADROP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMG4_ADRHLD                     ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMG4_ADRHLD_0                   ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMG4_ADRHLD_1                   ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMG4_ADRHLD_2                   ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMG4_ADRHLD_3                   ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMG4_DTOP                       ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMG4_DTOP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMG4_DTOP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMG4_DTOP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMG4_DTOP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMG4_INTVLOP                    ((uint32_t)0x000F0000)        /*!< BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define  XMC_BK1TMG4_INTVLOP_0                  ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK1TMG4_INTVLOP_1                  ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK1TMG4_INTVLOP_2                  ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK1TMG4_INTVLOP_3                  ((uint32_t)0x00080000)        /*!< Bit 3 */

#define  XMC_BK1TMG4_CLKPSC                     ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMG4_CLKPSC_0                   ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMG4_CLKPSC_1                   ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMG4_CLKPSC_2                   ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMG4_CLKPSC_3                   ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMG4_DTSTBL                     ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMG4_DTSTBL_0                   ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMG4_DTSTBL_1                   ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMG4_DTSTBL_2                   ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMG4_DTSTBL_3                   ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMG4_MODE                       ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMG4_MODE_0                     ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMG4_MODE_1                     ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK1TMGWR1 register  ******************/
#define  XMC_BK1TMGWR1_ADROP                    ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMGWR1_ADROP_0                  ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMGWR1_ADROP_1                  ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMGWR1_ADROP_2                  ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMGWR1_ADROP_3                  ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMGWR1_ADRHLD                   ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMGWR1_ADRHLD_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMGWR1_ADRHLD_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMGWR1_ADRHLD_2                 ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMGWR1_ADRHLD_3                 ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMGWR1_DTOP                     ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMGWR1_DTOP_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMGWR1_DTOP_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMGWR1_DTOP_2                   ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMGWR1_DTOP_3                   ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMGWR1_CLKPSC                   ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMGWR1_CLKPSC_0                 ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR1_CLKPSC_1                 ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR1_CLKPSC_2                 ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR1_CLKPSC_3                 ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR1_DTSTBL                   ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMGWR1_DTSTBL_0                 ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR1_DTSTBL_1                 ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR1_DTSTBL_2                 ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR1_DTSTBL_3                 ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR1_MODE                     ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMGWR1_MODE_0                   ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR1_MODE_1                   ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK1TMGWR2 register  ******************/
#define  XMC_BK1TMGWR2_ADROP                    ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMGWR2_ADROP_0                  ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMGWR2_ADROP_1                  ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMGWR2_ADROP_2                  ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMGWR2_ADROP_3                  ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMGWR2_ADRHLD                   ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMGWR2_ADRHLD_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMGWR2_ADRHLD_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMGWR2_ADRHLD_2                 ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMGWR2_ADRHLD_3                 ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMGWR2_DTOP                     ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMGWR2_DTOP_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMGWR2_DTOP_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMGWR2_DTOP_2                   ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMGWR2_DTOP_3                   ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMGWR2_CLKPSC                   ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMGWR2_CLKPSC_0                 ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR2_CLKPSC_1                 ((uint32_t)0x00200000)        /*!< Bit 1*/
#define  XMC_BK1TMGWR2_CLKPSC_2                 ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR2_CLKPSC_3                 ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR2_DTSTBL                   ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMGWR2_DTSTBL_0                 ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR2_DTSTBL_1                 ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR2_DTSTBL_2                 ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR2_DTSTBL_3                 ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR2_MODE                     ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMGWR2_MODE_0                   ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR2_MODE_1                   ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK1TMGWR3 register  ******************/
#define  XMC_BK1TMGWR3_ADROP                    ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMGWR3_ADROP_0                  ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMGWR3_ADROP_1                  ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMGWR3_ADROP_2                  ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMGWR3_ADROP_3                  ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMGWR3_ADRHLD                   ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMGWR3_ADRHLD_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMGWR3_ADRHLD_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMGWR3_ADRHLD_2                 ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMGWR3_ADRHLD_3                 ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMGWR3_DTOP                     ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMGWR3_DTOP_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMGWR3_DTOP_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMGWR3_DTOP_2                   ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMGWR3_DTOP_3                   ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMGWR3_CLKPSC                   ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMGWR3_CLKPSC_0                 ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR3_CLKPSC_1                 ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR3_CLKPSC_2                 ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR3_CLKPSC_3                 ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR3_DTSTBL                   ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMGWR3_DTSTBL_0                 ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR3_DTSTBL_1                 ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR3_DTSTBL_2                 ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR3_DTSTBL_3                 ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR3_MODE                     ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMGWR3_MODE_0                   ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR3_MODE_1                   ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK1TMGWR4 register  ******************/
#define  XMC_BK1TMGWR4_ADROP                    ((uint32_t)0x0000000F)        /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define  XMC_BK1TMGWR4_ADROP_0                  ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK1TMGWR4_ADROP_1                  ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK1TMGWR4_ADROP_2                  ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK1TMGWR4_ADROP_3                  ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  XMC_BK1TMGWR4_ADRHLD                   ((uint32_t)0x000000F0)        /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define  XMC_BK1TMGWR4_ADRHLD_0                 ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK1TMGWR4_ADRHLD_1                 ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  XMC_BK1TMGWR4_ADRHLD_2                 ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  XMC_BK1TMGWR4_ADRHLD_3                 ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  XMC_BK1TMGWR4_DTOP                     ((uint32_t)0x0000FF00)        /*!< DATAST [3:0] bits (Data-phase duration) */
#define  XMC_BK1TMGWR4_DTOP_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK1TMGWR4_DTOP_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK1TMGWR4_DTOP_2                   ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK1TMGWR4_DTOP_3                   ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  XMC_BK1TMGWR4_CLKPSC                   ((uint32_t)0x00F00000)        /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define  XMC_BK1TMGWR4_CLKPSC_0                 ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR4_CLKPSC_1                 ((uint32_t)0x00200000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR4_CLKPSC_2                 ((uint32_t)0x00400000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR4_CLKPSC_3                 ((uint32_t)0x00800000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR4_DTSTBL                   ((uint32_t)0x0F000000)        /*!< DATLA[3:0] bits (Data latency) */
#define  XMC_BK1TMGWR4_DTSTBL_0                 ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR4_DTSTBL_1                 ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK1TMGWR4_DTSTBL_2                 ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK1TMGWR4_DTSTBL_3                 ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  XMC_BK1TMGWR4_MODE                     ((uint32_t)0x30000000)        /*!< ACCMOD[1:0] bits (Access mode) */
#define  XMC_BK1TMGWR4_MODE_0                   ((uint32_t)0x10000000)        /*!< Bit 0 */
#define  XMC_BK1TMGWR4_MODE_1                   ((uint32_t)0x20000000)        /*!< Bit 1 */

/******************  Bit definition for XMC_BK2CTRL register  *******************/
#define  XMC_BK2CTRL_WAITEN                     ((uint32_t)0x00000002)        /*!< Wait feature enable bit */
#define  XMC_BK2CTRL_EN                         ((uint32_t)0x00000004)        /*!< PC Card/NAND Flash memory bank enable bit */
#define  XMC_BK2CTRL_DEV                        ((uint32_t)0x00000008)        /*!< Memory type */

#define  XMC_BK2CTRL_BUSTYPE                    ((uint32_t)0x00000030)        /*!< PWID[1:0] bits (NAND Flash databus width) */
#define  XMC_BK2CTRL_BUSTYPE_0                  ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK2CTRL_BUSTYPE_1                  ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK2CTRL_ECCEN                      ((uint32_t)0x00000040)        /*!< ECC computation logic enable bit */

#define  XMC_BK2CTRL_DLYCR                      ((uint32_t)0x00001E00)        /*!< TCLR[3:0] bits (CLE to RE delay) */
#define  XMC_BK2CTRL_DLYCR_0                    ((uint32_t)0x00000200)        /*!< Bit 0 */
#define  XMC_BK2CTRL_DLYCR_1                    ((uint32_t)0x00000400)        /*!< Bit 1 */
#define  XMC_BK2CTRL_DLYCR_2                    ((uint32_t)0x00000800)        /*!< Bit 2 */
#define  XMC_BK2CTRL_DLYCR_3                    ((uint32_t)0x00001000)        /*!< Bit 3 */

#define  XMC_BK2CTRL_DLYAR                      ((uint32_t)0x0001E000)        /*!< TAR[3:0] bits (ALE to RE delay) */
#define  XMC_BK2CTRL_DLYAR_0                    ((uint32_t)0x00002000)        /*!< Bit 0 */
#define  XMC_BK2CTRL_DLYAR_1                    ((uint32_t)0x00004000)        /*!< Bit 1 */
#define  XMC_BK2CTRL_DLYAR_2                    ((uint32_t)0x00008000)        /*!< Bit 2 */
#define  XMC_BK2CTRL_DLYAR_3                    ((uint32_t)0x00010000)        /*!< Bit 3 */

#define  XMC_BK2CTRL_ECCPGSIZE                  ((uint32_t)0x000E0000)        /*!< ECCPS[1:0] bits (ECC page size) */
#define  XMC_BK2CTRL_ECCPGSIZE_0                ((uint32_t)0x00020000)        /*!< Bit 0 */
#define  XMC_BK2CTRL_ECCPGSIZE_1                ((uint32_t)0x00040000)        /*!< Bit 1 */
#define  XMC_BK2CTRL_ECCPGSIZE_2                ((uint32_t)0x00080000)        /*!< Bit 2 */

/******************  Bit definition for XMC_BK3CTRL register  *******************/
#define  XMC_BK3CTRL_WAITEN                     ((uint32_t)0x00000002)        /*!< Wait feature enable bit */
#define  XMC_BK3CTRL_EN                         ((uint32_t)0x00000004)        /*!< PC Card/NAND Flash memory bank enable bit */
#define  XMC_BK3CTRL_DEV                        ((uint32_t)0x00000008)        /*!< Memory type */

#define  XMC_BK3CTRL_BUSTYPE                    ((uint32_t)0x00000030)        /*!< PWID[1:0] bits (NAND Flash databus width) */
#define  XMC_BK3CTRL_BUSTYPE_0                  ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK3CTRL_BUSTYPE_1                  ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK3CTRL_ECCEN                      ((uint32_t)0x00000040)        /*!< ECC computation logic enable bit */

#define  XMC_BK3CTRL_DLYCR                      ((uint32_t)0x00001E00)        /*!< TCLR[3:0] bits (CLE to RE delay) */
#define  XMC_BK3CTRL_DLYCR_0                    ((uint32_t)0x00000200)        /*!< Bit 0 */
#define  XMC_BK3CTRL_DLYCR_1                    ((uint32_t)0x00000400)        /*!< Bit 1 */
#define  XMC_BK3CTRL_DLYCR_2                    ((uint32_t)0x00000800)        /*!< Bit 2 */
#define  XMC_BK3CTRL_DLYCR_3                    ((uint32_t)0x00001000)        /*!< Bit 3 */

#define  XMC_BK3CTRL_DLYAR                      ((uint32_t)0x0001E000)        /*!< TAR[3:0] bits (ALE to RE delay) */
#define  XMC_BK3CTRL_DLYAR_0                    ((uint32_t)0x00002000)        /*!< Bit 0 */
#define  XMC_BK3CTRL_DLYAR_1                    ((uint32_t)0x00004000)        /*!< Bit 1 */
#define  XMC_BK3CTRL_DLYAR_2                    ((uint32_t)0x00008000)        /*!< Bit 2 */
#define  XMC_BK3CTRL_DLYAR_3                    ((uint32_t)0x00010000)        /*!< Bit 3 */

#define  XMC_BK3CTRL_ECCPGSIZE                  ((uint32_t)0x000E0000)        /*!< ECCPS[2:0] bits (ECC page size) */
#define  XMC_BK3CTRL_ECCPGSIZE_0                ((uint32_t)0x00020000)        /*!< Bit 0 */
#define  XMC_BK3CTRL_ECCPGSIZE_1                ((uint32_t)0x00040000)        /*!< Bit 1 */
#define  XMC_BK3CTRL_ECCPGSIZE_2                ((uint32_t)0x00080000)        /*!< Bit 2 */

/******************  Bit definition for XMC_BK4CTRL register  *******************/
#define  XMC_BK4CTRL_WAITEN                     ((uint32_t)0x00000002)        /*!< Wait feature enable bit */
#define  XMC_BK4CTRL_EN                         ((uint32_t)0x00000004)        /*!< PC Card/NAND Flash memory bank enable bit */
#define  XMC_BK4CTRL_DEV                        ((uint32_t)0x00000008)        /*!< Memory type */

#define  XMC_BK4CTRL_BUSTYPE                    ((uint32_t)0x00000030)        /*!< PWID[1:0] bits (NAND Flash databus width) */
#define  XMC_BK4CTRL_BUSTYPE_0                  ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  XMC_BK4CTRL_BUSTYPE_1                  ((uint32_t)0x00000020)        /*!< Bit 1 */

#define  XMC_BK4CTRL_ECCEN                      ((uint32_t)0x00000040)        /*!< ECC computation logic enable bit */

#define  XMC_BK4CTRL_DLYCR                      ((uint32_t)0x00001E00)        /*!< TCLR[3:0] bits (CLE to RE delay) */
#define  XMC_BK4CTRL_DLYCR_0                    ((uint32_t)0x00000200)        /*!< Bit 0 */
#define  XMC_BK4CTRL_DLYCR_1                    ((uint32_t)0x00000400)        /*!< Bit 1 */
#define  XMC_BK4CTRL_DLYCR_2                    ((uint32_t)0x00000800)        /*!< Bit 2 */
#define  XMC_BK4CTRL_DLYCR_3                    ((uint32_t)0x00001000)        /*!< Bit 3 */

#define  XMC_BK4CTRL_DLYAR                      ((uint32_t)0x0001E000)        /*!< TAR[3:0] bits (ALE to RE delay) */
#define  XMC_BK4CTRL_DLYAR_0                    ((uint32_t)0x00002000)        /*!< Bit 0 */
#define  XMC_BK4CTRL_DLYAR_1                    ((uint32_t)0x00004000)        /*!< Bit 1 */
#define  XMC_BK4CTRL_DLYAR_2                    ((uint32_t)0x00008000)        /*!< Bit 2 */
#define  XMC_BK4CTRL_DLYAR_3                    ((uint32_t)0x00010000)        /*!< Bit 3 */

#define  XMC_BK4CTRL_ECCPGSIZE                  ((uint32_t)0x000E0000)        /*!< ECCPS[2:0] bits (ECC page size) */
#define  XMC_BK4CTRL_ECCPGSIZE_0                ((uint32_t)0x00020000)        /*!< Bit 0 */
#define  XMC_BK4CTRL_ECCPGSIZE_1                ((uint32_t)0x00040000)        /*!< Bit 1 */
#define  XMC_BK4CTRL_ECCPGSIZE_2                ((uint32_t)0x00080000)        /*!< Bit 2 */

/*******************  Bit definition for XMC_BK2STS register  *******************/
#define  XMC_BK2STS_IRF                         ((uint8_t)0x01)               /*!< Interrupt Rising Edge status */
#define  XMC_BK2STS_IHLF                        ((uint8_t)0x02)               /*!< Interrupt Level status */
#define  XMC_BK2STS_IFF                         ((uint8_t)0x04)               /*!< Interrupt Falling Edge status */
#define  XMC_BK2STS_IREN                        ((uint8_t)0x08)               /*!< Interrupt Rising Edge detection Enable bit */
#define  XMC_BK2STS_IHLEN                       ((uint8_t)0x10)               /*!< Interrupt Level detection Enable bit */
#define  XMC_BK2STS_IFEN                        ((uint8_t)0x20)               /*!< Interrupt Falling Edge detection Enable bit */
#define  XMC_BK2STS_FIFOE                       ((uint8_t)0x40)               /*!< FIFO empty */

/*******************  Bit definition for XMC_BK3STS register  *******************/
#define  XMC_BK3STS_IRF                         ((uint8_t)0x01)               /*!< Interrupt Rising Edge status */
#define  XMC_BK3STS_IHLF                        ((uint8_t)0x02)               /*!< Interrupt Level status */
#define  XMC_BK3STS_IFF                         ((uint8_t)0x04)               /*!< Interrupt Falling Edge status */
#define  XMC_BK3STS_IREN                        ((uint8_t)0x08)               /*!< Interrupt Rising Edge detection Enable bit */
#define  XMC_BK3STS_IHLEN                       ((uint8_t)0x10)               /*!< Interrupt Level detection Enable bit */
#define  XMC_BK3STS_IFEN                        ((uint8_t)0x20)               /*!< Interrupt Falling Edge detection Enable bit */
#define  XMC_BK3STS_FIFOE                       ((uint8_t)0x40)               /*!< FIFO empty */

/*******************  Bit definition for XMC_BK4STS register  *******************/
#define  XMC_BK4STS_IRF                         ((uint8_t)0x01)               /*!< Interrupt Rising Edge status */
#define  XMC_BK4STS_IHLF                        ((uint8_t)0x02)               /*!< Interrupt Level status */
#define  XMC_BK4STS_IFF                         ((uint8_t)0x04)               /*!< Interrupt Falling Edge status */
#define  XMC_BK4STS_IREN                        ((uint8_t)0x08)               /*!< Interrupt Rising Edge detection Enable bit */
#define  XMC_BK4STS_IHLEN                       ((uint8_t)0x10)               /*!< Interrupt Level detection Enable bit */
#define  XMC_BK4STS_IFEN                        ((uint8_t)0x20)               /*!< Interrupt Falling Edge detection Enable bit */
#define  XMC_BK4STS_FIFOE                       ((uint8_t)0x40)               /*!< FIFO empty */

/******************  Bit definition for XMC_BK2TMGMEM register  ******************/
#define  XMC_BK2TMGMEM_STP                      ((uint32_t)0x000000FF)        /*!< MEMSET2[7:0] bits (Common memory 2 setup time) */
#define  XMC_BK2TMGMEM_STP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK2TMGMEM_STP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK2TMGMEM_STP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK2TMGMEM_STP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK2TMGMEM_STP_4                    ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK2TMGMEM_STP_5                    ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK2TMGMEM_STP_6                    ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK2TMGMEM_STP_7                    ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK2TMGMEM_OP                       ((uint32_t)0x0000FF00)        /*!< MEMWAIT2[7:0] bits (Common memory 2 wait time) */
#define  XMC_BK2TMGMEM_OP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK2TMGMEM_OP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK2TMGMEM_OP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK2TMGMEM_OP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK2TMGMEM_OP_4                     ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK2TMGMEM_OP_5                     ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK2TMGMEM_OP_6                     ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK2TMGMEM_OP_7                     ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK2TMGMEM_HLD                      ((uint32_t)0x00FF0000)        /*!< MEMHOLD2[7:0] bits (Common memory 2 hold time) */
#define  XMC_BK2TMGMEM_HLD_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK2TMGMEM_HLD_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK2TMGMEM_HLD_2                    ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK2TMGMEM_HLD_3                    ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK2TMGMEM_HLD_4                    ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK2TMGMEM_HLD_5                    ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK2TMGMEM_HLD_6                    ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK2TMGMEM_HLD_7                    ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK2TMGMEM_WRSTP                    ((uint32_t)0xFF000000)        /*!< MEMHIZ2[7:0] bits (Common memory 2 databus HiZ time) */
#define  XMC_BK2TMGMEM_WRSTP_0                  ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK2TMGMEM_WRSTP_1                  ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK2TMGMEM_WRSTP_2                  ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK2TMGMEM_WRSTP_3                  ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK2TMGMEM_WRSTP_4                  ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK2TMGMEM_WRSTP_5                  ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK2TMGMEM_WRSTP_6                  ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK2TMGMEM_WRSTP_7                  ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK3TMGMEM register  ******************/
#define  XMC_BK3TMGMEM_STP                      ((uint32_t)0x000000FF)        /*!< MEMSET3[7:0] bits (Common memory 3 setup time) */
#define  XMC_BK3TMGMEM_STP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK3TMGMEM_STP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK3TMGMEM_STP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK3TMGMEM_STP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK3TMGMEM_STP_4                    ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK3TMGMEM_STP_5                    ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK3TMGMEM_STP_6                    ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK3TMGMEM_STP_7                    ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK3TMGMEM_OP                       ((uint32_t)0x0000FF00)        /*!< MEMWAIT3[7:0] bits (Common memory 3 wait time) */
#define  XMC_BK3TMGMEM_OP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK3TMGMEM_OP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK3TMGMEM_OP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK3TMGMEM_OP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK3TMGMEM_OP_4                     ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK3TMGMEM_OP_5                     ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK3TMGMEM_OP_6                     ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK3TMGMEM_OP_7                     ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK3TMGMEM_HLD                      ((uint32_t)0x00FF0000)        /*!< MEMHOLD3[7:0] bits (Common memory 3 hold time) */
#define  XMC_BK3TMGMEM_HLD_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK3TMGMEM_HLD_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK3TMGMEM_HLD_2                    ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK3TMGMEM_HLD_3                    ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK3TMGMEM_HLD_4                    ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK3TMGMEM_HLD_5                    ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK3TMGMEM_HLD_6                    ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK3TMGMEM_HLD_7                    ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK3TMGMEM_WRSTP                    ((uint32_t)0xFF000000)        /*!< MEMHIZ3[7:0] bits (Common memory 3 databus HiZ time) */
#define  XMC_BK3TMGMEM_WRSTP_0                  ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK3TMGMEM_WRSTP_1                  ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK3TMGMEM_WRSTP_2                  ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK3TMGMEM_WRSTP_3                  ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK3TMGMEM_WRSTP_4                  ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK3TMGMEM_WRSTP_5                  ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK3TMGMEM_WRSTP_6                  ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK3TMGMEM_WRSTP_7                  ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK4TMGMEM register  ******************/
#define  XMC_BK4TMGMEM_STP                      ((uint32_t)0x000000FF)        /*!< MEMSET4[7:0] bits (Common memory 4 setup time) */
#define  XMC_BK4TMGMEM_STP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK4TMGMEM_STP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK4TMGMEM_STP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK4TMGMEM_STP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK4TMGMEM_STP_4                    ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK4TMGMEM_STP_5                    ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK4TMGMEM_STP_6                    ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK4TMGMEM_STP_7                    ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK4TMGMEM_OP                       ((uint32_t)0x0000FF00)        /*!< MEMWAIT4[7:0] bits (Common memory 4 wait time) */
#define  XMC_BK4TMGMEM_OP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK4TMGMEM_OP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK4TMGMEM_OP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK4TMGMEM_OP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK4TMGMEM_OP_4                     ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK4TMGMEM_OP_5                     ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK4TMGMEM_OP_6                     ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK4TMGMEM_OP_7                     ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK4TMGMEM_HLD                      ((uint32_t)0x00FF0000)        /*!< MEMHOLD4[7:0] bits (Common memory 4 hold time) */
#define  XMC_BK4TMGMEM_HLD_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK4TMGMEM_HLD_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK4TMGMEM_HLD_2                    ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK4TMGMEM_HLD_3                    ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK4TMGMEM_HLD_4                    ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK4TMGMEM_HLD_5                    ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK4TMGMEM_HLD_6                    ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK4TMGMEM_HLD_7                    ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK4TMGMEM_WRSTP                    ((uint32_t)0xFF000000)        /*!< MEMHIZ4[7:0] bits (Common memory 4 databus HiZ time) */
#define  XMC_BK4TMGMEM_WRSTP_0                  ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK4TMGMEM_WRSTP_1                  ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK4TMGMEM_WRSTP_2                  ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK4TMGMEM_WRSTP_3                  ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK4TMGMEM_WRSTP_4                  ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK4TMGMEM_WRSTP_5                  ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK4TMGMEM_WRSTP_6                  ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK4TMGMEM_WRSTP_7                  ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK2TMGATT register  ******************/
#define  XMC_BK2TMGATT_STP                      ((uint32_t)0x000000FF)        /*!< ATTSET2[7:0] bits (Attribute memory 2 setup time) */
#define  XMC_BK2TMGATT_STP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK2TMGATT_STP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK2TMGATT_STP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK2TMGATT_STP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK2TMGATT_STP_4                    ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK2TMGATT_STP_5                    ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK2TMGATT_STP_6                    ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK2TMGATT_STP_7                    ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK2TMGATT_OP                       ((uint32_t)0x0000FF00)        /*!< ATTWAIT2[7:0] bits (Attribute memory 2 wait time) */
#define  XMC_BK2TMGATT_OP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK2TMGATT_OP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK2TMGATT_OP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK2TMGATT_OP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK2TMGATT_OP_4                     ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK2TMGATT_OP_5                     ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK2TMGATT_OP_6                     ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK2TMGATT_OP_7                     ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK2TMGATT_HLD                      ((uint32_t)0x00FF0000)        /*!< ATTHOLD2[7:0] bits (Attribute memory 2 hold time) */
#define  XMC_BK2TMGATT_HLD_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK2TMGATT_HLD_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK2TMGATT_HLD_2                    ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK2TMGATT_HLD_3                    ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK2TMGATT_HLD_4                    ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK2TMGATT_HLD_5                    ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK2TMGATT_HLD_6                    ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK2TMGATT_HLD_7                    ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK2TMGATT_WRSTP                    ((uint32_t)0xFF000000)        /*!< ATTHIZ2[7:0] bits (Attribute memory 2 databus HiZ time) */
#define  XMC_BK2TMGATT_WRSTP_0                  ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK2TMGATT_WRSTP_1                  ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK2TMGATT_WRSTP_2                  ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK2TMGATT_WRSTP_3                  ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK2TMGATT_WRSTP_4                  ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK2TMGATT_WRSTP_5                  ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK2TMGATT_WRSTP_6                  ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK2TMGATT_WRSTP_7                  ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK3TMGATT register  ******************/
#define  XMC_BK3TMGATT_STP                      ((uint32_t)0x000000FF)        /*!< ATTSET3[7:0] bits (Attribute memory 3 setup time) */
#define  XMC_BK3TMGATT_STP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK3TMGATT_STP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK3TMGATT_STP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK3TMGATT_STP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK3TMGATT_STP_4                    ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK3TMGATT_STP_5                    ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK3TMGATT_STP_6                    ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK3TMGATT_STP_7                    ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK3TMGATT_OP                       ((uint32_t)0x0000FF00)        /*!< ATTWAIT3[7:0] bits (Attribute memory 3 wait time) */
#define  XMC_BK3TMGATT_OP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK3TMGATT_OP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK3TMGATT_OP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK3TMGATT_OP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK3TMGATT_OP_4                     ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK3TMGATT_OP_5                     ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK3TMGATT_OP_6                     ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK3TMGATT_OP_7                     ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK3TMGATT_HLD                      ((uint32_t)0x00FF0000)        /*!< ATTHOLD3[7:0] bits (Attribute memory 3 hold time) */
#define  XMC_BK3TMGATT_HLD_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK3TMGATT_HLD_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK3TMGATT_HLD_2                    ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK3TMGATT_HLD_3                    ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK3TMGATT_HLD_4                    ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK3TMGATT_HLD_5                    ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK3TMGATT_HLD_6                    ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK3TMGATT_HLD_7                    ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK3TMGATT_WRSTP                    ((uint32_t)0xFF000000)        /*!< ATTHIZ3[7:0] bits (Attribute memory 3 databus HiZ time) */
#define  XMC_BK3TMGATT_WRSTP_0                  ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK3TMGATT_WRSTP_1                  ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK3TMGATT_WRSTP_2                  ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK3TMGATT_WRSTP_3                  ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK3TMGATT_WRSTP_4                  ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK3TMGATT_WRSTP_5                  ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK3TMGATT_WRSTP_6                  ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK3TMGATT_WRSTP_7                  ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK4TMGATT register  ******************/
#define  XMC_BK4TMGATT_STP                      ((uint32_t)0x000000FF)        /*!< ATTSET4[7:0] bits (Attribute memory 4 setup time) */
#define  XMC_BK4TMGATT_STP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK4TMGATT_STP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK4TMGATT_STP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK4TMGATT_STP_3                    ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK4TMGATT_STP_4                    ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK4TMGATT_STP_5                    ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK4TMGATT_STP_6                    ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK4TMGATT_STP_7                    ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK4TMGATT_OP                       ((uint32_t)0x0000FF00)        /*!< ATTWAIT4[7:0] bits (Attribute memory 4 wait time) */
#define  XMC_BK4TMGATT_OP_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK4TMGATT_OP_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK4TMGATT_OP_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK4TMGATT_OP_3                     ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK4TMGATT_OP_4                     ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK4TMGATT_OP_5                     ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK4TMGATT_OP_6                     ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK4TMGATT_OP_7                     ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK4TMGATT_HLD                      ((uint32_t)0x00FF0000)        /*!< ATTHOLD4[7:0] bits (Attribute memory 4 hold time) */
#define  XMC_BK4TMGATT_HLD_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK4TMGATT_HLD_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK4TMGATT_HLD_2                    ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK4TMGATT_HLD_3                    ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK4TMGATT_HLD_4                    ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK4TMGATT_HLD_5                    ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK4TMGATT_HLD_6                    ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK4TMGATT_HLD_7                    ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK4TMGATT_WRSTP                    ((uint32_t)0xFF000000)        /*!< ATTHIZ4[7:0] bits (Attribute memory 4 databus HiZ time) */
#define  XMC_BK4TMGATT_WRSTP_0                  ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK4TMGATT_WRSTP_1                  ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK4TMGATT_WRSTP_2                  ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK4TMGATT_WRSTP_3                  ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK4TMGATT_WRSTP_4                  ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK4TMGATT_WRSTP_5                  ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK4TMGATT_WRSTP_6                  ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK4TMGATT_WRSTP_7                  ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK4TMGIO register  *******************/
#define  XMC_BK4TMGIO_STP                       ((uint32_t)0x000000FF)        /*!< IOSET4[7:0] bits (I/O 4 setup time) */
#define  XMC_BK4TMGIO_STP_0                     ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  XMC_BK4TMGIO_STP_1                     ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  XMC_BK4TMGIO_STP_2                     ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  XMC_BK4TMGIO_STP_3                     ((uint32_t)0x00000008)        /*!< Bit 3 */
#define  XMC_BK4TMGIO_STP_4                     ((uint32_t)0x00000010)        /*!< Bit 4 */
#define  XMC_BK4TMGIO_STP_5                     ((uint32_t)0x00000020)        /*!< Bit 5 */
#define  XMC_BK4TMGIO_STP_6                     ((uint32_t)0x00000040)        /*!< Bit 6 */
#define  XMC_BK4TMGIO_STP_7                     ((uint32_t)0x00000080)        /*!< Bit 7 */

#define  XMC_BK4TMGIO_OP                        ((uint32_t)0x0000FF00)        /*!< IOWAIT4[7:0] bits (I/O 4 wait time) */
#define  XMC_BK4TMGIO_OP_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  XMC_BK4TMGIO_OP_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  XMC_BK4TMGIO_OP_2                      ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  XMC_BK4TMGIO_OP_3                      ((uint32_t)0x00000800)        /*!< Bit 3 */
#define  XMC_BK4TMGIO_OP_4                      ((uint32_t)0x00001000)        /*!< Bit 4 */
#define  XMC_BK4TMGIO_OP_5                      ((uint32_t)0x00002000)        /*!< Bit 5 */
#define  XMC_BK4TMGIO_OP_6                      ((uint32_t)0x00004000)        /*!< Bit 6 */
#define  XMC_BK4TMGIO_OP_7                      ((uint32_t)0x00008000)        /*!< Bit 7 */

#define  XMC_BK4TMGIO_HLD                       ((uint32_t)0x00FF0000)        /*!< IOHOLD4[7:0] bits (I/O 4 hold time) */
#define  XMC_BK4TMGIO_HLD_0                     ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  XMC_BK4TMGIO_HLD_1                     ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  XMC_BK4TMGIO_HLD_2                     ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  XMC_BK4TMGIO_HLD_3                     ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  XMC_BK4TMGIO_HLD_4                     ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  XMC_BK4TMGIO_HLD_5                     ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  XMC_BK4TMGIO_HLD_6                     ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  XMC_BK4TMGIO_HLD_7                     ((uint32_t)0x00800000)        /*!< Bit 7 */

#define  XMC_BK4TMGIO_WRSTP                     ((uint32_t)0xFF000000)        /*!< IOHIZ4[7:0] bits (I/O 4 databus HiZ time) */
#define  XMC_BK4TMGIO_WRSTP_0                   ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  XMC_BK4TMGIO_WRSTP_1                   ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  XMC_BK4TMGIO_WRSTP_2                   ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  XMC_BK4TMGIO_WRSTP_3                   ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  XMC_BK4TMGIO_WRSTP_4                   ((uint32_t)0x10000000)        /*!< Bit 4 */
#define  XMC_BK4TMGIO_WRSTP_5                   ((uint32_t)0x20000000)        /*!< Bit 5 */
#define  XMC_BK4TMGIO_WRSTP_6                   ((uint32_t)0x40000000)        /*!< Bit 6 */
#define  XMC_BK4TMGIO_WRSTP_7                   ((uint32_t)0x80000000)        /*!< Bit 7 */

/******************  Bit definition for XMC_BK2ECC register  ******************/
#define  XMC_BK2ECC_ECC                         ((uint32_t)0xFFFFFFFF)        /*!< ECC result */

/******************  Bit definition for XMC_BK3ECC register  ******************/
#define  XMC_BK3ECC_ECC                         ((uint32_t)0xFFFFFFFF)        /*!< ECC result */

/******************************************************************************/
/*                                                                            */
/*                          SD host Interface                                 */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for SDIO_POWER register  ******************/
#define  SDIO_POWER_PWRCTRL                     ((uint8_t)0x03)               /*!< PWRCTRL[1:0] bits (Power supply control bits) */
#define  SDIO_POWER_PWRCTRL_0                   ((uint8_t)0x01)               /*!< Bit 0 */
#define  SDIO_POWER_PWRCTRL_1                   ((uint8_t)0x02)               /*!< Bit 1 */

/******************  Bit definition for SDIO_CLKCTRL register  ******************/
#define  SDIO_CLKCTRL_CLKPSC                    ((uint16_t)0x00FF)            /*!< Clock divide factor */
#define  SDIO_CLKCTRL_CLKEN                     ((uint16_t)0x0100)            /*!< Clock enable bit */
#define  SDIO_CLKCTRL_PWRSVG                    ((uint16_t)0x0200)            /*!< Power saving configuration bit */
#define  SDIO_CLKCTRL_BYPS                      ((uint16_t)0x0400)            /*!< Clock divider bypass enable bit */

#define  SDIO_CLKCTRL_BUSWIDTH                  ((uint16_t)0x1800)            /*!< WIDBUS[1:0] bits (Wide bus mode enable bit) */
#define  SDIO_CLKCR_WIDBUS_0                    ((uint16_t)0x0800)            /*!< Bit 0 */
#define  SDIO_CLKCR_WIDBUS_1                    ((uint16_t)0x1000)            /*!< Bit 1 */

#define  SDIO_CLKCTRL_CLKEDG                    ((uint16_t)0x2000)            /*!< SDIO_CK dephasing selection bit */
#define  SDIO_CLKCTRL_FLWCTRLEN                 ((uint16_t)0x4000)            /*!< HW Flow Control enable */

/*******************  Bit definition for SDIO_ARG register  *******************/
#define  SDIO_ARG_ARG                           ((uint32_t)0xFFFFFFFF)            /*!< Command argument */

/*******************  Bit definition for SDIO_CMD register  *******************/
#define  SDIO_CMD_CMDIDX                        ((uint16_t)0x003F)            /*!< Command Index */

#define  SDIO_CMD_RSPWT                         ((uint16_t)0x00C0)            /*!< WAITRESP[1:0] bits (Wait for response bits) */
#define  SDIO_CMD_WAITRESP_0                    ((uint16_t)0x0040)            /*!<  Bit 0 */
#define  SDIO_CMD_WAITRESP_1                    ((uint16_t)0x0080)            /*!<  Bit 1 */

#define  SDIO_CMD_INTWT                         ((uint16_t)0x0100)            /*!< CPSM Waits for Interrupt Request */
#define  SDIO_CMD_PNDWT                         ((uint16_t)0x0200)            /*!< CPSM Waits for ends of data transfer (CmdPend internal signal) */
#define  SDIO_CMD_CMDMEN                        ((uint16_t)0x0400)            /*!< Command path state machine (CPSM) Enable bit */
#define  SDIO_CMD_SDIOSUSP                      ((uint16_t)0x0800)            /*!< SD I/O suspend command */
#define  SDIO_CMD_CMPLSGNLEN                    ((uint16_t)0x1000)            /*!< Enable CMD completion */
#define  SDIO_CMD_INTDIS                        ((uint16_t)0x2000)            /*!< Interrupt Disable */
#define  SDIO_CMD_ATACMD                        ((uint16_t)0x4000)            /*!< CE-ATA command */

/*****************  Bit definition for SDIO_RSPCMD register  *****************/
#define  SDIO_RSPCMD_RSPCMD                     ((uint8_t)0x3F)               /*!< Response command index */

/******************  Bit definition for SDIO_RESP0 register  ******************/
#define  SDIO_RESP0_CARDSTATUS0                 ((uint32_t)0xFFFFFFFF)        /*!< Card Status */

/******************  Bit definition for SDIO_RSP1 register  ******************/
#define  SDIO_RSP1_CARDSTS1                     ((uint32_t)0xFFFFFFFF)        /*!< Card Status */

/******************  Bit definition for SDIO_RSP2 register  ******************/
#define  SDIO_RSP2_CARDSTS2                     ((uint32_t)0xFFFFFFFF)        /*!< Card Status */

/******************  Bit definition for SDIO_RSP3 register  ******************/
#define  SDIO_RSP3_CARDSTS3                     ((uint32_t)0xFFFFFFFF)        /*!< Card Status */

/******************  Bit definition for SDIO_RSP4 register  ******************/
#define  SDIO_RSP4_CARDSTS4                     ((uint32_t)0xFFFFFFFF)        /*!< Card Status */

/******************  Bit definition for SDIO_DTTMR register  *****************/
#define  SDIO_DTTMR_TIMEOUT                     ((uint32_t)0xFFFFFFFF)        /*!< Data timeout period. */

/******************  Bit definition for SDIO_DTLEN register  *******************/
#define  SDIO_DTLEN_DTLEN                       ((uint32_t)0x01FFFFFF)        /*!< Data length value */

/******************  Bit definition for SDIO_DTCTRL register  ******************/
#define  SDIO_DTCTRL_TFREN                      ((uint16_t)0x0001)            /*!< Data transfer enabled bit */
#define  SDIO_DTCTRL_TFRDIR                     ((uint16_t)0x0002)            /*!< Data transfer direction selection */
#define  SDIO_DTCTRL_TFRMODE                    ((uint16_t)0x0004)            /*!< Data transfer mode selection */
#define  SDIO_DTCTRL_DMAEN                      ((uint16_t)0x0008)            /*!< DMA enabled bit */

#define  SDIO_DTCTRL_BLKSIZE                    ((uint16_t)0x00F0)            /*!< DBLOCKSIZE[3:0] bits (Data block size) */
#define  SDIO_DTCTRL_DBLOCKSIZE_0               ((uint16_t)0x0010)            /*!< Bit 0 */
#define  SDIO_DTCTRL_DBLOCKSIZE_1               ((uint16_t)0x0020)            /*!< Bit 1 */
#define  SDIO_DTCTRL_DBLOCKSIZE_2               ((uint16_t)0x0040)            /*!< Bit 2 */
#define  SDIO_DTCTRL_DBLOCKSIZE_3               ((uint16_t)0x0080)            /*!< Bit 3 */

#define  SDIO_DTCTRL_RDWTSTART                  ((uint16_t)0x0100)            /*!< Read wait start */
#define  SDIO_DTCTRL_RDWTSTOP                   ((uint16_t)0x0200)            /*!< Read wait stop */
#define  SDIO_DTCTRL_RDWTMODE                   ((uint16_t)0x0400)            /*!< Read wait mode */
#define  SDIO_DTCTRL_SDIOEN                     ((uint16_t)0x0800)            /*!< SD I/O enable functions */

/******************  Bit definition for SDIO_DTCNTR register  *****************/
#define  SDIO_DTCNTR_DTCNT                      ((uint32_t)0x01FFFFFF)        /*!< Data count value */

/******************  Bit definition for SDIO_STS register  ********************/
#define  SDIO_STS_CMDFAIL                       ((uint32_t)0x00000001)        /*!< Command response received (CRC check failed) */
#define  SDIO_STS_DTFAIL                        ((uint32_t)0x00000002)        /*!< Data block sent/received (CRC check failed) */
#define  SDIO_STS_CMDTIMEOUT                    ((uint32_t)0x00000004)        /*!< Command response timeout */
#define  SDIO_STS_DTTIMEOUT                     ((uint32_t)0x00000008)        /*!< Data timeout */
#define  SDIO_STS_TXERRU                        ((uint32_t)0x00000010)        /*!< Transmit FIFO underrun error */
#define  SDIO_STS_RXERRO                        ((uint32_t)0x00000020)        /*!< Received FIFO overrun error */
#define  SDIO_STS_CMDRSPCMPL                    ((uint32_t)0x00000040)        /*!< Command response received (CRC check passed) */
#define  SDIO_STS_CMDCMPL                       ((uint32_t)0x00000080)        /*!< Command sent (no response required) */
#define  SDIO_STS_DTCMPL                        ((uint32_t)0x00000100)        /*!< Data end (data counter, SDIDCOUNT, is zero) */
#define  SDIO_STS_SBITERR                       ((uint32_t)0x00000200)        /*!< Start bit not detected on all data signals in wide bus mode */
#define  SDIO_STS_DTBLKCMPL                     ((uint32_t)0x00000400)        /*!< Data block sent/received (CRC check passed) */
#define  SDIO_STS_DOCMD                         ((uint32_t)0x00000800)        /*!< Command transfer in progress */
#define  SDIO_STS_DOTX                          ((uint32_t)0x00001000)        /*!< Data transmit in progress */
#define  SDIO_STS_DORX                          ((uint32_t)0x00002000)        /*!< Data receive in progress */
#define  SDIO_STS_TXBUF_H                       ((uint32_t)0x00004000)        /*!< Transmit FIFO Half Empty: at least 8 words can be written into the FIFO */
#define  SDIO_STS_RXBUF_H                       ((uint32_t)0x00008000)        /*!< Receive FIFO Half Full: there are at least 8 words in the FIFO */
#define  SDIO_STS_TXBUF_F                       ((uint32_t)0x00010000)        /*!< Transmit FIFO full */
#define  SDIO_STS_RXBUF_F                       ((uint32_t)0x00020000)        /*!< Receive FIFO full */
#define  SDIO_STS_TXBUF_E                       ((uint32_t)0x00040000)        /*!< Transmit FIFO empty */
#define  SDIO_STS_RXBUF_E                       ((uint32_t)0x00080000)        /*!< Receive FIFO empty */
#define  SDIO_STS_TXBUF                         ((uint32_t)0x00100000)        /*!< Data available in transmit FIFO */
#define  SDIO_STS_RXBUF                         ((uint32_t)0x00200000)        /*!< Data available in receive FIFO */
#define  SDIO_STS_SDIOIF                        ((uint32_t)0x00400000)        /*!< SDIO interrupt received */
#define  SDIO_STS_ATACMPL                       ((uint32_t)0x00800000)        /*!< CE-ATA command completion signal received for CMD61 */

/*******************  Bit definition for SDIO_INTCLR register  *******************/
#define  SDIO_INTCLR_CMDFAIL                    ((uint32_t)0x00000001)        /*!< CCRCFAIL flag clear bit */
#define  SDIO_INTCLR_DTFAIL                     ((uint32_t)0x00000002)        /*!< DCRCFAIL flag clear bit */
#define  SDIO_INTCLR_CMDTIMEOUT                 ((uint32_t)0x00000004)        /*!< CTIMEOUT flag clear bit */
#define  SDIO_INTCLR_DTTIMEOUT                  ((uint32_t)0x00000008)        /*!< DTIMEOUT flag clear bit */
#define  SDIO_INTCLR_TXERRU                     ((uint32_t)0x00000010)        /*!< TXUNDERR flag clear bit */
#define  SDIO_INTCLR_RXERRO                     ((uint32_t)0x00000020)        /*!< RXOVERR flag clear bit */
#define  SDIO_INTCLR_CMDRSPCMPL                 ((uint32_t)0x00000040)        /*!< CMDREND flag clear bit */
#define  SDIO_INTCLR_CMDCMPL                    ((uint32_t)0x00000080)        /*!< CMDSENT flag clear bit */
#define  SDIO_INTCLR_DTCMPL                     ((uint32_t)0x00000100)        /*!< DATAEND flag clear bit */
#define  SDIO_INTCLR_SBITERR                    ((uint32_t)0x00000200)        /*!< STBITERR flag clear bit */
#define  SDIO_INTCLR_DTBLKCMPL                  ((uint32_t)0x00000400)        /*!< DBCKEND flag clear bit */
#define  SDIO_INTCLR_SDIOIF                     ((uint32_t)0x00400000)        /*!< SDIOIT flag clear bit */
#define  SDIO_INTCLR_ATACMPL                    ((uint32_t)0x00800000)        /*!< CEATAEND flag clear bit */

/******************  Bit definition for SDIO_MASK register  *******************/
#define  SDIO_MASK_CCRCFAILIE                   ((uint32_t)0x00000001)        /*!< Command CRC Fail Interrupt Enable */
#define  SDIO_INTEN_DTFAIL                      ((uint32_t)0x00000002)        /*!< Data CRC Fail Interrupt Enable */
#define  SDIO_INTEN_CMDTIMEOUT                  ((uint32_t)0x00000004)        /*!< Command TimeOut Interrupt Enable */
#define  SDIO_INTEN_DTTIMEOUT                   ((uint32_t)0x00000008)        /*!< Data TimeOut Interrupt Enable */
#define  SDIO_INTEN_TXERRU                      ((uint32_t)0x00000010)        /*!< Tx FIFO UnderRun Error Interrupt Enable */
#define  SDIO_INTEN_RXERRO                      ((uint32_t)0x00000020)        /*!< Rx FIFO OverRun Error Interrupt Enable */
#define  SDIO_INTEN_CMDRSPCMPL                  ((uint32_t)0x00000040)        /*!< Command Response Received Interrupt Enable */
#define  SDIO_INTEN_CMDCMPL                     ((uint32_t)0x00000080)        /*!< Command Sent Interrupt Enable */
#define  SDIO_INTEN_DTCMPL                      ((uint32_t)0x00000100)        /*!< Data End Interrupt Enable */
#define  SDIO_INTEN_SBITERR                     ((uint32_t)0x00000200)        /*!< Start Bit Error Interrupt Enable */
#define  SDIO_INTEN_DTBLKCMPL                   ((uint32_t)0x00000400)        /*!< Data Block End Interrupt Enable */
#define  SDIO_INTEN_DOCMD                       ((uint32_t)0x00000800)        /*!< Command Acting Interrupt Enable */
#define  SDIO_INTEN_DOTX                        ((uint32_t)0x00001000)        /*!< Data Transmit Acting Interrupt Enable */
#define  SDIO_INTEN_DORX                        ((uint32_t)0x00002000)        /*!< Data receive acting interrupt enabled */
#define  SDIO_INTEN_TXBUF_H                     ((uint32_t)0x00004000)        /*!< Tx FIFO Half Empty interrupt Enable */
#define  SDIO_INTEN_RXBUF_H                     ((uint32_t)0x00008000)        /*!< Rx FIFO Half Full interrupt Enable */
#define  SDIO_INTEN_TXBUF_F                     ((uint32_t)0x00010000)        /*!< Tx FIFO Full interrupt Enable */
#define  SDIO_INTEN_RXBUF_F                     ((uint32_t)0x00020000)        /*!< Rx FIFO Full interrupt Enable */
#define  SDIO_INTEN_TXBUF_E                     ((uint32_t)0x00040000)        /*!< Tx FIFO Empty interrupt Enable */
#define  SDIO_INTEN_RXBUF_E                     ((uint32_t)0x00080000)        /*!< Rx FIFO Empty interrupt Enable */
#define  SDIO_INTEN_TXBUF                       ((uint32_t)0x00100000)        /*!< Data available in Tx FIFO interrupt Enable */
#define  SDIO_INTEN_RXBUF                       ((uint32_t)0x00200000)        /*!< Data available in Rx FIFO interrupt Enable */
#define  SDIO_INTEN_SDIOIF                      ((uint32_t)0x00400000)        /*!< SDIO Mode Interrupt Received interrupt Enable */
#define  SDIO_INTEN_ATACMPL                     ((uint32_t)0x00800000)        /*!< CE-ATA command completion signal received Interrupt Enable */

/*****************  Bit definition for SDIO_BUFCNTR register  *****************/
#define  SDIO_BUFCNTR_CNT                       ((uint32_t)0x00FFFFFF)        /*!< Remaining number of words to be written to or read from the FIFO */

/******************  Bit definition for SDIO_BUF register  *******************/
#define  SDIO_BUF_DT                            ((uint32_t)0xFFFFFFFF)        /*!< Receive and transmit BUF data */

/******************************************************************************/
/*                                                                            */
/*                                   USB Device FS                            */
/*                                                                            */
/******************************************************************************/

/** Endpoint-specific registers */
/*******************  Bit definition for USB_EPT0 register  *******************/
#define  USB_EPT0_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT0_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT0_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT0_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT0_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT0_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT0_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT0_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT0_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT0_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT0_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT0_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT0_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT0_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT0_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT0_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT1 register  *******************/
#define  USB_EPT1_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT1_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT1_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT1_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT1_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT1_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT1_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT1_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT1_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT1_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT1_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT1_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT1_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT1_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT1_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT1_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT2 register  *******************/
#define  USB_EPT2_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT2_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT2_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT2_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT2_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT2_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT2_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT2_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT2_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT2_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT2_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT2_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT2_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT2_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT2_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT2_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT3 register  *******************/
#define  USB_EPT3_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT3_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT3_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT3_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT3_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT3_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT3_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT3_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT3_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT3_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT3_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT3_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT3_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT3_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT3_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT3_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT4 register  *******************/
#define  USB_EPT4_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT4_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT4_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT4_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT4_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT4_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT4_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT4_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT4_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT4_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT4_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT4_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT4_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT4_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT4_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT4_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT5 register  *******************/
#define  USB_EPT5_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT5_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT5_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT5_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT5_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT5_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT5_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT5_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT5_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT5_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT5_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT5_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT5_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT5_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT5_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT5_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT6 register  *******************/
#define  USB_EPT6_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT6_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT6_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT6_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT6_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT6_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT6_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT6_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT6_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT6_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT6_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT6_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT6_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT6_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT6_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT6_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EPT7 register  *******************/
#define  USB_EPT7_EPTADR                        ((uint16_t)0x000F)            /*!< Endpoint Address */

#define  USB_EPT7_STS_TX                        ((uint16_t)0x0030)            /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define  USB_EPT7_STS_TX_0                      ((uint16_t)0x0010)            /*!< Bit 0 */
#define  USB_EPT7_STS_TX_1                      ((uint16_t)0x0020)            /*!< Bit 1 */

#define  USB_EPT7_DTOG_TX                       ((uint16_t)0x0040)            /*!< Data Toggle, for transmission transfers */
#define  USB_EPT7_CTFR_TX                       ((uint16_t)0x0080)            /*!< Correct Transfer for transmission */
#define  USB_EPT7_EPT_SUBTYPE                   ((uint16_t)0x0100)            /*!< Endpoint Kind */

#define  USB_EPT7_EPT_TYPE                      ((uint16_t)0x0600)            /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define  USB_EPT7_EPT_TYPE_0                    ((uint16_t)0x0200)            /*!< Bit 0 */
#define  USB_EPT7_EPT_TYPE_1                    ((uint16_t)0x0400)            /*!< Bit 1 */

#define  USB_EPT7_SETUP                         ((uint16_t)0x0800)            /*!< Setup transaction completed */

#define  USB_EPT7_STS_RX                        ((uint16_t)0x3000)            /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define  USB_EPT7_STS_RX_0                      ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USB_EPT7_STS_RX_1                      ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USB_EPT7_DTOG_RX                       ((uint16_t)0x4000)            /*!< Data Toggle, for reception transfers */
#define  USB_EPT7_CTFR_RX                       ((uint16_t)0x8000)            /*!< Correct Transfer for reception */

/** Common registers */
/*******************  Bit definition for USB_CTRL register  *******************/
#define  USB_CTRL_FRST                          ((uint16_t)0x0001)            /*!< Force USB Reset */
#define  USB_CTRL_PDWN                          ((uint16_t)0x0002)            /*!< Power down */
#define  USB_CTRL_LPWR                          ((uint16_t)0x0004)            /*!< Low-power mode */
#define  USB_CTRL_FSUSP                         ((uint16_t)0x0008)            /*!< Force suspend */
#define  USB_CTRL_RESUME                        ((uint16_t)0x0010)            /*!< Resume request */
#define  USB_CTRL_ESOF_IEN                      ((uint16_t)0x0100)            /*!< Expected Start Of Frame Interrupt Mask */
#define  USB_CTRL_SOF_IEN                       ((uint16_t)0x0200)            /*!< Start Of Frame Interrupt Mask */
#define  USB_CTRL_RST_IEN                       ((uint16_t)0x0400)            /*!< RESET Interrupt Mask */
#define  USB_CTRL_SUSP_IEN                      ((uint16_t)0x0800)            /*!< Suspend mode Interrupt Mask */
#define  USB_CTRL_WKUP_IEN                      ((uint16_t)0x1000)            /*!< Wakeup Interrupt Mask */
#define  USB_CTRL_ERR_IEN                       ((uint16_t)0x2000)            /*!< Error Interrupt Mask */
#define  USB_CTRL_PMOVR_IEN                     ((uint16_t)0x4000)            /*!< Packet Memory Area Over / Underrun Interrupt Mask */
#define  USB_CTRL_CTFR_IEN                      ((uint16_t)0x8000)            /*!< Correct Transfer Interrupt Mask */

/*******************  Bit definition for USB_INTSTS register  *******************/
#define  USB_INTSTS_EPT_ID                      ((uint16_t)0x000F)            /*!< Endpoint Identifier */
#define  USB_INTSTS_DIR                         ((uint16_t)0x0010)            /*!< Direction of transaction */
#define  USB_INTSTS_ESOF                        ((uint16_t)0x0100)            /*!< Expected Start Of Frame */
#define  USB_INTSTS_SOFF                        ((uint16_t)0x0200)            /*!< Start Of Frame */
#define  USB_INTSTS_RSTF                        ((uint16_t)0x0400)            /*!< USB RESET request */
#define  USB_INTSTS_SUSPF                       ((uint16_t)0x0800)            /*!< Suspend mode request */
#define  USB_INTSTS_WKUPF                       ((uint16_t)0x1000)            /*!< Wake up */
#define  USB_INTSTS_ERRF                        ((uint16_t)0x2000)            /*!< Error */
#define  USB_INTSTS_PMOVERF                     ((uint16_t)0x4000)            /*!< Packet Memory Area Over / Underrun */
#define  USB_INTSTS_CTFRF                       ((uint16_t)0x8000)            /*!< Correct Transfer */

/*******************  Bit definition for USB_FRNUM register  ********************/
#define  USB_FRNUM_FRNUM                        ((uint16_t)0x07FF)            /*!< Frame Number */
#define  USB_FRNUM_LSOF                         ((uint16_t)0x1800)            /*!< Lost SOF */
#define  USB_FRNUM_LCK                          ((uint16_t)0x2000)            /*!< Locked */
#define  USB_FRNUM_DMSTS                        ((uint16_t)0x4000)            /*!< Receive Data - Line Status */
#define  USB_FRNUM_DPSTS                        ((uint16_t)0x8000)            /*!< Receive Data + Line Status */

/******************  Bit definition for USB_DEVADR register  *******************/
#define  USB_DEVADR_ADR                         ((uint8_t)0x7F)               /*!< ADD[6:0] bits (Device Address) */
#define  USB_DEVADR_ADR_B0                      ((uint8_t)0x01)               /*!< Bit 0 */
#define  USB_DEVADR_ADR_B1                      ((uint8_t)0x02)               /*!< Bit 1 */
#define  USB_DEVADR_ADR_B2                      ((uint8_t)0x04)               /*!< Bit 2 */
#define  USB_DEVADR_ADR_B3                      ((uint8_t)0x08)               /*!< Bit 3 */
#define  USB_DEVADR_ADR_B4                      ((uint8_t)0x10)               /*!< Bit 4 */
#define  USB_DEVADR_ADR_B5                      ((uint8_t)0x20)               /*!< Bit 5 */
#define  USB_DEVADR_ADR_B6                      ((uint8_t)0x40)               /*!< Bit 6 */

#define  USB_DEVADR_EN                          ((uint8_t)0x80)               /*!< Enable Function */

/******************  Bit definition for USB_BUFTBL register  ******************/
#define  USB_BUFTBL_ADR                         ((uint16_t)0xFFF8)            /*!< Buffer Table */

/** Buffer descriptor table */
/*****************  Bit definition for USB_ADR0_TX register  *****************/
#define  USB_ADR0_TX_ADR0_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 0 */

/*****************  Bit definition for USB_ADR1_TX register  *****************/
#define  USB_ADR1_TX_ADR1_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 1 */

/*****************  Bit definition for USB_ADR2_TX register  *****************/
#define  USB_ADR2_TX_ADR2_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 2 */

/*****************  Bit definition for USB_ADR3_TX register  *****************/
#define  USB_ADR3_TX_ADR3_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 3 */

/*****************  Bit definition for USB_ADR4_TX register  *****************/
#define  USB_ADR4_TX_ADR4_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 4 */

/*****************  Bit definition for USB_ADR5_TX register  *****************/
#define  USB_ADR5_TX_ADR5_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 5 */

/*****************  Bit definition for USB_ADR6_TX register  *****************/
#define  USB_ADR6_TX_ADR6_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 6 */

/*****************  Bit definition for USB_ADR7_TX register  *****************/
#define  USB_ADR7_TX_ADR7_TX                    ((uint16_t)0xFFFE)            /*!< Transmission Buffer Address 7 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_CNT0_TX register  ****************/
#define  USB_CNT0_TX_CNT0_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 0 */

/*****************  Bit definition for USB_CNT1_TX register  ****************/
#define  USB_CNT1_TX_CNT1_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 1 */

/*****************  Bit definition for USB_CNT2_TX register  ****************/
#define  USB_CNT2_TX_CNT2_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 2 */

/*****************  Bit definition for USB_CNT3_TX register  ****************/
#define  USB_CNT3_TX_CNT3_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 3 */

/*****************  Bit definition for USB_CNT4_TX register  ****************/
#define  USB_CNT4_TX_CNT4_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 4 */

/*****************  Bit definition for USB_CNT5_TX register  ****************/
#define  USB_CNT5_TX_CNT5_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 5 */

/*****************  Bit definition for USB_CNT6_TX register  ****************/
#define  USB_CNT6_TX_CNT6_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 6 */

/*****************  Bit definition for USB_CNT7_TX register  ****************/
#define  USB_CNT7_TX_CNT7_TX                    ((uint16_t)0x03FF)            /*!< Transmission Byte Count 7 */

/*----------------------------------------------------------------------------*/

/****************  Bit definition for USB_CNT0_TX_0 register  ***************/
#define  USB_CNT0_TX_0_CNT0_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 0 (low) */

/****************  Bit definition for USB_CNT0_TX_1 register  ***************/
#define  USB_CNT0_TX_1_CNT0_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 0 (high) */

/****************  Bit definition for USB_CNT1_TX_0 register  ***************/
#define  USB_CNT1_TX_0_CNT1_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 1 (low) */

/****************  Bit definition for USB_CNT1_TX_1 register  ***************/
#define  USB_CNT1_TX_1_CNT1_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 1 (high) */

/****************  Bit definition for USB_CNT2_TX_0 register  ***************/
#define  USB_CNT2_TX_0_CNT2_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 2 (low) */

/****************  Bit definition for USB_CNT2_TX_1 register  ***************/
#define  USB_CNT2_TX_1_CNT2_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 2 (high) */

/****************  Bit definition for USB_CNT3_TX_0 register  ***************/
#define  USB_CNT3_TX_0_CNT3_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 3 (low) */

/****************  Bit definition for USB_CNT3_TX_1 register  ***************/
#define  USB_CNT3_TX_1_CNT3_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 3 (high) */

/****************  Bit definition for USB_CNT4_TX_0 register  ***************/
#define  USB_CNT4_TX_0_CNT4_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 4 (low) */

/****************  Bit definition for USB_CNT4_TX_1 register  ***************/
#define  USB_CNT4_TX_1_CNT4_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 4 (high) */

/****************  Bit definition for USB_CNT5_TX_0 register  ***************/
#define  USB_CNT5_TX_0_CNT5_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 5 (low) */

/****************  Bit definition for USB_CNT5_TX_1 register  ***************/
#define  USB_CNT5_TX_1_CNT5_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 5 (high) */

/****************  Bit definition for USB_CNT6_TX_0 register  ***************/
#define  USB_CNT6_TX_0_CNT6_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 6 (low) */

/****************  Bit definition for USB_CNT6_TX_1 register  ***************/
#define  USB_CNT6_TX_1_CNT6_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 6 (high) */

/****************  Bit definition for USB_CNT7_TX_0 register  ***************/
#define  USB_CNT7_TX_0_CNT7_TX_0                ((uint32_t)0x000003FF)        /*!< Transmission Byte Count 7 (low) */

/****************  Bit definition for USB_CNT7_TX_1 register  ***************/
#define  USB_CNT7_TX_1_CNT7_TX_1                ((uint32_t)0x03FF0000)        /*!< Transmission Byte Count 7 (high) */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_ADR0_RX register  *****************/
#define  USB_ADR0_RX_ADR0_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 0 */

/*****************  Bit definition for USB_ADR1_RX register  *****************/
#define  USB_ADR1_RX_ADR1_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 1 */

/*****************  Bit definition for USB_ADR2_RX register  *****************/
#define  USB_ADR2_RX_ADR2_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 2 */

/*****************  Bit definition for USB_ADR3_RX register  *****************/
#define  USB_ADR3_RX_ADR3_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 3 */

/*****************  Bit definition for USB_ADR4_RX register  *****************/
#define  USB_ADR4_RX_ADR4_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 4 */

/*****************  Bit definition for USB_ADR5_RX register  *****************/
#define  USB_ADR5_RX_ADR5_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 5 */

/*****************  Bit definition for USB_ADR6_RX register  *****************/
#define  USB_ADR6_RX_ADR6_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 6 */

/*****************  Bit definition for USB_ADR7_RX register  *****************/
#define  USB_ADR7_RX_ADR7_RX                    ((uint16_t)0xFFFE)            /*!< Reception Buffer Address 7 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_CNT0_RX register  ****************/
#define  USB_CNT0_RX_CNT0_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT0_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT0_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT0_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT0_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT0_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT0_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT0_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT1_RX register  ****************/
#define  USB_CNT1_RX_CNT1_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT1_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT1_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT1_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT1_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT1_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT1_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT1_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT2_RX register  ****************/
#define  USB_CNT2_RX_CNT2_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT2_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT2_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT2_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT2_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT2_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT2_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT2_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT3_RX register  ****************/
#define  USB_CNT3_RX_CNT0_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT3_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT3_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT3_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT3_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT3_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT3_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT3_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT4_RX register  ****************/
#define  USB_CNT4_RX_CNT0_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT4_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT4_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT4_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT4_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT4_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT4_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT4_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT5_RX register  ****************/
#define  USB_CNT5_RX_CNT0_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT5_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT5_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT5_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT5_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT5_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT5_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT5_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT6_RX register  ****************/
#define  USB_CNT6_RX_CNT0_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT6_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT6_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT6_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT6_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT6_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT6_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT6_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*****************  Bit definition for USB_CNT7_RX register  ****************/
#define  USB_CNT7_RX_CNT0_RX                    ((uint16_t)0x03FF)            /*!< Reception Byte Count */

#define  USB_CNT7_RX_NUM_BLK                    ((uint16_t)0x7C00)            /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define  USB_CNT7_RX_NUM_BLK_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  USB_CNT7_RX_NUM_BLK_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  USB_CNT7_RX_NUM_BLK_2                  ((uint16_t)0x1000)            /*!< Bit 2 */
#define  USB_CNT7_RX_NUM_BLK_3                  ((uint16_t)0x2000)            /*!< Bit 3 */
#define  USB_CNT7_RX_NUM_BLK_4                  ((uint16_t)0x4000)            /*!< Bit 4 */

#define  USB_CNT7_RX_BLKSIZE                    ((uint16_t)0x8000)            /*!< BLock SIZE */

/*----------------------------------------------------------------------------*/

/****************  Bit definition for USB_CNT0_RX_0 register  ***************/
#define  USB_CNT0_RX_0_CNT0_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT0_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT0_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT0_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT0_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT0_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT0_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT0_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT0_RX_1 register  ***************/
#define  USB_CNT0_RX_1_CNT0_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT0_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT0_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 1 */
#define  USB_CNT0_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT0_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT0_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT0_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT0_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/****************  Bit definition for USB_CNT1_RX_0 register  ***************/
#define  USB_CNT1_RX_0_CNT1_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT1_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT1_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT1_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT1_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT1_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT1_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT1_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT1_RX_1 register  ***************/
#define  USB_CNT1_RX_1_CNT1_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT1_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT1_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT1_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT1_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT1_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT1_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT1_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/****************  Bit definition for USB_CNT2_RX_0 register  ***************/
#define  USB_CNT2_RX_0_CNT2_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT2_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT2_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT2_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT2_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT2_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT2_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT2_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT2_RX_1 register  ***************/
#define  USB_CNT2_RX_1_CNT2_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT2_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT2_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT2_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT2_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT2_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT2_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT2_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/****************  Bit definition for USB_CNT3_RX_0 register  ***************/
#define  USB_CNT3_RX_0_CNT3_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT3_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT3_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT3_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT3_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT3_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT3_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT3_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT3_RX_1 register  ***************/
#define  USB_CNT3_RX_1_CNT3_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT3_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT3_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT3_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT3_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT3_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT3_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT3_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/****************  Bit definition for USB_CNT4_RX_0 register  ***************/
#define  USB_CNT4_RX_0_CNT4_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT4_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT4_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT4_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT4_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT4_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT4_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT4_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT4_RX_1 register  ***************/
#define  USB_CNT4_RX_1_CNT4_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT4_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT4_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT4_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT4_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT4_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT4_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT4_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/****************  Bit definition for USB_CNT5_RX_0 register  ***************/
#define  USB_CNT5_RX_0_CNT5_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT5_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT5_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT5_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT5_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT5_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT5_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT5_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT5_RX_1 register  ***************/
#define  USB_CNT5_RX_1_CNT5_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT5_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT5_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT5_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT5_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT5_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT5_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT5_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/***************  Bit definition for USB_CNT6_RX_0  register  ***************/
#define  USB_CNT6_RX_0_CNT6_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT6_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT6_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT6_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT6_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT6_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT6_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT6_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/****************  Bit definition for USB_CNT6_RX_1 register  ***************/
#define  USB_CNT6_RX_1_CNT6_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT6_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT6_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT6_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT6_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT6_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT6_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT6_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/***************  Bit definition for USB_CNT7_RX_0 register  ****************/
#define  USB_CNT7_RX_0_CNT7_RX_0                ((uint32_t)0x000003FF)        /*!< Reception Byte Count (low) */

#define  USB_CNT7_RX_0_NUM_BLK_0                ((uint32_t)0x00007C00)        /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define  USB_CNT7_RX_0_NUM_BLK_0_0              ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  USB_CNT7_RX_0_NUM_BLK_0_1              ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  USB_CNT7_RX_0_NUM_BLK_0_2              ((uint32_t)0x00001000)        /*!< Bit 2 */
#define  USB_CNT7_RX_0_NUM_BLK_0_3              ((uint32_t)0x00002000)        /*!< Bit 3 */
#define  USB_CNT7_RX_0_NUM_BLK_0_4              ((uint32_t)0x00004000)        /*!< Bit 4 */

#define  USB_CNT7_RX_0_BLKSIZE_0                ((uint32_t)0x00008000)        /*!< BLock SIZE (low) */

/***************  Bit definition for USB_CNT7_RX_1 register  ****************/
#define  USB_CNT7_RX_1_CNT7_RX_1                ((uint32_t)0x03FF0000)        /*!< Reception Byte Count (high) */

#define  USB_CNT7_RX_1_NUM_BLK_1                ((uint32_t)0x7C000000)        /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define  USB_CNT7_RX_1_NUM_BLK_1_0              ((uint32_t)0x04000000)        /*!< Bit 0 */
#define  USB_CNT7_RX_1_NUM_BLK_1_1              ((uint32_t)0x08000000)        /*!< Bit 1 */
#define  USB_CNT7_RX_1_NUM_BLK_1_2              ((uint32_t)0x10000000)        /*!< Bit 2 */
#define  USB_CNT7_RX_1_NUM_BLK_1_3              ((uint32_t)0x20000000)        /*!< Bit 3 */
#define  USB_CNT7_RX_1_NUM_BLK_1_4              ((uint32_t)0x40000000)        /*!< Bit 4 */

#define  USB_CNT7_RX_1_BLKSIZE_1                ((uint32_t)0x80000000)        /*!< BLock SIZE (high) */

/******************************************************************************/
/*                                                                            */
/*                         Controller Area Network                            */
/*                                                                            */
/******************************************************************************/

/** CAN control and status registers */
/*******************  Bit definition for CAN_MCTRL register  ********************/
#define  CAN_MCTRL_INRQ                         ((uint16_t)0x0001)            /*!< Initialization Request */
#define  CAN_MCTRL_SLP                          ((uint16_t)0x0002)            /*!< Sleep Mode Request */
#define  CAN_MCTRL_TFP                          ((uint16_t)0x0004)            /*!< Transmit FIFO Priority */
#define  CAN_MCTRL_RFL                          ((uint16_t)0x0008)            /*!< Receive FIFO Locked Mode */
#define  CAN_MCTRL_NART                         ((uint16_t)0x0010)            /*!< No Automatic Retransmission */
#define  CAN_MCTRL_AWU                          ((uint16_t)0x0020)            /*!< Automatic Wakeup Mode */
#define  CAN_MCTRL_ABO                          ((uint16_t)0x0040)            /*!< Automatic Bus-Off Management */
#define  CAN_MCTRL_TTC                          ((uint16_t)0x0080)            /*!< Time Triggered Communication Mode */
#define  CAN_MCTRL_RST                          ((uint16_t)0x8000)            /*!< CAN software master reset */

/*******************  Bit definition for CAN_MSTS register  ********************/
#define  CAN_MSTS_IAK                           ((uint16_t)0x0001)            /*!< Initialization Acknowledge */
#define  CAN_MSTS_SAK                           ((uint16_t)0x0002)            /*!< Sleep Acknowledge */
#define  CAN_MSTS_ERIT                          ((uint16_t)0x0004)            /*!< Error Interrupt */
#define  CAN_MSTS_WKIT                          ((uint16_t)0x0008)            /*!< Wakeup Interrupt */
#define  CAN_MSTS_SAKIT                         ((uint16_t)0x0010)            /*!< Sleep Acknowledge Interrupt */
#define  CAN_MSTS_TX                            ((uint16_t)0x0100)            /*!< Transmit Mode */
#define  CAN_MSTS_RX                            ((uint16_t)0x0200)            /*!< Receive Mode */
#define  CAN_MSTS_LSAP                          ((uint16_t)0x0400)            /*!< Last Sample Point */
#define  CAN_MSTS_RXS                           ((uint16_t)0x0800)            /*!< CAN Rx Signal */

/*******************  Bit definition for CAN_TSTS register  ********************/
#define  CAN_TSTS_RQC0                          ((uint32_t)0x00000001)        /*!< Request Completed Mailbox0 */
#define  CAN_TSTS_TOK0                          ((uint32_t)0x00000002)        /*!< Transmission OK of Mailbox0 */
#define  CAN_TSTS_ALS0                          ((uint32_t)0x00000004)        /*!< Arbitration Lost for Mailbox0 */
#define  CAN_TSTS_TER0                          ((uint32_t)0x00000008)        /*!< Transmission Error of Mailbox0 */
#define  CAN_TSTS_ARQ0                          ((uint32_t)0x00000080)        /*!< Abort Request for Mailbox0 */
#define  CAN_TSTS_RQC1                          ((uint32_t)0x00000100)        /*!< Request Completed Mailbox1 */
#define  CAN_TSTS_TOK1                          ((uint32_t)0x00000200)        /*!< Transmission OK of Mailbox1 */
#define  CAN_TSTS_ALS1                          ((uint32_t)0x00000400)        /*!< Arbitration Lost for Mailbox1 */
#define  CAN_TSTS_TER1                          ((uint32_t)0x00000800)        /*!< Transmission Error of Mailbox1 */
#define  CAN_TSTS_ARQ1                          ((uint32_t)0x00008000)        /*!< Abort Request for Mailbox 1 */
#define  CAN_TSTS_RQC2                          ((uint32_t)0x00010000)        /*!< Request Completed Mailbox2 */
#define  CAN_TSTS_TOK2                          ((uint32_t)0x00020000)        /*!< Transmission OK of Mailbox 2 */
#define  CAN_TSTS_ALS2                          ((uint32_t)0x00040000)        /*!< Arbitration Lost for mailbox 2 */
#define  CAN_TSTS_TER2                          ((uint32_t)0x00080000)        /*!< Transmission Error of Mailbox 2 */
#define  CAN_TSTS_ARQ2                          ((uint32_t)0x00800000)        /*!< Abort Request for Mailbox 2 */
#define  CAN_TSTS_NTM                           ((uint32_t)0x03000000)        /*!< Mailbox Code */

#define  CAN_TSTS_TSME                          ((uint32_t)0x1C000000)        /*!< TME[2:0] bits */
#define  CAN_TSTS_TSME0                         ((uint32_t)0x04000000)        /*!< Transmit Mailbox 0 Empty */
#define  CAN_TSTS_TSME1                         ((uint32_t)0x08000000)        /*!< Transmit Mailbox 1 Empty */
#define  CAN_TSTS_TSME2                         ((uint32_t)0x10000000)        /*!< Transmit Mailbox 2 Empty */

#define  CAN_TSTS_LPM                           ((uint32_t)0xE0000000)        /*!< LOW[2:0] bits */
#define  CAN_TSTS_LPM0                          ((uint32_t)0x20000000)        /*!< Lowest Priority Flag for Mailbox 0 */
#define  CAN_TSTS_LPM1                          ((uint32_t)0x40000000)        /*!< Lowest Priority Flag for Mailbox 1 */
#define  CAN_TSTS_LPM2                          ((uint32_t)0x80000000)        /*!< Lowest Priority Flag for Mailbox 2 */

/*******************  Bit definition for CAN_RF0 register  *******************/
#define  CAN_RF0_RFP0                           ((uint8_t)0x03)               /*!< FIFO 0 Message Pending */
#define  CAN_RF0_RFFU0                          ((uint8_t)0x08)               /*!< FIFO 0 Full */
#define  CAN_RF0_RFOV0                          ((uint8_t)0x10)               /*!< FIFO 0 Overrun */
#define  CAN_RF0_RRFM0                          ((uint8_t)0x20)               /*!< Release FIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RF1 register  *******************/
#define  CAN_RF1_RFP1                           ((uint8_t)0x03)               /*!< FIFO 1 Message Pending */
#define  CAN_RF1_RFFU1                          ((uint8_t)0x08)               /*!< FIFO 1 Full */
#define  CAN_RF1_RFOV1                          ((uint8_t)0x10)               /*!< FIFO 1 Overrun */
#define  CAN_RF1_RRFM1                          ((uint8_t)0x20)               /*!< Release FIFO 1 Output Mailbox */

/********************  Bit definition for CAN_INTEN register  *******************/
#define  CAN_INTEN_TSMEIE                       ((uint32_t)0x00000001)        /*!< Transmit Mailbox Empty Interrupt Enable */
#define  CAN_INTEN_RFPIE0                       ((uint32_t)0x00000002)        /*!< FIFO Message Pending Interrupt Enable */
#define  CAN_INTEN_RFFUIE0                      ((uint32_t)0x00000004)        /*!< FIFO Full Interrupt Enable */
#define  CAN_INTEN_RFOVIE0                      ((uint32_t)0x00000008)        /*!< FIFO Overrun Interrupt Enable */
#define  CAN_INTEN_RFPIE1                       ((uint32_t)0x00000010)        /*!< FIFO Message Pending Interrupt Enable */
#define  CAN_INTEN_RFFUIE1                      ((uint32_t)0x00000020)        /*!< FIFO Full Interrupt Enable */
#define  CAN_INTEN_RFOVIE1                      ((uint32_t)0x00000040)        /*!< FIFO Overrun Interrupt Enable */
#define  CAN_INTEN_ERWIE                        ((uint32_t)0x00000100)        /*!< Error Warning Interrupt Enable */
#define  CAN_INTEN_ERPIE                        ((uint32_t)0x00000200)        /*!< Error Passive Interrupt Enable */
#define  CAN_INTEN_BUIE                         ((uint32_t)0x00000400)        /*!< Bus-Off Interrupt Enable */
#define  CAN_INTEN_ERCIE                        ((uint32_t)0x00000800)        /*!< Last Error Code Interrupt Enable */
#define  CAN_INTEN_ERIE                         ((uint32_t)0x00008000)        /*!< Error Interrupt Enable */
#define  CAN_INTEN_WKIE                         ((uint32_t)0x00010000)        /*!< Wakeup Interrupt Enable */
#define  CAN_INTEN_SAKIE                        ((uint32_t)0x00020000)        /*!< Sleep Interrupt Enable */

/********************  Bit definition for CAN_ESTS register  *******************/
#define  CAN_ESTS_ERWF                          ((uint32_t)0x00000001)        /*!< Error Warning Flag */
#define  CAN_ESTS_ERPF                          ((uint32_t)0x00000002)        /*!< Error Passive Flag */
#define  CAN_ESTS_BFF                           ((uint32_t)0x00000004)        /*!< Bus-Off Flag */

#define  CAN_ESTS_ERC                           ((uint32_t)0x00000070)        /*!< LEC[2:0] bits (Last Error Code) */
#define  CAN_ESTS_ERC_0                         ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  CAN_ESTS_ERC_1                         ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  CAN_ESTS_ERC_2                         ((uint32_t)0x00000040)        /*!< Bit 2 */

#define  CAN_ESTS_TEC                           ((uint32_t)0x00FF0000)        /*!< Least significant byte of the 9-bit Transmit Error Counter */
#define  CAN_ESTS_REC                           ((uint32_t)0xFF000000)        /*!< Receive Error Counter */

/*******************  Bit definition for CAN_BTMG register  ********************/
#define  CAN_BTMG_BRP                           ((uint32_t)0x000003FF)        /*!< Baud Rate Prescaler */
#define  CAN_BTMG_BS1                           ((uint32_t)0x000F0000)        /*!< Time Segment 1 */
#define  CAN_BTMG_BS2                           ((uint32_t)0x00700000)        /*!< Time Segment 2 */
#define  CAN_BTMG_SJW                           ((uint32_t)0x03000000)        /*!< Resynchronization Jump Width */
#define  CAN_BTMG_LBK                           ((uint32_t)0x40000000)        /*!< Loop Back Mode (Debug) */
#define  CAN_BTMG_SIL                           ((uint32_t)0x80000000)        /*!< Silent Mode */

/** Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define  CAN_TMI0_TRQ                           ((uint32_t)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TMI0_RTR                           ((uint32_t)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TMI0_IDT                           ((uint32_t)0x00000004)        /*!< Identifier Extension */
#define  CAN_TMI0_EID                           ((uint32_t)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_TMI0_SID                           ((uint32_t)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TDT0 register  *******************/
#define  CAN_TDT0_DLC                           ((uint32_t)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT0_TMEN                          ((uint32_t)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT0_TS                            ((uint32_t)0xFFFF0000)        /*!< Message Time Stamp */

/******************  Bit definition for CAN_TDL0 register  *******************/
#define  CAN_TDL0_D0                            ((uint32_t)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL0_D1                            ((uint32_t)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL0_D2                            ((uint32_t)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL0_D3                            ((uint32_t)0xFF000000)        /*!< Data byte 3 */

/******************  Bit definition for CAN_TDH0 register  *******************/
#define  CAN_TDH0_D4                            ((uint32_t)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH0_D5                            ((uint32_t)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH0_D6                            ((uint32_t)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH0_D7                            ((uint32_t)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_TMI1 register  *******************/
#define  CAN_TMI1_TRQ                           ((uint32_t)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TMI1_RTR                           ((uint32_t)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TMI1_IDT                           ((uint32_t)0x00000004)        /*!< Identifier Extension */
#define  CAN_TMI1_EID                           ((uint32_t)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_TMI1_SID                           ((uint32_t)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT1 register  ******************/
#define  CAN_TDT1_DLC                           ((uint32_t)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT1_TMEN                          ((uint32_t)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT1_TS                            ((uint32_t)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL1 register  ******************/
#define  CAN_TDL1_D0                            ((uint32_t)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL1_D1                            ((uint32_t)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL1_D2                            ((uint32_t)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL1_D3                            ((uint32_t)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH1 register  ******************/
#define  CAN_TDH1_D4                            ((uint32_t)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH1_D5                            ((uint32_t)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH1_D6                            ((uint32_t)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH1_D7                            ((uint32_t)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_TMI2 register  *******************/
#define  CAN_TMI2_TRQ                           ((uint32_t)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TMI2_RTR                           ((uint32_t)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TMI2_IDT                           ((uint32_t)0x00000004)        /*!< Identifier Extension */
#define  CAN_TMI2_EID                           ((uint32_t)0x001FFFF8)        /*!< Extended identifier */
#define  CAN_TMI2_SID                           ((uint32_t)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT2 register  ******************/
#define  CAN_TDT2_DLC                           ((uint32_t)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT2_TMEN                          ((uint32_t)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT2_TS                            ((uint32_t)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL2 register  ******************/
#define  CAN_TDL2_D0                            ((uint32_t)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL2_D1                            ((uint32_t)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL2_D2                            ((uint32_t)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL2_D3                            ((uint32_t)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH2 register  ******************/
#define  CAN_TDH2_D4                            ((uint32_t)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH2_D5                            ((uint32_t)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH2_D6                            ((uint32_t)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH2_D7                            ((uint32_t)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_RFI0 register  *******************/
#define  CAN_RFI0_RTR                           ((uint32_t)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_RFI0_IDT                           ((uint32_t)0x00000004)        /*!< Identifier Extension */
#define  CAN_RFI0_EID                           ((uint32_t)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_RFI0_SID                           ((uint32_t)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0 register  ******************/
#define  CAN_RDT0_DLC                           ((uint32_t)0x0000000F)        /*!< Data Length Code */
#define  CAN_RDT0_FID                           ((uint32_t)0x0000FF00)        /*!< Filter Match Index */
#define  CAN_RDT0_TS                            ((uint32_t)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL0 register  ******************/
#define  CAN_RDL0_D0                            ((uint32_t)0x000000FF)        /*!< Data byte 0 */
#define  CAN_RDL0_D1                            ((uint32_t)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_RDL0_D2                            ((uint32_t)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_RDL0_D3                            ((uint32_t)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH0 register  ******************/
#define  CAN_RDH0_D4                            ((uint32_t)0x000000FF)        /*!< Data byte 4 */
#define  CAN_RDH0_D5                            ((uint32_t)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_RDH0_D6                            ((uint32_t)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_RDH0_D7                            ((uint32_t)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_RFI1 register  *******************/
#define  CAN_RFI1_RTR                           ((uint32_t)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_RFI1_IDT                           ((uint32_t)0x00000004)        /*!< Identifier Extension */
#define  CAN_RFI1_EID                           ((uint32_t)0x001FFFF8)        /*!< Extended identifier */
#define  CAN_RFI1_SID                           ((uint32_t)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT1 register  ******************/
#define  CAN_RDT1_DLC                           ((uint32_t)0x0000000F)        /*!< Data Length Code */
#define  CAN_RDT1_FID                           ((uint32_t)0x0000FF00)        /*!< Filter Match Index */
#define  CAN_RDT1_TS                            ((uint32_t)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL1 register  ******************/
#define  CAN_RDL1_D0                            ((uint32_t)0x000000FF)        /*!< Data byte 0 */
#define  CAN_RDL1_D1                            ((uint32_t)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_RDL1_D2                            ((uint32_t)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_RDL1_D3                            ((uint32_t)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH1 register  ******************/
#define  CAN_RDH1_D4                            ((uint32_t)0x000000FF)        /*!< Data byte 4 */
#define  CAN_RDH1_D5                            ((uint32_t)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_RDH1_D6                            ((uint32_t)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_RDH1_D7                            ((uint32_t)0xFF000000)        /*!< Data byte 7 */

/** CAN filter registers */
/*******************  Bit definition for CAN_FM register  ********************/
#define  CAN_FM_FINT                            ((uint8_t)0x01)               /*!< Filter Init Mode */

/*******************  Bit definition for CAN_FM1 register  *******************/
#define  CAN_FM1_FMS                            ((uint16_t)0x3FFF)            /*!< Filter Mode */
#define  CAN_FM1_FMS0                           ((uint16_t)0x0001)            /*!< Filter Init Mode bit 0 */
#define  CAN_FM1_FMS1                           ((uint16_t)0x0002)            /*!< Filter Init Mode bit 1 */
#define  CAN_FM1_FMS2                           ((uint16_t)0x0004)            /*!< Filter Init Mode bit 2 */
#define  CAN_FM1_FMS3                           ((uint16_t)0x0008)            /*!< Filter Init Mode bit 3 */
#define  CAN_FM1_FMS4                           ((uint16_t)0x0010)            /*!< Filter Init Mode bit 4 */
#define  CAN_FM1_FMS5                           ((uint16_t)0x0020)            /*!< Filter Init Mode bit 5 */
#define  CAN_FM1_FMS6                           ((uint16_t)0x0040)            /*!< Filter Init Mode bit 6 */
#define  CAN_FM1_FMS7                           ((uint16_t)0x0080)            /*!< Filter Init Mode bit 7 */
#define  CAN_FM1_FMS8                           ((uint16_t)0x0100)            /*!< Filter Init Mode bit 8 */
#define  CAN_FM1_FMS9                           ((uint16_t)0x0200)            /*!< Filter Init Mode bit 9 */
#define  CAN_FM1_FMS10                          ((uint16_t)0x0400)            /*!< Filter Init Mode bit 10 */
#define  CAN_FM1_FMS11                          ((uint16_t)0x0800)            /*!< Filter Init Mode bit 11 */
#define  CAN_FM1_FMS12                          ((uint16_t)0x1000)            /*!< Filter Init Mode bit 12 */
#define  CAN_FM1_FMS13                          ((uint16_t)0x2000)            /*!< Filter Init Mode bit 13 */

/*******************  Bit definition for CAN_FS1 register  *******************/
#define  CAN_FS1_FBS                            ((uint16_t)0x3FFF)            /*!< Filter Scale Configuration */
#define  CAN_FS1_FBS0                           ((uint16_t)0x0001)            /*!< Filter Scale Configuration bit 0 */
#define  CAN_FS1_FBS1                           ((uint16_t)0x0002)            /*!< Filter Scale Configuration bit 1 */
#define  CAN_FS1_FBS2                           ((uint16_t)0x0004)            /*!< Filter Scale Configuration bit 2 */
#define  CAN_FS1_FBS3                           ((uint16_t)0x0008)            /*!< Filter Scale Configuration bit 3 */
#define  CAN_FS1_FBS4                           ((uint16_t)0x0010)            /*!< Filter Scale Configuration bit 4 */
#define  CAN_FS1_FBS5                           ((uint16_t)0x0020)            /*!< Filter Scale Configuration bit 5 */
#define  CAN_FS1_FBS6                           ((uint16_t)0x0040)            /*!< Filter Scale Configuration bit 6 */
#define  CAN_FS1_FBS7                           ((uint16_t)0x0080)            /*!< Filter Scale Configuration bit 7 */
#define  CAN_FS1_FBS8                           ((uint16_t)0x0100)            /*!< Filter Scale Configuration bit 8 */
#define  CAN_FS1_FBS9                           ((uint16_t)0x0200)            /*!< Filter Scale Configuration bit 9 */
#define  CAN_FS1_FBS10                          ((uint16_t)0x0400)            /*!< Filter Scale Configuration bit 10 */
#define  CAN_FS1_FBS11                          ((uint16_t)0x0800)            /*!< Filter Scale Configuration bit 11 */
#define  CAN_FS1_FBS12                          ((uint16_t)0x1000)            /*!< Filter Scale Configuration bit 12 */
#define  CAN_FS1_FBS13                          ((uint16_t)0x2000)            /*!< Filter Scale Configuration bit 13 */

/******************  Bit definition for CAN_FFA1 register  *******************/
#define  CAN_FFA1_FAF                           ((uint16_t)0x3FFF)            /*!< Filter FIFO Assignment */
#define  CAN_FFA1_FAF0                          ((uint16_t)0x0001)            /*!< Filter FIFO Assignment for Filter 0 */
#define  CAN_FFA1_FAF1                          ((uint16_t)0x0002)            /*!< Filter FIFO Assignment for Filter 1 */
#define  CAN_FFA1_FAF2                          ((uint16_t)0x0004)            /*!< Filter FIFO Assignment for Filter 2 */
#define  CAN_FFA1_FAF3                          ((uint16_t)0x0008)            /*!< Filter FIFO Assignment for Filter 3 */
#define  CAN_FFA1_FAF4                          ((uint16_t)0x0010)            /*!< Filter FIFO Assignment for Filter 4 */
#define  CAN_FFA1_FAF5                          ((uint16_t)0x0020)            /*!< Filter FIFO Assignment for Filter 5 */
#define  CAN_FFA1_FAF6                          ((uint16_t)0x0040)            /*!< Filter FIFO Assignment for Filter 6 */
#define  CAN_FFA1_FAF7                          ((uint16_t)0x0080)            /*!< Filter FIFO Assignment for Filter 7 */
#define  CAN_FFA1_FAF8                          ((uint16_t)0x0100)            /*!< Filter FIFO Assignment for Filter 8 */
#define  CAN_FFA1_FAF9                          ((uint16_t)0x0200)            /*!< Filter FIFO Assignment for Filter 9 */
#define  CAN_FFA1_FAF10                         ((uint16_t)0x0400)            /*!< Filter FIFO Assignment for Filter 10 */
#define  CAN_FFA1_FAF11                         ((uint16_t)0x0800)            /*!< Filter FIFO Assignment for Filter 11 */
#define  CAN_FFA1_FAF12                         ((uint16_t)0x1000)            /*!< Filter FIFO Assignment for Filter 12 */
#define  CAN_FFA1_FAF13                         ((uint16_t)0x2000)            /*!< Filter FIFO Assignment for Filter 13 */

/*******************  Bit definition for CAN_FA1 register  *******************/
#define  CAN_FA1_FEN                            ((uint16_t)0x3FFF)            /*!< Filter Active */
#define  CAN_FA1_FEN0                           ((uint16_t)0x0001)            /*!< Filter 0 Active */
#define  CAN_FA1_FEN1                           ((uint16_t)0x0002)            /*!< Filter 1 Active */
#define  CAN_FA1_FEN2                           ((uint16_t)0x0004)            /*!< Filter 2 Active */
#define  CAN_FA1_FEN3                           ((uint16_t)0x0008)            /*!< Filter 3 Active */
#define  CAN_FA1_FEN4                           ((uint16_t)0x0010)            /*!< Filter 4 Active */
#define  CAN_FA1_FEN5                           ((uint16_t)0x0020)            /*!< Filter 5 Active */
#define  CAN_FA1_FEN6                           ((uint16_t)0x0040)            /*!< Filter 6 Active */
#define  CAN_FA1_FEN7                           ((uint16_t)0x0080)            /*!< Filter 7 Active */
#define  CAN_FA1_FEN8                           ((uint16_t)0x0100)            /*!< Filter 8 Active */
#define  CAN_FA1_FEN9                           ((uint16_t)0x0200)            /*!< Filter 9 Active */
#define  CAN_FA1_FEN10                          ((uint16_t)0x0400)            /*!< Filter 10 Active */
#define  CAN_FA1_FEN11                          ((uint16_t)0x0800)            /*!< Filter 11 Active */
#define  CAN_FA1_FEN12                          ((uint16_t)0x1000)            /*!< Filter 12 Active */
#define  CAN_FA1_FEN13                          ((uint16_t)0x2000)            /*!< Filter 13 Active */

/*******************  Bit definition for CAN_FB0R1 register  *******************/
#define  CAN_FB0R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB0R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB0R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB0R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB0R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB0R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB0R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB0R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB0R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB0R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB0R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB0R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB0R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB0R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB0R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB0R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB0R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB0R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB0R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB0R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB0R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB0R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB0R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB0R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB0R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB0R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB0R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB0R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB0R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB0R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB0R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB0R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB1R1 register  *******************/
#define  CAN_FB1R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB1R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB1R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB1R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB1R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB1R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB1R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB1R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB1R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB1R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB1R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB1R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB1R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB1R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB1R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB1R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB1R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB1R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB1R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB1R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB1R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB1R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB1R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB1R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB1R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB1R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB1R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB1R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB1R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB1R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB1R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB1R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB2R1 register  *******************/
#define  CAN_FB2R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB2R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB2R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB2R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB2R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB2R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB2R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB2R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB2R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB2R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB2R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB2R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB2R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB2R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB2R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB2R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB2R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB2R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB2R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB2R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB2R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB2R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB2R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB2R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB2R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB2R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB2R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB2R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB2R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB2R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB2R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB2R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB3R1 register  *******************/
#define  CAN_FB3R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB3R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB3R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB3R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB3R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB3R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB3R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB3R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB3R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB3R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB3R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB3R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB3R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB3R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB3R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB3R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB3R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB3R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB3R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB3R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB3R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB3R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB3R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB3R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB3R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB3R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB3R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB3R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB3R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB3R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB3R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB3R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB4R1 register  *******************/
#define  CAN_FB4R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB4R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB4R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB4R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB4R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB4R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB4R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB4R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB4R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB4R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB4R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB4R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB4R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB4R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB4R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB4R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB4R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB4R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB4R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB4R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB4R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB4R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB4R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB4R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB4R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB4R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB4R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB4R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB4R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB4R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB4R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB4R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB5R1 register  *******************/
#define  CAN_FB5R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB5R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB5R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB5R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB5R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB5R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB5R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB5R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB5R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB5R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB5R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB5R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB5R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB5R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB5R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB5R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB5R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB5R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB5R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB5R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB5R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB5R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB5R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB5R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB5R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB5R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB5R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB5R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB5R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB5R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB5R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB5R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB6R1 register  *******************/
#define  CAN_FB6R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB6R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB6R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB6R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB6R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB6R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB6R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB6R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB6R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB6R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB6R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB6R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB6R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB6R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB6R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB6R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB6R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB6R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB6R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB6R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB6R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB6R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB6R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB6R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB6R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB6R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB6R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB6R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB6R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB6R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB6R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB6R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB7R1 register  *******************/
#define  CAN_FB7R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB7R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB7R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB7R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB7R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB7R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB7R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB7R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB7R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB7R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB7R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB7R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB7R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB7R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB7R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB7R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB7R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB7R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB7R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB7R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB7R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB7R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB7R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB7R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB7R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB7R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB7R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB7R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB7R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB7R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB7R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB7R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB8R1 register  *******************/
#define  CAN_FB8R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB8R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB8R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB8R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB8R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB8R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB8R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB8R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB8R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB8R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB8R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB8R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB8R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB8R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB8R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB8R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB8R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB8R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB8R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB8R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB8R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB8R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB8R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB8R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB8R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB8R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB8R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB8R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB8R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB8R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB8R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB8R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB9R1 register  *******************/
#define  CAN_FB9R1_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB9R1_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB9R1_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB9R1_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB9R1_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB9R1_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB9R1_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB9R1_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB9R1_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB9R1_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB9R1_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB9R1_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB9R1_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB9R1_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB9R1_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB9R1_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB9R1_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB9R1_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB9R1_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB9R1_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB9R1_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB9R1_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB9R1_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB9R1_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB9R1_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB9R1_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB9R1_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB9R1_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB9R1_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB9R1_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB9R1_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB9R1_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB10R1 register  ******************/
#define  CAN_FB10R1_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB10R1_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB10R1_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB10R1_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB10R1_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB10R1_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB10R1_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB10R1_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB10R1_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB10R1_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB10R1_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB10R1_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB10R1_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB10R1_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB10R1_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB10R1_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB10R1_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB10R1_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB10R1_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB10R1_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB10R1_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB10R1_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB10R1_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB10R1_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB10R1_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB10R1_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB10R1_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB10R1_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB10R1_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB10R1_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB10R1_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB10R1_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB11R1 register  ******************/
#define  CAN_FB11R1_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB11R1_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB11R1_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB11R1_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB11R1_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB11R1_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB11R1_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB11R1_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB11R1_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB11R1_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB11R1_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB11R1_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB11R1_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB11R1_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB11R1_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB11R1_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB11R1_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB11R1_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB11R1_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB11R1_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB11R1_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB11R1_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB11R1_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB11R1_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB11R1_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB11R1_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB11R1_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB11R1_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB11R1_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB11R1_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB11R1_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB11R1_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB12R1 register  ******************/
#define  CAN_FB12R1_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB12R1_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB12R1_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB12R1_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB12R1_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB12R1_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB12R1_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB12R1_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB12R1_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB12R1_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB12R1_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB12R1_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB12R1_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB12R1_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB12R1_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB12R1_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB12R1_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB12R1_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB12R1_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB12R1_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB12R1_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB12R1_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB12R1_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB12R1_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB12R1_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB12R1_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB12R1_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB12R1_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB12R1_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB12R1_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB12R1_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB12R1_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB13R1 register  ******************/
#define  CAN_FB13R1_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB13R1_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB13R1_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB13R1_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB13R1_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB13R1_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB13R1_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB13R1_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB13R1_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB13R1_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB13R1_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB13R1_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB13R1_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB13R1_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB13R1_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB13R1_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB13R1_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB13R1_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB13R1_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB13R1_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB13R1_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB13R1_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB13R1_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB13R1_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB13R1_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB13R1_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB13R1_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB13R1_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB13R1_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB13R1_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB13R1_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB13R1_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB0R2 register  *******************/
#define  CAN_FB0R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB0R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB0R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB0R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB0R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB0R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB0R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB0R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB0R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB0R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB0R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB0R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB0R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB0R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB0R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB0R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB0R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB0R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB0R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB0R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB0R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB0R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB0R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB0R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB0R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB0R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB0R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB0R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB0R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB0R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB0R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB0R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB1R2 register  *******************/
#define  CAN_FB1R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB1R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB1R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB1R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB1R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB1R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB1R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB1R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB1R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB1R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB1R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB1R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB1R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB1R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB1R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB1R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB1R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB1R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB1R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB1R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB1R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB1R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB1R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB1R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB1R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB1R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB1R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB1R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB1R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB1R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB1R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB1R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB2R2 register  *******************/
#define  CAN_FB2R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB2R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB2R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB2R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB2R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB2R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB2R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB2R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB2R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB2R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB2R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB2R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB2R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB2R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB2R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB2R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB2R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB2R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB2R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB2R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB2R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB2R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB2R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB2R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB2R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB2R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB2R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB2R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB2R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB2R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB2R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB2R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB3R2 register  *******************/
#define  CAN_FB3R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB3R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB3R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB3R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB3R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB3R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB3R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB3R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB3R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB3R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB3R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB3R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB3R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB3R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB3R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB3R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB3R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB3R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB3R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB3R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB3R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB3R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB3R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB3R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB3R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB3R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB3R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB3R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB3R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB3R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB3R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB3R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB4R2 register  *******************/
#define  CAN_FB4R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB4R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB4R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB4R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB4R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB4R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB4R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB4R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB4R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB4R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB4R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB4R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB4R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB4R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB4R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB4R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB4R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB4R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB4R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB4R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB4R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB4R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB4R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB4R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB4R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB4R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB4R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB4R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB4R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB4R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB4R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB4R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB5R2 register  *******************/
#define  CAN_FB5R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB5R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB5R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB5R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB5R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB5R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB5R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB5R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB5R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB5R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB5R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB5R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB5R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB5R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB5R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB5R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB5R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB5R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB5R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB5R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB5R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB5R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB5R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB5R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB5R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB5R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB5R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB5R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB5R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB5R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB5R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB5R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB6R2 register  *******************/
#define  CAN_FB6R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB6R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB6R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB6R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB6R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB6R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB6R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB6R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB6R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB6R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB6R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB6R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB6R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB6R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB6R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB6R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB6R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB6R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB6R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB6R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB6R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB6R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB6R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB6R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB6R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB6R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB6R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB6R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB6R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB6R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB6R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB6R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB7R2 register  *******************/
#define  CAN_FB7R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB7R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB7R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB7R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB7R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB7R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB7R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB7R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB7R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB7R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB7R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB7R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB7R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB7R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB7R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB7R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB7R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB7R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB7R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB7R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB7R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB7R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB7R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB7R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB7R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB7R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB7R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB7R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB7R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB7R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB7R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB7R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB8R2 register  *******************/
#define  CAN_FB8R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB8R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB8R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB8R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB8R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB8R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB8R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB8R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB8R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB8R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB8R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB8R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB8R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB8R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB8R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB8R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB8R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB8R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB8R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB8R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB8R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB8R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB8R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB8R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB8R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB8R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB8R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB8R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB8R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB8R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB8R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB8R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB9R2 register  *******************/
#define  CAN_FB9R2_FD0                          ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB9R2_FD1                          ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB9R2_FD2                          ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB9R2_FD3                          ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB9R2_FD4                          ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB9R2_FD5                          ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB9R2_FD6                          ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB9R2_FD7                          ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB9R2_FD8                          ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB9R2_FD9                          ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB9R2_FD10                         ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB9R2_FD11                         ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB9R2_FD12                         ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB9R2_FD13                         ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB9R2_FD14                         ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB9R2_FD15                         ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB9R2_FD16                         ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB9R2_FD17                         ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB9R2_FD18                         ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB9R2_FD19                         ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB9R2_FD20                         ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB9R2_FD21                         ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB9R2_FD22                         ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB9R2_FD23                         ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB9R2_FD24                         ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB9R2_FD25                         ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB9R2_FD26                         ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB9R2_FD27                         ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB9R2_FD28                         ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB9R2_FD29                         ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB9R2_FD30                         ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB9R2_FD31                         ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB10R2 register  ******************/
#define  CAN_FB10R2_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB10R2_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB10R2_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB10R2_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB10R2_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB10R2_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB10R2_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB10R2_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB10R2_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB10R2_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB10R2_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB10R2_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB10R2_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB10R2_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB10R2_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB10R2_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB10R2_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB10R2_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB10R2_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB10R2_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB10R2_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB10R2_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB10R2_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB10R2_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB10R2_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB10R2_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB10R2_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB10R2_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB10R2_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB10R2_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB10R2_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB10R2_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB11R2 register  ******************/
#define  CAN_FB11R2_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB11R2_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB11R2_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB11R2_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB11R2_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB11R2_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB11R2_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB11R2_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB11R2_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB11R2_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB11R2_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB11R2_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB11R2_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB11R2_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB11R2_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB11R2_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB11R2_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB11R2_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB11R2_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB11R2_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB11R2_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB11R2_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB11R2_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB11R2_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB11R2_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB11R2_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB11R2_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB11R2_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB11R2_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB11R2_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB11R2_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB11R2_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB12R2 register  ******************/
#define  CAN_FB12R2_FD0                         ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB12R2_FD1                         ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB12R2_FD2                         ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB12R2_FD3                         ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB12R2_FD4                         ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB12R2_FD5                         ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB12R2_FD6                         ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB12R2_FD7                         ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB12R2_FD8                         ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB12R2_FD9                         ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB12R2_FD10                        ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB12R2_FD11                        ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB12R2_FD12                        ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB12R2_FD13                        ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB12R2_FD14                        ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB12R2_FD15                        ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB12R2_FD16                        ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB12R2_FD17                        ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB12R2_FD18                        ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB12R2_FD19                        ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB12R2_FD20                        ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB12R2_FD21                        ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB12R2_FD22                        ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB12R2_FD23                        ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB12R2_FD24                        ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB12R2_FD25                        ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB12R2_FD26                        ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB12R2_FD27                        ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB12R2_FD28                        ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB12R2_FD29                        ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB12R2_FD30                        ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB12R2_FD31                        ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/*******************  Bit definition for CAN_FB13R2 register  ******************/
#define  CAN_FB13R2_FD0                        ((uint32_t)0x00000001)        /*!< Filter bit 0 */
#define  CAN_FB13R2_FD1                        ((uint32_t)0x00000002)        /*!< Filter bit 1 */
#define  CAN_FB13R2_FD2                        ((uint32_t)0x00000004)        /*!< Filter bit 2 */
#define  CAN_FB13R2_FD3                        ((uint32_t)0x00000008)        /*!< Filter bit 3 */
#define  CAN_FB13R2_FD4                        ((uint32_t)0x00000010)        /*!< Filter bit 4 */
#define  CAN_FB13R2_FD5                        ((uint32_t)0x00000020)        /*!< Filter bit 5 */
#define  CAN_FB13R2_FD6                        ((uint32_t)0x00000040)        /*!< Filter bit 6 */
#define  CAN_FB13R2_FD7                        ((uint32_t)0x00000080)        /*!< Filter bit 7 */
#define  CAN_FB13R2_FD8                        ((uint32_t)0x00000100)        /*!< Filter bit 8 */
#define  CAN_FB13R2_FD9                        ((uint32_t)0x00000200)        /*!< Filter bit 9 */
#define  CAN_FB13R2_FD10                       ((uint32_t)0x00000400)        /*!< Filter bit 10 */
#define  CAN_FB13R2_FD11                       ((uint32_t)0x00000800)        /*!< Filter bit 11 */
#define  CAN_FB13R2_FD12                       ((uint32_t)0x00001000)        /*!< Filter bit 12 */
#define  CAN_FB13R2_FD13                       ((uint32_t)0x00002000)        /*!< Filter bit 13 */
#define  CAN_FB13R2_FD14                       ((uint32_t)0x00004000)        /*!< Filter bit 14 */
#define  CAN_FB13R2_FD15                       ((uint32_t)0x00008000)        /*!< Filter bit 15 */
#define  CAN_FB13R2_FD16                       ((uint32_t)0x00010000)        /*!< Filter bit 16 */
#define  CAN_FB13R2_FD17                       ((uint32_t)0x00020000)        /*!< Filter bit 17 */
#define  CAN_FB13R2_FD18                       ((uint32_t)0x00040000)        /*!< Filter bit 18 */
#define  CAN_FB13R2_FD19                       ((uint32_t)0x00080000)        /*!< Filter bit 19 */
#define  CAN_FB13R2_FD20                       ((uint32_t)0x00100000)        /*!< Filter bit 20 */
#define  CAN_FB13R2_FD21                       ((uint32_t)0x00200000)        /*!< Filter bit 21 */
#define  CAN_FB13R2_FD22                       ((uint32_t)0x00400000)        /*!< Filter bit 22 */
#define  CAN_FB13R2_FD23                       ((uint32_t)0x00800000)        /*!< Filter bit 23 */
#define  CAN_FB13R2_FD24                       ((uint32_t)0x01000000)        /*!< Filter bit 24 */
#define  CAN_FB13R2_FD25                       ((uint32_t)0x02000000)        /*!< Filter bit 25 */
#define  CAN_FB13R2_FD26                       ((uint32_t)0x04000000)        /*!< Filter bit 26 */
#define  CAN_FB13R2_FD27                       ((uint32_t)0x08000000)        /*!< Filter bit 27 */
#define  CAN_FB13R2_FD28                       ((uint32_t)0x10000000)        /*!< Filter bit 28 */
#define  CAN_FB13R2_FD29                       ((uint32_t)0x20000000)        /*!< Filter bit 29 */
#define  CAN_FB13R2_FD30                       ((uint32_t)0x40000000)        /*!< Filter bit 30 */
#define  CAN_FB13R2_FD31                       ((uint32_t)0x80000000)        /*!< Filter bit 31 */

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface                         */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for SPI_CTRL1 register  ********************/
#define  SPI_CTRL1_CPHA                         ((uint16_t)0x0001)            /*!< Clock Phase */
#define  SPI_CTRL1_CPOL                         ((uint16_t)0x0002)            /*!< Clock Polarity */
#define  SPI_CTRL1_MSTEN                        ((uint16_t)0x0004)            /*!< Master Selection */

#define  SPI_CTRL1_MCLKP                        ((uint16_t)0x0038)            /*!< BR[2:0] bits (Baud Rate Control) */
#define  SPI_CTRL1_MCLKP_0                      ((uint16_t)0x0008)            /*!< Bit 0 */
#define  SPI_CTRL1_MCLKP_1                      ((uint16_t)0x0010)            /*!< Bit 1 */
#define  SPI_CTRL1_MCLKP_2                      ((uint16_t)0x0020)            /*!< Bit 2 */

#define  SPI_CTRL1_SPIEN                        ((uint16_t)0x0040)            /*!< SPI Enable */
#define  SPI_CTRL1_LSBEN                        ((uint16_t)0x0080)            /*!< Frame Format */
#define  SPI_CTRL1_ISS                          ((uint16_t)0x0100)            /*!< Internal slave select */
#define  SPI_CTRL1_SWNSSEN                      ((uint16_t)0x0200)            /*!< Software slave management */
#define  SPI_CTRL1_RONLY                        ((uint16_t)0x0400)            /*!< Receive only */
#define  SPI_CTRL1_DFF16                        ((uint16_t)0x0800)            /*!< Data Frame Format */
#define  SPI_CTRL1_CTN                          ((uint16_t)0x1000)            /*!< Transmit CRC next */
#define  SPI_CTRL1_CCE                          ((uint16_t)0x2000)            /*!< Hardware CRC calculation enable */
#define  SPI_CTRL1_BDOE                         ((uint16_t)0x4000)            /*!< Output enable in bidirectional mode */
#define  SPI_CTRL1_BDMODE                       ((uint16_t)0x8000)            /*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CTRL2 register  ********************/
#define  SPI_CTRL2_DMAREN                       ((uint16_t)0x0001)            /*!< Rx Buffer DMA Enable */
#define  SPI_CTRL2_DMATEN                       ((uint16_t)0x0002)            /*!< Tx Buffer DMA Enable */
#define  SPI_CTRL2_NSSOE                        ((uint16_t)0x0004)            /*!< SS Output Enable */
#define  SPI_CTRL2_ERRIE                        ((uint16_t)0x0020)            /*!< Error Interrupt Enable */
#define  SPI_CTRL2_RNEIE                        ((uint16_t)0x0040)            /*!< RX buffer Not Empty Interrupt Enable */
#define  SPI_CTRL2_TEIE                         ((uint16_t)0x0080)            /*!< Tx buffer Empty Interrupt Enable */
#define  SPI_CTRL2_MCLKP_EXT                    ((uint16_t)0x0100)            /*!< BR[3] bits (Baud Rate Control) */
#define  SPI_CTRL2_MCLKP_3                      ((uint16_t)0x0100)            /*!< Bit 3 */

/********************  Bit definition for SPI_STS register  ********************/
#define  SPI_STS_RNE                            ((uint8_t)0x01)               /*!< Receive buffer Not Empty */
#define  SPI_STS_TE                             ((uint8_t)0x02)               /*!< Transmit buffer Empty */
#define  SPI_STS_I2SCS                          ((uint8_t)0x04)               /*!< Channel side */
#define  SPI_STS_UDR                            ((uint8_t)0x08)               /*!< Underrun flag */
#define  SPI_STS_CERR                           ((uint8_t)0x10)               /*!< CRC Error flag */
#define  SPI_STS_MODF                           ((uint8_t)0x20)               /*!< Mode fault */
#define  SPI_STS_OVR                            ((uint8_t)0x40)               /*!< Overrun flag */
#define  SPI_STS_BSY                            ((uint8_t)0x80)               /*!< Busy flag */

/********************  Bit definition for SPI_DT register  ********************/
#define  SPI_DT_DT                              ((uint16_t)0xFFFF)            /*!< Data Register */

/*******************  Bit definition for SPI_CPOLY register  ******************/
#define  SPI_CPOLY_CPOLY                        ((uint16_t)0xFFFF)            /*!< CRC polynomial register */

/******************  Bit definition for SPI_RCRC register  ******************/
#define  SPI_RCRC_RCRC                          ((uint16_t)0xFFFF)            /*!< Rx CRC Register */

/******************  Bit definition for SPI_TCRC register  ******************/
#define  SPI_TCRC_TCRC                          ((uint16_t)0xFFFF)            /*!< Tx CRC Register */

/******************  Bit definition for SPI_I2SCTRL register  *****************/
#define  SPI_I2SCTRL_CHLEN                      ((uint16_t)0x0001)            /*!< Channel length (number of bits per audio channel) */

#define  SPI_I2SCTRL_DLEN                       ((uint16_t)0x0006)            /*!< DATLEN[1:0] bits (Data length to be transferred) */
#define  SPI_I2SCTRL_DLEN_0                     ((uint16_t)0x0002)            /*!< Bit 0 */
#define  SPI_I2SCTRL_DLEN_1                     ((uint16_t)0x0004)            /*!< Bit 1 */

#define  SPI_I2SCTRL_CPOL                       ((uint16_t)0x0008)            /*!< steady state clock polarity */

#define  SPI_I2SCTRL_I2SAP                      ((uint16_t)0x0030)            /*!< I2SSTD[1:0] bits (I2S standard selection) */
#define  SPI_I2SCTRL_I2SAP_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  SPI_I2SCTRL_I2SAP_1                    ((uint16_t)0x0020)            /*!< Bit 1 */

#define  SPI_I2SCTRL_PCMSYNCSEL                 ((uint16_t)0x0080)            /*!< PCM frame synchronization */

#define  SPI_I2SCTRL_I2SMOD                     ((uint16_t)0x0300)            /*!< I2SCFG[1:0] bits (I2S configuration mode) */
#define  SPI_I2SCTRL_I2SMOD_0                   ((uint16_t)0x0100)            /*!< Bit 0 */
#define  SPI_I2SCTRL_I2SMOD_1                   ((uint16_t)0x0200)            /*!< Bit 1 */

#define  SPI_I2SCTRL_I2SEN                      ((uint16_t)0x0400)            /*!< I2S Enable */
#define  SPI_I2SCTRL_I2SSEL                     ((uint16_t)0x0800)            /*!< I2S mode selection */

/******************  Bit definition for SPI_I2SCLKP register  *******************/
#define  SPI_I2SCLKP_I2SDIV                     ((uint16_t)0x0CFF)            /*!< I2S Linear prescaler */
#define  SPI_I2SCLKP_I2SODD                     ((uint16_t)0x0100)            /*!< Odd factor for the prescaler */
#define  SPI_I2SCLKP_I2SMCLKOE                  ((uint16_t)0x0200)            /*!< Master Clock Output Enable */




/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for I2C_CTRL1 register  ********************/
#define  I2C_CTRL1_PEN                          ((uint16_t)0x0001)            /*!< Peripheral Enable */
#define  I2C_CTRL1_SMBMODE                      ((uint16_t)0x0002)            /*!< SMBus Mode */
#define  I2C_CTRL1_SMBTYPE                      ((uint16_t)0x0008)            /*!< SMBus Type */
#define  I2C_CTRL1_ARPEN                        ((uint16_t)0x0010)            /*!< ARP Enable */
#define  I2C_CTRL1_PECEN                        ((uint16_t)0x0020)            /*!< PEC Enable */
#define  I2C_CTRL1_GCEN                         ((uint16_t)0x0040)            /*!< General Call Enable */
#define  I2C_CTRL1_NOCLKSTRETCH                 ((uint16_t)0x0080)            /*!< Clock Stretching Disable (Slave mode) */
#define  I2C_CTRL1_STARTGEN                     ((uint16_t)0x0100)            /*!< Start Generation */
#define  I2C_CTRL1_STOPGEN                      ((uint16_t)0x0200)            /*!< Stop Generation */
#define  I2C_CTRL1_ACKEN                        ((uint16_t)0x0400)            /*!< Acknowledge Enable */
#define  I2C_CTRL1_POSEN                        ((uint16_t)0x0800)            /*!< Acknowledge/PEC Position (for data reception) */
#define  I2C_CTRL1_PECTRA                       ((uint16_t)0x1000)            /*!< Packet Error Checking */
#define  I2C_CTRL1_SMBALERT                     ((uint16_t)0x2000)            /*!< SMBus Alert */
#define  I2C_CTRL1_SWRESET                      ((uint16_t)0x8000)            /*!< Software Reset */

/*******************  Bit definition for I2C_CTRL2 register  ********************/
#define  I2C_CTRL2_CLKFREQ                      ((uint16_t)0x003F)            /*!< FREQ[7:0] bits (Peripheral Clock Frequency) */
#define  I2C_CTRL2_CLKFREQ_B0                   ((uint16_t)0x0001)            /*!< Bit 0 */
#define  I2C_CTRL2_CLKFREQ_B1                   ((uint16_t)0x0002)            /*!< Bit 1 */
#define  I2C_CTRL2_CLKFREQ_B2                   ((uint16_t)0x0004)            /*!< Bit 2 */
#define  I2C_CTRL2_CLKFREQ_B3                   ((uint16_t)0x0008)            /*!< Bit 3 */
#define  I2C_CTRL2_CLKFREQ_B4                   ((uint16_t)0x0010)            /*!< Bit 4 */
#define  I2C_CTRL2_CLKFREQ_B5                   ((uint16_t)0x0020)            /*!< Bit 5 */
#define  I2C_CTRL2_CLKFREQ_B6                   ((uint16_t)0x0040)            /*!< Bit 6 */
#define  I2C_CTRL2_CLKFREQ_B7                   ((uint16_t)0x0080)            /*!< Bit 7 */

#define  I2C_CTRL2_ERRITEN                      ((uint16_t)0x0100)            /*!< Error Interrupt Enable */
#define  I2C_CTRL2_EVTITEN                      ((uint16_t)0x0200)            /*!< Event Interrupt Enable */
#define  I2C_CTRL2_BUFITEN                      ((uint16_t)0x0400)            /*!< Buffer Interrupt Enable */
#define  I2C_CTRL2_DMAEN                        ((uint16_t)0x0800)            /*!< DMA Requests Enable */
#define  I2C_CTRL2_DMALAST                      ((uint16_t)0x1000)            /*!< DMA Last Transfer */

/*******************  Bit definition for I2C_OADDR1 register  *******************/
#define  I2C_OADDR1_ADDR1_7                     ((uint16_t)0x00FE)            /*!< Interface Address */
#define  I2C_OADDR1_ADDR8_9                     ((uint16_t)0x0300)            /*!< Interface Address */

#define  I2C_OADDR1_ADDR_B0                     ((uint16_t)0x0001)            /*!< Bit 0 */
#define  I2C_OADDR1_ADDR_B1                     ((uint16_t)0x0002)            /*!< Bit 1 */
#define  I2C_OADDR1_ADDR_B2                     ((uint16_t)0x0004)            /*!< Bit 2 */
#define  I2C_OADDR1_ADDR_B3                     ((uint16_t)0x0008)            /*!< Bit 3 */
#define  I2C_OADDR1_ADDR_B4                     ((uint16_t)0x0010)            /*!< Bit 4 */
#define  I2C_OADDR1_ADDR_B5                     ((uint16_t)0x0020)            /*!< Bit 5 */
#define  I2C_OADDR1_ADDR_B6                     ((uint16_t)0x0040)            /*!< Bit 6 */
#define  I2C_OADDR1_ADDR_B7                     ((uint16_t)0x0080)            /*!< Bit 7 */
#define  I2C_OADDR1_ADDR_B8                     ((uint16_t)0x0100)            /*!< Bit 8 */
#define  I2C_OADDR1_ADDR_B9                     ((uint16_t)0x0200)            /*!< Bit 9 */

#define  I2C_OADDR1_ADDRMODE                    ((uint16_t)0x8000)            /*!< Addressing Mode (Slave mode) */

/*******************  Bit definition for I2C_OADDR2 register  *******************/
#define  I2C_OADDR2_DUALEN                      ((uint8_t)0x01)               /*!< Dual addressing mode enable */
#define  I2C_OADDR2_ADDR2                       ((uint8_t)0xFE)               /*!< Interface address */

/********************  Bit definition for I2C_DT register  ********************/
#define  I2C_DT_DT                              ((uint8_t)0xFF)               /*!< 8-bit Data Register */

/*******************  Bit definition for I2C_STS1 register  ********************/
#define  I2C_STS1_STARTF                        ((uint16_t)0x0001)            /*!< Start Bit (Master mode) */
#define  I2C_STS1_ADDRF                         ((uint16_t)0x0002)            /*!< Address sent (master mode)/matched (slave mode) */
#define  I2C_STS1_BTFF                          ((uint16_t)0x0004)            /*!< Byte Transfer Finished */
#define  I2C_STS1_ADDR10F                       ((uint16_t)0x0008)            /*!< 10-bit header sent (Master mode) */
#define  I2C_STS1_STOPF                         ((uint16_t)0x0010)            /*!< Stop detection (Slave mode) */
#define  I2C_STS1_RDNE                          ((uint16_t)0x0040)            /*!< Data Register not Empty (receivers) */
#define  I2C_STS1_TDE                           ((uint16_t)0x0080)            /*!< Data Register Empty (transmitters) */
#define  I2C_STS1_BUSERR                        ((uint16_t)0x0100)            /*!< Bus Error */
#define  I2C_STS1_ARLOST                        ((uint16_t)0x0200)            /*!< Arbitration Lost (master mode) */
#define  I2C_STS1_ACKFAIL                       ((uint16_t)0x0400)            /*!< Acknowledge Failure */
#define  I2C_STS1_OVRUN                         ((uint16_t)0x0800)            /*!< Overrun/Underrun */
#define  I2C_STS1_PECERR                        ((uint16_t)0x1000)            /*!< PEC Error in reception */
#define  I2C_STS1_TIMOUT                        ((uint16_t)0x4000)            /*!< Timeout or Tlow Error */
#define  I2C_STS1_SMBALERTF                     ((uint16_t)0x8000)            /*!< SMBus Alert */

/*******************  Bit definition for I2C_STS2 register  ********************/
#define  I2C_STS2_MSF                           ((uint16_t)0x0001)            /*!< Master/Slave */
#define  I2C_STS2_BUSYF                         ((uint16_t)0x0002)            /*!< Bus Busy */
#define  I2C_STS2_TRF                           ((uint16_t)0x0004)            /*!< Transmitter/Receiver */
#define  I2C_STS2_GCADDRF                       ((uint16_t)0x0010)            /*!< General Call Address (Slave mode) */
#define  I2C_STS2_SMBDEFTADDRF                  ((uint16_t)0x0020)            /*!< SMBus Device Default Address (Slave mode) */
#define  I2C_STS2_SMBHOSTADDRF                  ((uint16_t)0x0040)            /*!< SMBus Host Header (Slave mode) */
#define  I2C_STS2_DUALF                         ((uint16_t)0x0080)            /*!< Dual Flag (Slave mode) */
#define  I2C_STS2_PECVAL                        ((uint16_t)0xFF00)            /*!< Packet Error Checking Register */

/*******************  Bit definition for I2C_CLKCTRL register  ********************/
#define  I2C_CLKCTRL_CLKCTRL                    ((uint16_t)0x0FFF)            /*!< Clock Control Register in Fast/Standard mode (Master mode) */
#define  I2C_CLKCTRL_FMDUTY                     ((uint16_t)0x4000)            /*!< Fast Mode Duty Cycle */
#define  I2C_CLKCTRL_FSMODE                     ((uint16_t)0x8000)            /*!< I2C Master Mode Selection */

/******************  Bit definition for I2C_TMRISE register  *******************/
#define  I2C_TMRISE_TMRISE                      ((uint8_t)0x3F)               /*!< Maximum Rise Time in Fast/Standard mode (Master mode) */

/******************************************************************************/
/*                                                                            */
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for USART_STS register  *******************/
#define  USART_STS_PERR                         ((uint16_t)0x0001)            /*!< Parity Error */
#define  USART_STS_FERR                         ((uint16_t)0x0002)            /*!< Framing Error */
#define  USART_STS_NERR                         ((uint16_t)0x0004)            /*!< Noise Error Flag */
#define  USART_STS_ORERR                        ((uint16_t)0x0008)            /*!< OverRun Error */
#define  USART_STS_IDLEF                        ((uint16_t)0x0010)            /*!< IDLE line detected */
#define  USART_STS_RDNE                         ((uint16_t)0x0020)            /*!< Read Data Register Not Empty */
#define  USART_STS_TRAC                         ((uint16_t)0x0040)            /*!< Transmission Complete */
#define  USART_STS_TDE                          ((uint16_t)0x0080)            /*!< Transmit Data Register Empty */
#define  USART_STS_LBDF                         ((uint16_t)0x0100)            /*!< LIN Break Detection Flag */
#define  USART_STS_CTSF                         ((uint16_t)0x0200)            /*!< CTS Flag */

/*******************  Bit definition for USART_DT register  *******************/
#define  USART_DT_DT                            ((uint16_t)0x01FF)            /*!< Data value */

/******************  Bit definition for USART_BAUDR register  *******************/
#define  USART_BAUDR_DIV_Decimal                ((uint16_t)0x000F)            /*!< Fraction of USARTDIV */
#define  USART_BAUDR_DIV_Integer                ((uint16_t)0xFFF0)            /*!< Mantissa of USARTDIV */

/******************  Bit definition for USART_CTRL1 register  *******************/
#define  USART_CTRL1_SBRK                       ((uint16_t)0x0001)            /*!< Send Break */
#define  USART_CTRL1_RECMUTE                    ((uint16_t)0x0002)            /*!< Receiver wakeup */
#define  USART_CTRL1_REN                        ((uint16_t)0x0004)            /*!< Receiver Enable */
#define  USART_CTRL1_TEN                        ((uint16_t)0x0008)            /*!< Transmitter Enable */
#define  USART_CTRL1_IDLEIEN                    ((uint16_t)0x0010)            /*!< IDLE Interrupt Enable */
#define  USART_CTRL1_RDNEIEN                    ((uint16_t)0x0020)            /*!< RXNE Interrupt Enable */
#define  USART_CTRL1_TRACIEN                    ((uint16_t)0x0040)            /*!< Transmission Complete Interrupt Enable */
#define  USART_CTRL1_TDEIEN                     ((uint16_t)0x0080)            /*!< PE Interrupt Enable */
#define  USART_CTRL1_PERRIEN                    ((uint16_t)0x0100)            /*!< PE Interrupt Enable */
#define  USART_CTRL1_PSEL                       ((uint16_t)0x0200)            /*!< Parity Selection */
#define  USART_CTRL1_PCEN                       ((uint16_t)0x0400)            /*!< Parity Control Enable */
#define  USART_CTRL1_WUMODE                     ((uint16_t)0x0800)            /*!< Wakeup method */
#define  USART_CTRL1_LEN                        ((uint16_t)0x1000)            /*!< Word length */
#define  USART_CTRL1_UEN                        ((uint16_t)0x2000)            /*!< USART Enable */
#define  USART_CTRL1_OVER8                      ((uint16_t)0x8000)            /*!< USART Oversmapling 8-bits */

/******************  Bit definition for USART_CTRL2 register  *******************/
#define  USART_CTRL2_ADDR                       ((uint16_t)0x000F)            /*!< Address of the USART node */
#define  USART_CTRL2_LBDLEN                     ((uint16_t)0x0020)            /*!< LIN Break Detection Length */
#define  USART_CTRL2_LBDIEN                     ((uint16_t)0x0040)            /*!< LIN Break Detection Interrupt Enable */
#define  USART_CTRL2_LBCP                       ((uint16_t)0x0100)            /*!< Last Bit Clock pulse */
#define  USART_CTRL2_CLKPHA                     ((uint16_t)0x0200)            /*!< Clock Phase */
#define  USART_CTRL2_CLKPOL                     ((uint16_t)0x0400)            /*!< Clock Polarity */
#define  USART_CTRL2_CLKEN                      ((uint16_t)0x0800)            /*!< Clock Enable */

#define  USART_CTRL2_STOPB                      ((uint16_t)0x3000)            /*!< STOP[1:0] bits (STOP bits) */
#define  USART_CTRL2_STOP_B0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  USART_CTRL2_STOP_B1                    ((uint16_t)0x2000)            /*!< Bit 1 */

#define  USART_CTRL2_LINEN                      ((uint16_t)0x4000)            /*!< LIN mode enable */

/******************  Bit definition for USART_CTRL3 register  *******************/
#define  USART_CTRL3_ERRIEN                     ((uint16_t)0x0001)            /*!< Error Interrupt Enable */
#define  USART_CTRL3_IRDAEN                     ((uint16_t)0x0002)            /*!< IrDA mode Enable */
#define  USART_CTRL3_IRDALP                     ((uint16_t)0x0004)            /*!< IrDA Low-Power */
#define  USART_CTRL3_HALFSEL                    ((uint16_t)0x0008)            /*!< Half-Duplex Selection */
#define  USART_CTRL3_NACKEN                     ((uint16_t)0x0010)            /*!< Smartcard NACK enable */
#define  USART_CTRL3_SCMEN                      ((uint16_t)0x0020)            /*!< Smartcard mode enable */
#define  USART_CTRL3_DMAREN                     ((uint16_t)0x0040)            /*!< DMA Enable Receiver */
#define  USART_CTRL3_DMATEN                     ((uint16_t)0x0080)            /*!< DMA Enable Transmitter */
#define  USART_CTRL3_RTSEN                      ((uint16_t)0x0100)            /*!< RTS Enable */
#define  USART_CTRL3_CTSEN                      ((uint16_t)0x0200)            /*!< CTS Enable */
#define  USART_CTRL3_CTSIEN                     ((uint16_t)0x0400)            /*!< CTS Interrupt Enable */
#define  USART_CTRL3_ONEBIT                     ((uint16_t)0x0800)            /*!< One Bit method */

/******************  Bit definition for USART_GTP register  ******************/
#define  USART_GTP_PSC                          ((uint16_t)0x00FF)            /*!< PSC[7:0] bits (Prescaler value) */
#define  USART_GTP_PSC_B0                       ((uint16_t)0x0001)            /*!< Bit 0 */
#define  USART_GTP_PSC_B1                       ((uint16_t)0x0002)            /*!< Bit 1 */
#define  USART_GTP_PSC_B2                       ((uint16_t)0x0004)            /*!< Bit 2 */
#define  USART_GTP_PSC_B3                       ((uint16_t)0x0008)            /*!< Bit 3 */
#define  USART_GTP_PSC_B4                       ((uint16_t)0x0010)            /*!< Bit 4 */
#define  USART_GTP_PSC_B5                       ((uint16_t)0x0020)            /*!< Bit 5 */
#define  USART_GTP_PSC_B6                       ((uint16_t)0x0040)            /*!< Bit 6 */
#define  USART_GTP_PSC_B7                       ((uint16_t)0x0080)            /*!< Bit 7 */

#define  USART_GTP_GTVAL                        ((uint16_t)0xFF00)            /*!< Guard time value */

/******************************************************************************/
/*                                                                            */
/*                                 Debug MCU                                  */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for DBGMCU_IDCR register  *****************/
#define  MCUDBG_IDCR_DEV_ID                     ((uint32_t)0x00000FFF)        /*!< Device Identifier */

#define  MCUDBG_IDCR_REV_ID                     ((uint32_t)0xFFFF0000)        /*!< REV_ID[15:0] bits (Revision Identifier) */
#define  MCUDBG_IDCR_REV_ID_0                   ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  MCUDBG_IDCR_REV_ID_1                   ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  MCUDBG_IDCR_REV_ID_2                   ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  MCUDBG_IDCR_REV_ID_3                   ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  MCUDBG_IDCR_REV_ID_4                   ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  MCUDBG_IDCR_REV_ID_5                   ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  MCUDBG_IDCR_REV_ID_6                   ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  MCUDBG_IDCR_REV_ID_7                   ((uint32_t)0x00800000)        /*!< Bit 7 */
#define  MCUDBG_IDCR_REV_ID_8                   ((uint32_t)0x01000000)        /*!< Bit 8 */
#define  MCUDBG_IDCR_REV_ID_9                   ((uint32_t)0x02000000)        /*!< Bit 9 */
#define  MCUDBG_IDCR_REV_ID_10                  ((uint32_t)0x04000000)        /*!< Bit 10 */
#define  MCUDBG_IDCR_REV_ID_11                  ((uint32_t)0x08000000)        /*!< Bit 11 */
#define  MCUDBG_IDCR_REV_ID_12                  ((uint32_t)0x10000000)        /*!< Bit 12 */
#define  MCUDBG_IDCR_REV_ID_13                  ((uint32_t)0x20000000)        /*!< Bit 13 */
#define  MCUDBG_IDCR_REV_ID_14                  ((uint32_t)0x40000000)        /*!< Bit 14 */
#define  MCUDBG_IDCR_REV_ID_15                  ((uint32_t)0x80000000)        /*!< Bit 15 */

/******************  Bit definition for DBGMCU_CTRL register  *******************/
#define  MCUDBG_CTRL_DBG_SLEEP                  ((uint32_t)0x00000001)        /*!< Debug Sleep Mode */
#define  MCUDBG_CTRL_DBG_STOP                   ((uint32_t)0x00000002)        /*!< Debug Stop Mode */
#define  MCUDBG_CTRL_DBG_STANDBY                ((uint32_t)0x00000004)        /*!< Debug Standby mode */
#define  MCUDBG_CTRL_TRACE_IOEN                 ((uint32_t)0x00000020)        /*!< Trace Pin Assignment Control */

#define  MCUDBG_CTRL_TRACE_MODE                 ((uint32_t)0x000000C0)        /*!< TRACE_MODE[1:0] bits (Trace Pin Assignment Control) */
#define  MCUDBG_CTRL_TRACE_MODE_0               ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  MCUDBG_CTRL_TRACE_MODE_1               ((uint32_t)0x00000080)        /*!< Bit 1 */

#define  MCUDBG_CTRL_DBG_IWDG_STOP              ((uint32_t)0x00000100)        /*!< Debug Independent Watchdog stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_WWDG_STOP              ((uint32_t)0x00000200)        /*!< Debug Window Watchdog stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR1_STOP              ((uint32_t)0x00000400)        /*!< TMR1 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_TMR2_STOP              ((uint32_t)0x00000800)        /*!< TMR2 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_TMR3_STOP              ((uint32_t)0x00001000)        /*!< TMR3 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_TMR4_STOP              ((uint32_t)0x00002000)        /*!< TMR4 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_CAN1_STOP              ((uint32_t)0x00004000)        /*!< Debug CAN1 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_I2C1_SMBUS_TIMEOUT     ((uint32_t)0x00008000)        /*!< SMBUS timeout mode stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_I2C2_SMBUS_TIMEOUT     ((uint32_t)0x00010000)        /*!< SMBUS timeout mode stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR8_STOP              ((uint32_t)0x00020000)        /*!< TMR8 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_TMR5_STOP              ((uint32_t)0x00040000)        /*!< TMR5 counter stopped when core is halted */


#define  MCUDBG_CTRL_DBG_TMR9_STOP              ((uint32_t)0x10000000)        /*!< Debug TMR9 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR10_STOP             ((uint32_t)0x20000000)        /*!< Debug TMR10 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR11_STOP             ((uint32_t)0x40000000)        /*!< Debug TMR11 stopped when Core is halted */

#ifdef AT32F413xx
#if !defined (AT32FEBKCx_MD)
#define  MCUDBG_CTRL_DBG_CAN2_STOP              ((uint32_t)0x00200000)        /*!< Debug CAN2 stopped when Core is halted */
#endif
#else
#define  MCUDBG_CTRL_DBG_TMR6_STOP              ((uint32_t)0x00080000)        /*!< TMR6 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_TMR7_STOP              ((uint32_t)0x00100000)        /*!< TMR7 counter stopped when core is halted */
#define  MCUDBG_CTRL_DBG_TMR15_STOP             ((uint32_t)0x00400000)        /*!< Debug TMR15 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR12_STOP             ((uint32_t)0x02000000)        /*!< Debug TMR12 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR13_STOP             ((uint32_t)0x04000000)        /*!< Debug TMR13 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_TMR14_STOP             ((uint32_t)0x08000000)        /*!< Debug TMR14 stopped when Core is halted */
#define  MCUDBG_CTRL_DBG_I2C3_SMBUS_TIMEOUT     ((uint32_t)0x80000000)        /*!< SMBUS timeout mode stopped when Core is halted */
#endif

/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FLASH_ACR register  ******************/
#define  FLASH_ACR_LATENCY                      ((uint8_t)0x07)               /*!< LATENCY[2:0] bits (Latency) */
#define  FLASH_ACR_LATENCY_0                    ((uint8_t)0x00)               /*!< Bit 0 */
#define  FLASH_ACR_LATENCY_1                    ((uint8_t)0x01)               /*!< Bit 0 */
#define  FLASH_ACR_LATENCY_2                    ((uint8_t)0x02)               /*!< Bit 1 */
#define  FLASH_ACR_LATENCY_3                    ((uint8_t)0x03)               /*!< Bit 1 & Bit 0 */
#define  FLASH_ACR_LATENCY_4                    ((uint8_t)0x04)               /*!< Bit 2 */
#define  FLASH_ACR_LATENCY_5                    ((uint8_t)0x05)               /*!< Bit 2 & Bit 0 */

#define  FLASH_ACR_HLFCYA                       ((uint8_t)0x08)               /*!< Flash Half Cycle Access Enable */
#define  FLASH_ACR_PRFTBE                       ((uint8_t)0x10)               /*!< Prefetch Buffer Enable */
#define  FLASH_ACR_PRFTBS                       ((uint8_t)0x20)               /*!< Prefetch Buffer Status */

/******************  Bit definition for FLASH_FCKEY register  ******************/
#define  FLASH_FCKEY_KEY                        ((uint32_t)0xFFFFFFFF)        /*!< FPEC Key */

/*****************  Bit definition for FLASH_UOBKEY register  ****************/
#define  FLASH_UOBKEY_KEY                       ((uint32_t)0xFFFFFFFF)        /*!< Option Byte Key */

/******************  Bit definition for FLASH_STS register  *******************/
#define  FLASH_STS_BSY                          ((uint8_t)0x01)               /*!< Busy */
#define  FLASH_STS_PRGMFLR                      ((uint8_t)0x04)               /*!< Programming Error */
#define  FLASH_STS_WRPRTFLR                     ((uint8_t)0x10)               /*!< Write Protection Error */
#define  FLASH_STS_PRCDN                        ((uint8_t)0x20)               /*!< End of operation */

/*******************  Bit definition for FLASH_CTRL register  *******************/
#define  FLASH_CTRL_PRGM                        ((uint16_t)0x0001)            /*!< Programming */
#define  FLASH_CTRL_PGERS                       ((uint16_t)0x0002)            /*!< Page Erase */
#define  FLASH_CTRL_CHPERS                      ((uint16_t)0x0004)            /*!< Mass Erase */
#define  FLASH_CTRL_UOBPRGM                     ((uint16_t)0x0010)            /*!< Option Byte Programming */
#define  FLASH_CTRL_UOBERS                      ((uint16_t)0x0020)            /*!< Option Byte Erase */
#define  FLASH_CTRL_STRT                        ((uint16_t)0x0040)            /*!< Start */
#define  FLASH_CTRL_LCK                         ((uint16_t)0x0080)            /*!< Lock */
#define  FLASH_CTRL_UOBWE                       ((uint16_t)0x0200)            /*!< Option Bytes Write Enable */
#define  FLASH_CTRL_FLRIE                       ((uint16_t)0x0400)            /*!< Error Interrupt Enable */
#define  FLASH_CTRL_PRCDNIE                     ((uint16_t)0x1000)            /*!< End of operation interrupt enable */
#define  FLASH_CTRL_OPTION_BYTE_PRT_DIS_TRIG    ((uint32_t)0x00010000)        /*!< Disable Option Byte Protection */

/*******************  Bit definition for FLASH_ADDR register  *******************/
#define  FLASH_ADDR_TA                          ((uint32_t)0xFFFFFFFF)        /*!< Flash Address */

/******************  Bit definition for FLASH_UOB register  *******************/
#define  FLASH_UOB_UOBFLR                       ((uint16_t)0x0001)            /*!< Option Byte Error */
#define  FLASH_UOB_RDPRTEN                      ((uint16_t)0x0002)            /*!< Read protection */

#define  FLASH_UOB_USR                          ((uint16_t)0x03FC)            /*!< User Option Bytes */
#define  FLASH_UOB_SW_WDG                       ((uint16_t)0x0004)            /*!< WDG_SW */
#define  FLASH_UOB_nSTP_RST                     ((uint16_t)0x0008)            /*!< nRST_STOP */
#define  FLASH_UOB_nSTDBY_RST                   ((uint16_t)0x0010)            /*!< nRST_STDBY */
#define  FLASH_UOB_BTOPT                        ((uint16_t)0x0020)            /*!< BFB2 */

#define  FLASH_UOB_DATA0                        ((uint32_t)0x0003FC00)        /*!< User data 0 */
#define  FLASH_UOB_DATA1                        ((uint32_t)0x03FC0000)        /*!< User data 1 */
#define  FLASH_UOB_OPTION_BYTE_PRT_EN           ((uint32_t)0x04000000)        /*!< Option Byte Protection */

/******************  Bit definition for FLASH_WRPRT register  ******************/
#define  FLASH_WRPRT_WRPRTBMP                   ((uint32_t)0xFFFFFFFF)        /*!< Write Protect */

/******************  Bit definition for FSLIB_CDR0 register  ******************/
#define  FLASH_SLIB_CDR0_BOOT_DIS               ((uint8_t)0x01)               /*!< Boot mode disable in System Memory */
#define  FLASH_SLIB_CDR0_SYS_SLIB_EN            ((uint8_t)0x04)               /*!< SLIB code enable in System Memory */
#define  FLASH_SLIB_CDR0_SLIB_EN                ((uint8_t)0x08)               /*!< SLIB code enable in Flash */

/******************  Bit definition for FSLIB_CDR1 register  ******************/
#define  FLASH_SLIB_START_PAGE                  ((uint32_t)0x000007FF)        /*!< SLIB Start Page */
#define  FLASH_SLIB_DATA_START_PAGE             ((uint32_t)0x003FF800)        /*!< SLIB Data Start Page */
#define  FLASH_SLIB_END_PAGE                    ((uint32_t)0xFFC00000)        /*!< SLIB End Page */
/******************  Bit definition for FSLIB_PSW register  ******************/
#define  FLASH_SLIB_PSW_PSW                     ((uint32_t)0xFFFFFFFF)        /*!< SLIB password */

/******************  Bit definition for FSLIB_PSWSTS register  ******************/
#define  FLASH_SLIB_PSWSTS_PSW_ERR              ((uint8_t)0x01)               /*!< SLIB password mismatch */
#define  FLASH_SLIB_PSWSTS_PSW_OK               ((uint8_t)0x02)               /*!< SLIB password match */
#define  FLASH_SLIB_UNLOCK                      ((uint8_t)0x04)               /*!< SLIB unlock status */
#define  FLASH_SLIB_CNT                         ((uint32_t)0x01FF0000)        /*!< SLIB remaining CFG count */

/*----------------------------------------------------------------------------*/

/******************  Bit definition for FLASH_RDPRT register  *******************/
#define  FLASH_RDPRT_RDPRT                      ((uint32_t)0x000000FF)        /*!< Read protection option byte */
#define  FLASH_RDPRT_nRDPRT                     ((uint32_t)0x0000FF00)        /*!< Read protection complemented option byte */

/******************  Bit definition for FLASH_USR register  ******************/
#define  FLASH_USR_USR                          ((uint32_t)0x00FF0000)        /*!< User option byte */
#define  FLASH_USR_nUSR                         ((uint32_t)0xFF000000)        /*!< User complemented option byte */

/******************  Bit definition for FLASH_DT0 register  *****************/
#define  FLASH_DT0_DT0                          ((uint32_t)0x000000FF)        /*!< User data storage option byte */
#define  FLASH_DT0_nDT0                         ((uint32_t)0x0000FF00)        /*!< User data storage complemented option byte */

/******************  Bit definition for FLASH_DT1 register  *****************/
#define  FLASH_DT1_DT1                          ((uint32_t)0x00FF0000)        /*!< User data storage option byte */
#define  FLASH_DT1_nDT1                         ((uint32_t)0xFF000000)        /*!< User data storage complemented option byte */

/******************  Bit definition for FLASH_WRPRT0 register  ******************/
#define  FLASH_WRPRT0_WRPRT0                    ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRPRT0_nWRPRT0                   ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRPRT1 register  ******************/
#define  FLASH_WRPRT1_WRPRT1                    ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRPRT1_nWRPRT1                   ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRPRT2 register  ******************/
#define  FLASH_WRPRT2_WRPRT2                    ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRPRT2_nWRPRT2                   ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRPRT3 register  ******************/
#define  FLASH_WRPRT3_WRPRT3                    ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRPRT3_nWRPRT3                   ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */

/****************** Bit definition for FSLIB_SET_PSW register ******************/
#define  FLASH_SLIB_SET_PSW                     ((uint32_t)0xFFFFFFFF)        /*!< SLIB Password */

/****************** Bit definition for FSLIB_SET_RANGE register ******************/
#define  FLASH_SLIB_SET_START_PAGE              ((uint32_t)0x000007FF)        /*!< SLIB Start Page */
#define  FLASH_SLIB_SET_DATA_START_PAGE         ((uint32_t)0x003FF800)        /*!< SLIB Data Start Page */
#define  FLASH_SLIB_SET_END_PAGE                ((uint32_t)0xFFC00000)        /*!< SLIB End Page */

/****************** Bit definition for SLIB_KEYR register ******************/
#define  FLASH_SLIB_KEYR                        ((uint32_t)0xFFFFFFFF)        /*!< SLIB Unlock Key Register */

#if defined (AT32F407xx)
/******************************************************************************/
/*                                                                            */
/*               Ethernet MAC Registers bits definitions                      */
/*                                                                            */
/******************************************************************************/
/********** Bit definition for Ethernet MAC Control Register register ***********/
#define ETH_MACCTRL_WDOGD                          ((uint32_t)0x00800000)        /*!< Watchdog disable */
#define ETH_MACCTRL_JAD                            ((uint32_t)0x00400000)        /*!< Jabber disable */

#define ETH_MACCTRL_FG                             ((uint32_t)0x000E0000)        /*!< Inter-frame gap */
#define ETH_MACCTRL_FG_96Bit                       ((uint32_t)0x00000000)        /*!< Minimum IFG between frames during transmission is 96Bit */
#define ETH_MACCTRL_FG_88Bit                       ((uint32_t)0x00020000)        /*!< Minimum IFG between frames during transmission is 88Bit */
#define ETH_MACCTRL_FG_80Bit                       ((uint32_t)0x00040000)        /*!< Minimum IFG between frames during transmission is 80Bit */
#define ETH_MACCTRL_FG_72Bit                       ((uint32_t)0x00060000)        /*!< Minimum IFG between frames during transmission is 72Bit */
#define ETH_MACCTRL_FG_64Bit                       ((uint32_t)0x00080000)        /*!< Minimum IFG between frames during transmission is 64Bit */
#define ETH_MACCTRL_FG_56Bit                       ((uint32_t)0x000A0000)        /*!< Minimum IFG between frames during transmission is 56Bit */
#define ETH_MACCTRL_FG_48Bit                       ((uint32_t)0x000C0000)        /*!< Minimum IFG between frames during transmission is 48Bit */
#define ETH_MACCTRL_FG_40Bit                       ((uint32_t)0x000E0000)        /*!< Minimum IFG between frames during transmission is 40Bit */

#define ETH_MACCTRL_CSD                            ((uint32_t)0x00010000)        /*!< Carrier sense disable (during transmission) */
#define ETH_MACCTRL_FESM                           ((uint32_t)0x00004000)        /*!< Fast ethernet speed */
#define ETH_MACCTRL_ROD                            ((uint32_t)0x00002000)        /*!< Receive own disable */
#define ETH_MACCTRL_LBM                            ((uint32_t)0x00001000)        /*!< loopback mode */
#define ETH_MACCTRL_DM                             ((uint32_t)0x00000800)        /*!< Duplex mode */
#define ETH_MACCTRL_IP4CO                          ((uint32_t)0x00000400)        /*!< IP Checksum offload */
#define ETH_MACCTRL_RD                             ((uint32_t)0x00000200)        /*!< Retry disable */
#define ETH_MACCTRL_AUPCS                          ((uint32_t)0x00000080)        /*!< Automatic Pad/CRC stripping */

#define ETH_MACCTRL_BOL                            ((uint32_t)0x00000060)        /*!< Back-off limit: random integer number (r) of slot time delays before rescheduling
                                                                                   a transmission attempt during retries after a collision: 0 =< r <2^k */
#define ETH_MACCTRL_BOL_10                         ((uint32_t)0x00000000)        /*!< k = min (n, 10) */
#define ETH_MACCTRL_BOL_8                          ((uint32_t)0x00000020)        /*!< k = min (n, 8) */
#define ETH_MACCTRL_BOL_4                          ((uint32_t)0x00000040)        /*!< k = min (n, 4) */
#define ETH_MACCTRL_BOL_1                          ((uint32_t)0x00000060)        /*!< k = min (n, 1) */

#define ETH_MACCTRL_DC                             ((uint32_t)0x00000010)        /*!< Defferal check */
#define ETH_MACCTRL_TE                             ((uint32_t)0x00000008)        /*!< Transmitter enable */
#define ETH_MACCTRL_RE                             ((uint32_t)0x00000004)        /*!< Receiver enable */

/************** Bit definition for Ethernet MAC Frame Filter Register ***************/
#define ETH_MACFRMF_RALL                           ((uint32_t)0x80000000)        /*!< Receive all */
#define ETH_MACFRMF_HOPF                           ((uint32_t)0x00000400)        /*!< Hash or perfect filter */
#define ETH_MACFRMF_SADDRF                         ((uint32_t)0x00000200)        /*!< Source address filter enable */
#define ETH_MACFRMF_SADDRIF                        ((uint32_t)0x00000100)        /*!< SA inverse filtering */

#define ETH_MACFRMF_PCF                            ((uint32_t)0x000000C0)        /*!< Pass control frames: 3 cases */
#define ETH_MACFRMF_PCF_BlockAll                   ((uint32_t)0x00000040)        /*!< MAC filters all control frames from reaching the application */
#define ETH_MACFRMF_PCF_ForwardAll                 ((uint32_t)0x00000080)        /*!< MAC forwards all control frames to application even if they fail the Address Filter */
#define ETH_MACFRMF_ForwardPassedAddrFilter        ((uint32_t)0x000000C0)        /*!< MAC forwards control frames that pass the Address Filter. */

#define ETH_MACFRMF_BFD                            ((uint32_t)0x00000020)        /*!< Broadcast frame disable */
#define ETH_MACFRMF_PALLM                          ((uint32_t)0x00000010)        /*!< Pass all mutlicast */
#define ETH_MACFRMF_DADDRIF                        ((uint32_t)0x00000008)        /*!< DA Inverse filtering */
#define ETH_MACFRMF_HM                             ((uint32_t)0x00000004)        /*!< Hash multicast */
#define ETH_MACFRMF_HU                             ((uint32_t)0x00000002)        /*!< Hash unicast */
#define ETH_MACFRMF_PM                             ((uint32_t)0x00000001)        /*!< Promiscuous mode */

/************ Bit definition for Ethernet MAC Hash Table High Register *************/
#define ETH_MACHTH_HTH                             ((uint32_t)0xFFFFFFFF)        /*!< Hash table high */

/************* Bit definition for Ethernet MAC Hash Table Low Register *************/
#define ETH_MACHTL_HTL                             ((uint32_t)0xFFFFFFFF)        /*!< Hash table low */

/************** Bit definition for Ethernet MAC MII Address Register ***************/
#define ETH_MACMIIADDR_PA                          ((uint32_t)0x0000F800)        /*!< Physical layer address */
#define ETH_MACMIIADDR_MII                         ((uint32_t)0x000007C0)        /*!< MII register in the selected PHY */

#define ETH_MACMIIADDR_CLKR                        ((uint32_t)0x0000001C)        /*!< CR clock range: 6 cases */
#define ETH_MACMIIADDR_CLKR_DIV42                  ((uint32_t)0x00000000)        /*!< HCLK:60-72 MHz; MDC clock= HCLK/42 */
#define ETH_MACMIIADDR_CLKR_DIV62                  ((uint32_t)0x00000004)        /*!< HCLK:100-150 MHz; MDC clock= HCLK/62 */
#define ETH_MACMIIADDR_CLKR_DIV16                  ((uint32_t)0x00000008)        /*!< HCLK:20-35 MHz; MDC clock= HCLK/16 */
#define ETH_MACMIIADDR_CLKR_DIV26                  ((uint32_t)0x0000000C)        /*!< HCLK:35-60 MHz; MDC clock= HCLK/26 */
#define ETH_MACMIIADDR_CLKR_DIV102                 ((uint32_t)0x00000010)        /*!< HCLK:150-250 MHz; MDC clock= HCLK/102 */
#define ETH_MACMIIADDR_CLKR_DIV124                 ((uint32_t)0x00000014)        /*!< HCLK:250-300 MHz; MDC clock= HCLK/124 */

#define ETH_MACMIIADDR_MIIW                        ((uint32_t)0x00000002)        /*!< MII write */
#define ETH_MACMIIADDR_MIIB                        ((uint32_t)0x00000001)        /*!< MII busy */

/**************** Bit definition for Ethernet MAC MII Data Register ****************/
#define ETH_MACMIIDT_MIID                          ((uint32_t)0x0000FFFF)        /*!< MII data: read/write data from/to PHY */

/************** Bit definition for Ethernet MAC Flow Control Register **************/
#define ETH_MACFCTRL_PTM                           ((uint32_t)0xFFFF0000)        /*!< Pause time */
#define ETH_MACFCTRL_ZQPD                          ((uint32_t)0x00000080)        /*!< Zero-quanta pause disable */

#define ETH_MACFCTRL_PLT                           ((uint32_t)0x00000030)        /*!< Pause low threshold: 4 cases */
#define ETH_MACFCTRL_PLT_Minus4                    ((uint32_t)0x00000000)        /*!< Pause time minus 4 slot times */
#define ETH_MACFCTRL_PLT_Minus28                   ((uint32_t)0x00000010)        /*!< Pause time minus 28 slot times */
#define ETH_MACFCTRL_PLT_Minus144                  ((uint32_t)0x00000020)        /*!< Pause time minus 144 slot times */
#define ETH_MACFCTRL_PLT_Minus256                  ((uint32_t)0x00000030)        /*!< Pause time minus 256 slot times */

#define ETH_MACFCTRL_UPFD                          ((uint32_t)0x00000008)        /*!< Unicast pause frame detect */
#define ETH_MACFCTRL_RFCEN                         ((uint32_t)0x00000004)        /*!< Receive flow control enable */
#define ETH_MACFCTRL_TFCEN                         ((uint32_t)0x00000002)        /*!< Transmit flow control enable */
#define ETH_MACFCTRL_FCBBPA                        ((uint32_t)0x00000001)        /*!< Flow control busy/backpressure activate */

/************** Bit definition for Ethernet MAC VLAN Tag Register ****************/
#define ETH_MACVLT_VLTC                            ((uint32_t)0x00010000)        /*!< 12-bit VLAN tag comparison */
#define ETH_MACVLT_VLTI                            ((uint32_t)0x0000FFFF)        /*!< VLAN tag identifier (for receive frames) */

/****** Bit definition for Ethernet MAC Remote Wake-UpFrame Filter Register ******/
#define ETH_MACRWFF_D                              ((uint32_t)0xFFFFFFFF)        /*!< Wake-up frame filter register data */

/*!< Eight sequential Writes to this address (offset 0x28) will write all Wake-UpFrame Filter Registers.
   Eight sequential Reads from this address (offset 0x28) will read all Wake-UpFrame Filter Registers. */
/*!< Wake-UpFrame Filter Reg0 : Filter 0 Byte Mask
   Wake-UpFrame Filter Reg1 : Filter 1 Byte Mask
   Wake-UpFrame Filter Reg2 : Filter 2 Byte Mask
   Wake-UpFrame Filter Reg3 : Filter 3 Byte Mask
   Wake-UpFrame Filter Reg4 : RSVD - Filter3 Command - RSVD - Filter2 Command - 
                              RSVD - Filter1 Command - RSVD - Filter0 Command
   Wake-UpFrame Filter Re5 : Filter3 Offset - Filter2 Offset - Filter1 Offset - Filter0 Offset
   Wake-UpFrame Filter Re6 : Filter1 CRC16 - Filter0 CRC16
   Wake-UpFrame Filter Re7 : Filter3 CRC16 - Filter2 CRC16 */

/******** Bit definition for Ethernet MAC PMT Control and Status Register **********/
#define ETH_MACPMTCTRLSTS_WFFPR                    ((uint32_t)0x80000000)        /*!< Wake-Up Frame Filter Register Pointer Reset */
#define ETH_MACPMTCTRLSTS_GLBU                     ((uint32_t)0x00000200)        /*!< Global Unicast */
#define ETH_MACPMTCTRLSTS_WFR                      ((uint32_t)0x00000040)        /*!< Wake-Up Frame Received */
#define ETH_MACPMTCTRLSTS_MPR                      ((uint32_t)0x00000020)        /*!< Magic Packet Received */
#define ETH_MACPMTCTRLSTS_WFEN                     ((uint32_t)0x00000004)        /*!< Wake-Up Frame Enable */
#define ETH_MACPMTCTRLSTS_MPEN                     ((uint32_t)0x00000002)        /*!< Magic Packet Enable */
#define ETH_MACPMTCTRLSTS_PD                       ((uint32_t)0x00000001)        /*!< Power Down */

/**************** Bit definition for Ethernet MAC Status Register ******************/
#define ETH_MACISTS_TSTS                           ((uint32_t)0x00000200)        /*!< Time stamp trigger status */
#define ETH_MACISTS_MMCTS                          ((uint32_t)0x00000040)        /*!< MMC transmit status */
#define ETH_MACISTS_MMCRS                          ((uint32_t)0x00000020)        /*!< MMC receive status */
#define ETH_MACISTS_MMCS                           ((uint32_t)0x00000010)        /*!< MMC status */
#define ETH_MACISTS_PMTS                           ((uint32_t)0x00000008)        /*!< PMT status */

/************ Bit definition for Ethernet MAC Interrupt Mask Register **************/
#define ETH_MACIM_TSTINTM                          ((uint32_t)0x00000200)        /*!< Time stamp trigger interrupt mask */
#define ETH_MACIM_PMTINTM                          ((uint32_t)0x00000008)        /*!< PMT interrupt mask */

/************ Bit definition for Ethernet MAC Address0 High Register ***************/
#define ETH_MACA0H_MACADDR0H                       ((uint32_t)0x0000FFFF)        /*!< MAC address0 high */

/************* Bit definition for Ethernet MAC Address0 Low Register ***************/
#define ETH_MACA0L_MACADDR0L                       ((uint32_t)0xFFFFFFFF)        /*!< MAC address0 low */

/************* Bit definition for Ethernet MAC Address1 High Register **************/
#define ETH_MACA1H_AEN                             ((uint32_t)0x80000000)        /*!< Address enable */
#define ETH_MACA1H_SADDR                           ((uint32_t)0x40000000)        /*!< Source address */

#define ETH_MACA1H_MBCTRL                          ((uint32_t)0x3F000000)        /*!< Mask byte control: bits to mask for comparison of the MAC Address bytes */
#define ETH_MACA1H_MBCTRL_HBits15_8                ((uint32_t)0x20000000)        /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MACA1H_MBCTRL_HBits7_0                 ((uint32_t)0x10000000)        /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MACA1H_MBCTRL_LBits31_24               ((uint32_t)0x08000000)        /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MACA1H_MBCTRL_LBits23_16               ((uint32_t)0x04000000)        /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MACA1H_MBCTRL_LBits15_8                ((uint32_t)0x02000000)        /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MACA1H_MBCTRL_LBits7_0                 ((uint32_t)0x01000000)        /*!< Mask MAC Address low reg bits [7:0] */

#define ETH_MACA1H_MACADDR1H                       ((uint32_t)0x0000FFFF)        /*!< MAC address1 high */
/************** Bit definition for Ethernet MAC Address1 Low Register **************/

#define ETH_MACA1L_MACADDR1L                       ((uint32_t)0xFFFFFFFF)        /*!< MAC address1 low */

/************** Bit definition for Ethernet MAC Address2 High Register *************/
#define ETH_MACA2H_AEN                             ((uint32_t)0x80000000)        /*!< Address enable */
#define ETH_MACA2H_SADDR                           ((uint32_t)0x40000000)        /*!< Source address */

#define ETH_MACA2H_MBCTRL                          ((uint32_t)0x3F000000)        /*!< Mask byte control */
#define ETH_MACA2H_MBCTRL_HBits15_8                ((uint32_t)0x20000000)        /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MACA2H_MBCTRL_HBits7_0                 ((uint32_t)0x10000000)        /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MACA2H_MBCTRL_LBits31_24               ((uint32_t)0x08000000)        /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MACA2H_MBCTRL_LBits23_16               ((uint32_t)0x04000000)        /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MACA2H_MBCTRL_LBits15_8                ((uint32_t)0x02000000)        /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MACA2H_MBCTRL_LBits7_0                 ((uint32_t)0x01000000)        /*!< Mask MAC Address low reg bits [70] */

#define ETH_MACA2H_MACADDR2H                       ((uint32_t)0x0000FFFF)        /*!< MAC address1 high */

/************** Bit definition for Ethernet MAC Address2 Low Register **************/
#define ETH_MACA2L_MACADDR2L                       ((uint32_t)0xFFFFFFFF)        /*!< MAC address2 low */

/************** Bit definition for Ethernet MAC Address3 High Register *************/
#define ETH_MACA3H_AEN                             ((uint32_t)0x80000000)        /*!< Address enable */
#define ETH_MACA3H_SADDR                           ((uint32_t)0x40000000)        /*!< Source address */

#define ETH_MACA3H_MBCTRL                          ((uint32_t)0x3F000000)        /*!< Mask byte control */
#define ETH_MACA3H_MBCTRL_HBits15_8                ((uint32_t)0x20000000)        /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MACA3H_MBCTRL_HBits7_0                 ((uint32_t)0x10000000)        /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MACA3H_MBCTRL_LBits31_24               ((uint32_t)0x08000000)        /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MACA3H_MBCTRL_LBits23_16               ((uint32_t)0x04000000)        /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MACA3H_MBCTRL_LBits15_8                ((uint32_t)0x02000000)        /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MACA3H_MBCTRL_LBits7_0                 ((uint32_t)0x01000000)        /*!< Mask MAC Address low reg bits [70] */

#define ETH_MACA3H_MACADDR3H                       ((uint32_t)0x0000FFFF)        /*!< MAC address3 high */

/************** Bit definition for Ethernet MAC Address3 Low Register **************/
#define ETH_MACA3L_MACADDR3L                       ((uint32_t)0xFFFFFFFF)        /*!< MAC address3 low */

/******************************************************************************/
/*                                                                            */
/*               Ethernet MMC Registers bits definition                       */
/*                                                                            */
/******************************************************************************/

/***************** Bit definition for Ethernet MMC Contol Register *****************/
#define ETH_MMCCTRL_MCNTF                         ((uint32_t)0x00000008)        /*!< MMC Counter Freeze */
#define ETH_MMCCTRL_RSTOR                         ((uint32_t)0x00000004)        /*!< Reset on Read */
#define ETH_MMCCTRL_CSR                           ((uint32_t)0x00000002)        /*!< Counter Stop Rollover */
#define ETH_MMCCTRL_CNTR                          ((uint32_t)0x00000001)        /*!< Counters Reset */

/*********** Bit definition for Ethernet MMC Receive Interrupt Register ************/
#define ETH_MMCRI_RGUF                            ((uint32_t)0x00020000)        /*!< Set when Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMCRI_RFAE                            ((uint32_t)0x00000040)        /*!< Set when Rx alignment error counter reaches half the maximum value */
#define ETH_MMCRI_RFCE                            ((uint32_t)0x00000020)        /*!< Set when Rx crc error counter reaches half the maximum value */

/*********** Bit definition for Ethernet MMC Transmit Interrupt Register ***********/
#define ETH_MMCTI_TGF                             ((uint32_t)0x00200000)        /*!< Set when Tx good frame count counter reaches half the maximum value */
#define ETH_MMCTI_TGFMSC                          ((uint32_t)0x00008000)        /*!< Set when Tx good multi col counter reaches half the maximum value */
#define ETH_MMCTI_TGFSC                           ((uint32_t)0x00004000)        /*!< Set when Tx good single col counter reaches half the maximum value */

/********* Bit definition for Ethernet MMC Receive Interrupt Mask Register *********/
#define ETH_MMCRIM_RGUFM                          ((uint32_t)0x00020000)        /*!< Mask the interrupt when Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMCRIM_RFAEM                          ((uint32_t)0x00000040)        /*!< Mask the interrupt when when Rx alignment error counter reaches half the maximum value */
#define ETH_MMCRIM_RFCEM                          ((uint32_t)0x00000020)        /*!< Mask the interrupt when Rx crc error counter reaches half the maximum value */

/********* Bit definition for Ethernet MMC Transmit Interrupt Mask Register ********/
#define ETH_MMCTIM_TGFM                           ((uint32_t)0x00200000)        /*!< Mask the interrupt when Tx good frame count counter reaches half the maximum value */
#define ETH_MMCTIM_TGFMSCM                        ((uint32_t)0x00008000)        /*!< Mask the interrupt when Tx good multi col counter reaches half the maximum value */
#define ETH_MMCTIM_TGFSCM                         ((uint32_t)0x00004000)        /*!< Mask the interrupt when Tx good single col counter reaches half the maximum value */

/** Bit definition for Ethernet MMC Transmitted Good Frames after Single Collision Counter Register */
#define ETH_MMCTFSCC_TGFSCC                       ((uint32_t)0xFFFFFFFF)        /*!< Number of successfully transmitted frames after a single collision in Half-duplex mode. */

/** Bit definition for Ethernet MMC Transmitted Good Frames after More than a Single Collision Counter Register */
#define ETH_MMCTFMSCC_TGFMSCC                     ((uint32_t)0xFFFFFFFF)        /*!< Number of successfully transmitted frames after more than a single collision in Half-duplex mode. */

/***** Bit definition for Ethernet MMC Transmitted Good Frames Counter Register ****/
#define ETH_MMCTFCNT_TGFC                         ((uint32_t)0xFFFFFFFF)        /*!< Number of good frames transmitted. */
/** Bit definition for Ethernet MMC Received Frames with CRC Error Counter Register */
#define ETH_MMCRFCECNT_RFCEC                      ((uint32_t)0xFFFFFFFF)        /*!< Number of frames received with CRC error. */

/** Bit definition for Ethernet MMC Received Frames with Alignement Error Counter Register */
#define ETH_MMCRFAECNT_RFAEC                      ((uint32_t)0xFFFFFFFF)        /*!< Number of frames received with alignment (dribble) error */

/** Bit definition for Ethernet MMC Received Good Unicast Frames Counter Register */
#define ETH_MMCRGUFCNT_RGUFC                      ((uint32_t)0xFFFFFFFF)        /*!< Number of good unicast frames received. */

/******************************************************************************/
/*                                                                            */
/*               Ethernet PTP Registers bits definition                       */
/*                                                                            */
/******************************************************************************/

/************ Bit definition for Ethernet PTP Time Stamp Contol Register ***********/
#define ETH_PTPTSCTRL_TSARU                       ((uint32_t)0x00000020)        /*!< Addend register update */
#define ETH_PTPTSCTRL_TSITE                       ((uint32_t)0x00000010)        /*!< Time stamp interrupt trigger enable */
#define ETH_PTPTSCTRL_TSSTU                       ((uint32_t)0x00000008)        /*!< Time stamp update */
#define ETH_PTPTSCTRL_TSSTI                       ((uint32_t)0x00000004)        /*!< Time stamp initialize */
#define ETH_PTPTSCTRL_TSFCU                       ((uint32_t)0x00000002)        /*!< Time stamp fine or coarse update */
#define ETH_PTPTSCTRL_TSE                         ((uint32_t)0x00000001)        /*!< Time stamp enable */

/********** Bit definition for Ethernet PTP Sub-Second Increment Register **********/
#define ETH_PTPSSINC_STSINC                       ((uint32_t)0x000000FF)        /*!< System time Sub-second increment value */

/************ Bit definition for Ethernet PTP Time Stamp High Register *************/
#define ETH_PTPTSH_STS                            ((uint32_t)0xFFFFFFFF)        /*!< System Time second */

/************ Bit definition for Ethernet PTP Time Stamp Low Register **************/
#define ETH_PTPTSL_STPNS                          ((uint32_t)0x80000000)        /*!< System Time Positive or negative time */
#define ETH_PTPTSL_STSS                           ((uint32_t)0x7FFFFFFF)        /*!< System Time sub-seconds */

/********* Bit definition for Ethernet PTP Time Stamp High Update Register *********/
#define ETH_PTPTSHUD_TSUS                         ((uint32_t)0xFFFFFFFF)        /*!< Time stamp update seconds */

/********* Bit definition for Ethernet PTP Time Stamp Low Update Register **********/
#define ETH_PTPTSLUD_TSUPNS                       ((uint32_t)0x80000000)        /*!< Time stamp update Positive or negative time */
#define ETH_PTPTSLUD_TSUSS                        ((uint32_t)0x7FFFFFFF)        /*!< Time stamp update sub-seconds */

/*********** Bit definition for Ethernet PTP Time Stamp Addend Register ************/
#define ETH_PTPTSAD_TSA                           ((uint32_t)0xFFFFFFFF)        /*!< Time stamp addend */

/*********** Bit definition for Ethernet PTP Target Time High Register *************/
#define ETH_PTPTTH_TTSH                           ((uint32_t)0xFFFFFFFF)        /*!< Target time stamp high */

/************ Bit definition for Ethernet PTP Target Time Low Register *************/
#define ETH_PTPTTL_TTSL                           ((uint32_t)0xFFFFFFFF)        /*!< Target time stamp low */

/******************************************************************************/
/*                                                                            */
/*               Ethernet DMA Registers bits definition                       */
/*                                                                            */
/******************************************************************************/

/**************** Bit definition for Ethernet DMA Bus Mode Register ****************/
#define ETH_DMABM_AAB                          ((uint32_t)0x02000000)        /*!< Address-Aligned beats */
#define ETH_DMABM_FPBLM                        ((uint32_t)0x01000000)        /*!< 4xPBL mode */
#define ETH_DMABM_USP                          ((uint32_t)0x00800000)        /*!< Use separate PBL */

#define ETH_DMABM_RDPBL                        ((uint32_t)0x007E0000)        /*!< RxDMA PBL */
#define ETH_DMABM_RDPBL_1Beat                  ((uint32_t)0x00020000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define ETH_DMABM_RDPBL_2Beat                  ((uint32_t)0x00040000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define ETH_DMABM_RDPBL_4Beat                  ((uint32_t)0x00080000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_DMABM_RDPBL_8Beat                  ((uint32_t)0x00100000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_DMABM_RDPBL_16Beat                 ((uint32_t)0x00200000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_DMABM_RDPBL_32Beat                 ((uint32_t)0x00400000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_DMABM_RDPBL_4xPBL_4Beat            ((uint32_t)0x01020000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_DMABM_RDPBL_4xPBL_8Beat            ((uint32_t)0x01040000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_DMABM_RDPBL_4xPBL_16Beat           ((uint32_t)0x01080000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_DMABM_RDPBL_4xPBL_32Beat           ((uint32_t)0x01100000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_DMABM_RDPBL_4xPBL_64Beat           ((uint32_t)0x01200000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define ETH_DMABM_RDPBL_4xPBL_128Beat          ((uint32_t)0x01400000)        /*!< maximum number of beats to be transferred in one RxDMA transaction is 128 */

#define ETH_DMABM_FB                           ((uint32_t)0x00010000)        /*!< Fixed Burst */

#define ETH_DMABM_RTPR                         ((uint32_t)0x0000C000)        /*!< Rx Tx priority ratio */
#define ETH_DMABM_RTPR_1_1                     ((uint32_t)0x00000000)        /*!< Rx Tx priority ratio */
#define ETH_DMABM_RTPR_2_1                     ((uint32_t)0x00004000)        /*!< Rx Tx priority ratio */
#define ETH_DMABM_RTPR_3_1                     ((uint32_t)0x00008000)        /*!< Rx Tx priority ratio */
#define ETH_DMABM_RTPR_4_1                     ((uint32_t)0x0000C000)        /*!< Rx Tx priority ratio */

#define ETH_DMABM_PBL                          ((uint32_t)0x00003F00)        /*!< Programmable burst length */
#define ETH_DMABM_PBL_1Beat                    ((uint32_t)0x00000100)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define ETH_DMABM_PBL_2Beat                    ((uint32_t)0x00000200)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define ETH_DMABM_PBL_4Beat                    ((uint32_t)0x00000400)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_DMABM_PBL_8Beat                    ((uint32_t)0x00000800)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_DMABM_PBL_16Beat                   ((uint32_t)0x00001000)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_DMABM_PBL_32Beat                   ((uint32_t)0x00002000)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_DMABM_PBL_4xPBL_4Beat              ((uint32_t)0x01000100)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_DMABM_PBL_4xPBL_8Beat              ((uint32_t)0x01000200)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_DMABM_PBL_4xPBL_16Beat             ((uint32_t)0x01000400)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_DMABM_PBL_4xPBL_32Beat             ((uint32_t)0x01000800)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_DMABM_PBL_4xPBL_64Beat             ((uint32_t)0x01001000)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define ETH_DMABM_PBL_4xPBL_128Beat            ((uint32_t)0x01002000)        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */

#define ETH_DMABM_DSL                          ((uint32_t)0x0000007C)        /*!< Descriptor Skip Length */
#define ETH_DMABM_DA                           ((uint32_t)0x00000002)        /*!< DMA arbitration scheme */
#define ETH_DMABM_SWRST                        ((uint32_t)0x00000001)        /*!< Software reset */

/********** Bit definition for Ethernet DMA Transmit Poll Demand Register **********/
#define ETH_DMATPD_TPD                         ((uint32_t)0xFFFFFFFF)        /*!< Transmit poll demand */

/********** Bit definition for Ethernet DMA Receive Poll Demand Register ***********/
#define ETH_DMARPD_RPD                         ((uint32_t)0xFFFFFFFF)        /*!< Receive poll demand  */

/**** Bit definition for Ethernet DMA Receive Descriptor List Address Register *****/
#define ETH_DMARDLADDR_SRL                     ((uint32_t)0xFFFFFFFF)        /*!< Start of receive list */

/**** Bit definition for Ethernet DMA Transmit Descriptor List Address Register ****/
#define ETH_DMATDLADDR_STL                     ((uint32_t)0xFFFFFFFF)        /*!< Start of transmit list */

/***************** Bit definition for Ethernet DMA Status Register *****************/
#define ETH_DMASTS_TST                          ((uint32_t)0x20000000)        /*!< Time-stamp trigger status */
#define ETH_DMASTS_PMT                          ((uint32_t)0x10000000)        /*!< PMT status */
#define ETH_DMASTS_MMC                          ((uint32_t)0x08000000)        /*!< MMC status */

#define ETH_DMASTS_EB                           ((uint32_t)0x03800000)        /*!< Error bits status */
#define ETH_DMASTS_EB_DescAccess                ((uint32_t)0x02000000)        /*!< Error bits 0-data buffer, 1-desc. access */
#define ETH_DMASTS_EB_ReadTransf                ((uint32_t)0x01000000)        /*!< Error bits 0-write trnsf, 1-read transfr */
#define ETH_DMASTS_EB_DataTransfTx              ((uint32_t)0x00800000)        /*!< Error bits 0-Rx DMA, 1-Tx DMA */

#define ETH_DMASTS_TP                           ((uint32_t)0x00700000)        /*!< Transmit process state */
#define ETH_DMASTS_TP_Stopped                   ((uint32_t)0x00000000)        /*!< Stopped - Reset or Stop Tx Command issued  */
#define ETH_DMASTS_TP_Fetching                  ((uint32_t)0x00100000)        /*!< Running - fetching the Tx descriptor */
#define ETH_DMASTS_TP_Waiting                   ((uint32_t)0x00200000)        /*!< Running - waiting for status */
#define ETH_DMASTS_TP_Reading                   ((uint32_t)0x00300000)        /*!< Running - reading the data from host memory */
#define ETH_DMASTS_TP_Suspended                 ((uint32_t)0x00600000)        /*!< Suspended - Tx Descriptor unavailabe */
#define ETH_DMASTS_TP_Closing                   ((uint32_t)0x00700000)        /*!< Running - closing Rx descriptor */

#define ETH_DMASTS_RP                           ((uint32_t)0x000E0000)        /*!< Receive process state */
#define ETH_DMASTS_RP_Stopped                   ((uint32_t)0x00000000)        /*!< Stopped - Reset or Stop Rx Command issued */
#define ETH_DMASTS_RP_Fetching                  ((uint32_t)0x00020000)        /*!< Running - fetching the Rx descriptor */
#define ETH_DMASTS_RP_Waiting                   ((uint32_t)0x00060000)        /*!< Running - waiting for packet */
#define ETH_DMASTS_RP_Suspended                 ((uint32_t)0x00080000)        /*!< Suspended - Rx Descriptor unavailable */
#define ETH_DMASTS_RP_Closing                   ((uint32_t)0x000A0000)        /*!< Running - closing descriptor */
#define ETH_DMASTS_RP_Queuing                   ((uint32_t)0x000E0000)        /*!< Running - queuing the recieve frame into host memory */

#define ETH_DMASTS_NIS                          ((uint32_t)0x00010000)        /*!< Normal interrupt summary */
#define ETH_DMASTS_AIS                          ((uint32_t)0x00008000)        /*!< Abnormal interrupt summary */
#define ETH_DMASTS_ER                           ((uint32_t)0x00004000)        /*!< Early receive status */
#define ETH_DMASTS_FBE                          ((uint32_t)0x00002000)        /*!< Fatal bus error status */
#define ETH_DMASTS_ET                           ((uint32_t)0x00000400)        /*!< Early transmit status */
#define ETH_DMASTS_RWT                          ((uint32_t)0x00000200)        /*!< Receive watchdog timeout status */
#define ETH_DMASTS_RPS                          ((uint32_t)0x00000100)        /*!< Receive process stopped status */
#define ETH_DMASTS_RBU                          ((uint32_t)0x00000080)        /*!< Receive buffer unavailable status */
#define ETH_DMASTS_RECV                         ((uint32_t)0x00000040)        /*!< Receive status */
#define ETH_DMASTS_TU                           ((uint32_t)0x00000020)        /*!< Transmit underflow status */
#define ETH_DMASTS_RO                           ((uint32_t)0x00000010)        /*!< Receive overflow status */
#define ETH_DMASTS_TJT                          ((uint32_t)0x00000008)        /*!< Transmit jabber timeout status */
#define ETH_DMASTS_TBU                          ((uint32_t)0x00000004)        /*!< Transmit buffer unavailable status */
#define ETH_DMASTS_TPS                          ((uint32_t)0x00000002)        /*!< Transmit process stopped status */
#define ETH_DMASTS_TX                           ((uint32_t)0x00000001)        /*!< Transmit status */

/************* Bit definition for Ethernet DMA Operation Mode Register *************/
#define ETH_DMAOPM_DTCEFD                       ((uint32_t)0x04000000)        /*!< Disable Dropping of TCP/IP checksum error frames */
#define ETH_DMAOPM_RSFD                         ((uint32_t)0x02000000)        /*!< Receive store and forward */
#define ETH_DMAOPM_DFRFD                        ((uint32_t)0x01000000)        /*!< Disable flushing of received frames */
#define ETH_DMAOPM_TXSF                         ((uint32_t)0x00200000)        /*!< Transmit store and forward */
#define ETH_DMAOPM_FTXF                         ((uint32_t)0x00100000)        /*!< Flush transmit FIFO */

#define ETH_DMAOPM_TXTC                         ((uint32_t)0x0001C000)        /*!< Transmit threshold control */
#define ETH_DMAOPM_TXTC_64Bytes                 ((uint32_t)0x00000000)        /*!< threshold level of the MTL Transmit FIFO is 64 Bytes */
#define ETH_DMAOPM_TXTC_128Bytes                ((uint32_t)0x00004000)        /*!< threshold level of the MTL Transmit FIFO is 128 Bytes */
#define ETH_DMAOPM_TXTC_192Bytes                ((uint32_t)0x00008000)        /*!< threshold level of the MTL Transmit FIFO is 192 Bytes */
#define ETH_DMAOPM_TXTC_256Bytes                ((uint32_t)0x0000C000)        /*!< threshold level of the MTL Transmit FIFO is 256 Bytes */
#define ETH_DMAOPM_TXTC_40Bytes                 ((uint32_t)0x00010000)        /*!< threshold level of the MTL Transmit FIFO is 40 Bytes */
#define ETH_DMAOPM_TXTC_32Bytes                 ((uint32_t)0x00014000)        /*!< threshold level of the MTL Transmit FIFO is 32 Bytes */
#define ETH_DMAOPM_TXTC_24Bytes                 ((uint32_t)0x00018000)        /*!< threshold level of the MTL Transmit FIFO is 24 Bytes */
#define ETH_DMAOPM_TXTC_16Bytes                 ((uint32_t)0x0001C000)        /*!< threshold level of the MTL Transmit FIFO is 16 Bytes */

#define ETH_DMAOPM_STXE                         ((uint32_t)0x00002000)        /*!< Start/stop transmission command */
#define ETH_DMAOPM_FEF                          ((uint32_t)0x00000080)        /*!< Forward error frames */
#define ETH_DMAOPM_FUGF                         ((uint32_t)0x00000040)        /*!< Forward undersized good frames */

#define ETH_DMAOPM_RXTC                         ((uint32_t)0x00000018)        /*!< receive threshold control */
#define ETH_DMAOPM_RXTC_64Bytes                 ((uint32_t)0x00000000)        /*!< threshold level of the MTL Receive FIFO is 64 Bytes */
#define ETH_DMAOPM_RXTC_32Bytes                 ((uint32_t)0x00000008)        /*!< threshold level of the MTL Receive FIFO is 32 Bytes */
#define ETH_DMAOPM_RXTC_96Bytes                 ((uint32_t)0x00000010)        /*!< threshold level of the MTL Receive FIFO is 96 Bytes */
#define ETH_DMAOPM_RXTC_128Bytes                ((uint32_t)0x00000018)        /*!< threshold level of the MTL Receive FIFO is 128 Bytes */

#define ETH_DMAOPM_OPSF                         ((uint32_t)0x00000004)        /*!< operate on second frame */
#define ETH_DMAOPM_SRXE                         ((uint32_t)0x00000002)        /*!< Start/stop receive */

/************ Bit definition for Ethernet DMA Interrupt Enable Register ************/
#define ETH_DMAIE_NISE                          ((uint32_t)0x00010000)        /*!< Normal interrupt summary enable */
#define ETH_DMAIE_AISE                          ((uint32_t)0x00008000)        /*!< Abnormal interrupt summary enable */
#define ETH_DMAIE_ERIE                          ((uint32_t)0x00004000)        /*!< Early receive interrupt enable */
#define ETH_DMAIE_FBEIE                         ((uint32_t)0x00002000)        /*!< Fatal bus error interrupt enable */
#define ETH_DMAIE_ETIE                          ((uint32_t)0x00000400)        /*!< Early transmit interrupt enable */
#define ETH_DMAIE_RXWTIE                        ((uint32_t)0x00000200)        /*!< Receive watchdog timeout interrupt enable */
#define ETH_DMAIE_RXPSIE                        ((uint32_t)0x00000100)        /*!< Receive process stopped interrupt enable */
#define ETH_DMAIE_RXBUIE                        ((uint32_t)0x00000080)        /*!< Receive buffer unavailable interrupt enable */
#define ETH_DMAIE_RXIE                          ((uint32_t)0x00000040)        /*!< Receive interrupt enable */
#define ETH_DMAIE_TUIE                          ((uint32_t)0x00000020)        /*!< Transmit Underflow interrupt enable */
#define ETH_DMAIE_ROIE                          ((uint32_t)0x00000010)        /*!< Receive Overflow interrupt enable */
#define ETH_DMAIE_TXJTIE                        ((uint32_t)0x00000008)        /*!< Transmit jabber timeout interrupt enable */
#define ETH_DMAIE_TXBUIE                        ((uint32_t)0x00000004)        /*!< Transmit buffer unavailable interrupt enable */
#define ETH_DMAIE_TXPSIE                        ((uint32_t)0x00000002)        /*!< Transmit process stopped interrupt enable */
#define ETH_DMAIE_TXIE                          ((uint32_t)0x00000001)        /*!< Transmit interrupt enable */

/** Bit definition for Ethernet DMA Missed Frame and Buffer Overflow Counter Register */
#define ETH_DMAMFBOCNT_OFOC                     ((uint32_t)0x10000000)        /*!< Overflow bit for FIFO overflow counter */
#define ETH_DMAMFBOCNT_MFA                      ((uint32_t)0x0FFE0000)        /*!< Number of frames missed by the application */
#define ETH_DMAMFBOCNT_OMFC                     ((uint32_t)0x00010000)        /*!< Overflow bit for missed frame counter */
#define ETH_DMAMFBOCNT_MFC                      ((uint32_t)0x0000FFFF)        /*!< Number of frames missed by the controller */

/** Bit definition for Ethernet DMA Current Host Transmit Descriptor Register */
#define ETH_DMACTD_HTDAP                        ((uint32_t)0xFFFFFFFF)        /*!< Host transmit descriptor address pointer */

/** Bit definition for Ethernet DMA Current Host Receive Descriptor Register */
#define ETH_DMACRD_HRDAP                        ((uint32_t)0xFFFFFFFF)        /*!< Host receive descriptor address pointer */

/** Bit definition for Ethernet DMA Current Host Transmit Buffer Address Register */
#define ETH_DMACTBADDR_HTBAP                    ((uint32_t)0xFFFFFFFF)        /*!< Host transmit buffer address pointer */

/** Bit definition for Ethernet DMA Current Host Receive Buffer Address Register */
#define ETH_DMACRBADDR_HRBAP                    ((uint32_t)0xFFFFFFFF)        /*!< Host receive buffer address pointer */
#endif /* AT32F407xx */

/**
  * @}
  */

/**
 * @}
 */

#if defined (LIBRARY_VERSION) || defined (USE_STDPERIPH_DRIVER)
#include "at32f4xx_conf.h"
#endif

/** @addtogroup Exported_macro
  * @{
  */

#define BIT_SET(REG, BIT)                       ((REG) |= (BIT))

#define BIT_CLEAR(REG, BIT)                     ((REG) &= ~(BIT))

#define BIT_READ(REG, BIT)                      ((REG) & (BIT))

#define REG_CLEAR(REG)                          ((REG) = (0x0))

#define REG_WRITE(REG, VAL)                     ((REG) = (VAL))

#define REG_READ(REG)                           ((REG))

#define REG_CHANGE(REG, CLEARMASK, SETMASK)     REG_WRITE((REG), (((REG_READ(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_H */

/**
  * @}
  */

/**
* @}
*/
