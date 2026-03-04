/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l40x.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32L40X_H__
#define __N32L40X_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup n32l40x_Library_Basic
 * @{
 */

#if !defined USE_STDPERIPH_DRIVER
/*
 * Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
#define USE_STDPERIPH_DRIVER
#endif

/*
 * In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application

   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined HSE_VALUE
#define HSE_VALUE (8000000) /*!< Value of the External oscillator in Hz */
#endif                      /* HSE_VALUE */

/*
 * In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value
   */
#define HSE_STARTUP_TIMEOUT ((uint16_t)0x2000) /*!< Time out for HSE start up */
#define HSI_STARTUP_TIMEOUT ((uint16_t)0x0500) /*!< Time out for HSI start up */
#define MSI_STARTUP_TIMEOUT ((uint16_t)0x0500) /*!< Time out for MSI start up */

#define MSI_VALUE_L0 (100000)  /*!< L0 Value of the Multi oscillator in Hz*/
#define MSI_VALUE_L1 (200000)  /*!< L1 Value of the Multi oscillator in Hz*/
#define MSI_VALUE_L2 (400000)  /*!< L2 Value of the Multi oscillator in Hz*/
#define MSI_VALUE_L3 (800000)  /*!< L3 Value of the Multi oscillator in Hz*/
#define MSI_VALUE_L4 (1000000) /*!< L4 Value of the Multi oscillator in Hz*/
#define MSI_VALUE_L5 (2000000) /*!< L5 Value of the Multi oscillator in Hz*/
#define MSI_VALUE_L6 (4000000) /*!< L6 Value of the Multi oscillator in Hz*/

#define HSI_VALUE (16000000) /*!< Value of the Internal oscillator in Hz*/

#define __N32L40X_STDPERIPH_VERSION_MAIN (0x00) /*!< [31:24] main version */
#define __N32L40X_STDPERIPH_VERSION_SUB1 (0x04) /*!< [23:16] sub1 version */
#define __N32L40X_STDPERIPH_VERSION_SUB2 (0x00) /*!< [15:8]  sub2 version */
#define __N32L40X_STDPERIPH_VERSION_RC   (0x00) /*!< [7:0]  release candidate */

/**
 * @brief n32l40x Standard Peripheral Library version number
 */
#define __N32L40X_STDPERIPH_VERSION                                                                                    \
    ((__N32L40X_STDPERIPH_VERSION_MAIN << 24) | (__N32L40X_STDPERIPH_VERSION_SUB1 << 16)                               \
     | (__N32L40X_STDPERIPH_VERSION_SUB2 << 8) | (__N32L40X_STDPERIPH_VERSION_RC))

/*
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 */
#ifdef N32L40X
#define __MPU_PRESENT 1          /*!< n32l40x devices does not provide an MPU */
#define __FPU_PRESENT 1          /*!< FPU present                            */
#endif                           /* n32l40x */
#define __NVIC_PRIO_BITS       4 /*!< n32l40x uses 4 Bits for the Priority Levels    */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used */

/**
 * @brief n32l40x Interrupt Number Definition
 */
typedef enum IRQn
{
    /******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn   = -14, /*!< 2 Non Maskable Interrupt                            */
    HardFault_IRQn        = -13, /*!< 3 Hard Fault Interrupt                              */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M4 Memory Management Interrupt             */
    BusFault_IRQn         = -11, /*!< 5 Cortex-M4 Bus Fault Interrupt                     */
    UsageFault_IRQn       = -10, /*!< 6 Cortex-M4 Usage Fault Interrupt                   */
    SVCall_IRQn           = -5,  /*!< 11 Cortex-M4 SV Call Interrupt                      */
    DebugMonitor_IRQn     = -4,  /*!< 12 Cortex-M4 Debug Monitor Interrupt                */
    PendSV_IRQn           = -2,  /*!< 14 Cortex-M4 Pend SV Interrupt                      */
    SysTick_IRQn          = -1,  /*!< 15 Cortex-M4 System Tick Interrupt                  */

    /******  n32l40x specific Interrupt Numbers ********************************************************/
    WWDG_IRQn             = 0,  /*!< Window WatchDog Interrupt                            */
    PVD_IRQn              = 1,  /*!< PVD through EXTI Line detection Interrupt            */
    TAMPER_IRQn           = 2,  /*!< RTC Tamper interrupt or Timestamp through EXTI line 19 */
    RTC_IRQn              = 3,  /*!< RTC wakeup timer through EXTI line 20                */
    FLASH_IRQn            = 4,  /*!< FLASH global Interrupt                               */
    RCC_IRQn              = 5,  /*!< RCC global Interrupt                                 */
    EXTI0_IRQn            = 6,  /*!< EXTI Line0 Interrupt                                 */
    EXTI1_IRQn            = 7,  /*!< EXTI Line1 Interrupt                                 */
    EXTI2_IRQn            = 8,  /*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn            = 9,  /*!< EXTI Line3 Interrupt                                 */
    EXTI4_IRQn            = 10, /*!< EXTI Line4 Interrupt                                 */
    DMA_Channel1_IRQn     = 11, /*!< DMA Channel 1 global Interrupt                       */
    DMA_Channel2_IRQn     = 12, /*!< DMA Channel 2 global Interrupt                       */
    DMA_Channel3_IRQn     = 13, /*!< DMA Channel 3 global Interrupt                       */
    DMA_Channel4_IRQn     = 14, /*!< DMA Channel 4 global Interrupt                       */
    DMA_Channel5_IRQn     = 15, /*!< DMA Channel 5 global Interrupt                       */
    DMA_Channel6_IRQn     = 16, /*!< DMA Channel 6 global Interrupt                       */
    DMA_Channel7_IRQn     = 17, /*!< DMA Channel 7 global Interrupt                       */
    DMA_Channel8_IRQn     = 18, /*!< DMA Channel 8 global Interrupt                       */
    ADC_IRQn              = 19, /*!< ADC global Interrupt                                 */
    USB_HP_IRQn           = 20, /*!< USB Device High Priority Interrupts                  */
    USB_LP_IRQn           = 21, /*!< USB Device Low Priority Interrupts                   */
    COMP_1_2_IRQn         = 22, /*!< COMP1 & COMP2 global Interrupt through EXTI line 21/22 */
    EXTI9_5_IRQn          = 23, /*!< External Line[9:5] Interrupts                        */
    TIM1_BRK_IRQn         = 24, /*!< TIM1 Break Interrupt                                 */
    TIM1_UP_IRQn          = 25, /*!< TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQn     = 26, /*!< TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQn          = 27, /*!< TIM1 Capture Compare Interrupt                       */
    TIM2_IRQn             = 28, /*!< TIM2 global Interrupt                                */
    TIM3_IRQn             = 29, /*!< TIM3 global Interrupt                                */
    TIM4_IRQn             = 30, /*!< TIM4 global Interrupt                                */
    I2C1_EV_IRQn          = 31, /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn          = 32, /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn          = 33, /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn          = 34, /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn             = 35, /*!< SPI1 global Interrupt                                */
    SPI2_IRQn             = 36, /*!< SPI2 global Interrupt                                */
    USART1_IRQn           = 37, /*!< USART1 global Interrupt                              */
    USART2_IRQn           = 38, /*!< USART2 global Interrupt                              */
    USART3_IRQn           = 39, /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn        = 40, /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn         = 41, /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn        = 42, /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TIM8_BRK_IRQn         = 43, /*!< TIM8 Break Interrupt                                 */
    TIM8_UP_IRQn          = 44, /*!< TIM8 Update Interrupt                                */
    TIM8_TRG_COM_IRQn     = 45, /*!< TIM8 Trigger and Commutation Interrupt               */
    TIM8_CC_IRQn          = 46, /*!< TIM8 Capture Compare Interrupt                       */
    UART4_IRQn            = 47, /*!< UART4 global Interrupt                               */
    UART5_IRQn            = 48, /*!< UART5 global Interrupt                               */
    LPUART_IRQn           = 49, /*!< LPUART global Interrupt                              */
    TIM5_IRQn             = 50, /*!< TIM5 global Interrupt                                */
    TIM6_IRQn             = 51, /*!< TIM6 global Interrupt                                */
    TIM7_IRQn             = 52, /*!< TIM7 global Interrupt                                */
    CAN_TX_IRQn           = 53, /*!< CAN TX Interrupt                                     */
    CAN_RX0_IRQn          = 54, /*!< CAN RX0 Interrupt                                    */
    CAN_RX1_IRQn          = 55, /*!< CAN RX1 Interrupt                                    */
    CAN_SCE_IRQn          = 56, /*!< CAN SCE Interrupt                                    */
    LPUART_WKUP_IRQn      = 57, /*!< LPUART wakeup interrupt through EXTI line 23         */
    LPTIM_WKUP_IRQn       = 58, /*!< LPTIMER wakeup interrupt through EXTI line 24        */
    LCD_IRQn              = 59, /*!< LCD global interrupt through EXTI line 26            */
    SAC_IRQn              = 60, /*!< SAC global Interrupt                                 */
    MMU_IRQn              = 61, /*!< MMU global Interrupt                                 */
    TSC_IRQn              = 62, /*!< TSC global Interrupt                                 */
    RAMC_PERR_IRQn        = 63, /*!< RAM parity error interrupt                           */
    TIM9_IRQn             = 64, /*!< TIM9 global interrupt                                */
    UCDR_IRQn             = 65, /*!< UCDR error interrupt                                 */

} IRQn_Type;

#include "core_cm4.h"
#include "system_n32l40x.h"
#include <stdint.h>
#include <stdbool.h>

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef const int32_t sc32; /*!< Read Only */
typedef const int16_t sc16; /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t vs8;

typedef __I int32_t vsc32; /*!< Read Only */
typedef __I int16_t vsc16; /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef const uint32_t uc32; /*!< Read Only */
typedef const uint16_t uc16; /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t vu8;

typedef __I uint32_t vuc32; /*!< Read Only */
typedef __I uint16_t vuc16; /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */
typedef enum
{
    RESET = 0,
    SET   = !RESET
} FlagStatus,
    INTStatus;

typedef enum
{
    DISABLE = 0,
    ENABLE  = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
    ERROR   = 0,
    SUCCESS = !ERROR
} ErrorStatus;

/* n32l40x Standard Peripheral Library old definitions (maintained for legacy purpose) */
#define HSEStartUp_TimeOut HSE_STARTUP_TIMEOUT
#define HSE_Value          HSE_VALUE
#define HSI_Value          HSI_VALUE

/**
 * @brief Analog to Digital Converter
 */
typedef struct
{
    __IO uint32_t STS;
    __IO uint32_t CTRL1;
    __IO uint32_t CTRL2;
    __IO uint32_t SAMPT1;
    __IO uint32_t SAMPT2;
    __IO uint32_t JOFFSET1;
    __IO uint32_t JOFFSET2;
    __IO uint32_t JOFFSET3;
    __IO uint32_t JOFFSET4;
    __IO uint32_t WDGHIGH;
    __IO uint32_t WDGLOW;
    __IO uint32_t RSEQ1;
    __IO uint32_t RSEQ2;
    __IO uint32_t RSEQ3;
    __IO uint32_t JSEQ;
    __IO uint32_t JDAT1;
    __IO uint32_t JDAT2;
    __IO uint32_t JDAT3;
    __IO uint32_t JDAT4;
    __IO uint32_t DAT;
    __IO uint32_t DIFSEL;
    __IO uint32_t CALFACT;
    __IO uint32_t CTRL3;
    __IO uint32_t SAMPT3;
} ADC_Module;

/**
 * @brief OPAMP
 */
typedef struct
{
    __IO uint32_t CS1;
    __IO uint32_t RES1[3];
    __IO uint32_t CS2;
    __IO uint32_t RES2[3];
    __IO uint32_t LOCK;
} OPAMP_Module;

/**
 * @brief COMP_Single
 */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t FILC;
    __IO uint32_t FILP;
} COMP_SingleType;

/**
 * @brief COMP
 */
typedef struct
{
    __IO uint32_t INTEN;
    __IO uint32_t LPCKSEL;
    __IO uint32_t WINMODE;
    __IO uint32_t LOCK;
    COMP_SingleType Cmp1;
    __IO uint32_t RES;
    COMP_SingleType Cmp2;
    __IO uint32_t CMP2OSEL;
    __IO uint32_t VREFSCL;
    __IO uint32_t TEST;
    __IO uint32_t INTSTS;
} COMP_Module;

/**
 * @brief AFEC
 */

typedef struct
{
    __IO uint32_t TRIMR0;
    __IO uint32_t TRIMR1;
    __IO uint32_t TRIMR2;
    __IO uint32_t TRIMR3;
    __IO uint32_t TRIMR4;
    __IO uint32_t TRIMR5;
    __IO uint32_t TRIMR6;
      __IO uint32_t TRIMR7;
    __IO uint32_t TRIMR8;
   //uint32_t RESERVED0;
    __IO uint32_t TESTR0;
    __IO uint32_t TESTR1;
} AFEC_Module;

/**
 * @brief Controller Area Network TxMailBox
 */

typedef struct
{
    __IO uint32_t TMI;
    __IO uint32_t TMDT;
    __IO uint32_t TMDL;
    __IO uint32_t TMDH;
} CAN_TxMailBox_Param;

/**
 * @brief Controller Area Network FIFOMailBox
 */

typedef struct
{
    __IO uint32_t RMI;
    __IO uint32_t RMDT;
    __IO uint32_t RMDL;
    __IO uint32_t RMDH;
} CAN_FIFOMailBox_Param;

/**
 * @brief Controller Area Network FilterRegister
 */

typedef struct
{
    __IO uint32_t FR1;
    __IO uint32_t FR2;
} CAN_FilterRegister_Param;

/**
 * @brief Controller Area Network
 */

typedef struct
{
    __IO uint32_t MCTRL;
    __IO uint32_t MSTS;
    __IO uint32_t TSTS;
    __IO uint32_t RFF0;
    __IO uint32_t RFF1;
    __IO uint32_t INTE;
    __IO uint32_t ESTS;
    __IO uint32_t BTIM;
    uint32_t RESERVED0[88];
    CAN_TxMailBox_Param sTxMailBox[3];
    CAN_FIFOMailBox_Param sFIFOMailBox[2];
    uint32_t RESERVED1[12];
    __IO uint32_t FMC;
    __IO uint32_t FM1;
    uint32_t RESERVED2;
    __IO uint32_t FS1;
    uint32_t RESERVED3;
    __IO uint32_t FFA1;
    uint32_t RESERVED4;
    __IO uint32_t FA1;
    uint32_t RESERVED5[8];
    CAN_FilterRegister_Param sFilterRegister[14];
} CAN_Module;

/**
 * @brief CRC calculation unit
 */

typedef struct
{
    __IO uint32_t CRC32DAT; /*!< CRC data register */
    __IO uint8_t CRC32IDAT; /*!< CRC independent data register*/
    uint8_t RESERVED0;
    uint16_t RESERVED1;
    __IO uint32_t CRC32CTRL; /*!< CRC control register */
    __IO uint32_t CRC16CTRL;
    __IO uint8_t CRC16DAT;
    uint8_t RESERVED2;
    uint16_t RESERVED3;
    __IO uint16_t CRC16D;
    uint16_t RESERVED4;
    __IO uint8_t LRC;
    uint8_t RESERVED5;
    uint16_t RESERVED6;
} CRC_Module;

/**
 * @brief Digital to Analog Converter
 */

typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t SOTTR;
    __IO uint32_t DR12CH;
    __IO uint32_t DL12CH;
    __IO uint32_t DR8CH;
    __IO uint32_t DATO;

} DAC_Module;
/**
 * @brief USB
 */

typedef struct
{
    __IO uint32_t EP0;
    __IO uint32_t EP1;
    __IO uint32_t EP2;
    __IO uint32_t EP3;
    __IO uint32_t EP4;
    __IO uint32_t EP5;
    __IO uint32_t EP6;
    __IO uint32_t EP7;
    __IO uint32_t Reserve20h;
    __IO uint32_t Reserve24h;
    __IO uint32_t Reserve28h;
    __IO uint32_t Reserve2Ch;
    __IO uint32_t Reserve30h;
    __IO uint32_t Reserve34h;
    __IO uint32_t Reserve38h;
    __IO uint32_t Reserve3Ch;
    __IO uint32_t CTRL;
    __IO uint32_t STS;
    __IO uint32_t FN;
    __IO uint32_t ADDR;
    __IO uint32_t BUFTAB;
} USB_Module;

/**
 * @brief Debug MCU
 */

typedef struct
{
    __IO uint32_t ID;
    __IO uint32_t CTRL;
} DBG_Module;

/**
 * @brief DMA Controller
 */

typedef struct
{
    __IO uint32_t CHCFG;
    __IO uint32_t TXNUM;
    __IO uint32_t PADDR;
    __IO uint32_t MADDR;
    __IO uint32_t CHSEL;

} DMA_ChannelType;

typedef struct
{
    __IO uint32_t INTSTS;
    __IO uint32_t INTCLR;
    __IO DMA_ChannelType DMA_Channel[8];
} DMA_Module;

/**
 * @brief External Interrupt/Event Controller
 */

typedef struct
{
    __IO uint32_t IMASK;    /*offset 0x00*/
    __IO uint32_t EMASK;    /*offset 0x04*/
    __IO uint32_t RT_CFG;   /*offset 0x08*/
    __IO uint32_t FT_CFG;   /*offset 0x0C*/
    __IO uint32_t SWIE;     /*offset 0x10*/
    __IO uint32_t PEND;     /*offset 0x14*/
    __IO uint32_t TS_SEL;   /*offset 0x18*/
} EXTI_Module;

/**
 * @brief FLASH Registers
 */

typedef struct
{
    __IO uint32_t AC;
    __IO uint32_t KEYR;
    __IO uint32_t OPTKEY;
    __IO uint32_t STS;
    __IO uint32_t CTRL;
    __IO uint32_t ADD;
    __IO uint32_t OB2;
    __IO uint32_t OB;
    __IO uint32_t WRP;
    __IO uint32_t RESERVED0;
    __IO uint32_t RESERVED1;
    __IO uint32_t RESERVED2;
    __IO uint32_t CAHR;
} FLASH_Module;

/**
 * @brief Option Bytes Registers
 */

typedef struct
{
    __IO uint32_t USER_RDP;
    __IO uint32_t Data1_Data0;
    __IO uint32_t WRP1_WRP0;
    __IO uint32_t WRP3_WRP2;
    __IO uint32_t USER2_RDP2;
} OB_Module;

/**
 * @brief General Purpose I/O
 */

typedef struct
{
    __IO uint32_t PMODE;  /*offset 0x00*/
    __IO uint32_t POTYPE; /*offset 0x04*/
      __IO uint32_t SR;     /*offset 0x08*/
    __IO uint32_t PUPD;  /*offset 0x0C*/
    __IO uint32_t PID;   /*offset 0x10*/
    __IO uint32_t POD;   /*offset 0x14*/
    __IO uint32_t PBSC;  /*offset 0x18*/
    __IO uint32_t PLOCK; /*offset 0x1C*/
    __IO uint32_t AFL;   /*offset 0x20*/
    __IO uint32_t AFH;   /*offset 0x24*/
    __IO uint32_t PBC;   /*offset 0x28*/
    __IO uint32_t DS;    /*offset 0x2C*/

} GPIO_Module;

/**
 * @brief Alternate Function I/O
 */

typedef struct
{
    __IO uint32_t RMP_CFG;
    __IO uint32_t EXTI_CFG[4];
} AFIO_Module;
/**
 * @brief Inter Integrated Circuit Interface
 */

typedef struct
{
    __IO uint16_t CTRL1;
    uint16_t RESERVED0;
    __IO uint16_t CTRL2;
    uint16_t RESERVED1;
    __IO uint16_t OADDR1;
    uint16_t RESERVED2;
    __IO uint16_t OADDR2;
    uint16_t RESERVED3;
    __IO uint16_t DAT;
    uint16_t RESERVED4;
    __IO uint16_t STS1;
    uint16_t RESERVED5;
    __IO uint16_t STS2;
    uint16_t RESERVED6;
    __IO uint16_t CLKCTRL;
    uint16_t RESERVED7;
    __IO uint16_t TMRISE;
    uint16_t RESERVED8;
} I2C_Module;

/**
 * @brief Independent WATCHDOG
 */

typedef struct
{
    __IO uint32_t KEY;
    __IO uint32_t PREDIV; /*!< IWDG PREDIV */
    __IO uint32_t RELV;
    __IO uint32_t STS;
} IWDG_Module;

/**
 * @brief Power Control
 */

typedef struct
{
    __IO uint32_t CTRL1;
    __IO uint32_t CTRL2;
    __IO uint32_t CTRL3;
      __IO uint32_t STS1;
      __IO uint32_t STS2;
      __IO uint32_t STSCLR;
} PWR_Module;
/**
 * @brief Low-Power Timer
 */
typedef struct
{
    __IO uint32_t INTSTS;
  __IO uint32_t INTCLR;
  __IO uint32_t INTEN;
  __IO uint32_t CFG;
    __IO uint32_t CTRL;
  __IO uint32_t COMPx;
  __IO uint32_t ARR;
  __IO uint32_t CNT;

} LPTIM_Module;

/**
 * @brief Reset and Clock Control
 */

typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CFG;
    __IO uint32_t CLKINT;
    __IO uint32_t APB2PRST;
    __IO uint32_t APB1PRST;
    __IO uint32_t AHBPCLKEN;
    __IO uint32_t APB2PCLKEN;
    __IO uint32_t APB1PCLKEN;
    __IO uint32_t LDCTRL;
    __IO uint32_t CTRLSTS;
    __IO uint32_t AHBPRST;
    __IO uint32_t CFG2;
    __IO uint32_t CFG3;
    __IO uint32_t RDCTRL;
    __IO uint32_t Reserve0;
    __IO uint32_t Reserve1;
    __IO uint32_t PLLHSIPRE;
    __IO uint32_t SRAM_CTRLSTS;
} RCC_Module;

/**
 * @brief Real-Time Clock
 */

typedef struct
{
    __IO uint32_t TSH;         /*!< RTC time register,                                         Address offset: 0x00 */
    __IO uint32_t DATE;        /*!< RTC date register,                                         Address offset: 0x04 */
    __IO uint32_t CTRL;        /*!< RTC control register,                                      Address offset: 0x08 */
    __IO uint32_t INITSTS;     /*!< RTC initialization and status register,                    Address offset: 0x0C */
    __IO uint32_t PRE;         /*!< RTC prescaler register,                                    Address offset: 0x10 */
    __IO uint32_t WKUPT;       /*!< RTC wakeup timer register,                                 Address offset: 0x14 */
    uint32_t reserved0;        /*!< Reserved  */
    __IO uint32_t ALARMA;      /*!< RTC alarm A register,                                      Address offset: 0x1C */
    __IO uint32_t ALARMB;      /*!< RTC alarm B register,                                      Address offset: 0x20 */
    __IO uint32_t WRP;         /*!< RTC write protection register,                             Address offset: 0x24 */
    __IO uint32_t SUBS;        /*!< RTC sub second register,                                   Address offset: 0x28 */
    __IO uint32_t SCTRL;       /*!< RTC shift control register,                                Address offset: 0x2C */
    __IO uint32_t TST;         /*!< RTC time stamp time register,                              Address offset: 0x30 */
    __IO uint32_t TSD;         /*!< RTC time stamp date register,                              Address offset: 0x34 */
    __IO uint32_t TSSS;        /*!< RTC time-stamp sub second register,                        Address offset: 0x38 */
    __IO uint32_t CALIB;       /*!< RTC calibration register,                                  Address offset: 0x3C */
    __IO uint32_t TMPCFG;     /*!< RTC tamper configuration register,                          Address offset: 0x40 */
    __IO uint32_t ALRMASS;     /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
    __IO uint32_t ALRMBSS;     /*!< RTC alarm B sub second register,                           Address offset: 0x48 */
    __IO uint32_t OPT;         /*!< RTC option register,                                       Address offset: 0x4C */
    __IO uint32_t BKP1R;       /*!< RTC backup register 0,                                     Address offset: 0x50 */
    __IO uint32_t BKP2R;       /*!< RTC backup register 1,                                     Address offset: 0x54 */
    __IO uint32_t BKP3R;       /*!< RTC backup register 2,                                     Address offset: 0x58 */
    __IO uint32_t BKP4R;       /*!< RTC backup register 3,                                     Address offset: 0x5C */
    __IO uint32_t BKP5R;       /*!< RTC backup register 4,                                     Address offset: 0x60 */
    __IO uint32_t BKP6R;       /*!< RTC backup register 5,                                     Address offset: 0x64 */
    __IO uint32_t BKP7R;       /*!< RTC backup register 6,                                     Address offset: 0x68 */
    __IO uint32_t BKP8R;       /*!< RTC backup register 7,                                     Address offset: 0x6C */
    __IO uint32_t BKP9R;       /*!< RTC backup register 8,                                     Address offset: 0x70 */
    __IO uint32_t BKP10R;      /*!< RTC backup register 9,                                     Address offset: 0x74 */
    __IO uint32_t BKP11R;      /*!< RTC backup register 10,                                    Address offset: 0x78 */
    __IO uint32_t BKP12R;      /*!< RTC backup register 11,                                    Address offset: 0x7C */
    __IO uint32_t BKP13R;      /*!< RTC backup register 12,                                    Address offset: 0x80 */
    __IO uint32_t BKP14R;      /*!< RTC backup register 13,                                    Address offset: 0x84 */
    __IO uint32_t BKP15R;      /*!< RTC backup register 14,                                    Address offset: 0x88 */
    __IO uint32_t BKP16R;      /*!< RTC backup register 15,                                    Address offset: 0x8C */
    __IO uint32_t BKP17R;      /*!< RTC backup register 16,                                    Address offset: 0x90 */
    __IO uint32_t BKP18R;      /*!< RTC backup register 17,                                    Address offset: 0x94 */
    __IO uint32_t BKP19R;      /*!< RTC backup register 18,                                    Address offset: 0x98 */
    __IO uint32_t BKP20R;      /*!< RTC backup register 19,                                    Address offset: 0x9C */
    __IO uint32_t TSCWKUPCTRL; /*!< TSC register 1,                                            Address offset: 0xA0 */
    __IO uint32_t TSCWKUPCNT;  /*!< TSC register 2,                                            Address offset: 0xA4 */
} RTC_Module;

/**
 * @brief Serial Peripheral Interface
 */

typedef struct
{
    __IO uint16_t CTRL1;
    uint16_t RESERVED0;
    __IO uint16_t CTRL2;
    uint16_t RESERVED1;
    __IO uint16_t STS;
    uint16_t RESERVED2;
    __IO uint16_t DAT;
    uint16_t RESERVED3;
    __IO uint16_t CRCPOLY;
    uint16_t RESERVED4;
    __IO uint16_t CRCRDAT;
    uint16_t RESERVED5;
    __IO uint16_t CRCTDAT;
    uint16_t RESERVED6;
    __IO uint16_t I2SCFG;
    uint16_t RESERVED7;
    __IO uint16_t I2SPREDIV;
    uint16_t RESERVED8;
} SPI_Module;

/**
 * @brief TIM
 */

typedef struct
{
    __IO uint32_t CTRL1;
    __IO uint32_t CTRL2;
    __IO uint16_t SMCTRL;
    uint16_t RESERVED1;
    __IO uint16_t DINTEN;
    uint16_t RESERVED2;
    __IO uint32_t STS;
    __IO uint16_t EVTGEN;
    uint16_t RESERVED3;
    __IO uint16_t CCMOD1;
    uint16_t RESERVED4;
    __IO uint16_t CCMOD2;
    uint16_t RESERVED5;
    __IO uint32_t CCEN;
    __IO uint16_t CNT;
    uint16_t RESERVED6;
    __IO uint16_t PSC;
    uint16_t RESERVED7;
    __IO uint16_t AR;
    uint16_t RESERVED8;
    __IO uint16_t REPCNT;
    uint16_t RESERVED9;
    __IO uint16_t CCDAT1;
    uint16_t RESERVED10;
    __IO uint16_t CCDAT2;
    uint16_t RESERVED11;
    __IO uint16_t CCDAT3;
    uint16_t RESERVED12;
    __IO uint16_t CCDAT4;
    uint16_t RESERVED13;
    __IO uint16_t BKDT;
    uint16_t RESERVED14;
    __IO uint16_t DCTRL;
    uint16_t RESERVED15;
    __IO uint16_t DADDR;
    uint16_t RESERVED16;
    uint32_t RESERVED17;
    __IO uint16_t CCMOD3;
    uint16_t RESERVED18;
    __IO uint16_t CCDAT5;
    uint16_t RESERVED19;
    __IO uint16_t CCDAT6;
    uint16_t RESERVED20;
} TIM_Module;

/**
 * @brief Universal Synchronous Asynchronous Receiver Transmitter
 */

typedef struct
{
    __IO uint16_t STS;
    uint16_t RESERVED0;
    __IO uint16_t DAT;
    uint16_t RESERVED1;
    __IO uint16_t BRCF;
    uint16_t RESERVED2;
    __IO uint16_t CTRL1;
    uint16_t RESERVED3;
    __IO uint16_t CTRL2;
    uint16_t RESERVED4;
    __IO uint16_t CTRL3;
    uint16_t RESERVED5;
    __IO uint16_t GTP;
    uint16_t RESERVED6;
} USART_Module;

/**
 * @brief Low-power Universal Asynchronous Receiver Transmitter
 */

typedef struct
{
   __IO uint16_t STS;
   uint16_t RESERVED0;
   __IO uint8_t INTEN;
   uint8_t RESERVED1;
   uint16_t RESERVED2;
   __IO uint16_t CTRL;
   uint16_t RESERVED3;
   __IO uint16_t BRCFG1;
   uint16_t RESERVED4;
   __IO uint8_t DAT;
   uint8_t RESERVED5;
   uint16_t RESERVED6;
   __IO uint8_t BRCFG2;
   uint8_t RESERVED7;
   uint16_t RESERVED8;
   __IO uint32_t WUDAT;
} LPUART_Module;

/**
 * @brief Window WATCHDOG
 */

typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CFG;
    __IO uint32_t STS;
} WWDG_Module;

/**
 * @brief LCD Controller
 */

typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t FCTRL;
    __IO uint32_t STS;
    __IO uint32_t CLR;
    uint32_t RESERVED;
    __IO uint32_t RAM_COM[16];
} LCD_Module;

/**
 * @brief Touch Sensor Controller
 */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CHNEN;
    __IO uint32_t STS;
    __IO uint32_t RESERVED;
    __IO uint32_t ANA_CTRL;
    __IO uint32_t ANA_SEL;
    __IO uint32_t RESR[3];
//    __IO uint32_t RESR0;
//    __IO uint32_t RESR1;
//    __IO uint32_t RESR2;
    __IO uint32_t THRHD[24];
//    __IO uint32_t THRHD0;
//    __IO uint32_t THRHD1;
//    __IO uint32_t THRHD2;
//    __IO uint32_t THRHD3;
//    __IO uint32_t THRHD4;
//    __IO uint32_t THRHD5;
//    __IO uint32_t THRHD6;
//    __IO uint32_t THRHD7;
//    __IO uint32_t THRHD8;
//    __IO uint32_t THRHD9;
//    __IO uint32_t THRHD10;
//    __IO uint32_t THRHD11;
//    __IO uint32_t THRHD12;
//    __IO uint32_t THRHD13;
//    __IO uint32_t THRHD14;
//    __IO uint32_t THRHD15;
//    __IO uint32_t THRHD16;
//    __IO uint32_t THRHD17;
//    __IO uint32_t THRHD18;
//    __IO uint32_t THRHD19;
//    __IO uint32_t THRHD20;
//    __IO uint32_t THRHD21;
//    __IO uint32_t THRHD22;
//    __IO uint32_t THRHD23;

} TSC_Module;

#define FLASH_BASE  ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE   ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE   ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */

#define UCID_BASE           ((uint32_t)0x1FFFF7C0) /*!< UCID Address : 0x1FFF_F7C0 */
#define UCID_LENGTH         ((uint32_t)0x10)       /*!< UCID Length  : 16Bytes */
#define UID_BASE            ((uint32_t)0x1FFFF7F0) /*!< UID Address  : 0x1FFF_F7F0 */
#define UID_LENGTH          ((uint32_t)0x0C)       /*!< UID Length   : 12Bytes */
#define DBGMCU_ID_BASE      ((uint32_t)0x1FFFF7FC) /*!< DBGMCU_ID Address */
#define DBGMCU_ID_LENGTH    ((uint8_t)0x04)        /*!< DBGMCU_ID Length : 4 Bytes */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE (PERIPH_BASE)
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x18000)

/* APB1 */
#define TIM2_BASE          (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE          (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE          (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE          (APB1PERIPH_BASE + 0x0C00)
#define TIM6_BASE          (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE          (APB1PERIPH_BASE + 0x1400)
#define AFEC_BASE          (APB1PERIPH_BASE + 0x1800)
#define OPAMP_BASE         (APB1PERIPH_BASE + 0x2000)
#define COMP_BASE          (APB1PERIPH_BASE + 0x2400)
#define RTC_BASE           (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE          (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE          (APB1PERIPH_BASE + 0x3000)
#define TSC_BASE           (APB1PERIPH_BASE + 0x3400)

#define TIM9_BASE          (APB1PERIPH_BASE + 0x3C00)
#define LCD_BASE           (APB1PERIPH_BASE + 0x4000)
#define USART2_BASE        (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE        (APB1PERIPH_BASE + 0x4800)
#define LPTIM_BASE         (APB1PERIPH_BASE + 0x4C00)
#define LPUART_BASE        (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE          (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE          (APB1PERIPH_BASE + 0x5800)
#define USB_BASE           (APB1PERIPH_BASE + 0x5C00)
#define USB_SRAM_BASE      (APB1PERIPH_BASE + 0x6000)
#define CAN_BASE           (APB1PERIPH_BASE + 0x6400)
#define PWR_BASE           (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE           (APB1PERIPH_BASE + 0x7400)

/* APB2 */
#define AFIO_BASE          (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE          (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE         (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE         (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE         (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE         (APB2PERIPH_BASE + 0x1400)
#define TIM1_BASE          (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE          (APB2PERIPH_BASE + 0x3000)
#define TIM8_BASE          (APB2PERIPH_BASE + 0x3400)
#define USART1_BASE        (APB2PERIPH_BASE + 0x3800)
#define SPI2_BASE          (APB2PERIPH_BASE + 0x3C00)
#define UART4_BASE         (APB2PERIPH_BASE + 0x5000)
#define UART5_BASE         (APB2PERIPH_BASE + 0x5400)

/* AHB */
#define DMA_BASE           (AHBPERIPH_BASE + 0x8000)
#define DMA_CH1_BASE       (AHBPERIPH_BASE + 0x8008)
#define DMA_CH2_BASE       (AHBPERIPH_BASE + 0x801C)
#define DMA_CH3_BASE       (AHBPERIPH_BASE + 0x8030)
#define DMA_CH4_BASE       (AHBPERIPH_BASE + 0x8044)
#define DMA_CH5_BASE       (AHBPERIPH_BASE + 0x8058)
#define DMA_CH6_BASE       (AHBPERIPH_BASE + 0x806C)
#define DMA_CH7_BASE       (AHBPERIPH_BASE + 0x8080)
#define DMA_CH8_BASE       (AHBPERIPH_BASE + 0x8094)
#define ADC_BASE           (AHBPERIPH_BASE + 0x8800)
#define RCC_BASE           (AHBPERIPH_BASE + 0x9000)
#define FLASH_R_BASE       (AHBPERIPH_BASE + 0xA000) /*!< Flash registers base address */
#define OB_BASE            ((uint32_t)0x1FFFF800)    /*!< Flash Option Bytes base address */
#define CRC_BASE           (AHBPERIPH_BASE + 0xB000)
#define SAC_BASE           (AHBPERIPH_BASE + 0xC000)
#define SAC_SRAM_BASE      (AHBPERIPH_BASE + 0xC400)
#define MMU_BASE           (AHBPERIPH_BASE + 0xCC00)

#define DBG_BASE ((uint32_t)0xE0042000) /*!< Debug MCU registers base address */

#define TIM2        ((TIM_Module*)TIM2_BASE)
#define TIM3        ((TIM_Module*)TIM3_BASE)
#define TIM4        ((TIM_Module*)TIM4_BASE)
#define TIM5        ((TIM_Module*)TIM5_BASE)
#define TIM6        ((TIM_Module*)TIM6_BASE)
#define TIM7        ((TIM_Module*)TIM7_BASE)
#define AFEC        ((AFEC_Module*)AFEC_BASE)
#define OPAMP       ((OPAMP_Module*)OPAMP_BASE)
#define COMP        ((COMP_Module*)COMP_BASE)
#define RTC         ((RTC_Module*)RTC_BASE)
#define WWDG        ((WWDG_Module*)WWDG_BASE)
#define IWDG        ((IWDG_Module*)IWDG_BASE)
#define TSC         ((TSC_Module*)TSC_BASE)

#define TIM9        ((TIM_Module*)TIM9_BASE)
#define LCD         ((LCD_Module*)LCD_BASE)
#define USART2      ((USART_Module*)USART2_BASE)
#define USART3      ((USART_Module*)USART3_BASE)
#define LPTIM       ((LPTIM_Module*)LPTIM_BASE)
#define LPUART      ((LPUART_Module*)LPUART_BASE)
#define I2C1        ((I2C_Module*)I2C1_BASE)
#define I2C2        ((I2C_Module*)I2C2_BASE)
#define USB         ((USB_Module*)USB_BASE)
#define CAN         ((CAN_Module*)CAN_BASE)
#define PWR         ((PWR_Module*)PWR_BASE)
#define DAC         ((DAC_Module*)DAC_BASE)
#define AFIO        ((AFIO_Module*)AFIO_BASE)
#define EXTI        ((EXTI_Module*)EXTI_BASE)
#define GPIOA       ((GPIO_Module*)GPIOA_BASE)
#define GPIOB       ((GPIO_Module*)GPIOB_BASE)
#define GPIOC       ((GPIO_Module*)GPIOC_BASE)
#define GPIOD       ((GPIO_Module*)GPIOD_BASE)
#define TIM1        ((TIM_Module*)TIM1_BASE)
#define SPI1        ((SPI_Module*)SPI1_BASE)
#define TIM8        ((TIM_Module*)TIM8_BASE)
#define USART1      ((USART_Module*)USART1_BASE)
#define SPI2        ((SPI_Module*)SPI2_BASE)
#define UART4       ((USART_Module*)UART4_BASE)
#define UART5       ((USART_Module*)UART5_BASE)
#define DMA         ((DMA_Module*)DMA_BASE)
#define DMA_CH1     ((DMA_ChannelType*)DMA_CH1_BASE)
#define DMA_CH2     ((DMA_ChannelType*)DMA_CH2_BASE)
#define DMA_CH3     ((DMA_ChannelType*)DMA_CH3_BASE)
#define DMA_CH4     ((DMA_ChannelType*)DMA_CH4_BASE)
#define DMA_CH5     ((DMA_ChannelType*)DMA_CH5_BASE)
#define DMA_CH6     ((DMA_ChannelType*)DMA_CH6_BASE)
#define DMA_CH7     ((DMA_ChannelType*)DMA_CH7_BASE)
#define DMA_CH8     ((DMA_ChannelType*)DMA_CH8_BASE)
#define ADC         ((ADC_Module*)ADC_BASE)
#define RCC         ((RCC_Module*)RCC_BASE)
#define FLASH       ((FLASH_Module*)FLASH_R_BASE)
#define OBT         ((OB_Module*)OB_BASE)
#define CRC         ((CRC_Module*)CRC_BASE)

#define DBG ((DBG_Module*)DBG_BASE)

/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                          CRC calculation unit                              */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for CRC_CRC32DAT register  *********************/
#define CRC32_DAT_DAT ((uint32_t)0xFFFFFFFF) /*!< Data register bits */

/*******************  Bit definition for CRC_CRC32IDAT register  ********************/
#define CRC32_IDAT_IDAT ((uint8_t)0xFF) /*!< General-purpose 8-bit data register bits */

/********************  Bit definition for CRC_CRC32CTRL register  ********************/
#define CRC32_CTRL_RESET ((uint8_t)0x01) /*!< RESET bit */

/********************  Bit definition for CRC16_CR register  ********************/
#define CRC16_CTRL_LITTLE ((uint8_t)0x02)
#define CRC16_CTRL_BIG    ((uint8_t)0xFD)

#define CRC16_CTRL_RESET    ((uint8_t)0x04)
#define CRC16_CTRL_NO_RESET ((uint8_t)0xFB)

/******************************************************************************/
/*                                                                            */
/*                             Power Control                                  */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for PWR_CTRL1 register  ********************/
#define PWR_CTRL1_LPMSEL                       ((uint16_t)0x0007)     /*!< no low power mode entered */
#define PWR_CTRL1_STOP2                        ((uint16_t)0x0002)     /*!< stop2 mode */
#define PWR_CTRL1_STANDBY                      ((uint16_t)0x0003)     /*!< standby mode */


#define PWR_CTRL1_DRBP                         ((uint16_t)0x0100)     /*!< Access to RTC and Backup registers enabled */

#define PWR_CTRL1_MRSEL                        ((uint16_t)0x0600)     /*!< vddd Range Mask */
#define PWR_CTRL1_MRSEL_bit0                   ((uint16_t)0x0200)     /*!< vddd Range MRSEL bit0 */
#define PWR_CTRL1_MRSEL_bit1                   ((uint16_t)0x0400)     /*!< vddd Range MRSEL bit1 */
#define PWR_CTRL1_MRSEL2                       ((uint16_t)0x0400)     /*!< vddd Range2=1.0 V */

#define PWR_CTRL1_LPREN                        ((uint16_t)0x4000)     /*!< When this bit is set, MR is turned off and LPR is used to run the main power domain. */
#define PWR_CTRL1_MRSELMASK                    ((uint16_t)0x0600)     /*!< MR voltage mask */
/********************  Bit definition for PWR_CTRL2 register  ********************/
#define PWR_CTRL2_PVDEN                        ((uint16_t)0x0001)     /*!< Power voltage detector enable */
#define PWR_CTRL2_PLS1                         ((uint16_t)0x0000)     /*!< voltage threshold around 2.1 V */
#define PWR_CTRL2_PLS2                         ((uint16_t)0x0002)     /*!< voltage threshold around 2.25 V */
#define PWR_CTRL2_PLS3                         ((uint16_t)0x0004)     /*!< voltage threshold around 2.4 V */
#define PWR_CTRL2_PLS4                         ((uint16_t)0x0006)     /*!< voltage threshold around 2.55 V */
#define PWR_CTRL2_PLS5                         ((uint16_t)0x0008)     /*!< voltage threshold around 2.7 V */
#define PWR_CTRL2_PLS6                         ((uint16_t)0x000A)     /*!< voltage threshold around 2.85 V */
#define PWR_CTRL2_PLS7                         ((uint16_t)0x000C)     /*!< voltage threshold around 2.95 V */
#define PWR_CTRL2_PLS8                         ((uint16_t)0x000E)     /*!< external input analog voltage PVD_IN (compared internally to VREFINT) */

#define PWR_CTRL2_PVDFLTEN                     ((uint16_t)0x0010)     /*!< Power voltage detector filter enable */


/********************  Bit definition for PWR_CTRL3 register  ********************/
#define PWR_CTRL3_WKUP0EN                      ((uint16_t)0x0001)     /*!< When this bit is set, WKUP0 pin is enable and triggers a wakeup from standby . */
#define PWR_CTRL3_WKUP1EN                      ((uint16_t)0x0002)     /*!< When this bit is set, WKUP1 pin is enable and triggers a wakeup from standby . */
#define PWR_CTRL3_WKUP2EN                      ((uint16_t)0x0004)     /*!< When this bit is set, WKUP2 pin is enable and triggers a wakeup from standby. */
#define PWR_CTRL3_WKUP0PS                      ((uint16_t)0x0010)     /*!< falling edge wake up */
#define PWR_CTRL3_WKUP1PS                      ((uint16_t)0x0020)     /*!< falling edge wake up */
#define PWR_CTRL3_WKUP2PS                      ((uint16_t)0x0040)     /*!< falling edge wake up */
#define PWR_CTRL3_BGDTLPR                      ((uint16_t)0x0100)     /*!< BANDGAP/BG_Buffer/IBIAS duty on in LPRUN */
#define PWR_CTRL3_BGDTSTP2                     ((uint16_t)0x0200)     /*!< BANDGAP/BG_Buffer/IBIAS duty on in stop2 */
#define PWR_CTRL3_BGDTSTBY                     ((uint16_t)0x0400)     /*!< BANDGAP/BG_Buffer/IBIAS duty on in standby */
#define PWR_CTRL3_RAM1RET                      ((uint16_t)0x1000)     /*!< SRAM1 is powered by the LPR in stop2 mode */
#define PWR_CTRL3_RAM2RET                      ((uint16_t)0x2000)     /*!< SRAM2 is powered by the LPR in standby mode */
#define PWR_CTRL3_IWKUPLEN                      ((uint16_t)0x4000)    /*!< internal wakeup line enable */

#define PWR_CTRL3_PBDTLPR                      ((uint32_t)0x10000)     /*!< PVDBOR duty on in LP RUN */
#define PWR_CTRL3_PBDTSTP2                     ((uint32_t)0x20000)     /*!< PVDBOR duty on in STOP2 */
#define PWR_CTRL3_PBDTSTBY                     ((uint32_t)0x40000)     /*!< PVDBOR is iduty on standby */
#define PWR_CTRL3_PSTSTBY                      ((uint32_t)0x100000)     /*!< PAD in HI-Z state  */
#define PWR_CTRL3_PSTSTP2                      ((uint32_t)0x200000)     /*!< PAD in HI-Z state  */

#define PWR_CTRL3_RAMRETMASK                       ((uint16_t)0x3000)     /*!< SRAM1 and SRAM2 ENABLE */
#define PWR_CTRL1_LPMSELMASK                       ((uint16_t)0x0007)     /*!< Low power mode selection */
#define PWR_CTRL2_PLSMASK                          ((uint16_t)0x000E)     /*!< Low power mode selection */
/********************  Bit definition for PWR_STS1 register  ********************/
#define PWR_STS1_WKUPF0                         ((uint16_t)0x0001)     /*!< This bit is set when a wakeup event is detected on wakeup pin, WKUP0. */
#define PWR_STS1_WKUPF1                         ((uint16_t)0x0002)     /*!< This bit is set when a wakeup event is detected on wakeup pin, WKUP1. */
#define PWR_STS1_WKUPF2                         ((uint16_t)0x0004)     /*!< This bit is set when a wakeup event is detected on wakeup pin, WKUP2. */
#define PWR_STS1_STBYF                          ((uint16_t)0x0100)     /*!< the device entered the standby mode */
#define PWR_STS1_IWKUPF                         ((uint16_t)0x8000)     /*!< This bit is set when a wakeup is detected on the internal wakeup line. */

/********************  Bit definition for PWR_STS2 register  ********************/
#define PWR_STS2_LPRUNF                       ((uint16_t)0x0001)     /*!< MCU is in low power run mode */
#define PWR_STS2_MRF                          ((uint16_t)0x0002)     /*!< voltage scaling ready */
#define PWR_STS2_PVDO                         ((uint16_t)0x0004)     /*!< Power voltage detector output */

/********************  Bit definition for PWR_STSCLR register  ********************/
#define PWR_STSCLR_CLRWKUP0                        ((uint16_t)0x0001)     /*!< Setting this bit clears the WKPF1 flag in the PWR_STS1 register */
#define PWR_STSCLR_CLRWKUP1                        ((uint16_t)0x0002)     /*!< Setting this bit clears the WKPF2 flag in the PWR_STS1 register */
#define PWR_STSCLR_CLRWKUP2                        ((uint16_t)0x0004)     /*!< Setting this bit clears the WKPF3 flag in the PWR_STS1 register */
#define PWR_STSCLR_CLRSTBY                         ((uint16_t)0x0100)     /*!< Setting this bit clears the SBF flag in the PWR_STS1 register */




/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for RCC_CTRL register  ********************/
#define RCC_CTRL_HSIEN   ((uint32_t)0x00000001) /*!< Internal High Speed clock enable */
#define RCC_CTRL_HSIRDF  ((uint32_t)0x00000002) /*!< Internal High Speed clock ready flag */
#define RCC_CTRL_HSITRIM ((uint32_t)0x0000007C) /*!< Internal High Speed clock trimming */
#define RCC_CTRL_HSICAL  ((uint32_t)0x0000FF80) /*!< Internal High Speed clock Calibration */
#define RCC_CTRL_HSEEN   ((uint32_t)0x00010000) /*!< External High Speed clock enable */
#define RCC_CTRL_HSERDF  ((uint32_t)0x00020000) /*!< External High Speed clock ready flag */
#define RCC_CTRL_HSEBP   ((uint32_t)0x00040000) /*!< External High Speed clock Bypass */
#define RCC_CTRL_CLKSSEN ((uint32_t)0x00080000) /*!< Clock Security System enable */
#define RCC_CTRL_PLLEN   ((uint32_t)0x01000000) /*!< PLL enable */
#define RCC_CTRL_PLLRDF  ((uint32_t)0x02000000) /*!< PLL clock ready flag */

/*******************  Bit definition for RCC_CFG register  *******************/
/*!< SW configuration */
#define RCC_CFG_SCLKSW   ((uint32_t)0x00000003) /*!< SW[1:0] bits (System clock Switch) */
#define RCC_CFG_SCLKSW_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define RCC_CFG_SCLKSW_1 ((uint32_t)0x00000002) /*!< Bit 1 */

#define RCC_CFG_SCLKSW_MSI ((uint32_t)0x00000000) /*!< MSI selected as system clock */
#define RCC_CFG_SCLKSW_HSI ((uint32_t)0x00000001) /*!< HSI selected as system clock */
#define RCC_CFG_SCLKSW_HSE ((uint32_t)0x00000002) /*!< HSE selected as system clock */
#define RCC_CFG_SCLKSW_PLL ((uint32_t)0x00000003) /*!< PLL selected as system clock */

/*!< SWS configuration */
#define RCC_CFG_SCLKSTS   ((uint32_t)0x0000000C) /*!< SWS[1:0] bits (System Clock Switch Status) */
#define RCC_CFG_SCLKSTS_0 ((uint32_t)0x00000004) /*!< Bit 0 */
#define RCC_CFG_SCLKSTS_1 ((uint32_t)0x00000008) /*!< Bit 1 */

#define RCC_CFG_SCLKSTS_MSI ((uint32_t)0x00000000) /*!< MSI oscillator used as system clock */
#define RCC_CFG_SCLKSTS_HSI ((uint32_t)0x00000004) /*!< HSI oscillator used as system clock */
#define RCC_CFG_SCLKSTS_HSE ((uint32_t)0x00000008) /*!< HSE oscillator used as system clock */
#define RCC_CFG_SCLKSTS_PLL ((uint32_t)0x0000000C) /*!< PLL used as system clock */

/*!< AHBPRES configuration */
#define RCC_CFG_AHBPRES   ((uint32_t)0x000000F0) /*!< AHBPRES[3:0] bits (AHB prescaler) */
#define RCC_CFG_AHBPRES_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define RCC_CFG_AHBPRES_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define RCC_CFG_AHBPRES_2 ((uint32_t)0x00000040) /*!< Bit 2 */
#define RCC_CFG_AHBPRES_3 ((uint32_t)0x00000080) /*!< Bit 3 */

#define RCC_CFG_AHBPRES_DIV1   ((uint32_t)0x00000000) /*!< SYSCLK not divided */
#define RCC_CFG_AHBPRES_DIV2   ((uint32_t)0x00000080) /*!< SYSCLK divided by 2 */
#define RCC_CFG_AHBPRES_DIV4   ((uint32_t)0x00000090) /*!< SYSCLK divided by 4 */
#define RCC_CFG_AHBPRES_DIV8   ((uint32_t)0x000000A0) /*!< SYSCLK divided by 8 */
#define RCC_CFG_AHBPRES_DIV16  ((uint32_t)0x000000B0) /*!< SYSCLK divided by 16 */
#define RCC_CFG_AHBPRES_DIV64  ((uint32_t)0x000000C0) /*!< SYSCLK divided by 64 */
#define RCC_CFG_AHBPRES_DIV128 ((uint32_t)0x000000D0) /*!< SYSCLK divided by 128 */
#define RCC_CFG_AHBPRES_DIV256 ((uint32_t)0x000000E0) /*!< SYSCLK divided by 256 */
#define RCC_CFG_AHBPRES_DIV512 ((uint32_t)0x000000F0) /*!< SYSCLK divided by 512 */

/*!< APB1PRES configuration */
#define RCC_CFG_APB1PRES   ((uint32_t)0x00000700) /*!< APB1PRES[2:0] bits (APB1 prescaler) */
#define RCC_CFG_APB1PRES_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define RCC_CFG_APB1PRES_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define RCC_CFG_APB1PRES_2 ((uint32_t)0x00000400) /*!< Bit 2 */

#define RCC_CFG_APB1PRES_DIV1  ((uint32_t)0x00000000) /*!< HCLK not divided */
#define RCC_CFG_APB1PRES_DIV2  ((uint32_t)0x00000400) /*!< HCLK divided by 2 */
#define RCC_CFG_APB1PRES_DIV4  ((uint32_t)0x00000500) /*!< HCLK divided by 4 */
#define RCC_CFG_APB1PRES_DIV8  ((uint32_t)0x00000600) /*!< HCLK divided by 8 */
#define RCC_CFG_APB1PRES_DIV16 ((uint32_t)0x00000700) /*!< HCLK divided by 16 */

/*!< APB2PRES configuration */
#define RCC_CFG_APB2PRES   ((uint32_t)0x00003800) /*!< APB2PRES[2:0] bits (APB2 prescaler) */
#define RCC_CFG_APB2PRES_0 ((uint32_t)0x00000800) /*!< Bit 0 */
#define RCC_CFG_APB2PRES_1 ((uint32_t)0x00001000) /*!< Bit 1 */
#define RCC_CFG_APB2PRES_2 ((uint32_t)0x00002000) /*!< Bit 2 */

#define RCC_CFG_APB2PRES_DIV1  ((uint32_t)0x00000000) /*!< HCLK not divided */
#define RCC_CFG_APB2PRES_DIV2  ((uint32_t)0x00002000) /*!< HCLK divided by 2 */
#define RCC_CFG_APB2PRES_DIV4  ((uint32_t)0x00002800) /*!< HCLK divided by 4 */
#define RCC_CFG_APB2PRES_DIV8  ((uint32_t)0x00003000) /*!< HCLK divided by 8 */
#define RCC_CFG_APB2PRES_DIV16 ((uint32_t)0x00003800) /*!< HCLK divided by 16 */

/*!< PLLSRC configuration */
#define RCC_CFG_PLLSRC ((uint32_t)0x00010000) /*!< PLL entry clock source */

#define RCC_CFG_PLLSRC_HSI ((uint32_t)0x00000000) /*!< HSI clock selected as PLL entry clock source */
#define RCC_CFG_PLLSRC_HSE ((uint32_t)0x00010000) /*!< HSE clock selected as PLL entry clock source */

/*!< PLLXTPRE configuration */
#define RCC_CFG_PLLHSEPRES ((uint32_t)0x00020000) /*!< HSE divider for PLL entry */

#define RCC_CFG_PLLHSEPRES_HSE      ((uint32_t)0x00000000) /*!< HSE clock not divided for PLL entry */
#define RCC_CFG_PLLHSEPRES_HSE_DIV2 ((uint32_t)0x00020000) /*!< HSE clock divided by 2 for PLL entry */

/*!< PLLMUL configuration */
#define RCC_CFG_PLLMULFCT   ((uint32_t)0x083C0000) /*!< PLLMUL[4:0] bits (PLL multiplication factor) */
#define RCC_CFG_PLLMULFCT_0 ((uint32_t)0x00040000) /*!< Bit 0 */
#define RCC_CFG_PLLMULFCT_1 ((uint32_t)0x00080000) /*!< Bit 1 */
#define RCC_CFG_PLLMULFCT_2 ((uint32_t)0x00100000) /*!< Bit 2 */
#define RCC_CFG_PLLMULFCT_3 ((uint32_t)0x00200000) /*!< Bit 3 */
#define RCC_CFG_PLLMULFCT_4 ((uint32_t)0x08000000) /*!< Bit 4 */

#define RCC_CFG_PLLMULFCT2          ((uint32_t)0x00000000) /*!< PLL input clock*2 */
#define RCC_CFG_PLLMULFCT3          ((uint32_t)0x00040000) /*!< PLL input clock*3 */
#define RCC_CFG_PLLMULFCT4          ((uint32_t)0x00080000) /*!< PLL input clock*4 */
#define RCC_CFG_PLLMULFCT5          ((uint32_t)0x000C0000) /*!< PLL input clock*5 */
#define RCC_CFG_PLLMULFCT6          ((uint32_t)0x00100000) /*!< PLL input clock*6 */
#define RCC_CFG_PLLMULFCT7          ((uint32_t)0x00140000) /*!< PLL input clock*7 */
#define RCC_CFG_PLLMULFCT8          ((uint32_t)0x00180000) /*!< PLL input clock*8 */
#define RCC_CFG_PLLMULFCT9          ((uint32_t)0x001C0000) /*!< PLL input clock*9 */
#define RCC_CFG_PLLMULFCT10         ((uint32_t)0x00200000) /*!< PLL input clock*10 */
#define RCC_CFG_PLLMULFCT11         ((uint32_t)0x00240000) /*!< PLL input clock*11 */
#define RCC_CFG_PLLMULFCT12         ((uint32_t)0x00280000) /*!< PLL input clock*12 */
#define RCC_CFG_PLLMULFCT13         ((uint32_t)0x002C0000) /*!< PLL input clock*13 */
#define RCC_CFG_PLLMULFCT14         ((uint32_t)0x00300000) /*!< PLL input clock*14 */
#define RCC_CFG_PLLMULFCT15         ((uint32_t)0x00340000) /*!< PLL input clock*15 */
#define RCC_CFG_PLLMULFCT16         ((uint32_t)0x00380000) /*!< PLL input clock*16 */
#define RCC_CFG_PLLMULFCT16N        ((uint32_t)0x003C0000) /*!< PLL input clock*16 */
#define RCC_CFG_PLLMULFCT17         ((uint32_t)0x08000000) /*!< PLL input clock*17 */
#define RCC_CFG_PLLMULFCT18         ((uint32_t)0x08040000) /*!< PLL input clock*18 */
#define RCC_CFG_PLLMULFCT19         ((uint32_t)0x08080000) /*!< PLL input clock*19 */
#define RCC_CFG_PLLMULFCT20         ((uint32_t)0x080C0000) /*!< PLL input clock*20 */
#define RCC_CFG_PLLMULFCT21         ((uint32_t)0x08100000) /*!< PLL input clock*21 */
#define RCC_CFG_PLLMULFCT22         ((uint32_t)0x08140000) /*!< PLL input clock*22 */
#define RCC_CFG_PLLMULFCT23         ((uint32_t)0x08180000) /*!< PLL input clock*23 */
#define RCC_CFG_PLLMULFCT24         ((uint32_t)0x081C0000) /*!< PLL input clock*24 */
#define RCC_CFG_PLLMULFCT25         ((uint32_t)0x08200000) /*!< PLL input clock*25 */
#define RCC_CFG_PLLMULFCT26         ((uint32_t)0x08240000) /*!< PLL input clock*26 */
#define RCC_CFG_PLLMULFCT27         ((uint32_t)0x08280000) /*!< PLL input clock*27 */
#define RCC_CFG_PLLMULFCT28         ((uint32_t)0x082C0000) /*!< PLL input clock*28 */
#define RCC_CFG_PLLMULFCT29         ((uint32_t)0x08300000) /*!< PLL input clock*29 */
#define RCC_CFG_PLLMULFCT30         ((uint32_t)0x08340000) /*!< PLL input clock*30 */
#define RCC_CFG_PLLMULFCT31         ((uint32_t)0x08380000) /*!< PLL input clock*31 */
#define RCC_CFG_PLLMULFCT32         ((uint32_t)0x083C0000) /*!< PLL input clock*32 */

/*!< USBPRES configuration */
#define RCC_CFG_USBPRES   ((uint32_t)0x00C00000) /*!< USB Device prescaler */
#define RCC_CFG_USBPRES_0 ((uint32_t)0x00400000) /*!< Bit 0 */
#define RCC_CFG_USBPRES_1 ((uint32_t)0x00800000) /*!< Bit 1 */

#define RCC_CFG_USBPRES_PLLDIV1_5 ((uint32_t)0x00000000) /*!< PLL clock is divided by 1.5 */
#define RCC_CFG_USBPRES_PLLDIV1   ((uint32_t)0x00400000) /*!< PLL clock is not divided */
#define RCC_CFG_USBPRES_PLLDIV2   ((uint32_t)0x00800000) /*!< PLL clock is divided by 2 */
#define RCC_CFG_USBPRES_PLLDIV3   ((uint32_t)0x00C00000) /*!< PLL clock is divided by 3 */

/*!< MCO configuration */
#define RCC_CFG_MCO   ((uint32_t)0x07000000) /*!< MCO[2:0] bits (Microcontroller Clock Output) */
#define RCC_CFG_MCO_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define RCC_CFG_MCO_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define RCC_CFG_MCO_2 ((uint32_t)0x04000000) /*!< Bit 2 */

#define RCC_CFG_MCO_NOCLK  ((uint32_t)0x00000000) /*!< No clock */
#define RCC_CFG_MCO_LSI    ((uint32_t)0x01000000) /*!< LSI clock selected as MCO source */
#define RCC_CFG_MCO_LSE    ((uint32_t)0x02000000) /*!< LSE clock selected as MCO source */
#define RCC_CFG_MCO_MSI    ((uint32_t)0x03000000) /*!< MSI clock selected as MCO source */
#define RCC_CFG_MCO_SYSCLK ((uint32_t)0x04000000) /*!< System clock selected as MCO source */
#define RCC_CFG_MCO_HSI    ((uint32_t)0x05000000) /*!< HSI clock selected as MCO source */
#define RCC_CFG_MCO_HSE    ((uint32_t)0x06000000) /*!< HSE clock selected as MCO source  */
#define RCC_CFG_MCO_PLL    ((uint32_t)0x07000000) /*!< PLL clock selected as MCO source */

/*!< MCOPRE configuration */
#define RCC_CFG_MCOPRES   ((uint32_t)0xF0000000) /*!< MCOPRE[3:0] bits ( PLL prescaler set and cleared by
                                                      software to generate MCOPRE clock.) */
#define RCC_CFG_MCOPRES_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define RCC_CFG_MCOPRES_1 ((uint32_t)0x20000000) /*!< Bit 1 */
#define RCC_CFG_MCOPRES_2 ((uint32_t)0x40000000) /*!< Bit 2 */
#define RCC_CFG_MCOPRES_3 ((uint32_t)0x80000000) /*!< Bit 3 */

#define RCC_CFG_MCOPRES_PLLDIV1  ((uint32_t)0x00000000) /*!< PLL clock is not divided */
#define RCC_CFG_MCOPRES_PLLDIV2  ((uint32_t)0x10000000) /*!< PLL clock is divided by 2 */
#define RCC_CFG_MCOPRES_PLLDIV3  ((uint32_t)0x20000000) /*!< PLL clock is divided by 3 */
#define RCC_CFG_MCOPRES_PLLDIV4  ((uint32_t)0x30000000) /*!< PLL clock is divided by 4 */
#define RCC_CFG_MCOPRES_PLLDIV5  ((uint32_t)0x40000000) /*!< PLL clock is divided by 5 */
#define RCC_CFG_MCOPRES_PLLDIV6  ((uint32_t)0x50000000) /*!< PLL clock is divided by 6 */
#define RCC_CFG_MCOPRES_PLLDIV7  ((uint32_t)0x60000000) /*!< PLL clock is divided by 7 */
#define RCC_CFG_MCOPRES_PLLDIV8  ((uint32_t)0x70000000) /*!< PLL clock is divided by 8 */
#define RCC_CFG_MCOPRES_PLLDIV9  ((uint32_t)0x80000000) /*!< PLL clock is divided by 9 */
#define RCC_CFG_MCOPRES_PLLDIV10 ((uint32_t)0x90000000) /*!< PLL clock is divided by 10 */
#define RCC_CFG_MCOPRES_PLLDIV11 ((uint32_t)0xA0000000) /*!< PLL clock is divided by 11 */
#define RCC_CFG_MCOPRES_PLLDIV12 ((uint32_t)0xB0000000) /*!< PLL clock is divided by 12 */
#define RCC_CFG_MCOPRES_PLLDIV13 ((uint32_t)0xC0000000) /*!< PLL clock is divided by 13 */
#define RCC_CFG_MCOPRES_PLLDIV14 ((uint32_t)0xD0000000) /*!< PLL clock is divided by 14 */
#define RCC_CFG_MCOPRES_PLLDIV15 ((uint32_t)0xE0000000) /*!< PLL clock is divided by 15 */
#define RCC_CFG_MCOPRES_PLLDIV16 ((uint32_t)0xF0000000) /*!< PLL clock is divided by 16 */

/*!<******************  Bit definition for RCC_CLKINT register  ********************/
#define RCC_CLKINT_LSIRDIF   ((uint32_t)0x00000001) /*!< LSI Ready Interrupt flag */
#define RCC_CLKINT_LSERDIF   ((uint32_t)0x00000002) /*!< LSE Ready Interrupt flag */
#define RCC_CLKINT_HSIRDIF   ((uint32_t)0x00000004) /*!< HSI Ready Interrupt flag */
#define RCC_CLKINT_HSERDIF   ((uint32_t)0x00000008) /*!< HSE Ready Interrupt flag */
#define RCC_CLKINT_PLLRDIF   ((uint32_t)0x00000010) /*!< PLL Ready Interrupt flag */
#define RCC_CLKINT_BORIF     ((uint32_t)0x00000020) /*!< BOR Interrupt flag */
#define RCC_CLKINT_MSIRDIF   ((uint32_t)0x00000040) /*!< MSI Ready Interrupt flag */
#define RCC_CLKINT_CLKSSIF   ((uint32_t)0x00000080) /*!< Clock Security System Interrupt flag */
#define RCC_CLKINT_LSIRDIEN  ((uint32_t)0x00000100) /*!< LSI Ready Interrupt Enable */
#define RCC_CLKINT_LSERDIEN  ((uint32_t)0x00000200) /*!< LSE Ready Interrupt Enable */
#define RCC_CLKINT_HSIRDIEN  ((uint32_t)0x00000400) /*!< HSI Ready Interrupt Enable */
#define RCC_CLKINT_HSERDIEN  ((uint32_t)0x00000800) /*!< HSE Ready Interrupt Enable */
#define RCC_CLKINT_PLLRDIEN  ((uint32_t)0x00001000) /*!< PLL Ready Interrupt Enable */
#define RCC_CLKINT_BORIEN    ((uint32_t)0x00002000) /*!< BOR Interrupt Enable */
#define RCC_CLKINT_MSIRDIEN  ((uint32_t)0x00004000) /*!< MSI Ready Interrupt Enable */
#define RCC_CLKINT_MSIRDICLR ((uint32_t)0x00008000) /*!< MSI Ready Interrupt Clear */
#define RCC_CLKINT_LSIRDICLR ((uint32_t)0x00010000) /*!< LSI Ready Interrupt Clear */
#define RCC_CLKINT_LSERDICLR ((uint32_t)0x00020000) /*!< LSE Ready Interrupt Clear */
#define RCC_CLKINT_HSIRDICLR ((uint32_t)0x00040000) /*!< HSI Ready Interrupt Clear */
#define RCC_CLKINT_HSERDICLR ((uint32_t)0x00080000) /*!< HSE Ready Interrupt Clear */
#define RCC_CLKINT_PLLRDICLR ((uint32_t)0x00100000) /*!< PLL Ready Interrupt Clear */
#define RCC_CLKINT_BORICLR   ((uint32_t)0x00200000) /*!< BOR Interrupt Clear */
#define RCC_CLKINT_CLKSSICLR ((uint32_t)0x00800000) /*!< Clock Security System Interrupt Clear */
#define RCC_CLKINT_LSESSIF   ((uint32_t)0x01000000) /*!< LSE Security System Interrupt flag */
#define RCC_CLKINT_LSESSIEN  ((uint32_t)0x02000000) /*!< LSE ecurity System Interrupt Enable */
#define RCC_CLKINT_LSESSICLR ((uint32_t)0x04000000) /*!< LSE ecurity System Interrupt Clear */

/*****************  Bit definition for RCC_APB2PRST register  *****************/
#define RCC_APB2PRST_AFIORST   ((uint32_t)0x00000001) /*!< Alternate Function I/O reset */
#define RCC_APB2PRST_IOPARST   ((uint32_t)0x00000004) /*!< I/O port A reset */
#define RCC_APB2PRST_IOPBRST   ((uint32_t)0x00000008) /*!< I/O port B reset */
#define RCC_APB2PRST_IOPCRST   ((uint32_t)0x00000010) /*!< I/O port C reset */
#define RCC_APB2PRST_IOPDRST   ((uint32_t)0x00000020) /*!< I/O port D reset */
#define RCC_APB2PRST_TIM1RST   ((uint32_t)0x00000800) /*!< TIM1 Timer reset */
#define RCC_APB2PRST_SPI1RST   ((uint32_t)0x00001000) /*!< SPI 1 reset */
#define RCC_APB2PRST_TIM8RST   ((uint32_t)0x00002000) /*!< TIM8 Timer reset */
#define RCC_APB2PRST_USART1RST ((uint32_t)0x00004000) /*!< USART1 reset */
#define RCC_APB2PRST_UART4RST  ((uint32_t)0x00020000) /*!< UART4 reset */
#define RCC_APB2PRST_UART5RST  ((uint32_t)0x00040000) /*!< UART5 reset */
#define RCC_APB2PRST_SPI2RST   ((uint32_t)0x00080000) /*!< SPI2 reset */

/*****************  Bit definition for RCC_APB1PRST register  *****************/
#define RCC_APB1PRST_TIM2RST   ((uint32_t)0x00000001) /*!< Timer 2 reset */
#define RCC_APB1PRST_TIM3RST   ((uint32_t)0x00000002) /*!< Timer 3 reset */
#define RCC_APB1PRST_TIM4RST   ((uint32_t)0x00000004) /*!< Timer 4 reset */
#define RCC_APB1PRST_TIM5RST   ((uint32_t)0x00000008) /*!< Timer 5 reset */
#define RCC_APB1PRST_TIM6RST   ((uint32_t)0x00000010) /*!< Timer 6 reset */
#define RCC_APB1PRST_TIM7RST   ((uint32_t)0x00000020) /*!< Timer 7 reset */
#define RCC_APB1PRST_COMPRST   ((uint32_t)0x00000040) /*!< COMP reset */
#define RCC_APB1PRST_TIM9RST   ((uint32_t)0x00000200) /*!< Timer 9 reset */
#define RCC_APB1PRST_TSCRST    ((uint32_t)0x00000400) /*!< TSC reset */
#define RCC_APB1PRST_WWDGRST   ((uint32_t)0x00000800) /*!< Window Watchdog reset */
#define RCC_APB1PRST_USART2RST ((uint32_t)0x00020000) /*!< USART 2 reset */
#define RCC_APB1PRST_USART3RST ((uint32_t)0x00040000) /*!< USART 3 reset */
#define RCC_APB1PRST_I2C1RST   ((uint32_t)0x00200000) /*!< I2C 1 reset */
#define RCC_APB1PRST_I2C2RST   ((uint32_t)0x00400000) /*!< I2C 2 reset */
#define RCC_APB1PRST_USBRST    ((uint32_t)0x00800000) /*!< USB Device reset */
#define RCC_APB1PRST_UCDRRST   ((uint32_t)0x01000000) /*!< UCDR reset */
#define RCC_APB1PRST_CANRST    ((uint32_t)0x02000000) /*!< CAN reset */
#define RCC_APB1PRST_PWRRST    ((uint32_t)0x10000000) /*!< Power interface reset */
#define RCC_APB1PRST_DACRST    ((uint32_t)0x20000000) /*!< DAC interface reset */
#define RCC_APB1PRST_OPARST    ((uint32_t)0x80000000) /*!< OPA interface reset */

/******************  Bit definition for RCC_AHBPCLKEN register  ******************/
#define RCC_AHBPCLKEN_DMAEN    ((uint32_t)0x00000001) /*!< DMA clock enable */
#define RCC_AHBPCLKEN_SRAMEN   ((uint32_t)0x00000004) /*!< SRAM interface clock enable */
#define RCC_AHBPCLKEN_FLITFEN  ((uint32_t)0x00000010) /*!< FLITF clock enable */
#define RCC_AHBPCLKEN_CRCEN    ((uint32_t)0x00000040) /*!< CRC clock enable */
#define RCC_AHBPCLKEN_RNGCEN   ((uint32_t)0x00000200) /*!< RNGC clock enable */
#define RCC_AHBPCLKEN_SACEN    ((uint32_t)0x00000800) /*!< SAC clock enable */
#define RCC_AHBPCLKEN_ADCEN    ((uint32_t)0x00001000) /*!< ADC clock enable */

/******************  Bit definition for RCC_APB2PCLKEN register  *****************/
#define RCC_APB2PCLKEN_AFIOEN   ((uint32_t)0x00000001) /*!< Alternate Function I/O clock enable */
#define RCC_APB2PCLKEN_IOPAEN   ((uint32_t)0x00000004) /*!< I/O port A clock enable */
#define RCC_APB2PCLKEN_IOPBEN   ((uint32_t)0x00000008) /*!< I/O port B clock enable */
#define RCC_APB2PCLKEN_IOPCEN   ((uint32_t)0x00000010) /*!< I/O port C clock enable */
#define RCC_APB2PCLKEN_IOPDEN   ((uint32_t)0x00000020) /*!< I/O port D clock enable */
#define RCC_APB2PCLKEN_TIM1EN   ((uint32_t)0x00000800) /*!< TIM1 Timer clock enable */
#define RCC_APB2PCLKEN_SPI1EN   ((uint32_t)0x00001000) /*!< SPI1 clock enable */
#define RCC_APB2PCLKEN_TIM8EN   ((uint32_t)0x00002000) /*!< TIM8 Timer clock enable */
#define RCC_APB2PCLKEN_USART1EN ((uint32_t)0x00004000) /*!< USART1 clock enable */
#define RCC_APB2PCLKEN_UART4EN  ((uint32_t)0x00020000) /*!< UART4 clock enable */
#define RCC_APB2PCLKEN_UART5EN  ((uint32_t)0x00040000) /*!< UART5 clock enable */
#define RCC_APB2PCLKEN_SPI2EN   ((uint32_t)0x00080000) /*!< SPI2 clock enable */

/*****************  Bit definition for RCC_APB1PCLKEN register  ******************/
#define RCC_APB1PCLKEN_TIM2EN     ((uint32_t)0x00000001) /*!< Timer 2 clock enabled*/
#define RCC_APB1PCLKEN_TIM3EN     ((uint32_t)0x00000002) /*!< Timer 3 clock enable */
#define RCC_APB1PCLKEN_TIM4EN     ((uint32_t)0x00000004) /*!< Timer 4 clock enable */
#define RCC_APB1PCLKEN_TIM5EN     ((uint32_t)0x00000008) /*!< Timer 5 clock enable */
#define RCC_APB1PCLKEN_TIM6EN     ((uint32_t)0x00000010) /*!< Timer 6 clock enable */
#define RCC_APB1PCLKEN_TIM7EN     ((uint32_t)0x00000020) /*!< Timer 7 clock enable */
#define RCC_APB1PCLKEN_COMPEN     ((uint32_t)0x00000040) /*!< COMP clock enable */
#define RCC_APB1PCLKEN_COMPFILTEN ((uint32_t)0x00000080) /*!< COMPFILT clock enable */
#define RCC_APB1PCLKEN_AFECEN     ((uint32_t)0x00000100) /*!< AFEC clock enable */
#define RCC_APB1PCLKEN_TIM9EN     ((uint32_t)0x00000200) /*!< Timer 9 clock enable */
#define RCC_APB1PCLKEN_TSCEN      ((uint32_t)0x00000400) /*!< TSC clock enable */
#define RCC_APB1PCLKEN_WWDGEN     ((uint32_t)0x00000800) /*!< Window Watchdog clock enable */
#define RCC_APB1PCLKEN_USART2EN   ((uint32_t)0x00020000) /*!< USART 2 clock enable */
#define RCC_APB1PCLKEN_USART3EN   ((uint32_t)0x00040000) /*!< USART 3 clock enable */
#define RCC_APB1PCLKEN_I2C1EN     ((uint32_t)0x00200000) /*!< I2C 1 clock enable */
#define RCC_APB1PCLKEN_I2C2EN     ((uint32_t)0x00400000) /*!< I2C 2 clock enable */
#define RCC_APB1PCLKEN_USBEN      ((uint32_t)0x00800000) /*!< USB Device clock enable */
#define RCC_APB1PCLKEN_CANEN      ((uint32_t)0x02000000) /*!< CAN clock enable */
#define RCC_APB1PCLKEN_PWREN      ((uint32_t)0x10000000) /*!< Power interface clock enable */
#define RCC_APB1PCLKEN_DACEN      ((uint32_t)0x20000000) /*!< DAC interface clock enable */
#define RCC_APB1PCLKEN_OPAMPEN    ((uint32_t)0x80000000) /*!< OPAMP interface clock enable */

/*******************  Bit definition for RCC_LDCTRL register  *******************/
#define RCC_LDCTRL_LSEEN ((uint32_t)0x00000001) /*!< External Low Speed oscillator enable */
#define RCC_LDCTRL_LSERD ((uint32_t)0x00000002) /*!< External Low Speed oscillator Ready */
#define RCC_LDCTRL_LSEBP ((uint32_t)0x00000004) /*!< External Low Speed oscillator Bypass */

#define RCC_LDCTRL_LSECLKSSEN ((uint32_t)0x00000008) /*!< LSE Security System enable */
#define RCC_LDCTRL_LSECLKSSF  ((uint32_t)0x00000010) /*!< LSE Security System failure detection */
#define RCC_LDCTRL_LSXSEL     ((uint32_t)0x00000020) /*!< LSXSEL bits (TSC clock source selection) */

#define RCC_LDCTRL_RTCSEL   ((uint32_t)0x00000300) /*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define RCC_LDCTRL_RTCSEL_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define RCC_LDCTRL_RTCSEL_1 ((uint32_t)0x00000200) /*!< Bit 1 */

/*!< RTC congiguration */
#define RCC_LDCTRL_RTCSEL_NOCLOCK ((uint32_t)0x00000000) /*!< No clock */
#define RCC_LDCTRL_RTCSEL_LSE     ((uint32_t)0x00000100) /*!< LSE oscillator clock used as RTC clock */
#define RCC_LDCTRL_RTCSEL_LSI     ((uint32_t)0x00000200) /*!< LSI oscillator clock used as RTC clock */
#define RCC_LDCTRL_RTCSEL_HSE     ((uint32_t)0x00000300) /*!< HSE oscillator clock divided by 32 used as RTC clock */

#define RCC_LDCTRL_RTCEN     ((uint32_t)0x00008000) /*!< RTC clock enable */
#define RCC_LDCTRL_LDSFTRST  ((uint32_t)0x00010000) /*!< Low power domain software reset  */
#define RCC_LDCTRL_BORRSTF   ((uint32_t)0x10000000) /*!< BOR reset flag */
#define RCC_LDCTRL_LDEMCRSTF ((uint32_t)0x40000000) /*!< Low power EMC reset flag */

/*******************  Bit definition for RCC_CTRLSTS register  ********************/
#define RCC_CTRLSTS_LSIEN    ((uint32_t)0x00000001) /*!< Internal Low Speed oscillator enable */
#define RCC_CTRLSTS_LSIRD    ((uint32_t)0x00000002) /*!< Internal Low Speed oscillator Ready */
#define RCC_CTRLSTS_MSIEN    ((uint32_t)0x00000004) /*!< Internal Multi Speed oscillator enable */
#define RCC_CTRLSTS_MSIRD    ((uint32_t)0x00000008) /*!< Internal Multi Speed oscillator Ready */

#define RCC_CTRLSTS_MSIRANGE   ((uint32_t)0x00000070) /*!< Internal Multi Speed oscillator Clock Range */
#define RCC_CTRLSTS_MSIRANGE_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define RCC_CTRLSTS_MSIRANGE_1 ((uint32_t)0x00000020) /*!< Bit 0 */
#define RCC_CTRLSTS_MSIRANGE_2 ((uint32_t)0x00000040) /*!< Bit 0 */

#define RCC_CTRLSTS_MSIRANGE_100KHz ((uint32_t)0x00000000) /*!< Internal Multi Speed oscillator output 100KHz */
#define RCC_CTRLSTS_MSIRANGE_200KHz ((uint32_t)0x00000010) /*!< Internal Multi Speed oscillator output 200KHz */
#define RCC_CTRLSTS_MSIRANGE_400KHz ((uint32_t)0x00000020) /*!< Internal Multi Speed oscillator output 400KHz */
#define RCC_CTRLSTS_MSIRANGE_800KHz ((uint32_t)0x00000030) /*!< Internal Multi Speed oscillator output 800KHz */
#define RCC_CTRLSTS_MSIRANGE_1MHz   ((uint32_t)0x00000040) /*!< Internal Multi Speed oscillator output 1MHz */
#define RCC_CTRLSTS_MSIRANGE_2MHz   ((uint32_t)0x00000050) /*!< Internal Multi Speed oscillator output 2MHz */
#define RCC_CTRLSTS_MSIRANGE_4MHz   ((uint32_t)0x00000060) /*!< Internal Multi Speed oscillator output 4MHz */

#define RCC_CTRLSTS_MSICAL   ((uint32_t)0x00007F80) /*!< Internal Multi Speed clock Calibration */
#define RCC_CTRLSTS_MSITRIM  ((uint32_t)0x007F8000) /*!< Internal Multi Speed clock trimming */
#define RCC_CTRLSTS_RAMRSTF  ((uint32_t)0x00800000) /*!< RAM reset flag */
#define RCC_CTRLSTS_RMRSTF   ((uint32_t)0x01000000) /*!< Remove reset flag */
#define RCC_CTRLSTS_MMURSTF  ((uint32_t)0x02000000) /*!< MMU reset flag */
#define RCC_CTRLSTS_PINRSTF  ((uint32_t)0x04000000) /*!< PIN reset flag */
#define RCC_CTRLSTS_PORRSTF  ((uint32_t)0x08000000) /*!< POR reset flag */
#define RCC_CTRLSTS_SFTRSTF  ((uint32_t)0x10000000) /*!< Software Reset flag */
#define RCC_CTRLSTS_IWDGRSTF ((uint32_t)0x20000000) /*!< Independent Watchdog reset flag */
#define RCC_CTRLSTS_WWDGRSTF ((uint32_t)0x40000000) /*!< Window watchdog reset flag */
#define RCC_CTRLSTS_LPWRRSTF ((uint32_t)0x80000000) /*!< Low-Power reset flag */

/*******************  Bit definition for RCC_AHBPRST register  ****************/
#define RCC_AHBRST_RNGCRST   ((uint32_t)0x00000200) /*!< RNGC reset */
#define RCC_AHBRST_SACRST    ((uint32_t)0x00000800) /*!< SAC reset */
#define RCC_AHBRST_ADCRST    ((uint32_t)0x00001000) /*!< ADC reset */

/*******************  Bit definition for RCC_CFG2 register  ******************/
/*!< ADCHPRE configuration */
#define RCC_CFG2_ADCHPRES   ((uint32_t)0x0000000F) /*!< ADCHPRE[3:0] bits */
#define RCC_CFG2_ADCHPRES_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define RCC_CFG2_ADCHPRES_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define RCC_CFG2_ADCHPRES_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define RCC_CFG2_ADCHPRES_3 ((uint32_t)0x00000008) /*!< Bit 3 */

#define RCC_CFG2_ADCHPRES_DIV1   ((uint32_t)0x00000000) /*!< HCLK clock divided by 1 */
#define RCC_CFG2_ADCHPRES_DIV2   ((uint32_t)0x00000001) /*!< HCLK clock divided by 2 */
#define RCC_CFG2_ADCHPRES_DIV4   ((uint32_t)0x00000002) /*!< HCLK clock divided by 4 */
#define RCC_CFG2_ADCHPRES_DIV6   ((uint32_t)0x00000003) /*!< HCLK clock divided by 6 */
#define RCC_CFG2_ADCHPRES_DIV8   ((uint32_t)0x00000004) /*!< HCLK clock divided by 8 */
#define RCC_CFG2_ADCHPRES_DIV10  ((uint32_t)0x00000005) /*!< HCLK clock divided by 10 */
#define RCC_CFG2_ADCHPRES_DIV12  ((uint32_t)0x00000006) /*!< HCLK clock divided by 12 */
#define RCC_CFG2_ADCHPRES_DIV16  ((uint32_t)0x00000007) /*!< HCLK clock divided by 16 */
#define RCC_CFG2_ADCHPRES_DIV32  ((uint32_t)0x00000008) /*!< HCLK clock divided by 32 */
#define RCC_CFG2_ADCHPRES_OTHERS ((uint32_t)0x00000008) /*!< HCLK clock divided by 32 */

/*!< ADCPLLPRES configuration */
#define RCC_CFG2_ADCPLLPRES   ((uint32_t)0x000001F0) /*!< ADCPLLPRES[4:0] bits */
#define RCC_CFG2_ADCPLLPRES_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define RCC_CFG2_ADCPLLPRES_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define RCC_CFG2_ADCPLLPRES_2 ((uint32_t)0x00000040) /*!< Bit 2 */
#define RCC_CFG2_ADCPLLPRES_3 ((uint32_t)0x00000080) /*!< Bit 3 */
#define RCC_CFG2_ADCPLLPRES_4 ((uint32_t)0x00000100) /*!< Bit 4 */

#define RCC_CFG2_ADCPLLCLK_DISABLE  ((uint32_t)0xFFFFFEFF) /*!< ADC PLL clock Disable */
#define RCC_CFG2_ADCPLLPRES_DIV1    ((uint32_t)0x00000100) /*!< PLL clock divided by 1 */
#define RCC_CFG2_ADCPLLPRES_DIV2    ((uint32_t)0x00000110) /*!< PLL clock divided by 2 */
#define RCC_CFG2_ADCPLLPRES_DIV4    ((uint32_t)0x00000120) /*!< PLL clock divided by 4 */
#define RCC_CFG2_ADCPLLPRES_DIV6    ((uint32_t)0x00000130) /*!< PLL clock divided by 6 */
#define RCC_CFG2_ADCPLLPRES_DIV8    ((uint32_t)0x00000140) /*!< PLL clock divided by 8 */
#define RCC_CFG2_ADCPLLPRES_DIV10   ((uint32_t)0x00000150) /*!< PLL clock divided by 10 */
#define RCC_CFG2_ADCPLLPRES_DIV12   ((uint32_t)0x00000160) /*!< PLL clock divided by 12 */
#define RCC_CFG2_ADCPLLPRES_DIV16   ((uint32_t)0x00000170) /*!< PLL clock divided by 16 */
#define RCC_CFG2_ADCPLLPRES_DIV32   ((uint32_t)0x00000180) /*!< PLL clock divided by 32 */
#define RCC_CFG2_ADCPLLPRES_DIV64   ((uint32_t)0x00000190) /*!< PLL clock divided by 64 */
#define RCC_CFG2_ADCPLLPRES_DIV128  ((uint32_t)0x000001A0) /*!< PLL clock divided by 128 */
#define RCC_CFG2_ADCPLLPRES_DIV256  ((uint32_t)0x000001B0) /*!< PLL clock divided by 256 */
#define RCC_CFG2_ADCPLLPRES_DIV256N ((uint32_t)0x000001C0) /*!< PLL clock divided by 256 */

/*!< ADC1MPRE configuration */
#define RCC_CFG2_ADC1MPRES   ((uint32_t)0x0001F000) /*!< ADC1MPRE[4:0] bits */
#define RCC_CFG2_ADC1MPRES_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define RCC_CFG2_ADC1MPRES_1 ((uint32_t)0x00002000) /*!< Bit 1 */
#define RCC_CFG2_ADC1MPRES_2 ((uint32_t)0x00004000) /*!< Bit 2 */
#define RCC_CFG2_ADC1MPRES_3 ((uint32_t)0x00008000) /*!< Bit 3 */
#define RCC_CFG2_ADC1MPRES_4 ((uint32_t)0x00010000) /*!< Bit 4 */

#define RCC_CFG2_ADC1MPRES_DIV1  ((uint32_t)0x00000000) /*!< ADC1M source clock is divided by 1 */
#define RCC_CFG2_ADC1MPRES_DIV2  ((uint32_t)0x00001000) /*!< ADC1M source clock is divided by 2 */
#define RCC_CFG2_ADC1MPRES_DIV3  ((uint32_t)0x00002000) /*!< ADC1M source clock is divided by 3 */
#define RCC_CFG2_ADC1MPRES_DIV4  ((uint32_t)0x00003000) /*!< ADC1M source clock is divided by 4 */
#define RCC_CFG2_ADC1MPRES_DIV5  ((uint32_t)0x00004000) /*!< ADC1M source clock is divided by 5 */
#define RCC_CFG2_ADC1MPRES_DIV6  ((uint32_t)0x00005000) /*!< ADC1M source clock is divided by 6 */
#define RCC_CFG2_ADC1MPRES_DIV7  ((uint32_t)0x00006000) /*!< ADC1M source clock is divided by 7 */
#define RCC_CFG2_ADC1MPRES_DIV8  ((uint32_t)0x00007000) /*!< ADC1M source clock is divided by 8 */
#define RCC_CFG2_ADC1MPRES_DIV9  ((uint32_t)0x00008000) /*!< ADC1M source clock is divided by 9 */
#define RCC_CFG2_ADC1MPRES_DIV10 ((uint32_t)0x00009000) /*!< ADC1M source clock is divided by 10 */
#define RCC_CFG2_ADC1MPRES_DIV11 ((uint32_t)0x0000A000) /*!< ADC1M source clock is divided by 11 */
#define RCC_CFG2_ADC1MPRES_DIV12 ((uint32_t)0x0000B000) /*!< ADC1M source clock is divided by 12 */
#define RCC_CFG2_ADC1MPRES_DIV13 ((uint32_t)0x0000C000) /*!< ADC1M source clock is divided by 13 */
#define RCC_CFG2_ADC1MPRES_DIV14 ((uint32_t)0x0000D000) /*!< ADC1M source clock is divided by 14 */
#define RCC_CFG2_ADC1MPRES_DIV15 ((uint32_t)0x0000E000) /*!< ADC1M source clock is divided by 15 */
#define RCC_CFG2_ADC1MPRES_DIV16 ((uint32_t)0x0000F000) /*!< ADC1M source clock is divided by 16 */
#define RCC_CFG2_ADC1MPRES_DIV17 ((uint32_t)0x00010000) /*!< ADC1M source clock is divided by 17 */
#define RCC_CFG2_ADC1MPRES_DIV18 ((uint32_t)0x00011000) /*!< ADC1M source clock is divided by 18 */
#define RCC_CFG2_ADC1MPRES_DIV19 ((uint32_t)0x00012000) /*!< ADC1M source clock is divided by 19 */
#define RCC_CFG2_ADC1MPRES_DIV20 ((uint32_t)0x00013000) /*!< ADC1M source clock is divided by 20 */
#define RCC_CFG2_ADC1MPRES_DIV21 ((uint32_t)0x00014000) /*!< ADC1M source clock is divided by 21 */
#define RCC_CFG2_ADC1MPRES_DIV22 ((uint32_t)0x00015000) /*!< ADC1M source clock is divided by 22 */
#define RCC_CFG2_ADC1MPRES_DIV23 ((uint32_t)0x00016000) /*!< ADC1M source clock is divided by 23 */
#define RCC_CFG2_ADC1MPRES_DIV24 ((uint32_t)0x00017000) /*!< ADC1M source clock is divided by 24 */
#define RCC_CFG2_ADC1MPRES_DIV25 ((uint32_t)0x00018000) /*!< ADC1M source clock is divided by 25 */
#define RCC_CFG2_ADC1MPRES_DIV26 ((uint32_t)0x00019000) /*!< ADC1M source clock is divided by 26 */
#define RCC_CFG2_ADC1MPRES_DIV27 ((uint32_t)0x0001A000) /*!< ADC1M source clock is divided by 27 */
#define RCC_CFG2_ADC1MPRES_DIV28 ((uint32_t)0x0001B000) /*!< ADC1M source clock is divided by 28 */
#define RCC_CFG2_ADC1MPRES_DIV29 ((uint32_t)0x0001C000) /*!< ADC1M source clock is divided by 29 */
#define RCC_CFG2_ADC1MPRES_DIV30 ((uint32_t)0x0001D000) /*!< ADC1M source clock is divided by 30 */
#define RCC_CFG2_ADC1MPRES_DIV31 ((uint32_t)0x0001E000) /*!< ADC1M source clock is divided by 31 */
#define RCC_CFG2_ADC1MPRES_DIV32 ((uint32_t)0x0001F000) /*!< ADC1M source clock is divided by 32 */

/*!< ADC1MSEL configuration */
#define RCC_CFG2_ADC1MSEL ((uint32_t)0x00020000) /*!< ADC1M clock source select */

#define RCC_CFG2_ADC1MSEL_HSI ((uint32_t)0x00000000) /*!< HSI clock selected as ADC1M input clock */
#define RCC_CFG2_ADC1MSEL_HSE ((uint32_t)0x00020000) /*!< HSE clock selected as ADC1M input clock */

/*!< RNGCPRE configuration */
#define RCC_CFG2_RNGCPRES   ((uint32_t)0x1F000000) /*!< RNGCPRE[4:0] bits */
#define RCC_CFG2_RNGCPRES_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define RCC_CFG2_RNGCPRES_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define RCC_CFG2_RNGCPRES_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define RCC_CFG2_RNGCPRES_3 ((uint32_t)0x08000000) /*!< Bit 3 */
#define RCC_CFG2_RNGCPRES_4 ((uint32_t)0x10000000) /*!< Bit 4 */

#define RCC_CFG2_RNGCPRES_DIV1  ((uint32_t)0x00000000) /*!< SYSCLK source clock is divided by 1 */
#define RCC_CFG2_RNGCPRES_DIV2  ((uint32_t)0x01000000) /*!< SYSCLK source clock is divided by 2 */
#define RCC_CFG2_RNGCPRES_DIV3  ((uint32_t)0x02000000) /*!< SYSCLK source clock is divided by 3 */
#define RCC_CFG2_RNGCPRES_DIV4  ((uint32_t)0x03000000) /*!< SYSCLK source clock is divided by 4 */
#define RCC_CFG2_RNGCPRES_DIV5  ((uint32_t)0x04000000) /*!< SYSCLK source clock is divided by 5 */
#define RCC_CFG2_RNGCPRES_DIV6  ((uint32_t)0x05000000) /*!< SYSCLK source clock is divided by 6 */
#define RCC_CFG2_RNGCPRES_DIV7  ((uint32_t)0x06000000) /*!< SYSCLK source clock is divided by 7 */
#define RCC_CFG2_RNGCPRES_DIV8  ((uint32_t)0x07000000) /*!< SYSCLK source clock is divided by 8 */
#define RCC_CFG2_RNGCPRES_DIV9  ((uint32_t)0x08000000) /*!< SYSCLK source clock is divided by 9 */
#define RCC_CFG2_RNGCPRES_DIV10 ((uint32_t)0x09000000) /*!< SYSCLK source clock is divided by 10 */
#define RCC_CFG2_RNGCPRES_DIV11 ((uint32_t)0x0A000000) /*!< SYSCLK source clock is divided by 11 */
#define RCC_CFG2_RNGCPRES_DIV12 ((uint32_t)0x0B000000) /*!< SYSCLK source clock is divided by 12 */
#define RCC_CFG2_RNGCPRES_DIV13 ((uint32_t)0x0C000000) /*!< SYSCLK source clock is divided by 13 */
#define RCC_CFG2_RNGCPRES_DIV14 ((uint32_t)0x0D000000) /*!< SYSCLK source clock is divided by 14 */
#define RCC_CFG2_RNGCPRES_DIV15 ((uint32_t)0x0E000000) /*!< SYSCLK source clock is divided by 15 */
#define RCC_CFG2_RNGCPRES_DIV16 ((uint32_t)0x0F000000) /*!< SYSCLK source clock is divided by 16 */
#define RCC_CFG2_RNGCPRES_DIV17 ((uint32_t)0x10000000) /*!< SYSCLK source clock is divided by 17 */
#define RCC_CFG2_RNGCPRES_DIV18 ((uint32_t)0x11000000) /*!< SYSCLK source clock is divided by 18 */
#define RCC_CFG2_RNGCPRES_DIV19 ((uint32_t)0x12000000) /*!< SYSCLK source clock is divided by 19 */
#define RCC_CFG2_RNGCPRES_DIV20 ((uint32_t)0x13000000) /*!< SYSCLK source clock is divided by 20 */
#define RCC_CFG2_RNGCPRES_DIV21 ((uint32_t)0x14000000) /*!< SYSCLK source clock is divided by 21 */
#define RCC_CFG2_RNGCPRES_DIV22 ((uint32_t)0x15000000) /*!< SYSCLK source clock is divided by 22 */
#define RCC_CFG2_RNGCPRES_DIV23 ((uint32_t)0x16000000) /*!< SYSCLK source clock is divided by 23 */
#define RCC_CFG2_RNGCPRES_DIV24 ((uint32_t)0x17000000) /*!< SYSCLK source clock is divided by 24 */
#define RCC_CFG2_RNGCPRES_DIV25 ((uint32_t)0x18000000) /*!< SYSCLK source clock is divided by 25 */
#define RCC_CFG2_RNGCPRES_DIV26 ((uint32_t)0x19000000) /*!< SYSCLK source clock is divided by 26 */
#define RCC_CFG2_RNGCPRES_DIV27 ((uint32_t)0x1A000000) /*!< SYSCLK source clock is divided by 27 */
#define RCC_CFG2_RNGCPRES_DIV28 ((uint32_t)0x1B000000) /*!< SYSCLK source clock is divided by 28 */
#define RCC_CFG2_RNGCPRES_DIV29 ((uint32_t)0x1C000000) /*!< SYSCLK source clock is divided by 29 */
#define RCC_CFG2_RNGCPRES_DIV30 ((uint32_t)0x1D000000) /*!< SYSCLK source clock is divided by 30 */
#define RCC_CFG2_RNGCPRES_DIV31 ((uint32_t)0x1E000000) /*!< SYSCLK source clock is divided by 31 */
#define RCC_CFG2_RNGCPRES_DIV32 ((uint32_t)0x1F000000) /*!< SYSCLK source clock is divided by 32 */

/*!< TIMCLK_SEL configuration */
#define RCC_CFG2_TIMCLKSEL ((uint32_t)0x20000000) /*!< Timer1/8 clock source select */

#define RCC_CFG2_TIMCLKSEL_TIM18CLK ((uint32_t)0x00000000) /*!< Timer1/8 clock selected as tim1/8_clk input clock */
#define RCC_CFG2_TIMCLKSEL_SYSCLK   ((uint32_t)0x20000000) /*!< Timer1/8 clock selected as sysclk input clock */

/*******************  Bit definition for RCC_CFG3 register  ******************/
/*!< UCDREN configuration */
#define RCC_CFG3_UCDREN ((uint32_t)0x00000080) /*!< UCDR enable */

#define RCC_CFG3_UCDREN_ENABLE  ((uint32_t)0x00000080) /*!< UCDREN enable */
#define RCC_CFG3_UCDREN_DISABLE ((uint32_t)0x00000000) /*!< UCDREN disable */

/*!< USBXTALESS configuration */
#define RCC_CFG3_USBXTALESS ((uint32_t)0x00000100) /*!< UCDR enable */

#define RCC_CFG3_USBXTALESS_LESSMODE ((uint32_t)0x00000100) /*!< USB Crystalless mode */
#define RCC_CFG3_USBXTALESS_MODE     ((uint32_t)0x00000000) /*!< USB Crystal mode */

/*!< UCDR300MSEL configuration */
#define RCC_CFG3_UCDR300MSEL ((uint32_t)0x00000200) /*!< UCDR 300M Clock source */

#define RCC_CFG3_UCDR300MSEL_PLLVCO  ((uint32_t)0x00000200) /*!< PLL VCO selected as UCDR 300M Clock source */
#define RCC_CFG3_UCDR300MSEL_OSC300M ((uint32_t)0x00000000) /*!< OSC300M selected as UCDR 300M Clock source */

/*!< TRNG1MPRE configuration */
#define RCC_CFG3_TRNG1MPRES   ((uint32_t)0x0000F800) /*!< TRNG1MPRE[4:0] bits */
#define RCC_CFG3_TRNG1MPRES_0 ((uint32_t)0x00000800) /*!< Bit 0 */
#define RCC_CFG3_TRNG1MPRES_1 ((uint32_t)0x00001000) /*!< Bit 1 */
#define RCC_CFG3_TRNG1MPRES_2 ((uint32_t)0x00002000) /*!< Bit 2 */
#define RCC_CFG3_TRNG1MPRES_3 ((uint32_t)0x00004000) /*!< Bit 3 */
#define RCC_CFG3_TRNG1MPRES_4 ((uint32_t)0x00008000) /*!< Bit 4 */

#define RCC_CFG3_TRNG1MPRES_VAL2  ((uint32_t)0x00000800) /*!< TRNG 1M source clock is divided by 2 */
#define RCC_CFG3_TRNG1MPRES_VAL3  ((uint32_t)0x00001000) /*!< TRNG 1M source clock is divided by 4 */
#define RCC_CFG3_TRNG1MPRES_VAL4  ((uint32_t)0x00001800) /*!< TRNG 1M source clock is divided by 6 */
#define RCC_CFG3_TRNG1MPRES_VAL5  ((uint32_t)0x00002000) /*!< TRNG 1M source clock is divided by 8 */
#define RCC_CFG3_TRNG1MPRES_VAL6  ((uint32_t)0x00002800) /*!< TRNG 1M source clock is divided by 10 */
#define RCC_CFG3_TRNG1MPRES_VAL7  ((uint32_t)0x00003000) /*!< TRNG 1M source clock is divided by 12 */
#define RCC_CFG3_TRNG1MPRES_VAL8  ((uint32_t)0x00003800) /*!< TRNG 1M source clock is divided by 14 */
#define RCC_CFG3_TRNG1MPRES_VAL9  ((uint32_t)0x00004000) /*!< TRNG 1M source clock is divided by 16 */
#define RCC_CFG3_TRNG1MPRES_VAL10 ((uint32_t)0x00004800) /*!< TRNG 1M source clock is divided by 18 */
#define RCC_CFG3_TRNG1MPRES_VAL11 ((uint32_t)0x00005000) /*!< TRNG 1M source clock is divided by 20 */
#define RCC_CFG3_TRNG1MPRES_VAL12 ((uint32_t)0x00005800) /*!< TRNG 1M source clock is divided by 22 */
#define RCC_CFG3_TRNG1MPRES_VAL13 ((uint32_t)0x00006000) /*!< TRNG 1M source clock is divided by 24 */
#define RCC_CFG3_TRNG1MPRES_VAL14 ((uint32_t)0x00006800) /*!< TRNG 1M source clock is divided by 26 */
#define RCC_CFG3_TRNG1MPRES_VAL15 ((uint32_t)0x00007000) /*!< TRNG 1M source clock is divided by 28 */
#define RCC_CFG3_TRNG1MPRES_VAL16 ((uint32_t)0x00007800) /*!< TRNG 1M source clock is divided by 30 */
#define RCC_CFG3_TRNG1MPRES_VAL17 ((uint32_t)0x00008000) /*!< TRNG 1M source clock is divided by 32 */
#define RCC_CFG3_TRNG1MPRES_VAL18 ((uint32_t)0x00008800) /*!< TRNG 1M source clock is divided by 34 */
#define RCC_CFG3_TRNG1MPRES_VAL19 ((uint32_t)0x00009000) /*!< TRNG 1M source clock is divided by 36 */
#define RCC_CFG3_TRNG1MPRES_VAL20 ((uint32_t)0x00009800) /*!< TRNG 1M source clock is divided by 38 */
#define RCC_CFG3_TRNG1MPRES_VAL21 ((uint32_t)0x0000A000) /*!< TRNG 1M source clock is divided by 40 */
#define RCC_CFG3_TRNG1MPRES_VAL22 ((uint32_t)0x0000A800) /*!< TRNG 1M source clock is divided by 42 */
#define RCC_CFG3_TRNG1MPRES_VAL23 ((uint32_t)0x0000B000) /*!< TRNG 1M source clock is divided by 44 */
#define RCC_CFG3_TRNG1MPRES_VAL24 ((uint32_t)0x0000B800) /*!< TRNG 1M source clock is divided by 46 */
#define RCC_CFG3_TRNG1MPRES_VAL25 ((uint32_t)0x0000C000) /*!< TRNG 1M source clock is divided by 48 */
#define RCC_CFG3_TRNG1MPRES_VAL26 ((uint32_t)0x0000C800) /*!< TRNG 1M source clock is divided by 50 */
#define RCC_CFG3_TRNG1MPRES_VAL27 ((uint32_t)0x0000D000) /*!< TRNG 1M source clock is divided by 52 */
#define RCC_CFG3_TRNG1MPRES_VAL28 ((uint32_t)0x0000D800) /*!< TRNG 1M source clock is divided by 54 */
#define RCC_CFG3_TRNG1MPRES_VAL29 ((uint32_t)0x0000E000) /*!< TRNG 1M source clock is divided by 56 */
#define RCC_CFG3_TRNG1MPRES_VAL30 ((uint32_t)0x0000E800) /*!< TRNG 1M source clock is divided by 58 */
#define RCC_CFG3_TRNG1MPRES_VAL31 ((uint32_t)0x0000F000) /*!< TRNG 1M source clock is divided by 60 */
#define RCC_CFG3_TRNG1MPRES_VAL32 ((uint32_t)0x0000F800) /*!< TRNG 1M source clock is divided by 62 */

/*!< TRNG1MSEL configuration */
#define RCC_CFG3_TRNG1MSEL ((uint32_t)0x00020000) /*!< TRNG_1M clock source select */

#define RCC_CFG3_TRNG1MSEL_HSI ((uint32_t)0x00000000) /*!< HSI clock selected as TRNG_1M input clock */
#define RCC_CFG3_TRNG1MSEL_HSE ((uint32_t)0x00020000) /*!< HSE clock selected as TRNG_1M input clock */

/*!< TRNG1MEN configuration */
#define RCC_CFG3_TRNG1MEN ((uint32_t)0x00040000) /*!< TRNG_1M clock enable */

#define RCC_CFG3_TRNG1MEN_DISABLE ((uint32_t)0x00000000) /*!< TRNG_1M clock disable */
#define RCC_CFG3_TRNG1MEN_ENABLE  ((uint32_t)0x00040000) /*!< TRNG_1M clock enable */

/*******************  Bit definition for RCC_RDCTRL register  ******************/
/*!< LPTIMSEL congiguration */
#define RCC_RDCTRL_LPTIMSEL   ((uint32_t)0x00000007) /*!< LPTIMSEL[2:0] bits (LPTIM clock source selection) */
#define RCC_RDCTRL_LPTIMSEL_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define RCC_RDCTRL_LPTIMSEL_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define RCC_RDCTRL_LPTIMSEL_2 ((uint32_t)0x00000004) /*!< Bit 2 */

#define RCC_RDCTRL_LPTIMSEL_APB1  ((uint32_t)0x00000000) /*!< APB1 clock used as LPTIM clock */
#define RCC_RDCTRL_LPTIMSEL_LSI   ((uint32_t)0x00000001) /*!< LSI oscillator clock used as LPTIM clock */
#define RCC_RDCTRL_LPTIMSEL_HSI   ((uint32_t)0x00000002) /*!< HSI oscillator clock used as LPTIM clock */
#define RCC_RDCTRL_LPTIMSEL_LSE   ((uint32_t)0x00000003) /*!< LSE oscillator clock used as LPTIM clock */
#define RCC_RDCTRL_LPTIMSEL_COMP1 ((uint32_t)0x00000004) /*!< COMP1 output used as LPTIM clock */
#define RCC_RDCTRL_LPTIMSEL_COMP2 ((uint32_t)0x00000005) /*!< COMP1 output used as LPTIM clock */

/*!< LPUARTSEL congiguration */
#define RCC_RDCTRL_LPUARTSEL   ((uint32_t)0x00000018) /*!< LPUARTSEL[1:0] bits (LPUART clock source selection) */
#define RCC_RDCTRL_LPUARTSEL_0 ((uint32_t)0x00000008) /*!< Bit 0 */
#define RCC_RDCTRL_LPUARTSEL_1 ((uint32_t)0x00000010) /*!< Bit 1 */

#define RCC_RDCTRL_LPUARTSEL_APB1   ((uint32_t)0x00000000) /*!< APB1 clock used as LPUART clock */
#define RCC_RDCTRL_LPUARTSEL_SYSCLK ((uint32_t)0x00000008) /*!< SYSCLK used as LPUART clock */
#define RCC_RDCTRL_LPUARTSEL_HSI    ((uint32_t)0x00000010) /*!< HSI oscillator clock used as LPUART clock */
#define RCC_RDCTRL_LPUARTSEL_LSE    ((uint32_t)0x00000018) /*!< LSE oscillator clock used as LPUART clock */

#define RCC_RDCTRL_LPTIMEN   ((uint32_t)0x00000040) /*!< LPTIM clock enable */
#define RCC_RDCTRL_LPUARTEN  ((uint32_t)0x00000080) /*!< LPUART clock enable */
#define RCC_RDCTRL_LCDEN     ((uint32_t)0x00000100) /*!< LCD clock enable */

#define RCC_RDCTRL_LPTIMRST  ((uint32_t)0x00000400) /*!< LPTIM reset */
#define RCC_RDCTRL_LPUARTRST ((uint32_t)0x00000800) /*!< LPUART reset */
#define RCC_RDCTRL_LCDRST    ((uint32_t)0x00001000) /*!< LCD reset */


/*******************  Bit definition for RCC_PLLHSIPRE register  ******************/
/*!< PLLHSIPRE configuration */
#define RCC_PLLHSIPRE_PLLHSIPRE ((uint32_t)0x00000001) /*!< HSI divider for PLL entry */

#define RCC_PLLHSIPRE_PLLHSIPRE_HSI      ((uint32_t)0x00000000) /*!< HSI clock not divided for PLL entry */
#define RCC_PLLHSIPRE_PLLHSIPRE_HSI_DIV2 ((uint32_t)0x00000001) /*!< HSI clock divided by 2 for PLL entry */

/*!< PLLSRCDIV configuration */
#define RCC_PLLHSIPRE_PLLSRCDIV ((uint32_t)0x00000002) /*!< PLL source clock for PLL entry */

#define RCC_PLLHSIPRE_PLLSRCDIV_DISABLE ((uint32_t)0x00000000) /*!< PLL source clock not divided for PLL entry */
#define RCC_PLLHSIPRE_PLLSRCDIV_ENABLE  ((uint32_t)0x00000002) /*!< PLL source clock divided by 2 for PLL entry */

/*******************  Bit definition for RCC_SRAM_CTRLSTS register  ******************/
#define RCC_SRAM_CTRLSTS_ERR1EN    ((uint32_t)0x00000001) /*!< SRAM1 Parity Error Interrupt Enable */
#define RCC_SRAM_CTRLSTS_ERR1RSTEN ((uint32_t)0x00000002) /*!< SRAM1 Parity Error Reset Enable */
#define RCC_SRAM_CTRLSTS_ERR1STS   ((uint32_t)0x00000004) /*!< SRAM1 Parity Error Status */
#define RCC_SRAM_CTRLSTS_ERR2EN    ((uint32_t)0x00000008) /*!< SRAM2 Parity Error Interrupt Enable */
#define RCC_SRAM_CTRLSTS_ERR2RSTEN ((uint32_t)0x00000010) /*!< SRAM2 Parity Error Reset Enable */
#define RCC_SRAM_CTRLSTS_ERR2STS   ((uint32_t)0x00000020) /*!< SRAM2 Parity Error Status */

/******************************************************************************/
/*                                                                            */
/*                               SystemTick                                   */
/*                                                                            */
/******************************************************************************/

/*****************  Bit definition for SysTick_CTRL register  *****************/
#define SysTick_CTRL_ENABLE    ((uint32_t)0x00000001) /*!< Counter enable */
#define SysTick_CTRL_TICKINT   ((uint32_t)0x00000002) /*!< Counting down to 0 pends the SysTick handler */
#define SysTick_CTRL_CLKSOURCE ((uint32_t)0x00000004) /*!< Clock source */
#define SysTick_CTRL_COUNTFLAG ((uint32_t)0x00010000) /*!< Count Flag */

/*****************  Bit definition for SysTick_LOAD register  *****************/
#define SysTick_LOAD_RELOAD                                                                                            \
    ((uint32_t)0x00FFFFFF) /*!< Value to load into the SysTick Current Value Register when the counter reaches 0 */

/*****************  Bit definition for SysTick_VAL register  ******************/
#define SysTick_VAL_CURRENT ((uint32_t)0x00FFFFFF) /*!< Current value at the time the register is accessed */

/*****************  Bit definition for SysTick_CALIB register  ****************/
#define SysTick_CALIB_TENMS ((uint32_t)0x00FFFFFF) /*!< Reload value to use for 10ms timing */
#define SysTick_CALIB_SKEW  ((uint32_t)0x40000000) /*!< Calibration value is not exactly 10 ms */
#define SysTick_CALIB_NOREF ((uint32_t)0x80000000) /*!< The reference clock is not provided */

/******************************************************************************/
/*                                                                            */
/*                  Nested Vectored Interrupt Controller                      */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for NVIC_ISER register  *******************/
#define NVIC_ISER_SETENA    ((uint32_t)0xFFFFFFFF) /*!< Interrupt set enable bits */
#define NVIC_ISER_SETENA_0  ((uint32_t)0x00000001) /*!< bit 0 */
#define NVIC_ISER_SETENA_1  ((uint32_t)0x00000002) /*!< bit 1 */
#define NVIC_ISER_SETENA_2  ((uint32_t)0x00000004) /*!< bit 2 */
#define NVIC_ISER_SETENA_3  ((uint32_t)0x00000008) /*!< bit 3 */
#define NVIC_ISER_SETENA_4  ((uint32_t)0x00000010) /*!< bit 4 */
#define NVIC_ISER_SETENA_5  ((uint32_t)0x00000020) /*!< bit 5 */
#define NVIC_ISER_SETENA_6  ((uint32_t)0x00000040) /*!< bit 6 */
#define NVIC_ISER_SETENA_7  ((uint32_t)0x00000080) /*!< bit 7 */
#define NVIC_ISER_SETENA_8  ((uint32_t)0x00000100) /*!< bit 8 */
#define NVIC_ISER_SETENA_9  ((uint32_t)0x00000200) /*!< bit 9 */
#define NVIC_ISER_SETENA_10 ((uint32_t)0x00000400) /*!< bit 10 */
#define NVIC_ISER_SETENA_11 ((uint32_t)0x00000800) /*!< bit 11 */
#define NVIC_ISER_SETENA_12 ((uint32_t)0x00001000) /*!< bit 12 */
#define NVIC_ISER_SETENA_13 ((uint32_t)0x00002000) /*!< bit 13 */
#define NVIC_ISER_SETENA_14 ((uint32_t)0x00004000) /*!< bit 14 */
#define NVIC_ISER_SETENA_15 ((uint32_t)0x00008000) /*!< bit 15 */
#define NVIC_ISER_SETENA_16 ((uint32_t)0x00010000) /*!< bit 16 */
#define NVIC_ISER_SETENA_17 ((uint32_t)0x00020000) /*!< bit 17 */
#define NVIC_ISER_SETENA_18 ((uint32_t)0x00040000) /*!< bit 18 */
#define NVIC_ISER_SETENA_19 ((uint32_t)0x00080000) /*!< bit 19 */
#define NVIC_ISER_SETENA_20 ((uint32_t)0x00100000) /*!< bit 20 */
#define NVIC_ISER_SETENA_21 ((uint32_t)0x00200000) /*!< bit 21 */
#define NVIC_ISER_SETENA_22 ((uint32_t)0x00400000) /*!< bit 22 */
#define NVIC_ISER_SETENA_23 ((uint32_t)0x00800000) /*!< bit 23 */
#define NVIC_ISER_SETENA_24 ((uint32_t)0x01000000) /*!< bit 24 */
#define NVIC_ISER_SETENA_25 ((uint32_t)0x02000000) /*!< bit 25 */
#define NVIC_ISER_SETENA_26 ((uint32_t)0x04000000) /*!< bit 26 */
#define NVIC_ISER_SETENA_27 ((uint32_t)0x08000000) /*!< bit 27 */
#define NVIC_ISER_SETENA_28 ((uint32_t)0x10000000) /*!< bit 28 */
#define NVIC_ISER_SETENA_29 ((uint32_t)0x20000000) /*!< bit 29 */
#define NVIC_ISER_SETENA_30 ((uint32_t)0x40000000) /*!< bit 30 */
#define NVIC_ISER_SETENA_31 ((uint32_t)0x80000000) /*!< bit 31 */

/******************  Bit definition for NVIC_ICER register  *******************/
#define NVIC_ICER_CLRENA    ((uint32_t)0xFFFFFFFF) /*!< Interrupt clear-enable bits */
#define NVIC_ICER_CLRENA_0  ((uint32_t)0x00000001) /*!< bit 0 */
#define NVIC_ICER_CLRENA_1  ((uint32_t)0x00000002) /*!< bit 1 */
#define NVIC_ICER_CLRENA_2  ((uint32_t)0x00000004) /*!< bit 2 */
#define NVIC_ICER_CLRENA_3  ((uint32_t)0x00000008) /*!< bit 3 */
#define NVIC_ICER_CLRENA_4  ((uint32_t)0x00000010) /*!< bit 4 */
#define NVIC_ICER_CLRENA_5  ((uint32_t)0x00000020) /*!< bit 5 */
#define NVIC_ICER_CLRENA_6  ((uint32_t)0x00000040) /*!< bit 6 */
#define NVIC_ICER_CLRENA_7  ((uint32_t)0x00000080) /*!< bit 7 */
#define NVIC_ICER_CLRENA_8  ((uint32_t)0x00000100) /*!< bit 8 */
#define NVIC_ICER_CLRENA_9  ((uint32_t)0x00000200) /*!< bit 9 */
#define NVIC_ICER_CLRENA_10 ((uint32_t)0x00000400) /*!< bit 10 */
#define NVIC_ICER_CLRENA_11 ((uint32_t)0x00000800) /*!< bit 11 */
#define NVIC_ICER_CLRENA_12 ((uint32_t)0x00001000) /*!< bit 12 */
#define NVIC_ICER_CLRENA_13 ((uint32_t)0x00002000) /*!< bit 13 */
#define NVIC_ICER_CLRENA_14 ((uint32_t)0x00004000) /*!< bit 14 */
#define NVIC_ICER_CLRENA_15 ((uint32_t)0x00008000) /*!< bit 15 */
#define NVIC_ICER_CLRENA_16 ((uint32_t)0x00010000) /*!< bit 16 */
#define NVIC_ICER_CLRENA_17 ((uint32_t)0x00020000) /*!< bit 17 */
#define NVIC_ICER_CLRENA_18 ((uint32_t)0x00040000) /*!< bit 18 */
#define NVIC_ICER_CLRENA_19 ((uint32_t)0x00080000) /*!< bit 19 */
#define NVIC_ICER_CLRENA_20 ((uint32_t)0x00100000) /*!< bit 20 */
#define NVIC_ICER_CLRENA_21 ((uint32_t)0x00200000) /*!< bit 21 */
#define NVIC_ICER_CLRENA_22 ((uint32_t)0x00400000) /*!< bit 22 */
#define NVIC_ICER_CLRENA_23 ((uint32_t)0x00800000) /*!< bit 23 */
#define NVIC_ICER_CLRENA_24 ((uint32_t)0x01000000) /*!< bit 24 */
#define NVIC_ICER_CLRENA_25 ((uint32_t)0x02000000) /*!< bit 25 */
#define NVIC_ICER_CLRENA_26 ((uint32_t)0x04000000) /*!< bit 26 */
#define NVIC_ICER_CLRENA_27 ((uint32_t)0x08000000) /*!< bit 27 */
#define NVIC_ICER_CLRENA_28 ((uint32_t)0x10000000) /*!< bit 28 */
#define NVIC_ICER_CLRENA_29 ((uint32_t)0x20000000) /*!< bit 29 */
#define NVIC_ICER_CLRENA_30 ((uint32_t)0x40000000) /*!< bit 30 */
#define NVIC_ICER_CLRENA_31 ((uint32_t)0x80000000) /*!< bit 31 */

/******************  Bit definition for NVIC_ISPR register  *******************/
#define NVIC_ISPR_SETPEND    ((uint32_t)0xFFFFFFFF) /*!< Interrupt set-pending bits */
#define NVIC_ISPR_SETPEND_0  ((uint32_t)0x00000001) /*!< bit 0 */
#define NVIC_ISPR_SETPEND_1  ((uint32_t)0x00000002) /*!< bit 1 */
#define NVIC_ISPR_SETPEND_2  ((uint32_t)0x00000004) /*!< bit 2 */
#define NVIC_ISPR_SETPEND_3  ((uint32_t)0x00000008) /*!< bit 3 */
#define NVIC_ISPR_SETPEND_4  ((uint32_t)0x00000010) /*!< bit 4 */
#define NVIC_ISPR_SETPEND_5  ((uint32_t)0x00000020) /*!< bit 5 */
#define NVIC_ISPR_SETPEND_6  ((uint32_t)0x00000040) /*!< bit 6 */
#define NVIC_ISPR_SETPEND_7  ((uint32_t)0x00000080) /*!< bit 7 */
#define NVIC_ISPR_SETPEND_8  ((uint32_t)0x00000100) /*!< bit 8 */
#define NVIC_ISPR_SETPEND_9  ((uint32_t)0x00000200) /*!< bit 9 */
#define NVIC_ISPR_SETPEND_10 ((uint32_t)0x00000400) /*!< bit 10 */
#define NVIC_ISPR_SETPEND_11 ((uint32_t)0x00000800) /*!< bit 11 */
#define NVIC_ISPR_SETPEND_12 ((uint32_t)0x00001000) /*!< bit 12 */
#define NVIC_ISPR_SETPEND_13 ((uint32_t)0x00002000) /*!< bit 13 */
#define NVIC_ISPR_SETPEND_14 ((uint32_t)0x00004000) /*!< bit 14 */
#define NVIC_ISPR_SETPEND_15 ((uint32_t)0x00008000) /*!< bit 15 */
#define NVIC_ISPR_SETPEND_16 ((uint32_t)0x00010000) /*!< bit 16 */
#define NVIC_ISPR_SETPEND_17 ((uint32_t)0x00020000) /*!< bit 17 */
#define NVIC_ISPR_SETPEND_18 ((uint32_t)0x00040000) /*!< bit 18 */
#define NVIC_ISPR_SETPEND_19 ((uint32_t)0x00080000) /*!< bit 19 */
#define NVIC_ISPR_SETPEND_20 ((uint32_t)0x00100000) /*!< bit 20 */
#define NVIC_ISPR_SETPEND_21 ((uint32_t)0x00200000) /*!< bit 21 */
#define NVIC_ISPR_SETPEND_22 ((uint32_t)0x00400000) /*!< bit 22 */
#define NVIC_ISPR_SETPEND_23 ((uint32_t)0x00800000) /*!< bit 23 */
#define NVIC_ISPR_SETPEND_24 ((uint32_t)0x01000000) /*!< bit 24 */
#define NVIC_ISPR_SETPEND_25 ((uint32_t)0x02000000) /*!< bit 25 */
#define NVIC_ISPR_SETPEND_26 ((uint32_t)0x04000000) /*!< bit 26 */
#define NVIC_ISPR_SETPEND_27 ((uint32_t)0x08000000) /*!< bit 27 */
#define NVIC_ISPR_SETPEND_28 ((uint32_t)0x10000000) /*!< bit 28 */
#define NVIC_ISPR_SETPEND_29 ((uint32_t)0x20000000) /*!< bit 29 */
#define NVIC_ISPR_SETPEND_30 ((uint32_t)0x40000000) /*!< bit 30 */
#define NVIC_ISPR_SETPEND_31 ((uint32_t)0x80000000) /*!< bit 31 */

/******************  Bit definition for NVIC_ICPR register  *******************/
#define NVIC_ICPR_CLRPEND    ((uint32_t)0xFFFFFFFF) /*!< Interrupt clear-pending bits */
#define NVIC_ICPR_CLRPEND_0  ((uint32_t)0x00000001) /*!< bit 0 */
#define NVIC_ICPR_CLRPEND_1  ((uint32_t)0x00000002) /*!< bit 1 */
#define NVIC_ICPR_CLRPEND_2  ((uint32_t)0x00000004) /*!< bit 2 */
#define NVIC_ICPR_CLRPEND_3  ((uint32_t)0x00000008) /*!< bit 3 */
#define NVIC_ICPR_CLRPEND_4  ((uint32_t)0x00000010) /*!< bit 4 */
#define NVIC_ICPR_CLRPEND_5  ((uint32_t)0x00000020) /*!< bit 5 */
#define NVIC_ICPR_CLRPEND_6  ((uint32_t)0x00000040) /*!< bit 6 */
#define NVIC_ICPR_CLRPEND_7  ((uint32_t)0x00000080) /*!< bit 7 */
#define NVIC_ICPR_CLRPEND_8  ((uint32_t)0x00000100) /*!< bit 8 */
#define NVIC_ICPR_CLRPEND_9  ((uint32_t)0x00000200) /*!< bit 9 */
#define NVIC_ICPR_CLRPEND_10 ((uint32_t)0x00000400) /*!< bit 10 */
#define NVIC_ICPR_CLRPEND_11 ((uint32_t)0x00000800) /*!< bit 11 */
#define NVIC_ICPR_CLRPEND_12 ((uint32_t)0x00001000) /*!< bit 12 */
#define NVIC_ICPR_CLRPEND_13 ((uint32_t)0x00002000) /*!< bit 13 */
#define NVIC_ICPR_CLRPEND_14 ((uint32_t)0x00004000) /*!< bit 14 */
#define NVIC_ICPR_CLRPEND_15 ((uint32_t)0x00008000) /*!< bit 15 */
#define NVIC_ICPR_CLRPEND_16 ((uint32_t)0x00010000) /*!< bit 16 */
#define NVIC_ICPR_CLRPEND_17 ((uint32_t)0x00020000) /*!< bit 17 */
#define NVIC_ICPR_CLRPEND_18 ((uint32_t)0x00040000) /*!< bit 18 */
#define NVIC_ICPR_CLRPEND_19 ((uint32_t)0x00080000) /*!< bit 19 */
#define NVIC_ICPR_CLRPEND_20 ((uint32_t)0x00100000) /*!< bit 20 */
#define NVIC_ICPR_CLRPEND_21 ((uint32_t)0x00200000) /*!< bit 21 */
#define NVIC_ICPR_CLRPEND_22 ((uint32_t)0x00400000) /*!< bit 22 */
#define NVIC_ICPR_CLRPEND_23 ((uint32_t)0x00800000) /*!< bit 23 */
#define NVIC_ICPR_CLRPEND_24 ((uint32_t)0x01000000) /*!< bit 24 */
#define NVIC_ICPR_CLRPEND_25 ((uint32_t)0x02000000) /*!< bit 25 */
#define NVIC_ICPR_CLRPEND_26 ((uint32_t)0x04000000) /*!< bit 26 */
#define NVIC_ICPR_CLRPEND_27 ((uint32_t)0x08000000) /*!< bit 27 */
#define NVIC_ICPR_CLRPEND_28 ((uint32_t)0x10000000) /*!< bit 28 */
#define NVIC_ICPR_CLRPEND_29 ((uint32_t)0x20000000) /*!< bit 29 */
#define NVIC_ICPR_CLRPEND_30 ((uint32_t)0x40000000) /*!< bit 30 */
#define NVIC_ICPR_CLRPEND_31 ((uint32_t)0x80000000) /*!< bit 31 */

/******************  Bit definition for NVIC_IABR register  *******************/
#define NVIC_IABR_ACTIVE    ((uint32_t)0xFFFFFFFF) /*!< Interrupt active flags */
#define NVIC_IABR_ACTIVE_0  ((uint32_t)0x00000001) /*!< bit 0 */
#define NVIC_IABR_ACTIVE_1  ((uint32_t)0x00000002) /*!< bit 1 */
#define NVIC_IABR_ACTIVE_2  ((uint32_t)0x00000004) /*!< bit 2 */
#define NVIC_IABR_ACTIVE_3  ((uint32_t)0x00000008) /*!< bit 3 */
#define NVIC_IABR_ACTIVE_4  ((uint32_t)0x00000010) /*!< bit 4 */
#define NVIC_IABR_ACTIVE_5  ((uint32_t)0x00000020) /*!< bit 5 */
#define NVIC_IABR_ACTIVE_6  ((uint32_t)0x00000040) /*!< bit 6 */
#define NVIC_IABR_ACTIVE_7  ((uint32_t)0x00000080) /*!< bit 7 */
#define NVIC_IABR_ACTIVE_8  ((uint32_t)0x00000100) /*!< bit 8 */
#define NVIC_IABR_ACTIVE_9  ((uint32_t)0x00000200) /*!< bit 9 */
#define NVIC_IABR_ACTIVE_10 ((uint32_t)0x00000400) /*!< bit 10 */
#define NVIC_IABR_ACTIVE_11 ((uint32_t)0x00000800) /*!< bit 11 */
#define NVIC_IABR_ACTIVE_12 ((uint32_t)0x00001000) /*!< bit 12 */
#define NVIC_IABR_ACTIVE_13 ((uint32_t)0x00002000) /*!< bit 13 */
#define NVIC_IABR_ACTIVE_14 ((uint32_t)0x00004000) /*!< bit 14 */
#define NVIC_IABR_ACTIVE_15 ((uint32_t)0x00008000) /*!< bit 15 */
#define NVIC_IABR_ACTIVE_16 ((uint32_t)0x00010000) /*!< bit 16 */
#define NVIC_IABR_ACTIVE_17 ((uint32_t)0x00020000) /*!< bit 17 */
#define NVIC_IABR_ACTIVE_18 ((uint32_t)0x00040000) /*!< bit 18 */
#define NVIC_IABR_ACTIVE_19 ((uint32_t)0x00080000) /*!< bit 19 */
#define NVIC_IABR_ACTIVE_20 ((uint32_t)0x00100000) /*!< bit 20 */
#define NVIC_IABR_ACTIVE_21 ((uint32_t)0x00200000) /*!< bit 21 */
#define NVIC_IABR_ACTIVE_22 ((uint32_t)0x00400000) /*!< bit 22 */
#define NVIC_IABR_ACTIVE_23 ((uint32_t)0x00800000) /*!< bit 23 */
#define NVIC_IABR_ACTIVE_24 ((uint32_t)0x01000000) /*!< bit 24 */
#define NVIC_IABR_ACTIVE_25 ((uint32_t)0x02000000) /*!< bit 25 */
#define NVIC_IABR_ACTIVE_26 ((uint32_t)0x04000000) /*!< bit 26 */
#define NVIC_IABR_ACTIVE_27 ((uint32_t)0x08000000) /*!< bit 27 */
#define NVIC_IABR_ACTIVE_28 ((uint32_t)0x10000000) /*!< bit 28 */
#define NVIC_IABR_ACTIVE_29 ((uint32_t)0x20000000) /*!< bit 29 */
#define NVIC_IABR_ACTIVE_30 ((uint32_t)0x40000000) /*!< bit 30 */
#define NVIC_IABR_ACTIVE_31 ((uint32_t)0x80000000) /*!< bit 31 */

/******************  Bit definition for NVIC_PRI0 register  *******************/
#define NVIC_IPR0_PRI_0 ((uint32_t)0x000000FF) /*!< Priority of interrupt 0 */
#define NVIC_IPR0_PRI_1 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 1 */
#define NVIC_IPR0_PRI_2 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 2 */
#define NVIC_IPR0_PRI_3 ((uint32_t)0xFF000000) /*!< Priority of interrupt 3 */

/******************  Bit definition for NVIC_PRI1 register  *******************/
#define NVIC_IPR1_PRI_4 ((uint32_t)0x000000FF) /*!< Priority of interrupt 4 */
#define NVIC_IPR1_PRI_5 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 5 */
#define NVIC_IPR1_PRI_6 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 6 */
#define NVIC_IPR1_PRI_7 ((uint32_t)0xFF000000) /*!< Priority of interrupt 7 */

/******************  Bit definition for NVIC_PRI2 register  *******************/
#define NVIC_IPR2_PRI_8  ((uint32_t)0x000000FF) /*!< Priority of interrupt 8 */
#define NVIC_IPR2_PRI_9  ((uint32_t)0x0000FF00) /*!< Priority of interrupt 9 */
#define NVIC_IPR2_PRI_10 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 10 */
#define NVIC_IPR2_PRI_11 ((uint32_t)0xFF000000) /*!< Priority of interrupt 11 */

/******************  Bit definition for NVIC_PRI3 register  *******************/
#define NVIC_IPR3_PRI_12 ((uint32_t)0x000000FF) /*!< Priority of interrupt 12 */
#define NVIC_IPR3_PRI_13 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 13 */
#define NVIC_IPR3_PRI_14 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 14 */
#define NVIC_IPR3_PRI_15 ((uint32_t)0xFF000000) /*!< Priority of interrupt 15 */

/******************  Bit definition for NVIC_PRI4 register  *******************/
#define NVIC_IPR4_PRI_16 ((uint32_t)0x000000FF) /*!< Priority of interrupt 16 */
#define NVIC_IPR4_PRI_17 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 17 */
#define NVIC_IPR4_PRI_18 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 18 */
#define NVIC_IPR4_PRI_19 ((uint32_t)0xFF000000) /*!< Priority of interrupt 19 */

/******************  Bit definition for NVIC_PRI5 register  *******************/
#define NVIC_IPR5_PRI_20 ((uint32_t)0x000000FF) /*!< Priority of interrupt 20 */
#define NVIC_IPR5_PRI_21 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 21 */
#define NVIC_IPR5_PRI_22 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 22 */
#define NVIC_IPR5_PRI_23 ((uint32_t)0xFF000000) /*!< Priority of interrupt 23 */

/******************  Bit definition for NVIC_PRI6 register  *******************/
#define NVIC_IPR6_PRI_24 ((uint32_t)0x000000FF) /*!< Priority of interrupt 24 */
#define NVIC_IPR6_PRI_25 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 25 */
#define NVIC_IPR6_PRI_26 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 26 */
#define NVIC_IPR6_PRI_27 ((uint32_t)0xFF000000) /*!< Priority of interrupt 27 */

/******************  Bit definition for NVIC_PRI7 register  *******************/
#define NVIC_IPR7_PRI_28 ((uint32_t)0x000000FF) /*!< Priority of interrupt 28 */
#define NVIC_IPR7_PRI_29 ((uint32_t)0x0000FF00) /*!< Priority of interrupt 29 */
#define NVIC_IPR7_PRI_30 ((uint32_t)0x00FF0000) /*!< Priority of interrupt 30 */
#define NVIC_IPR7_PRI_31 ((uint32_t)0xFF000000) /*!< Priority of interrupt 31 */

/******************  Bit definition for SCB_CPUID register  *******************/
#define SCB_CPUID_REVISION    ((uint32_t)0x0000000F) /*!< Implementation defined revision number */
#define SCB_CPUID_PARTNO      ((uint32_t)0x0000FFF0) /*!< Number of processor within family */
#define SCB_CPUID_Constant    ((uint32_t)0x000F0000) /*!< Reads as 0x0F */
#define SCB_CPUID_VARIANT     ((uint32_t)0x00F00000) /*!< Implementation defined variant number */
#define SCB_CPUID_IMPLEMENTER ((uint32_t)0xFF000000) /*!< Implementer code. ARM is 0x41 */

/*******************  Bit definition for SCB_ICSR register  *******************/
#define SCB_ICSR_VECTACTIVE ((uint32_t)0x000001FF) /*!< Active INTSTS number field */
#define SCB_ICSR_RETTOBASE                                                                                             \
    ((uint32_t)0x00000800) /*!< All active exceptions minus the IPSR_current_exception yields the empty set */
#define SCB_ICSR_VECTPENDING ((uint32_t)0x003FF000) /*!< Pending INTSTS number field */
#define SCB_ICSR_ISRPENDING  ((uint32_t)0x00400000) /*!< Interrupt pending flag */
#define SCB_ICSR_ISRPREEMPT                                                                                            \
    ((uint32_t)0x00800000) /*!< It indicates that a pending interrupt becomes active in the next running cycle */
#define SCB_ICSR_PENDSTCLR  ((uint32_t)0x02000000) /*!< Clear pending SysTick bit */
#define SCB_ICSR_PENDSTSET  ((uint32_t)0x04000000) /*!< Set pending SysTick bit */
#define SCB_ICSR_PENDSVCLR  ((uint32_t)0x08000000) /*!< Clear pending pendSV bit */
#define SCB_ICSR_PENDSVSET  ((uint32_t)0x10000000) /*!< Set pending pendSV bit */
#define SCB_ICSR_NMIPENDSET ((uint32_t)0x80000000) /*!< Set pending NMI bit */

/*******************  Bit definition for SCB_VTOR register  *******************/
#define SCB_VTOR_TBLOFF  ((uint32_t)0x1FFFFF80) /*!< Vector table base offset field */
#define SCB_VTOR_TBLBASE ((uint32_t)0x20000000) /*!< Table base in code(0) or RAM(1) */

/*!<*****************  Bit definition for SCB_AIRCR register  *******************/
#define SCB_AIRCR_VECTRESET     ((uint32_t)0x00000001) /*!< System Reset bit */
#define SCB_AIRCR_VECTCLRACTIVE ((uint32_t)0x00000002) /*!< Clear active vector bit */
#define SCB_AIRCR_SYSRESETREQ   ((uint32_t)0x00000004) /*!< Requests chip control logic to generate a reset */

#define SCB_AIRCR_PRIGROUP   ((uint32_t)0x00000700) /*!< PRIGROUP[2:0] bits (Priority group) */
#define SCB_AIRCR_PRIGROUP_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define SCB_AIRCR_PRIGROUP_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define SCB_AIRCR_PRIGROUP_2 ((uint32_t)0x00000400) /*!< Bit 2  */

/* prority group configuration */
#define SCB_AIRCR_PRIGROUP0                                                                                            \
    ((uint32_t)0x00000000) /*!< Priority group=0 (7 bits of pre-emption priority, 1 bit of subpriority) */
#define SCB_AIRCR_PRIGROUP1                                                                                            \
    ((uint32_t)0x00000100) /*!< Priority group=1 (6 bits of pre-emption priority, 2 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP2                                                                                            \
    ((uint32_t)0x00000200) /*!< Priority group=2 (5 bits of pre-emption priority, 3 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP3                                                                                            \
    ((uint32_t)0x00000300) /*!< Priority group=3 (4 bits of pre-emption priority, 4 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP4                                                                                            \
    ((uint32_t)0x00000400) /*!< Priority group=4 (3 bits of pre-emption priority, 5 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP5                                                                                            \
    ((uint32_t)0x00000500) /*!< Priority group=5 (2 bits of pre-emption priority, 6 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP6                                                                                            \
    ((uint32_t)0x00000600) /*!< Priority group=6 (1 bit of pre-emption priority, 7 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP7                                                                                            \
    ((uint32_t)0x00000700) /*!< Priority group=7 (no pre-emption priority, 8 bits of subpriority) */

#define SCB_AIRCR_ENDIANESS ((uint32_t)0x00008000) /*!< Data endianness bit */
#define SCB_AIRCR_VECTKEY   ((uint32_t)0xFFFF0000) /*!< Register key (VECTKEY) - Reads as 0xFA05 (VECTKEYSTAT) */

/*******************  Bit definition for SCB_SCR register  ********************/
#define SCB_SCR_SLEEPONEXIT ((uint8_t)0x02) /*!< Sleep on exit bit */
#define SCB_SCR_SLEEPDEEP   ((uint8_t)0x04) /*!< Sleep deep bit */
#define SCB_SCR_SEVONPEND   ((uint8_t)0x10) /*!< Wake up from WFE */

/********************  Bit definition for SCB_CCR register  *******************/
#define SCB_CCR_NONBASETHRDENA                                                                                         \
    ((uint16_t)0x0001) /*!< Thread mode can be entered from any level in Handler mode by controlled return value */
#define SCB_CCR_USERSETMPEND                                                                                           \
    ((uint16_t)0x0002) /*!< Enables user code to write the Software Trigger Interrupt register to trigger (pend) a     \
                          Main exception */
#define SCB_CCR_UNALIGN_TRP ((uint16_t)0x0008) /*!< Trap for unaligned access */
#define SCB_CCR_DIV_0_TRP   ((uint16_t)0x0010) /*!< Trap on Divide by 0 */
#define SCB_CCR_BFHFNMIGN   ((uint16_t)0x0100) /*!< Handlers running at priority -1 and -2 */
#define SCB_CCR_STKALIGN                                                                                               \
    ((uint16_t)0x0200) /*!< On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned */

/*******************  Bit definition for SCB_SHPR register ********************/
#define SCB_SHPR_PRI_N                                                                                                 \
    ((uint32_t)0x000000FF) /*!< Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor */
#define SCB_SHPR_PRI_N1                                                                                                \
    ((uint32_t)0x0000FF00) /*!< Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved */
#define SCB_SHPR_PRI_N2                                                                                                \
    ((uint32_t)0x00FF0000) /*!< Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV */
#define SCB_SHPR_PRI_N3                                                                                                \
    ((uint32_t)0xFF000000) /*!< Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick */

/******************  Bit definition for SCB_SHCSR register  *******************/
#define SCB_SHCSR_MEMFAULTACT    ((uint32_t)0x00000001) /*!< MemManage is active */
#define SCB_SHCSR_BUSFAULTACT    ((uint32_t)0x00000002) /*!< BusFault is active */
#define SCB_SHCSR_USGFAULTACT    ((uint32_t)0x00000008) /*!< UsageFault is active */
#define SCB_SHCSR_SVCALLACT      ((uint32_t)0x00000080) /*!< SVCall is active */
#define SCB_SHCSR_MONITORACT     ((uint32_t)0x00000100) /*!< Monitor is active */
#define SCB_SHCSR_PENDSVACT      ((uint32_t)0x00000400) /*!< PendSV is active */
#define SCB_SHCSR_SYSTICKACT     ((uint32_t)0x00000800) /*!< SysTick is active */
#define SCB_SHCSR_USGFAULTPENDED ((uint32_t)0x00001000) /*!< Usage Fault is pended */
#define SCB_SHCSR_MEMFAULTPENDED ((uint32_t)0x00002000) /*!< MemManage is pended */
#define SCB_SHCSR_BUSFAULTPENDED ((uint32_t)0x00004000) /*!< Bus Fault is pended */
#define SCB_SHCSR_SVCALLPENDED   ((uint32_t)0x00008000) /*!< SVCall is pended */
#define SCB_SHCSR_MEMFAULTENA    ((uint32_t)0x00010000) /*!< MemManage enable */
#define SCB_SHCSR_BUSFAULTENA    ((uint32_t)0x00020000) /*!< Bus Fault enable */
#define SCB_SHCSR_USGFAULTENA    ((uint32_t)0x00040000) /*!< UsageFault enable */

/*******************  Bit definition for SCB_CFSR register  *******************/
/*!< MFSR */
#define SCB_CFSR_IACCVIOL  ((uint32_t)0x00000001) /*!< Instruction access violation */
#define SCB_CFSR_DACCVIOL  ((uint32_t)0x00000002) /*!< Data access violation */
#define SCB_CFSR_MUNSTKERR ((uint32_t)0x00000008) /*!< Unstacking error */
#define SCB_CFSR_MSTKERR   ((uint32_t)0x00000010) /*!< Stacking error */
#define SCB_CFSR_MMARVALID ((uint32_t)0x00000080) /*!< Memory Manage Address Register address valid flag */
/*!< BFSR */
#define SCB_CFSR_IBUSERR     ((uint32_t)0x00000100) /*!< Instruction bus error flag */
#define SCB_CFSR_PRECISERR   ((uint32_t)0x00000200) /*!< Precise data bus error */
#define SCB_CFSR_IMPRECISERR ((uint32_t)0x00000400) /*!< Imprecise data bus error */
#define SCB_CFSR_UNSTKERR    ((uint32_t)0x00000800) /*!< Unstacking error */
#define SCB_CFSR_STKERR      ((uint32_t)0x00001000) /*!< Stacking error */
#define SCB_CFSR_BFARVALID   ((uint32_t)0x00008000) /*!< Bus Fault Address Register address valid flag */
/*!< UFSR */
#define SCB_CFSR_UNDEFINSTR ((uint32_t)0x00010000) /*!< The processor attempt to execute an undefined instruction */
#define SCB_CFSR_INVSTATE   ((uint32_t)0x00020000) /*!< Invalid combination of EPSR and instruction */
#define SCB_CFSR_INVPC      ((uint32_t)0x00040000) /*!< Attempt to load EXC_RETURN into pc illegally */
#define SCB_CFSR_NOCP       ((uint32_t)0x00080000) /*!< Attempt to use a coprocessor instruction */
#define SCB_CFSR_UNALIGNED                                                                                             \
    ((uint32_t)0x01000000) /*!< Fault occurs when there is an attempt to make an unaligned memory access */
#define SCB_CFSR_DIVBYZERO                                                                                             \
    ((uint32_t)0x02000000) /*!< Fault occurs when SDIV or DIV instruction is used with a divisor of 0 */

/*******************  Bit definition for SCB_HFSR register  *******************/
#define SCB_HFSR_VECTTBL                                                                                               \
    ((uint32_t)0x00000002) /*!< Fault occurs because of vector table read on exception processing */
#define SCB_HFSR_FORCED                                                                                                \
    ((uint32_t)0x40000000) /*!< Hard Fault activated when a configurable Fault was received and cannot activate */
#define SCB_HFSR_DEBUGEVT ((uint32_t)0x80000000) /*!< Fault related to debug */

/*******************  Bit definition for SCB_DFSR register  *******************/
#define SCB_DFSR_HALTED   ((uint8_t)0x01) /*!< Halt request flag */
#define SCB_DFSR_BKPT     ((uint8_t)0x02) /*!< BKPT flag */
#define SCB_DFSR_DWTTRAP  ((uint8_t)0x04) /*!< Data Watchpoint and Trace (DWT) flag */
#define SCB_DFSR_VCATCH   ((uint8_t)0x08) /*!< Vector catch flag */
#define SCB_DFSR_EXTERNAL ((uint8_t)0x10) /*!< External debug request flag */

/*******************  Bit definition for SCB_MMFAR register  ******************/
#define SCB_MMFAR_ADDRESS ((uint32_t)0xFFFFFFFF) /*!< Mem Manage fault address field */

/*******************  Bit definition for SCB_BFAR register  *******************/
#define SCB_BFAR_ADDRESS ((uint32_t)0xFFFFFFFF) /*!< Bus fault address field */

/*******************  Bit definition for SCB_afsr register  *******************/
#define SCB_AFSR_IMPDEF ((uint32_t)0xFFFFFFFF) /*!< Implementation defined */


/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for DMA_INTSTS register  ********************/
#define DMA_INTSTS_GLBF1 ((uint32_t)0x00000001) /*!< Channel 1 Global interrupt flag */
#define DMA_INTSTS_TXCF1 ((uint32_t)0x00000002) /*!< Channel 1 Transfer Complete flag */
#define DMA_INTSTS_HTXF1 ((uint32_t)0x00000004) /*!< Channel 1 Half Transfer flag */
#define DMA_INTSTS_ERRF1 ((uint32_t)0x00000008) /*!< Channel 1 Transfer Error flag */
#define DMA_INTSTS_GLBF2 ((uint32_t)0x00000010) /*!< Channel 2 Global interrupt flag */
#define DMA_INTSTS_TXCF2 ((uint32_t)0x00000020) /*!< Channel 2 Transfer Complete flag */
#define DMA_INTSTS_HTXF2 ((uint32_t)0x00000040) /*!< Channel 2 Half Transfer flag */
#define DMA_INTSTS_ERRF2 ((uint32_t)0x00000080) /*!< Channel 2 Transfer Error flag */
#define DMA_INTSTS_GLBF3 ((uint32_t)0x00000100) /*!< Channel 3 Global interrupt flag */
#define DMA_INTSTS_TXCF3 ((uint32_t)0x00000200) /*!< Channel 3 Transfer Complete flag */
#define DMA_INTSTS_HTXF3 ((uint32_t)0x00000400) /*!< Channel 3 Half Transfer flag */
#define DMA_INTSTS_ERRF3 ((uint32_t)0x00000800) /*!< Channel 3 Transfer Error flag */
#define DMA_INTSTS_GLBF4 ((uint32_t)0x00001000) /*!< Channel 4 Global interrupt flag */
#define DMA_INTSTS_TXCF4 ((uint32_t)0x00002000) /*!< Channel 4 Transfer Complete flag */
#define DMA_INTSTS_HTXF4 ((uint32_t)0x00004000) /*!< Channel 4 Half Transfer flag */
#define DMA_INTSTS_ERRF4 ((uint32_t)0x00008000) /*!< Channel 4 Transfer Error flag */
#define DMA_INTSTS_GLBF5 ((uint32_t)0x00010000) /*!< Channel 5 Global interrupt flag */
#define DMA_INTSTS_TXCF5 ((uint32_t)0x00020000) /*!< Channel 5 Transfer Complete flag */
#define DMA_INTSTS_HTXF5 ((uint32_t)0x00040000) /*!< Channel 5 Half Transfer flag */
#define DMA_INTSTS_ERRF5 ((uint32_t)0x00080000) /*!< Channel 5 Transfer Error flag */
#define DMA_INTSTS_GLBF6 ((uint32_t)0x00100000) /*!< Channel 6 Global interrupt flag */
#define DMA_INTSTS_TXCF6 ((uint32_t)0x00200000) /*!< Channel 6 Transfer Complete flag */
#define DMA_INTSTS_HTXF6 ((uint32_t)0x00400000) /*!< Channel 6 Half Transfer flag */
#define DMA_INTSTS_ERRF6 ((uint32_t)0x00800000) /*!< Channel 6 Transfer Error flag */
#define DMA_INTSTS_GLBF7 ((uint32_t)0x01000000) /*!< Channel 7 Global interrupt flag */
#define DMA_INTSTS_TXCF7 ((uint32_t)0x02000000) /*!< Channel 7 Transfer Complete flag */
#define DMA_INTSTS_HTXF7 ((uint32_t)0x04000000) /*!< Channel 7 Half Transfer flag */
#define DMA_INTSTS_ERRF7 ((uint32_t)0x08000000) /*!< Channel 7 Transfer Error flag */
#define DMA_INTSTS_GLBF8 ((uint32_t)0x10000000) /*!< Channel 7 Global interrupt flag */
#define DMA_INTSTS_TXCF8 ((uint32_t)0x20000000) /*!< Channel 7 Transfer Complete flag */
#define DMA_INTSTS_HTXF8 ((uint32_t)0x40000000) /*!< Channel 7 Half Transfer flag */
#define DMA_INTSTS_ERRF8 ((uint32_t)0x80000000) /*!< Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_INTCLR register  *******************/
#define DMA_INTCLR_CGLBF1 ((uint32_t)0x00000001) /*!< Channel 1 Global interrupt clear */
#define DMA_INTCLR_CTXCF1 ((uint32_t)0x00000002) /*!< Channel 1 Transfer Complete clear */
#define DMA_INTCLR_CHTXF1 ((uint32_t)0x00000004) /*!< Channel 1 Half Transfer clear */
#define DMA_INTCLR_CERRF1 ((uint32_t)0x00000008) /*!< Channel 1 Transfer Error clear */
#define DMA_INTCLR_CGLBF2 ((uint32_t)0x00000010) /*!< Channel 2 Global interrupt clear */
#define DMA_INTCLR_CTXCF2 ((uint32_t)0x00000020) /*!< Channel 2 Transfer Complete clear */
#define DMA_INTCLR_CHTXF2 ((uint32_t)0x00000040) /*!< Channel 2 Half Transfer clear */
#define DMA_INTCLR_CERRF2 ((uint32_t)0x00000080) /*!< Channel 2 Transfer Error clear */
#define DMA_INTCLR_CGLBF3 ((uint32_t)0x00000100) /*!< Channel 3 Global interrupt clear */
#define DMA_INTCLR_CTXCF3 ((uint32_t)0x00000200) /*!< Channel 3 Transfer Complete clear */
#define DMA_INTCLR_CHTXF3 ((uint32_t)0x00000400) /*!< Channel 3 Half Transfer clear */
#define DMA_INTCLR_CERRF3 ((uint32_t)0x00000800) /*!< Channel 3 Transfer Error clear */
#define DMA_INTCLR_CGLBF4 ((uint32_t)0x00001000) /*!< Channel 4 Global interrupt clear */
#define DMA_INTCLR_CTXCF4 ((uint32_t)0x00002000) /*!< Channel 4 Transfer Complete clear */
#define DMA_INTCLR_CHTXF4 ((uint32_t)0x00004000) /*!< Channel 4 Half Transfer clear */
#define DMA_INTCLR_CERRF4 ((uint32_t)0x00008000) /*!< Channel 4 Transfer Error clear */
#define DMA_INTCLR_CGLBF5 ((uint32_t)0x00010000) /*!< Channel 5 Global interrupt clear */
#define DMA_INTCLR_CTXCF5 ((uint32_t)0x00020000) /*!< Channel 5 Transfer Complete clear */
#define DMA_INTCLR_CHTXF5 ((uint32_t)0x00040000) /*!< Channel 5 Half Transfer clear */
#define DMA_INTCLR_CERRF5 ((uint32_t)0x00080000) /*!< Channel 5 Transfer Error clear */
#define DMA_INTCLR_CGLBF6 ((uint32_t)0x00100000) /*!< Channel 6 Global interrupt clear */
#define DMA_INTCLR_CTXCF6 ((uint32_t)0x00200000) /*!< Channel 6 Transfer Complete clear */
#define DMA_INTCLR_CHTXF6 ((uint32_t)0x00400000) /*!< Channel 6 Half Transfer clear */
#define DMA_INTCLR_CERRF6 ((uint32_t)0x00800000) /*!< Channel 6 Transfer Error clear */
#define DMA_INTCLR_CGLBF7 ((uint32_t)0x01000000) /*!< Channel 7 Global interrupt clear */
#define DMA_INTCLR_CTXCF7 ((uint32_t)0x02000000) /*!< Channel 7 Transfer Complete clear */
#define DMA_INTCLR_CHTXF7 ((uint32_t)0x04000000) /*!< Channel 7 Half Transfer clear */
#define DMA_INTCLR_CERRF7 ((uint32_t)0x08000000) /*!< Channel 7 Transfer Error clear */
#define DMA_INTCLR_CGLBF8 ((uint32_t)0x10000000) /*!< Channel 7 Global interrupt clear */
#define DMA_INTCLR_CTXCF8 ((uint32_t)0x20000000) /*!< Channel 7 Transfer Complete clear */
#define DMA_INTCLR_CHTXF8 ((uint32_t)0x40000000) /*!< Channel 7 Half Transfer clear */
#define DMA_INTCLR_CERRF8 ((uint32_t)0x80000000) /*!< Channel 7 Transfer Error clear */

/*******************  Bit definition for DMA_CHCFG1 register  *******************/
#define DMA_CHCFG1_CHEN  ((uint16_t)0x0001) /*!< Channel enable*/
#define DMA_CHCFG1_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG1_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG1_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG1_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG1_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG1_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG1_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG1_PSIZE   ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG1_PSIZE_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define DMA_CHCFG1_PSIZE_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define DMA_CHCFG1_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG1_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG1_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG1_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits(Channel Priority level) */
#define DMA_CHCFG1_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG1_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG1_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode */

/*******************  Bit definition for DMA_CHCFG2 register  *******************/
#define DMA_CHCFG2_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG2_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG2_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG2_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG2_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG2_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG2_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG2_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG2_PSIZE   ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG2_PSIZE_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define DMA_CHCFG2_PSIZE_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define DMA_CHCFG2_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG2_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG2_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG2_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG2_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG2_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG2_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode */

/*******************  Bit definition for DMA_CHCFG3 register  *******************/
#define DMA_CHCFG3_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG3_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG3_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG3_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG3_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG3_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG3_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG3_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG3_PSIZE   ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG3_PSIZE_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define DMA_CHCFG3_PSIZE_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define DMA_CHCFG3_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG3_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG3_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG3_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG3_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG3_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG3_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode */

/*!<******************  Bit definition for DMA_CHCFG4 register  *******************/
#define DMA_CHCFG4_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG4_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG4_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG4_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG4_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG4_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG4_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG4_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG4_PSIZE   ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG4_PSIZE_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define DMA_CHCFG4_PSIZE_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define DMA_CHCFG4_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG4_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG4_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG4_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG4_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG4_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG4_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCFG5 register  *******************/
#define DMA_CHCFG5_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG5_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG5_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG5_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG5_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG5_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG5_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG5_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG5_PSIZE   ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG5_PSIZE_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define DMA_CHCFG5_PSIZE_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define DMA_CHCFG5_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG5_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG5_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG5_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG5_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG5_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG5_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode enable */

/*******************  Bit definition for DMA_CHCFG6 register  *******************/
#define DMA_CHCFG6_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG6_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG6_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG6_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG6_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG6_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG6_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG6_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG6_PSIZE   ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG6_PSIZE_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define DMA_CHCFG6_PSIZE_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define DMA_CHCFG6_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG6_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG6_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG6_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG6_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG6_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG6_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode */

/*******************  Bit definition for DMA_CHCFG7 register  *******************/
#define DMA_CHCFG7_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG7_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG7_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG7_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG7_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG7_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG7_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG7_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG7_PSIZE   , ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG7_PSIZE_0 ((uint16_t)0x0100)   /*!< Bit 0 */
#define DMA_CHCFG7_PSIZE_1 ((uint16_t)0x0200)   /*!< Bit 1 */

#define DMA_CHCFG7_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG7_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG7_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG7_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG7_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG7_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG7_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode enable */

/*******************  Bit definition for DMA_CHCFG8 register  *******************/
#define DMA_CHCFG8_CHEN  ((uint16_t)0x0001) /*!< Channel enable */
#define DMA_CHCFG8_TXCIE ((uint16_t)0x0002) /*!< Transfer complete interrupt enable */
#define DMA_CHCFG8_HTXIE ((uint16_t)0x0004) /*!< Half Transfer interrupt enable */
#define DMA_CHCFG8_ERRIE ((uint16_t)0x0008) /*!< Transfer error interrupt enable */
#define DMA_CHCFG8_DIR   ((uint16_t)0x0010) /*!< Data transfer direction */
#define DMA_CHCFG8_CIRC  ((uint16_t)0x0020) /*!< Circular mode */
#define DMA_CHCFG8_PINC  ((uint16_t)0x0040) /*!< Peripheral increment mode */
#define DMA_CHCFG8_MINC  ((uint16_t)0x0080) /*!< Memory increment mode */

#define DMA_CHCFG8_PSIZE   , ((uint16_t)0x0300) /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG8_PSIZE_0 ((uint16_t)0x0100)   /*!< Bit 0 */
#define DMA_CHCFG8_PSIZE_1 ((uint16_t)0x0200)   /*!< Bit 1 */

#define DMA_CHCFG8_MSIZE   ((uint16_t)0x0C00) /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG8_MSIZE_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define DMA_CHCFG8_MSIZE_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define DMA_CHCFG8_PRIOLVL   ((uint16_t)0x3000) /*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG8_PRIOLVL_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define DMA_CHCFG8_PRIOLVL_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define DMA_CHCFG8_MEM2MEM ((uint16_t)0x4000) /*!< Memory to memory mode enable */

/******************  Bit definition for DMA_TXNUM1 register  ******************/
#define DMA_TXNUM1_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM2 register  ******************/
#define DMA_TXNUM2_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM3 register  ******************/
#define DMA_TXNUM3_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM4 register  ******************/
#define DMA_TXNUM4_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM5 register  ******************/
#define DMA_TXNUM5_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM6 register  ******************/
#define DMA_TXNUM6_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM7 register  ******************/
#define DMA_TXNUM7_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM8 register  ******************/
#define DMA_TXNUM8_NDTX ((uint16_t)0xFFFF) /*!< Number of data to Transfer */

/******************  Bit definition for DMA_PADDR1 register  *******************/
#define DMA_PADDR1_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR2 register  *******************/
#define DMA_PADDR2_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR3 register  *******************/
#define DMA_PADDR3_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR4 register  *******************/
#define DMA_PADDR4_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR5 register  *******************/
#define DMA_PADDR5_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR6 register  *******************/
#define DMA_PADDR6_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR7 register  *******************/
#define DMA_PADDR7_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR8 register  *******************/
#define DMA_PADDR8_ADDR ((uint32_t)0xFFFFFFFF) /*!< Peripheral Address */

/******************  Bit definition for DMA_MADDR1 register  *******************/
#define DMA_MADDR1_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR2 register  *******************/
#define DMA_MADDR2_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR3 register  *******************/
#define DMA_MADDR3_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR4 register  *******************/
#define DMA_MADDR4_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR5 register  *******************/
#define DMA_MADDR5_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR6 register  *******************/
#define DMA_MADDR6_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR7 register  *******************/
#define DMA_MADDR7_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************  Bit definition for DMA_MADDR8 register  *******************/
#define DMA_MADDR8_ADDR ((uint32_t)0xFFFFFFFF) /*!< Memory Address */

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for ADC_STS register  ********************/
#define ADC_STS_AWDG  ((uint8_t)0x01) /*!< Analog watchdog flag */
#define ADC_STS_ENDC  ((uint8_t)0x02) /*!< End of conversion */
#define ADC_STS_JENDC ((uint8_t)0x04) /*!< Injected channel end of conversion */
#define ADC_STS_JSTR  ((uint8_t)0x08) /*!< Injected channel Start flag */
#define ADC_STS_STR   ((uint8_t)0x10) /*!< Regular channel Start flag */
#define ADC_STS_ENDCA  ((uint8_t)0x20) /*!< Regular channel any end flag */
#define ADC_STS_JENDCA   ((uint8_t)0x40) /*!< Injected channel any end flag */


/*******************  Bit definition for ADC_CTRL1 register  ********************/
#define ADC_CTRL1_AWDGCH  ((uint32_t)0x0000001F) /*!< AWDG_CH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_CTRL1_AWDCH_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_CTRL1_AWDCH_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_CTRL1_AWDCH_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define ADC_CTRL1_AWDCH_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define ADC_CTRL1_AWDCH_4 ((uint32_t)0x00000010) /*!< Bit 4 */

#define ADC_CTRL1_ENDCIEN   ((uint32_t)0x00000020) /*!< Interrupt enable for EOC */
#define ADC_CTRL1_AWDGIEN   ((uint32_t)0x00000040) /*!< Analog Watchdog interrupt enable */
#define ADC_CTRL1_JENDCIEN  ((uint32_t)0x00000080) /*!< Interrupt enable for injected channels */
#define ADC_CTRL1_SCANMD    ((uint32_t)0x00000100) /*!< Scan mode */
#define ADC_CTRL1_AWDGSGLEN ((uint32_t)0x00000200) /*!< Enable the watchdog on a single channel in scan mode */
#define ADC_CTRL1_AUTOJC    ((uint32_t)0x00000400) /*!< Automatic injected group conversion */
#define ADC_CTRL1_DREGCH    ((uint32_t)0x00000800) /*!< Discontinuous mode on regular channels */
#define ADC_CTRL1_DJCH      ((uint32_t)0x00001000) /*!< Discontinuous mode on injected channels */

#define ADC_CTRL1_DCTU   ((uint32_t)0x0000E000) /*!< DISC_NUM[2:0] bits (Discontinuous mode channel count) */
#define ADC_CTRL1_DCTU_0 ((uint32_t)0x00002000) /*!< Bit 0 */
#define ADC_CTRL1_DCTU_1 ((uint32_t)0x00004000) /*!< Bit 1 */
#define ADC_CTRL1_DCTU_2 ((uint32_t)0x00008000) /*!< Bit 2 */

#define ADC_CTRL1_AWDGEJCH ((uint32_t)0x00400000) /*!< Analog watchdog enable on injected channels */
#define ADC_CTRL1_AWDGERCH ((uint32_t)0x00800000) /*!< Analog watchdog enable on regular channels */

/*******************  Bit definition for ADC_CTRL2 register  ********************/
#define ADC_CTRL2_ON    ((uint32_t)0x00000001) /*!< A/D Converter ON / OFF */
#define ADC_CTRL2_CTU   ((uint32_t)0x00000002) /*!< Continuous Conversion */
#define ADC_CTRL2_ENCAL ((uint32_t)0x00000004) /*!< A/D Calibration */
#define ADC_CTRL2_ENDMA ((uint32_t)0x00000100) /*!< Direct Memory access mode */
#define ADC_CTRL2_ALIG  ((uint32_t)0x00000800) /*!< Data Alignment */

#define ADC_CTRL2_EXTJSEL                                                                                              \
    ((uint32_t)0x00007000) /*!< INJ_EXT_SEL[2:0] bits (External event select for injected group) */
#define ADC_CTRL2_EXTJSEL_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define ADC_CTRL2_EXTJSEL_1 ((uint32_t)0x00002000) /*!< Bit 1 */
#define ADC_CTRL2_EXTJSEL_2 ((uint32_t)0x00004000) /*!< Bit 2 */

#define ADC_CTRL2_EXTJTRIG ((uint32_t)0x00008000) /*!< External Trigger Conversion mode for injected channels */

#define ADC_CTRL2_EXTRSEL   ((uint32_t)0x000E0000) /*!< EXTSEL[2:0] bits (External Event Select for regular group) */
#define ADC_CTRL2_EXTRSEL_0 ((uint32_t)0x00020000) /*!< Bit 0 */
#define ADC_CTRL2_EXTRSEL_1 ((uint32_t)0x00040000) /*!< Bit 1 */
#define ADC_CTRL2_EXTRSEL_2 ((uint32_t)0x00080000) /*!< Bit 2 */

#define ADC_CTRL2_EXTRTRIG ((uint32_t)0x00100000) /*!< External Trigger Conversion mode for regular channels */
#define ADC_CTRL2_SWSTRJCH ((uint32_t)0x00200000) /*!< Start Conversion of injected channels */
#define ADC_CTRL2_SWSTRRCH ((uint32_t)0x00400000) /*!< Start Conversion of regular channels */
#define ADC_CTRL2_TEMPEN   ((uint32_t)0x00800000) /*!< Temperature Sensor and VREFINT Enable */

/******************  Bit definition for ADC_SAMPT1 register  *******************/
#define ADC_SAMPT1_SAMP10   ((uint32_t)0x00000007) /*!< SMP10[2:0] bits (Channel 10 Sample time selection) */
#define ADC_SAMPT1_SAMP10_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP10_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP10_2 ((uint32_t)0x00000004) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP11   ((uint32_t)0x00000038) /*!< SMP11[2:0] bits (Channel 11 Sample time selection) */
#define ADC_SAMPT1_SAMP11_0 ((uint32_t)0x00000008) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP11_1 ((uint32_t)0x00000010) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP11_2 ((uint32_t)0x00000020) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP12   ((uint32_t)0x000001C0) /*!< SMP12[2:0] bits (Channel 12 Sample time selection) */
#define ADC_SAMPT1_SAMP12_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP12_1 ((uint32_t)0x00000080) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP12_2 ((uint32_t)0x00000100) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP13   ((uint32_t)0x00000E00) /*!< SMP13[2:0] bits (Channel 13 Sample time selection) */
#define ADC_SAMPT1_SAMP13_0 ((uint32_t)0x00000200) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP13_1 ((uint32_t)0x00000400) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP13_2 ((uint32_t)0x00000800) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP14   ((uint32_t)0x00007000) /*!< SMP14[2:0] bits (Channel 14 Sample time selection) */
#define ADC_SAMPT1_SAMP14_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP14_1 ((uint32_t)0x00002000) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP14_2 ((uint32_t)0x00004000) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP15   ((uint32_t)0x00038000) /*!< SMP15[2:0] bits (Channel 15 Sample time selection) */
#define ADC_SAMPT1_SAMP15_0 ((uint32_t)0x00008000) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP15_1 ((uint32_t)0x00010000) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP15_2 ((uint32_t)0x00020000) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP16   ((uint32_t)0x001C0000) /*!< SMP16[2:0] bits (Channel 16 Sample time selection) */
#define ADC_SAMPT1_SAMP16_0 ((uint32_t)0x00040000) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP16_1 ((uint32_t)0x00080000) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP16_2 ((uint32_t)0x00100000) /*!< Bit 2 */

#define ADC_SAMPT1_SAMP17   ((uint32_t)0x00E00000) /*!< SMP17[2:0] bits (Channel 17 Sample time selection) */
#define ADC_SAMPT1_SAMP17_0 ((uint32_t)0x00200000) /*!< Bit 0 */
#define ADC_SAMPT1_SAMP17_1 ((uint32_t)0x00400000) /*!< Bit 1 */
#define ADC_SAMPT1_SAMP17_2 ((uint32_t)0x00800000) /*!< Bit 2 */

/******************  Bit definition for ADC_SAMPT2 register  *******************/
#define ADC_SAMPT2_SAMP0   ((uint32_t)0x00000007) /*!< SMP0[2:0] bits (Channel 0 Sample time selection) */
#define ADC_SAMPT2_SAMP0_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP0_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP0_2 ((uint32_t)0x00000004) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP1   ((uint32_t)0x00000038) /*!< SMP1[2:0] bits (Channel 1 Sample time selection) */
#define ADC_SAMPT2_SAMP1_0 ((uint32_t)0x00000008) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP1_1 ((uint32_t)0x00000010) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP1_2 ((uint32_t)0x00000020) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP2   ((uint32_t)0x000001C0) /*!< SMP2[2:0] bits (Channel 2 Sample time selection) */
#define ADC_SAMPT2_SAMP2_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP2_1 ((uint32_t)0x00000080) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP2_2 ((uint32_t)0x00000100) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP3   ((uint32_t)0x00000E00) /*!< SMP3[2:0] bits (Channel 3 Sample time selection) */
#define ADC_SAMPT2_SAMP3_0 ((uint32_t)0x00000200) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP3_1 ((uint32_t)0x00000400) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP3_2 ((uint32_t)0x00000800) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP4   ((uint32_t)0x00007000) /*!< SMP4[2:0] bits (Channel 4 Sample time selection) */
#define ADC_SAMPT2_SAMP4_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP4_1 ((uint32_t)0x00002000) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP4_2 ((uint32_t)0x00004000) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP5   ((uint32_t)0x00038000) /*!< SMP5[2:0] bits (Channel 5 Sample time selection) */
#define ADC_SAMPT2_SAMP5_0 ((uint32_t)0x00008000) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP5_1 ((uint32_t)0x00010000) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP5_2 ((uint32_t)0x00020000) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP6   ((uint32_t)0x001C0000) /*!< SMP6[2:0] bits (Channel 6 Sample time selection) */
#define ADC_SAMPT2_SAMP6_0 ((uint32_t)0x00040000) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP6_1 ((uint32_t)0x00080000) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP6_2 ((uint32_t)0x00100000) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP7   ((uint32_t)0x00E00000) /*!< SMP7[2:0] bits (Channel 7 Sample time selection) */
#define ADC_SAMPT2_SAMP7_0 ((uint32_t)0x00200000) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP7_1 ((uint32_t)0x00400000) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP7_2 ((uint32_t)0x00800000) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP8   ((uint32_t)0x07000000) /*!< SMP8[2:0] bits (Channel 8 Sample time selection) */
#define ADC_SAMPT2_SAMP8_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP8_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP8_2 ((uint32_t)0x04000000) /*!< Bit 2 */

#define ADC_SAMPT2_SAMP9   ((uint32_t)0x38000000) /*!< SMP9[2:0] bits (Channel 9 Sample time selection) */
#define ADC_SAMPT2_SAMP9_0 ((uint32_t)0x08000000) /*!< Bit 0 */
#define ADC_SAMPT2_SAMP9_1 ((uint32_t)0x10000000) /*!< Bit 1 */
#define ADC_SAMPT2_SAMP9_2 ((uint32_t)0x20000000) /*!< Bit 2 */

/******************  Bit definition for ADC_JOFFSET1 register  *******************/
#define ADC_JOFFSET1_OFFSETJCH1 ((uint16_t)0x0FFF) /*!< Data offset for injected channel 1 */

/******************  Bit definition for ADC_JOFFSET2 register  *******************/
#define ADC_JOFFSET2_OFFSETJCH2 ((uint16_t)0x0FFF) /*!< Data offset for injected channel 2 */

/******************  Bit definition for ADC_JOFFSET3 register  *******************/
#define ADC_JOFFSET3_OFFSETJCH3 ((uint16_t)0x0FFF) /*!< Data offset for injected channel 3 */

/******************  Bit definition for ADC_JOFFSET4 register  *******************/
#define ADC_JOFFSET4_OFFSETJCH4 ((uint16_t)0x0FFF) /*!< Data offset for injected channel 4 */

/*******************  Bit definition for ADC_WDGHIGH register  ********************/
#define ADC_WDGHIGH_HTH ((uint16_t)0x0FFF) /*!< Analog watchdog high threshold */

/*******************  Bit definition for ADC_WDGLOW register  ********************/
#define ADC_WDGLOW_LTH ((uint16_t)0x0FFF) /*!< Analog watchdog low threshold */

/*******************  Bit definition for ADC_RSEQ1 register  *******************/
#define ADC_RSEQ1_SEQ13   ((uint32_t)0x0000001F) /*!< SQ13[4:0] bits (13th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ13_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_RSEQ1_SEQ13_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_RSEQ1_SEQ13_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define ADC_RSEQ1_SEQ13_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define ADC_RSEQ1_SEQ13_4 ((uint32_t)0x00000010) /*!< Bit 4 */

#define ADC_RSEQ1_SEQ14   ((uint32_t)0x000003E0) /*!< SQ14[4:0] bits (14th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ14_0 ((uint32_t)0x00000020) /*!< Bit 0 */
#define ADC_RSEQ1_SEQ14_1 ((uint32_t)0x00000040) /*!< Bit 1 */
#define ADC_RSEQ1_SEQ14_2 ((uint32_t)0x00000080) /*!< Bit 2 */
#define ADC_RSEQ1_SEQ14_3 ((uint32_t)0x00000100) /*!< Bit 3 */
#define ADC_RSEQ1_SEQ14_4 ((uint32_t)0x00000200) /*!< Bit 4 */

#define ADC_RSEQ1_SEQ15   ((uint32_t)0x00007C00) /*!< SQ15[4:0] bits (15th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ15_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define ADC_RSEQ1_SEQ15_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define ADC_RSEQ1_SEQ15_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define ADC_RSEQ1_SEQ15_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define ADC_RSEQ1_SEQ15_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define ADC_RSEQ1_SEQ16   ((uint32_t)0x000F8000) /*!< SQ16[4:0] bits (16th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ16_0 ((uint32_t)0x00008000) /*!< Bit 0 */
#define ADC_RSEQ1_SEQ16_1 ((uint32_t)0x00010000) /*!< Bit 1 */
#define ADC_RSEQ1_SEQ16_2 ((uint32_t)0x00020000) /*!< Bit 2 */
#define ADC_RSEQ1_SEQ16_3 ((uint32_t)0x00040000) /*!< Bit 3 */
#define ADC_RSEQ1_SEQ16_4 ((uint32_t)0x00080000) /*!< Bit 4 */

#define ADC_RSEQ1_LEN   ((uint32_t)0x00F00000) /*!< L[3:0] bits (Regular channel sequence length) */
#define ADC_RSEQ1_LEN_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define ADC_RSEQ1_LEN_1 ((uint32_t)0x00200000) /*!< Bit 1 */
#define ADC_RSEQ1_LEN_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define ADC_RSEQ1_LEN_3 ((uint32_t)0x00800000) /*!< Bit 3 */

/*******************  Bit definition for ADC_RSEQ2 register  *******************/
#define ADC_RSEQ2_SEQ7   ((uint32_t)0x0000001F) /*!< SQ7[4:0] bits (7th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ7_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_RSEQ2_SEQ7_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_RSEQ2_SEQ7_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define ADC_RSEQ2_SEQ7_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define ADC_RSEQ2_SEQ7_4 ((uint32_t)0x00000010) /*!< Bit 4 */

#define ADC_RSEQ2_SEQ8   ((uint32_t)0x000003E0) /*!< SQ8[4:0] bits (8th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ8_0 ((uint32_t)0x00000020) /*!< Bit 0 */
#define ADC_RSEQ2_SEQ8_1 ((uint32_t)0x00000040) /*!< Bit 1 */
#define ADC_RSEQ2_SEQ8_2 ((uint32_t)0x00000080) /*!< Bit 2 */
#define ADC_RSEQ2_SEQ8_3 ((uint32_t)0x00000100) /*!< Bit 3 */
#define ADC_RSEQ2_SEQ8_4 ((uint32_t)0x00000200) /*!< Bit 4 */

#define ADC_RSEQ2_SEQ9   ((uint32_t)0x00007C00) /*!< SQ9[4:0] bits (9th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ9_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define ADC_RSEQ2_SEQ9_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define ADC_RSEQ2_SEQ9_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define ADC_RSEQ2_SEQ9_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define ADC_RSEQ2_SEQ9_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define ADC_RSEQ2_SEQ10   ((uint32_t)0x000F8000) /*!< SQ10[4:0] bits (10th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ10_0 ((uint32_t)0x00008000) /*!< Bit 0 */
#define ADC_RSEQ2_SEQ10_1 ((uint32_t)0x00010000) /*!< Bit 1 */
#define ADC_RSEQ2_SEQ10_2 ((uint32_t)0x00020000) /*!< Bit 2 */
#define ADC_RSEQ2_SEQ10_3 ((uint32_t)0x00040000) /*!< Bit 3 */
#define ADC_RSEQ2_SEQ10_4 ((uint32_t)0x00080000) /*!< Bit 4 */

#define ADC_RSEQ2_SEQ11   ((uint32_t)0x01F00000) /*!< SQ11[4:0] bits (11th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ11_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define ADC_RSEQ2_SEQ11_1 ((uint32_t)0x00200000) /*!< Bit 1 */
#define ADC_RSEQ2_SEQ11_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define ADC_RSEQ2_SEQ11_3 ((uint32_t)0x00800000) /*!< Bit 3 */
#define ADC_RSEQ2_SEQ11_4 ((uint32_t)0x01000000) /*!< Bit 4 */

#define ADC_RSEQ2_SEQ12   ((uint32_t)0x3E000000) /*!< SQ12[4:0] bits (12th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ12_0 ((uint32_t)0x02000000) /*!< Bit 0 */
#define ADC_RSEQ2_SEQ12_1 ((uint32_t)0x04000000) /*!< Bit 1 */
#define ADC_RSEQ2_SEQ12_2 ((uint32_t)0x08000000) /*!< Bit 2 */
#define ADC_RSEQ2_SEQ12_3 ((uint32_t)0x10000000) /*!< Bit 3 */
#define ADC_RSEQ2_SEQ12_4 ((uint32_t)0x20000000) /*!< Bit 4 */

/*******************  Bit definition for ADC_RSEQ3 register  *******************/
#define ADC_RSEQ3_SEQ1   ((uint32_t)0x0000001F) /*!< SQ1[4:0] bits (1st conversion in regular sequence) */
#define ADC_RSEQ3_SEQ1_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_RSEQ3_SEQ1_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_RSEQ3_SEQ1_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define ADC_RSEQ3_SEQ1_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define ADC_RSEQ3_SEQ1_4 ((uint32_t)0x00000010) /*!< Bit 4 */

#define ADC_RSEQ3_SEQ2   ((uint32_t)0x000003E0) /*!< SQ2[4:0] bits (2nd conversion in regular sequence) */
#define ADC_RSEQ3_SEQ2_0 ((uint32_t)0x00000020) /*!< Bit 0 */
#define ADC_RSEQ3_SEQ2_1 ((uint32_t)0x00000040) /*!< Bit 1 */
#define ADC_RSEQ3_SEQ2_2 ((uint32_t)0x00000080) /*!< Bit 2 */
#define ADC_RSEQ3_SEQ2_3 ((uint32_t)0x00000100) /*!< Bit 3 */
#define ADC_RSEQ3_SEQ2_4 ((uint32_t)0x00000200) /*!< Bit 4 */

#define ADC_RSEQ3_SEQ3   ((uint32_t)0x00007C00) /*!< SQ3[4:0] bits (3rd conversion in regular sequence) */
#define ADC_RSEQ3_SEQ3_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define ADC_RSEQ3_SEQ3_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define ADC_RSEQ3_SEQ3_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define ADC_RSEQ3_SEQ3_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define ADC_RSEQ3_SEQ3_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define ADC_RSEQ3_SEQ4   ((uint32_t)0x000F8000) /*!< SQ4[4:0] bits (4th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ4_0 ((uint32_t)0x00008000) /*!< Bit 0 */
#define ADC_RSEQ3_SEQ4_1 ((uint32_t)0x00010000) /*!< Bit 1 */
#define ADC_RSEQ3_SEQ4_2 ((uint32_t)0x00020000) /*!< Bit 2 */
#define ADC_RSEQ3_SEQ4_3 ((uint32_t)0x00040000) /*!< Bit 3 */
#define ADC_RSEQ3_SEQ4_4 ((uint32_t)0x00080000) /*!< Bit 4 */

#define ADC_RSEQ3_SEQ5   ((uint32_t)0x01F00000) /*!< SQ5[4:0] bits (5th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ5_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define ADC_RSEQ3_SEQ5_1 ((uint32_t)0x00200000) /*!< Bit 1 */
#define ADC_RSEQ3_SEQ5_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define ADC_RSEQ3_SEQ5_3 ((uint32_t)0x00800000) /*!< Bit 3 */
#define ADC_RSEQ3_SEQ5_4 ((uint32_t)0x01000000) /*!< Bit 4 */

#define ADC_RSEQ3_SEQ6   ((uint32_t)0x3E000000) /*!< SQ6[4:0] bits (6th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ6_0 ((uint32_t)0x02000000) /*!< Bit 0 */
#define ADC_RSEQ3_SEQ6_1 ((uint32_t)0x04000000) /*!< Bit 1 */
#define ADC_RSEQ3_SEQ6_2 ((uint32_t)0x08000000) /*!< Bit 2 */
#define ADC_RSEQ3_SEQ6_3 ((uint32_t)0x10000000) /*!< Bit 3 */
#define ADC_RSEQ3_SEQ6_4 ((uint32_t)0x20000000) /*!< Bit 4 */

/*******************  Bit definition for ADC_JSEQ register  *******************/
#define ADC_JSEQ_JSEQ1   ((uint32_t)0x0000001F) /*!< JSQ1[4:0] bits (1st conversion in injected sequence) */
#define ADC_JSEQ_JSEQ1_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_JSEQ_JSEQ1_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_JSEQ_JSEQ1_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define ADC_JSEQ_JSEQ1_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define ADC_JSEQ_JSEQ1_4 ((uint32_t)0x00000010) /*!< Bit 4 */

#define ADC_JSEQ_JSEQ2   ((uint32_t)0x000003E0) /*!< JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define ADC_JSEQ_JSEQ2_0 ((uint32_t)0x00000020) /*!< Bit 0 */
#define ADC_JSEQ_JSEQ2_1 ((uint32_t)0x00000040) /*!< Bit 1 */
#define ADC_JSEQ_JSEQ2_2 ((uint32_t)0x00000080) /*!< Bit 2 */
#define ADC_JSEQ_JSEQ2_3 ((uint32_t)0x00000100) /*!< Bit 3 */
#define ADC_JSEQ_JSEQ2_4 ((uint32_t)0x00000200) /*!< Bit 4 */

#define ADC_JSEQ_JSEQ3   ((uint32_t)0x00007C00) /*!< JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define ADC_JSEQ_JSEQ3_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define ADC_JSEQ_JSEQ3_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define ADC_JSEQ_JSEQ3_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define ADC_JSEQ_JSEQ3_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define ADC_JSEQ_JSEQ3_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define ADC_JSEQ_JSEQ4   ((uint32_t)0x000F8000) /*!< JSQ4[4:0] bits (4th conversion in injected sequence) */
#define ADC_JSEQ_JSEQ4_0 ((uint32_t)0x00008000) /*!< Bit 0 */
#define ADC_JSEQ_JSEQ4_1 ((uint32_t)0x00010000) /*!< Bit 1 */
#define ADC_JSEQ_JSEQ4_2 ((uint32_t)0x00020000) /*!< Bit 2 */
#define ADC_JSEQ_JSEQ4_3 ((uint32_t)0x00040000) /*!< Bit 3 */
#define ADC_JSEQ_JSEQ4_4 ((uint32_t)0x00080000) /*!< Bit 4 */

#define ADC_JSEQ_JLEN   ((uint32_t)0x00300000) /*!< INJ_LEN[1:0] bits (Injected Sequence length) */
#define ADC_JSEQ_JLEN_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define ADC_JSEQ_JLEN_1 ((uint32_t)0x00200000) /*!< Bit 1 */

/*******************  Bit definition for ADC_JDAT1 register  *******************/
#define ADC_JDAT1_JDAT ((uint16_t)0xFFFF) /*!< Injected data */

/*******************  Bit definition for ADC_JDAT2 register  *******************/
#define ADC_JDAT2_JDAT ((uint16_t)0xFFFF) /*!< Injected data */

/*******************  Bit definition for ADC_JDAT3 register  *******************/
#define ADC_JDAT3_JDAT ((uint16_t)0xFFFF) /*!< Injected data */

/*******************  Bit definition for ADC_JDAT4 register  *******************/
#define ADC_JDAT4_JDAT ((uint16_t)0xFFFF) /*!< Injected data */

/********************  Bit definition for ADC_DAT register  ********************/
#define ADC_DAT_DAT     ((uint32_t)0x0000FFFF) /*!< Regular data */

///********************  Bit definition for ADC_DIFSEL register  ********************/
//#define ADC_DIFSEL_DIFSEL       ((uint32_t)0x000FFFFE) /*!< Differential data */
//#define ADC_DIFSEL_DIFSEL_0     ((uint32_t)0x00000002) /*!< Differential_1 data */
//#define ADC_DIFSEL_DIFSEL_1     ((uint32_t)0x00000004) /*!< Differential_2 data */
//#define ADC_DIFSEL_DIFSEL_2     ((uint32_t)0x00000008) /*!< Differential_3 data */
//#define ADC_DIFSEL_DIFSEL_3     ((uint32_t)0x00000010) /*!< Differential_4 data */
//#define ADC_DIFSEL_DIFSEL_4     ((uint32_t)0x00000020) /*!< Differential_5 data */
//#define ADC_DIFSEL_DIFSEL_5     ((uint32_t)0x00000040) /*!< Differential_6 data */
//#define ADC_DIFSEL_DIFSEL_6     ((uint32_t)0x00000080) /*!< Differential_7 data */
//#define ADC_DIFSEL_DIFSEL_7     ((uint32_t)0x00000100) /*!< Differential_8 data */
//#define ADC_DIFSEL_DIFSEL_8     ((uint32_t)0x00000200) /*!< Differential_9 data */
//#define ADC_DIFSEL_DIFSEL_9     ((uint32_t)0x00000400) /*!< Differential_10 data */
//#define ADC_DIFSEL_DIFSEL_10     ((uint32_t)0x00000800) /*!< Differential_11 data */
//#define ADC_DIFSEL_DIFSEL_11     ((uint32_t)0x00001000) /*!< Differential_12 data */
//#define ADC_DIFSEL_DIFSEL_12     ((uint32_t)0x00002000) /*!< Differential_13 data */
//#define ADC_DIFSEL_DIFSEL_13     ((uint32_t)0x00004000) /*!< Differential_14 data */
//#define ADC_DIFSEL_DIFSEL_14     ((uint32_t)0x00008000) /*!< Differential_15 data */
//#define ADC_DIFSEL_DIFSEL_15     ((uint32_t)0x00010000) /*!< Differential_16 data */
//#define ADC_DIFSEL_DIFSEL_16     ((uint32_t)0x00020000) /*!< Differential_17 data */
//#define ADC_DIFSEL_DIFSEL_17     ((uint32_t)0x00040000) /*!< Differential_18 data */
//#define ADC_DIFSEL_DIFSEL_18     ((uint32_t)0x00080000) /*!< Differential_19 data */

///********************  Bit definition for ADC_CALFACT register  ********************/
//#define ADC_CALFACT_CALFACTS     ((uint32_t)0x0000007F) /*!< Calibration factors in single data */
//#define ADC_CALFACT_CALFACTS_0   ((uint32_t)0x00000001) /*!< Calibration factors_0 in single data */
//#define ADC_CALFACT_CALFACTS_1   ((uint32_t)0x00000002) /*!< Calibration factors_1 in single data */
//#define ADC_CALFACT_CALFACTS_2   ((uint32_t)0x00000004) /*!< Calibration factors_2 in single data */
//#define ADC_CALFACT_CALFACTS_3   ((uint32_t)0x00000008) /*!< Calibration factors_3 in single data */
//#define ADC_CALFACT_CALFACTS_4   ((uint32_t)0x00000010) /*!< Calibration factors_4 in single data */
//#define ADC_CALFACT_CALFACTS_5   ((uint32_t)0x00000020) /*!< Calibration factors_5 in single data */
//#define ADC_CALFACT_CALFACTS_6   ((uint32_t)0x00000040) /*!< Calibration factors_6 in single data */

//#define ADC_CALFACT_CALFACTD     ((uint32_t)0x007F0000) /*!< Calibration factors in differential data */
//#define ADC_CALFACT_CALFACTD_0   ((uint32_t)0x00010000) /*!< Calibration factors_0 in differential data */
//#define ADC_CALFACT_CALFACTD_1   ((uint32_t)0x00020000) /*!< Calibration factors_1 in differential data */
//#define ADC_CALFACT_CALFACTD_2   ((uint32_t)0x00040000) /*!< Calibration factors_2 in differential data */
//#define ADC_CALFACT_CALFACTD_3   ((uint32_t)0x00080000) /*!< Calibration factors_3 in differential data */
//#define ADC_CALFACT_CALFACTD_4   ((uint32_t)0x00100000) /*!< Calibration factors_4 in differential data */
//#define ADC_CALFACT_CALFACTD_5   ((uint32_t)0x00200000) /*!< Calibration factors_5 in differential data */
//#define ADC_CALFACT_CALFACTD_6   ((uint32_t)0x00400000) /*!< Calibration factors_6 in differential data */

///********************  Bit definition for ADC_CTRL3 register  ********************/
//#define ADC_CTRL3_RES       ((uint32_t)0x00000003) /*!< Resolution data */
//#define ADC_CTRL3_RES_0     ((uint32_t)0x00000001) /*!< Resolution_0 data */
//#define ADC_CTRL3_RES_1     ((uint32_t)0x00000002) /*!< Resolution_1 data */

//#define ADC_CTRL3_CALDIF     ((uint32_t)0x00000004) /*!< Differential mode for calibration enable */
//#define ADC_CTRL3_CALALD     ((uint32_t)0x00000008) /*!< Differential mode for calibration auto reload enable */
//#define ADC_CTRL3_CKMOD      ((uint32_t)0x00000010) /*!< Clock mode selection */
//#define ADC_CTRL3_RDY        ((uint32_t)0x00000020) /*!< Ready flag */
//#define ADC_CTRL3_PDRDY      ((uint32_t)0x00000040) /*!< Powerdown ready flag */
//#define ADC_CTRL3_BPCAL      ((uint32_t)0x00000080) /*!< Bypass calibration */
//#define ADC_CTRL3_ENDCAIEN      ((uint32_t)0x00000100) /*!< Interrupt enable for any regular channels */
//#define ADC_CTRL3_JENDCAIEN      ((uint32_t)0x00000200) /*!< Interrupt enable for any injected channels */
//#define ADC_CTRL3_DPWMOD         ((uint32_t)0x00000400) /*!< Deep Power Mode */
//#define ADC_CTRL3_VBATMEN        ((uint32_t)0x00000800) /*!< Vbat monitor enable */

///********************  Bit definition for ADC_SAMPT3 register  ********************/
//#define ADC_SAMPT3_SAMP18   ((uint32_t)0x00000007) /*!< SMP9[2:0] bits (Channel 9 Sample time selection) */
//#define ADC_SAMPT3_SAMP18_0 ((uint32_t)0x00000001) /*!< Bit 0 */
//#define ADC_SAMPT3_SAMP18_1 ((uint32_t)0x00000002) /*!< Bit 1 */
//#define ADC_SAMPT3_SAMP18_2 ((uint32_t)0x00000004) /*!< Bit 2 */

//#define ADC_SAMPT3_SAMPSEL  ((uint32_t)0x00000008) /*!< Sample time selection */


/******************************************************************************/
/*                                                                            */
/*                      Digital to Analog Converter                           */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DAC_CTRL register  ********************/
#define DAC_CTRL_CHEN ((uint32_t)0x00000001) /*!< DAC channel enable */
#define DAC_CTRL_BEN  ((uint32_t)0x00000002) /*!< DAC channel output buffer enable */
#define DAC_CTRL_TEN  ((uint32_t)0x00000004) /*!< DAC channel Trigger enable */

#define DAC_CTRL_TSEL   ((uint32_t)0x00000038) /*!< TSEL[2:0] (DAC channel Trigger selection) */
#define DAC_CTRL_TSEL_0 ((uint32_t)0x00000008) /*!< Bit 0 */
#define DAC_CTRL_TSEL_1 ((uint32_t)0x00000010) /*!< Bit 1 */
#define DAC_CTRL_TSEL_2 ((uint32_t)0x00000020) /*!< Bit 2 */

#define DAC_CTRL_WEN   ((uint32_t)0x000000C0) /*!< WEN[1:0] (DAC channel noise/triangle wave generation enable) */
#define DAC_CTRL_WEN_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define DAC_CTRL_WEN_1 ((uint32_t)0x00000080) /*!< Bit 1 */

#define DAC_CTRL_MASEL   ((uint32_t)0x00000F00) /*!< MASEL [3:0] (DAC channel Mask/Amplitude selector) */
#define DAC_CTRL_MASEL_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define DAC_CTRL_MASEL_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define DAC_CTRL_MASEL_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define DAC_CTRL_MASEL_3 ((uint32_t)0x00000800) /*!< Bit 3 */

#define DAC_CTRL_DMAEN ((uint32_t)0x00001000) /*!< DAC channel DMA enable */



/*****************  Bit definition for DAC_SOTTR register  ******************/
#define DAC_SOTTR_TREN ((uint8_t)0x01) /*!< DAC channel software trigger */


/*****************  Bit definition for DAC_DR12CH register  ******************/
#define DAC_DR12CH_DACCHD ((uint16_t)0x0FFF) /*!< DAC channel 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12CH register  ******************/
#define DAC_DL12CH_DACCHD ((uint16_t)0xFFF0) /*!< DAC channel 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8CH register  ******************/
#define DAC_DR8CH_DACCHD ((uint8_t)0xFF) /*!< DAC channel 8-bit Right aligned data */




/*******************  Bit definition for DAC_DATO register  *******************/
#define DAC_DATO_DACCHDO ((uint16_t)0x0FFF) /*!< DAC channel data output */




/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for TIM_CTRL1 register  ********************/
#define TIM_CTRL1_CNTEN ((uint32_t)0x00000001) /*!< Counter enable */
#define TIM_CTRL1_UPDIS ((uint32_t)0x00000002) /*!< Update disable */
#define TIM_CTRL1_UPRS  ((uint32_t)0x00000004) /*!< Update request source */
#define TIM_CTRL1_ONEPM ((uint32_t)0x00000008) /*!< One pulse mode */
#define TIM_CTRL1_DIR   ((uint32_t)0x00000010) /*!< Direction */

#define TIM_CTRL1_CAMSEL   ((uint32_t)0x00000060) /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CTRL1_CAMSEL_0 ((uint32_t)0x00000020) /*!< Bit 0 */
#define TIM_CTRL1_CAMSEL_1 ((uint32_t)0x00000040) /*!< Bit 1 */

#define TIM_CTRL1_ARPEN ((uint32_t)0x00000080) /*!< Auto-reload preload enable */

#define TIM_CTRL1_CLKD   ((uint32_t)0x00000300) /*!< CKD[1:0] bits (clock division) */
#define TIM_CTRL1_CLKD_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define TIM_CTRL1_CLKD_1 ((uint32_t)0x00000200) /*!< Bit 1 */

#define TIM_CTRL1_IOMBKPEN ((uint32_t)0x00000400) /*!< Break_in selection from IOM/COMP */
#define TIM_CTRL1_C1SEL    ((uint32_t)0x00000800) /*!< Channel 1 selection from IOM/COMP */
#define TIM_CTRL1_C2SEL    ((uint32_t)0x00001000) /*!< Channel 2 selection from IOM/COMP */
#define TIM_CTRL1_C3SEL    ((uint32_t)0x00002000) /*!< Channel 3 selection from IOM/COMP */
#define TIM_CTRL1_C4SEL    ((uint32_t)0x00004000) /*!< Channel 4 selection from IOM/COMP */
#define TIM_CTRL1_CLRSEL   ((uint32_t)0x00008000) /*!< OCxRef selection from ETR/COMP */

#define TIM_CTRL1_LBKPEN ((uint32_t)0x00010000) /*!< LOCKUP as bkp Enable*/
#define TIM_CTRL1_PBKPEN ((uint32_t)0x00020000) /*!< PVD as bkp Enable */

/*******************  Bit definition for TIM_CTRL2 register  ********************/
#define TIM_CTRL2_CCPCTL ((uint32_t)0x00000001) /*!< Capture/Compare Preloaded Control */
#define TIM_CTRL2_CCUSEL ((uint32_t)0x00000004) /*!< Capture/Compare Control Update Selection */
#define TIM_CTRL2_CCDSEL ((uint32_t)0x00000008) /*!< Capture/Compare DMA Selection */

#define TIM_CTRL2_MMSEL   ((uint32_t)0x00000070) /*!< MMS[2:0] bits (Master Mode Selection) */
#define TIM_CTRL2_MMSEL_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define TIM_CTRL2_MMSEL_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define TIM_CTRL2_MMSEL_2 ((uint32_t)0x00000040) /*!< Bit 2 */

#define TIM_CTRL2_TI1SEL ((uint32_t)0x00000080) /*!< TI1 Selection */
#define TIM_CTRL2_OI1    ((uint32_t)0x00000100) /*!< Output Idle state 1 (OC1 output) */
#define TIM_CTRL2_OI1N   ((uint32_t)0x00000200) /*!< Output Idle state 1 (OC1N output) */
#define TIM_CTRL2_OI2    ((uint32_t)0x00000400) /*!< Output Idle state 2 (OC2 output) */
#define TIM_CTRL2_OI2N   ((uint32_t)0x00000800) /*!< Output Idle state 2 (OC2N output) */
#define TIM_CTRL2_OI3    ((uint32_t)0x00001000) /*!< Output Idle state 3 (OC3 output) */
#define TIM_CTRL2_OI3N   ((uint32_t)0x00002000) /*!< Output Idle state 3 (OC3N output) */
#define TIM_CTRL2_OI4    ((uint32_t)0x00004000) /*!< Output Idle state 4 (OC4 output) */

#define TIM_CTRL2_OI5 ((uint32_t)0x00010000) /*!< Output Idle state 5 (OC5 output) */
#define TIM_CTRL2_OI6 ((uint32_t)0x00040000) /*!< Output Idle state 6 (OC6 output) */

/*******************  Bit definition for TIM_SMCTRL register  *******************/
#define TIM_SMCTRL_SMSEL   ((uint16_t)0x0007) /*!< SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCTRL_SMSEL_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define TIM_SMCTRL_SMSEL_1 ((uint16_t)0x0002) /*!< Bit 1 */
#define TIM_SMCTRL_SMSEL_2 ((uint16_t)0x0004) /*!< Bit 2 */

#define TIM_SMCTRL_TSEL   ((uint16_t)0x0070) /*!< TS[2:0] bits (Trigger selection) */
#define TIM_SMCTRL_TSEL_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define TIM_SMCTRL_TSEL_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define TIM_SMCTRL_TSEL_2 ((uint16_t)0x0040) /*!< Bit 2 */

#define TIM_SMCTRL_MSMD ((uint16_t)0x0080) /*!< Master/slave mode */

#define TIM_SMCTRL_EXTF   ((uint16_t)0x0F00) /*!< ETF[3:0] bits (External trigger filter) */
#define TIM_SMCTRL_EXTF_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define TIM_SMCTRL_EXTF_1 ((uint16_t)0x0200) /*!< Bit 1 */
#define TIM_SMCTRL_EXTF_2 ((uint16_t)0x0400) /*!< Bit 2 */
#define TIM_SMCTRL_EXTF_3 ((uint16_t)0x0800) /*!< Bit 3 */

#define TIM_SMCTRL_EXTPS   ((uint16_t)0x3000) /*!< ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCTRL_EXTPS_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define TIM_SMCTRL_EXTPS_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define TIM_SMCTRL_EXCEN ((uint16_t)0x4000) /*!< External clock enable */
#define TIM_SMCTRL_EXTP  ((uint16_t)0x8000) /*!< External trigger polarity */

/*******************  Bit definition for TIM_DINTEN register  *******************/
#define TIM_DINTEN_UIEN   ((uint16_t)0x0001) /*!< Update interrupt enable */
#define TIM_DINTEN_CC1IEN ((uint16_t)0x0002) /*!< Capture/Compare 1 interrupt enable */
#define TIM_DINTEN_CC2IEN ((uint16_t)0x0004) /*!< Capture/Compare 2 interrupt enable */
#define TIM_DINTEN_CC3IEN ((uint16_t)0x0008) /*!< Capture/Compare 3 interrupt enable */
#define TIM_DINTEN_CC4IEN ((uint16_t)0x0010) /*!< Capture/Compare 4 interrupt enable */
#define TIM_DINTEN_COMIEN ((uint16_t)0x0020) /*!< COM interrupt enable */
#define TIM_DINTEN_TIEN   ((uint16_t)0x0040) /*!< Trigger interrupt enable */
#define TIM_DINTEN_BIEN   ((uint16_t)0x0080) /*!< Break interrupt enable */
#define TIM_DINTEN_UDEN   ((uint16_t)0x0100) /*!< Update DMA request enable */
#define TIM_DINTEN_CC1DEN ((uint16_t)0x0200) /*!< Capture/Compare 1 DMA request enable */
#define TIM_DINTEN_CC2DEN ((uint16_t)0x0400) /*!< Capture/Compare 2 DMA request enable */
#define TIM_DINTEN_CC3DEN ((uint16_t)0x0800) /*!< Capture/Compare 3 DMA request enable */
#define TIM_DINTEN_CC4DEN ((uint16_t)0x1000) /*!< Capture/Compare 4 DMA request enable */
#define TIM_DINTEN_COMDEN ((uint16_t)0x2000) /*!< COM DMA request enable */
#define TIM_DINTEN_TDEN   ((uint16_t)0x4000) /*!< Trigger DMA request enable */

/********************  Bit definition for TIM_STS register  ********************/
#define TIM_STS_UDITF  ((uint32_t)0x00000001) /*!< Update interrupt Flag */
#define TIM_STS_CC1ITF ((uint32_t)0x00000002) /*!< Capture/Compare 1 interrupt Flag */
#define TIM_STS_CC2ITF ((uint32_t)0x00000004) /*!< Capture/Compare 2 interrupt Flag */
#define TIM_STS_CC3ITF ((uint32_t)0x00000008) /*!< Capture/Compare 3 interrupt Flag */
#define TIM_STS_CC4ITF ((uint32_t)0x00000010) /*!< Capture/Compare 4 interrupt Flag */
#define TIM_STS_COMITF ((uint32_t)0x00000020) /*!< COM interrupt Flag */
#define TIM_STS_TITF   ((uint32_t)0x00000040) /*!< Trigger interrupt Flag */
#define TIM_STS_BITF   ((uint32_t)0x00000080) /*!< Break interrupt Flag */
#define TIM_STS_CC1OCF ((uint32_t)0x00000200) /*!< Capture/Compare 1 Overcapture Flag */
#define TIM_STS_CC2OCF ((uint32_t)0x00000400) /*!< Capture/Compare 2 Overcapture Flag */
#define TIM_STS_CC3OCF ((uint32_t)0x00000800) /*!< Capture/Compare 3 Overcapture Flag */
#define TIM_STS_CC4OCF ((uint32_t)0x00001000) /*!< Capture/Compare 4 Overcapture Flag */

#define TIM_STS_CC5ITF ((uint32_t)0x00010000) /*!< Capture/Compare 5 interrupt Flag */
#define TIM_STS_CC6ITF ((uint32_t)0x00020000) /*!< Capture/Compare 6 interrupt Flag */

/*******************  Bit definition for TIM_EVTGEN register  ********************/
#define TIM_EVTGEN_UDGN   ((uint8_t)0x01) /*!< Update Generation */
#define TIM_EVTGEN_CC1GN  ((uint8_t)0x02) /*!< Capture/Compare 1 Generation */
#define TIM_EVTGEN_CC2GN  ((uint8_t)0x04) /*!< Capture/Compare 2 Generation */
#define TIM_EVTGEN_CC3GN  ((uint8_t)0x08) /*!< Capture/Compare 3 Generation */
#define TIM_EVTGEN_CC4GN  ((uint8_t)0x10) /*!< Capture/Compare 4 Generation */
#define TIM_EVTGEN_CCUDGN ((uint8_t)0x20) /*!< Capture/Compare Control Update Generation */
#define TIM_EVTGEN_TGN    ((uint8_t)0x40) /*!< Trigger Generation */
#define TIM_EVTGEN_BGN    ((uint8_t)0x80) /*!< Break Generation */

/******************  Bit definition for TIM_CCMOD1 register  *******************/
#define TIM_CCMOD1_CC1SEL   ((uint16_t)0x0003) /*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMOD1_CC1SEL_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define TIM_CCMOD1_CC1SEL_1 ((uint16_t)0x0002) /*!< Bit 1 */

#define TIM_CCMOD1_OC1FEN ((uint16_t)0x0004) /*!< Output Compare 1 Fast enable */
#define TIM_CCMOD1_OC1PEN ((uint16_t)0x0008) /*!< Output Compare 1 Preload enable */

#define TIM_CCMOD1_OC1M   ((uint16_t)0x0070) /*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMOD1_OC1M_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define TIM_CCMOD1_OC1M_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define TIM_CCMOD1_OC1M_2 ((uint16_t)0x0040) /*!< Bit 2 */

#define TIM_CCMOD1_OC1CEN ((uint16_t)0x0080) /*!< Output Compare 1Clear Enable */

#define TIM_CCMOD1_CC2SEL   ((uint16_t)0x0300) /*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMOD1_CC2SEL_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define TIM_CCMOD1_CC2SEL_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define TIM_CCMOD1_OC2FEN ((uint16_t)0x0400) /*!< Output Compare 2 Fast enable */
#define TIM_CCMOD1_OC2PEN ((uint16_t)0x0800) /*!< Output Compare 2 Preload enable */

#define TIM_CCMOD1_OC2M   ((uint16_t)0x7000) /*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMOD1_OC2M_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define TIM_CCMOD1_OC2M_1 ((uint16_t)0x2000) /*!< Bit 1 */
#define TIM_CCMOD1_OC2M_2 ((uint16_t)0x4000) /*!< Bit 2 */

#define TIM_CCMOD1_OC2CEN ((uint16_t)0x8000) /*!< Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMOD1_IC1PSC   ((uint16_t)0x000C) /*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMOD1_IC1PSC_0 ((uint16_t)0x0004) /*!< Bit 0 */
#define TIM_CCMOD1_IC1PSC_1 ((uint16_t)0x0008) /*!< Bit 1 */

#define TIM_CCMOD1_IC1F   ((uint16_t)0x00F0) /*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMOD1_IC1F_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define TIM_CCMOD1_IC1F_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define TIM_CCMOD1_IC1F_2 ((uint16_t)0x0040) /*!< Bit 2 */
#define TIM_CCMOD1_IC1F_3 ((uint16_t)0x0080) /*!< Bit 3 */

#define TIM_CCMOD1_IC2PSC   ((uint16_t)0x0C00) /*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMOD1_IC2PSC_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define TIM_CCMOD1_IC2PSC_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define TIM_CCMOD1_IC2F   ((uint16_t)0xF000) /*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMOD1_IC2F_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define TIM_CCMOD1_IC2F_1 ((uint16_t)0x2000) /*!< Bit 1 */
#define TIM_CCMOD1_IC2F_2 ((uint16_t)0x4000) /*!< Bit 2 */
#define TIM_CCMOD1_IC2F_3 ((uint16_t)0x8000) /*!< Bit 3 */

/******************  Bit definition for TIM_CCMOD2 register  *******************/
#define TIM_CCMOD2_CC3SEL   ((uint16_t)0x0003) /*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMOD2_CC3SEL_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define TIM_CCMOD2_CC3SEL_1 ((uint16_t)0x0002) /*!< Bit 1 */

#define TIM_CCMOD2_OC3FEN ((uint16_t)0x0004) /*!< Output Compare 3 Fast enable */
#define TIM_CCMOD2_OC3PEN ((uint16_t)0x0008) /*!< Output Compare 3 Preload enable */

#define TIM_CCMOD2_OC3MD   ((uint16_t)0x0070) /*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMOD2_OC3MD_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define TIM_CCMOD2_OC3MD_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define TIM_CCMOD2_OC3MD_2 ((uint16_t)0x0040) /*!< Bit 2 */

#define TIM_CCMOD2_OC3CEN ((uint16_t)0x0080) /*!< Output Compare 3 Clear Enable */

#define TIM_CCMOD2_CC4SEL   ((uint16_t)0x0300) /*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMOD2_CC4SEL_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define TIM_CCMOD2_CC4SEL_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define TIM_CCMOD2_OC4FEN ((uint16_t)0x0400) /*!< Output Compare 4 Fast enable */
#define TIM_CCMOD2_OC4PEN ((uint16_t)0x0800) /*!< Output Compare 4 Preload enable */

#define TIM_CCMOD2_OC4MD   ((uint16_t)0x7000) /*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMOD2_OC4MD_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define TIM_CCMOD2_OC4MD_1 ((uint16_t)0x2000) /*!< Bit 1 */
#define TIM_CCMOD2_OC4MD_2 ((uint16_t)0x4000) /*!< Bit 2 */

#define TIM_CCMOD2_OC4CEN ((uint16_t)0x8000) /*!< Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMOD2_IC3PSC   ((uint16_t)0x000C) /*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMOD2_IC3PSC_0 ((uint16_t)0x0004) /*!< Bit 0 */
#define TIM_CCMOD2_IC3PSC_1 ((uint16_t)0x0008) /*!< Bit 1 */

#define TIM_CCMOD2_IC3F   ((uint16_t)0x00F0) /*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMOD2_IC3F_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define TIM_CCMOD2_IC3F_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define TIM_CCMOD2_IC3F_2 ((uint16_t)0x0040) /*!< Bit 2 */
#define TIM_CCMOD2_IC3F_3 ((uint16_t)0x0080) /*!< Bit 3 */

#define TIM_CCMOD2_IC4PSC   ((uint16_t)0x0C00) /*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMOD2_IC4PSC_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define TIM_CCMOD2_IC4PSC_1 ((uint16_t)0x0800) /*!< Bit 1 */

#define TIM_CCMOD2_IC4F   ((uint16_t)0xF000) /*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMOD2_IC4F_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define TIM_CCMOD2_IC4F_1 ((uint16_t)0x2000) /*!< Bit 1 */
#define TIM_CCMOD2_IC4F_2 ((uint16_t)0x4000) /*!< Bit 2 */
#define TIM_CCMOD2_IC4F_3 ((uint16_t)0x8000) /*!< Bit 3 */

/******************  Bit definition for TIM_CCMOD3 register  *******************/
#define TIM_CCMOD3_OC5FEN ((uint16_t)0x0004) /*!< Output Compare 5 Fast enable */
#define TIM_CCMOD3_OC5PEN ((uint16_t)0x0008) /*!< Output Compare 5 Preload enable */

#define TIM_CCMOD3_OC5MD   ((uint16_t)0x0070) /*!< OC5M[2:0] bits (Output Compare 5 Mode) */
#define TIM_CCMOD3_OC5MD_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define TIM_CCMOD3_OC5MD_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define TIM_CCMOD3_OC5MD_2 ((uint16_t)0x0040) /*!< Bit 2 */

#define TIM_CCMOD3_OC5CEN ((uint16_t)0x0080) /*!< Output Compare 5Clear Enable */

#define TIM_CCMOD3_OC6FEN ((uint16_t)0x0400) /*!< Output Compare 6 Fast enable */
#define TIM_CCMOD3_OC6PEN ((uint16_t)0x0800) /*!< Output Compare 6 Preload enable */

#define TIM_CCMOD3_OC6MD   ((uint16_t)0x7000) /*!< OC6M[2:0] bits (Output Compare 6 Mode) */
#define TIM_CCMOD3_OC6MD_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define TIM_CCMOD3_OC6MD_1 ((uint16_t)0x2000) /*!< Bit 1 */
#define TIM_CCMOD3_OC6MD_2 ((uint16_t)0x4000) /*!< Bit 2 */

#define TIM_CCMOD3_OC6CEN ((uint16_t)0x8000) /*!< Output Compare 6 Clear Enable */

/*----------------------------------------------------------------------------*/

/*******************  Bit definition for TIM_CCEN register  *******************/
#define TIM_CCEN_CC1EN  ((uint32_t)0x00000001) /*!< Capture/Compare 1 output enable */
#define TIM_CCEN_CC1P   ((uint32_t)0x00000002) /*!< Capture/Compare 1 output Polarity */
#define TIM_CCEN_CC1NEN ((uint32_t)0x00000004) /*!< Capture/Compare 1 Complementary output enable */
#define TIM_CCEN_CC1NP  ((uint32_t)0x00000008) /*!< Capture/Compare 1 Complementary output Polarity */
#define TIM_CCEN_CC2EN  ((uint32_t)0x00000010) /*!< Capture/Compare 2 output enable */
#define TIM_CCEN_CC2P   ((uint32_t)0x00000020) /*!< Capture/Compare 2 output Polarity */
#define TIM_CCEN_CC2NEN ((uint32_t)0x00000040) /*!< Capture/Compare 2 Complementary output enable */
#define TIM_CCEN_CC2NP  ((uint32_t)0x00000080) /*!< Capture/Compare 2 Complementary output Polarity */
#define TIM_CCEN_CC3EN  ((uint32_t)0x00000100) /*!< Capture/Compare 3 output enable */
#define TIM_CCEN_CC3P   ((uint32_t)0x00000200) /*!< Capture/Compare 3 output Polarity */
#define TIM_CCEN_CC3NEN ((uint32_t)0x00000400) /*!< Capture/Compare 3 Complementary output enable */
#define TIM_CCEN_CC3NP  ((uint32_t)0x00000800) /*!< Capture/Compare 3 Complementary output Polarity */
#define TIM_CCEN_CC4EN  ((uint32_t)0x00001000) /*!< Capture/Compare 4 output enable */
#define TIM_CCEN_CC4P   ((uint32_t)0x00002000) /*!< Capture/Compare 4 output Polarity */

#define TIM_CCEN_CC5EN ((uint32_t)0x00010000) /*!< Capture/Compare 5 output enable */
#define TIM_CCEN_CC5P  ((uint32_t)0x00020000) /*!< Capture/Compare 5 output Polarity */
#define TIM_CCEN_CC6EN ((uint32_t)0x00100000) /*!< Capture/Compare 6 output enable */
#define TIM_CCEN_CC6P  ((uint32_t)0x00200000) /*!< Capture/Compare 6 output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT ((uint16_t)0xFFFF) /*!< Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC ((uint16_t)0xFFFF) /*!< Prescaler Value */

/*******************  Bit definition for TIM_AR register  ********************/
#define TIM_AR_AR ((uint16_t)0xFFFF) /*!< actual auto-reload Value */

/*******************  Bit definition for TIM_REPCNT register  ********************/
#define TIM_REPCNT_REPCNT ((uint8_t)0xFF) /*!< Repetition Counter Value */

/*******************  Bit definition for TIM_CCDAT1 register  *******************/
#define TIM_CCDAT1_CCDAT1 ((uint16_t)0xFFFF) /*!< Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCDAT2 register  *******************/
#define TIM_CCDAT2_CCDAT2 ((uint16_t)0xFFFF) /*!< Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCDAT3 register  *******************/
#define TIM_CCDAT3_CCDAT3 ((uint16_t)0xFFFF) /*!< Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCDAT4 register  *******************/
#define TIM_CCDAT4_CCDAT4 ((uint16_t)0xFFFF) /*!< Capture/Compare 4 Value */

/*******************  Bit definition for TIM_CCDAT5 register  *******************/
#define TIM_CCDAT5_CCDAT5 ((uint16_t)0xFFFF) /*!< Capture/Compare 5 Value */

/*******************  Bit definition for TIM_CCDAT6 register  *******************/
#define TIM_CCDAT6_CCDAT6 ((uint16_t)0xFFFF) /*!< Capture/Compare 6 Value */

/*******************  Bit definition for TIM_BKDT register  *******************/
#define TIM_BKDT_DTGN   ((uint16_t)0x00FF) /*!< DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BKDT_DTGN_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define TIM_BKDT_DTGN_1 ((uint16_t)0x0002) /*!< Bit 1 */
#define TIM_BKDT_DTGN_2 ((uint16_t)0x0004) /*!< Bit 2 */
#define TIM_BKDT_DTGN_3 ((uint16_t)0x0008) /*!< Bit 3 */
#define TIM_BKDT_DTGN_4 ((uint16_t)0x0010) /*!< Bit 4 */
#define TIM_BKDT_DTGN_5 ((uint16_t)0x0020) /*!< Bit 5 */
#define TIM_BKDT_DTGN_6 ((uint16_t)0x0040) /*!< Bit 6 */
#define TIM_BKDT_DTGN_7 ((uint16_t)0x0080) /*!< Bit 7 */

#define TIM_BKDT_LCKCFG   ((uint16_t)0x0300) /*!< LOCK[1:0] bits (Lock Configuration) */
#define TIM_BKDT_LCKCFG_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define TIM_BKDT_LCKCFG_1 ((uint16_t)0x0200) /*!< Bit 1 */

#define TIM_BKDT_OSSI ((uint16_t)0x0400) /*!< Off-State Selection for Idle mode */
#define TIM_BKDT_OSSR ((uint16_t)0x0800) /*!< Off-State Selection for Run mode */
#define TIM_BKDT_BKEN ((uint16_t)0x1000) /*!< Break enable */
#define TIM_BKDT_BKP  ((uint16_t)0x2000) /*!< Break Polarity */
#define TIM_BKDT_AOEN ((uint16_t)0x4000) /*!< Automatic Output enable */
#define TIM_BKDT_MOEN ((uint16_t)0x8000) /*!< Main Output enable */

/*******************  Bit definition for TIM_DCTRL register  ********************/
#define TIM_DCTRL_DBADDR   ((uint16_t)0x001F) /*!< DBA[4:0] bits (DMA Base Address) */
#define TIM_DCTRL_DBADDR_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define TIM_DCTRL_DBADDR_1 ((uint16_t)0x0002) /*!< Bit 1 */
#define TIM_DCTRL_DBADDR_2 ((uint16_t)0x0004) /*!< Bit 2 */
#define TIM_DCTRL_DBADDR_3 ((uint16_t)0x0008) /*!< Bit 3 */
#define TIM_DCTRL_DBADDR_4 ((uint16_t)0x0010) /*!< Bit 4 */

#define TIM_DCTRL_DBLEN   ((uint16_t)0x1F00) /*!< DBL[4:0] bits (DMA Burst Length) */
#define TIM_DCTRL_DBLEN_0 ((uint16_t)0x0100) /*!< Bit 0 */
#define TIM_DCTRL_DBLEN_1 ((uint16_t)0x0200) /*!< Bit 1 */
#define TIM_DCTRL_DBLEN_2 ((uint16_t)0x0400) /*!< Bit 2 */
#define TIM_DCTRL_DBLEN_3 ((uint16_t)0x0800) /*!< Bit 3 */
#define TIM_DCTRL_DBLEN_4 ((uint16_t)0x1000) /*!< Bit 4 */

/*******************  Bit definition for TIM_DADDR register  *******************/
#define TIM_DADDR_BURST ((uint16_t)0xFFFF) /*!< DMA register for burst accesses */
/******************************************************************************/
/*                                                                            */
/*                         Low Power Timer (LPTTIM)                           */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for LPTIM_INTSTS register  *******************/
#define LPTIM_INTSTS_CMPM                       ((uint32_t)0x00000001)       /*!< Compare match */
#define LPTIM_INTSTS_ARRM                      ((uint32_t)0x00000002)       /*!< Autoreload match */
#define LPTIM_INTSTS_EXTRIG                   ((uint32_t)0x00000004)       /*!< External trigger edge event */
#define LPTIM_INTSTS_CMPUPD                      ((uint32_t)0x00000008)       /*!< Compare register update OK */
#define LPTIM_INTSTS_ARRUPD                      ((uint32_t)0x00000010)       /*!< Autoreload register update OK */
#define LPTIM_INTSTS_UP                         ((uint32_t)0x00000020)       /*!< Counter direction change down to up */
#define LPTIM_INTSTS_DOWN                       ((uint32_t)0x00000040)       /*!< Counter direction change up to down */

/******************  Bit definition for LPTIM_INTCLR register  *******************/
#define LPTIM_INTCLR_CMPMCF                     ((uint32_t)0x00000001)       /*!< Compare match Clear Flag */
#define LPTIM_INTCLR_ARRMCF                     ((uint32_t)0x00000002)       /*!< Autoreload match Clear Flag */
#define LPTIM_INTCLR_EXTRIGCF                  ((uint32_t)0x00000004)       /*!< External trigger edge event Clear Flag */
#define LPTIM_INTCLR_CMPUPDCF                    ((uint32_t)0x00000008)       /*!< Compare register update OK Clear Flag */
#define LPTIM_INTCLR_ARRUPDCF                    ((uint32_t)0x00000010)       /*!< Autoreload register update OK Clear Flag */
#define LPTIM_INTCLR_UPCF                       ((uint32_t)0x00000020)       /*!< Counter direction change down to up Clear Flag */
#define LPTIM_INTCLR_DOWNCF                     ((uint32_t)0x00000040)       /*!< Counter direction change up to down Clear Flag */

/******************  Bit definition for LPTIM_INTEN register ********************/
#define LPTIM_INTEN_CMPMIE                     ((uint32_t)0x00000001)       /*!< Compare match Interrupt Enable */
#define LPTIM_INTEN_ARRMIE                    ((uint32_t)0x00000002)       /*!< Autoreload match Interrupt Enable */
#define LPTIM_INTEN_EXTRIGIE                  ((uint32_t)0x00000004)       /*!< External trigger edge event Interrupt Enable */
#define LPTIM_INTEN_CMPUPDIE                   ((uint32_t)0x00000008)       /*!< Compare register update OK Interrupt Enable */
#define LPTIM_INTEN_ARRUPDIE                   ((uint32_t)0x00000010)       /*!< Autoreload register update OK Interrupt Enable */
#define LPTIM_INTEN_UPIE                       ((uint32_t)0x00000020)       /*!< Counter direction change down to up Interrupt Enable */
#define LPTIM_INTEN_DOWNIE                    ((uint32_t)0x00000040)       /*!< Counter direction change up to down Interrupt Enable */

/******************  Bit definition for LPTIM_CFG register *******************/
#define LPTIM_CFG_CLKSEL                     ((uint32_t)0x00000001)       /*!< Clock selector */

#define LPTIM_CFG_CLKPOL                     ((uint32_t)0x00000006)       /*!< CLKP[1:0] bits (Clock polarity) */
#define LPTIM_CFG_CLKPOL_0                   ((uint32_t)0x00000002)       /*!< 0x00000002 */
#define LPTIM_CFG_CLKPOL_1                   ((uint32_t)0x00000004)       /*!< 0x00000004 */

#define LPTIM_CFG_CLKFLT                     ((uint32_t)0x00000018)       /*!< CFGDFFEXT[1:0] bits (Configurable digital filter for external clock) */
#define LPTIM_CFG_CLKFLT_0                   ((uint32_t)0x00000008)       /*!< 0x00000008 */
#define LPTIM_CFG_CLKFLT_1                   ((uint32_t)0x00000010)       /*!< 0x00000010 */

#define LPTIM_CFG_TRIGFLT                    ((uint32_t)0x000000C0)       /*!< CFGDFFTRG[1:0] bits (Configurable digital filter for trigger) */
#define LPTIM_CFG_TRIGFLT_0                  ((uint32_t)0x00000040)       /*!< 0x00000040 */
#define LPTIM_CFG_TRIGFLT_1                  ((uint32_t)0x00000080)       /*!< 0x00000080 */

#define LPTIM_CFG_CLKPRE                     ((uint32_t)0x00000E00)       /*!< CLKPRE[2:0] bits (Clock prescaler) */
#define LPTIM_CFG_CLKPRE_0                   ((uint32_t)0x00000200)       /*!< 0x00000200 */
#define LPTIM_CFG_CLKPRE_1                   ((uint32_t)0x00000400)       /*!< 0x00000400 */
#define LPTIM_CFG_CLKPRE_2                   ((uint32_t)0x00000800)       /*!< 0x00000800 */

#define LPTIM_CFG_TRGSEL                   ((uint32_t)0x0000E000)       /*!< TRGS[2:0]] bits (Trigger selector) */
#define LPTIM_CFG_TRGSEL_0                 ((uint32_t)0x00002000)       /*!< 0x00002000 */
#define LPTIM_CFG_TRGSEL_1                 ((uint32_t)0x00004000)       /*!< 0x00004000 */
#define LPTIM_CFG_TRGSEL_2                 ((uint32_t)0x00008000)       /*!< 0x00008000 */

#define LPTIM_CFG_TRGEN                    ((uint32_t)0x00060000)       /*!< TRGEN[1:0] bits (Trigger enable and polarity) */
#define LPTIM_CFG_TRGEN_0                  ((uint32_t)0x00020000)       /*!< 0x00020000 */
#define LPTIM_CFG_TRGEN_1                  ((uint32_t)0x00040000)       /*!< 0x00040000 */

#define LPTIM_CFG_TIMOUTEN                  ((uint32_t)0x00080000)       /*!< Timout enable */
#define LPTIM_CFG_WAVE                      ((uint32_t)0x00100000)       /*!< Waveform shape */
#define LPTIM_CFG_WAVEPOL                   ((uint32_t)0x00200000)       /*!< Waveform shape polarity */
#define LPTIM_CFG_RELOAD                    ((uint32_t)0x00400000)       /*!< Reg update mode */
#define LPTIM_CFG_CNTMEN                    ((uint32_t)0x00800000)       /*!< Counter mode enable */
#define LPTIM_CFG_ENC                       ((uint32_t)0x01000000)       /*!< Encoder mode enable */
#define LPTIM_CFG_NENC                      ((uint32_t)0x02000000)       /*!< NONEncoder mode enable */
/******************  Bit definition for LPTIM_CTRL register  ********************/
#define LPTIM_CTRL_LPTIMEN                      ((uint32_t)0x000000001)      /*!< LPTIMer enable */
#define LPTIM_CTRL_SNGMST                       ((uint32_t)0x000000002)      /*!< Timer start in single mode */
#define LPTIM_CTRL_TSTCM                        ((uint32_t)0x000000004)      /*!< Timer start in continuous mode */

/******************  Bit definition for LPTIM_CMPT register  *******************/
#define LPTIM_COMP_CMPVAL                          ((uint16_t)0xFFFF)           /*!< Compare register */

/******************  Bit definition for LPTIM_AUTRLD register  *******************/
#define LPTIM_ARR_ARRVAL                     ((uint16_t)0xFFFF)           /*!< Auto reload register */

/******************  Bit definition for LPTIM_CNT register  *******************/
#define LPTIM_CNT_CNTVAL                        ((uint16_t)0xFFFF)           /*!< Counter register */

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RTC_TSH register  *******************/
#define RTC_TSH_APM   ((uint32_t)0x00400000)
#define RTC_TSH_HOT   ((uint32_t)0x00300000)
#define RTC_TSH_HOT_0 ((uint32_t)0x00100000)
#define RTC_TSH_HOT_1 ((uint32_t)0x00200000)
#define RTC_TSH_HOU   ((uint32_t)0x000F0000)
#define RTC_TSH_HOU_0 ((uint32_t)0x00010000)
#define RTC_TSH_HOU_1 ((uint32_t)0x00020000)
#define RTC_TSH_HOU_2 ((uint32_t)0x00040000)
#define RTC_TSH_HOU_3 ((uint32_t)0x00080000)
#define RTC_TSH_MIT   ((uint32_t)0x00007000)
#define RTC_TSH_MIT_0 ((uint32_t)0x00001000)
#define RTC_TSH_MIT_1 ((uint32_t)0x00002000)
#define RTC_TSH_MIT_2 ((uint32_t)0x00004000)
#define RTC_TSH_MIU   ((uint32_t)0x00000F00)
#define RTC_TSH_MIU_0 ((uint32_t)0x00000100)
#define RTC_TSH_MIU_1 ((uint32_t)0x00000200)
#define RTC_TSH_MIU_2 ((uint32_t)0x00000400)
#define RTC_TSH_MIU_3 ((uint32_t)0x00000800)
#define RTC_TSH_SCT   ((uint32_t)0x00000070)
#define RTC_TSH_SCT_0 ((uint32_t)0x00000010)
#define RTC_TSH_SCT_1 ((uint32_t)0x00000020)
#define RTC_TSH_SCT_2 ((uint32_t)0x00000040)
#define RTC_TSH_SCU   ((uint32_t)0x0000000F)
#define RTC_TSH_SCU_0 ((uint32_t)0x00000001)
#define RTC_TSH_SCU_1 ((uint32_t)0x00000002)
#define RTC_TSH_SCU_2 ((uint32_t)0x00000004)
#define RTC_TSH_SCU_3 ((uint32_t)0x00000008)

/********************  Bits definition for RTC_DATE register  *******************/
#define RTC_DATE_YRT   ((uint32_t)0x00F00000)
#define RTC_DATE_YRT_0 ((uint32_t)0x00100000)
#define RTC_DATE_YRT_1 ((uint32_t)0x00200000)
#define RTC_DATE_YRT_2 ((uint32_t)0x00400000)
#define RTC_DATE_YRT_3 ((uint32_t)0x00800000)
#define RTC_DATE_YRU   ((uint32_t)0x000F0000)
#define RTC_DATE_YRU_0 ((uint32_t)0x00010000)
#define RTC_DATE_YRU_1 ((uint32_t)0x00020000)
#define RTC_DATE_YRU_2 ((uint32_t)0x00040000)
#define RTC_DATE_YRU_3 ((uint32_t)0x00080000)
#define RTC_DATE_WDU   ((uint32_t)0x0000E000)
#define RTC_DATE_WDU_0 ((uint32_t)0x00002000)
#define RTC_DATE_WDU_1 ((uint32_t)0x00004000)
#define RTC_DATE_WDU_2 ((uint32_t)0x00008000)
#define RTC_DATE_MOT   ((uint32_t)0x00001000)
#define RTC_DATE_MOU   ((uint32_t)0x00000F00)
#define RTC_DATE_MOU_0 ((uint32_t)0x00000100)
#define RTC_DATE_MOU_1 ((uint32_t)0x00000200)
#define RTC_DATE_MOU_2 ((uint32_t)0x00000400)
#define RTC_DATE_MOU_3 ((uint32_t)0x00000800)
#define RTC_DATE_DAT   ((uint32_t)0x00000030)
#define RTC_DATE_DAT_0 ((uint32_t)0x00000010)
#define RTC_DATE_DAT_1 ((uint32_t)0x00000020)
#define RTC_DATE_DAU   ((uint32_t)0x0000000F)
#define RTC_DATE_DAU_0 ((uint32_t)0x00000001)
#define RTC_DATE_DAU_1 ((uint32_t)0x00000002)
#define RTC_DATE_DAU_2 ((uint32_t)0x00000004)
#define RTC_DATE_DAU_3 ((uint32_t)0x00000008)

/********************  Bits definition for RTC_CTRL register  *******************/
#define RTC_CTRL_COEN     ((uint32_t)0x00800000)
#define RTC_CTRL_OUTSEL   ((uint32_t)0x00600000)
#define RTC_CTRL_OUTSEL_0 ((uint32_t)0x00200000)
#define RTC_CTRL_OUTSEL_1 ((uint32_t)0x00400000)
#define RTC_CTRL_OPOL     ((uint32_t)0x00100000)
#define RTC_CTRL_CALOSEL  ((uint32_t)0x00080000)
#define RTC_CTRL_BAKP     ((uint32_t)0x00040000)
#define RTC_CTRL_SU1H     ((uint32_t)0x00020000)
#define RTC_CTRL_AD1H     ((uint32_t)0x00010000)
#define RTC_CTRL_TSIEN    ((uint32_t)0x00008000)
#define RTC_CTRL_WTIEN    ((uint32_t)0x00004000)
#define RTC_CTRL_ALBIEN   ((uint32_t)0x00002000)
#define RTC_CTRL_ALAIEN   ((uint32_t)0x00001000)
#define RTC_CTRL_TSEN     ((uint32_t)0x00000800)
#define RTC_CTRL_WTEN     ((uint32_t)0x00000400)
#define RTC_CTRL_ALBEN    ((uint32_t)0x00000200)
#define RTC_CTRL_ALAEN    ((uint32_t)0x00000100)

#define RTC_CTRL_HFMT      ((uint32_t)0x00000040)
#define RTC_CTRL_BYPS      ((uint32_t)0x00000020)
#define RTC_CTRL_REFCLKEN  ((uint32_t)0x00000010)
#define RTC_CTRL_TEDGE     ((uint32_t)0x00000008)
#define RTC_CTRL_WKUPSEL   ((uint32_t)0x00000007)
#define RTC_CTRL_WKUPSEL_0 ((uint32_t)0x00000001)
#define RTC_CTRL_WKUPSEL_1 ((uint32_t)0x00000002)
#define RTC_CTRL_WKUPSEL_2 ((uint32_t)0x00000004)

/********************  Bits definition for RTC_INITSTS register  ******************/
#define RTC_INITSTS_RECPF  ((uint32_t)0x00010000)
#define RTC_INITSTS_TAM3F  ((uint32_t)0x00008000)
#define RTC_INITSTS_TAM2F  ((uint32_t)0x00004000)
#define RTC_INITSTS_TAM1F  ((uint32_t)0x00002000)
#define RTC_INITSTS_TISOVF ((uint32_t)0x00001000)
#define RTC_INITSTS_TISF   ((uint32_t)0x00000800)
#define RTC_INITSTS_WTF    ((uint32_t)0x00000400)
#define RTC_INITSTS_ALBF   ((uint32_t)0x00000200)
#define RTC_INITSTS_ALAF   ((uint32_t)0x00000100)
#define RTC_INITSTS_INITM  ((uint32_t)0x00000080)
#define RTC_INITSTS_INITF  ((uint32_t)0x00000040)
#define RTC_INITSTS_RSYF   ((uint32_t)0x00000020)
#define RTC_INITSTS_INITSF ((uint32_t)0x00000010)
#define RTC_INITSTS_SHOPF  ((uint32_t)0x00000008)
#define RTC_INITSTS_WTWF   ((uint32_t)0x00000004)
#define RTC_INITSTS_ALBWF  ((uint32_t)0x00000002)
#define RTC_INITSTS_ALAWF  ((uint32_t)0x00000001)

/********************  Bits definition for RTC_PRE register  *****************/
#define RTC_PRE_DIVA ((uint32_t)0x007F0000)
#define RTC_PRE_DIVS ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_WKUPT register  *****************/
#define RTC_WKUPT_WKUPT ((uint32_t)0x0000FFFF)


/********************  Bits definition for RTC_ALARMA register  ***************/
#define RTC_ALARMA_MASK4  ((uint32_t)0x80000000)
#define RTC_ALARMA_WKDSEL ((uint32_t)0x40000000)
#define RTC_ALARMA_DTT    ((uint32_t)0x30000000)
#define RTC_ALARMA_DTT_0  ((uint32_t)0x10000000)
#define RTC_ALARMA_DTT_1  ((uint32_t)0x20000000)
#define RTC_ALARMA_DTU    ((uint32_t)0x0F000000)
#define RTC_ALARMA_DTU_0  ((uint32_t)0x01000000)
#define RTC_ALARMA_DTU_1  ((uint32_t)0x02000000)
#define RTC_ALARMA_DTU_2  ((uint32_t)0x04000000)
#define RTC_ALARMA_DTU_3  ((uint32_t)0x08000000)
#define RTC_ALARMA_MASK3  ((uint32_t)0x00800000)
#define RTC_ALARMA_APM    ((uint32_t)0x00400000)
#define RTC_ALARMA_HOT    ((uint32_t)0x00300000)
#define RTC_ALARMA_HOT_0  ((uint32_t)0x00100000)
#define RTC_ALARMA_HOT_1  ((uint32_t)0x00200000)
#define RTC_ALARMA_HOU    ((uint32_t)0x000F0000)
#define RTC_ALARMA_HOU_0  ((uint32_t)0x00010000)
#define RTC_ALARMA_HOU_1  ((uint32_t)0x00020000)
#define RTC_ALARMA_HOU_2  ((uint32_t)0x00040000)
#define RTC_ALARMA_HOU_3  ((uint32_t)0x00080000)
#define RTC_ALARMA_MASK2  ((uint32_t)0x00008000)
#define RTC_ALARMA_MIT    ((uint32_t)0x00007000)
#define RTC_ALARMA_MIT_0  ((uint32_t)0x00001000)
#define RTC_ALARMA_MIT_1  ((uint32_t)0x00002000)
#define RTC_ALARMA_MIT_2  ((uint32_t)0x00004000)
#define RTC_ALARMA_MIU    ((uint32_t)0x00000F00)
#define RTC_ALARMA_MIU_0  ((uint32_t)0x00000100)
#define RTC_ALARMA_MIU_1  ((uint32_t)0x00000200)
#define RTC_ALARMA_MIU_2  ((uint32_t)0x00000400)
#define RTC_ALARMA_MIU_3  ((uint32_t)0x00000800)
#define RTC_ALARMA_MASK1  ((uint32_t)0x00000080)
#define RTC_ALARMA_SET    ((uint32_t)0x00000070)
#define RTC_ALARMA_SET_0  ((uint32_t)0x00000010)
#define RTC_ALARMA_SET_1  ((uint32_t)0x00000020)
#define RTC_ALARMA_SET_2  ((uint32_t)0x00000040)
#define RTC_ALARMA_SEU    ((uint32_t)0x0000000F)
#define RTC_ALARMA_SEU_0  ((uint32_t)0x00000001)
#define RTC_ALARMA_SEU_1  ((uint32_t)0x00000002)
#define RTC_ALARMA_SEU_2  ((uint32_t)0x00000004)
#define RTC_ALARMA_SEU_3  ((uint32_t)0x00000008)

/********************  Bits definition for RTC_ALARMB register  ***************/
#define RTC_ALARMB_MASK4  ((uint32_t)0x80000000)
#define RTC_ALARMB_WKDSEL ((uint32_t)0x40000000)
#define RTC_ALARMB_DTT    ((uint32_t)0x30000000)
#define RTC_ALARMB_DTT_0  ((uint32_t)0x10000000)
#define RTC_ALARMB_DTT_1  ((uint32_t)0x20000000)
#define RTC_ALARMB_DTU    ((uint32_t)0x0F000000)
#define RTC_ALARMB_DTU_0  ((uint32_t)0x01000000)
#define RTC_ALARMB_DTU_1  ((uint32_t)0x02000000)
#define RTC_ALARMB_DTU_2  ((uint32_t)0x04000000)
#define RTC_ALARMB_DTU_3  ((uint32_t)0x08000000)
#define RTC_ALARMB_MASK3  ((uint32_t)0x00800000)
#define RTC_ALARMB_APM    ((uint32_t)0x00400000)
#define RTC_ALARMB_HOT    ((uint32_t)0x00300000)
#define RTC_ALARMB_HOT_0  ((uint32_t)0x00100000)
#define RTC_ALARMB_HOT_1  ((uint32_t)0x00200000)
#define RTC_ALARMB_HOU    ((uint32_t)0x000F0000)
#define RTC_ALARMB_HOU_0  ((uint32_t)0x00010000)
#define RTC_ALARMB_HOU_1  ((uint32_t)0x00020000)
#define RTC_ALARMB_HOU_2  ((uint32_t)0x00040000)
#define RTC_ALARMB_HOU_3  ((uint32_t)0x00080000)
#define RTC_ALARMB_MASK2  ((uint32_t)0x00008000)
#define RTC_ALARMB_MIT    ((uint32_t)0x00007000)
#define RTC_ALARMB_MIT_0  ((uint32_t)0x00001000)
#define RTC_ALARMB_MIT_1  ((uint32_t)0x00002000)
#define RTC_ALARMB_MIT_2  ((uint32_t)0x00004000)
#define RTC_ALARMB_MIU    ((uint32_t)0x00000F00)
#define RTC_ALARMB_MIU_0  ((uint32_t)0x00000100)
#define RTC_ALARMB_MIU_1  ((uint32_t)0x00000200)
#define RTC_ALARMB_MIU_2  ((uint32_t)0x00000400)
#define RTC_ALARMB_MIU_3  ((uint32_t)0x00000800)
#define RTC_ALARMB_MASK1  ((uint32_t)0x00000080)
#define RTC_ALARMB_SET    ((uint32_t)0x00000070)
#define RTC_ALARMB_SET_0  ((uint32_t)0x00000010)
#define RTC_ALARMB_SET_1  ((uint32_t)0x00000020)
#define RTC_ALARMB_SET_2  ((uint32_t)0x00000040)
#define RTC_ALARMB_SEU    ((uint32_t)0x0000000F)
#define RTC_ALARMB_SEU_0  ((uint32_t)0x00000001)
#define RTC_ALARMB_SEU_1  ((uint32_t)0x00000002)
#define RTC_ALARMB_SEU_2  ((uint32_t)0x00000004)
#define RTC_ALARMB_SEU_3  ((uint32_t)0x00000008)

/********************  Bits definition for RTC_WRP register  ******************/
#define RTC_WRP_PKEY ((uint32_t)0x000000FF)

/********************  Bits definition for RTC_SUBS register  ******************/
#define RTC_SUBS_SS ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_SCTRL register  ***************/
#define RTC_SCTRL_SUBF ((uint32_t)0x00007FFF)
#define RTC_SCTRL_AD1S  ((uint32_t)0x80000000)

/********************  Bits definition for RTC_TST register  *****************/
#define RTC_TST_APM   ((uint32_t)0x00400000)
#define RTC_TST_HOT   ((uint32_t)0x00300000)
#define RTC_TST_HOT_0 ((uint32_t)0x00100000)
#define RTC_TST_HOT_1 ((uint32_t)0x00200000)
#define RTC_TST_HOU   ((uint32_t)0x000F0000)
#define RTC_TST_HOU_0 ((uint32_t)0x00010000)
#define RTC_TST_HOU_1 ((uint32_t)0x00020000)
#define RTC_TST_HOU_2 ((uint32_t)0x00040000)
#define RTC_TST_HOU_3 ((uint32_t)0x00080000)
#define RTC_TST_MIT   ((uint32_t)0x00007000)
#define RTC_TST_MIT_0 ((uint32_t)0x00001000)
#define RTC_TST_MIT_1 ((uint32_t)0x00002000)
#define RTC_TST_MIT_2 ((uint32_t)0x00004000)
#define RTC_TST_MIU   ((uint32_t)0x00000F00)
#define RTC_TST_MIU_0 ((uint32_t)0x00000100)
#define RTC_TST_MIU_1 ((uint32_t)0x00000200)
#define RTC_TST_MIU_2 ((uint32_t)0x00000400)
#define RTC_TST_MIU_3 ((uint32_t)0x00000800)
#define RTC_TST_SET   ((uint32_t)0x00000070)
#define RTC_TST_SET_0 ((uint32_t)0x00000010)
#define RTC_TST_SET_1 ((uint32_t)0x00000020)
#define RTC_TST_SET_2 ((uint32_t)0x00000040)
#define RTC_TST_SEU   ((uint32_t)0x0000000F)
#define RTC_TST_SEU_0 ((uint32_t)0x00000001)
#define RTC_TST_SEU_1 ((uint32_t)0x00000002)
#define RTC_TST_SEU_2 ((uint32_t)0x00000004)
#define RTC_TST_SEU_3 ((uint32_t)0x00000008)

/********************  Bits definition for RTC_TSD register  *****************/
#define RTC_TSD_YRT   ((uint32_t)0x00F00000)
#define RTC_TSD_YRT_0 ((uint32_t)0x00100000)
#define RTC_TSD_YRT_1 ((uint32_t)0x00200000)
#define RTC_TSD_YRT_2 ((uint32_t)0x00400000)
#define RTC_TSD_YRT_3 ((uint32_t)0x00800000)
#define RTC_TSD_YRU   ((uint32_t)0x000F0000)
#define RTC_TSD_YRU_0 ((uint32_t)0x00010000)
#define RTC_TSD_YRU_1 ((uint32_t)0x00020000)
#define RTC_TSD_YRU_2 ((uint32_t)0x00040000)
#define RTC_TSD_YRU_3 ((uint32_t)0x00080000)

#define RTC_TSD_WDU   ((uint32_t)0x0000E000)
#define RTC_TSD_WDU_0 ((uint32_t)0x00002000)
#define RTC_TSD_WDU_1 ((uint32_t)0x00004000)
#define RTC_TSD_WDU_2 ((uint32_t)0x00008000)
#define RTC_TSD_MOT   ((uint32_t)0x00001000)
#define RTC_TSD_MOU   ((uint32_t)0x00000F00)
#define RTC_TSD_MOU_0 ((uint32_t)0x00000100)
#define RTC_TSD_MOU_1 ((uint32_t)0x00000200)
#define RTC_TSD_MOU_2 ((uint32_t)0x00000400)
#define RTC_TSD_MOU_3 ((uint32_t)0x00000800)
#define RTC_TSD_DAT   ((uint32_t)0x00000030)
#define RTC_TSD_DAT_0 ((uint32_t)0x00000010)
#define RTC_TSD_DAT_1 ((uint32_t)0x00000020)
#define RTC_TSD_DAU   ((uint32_t)0x0000000F)
#define RTC_TSD_DAU_0 ((uint32_t)0x00000001)
#define RTC_TSD_DAU_1 ((uint32_t)0x00000002)
#define RTC_TSD_DAU_2 ((uint32_t)0x00000004)
#define RTC_TSD_DAU_3 ((uint32_t)0x00000008)

/********************  Bits definition for RTC_TSSS register  ****************/
#define RTC_TSSS_SSE ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_CALIB register  *****************/
#define RTC_CALIB_CP   ((uint32_t)0x00008000)
#define RTC_CALIB_CW8  ((uint32_t)0x00004000)
#define RTC_CALIB_CW16 ((uint32_t)0x00002000)
#define RTC_CALIB_CM   ((uint32_t)0x000001FF)
#define RTC_CALIB_CM_0 ((uint32_t)0x00000001)
#define RTC_CALIB_CM_1 ((uint32_t)0x00000002)
#define RTC_CALIB_CM_2 ((uint32_t)0x00000004)
#define RTC_CALIB_CM_3 ((uint32_t)0x00000008)
#define RTC_CALIB_CM_4 ((uint32_t)0x00000010)
#define RTC_CALIB_CM_5 ((uint32_t)0x00000020)
#define RTC_CALIB_CM_6 ((uint32_t)0x00000040)
#define RTC_CALIB_CM_7 ((uint32_t)0x00000080)
#define RTC_CALIB_CM_8 ((uint32_t)0x00000100)

/********************  Bits definition for RTC_TMPCFG register  ****************/

#define RTC_TMPCFG_TP3MF                    ((uint32_t)0x01000000)
#define RTC_TMPCFG_TP3NOE                   ((uint32_t)0x00800000)
#define RTC_TMPCFG_TP3INTEN                 ((uint32_t)0x00400000)
#define RTC_TMPCFG_TP2MF                    ((uint32_t)0x00200000)
#define RTC_TMPCFG_TP2NOE                   ((uint32_t)0x00100000)
#define RTC_TMPCFG_TP2INTEN                 ((uint32_t)0x00080000)
#define RTC_TMPCFG_TP1MF                    ((uint32_t)0x00040000)
#define RTC_TMPCFG_TP1NOE                   ((uint32_t)0x00020000)
#define RTC_TMPCFG_TP1INTEN                 ((uint32_t)0x00010000)
#define RTC_TMPCFG_TPPUDIS                  ((uint32_t)0x00008000)
#define RTC_TMPCFG_TPPRCH                   ((uint32_t)0x00006000)
#define RTC_TMPCFG_TPPRCH_0                 ((uint32_t)0x00002000)
#define RTC_TMPCFG_TPPRCH_1                 ((uint32_t)0x00004000)
#define RTC_TMPCFG_TPFLT                    ((uint32_t)0x00001800)
#define RTC_TMPCFG_TPFLT_0                  ((uint32_t)0x00000800)
#define RTC_TMPCFG_TPFLT_1                  ((uint32_t)0x00001000)
#define RTC_TMPCFG_TPFREQ                   ((uint32_t)0x00000700)
#define RTC_TMPCFG_TPFREQ_0                 ((uint32_t)0x00000100)
#define RTC_TMPCFG_TPFREQ_1                 ((uint32_t)0x00000200)
#define RTC_TMPCFG_TPFREQ_2                 ((uint32_t)0x00000400)
#define RTC_TMPCFG_TPTS                     ((uint32_t)0x00000080)
#define RTC_TMPCFG_TP3TRG                   ((uint32_t)0x00000040)
#define RTC_TMPCFG_TP3EN                    ((uint32_t)0x00000020)
#define RTC_TMPCFG_TP2TRG                   ((uint32_t)0x00000010)
#define RTC_TMPCFG_TP2EN                    ((uint32_t)0x00000008)
#define RTC_TMPCFG_TPINTEN                  ((uint32_t)0x00000004)
#define RTC_TMPCFG_TP1TRG                   ((uint32_t)0x00000002)
#define RTC_TMPCFG_TP1EN                    ((uint32_t)0x00000001)

/********************  Bits definition for RTC_ALRMASS register  *************/
#define RTC_ALRMASS_MASKSSB   ((uint32_t)0x0F000000)
#define RTC_ALRMASS_MASKSSB_0 ((uint32_t)0x01000000)
#define RTC_ALRMASS_MASKSSB_1 ((uint32_t)0x02000000)
#define RTC_ALRMASS_MASKSSB_2 ((uint32_t)0x04000000)
#define RTC_ALRMASS_MASKSSB_3 ((uint32_t)0x08000000)
#define RTC_ALRMASS_SSV       ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_ALRMBSS register  *************/
#define RTC_ALRMBSS_MASKSSB   ((uint32_t)0x0F000000)
#define RTC_ALRMBSS_MASKSSB_0 ((uint32_t)0x01000000)
#define RTC_ALRMBSS_MASKSSB_1 ((uint32_t)0x02000000)
#define RTC_ALRMBSS_MASKSSB_2 ((uint32_t)0x04000000)
#define RTC_ALRMBSS_MASKSSB_3 ((uint32_t)0x08000000)
#define RTC_ALRMBSS_SSV       ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_OPT register  *******************/
#define RTC_OPT_TYPE ((uint32_t)0x00000001)
/********************  Bits definition for  RTC_TSCWKUPCTRL register  *******************/
#define RTC_TSCWKUPCTRL_WKUPOFF ((uint32_t)0x00000008)
#define RTC_TSCWKUPCTRL_WKUPCNF ((uint32_t)0x00000004)
#define RTC_TSCWKUPCTRL_WKUPEN  ((uint32_t)0x00000001)
/********************  Bits definition for  RTC_TSCWKUPCNT register  *******************/
#define RTC_TSCWKUPCNT_CNT ((uint32_t)0x00003FFF)
/********************  Bits definition for RTC_BKP1 register  ****************/
#define RTC_BKP1                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP2 register  ****************/
#define RTC_BKP2                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP3 register  ****************/
#define RTC_BKP3                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP4 register  ****************/
#define RTC_BKP4                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP5 register  ****************/
#define RTC_BKP5                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP6 register  ****************/
#define RTC_BKP6                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP7 register  ****************/
#define RTC_BKP7                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP8 register  ****************/
#define RTC_BKP8                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP9 register  ****************/
#define RTC_BKP9                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP10 register  ****************/
#define RTC_BKP10                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP11 register  ***************/
#define RTC_BKP11                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP12register  ***************/
#define RTC_BKP12                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP13 register  ***************/
#define RTC_BKP13                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP14 register  ***************/
#define RTC_BKP14                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP15 register  ***************/
#define RTC_BKP15                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP16 register  ***************/
#define RTC_BKP16                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP17register  ***************/
#define RTC_BKP17                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP18 register  ***************/
#define RTC_BKP18                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP19 register  ***************/
#define RTC_BKP19                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP20 register  ***************/
#define RTC_BKP20                           ((uint32_t)0xFFFFFFFF)



/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for IWDG_KEY register  ********************/
#define IWDG_KEY_KEYV ((uint16_t)0xFFFF) /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PREDIV register  ********************/
#define IWDG_PREDIV_PD ((uint8_t)0x07) /*!< PD[2:0] (Prescaler divider) */
#define IWDG_PR_PR_0   ((uint8_t)0x01) /*!< Bit 0 */
#define IWDG_PR_PR_1   ((uint8_t)0x02) /*!< Bit 1 */
#define IWDG_PR_PR_2   ((uint8_t)0x04) /*!< Bit 2 */

/*******************  Bit definition for IWDG_RELV register  *******************/
#define IWDG_RELV_REL ((uint16_t)0x0FFF) /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_STS register  ********************/
#define IWDG_STS_PVU  ((uint8_t)0x01) /*!< Watchdog prescaler value update */
#define IWDG_STS_CRVU ((uint8_t)0x02) /*!< Watchdog counter reload value update */

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for WWDG_CTRL register  ********************/
#define WWDG_CTRL_T  ((uint8_t)0x7F) /*!< T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define WWDG_CTRL_T0 ((uint8_t)0x01) /*!< Bit 0 */
#define WWDG_CTRL_T1 ((uint8_t)0x02) /*!< Bit 1 */
#define WWDG_CTRL_T2 ((uint8_t)0x04) /*!< Bit 2 */
#define WWDG_CTRL_T3 ((uint8_t)0x08) /*!< Bit 3 */
#define WWDG_CTRL_T4 ((uint8_t)0x10) /*!< Bit 4 */
#define WWDG_CTRL_T5 ((uint8_t)0x20) /*!< Bit 5 */
#define WWDG_CTRL_T6 ((uint8_t)0x40) /*!< Bit 6 */

#define WWDG_CTRL_ACTB ((uint8_t)0x80) /*!< Activation bit */

/*******************  Bit definition for WWDG_CFG register  *******************/
#define WWDG_CFG_W  ((uint16_t)0x007F) /*!< W[6:0] bits (7-bit window value) */
#define WWDG_CFG_W0 ((uint16_t)0x0001) /*!< Bit 0 */
#define WWDG_CFG_W1 ((uint16_t)0x0002) /*!< Bit 1 */
#define WWDG_CFG_W2 ((uint16_t)0x0004) /*!< Bit 2 */
#define WWDG_CFG_W3 ((uint16_t)0x0008) /*!< Bit 3 */
#define WWDG_CFG_W4 ((uint16_t)0x0010) /*!< Bit 4 */
#define WWDG_CFG_W5 ((uint16_t)0x0020) /*!< Bit 5 */
#define WWDG_CFG_W6 ((uint16_t)0x0040) /*!< Bit 6 */

#define WWDG_CFG_TIMERB  ((uint16_t)0x0180) /*!< TIMERB[1:0] bits (Timer Base) */
#define WWDG_CFG_TIMERB0 ((uint16_t)0x0080) /*!< Bit 0 */
#define WWDG_CFG_TIMERB1 ((uint16_t)0x0100) /*!< Bit 1 */

#define WWDG_CFG_EWINT ((uint16_t)0x0200) /*!< Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_STS register  ********************/
#define WWDG_STS_EWINTF ((uint8_t)0x01) /*!< Early Wakeup Interrupt Flag */

/******************************************************************************/
/*                                                                            */
/*                       Flexible Static Memory Controller                    */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for XFMC_BCR1 register  *******************/
#define XFMC_BK1CSCTRL1_MBEN  ((uint32_t)0x00000001) /*!< Memory bank enable bit */
#define XFMC_BK1CSCTRL1_MUXEN ((uint32_t)0x00000002) /*!< Address/data multiplexing enable bit */

#define XFMC_BK1CSCTRL1_MTYPE   ((uint32_t)0x0000000C) /*!< MTYP[1:0] bits (Memory type) */
#define XFMC_BK1CSCTRL1_MTYPE_0 ((uint32_t)0x00000004) /*!< Bit 0 */
#define XFMC_BK1CSCTRL1_MTYPE_1 ((uint32_t)0x00000008) /*!< Bit 1 */

#define XFMC_BK1CSCTRL1_MDBW   ((uint32_t)0x00000030) /*!< MWID[1:0] bits (Memory data bus width) */
#define XFMC_BK1CSCTRL1_MDBW_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK1CSCTRL1_MDBW_1 ((uint32_t)0x00000020) /*!< Bit 1 */

#define XFMC_BK1CSCTRL1_ACCEN     ((uint32_t)0x00000040) /*!< Flash access enable */
#define XFMC_BK1CSCTRL1_BURSTEN   ((uint32_t)0x00000100) /*!< Burst enable bit */
#define XFMC_BK1CSCTRL1_WAITDIR   ((uint32_t)0x00000200) /*!< Wait signal polarity bit */
#define XFMC_BK1CSCTRL1_WRAPEN    ((uint32_t)0x00000400) /*!< Wrapped burst mode support */
#define XFMC_BK1CSCTRL1_WCFG      ((uint32_t)0x00000800) /*!< Wait timing configuration */
#define XFMC_BK1CSCTRL1_WREN      ((uint32_t)0x00001000) /*!< Write enable bit */
#define XFMC_BK1CSCTRL1_WAITEN    ((uint32_t)0x00002000) /*!< Wait enable bit */
#define XFMC_BK1CSCTRL1_EXTEN     ((uint32_t)0x00004000) /*!< Extended mode enable */
#define XFMC_BK1CSCTRL1_WAITASYNC ((uint32_t)0x00008000) /*!< Asynchronous wait */
#define XFMC_BK1CSCTRL1_BURSTWREN ((uint32_t)0x00080000) /*!< Write burst enable */

/******************  Bit definition for XFMC_BCR2 register  *******************/
#define XFMC_BK1CSCTRL2_MBEN  ((uint32_t)0x00000001) /*!< Memory bank enable bit */
#define XFMC_BK1CSCTRL2_MUXEN ((uint32_t)0x00000002) /*!< Address/data multiplexing enable bit */

#define XFMC_BK1CSCTRL2_MTYPE   ((uint32_t)0x0000000C) /*!< MTYP[1:0] bits (Memory type) */
#define XFMC_BK1CSCTRL2_MTYPE_0 ((uint32_t)0x00000004) /*!< Bit 0 */
#define XFMC_BK1CSCTRL2_MTYPE_1 ((uint32_t)0x00000008) /*!< Bit 1 */

#define XFMC_BK1CSCTRL2_MDBW   ((uint32_t)0x00000030) /*!< MWID[1:0] bits (Memory data bus width) */
#define XFMC_BK1CSCTRL2_MDBW_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK1CSCTRL2_MDBW_1 ((uint32_t)0x00000020) /*!< Bit 1 */

#define XFMC_BK1CSCTRL2_ACCEN     ((uint32_t)0x00000040) /*!< Flash access enable */
#define XFMC_BK1CSCTRL2_BURSTEN   ((uint32_t)0x00000100) /*!< Burst enable bit */
#define XFMC_BK1CSCTRL2_WAITDIR   ((uint32_t)0x00000200) /*!< Wait signal polarity bit */
#define XFMC_BK1CSCTRL2_WRAPEN    ((uint32_t)0x00000400) /*!< Wrapped burst mode support */
#define XFMC_BK1CSCTRL2_WCFG      ((uint32_t)0x00000800) /*!< Wait timing configuration */
#define XFMC_BK1CSCTRL2_WREN      ((uint32_t)0x00001000) /*!< Write enable bit */
#define XFMC_BK1CSCTRL2_WAITEN    ((uint32_t)0x00002000) /*!< Wait enable bit */
#define XFMC_BK1CSCTRL2_EXTEN     ((uint32_t)0x00004000) /*!< Extended mode enable */
#define XFMC_BK1CSCTRL2_WAITASYNC ((uint32_t)0x00008000) /*!< Asynchronous wait */
#define XFMC_BK1CSCTRL2_BURSTWREN ((uint32_t)0x00080000) /*!< Write burst enable */

/******************  Bit definition for XFMC_BTR1 register  ******************/
#define XFMC_BK1TM1_ADDBLD   ((uint32_t)0x0000000F) /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define XFMC_BK1TM1_ADDBLD_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_BK1TM1_ADDBLD_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_BK1TM1_ADDBLD_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_BK1TM1_ADDBLD_3 ((uint32_t)0x00000008) /*!< Bit 3 */

#define XFMC_BK1TM1_ADDHLD   ((uint32_t)0x000000F0) /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define XFMC_BK1TM1_ADDHLD_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK1TM1_ADDHLD_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define XFMC_BK1TM1_ADDHLD_2 ((uint32_t)0x00000040) /*!< Bit 2 */
#define XFMC_BK1TM1_ADDHLD_3 ((uint32_t)0x00000080) /*!< Bit 3 */

#define XFMC_BK1TM1_DATABLD   ((uint32_t)0x0000FF00) /*!< DATAST [3:0] bits (Data-phase duration) */
#define XFMC_BK1TM1_DATABLD_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_BK1TM1_DATABLD_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_BK1TM1_DATABLD_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_BK1TM1_DATABLD_3 ((uint32_t)0x00000800) /*!< Bit 3 */

#define XFMC_BK1TM1_BUSRECOVERY   ((uint32_t)0x000F0000) /*!< BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define XFMC_BK1TM1_BUSRECOVERY_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define XFMC_BK1TM1_BUSRECOVERY_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define XFMC_BK1TM1_BUSRECOVERY_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define XFMC_BK1TM1_BUSRECOVERY_3 ((uint32_t)0x00080000) /*!< Bit 3 */

#define XFMC_BK1TM1_CLKDIV   ((uint32_t)0x00F00000) /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define XFMC_BK1TM1_CLKDIV_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define XFMC_BK1TM1_CLKDIV_1 ((uint32_t)0x00200000) /*!< Bit 1 */
#define XFMC_BK1TM1_CLKDIV_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define XFMC_BK1TM1_CLKDIV_3 ((uint32_t)0x00800000) /*!< Bit 3 */

#define XFMC_BK1TM1_DATAHLD   ((uint32_t)0x0F000000) /*!< DATLA[3:0] bits (Data latency) */
#define XFMC_BK1TM1_DATAHLD_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_BK1TM1_DATAHLD_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_BK1TM1_DATAHLD_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_BK1TM1_DATAHLD_3 ((uint32_t)0x08000000) /*!< Bit 3 */

#define XFMC_BK1TM1_ACCMODE   ((uint32_t)0x30000000) /*!< ACCMOD[1:0] bits (Access mode) */
#define XFMC_BK1TM1_ACCMODE_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define XFMC_BK1TM1_ACCMODE_1 ((uint32_t)0x20000000) /*!< Bit 1 */

/******************  Bit definition for XFMC_BTR2 register  *******************/
#define XFMC_BK1TM2_ADDBLD   ((uint32_t)0x0000000F) /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define XFMC_BK1TM2_ADDBLD_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_BK1TM2_ADDBLD_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_BK1TM2_ADDBLD_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_BK1TM2_ADDBLD_3 ((uint32_t)0x00000008) /*!< Bit 3 */

#define XFMC_BK1TM2_ADDHLD   ((uint32_t)0x000000F0) /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define XFMC_BK1TM2_ADDHLD_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK1TM2_ADDHLD_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define XFMC_BK1TM2_ADDHLD_2 ((uint32_t)0x00000040) /*!< Bit 2 */
#define XFMC_BK1TM2_ADDHLD_3 ((uint32_t)0x00000080) /*!< Bit 3 */

#define XFMC_BK1TM2_DATABLD   ((uint32_t)0x0000FF00) /*!< DATAST [3:0] bits (Data-phase duration) */
#define XFMC_BK1TM2_DATABLD_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_BK1TM2_DATABLD_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_BK1TM2_DATABLD_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_BK1TM2_DATABLD_3 ((uint32_t)0x00000800) /*!< Bit 3 */

#define XFMC_BK1TM2_BUSRECOVERY   ((uint32_t)0x000F0000) /*!< BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define XFMC_BK1TM2_BUSRECOVERY_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define XFMC_BK1TM2_BUSRECOVERY_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define XFMC_BK1TM2_BUSRECOVERY_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define XFMC_BK1TM2_BUSRECOVERY_3 ((uint32_t)0x00080000) /*!< Bit 3 */

#define XFMC_BK1TM2_CLKDIV   ((uint32_t)0x00F00000) /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define XFMC_BK1TM2_CLKDIV_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define XFMC_BK1TM2_CLKDIV_1 ((uint32_t)0x00200000) /*!< Bit 1 */
#define XFMC_BK1TM2_CLKDIV_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define XFMC_BK1TM2_CLKDIV_3 ((uint32_t)0x00800000) /*!< Bit 3 */

#define XFMC_BK1TM2_DATAHLD   ((uint32_t)0x0F000000) /*!< DATLA[3:0] bits (Data latency) */
#define XFMC_BK1TM2_DATAHLD_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_BK1TM2_DATAHLD_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_BK1TM2_DATAHLD_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_BK1TM2_DATAHLD_3 ((uint32_t)0x08000000) /*!< Bit 3 */

#define XFMC_BK1TM2_ACCMODE   ((uint32_t)0x30000000) /*!< ACCMOD[1:0] bits (Access mode) */
#define XFMC_BK1TM2_ACCMODE_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define XFMC_BK1TM2_ACCMODE_1 ((uint32_t)0x20000000) /*!< Bit 1 */

/******************  Bit definition for XFMC_BWTR1 register  ******************/
#define XFMC_BK1WTM1_ADDBLD   ((uint32_t)0x0000000F) /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define XFMC_BK1WTM1_ADDBLD_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_BK1WTM1_ADDBLD_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_BK1WTM1_ADDBLD_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_BK1WTM1_ADDBLD_3 ((uint32_t)0x00000008) /*!< Bit 3 */

#define XFMC_BK1WTM1_ADDHLD   ((uint32_t)0x000000F0) /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define XFMC_BK1WTM1_ADDHLD_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK1WTM1_ADDHLD_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define XFMC_BK1WTM1_ADDHLD_2 ((uint32_t)0x00000040) /*!< Bit 2 */
#define XFMC_BK1WTM1_ADDHLD_3 ((uint32_t)0x00000080) /*!< Bit 3 */

#define XFMC_BK1WTM1_DATABLD   ((uint32_t)0x0000FF00) /*!< DATAST [3:0] bits (Data-phase duration) */
#define XFMC_BK1WTM1_DATABLD_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_BK1WTM1_DATABLD_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_BK1WTM1_DATABLD_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_BK1WTM1_DATABLD_3 ((uint32_t)0x00000800) /*!< Bit 3 */

#define XFMC_BK1WTM1_CLKDIV   ((uint32_t)0x00F00000) /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define XFMC_BK1WTM1_CLKDIV_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define XFMC_BK1WTM1_CLKDIV_1 ((uint32_t)0x00200000) /*!< Bit 1 */
#define XFMC_BK1WTM1_CLKDIV_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define XFMC_BK1WTM1_CLKDIV_3 ((uint32_t)0x00800000) /*!< Bit 3 */

#define XFMC_BK1WTM1_DATAHLD   ((uint32_t)0x0F000000) /*!< DATLA[3:0] bits (Data latency) */
#define XFMC_BK1WTM1_DATAHLD_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_BK1WTM1_DATAHLD_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_BK1WTM1_DATAHLD_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_BK1WTM1_DATAHLD_3 ((uint32_t)0x08000000) /*!< Bit 3 */

#define XFMC_BK1WTM1_ACCMODE   ((uint32_t)0x30000000) /*!< ACCMOD[1:0] bits (Access mode) */
#define XFMC_BK1WTM1_ACCMODE_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define XFMC_BK1WTM1_ACCMODE_1 ((uint32_t)0x20000000) /*!< Bit 1 */

/******************  Bit definition for XFMC_BWTR2 register  ******************/
#define XFMC_BK1WTM2_ADDBLD   ((uint32_t)0x0000000F) /*!< ADDSET[3:0] bits (Address setup phase duration) */
#define XFMC_BK1WTM2_ADDBLD_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_BK1WTM2_ADDBLD_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_BK1WTM2_ADDBLD_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_BK1WTM2_ADDBLD_3 ((uint32_t)0x00000008) /*!< Bit 3 */

#define XFMC_BK1WTM2_ADDHLD   ((uint32_t)0x000000F0) /*!< ADDHLD[3:0] bits (Address-hold phase duration) */
#define XFMC_BK1WTM2_ADDHLD_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK1WTM2_ADDHLD_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define XFMC_BK1WTM2_ADDHLD_2 ((uint32_t)0x00000040) /*!< Bit 2 */
#define XFMC_BK1WTM2_ADDHLD_3 ((uint32_t)0x00000080) /*!< Bit 3 */

#define XFMC_BK1WTM2_DATABLD   ((uint32_t)0x0000FF00) /*!< DATAST [3:0] bits (Data-phase duration) */
#define XFMC_BK1WTM2_DATABLD_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_BK1WTM2_DATABLD_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_BK1WTM2_DATABLD_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_BK1WTM2_DATABLD_3 ((uint32_t)0x00000800) /*!< Bit 3 */

#define XFMC_BK1WTM2_CLKDIV   ((uint32_t)0x00F00000) /*!< CLKDIV[3:0] bits (Clock divide ratio) */
#define XFMC_BK1WTM2_CLKDIV_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define XFMC_BK1WTM2_CLKDIV_1 ((uint32_t)0x00200000) /*!< Bit 1*/
#define XFMC_BK1WTM2_CLKDIV_2 ((uint32_t)0x00400000) /*!< Bit 2 */
#define XFMC_BK1WTM2_CLKDIV_3 ((uint32_t)0x00800000) /*!< Bit 3 */

#define XFMC_BK1WTM2_DATAHLD   ((uint32_t)0x0F000000) /*!< DATLA[3:0] bits (Data latency) */
#define XFMC_BK1WTM2_DATAHLD_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_BK1WTM2_DATAHLD_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_BK1WTM2_DATAHLD_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_BK1WTM2_DATAHLD_3 ((uint32_t)0x08000000) /*!< Bit 3 */

#define XFMC_BK1WTM2_ACCMODE   ((uint32_t)0x30000000) /*!< ACCMOD[1:0] bits (Access mode) */
#define XFMC_BK1WTM2_ACCMODE_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define XFMC_BK1WTM2_ACCMODE_1 ((uint32_t)0x20000000) /*!< Bit 1 */

/******************  Bit definition for XFMC_PCR2 register  *******************/
#define XFMC_BK2CTRL_WAITEN  ((uint32_t)0x00000002) /*!< Wait feature enable bit */
#define XFMC_BK2CTRL_BANKEN  ((uint32_t)0x00000004) /*!< PC Card/NAND Flash memory bank enable bit */
#define XFMC_BK2CTRL_MEMTYPE ((uint32_t)0x00000008) /*!< Memory type */

#define XFMC_BK2CTRL_BUSWID   ((uint32_t)0x00000030) /*!< PWID[1:0] bits (NAND Flash databus width) */
#define XFMC_BK2CTRL_BUSWID_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK2CTRL_BUSWID_1 ((uint32_t)0x00000020) /*!< Bit 1 */

#define XFMC_BK2CTRL_ECCEN ((uint32_t)0x00000040) /*!< ECC computation logic enable bit */

#define XFMC_BK2CTRL_CRDLY   ((uint32_t)0x00001E00) /*!< TCLR[3:0] bits (CLE to RE delay) */
#define XFMC_BK2CTRL_CRDLY_0 ((uint32_t)0x00000200) /*!< Bit 0 */
#define XFMC_BK2CTRL_CRDLY_1 ((uint32_t)0x00000400) /*!< Bit 1 */
#define XFMC_BK2CTRL_CRDLY_2 ((uint32_t)0x00000800) /*!< Bit 2 */
#define XFMC_BK2CTRL_CRDLY_3 ((uint32_t)0x00001000) /*!< Bit 3 */

#define XFMC_BK2CTRL_ARDLY   ((uint32_t)0x0001E000) /*!< TAR[3:0] bits (ALE to RE delay) */
#define XFMC_BK2CTRL_ARDLY_0 ((uint32_t)0x00002000) /*!< Bit 0 */
#define XFMC_BK2CTRL_ARDLY_1 ((uint32_t)0x00004000) /*!< Bit 1 */
#define XFMC_BK2CTRL_ARDLY_2 ((uint32_t)0x00008000) /*!< Bit 2 */
#define XFMC_BK2CTRL_ARDLY_3 ((uint32_t)0x00010000) /*!< Bit 3 */

#define XFMC_BK2CTRL_ECCPGS   ((uint32_t)0x000E0000) /*!< ECCPS[1:0] bits (ECC page size) */
#define XFMC_BK2CTRL_ECCPGS_0 ((uint32_t)0x00020000) /*!< Bit 0 */
#define XFMC_BK2CTRL_ECCPGS_1 ((uint32_t)0x00040000) /*!< Bit 1 */
#define XFMC_BK2CTRL_ECCPGS_2 ((uint32_t)0x00080000) /*!< Bit 2 */

/******************  Bit definition for XFMC_PCR3 register  *******************/
#define XFMC_BK3CTRL_WAITEN  ((uint32_t)0x00000002) /*!< Wait feature enable bit */
#define XFMC_BK3CTRL_BANKEN  ((uint32_t)0x00000004) /*!< PC Card/NAND Flash memory bank enable bit */
#define XFMC_BK3CTRL_MEMTYPE ((uint32_t)0x00000008) /*!< Memory type */

#define XFMC_BK3CTRL_BUSWID   ((uint32_t)0x00000030) /*!< PWID[1:0] bits (NAND Flash databus width) */
#define XFMC_BK3CTRL_BUSWID_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define XFMC_BK3CTRL_BUSWID_1 ((uint32_t)0x00000020) /*!< Bit 1 */

#define XFMC_BK3CTRL_ECCEN ((uint32_t)0x00000040) /*!< ECC computation logic enable bit */

#define XFMC_BK3CTRL_CRDLY   ((uint32_t)0x00001E00) /*!< TCLR[3:0] bits (CLE to RE delay) */
#define XFMC_BK3CTRL_CRDLY_0 ((uint32_t)0x00000200) /*!< Bit 0 */
#define XFMC_BK3CTRL_CRDLY_1 ((uint32_t)0x00000400) /*!< Bit 1 */
#define XFMC_BK3CTRL_CRDLY_2 ((uint32_t)0x00000800) /*!< Bit 2 */
#define XFMC_BK3CTRL_CRDLY_3 ((uint32_t)0x00001000) /*!< Bit 3 */

#define XFMC_BK3CTRL_ARDLY   ((uint32_t)0x0001E000) /*!< TAR[3:0] bits (ALE to RE delay) */
#define XFMC_BK3CTRL_ARDLY_0 ((uint32_t)0x00002000) /*!< Bit 0 */
#define XFMC_BK3CTRL_ARDLY_1 ((uint32_t)0x00004000) /*!< Bit 1 */
#define XFMC_BK3CTRL_ARDLY_2 ((uint32_t)0x00008000) /*!< Bit 2 */
#define XFMC_BK3CTRL_ARDLY_3 ((uint32_t)0x00010000) /*!< Bit 3 */

#define XFMC_BK3CTRL_ECCPGS   ((uint32_t)0x000E0000) /*!< ECCPS[2:0] bits (ECC page size) */
#define XFMC_BK3CTRL_ECCPGS_0 ((uint32_t)0x00020000) /*!< Bit 0 */
#define XFMC_BK3CTRL_ECCPGS_1 ((uint32_t)0x00040000) /*!< Bit 1 */
#define XFMC_BK3CTRL_ECCPGS_2 ((uint32_t)0x00080000) /*!< Bit 2 */

/*******************  Bit definition for XFMC_SR2 register  *******************/
//#define  XFMC_SR2_IRS                        ((uint8_t)0x01)               /*!< Interrupt Rising Edge status */
//#define  XFMC_SR2_ILS                        ((uint8_t)0x02)               /*!< Interrupt Level status */
//#define  XFMC_SR2_IFS                        ((uint8_t)0x04)               /*!< Interrupt Falling Edge status */
//#define  XFMC_SR2_IREN                       ((uint8_t)0x08)               /*!< Interrupt Rising Edge detection Enable
// bit */ #define  XFMC_SR2_ILEN                       ((uint8_t)0x10)               /*!< Interrupt Level detection
// Enable bit */ #define  XFMC_SR2_IFEN                       ((uint8_t)0x20)               /*!< Interrupt Falling Edge
// detection Enable bit */
#define XFMC_STS2_FIFOEMPT ((uint8_t)0x40) /*!< DATFIFO empty */

/*******************  Bit definition for XFMC_SR3 register  *******************/
//#define  XFMC_SR3_IRS                        ((uint8_t)0x01)               /*!< Interrupt Rising Edge status */
//#define  XFMC_SR3_ILS                        ((uint8_t)0x02)               /*!< Interrupt Level status */
//#define  XFMC_SR3_IFS                        ((uint8_t)0x04)               /*!< Interrupt Falling Edge status */
//#define  XFMC_SR3_IREN                       ((uint8_t)0x08)               /*!< Interrupt Rising Edge detection Enable
// bit */ #define  XFMC_SR3_ILEN                       ((uint8_t)0x10)               /*!< Interrupt Level detection
// Enable bit */ #define  XFMC_SR3_IFEN                       ((uint8_t)0x20)               /*!< Interrupt Falling Edge
// detection Enable bit */
#define XFMC_STS3_FIFOEMPT ((uint8_t)0x40) /*!< DATFIFO empty */

/******************  Bit definition for XFMC_PMEM2 register  ******************/
#define XFMC_CMEMTM2_SET   ((uint32_t)0x000000FF) /*!< MEMSET2[7:0] bits (Common memory 2 setup time) */
#define XFMC_CMEMTM2_SET_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_CMEMTM2_SET_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_CMEMTM2_SET_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_CMEMTM2_SET_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define XFMC_CMEMTM2_SET_4 ((uint32_t)0x00000010) /*!< Bit 4 */
#define XFMC_CMEMTM2_SET_5 ((uint32_t)0x00000020) /*!< Bit 5 */
#define XFMC_CMEMTM2_SET_6 ((uint32_t)0x00000040) /*!< Bit 6 */
#define XFMC_CMEMTM2_SET_7 ((uint32_t)0x00000080) /*!< Bit 7 */

#define XFMC_CMEMTM2_WAIT   ((uint32_t)0x0000FF00) /*!< MEMWAIT2[7:0] bits (Common memory 2 wait time) */
#define XFMC_CMEMTM2_WAIT_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_CMEMTM2_WAIT_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_CMEMTM2_WAIT_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_CMEMTM2_WAIT_3 ((uint32_t)0x00000800) /*!< Bit 3 */
#define XFMC_CMEMTM2_WAIT_4 ((uint32_t)0x00001000) /*!< Bit 4 */
#define XFMC_CMEMTM2_WAIT_5 ((uint32_t)0x00002000) /*!< Bit 5 */
#define XFMC_CMEMTM2_WAIT_6 ((uint32_t)0x00004000) /*!< Bit 6 */
#define XFMC_CMEMTM2_WAIT_7 ((uint32_t)0x00008000) /*!< Bit 7 */

#define XFMC_CMEMTM2_HLD   ((uint32_t)0x00FF0000) /*!< MEMHOLD2[7:0] bits (Common memory 2 hold time) */
#define XFMC_CMEMTM2_HLD_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define XFMC_CMEMTM2_HLD_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define XFMC_CMEMTM2_HLD_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define XFMC_CMEMTM2_HLD_3 ((uint32_t)0x00080000) /*!< Bit 3 */
#define XFMC_CMEMTM2_HLD_4 ((uint32_t)0x00100000) /*!< Bit 4 */
#define XFMC_CMEMTM2_HLD_5 ((uint32_t)0x00200000) /*!< Bit 5 */
#define XFMC_CMEMTM2_HLD_6 ((uint32_t)0x00400000) /*!< Bit 6 */
#define XFMC_CMEMTM2_HLD_7 ((uint32_t)0x00800000) /*!< Bit 7 */

#define XFMC_CMEMTM2_HIZ   ((uint32_t)0xFF000000) /*!< MEMHIZ2[7:0] bits (Common memory 2 databus HiZ time) */
#define XFMC_CMEMTM2_HIZ_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_CMEMTM2_HIZ_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_CMEMTM2_HIZ_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_CMEMTM2_HIZ_3 ((uint32_t)0x08000000) /*!< Bit 3 */
#define XFMC_CMEMTM2_HIZ_4 ((uint32_t)0x10000000) /*!< Bit 4 */
#define XFMC_CMEMTM2_HIZ_5 ((uint32_t)0x20000000) /*!< Bit 5 */
#define XFMC_CMEMTM2_HIZ_6 ((uint32_t)0x40000000) /*!< Bit 6 */
#define XFMC_CMEMTM2_HIZ_7 ((uint32_t)0x80000000) /*!< Bit 7 */

/******************  Bit definition for XFMC_PMEM3 register  ******************/
#define XFMC_CMEMTM3_SET   ((uint32_t)0x000000FF) /*!< MEMSET3[7:0] bits (Common memory 3 setup time) */
#define XFMC_CMEMTM3_SET_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_CMEMTM3_SET_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_CMEMTM3_SET_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_CMEMTM3_SET_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define XFMC_CMEMTM3_SET_4 ((uint32_t)0x00000010) /*!< Bit 4 */
#define XFMC_CMEMTM3_SET_5 ((uint32_t)0x00000020) /*!< Bit 5 */
#define XFMC_CMEMTM3_SET_6 ((uint32_t)0x00000040) /*!< Bit 6 */
#define XFMC_CMEMTM3_SET_7 ((uint32_t)0x00000080) /*!< Bit 7 */

#define XFMC_CMEMTM3_WAIT   ((uint32_t)0x0000FF00) /*!< MEMWAIT3[7:0] bits (Common memory 3 wait time) */
#define XFMC_CMEMTM3_WAIT_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_CMEMTM3_WAIT_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_CMEMTM3_WAIT_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_CMEMTM3_WAIT_3 ((uint32_t)0x00000800) /*!< Bit 3 */
#define XFMC_CMEMTM3_WAIT_4 ((uint32_t)0x00001000) /*!< Bit 4 */
#define XFMC_CMEMTM3_WAIT_5 ((uint32_t)0x00002000) /*!< Bit 5 */
#define XFMC_CMEMTM3_WAIT_6 ((uint32_t)0x00004000) /*!< Bit 6 */
#define XFMC_CMEMTM3_WAIT_7 ((uint32_t)0x00008000) /*!< Bit 7 */

#define XFMC_CMEMTM3_HLD   ((uint32_t)0x00FF0000) /*!< MEMHOLD3[7:0] bits (Common memory 3 hold time) */
#define XFMC_CMEMTM3_HLD_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define XFMC_CMEMTM3_HLD_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define XFMC_CMEMTM3_HLD_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define XFMC_CMEMTM3_HLD_3 ((uint32_t)0x00080000) /*!< Bit 3 */
#define XFMC_CMEMTM3_HLD_4 ((uint32_t)0x00100000) /*!< Bit 4 */
#define XFMC_CMEMTM3_HLD_5 ((uint32_t)0x00200000) /*!< Bit 5 */
#define XFMC_CMEMTM3_HLD_6 ((uint32_t)0x00400000) /*!< Bit 6 */
#define XFMC_CMEMTM3_HLD_7 ((uint32_t)0x00800000) /*!< Bit 7 */

#define XFMC_CMEMTM3_HIZ   ((uint32_t)0xFF000000) /*!< MEMHIZ3[7:0] bits (Common memory 3 databus HiZ time) */
#define XFMC_CMEMTM3_HIZ_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_CMEMTM3_HIZ_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_CMEMTM3_HIZ_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_CMEMTM3_HIZ_3 ((uint32_t)0x08000000) /*!< Bit 3 */
#define XFMC_CMEMTM3_HIZ_4 ((uint32_t)0x10000000) /*!< Bit 4 */
#define XFMC_CMEMTM3_HIZ_5 ((uint32_t)0x20000000) /*!< Bit 5 */
#define XFMC_CMEMTM3_HIZ_6 ((uint32_t)0x40000000) /*!< Bit 6 */
#define XFMC_CMEMTM3_HIZ_7 ((uint32_t)0x80000000) /*!< Bit 7 */

/******************  Bit definition for XFMC_PATT2 register  ******************/
#define XFMC_ATTMEMTM2_SET   ((uint32_t)0x000000FF) /*!< ATTSET2[7:0] bits (Attribute memory 2 setup time) */
#define XFMC_ATTMEMTM2_SET_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_ATTMEMTM2_SET_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_ATTMEMTM2_SET_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_ATTMEMTM2_SET_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define XFMC_ATTMEMTM2_SET_4 ((uint32_t)0x00000010) /*!< Bit 4 */
#define XFMC_ATTMEMTM2_SET_5 ((uint32_t)0x00000020) /*!< Bit 5 */
#define XFMC_ATTMEMTM2_SET_6 ((uint32_t)0x00000040) /*!< Bit 6 */
#define XFMC_ATTMEMTM2_SET_7 ((uint32_t)0x00000080) /*!< Bit 7 */

#define XFMC_ATTMEMTM2_WAIT   ((uint32_t)0x0000FF00) /*!< ATTWAIT2[7:0] bits (Attribute memory 2 wait time) */
#define XFMC_ATTMEMTM2_WAIT_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_ATTMEMTM2_WAIT_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_ATTMEMTM2_WAIT_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_ATTMEMTM2_WAIT_3 ((uint32_t)0x00000800) /*!< Bit 3 */
#define XFMC_ATTMEMTM2_WAIT_4 ((uint32_t)0x00001000) /*!< Bit 4 */
#define XFMC_ATTMEMTM2_WAIT_5 ((uint32_t)0x00002000) /*!< Bit 5 */
#define XFMC_ATTMEMTM2_WAIT_6 ((uint32_t)0x00004000) /*!< Bit 6 */
#define XFMC_ATTMEMTM2_WAIT_7 ((uint32_t)0x00008000) /*!< Bit 7 */

#define XFMC_ATTMEMTM2_HLD   ((uint32_t)0x00FF0000) /*!< ATTHOLD2[7:0] bits (Attribute memory 2 hold time) */
#define XFMC_ATTMEMTM2_HLD_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define XFMC_ATTMEMTM2_HLD_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define XFMC_ATTMEMTM2_HLD_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define XFMC_ATTMEMTM2_HLD_3 ((uint32_t)0x00080000) /*!< Bit 3 */
#define XFMC_ATTMEMTM2_HLD_4 ((uint32_t)0x00100000) /*!< Bit 4 */
#define XFMC_ATTMEMTM2_HLD_5 ((uint32_t)0x00200000) /*!< Bit 5 */
#define XFMC_ATTMEMTM2_HLD_6 ((uint32_t)0x00400000) /*!< Bit 6 */
#define XFMC_ATTMEMTM2_HLD_7 ((uint32_t)0x00800000) /*!< Bit 7 */

#define XFMC_ATTMEMTM2_HIZ   ((uint32_t)0xFF000000) /*!< ATTHIZ2[7:0] bits (Attribute memory 2 databus HiZ time) */
#define XFMC_ATTMEMTM2_HIZ_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_ATTMEMTM2_HIZ_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_ATTMEMTM2_HIZ_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_ATTMEMTM2_HIZ_3 ((uint32_t)0x08000000) /*!< Bit 3 */
#define XFMC_ATTMEMTM2_HIZ_4 ((uint32_t)0x10000000) /*!< Bit 4 */
#define XFMC_ATTMEMTM2_HIZ_5 ((uint32_t)0x20000000) /*!< Bit 5 */
#define XFMC_ATTMEMTM2_HIZ_6 ((uint32_t)0x40000000) /*!< Bit 6 */
#define XFMC_ATTMEMTM2_HIZ_7 ((uint32_t)0x80000000) /*!< Bit 7 */

/******************  Bit definition for XFMC_PATT3 register  ******************/
#define XFMC_ATTMEMTM3_SET   ((uint32_t)0x000000FF) /*!< ATTSET3[7:0] bits (Attribute memory 3 setup time) */
#define XFMC_ATTMEMTM3_SET_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define XFMC_ATTMEMTM3_SET_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define XFMC_ATTMEMTM3_SET_2 ((uint32_t)0x00000004) /*!< Bit 2 */
#define XFMC_ATTMEMTM3_SET_3 ((uint32_t)0x00000008) /*!< Bit 3 */
#define XFMC_ATTMEMTM3_SET_4 ((uint32_t)0x00000010) /*!< Bit 4 */
#define XFMC_ATTMEMTM3_SET_5 ((uint32_t)0x00000020) /*!< Bit 5 */
#define XFMC_ATTMEMTM3_SET_6 ((uint32_t)0x00000040) /*!< Bit 6 */
#define XFMC_ATTMEMTM3_SET_7 ((uint32_t)0x00000080) /*!< Bit 7 */

#define XFMC_ATTMEMTM3_WAIT   ((uint32_t)0x0000FF00) /*!< ATTWAIT3[7:0] bits (Attribute memory 3 wait time) */
#define XFMC_ATTMEMTM3_WAIT_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define XFMC_ATTMEMTM3_WAIT_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define XFMC_ATTMEMTM3_WAIT_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define XFMC_ATTMEMTM3_WAIT_3 ((uint32_t)0x00000800) /*!< Bit 3 */
#define XFMC_ATTMEMTM3_WAIT_4 ((uint32_t)0x00001000) /*!< Bit 4 */
#define XFMC_ATTMEMTM3_WAIT_5 ((uint32_t)0x00002000) /*!< Bit 5 */
#define XFMC_ATTMEMTM3_WAIT_6 ((uint32_t)0x00004000) /*!< Bit 6 */
#define XFMC_ATTMEMTM3_WAIT_7 ((uint32_t)0x00008000) /*!< Bit 7 */

#define XFMC_ATTMEMTM3_HLD   ((uint32_t)0x00FF0000) /*!< ATTHOLD3[7:0] bits (Attribute memory 3 hold time) */
#define XFMC_ATTMEMTM3_HLD_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define XFMC_ATTMEMTM3_HLD_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define XFMC_ATTMEMTM3_HLD_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define XFMC_ATTMEMTM3_HLD_3 ((uint32_t)0x00080000) /*!< Bit 3 */
#define XFMC_ATTMEMTM3_HLD_4 ((uint32_t)0x00100000) /*!< Bit 4 */
#define XFMC_ATTMEMTM3_HLD_5 ((uint32_t)0x00200000) /*!< Bit 5 */
#define XFMC_ATTMEMTM3_HLD_6 ((uint32_t)0x00400000) /*!< Bit 6 */
#define XFMC_ATTMEMTM3_HLD_7 ((uint32_t)0x00800000) /*!< Bit 7 */

#define XFMC_ATTMEMTM3_HIZ   ((uint32_t)0xFF000000) /*!< ATTHIZ3[7:0] bits (Attribute memory 3 databus HiZ time) */
#define XFMC_ATTMEMTM3_HIZ_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define XFMC_ATTMEMTM3_HIZ_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define XFMC_ATTMEMTM3_HIZ_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define XFMC_ATTMEMTM3_HIZ_3 ((uint32_t)0x08000000) /*!< Bit 3 */
#define XFMC_ATTMEMTM3_HIZ_4 ((uint32_t)0x10000000) /*!< Bit 4 */
#define XFMC_ATTMEMTM3_HIZ_5 ((uint32_t)0x20000000) /*!< Bit 5 */
#define XFMC_ATTMEMTM3_HIZ_6 ((uint32_t)0x40000000) /*!< Bit 6 */
#define XFMC_ATTMEMTM3_HIZ_7 ((uint32_t)0x80000000) /*!< Bit 7 */

/******************  Bit definition for XFMC_ECCR2 register  ******************/
#define XFMC_ECCR2 ((uint32_t)0xFFFFFFFF) /*!< ECC result */

/******************  Bit definition for XFMC_ECCR3 register  ******************/
#define XFMC_ECCR3_ECC3 ((uint32_t)0xFFFFFFFF) /*!< ECC result */

/******************************************************************************/
/*                                                                            */
/*                                   USB Device FS                            */
/*                                                                            */
/******************************************************************************/

/*!< Endpoint-specific registers */
/*******************  Bit definition for USB_EP0R register  *******************/
#define USB_EP0_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP0_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP0_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP0_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP0_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP0_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP0_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP0_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP0_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP0_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP0_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP0_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP0_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP0_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP0_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP0_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP1R register  *******************/
#define USB_EP1_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP1_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP1_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP1_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP1_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP1_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP1_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP1_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP1_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP1_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP1_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP1_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP1_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP1_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP1_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP1_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP2R register  *******************/
#define USB_EP2_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP2_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP2_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP2_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP2_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP2_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP2_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP2_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP2_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP2_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP2_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP2_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP2_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP2_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP2_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP2_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP3R register  *******************/
#define USB_EP3_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP3_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP3_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP3_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP3_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP3_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP3_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP3_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP3_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP3_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP3_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP3_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP3_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP3_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP3_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP3_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP4R register  *******************/
#define USB_EP4_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP4_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP4_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP4_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP4_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP4_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP4_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP4_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP4_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP4_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP4_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP4_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP4_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP4_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP4_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP4_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP5R register  *******************/
#define USB_EP5_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP5_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP5_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP5_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP5_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP5_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP5_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP5_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP5_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP5_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP5_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP5_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP5_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP5_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP5_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP5_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP6R register  *******************/
#define USB_EP6_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP6_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP6_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP6_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP6_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP6_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP6_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP6_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP6_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP6_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP6_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP6_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP6_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP6_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP6_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP6_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP7R register  *******************/
#define USB_EP7_EPADDR ((uint16_t)0x000F) /*!< Endpoint Address */

#define USB_EP7_STS_TX   ((uint16_t)0x0030) /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP7_STS_TX_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define USB_EP7_STS_TX_1 ((uint16_t)0x0020) /*!< Bit 1 */

#define USB_EP7_DATTOG_TX ((uint16_t)0x0040) /*!< Data Toggle, for transmission transfers */
#define USB_EP7_CTRS_TX   ((uint16_t)0x0080) /*!< Correct Transfer for transmission */
#define USB_EP7_EP_KIND   ((uint16_t)0x0100) /*!< Endpoint Kind */

#define USB_EP7_EP_TYPE   ((uint16_t)0x0600) /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP7_EP_TYPE_0 ((uint16_t)0x0200) /*!< Bit 0 */
#define USB_EP7_EP_TYPE_1 ((uint16_t)0x0400) /*!< Bit 1 */

#define USB_EP7_SETUP ((uint16_t)0x0800) /*!< Setup transaction completed */

#define USB_EP7_STS_RX   ((uint16_t)0x3000) /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP7_STS_RX_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USB_EP7_STS_RX_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USB_EP7_DATTOG_RX ((uint16_t)0x4000) /*!< Data Toggle, for reception transfers */
#define USB_EP7_CTRS_RX   ((uint16_t)0x8000) /*!< Correct Transfer for reception */

/*!< Common registers */
/*******************  Bit definition for USB_CNTR register  *******************/
#define USB_CTRL_FRST    ((uint16_t)0x0001) /*!< Force USB Reset */
#define USB_CTRL_PD      ((uint16_t)0x0002) /*!< Power down */
#define USB_CNTR_LP_MODE ((uint16_t)0x0004) /*!< Low-power mode */
#define USB_CTRL_FSUSPD  ((uint16_t)0x0008) /*!< Force suspend */
#define USB_CTRL_RESUM   ((uint16_t)0x0010) /*!< Resume request */
#define USB_CNTR_ESOFM   ((uint16_t)0x0100) /*!< Expected Start Of Frame Interrupt Mask */
#define USB_CNTR_SOFM    ((uint16_t)0x0200) /*!< Start Of Frame Interrupt Mask */
#define USB_CTRL_RSTM    ((uint16_t)0x0400) /*!< RESET Interrupt Mask */
#define USB_CTRL_SUSPDM  ((uint16_t)0x0800) /*!< Suspend mode Interrupt Mask */
#define USB_CTRL_WKUPM   ((uint16_t)0x1000) /*!< Wakeup Interrupt Mask */
#define USB_CTRL_ERRORM  ((uint16_t)0x2000) /*!< Error Interrupt Mask */
#define USB_CTRL_PMAOM   ((uint16_t)0x4000) /*!< Packet Memory Area Over / Underrun Interrupt Mask */
#define USB_CTRL_CTRSM   ((uint16_t)0x8000) /*!< Correct Transfer Interrupt Mask */

/*******************  Bit definition for USB_ISTR register  *******************/
#define USB_ISTR_EP_ID ((uint16_t)0x000F) /*!< Endpoint Identifier */
#define USB_ISTR_DIR   ((uint16_t)0x0010) /*!< Direction of transaction */
#define USB_ISTR_ESOF  ((uint16_t)0x0100) /*!< Expected Start Of Frame */
#define USB_ISTR_SOF   ((uint16_t)0x0200) /*!< Start Of Frame */
#define USB_STS_RST    ((uint16_t)0x0400) /*!< USB RESET request */
#define USB_STS_SUSPD  ((uint16_t)0x0800) /*!< Suspend mode request */
#define USB_ISTR_WKUP  ((uint16_t)0x1000) /*!< Wake up */
#define USB_STS_ERROR  ((uint16_t)0x2000) /*!< Error */
#define USB_STS_PMAO   ((uint16_t)0x4000) /*!< Packet Memory Area Over / Underrun */
#define USB_STS_CTRS   ((uint16_t)0x8000) /*!< Correct Transfer */

/*******************  Bit definition for USB_FNR register  ********************/
#define USB_FN_FNUM     ((uint16_t)0x07FF) /*!< Frame Number */
#define USB_FN_LSTSOF   ((uint16_t)0x1800) /*!< Lost SOF */
#define USB_FNR_LCK     ((uint16_t)0x2000) /*!< Locked */
#define USB_FN_RXDM_STS ((uint16_t)0x4000) /*!< Receive Data - Line Status */
#define USB_FN_RXDP_STS ((uint16_t)0x8000) /*!< Receive Data + Line Status */

/******************  Bit definition for USB_DADDR register  *******************/
#define USB_ADDR_ADDR  ((uint8_t)0x7F) /*!< ADD[6:0] bits (Device Address) */
#define USB_ADDR_ADDR0 ((uint8_t)0x01) /*!< Bit 0 */
#define USB_ADDR_ADDR1 ((uint8_t)0x02) /*!< Bit 1 */
#define USB_ADDR_ADDR2 ((uint8_t)0x04) /*!< Bit 2 */
#define USB_ADDR_ADDR3 ((uint8_t)0x08) /*!< Bit 3 */
#define USB_ADDR_ADDR4 ((uint8_t)0x10) /*!< Bit 4 */
#define USB_ADDR_ADDR5 ((uint8_t)0x20) /*!< Bit 5 */
#define USB_ADDR_ADDR6 ((uint8_t)0x40) /*!< Bit 6 */

#define USB_ADDR_EFUC ((uint8_t)0x80) /*!< Enable Function */

/******************  Bit definition for USB_BTABLE register  ******************/
#define USB_BUFTAB_BUFTAB ((uint16_t)0xFFF8) /*!< Buffer Table */

/*!< Buffer descriptor table */
/*****************  Bit definition for USB_ADDR0_TX register  *****************/
#define USB_ADDR0_TX_ADDR0_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 0 */

/*****************  Bit definition for USB_ADDR1_TX register  *****************/
#define USB_ADDR1_TX_ADDR1_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 1 */

/*****************  Bit definition for USB_ADDR2_TX register  *****************/
#define USB_ADDR2_TX_ADDR2_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 2 */

/*****************  Bit definition for USB_ADDR3_TX register  *****************/
#define USB_ADDR3_TX_ADDR3_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 3 */

/*****************  Bit definition for USB_ADDR4_TX register  *****************/
#define USB_ADDR4_TX_ADDR4_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 4 */

/*****************  Bit definition for USB_ADDR5_TX register  *****************/
#define USB_ADDR5_TX_ADDR5_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 5 */

/*****************  Bit definition for USB_ADDR6_TX register  *****************/
#define USB_ADDR6_TX_ADDR6_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 6 */

/*****************  Bit definition for USB_ADDR7_TX register  *****************/
#define USB_ADDR7_TX_ADDR7_TX ((uint16_t)0xFFFE) /*!< Transmission Buffer Address 7 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_COUNT0_TX register  ****************/
#define USB_CNT0_TX_CNT0_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 0 */

/*****************  Bit definition for USB_COUNT1_TX register  ****************/
#define USB_CNT1_TX_CNT1_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 1 */

/*****************  Bit definition for USB_COUNT2_TX register  ****************/
#define USB_CNT2_TX_CNT2_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 2 */

/*****************  Bit definition for USB_COUNT3_TX register  ****************/
#define USB_CNT3_TX_CNT3_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 3 */

/*****************  Bit definition for USB_COUNT4_TX register  ****************/
#define USB_CNT4_TX_CNT4_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 4 */

/*****************  Bit definition for USB_COUNT5_TX register  ****************/
#define USB_CNT5_TX_CNT5_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 5 */

/*****************  Bit definition for USB_COUNT6_TX register  ****************/
#define USB_CNT6_TX_CNT6_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 6 */

/*****************  Bit definition for USB_COUNT7_TX register  ****************/
#define USB_CNT7_TX_CNT7_TX ((uint16_t)0x03FF) /*!< Transmission Byte Count 7 */

/*----------------------------------------------------------------------------*/

/****************  Bit definition for USB_COUNT0_TX_0 register  ***************/
#define USB_CNT0_TX_0_CNT0_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 0 (low) */

/****************  Bit definition for USB_COUNT0_TX_1 register  ***************/
#define USB_CNT0_TX_1_CNT0_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 0 (high) */

/****************  Bit definition for USB_COUNT1_TX_0 register  ***************/
#define USB_CNT1_TX_0_CNT1_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 1 (low) */

/****************  Bit definition for USB_COUNT1_TX_1 register  ***************/
#define USB_CNT1_TX_1_CNT1_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 1 (high) */

/****************  Bit definition for USB_COUNT2_TX_0 register  ***************/
#define USB_CNT2_TX_0_CNT2_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 2 (low) */

/****************  Bit definition for USB_COUNT2_TX_1 register  ***************/
#define USB_CNT2_TX_1_CNT2_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 2 (high) */

/****************  Bit definition for USB_COUNT3_TX_0 register  ***************/
#define USB_CNT3_TX_0_CNT3_TX_0 ((uint16_t)0x000003FF) /*!< Transmission Byte Count 3 (low) */

/****************  Bit definition for USB_COUNT3_TX_1 register  ***************/
#define USB_CNT3_TX_1_CNT3_TX_1 ((uint16_t)0x03FF0000) /*!< Transmission Byte Count 3 (high) */

/****************  Bit definition for USB_COUNT4_TX_0 register  ***************/
#define USB_CNT4_TX_0_CNT4_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 4 (low) */

/****************  Bit definition for USB_COUNT4_TX_1 register  ***************/
#define USB_CNT4_TX_1_CNT4_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 4 (high) */

/****************  Bit definition for USB_COUNT5_TX_0 register  ***************/
#define USB_CNT5_TX_0_CNT5_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 5 (low) */

/****************  Bit definition for USB_COUNT5_TX_1 register  ***************/
#define USB_CNT5_TX_1_CNT5_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 5 (high) */

/****************  Bit definition for USB_COUNT6_TX_0 register  ***************/
#define USB_CNT6_TX_0_CNT6_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 6 (low) */

/****************  Bit definition for USB_COUNT6_TX_1 register  ***************/
#define USB_CNT6_TX_1_CNT6_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 6 (high) */

/****************  Bit definition for USB_COUNT7_TX_0 register  ***************/
#define USB_CNT7_TX_0_CNT7_TX_0 ((uint32_t)0x000003FF) /*!< Transmission Byte Count 7 (low) */

/****************  Bit definition for USB_COUNT7_TX_1 register  ***************/
#define USB_CNT7_TX_1_CNT7_TX_1 ((uint32_t)0x03FF0000) /*!< Transmission Byte Count 7 (high) */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_ADDR0_RX register  *****************/
#define USB_ADDR0_RX_ADDR0_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 0 */

/*****************  Bit definition for USB_ADDR1_RX register  *****************/
#define USB_ADDR1_RX_ADDR1_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 1 */

/*****************  Bit definition for USB_ADDR2_RX register  *****************/
#define USB_ADDR2_RX_ADDR2_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 2 */

/*****************  Bit definition for USB_ADDR3_RX register  *****************/
#define USB_ADDR3_RX_ADDR3_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 3 */

/*****************  Bit definition for USB_ADDR4_RX register  *****************/
#define USB_ADDR4_RX_ADDR4_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 4 */

/*****************  Bit definition for USB_ADDR5_RX register  *****************/
#define USB_ADDR5_RX_ADDR5_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 5 */

/*****************  Bit definition for USB_ADDR6_RX register  *****************/
#define USB_ADDR6_RX_ADDR6_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 6 */

/*****************  Bit definition for USB_ADDR7_RX register  *****************/
#define USB_ADDR7_RX_ADDR7_RX ((uint16_t)0xFFFE) /*!< Reception Buffer Address 7 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_COUNT0_RX register  ****************/
#define USB_CNT0_RX_CNT0_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT0_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT0_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT0_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT0_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT0_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT0_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT0_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT1_RX register  ****************/
#define USB_CNT1_RX_CNT1_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT1_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT1_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT1_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT1_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT1_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT1_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT1_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT2_RX register  ****************/
#define USB_CNT2_RX_CNT2_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT2_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT2_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT2_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT2_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT2_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT2_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT2_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT3_RX register  ****************/
#define USB_CNT3_RX_CNT3_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT3_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT3_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT3_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT3_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT3_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT3_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT3_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT4_RX register  ****************/
#define USB_CNT4_RX_CNT4_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT4_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT4_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT4_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT4_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT4_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT4_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT4_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT5_RX register  ****************/
#define USB_CNT5_RX_CNT5_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT5_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT5_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT5_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT5_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT5_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT5_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT5_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT6_RX register  ****************/
#define USB_CNT6_RX_CNT6_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT6_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT6_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT6_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT6_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT6_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT6_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT6_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT7_RX register  ****************/
#define USB_CNT7_RX_CNT7_RX ((uint16_t)0x03FF) /*!< Reception Byte Count */

#define USB_CNT7_RX_NUM_BLK   ((uint16_t)0x7C00) /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_CNT7_RX_NUM_BLK_0 ((uint16_t)0x0400) /*!< Bit 0 */
#define USB_CNT7_RX_NUM_BLK_1 ((uint16_t)0x0800) /*!< Bit 1 */
#define USB_CNT7_RX_NUM_BLK_2 ((uint16_t)0x1000) /*!< Bit 2 */
#define USB_CNT7_RX_NUM_BLK_3 ((uint16_t)0x2000) /*!< Bit 3 */
#define USB_CNT7_RX_NUM_BLK_4 ((uint16_t)0x4000) /*!< Bit 4 */

#define USB_CNT7_RX_BLSIZE ((uint16_t)0x8000) /*!< BLock SIZE */

/*----------------------------------------------------------------------------*/

/****************  Bit definition for USB_COUNT0_RX_0 register  ***************/
#define USB_CNT0_RX_0_CNT0_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT0_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT0_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT0_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT0_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT0_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT0_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT0_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT0_RX_1 register  ***************/
#define USB_CNT0_RX_1_CNT0_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT0_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT0_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 1 */
#define USB_CNT0_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT0_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT0_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT0_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT0_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT1_RX_0 register  ***************/
#define USB_CNT1_RX_0_CNT1_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT1_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT1_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT1_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT1_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT1_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT1_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT1_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT1_RX_1 register  ***************/
#define USB_CNT1_RX_1_CNT1_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT1_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT1_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT1_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT1_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT1_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT1_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT1_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT2_RX_0 register  ***************/
#define USB_CNT2_RX_0_CNT2_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT2_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT2_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT2_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT2_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT2_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT2_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT2_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT2_RX_1 register  ***************/
#define USB_CNT2_RX_1_CNT2_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT2_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT2_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT2_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT2_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT2_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT2_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT2_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT3_RX_0 register  ***************/
#define USB_CNT3_RX_0_CNT3_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT3_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT3_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT3_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT3_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT3_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT3_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT3_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT3_RX_1 register  ***************/
#define USB_CNT3_RX_1_CNT3_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT3_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT3_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT3_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT3_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT3_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT3_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT3_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT4_RX_0 register  ***************/
#define USB_CNT4_RX_0_CNT4_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT4_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT4_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT4_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT4_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT4_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT4_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT4_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT4_RX_1 register  ***************/
#define USB_CNT4_RX_1_CNT4_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT4_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT4_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT4_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT4_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT4_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT4_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT4_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT5_RX_0 register  ***************/
#define USB_CNT5_RX_0_CNT5_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT5_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT5_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT5_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT5_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT5_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT5_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT5_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT5_RX_1 register  ***************/
#define USB_CNT5_RX_1_CNT5_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT5_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT5_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT5_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT5_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT5_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT5_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT5_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/***************  Bit definition for USB_COUNT6_RX_0  register  ***************/
#define USB_CNT6_RX_0_CNT6_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT6_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT6_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT6_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT6_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT6_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT6_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT6_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT6_RX_1 register  ***************/
#define USB_CNT6_RX_1_CNT6_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT6_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT6_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT6_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT6_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT6_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT6_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT6_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/***************  Bit definition for USB_COUNT7_RX_0 register  ****************/
#define USB_CNT7_RX_0_CNT7_RX_0 ((uint32_t)0x000003FF) /*!< Reception Byte Count (low) */

#define USB_CNT7_RX_0_NUM_BLK_0   ((uint32_t)0x00007C00) /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_CNT7_RX_0_NUM_BLK_0_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define USB_CNT7_RX_0_NUM_BLK_0_1 ((uint32_t)0x00000800) /*!< Bit 1 */
#define USB_CNT7_RX_0_NUM_BLK_0_2 ((uint32_t)0x00001000) /*!< Bit 2 */
#define USB_CNT7_RX_0_NUM_BLK_0_3 ((uint32_t)0x00002000) /*!< Bit 3 */
#define USB_CNT7_RX_0_NUM_BLK_0_4 ((uint32_t)0x00004000) /*!< Bit 4 */

#define USB_CNT7_RX_0_BLSIZE_0 ((uint32_t)0x00008000) /*!< BLock SIZE (low) */

/***************  Bit definition for USB_COUNT7_RX_1 register  ****************/
#define USB_CNT7_RX_1_CNT7_RX_1 ((uint32_t)0x03FF0000) /*!< Reception Byte Count (high) */

#define USB_CNT7_RX_1_NUM_BLK_1   ((uint32_t)0x7C000000) /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_CNT7_RX_1_NUM_BLK_1_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define USB_CNT7_RX_1_NUM_BLK_1_1 ((uint32_t)0x08000000) /*!< Bit 1 */
#define USB_CNT7_RX_1_NUM_BLK_1_2 ((uint32_t)0x10000000) /*!< Bit 2 */
#define USB_CNT7_RX_1_NUM_BLK_1_3 ((uint32_t)0x20000000) /*!< Bit 3 */
#define USB_CNT7_RX_1_NUM_BLK_1_4 ((uint32_t)0x40000000) /*!< Bit 4 */

#define USB_CNT7_RX_1_BLSIZE_1 ((uint32_t)0x80000000) /*!< BLock SIZE (high) */

/******************************************************************************/
/*                                                                            */
/*                         Controller Area Network                            */
/*                                                                            */
/******************************************************************************/

/*!< CAN control and status registers */
/*******************  Bit definition for CAN_MCTRL register  ********************/
#define CAN_MCTRL_INIRQ ((uint16_t)0x0001) /*!< Initialization Request */
#define CAN_MCTRL_SLPRQ ((uint16_t)0x0002) /*!< Sleep Mode Request */
#define CAN_MCTRL_TXFP  ((uint16_t)0x0004) /*!< Transmit DATFIFO Priority */
#define CAN_MCTRL_RFLM  ((uint16_t)0x0008) /*!< Receive DATFIFO Locked Mode */
#define CAN_MCTRL_NART  ((uint16_t)0x0010) /*!< No Automatic Retransmission */
#define CAN_MCTRL_AWKUM ((uint16_t)0x0020) /*!< Automatic Wakeup Mode */
#define CAN_MCTRL_ABOM  ((uint16_t)0x0040) /*!< Automatic Bus-Off Management */
#define CAN_MCTRL_TTCM  ((uint16_t)0x0080) /*!< Time Triggered Communication Mode */
#define CAN_MCTRL_MRST  ((uint16_t)0x8000) /*!< CAN software master reset */
#define CAN_MCTRL_DBGF  ((uint32_t)0x00010000) /*!< CAN Debug freeze */

/*******************  Bit definition for CAN_MSTS register  ********************/
#define CAN_MSTS_INIAK   ((uint16_t)0x0001) /*!< Initialization Acknowledge */
#define CAN_MSTS_SLPAK   ((uint16_t)0x0002) /*!< Sleep Acknowledge */
#define CAN_MSTS_ERRINT  ((uint16_t)0x0004) /*!< Error Interrupt */
#define CAN_MSTS_WKUINT  ((uint16_t)0x0008) /*!< Wakeup Interrupt */
#define CAN_MSTS_SLAKINT ((uint16_t)0x0010) /*!< Sleep Acknowledge Interrupt */
#define CAN_MSTS_TXMD    ((uint16_t)0x0100) /*!< Transmit Mode */
#define CAN_MSTS_RXMD    ((uint16_t)0x0200) /*!< Receive Mode */
#define CAN_MSTS_LSMP    ((uint16_t)0x0400) /*!< Last Sample Point */
#define CAN_MSTS_RXS     ((uint16_t)0x0800) /*!< CAN Rx Signal */

/*******************  Bit definition for CAN_TSTS register  ********************/
#define CAN_TSTS_RQCPM0 ((uint32_t)0x00000001) /*!< Request Completed Mailbox0 */
#define CAN_TSTS_TXOKM0 ((uint32_t)0x00000002) /*!< Transmission OK of Mailbox0 */
#define CAN_TSTS_ALSTM0 ((uint32_t)0x00000004) /*!< Arbitration Lost for Mailbox0 */
#define CAN_TSTS_TERRM0 ((uint32_t)0x00000008) /*!< Transmission Error of Mailbox0 */
#define CAN_TSTS_ABRQM0 ((uint32_t)0x00000080) /*!< Abort Request for Mailbox0 */
#define CAN_TSTS_RQCPM1 ((uint32_t)0x00000100) /*!< Request Completed Mailbox1 */
#define CAN_TSTS_TXOKM1 ((uint32_t)0x00000200) /*!< Transmission OK of Mailbox1 */
#define CAN_TSTS_ALSTM1 ((uint32_t)0x00000400) /*!< Arbitration Lost for Mailbox1 */
#define CAN_TSTS_TERRM1 ((uint32_t)0x00000800) /*!< Transmission Error of Mailbox1 */
#define CAN_TSTS_ABRQM1 ((uint32_t)0x00008000) /*!< Abort Request for Mailbox 1 */
#define CAN_TSTS_RQCPM2 ((uint32_t)0x00010000) /*!< Request Completed Mailbox2 */
#define CAN_TSTS_TXOKM2 ((uint32_t)0x00020000) /*!< Transmission OK of Mailbox 2 */
#define CAN_TSTS_ALSTM2 ((uint32_t)0x00040000) /*!< Arbitration Lost for mailbox 2 */
#define CAN_TSTS_TERRM2 ((uint32_t)0x00080000) /*!< Transmission Error of Mailbox 2 */
#define CAN_TSTS_ABRQM2 ((uint32_t)0x00800000) /*!< Abort Request for Mailbox 2 */
#define CAN_TSTS_CODE   ((uint32_t)0x03000000) /*!< Mailbox Code */

#define CAN_TSTS_TMEM  ((uint32_t)0x1C000000) /*!< TME[2:0] bits */
#define CAN_TSTS_TMEM0 ((uint32_t)0x04000000) /*!< Transmit Mailbox 0 Empty */
#define CAN_TSTS_TMEM1 ((uint32_t)0x08000000) /*!< Transmit Mailbox 1 Empty */
#define CAN_TSTS_TMEM2 ((uint32_t)0x10000000) /*!< Transmit Mailbox 2 Empty */

#define CAN_TSTS_LOWM  ((uint32_t)0xE0000000) /*!< LOW[2:0] bits */
#define CAN_TSTS_LOWM0 ((uint32_t)0x20000000) /*!< Lowest Priority Flag for Mailbox 0 */
#define CAN_TSTS_LOWM1 ((uint32_t)0x40000000) /*!< Lowest Priority Flag for Mailbox 1 */
#define CAN_TSTS_LOWM2 ((uint32_t)0x80000000) /*!< Lowest Priority Flag for Mailbox 2 */

/*******************  Bit definition for CAN_RFF0 register  *******************/
#define CAN_RFF0_FFMP0  ((uint8_t)0x03) /*!< DATFIFO 0 Message Pending */
#define CAN_RFF0_FFULL0 ((uint8_t)0x08) /*!< DATFIFO 0 Full */
#define CAN_RFF0_FFOVR0 ((uint8_t)0x10) /*!< DATFIFO 0 Overrun */
#define CAN_RFF0_RFFOM0 ((uint8_t)0x20) /*!< Release DATFIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RFF1 register  *******************/
#define CAN_RFF1_FFMP1  ((uint8_t)0x03) /*!< DATFIFO 1 Message Pending */
#define CAN_RFF1_FFULL1 ((uint8_t)0x08) /*!< DATFIFO 1 Full */
#define CAN_RFF1_FFOVR1 ((uint8_t)0x10) /*!< DATFIFO 1 Overrun */
#define CAN_RFF1_RFFOM1 ((uint8_t)0x20) /*!< Release DATFIFO 1 Output Mailbox */

/********************  Bit definition for CAN_INTE register  *******************/
#define CAN_INTE_TMEITE  ((uint32_t)0x00000001) /*!< Transmit Mailbox Empty Interrupt Enable */
#define CAN_INTE_FMPITE0 ((uint32_t)0x00000002) /*!< DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE0  ((uint32_t)0x00000004) /*!< DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE0 ((uint32_t)0x00000008) /*!< DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_FMPITE1 ((uint32_t)0x00000010) /*!< DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE1  ((uint32_t)0x00000020) /*!< DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE1 ((uint32_t)0x00000040) /*!< DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_EWGITE  ((uint32_t)0x00000100) /*!< Error Warning Interrupt Enable */
#define CAN_INTE_EPVITE  ((uint32_t)0x00000200) /*!< Error Passive Interrupt Enable */
#define CAN_INTE_BOFITE  ((uint32_t)0x00000400) /*!< Bus-Off Interrupt Enable */
#define CAN_INTE_LECITE  ((uint32_t)0x00000800) /*!< Last Error Code Interrupt Enable */
#define CAN_INTE_ERRITE  ((uint32_t)0x00008000) /*!< Error Interrupt Enable */
#define CAN_INTE_WKUITE  ((uint32_t)0x00010000) /*!< Wakeup Interrupt Enable */
#define CAN_INTE_SLKITE  ((uint32_t)0x00020000) /*!< Sleep Interrupt Enable */

/********************  Bit definition for CAN_ESTS register  *******************/
#define CAN_ESTS_EWGFL ((uint32_t)0x00000001) /*!< Error Warning Flag */
#define CAN_ESTS_EPVFL ((uint32_t)0x00000002) /*!< Error Passive Flag */
#define CAN_ESTS_BOFFL ((uint32_t)0x00000004) /*!< Bus-Off Flag */

#define CAN_ESTS_LEC   ((uint32_t)0x00000070) /*!< LEC[2:0] bits (Last Error Code) */
#define CAN_ESTS_LEC_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define CAN_ESTS_LEC_1 ((uint32_t)0x00000020) /*!< Bit 1 */
#define CAN_ESTS_LEC_2 ((uint32_t)0x00000040) /*!< Bit 2 */

#define CAN_ESTS_TXEC ((uint32_t)0x00FF0000) /*!< Least significant byte of the 9-bit Transmit Error Counter */
#define CAN_ESTS_RXEC ((uint32_t)0xFF000000) /*!< Receive Error Counter */

/*******************  Bit definition for CAN_BTIM register  ********************/
#define CAN_BTIM_BRTP ((uint32_t)0x000003FF) /*!< Baud Rate Prescaler */
#define CAN_BTIM_TBS1 ((uint32_t)0x000F0000) /*!< Time Segment 1 */
#define CAN_BTIM_TBS2 ((uint32_t)0x00700000) /*!< Time Segment 2 */
#define CAN_BTIM_RSJW ((uint32_t)0x03000000) /*!< Resynchronization Jump Width */
#define CAN_BTIM_LBM  ((uint32_t)0x40000000) /*!< Loop Back Mode (Debug) */
#define CAN_BTIM_SLM  ((uint32_t)0x80000000) /*!< Silent Mode */

/*!< Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define CAN_TMI0_TXRQ  ((uint32_t)0x00000001) /*!< Transmit Mailbox Request */
#define CAN_TMI0_RTRQ  ((uint32_t)0x00000002) /*!< Remote Transmission Request */
#define CAN_TMI0_IDE   ((uint32_t)0x00000004) /*!< Identifier Extension */
#define CAN_TMI0_EXTID ((uint32_t)0x001FFFF8) /*!< Extended Identifier */
#define CAN_TMI0_STDID ((uint32_t)0xFFE00000) /*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TDT0R register  *******************/
#define CAN_TMDT0_DLC  ((uint32_t)0x0000000F) /*!< Data Length Code */
#define CAN_TMDT0_TGT  ((uint32_t)0x00000100) /*!< Transmit Global Time */
#define CAN_TMDT0_MTIM ((uint32_t)0xFFFF0000) /*!< Message Time Stamp */

/******************  Bit definition for CAN_TDL0R register  *******************/
#define CAN_TMDL0_DATA0 ((uint32_t)0x000000FF) /*!< Data byte 0 */
#define CAN_TMDL0_DATA1 ((uint32_t)0x0000FF00) /*!< Data byte 1 */
#define CAN_TMDL0_DATA2 ((uint32_t)0x00FF0000) /*!< Data byte 2 */
#define CAN_TMDL0_DATA3 ((uint32_t)0xFF000000) /*!< Data byte 3 */

/******************  Bit definition for CAN_TDH0R register  *******************/
#define CAN_TMDH0_DATA4 ((uint32_t)0x000000FF) /*!< Data byte 4 */
#define CAN_TMDH0_DATA5 ((uint32_t)0x0000FF00) /*!< Data byte 5 */
#define CAN_TMDH0_DATA6 ((uint32_t)0x00FF0000) /*!< Data byte 6 */
#define CAN_TMDH0_DATA7 ((uint32_t)0xFF000000) /*!< Data byte 7 */

/*******************  Bit definition for CAN_TI1R register  *******************/
#define CAN_TMI1_TXRQ  ((uint32_t)0x00000001) /*!< Transmit Mailbox Request */
#define CAN_TMI1_RTRQ  ((uint32_t)0x00000002) /*!< Remote Transmission Request */
#define CAN_TMI1_IDE   ((uint32_t)0x00000004) /*!< Identifier Extension */
#define CAN_TMI1_EXTID ((uint32_t)0x001FFFF8) /*!< Extended Identifier */
#define CAN_TMI1_STDID ((uint32_t)0xFFE00000) /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT1R register  ******************/
#define CAN_TMDT1_DLC  ((uint32_t)0x0000000F) /*!< Data Length Code */
#define CAN_TMDT1_TGT  ((uint32_t)0x00000100) /*!< Transmit Global Time */
#define CAN_TMDT1_MTIM ((uint32_t)0xFFFF0000) /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL1R register  ******************/
#define CAN_TMDL1_DATA0 ((uint32_t)0x000000FF) /*!< Data byte 0 */
#define CAN_TMDL1_DATA1 ((uint32_t)0x0000FF00) /*!< Data byte 1 */
#define CAN_TMDL1_DATA2 ((uint32_t)0x00FF0000) /*!< Data byte 2 */
#define CAN_TMDL1_DATA3 ((uint32_t)0xFF000000) /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH1R register  ******************/
#define CAN_TMDH1_DATA4 ((uint32_t)0x000000FF) /*!< Data byte 4 */
#define CAN_TMDH1_DATA5 ((uint32_t)0x0000FF00) /*!< Data byte 5 */
#define CAN_TMDH1_DATA6 ((uint32_t)0x00FF0000) /*!< Data byte 6 */
#define CAN_TMDH1_DATA7 ((uint32_t)0xFF000000) /*!< Data byte 7 */

/*******************  Bit definition for CAN_TI2R register  *******************/
#define CAN_TMI2_TXRQ  ((uint32_t)0x00000001) /*!< Transmit Mailbox Request */
#define CAN_TMI2_RTRQ  ((uint32_t)0x00000002) /*!< Remote Transmission Request */
#define CAN_TMI2_IDE   ((uint32_t)0x00000004) /*!< Identifier Extension */
#define CAN_TMI2_EXTID ((uint32_t)0x001FFFF8) /*!< Extended identifier */
#define CAN_TMI2_STDID ((uint32_t)0xFFE00000) /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT2R register  ******************/
#define CAN_TMDT2_DLC  ((uint32_t)0x0000000F) /*!< Data Length Code */
#define CAN_TMDT2_TGT  ((uint32_t)0x00000100) /*!< Transmit Global Time */
#define CAN_TMDT2_MTIM ((uint32_t)0xFFFF0000) /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL2R register  ******************/
#define CAN_TMDL2_DATA0 ((uint32_t)0x000000FF) /*!< Data byte 0 */
#define CAN_TMDL2_DATA1 ((uint32_t)0x0000FF00) /*!< Data byte 1 */
#define CAN_TMDL2_DATA2 ((uint32_t)0x00FF0000) /*!< Data byte 2 */
#define CAN_TMDL2_DATA3 ((uint32_t)0xFF000000) /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH2R register  ******************/
#define CAN_TMDH2_DATA4 ((uint32_t)0x000000FF) /*!< Data byte 4 */
#define CAN_TMDH2_DATA5 ((uint32_t)0x0000FF00) /*!< Data byte 5 */
#define CAN_TMDH2_DATA6 ((uint32_t)0x00FF0000) /*!< Data byte 6 */
#define CAN_TMDH2_DATA7 ((uint32_t)0xFF000000) /*!< Data byte 7 */

/*******************  Bit definition for CAN_RI0R register  *******************/
#define CAN_RMI0_RTRQ  ((uint32_t)0x00000002) /*!< Remote Transmission Request */
#define CAN_RMI0_IDE   ((uint32_t)0x00000004) /*!< Identifier Extension */
#define CAN_RMI0_EXTID ((uint32_t)0x001FFFF8) /*!< Extended Identifier */
#define CAN_RMI0_STDID ((uint32_t)0xFFE00000) /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0R register  ******************/
#define CAN_RMDT0_DLC  ((uint32_t)0x0000000F) /*!< Data Length Code */
#define CAN_RMDT0_FMI  ((uint32_t)0x0000FF00) /*!< Filter Match Index */
#define CAN_RMDT0_MTIM ((uint32_t)0xFFFF0000) /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL0R register  ******************/
#define CAN_RMDL0_DATA0 ((uint32_t)0x000000FF) /*!< Data byte 0 */
#define CAN_RMDL0_DATA1 ((uint32_t)0x0000FF00) /*!< Data byte 1 */
#define CAN_RMDL0_DATA2 ((uint32_t)0x00FF0000) /*!< Data byte 2 */
#define CAN_RMDL0_DATA3 ((uint32_t)0xFF000000) /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH0R register  ******************/
#define CAN_RMDH0_DATA4 ((uint32_t)0x000000FF) /*!< Data byte 4 */
#define CAN_RMDH0_DATA5 ((uint32_t)0x0000FF00) /*!< Data byte 5 */
#define CAN_RMDH0_DATA6 ((uint32_t)0x00FF0000) /*!< Data byte 6 */
#define CAN_RMDH0_DATA7 ((uint32_t)0xFF000000) /*!< Data byte 7 */

/*******************  Bit definition for CAN_RI1R register  *******************/
#define CAN_RMI1_RTRQ  ((uint32_t)0x00000002) /*!< Remote Transmission Request */
#define CAN_RMI1_IDE   ((uint32_t)0x00000004) /*!< Identifier Extension */
#define CAN_RMI1_EXTID ((uint32_t)0x001FFFF8) /*!< Extended identifier */
#define CAN_RMI1_STDID ((uint32_t)0xFFE00000) /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT1R register  ******************/
#define CAN_RMDT1_DLC  ((uint32_t)0x0000000F) /*!< Data Length Code */
#define CAN_RMDT1_FMI  ((uint32_t)0x0000FF00) /*!< Filter Match Index */
#define CAN_RMDT1_MTIM ((uint32_t)0xFFFF0000) /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL1R register  ******************/
#define CAN_RMDL1_DATA0 ((uint32_t)0x000000FF) /*!< Data byte 0 */
#define CAN_RMDL1_DATA1 ((uint32_t)0x0000FF00) /*!< Data byte 1 */
#define CAN_RMDL1_DATA2 ((uint32_t)0x00FF0000) /*!< Data byte 2 */
#define CAN_RMDL1_DATA3 ((uint32_t)0xFF000000) /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH1R register  ******************/
#define CAN_RMDH1_DATA4 ((uint32_t)0x000000FF) /*!< Data byte 4 */
#define CAN_RMDH1_DATA5 ((uint32_t)0x0000FF00) /*!< Data byte 5 */
#define CAN_RMDH1_DATA6 ((uint32_t)0x00FF0000) /*!< Data byte 6 */
#define CAN_RMDH1_DATA7 ((uint32_t)0xFF000000) /*!< Data byte 7 */

/*!< CAN filter registers */
/*******************  Bit definition for CAN_FMC register  ********************/
#define CAN_FMC_FINITM ((uint8_t)0x01) /*!< Filter Init Mode */

/*******************  Bit definition for CAN_FM1 register  *******************/
#define CAN_FM1_FB   ((uint16_t)0x3FFF) /*!< Filter Mode */
#define CAN_FM1_FB0  ((uint16_t)0x0001) /*!< Filter Init Mode bit 0 */
#define CAN_FM1_FB1  ((uint16_t)0x0002) /*!< Filter Init Mode bit 1 */
#define CAN_FM1_FB2  ((uint16_t)0x0004) /*!< Filter Init Mode bit 2 */
#define CAN_FM1_FB3  ((uint16_t)0x0008) /*!< Filter Init Mode bit 3 */
#define CAN_FM1_FB4  ((uint16_t)0x0010) /*!< Filter Init Mode bit 4 */
#define CAN_FM1_FB5  ((uint16_t)0x0020) /*!< Filter Init Mode bit 5 */
#define CAN_FM1_FB6  ((uint16_t)0x0040) /*!< Filter Init Mode bit 6 */
#define CAN_FM1_FB7  ((uint16_t)0x0080) /*!< Filter Init Mode bit 7 */
#define CAN_FM1_FB8  ((uint16_t)0x0100) /*!< Filter Init Mode bit 8 */
#define CAN_FM1_FB9  ((uint16_t)0x0200) /*!< Filter Init Mode bit 9 */
#define CAN_FM1_FB10 ((uint16_t)0x0400) /*!< Filter Init Mode bit 10 */
#define CAN_FM1_FB11 ((uint16_t)0x0800) /*!< Filter Init Mode bit 11 */
#define CAN_FM1_FB12 ((uint16_t)0x1000) /*!< Filter Init Mode bit 12 */
#define CAN_FM1_FB13 ((uint16_t)0x2000) /*!< Filter Init Mode bit 13 */

/*******************  Bit definition for CAN_FS1 register  *******************/
#define CAN_FS1_FSC   ((uint16_t)0x3FFF) /*!< Filter Scale Configuration */
#define CAN_FS1_FSC0  ((uint16_t)0x0001) /*!< Filter Scale Configuration bit 0 */
#define CAN_FS1_FSC1  ((uint16_t)0x0002) /*!< Filter Scale Configuration bit 1 */
#define CAN_FS1_FSC2  ((uint16_t)0x0004) /*!< Filter Scale Configuration bit 2 */
#define CAN_FS1_FSC3  ((uint16_t)0x0008) /*!< Filter Scale Configuration bit 3 */
#define CAN_FS1_FSC4  ((uint16_t)0x0010) /*!< Filter Scale Configuration bit 4 */
#define CAN_FS1_FSC5  ((uint16_t)0x0020) /*!< Filter Scale Configuration bit 5 */
#define CAN_FS1_FSC6  ((uint16_t)0x0040) /*!< Filter Scale Configuration bit 6 */
#define CAN_FS1_FSC7  ((uint16_t)0x0080) /*!< Filter Scale Configuration bit 7 */
#define CAN_FS1_FSC8  ((uint16_t)0x0100) /*!< Filter Scale Configuration bit 8 */
#define CAN_FS1_FSC9  ((uint16_t)0x0200) /*!< Filter Scale Configuration bit 9 */
#define CAN_FS1_FSC10 ((uint16_t)0x0400) /*!< Filter Scale Configuration bit 10 */
#define CAN_FS1_FSC11 ((uint16_t)0x0800) /*!< Filter Scale Configuration bit 11 */
#define CAN_FS1_FSC12 ((uint16_t)0x1000) /*!< Filter Scale Configuration bit 12 */
#define CAN_FS1_FSC13 ((uint16_t)0x2000) /*!< Filter Scale Configuration bit 13 */

/******************  Bit definition for CAN_FFA1 register  *******************/
#define CAN_FFA1_FAF   ((uint16_t)0x3FFF) /*!< Filter DATFIFO Assignment */
#define CAN_FFA1_FAF0  ((uint16_t)0x0001) /*!< Filter DATFIFO Assignment for Filter 0 */
#define CAN_FFA1_FAF1  ((uint16_t)0x0002) /*!< Filter DATFIFO Assignment for Filter 1 */
#define CAN_FFA1_FAF2  ((uint16_t)0x0004) /*!< Filter DATFIFO Assignment for Filter 2 */
#define CAN_FFA1_FAF3  ((uint16_t)0x0008) /*!< Filter DATFIFO Assignment for Filter 3 */
#define CAN_FFA1_FAF4  ((uint16_t)0x0010) /*!< Filter DATFIFO Assignment for Filter 4 */
#define CAN_FFA1_FAF5  ((uint16_t)0x0020) /*!< Filter DATFIFO Assignment for Filter 5 */
#define CAN_FFA1_FAF6  ((uint16_t)0x0040) /*!< Filter DATFIFO Assignment for Filter 6 */
#define CAN_FFA1_FAF7  ((uint16_t)0x0080) /*!< Filter DATFIFO Assignment for Filter 7 */
#define CAN_FFA1_FAF8  ((uint16_t)0x0100) /*!< Filter DATFIFO Assignment for Filter 8 */
#define CAN_FFA1_FAF9  ((uint16_t)0x0200) /*!< Filter DATFIFO Assignment for Filter 9 */
#define CAN_FFA1_FAF10 ((uint16_t)0x0400) /*!< Filter DATFIFO Assignment for Filter 10 */
#define CAN_FFA1_FAF11 ((uint16_t)0x0800) /*!< Filter DATFIFO Assignment for Filter 11 */
#define CAN_FFA1_FAF12 ((uint16_t)0x1000) /*!< Filter DATFIFO Assignment for Filter 12 */
#define CAN_FFA1_FAF13 ((uint16_t)0x2000) /*!< Filter DATFIFO Assignment for Filter 13 */

/*******************  Bit definition for CAN_FA1 register  *******************/
#define CAN_FA1_FAC   ((uint16_t)0x3FFF) /*!< Filter Active */
#define CAN_FA1_FAC0  ((uint16_t)0x0001) /*!< Filter 0 Active */
#define CAN_FA1_FAC1  ((uint16_t)0x0002) /*!< Filter 1 Active */
#define CAN_FA1_FAC2  ((uint16_t)0x0004) /*!< Filter 2 Active */
#define CAN_FA1_FAC3  ((uint16_t)0x0008) /*!< Filter 3 Active */
#define CAN_FA1_FAC4  ((uint16_t)0x0010) /*!< Filter 4 Active */
#define CAN_FA1_FAC5  ((uint16_t)0x0020) /*!< Filter 5 Active */
#define CAN_FA1_FAC6  ((uint16_t)0x0040) /*!< Filter 6 Active */
#define CAN_FA1_FAC7  ((uint16_t)0x0080) /*!< Filter 7 Active */
#define CAN_FA1_FAC8  ((uint16_t)0x0100) /*!< Filter 8 Active */
#define CAN_FA1_FAC9  ((uint16_t)0x0200) /*!< Filter 9 Active */
#define CAN_FA1_FAC10 ((uint16_t)0x0400) /*!< Filter 10 Active */
#define CAN_FA1_FAC11 ((uint16_t)0x0800) /*!< Filter 11 Active */
#define CAN_FA1_FAC12 ((uint16_t)0x1000) /*!< Filter 12 Active */
#define CAN_FA1_FAC13 ((uint16_t)0x2000) /*!< Filter 13 Active */

/*******************  Bit definition for CAN_F0R1 register  *******************/
#define CAN_F0B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F0B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F0B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F0B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F0B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F0B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F0B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F0B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F0B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F0B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F0B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F0B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F0B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F0B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F0B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F0B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F0B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F0B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F0B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F0B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F0B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F0B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F0B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F0B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F0B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F0B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F0B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F0B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F0B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F0B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F0B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F0B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F1R1 register  *******************/
#define CAN_F1B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F1B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F1B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F1B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F1B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F1B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F1B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F1B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F1B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F1B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F1B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F1B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F1B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F1B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F1B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F1B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F1B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F1B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F1B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F1B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F1B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F1B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F1B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F1B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F1B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F1B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F1B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F1B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F1B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F1B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F1B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F1B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F2R1 register  *******************/
#define CAN_F2B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F2B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F2B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F2B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F2B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F2B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F2B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F2B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F2B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F2B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F2B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F2B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F2B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F2B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F2B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F2B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F2B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F2B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F2B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F2B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F2B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F2B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F2B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F2B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F2B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F2B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F2B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F2B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F2B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F2B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F2B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F2B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F3R1 register  *******************/
#define CAN_F3B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F3B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F3B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F3B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F3B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F3B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F3B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F3B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F3B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F3B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F3B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F3B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F3B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F3B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F3B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F3B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F3B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F3B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F3B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F3B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F3B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F3B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F3B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F3B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F3B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F3B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F3B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F3B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F3B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F3B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F3B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F3B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F4R1 register  *******************/
#define CAN_F4B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F4B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F4B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F4B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F4B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F4B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F4B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F4B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F4B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F4B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F4B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F4B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F4B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F4B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F4B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F4B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F4B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F4B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F4B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F4B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F4B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F4B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F4B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F4B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F4B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F4B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F4B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F4B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F4B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F4B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F4B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F4B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F5R1 register  *******************/
#define CAN_F5B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F5B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F5B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F5B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F5B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F5B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F5B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F5B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F5B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F5B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F5B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F5B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F5B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F5B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F5B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F5B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F5B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F5B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F5B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F5B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F5B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F5B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F5B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F5B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F5B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F5B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F5B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F5B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F5B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F5B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F5B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F5B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F6R1 register  *******************/
#define CAN_F6B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F6B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F6B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F6B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F6B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F6B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F6B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F6B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F6B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F6B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F6B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F6B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F6B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F6B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F6B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F6B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F6B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F6B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F6B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F6B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F6B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F6B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F6B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F6B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F6B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F6B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F6B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F6B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F6B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F6B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F6B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F6B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F7R1 register  *******************/
#define CAN_F7B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F7B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F7B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F7B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F7B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F7B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F7B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F7B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F7B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F7B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F7B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F7B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F7B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F7B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F7B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F7B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F7B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F7B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F7B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F7B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F7B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F7B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F7B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F7B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F7B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F7B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F7B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F7B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F7B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F7B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F7B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F7B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F8R1 register  *******************/
#define CAN_F8B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F8B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F8B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F8B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F8B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F8B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F8B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F8B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F8B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F8B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F8B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F8B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F8B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F8B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F8B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F8B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F8B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F8B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F8B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F8B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F8B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F8B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F8B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F8B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F8B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F8B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F8B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F8B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F8B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F8B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F8B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F8B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F9R1 register  *******************/
#define CAN_F9B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F9B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F9B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F9B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F9B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F9B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F9B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F9B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F9B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F9B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F9B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F9B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F9B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F9B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F9B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F9B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F9B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F9B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F9B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F9B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F9B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F9B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F9B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F9B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F9B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F9B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F9B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F9B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F9B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F9B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F9B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F9B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F10R1 register  ******************/
#define CAN_F10B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F10B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F10B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F10B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F10B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F10B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F10B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F10B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F10B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F10B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F10B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F10B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F10B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F10B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F10B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F10B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F10B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F10B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F10B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F10B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F10B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F10B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F10B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F10B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F10B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F10B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F10B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F10B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F10B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F10B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F10B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F10B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F11R1 register  ******************/
#define CAN_F11B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F11B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F11B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F11B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F11B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F11B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F11B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F11B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F11B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F11B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F11B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F11B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F11B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F11B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F11B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F11B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F11B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F11B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F11B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F11B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F11B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F11B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F11B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F11B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F11B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F11B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F11B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F11B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F11B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F11B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F11B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F11B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F12R1 register  ******************/
#define CAN_F12B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F12B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F12B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F12B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F12B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F12B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F12B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F12B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F12B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F12B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F12B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F12B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F12B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F12B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F12B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F12B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F12B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F12B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F12B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F12B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F12B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F12B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F12B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F12B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F12B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F12B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F12B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F12B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F12B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F12B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F12B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F12B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F13R1 register  ******************/
#define CAN_F13B1_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F13B1_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F13B1_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F13B1_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F13B1_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F13B1_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F13B1_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F13B1_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F13B1_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F13B1_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F13B1_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F13B1_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F13B1_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F13B1_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F13B1_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F13B1_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F13B1_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F13B1_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F13B1_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F13B1_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F13B1_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F13B1_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F13B1_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F13B1_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F13B1_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F13B1_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F13B1_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F13B1_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F13B1_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F13B1_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F13B1_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F13B1_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F0R2 register  *******************/
#define CAN_F0B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F0B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F0B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F0B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F0B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F0B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F0B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F0B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F0B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F0B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F0B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F0B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F0B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F0B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F0B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F0B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F0B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F0B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F0B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F0B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F0B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F0B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F0B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F0B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F0B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F0B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F0B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F0B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F0B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F0B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F0B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F0B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F1R2 register  *******************/
#define CAN_F1B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F1B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F1B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F1B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F1B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F1B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F1B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F1B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F1B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F1B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F1B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F1B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F1B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F1B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F1B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F1B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F1B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F1B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F1B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F1B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F1B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F1B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F1B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F1B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F1B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F1B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F1B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F1B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F1B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F1B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F1B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F1B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F2R2 register  *******************/
#define CAN_F2B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F2B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F2B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F2B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F2B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F2B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F2B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F2B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F2B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F2B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F2B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F2B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F2B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F2B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F2B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F2B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F2B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F2B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F2B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F2B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F2B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F2B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F2B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F2B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F2B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F2B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F2B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F2B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F2B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F2B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F2B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F2B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F3R2 register  *******************/
#define CAN_F3B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F3B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F3B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F3B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F3B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F3B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F3B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F3B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F3B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F3B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F3B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F3B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F3B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F3B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F3B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F3B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F3B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F3B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F3B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F3B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F3B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F3B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F3B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F3B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F3B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F3B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F3B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F3B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F3B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F3B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F3B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F3B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F4R2 register  *******************/
#define CAN_F4B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F4B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F4B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F4B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F4B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F4B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F4B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F4B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F4B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F4B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F4B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F4B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F4B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F4B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F4B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F4B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F4B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F4B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F4B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F4B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F4B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F4B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F4B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F4B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F4B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F4B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F4B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F4B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F4B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F4B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F4B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F4B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F5R2 register  *******************/
#define CAN_F5B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F5B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F5B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F5B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F5B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F5B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F5B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F5B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F5B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F5B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F5B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F5B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F5B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F5B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F5B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F5B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F5B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F5B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F5B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F5B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F5B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F5B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F5B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F5B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F5B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F5B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F5B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F5B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F5B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F5B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F5B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F5B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F6R2 register  *******************/
#define CAN_F6B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F6B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F6B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F6B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F6B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F6B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F6B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F6B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F6B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F6B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F6B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F6B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F6B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F6B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F6B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F6B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F6B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F6B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F6B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F6B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F6B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F6B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F6B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F6B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F6B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F6B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F6B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F6B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F6B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F6B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F6B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F6B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F7R2 register  *******************/
#define CAN_F7B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F7B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F7B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F7B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F7B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F7B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F7B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F7B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F7B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F7B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F7B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F7B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F7B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F7B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F7B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F7B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F7B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F7B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F7B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F7B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F7B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F7B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F7B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F7B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F7B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F7B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F7B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F7B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F7B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F7B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F7B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F7B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F8R2 register  *******************/
#define CAN_F8B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F8B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F8B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F8B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F8B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F8B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F8B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F8B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F8B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F8B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F8B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F8B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F8B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F8B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F8B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F8B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F8B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F8B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F8B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F8B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F8B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F8B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F8B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F8B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F8B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F8B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F8B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F8B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F8B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F8B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F8B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F8B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F9R2 register  *******************/
#define CAN_F9B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F9B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F9B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F9B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F9B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F9B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F9B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F9B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F9B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F9B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F9B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F9B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F9B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F9B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F9B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F9B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F9B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F9B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F9B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F9B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F9B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F9B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F9B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F9B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F9B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F9B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F9B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F9B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F9B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F9B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F9B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F9B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F10R2 register  ******************/
#define CAN_F10B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F10B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F10B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F10B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F10B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F10B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F10B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F10B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F10B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F10B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F10B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F10B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F10B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F10B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F10B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F10B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F10B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F10B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F10B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F10B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F10B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F10B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F10B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F10B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F10B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F10B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F10B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F10B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F10B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F10B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F10B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F10B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F11R2 register  ******************/
#define CAN_F11B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F11B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F11B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F11B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F11B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F11B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F11B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F11B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F11B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F11B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F11B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F11B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F11B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F11B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F11B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F11B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F11B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F11B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F11B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F11B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F11B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F11B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F11B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F11B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F11B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F11B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F11B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F11B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F11B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F11B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F11B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F11B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F12R2 register  ******************/
#define CAN_F12B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F12B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F12B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F12B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F12B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F12B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F12B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F12B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F12B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F12B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F12B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F12B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F12B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F12B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F12B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F12B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F12B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F12B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F12B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F12B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F12B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F12B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F12B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F12B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F12B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F12B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F12B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F12B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F12B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F12B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F12B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F12B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/*******************  Bit definition for CAN_F13R2 register  ******************/
#define CAN_F13B2_FBC0  ((uint32_t)0x00000001) /*!< Filter bit 0 */
#define CAN_F13B2_FBC1  ((uint32_t)0x00000002) /*!< Filter bit 1 */
#define CAN_F13B2_FBC2  ((uint32_t)0x00000004) /*!< Filter bit 2 */
#define CAN_F13B2_FBC3  ((uint32_t)0x00000008) /*!< Filter bit 3 */
#define CAN_F13B2_FBC4  ((uint32_t)0x00000010) /*!< Filter bit 4 */
#define CAN_F13B2_FBC5  ((uint32_t)0x00000020) /*!< Filter bit 5 */
#define CAN_F13B2_FBC6  ((uint32_t)0x00000040) /*!< Filter bit 6 */
#define CAN_F13B2_FBC7  ((uint32_t)0x00000080) /*!< Filter bit 7 */
#define CAN_F13B2_FBC8  ((uint32_t)0x00000100) /*!< Filter bit 8 */
#define CAN_F13B2_FBC9  ((uint32_t)0x00000200) /*!< Filter bit 9 */
#define CAN_F13B2_FBC10 ((uint32_t)0x00000400) /*!< Filter bit 10 */
#define CAN_F13B2_FBC11 ((uint32_t)0x00000800) /*!< Filter bit 11 */
#define CAN_F13B2_FBC12 ((uint32_t)0x00001000) /*!< Filter bit 12 */
#define CAN_F13B2_FBC13 ((uint32_t)0x00002000) /*!< Filter bit 13 */
#define CAN_F13B2_FBC14 ((uint32_t)0x00004000) /*!< Filter bit 14 */
#define CAN_F13B2_FBC15 ((uint32_t)0x00008000) /*!< Filter bit 15 */
#define CAN_F13B2_FBC16 ((uint32_t)0x00010000) /*!< Filter bit 16 */
#define CAN_F13B2_FBC17 ((uint32_t)0x00020000) /*!< Filter bit 17 */
#define CAN_F13B2_FBC18 ((uint32_t)0x00040000) /*!< Filter bit 18 */
#define CAN_F13B2_FBC19 ((uint32_t)0x00080000) /*!< Filter bit 19 */
#define CAN_F13B2_FBC20 ((uint32_t)0x00100000) /*!< Filter bit 20 */
#define CAN_F13B2_FBC21 ((uint32_t)0x00200000) /*!< Filter bit 21 */
#define CAN_F13B2_FBC22 ((uint32_t)0x00400000) /*!< Filter bit 22 */
#define CAN_F13B2_FBC23 ((uint32_t)0x00800000) /*!< Filter bit 23 */
#define CAN_F13B2_FBC24 ((uint32_t)0x01000000) /*!< Filter bit 24 */
#define CAN_F13B2_FBC25 ((uint32_t)0x02000000) /*!< Filter bit 25 */
#define CAN_F13B2_FBC26 ((uint32_t)0x04000000) /*!< Filter bit 26 */
#define CAN_F13B2_FBC27 ((uint32_t)0x08000000) /*!< Filter bit 27 */
#define CAN_F13B2_FBC28 ((uint32_t)0x10000000) /*!< Filter bit 28 */
#define CAN_F13B2_FBC29 ((uint32_t)0x20000000) /*!< Filter bit 29 */
#define CAN_F13B2_FBC30 ((uint32_t)0x40000000) /*!< Filter bit 30 */
#define CAN_F13B2_FBC31 ((uint32_t)0x80000000) /*!< Filter bit 31 */

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface                         */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for SPI_CTRL1 register  ********************/
#define SPI_CTRL1_CLKPHA ((uint16_t)0x0001) /*!< Clock Phase */
#define SPI_CTRL1_CLKPOL ((uint16_t)0x0002) /*!< Clock Polarity */
#define SPI_CTRL1_MSEL   ((uint16_t)0x0004) /*!< Master Selection */

#define SPI_CTRL1_BR  ((uint16_t)0x0038) /*!< BR[2:0] bits (Baud Rate Control) */
#define SPI_CTRL1_BR0 ((uint16_t)0x0008) /*!< Bit 0 */
#define SPI_CTRL1_BR1 ((uint16_t)0x0010) /*!< Bit 1 */
#define SPI_CTRL1_BR2 ((uint16_t)0x0020) /*!< Bit 2 */

#define SPI_CTRL1_SPIEN     ((uint16_t)0x0040) /*!< SPI Enable */
#define SPI_CTRL1_LSBFF     ((uint16_t)0x0080) /*!< Frame Format */
#define SPI_CTRL1_SSEL      ((uint16_t)0x0100) /*!< Internal slave select */
#define SPI_CTRL1_SSMEN     ((uint16_t)0x0200) /*!< Software slave management */
#define SPI_CTRL1_RONLY     ((uint16_t)0x0400) /*!< Receive only */
#define SPI_CTRL1_DATFF     ((uint16_t)0x0800) /*!< Data Frame Format */
#define SPI_CTRL1_CRCNEXT   ((uint16_t)0x1000) /*!< Transmit CRC next */
#define SPI_CTRL1_CRCEN     ((uint16_t)0x2000) /*!< Hardware CRC calculation enable */
#define SPI_CTRL1_BIDIROEN  ((uint16_t)0x4000) /*!< Output enable in bidirectional mode */
#define SPI_CTRL1_BIDIRMODE ((uint16_t)0x8000) /*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CTRL2 register  ********************/
#define SPI_CTRL2_RDMAEN   ((uint8_t)0x01) /*!< Rx Buffer DMA Enable */
#define SPI_CTRL2_TDMAEN   ((uint8_t)0x02) /*!< Tx Buffer DMA Enable */
#define SPI_CTRL2_SSOEN    ((uint8_t)0x04) /*!< SS Output Enable */
#define SPI_CTRL2_ERRINTEN ((uint8_t)0x20) /*!< Error Interrupt Enable */
#define SPI_CTRL2_RNEINTEN ((uint8_t)0x40) /*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CTRL2_TEINTEN  ((uint8_t)0x80) /*!< Tx buffer Empty Interrupt Enable */

/********************  Bit definition for SPI_STS register  ********************/
#define SPI_STS_RNE    ((uint8_t)0x01) /*!< Receive buffer Not Empty */
#define SPI_STS_TE     ((uint8_t)0x02) /*!< Transmit buffer Empty */
#define SPI_STS_CHSIDE ((uint8_t)0x04) /*!< Channel side */
#define SPI_STS_UNDER  ((uint8_t)0x08) /*!< Underrun flag */
#define SPI_STS_CRCERR ((uint8_t)0x10) /*!< CRC Error flag */
#define SPI_STS_MODERR ((uint8_t)0x20) /*!< Mode fault */
#define SPI_STS_OVER   ((uint8_t)0x40) /*!< Overrun flag */
#define SPI_STS_BUSY   ((uint8_t)0x80) /*!< Busy flag */

/********************  Bit definition for SPI_DAT register  ********************/
#define SPI_DAT_DAT ((uint16_t)0xFFFF) /*!< Data Register */

/*******************  Bit definition for SPI_CRCPOLY register  ******************/
#define SPI_CRCPOLY_CRCPOLY ((uint16_t)0xFFFF) /*!< CRC polynomial register */

/******************  Bit definition for SPI_CRCRDAT register  ******************/
#define SPI_CRCRDAT_CRCRDAT ((uint16_t)0xFFFF) /*!< Rx CRC Register */

/******************  Bit definition for SPI_CRCTDAT register  ******************/
#define SPI_CRCTDAT_CRCTDAT ((uint16_t)0xFFFF) /*!< Tx CRC Register */

/******************  Bit definition for SPI_I2SCFG register  *****************/
#define SPI_I2SCFG_CHBITS ((uint16_t)0x0001) /*!< Channel length (number of bits per audio channel) */

#define SPI_I2SCFG_TDATLEN  ((uint16_t)0x0006) /*!< TDATLEN[1:0] bits (Data length to be transferred) */
#define SPI_I2SCFG_TDATLEN0 ((uint16_t)0x0002) /*!< Bit 0 */
#define SPI_I2SCFG_TDATLEN1 ((uint16_t)0x0004) /*!< Bit 1 */

#define SPI_I2SCFG_CLKPOL ((uint16_t)0x0008) /*!< steady state clock polarity */

#define SPI_I2SCFG_STDSEL  ((uint16_t)0x0030) /*!< STDSEL[1:0] bits (I2S standard selection) */
#define SPI_I2SCFG_STDSEL0 ((uint16_t)0x0010) /*!< Bit 0 */
#define SPI_I2SCFG_STDSEL1 ((uint16_t)0x0020) /*!< Bit 1 */

#define SPI_I2SCFG_PCMFSYNC ((uint16_t)0x0080) /*!< PCM frame synchronization */

#define SPI_I2SCFG_MODCFG  ((uint16_t)0x0300) /*!< MODCFG[1:0] bits (I2S configuration mode) */
#define SPI_I2SCFG_MODCFG0 ((uint16_t)0x0100) /*!< Bit 0 */
#define SPI_I2SCFG_MODCFG1 ((uint16_t)0x0200) /*!< Bit 1 */

#define SPI_I2SCFG_I2SEN  ((uint16_t)0x0400) /*!< I2S Enable */
#define SPI_I2SCFG_MODSEL ((uint16_t)0x0800) /*!< I2S mode selection */

/******************  Bit definition for SPI_I2SPREDIV register  *******************/
#define SPI_I2SPREDIV_LDIV     ((uint16_t)0x00FF) /*!< I2S Linear prescaler */
#define SPI_I2SPREDIV_ODD_EVEN ((uint16_t)0x0100) /*!< Odd factor for the prescaler */
#define SPI_I2SPREDIV_MCLKOEN  ((uint16_t)0x0200) /*!< Master Clock Output Enable */

/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for I2C_CTRL1 register  ********************/
#define I2C_CTRL1_EN       ((uint16_t)0x0001) /*!< Peripheral Enable */
#define I2C_CTRL1_SMBMODE  ((uint16_t)0x0002) /*!< SMBus Mode */
#define I2C_CTRL1_SMBTYPE  ((uint16_t)0x0008) /*!< SMBus Type */
#define I2C_CTRL1_ARPEN    ((uint16_t)0x0010) /*!< ARP Enable */
#define I2C_CTRL1_PECEN    ((uint16_t)0x0020) /*!< PEC Enable */
#define I2C_CTRL1_GCEN     ((uint16_t)0x0040) /*!< General Call Enable */
#define I2C_CTRL1_NOEXTEND ((uint16_t)0x0080) /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CTRL1_STARTGEN ((uint16_t)0x0100) /*!< Start Generation */
#define I2C_CTRL1_STOPGEN  ((uint16_t)0x0200) /*!< Stop Generation */
#define I2C_CTRL1_ACKEN    ((uint16_t)0x0400) /*!< Acknowledge Enable */
#define I2C_CTRL1_ACKPOS   ((uint16_t)0x0800) /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CTRL1_PEC      ((uint16_t)0x1000) /*!< Packet Error Checking */
#define I2C_CTRL1_SMBALERT ((uint16_t)0x2000) /*!< SMBus Alert */
#define I2C_CTRL1_SWRESET  ((uint16_t)0x8000) /*!< Software Reset */

/*******************  Bit definition for I2C_CTRL2 register  ********************/
#define I2C_CTRL2_CLKFREQ   ((uint16_t)0x003F) /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CTRL2_CLKFREQ_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define I2C_CTRL2_CLKFREQ_1 ((uint16_t)0x0002) /*!< Bit 1 */
#define I2C_CTRL2_CLKFREQ_2 ((uint16_t)0x0004) /*!< Bit 2 */
#define I2C_CTRL2_CLKFREQ_3 ((uint16_t)0x0008) /*!< Bit 3 */
#define I2C_CTRL2_CLKFREQ_4 ((uint16_t)0x0010) /*!< Bit 4 */
#define I2C_CTRL2_CLKFREQ_5 ((uint16_t)0x0020) /*!< Bit 5 */

#define I2C_CTRL2_ERRINTEN ((uint16_t)0x0100) /*!< Error Interrupt Enable */
#define I2C_CTRL2_EVTINTEN ((uint16_t)0x0200) /*!< Event Interrupt Enable */
#define I2C_CTRL2_BUFINTEN ((uint16_t)0x0400) /*!< Buffer Interrupt Enable */
#define I2C_CTRL2_DMAEN    ((uint16_t)0x0800) /*!< DMA Requests Enable */
#define I2C_CTRL2_DMALAST  ((uint16_t)0x1000) /*!< DMA Last Transfer */

/*******************  Bit definition for I2C_OADDR1 register  *******************/
#define I2C_OADDR1_ADDR1_7 ((uint16_t)0x00FE) /*!< Interface Address */
#define I2C_OADDR1_ADDR8_9 ((uint16_t)0x0300) /*!< Interface Address */

#define I2C_OADDR1_ADDR0 ((uint16_t)0x0001) /*!< Bit 0 */
#define I2C_OADDR1_ADDR1 ((uint16_t)0x0002) /*!< Bit 1 */
#define I2C_OADDR1_ADDR2 ((uint16_t)0x0004) /*!< Bit 2 */
#define I2C_OADDR1_ADDR3 ((uint16_t)0x0008) /*!< Bit 3 */
#define I2C_OADDR1_ADDR4 ((uint16_t)0x0010) /*!< Bit 4 */
#define I2C_OADDR1_ADDR5 ((uint16_t)0x0020) /*!< Bit 5 */
#define I2C_OADDR1_ADDR6 ((uint16_t)0x0040) /*!< Bit 6 */
#define I2C_OADDR1_ADDR7 ((uint16_t)0x0080) /*!< Bit 7 */
#define I2C_OADDR1_ADDR8 ((uint16_t)0x0100) /*!< Bit 8 */
#define I2C_OADDR1_ADDR9 ((uint16_t)0x0200) /*!< Bit 9 */

#define I2C_OADDR1_ADDRMODE ((uint16_t)0x8000) /*!< Addressing Mode (Slave mode) */

/*******************  Bit definition for I2C_OADDR2 register  *******************/
#define I2C_OADDR2_DUALEN ((uint8_t)0x01) /*!< Dual addressing mode enable */
#define I2C_OADDR2_ADDR2  ((uint8_t)0xFE) /*!< Interface address */

/********************  Bit definition for I2C_DAT register  ********************/
#define I2C_DAT_DATA ((uint8_t)0xFF) /*!< 8-bit Data Register */

/*******************  Bit definition for I2C_STS1 register  ********************/
#define I2C_STS1_STARTBF  ((uint16_t)0x0001) /*!< Start Bit (Master mode) */
#define I2C_STS1_ADDRF    ((uint16_t)0x0002) /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_STS1_BSF      ((uint16_t)0x0004) /*!< Byte Transfer Finished */
#define I2C_STS1_ADDR10F  ((uint16_t)0x0008) /*!< 10-bit header sent (Master mode) */
#define I2C_STS1_STOPF    ((uint16_t)0x0010) /*!< Stop detection (Slave mode) */
#define I2C_STS1_RXDATNE  ((uint16_t)0x0040) /*!< Data Register not Empty (receivers) */
#define I2C_STS1_TXDATE   ((uint16_t)0x0080) /*!< Data Register Empty (transmitters) */
#define I2C_STS1_BUSERR   ((uint16_t)0x0100) /*!< Bus Error */
#define I2C_STS1_ARLOST   ((uint16_t)0x0200) /*!< Arbitration Lost (master mode) */
#define I2C_STS1_ACKFAIL  ((uint16_t)0x0400) /*!< Acknowledge Failure */
#define I2C_STS1_OVERRUN  ((uint16_t)0x0800) /*!< Overrun/Underrun */
#define I2C_STS1_PECERR   ((uint16_t)0x1000) /*!< PEC Error in reception */
#define I2C_STS1_TIMOUT   ((uint16_t)0x4000) /*!< Timeout or Tlow Error */
#define I2C_STS1_SMBALERT ((uint16_t)0x8000) /*!< SMBus Alert */

/*******************  Bit definition for I2C_STS2 register  ********************/
#define I2C_STS2_MSMODE    ((uint16_t)0x0001) /*!< Master/Slave */
#define I2C_STS2_BUSY      ((uint16_t)0x0002) /*!< Bus Busy */
#define I2C_STS2_TRF       ((uint16_t)0x0004) /*!< Transmitter/Receiver */
#define I2C_STS2_GCALLADDR ((uint16_t)0x0010) /*!< General Call Address (Slave mode) */
#define I2C_STS2_SMBDADDR  ((uint16_t)0x0020) /*!< SMBus Device Default Address (Slave mode) */
#define I2C_STS2_SMBHADDR  ((uint16_t)0x0040) /*!< SMBus Host Header (Slave mode) */
#define I2C_STS2_DUALFLAG  ((uint16_t)0x0080) /*!< Dual Flag (Slave mode) */
#define I2C_STS2_PECVAL    ((uint16_t)0xFF00) /*!< Packet Error Checking Register */

/*******************  Bit definition for I2C_CLKCTRL register  ********************/
#define I2C_CLKCTRL_CLKCTRL ((uint16_t)0x0FFF) /*!< Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CLKCTRL_DUTY    ((uint16_t)0x4000) /*!< Fast Mode Duty Cycle */
#define I2C_CLKCTRL_FSMODE  ((uint16_t)0x8000) /*!< I2C Master Mode Selection */

/******************  Bit definition for I2C_TRISE register  *******************/
#define I2C_TMRISE_TMRISE ((uint8_t)0x3F) /*!< Maximum Rise Time in Fast/Standard mode (Master mode) */

/******************************************************************************/
/*                                                                            */
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for USART_STS register  *******************/
#define USART_STS_PEF    ((uint16_t)0x0001) /*!< Parity Error */
#define USART_STS_FEF    ((uint16_t)0x0002) /*!< Framing Error */
#define USART_STS_NEF    ((uint16_t)0x0004) /*!< Noise Error Flag */
#define USART_STS_OREF   ((uint16_t)0x0008) /*!< OverRun Error */
#define USART_STS_IDLEF  ((uint16_t)0x0010) /*!< IDLE line detected */
#define USART_STS_RXDNE  ((uint16_t)0x0020) /*!< Read Data Register Not Empty */
#define USART_STS_TXC    ((uint16_t)0x0040) /*!< Transmission Complete */
#define USART_STS_TXDE   ((uint16_t)0x0080) /*!< Transmit Data Register Empty */
#define USART_STS_LINBDF ((uint16_t)0x0100) /*!< LIN Break Detection Flag */
#define USART_STS_CTSF   ((uint16_t)0x0200) /*!< CTS Flag */

/*******************  Bit definition for USART_DAT register  *******************/
#define USART_DAT_DATV ((uint16_t)0x01FF) /*!< Data value */

/******************  Bit definition for USART_BRCF register  *******************/
#define USART_BRCF_DIV_Decimal ((uint16_t)0x000F) /*!< Fraction of USARTDIV */
#define USART_BRCF_DIV_Integer ((uint16_t)0xFFF0) /*!< Mantissa of USARTDIV */

/******************  Bit definition for USART_CTRL1 register  *******************/
#define USART_CTRL1_SDBRK    ((uint16_t)0x0001) /*!< Send Break */
#define USART_CTRL1_RCVWU    ((uint16_t)0x0002) /*!< Receiver wakeup */
#define USART_CTRL1_RXEN     ((uint16_t)0x0004) /*!< Receiver Enable */
#define USART_CTRL1_TXEN     ((uint16_t)0x0008) /*!< Transmitter Enable */
#define USART_CTRL1_IDLEIEN  ((uint16_t)0x0010) /*!< IDLE Interrupt Enable */
#define USART_CTRL1_RXDNEIEN ((uint16_t)0x0020) /*!< RXNE Interrupt Enable */
#define USART_CTRL1_TXCIEN   ((uint16_t)0x0040) /*!< Transmission Complete Interrupt Enable */
#define USART_CTRL1_TXDEIEN  ((uint16_t)0x0080) /*!< PE Interrupt Enable */
#define USART_CTRL1_PEIEN    ((uint16_t)0x0100) /*!< PE Interrupt Enable */
#define USART_CTRL1_PSEL     ((uint16_t)0x0200) /*!< Parity Selection */
#define USART_CTRL1_PCEN     ((uint16_t)0x0400) /*!< Parity Control Enable */
#define USART_CTRL1_WUM      ((uint16_t)0x0800) /*!< Wakeup method */
#define USART_CTRL1_WL       ((uint16_t)0x1000) /*!< Word length */
#define USART_CTRL1_UEN      ((uint16_t)0x2000) /*!< USART Enable */

/******************  Bit definition for USART_CTRL2 register  *******************/
#define USART_CTRL2_ADDR        ((uint16_t)0x000F) /*!< Address of the USART node */
#define USART_CTRL2_LINBDL      ((uint16_t)0x0020) /*!< LIN Break Detection Length */
#define USART_CTRL2_LINBDIEN    ((uint16_t)0x0040) /*!< LIN Break Detection Interrupt Enable */
#define USART_CTRL2_LBCLK       ((uint16_t)0x0100) /*!< Last Bit Clock pulse */
#define USART_CTRL2_CLKPHA      ((uint16_t)0x0200) /*!< Clock Phase */
#define USART_CTRL2_CLKPOL      ((uint16_t)0x0400) /*!< Clock Polarity */
#define USART_CTRL2_CLKEN       ((uint16_t)0x0800) /*!< Clock Enable */

#define USART_CTRL2_STPB   ((uint16_t)0x3000) /*!< STOP[1:0] bits (STOP bits) */
#define USART_CTRL2_STPB_0 ((uint16_t)0x1000) /*!< Bit 0 */
#define USART_CTRL2_STPB_1 ((uint16_t)0x2000) /*!< Bit 1 */

#define USART_CTRL2_LINMEN ((uint16_t)0x4000) /*!< LIN mode enable */

/******************  Bit definition for USART_CTRL3 register  *******************/
#define USART_CTRL3_ERRIEN  ((uint16_t)0x0001) /*!< Error Interrupt Enable */
#define USART_CTRL3_IRDAMEN ((uint16_t)0x0002) /*!< IrDA mode Enable */
#define USART_CTRL3_IRDALP  ((uint16_t)0x0004) /*!< IrDA Low-Power */
#define USART_CTRL3_HDMEN   ((uint16_t)0x0008) /*!< Half-Duplex Selection */
#define USART_CTRL3_SCNACK  ((uint16_t)0x0010) /*!< Smartcard NACK enable */
#define USART_CTRL3_SCMEN   ((uint16_t)0x0020) /*!< Smartcard mode enable */
#define USART_CTRL3_DMARXEN ((uint16_t)0x0040) /*!< DMA Enable Receiver */
#define USART_CTRL3_DMATXEN ((uint16_t)0x0080) /*!< DMA Enable Transmitter */
#define USART_CTRL3_RTSEN   ((uint16_t)0x0100) /*!< RTS Enable */
#define USART_CTRL3_CTSEN   ((uint16_t)0x0200) /*!< CTS Enable */
#define USART_CTRL3_CTSIEN  ((uint16_t)0x0400) /*!< CTS Interrupt Enable */

/******************  Bit definition for USART_GTP register  ******************/
#define USART_GTP_PSCV   ((uint16_t)0x00FF) /*!< PSC[7:0] bits (Prescaler value) */
#define USART_GTP_PSCV_0 ((uint16_t)0x0001) /*!< Bit 0 */
#define USART_GTP_PSCV_1 ((uint16_t)0x0002) /*!< Bit 1 */
#define USART_GTP_PSCV_2 ((uint16_t)0x0004) /*!< Bit 2 */
#define USART_GTP_PSCV_3 ((uint16_t)0x0008) /*!< Bit 3 */
#define USART_GTP_PSCV_4 ((uint16_t)0x0010) /*!< Bit 4 */
#define USART_GTP_PSCV_5 ((uint16_t)0x0020) /*!< Bit 5 */
#define USART_GTP_PSCV_6 ((uint16_t)0x0040) /*!< Bit 6 */
#define USART_GTP_PSCV_7 ((uint16_t)0x0080) /*!< Bit 7 */

#define USART_GTP_GTV ((uint16_t)0xFF00) /*!< Guard time value */

/******************************************************************************/
/*                                                                            */
/*          Low-power Universal Asynchronous Receiver Transmitter             */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for LPUART_STS register  ******************/
#define LPUART_STS_PEF      ((uint16_t)0x0001) /*!< Parity Check Error Flag */
#define LPUART_STS_TXC      ((uint16_t)0x0002) /*!< TX Complete Flag */
#define LPUART_STS_FIFO_OV  ((uint16_t)0x0004) /*!< FIFO Overflow Flag */
#define LPUART_STS_FIFO_FU  ((uint16_t)0x0008) /*!< FIFO Full Flag */
#define LPUART_STS_FIFO_HF  ((uint16_t)0x0010) /*!< FIFO Half Full Flag */
#define LPUART_STS_FIFO_NE  ((uint16_t)0x0020) /*!< FIFO Non-Empty Flag */
#define LPUART_STS_CTS      ((uint16_t)0x0040) /*!< Clear to Send (Hardware Flow Control) Flag */
#define LPUART_STS_WUF      ((uint16_t)0x0080) /*!< Wakeup from Stop mode Flag */
#define LPUART_STS_NF       ((uint16_t)0x0100) /*!< Noise Detected Flag */

/******************  Bit definition for LPUART_INTEN register  ******************/
#define LPUART_INTEN_PEIE       ((uint8_t)0x01) /*!< Parity Check Error Interrupt Enable */
#define LPUART_INTEN_TXCIE      ((uint8_t)0x02) /*!< TX Complete Interrupt Enable */
#define LPUART_INTEN_FIFO_OVIE  ((uint8_t)0x04) /*!< FIFO Overflow Interrupt Enable */
#define LPUART_INTEN_FIFO_FUIE  ((uint8_t)0x08) /*!< FIFO Full Interrupt Enable*/
#define LPUART_INTEN_FIFO_HFIE  ((uint8_t)0x10) /*!< FIFO Half Full Interrupt Enable */
#define LPUART_INTEN_FIFO_NEIE  ((uint8_t)0x20) /*!< FIFO Non-Empty Interrupt Enable */
#define LPUART_INTEN_WUFIE      ((uint8_t)0x40) /*!< Wakeup Interrupt Enable */

/******************  Bit definition for LPUART_CTRL register  ******************/
#define LPUART_CTRL_PSEL      ((uint16_t)0x0001) /*!< Odd Parity Bit Enable */
#define LPUART_CTRL_TXEN      ((uint16_t)0x0002) /*!< TX Enable */
#define LPUART_CTRL_FLUSH     ((uint16_t)0x0004) /*!< Flush Receiver FIFO Enable */
#define LPUART_CTRL_PCDIS     ((uint16_t)0x0008) /*!< Parity Control Disable */
#define LPUART_CTRL_LOOPBACK  ((uint16_t)0x0010) /*!< Loop Back Self-Test */
#define LPUART_CTRL_DMA_TXEN  ((uint16_t)0x0020) /*!< DMA TX Request Enable */
#define LPUART_CTRL_DMA_RXEN  ((uint16_t)0x0040) /*!< DMA RX Request Enable */
#define LPUART_CTRL_WUSTP     ((uint16_t)0x0080) /*!< LPUART Wakeup Enable in Stop mode */
#define LPUART_CTRL_RTS_THSEL ((uint16_t)0x0300) /*!< RTS Threshold Selection */
#define LPUART_CTRL_CTSEN     ((uint16_t)0x0400) /*!< Hardware Flow Control TX Enable */
#define LPUART_CTRL_RTSEN     ((uint16_t)0x0800) /*!< Hardware Flow Control RX Enable */
#define LPUART_CTRL_WUSEL     ((uint16_t)0x3000) /*!< Wakeup Event Selection */
#define LPUART_CTRL_SMPCNT    ((uint16_t)0x4000) /*!< Specify the Sampling Method */

/******************  Bit definition for LPUART_BRCFG1 register  ******************/
#define LPUART_BRCFG1_INTEGER  ((uint16_t)0xFFFF) /*!< Baud Rate Parameter Configeration Register1: Fraction */

/******************  Bit definition for LPUART_DAT register  ******************/
#define LPUART_DAT_DAT  ((uint8_t)0xFF) /*!< Data Register */

/******************  Bit definition for LPUART_BRCFG2 register  ******************/
#define LPUART_BRCFG2_DECIMAL  ((uint8_t)0xFF) /*!< Baud Rate Parameter Configeration Register2: Mantissa */

/******************  Bit definition for LPUART_WUDAT register  ******************/
#define LPUART_WUDAT_WUDAT  ((uint32_t)0xFFFFFFFF) /*!< Data Register */

/******************************************************************************/
/*                                                                            */
/*                                 Debug MCU                                  */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for DBG_ID register  *****************/
#define DBG_ID_DEV ((uint32_t)0x00000FFF) /*!< Device Identifier */

#define DBG_ID_REV    ((uint32_t)0xFFFF0000) /*!< REV_ID[15:0] bits (Revision Identifier) */
#define DBG_ID_REV_0  ((uint32_t)0x00010000) /*!< Bit 0 */
#define DBG_ID_REV_1  ((uint32_t)0x00020000) /*!< Bit 1 */
#define DBG_ID_REV_2  ((uint32_t)0x00040000) /*!< Bit 2 */
#define DBG_ID_REV_3  ((uint32_t)0x00080000) /*!< Bit 3 */
#define DBG_ID_REV_4  ((uint32_t)0x00100000) /*!< Bit 4 */
#define DBG_ID_REV_5  ((uint32_t)0x00200000) /*!< Bit 5 */
#define DBG_ID_REV_6  ((uint32_t)0x00400000) /*!< Bit 6 */
#define DBG_ID_REV_7  ((uint32_t)0x00800000) /*!< Bit 7 */
#define DBG_ID_REV_8  ((uint32_t)0x01000000) /*!< Bit 8 */
#define DBG_ID_REV_9  ((uint32_t)0x02000000) /*!< Bit 9 */
#define DBG_ID_REV_10 ((uint32_t)0x04000000) /*!< Bit 10 */
#define DBG_ID_REV_11 ((uint32_t)0x08000000) /*!< Bit 11 */
#define DBG_ID_REV_12 ((uint32_t)0x10000000) /*!< Bit 12 */
#define DBG_ID_REV_13 ((uint32_t)0x20000000) /*!< Bit 13 */
#define DBG_ID_REV_14 ((uint32_t)0x40000000) /*!< Bit 14 */
#define DBG_ID_REV_15 ((uint32_t)0x80000000) /*!< Bit 15 */

/******************  Bit definition for DBG_CTRL register  *******************/
#define DBG_CTRL_SLEEP  ((uint32_t)0x00000001) /*!< Debug Sleep Mode */
#define DBG_CTRL_STOP   ((uint32_t)0x00000002) /*!< Debug Stop Mode */
#define DBG_CTRL_STDBY  ((uint32_t)0x00000004) /*!< Debug Standby mode */

#define DBG_CTRL_IWDG_STOP    ((uint32_t)0x00000100) /*!< Debug Independent Watchdog stopped when Core is halted */
#define DBG_CTRL_WWDG_STOP    ((uint32_t)0x00000200) /*!< Debug Window Watchdog stopped when Core is halted */
#define DBG_CTRL_TIM1_STOP    ((uint32_t)0x00000400) /*!< TIM1 counter stopped when core is halted */
#define DBG_CTRL_TIM2_STOP    ((uint32_t)0x00000800) /*!< TIM2 counter stopped when core is halted */
#define DBG_CTRL_TIM3_STOP    ((uint32_t)0x00001000) /*!< TIM3 counter stopped when core is halted */
#define DBG_CTRL_TIM4_STOP    ((uint32_t)0x00002000) /*!< TIM4 counter stopped when core is halted */
#define DBG_CTRL_CAN_STOP     ((uint32_t)0x00004000) /*!< Debug CAN stopped when Core is halted */
#define DBG_CTRL_I2C1SMBUS_TO ((uint32_t)0x00008000) /*!< SMBUS I2C1 timeout mode stopped when Core is halted */
#define DBG_CTRL_I2C2SMBUS_TO ((uint32_t)0x00010000) /*!< SMBUS I2C2 timeout mode stopped when Core is halted */
#define DBG_CTRL_TIM8_STOP    ((uint32_t)0x00020000) /*!< TIM8 counter stopped when core is halted */
#define DBG_CTRL_TIM5_STOP    ((uint32_t)0x00040000) /*!< TIM5 counter stopped when core is halted */
#define DBG_CTRL_TIM6_STOP    ((uint32_t)0x00080000) /*!< TIM6 counter stopped when core is halted */
#define DBG_CTRL_TIM7_STOP    ((uint32_t)0x00100000) /*!< TIM7 counter stopped when core is halted */
#define DBG_CTRL_TIM9_STOP    ((uint32_t)0x00200000) /*!< TIM9 counter stopped when core is halted*/
/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FLASH_AC register  ******************/
#define FLASH_AC_LATENCY   ((uint32_t)0x00000003) /*!< LATENCY[2:0] bits (Latency) */
#define FLASH_AC_LATENCY_0 ((uint32_t)0x00000000) /*!< Bit 0 = 0 */
#define FLASH_AC_LATENCY_1 ((uint32_t)0x00000001) /*!< Bit 0 = 1 */
#define FLASH_AC_LATENCY_2 ((uint32_t)0x00000002) /*!< Bit 0 = 0; Bit 1 = 1 */
#define FLASH_AC_LATENCY_3 ((uint32_t)0x00000003) /*!< Bit 0 = 1; Bit 1 = 1 */

#define FLASH_AC_PRFTBFEN  ((uint32_t)0x00000010) /*!< Prefetch Buffer Enable */
#define FLASH_AC_PRFTBFSTS ((uint32_t)0x00000020) /*!< Prefetch Buffer Status */
#define FLASH_AC_ICAHRST   ((uint32_t)0x00000040) /*!< Icache Reset */
#define FLASH_AC_ICAHEN    ((uint32_t)0x00000080) /*!< Icache Enable */
#define FLASH_AC_LVMF      ((uint32_t)0x00000100) /*!< Flash low power work mode status */
#define FLASH_AC_LVMEN     ((uint32_t)0x00000200) /*!< Flash low power work mode Enable */
#define FLASH_AC_SLMF      ((uint32_t)0x00000400) /*!< Flash sleep mode status */
#define FLASH_AC_SLMEN     ((uint32_t)0x00000800) /*!< Flash sleep mode Enable */

/******************  Bit definition for FLASH_KEY register  ******************/
#define FLASH_KEY_FKEY ((uint32_t)0xFFFFFFFF) /*!< FLASH Key */

/*****************  Bit definition for FLASH_OPTKEY register  ****************/
#define FLASH_OPTKEY_OPTKEY ((uint32_t)0xFFFFFFFF) /*!< Option Byte Key */

/******************  Bit definition for FLASH_STS register  *******************/
#define FLASH_STS_BUSY     ((uint8_t)0x01) /*!< Busy */
#define FLASH_STS_PGERR    ((uint8_t)0x04) /*!< Programming Error */
#define FLASH_STS_PVERR    ((uint8_t)0x08) /*!< Programming Verify ERROR after program */
#define FLASH_STS_WRPERR   ((uint8_t)0x10) /*!< Write Protection Error */
#define FLASH_STS_EOP      ((uint8_t)0x20) /*!< End of operation */
#define FLASH_STS_EVERR    ((uint8_t)0x40) /*!< Erase Verify ERROR after page erase */

/*******************  Bit definition for FLASH_CTRL register  *******************/
#define FLASH_CTRL_PG        ((uint16_t)0x0001) /*!< Programming */
#define FLASH_CTRL_PER       ((uint16_t)0x0002) /*!< Page Erase */
#define FLASH_CTRL_MER       ((uint16_t)0x0004) /*!< Mass Erase */
#define FLASH_CTRL_OPTPG     ((uint16_t)0x0010) /*!< Option Byte Programming */
#define FLASH_CTRL_OPTER     ((uint16_t)0x0020) /*!< Option Byte Erase */
#define FLASH_CTRL_START     ((uint16_t)0x0040) /*!< Start */
#define FLASH_CTRL_LOCK      ((uint16_t)0x0080) /*!< Lock */
#define FLASH_CTRL_SMPSEL    ((uint16_t)0x0100) /*!< Flash Program Option Select */
#define FLASH_CTRL_OPTWE     ((uint16_t)0x0200) /*!< Option Bytes Write Enable */
#define FLASH_CTRL_ERRITE    ((uint16_t)0x0400) /*!< Error Interrupt Enable */
#define FLASH_CTRL_FERRITE   ((uint16_t)0x0800) /*!< EVERR PVERR Error Interrupt Enable */
#define FLASH_CTRL_EOPITE    ((uint16_t)0x1000) /*!< End of operation Interrupt Enable */

/*******************  Bit definition for FLASH_ADD register  *******************/
#define FLASH_ADD_FADD ((uint32_t)0xFFFFFFFF) /*!< Flash Address */

/******************  Bit definition for FLASH_OB2 register  *******************/
#define FLASH_OB2_BOR_LEV  ((uint32_t)0x00000700) /*!< BOR_LEV[2:0] */
#define FLASH_OB2_nBOOT1   ((uint32_t)0x00800000) /*!< nBOOT1 */
#define FLASH_OB2_nSWBOOT0 ((uint32_t)0x04000000) /*!< nSWBOOT0 */
#define FLASH_OB2_nBOOT0   ((uint32_t)0x08000000) /*!< nBOOT1 */

/******************  Bit definition for FLASH_OB register  *******************/
#define FLASH_OB_OBERR   ((uint16_t)0x0001) /*!< Option Byte Error */
#define FLASH_OB_RDPRT1 ((uint16_t)0x0002) /*!< Read Protection */

#define FLASH_OB_USER       ((uint16_t)0x03FC) /*!< User Option Bytes */
#define FLASH_OB_WDG_SW     ((uint16_t)0x0004) /*!< WDG_SW */
#define FLASH_OB_NRST_STOP2 ((uint16_t)0x0008) /*!< nRST_STOP2 */
#define FLASH_OB_NRST_STDBY ((uint16_t)0x0010) /*!< nRST_STDBY */
#define FLASH_OB_NRST_PD    ((uint16_t)0x0020) /*!< nRST_PD */

#define FLASH_OB_DATA0_MSK ((uint32_t)0x0003FC00) /*!< Data0 Mask */
#define FLASH_OB_DATA1_MSK ((uint32_t)0x03FC0000) /*!< Data1 Mask */
#define FLASH_OB_RDPRT2    ((uint32_t)0x80000000) /*!< Read Protection Level 2 */

/******************  Bit definition for FLASH_WRP register  ******************/
#define FLASH_WRP_WRPT ((uint32_t)0xFFFFFFFF) /*!< Write Protect */

/******************  Bit definition for FLASH_CAHR register  ******************/
#define FLASH_CAHR_LOCKSTRT_MSK ((uint32_t)0x000F) /*!< LOCKSTRT Mask */
#define FLASH_CAHR_LOCKSTOP_MSK ((uint32_t)0x00F0) /*!< LOCKSTOP Mask */
/*----------------------------------------------------------------------------*/

/******************  Bit definition for OptionByte USER  ******************/
#define FLASH_RDP_RDP1  ((uint32_t)0x000000FF) /*!< Read protection option byte */
#define FLASH_RDP_NRDP1 ((uint32_t)0x0000FF00) /*!< Read protection complemented option byte */

/******************  Bit definition for OptionByte USER  ******************/
#define FLASH_USER_USER  ((uint32_t)0x00FF0000) /*!< User option byte */
#define FLASH_USER_NUSER ((uint32_t)0xFF000000) /*!< User complemented option byte */

/******************  Bit definition for OptionByte Data0  *****************/
#define FLASH_Data0_Data0  ((uint32_t)0x000000FF) /*!< User data storage option byte */
#define FLASH_Data0_NData0 ((uint32_t)0x0000FF00) /*!< User data storage complemented option byte */

/******************  Bit definition for OptionByte Data1  *****************/
#define FLASH_Data1_Data1  ((uint32_t)0x00FF0000) /*!< User data storage option byte */
#define FLASH_Data1_NData1 ((uint32_t)0xFF000000) /*!< User data storage complemented option byte */

/******************  Bit definition for OptionByte WRP0  ******************/
#define FLASH_WRP0_WRP0  ((uint32_t)0x000000FF) /*!< Flash memory write protection option bytes */
#define FLASH_WRP0_NWRP0 ((uint32_t)0x0000FF00) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OptionByte WRP1  ******************/
#define FLASH_WRP1_WRP1  ((uint32_t)0x00FF0000) /*!< Flash memory write protection option bytes */
#define FLASH_WRP1_NWRP1 ((uint32_t)0xFF000000) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OptionByte WRP2  ******************/
#define FLASH_WRP2_WRP2  ((uint32_t)0x000000FF) /*!< Flash memory write protection option bytes */
#define FLASH_WRP2_NWRP2 ((uint32_t)0x0000FF00) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OptionByte WRP3  ******************/
#define FLASH_WRP3_WRP3  ((uint32_t)0x00FF0000) /*!< Flash memory write protection option bytes */
#define FLASH_WRP3_NWRP3 ((uint32_t)0xFF000000) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OptionByte RDP2  *******************/
#define FLASH_RDP_RDP2  ((uint32_t)0x000000FF) /*!< Read protection level 2 option byte */
#define FLASH_RDP_NRDP2 ((uint32_t)0x0000FF00) /*!< Read protection level 2 complemented option byte */

/******************  Bit definition for OptionByte USER2  ******************/
#define FLASH_USER_USER2  ((uint32_t)0x00FF0000) /*!< User option byte */
#define FLASH_USER_NUSER2 ((uint32_t)0xFF000000) /*!< User complemented option byte */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_PMODE register  *******************/


#define GPIO_PMODE0_Pos            (0)
#define GPIO_PMODE0_Msk            (0x3 << GPIO_PMODE0_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE0                GPIO_PMODE0_Msk
#define GPIO_PMODE0_0              (0x0 << GPIO_PMODE0_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE0_1              (0x1 << GPIO_PMODE0_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE0_2              (0x2 << GPIO_PMODE0_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE0_3              (0x3 << GPIO_PMODE0_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE1_Pos            (2)
#define GPIO_PMODE1_Msk            (0x3 << GPIO_PMODE1_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE1                GPIO_PMODE1_Msk
#define GPIO_PMODE1_0              (0x0 << GPIO_PMODE1_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE1_1              (0x1 << GPIO_PMODE1_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE1_2              (0x2 << GPIO_PMODE1_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE1_3              (0x3 << GPIO_PMODE1_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE2_Pos            (4)
#define GPIO_PMODE2_Msk            (0x3 << GPIO_PMODE2_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE2                GPIO_PMODE2_Msk
#define GPIO_PMODE2_0              (0x0 << GPIO_PMODE2_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE2_1              (0x1 << GPIO_PMODE2_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE2_2              (0x2 << GPIO_PMODE2_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE2_3              (0x3 << GPIO_PMODE2_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE3_Pos            (6)
#define GPIO_PMODE3_Msk            (0x3 << GPIO_PMODE3_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE3                GPIO_PMODE3_Msk
#define GPIO_PMODE3_0              (0x0 << GPIO_PMODE3_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE3_1              (0x1 << GPIO_PMODE3_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE3_2              (0x2 << GPIO_PMODE3_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE3_3              (0x3 << GPIO_PMODE3_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE4_Pos            (8)
#define GPIO_PMODE4_Msk            (0x3 << GPIO_PMODE4_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE4                GPIO_PMODE4_Msk
#define GPIO_PMODE4_0              (0x0 << GPIO_PMODE4_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE4_1              (0x1 << GPIO_PMODE4_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE4_2              (0x2 << GPIO_PMODE4_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE4_3              (0x3 << GPIO_PMODE4_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE5_Pos            (10)
#define GPIO_PMODE5_Msk            (0x3 << GPIO_PMODE5_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE5                GPIO_PMODE5_Msk
#define GPIO_PMODE5_0              (0x0 << GPIO_PMODE5_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE5_1              (0x1 << GPIO_PMODE5_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE5_2              (0x2 << GPIO_PMODE5_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE5_3              (0x3 << GPIO_PMODE5_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE6_Pos            (12)
#define GPIO_PMODE6_Msk            (0x3 << GPIO_PMODE6_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE6                GPIO_PMODE6_Msk
#define GPIO_PMODE6_0              (0x0 << GPIO_PMODE6_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE6_1              (0x1 << GPIO_PMODE6_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE6_2              (0x2 << GPIO_PMODE6_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE6_3              (0x3 << GPIO_PMODE6_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE7_Pos            (14)
#define GPIO_PMODE7_Msk            (0x3 << GPIO_PMODE7_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE7                GPIO_PMODE7_Msk
#define GPIO_PMODE7_0              (0x0 << GPIO_PMODE7_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE7_1              (0x1 << GPIO_PMODE7_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE7_2              (0x2 << GPIO_PMODE7_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE7_3              (0x3 << GPIO_PMODE7_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE8_Pos            (16)
#define GPIO_PMODE8_Msk            (0x3 << GPIO_PMODE8_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE8                GPIO_PMODE8_Msk
#define GPIO_PMODE8_0              (0x0 << GPIO_PMODE8_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE8_1              (0x1 << GPIO_PMODE8_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE8_2              (0x2 << GPIO_PMODE8_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE8_3              (0x3 << GPIO_PMODE8_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE9_Pos            (18)
#define GPIO_PMODE9_Msk            (0x3 << GPIO_PMODE9_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE9                GPIO_PMODE9_Msk
#define GPIO_PMODE9_0              (0x0 << GPIO_PMODE9_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE9_1              (0x1 << GPIO_PMODE9_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE9_2              (0x2 << GPIO_PMODE9_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE9_3              (0x3 << GPIO_PMODE9_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE10_Pos            (20)
#define GPIO_PMODE10_Msk            (0x3 << GPIO_PMODE10_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE10                GPIO_PMODE10_Msk
#define GPIO_PMODE10_0              (0x0 << GPIO_PMODE10_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE10_1              (0x1 << GPIO_PMODE10_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE10_2              (0x2 << GPIO_PMODE10_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE10_3              (0x3 << GPIO_PMODE10_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE11_Pos            (22)
#define GPIO_PMODE11_Msk            (0x3 << GPIO_PMODE11_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE11                GPIO_PMODE11_Msk
#define GPIO_PMODE11_0              (0x0 << GPIO_PMODE11_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE11_1              (0x1 << GPIO_PMODE11_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE11_2              (0x2 << GPIO_PMODE11_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE11_3              (0x3 << GPIO_PMODE11_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE12_Pos            (24)
#define GPIO_PMODE12_Msk            (0x3 << GPIO_PMODE12_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE12                GPIO_PMODE12_Msk
#define GPIO_PMODE12_0              (0x0 << GPIO_PMODE12_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE12_1              (0x1 << GPIO_PMODE12_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE12_2              (0x2 << GPIO_PMODE12_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE12_3              (0x3 << GPIO_PMODE12_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE13_Pos            (26)
#define GPIO_PMODE13_Msk            (0x3 << GPIO_PMODE13_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE13                GPIO_PMODE13_Msk
#define GPIO_PMODE13_0              (0x0 << GPIO_PMODE13_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE13_1              (0x1 << GPIO_PMODE13_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE13_2              (0x2 << GPIO_PMODE13_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE13_3              (0x3 << GPIO_PMODE13_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE14_Pos            (28)
#define GPIO_PMODE14_Msk            (0x3 << GPIO_PMODE14_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE14                GPIO_PMODE14_Msk
#define GPIO_PMODE14_0              (0x0 << GPIO_PMODE14_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE14_1              (0x1 << GPIO_PMODE14_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE14_2              (0x2 << GPIO_PMODE14_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE14_3              (0x3 << GPIO_PMODE14_Pos)         /*!< 0x00000003 */

#define GPIO_PMODE15_Pos            (30)
#define GPIO_PMODE15_Msk            (0x3 << GPIO_PMODE15_Pos)         /*!< 0x00000003 */
#define GPIO_PMODE15                GPIO_PMODE15_Msk
#define GPIO_PMODE15_0              (0x0 << GPIO_PMODE15_Pos)         /*!< 0x00000000 */
#define GPIO_PMODE15_1              (0x1 << GPIO_PMODE15_Pos)         /*!< 0x00000001 */
#define GPIO_PMODE15_2              (0x2 << GPIO_PMODE15_Pos)         /*!< 0x00000002 */
#define GPIO_PMODE15_3              (0x3 << GPIO_PMODE15_Pos)         /*!< 0x00000003 */




/******************  Bit definition for GPIO_POTYPER register  *****************/
#define GPIO_POTYPE_POT_0                (0x00000001)
#define GPIO_POTYPE_POT_1                (0x00000002)
#define GPIO_POTYPE_POT_2                (0x00000004)
#define GPIO_POTYPE_POT_3                (0x00000008)
#define GPIO_POTYPE_POT_4                (0x00000010)
#define GPIO_POTYPE_POT_5                (0x00000020)
#define GPIO_POTYPE_POT_6                (0x00000040)
#define GPIO_POTYPE_POT_7                (0x00000080)
#define GPIO_POTYPE_POT_8                (0x00000100)
#define GPIO_POTYPE_POT_9                (0x00000200)
#define GPIO_POTYPE_POT_10               (0x00000400)
#define GPIO_POTYPE_POT_11               (0x00000800)
#define GPIO_POTYPE_POT_12               (0x00001000)
#define GPIO_POTYPE_POT_13               (0x00002000)
#define GPIO_POTYPE_POT_14               (0x00004000)
#define GPIO_POTYPE_POT_15               (0x00008000)


/*******************  Bit definition for GPIO_PUPDR register ******************/
#define GPIO_PUPD0_Pos            (0)
#define GPIO_PUPD0_Msk            (0x3 << GPIO_PUPD0_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD0                GPIO_PUPD0_Msk
#define GPIO_PUPD0_0              (0x0 << GPIO_PUPD0_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD0_1              (0x1 << GPIO_PUPD0_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD0_2              (0x2 << GPIO_PUPD0_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD1_Pos            (2)
#define GPIO_PUPD1_Msk            (0x3 << GPIO_PUPD1_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD1                GPIO_PUPD1_Msk
#define GPIO_PUPD1_0              (0x0 << GPIO_PUPD1_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD1_1              (0x1 << GPIO_PUPD1_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD1_2              (0x2 << GPIO_PUPD1_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD2_Pos            (4)
#define GPIO_PUPD2_Msk            (0x3 << GPIO_PUPD2_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD2                GPIO_PUPD2_Msk
#define GPIO_PUPD2_0              (0x0 << GPIO_PUPD2_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD2_1              (0x1 << GPIO_PUPD2_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD2_2              (0x2 << GPIO_PUPD2_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD3_Pos            (6)
#define GPIO_PUPD3_Msk            (0x3 << GPIO_PUPD3_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD3                GPIO_PUPD3_Msk
#define GPIO_PUPD3_0              (0x0 << GPIO_PUPD3_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD3_1              (0x1 << GPIO_PUPD3_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD3_2              (0x2 << GPIO_PUPD3_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD4_Pos            (8)
#define GPIO_PUPD4_Msk            (0x3 << GPIO_PUPD4_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD4                GPIO_PUPD4_Msk
#define GPIO_PUPD4_0              (0x0 << GPIO_PUPD4_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD4_1              (0x1 << GPIO_PUPD4_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD4_2              (0x2 << GPIO_PUPD4_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD5_Pos            (10)
#define GPIO_PUPD5_Msk            (0x3 << GPIO_PUPD5_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD5                GPIO_PUPD5_Msk
#define GPIO_PUPD5_0              (0x0 << GPIO_PUPD5_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD5_1              (0x1 << GPIO_PUPD5_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD5_2              (0x2 << GPIO_PUPD5_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD6_Pos            (12)
#define GPIO_PUPD6_Msk            (0x3 << GPIO_PUPD6_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD6                GPIO_PUPD6_Msk
#define GPIO_PUPD6_0              (0x0 << GPIO_PUPD6_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD6_1              (0x1 << GPIO_PUPD6_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD6_2              (0x2 << GPIO_PUPD6_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD7_Pos            (14)
#define GPIO_PUPD7_Msk            (0x3 << GPIO_PUPD7_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD7                GPIO_PUPD7_Msk
#define GPIO_PUPD7_0              (0x0 << GPIO_PUPD7_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD7_1              (0x1 << GPIO_PUPD7_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD7_2              (0x2 << GPIO_PUPD7_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD8_Pos            (16)
#define GPIO_PUPD8_Msk            (0x3 << GPIO_PUPD8_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD8                GPIO_PUPD8_Msk
#define GPIO_PUPD8_0              (0x0 << GPIO_PUPD8_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD8_1              (0x1 << GPIO_PUPD8_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD8_2              (0x2 << GPIO_PUPD8_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD9_Pos            (18)
#define GPIO_PUPD9_Msk            (0x3 << GPIO_PUPD9_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD9                GPIO_PUPD9_Msk
#define GPIO_PUPD9_0              (0x0 << GPIO_PUPD9_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD9_1              (0x1 << GPIO_PUPD9_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD9_2              (0x2 << GPIO_PUPD9_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD10_Pos             (20)
#define GPIO_PUPD10_Msk            (0x3 << GPIO_PUPD10_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD10                GPIO_PUPD10_Msk
#define GPIO_PUPD10_0              (0x0 << GPIO_PUPD10_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD10_1              (0x1 << GPIO_PUPD10_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD10_2              (0x2 << GPIO_PUPD10_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD11_Pos            (22)
#define GPIO_PUPD11_Msk            (0x3 << GPIO_PUPD11_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD11                GPIO_PUPD11_Msk
#define GPIO_PUPD11_0              (0x0 << GPIO_PUPD11_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD11_1              (0x1 << GPIO_PUPD11_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD11_2              (0x2 << GPIO_PUPD11_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD12_Pos            (24)
#define GPIO_PUPD12_Msk            (0x3 << GPIO_PUPD12_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD12                GPIO_PUPD12_Msk
#define GPIO_PUPD12_0              (0x0 << GPIO_PUPD12_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD12_1              (0x1 << GPIO_PUPD12_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD12_2              (0x2 << GPIO_PUPD12_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD13_Pos            (26)
#define GPIO_PUPD13_Msk            (0x3 << GPIO_PUPD13_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD13                GPIO_PUPD13_Msk
#define GPIO_PUPD13_0              (0x0 << GPIO_PUPD13_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD13_1              (0x1 << GPIO_PUPD13_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD13_2              (0x2 << GPIO_PUPD13_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD14_Pos            (28)
#define GPIO_PUPD14_Msk            (0x3 << GPIO_PUPD14_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD14                GPIO_PUPD14_Msk
#define GPIO_PUPD14_0              (0x0 << GPIO_PUPD14_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD14_1              (0x1 << GPIO_PUPD14_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD14_2              (0x2 << GPIO_PUPD14_Pos)         /*!< 0x00000002 */

#define GPIO_PUPD15_Pos            (30)
#define GPIO_PUPD15_Msk            (0x3 << GPIO_PUPD15_Pos)         /*!< 0x00000003 */
#define GPIO_PUPD15                GPIO_PUPD15_Msk
#define GPIO_PUPD15_0              (0x0 << GPIO_PUPD15_Pos)         /*!< 0x00000000 */
#define GPIO_PUPD15_1              (0x1 << GPIO_PUPD15_Pos)         /*!< 0x00000001 */
#define GPIO_PUPD15_2              (0x2 << GPIO_PUPD15_Pos)         /*!< 0x00000002 */


/*!<******************  Bit definition for GPIO_IDR register  *******************/
#define GPIO_PID_PID0  ((uint16_t)0x0001) /*!< Port input data, bit 0 */
#define GPIO_PID_PID1  ((uint16_t)0x0002) /*!< Port input data, bit 1 */
#define GPIO_PID_PID2  ((uint16_t)0x0004) /*!< Port input data, bit 2 */
#define GPIO_PID_PID3  ((uint16_t)0x0008) /*!< Port input data, bit 3 */
#define GPIO_PID_PID4  ((uint16_t)0x0010) /*!< Port input data, bit 4 */
#define GPIO_PID_PID5  ((uint16_t)0x0020) /*!< Port input data, bit 5 */
#define GPIO_PID_PID6  ((uint16_t)0x0040) /*!< Port input data, bit 6 */
#define GPIO_PID_PID7  ((uint16_t)0x0080) /*!< Port input data, bit 7 */
#define GPIO_PID_PID8  ((uint16_t)0x0100) /*!< Port input data, bit 8 */
#define GPIO_PID_PID9  ((uint16_t)0x0200) /*!< Port input data, bit 9 */
#define GPIO_PID_PID10 ((uint16_t)0x0400) /*!< Port input data, bit 10 */
#define GPIO_PID_PID11 ((uint16_t)0x0800) /*!< Port input data, bit 11 */
#define GPIO_PID_PID12 ((uint16_t)0x1000) /*!< Port input data, bit 12 */
#define GPIO_PID_PID13 ((uint16_t)0x2000) /*!< Port input data, bit 13 */
#define GPIO_PID_PID14 ((uint16_t)0x4000) /*!< Port input data, bit 14 */
#define GPIO_PID_PID15 ((uint16_t)0x8000) /*!< Port input data, bit 15 */

/*******************  Bit definition for GPIO_POD register  *******************/
#define GPIO_POD_POD0  ((uint16_t)0x0001) /*!< Port output data, bit 0 */
#define GPIO_POD_POD1  ((uint16_t)0x0002) /*!< Port output data, bit 1 */
#define GPIO_POD_POD2  ((uint16_t)0x0004) /*!< Port output data, bit 2 */
#define GPIO_POD_POD3  ((uint16_t)0x0008) /*!< Port output data, bit 3 */
#define GPIO_POD_POD4  ((uint16_t)0x0010) /*!< Port output data, bit 4 */
#define GPIO_POD_POD5  ((uint16_t)0x0020) /*!< Port output data, bit 5 */
#define GPIO_POD_POD6  ((uint16_t)0x0040) /*!< Port output data, bit 6 */
#define GPIO_POD_POD7  ((uint16_t)0x0080) /*!< Port output data, bit 7 */
#define GPIO_POD_POD8  ((uint16_t)0x0100) /*!< Port output data, bit 8 */
#define GPIO_POD_POD9  ((uint16_t)0x0200) /*!< Port output data, bit 9 */
#define GPIO_POD_POD10 ((uint16_t)0x0400) /*!< Port output data, bit 10 */
#define GPIO_POD_POD11 ((uint16_t)0x0800) /*!< Port output data, bit 11 */
#define GPIO_POD_POD12 ((uint16_t)0x1000) /*!< Port output data, bit 12 */
#define GPIO_POD_POD13 ((uint16_t)0x2000) /*!< Port output data, bit 13 */
#define GPIO_POD_POD14 ((uint16_t)0x4000) /*!< Port output data, bit 14 */
#define GPIO_POD_POD15 ((uint16_t)0x8000) /*!< Port output data, bit 15 */

/******************  Bit definition for GPIO_BSRR register  *******************/
#define GPIO_PBSC_PBS0  ((uint32_t)0x00000001) /*!< Port x Set bit 0 */
#define GPIO_PBSC_PBS1  ((uint32_t)0x00000002) /*!< Port x Set bit 1 */
#define GPIO_PBSC_PBS2  ((uint32_t)0x00000004) /*!< Port x Set bit 2 */
#define GPIO_PBSC_PBS3  ((uint32_t)0x00000008) /*!< Port x Set bit 3 */
#define GPIO_PBSC_PBS4  ((uint32_t)0x00000010) /*!< Port x Set bit 4 */
#define GPIO_PBSC_PBS5  ((uint32_t)0x00000020) /*!< Port x Set bit 5 */
#define GPIO_PBSC_PBS6  ((uint32_t)0x00000040) /*!< Port x Set bit 6 */
#define GPIO_PBSC_PBS7  ((uint32_t)0x00000080) /*!< Port x Set bit 7 */
#define GPIO_PBSC_PBS8  ((uint32_t)0x00000100) /*!< Port x Set bit 8 */
#define GPIO_PBSC_PBS9  ((uint32_t)0x00000200) /*!< Port x Set bit 9 */
#define GPIO_PBSC_PBS10 ((uint32_t)0x00000400) /*!< Port x Set bit 10 */
#define GPIO_PBSC_PBS11 ((uint32_t)0x00000800) /*!< Port x Set bit 11 */
#define GPIO_PBSC_PBS12 ((uint32_t)0x00001000) /*!< Port x Set bit 12 */
#define GPIO_PBSC_PBS13 ((uint32_t)0x00002000) /*!< Port x Set bit 13 */
#define GPIO_PBSC_PBS14 ((uint32_t)0x00004000) /*!< Port x Set bit 14 */
#define GPIO_PBSC_PBS15 ((uint32_t)0x00008000) /*!< Port x Set bit 15 */

#define GPIO_PBSC_PBC0  ((uint32_t)0x00010000) /*!< Port x Reset bit 0 */
#define GPIO_PBSC_PBC1  ((uint32_t)0x00020000) /*!< Port x Reset bit 1 */
#define GPIO_PBSC_PBC2  ((uint32_t)0x00040000) /*!< Port x Reset bit 2 */
#define GPIO_PBSC_PBC3  ((uint32_t)0x00080000) /*!< Port x Reset bit 3 */
#define GPIO_PBSC_PBC4  ((uint32_t)0x00100000) /*!< Port x Reset bit 4 */
#define GPIO_PBSC_PBC5  ((uint32_t)0x00200000) /*!< Port x Reset bit 5 */
#define GPIO_PBSC_PBC6  ((uint32_t)0x00400000) /*!< Port x Reset bit 6 */
#define GPIO_PBSC_PBC7  ((uint32_t)0x00800000) /*!< Port x Reset bit 7 */
#define GPIO_PBSC_PBC8  ((uint32_t)0x01000000) /*!< Port x Reset bit 8 */
#define GPIO_PBSC_PBC9  ((uint32_t)0x02000000) /*!< Port x Reset bit 9 */
#define GPIO_PBSC_PBC10 ((uint32_t)0x04000000) /*!< Port x Reset bit 10 */
#define GPIO_PBSC_PBC11 ((uint32_t)0x08000000) /*!< Port x Reset bit 11 */
#define GPIO_PBSC_PBC12 ((uint32_t)0x10000000) /*!< Port x Reset bit 12 */
#define GPIO_PBSC_PBC13 ((uint32_t)0x20000000) /*!< Port x Reset bit 13 */
#define GPIO_PBSC_PBC14 ((uint32_t)0x40000000) /*!< Port x Reset bit 14 */
#define GPIO_PBSC_PBC15 ((uint32_t)0x80000000) /*!< Port x Reset bit 15 */

/*******************  Bit definition for GPIO_BRR register  *******************/
#define GPIO_PBC_PBC0  ((uint16_t)0x0001) /*!< Port x Reset bit 0 */
#define GPIO_PBC_PBC1  ((uint16_t)0x0002) /*!< Port x Reset bit 1 */
#define GPIO_PBC_PBC2  ((uint16_t)0x0004) /*!< Port x Reset bit 2 */
#define GPIO_PBC_PBC3  ((uint16_t)0x0008) /*!< Port x Reset bit 3 */
#define GPIO_PBC_PBC4  ((uint16_t)0x0010) /*!< Port x Reset bit 4 */
#define GPIO_PBC_PBC5  ((uint16_t)0x0020) /*!< Port x Reset bit 5 */
#define GPIO_PBC_PBC6  ((uint16_t)0x0040) /*!< Port x Reset bit 6 */
#define GPIO_PBC_PBC7  ((uint16_t)0x0080) /*!< Port x Reset bit 7 */
#define GPIO_PBC_PBC8  ((uint16_t)0x0100) /*!< Port x Reset bit 8 */
#define GPIO_PBC_PBC9  ((uint16_t)0x0200) /*!< Port x Reset bit 9 */
#define GPIO_PBC_PBC10 ((uint16_t)0x0400) /*!< Port x Reset bit 10 */
#define GPIO_PBC_PBC11 ((uint16_t)0x0800) /*!< Port x Reset bit 11 */
#define GPIO_PBC_PBC12 ((uint16_t)0x1000) /*!< Port x Reset bit 12 */
#define GPIO_PBC_PBC13 ((uint16_t)0x2000) /*!< Port x Reset bit 13 */
#define GPIO_PBC_PBC14 ((uint16_t)0x4000) /*!< Port x Reset bit 14 */
#define GPIO_PBC_PBC15 ((uint16_t)0x8000) /*!< Port x Reset bit 15 */

/******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_PLOCK_PLOCK0  ((uint32_t)0x00000001) /*!< Port x Lock bit 0 */
#define GPIO_PLOCK_PLOCK1  ((uint32_t)0x00000002) /*!< Port x Lock bit 1 */
#define GPIO_PLOCK_PLOCK2  ((uint32_t)0x00000004) /*!< Port x Lock bit 2 */
#define GPIO_PLOCK_PLOCK3  ((uint32_t)0x00000008) /*!< Port x Lock bit 3 */
#define GPIO_PLOCK_PLOCK4  ((uint32_t)0x00000010) /*!< Port x Lock bit 4 */
#define GPIO_PLOCK_PLOCK5  ((uint32_t)0x00000020) /*!< Port x Lock bit 5 */
#define GPIO_PLOCK_PLOCK6  ((uint32_t)0x00000040) /*!< Port x Lock bit 6 */
#define GPIO_PLOCK_PLOCK7  ((uint32_t)0x00000080) /*!< Port x Lock bit 7 */
#define GPIO_PLOCK_PLOCK8  ((uint32_t)0x00000100) /*!< Port x Lock bit 8 */
#define GPIO_PLOCK_PLOCK9  ((uint32_t)0x00000200) /*!< Port x Lock bit 9 */
#define GPIO_PLOCK_PLOCK10 ((uint32_t)0x00000400) /*!< Port x Lock bit 10 */
#define GPIO_PLOCK_PLOCK11 ((uint32_t)0x00000800) /*!< Port x Lock bit 11 */
#define GPIO_PLOCK_PLOCK12 ((uint32_t)0x00001000) /*!< Port x Lock bit 12 */
#define GPIO_PLOCK_PLOCK13 ((uint32_t)0x00002000) /*!< Port x Lock bit 13 */
#define GPIO_PLOCK_PLOCK14 ((uint32_t)0x00004000) /*!< Port x Lock bit 14 */
#define GPIO_PLOCK_PLOCK15 ((uint32_t)0x00008000) /*!< Port x Lock bit 15 */
#define GPIO_PLOCK_PLOCKK  ((uint32_t)0x00010000) /*!< Lock key */

/******************  Bit definition for GPIO_AFL register  *******************/
#define GPIO_AFL_AFSEL0  ((uint32_t)0x0000000F) /*!< Port x AFL bit (0..3) */
#define GPIO_AFL_AFSEL1  ((uint32_t)0x000000F0) /*!< Port x AFL bit (4..7) */
#define GPIO_AFL_AFSEL2  ((uint32_t)0x00000F00) /*!< Port x AFL bit (8..11) */
#define GPIO_AFL_AFSEL3  ((uint32_t)0x0000F000) /*!< Port x AFL bit (12..15) */
#define GPIO_AFL_AFSEL4  ((uint32_t)0x000F0000) /*!< Port x AFL bit (16..19) */
#define GPIO_AFL_AFSEL5  ((uint32_t)0x00F00000) /*!< Port x AFL bit (20..23) */
#define GPIO_AFL_AFSEL6  ((uint32_t)0x0F000000) /*!< Port x AFL bit (24..27) */
#define GPIO_AFL_AFSEL7  ((uint32_t)0xF0000000) /*!< Port x AFL bit (27..31) */

/******************  Bit definition for GPIO_AFH register  *******************/
#define GPIO_AFH_AFSEL8  ((uint32_t)0x0000000F) /*!< Port x AFH bit (0..3) */
#define GPIO_AFH_AFSEL9  ((uint32_t)0x000000F0) /*!< Port x AFH bit (4..7) */
#define GPIO_AFH_AFSEL10 ((uint32_t)0x00000F00) /*!< Port x AFH bit (8..11) */
#define GPIO_AFH_AFSEL11 ((uint32_t)0x0000F000) /*!< Port x AFH bit (12..15) */
#define GPIO_AFH_AFSEL12 ((uint32_t)0x000F0000) /*!< Port x AFH bit (16..19) */
#define GPIO_AFH_AFSEL13 ((uint32_t)0x00F00000) /*!< Port x AFH bit (20..23) */
#define GPIO_AFH_AFSEL14 ((uint32_t)0x0F000000) /*!< Port x AFH bit (24..27) */
#define GPIO_AFH_AFSEL15 ((uint32_t)0xF0000000) /*!< Port x AFH bit (27..31) */


/*******************  Bit definition for GPIO_DS register ******************/
#define GPIO_DS0_Pos            (0)
#define GPIO_DS0_Msk            (0x3 << GPIO_DS0_Pos)         /*!< 0x00000003 */
#define GPIO_DS0                        GPIO_DS0_Msk
#define GPIO_DS0_0              (0x0 << GPIO_DS0_Pos)         /*!< 0x00000000 */
#define GPIO_DS0_1              (0x1 << GPIO_DS0_Pos)         /*!< 0x00000001 */
#define GPIO_DS0_2              (0x2 << GPIO_DS0_Pos)         /*!< 0x00000002 */
#define GPIO_DS0_3              (0x3 << GPIO_DS0_Pos)         /*!< 0x00000003 */

#define GPIO_DS1_Pos            (2)
#define GPIO_DS1_Msk            (0x3 << GPIO_DS1_Pos)         /*!< 0x00000003 */
#define GPIO_DS1                        GPIO_DS1_Msk
#define GPIO_DS1_0              (0x0 << GPIO_DS1_Pos)         /*!< 0x00000000 */
#define GPIO_DS1_1              (0x1 << GPIO_DS1_Pos)         /*!< 0x00000001 */
#define GPIO_DS1_2              (0x2 << GPIO_DS1_Pos)         /*!< 0x00000002 */
#define GPIO_DS1_3              (0x3 << GPIO_DS1_Pos)         /*!< 0x00000003 */

#define GPIO_DS2_Pos            (4)
#define GPIO_DS2_Msk            (0x3 << GPIO_DS2_Pos)         /*!< 0x00000003 */
#define GPIO_DS2                        GPIO_DS2_Msk
#define GPIO_DS2_0              (0x0 << GPIO_DS2_Pos)         /*!< 0x00000000 */
#define GPIO_DS2_1              (0x1 << GPIO_DS2_Pos)         /*!< 0x00000001 */
#define GPIO_DS2_2              (0x2 << GPIO_DS2_Pos)         /*!< 0x00000002 */
#define GPIO_DS2_3              (0x3 << GPIO_DS2_Pos)         /*!< 0x00000003 */

#define GPIO_DS3_Pos            (6)
#define GPIO_DS3_Msk            (0x3 << GPIO_DS3_Pos)         /*!< 0x00000003 */
#define GPIO_DS3                        GPIO_DS3_Msk
#define GPIO_DS3_0              (0x0 << GPIO_DS3_Pos)         /*!< 0x00000000 */
#define GPIO_DS3_1              (0x1 << GPIO_DS3_Pos)         /*!< 0x00000001 */
#define GPIO_DS3_2              (0x2 << GPIO_DS3_Pos)         /*!< 0x00000002 */
#define GPIO_DS3_3              (0x3 << GPIO_DS3_Pos)         /*!< 0x00000003 */

#define GPIO_DS4_Pos            (8)
#define GPIO_DS4_Msk            (0x3 << GPIO_DS4_Pos)         /*!< 0x00000003 */
#define GPIO_DS4                        GPIO_DS4_Msk
#define GPIO_DS4_0              (0x0 << GPIO_DS4_Pos)         /*!< 0x00000000 */
#define GPIO_DS4_1              (0x1 << GPIO_DS4_Pos)         /*!< 0x00000001 */
#define GPIO_DS4_2              (0x2 << GPIO_DS4_Pos)         /*!< 0x00000002 */
#define GPIO_DS4_3              (0x3 << GPIO_DS4_Pos)         /*!< 0x00000003 */

#define GPIO_DS5_Pos            (10)
#define GPIO_DS5_Msk            (0x3 << GPIO_DS5_Pos)         /*!< 0x00000003 */
#define GPIO_DS5                        GPIO_DS5_Msk
#define GPIO_DS5_0              (0x0 << GPIO_DS5_Pos)         /*!< 0x00000000 */
#define GPIO_DS5_1              (0x1 << GPIO_DS5_Pos)         /*!< 0x00000001 */
#define GPIO_DS5_2              (0x2 << GPIO_DS5_Pos)         /*!< 0x00000002 */
#define GPIO_DS5_3              (0x3 << GPIO_DS5_Pos)         /*!< 0x00000003 */

#define GPIO_DS6_Pos            (12)
#define GPIO_DS6_Msk            (0x3 << GPIO_DS6_Pos)         /*!< 0x00000003 */
#define GPIO_DS6                        GPIO_DS6_Msk
#define GPIO_DS6_0              (0x0 << GPIO_DS6_Pos)         /*!< 0x00000000 */
#define GPIO_DS6_1              (0x1 << GPIO_DS6_Pos)         /*!< 0x00000001 */
#define GPIO_DS6_2              (0x2 << GPIO_DS6_Pos)         /*!< 0x00000002 */
#define GPIO_DS6_3              (0x3 << GPIO_DS6_Pos)         /*!< 0x00000003 */

#define GPIO_DS7_Pos            (14)
#define GPIO_DS7_Msk            (0x3 << GPIO_DS7_Pos)         /*!< 0x00000003 */
#define GPIO_DS7                        GPIO_DS7_Msk
#define GPIO_DS7_0              (0x0 << GPIO_DS7_Pos)         /*!< 0x00000000 */
#define GPIO_DS7_1              (0x1 << GPIO_DS7_Pos)         /*!< 0x00000001 */
#define GPIO_DS7_2              (0x2 << GPIO_DS7_Pos)         /*!< 0x00000002 */
#define GPIO_DS7_3              (0x3 << GPIO_DS7_Pos)         /*!< 0x00000003 */


#define GPIO_DS8_Pos            (16)
#define GPIO_DS8_Msk            (0x3 << GPIO_DS8_Pos)         /*!< 0x00000003 */
#define GPIO_DS8                        GPIO_DS8_Msk
#define GPIO_DS8_0              (0x0 << GPIO_DS8_Pos)         /*!< 0x00000000 */
#define GPIO_DS8_1              (0x1 << GPIO_DS8_Pos)         /*!< 0x00000001 */
#define GPIO_DS8_2              (0x2 << GPIO_DS8_Pos)         /*!< 0x00000002 */
#define GPIO_DS8_3              (0x3 << GPIO_DS8_Pos)         /*!< 0x00000003 */

#define GPIO_DS9_Pos            (18)
#define GPIO_DS9_Msk            (0x3 << GPIO_DS9_Pos)         /*!< 0x00000003 */
#define GPIO_DS9                        GPIO_DS9_Msk
#define GPIO_DS9_0              (0x0 << GPIO_DS9_Pos)         /*!< 0x00000000 */
#define GPIO_DS9_1              (0x1 << GPIO_DS9_Pos)         /*!< 0x00000001 */
#define GPIO_DS9_2              (0x2 << GPIO_DS9_Pos)         /*!< 0x00000002 */
#define GPIO_DS9_3              (0x3 << GPIO_DS9_Pos)         /*!< 0x00000003 */

#define GPIO_DS10_Pos            (20)
#define GPIO_DS10_Msk            (0x3 << GPIO_DS10_Pos)         /*!< 0x00000003 */
#define GPIO_DS10                        GPIO_DS10_Msk
#define GPIO_DS10_0              (0x0 << GPIO_DS10_Pos)         /*!< 0x00000000 */
#define GPIO_DS10_1              (0x1 << GPIO_DS10_Pos)         /*!< 0x00000001 */
#define GPIO_DS10_2              (0x2 << GPIO_DS10_Pos)         /*!< 0x00000002 */
#define GPIO_DS10_3              (0x3 << GPIO_DS10_Pos)         /*!< 0x00000003 */

#define GPIO_DS11_Pos            (22)
#define GPIO_DS11_Msk            (0x3 << GPIO_DS11_Pos)         /*!< 0x00000003 */
#define GPIO_DS11                        GPIO_DS11_Msk
#define GPIO_DS11_0              (0x0 << GPIO_DS11_Pos)         /*!< 0x00000000 */
#define GPIO_DS11_1              (0x1 << GPIO_DS11_Pos)         /*!< 0x00000001 */
#define GPIO_DS11_2              (0x2 << GPIO_DS11_Pos)         /*!< 0x00000002 */
#define GPIO_DS11_3              (0x3 << GPIO_DS11_Pos)         /*!< 0x00000003 */

#define GPIO_DS12_Pos            (24)
#define GPIO_DS12_Msk            (0x3 << GPIO_DS12_Pos)         /*!< 0x00000003 */
#define GPIO_DS12                        GPIO_DS12_Msk
#define GPIO_DS12_0              (0x0 << GPIO_DS12_Pos)         /*!< 0x00000000 */
#define GPIO_DS12_1              (0x1 << GPIO_DS12_Pos)         /*!< 0x00000001 */
#define GPIO_DS12_2              (0x2 << GPIO_DS12_Pos)         /*!< 0x00000002 */
#define GPIO_DS12_3              (0x3 << GPIO_DS12_Pos)         /*!< 0x00000003 */

#define GPIO_DS13_Pos            (26)
#define GPIO_DS13_Msk            (0x3 << GPIO_DS13_Pos)         /*!< 0x00000003 */
#define GPIO_DS13                        GPIO_DS13_Msk
#define GPIO_DS13_0              (0x0 << GPIO_DS13_Pos)         /*!< 0x00000000 */
#define GPIO_DS13_1              (0x1 << GPIO_DS13_Pos)         /*!< 0x00000001 */
#define GPIO_DS13_2              (0x2 << GPIO_DS13_Pos)         /*!< 0x00000002 */
#define GPIO_DS13_3              (0x3 << GPIO_DS13_Pos)         /*!< 0x00000003 */

#define GPIO_DS14_Pos            (28)
#define GPIO_DS14_Msk            (0x3 << GPIO_DS14_Pos)         /*!< 0x00000003 */
#define GPIO_DS14                        GPIO_DS14_Msk
#define GPIO_DS14_0              (0x0 << GPIO_DS14_Pos)         /*!< 0x00000000 */
#define GPIO_DS14_1              (0x1 << GPIO_DS14_Pos)         /*!< 0x00000001 */
#define GPIO_DS14_2              (0x2 << GPIO_DS14_Pos)         /*!< 0x00000002 */
#define GPIO_DS14_3              (0x3 << GPIO_DS14_Pos)         /*!< 0x00000003 */

#define GPIO_DS15_Pos            (30)
#define GPIO_DS15_Msk            (0x3 << GPIO_DS15_Pos)         /*!< 0x00000003 */
#define GPIO_DS15                        GPIO_DS15_Msk
#define GPIO_DS15_0              (0x0 << GPIO_DS15_Pos)         /*!< 0x00000000 */
#define GPIO_DS15_1              (0x1 << GPIO_DS15_Pos)         /*!< 0x00000001 */
#define GPIO_DS15_2              (0x2 << GPIO_DS15_Pos)         /*!< 0x00000002 */
#define GPIO_DS15_3              (0x3 << GPIO_DS15_Pos)         /*!< 0x00000003 */

/*******************  Bit definition for GPIO_SR register  *******************/
#define GPIO_SR_SR0  ((uint16_t)0x0001) /*!<  Slew rate bit 0 */
#define GPIO_SR_SR1  ((uint16_t)0x0002) /*!<  Slew rate bit 1 */
#define GPIO_SR_SR2  ((uint16_t)0x0004) /*!<  Slew rate bit 2 */
#define GPIO_SR_SR3  ((uint16_t)0x0008) /*!<  Slew rate bit 3 */
#define GPIO_SR_SR4  ((uint16_t)0x0010) /*!<  Slew rate bit 4 */
#define GPIO_SR_SR5  ((uint16_t)0x0020) /*!<  Slew rate bit 5 */
#define GPIO_SR_SR6  ((uint16_t)0x0040) /*!<  Slew rate bit 6 */
#define GPIO_SR_SR7  ((uint16_t)0x0080) /*!<  Slew rate bit 7 */
#define GPIO_SR_SR8  ((uint16_t)0x0100) /*!<  Slew rate bit 8 */
#define GPIO_SR_SR9  ((uint16_t)0x0200) /*!<  Slew rate bit 9 */
#define GPIO_SR_SR10 ((uint16_t)0x0400) /*!<  Slew rate bit 10 */
#define GPIO_SR_SR11 ((uint16_t)0x0800) /*!<  Slew rate bit 11 */
#define GPIO_SR_SR12 ((uint16_t)0x1000) /*!<  Slew rate bit 12 */
#define GPIO_SR_SR13 ((uint16_t)0x2000) /*!<  Slew rate bit 13 */
#define GPIO_SR_SR14 ((uint16_t)0x4000) /*!<  Slew rate bit 14 */
#define GPIO_SR_SR15 ((uint16_t)0x8000) /*!<  Slew rate bit 15 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for AFIO_RMP_CFG register  *****************/
#define AFIO_RMP_CFG_SPI1_NSS ((uint16_t)0x0800) /*!< AFIO_RMP_CFG bit 11 */
#define AFIO_RMP_CFG_SPI2_NSS ((uint16_t)0x0400) /*!< AFIO_RMP_CFG bit 10 */
#define AFIO_RMP_CFG_ADC_ETRI ((uint16_t)0x0200) /*!< AFIO_RMP_CFG bit 9 */
#define AFIO_RMP_CFG_ADC_ETRR ((uint16_t)0x0100) /*!< AFIO_RMP_CFG bit 8 */
#define AFIO_RMP_CFG_EXTI_ETRI ((uint16_t)0x00F0) /*!< AFIO_RMP_CFG bit (4..7) */
#define AFIO_RMP_CFG_EXTI_ETRR ((uint16_t)0x000F) /*!< AFIO_RMP_CFG bit (0..3) */

/*****************  Bit definition for AFIO_EXTICR1 register  *****************/
#define AFIO_EXTI_CFG1_EXTI0 ((uint16_t)0x0003) /*!< EXTI 0 configuration */
#define AFIO_EXTI_CFG1_EXTI1 ((uint16_t)0x0030) /*!< EXTI 1 configuration */
#define AFIO_EXTI_CFG1_EXTI2 ((uint16_t)0x0300) /*!< EXTI 2 configuration */
#define AFIO_EXTI_CFG1_EXTI3 ((uint16_t)0x3000) /*!< EXTI 3 configuration */

/*!< EXTI0 configuration */
#define AFIO_EXTI_CFG1_EXTI0_PA ((uint16_t)0x0000) /*!< PA[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PB ((uint16_t)0x0001) /*!< PB[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PC ((uint16_t)0x0002) /*!< PC[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PD ((uint16_t)0x0003) /*!< PD[0] pin */

/*!< EXTI1 configuration */
#define AFIO_EXTI_CFG1_EXTI1_PA ((uint16_t)0x0000) /*!< PA[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PB ((uint16_t)0x0010) /*!< PB[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PC ((uint16_t)0x0020) /*!< PC[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PD ((uint16_t)0x0030) /*!< PD[1] pin */

/*!< EXTI2 configuration */
#define AFIO_EXTI_CFG1_EXTI2_PA ((uint16_t)0x0000) /*!< PA[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PB ((uint16_t)0x0100) /*!< PB[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PC ((uint16_t)0x0200) /*!< PC[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PD ((uint16_t)0x0300) /*!< PD[2] pin */

/*!< EXTI3 configuration */
#define AFIO_EXTI_CFG1_EXTI3_PA ((uint16_t)0x0000) /*!< PA[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PB ((uint16_t)0x1000) /*!< PB[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PC ((uint16_t)0x2000) /*!< PC[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PD ((uint16_t)0x3000) /*!< PD[3] pin */

/*****************  Bit definition for AFIO_EXTICR2 register  *****************/
#define AFIO_EXTI_CFG2_EXTI4 ((uint16_t)0x0003) /*!< EXTI 4 configuration */
#define AFIO_EXTI_CFG2_EXTI5 ((uint16_t)0x0030) /*!< EXTI 5 configuration */
#define AFIO_EXTI_CFG2_EXTI6 ((uint16_t)0x0300) /*!< EXTI 6 configuration */
#define AFIO_EXTI_CFG2_EXTI7 ((uint16_t)0x3000) /*!< EXTI 7 configuration */

/*!< EXTI4 configuration */
#define AFIO_EXTI_CFG2_EXTI4_PA ((uint16_t)0x0000) /*!< PA[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PB ((uint16_t)0x0001) /*!< PB[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PC ((uint16_t)0x0002) /*!< PC[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PD ((uint16_t)0x0003) /*!< PD[4] pin */

/*!< EXTI5 configuration */
#define AFIO_EXTI_CFG2_EXTI5_PA ((uint16_t)0x0000) /*!< PA[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PB ((uint16_t)0x0010) /*!< PB[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PC ((uint16_t)0x0020) /*!< PC[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PD ((uint16_t)0x0030) /*!< PD[5] pin */

/*!< EXTI6 configuration */
#define AFIO_EXTI_CFG2_EXTI6_PA ((uint16_t)0x0000) /*!< PA[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PB ((uint16_t)0x0100) /*!< PB[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PC ((uint16_t)0x0200) /*!< PC[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PD ((uint16_t)0x0300) /*!< PD[6] pin */

/*!< EXTI7 configuration */
#define AFIO_EXTI_CFG2_EXTI7_PA ((uint16_t)0x0000) /*!< PA[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PB ((uint16_t)0x1000) /*!< PB[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PC ((uint16_t)0x2000) /*!< PC[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PD ((uint16_t)0x3000) /*!< PD[7] pin */

/*****************  Bit definition for AFIO_EXTICR3 register  *****************/
#define AFIO_EXTI_CFG3_EXTI8  ((uint16_t)0x0003) /*!< EXTI 8 configuration */
#define AFIO_EXTI_CFG3_EXTI9  ((uint16_t)0x0030) /*!< EXTI 9 configuration */
#define AFIO_EXTI_CFG3_EXTI10 ((uint16_t)0x0300) /*!< EXTI 10 configuration */
#define AFIO_EXTI_CFG3_EXTI11 ((uint16_t)0x3000) /*!< EXTI 11 configuration */

/*!< EXTI8 configuration */
#define AFIO_EXTI_CFG3_EXTI8_PA ((uint16_t)0x0000) /*!< PA[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PB ((uint16_t)0x0001) /*!< PB[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PC ((uint16_t)0x0002) /*!< PC[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PD ((uint16_t)0x0003) /*!< PD[8] pin */

/*!< EXTI9 configuration */
#define AFIO_EXTI_CFG3_EXTI9_PA ((uint16_t)0x0000) /*!< PA[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PB ((uint16_t)0x0010) /*!< PB[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PC ((uint16_t)0x0020) /*!< PC[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PD ((uint16_t)0x0030) /*!< PD[9] pin */

/*!< EXTI10 configuration */
#define AFIO_EXTI_CFG3_EXTI10_PA ((uint16_t)0x0000) /*!< PA[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PB ((uint16_t)0x0100) /*!< PB[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PC ((uint16_t)0x0200) /*!< PC[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PD ((uint16_t)0x0300) /*!< PD[10] pin */

/*!< EXTI11 configuration */
#define AFIO_EXTI_CFG3_EXTI11_PA ((uint16_t)0x0000) /*!< PA[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PB ((uint16_t)0x1000) /*!< PB[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PC ((uint16_t)0x2000) /*!< PC[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PD ((uint16_t)0x3000) /*!< PD[11] pin */

/*****************  Bit definition for AFIO_EXTICR4 register  *****************/
#define AFIO_EXTI_CFG4_EXTI12 ((uint16_t)0x0003) /*!< EXTI 12 configuration */
#define AFIO_EXTI_CFG4_EXTI13 ((uint16_t)0x0030) /*!< EXTI 13 configuration */
#define AFIO_EXTI_CFG4_EXTI14 ((uint16_t)0x0300) /*!< EXTI 14 configuration */
#define AFIO_EXTI_CFG4_EXTI15 ((uint16_t)0x3000) /*!< EXTI 15 configuration */

/*!< EXTI12 configuration */
#define AFIO_EXTI_CFG4_EXTI12_PA ((uint16_t)0x0000) /*!< PA[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PB ((uint16_t)0x0001) /*!< PB[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PC ((uint16_t)0x0002) /*!< PC[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PD ((uint16_t)0x0003) /*!< PD[12] pin */

/*!< EXTI13 configuration */
#define AFIO_EXTI_CFG4_EXTI13_PA ((uint16_t)0x0000) /*!< PA[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PB ((uint16_t)0x0010) /*!< PB[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PC ((uint16_t)0x0020) /*!< PC[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PD ((uint16_t)0x0030) /*!< PD[13] pin */

/*!< EXTI14 configuration */
#define AFIO_EXTI_CFG4_EXTI14_PA ((uint16_t)0x0000) /*!< PA[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PB ((uint16_t)0x0100) /*!< PB[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PC ((uint16_t)0x0200) /*!< PC[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PD ((uint16_t)0x0300) /*!< PD[14] pin */

/*!< EXTI15 configuration */
#define AFIO_EXTI_CFG4_EXTI15_PA ((uint16_t)0x0000) /*!< PA[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PB ((uint16_t)0x1000) /*!< PB[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PC ((uint16_t)0x2000) /*!< PC[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PD ((uint16_t)0x3000) /*!< PD[15] pin */


/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for EXTI_IMR register  *******************/
#define EXTI_IMASK_IMASK0  ((uint32_t)0x00000001) /*!< Interrupt Mask on line 0 */
#define EXTI_IMASK_IMASK1  ((uint32_t)0x00000002) /*!< Interrupt Mask on line 1 */
#define EXTI_IMASK_IMASK2  ((uint32_t)0x00000004) /*!< Interrupt Mask on line 2 */
#define EXTI_IMASK_IMASK3  ((uint32_t)0x00000008) /*!< Interrupt Mask on line 3 */
#define EXTI_IMASK_IMASK4  ((uint32_t)0x00000010) /*!< Interrupt Mask on line 4 */
#define EXTI_IMASK_IMASK5  ((uint32_t)0x00000020) /*!< Interrupt Mask on line 5 */
#define EXTI_IMASK_IMASK6  ((uint32_t)0x00000040) /*!< Interrupt Mask on line 6 */
#define EXTI_IMASK_IMASK7  ((uint32_t)0x00000080) /*!< Interrupt Mask on line 7 */
#define EXTI_IMASK_IMASK8  ((uint32_t)0x00000100) /*!< Interrupt Mask on line 8 */
#define EXTI_IMASK_IMASK9  ((uint32_t)0x00000200) /*!< Interrupt Mask on line 9 */
#define EXTI_IMASK_IMASK10 ((uint32_t)0x00000400) /*!< Interrupt Mask on line 10 */
#define EXTI_IMASK_IMASK11 ((uint32_t)0x00000800) /*!< Interrupt Mask on line 11 */
#define EXTI_IMASK_IMASK12 ((uint32_t)0x00001000) /*!< Interrupt Mask on line 12 */
#define EXTI_IMASK_IMASK13 ((uint32_t)0x00002000) /*!< Interrupt Mask on line 13 */
#define EXTI_IMASK_IMASK14 ((uint32_t)0x00004000) /*!< Interrupt Mask on line 14 */
#define EXTI_IMASK_IMASK15 ((uint32_t)0x00008000) /*!< Interrupt Mask on line 15 */
#define EXTI_IMASK_IMASK16 ((uint32_t)0x00010000) /*!< Interrupt Mask on line 16 */
#define EXTI_IMASK_IMASK17 ((uint32_t)0x00020000) /*!< Interrupt Mask on line 17 */
#define EXTI_IMASK_IMASK18 ((uint32_t)0x00040000) /*!< Interrupt Mask on line 18 */
#define EXTI_IMASK_IMASK19 ((uint32_t)0x00080000) /*!< Interrupt Mask on line 19 */
#define EXTI_IMASK_IMASK20 ((uint32_t)0x00100000) /*!< Interrupt Mask on line 20 */
#define EXTI_IMASK_IMASK21 ((uint32_t)0x00200000) /*!< Interrupt Mask on line 21 */
#define EXTI_IMASK_IMASK22 ((uint32_t)0x00400000) /*!< Interrupt Mask on line 22 */
#define EXTI_IMASK_IMASK23 ((uint32_t)0x00800000) /*!< Interrupt Mask on line 23 */
#define EXTI_IMASK_IMASK24 ((uint32_t)0x01000000) /*!< Interrupt Mask on line 24 */
#define EXTI_IMASK_IMASK25 ((uint32_t)0x02000000) /*!< Interrupt Mask on line 25 */
#define EXTI_IMASK_IMASK26 ((uint32_t)0x04000000) /*!< Interrupt Mask on line 26 */
#define EXTI_IMASK_IMASK27 ((uint32_t)0x08000000) /*!< Interrupt Mask on line 27 */

/*******************  Bit definition for EXTI_EMR register  *******************/
#define EXTI_EMASK_EMASK0  ((uint32_t)0x00000001) /*!< Event Mask on line 0 */
#define EXTI_EMASK_EMASK1  ((uint32_t)0x00000002) /*!< Event Mask on line 1 */
#define EXTI_EMASK_EMASK2  ((uint32_t)0x00000004) /*!< Event Mask on line 2 */
#define EXTI_EMASK_EMASK3  ((uint32_t)0x00000008) /*!< Event Mask on line 3 */
#define EXTI_EMASK_EMASK4  ((uint32_t)0x00000010) /*!< Event Mask on line 4 */
#define EXTI_EMASK_EMASK5  ((uint32_t)0x00000020) /*!< Event Mask on line 5 */
#define EXTI_EMASK_EMASK6  ((uint32_t)0x00000040) /*!< Event Mask on line 6 */
#define EXTI_EMASK_EMASK7  ((uint32_t)0x00000080) /*!< Event Mask on line 7 */
#define EXTI_EMASK_EMASK8  ((uint32_t)0x00000100) /*!< Event Mask on line 8 */
#define EXTI_EMASK_EMASK9  ((uint32_t)0x00000200) /*!< Event Mask on line 9 */
#define EXTI_EMASK_EMASK10 ((uint32_t)0x00000400) /*!< Event Mask on line 10 */
#define EXTI_EMASK_EMASK11 ((uint32_t)0x00000800) /*!< Event Mask on line 11 */
#define EXTI_EMASK_EMASK12 ((uint32_t)0x00001000) /*!< Event Mask on line 12 */
#define EXTI_EMASK_EMASK13 ((uint32_t)0x00002000) /*!< Event Mask on line 13 */
#define EXTI_EMASK_EMASK14 ((uint32_t)0x00004000) /*!< Event Mask on line 14 */
#define EXTI_EMASK_EMASK15 ((uint32_t)0x00008000) /*!< Event Mask on line 15 */
#define EXTI_EMASK_EMASK16 ((uint32_t)0x00010000) /*!< Event Mask on line 16 */
#define EXTI_EMASK_EMASK17 ((uint32_t)0x00020000) /*!< Event Mask on line 17 */
#define EXTI_EMASK_EMASK18 ((uint32_t)0x00040000) /*!< Event Mask on line 18 */
#define EXTI_EMASK_EMASK19 ((uint32_t)0x00080000) /*!< Event Mask on line 19 */
#define EXTI_EMASK_EMASK20 ((uint32_t)0x00100000) /*!< Event Mask on line 20 */
#define EXTI_EMASK_EMASK21 ((uint32_t)0x00200000) /*!< Event Mask on line 21 */
#define EXTI_EMASK_EMASK22 ((uint32_t)0x00400000) /*!< Event Mask on line 22 */
#define EXTI_EMASK_EMASK23 ((uint32_t)0x00800000) /*!< Event Mask on line 23 */
#define EXTI_EMASK_EMASK24 ((uint32_t)0x01000000) /*!< Event Mask on line 24 */
#define EXTI_EMASK_EMASK25 ((uint32_t)0x02000000) /*!< Event Mask on line 25 */
#define EXTI_EMASK_EMASK26 ((uint32_t)0x04000000) /*!< Event Mask on line 26 */
#define EXTI_EMASK_EMASK27 ((uint32_t)0x08000000) /*!< Event Mask on line 27 */


/******************  Bit definition for EXTI_RT_CFG register  *******************/
#define EXTI_EMASK_RT_CFG_RT_CFG0  ((uint32_t)0x00000001) /*!< Rising trigger event configuration bit of line 0 */
#define EXTI_EMASK_RT_CFG_RT_CFG1  ((uint32_t)0x00000002) /*!< Rising trigger event configuration bit of line 1 */
#define EXTI_EMASK_RT_CFG_RT_CFG2  ((uint32_t)0x00000004) /*!< Rising trigger event configuration bit of line 2 */
#define EXTI_EMASK_RT_CFG_RT_CFG3  ((uint32_t)0x00000008) /*!< Rising trigger event configuration bit of line 3 */
#define EXTI_EMASK_RT_CFG_RT_CFG4  ((uint32_t)0x00000010) /*!< Rising trigger event configuration bit of line 4 */
#define EXTI_EMASK_RT_CFG_RT_CFG5  ((uint32_t)0x00000020) /*!< Rising trigger event configuration bit of line 5 */
#define EXTI_EMASK_RT_CFG_RT_CFG6  ((uint32_t)0x00000040) /*!< Rising trigger event configuration bit of line 6 */
#define EXTI_EMASK_RT_CFG_RT_CFG7  ((uint32_t)0x00000080) /*!< Rising trigger event configuration bit of line 7 */
#define EXTI_EMASK_RT_CFG_RT_CFG8  ((uint32_t)0x00000100) /*!< Rising trigger event configuration bit of line 8 */
#define EXTI_EMASK_RT_CFG_RT_CFG9  ((uint32_t)0x00000200) /*!< Rising trigger event configuration bit of line 9 */
#define EXTI_EMASK_RT_CFG_RT_CFG10 ((uint32_t)0x00000400) /*!< Rising trigger event configuration bit of line 10 */
#define EXTI_EMASK_RT_CFG_RT_CFG11 ((uint32_t)0x00000800) /*!< Rising trigger event configuration bit of line 11 */
#define EXTI_EMASK_RT_CFG_RT_CFG12 ((uint32_t)0x00001000) /*!< Rising trigger event configuration bit of line 12 */
#define EXTI_EMASK_RT_CFG_RT_CFG13 ((uint32_t)0x00002000) /*!< Rising trigger event configuration bit of line 13 */
#define EXTI_EMASK_RT_CFG_RT_CFG14 ((uint32_t)0x00004000) /*!< Rising trigger event configuration bit of line 14 */
#define EXTI_EMASK_RT_CFG_RT_CFG15 ((uint32_t)0x00008000) /*!< Rising trigger event configuration bit of line 15 */
#define EXTI_EMASK_RT_CFG_RT_CFG16 ((uint32_t)0x00010000) /*!< Rising trigger event configuration bit of line 16 */
#define EXTI_EMASK_RT_CFG_RT_CFG17 ((uint32_t)0x00020000) /*!< Rising trigger event configuration bit of line 17 */
#define EXTI_EMASK_RT_CFG_RT_CFG18 ((uint32_t)0x00040000) /*!< Rising trigger event configuration bit of line 18 */
#define EXTI_EMASK_RT_CFG_RT_CFG19 ((uint32_t)0x00080000) /*!< Rising trigger event configuration bit of line 19 */
#define EXTI_EMASK_RT_CFG_RT_CFG20 ((uint32_t)0x00100000) /*!< Rising trigger event configuration bit of line 20 */
#define EXTI_EMASK_RT_CFG_RT_CFG21 ((uint32_t)0x00200000) /*!< Rising trigger event configuration bit of line 21 */
#define EXTI_EMASK_RT_CFG_RT_CFG22 ((uint32_t)0x00400000) /*!< Rising trigger event configuration bit of line 22 */
#define EXTI_EMASK_RT_CFG_RT_CFG23 ((uint32_t)0x00800000) /*!< Rising trigger event configuration bit of line 23 */
#define EXTI_EMASK_RT_CFG_RT_CFG24 ((uint32_t)0x01000000) /*!< Rising trigger event configuration bit of line 24 */
#define EXTI_EMASK_RT_CFG_RT_CFG25 ((uint32_t)0x02000000) /*!< Rising trigger event configuration bit of line 25 */
#define EXTI_EMASK_RT_CFG_RT_CFG26 ((uint32_t)0x04000000) /*!< Rising trigger event configuration bit of line 26 */
#define EXTI_EMASK_RT_CFG_RT_CFG27 ((uint32_t)0x08000000) /*!< Rising trigger event configuration bit of line 27 */



/******************  Bit definition for EXTI_FT_CFG register  *******************/
#define EXTI_EMASK_FT_CFG_FT_CFG0  ((uint32_t)0x00000001) /*!< Falling trigger event configuration bit of line 0 */
#define EXTI_EMASK_FT_CFG_FT_CFG1  ((uint32_t)0x00000002) /*!< Falling trigger event configuration bit of line 1 */
#define EXTI_EMASK_FT_CFG_FT_CFG2  ((uint32_t)0x00000004) /*!< Falling trigger event configuration bit of line 2 */
#define EXTI_EMASK_FT_CFG_FT_CFG3  ((uint32_t)0x00000008) /*!< Falling trigger event configuration bit of line 3 */
#define EXTI_EMASK_FT_CFG_FT_CFG4  ((uint32_t)0x00000010) /*!< Falling trigger event configuration bit of line 4 */
#define EXTI_EMASK_FT_CFG_FT_CFG5  ((uint32_t)0x00000020) /*!< Falling trigger event configuration bit of line 5 */
#define EXTI_EMASK_FT_CFG_FT_CFG6  ((uint32_t)0x00000040) /*!< Falling trigger event configuration bit of line 6 */
#define EXTI_EMASK_FT_CFG_FT_CFG7  ((uint32_t)0x00000080) /*!< Falling trigger event configuration bit of line 7 */
#define EXTI_EMASK_FT_CFG_FT_CFG8  ((uint32_t)0x00000100) /*!< Falling trigger event configuration bit of line 8 */
#define EXTI_EMASK_FT_CFG_FT_CFG9  ((uint32_t)0x00000200) /*!< Falling trigger event configuration bit of line 9 */
#define EXTI_EMASK_FT_CFG_FT_CFG10 ((uint32_t)0x00000400) /*!< Falling trigger event configuration bit of line 10 */
#define EXTI_EMASK_FT_CFG_FT_CFG11 ((uint32_t)0x00000800) /*!< Falling trigger event configuration bit of line 11 */
#define EXTI_EMASK_FT_CFG_FT_CFG12 ((uint32_t)0x00001000) /*!< Falling trigger event configuration bit of line 12 */
#define EXTI_EMASK_FT_CFG_FT_CFG13 ((uint32_t)0x00002000) /*!< Falling trigger event configuration bit of line 13 */
#define EXTI_EMASK_FT_CFG_FT_CFG14 ((uint32_t)0x00004000) /*!< Falling trigger event configuration bit of line 14 */
#define EXTI_EMASK_FT_CFG_FT_CFG15 ((uint32_t)0x00008000) /*!< Falling trigger event configuration bit of line 15 */
#define EXTI_EMASK_FT_CFG_FT_CFG16 ((uint32_t)0x00010000) /*!< Falling trigger event configuration bit of line 16 */
#define EXTI_EMASK_FT_CFG_FT_CFG17 ((uint32_t)0x00020000) /*!< Falling trigger event configuration bit of line 17 */
#define EXTI_EMASK_FT_CFG_FT_CFG18 ((uint32_t)0x00040000) /*!< Falling trigger event configuration bit of line 18 */
#define EXTI_EMASK_FT_CFG_FT_CFG19 ((uint32_t)0x00080000) /*!< Falling trigger event configuration bit of line 19 */
#define EXTI_EMASK_FT_CFG_FT_CFG20 ((uint32_t)0x00100000) /*!< Falling trigger event configuration bit of line 20 */
#define EXTI_EMASK_FT_CFG_FT_CFG21 ((uint32_t)0x00200000) /*!< Falling trigger event configuration bit of line 21 */
#define EXTI_EMASK_FT_CFG_FT_CFG22 ((uint32_t)0x00400000) /*!< Falling trigger event configuration bit of line 22 */
#define EXTI_EMASK_FT_CFG_FT_CFG23 ((uint32_t)0x00800000) /*!< Falling trigger event configuration bit of line 23 */
#define EXTI_EMASK_FT_CFG_FT_CFG24 ((uint32_t)0x01000000) /*!< Falling trigger event configuration bit of line 24 */
#define EXTI_EMASK_FT_CFG_FT_CFG25 ((uint32_t)0x02000000) /*!< Falling trigger event configuration bit of line 25 */
#define EXTI_EMASK_FT_CFG_FT_CFG26 ((uint32_t)0x04000000) /*!< Falling trigger event configuration bit of line 26 */
#define EXTI_EMASK_FT_CFG_FT_CFG27 ((uint32_t)0x08000000) /*!< Falling trigger event configuration bit of line 27 */

/******************  Bit definition for EXTI_SWIE register  ******************/
#define EXTI_SWIE_SWIE0  ((uint32_t)0x00000001) /*!< Software Interrupt on line 0 */
#define EXTI_SWIE_SWIE1  ((uint32_t)0x00000002) /*!< Software Interrupt on line 1 */
#define EXTI_SWIE_SWIE2  ((uint32_t)0x00000004) /*!< Software Interrupt on line 2 */
#define EXTI_SWIE_SWIE3  ((uint32_t)0x00000008) /*!< Software Interrupt on line 3 */
#define EXTI_SWIE_SWIE4  ((uint32_t)0x00000010) /*!< Software Interrupt on line 4 */
#define EXTI_SWIE_SWIE5  ((uint32_t)0x00000020) /*!< Software Interrupt on line 5 */
#define EXTI_SWIE_SWIE6  ((uint32_t)0x00000040) /*!< Software Interrupt on line 6 */
#define EXTI_SWIE_SWIE7  ((uint32_t)0x00000080) /*!< Software Interrupt on line 7 */
#define EXTI_SWIE_SWIE8  ((uint32_t)0x00000100) /*!< Software Interrupt on line 8 */
#define EXTI_SWIE_SWIE9  ((uint32_t)0x00000200) /*!< Software Interrupt on line 9 */
#define EXTI_SWIE_SWIE10 ((uint32_t)0x00000400) /*!< Software Interrupt on line 10 */
#define EXTI_SWIE_SWIE11 ((uint32_t)0x00000800) /*!< Software Interrupt on line 11 */
#define EXTI_SWIE_SWIE12 ((uint32_t)0x00001000) /*!< Software Interrupt on line 12 */
#define EXTI_SWIE_SWIE13 ((uint32_t)0x00002000) /*!< Software Interrupt on line 13 */
#define EXTI_SWIE_SWIE14 ((uint32_t)0x00004000) /*!< Software Interrupt on line 14 */
#define EXTI_SWIE_SWIE15 ((uint32_t)0x00008000) /*!< Software Interrupt on line 15 */
#define EXTI_SWIE_SWIE16 ((uint32_t)0x00010000) /*!< Software Interrupt on line 16 */
#define EXTI_SWIE_SWIE17 ((uint32_t)0x00020000) /*!< Software Interrupt on line 17 */
#define EXTI_SWIE_SWIE18 ((uint32_t)0x00040000) /*!< Software Interrupt on line 18 */
#define EXTI_SWIE_SWIE19 ((uint32_t)0x00080000) /*!< Software Interrupt on line 19 */
#define EXTI_SWIE_SWIE20 ((uint32_t)0x00100000) /*!< Software Interrupt on line 20 */
#define EXTI_SWIE_SWIE21 ((uint32_t)0x00200000) /*!< Software Interrupt on line 21 */
#define EXTI_SWIE_SWIE22 ((uint32_t)0x00400000) /*!< Software Interrupt on line 22 */
#define EXTI_SWIE_SWIE23 ((uint32_t)0x00800000) /*!< Software Interrupt on line 23 */
#define EXTI_SWIE_SWIE24 ((uint32_t)0x01000000) /*!< Software Interrupt on line 24 */
#define EXTI_SWIE_SWIE25 ((uint32_t)0x02000000) /*!< Software Interrupt on line 25 */
#define EXTI_SWIE_SWIE26 ((uint32_t)0x04000000) /*!< Software Interrupt on line 26 */
#define EXTI_SWIE_SWIE27 ((uint32_t)0x08000000) /*!< Software Interrupt on line 27 */

/*******************  Bit definition for EXTI_PEND register  ********************/
#define EXTI_PEND_PEND0  ((uint32_t)0x00000001) /*!< Pending bit for line 0 */
#define EXTI_PEND_PEND1  ((uint32_t)0x00000002) /*!< Pending bit for line 1 */
#define EXTI_PEND_PEND2  ((uint32_t)0x00000004) /*!< Pending bit for line 2 */
#define EXTI_PEND_PEND3  ((uint32_t)0x00000008) /*!< Pending bit for line 3 */
#define EXTI_PEND_PEND4  ((uint32_t)0x00000010) /*!< Pending bit for line 4 */
#define EXTI_PEND_PEND5  ((uint32_t)0x00000020) /*!< Pending bit for line 5 */
#define EXTI_PEND_PEND6  ((uint32_t)0x00000040) /*!< Pending bit for line 6 */
#define EXTI_PEND_PEND7  ((uint32_t)0x00000080) /*!< Pending bit for line 7 */
#define EXTI_PEND_PEND8  ((uint32_t)0x00000100) /*!< Pending bit for line 8 */
#define EXTI_PEND_PEND9  ((uint32_t)0x00000200) /*!< Pending bit for line 9 */
#define EXTI_PEND_PEND10 ((uint32_t)0x00000400) /*!< Pending bit for line 10 */
#define EXTI_PEND_PEND11 ((uint32_t)0x00000800) /*!< Pending bit for line 11 */
#define EXTI_PEND_PEND12 ((uint32_t)0x00001000) /*!< Pending bit for line 12 */
#define EXTI_PEND_PEND13 ((uint32_t)0x00002000) /*!< Pending bit for line 13 */
#define EXTI_PEND_PEND14 ((uint32_t)0x00004000) /*!< Pending bit for line 14 */
#define EXTI_PEND_PEND15 ((uint32_t)0x00008000) /*!< Pending bit for line 15 */
#define EXTI_PEND_PEND16 ((uint32_t)0x00010000) /*!< Pending bit for line 16 */
#define EXTI_PEND_PEND17 ((uint32_t)0x00020000) /*!< Pending bit for line 17 */
#define EXTI_PEND_PEND18 ((uint32_t)0x00040000) /*!< Pending bit for line 18 */
#define EXTI_PEND_PEND19 ((uint32_t)0x00080000) /*!< Pending bit for line 19 */
#define EXTI_PEND_PEND20 ((uint32_t)0x00100000) /*!< Pending bit for line 20 */
#define EXTI_PEND_PEND21 ((uint32_t)0x00200000) /*!< Pending bit for line 21 */
#define EXTI_PEND_PEND22 ((uint32_t)0x00400000) /*!< Pending bit for line 22 */
#define EXTI_PEND_PEND23 ((uint32_t)0x00800000) /*!< Pending bit for line 23 */
#define EXTI_PEND_PEND24 ((uint32_t)0x01000000) /*!< Pending bit for line 24 */
#define EXTI_PEND_PEND25 ((uint32_t)0x02000000) /*!< Pending bit for line 25 */
#define EXTI_PEND_PEND26 ((uint32_t)0x04000000) /*!< Pending bit for line 26 */
#define EXTI_PEND_PEND27 ((uint32_t)0x08000000) /*!< Pending bit for line 27 */


/******************************************************************************/
/*                                                                            */
/*                             LCD Controller                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for LCD_CTRL register  *******************/
#define LCD_CTRL_BUFEN_Msk      ((uint32_t)0x00000100)
#define LCD_CTRL_BUFEN_Pos      (8U)
#define LCD_CTRL_BUFEN          (LCD_CTRL_BUFEN_Msk)                    /*!< High driving capacity buffer enable bit*/

#define LCD_CTRL_MUXSEG_Msk     ((uint32_t)0x00000080)
#define LCD_CTRL_MUXSEG_Pos     (7U)
#define LCD_CTRL_MUXSEG         (LCD_CTRL_MUXSEG_Msk)                   /*!< Mux segment enable bit*/

#define LCD_CTRL_BIAS_Msk       ((uint32_t)0x00000060)
#define LCD_CTRL_BIAS_Pos       (5U)
#define LCD_CTRL_BIAS           (LCD_CTRL_BIAS_Msk)
#define LCD_CTRL_BIAS_0         (0x1UL << LCD_CTRL_BIAS_Pos)            /*!< Bias selector bit*/
#define LCD_CTRL_BIAS_1         (0x2UL << LCD_CTRL_BIAS_Pos)

#define LCD_CTRL_DUTY_Msk       ((uint32_t)0x0000001C)
#define LCD_CTRL_DUTY_Pos       (2U)
#define LCD_CTRL_DUTY           (LCD_CTRL_DUTY_Msk)                     /*!< Duty selection bit*/
#define LCD_CTRL_DUTY_0         (0x1UL << LCD_CTRL_DUTY_Pos)
#define LCD_CTRL_DUTY_1         (0x2UL << LCD_CTRL_DUTY_Pos)
#define LCD_CTRL_DUTY_2         (0x4UL << LCD_CTRL_DUTY_Pos)

#define LCD_CTRL_VSEL_Msk       ((uint32_t)0x00000002)
#define LCD_CTRL_VSEL_Pos       (1U)
#define LCD_CTRL_VSEL           (LCD_CTRL_VSEL_Msk)                     /*!< Voltage source selection bit*/

#define LCD_CTRL_LCDEN_Msk      ((uint32_t)0x00000001)
#define LCD_CTRL_LCDEN_Pos      (0U)
#define LCD_CTRL_LCDEN          (LCD_CTRL_LCDEN_Msk)                    /*!< LCD controller enable bit*/

/*******************  Bit definition for LCD_FCTRL register  *******************/
#define LCD_FCTRL_PRES_Msk          ((uint32_t)0x03C00000)
#define LCD_FCTRL_PRES_Pos          (22U)
#define LCD_FCTRL_PRES              (LCD_FCTRL_PRES_Msk)                /*!< 16-bit prescaler bit*/
#define LCD_FCTRL_PRES_0            (0x1UL << LCD_FCTRL_PRES_Pos)
#define LCD_FCTRL_PRES_1            (0x2UL << LCD_FCTRL_PRES_Pos)
#define LCD_FCTRL_PRES_2            (0x4UL << LCD_FCTRL_PRES_Pos)
#define LCD_FCTRL_PRES_3            (0x8UL << LCD_FCTRL_PRES_Pos)

#define LCD_FCTRL_DIV_Msk           ((uint32_t)0x003C0000)
#define LCD_FCTRL_DIV_Pos           (18U)
#define LCD_FCTRL_DIV               (LCD_FCTRL_DIV_Msk)                 /*!< DIV clock divider bit*/
#define LCD_FCTRL_DIV_0             (0x1UL << LCD_FCTRL_DIV_Pos)
#define LCD_FCTRL_DIV_1             (0x2UL << LCD_FCTRL_DIV_Pos)
#define LCD_FCTRL_DIV_2             (0x4UL << LCD_FCTRL_DIV_Pos)
#define LCD_FCTRL_DIV_3             (0x8UL << LCD_FCTRL_DIV_Pos)

#define LCD_FCTRL_BLINK_Msk         ((uint32_t)0x00030000)
#define LCD_FCTRL_BLINK_Pos         (16U)
#define LCD_FCTRL_BLINK             (LCD_FCTRL_BLINK_Msk)               /*!< Blink mode selection bit*/
#define LCD_FCTRL_BLINK_0           (0x1UL << LCD_FCTRL_BLINK_Pos)
#define LCD_FCTRL_BLINK_1           (0x2UL << LCD_FCTRL_BLINK_Pos)

#define LCD_FCTRL_BLINKF_Msk        ((uint32_t)0x0000E000)
#define LCD_FCTRL_BLINKF_Pos        (13U)
#define LCD_FCTRL_BLINKF            (LCD_FCTRL_BLINKF_Msk)              /*!< Blink frequency selection bit*/
#define LCD_FCTRL_BLINKF_0          (0x1UL << LCD_FCTRL_BLINKF_Pos)
#define LCD_FCTRL_BLINKF_1          (0x2UL << LCD_FCTRL_BLINKF_Pos)
#define LCD_FCTRL_BLINKF_2          (0x4UL << LCD_FCTRL_BLINKF_Pos)

#define LCD_FCTRL_CONTRAST_Msk      ((uint32_t)0x00001C00)
#define LCD_FCTRL_CONTRAST_Pos      (10U)
#define LCD_FCTRL_CONTRAST          (LCD_FCTRL_CONTRAST_Msk)            /*!< Contrast Control bit*/
#define LCD_FCTRL_CONTRAST_0        (0x1UL << LCD_FCTRL_CONTRAST_Pos)
#define LCD_FCTRL_CONTRAST_1        (0x2UL << LCD_FCTRL_CONTRAST_Pos)
#define LCD_FCTRL_CONTRAST_2        (0x4UL << LCD_FCTRL_CONTRAST_Pos)

#define LCD_FCTRL_DEAD_Msk          ((uint32_t)0x00000380)
#define LCD_FCTRL_DEAD_Pos          (7U)
#define LCD_FCTRL_DEAD              (LCD_FCTRL_DEAD_Msk)                /*!< Dead time duration bit*/
#define LCD_FCTRL_DEAD_0            (0x1UL << LCD_FCTRL_DEAD_Pos)
#define LCD_FCTRL_DEAD_1            (0x2UL << LCD_FCTRL_DEAD_Pos)
#define LCD_FCTRL_DEAD_2            (0x4UL << LCD_FCTRL_DEAD_Pos)

#define LCD_FCTRL_PULSEON_Msk       ((uint32_t)0x00000070)
#define LCD_FCTRL_PULSEON_Pos       (4U)
#define LCD_FCTRL_PULSEON           (LCD_FCTRL_PULSEON_Msk)             /*!< Pulse on duration bit*/
#define LCD_FCTRL_PULSEON_0         (0x1UL << LCD_FCTRL_PULSEON_Pos)
#define LCD_FCTRL_PULSEON_1         (0x2UL << LCD_FCTRL_PULSEON_Pos)
#define LCD_FCTRL_PULSEON_2         (0x4UL << LCD_FCTRL_PULSEON_Pos)

#define LCD_FCTRL_UDDIE_Msk         ((uint32_t)0x00000008)
#define LCD_FCTRL_UDDIE_Pos         (3U)
#define LCD_FCTRL_UDDIE             (LCD_FCTRL_UDDIE_Msk)               /*!< Update display done interrupt enable bit*/

#define LCD_FCTRL_SOFIE_Msk         ((uint32_t)0x00000002)
#define LCD_FCTRL_SOFIE_Pos         (1U)
#define LCD_FCTRL_SOFIE             (LCD_FCTRL_SOFIE_Msk)               /*!< Start of frame interrupt enable bit*/

#define LCD_FCTRL_HDEN_Msk          ((uint32_t)0x00000001)
#define LCD_FCTRL_HDEN_Pos          (0U)
#define LCD_FCTRL_HDEN              (LCD_FCTRL_HDEN_Msk)                /*!< High drive enable bit*/

/*******************  Bit definition for LCD_STS register  *******************/
#define LCD_STS_FCRSF_Msk           ((uint32_t)0x00000020)
#define LCD_STS_FCRSF_Pos           (5U)
#define LCD_STS_FCRSF               (LCD_STS_FCRSF_Msk)                 /*!< LCD Frame Control Register Synchronization flag bit*/

#define LCD_STS_RDY_Msk             ((uint32_t)0x00000010)
#define LCD_STS_RDY_Pos             (4U)
#define LCD_STS_RDY                 (LCD_STS_RDY_Msk)                   /*!< VLCD Ready Flag bit*/

#define LCD_STS_UDD_Msk             ((uint32_t)0x00000008)
#define LCD_STS_UDD_Pos             (3U)
#define LCD_STS_UDD                 (LCD_STS_UDD_Msk)                   /*!< Update Display Done bit*/

#define LCD_STS_UDR_Msk             ((uint32_t)0x00000004)
#define LCD_STS_UDR_Pos             (2U)
#define LCD_STS_UDR                 (LCD_STS_UDR_Msk)                   /*!< Update Display Request bit*/

#define LCD_STS_SOF_Msk             ((uint32_t)0x00000002)
#define LCD_STS_SOF_Pos             (1U)
#define LCD_STS_SOF                 (LCD_STS_SOF_Msk)                   /*!< Start of Frame flag*/

#define LCD_STS_ENSTS_Msk           ((uint32_t)0x00000001)
#define LCD_STS_ENSTS_Pos           (0U)
#define LCD_STS_ENSTS               (LCD_STS_ENSTS_Msk)                 /*!< LCD state bit*/

/*******************  Bit definition for LCD_CLR register  *******************/
#define LCD_CLR_UDDCLR_Msk          ((uint32_t)0x00000008) /*!< Update display done clear bit*/
#define LCD_CLR_UDDCLR_Pos          (3U)
#define LCD_CLR_UDDCLR              (LCD_CLR_UDDCLR_Msk)

#define LCD_CLR_SOFCLR_Msk          ((uint32_t)0x00000002) /*!<Start of frame flag clear bit*/
#define LCD_CLR_SOFCLR_Pos          (1)
#define LCD_CLR_SOFCLR              (LCD_CLR_SOFCLR_Msk)

/*******************  Bit definition for LCD_RAM register  *******************/
#define LCD_RAM_SEG_DATA_RAM1_Msk           ((uint32_t)0xFFFFFFFFUL)
#define LCD_RAM_SEG_DATA_RAM2_COM0123_Msk   ((uint32_t)0x00000FFFUL)
#define LCD_RAM_SEG_DATA_RAM2_COM4567_Msk   ((uint32_t)0x000000FFUL)
#define LCD_RAM_SEG_DATA_RAMx_Pos           (0U)
#define LCD_RAM_SEG_DATA_RAM1               LCD_RAM_SEG_DATA_RAM1_Msk           /*!< LCD RAM data for LCD_RAM1_COMx, x=0...7*/
#define LCD_RAM_SEG_DATA_RAM2_COM0123       LCD_RAM_SEG_DATA_RAM2_COM0123_Msk   /*!< LCD RAM data for LCD_RAM2_COMx, x=0...3*/
#define LCD_RAM_SEG_DATA_RAM2_COM4567       LCD_RAM_SEG_DATA_RAM2_COM4567_Msk   /*!< LCD RAM data for LCD_RAM2_COMx, x=4...7*/


/******************************************************************************/
/*                                                                            */
/*                                 TSC Registers                              */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for TSC_CTRL register         ****************/
#define TSC_CTRL_TM2_ETR_CH1_Msk    ((uint32_t)0x2000)
#define TSC_CTRL_TM2_ETR_CH1_Pos    (13U)
#define TSC_CTRL_TM2_ETR_CH1        (TSC_CTRL_TM2_ETR_CH1_Msk)      /*!<TSC_out connected to TIM2_ETR and TIM2_CH1*/

#define TSC_CTRL_TM4_ETR_Msk        ((uint32_t)0x1000)
#define TSC_CTRL_TM4_ETR_Pos        (12U)
#define TSC_CTRL_TM4_ETR            (TSC_CTRL_TM4_ETR_Msk)          /*!<TSC_out connected to TIM4_ETR*/

#define TSC_CTRL_DET_INTEN_Msk      ((uint32_t)0x0400)
#define TSC_CTRL_DET_INTEN_Pos      (10U)
#define TSC_CTRL_DET_INTEN          (TSC_CTRL_DET_INTEN_Msk)        /*!<TSC interrupt control bit*/

#define TSC_CTRL_GREAT_DET_SEL_Msk  ((uint32_t)0x0200)
#define TSC_CTRL_GREAT_DET_SEL_Pos  (9U)
#define TSC_CTRL_GREAT_DET_SEL      (TSC_CTRL_GREAT_DET_SEL_Msk)    /*!<TSC great detect control*/

#define TSC_CTRL_LESS_DET_SEL_Msk   ((uint32_t)0x0100)
#define TSC_CTRL_LESS_DET_SEL_Pos   (8U)
#define TSC_CTRL_LESS_DET_SEL       (TSC_CTRL_LESS_DET_SEL_Msk)     /*!<TSC less detect control*/

#define TSC_CTRL_HW_DET_ST_Msk      ((uint32_t)0x0080)
#define TSC_CTRL_HW_DET_ST_Pos      (7U)
#define TSC_CTRL_HW_DET_ST          (TSC_CTRL_HW_DET_ST_Msk)        /*!<Status of TSC hardware detect mode*/

#define TSC_CTRL_HW_DET_MODE_Msk    ((uint32_t)0x0040)
#define TSC_CTRL_HW_DET_MODE_Pos    (6U)
#define TSC_CTRL_HW_DET_MODE        (TSC_CTRL_HW_DET_MODE_Msk)      /*!<TSC hardware detect mode control*/

#define TSC_CTRL_DET_FILTER_Msk     ((uint32_t)0x0030)
#define TSC_CTRL_DET_FILTER_Pos     (4U)
#define TSC_CTRL_DET_FILTER         (TSC_CTRL_DET_FILTER_Msk)       /*!<TSC filter for continuously detect */
#define TSC_CTRL_DET_FILTER_0       (0x1UL << TSC_CTRL_DET_FILTER_Pos)
#define TSC_CTRL_DET_FILTER_1       (0x2UL << TSC_CTRL_DET_FILTER_Pos)

#define TSC_CTRL_DET_PERIOD_Msk     ((uint32_t)0x000F)
#define TSC_CTRL_DET_PERIOD_Pos     (0U)
#define TSC_CTRL_DET_PERIOD         (TSC_CTRL_DET_PERIOD_Msk)       /*!<TSC detect time of one sample */
#define TSC_CTRL_DET_PERIOD_0       (0x1UL << TSC_CTRL_DET_PERIOD_Pos)
#define TSC_CTRL_DET_PERIOD_1       (0x2UL << TSC_CTRL_DET_PERIOD_Pos)
#define TSC_CTRL_DET_PERIOD_2       (0x4UL << TSC_CTRL_DET_PERIOD_Pos)
#define TSC_CTRL_DET_PERIOD_3       (0x8UL << TSC_CTRL_DET_PERIOD_Pos)

/****************  Bit definition for TSC TSC_CHNEN register    ****************/
#define TSC_CHNEN_CHN_SELx_Msk      ((uint32_t)0x00FFFFFF)
#define TSC_CHNEN_CHN_SELx_Pos      (0U)
#define TSC_CHNEN_CHN_SEL0          ((uint32_t)0x00000001) /*!< Channel 0 enable bit */
#define TSC_CHNEN_CHN_SEL1          ((uint32_t)0x00000002) /*!< Channel 1 enable bit */
#define TSC_CHNEN_CHN_SEL2          ((uint32_t)0x00000004) /*!< Channel 2 enable bit */
#define TSC_CHNEN_CHN_SEL3          ((uint32_t)0x00000008) /*!< Channel 3 enable bit */
#define TSC_CHNEN_CHN_SEL4          ((uint32_t)0x00000010) /*!< Channel 4 enable bit */
#define TSC_CHNEN_CHN_SEL5          ((uint32_t)0x00000020) /*!< Channel 5 enable bit */
#define TSC_CHNEN_CHN_SEL6          ((uint32_t)0x00000040) /*!< Channel 6 enable bit */
#define TSC_CHNEN_CHN_SEL7          ((uint32_t)0x00000080) /*!< Channel 7 enable bit */
#define TSC_CHNEN_CHN_SEL8          ((uint32_t)0x00000100) /*!< Channel 8 enable bit */
#define TSC_CHNEN_CHN_SEL9          ((uint32_t)0x00000200) /*!< Channel 9 enable bit */
#define TSC_CHNEN_CHN_SEL10         ((uint32_t)0x00000400) /*!< Channel 10 enable bit */
#define TSC_CHNEN_CHN_SEL11         ((uint32_t)0x00000800) /*!< Channel 11 enable bit */
#define TSC_CHNEN_CHN_SEL12         ((uint32_t)0x00001000) /*!< Channel 12 enable bit */
#define TSC_CHNEN_CHN_SEL13         ((uint32_t)0x00002000) /*!< Channel 13 enable bit */
#define TSC_CHNEN_CHN_SEL14         ((uint32_t)0x00004000) /*!< Channel 14 enable bit */
#define TSC_CHNEN_CHN_SEL15         ((uint32_t)0x00008000) /*!< Channel 15 enable bit */
#define TSC_CHNEN_CHN_SEL16         ((uint32_t)0x00010000) /*!< Channel 16 enable bit */
#define TSC_CHNEN_CHN_SEL17         ((uint32_t)0x00020000) /*!< Channel 17 enable bit */
#define TSC_CHNEN_CHN_SEL18         ((uint32_t)0x00040000) /*!< Channel 18 enable bit */
#define TSC_CHNEN_CHN_SEL19         ((uint32_t)0x00080000) /*!< Channel 19 enable bit */
#define TSC_CHNEN_CHN_SEL20         ((uint32_t)0x00100000) /*!< Channel 20 enable bit */
#define TSC_CHNEN_CHN_SEL21         ((uint32_t)0x00200000) /*!< Channel 21 enable bit */
#define TSC_CHNEN_CHN_SEL22         ((uint32_t)0x00400000) /*!< Channel 22 enable bit */
#define TSC_CHNEN_CHN_SEL23         ((uint32_t)0x00800000) /*!< Channel 23 enable bit */

/****************  Bit definition for TSC TSC_STS register      ****************/
#define TSC_STS_CHN_NUM_Msk         ((uint32_t)0x001F0000)
#define TSC_STS_CHN_NUM_Pos         (16U)
#define TSC_STS_CHN_NUM             TSC_STS_CHN_NUM_Msk     /*!<Current detect channel number */

#define TSC_STS_GREAT_DET_Msk        ((uint32_t)0x00002000)
#define TSC_STS_GREAT_DET_Pos       (13U)
#define TSC_STS_GREAT_DET           TSC_STS_GREAT_DET_Msk   /*!<Status of TSC great detect*/

#define TSC_STS_LESS_DET_Msk        ((uint32_t)0x00001000)
#define TSC_STS_LESS_DET_Pos        (12U)
#define TSC_STS_LESS_DET            TSC_STS_LESS_DET_Msk    /*!<Status of TSC less detect*/

#define TSC_STS_CNT_VAL_Msk         ((uint32_t)0x000007FF)
#define TSC_STS_CNT_VAL_Pos         (0U)
#define TSC_STS_CNT_VAL             TSC_STS_CNT_VAL_Msk     /*!<The pulse count value for current channel*/

/****************  Bit definition for TSC_ANA_CTRL register      ****************/
#define TSC_ANA_CTRL_SW_TSC_EN_Msk  ((uint32_t)0x0020)
#define TSC_ANA_CTRL_SW_TSC_EN_Pos  (5U)
#define TSC_ANA_CTRL_SW_TSC_EN      TSC_ANA_CTRL_SW_TSC_EN_Msk  /*!<TSC software detect mode control bit*/

#define TSC_ANA_CTRL_SW_PAD_MUX_Msk ((uint32_t)0x001F)
#define TSC_ANA_CTRL_SW_PAD_MUX_Pos (0U)
#define TSC_ANA_CTRL_SW_PAD_MUX     TSC_ANA_CTRL_SW_PAD_MUX_Msk /*!<Current channel number of TSC software detect mode*/

/****************  Bit definition for TSC_ANA_SEL register      ****************/
#define TSC_ANA_SEL_PAD_OPT_Msk     ((uint32_t)0x0040)
#define TSC_ANA_SEL_PAD_OPT_Pos     (6U)
#define TSC_ANA_SEL_PAD_OPT         TSC_ANA_SEL_PAD_OPT_Msk     /*!<TSC charge pad control bit,internal or external resistor*/

#define TSC_ANA_SEL_SP_OPT_Msk      ((uint32_t)0x0030)
#define TSC_ANA_SEL_SP_OPT_Pos      (4U)
#define TSC_ANA_SEL_SP_OPT          TSC_ANA_SEL_SP_OPT_Msk          /*!<TSC speed control bits*/
#define TSC_ANA_SEL_SP_OPT_0        (0x1UL << TSC_ANA_SEL_SP_OPT_Pos)
#define TSC_ANA_SEL_SP_OPT_1        (0x2UL << TSC_ANA_SEL_SP_OPT_Pos)

/*****************  Resistor value of  TSC_RESRx register  *****************/
#define TSC_RESRx_CHN_RESIST_Msk    ((uint32_t)0x00000007) /*!< TSC_RESRx CHx MASK */
#define TSC_RESRx_CHN_RESIST_0      ((uint32_t)0x00000000) /*!< 812.5K ohm */
#define TSC_RESRx_CHN_RESIST_1      ((uint32_t)0x00000001) /*!< 437.5K 0hm */
#define TSC_RESRx_CHN_RESIST_2      ((uint32_t)0x00000002) /*!< 281.25K ohm */
#define TSC_RESRx_CHN_RESIST_3      ((uint32_t)0x00000003) /*!< 218.75K ohm */
#define TSC_RESRx_CHN_RESIST_4      ((uint32_t)0x00000004) /*!< 187.5K ohm */
#define TSC_RESRx_CHN_RESIST_5      ((uint32_t)0x00000005) /*!< 156.25K ohm */
#define TSC_RESRx_CHN_RESIST_6      ((uint32_t)0x00000006) /*!< 125K ohm */
#define TSC_RESRx_CHN_RESIST_7      ((uint32_t)0x00000007) /*!< 93.75K ohm */

/*****************  Bit definition for TSC_RESR0 register  *****************/
#define TSC_RESR0_CHN_RESIST0_Pos   (0U)  /*!< TSC_RESR 0 channel 0 */
#define TSC_RESR0_CHN_RESIST1_Pos   (4U)  /*!< TSC_RESR 0 channel 1 */
#define TSC_RESR0_CHN_RESIST2_Pos   (8U)  /*!< TSC_RESR 0 channel 2 */
#define TSC_RESR0_CHN_RESIST3_Pos   (12U) /*!< TSC_RESR 0 channel 3 */
#define TSC_RESR0_CHN_RESIST4_Pos   (16U) /*!< TSC_RESR 0 channel 4 */
#define TSC_RESR0_CHN_RESIST5_Pos   (20U) /*!< TSC_RESR 0 channel 5 */
#define TSC_RESR0_CHN_RESIST6_Pos   (24U) /*!< TSC_RESR 0 channel 6 */
#define TSC_RESR0_CHN_RESIST7_Pos   (28U) /*!< TSC_RESR 0 channel 7 */

/*****************  Bit definition for TSC_RESR1 register  *****************/
#define TSC_RESR1_CHN_RESIST8_Pos   (0U)  /*!< TSC_RESR 1 channel 8  */
#define TSC_RESR1_CHN_RESIST9_Pos   (4U)  /*!< TSC_RESR 1 channel 9  */
#define TSC_RESR1_CHN_RESIST10_Pos  (8U)  /*!< TSC_RESR 1 channel 10 */
#define TSC_RESR1_CHN_RESIST11_Pos  (12U) /*!< TSC_RESR 1 channel 11 */
#define TSC_RESR1_CHN_RESIST12_Pos  (16U) /*!< TSC_RESR 1 channel 12 */
#define TSC_RESR1_CHN_RESIST13_Pos  (20U) /*!< TSC_RESR 1 channel 13 */
#define TSC_RESR1_CHN_RESIST14_Pos  (24U) /*!< TSC_RESR 1 channel 14 */
#define TSC_RESR1_CHN_RESIST15_Pos  (28U) /*!< TSC_RESR 1 channel 15 */

/*****************  Bit definition for TSC_RESR2 register  *****************/
#define TSC_RESR2_CHN_RESIST16_Pos  (0U)  /*!< TSC_RESR 2 channel 16 */
#define TSC_RESR2_CHN_RESIST17_Pos  (4U)  /*!< TSC_RESR 2 channel 17 */
#define TSC_RESR2_CHN_RESIST18_Pos  (8U)  /*!< TSC_RESR 2 channel 18 */
#define TSC_RESR2_CHN_RESIST19_Pos  (12U) /*!< TSC_RESR 2 channel 19 */
#define TSC_RESR2_CHN_RESIST20_Pos  (16U) /*!< TSC_RESR 2 channel 20 */
#define TSC_RESR2_CHN_RESIST21_Pos  (20U) /*!< TSC_RESR 2 channel 21 */
#define TSC_RESR2_CHN_RESIST22_Pos  (24U) /*!< TSC_RESR 2 channel 22 */
#define TSC_RESR2_CHN_RESIST23_Pos  (28U) /*!< TSC_RESR 2 channel 23 */

/****************  Bit definition for TSC_THRHDx register       ****************/
#define TSC_THRHDx_DELTA_Msk        ((uint32_t)0x00FF0000)
#define TSC_THRHDx_DELTA_Pos        (16U)
#define TSC_THRHDx_DELTA            TSC_THRHDx_DELTA_Msk    /*!<TSC_THRHD register delta bit */

#define TSC_THRHDx_BASE_Msk         ((uint32_t)0x000007FF)
#define TSC_THRHDx_BASE_Pos         (0U)
#define TSC_THRHDx_BASE             TSC_THRHDx_BASE_Msk     /*!<TSC_THRHD register base bit */



#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
 * @}
 */

#ifdef USE_STDPERIPH_DRIVER
#include "n32l40x_conf.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* __N32L40X_H__ */

