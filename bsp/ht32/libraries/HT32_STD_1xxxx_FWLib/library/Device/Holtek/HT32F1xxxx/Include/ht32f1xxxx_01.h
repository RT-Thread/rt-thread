/***************************************************************************//**
 * @file    ht32f1xxxx_01.h
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File
 * @version $Rev:: 2914         $
 * @date    $Date:: 2023-05-18 #$
 *
 * @note
 * Copyright (C) Holtek Semiconductor Inc. All rights reserved.
 *
 * @par
 * Holtek supplies this software for Cortex-M processor-based
 * microcontrollers.  This file can be freely distributed within
 * development tools that are supporting such ARM-based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

// Supported Device
// ========================================
//   HT32F1653, HT32F1654
//   HT32F1655, HT32F1656
//   HT32F12345
//   HT32F12365, HT32F12366
//   HT32F22366
//   HT32F12364

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup HT32F1xxxx HT32F1xxxx
  * @{
  */


#ifndef __HT32F1XXXX_01_H__
#define __HT32F1XXXX_01_H__

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined(USE_HT32F1653_54) && \
    !defined(USE_HT32F1655_56) && \
    !defined(USE_HT32F12345) && \
    !defined(USE_HT32F12365_66) && \
    !defined(USE_HT32F12364)

  //#define USE_HT32F1653_54
  //#define USE_HT32F1655_56
  //#define USE_HT32F12345
  //#define USE_HT32F12365_66

#endif

#if !defined(USE_NOCHIP) && \
    !defined(USE_HT32F1653_54) && \
    !defined(USE_HT32F1655_56) && \
    !defined(USE_HT32F12345) && \
    !defined(USE_HT32F12365_66) && \
    !defined(USE_HT32F12364)

  #error Please add "USE_HT32Fxxxxx_xx" define into C Preprocessor Symbols of the Project configuration.

#endif

/** @addtogroup Library_configuration_section
  * @{
  */
/**
 * @brief Value of the High Speed Internal oscillator in Hz
  */
#define HSI_VALUE         8000000UL   /*!< Value of the High Speed Internal oscillator in Hz                */

/**
 * @brief Value of the Low Speed Internal oscillator in Hz
  */
#define LSI_VALUE         32000UL     /*!< Value of the Low Speed Internal oscillator in Hz                 */

/**
 * @brief Value of the Low Speed External oscillator in Hz
  */
#define LSE_VALUE         32768UL     /*!< Value of the Low Speed External oscillator in Hz                 */

/**
 * @brief Adjust the High Speed External oscillator (HSE) Startup Timeout value
   */
#define HSE_READY_TIME    ((uint16_t)0xFFFF)    /*!< Time out for HSE start up                              */
/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */
#define __MPU_PRESENT             0    /*!< MPU present or not                                              */
#define __NVIC_PRIO_BITS          4    /*!< Number of Bits used for Priority Levels                         */
#define __Vendor_SysTickConfig    0    /*!< Set to 1 if different SysTick Config is used                    */

/**
  * @}
  */


/** @addtogroup Configuration_for_Interrupt_Number
  * @{
  */
typedef enum IRQn
{
/****** Cortex-M3 Processor Exceptions Numbers ******************************                               */
  NonMaskableInt_IRQn     = -14,    /*!< 2 Non Maskable Interrupt                                           */
  HardFault_IRQn          = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                                   */
  MemoryManagement_IRQn   = -12,    /*!< 4 Cortex-M3 Memory Management Int                                  */
  BusFault_IRQn           = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                                    */
  UsageFault_IRQn         = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                                  */
  SVCall_IRQn             = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                                     */
  DebugMonitor_IRQn       = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                               */
  PendSV_IRQn             = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                                     */
  SysTick_IRQn            = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                                 */

/******  HT32 Specific Interrupt Numbers ************************************                               */
  CKRDY_IRQn              = 0,      /*!< Clock ready interrupt                                              */
  LVD_IRQn                = 1,      /*!< Low voltage detection interrupt                                    */
  BOD_IRQn                = 2,      /*!< Brown-Out detection interrupt                                      */
  #if defined(USE_HT32F1653_54) || defined(USE_HT32F1655_56)
  WDT_IRQn                = 3,      /*!< WDT global interrupt                                               */
  #endif
  RTC_IRQn                = 4,      /*!< RTC Wake-up Interrupt                                              */
  FLASH_IRQn              = 5,      /*!< FLASH global Interrupt                                             */
  EVWUP_IRQn              = 6,      /*!< Event Wake-up Interrupt                                            */
  LPWUP_IRQn              = 7,      /*!< WAKEUP pin Interrupt                                               */
  EXTI0_IRQn              = 8,      /*!< EXTI0 Line detection Interrupt                                     */
  EXTI1_IRQn              = 9,      /*!< EXTI1 Line detection Interrupt                                     */
  EXTI2_IRQn              = 10,     /*!< EXTI2 Line detection Interrupt                                     */
  EXTI3_IRQn              = 11,     /*!< EXTI3 Line detection Interrupt                                     */
  EXTI4_IRQn              = 12,     /*!< EXTI4 Line detection Interrupt                                     */
  EXTI5_IRQn              = 13,     /*!< EXTI5 Line detection Interrupt                                     */
  EXTI6_IRQn              = 14,     /*!< EXTI6 Line detection Interrupt                                     */
  EXTI7_IRQn              = 15,     /*!< EXTI7 Line detection Interrupt                                     */
  EXTI8_IRQn              = 16,     /*!< EXTI8 Line detection Interrupt                                     */
  EXTI9_IRQn              = 17,     /*!< EXTI9 Line detection Interrupt                                     */
  EXTI10_IRQn             = 18,     /*!< EXTI10 Line detection Interrupt                                    */
  EXTI11_IRQn             = 19,     /*!< EXTI11 Line detection Interrupt                                    */
  EXTI12_IRQn             = 20,     /*!< EXTI12 Line detection Interrupt                                    */
  EXTI13_IRQn             = 21,     /*!< EXTI13 Line detection Interrupt                                    */
  EXTI14_IRQn             = 22,     /*!< EXTI14 Line detection Interrupt                                    */
  EXTI15_IRQn             = 23,     /*!< EXTI15 Line detection Interrupt                                    */
  #if !defined(USE_HT32F12364)
  COMP_IRQn               = 24,     /*!< Comparator global Interrupt                                        */
  #endif
  ADC0_IRQn               = 25,     /*!< ADC Interrupt                                                      */
  #if !defined(USE_HT32F12364)
  MCTM0BRK_IRQn           = 27,     /*!< MCTM0 BRK interrupt                                                */
  MCTM0UP_IRQn            = 28,     /*!< MCTM0 UP interrupt                                                 */
  MCTM0TR_IRQn            = 29,     /*!< MCTM0 TR interrupt                                                 */
  MCTM0CC_IRQn            = 30,     /*!< MCTM0 CC interrupt                                                 */
  MCTM1BRK_IRQn           = 31,     /*!< MCTM1 BRK interrupt                                                */
  MCTM1UP_IRQn            = 32,     /*!< MCTM1 UP interrupt                                                 */
  MCTM1TR_IRQn            = 33,     /*!< MCTM1 TR interrupt                                                 */
  MCTM1CC_IRQn            = 34,     /*!< MCTM1 CC interrupt                                                 */
  #endif
  GPTM0_IRQn              = 35,     /*!< General-Purpose Timer0 Interrupt                                   */
  #if !defined(USE_HT32F12364)
  GPTM1_IRQn              = 36,     /*!< General-Purpose Timer1 Interrupt                                   */
  #endif
  #if defined(USE_HT32F12364)
  SCTM0_IRQn              = 37,     /*!< Single-Channel Timer0 Interrupt                                    */
  SCTM1_IRQn              = 38,     /*!< Single-Channel Timer1 Interrupt                                    */
  PWM0_IRQn               = 39,     /*!< Pulse Width Modulator Timer0 Interrupt                             */
  #endif
  BFTM0_IRQn              = 41,     /*!< Basic Function Timer0 interrupt                                    */
  BFTM1_IRQn              = 42,     /*!< Basic Function Timer1 interrupt                                    */
  I2C0_IRQn               = 43,     /*!< I2C0 global Interrupt                                              */
  I2C1_IRQn               = 44,     /*!< I2C1 global Interrupt                                              */
  SPI0_IRQn               = 45,     /*!< SPI0 global Interrupt                                              */
  SPI1_IRQn               = 46,     /*!< SPI1 global Interrupt                                              */
  USART0_IRQn             = 47,     /*!< USART0 global Interrupt                                            */
  #if !defined(USE_HT32F12364)
  USART1_IRQn             = 48,     /*!< USART1 global Interrupt                                            */
  #endif
  UART0_IRQn              = 49,     /*!< UART0 global Interrupt                                             */
  UART1_IRQn              = 50,     /*!< UART1 global Interrupt                                             */
  #if !defined(USE_HT32F12345)
  SCI_IRQn                = 51,     /*!< Smart Card interface interrupt                                     */
  #endif
  #if !defined(USE_HT32F12364)
  I2S_IRQn                = 52,     /*!< I2S global Interrupt                                               */
  #endif
  USB_IRQn                = 53,     /*!< USB interrupt                                                      */
  #if defined(USE_HT32F12365_66) || defined(USE_HT32F12345)
  SDIO_IRQn               = 54,     /*!< SDIO interrupt                                                     */
  #endif
  PDMACH0_IRQn            = 55,     /*!< PDMA channel 0 global interrupt                                    */
  PDMACH1_IRQn            = 56,     /*!< PDMA channel 1 global interrupt                                    */
  PDMACH2_IRQn            = 57,     /*!< PDMA channel 2 global interrupt                                    */
  PDMACH3_IRQn            = 58,     /*!< PDMA channel 3 global interrupt                                    */
  PDMACH4_IRQn            = 59,     /*!< PDMA channel 4 global interrupt                                    */
  PDMACH5_IRQn            = 60,     /*!< PDMA channel 5 global interrupt                                    */
  #if !defined(USE_HT32F12364)
  PDMACH6_IRQn            = 61,     /*!< PDMA channel 6 global interrupt                                    */
  PDMACH7_IRQn            = 62,     /*!< PDMA channel 7 global interrupt                                    */
  #endif
  #if defined(USE_HT32F12365_66) || defined(USE_HT32F12345)
  PDMACH8_IRQn            = 63,     /*!< PDMA channel 8 global interrupt                                    */
  PDMACH9_IRQn            = 64,     /*!< PDMA channel 9 global interrupt                                    */
  PDMACH10_IRQn           = 65,     /*!< PDMA channel 10 global interrupt                                   */
  PDMACH11_IRQn           = 66,     /*!< PDMA channel 11 global interrupt                                   */
  #endif
  #if defined(USE_HT32F12365_66)
  CSIF_IRQn               = 67,     /*!< CMOS sensor interface interrupt                                    */
  #endif
  #if !defined(USE_HT32F12364)
  EBI_IRQn                = 68,     /*!< External bus interface interrupt                                   */
  #endif
  #if defined(USE_HT32F12365_66) || defined(USE_HT32F12364)
  AES_IRQn                = 69,     /*!< AES interrupt                                                      */
  #endif
} IRQn_Type;

#define MCTM0_IRQn               MCTM0UP_IRQn
#define MCTM0_IRQHandler         MCTM0UP_IRQHandler
#define MCTM1_IRQn               MCTM1UP_IRQn
#define MCTM1_IRQHandler         MCTM1UP_IRQHandler


/**
  * @}
  */

#include "core_cm3.h"                  /* Cortex-M3 processor and core peripherals                          */
#include "system_ht32f1xxxx_01.h"      /* HT32 system                                                       */


/** @addtogroup Exported_Types
  * @{
  */

typedef signed long long s64;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

typedef const s64      sc64;          /*!< Read Only                                                        */
typedef const s32      sc32;          /*!< Read Only                                                        */
typedef const s16      sc16;          /*!< Read Only                                                        */
typedef const s8       sc8;           /*!< Read Only                                                        */

typedef __IO s64       vs64;
typedef __IO s32       vs32;
typedef __IO s16       vs16;
typedef __IO s8        vs8;

typedef __I s64        vsc64;         /*!< Read Only                                                        */
typedef __I s32        vsc32;         /*!< Read Only                                                        */
typedef __I s16        vsc16;         /*!< Read Only                                                        */
typedef __I s8         vsc8;          /*!< Read Only                                                        */

typedef unsigned long long u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef const u64      uc64;          /*!< Read Only                                                        */
typedef const u32      uc32;          /*!< Read Only                                                        */
typedef const u16      uc16;          /*!< Read Only                                                        */
typedef const u8       uc8;           /*!< Read Only                                                        */

typedef __IO u64       vu64;
typedef __IO u32       vu32;
typedef __IO u16       vu16;
typedef __IO u8        vu8;

typedef __I u64        vuc64;         /*!< Read Only                                                        */
typedef __I u32        vuc32;         /*!< Read Only                                                        */
typedef __I u16        vuc16;         /*!< Read Only                                                        */
typedef __I u8         vuc8;          /*!< Read Only                                                        */


typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;

#if !defined(bool) && !defined(__cplusplus) // user may already included <stdbool.h> or CPP
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#define false FALSE
#define true  TRUE
#else
#define FALSE 0
#define TRUE  1
#endif

typedef enum {RESET = 0, SET = !RESET} FlagStatus;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/**
  * @}
  */

#if defined (__CC_ARM)
  #define __ALIGN4 __align(4)
#elif defined (__ICCARM__)
  #define __ALIGN4 _Pragma("data_alignment = 4")
#elif defined (__GNUC__)
  #define __ALIGN4  __attribute__((aligned(4)))
#endif

#if defined (__GNUC__)
  #define __PACKED_H
  #define __PACKED_F __attribute__ ((packed))
#elif defined (__ICCARM__) || (__CC_ARM)
  #define __PACKED_H __packed
  #define __PACKED_F
#endif

#if defined (__CC_ARM)
#pragma anon_unions
#endif


#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)


/**
 * @brief Exported constants and macro
 */
#define IS_CONTROL_STATUS(STATUS) ((STATUS == DISABLE) || (STATUS == ENABLE))

#define wb(addr, value)     (*((u8  volatile *) (addr)) = value)
#define rb(addr)            (*((u8  volatile *) (addr)))
#define whw(addr, value)    (*((u16 volatile *) (addr)) = value)
#define rhw(addr)           (*((u16 volatile *) (addr)))
#define ww(addr, value)     (*((u32 volatile *) (addr)) = value)
#define rw(addr)            (*((u32 volatile *) (addr)))


#define ResetBit_BB(Addr, BitNumber) (*(vu32 *) ((Addr & 0xF0000000) + 0x02000000 + \
                                      ((Addr & 0xFFFFF) << 5) + (BitNumber << 2)) = 0)
#define SetBit_BB(Addr, BitNumber)   (*(vu32 *) ((Addr & 0xF0000000) + 0x02000000 + \
                                      ((Addr & 0xFFFFF) << 5) + (BitNumber << 2)) = 1)
#define GetBit_BB(Addr, BitNumber)   (*(vu32 *) ((Addr & 0xF0000000) + 0x02000000 + \
                                      ((Addr & 0xFFFFF) << 5) + (BitNumber << 2)))
#define BitBand(Addr, BitNumber)     (*(vu32 *) ((Addr & 0xF0000000) + 0x02000000 + \
                                     ((Addr & 0xFFFFF) << 5) + (BitNumber << 2)))

#define STRCAT2_(a, b)       a##b
#define STRCAT2(a, b)        STRCAT2_(a, b)
#define STRCAT3_(a, b, c)    a##b##c
#define STRCAT3(a, b, c)     STRCAT3_(a, b, c)

#define IPN_NULL                        (0)
#define IPN_MCTM0                       (0x4002C000)
#define IPN_MCTM1                       (0x4002D000)
#define IPN_GPTM0                       (0x4006E000)
#define IPN_GPTM1                       (0x4006F000)
#define IPN_CHECK(IP)                   STRCAT2(IPN_, IP)
#define IS_IPN_MCTM(IP)                 (IPN_CHECK(IP) == IPN_MCTM0) || (IPN_CHECK(IP) == IPN_MCTM1)
#define IS_IPN_GPTM(IP)                 (IPN_CHECK(IP) == IPN_GPTM0) || (IPN_CHECK(IP) == IPN_GPTM1)


/** @addtogroup Peripheral_Registers_Structures
  * @{
  */


/**
 * @brief Universal Synchronous Asynchronous Receiver Transmitter
 */
typedef struct
{
                                 /* USART0: 0x40000000                                                      */
                                 /* USART1: 0x40040000                                                      */
                                 /* UART0:  0x40001000                                                      */
                                 /* UART1:  0x40041000                                                      */
  #if defined(USE_HT32F1653_54) || defined(USE_HT32F1655_56)
  union {
  __IO uint32_t DR;              /*!< 0x000         Data Register                                           */
  __IO uint32_t RBR;             /*!< 0x000         Receive Buffer Register                                 */
  __IO uint32_t TBR;             /*!< 0x000         Transmit Holding Register                               */
  };
  __IO uint32_t IER;             /*!< 0x004         Interrupt Enable Register                               */
  __IO uint32_t IIR;             /*!< 0x008         Interrupt Identification Register/FIFO Control Register */
  __IO uint32_t FCR;             /*!< 0x00C         FIFO Control Register                                   */
  __IO uint32_t LCR;             /*!< 0x010         Line Control Register                                   */
  __IO uint32_t MCR;             /*!< 0x014         Modem Control Register                                  */
  union {
  __IO uint32_t LSR;             /*!< 0x018         Line Status Register                                    */
  __IO uint32_t SR;              /*!< 0x018         Line Status Register                                    */
  };
  __IO uint32_t MSR;             /*!< 0x01C         Modem Status Register                                   */
  __IO uint32_t TPR;             /*!< 0x020         Timing Parameter Register                               */
  __IO uint32_t MDR;             /*!< 0x024         Mode Register                                           */
  __IO uint32_t ICR;             /*!< 0x028         IrDA Register                                           */
  __IO uint32_t RCR;             /*!< 0x02C         RS485 Control Register                                  */
  __IO uint32_t SCR;             /*!< 0x030         Synchronous Control Register                            */
  __IO uint32_t FSR;             /*!< 0x034         FIFO Status Register                                    */
  __IO uint32_t DLR;             /*!< 0x038         Divisor Latch Register                                  */
  __IO uint32_t DTR;             /*!< 0x040         Debug/Test Register                                     */
  #else
  __IO uint32_t DR;              /*!< 0x000         Data Register                                           */
  __IO uint32_t CR;              /*!< 0x004         Control Register                                        */
  __IO uint32_t FCR;             /*!< 0x008         FIFO Control Register                                   */
  __IO uint32_t IER;             /*!< 0x00C         Interrupt Enable Register                               */
  __IO uint32_t SR;              /*!< 0x010         Status Register                                         */
  __IO uint32_t TPR;             /*!< 0x014         Timing Parameter Register                               */
  __IO uint32_t ICR;             /*!< 0x018         IrDA COntrol Register                                   */
  __IO uint32_t RCR;             /*!< 0x01C         RS485 Control Register                                  */
  __IO uint32_t SCR;             /*!< 0x020         Synchronous Control Register                            */
  __IO uint32_t DLR;             /*!< 0x024         Divisor Latch Register                                  */
  __IO uint32_t DTR;             /*!< 0x028         Debug/Test Register                                     */
  #endif
} HT_USART_TypeDef;


/**
 * @brief SPI
 */
typedef struct
{
                                 /* SPI0: 0x40004000                                                        */
                                 /* SPI1: 0x40044000                                                        */
  __IO uint32_t CR0;             /*!< 0x000         Control Register 0                                      */
  __IO uint32_t CR1;             /*!< 0x004         Control Register 1                                      */
  __IO uint32_t IER;             /*!< 0x008         Interrupt Enable Register                               */
  __IO uint32_t CPR;             /*!< 0x00C         Clock Prescaler Register                                */
  __IO uint32_t DR;              /*!< 0x010         Data Register                                           */
  __IO uint32_t SR;              /*!< 0x014         Status Register                                         */
  __IO uint32_t FCR;             /*!< 0x018         FIFO Control Register                                   */
  __IO uint32_t FSR;             /*!< 0x01C         FIFO Status Register                                    */
  __IO uint32_t FTOCR;           /*!< 0x020         FIFO Time Out Counter Register                          */
} HT_SPI_TypeDef;


/**
 * @brief Analog to Digital Converter
 */
typedef struct
{
                                 /* ADC: 0x40010000                                                         */
#if defined(USE_HT32F12364)
  __IO uint32_t CR;              /*!< 0x000         ADC Conversion Control Register                         */
  __IO uint32_t LST[2];          /*!< 0x004 - 0x008 ADC Conversion List Register 0-1                        */
       uint32_t RESERVE0[5];     /*!< 0x00C - 0x01C Reserved                                                */
  __IO uint32_t STR;             /*!< 0x020         ADC Input Sampling Time Register                        */
       uint32_t RESERVE1[3];     /*!< 0x024 - 0x02C Reserved                                                */
  __IO uint32_t DR[8];           /*!< 0x030 - 0x04C ADC Conversion Data Register 0-7                        */
       uint32_t RESERVE2[8];     /*!< 0x050 - 0x06C Reserved                                                */
  __IO uint32_t TCR;             /*!< 0x070         ADC Trigger Control Register                            */
  __IO uint32_t TSR;             /*!< 0x074         ADC Trigger Source Register                             */
  __IO uint32_t WCR;             /*!< 0x078         ADC Watchdog Control Register                           */
  __IO uint32_t WTR;             /*!< 0x07C         ADC Watchdog Threshold Register                         */
  __IO uint32_t IER;             /*!< 0x080         ADC Interrupt Enable Register                           */
  __IO uint32_t IRAW;            /*!< 0x084         ADC Interrupt Raw Status Register                       */
  __IO uint32_t ISR;             /*!< 0x088         ADC Interrupt Status Register                           */
  __IO uint32_t ICLR;            /*!< 0x08C         ADC Interrupt Clear Register                            */
  __IO uint32_t PDMAR;           /*!< 0x090         ADC PDMA Request Register                               */
       uint32_t RESERVE3[3];     /*!< 0x094 - 0x09C Reserved                                                */
  __IO uint32_t VREFCR;          /*!< 0x0A0         ADC Reference Voltage Control Register                  */
  __IO uint32_t VREFVALR;        /*!< 0x0A4         ADC Reference Voltage Value Register                    */
#else
       uint32_t RESERVE0[1];     /*!< 0x000         Reserved                                                */
  __IO uint32_t RST;             /*!< 0x004         ADC Reset Register                                      */
  __IO uint32_t CONV;            /*!< 0x008         ADC Regular Conversion Mode Register                    */
  __IO uint32_t HCONV;           /*!< 0x00C         ADC High-priority Conversion Mode Register              */
  __IO uint32_t LST[4];          /*!< 0x010 - 0x01C ADC Regular Conversion List Register 0-3                */
  __IO uint32_t HLST;            /*!< 0x020         ADC High-priority Conversion List Register              */
       uint32_t RESERVE1[3];     /*!< 0x024 - 0x02C Reserved                                                */
  __IO uint32_t OFR[16];         /*!< 0x030 - 0x06C ADC Input Offset Register 0-15                          */
  __IO uint32_t STR[16];         /*!< 0x070 - 0x0AC ADC Input Sampling Time Register 0-15                   */
  __IO uint32_t DR[16];          /*!< 0x0B0 - 0x0EC ADC Regular Conversion Data Register 0-15               */
  __IO uint32_t HDR[4];          /*!< 0x0F0 - 0x0FC ADC High-priority Conversion Data Register 0-3          */
  __IO uint32_t TCR;             /*!< 0x100         ADC Regular Trigger Control Register                    */
  __IO uint32_t TSR;             /*!< 0x104         ADC Regular Trigger Source Register                     */
       uint32_t RESERVE2[2];     /*!< 0x108 - 0x10C Reserved                                                */
  __IO uint32_t HTCR;            /*!< 0x110         ADC High-priority Trigger Control Register              */
  __IO uint32_t HTSR;            /*!< 0x114         ADC High-priority Trigger Source Register               */
       uint32_t RESERVE3[2];     /*!< 0x118 - 0x11C Reserved                                                */
  __IO uint32_t WCR;             /*!< 0x120         ADC Watchdog Control Register                           */
  __IO uint32_t LTR;             /*!< 0x124         ADC Lower Threshold Register                            */
  __IO uint32_t UTR;             /*!< 0x128         ADC Upper Threshold Register                            */
       uint32_t RESERVE4[1];     /*!< 0x12C         Reserved                                                */
  __IO uint32_t IER;             /*!< 0x130         ADC Interrupt Enable Register                           */
  __IO uint32_t IRAW;            /*!< 0x134         ADC Interrupt Raw Status Register                       */
  __IO uint32_t ISR;             /*!< 0x138         ADC Interrupt Status Register                           */
  __IO uint32_t ICLR;            /*!< 0x13C         ADC Interrupt Clear Register                            */
  __IO uint32_t PDMAR;           /*!< 0x140         ADC PDMA Request Register                               */
#endif
} HT_ADC_TypeDef;


/**
 * @brief Op Amp/Comparator
 */
typedef struct
{
                                 /* CMP_OP0: 0x40018000                                                     */
                                 /* CMP_OP1: 0x40018100                                                     */
  __IO uint32_t OPACR;           /*!< 0x000         Operational Amplifier control register                  */
  __IO uint32_t OFVCR;           /*!< 0x004         Comparator input offset voltage cancellation register   */
  __IO uint32_t CMPIER;          /*!< 0x008         Comparator interrupt enable register                    */
  __IO uint32_t CMPRSR;          /*!< 0x00C         Comparator raw status register                          */
  __IO uint32_t CMPISR;          /*!< 0x010         Comparator interrupt status register                    */
  __IO uint32_t CMPICLR;         /*!< 0x014         Comparator interrupt clear register                     */
} HT_CMP_OP_TypeDef;

/**
 * @brief Comparator
 */
typedef struct
{
                                 /* CMP0: 0x40058000                                                        */
                                 /* CMP1: 0x40058100                                                        */
  __IO uint32_t CR;              /*!< 0x000          Comparator Control Register                            */
  __IO uint32_t VALR;            /*!< 0x004          Comparator Voltage Reference Value Register            */
  __IO uint32_t IER;             /*!< 0x008          Comparator Interrupt Enable Register                   */
  __IO uint32_t TFR;             /*!< 0x00C          Comparator Transition Flag Register                    */
} HT_CMP_TypeDef;


/**
 * @brief General Purpose I/O
 */
typedef struct
{
                                 /* GPIOA: 0x400B0000                                                       */
                                 /* GPIOB: 0x400B2000                                                       */
                                 /* GPIOC: 0x400B4000                                                       */
                                 /* GPIOD: 0x400B6000                                                       */
                                 /* GPIOE: 0x400B8000                                                       */
                                 /* GPIOF: 0x400BA000                                                       */
  __IO uint32_t DIRCR;           /*!< 0x000         Data Direction Control Register                         */
  __IO uint32_t INER;            /*!< 0x004         Input function enable register                          */
  __IO uint32_t PUR;             /*!< 0x008         Pull-Up Selection Register                              */
  __IO uint32_t PDR;             /*!< 0x00C         Pull-Down Selection Register                            */
  __IO uint32_t ODR;             /*!< 0x010         Open Drain Selection Register                           */
  __IO uint32_t DRVR;            /*!< 0x014         Drive Current Selection Register                        */
  __IO uint32_t LOCKR;           /*!< 0x018         Lock Register                                           */
  __IO uint32_t DINR;            /*!< 0x01c         Data Input Register                                     */
  __IO uint32_t DOUTR;           /*!< 0x020         Data Output Register                                    */
  __IO uint32_t SRR;             /*!< 0x024         Output Set and Reset Control Register                   */
  __IO uint32_t RR;              /*!< 0x028         Output Reset Control Register                           */
} HT_GPIO_TypeDef;


/**
 * @brief AFIO
 */
typedef struct
{
                                 /* AFIO: 0x40022000                                                        */
  __IO uint32_t ESSR[2];         /*!< 0x000         EXTI Source Selection Register 0 ~ 1                    */
       uint32_t RESERVE0[6];     /*!< 0x008 - 0x01C Reserved                                                */
  __IO uint32_t GPACFGR[2];      /*!< 0x020         GPIO Port A Configuration Register 0 ~ 1                */
  __IO uint32_t GPBCFGR[2];      /*!< 0x028         GPIO Port B Configuration Register 0 ~ 1                */
  __IO uint32_t GPCCFGR[2];      /*!< 0x030         GPIO Port C Configuration Register 0 ~ 1                */
  __IO uint32_t GPDCFGR[2];      /*!< 0x038         GPIO Port D Configuration Register 0 ~ 1                */
#if defined(USE_HT32F1655_56) || defined(USE_HT32F12365_66)
  __IO uint32_t GPECFGR[2];      /*!< 0x040         GPIO Port E Configuration Register 0 ~ 1                */
#else
       uint32_t RESERVE1[2];     /*!< 0x040 - 0x044 Reserved                                                */
#endif
#if defined(USE_HT32F12364)
  __IO uint32_t GPECFGR[2];      /*!< 0x048         GPIO Port F Configuration Register 0 ~ 1                */
#endif
} HT_AFIO_TypeDef;


/**
 * @brief External Interrupt/Event Controller
 */
typedef struct
{
                                 /* EXTI: 0x40024000                                                        */
  __IO uint32_t CFGR0;           /*!< 0x000         EXTI Interrupt 0 Configuration Register                 */
  __IO uint32_t CFGR1;           /*!< 0x004         EXTI Interrupt 1 Configuration Register                 */
  __IO uint32_t CFGR2;           /*!< 0x008         EXTI Interrupt 2 Configuration Register                 */
  __IO uint32_t CFGR3;           /*!< 0x00C         EXTI Interrupt 3 Configuration Register                 */
  __IO uint32_t CFGR4;           /*!< 0x010         EXTI Interrupt 4 Configuration Register                 */
  __IO uint32_t CFGR5;           /*!< 0x014         EXTI Interrupt 5 Configuration Register                 */
  __IO uint32_t CFGR6;           /*!< 0x018         EXTI Interrupt 6 Configuration Register                 */
  __IO uint32_t CFGR7;           /*!< 0x01C         EXTI Interrupt 7 Configuration Register                 */
  __IO uint32_t CFGR8;           /*!< 0x020         EXTI Interrupt 8 Configuration Register                 */
  __IO uint32_t CFGR9;           /*!< 0x024         EXTI Interrupt 9 Configuration Register                 */
  __IO uint32_t CFGR10;          /*!< 0x028         EXTI Interrupt 10 Configuration Register                */
  __IO uint32_t CFGR11;          /*!< 0x02C         EXTI Interrupt 11 Configuration Register                */
  __IO uint32_t CFGR12;          /*!< 0x030         EXTI Interrupt 12 Configuration Register                */
  __IO uint32_t CFGR13;          /*!< 0x034         EXTI Interrupt 13 Configuration Register                */
  __IO uint32_t CFGR14;          /*!< 0x038         EXTI Interrupt 14 Configuration Register                */
  __IO uint32_t CFGR15;          /*!< 0x03C         EXTI Interrupt 15 Configuration Register                */
  __IO uint32_t CR;              /*!< 0x040         EXTI Interrupt Control Register                         */
  __IO uint32_t EDGEFLGR;        /*!< 0x044         EXTI Interrupt Edge Flag Register                       */
  __IO uint32_t EDGESR;          /*!< 0x048         EXTI Interrupt Edge Status Register                     */
  __IO uint32_t SSCR;            /*!< 0x04C         EXTI Interrupt Software Set Command Register            */
  __IO uint32_t WAKUPCR;         /*!< 0x050         EXTI Interrupt Wakeup Control Register                  */
  __IO uint32_t WAKUPPOLR;       /*!< 0x054         EXTI Interrupt Wakeup Polarity Register                 */
  __IO uint32_t WAKUPFLG;        /*!< 0x058         EXTI Interrupt Wakeup Flag Register                     */
} HT_EXTI_TypeDef;


/**
 * @brief Inter-integrated Circuit Interface
 */
typedef struct
{
                                 /* I2C0: 0x40048000                                                        */
                                 /* I2C1: 0x40049000                                                        */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t IER;             /*!< 0x004         Interrupt Enable Register                               */
  __IO uint32_t ADDR;            /*!< 0x008         Address Register                                        */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t SHPGR;           /*!< 0x010         SCL High Period Generation Register                     */
  __IO uint32_t SLPGR;           /*!< 0x014         SCL Low Period Generation Register                      */
  __IO uint32_t DR;              /*!< 0x018         Data Register                                           */
  __IO uint32_t TAR;             /*!< 0x01C         Target Register                                         */
  __IO uint32_t ADDMR;           /*!< 0x020         Address Mask Register                                   */
  __IO uint32_t ADDSR;           /*!< 0x024         Address Snoop Register                                  */
  __IO uint32_t TOUT;            /*!< 0x028         Timeout Register                                        */
} HT_I2C_TypeDef;


/**
 * @brief WATCHDOG
 */
typedef struct
{
                                 /* WDT: 0x40068000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t MR0;             /*!< 0x004         Mode 0 Register                                         */
  __IO uint32_t MR1;             /*!< 0x008         Mode 1 Register                                         */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t PR;              /*!< 0x010         Write Protect Register                                  */
#if defined(USE_HT32F1655_56)
  __IO uint32_t CNTR;            /*!< 0x014         Counter Register                                        */
#else
       uint32_t RESERVED0[1];    /*!< 0x014         Reserved                                                */
#endif
  __IO uint32_t CSR;             /*!< 0x018         Clock Selection Register                                */
} HT_WDT_TypeDef;


/**
 * @brief Real-Time Clock
 */
typedef struct
{
                                 /* RTC: 0x4006A000                                                         */
  __IO uint32_t CNT;             /*!< 0x000         RTC Counter Register                                    */
  __IO uint32_t CMP;             /*!< 0x004         RTC Compare Register                                    */
  __IO uint32_t CR;              /*!< 0x008         RTC Control Register                                    */
  __IO uint32_t SR;              /*!< 0x00C         RTC Status Register                                     */
  __IO uint32_t IWEN;            /*!< 0x010         RTC Interrupt/Wake-up Enable Register                   */
} HT_RTC_TypeDef;


/**
 * @brief Power Control Unit
 */
typedef struct
{
                                 /* PWRCU: 0x4006A100                                                       */
  __IO uint32_t SR;              /*!< 0x000         Status Register                                         */
  __IO uint32_t CR;              /*!< 0x004         Control Register                                        */
  __IO uint32_t TEST;            /*!< 0x008         Test Register                                           */
  __IO uint32_t HSIRCR;          /*!< 0x00C         HSI Ready Counter Control Register                      */
  __IO uint32_t LVDCSR;          /*!< 0x010         Low Voltage/Brown Out Detect Control and Status Register*/
       uint32_t RESERVE1[59];    /*!< 0x014 ~ 0x0FC Reserved                                                */
#if !defined(USE_HT32F12364)
  __IO uint32_t BAKREG[10];      /*!< 0x100 ~ 0x124 Backup Register 0 ~ 9                                   */
#endif
} HT_PWRCU_TypeDef;


#if 0
/**
 * @brief General-Purpose Timer
 */
typedef struct
{
                                 /* GPTM0: 0x4006E000                                                       */
                                 /* GPTM1: 0x4006F000                                                       */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[7];    /*!< 0x058 - 0x070  Reserved                                               */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
       uint32_t RESERVED4[1];    /*!< 0x08C          Reserved                                               */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
} HT_GPTM_TypeDef;
#endif


/**
 * @brief Flash Memory Controller
 */
typedef struct
{
                                 /* FLASH: 0x40080000                                                       */
  __IO uint32_t TADR;            /*!< 0x000         Flash Target Address Register                           */
  __IO uint32_t WRDR;            /*!< 0x004         Flash Write Data Register                               */
       uint32_t RESERVED0[1];    /*!< 0x008         Reserved                                                */
  __IO uint32_t OCMR;            /*!< 0x00C         Flash Operation Command Register                        */
  __IO uint32_t OPCR;            /*!< 0x010         Flash Operation Control Register                        */
  __IO uint32_t OIER;            /*!< 0x014         Flash Operation Interrupt Enable Register               */
  __IO uint32_t OISR;            /*!< 0x018         Flash Operation Interrupt and Status Register           */
       uint32_t RESERVED1[1];    /*!< 0x01C         Reserved                                                */
  __IO uint32_t PPSR[4];         /*!< 0x020 ~ 0x02C Flash Page Erase/Program Protection Status Register     */
  __IO uint32_t CPSR;            /*!< 0x030         Flash Security Protection Status Register               */
       uint32_t RESERVED2[51];   /*!< 0x034 ~ 0x0FC Reserved                                                */
  __IO uint32_t VMCR;            /*!< 0x100         Flash Vector Mapping Control Register                   */
       uint32_t RESERVED3[31];   /*!< 0x104 ~ 0x17C Reserved                                                */
  __IO uint32_t MDID;            /*!< 0x180         Manufacturer and Device ID Register                     */
  __IO uint32_t PNSR;            /*!< 0x184         Flash Page Number Status Register                       */
  __IO uint32_t PSSR;            /*!< 0x188         Flash Page Size Status Register                         */
#if defined(USE_HT32F1653_54) | defined(USE_HT32F1655_56)
       uint32_t RESERVED4[29];   /*!< 0x18C ~ 0x1FC Reserved                                                */
#else
  __IO uint32_t DID;             /*!< 0x18C         Device ID Register                                      */
       uint32_t RESERVED4[28];   /*!< 0x190 ~ 0x1FC Reserved                                                */
#endif
  __IO uint32_t CFCR;            /*!< 0x200         Flash Cache and Pre-fetch Control Register              */
       uint32_t RESERVED5[63];   /*!< 0x204 ~ 0x2FC Reserved                                                */
  __IO uint32_t SBVT[4];         /*!< 0x300 ~ 0x30C SRAM Booting Vector (4x32Bit)                           */
#if defined(USE_HT32F1653_54) | defined(USE_HT32F1655_56)
#else
  __IO uint32_t CID[4];          /*!< 0x310 ~ 0x31C Custom ID Register                                      */
#endif
} HT_FLASH_TypeDef;


/**
 * @brief Clock Control Unit
 */
typedef struct
{
                                 /* CKCU: 0x40088000                                                        */
  __IO uint32_t GCFGR;           /*!< 0x000         Global Clock Configuration Register                     */
  __IO uint32_t GCCR;            /*!< 0x004         Global Clock Control Register                           */
  __IO uint32_t GCSR;            /*!< 0x008         Global Clock Status Register                            */
  __IO uint32_t GCIR;            /*!< 0x00C         Global Clock Interrupt Register                         */
       uint32_t RESERVED0[2];    /*!< 0x010 ~ 0x14  Reserved                                                */
  __IO uint32_t PLLCFGR;         /*!< 0x018         PLL Configuration Register                              */
  __IO uint32_t PLLCR;           /*!< 0x01C         PLL Control Register                                    */
  __IO uint32_t AHBCFGR;         /*!< 0x020         AHB Configuration Register                              */
  __IO uint32_t AHBCCR;          /*!< 0x024         AHB Clock Control Register                              */
  __IO uint32_t APBCFGR;         /*!< 0x028         APB Configuration Register                              */
  __IO uint32_t APBCCR0;         /*!< 0x02C         APB Clock Control Register 0                            */
  __IO uint32_t APBCCR1;         /*!< 0x030         APB Clock Control Register 1                            */
  __IO uint32_t CKST;            /*!< 0x034         Clock source status Register                            */
#if defined(USE_HT32F1655_56)
       uint32_t RESERVED1[4];    /*!< 0x038 ~ 0x44  Reserved                                                */
#else
  __IO uint32_t APBPCSR0;        /*!< 0x038         APB Peripheral Clock Selection Register 0               */
  __IO uint32_t APBPCSR1;        /*!< 0x03C         APB Peripheral Clock Selection Register 1               */
  __IO uint32_t HSICR;           /*!< 0x040         HSI Control Register                                    */
  __IO uint32_t HSIATCR;         /*!< 0x044         HSI Auto Trimming Counter Register                      */
#endif
#if defined(USE_HT32F12364)
  __IO uint32_t APBPCSR2;        /*!< 0x048         APB Peripheral Clock Selection Register 2               */
       uint32_t RESERVED2[173];  /*!< 0x04C ~ 0x2FC Reserved                                                */
#else
       uint32_t RESERVED2[174];  /*!< 0x048 ~ 0x2FC Reserved                                                */
#endif
  __IO uint32_t LPCR;            /*!< 0x300         Low Power Control Register                              */
  __IO uint32_t MCUDBGCR;        /*!< 0x304         MCU Debug Control Register                              */
} HT_CKCU_TypeDef;


/**
 * @brief Reset Control Unit
 */
typedef struct
{
                                 /* RSTCU: 0x40088100                                                       */
  __IO uint32_t GRSR;            /*!< 0x000         Global Reset Status Register                            */
  __IO uint32_t AHBPRST;         /*!< 0x004         AHB Peripheral Reset Register                           */
  __IO uint32_t APBPRST0;        /*!< 0x008         APB Peripheral Reset Register 0                         */
  __IO uint32_t APBPRST1;        /*!< 0x00C         APB Peripheral Reset Register 1                         */
} HT_RSTCU_TypeDef;


/**
 * @brief Smart Card Interface
 */
typedef struct
{
                                 /* SCI0: 0x40043000                                                        */
                                 /* SCI1: 0x4003A000                                                        */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t SR;              /*!< 0x004         Status Register                                         */
  __IO uint32_t CCR;             /*!< 0x008         Contact Control Register                                */
  __IO uint32_t ETU;             /*!< 0x00C         Elementary Time Unit Register                           */
  __IO uint32_t GT;              /*!< 0x010         Guardtime Register                                      */
  __IO uint32_t WT;              /*!< 0x014         Waiting Time Register                                   */
  __IO uint32_t IER;             /*!< 0x018         Interrupt Enable Register                               */
  __IO uint32_t IPR;             /*!< 0x01C         Interrupt Pending Register                              */
  __IO uint32_t TXB;             /*!< 0x020         Transmit Buffer Register                                */
  __IO uint32_t RXB;             /*!< 0x024         Receive Buffer Register                                 */
  __IO uint32_t PSC;             /*!< 0x028         Prescaler Register                                      */
} HT_SCI_TypeDef;


/**
 * @brief Basic Function Timer
 */
typedef struct
{
                                 /* BFTM0: 0x40076000                                                       */
                                 /* BFTM1: 0x40077000                                                       */
  __IO uint32_t CR;              /*!< 0x000          Control Register                                       */
  __IO uint32_t SR;              /*!< 0x004          Status Register                                        */
  __IO uint32_t CNTR;            /*!< 0x008          Counter Value Register                                 */
  __IO uint32_t CMP;             /*!< 0x00C          Compare Value Register                                 */
} HT_BFTM_TypeDef;


#if 0
/**
 * @brief Motor Control Timer
 */
typedef struct
{
                                 /* MCTM0: 0x4002C000                                                       */
                                 /* MCTM1: 0x4002D000                                                       */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[5];    /*!< 0x058 - 0x068  Reserved                                               */
  __IO uint32_t CHBRKCFR;        /*!< 0x06C          Channel Break Configuration Register                   */
  __IO uint32_t CHBRKCTR;        /*!< 0x070          Channel Break Control Register                         */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
  __IO uint32_t REPR;            /*!< 0x08C          Repetition Register                                    */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
} HT_MCTM_TypeDef;
#endif


/**
 * @brief Timer
 */
typedef struct
{
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[5];    /*!< 0x058 - 0x068  Reserved                                               */
  __IO uint32_t CHBRKCFR;        /*!< 0x06C          Channel Break Configuration Register                   */
  __IO uint32_t CHBRKCTR;        /*!< 0x070          Channel Break Control Register                         */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
  __IO uint32_t REPR;            /*!< 0x08C          Repetition Register                                    */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
} HT_TM_TypeDef;


/**
 * @brief Peripheral Direct Memory Access Channel
 */
typedef struct
{
  __IO uint32_t CR;              /*!< 0x000    PDMA Channel Control Register                                */
  __IO uint32_t SADR;            /*!< 0x004    PDMA Channel Source Address Register                         */
  __IO uint32_t DADR;            /*!< 0x008    PDMA Channel Destination Address Register                    */
#if defined(USE_HT32F1653_54) || defined(USE_HT32F1655_56)
  __IO uint32_t CADR;            /*!< 0x00C    PDMA Channel Current Address Register                        */
#else
       uint32_t RESERVED0[1];    /*!< 0x00C    Reserved                                                     */
#endif
  __IO uint32_t TSR;             /*!< 0x010    PDMA Channel Transfer Size Register                          */
  __IO uint32_t CTSR;            /*!< 0x014    PDMA Channel Current Transfer Size Register                  */
} HT_PDMACH_TypeDef;


/**
 * @brief Peripheral Direct Memory Access Global
 */
typedef struct
{
                                  /* PDMA: 0x40090000                                                       */
  HT_PDMACH_TypeDef PDMACH0;      /*!< 0x000          PDMA channel  0 registers                             */
  HT_PDMACH_TypeDef PDMACH1;      /*!< 0x018          PDMA channel  1 registers                             */
  HT_PDMACH_TypeDef PDMACH2;      /*!< 0x030          PDMA channel  2 registers                             */
  HT_PDMACH_TypeDef PDMACH3;      /*!< 0x048          PDMA channel  3 registers                             */
  HT_PDMACH_TypeDef PDMACH4;      /*!< 0x060          PDMA channel  4 registers                             */
  HT_PDMACH_TypeDef PDMACH5;      /*!< 0x078          PDMA channel  5 registers                             */
#if !defined(USE_HT32F12364)
  HT_PDMACH_TypeDef PDMACH6;      /*!< 0x090          PDMA channel  6 registers                             */
  HT_PDMACH_TypeDef PDMACH7;      /*!< 0x0A8          PDMA channel  7 registers                             */
#endif
#if defined(USE_HT32F1653_54) || defined(USE_HT32F1655_56)
       uint32_t     RESERVED0[24];/*!< 0x0C0 - 0x011C Reserved                                              */
#elif defined(USE_HT32F12365_66) || defined(USE_HT32F12345)
  HT_PDMACH_TypeDef PDMACH8;      /*!< 0x0C0          PDMA channel  8 registers                             */
  HT_PDMACH_TypeDef PDMACH9;      /*!< 0x0D8          PDMA channel  9 registers                             */
  HT_PDMACH_TypeDef PDMACH10;     /*!< 0x0F0          PDMA channel 10 registers                             */
  HT_PDMACH_TypeDef PDMACH11;     /*!< 0x108          PDMA channel 11 registers                             */
#elif defined(USE_HT32F12364)
       uint32_t     RESERVED0[36];/*!< 0x090 - 0x11C  Reserved                                              */
#endif
  __IO uint32_t     ISR0;         /*!< 0x120          PDMA Interrupt Status Register 0                      */
#if !defined(USE_HT32F12364)
  __IO uint32_t     ISR1;         /*!< 0x124          PDMA Interrupt Status Register 1                      */
#else
       uint32_t     RESERVED1[1]; /*!< 0x124          Reserved                                              */
#endif
  __IO uint32_t     ISCR0;        /*!< 0x128          PDMA Interrupt Status Clear Register 0                */
#if !defined(USE_HT32F12364)
  __IO uint32_t     ISCR1;        /*!< 0x12C          PDMA Interrupt Status Clear Register 1                */
#else
       uint32_t     RESERVED2[1]; /*!< 0x12C          Reserved                                              */
#endif
  __IO uint32_t     IER0;         /*!< 0x130          PDMA Interrupt Enable Register 0                      */
#if !defined(USE_HT32F12364)
  __IO uint32_t     IER1;         /*!< 0x134          PDMA Interrupt Enable Register 1                      */
#endif
} HT_PDMA_TypeDef;


/**
 * @brief Universal Serial Bus Global
 */
typedef struct
{
                                 /* USB: 0x400A8000                                                         */
  __IO uint32_t CSR;             /*!< 0x000 USB Control and Status Register                                 */
  __IO uint32_t IER;             /*!< 0x004 USB Interrupt Enable Register                                   */
  __IO uint32_t ISR;             /*!< 0x008 USB Interrupt Status Register                                   */
  __IO uint32_t FCR;             /*!< 0x00C USB Frame Count Register                                        */
  __IO uint32_t DEVAR;           /*!< 0x010 USB Device Address Register                                     */
  __IO uint32_t EP0CSR;          /*!< 0x014 USB Endpoint 0 Control and Status Register                      */
  __IO uint32_t EP0IER;          /*!< 0x018 USB Endpoint 0 Interrupt Enable Register                        */
  __IO uint32_t EP0ISR;          /*!< 0x01C USB Endpoint 0 Interrupt Status Register                        */
  __IO uint32_t EP0TCR;          /*!< 0x020 USB Endpoint 0 Transfer Count Register                          */
  __IO uint32_t EP0CFGR;         /*!< 0x024 USB Endpoint 0 Configuration Register                           */
  __IO uint32_t EP1CSR;          /*!< 0x028 USB Endpoint 1 Control and Status Register                      */
  __IO uint32_t EP1IER;          /*!< 0x02C USB Endpoint 1 Interrupt Enable Register                        */
  __IO uint32_t EP1ISR;          /*!< 0x030 USB Endpoint 1 Interrupt Status Register                        */
  __IO uint32_t EP1TCR;          /*!< 0x034 USB Endpoint 1 Transfer Count Register                          */
  __IO uint32_t EP1CFGR;         /*!< 0x038 USB Endpoint 1 Configuration Register                           */
  __IO uint32_t EP2CSR;          /*!< 0x03C USB Endpoint 2 Control and Status Register                      */
  __IO uint32_t EP2IER;          /*!< 0x040 USB Endpoint 2 Interrupt Enable Register                        */
  __IO uint32_t EP2ISR;          /*!< 0x044 USB Endpoint 2 Interrupt Status Register                        */
  __IO uint32_t EP2TCR;          /*!< 0x048 USB Endpoint 2 Transfer Count Register                          */
  __IO uint32_t EP2CFGR;         /*!< 0x04C USB Endpoint 2 Configuration Register                           */
  __IO uint32_t EP3CSR;          /*!< 0x050 USB Endpoint 3 Control and Status Register                      */
  __IO uint32_t EP3IER;          /*!< 0x054 USB Endpoint 3 Interrupt Enable Register                        */
  __IO uint32_t EP3ISR;          /*!< 0x058 USB Endpoint 3 Interrupt Status Register                        */
  __IO uint32_t EP3TCR;          /*!< 0x05C USB Endpoint 3 Transfer Count Register                          */
  __IO uint32_t EP3CFGR;         /*!< 0x060 USB Endpoint 3 Configuration Register                           */
  __IO uint32_t EP4CSR;          /*!< 0x064 USB Endpoint 4 Control and Status Register                      */
  __IO uint32_t EP4IER;          /*!< 0x068 USB Endpoint 4 Interrupt Enable Register                        */
  __IO uint32_t EP4ISR;          /*!< 0x06C USB Endpoint 4 Interrupt Status Register                        */
  __IO uint32_t EP4TCR;          /*!< 0x070 USB Endpoint 4 Transfer Count Register                          */
  __IO uint32_t EP4CFGR;         /*!< 0x074 USB Endpoint 4 Configuration Register                           */
  __IO uint32_t EP5CSR;          /*!< 0x078 USB Endpoint 5 Control and Status Register                      */
  __IO uint32_t EP5IER;          /*!< 0x07C USB Endpoint 5 Interrupt Enable Register                        */
  __IO uint32_t EP5ISR;          /*!< 0x080 USB Endpoint 5 Interrupt Status Register                        */
  __IO uint32_t EP5TCR;          /*!< 0x084 USB Endpoint 5 Transfer Count Register                          */
  __IO uint32_t EP5CFGR;         /*!< 0x088 USB Endpoint 5 Configuration Register                           */
  __IO uint32_t EP6CSR;          /*!< 0x08C USB Endpoint 6 Control and Status Register                      */
  __IO uint32_t EP6IER;          /*!< 0x090 USB Endpoint 6 Interrupt Enable Register                        */
  __IO uint32_t EP6ISR;          /*!< 0x094 USB Endpoint 6 Interrupt Status Register                        */
  __IO uint32_t EP6TCR;          /*!< 0x098 USB Endpoint 6 Transfer Count Register                          */
  __IO uint32_t EP6CFGR;         /*!< 0x09C USB Endpoint 6 Configuration Register                           */
  __IO uint32_t EP7CSR;          /*!< 0x0A0 USB Endpoint 7 Control and Status Register                      */
  __IO uint32_t EP7IER;          /*!< 0x0A4 USB Endpoint 7 Interrupt Enable Register                        */
  __IO uint32_t EP7ISR;          /*!< 0x0A8 USB Endpoint 7 Interrupt Status Register                        */
  __IO uint32_t EP7TCR;          /*!< 0x0AC USB Endpoint 7 Transfer Count Register                          */
  __IO uint32_t EP7CFGR;         /*!< 0x0B0 USB Endpoint 7 Configuration Register                           */
} HT_USB_TypeDef;


/**
 * @brief Universal Serial Bus Endpoint
 */
typedef struct
{
                                 /* USB Endpoint0: 0x400A8014                                               */
                                 /* USB Endpoint1: 0x400A8028                                               */
                                 /* USB Endpoint2: 0x400A803C                                               */
                                 /* USB Endpoint3: 0x400A8050                                               */
                                 /* USB Endpoint4: 0x400A8064                                               */
                                 /* USB Endpoint5: 0x400A8078                                               */
                                 /* USB Endpoint6: 0x400A808C                                               */
                                 /* USB Endpoint7: 0x400A80A0                                               */
  __IO uint32_t CSR;             /*!< 0x000 USB Endpoint n Control and Status Register                      */
  __IO uint32_t IER;             /*!< 0x004 USB Endpoint n Interrupt Enable Register                        */
  __IO uint32_t ISR;             /*!< 0x008 USB Endpoint n Interrupt Status Register                        */
  __IO uint32_t TCR;             /*!< 0x00C USB Endpoint n Transfer Count Register                          */
  __IO uint32_t CFGR;            /*!< 0x010 USB Endpoint n Configuration Register                           */
} HT_USBEP_TypeDef;


/**
 * @brief External Bus Interface
 */
typedef struct
{
                                 /* EBI: 0x40098000                                                         */
  __IO uint32_t CR;              /*!< 0x000    EBI Control Register                                         */
#if !defined(USE_HT32F12364)
  __IO uint32_t PCR;             /*!< 0x004    EBI Page Control Register                                    */
#else
       uint32_t RESERVED0[1];    /*!< 0x004    Reserved                                                     */
#endif
  __IO uint32_t SR;              /*!< 0x008    EBI Status Register                                          */
       uint32_t RESERVED1[1];    /*!< 0x00C    Reserved                                                     */
  __IO uint32_t ATR0;            /*!< 0x010    EBI Address Timing Register 0                                */
  __IO uint32_t RTR0;            /*!< 0x014    EBI Read Timing Register 0                                   */
  __IO uint32_t WTR0;            /*!< 0x018    EBI Write Timing Register 0                                  */
  __IO uint32_t PR0;             /*!< 0x01C    EBI Parity Register 0                                        */
#if !defined(USE_HT32F12364)
  __IO uint32_t ATR1;            /*!< 0x020    EBI Address Timing Register 1                                */
  __IO uint32_t RTR1;            /*!< 0x024    EBI Read Timing Register 1                                   */
  __IO uint32_t WTR1;            /*!< 0x028    EBI Write Timing Register 1                                  */
  __IO uint32_t PR1;             /*!< 0x02C    EBI Parity Register 1                                        */
  __IO uint32_t ATR2;            /*!< 0x030    EBI Address Timing Register 2                                */
  __IO uint32_t RTR2;            /*!< 0x034    EBI Read Timing Register 2                                   */
  __IO uint32_t WTR2;            /*!< 0x038    EBI Write Timing Register 2                                  */
  __IO uint32_t PR2;             /*!< 0x03C    EBI Parity Register 2                                        */
  __IO uint32_t ATR3;            /*!< 0x040    EBI Address Timing Register 3                                */
  __IO uint32_t RTR3;            /*!< 0x044    EBI Read Timing Register 3                                   */
  __IO uint32_t WTR3;            /*!< 0x048    EBI Write Timing Register 3                                  */
  __IO uint32_t PR3;             /*!< 0x04C    EBI Parity Register 3                                        */
  __IO uint32_t IEN;             /*!< 0x050    EBI Interrupt Enable Register                                */
  __IO uint32_t IF;              /*!< 0x054    EBI Interrupt Flag Register                                  */
  __IO uint32_t IFC;             /*!< 0x058    EBI Interrupt Clear Register                                 */
#endif
} HT_EBI_TypeDef;


/**
 * @brief Cyclic Redundancy Check
 */
typedef struct
{
                                 /* CRC: 0x4008A000                                                         */
  __IO uint32_t CR;              /*!< 0x000 CRC Control Register                                            */
  __IO uint32_t SDR;             /*!< 0x004 CRC Seed Register                                               */
  __IO uint32_t CSR;             /*!< 0x008 CRC Checksum Register                                           */
  __IO uint32_t DR;              /*!< 0x00C CRC Data Register                                               */
} HT_CRC_TypeDef;


/**
 * @brief Integrated Interchip Sound
 */
typedef struct
{
                                 /* I2S: 0x40026000                                                         */
  __IO uint32_t CR;              /*!< 0x000 I2S Control Register                                            */
  __IO uint32_t IER;             /*!< 0x004 I2S Interrupt Enable Register                                   */
  __IO uint32_t CDR;             /*!< 0x008 I2S Clock Divider Register                                      */
  __IO uint32_t TXDR;            /*!< 0x00C I2S TX Data Register                                            */
  __IO uint32_t RXDR;            /*!< 0x010 I2S RX Data Register                                            */
  __IO uint32_t FCR;             /*!< 0x014 I2S FIFO Control Register                                       */
  __IO uint32_t SR;              /*!< 0x018 I2S Status Register                                             */
  __IO uint32_t RCNTR;           /*!< 0x01C I2S Rate Counter Register                                       */
} HT_I2S_TypeDef;


/**
 * @brief Secure digital input/output
 */
typedef struct
{
                                 /* SDIO: 0x400A0000                                                        */
  __IO uint32_t BLKSIZE;         /*!< 0x000         Block Size Register                                     */
  __IO uint32_t BLKCNT;          /*!< 0x004         Block Count Register                                    */
  __IO uint32_t ARG;             /*!< 0x008         Argument Register                                       */
  __IO uint32_t TMR;             /*!< 0x00C         Transfer Mode Register                                  */
  __IO uint32_t CMD;             /*!< 0x010         Command Register Register                               */
  __IO uint32_t RESP0;           /*!< 0x014         Response Register 0                                     */
  __IO uint32_t RESP1;           /*!< 0x018         Response Register 1                                     */
  __IO uint32_t RESP2;           /*!< 0x01C         Response Register 2                                     */
  __IO uint32_t RESP3;           /*!< 0x020         Response Register 3                                     */
  __IO uint32_t DR;              /*!< 0x024         Data Register                                           */
  __IO uint32_t PSR;             /*!< 0x028         Present Status Register                                 */
  __IO uint32_t CR;              /*!< 0x02C         Control Register                                        */
       uint32_t RESERVED0[2];    /*!< 0x030 - 0x034 Reserved                                                */
  __IO uint32_t CLKCR;           /*!< 0x038         Clock Control Register                                  */
  __IO uint32_t TMOCR;           /*!< 0x03C         Timeout Control Register                                */
  __IO uint32_t SWRST;           /*!< 0x040         Software Reset Register                                 */
  __IO uint32_t SR;              /*!< 0x044         Status Register                                         */
  __IO uint32_t SER;             /*!< 0x048         Status Enable Register                                  */
  __IO uint32_t IER;             /*!< 0x04C         Interrupt Enable Register                               */
} HT_SDIO_TypeDef;


/**
 * @brief CMOS Sensor Interface
 */
typedef struct
{
                                 /* CSIF: 0x400CC000                                                        */
  __IO uint32_t ENR;             /*!< 0x000    Enable Register                                              */
  __IO uint32_t CR;              /*!< 0x004    Control Register                                             */
  __IO uint32_t IMGWH;           /*!< 0x008    Image Width/Height Register                                  */
  __IO uint32_t WCR0;            /*!< 0x00C    Window Capture 0 Register                                    */
  __IO uint32_t WCR1;            /*!< 0x010    Window Capture 1 Register                                    */
  __IO uint32_t SMP;             /*!< 0x014    Row & Column Sub-Sample Register                             */
  __IO uint32_t SMPCOL;          /*!< 0x018    Column Sub-Sample Register                                   */
  __IO uint32_t SMPROW;          /*!< 0x01C    Row Sub-Sample Register                                      */
  __IO uint32_t FIFO0;           /*!< 0x020    FIFO Register 0                                              */
  __IO uint32_t FIFO1;           /*!< 0x024    FIFO Register 1                                              */
  __IO uint32_t FIFO2;           /*!< 0x028    FIFO Register 2                                              */
  __IO uint32_t FIFO3;           /*!< 0x02C    FIFO Register 3                                              */
  __IO uint32_t FIFO4;           /*!< 0x030    FIFO Register 4                                              */
  __IO uint32_t FIFO5;           /*!< 0x034    FIFO Register 5                                              */
  __IO uint32_t FIFO6;           /*!< 0x038    FIFO Register 6                                              */
  __IO uint32_t FIFO7;           /*!< 0x03C    FIFO Register 7                                              */
  __IO uint32_t IER;             /*!< 0x040    Interrupt Enable Register                                    */
  __IO uint32_t SR;              /*!< 0x044    Status Register                                              */
} HT_CSIF_TypeDef;


/**
 * @brief Advanced Encryption Standard
 */
typedef struct
{
                                 /* AES: 0x400C8000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t SR;              /*!< 0x004         Status Register                                         */
  __IO uint32_t PDMAR;           /*!< 0x008         PDMA Register                                           */
  __IO uint32_t ISR;             /*!< 0x00C         Interrupt Status Register                               */
  __IO uint32_t IER;             /*!< 0x010         Interrupt Enable Register                               */
  __IO uint32_t DINR;            /*!< 0x014         Data Input Register                                     */
  __IO uint32_t DOUTR;           /*!< 0x018         Data Output Register                                    */
  __IO uint32_t KEYR[8];         /*!< 0x01C - 0x038 Key Register 0~7                                        */
  __IO uint32_t IVR[4];          /*!< 0x03C - 0x048 Initial Vector Register 0~3                             */
} HT_AES_TypeDef;


/**
  * @}
  */


/** @addtogroup Peripheral_Memory_Map
  * @{
  */

#define HT_SRAM_BASE             (0x20000000UL)
#define HT_SRAM_BB_BASE          (0x22000000UL)

#define HT_PERIPH_BASE           (0x40000000UL)
#define HT_PERIPH_BB_BASE        (0x42000000UL)

#define HT_APB0PERIPH_BASE       (HT_PERIPH_BASE)                 /* 0x40000000                             */
#define HT_APB1PERIPH_BASE       (HT_PERIPH_BASE + 0x40000)       /* 0x40040000                             */
#define HT_AHBPERIPH_BASE        (HT_PERIPH_BASE + 0x80000)       /* 0x40080000                             */

/* APB0                                                                                                     */
#define HT_USART0_BASE           (HT_APB0PERIPH_BASE + 0x0000)    /* 0x40000000                             */
#define HT_UART0_BASE            (HT_APB0PERIPH_BASE + 0x1000)    /* 0x40001000                             */
#define HT_SPI0_BASE             (HT_APB0PERIPH_BASE + 0x4000)    /* 0x40004000                             */
#define HT_ADC0_BASE             (HT_APB0PERIPH_BASE + 0x10000)   /* 0x40010000                             */
#define HT_CMP_OP0_BASE          (HT_APB0PERIPH_BASE + 0x18000)   /* 0x40018000                             */
#define HT_CMP_OP1_BASE          (HT_APB0PERIPH_BASE + 0x18100)   /* 0x40018100                             */
#define HT_AFIO_BASE             (HT_APB0PERIPH_BASE + 0x22000)   /* 0x40022000                             */
#define HT_EXTI_BASE             (HT_APB0PERIPH_BASE + 0x24000)   /* 0x40024000                             */
#define HT_I2S_BASE              (HT_APB0PERIPH_BASE + 0x26000)   /* 0x40026000                             */
#define HT_MCTM0_BASE            (HT_APB0PERIPH_BASE + 0x2C000)   /* 0x4002C000                             */
#define HT_MCTM1_BASE            (HT_APB0PERIPH_BASE + 0x2D000)   /* 0x4002D000                             */
#define HT_PWM0_BASE             (HT_APB0PERIPH_BASE + 0x31000)   /* 0x40031000                             */
#define HT_SCTM0_BASE            (HT_APB0PERIPH_BASE + 0x34000)   /* 0x40034000                             */
#define HT_SCI1_BASE             (HT_APB0PERIPH_BASE + 0x3A000)   /* 0x4003A000                             */

/* APB1                                                                                                     */
#define HT_USART1_BASE           (HT_APB1PERIPH_BASE + 0x0000)    /* 0x40040000                             */
#define HT_UART1_BASE            (HT_APB1PERIPH_BASE + 0x1000)    /* 0x40041000                             */
#define HT_SCI0_BASE             (HT_APB1PERIPH_BASE + 0x3000)    /* 0x40043000                             */
#define HT_SPI1_BASE             (HT_APB1PERIPH_BASE + 0x4000)    /* 0x40044000                             */
#define HT_I2C0_BASE             (HT_APB1PERIPH_BASE + 0x8000)    /* 0x40048000                             */
#define HT_I2C1_BASE             (HT_APB1PERIPH_BASE + 0x9000)    /* 0x40049000                             */
#define HT_CMP0_BASE             (HT_APB1PERIPH_BASE + 0x18000)   /* 0x40058000                             */
#define HT_CMP1_BASE             (HT_APB1PERIPH_BASE + 0x18100)   /* 0x40058100                             */
#define HT_WDT_BASE              (HT_APB1PERIPH_BASE + 0x28000)   /* 0x40068000                             */
#define HT_RTC_BASE              (HT_APB1PERIPH_BASE + 0x2A000)   /* 0x4006A000                             */
#define HT_PWRCU_BASE            (HT_APB1PERIPH_BASE + 0x2A100)   /* 0x4006A100                             */
#define HT_GPTM0_BASE            (HT_APB1PERIPH_BASE + 0x2E000)   /* 0x4006E000                             */
#define HT_GPTM1_BASE            (HT_APB1PERIPH_BASE + 0x2F000)   /* 0x4006F000                             */
#define HT_SCTM1_BASE            (HT_APB1PERIPH_BASE + 0x34000)   /* 0x40074000                             */
#define HT_BFTM0_BASE            (HT_APB1PERIPH_BASE + 0x36000)   /* 0x40076000                             */
#define HT_BFTM1_BASE            (HT_APB1PERIPH_BASE + 0x37000)   /* 0x40077000                             */

/* AHB                                                                                                      */
#define HT_FLASH_BASE            (HT_AHBPERIPH_BASE + 0x0000)     /* 0x40080000                             */
#define HT_CKCU_BASE             (HT_AHBPERIPH_BASE + 0x8000)     /* 0x40088000                             */
#define HT_RSTCU_BASE            (HT_AHBPERIPH_BASE + 0x8100)     /* 0x40088100                             */
#define HT_CRC_BASE              (HT_AHBPERIPH_BASE + 0xA000)     /* 0x4008A000                             */
#define HT_PDMA_BASE             (HT_AHBPERIPH_BASE + 0x10000)    /* 0x40090000                             */
#define HT_EBI_BASE              (HT_AHBPERIPH_BASE + 0x18000)    /* 0x40098000                             */
#define HT_SDIO_BASE             (HT_AHBPERIPH_BASE + 0x20000)    /* 0x400A0000                             */
#define HT_USB_BASE              (HT_AHBPERIPH_BASE + 0x28000)    /* 0x400A8000                             */
#define HT_USB_EP0_BASE          (HT_USB_BASE       + 0x0014)     /* 0x400A8014                             */
#define HT_USB_EP1_BASE          (HT_USB_BASE       + 0x0028)     /* 0x400A8028                             */
#define HT_USB_EP2_BASE          (HT_USB_BASE       + 0x003C)     /* 0x400A803C                             */
#define HT_USB_EP3_BASE          (HT_USB_BASE       + 0x0050)     /* 0x400A8050                             */
#define HT_USB_EP4_BASE          (HT_USB_BASE       + 0x0064)     /* 0x400A8064                             */
#define HT_USB_EP5_BASE          (HT_USB_BASE       + 0x0078)     /* 0x400A8078                             */
#define HT_USB_EP6_BASE          (HT_USB_BASE       + 0x008C)     /* 0x400A808C                             */
#define HT_USB_EP7_BASE          (HT_USB_BASE       + 0x00A0)     /* 0x400A80A0                             */
#define HT_USB_SRAM_BASE         (HT_AHBPERIPH_BASE + 0x2A000)    /* 0x400AA000                             */
#define HT_GPIOA_BASE            (HT_AHBPERIPH_BASE + 0x30000)    /* 0x400B0000                             */
#define HT_GPIOB_BASE            (HT_AHBPERIPH_BASE + 0x32000)    /* 0x400B2000                             */
#define HT_GPIOC_BASE            (HT_AHBPERIPH_BASE + 0x34000)    /* 0x400B4000                             */
#define HT_GPIOD_BASE            (HT_AHBPERIPH_BASE + 0x36000)    /* 0x400B6000                             */
#define HT_GPIOE_BASE            (HT_AHBPERIPH_BASE + 0x38000)    /* 0x400B8000                             */
#define HT_GPIOF_BASE            (HT_AHBPERIPH_BASE + 0x3A000)    /* 0x400BA000                             */
#define HT_AES_BASE              (HT_AHBPERIPH_BASE + 0x48000)    /* 0x400C8000                             */
#define HT_CSIF_BASE             (HT_AHBPERIPH_BASE + 0x4C000)    /* 0x400CC000                             */

/**
  * @}
  */

/* Peripheral declaration                                                                                   */
#define HT_ADC0                  ((HT_ADC_TypeDef *) HT_ADC0_BASE)
#define HT_AFIO                  ((HT_AFIO_TypeDef *) HT_AFIO_BASE)
#define HT_BFTM0                 ((HT_BFTM_TypeDef *) HT_BFTM0_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_CKCU                  ((HT_CKCU_TypeDef *) HT_CKCU_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_EXTI                  ((HT_EXTI_TypeDef *) HT_EXTI_BASE)
#define HT_FLASH                 ((HT_FLASH_TypeDef *) HT_FLASH_BASE)
#define HT_GPIOA                 ((HT_GPIO_TypeDef *) HT_GPIOA_BASE)
#define HT_GPIOB                 ((HT_GPIO_TypeDef *) HT_GPIOB_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_GPTM0                 ((HT_TM_TypeDef *) HT_GPTM0_BASE)
#define HT_I2C0                  ((HT_I2C_TypeDef *) HT_I2C0_BASE)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_PWRCU                 ((HT_PWRCU_TypeDef *) HT_PWRCU_BASE)
#define HT_RSTCU                 ((HT_RSTCU_TypeDef *) HT_RSTCU_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_SPI0                  ((HT_SPI_TypeDef *) HT_SPI0_BASE)
#define HT_UART0                 ((HT_USART_TypeDef *) HT_UART0_BASE)
#define HT_USART0                ((HT_USART_TypeDef *) HT_USART0_BASE)
#define HT_USB                   ((HT_USB_TypeDef *) HT_USB_BASE)
#define HT_USBEP0                ((HT_USBEP_TypeDef *) HT_USB_EP0_BASE)
#define HT_USBEP1                ((HT_USBEP_TypeDef *) HT_USB_EP1_BASE)
#define HT_USBEP2                ((HT_USBEP_TypeDef *) HT_USB_EP2_BASE)
#define HT_USBEP3                ((HT_USBEP_TypeDef *) HT_USB_EP3_BASE)
#define HT_USBEP4                ((HT_USBEP_TypeDef *) HT_USB_EP4_BASE)
#define HT_USBEP5                ((HT_USBEP_TypeDef *) HT_USB_EP5_BASE)
#define HT_USBEP6                ((HT_USBEP_TypeDef *) HT_USB_EP6_BASE)
#define HT_USBEP7                ((HT_USBEP_TypeDef *) HT_USB_EP7_BASE)
#define HT_WDT                   ((HT_WDT_TypeDef *) HT_WDT_BASE)


#if defined(USE_HT32F1655_56)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CMP_OP0               ((HT_CMP_OP_TypeDef *) HT_CMP_OP0_BASE)
#define HT_CMP_OP1               ((HT_CMP_OP_TypeDef *) HT_CMP_OP1_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_MCTM1                 ((HT_TM_TypeDef *) HT_MCTM1_BASE)
#define HT_GPTM1                 ((HT_TM_TypeDef *) HT_GPTM1_BASE)
#define HT_SCI0                  ((HT_SCI_TypeDef *) HT_SCI0_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_GPIOE                 ((HT_GPIO_TypeDef *) HT_GPIOE_BASE)
#endif

#if defined(USE_HT32F1653_54)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_MCTM1                 ((HT_TM_TypeDef *) HT_MCTM1_BASE)
#define HT_GPTM1                 ((HT_TM_TypeDef *) HT_GPTM1_BASE)
#define HT_SCI0                  ((HT_SCI_TypeDef *) HT_SCI0_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#endif

#if defined(USE_HT32F12365_66)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_MCTM1                 ((HT_TM_TypeDef *) HT_MCTM1_BASE)
#define HT_GPTM1                 ((HT_TM_TypeDef *) HT_GPTM1_BASE)
#define HT_SCI0                  ((HT_SCI_TypeDef *) HT_SCI0_BASE)
#define HT_SCI1                  ((HT_SCI_TypeDef *) HT_SCI1_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_GPIOE                 ((HT_GPIO_TypeDef *) HT_GPIOE_BASE)
#define HT_SDIO                  ((HT_SDIO_TypeDef *) HT_SDIO_BASE)
#define HT_AES                   ((HT_AES_TypeDef *) HT_AES_BASE)
#define HT_CSIF                  ((HT_CSIF_TypeDef *) HT_CSIF_BASE)
#endif

#if defined(USE_HT32F12345)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_MCTM1                 ((HT_TM_TypeDef *) HT_MCTM1_BASE)
#define HT_GPTM1                 ((HT_TM_TypeDef *) HT_GPTM1_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_SDIO                  ((HT_SDIO_TypeDef *) HT_SDIO_BASE)
#endif

#if defined(USE_HT32F12364)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_SCI0                  ((HT_SCI_TypeDef *) HT_SCI0_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_GPIOF                 ((HT_GPIO_TypeDef *) HT_GPIOF_BASE)
#define HT_AES                   ((HT_AES_TypeDef *) HT_AES_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_SCTM0                 ((HT_TM_TypeDef *) HT_SCTM0_BASE)
#define HT_SCTM1                 ((HT_TM_TypeDef *) HT_SCTM1_BASE)
#endif

#if defined USE_HT32_DRIVER
  #include "ht32f1xxxx_lib.h"
#endif

/**
 * @brief Adjust the value of High Speed External oscillator (HSE)
          Tip: To avoid from modifying every time for different HSE, please define
          the "HSE_VALUE=n000000" ("n" represents n MHz) in your own toolchain compiler preprocessor,
          or edit the "HSE_VALUE" in the "ht32f1xxxx_conf.h" file.
  */
#if !defined  HSE_VALUE
  /* Available HSE_VALUE: 4 MHz ~ 16 MHz                                                                    */
  #define HSE_VALUE       8000000UL   /*!< Value of the External oscillator in Hz                           */
#endif

/**
 * @brief Define for backward compatibility
 */
#define HT_ADC                   HT_ADC0
#define ADC                      ADC0
#define ADC_IRQn                 ADC0_IRQn


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT Holtek Semiconductor Inc. *****END OF FILE***                            */
